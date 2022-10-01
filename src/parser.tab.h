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
#define tknTLT 368
#define tknTGT 369
#define templatespecificationstart 370
#define templatespecificationend 371
#define COMMA 372
#define TERNARYCOND 373
#define PREINCR 374
#define PREDECR 375
#define UNARYMINUS 376
#define CSTYLECAST 377
#define DEREF 378
#define ADDRESSOF 379
#define POSTINCR 380
#define POSTDECR 381
#define FUNCTIONALCAST 382
#define FUNCCALL 383
#define SUBSCRIPT 384
#define GLOBAL 385
#define TEMPLATE 386
#define PTRDECL 387
#define REFDECL 388
#define CTORDECL 389
#define DTORDECL 390
#define YYERRCODE 256

#line 166 "/home/dassat/github/cppparser/src/parser.y"
typedef union {
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
  CppMemInits             memInitList;
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

  CppExpr*                attribSpecifier;
  AttribSpecifierArray*   attribSpecifiers;

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

  CppLabel*               label;
} YYSTYPE;
#define YYSTYPE YYSTYPE
extern YYSTYPE yylval;
#if defined(YYPOSN)
extern YYPOSN yyposn;
#endif

#endif
