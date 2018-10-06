/*
 * [test] btyacc
 * [test] cc -pedantic -Wall -Werror
 */
%%
S: error
%%
int main() { int rv = yyparse(); printf("yyparse() = %d\n", rv); return rv; }
int yylex() { return-1; }
void yyerror(const char *s, ...) { printf("%s\n",s); }
