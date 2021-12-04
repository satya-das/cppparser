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
#define tknLShiftEq 314
#define tknRShiftEq 315
#define tknCmpEq 316
#define tknNotEq 317
#define tknLessEq 318
#define tknGreaterEq 319
#define tkn3WayCmp 320
#define tknAnd 321
#define tknOr 322
#define tknInc 323
#define tknDec 324
#define tknArrow 325
#define tknArrowStar 326
#define tknLT 327
#define tknGT 328
#define tknNew 329
#define tknDelete 330
#define tknConst 331
#define tknConstExpr 332
#define tknVoid 333
#define tknOverride 334
#define tknFinal 335
#define tknAsm 336
#define tknBlob 337
#define tknGoto 338
#define tknStatic 339
#define tknExtern 340
#define tknVirtual 341
#define tknInline 342
#define tknExplicit 343
#define tknFriend 344
#define tknVolatile 345
#define tknMutable 346
#define tknNoExcept 347
#define tknPreProHash 348
#define tknDefine 349
#define tknUndef 350
#define tknInclude 351
#define tknImport 352
#define tknIf 353
#define tknIfDef 354
#define tknIfNDef 355
#define tknElse 356
#define tknElIf 357
#define tknEndIf 358
#define tknFor 359
#define tknWhile 360
#define tknDo 361
#define tknSwitch 362
#define tknCase 363
#define tknDefault 364
#define tknReturn 365
#define tknBlankLine 366
#define COMMA 367
#define TERNARYCOND 368
#define RSHIFT 369
#define PREINCR 370
#define PREDECR 371
#define UNARYMINUS 372
#define CSTYLECAST 373
#define DEREF 374
#define ADDRESSOF 375
#define POSTINCR 376
#define POSTDECR 377
#define FUNCTIONALCAST 378
#define FUNCCALL 379
#define SUBSCRIPT 380
#define GLOBAL 381
#define TEMPLATE 382
#define PTRDECL 383
#define REFDECL 384
#define CTORDECL 385
#define DTORDECL 386
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
