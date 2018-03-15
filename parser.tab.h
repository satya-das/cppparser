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
#define tknConst 314
#define tknStatic 315
#define tknExtern 316
#define tknVirtual 317
#define tknOverride 318
#define tknInline 319
#define tknExplicit 320
#define tknFriend 321
#define tknVolatile 322
#define tknPreProHash 323
#define tknDefine 324
#define tknUndef 325
#define tknInclude 326
#define tknIf 327
#define tknIfDef 328
#define tknIfNDef 329
#define tknElse 330
#define tknElIf 331
#define tknEndIf 332
#define tknFor 333
#define tknWhile 334
#define tknDo 335
#define tknSwitch 336
#define tknCase 337
#define tknNew 338
#define tknDelete 339
#define tknReturn 340
#define tknBlankLine 341
#define CMPEQUAL 342
#define LSHIFT 343
#define RSHIFT 344
#define ARROW 345
#define PREFIX 346
#define POSTFIX 347
#define PTRDECL 348
#define REFDECL 349
#define CTORDECL 350
#define DTORDECL 351
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
