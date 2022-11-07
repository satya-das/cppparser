#include "defs.h"
#include "mstring.h"

destructor *destructors = 0;
destructor *default_destructor = 0;
static destructor **destructors_tail = &destructors;

void declare_destructor()
{
struct mstring	*code = msnew();
destructor	*dtor;
int             a_lineno = input_file->lineno;
char            *a_line = dup_line();
char            *a_cptr = a_line + (cptr - line - 1);
int		depth = 1, quote = 0, c;

    if (nextc() != '{')
	syntax_error(input_file->lineno, line, cptr);
    if (!lflag)
	msprintf(code, line_format, input_file->lineno, input_file->name);
    mputc(code, *cptr++);
    while (depth > 0) {
	switch(mputc(code, *cptr++)) {
	case '{': if (!quote) depth++; break;
	case '}': if (!quote) depth--; break;
	case '"': case '\'':
	    if (quote) {
		if (quote == cptr[-1]) quote = 0;
	    } else
		quote = cptr[-1];
	    break;
	case '\\':
	    if (quote && *cptr != '\n') mputc(code, *cptr++);
	    break;
	case '\n':
	    if (quote)
		unterminated_string(input_file->lineno, line, cptr);
	    get_line();
	    if (!line)
		unterminated_action(a_lineno, a_line, a_cptr);
	    break;
	default:
	    break; } }
    FREE(a_line);
    if (!(dtor = NEW(destructor)))
	no_space();
    memset(dtor, 0, sizeof(destructor));
    dtor->code = msdone(code);
    dtor->lineno = a_lineno;
    do {
	while (isspace(*cptr)) cptr++;
	if ((c = *cptr) == '<') {
	    cptr++;
	    do {
		if ((c = nextc()) == EOF) unexpected_EOF();
		if (c == '*') {
		    if (default_destructor)
			error(input_file->lineno, line, cptr,
			      "duplicate %%destructor for <*>");
		    else
			default_destructor = dtor;
		    cptr++;
		} else if (isalpha(c) || c == '_' || c == '$') {
		    union_tag *tag = get_tag(0);
		    if (tag->dtor)
			error(input_file->lineno, line, cptr,
			      "duplicate %%destructor for <%s>", tag->name);
		    else
			tag->dtor = dtor;
		} else {
		    syntax_error(input_file->lineno, line, cptr);
		}
		if ((c = nextc()) == EOF) unexpected_EOF();
	    } while (c != '>');
	    cptr++;
	} else if (isalpha(c) || c == '_' || c == '$') {
	    bucket *bp = get_name();
	    if (bp->dtor)
		error(input_file->lineno, line, cptr, "duplicate %%destructor for %s",
		      bp->name);
	    else
		bp->dtor = dtor;
	} else if (*cptr) {
	    syntax_error(input_file->lineno, line, cptr);
	}
    } while (*cptr);
    get_line();
    *destructors_tail = dtor;
    destructors_tail = &dtor->next;
}

void free_destructors(void)
{
    destructor	*dtor, *next;
    int		i;

    for (dtor = destructors; dtor; dtor = next) {
	next = dtor->next;
	for (i = 0; i < dtor->num_tags; i++) {
	    free(dtor->tags[i].syms);
	    free(dtor->tags[i].trialsyms); }
	free(dtor->tags);
	free(dtor); }
    destructors = default_destructor = 0;
    destructors_tail = &destructors;
}


void add_destructor_symbol(destructor *d, int sym, int trial, union_tag *tag)
{
int	i;

    for (i = 0; i < d->num_tags; i++)
	if (d->tags[i].tag == tag)
	    break;
    if (i >= d->max_tags) {
	d->max_tags += 4;
	if (!(d->tags = realloc(d->tags, d->max_tags * sizeof(d->tags[0]))))
	    no_space(); }
    if (i >= d->num_tags) {
	d->tags[i].tag = tag;
	d->tags[i].max_syms = d->tags[i].max_trialsyms = 4;
	if (!(d->tags[i].syms = malloc(4 * sizeof(int)))) no_space();
	if (!(d->tags[i].trialsyms = malloc(4 * sizeof(int)))) no_space();
	d->tags[i].num_syms = d->tags[i].num_trialsyms = 0;
	d->num_tags++; }
    if (trial) {
	if (d->tags[i].num_trialsyms == d->tags[i].max_trialsyms) {
	    d->tags[i].max_trialsyms *= 2;
	    if (!(d->tags[i].trialsyms = realloc(d->tags[i].trialsyms,
		    d->tags[i].max_trialsyms * sizeof(int))))
		no_space(); }
	d->tags[i].trialsyms[d->tags[i].num_trialsyms++] = sym;
    } else {
	if (d->tags[i].num_syms == d->tags[i].max_syms) {
	    d->tags[i].max_syms *= 2;
	    if (!(d->tags[i].syms = realloc(d->tags[i].syms,
		    d->tags[i].max_syms * sizeof(int))))
		no_space(); }
	d->tags[i].syms[d->tags[i].num_syms++] = sym;
    }
}

void gen_yydestruct()
{
    bucket	*bp;
    destructor	*dtor;
    int		i, j, max_symbol_value, *ttable;

    if (!destructors) return;
    fprintf(text_file, "#\n#ifdef YYPOSN\n"
		       "#define YYDESTRUCT(T,S,V,P) yydestruct(T,S,V,P)\n"
		       "#else\n"
		       "#define YYDESTRUCT(T,S,V,P) yydestruct(T,S,V)\n"
		       "#endif\n"
		       "void YYDESTRUCT(int trial, int sym, YYSTYPE *val, "
				       "YYPOSN *pos) {\n"
		       "    switch(sym) {\n");
    for (bp = first_symbol; bp; bp = bp->next) {
	dtor = bp->dtor;
	if (!dtor && bp->tag)
	    dtor = bp->tag->dtor;
	if (!dtor)
	    dtor = default_destructor;
	if (dtor)
	    add_destructor_symbol(dtor, bp->index, bp->trialaction>0, bp->tag);
    }
    for (dtor = destructors; dtor; dtor = dtor->next) {
	for (i = 0; i < dtor->num_tags; i++) {
	    char *p = dtor->code;
	    char *tag = dtor->tags[i].tag ? dtor->tags[i].tag->name : 0;
	    int quote = 0;
	    for (j = 0; j < dtor->tags[i].num_syms; j++) {
		int sym = dtor->tags[i].syms[j];
		fprintf(text_file, "    case %d: /* %s */\n", sym,
			symbol_name[sym]); }
	    if (dtor->tags[i].num_syms)
		fprintf(text_file, "      if (!trial) {\n");
	    else if (!dtor->tags[i].num_trialsyms) {
		unused_destructor_warning(dtor->lineno);
		continue;
	    }
	    for (j = 0; j < dtor->tags[i].num_trialsyms; j++) {
		int sym = dtor->tags[i].trialsyms[j];
		fprintf(text_file, "    case %d: /* %s */\n", sym,
			symbol_name[sym]); }
	    while (*p) {
		switch (*p) {
		case '\"': case '\'':
		    if (quote == *p) quote = 0;
		    else if (!quote) quote = *p;
		    break;
		case '\\':
		    if (quote) putc(*p++, text_file);
		    break;
		case '\n':
		    quote = 0;
		    putc(*p++, text_file);
		    if (*p != '#' && *p != 0 && !isspace(*p))
			putc('\t', text_file);
		    continue;
		case '$':
		    if (p[1] == '$') {
			if (tag)
			    fprintf(text_file, "val->%s", tag);
			else
			    fprintf(text_file, "(*val)");
			p += 2;
			continue; }
		    break;
		case '@':
		    if (p[1] == '@' || p[1] == '$') {
			if (tag)
			    fprintf(text_file, "pos->%s", tag);
			else
			    fprintf(text_file, "(*pos)");
			p += 2;
			continue; }
		    break;
		default:
		    break; }
		putc(*p++, text_file); }
	    if (p[-1] != '\n')
		putc('\n', text_file);
	    fprintf(text_file, "#\n");
	    if (dtor->tags[i].num_syms)
		fprintf(text_file, "      }\n");
	    fprintf(text_file, "      break;\n"); } }
    fprintf(text_file, "    default:\n"
		       "        break;\n");
    fprintf(text_file, "    }\n"
                       "}\n"
		       );
    max_symbol_value = 0;
    for (i = 1; i < ntokens; i++)
	if (symbol_value[i] > max_symbol_value)
	    max_symbol_value = symbol_value[i];
    ttable = malloc((max_symbol_value+1) * sizeof(int));
    memset(ttable, 0, (max_symbol_value+1) * sizeof(int));
    for (i = 1; i < ntokens; i++)
	if (symbol_value[i] >= 0)
	    ttable[symbol_value[i]] = i;
    if (!rflag)
	fprintf(output_file, "static ");
    fprintf(output_file, "int yyttable[] = {");
    for (i = 0; i <= max_symbol_value; i++) {
	if (i%10 == 0) {
	    fprintf(output_file, "\n");
	    if (!rflag) ++outline; }
	fprintf(output_file, "%5d,", ttable[i]); }
    fprintf(output_file, "\n};\n");
    if (!rflag) outline += 2;
    free(ttable);
}
