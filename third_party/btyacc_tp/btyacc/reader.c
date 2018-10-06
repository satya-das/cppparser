#include "defs.h"
#include "mstring.h"

/*  The line size must be a positive integer.  One hundred was chosen	*/
/*  because few lines in Yacc input grammars exceed 100 characters.	*/
/*  Note that if a line exceeds LINESIZE characters, the line buffer	*/
/*  will be expanded to accomodate it.					*/

#define LINESIZE 100

/* the maximum nember of arguments (inherited attributes) to a non-terminal */
/* this is a hard limit, but seems more than adequate */
#define MAXARGS	20

file_info *input_file = 0;

char *cache;
int cinc, cache_size;

int havetags=0;
static union_tag *tag_table = 0;

char saw_eof, unionized, location_defined;
char *cptr, *line;
int linesize;

struct ifdef_state {
  struct ifdef_state	*next;
  file_info	*file;
  int		lineno;
  int		state;	/* 0 = in true part
  			 * 1 = in false part looking for else/end
			 * 2 = in false part looking for end */
  int		nested;
} *ifdef = 0;

#define MAX_DEFD_VARS 1000
char *defd_vars[MAX_DEFD_VARS] = {NULL};

bucket *goal;
int prec;
int gensym;
char last_was_action, trialaction;

int maxitems;
bucket **pitem;

int maxrules;
bucket **plhs;

int name_pool_size;
char *name_pool;

char line_format[] = "#line %d \"%s\"\n";

int cachec(int c)
{
    assert(cinc >= 0);
    if (cinc >= cache_size) {
	if (!(cache = REALLOC(cache, cache_size += 256))) no_space(); }
    return cache[cinc++] = c;
}

/*
 * Open a file for input and make future input come from it
 *
 */
void read_from_file(char *name)
{
  file_info *n;
  FILE *fp;
  if (!name) {
    fp = stdin;
  } else if (!(fp = fopen(name, "r"))) {
    if (!input_file)
      open_error(name);	/* fatal -- does not return */
    error(input_file->lineno, 0, 0, "Cannot open include file %s", name);
    return; }
  n = NEW(file_info);
  n->next = input_file;
  n->file = fp;
  n->name = name ? strdup(name) : 0;
  n->lineno = 0;
  input_file = n;
}

/*
 * Get line
 * Return: 1 - reg. line finished with '\n'.
 *         0 - EOF.
 */
char *get_line() {
  extern int Eflag;
  int c;
  int i;

 NextLine:;
  i = 0;

  if (saw_eof || (c = getc(input_file->file)) == EOF) {

    /* end of current file */
    if (input_file->next) {
      void *t = input_file;
      while (ifdef && ifdef->file == input_file) {
	void *t1 = ifdef;
	error(ifdef->lineno, 0, 0, "No %%endif for %%if");
	ifdef = ifdef->next;
	FREE(t1); }
      fclose(input_file->file);
      FREE(input_file->name);
      input_file = input_file->next;
      FREE(t);
      goto NextLine;
    }

    if (line) FREE(line);
    saw_eof = 1;
    return line = cptr = 0;
  }
  if (line == 0 || linesize != (LINESIZE + 1)) {
    if (line) FREE(line);
    linesize = LINESIZE + 1;
    if (!(line = MALLOC(linesize))) no_space();
  }
  ++input_file->lineno;
  while ((line[i] = c) != '\n') {
    if (++i + 1 >= linesize)
      if (!(line = REALLOC(line, linesize += LINESIZE)))
	no_space();
    if ((c = getc(input_file->file)) == EOF) {
      c = '\n';
      saw_eof = 1;
    }
  }
  line[i+1] = 0;

  /* VM: process %ifdef/%ifndef line */
  if (!strncmp(&line[0], "%ifdef ", 7) || !strncmp(&line[0], "%ifndef ", 8)) {
    char *var_name = line + 7;
    char **ps;
    while (isspace(*var_name)) var_name++;
    for(i=0; var_name[i]!='\n' && var_name[i]!=' '; i++);
    var_name[i] = 0;
    if (ifdef && ifdef->state) {
      ifdef->nested++;
    } else {
      struct ifdef_state *n = NEW(struct ifdef_state);
      n->next = ifdef;
      n->file = input_file;
      n->lineno = input_file->lineno;
      n->state = line[3] != 'n';
      n->nested = 0;
      ifdef = n;
      /* Find the preprocessor variable */
      for(ps=&defd_vars[0]; *ps; ps++) {
	if(strcmp(*ps,var_name)==0) {
	  n->state ^= 1;
	  break;
	}
      }
    }
    goto NextLine;
  }

  /* VM: process %endif line */
  if(strncmp(&line[0], "%endif", 6)==0) {
    if(!ifdef || ifdef->file != input_file) {
      error(input_file->lineno, 0, 0, "There is no corresponding %%ifdef for %%endif");
    } else {
      if (ifdef->nested)
	ifdef->nested--;
      else {
	void *t = ifdef;
	ifdef = ifdef->next;
	FREE(t);
      }
    }
    goto NextLine;
  }

  /* VM: skip ordinary lines if ordered by %endif */
  if (ifdef && ifdef->state) {
    goto NextLine;
  }

  /* VM: Process %include line */
  if(strncmp(&line[0], "%include ", 9)==0) {
    char *name = line+9;
    while (isspace(*name)) name++;
    for(i=0; name[i]!='\n' && name[i]!=' '; i++);
    name[i] = 0;
    read_from_file(name);
    goto NextLine;
  }

  /* VM: process %define line */
  if(strncmp(&line[0], "%define ", 8)==0) {
    char var_name[80];
    int ii=0;
    char **ps;
    for(i=8; line[i]!='\n' && line[i]!=' '; i++, ii++) {
      var_name[ii] = line[i];
    }
    var_name[ii] = 0;
    /* Find the preprocessor variable */
    for(ps=&defd_vars[0]; *ps; ps++) {
      if(strcmp(*ps,var_name)==0) {
	error(input_file->lineno, 0, 0, "Preprocessor variable %s already defined", var_name);
      }
    }
    *ps = MALLOC(strlen(var_name)+1);
    strcpy(*ps, var_name);
    *++ps = NULL;
    goto NextLine;
  }

  if(Eflag) {
    printf("YPP: %s", line);
  }

  return cptr = line;
}

char *dup_line()
{
    register char *p, *s, *t;

    if (line == 0) return (0);
    s = line;
    while (*s != '\n') ++s;
    if (!(p = MALLOC(s - line + 1))) no_space();
    s = line;
    t = p;
    while ((*t++ = *s++) != '\n');
    return (p);
}

char *skip_comment()
{
    register char *s;

    int st_lineno = input_file->lineno;
    char *st_line = dup_line();
    char *st_cptr = st_line + (cptr - line);

    s = cptr + 2;
    while (s[0] != '*' || s[1] != '/') {
	if (*s == '\n') {
	    if ((s = get_line()) == 0)
		unterminated_comment(st_lineno, st_line, st_cptr); }
	else
	    ++s; }
    FREE(st_line);
    return cptr = s + 2;
}

int nextc()
{
    register char *s;

    if (line == 0 && get_line() == 0)
	return (EOF);
    s = cptr;
    for (;;) {
	switch (*s) {
	case '\n':
	    if ((s = get_line()) == 0) return EOF;
	    break;
	case ' ':
	case '\t':
	case '\f':
	case '\r':
	case '\v':
	case ',':
	case ';':
	    ++s;
	    break;
	case '\\':
	    cptr = s;
	    return ('%');
	case '/':
	    if (s[1] == '*') {
		cptr = s;
		s = skip_comment();
		break; }
	    else if (s[1] == '/') {
		if ((s = get_line()) == 0) return EOF;
		break; }
	    /* fall through */
	default:
	    cptr = s;
	    return (*s); } }
}

static struct keyword { char name[12]; int token; } keywords[] = {
    { "binary", NONASSOC },
    { "destructor", DESTRUCTOR },
    { "ident", IDENT },
    { "left", LEFT },
    { "location", LOCATION },
    { "nonassoc", NONASSOC },
    { "position", LOCATION },
    { "right", RIGHT },
    { "start", START },
    { "term", TOKEN },
    { "token", TOKEN },
    { "type", TYPE },
    { "union", UNION },
};

int keyword()
{
  register int	c;
  char		*t_cptr = cptr;
  struct keyword	*key;

  c = *++cptr;
  if (isalpha(c)) {
    cinc = 0;
    while (isalnum(c) || c == '_' || c == '.' || c == '$') {
      cachec(tolower(c));
      c = *++cptr;
    }
    cachec(NUL);

    if ((key = bsearch(cache, keywords, sizeof(keywords)/sizeof(*key),
		       sizeof(*key),
		       (int (*)(const void *, const void *))strcmp)))
      return key->token;
  } else {
    ++cptr;
    if (c == '{') return (TEXT);
    if (c == '%' || c == '\\') return (MARK);
    if (c == '<') return (LEFT);
    if (c == '>') return (RIGHT);
    if (c == '0') return (TOKEN);
    if (c == '2') return (NONASSOC);
    if (c == '@') return (LOCATION);
    if (c == '$') return (UNION);
  }
  syntax_error(input_file->lineno, line, t_cptr);
  /*NOTREACHED*/
  return 0;
}

void copy_ident()
{
    register int c;
    register FILE *f = output_file;

    if ((c = nextc()) == EOF) unexpected_EOF();
    if (c != '"') syntax_error(input_file->lineno, line, cptr);
    if (!rflag) ++outline;
    fprintf(f, "#ident \"");
    for (;;) {
	c = *++cptr;
	if (c == '\n') {
	    fprintf(f, "\"\n");
	    return; }
	putc(c, f);
	if (c == '"') {
	    putc('\n', f);
	    ++cptr;
	    return; } }
}

#define OUTC(c)	do { /* output a character on f1 and f2, if non-null */ \
    int _c = (c);							\
    putc(_c, f1);							\
    if (f2) putc(_c, f2);						\
    } while(0)

void copy_string(int quote, FILE *f1, FILE *f2)
{
register int	c;
int		s_lineno = input_file->lineno;
char		*s_line = dup_line();
char		*s_cptr = s_line + (cptr - line - 1);

    for (;;) {
	OUTC(c = *cptr++);
	if (c == quote) {
	    FREE(s_line);
	    return; }
	if (c == '\n')
	    unterminated_string(s_lineno, s_line, s_cptr);
	if (c == '\\') {
	    OUTC(c = *cptr++);
	    if (c == '\n') {
		if (get_line() == 0)
		    unterminated_string(s_lineno, s_line, s_cptr); } } }
}

void copy_comment(FILE *f1, FILE *f2)
{
register int	c;

    if ((c = *cptr) == '/') {
	OUTC('*');
	while ((c = *++cptr) != '\n') {
	    OUTC(c);
	    if (c == '*' && cptr[1] == '/')
		OUTC(' '); }
	OUTC('*'); OUTC('/'); }
    else if (c == '*') {
	int c_lineno = input_file->lineno;
	char *c_line = dup_line();
	char *c_cptr = c_line + (cptr - line - 1);
	OUTC(c);
	while ((c = *++cptr) != '*' || cptr[1] != '/') {
	    OUTC(c);
	    if (c == '\n') {
		if (get_line() == 0)
		    unterminated_comment(c_lineno, c_line, c_cptr); } }
	OUTC(c);
	OUTC('/');
	FREE(c_line);
	cptr += 2; }
}

#undef OUTC

void copy_text()
{
    register int c;
    register FILE *f = text_file;
    int need_newline = 0;
    int t_lineno = input_file->lineno;
    char *t_line = dup_line();
    char *t_cptr = t_line + (cptr - line - 2);

    if (*cptr == '\n') {
	if (get_line() == 0)
	    unterminated_text(t_lineno, t_line, t_cptr); }
    if (!lflag) fprintf(f, line_format, input_file->lineno, input_file->name);
loop:
    switch (c = *cptr++) {
    case '\n':
	putc('\n', f);
	need_newline = 0;
	if (get_line()) goto loop;
	unterminated_text(t_lineno, t_line, t_cptr);
    case '\'':
    case '"':
	putc(c, f);
	copy_string(c, f, 0);
	need_newline = 1;
	goto loop;
    case '/':
	putc(c, f);
	copy_comment(f, 0);
	need_newline = 1;
	goto loop;
    case '%':
    case '\\':
	if (*cptr == '}') {
	    if (need_newline) putc('\n', f);
	    ++cptr;
	    FREE(t_line);
	    return; }
	/* fall through */
    default:
	putc(c, f);
	need_newline = 1;
	goto loop; }
}

void copy_structdecl(const char *kind, const char *name)
{
    FILE *dc_file;
    register int c;
    int depth;
    int u_lineno = input_file->lineno;
    char *u_line = dup_line();
    char *u_cptr = u_line + (cptr - line - 6);

    /* VM: Print to either code file or defines file but not to both */
    dc_file = dflag ? union_file : text_file;
    fprintf(dc_file, "\n");
    if (!lflag)
	fprintf(dc_file, line_format, input_file->lineno, input_file->name);
    fprintf(dc_file, "typedef %s", kind);
    depth = 0;
loop:
    c = *cptr++;
    putc(c, dc_file);
    switch (c) {
    case '\n':
      get_line();
      if (line == 0) unterminated_union(u_lineno, u_line, u_cptr);
      goto loop;
    case '{':
      ++depth;
      goto loop;
    case '}':
      if (--depth == 0) {
	fprintf(dc_file, " %s;\n", name);
	FREE(u_line);
	break; }
      goto loop;
    case '\'':
    case '"':
      copy_string(c, dc_file, 0);
      goto loop;
    case '/':
      copy_comment(dc_file, 0);
      goto loop;
    default:
      goto loop;
    }
    fprintf(dc_file, "#define %s %s\n", name, name);
}

int hexval(int c)
{
    if (c >= '0' && c <= '9')
	return (c - '0');
    if (c >= 'A' && c <= 'F')
	return (c - 'A' + 10);
    if (c >= 'a' && c <= 'f')
	return (c - 'a' + 10);
    return (-1);
}

bucket *get_literal()
{
    register int c, quote;
    register int i;
    register int n;
    register char *s;
    register bucket *bp;
    int s_lineno = input_file->lineno;
    char *s_line = dup_line();
    char *s_cptr = s_line + (cptr - line);

    quote = *cptr++;
    cinc = 0;
    for (;;) {
	c = *cptr++;
	if (c == quote) break;
	if (c == '\n') unterminated_string(s_lineno, s_line, s_cptr);
	if (c == '\\') {
	    char *c_cptr = cptr - 1;
	    c = *cptr++;
	    switch (c) {
	    case '\n':
		get_line();
		if (line == 0) unterminated_string(s_lineno, s_line, s_cptr);
		continue;
	    case '0': case '1': case '2': case '3':
	    case '4': case '5': case '6': case '7':
		n = c - '0';
		c = *cptr;
		if (IS_OCTAL(c)) {
		    n = (n << 3) + (c - '0');
		    c = *++cptr;
		    if (IS_OCTAL(c)) {
			n = (n << 3) + (c - '0');
			++cptr; } }
		if (n > MAXCHAR) illegal_character(c_cptr);
		c = n;
	    	break;
	    case 'x':
		c = *cptr++;
		n = hexval(c);
		if (n < 0 || n >= 16)
		    illegal_character(c_cptr);
		for (;;) {
		    c = *cptr;
		    i = hexval(c);
		    if (i < 0 || i >= 16) break;
		    ++cptr;
		    n = (n << 4) + i;
		    if (n > MAXCHAR) illegal_character(c_cptr); }
		c = n;
		break;
	    case 'a': c = 7; break;
	    case 'b': c = '\b'; break;
	    case 'f': c = '\f'; break;
	    case 'n': c = '\n'; break;
	    case 'r': c = '\r'; break;
	    case 't': c = '\t'; break;
	    case 'v': c = '\v'; break; } }
	cachec(c); }
    FREE(s_line);

    n = cinc;
    s = MALLOC(n);
    if (s == 0) no_space();

    for (i = 0; i < n; ++i)
	s[i] = cache[i];

    cinc = 0;
    if (n == 1)
	cachec('\'');
    else
	cachec('"');

    for (i = 0; i < n; ++i) {
	c = ((unsigned char *)s)[i];
	if (c == '\\' || c == cache[0]) {
	    cachec('\\');
	    cachec(c); }
	else if (isprint(c))
	    cachec(c);
	else {
	    cachec('\\');
	    switch (c) {
	    case 7: cachec('a'); break;
	    case '\b': cachec('b'); break;
	    case '\f': cachec('f'); break;
	    case '\n': cachec('n'); break;
	    case '\r': cachec('r'); break;
	    case '\t': cachec('t'); break;
	    case '\v': cachec('v'); break;
	    default:
		cachec(((c >> 6) & 7) + '0');
		cachec(((c >> 3) & 7) + '0');
		cachec((c & 7) + '0');
		break; } } }
    if (n == 1)
	cachec('\'');
    else
	cachec('"');

    cachec(NUL);
    bp = lookup(cache);
    bp->class = TERM;
    if (n == 1 && bp->value == UNDEFINED)
	bp->value = *(unsigned char *)s;
    FREE(s);

    return (bp);
}

int is_reserved(char *name)
{
    char *s;

    if (strcmp(name, ".") == 0 ||
	strcmp(name, "$accept") == 0 ||
	strcmp(name, "$end") == 0)
	return (1);

    if (name[0] == '$' && name[1] == '$' && isdigit(name[2])) {
	s = name + 3;
	while (isdigit(*s)) ++s;
	if (*s == NUL) return (1); }

    return (0);
}

bucket *get_name()
{
    register int c;

    cinc = 0;
    for (c = *cptr; IS_IDENT(c); c = *++cptr)
	cachec(c);
    cachec(NUL);
    if (is_reserved(cache)) used_reserved(cache);
    return (lookup(cache));
}

int get_number()
{
    register int c;
    register int n;

    n = 0;
    for (c = *cptr; isdigit(c); c = *++cptr)
	n = 10*n + (c - '0');
    return (n);
}

static union_tag *cache_tag(char *tag, int len)
{
union_tag	**p, *rv;

    for (p = &tag_table; *p; p = &(*p)->next) {
	if (strncmp(tag, (*p)->name, len) == 0 && (*p)->name[len] == 0)
	    return *p; }
    if (!(*p = rv = NEW(union_tag))) no_space();
    if (!(rv->name = MALLOC(len + 1))) no_space();
    rv->next = 0;
    strncpy(rv->name, tag, len);
    rv->name[len] = 0;
    rv->dtor = 0;
    return rv;
}

union_tag *get_tag(int braces)
{
    register int c = *cptr;
    int t_lineno = input_file->lineno;
    char *t_line = dup_line();
    char *t_cptr = t_line + (cptr - line);

    if (braces) {
	if (c != '<')
	    illegal_tag(t_lineno, t_line, t_cptr);
	++cptr;
	c = nextc();
	if (c == EOF) unexpected_EOF(); }
    if (!isalpha(c) && c != '_' && c != '$')
	illegal_tag(t_lineno, t_line, t_cptr);
    cinc = 0;
    do { cachec(c); c = *++cptr; } while (IS_IDENT(c));
    if (braces) {
	c = nextc();
	if (c == EOF) unexpected_EOF();
	if (c != '>')
	    illegal_tag(t_lineno, t_line, t_cptr);
	++cptr; }
    FREE(t_line);
    havetags = 1;
    return cache_tag(cache, cinc);
}

void declare_tokens(int assoc)
{
    register int c;
    register bucket *bp;
    int value;
    union_tag *tag = 0;

    if (assoc != TOKEN) ++prec;

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c == '<') {
	tag = get_tag(1);
	c = nextc();
	if (c == EOF) unexpected_EOF(); }

    for (;;) {
	if (isalpha(c) || c == '_' || c == '.' || c == '$')
	    bp = get_name();
	else if (c == '\'' || c == '"')
	    bp = get_literal();
	else
	    return;

	if (bp == goal) tokenized_start(bp->name);
	bp->class = TERM;

	if (tag) {
	    if (bp->tag && tag != bp->tag)
		retyped_warning(bp->name);
	    bp->tag = tag; }

	if (assoc != TOKEN) {
	    if (bp->prec && prec != bp->prec)
		reprec_warning(bp->name);
	    bp->assoc = assoc;
	    bp->prec = prec; }

	c = nextc();
	if (c == EOF) unexpected_EOF();
	value = UNDEFINED;
	if (isdigit(c)) {
	    value = get_number();
	    if (bp->value != UNDEFINED && value != bp->value)
		revalued_warning(bp->name);
	    bp->value = value;
	    c = nextc();
	    if (c == EOF) unexpected_EOF(); } }
}

static void declare_argtypes(bucket *bp)
{
char	*tags[MAXARGS];
int	args = 0, c;

    if (bp->args >= 0) retyped_warning(bp->name);
    cptr++; /* skip open paren */
    for (;;) {
	c = nextc();
	if (c == EOF) unexpected_EOF();
	if (c != '<') syntax_error(input_file->lineno, line, cptr);
	tags[args++] = get_tag(1)->name;
	c = nextc();
	if (c == ')') break;
	if (c == EOF) unexpected_EOF(); }
    cptr++; /* skip close paren */
    bp->args = args;
    if (!(bp->argnames = NEW2(args, char *))) no_space();
    if (!(bp->argtags = NEW2(args, char *))) no_space();
    while (--args >= 0) {
	bp->argtags[args] = tags[args];
	bp->argnames[args] = 0; }
}

void declare_types()
{
    register int c;
    register bucket *bp=0;
    union_tag *tag=0;

    c = nextc();
    if (c == '<') {
	tag = get_tag(1);
	c = nextc(); }
    if (c == EOF) unexpected_EOF();

    for (;;) {
	c = nextc();
	if (isalpha(c) || c == '_' || c == '.' || c == '$') {
	    bp = get_name();
	    if (nextc() == '(')
		declare_argtypes(bp);
	    else
		bp->args = 0; }
	else if (c == '\'' || c == '"') {
	    bp = get_literal();
	    bp->args = 0; }
	else
	    return;

	if (tag) {
	    if (bp->tag && tag != bp->tag)
		retyped_warning(bp->name);
	    bp->tag = tag; } }
}

void declare_start()
{
    register int c;
    register bucket *bp;

    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (!isalpha(c) && c != '_' && c != '.' && c != '$')
	syntax_error(input_file->lineno, line, cptr);
    bp = get_name();
    if (bp->class == TERM)
	terminal_start(bp->name);
    if (goal && goal != bp)
	restarted_warning();
    goal = bp;
}

void read_declarations()
{
    register int c, k;

    cache_size = 256;
    cache = MALLOC(cache_size);
    if (cache == 0) no_space();

    for (;;) {
	c = nextc();
	if (c == EOF) unexpected_EOF();
	if (c != '%') syntax_error(input_file->lineno, line, cptr);
	switch (k = keyword()) {
	case MARK:
	    return;
	case IDENT:
	    copy_ident();
	    break;
	case TEXT:
	    copy_text();
	    break;
	case UNION:
	    if (unionized) over_unionized(cptr - 6);
	    unionized = 1;
	    copy_structdecl("union", "YYSTYPE");
	    break;
	case TOKEN:
	case LEFT:
	case RIGHT:
	case NONASSOC:
	    declare_tokens(k);
	    break;
	case TYPE:
	    declare_types();
	    break;
	case DESTRUCTOR:
	    declare_destructor();
	    break;
	case LOCATION:
	    if (location_defined) repeat_location_defined(cptr - 9);
	    location_defined = 1;
	    copy_structdecl("struct", "YYPOSN");
	    break;
	case START:
	    declare_start();
	    break; } }
}

void initialize_grammar()
{
    nitems = 4;
    maxitems = 300;
    pitem = NEW2(maxitems, bucket *);
    if (pitem == 0) no_space();
    pitem[0] = 0;
    pitem[1] = 0;
    pitem[2] = 0;
    pitem[3] = 0;

    nrules = 3;
    maxrules = 100;
    plhs = NEW2(maxrules, bucket *);
    if (plhs == 0) no_space();
    plhs[0] = 0;
    plhs[1] = 0;
    plhs[2] = 0;
    rprec = NEW2(maxrules, Yshort);
    if (rprec == 0) no_space();
    rprec[0] = 0;
    rprec[1] = 0;
    rprec[2] = 0;
    rassoc = NEW2(maxrules, char);
    if (rassoc == 0) no_space();
    rassoc[0] = TOKEN;
    rassoc[1] = TOKEN;
    rassoc[2] = TOKEN;
}

void expand_items()
{
    maxitems += 300;
    pitem = RENEW(pitem, maxitems, bucket *);
    if (pitem == 0) no_space();
}

void expand_rules()
{
    maxrules += 100;
    plhs = RENEW(plhs, maxrules, bucket *);
    if (plhs == 0) no_space();
    rprec = RENEW(rprec, maxrules, Yshort);
    if (rprec == 0) no_space();
    rassoc = RENEW(rassoc, maxrules, char);
    if (rassoc == 0) no_space();
}

/* set in copy_args and incremented by the various routines that will rescan
** the argument list as appropriate */
static int rescan_lineno;

static char *copy_args(int *alen)
{
struct mstring	*s = msnew();
int		depth = 0, len = 1, c;
char		quote = 0;
int		a_lineno = input_file->lineno;
char		*a_line = dup_line();
char		*a_cptr = a_line + (cptr - line - 1);
int		skipspace = 1;

    rescan_lineno = input_file->lineno;
    while ((c = *cptr++) != ')' || depth || quote) {
	if (c == ',' && !quote && !depth) {
	    len++;
	    mstrim(s, " ");
	    mputc(s, 0);
	    skipspace = 1;
	    continue; }
	if (!quote && c == '/' && (*cptr == '/' || *cptr == '*')) {
	    if (*cptr == '/') {
		c = '\n';
	    } else {
		cptr--;
		skip_comment();
		c = ' '; } }
	if (!quote && isspace(c)) {
	    if (!skipspace) {
		mputc(s, ' ');
		skipspace = 1; }
	} else {
	    mputc(s, c);
	    skipspace = 0; }
	if (c == '\n') {
	    get_line();
	    if (!line) {
		if (quote)
		    unterminated_string(a_lineno, a_line, a_cptr);
		else
		    unterminated_arglist(a_lineno, a_line, a_cptr); } }
	else if (quote) {
	    if (c == quote) quote = 0;
	    else if (c == '\\') {
		if (*cptr != '\n') mputc(s, *cptr++); } }
	else {
	    if (c == '(') depth++;
	    else if (c == ')') depth--;
	    else if (c == '\"' || c == '\'') quote = c; } }
    if (alen) *alen = len;
    FREE(a_line);
    mstrim(s, " ");
    return msdone(s);
}

static char *parse_id(char *p, char **save)
{
char	*b;

    while (isspace(*p)) if (*p++ == '\n') rescan_lineno++;
    if (!isalpha(*p) && *p != '_') return 0;
    b = p;
    while (isalnum(*p) || *p == '_' || *p == '$') p++;
    if (save) {
	*save = cache_tag(b, p-b)->name; }
    return p;
}

static char *parse_int(char *p, int *save)
{
int	neg=0, val=0;

    while (isspace(*p)) if (*p++ == '\n') rescan_lineno++;
    if (*p == '-') {
	neg=1;
	p++; }
    if (!isdigit(*p)) return 0;
    while (isdigit(*p))
	val = val*10 + *p++ - '0';
    if (neg) val = -val;
    if (save) *save = val;
    return p;
}

static void parse_arginfo(bucket *a, char *args, int argslen)
{
char	*p=args, *tmp;
int	i, redec=0;

    if (a->args >= 0) {
	if (a->args != argslen)
	    error(rescan_lineno, 0, 0, "number of arguments of %s does't "
		  "agree with previous declaration", a->name);
	redec = 1; }
    else {
	if (!(a->args = argslen)) return;
	if (!(a->argnames = NEW2(argslen, char *)) ||
	    !(a->argtags = NEW2(argslen, char *)))
	    no_space(); }
    if (!args) return;
    for (i=0; i<argslen; i++) {
	while (isspace(*p)) if (*p++ == '\n') rescan_lineno++;
	if (*p++ != '$') bad_formals();
	while (isspace(*p)) if (*p++ == '\n') rescan_lineno++;
	if (*p == '<') {
	    havetags = 1;
	    if (!(p = parse_id(p+1, &tmp))) bad_formals();
	    while (isspace(*p)) if (*p++ == '\n') rescan_lineno++;
	    if (*p++ != '>') bad_formals();
	    if (redec) {
		if (a->argtags[i] != tmp)
		    error(rescan_lineno, 0, 0, "type of argument %d to %s "
			  "doesn't agree with previous declaration", i+1,
			  a->name); }
	    else
		a->argtags[i] = tmp; }
	else if (!redec)
	    a->argtags[i] = 0;
	if (!(p = parse_id(p, &a->argnames[i]))) bad_formals();
	while (isspace(*p)) if (*p++ == '\n') rescan_lineno++;
	if (*p++) bad_formals(); }
    free(args);
}

static char *compile_arg(char **theptr, char *yyvaltag)
{
char		*p = *theptr;
struct mstring	*c = msnew();
int		i, j, n;
Yshort		*offsets=0, maxoffset;
bucket		**rhs;

    /* FIXME -- the argument offset table is computed independently in
     * FIXME -- several places (compile_arg, copy_action, and can_elide_arg)
     * FIXME -- those multiple implementations should be factored into
     * FIXME -- a single function. */
    maxoffset = n = 0;
    for (i = nitems - 1; pitem[i]; --i) {
	n++;
	if (pitem[i]->class != ARGUMENT)
	    maxoffset++; }
    if (maxoffset > 0) {
	offsets = NEW2(maxoffset+1, Yshort);
	if (offsets == 0) no_space(); }
    for (j=0, i++; i<nitems; i++)
	if (pitem[i]->class != ARGUMENT)
	    offsets[++j] = i - nitems + 1;
    rhs = pitem + nitems - 1;

    if (yyvaltag)
	msprintf(c, "yyval.%s = ", yyvaltag);
    else
	msprintf(c, "yyval = ");
    while (*p) {
      if (*p == '$') {
	char	*tag = 0;
	if (*++p == '<')
	  if (!(p = parse_id(++p, &tag)) || *p++ != '>')
	    illegal_tag(rescan_lineno, 0, 0);
	if (isdigit(*p) || *p == '-') {
	  int val;
	  if (!(p = parse_int(p, &val)))
	    dollar_error(rescan_lineno, 0, 0);
	  if (val <= 0) i = val - n;
	  else if (val > maxoffset) {
	    dollar_warning(rescan_lineno, val);
	    i = val - maxoffset;
	  } else {
	    i = offsets[val];
	    if (!tag && !(tag = rhs[i]->tag->name) && havetags)
	      untyped_rhs(val, rhs[i]->name);
	  }
	  msprintf(c, "yyvsp[%d]", i);
	  if (tag) msprintf(c, ".%s", tag);
	  else if (havetags)
	    unknown_rhs(val);
	} else if (isalpha(*p) || *p == '_') {
	  char	*arg;
	  if (!(p = parse_id(p, &arg)))
	    dollar_error(rescan_lineno, 0, 0);
	  for (i=plhs[nrules]->args-1; i>=0; i--)
	    if (arg == plhs[nrules]->argnames[i]) break;
	  if (i<0)
	    error(rescan_lineno, 0, 0, "unknown argument $%s", arg);
	  if (!tag)
	    tag = plhs[nrules]->argtags[i];
	  msprintf(c, "yyvsp[%d]", i - plhs[nrules]->args + 1 - n);
	  if (tag) msprintf(c, ".%s", tag);
	  else if (havetags)
	    error(rescan_lineno, 0, 0, "untyped argument $%s", arg); }
	else
	  dollar_error(rescan_lineno, 0, 0);
      } else if (*p == '@') {
	if (isdigit(*p) || *p == '-') {
	  int val;
	  if (!(p = parse_int(p, &val)))
	    at_error(rescan_lineno, 0, 0);
	  if (val <= 0) i = val - n;
	  else if (val > maxoffset) {
	    at_warning(rescan_lineno, val);
	    i = val - maxoffset;
	  } else {
	    i = offsets[val];
	  }
	  msprintf(c, "yypsp[%d]", i);
	} else
	  at_error(rescan_lineno, 0, 0);
      } else {
	if (*p == '\n') rescan_lineno++;
	mputc(c, *p++);
      }
    }
    *theptr = p;
    if (maxoffset > 0) FREE(offsets);
    return msdone(c);
}

static int can_elide_arg(char **theptr, char *yyvaltag)
{
char		*p = *theptr;
int		rv = 0;
int		i, j, n=0;
Yshort		*offsets=0, maxoffset=0;
bucket		**rhs;
char		*tag = 0;

    if (*p++ != '$') return 0;
    if (*p == '<') {
      if (!(p = parse_id(++p, &tag)) || *p++ != '>')
	return 0; }
    /* FIXME -- the argument offset table is computed independently in
     * FIXME -- several places (compile_arg, copy_action, and can_elide_arg)
     * FIXME -- those multiple implementations should be factored into
     * FIXME -- a single function. */
    for (i = nitems - 1; pitem[i]; --i) {
	n++;
	if (pitem[i]->class != ARGUMENT)
	    maxoffset++; }
    if (maxoffset > 0) {
	offsets = NEW2(maxoffset+1, Yshort);
	if (offsets == 0) no_space(); }
    for (j=0, i++; i<nitems; i++)
	if (pitem[i]->class != ARGUMENT)
	    offsets[++j] = i - nitems + 1;
    rhs = pitem + nitems - 1;
    if (isdigit(*p) || *p == '-') {
      int val;
      if (!(p = parse_int(p, &val)))
	rv = 0;
      else {
	if (val <= 0)
	  rv = 1 - val + n;
	else if (val > maxoffset)
	  rv = 0;
	else {
	  i = offsets[val];
	  rv = 1 - i;
	  if (!tag) tag = rhs[i]->tag->name; } }
    } else if (isalpha(*p) || *p == '_') {
      char	*arg;
      if (!(p = parse_id(p, &arg)))
	return 0;
      for (i=plhs[nrules]->args-1; i>=0; i--)
	if (arg == plhs[nrules]->argnames[i]) break;
      if (i>=0) {
	if (!tag)
	  tag = plhs[nrules]->argtags[i];
	rv = plhs[nrules]->args + n - i; } }
    if (tag && yyvaltag) {
      if (strcmp(tag, yyvaltag)) rv = 0;
    } else if (tag || yyvaltag)
      rv = 0;
    if (maxoffset > 0) FREE(offsets);
    if (*p || rv <= 0)
      return 0;
    *theptr = p+1;
    return rv;
}

#define ARG_CACHE_SIZE	1024
static struct arg_cache {
    struct arg_cache	*next;
    char		*code;
    int			rule;
    } *arg_cache[ARG_CACHE_SIZE];

static int lookup_arg_cache(char *code)
{
struct arg_cache	*entry;

    entry = arg_cache[strnshash(code) % ARG_CACHE_SIZE];
    while (entry) {
	if (!strnscmp(entry->code, code)) return entry->rule;
	entry = entry->next; }
    return -1;
}

static void insert_arg_cache(char *code, int rule)
{
struct arg_cache	*entry = NEW(struct arg_cache);
int			i;

    if (!entry) no_space();
    i = strnshash(code) % ARG_CACHE_SIZE;
    entry->code = code;
    entry->rule = rule;
    entry->next = arg_cache[i];
    arg_cache[i] = entry;
}

static void clean_arg_cache(void)
{
struct arg_cache	*e, *t;
int			i;

    for (i=0; i<ARG_CACHE_SIZE; i++) {
	for (e=arg_cache[i]; (t=e); e=e->next, FREE(t))
	    free(e->code);
	arg_cache[i] = 0; }
}

void advance_to_start()
{
    register int c;
    register bucket *bp;
    char *s_cptr;
    int s_lineno;
    char	*args = 0;
    int		argslen = 0;

    for (;;) {
	c = nextc();
	if (c != '%') break;
	s_cptr = cptr;
	switch (keyword()) {
	case MARK:
	    no_grammar();
	case TEXT:
	    copy_text();
	    break;
	case START:
	    declare_start();
	    break;
	default:
	    syntax_error(input_file->lineno, line, s_cptr); } }

    c = nextc();
    if (!isalpha(c) && c != '_' && c != '.' && c != '_')
	syntax_error(input_file->lineno, line, cptr);
    bp = get_name();
    if (goal == 0) {
	if (bp->class == TERM)
	    terminal_start(bp->name);
	goal = bp; }

    s_lineno = input_file->lineno;
    c = nextc();
    if (c == EOF) unexpected_EOF();
    if (c == '(') {
	++cptr;
	args = copy_args(&argslen);
	if (args == 0) no_space();
	c = nextc(); }
    if (c != ':') syntax_error(input_file->lineno, line, cptr);
    start_rule(bp, s_lineno);
    parse_arginfo(bp, args, argslen);
    ++cptr;
}

void start_rule(bucket *bp, int s_lineno)
{
    if (bp->class == TERM)
	terminal_lhs(s_lineno);
    bp->class = NONTERM;
    if (!bp->index) bp->index = nrules;
    if (nrules >= maxrules)
	expand_rules();
    plhs[nrules] = bp;
    rprec[nrules] = UNDEFINED;
    rassoc[nrules] = TOKEN;
}

void end_rule()
{
    register int i;

    if (!last_was_action && plhs[nrules]->tag) {
	for (i = nitems - 1; pitem[i]; --i) continue;
	if (pitem[i+1] == 0 || pitem[i+1]->tag != plhs[nrules]->tag)
	    default_action_warning(plhs[nrules]->name); }
    if (last_was_action) {
	if (plhs[nrules]->trialaction != UNDEFINED &&
	    plhs[nrules]->trialaction != trialaction)
	{
	    inconsistent_trial_action_warning(plhs[nrules]->name);
	    plhs[nrules]->trialaction = 1;
	} else
	    plhs[nrules]->trialaction = trialaction;
    }
    last_was_action = 0;
    if (nitems >= maxitems) expand_items();
    pitem[nitems] = 0;
    ++nitems;
    ++nrules;
}

void insert_empty_rule()
{
    register bucket *bp, **bpp;

    assert(cache);
    sprintf(cache, "$$%d", ++gensym);
    bp = make_bucket(cache);
    last_symbol->next = bp;
    last_symbol = bp;
    bp->tag = plhs[nrules]->tag;
    bp->class = ACTION;
    bp->args = 0;
    bp->trialaction = trialaction;

    if ((nitems += 2) > maxitems)
	expand_items();
    bpp = pitem + nitems - 1;
    *bpp-- = bp;
    while ((bpp[0] = bpp[-1])) --bpp;

    if (++nrules >= maxrules)
	expand_rules();
    plhs[nrules] = plhs[nrules-1];
    plhs[nrules-1] = bp;
    rprec[nrules] = rprec[nrules-1];
    rprec[nrules-1] = 0;
    rassoc[nrules] = rassoc[nrules-1];
    rassoc[nrules-1] = TOKEN;
}

static char *insert_arg_rule(char *arg, char *tag)
{
int	lineno = rescan_lineno;
char	*code = compile_arg(&arg, tag);
int	rule = lookup_arg_cache(code);
FILE	*f = action_file;

    if (rule<0) {
	rule = nrules;
	insert_arg_cache(code, rule);
	trialaction = 1;  // arg rules always run in trial mode
	fprintf(f, "case %d:\n", rule - 2);
	if (!lflag)
	    fprintf(f, line_format, lineno, input_file->name);
	fprintf(f, "%s;\n", code);
	fprintf(f, "break;\n");
	insert_empty_rule();
	plhs[rule]->tag = cache_tag(tag, strlen(tag));
	plhs[rule]->class = ARGUMENT; }
    else {
	if (++nitems > maxitems)
	    expand_items();
	pitem[nitems-1] = plhs[rule];
	free(code); }
    return arg+1;
}

void add_symbol()
{
    register int c;
    register bucket *bp;
    int s_lineno = input_file->lineno;
    char *args = 0;
    int argslen = 0;

    c = *cptr;
    if (c == '\'' || c == '"')
	bp = get_literal();
    else
	bp = get_name();

    c = nextc();
    if (c == '(') {
	++cptr;
	args = copy_args(&argslen);
	if (args == 0) no_space();
	c = nextc(); }
    if (c == ':') {
	end_rule();
	start_rule(bp, s_lineno);
	parse_arginfo(bp, args, argslen);
	++cptr;
	return; }

    if (last_was_action)
	insert_empty_rule();
    last_was_action = 0;

    if (bp->args < 0)
	bp->args = argslen;
    if (argslen == 0 && bp->args > 0 && pitem[nitems-1] == 0) {
	int	i;
	if (plhs[nrules]->args != bp->args)
	    error(input_file->lineno, line, cptr, "Wrong number of default arguments "
		  "for %s", bp->name);
	for (i=bp->args-1; i>=0; i--)
	    if (plhs[nrules]->argtags[i] != bp->argtags[i])
		error(input_file->lineno, line, cptr, "Wrong type for default argument "
		      "%d to %s", i+1, bp->name); }
    else if (bp->args != argslen)
	error(input_file->lineno, line, cptr, "wrong number of arguments for %s",
				  bp->name);
    if (args != 0) {
	int	i;
	char	*ap = args;
	int	elide_cnt = can_elide_arg(&ap, bp->argtags[0]);

	if (elide_cnt > argslen)
	  elide_cnt = 0;
	if (elide_cnt) {
	  for (i=1; i<elide_cnt; i++)
	    if (can_elide_arg(&ap, bp->argtags[i]) != elide_cnt-i) {
	      elide_cnt = 0;
	      break; } }
	if (elide_cnt) {
	  assert(i == elide_cnt);
	} else {
	  ap = args;
	  i = 0; }
	for (; i<argslen; i++)
	    ap = insert_arg_rule(ap, bp->argtags[i]);
	free(args); }
    if (++nitems > maxitems)
	expand_items();
    pitem[nitems-1] = bp;
}

void copy_action()
{
    register int c;
    register int i, j, n;
    int depth;
    int haveyyval = 0;
    char *tag;
    register FILE *f = action_file;
    int a_lineno = input_file->lineno;
    char *a_line = dup_line();
    char *a_cptr = a_line + (cptr - line);
    Yshort *offsets=0, maxoffset;
    bucket **rhs;

    if (last_was_action)
	insert_empty_rule();
    last_was_action = 1;
    trialaction = (*cptr == '[');

    fprintf(f, "case %d:\n", nrules - 2);
    if (!trialaction)
	fprintf(f, "  if (!yytrial)\n");
    if (!lflag)
	fprintf(f, line_format, input_file->lineno, input_file->name);
    if (*cptr == '=') ++cptr;

    /* FIXME -- the argument offset table is computed independently in
     * FIXME -- several places (compile_arg, copy_action, and can_elide_arg)
     * FIXME -- those multiple implementations should be factored into
     * FIXME -- a single function. */
    maxoffset = n = 0;
    for (i = nitems - 1; pitem[i]; --i) {
	n++;
	if (pitem[i]->class != ARGUMENT)
	    maxoffset++; }
    if (maxoffset > 0) {
	offsets = NEW2(maxoffset+1, Yshort);
	if (offsets == 0) no_space(); }
    for (j=0, i++; i<nitems; i++)
	if (pitem[i]->class != ARGUMENT)
	    offsets[++j] = i - nitems + 1;
    rhs = pitem + nitems - 1;

    depth = 0;
loop:
    c = *cptr;
    if (c == '$') {
	if (cptr[1] == '<') {
	    int d_lineno = input_file->lineno;
	    char *d_line = dup_line();
	    char *d_cptr = d_line + (cptr - line);

	    ++cptr;
	    tag = get_tag(1)->name;
	    c = *cptr;
	    if (c == '$') {
		fprintf(f, "yyval.%s", tag);
		++cptr;
		FREE(d_line);
		goto loop; }
	    else if (isdigit(c)) {
		i = get_number();
		if (i > maxoffset) {
		    dollar_warning(d_lineno, i);
		    fprintf(f, "yyvsp[%d].%s", i - maxoffset, tag); }
		else
		    fprintf(f, "yyvsp[%d].%s", offsets[i], tag);
		FREE(d_line);
		goto loop; }
	    else if (c == '-' && isdigit(cptr[1])) {
		++cptr;
		i = -get_number() - n;
		fprintf(f, "yyvsp[%d].%s", i, tag);
		FREE(d_line);
		goto loop; }
	    else if (isalpha(c) || c == '_') {
		char *arg = get_tag(0)->name;
		for (i=plhs[nrules]->args-1; i>=0; i--)
		    if (arg == plhs[nrules]->argnames[i]) break;
		if (i<0)
		    error(d_lineno,d_line,d_cptr,"unknown argument %s",arg);
		fprintf(f, "yyvsp[%d].%s", i-plhs[nrules]->args+1-n, tag);
		FREE(d_line);
		goto loop; }
	    else
		dollar_error(d_lineno, d_line, d_cptr); }
	else if (cptr[1] == '$') {
	    if (havetags) {
		tag = plhs[nrules]->tag->name;
		if (tag == 0) untyped_lhs();
		fprintf(f, "yyval.%s", tag); }
	    else
		fprintf(f, "yyval");
	    cptr += 2;
	    haveyyval = 1;
	    goto loop; }
	else if (isdigit(cptr[1])) {
	    ++cptr;
	    i = get_number();
	    if (havetags) {
		if (i <= 0 || i > maxoffset)
		    unknown_rhs(i);
		tag = rhs[offsets[i]]->tag->name;
		if (tag == 0)
		    untyped_rhs(i, rhs[offsets[i]]->name);
		fprintf(f, "yyvsp[%d].%s", offsets[i], tag); }
	    else {
		if (i > n) {
		    dollar_warning(input_file->lineno, i);
		    fprintf(f, "yyvsp[%d]", i - maxoffset); }
		else
		    fprintf(f, "yyvsp[%d]", offsets[i]); }
	    goto loop; }
	else if (cptr[1] == '-') {
	    cptr += 2;
	    i = get_number();
	    if (havetags)
		unknown_rhs(-i);
	    fprintf(f, "yyvsp[%d]", -i - n);
	    goto loop; }
	else if (isalpha(cptr[1]) || cptr[1] == '_') {
	    char *arg;
	    ++cptr;
	    arg = get_tag(0)->name;
	    for (i=plhs[nrules]->args-1; i>=0; i--)
		if (arg == plhs[nrules]->argnames[i]) break;
	    if (i<0)
		error(input_file->lineno, line, cptr, "unknown argument %s", arg);
	    tag = plhs[nrules]->argtags[i];
	    fprintf(f, "yyvsp[%d]", i - plhs[nrules]->args + 1 - n);
	    if (tag) fprintf(f, ".%s", tag);
	    else if (havetags)
		error(input_file->lineno, 0, 0, "untyped argument $%s", arg);
	    goto loop; }
    } else if (c == '@') {
	if (cptr[1] == '@' || cptr[1] == '$') {
	    fprintf(f, "yypos");
	    cptr += 2;
	    goto loop; }
	else if (isdigit(cptr[1])) {
	    ++cptr;
	    i = get_number();
	    if (i > n) {
		at_warning(input_file->lineno, i);
		fprintf(f, "yypsp[%d]", i - maxoffset); }
	    else
		fprintf(f, "yypsp[%d]", offsets[i]);
	    goto loop; }
	else if (cptr[1] == '-') {
	    cptr += 2;
	    i = get_number();
	    fprintf(f, "yypsp[%d]", -i - n);
	    goto loop; } }
    if (isalpha(c) || c == '_' || c == '$') {
	do {
	    putc(c, f);
	    c = *++cptr;
	} while (isalnum(c) || c == '_' || c == '$');
	goto loop; }
    ++cptr;
    if (trialaction && c == '[' && depth == 0) {
	++depth;
	putc('{', f);
	goto loop; }
    if (trialaction && c == ']' && depth == 1) {
	--depth;
	putc('}', f);
	c = nextc();
	if (c == '[' && !haveyyval) {
	    goto loop; }
	else if (c == '{' && !haveyyval) {
	    fprintf(f, "\n");
	    if (!lflag) fprintf(f, "#\n");
	    fprintf(f, "  if (!yytrial)\n");
	    if (!lflag)
		fprintf(f, line_format, input_file->lineno, input_file->name);
	    trialaction = 0;
	    goto loop; }
	else {
	    fprintf(f, "\n");
	    if (!lflag) fprintf(f, "#\n");
	    fprintf(f, "break;\n");
	    FREE(a_line);
	    if (maxoffset > 0) FREE(offsets);
	    return; } }
    putc(c, f);
    switch (c) {
    case '\n':
	get_line();
	if (line) goto loop;
	unterminated_action(a_lineno, a_line, a_cptr);
    case ';':
	if (depth > 0) goto loop;
	fprintf(f, "\n");
	if (!lflag) fprintf(f, "#\n");
	fprintf(f, "break;\n");
	FREE(a_line);
	if (maxoffset > 0) FREE(offsets);
	return;
    case '[':
	++depth;
	goto loop;
    case ']':
	--depth;
	goto loop;
    case '{':
	++depth;
	goto loop;
    case '}':
	if (--depth > 0) goto loop;
	c = nextc();
	if (c == '[' && !haveyyval) {
	    trialaction = 1;
	    goto loop; }
	else if (c == '{' && !haveyyval) {
	    fprintf(f, "\n");
	    if (!lflag) fprintf(f, "#\n");
	    fprintf(f, "  if (!yytrial)\n");
	    if (!lflag)
		fprintf(f, line_format, input_file->lineno, input_file->name);
	    goto loop; }
	else {
	    fprintf(f, "\n");
	    if (!lflag) fprintf(f, "#\n");
	    fprintf(f, "break;\n");
	    FREE(a_line);
	    if (maxoffset > 0) FREE(offsets);
	    return; }
    case '\'':
    case '"':
	copy_string(c, f, 0);
	goto loop;
    case '/':
	copy_comment(f, 0);
	goto loop;
    default:
	goto loop; }
}

int mark_symbol()
{
    register int c;
    register bucket *bp;

    c = cptr[1];
    if (c == '%' || c == '\\') {
	cptr += 2;
	return (1); }

    if (c == '=')
	cptr += 2;
    else if ((c == 'p' || c == 'P') &&
	     ((c = cptr[2]) == 'r' || c == 'R') &&
	     ((c = cptr[3]) == 'e' || c == 'E') &&
	     ((c = cptr[4]) == 'c' || c == 'C') &&
	     ((c = cptr[5], !IS_IDENT(c))))
	cptr += 5;
    else
	syntax_error(input_file->lineno, line, cptr);

    c = nextc();
    if (isalpha(c) || c == '_' || c == '.' || c == '$')
	bp = get_name();
    else if (c == '\'' || c == '"')
	bp = get_literal();
    else {
	syntax_error(input_file->lineno, line, cptr);
	/*NOTREACHED*/
	return 0;}

    if (rprec[nrules] != UNDEFINED && bp->prec != rprec[nrules])
	prec_redeclared();

    rprec[nrules] = bp->prec;
    rassoc[nrules] = bp->assoc;
    return (0);
}

void read_grammar()
{
    register int c;

    initialize_grammar();
    advance_to_start();

    for (;;) {
	c = nextc();
	if (c == EOF) break;
	if (isalpha(c) || c == '_' || c == '.' || c == '$' || c == '\'' ||
		c == '"')
	    add_symbol();
	else if (c == '{' || c == '=' || c == '[')
	    copy_action();
	else if (c == '|') {
	    end_rule();
	    start_rule(plhs[nrules-1], 0);
	    ++cptr; }
	else if (c == '%') {
	    if (mark_symbol()) break; }
	else
	    syntax_error(input_file->lineno, line, cptr); }
    end_rule();
    if (goal->args > 0)
	error(0, 0, 0, "start symbol %s requires arguments", goal->name);
}

void free_tags()
{
union_tag	*p, *next;

    for (p = tag_table; p; p = next) {
	next = p->next;
	FREE(p->name);
	FREE(p); }
    tag_table = 0;
}

void pack_names()
{
    register bucket *bp;
    register char *p, *s, *t;

    name_pool_size = 13;  /* 13 == sizeof("$end") + sizeof("$accept") */
    for (bp = first_symbol; bp; bp = bp->next)
	name_pool_size += strlen(bp->name) + 1;
    name_pool = MALLOC(name_pool_size);
    if (name_pool == 0) no_space();

    strcpy(name_pool, "$accept");
    strcpy(name_pool+8, "$end");
    t = name_pool + 13;
    for (bp = first_symbol; bp; bp = bp->next) {
	p = t;
	s = bp->name;
	while ((*t++ = *s++)) continue;
	FREE(bp->name);
	bp->name = p; }
}

void check_symbols()
{
    register bucket *bp;

    if (goal->class == UNKNOWN)
	undefined_goal(goal->name);

    for (bp = first_symbol; bp; bp = bp->next) {
	if (bp->class == UNKNOWN) {
	    undefined_symbol_warning(bp->name);
	    bp->class = TERM; } }
}

void pack_symbols()
{
    register bucket *bp;
    register bucket **v;
    register int i, j, k, n;

    nsyms = 2;
    ntokens = 1;
    for (bp = first_symbol; bp; bp = bp->next) {
	++nsyms;
	if (bp->class == TERM) ++ntokens; }
    start_symbol = ntokens;
    nvars = nsyms - ntokens;

    symbol_name = NEW2(nsyms, char *);
    if (symbol_name == 0) no_space();
    symbol_value = NEW2(nsyms, Yshort);
    if (symbol_value == 0) no_space();
    symbol_prec = NEW2(nsyms, Yshort);
    if (symbol_prec == 0) no_space();
    symbol_assoc = MALLOC(nsyms);
    if (symbol_assoc == 0) no_space();

    v = NEW2(nsyms, bucket *);
    if (v == 0) no_space();

    v[0] = 0;
    v[start_symbol] = 0;

    i = 1;
    j = start_symbol + 1;
    for (bp = first_symbol; bp; bp = bp->next)
    {
	if (bp->class == TERM)
	    v[i++] = bp;
	else
	    v[j++] = bp;
    }
    assert(i == ntokens && j == nsyms);

    for (i = 1; i < ntokens; ++i)
	v[i]->index = i;

    goal->index = start_symbol + 1;
    k = start_symbol + 2;
    while (++i < nsyms)
	if (v[i] != goal) {
	    v[i]->index = k;
	    ++k; }
    goal->value = 0;
    k = 1;
    for (i = start_symbol + 1; i < nsyms; ++i) {
	if (v[i] != goal) {
	    v[i]->value = k;
	    ++k; } }
    k = 0;
    for (i = 1; i < ntokens; ++i) {
	n = v[i]->value;
	if (n > 256) {
	    for (j = k++; j > 0 && symbol_value[j-1] > n; --j)
		symbol_value[j] = symbol_value[j-1];
	    symbol_value[j] = n; } }
    if (v[1]->value == UNDEFINED)
	v[1]->value = 256;
    j = 0;
    n = 257;
    for (i = 2; i < ntokens; ++i) {
	if (v[i]->value == UNDEFINED) {
	    while (j < k && n == symbol_value[j]) {
		while (++j < k && n == symbol_value[j]) continue;
		++n; }
	    v[i]->value = n;
	    ++n; } }
    symbol_name[0] = name_pool + 8;
    symbol_value[0] = 0;
    symbol_prec[0] = 0;
    symbol_assoc[0] = TOKEN;
    for (i = 1; i < ntokens; ++i) {
	symbol_name[i] = v[i]->name;
	symbol_value[i] = v[i]->value;
	symbol_prec[i] = v[i]->prec;
	symbol_assoc[i] = v[i]->assoc; }
    symbol_name[start_symbol] = name_pool;
    symbol_value[start_symbol] = -1;
    symbol_prec[start_symbol] = 0;
    symbol_assoc[start_symbol] = TOKEN;
    for (++i; i < nsyms; ++i) {
	k = v[i]->index;
	symbol_name[k] = v[i]->name;
	symbol_value[k] = v[i]->value;
	symbol_prec[k] = v[i]->prec;
	symbol_assoc[k] = v[i]->assoc; }
    FREE(v);
}

void pack_grammar()
{
    register int i, j;
    int assoc, prec;

    ritem = NEW2(nitems, Yshort);
    if (ritem == 0) no_space();
    rlhs = NEW2(nrules, Yshort);
    if (rlhs == 0) no_space();
    rrhs = NEW2(nrules+1, Yshort);
    if (rrhs == 0) no_space();
    rprec = RENEW(rprec, nrules, Yshort);
    if (rprec == 0) no_space();
    rassoc = RENEW(rassoc, nrules, char);
    if (rassoc == 0) no_space();

    ritem[0] = -1;
    ritem[1] = goal->index;
    ritem[2] = 0;
    ritem[3] = -2;
    rlhs[0] = 0;
    rlhs[1] = 0;
    rlhs[2] = start_symbol;
    rrhs[0] = 0;
    rrhs[1] = 0;
    rrhs[2] = 1;

    j = 4;
    for (i = 3; i < nrules; ++i) {
	if (plhs[i]->args > 0) {
	  if (plhs[i]->argnames) {
	    FREE(plhs[i]->argnames);
	    plhs[i]->argnames = 0;
	  }
	  if (plhs[i]->argtags) {
	    FREE(plhs[i]->argtags);
	    plhs[i]->argtags = 0;
	  }
	}
	rlhs[i] = plhs[i]->index;
	rrhs[i] = j;
	assoc = TOKEN;
	prec = 0;
	while (pitem[j]) {
	    ritem[j] = pitem[j]->index;
	    if (pitem[j]->class == TERM) {
		prec = pitem[j]->prec;
		assoc = pitem[j]->assoc; }
	    ++j; }
	ritem[j] = -i;
	++j;
	if (rprec[i] == UNDEFINED) {
	    rprec[i] = prec;
	    rassoc[i] = assoc; } }
    rrhs[i] = j;
    FREE(plhs);
    FREE(pitem);
    clean_arg_cache();
}

void print_grammar()
{
    register int i, j, k;
    int spacing = 0;
    register FILE *f = verbose_file;

    if (!vflag) return;

    k = 1;
    for (i = 2; i < nrules; ++i) {
	if (rlhs[i] != rlhs[i-1]) {
	    if (i != 2) fprintf(f, "\n");
	    fprintf(f, "%4d  %s :", i - 2, symbol_name[rlhs[i]]);
	    spacing = strlen(symbol_name[rlhs[i]]) + 1; }
	else {
	    fprintf(f, "%4d  ", i - 2);
	    j = spacing;
	    while (--j >= 0) putc(' ', f);
	    putc('|', f); }
	while (ritem[k] >= 0) {
	    fprintf(f, " %s", symbol_name[ritem[k]]);
	    ++k; }
	++k;
	putc('\n', f); }
}

extern int read_errs;

void reader() {
  write_section("banner");
  if (dflag)
    fprintf(text_file, "#include \"%s\"\n\n", defines_file_name);
  create_symbol_table();
  read_declarations();
  read_grammar();
  if(read_errs) done(1);
  free_symbol_table();
  pack_names();
  check_symbols();
  pack_symbols();
  gen_yydestruct();
  free_destructors();
  free_tags();
  pack_grammar();
  free_symbols();
  print_grammar();
}
