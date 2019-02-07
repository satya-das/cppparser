/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

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

// clang-format off

%{
#include "cpptoken.h"
#include "cppdom.h"
#include "parser.tab.h"
#include "cppobjfactory.h"
#include "utils.h"

#include <iostream>
#include <stack>
#include <map>

//////////////////////////////////////////////////////////////////////////
  
std::map<std::string, int> gRenamedKeywords = {{"ADESK_SEALED_VIRTUAL", tknVirtual},
                                               {"ADESK_SEALED", tknFinal},
                                               {"ADESK_OVERRIDE", tknOverride}};

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
#define ZZVALID   { \
  if (gLog) \
    printf("YYVALID @line#%d\n", __LINE__); \
  YYVALID; }
  
/** {Globals} */
/**
 * A program unit is the entire parse tree of a source/header file
 */
static CppCompound*  gProgUnit;

// FuncdeclHack:
// Following gets parsed as variable with initialization:
// Type Identifier(Type * Id);
// `Type * Id` gets parsed as expression involving multiplication and so `Identifier`
//  followed by expression in brackets becomes a call to constructor of `Type`.
// Actually there is an ambiguity in the grammer which compilers solve by using context.
// For purpose of this parser we cannot collect all required context to solve this ambiguity.
// So, we use a hack:
// We define a production rule for this case and flag it as error. But before flagging error
// we save the position of operator '*' (or '&', or "&&") and then we check for location of
// the same operator in other expression production rule before accepting that as valid expression.
// For us we always want to parse it as function declaration rather than call to constructor by passing an expression,
// and so the hack is expected to serve us well.
static const char* gParamModPos = nullptr;

// TemplateParamHack:
// Template parameter gets parsed as vardecl which then gets reduced as templateparam without name as used in forward declaration.
// We don't want that, so to avoid such templateparam getting reduced as vardecl we apply some hack.
static const char* gTemplateParamStart = nullptr;
static bool gInTemplateSpec = false;

/**
 * A stack to know where (i.e. how deep inside class defnition) the current parsing activity is taking place.
 */
typedef std::stack<CppToken>        CppCompoundStack;
static CppCompoundStack             gCompoundStack;

static CppObjProtLevel              gCurProtLevel;
static std::stack<CppObjProtLevel>  gProtLevelStack;

/** {End of Globals} */

#define YYPOSN char*
/**
 * To track the line being parsed so that we can emit precise location of parsing error.
 */
int gLineNo = 1;

extern int yylex();

// Yacc generated code causes warnings that need suppression.
// This pragma should be at the end.
#if defined(__clang__) || defined(__GNUC__)
# pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

%}

%union {
  CppToken              str;
  CppObj*               cppObj;
  CppTypeModifier       typeModifier;
  CppVarType*           cppVarType;
  CppVar*               cppVarObj;
  CppEnum*              cppEnum;
  CppEnumItem*          enumItem;
  CppEnumItemList*      enumItemList;
  CppTypedefName*       typedefName;
  CppTypedefList*       typedefList;
  CppUsingDecl*         usingDecl;
  CppUsingNamespaceDecl*  usingNamespaceDecl;
  CppNamespaceAlias*    namespaceAlias;
  CppCompound*          cppCompundObj;
  CppTemplateParam*     templateParam;
  CppTemplateParamList* templSpec;
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
  CppTypeConverter*     cppTypeConverter;
  CppMemInitList*       memInitList;
  CppInheritanceList*   inheritList;
  CppIdentifierList*    identifierList;
  CppNtMemInit          memInit;
  CppFuncThrowSpec*     funcThrowSpec;
  CppCompoundType       compoundType;
  unsigned short        ptrLevel;
  CppRefType            refType;
  unsigned int          attr;
  CppObjProtLevel       protLevel;

  CppIfBlock*           ifBlock;
  CppWhileBlock*        whileBlock;
  CppDoWhileBlock*      doWhileBlock;
  CppForBlock*          forBlock;
  CppSwitchBlock*       switchBlock;
  CppSwitchBody*        switchBody;

  CppDefine*            hashDefine;
  CppUndef*             hashUndef;
  CppInclude*           hashInclude;
  CppHashIf*            hashIf;
  CppHashError*         hashError;
  CppPragma*            hashPragma;
}

%token  <str>   tknID tknStrLit tknCharLit tknNumber tknMacro tknApiDecor
%token  <str>   tknTypedef tknUsing
%token  <str>   tknLongLong tknLong tknInt tknShort tknChar
%token  <str>   tknEnum
%token  <str>   tknPreProDef
%token  <str>   tknClass tknStruct tknUnion tknNamespace
%token  <str>   tknTemplate tknTypename
%token  <str>   tknDocBlockComment tknDocLineComment
%token  <str>   tknScopeResOp
%token  <str>   tknNumSignSpec // signed/unsigned
%token  <str>   tknPublic tknProtected tknPrivate
%token  <str>   tknExternC
%token  <str>   tknUnRecogPrePro
%token  <str>   tknStdHdrInclude
%token  <str>   tknPragma tknHashError
%token  <str>   tknEllipsis
%token  <str>   tknConstCast tknStaticCast tknDynamicCast tknReinterpretCast
%token  <str>   tknTry tknCatch tknThrow tknSizeOf
%token  <str>   tknOperator tknPlusEq tknMinusEq tknMulEq tknDivEq tknPerEq tknXorEq tknAndEq tknOrEq
%token  <str>   tknLShift tknRShift tknLShiftEq tknRShiftEq tknCmpEq tknNotEq tknLessEq tknGreaterEq
%token  <str>   tkn3WayCmp tknAnd tknOr tknInc tknDec tknArrow tknArrowStar
%token  <str>   '<' '>' // We will need the position of these operators in stream when used for declaring template instance.
%token  <str>   '+' '-' '*' '/' '%' '^' '&' '|' '~' '!' '=' ',' '(' ')' '[' ']' ';'
%token  <str>   tknNew tknDelete
%token  <str>   tknConst tknConstExpr // For templatearg parsing it is made as str type.
%token  <str>   tknVoid // For the cases when void is used as function parameter.
%token  <str>   tknOverride // override is not a reserved keyword
%token  tknStatic tknExtern tknVirtual tknInline tknExplicit tknFriend tknVolatile tknFinal tknNoExcept

%token  tknPreProHash /* When # is encountered for pre processor definition */
%token  tknDefine tknUndef
%token  tknInclude
%token  tknIf tknIfDef tknIfNDef tknElse tknElIf tknEndIf
%token  tknFor tknWhile tknDo tknSwitch tknCase tknDefault
%token  tknReturn

%token  tknBlankLine

%type  <str>                optapidecor apidecor
%type  <str>                optnumsignspec
%type  <str>                identifier typeidentifier templidentifier varidentifier optid operfuncname funcname
%type  <str>                doccommentstr
%type  <str>                macrocall
%type  <cppObj>             stmt functptrtype
%type  <typeModifier>       opttypemodifier typemodifier
%type  <cppEnum>            enumdefn enumfwddecl
%type  <enumItem>           enumitem
%type  <enumItemList>       enumitemlist
%type  <fwdDeclObj>         fwddecl
%type  <cppVarType>         vartype
%type  <cppVarObj>          vardecl varinit vardeclstmt
%type  <varOrFuncPtr>       param
%type  <str>                templatearg templatearglist /* For time being. We may need to make it more robust in future. */
%type  <cppVarObjList>      vardecllist vardeclliststmt
%type  <paramList>          paramlist
%type  <typedefName>        typedefname typedefnamestmt
%type  <typedefList>        typedeflist typedefliststmt
%type  <usingNamespaceDecl> usingnamespacedecl
%type  <namespaceAlias>     namespacealias
%type  <usingDecl>          usingdecl
%type  <cppCompundObj>      stmtlist optstmtlist progunit classdefn classdefnstmt externcblock block
%type  <templSpec>          templatespecifier templateparamlist
%type  <templateParam>      templateparam
%type  <docCommentObj>      doccomment
%type  <cppExprObj>         expr exprstmt optexpr
%type  <ifBlock>            ifblock;
%type  <whileBlock>         whileblock;
%type  <doWhileBlock>       dowhileblock;
%type  <forBlock>           forblock;
%type  <switchBlock>        switchstmt;
%type  <switchBody>         caselist;
%type  <cppFuncPointerObj>  functionpointer funcpointerdecl
%type  <cppFuncObj>         funcdecl funcdeclstmt funcdefn
%type  <cppCtorObj>         ctordecl ctordeclstmt ctordefn
%type  <cppDtorObj>         dtordecl dtordeclstmt dtordefn
%type  <cppTypeConverter>   typeconverter typeconverterstmt
%type  <memInitList>        meminitlist
%type  <memInit>            meminit
%type  <compoundType>       compoundSpecifier
%type  <attr>               varattrib exptype optfuncattrib functype optfunctype
%type  <inheritList>        optinheritlist
%type  <protLevel>          protlevel changeprotlevel
%type  <identifierList>     identifierlist
%type  <funcThrowSpec>      functhrowspec optfuncthrowspec

%type  <hashDefine>         define
%type  <hashUndef>          undef
%type  <hashInclude>        include
%type  <hashIf>             hashif
%type  <hashError>          hasherror
%type  <hashPragma>         pragma

// precedence as mentioned at https://en.cppreference.com/w/cpp/language/operator_precedence
// &=, ^=, |=, <<=, >>=, *=, /=, %=, +=, -=, =, throw, a?b:c
%left ','
%right tknAndEq tknXorEq tknOrEq tknLShiftEq tknRShiftEq tknMulEq tknDivEq tknPerEq tknPlusEq tknMinusEq '=' tknThrow TERNARYCOND tknReturn
%left tknOr
%left tknAnd
%left '|'
%left '^'
%left '&'
%left tknCmpEq tknNotEq // ==, !=
// LESSTHAN and GREATERTHAN are used instead of '<' and '>' because otherwise template <...> was causing problem.
%left '<' tknLessEq '>' tknGreaterEq           //<, <=, >, >=
%left tkn3WayCmp       // <=>
%left  tknLShift tknRShift
%left   '+' '-'
%left   '*' '/' '%'
%left tknArrowStar
%right PREINCR PREDECR UNARYMINUS '!' '~' CSTYLECAST DEREF ADDRESSOF tknSizeOf tknNew tknDelete
%left POSTINCR POSTDECR FUNCTIONALCAST FUNCCALL SUBSCRIPT '.' tknArrow
%left tknScopeResOp
%right GLOBAL

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
progunit          : optstmtlist  {
                    gProgUnit = $$ = $1;
                    if (gProgUnit)
                      gProgUnit->compoundType_ = kCppFile;
                  }
                  ;

optstmtlist       : {
                    $$ = nullptr;
                  }
                  | stmtlist {
                    $$ = $1;
                  }
                  ;

stmtlist          : stmt {
                    $$ = newCompound(gProtLevelStack.empty() ? gCurProtLevel : gProtLevelStack.top());
                    if ($1)
                    {
                      $1->owner_ = $$;
                      $$->addMember($1);
                    } // Avoid 'comment-btyacc-constructs.sh' to act on this
                  }
                  | stmtlist stmt {
                    $$ = ($1 == 0) ? newCompound(gProtLevelStack.empty() ? gCurProtLevel : gProtLevelStack.top()) : $1;
                    if ($2)
                    {
                      $2->owner_ = $$;
                      $$->addMember($2);
                    } // Avoid 'comment-btyacc-constructs.sh' to act on this
                  }
                  | optstmtlist changeprotlevel { $$ = $1; gCurProtLevel = $2; } // Change of protection level is not a statement but this way it is easier to implement.
                  ;

stmt              : vardeclstmt     { $$ = $1; }
                  | vardeclliststmt { $$ = $1; }
                  | enumdefn        { $$ = $1; }
                  | enumfwddecl     { $$ = $1; }
                  | typedefnamestmt { $$ = $1; }
                  | typedefliststmt { $$ = $1; }
                  | classdefnstmt   { $$ = $1; }
                  | fwddecl         { $$ = $1; }
                  | doccomment      { $$ = $1; }
                  | exprstmt        { $$ = $1; }
                  | ifblock         { $$ = $1; }
                  | whileblock      { $$ = $1; }
                  | dowhileblock    { $$ = $1; }
                  | forblock        { $$ = $1; }
                  | funcpointerdecl { $$ = $1; }
                  | funcdeclstmt    { $$ = $1; }
                  | funcdefn        { $$ = $1; }
                  | ctordeclstmt    { $$ = $1; }
                  | ctordefn        { $$ = $1; }
                  | dtordeclstmt    { $$ = $1; }
                  | dtordefn        { $$ = $1; }
                  | typeconverterstmt { $$ = $1; }
                  | externcblock    { $$ = $1; }
                  | functptrtype    { $$ = $1; }
                  | define          { $$ = $1; }
                  | undef           { $$ = $1; }
                  | include         { $$ = $1; }
                  | hashif          { $$ = $1; }
                  | hasherror       { $$ = $1; }
                  | pragma          { $$ = $1; }
                  | block           { $$ = $1; }
                  | switchstmt      { $$ = $1; }
                  | usingdecl       { $$ = $1; }
                  | usingnamespacedecl { $$ = $1; }
                  | namespacealias  { $$ = $1; }
                  | macrocall       { $$ = new CppMacroCall($1, gCurProtLevel); }
                  | ';' /* blank statement */ { $$ = nullptr; }
                  ;

macrocall         : tknMacro
                  {
                    $$ = $1;
                  }
                  | macrocall '(' ')' {
                    $$ = mergeCppToken($1, $3);
                  }
                  | macrocall '(' expr ')' {
                    $$ = mergeCppToken($1, $4);
                    delete $3;
                  }
                  | macrocall ';' {
                    $$ = mergeCppToken($1, $2);
                  }
                  ;

switchstmt        : tknSwitch '(' expr ')' '{' caselist '}' {
                    $$ = new CppSwitchBlock($3, $6);
                  }
                  ;

caselist          : {
                    $$ = new CppSwitchBody;
                  }
                  | caselist tknCase expr ':' optstmtlist {
                    $$ = $1;
                    $$->emplace_back($3, $5);
                  }
                  | caselist tknDefault ':' optstmtlist {
                    $$ = $1;
                    $$->emplace_back(nullptr, $4);
                  }
                  ;

block             : '{' optstmtlist '}' {
                    $$ = $2 ? $2 : newCompound(kUnknownProt, kBlock);
                    $$->compoundType_ = kBlock;
                  }
                  | doccomment block {
                    $$ = $2;
                  }
                  ;

ifblock           : tknIf '(' expr ')' stmt {
                    $$ = new CppIfBlock($3);
                    $$->body_ = $5;
                  }
                  | ifblock tknElse stmt {
                    $$ = $1;
                    $$->else_ = $3;
                  }
                  ;

whileblock        : tknWhile '(' expr ')' stmt {
                    $$ = new CppWhileBlock($3);
                    $$->body_ = $5;
                  }
                  ;

dowhileblock      : tknDo stmt tknWhile '(' expr ')' {
                    $$ = new CppDoWhileBlock($5);
                    $$->body_ = $2;
                  }
                  ;

forblock          : tknFor '(' optexpr ';' optexpr ';' optexpr ')' stmt {
                    $$ = new CppForBlock($3, $5, $7, $9);
                  }
                  | tknFor '(' varinit ';' optexpr ';' optexpr ')' stmt {
                    $$ = new CppForBlock($3, $5, $7, $9);
                  }
                  ;

optexpr           : {
                    $$ = nullptr;
                  }
                  | expr {
                    $$ = $1;
                  }
                  ;

define            : tknPreProHash tknDefine tknID tknID         [ZZVALID;] {
                    $$ = new CppDefine($3, $4);
                    $$->defType_ = CppDefine::kRename;
                  }
                  | tknPreProHash tknDefine tknID               [ZZVALID;] {
                    $$ = new CppDefine($3);
                    $$->defType_ = CppDefine::kRename;
                  }
                  | tknPreProHash tknDefine tknID tknNumber     [ZZVALID;] {
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

hasherror         : tknPreProHash tknHashError [ZZVALID;] { $$ = new CppHashError($2); }
                  ;

pragma            : tknPreProHash tknPragma tknPreProDef        [ZZVALID;]  { $$ = new CppPragma($3); }
                  ;

doccomment        : doccommentstr  [ZZVALID;] { $$ = new CppDocComment((std::string) $1, gCurProtLevel); }
                  ;

doccommentstr     : tknDocBlockComment  [ZZVALID;] { $$ = $1; }
                  | tknDocLineComment   [ZZVALID;] { $$ = $1; }
                  | doccommentstr tknDocBlockComment [ZZVALID;] { $$ = mergeCppToken($1, $2); }
                  | doccommentstr tknDocLineComment  [ZZVALID;] { $$ = mergeCppToken($1, $2); }
                  ;

identifier        : tknID                                 { $$ = $1; }
                  | identifier tknScopeResOp identifier   { $$ = mergeCppToken($1, $3); }
                  | tknScopeResOp identifier %prec GLOBAL { $$ = mergeCppToken($1, $2); }
                  | templidentifier                       { $$ = $1; }
                  | tknOverride                           { $$ = $1; } /* override is not a reserved keyword */
                  | identifier tknEllipsis                { $$ = mergeCppToken($1, $2); }
                  ;

typeidentifier    : identifier                            { $$ = $1; }
                  | optnumsignspec tknLongLong            { $$ = mergeCppToken($1, $2); }
                  | optnumsignspec tknLong                { $$ = mergeCppToken($1, $2); }
                  | optnumsignspec tknInt                 { $$ = mergeCppToken($1, $2); }
                  | optnumsignspec tknShort               { $$ = mergeCppToken($1, $2); }
                  | optnumsignspec tknChar                { $$ = mergeCppToken($1, $2); }
                  | tknVoid                               { $$ = $1; }
                  | tknLong typeidentifier                { $$ = mergeCppToken($1, $2); }
                  | tknNumSignSpec                        { $$ = $1; }
                  | tknClass identifier [
                    if (gTemplateParamStart == $1.sz)
                      YYERROR;
                  ]                                       { $$ = mergeCppToken($1, $2); }
                  | tknStruct identifier                  { $$ = mergeCppToken($1, $2); }
                  | tknUnion identifier                   { $$ = mergeCppToken($1, $2); }
                  | tknEnum  identifier                   { $$ = mergeCppToken($1, $2); }
                  | tknTypename identifier  [
                    if (gTemplateParamStart == $1.sz)
                      YYERROR;
                  ]                                       { $$ = mergeCppToken($1, $2); }
                  | tknEllipsis                           { $$ = $1; }
                  | tknTypename tknEllipsis               { $$ = mergeCppToken($1, $2); }
                  | tknClass tknEllipsis                  { $$ = mergeCppToken($1, $2); }
                  | identifier tknEllipsis                { $$ = mergeCppToken($1, $2); }
                  ;

optnumsignspec    :                 { $$ = makeCppToken(nullptr, nullptr); }
                  | tknNumSignSpec  { $$ = $1; }
                  ;

templidentifier   : identifier '<' templatearglist '>' {
                    $$ = mergeCppToken($1, $4);
                  }
                  ;

optid             : { $$ = makeCppToken(nullptr, nullptr); }
                  | tknID      { $$ = $1; }
                  ;

enumitem          : tknID           { $$ = new CppEnumItem($1);     }
                  | tknID '=' expr  { $$ = new CppEnumItem($1, $3); }
                  | doccomment      { $$ = new CppEnumItem($1);     }
                  | hashif          { $$ = new CppEnumItem($1);     }
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
                  | tknEnum optapidecor tknID ':' typeidentifier '{' enumitemlist '}' ';'           [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $3, $7, false, $5);
                  };
                  | tknEnum optapidecor tknID '{' enumitemlist '}' ';'           [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $3, $5, false);
                  };
                  | tknEnum tknClass optapidecor tknID ':' typeidentifier '{' enumitemlist '}' ';'  [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $4, $8, true, $6);
                  }
                  | tknEnum tknClass optapidecor tknID '{' enumitemlist '}' ';'                 [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $4, $6, true);
                  }
                  | tknTypedef tknEnum optapidecor optid '{' enumitemlist '}' tknID ';'         [ZZVALID;] {
                    $$ = new CppEnum(gCurProtLevel, $8, $6);
                  }
                  ;

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

typedefnamestmt   : typedefname ';'     [ZZVALID;] { $$ = $1; }
                  ;

typedefliststmt   : typedeflist ';' [ZZVALID;] { $$ = $1; }
                  ;

typedeflist       : tknTypedef vardecllist { $$ = new CppTypedefList($2); }
                  ;

typedefname       : tknTypedef vardecl { $$ = new CppTypedefName($2); }
                  ;

usingdecl         : tknUsing tknID '=' vartype ';' {
                    $$ = new CppUsingDecl($2, $4);
                  }
                  | tknUsing tknID '=' functionpointer ';' {
                    $$ = new CppUsingDecl($2, $4);
                  }
                  | tknUsing tknID '=' classdefn ';' {
                    $$ = new CppUsingDecl($2, $4);
                  }
                  | templatespecifier usingdecl {
                    $$ = $2;
                    $$->templSpec_.reset($1);
                  }
                  | tknUsing identifier ';' {
                    $$ = new CppUsingDecl($2);
                  }
                  ;
                  ;

namespacealias    : tknNamespace tknID '=' identifier ';' {
                    $$ = new CppNamespaceAlias($2, $4);
                  }
                  ;

usingnamespacedecl: tknUsing tknNamespace identifier ';' {
                    $$ = new CppUsingNamespaceDecl($3);
                  }
                  ;

vardeclliststmt   : vardecllist ';' [ZZVALID;] { $$ = $1; }
                  ;

vardeclstmt       : vardecl ';'             [ZZVALID;] { $$ = $1; }
                  | varinit ';'             [ZZVALID;] { $$ = $1; }
                  | apidecor vardeclstmt    [ZZVALID;] { $$ = $2; $$->apidecor_ = $1; }
                  | exptype vardeclstmt     [ZZVALID;] { $$ = $2; $$->varType_->typeAttr_ |= $1; }
                  ;

vardecllist       : typeidentifier opttypemodifier tknID ',' opttypemodifier tknID {
                    $$ = new CppVarList($1);
                    $$->addVarDecl(CppVarDeclInList($2, {$3}));
                    $$->addVarDecl(CppVarDeclInList($5, {$6}));
                  }
                  | vardecllist ',' opttypemodifier tknID {
                    $$ = $1;
                    $$->addVarDecl(CppVarDeclInList($3, {$4}));
                  }
                  ;

varinit           : vardecl '(' typeidentifier '*' tknID      [gParamModPos = $4.sz; YYERROR;] { $$ = nullptr; } //FuncDeclHack
                  | vardecl '(' typeidentifier '*' '*' tknID  [gParamModPos = $4.sz; YYERROR;] { $$ = nullptr; } //FuncDeclHack
                  | vardecl '(' typeidentifier '*' '&' tknID  [gParamModPos = $4.sz; YYERROR;] { $$ = nullptr; } //FuncDeclHack
                  | vardecl '(' typeidentifier '&' tknID      [gParamModPos = $4.sz; YYERROR;] { $$ = nullptr; } //FuncDeclHack
                  | vardecl '(' typeidentifier tknAnd tknID   [gParamModPos = $4.sz; YYERROR;] { $$ = nullptr; } //FuncDeclHack
                  | vardecl '(' typeidentifier ')'            [gParamModPos = $3.sz; YYERROR;] { $$ = nullptr; } //FuncDeclHack
                  | vardecl '=' expr {
                    $$ = $1;
                    $$->varDecl_.assign_.reset($3);
                  }
                  | vardecl '(' expr ')' {
                    $$ = $1;
                    $$->varDecl_.constructFrom_.reset($3);
                  }
                  | vardecl '{' expr '}' {
                    $$ = $1;
                    $$->varDecl_.initializedFrom_.reset($3);
                  }
                  ;

vardecl           : vartype varidentifier {
                    $$ = new CppVar($1, $2.toString());
                  }
                  | vardecl '[' expr ']' {
                    $$ = $1;
                    $$->varDecl_.arraySizes_.push_back(std::unique_ptr<CppExpr>($3));
                  }
                  | vardecl '[' ']' {
                    $$ = $1;
                    $$->varDecl_.arraySizes_.push_back(nullptr);
                  }
                  | vardecl ':' expr {
                    $$ = $1;
                    $$->varDecl_.bitField_.reset($3);
                  }
                  ;

vartype           : typeidentifier opttypemodifier {
                    $$ = new CppVarType(gCurProtLevel, $1, $2);
                  }
                  | classdefn {
                    $$ = new CppVarType(gCurProtLevel, $1, CppTypeModifier());
                  }
                  | classdefn typemodifier {
                    $$ = new CppVarType(gCurProtLevel, $1, $2);
                  }
                  | varattrib vartype {
                    $$ = $2;
                    $$->typeAttr_ |= $1;
                  }
                  ;

varidentifier     : identifier                 { $$ = $1; }
                  | '(' '&' tknID ')'     { $$ = mergeCppToken($1, $4); }
                  | '(' '*' tknID ')'     { $$ = mergeCppToken($1, $4); }
                  | '(' '*' '*' tknID ')' { $$ = mergeCppToken($1, $5); }
                  ;

opttypemodifier   : { $$ = CppTypeModifier(); }
                  | typemodifier { $$ = $1; }
                  ;

typemodifier      : tknConst {
                    $$ = CppTypeModifier();
                    $$.constBits_ |= (1 << $$.ptrLevel_);
                  }
                  | '*' %prec PTRDECL {
                    $$ = CppTypeModifier();
                    $$.ptrLevel_++;
                  }
                  | '&' %prec REFDECL {
                    $$ = CppTypeModifier();
                    $$.refType_ = kByRef;
                  }
                  | tknAnd %prec REFDECL {
                    $$ = CppTypeModifier();
                    $$.refType_ = kRValRef;
                  }
                  | typemodifier tknConst {
                    $$ = $1;
                    $$.constBits_ |= (1 << $$.ptrLevel_);
                  }
                  | typemodifier '*' %prec PTRDECL {
                    $$ = $1;
                    $$.ptrLevel_++;
                  }
                  | typemodifier '&' %prec REFDECL {
                    $$ = $1;
                    $$.refType_ = kByRef;
                  }
                  | typemodifier tknAnd %prec REFDECL {
                    $$ = $1;
                    $$.refType_ = kRValRef;
                  }

                  ;

exptype           : tknStatic  { $$ = kStatic;  }
                  | tknExtern  { $$ = kExtern;  }
                  | tknExternC { $$ = kExternC; }
                  ;

varattrib         : tknConst    { $$ = kConst; }
                  | tknVolatile { $$ = kVolatile; }
                  | tknConstExpr{ $$ = kConstExpr; }
                  ;

typeconverter     : tknOperator vartype '(' optvoid ')' {
                    $$ = newTypeConverter($2, makeCppToken($1.sz, $3.sz));
                  }
                  | identifier tknScopeResOp tknOperator vartype '(' optvoid ')' {
                    $$ = newTypeConverter($4, makeCppToken($1.sz, $5.sz));
                  }
                  | functype typeconverter {
                    $$ = $2;
                    $$->attr_ = $1;
                  }
                  | typeconverter tknConst {
                    $$ = $1;
                    $$->attr_ |= kConst;
                  }
                  | apidecor typeconverter {
                    $$ = $2;
                    $$->docer1_ = $1;
                  }
                  | templatespecifier typeconverter {
                    $$ = $2;
                    $$->templSpec_.reset($1);
                  }
                  ;

typeconverterstmt : typeconverter ';' [ZZVALID;] {
                    $$ = $1;
                  }
                  | typeconverter block [ZZVALID;] {
                    $$ = $1;
                    $$->defn_ = $2;
                  }
                  ;

funcdeclstmt      : funcdecl ';' [ZZVALID;] { $$ = $1; }
                  ;

funcdefn          : funcdecl block [ZZVALID;] {
                    $$ = $1;
                    $$->defn_ = $2 ? $2 : newCompound(kUnknownProt, kBlock);
                  }
                  ;

functptrtype      : tknTypedef functionpointer ';' [ZZVALID;] {
                    $2->attr_ |= kTypedef;
                    $$ = $2;
                  }

functionpointer   : functype vartype '(' optapidecor identifier tknScopeResOp '*' optid ')' '(' paramlist ')' {
                    $$ = new CppFunctionPtr(gCurProtLevel, $8, $2, $11, $1);
                    $$->docer2_ = $4;
                    $$->ownerName_ = mergeCppToken($5, $6);
                  }
                  | vartype '(' optapidecor identifier tknScopeResOp '*' optid ')' '(' paramlist ')' {
                    $$ = new CppFunctionPtr(gCurProtLevel, $7, $1, $10, 0);
                    $$->docer2_ = $3;
                    $$->ownerName_ = mergeCppToken($4, $5);
                  }
                  | functype vartype '(' optapidecor '*' optid ')' '(' paramlist ')' {
                    $$ = new CppFunctionPtr(gCurProtLevel, $6, $2, $9, $1);
                    $$->docer2_ = $4;
                  }
                  | vartype '(' optapidecor '*' optid ')' '(' paramlist ')' {
                    $$ = new CppFunctionPtr(gCurProtLevel, $5, $1, $8, 0);
                    $$->docer2_ = $3;
                  }
                  | apidecor functionpointer {
                    $$ = $2;
                    $$->docer1_ = $1;
                  }
                  | functionpointer optfuncattrib {
                    $$ = $1;
                    $$->attr_ |= $2;
                  }
                  ;

funcpointerdecl   : functionpointer ';' [ZZVALID;] { $$ = $1;}
                  ;

funcdecl          : vartype apidecor funcname '(' paramlist ')' {
                    $$ = newFunction(gCurProtLevel, $3, $1, $5, 0);
                    $$->docer2_ = $2;
                  }
                  | vartype funcname '(' paramlist ')' {
                    $$ = newFunction(gCurProtLevel, $2, $1, $4, 0);
                  }
                  | apidecor funcdecl {
                    $$ = $2;
                    if (!$$->docer1_.empty())
                      std::swap($$->docer1_, $$->docer2_);
                    $$->docer1_ = $1;
                  }
                  | templatespecifier funcdecl {
                    $$ = $2;
                    $$->templSpec_.reset($1);
                  }
                  | functype funcdecl {
                    $$ = $2;
                    $$->attr_ |= $1;
                  }
                  | funcdecl '=' tknDelete {
                    $$ = $1;
                    $$->attr_ |= kDelete;
                  }
                  | funcdecl '=' tknDefault {
                    $$ = $1;
                    $$->attr_ |= kDefault;
                  }
                  | funcdecl functhrowspec {
                    $$ = $1;
                    $$->throwSpec_ = $2;
                  }
                  | funcdecl optfuncattrib {
                    $$ = $1;
                    $$->attr_ |= $2;
                  }
                  ;

funcname          : operfuncname { $$ = $1; }
                  | identifier   { $$ = $1; }
                  | tknScopeResOp operfuncname { $$ = mergeCppToken($1, $2); }
                  | identifier tknScopeResOp operfuncname { $$ = mergeCppToken($1, $3); }
                  ;

operfuncname      : tknOperator '+' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '-' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '*' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '/' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '%' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '^' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '&' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '|' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '~' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '!' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '=' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '<' { $$ = mergeCppToken($1, $2); }
                  | tknOperator '>' { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknPlusEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknMinusEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknMulEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknDivEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknPerEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknXorEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknAndEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknOrEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknLShift { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknRShift { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknLShiftEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknRShiftEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknCmpEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknNotEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknLessEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknGreaterEq { $$ = mergeCppToken($1, $2); }
                  | tknOperator tkn3WayCmp { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknAnd { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknOr { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknInc { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknDec { $$ = mergeCppToken($1, $2); }
                  | tknOperator ',' { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknArrow { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknArrowStar { $$ = mergeCppToken($1, $2); }
                  | tknOperator '(' ')' { $$ = mergeCppToken($1, $3); }
                  | tknOperator '[' ']' { $$ = mergeCppToken($1, $3); }
                  | tknOperator tknNew { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknNew '[' ']' { $$ = mergeCppToken($1, $4); }
                  | tknOperator tknDelete { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknDelete '[' ']' { $$ = mergeCppToken($1, $4); }
                  ;

paramlist         : { $$ = new CppParamList; }
                  | param {
                    $$ = new CppParamList;
                    $$->push_back($1);
                  }
                  | paramlist ',' param {
                    $1->push_back($3);
                    $$ = $1;
                  }
                  ;

param             : varinit                 { $$ = $1; $1->varType_->typeAttr_ |= kFuncParam;  }
                  | vartype '=' expr        {
                    auto var = new CppVar($1, std::string());
                    var->varType_->typeAttr_ |= kFuncParam;
                    var->varDecl_.assign_.reset($3);
                    $$ = var;
                  }
                  | vardecl                 { $$ = $1; $1->varType_->typeAttr_ |= kFuncParam;  }
                  | vartype                 {
                    auto var = new CppVar($1, std::string());
                    var->varType_->typeAttr_ |= kFuncParam;
                    $$ = var;
                  }
                  | functionpointer         { $$ = $1; $1->attr_ |= kFuncParam;     }
                  | doccomment param        { $$ = $2; }
                  | vartype '[' expr ']' {
                    auto var = new CppVar($1, std::string());
                    var->varType_->typeAttr_ |= kFuncParam;
                    var->varDecl_.arraySizes_.push_back(std::unique_ptr<CppExpr>($3));
                    $$ = var;
                  }
                  | vartype '[' ']' {
                    auto var = new CppVar($1, std::string());
                    var->varType_->typeAttr_ |= kFuncParam;
                    var->varDecl_.arraySizes_.push_back(std::unique_ptr<CppExpr>(nullptr));
                    $$ = var;
                  }
                  ;

templatearg       :                               { $$ = makeCppToken(nullptr, nullptr); }
                  | typeidentifier                { $$ = $1; }
                  | tknConst templatearg          { $$ = mergeCppToken($1, $2); }
                  | templatearg tknConst          { $$ = mergeCppToken($1, $2); }
                  | tknNumber                     { $$ = $1; }
                  | templatearg '*'               {
                    auto p = $1.sz + $1.len;
                    while (*p && (*p != '*'))
                      ++p;
                    if (*p == '*')
                      ++p;
                    $$ = makeCppToken($1.sz, p - $1.sz);
                  }
                  | typeidentifier '=' identifier { $$ = $1; /* TODO: use 'identifier' too */ }
                  ;

templatearglist   : templatearg { $$ = $1; }
                  | templatearglist ',' templatearg  { $$ = mergeCppToken($1, $3); }
                  ;

optfunctype       : {
                    $$ = 0;
                  }
                  | functype {
                    $$ = $1;
                  }
                  ;

/* Although not all combinations are valid but we don't care. */
functype          : optfunctype tknStatic      { $$ = $1 | kStatic;    }
                  | optfunctype tknInline      { $$ = $1 | kInline;    }
                  | optfunctype tknVirtual     { $$ = $1 | kVirtual;   }
                  | optfunctype tknExtern      { $$ = $1 | kExtern;    }
                  | optfunctype tknExternC     { $$ = $1 | kExternC;   }
                  | optfunctype tknExplicit    { $$ = $1 | kExplicit;  }
                  | optfunctype tknFriend      { $$ = $1 | kFriend;    }
                  ;

optfuncattrib     : tknConst       { $$ = kConst; }
                  | tknOverride    { $$ = kOverride; }
                  | tknFinal       { $$ = kFinal; }
                  | tknNoExcept    { $$ = kNoExcept; }
                  | '=' tknNumber  [if($2.len != 1 || $2.sz[0] != '0') YYABORT; else ZZVALID;]
                                                  { $$ = kPureVirtual; }
                  | optfuncattrib tknConst        { $$ = $1 | kConst; }
                  | optfuncattrib tknOverride     { $$ = $1 | kOverride; }
                  | optfuncattrib tknFinal        { $$ = $1 | kFinal; }
                  | optfuncattrib tknNoExcept     { $$ = $1 | kNoExcept; }
                  | optfuncattrib '=' tknNumber  [if($3.len != 1 || $3.sz[0] != '0') YYABORT; else ZZVALID;]
                                                  { $$ = $1 | kPureVirtual; }
                  ;

optfuncthrowspec  : { $$ = nullptr; }
                  | functhrowspec { $$ = $1; }
                  ;

functhrowspec     : tknThrow '(' identifierlist ')' {
                    $$ = $3 ? $3 : new CppFuncThrowSpec;
                  }
                  ;

identifierlist    : { $$ = nullptr; }
                  | identifier {
                    $$ = new CppIdentifierList;
                    $$->push_back($1);
                  }
                  | identifierlist ',' identifier {
                    $$ = $1;
                    $$->push_back($3);
                  }
                  ;

ctordeclstmt      : ctordecl';' [ZZVALID;] { $$ = $1; }
                  ;

ctordefn          : ctordecl meminitlist block [ZZVALID;]
                  {
                    $$ = $1;
                    $$->memInitList_  = $2;
                    $$->defn_      = $3;
                  }
                  | tknID tknScopeResOp tknID [if($1 != $3) YYERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
                  {
                    $$ = newConstructor(gCurProtLevel, mergeCppToken($1, $3), $6, $9, 0);
                    $$->defn_      = $10;
                    $$->throwSpec_ = $8;
                  }
                  | identifier tknScopeResOp tknID tknScopeResOp tknID [if($3 != $5) YYERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
                  {
                    $$ = newConstructor(gCurProtLevel, mergeCppToken($1, $5), $8, $11, 0);
                    $$->defn_      = $12;
                    $$->throwSpec_ = $10;
                  }
                  | tknID '<' templatearglist '>' tknScopeResOp tknID [if($1 != $6) YYERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
                  {
                    $$ = newConstructor(gCurProtLevel, mergeCppToken($1, $6), $9, $12, 0);
                    $$->defn_      = $13;
                    $$->throwSpec_ = $11;
                  }
                  | functype ctordefn {
                    $$ = $2;
                    $$->attr_ |= $1;
                  }
                  | templatespecifier ctordefn {
                    $$ = $2;
                    $$->templSpec_.reset($1);
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
                  | functype ctordecl {
                    $$ = $2;
                    $$->attr_ |= $1;
                  }
                  | templatespecifier ctordecl {
                    $$ = $2;
                    $$->templSpec_.reset($1);
                  }
                  | ctordecl '=' tknDelete {
                    $$ = $1;
                    $$->attr_ |= kDelete;
                  }
                  | ctordecl '=' tknDefault {
                    $$ = $1;
                    $$->attr_ |= kDefault;
                  }
                  | ctordecl functhrowspec {
                    $$ = $1;
                    $$->throwSpec_ = $2;
                  }
                  | apidecor ctordecl {
                    $$ = $2;
                    $$->docer1_ = $1;
                  }
                  ;

meminitlist       : { $$ = nullptr; }
                  | ':' meminit                 { $$ = new CppMemInitList; $$->push_back(CppMemInit($2.mem, $2.init)); }
                  | meminitlist ',' meminit     { $$ = $1; $$->push_back(CppMemInit($3.mem, $3.init)); }
                  ;

meminit           : identifier '(' expr ')' { $$ = CppNtMemInit{$1, $3}; }
                  | identifier '(' ')'          { $$ = CppNtMemInit{$1, nullptr}; }
                  ;

dtordeclstmt      : dtordecl ';' [ZZVALID;] { $$ = $1; }
                  ;

dtordefn          : dtordecl block [ZZVALID;]
                  {
                    $$ = $1;
                    $$->defn_ = $2 ? $2 : newCompound(kUnknownProt, kBlock);
                  }
                  | tknID tknScopeResOp '~' tknID [if($1 != $4) YYERROR; else ZZVALID;]
                    '(' ')' block
                  {
                    $$ = newDestructor(gCurProtLevel, mergeCppToken($1, $4), 0);
                    $$->defn_      = $8 ? $8 : newCompound(kUnknownProt, kBlock);
                  }
                  | identifier tknScopeResOp tknID tknScopeResOp '~' tknID [if($3 != $6) YYERROR; else ZZVALID;]
                    '(' ')' block
                  {
                    $$ = newDestructor(gCurProtLevel, mergeCppToken($1, $6), 0);
                    $$->defn_      = $10 ? $10 : newCompound(kUnknownProt, kBlock);
                  }
                  | tknID '<' templatearglist '>' tknScopeResOp '~' tknID [if($1 != $7) YYERROR; else ZZVALID;]
                    '(' ')' block
                  {
                    $$ = newDestructor(gCurProtLevel, mergeCppToken($1, $7), 0);
                    $$->defn_      = $11 ? $11 : newCompound(kUnknownProt, kBlock);
                  }
                  | templatespecifier dtordefn {
                    $$ = $2;
                    $$->templSpec_.reset($1);
                  }
                  | functype dtordefn {
                    $$ = $2;
                    $$->attr_ |= $1;
                  }
                  ;

dtordecl          : '~' tknID '(' optvoid ')' %prec DTORDECL
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
                  | apidecor dtordecl {
                    $$ = $2;
                    $$->docer1_ = $1;
                  }
                  | functype dtordecl {
                    $$ = $2;
                    $$->attr_ |= $1;
                  }
                  | dtordecl '=' tknNumber
                  {
                    $$ = $1;
                    $$->attr_ |= kPureVirtual;
                  }
                  | dtordecl '=' tknDelete {
                    $$ = $1;
                    $$->attr_ |= kDelete;
                  }
                  | dtordecl '=' tknDefault {
                    $$ = $1;
                    $$->attr_ |= kDefault;
                  }
                  | dtordecl functhrowspec {
                    $$ = $1;
                    $$->throwSpec_ = $2;
                  }
                  ;

optvoid           :
                  | tknVoid
                  ;

optcomment        : {
                  }
                  | doccomment [ZZVALID;] {
                  }
                  ;

classdefnstmt     : classdefn ';' [ZZVALID;] { $$ = $1;}
                  | classdefn
                      [
                        if ($1->compoundType_ == kNamespace)
                          ZZVALID;
                      ]
                      {
                        $$ = $1;
                      }
                  ;

classdefn         : compoundSpecifier optapidecor identifier optinheritlist optcomment '{'
                  [
                    ZZVALID;
                    gCompoundStack.push(classNameFromIdentifier($3));
                  ]
                  {
                    gProtLevelStack.push(gCurProtLevel); gCurProtLevel = kUnknownProt;
                  }
                  optstmtlist '}'
                  [
                    ZZVALID;
                    gCompoundStack.pop();
                  ]
                  {
                    gCurProtLevel = gProtLevelStack.top();
                    gProtLevelStack.pop();

                    $$ = $8 ? $8 : newCompound(gCurProtLevel);
                    $$->compoundType_  = $1;
                    $$->apidecor_    = $2;
                    $$->name_      = $3;
                    $$->inheritList_  = $4;
                  }
                  | compoundSpecifier optinheritlist optcomment
                    '{' { gProtLevelStack.push(gCurProtLevel); gCurProtLevel = kUnknownProt; }
                      optstmtlist
                    '}' [ZZVALID;]
                  {
                    gCurProtLevel = gProtLevelStack.top();
                    gProtLevelStack.pop();

                    $$ = $6 ? $6 : newCompound(gCurProtLevel);
                    $$->compoundType_  = $1;
                    $$->inheritList_  = $2;
                  }
                  | templatespecifier classdefn
                  {
                    $$ = $2;
                    $$->templSpec_.reset($1);
                  }
                  ;

optinheritlist    : { $$ = 0; }
                  | ':' protlevel identifier [ZZVALID;]        { $$ = new CppInheritanceList; $$->push_back(CppInheritInfo((std::string) $3, $2)); }
                  | optinheritlist ',' protlevel identifier [ZZVALID;]  { $$ = $1; $$->push_back(CppInheritInfo((std::string) $4, $3)); }
                  ;

protlevel         :        { $$ = kUnknownProt;}
                  | tknPublic    { $$ = kPublic;    }
                  | tknProtected  { $$ = kProtected;  }
                  | tknPrivate  { $$ = kPrivate;  }
                  ;

fwddecl           : compoundSpecifier identifier ';' [ZZVALID;] { $$ = new CppFwdClsDecl(gCurProtLevel, $2, $1); }
                  | compoundSpecifier optapidecor identifier ';' [ZZVALID;] { $$ = new CppFwdClsDecl(gCurProtLevel, $3, $1); }
                  | templatespecifier fwddecl {
                    $$ = $2;
                    $$->templSpec_.reset($1);
                  }
                  | tknFriend identifier ';' [ZZVALID;] { $$ = new CppFwdClsDecl(gCurProtLevel, $2); }
                  | tknFriend fwddecl [ZZVALID;]  { $$ = $2; $$->attr_ = kFriend; }
                  ;

compoundSpecifier : tknClass    { $$ = kClass;    }
                  | tknStruct    { $$ = kStruct;    }
                  | tknUnion    { $$ = kUnion;    }
                  | tknNamespace  { $$ = kNamespace;  }
                  ;

templatespecifier : tknTemplate '<' [gInTemplateSpec = true;] templateparamlist '>' [gInTemplateSpec = false;] {
                    $$ = $4;
                  }
                  ;

templateparamlist : {
                    $$ = new CppTemplateParamList;
                  }
                  | templateparam {
                    $$ = new CppTemplateParamList;
                    $$->emplace_back($1);
                  }
                  | templateparamlist ',' templateparam {
                    $$ = $1;
                    $$->emplace_back($3);
                  }
                  ;

templateparam     : tknTypename tknID {
                    $$ = new CppTemplateParam(nullptr, $2);
                  }
                  | tknTypename tknID '=' vartype {
                    $$ = new CppTemplateParam(nullptr, $2);
                    $$->setDefaultParam($4);
                  }
                  | tknClass tknID {
                    $$ = new CppTemplateParam(nullptr, $2);
                  }
                  | tknClass tknID '=' vartype {
                    $$ = new CppTemplateParam(nullptr, $2);
                    $$->setDefaultParam($4);
                  }
                  | vartype tknID {
                    $$ = new CppTemplateParam($1, $2);
                  }
                  | vartype tknID '=' expr {
                    $$ = new CppTemplateParam($1, $2);
                    $$->setDefaultParam($4);
                  }
                  | vartype { // Can happen when forward declaring
                    $$ = new CppTemplateParam($1, std::string());
                  }
                  | vartype '=' expr { // Can happen when forward declaring
                    $$ = new CppTemplateParam($1, std::string());
                    $$->setDefaultParam($3);
                  }
                  // <TemplateParamHack>
                  | tknTypename tknID ',' [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    YYERROR;
                  ] { $$ = nullptr; }
                  | tknTypename tknID '>' [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    YYERROR;
                  ] { $$ = nullptr; }
                  | tknClass tknID ',' [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    YYERROR;
                  ] { $$ = nullptr; }
                  | tknClass tknID '>' [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    YYERROR;
                  ] { $$ = nullptr; }
                  // </TemplateParamHack>
                  ;

optapidecor       :                     { $$ = makeCppToken(nullptr, nullptr); }
                  | apidecor            { $$ = $1; }
                  ;

apidecor          : tknApiDecor         { $$ = $1; }
                  | apidecor tknApiDecor{ $$ = mergeCppToken($1, $2); }
                  | tknID '(' tknID ')' { $$ = mergeCppToken($1, $4); }
                  | tknID               { $$ = $1; }
                  ;

changeprotlevel   : tknPublic     ':'  [ZZVALID;] { $$ = kPublic;     }
                  | tknProtected  ':'  [ZZVALID;] { $$ = kProtected;  }
                  | tknPrivate    ':'  [ZZVALID;] { $$ = kPrivate;    }
                  ;

externcblock      : tknExternC block [ZZVALID;] {$$ = $2; $$->compoundType_ = kExternCBlock; }
                  ;

expr              : tknStrLit                                                 { $$ = new CppExpr((std::string) $1, kNone);          }
                  | tknCharLit                                                { $$ = new CppExpr((std::string) $1, kNone);          }
                  | tknNumber                                                 { $$ = new CppExpr((std::string) $1, kNone);          }
                  | funcname [ if ($1.sz == gParamModPos) YYERROR; ]          { $$ = new CppExpr((std::string) $1, kNone);          }
                  | '{' expr '}'                                              { $$ = new CppExpr($2, CppExpr::kInitializer);        }
                  | '{' /*empty expr*/ '}'                                    { $$ = new CppExpr((CppExpr*)nullptr, CppExpr::kInitializer);   }
                  | '-' expr %prec UNARYMINUS                                 { $$ = new CppExpr($2, kUnaryMinus);                  }
                  | '~' expr                                                  { $$ = new CppExpr($2, kBitToggle);                   }
                  | '!' expr                                                  { $$ = new CppExpr($2, kLogNot);                      }
                  | '*' expr %prec DEREF                                      { $$ = new CppExpr($2, kDerefer);                     }
                  | '&' expr %prec ADDRESSOF                                  { $$ = new CppExpr($2, kRefer);                       }
                  | tknInc expr  %prec PREINCR                                { $$ = new CppExpr($2, kPreIncrement);                }
                  | expr tknInc  %prec POSTINCR                               { $$ = new CppExpr($1, kPostIncrement);               }
                  | tknDec expr  %prec PREDECR                                { $$ = new CppExpr($2, kPreDecrement);                }
                  | expr tknDec  %prec POSTDECR                               { $$ = new CppExpr($1, kPostDecrement);               }
                  | expr '+' expr                                             { $$ = new CppExpr($1, kPlus, $3);                    }
                  | expr '-' expr                                             { $$ = new CppExpr($1, kMinus, $3);                   }
                  | expr '*' expr [ if ($2.sz == gParamModPos) YYERROR; ]     { $$ = new CppExpr($1, kMul, $3);                     }
                  | expr '/' expr                                             { $$ = new CppExpr($1, kDiv, $3);                     }
                  | expr '%' expr                                             { $$ = new CppExpr($1, kPercent, $3);                 }
                  | expr '&' expr [ if ($2.sz == gParamModPos) YYERROR; ]     { $$ = new CppExpr($1, kBitAnd, $3);                  }
                  | expr '|' expr                                             { $$ = new CppExpr($1, kBitOr, $3);                   }
                  | expr '^' expr                                             { $$ = new CppExpr($1, kXor, $3);                     }
                  | expr '=' expr                                             { $$ = new CppExpr($1, kEqual, $3);                   }
                  | expr '<' expr                                             { $$ = new CppExpr($1, kLess, $3);                    }
                  | expr '>' expr                                             { $$ = new CppExpr($1, kGreater, $3);                 }
                  | expr '?' expr ':' expr %prec TERNARYCOND                  { $$ = new CppExpr($1, $3, $5);                       }
                  | expr tknPlusEq expr                                       { $$ = new CppExpr($1, kPlusEqual, $3);               }
                  | expr tknMinusEq expr                                      { $$ = new CppExpr($1, kMinusEqual, $3);              }
                  | expr tknMulEq expr                                        { $$ = new CppExpr($1, kMulEqual, $3);                }
                  | expr tknDivEq expr                                        { $$ = new CppExpr($1, kDivEqual, $3);                }
                  | expr tknPerEq expr                                        { $$ = new CppExpr($1, kPerEqual, $3);                }
                  | expr tknXorEq expr                                        { $$ = new CppExpr($1, kXorEqual, $3);                }
                  | expr tknAndEq expr                                        { $$ = new CppExpr($1, kAndEqual, $3);                }
                  | expr tknOrEq expr                                         { $$ = new CppExpr($1, kOrEqual, $3);                 }
                  | expr tknLShift expr                                       { $$ = new CppExpr($1, kLeftShift, $3);               }
                  | expr tknRShift expr                                       { $$ = new CppExpr($1, kRightShift, $3);              }
                  | expr tknLShiftEq expr                                     { $$ = new CppExpr($1, kLShiftEqual, $3);             }
                  | expr tknRShiftEq expr                                     { $$ = new CppExpr($1, kRShiftEqual, $3);             }
                  | expr tknCmpEq expr                                        { $$ = new CppExpr($1, kCmpEqual, $3);                }
                  | expr tknNotEq expr                                        { $$ = new CppExpr($1, kNotEqual, $3);                }
                  | expr tknLessEq expr                                       { $$ = new CppExpr($1, kLessEqual, $3);               }
                  | expr tknGreaterEq expr                                    { $$ = new CppExpr($1, kGreaterEqual, $3);            }
                  | expr tkn3WayCmp expr                                      { $$ = new CppExpr($1, k3WayCmp, $3);                 }
                  | expr tknAnd expr  [ if ($2.sz == gParamModPos) YYERROR; ] { $$ = new CppExpr($1, kAnd, $3);                     }
                  | expr tknOr expr                                           { $$ = new CppExpr($1, kOr, $3);                      }
                  | expr ',' expr                                             { $$ = new CppExpr($1, kComma, $3);                   }
                  | expr '.' expr                                             { $$ = new CppExpr($1, kDot, $3);                     }
                  | expr tknArrow expr                                        { $$ = new CppExpr($1, kArrow, $3);                   }
                  | expr tknArrowStar expr                                    { $$ = new CppExpr($1, kArrowStar, $3);               }
                  | expr '[' expr ']' %prec SUBSCRIPT                         { $$ = new CppExpr($1, kArrayElem, $3);               }
                  | expr '(' ')' %prec FUNCCALL                               { $$ = new CppExpr($1, kFunctionCall);                }
                  | expr '(' expr ')' %prec FUNCCALL                          { $$ = new CppExpr($1, kFunctionCall, $3);            }
                  | '(' vartype ')' expr %prec CSTYLECAST                     { $$ = new CppExpr($2, kCStyleCast, $4);              }
                  | tknConstCast '<' vartype '>' '(' expr ')'                 { $$ = new CppExpr($3, kConstCast, $6);               }
                  | tknStaticCast '<' vartype '>' '(' expr ')'                { $$ = new CppExpr($3, kStaticCast, $6);              }
                  | tknDynamicCast '<' vartype '>' '(' expr ')'               { $$ = new CppExpr($3, kDynamicCast, $6);             }
                  | tknReinterpretCast '<' vartype '>' '(' expr ')'           { $$ = new CppExpr($3, kReinterpretCast, $6);         }
                  | '(' expr ')'                                              { $$ = $2; $2->flags_ |= CppExpr::kBracketed;         }
                  | tknNew typeidentifier                                     { $$ = new CppExpr((std::string) $2, CppExpr::kNew);  }
                  | tknNew '(' expr ')' expr %prec tknNew                     { $$ = new CppExpr($3, kPlacementNew, $5);            }
                  | tknScopeResOp tknNew '(' expr ')' expr %prec tknNew       { $$ = new CppExpr($4, kPlacementNew, $6);            }
                  | tknDelete  expr                                           { $$ = $2; $2->flags_ |= CppExpr::kDelete;            }
                  | tknDelete  '[' ']' expr %prec tknDelete                   { $$ = $4; $4->flags_ |= CppExpr::kDeleteArray;       }
                  | tknReturn  expr                                           { $$ = $2; $2->flags_ |= CppExpr::kReturn;            }
                  | tknReturn                                                 { $$ = new CppExpr(CppExprAtom(), CppExpr::kReturn);  }
                  | tknThrow  expr                                            { $$ = $2; $2->flags_ |= CppExpr::kThrow;             }
                  | tknThrow                                                  { $$ = new CppExpr(CppExprAtom(), CppExpr::kThrow);   }
                  | tknSizeOf '(' vartype ')'                                 { $$ = new CppExpr($3, CppExpr::kSizeOf);             }
                  | tknSizeOf '(' expr ')'                                    { $$ = new CppExpr($3, CppExpr::kSizeOf);             }
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
  gCurProtLevel = kUnknownProt;
  
  void setupScanBuffer(char* buf, size_t bufsize);
  void cleanupScanBuffer();
  setupScanBuffer(stm, stmSize);
  gLineNo = 1; // Reset so that we do not start counting beyond previous parsing.
  gTemplateParamStart = nullptr;
  gParamModPos = nullptr;
  yyparse();
  cleanupScanBuffer();
  CppCompoundStack tmpStack;
  gCompoundStack.swap(tmpStack);
  
  return gProgUnit;
}
