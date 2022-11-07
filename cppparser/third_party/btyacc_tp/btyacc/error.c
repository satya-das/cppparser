/*
 * routines for printing error messages
 */

#include "defs.h"
#include <stdarg.h>

extern FILE *inc_file;
extern char inc_file_name[];
void FileError(char *fmt, ...);

/*
 * VM: print error message with file coordinates.
 * Do it in style acceptable to emacs.
 */
void FileError(char *fmt, ...) {
  va_list args;

  fprintf(stderr, "%s:%d: ", input_file->name, input_file->lineno);
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
}

void fatal(char *msg)
{
    fprintf(stderr, "fatal - %s\n", msg);
    done(2);
}


void no_space()
{
    fprintf(stderr, "fatal - out of space\n");
    done(2);
}


void open_error(char *filename)
{
    fprintf(stderr, "fatal - cannot open \"%s\"\n", filename);
    done(2);
}


void unexpected_EOF()
{
  FileError("unexpected end-of-file");
  done(1);
}


void print_pos(char *st_line, char *st_cptr)
{
    register char *s;

    if (st_line == 0) return;
    for (s = st_line; *s != '\n'; ++s)
    {
	if (isprint(*s) || *s == '\t')
	    putc(*s, stderr);
	else
	    putc('?', stderr);
    }
    putc('\n', stderr);
    for (s = st_line; s < st_cptr; ++s)
    {
	if (*s == '\t')
	    putc('\t', stderr);
	else
	    putc(' ', stderr);
    }
    putc('^', stderr);
    putc('\n', stderr);
}

int read_errs = 0;

void error(int lineno, char *line, char *cptr, char *msg, ...)
{
  char sbuf[512];
  va_list args;

  va_start(args, msg);
  vsprintf(sbuf, msg, args);
  va_end(args);
  FileError("%s", sbuf);
  read_errs++;
}

void syntax_error(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "syntax error");
  exit(1);
}

void unterminated_comment(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "unmatched /*");
  exit(1);
}

void unterminated_string(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "unterminated string");
  exit(1);
}

void unterminated_text(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "unmatched %%{");
  exit(1);
}

void unterminated_union(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "unterminated %%union");
  exit(1);
}

void over_unionized(char *cptr) {
  error(input_file->lineno, line, cptr, "too many %%union declarations");
  exit(1);
}

void repeat_location_defined(char *cptr) {
  error(input_file->lineno, line, cptr, "too many %%location declarations");
  exit(1);
}

void illegal_tag(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "illegal tag");
}

void illegal_character(char *cptr) {
  error(input_file->lineno, line, cptr, "illegal character");
}

void used_reserved(char *s) {
  error(input_file->lineno, 0, 0, "illegal use of reserved symbol %s", s);
}

void tokenized_start(char *s) {
  error(input_file->lineno, 0, 0, "the start symbol %s cannot be declared to be a token", s);
}

void retyped_warning(char *s) {
  FileError("the type of %s has been redeclared", s);
}


void reprec_warning(char *s) {
  FileError("the precedence of %s has been redeclared", s);
}


void revalued_warning(char *s) {
  FileError("the value of %s has been redeclared", s);
}


void terminal_start(char *s) {
  error(input_file->lineno, 0, 0, "the start symbol %s is a token", s);
}

void restarted_warning() {
  FileError("the start symbol has been redeclared");
}

void no_grammar() {
  error(input_file->lineno, 0, 0, "no grammar has been specified");
}

void terminal_lhs(int lineno) {
  error(lineno, 0, 0, "a token appears on the lhs of a production");
}

void prec_redeclared() {
  error(input_file->lineno, 0, 0, "conflicting %%prec specifiers");
}

void unterminated_action(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "unterminated action");
}

void unterminated_arglist(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "unterminated argument list");
}

void bad_formals() {
  error(input_file->lineno, 0, 0, "bad formal argument list");
}

void dollar_warning(int a_lineno, int i) {
  int slineno = input_file->lineno;
  input_file->lineno = a_lineno;
  FileError("$%d references beyond the end of the current rule", i);
  input_file->lineno = slineno;
}

void dollar_error(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "illegal $-name");
}

void at_warning(int a_lineno, int i) {
  int slineno = input_file->lineno;
  input_file->lineno = a_lineno;
  FileError("@%d references beyond the end of the current rule", i);
  input_file->lineno = slineno;
}

void at_error(int lineno, char *line, char *cptr) {
  error(lineno, line, cptr, "illegal @-name");
}

void untyped_lhs() {
  error(input_file->lineno, 0, 0, "$$ is untyped");
}

void untyped_rhs(int i, char *s) {
  error(input_file->lineno, 0, 0, "$%d (%s) is untyped", i, s);
}

void unknown_rhs(int i) {
  error(input_file->lineno, 0, 0, "$%d is untyped (out of range)", i);
}

void default_action_warning(char *s) {
  FileError("the default action for %s assigns an undefined value to $$", s);
}

void inconsistent_trial_action_warning(char *s) {
  FileError("inconsistent trial actions for %s", s);
}

void undefined_goal(char *s) {
  error(input_file->lineno, 0, 0, "the start symbol %s is undefined", s);
}

void undefined_symbol_warning(char *s) {
  fprintf(stderr, "warning - the symbol %s is undefined\n", s);
}

void unused_destructor_warning(int lineno)
{
  error(lineno, 0, 0, "unused %%destructor");
}
