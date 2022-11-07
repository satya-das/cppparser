%union {
    struct Scope	*scope;
    struct Expr		*expr;
    struct Expr_List	*elist;
    struct Type		*type;
    struct Decl		*decl;
    struct Decl_List	*dlist;
    struct Code		*code;
    const char		*id;
}

%location {
    struct {
	int	line, column;
    }		start, end;
}
/*
 * [test] btyacc
 * [test] cc -c -Wall -Werror
 * [test] btyacc -d
 * [test] cc -c -Wall -Werror
 * [test] btyacc -r
 * [test] cc -c -Wall -Werror t2.code.c
 * [test] btyacc -rd
 * [test] cc -c -Wall -Werror t2.code.c
 */

%{
    struct Decl {
	struct Scope	*scope;
	struct Type	*type;
	int		istype;
    };
    extern struct Scope *global_scope;
    enum { ADD, SUB, MUL, MOD, DIV, REF };

    struct Decl_List *append_dlist(struct Decl_List *, struct Decl *);
    struct Type *bare_const(void);
    struct Type *bare_extern(void);
    struct Type *bare_register(void);
    struct Type *bare_static(void);
    struct Type *bare_volatile(void);
    struct Decl_List *build_dlist(struct Decl *);
    struct Code *build_expr_code(struct Expr *);
    struct Expr *build_expr(struct Expr *, int, struct Expr *);
    struct Decl *build_function(struct Decl *, struct Decl_List *, struct Type *);
    struct Code *build_if(struct Expr *, struct Code *, struct Code *);
    struct Code *code_append(struct Code *, struct Code *);
    struct Decl *declare(struct Scope *, const char *, struct Type *);
    struct Decl *finish_fn_def(struct Decl *, struct Code *);
    struct Decl *lookup(struct Scope *, const char *);
    struct Decl *make_array(struct Decl *, struct Expr *);
    struct Decl *make_pointer(struct Decl *, struct Type *);
    struct Scope *new_scope(struct Scope *);
    struct Scope *start_fn_def(struct Scope *, struct Decl *);
    struct Type *type_combine(struct Type *, struct Type *);
    struct Expr *var_expr(struct Scope *, const char *);
    void free_expr(struct Expr *);
%}

%left '+' '-'
%left '*' '/' '%'
%nonassoc PREFIX
%nonassoc POSTFIX '(' '[' '.'

%token <id>	ID
%token <expr>	CONSTANT
%token		EXTERN REGISTER STATIC CONST VOLATILE IF THEN ELSE CLCL

%type <expr>	expr(<scope>)
%type		decl(<scope>) declarator_list(<scope>, <type>)
		decl_list(<scope>)
%type <code>	statement(<scope>) statement_list(<scope>)
		block_statement(<scope>)
%type <decl>	declarator(<scope>, <type>) formal_arg(<scope>)
%type <type>	decl_specs(<scope>) decl_spec(<scope>) typename(<scope>)
		cv_quals cv_qual
%type <scope>	opt_scope(<scope>)
%type <dlist>	formal_arg_list(<scope>) nonempty_formal_arg_list(<scope>)

%destructor { free_expr($$); } <expr>
%destructor { free($$); } <elist,dlist> CONSTANT

%start input

%%

opt_scope($e):		  [ $$ = $e; ]
  | CLCL		  [ $$ = global_scope; ]
  | opt_scope($e) ID CLCL [ struct Decl *d = lookup($1, $2);
			    if (!d || !d->scope) YYERROR;
			    $$ = d->scope; ]
  ;

typename($e /* comment*/): opt_scope($e) ID
      [ struct Decl *d = lookup($1, $2);
	if (!d || !d->istype) YYERROR;
	$$ = d->type;
	@@ = @2; ]
  ;

input: decl_list(global_scope = new_scope(0)) ;
decl_list($e): | decl_list decl($e) ;
decl($e):
    decl_specs($e) declarator_list($e,$1) ';' [YYVALID;]
      { @@.start = @1.start; @@.end = @3.end; }
  | decl_specs($e) declarator($e,$1) block_statement(start_fn_def($e, $2))
      { finish_fn_def($2, $3);
	@@.start = @1.start; @@.end = @3.end; }
  ;

decl_specs($e):	
    decl_spec($e /*comment*/)	{ @@ = @1; } [ $$ = $1; ]
  | decl_specs
    (
    $e
    )
    decl_spec($e)
	{ @@.start = @1.start; @@.end = @2.end; }
	[ $$ = type_combine($1, $2); ]
  ;

cv_quals:			[ $$ = 0; ]
  | cv_quals cv_qual		[ $$ = type_combine($1, $2); ]
  ;

decl_spec($e):
    cv_qual		{ @@ = @1; } [ $$ = $1; ]
  | typename($e)	{ @@ = @1; } [ $$ = $1; ]
  | EXTERN		{ @@ = @1; } [ $$ = bare_extern(); ]
  | REGISTER		{ @@ = @1; } [ $$ = bare_register(); ]
  | STATIC		{ @@ = @1; } [ $$ = bare_static(); ]
  ;

cv_qual:
    CONST		{ @@ = @1; } [ $$ = bare_const(); ]
  | VOLATILE		{ @@ = @1; } [ $$ = bare_volatile(); ]
  ;

declarator_list($e, $t):
    declarator_list($e, $t) ',' declarator($e, $t)
	{ @@.start = @1.start; @@.end = @3.end; }
  | declarator($e, $t)
	{ @@ = @1; }
  ;

declarator($e, $t):
    /* empty */			[ if (!$t) YYERROR; ]	
				{ $$ = declare($e, 0, $t); }
  | opt_scope($e) ID		{ $$ = declare($1, $2, $t); @@ = @1; }
  | '(' declarator($e, $t) ')'
	  { $$ = $2;
	    @@.start = @1.start; @@.end = @3.end; }
  | '*' cv_quals declarator($e, $t) %prec PREFIX
	  { $$ = make_pointer($3, $2);
	    @@.start = @1.start; @@.end = @3.end; }
  | declarator($e, $t) '[' expr($e) ']'
	  { $$ = make_array($1, $3);
	    @@.start = @1.start.line ? @1.start : @2.start;
	    @@.end = @4.end; }
  | declarator($e, $t) '(' formal_arg_list($e) ')' cv_quals
	  { $$ = build_function($1, $3, $5);
	    @@.start = @1.start.line ? @1.start : @2.start;
	    @@.end = @4.end; }
  ;

formal_arg_list($e):		 { $$ = 0; }
  | nonempty_formal_arg_list($e) { $$ = $1; @@ = @1; }
  ;
nonempty_formal_arg_list($e):
    nonempty_formal_arg_list($e) ',' formal_arg($e)
	  { $$ = append_dlist($1, $3);
	    @@.start = @1.start; @@.end = @3.end; }
  | formal_arg($e)
          { $$ = build_dlist($1);
	    @@ = @1; }
  ;
formal_arg($e):
    decl_specs($e) declarator($e,$1)
	  { $$ = $2;
	    @@.start = @1.start.line ? @1.start : @2.start;
	    @@.end = @2.end; }
  ;

expr($e):
    expr($e) '+' expr($e)	{ $$ = build_expr($1, ADD, $3);
				  @@.start = @1.start; @@.end = @3.end; }
  | expr($e) '-' expr($e)	{ $$ = build_expr($1, SUB, $3);
				  @@.start = @1.start; @@.end = @3.end; }
  | expr($e) '*' expr($e)	{ $$ = build_expr($1, MUL, $3);
				  @@.start = @1.start; @@.end = @3.end; }
  | expr($e) '%' expr($e)	{ $$ = build_expr($1, MOD, $3);
				  @@.start = @1.start; @@.end = @3.end; }
  | expr($e) '/' expr($e)	{ $$ = build_expr($1, DIV, $3);
				  @@.start = @1.start; @@.end = @3.end; }
  | '*' expr($e) %prec PREFIX	{ $$ = build_expr(0, REF, $2);
				  @@.start = @1.start; @@.end = @2.end; }
  | opt_scope($e) ID		{ $$ = var_expr($1, $2); @@ = @2; }
  | CONSTANT			{ $$ = $1; @@ = @1; }
  ;

statement($e):
    decl($e)			{ $$ = 0; @@ = @1; }
  | expr($e) ';' [YYVALID;]	{ $$ = build_expr_code($1);
				  @@.start = @1.start; @@.end = @2.end; }
  | IF '(' expr($e) ')' THEN statement($e) ELSE statement($e) [YYVALID;]
	  { $$ = build_if($3, $6, $8);
	    @@.start = @1.start; @@.end = @8.end; }
  | IF '(' expr($e) ')' THEN statement($e) [YYVALID;]
	  { $$ = build_if($3, $6, 0);
	    @@.start = @1.start; @@.end = @6.end; }
  | block_statement(new_scope($e)) [YYVALID;]{ $$ = $1; @@ = @1; }
  ;

statement_list($e):			{ $$ = 0; }
  | statement_list($e) statement($e)
	  { $$ = code_append($1, $2);
	    @@.start = @1.start.line ? @1.start : @2.start;
	    @@.end = @2.end; }
  ;

block_statement($e):
    '{' statement_list($e) '}'
	  { $$ = $2;
	    @@.start = @1.start; @@.end = @3.end; }
  ;

%%

/* trailing code */
