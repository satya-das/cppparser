#include "defs.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

char dflag;
char lflag;
char rflag;
char tflag;
char vflag;
int Eflag = 0;

char *symbol_prefix = "yy";
char *myname = "yacc";
#if defined(__MSDOS__) || defined(_WIN32)
#define DIR_CHAR '\\'
#define DEFAULT_TMPDIR "."
char *file_prefix = "y";
#else  /* Unix */
#define DIR_CHAR '/'
#define DEFAULT_TMPDIR "/tmp"
char *file_prefix = 0;
#endif
char *temp_form = "yacc_t_XXXXXX";

int outline;

char *action_file_name;
char *code_file_name;
char *defines_file_name;
char include_defines;
char *output_file_name;
char *text_file_name;
char *union_file_name;
char *verbose_file_name;

FILE *action_file;	/*  a temp file, used to save actions associated    */
			/*  with rules until the parser is written	    */
FILE *code_file;	/*  y.code.c (used when the -r option is specified) */
FILE *defines_file;	/*  y.tab.h					    */
FILE *output_file;	/*  y.tab.c					    */
FILE *text_file;	/*  a temp file, used to save text until all	    */
			/*  symbols have been defined			    */
FILE *union_file;	/*  a temp file, used to save the union		    */
			/*  definition until all symbol have been	    */
			/*  defined					    */
FILE *verbose_file;	/*  y.output					    */

int nitems;
int nrules;
int nsyms;
int ntokens;
int nvars;

int   start_symbol;
char  **symbol_name;
Yshort *symbol_value;
Yshort *symbol_prec;
char  *symbol_assoc;

Yshort *ritem;
Yshort *rlhs;
Yshort *rrhs;
Yshort *rprec;
char  *rassoc;
Yshort **derives;
char *nullable;


void done(int k)
{
    if (action_file) { fclose(action_file); unlink(action_file_name); }
    if (text_file) { fclose(text_file); unlink(text_file_name); }
    if (union_file) { fclose(union_file); unlink(union_file_name); }
    exit(k);
}


void onintr(int ignore)
{
    done(1);
}


void set_signals()
{
#ifdef SIGINT
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
	signal(SIGINT, onintr);
#endif
#ifdef SIGTERM
    if (signal(SIGTERM, SIG_IGN) != SIG_IGN)
	signal(SIGTERM, onintr);
#endif
#ifdef SIGHUP
    if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
	signal(SIGHUP, onintr);
#endif
}


void usage()
{
    fprintf(stderr, "usage: %s [-dlrtv] [-b file_prefix] [-S skeleton file] "
		    "[-p symbol_prefix] filename\n", myname);
    exit(1);
}


void getargs(int argc, char **argv)
{
    register int i;
    register char *s;

    if (argc > 0) myname = argv[0];
    for (i = 1; i < argc; ++i)
    {
	s = argv[i];
	if (*s != '-') break;
	switch (*++s)
	{
	case '\0':
	    read_from_file("-");
	    if (i + 1 < argc) usage();
	    return;

	case '-':
	    ++i;
	    goto no_more_options;

	case 'b':
	    if (*++s)
		 file_prefix = s;
	    else if (++i < argc)
		file_prefix = argv[i];
	    else
		usage();
	    continue;

	case 'p':
	    if (*++s)
		 symbol_prefix = s;
	    else if (++i < argc)
		symbol_prefix = argv[i];
	    else
		usage();
	    continue;

	case 'd':
	    dflag = 1;
	    break;

	case 'D':
	    /* Find the preprocessor variable */
	    { char **ps;
	      char *var_name = s + 1;
	      extern char *defd_vars[];
	      for(ps=&defd_vars[0]; *ps; ps++) {
		if(strcmp(*ps,var_name)==0) {
		  error(input_file->lineno, 0, 0,
		        "Preprocessor variable %s already defined", var_name);
		}
	      }
	      *ps = MALLOC(strlen(var_name)+1);
	      strcpy(*ps, var_name);
	      *++ps = NULL;
	    }
	    continue;

	case 'E':
	    Eflag = 1;
	    break;

	case 'l':
	    lflag = 1;
	    break;

	case 'r':
	    rflag = 1;
	    break;

	case 't':
	    tflag = 1;
	    break;

	case 'v':
	    vflag = 1;
	    break;

	case 'y':
	    file_prefix = "y";
	    break;

	case 'S':
	    if (*++s)
		read_skel(s);
	    else if (++i < argc)
		read_skel(argv[i]);
	    else
		usage();
	    continue;

	default:
	    usage();
	}

	for (;;)
	{
	    switch (*++s)
	    {
	    case '\0':
		goto end_of_option;

	    case 'd':
		dflag = 1;
		break;

	    case 'l':
		lflag = 1;
		break;

	    case 'r':
		rflag = 1;
		break;

	    case 't':
		tflag = 1;
		break;

	    case 'v':
		vflag = 1;
		break;

	    case 'y':
		file_prefix = "y";
		break;

	    default:
		usage();
	    }
	}
end_of_option:;
    }

no_more_options:;
    if (i + 1 != argc) usage();
    read_from_file(argv[i]);

    if (!file_prefix) {
      if (input_file && input_file->name) {
	file_prefix = strdup(input_file->name);
	if ((s = strrchr(file_prefix, '.')))
	  *s = 0;
      } else {
	file_prefix = "y";
      }
    }

    /* Replace symbol prefix in the skeleton */
    if (strcmp(symbol_prefix, "yy")) {
      struct section *s;
      char **l, *q, *n, *p;

      for (s = section_list; s->name; s++)
        for (l = s->ptr; *l; l++) {
	  /* Very conservative estimate */
	  p = n = malloc(strlen(*l) * strlen(symbol_prefix));
	  for (q = *l; *q; q++)
	    if (q[0] == 'y' && q[1] == 'y') {
	      strcpy(p, symbol_prefix);
	      p += strlen(symbol_prefix);
	      q++;
	    } else
	      *p++ = *q;
	  *p = 0;
	  *l = realloc(n ,strlen(n) + 1);
        }
    }
}

char *allocate(unsigned n)
{
    register char *p;

    p = NULL;
    if (n)
    {
        /* VM: add a few bytes here, cause
         * Linux calloc does not like sizes like 32768 */
	p = CALLOC(1, n+10);
	if (!p) no_space();
    }
    return (p);
}


void create_file_names()
{
    int i, len;
    char *tmpdir;

    tmpdir = getenv("TMPDIR");
    if (tmpdir == 0) tmpdir = DEFAULT_TMPDIR;

    len = strlen(tmpdir);
    i = len + 13;
    if (len && tmpdir[len-1] != DIR_CHAR)
	++i;

    action_file_name = MALLOC(i);
    if (action_file_name == 0) no_space();
    text_file_name = MALLOC(i);
    if (text_file_name == 0) no_space();
    union_file_name = MALLOC(i);
    if (union_file_name == 0) no_space();

    strcpy(action_file_name, tmpdir);
    strcpy(text_file_name, tmpdir);
    strcpy(union_file_name, tmpdir);

    if (len && tmpdir[len - 1] != DIR_CHAR)
    {
	action_file_name[len] = DIR_CHAR;
	text_file_name[len] = DIR_CHAR;
	union_file_name[len] = DIR_CHAR;
	++len;
    }

    strcpy(action_file_name + len, temp_form);
    strcpy(text_file_name + len, temp_form);
    strcpy(union_file_name + len, temp_form);

    action_file_name[len + 5] = 'a';
    text_file_name[len + 5] = 't';
    union_file_name[len + 5] = 'u';

    if(mktemp(action_file_name)==NULL) {
      fprintf(stderr, "btyacc: Cannot create temporary file\n");
      exit(1);
    }
    if(mktemp(text_file_name)==NULL) {
      fprintf(stderr, "btyacc: Cannot create temporary file\n");
      exit(1);
    }
    if(mktemp(union_file_name)==NULL) {
      fprintf(stderr, "btyacc: Cannot create temporary file\n");
      exit(1);
    }

    len = strlen(file_prefix);

    output_file_name = MALLOC(len + 7);
    if (output_file_name == 0)
	no_space();
    strcpy(output_file_name, file_prefix);
    strcpy(output_file_name + len, OUTPUT_SUFFIX);

    if (rflag)
    {
	code_file_name = MALLOC(len + 8);
	if (code_file_name == 0)
	    no_space();
	strcpy(code_file_name, file_prefix);
	strcpy(code_file_name + len, CODE_SUFFIX);
    }
    else
	code_file_name = output_file_name;

    if (dflag)
    {
	defines_file_name = MALLOC(len + 7);
	if (defines_file_name == 0)
	    no_space();
	strcpy(defines_file_name, file_prefix);
	strcpy(defines_file_name + len, DEFINES_SUFFIX);
    }

    if (vflag)
    {
	verbose_file_name = MALLOC(len + 8);
	if (verbose_file_name == 0)
	    no_space();
	strcpy(verbose_file_name, file_prefix);
	strcpy(verbose_file_name + len, VERBOSE_SUFFIX);
    }
}


void open_files()
{
    create_file_names();

    action_file = fopen(action_file_name, "w");
    if (action_file == 0)
	open_error(action_file_name);

    text_file = fopen(text_file_name, "w");
    if (text_file == 0)
	open_error(text_file_name);

    if (vflag)
    {
	verbose_file = fopen(verbose_file_name, "w");
	if (verbose_file == 0)
	    open_error(verbose_file_name);
    }

    if (dflag)
    {
	defines_file = fopen(defines_file_name, "w");
	if (defines_file == 0)
	    open_error(defines_file_name);
	union_file = fopen(union_file_name, "w");
	if (union_file ==  0)
	    open_error(union_file_name);
    }

    output_file = fopen(output_file_name, "w");
    if (output_file == 0)
	open_error(output_file_name);

    if (rflag)
    {
	code_file = fopen(code_file_name, "w");
	if (code_file == 0)
	    open_error(code_file_name);
    }
    else
	code_file = output_file;
}


int main(int argc, char **argv)
{
    set_signals();
    getargs(argc, argv);
    open_files();
    reader();
    lr0();
    lalr();
    make_parser();
    verbose();
    output();
    done(0);
    return 0;
}
