/*
The MIT License (MIT)

Copyright (c) 2014

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

%{
#include "cpptoken.h"
#include "cppdom.h"
#include "parser.tab.h"
#include "cppobjfactory.h"

#include <stack>

//////////////////////////////////////////////////////////////////////////

#ifndef NDEBUG
#  define YYDEBUG 1
#else 
#  define YYDEBUG 0
#endif //#ifndef NDEBUG

#define YYERROR_DETAILED

#define YYDELETEPOSN(x, y)
#define YYDELETEVAL(x, y)

#ifndef TRUE // Need this to fix BtYacc compilation error.
#  define TRUE true
#endif

static int gLog = 0;
#define ZZVALID   \
  if (gLog) \
    printf("YYVALID @line#%d\n", __LINE__); \
  YYVALID
/**
 * A program unit is the entire parse tree of a source/header file
 */
static CppCompound*  gProgUnit;

/**
 * A stack to know where (i.e. how deep inside class defnition) the current parsing activity is taking place.
 */
typedef std::stack<CppToken>        CppCompoundStack;
static CppCompoundStack             gCompoundStack;

static CppObjProtLevel              gCurProtLevel;
static std::stack<CppObjProtLevel>  gProtLevelStack;

extern CppObjFactory*               gObjFactory;

template<typename... Params>
CppCompound* newCompound(Params... params)
{
  return gObjFactory->CreateCompound(params...);
}

template<typename... Params>
CppConstructor* newConstructor(Params... params)
{
  return gObjFactory->CreateConstructor(params...);
}

template<typename... Params>
CppDestructor* newDestructor(Params... params)
{
  return gObjFactory->CreateDestructor(params...);
}

template<typename... Params>
CppFunction* newFunction(Params... params)
{
  return gObjFactory->CreateFunction(params...);
}

#define YYPOSN char*
/**
 * To track the line being parsed so that we can emit precise location of parsing error.
 */
int gLineNo = 1;

extern int yylex();

%}

/**
 * The union that can hold terminal and non-terminal objects in a parse tree.
 */
%union {
  CppToken              str;
  CppObj*               cppObj;
  CppVar*               cppVarObj;
  CppEnum*              cppEnum;
  CppEnumItem*          enumItem;
  CppEnumItemList*      enumItemList;
  CppTypedef*           typedefObj;
  CppCompound*          cppCompundObj;
  CppDocComment*        docCommentObj;
  CppFwdClsDecl*        fwdDeclObj;
  CppVarList*           cppVarObjList;
  CppUnRecogPrePro*     unRecogPreProObj;
  CppExpr*              cppExprObj;
  CppFunction*          cppFuncObj;
  CppFunctionPtr*       cppFuncPointerObj;
  CppVarOrFuncPtrType   varOrFuncPtr;
  CppParamList*         paramList;
  CppConstructor*       cppCtorObj;
  CppDestructor*        cppDtorObj;
  CppMemInitList*       memInitList;
  CppInheritanceList*   inheritList;
  CppCompoundType       compoundType;
  unsigned short        ptrLevel;
  CppRefType            refType;
  unsigned int          attr;
  CppObjProtLevel       protLevel;

  CppExprList*          exprList;

  CppDefine*            hashDefine;
  CppUndef*             hashUndef;
  CppInclude*           hashInclude;
  CppHashIf*            hashIf;
  CppPragma*            hashPragma;

  CppBlankLine*         blankLine;
}

%token  <str>   tknID tknStrLit tknCharLit tknNumber tknTypedef
%token  <str>   tknLong
%token  <str>   tknEnum
%token  <str>   tknPreProDef
%token  <str>   tknClass tknStruct tknUnion tknNamespace
%token  <str>   tknDocBlockComment tknDocLineComment
%token  <str>   tknScopeResOp
%token  <str>   tknNumSignSpec // signed/unsigned
%token  <str>   tknPublic tknProtected tknPrivate
%token  <str>   tknExternC
%token  <str>   tknUnRecogPrePro
%token  <str>   tknStdHdrInclude
%token  <str>   tknPragma
%token  <str>   tknEllipsis
%token  <str>   '<' '>' // We will need the position of these operators in stream when used for declaring template instance.

%token  tknConst tknStatic tknExtern tknVirtual tknOverride tknInline tknExplicit tknFriend tknVolatile

%token  tknPreProHash /* When # is encountered for pre processor definition */
%token  tknDefine tknUndef
%token  tknInclude tknStdHdrInclude
%token  tknIf tknIfDef tknIfNDef tknElse tknElIf tknEndIf
%token  tknNew tknDelete tknReturn

%token  tknBlankLine

%type  <str>                apidocer
%type  <str>                identifier vartype optid
%type  <cppObj>             stmt functptrtype
%type  <cppEnum>            enumdefn enumfwddecl
%type  <enumItem>           enumitem
%type  <enumItemList>       enumitemlist
%type  <fwdDeclObj>         fwddecl
%type  <cppVarObj>          varqual vardecl varinit vardeclstmt
%type  <varOrFuncPtr>       param templateparam
%type  <cppVarObjList>      vardecllist vardeclliststmt
%type  <paramList>          paramlist
%type  <typedefObj>         typedefname typedefnamelist typedefnamestmt
%type  <cppCompundObj>      stmtlist progunit classdefn classdefnstmt externcblock
%type  <docCommentObj>      doccomment
%type  <cppExprObj>         expr exprstmt
%type  <cppFuncPointerObj>  functionpointer funcpointerdecl
%type  <cppFuncObj>         funcdecl funcdeclstmt funcdefn
%type  <cppCtorObj>         ctordecl ctordeclstmt ctordefn
%type  <cppDtorObj>         dtordecl dtordeclstmt dtordefn
%type  <memInitList>        meminitlist
%type  <compoundType>       compoundSpecifier
%type  <ptrLevel>           ptrlevelopt ptrlevel
%type  <refType>            reftype
%type  <attr>               optattr varattrib funcattrib functype
%type  <inheritList>        inheritlist
%type  <protLevel>          protlevel changeprotlevel

%type  <exprList>           exprlist
%type  <hashDefine>         define
%type  <hashUndef>          undef
%type  <hashInclude>        include
%type  <hashIf>             hashif
%type  <hashPragma>         pragma

%type  <blankLine>          blankline

%right  '=' CMPEQUAL
%left   '+' '-'
%left   '*' '/' '%'
%right  LSHIFT RSHIFT
%left   '&' '|'
%left   '.' ARROW

%nonassoc PREFIX
%nonassoc POSTFIX '(' '['

/*
These are required to remove following ambiguity in the grammer.
Consider the following example:
  x * y;
Now it can be parsed as:
  (1) y is a pointer to type-x.
  (2) Or, the expression is multiplication of x and y.
Same ambiguity exists for:
  x * y = z;
  x & y;
  x & y = z;
  x && y;
  x && y = z;
PTRDECL and REFDECL solve this problem by giving variable declaration higher precedence.
*/
%left PTRDECL REFDECL

/*
These are required to remove following ambiguity in the grammer.
Consider the following example:
  class A
  {
    A();  // ctor declaration
    ~A(); // dtor declaration
  };

Now A() can be parsed in two different ways:
  (1) As a constructor declaration.
  (2) Or, as a function call.
Also, ~A() can be parsed as:
  (1) As a destructor declaration.
  (2) Or, as an expression where bit toggle operation is done on a return value of function call.
CTORDECL and DTORDECL solve this problem by giving constructor and destructor declarations higher precedence.
*/
%left CTORDECL DTORDECL


%%

/* A program unit is a source file, be it header file or implementation file */
progunit          : stmtlist  {
                    gProgUnit = $$ = $1;
                    if (gProgUnit)
                      gProgUnit->compoundType_ = kCppFile;
                  }
                  ;

stmtlist          : { $$ = 0; }
                  | stmt {
                    $$ = newCompound(gProtLevelStack.empty() ? gCurProtLevel : gProtLevelStack.top());
                    $1->owner_ = $$;
                    $$->addMember($1);
                  }
                  | stmtlist stmt {
                    $$ = ($1 == 0) ? newCompound(gProtLevelStack.empty() ? gCurProtLevel : gProtLevelStack.top()) : $1;
                    $2->owner_ = $$;
                    $$->addMember($2);
                  }
                  | stmtlist changeprotlevel { $$ = $1; gCurProtLevel = $2; } // Change of protection level is not a statement but this way it is easier to implement.
                  ;

stmt              : vardeclstmt     { $$ = $1; }
                  | vardeclliststmt { $$ = $1; }
                  | enumdefn        { $$ = $1; }
                  | enumfwddecl     { $$ = $1; }
                  | typedefnamestmt { $$ = $1; }
                  | classdefnstmt   { $$ = $1; }
                  | fwddecl         { $$ = $1; }
                  | doccomment      { $$ = $1; }
                  | exprstmt        { $$ = $1; }
                  | funcpointerdecl { $$ = $1; }
                  | funcdeclstmt    { $$ = $1; }
                  | funcdefn        { $$ = $1; }
                  | ctordeclstmt    { $$ = $1; }
                  | ctordefn        { $$ = $1; }
                  | dtordeclstmt    { $$ = $1; }
                  | dtordefn        { $$ = $1; }
                  | externcblock    { $$ = $1; }
                  | functptrtype    { $$ = $1; }
                  | define          { $$ = $1; }
                  | undef           { $$ = $1; }
                  | include         { $$ = $1; }
                  | hashif          { $$ = $1; }
                  | pragma          { $$ = $1; }
                  | blankline       { $$ = $1; }
                  ;

blankline         : tknBlankLine { $$ = new CppBlankLine; }
                  | blankline tknBlankLine { $$ = $1; $$->numLines_++; }
                  ;

define            : tknPreProHash tknDefine tknID tknID         [ZZVALID;] { // Simple rename using #define
                    $$ = new CppDefine($3, $4);
                    $$->defType_ = CppDefine::kRename;
                  }
                  | tknPreProHash tknDefine tknID               [ZZVALID;] { // blank define
                    $$ = new CppDefine($3);
                    $$->defType_ = CppDefine::kRename;
                  }
                  | tknPreProHash tknDefine tknID tknNumber     [ZZVALID;] {// Constant definition
                    $$ = new CppDefine($3, $4);
                    $$->defType_ = CppDefine::kConstNumDef;
                  }
                  | tknPreProHash tknDefine tknID tknStrLit     [ZZVALID;] {
                    $$ = new CppDefine($3, $4);
                    $$->defType_ = CppDefine::kConstStrDef;
                  }
                  | tknPreProHash tknDefine tknID tknCharLit    [ZZVALID;] {
                    $$ = new CppDefine($3, $4);
                    $$->defType_ = CppDefine::kConstCharDef;
                  }
                  | tknPreProHash tknDefine tknID tknPreProDef  [ZZVALID;] {
                    $$ = new CppDefine($3, $4);
                    $$->defType_ = CppDefine::kComplexMacro;
                  }
                  ;

undef             : tknPreProHash tknUndef tknID                [ZZVALID;]  { $$ = new CppUndef($3); }
                  ;

include           : tknPreProHash tknInclude tknStrLit          [ZZVALID;]  { $$ = new CppInclude((std::string) $3); }
                  | tknPreProHash tknInclude tknStdHdrInclude   [ZZVALID;]  { $$ = new CppInclude((std::string) $3); }
                  ;
/*
preprocessor    : tknPreProHash tknUnRecogPrePro tknPreProDef { $$ = new CppUnRecogPrePro((std::string) $2, (std::string) $3); }
          ;
*/
hashif            : tknPreProHash tknIf tknPreProDef            [ZZVALID;]  { $$ = new CppHashIf(CppHashIf::kIf,      $3); }
                  | tknPreProHash tknIfDef tknID                [ZZVALID;]  { $$ = new CppHashIf(CppHashIf::kIfDef,   $3); }
                  | tknPreProHash tknIfNDef tknID               [ZZVALID;]  { $$ = new CppHashIf(CppHashIf::kIfNDef,  $3); }
                  | tknPreProHash tknElse                       [ZZVALID;]  { $$ = new CppHashIf(CppHashIf::kElse       ); }
                  | tknPreProHash tknElIf  tknPreProDef         [ZZVALID;]  { $$ = new CppHashIf(CppHashIf::kElIf,    $3); }
                  | tknPreProHash tknEndIf                      [ZZVALID;]  { $$ = new CppHashIf(CppHashIf::kEndIf      ); }
                  ;

pragma            : tknPreProHash tknPragma tknPreProDef        [ZZVALID;]  { $$ = new CppPragma($3); }
                  ;

doccomment        : tknDocBlockComment  [ZZVALID;] { $$ = new CppDocComment((std::string) $1); }
                  | tknDocLineComment   [ZZVALID;] { $$ = new CppDocComment((std::string) $1); }
                  ;

identifier        : tknID                                 { $$ = $1; }
                  | tknScopeResOp identifier              { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  | identifier tknScopeResOp identifier   { $$ = makeCppToken($1.sz, $3.sz+$3.len-$1.sz); }
                  | tknLong                               { $$ = $1; }
                  | tknLong identifier                    { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  | tknNumSignSpec                        { $$ = $1; }
                  | tknNumSignSpec identifier             { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  | tknEllipsis                           { $$ = $1; }
                  | identifier tknEllipsis                { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  ;

optid             : { $$ = makeCppToken(0, 0); }
                  | tknID      { $$ = $1; }
                  ;

enumitem          : tknID           { $$ = new CppEnumItem($1);     }
                  | tknID '=' expr  { $$ = new CppEnumItem($1, $3); }
                  | doccomment      { $$ = new CppEnumItem($1);     }
                  | hashif          { $$ = new CppEnumItem($1);     }
                  | blankline       { $$ = new CppEnumItem($1);     }
                  ;

enumitemlist      : { $$ = 0; }
                  | enumitemlist enumitem {
                    $$ = $1 ? $1 : new CppEnumItemList;
                    $$->push_back($2);
                  }
                  | enumitemlist ',' enumitem {
                    $$ = $1 ? $1 : new CppEnumItemList;
                    $$->push_back($3);
                  }
                  | enumitemlist ',' {
                    $$ = $1;
                  }
                  ;

enumdefn          : tknEnum optid '{' enumitemlist '}' ';'                          [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $2, $4);
                  }
                  | tknEnum tknID ':' identifier '{' enumitemlist '}' ';'           [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $2, $6, false, $4);
                  };
                  | tknEnum tknClass tknID ':' identifier '{' enumitemlist '}' ';'  [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $3, $7, true, $5);
                  }
                  | tknEnum tknClass tknID '{' enumitemlist '}' ';'                 [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $3, $5, true);
                  }

enumfwddecl       : tknEnum tknID ':' identifier ';'                                [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $2, nullptr, false, $4);
                  }
                  | tknEnum tknClass tknID ':' identifier ';'                       [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $3, nullptr, true, $5);
                  }
                  | tknEnum tknClass tknID ';'                                      [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $3, nullptr, true);
                  }
                  ;

typedefnamestmt   : typedefnamelist ';' [ZZVALID;] { $$ = $1; }
                  | typedefname ';'     [ZZVALID;] { $$ = $1; }
                  ;

typedefnamelist   : typedefname ',' tknID { $$ = $1; $$->names_.push_back((std::string) $3); }
                  ;

typedefname       : tknTypedef optattr vartype ptrlevelopt reftype tknID {
                    $$ = new CppTypedef(gCurProtLevel, $3, $2, $4, $5);
                    $$->names_.push_back((std::string) $6);
                  }
                  ;

vartype           : identifier                  { $$ = $1; }
                  | tknNumSignSpec identifier   { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  | tknClass identifier         { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  | tknStruct identifier        { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  | tknUnion identifier         { $$ = makeCppToken($1.sz, $2.sz+$2.len-$1.sz); }
                  | identifier '<' templateparam '>'{
                    $$ = makeCppToken($1.sz, $4.sz+1-$1.sz);
                    delete $3.cppObj; // We don't need template parameter
                  }
                  ;

varinit           : vardecl '=' expr            { $$ = $1; $$->assign_ = $3; }
                  ;

vardecl           : varattrib varqual identifier optattr {
                    $$ = $2;
                    $$->name_ = $3;
                    $$->varAttr_ |= $4;
                    $$->typeAttr_|= $1;
                  }
                  | varqual identifier optattr {
                    $$ = $1;
                    $$->name_ = $2;
                    $$->varAttr_ |= $3;
                  }
                  | varattrib varqual identifier '[' expr ']' {
                    $$ = $2;
                    $$->name_ = $3;
                    $$->varAttr_|= $1|kArray;
                    $$->arraySize_ = $5;
                  }
                  | varattrib varqual identifier '[' ']' {
                    $$ = $2;
                    $$->name_ = $3;
                    $$->varAttr_|= $1|kArray;
                  }
                  | varqual identifier '[' expr ']' {
                    $$ = $1;
                    $$->name_ = $2;
                    $$->varAttr_|= kArray;
                    $$->arraySize_ = $4;
                  }
                  | varqual identifier '[' ']' {
                    $$ = $1;
                    $$->name_ = $2;
                    $$->varAttr_|= kArray;
                  }


                  /* Below rules are defined to remove ambiguity in the grammer. */
                  /* See comments near definition of PTRDECL above for details. */
                  | vartype ptrlevel identifier %prec PTRDECL {
                    $$ = new CppVar(gCurProtLevel, $1, 0, 0, $2, kNoRef, $3);
                  }
                  | vartype '&' identifier %prec REFDECL {
                    $$ = new CppVar(gCurProtLevel, $1, 0, 0, 0, kByRef, $3);
                  }
                  | vartype '&' '&' identifier %prec REFDECL {
                    $$ = new CppVar(gCurProtLevel, $1, 0, 0, 0, kRValRef, $4);
                  }
                  /* Disambiguation rules end. */
                  ;

varqual           : optattr vartype optattr ptrlevelopt reftype optattr {
                    $$ = new CppVar(gCurProtLevel, $2, $1|$3, $6, $4, $5, "");
                  }
                  | optattr vartype optattr ptrlevelopt reftype '[' expr ']' optattr {
                    $$ = new CppVar(gCurProtLevel, $2, $1|$3|kArray, $9, $4, $5, "");
                    $$->arraySize_ = $7;
                  }
                  | optattr vartype optattr ptrlevelopt reftype '[' ']' optattr {
                    $$ = new CppVar(gCurProtLevel, $2, $1|$3|kArray, $8, $4, $5, "");
                  }
                  ;

varattrib         : tknStatic { $$ = kStatic;  }
                  | tknExtern  { $$ = kExtern;  }
                  ;

funcdeclstmt      : funcdecl ';' [ZZVALID;] { $$ = $1; }
                  ;

funcdefn          : funcdecl '{' stmtlist '}' [ZZVALID;] {
                    $$ = $1;
                    $$->defn_ = $3 ? $3 : newCompound(kUnknownProt);
                    $$->defn_->compoundType_ = kBlock;
                  }
                  ;

functptrtype      : tknTypedef functionpointer ';' [ZZVALID;] {
                    $2->attr_ |= kTypedef;
                    $$ = $2;
                  }

functionpointer   : apidocer functype varqual '(' apidocer '*' optid ')' '(' paramlist ')' {
                    $$ = new CppFunctionPtr(gCurProtLevel, $7, $3, $10, $2);
                    $$->docer1_ = $1;
                    $$->docer2_ = $5;
                  }
                  | apidocer varqual '(' apidocer '*' optid ')' '(' paramlist ')' {
                    $$ = new CppFunctionPtr(gCurProtLevel, $6, $2, $9, 0);
                    $$->docer1_ = $1;
                    $$->docer2_ = $4;
                  }
                  ;

funcpointerdecl   : functionpointer ';' [ZZVALID;] { $$ = $1;}
                  ;

funcdecl          : functype apidocer varqual apidocer identifier '(' paramlist ')' funcattrib {
                    $$ = newFunction(gCurProtLevel, $5, $3, $7, $1 | $9);
                    $$->docer1_ = $2;
                    $$->docer2_ = $4;
                  }
                  | apidocer varqual apidocer identifier '(' paramlist ')' funcattrib {
                    $$ = newFunction(gCurProtLevel, $4, $2, $6, $8);
                    $$->docer1_ = $1;
                    $$->docer2_ = $3;
                  }
                  ;

paramlist         : { $$ = 0; }
                  | param {
                    $$ = new CppParamList;
                    $$->push_back($1);
                  }
                  | paramlist ',' param {
                    $1->push_back($3);
                    $$ = $1;
                  }
                  ;

param             : varinit                 { $$ = $1; $1->varAttr_ |= kFuncParam;  }
                  | vardecl                 { $$ = $1; $1->varAttr_ |= kFuncParam;  }
                  | varqual                 { $$ = $1; $1->varAttr_ |= kFuncParam;  }
                  | functionpointer         { $$ = $1; $1->attr_ |= kFuncParam;    }
                  ;

templateparam     : varqual                 { $$ = $1; }
                  | functionpointer         { $$ = $1; }
                  ;

functype          : varattrib               { $$ = $1;      }
                  | tknInline               { $$ = kInline;    }
                  | tknVirtual              { $$ = kVirtual;  }
                  | tknExtern               { $$ = kExtern;    }
                  | tknExplicit             { $$ = kExplicit;  }
                  | tknInline tknExplicit   { $$ = kInline | kExplicit; }
                  | tknExplicit tknInline   { $$ = kInline | kExplicit; }
                  ;

funcattrib        :                           { $$ = 0; }
                  | funcattrib tknConst       { $$ = $1 | kConst; }
                  | funcattrib tknOverride    { $$ = $1 | kOverride; }
                  | funcattrib '=' tknNumber  [if($3.len != 1 || $3.sz[0] != '0') YYABORT; else ZZVALID;]
                                              { $$ = $1 | kPureVirtual; }
                  ;

optattr           : { $$ = 0; }
                  | tknConst { $$ = kConst; }
                  | tknVolatile { $$ = kVolatile; }
                  ;

ctordeclstmt      : ctordecl';' [ZZVALID;] { $$ = $1; }
                  ;

ctordefn          : ctordecl meminitlist
                    '{'
                      stmtlist
                    '}' [ZZVALID;]
                  {
                    $$ = $1;
                    $$->memInitList_  = $2;
                    $$->defn_      = $4 ? $4 : newCompound(kUnknownProt, kBlock);
                  }
                  | tknID tknScopeResOp tknID [if($1 != $3) YYERROR; else ZZVALID;]
                    '(' paramlist ')' meminitlist
                    '{'
                      stmtlist
                    '}' [ZZVALID;]
                  {
                    $$ = newConstructor(gCurProtLevel, makeCppToken($1.sz, $3.sz+$3.len-$1.sz), $6, $8, 0);
                    $$->defn_      = $10 ? $10 : newCompound(kUnknownProt, kBlock);
                  }
                  | identifier tknScopeResOp tknID tknScopeResOp tknID [if($3 != $5) YYERROR; else ZZVALID;]
                    '(' paramlist ')' meminitlist
                    '{'
                      stmtlist
                    '}' [ZZVALID;]
                  {
                    $$ = newConstructor(gCurProtLevel, makeCppToken($1.sz, $5.sz+$5.len-$1.sz), $8, $10, 0);
                    $$->defn_      = $12 ? $12 : newCompound(gCurProtLevel, kBlock);
                  }
                  ;

ctordecl          : tknID '(' paramlist ')' %prec CTORDECL
                  [
                    if(gCompoundStack.empty())
                      YYERROR;
                    if(gCompoundStack.top() != $1)
                      YYERROR;
                    else
                      ZZVALID;
                  ]
                  {
                    $$ = newConstructor(gCurProtLevel, $1, $3, nullptr, 0);
                  }
                  | functype tknID [if(gCompoundStack.empty()) YYERROR; if(gCompoundStack.top() != $2) YYERROR; else ZZVALID;] '(' paramlist ')'
                  {
                    $$ = newConstructor(gCurProtLevel, $2, $5, nullptr, $1);
                  }
                  ;

meminitlist       : { $$ = NULL; }
                  | ':' tknID '(' expr ')'        { $$ = new CppMemInitList; $$->push_back(CppMemInit($2, $4)); }
                  | meminitlist ',' tknID '(' expr ')'  { $$ = $1; $$->push_back(CppMemInit($3, $5)); }
                  ;

dtordeclstmt      : dtordecl ';' [ZZVALID;] { $$ = $1; }
                  ;

dtordefn          : dtordecl '{' stmtlist '}' [ZZVALID;]
                  {
                    $$ = $1;
                    $$->defn_ = $3 ? $3 : newCompound(kUnknownProt, kBlock);
                  }
                  | tknID tknScopeResOp '~' tknID [if($1 != $4) YYERROR; else ZZVALID;]
                    '(' ')' '{' stmtlist '}'
                  {
                    $$ = newDestructor(gCurProtLevel, makeCppToken($1.sz, $4.sz+$4.len-$1.sz), 0);
                    $$->defn_      = $9 ? $9 : newCompound(kUnknownProt, kBlock);
                  }
                  | identifier tknScopeResOp tknID tknScopeResOp '~' tknID [if($3 != $6) YYERROR; else ZZVALID;]
                    '(' ')' '{' stmtlist '}'
                  {
                    $$ = newDestructor(gCurProtLevel, makeCppToken($1.sz, $6.sz+$6.len-$1.sz), 0);
                    $$->defn_      = $11 ? $11 : newCompound(kUnknownProt, kBlock);
                  }
                  ;

dtordecl          : '~' tknID '(' ')' %prec DTORDECL
                  [
                    if(gCompoundStack.empty())
                      YYERROR;
                    if(gCompoundStack.top() != $2)
                      YYERROR;
                    else
                      ZZVALID;
                  ]
                  {
                    const char* tildaStartPos = $2.sz-1;
                    while(*tildaStartPos != '~') --tildaStartPos;
                    $$ = newDestructor(gCurProtLevel, makeCppToken(tildaStartPos, $2.sz+$2.len-tildaStartPos), 0);
                  }
                  | functype '~' tknID '(' ')' %prec DTORDECL
                  [
                    if(gCompoundStack.empty())
                      YYERROR;
                    if(gCompoundStack.top() != $3)
                      YYERROR;
                    else
                      ZZVALID;
                  ]
                  {
                    const char* tildaStartPos = $3.sz-1;
                    while(*tildaStartPos != '~') --tildaStartPos;
                    $$ = newDestructor(gCurProtLevel, makeCppToken(tildaStartPos, $3.sz+$3.len-tildaStartPos), $1);
                  }
                  | tknVirtual '~' tknID '(' ')' '=' tknNumber
                  [
                    if(gCompoundStack.empty())
                      YYERROR;
                    if(gCompoundStack.top() != $3)
                      YYERROR;
                    else
                      ZZVALID;
                  ]
                  {
                    const char* tildaStartPos = $3.sz-1;
                    while(*tildaStartPos != '~') --tildaStartPos;
                    $$ = newDestructor(gCurProtLevel, makeCppToken(tildaStartPos, $3.sz+$3.len-tildaStartPos), kPureVirtual);
                  }
                  ;

vardecllist       : vardecl ',' optattr ptrlevelopt reftype optattr identifier optattr {
                    $$ = new CppVarList();
                    $$->addVar($1);
                    $$->addVar(new CppVar(gCurProtLevel, $1->baseType_, $1->typeAttr_|$3, $6|$8, $4, $5, $7));
                  }
                  | vardecllist ',' optattr ptrlevelopt reftype optattr identifier optattr {
                    $$ = $1;
                    $$->addVar(new CppVar(gCurProtLevel, $1->varlist_.back()->baseType_, $1->varlist_.back()->typeAttr_|$3, $6|$8, $4, $5, $7));
                  }
                  ;

vardeclliststmt   : vardecllist ';' [ZZVALID;] { $$ = $1; }
                  ;

vardeclstmt       : vardecl ';'    [ZZVALID;] { $$ = $1; }
                  | varinit ';'    [ZZVALID;] { $$ = $1; }
                  | tknID vardecl ';'  [ZZVALID;] { $$ = $2; $$->apidocer_ = $1; }
                  ;

ptrlevelopt       :        { $$ = 0;    }
                  | ptrlevel    { $$ = $1;    }
                  ;

ptrlevel          : '*'      { $$ = 1;    }
                  | ptrlevel '*'  { $$ = $1 + 1;  }
                  ;

reftype           :      { $$ = kNoRef;    }
                  | '&'    { $$ = kByRef;    }
                  | '&' '&'  { $$ = kRValRef;  }
                  ;

classdefnstmt     : classdefn ';' [ZZVALID;] { $$ = $1;}
                  ;

classdefn         : compoundSpecifier apidocer tknID inheritlist
                    '{' [gCompoundStack.push($3); ZZVALID;] { gProtLevelStack.push(gCurProtLevel); gCurProtLevel = kUnknownProt; }
                      stmtlist
                    '}' [gCompoundStack.pop(); ZZVALID;]
                  {
                    gCurProtLevel = gProtLevelStack.top();
                    gProtLevelStack.pop();

                    $$ = $7 ? $7 : newCompound(gCurProtLevel);
                    $$->compoundType_  = $1;
                    $$->apidocer_    = $2;
                    $$->name_      = $3;
                    $$->inheritList_  = $4;
                  }

inheritlist       : { $$ = 0; }
                  | ':' protlevel identifier [ZZVALID;]        { $$ = new CppInheritanceList; $$->push_back(CppInheritInfo((std::string) $3, $2)); }
                  | inheritlist ',' protlevel identifier [ZZVALID;]  { $$ = $1; $$->push_back(CppInheritInfo((std::string) $4, $3)); }
                  ;

protlevel         :        { $$ = kUnknownProt;}
                  | tknPublic    { $$ = kPublic;    }
                  | tknProtected  { $$ = kProtected;  }
                  | tknPrivate  { $$ = kPrivate;  }
                  ;

fwddecl           : compoundSpecifier identifier ';' [ZZVALID;] { $$ = new CppFwdClsDecl(gCurProtLevel, $2, $1); }
                  | compoundSpecifier apidocer identifier ';' [ZZVALID;] { $$ = new CppFwdClsDecl(gCurProtLevel, $3, $1); }
                  ;

compoundSpecifier : tknClass    { $$ = kClass;    }
                  | tknStruct    { $$ = kStruct;    }
                  | tknUnion    { $$ = kUnion;    }
                  | tknNamespace  { $$ = kNamespace;  }
                  ;

apidocer          : { $$ = makeCppToken(0, 0); }
                  | tknID { $$ = $1; }
                  ;

changeprotlevel   : tknPublic     ':'  [ZZVALID;] { $$ = kPublic;     }
                  | tknProtected  ':'  [ZZVALID;] { $$ = kProtected;  }
                  | tknPrivate    ':'  [ZZVALID;] { $$ = kPrivate;    }
                  ;

externcblock      : tknExternC '{' stmtlist '}' [ZZVALID;] {$$ = $3; $$->compoundType_ = kExternCBlock; }
                  ;

exprlist          : expr              { $$ = new CppExprList(); $$->push_back($1);  }
                  | exprlist ',' expr { $$ = $1; $$->push_back($3);                 }
                  ;

expr              : tknStrLit                         { $$ = new CppExpr((std::string) $1, kNone);          }
                  | tknCharLit                        { $$ = new CppExpr((std::string) $1, kNone);          }
                  | tknNumber                         { $$ = new CppExpr((std::string) $1, kNone);          }
                  | identifier                        { $$ = new CppExpr((std::string) $1, kNone);          }
                  | '{' exprlist '}'                  { $$ = new CppExpr($2, CppExpr::kInitializer);        }
                  | '-' expr %prec PREFIX             { $$ = new CppExpr($2, kUnaryMinus);                  }
                  | '~' expr %prec PREFIX             { $$ = new CppExpr($2, kBitToggle);                   }
                  | '!' expr %prec PREFIX             { $$ = new CppExpr($2, kLogNot);                      }
                  | '*' expr %prec PREFIX             { $$ = new CppExpr($2, kDerefer);                     }
                  | '&' expr %prec PREFIX             { $$ = new CppExpr($2, kRefer);                       }
                  | expr '+' expr                     { $$ = new CppExpr($1, kPlus, $3);                    }
                  | expr '-' expr                     { $$ = new CppExpr($1, kMinus, $3);                   }
                  | expr '*' expr                     { $$ = new CppExpr($1, kMul, $3);                     }
                  | expr '/' expr                     { $$ = new CppExpr($1, kDiv, $3);                     }
                  | expr '&' expr                     { $$ = new CppExpr($1, kBitAnd, $3);                  }
                  | expr '|' expr                     { $$ = new CppExpr($1, kBitOr, $3);                   }
                  | expr '=' expr                     { $$ = new CppExpr($1, kEqual, $3);                   }
                  | expr '[' expr ']' %prec POSTFIX   { $$ = new CppExpr($1, kArrayElem, $3);               }
                  | expr '=' '=' expr %prec CMPEQUAL  { $$ = new CppExpr($1, kCmpEqual, $4);                }
                  | expr '<' '<' expr %prec LSHIFT    { $$ = new CppExpr($1, kLeftShift, $4);               }
                  | expr '>' '>' expr %prec RSHIFT    { $$ = new CppExpr($1, kRightShift, $4);              }
                  | expr '-' '>' expr %prec ARROW     { $$ = new CppExpr($1, kArrow, $4);                   }
                  | expr '.' expr                     { $$ = new CppExpr($1, kDot, $3);                     }
                  | expr '(' ')'                      { $$ = new CppExpr($1, kFunctionCall);                }
                  | expr '(' exprlist ')'             { $$ = new CppExpr($1, kFunctionCall, $3);            }
                  | '(' expr ')'                      { $$ = $2; $2->flags_ |= CppExpr::kBracketed;         }
                  | tknNew  expr                      { $$ = $2; $2->flags_ |= CppExpr::kNew;               }
                  | tknDelete  expr                   { $$ = $2; $2->flags_ |= CppExpr::kDelete;            }
                  | tknDelete  '[' ']' expr           { $$ = $4; $4->flags_ |= CppExpr::kDeleteArray;       }
                  | tknReturn  expr                   { $$ = $2; $2->flags_ |= CppExpr::kReturn;            }
                  | tknReturn                         { $$ = new CppExpr(CppExprAtom(), CppExpr::kReturn);  }
                  ;

exprstmt          : expr ';'  [ZZVALID;]              { $$ = $1; }
                  ;

%%

//////////////////////////////////////////////////////////////////////////

/**
 * yyparser() invokes this function when it encounters unexpected token.
 */
void yyerror_detailed  (  char* text,
              int errt,
              YYSTYPE& errt_value,
              YYPOSN& errt_posn
            )
{
  extern const char* get_start_of_buffer();
  extern int get_context();

  const char* lineStart = errt_posn;
  const char* buffStart = get_start_of_buffer();
  while(lineStart > buffStart)
  {
    if(lineStart[-1] == '\n' || lineStart[-1] == '\r')
      break;
    --lineStart;
  }
  char* lineEnd = errt_posn;
  char endReplaceChar = 0;
  while(*lineEnd)
  {
    if(*lineEnd == '\r' || *lineEnd == '\n')
    {
      endReplaceChar = *lineEnd;
      *lineEnd = '\0'; // So that printing of lineStart does not print things beyond current line.
    }
    else
    {
      ++lineEnd;
    }
  }
  char spacechars[1024] = {0}; // For printing enough whitespace chars so that we can show a ^ below the start of unexpected token.
  for(const char* p = lineStart; p < errt_posn; ++p)
    spacechars[p-lineStart] = *p == '\t' ? '\t' : ' ';
  char errmsg[1024];
  sprintf(errmsg, "%s%s%s%d%s%d%c%s%c%s%c%c",
    "Error: Unexpected token '", errt_posn, "', while in context=", get_context(), ", found at line#", gLineNo, '\n', // The error message
    lineStart, '\n',    // Line that contains the error.
    spacechars, '^', '\n');  // A ^ below the beginning of unexpected token.
  printf("%s", errmsg);
  // Replace back the end char
  if(endReplaceChar)
    *lineEnd = endReplaceChar;
}

CppCompound* parseStream(char* stm, size_t stmSize)
{
  gProgUnit = nullptr;
  void setupScanBuffer(char* buf, size_t bufsize);
  setupScanBuffer(stm, stmSize);
  gLineNo = 1; // Reset so that we do not start counting beyond previous parsing.
  yyparse();

  return gProgUnit;
}
