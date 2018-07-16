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
#define tknStatic 317
#define tknExtern 318
#define tknVirtual 319
#define tknOverride 320
#define tknInline 321
#define tknExplicit 322
#define tknFriend 323
#define tknVolatile 324
#define tknFinal 325
#define tknPreProHash 326
#define tknDefine 327
#define tknUndef 328
#define tknInclude 329
#define tknIf 330
#define tknIfDef 331
#define tknIfNDef 332
#define tknElse 333
#define tknElIf 334
#define tknEndIf 335
#define tknFor 336
#define tknWhile 337
#define tknDo 338
#define tknSwitch 339
#define tknCase 340
#define tknReturn 341
#define tknBlankLine 342
#define CMPEQUAL 343
#define LSHIFT 344
#define RSHIFT 345
#define ARROW 346
#define PREFIX 347
#define POSTFIX 348
#define PTRDECL 349
#define REFDECL 350
#define CTORDECL 351
#define DTORDECL 352
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
