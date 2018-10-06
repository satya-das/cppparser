#ifndef __home_dassat_github_cppparser_parser_tab_h_
#define __home_dassat_github_cppparser_parser_tab_h_

#define tknID 257
#define tknStrLit 258
#define tknCharLit 259
#define tknNumber 260
#define tknMacro 261
#define tknApiDecor 262
#define tknTypedef 263
#define tknUsing 264
#define tknLong 265
#define tknEnum 266
#define tknPreProDef 267
#define tknClass 268
#define tknStruct 269
#define tknUnion 270
#define tknNamespace 271
#define tknTemplate 272
#define tknTypename 273
#define tknDocBlockComment 274
#define tknDocLineComment 275
#define tknScopeResOp 276
#define tknNumSignSpec 277
#define tknPublic 278
#define tknProtected 279
#define tknPrivate 280
#define tknExternC 281
#define tknUnRecogPrePro 282
#define tknStdHdrInclude 283
#define tknPragma 284
#define tknHashError 285
#define tknEllipsis 286
#define tknConstCast 287
#define tknStaticCast 288
#define tknDynamicCast 289
#define tknReinterpretCast 290
#define tknTry 291
#define tknCatch 292
#define tknThrow 293
#define tknSizeOf 294
#define tknOperator 295
#define tknPlusEq 296
#define tknMinusEq 297
#define tknMulEq 298
#define tknDivEq 299
#define tknPerEq 300
#define tknXorEq 301
#define tknAndEq 302
#define tknOrEq 303
#define tknLShift 304
#define tknRShift 305
#define tknLShiftEq 306
#define tknRShiftEq 307
#define tknCmpEq 308
#define tknNotEq 309
#define tknLessEq 310
#define tknGreaterEq 311
#define tkn3WayCmp 312
#define tknAnd 313
#define tknOr 314
#define tknInc 315
#define tknDec 316
#define tknArrow 317
#define tknArrowStar 318
#define tknNew 319
#define tknDelete 320
#define tknConst 321
#define tknConstExpr 322
#define tknVoid 323
#define tknOverride 324
#define tknStatic 325
#define tknExtern 326
#define tknVirtual 327
#define tknInline 328
#define tknExplicit 329
#define tknFriend 330
#define tknVolatile 331
#define tknFinal 332
#define tknNoExcept 333
#define tknPreProHash 334
#define tknDefine 335
#define tknUndef 336
#define tknInclude 337
#define tknIf 338
#define tknIfDef 339
#define tknIfNDef 340
#define tknElse 341
#define tknElIf 342
#define tknEndIf 343
#define tknFor 344
#define tknWhile 345
#define tknDo 346
#define tknSwitch 347
#define tknCase 348
#define tknDefault 349
#define tknReturn 350
#define tknBlankLine 351
#define TERNARYCOND 352
#define PREINCR 353
#define PREDECR 354
#define UNARYMINUS 355
#define CSTYLECAST 356
#define DEREF 357
#define ADDRESSOF 358
#define POSTINCR 359
#define POSTDECR 360
#define FUNCTIONALCAST 361
#define FUNCCALL 362
#define SUBSCRIPT 363
#define GLOBAL 364
#define PTRDECL 365
#define REFDECL 366
#define CTORDECL 367
#define DTORDECL 368
#define YYERRCODE 256

#line 97 "/home/dassat/github/cppparser/parser.y"
typedef union {
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
  CppTypeCoverter*      cppTypeConverter;
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
} YYSTYPE;
#define YYSTYPE YYSTYPE
extern YYSTYPE yylval;
#if defined(YYPOSN)
extern YYPOSN yyposn;
#endif

#endif
