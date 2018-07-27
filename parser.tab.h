#ifndef _yacc_defines_h_
#define _yacc_defines_h_

#define tknID 257
#define tknStrLit 258
#define tknCharLit 259
#define tknNumber 260
#define tknTypedef 261
#define tknLong 262
#define tknEnum 263
#define tknPreProDef 264
#define tknClass 265
#define tknStruct 266
#define tknUnion 267
#define tknNamespace 268
#define tknTemplate 269
#define tknTypename 270
#define tknDocBlockComment 271
#define tknDocLineComment 272
#define tknScopeResOp 273
#define tknNumSignSpec 274
#define tknPublic 275
#define tknProtected 276
#define tknPrivate 277
#define tknExternC 278
#define tknUnRecogPrePro 279
#define tknStdHdrInclude 280
#define tknPragma 281
#define tknEllipsis 282
#define tknConstCast 283
#define tknStaticCast 284
#define tknDynamicCast 285
#define tknReinterpretCast 286
#define tknTry 287
#define tknCatch 288
#define tknThrow 289
#define tknOperator 290
#define tknPlusEq 291
#define tknMinusEq 292
#define tknMulEq 293
#define tknDivEq 294
#define tknPerEq 295
#define tknXorEq 296
#define tknAndEq 297
#define tknOrEq 298
#define tknLShift 299
#define tknRShift 300
#define tknLShiftEq 301
#define tknRShiftEq 302
#define tknCmpEq 303
#define tknNotEq 304
#define tknLessEq 305
#define tknGreaterEq 306
#define tkn3WayCmp 307
#define tknAnd 308
#define tknOr 309
#define tknInc 310
#define tknDec 311
#define tknArrow 312
#define tknArrowStar 313
#define tknNew 314
#define tknDelete 315
#define tknConst 316
#define tknVoid 317
#define tknStatic 318
#define tknExtern 319
#define tknVirtual 320
#define tknOverride 321
#define tknInline 322
#define tknExplicit 323
#define tknFriend 324
#define tknVolatile 325
#define tknFinal 326
#define tknNoExcept 327
#define tknPreProHash 328
#define tknDefine 329
#define tknUndef 330
#define tknInclude 331
#define tknIf 332
#define tknIfDef 333
#define tknIfNDef 334
#define tknElse 335
#define tknElIf 336
#define tknEndIf 337
#define tknFor 338
#define tknWhile 339
#define tknDo 340
#define tknSwitch 341
#define tknCase 342
#define tknReturn 343
#define tknBlankLine 344
#define CMPEQUAL 345
#define LSHIFT 346
#define RSHIFT 347
#define ARROW 348
#define PREFIX 349
#define POSTFIX 350
#define PTRDECL 351
#define REFDECL 352
#define CTORDECL 353
#define DTORDECL 354
#define tknDefault 355
#define YYERRCODE 256

typedef union {
  CppToken              str;
  CppObj*               cppObj;
  CppVar*               cppVarObj;
  CppEnum*              cppEnum;
  CppEnumItem*          enumItem;
  CppEnumItemList*      enumItemList;
  CppTypedef*           typedefObj;
  CppCompound*          cppCompundObj;
  CppTemplateArgList*   templSpec;
  CppTemplateArg*       templArg;
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
  CppCompoundType       compoundType;
  unsigned short        ptrLevel;
  CppRefType            refType;
  unsigned int          attr;
  CppObjProtLevel       protLevel;

  CppExprList*          exprList;

  CppIfBlock*           ifBlock;
  CppWhileBlock*        whileBlock;
  CppDoWhileBlock*      doWhileBlock;
  CppForBlock*          forBlock;

  CppDefine*            hashDefine;
  CppUndef*             hashUndef;
  CppInclude*           hashInclude;
  CppHashIf*            hashIf;
  CppPragma*            hashPragma;
} YYSTYPE;
extern YYSTYPE yylval;

#endif
