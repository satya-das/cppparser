/*
 * [test] btyacc -v
 * [test] cc -Wall -Werror -DYYDEBUG
 * [test] input 0xf+09*010
 * [test] match 87
 */
%left LO '+' '-'
%left HI '*' '/' '%'
%nonassoc UNARY

%union {
    long val;
    long (*binop)(long, long);
    long (*unop)(long);
}

%type<binop> op1 op2
%type<unop> unary
%type<val> expr number(<val>) digit(<val>)

%%

input: /*empty*/
    | input expr '\n' [ YYVALID;] { printf("%ld\n", $2); }
    | '\n'
    | error '\n'
    ;

expr: expr op1 expr %prec LO { $$ = $2($1, $3); }
    | expr op2 expr %prec HI { $$ = $2($1, $3); } 
    | unary expr %prec UNARY { $$ = $1($2); }
    | '(' expr ')' { $$ = $2; }
    | '0' number(8) { $$ = $2; }
    | '0' 'x' number(16) { $$ = $3; }
    | '0' 'X' number(16) { $$ = $3; }
    | number(10) { $$ = $1; }

number($base): digit($base) { $$ = $1; }
    | number($base) digit($base) { $$ = $1*$base + $2; }
    ;

digit($base):
      '0' { $$ = 0; }
    | '1' { $$ = 1; }
    | '2' [ if ($base<=2) YYERROR; ] { $$ = 2; }
    | '3' [ if ($base<=3) YYERROR; ] { $$ = 3; }
    | '4' [ if ($base<=4) YYERROR; ] { $$ = 4; }
    | '5' [ if ($base<=5) YYERROR; ] { $$ = 5; }
    | '6' [ if ($base<=6) YYERROR; ] { $$ = 6; }
    | '7' [ if ($base<=7) YYERROR; ] { $$ = 7; }
    | '8' [ if ($base<=8) YYERROR; ] { $$ = 8; }
    | '9' [ if ($base<=9) YYERROR; ] { $$ = 9; }
    | 'a' [ if ($base<=10) YYERROR; ] { $$ = 10; }
    | 'b' [ if ($base<=11) YYERROR; ] { $$ = 11; }
    | 'c' [ if ($base<=12) YYERROR; ] { $$ = 12; }
    | 'd' [ if ($base<=13) YYERROR; ] { $$ = 13; }
    | 'e' [ if ($base<=14) YYERROR; ] { $$ = 14; }
    | 'f' [ if ($base<=15) YYERROR; ] { $$ = 15; }
    | 'A' [ if ($base<=10) YYERROR; ] { $$ = 10; }
    | 'B' [ if ($base<=11) YYERROR; ] { $$ = 11; }
    | 'C' [ if ($base<=12) YYERROR; ] { $$ = 12; }
    | 'D' [ if ($base<=13) YYERROR; ] { $$ = 13; }
    | 'E' [ if ($base<=14) YYERROR; ] { $$ = 14; }
    | 'F' [ if ($base<=15) YYERROR; ] { $$ = 15; }
    ;

op1 : '+' { $$ = add; }
    | '-' { $$ = sub; }
    ;

op2 : '*' { $$ = mul; }
    | '/' { $$ = divide; }
    ;

unary : '+' { $$ = pos; }
    | '-'   { $$ = neg; }
    ;

%%
#include <stdio.h>
#include <ctype.h>

int main() {
  return yyparse();
}

int yylex() {
    int ch;
    do { ch = getchar(); } while (ch != '\n' && isspace(ch));
    return ch;
}

void yyerror(const char *s, ...) {
  printf("%s\n",s);
}

long add(long a, long b) { return a+b; }
long sub(long a, long b) { return a-b; }
long mul(long a, long b) { return a*b; }
long divide(long a, long b) { return a/b; }
long pos(long a) { return a; }
long neg(long a) { return -a; }
