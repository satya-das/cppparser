// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

/*
  TODOs:
    (1) Parsing of following needs improvements/support:
      (a) Imp: Function pointer
      (b) Sup: Reference to array
      (c) Sup: Pointer to array
      Need to borrow ideas from https://www.nongnu.org/hcb/
        and may be http://www.computing.surrey.ac.uk/research/dsrg/fog/CxxGrammar.y too can help.
*/

// clang-format off

%{
#include "cpptoken.h"
#include "cpp_entity_builders.h"

#include "cppast/cppast.h"
#include "optional.h"
#include "parser.tab.h"
#include "parser.l.h"
#include "utils.h"

#include "memory_util.h"

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>

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
static cppast::CppCompound*  gProgUnit;

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

static CppCompoundStack                     gCompoundStack;

/** {End of Globals} */

#define YYPOSN char*

extern int yylex();

// Yacc generated code causes warnings that need suppression.
// This pragma should be at the end.
#if defined(__clang__) || defined(__GNUC__)
# pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

using namespace cppast;

// FIXME: Improve template arg parsing.
// Template argument needs more robust support.
// As of now we are treating them just as string.
// But for parsing we need to have a type.
class CppTemplateArg;

%}

%union {
  struct CppToken                                  str;
  struct CppFunctionData                           funcDeclData;
  cppast::CppMemberInit*                           memInit;
  cppast::CppEntity*                               cppEntity;
  cppast::CppEntityAccessSpecifier*                accessSpecifier;
  cppast::CppTypeModifier                          typeModifier;
  cppast::CppVarType*                              cppVarType;
  cppast::CppVar*                                  cppVarObj;
  cppast::CppEnum*                                 cppEnum;
  cppast::CppEnumItem*                             enumItem;
  std::list<cppast::CppEnumItem>*                  enumItemList;
  cppast::CppTypedefName*                          typedefName;
  cppast::CppTypedefList*                          typedefList;
  cppast::CppUsingDecl*                            usingDecl;
  cppast::CppUsingNamespaceDecl*                   usingNamespaceDecl;
  cppast::CppNamespaceAlias*                       namespaceAlias;
  cppast::CppCompound*                             cppCompundObj;
  cppast::CppTemplateParam*                        templateParam;
  std::vector<cppast::CppTemplateParam>*           templateParamList;
  cppast::CppDocumentationComment*                 docCommentObj;
  cppast::CppForwardClassDecl*                     fwdDeclObj;
  cppast::CppVarList*                              cppVarObjList;
  cppast::CppPreprocessorUnrecognized*             unRecogPreProObj;
  cppast::CppExpression*                           cppExprObj;
  cppast::CppCallArgs*                             exprList;
  cppast::CppLambda*                               cppLambda;
  cppast::CppFunction*                             cppFuncObj;
  cppast::CppFunctionPointer*                      cppFuncPointerObj;
  cppast::CppEntity*                               varOrFuncPtr;
  std::vector<std::unique_ptr<const cppast::CppEntity>>* paramList;
  cppast::CppConstructor*                          cppCtorObj;
  cppast::CppDestructor*                           cppDtorObj;
  cppast::CppTypeConverter*                        cppTypeConverter;
  cppast::CppMemberInits*                          memInitList;
  std::list<cppast::CppInheritanceInfo>*           inheritList;
  bool                                             inheritType;
  std::vector<std::string>*                        identifierList;
  std::vector<std::string>*                        funcThrowSpec;
  class CppTemplateArg*                            templateArg;
  cppast::CppAsmBlock*                             asmBlock;
  cppast::CppCompoundType                          compoundType;
  unsigned short                                   ptrLevel;
  cppast::CppRefType                               refType;
  unsigned int                                     attr;
  Optional<cppast::CppAccessType>                  objAccessType;
  cppast::CppExpression*                           attribSpecifier;
  cppast::CppCallArgs*                             attribSpecifiers;
  cppast::CppIfBlock*                              ifBlock;
  cppast::CppWhileBlock*                           whileBlock;
  cppast::CppDoWhileBlock*                         doWhileBlock;
  cppast::CppForBlock*                             forBlock;
  cppast::CppRangeForBlock*                        forRangeBlock;
  cppast::CppSwitchBlock*                          switchBlock;
  std::vector<cppast::CppCase>*                    switchBody;
  cppast::CppTryBlock*                             tryBlock;
  cppast::CppCatchBlock*                           catchBlock;
  cppast::CppPreprocessorDefine*                      hashDefine;
  cppast::CppPreprocessorUndef*                    hashUndef;
  cppast::CppPreprocessorInclude*                  hashInclude;
  cppast::CppPreprocessorImport*                   hashImport;
  cppast::CppPreprocessorConditional*              hashIf;
  cppast::CppPreprocessorError*                    hashError;
  cppast::CppPreprocessorWarning*                  hashWarning;
  cppast::CppPreprocessorPragma*                   hashPragma;
  cppast::CppReturnStatement*                      returnStmt;
  cppast::CppThrowStatement*                       throwStmt;
  cppast::CppGotoStatement*                        gotoStmt;
  cppast::CppBlob*                                 blob;
  cppast::CppLabel*                                label;
  cppast::CppVarInitInfo*                          cppVarInitInfo;
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
%token  <str>   tknLShift tknRShift tknLShiftEq tknRShiftEq tknCmpEq tknNotEq tknLessEq tknGreaterEq
%token  <str>   tkn3WayCmp tknAnd tknOr tknInc tknDec tknArrow tknArrowStar
%token  <str>   tknLT tknGT // We will need the position of these operators in stream when used for declaring template instance.
%token  <str>   '+' '-' '*' '/' '%' '^' '&' '|' '~' '!' '=' ',' '(' ')' '[' ']' ';' '.'
%token  <str>   tknNew tknDelete
%token  <str>   tknConst tknConstExpr // For templatearg parsing it is made as str type.
%token  <str>   tknVoid // For the cases when void is used as function parameter.
%token  <str>   tknOverride tknFinal // override, final are not a reserved keywords
%token  <str>   tknAsm
%token  <str>   tknBlob
%token  <str>   tknGoto

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
%type  <str>                identifier optidentifier numbertype typeidentifier varidentifier optname id name designatedname operfuncname funcname
%type  <str>                templidentifier templqualifiedid
%type  <str>                doccommentstr optdoccommentstr
%type  <str>                rshift
%type  <str>                macrocall
%type  <cppEntity>          stmt
%type  <typeModifier>       opttypemodifier typemodifier
%type  <cppEnum>            enumdefn enumfwddecl enumdefnstmt
%type  <enumItem>           enumitem
%type  <enumItemList>       enumitemlist
%type  <fwdDeclObj>         fwddecl
%type  <cppVarType>         vartype
%type  <cppVarObj>          vardecl varinit vardeclstmt
%type  <cppVarInitInfo>     varassign optvarassign
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
%type  <cppExprObj>         expr exprstmt optexpr lambdacapture captureallbyref captureallbyval exprorlist optexprorlist desinatedinitialization
%type  <exprList>           exprlist optexprlist
%type  <cppExprObj>         objcarg objcarglist
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
%type  <objAccessType>      protlevel
%type  <accessSpecifier>    entityaccessspecifier
%type  <identifierList>     identifierlist
%type  <funcThrowSpec>      functhrowspec optfuncthrowspec
%type  <attribSpecifier>    attribspecifier
%type  <attribSpecifiers>   attribspecifiers optattribspecifiers
%type  <hashDefine>         define
%type  <hashUndef>          undef
%type  <hashInclude>        include
%type  <hashImport>         import
%type  <hashIf>             hashif
%type  <hashError>          hasherror
%type  <hashWarning>        hashwarning
%type  <hashPragma>         pragma
%type  <returnStmt>         returnstmt
%type  <throwStmt>          throwstmt
%type  <gotoStmt>           gotostmt
%type  <cppEntity>          preprocessor

%type  <blob>               blob

%type  <label>              label

// precedence as mentioned at https://en.cppreference.com/w/cpp/language/operator_precedence
%left COMMA
// &=, ^=, |=, <<=, >>=, *=, /=, %=, +=, -=, =, throw, a?b:c
%right tknAndEq tknXorEq tknOrEq tknLShiftEq tknRShiftEq tknMulEq tknDivEq tknPerEq tknPlusEq tknMinusEq '=' tknThrow '?' TERNARYCOND tknReturn
%left tknOr
%left tknAnd
%left '|'
%left '^'
%left '&'
%left tknCmpEq tknNotEq // ==, !=
// tknLT and tknGT are used instead of '<', and '>' because otherwise parsing template and template args is very difficult.
%left tknLT tknGT tknLessEq tknGreaterEq
%left tkn3WayCmp       // <=>
%left  tknLShift tknRShift RSHIFT

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
progunit
  : optstmtlist [ZZLOG;] {
    gProgUnit = $$ = $1;
    if (gProgUnit)
      gProgUnit->compoundType(CppCompoundType::FILE);
    }
  ;

optstmtlist
  : [ZZLOG;] {
    $$ = nullptr;
  }
  | stmtlist [ZZLOG;] {
    $$ = $1;
  }
  ;

stmtlist
  : stmt [ZZLOG;] {
    $$ = new cppast::CppCompound();
    if ($1)
    {
      $$->add(Ptr($1));
    } // Avoid 'comment-btyacc-constructs.sh' to act on this
  }
  | stmtlist stmt [ZZLOG;] {
    $$ = ($1 == 0) ? new cppast::CppCompound() : $1;
    if ($2)
    {
        $$->add(Ptr($2));
    } // Avoid 'comment-btyacc-constructs.sh' to act on this
  }
  ;

stmt
  : vardeclstmt         [ZZLOG;] { $$ = $1; }
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
  | macrocall           [ZZLOG;] { $$ = new cppast::CppMacroCall($1); }
  | macrocall ';'       [ZZLOG;] { $$ = new cppast::CppMacroCall(MergeCppToken($1, $2)); }
  | apidecortokensq macrocall [ZZLOG;] { $$ = new cppast::CppMacroCall(MergeCppToken($1, $2)); }
  | ';'                 [ZZLOG;] { $$ = nullptr; }  /* blank statement */
  | asmblock            [ZZLOG;] { $$ = $1; }
  | blob                [ZZLOG;] { $$ = $1; }
  | label               [ZZLOG;] { $$ = $1; }
  | returnstmt          [ZZLOG;] { $$ = $1; }
  | throwstmt           [ZZLOG;] { $$ = $1; }
  | gotostmt            [ZZLOG;] { $$ = $1; }
  | entityaccessspecifier     [ZZLOG;] { $$ = $1; }
  ;

label
  : name ':'            [ZZLOG;] { $$ = new cppast::CppLabel($1); }
  ;

preprocessor
  : define              [ZZLOG;] { $$ = $1; }
  | undef               [ZZLOG;] { $$ = $1; }
  | include             [ZZLOG;] { $$ = $1; }
  | import              [ZZLOG;] { $$ = $1; }
  | hashif              [ZZLOG;] { $$ = $1; }
  | hasherror           [ZZLOG;] { $$ = $1; }
  | hashwarning         [ZZLOG;] { $$ = $1; }
  | pragma              [ZZLOG;] { $$ = $1; }
  ;

asmblock
  : tknAsm              [ZZLOG;] { $$ = new cppast::CppAsmBlock($1); }
  ;

macrocall
  : tknMacro [ZZLOG; $$ = $1;] {}
  | macrocall '(' ')' [ZZLOG; $$ = MergeCppToken($1, $3); ] {}
  | macrocall '(' expr ')' [
    ZZLOG;
    $$ = MergeCppToken($1, $4);
    delete $3;
  ] {}
  ;

switchstmt
  : tknSwitch '(' expr ')' '{' caselist '}' [ZZLOG;] {
    $$ = new cppast::CppSwitchBlock(Ptr($3), std::move(*Ptr($6)));
  }
  ;

caselist
  : [ZZLOG;] {
    $$ = new std::vector<cppast::CppCase>;
  }
  | caselist tknCase expr ':' optstmtlist [ZZLOG;] {
    $$ = $1;
    $$->emplace_back(Ptr($3), Ptr($5));
  }
  | caselist tknDefault ':' optstmtlist [ZZLOG;] {
    $$ = $1;
    $$->emplace_back(nullptr, Ptr($4));
  }
  | doccommentstr caselist [ZZLOG;] { $$ = $2; }
  | caselist doccommentstr [ZZLOG;] { $$ = $1; }
  ;

block
  : '{' optstmtlist '}' [ZZLOG;] {
    $$ = $2;
    if ($$ == nullptr)
      $$ = new cppast::CppCompound(CppCompoundType::BLOCK);
    else
      $$->compoundType(CppCompoundType::BLOCK);
  }
  | doccomment block [ZZLOG;] {
    $$ = $2;
  }
  ;

ifblock
  : tknIf '(' expr ')' stmt [ZZLOG;] {
    $$ = new cppast::CppIfBlock(Ptr($3), Ptr($5));
  }
  | tknIf '(' expr ')' stmt tknElse stmt [ZZLOG;] {
    $$ = new cppast::CppIfBlock(Ptr($3), Ptr($5), Ptr($7));
  }
  | tknIf '(' varinit ')' stmt [ZZLOG;] {
    $$ = new cppast::CppIfBlock(Ptr($3), Ptr($5));
  }
  | tknIf '(' varinit ')' stmt tknElse stmt [ZZLOG;] {
    $$ = new cppast::CppIfBlock(Ptr($3), Ptr($5), Ptr($7));
  }
  /* TODO: Add support for else-if: compare the if.cpp file and its output by e2e test. */
  ;

whileblock
  : tknWhile '(' expr ')' stmt [ZZLOG;] {
    $$ = new cppast::CppWhileBlock(Ptr($3), Ptr($5));
  }
  | tknWhile '(' varinit ')' stmt [ZZLOG;] {
    $$ = new cppast::CppWhileBlock(Ptr($3), Ptr($5));
  }
  ;

dowhileblock
  : tknDo stmt tknWhile '(' expr ')' [ZZLOG;] {
    $$ = new cppast::CppDoWhileBlock(Ptr($5), Ptr($2));
  }
  ;

forblock
  : tknFor '(' optexprorlist ';' optexprorlist ';' optexprorlist ')' stmt [ZZLOG;] {
    $$ = new cppast::CppForBlock(Ptr($3), Ptr($5), Ptr($7), Ptr($9));
  }
  | tknFor '(' varinit ';' optexprorlist ';' optexprorlist ')' stmt [ZZLOG;] {
    $$ = new cppast::CppForBlock(Ptr($3), Ptr($5), Ptr($7), Ptr($9));
  }
  | tknFor '(' vardecllist ';' optexprorlist ';' optexprorlist ')' stmt [ZZLOG;] {
    $$ = new cppast::CppForBlock(Ptr($3), Ptr($5), Ptr($7), Ptr($9));
  }
  ;

forrangeblock
  : tknFor '(' vardecl ':' expr ')' stmt [ZZLOG;] {
    $$ = new cppast::CppRangeForBlock(Ptr($3), Ptr($5), Ptr($7));
  }
  ;

tryblock
  : tknTry block catchblock [ZZLOG;] {
    $$ = new cppast::CppTryBlock(Ptr($2), Ptr($3));
  }
  | tryblock catchblock [ZZLOG;] {
    $$ = $1;
    $$->addCatchBlock(Ptr($2));
  }
  ;

catchblock
  : tknCatch '(' vartype optname ')' block [ZZLOG;] {
    $$ = new cppast::CppCatchBlock{Ptr($3), $4, Ptr($6)};
  }
  ;

optexpr
  : {
    $$ = nullptr;
  }
  | expr [ZZLOG;] {
    $$ = $1;
  }
  /* | exprlist [ZZLOG;] {
    $$ = $1;
  } */
  ;

define
  : tknPreProHash tknDefine name name [ZZLOG;] {
    $$ = new cppast::CppPreprocessorDefine(cppast::CppPreprocessorDefineType::RENAME, $3, $4);
  }
  | tknPreProHash tknDefine name [ZZLOG;] {
    $$ = new cppast::CppPreprocessorDefine(cppast::CppPreprocessorDefineType::RENAME, $3);
  }
  | tknPreProHash tknDefine name tknNumber [ZZLOG;] {
    $$ = new cppast::CppPreprocessorDefine(cppast::CppPreprocessorDefineType::NUMBER, $3, $4);
  }
  | tknPreProHash tknDefine name tknStrLit [ZZLOG;] {
    $$ = new cppast::CppPreprocessorDefine(cppast::CppPreprocessorDefineType::STRING, $3, $4);
  }
  | tknPreProHash tknDefine name tknCharLit [ZZLOG;] {
    $$ = new cppast::CppPreprocessorDefine(cppast::CppPreprocessorDefineType::CHARACTER, $3, $4);
  }
  | tknPreProHash tknDefine name tknPreProDef [ZZLOG;] {
    $$ = new cppast::CppPreprocessorDefine(cppast::CppPreprocessorDefineType::COMPLEX_DEFN, $3, $4);
  }
  ;

undef
  : tknPreProHash tknUndef name                 [ZZLOG;]  { $$ = new cppast::CppPreprocessorUndef($3); }
  ;

include
  : tknPreProHash tknInclude tknStrLit          [ZZLOG;]  { $$ = new cppast::CppPreprocessorInclude($3); }
  | tknPreProHash tknInclude tknStdHdrInclude   [ZZLOG;]  { $$ = new cppast::CppPreprocessorInclude($3); }
  ;

import
  : tknPreProHash tknImport tknStrLit           [ZZLOG;]  { $$ = new cppast::CppPreprocessorImport($3); }
  | tknPreProHash tknImport tknStdHdrInclude    [ZZLOG;]  { $$ = new cppast::CppPreprocessorImport($3); }
  ;

hashif
  : tknPreProHash tknIf tknPreProDef            [ZZLOG;]  { $$ = new cppast::CppPreprocessorConditional(PreprocessorConditionalType::IF,      $3); }
  | tknPreProHash tknIfDef name                 [ZZLOG;]  { $$ = new cppast::CppPreprocessorConditional(PreprocessorConditionalType::IFDEF,   $3); }
  | tknPreProHash tknIfNDef name                [ZZLOG;]  { $$ = new cppast::CppPreprocessorConditional(PreprocessorConditionalType::IFNDEF,  $3); }
  | tknPreProHash tknIfNDef tknApiDecor         [ZZLOG;]  { $$ = new cppast::CppPreprocessorConditional(PreprocessorConditionalType::IFNDEF,  $3); }
  | tknPreProHash tknElse                       [ZZLOG;]  { $$ = new cppast::CppPreprocessorConditional(PreprocessorConditionalType::ELSE       ); }
  | tknPreProHash tknElIf  tknPreProDef         [ZZLOG;]  { $$ = new cppast::CppPreprocessorConditional(PreprocessorConditionalType::ELIF,    $3); }
  | tknPreProHash tknEndIf                      [ZZLOG;]  { $$ = new cppast::CppPreprocessorConditional(PreprocessorConditionalType::ENDIF      ); }
  ;

hasherror
  : tknPreProHash tknHashError                  [ZZLOG;]  { $$ = new cppast::CppPreprocessorError($2); }
  | tknPreProHash tknHashError strlit           [ZZLOG;]  { $$ = new cppast::CppPreprocessorError(MergeCppToken($2, $3)); }
  ;

hashwarning
  : tknPreProHash tknHashWarning                [ZZLOG;]  { $$ = new cppast::CppPreprocessorWarning($2); }
  | tknPreProHash tknHashWarning strlit         [ZZLOG;]  { $$ = new cppast::CppPreprocessorWarning(MergeCppToken($2, $3)); }
  ;

pragma
  : tknPreProHash tknPragma tknPreProDef        [ZZLOG;]  { $$ = new cppast::CppPreprocessorPragma($3); }
  ;

doccomment
  : doccommentstr                               [ZZLOG;]  { $$ = new cppast::CppDocumentationComment((std::string) $1); }
  ;

optdoccommentstr
  :               [ZZLOG;] { $$ = CppToken{nullptr, 0}; }
  | doccommentstr [ZZLOG;] { $$ = $1; }
  ;

doccommentstr
  : tknFreeStandingBlockComment                          [ZZLOG;]  { $$ = $1; }
  | tknFreeStandingLineComment                           [ZZLOG;]  { $$ = $1; }
  | doccommentstr tknFreeStandingBlockComment            [ZZLOG;]  { $$ = MergeCppToken($1, $2); }
  | doccommentstr tknFreeStandingLineComment             [ZZLOG;]  { $$ = MergeCppToken($1, $2); }
  ;

identifier
  : name                                          [ZZLOG; $$ = $1; ] {}
  | identifier tknScopeResOp identifier           [ZZLOG; $$ = MergeCppToken($1, $3); ] {}
  | id                                            [ZZLOG; $$ = $1; ] {}
  | templidentifier                               [ZZLOG; $$ = $1; ] {}
  | tknOverride                                   [ZZLOG; $$ = $1;] { /* override is not a reserved keyword */ }
  | identifier tknEllipsis                        [ZZLOG; $$ = MergeCppToken($1, $2); ] {}
  | macrocall                                     [ZZLOG; $$ = $1; ] {}
  | templqualifiedid                              [ZZLOG; $$ = $1; ] {}
  ;

numbertype
  : tknInteger                            [ZZLOG;] { $$ = $1; }
  | tknFloat                              [ZZLOG;] { $$ = $1; }
  | tknDouble                             [ZZLOG;] { $$ = $1; }
  | tknChar                               [ZZLOG;] { $$ = $1; }
  | tknNumSignSpec                        [ZZLOG;] { $$ = $1; }
  | tknNumSignSpec numbertype             [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  ;

typeidentifier
  : identifier                            [ZZLOG;] { $$ = $1; }
  | tknScopeResOp identifier %prec GLOBAL [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | typeidentifier tknScopeResOp typeidentifier [ZZLOG;] { $$ = MergeCppToken($1, $3); }
  | numbertype                            [ZZLOG;] { $$ = $1; }
  | typeidentifier '[' ']'                [ZZLOG;] { $$ = MergeCppToken($1, $3); }
  | tknAuto                               [ZZLOG;] { $$ = $1; }
  | tknVoid                               [ZZLOG;] { $$ = $1; }
  | tknEnum  identifier                   [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknTypename identifier  [
                    if (gTemplateParamStart == $1.sz)
                      ZZERROR;
                    else
                      ZZLOG;
                  ]                                       [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknEllipsis                           [ZZLOG;] { $$ = $1; }
  | tknTypename tknEllipsis               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknClass tknEllipsis                  [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | typeidentifier tknEllipsis            [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknDecltype '(' expr ')'              [ZZLOG;] { $$ = MergeCppToken($1, $4); delete $3; }
  ;

templidentifier
  : identifier tknLT templatearglist tknGT    [ZZLOG; $$ = MergeCppToken($1, $4); ] {}
// The following rule is needed to parse an ambiguous input as template identifier,
// see the test "vardecl-or-expr-ambiguity".
  | identifier tknLT expr tknNotEq expr tknGT [ZZLOG; $$ = MergeCppToken($1, $6); ] {}
// The following rule is needed to parse a template identifier which otherwise fails to parse
// because of higher precedence of tknLT and tknGT,
// see the test "C<Class, v != 0> x;".
  | identifier tknLT templatearglist ',' expr tknNotEq expr tknGT [ZZLOG; $$ = MergeCppToken($1, $8); ] {}
  ;

templqualifiedid
  : tknTemplate templidentifier               [ZZLOG; $$ = MergeCppToken($1, $2); ] {}
  ;

name
  : tknName  [ZZLOG; $$ = $1;] {}
  ;

designatedname
  : '.' name [ZZLOG;] {$$ = MergeCppToken($1, $2);}
  ;

id
  : tknID  [ZZLOG; $$ = $1; ] {}
  ;

optname
  :         [ZZLOG;] { $$ = MakeCppToken(nullptr, nullptr); }
  | name    [ZZLOG;] { $$ = $1; }

optidentifier
  :             [ZZLOG;] { $$ = MakeCppToken(nullptr, nullptr); }
  | identifier  [ZZLOG;] { $$ = $1; }
  ;

enumitem
  : name            [ZZLOG;]   { $$ = new cppast::CppEnumItem($1); }
  | name '=' expr   [ZZLOG;]   { $$ = new cppast::CppEnumItem($1, Ptr($3)); }
  | doccomment      [ZZLOG;]   { $$ = new cppast::CppEnumItem(Ptr($1)); }
  | preprocessor    [ZZLOG;]   { $$ = new cppast::CppEnumItem(Ptr($1)); }
  | macrocall       [ZZLOG;]   { $$ = new cppast::CppEnumItem(Ptr(new cppast::CppMacroCall($1))); }
  | blob            [ZZLOG;]   { $$ = new cppast::CppEnumItem(Ptr($1)); }
  ;

blob
  : tknBlob      [ZZLOG;]   { $$ = new cppast::CppBlob($1); }
  ;

enumitemlist
  :                           [ZZLOG;] { $$ = 0; }
  | enumitemlist enumitem [ZZLOG;] {
    $$ = $1 ? $1 : new std::list<cppast::CppEnumItem>;
    $$->push_back(Obj($2));
  }
  | enumitemlist ',' enumitem [ZZLOG;] {
    $$ = $1 ? $1 : new std::list<cppast::CppEnumItem>;
    $$->push_back(Obj($3));
  }
  | enumitemlist ',' [ZZLOG;] {
    $$ = $1;
  }
  ;

enumdefn
  : tknEnum optname '{' enumitemlist '}' [ZZVALID;] {
    $$ = new cppast::CppEnum($2, Obj($4));
  }
  | tknEnum optapidecor name ':' typeidentifier '{' enumitemlist '}' [ZZVALID;] {
    $$ = new cppast::CppEnum($3, Obj($7), false, $5);
  };
  | tknEnum ':' typeidentifier '{' enumitemlist '}' [ZZVALID;] {
    $$ = new cppast::CppEnum("", Obj($5), false, $3);
  };
  | tknEnum optapidecor name '{' enumitemlist '}' [ZZVALID;] {
    $$ = new cppast::CppEnum($3, Obj($5), false);
  };
  | tknEnum tknClass optapidecor name ':' typeidentifier '{' enumitemlist '}' [ZZVALID;] {
    $$ = new cppast::CppEnum($4, Obj($8), true, $6);
  }
  | tknEnum tknClass optapidecor name '{' enumitemlist '}' [ZZVALID;] {
    $$ = new cppast::CppEnum($4, Obj($6), true);
  }
  | tknTypedef tknEnum optapidecor optname '{' enumitemlist '}' name [ZZVALID;] {
    $$ = new cppast::CppEnum($8, Obj($6));
  }
  ;

enumdefnstmt
  : enumdefn ';' [ZZLOG;] { $$ = $1; }
  ;

enumfwddecl
  : tknEnum name ':' typeidentifier ';' [ZZVALID;] {
    $$ = new cppast::CppEnum($2, {}, false, $4);
  }
  | tknEnum tknClass name ':' typeidentifier ';' [ZZVALID;] {
    $$ = new cppast::CppEnum($3, {}, true, $5);
  }
  | tknEnum tknClass name ';' [ZZVALID;] {
    $$ = new cppast::CppEnum($3, {}, true);
  }
  ;

funcptrtypedef
  : tknTypedef functionpointer ';' [ZZVALID;] {
    $2->addAttr(TYPEDEF);
    $$ = $2;
  }

typedefnamestmt
  : typedefname ';'     [ZZVALID;] { $$ = $1; }
  ;

typedefliststmt
  : typedeflist ';'     [ZZVALID;] { $$ = $1; }
  ;

typedeflist
  : tknTypedef vardecllist  [ZZLOG;] { $$ = new cppast::CppTypedefList(Ptr($2)); }
  ;

typedefname
  : tknTypedef vardecl      [ZZLOG;] { $$ = new cppast::CppTypedefName(Ptr($2)); }
  ;

usingdecl
  : tknUsing name '=' vartype ';' [ZZLOG;] {
    $$ = new cppast::CppUsingDecl($2, Ptr($4));
  }
  | tknUsing name '=' functionptrtype ';' [ZZLOG;] {
    $$ = new cppast::CppUsingDecl($2, Ptr($4));
  }
  | tknUsing name '=' funcobj ';' [ZZLOG;] {
    $$ = new cppast::CppUsingDecl($2, Ptr($4));
  }
  | tknUsing name '=' classdefn ';' [ZZLOG;] {
    $$ = new cppast::CppUsingDecl($2, Ptr($4));
  }
  | templatespecifier usingdecl [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  | tknUsing identifier ';' [ZZLOG;] {
    $$ = new cppast::CppUsingDecl($2);
  }
  ;

namespacealias
  : tknNamespace name '=' identifier ';' [ZZLOG;] {
    $$ = new cppast::CppNamespaceAlias($2, $4);
  }
  ;

usingnamespacedecl
  : tknUsing tknNamespace identifier ';' [ZZLOG;] {
    $$ = new cppast::CppUsingNamespaceDecl($3);
  }
  ;

vardeclliststmt
  : vardecllist ';' [ZZVALID;] { $$ = $1; }
  | exptype vardecllist ';' [ZZVALID;] { $$ = $2; }
  ;

vardeclstmt
  : vardecl ';'                   [ZZVALID;] { $$ = $1; }
  | varinit ';'                   [ZZVALID;] { $$ = $1; }
  | apidecor vardeclstmt          [ZZVALID;] { $$ = $2; $$->apidecor($1); }
  | exptype vardeclstmt           [ZZVALID;] { $$ = $2; $$->addAttr($1); }
  | varattrib vardeclstmt         [ZZVALID;] { $$ = $2; $$->addAttr($1); }
  ;

vardecllist
  : optfunctype varinit ',' opttypemodifier name optvarassign [ZZLOG;] {
    $2->addAttr($1);
    $$ = new cppast::CppVarList($2, CppVarDeclInList($4, VarDecl($5, $6)));
  }
  | optfunctype vardecl ',' opttypemodifier name optvarassign [ZZLOG;] {
    $2->addAttr($1);
    $$ = new cppast::CppVarList($2, CppVarDeclInList($4, VarDecl($5, $6)));
  }
  | optfunctype vardecl ',' opttypemodifier name '[' expr ']' [ZZLOG;] {
    $2->addAttr($1);
    CppVarDecl var2($5);
    var2.addArraySize($7);
    $$ = new cppast::CppVarList($2, CppVarDeclInList($4, std::move(var2)));
  }
  | vardecllist ',' opttypemodifier name '[' expr ']' [ZZLOG;] {
    $$ = $1;
    CppVarDecl var2($4);
    var2.addArraySize($6);
    $$->addVarDecl(CppVarDeclInList($3, std::move(var2)));
  }
  | optfunctype vardecl ',' opttypemodifier name ':' expr [ZZLOG;] {
    $2->addAttr($1);
    $$ = new cppast::CppVarList($2, CppVarDeclInList($4, CppVarDecl{$5}));
    /* TODO: Use optvarassign as well */
  }
  | vardecllist ',' opttypemodifier name optvarassign [ZZLOG;] {
    $$ = $1;
    $$->addVarDecl(CppVarDeclInList($3, VarDecl($4, $5)));
  }
  | vardecllist ',' opttypemodifier name optvarassign ':' expr [ZZLOG;] {
    $$ = $1;
    $$->addVarDecl(CppVarDeclInList($3, VarDecl($4, $5)));
    /* TODO: Use optvarassign as well */
  }
  ;

varinit
  : vardecl '(' typeidentifier '*' name      [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
  | vardecl '(' typeidentifier '*' '*' name  [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
  | vardecl '(' typeidentifier '*' '&' name  [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
  | vardecl '(' typeidentifier '&' name      [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
  | vardecl '(' typeidentifier tknAnd name   [gParamModPos = $4.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
  | vardecl '(' typeidentifier ')'           [gParamModPos = $3.sz; ZZERROR;] { /*FuncDeclHack*/ $$ = nullptr; }
  | vardecl '(' ')'                          [ZZERROR;]                       { /*FuncDeclHack*/ $$ = nullptr; }
  | vardecl varassign [ZZLOG;] {
    $$ = $1;
    $$->initialize(Obj($2));
  }
  | tknConstExpr varinit [ZZLOG;] {
    $$ = $2;
    $$->addAttr(CONST_EXPR);
  }
  ;

varassign
  : '=' expr [ZZLOG;] {
                    $$ = VarInitInfo($2);
  }
  | '(' exprlist ')' [ZZLOG;] {
                    $$ = VarInitInfo($2, CppConstructorCallStyle::USING_PARENTHESES);
  }
  | '{' optexprlist '}' [ZZLOG;] {
                    $$ = VarInitInfo($2, CppConstructorCallStyle::USING_BRACES);
  }
  ;

optvarassign
  :                     [ZZLOG;]  { $$ = nullptr; }
  | varassign           [ZZLOG;]  { $$ = $1; }
  ;

vardecl
  : vartype varidentifier       [ZZLOG;]         {
    $$ = new cppast::CppVar($1, $2.toString());
  }
  | vartype apidecor varidentifier       [ZZLOG;]         {
    $$ = new cppast::CppVar($1, $3.toString());
    $$->apidecor($2);
  }
  | functionpointer [ZZLOG;] {
    $$ = new cppast::CppVar($1, CppTypeModifier());
  }
  | vardecl '[' expr ']' [ZZLOG;] {
    $$ = $1;
    $$->addArraySize($3);
  }
  | vardecl '[' ']' [ZZLOG;] {
    $$ = $1;
    $$->addArraySize(nullptr);
  }
  | vardecl ':' expr [ZZLOG;] {
    $$ = $1;
    $$->bitField(Ptr($3));
  }
  | templatespecifier vardecl [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  | varattrib vardecl [ZZLOG;] {
    $$ = $2;
    $$->addAttr($1);
  }
  ;

vartype
  : attribspecifiers typeidentifier opttypemodifier [ZZLOG;] {
    $$ = new cppast::CppVarType($2, $3);
    $$->attribSpecifierSequence(Obj($1));
  }
  | typeidentifier opttypemodifier [ZZLOG;] {
    $$ = new cppast::CppVarType($1, $2);
  }
  | tknClass identifier opttypemodifier [
    if (gTemplateParamStart == $1.sz)
      ZZERROR;
    else
      ZZLOG;
  ] {
    $$ = new cppast::CppVarType(MergeCppToken($1, $2), $3);
  }
  | tknClass optapidecor identifier opttypemodifier [ZZLOG;] {
    $$ = new cppast::CppVarType(MergeCppToken($1, $3), $4);
  }
  | tknStruct optapidecor identifier opttypemodifier [ZZLOG;] {
    $$ = new cppast::CppVarType(MergeCppToken($1, $3), $4);
  }
  | tknUnion identifier opttypemodifier [ZZLOG;] {
    $$ = new cppast::CppVarType(MergeCppToken($1, $2), $3);
  }
  | functionptrtype [ZZLOG;] {
    $$ = new cppast::CppVarType($1, CppTypeModifier());
  }
  | classdefn [ZZLOG;] {
    $$ = new cppast::CppVarType($1, CppTypeModifier());
  }
  | classdefn typemodifier [ZZLOG;] {
    $$ = new cppast::CppVarType($1, $2);
  }
  | enumdefn [ZZLOG;] {
    $$ = new cppast::CppVarType($1, CppTypeModifier());
  }
  | enumdefn typemodifier [ZZLOG;] {
    $$ = new cppast::CppVarType($1, $2);
  }
  | varattrib vartype [ZZLOG;] {
    $$ = $2;
    $$->addAttr($1);
  }
  | vartype tknEllipsis [ZZLOG;] {
    $$ = $1;
    $$->parameterPack(true);
  }
  | typeidentifier typeidentifier tknScopeResOp typemodifier [ZZLOG;] {
    // reference to member declrations. E.g.:
    // int GrCCStrokeGeometry::InstanceTallies::* InstanceType
    $$ = new cppast::CppVarType(MergeCppToken($1, $3), $4);
  }
  ;

varidentifier
  : identifier          [ZZLOG;]  { $$ = $1; }
  | tknFinal            [ZZLOG;]  { $$ = $1; /* final is not a reserved keyword */ }
  | '(' '&' name ')'      [ZZLOG;]  { $$ = MergeCppToken($1, $4); }
  | '(' '*' name ')'      [ZZLOG;]  { $$ = MergeCppToken($1, $4); }
  | '(' '*' '*' name ')'  [ZZLOG;]  { $$ = MergeCppToken($1, $5); }
  ;

opttypemodifier
  : [ZZLOG;] { $$ = CppTypeModifier(); }
  | typemodifier { $$ = $1; }
  | doccomment opttypemodifier { $$ = $2; }
  ;

typemodifier
  : tknConst [ZZLOG;] {
    $$ = CppTypeModifier();
    $$.constBits_ |= (1 << $$.ptrLevel_);
  }
  | '*' %prec PTRDECL [ZZLOG;] {
    $$ = CppTypeModifier();
    $$.ptrLevel_++;
  }
  | '&' %prec REFDECL [ZZLOG;] {
    $$ = CppTypeModifier();
    $$.refType_ = CppRefType::BY_REF;
  }
  | tknAnd %prec REFDECL [ZZLOG;] {
    $$ = CppTypeModifier();
    $$.refType_ = CppRefType::RVAL_REF;
  }
  | typemodifier tknConst [ZZLOG;] {
    $$ = $1;
    $$.constBits_ |= (1 << $$.ptrLevel_);
  }
  | typemodifier '*' %prec PTRDECL [ZZLOG;] {
    $$ = $1;
    $$.ptrLevel_++;
  }
  | typemodifier '&' %prec REFDECL [ZZLOG;] {
    $$ = $1;
    $$.refType_ = CppRefType::BY_REF;
  }
  | typemodifier tknAnd %prec REFDECL [ZZLOG;] {
    $$ = $1;
    $$.refType_ = CppRefType::RVAL_REF;
  }

  ;

exptype
  : tknStatic    [ZZLOG;] { $$ = STATIC; }
  | tknExtern    [ZZLOG;] { $$ = EXTERN; }
  | tknExternC   [ZZLOG;] { $$ = EXTERN_C; }
  ;

varattrib
  : tknConst     [ZZLOG;] { $$ = CONST; }
  | tknVolatile  [ZZLOG;] { $$ = VOLATILE; }
  | tknMutable   [ZZLOG;] { $$ = MUTABLE; }
  | tknConstExpr [ZZLOG;] { $$ = CONST_EXPR; }
  ;

typeconverter
  : tknOperator vartype '(' optvoid ')' [ZZLOG;] {
    $$ = new cppast::CppTypeConverter($2, MakeCppToken($1.sz, $3.sz));
  }
  | identifier tknScopeResOp tknOperator vartype '(' optvoid ')' [ZZLOG;] {
    $$ = new cppast::CppTypeConverter($4, MakeCppToken($1.sz, $5.sz));
  }
  | functype typeconverter [ZZLOG;] {
    $$ = $2;
    $$->addAttr($1);
  }
  | typeconverter tknConst [ZZLOG;] {
    $$ = $1;
    $$->addAttr(CONST);
  }
  | apidecor typeconverter [ZZLOG;] {
    $$ = $2;
    $$->decor1($1);
  }
  | templatespecifier typeconverter [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  ;

typeconverterstmt
  : typeconverter ';' [ZZVALID;] {
    $$ = $1;
  }
  | typeconverter block [ZZVALID;] {
    $$ = $1;
    $$->defn(Ptr($2));
  }
  ;

funcdeclstmt
  : funcdecl ';' [ZZVALID;] { $$ = $1; }
  ;

funcdefn
  : funcdecl block [ZZVALID;] {
    $$ = $1;
    $$->defn(Ptr($2 ? $2 : new cppast::CppCompound(CppCompoundType::BLOCK)));
  }
  ;

lambda
  : '[' lambdacapture ']' lambdaparams block {
    $$ = new cppast::CppLambda(Ptr($2), Obj($4), Ptr($5));
  }
  | '[' lambdacapture ']' lambdaparams tknArrow vartype block {
    $$ = new cppast::CppLambda(Ptr($2), Obj($4), Ptr($7), Ptr($6));
  }
  ;

lambdaparams
  :                   [ZZLOG;] { $$ = nullptr; }
  | '(' paramlist ')' [ZZLOG;] { $$ = $2; }
  ;

funcptrortype
  : functype vartype '(' optapidecor identifier tknScopeResOp '*' optname ')' '(' paramlist ')' [ZZVALID;] {
    $$ = new cppast::CppFunctionPointer($8, Ptr($2), Obj($11), $1, MergeCppToken($5, $6));
    $$->decor2($4);
  }
  | vartype '(' optapidecor identifier tknScopeResOp '*' optname ')' '(' paramlist ')' [ZZVALID;] {
    $$ = new cppast::CppFunctionPointer($7, Ptr($1), Obj($10), 0, MergeCppToken($4, $5));
    $$->decor2($3);
  }
  | functype vartype '(' optapidecor '*' optname ')' '(' paramlist ')' [ZZVALID;] {
    $$ = new cppast::CppFunctionPointer($6, Ptr($2), Obj($9), $1);
    $$->decor2($4);
  }
  | vartype '(' optapidecor '*' optname ')' '(' paramlist ')' [ZZVALID;] {
    $$ = new cppast::CppFunctionPointer($5, Ptr($1), Obj($8), 0);
    $$->decor2($3);
  }
  | vartype '(' '*'  apidecor optname ')' '(' paramlist ')' [ZZVALID;] {
    $$ = new cppast::CppFunctionPointer($5, Ptr($1), Obj($8), 0);
    $$->decor2($4);
  }
  | apidecor funcptrortype [ZZVALID;] {
    $$ = $2;
    $$->decor1($1);
  }
  | funcptrortype optfuncattrib [ZZVALID;] {
    $$ = $1;
    $$->addAttr($2);
  }
  ;

functionpointer
  : funcptrortype
  [
    if ($1->name().empty() == true) {
      ZZERROR;
    }
  ]
  ;

functionptrtype
  : funcptrortype
  [
    if ($1->name().empty() == false) {
      ZZERROR;
    }
  ]
  ;

funcobj
  : vartype optapidecor '(' paramlist ')' [ZZLOG;] {
    $$ = new cppast::CppFunctionPointer("", Ptr($1), Obj($4), 0);
  }
  ;

funcpointerdecl
  : functionpointer ';' [ZZVALID;] { $$ = $1; }
  ;

funcdecldata
  : funcname '(' paramlist ')' [ZZLOG;] {
    $$ = CppFunctionData{$1, $3, 0};
  }
  | funcname '(' paramlist ')' optfuncattrib [ZZLOG;] {
    $$ = CppFunctionData{$1, $3, $5};
  }
  ;

funcdecl
  : vartype apidecor funcdecldata [ZZVALID;] {
    $$ = new cppast::CppFunction($3.funcName, Ptr($1), Obj($3.paramList), $3.funcAttr);
    $$->decor2($2);
  }
  | vartype funcdecldata [ZZVALID;] {
    $$ = new cppast::CppFunction($2.funcName, Ptr($1), Obj($2.paramList), $2.funcAttr);
  }
  | vartype tknConstExpr funcdecldata [ZZVALID;] {
    $$ = new cppast::CppFunction($3.funcName, Ptr($1), Obj($3.paramList), $3.funcAttr | CONST_EXPR);
  }
  | tknAuto funcdecldata tknArrow vartype [ZZVALID;] {
    $$ = new cppast::CppFunction($2.funcName, Ptr($4), Obj($2.paramList), $2.funcAttr | TRAILING_RETURN);
  }
  | tknAuto tknConstExpr funcdecldata tknArrow vartype [ZZVALID;] {
    $$ = new cppast::CppFunction($3.funcName, Ptr($5), Obj($3.paramList), $3.funcAttr | TRAILING_RETURN | CONST_EXPR);
  }
  | tknConstExpr funcdecl [ZZLOG;] {
    $$ = $2;
    $$->addAttr(CONST_EXPR);
  }
  | apidecor funcdecl [ZZLOG;] {
    $$ = $2;
    if (!$$->decor1().empty())
      $$->decor2($$->decor1());
    $$->decor1($1);
  }
  | templatespecifier funcdecl [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  | functype funcdecl [ZZLOG;] {
    $$ = $2;
    $$->addAttr($1);
  }
  | funcdecl '=' tknDelete [ZZLOG;] {
    $$ = $1;
    $$->addAttr(DELETE);
  }
  | funcdecl '=' tknDefault [ZZLOG;] {
    $$ = $1;
    $$->addAttr(DEFAULT);
  }
  | funcdecl functhrowspec [ZZLOG;] {
    $$ = $1;
    $$->throwSpec(Obj($2));
  }
  ;

funcobjstr
  : typeidentifier optapidecor '(' paramlist ')' [ZZLOG;] {
    delete $4;
    $$ = MergeCppToken($1, $5);
  }
  ;

funcname
  : operfuncname                          [ZZLOG;] { $$ = $1; }
  | typeidentifier                        [ZZLOG;] { $$ = $1; }
  | tknScopeResOp operfuncname            [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  /* final can be a function name too, see SkOpSpan.h :| */
  | tknFinal                              [ZZLOG;] { $$ = $1; }
  ;

rshift
  : tknGT tknGT %prec RSHIFT [ if ($2.sz != ($1.sz + 1)) ZZERROR; ] { $$ = MergeCppToken($1, $2); }
  ;

operfuncname
  : tknOperator '+'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '-'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '*'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '/'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '%'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '^'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '&'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '|'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '~'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '!'               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '='               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknLT             [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknGT             [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknPlusEq         [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknMinusEq        [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknMulEq          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknDivEq          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknPerEq          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknXorEq          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknAndEq          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknOrEq           [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknLShift         [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknRShift         [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknLShiftEq       [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknRShiftEq       [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknCmpEq          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknNotEq          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknLessEq         [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknGreaterEq      [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tkn3WayCmp        [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknAnd            [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknOr             [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknInc            [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknDec            [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator ','               [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknArrow          [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknArrowStar      [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator '(' ')'           [ZZLOG;] { $$ = MergeCppToken($1, $3); }
  | tknOperator '[' ']'           [ZZLOG;] { $$ = MergeCppToken($1, $3); }
  | tknOperator tknNew            [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknNew '[' ']'    [ZZLOG;] { $$ = MergeCppToken($1, $4); }
  | tknOperator tknDelete         [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator tknDelete '[' ']' [ZZLOG;] { $$ = MergeCppToken($1, $4); }
  | tknOperator typeidentifier    [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknOperator typeidentifier '*'       [ZZLOG;] { $$ = MergeCppToken($1, $3); }
  | identifier tknScopeResOp operfuncname [ZZLOG;] { $$ = MergeCppToken($1, $3); }

  /* see https://en.cppreference.com/w/cpp/language/user_literal */
  | tknOperator tknStrLit name      [ZZLOG;] { $$ = MergeCppToken($1, $3); }

  /* To fix something like:
      friend void* operator new<T>(size_t, GrTAllocator*);
  */
  | operfuncname tknLT templatearglist tknGT [ZZLOG;] { $$ = MergeCppToken($1, $4); }
  ;

paramlist
  : [ZZLOG;] {
    $$ = new std::vector<std::unique_ptr<const cppast::CppEntity>>;
  }
  | param [ZZLOG;] {
    $$ = new std::vector<std::unique_ptr<const cppast::CppEntity>>;
    $$->emplace_back($1);
  }
  | paramlist ',' param [ZZLOG;] {
    $1->emplace_back($3);
    $$ = $1;
  }
  ;

param
  : varinit                        [ZZLOG;] { $$ = $1; $1->addAttr(FUNC_PARAM); }
  | vartype '=' expr [ZZLOG;] {
    auto var = new cppast::CppVar($1, std::string());
    var->addAttr(FUNC_PARAM);
    var->initialize(Ptr($3));
    $$ = var;
  }
  | vardecl                         [ZZLOG;] { $$ = $1; $1->addAttr(FUNC_PARAM); }
  | vartype [ZZLOG;] {
    auto var = new cppast::CppVar($1, std::string());
    var->addAttr(FUNC_PARAM);
    $$ = var;
  }
  | funcptrortype                   [ZZLOG;] { $$ = $1; $1->addAttr(FUNC_PARAM); }
  | doccomment param                [ZZLOG;] { $$ = $2; }
  | vartype '[' expr ']' [ZZLOG;] {
    auto var = new cppast::CppVar($1, std::string());
    var->addAttr(FUNC_PARAM);
    var->addArraySize($3);
    $$ = var;
  }
  | vartype '[' ']' [ZZLOG;] {
    auto var = new cppast::CppVar($1, std::string());
    var->addAttr(FUNC_PARAM);
    var->addArraySize(nullptr);
    $$ = var;
  }
  ;

templatearg
  :                 [ZZLOG; $$ = nullptr;] { /*$$ = MakeCppToken(nullptr, nullptr);*/ }
  | vartype         [ZZLOG; $$ = nullptr;] { /*$$ = MergeCppToken($1, $2);*/ }
  | funcobjstr      [ZZLOG; $$ = nullptr;] { /*$$ = $1;*/ }
  | expr            [ZZLOG; $$ = nullptr;] {}
  ;

templatearglist
  : templatearg                      [ZZLOG; $$ = $1; ] {}
  | templatearglist ',' templatearg   [ZZLOG; $$ = $1;] { /*$$ = MergeCppToken($1, $3);*/ }
  | templatearglist ',' doccomment templatearg   [ZZLOG; $$ = $1;] { /*$$ = MergeCppToken($1, $3);*/ }
  ;

functype
  : exptype        [ZZLOG;] { $$ = $1; }
  | tknInline      [ZZLOG;] { $$ = INLINE; }
  | tknVirtual     [ZZLOG;] { $$ = VIRTUAL; }
  | tknExplicit    [ZZLOG;] { $$ = EXPLICIT; }
  | tknFriend      [ZZLOG;] { $$ = FRIEND; }
  | tknConstExpr   [ZZLOG;] { $$ = CONST_EXPR; }
  ;

optfunctype
  :                [ZZLOG;] { $$ = 0; }
  | functype       [ZZLOG;] { $$ = $1; }
  ;

optfuncattrib
  : tknConst                      [ZZLOG;] { $$ = CONST; }
  | tknOverride                   [ZZLOG;] { $$ = OVERRIDE; }
  | tknFinal                      [ZZLOG;] { $$ = FINAL; }
  | tknNoExcept                   [ZZLOG;] { $$ = NO_EXCEPT; }
  | '=' tknNumber  [if($2.len != 1 || $2.sz[0] != '0') YYABORT; else ZZVALID;] [ZZLOG;]
  {
    $$ = PURE_VIRTUAL;
  }
  | optfuncattrib tknConst        [ZZLOG;] { $$ = $1 | CONST; }
  | optfuncattrib tknOverride     [ZZLOG;] { $$ = $1 | OVERRIDE; }
  | optfuncattrib tknFinal        [ZZLOG;] { $$ = $1 | FINAL; }
  | optfuncattrib tknNoExcept     [ZZLOG;] { $$ = $1 | NO_EXCEPT; }
  | optfuncattrib '=' tknNumber   [if($3.len != 1 || $3.sz[0] != '0') YYABORT; else ZZVALID;]
  {
    $$ = $1 | PURE_VIRTUAL;
  }
  | tknMacro                      [ZZLOG;] { $$ = 0; } /* Ignore macros used as function attributes */
  ;

optfuncthrowspec
  :               [ZZLOG;] { $$ = new std::vector<std::string>; }
  | functhrowspec [ZZLOG;] { $$ = $1; }
  ;

functhrowspec
  : tknThrow '(' identifierlist ')' [ZZLOG;] {
    $$ = $3 ? $3 : new std::vector<std::string>;
  }
  ;

identifierlist
  :                               [ZZLOG;] { $$ = nullptr; }
  | identifier [ZZLOG;] {
    $$ = new std::vector<std::string>;
    $$->push_back($1);
  }
  | identifierlist ',' identifier [ZZLOG;] {
    $$ = $1;
    $$->push_back($3);
  }
  ;

ctordeclstmt
  : ctordecl';'                 [ZZVALID;] { $$ = $1; }
  ;

ctordefn
  : ctordecl meminitlist block  [ZZVALID;]
  {
    $$ = $1;
    $$->memberInits(Obj($2));
    $$->defn(Ptr($3));
  }
  | name tknScopeResOp name [if($1 != $3) ZZERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
  {
    $$ = new cppast::CppConstructor(MergeCppToken($1, $3), Obj($6), Obj($9), 0);
    $$->defn(Ptr($10));
    $$->throwSpec(Obj($8));
  }
  | identifier tknScopeResOp name tknScopeResOp name [if($3 != $5) ZZERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
  {
    $$ = new cppast::CppConstructor(MergeCppToken($1, $5), Obj($8), Obj($11), 0);
    $$->defn(Ptr($12));
    $$->throwSpec(Obj($10));
  }
  | name tknLT templatearglist tknGT tknScopeResOp name [if($1 != $6) ZZERROR; else ZZVALID;]
                    '(' paramlist ')' optfuncthrowspec meminitlist block [ZZVALID;]
  {
    $$ = new cppast::CppConstructor(MergeCppToken($1, $6), Obj($9), Obj($12), 0);
    $$->defn(Ptr($13));
    $$->throwSpec(Obj($11));
  }
  | functype ctordefn [ZZLOG;] {
    $$ = $2;
    $$->addAttr($1);
  }
  | templatespecifier ctordefn [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  ;

ctordecl
  : identifier '(' paramlist ')' %prec CTORDECL
  [
    if(gCompoundStack.empty())
      ZZERROR;
    if((gCompoundStack.top() != $1) && (ClassNameFromIdentifier(gCompoundStack.top()) != $1))
      ZZERROR;
    else
      ZZVALID;
  ]
  {
    $$ = new cppast::CppConstructor($1, Obj($3), {}, 0);
  }
  | functype ctordecl [ZZLOG;] {
    $$ = $2;
    $$->addAttr($1);
  }
  | templatespecifier ctordecl [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  | ctordecl '=' tknDelete [ZZLOG;] {
    $$ = $1;
    $$->addAttr(DELETE);
  }
  | ctordecl '=' tknDefault [ZZLOG;] {
    $$ = $1;
    $$->addAttr(DEFAULT);
  }
  | ctordecl functhrowspec [ZZLOG;] {
    $$ = $1;
    $$->throwSpec(Obj($2));
  }
  | ctordecl tknNoExcept [ZZLOG;] {
    $$ = $1;
    $$->addAttr(NO_EXCEPT);
  }
  | apidecor ctordecl [ZZLOG;] {
    $$ = $2;
    $$->decor1($1);
  }
  ;

meminitlist
  : [ZZLOG;] {
    $$ = new cppast::CppMemberInits;
  }
  | ':' meminit [ZZLOG;] {
    $$ = new cppast::CppMemberInits;
    $$->push_back(Obj($2));
  }
/*| ':' blob                 [ZZLOG;] { $$ = new CppMemberInits{{}, Ptr($2)}; } */
  | meminitlist ',' meminit [ZZLOG;] {
    $$ = $1;
    $$->push_back(Obj($3));
  }
  ;

meminit
  : identifier '(' exprlist ')'    [ZZLOG;] { $$ = MemberInit($1, Obj($3), cppast::CppConstructorCallStyle::USING_PARENTHESES); }
  | identifier '(' ')'             [ZZLOG;] { $$ = MemberInit($1, cppast::CppCallArgs(), cppast::CppConstructorCallStyle::USING_PARENTHESES); }
  | identifier '{' exprlist '}'    [ZZLOG;] { $$ = MemberInit($1, Obj($3), cppast::CppConstructorCallStyle::USING_BRACES); }
  | identifier '{' '}'             [ZZLOG;] { $$ = MemberInit($1, cppast::CppCallArgs(), cppast::CppConstructorCallStyle::USING_BRACES); }
  ;

dtordeclstmt
  : dtordecl ';'    [ZZVALID;]     { $$ = $1; }
  ;

dtordefn
  : dtordecl block  [ZZVALID;]
  {
    $$ = $1;
    $$->defn(Ptr($2 ? $2 : new cppast::CppCompound(CppCompoundType::BLOCK)));
  }
  | name tknScopeResOp '~' name [if($1 != $4) ZZERROR; else ZZVALID;] '(' ')' block
  {
    $$ = new cppast::CppDestructor(MergeCppToken($1, $4), 0);
    $$->defn(Ptr($8 ? $8 : new cppast::CppCompound(CppCompoundType::BLOCK)));
  }
  | identifier tknScopeResOp name tknScopeResOp '~' name [if($3 != $6) ZZERROR; else ZZVALID;] '(' ')' block
  {
    $$ = new cppast::CppDestructor(MergeCppToken($1, $6), 0);
    $$->defn(Ptr($10 ? $10 : new cppast::CppCompound(CppCompoundType::BLOCK)));
  }
  | name tknLT templatearglist tknGT tknScopeResOp '~' name [if($1 != $7) ZZERROR; else ZZVALID;] '(' ')' block
  {
    $$ = new cppast::CppDestructor(MergeCppToken($1, $7), 0);
    $$->defn(Ptr($11 ? $11 : new cppast::CppCompound(CppCompoundType::BLOCK)));
  }
  | templatespecifier dtordefn [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  | functype dtordefn [ZZLOG;] {
    $$ = $2;
    $$->addAttr($1);
  }
  ;

dtordecl
  : '~' name '(' optvoid ')' %prec DTORDECL [ZZLOG;]
  [
    if(gCompoundStack.empty())
      ZZERROR;
    if(ClassNameFromIdentifier(gCompoundStack.top()) != $2)
      ZZERROR;
    else
      ZZVALID;
  ]
  {
    const char* tildaStartPos = $2.sz-1;
    while(*tildaStartPos != '~') --tildaStartPos;
    $$ = new cppast::CppDestructor(MakeCppToken(tildaStartPos, $2.sz+$2.len-tildaStartPos), 0);
  }
  | apidecor dtordecl [ZZLOG;] {
    $$ = $2;
    $$->decor1($1);
  }
  | functype dtordecl [ZZLOG;] {
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
    $$->addAttr(PURE_VIRTUAL);
  }
  | dtordecl '=' tknDelete [ZZLOG;] {
    $$ = $1;
    $$->addAttr(DELETE);
  }
  | dtordecl '=' tknDefault [ZZLOG;] {
    $$ = $1;
    $$->addAttr(DEFAULT);
  }
  | dtordecl functhrowspec [ZZLOG;] {
    $$ = $1;
    $$->throwSpec(Obj($2));
  }
  ;

optvoid
  :          [ZZLOG;]
  | tknVoid  [ZZLOG;]
  ;

optcomment
  :            [ZZLOG;]{
  }
  | doccomment [ZZVALID;] {
  }
  ;

classdefnstmt
  : classdefn ';' [ZZVALID;] { $$ = $1; }
  ;

attribspecifier
  : '[' '[' expr ']' ']' {
    $$ = $3;
  }
  ;

optattribspecifiers
  : {
    $$ = new std::vector<std::unique_ptr<const cppast::CppExpression>>;
  }
  | attribspecifiers { $$ = $1; }
  ;

attribspecifiers
  : attribspecifier {
    $$ = new std::vector<std::unique_ptr<const cppast::CppExpression>>;
    $$->push_back(Ptr($1));
  }
  | attribspecifiers attribspecifier {
    $$ = $1;
    $$->push_back(Ptr($2));
  }
  ;

classdefn
  : classspecifier optapidecor optattribspecifiers identifier optfinal optinheritlist optcomment '{'
  [
    ZZVALID;
    gCompoundStack.push($4);
  ]
  optstmtlist '}'
  [
    ZZVALID;
    gCompoundStack.pop();
  ]
  {
    $$ = $10 ? $10 : new cppast::CppCompound();
    $$->compoundType($1);
    $$->apidecor($2);
    $$->attribSpecifierSequence(Obj($3));
    $$->name(PruneClassName($4));
    $$->inheritanceList(Obj($6));
    $$->addAttr($5);
  }
  | classspecifier optattribspecifiers optinheritlist optcomment
    '{'
      optstmtlist
    '}' [ZZVALID;]
  {
    $$ = $6 ? $6 : new cppast::CppCompound();
    $$->compoundType($1);
    $$->attribSpecifierSequence(Obj($2));
    $$->inheritanceList(Obj($3));
  }
  | templatespecifier classdefn [ZZLOG;]
  {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  ;

namespacedefn
  : tknNamespace optidentifier '{'
  [
    ZZVALID;
    gCompoundStack.push(ClassNameFromIdentifier($2));
  ]
  optstmtlist '}'
  [
    ZZVALID;
    gCompoundStack.pop();
  ]
  {
    $$ = $5 ? $5 : new cppast::CppCompound();
    $$->compoundType(CppCompoundType::NAMESPACE);
    $$->name($2);
  }
  ;

optfinal
  :          [ZZLOG;] { $$ = 0; }
  | tknFinal [ZZLOG;] { $$ = FINAL; }
  ;

optinheritlist
  : [ZZLOG;] {
    $$ = new std::list<CppInheritanceInfo>;
  }
  | ':' protlevel optinherittype typeidentifier [ZZVALID;] {
    $$ = new std::list<CppInheritanceInfo>; $$->push_back({(std::string) $4, $2, $3});
  }
  | optinheritlist ',' protlevel optinherittype typeidentifier [ZZVALID;] {
    $$ = $1; $$->push_back({(std::string) $5, $3, $4});
  }
  | ':' optinherittype protlevel typeidentifier [ZZVALID;] {
    $$ = new std::list<CppInheritanceInfo>; $$->push_back({(std::string) $4, $3, $2});
  }
  | optinheritlist ',' optinherittype protlevel typeidentifier [ZZVALID;] {
    $$ = $1; $$->push_back({(std::string) $5, $4, $3});
  }
  ;

protlevel
  : { Init($$); }
  | tknPublic     [ZZLOG;] { Init($$, CppAccessType::PUBLIC); }
  | tknProtected  [ZZLOG;] { Init($$, CppAccessType::PROTECTED); }
  | tknPrivate    [ZZLOG;] { Init($$, CppAccessType::PRIVATE); }
  ;

optinherittype
  :             [ZZLOG;] { $$ = false; }
  | tknVirtual  [ZZLOG;] { $$ = true; }
  ;

fwddecl
  : classspecifier typeidentifier ';'          [ZZVALID;] { $$ = new cppast::CppForwardClassDecl($2, $1); }
  | classspecifier optapidecor identifier ';'  [ZZVALID;] { $$ = new cppast::CppForwardClassDecl($3, $2, $1); }
  | templatespecifier fwddecl [ZZLOG;] {
    $$ = $2;
    $$->templateSpecification(Obj($1));
  }
  | tknFriend typeidentifier ';'  [ZZVALID;] { $$ = new cppast::CppForwardClassDecl($2); $$->addAttr(FRIEND); }
  | tknFriend fwddecl             [ZZVALID;] { $$ = $2; $$->addAttr(FRIEND); }
  ;

classspecifier
  : tknClass      [ZZLOG;] { $$ = CppCompoundType::CLASS; }
  | tknStruct     [ZZLOG;] { $$ = CppCompoundType::STRUCT; }
  | tknUnion      [ZZLOG;] { $$ = CppCompoundType::UNION; }
  ;

templatespecifier
  : tknTemplate tknLT       [gInTemplateSpec = true;  ZZLOG;   ]
    templateparamlist tknGT [gInTemplateSpec = false; ZZVALID; ]
  {
    $$ = $4;
  }
  ;

templateparamlist
  : [ZZLOG;] {
    $$ = new cppast::CppTemplateParams;
  }
  | templateparam [ZZLOG;] {
    $$ = new cppast::CppTemplateParams;
    $$->emplace_back(Obj($1));
  }
  | templateparamlist ',' templateparam [ZZLOG;] {
    $$ = $1;
    $$->emplace_back(Obj($3));
  }
  ;

templateparam
  : tknTypename optname [ZZLOG;] {
    $$ = new cppast::CppTemplateParam($2);
  }
  | tknTypename optname '=' vartype [ZZLOG;] {
    $$ = new cppast::CppTemplateParam($2, Ptr($4));
  }
  | tknClass optname [ZZLOG;] {
    $$ = new cppast::CppTemplateParam($2);
  }
  | tknClass optname '=' vartype [ZZLOG;] {
    $$ = new cppast::CppTemplateParam($2, Ptr($4));
  }
  | vartype name [ZZLOG;] {
    $$ = new cppast::CppTemplateParam(Ptr($1), $2);
  }
  | vartype name '=' expr  %prec TEMPLATE [ZZLOG;] {
    $$ = new cppast::CppTemplateParam(Ptr($1), $2, Ptr($4));
  }
  | functionpointer [ZZLOG;] {
    $$ = new cppast::CppTemplateParam(Ptr($1), std::string());
  }
  | functionpointer '=' expr  %prec TEMPLATE [ZZLOG;] {
    $$ = new cppast::CppTemplateParam(Ptr($1), std::string(), Ptr($3));
  }
  | vartype                       [ZZLOG;] { // Can happen when forward declaring
    $$ = new cppast::CppTemplateParam(Ptr($1), std::string());
  }
  | vartype '=' expr              [ZZLOG;] { // Can happen when forward declaring
    $$ = new cppast::CppTemplateParam(Ptr($1), std::string(), Ptr($3));
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

optapidecor
  :             [ZZLOG;] { $$ = MakeCppToken(nullptr, nullptr); }
  | apidecor    [ZZLOG;] { $$ = $1; }
  ;

apidecor
  : apidecortokensq                     [ZZLOG;] { $$ = $1; }
  | apidecortokensq '(' name ')'          [ZZLOG;] { $$ = MergeCppToken($1, $4); }
  | apidecortokensq '(' tknNumber ')'   [ZZLOG;] { $$ = MergeCppToken($1, $4); }
  | apidecortokensq '(' strlit ')'   [ZZLOG;] { $$ = MergeCppToken($1, $4); }
  ;

apidecortokensq
  : tknApiDecor                  [ZZLOG;] { $$ = $1; }
  | apidecortokensq tknApiDecor  [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  | tknApiDecor '(' strlit ')'   [ZZLOG;] { $$ = MergeCppToken($1, $4); }
  ;

entityaccessspecifier
  : tknPublic     ':'  [ZZVALID;] { $$ = new cppast::CppEntityAccessSpecifier(CppAccessType::PUBLIC); }
  | tknProtected  ':'  [ZZVALID;] { $$ = new cppast::CppEntityAccessSpecifier(CppAccessType::PROTECTED); }
  | tknPrivate    ':'  [ZZVALID;] { $$ = new cppast::CppEntityAccessSpecifier(CppAccessType::PRIVATE); }
  ;

externcblock
  : tknExternC block   [ZZVALID;] {$$ = $2; $$->compoundType(CppCompoundType::EXTERN_C_BLOCK); }
  ;

strlit
                  : tknStrLit          [ZZLOG;] { $$ = $1; }
  | strlit tknStrLit   [ZZLOG;] { $$ = MergeCppToken($1, $2); }
  ;

expr
  : strlit                            [ZZLOG;] { $$ = new cppast::CppStringLiteralExpr($1); }
  | tknCharLit                        [ZZLOG;] { $$ = new cppast::CppCharLiteralExpr($1); }
  | tknNumber                         [ZZLOG;] { $$ = new cppast::CppNumberLiteralExpr($1); }
  | identifier
    [
      if ($1.sz == gParamModPos) {
        gParamModPos = nullptr;
        ZZERROR;
      } else {
        ZZLOG;
      }
    ]                                 [ZZLOG;] { $$ = NameExpr($1); }
  | '(' exprlist ')'                  [ZZLOG;] { $$ = ExpressionListExpr(Obj($2)); };
  | '{' optexprlist '}'               [ZZLOG;] { $$ = InitializerListExpr($2); }
  | '{' optexprlist ',' '}'           [ZZLOG;] { $$ = InitializerListExpr($2); }
  | '+' expr                          [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::UNARY_PLUS, $2); }
  | '-' expr %prec UNARYMINUS         [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::UNARY_MINUS, $2); }
  | '~' expr                          [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::BIT_TOGGLE, $2); }
  | '!' expr                          [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::LOGICAL_NOT, $2); }
  | '*' expr %prec DEREF              [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::DEREFER, $2); }
  | '&' expr %prec ADDRESSOF          [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::REFER, $2); }
  | '&' operfuncname %prec ADDRESSOF  [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::REFER, NameExpr($2)); }
  | tknInc expr  %prec PREINCR        [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::PREFIX_INCREMENT, $2); }
  | tknDec expr  %prec PREDECR        [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::PREFIX_DECREMENT, $2); }
  | expr tknInc  %prec POSTINCR       [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::POSTFIX_INCREMENT, $1); }
  | expr tknDec  %prec POSTDECR       [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::POSTFIX_DECREMENT, $1); }
  | expr '+' expr                     [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::PLUS, $1, $3); }
  | expr '-' expr                     [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::MINUS, $1, $3); }
  | expr '*' expr
    [
      if ($2.sz == gParamModPos) {
        gParamModPos = nullptr;
        ZZERROR;
      } else {
        ZZLOG;
      }
    ]                                         [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::MUL, $1, $3); }
  | expr '/' expr                             [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::DIV, $1, $3); }
  | expr '%' expr                             [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::PERCENT, $1, $3); }
  | expr '&' expr
    [
      if ($2.sz == gParamModPos) {
        gParamModPos = nullptr;
        ZZERROR;
      } else {
        ZZLOG;
      }
    ]                                         [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::AND, $1, $3); }
  | expr '|' expr                             [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::OR, $1, $3); }
  | expr '^' expr                             [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::XOR, $1, $3); }
  | expr '=' expr                             [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::ASSIGN, $1, $3); }
  | expr tknLT expr                           [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::LESS, $1, $3); }
  | expr tknGT expr                           [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::GREATER, $1, $3); }
  | expr tknPlusEq expr                       [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::PLUS_ASSIGN, $1, $3); }
  | expr tknMinusEq expr                      [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::MINUS_ASSIGN, $1, $3); }
  | expr tknMulEq expr                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::MUL_ASSIGN, $1, $3); }
  | expr tknDivEq expr                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::DIV_ASSIGN, $1, $3); }
  | expr tknPerEq expr                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::PERCENT_ASSIGN, $1, $3); }
  | expr tknXorEq expr                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::XOR_ASSIGN, $1, $3); }
  | expr tknAndEq expr                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::AND_ASSIGN, $1, $3); }
  | expr tknOrEq expr                         [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::OR_ASSIGN, $1, $3); }
  | expr tknLShift expr                       [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::LEFT_SHIFT, $1, $3); }
  | expr rshift expr                          [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::RIGHT_SHIFT, $1, $3); }
  | expr tknLShiftEq expr                     [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::LSHIFT_ASSIGN, $1, $3); }
  | expr tknRShiftEq expr                     [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::RSHIFT_ASSIGN, $1, $3); }
  | expr tknCmpEq expr                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::EQUAL, $1, $3); }
  | expr tknNotEq expr                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::NOT_EQUAL, $1, $3); }
  | expr tknLessEq expr                       [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::LESS_EQUAL, $1, $3); }
  | expr tknGreaterEq expr                    [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::GREATER_EQUAL, $1, $3); }
  | expr tkn3WayCmp expr                      [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::THREE_WAY_CMP, $1, $3); }
  | expr tknAnd expr
    [
      if ($2.sz == gParamModPos) {
        gParamModPos = nullptr;
        ZZERROR;
      } else {
        ZZLOG;
      }
    ]                                                     [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::LOGICAL_AND, $1, $3); }
  | expr tknOr expr                                       [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::LOGICAL_OR, $1, $3); }
  | expr '.' expr                                         [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::DOT, $1, $3); }
  | expr '.' '*' expr                                     [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::DOT, $1, MonomialExpr(cppast::CppUnaryOperator::DEREFER, $4)); }
  | expr tknArrow expr                                    [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::ARROW, $1, $3); }
  | expr tknArrowStar expr                                [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::ARROW_STAR, $1, $3); }
  | expr '.' '~' funcname                                 [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::DOT, $1, MergeCppToken($3, $4)); }
  | expr tknArrow '~' funcname                            [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::ARROW, $1, MergeCppToken($3, $4)); }
  | expr '[' expr ']' %prec SUBSCRIPT                     [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::ARRAY_INDEX, $1, $3); }
  /*| expr '[' ']' %prec SUBSCRIPT                        [ZZLOG;] { $$ = BinomialExpr($1, kArrayElem); }*/
  | expr '(' optexprlist ')' %prec FUNCCALL               [ZZLOG;] { $$ = FuncCallExpr($1, $3); }
  | funcname '(' optexprlist ')' %prec FUNCCALL           [ZZLOG;] { $$ = FuncCallExpr(NameExpr($1), $3); }
  | expr tknArrow '~' identifier '(' ')' %prec FUNCCALL   [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::ARROW, $1, FuncCallExpr(NameExpr(MergeCppToken($3, $4)))); }
  | expr '?' expr ':' expr %prec TERNARYCOND              [ZZLOG;] { $$ = TrinomialExpr(cppast::CppTernaryOperator::CONDITIONAL, $1, $3, $5); }
  | identifier '{' optexprlist '}' %prec FUNCCALL         [ZZLOG;] { $$ = UniformInitExpr($1, $3); }
  | '(' vartype ')' expr %prec CSTYLECAST                 [ZZLOG;] { $$ = CStyleCastExpr($2, $4); }
  | tknConstCast tknLT vartype tknGT '(' expr ')'         [ZZLOG;] { $$ = ConstCastExpr($3, $6); }
  | tknStaticCast tknLT vartype tknGT '(' expr ')'        [ZZLOG;] { $$ = StaticCastExpr($3, $6); }
  | tknDynamicCast tknLT vartype tknGT '(' expr ')'       [ZZLOG;] { $$ = DynamiCastExpr($3, $6); }
  | tknReinterpretCast tknLT vartype tknGT '(' expr ')'   [ZZLOG;] { $$ = ReinterpretCastExpr($3, $6); }
  | '(' expr ')'                                          [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::PARENTHESIZE, $2); }
  | tknNew typeidentifier opttypemodifier                 [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::NEW, VarTypeExpr($2, $3)); }
  | tknNew expr                                           [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::NEW, $2); }
  | tknNew '(' expr ')' expr %prec tknNew                 [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::PLACEMENT_NEW, $3, $5); }
  | tknScopeResOp tknNew '(' expr ')' expr %prec tknNew   [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::GLOBAL_PLACEMENT_NEW, $4, $6); }
  | tknDelete  expr                                       [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::DELETE, $2); }
  | tknDelete  '[' ']' expr %prec tknDelete               [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::DELETE_AARAY, $4); }
  | tknSizeOf '(' vartype ')'                             [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::SIZE_OF, VarTypeExpr($3)); }
  | tknSizeOf '(' expr ')'                                [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::SIZE_OF, $3); }
  | tknSizeOf tknEllipsis '(' vartype ')'                 [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::VARIADIC_SIZE_OF, VarTypeExpr($4)); }
  | tknSizeOf tknEllipsis '(' expr ')'                    [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::VARIADIC_SIZE_OF, $4); }
  | expr tknEllipsis                                      [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::VARIADIC, $1); }
  | lambda                                                [ZZLOG;] { $$ = LambdaExpression($1); }
  /* This is to parse implementation of string user literal, see https://en.cppreference.com/w/cpp/language/user_literal */
  | tknNumber name                                        [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::USER_LITERAL, NumberLiteralExpr($1), NameExpr($2)); }
  /* Objective C expressions */
  /* This will need improvements, as of now the aim is just to mainly parse C++ content. */
  | '[' expr expr ']'                                     [ZZLOG;] { $$ = $2; }
  | '[' expr objcarglist ']'                              [ZZLOG;] { $$ = $2; }
  ;

objcarg
  : name ':' expr { $$ = $3; }
  ;

objcarglist
  : objcarg { $$ = $1; }
  | objcarglist objcarg { $$ = $1; }
  ;

exprlist
  : expr [ZZLOG;] {
     $$ = new std::vector<std::unique_ptr<const cppast::CppExpression>>;
     $$->emplace_back($1);
  }
  | desinatedinitialization [ZZLOG;] {
     $$ = new std::vector<std::unique_ptr<const cppast::CppExpression>>;
     $$->emplace_back($1);
  }
  | exprlist optdoccommentstr ',' optdoccommentstr expr %prec COMMA [ZZLOG;] { $1->emplace_back($5); $$ = $1; }
  | exprlist optdoccommentstr ',' optdoccommentstr desinatedinitialization %prec COMMA [ZZLOG;] { $1->emplace_back($5); $$ = $1; }
  | doccommentstr exprlist [ZZLOG;] { $$ = $2; }
  | exprlist doccommentstr [ZZLOG;] { $$ = $1; }
  ;

desinatedinitialization
  : designatedname '=' expr [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::ASSIGN, NameExpr($1), $3); }
  ;

optexprlist
  :           [ZZLOG;] { $$ = nullptr; }
  | exprlist  [ZZLOG;] { $$ = $1; }
  ;

exprorlist
  : expr                        [ZZLOG;] { $$ = $1; }
  | exprlist                    [ZZLOG;] { $$ = ExpressionListExpr(Obj($1)); }
  | doccommentstr exprorlist    [ZZLOG;] { $$ = $2; }
  ;

optexprorlist
  :             [ZZLOG;] { $$ = nullptr; }
  | exprorlist  [ZZLOG;] { $$ = $1; }
  ;

/* TODO: Improve lambda capture types. As of now use of use of MonomialExpr and  BinomialExpr are hacks. */
captureallbyref
  : '&'  [ZZLOG;] { $$ = MonomialExpr(cppast::CppUnaryOperator::REFER, NameExpr("")); }
  ;

captureallbyval
  : '='  [ZZLOG;] { $$ = BinomialExpr(cppast::CppBinaryOperator::EQUAL, NameExpr(""), NameExpr("")); }
  ;

lambdacapture
  : optexprlist        [ZZLOG;] { $$ = nullptr; }
  | captureallbyref    [ZZLOG;] { $$ = nullptr; }
  | captureallbyval    [ZZLOG;] { $$ = nullptr; }
  ;

exprstmt
  : expr ';'           [ZZLOG;] { $$ = $1; }
  ;

returnstmt
  : tknReturn  exprorlist ';' [ZZLOG;] { $$ = new cppast::CppReturnStatement(Ptr($2)); }
  | tknReturn  ';'            [ZZLOG;] { $$ = new cppast::CppReturnStatement(); }
  ;

throwstmt
  : tknThrow  expr         [ZZLOG;] { $$ = new cppast::CppThrowStatement(Ptr($2)); }
  | tknThrow               [ZZLOG;] { $$ = new cppast::CppThrowStatement(); }
  ;

gotostmt
  : tknGoto expr           [ZZLOG;] { $$ = new cppast::CppGotoStatement(Ptr($2)); }
  ;

%%

//////////////////////////////////////////////////////////////////////////

// clang-format on

#include "parser.h"

  extern LexerData g;

extern const char* contextNameFromState(int ctx);

enum class ParseStatus
{
  NotAvailable,
  Success,
  Failure
};

ParseStatus gParseStatus = ParseStatus::NotAvailable;

void defaultErrorHandler(const char* errLineText, size_t lineNum, size_t errorStartPos, int lexerContext)
{
  constexpr size_t bufsize             = 1024;
  char             spacechars[bufsize] = {0};
  for (size_t i = 0; i < errorStartPos; ++i)
    spacechars[i] = (errLineText[i] == '\t') ? '\t' : ' ';
  char        errmsg[bufsize];
  const auto* errText         = errLineText + errorStartPos;
  const auto* strLexerContext = contextNameFromState(lexerContext);

  std::sprintf(errmsg,
               "Error: Unexpected '%.*s', while in context=%.*s(%d), found at line#%ld\n"
               "%.*s\n"   // Line that contains the error.
               "%.*s^\n", // A ^ below the beginning of unexpected token.
               static_cast<int>(strlen(errText)),
               errText,
               static_cast<int>(strlen(strLexerContext)),
               strLexerContext,
               lexerContext,
               lineNum,
               static_cast<int>(strlen(errLineText)),
               errLineText,
               static_cast<int>(strlen(spacechars)),
               spacechars);

  printf("%s", errmsg);
}

ErrorHandler gErrorHandler = defaultErrorHandler;

/**
 * yyparser() invokes this function when it encounters unexpected token.
 */
void yyerror_detailed(char* text, int errt, YYSTYPE& errt_value, YYPOSN& errt_posn)
{
  extern int getLexerContext();

  const char* lineStart = errt_posn;
  const char* buffStart = g.mInputBuffer;
  while (lineStart > buffStart)
  {
    if (lineStart[-1] == '\n' || lineStart[-1] == '\r')
      break;
    --lineStart;
  }
  char* lineEnd        = errt_posn;
  char  endReplaceChar = 0;
  while (*lineEnd)
  {
    if (*lineEnd == '\r' || *lineEnd == '\n')
    {
      endReplaceChar = *lineEnd;
      *lineEnd       = '\0'; // So that printing of lineStart does not print things beyond current line.
    }
    else
    {
      ++lineEnd;
    }
  }
  gParseStatus = ParseStatus::Failure;
  gErrorHandler(lineStart, g.mLineNo, errt_posn - lineStart, getLexerContext());
  // Replace back the end char
  if (endReplaceChar)
    *lineEnd = endReplaceChar;
}

enum
{
  kNoLog    = 0x000,
  kLexLog   = 0x001,
  kParseLog = 0x002,
  kYaccLog  = 0x004
};

static void setupEnv()
{
#if YYDEBUG
  const char* yys = getenv("ZZDEBUG");
  if (yys)
  {
    const int yyn = *yys - '0';

    gParseLog = ((yyn & kParseLog) ? 1 : 0);
    g.mLexLog = ((yyn & kLexLog) ? 1 : 0);
    yydebug   = ((yyn & kYaccLog) ? 1 : 0);
  }
#endif
}

void SetErrorHandler(ErrorHandler errorHandler)
{
  gErrorHandler = errorHandler;
}

void ResetErrorHandler()
{
  gErrorHandler = defaultErrorHandler;
}

int GetKeywordId(const std::string& keyword)
{
  static const std::unordered_map<std::string, int> keywordToIdMap = {{"virtual", tknVirtual},
                                                                      {"final", tknFinal},
                                                                      {"override", tknOverride},
                                                                      {"const", tknConst},
                                                                      {"noexcept", tknNoExcept},
                                                                      {"inline", tknInline},
                                                                      {"explicit", tknExplicit},
                                                                      {"friend", tknFriend},
                                                                      {"public", tknPublic},
                                                                      {"protected", tknProtected},
                                                                      {"private", tknPrivate},
                                                                      {"struct", tknStruct},
                                                                      {"class", tknClass},
                                                                      {"union", tknUnion},
                                                                      {"namespace", tknNamespace},
                                                                      {"typename", tknTypename},
                                                                      {"template", tknTemplate},
                                                                      {"extern", tknExtern},
                                                                      {"extern", tknExtern},
                                                                      {"static", tknStatic},
                                                                      {"auto", tknAuto},
                                                                      {"mutable", tknMutable},
                                                                      {"volatile", tknVolatile},
                                                                      {"constexpr", tknConstExpr},
                                                                      {"constexpr", tknConstExpr},
                                                                      {"typedef", tknTypedef}};

  auto itr = keywordToIdMap.find(keyword);
  return (itr != keywordToIdMap.end()) ? itr->second : -1;
}

std::unique_ptr<CppCompound> ParseStream(char* stm, size_t stmSize)
{
  gProgUnit = nullptr;

  void setupScanBuffer(char* buf, size_t bufsize);
  void cleanupScanBuffer();
  setupScanBuffer(stm, stmSize);
  setupEnv();
  gTemplateParamStart = nullptr;
  gParamModPos        = nullptr;
  gInTemplateSpec     = false;
  gDisableYyValid     = 0;
  gParseStatus        = ParseStatus::NotAvailable;
  yyparse();
  cleanupScanBuffer();
  CppCompoundStack tmpStack;
  gCompoundStack.swap(tmpStack);

  std::unique_ptr<CppCompound> ret(gProgUnit);
  gProgUnit = nullptr;

  return ret;
}
