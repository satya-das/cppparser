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
#define tknConst 281
#define tknStatic 282
#define tknExtern 283
#define tknVirtual 284
#define tknOverride 285
#define tknInline 286
#define tknExplicit 287
#define tknFriend 288
#define tknVolatile 289
#define tknPreProHash 290
#define tknDefine 291
#define tknUndef 292
#define tknInclude 293
#define tknIf 294
#define tknIfDef 295
#define tknIfNDef 296
#define tknElse 297
#define tknElIf 298
#define tknEndIf 299
#define tknNew 300
#define tknDelete 301
#define tknReturn 302
#define tknBlankLine 303
#define CMPEQUAL 304
#define LSHIFT 305
#define RSHIFT 306
#define ARROW 307
#define PREFIX 308
#define POSTFIX 309
#define PTRDECL 310
#define REFDECL 311
#define CTORDECL 312
#define DTORDECL 313
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

  CppDefine*            hashDefine;
  CppUndef*             hashUndef;
  CppInclude*           hashInclude;
  CppHashIf*            hashIf;
  CppPragma*            hashPragma;

  CppBlankLine*         blankLine;
} YYSTYPE;
extern YYSTYPE yylval;

#endif
