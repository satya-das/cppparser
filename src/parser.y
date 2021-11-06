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

/*
  TODOs:
    (1) Parsing of following needs improvements/support:
      (a) Imp: Function pointer
      (b) Sup: Reference to array
      (c) Sup: Pointer to array
      Need to borrow ideas from https://www.nongnu.org/hcb/
        and may be http://www.computing.surrey.ac.uk/research/dsrg/fog/CxxGrammar.y too can help.

*/

%{
#include "cpptoken.h"
#include "cppast.h"
#include "cppvarinit.h"
#include "parser.tab.h"
#include "parser.l.h"
#include "cppobjfactory.h"
#include "obj-factory-helper.h"
#include "utils.h"

#include <iostream>
#include <stack>
#include <map>

//////////////////////////////////////////////////////////////////////////

int GetKeywordId(const std::string& keyword) {
  static const std::map<std::string, int> keywordToIdMap =
  {
      {"virtual",   tknVirtual},
      {"final",     tknFinal},
      {"override",  tknOverride},
      {"const",     tknConst},
      {"noexcept",  tknNoExcept}
  };

  auto itr = keywordToIdMap.find(keyword);
  return (itr != keywordToIdMap.end()) ? itr->second : -1;
}

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

static int gParseLog = 0;

#define ZZLOG               \
  {                         \
  if (gParseLog)                 \
    printf("ZZLOG @line#%d, parsing stream line#%d\n", __LINE__, g.mLineNo); \
}

static int gDisableYyValid = 0;

#define ZZVALID   {         \
  if (gParseLog)                 \
    printf("ZZVALID: ");    \
  ZZLOG;                    \
  if (!gDisableYyValid)     \
    YYVALID;                \
  }

#define ZZERROR             \
  do {                      \
    if (gParseLog)               \
      printf("ZZERROR: ");  \
    ZZLOG;                  \
    YYERROR;                \
  } while(0)

#define ZZVALID_DISABLE     \
  ++gDisableYyValid;

#define ZZVALID_ENABLE      \
  --gDisableYyValid;


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
using CppCompoundStack = std::stack<CppToken>;

static CppCompoundStack             gCompoundStack;
static CppAccessType                gCurAccessType;
static std::stack<CppAccessType>    gAccessTypeStack;

/** {End of Globals} */

#define YYPOSN char*

extern int yylex();

// Yacc generated code causes warnings that need suppression.
// This pragma should be at the end.
#if defined(__clang__) || defined(__GNUC__)
# pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

%}

%union {
  CppToken                str;
  CppNtFuncDeclData       funcDeclData;
  CppNtMemInit            memInit;

  CppObj*                 cppObj;
  CppTypeModifier         typeModifier;
  CppVarType*             cppVarType;
  CppVar*                 cppVarObj;
  CppEnum*                cppEnum;
  CppEnumItem*            enumItem;
  CppEnumItemList*        enumItemList;
  CppTypedefName*         typedefName;
  CppTypedefList*         typedefList;
  CppUsingDecl*           usingDecl;
  CppUsingNamespaceDecl*  usingNamespaceDecl;
  CppNamespaceAlias*      namespaceAlias;
  CppCompound*            cppCompundObj;
  CppTemplateParam*       templateParam;
  CppTemplateParamList*   templateParamList;
  CppDocComment*          docCommentObj;
  CppFwdClsDecl*          fwdDeclObj;
  CppVarList*             cppVarObjList;
  CppVarAssign            cppVarAssign;
  CppUnRecogPrePro*       unRecogPreProObj;
  CppExpr*                cppExprObj;
  CppLambda*              cppLambda;
  CppFunction*            cppFuncObj;
  CppFunctionPointer*     cppFuncPointerObj;
  CppObj*                 varOrFuncPtr;
  CppParamVector*         paramList;
  CppConstructor*         cppCtorObj;
  CppDestructor*          cppDtorObj;
  CppTypeConverter*       cppTypeConverter;
  CppMemInits          memInitList;
  CppInheritanceList*     inheritList;
  bool                    inheritType;
  CppIdentifierList*      identifierList;
  CppFuncThrowSpec*       funcThrowSpec;
  CppTemplateArg*         templateArg;
  CppAsmBlock*            asmBlock;
  CppCompoundType         compoundType;
  unsigned short          ptrLevel;
  CppRefType              refType;
  unsigned int            attr;
  CppAccessType           objAccessType;

  CppIfBlock*             ifBlock;
  CppWhileBlock*          whileBlock;
  CppDoWhileBlock*        doWhileBlock;
  CppForBlock*            forBlock;
  CppRangeForBlock*       forRangeBlock;
  CppSwitchBlock*         switchBlock;
  CppSwitchBody*          switchBody;
  CppTryBlock*            tryBlock;
  CppCatchBlock*          catchBlock;

  CppDefine*              hashDefine;
  CppUndef*               hashUndef;
  CppInclude*             hashInclude;
  CppImport*              hashImport;
  CppHashIf*              hashIf;
  CppHashError*           hashError;
  CppHashWarning*         hashWarning;
  CppPragma*              hashPragma;

  CppBlob*                blob;
}

%token  <str>   tknName tknID tknStrLit tknCharLit tknNumber tknMacro tknApiDecor
%token  <str>   tknTypedef tknUsing
%token  <str>   tknInteger tknChar tknDouble tknFloat
%token  <str>   tknEnum
%token  <str>   tknAuto
%token  <str>   tknPreProDef
%token  <str>   tknClass tknStruct tknUnion tknNamespace
%token  <str>   tknTemplate tknTypename tknDecltype
%token  <str>   tknFreeStandingBlockComment tknSideBlockComment tknFreeStandingLineComment tknSideLineComment
%token  <str>   tknScopeResOp
%token  <str>   tknNumSignSpec // signed/unsigned
%token  <str>   tknPublic tknProtected tknPrivate
%token  <str>   tknExternC
%token  <str>   tknUnRecogPrePro
%token  <str>   tknStdHdrInclude
%token  <str>   tknPragma tknHashError tknHashWarning
%token  <str>   tknEllipsis
%token  <str>   tknConstCast tknStaticCast tknDynamicCast tknReinterpretCast
%token  <str>   tknTry tknCatch tknThrow tknSizeOf
%token  <str>   tknOperator tknPlusEq tknMinusEq tknMulEq tknDivEq tknPerEq tknXorEq tknAndEq tknOrEq
%token  <str>   tknLShift /*tknRShift*/ tknLShiftEq tknRShiftEq tknCmpEq tknNotEq tknLessEq tknGreaterEq
%token  <str>   tkn3WayCmp tknAnd tknOr tknInc tknDec tknArrow tknArrowStar
%token  <str>   tknLT tknGT // We will need the position of these operators in stream when used for declaring template instance.
%token  <str>   '+' '-' '*' '/' '%' '^' '&' '|' '~' '!' '=' ',' '(' ')' '[' ']' ';'
%token  <str>   tknNew tknDelete
%token  <str>   tknConst tknConstExpr // For templatearg parsing it is made as str type.
%token  <str>   tknVoid // For the cases when void is used as function parameter.
%token  <str>   tknOverride tknFinal // override, final are not a reserved keywords
%token  <str>   tknAsm
%token  <str>   tknBlob

%token  tknStatic tknExtern tknVirtual tknInline tknExplicit tknFriend tknVolatile tknMutable tknNoExcept

%token  tknPreProHash /* When # is encountered for pre processor definition */
%token  tknDefine tknUndef
%token  tknInclude tknImport
%token  tknIf tknIfDef tknIfNDef tknElse tknElIf tknEndIf
%token  tknFor tknWhile tknDo tknSwitch tknCase tknDefault
%token  tknReturn

%token  tknBlankLine

%type  <str>                strlit
%type  <str>                optapidecor apidecor apidecortokensq
%type  <str>                identifier numbertype typeidentifier varidentifier optname id name operfuncname funcname
%type  <str>                templidentifier templqualifiedid
%type  <str>                doccommentstr
%type  <str>                rshift
%type  <str>                macrocall
%type  <cppObj>             stmt
%type  <typeModifier>       opttypemodifier typemodifier
%type  <cppEnum>            enumdefn enumfwddecl enumdefnstmt
%type  <enumItem>           enumitem
%type  <enumItemList>       enumitemlist
%type  <fwdDeclObj>         fwddecl
%type  <cppVarType>         vartype
%type  <cppVarObj>          vardecl varinit vardeclstmt
%type  <cppVarAssign>       varassign optvarassign
%type  <varOrFuncPtr>       param
%type  <str>                funcobjstr /* Identify funcobjstr as str, at least for time being */
%type  <templateArg>        templatearg templatearglist /* For time being. We may need to make it more robust in future. */
%type  <asmBlock>           asmblock
%type  <cppVarObjList>      vardecllist vardeclliststmt
%type  <paramList>          paramlist lambdaparams
%type  <typedefName>        typedefname typedefnamestmt
%type  <typedefList>        typedeflist typedefliststmt
%type  <usingNamespaceDecl> usingnamespacedecl
%type  <namespaceAlias>     namespacealias
%type  <usingDecl>          usingdecl
%type  <cppCompundObj>      stmtlist optstmtlist progunit classdefn namespacedefn classdefnstmt externcblock block
%type  <templateParamList>  templatespecifier templateparamlist
%type  <templateParam>      templateparam
%type  <docCommentObj>      doccomment
%type  <cppExprObj>         expr exprlist exprorlist funcargs exprstmt optexpr lambdacapture captureallbyref captureallbyval
%type  <cppLambda>          lambda
%type  <ifBlock>            ifblock;
%type  <whileBlock>         whileblock;
%type  <doWhileBlock>       dowhileblock;
%type  <forBlock>           forblock;
%type  <forRangeBlock>      forrangeblock;
%type  <switchBlock>        switchstmt;
%type  <switchBody>         caselist;
%type  <tryBlock>           tryblock;
%type  <catchBlock>         catchblock;
%type  <cppFuncPointerObj>  functionpointer functionptrtype funcpointerdecl funcptrtypedef funcptrortype funcobj
%type  <funcDeclData>       funcdecldata
%type  <cppFuncObj>         funcdecl funcdeclstmt funcdefn
%type  <cppCtorObj>         ctordecl ctordeclstmt ctordefn
%type  <cppDtorObj>         dtordecl dtordeclstmt dtordefn
%type  <cppTypeConverter>   typeconverter typeconverterstmt
%type  <memInitList>        meminitlist
%type  <memInit>            meminit
%type  <compoundType>       classspecifier
%type  <attr>               varattrib exptype optfuncattrib functype optfunctype optfinal
%type  <inheritList>        optinheritlist
%type  <inheritType>        optinherittype
%type  <objAccessType>      protlevel changeprotlevel
%type  <identifierList>     identifierlist
%type  <funcThrowSpec>      functhrowspec optfuncthrowspec

%type  <hashDefine>         define
%type  <hashUndef>          undef
%type  <hashInclude>        include
%type  <hashImport>         import
%type  <hashIf>             hashif
%type  <hashError>          hasherror
%type  <hashWarning>        hashwarning
%type  <hashPragma>         pragma
%type  <cppObj>             preprocessor

%type  <blob>               blob

// precedence as mentioned at https://en.cppreference.com/w/cpp/language/operator_precedence
%left COMMA
// &=, ^=, |=, <<=, >>=, *=, /=, %=, +=, -=, =, throw, a?b:c
%right tknAndEq tknXorEq tknOrEq tknLShiftEq tknRShiftEq tknMulEq tknDivEq tknPerEq tknPlusEq tknMinusEq '=' tknThrow TERNARYCOND tknReturn
%left tknOr
%left tknAnd
%left '|'
%left '^'
%left '&'
%left tknCmpEq tknNotEq // ==, !=
// tknLT and tknGT are used instead of '<', and '>' because otherwise parsing template and template args is very difficult.
%left tknLT /*tknGT*/ tknLessEq tknGreaterEq
%left tkn3WayCmp       // <=>
%left  tknLShift RSHIFT

%left   '+' '-'
%left   '*' '/' '%'
%left tknArrowStar
%right PREINCR PREDECR UNARYMINUS '!' '~' CSTYLECAST DEREF ADDRESSOF tknSizeOf tknNew tknDelete
%left POSTINCR POSTDECR FUNCTIONALCAST FUNCCALL SUBSCRIPT '.' tknArrow
%left tknScopeResOp
%right GLOBAL
%left TEMPLATE

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
progunit          : optstmtlist [ZZLOG;] {
                    gProgUnit = $$ = $1;
                    if (gProgUnit)
                      gProgUnit->compoundType(CppCompoundType::kCppFile);
                  }
                  ;

optstmtlist       : [ZZLOG;] {
                    $$ = nullptr;
                  }
                  | stmtlist [ZZLOG;] {
                    $$ = $1;
                  }
                  ;

stmtlist          : stmt [ZZLOG;] {
                    $$ = newCompound(gAccessTypeStack.empty() ? gCurAccessType : gAccessTypeStack.top());
                    if ($1)
                    {
                      $$->addMember($1);
                    } // Avoid 'comment-btyacc-constructs.sh' to act on this
                  }
                  | stmtlist stmt [ZZLOG;] {
                    $$ = ($1 == 0) ? newCompound(gAccessTypeStack.empty() ? gCurAccessType : gAccessTypeStack.top()) : $1;
                    if ($2)
                    {
                      $$->addMember($2);
                    } // Avoid 'comment-btyacc-constructs.sh' to act on this
                  }
                  | optstmtlist changeprotlevel [ZZLOG;] { $$ = $1; gCurAccessType = $2; } // Change of protection level is not a statement but this way it is easier to implement.
                  ;

stmt              : vardeclstmt         [ZZLOG;] { $$ = $1; }
                  | vardeclliststmt     [ZZLOG;] { $$ = $1; }
                  | enumdefnstmt        [ZZLOG;] { $$ = $1; }
                  | enumfwddecl         [ZZLOG;] { $$ = $1; }
                  | typedefnamestmt     [ZZLOG;] { $$ = $1; }
                  | typedefliststmt     [ZZLOG;] { $$ = $1; }
                  | classdefnstmt       [ZZLOG;] { $$ = $1; }
                  | namespacedefn       [ZZLOG;] { $$ = $1; }
                  | fwddecl             [ZZLOG;] { $$ = $1; }
                  | doccomment          [ZZLOG;] { $$ = $1; }
                  | exprstmt            [ZZLOG;] { $$ = $1; }
                  | ifblock             [ZZLOG;] { $$ = $1; }
                  | whileblock          [ZZLOG;] { $$ = $1; }
                  | dowhileblock        [ZZLOG;] { $$ = $1; }
                  | forblock            [ZZLOG;] { $$ = $1; }
                  | forrangeblock       [ZZLOG;] { $$ = $1; }
                  | funcpointerdecl     [ZZLOG;] { $$ = $1; }
                  | funcdeclstmt        [ZZLOG;] { $$ = $1; }
                  | funcdefn            [ZZLOG;] { $$ = $1; }
                  | ctordeclstmt        [ZZLOG;] { $$ = $1; }
                  | ctordefn            [ZZLOG;] { $$ = $1; }
                  | dtordeclstmt        [ZZLOG;] { $$ = $1; }
                  | dtordefn            [ZZLOG;] { $$ = $1; }
                  | typeconverterstmt   [ZZLOG;] { $$ = $1; }
                  | externcblock        [ZZLOG;] { $$ = $1; }
                  | funcptrtypedef      [ZZLOG;] { $$ = $1; }
                  | preprocessor        [ZZLOG;] { $$ = $1; }
                  | block               [ZZLOG;] { $$ = $1; }
                  | switchstmt          [ZZLOG;] { $$ = $1; }
                  | tryblock            [ZZLOG;] { $$ = $1; }
                  | usingdecl           [ZZLOG;] { $$ = $1; }
                  | usingnamespacedecl  [ZZLOG;] { $$ = $1; }
                  | namespacealias      [ZZLOG;] { $$ = $1; }
                  | macrocall           [ZZLOG;] { $$ = new CppMacroCall($1, gCurAccessType); }
                  | macrocall ';'       [ZZLOG;] { $$ = new CppMacroCall(mergeCppToken($1, $2), gCurAccessType); }
                  | ';'                 [ZZLOG;] { $$ = nullptr; }  /* blank statement */
                  | asmblock            [ZZLOG;] { $$ = $1; }
                  | blob                [ZZLOG;] { $$ = $1; }
                  ;

preprocessor      : define              [ZZLOG;] { $$ = $1; }
                  | undef               [ZZLOG;] { $$ = $1; }
                  | include             [ZZLOG;] { $$ = $1; }
                  | import              [ZZLOG;] { $$ = $1; }
                  | hashif              [ZZLOG;] { $$ = $1; }
                  | hasherror           [ZZLOG;] { $$ = $1; }
                  | hashwarning         [ZZLOG;] { $$ = $1; }
                  | pragma              [ZZLOG;] { $$ = $1; }
                  ;

asmblock          : tknAsm              [ZZLOG;] { $$ = new CppAsmBlock($1); }
                  ;

macrocall         : tknMacro [ZZLOG; $$ = $1;] {}
                  | macrocall '(' ')' [ZZLOG; $$ = mergeCppToken($1, $3); ] {}
                  | macrocall '(' expr ')' [
                    ZZLOG;
                    $$ = mergeCppToken($1, $4);
                    delete $3;
                  ] {}
                  ;

switchstmt        : tknSwitch '(' expr ')' '{' caselist '}' [ZZLOG;] {
                    $$ = new CppSwitchBlock($3, $6);
                  }
                  ;

caselist          : [ZZLOG;] {
                    $$ = new CppSwitchBody;
                  }
                  | caselist tknCase expr ':' optstmtlist [ZZLOG;] {
                    $$ = $1;
                    $$->emplace_back($3, $5);
                  }
                  | caselist tknDefault ':' optstmtlist [ZZLOG;] {
                    $$ = $1;
                    $$->emplace_back(nullptr, $4);
                  }
                  | doccommentstr caselist [ZZLOG;] { $$ = $2; }
                  | caselist doccommentstr [ZZLOG;] { $$ = $1; }
                  ;

block             : '{' optstmtlist '}' [ZZLOG;] {
                    $$ = $2;
                    if ($$ == nullptr)
                      $$ = newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock);
                    else
                      $$->compoundType(CppCompoundType::kBlock);
                  }
                  | doccomment block [ZZLOG;] {
                    $$ = $2;
                  }
                  ;

ifblock           : tknIf '(' expr ')' stmt [ZZLOG;] {
                    $$ = new CppIfBlock($3, $5);
                  }
                  | tknIf '(' varinit ')' stmt [ZZLOG;] {
                    $$ = new CppIfBlock($3, $5);
                  }
                  | ifblock tknElse stmt [ZZLOG;] {
                    $$ = $1;
                    $$->elsePart($3);
                  }
                  ;

whileblock        : tknWhile '(' expr ')' stmt [ZZLOG;] {
                    $$ = new CppWhileBlock($3, $5);
                  }
                  | tknWhile '(' varinit ')' stmt [ZZLOG;] {
                    $$ = new CppWhileBlock($3, $5);
                  }
                  ;

dowhileblock      : tknDo stmt tknWhile '(' expr ')' [ZZLOG;] {
                    $$ = new CppDoWhileBlock($5, $2);
                  }
                  ;

forblock          : tknFor '(' optexpr ';' optexpr ';' optexpr ')' stmt [ZZLOG;] {
                    $$ = new CppForBlock($3, $5, $7, $9);
                  }
                  | tknFor '(' varinit ';' optexpr ';' optexpr ')' stmt [ZZLOG;] {
                    $$ = new CppForBlock($3, $5, $7, $9);
                  }
                  | tknFor '(' vardecllist ';' optexpr ';' optexpr ')' stmt [ZZLOG;] {
                    $$ = new CppForBlock($3, $5, $7, $9);
                  }
                  ;

forrangeblock     : tknFor '(' vardecl ':' expr ')' stmt [ZZLOG;] {
                    $$ = new CppRangeForBlock($3, $5, $7);
                  }
                  ;

tryblock          : tknTry block catchblock [ZZLOG;] {
                    $$ = new CppTryBlock($2, $3);
                  }
                  | tryblock catchblock [ZZLOG;] {
                    $$ = $1;
                    $$->addCatchBlock($2);
                  }
                  ;

catchblock        : tknCatch '(' vartype optname ')' block [ZZLOG;] {
                    $$ = new CppCatchBlock{CppVarTypePtr($3), $4, CppCompoundPtr($6)};
                  }
                  ;

optexpr           : {
                    $$ = nullptr;
                  }
                  | expr [ZZLOG;] {
                    $$ = $1;
                  }
                  | exprlist [ZZLOG;] {
                    $$ = $1;
                  }
                  ;

define            : tknPreProHash tknDefine name name          [ZZLOG;] {
                    $$ = new CppDefine(CppDefine::kRename, $3, $4);
                  }
                  | tknPreProHash tknDefine name               [ZZLOG;] {
                    $$ = new CppDefine(CppDefine::kRename, $3);
                  }
                  | tknPreProHash tknDefine name tknNumber     [ZZLOG;] {
                    $$ = new CppDefine(CppDefine::kConstNumDef, $3, $4);
                  }
                  | tknPreProHash tknDefine name tknStrLit     [ZZLOG;] {
                    $$ = new CppDefine(CppDefine::kConstStrDef, $3, $4);
                  }
                  | tknPreProHash tknDefine name tknCharLit    [ZZLOG;] {
                    $$ = new CppDefine(CppDefine::kConstCharDef, $3, $4);
                  }
                  | tknPreProHash tknDefine name tknPreProDef  [ZZLOG;] {
                    $$ = new CppDefine(CppDefine::kComplexMacro, $3, $4);
                  }
                  ;

undef             : tknPreProHash tknUndef name                 [ZZLOG;]  { $$ = new CppUndef($3); }
                  ;

include           : tknPreProHash tknInclude tknStrLit          [ZZLOG;]  { $$ = new CppInclude((std::string) $3); }
                  | tknPreProHash tknInclude tknStdHdrInclude   [ZZLOG;]  { $$ = new CppInclude((std::string) $3); }
                  ;

import            : tknPreProHash tknImport tknStrLit           [ZZLOG;]  { $$ = new CppImport((std::string) $3); }
                  | tknPreProHash tknImport tknStdHdrInclude    [ZZLOG;]  { $$ = new CppImport((std::string) $3); }
                  ;

hashif            : tknPreProHash tknIf tknPreProDef            [ZZLOG;]  { $$ = new CppHashIf(CppHashIf::kIf,      $3); }
                  | tknPreProHash tknIfDef name                 [ZZLOG;]  { $$ = new CppHashIf(CppHashIf::kIfDef,   $3); }
                  | tknPreProHash tknIfNDef name                [ZZLOG;]  { $$ = new CppHashIf(CppHashIf::kIfNDef,  $3); }
                  | tknPreProHash tknIfNDef tknApiDecor         [ZZLOG;]  { $$ = new CppHashIf(CppHashIf::kIfNDef,  $3); }
                  | tknPreProHash tknElse                       [ZZLOG;]  { $$ = new CppHashIf(CppHashIf::kElse       ); }
                  | tknPreProHash tknElIf  tknPreProDef         [ZZLOG;]  { $$ = new CppHashIf(CppHashIf::kElIf,    $3); }
                  | tknPreProHash tknEndIf                      [ZZLOG;]  { $$ = new CppHashIf(CppHashIf::kEndIf      ); }
                  ;

hasherror         : tknPreProHash tknHashError                  [ZZLOG;]  { $$ = new CppHashError($2); }
                  | tknPreProHash tknHashError strlit           [ZZLOG;]  { $$ = new CppHashError(mergeCppToken($2, $3)); }
                  ;

hashwarning       : tknPreProHash tknHashWarning                [ZZLOG;]  { $$ = new CppHashWarning($2); }
                  | tknPreProHash tknHashWarning strlit         [ZZLOG;]  { $$ = new CppHashWarning(mergeCppToken($2, $3)); }
                  ;

pragma            : tknPreProHash tknPragma tknPreProDef        [ZZLOG;]  { $$ = new CppPragma($3); }
                  ;

doccomment        : doccommentstr                               [ZZLOG;]  { $$ = new CppDocComment((std::string) $1, gCurAccessType); }
                  ;

doccommentstr     : tknFreeStandingBlockComment                          [ZZLOG;]  { $$ = $1; }
                  | tknFreeStandingLineComment                           [ZZLOG;]  { $$ = $1; }
                  | doccommentstr tknFreeStandingBlockComment            [ZZLOG;]  { $$ = mergeCppToken($1, $2); }
                  | doccommentstr tknFreeStandingLineComment             [ZZLOG;]  { $$ = mergeCppToken($1, $2); }
                  ;

identifier        : name                                          [ZZLOG; $$ = $1; ] {}
                  | identifier tknScopeResOp identifier           [ZZLOG; $$ = mergeCppToken($1, $3); ] {}
                  | id                                            [ZZLOG; $$ = $1; ] {}
                  | templidentifier                               [ZZLOG; $$ = $1; ] {}
                  | tknOverride                                   [ZZLOG; $$ = $1; /* override is not a reserved keyword */ ] {}
                  | identifier tknEllipsis                        [ZZLOG; $$ = mergeCppToken($1, $2); ] {}
                  | macrocall                                     [ZZLOG; $$ = $1; ] {}
                  | templqualifiedid                              [ZZLOG; $$ = $1; ] {}
                  ;

numbertype        : tknInteger                            [ZZLOG;] { $$ = $1; }
                  | tknFloat                              [ZZLOG;] { $$ = $1; }
                  | tknDouble                             [ZZLOG;] { $$ = $1; }
                  | tknChar                               [ZZLOG;] { $$ = $1; }
                  | tknNumSignSpec                        [ZZLOG;] { $$ = $1; }
                  | tknNumSignSpec numbertype             [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  ;

typeidentifier    : identifier                            [ZZLOG;] { $$ = $1; }
                  | tknScopeResOp identifier %prec GLOBAL [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | typeidentifier tknScopeResOp typeidentifier [ZZLOG;] { $$ = mergeCppToken($1, $3); }
                  | numbertype                            [ZZLOG;] { $$ = $1; }
                  | tknAuto                               [ZZLOG;] { $$ = $1; }
                  | tknVoid                               [ZZLOG;] { $$ = $1; }
                  | tknEnum  identifier                   [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknTypename identifier  [
                    if (gTemplateParamStart == $1.sz)
                      ZZERROR;
                    else
                      ZZLOG;
                  ]                                       [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknEllipsis                           [ZZLOG;] { $$ = $1; }
                  | tknTypename tknEllipsis               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknClass tknEllipsis                  [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | typeidentifier tknEllipsis            [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknDecltype '(' expr ')'              [ZZLOG;] { $$ = mergeCppToken($1, $4); delete $3; }
                  ;

templidentifier   : identifier tknLT templatearglist tknGT  [ZZLOG; $$ = mergeCppToken($1, $4); ] {}
                  ;

templqualifiedid  : tknTemplate templidentifier             [ZZLOG; $$ = mergeCppToken($1, $2); ] {}
                  ;

name              : tknName  [ZZLOG; $$ = $1;] {}
                  ;

id                : tknID  [ZZLOG; $$ = $1; ] {}
                  ;

optname           :         [ZZLOG;] { $$ = makeCppToken(nullptr, nullptr); }
                  | name    [ZZLOG;] { $$ = $1; }
                  ;

enumitem          : name            [ZZLOG;]   { $$ = new CppEnumItem($1);     }
                  | name '=' expr   [ZZLOG;]   { $$ = new CppEnumItem($1, $3); }
                  | doccomment      [ZZLOG;]   { $$ = new CppEnumItem($1);     }
                  | preprocessor    [ZZLOG;]   { $$ = new CppEnumItem($1);     }
                  | macrocall       [ZZLOG;]   { $$ = new CppEnumItem($1);     }
                  | blob            [ZZLOG;]   { $$ = new CppEnumItem($1);     }
                  ;

blob              : tknBlob      [ZZLOG;]   { $$ = new CppBlob($1);         }
                  ;

enumitemlist      :                           [ZZLOG;] { $$ = 0; }
                  | enumitemlist enumitem     [ZZLOG;] {
                    $$ = $1 ? $1 : new CppEnumItemList;
                    $$->push_back($2);
                  }
                  | enumitemlist ',' enumitem [ZZLOG;] {
                    $$ = $1 ? $1 : new CppEnumItemList;
                    $$->push_back($3);
                  }
                  | enumitemlist ','          [ZZLOG;] {
                    $$ = $1;
                  }
                  ;

enumdefn          : tknEnum optname '{' enumitemlist '}'                                        [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $2, $4);
                  }
                  | tknEnum optapidecor name ':' typeidentifier '{' enumitemlist '}'            [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $3, $7, false, $5);
                  };
                  | tknEnum ':' typeidentifier '{' enumitemlist '}'                           [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, "", $5, false, $3);
                  };
                  | tknEnum optapidecor name '{' enumitemlist '}'                               [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $3, $5, false);
                  };
                  | tknEnum tknClass optapidecor name ':' typeidentifier '{' enumitemlist '}'   [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $4, $8, true, $6);
                  }
                  | tknEnum tknClass optapidecor name '{' enumitemlist '}'                      [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $4, $6, true);
                  }
                  | tknTypedef tknEnum optapidecor optname '{' enumitemlist '}' name              [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $8, $6);
                  }
                  ;

enumdefnstmt      : enumdefn ';' [ZZLOG;] { $$ = $1; }
                  ;

enumfwddecl       : tknEnum name ':' typeidentifier ';'                                 [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $2, nullptr, false, $4);
                  }
                  | tknEnum tknClass name ':' typeidentifier ';'                        [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $3, nullptr, true, $5);
                  }
                  | tknEnum tknClass name ';'                                           [ZZVALID;] {
                    $$ = new CppEnum(gCurAccessType, $3, nullptr, true);
                  }
                  ;

funcptrtypedef    : tknTypedef functionpointer ';' [ZZVALID;] {
                    $2->addAttr(kTypedef);
                    $$ = $2;
                  }

typedefnamestmt   : typedefname ';'     [ZZVALID;] { $$ = $1; }
                  ;

typedefliststmt   : typedeflist ';'     [ZZVALID;] { $$ = $1; }
                  ;

typedeflist       : tknTypedef vardecllist  [ZZLOG;] { $$ = new CppTypedefList($2); }
                  ;

typedefname       : tknTypedef vardecl      [ZZLOG;] { $$ = new CppTypedefName($2); }
                  ;

usingdecl         : tknUsing name '=' vartype ';'         [ZZLOG;] {
                    $$ = new CppUsingDecl($2, $4);
                  }
                  | tknUsing name '=' functionptrtype ';' [ZZLOG;] {
                    $$ = new CppUsingDecl($2, $4);
                  }
                  | tknUsing name '=' funcobj ';'         [ZZLOG;] {
                    $$ = new CppUsingDecl($2, $4);
                  }
                  | tknUsing name '=' classdefn ';'       [ZZLOG;] {
                    $$ = new CppUsingDecl($2, $4);
                  }
                  | templatespecifier usingdecl         [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  | tknUsing identifier ';'             [ZZLOG;] {
                    $$ = new CppUsingDecl($2, gCurAccessType);
                  }
                  ;
                  ;

namespacealias    : tknNamespace name '=' identifier ';'    [ZZLOG;] {
                    $$ = new CppNamespaceAlias($2, $4);
                  }
                  ;

usingnamespacedecl: tknUsing tknNamespace identifier ';'  [ZZLOG;] {
                    $$ = new CppUsingNamespaceDecl($3);
                  }
                  ;

vardeclliststmt   : vardecllist ';' [ZZVALID;] { $$ = $1; }
                  | exptype vardecllist ';' [ZZVALID;] { $$ = $2; }
                  ;

vardeclstmt       : vardecl ';'                   [ZZVALID;] { $$ = $1; }
                  | varinit ';'                   [ZZVALID;] { $$ = $1; }
                  | apidecor vardeclstmt          [ZZVALID;] { $$ = $2; $$->apidecor($1); }
                  | exptype vardeclstmt           [ZZVALID;] { $$ = $2; $$->addAttr($1); }
                  | varattrib vardeclstmt         [ZZVALID;] { $$ = $2; $$->addAttr($1); }
                  ;

vardecllist       : optfunctype varinit ',' opttypemodifier name optvarassign [ZZLOG;] {
                    $2->addAttr($1);
                    $$ = new CppVarList($2, CppVarDeclInList($4, CppVarDecl{$5}));
                    /* TODO: Use optvarassign as well */
                  }
                  | optfunctype vardecl ',' opttypemodifier name optvarassign [ZZLOG;] {
                    $2->addAttr($1);
                    $$ = new CppVarList($2, CppVarDeclInList($4, CppVarDecl{$5}));
                    /* TODO: Use optvarassign as well */
                  }
                  | optfunctype vardecl ',' opttypemodifier name ':' expr [ZZLOG;] {
                    $2->addAttr($1);
                    $$ = new CppVarList($2, CppVarDeclInList($4, CppVarDecl{$5}));
                    /* TODO: Use optvarassign as well */
                  }
                  | vardecllist ',' opttypemodifier name optvarassign [ZZLOG;] {
                    $$ = $1;
                    $$->addVarDecl(CppVarDeclInList($3, CppVarDecl{$4}));
                    /* TODO: Use optvarassign as well */
                  }
                  | vardecllist ',' opttypemodifier name optvarassign ':' expr [ZZLOG;] {
                    $$ = $1;
                    $$->addVarDecl(CppVarDeclInList($3, CppVarDecl{$4}));
                    /* TODO: Use optvarassign as well */
                  }
                  ;

varinit           : vardecl '(' typeidentifier '*' name      [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
                  | vardecl '(' typeidentifier '*' '*' name  [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
                  | vardecl '(' typeidentifier '*' '&' name  [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
                  | vardecl '(' typeidentifier '&' name      [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
                  | vardecl '(' typeidentifier tknAnd name   [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
                  | vardecl '(' typeidentifier ')'         [gParamModPos = $3.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
                  | vardecl '(' ')'                        [ZZERROR;]                       { /*FuncDeclHack*/ $$ = nullptr; }
                  | vardecl varassign           [ZZLOG;] {
                    $$ = $1;
                    $$->assign($2.assignValue_, $2.assignType_);
                  }
                  | tknConstExpr varinit        [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr(kConstExpr);
                  }
                  ;

varassign         : '=' expr            [ZZLOG;] {
                    $$ = CppVarAssign{$2, AssignType::kUsingEqual};
                  }
                  | '(' exprorlist ')'  [ZZLOG;] {
                    $$ = CppVarAssign{$2, AssignType::kUsingBracket};
                  }
                  | '{' funcargs '}'    [ZZLOG;] {
                    $$ = CppVarAssign{$2, AssignType::kUsingBraces};
                  }
                  ;

optvarassign      :                     [ZZLOG;]  { $$ = CppVarAssign{nullptr, AssignType::kNone}; }
                  | varassign           [ZZLOG;]  { $$ = $1; }
                  ;

vardecl           : vartype varidentifier       [ZZLOG;]         {
                    $$ = new CppVar($1, $2.toString());
                  }
                  | vartype apidecor varidentifier       [ZZLOG;]         {
                    $$ = new CppVar($1, $3.toString());
                    $$->apidecor($2);
                  }
                  | functionpointer             [ZZLOG;] {
                    $$ = new CppVar(gCurAccessType, $1, CppTypeModifier());
                  }
                  | vardecl '[' expr ']'        [ZZLOG;] {
                    $$ = $1;
                    $$->addArraySize($3);
                  }
                  | vardecl '[' ']'             [ZZLOG;] {
                    $$ = $1;
                    $$->addArraySize(nullptr);
                  }
                  | vardecl ':' expr            [ZZLOG;] {
                    $$ = $1;
                    $$->bitField($3);
                  }
                  | templatespecifier vardecl   [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  | varattrib vardecl           [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  ;

vartype           : typeidentifier opttypemodifier    [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, $1, $2);
                  }
                  | tknClass identifier opttypemodifier [
                    if (gTemplateParamStart == $1.sz)
                      ZZERROR;
                    else
                      ZZLOG;
                  ] {
                    $$ = new CppVarType(gCurAccessType, mergeCppToken($1, $2), $3);
                  }
                  | tknStruct optapidecor identifier opttypemodifier                 [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, mergeCppToken($1, $3), $4);
                  }
                  | tknUnion identifier opttypemodifier                  [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, mergeCppToken($1, $2), $3);
                  }
                  | functionptrtype                   [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, $1, CppTypeModifier());
                  }
                  | classdefn                         [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, $1, CppTypeModifier());
                  }
                  | classdefn typemodifier            [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, $1, $2);
                  }
                  | enumdefn                          [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, $1, CppTypeModifier());
                  }
                  | enumdefn typemodifier             [ZZLOG;] {
                    $$ = new CppVarType(gCurAccessType, $1, $2);
                  }
                  | varattrib vartype                 [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  | vartype tknEllipsis               [ZZLOG;] {
                    $$ = $1;
                    $$->paramPack_ = true;
                  }
                  | typeidentifier typeidentifier tknScopeResOp typemodifier [ZZLOG;] {
                    // reference to member declrations. E.g.:
                    // int GrCCStrokeGeometry::InstanceTallies::* InstanceType
                    $$ = new CppVarType(gCurAccessType, mergeCppToken($1, $3), $4);
                  }
                  ;

varidentifier     : identifier          [ZZLOG;]  { $$ = $1; }
                  | tknFinal            [ZZLOG;]  { $$ = $1; /* final is not a reserved keyword */ }
                  | '(' '&' name ')'      [ZZLOG;]  { $$ = mergeCppToken($1, $4); }
                  | '(' '*' name ')'      [ZZLOG;]  { $$ = mergeCppToken($1, $4); }
                  | '(' '*' '*' name ')'  [ZZLOG;]  { $$ = mergeCppToken($1, $5); }
                  ;

opttypemodifier   : [ZZLOG;] { $$ = CppTypeModifier(); }
                  | typemodifier { $$ = $1; }
                  | doccomment opttypemodifier { $$ = $2; }
                  ;

typemodifier      : tknConst                              [ZZLOG;] {
                    $$ = CppTypeModifier();
                    $$.constBits_ |= (1 << $$.ptrLevel_);
                  }
                  | '*' %prec PTRDECL                     [ZZLOG;] {
                    $$ = CppTypeModifier();
                    $$.ptrLevel_++;
                  }
                  | '&' %prec REFDECL                     [ZZLOG;] {
                    $$ = CppTypeModifier();
                    $$.refType_ = CppRefType::kByRef;
                  }
                  | tknAnd %prec REFDECL                  [ZZLOG;] {
                    $$ = CppTypeModifier();
                    $$.refType_ = CppRefType::kRValRef;
                  }
                  | typemodifier tknConst                 [ZZLOG;] {
                    $$ = $1;
                    $$.constBits_ |= (1 << $$.ptrLevel_);
                  }
                  | typemodifier '*' %prec PTRDECL        [ZZLOG;] {
                    $$ = $1;
                    $$.ptrLevel_++;
                  }
                  | typemodifier '&' %prec REFDECL        [ZZLOG;] {
                    $$ = $1;
                    $$.refType_ = CppRefType::kByRef;
                  }
                  | typemodifier tknAnd %prec REFDECL     [ZZLOG;] {
                    $$ = $1;
                    $$.refType_ = CppRefType::kRValRef;
                  }

                  ;

exptype           : tknStatic    [ZZLOG;] { $$ = kStatic;  }
                  | tknExtern    [ZZLOG;] { $$ = kExtern;  }
                  | tknExternC   [ZZLOG;] { $$ = kExternC; }
                  ;

varattrib         : tknConst     [ZZLOG;] { $$ = kConst;      }
                  | tknVolatile  [ZZLOG;] { $$ = kVolatile;   }
                  | tknMutable   [ZZLOG;] { $$ = kMutable;    }
                  | tknConstExpr [ZZLOG;] { $$ = kConstExpr;  }
                  ;

typeconverter     : tknOperator vartype '(' optvoid ')'                           [ZZLOG;] {
                    $$ = newTypeConverter($2, makeCppToken($1.sz, $3.sz));
                  }
                  | identifier tknScopeResOp tknOperator vartype '(' optvoid ')'  [ZZLOG;] {
                    $$ = newTypeConverter($4, makeCppToken($1.sz, $5.sz));
                  }
                  | functype typeconverter                                        [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  | typeconverter tknConst                                        [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kConst);
                  }
                  | apidecor typeconverter                                        [ZZLOG;] {
                    $$ = $2;
                    $$->decor1($1);
                  }
                  | templatespecifier typeconverter                               [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  ;

typeconverterstmt : typeconverter ';'   [ZZVALID;] {
                    $$ = $1;
                  }
                  | typeconverter block [ZZVALID;] {
                    $$ = $1;
                    $$->defn($2);
                  }
                  ;

funcdeclstmt      : funcdecl ';' [ZZVALID;] { $$ = $1; }
                  ;

funcdefn          : funcdecl block [ZZVALID;] {
                    $$ = $1;
                    $$->defn($2 ? $2 : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
                  ;

lambda            : '[' lambdacapture ']' lambdaparams block {
                    $$ = new CppLambda($2, $4, $5);
                  }
                  | '[' lambdacapture ']' lambdaparams tknArrow vartype block {
                    $$ = new CppLambda($2, $4, $7, $6);
                  }
                  ;

lambdaparams      :                   [ZZLOG;] { $$ = nullptr; }
                  | '(' paramlist ')' [ZZLOG;] { $$ = $2; }
                  ;

funcptrortype     : functype vartype '(' optapidecor identifier tknScopeResOp '*' optname ')' '(' paramlist ')' [ZZVALID;] {
                    $$ = new CppFunctionPointer(gCurAccessType, $8, $2, $11, $1, mergeCppToken($5, $6));
                    $$->decor2($4);
                  }
                  | vartype '(' optapidecor identifier tknScopeResOp '*' optname ')' '(' paramlist ')'          [ZZVALID;] {
                    $$ = new CppFunctionPointer(gCurAccessType, $7, $1, $10, 0, mergeCppToken($4, $5));
                    $$->decor2($3);
                  }
                  | functype vartype '(' optapidecor '*' optname ')' '(' paramlist ')'                          [ZZVALID;] {
                    $$ = new CppFunctionPointer(gCurAccessType, $6, $2, $9, $1);
                    $$->decor2($4);
                  }
                  | vartype '(' optapidecor '*' optname ')' '(' paramlist ')'                                   [ZZVALID;] {
                    $$ = new CppFunctionPointer(gCurAccessType, $5, $1, $8, 0);
                    $$->decor2($3);
                  }
                  | vartype '(' '*'  apidecor optname ')' '(' paramlist ')'                                     [ZZVALID;] {
                    $$ = new CppFunctionPointer(gCurAccessType, $5, $1, $8, 0);
                    $$->decor2($4);
                  }
                  | apidecor funcptrortype                                                                      [ZZVALID;] {
                    $$ = $2;
                    $$->decor1($1);
                  }
                  | funcptrortype optfuncattrib                                                                 [ZZVALID;] {
                    $$ = $1;
                    $$->addAttr($2);
                  }
                  ;

functionpointer   : funcptrortype
                    [
                      if ($1->name_.empty() == true) {
                        ZZERROR;
                      }
                    ]
                  ;

functionptrtype   : funcptrortype
                    [
                      if ($1->name_.empty() == false) {
                        ZZERROR;
                      }
                    ]
                  ;

funcobj           : vartype optapidecor '(' paramlist ')' [ZZLOG;] {
                    $$ = new CppFunctionPointer(gCurAccessType, "", $1, $4, 0);
                  }
                  ;

funcpointerdecl   : functionpointer ';' [ZZVALID;] { $$ = $1;}
                  ;

funcdecldata      : funcname '(' paramlist ')' [ZZLOG;] {
                    $$ = CppNtFuncDeclData{$1, $3, 0};
                  }
                  | funcname '(' paramlist ')' optfuncattrib [ZZLOG;] {
                    $$ = CppNtFuncDeclData{$1, $3, $5};
                  }
                  ;

funcdecl          : vartype apidecor funcdecldata                                   [ZZVALID;] {
                    $$ = newFunction(gCurAccessType, $3.funcName, $1, $3.paramList, $3.funcAttr);
                    $$->decor2($2);
                  }
                  | vartype funcdecldata                                            [ZZVALID;] {
                    $$ = newFunction(gCurAccessType, $2.funcName, $1, $2.paramList, $2.funcAttr);
                  }
                  | vartype tknConstExpr funcdecldata                               [ZZVALID;] {
                    $$ = newFunction(gCurAccessType, $3.funcName, $1, $3.paramList, $3.funcAttr | kConstExpr);
                  }
                  | tknAuto funcdecldata tknArrow vartype                           [ZZVALID;] {
                    $$ = newFunction(gCurAccessType, $2.funcName, $4, $2.paramList, $2.funcAttr | kTrailingRet);
                  }
                  | tknAuto tknConstExpr funcdecldata tknArrow vartype              [ZZVALID;] {
                    $$ = newFunction(gCurAccessType, $3.funcName, $5, $3.paramList, $3.funcAttr | kTrailingRet | kConstExpr);
                  }
                  | tknConstExpr funcdecl                                               [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr(kConstExpr);
                  }
                  | apidecor funcdecl                                                   [ZZLOG;] {
                    $$ = $2;
                    if (!$$->decor1().empty())
                      $$->decor2($$->decor1());
                    $$->decor1($1);
                  }
                  | templatespecifier funcdecl                                          [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  | functype funcdecl                                                   [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  | funcdecl '=' tknDelete                                              [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kDelete);
                  }
                  | funcdecl '=' tknDefault                                             [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kDefault);
                  }
                  | funcdecl functhrowspec                                              [ZZLOG;] {
                    $$ = $1;
                    $$->throwSpec($2);
                  }
                  ;

funcobjstr        : typeidentifier optapidecor '(' paramlist ')' [ZZLOG;] {
                    delete $4;
                    $$ = mergeCppToken($1, $5);
                  }
                  ;

funcname          : operfuncname                          [ZZLOG;] { $$ = $1; }
                  | typeidentifier                        [ZZLOG;] { $$ = $1; }
                  | tknScopeResOp operfuncname            [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  /* final can be a function name too, see SkOpSpan.h :| */
                  | tknFinal                              [ZZLOG;] { $$ = $1; }
                  ;

rshift            : tknGT tknGT %prec RSHIFT [ if ($2.sz != ($1.sz + 1)) ZZERROR; ] { $$ = mergeCppToken($1, $2); }
                  ;

operfuncname      : tknOperator '+'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '-'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '*'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '/'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '%'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '^'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '&'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '|'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '~'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '!'               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '='               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknLT             [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknGT             [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknPlusEq         [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknMinusEq        [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknMulEq          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknDivEq          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknPerEq          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknXorEq          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknAndEq          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknOrEq           [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknLShift         [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator rshift            [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknLShiftEq       [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknRShiftEq       [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknCmpEq          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknNotEq          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknLessEq         [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknGreaterEq      [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tkn3WayCmp        [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknAnd            [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknOr             [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknInc            [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknDec            [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator ','               [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknArrow          [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknArrowStar      [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator '(' ')'           [ZZLOG;] { $$ = mergeCppToken($1, $3); }
                  | tknOperator '[' ']'           [ZZLOG;] { $$ = mergeCppToken($1, $3); }
                  | tknOperator tknNew            [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknNew '[' ']'    [ZZLOG;] { $$ = mergeCppToken($1, $4); }
                  | tknOperator tknDelete         [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator tknDelete '[' ']' [ZZLOG;] { $$ = mergeCppToken($1, $4); }
                  | tknOperator typeidentifier    [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  | tknOperator typeidentifier '*'       [ZZLOG;] { $$ = mergeCppToken($1, $3); }
                  | identifier tknScopeResOp operfuncname [ZZLOG;] { $$ = mergeCppToken($1, $3); }

                  /* see https://en.cppreference.com/w/cpp/language/user_literal */
                  | tknOperator tknStrLit name      [ZZLOG;] { $$ = mergeCppToken($1, $3); }

                  /* To fix something like:
                      friend void* operator new<T>(size_t, GrTAllocator*);
                  */
                  | operfuncname tknLT templatearglist tknGT [ZZLOG;] { $$ = mergeCppToken($1, $4); }
                  ;

paramlist         :                     [ZZLOG;] { $$ = nullptr; }
                  | param {
                    $$ = new CppParamVector;
                    $$->emplace_back($1);
                  }
                  | paramlist ',' param [ZZLOG;] {
                    $1->emplace_back($3);
                    $$ = $1;
                  }
                  ;

param             : varinit                        [ZZLOG;] { $$ = $1; $1->addAttr(kFuncParam);  }
                  | vartype '=' expr               [ZZLOG;] {
                    auto var = new CppVar($1, std::string());
                    var->addAttr(kFuncParam);
                    var->assign($3, AssignType::kUsingEqual);
                    $$ = var;
                  }
                  | vardecl                         [ZZLOG;] { $$ = $1; $1->addAttr(kFuncParam);  }
                  | vartype                         [ZZLOG;] {
                    auto var = new CppVar($1, std::string());
                    var->addAttr(kFuncParam);
                    $$ = var;
                  }
                  | funcptrortype                   [ZZLOG;] { $$ = $1; $1->addAttr(kFuncParam);     }
                  | doccomment param                [ZZLOG;] { $$ = $2; }
                  | vartype '[' expr ']'            [ZZLOG;] {
                    auto var = new CppVar($1, std::string());
                    var->addAttr(kFuncParam);
                    var->addArraySize($3);
                    $$ = var;
                  }
                  | vartype '[' ']'                 [ZZLOG;] {
                    auto var = new CppVar($1, std::string());
                    var->addAttr(kFuncParam);
                    var->addArraySize(nullptr);
                    $$ = var;
                  }
                  ;

templatearg       :                 [ZZLOG; $$ = nullptr; /*$$ = makeCppToken(nullptr, nullptr);*/ ] {}
                  | vartype         [ZZLOG; $$ = nullptr; /*$$ = mergeCppToken($1, $2);*/ ] {}
                  | funcobjstr      [ZZLOG; $$ = nullptr; /*$$ = $1;*/ ] {}
                  | expr            [ZZLOG; $$ = nullptr; ] {}
                  ;

templatearglist   : templatearg                       [ZZLOG; $$ = $1; ] {}
                  | templatearglist ',' templatearg   [ZZLOG; $$ = $1; /*$$ = mergeCppToken($1, $3);*/ ] {}
                  ;

functype          : exptype        [ZZLOG;] { $$ = $1; }
                  | tknInline      [ZZLOG;] { $$ = kInline;    }
                  | tknVirtual     [ZZLOG;] { $$ = kVirtual;   }
                  | tknExplicit    [ZZLOG;] { $$ = kExplicit;  }
                  | tknFriend      [ZZLOG;] { $$ = kFriend;    }
                  | tknConstExpr   [ZZLOG;] { $$ = kConstExpr; }
                  ;

optfunctype       :                [ZZLOG;] { $$ = 0;}
                  | functype       [ZZLOG;] { $$ = $1;}
                  ;

optfuncattrib     : tknConst                      [ZZLOG;] { $$ = kConst; }
                  | tknOverride                   [ZZLOG;] { $$ = kOverride; }
                  | tknFinal                      [ZZLOG;] { $$ = kFinal; }
                  | tknNoExcept                   [ZZLOG;] { $$ = kNoExcept; }
                  | '=' tknNumber  [if($2.len != 1 || $2.sz[0] != '0') YYABORT; else ZZVALID;]
                                                  [ZZLOG;] { $$ = kPureVirtual; }
                  | optfuncattrib tknConst        [ZZLOG;] { $$ = $1 | kConst; }
                  | optfuncattrib tknOverride     [ZZLOG;] { $$ = $1 | kOverride; }
                  | optfuncattrib tknFinal        [ZZLOG;] { $$ = $1 | kFinal; }
                  | optfuncattrib tknNoExcept     [ZZLOG;] { $$ = $1 | kNoExcept; }
                  | optfuncattrib '=' tknNumber   [if($3.len != 1 || $3.sz[0] != '0') YYABORT; else ZZVALID;]
                                                  { $$ = $1 | kPureVirtual; }
                  | tknMacro                      [ZZLOG;] { $$ = 0; } /* Ignore macros used as function attributes */
                  ;

optfuncthrowspec  :               [ZZLOG;] { $$ = nullptr; }
                  | functhrowspec [ZZLOG;] { $$ = $1; }
                  ;

functhrowspec     : tknThrow '(' identifierlist ')' [ZZLOG;] {
                    $$ = $3 ? $3 : new CppFuncThrowSpec;
                  }
                  ;

identifierlist    :                               [ZZLOG;] { $$ = nullptr; }
                  | identifier                    [ZZLOG;] {
                    $$ = new CppIdentifierList;
                    $$->push_back($1);
                  }
                  | identifierlist ',' identifier [ZZLOG;] {
                    $$ = $1;
                    $$->push_back($3);
                  }
                  ;

ctordeclstmt      : ctordecl';'                 [ZZVALID;] { $$ = $1; }
                  ;

ctordefn          : ctordecl meminitlist block  [ZZVALID;]
                  {
                    $$ = $1;
                    $$->memInits_  = $2;
                    $$->defn($3);
                  }
                  | name tknScopeResOp name [if($1 != $3) ZZERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
                  {
                    $$ = newConstructor(gCurAccessType, mergeCppToken($1, $3), $6, $9, 0);
                    $$->defn($10);
                    $$->throwSpec($8);
                  }
                  | identifier tknScopeResOp name tknScopeResOp name [if($3 != $5) ZZERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
                  {
                    $$ = newConstructor(gCurAccessType, mergeCppToken($1, $5), $8, $11, 0);
                    $$->defn($12);
                    $$->throwSpec($10);
                  }
                  | name tknLT templatearglist tknGT tknScopeResOp name [if($1 != $6) ZZERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
                  {
                    $$ = newConstructor(gCurAccessType, mergeCppToken($1, $6), $9, $12, 0);
                    $$->defn($13);
                    $$->throwSpec($11);
                  }
                  | functype ctordefn           [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  | templatespecifier ctordefn  [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  ;

ctordecl          : identifier '(' paramlist ')' %prec CTORDECL
                  [
                    if(gCompoundStack.empty())
                      ZZERROR;
                    if((gCompoundStack.top() != $1) && (classNameFromIdentifier(gCompoundStack.top()) != $1))
                      ZZERROR;
                    else
                      ZZVALID;
                  ]
                  {
                    $$ = newConstructor(gCurAccessType, $1, $3, makeEmptyCppMemInitList(), 0);
                  }
                  | functype ctordecl          [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  | templatespecifier ctordecl [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  | ctordecl '=' tknDelete     [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kDelete);
                  }
                  | ctordecl '=' tknDefault    [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kDefault);
                  }
                  | ctordecl functhrowspec     [ZZLOG;] {
                    $$ = $1;
                    $$->throwSpec($2);
                  }
                  | ctordecl tknNoExcept     [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kNoExcept);
                  }
                  | apidecor ctordecl          [ZZLOG;] {
                    $$ = $2;
                    $$->decor1($1);
                  }
                  ;

meminitlist       :                          [ZZLOG;] { $$ = makeEmptyCppMemInitList(); }
                  | ':' meminit              [ZZLOG;] {
                    $$ = makeCppMemInitList(new std::list<CppMemInit>);
                    $$.memInitList->push_back(CppMemInit($2.mem, $2.init));
                  }
                  | ':' blob                 [ZZLOG;] { $$ = makeCppMemInitList($2); }
                  | meminitlist ',' meminit  [ZZLOG;] {
                    $$ = $1;
                    assert($$.memInitListIsABlob_ == false);
                    $$.memInitList->push_back(CppMemInit($3.mem, $3.init));
                  }
                  ;

meminit           : identifier '(' exprorlist ')'    [ZZLOG;] { $$ = CppNtMemInit{$1, $3}; }
                  | identifier '(' ')'               [ZZLOG;] { $$ = CppNtMemInit{$1, nullptr}; }
                  | identifier '{' exprorlist '}'    [ZZLOG;] { $$ = CppNtMemInit{$1, $3}; }
                  | identifier '{' '}'               [ZZLOG;] { $$ = CppNtMemInit{$1, nullptr}; }
                  ;

dtordeclstmt      : dtordecl ';'    [ZZVALID;]     { $$ = $1; }
                  ;

dtordefn          : dtordecl block  [ZZVALID;]
                  {
                    $$ = $1;
                    $$->defn($2 ? $2 : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
                  | name tknScopeResOp '~' name [if($1 != $4) ZZERROR; else ZZVALID;]
                    '(' ')' block
                  {
                    $$ = newDestructor(gCurAccessType, mergeCppToken($1, $4), 0);
                    $$->defn($8 ? $8 : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
                  | identifier tknScopeResOp name tknScopeResOp '~' name [if($3 != $6) ZZERROR; else ZZVALID;]
                    '(' ')' block
                  {
                    $$ = newDestructor(gCurAccessType, mergeCppToken($1, $6), 0);
                    $$->defn($10 ? $10 : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
                  | name tknLT templatearglist tknGT tknScopeResOp '~' name [if($1 != $7) ZZERROR; else ZZVALID;]
                    '(' ')' block
                  {
                    $$ = newDestructor(gCurAccessType, mergeCppToken($1, $7), 0);
                    $$->defn($11 ? $11 : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
                  | templatespecifier dtordefn  [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  | functype dtordefn           [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  ;

dtordecl          : '~' name '(' optvoid ')' %prec DTORDECL [ZZLOG;]
                  [
                    if(gCompoundStack.empty())
                      ZZERROR;
                    if(classNameFromIdentifier(gCompoundStack.top()) != $2)
                      ZZERROR;
                    else
                      ZZVALID;
                  ]
                  {
                    const char* tildaStartPos = $2.sz-1;
                    while(*tildaStartPos != '~') --tildaStartPos;
                    $$ = newDestructor(gCurAccessType, makeCppToken(tildaStartPos, $2.sz+$2.len-tildaStartPos), 0);
                  }
                  | apidecor dtordecl         [ZZLOG;] {
                    $$ = $2;
                    $$->decor1($1);
                  }
                  | functype dtordecl         [ZZLOG;] {
                    $$ = $2;
                    $$->addAttr($1);
                  }
                  | dtordecl optfuncattrib    [ZZLOG;]
                  {
                    $$ = $1;
                    $$->addAttr($2);
                  }
                  | dtordecl '=' tknNumber    [ZZLOG;]
                  {
                    $$ = $1;
                    $$->addAttr(kPureVirtual);
                  }
                  | dtordecl '=' tknDelete    [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kDelete);
                  }
                  | dtordecl '=' tknDefault   [ZZLOG;] {
                    $$ = $1;
                    $$->addAttr(kDefault);
                  }
                  | dtordecl functhrowspec    [ZZLOG;] {
                    $$ = $1;
                    $$->throwSpec($2);
                  }
                  ;

optvoid           :          [ZZLOG;]
                  | tknVoid  [ZZLOG;]
                  ;

optcomment        :            [ZZLOG;]{
                  }
                  | doccomment [ZZVALID;] {
                  }
                  ;

classdefnstmt     : classdefn ';' [ZZVALID;] { $$ = $1;}
                  ;

classdefn         : classspecifier optapidecor identifier optfinal optinheritlist optcomment '{'
                  [
                    ZZVALID;
                    gCompoundStack.push($3);
                    gAccessTypeStack.push(gCurAccessType); gCurAccessType = CppAccessType::kUnknown;
                  ]
                  optstmtlist '}'
                  [
                    ZZVALID;
                    gCompoundStack.pop();
                    gCurAccessType = gAccessTypeStack.top();
                    gAccessTypeStack.pop();
                  ]
                  {
                    $$ = $9 ? $9 : newCompound(gCurAccessType);
                    $$->compoundType($1);
                    $$->apidecor($2);
                    $$->name(pruneClassName($3));
                    $$->inheritanceList($5);
                    $$->addAttr($4);
                  }
                  | classspecifier optinheritlist optcomment
                    '{' { gAccessTypeStack.push(gCurAccessType); gCurAccessType = CppAccessType::kUnknown; }
                      optstmtlist
                    '}' [ZZVALID;]
                  {
                    gCurAccessType = gAccessTypeStack.top();
                    gAccessTypeStack.pop();

                    $$ = $6 ? $6 : newCompound(gCurAccessType);
                    $$->compoundType($1);
                    $$->inheritanceList($2);
                  }
                  | templatespecifier classdefn [ZZLOG;]
                  {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  ;

namespacedefn     : tknNamespace optname '{'
                  [
                    ZZVALID;
                    gCompoundStack.push(classNameFromIdentifier($2));
                    gAccessTypeStack.push(gCurAccessType); gCurAccessType = CppAccessType::kUnknown;
                  ]
                  optstmtlist '}'
                  [
                    ZZVALID;
                    gCompoundStack.pop();
                    gCurAccessType = gAccessTypeStack.top();
                    gAccessTypeStack.pop();
                  ]
                  {
                    $$ = $5 ? $5 : newCompound(gCurAccessType);
                    $$->compoundType(CppCompoundType::kNamespace);
                    $$->name($2);
                  }
                  ;

optfinal          :          [ZZLOG;] { $$ = 0; }
                  | tknFinal [ZZLOG;] { $$ = kFinal; }
                  ;

optinheritlist    :                                                         [ZZLOG;] { $$ = 0; }
                  | ':' protlevel optinherittype typeidentifier                 [ZZVALID;] {
                    $$ = new CppInheritanceList; $$->push_back(CppInheritInfo((std::string) $4, $2, $3));
                  }
                  | optinheritlist ',' protlevel optinherittype typeidentifier  [ZZVALID;] {
                    $$ = $1; $$->push_back(CppInheritInfo((std::string) $5, $3, $4));
                  }
                  | ':' optinherittype protlevel typeidentifier                 [ZZVALID;] {
                    $$ = new CppInheritanceList; $$->push_back(CppInheritInfo((std::string) $4, $3, $2));
                  }
                  | optinheritlist ',' optinherittype protlevel typeidentifier  [ZZVALID;] {
                    $$ = $1; $$->push_back(CppInheritInfo((std::string) $5, $4, $3));
                  }
                  ;

protlevel         :               [ZZLOG;] { $$ = CppAccessType::kUnknown;    }
                  | tknPublic     [ZZLOG;] { $$ = CppAccessType::kPublic;     }
                  | tknProtected  [ZZLOG;] { $$ = CppAccessType::kProtected;  }
                  | tknPrivate    [ZZLOG;] { $$ = CppAccessType::kPrivate;    }
                  ;

optinherittype    :             [ZZLOG;] { $$ = false; }
                  | tknVirtual  [ZZLOG;] { $$ = true; }
                  ;

fwddecl           : classspecifier typeidentifier ';'              [ZZVALID;] { $$ = new CppFwdClsDecl(gCurAccessType, $2, $1); }
                  | classspecifier optapidecor identifier ';'  [ZZVALID;] { $$ = new CppFwdClsDecl(gCurAccessType, $3, $2, $1); }
                  | templatespecifier fwddecl [ZZLOG;] {
                    $$ = $2;
                    $$->templateParamList($1);
                  }
                  | tknFriend typeidentifier ';'  [ZZVALID;] { $$ = new CppFwdClsDecl(gCurAccessType, $2); $$->addAttr(kFriend); }
                  | tknFriend fwddecl             [ZZVALID;] { $$ = $2; $$->addAttr(kFriend); }
                  ;

classspecifier    : tknClass      [ZZLOG;] { $$ = CppCompoundType::kClass;     }
                  | tknStruct     [ZZLOG;] { $$ = CppCompoundType::kStruct;    }
                  | tknUnion      [ZZLOG;] { $$ = CppCompoundType::kUnion;     }
                  ;

templatespecifier : tknTemplate tknLT       [gInTemplateSpec = true;  ZZLOG;   ]
                    templateparamlist tknGT [gInTemplateSpec = false; ZZVALID; ]
                  {
                    $$ = $4;
                  }
                  ;

templateparamlist :                                       [ZZLOG;] {
                    $$ = new CppTemplateParamList;
                  }
                  | templateparam                         [ZZLOG;] {
                    $$ = new CppTemplateParamList;
                    $$->emplace_back($1);
                  }
                  | templateparamlist ',' templateparam   [ZZLOG;] {
                    $$ = $1;
                    $$->emplace_back($3);
                  }
                  ;

templateparam     : tknTypename optname             [ZZLOG;] {
                    $$ = new CppTemplateParam($2);
                  }
                  | tknTypename optname '=' vartype [ZZLOG;] {
                    $$ = new CppTemplateParam($2);
                    $$->defaultArg($4);
                  }
                  | tknClass optname                [ZZLOG;] {
                    $$ = new CppTemplateParam($2);
                  }
                  | tknClass optname '=' vartype    [ZZLOG;] {
                    $$ = new CppTemplateParam($2);
                    $$->defaultArg($4);
                  }
                  | vartype name                    [ZZLOG;] {
                    $$ = new CppTemplateParam($1, $2);
                  }
                  | vartype name '=' expr           [ZZLOG;] {
                    $$ = new CppTemplateParam($1, $2);
                    $$->defaultArg($4);
                  }
                  | functionpointer               [ZZLOG;] {
                    $$ = new CppTemplateParam($1, std::string());
                  }
                  | functionpointer '=' expr        [ZZLOG;] {
                    $$ = new CppTemplateParam($1, std::string());
                    $$->defaultArg($3);
                  }
                  | vartype                       [ZZLOG;] { // Can happen when forward declaring
                    $$ = new CppTemplateParam($1, std::string());
                  }
                  | vartype '=' expr              [ZZLOG;] { // Can happen when forward declaring
                    $$ = new CppTemplateParam($1, std::string());
                    $$->defaultArg($3);
                  }
                  // <TemplateParamHack>
                  | tknTypename name ',' [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] { $$ = nullptr; }
                  | tknTypename name '=' [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] { $$ = nullptr; }
                  | tknTypename name tknGT [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] { $$ = nullptr; }
                  | tknClass name ',' [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] { $$ = nullptr; }
                  | tknClass name tknGT [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] { $$ = nullptr; }
                  // </TemplateParamHack>
                  ;

optapidecor       :             [ZZLOG;] { $$ = makeCppToken(nullptr, nullptr); }
                  | apidecor    [ZZLOG;] { $$ = $1; }
                  ;

apidecor          : apidecortokensq                     [ZZLOG;] { $$ = $1; }
                  | apidecortokensq '(' name ')'          [ZZLOG;] { $$ = mergeCppToken($1, $4); }
                  | apidecortokensq '(' tknNumber ')'   [ZZLOG;] { $$ = mergeCppToken($1, $4); }
                  | apidecortokensq '(' strlit ')'   [ZZLOG;] { $$ = mergeCppToken($1, $4); }
                  ;

apidecortokensq   : tknApiDecor                  [ZZLOG;] { $$ = $1; }
                  | apidecortokensq tknApiDecor  [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  ;

changeprotlevel   : tknPublic     ':'  [ZZVALID;] { $$ = CppAccessType::kPublic;     }
                  | tknProtected  ':'  [ZZVALID;] { $$ = CppAccessType::kProtected;  }
                  | tknPrivate    ':'  [ZZVALID;] { $$ = CppAccessType::kPrivate;    }
                  ;

externcblock      : tknExternC block   [ZZVALID;] {$$ = $2; $$->compoundType(CppCompoundType::kExternCBlock); }
                  ;

strlit            : tknStrLit          [ZZLOG;] { $$ = $1; }
                  | strlit tknStrLit   [ZZLOG;] { $$ = mergeCppToken($1, $2); }
                  ;

expr              : strlit                                                [ZZLOG;] { $$ = new CppExpr((std::string) $1, kNone);          }
                  | tknCharLit                                            [ZZLOG;] { $$ = new CppExpr((std::string) $1, kNone);          }
                  | tknNumber                                             [ZZLOG;] { $$ = new CppExpr((std::string) $1, kNone);          }
                  | '+' tknNumber                                         [ZZLOG;] { $$ = new CppExpr((std::string) $2, kNone);          }
                  | identifier
                    [
                      if ($1.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ]                                                     [ZZLOG;] { $$ = new CppExpr((std::string) $1, kNone);          }
                  | '{' exprlist '}'                                      [ZZLOG;] { $$ = new CppExpr($2, CppExpr::kInitializer);        }
                  | '{' exprlist ',' '}'                                  [ZZLOG;] { $$ = new CppExpr($2, CppExpr::kInitializer);        }
                  | '{' exprorlist '}'                                    [ZZLOG;] { $$ = new CppExpr($2, CppExpr::kInitializer);        }
                  | '{' exprorlist ',' '}'                                [ZZLOG;] { $$ = new CppExpr($2, CppExpr::kInitializer);        }
                  | '{' /*empty expr*/ '}'                                [ZZLOG;] { $$ = new CppExpr((CppExpr*)nullptr, CppExpr::kInitializer);   }
                  | '-' expr %prec UNARYMINUS                             [ZZLOG;] { $$ = new CppExpr($2, kUnaryMinus);                  }
                  | '~' expr                                              [ZZLOG;] { $$ = new CppExpr($2, kBitToggle);                   }
                  | '!' expr                                              [ZZLOG;] { $$ = new CppExpr($2, kLogNot);                      }
                  | '*' expr %prec DEREF                                  [ZZLOG;] { $$ = new CppExpr($2, kDerefer);                     }
                  | '&' expr %prec ADDRESSOF                              [ZZLOG;] { $$ = new CppExpr($2, kRefer);                       }
                  | '&' operfuncname %prec ADDRESSOF                          [ZZLOG;] { $$ = new CppExpr(CppExprAtom($2), kRefer);          }
                  | tknInc expr  %prec PREINCR                            [ZZLOG;] { $$ = new CppExpr($2, kPreIncrement);                }
                  | expr tknInc  %prec POSTINCR                           [ZZLOG;] { $$ = new CppExpr($1, kPostIncrement);               }
                  | tknDec expr  %prec PREDECR                            [ZZLOG;] { $$ = new CppExpr($2, kPreDecrement);                }
                  | expr tknDec  %prec POSTDECR                           [ZZLOG;] { $$ = new CppExpr($1, kPostDecrement);               }
                  | expr '+' expr                                         [ZZLOG;] { $$ = new CppExpr($1, kPlus, $3);                    }
                  | expr '-' expr                                         [ZZLOG;] { $$ = new CppExpr($1, kMinus, $3);                   }
                  | expr '*' expr
                    [
                      if ($2.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ]                                                     [ZZLOG;] { $$ = new CppExpr($1, kMul, $3);                     }
                  | expr '/' expr                                         [ZZLOG;] { $$ = new CppExpr($1, kDiv, $3);                     }
                  | expr '%' expr                                         [ZZLOG;] { $$ = new CppExpr($1, kPercent, $3);                 }
                  | expr '&' expr
                    [
                      if ($2.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ]                                                     [ZZLOG;] { $$ = new CppExpr($1, kBitAnd, $3);                  }
                  | expr '|' expr                                         [ZZLOG;] { $$ = new CppExpr($1, kBitOr, $3);                   }
                  | expr '^' expr                                         [ZZLOG;] { $$ = new CppExpr($1, kXor, $3);                     }
                  | expr '=' expr                                         [ZZLOG;] { $$ = new CppExpr($1, kEqual, $3);                   }
                  | expr tknLT expr                                       [ZZLOG;] { $$ = new CppExpr($1, kLess, $3);                    }
                  | expr tknGT expr                                       [ZZLOG;] { $$ = new CppExpr($1, kGreater, $3);                 }
                  | expr '?' expr ':' expr %prec TERNARYCOND              [ZZLOG;] { $$ = new CppExpr($1, $3, $5);                       }
                  | expr tknPlusEq expr                                   [ZZLOG;] { $$ = new CppExpr($1, kPlusEqual, $3);               }
                  | expr tknMinusEq expr                                  [ZZLOG;] { $$ = new CppExpr($1, kMinusEqual, $3);              }
                  | expr tknMulEq expr                                    [ZZLOG;] { $$ = new CppExpr($1, kMulEqual, $3);                }
                  | expr tknDivEq expr                                    [ZZLOG;] { $$ = new CppExpr($1, kDivEqual, $3);                }
                  | expr tknPerEq expr                                    [ZZLOG;] { $$ = new CppExpr($1, kPerEqual, $3);                }
                  | expr tknXorEq expr                                    [ZZLOG;] { $$ = new CppExpr($1, kXorEqual, $3);                }
                  | expr tknAndEq expr                                    [ZZLOG;] { $$ = new CppExpr($1, kAndEqual, $3);                }
                  | expr tknOrEq expr                                     [ZZLOG;] { $$ = new CppExpr($1, kOrEqual, $3);                 }
                  | expr tknLShift expr                                   [ZZLOG;] { $$ = new CppExpr($1, kLeftShift, $3);               }
                  | expr rshift expr                                      [ZZLOG;] { $$ = new CppExpr($1, kRightShift, $3);              }
                  | expr tknLShiftEq expr                                 [ZZLOG;] { $$ = new CppExpr($1, kLShiftEqual, $3);             }
                  | expr tknRShiftEq expr                                 [ZZLOG;] { $$ = new CppExpr($1, kRShiftEqual, $3);             }
                  | expr tknCmpEq expr                                    [ZZLOG;] { $$ = new CppExpr($1, kCmpEqual, $3);                }
                  | expr tknNotEq expr                                    [ZZLOG;] { $$ = new CppExpr($1, kNotEqual, $3);                }
                  | expr tknLessEq expr                                   [ZZLOG;] { $$ = new CppExpr($1, kLessEqual, $3);               }
                  | expr tknGreaterEq expr                                [ZZLOG;] { $$ = new CppExpr($1, kGreaterEqual, $3);            }
                  | expr tkn3WayCmp expr                                  [ZZLOG;] { $$ = new CppExpr($1, k3WayCmp, $3);                 }
                  | expr tknAnd expr
                    [
                      if ($2.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ]                                                     [ZZLOG;] { $$ = new CppExpr($1, kAnd, $3);                     }
                  | expr tknOr expr                                       [ZZLOG;] { $$ = new CppExpr($1, kOr, $3);                      }
                  | expr '.' funcname                                     [ZZLOG;] { $$ = new CppExpr($1, kDot, CppExprAtom($3));                     }
                  // Member function pointer dereferencing
                  | expr '.' '*' funcname                                 [ZZLOG;] { $$ = new CppExpr($1, kDot, CppExprAtom(mergeCppToken($3, $4)));                     }
                  | expr tknArrow funcname                                [ZZLOG;] { $$ = new CppExpr($1, kArrow, CppExprAtom($3));      }
                  | expr tknArrowStar funcname                            [ZZLOG;] { $$ = new CppExpr($1, kArrowStar, CppExprAtom($3));  }
                  | expr '.' '~' funcname                                 [ZZLOG;] { $$ = new CppExpr($1, kDot, CppExprAtom(mergeCppToken($3, $4)));                     }
                  | expr tknArrow '~' funcname                            [ZZLOG;] { $$ = new CppExpr($1, kArrow, CppExprAtom(mergeCppToken($3, $4)));      }
                  | expr '[' expr ']' %prec SUBSCRIPT                     [ZZLOG;] { $$ = new CppExpr($1, kArrayElem, $3);               }
                  | expr '[' ']' %prec SUBSCRIPT                          [ZZLOG;] { $$ = new CppExpr($1, kArrayElem);                   }
                  | expr '(' funcargs ')' %prec FUNCCALL                  [ZZLOG;] { $$ = new CppExpr($1, kFunctionCall, $3);            }
                  | funcname '(' funcargs ')' %prec FUNCCALL              [ZZLOG;] { $$ = new CppExpr(CppExprAtom($1), kFunctionCall, $3);            }
                  | expr tknArrow '~' identifier '(' ')' %prec FUNCCALL   [ZZLOG;] { $$ = new CppExpr(new CppExpr($1, kArrow, CppExprAtom(mergeCppToken($3, $4))), kFunctionCall, (CppExpr*)nullptr); }
                  /* TODO: Properly support uniform initialization */
                  | identifier '{' funcargs '}' %prec FUNCCALL            [ZZLOG;] { $$ = new CppExpr(new CppExpr((std::string) $1, kNone), kFunctionCall, $3);            }
                  | '(' vartype ')' expr %prec CSTYLECAST                 [ZZLOG;] { $$ = new CppExpr($2, kCStyleCast, $4);              }
                  | tknConstCast tknLT vartype tknGT '(' expr ')'         [ZZLOG;] { $$ = new CppExpr($3, kConstCast, $6);               }
                  | tknStaticCast tknLT vartype tknGT '(' expr ')'        [ZZLOG;] { $$ = new CppExpr($3, kStaticCast, $6);              }
                  | tknDynamicCast tknLT vartype tknGT '(' expr ')'       [ZZLOG;] { $$ = new CppExpr($3, kDynamicCast, $6);             }
                  | tknReinterpretCast tknLT vartype tknGT '(' expr ')'   [ZZLOG;] { $$ = new CppExpr($3, kReinterpretCast, $6);         }
                  | '(' exprorlist ')'                                    [ZZLOG;] { $$ = $2; $2->flags_ |= CppExpr::kBracketed;         }
                  | tknNew typeidentifier                                 [ZZLOG;] { $$ = new CppExpr((std::string) $2, CppExpr::kNew);  }
                  | tknNew expr                                           [ZZLOG;] { $$ = new CppExpr($2, CppExpr::kNew);  }
                  | tknNew '(' expr ')' expr %prec tknNew                 [ZZLOG;] { $$ = new CppExpr($3, kPlacementNew, $5);            }
                  | tknScopeResOp tknNew '(' expr ')' expr %prec tknNew   [ZZLOG;] { $$ = new CppExpr($4, kPlacementNew, $6);            }
                  | tknDelete  expr                                       [ZZLOG;] { $$ = $2; $2->flags_ |= CppExpr::kDelete;            }
                  | tknDelete  '[' ']' expr %prec tknDelete               [ZZLOG;] { $$ = $4; $4->flags_ |= CppExpr::kDeleteArray;       }
                  | tknReturn  exprorlist                                 [ZZLOG;] { $$ = $2; $2->flags_ |= CppExpr::kReturn;            }
                  | tknReturn                                             [ZZLOG;] { $$ = new CppExpr(CppExprAtom(), CppExpr::kReturn);  }
                  | tknThrow  expr                                        [ZZLOG;] { $$ = $2; $2->flags_ |= CppExpr::kThrow;             }
                  | tknThrow                                              [ZZLOG;] { $$ = new CppExpr(CppExprAtom(), CppExpr::kThrow);   }
                  | tknSizeOf '(' vartype ')'                             [ZZLOG;] { $$ = new CppExpr($3, CppExpr::kSizeOf);             }
                  | tknSizeOf '(' expr ')'                                [ZZLOG;] { $$ = new CppExpr($3, CppExpr::kSizeOf);             }
                  | tknSizeOf tknEllipsis '(' vartype ')'                 [ZZLOG;] { $$ = new CppExpr($4, CppExpr::kSizeOf | CppExpr::kVariadicPack);             }
                  | tknSizeOf tknEllipsis '(' expr ')'                    [ZZLOG;] { $$ = new CppExpr($4, CppExpr::kSizeOf | CppExpr::kVariadicPack);             }
                  | expr tknEllipsis                                      [ZZLOG;] { $$ = $1; $$->flags_ |= CppExpr::kVariadicPack; }
                  | lambda                                                [ZZLOG;] { $$ = new CppExpr($1); }

                  /* This is to parse implementation of string user literal, see https://en.cppreference.com/w/cpp/language/user_literal */
                  | tknNumber name                                          [ZZLOG;] { $$ = new CppExpr((std::string) $1, kNone);          }
                  ;

exprlist          : expr ',' expr %prec COMMA                             [ZZLOG;] { $$ = new CppExpr($1, kComma, $3);                   }
                  | exprlist ',' expr %prec COMMA                         [ZZLOG;] { $$ = new CppExpr($1, kComma, $3);                   }
                  | doccommentstr exprlist                                [ZZLOG;] { $$ = $2; }
                  ;

exprorlist        : expr                        [ZZLOG;] { $$ = $1; }
                  | exprlist                    [ZZLOG;] { $$ = $1; }
                  | doccommentstr exprorlist    [ZZLOG;] { $$ = $2; }
                  ;

funcargs          :             [ZZLOG;] { $$ = nullptr; }
                  | exprorlist  [ZZLOG;] { $$ = $1;      }
                  ;

captureallbyref   : '&'  [ZZLOG;] { $$ = new CppExpr("", kRefer); }
                  ;

captureallbyval   : '='  [ZZLOG;] { $$ = new CppExpr("", kEqual, ""); }
                  ;

lambdacapture     : funcargs           [ZZLOG;]
                  | captureallbyref    [ZZLOG;]
                  | captureallbyval    [ZZLOG;]
                  ;

exprstmt          : expr ';'           [ZZLOG;] { $$ = $1; }
                  ;

%%

//////////////////////////////////////////////////////////////////////////

extern LexerData g;

extern const char* contextNameFromState(int ctx);

/**
 * yyparser() invokes this function when it encounters unexpected token.
 */
void yyerror_detailed  (  char* text,
              int errt,
              YYSTYPE& errt_value,
              YYPOSN& errt_posn
            )
{
  extern int getLexerContext();

  const char* lineStart = errt_posn;
  const char* buffStart = g.mInputBuffer;
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
  sprintf(errmsg, "Error: Unexpected token '%s', while in context=%s(%d), found at line#%d\n"
    "%s\n"   // Line that contains the error.
    "%s^\n",  // A ^ below the beginning of unexpected token.
    errt_posn, contextNameFromState(getLexerContext()), getLexerContext(), g.mLineNo, // The error message
    lineStart,
    spacechars);

  printf("%s", errmsg);
  // Replace back the end char
  if(endReplaceChar)
    *lineEnd = endReplaceChar;
}

enum {
  kNoLog    = 0x000,
  kParseLog = 0x001,
  kLexLog   = 0x002,
  kYaccLog  = 0x004
};

static void setupEnv()
{
#if YYDEBUG
  const char* yys = getenv("ZZDEBUG");
  if (yys) {
    const int yyn = *yys - '0';

    gParseLog = ((yyn & kParseLog) ? 1 : 0);
    g.mLexLog = ((yyn & kLexLog)   ? 1 : 0);
    yydebug   = ((yyn & kYaccLog)  ? 1 : 0);
  }
#endif
}

CppCompoundPtr parseStream(char* stm, size_t stmSize)
{
  gProgUnit = nullptr;
  gCurAccessType = CppAccessType::kUnknown;
  
  void setupScanBuffer(char* buf, size_t bufsize);
  void cleanupScanBuffer();
  setupScanBuffer(stm, stmSize);
  setupEnv();
  gTemplateParamStart = nullptr;
  gParamModPos = nullptr;
  gInTemplateSpec = false;
  gDisableYyValid = 0;
  yyparse();
  cleanupScanBuffer();
  CppCompoundStack tmpStack;
  gCompoundStack.swap(tmpStack);
  
  CppCompoundPtr ret(gProgUnit);
  gProgUnit = nullptr;
  return ret;
}
