/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 37 "parser.y" /* yacc.c:339  */

#include "cpptoken.h"
#include "cppast.h"
#include "cppvarinit.h"
#include "parser.tab.h"
#include "cppobjfactory.h"
#include "obj-factory-helper.h"
#include "utils.h"

#include <iostream>
#include <stack>
#include <map>

//////////////////////////////////////////////////////////////////////////

int GetKeywordId(const std::string& keyword) {
  static const std::map<std::string, int> keywordToIdMap =
   {{"virtual",   tknVirtual},
    {"final",     tknFinal},
    {"override",  tknOverride},
    {"const",     tknConst}
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
    printf("ZZLOG @line#%d, parsing stream line#%d\n", __LINE__, gLineNo); \
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


#line 193 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    tknName = 258,
    tknID = 259,
    tknStrLit = 260,
    tknCharLit = 261,
    tknNumber = 262,
    tknMacro = 263,
    tknApiDecor = 264,
    tknTypedef = 265,
    tknUsing = 266,
    tknInteger = 267,
    tknChar = 268,
    tknDouble = 269,
    tknFloat = 270,
    tknEnum = 271,
    tknAuto = 272,
    tknPreProDef = 273,
    tknClass = 274,
    tknStruct = 275,
    tknUnion = 276,
    tknNamespace = 277,
    tknTemplate = 278,
    tknTypename = 279,
    tknDecltype = 280,
    tknFreeStandingBlockComment = 281,
    tknSideBlockComment = 282,
    tknFreeStandingLineComment = 283,
    tknSideLineComment = 284,
    tknScopeResOp = 285,
    tknNumSignSpec = 286,
    tknPublic = 287,
    tknProtected = 288,
    tknPrivate = 289,
    tknExternC = 290,
    tknUnRecogPrePro = 291,
    tknStdHdrInclude = 292,
    tknPragma = 293,
    tknHashError = 294,
    tknEllipsis = 295,
    tknConstCast = 296,
    tknStaticCast = 297,
    tknDynamicCast = 298,
    tknReinterpretCast = 299,
    tknTry = 300,
    tknCatch = 301,
    tknThrow = 302,
    tknSizeOf = 303,
    tknOperator = 304,
    tknPlusEq = 305,
    tknMinusEq = 306,
    tknMulEq = 307,
    tknDivEq = 308,
    tknPerEq = 309,
    tknXorEq = 310,
    tknAndEq = 311,
    tknOrEq = 312,
    tknLShift = 313,
    tknLShiftEq = 314,
    tknRShiftEq = 315,
    tknCmpEq = 316,
    tknNotEq = 317,
    tknLessEq = 318,
    tknGreaterEq = 319,
    tkn3WayCmp = 320,
    tknAnd = 321,
    tknOr = 322,
    tknInc = 323,
    tknDec = 324,
    tknArrow = 325,
    tknArrowStar = 326,
    tknLT = 327,
    tknGT = 328,
    tknNew = 329,
    tknDelete = 330,
    tknConst = 331,
    tknConstExpr = 332,
    tknVoid = 333,
    tknOverride = 334,
    tknFinal = 335,
    tknAsm = 336,
    tknBlob = 337,
    tknStatic = 338,
    tknExtern = 339,
    tknVirtual = 340,
    tknInline = 341,
    tknExplicit = 342,
    tknFriend = 343,
    tknVolatile = 344,
    tknMutable = 345,
    tknNoExcept = 346,
    tknPreProHash = 347,
    tknDefine = 348,
    tknUndef = 349,
    tknInclude = 350,
    tknImport = 351,
    tknIf = 352,
    tknIfDef = 353,
    tknIfNDef = 354,
    tknElse = 355,
    tknElIf = 356,
    tknEndIf = 357,
    tknFor = 358,
    tknWhile = 359,
    tknDo = 360,
    tknSwitch = 361,
    tknCase = 362,
    tknDefault = 363,
    tknReturn = 364,
    tknBlankLine = 365,
    COMMA = 366,
    TERNARYCOND = 367,
    RSHIFT = 368,
    PREINCR = 369,
    PREDECR = 370,
    UNARYMINUS = 371,
    CSTYLECAST = 372,
    DEREF = 373,
    ADDRESSOF = 374,
    POSTINCR = 375,
    POSTDECR = 376,
    FUNCTIONALCAST = 377,
    FUNCCALL = 378,
    SUBSCRIPT = 379,
    GLOBAL = 380,
    TEMPLATE = 381,
    PTRDECL = 382,
    REFDECL = 383,
    CTORDECL = 384,
    DTORDECL = 385
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 164 "parser.y" /* yacc.c:355  */

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
  CppMemInitList*         memInitList;
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
  CppPragma*              hashPragma;

  CppBlob*                blob;

#line 429 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 446 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  383
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   9819

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  153
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  695
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1708

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   385

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    83,     2,     2,     2,    78,    80,     2,
      86,    87,    76,    74,    85,    75,   142,    77,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   151,    90,
       2,    84,     2,   152,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    88,     2,    89,    79,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   149,    81,   150,    82,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     143,   144,   145,   146,   147,   148
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   407,   407,   407,   414,   414,   417,   417,   422,   422,
     429,   429,   436,   436,   439,   439,   440,   440,   441,   441,
     442,   442,   443,   443,   444,   444,   445,   445,   446,   446,
     447,   447,   448,   448,   449,   449,   450,   450,   451,   451,
     452,   452,   453,   453,   454,   454,   455,   455,   456,   456,
     457,   457,   458,   458,   459,   459,   460,   460,   461,   461,
     462,   462,   463,   463,   464,   464,   465,   465,   466,   466,
     467,   467,   468,   468,   469,   469,   470,   470,   471,   471,
     472,   472,   473,   473,   474,   474,   475,   475,   478,   478,
     479,   479,   480,   480,   481,   481,   482,   482,   483,   483,
     484,   484,   487,   487,   490,   490,   494,   494,   497,   497,
     503,   503,   508,   508,   511,   511,   515,   515,   519,   519,
     520,   520,   523,   523,   530,   530,   535,   535,   538,   538,
     541,   541,   547,   547,   550,   550,   555,   555,   560,   560,
     563,   563,   566,   566,   571,   571,   576,   576,   579,   579,
     585,   585,   590,   593,   593,   596,   596,   601,   601,   604,
     604,   607,   607,   610,   610,   613,   613,   616,   616,   621,
     621,   624,   624,   625,   625,   628,   628,   629,   629,   632,
     632,   633,   633,   634,   634,   635,   635,   636,   636,   637,
     637,   638,   638,   641,   641,   644,   644,   647,   647,   650,
     650,   651,   651,   652,   652,   653,   653,   656,   656,   657,
     657,   658,   658,   659,   659,   660,   660,   661,   661,   662,
     662,   663,   663,   666,   666,   667,   667,   668,   668,   669,
     669,   672,   672,   673,   673,   674,   674,   675,   675,   676,
     676,   677,   677,   678,   678,   679,   684,   679,   685,   685,
     686,   686,   687,   687,   688,   688,   689,   689,   692,   692,
     695,   695,   698,   698,   703,   703,   708,   708,   709,   709,
     712,   712,   713,   713,   714,   714,   715,   715,   716,   716,
     717,   717,   720,   720,   723,   723,   724,   724,   728,   728,
     732,   732,   737,   737,   740,   740,   743,   743,   746,   746,
     749,   749,   752,   752,   755,   755,   760,   760,   763,   763,
     766,   766,   769,   769,   774,   774,   779,   779,   782,   782,
     785,   785,   788,   788,   791,   791,   794,   794,   797,   797,
     800,   800,   803,   803,   807,   807,   813,   813,   818,   818,
     823,   823,   824,   824,   827,   827,   828,   828,   829,   829,
     830,   830,   831,   831,   834,   834,   839,   839,   844,   844,
     851,   851,   852,   852,   853,   853,   854,   854,   855,   855,
     856,   856,   857,   857,   858,   858,   862,   862,   868,   868,
     871,   871,   874,   874,   879,   879,   880,   880,   883,   883,
     886,   886,   889,   889,   893,   893,   897,   897,   901,   901,
     905,   905,   911,   911,   914,   914,   922,   922,   925,   925,
     928,   928,   931,   931,   934,   934,   937,   937,   940,   940,
     943,   943,   947,   947,   951,   951,   958,   958,   959,   959,
     960,   960,   961,   961,   962,   962,   965,   965,   966,   969,
     969,   973,   973,   977,   977,   981,   981,   985,   985,   989,
     989,   993,   993,   997,   997,  1004,  1004,  1005,  1005,  1006,
    1006,  1009,  1009,  1010,  1010,  1011,  1011,  1012,  1012,  1015,
    1015,  1018,  1018,  1021,  1021,  1025,  1025,  1029,  1029,  1033,
    1033,  1039,  1039,  1042,  1042,  1048,  1048,  1051,  1051,  1057,
    1060,  1065,  1065,  1066,  1066,  1069,  1069,  1073,  1073,  1077,
    1077,  1081,  1081,  1085,  1085,  1089,  1089,  1095,  1103,  1111,
    1111,  1116,  1116,  1119,  1119,  1122,  1122,  1127,  1127,  1131,
    1131,  1134,  1134,  1137,  1137,  1140,  1140,  1143,  1143,  1147,
    1147,  1153,  1153,  1157,  1157,  1161,  1161,  1165,  1165,  1169,
    1169,  1175,  1175,  1181,  1181,  1182,  1182,  1183,  1183,  1185,
    1185,  1188,  1188,  1191,  1191,  1192,  1192,  1193,  1193,  1194,
    1194,  1195,  1195,  1196,  1196,  1197,  1197,  1198,  1198,  1199,
    1199,  1200,  1200,  1201,  1201,  1202,  1202,  1203,  1203,  1204,
    1204,  1205,  1205,  1206,  1206,  1207,  1207,  1208,  1208,  1209,
    1209,  1210,  1210,  1211,  1211,  1212,  1212,  1213,  1213,  1214,
    1214,  1215,  1215,  1216,  1216,  1217,  1217,  1218,  1218,  1219,
    1219,  1220,  1220,  1221,  1221,  1222,  1222,  1223,  1223,  1224,
    1224,  1225,  1225,  1226,  1226,  1227,  1227,  1228,  1228,  1229,
    1229,  1230,  1230,  1231,  1231,  1232,  1232,  1233,  1233,  1234,
    1234,  1235,  1235,  1236,  1236,  1239,  1239,  1244,  1244,  1247,
    1247,  1248,  1252,  1252,  1258,  1258,  1259,  1259,  1265,  1265,
    1266,  1266,  1271,  1271,  1272,  1272,  1273,  1273,  1279,  1279,
    1287,  1287,  1288,  1288,  1289,  1289,  1290,  1290,  1295,  1295,
    1296,  1296,  1299,  1299,  1300,  1300,  1301,  1301,  1302,  1302,
    1303,  1303,  1304,  1304,  1307,  1307,  1308,  1308,  1311,  1311,
    1312,  1312,  1313,  1313,  1314,  1314,  1315,  1316,  1315,  1317,
    1317,  1318,  1318,  1319,  1319,  1320,  1320,  1321,  1321,  1323,
    1323,  1326,  1326,  1327,  1327,  1330,  1330,  1335,  1335,  1336,
    1336,  1340,  1340,  1346,  1346,  1349,  1349,  1355,  1356,  1355,
    1362,  1363,  1362,  1369,  1370,  1369,  1376,  1376,  1380,  1380,
    1387,  1386,  1398,  1398,  1402,  1402,  1406,  1406,  1410,  1410,
    1414,  1414,  1418,  1418,  1422,  1422,  1428,  1428,  1429,  1429,
    1430,  1430,  1433,  1433,  1434,  1434,  1435,  1435,  1436,  1436,
    1439,  1439,  1442,  1442,  1447,  1447,  1453,  1453,  1459,  1459,
    1465,  1465,  1469,  1469,  1475,  1476,  1475,  1489,  1489,  1493,
    1493,  1497,  1497,  1502,  1502,  1507,  1507,  1511,  1511,  1515,
    1515,  1521,  1522,  1525,  1525,  1527,  1527,  1531,  1531,  1535,
    1541,  1534,  1556,  1558,  1555,  1567,  1567,  1575,  1581,  1574,
    1594,  1594,  1595,  1595,  1598,  1598,  1599,  1599,  1602,  1602,
    1605,  1605,  1608,  1608,  1613,  1613,  1614,  1614,  1615,  1615,
    1616,  1616,  1619,  1619,  1620,  1620,  1623,  1623,  1624,  1624,
    1625,  1625,  1629,  1629,  1630,  1630,  1633,  1633,  1634,  1634,
    1635,  1635,  1638,  1639,  1638,  1645,  1645,  1648,  1648,  1652,
    1652,  1658,  1658,  1661,  1661,  1665,  1665,  1668,  1668,  1672,
    1672,  1675,  1675,  1679,  1679,  1682,  1682,  1686,  1686,  1689,
    1689,  1694,  1694,  1699,  1699,  1704,  1704,  1709,  1709,  1714,
    1714,  1722,  1722,  1723,  1723,  1726,  1726,  1727,  1727,  1728,
    1728,  1729,  1729,  1732,  1732,  1733,  1733,  1736,  1736,  1737,
    1737,  1738,  1738,  1741,  1741,  1744,  1744,  1745,  1745,  1748,
    1748,  1749,  1749,  1750,  1750,  1751,  1751,  1753,  1760,  1752,
    1761,  1761,  1762,  1762,  1763,  1763,  1764,  1764,  1765,  1765,
    1766,  1766,  1767,  1767,  1768,  1768,  1769,  1769,  1770,  1770,
    1771,  1771,  1772,  1772,  1773,  1773,  1774,  1774,  1775,  1775,
    1776,  1776,  1777,  1777,  1779,  1786,  1778,  1787,  1787,  1788,
    1788,  1790,  1797,  1789,  1798,  1798,  1799,  1799,  1800,  1800,
    1801,  1801,  1802,  1802,  1803,  1803,  1804,  1804,  1805,  1805,
    1806,  1806,  1807,  1807,  1808,  1808,  1809,  1809,  1810,  1810,
    1811,  1811,  1812,  1812,  1813,  1813,  1814,  1814,  1815,  1815,
    1816,  1816,  1817,  1817,  1818,  1818,  1819,  1819,  1820,  1820,
    1822,  1829,  1821,  1830,  1830,  1831,  1831,  1832,  1832,  1833,
    1833,  1834,  1834,  1835,  1835,  1836,  1836,  1837,  1837,  1838,
    1838,  1839,  1839,  1840,  1840,  1842,  1842,  1843,  1843,  1844,
    1844,  1845,  1845,  1846,  1846,  1847,  1847,  1848,  1848,  1849,
    1849,  1850,  1850,  1851,  1851,  1852,  1852,  1853,  1853,  1854,
    1854,  1855,  1855,  1856,  1856,  1857,  1857,  1858,  1858,  1859,
    1859,  1860,  1860,  1861,  1861,  1862,  1862,  1863,  1863,  1864,
    1864,  1867,  1867,  1870,  1870,  1871,  1871,  1872,  1872,  1875,
    1875,  1876,  1876,  1877,  1877,  1880,  1880,  1881,  1881,  1884,
    1884,  1887,  1887,  1890,  1891,  1892,  1895,  1895
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "tknName", "tknID", "tknStrLit",
  "tknCharLit", "tknNumber", "tknMacro", "tknApiDecor", "tknTypedef",
  "tknUsing", "tknInteger", "tknChar", "tknDouble", "tknFloat", "tknEnum",
  "tknAuto", "tknPreProDef", "tknClass", "tknStruct", "tknUnion",
  "tknNamespace", "tknTemplate", "tknTypename", "tknDecltype",
  "tknFreeStandingBlockComment", "tknSideBlockComment",
  "tknFreeStandingLineComment", "tknSideLineComment", "tknScopeResOp",
  "tknNumSignSpec", "tknPublic", "tknProtected", "tknPrivate",
  "tknExternC", "tknUnRecogPrePro", "tknStdHdrInclude", "tknPragma",
  "tknHashError", "tknEllipsis", "tknConstCast", "tknStaticCast",
  "tknDynamicCast", "tknReinterpretCast", "tknTry", "tknCatch", "tknThrow",
  "tknSizeOf", "tknOperator", "tknPlusEq", "tknMinusEq", "tknMulEq",
  "tknDivEq", "tknPerEq", "tknXorEq", "tknAndEq", "tknOrEq", "tknLShift",
  "tknLShiftEq", "tknRShiftEq", "tknCmpEq", "tknNotEq", "tknLessEq",
  "tknGreaterEq", "tkn3WayCmp", "tknAnd", "tknOr", "tknInc", "tknDec",
  "tknArrow", "tknArrowStar", "tknLT", "tknGT", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'^'", "'&'", "'|'", "'~'", "'!'", "'='", "','", "'('", "')'",
  "'['", "']'", "';'", "tknNew", "tknDelete", "tknConst", "tknConstExpr",
  "tknVoid", "tknOverride", "tknFinal", "tknAsm", "tknBlob", "tknStatic",
  "tknExtern", "tknVirtual", "tknInline", "tknExplicit", "tknFriend",
  "tknVolatile", "tknMutable", "tknNoExcept", "tknPreProHash", "tknDefine",
  "tknUndef", "tknInclude", "tknImport", "tknIf", "tknIfDef", "tknIfNDef",
  "tknElse", "tknElIf", "tknEndIf", "tknFor", "tknWhile", "tknDo",
  "tknSwitch", "tknCase", "tknDefault", "tknReturn", "tknBlankLine",
  "COMMA", "TERNARYCOND", "RSHIFT", "PREINCR", "PREDECR", "UNARYMINUS",
  "CSTYLECAST", "DEREF", "ADDRESSOF", "POSTINCR", "POSTDECR",
  "FUNCTIONALCAST", "FUNCCALL", "SUBSCRIPT", "'.'", "GLOBAL", "TEMPLATE",
  "PTRDECL", "REFDECL", "CTORDECL", "DTORDECL", "'{'", "'}'", "':'", "'?'",
  "$accept", "progunit", "$@1", "optstmtlist", "$@2", "$@3", "stmtlist",
  "$@4", "$@5", "$@6", "stmt", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "$@15", "$@16", "$@17", "$@18", "$@19", "$@20", "$@21",
  "$@22", "$@23", "$@24", "$@25", "$@26", "$@27", "$@28", "$@29", "$@30",
  "$@31", "$@32", "$@33", "$@34", "$@35", "$@36", "$@37", "$@38", "$@39",
  "$@40", "$@41", "$@42", "$@43", "preprocessor", "$@44", "$@45", "$@46",
  "$@47", "$@48", "$@49", "$@50", "asmblock", "$@51", "macrocall", "$@52",
  "$@53", "$@54", "switchstmt", "$@55", "caselist", "$@56", "$@57", "$@58",
  "$@59", "$@60", "block", "$@61", "$@62", "ifblock", "$@63", "$@64",
  "$@65", "whileblock", "$@66", "$@67", "dowhileblock", "$@68", "forblock",
  "$@69", "$@70", "$@71", "forrangeblock", "$@72", "tryblock", "$@73",
  "$@74", "catchblock", "$@75", "optexpr", "$@76", "$@77", "define",
  "$@78", "$@79", "$@80", "$@81", "$@82", "$@83", "undef", "$@84",
  "include", "$@85", "$@86", "import", "$@87", "$@88", "hashif", "$@89",
  "$@90", "$@91", "$@92", "$@93", "$@94", "$@95", "hasherror", "$@96",
  "pragma", "$@97", "doccomment", "$@98", "doccommentstr", "$@99", "$@100",
  "$@101", "$@102", "identifier", "$@103", "$@104", "$@105", "$@106",
  "$@107", "$@108", "$@109", "$@110", "numbertype", "$@111", "$@112",
  "$@113", "$@114", "typeidentifier", "$@115", "$@116", "$@117", "$@118",
  "$@119", "$@120", "$@121", "$@122", "$@123", "$@124", "$@125", "$@126",
  "$@127", "$@128", "templidentifier", "$@129", "templqualifiedid",
  "$@130", "name", "$@131", "id", "$@132", "optname", "$@133", "$@134",
  "enumitem", "$@135", "$@136", "$@137", "$@138", "$@139", "$@140", "blob",
  "$@141", "enumitemlist", "$@142", "$@143", "$@144", "$@145", "enumdefn",
  "$@146", "$@147", "$@148", "$@149", "$@150", "$@151", "$@152",
  "enumdefnstmt", "$@153", "enumfwddecl", "$@154", "$@155", "$@156",
  "funcptrtypedef", "$@157", "typedefnamestmt", "$@158", "typedefliststmt",
  "$@159", "typedeflist", "$@160", "typedefname", "$@161", "usingdecl",
  "$@162", "$@163", "$@164", "$@165", "$@166", "$@167", "namespacealias",
  "$@168", "usingnamespacedecl", "$@169", "vardeclliststmt", "$@170",
  "$@171", "vardeclstmt", "$@172", "$@173", "$@174", "$@175", "$@176",
  "vardecllist", "$@177", "$@178", "$@179", "varinit", "$@180", "$@181",
  "$@182", "$@183", "$@184", "$@185", "$@186", "$@187", "$@188",
  "varassign", "$@189", "$@190", "$@191", "optvarassign", "$@192", "$@193",
  "vardecl", "$@194", "$@195", "$@196", "$@197", "$@198", "$@199", "$@200",
  "vartype", "$@201", "$@202", "$@203", "$@204", "$@205", "$@206", "$@207",
  "$@208", "$@209", "$@210", "$@211", "$@212", "varidentifier", "$@213",
  "$@214", "$@215", "$@216", "$@217", "opttypemodifier", "$@218",
  "typemodifier", "$@219", "$@220", "$@221", "$@222", "$@223", "$@224",
  "$@225", "$@226", "exptype", "$@227", "$@228", "$@229", "varattrib",
  "$@230", "$@231", "$@232", "$@233", "typeconverter", "$@234", "$@235",
  "$@236", "$@237", "$@238", "$@239", "typeconverterstmt", "$@240",
  "$@241", "funcdeclstmt", "$@242", "funcdefn", "$@243", "lambda",
  "lambdaparams", "$@244", "$@245", "funcptrortype", "$@246", "$@247",
  "$@248", "$@249", "$@250", "$@251", "functionpointer", "functionptrtype",
  "funcobj", "$@252", "funcpointerdecl", "$@253", "funcdecldata", "$@254",
  "$@255", "funcdecl", "$@256", "$@257", "$@258", "$@259", "$@260",
  "$@261", "$@262", "$@263", "$@264", "$@265", "$@266", "$@267",
  "funcobjstr", "$@268", "funcname", "$@269", "$@270", "$@271", "$@272",
  "rshift", "$@273", "operfuncname", "$@274", "$@275", "$@276", "$@277",
  "$@278", "$@279", "$@280", "$@281", "$@282", "$@283", "$@284", "$@285",
  "$@286", "$@287", "$@288", "$@289", "$@290", "$@291", "$@292", "$@293",
  "$@294", "$@295", "$@296", "$@297", "$@298", "$@299", "$@300", "$@301",
  "$@302", "$@303", "$@304", "$@305", "$@306", "$@307", "$@308", "$@309",
  "$@310", "$@311", "$@312", "$@313", "$@314", "$@315", "$@316", "$@317",
  "$@318", "$@319", "$@320", "$@321", "paramlist", "$@322", "$@323",
  "param", "$@324", "$@325", "$@326", "$@327", "$@328", "$@329", "$@330",
  "$@331", "templatearg", "$@332", "$@333", "$@334", "$@335",
  "templatearglist", "$@336", "$@337", "functype", "$@338", "$@339",
  "$@340", "$@341", "$@342", "$@343", "optfunctype", "$@344", "$@345",
  "optfuncattrib", "$@346", "$@347", "$@348", "$@349", "$@350", "$@351",
  "$@352", "$@353", "$@354", "$@355", "$@356", "$@357", "optfuncthrowspec",
  "$@358", "$@359", "functhrowspec", "$@360", "identifierlist", "$@361",
  "$@362", "$@363", "ctordeclstmt", "$@364", "ctordefn", "$@365", "$@366",
  "$@367", "$@368", "$@369", "$@370", "$@371", "$@372", "$@373",
  "ctordecl", "$@374", "$@375", "$@376", "$@377", "$@378", "$@379",
  "$@380", "$@381", "meminitlist", "$@382", "$@383", "$@384", "meminit",
  "$@385", "$@386", "$@387", "$@388", "dtordeclstmt", "$@389", "dtordefn",
  "$@390", "$@391", "$@392", "$@393", "$@394", "$@395", "dtordecl",
  "$@396", "$@397", "$@398", "$@399", "$@400", "$@401", "$@402", "$@403",
  "$@404", "optvoid", "optcomment", "$@405", "$@406", "classdefnstmt",
  "$@407", "classdefn", "$@408", "$@409", "$@410", "$@411", "$@412",
  "namespacedefn", "$@413", "$@414", "optfinal", "$@415", "$@416",
  "optinheritlist", "$@417", "$@418", "$@419", "$@420", "$@421",
  "protlevel", "$@422", "$@423", "$@424", "$@425", "optinherittype",
  "$@426", "$@427", "fwddecl", "$@428", "$@429", "$@430", "$@431", "$@432",
  "classspecifier", "$@433", "$@434", "$@435", "templatespecifier",
  "$@436", "$@437", "templateparamlist", "$@438", "$@439", "$@440",
  "templateparam", "$@441", "$@442", "$@443", "$@444", "$@445", "$@446",
  "$@447", "$@448", "$@449", "$@450", "$@451", "$@452", "$@453", "$@454",
  "$@455", "optapidecor", "$@456", "$@457", "apidecor", "$@458", "$@459",
  "$@460", "$@461", "apidecortokensq", "$@462", "$@463", "changeprotlevel",
  "$@464", "$@465", "$@466", "externcblock", "$@467", "strlit", "$@468",
  "$@469", "expr", "$@470", "$@471", "$@472", "$@473", "$@474", "$@475",
  "$@476", "$@477", "$@478", "$@479", "$@480", "$@481", "$@482", "$@483",
  "$@484", "$@485", "$@486", "$@487", "$@488", "$@489", "$@490", "$@491",
  "$@492", "$@493", "$@494", "$@495", "$@496", "$@497", "$@498", "$@499",
  "$@500", "$@501", "$@502", "$@503", "$@504", "$@505", "$@506", "$@507",
  "$@508", "$@509", "$@510", "$@511", "$@512", "$@513", "$@514", "$@515",
  "$@516", "$@517", "$@518", "$@519", "$@520", "$@521", "$@522", "$@523",
  "$@524", "$@525", "$@526", "$@527", "$@528", "$@529", "$@530", "$@531",
  "$@532", "$@533", "$@534", "$@535", "$@536", "$@537", "$@538", "$@539",
  "$@540", "$@541", "$@542", "$@543", "$@544", "$@545", "$@546", "$@547",
  "$@548", "$@549", "$@550", "$@551", "$@552", "$@553", "$@554", "$@555",
  "$@556", "$@557", "$@558", "exprlist", "$@559", "$@560", "$@561",
  "exprorlist", "$@562", "$@563", "$@564", "funcargs", "$@565", "$@566",
  "captureallbyref", "$@567", "captureallbyval", "$@568", "lambdacapture",
  "exprstmt", "$@569", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,    43,    45,    42,    47,    37,    94,
      38,   124,   126,    33,    61,    44,    40,    41,    91,    93,
      59,   329,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,    46,   380,   381,   382,   383,   384,   385,   123,
     125,    58,    63
};
# endif

#define YYPACT_NINF -1585

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-1585)))

#define YYTABLE_NINF -922

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    5365, -1585, -1585, -1585, -1585,    43, -1585, -1585,  9049,   370,
   -1585, -1585,   141,  1008,   622,  1133,  1133,    43,   632,   792,
      -9, -1585, -1585,   853,   663,    76, -1585,    23,    34,    83,
      86,    76,  7027,   259,  8771,  7027,  7027,   187,  7027,  7027,
    7027,  7027,  7027,  5516,  6057, -1585,  7124,  7221, -1585,  9154,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  3110,
   -1585, -1585,  1200,   134,   157,   168,  5365,   179,  6348,  4918,
     273,   996, -1585,  5365, -1585, -1585, -1585,  4686, -1585, -1585,
     199, -1585, -1585, -1585, -1585,   279, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585,    76,   411,  3003, -1585,  9648, -1585, -1585,
     639, -1585,   728, -1585, -1585, -1585, -1585, -1585,   290,   306,
   -1585, -1585, -1585, -1585, -1585,   701,   365,  1113,  3163,  9183,
    9183,    32, -1585, -1585, -1585, -1585,   675,   372, -1585, -1585,
     201,   243,   277,  4478,  9183, -1585, -1585, -1585,   413, -1585,
   -1585,   723, -1585,  1167, -1585, -1585,   538,  3988,  8876,   119,
   -1585,   518,  5269, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,   519,   192, -1585,  1133, -1585, -1585, -1585,   453,
     508,  9648,   887,  1147,   468,   -25,   750, -1585,  9288,   568,
    9288,  1147,    75,  9288,  9288,  1133,  1133,   739,   493, -1585,
   -1585,   515,  2084,   508,   629,   535, -1585,    43, -1585, -1585,
    1133,   625,   802,  9537,  3919,   860,   312, -1585, -1585,   653,
     605, -1585,  1292, -1585,  1292, -1585,  1292, -1585,   626,   618,
   -1585,   508,   928, -1585,   508,  7027, -1585, -1585,   631,   860,
     277, -1585, -1585,  5365, -1585,    76, -1585, -1585,  9288,  9288,
    9288,  9288,   279,  7027,  4177,    87,  8668, -1585,   643,  5738,
      43,   192, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585,   659, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,   668,   700,
     694,   709,  9623,   418,  9288,   224, -1585,  9288,   893,  8668,
    8668, -1585,  8668,  8668,   242,  8668,   766,  8668,  8668,  6445,
     450,  7321,   798,   809,  7027, -1585, -1585, -1585, -1585, -1585,
   -1585,   832, -1585,  5516,   371,  8668,  5960,  8668, -1585, -1585,
     715, -1585, -1585,   228,  9317, -1585,  9317,  9317, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,   625, -1585, -1585,
    3110,   316, -1585, -1585,  1492,   356, -1585, -1585,   902, -1585,
      43,    43,   398,   507,   910,    43,   634, -1585,   924, -1585,
    5849,  5627,  5849,   835,  7027, -1585, -1585, -1585,   238,  6445,
    4579,    52,   105, -1585,   790,   813,   814, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585,  6542, -1585, -1585, -1585, -1585, -1585,
    5365, -1585, -1585, -1585, -1585, -1585,   884, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585,   878, -1585,  5738,  6348, -1585, -1585, -1585,  2084,   563,
   -1585, -1585, -1585, -1585,   578, -1585, -1585,  1227, -1585, -1585,
   -1585,    72,  5738,  8910, -1585, -1585, -1585, -1585, -1585,  1227,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,  1147, -1585, -1585,  7027,  6154,  6639, -1585,  6348,
    7027, -1585,   552,   469,  3919, -1585,   819, -1585, -1585,  3919,
    9183, -1585,   724,  9183, -1585,  9183, -1585,  1113,   750, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,   972, -1585, -1585,
   -1585, -1585,  1249, -1585, -1585, -1585, -1585,   954,   -22, -1585,
   -1585, -1585,  6348,  5738, -1585,  9288,    43,  9317,   932,  3651,
     921,   228,  4478, -1585, -1585,   -16, -1585,   160,  4478,  4478,
     895,  1140, -1585, -1585,   226, -1585, -1585,  1133, -1585,   125,
   -1585, -1585, -1585,    78, -1585, -1585,  1249, -1585, -1585, -1585,
   -1585,  1227, -1585, -1585,   500,   374,   481, -1585,  1133,  1133,
   -1585,   -25,   921,   228, -1585,   -16, -1585,   160,  1294, -1585,
     983,   833, -1585,   921,   224,   228,  4478,   122,   606,  9015,
   -1585,   206, -1585, -1585, -1585, -1585, -1585,  7027,  7027,  7027,
    7027,  7027,  7027,  7027,  7027,  7027,  7027,  7027,  7027,  7027,
    7027,  7027,  7027,  7027,  7027, -1585, -1585,  4765,  3919,  7027,
    6736,  7027,  7027,  7027,  7027,  7027,  7027,  7027,  7027,  7027,
    6348,  6833, -1585,  9451,  7027,  7027, -1585, -1585,   515,   515,
   -1585,    43,   508,  1133, -1585, -1585, -1585, -1585,   508,   -25,
   -1585,   470, -1585,  1133,   640,   224,   839, -1585,  9288,   232,
      43,    25, -1585,  2084, -1585, -1585,   693, -1585,   736,   976,
     802,  2084, -1585,  9288,  8910, -1585, -1585, -1585, -1585,  1133,
   -1585,  9422, -1585, -1585, -1585,  4323,  7027, -1585, -1585, -1585,
   -1585,   744,   762,   831,   929, -1585, -1585,  5738,   487,  7363,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
     982, -1585,   992, -1585,  1011, -1585,   215,   640, -1585, -1585,
    1012, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  1014,
   -1585, -1585,  2768,  3772,   798, -1585,   515,  7027,  7027, -1585,
    7027, -1585, -1585, -1585, -1585, -1585,  1029,  1733, -1585, -1585,
    7027, -1585, -1585, -1585,  9317,  4023, -1585, -1585,  1133, -1585,
   -1585,  1393, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585,  1035,  7466,  1045,  6445,   755,  1048,
     911,  7321,   798,  1038,  7508,  1057,  7611, -1585, -1585, -1585,
    5163, -1585,   999, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
    7653, -1585, -1585,  9288, -1585, -1585, -1585, -1585,  8771,   860,
    1136,   277, -1585,  3372,   640, -1585, -1585, -1585,   559,  8668,
    1019, -1585,   508,   312, -1585, -1585, -1585, -1585, -1585,  9723,
   -1585, -1585, -1585, -1585, -1585,    43, -1585,   588,  8910, -1585,
     715,  1170,   491,   621, -1585, -1585, -1585, -1585, -1585, -1585,
      43, -1585, -1585,  8668, -1585,  1099,  1085, -1585,  7756, -1585,
    1026,  8668, -1585, -1585,    90,    43,   922, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,  1181, -1585, -1585,
   -1585, -1585, -1585, -1585,  1133, -1585, -1585, -1585, -1585, -1585,
    1102,   594,   766,   973,   515, -1585, -1585, -1585, -1585, -1585,
   -1585,  9015,  1147,  1147, -1585, -1585, -1585, -1585,    70, -1585,
   -1585,  1133, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585,  1088, -1585,  1120, -1585,
   -1585,   500, -1585,  1047, -1585,   580, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585,   973, -1585, -1585, -1585, -1585,
     122,   606, -1585, -1585,  9015,   122,  9015, -1585,  1111,  1119,
   -1585, -1585,  8668,  8668,  8668,  8668,  8668,  8668,  8668,  8668,
    8668,  8668,  8668,  8668,  8668,  8668,  8668,  8668,  8668,  8668,
   -1585, -1585,  3919, -1585, -1585,  8668,  8668,  8668,  8668,  8668,
    8668,  8668,  8668,  8668,  8668,  8668,  1121, -1585,  7798, -1585,
    3919, -1585,  7901,  8668,    43,   693,  1058,   508, -1585,   655,
   -1585, -1585,   304,  1129,  1130,  1175, -1585,  2084,   714, -1585,
     564,   113, -1585, -1585,  2084, -1585,  9288,   640,   866, -1585,
   -1585, -1585,  1078,  5365,   870,   792,   323,  1127,   615, -1585,
   -1585, -1585, -1585,  7943,  1135,  1148,  1149,  1162, -1585,   611,
    8046, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585,  1163,  1165, -1585, -1585,  8668,  8668,  8668, -1585,  8910,
     233, -1585,  7027,  8668, -1585,  1115, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585,  5365,  5365,  6348,  7321,   798,  6348,  6348,
    7027, -1585, -1585,  5365,  5365,  7027,  1100, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,   359,   661,
   -1585,    85, -1585,  1173, -1585, -1585, -1585, -1585,  5738, -1585,
   -1585, -1585,  1227, -1585, -1585, -1585, -1585, -1585,  1184,  1241,
   -1585, -1585, -1585,  7027,  6930, -1585, -1585,  8910, -1585,   209,
   -1585, -1585,    43,   239,    43, -1585, -1585, -1585, -1585, -1585,
   -1585,    43,  1185,  1188,    43,  1056, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585,   508,   874, -1585, -1585, -1585,
   -1585, -1585,  9288,  1050,    43,    43, -1585, -1585,  6251,  5046,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
    2084,  2084, -1585,  1088,  1120, -1585, -1585, -1585, -1585,  1126,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585,   820, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585,  7027, -1585, -1585, -1585, -1585, -1585,  1193, -1585, -1585,
   -1585, -1585,   747, -1585,  2084,   327, -1585,   613, -1585, -1585,
   -1585,   453, -1585,  1201, -1585, -1585,   402,    59,   640, -1585,
     224, -1585,   245,   620,  1202,   516,  1203,  7027,  1204, -1585,
    7027, -1585, -1585,  9422, -1585, -1585,  7027,  7027,  7027,  7027,
    7027, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,   886,  9288, -1585,  8668, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585,  1206,  1209,  1214,  8088, -1585, -1585,
    8191,   957, -1585, -1585, -1585,  1205,   215,    43, -1585,  8910,
   -1585, -1585, -1585, -1585,  1219,  8910,    93, -1585,  8668, -1585,
    8233, -1585, -1585,  6348, -1585, -1585, -1585, -1585,    43,    43,
   -1585, -1585, -1585, -1585, -1585, -1585,  1221, -1585, -1585,  1234,
    1064, -1585, -1585, -1585,  1133, -1585, -1585, -1585,    43,  1090,
     209,   209, -1585,  1237, -1585,  1176, -1585,   312,   312,  2084,
    2084,  5365, -1585, -1585,   481, -1585, -1585, -1585,  1238, -1585,
   -1585, -1585, -1585, -1585, -1585,  8668,   421, -1585,  8910, -1585,
   -1585, -1585, -1585,   557,   147, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585,  7027, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,  1249, -1585, -1585, -1585, -1585,  9288, -1585, -1585,
   -1585, -1585,  9288, -1585,  8668,  7027, -1585,  8668, -1585, -1585,
    8668,  8336,  8378,  8481,  8523, -1585, -1585, -1585, -1585, -1585,
     103, -1585, -1585, -1585,  6348,  6348,  6348,  5365, -1585, -1585,
   -1585,   110, -1585,   979,    76,  1240, -1585,  1242,   923, -1585,
    1243,   950,    43, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  1258,    43,
     508, -1585,  1248,  1177, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,   312,   312,   248,  1180, -1585, -1585,    43,   958,
   -1585, -1585, -1585, -1585, -1585,  8668, -1585,   583, -1585, -1585,
   -1585, -1585,   640, -1585, -1585, -1585,   640, -1585,  8668, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  1260,
    1261,  1265, -1585, -1585,  7027,  1208, -1585,   411,   261, -1585,
   -1585,  1267,  8910, -1585,    76,  1307, -1585,  1269, -1585, -1585,
   -1585, -1585,  8910,  1274, -1585,  1270,    43, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,   587,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  5365,
    5365,  5365, -1585,  8626,  5365, -1585, -1585, -1585, -1585, -1585,
    1275,   965, -1585, -1585,  1212, -1585, -1585,  1279,  8910,   974,
    1285,  8910,  1286, -1585,  5365, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,  5365,   996,    76,  1307,   125, -1585,  1290,   989,
   -1585,  8910,  1007,  1297,   272, -1585, -1585, -1585, -1585,   996,
   -1585, -1585,  1212, -1585,    76,  1307, -1585,  1010, -1585,  8910,
   -1585, -1585,   125, -1585, -1585,  1212, -1585, -1585,  1074, -1585,
   -1585,   125, -1585, -1585, -1585, -1585, -1585, -1585
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,   262,   264,   935,   941,   943,   104,   923,     0,     0,
     223,   225,   266,   239,   866,   868,   870,   266,     0,     0,
       0,   199,   201,     0,   227,   459,   248,     0,     0,     0,
       0,     0,  1097,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1125,    84,     0,     0,   461,   692,
     241,   215,   549,   102,   455,   457,   686,   684,   688,   690,
     463,   465,     0,     0,     0,     0,     0,     0,  1093,     4,
       0,     2,     5,     6,     8,    66,    86,    80,    70,    68,
      36,    38,    40,    42,    44,    72,    88,    90,    92,    94,
      96,    98,   100,    32,   197,   947,   237,   436,   213,   221,
     207,   211,   416,    18,    20,    64,    22,    24,     0,     0,
      74,    78,    76,    16,    14,     0,     0,     0,     0,   682,
       0,     0,    60,    48,    50,  1109,   508,   390,   410,    46,
       0,     0,   543,     0,     0,   695,    52,    54,   766,    56,
      58,     0,    26,   412,    28,    30,   834,     0,     0,   915,
      62,   939,     0,    34,   263,   265,   936,   942,  1111,   944,
     105,   924,     0,   266,   239,     0,   459,   467,   690,   219,
     231,   436,   207,   416,   320,   322,     0,   682,     0,   390,
       0,   412,   834,     0,     0,     0,     0,     0,   207,   224,
     226,     0,     0,   243,   207,     0,   267,     0,   912,   913,
       0,     0,     0,     0,     0,   231,   545,   240,   207,     0,
       0,   252,   436,   867,   436,   869,   436,   871,   268,     0,
     872,     0,   260,   250,   245,     0,   200,   202,     0,   233,
     547,   229,   228,     4,   933,     0,   460,   249,     0,     0,
       0,     0,     0,     0,     0,   231,  1095,  1098,     0,     0,
       0,   266,   579,   581,   583,   585,   587,   589,   591,   593,
     595,   599,   601,   603,   605,   607,   609,   611,   613,   615,
     617,   619,   623,   625,   575,   577,   553,   555,   557,   559,
     561,   563,   565,   567,   569,   571,   573,   621,     0,     0,
     631,   635,   436,     0,     0,   508,   597,     0,     0,   972,
     976,   945,   960,   966,   970,   968,   207,   962,   964,     0,
       0,  1119,  1121,     0,  1129,  1131,  1127,  1133,  1126,  1134,
    1135,     0,    85,     0,  1079,  1081,     0,  1087,   462,   376,
       0,   468,   390,   527,     0,   693,     0,     0,   242,   216,
     550,   103,   456,   458,   687,   685,   689,   866,   868,   870,
       0,     0,   691,   864,     0,     0,   464,   466,     0,   193,
       0,     0,     0,     0,     0,     0,     0,   187,     0,   191,
       0,   152,     0,     0,     0,  1094,  1091,   958,     0,   197,
    1119,     0,     0,     1,     0,     0,     0,     3,    12,     7,
      10,     9,    67,    87,     0,    82,    81,   220,    71,    69,
       0,    37,    39,    41,    43,    45,     0,    73,   148,    89,
      91,    93,    95,    97,    99,   101,    33,   124,   203,   205,
     198,     0,   217,   670,  1125,   232,   948,   238,     0,   254,
     445,   441,   443,   439,     0,   402,   437,   438,   546,   214,
     222,     0,   670,   649,   208,   922,   212,   306,   417,   418,
      19,    21,    65,    23,    25,   318,   316,    75,    79,    77,
      17,    15,   436,   340,   346,     0,     0,     0,   344,  1125,
       0,   374,   422,   911,     0,   428,   426,   388,   519,     0,
       0,   350,     0,   682,   683,     0,   352,     0,   420,   481,
     475,   483,    61,    49,    51,  1110,   719,     0,   698,   700,
     702,   704,   505,   511,   391,   411,    47,     0,     0,   485,
     487,   539,  1125,   670,   544,     0,     0,   692,   231,     0,
     473,   533,     0,   697,   746,   752,   792,   799,     0,     0,
       0,     0,    53,    55,     0,   733,   762,     0,   760,     0,
     767,    57,    59,     0,   780,   782,   801,   809,    27,   817,
     413,   414,    29,    31,   844,     0,   813,   835,     0,     0,
     332,   398,   479,   531,   748,   754,   790,     0,   412,   860,
     231,   207,   348,   477,   503,   529,     0,   764,   797,     0,
     925,     0,   916,    63,   937,   940,  1107,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   974,   978,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1125,     0,  1136,     0,     0,     0,    35,  1112,   911,     0,
     207,   266,   233,     0,   321,   323,   422,   428,   426,   400,
     314,     0,   921,     0,     0,   503,     0,   334,     0,   921,
       0,     0,   244,     0,   269,   284,     0,   914,   639,     0,
       0,     0,   254,     0,   649,   253,   404,   406,   408,     0,
     827,   875,   261,   251,   246,     0,     0,   234,   548,   230,
     934,     0,     0,     0,     0,   146,  1096,     0,     0,     0,
     645,   580,   582,   584,   586,   588,   590,   592,   594,   596,
     600,   602,   604,   606,   608,   610,   612,   614,   616,   618,
     620,   624,   626,   576,   551,   578,   554,   556,   558,   560,
     562,   564,   566,   568,   570,   572,   574,   622,   627,   629,
       0,   632,     0,   636,   441,   640,   911,   420,   598,   866,
       0,   825,   973,   977,   946,   961,   967,   971,   969,   811,
     963,   965,   199,   201,  1117,  1123,   911,     0,     0,  1120,
       0,  1122,  1077,  1130,  1132,  1128,   491,     0,  1080,  1082,
       0,  1088,   377,   528,     0,     0,   862,   865,     0,   195,
     194,   159,   169,   171,   173,   175,   177,   179,   181,   185,
     183,   188,   189,   192,     0,     0,     0,     0,     0,     0,
       0,   153,   155,     0,     0,     0,     0,  1092,   959,   122,
       0,   950,     0,   954,   927,   929,   931,    13,    11,   106,
       0,    83,   130,     0,   149,   125,   204,   206,     0,   209,
     207,   643,   218,   436,   672,   674,   678,   671,     0,   676,
       0,   949,   231,   235,   255,   446,   442,   444,   440,     0,
     403,   453,   449,   451,   447,     0,   737,     0,     0,   654,
     658,   660,   507,     0,   650,   651,   307,   419,   319,   317,
       0,   341,   347,   378,   372,   545,     0,   394,     0,   345,
       0,   396,   375,   423,     0,     0,     0,   521,   429,   427,
     389,   520,   517,   351,   342,   353,   401,   421,   482,   476,
     484,   720,   706,   699,   701,   703,   705,     0,   709,   711,
     713,   715,   506,   512,   727,   535,   537,   486,   488,   540,
       0,     0,     0,     0,   911,   474,   534,   747,   753,   793,
     800,     0,   436,   436,   756,   758,   734,   763,     0,   768,
     761,     0,   735,   706,   805,   807,   781,   783,   802,   810,
     818,   415,   846,   848,   850,   854,   852,   845,   844,   853,
     856,   844,   815,     0,   814,   830,   333,   399,   480,   532,
     749,   755,   791,   826,   861,     0,   349,   478,   504,   530,
     752,   799,   765,   798,     0,   754,     0,   926,     0,     0,
     938,  1108,  1006,  1008,  1010,  1012,  1014,  1016,  1018,  1020,
    1022,  1026,  1028,  1030,  1032,  1034,  1036,  1038,  1040,  1043,
     975,   979,     0,  1047,  1049,  1000,  1002,   980,   982,   984,
     987,   989,   996,   991,   994,   998,     0,  1057,     0,  1137,
       0,  1045,     0,  1024,   266,     0,     0,   209,   315,   830,
     338,   335,     0,   410,     0,   412,   312,     0,     0,   284,
       0,     0,   285,   284,     0,   641,     0,   523,     0,   405,
     407,   409,     0,     4,   866,   266,   897,   893,     0,   876,
     877,   247,   256,     0,     0,     0,     0,     0,   147,     0,
       0,  1099,  1101,   646,   552,   628,   630,   633,   637,   642,
     812,     0,     0,  1118,  1124,  1067,  1113,  1115,  1078,   649,
       0,   492,     0,  1089,   863,     0,   196,   163,   165,   161,
     167,   160,   157,   170,   172,   174,   176,   178,   180,   182,
     186,   184,   190,     0,     0,   152,     0,  1117,   152,   152,
       0,   154,   156,     0,     0,     0,     0,   123,   952,   951,
     956,   955,   928,   930,   932,   107,   108,   131,   266,     0,
     210,     0,   644,     0,   673,   675,   679,   258,   670,   677,
    1065,   236,   424,   454,   450,   452,   448,   784,     0,     0,
     664,   655,   659,     0,     0,   661,   663,     0,   750,   384,
     379,   373,     0,     0,     0,   370,   380,   395,   392,   382,
     397,     0,     0,     0,   266,     0,   522,   518,   343,   707,
     717,   710,   712,   714,   716,   729,     0,   728,   536,   538,
    1061,   647,     0,     0,     0,     0,   757,   759,     0,     0,
     769,   770,   736,   804,   806,   808,   847,   849,   851,   855,
       0,     0,   857,   852,   844,   816,   822,   858,   832,   834,
     831,   919,   917,  1007,  1009,  1011,  1013,  1015,  1017,  1019,
    1021,  1023,  1027,  1029,  1031,  1033,  1035,  1037,  1039,  1041,
    1044,   231,  1053,  1048,  1050,  1001,  1003,   981,   983,   985,
     988,   990,   997,   992,   995,   999,  1059,  1058,  1055,  1051,
    1046,     0,  1025,   268,   284,   339,   324,     0,   326,   328,
     330,   313,     0,   284,     0,     0,   308,   290,   282,   292,
     276,   278,   274,   270,   286,   280,     0,     0,   525,   524,
     513,   336,     0,   207,   885,   207,   881,     0,   889,   898,
       0,   894,   873,     0,   878,   257,     0,     0,     0,     0,
       0,  1103,  1105,  1100,  1102,   634,   638,   469,   794,  1068,
    1114,  1116,     0,     0,   489,  1083,  1090,   164,   166,   162,
     168,   158,   128,   126,     0,     0,     0,   396,   134,   132,
       0,   112,   953,   957,   109,     0,   911,     0,   740,   649,
     259,   680,  1066,   425,     0,   649,     0,   665,   656,   668,
       0,   652,   751,     0,   386,   358,   385,   368,     0,     0,
     360,   366,   371,   381,   393,   383,     0,   432,   430,     0,
       0,   708,   718,   730,     0,   725,  1062,   648,   266,     0,
     384,   384,   774,     0,   778,     0,   771,   836,   840,     0,
       0,     4,   859,   833,   813,   920,   918,  1042,     0,  1054,
     986,   993,  1060,  1056,  1052,  1004,     0,   325,   649,   327,
     329,   331,   310,     0,     0,   296,   309,   288,   291,   283,
     293,   277,   279,   275,     0,   271,   287,   281,   298,   284,
     526,   514,   515,   337,   828,   909,   907,     0,   886,   905,
     903,   901,     0,   882,   899,     0,   890,   895,   874,   879,
    1085,     0,     0,     0,     0,  1104,  1106,   470,   795,   493,
       0,  1084,   129,   127,   152,   152,   152,     0,   135,   133,
     136,     0,   113,   112,     0,     0,   786,     0,     0,   681,
       0,     0,     0,   743,   657,   669,   666,   653,   387,   359,
     369,   362,   364,   361,   367,   434,   433,   431,     0,   266,
     731,   726,     0,     0,   354,   356,   775,   772,   779,   776,
     837,   841,   838,   842,     0,     0,  1063,  1005,     0,     0,
     311,   302,   284,   297,   289,   272,   299,     0,   516,   829,
     910,   908,   887,   906,   904,   902,   883,   900,   891,   896,
     880,  1086,  1069,  1071,  1073,  1075,   796,   494,   490,     0,
       0,     0,   144,   137,     0,     0,   110,   120,   118,   150,
     471,     0,   649,   541,     0,   721,   788,     0,   667,   363,
     365,   435,   649,     0,   732,     0,   266,   355,   357,   773,
     777,   839,   843,   823,   819,  1064,   304,   509,   303,     0,
     273,   294,   888,   884,   892,  1070,  1072,  1074,  1076,     0,
       0,     0,   145,     0,     4,   111,   121,   119,   151,   472,
       0,     0,   542,   785,   766,   722,   723,     0,   649,     0,
       0,   649,     0,   824,     4,   305,   510,   300,   295,   138,
     142,   140,     4,   116,     0,   721,     0,   724,     0,     0,
     501,   649,     0,     0,     0,   301,   139,   143,   141,   114,
     117,   787,   766,   738,     0,   721,   502,     0,   499,   649,
     820,   115,     0,   739,   789,   766,   497,   500,     0,   821,
     741,     0,   498,   495,   742,   744,   496,   745
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1585, -1585, -1585,     7, -1585, -1585, -1585, -1585, -1585, -1585,
     -33, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  -938, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,   647, -1585,
   -1585, -1585, -1585, -1585,  -123, -1585, -1585, -1585, -1585, -1585,
      31, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585,  1144, -1585, -1020, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585,  2167, -1585,  2486, -1585, -1585, -1585, -1585,
    1098, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  1367,
   -1585, -1585, -1585, -1585,  1933, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,    30,
   -1585, -1585, -1585,     0, -1585, -1585, -1585,    15, -1585, -1585,
      96, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1026,
   -1585, -1585, -1585, -1585,   909, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,  1247, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,   -94, -1585, -1585, -1585, -1585, -1585,    13, -1585,
   -1585, -1585,   235, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1164, -1585, -1585, -1585, -1296, -1585, -1585,    45,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,  2473, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585,  -198, -1585,   -99, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,   719, -1585, -1585,
   -1585,  1815, -1585, -1585, -1585, -1585,  -109, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585,  3386, -1585, -1585, -1585, -1585, -1585,
   -1585,  1009,   749, -1585, -1585, -1585, -1585,    17, -1585, -1585,
     -36, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585,   -11, -1585, -1585, -1585, -1585,
     -30, -1585,    -3, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585,  -645, -1585, -1585,  -830, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585,   244, -1585, -1585, -1585, -1585,  -351, -1585,
   -1585,  2702, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585,  -140, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1584, -1585, -1585,  -119, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585,   -88, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585,   -97, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1193, -1585, -1585, -1585,   462, -1585,
   -1585, -1585, -1585, -1585, -1585,   -57, -1585, -1585, -1585, -1585,
   -1585, -1585,   -76, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585,  -739,   -20, -1585, -1585, -1585, -1585,   894, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
     166, -1585, -1585, -1585, -1585, -1585,  -894, -1585, -1585, -1585,
   -1585,  -909, -1585, -1585,   -17, -1585, -1585, -1585, -1585, -1585,
     217, -1585, -1585, -1585,  1841, -1585, -1585, -1585, -1585, -1585,
   -1585,    84, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,    -6, -1585, -1585,
    3173, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,  4099, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585, -1585, -1585,   -40, -1585, -1585,
   -1585,    18, -1585, -1585, -1585,  -389, -1585, -1585, -1585, -1585,
   -1585, -1585, -1585, -1585, -1585
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    70,   387,   378,    72,   389,    73,   391,   818,   817,
      74,   461,   460,   450,   451,   453,   454,   548,   552,   553,
     416,   626,   401,   402,   403,   404,   405,   506,   493,   494,
     532,   533,   541,   542,   492,   583,   452,   392,   399,   398,
     407,   457,   459,   458,   396,   821,   322,   393,    75,   409,
     410,   411,   412,   413,   414,   415,    76,   341,   169,   160,
    1145,  1364,    78,  1635,  1501,  1502,  1691,  1680,  1637,  1636,
      79,  1137,   825,    80,  1493,  1492,  1147,    81,  1499,  1498,
      82,  1583,    83,  1676,  1678,  1677,    84,  1632,    85,  1078,
     824,   408,  1638,   796,  1131,  1132,    86,  1351,  1111,  1349,
    1347,  1348,  1350,    87,  1113,    88,  1114,  1115,    89,  1116,
    1117,    90,  1118,  1119,  1121,  1120,   791,  1122,   793,    91,
     780,    92,  1106,    93,   420,    94,   226,   227,   826,   827,
     245,   444,  1150,   446,   439,   339,   832,   397,   440,    96,
     189,   190,   232,   679,   206,   425,   677,  1161,   427,   207,
     338,   652,   674,  1071,   237,   673,   665,   844,  1325,    98,
    1370,    99,   672,   208,   154,   101,   155,   195,   196,   654,
    1304,  1455,  1620,  1453,  1451,  1452,  1457,  1305,  1449,  1051,
    1052,  1456,  1554,  1448,   173,  1450,  1658,  1553,  1556,  1675,
    1618,  1655,   103,   866,   104,  1446,  1550,  1291,   105,  1038,
     106,   869,   107,   868,   108,   634,   109,   635,   110,  1437,
    1439,  1440,  1441,   966,  1041,   111,  1463,   112,  1285,   113,
     871,  1198,   114,   879,   872,   976,   893,   895,   115,  1607,
    1608,  1519,   116,  1523,  1599,  1600,  1524,  1520,  1392,  1181,
     882,   772,   471,  1180,  1393,  1395,  1385,  1386,  1518,   117,
     890,   504,  1394,  1187,  1190,   967,   896,   118,   850,  1059,
    1060,  1061,   505,   550,   951,   448,   867,   897,   883,  1373,
     477,   889,   888,  1527,  1526,  1601,   435,   436,   437,   848,
     846,   847,   845,  1166,  1164,  1165,  1163,   177,   342,   343,
     236,   294,   328,   356,   357,   331,   121,  1487,  1639,   925,
     899,   977,   968,   122,   898,   900,   123,   917,   124,   918,
     125,  1100,  1101,  1577,   126,  1706,  1702,  1697,  1686,   978,
     912,   332,   128,  1044,  1656,   129,   913,   478,  1461,  1558,
     130,  1197,   891,  1196,  1309,  1460,   773,   979,   969,   926,
    1208,  1209,   919,   835,  1642,   131,   514,   438,   678,   340,
     625,  1084,   132,   716,   717,   718,   719,   720,   721,   722,
     723,   724,   725,   726,   713,   715,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   738,   700,   701,   702,   703,
     704,   705,   706,   707,   708,   709,   710,   727,   711,   712,
    1085,  1086,   731,  1335,   733,  1336,   735,  1089,  1152,  1083,
    1407,   863,   864,  1517,   865,  1171,  1514,  1172,  1175,  1176,
    1377,  1598,  1515,   836,   837,  1154,  1155,  1159,   838,  1156,
    1509,   297,   484,   345,   344,   346,   352,   335,   134,   135,
     523,   502,   903,   904,   905,   906,  1199,  1401,  1201,  1202,
    1203,  1204,  1402,   901,  1644,  1645,  1667,   538,  1531,  1206,
    1207,  1403,  1604,   136,   936,   137,  1222,  1168,  1693,  1507,
    1704,  1597,  1707,   927,   970,   138,  1382,   928,   971,  1216,
    1217,   940,   937,   982,   539,   540,  1220,  1416,   939,  1609,
    1536,  1610,  1538,   139,   946,   140,   947,  1374,  1591,  1647,
     972,   929,   141,  1488,  1576,   983,   930,   948,  1223,  1224,
    1225,   949,  1091,   963,   964,  1235,   142,   950,   181,  1654,
    1699,  1421,  1653,   973,   144,  1063,  1559,  1239,  1240,  1423,
     556,   557,  1540,  1611,  1541,  1612,   956,   957,  1226,  1227,
    1228,   958,   959,  1229,   145,  1232,  1422,   974,  1104,   777,
     182,   213,   215,   217,   298,   671,  1478,  1068,  1069,  1324,
    1570,  1070,  1473,  1623,  1468,  1622,  1476,  1624,  1321,  1569,
    1319,  1567,  1565,  1564,  1563,  1561,  1560,   886,   198,   657,
     184,   582,  1426,  1425,   445,   149,   161,   987,   388,  1142,
    1143,  1144,   150,   680,   151,   156,   990,   152,   585,   157,
     159,   744,   426,   841,  1139,  1362,  1141,  1363,   808,   745,
     750,   751,   746,   748,   747,   742,  1010,   743,  1011,  1267,
    1268,  1269,  1430,  1270,  1271,  1273,  1431,  1274,  1272,  1275,
    1265,  1266,  1547,  1243,  1244,  1245,  1246,  1247,  1248,  1249,
    1250,  1251,  1282,  1252,  1253,  1254,  1255,  1256,  1257,  1258,
    1259,  1427,  1260,  1280,  1263,  1264,  1434,  1429,  1433,  1277,
    1432,  1406,  1615,  1372,  1339,  1625,  1626,  1627,  1628,  1098,
     768,   769,  1491,  1571,   771,  1346,   807,   375,   686,   247,
    1333,  1334,  1485,  1486,   991,   495,   627,   312,  1340,  1341,
    1093,   316,   759,   761,  1094,   317,   318,   765,   319,   763,
     320,   764,   321,   153,  1029
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     100,   546,   210,   449,   296,   158,   197,    71,   172,   188,
    1092,   511,   194,   333,   666,  1384,   667,   218,   668,  1058,
     230,   174,   547,  1295,   520,   481,   486,  1306,  1170,   381,
     209,   507,   219,   373,   172,   840,   525,   304,   562,   573,
     390,   306,   353,   172,   551,   524,     1,  1230,   222,   172,
     565,   577,  1234,   175,   572,   661,   234,   527,    21,   564,
      22,   313,   242,   467,  1231,   662,   100,  1233,   534,   100,
     915,   567,   578,   100,   449,     1,   526,   225,     1,  -911,
     880,  1682,   551,  -911,     7,   943,   376,   382,     1,   661,
     566,   857,   536,     1,   330,   238,     1,   521,  -911,   662,
     633,  1695,    21,   916,    22,  1354,   239,   210,  1355,  1356,
     422,   563,   575,  1300,  1534,  1535,     1,   660,   172,   172,
     172,     6,   489,   920,   417,   490,   470,   422,   580,    21,
     569,    22,   482,   100,   172,   537,    21,   810,    22,    21,
     558,    22,   423,   636,     1,     2,   172,   100,   571,     6,
       7,    21,   491,    22,   855,   240,  1218,   631,   241,   423,
     191,   510,   921,   630,   186,   487,  1191,  1367,   496,   507,
     944,  -911,   545,   296,  1049,  1512,   643,   661,   172,   531,
     172,   233,   642,   172,   172,   650,    21,   662,    22,   756,
     812,   649,   561,   210,   301,     1,     2,   656,  1297,   230,
       6,     7,   811,   945,   381,   581,   534,   507,  1459,     1,
     941,   629,  1298,   988,   511,   186,   222,   146,     1,  1219,
     370,   659,    62,   639,     7,   233,   554,    21,   561,    22,
     536,  1026,   496,   100,  1584,  1585,   424,    51,   172,   172,
     172,   172,     1,   371,   543,   197,  1384,  1384,   507,   172,
     690,   630,   233,   498,   372,   813,   499,   500,  1436,    21,
    1586,    22,   382,  1299,   870,   374,   417,  1443,   501,   754,
     384,   385,   386,   383,   233,   507,   354,   384,   385,   386,
     384,   385,   386,   146,   329,   508,   146,    21,    51,    22,
     146,   509,   192,   465,   172,  1383,  1552,   172,   521,   248,
     563,   575,  -811,  1343,   384,   385,   386,     1,   497,   233,
    1090,   304,   508,     7,   513,  1388,   400,   498,   934,  1389,
     499,   500,  1046,   172,  1419,   406,     1,   755,  -543,   512,
       1,   802,   501,   353,   172,     6,   172,   172,   569,   754,
    1420,   313,   661,   192,   636,   249,   661,  1381,   778,   513,
     233,   935,   662,    21,   172,    22,   662,  1300,   469,  1300,
     781,   782,     1,   636,   146,   788,   790,   822,  1300,   530,
     172,   172,   172,     1,     2,   739,   348,   349,     6,   740,
     455,   561,   233,  1047,   798,  1584,  1585,   546,   809,   481,
     756,   572,   185,   186,  1286,  1464,   456,   755,  1613,   636,
     100,   661,   511,   783,   661,     1,   776,  1317,   547,   756,
       6,   662,  1297,   520,   662,   330,   800,   330,   831,   562,
     573,   830,  1690,   172,     1,   525,  1298,   546,    21,     6,
      22,   565,   577,  1557,   524,   784,    62,   418,   546,   419,
     564,   856,   172,   172,   511,   756,   527,    21,   547,    22,
     146,  1666,   567,   578,  1342,   464,   511,  -545,   636,   547,
     507,   350,   503,   210,   960,   526,    51,   520,   210,   551,
     562,   566,     1,   642,  1579,  1580,  1581,  1445,     7,   980,
     172,   333,   985,   172,   876,   172,   521,  1297,   860,  1692,
     636,   887,   563,   575,  -508,  -508,   892,   534,  1300,   496,
     981,  1298,  1701,   535,   736,  1300,  1297,    21,   210,    22,
     636,    62,   785,   172,  -508,   172,   922,   172,     1,   172,
    1298,   536,   100,   584,     7,   330,  1619,   636,   100,   571,
      62,  -508,   952,   953,   954,   628,   756,   757,   633,   394,
     521,     1,     2,   563,   786,   884,     6,     7,   422,   885,
      10,    11,  1458,   462,   200,   164,   924,   201,   545,   188,
       1,   186,    19,    20,   537,     6,   961,   354,   165,    24,
     942,  1548,   354,   756,  1081,   497,   571,   648,    26,   571,
     423,   989,  -248,    21,   498,    22,     1,   499,   500,  1469,
       1,     6,  -248,  -248,   661,     6,  1013,  1014,   545,   501,
    1470,  1471,   955,  -248,   662,   794,   799,   803,   849,    21,
     633,    22,  1031,    21,   496,    22,     1,   146,   662,  1300,
     422,     6,  1034,   650,   561,     1,     2,  1505,   642,   642,
       6,  1035,  1157,    50,    51,     1,     2,     1,  -248,    21,
       6,    22,  1297,   789,  1158,   186,  1036,    77,   172,  -921,
    1048,   636,   423,   507,  1296,   186,  1298,   831,   640,  -921,
    -921,  1169,   211,   172,   172,   211,    62,  1211,  1297,   441,
    1237,   172,  1297,  1158,  -921,    10,    11,  1238,   859,  1158,
     636,  1300,  1298,   496,   655,   633,  1298,   172,  1322,   554,
     543,   664,    62,  1465,    24,   422,    62,   756,  1331,   498,
    1323,   636,   499,   500,   220,  1466,  1177,  1551,  1178,   860,
     669,   442,  1298,    77,   501,   329,    77,   676,    51,   119,
      77,  -921,    62,   663,  1508,   443,   756,   423,    51,   687,
    1511,   496,   714,  1621,  1214,  1215,   642,  1657,   563,  -921,
    -921,  -921,  -921,  -921,  -921,  -921,  -921,  1366,  -507,    21,
    1162,    22,  1238,     1,     2,   728,   642,  1127,     6,   497,
    -507,  -507,  -507,  -507,   210,  -507,   661,   670,   498,   633,
     507,   499,   500,   186,   172,   172,   662,   661,  -268,   422,
     653,  1112,   730,   501,   636,   119,   462,   662,   119,   729,
     636,   463,   119,  1549,   430,     1,     2,   732,   296,   465,
       6,   466,   636,   467,   431,     1,     2,   543,   432,   462,
       6,   423,  1055,   544,   894,   186,   498,  1074,   447,   499,
     500,   433,   562,   172,  -507,   186,  -507,  1153,   172,   647,
     756,   501,   223,   172,   985,  1075,   473,  1442,   483,   483,
     462,   546,  1053,  -921,  1054,  1128,    51,   637,   756,   660,
     660,   203,   749,  -921,  -921,  1167,     1,     2,   172,   422,
     422,     6,   547,  1293,   469,  1294,   470,   483,  -921,   633,
    1179,   636,   233,     1,     2,   520,   186,   573,     6,   422,
      77,     1,     2,   760,  1192,  1193,     6,   980,    51,   577,
     660,   423,   423,   186,   143,   563,   762,  -921,    51,   859,
     422,   186,   203,   860,  1076,  -231,  1428,  -921,  -921,   102,
     211,   423,   739,   348,   349,  -921,   740,   756,  1213,   443,
     779,   766,  -921,   830,   642,     1,     2,   828,   787,  1040,
       6,   571,   423,  -921,  -921,  -921,  -921,  -921,  -921,  -921,
    -921,   814,   792,  -266,   228,   186,   551,  1641,   521,    51,
     575,  1177,   119,  1310,  -266,  -266,   805,  1649,  -213,  1404,
     143,  1405,   923,   143,   815,   816,    51,   143,  -213,   636,
     823,  1177,   422,  1489,    51,   102,     1,     2,   102,   902,
     932,     6,   102,    21,   571,    22,   571,  -921,  -921,  -921,
    -921,  -921,  -921,  -921,  -921,   465,   186,   466,  1194,   467,
    -213,  1262,  1077,  1669,   423,   752,  1672,   753,  1177,   127,
    1593,     1,     2,   975,   490,   756,     6,   179,    51,  1279,
      10,    11,  1212,   422,   200,   164,  1687,   201,   384,   385,
     386,   186,    19,    20,  1283,  1177,  1287,  1595,   202,    24,
     914,   568,   642,  1177,  1698,  1617,  1056,    77,    26,  1036,
    1177,  1303,  1665,     1,     2,   423,   172,   203,     6,  1177,
     469,  1670,  1130,   100,  1313,  1315,  1318,     1,     2,    51,
    1312,  1087,     6,   186,  1177,   127,  1685,   568,   127,  1314,
    1316,  1088,   127,  -641,   220,   802,  1400,   186,   802,   802,
    1352,  1353,  1177,   859,  1688,  1177,   422,  1696,    95,   172,
    1358,  1359,   204,    50,    51,    52,   170,   187,   633,  1090,
     193,   205,   212,   214,   216,  1099,   221,   224,   422,   119,
    1533,   229,  1123,   100,   100,  1133,  1408,   143,   423,   661,
     422,  1344,   170,   100,   100,  1125,     1,     2,  1129,   662,
    1529,     6,   102,  1135,   860,   633,    51,   170,  1283,  1140,
     423,  1368,   952,   953,   954,   422,   186,   170,   172,  1177,
      51,  1703,   423,  1365,    95,  1182,  1151,    95,  1311,  1160,
    1462,    95,  1186,     1,     2,  1183,  1189,   172,     6,  1184,
       1,     2,  1387,  1390,  1391,     6,  1185,   423,  1200,  1210,
     955,  1396,   741,   186,  1283,   170,  1236,   465,  1241,   466,
     186,   467,   483,   468,   483,  1237,  1242,  1284,  1276,  1399,
     636,  1320,   172,   430,  1410,  1411,   476,   170,   170,  1288,
    1289,  1327,   860,   431,   465,   933,   466,   432,   467,    51,
     568,   518,   170,   430,  1328,  1329,  1413,  1415,   358,   359,
     433,   430,   127,   431,   170,   518,   570,   432,  1330,  1361,
    1337,   431,  1338,  1606,  1173,   432,   473,   549,  1174,  1369,
     433,   193,   469,   632,   470,  1290,    51,   637,   433,   170,
    1375,  1376,  1397,    51,   638,  1398,   170,   554,   170,  1438,
     146,   170,   170,   646,   221,  1454,  1467,  1472,  1475,   469,
     170,   470,  1504,   851,   143,  1303,  1494,  1303,   193,  1495,
     229,   170,   205,   852,  1496,  1510,  1303,   853,  1525,   102,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     854,  1528,   633,   172,  1537,  1546,  1539,  1590,  1592,  1614,
    1594,    95,   422,   907,   859,  1605,   170,   170,   170,   170,
     146,   146,   908,   172,  1602,   909,   910,  1629,  1630,   193,
     146,   146,  1631,  1640,   507,  1648,  1651,   911,   430,  1634,
     430,  1650,  1664,   537,   423,  1668,   642,  1506,   431,   172,
     431,  1671,   432,  1673,   432,   172,  1513,  1684,  -825,  -825,
    1588,  -825,  -825,  1689,  -825,   433,   685,   433,  1521,  1522,
     170,   231,   170,  1447,   560,   170,     1,  1043,  1107,  1108,
    1109,   876,  1371,  1221,  1545,  1424,     0,  1479,  1283,   127,
       0,  1110,   859,     0,   860,     0,     0,     0,     0,     0,
     860,   100,   568,  1532,     0,     0,     0,     0,  1544,     0,
       0,     0,   170,     0,   170,   170,  1303,     0,   172,     0,
       0,     0,     0,  1303,     0,     0,     0,     0,   170,     0,
       0,     0,   170,     0,   802,   802,   802,     0,     0,     0,
       0,     0,     0,     0,  1582,     0,     0,   172,     0,     0,
       0,     0,   172,   568,     0,     0,  1646,     0,     0,     0,
       0,     0,     0,   860,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,   100,    95,     0,
       6,     7,     0,     0,    10,    11,     0,     0,   200,   164,
       0,   201,  1596,     0,     0,   186,    19,    20,     0,   829,
       0,  1578,   165,    24,     0,     0,   842,     0,     0,  1283,
       0,     0,    26,     0,     0,  1589,     0,     0,     0,     0,
       0,   170,  1045,     0,  1603,     0,  1646,     0,  1616,     0,
       0,     0,     0,     0,     0,     0,     0,  1303,     0,     0,
       0,     0,     0,     0,     0,     0,  1646,     0,     0,     0,
       0,     0,   205,     0,     0,     0,     0,   205,   170,     0,
       0,   170,     0,   170,     0,     0,   638,    50,    51,     0,
       0,     0,   172,     0,     0,     0,  1659,  1660,  1661,     0,
       0,     0,   172,     0,   859,     0,  1283,     0,     0,     0,
     859,     0,     0,   170,     0,   170,     0,   205,     0,  1303,
     518,  1652,     0,     0,     0,  1643,   518,   570,     0,   100,
     100,   100,     0,     0,   100,   938,     0,   860,   146,     0,
       0,  1663,     0,     0,     0,     0,     0,   860,   172,     0,
       0,   172,     0,     0,   100,     0,   965,   187,     0,     0,
       0,  1674,   100,     0,     0,     0,     0,     0,   568,  1679,
       0,   172,     0,   859,   570,     0,     0,   570,     0,     0,
    1067,     0,     0,     0,     0,     0,     0,     0,     0,   172,
       0,     0,     0,   860,     0,  1681,   860,  1683,  1301,     0,
       0,     0,     0,     0,     0,   205,   205,     0,     0,     0,
      77,     0,     0,     0,   146,  1694,   860,     0,     0,     0,
       0,   205,     0,  1700,     0,     0,     0,     0,     0,     0,
       0,  1037,  1705,     0,   860,     0,     0,     0,     0,     0,
       0,  1039,     0,     0,     0,     0,   170,     0,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,   829,   170,
       0,   170,   170,     0,     0,     0,     0,  1062,     0,   170,
      77,    77,     0,   586,     0,     0,     0,     0,     0,     0,
      77,    77,   119,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,   120,     0,   619,   758,   620,
    1102,   621,     0,   178,     0,   568,     0,   859,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   859,     0,     0,
       0,   147,   119,   119,     0,     0,   146,   146,   146,   183,
       0,   146,   119,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   178,     0,     0,     0,     0,     0,
       0,   146,   170,   205,     0,   623,  1105,     0,     0,   146,
       0,   120,     0,   859,   120,   624,   859,     0,   120,     0,
     336,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     355,     0,     0,     0,     0,     0,   859,   147,     0,     0,
     147,     0,     0,     0,   147,     0,     0,     0,     0,     0,
       0,   170,     0,     0,   859,     0,   170,     0,     0,     0,
       0,   170,     0,    97,   120,   120,     0,     0,     0,     0,
       0,   171,  1301,     0,  1301,     0,     0,   170,     0,   178,
       0,     0,     0,  1301,     0,     0,   170,   143,     0,   638,
     183,   183,   178,   120,     0,     0,     0,   292,     0,     0,
       0,     0,   102,     0,   528,   183,    97,     0,     0,   324,
       0,     0,   171,     0,  1195,     0,     0,     0,   147,   579,
       0,     0,   351,   178,     0,     0,     0,     0,   178,    97,
       0,     0,    97,     0,     0,     0,    97,     0,     0,     0,
       0,     0,  1205,     0,     0,     0,     0,   143,   143,   183,
       0,  1037,     0,     0,   183,     0,     0,   143,   143,   570,
     434,     0,   102,   102,     0,     0,     0,     0,     0,   938,
       0,     0,   102,   102,     0,     0,     0,     0,   120,     0,
       0,     0,   171,   171,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   171,   171,    77,     0,
       0,     0,   127,  1037,   147,     0,     0,     0,     0,   555,
     171,   171,   570,  1301,   570,     0,     0,     1,     2,     0,
    1301,     0,     6,     0,     0,     0,    10,    11,     0,     0,
     200,   164,     0,   201,   434,     0,     0,   186,    19,    20,
    1261,   171,     0,   171,   165,    24,   171,   171,     0,     0,
       0,     0,     0,     0,    26,   651,     0,     0,   205,     0,
       0,     0,   127,   127,     0,     0,   658,     0,     0,     0,
     119,     0,   127,   127,    77,   170,     0,     0,     0,     0,
       0,   178,   170,     0,   170,     0,     0,     0,     0,     0,
       0,    95,   212,   224,     0,     0,    97,     0,     0,     0,
       0,   171,   171,   171,   171,   774,     0,   336,   774,    50,
      51,     0,    97,     0,     0,   178,   178,   178,     0,     0,
       0,   355,   235,     0,     0,     0,   355,   170,   235,     0,
       0,     0,     0,     0,  1301,     0,     0,     0,     0,     0,
       0,   183,   183,   183,     0,   120,   119,     0,     0,     0,
       0,    95,    95,     0,     0,   434,     0,   171,     0,     0,
     171,    95,    95,     0,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,     0,   178,     0,
     235,     0,     0,     0,     0,     0,  1301,   171,     0,   171,
     171,     0,     0,     0,     0,   170,    77,    77,    77,     0,
       0,    77,     0,   351,   183,     0,     0,   555,   235,     0,
       0,     0,     0,     0,     0,   178,     0,   235,   120,     0,
     120,    77,     0,    97,    97,    97,     0,     0,   235,    77,
     170,  1409,     0,     0,     0,   143,     0,     0,     0,     0,
       0,   183,     0,     0,   183,     0,   183,     0,   170,   170,
     102,     0,  1067,    97,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   119,
     119,     0,     0,   119,     0,     0,   833,     0,   774,     0,
       0,   843,     0,   528,     0,     0,     0,     0,     0,   528,
     931,     0,     0,   119,     0,   833,   171,     0,     0,     0,
       0,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,   170,     0,   178,     0,     0,     0,     0,   875,
       0,     0,   235,     0,     0,     0,   102,     0,     0,     0,
       0,     0,     0,   171,     0,     0,   171,   931,   171,     0,
     579,   170,     0,     0,     0,     0,     0,     0,     0,     0,
     127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   170,     0,     0,     0,     0,   833,     0,   171,     0,
     171,     0,     0,     0,     0,   171,     0,     0,     0,     0,
       0,   171,   171,     0,     0,     0,     0,   170,     0,     0,
       0,     0,     0,   170,     0,     0,     0,     0,     0,   178,
       0,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1037,     0,
       0,     0,  1530,     0,     0,   183,   127,   293,     0,   171,
       0,     0,   171,     0,     0,     0,   310,   170,   170,    95,
       0,     0,     0,   143,   143,   143,     0,     0,   143,   309,
     309,     0,     0,     0,     0,     0,   170,     0,   102,   102,
     102,     0,     0,   102,     0,     0,     0,     0,   143,     0,
       0,     0,     0,     0,   309,   379,   143,     0,     0,     0,
       0,     0,     0,   102,     0,   170,     0,     0,     0,     0,
     170,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   171,     0,     0,     0,     0,  1050,     0,     0,     0,
       0,     0,   176,   488,   843,    95,   171,   171,     0,     0,
       0,     0,     0,     0,   171,     0,   519,   176,     0,     0,
     858,     0,     0,     0,     0,   774,     0,     0,     0,     0,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1037,     0,     0,     0,     0,     0,     0,   127,   127,
     127,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,   488,     0,   641,     0,     0,   176,   644,     0,     0,
       0,     0,     0,   127,     0,     0,     0,     0,     0,     0,
       0,   127,     0,   178,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     170,     0,     0,     0,   235,     0,     0,     0,     0,   183,
     170,     0,   133,     0,     0,     0,   235,   171,     0,     0,
     180,   681,   682,   683,   684,     0,     0,     0,     0,     0,
       0,     0,   688,   962,     0,     0,     0,    95,    95,    95,
     309,     0,    95,     0,   235,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,     0,     0,   170,
       0,   334,    95,     0,     0,     0,   171,     0,     0,     0,
      95,   292,     0,     0,     0,     0,   434,   737,   133,   170,
     641,   133,   931,     0,     0,   133,     0,  -203,  -203,  -203,
       0,     0,   843,     0,     0,     0,     0,   170,  -203,  -203,
    -203,   171,     0,     0,     0,   309,   310,     0,     0,     0,
    -203,  -203,  -203,  -203,     0,     0,     0,   519,     0,   309,
     775,     0,   309,  -203,     0,     0,     0,     0,     0,     0,
       0,   180,     0,     0,     0,   931,     0,   931,     0,     0,
       0,   858,     0,     0,     0,   522,     0,     0,     0,     0,
       0,     0,     0,   176,   176,   176,     0,     0,     0,   522,
     576,     0,     0,     0,     0,     0,     0,   797,  -203,     0,
       0,  -203,  -203,     0,   171,   309,  -203,     0,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,     0,  -203,   120,     0,
       0,     0,  -203,     0,     0,     0,     0,     0,  -203,  -203,
    -203,  -203,     0,     0,     0,     0,   834,     0,     0,     0,
       0,     0,     0,     0,   147,     0,     0,     0,     0,     0,
     309,     0,     0,     0,   178,   834,   861,   171,     0,   171,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,     0,     0,   120,   120,
     183,     0,     0,     0,     0,     0,     0,     0,   120,   120,
       0,     0,   309,   176,     0,   309,   176,     0,   176,     0,
       0,     0,     0,     0,   147,   147,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   147,     0,     0,     0,     0,
    1292,     0,     0,     0,     0,     0,   834,  1307,   293,   171,
     775,     0,   178,     0,     0,   519,    97,     0,   309,     0,
       0,   775,   775,     0,     0,     0,  -231,  -231,     0,     0,
       0,  -231,  -231,     0,     0,  -231,  -231,     0,   183,  -231,
    -231,     0,  -231,     0,     0,   858,  -231,  -231,  -231,     0,
       0,     0,   171,   421,  -231,     0,   334,     0,   334,   334,
       0,     0,     0,   422,     0,     0,     0,     0,     0,   519,
       0,     0,  -231,     0,     0,     0,    97,    97,     0,     0,
       0,     0,     0,     0,     0,     0,    97,    97,     0,  -231,
       0,     0,     0,   180,     0,   423,     0,     0,     0,  -231,
       0,     0,     0,  -231,     0,     0,     0,     0,     0,  -231,
       0,   833,     0,     0,     0,     0,  -231,  -231,  -231,  -231,
    -231,     0,   133,     0,     0,     0,   309,     0,     0,     0,
     171,     0,     0,     1,     2,     0,     0,     0,     6,     0,
       0,  1042,    10,    11,     0,     0,   200,   164,     0,   347,
     348,   349,     0,    18,    19,    20,  1057,   861,     0,     0,
     165,    24,     0,     0,  1066,   171,     0,     0,     0,     0,
      26,     0,   424,     0,     0,     0,     0,     0,     0,     0,
    1079,     0,     0,  1417,  1418,     0,     1,     2,     0,     0,
       0,     6,     7,   148,     0,    10,    11,     0,     0,   200,
     164,     0,   201,     0,   178,   199,   186,    19,    20,     0,
     178,     0,     0,   202,    24,     0,     0,     0,     0,     0,
       0,     0,     0,   472,     0,    50,    51,     0,     0,     0,
     183,     0,   203,     0,     0,   350,   183,     0,  1302,   334,
       0,     0,   337,     0,   522,     0,     0,  1444,     0,     0,
     522,   576,     0,     0,     0,     0,   120,     0,     0,   148,
       0,     0,   148,     0,     0,     0,   148,   775,     0,   473,
       0,     0,     0,   178,     0,     0,   171,   474,    50,    51,
     475,     0,   147,     0,     0,     0,   858,   235,     0,     0,
       0,     0,     0,     0,     0,     0,   171,     0,   576,   183,
       0,   984,     0,   797,     0,     0,     0,     0,     0,     0,
       0,   479,   485,   485,     0,     0,  1148,     0,     0,     0,
       0,  1149,   171,     0,     0,     0,   529,     0,   171,     0,
       0,     0,   120,     0,     0,     0,     0,     0,     0,   199,
     529,   148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   861,     0,     0,     0,     0,   199,     0,   147,     0,
       0,     0,     0,     0,   858,     0,     0,     0,     0,     0,
       0,     0,  1542,  1543,    97,   199,     0,     0,     0,     0,
       0,     0,     0,     0,   199,     0,     0,     0,     0,     0,
       0,   171,     0,     0,     0,     1,     2,     0,     0,     0,
       6,     7,     0,     0,    10,    11,     0,     0,   200,   164,
       0,   201,     0,     0,     0,   186,    19,    20,     0,     0,
     171,     0,   428,    24,   775,   171,   148,   178,     0,     0,
       0,     0,   429,     0,     0,     0,     0,   178,     0,     0,
     295,     0,     0,     0,   199,     0,     0,     0,     0,   295,
      97,     0,     0,   183,     0,     0,     0,     0,   430,     0,
       0,     0,     0,   183,   120,   120,   120,     0,   431,   120,
       0,     0,   432,     0,     0,     0,     0,   519,     0,   775,
       0,     0,  1302,   178,  1302,   433,   178,    50,    51,   120,
     147,   147,   147,  1302,     0,   147,   334,   120,     0,     0,
       0,     0,     0,     0,     0,     0,   178,     0,     0,   183,
       0,     0,   183,     0,     0,   147,     0,     0,     0,     0,
       0,     0,     0,   147,   178,     0,     0,   337,     0,   337,
     337,     0,   183,     0,     0,     0,     0,     0,     0,   295,
       0,     0,     0,     0,     0,   171,     0,   199,     0,  1308,
     183,     0,     0,     0,   574,   171,   858,     0,     0,     0,
       0,     0,   858,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    97,    97,     0,   295,    97,     0,     0,
     645,     0,   861,   148,     0,     0,     0,     0,     0,     0,
       0,   171,     0,     0,   171,     0,     0,    97,     0,     0,
       0,   962,     0,     0,     0,    97,     0,     0,     0,     0,
       0,     0,     0,  1302,   171,   858,     0,     0,     0,     0,
    1302,   797,     0,     0,   797,   797,     0,     0,     0,     0,
       0,     0,   171,     0,   295,   295,   295,   295,     0,     0,
       0,   834,     0,   984,     0,   295,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   199,     0,     0,     0,
     861,     0,     0,     0,     1,     2,   485,   235,   485,     6,
       7,     0,     0,    10,    11,     0,     0,   200,   164,     0,
     201,   235,     0,     0,   186,    19,    20,     0,     0,     0,
     295,   202,    24,   295,     0,  1149,   984,     0,   984,     0,
     337,   472,   479,     0,     0,   529,     0,     0,     0,     0,
     203,   529,   529,     0,   309,   309,     0,     0,     0,   295,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     295,     0,     0,   645,  1302,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   924,     0,     0,
       0,     0,     0,     0,     0,   474,    50,    51,    52,   529,
       0,     0,   986,     0,     0,     0,     0,     0,     0,   858,
       0,   235,     0,     0,     0,   133,     0,     0,     0,   858,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -205,  -205,  -205,     0,     0,  1302,     0,     0,     0,
       0,     0,  -205,  -205,  -205,     0,  1066,     0,     0,     0,
       0,   199,   199,     0,  -205,  -205,  -205,  -205,     0,   295,
       0,     0,     0,     0,     0,   858,  1490,  -205,   858,     0,
       0,     0,     0,     0,     0,   133,   133,     0,   295,   862,
       0,   235,     0,   235,     0,   133,   133,     0,   858,     0,
       0,     0,   861,     0,     0,     0,     0,  1503,   861,     0,
       0,   235,     0,     0,     0,     0,   858,     0,     0,   235,
       0,     0,  -205,     0,     0,  -205,  -205,     0,   235,   309,
    -205,   574,  -205,  -205,  -205,  -205,  -205,  -205,  -205,  -205,
       0,  -205,     0,     0,     0,     0,  -205,     0,     0,     0,
       0,     0,  -205,  -205,  -205,  -205,     0,     0,     0,   295,
       0,   295,     0,   295,     0,     0,     0,     0,   295,   199,
       0,   861,     0,     0,   295,   645,     0,     0,     0,     0,
       0,     0,     1,     2,     0,     0,     0,     6,     0,   199,
       0,    10,    11,     0,     0,   200,   164,     0,   201,     0,
    1562,     0,   186,    19,    20,  1566,     0,   337,   479,   202,
      24,     0,     0,     0,     0,     0,     0,     0,     0,    26,
       0,     0,   295,     0,     0,     0,     0,     0,   203,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     797,   797,   797,     0,     0,     0,     0,  1587,     0,  1503,
       0,     1,     2,     0,     0,     0,     6,     7,   162,   559,
      10,    11,     0,     0,   251,    13,   199,    14,    15,    16,
       0,    18,    19,    20,    50,    51,    52,     0,   165,    24,
       0,     0,     0,   166,     0,     0,     1,     2,    26,     0,
       0,     6,     7,     0,   295,    10,    11,   515,     0,   200,
     164,     0,   201,     0,     0,     0,   186,    19,    20,   295,
     862,     0,     0,   202,    24,     0,     0,     0,     0,     0,
       0,     0,     0,   472,     0,   861,     0,     0,     0,     0,
     516,     0,   203,   295,  1587,   861,     0,     0,     0,     0,
       0,    48,   517,    50,    51,     0,     0,     0,    54,    55,
      56,    57,    58,    59,    60,    61,     0,   199,     0,     0,
       0,     0,     0,     0,   986,     0,     0,     0,     0,   756,
       0,     0,     0,     0,     0,     0,     0,   474,    50,    51,
      52,   861,     0,   133,   861,     0,     0,     0,     0,     0,
       0,   246,     0,     0,   299,   300,     0,   302,   303,   305,
     307,   308,   311,   311,   861,   325,   327,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   986,     0,   986,
     295,     0,   861,     0,     0,     0,     0,   311,   380,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     2,     3,     4,     5,     6,     0,     0,     0,    10,
      11,     0,     0,   200,   164,     0,   201,     0,     0,   133,
     186,    19,    20,    21,     0,    22,     0,    23,    24,   295,
       0,     0,     0,     0,   295,   199,     0,    26,    27,    28,
      29,    30,     0,     0,    32,    33,   203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,     0,     0,     0,
       0,     0,     0,     0,   862,    35,    36,     0,     0,     0,
       0,    37,    38,    39,     0,     0,     0,    40,     0,   243,
      42,     0,     0,    43,     0,    44,     0,     0,    46,    47,
       0,     0,    50,    51,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   148,   148,     0,     0,
       0,     0,     0,    68,     0,     0,   148,   148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   295,     0,     0,
       0,     0,     0,     0,   675,     0,   244,   377,     0,     0,
       0,   133,   133,   133,     0,     0,   133,     0,     0,     0,
       0,     0,   307,   311,     0,     0,     0,     0,   689,     0,
       0,     0,     0,     0,     0,     0,   133,     0,     0,     0,
       0,     0,     0,   586,   133,     0,     0,     0,     0,     0,
     295,     0,   645,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,   311,   620,
    1072,   621,     0,   305,     0,     0,     0,     0,     0,     0,
       0,     0,   767,     0,     0,   311,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   295,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   623,     0,     0,     0,   795,
     801,   804,     0,   806,     0,   624,     0,     0,   311,     0,
       0,     1,     2,     0,     0,   862,     6,     7,   162,     0,
      10,    11,     0,   820,   251,    13,     0,    14,    15,    16,
       0,    18,    19,    20,     0,     0,     0,     0,   165,    24,
       0,     0,     0,   166,     0,     0,     0,     0,    26,     0,
       0,     0,   839,   311,     0,     0,     0,   515,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   199,
       0,   839,     0,     0,   295,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     516,     0,     0,   862,   873,   311,   878,     0,   311,   881,
       0,    48,   517,    50,    51,     0,     0,     0,    54,    55,
      56,    57,    58,   168,    60,    61,     0,     0,     0,     0,
       0,     0,     0,     0,   148,     0,     0,     0,   295,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   311,   839,     0,     0,     0,     0,     0,     0,   586,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   587,
     588,   589,   590,   591,   592,   593,   594,   595,   596,   597,
     598,   599,   600,   601,   602,   603,   604,   605,   606,   607,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     618,     0,     0,   619,   758,   620,     0,   621,     0,   622,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   992,   993,   994,   995,
     996,   997,   998,   999,  1000,  1001,  1002,  1003,  1004,  1005,
    1006,  1007,  1008,  1009,     0,     0,     0,     0,  1015,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,   311,
    1028,   623,     0,  1032,  1033,     0,     0,     0,     0,   295,
       0,   624,     0,     0,     0,     0,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,     0,   862,  -219,  -219,  -219,  -219,
       0,   862,     0,  -219,  -219,  -219,     0,  -219,     1,     2,
    -219,  -219,   394,     6,     0,  1073,   395,    10,    11,     0,
       0,   200,   164,     0,   201,     0,  1080,     0,   186,    19,
      20,     0,     0,     0,     0,   202,    24,     0,     0,     0,
       0,     0,   148,   148,   148,    26,     0,   148,     0,     0,
       0,     0,     0,     0,   203,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   862,     0,     0,   148,  -219,     0,
       0,     0,     0,     0,     0,   148,     0,     0,  -219,     0,
       0,     0,     0,     0,     0,     0,     0,  1012,     0,     0,
       0,     0,     0,   295,     0,     0,  1095,  1096,   295,  1097,
      50,    51,    52,     0,     0,     0,     0,     0,     0,  1103,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1126,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1097,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,     0,     0,    12,    13,     0,    14,    15,    16,
      17,    18,    19,    20,    21,     0,    22,     0,    23,    24,
       0,     0,     0,    25,     0,     0,     0,     0,    26,    27,
      28,    29,    30,    31,     0,    32,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   862,     0,
       0,     0,     0,     0,     0,     0,    35,    36,   862,     0,
       0,     0,    37,    38,    39,     0,     0,     0,    40,     0,
      41,    42,     0,     0,    43,     0,    44,     0,    45,    46,
      47,    48,    49,    50,    51,    52,    53,     0,    54,    55,
      56,    57,    58,    59,    60,    61,     0,    62,     0,     0,
       0,     0,    63,     0,   862,     0,     0,   862,    64,    65,
      66,    67,     0,     0,    68,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     0,     0,   862,    10,    11,
       0,     0,   200,   164,     0,   201,     0,    69,   377,   186,
      19,    20,    21,     0,    22,   862,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    27,    28,    29,
      30,     0,     0,    32,    33,   203,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,     0,     0,
      37,    38,    39,     0,     0,     0,    40,     0,   243,    42,
       0,     0,    43,     0,    44,     0,     0,    46,    47,     0,
       0,    50,    51,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     2,     3,     4,
       5,     6,    68,     0,     0,    10,    11,     0,     0,   200,
     164,     0,   201,     0,     0,     0,   186,    19,    20,     0,
       0,     0,     0,    23,    24,   244,  1414,     0,     0,     0,
       0,  1345,     0,    26,    27,    28,    29,    30,     0,     0,
      32,    33,   203,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   801,     0,     0,   801,   801,  1357,
       0,    35,    36,     0,  1360,     0,     0,    37,    38,    39,
       0,     0,     0,    40,     0,   243,    42,     0,     0,    43,
       0,    44,     0,     0,    46,    47,     0,   839,    50,    51,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1378,  1380,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    68,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   586,
       0,     0,   244,  1138,     0,     0,     0,   311,   311,   587,
     588,   589,   590,   591,   592,   593,   594,   595,   596,   597,
     598,   599,   600,   601,   602,   603,   604,   605,   606,   607,
     608,   609,   610,   611,   612,   613,   614,   615,   616,   617,
     618,     0,     0,   619,     0,   620,     0,   621,     0,   622,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,     0,
    1435,    12,    13,     0,    14,    15,    16,    17,    18,    19,
      20,    21,     0,    22,     0,    23,    24,     0,     0,     0,
      25,     0,     0,     0,     0,    26,    27,    28,    29,    30,
      31,   623,    32,    33,    34,     0,  1474,     0,     0,  1477,
       0,   624,     0,     0,     0,  1480,  1481,  1482,  1483,  1484,
       0,     0,     0,    35,    36,     0,     0,     0,     0,    37,
      38,    39,     0,     0,     0,    40,     0,    41,    42,     0,
       0,    43,     0,    44,     0,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     0,    54,    55,    56,    57,    58,
      59,    60,    61,     0,    62,     0,     0,     0,     0,    63,
       0,     0,   311,     0,     0,    64,    65,    66,    67,     0,
       0,    68,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     7,   162,     0,    10,    11,
       0,     0,   251,   164,     0,    14,    15,    16,     0,    18,
      19,    20,    21,     0,    22,     0,    23,    24,     0,     0,
       0,   166,     0,  1555,     0,     0,    26,    27,    28,    29,
      30,     0,     0,    32,    33,   203,     0,     0,     0,     0,
       0,     0,     0,     0,  1568,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,     0,     0,
      37,    38,    39,   801,   801,   801,    40,     0,   243,    42,
       0,     0,    43,     0,    44,     0,     0,    46,    47,    48,
     167,    50,    51,    52,     0,     0,    54,    55,    56,    57,
      58,   168,    60,    61,     0,     0,     0,     0,     0,     0,
       1,     2,     3,     4,     5,     6,     7,   162,     0,    10,
      11,     0,    68,   251,   164,     0,    14,    15,    16,     0,
      18,    19,    20,    21,     0,    22,     0,    23,    24,     0,
       0,     0,   166,     0,     0,   244,     0,    26,    27,    28,
      29,    30,     0,     0,    32,    33,   203,     0,     0,     0,
       0,     0,     0,  1633,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,     0,     0,     0,
       0,    37,    38,    39,     0,     0,     0,    40,     0,   243,
      42,     0,     0,    43,     0,    44,     0,     0,    46,    47,
      48,   480,    50,    51,    52,     0,     0,    54,    55,    56,
      57,    58,   168,    60,    61,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     7,   162,     0,
      10,    11,     0,    68,   251,   164,     0,    14,    15,    16,
       0,    18,    19,    20,     0,     0,     0,     0,    23,    24,
       0,     0,     0,   166,     0,     0,   244,     0,    26,    27,
      28,    29,    30,     0,     0,    32,    33,   203,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,     0,     0,
       0,     0,    37,    38,    39,     0,     0,     0,    40,     0,
     243,    42,     0,     0,    43,     0,    44,     0,     0,    46,
      47,    48,   167,    50,    51,    52,     0,     0,    54,    55,
      56,    57,    58,   168,    60,    61,     0,     0,     0,     0,
       0,     0,     1,     2,     3,     4,     5,     6,     7,   162,
       0,    10,    11,     0,    68,   251,   164,     0,    14,    15,
      16,     0,    18,    19,    20,     0,     0,     0,     0,    23,
      24,     0,     0,     0,   166,     0,     0,   244,     0,    26,
      27,    28,    29,    30,     0,     0,    32,    33,   203,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,     0,
       0,     0,     0,    37,    38,    39,     0,     0,     0,    40,
       0,   243,    42,     0,     0,    43,     0,    44,     0,     0,
      46,    47,    48,   480,    50,    51,    52,     0,     0,    54,
      55,    56,    57,    58,   168,    60,    61,     0,     0,     0,
       0,     0,     0,     1,     2,     3,     4,     5,     6,     0,
       0,     0,    10,    11,     0,    68,   200,   164,     0,   201,
       0,     0,     0,   186,    19,    20,    21,     0,    22,     0,
      23,    24,     0,     0,     0,     0,     0,     0,   244,     0,
      26,    27,    28,    29,    30,     0,     0,    32,    33,   203,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
       0,     0,     0,     0,    37,    38,    39,     0,     0,     0,
     314,     0,   243,    42,   315,     0,    43,     0,    44,   770,
       0,    46,    47,     0,     0,    50,    51,    52,     0,     0,
       1,     2,     3,     4,     5,     6,     0,     0,     0,    10,
      11,     0,     0,   200,   164,     0,   201,     0,     0,     0,
     186,    19,    20,    21,     0,    22,    68,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    27,    28,
      29,    30,     0,     0,    32,    33,   203,     0,     0,   244,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,     0,     0,     0,
       0,    37,    38,    39,     0,     0,     0,   314,     0,   243,
      42,   315,     0,    43,     0,    44,     0,     0,    46,    47,
       0,     0,    50,    51,    52,     0,     0,     1,     2,     3,
       4,     5,     6,     0,     0,     0,    10,    11,     0,     0,
     200,   164,     0,   201,     0,     0,     0,   186,    19,    20,
      21,     0,    22,    68,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,    26,    27,    28,    29,    30,     0,
       0,    32,    33,   203,     0,     0,   244,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,     0,     0,     0,     0,    37,    38,
      39,     0,     0,     0,    40,     0,   243,    42,     0,     0,
      43,   874,    44,     0,     0,    46,    47,     0,     0,    50,
      51,    52,     0,     0,     1,     2,     3,     4,     5,     6,
       0,     0,     0,    10,    11,     0,     0,   200,   164,     0,
     201,     0,     0,     0,   186,    19,    20,    21,     0,    22,
      68,    23,    24,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    27,    28,    29,    30,     0,     0,    32,    33,
     203,     0,     0,   244,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,     0,     0,     0,     0,    37,    38,    39,     0,     0,
       0,    40,     0,   243,    42,     0,     0,    43,  1412,    44,
       0,     0,    46,    47,     0,     0,    50,    51,    52,     0,
       0,     1,     2,     3,     4,     5,     6,     0,     0,     0,
      10,    11,     0,     0,   200,   164,     0,   201,     0,     0,
       0,   186,    19,    20,    21,     0,    22,    68,    23,    24,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    27,
      28,    29,    30,     0,     0,    32,    33,   203,     0,     0,
     244,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,     0,     0,
       0,     0,    37,    38,    39,     0,     0,     0,    40,     0,
     243,    42,     0,     0,    43,     0,    44,     0,     0,    46,
      47,     0,     0,    50,    51,    52,     0,     0,     1,     2,
       3,     4,     5,     6,     0,     0,     0,    10,    11,     0,
       0,   200,   164,     0,   201,     0,     0,     0,   186,    19,
      20,   752,     0,   753,    68,    23,    24,     0,     0,     0,
       0,     0,     0,     0,     0,    26,    27,    28,    29,    30,
       0,     0,    32,    33,   203,     0,     0,   244,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,    36,     0,     0,     0,     0,    37,
      38,    39,     0,     0,     0,    40,     0,   243,    42,     0,
       0,    43,     0,    44,     0,     0,    46,    47,     0,     0,
      50,    51,    52,     0,     0,     1,     2,     3,     4,     5,
       6,     0,     0,     0,    10,    11,     0,     0,   200,   164,
       0,   201,     0,     0,     0,   186,    19,    20,     0,     0,
       0,    68,    23,    24,     0,     0,     0,     0,     0,     0,
       0,     0,    26,    27,    28,    29,    30,     0,     0,    32,
      33,   203,     0,     0,   244,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,     0,     0,     0,     0,    37,    38,    39,     0,
       0,     0,    40,     0,   243,    42,     0,     0,    43,   819,
      44,     0,     0,    46,    47,     0,     0,    50,    51,    52,
       0,     0,     1,     2,     3,     4,     5,     6,     0,     0,
       0,    10,    11,     0,     0,   200,   164,     0,   201,     0,
       0,     0,   186,    19,    20,     0,     0,     0,    68,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      27,    28,    29,    30,     0,     0,    32,    33,   203,     0,
       0,   244,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,     0,
       0,     0,     0,    37,    38,    39,     0,     0,     0,    40,
       0,   243,    42,     0,     0,    43,     0,    44,   877,     0,
      46,    47,     0,     0,    50,    51,    52,     0,     0,     1,
       2,     3,     4,     5,     6,     0,     0,     0,    10,    11,
       0,     0,   200,   164,     0,   201,     0,     0,     0,   186,
      19,    20,     0,     0,     0,    68,    23,    24,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    27,    28,    29,
      30,     0,     0,    32,    33,   203,     0,     0,   244,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    36,     0,     0,     0,   714,
      37,    38,    39,     0,     0,     0,    40,     0,   243,    42,
       0,     0,    43,     0,    44,     0,     0,    46,    47,     0,
       0,    50,    51,    52,     0,     0,     1,     2,     3,     4,
       5,     6,     0,     0,     0,    10,    11,     0,     0,   200,
     164,     0,   201,     0,     0,     0,   186,    19,    20,     0,
       0,     0,    68,    23,    24,     0,     0,     0,     0,     0,
       0,     0,     0,    26,    27,    28,    29,    30,     0,     0,
      32,    33,   203,     0,     0,   244,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,     0,     0,     0,     0,    37,    38,    39,
       0,     0,     0,    40,     0,   243,    42,     0,     0,    43,
       0,    44,  1027,     0,    46,    47,     0,     0,    50,    51,
      52,     0,     0,     1,     2,     3,     4,     5,     6,     0,
       0,     0,    10,    11,     0,     0,   200,   164,     0,   201,
       0,     0,     0,   186,    19,    20,     0,     0,     0,    68,
      23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
      26,    27,    28,    29,    30,     0,     0,    32,    33,   203,
       0,     0,   244,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    36,
       0,     0,     0,     0,    37,    38,    39,     0,     0,     0,
      40,     0,   243,    42,     0,     0,    43,     0,    44,  1379,
       0,    46,    47,     0,     0,    50,    51,    52,     0,     0,
       1,     2,     3,     4,     5,     6,     0,     0,     0,    10,
      11,     0,     0,   200,   164,     0,   201,     0,     0,     0,
     186,    19,    20,     0,     0,     0,    68,    23,    24,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    27,    28,
      29,    30,     0,     0,    32,    33,   203,     0,     0,   244,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,    36,     0,     0,     0,
       0,    37,    38,    39,     0,     0,     0,    40,     0,   243,
      42,     0,     0,    43,     0,    44,     0,     0,    46,    47,
       0,     0,    50,    51,    52,     0,     0,     1,     2,     3,
       4,     5,     6,     0,     0,     0,    10,    11,     0,     0,
     200,   164,     0,   201,     0,     0,     0,   186,    19,    20,
       0,     0,     0,    68,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,    26,    27,    28,    29,    30,     0,
       0,    32,    33,   203,     0,     0,   244,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,     0,     0,     0,     0,    37,    38,
      39,     0,     0,     0,    40,     0,   243,    42,     0,     0,
     323,     0,    44,     0,     0,    46,    47,     0,     0,    50,
      51,    52,     0,     0,     1,     2,     3,     4,     5,     6,
       0,     0,     0,    10,    11,     0,     0,   200,   164,     0,
     201,     0,     0,     0,   186,    19,    20,     0,     0,     0,
      68,    23,    24,     0,     0,     0,     0,     0,     0,     0,
       0,    26,    27,    28,    29,    30,     0,     0,    32,    33,
     203,     0,     0,   244,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,     0,     0,     0,     0,    37,    38,    39,     0,     0,
       0,    40,     0,   243,    42,     0,     0,    43,     0,   326,
       0,     0,    46,    47,     0,     0,    50,    51,    52,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   586,     0,     0,     0,     0,     0,     0,     0,     0,
     244,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   586,     0,   619,   758,   620,     0,   621,
       0,     0,     0,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,     0,   620,
    1082,   621,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   623,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   624,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   623,   586,     0,     0,     0,
       0,     0,     0,     0,     0,   624,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   618,   586,     0,
     619,     0,   620,  1124,   621,     0,     0,     0,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,   620,  1134,   621,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   623,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   624,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     623,   586,     0,     0,     0,     0,     0,     0,     0,     0,
     624,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   586,     0,   619,     0,   620,  1136,   621,
       0,     0,     0,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,     0,   620,
    1146,   621,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   623,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   624,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   623,   586,     0,     0,     0,
       0,     0,     0,     0,     0,   624,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   618,   586,     0,
     619,     0,   620,     0,   621,  1188,     0,     0,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,   620,     0,   621,  1278,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   623,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   624,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     623,   586,     0,     0,     0,     0,     0,     0,     0,     0,
     624,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   586,     0,   619,     0,   620,     0,   621,
       0,     0,     0,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,     0,   620,
    1326,   621,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   623,     0,     0,     0,     0,     0,     0,
       0,     0,  1281,   624,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   623,   586,     0,     0,     0,
       0,     0,     0,     0,     0,   624,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   618,   586,     0,
     619,     0,   620,  1332,   621,     0,     0,     0,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,   620,  1497,   621,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   623,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   624,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     623,   586,     0,     0,     0,     0,     0,     0,     0,     0,
     624,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   586,     0,   619,     0,   620,  1500,   621,
       0,     0,     0,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,     0,   620,
       0,   621,  1516,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   623,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   624,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   623,   586,     0,     0,     0,
       0,     0,     0,     0,     0,   624,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   618,   586,     0,
     619,     0,   620,  1572,   621,     0,     0,     0,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,   620,  1573,   621,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   623,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   624,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     623,   586,     0,     0,     0,     0,     0,     0,     0,     0,
     624,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   586,     0,   619,     0,   620,  1574,   621,
       0,     0,     0,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   599,   600,   601,   602,   603,
     604,   605,   606,   607,   608,   609,   610,   611,   612,   613,
     614,   615,   616,   617,   618,     0,     0,   619,     0,   620,
    1575,   621,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   623,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   624,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   623,   586,     0,     0,     0,
       0,     0,     0,     0,     0,   624,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   618,   586,     0,
     619,     0,   620,     0,   621,     0,     0,     0,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,   601,   602,   603,   604,   605,   606,   607,   608,
     609,   610,   611,   612,   613,   614,   615,   616,   617,   618,
       0,     0,   619,     0,   620,     0,   621,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   623,     0,
       0,     0,     0,     0,     1,     2,   250,  1662,   624,     6,
       7,   162,     0,    10,    11,     0,     0,   251,   164,     0,
      14,    15,    16,     0,    18,    19,    20,     0,     0,     0,
       0,   165,    24,     0,     0,     0,   166,     0,     0,     0,
     623,    26,     0,     0,     0,     0,     0,     0,     0,     0,
     624,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,     0,   289,
       0,     0,   290,   291,    48,   167,    50,    51,     0,     0,
       0,    54,    55,    56,    57,    58,   168,    60,    61,     1,
       2,     0,     0,     0,     6,     7,   162,     0,    10,    11,
       0,     0,   251,    13,     0,    14,    15,    16,     0,    18,
      19,    20,     0,     0,     0,     0,   165,    24,     0,     0,
       0,   166,     0,     1,     2,     0,    26,     0,     6,     7,
     162,     0,    10,    11,     0,   515,   251,   164,     0,    14,
      15,    16,     0,    18,    19,    20,    21,     0,    22,     0,
     165,    24,     0,     0,     0,   166,     0,     0,     0,     0,
      26,     0,     0,     0,     0,     0,     0,     0,   516,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      49,    50,    51,     0,     0,     0,    54,    55,    56,    57,
      58,   168,    60,    61,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,   480,    50,    51,     0,     0,     0,
      54,    55,    56,    57,    58,   168,    60,    61,     1,     2,
       0,     0,     0,     6,     7,   162,     0,    10,    11,     0,
       0,   251,    13,     0,    14,    15,    16,     0,    18,    19,
      20,     0,     0,     0,     0,   165,    24,     0,     0,     0,
     166,     0,     1,     2,     0,    26,     0,     6,     7,   162,
       0,    10,    11,     0,   515,   163,   164,     0,    14,    15,
      16,     0,    18,    19,    20,     0,     0,     0,     0,   165,
      24,     0,     0,     0,   166,     0,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    48,   517,
      50,    51,     0,     0,     0,    54,    55,    56,    57,    58,
     168,    60,    61,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    48,   167,    50,    51,     0,     0,     0,    54,
      55,    56,    57,    58,   168,    60,    61,     1,     2,     0,
       0,     0,     6,     7,   162,     0,    10,    11,     0,     0,
     251,    13,     0,    14,    15,    16,     0,    18,    19,    20,
       0,     0,     0,     0,   165,    24,     1,     2,     0,   166,
       0,     6,     7,   162,    26,    10,    11,     0,     0,   251,
     164,     0,    14,    15,    16,     0,    18,    19,    20,     0,
       0,     0,     0,   165,    24,     0,     0,     0,   166,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,    49,    50,
      51,     0,     0,     0,    54,    55,    56,    57,    58,   168,
      60,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,   480,    50,    51,
       0,     0,     0,    54,    55,    56,    57,    58,   168,    60,
      61,     1,     2,     0,     0,     0,     6,     7,   162,     0,
      10,    11,     0,     0,   251,   164,     0,    14,    15,    16,
       0,    18,    19,    20,     0,     0,     0,     0,   165,    24,
       1,     2,     0,   166,     0,     6,     7,   162,    26,    10,
      11,     0,     0,   251,    13,     0,    14,    15,    16,     0,
      18,    19,    20,     0,     0,     0,     0,   165,    24,     0,
       0,     0,   166,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    48,   167,    50,    51,     0,     0,     0,    54,    55,
      56,    57,    58,   168,    60,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,   517,    50,    51,     0,     0,     0,    54,    55,    56,
      57,    58,   168,    60,    61,     1,     2,     0,     0,     0,
       6,     7,   162,     0,    10,    11,     0,     0,   251,   164,
       0,  1064,    15,    16,     0,    18,  1065,    20,     0,     0,
       0,     0,   165,    24,     1,     2,     0,   166,     0,     6,
       0,     0,    26,    10,    11,     0,     0,   200,   164,     0,
     201,     0,     0,     0,   186,    19,    20,     0,     0,     0,
       0,   202,    24,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    48,   167,    50,    51,     0,
       0,     0,    54,    55,    56,    57,    58,   168,    60,    61,
       0,     0,     0,  1030,     0,     0,     0,     0,     0,     0,
       1,     2,   250,     0,     0,     6,    50,    51,    52,    10,
      11,     0,     0,   200,   164,     0,   201,     0,     0,     0,
     186,    19,    20,     0,     0,     0,     0,   165,    24,     0,
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,     0,   289,     1,     2,   290,   291,
       0,     6,    50,    51,     0,    10,    11,     0,     0,   200,
     164,     0,   201,     0,     0,     0,   186,    19,    20,     0,
       0,     1,     2,   428,    24,     0,     6,     0,     0,     0,
      10,    11,     0,   429,   200,   164,     0,   201,     0,     0,
       0,   186,    19,    20,     0,     0,     0,     0,   428,    24,
       0,     0,     0,     0,     0,     0,     0,     0,   429,   430,
       0,     0,     0,     0,     0,  -639,     0,     0,     0,   734,
       0,     0,     0,   432,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   430,     0,   433,     0,    50,    51,
       0,     0,     0,     0,   431,     0,     1,     2,   432,     0,
       0,     6,     0,     0,     0,    10,    11,     0,     0,   200,
     164,   433,   201,    50,    51,     0,   186,    19,    20,     0,
       0,     0,     0,   165,    24,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   430,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   431,
       0,     0,     0,   432,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   433,     0,    50,    51
};

static const yytype_int16 yycheck[] =
{
       0,   141,    13,   102,    34,     5,    12,     0,     8,     9,
     749,   130,    12,    49,   212,  1179,   214,    17,   216,   664,
      23,     8,   141,  1049,   133,   119,   120,  1053,   858,    69,
      13,    47,    17,    66,    34,   424,   133,    40,   147,   148,
      73,    41,    59,    43,   143,   133,     3,   956,    18,    49,
     147,   148,   961,     8,   148,    30,    25,   133,    26,   147,
      28,    43,    31,    88,   958,    40,    66,   961,    84,    69,
      92,   147,   148,    73,   173,     3,   133,    86,     3,     4,
     469,  1665,   181,     8,     9,     7,    68,    69,     3,    30,
     147,   442,   108,     3,    49,    72,     3,   133,    23,    40,
      30,  1685,    26,   125,    28,  1125,    72,   118,  1128,  1129,
      40,   147,   148,  1051,  1410,  1411,     3,    30,   118,   119,
     120,     8,    90,   512,    93,    93,   151,    40,     9,    26,
     147,    28,   119,   133,   134,   151,    26,    85,    28,    26,
     146,    28,    72,    40,     3,     4,   146,   147,   148,     8,
       9,    26,   121,    28,    82,    72,    86,   163,    72,    72,
      19,   130,   513,   163,    23,   120,    76,    82,     8,    47,
      92,    96,   141,   203,   149,    82,   182,    30,   178,   134,
     180,   149,   182,   183,   184,   191,    26,    40,    28,    86,
      85,   191,   147,   204,     7,     3,     4,   197,    85,   202,
       8,     9,   150,   125,   244,    86,    84,    47,   149,     3,
      85,    19,    99,     7,   333,    23,   186,     0,     3,   149,
      86,   204,   109,   178,     9,   149,   151,    26,   183,    28,
     108,   620,     8,   233,   124,   125,   149,    96,   238,   239,
     240,   241,     3,    86,    84,   251,  1410,  1411,    47,   249,
     250,   251,   149,    93,    86,   150,    96,    97,  1284,    26,
     150,    28,   244,   150,   462,    86,   235,  1293,   108,   309,
      32,    33,    34,     0,   149,    47,    59,    32,    33,    34,
      32,    33,    34,    66,    49,    84,    69,    26,    96,    28,
      73,    90,   151,    84,   294,    86,   149,   297,   334,    40,
     336,   337,    87,    70,    32,    33,    34,     3,    84,   149,
      95,   314,    84,     9,    72,    76,   117,    93,    92,    80,
      96,    97,    90,   323,  1233,    46,     3,   309,    86,    86,
       3,   371,   108,   350,   334,     8,   336,   337,   355,   379,
    1234,   323,    30,   151,    40,    86,    30,  1177,   354,    72,
     149,   125,    40,    26,   354,    28,    40,  1295,   149,  1297,
     360,   361,     3,    40,   147,   365,   366,   400,  1306,   134,
     370,   371,   372,     3,     4,    19,    20,    21,     8,    23,
      90,   336,   149,   151,   371,   124,   125,   527,   150,   483,
      86,   485,    22,    23,    90,   150,    90,   379,   150,    40,
     400,    30,   521,     5,    30,     3,    90,    84,   527,    86,
       8,    40,    85,   522,    40,   370,   371,   372,   421,   528,
     529,   421,   150,   423,     3,   522,    99,   567,    26,     8,
      28,   528,   529,  1459,   522,    37,   109,    26,   578,    28,
     528,   441,   442,   443,   563,    86,   522,    26,   567,    28,
     233,  1644,   528,   529,  1099,    90,   575,    86,    40,   578,
      47,   105,    90,   474,    90,   522,    96,   576,   479,   568,
     579,   528,     3,   473,  1494,  1495,  1496,   150,     9,   576,
     480,   517,   579,   483,   466,   485,   522,    85,   443,  1682,
      40,   474,   528,   529,     3,     4,   479,    84,  1436,     8,
     576,    99,  1695,    90,    86,  1443,    85,    26,   519,    28,
      40,   109,     5,   513,    23,   515,   516,   517,     3,   519,
      99,   108,   522,     5,     9,   480,  1552,    40,   528,   529,
     109,    40,    32,    33,    34,    16,    86,    87,    30,    86,
     576,     3,     4,   579,    37,    76,     8,     9,    40,    80,
      12,    13,   150,    85,    16,    17,    86,    19,   527,   559,
       3,    23,    24,    25,   151,     8,    85,   350,    30,    31,
     539,   150,   355,    86,    87,    84,   576,    84,    40,   579,
      72,   581,    30,    26,    93,    28,     3,    96,    97,    73,
       3,     8,    40,    30,    30,     8,   607,   608,   567,   108,
      84,    85,   102,    40,    40,   370,   371,   372,    30,    26,
      30,    28,   623,    26,     8,    28,     3,   400,    40,  1557,
      40,     8,   628,   629,   579,     3,     4,  1366,   628,   629,
       8,   631,    73,    95,    96,     3,     4,     3,    86,    26,
       8,    28,    85,     9,    85,    23,   631,     0,   648,    10,
     650,    40,    72,    47,    90,    23,    99,   660,    90,    20,
      21,    73,    40,   663,   664,    40,   109,    73,    85,    30,
      90,   671,    85,    85,    35,    12,    13,    97,   443,    85,
      40,  1619,    99,     8,   149,    30,    99,   687,    73,   151,
      84,    86,   109,    73,    31,    40,   109,    86,    87,    93,
      85,    40,    96,    97,    72,    85,    85,   150,    87,   664,
      84,    72,    99,    66,   108,   480,    69,    86,    96,     0,
      73,    82,   109,    70,  1369,    86,    86,    72,    96,    86,
    1375,     8,    73,   150,   932,   933,   736,   150,   774,   100,
     101,   102,   103,   104,   105,   106,   107,    86,    73,    26,
     849,    28,    97,     3,     4,    87,   756,   797,     8,    84,
      85,    86,    87,    88,   775,    90,    30,   149,    93,    30,
      47,    96,    97,    23,   774,   775,    40,    30,   149,    40,
     151,   781,    88,   108,    40,    66,    85,    40,    69,    89,
      40,    90,    73,  1438,    66,     3,     4,    88,   828,    84,
       8,    86,    40,    88,    76,     3,     4,    84,    80,    85,
       8,    72,    76,    90,    90,    23,    93,    73,    90,    96,
      97,    93,   931,   823,   149,    23,   151,   833,   828,    90,
      86,   108,    40,   833,   931,    73,    86,    90,   119,   120,
      85,   981,   149,    10,   151,    90,    96,    97,    86,    30,
      30,    49,    86,    20,    21,   855,     3,     4,   858,    40,
      40,     8,   981,   149,   149,   151,   151,   148,    35,    30,
     870,    40,   149,     3,     4,   984,    23,   986,     8,    40,
     233,     3,     4,    85,   884,   885,     8,   984,    96,   986,
      30,    72,    72,    23,     0,   931,    87,    10,    96,   664,
      40,    23,    49,   858,    73,    86,    86,    20,    21,     0,
      40,    72,    19,    20,    21,    82,    23,    86,   924,    86,
      18,    89,    35,   923,   924,     3,     4,    49,    18,    90,
       8,   931,    72,   100,   101,   102,   103,   104,   105,   106,
     107,   151,    18,    73,    91,    23,  1045,  1592,   984,    96,
     986,    85,   233,    87,    84,    85,   121,  1602,    30,    85,
      66,    87,    30,    69,   151,   151,    96,    73,    40,    40,
      86,    85,    40,    87,    96,    66,     3,     4,    69,     7,
      85,     8,    73,    26,   984,    28,   986,   100,   101,   102,
     103,   104,   105,   106,   107,    84,    23,    86,    76,    88,
      72,  1012,    73,  1648,    72,    26,  1651,    28,    85,     0,
      87,     3,     4,    30,    93,    86,     8,     8,    96,  1030,
      12,    13,    49,    40,    16,    17,  1671,    19,    32,    33,
      34,    23,    24,    25,  1034,    85,  1042,    87,    30,    31,
      86,   147,  1042,    85,  1689,    87,    70,   400,    40,  1034,
      85,  1051,    87,     3,     4,    72,  1056,    49,     8,    85,
     149,    87,   151,  1063,  1064,  1065,  1066,     3,     4,    96,
    1063,    89,     8,    23,    85,    66,    87,   183,    69,  1064,
    1065,    89,    73,    72,    72,  1125,    30,    23,  1128,  1129,
    1123,  1124,    85,   858,    87,    85,    40,    87,     0,  1099,
    1133,  1134,    94,    95,    96,    97,     8,     9,    30,    95,
      12,    13,    14,    15,    16,    86,    18,    19,    40,   400,
      30,    23,    87,  1123,  1124,    87,    76,   233,    72,    30,
      40,  1100,    34,  1133,  1134,    90,     3,     4,    90,    40,
      76,     8,   233,    86,  1099,    30,    96,    49,  1148,   150,
      72,  1151,    32,    33,    34,    40,    23,    59,  1158,    85,
      96,    87,    72,  1148,    66,    66,    30,    69,    90,   150,
    1310,    73,    87,     3,     4,    76,   150,  1177,     8,    80,
       3,     4,  1182,  1183,  1184,     8,    87,    72,     7,    87,
     102,  1191,   298,    23,  1194,    97,   149,    84,    87,    86,
      23,    88,   483,    90,   485,    90,    87,   149,    87,  1194,
      40,    84,  1212,    66,  1214,  1215,   118,   119,   120,    90,
      90,    86,  1177,    76,    84,    85,    86,    80,    88,    96,
     336,   133,   134,    66,    86,    86,  1218,  1219,    38,    39,
      93,    66,   233,    76,   146,   147,   148,    80,    86,   149,
      87,    76,    87,    76,    84,    80,    86,    90,    88,    86,
      93,   163,   149,   165,   151,    90,    96,    97,    93,   171,
      86,    30,    87,    96,   176,    87,   178,   151,   180,    86,
    1063,   183,   184,   185,   186,    84,    84,    84,    84,   149,
     192,   151,    87,    66,   400,  1295,    90,  1297,   200,    90,
     202,   203,   204,    76,    90,    86,  1306,    80,    87,   400,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
      93,    87,    30,  1323,    87,    87,   150,    87,    86,   149,
      87,   233,    40,    84,  1099,    87,   238,   239,   240,   241,
    1123,  1124,    93,  1343,    86,    96,    97,    87,    87,   251,
    1133,  1134,    87,    86,    47,    86,    86,   108,    66,   151,
      66,    87,    87,   151,    72,    86,  1366,  1367,    76,  1369,
      76,    86,    80,    87,    80,  1375,  1376,    87,    84,    85,
    1503,    87,    88,    86,    90,    93,   242,    93,  1388,  1389,
     292,    24,   294,  1297,   147,   297,     3,   648,     5,     6,
       7,  1383,  1158,   941,  1424,  1239,    -1,  1323,  1408,   400,
      -1,    18,  1177,    -1,  1369,    -1,    -1,    -1,    -1,    -1,
    1375,  1421,   528,  1408,    -1,    -1,    -1,    -1,  1421,    -1,
      -1,    -1,   334,    -1,   336,   337,  1436,    -1,  1438,    -1,
      -1,    -1,    -1,  1443,    -1,    -1,    -1,    -1,   350,    -1,
      -1,    -1,   354,    -1,  1494,  1495,  1496,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1497,    -1,    -1,  1467,    -1,    -1,
      -1,    -1,  1472,   579,    -1,    -1,  1595,    -1,    -1,    -1,
      -1,    -1,    -1,  1438,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,  1497,   400,    -1,
       8,     9,    -1,    -1,    12,    13,    -1,    -1,    16,    17,
      -1,    19,  1512,    -1,    -1,    23,    24,    25,    -1,   421,
      -1,  1490,    30,    31,    -1,    -1,   428,    -1,    -1,  1529,
      -1,    -1,    40,    -1,    -1,  1504,    -1,    -1,    -1,    -1,
      -1,   443,   648,    -1,  1529,    -1,  1665,    -1,  1548,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1557,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1685,    -1,    -1,    -1,
      -1,    -1,   474,    -1,    -1,    -1,    -1,   479,   480,    -1,
      -1,   483,    -1,   485,    -1,    -1,   488,    95,    96,    -1,
      -1,    -1,  1592,    -1,    -1,    -1,  1629,  1630,  1631,    -1,
      -1,    -1,  1602,    -1,  1369,    -1,  1606,    -1,    -1,    -1,
    1375,    -1,    -1,   515,    -1,   517,    -1,   519,    -1,  1619,
     522,  1606,    -1,    -1,    -1,  1594,   528,   529,    -1,  1629,
    1630,  1631,    -1,    -1,  1634,   537,    -1,  1592,  1421,    -1,
      -1,  1634,    -1,    -1,    -1,    -1,    -1,  1602,  1648,    -1,
      -1,  1651,    -1,    -1,  1654,    -1,   558,   559,    -1,    -1,
      -1,  1654,  1662,    -1,    -1,    -1,    -1,    -1,   774,  1662,
      -1,  1671,    -1,  1438,   576,    -1,    -1,   579,    -1,    -1,
     671,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1689,
      -1,    -1,    -1,  1648,    -1,  1664,  1651,  1666,  1051,    -1,
      -1,    -1,    -1,    -1,    -1,   607,   608,    -1,    -1,    -1,
    1063,    -1,    -1,    -1,  1497,  1684,  1671,    -1,    -1,    -1,
      -1,   623,    -1,  1692,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   633,  1701,    -1,  1689,    -1,    -1,    -1,    -1,    -1,
      -1,   643,    -1,    -1,    -1,    -1,   648,    -1,    -1,    -1,
      -1,   653,    -1,    -1,    -1,    -1,    -1,    -1,   660,   661,
      -1,   663,   664,    -1,    -1,    -1,    -1,   669,    -1,   671,
    1123,  1124,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
    1133,  1134,  1063,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,     0,    -1,    84,    85,    86,
      87,    88,    -1,     8,    -1,   931,    -1,  1592,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1602,    -1,    -1,
      -1,     0,  1123,  1124,    -1,    -1,  1629,  1630,  1631,     8,
      -1,  1634,  1133,  1134,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,  1654,   774,   775,    -1,   142,   778,    -1,    -1,  1662,
      -1,    66,    -1,  1648,    69,   152,  1651,    -1,    73,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    -1,    -1,    -1,    -1,    -1,  1671,    66,    -1,    -1,
      69,    -1,    -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,
      -1,   823,    -1,    -1,  1689,    -1,   828,    -1,    -1,    -1,
      -1,   833,    -1,     0,   119,   120,    -1,    -1,    -1,    -1,
      -1,     8,  1295,    -1,  1297,    -1,    -1,   849,    -1,   134,
      -1,    -1,    -1,  1306,    -1,    -1,   858,  1063,    -1,   861,
     119,   120,   147,   148,    -1,    -1,    -1,    34,    -1,    -1,
      -1,    -1,  1063,    -1,   133,   134,    43,    -1,    -1,    46,
      -1,    -1,    49,    -1,   886,    -1,    -1,    -1,   147,   148,
      -1,    -1,    59,   178,    -1,    -1,    -1,    -1,   183,    66,
      -1,    -1,    69,    -1,    -1,    -1,    73,    -1,    -1,    -1,
      -1,    -1,   914,    -1,    -1,    -1,    -1,  1123,  1124,   178,
      -1,   923,    -1,    -1,   183,    -1,    -1,  1133,  1134,   931,
      97,    -1,  1123,  1124,    -1,    -1,    -1,    -1,    -1,   941,
      -1,    -1,  1133,  1134,    -1,    -1,    -1,    -1,   233,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   133,   134,  1421,    -1,
      -1,    -1,  1063,   975,   233,    -1,    -1,    -1,    -1,   146,
     147,   148,   984,  1436,   986,    -1,    -1,     3,     4,    -1,
    1443,    -1,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,
      16,    17,    -1,    19,   171,    -1,    -1,    23,    24,    25,
    1012,   178,    -1,   180,    30,    31,   183,   184,    -1,    -1,
      -1,    -1,    -1,    -1,    40,   192,    -1,    -1,  1030,    -1,
      -1,    -1,  1123,  1124,    -1,    -1,   203,    -1,    -1,    -1,
    1421,    -1,  1133,  1134,  1497,  1047,    -1,    -1,    -1,    -1,
      -1,   336,  1054,    -1,  1056,    -1,    -1,    -1,    -1,    -1,
      -1,  1063,  1064,  1065,    -1,    -1,   233,    -1,    -1,    -1,
      -1,   238,   239,   240,   241,   334,    -1,   336,   337,    95,
      96,    -1,   249,    -1,    -1,   370,   371,   372,    -1,    -1,
      -1,   350,    25,    -1,    -1,    -1,   355,  1099,    31,    -1,
      -1,    -1,    -1,    -1,  1557,    -1,    -1,    -1,    -1,    -1,
      -1,   370,   371,   372,    -1,   400,  1497,    -1,    -1,    -1,
      -1,  1123,  1124,    -1,    -1,   292,    -1,   294,    -1,    -1,
     297,  1133,  1134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   400,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   323,    -1,   443,    -1,
      93,    -1,    -1,    -1,    -1,    -1,  1619,   334,    -1,   336,
     337,    -1,    -1,    -1,    -1,  1177,  1629,  1630,  1631,    -1,
      -1,  1634,    -1,   350,   443,    -1,    -1,   354,   121,    -1,
      -1,    -1,    -1,    -1,    -1,   480,    -1,   130,   483,    -1,
     485,  1654,    -1,   370,   371,   372,    -1,    -1,   141,  1662,
    1212,  1213,    -1,    -1,    -1,  1421,    -1,    -1,    -1,    -1,
      -1,   480,    -1,    -1,   483,    -1,   485,    -1,  1230,  1231,
    1421,    -1,  1323,   400,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1629,  1630,
    1631,    -1,    -1,  1634,    -1,    -1,   423,    -1,   517,    -1,
      -1,   428,    -1,   522,    -1,    -1,    -1,    -1,    -1,   528,
     529,    -1,    -1,  1654,    -1,   442,   443,    -1,    -1,    -1,
      -1,  1662,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1497,  1294,    -1,   579,    -1,    -1,    -1,    -1,   466,
      -1,    -1,   235,    -1,    -1,    -1,  1497,    -1,    -1,    -1,
      -1,    -1,    -1,   480,    -1,    -1,   483,   576,   485,    -1,
     579,  1323,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1421,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1343,    -1,    -1,    -1,    -1,   513,    -1,   515,    -1,
     517,    -1,    -1,    -1,    -1,   522,    -1,    -1,    -1,    -1,
      -1,   528,   529,    -1,    -1,    -1,    -1,  1369,    -1,    -1,
      -1,    -1,    -1,  1375,    -1,    -1,    -1,    -1,    -1,   664,
      -1,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1400,    -1,
      -1,    -1,  1404,    -1,    -1,   664,  1497,    34,    -1,   576,
      -1,    -1,   579,    -1,    -1,    -1,    43,  1419,  1420,  1421,
      -1,    -1,    -1,  1629,  1630,  1631,    -1,    -1,  1634,    43,
      44,    -1,    -1,    -1,    -1,    -1,  1438,    -1,  1629,  1630,
    1631,    -1,    -1,  1634,    -1,    -1,    -1,    -1,  1654,    -1,
      -1,    -1,    -1,    -1,    68,    69,  1662,    -1,    -1,    -1,
      -1,    -1,    -1,  1654,    -1,  1467,    -1,    -1,    -1,    -1,
    1472,  1662,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   648,    -1,    -1,    -1,    -1,   653,    -1,    -1,    -1,
      -1,    -1,   119,   120,   661,  1497,   663,   664,    -1,    -1,
      -1,    -1,    -1,    -1,   671,    -1,   133,   134,    -1,    -1,
     443,    -1,    -1,    -1,    -1,   774,    -1,    -1,    -1,    -1,
     687,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1533,    -1,    -1,    -1,    -1,    -1,    -1,  1629,  1630,
    1631,    -1,    -1,  1634,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   178,    -1,   180,    -1,    -1,   183,   184,    -1,    -1,
      -1,    -1,    -1,  1654,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1662,    -1,   858,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1592,    -1,    -1,    -1,   527,    -1,    -1,    -1,    -1,   858,
    1602,    -1,     0,    -1,    -1,    -1,   539,   774,    -1,    -1,
       8,   238,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   249,   556,    -1,    -1,    -1,  1629,  1630,  1631,
     244,    -1,  1634,    -1,   567,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1648,    -1,    -1,  1651,
      -1,    49,  1654,    -1,    -1,    -1,   823,    -1,    -1,    -1,
    1662,   828,    -1,    -1,    -1,    -1,   833,   294,    66,  1671,
     297,    69,   931,    -1,    -1,    73,    -1,     9,    10,    11,
      -1,    -1,   849,    -1,    -1,    -1,    -1,  1689,    20,    21,
      22,   858,    -1,    -1,    -1,   309,   323,    -1,    -1,    -1,
      32,    33,    34,    35,    -1,    -1,    -1,   334,    -1,   323,
     337,    -1,   326,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   119,    -1,    -1,    -1,   984,    -1,   986,    -1,    -1,
      -1,   664,    -1,    -1,    -1,   133,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   370,   371,   372,    -1,    -1,    -1,   147,
     148,    -1,    -1,    -1,    -1,    -1,    -1,   371,    90,    -1,
      -1,    93,    94,    -1,   931,   379,    98,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,   109,  1063,    -1,
      -1,    -1,   114,    -1,    -1,    -1,    -1,    -1,   120,   121,
     122,   123,    -1,    -1,    -1,    -1,   423,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1063,    -1,    -1,    -1,    -1,    -1,
     424,    -1,    -1,    -1,  1099,   442,   443,   984,    -1,   986,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,  1123,  1124,
    1099,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1133,  1134,
      -1,    -1,   466,   480,    -1,   469,   483,    -1,   485,    -1,
      -1,    -1,    -1,    -1,  1123,  1124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1133,  1134,    -1,    -1,    -1,    -1,
    1047,    -1,    -1,    -1,    -1,    -1,   513,  1054,   515,  1056,
     517,    -1,  1177,    -1,    -1,   522,  1063,    -1,   512,    -1,
      -1,   528,   529,    -1,    -1,    -1,     3,     4,    -1,    -1,
      -1,     8,     9,    -1,    -1,    12,    13,    -1,  1177,    16,
      17,    -1,    19,    -1,    -1,   858,    23,    24,    25,    -1,
      -1,    -1,  1099,    30,    31,    -1,   334,    -1,   336,   337,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,   576,
      -1,    -1,    49,    -1,    -1,    -1,  1123,  1124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1133,  1134,    -1,    66,
      -1,    -1,    -1,   371,    -1,    72,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    86,
      -1,  1158,    -1,    -1,    -1,    -1,    93,    94,    95,    96,
      97,    -1,   400,    -1,    -1,    -1,   620,    -1,    -1,    -1,
    1177,    -1,    -1,     3,     4,    -1,    -1,    -1,     8,    -1,
      -1,   648,    12,    13,    -1,    -1,    16,    17,    -1,    19,
      20,    21,    -1,    23,    24,    25,   663,   664,    -1,    -1,
      30,    31,    -1,    -1,   671,  1212,    -1,    -1,    -1,    -1,
      40,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     687,    -1,    -1,  1230,  1231,    -1,     3,     4,    -1,    -1,
      -1,     8,     9,     0,    -1,    12,    13,    -1,    -1,    16,
      17,    -1,    19,    -1,  1369,    12,    23,    24,    25,    -1,
    1375,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    95,    96,    -1,    -1,    -1,
    1369,    -1,    49,    -1,    -1,   105,  1375,    -1,  1051,   517,
      -1,    -1,    49,    -1,   522,    -1,    -1,  1294,    -1,    -1,
     528,   529,    -1,    -1,    -1,    -1,  1421,    -1,    -1,    66,
      -1,    -1,    69,    -1,    -1,    -1,    73,   774,    -1,    86,
      -1,    -1,    -1,  1438,    -1,    -1,  1323,    94,    95,    96,
      97,    -1,  1421,    -1,    -1,    -1,  1099,  1100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1343,    -1,   576,  1438,
      -1,   579,    -1,   797,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,   120,    -1,    -1,   823,    -1,    -1,    -1,
      -1,   828,  1369,    -1,    -1,    -1,   133,    -1,  1375,    -1,
      -1,    -1,  1497,    -1,    -1,    -1,    -1,    -1,    -1,   146,
     147,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   858,    -1,    -1,    -1,    -1,   163,    -1,  1497,    -1,
      -1,    -1,    -1,    -1,  1177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1419,  1420,  1421,   182,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   191,    -1,    -1,    -1,    -1,    -1,
      -1,  1438,    -1,    -1,    -1,     3,     4,    -1,    -1,    -1,
       8,     9,    -1,    -1,    12,    13,    -1,    -1,    16,    17,
      -1,    19,    -1,    -1,    -1,    23,    24,    25,    -1,    -1,
    1467,    -1,    30,    31,   931,  1472,   233,  1592,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,  1602,    -1,    -1,
      34,    -1,    -1,    -1,   251,    -1,    -1,    -1,    -1,    43,
    1497,    -1,    -1,  1592,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,  1602,  1629,  1630,  1631,    -1,    76,  1634,
      -1,    -1,    80,    -1,    -1,    -1,    -1,   984,    -1,   986,
      -1,    -1,  1295,  1648,  1297,    93,  1651,    95,    96,  1654,
    1629,  1630,  1631,  1306,    -1,  1634,   774,  1662,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1671,    -1,    -1,  1648,
      -1,    -1,  1651,    -1,    -1,  1654,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1662,  1689,    -1,    -1,   334,    -1,   336,
     337,    -1,  1671,    -1,    -1,    -1,    -1,    -1,    -1,   133,
      -1,    -1,    -1,    -1,    -1,  1592,    -1,   354,    -1,  1056,
    1689,    -1,    -1,    -1,   148,  1602,  1369,    -1,    -1,    -1,
      -1,    -1,  1375,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1629,  1630,  1631,    -1,   180,  1634,    -1,    -1,
     184,    -1,  1099,   400,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1648,    -1,    -1,  1651,    -1,    -1,  1654,    -1,    -1,
      -1,  1424,    -1,    -1,    -1,  1662,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1436,  1671,  1438,    -1,    -1,    -1,    -1,
    1443,  1125,    -1,    -1,  1128,  1129,    -1,    -1,    -1,    -1,
      -1,    -1,  1689,    -1,   238,   239,   240,   241,    -1,    -1,
      -1,  1158,    -1,   931,    -1,   249,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   473,    -1,    -1,    -1,
    1177,    -1,    -1,    -1,     3,     4,   483,  1490,   485,     8,
       9,    -1,    -1,    12,    13,    -1,    -1,    16,    17,    -1,
      19,  1504,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,
     294,    30,    31,   297,    -1,  1212,   984,    -1,   986,    -1,
     517,    40,   519,    -1,    -1,   522,    -1,    -1,    -1,    -1,
      49,   528,   529,    -1,  1218,  1219,    -1,    -1,    -1,   323,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     334,    -1,    -1,   337,  1557,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    94,    95,    96,    97,   576,
      -1,    -1,   579,    -1,    -1,    -1,    -1,    -1,    -1,  1592,
      -1,  1594,    -1,    -1,    -1,  1063,    -1,    -1,    -1,  1602,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     9,    10,    11,    -1,    -1,  1619,    -1,    -1,    -1,
      -1,    -1,    20,    21,    22,    -1,  1323,    -1,    -1,    -1,
      -1,   628,   629,    -1,    32,    33,    34,    35,    -1,   423,
      -1,    -1,    -1,    -1,    -1,  1648,  1343,    45,  1651,    -1,
      -1,    -1,    -1,    -1,    -1,  1123,  1124,    -1,   442,   443,
      -1,  1664,    -1,  1666,    -1,  1133,  1134,    -1,  1671,    -1,
      -1,    -1,  1369,    -1,    -1,    -1,    -1,  1361,  1375,    -1,
      -1,  1684,    -1,    -1,    -1,    -1,  1689,    -1,    -1,  1692,
      -1,    -1,    90,    -1,    -1,    93,    94,    -1,  1701,  1383,
      98,   485,   100,   101,   102,   103,   104,   105,   106,   107,
      -1,   109,    -1,    -1,    -1,    -1,   114,    -1,    -1,    -1,
      -1,    -1,   120,   121,   122,   123,    -1,    -1,    -1,   513,
      -1,   515,    -1,   517,    -1,    -1,    -1,    -1,   522,   736,
      -1,  1438,    -1,    -1,   528,   529,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,    -1,    -1,    -1,     8,    -1,   756,
      -1,    12,    13,    -1,    -1,    16,    17,    -1,    19,    -1,
    1467,    -1,    23,    24,    25,  1472,    -1,   774,   775,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,   576,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1494,  1495,  1496,    -1,    -1,    -1,    -1,  1501,    -1,  1503,
      -1,     3,     4,    -1,    -1,    -1,     8,     9,    10,    11,
      12,    13,    -1,    -1,    16,    17,   833,    19,    20,    21,
      -1,    23,    24,    25,    95,    96,    97,    -1,    30,    31,
      -1,    -1,    -1,    35,    -1,    -1,     3,     4,    40,    -1,
      -1,     8,     9,    -1,   648,    12,    13,    49,    -1,    16,
      17,    -1,    19,    -1,    -1,    -1,    23,    24,    25,   663,
     664,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,  1592,    -1,    -1,    -1,    -1,
      82,    -1,    49,   687,  1588,  1602,    -1,    -1,    -1,    -1,
      -1,    93,    94,    95,    96,    -1,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,   924,    -1,    -1,
      -1,    -1,    -1,    -1,   931,    -1,    -1,    -1,    -1,    86,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,
      97,  1648,    -1,  1421,  1651,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,  1671,    46,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   984,    -1,   986,
     774,    -1,  1689,    -1,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,  1497,
      23,    24,    25,    26,    -1,    28,    -1,    30,    31,   823,
      -1,    -1,    -1,    -1,   828,  1042,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1063,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   858,    68,    69,    -1,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,    82,
      83,    -1,    -1,    86,    -1,    88,    -1,    -1,    91,    92,
      -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1123,  1124,    -1,    -1,
      -1,    -1,    -1,   126,    -1,    -1,  1133,  1134,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   931,    -1,    -1,
      -1,    -1,    -1,    -1,   225,    -1,   149,   150,    -1,    -1,
      -1,  1629,  1630,  1631,    -1,    -1,  1634,    -1,    -1,    -1,
      -1,    -1,   243,   244,    -1,    -1,    -1,    -1,   249,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1654,    -1,    -1,    -1,
      -1,    -1,    -1,    40,  1662,    -1,    -1,    -1,    -1,    -1,
     984,    -1,   986,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,   309,    86,
      87,    88,    -1,   314,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   323,    -1,    -1,   326,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1056,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,   370,
     371,   372,    -1,   374,    -1,   152,    -1,    -1,   379,    -1,
      -1,     3,     4,    -1,    -1,  1099,     8,     9,    10,    -1,
      12,    13,    -1,   394,    16,    17,    -1,    19,    20,    21,
      -1,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,   423,   424,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1366,
      -1,   442,    -1,    -1,  1158,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      82,    -1,    -1,  1177,   465,   466,   467,    -1,   469,   470,
      -1,    93,    94,    95,    96,    -1,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1421,    -1,    -1,    -1,  1212,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   512,   513,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    84,    85,    86,    -1,    88,    -1,    90,
    1497,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   587,   588,   589,   590,
     591,   592,   593,   594,   595,   596,   597,   598,   599,   600,
     601,   602,   603,   604,    -1,    -1,    -1,    -1,   609,   610,
     611,   612,   613,   614,   615,   616,   617,   618,   619,   620,
     621,   142,    -1,   624,   625,    -1,    -1,    -1,    -1,  1343,
      -1,   152,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,  1369,    70,    71,    72,    73,
      -1,  1375,    -1,    77,    78,    79,    -1,    81,     3,     4,
      84,    85,    86,     8,    -1,   676,    90,    12,    13,    -1,
      -1,    16,    17,    -1,    19,    -1,   687,    -1,    23,    24,
      25,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    -1,
      -1,    -1,  1629,  1630,  1631,    40,    -1,  1634,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1438,    -1,    -1,  1654,   142,    -1,
      -1,    -1,    -1,    -1,    -1,  1662,    -1,    -1,   152,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    -1,  1467,    -1,    -1,   757,   758,  1472,   760,
      95,    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,   770,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   797,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   810,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    -1,    30,    31,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    45,    -1,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1592,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,  1602,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,
      82,    83,    -1,    -1,    86,    -1,    88,    -1,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,   109,    -1,    -1,
      -1,    -1,   114,    -1,  1648,    -1,    -1,  1651,   120,   121,
     122,   123,    -1,    -1,   126,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,  1671,    12,    13,
      -1,    -1,    16,    17,    -1,    19,    -1,   149,   150,    23,
      24,    25,    26,    -1,    28,  1689,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      74,    75,    76,    -1,    -1,    -1,    80,    -1,    82,    83,
      -1,    -1,    86,    -1,    88,    -1,    -1,    91,    92,    -1,
      -1,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,
       7,     8,   126,    -1,    -1,    12,    13,    -1,    -1,    16,
      17,    -1,    19,    -1,    -1,    -1,    23,    24,    25,    -1,
      -1,    -1,    -1,    30,    31,   149,   150,    -1,    -1,    -1,
      -1,  1102,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1125,    -1,    -1,  1128,  1129,  1130,
      -1,    68,    69,    -1,  1135,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    80,    -1,    82,    83,    -1,    -1,    86,
      -1,    88,    -1,    -1,    91,    92,    -1,  1158,    95,    96,
      97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1173,  1174,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      -1,    -1,   149,   150,    -1,    -1,    -1,  1218,  1219,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    84,    -1,    86,    -1,    88,    -1,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
    1281,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,    -1,    30,    31,    -1,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      45,   142,    47,    48,    49,    -1,  1317,    -1,    -1,  1320,
      -1,   152,    -1,    -1,    -1,  1326,  1327,  1328,  1329,  1330,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    80,    -1,    82,    83,    -1,
      -1,    86,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,    -1,   109,    -1,    -1,    -1,    -1,   114,
      -1,    -1,  1383,    -1,    -1,   120,   121,   122,   123,    -1,
      -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    12,    13,
      -1,    -1,    16,    17,    -1,    19,    20,    21,    -1,    23,
      24,    25,    26,    -1,    28,    -1,    30,    31,    -1,    -1,
      -1,    35,    -1,  1454,    -1,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1475,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      74,    75,    76,  1494,  1495,  1496,    80,    -1,    82,    83,
      -1,    -1,    86,    -1,    88,    -1,    -1,    91,    92,    93,
      94,    95,    96,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    -1,   126,    16,    17,    -1,    19,    20,    21,    -1,
      23,    24,    25,    26,    -1,    28,    -1,    30,    31,    -1,
      -1,    -1,    35,    -1,    -1,   149,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,  1584,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,    82,
      83,    -1,    -1,    86,    -1,    88,    -1,    -1,    91,    92,
      93,    94,    95,    96,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    13,    -1,   126,    16,    17,    -1,    19,    20,    21,
      -1,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    35,    -1,    -1,   149,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,
      82,    83,    -1,    -1,    86,    -1,    88,    -1,    -1,    91,
      92,    93,    94,    95,    96,    97,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    12,    13,    -1,   126,    16,    17,    -1,    19,    20,
      21,    -1,    23,    24,    25,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    35,    -1,    -1,   149,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,
      -1,    82,    83,    -1,    -1,    86,    -1,    88,    -1,    -1,
      91,    92,    93,    94,    95,    96,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,   126,    16,    17,    -1,    19,
      -1,    -1,    -1,    23,    24,    25,    26,    -1,    28,    -1,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    -1,    88,    89,
      -1,    91,    92,    -1,    -1,    95,    96,    97,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,
      23,    24,    25,    26,    -1,    28,   126,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    49,    -1,    -1,   149,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    -1,    88,    -1,    -1,    91,    92,
      -1,    -1,    95,    96,    97,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,
      16,    17,    -1,    19,    -1,    -1,    -1,    23,    24,    25,
      26,    -1,    28,   126,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    49,    -1,    -1,   149,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    -1,    -1,
      86,    87,    88,    -1,    -1,    91,    92,    -1,    -1,    95,
      96,    97,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    16,    17,    -1,
      19,    -1,    -1,    -1,    23,    24,    25,    26,    -1,    28,
     126,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      49,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      -1,    80,    -1,    82,    83,    -1,    -1,    86,    87,    88,
      -1,    -1,    91,    92,    -1,    -1,    95,    96,    97,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,
      -1,    23,    24,    25,    26,    -1,    28,   126,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      42,    43,    44,    -1,    -1,    47,    48,    49,    -1,    -1,
     149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,
      82,    83,    -1,    -1,    86,    -1,    88,    -1,    -1,    91,
      92,    -1,    -1,    95,    96,    97,    -1,    -1,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,
      -1,    16,    17,    -1,    19,    -1,    -1,    -1,    23,    24,
      25,    26,    -1,    28,   126,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,    -1,    -1,   149,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    74,
      75,    76,    -1,    -1,    -1,    80,    -1,    82,    83,    -1,
      -1,    86,    -1,    88,    -1,    -1,    91,    92,    -1,    -1,
      95,    96,    97,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    -1,    -1,    16,    17,
      -1,    19,    -1,    -1,    -1,    23,    24,    25,    -1,    -1,
      -1,   126,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    49,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,
      -1,    -1,    80,    -1,    82,    83,    -1,    -1,    86,    87,
      88,    -1,    -1,    91,    92,    -1,    -1,    95,    96,    97,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    -1,    16,    17,    -1,    19,    -1,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,   126,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,    49,    -1,
      -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,    80,
      -1,    82,    83,    -1,    -1,    86,    -1,    88,    89,    -1,
      91,    92,    -1,    -1,    95,    96,    97,    -1,    -1,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,    23,
      24,    25,    -1,    -1,    -1,   126,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    49,    -1,    -1,   149,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    73,
      74,    75,    76,    -1,    -1,    -1,    80,    -1,    82,    83,
      -1,    -1,    86,    -1,    88,    -1,    -1,    91,    92,    -1,
      -1,    95,    96,    97,    -1,    -1,     3,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    16,
      17,    -1,    19,    -1,    -1,    -1,    23,    24,    25,    -1,
      -1,    -1,   126,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,    -1,
      47,    48,    49,    -1,    -1,   149,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    -1,    -1,    -1,    -1,    74,    75,    76,
      -1,    -1,    -1,    80,    -1,    82,    83,    -1,    -1,    86,
      -1,    88,    89,    -1,    91,    92,    -1,    -1,    95,    96,
      97,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    -1,    16,    17,    -1,    19,
      -1,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,   126,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    49,
      -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,    -1,
      80,    -1,    82,    83,    -1,    -1,    86,    -1,    88,    89,
      -1,    91,    92,    -1,    -1,    95,    96,    97,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,
      23,    24,    25,    -1,    -1,    -1,   126,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    49,    -1,    -1,   149,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    74,    75,    76,    -1,    -1,    -1,    80,    -1,    82,
      83,    -1,    -1,    86,    -1,    88,    -1,    -1,    91,    92,
      -1,    -1,    95,    96,    97,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,
      16,    17,    -1,    19,    -1,    -1,    -1,    23,    24,    25,
      -1,    -1,    -1,   126,    30,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    49,    -1,    -1,   149,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    74,    75,
      76,    -1,    -1,    -1,    80,    -1,    82,    83,    -1,    -1,
      86,    -1,    88,    -1,    -1,    91,    92,    -1,    -1,    95,
      96,    97,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    16,    17,    -1,
      19,    -1,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,
     126,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      49,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    74,    75,    76,    -1,    -1,
      -1,    80,    -1,    82,    83,    -1,    -1,    86,    -1,    88,
      -1,    -1,    91,    92,    -1,    -1,    95,    96,    97,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   126,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    40,    -1,    84,    85,    86,    -1,    88,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    -1,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   152,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   152,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    40,    -1,
      84,    -1,    86,    87,    88,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    84,    -1,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     152,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    40,    -1,    84,    -1,    86,    87,    88,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    -1,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   152,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   152,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    40,    -1,
      84,    -1,    86,    -1,    88,    89,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    84,    -1,    86,    -1,    88,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     152,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    40,    -1,    84,    -1,    86,    -1,    88,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    -1,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   151,   152,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   152,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    40,    -1,
      84,    -1,    86,    87,    88,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    84,    -1,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     152,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    40,    -1,    84,    -1,    86,    87,    88,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    -1,    86,
      -1,    88,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   152,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   152,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    40,    -1,
      84,    -1,    86,    87,    88,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    84,    -1,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     142,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     152,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    40,    -1,    84,    -1,    86,    87,    88,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    -1,    -1,    84,    -1,    86,
      87,    88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   152,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   152,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    40,    -1,
      84,    -1,    86,    -1,    88,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    -1,    84,    -1,    86,    -1,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   142,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,   151,   152,     8,
       9,    10,    -1,    12,    13,    -1,    -1,    16,    17,    -1,
      19,    20,    21,    -1,    23,    24,    25,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    -1,    35,    -1,    -1,    -1,
     142,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     152,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    -1,    88,
      -1,    -1,    91,    92,    93,    94,    95,    96,    -1,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,     3,
       4,    -1,    -1,    -1,     8,     9,    10,    -1,    12,    13,
      -1,    -1,    16,    17,    -1,    19,    20,    21,    -1,    23,
      24,    25,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    35,    -1,     3,     4,    -1,    40,    -1,     8,     9,
      10,    -1,    12,    13,    -1,    49,    16,    17,    -1,    19,
      20,    21,    -1,    23,    24,    25,    26,    -1,    28,    -1,
      30,    31,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,
      94,    95,    96,    -1,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    93,    94,    95,    96,    -1,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,     3,     4,
      -1,    -1,    -1,     8,     9,    10,    -1,    12,    13,    -1,
      -1,    16,    17,    -1,    19,    20,    21,    -1,    23,    24,
      25,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,    -1,
      35,    -1,     3,     4,    -1,    40,    -1,     8,     9,    10,
      -1,    12,    13,    -1,    49,    16,    17,    -1,    19,    20,
      21,    -1,    23,    24,    25,    -1,    -1,    -1,    -1,    30,
      31,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,
      95,    96,    -1,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    95,    96,    -1,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,     3,     4,    -1,
      -1,    -1,     8,     9,    10,    -1,    12,    13,    -1,    -1,
      16,    17,    -1,    19,    20,    21,    -1,    23,    24,    25,
      -1,    -1,    -1,    -1,    30,    31,     3,     4,    -1,    35,
      -1,     8,     9,    10,    40,    12,    13,    -1,    -1,    16,
      17,    -1,    19,    20,    21,    -1,    23,    24,    25,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    95,
      96,    -1,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    94,    95,    96,
      -1,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,     3,     4,    -1,    -1,    -1,     8,     9,    10,    -1,
      12,    13,    -1,    -1,    16,    17,    -1,    19,    20,    21,
      -1,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,
       3,     4,    -1,    35,    -1,     8,     9,    10,    40,    12,
      13,    -1,    -1,    16,    17,    -1,    19,    20,    21,    -1,
      23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    94,    95,    96,    -1,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    94,    95,    96,    -1,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,     3,     4,    -1,    -1,    -1,
       8,     9,    10,    -1,    12,    13,    -1,    -1,    16,    17,
      -1,    19,    20,    21,    -1,    23,    24,    25,    -1,    -1,
      -1,    -1,    30,    31,     3,     4,    -1,    35,    -1,     8,
      -1,    -1,    40,    12,    13,    -1,    -1,    16,    17,    -1,
      19,    -1,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    94,    95,    96,    -1,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,    -1,    -1,     8,    95,    96,    97,    12,
      13,    -1,    -1,    16,    17,    -1,    19,    -1,    -1,    -1,
      23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    -1,    88,     3,     4,    91,    92,
      -1,     8,    95,    96,    -1,    12,    13,    -1,    -1,    16,
      17,    -1,    19,    -1,    -1,    -1,    23,    24,    25,    -1,
      -1,     3,     4,    30,    31,    -1,     8,    -1,    -1,    -1,
      12,    13,    -1,    40,    16,    17,    -1,    19,    -1,    -1,
      -1,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    66,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    93,    -1,    95,    96,
      -1,    -1,    -1,    -1,    76,    -1,     3,     4,    80,    -1,
      -1,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    16,
      17,    93,    19,    95,    96,    -1,    23,    24,    25,    -1,
      -1,    -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    93,    -1,    95,    96
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    16,    17,    19,    20,    21,    22,    23,    24,
      25,    26,    28,    30,    31,    35,    40,    41,    42,    43,
      44,    45,    47,    48,    49,    68,    69,    74,    75,    76,
      80,    82,    83,    86,    88,    90,    91,    92,    93,    94,
      95,    96,    97,    98,   100,   101,   102,   103,   104,   105,
     106,   107,   109,   114,   120,   121,   122,   123,   126,   149,
     154,   156,   157,   159,   163,   201,   209,   211,   215,   223,
     226,   230,   233,   235,   239,   241,   249,   256,   258,   261,
     264,   272,   274,   276,   278,   283,   292,   297,   312,   314,
     316,   318,   337,   345,   347,   351,   353,   355,   357,   359,
     361,   368,   370,   372,   375,   381,   385,   402,   410,   440,
     444,   449,   456,   459,   461,   463,   467,   474,   475,   478,
     483,   498,   505,   574,   581,   582,   606,   608,   618,   636,
     638,   645,   659,   661,   667,   687,   693,   697,   723,   728,
     735,   737,   740,   846,   317,   319,   738,   742,   316,   743,
     212,   729,    10,    16,    17,    30,    35,    94,   105,   211,
     283,   297,   316,   337,   381,   402,   410,   440,   444,   474,
     574,   661,   693,   697,   723,    22,    23,   283,   316,   293,
     294,    19,   151,   283,   316,   320,   321,   720,   721,   723,
      16,    19,    30,    49,    94,   283,   297,   302,   316,   480,
     498,    40,   283,   694,   283,   695,   283,   696,   316,   320,
      72,   283,   312,    40,   283,    86,   279,   280,    91,   283,
     505,   292,   295,   149,   223,   276,   443,   307,    72,    72,
      72,    72,   223,    82,   149,   283,   740,   822,    40,    86,
       5,    16,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    88,
      91,    92,   297,   410,   444,   467,   503,   574,   697,   740,
     740,     7,   740,   740,   505,   740,   316,   740,   740,   278,
     410,   740,   830,   834,    80,    84,   834,   838,   839,   841,
     843,   845,   199,    86,   297,   740,    88,   740,   445,   385,
     402,   448,   474,   483,   574,   580,   697,   723,   303,   288,
     502,   210,   441,   442,   577,   576,   578,    19,    20,    21,
     105,   297,   579,   687,   693,   697,   446,   447,    38,    39,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
      86,    86,    86,   163,    86,   820,   834,   150,   156,   278,
     740,   830,   834,     0,    32,    33,    34,   155,   731,   158,
     163,   160,   190,   200,    86,    90,   197,   290,   192,   191,
     117,   175,   176,   177,   178,   179,    46,   193,   244,   202,
     203,   204,   205,   206,   207,   208,   173,   223,    26,    28,
     277,    30,    40,    72,   149,   298,   745,   301,    30,    40,
      66,    76,    80,    93,   297,   429,   430,   431,   500,   287,
     291,    30,    72,    86,   284,   727,   286,    90,   418,   431,
     166,   167,   189,   168,   169,    90,    90,   194,   196,   195,
     165,   164,    85,    90,    90,    84,    86,    88,    90,   149,
     151,   395,    40,    86,    94,    97,   283,   423,   480,   723,
      94,   375,   381,   440,   575,   723,   375,   402,   410,    90,
      93,   223,   187,   181,   182,   828,     8,    84,    93,    96,
      97,   108,   584,    90,   404,   415,   180,    47,    84,    90,
     223,   600,    86,    72,   499,    49,    82,    94,   283,   410,
     449,   483,   574,   583,   608,   618,   638,   645,   697,   723,
     385,   402,   183,   184,    84,    90,   108,   151,   600,   627,
     628,   185,   186,    84,    90,   223,   584,   600,   170,    90,
     416,   431,   171,   172,   151,   297,   673,   674,   720,    11,
     361,   402,   449,   483,   608,   618,   638,   645,   661,   687,
     283,   316,   375,   449,   467,   483,   574,   618,   645,   697,
       9,    86,   724,   188,     5,   741,    40,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    84,
      86,    88,    90,   142,   152,   503,   174,   829,    16,    19,
     316,   720,   283,    30,   358,   360,    40,    97,   283,   402,
      90,   410,   316,   720,   410,   467,   283,    90,    84,   316,
     720,   297,   304,   151,   322,   149,   316,   722,   297,   480,
      30,    30,    40,    70,    86,   309,   429,   429,   429,    84,
     149,   698,   315,   308,   305,   740,    86,   299,   501,   296,
     736,   410,   410,   410,   410,   244,   821,    86,   410,   740,
     316,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   541,   542,   517,    73,   518,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   540,    87,    89,
      88,   545,    88,   547,    76,   549,    86,   410,   528,    19,
      23,   661,   758,   760,   744,   752,   755,   757,   756,    86,
     753,   754,    26,    28,   830,   834,    86,    87,    85,   835,
      85,   836,    87,   842,   844,   840,    89,   740,   813,   814,
      89,   817,   394,   489,   697,   410,    90,   692,   720,    18,
     273,   316,   316,     5,    37,     5,    37,    18,   316,     9,
     316,   269,    18,   271,   385,   740,   246,   278,   381,   385,
     402,   740,   830,   385,   740,   121,   740,   819,   751,   150,
      85,   150,    85,   150,   151,   151,   151,   162,   161,    87,
     740,   198,   163,    86,   243,   225,   281,   282,    49,   283,
     316,   505,   289,   297,   410,   496,   566,   567,   571,   740,
     838,   746,   283,   297,   310,   435,   433,   434,   432,    30,
     411,    66,    76,    80,    93,    82,   316,   571,   276,   385,
     402,   410,   467,   554,   555,   557,   346,   419,   356,   354,
     429,   373,   377,   740,    87,   297,   834,    89,   740,   376,
     838,   740,   393,   421,    76,    80,   720,   480,   425,   424,
     403,   485,   480,   379,    90,   380,   409,   420,   457,   453,
     458,   596,     7,   585,   586,   587,   588,    84,    93,    96,
      97,   108,   473,   479,    86,    92,   125,   460,   462,   495,
     838,   571,   316,    30,    86,   452,   492,   616,   620,   644,
     649,   697,    85,    85,    92,   125,   607,   625,   283,   631,
     624,    85,   223,     7,    92,   125,   637,   639,   650,   654,
     660,   417,    32,    33,    34,   102,   679,   680,   684,   685,
      90,    85,   276,   656,   657,   283,   366,   408,   455,   491,
     617,   621,   643,   666,   690,    30,   378,   454,   472,   490,
     618,   645,   626,   648,   574,   618,   723,   730,     7,   316,
     739,   827,   740,   740,   740,   740,   740,   740,   740,   740,
     740,   740,   740,   740,   740,   740,   740,   740,   740,   740,
     759,   761,    82,   498,   498,   740,   740,   740,   740,   740,
     740,   740,   740,   740,   740,   740,   838,    89,   740,   847,
      82,   498,   740,   740,   720,   316,   320,   283,   352,   283,
      90,   367,   410,   475,   476,   661,    90,   151,   316,   149,
     297,   332,   333,   149,   151,    76,    70,   410,   554,   412,
     413,   414,   283,   668,    19,    24,   410,   474,   700,   701,
     704,   306,    87,   740,    73,    73,    73,    73,   242,   410,
     740,    87,    87,   552,   504,   543,   544,    89,    89,   550,
      95,   655,   655,   833,   837,   740,   740,   740,   812,    86,
     464,   465,    87,   740,   691,   283,   275,     5,     6,     7,
      18,   251,   316,   257,   259,   260,   262,   263,   265,   266,
     268,   267,   270,    87,    87,    90,   740,   830,    90,    90,
     151,   247,   248,    87,    87,    86,    87,   224,   150,   747,
     150,   749,   732,   733,   734,   213,    87,   229,   410,   410,
     285,    30,   551,   720,   568,   569,   572,    73,    85,   570,
     150,   300,   431,   439,   437,   438,   436,   316,   610,    73,
     557,   558,   560,    84,    88,   561,   562,    85,    87,   316,
     396,   392,    66,    76,    80,    87,    87,   406,    89,   150,
     407,    76,   316,   316,    76,   283,   486,   484,   374,   589,
       7,   591,   592,   593,   594,   283,   602,   603,   493,   494,
      87,    73,    49,   720,   429,   429,   622,   623,    86,   149,
     629,   631,   609,   651,   652,   653,   681,   682,   683,   686,
     684,   679,   688,   679,   684,   658,   149,    90,    97,   670,
     671,    87,    87,   776,   777,   778,   779,   780,   781,   782,
     783,   784,   786,   787,   788,   789,   790,   791,   792,   793,
     795,   283,   498,   797,   798,   773,   774,   762,   763,   764,
     766,   767,   771,   768,   770,   772,    87,   802,    89,   498,
     796,   151,   785,   316,   149,   371,    90,   720,    90,    90,
      90,   350,   297,   149,   151,   332,    90,    85,    99,   150,
     201,   211,   276,   316,   323,   330,   332,   297,   410,   487,
      87,    90,   156,   316,   320,   316,   320,    84,   316,   713,
      84,   711,    73,    85,   702,   311,    87,    86,    86,    86,
      86,    87,    87,   823,   824,   546,   548,    87,    87,   807,
     831,   832,   554,    70,   223,   740,   818,   253,   254,   252,
     255,   250,   163,   163,   246,   246,   246,   740,   163,   163,
     740,   149,   748,   750,   214,   320,    86,    82,   316,    86,
     313,   566,   806,   422,   640,    86,    30,   563,   740,    89,
     740,   557,   619,    86,   395,   399,   400,   316,    76,    80,
     316,   316,   391,   397,   405,   398,   316,    87,    87,   320,
      30,   590,   595,   604,    85,    87,   804,   553,    76,   283,
     316,   316,    87,   834,   150,   834,   630,   297,   297,   684,
     679,   664,   689,   672,   673,   726,   725,   794,    86,   800,
     765,   769,   803,   801,   799,   740,   332,   362,    86,   363,
     364,   365,    90,   332,   297,   150,   348,   323,   336,   331,
     338,   327,   328,   326,    84,   324,   334,   329,   150,   149,
     488,   481,   584,   369,   150,    73,    85,    84,   707,    73,
      84,    85,    84,   705,   740,    84,   709,   740,   699,   704,
     740,   740,   740,   740,   740,   825,   826,   450,   646,    87,
     410,   815,   228,   227,    90,    90,    90,    87,   232,   231,
      87,   217,   218,   278,    87,   655,   316,   612,   554,   573,
      86,   554,    82,   316,   559,   565,    89,   556,   401,   384,
     390,   316,   316,   386,   389,    87,   427,   426,    87,    76,
     283,   601,   320,    30,   399,   399,   633,    87,   635,   150,
     675,   677,   297,   297,   156,   656,    87,   775,   150,   554,
     349,   150,   149,   340,   335,   740,   341,   332,   482,   669,
     719,   718,   410,   717,   716,   715,   410,   714,   740,   712,
     703,   816,    87,    87,    87,    87,   647,   466,   223,   246,
     246,   246,   163,   234,   124,   125,   150,   278,   217,   223,
      87,   641,    86,    87,    87,    87,   316,   614,   564,   387,
     388,   428,    86,   320,   605,    87,    76,   382,   383,   632,
     634,   676,   678,   150,   149,   805,   316,    87,   343,   332,
     325,   150,   708,   706,   710,   808,   809,   810,   811,    87,
      87,    87,   240,   740,   151,   216,   222,   221,   245,   451,
      86,   554,   497,   223,   597,   598,   600,   642,    86,   554,
      87,    86,   320,   665,   662,   344,   477,   150,   339,   163,
     163,   163,   151,   156,    87,    87,   627,   599,    86,   554,
      87,    86,   554,    87,   156,   342,   236,   238,   237,   156,
     220,   223,   597,   223,    87,    87,   471,   554,    87,    86,
     150,   219,   627,   611,   223,   597,    87,   470,   554,   663,
     223,   627,   469,    87,   613,   223,   468,   615
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   153,   155,   154,   157,   156,   158,   156,   160,   159,
     161,   159,   162,   159,   164,   163,   165,   163,   166,   163,
     167,   163,   168,   163,   169,   163,   170,   163,   171,   163,
     172,   163,   173,   163,   174,   163,   175,   163,   176,   163,
     177,   163,   178,   163,   179,   163,   180,   163,   181,   163,
     182,   163,   183,   163,   184,   163,   185,   163,   186,   163,
     187,   163,   188,   163,   189,   163,   190,   163,   191,   163,
     192,   163,   193,   163,   194,   163,   195,   163,   196,   163,
     197,   163,   198,   163,   199,   163,   200,   163,   202,   201,
     203,   201,   204,   201,   205,   201,   206,   201,   207,   201,
     208,   201,   210,   209,   212,   211,   213,   211,   214,   211,
     216,   215,   218,   217,   219,   217,   220,   217,   221,   217,
     222,   217,   224,   223,   225,   223,   227,   226,   228,   226,
     229,   226,   231,   230,   232,   230,   234,   233,   236,   235,
     237,   235,   238,   235,   240,   239,   242,   241,   243,   241,
     245,   244,   246,   247,   246,   248,   246,   250,   249,   251,
     249,   252,   249,   253,   249,   254,   249,   255,   249,   257,
     256,   259,   258,   260,   258,   262,   261,   263,   261,   265,
     264,   266,   264,   267,   264,   268,   264,   269,   264,   270,
     264,   271,   264,   273,   272,   275,   274,   277,   276,   279,
     278,   280,   278,   281,   278,   282,   278,   284,   283,   285,
     283,   286,   283,   287,   283,   288,   283,   289,   283,   290,
     283,   291,   283,   293,   292,   294,   292,   295,   292,   296,
     292,   298,   297,   299,   297,   300,   297,   301,   297,   302,
     297,   303,   297,   304,   297,   305,   306,   297,   307,   297,
     308,   297,   309,   297,   310,   297,   311,   297,   313,   312,
     315,   314,   317,   316,   319,   318,   321,   320,   322,   320,
     324,   323,   325,   323,   326,   323,   327,   323,   328,   323,
     329,   323,   331,   330,   333,   332,   334,   332,   335,   332,
     336,   332,   338,   337,   339,   337,   340,   337,   341,   337,
     342,   337,   343,   337,   344,   337,   346,   345,   348,   347,
     349,   347,   350,   347,   352,   351,   354,   353,   356,   355,
     358,   357,   360,   359,   362,   361,   363,   361,   364,   361,
     365,   361,   366,   361,   367,   361,   369,   368,   371,   370,
     373,   372,   374,   372,   376,   375,   377,   375,   378,   375,
     379,   375,   380,   375,   382,   381,   383,   381,   384,   381,
     386,   385,   387,   385,   388,   385,   389,   385,   390,   385,
     391,   385,   392,   385,   393,   385,   394,   385,   396,   395,
     397,   395,   398,   395,   400,   399,   401,   399,   403,   402,
     404,   402,   405,   402,   406,   402,   407,   402,   408,   402,
     409,   402,   411,   410,   412,   410,   413,   410,   414,   410,
     415,   410,   416,   410,   417,   410,   418,   410,   419,   410,
     420,   410,   421,   410,   422,   410,   424,   423,   425,   423,
     426,   423,   427,   423,   428,   423,   430,   429,   429,   432,
     431,   433,   431,   434,   431,   435,   431,   436,   431,   437,
     431,   438,   431,   439,   431,   441,   440,   442,   440,   443,
     440,   445,   444,   446,   444,   447,   444,   448,   444,   450,
     449,   451,   449,   452,   449,   453,   449,   454,   449,   455,
     449,   457,   456,   458,   456,   460,   459,   462,   461,   463,
     463,   465,   464,   466,   464,   468,   467,   469,   467,   470,
     467,   471,   467,   472,   467,   473,   467,   474,   475,   477,
     476,   479,   478,   481,   480,   482,   480,   484,   483,   485,
     483,   486,   483,   487,   483,   488,   483,   489,   483,   490,
     483,   491,   483,   492,   483,   493,   483,   494,   483,   495,
     483,   497,   496,   499,   498,   500,   498,   501,   498,   502,
     498,   504,   503,   506,   505,   507,   505,   508,   505,   509,
     505,   510,   505,   511,   505,   512,   505,   513,   505,   514,
     505,   515,   505,   516,   505,   517,   505,   518,   505,   519,
     505,   520,   505,   521,   505,   522,   505,   523,   505,   524,
     505,   525,   505,   526,   505,   527,   505,   528,   505,   529,
     505,   530,   505,   531,   505,   532,   505,   533,   505,   534,
     505,   535,   505,   536,   505,   537,   505,   538,   505,   539,
     505,   540,   505,   541,   505,   542,   505,   543,   505,   544,
     505,   545,   505,   546,   505,   547,   505,   548,   505,   549,
     505,   550,   505,   551,   505,   552,   505,   553,   505,   555,
     554,   554,   556,   554,   558,   557,   559,   557,   560,   557,
     561,   557,   562,   557,   563,   557,   564,   557,   565,   557,
     567,   566,   568,   566,   569,   566,   570,   566,   572,   571,
     573,   571,   575,   574,   576,   574,   577,   574,   578,   574,
     579,   574,   580,   574,   582,   581,   583,   581,   585,   584,
     586,   584,   587,   584,   588,   584,   589,   590,   584,   591,
     584,   592,   584,   593,   584,   594,   584,   595,   584,   596,
     584,   598,   597,   599,   597,   601,   600,   603,   602,   604,
     602,   605,   602,   607,   606,   609,   608,   610,   611,   608,
     612,   613,   608,   614,   615,   608,   616,   608,   617,   608,
     619,   618,   620,   618,   621,   618,   622,   618,   623,   618,
     624,   618,   625,   618,   626,   618,   628,   627,   629,   627,
     630,   627,   632,   631,   633,   631,   634,   631,   635,   631,
     637,   636,   639,   638,   640,   638,   641,   638,   642,   638,
     643,   638,   644,   638,   646,   647,   645,   648,   645,   649,
     645,   650,   645,   651,   645,   652,   645,   653,   645,   654,
     645,   655,   655,   657,   656,   658,   656,   660,   659,   662,
     663,   661,   664,   665,   661,   666,   661,   668,   669,   667,
     671,   670,   672,   670,   674,   673,   675,   673,   676,   673,
     677,   673,   678,   673,   680,   679,   681,   679,   682,   679,
     683,   679,   685,   684,   686,   684,   688,   687,   689,   687,
     690,   687,   691,   687,   692,   687,   694,   693,   695,   693,
     696,   693,   698,   699,   697,   701,   700,   702,   700,   703,
     700,   705,   704,   706,   704,   707,   704,   708,   704,   709,
     704,   710,   704,   711,   704,   712,   704,   713,   704,   714,
     704,   715,   704,   716,   704,   717,   704,   718,   704,   719,
     704,   721,   720,   722,   720,   724,   723,   725,   723,   726,
     723,   727,   723,   729,   728,   730,   728,   732,   731,   733,
     731,   734,   731,   736,   735,   738,   737,   739,   737,   741,
     740,   742,   740,   743,   740,   744,   740,   745,   746,   740,
     747,   740,   748,   740,   749,   740,   750,   740,   751,   740,
     752,   740,   753,   740,   754,   740,   755,   740,   756,   740,
     757,   740,   758,   740,   759,   740,   760,   740,   761,   740,
     762,   740,   763,   740,   764,   765,   740,   766,   740,   767,
     740,   768,   769,   740,   770,   740,   771,   740,   772,   740,
     773,   740,   774,   740,   775,   740,   776,   740,   777,   740,
     778,   740,   779,   740,   780,   740,   781,   740,   782,   740,
     783,   740,   784,   740,   785,   740,   786,   740,   787,   740,
     788,   740,   789,   740,   790,   740,   791,   740,   792,   740,
     793,   794,   740,   795,   740,   796,   740,   797,   740,   798,
     740,   799,   740,   800,   740,   801,   740,   802,   740,   803,
     740,   804,   740,   805,   740,   806,   740,   807,   740,   808,
     740,   809,   740,   810,   740,   811,   740,   812,   740,   813,
     740,   814,   740,   815,   740,   816,   740,   817,   740,   818,
     740,   819,   740,   820,   740,   821,   740,   822,   740,   823,
     740,   824,   740,   825,   740,   826,   740,   827,   740,   828,
     740,   829,   740,   831,   830,   832,   830,   833,   830,   835,
     834,   836,   834,   837,   834,   839,   838,   840,   838,   842,
     841,   844,   843,   845,   845,   845,   847,   846
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     1,     0,     2,     0,     2,
       0,     3,     0,     3,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     3,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     4,     0,     5,
       0,     8,     0,     1,     0,     6,     0,     5,     0,     3,
       0,     3,     0,     4,     0,     3,     0,     6,     0,     6,
       0,     4,     0,     6,     0,     6,     0,     7,     0,    10,
       0,    10,     0,    10,     0,     8,     0,     4,     0,     3,
       0,     7,     0,     0,     2,     0,     2,     0,     5,     0,
       4,     0,     5,     0,     5,     0,     5,     0,     5,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     3,     0,
       4,     0,     3,     0,     3,     0,     4,     0,     2,     0,
       2,     0,     2,     0,     3,     0,     3,     0,     2,     0,
       4,     0,     2,     0,     2,     0,     2,     0,     3,     0,
       2,     0,     2,     0,     2,     0,     2,     0,     2,     0,
       3,     0,     2,     0,     3,     0,     4,     0,     2,     0,
       2,     0,     2,     0,     3,     0,     0,     4,     0,     2,
       0,     3,     0,     3,     0,     3,     0,     5,     0,     5,
       0,     3,     0,     2,     0,     2,     0,     1,     0,     2,
       0,     2,     0,     4,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     1,     0,     3,     0,     4,
       0,     3,     0,     6,     0,     9,     0,     7,     0,     7,
       0,    10,     0,     8,     0,     9,     0,     3,     0,     6,
       0,     7,     0,     5,     0,     4,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     6,     0,     6,     0,     6,
       0,     6,     0,     3,     0,     4,     0,     6,     0,     5,
       0,     3,     0,     4,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     7,     0,     7,     0,     6,
       0,     6,     0,     7,     0,     7,     0,     6,     0,     6,
       0,     5,     0,     4,     0,     3,     0,     3,     0,     3,
       0,     4,     0,     4,     0,     1,     0,     2,     0,     3,
       0,     2,     0,     5,     0,     4,     0,     4,     0,     3,
       0,     3,     0,     3,     0,     4,     0,     4,     0,     4,
       0,     2,     0,     2,     0,     3,     0,     2,     0,     3,
       0,     3,     0,     3,     0,     5,     0,     2,     0,     2,
       0,     5,     0,     5,     0,     6,     0,     1,     1,     0,
       2,     0,     2,     0,     2,     0,     2,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     2,     0,     2,     0,
       2,     0,     2,     0,     2,     0,     2,     0,     2,     0,
       6,     0,     8,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     5,
       7,     0,     1,     0,     4,     0,    13,     0,    12,     0,
      11,     0,    10,     0,     3,     0,     3,     1,     1,     0,
       6,     0,     3,     0,     5,     0,     6,     0,     4,     0,
       3,     0,     4,     0,     5,     0,     6,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     4,     0,     4,     0,
       3,     0,     6,     0,     2,     0,     2,     0,     3,     0,
       2,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     4,     0,
       4,     0,     3,     0,     5,     0,     3,     0,     5,     0,
       3,     0,     4,     0,     4,     0,     4,     0,     5,     0,
       1,     1,     0,     4,     0,     2,     0,     4,     0,     2,
       0,     2,     0,     2,     0,     3,     0,     5,     0,     4,
       0,     1,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     4,     0,     2,     0,     2,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     1,     0,     2,     0,     2,
       0,     2,     0,     2,     0,     2,     0,     0,     4,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     4,     0,
       2,     0,     1,     0,     2,     0,     5,     0,     1,     0,
       2,     0,     4,     0,     3,     0,     4,     0,     0,    11,
       0,     0,    13,     0,     0,    14,     0,     3,     0,     3,
       0,     5,     0,     3,     0,     3,     0,     4,     0,     4,
       0,     3,     0,     3,     0,     3,     0,     1,     0,     3,
       0,     4,     0,     5,     0,     4,     0,     5,     0,     4,
       0,     3,     0,     3,     0,     8,     0,    10,     0,    11,
       0,     3,     0,     3,     0,     0,     7,     0,     3,     0,
       3,     0,     3,     0,     4,     0,     4,     0,     4,     0,
       3,     0,     1,     0,     1,     0,     2,     0,     3,     0,
       0,    11,     0,     0,     8,     0,     3,     0,     0,     7,
       0,     1,     0,     2,     0,     1,     0,     5,     0,     6,
       0,     5,     0,     6,     0,     1,     0,     2,     0,     2,
       0,     2,     0,     1,     0,     2,     0,     4,     0,     5,
       0,     3,     0,     4,     0,     3,     0,     2,     0,     2,
       0,     2,     0,     0,     6,     0,     1,     0,     2,     0,
       4,     0,     3,     0,     5,     0,     3,     0,     5,     0,
       3,     0,     5,     0,     2,     0,     4,     0,     2,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     1,     0,     2,     0,     2,     0,     5,     0,
       5,     0,     2,     0,     2,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     2,     0,     3,     0,
       2,     0,     2,     0,     2,     0,     3,     0,     0,     3,
       0,     4,     0,     5,     0,     4,     0,     5,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     4,     0,     4,     0,     0,     5,     0,     4,     0,
       4,     0,     0,     5,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     0,     5,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     5,     0,     5,     0,     5,     0,     4,     0,
       5,     0,     5,     0,     7,     0,     5,     0,     5,     0,
       8,     0,     8,     0,     8,     0,     8,     0,     4,     0,
       3,     0,     3,     0,     6,     0,     7,     0,     3,     0,
       5,     0,     3,     0,     2,     0,     3,     0,     2,     0,
       5,     0,     5,     0,     6,     0,     6,     0,     3,     0,
       2,     0,     3,     0,     4,     0,     4,     0,     3,     0,
       2,     0,     2,     0,     3,     0,     1,     0,     2,     0,
       2,     0,     2,     1,     1,     1,     0,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 407 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 407 "parser.y" /* yacc.c:1646  */
    {
                    gProgUnit = (yyval.cppCompundObj) = (yyvsp[-1].cppCompundObj);
                    if (gProgUnit)
                      gProgUnit->compoundType(CppCompoundType::kCppFile);
                  }
#line 4622 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 414 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4628 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 414 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = nullptr;
                  }
#line 4636 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 417 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 417 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = (yyvsp[-1].cppCompundObj);
                  }
#line 4650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 422 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 422 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = newCompound(gAccessTypeStack.empty() ? gCurAccessType : gAccessTypeStack.top());
                    if ((yyvsp[-1].cppObj))
                    {
                      (yyval.cppCompundObj)->addMember((yyvsp[-1].cppObj));
                    } // Avoid 'comment-btyacc-constructs.sh' to act on this
                  }
#line 4668 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 429 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 429 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = ((yyvsp[-2].cppCompundObj) == 0) ? newCompound(gAccessTypeStack.empty() ? gCurAccessType : gAccessTypeStack.top()) : (yyvsp[-2].cppCompundObj);
                    if ((yyvsp[-1].cppObj))
                    {
                      (yyval.cppCompundObj)->addMember((yyvsp[-1].cppObj));
                    } // Avoid 'comment-btyacc-constructs.sh' to act on this
                  }
#line 4686 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 436 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 436 "parser.y" /* yacc.c:1646  */
    { (yyval.cppCompundObj) = (yyvsp[-2].cppCompundObj); gCurAccessType = (yyvsp[-1].objAccessType); }
#line 4698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 439 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 439 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppVarObj); }
#line 4710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 440 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4716 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 440 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppVarObjList); }
#line 4722 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 441 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4728 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 441 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppEnum); }
#line 4734 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 442 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 442 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppEnum); }
#line 4746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 443 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4752 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 443 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].typedefName); }
#line 4758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 444 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 444 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].typedefList); }
#line 4770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 445 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 445 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppCompundObj); }
#line 4782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 446 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4788 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 446 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppCompundObj); }
#line 4794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 447 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 447 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].fwdDeclObj); }
#line 4806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 448 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4812 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 448 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].docCommentObj); }
#line 4818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 449 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 449 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppExprObj); }
#line 4830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 450 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 450 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].ifBlock); }
#line 4842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 451 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4848 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 451 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].whileBlock); }
#line 4854 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 452 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 452 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].doWhileBlock); }
#line 4866 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 453 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4872 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 453 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].forBlock); }
#line 4878 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 454 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4884 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 454 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].forRangeBlock); }
#line 4890 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 455 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4896 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 455 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppFuncPointerObj); }
#line 4902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 456 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4908 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 456 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppFuncObj); }
#line 4914 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 457 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 457 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppFuncObj); }
#line 4926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 458 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4932 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 458 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppCtorObj); }
#line 4938 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 459 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 459 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppCtorObj); }
#line 4950 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 460 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4956 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 460 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppDtorObj); }
#line 4962 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 461 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4968 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 461 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppDtorObj); }
#line 4974 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 462 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4980 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 462 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppTypeConverter); }
#line 4986 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 463 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 4992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 463 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppCompundObj); }
#line 4998 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 464 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 464 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppFuncPointerObj); }
#line 5010 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 465 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5016 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 465 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppObj); }
#line 5022 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 466 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5028 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 466 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].cppCompundObj); }
#line 5034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 467 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5040 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 467 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].switchBlock); }
#line 5046 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 468 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 468 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].tryBlock); }
#line 5058 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 469 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 469 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].usingDecl); }
#line 5070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 470 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5076 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 470 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].usingNamespaceDecl); }
#line 5082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 471 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 471 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].namespaceAlias); }
#line 5094 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 472 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 472 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = new CppMacroCall((yyvsp[-1].str), gCurAccessType); }
#line 5106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 473 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5112 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 473 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = new CppMacroCall(mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)), gCurAccessType); }
#line 5118 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 474 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5124 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 474 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = nullptr; }
#line 5130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 475 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5136 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 475 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].asmBlock); }
#line 5142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 478 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5148 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 478 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].hashDefine); }
#line 5154 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 479 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5160 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 479 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].hashUndef); }
#line 5166 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 480 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5172 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 480 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].hashInclude); }
#line 5178 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 481 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5184 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 481 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].hashImport); }
#line 5190 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 482 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 482 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].hashIf); }
#line 5202 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 483 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5208 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 483 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].hashError); }
#line 5214 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 484 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5220 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 484 "parser.y" /* yacc.c:1646  */
    { (yyval.cppObj) = (yyvsp[-1].hashPragma); }
#line 5226 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 487 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5232 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 487 "parser.y" /* yacc.c:1646  */
    { (yyval.asmBlock) = new CppAsmBlock((yyvsp[-1].str)); }
#line 5238 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 490 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 5244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 491 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.str) = (yyvsp[-1].str);
                  }
#line 5252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 494 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5258 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 494 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str));
                  }
#line 5266 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 497 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 497 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str));
                    delete (yyvsp[-2].cppExprObj);
                  }
#line 5281 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 503 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 503 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.switchBlock) = new CppSwitchBlock((yyvsp[-5].cppExprObj), (yyvsp[-2].switchBody));
                  }
#line 5295 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 508 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5301 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 508 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.switchBody) = new CppSwitchBody;
                  }
#line 5309 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 511 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5315 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 511 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.switchBody) = (yyvsp[-5].switchBody);
                    (yyval.switchBody)->emplace_back((yyvsp[-3].cppExprObj), (yyvsp[-1].cppCompundObj));
                  }
#line 5324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 515 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 515 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.switchBody) = (yyvsp[-4].switchBody);
                    (yyval.switchBody)->emplace_back(nullptr, (yyvsp[-1].cppCompundObj));
                  }
#line 5339 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 519 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5345 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 519 "parser.y" /* yacc.c:1646  */
    { (yyval.switchBody) = (yyvsp[-1].switchBody); }
#line 5351 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 520 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 520 "parser.y" /* yacc.c:1646  */
    { (yyval.switchBody) = (yyvsp[-2].switchBody); }
#line 5363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 523 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5369 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 523 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = (yyvsp[-2].cppCompundObj);
                    if ((yyval.cppCompundObj) == nullptr)
                      (yyval.cppCompundObj) = newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock);
                    else
                      (yyval.cppCompundObj)->compoundType(CppCompoundType::kBlock);
                  }
#line 5381 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 530 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5387 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 530 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = (yyvsp[-1].cppCompundObj);
                  }
#line 5395 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 535 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 535 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.ifBlock) = new CppIfBlock((yyvsp[-3].cppExprObj), (yyvsp[-1].cppObj));
                  }
#line 5409 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 538 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5415 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 538 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.ifBlock) = new CppIfBlock((yyvsp[-3].cppVarObj), (yyvsp[-1].cppObj));
                  }
#line 5423 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 541 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5429 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 541 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.ifBlock) = (yyvsp[-3].ifBlock);
                    (yyval.ifBlock)->elsePart((yyvsp[-1].cppObj));
                  }
#line 5438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 547 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 547 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.whileBlock) = new CppWhileBlock((yyvsp[-3].cppExprObj), (yyvsp[-1].cppObj));
                  }
#line 5452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 550 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 550 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.whileBlock) = new CppWhileBlock((yyvsp[-3].cppVarObj), (yyvsp[-1].cppObj));
                  }
#line 5466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 555 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 555 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.doWhileBlock) = new CppDoWhileBlock((yyvsp[-2].cppExprObj), (yyvsp[-5].cppObj));
                  }
#line 5480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 560 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 560 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forBlock) = new CppForBlock((yyvsp[-7].cppExprObj), (yyvsp[-5].cppExprObj), (yyvsp[-3].cppExprObj), (yyvsp[-1].cppObj));
                  }
#line 5494 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 563 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5500 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 563 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forBlock) = new CppForBlock((yyvsp[-7].cppVarObj), (yyvsp[-5].cppExprObj), (yyvsp[-3].cppExprObj), (yyvsp[-1].cppObj));
                  }
#line 5508 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 566 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 566 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forBlock) = new CppForBlock((yyvsp[-7].cppVarObjList), (yyvsp[-5].cppExprObj), (yyvsp[-3].cppExprObj), (yyvsp[-1].cppObj));
                  }
#line 5522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 571 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 571 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forRangeBlock) = new CppRangeForBlock((yyvsp[-5].cppVarObj), (yyvsp[-3].cppExprObj), (yyvsp[-1].cppObj));
                  }
#line 5536 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 576 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 576 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.tryBlock) = new CppTryBlock((yyvsp[-2].cppCompundObj), (yyvsp[-1].catchBlock));
                  }
#line 5550 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 579 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5556 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 579 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.tryBlock) = (yyvsp[-2].tryBlock);
                    (yyval.tryBlock)->addCatchBlock((yyvsp[-1].catchBlock));
                  }
#line 5565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 585 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5571 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 585 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.catchBlock) = new CppCatchBlock{CppVarTypePtr((yyvsp[-4].cppVarType)), (yyvsp[-3].str), CppCompoundPtr((yyvsp[-1].cppCompundObj))};
                  }
#line 5579 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 590 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppExprObj) = nullptr;
                  }
#line 5587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 593 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 593 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppExprObj) = (yyvsp[-1].cppExprObj);
                  }
#line 5601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 596 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 596 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppExprObj) = (yyvsp[-1].cppExprObj);
                  }
#line 5615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 601 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5621 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 601 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.hashDefine) = new CppDefine(CppDefine::kRename, (yyvsp[-2].str), (yyvsp[-1].str));
                  }
#line 5629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 604 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 604 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.hashDefine) = new CppDefine(CppDefine::kRename, (yyvsp[-1].str));
                  }
#line 5643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 607 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 607 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.hashDefine) = new CppDefine(CppDefine::kConstNumDef, (yyvsp[-2].str), (yyvsp[-1].str));
                  }
#line 5657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 610 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 610 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.hashDefine) = new CppDefine(CppDefine::kConstStrDef, (yyvsp[-2].str), (yyvsp[-1].str));
                  }
#line 5671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 613 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 613 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.hashDefine) = new CppDefine(CppDefine::kConstCharDef, (yyvsp[-2].str), (yyvsp[-1].str));
                  }
#line 5685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 616 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5691 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 616 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.hashDefine) = new CppDefine(CppDefine::kComplexMacro, (yyvsp[-2].str), (yyvsp[-1].str));
                  }
#line 5699 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 621 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5705 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 621 "parser.y" /* yacc.c:1646  */
    { (yyval.hashUndef) = new CppUndef((yyvsp[-1].str)); }
#line 5711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 624 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 624 "parser.y" /* yacc.c:1646  */
    { (yyval.hashInclude) = new CppInclude((std::string) (yyvsp[-1].str)); }
#line 5723 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 625 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 625 "parser.y" /* yacc.c:1646  */
    { (yyval.hashInclude) = new CppInclude((std::string) (yyvsp[-1].str)); }
#line 5735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 628 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5741 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 628 "parser.y" /* yacc.c:1646  */
    { (yyval.hashImport) = new CppImport((std::string) (yyvsp[-1].str)); }
#line 5747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 629 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5753 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 629 "parser.y" /* yacc.c:1646  */
    { (yyval.hashImport) = new CppImport((std::string) (yyvsp[-1].str)); }
#line 5759 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 632 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5765 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 632 "parser.y" /* yacc.c:1646  */
    { (yyval.hashIf) = new CppHashIf(CppHashIf::kIf,      (yyvsp[-1].str)); }
#line 5771 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 633 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5777 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 633 "parser.y" /* yacc.c:1646  */
    { (yyval.hashIf) = new CppHashIf(CppHashIf::kIfDef,   (yyvsp[-1].str)); }
#line 5783 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 634 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5789 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 634 "parser.y" /* yacc.c:1646  */
    { (yyval.hashIf) = new CppHashIf(CppHashIf::kIfNDef,  (yyvsp[-1].str)); }
#line 5795 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 635 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 635 "parser.y" /* yacc.c:1646  */
    { (yyval.hashIf) = new CppHashIf(CppHashIf::kIfNDef,  (yyvsp[-1].str)); }
#line 5807 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 636 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5813 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 636 "parser.y" /* yacc.c:1646  */
    { (yyval.hashIf) = new CppHashIf(CppHashIf::kElse       ); }
#line 5819 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 637 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5825 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 637 "parser.y" /* yacc.c:1646  */
    { (yyval.hashIf) = new CppHashIf(CppHashIf::kElIf,    (yyvsp[-1].str)); }
#line 5831 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 638 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 638 "parser.y" /* yacc.c:1646  */
    { (yyval.hashIf) = new CppHashIf(CppHashIf::kEndIf      ); }
#line 5843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 641 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5849 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 641 "parser.y" /* yacc.c:1646  */
    { (yyval.hashError) = new CppHashError((yyvsp[-1].str)); }
#line 5855 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 644 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 644 "parser.y" /* yacc.c:1646  */
    { (yyval.hashPragma) = new CppPragma((yyvsp[-1].str)); }
#line 5867 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 647 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5873 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 647 "parser.y" /* yacc.c:1646  */
    { (yyval.docCommentObj) = new CppDocComment((std::string) (yyvsp[-1].str), gCurAccessType); }
#line 5879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 650 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 650 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 5891 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 651 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 651 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 5903 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 652 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5909 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 652 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 5915 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 653 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5921 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 653 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 5927 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 656 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5933 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 656 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 5939 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 657 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5945 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 657 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 5951 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 658 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5957 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 658 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 5963 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 659 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5969 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 659 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 5975 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 660 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5981 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 660 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); /* override is not a reserved keyword */ }
#line 5987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 661 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 5993 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 661 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 5999 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 662 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6005 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 662 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6011 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 221:
#line 663 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6017 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 222:
#line 663 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6023 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 223:
#line 666 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6029 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 224:
#line 666 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6035 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 225:
#line 667 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6041 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 226:
#line 667 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6047 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 227:
#line 668 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6053 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 228:
#line 668 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6059 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 229:
#line 669 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6065 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 230:
#line 669 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 6071 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 231:
#line 672 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6077 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 232:
#line 672 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6083 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 233:
#line 673 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6089 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 234:
#line 673 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 6095 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 235:
#line 674 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6101 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 236:
#line 674 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 6107 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 237:
#line 675 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6113 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 238:
#line 675 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6119 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 239:
#line 676 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6125 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 240:
#line 676 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6131 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 241:
#line 677 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 242:
#line 677 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 243:
#line 678 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6149 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 244:
#line 678 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 6155 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 245:
#line 679 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if (gTemplateParamStart == $1.sz)
                      ZZERROR;
                    else
                      ZZLOG;
                  ] ToYacc*/}
#line 6166 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 246:
#line 684 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6172 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 247:
#line 684 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-2].str)); }
#line 6178 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 248:
#line 685 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6184 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 249:
#line 685 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6190 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 250:
#line 686 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 251:
#line 686 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 6202 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 252:
#line 687 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6208 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 253:
#line 687 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 6214 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 254:
#line 688 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6220 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 255:
#line 688 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 6226 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 256:
#line 689 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6232 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 257:
#line 689 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); delete (yyvsp[-2].cppExprObj); }
#line 6238 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 258:
#line 692 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 259:
#line 692 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 6250 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 260:
#line 695 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6256 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 261:
#line 695 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 6262 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 262:
#line 698 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6268 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 263:
#line 698 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.str) = (yyvsp[-1].str);
                  }
#line 6276 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 264:
#line 703 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6282 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 265:
#line 703 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.str) = (yyvsp[-1].str);
                  }
#line 6290 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 266:
#line 708 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6296 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 267:
#line 708 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = makeCppToken(nullptr, nullptr); }
#line 6302 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 268:
#line 709 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 269:
#line 709 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 6314 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 270:
#line 712 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 271:
#line 712 "parser.y" /* yacc.c:1646  */
    { (yyval.enumItem) = new CppEnumItem((yyvsp[-1].str));     }
#line 6326 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 272:
#line 713 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6332 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 273:
#line 713 "parser.y" /* yacc.c:1646  */
    { (yyval.enumItem) = new CppEnumItem((yyvsp[-3].str), (yyvsp[-1].cppExprObj)); }
#line 6338 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 274:
#line 714 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6344 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 275:
#line 714 "parser.y" /* yacc.c:1646  */
    { (yyval.enumItem) = new CppEnumItem((yyvsp[-1].docCommentObj));     }
#line 6350 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 276:
#line 715 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6356 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 277:
#line 715 "parser.y" /* yacc.c:1646  */
    { (yyval.enumItem) = new CppEnumItem((yyvsp[-1].cppObj));     }
#line 6362 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 278:
#line 716 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6368 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 279:
#line 716 "parser.y" /* yacc.c:1646  */
    { (yyval.enumItem) = new CppEnumItem((yyvsp[-1].str));     }
#line 6374 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 280:
#line 717 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6380 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 281:
#line 717 "parser.y" /* yacc.c:1646  */
    { (yyval.enumItem) = new CppEnumItem((yyvsp[-1].blob));     }
#line 6386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 282:
#line 720 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6392 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 283:
#line 720 "parser.y" /* yacc.c:1646  */
    { (yyval.blob) = new CppBlob((yyvsp[-1].str));         }
#line 6398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 284:
#line 723 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 285:
#line 723 "parser.y" /* yacc.c:1646  */
    { (yyval.enumItemList) = 0; }
#line 6410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 286:
#line 724 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6416 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 287:
#line 724 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.enumItemList) = (yyvsp[-2].enumItemList) ? (yyvsp[-2].enumItemList) : new CppEnumItemList;
                    (yyval.enumItemList)->push_back((yyvsp[-1].enumItem));
                  }
#line 6425 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 288:
#line 728 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6431 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 289:
#line 728 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.enumItemList) = (yyvsp[-3].enumItemList) ? (yyvsp[-3].enumItemList) : new CppEnumItemList;
                    (yyval.enumItemList)->push_back((yyvsp[-1].enumItem));
                  }
#line 6440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 290:
#line 732 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6446 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 291:
#line 732 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.enumItemList) = (yyvsp[-2].enumItemList);
                  }
#line 6454 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 292:
#line 737 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6460 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 293:
#line 737 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-4].str), (yyvsp[-2].enumItemList));
                  }
#line 6468 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 294:
#line 740 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 295:
#line 740 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-6].str), (yyvsp[-2].enumItemList), false, (yyvsp[-4].str));
                  }
#line 6482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 296:
#line 743 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6488 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 297:
#line 743 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, "", (yyvsp[-2].enumItemList), false, (yyvsp[-4].str));
                  }
#line 6496 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 298:
#line 746 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6502 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 299:
#line 746 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-4].str), (yyvsp[-2].enumItemList), false);
                  }
#line 6510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 300:
#line 749 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 301:
#line 749 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-6].str), (yyvsp[-2].enumItemList), true, (yyvsp[-4].str));
                  }
#line 6524 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 302:
#line 752 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 303:
#line 752 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-4].str), (yyvsp[-2].enumItemList), true);
                  }
#line 6538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 304:
#line 755 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6544 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 305:
#line 755 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-1].str), (yyvsp[-3].enumItemList));
                  }
#line 6552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 306:
#line 760 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 307:
#line 760 "parser.y" /* yacc.c:1646  */
    { (yyval.cppEnum) = (yyvsp[-2].cppEnum); }
#line 6564 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 308:
#line 763 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 309:
#line 763 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-4].str), nullptr, false, (yyvsp[-2].str));
                  }
#line 6578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 310:
#line 766 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 311:
#line 766 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-4].str), nullptr, true, (yyvsp[-2].str));
                  }
#line 6592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 312:
#line 769 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6598 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 313:
#line 769 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppEnum) = new CppEnum(gCurAccessType, (yyvsp[-2].str), nullptr, true);
                  }
#line 6606 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 314:
#line 774 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 315:
#line 774 "parser.y" /* yacc.c:1646  */
    {
                    (yyvsp[-2].cppFuncPointerObj)->addAttr(kTypedef);
                    (yyval.cppFuncPointerObj) = (yyvsp[-2].cppFuncPointerObj);
                  }
#line 6621 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 316:
#line 779 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6627 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 317:
#line 779 "parser.y" /* yacc.c:1646  */
    { (yyval.typedefName) = (yyvsp[-2].typedefName); }
#line 6633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 318:
#line 782 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6639 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 319:
#line 782 "parser.y" /* yacc.c:1646  */
    { (yyval.typedefList) = (yyvsp[-2].typedefList); }
#line 6645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 320:
#line 785 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6651 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 321:
#line 785 "parser.y" /* yacc.c:1646  */
    { (yyval.typedefList) = new CppTypedefList((yyvsp[-1].cppVarObjList)); }
#line 6657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 322:
#line 788 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 323:
#line 788 "parser.y" /* yacc.c:1646  */
    { (yyval.typedefName) = new CppTypedefName((yyvsp[-1].cppVarObj)); }
#line 6669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 324:
#line 791 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 325:
#line 791 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.usingDecl) = new CppUsingDecl((yyvsp[-4].str), (yyvsp[-2].cppVarType));
                  }
#line 6683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 326:
#line 794 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 327:
#line 794 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.usingDecl) = new CppUsingDecl((yyvsp[-4].str), (yyvsp[-2].cppFuncPointerObj));
                  }
#line 6697 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 328:
#line 797 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6703 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 329:
#line 797 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.usingDecl) = new CppUsingDecl((yyvsp[-4].str), (yyvsp[-2].cppFuncPointerObj));
                  }
#line 6711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 330:
#line 800 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 331:
#line 800 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.usingDecl) = new CppUsingDecl((yyvsp[-4].str), (yyvsp[-2].cppCompundObj));
                  }
#line 6725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 332:
#line 803 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 333:
#line 803 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.usingDecl) = (yyvsp[-1].usingDecl);
                    (yyval.usingDecl)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 6740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 334:
#line 807 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 335:
#line 807 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.usingDecl) = new CppUsingDecl((yyvsp[-2].str), gCurAccessType);
                  }
#line 6754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 336:
#line 813 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6760 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 337:
#line 813 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.namespaceAlias) = new CppNamespaceAlias((yyvsp[-4].str), (yyvsp[-2].str));
                  }
#line 6768 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 338:
#line 818 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 339:
#line 818 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.usingNamespaceDecl) = new CppUsingNamespaceDecl((yyvsp[-2].str));
                  }
#line 6782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 340:
#line 823 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6788 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 341:
#line 823 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarObjList) = (yyvsp[-2].cppVarObjList); }
#line 6794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 342:
#line 824 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 343:
#line 824 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarObjList) = (yyvsp[-2].cppVarObjList); }
#line 6806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 344:
#line 827 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6812 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 345:
#line 827 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarObj) = (yyvsp[-2].cppVarObj); }
#line 6818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 346:
#line 828 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 347:
#line 828 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarObj) = (yyvsp[-2].cppVarObj); }
#line 6830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 348:
#line 829 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 349:
#line 829 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarObj) = (yyvsp[-1].cppVarObj); (yyval.cppVarObj)->apidecor((yyvsp[-2].str)); }
#line 6842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 350:
#line 830 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6848 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 351:
#line 830 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarObj) = (yyvsp[-1].cppVarObj); (yyval.cppVarObj)->addAttr((yyvsp[-2].attr)); }
#line 6854 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 352:
#line 831 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 6860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 353:
#line 831 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarObj) = (yyvsp[-1].cppVarObj); (yyval.cppVarObj)->addAttr((yyvsp[-2].attr)); }
#line 6866 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 354:
#line 834 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6872 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 355:
#line 834 "parser.y" /* yacc.c:1646  */
    {
                    (yyvsp[-5].cppVarObj)->addAttr((yyvsp[-6].attr));
                    (yyval.cppVarObjList) = new CppVarList((yyvsp[-5].cppVarObj), CppVarDeclInList((yyvsp[-3].typeModifier), CppVarDecl{(yyvsp[-2].str)}));
                    /* TODO: Use optvarassign as well */
                  }
#line 6882 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 356:
#line 839 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6888 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 357:
#line 839 "parser.y" /* yacc.c:1646  */
    {
                    (yyvsp[-5].cppVarObj)->addAttr((yyvsp[-6].attr));
                    (yyval.cppVarObjList) = new CppVarList((yyvsp[-5].cppVarObj), CppVarDeclInList((yyvsp[-3].typeModifier), CppVarDecl{(yyvsp[-2].str)}));
                    /* TODO: Use optvarassign as well */
                  }
#line 6898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 358:
#line 844 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 6904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 359:
#line 844 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObjList) = (yyvsp[-5].cppVarObjList);
                    (yyval.cppVarObjList)->addVarDecl(CppVarDeclInList((yyvsp[-3].typeModifier), CppVarDecl{(yyvsp[-2].str)}));
                    /* TODO: Use optvarassign as well */
                  }
#line 6914 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 360:
#line 851 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gParamModPos = $4.sz; ZZERROR;] ToYacc*/}
#line 6920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 361:
#line 851 "parser.y" /* yacc.c:1646  */
    { /*FuncDeclHack*/ (yyval.cppVarObj) = nullptr; }
#line 6926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 362:
#line 852 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gParamModPos = $4.sz; ZZERROR;] ToYacc*/}
#line 6932 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 363:
#line 852 "parser.y" /* yacc.c:1646  */
    { /*FuncDeclHack*/ (yyval.cppVarObj) = nullptr; }
#line 6938 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 364:
#line 853 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gParamModPos = $4.sz; ZZERROR;] ToYacc*/}
#line 6944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 365:
#line 853 "parser.y" /* yacc.c:1646  */
    { /*FuncDeclHack*/ (yyval.cppVarObj) = nullptr; }
#line 6950 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 366:
#line 854 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gParamModPos = $4.sz; ZZERROR;] ToYacc*/}
#line 6956 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 367:
#line 854 "parser.y" /* yacc.c:1646  */
    { /*FuncDeclHack*/ (yyval.cppVarObj) = nullptr; }
#line 6962 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 368:
#line 855 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gParamModPos = $4.sz; ZZERROR;] ToYacc*/}
#line 6968 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 369:
#line 855 "parser.y" /* yacc.c:1646  */
    { /*FuncDeclHack*/ (yyval.cppVarObj) = nullptr; }
#line 6974 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 370:
#line 856 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gParamModPos = $3.sz; ZZERROR;] ToYacc*/}
#line 6980 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 371:
#line 856 "parser.y" /* yacc.c:1646  */
    { /*FuncDeclHack*/ (yyval.cppVarObj) = nullptr; }
#line 6986 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 372:
#line 857 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZERROR;] ToYacc*/}
#line 6992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 373:
#line 857 "parser.y" /* yacc.c:1646  */
    { /*FuncDeclHack*/ (yyval.cppVarObj) = nullptr; }
#line 6998 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 374:
#line 858 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 375:
#line 858 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = (yyvsp[-2].cppVarObj);
                    (yyval.cppVarObj)->assign((yyvsp[-1].cppVarAssign).assignValue_, (yyvsp[-1].cppVarAssign).assignType_);
                  }
#line 7013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 376:
#line 862 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7019 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 377:
#line 862 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = (yyvsp[-1].cppVarObj);
                    (yyval.cppVarObj)->addAttr(kConstExpr);
                  }
#line 7028 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 378:
#line 868 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 379:
#line 868 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarAssign) = CppVarAssign{(yyvsp[-1].cppExprObj), AssignType::kUsingEqual};
                  }
#line 7042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 380:
#line 871 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 381:
#line 871 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarAssign) = CppVarAssign{(yyvsp[-2].cppExprObj), AssignType::kUsingBracket};
                  }
#line 7056 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 382:
#line 874 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7062 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 383:
#line 874 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarAssign) = CppVarAssign{(yyvsp[-2].cppExprObj), AssignType::kUsingBraces};
                  }
#line 7070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 384:
#line 879 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7076 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 385:
#line 879 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarAssign) = CppVarAssign{nullptr, AssignType::kNone}; }
#line 7082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 386:
#line 880 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 387:
#line 880 "parser.y" /* yacc.c:1646  */
    { (yyval.cppVarAssign) = (yyvsp[-1].cppVarAssign); }
#line 7094 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 388:
#line 883 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 389:
#line 883 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = new CppVar((yyvsp[-2].cppVarType), (yyvsp[-1].str).toString());
                  }
#line 7108 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 390:
#line 886 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7114 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 391:
#line 886 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = new CppVar(gCurAccessType, (yyvsp[-1].cppFuncPointerObj), CppTypeModifier());
                  }
#line 7122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 392:
#line 889 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7128 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 393:
#line 889 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = (yyvsp[-4].cppVarObj);
                    (yyval.cppVarObj)->addArraySize((yyvsp[-2].cppExprObj));
                  }
#line 7137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 394:
#line 893 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 395:
#line 893 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = (yyvsp[-3].cppVarObj);
                    (yyval.cppVarObj)->addArraySize(nullptr);
                  }
#line 7152 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 396:
#line 897 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7158 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 397:
#line 897 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = (yyvsp[-3].cppVarObj);
                    (yyval.cppVarObj)->bitField((yyvsp[-1].cppExprObj));
                  }
#line 7167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 398:
#line 901 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 399:
#line 901 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = (yyvsp[-1].cppVarObj);
                    (yyval.cppVarObj)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 7182 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 400:
#line 905 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7188 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 401:
#line 905 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarObj) = (yyvsp[-1].cppVarObj);
                    (yyval.cppVarObj)->addAttr((yyvsp[-2].attr));
                  }
#line 7197 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 402:
#line 911 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7203 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 403:
#line 911 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, (yyvsp[-2].str), (yyvsp[-1].typeModifier));
                  }
#line 7211 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 404:
#line 914 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if (gTemplateParamStart == $1.sz)
                      ZZERROR;
                    else
                      ZZLOG;
                  ] ToYacc*/}
#line 7222 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 405:
#line 919 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, mergeCppToken((yyvsp[-3].str), (yyvsp[-2].str)), (yyvsp[-1].typeModifier));
                  }
#line 7230 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 406:
#line 922 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7236 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 407:
#line 922 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, mergeCppToken((yyvsp[-3].str), (yyvsp[-2].str)), (yyvsp[-1].typeModifier));
                  }
#line 7244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 408:
#line 925 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7250 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 409:
#line 925 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, mergeCppToken((yyvsp[-3].str), (yyvsp[-2].str)), (yyvsp[-1].typeModifier));
                  }
#line 7258 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 410:
#line 928 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7264 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 411:
#line 928 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, (yyvsp[-1].cppFuncPointerObj), CppTypeModifier());
                  }
#line 7272 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 412:
#line 931 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7278 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 413:
#line 931 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, (yyvsp[-1].cppCompundObj), CppTypeModifier());
                  }
#line 7286 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 414:
#line 934 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 415:
#line 934 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, (yyvsp[-2].cppCompundObj), (yyvsp[-1].typeModifier));
                  }
#line 7300 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 416:
#line 937 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7306 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 417:
#line 937 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, (yyvsp[-1].cppEnum), CppTypeModifier());
                  }
#line 7314 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 418:
#line 940 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 419:
#line 940 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, (yyvsp[-2].cppEnum), (yyvsp[-1].typeModifier));
                  }
#line 7328 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 420:
#line 943 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7334 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 421:
#line 943 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = (yyvsp[-1].cppVarType);
                    (yyval.cppVarType)->addAttr((yyvsp[-2].attr));
                  }
#line 7343 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 422:
#line 947 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7349 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 423:
#line 947 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppVarType) = (yyvsp[-2].cppVarType);
                    (yyval.cppVarType)->paramPack_ = true;
                  }
#line 7358 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 424:
#line 951 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7364 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 425:
#line 951 "parser.y" /* yacc.c:1646  */
    {
                    // reference to member declrations. E.g.:
                    // int GrCCStrokeGeometry::InstanceTallies::* InstanceType
                    (yyval.cppVarType) = new CppVarType(gCurAccessType, mergeCppToken((yyvsp[-4].str), (yyvsp[-2].str)), (yyvsp[-1].typeModifier));
                  }
#line 7374 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 426:
#line 958 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7380 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 427:
#line 958 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 7386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 428:
#line 959 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7392 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 429:
#line 959 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); /* final is not a reserved keyword */ }
#line 7398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 430:
#line 960 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 431:
#line 960 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 7410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 432:
#line 961 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7416 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 433:
#line 961 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 7422 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 434:
#line 962 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7428 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 435:
#line 962 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-5].str), (yyvsp[-1].str)); }
#line 7434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 436:
#line 965 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 437:
#line 965 "parser.y" /* yacc.c:1646  */
    { (yyval.typeModifier) = CppTypeModifier(); }
#line 7446 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 438:
#line 966 "parser.y" /* yacc.c:1646  */
    { (yyval.typeModifier) = (yyvsp[0].typeModifier); }
#line 7452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 439:
#line 969 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 440:
#line 969 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = CppTypeModifier();
                    (yyval.typeModifier).constBits_ |= (1 << (yyval.typeModifier).ptrLevel_);
                  }
#line 7467 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 441:
#line 973 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7473 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 442:
#line 973 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = CppTypeModifier();
                    (yyval.typeModifier).ptrLevel_++;
                  }
#line 7482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 443:
#line 977 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7488 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 444:
#line 977 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = CppTypeModifier();
                    (yyval.typeModifier).refType_ = CppRefType::kByRef;
                  }
#line 7497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 445:
#line 981 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7503 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 446:
#line 981 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = CppTypeModifier();
                    (yyval.typeModifier).refType_ = CppRefType::kRValRef;
                  }
#line 7512 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 447:
#line 985 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7518 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 448:
#line 985 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = (yyvsp[-2].typeModifier);
                    (yyval.typeModifier).constBits_ |= (1 << (yyval.typeModifier).ptrLevel_);
                  }
#line 7527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 449:
#line 989 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 450:
#line 989 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = (yyvsp[-2].typeModifier);
                    (yyval.typeModifier).ptrLevel_++;
                  }
#line 7542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 451:
#line 993 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7548 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 452:
#line 993 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = (yyvsp[-2].typeModifier);
                    (yyval.typeModifier).refType_ = CppRefType::kByRef;
                  }
#line 7557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 453:
#line 997 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 454:
#line 997 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.typeModifier) = (yyvsp[-2].typeModifier);
                    (yyval.typeModifier).refType_ = CppRefType::kRValRef;
                  }
#line 7572 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 455:
#line 1004 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 456:
#line 1004 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kStatic;  }
#line 7584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 457:
#line 1005 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7590 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 458:
#line 1005 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kExtern;  }
#line 7596 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 459:
#line 1006 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 460:
#line 1006 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kExternC; }
#line 7608 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 461:
#line 1009 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7614 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 462:
#line 1009 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kConst;      }
#line 7620 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 463:
#line 1010 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 464:
#line 1010 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kVolatile;   }
#line 7632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 465:
#line 1011 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7638 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 466:
#line 1011 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kMutable;    }
#line 7644 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 467:
#line 1012 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 468:
#line 1012 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kConstExpr;  }
#line 7656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 469:
#line 1015 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7662 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 470:
#line 1015 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = newTypeConverter((yyvsp[-4].cppVarType), makeCppToken((yyvsp[-5].str).sz, (yyvsp[-3].str).sz));
                  }
#line 7670 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 471:
#line 1018 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7676 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 472:
#line 1018 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = newTypeConverter((yyvsp[-4].cppVarType), makeCppToken((yyvsp[-7].str).sz, (yyvsp[-3].str).sz));
                  }
#line 7684 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 473:
#line 1021 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 474:
#line 1021 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = (yyvsp[-1].cppTypeConverter);
                    (yyval.cppTypeConverter)->addAttr((yyvsp[-2].attr));
                  }
#line 7699 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 475:
#line 1025 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7705 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 476:
#line 1025 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = (yyvsp[-2].cppTypeConverter);
                    (yyval.cppTypeConverter)->addAttr(kConst);
                  }
#line 7714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 477:
#line 1029 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 478:
#line 1029 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = (yyvsp[-1].cppTypeConverter);
                    (yyval.cppTypeConverter)->decor1((yyvsp[-2].str));
                  }
#line 7729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 479:
#line 1033 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 480:
#line 1033 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = (yyvsp[-1].cppTypeConverter);
                    (yyval.cppTypeConverter)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 7744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 481:
#line 1039 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7750 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 482:
#line 1039 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = (yyvsp[-2].cppTypeConverter);
                  }
#line 7758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 483:
#line 1042 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 484:
#line 1042 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppTypeConverter) = (yyvsp[-2].cppTypeConverter);
                    (yyval.cppTypeConverter)->defn((yyvsp[-1].cppCompundObj));
                  }
#line 7773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 485:
#line 1048 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7779 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 486:
#line 1048 "parser.y" /* yacc.c:1646  */
    { (yyval.cppFuncObj) = (yyvsp[-2].cppFuncObj); }
#line 7785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 487:
#line 1051 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 488:
#line 1051 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-2].cppFuncObj);
                    (yyval.cppFuncObj)->defn((yyvsp[-1].cppCompundObj) ? (yyvsp[-1].cppCompundObj) : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
#line 7800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 489:
#line 1057 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppLambda) = new CppLambda((yyvsp[-3].cppExprObj), (yyvsp[-1].paramList), (yyvsp[0].cppCompundObj));
                  }
#line 7808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 490:
#line 1060 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppLambda) = new CppLambda((yyvsp[-5].cppExprObj), (yyvsp[-3].paramList), (yyvsp[0].cppCompundObj), (yyvsp[-1].cppVarType));
                  }
#line 7816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 491:
#line 1065 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7822 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 492:
#line 1065 "parser.y" /* yacc.c:1646  */
    { (yyval.paramList) = nullptr; }
#line 7828 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 493:
#line 1066 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7834 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 494:
#line 1066 "parser.y" /* yacc.c:1646  */
    { (yyval.paramList) = (yyvsp[-2].paramList); }
#line 7840 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 495:
#line 1069 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 496:
#line 1069 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncPointerObj) = new CppFunctionPointer(gCurAccessType, (yyvsp[-5].str), (yyvsp[-11].cppVarType), (yyvsp[-2].paramList), (yyvsp[-12].attr), mergeCppToken((yyvsp[-8].str), (yyvsp[-7].str)));
                    (yyval.cppFuncPointerObj)->decor2((yyvsp[-9].str));
                  }
#line 7855 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 497:
#line 1073 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 498:
#line 1073 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncPointerObj) = new CppFunctionPointer(gCurAccessType, (yyvsp[-5].str), (yyvsp[-11].cppVarType), (yyvsp[-2].paramList), 0, mergeCppToken((yyvsp[-8].str), (yyvsp[-7].str)));
                    (yyval.cppFuncPointerObj)->decor2((yyvsp[-9].str));
                  }
#line 7870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 499:
#line 1077 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7876 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 500:
#line 1077 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncPointerObj) = new CppFunctionPointer(gCurAccessType, (yyvsp[-5].str), (yyvsp[-9].cppVarType), (yyvsp[-2].paramList), (yyvsp[-10].attr));
                    (yyval.cppFuncPointerObj)->decor2((yyvsp[-7].str));
                  }
#line 7885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 501:
#line 1081 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7891 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 502:
#line 1081 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncPointerObj) = new CppFunctionPointer(gCurAccessType, (yyvsp[-5].str), (yyvsp[-9].cppVarType), (yyvsp[-2].paramList), 0);
                    (yyval.cppFuncPointerObj)->decor2((yyvsp[-7].str));
                  }
#line 7900 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 503:
#line 1085 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7906 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 504:
#line 1085 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncPointerObj) = (yyvsp[-1].cppFuncPointerObj);
                    (yyval.cppFuncPointerObj)->decor1((yyvsp[-2].str));
                  }
#line 7915 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 505:
#line 1089 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7921 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 506:
#line 1089 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncPointerObj) = (yyvsp[-2].cppFuncPointerObj);
                    (yyval.cppFuncPointerObj)->addAttr((yyvsp[-1].attr));
                  }
#line 7930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 507:
#line 1096 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                      if ($1->name_.empty() == true) {
                        ZZERROR;
                      }
                    ] ToYacc*/}
#line 7940 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 508:
#line 1104 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                      if ($1->name_.empty() == false) {
                        ZZERROR;
                      }
                    ] ToYacc*/}
#line 7950 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 509:
#line 1111 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7956 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 510:
#line 1111 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncPointerObj) = new CppFunctionPointer(gCurAccessType, "", (yyvsp[-5].cppVarType), (yyvsp[-2].paramList), 0);
                  }
#line 7964 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 511:
#line 1116 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 7970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 512:
#line 1116 "parser.y" /* yacc.c:1646  */
    { (yyval.cppFuncPointerObj) = (yyvsp[-2].cppFuncPointerObj);}
#line 7976 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 513:
#line 1119 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7982 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 514:
#line 1119 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.funcDeclData) = CppNtFuncDeclData{(yyvsp[-4].str), (yyvsp[-2].paramList), 0};
                  }
#line 7990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 515:
#line 1122 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 7996 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 516:
#line 1122 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.funcDeclData) = CppNtFuncDeclData{(yyvsp[-5].str), (yyvsp[-3].paramList), (yyvsp[-1].attr)};
                  }
#line 8004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 517:
#line 1127 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 8010 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 518:
#line 1127 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = newFunction(gCurAccessType, (yyvsp[-1].funcDeclData).funcName, (yyvsp[-3].cppVarType), (yyvsp[-1].funcDeclData).paramList, (yyvsp[-1].funcDeclData).funcAttr);
                    (yyval.cppFuncObj)->decor2((yyvsp[-2].str));
                  }
#line 8019 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 519:
#line 1131 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 8025 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 520:
#line 1131 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = newFunction(gCurAccessType, (yyvsp[-1].funcDeclData).funcName, (yyvsp[-2].cppVarType), (yyvsp[-1].funcDeclData).paramList, (yyvsp[-1].funcDeclData).funcAttr);
                  }
#line 8033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 521:
#line 1134 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 8039 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 522:
#line 1134 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = newFunction(gCurAccessType, (yyvsp[-1].funcDeclData).funcName, (yyvsp[-3].cppVarType), (yyvsp[-1].funcDeclData).paramList, (yyvsp[-1].funcDeclData).funcAttr | kConstExpr);
                  }
#line 8047 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 523:
#line 1137 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 8053 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 524:
#line 1137 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = newFunction(gCurAccessType, (yyvsp[-3].funcDeclData).funcName, (yyvsp[-1].cppVarType), (yyvsp[-3].funcDeclData).paramList, (yyvsp[-3].funcDeclData).funcAttr | kTrailingRet);
                  }
#line 8061 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 525:
#line 1140 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 8067 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 526:
#line 1140 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = newFunction(gCurAccessType, (yyvsp[-3].funcDeclData).funcName, (yyvsp[-1].cppVarType), (yyvsp[-3].funcDeclData).paramList, (yyvsp[-3].funcDeclData).funcAttr | kTrailingRet | kConstExpr);
                  }
#line 8075 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 527:
#line 1143 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8081 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 528:
#line 1143 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-1].cppFuncObj);
                    (yyval.cppFuncObj)->addAttr(kConstExpr);
                  }
#line 8090 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 529:
#line 1147 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8096 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 530:
#line 1147 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-1].cppFuncObj);
                    if (!(yyval.cppFuncObj)->decor1().empty())
                      (yyval.cppFuncObj)->decor2((yyval.cppFuncObj)->decor1());
                    (yyval.cppFuncObj)->decor1((yyvsp[-2].str));
                  }
#line 8107 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 531:
#line 1153 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8113 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 532:
#line 1153 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-1].cppFuncObj);
                    (yyval.cppFuncObj)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 8122 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 533:
#line 1157 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8128 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 534:
#line 1157 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-1].cppFuncObj);
                    (yyval.cppFuncObj)->addAttr((yyvsp[-2].attr));
                  }
#line 8137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 535:
#line 1161 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 536:
#line 1161 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-3].cppFuncObj);
                    (yyval.cppFuncObj)->addAttr(kDelete);
                  }
#line 8152 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 537:
#line 1165 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8158 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 538:
#line 1165 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-3].cppFuncObj);
                    (yyval.cppFuncObj)->addAttr(kDefault);
                  }
#line 8167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 539:
#line 1169 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8173 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 540:
#line 1169 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppFuncObj) = (yyvsp[-2].cppFuncObj);
                    (yyval.cppFuncObj)->throwSpec((yyvsp[-1].funcThrowSpec));
                  }
#line 8182 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 541:
#line 1175 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8188 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 542:
#line 1175 "parser.y" /* yacc.c:1646  */
    {
                    delete (yyvsp[-2].paramList);
                    (yyval.str) = mergeCppToken((yyvsp[-5].str), (yyvsp[-1].str));
                  }
#line 8197 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 543:
#line 1181 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8203 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 544:
#line 1181 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 8209 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 545:
#line 1182 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8215 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 546:
#line 1182 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 8221 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 547:
#line 1183 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8227 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 548:
#line 1183 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8233 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 549:
#line 1185 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8239 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 550:
#line 1185 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 8245 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 551:
#line 1188 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ if ($2.sz != ($1.sz + 1)) ZZERROR; ] ToYacc*/}
#line 8251 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 552:
#line 1188 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8257 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 553:
#line 1191 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8263 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 554:
#line 1191 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8269 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 555:
#line 1192 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8275 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 556:
#line 1192 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8281 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 557:
#line 1193 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8287 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 558:
#line 1193 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8293 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 559:
#line 1194 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8299 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 560:
#line 1194 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8305 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 561:
#line 1195 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8311 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 562:
#line 1195 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8317 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 563:
#line 1196 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8323 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 564:
#line 1196 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8329 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 565:
#line 1197 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8335 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 566:
#line 1197 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8341 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 567:
#line 1198 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8347 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 568:
#line 1198 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8353 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 569:
#line 1199 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8359 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 570:
#line 1199 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8365 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 571:
#line 1200 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8371 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 572:
#line 1200 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 573:
#line 1201 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8383 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 574:
#line 1201 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8389 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 575:
#line 1202 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8395 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 576:
#line 1202 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8401 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 577:
#line 1203 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8407 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 578:
#line 1203 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8413 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 579:
#line 1204 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8419 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 580:
#line 1204 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8425 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 581:
#line 1205 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8431 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 582:
#line 1205 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8437 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 583:
#line 1206 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8443 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 584:
#line 1206 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8449 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 585:
#line 1207 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8455 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 586:
#line 1207 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 587:
#line 1208 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8467 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 588:
#line 1208 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8473 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 589:
#line 1209 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8479 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 590:
#line 1209 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8485 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 591:
#line 1210 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8491 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 592:
#line 1210 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8497 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 593:
#line 1211 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8503 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 594:
#line 1211 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8509 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 595:
#line 1212 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8515 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 596:
#line 1212 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8521 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 597:
#line 1213 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8527 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 598:
#line 1213 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 599:
#line 1214 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8539 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 600:
#line 1214 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8545 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 601:
#line 1215 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8551 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 602:
#line 1215 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 603:
#line 1216 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 604:
#line 1216 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 605:
#line 1217 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8575 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 606:
#line 1217 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 607:
#line 1218 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8587 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 608:
#line 1218 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8593 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 609:
#line 1219 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8599 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 610:
#line 1219 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 611:
#line 1220 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 612:
#line 1220 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 613:
#line 1221 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 614:
#line 1221 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 615:
#line 1222 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 616:
#line 1222 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 617:
#line 1223 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 618:
#line 1223 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 619:
#line 1224 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 620:
#line 1224 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 621:
#line 1225 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 622:
#line 1225 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8677 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 623:
#line 1226 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8683 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 624:
#line 1226 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 625:
#line 1227 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 626:
#line 1227 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 627:
#line 1228 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8707 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 628:
#line 1228 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 8713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 629:
#line 1229 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 630:
#line 1229 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 8725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 631:
#line 1230 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8731 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 632:
#line 1230 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 633:
#line 1231 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8743 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 634:
#line 1231 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 8749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 635:
#line 1232 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8755 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 636:
#line 1232 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8761 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 637:
#line 1233 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8767 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 638:
#line 1233 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 8773 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 639:
#line 1234 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8779 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 640:
#line 1234 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 8785 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 641:
#line 1235 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8791 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 642:
#line 1235 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 8797 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 643:
#line 1236 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8803 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 644:
#line 1236 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 8809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 645:
#line 1239 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8815 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 646:
#line 1239 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-3].str), (yyvsp[-1].str)); }
#line 8821 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 647:
#line 1244 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 648:
#line 1244 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 8833 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 649:
#line 1247 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8839 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 650:
#line 1247 "parser.y" /* yacc.c:1646  */
    { (yyval.paramList) = nullptr; }
#line 8845 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 651:
#line 1248 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.paramList) = new CppParamVector;
                    (yyval.paramList)->emplace_back((yyvsp[0].varOrFuncPtr));
                  }
#line 8854 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 652:
#line 1252 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 653:
#line 1252 "parser.y" /* yacc.c:1646  */
    {
                    (yyvsp[-3].paramList)->emplace_back((yyvsp[-1].varOrFuncPtr));
                    (yyval.paramList) = (yyvsp[-3].paramList);
                  }
#line 8869 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 654:
#line 1258 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8875 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 655:
#line 1258 "parser.y" /* yacc.c:1646  */
    { (yyval.varOrFuncPtr) = (yyvsp[-1].cppVarObj); (yyvsp[-1].cppVarObj)->addAttr(kFuncParam);  }
#line 8881 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 656:
#line 1259 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 657:
#line 1259 "parser.y" /* yacc.c:1646  */
    {
                    auto var = new CppVar((yyvsp[-3].cppVarType), std::string());
                    var->addAttr(kFuncParam);
                    var->assign((yyvsp[-1].cppExprObj), AssignType::kUsingEqual);
                    (yyval.varOrFuncPtr) = var;
                  }
#line 8898 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 658:
#line 1265 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8904 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 659:
#line 1265 "parser.y" /* yacc.c:1646  */
    { (yyval.varOrFuncPtr) = (yyvsp[-1].cppVarObj); (yyvsp[-1].cppVarObj)->addAttr(kFuncParam);  }
#line 8910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 660:
#line 1266 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8916 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 661:
#line 1266 "parser.y" /* yacc.c:1646  */
    {
                    auto var = new CppVar((yyvsp[-1].cppVarType), std::string());
                    var->addAttr(kFuncParam);
                    (yyval.varOrFuncPtr) = var;
                  }
#line 8926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 662:
#line 1271 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8932 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 663:
#line 1271 "parser.y" /* yacc.c:1646  */
    { (yyval.varOrFuncPtr) = (yyvsp[-1].cppFuncPointerObj); (yyvsp[-1].cppFuncPointerObj)->addAttr(kFuncParam);     }
#line 8938 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 664:
#line 1272 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 665:
#line 1272 "parser.y" /* yacc.c:1646  */
    { (yyval.varOrFuncPtr) = (yyvsp[-1].varOrFuncPtr); }
#line 8950 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 666:
#line 1273 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8956 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 667:
#line 1273 "parser.y" /* yacc.c:1646  */
    {
                    auto var = new CppVar((yyvsp[-4].cppVarType), std::string());
                    var->addAttr(kFuncParam);
                    var->addArraySize((yyvsp[-2].cppExprObj));
                    (yyval.varOrFuncPtr) = var;
                  }
#line 8967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 668:
#line 1279 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 669:
#line 1279 "parser.y" /* yacc.c:1646  */
    {
                    auto var = new CppVar((yyvsp[-3].cppVarType), std::string());
                    var->addAttr(kFuncParam);
                    var->addArraySize(nullptr);
                    (yyval.varOrFuncPtr) = var;
                  }
#line 8984 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 670:
#line 1287 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 8990 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 671:
#line 1287 "parser.y" /* yacc.c:1646  */
    { (yyval.templateArg) = nullptr; /*$$ = makeCppToken(nullptr, nullptr);*/ }
#line 8996 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 672:
#line 1288 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 673:
#line 1288 "parser.y" /* yacc.c:1646  */
    { (yyval.templateArg) = nullptr; /*$$ = mergeCppToken($1, $2);*/ }
#line 9008 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 674:
#line 1289 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9014 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 675:
#line 1289 "parser.y" /* yacc.c:1646  */
    { (yyval.templateArg) = nullptr; /*$$ = $1;*/ }
#line 9020 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 676:
#line 1290 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 677:
#line 1290 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateArg) = nullptr;
                  }
#line 9034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 678:
#line 1295 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9040 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 679:
#line 1295 "parser.y" /* yacc.c:1646  */
    { (yyval.templateArg) = (yyvsp[-1].templateArg); }
#line 9046 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 680:
#line 1296 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 681:
#line 1296 "parser.y" /* yacc.c:1646  */
    { (yyval.templateArg) = (yyvsp[-3].templateArg); /*$$ = mergeCppToken($1, $3);*/ }
#line 9058 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 682:
#line 1299 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 683:
#line 1299 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = (yyvsp[-1].attr); }
#line 9070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 684:
#line 1300 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9076 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 685:
#line 1300 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kInline;    }
#line 9082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 686:
#line 1301 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 687:
#line 1301 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kVirtual;   }
#line 9094 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 688:
#line 1302 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9100 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 689:
#line 1302 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kExplicit;  }
#line 9106 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 690:
#line 1303 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9112 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 691:
#line 1303 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kFriend;    }
#line 9118 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 692:
#line 1304 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9124 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 693:
#line 1304 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kConstExpr; }
#line 9130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 694:
#line 1307 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9136 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 695:
#line 1307 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = 0;}
#line 9142 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 696:
#line 1308 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9148 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 697:
#line 1308 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = (yyvsp[-1].attr);}
#line 9154 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 698:
#line 1311 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9160 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 699:
#line 1311 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kConst; }
#line 9166 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 700:
#line 1312 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9172 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 701:
#line 1312 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kOverride; }
#line 9178 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 702:
#line 1313 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9184 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 703:
#line 1313 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kFinal; }
#line 9190 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 704:
#line 1314 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9196 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 705:
#line 1314 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kNoExcept; }
#line 9202 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 706:
#line 1315 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($2.len != 1 || $2.sz[0] != '0') YYABORT; else ZZVALID;] ToYacc*/}
#line 9208 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 707:
#line 1316 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9214 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 708:
#line 1316 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kPureVirtual; }
#line 9220 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 709:
#line 1317 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9226 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 710:
#line 1317 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = (yyvsp[-2].attr) | kConst; }
#line 9232 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 711:
#line 1318 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9238 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 712:
#line 1318 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = (yyvsp[-2].attr) | kOverride; }
#line 9244 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 713:
#line 1319 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9250 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 714:
#line 1319 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = (yyvsp[-2].attr) | kFinal; }
#line 9256 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 715:
#line 1320 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9262 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 716:
#line 1320 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = (yyvsp[-2].attr) | kNoExcept; }
#line 9268 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 717:
#line 1321 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($3.len != 1 || $3.sz[0] != '0') YYABORT; else ZZVALID;] ToYacc*/}
#line 9274 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 718:
#line 1322 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = (yyvsp[-3].attr) | kPureVirtual; }
#line 9280 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 719:
#line 1323 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9286 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 720:
#line 1323 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = 0; }
#line 9292 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 721:
#line 1326 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9298 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 722:
#line 1326 "parser.y" /* yacc.c:1646  */
    { (yyval.funcThrowSpec) = nullptr; }
#line 9304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 723:
#line 1327 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9310 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 724:
#line 1327 "parser.y" /* yacc.c:1646  */
    { (yyval.funcThrowSpec) = (yyvsp[-1].funcThrowSpec); }
#line 9316 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 725:
#line 1330 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9322 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 726:
#line 1330 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.funcThrowSpec) = (yyvsp[-2].identifierList) ? (yyvsp[-2].identifierList) : new CppFuncThrowSpec;
                  }
#line 9330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 727:
#line 1335 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 728:
#line 1335 "parser.y" /* yacc.c:1646  */
    { (yyval.identifierList) = nullptr; }
#line 9342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 729:
#line 1336 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9348 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 730:
#line 1336 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.identifierList) = new CppIdentifierList;
                    (yyval.identifierList)->push_back((yyvsp[-1].str));
                  }
#line 9357 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 731:
#line 1340 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 732:
#line 1340 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.identifierList) = (yyvsp[-3].identifierList);
                    (yyval.identifierList)->push_back((yyvsp[-1].str));
                  }
#line 9372 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 733:
#line 1346 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9378 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 734:
#line 1346 "parser.y" /* yacc.c:1646  */
    { (yyval.cppCtorObj) = (yyvsp[-2].cppCtorObj); }
#line 9384 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 735:
#line 1349 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9390 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 736:
#line 1350 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-3].cppCtorObj);
                    (yyval.cppCtorObj)->memInitList_  = (yyvsp[-2].memInitList);
                    (yyval.cppCtorObj)->defn((yyvsp[-1].cppCompundObj));
                  }
#line 9400 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 737:
#line 1355 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($1 != $3) ZZERROR; else ZZVALID;] ToYacc*/}
#line 9406 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 738:
#line 1356 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9412 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 739:
#line 1357 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = newConstructor(gCurAccessType, mergeCppToken((yyvsp[-10].str), (yyvsp[-8].str)), (yyvsp[-5].paramList), (yyvsp[-2].memInitList), 0);
                    (yyval.cppCtorObj)->defn((yyvsp[-1].cppCompundObj));
                    (yyval.cppCtorObj)->throwSpec((yyvsp[-3].funcThrowSpec));
                  }
#line 9422 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 740:
#line 1362 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($3 != $5) ZZERROR; else ZZVALID;] ToYacc*/}
#line 9428 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 741:
#line 1363 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 742:
#line 1364 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = newConstructor(gCurAccessType, mergeCppToken((yyvsp[-12].str), (yyvsp[-8].str)), (yyvsp[-5].paramList), (yyvsp[-2].memInitList), 0);
                    (yyval.cppCtorObj)->defn((yyvsp[-1].cppCompundObj));
                    (yyval.cppCtorObj)->throwSpec((yyvsp[-3].funcThrowSpec));
                  }
#line 9444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 743:
#line 1369 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($1 != $6) ZZERROR; else ZZVALID;] ToYacc*/}
#line 9450 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 744:
#line 1370 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9456 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 745:
#line 1371 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = newConstructor(gCurAccessType, mergeCppToken((yyvsp[-13].str), (yyvsp[-8].str)), (yyvsp[-5].paramList), (yyvsp[-2].memInitList), 0);
                    (yyval.cppCtorObj)->defn((yyvsp[-1].cppCompundObj));
                    (yyval.cppCtorObj)->throwSpec((yyvsp[-3].funcThrowSpec));
                  }
#line 9466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 746:
#line 1376 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 747:
#line 1376 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-1].cppCtorObj);
                    (yyval.cppCtorObj)->addAttr((yyvsp[-2].attr));
                  }
#line 9481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 748:
#line 1380 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 749:
#line 1380 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-1].cppCtorObj);
                    (yyval.cppCtorObj)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 9496 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 750:
#line 1387 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if(gCompoundStack.empty())
                      ZZERROR;
                    if(classNameFromIdentifier(gCompoundStack.top()) != $1)
                      ZZERROR;
                    else
                      ZZVALID;
                  ] ToYacc*/}
#line 9509 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 751:
#line 1395 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = newConstructor(gCurAccessType, (yyvsp[-4].str), (yyvsp[-2].paramList), nullptr, 0);
                  }
#line 9517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 752:
#line 1398 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 753:
#line 1398 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-1].cppCtorObj);
                    (yyval.cppCtorObj)->addAttr((yyvsp[-2].attr));
                  }
#line 9532 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 754:
#line 1402 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 755:
#line 1402 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-1].cppCtorObj);
                    (yyval.cppCtorObj)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 9547 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 756:
#line 1406 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 757:
#line 1406 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-3].cppCtorObj);
                    (yyval.cppCtorObj)->addAttr(kDelete);
                  }
#line 9562 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 758:
#line 1410 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9568 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 759:
#line 1410 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-3].cppCtorObj);
                    (yyval.cppCtorObj)->addAttr(kDefault);
                  }
#line 9577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 760:
#line 1414 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 761:
#line 1414 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-2].cppCtorObj);
                    (yyval.cppCtorObj)->throwSpec((yyvsp[-1].funcThrowSpec));
                  }
#line 9592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 762:
#line 1418 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9598 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 763:
#line 1418 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-2].cppCtorObj);
                    (yyval.cppCtorObj)->addAttr(kNoExcept);
                  }
#line 9607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 764:
#line 1422 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9613 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 765:
#line 1422 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCtorObj) = (yyvsp[-1].cppCtorObj);
                    (yyval.cppCtorObj)->decor1((yyvsp[-2].str));
                  }
#line 9622 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 766:
#line 1428 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9628 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 767:
#line 1428 "parser.y" /* yacc.c:1646  */
    { (yyval.memInitList) = nullptr; }
#line 9634 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 768:
#line 1429 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9640 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 769:
#line 1429 "parser.y" /* yacc.c:1646  */
    { (yyval.memInitList) = new CppMemInitList; (yyval.memInitList)->push_back(CppMemInit((yyvsp[-1].memInit).mem, (yyvsp[-1].memInit).init)); }
#line 9646 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 770:
#line 1430 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9652 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 771:
#line 1430 "parser.y" /* yacc.c:1646  */
    { (yyval.memInitList) = (yyvsp[-3].memInitList); (yyval.memInitList)->push_back(CppMemInit((yyvsp[-1].memInit).mem, (yyvsp[-1].memInit).init)); }
#line 9658 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 772:
#line 1433 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9664 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 773:
#line 1433 "parser.y" /* yacc.c:1646  */
    { (yyval.memInit) = CppNtMemInit{(yyvsp[-4].str), (yyvsp[-2].cppExprObj)}; }
#line 9670 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 774:
#line 1434 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9676 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 775:
#line 1434 "parser.y" /* yacc.c:1646  */
    { (yyval.memInit) = CppNtMemInit{(yyvsp[-3].str), nullptr}; }
#line 9682 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 776:
#line 1435 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9688 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 777:
#line 1435 "parser.y" /* yacc.c:1646  */
    { (yyval.memInit) = CppNtMemInit{(yyvsp[-4].str), (yyvsp[-2].cppExprObj)}; }
#line 9694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 778:
#line 1436 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9700 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 779:
#line 1436 "parser.y" /* yacc.c:1646  */
    { (yyval.memInit) = CppNtMemInit{(yyvsp[-3].str), nullptr}; }
#line 9706 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 780:
#line 1439 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9712 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 781:
#line 1439 "parser.y" /* yacc.c:1646  */
    { (yyval.cppDtorObj) = (yyvsp[-2].cppDtorObj); }
#line 9718 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 782:
#line 1442 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9724 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 783:
#line 1443 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-2].cppDtorObj);
                    (yyval.cppDtorObj)->defn((yyvsp[-1].cppCompundObj) ? (yyvsp[-1].cppCompundObj) : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
#line 9733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 784:
#line 1447 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($1 != $4) ZZERROR; else ZZVALID;] ToYacc*/}
#line 9739 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 785:
#line 1449 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = newDestructor(gCurAccessType, mergeCppToken((yyvsp[-7].str), (yyvsp[-4].str)), 0);
                    (yyval.cppDtorObj)->defn((yyvsp[0].cppCompundObj) ? (yyvsp[0].cppCompundObj) : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
#line 9748 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 786:
#line 1453 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($3 != $6) ZZERROR; else ZZVALID;] ToYacc*/}
#line 9754 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 787:
#line 1455 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = newDestructor(gCurAccessType, mergeCppToken((yyvsp[-9].str), (yyvsp[-4].str)), 0);
                    (yyval.cppDtorObj)->defn((yyvsp[0].cppCompundObj) ? (yyvsp[0].cppCompundObj) : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
#line 9763 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 788:
#line 1459 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [if($1 != $7) ZZERROR; else ZZVALID;] ToYacc*/}
#line 9769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 789:
#line 1461 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = newDestructor(gCurAccessType, mergeCppToken((yyvsp[-10].str), (yyvsp[-4].str)), 0);
                    (yyval.cppDtorObj)->defn((yyvsp[0].cppCompundObj) ? (yyvsp[0].cppCompundObj) : newCompound(CppAccessType::kUnknown, CppCompoundType::kBlock));
                  }
#line 9778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 790:
#line 1465 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 791:
#line 1465 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-1].cppDtorObj);
                    (yyval.cppDtorObj)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 9793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 792:
#line 1469 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 793:
#line 1469 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-1].cppDtorObj);
                    (yyval.cppDtorObj)->addAttr((yyvsp[-2].attr));
                  }
#line 9808 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 794:
#line 1475 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9814 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 795:
#line 1476 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if(gCompoundStack.empty())
                      ZZERROR;
                    if(classNameFromIdentifier(gCompoundStack.top()) != $2)
                      ZZERROR;
                    else
                      ZZVALID;
                  ] ToYacc*/}
#line 9827 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 796:
#line 1484 "parser.y" /* yacc.c:1646  */
    {
                    const char* tildaStartPos = (yyvsp[-5].str).sz-1;
                    while(*tildaStartPos != '~') --tildaStartPos;
                    (yyval.cppDtorObj) = newDestructor(gCurAccessType, makeCppToken(tildaStartPos, (yyvsp[-5].str).sz+(yyvsp[-5].str).len-tildaStartPos), 0);
                  }
#line 9837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 797:
#line 1489 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 798:
#line 1489 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-1].cppDtorObj);
                    (yyval.cppDtorObj)->decor1((yyvsp[-2].str));
                  }
#line 9852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 799:
#line 1493 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9858 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 800:
#line 1493 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-1].cppDtorObj);
                    (yyval.cppDtorObj)->addAttr((yyvsp[-2].attr));
                  }
#line 9867 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 801:
#line 1497 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9873 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 802:
#line 1498 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-2].cppDtorObj);
                    (yyval.cppDtorObj)->addAttr((yyvsp[-1].attr));
                  }
#line 9882 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 803:
#line 1502 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9888 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 804:
#line 1503 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-3].cppDtorObj);
                    (yyval.cppDtorObj)->addAttr(kPureVirtual);
                  }
#line 9897 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 805:
#line 1507 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9903 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 806:
#line 1507 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-3].cppDtorObj);
                    (yyval.cppDtorObj)->addAttr(kDelete);
                  }
#line 9912 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 807:
#line 1511 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9918 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 808:
#line 1511 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-3].cppDtorObj);
                    (yyval.cppDtorObj)->addAttr(kDefault);
                  }
#line 9927 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 809:
#line 1515 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9933 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 810:
#line 1515 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppDtorObj) = (yyvsp[-2].cppDtorObj);
                    (yyval.cppDtorObj)->throwSpec((yyvsp[-1].funcThrowSpec));
                  }
#line 9942 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 811:
#line 1521 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9948 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 812:
#line 1522 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9954 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 813:
#line 1525 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 9960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 814:
#line 1525 "parser.y" /* yacc.c:1646  */
    {
                  }
#line 9967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 815:
#line 1527 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 816:
#line 1527 "parser.y" /* yacc.c:1646  */
    {
                  }
#line 9980 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 817:
#line 1531 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 9986 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 818:
#line 1531 "parser.y" /* yacc.c:1646  */
    { (yyval.cppCompundObj) = (yyvsp[-2].cppCompundObj);}
#line 9992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 819:
#line 1535 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    ZZVALID;
                    gCompoundStack.push(classNameFromIdentifier($3));
                    gAccessTypeStack.push(gCurAccessType); gCurAccessType = CppAccessType::kUnknown;
                  ] ToYacc*/}
#line 10002 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 820:
#line 1541 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    ZZVALID;
                    gCompoundStack.pop();
                    gCurAccessType = gAccessTypeStack.top();
                    gAccessTypeStack.pop();
                  ] ToYacc*/}
#line 10013 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 821:
#line 1547 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = (yyvsp[-2].cppCompundObj) ? (yyvsp[-2].cppCompundObj) : newCompound(gCurAccessType);
                    (yyval.cppCompundObj)->compoundType((yyvsp[-10].compoundType));
                    (yyval.cppCompundObj)->apidecor((yyvsp[-9].str));
                    (yyval.cppCompundObj)->name(pruneClassName((yyvsp[-8].str)));
                    (yyval.cppCompundObj)->inheritanceList((yyvsp[-6].inheritList));
                    (yyval.cppCompundObj)->addAttr((yyvsp[-7].attr));
                  }
#line 10026 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 822:
#line 1556 "parser.y" /* yacc.c:1646  */
    { gAccessTypeStack.push(gCurAccessType); gCurAccessType = CppAccessType::kUnknown; }
#line 10032 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 823:
#line 1558 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10038 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 824:
#line 1559 "parser.y" /* yacc.c:1646  */
    {
                    gCurAccessType = gAccessTypeStack.top();
                    gAccessTypeStack.pop();

                    (yyval.cppCompundObj) = (yyvsp[-2].cppCompundObj) ? (yyvsp[-2].cppCompundObj) : newCompound(gCurAccessType);
                    (yyval.cppCompundObj)->compoundType((yyvsp[-7].compoundType));
                    (yyval.cppCompundObj)->inheritanceList((yyvsp[-6].inheritList));
                  }
#line 10051 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 825:
#line 1567 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 826:
#line 1568 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = (yyvsp[-1].cppCompundObj);
                    (yyval.cppCompundObj)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 10066 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 827:
#line 1575 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    ZZVALID;
                    gCompoundStack.push(classNameFromIdentifier($2));
                    gAccessTypeStack.push(gCurAccessType); gCurAccessType = CppAccessType::kUnknown;
                  ] ToYacc*/}
#line 10076 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 828:
#line 1581 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    ZZVALID;
                    gCompoundStack.pop();
                    gCurAccessType = gAccessTypeStack.top();
                    gAccessTypeStack.pop();
                  ] ToYacc*/}
#line 10087 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 829:
#line 1587 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.cppCompundObj) = (yyvsp[-2].cppCompundObj) ? (yyvsp[-2].cppCompundObj) : newCompound(gCurAccessType);
                    (yyval.cppCompundObj)->compoundType(CppCompoundType::kNamespace);
                    (yyval.cppCompundObj)->name((yyvsp[-5].str));
                  }
#line 10097 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 830:
#line 1594 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10103 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 831:
#line 1594 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = 0; }
#line 10109 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 832:
#line 1595 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10115 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 833:
#line 1595 "parser.y" /* yacc.c:1646  */
    { (yyval.attr) = kFinal; }
#line 10121 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 834:
#line 1598 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10127 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 835:
#line 1598 "parser.y" /* yacc.c:1646  */
    { (yyval.inheritList) = 0; }
#line 10133 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 836:
#line 1599 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10139 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 837:
#line 1599 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.inheritList) = new CppInheritanceList; (yyval.inheritList)->push_back(CppInheritInfo((std::string) (yyvsp[-1].str), (yyvsp[-3].objAccessType), (yyvsp[-2].inheritType)));
                  }
#line 10147 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 838:
#line 1602 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10153 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 839:
#line 1602 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.inheritList) = (yyvsp[-5].inheritList); (yyval.inheritList)->push_back(CppInheritInfo((std::string) (yyvsp[-1].str), (yyvsp[-3].objAccessType), (yyvsp[-2].inheritType)));
                  }
#line 10161 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 840:
#line 1605 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10167 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 841:
#line 1605 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.inheritList) = new CppInheritanceList; (yyval.inheritList)->push_back(CppInheritInfo((std::string) (yyvsp[-1].str), (yyvsp[-2].objAccessType), (yyvsp[-3].inheritType)));
                  }
#line 10175 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 842:
#line 1608 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10181 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 843:
#line 1608 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.inheritList) = (yyvsp[-5].inheritList); (yyval.inheritList)->push_back(CppInheritInfo((std::string) (yyvsp[-1].str), (yyvsp[-2].objAccessType), (yyvsp[-3].inheritType)));
                  }
#line 10189 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 844:
#line 1613 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10195 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 845:
#line 1613 "parser.y" /* yacc.c:1646  */
    { (yyval.objAccessType) = CppAccessType::kUnknown;    }
#line 10201 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 846:
#line 1614 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10207 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 847:
#line 1614 "parser.y" /* yacc.c:1646  */
    { (yyval.objAccessType) = CppAccessType::kPublic;     }
#line 10213 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 848:
#line 1615 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10219 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 849:
#line 1615 "parser.y" /* yacc.c:1646  */
    { (yyval.objAccessType) = CppAccessType::kProtected;  }
#line 10225 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 850:
#line 1616 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10231 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 851:
#line 1616 "parser.y" /* yacc.c:1646  */
    { (yyval.objAccessType) = CppAccessType::kPrivate;    }
#line 10237 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 852:
#line 1619 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10243 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 853:
#line 1619 "parser.y" /* yacc.c:1646  */
    { (yyval.inheritType) = false; }
#line 10249 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 854:
#line 1620 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10255 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 855:
#line 1620 "parser.y" /* yacc.c:1646  */
    { (yyval.inheritType) = true; }
#line 10261 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 856:
#line 1623 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10267 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 857:
#line 1623 "parser.y" /* yacc.c:1646  */
    { (yyval.fwdDeclObj) = new CppFwdClsDecl(gCurAccessType, (yyvsp[-2].str), (yyvsp[-3].compoundType)); }
#line 10273 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 858:
#line 1624 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10279 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 859:
#line 1624 "parser.y" /* yacc.c:1646  */
    { (yyval.fwdDeclObj) = new CppFwdClsDecl(gCurAccessType, (yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[-4].compoundType)); }
#line 10285 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 860:
#line 1625 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10291 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 861:
#line 1625 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.fwdDeclObj) = (yyvsp[-1].fwdDeclObj);
                    (yyval.fwdDeclObj)->templateParamList((yyvsp[-2].templateParamList));
                  }
#line 10300 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 862:
#line 1629 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10306 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 863:
#line 1629 "parser.y" /* yacc.c:1646  */
    { (yyval.fwdDeclObj) = new CppFwdClsDecl(gCurAccessType, (yyvsp[-2].str)); (yyval.fwdDeclObj)->addAttr(kFriend); }
#line 10312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 864:
#line 1630 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10318 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 865:
#line 1630 "parser.y" /* yacc.c:1646  */
    { (yyval.fwdDeclObj) = (yyvsp[-1].fwdDeclObj); (yyval.fwdDeclObj)->addAttr(kFriend); }
#line 10324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 866:
#line 1633 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 867:
#line 1633 "parser.y" /* yacc.c:1646  */
    { (yyval.compoundType) = CppCompoundType::kClass;     }
#line 10336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 868:
#line 1634 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 869:
#line 1634 "parser.y" /* yacc.c:1646  */
    { (yyval.compoundType) = CppCompoundType::kStruct;    }
#line 10348 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 870:
#line 1635 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10354 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 871:
#line 1635 "parser.y" /* yacc.c:1646  */
    { (yyval.compoundType) = CppCompoundType::kUnion;     }
#line 10360 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 872:
#line 1638 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gInTemplateSpec = true;  ZZLOG;   ] ToYacc*/}
#line 10366 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 873:
#line 1639 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [gInTemplateSpec = false; ZZVALID; ] ToYacc*/}
#line 10372 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 874:
#line 1640 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParamList) = (yyvsp[-2].templateParamList);
                  }
#line 10380 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 875:
#line 1645 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10386 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 876:
#line 1645 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParamList) = new CppTemplateParamList;
                  }
#line 10394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 877:
#line 1648 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10400 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 878:
#line 1648 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParamList) = new CppTemplateParamList;
                    (yyval.templateParamList)->emplace_back((yyvsp[-1].templateParam));
                  }
#line 10409 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 879:
#line 1652 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10415 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 880:
#line 1652 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParamList) = (yyvsp[-3].templateParamList);
                    (yyval.templateParamList)->emplace_back((yyvsp[-1].templateParam));
                  }
#line 10424 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 881:
#line 1658 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 882:
#line 1658 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-1].str));
                  }
#line 10438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 883:
#line 1661 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 884:
#line 1661 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-3].str));
                    (yyval.templateParam)->defaultArg((yyvsp[-1].cppVarType));
                  }
#line 10453 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 885:
#line 1665 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10459 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 886:
#line 1665 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-1].str));
                  }
#line 10467 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 887:
#line 1668 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10473 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 888:
#line 1668 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-3].str));
                    (yyval.templateParam)->defaultArg((yyvsp[-1].cppVarType));
                  }
#line 10482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 889:
#line 1672 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10488 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 890:
#line 1672 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-2].cppVarType), (yyvsp[-1].str));
                  }
#line 10496 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 891:
#line 1675 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10502 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 892:
#line 1675 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-4].cppVarType), (yyvsp[-3].str));
                    (yyval.templateParam)->defaultArg((yyvsp[-1].cppExprObj));
                  }
#line 10511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 893:
#line 1679 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 894:
#line 1679 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-1].cppFuncPointerObj), std::string());
                  }
#line 10525 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 895:
#line 1682 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10531 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 896:
#line 1682 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-3].cppFuncPointerObj), std::string());
                    (yyval.templateParam)->defaultArg((yyvsp[-1].cppExprObj));
                  }
#line 10540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 897:
#line 1686 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 898:
#line 1686 "parser.y" /* yacc.c:1646  */
    { // Can happen when forward declaring
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-1].cppVarType), std::string());
                  }
#line 10554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 899:
#line 1689 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 900:
#line 1689 "parser.y" /* yacc.c:1646  */
    { // Can happen when forward declaring
                    (yyval.templateParam) = new CppTemplateParam((yyvsp[-3].cppVarType), std::string());
                    (yyval.templateParam)->defaultArg((yyvsp[-1].cppExprObj));
                  }
#line 10569 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 901:
#line 1694 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] ToYacc*/}
#line 10579 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 902:
#line 1698 "parser.y" /* yacc.c:1646  */
    { (yyval.templateParam) = nullptr; }
#line 10585 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 903:
#line 1699 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] ToYacc*/}
#line 10595 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 904:
#line 1703 "parser.y" /* yacc.c:1646  */
    { (yyval.templateParam) = nullptr; }
#line 10601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 905:
#line 1704 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] ToYacc*/}
#line 10611 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 906:
#line 1708 "parser.y" /* yacc.c:1646  */
    { (yyval.templateParam) = nullptr; }
#line 10617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 907:
#line 1709 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] ToYacc*/}
#line 10627 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 908:
#line 1713 "parser.y" /* yacc.c:1646  */
    { (yyval.templateParam) = nullptr; }
#line 10633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 909:
#line 1714 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                    if (gInTemplateSpec)
                      gTemplateParamStart = $1.sz;
                    ZZERROR;
                  ] ToYacc*/}
#line 10643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 910:
#line 1718 "parser.y" /* yacc.c:1646  */
    { (yyval.templateParam) = nullptr; }
#line 10649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 911:
#line 1722 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10655 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 912:
#line 1722 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = makeCppToken(nullptr, nullptr); }
#line 10661 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 913:
#line 1723 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10667 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 914:
#line 1723 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 10673 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 915:
#line 1726 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 916:
#line 1726 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 10685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 917:
#line 1727 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10691 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 918:
#line 1727 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 10697 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 919:
#line 1728 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10703 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 920:
#line 1728 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-4].str), (yyvsp[-1].str)); }
#line 10709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 921:
#line 1729 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10715 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 922:
#line 1729 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 10721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 923:
#line 1732 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 924:
#line 1732 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 10733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 925:
#line 1733 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10739 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 926:
#line 1733 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 10745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 927:
#line 1736 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10751 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 928:
#line 1736 "parser.y" /* yacc.c:1646  */
    { (yyval.objAccessType) = CppAccessType::kPublic;     }
#line 10757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 929:
#line 1737 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10763 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 930:
#line 1737 "parser.y" /* yacc.c:1646  */
    { (yyval.objAccessType) = CppAccessType::kProtected;  }
#line 10769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 931:
#line 1738 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10775 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 932:
#line 1738 "parser.y" /* yacc.c:1646  */
    { (yyval.objAccessType) = CppAccessType::kPrivate;    }
#line 10781 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 933:
#line 1741 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZVALID;] ToYacc*/}
#line 10787 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 934:
#line 1741 "parser.y" /* yacc.c:1646  */
    {(yyval.cppCompundObj) = (yyvsp[-1].cppCompundObj); (yyval.cppCompundObj)->compoundType(CppCompoundType::kExternCBlock); }
#line 10793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 935:
#line 1744 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 936:
#line 1744 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = (yyvsp[-1].str); }
#line 10805 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 937:
#line 1745 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10811 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 938:
#line 1745 "parser.y" /* yacc.c:1646  */
    { (yyval.str) = mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str)); }
#line 10817 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 939:
#line 1748 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10823 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 940:
#line 1748 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((std::string) (yyvsp[-1].str), kNone);          }
#line 10829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 941:
#line 1749 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 942:
#line 1749 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((std::string) (yyvsp[-1].str), kNone);          }
#line 10841 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 943:
#line 1750 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 944:
#line 1750 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((std::string) (yyvsp[-1].str), kNone);          }
#line 10853 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 945:
#line 1751 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 946:
#line 1751 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((std::string) (yyvsp[-1].str), kNone);          }
#line 10865 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 947:
#line 1753 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                      if ($1.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ] ToYacc*/}
#line 10878 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 948:
#line 1760 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10884 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 949:
#line 1760 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((std::string) (yyvsp[-2].str), kNone);          }
#line 10890 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 950:
#line 1761 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10896 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 951:
#line 1761 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppExprObj), CppExpr::kInitializer);        }
#line 10902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 952:
#line 1762 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10908 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 953:
#line 1762 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), CppExpr::kInitializer);        }
#line 10914 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 954:
#line 1763 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10920 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 955:
#line 1763 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppExprObj), CppExpr::kInitializer);        }
#line 10926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 956:
#line 1764 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10932 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 957:
#line 1764 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), CppExpr::kInitializer);        }
#line 10938 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 958:
#line 1765 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 959:
#line 1765 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((CppExpr*)nullptr, CppExpr::kInitializer);   }
#line 10950 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 960:
#line 1766 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10956 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 961:
#line 1766 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), kUnaryMinus);                  }
#line 10962 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 962:
#line 1767 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10968 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 963:
#line 1767 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), kBitToggle);                   }
#line 10974 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 964:
#line 1768 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10980 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 965:
#line 1768 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), kLogNot);                      }
#line 10986 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 966:
#line 1769 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 10992 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 967:
#line 1769 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), kDerefer);                     }
#line 10998 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 968:
#line 1770 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11004 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 969:
#line 1770 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), kRefer);                       }
#line 11010 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 970:
#line 1771 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11016 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 971:
#line 1771 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr(CppExprAtom((yyvsp[-1].str)), kRefer);          }
#line 11022 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 972:
#line 1772 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11028 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 973:
#line 1772 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), kPreIncrement);                }
#line 11034 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 974:
#line 1773 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11040 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 975:
#line 1773 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppExprObj), kPostIncrement);               }
#line 11046 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 976:
#line 1774 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11052 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 977:
#line 1774 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), kPreDecrement);                }
#line 11058 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 978:
#line 1775 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 979:
#line 1775 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppExprObj), kPostDecrement);               }
#line 11070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 980:
#line 1776 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11076 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 981:
#line 1776 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kPlus, (yyvsp[-1].cppExprObj));                    }
#line 11082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 982:
#line 1777 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11088 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 983:
#line 1777 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kMinus, (yyvsp[-1].cppExprObj));                   }
#line 11094 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 984:
#line 1779 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                      if ($2.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ] ToYacc*/}
#line 11107 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 985:
#line 1786 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11113 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 986:
#line 1786 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-4].cppExprObj), kMul, (yyvsp[-2].cppExprObj));                     }
#line 11119 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 987:
#line 1787 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11125 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 988:
#line 1787 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kDiv, (yyvsp[-1].cppExprObj));                     }
#line 11131 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 989:
#line 1788 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11137 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 990:
#line 1788 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kPercent, (yyvsp[-1].cppExprObj));                 }
#line 11143 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 991:
#line 1790 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                      if ($2.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ] ToYacc*/}
#line 11156 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 992:
#line 1797 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11162 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 993:
#line 1797 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-4].cppExprObj), kBitAnd, (yyvsp[-2].cppExprObj));                  }
#line 11168 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 994:
#line 1798 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11174 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 995:
#line 1798 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kBitOr, (yyvsp[-1].cppExprObj));                   }
#line 11180 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 996:
#line 1799 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11186 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 997:
#line 1799 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kXor, (yyvsp[-1].cppExprObj));                     }
#line 11192 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 998:
#line 1800 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11198 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 999:
#line 1800 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kEqual, (yyvsp[-1].cppExprObj));                   }
#line 11204 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1000:
#line 1801 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11210 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1001:
#line 1801 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kLess, (yyvsp[-1].cppExprObj));                    }
#line 11216 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1002:
#line 1802 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11222 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1003:
#line 1802 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kGreater, (yyvsp[-1].cppExprObj));                 }
#line 11228 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1004:
#line 1803 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11234 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1005:
#line 1803 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-5].cppExprObj), (yyvsp[-3].cppExprObj), (yyvsp[-1].cppExprObj));                       }
#line 11240 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1006:
#line 1804 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11246 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1007:
#line 1804 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kPlusEqual, (yyvsp[-1].cppExprObj));               }
#line 11252 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1008:
#line 1805 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11258 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1009:
#line 1805 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kMinusEqual, (yyvsp[-1].cppExprObj));              }
#line 11264 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1010:
#line 1806 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11270 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1011:
#line 1806 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kMulEqual, (yyvsp[-1].cppExprObj));                }
#line 11276 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1012:
#line 1807 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11282 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1013:
#line 1807 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kDivEqual, (yyvsp[-1].cppExprObj));                }
#line 11288 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1014:
#line 1808 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11294 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1015:
#line 1808 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kPerEqual, (yyvsp[-1].cppExprObj));                }
#line 11300 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1016:
#line 1809 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11306 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1017:
#line 1809 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kXorEqual, (yyvsp[-1].cppExprObj));                }
#line 11312 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1018:
#line 1810 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11318 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1019:
#line 1810 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kAndEqual, (yyvsp[-1].cppExprObj));                }
#line 11324 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1020:
#line 1811 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11330 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1021:
#line 1811 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kOrEqual, (yyvsp[-1].cppExprObj));                 }
#line 11336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1022:
#line 1812 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1023:
#line 1812 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kLeftShift, (yyvsp[-1].cppExprObj));               }
#line 11348 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1024:
#line 1813 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11354 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1025:
#line 1813 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kRightShift, (yyvsp[-1].cppExprObj));              }
#line 11360 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1026:
#line 1814 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11366 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1027:
#line 1814 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kLShiftEqual, (yyvsp[-1].cppExprObj));             }
#line 11372 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1028:
#line 1815 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11378 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1029:
#line 1815 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kRShiftEqual, (yyvsp[-1].cppExprObj));             }
#line 11384 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1030:
#line 1816 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11390 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1031:
#line 1816 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kCmpEqual, (yyvsp[-1].cppExprObj));                }
#line 11396 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1032:
#line 1817 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11402 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1033:
#line 1817 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kNotEqual, (yyvsp[-1].cppExprObj));                }
#line 11408 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1034:
#line 1818 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11414 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1035:
#line 1818 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kLessEqual, (yyvsp[-1].cppExprObj));               }
#line 11420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1036:
#line 1819 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11426 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1037:
#line 1819 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kGreaterEqual, (yyvsp[-1].cppExprObj));            }
#line 11432 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1038:
#line 1820 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1039:
#line 1820 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), k3WayCmp, (yyvsp[-1].cppExprObj));                 }
#line 11444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1040:
#line 1822 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [
                      if ($2.sz == gParamModPos) {
                        gParamModPos = nullptr;
                        ZZERROR;
                      } else {
                        ZZLOG;
                      }
                    ] ToYacc*/}
#line 11457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1041:
#line 1829 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11463 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1042:
#line 1829 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-4].cppExprObj), kAnd, (yyvsp[-2].cppExprObj));                     }
#line 11469 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1043:
#line 1830 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11475 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1044:
#line 1830 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kOr, (yyvsp[-1].cppExprObj));                      }
#line 11481 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1045:
#line 1831 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11487 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1046:
#line 1831 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kDot, CppExprAtom((yyvsp[-1].str)));                     }
#line 11493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1047:
#line 1832 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11499 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1048:
#line 1832 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kArrow, CppExprAtom((yyvsp[-1].str)));      }
#line 11505 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1049:
#line 1833 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1050:
#line 1833 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kArrowStar, CppExprAtom((yyvsp[-1].str)));  }
#line 11517 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1051:
#line 1834 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1052:
#line 1834 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-4].cppExprObj), kDot, CppExprAtom(mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str))));                     }
#line 11529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1053:
#line 1835 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11535 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1054:
#line 1835 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-4].cppExprObj), kArrow, CppExprAtom(mergeCppToken((yyvsp[-2].str), (yyvsp[-1].str))));      }
#line 11541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1055:
#line 1836 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11547 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1056:
#line 1836 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-4].cppExprObj), kArrayElem, (yyvsp[-2].cppExprObj));               }
#line 11553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1057:
#line 1837 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1058:
#line 1837 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kArrayElem);                   }
#line 11565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1059:
#line 1838 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11571 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1060:
#line 1838 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-4].cppExprObj), kFunctionCall, (yyvsp[-2].cppExprObj));            }
#line 11577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1061:
#line 1839 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1062:
#line 1839 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr(CppExprAtom((yyvsp[-4].str)), kFunctionCall, (yyvsp[-2].cppExprObj));            }
#line 11589 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1063:
#line 1840 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11595 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1064:
#line 1840 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr(new CppExpr((yyvsp[-6].cppExprObj), kArrow, CppExprAtom(mergeCppToken((yyvsp[-4].str), (yyvsp[-3].str)))), kFunctionCall, (CppExpr*)nullptr); }
#line 11601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1065:
#line 1842 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11607 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1066:
#line 1842 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr(new CppExpr((std::string) (yyvsp[-4].str), kNone), kFunctionCall, (yyvsp[-2].cppExprObj));            }
#line 11613 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1067:
#line 1843 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11619 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1068:
#line 1843 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppVarType), kCStyleCast, (yyvsp[-1].cppExprObj));              }
#line 11625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1069:
#line 1844 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1070:
#line 1844 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-5].cppVarType), kConstCast, (yyvsp[-2].cppExprObj));               }
#line 11637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1071:
#line 1845 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11643 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1072:
#line 1845 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-5].cppVarType), kStaticCast, (yyvsp[-2].cppExprObj));              }
#line 11649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1073:
#line 1846 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11655 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1074:
#line 1846 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-5].cppVarType), kDynamicCast, (yyvsp[-2].cppExprObj));             }
#line 11661 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1075:
#line 1847 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11667 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1076:
#line 1847 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-5].cppVarType), kReinterpretCast, (yyvsp[-2].cppExprObj));         }
#line 11673 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1077:
#line 1848 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1078:
#line 1848 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-2].cppExprObj); (yyvsp[-2].cppExprObj)->flags_ |= CppExpr::kBracketed;         }
#line 11685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1079:
#line 1849 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11691 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1080:
#line 1849 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((std::string) (yyvsp[-1].str), CppExpr::kNew);  }
#line 11697 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1081:
#line 1850 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11703 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1082:
#line 1850 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppExprObj), CppExpr::kNew);  }
#line 11709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1083:
#line 1851 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11715 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1084:
#line 1851 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kPlacementNew, (yyvsp[-1].cppExprObj));            }
#line 11721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1085:
#line 1852 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1086:
#line 1852 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kPlacementNew, (yyvsp[-1].cppExprObj));            }
#line 11733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1087:
#line 1853 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11739 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1088:
#line 1853 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); (yyvsp[-1].cppExprObj)->flags_ |= CppExpr::kDelete;            }
#line 11745 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1089:
#line 1854 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11751 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1090:
#line 1854 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); (yyvsp[-1].cppExprObj)->flags_ |= CppExpr::kDeleteArray;       }
#line 11757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1091:
#line 1855 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11763 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1092:
#line 1855 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); (yyvsp[-1].cppExprObj)->flags_ |= CppExpr::kReturn;            }
#line 11769 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1093:
#line 1856 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11775 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1094:
#line 1856 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr(CppExprAtom(), CppExpr::kReturn);  }
#line 11781 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1095:
#line 1857 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11787 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1096:
#line 1857 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); (yyvsp[-1].cppExprObj)->flags_ |= CppExpr::kThrow;             }
#line 11793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1097:
#line 1858 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11799 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1098:
#line 1858 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr(CppExprAtom(), CppExpr::kThrow);   }
#line 11805 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1099:
#line 1859 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11811 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1100:
#line 1859 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppVarType), CppExpr::kSizeOf);             }
#line 11817 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1101:
#line 1860 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11823 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1102:
#line 1860 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppExprObj), CppExpr::kSizeOf);             }
#line 11829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1103:
#line 1861 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11835 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1104:
#line 1861 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppVarType), CppExpr::kSizeOf | CppExpr::kVariadicPack);             }
#line 11841 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1105:
#line 1862 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11847 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1106:
#line 1862 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-2].cppExprObj), CppExpr::kSizeOf | CppExpr::kVariadicPack);             }
#line 11853 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1107:
#line 1863 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11859 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1108:
#line 1863 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-2].cppExprObj); (yyval.cppExprObj)->flags_ |= CppExpr::kVariadicPack; }
#line 11865 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1109:
#line 1864 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11871 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1110:
#line 1864 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-1].cppLambda)); }
#line 11877 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1111:
#line 1867 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11883 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1112:
#line 1867 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((std::string) (yyvsp[-2].str), kNone);          }
#line 11889 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1113:
#line 1870 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11895 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1114:
#line 1870 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kComma, (yyvsp[-1].cppExprObj));                   }
#line 11901 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1115:
#line 1871 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11907 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1116:
#line 1871 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr((yyvsp[-3].cppExprObj), kComma, (yyvsp[-1].cppExprObj));                   }
#line 11913 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1117:
#line 1872 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11919 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1118:
#line 1872 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); }
#line 11925 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1119:
#line 1875 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11931 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1120:
#line 1875 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); }
#line 11937 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1121:
#line 1876 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11943 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1122:
#line 1876 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); }
#line 11949 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1123:
#line 1877 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11955 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1124:
#line 1877 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj); }
#line 11961 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1125:
#line 1880 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1126:
#line 1880 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = nullptr; }
#line 11973 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1127:
#line 1881 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1128:
#line 1881 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-1].cppExprObj);      }
#line 11985 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1129:
#line 1884 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 11991 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1130:
#line 1884 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr("", kRefer); }
#line 11997 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1131:
#line 1887 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 12003 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1132:
#line 1887 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = new CppExpr("", kEqual, ""); }
#line 12009 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1133:
#line 1890 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 12015 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1134:
#line 1891 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 12021 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1135:
#line 1892 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 12027 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1136:
#line 1895 "parser.y" /* yacc.c:1646  */
    {/*ToYacc [ZZLOG;] ToYacc*/}
#line 12033 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 1137:
#line 1895 "parser.y" /* yacc.c:1646  */
    { (yyval.cppExprObj) = (yyvsp[-2].cppExprObj); }
#line 12039 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 12043 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1898 "parser.y" /* yacc.c:1906  */


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
    extern int gLexLog;

    gParseLog = ((yyn & kParseLog) ? 1 : 0);
    gLexLog   = ((yyn & kLexLog)   ? 1 : 0);
    yydebug   = ((yyn & kYaccLog)  ? 1 : 0);
  }
#endif
}

CppCompoundPtr parseStream(char* stm, size_t stmSize)
{
  setupEnv();

  gProgUnit = nullptr;
  gCurAccessType = CppAccessType::kUnknown;
  
  void setupScanBuffer(char* buf, size_t bufsize);
  void cleanupScanBuffer();
  setupScanBuffer(stm, stmSize);
  gLineNo = 1; // Reset so that we do not start counting beyond previous parsing.
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
