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
#define tknOperator 287
#define tknPlusEq 288
#define tknMinusEq 289
#define tknMulEq 290
#define tknDivEq 291
#define tknPerEq 292
#define tknXorEq 293
#define tknAndEq 294
#define tknOrEq 295
#define tknLShift 296
#define tknRShift 297
#define tknLShiftEq 298
#define tknRShiftEq 299
#define tknCmpEq 300
#define tknNotEq 301
#define tknLessEq 302
#define tknGreaterEq 303
#define tkn3WayCmp 304
#define tknAnd 305
#define tknOr 306
#define tknInc 307
#define tknDec 308
#define tknArrow 309
#define tknArrowStar 310
#define tknConst 311
#define tknStatic 312
#define tknExtern 313
#define tknVirtual 314
#define tknOverride 315
#define tknInline 316
#define tknExplicit 317
#define tknFriend 318
#define tknVolatile 319
#define tknPreProHash 320
#define tknDefine 321
#define tknUndef 322
#define tknInclude 323
#define tknIf 324
#define tknIfDef 325
#define tknIfNDef 326
#define tknElse 327
#define tknElIf 328
#define tknEndIf 329
#define tknFor 330
#define tknWhile 331
#define tknDo 332
#define tknSwitch 333
#define tknCase 334
#define tknNew 335
#define tknDelete 336
#define tknReturn 337
#define tknBlankLine 338
#define CMPEQUAL 339
#define LSHIFT 340
#define RSHIFT 341
#define ARROW 342
#define PREFIX 343
#define POSTFIX 344
#define PTRDECL 345
#define REFDECL 346
#define CTORDECL 347
#define DTORDECL 348
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
