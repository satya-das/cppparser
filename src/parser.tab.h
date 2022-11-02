#ifndef _parser_tab_h_
#define _parser_tab_h_

#define tknName 257
#define tknID 258
#define tknStrLit 259
#define tknCharLit 260
#define tknNumber 261
#define tknMacro 262
#define tknApiDecor 263
#define tknTypedef 264
#define tknUsing 265
#define tknInteger 266
#define tknChar 267
#define tknDouble 268
#define tknFloat 269
#define tknEnum 270
#define tknAuto 271
#define tknPreProDef 272
#define tknClass 273
#define tknStruct 274
#define tknUnion 275
#define tknNamespace 276
#define tknTemplate 277
#define tknTypename 278
#define tknDecltype 279
#define tknFreeStandingBlockComment 280
#define tknSideBlockComment 281
#define tknFreeStandingLineComment 282
#define tknSideLineComment 283
#define tknScopeResOp 284
#define tknNumSignSpec 285
#define tknPublic 286
#define tknProtected 287
#define tknPrivate 288
#define tknExternC 289
#define tknUnRecogPrePro 290
#define tknStdHdrInclude 291
#define tknPragma 292
#define tknHashError 293
#define tknHashWarning 294
#define tknEllipsis 295
#define tknConstCast 296
#define tknStaticCast 297
#define tknDynamicCast 298
#define tknReinterpretCast 299
#define tknTry 300
#define tknCatch 301
#define tknThrow 302
#define tknSizeOf 303
#define tknOperator 304
#define tknPlusEq 305
#define tknMinusEq 306
#define tknMulEq 307
#define tknDivEq 308
#define tknPerEq 309
#define tknXorEq 310
#define tknAndEq 311
#define tknOrEq 312
#define tknLShift 313
#define tknRShift 314
#define tknLShiftEq 315
#define tknRShiftEq 316
#define tknCmpEq 317
#define tknNotEq 318
#define tknLessEq 319
#define tknGreaterEq 320
#define tkn3WayCmp 321
#define tknAnd 322
#define tknOr 323
#define tknInc 324
#define tknDec 325
#define tknArrow 326
#define tknArrowStar 327
#define tknLT 328
#define tknGT 329
#define tknNew 330
#define tknDelete 331
#define tknConst 332
#define tknConstExpr 333
#define tknVoid 334
#define tknOverride 335
#define tknFinal 336
#define tknAsm 337
#define tknBlob 338
#define tknGoto 339
#define tknStatic 340
#define tknExtern 341
#define tknVirtual 342
#define tknInline 343
#define tknExplicit 344
#define tknFriend 345
#define tknVolatile 346
#define tknMutable 347
#define tknNoExcept 348
#define tknPreProHash 349
#define tknDefine 350
#define tknUndef 351
#define tknInclude 352
#define tknImport 353
#define tknIf 354
#define tknIfDef 355
#define tknIfNDef 356
#define tknElse 357
#define tknElIf 358
#define tknEndIf 359
#define tknFor 360
#define tknWhile 361
#define tknDo 362
#define tknSwitch 363
#define tknCase 364
#define tknDefault 365
#define tknReturn 366
#define tknBlankLine 367
#define COMMA 368
#define TERNARYCOND 369
#define RSHIFT 370
#define PREINCR 371
#define PREDECR 372
#define UNARYMINUS 373
#define CSTYLECAST 374
#define DEREF 375
#define ADDRESSOF 376
#define POSTINCR 377
#define POSTDECR 378
#define FUNCTIONALCAST 379
#define FUNCCALL 380
#define SUBSCRIPT 381
#define GLOBAL 382
#define TEMPLATE 383
#define PTRDECL 384
#define REFDECL 385
#define CTORDECL 386
#define DTORDECL 387
#define YYERRCODE 256

#line 168 "/home/dassat/github/cppparser/src/parser.y"
typedef union
{
  CppToken          str;
  CppNtFuncDeclData funcDeclData;
  CppNtMemInit      memInit;

  CppAst::CppEntity*                       cppEntity;
  CppAst::CppTypeModifier                  typeModifier;
  CppAst::CppVarType*                      cppVarType;
  CppAst::CppVar*                          cppVarObj;
  CppAst::CppEnum*                         cppEnum;
  CppAst::CppEnumItem*                     enumItem;
  std::list<CppEnumItem>*                  enumItemList;
  CppAst::CppTypedefName*                  typedefName;
  CppAst::CppTypedefList*                  typedefList;
  CppAst::CppUsingDecl*                    usingDecl;
  CppAst::CppUsingNamespaceDecl*           usingNamespaceDecl;
  CppAst::CppNamespaceAlias*               namespaceAlias;
  CppAst::CppCompound*                     cppCompundObj;
  CppAst::CppTemplateParam*                templateParam;
  CppAst::CppTemplateParams*               templateParamList;
  CppAst::CppDocumentationComment*         docCommentObj;
  CppAst::CppForwardClassDecl*             fwdDeclObj;
  CppAst::CppVarList*                      cppVarObjList;
  CppAst::CppVarAssign                     cppVarAssign;
  CppAst::CppUnRecogPrePro*                unRecogPreProObj;
  CppAst::CppExpr*                         cppExprObj;
  CppAst::CppLambda*                       cppLambda;
  CppAst::CppFunction*                     cppFuncObj;
  CppAst::CppFunctionPointer*              cppFuncPointerObj;
  CppAst::CppEntity*                       varOrFuncPtr;
  std::vector<std::unique_ptr<CppEntity>>* paramList;
  CppAst::CppConstructor*                  cppCtorObj;
  CppAst::CppDestructor*                   cppDtorObj;
  CppAst::CppTypeConverter*                cppTypeConverter;
  CppAst::CppMemInits                      memInitList;
  std::list<CppInheritanceInfo>*           inheritList;
  bool                                     inheritType;
  std::vector<std::string>*                identifierList;
  std::vector<std::string>*                funcThrowSpec;
  CppAst::CppTemplateArg*                  templateArg;
  CppAst::CppAsmBlock*                     asmBlock;
  CppAst::CppCompoundType                  compoundType;
  unsigned short                           ptrLevel;
  CppAst::CppRefType                       refType;
  unsigned int                             attr;
  CppAst::CppAccessType                    objAccessType;

  CppAst::CppExpr*              attribSpecifier;
  CppAst::AttribSpecifierArray* attribSpecifiers;

  CppAst::CppIfBlock*       ifBlock;
  CppAst::CppWhileBlock*    whileBlock;
  CppAst::CppDoWhileBlock*  doWhileBlock;
  CppAst::CppForBlock*      forBlock;
  CppAst::CppRangeForBlock* forRangeBlock;
  CppAst::CppSwitchBlock*   switchBlock;
  CppAst::CppSwitchBody*    switchBody;
  CppAst::CppTryBlock*      tryBlock;
  CppAst::CppCatchBlock*    catchBlock;

  CppAst::CppMacroDefinition*         hashDefine;
  CppAst::CppPreprocessorUndef*       hashUndef;
  CppAst::CppPreprocessorInclude*     hashInclude;
  CppAst::CppPreprocessorImport*      hashImport;
  CppAst::CppPreprocessorConditional* hashIf;
  CppAst::CppPreprocessorError*       hashError;
  CppAst::CppPreprocessorWarning*     hashWarning;
  CppAst::CppPreprocessorPragma*      hashPragma;

  CppAst::CppBlob* blob;

  CppAst::CppLabel* label;
} YYSTYPE;
#define YYSTYPE YYSTYPE
extern YYSTYPE yylval;
#if defined(YYPOSN)
extern YYPOSN yyposn;
#endif

#endif
