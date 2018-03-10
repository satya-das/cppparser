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
#define tknDocBlockComment 269
#define tknDocLineComment 270
#define tknScopeResOp 271
#define tknNumSignSpec 272
#define tknPublic 273
#define tknProtected 274
#define tknPrivate 275
#define tknExternC 276
#define tknUnRecogPrePro 277
#define tknStdHdrInclude 278
#define tknPragma 279
#define tknEllipsis 280
#define tknConstCast 281
#define tknStaticCast 282
#define tknDynamicCast 283
#define tknReinterpretCast 284
#define tknOperator 285
#define tknPlusEq 286
#define tknMinusEq 287
#define tknMulEq 288
#define tknDivEq 289
#define tknPerEq 290
#define tknXorEq 291
#define tknAndEq 292
#define tknOrEq 293
#define tknLShift 294
#define tknRShift 295
#define tknLShiftEq 296
#define tknRShiftEq 297
#define tknCmpEq 298
#define tknNotEq 299
#define tknLessEq 300
#define tknGreaterEq 301
#define tkn3WayCmp 302
#define tknAnd 303
#define tknOr 304
#define tknInc 305
#define tknDec 306
#define tknArrow 307
#define tknArrowStar 308
#define tknConst 309
#define tknStatic 310
#define tknExtern 311
#define tknVirtual 312
#define tknOverride 313
#define tknInline 314
#define tknExplicit 315
#define tknFriend 316
#define tknVolatile 317
#define tknPreProHash 318
#define tknDefine 319
#define tknUndef 320
#define tknInclude 321
#define tknIf 322
#define tknIfDef 323
#define tknIfNDef 324
#define tknElse 325
#define tknElIf 326
#define tknEndIf 327
#define tknFor 328
#define tknWhile 329
#define tknDo 330
#define tknSwitch 331
#define tknCase 332
#define tknNew 333
#define tknDelete 334
#define tknReturn 335
#define tknBlankLine 336
#define CMPEQUAL 337
#define LSHIFT 338
#define RSHIFT 339
#define ARROW 340
#define PREFIX 341
#define POSTFIX 342
#define PTRDECL 343
#define REFDECL 344
#define CTORDECL 345
#define DTORDECL 346
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

  CppBlankLine*         blankLine;
} YYSTYPE;
extern YYSTYPE yylval;

#endif
