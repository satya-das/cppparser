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
#define tknConst 285
#define tknStatic 286
#define tknExtern 287
#define tknVirtual 288
#define tknOverride 289
#define tknInline 290
#define tknExplicit 291
#define tknFriend 292
#define tknVolatile 293
#define tknPreProHash 294
#define tknDefine 295
#define tknUndef 296
#define tknInclude 297
#define tknIf 298
#define tknIfDef 299
#define tknIfNDef 300
#define tknElse 301
#define tknElIf 302
#define tknEndIf 303
#define tknFor 304
#define tknWhile 305
#define tknDo 306
#define tknSwitch 307
#define tknCase 308
#define tknNew 309
#define tknDelete 310
#define tknReturn 311
#define tknBlankLine 312
#define CMPEQUAL 313
#define LSHIFT 314
#define RSHIFT 315
#define ARROW 316
#define PREFIX 317
#define POSTFIX 318
#define PTRDECL 319
#define REFDECL 320
#define CTORDECL 321
#define DTORDECL 322
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
