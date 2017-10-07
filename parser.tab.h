#ifndef _yacc_defines_h_
#define _yacc_defines_h_

#define tknID 257
#define tknStrLit 258
#define tknCharLit 259
#define tknNumber 260
#define tknTypedef 261
#define tknEnum 262
#define tknPreProDef 263
#define tknClass 264
#define tknStruct 265
#define tknUnion 266
#define tknNamespace 267
#define tknDocBlockComment 268
#define tknDocLineComment 269
#define tknScopeResOp 270
#define tknNumSignSpec 271
#define tknPublic 272
#define tknProtected 273
#define tknPrivate 274
#define tknExternC 275
#define tknUnRecogPrePro 276
#define tknStdHdrInclude 277
#define tknPragma 278
#define tknConst 279
#define tknStatic 280
#define tknExtern 281
#define tknVirtual 282
#define tknOverride 283
#define tknInline 284
#define tknExplicit 285
#define tknFriend 286
#define tknPreProHash 287
#define tknDefine 288
#define tknUndef 289
#define tknInclude 290
#define tknIf 291
#define tknIfDef 292
#define tknIfNDef 293
#define tknElse 294
#define tknElIf 295
#define tknEndIf 296
#define tknNew 297
#define tknDelete 298
#define tknReturn 299
#define tknVarArg 300
#define tknBlankLine 301
#define CMPEQUAL 302
#define LSHIFT 303
#define RSHIFT 304
#define ARROW 305
#define PREFIX 306
#define POSTFIX 307
#define PTRDECL 308
#define REFDECL 309
#define CTORDECL 310
#define DTORDECL 311
#define YYERRCODE 256

typedef union {
	CppToken			str;
	CppObj*				cppObj;
	CppVar*				cppVarObj;
	CppEnum*			cppEnum;
	CppEnumItem*		enumItem;
	CppEnumItemList*	enumItemList;
	CppTypedef*			typedefObj;
	CppCompound*		cppCompundObj;
	CppDocComment*		docCommentObj;
	CppFwdClsDecl*		fwdDeclObj;
	CppVarList*			cppVarObjList;
	CppUnRecogPrePro*	unRecogPreProObj;
	CppExpr*			cppExprObj;
	CppFunction*		cppFuncObj;
	CppFunctionPtr*		cppFuncPointerObj;
	CppVarOrFuncPtrType	varOrFuncPtr;
	CppParamList*		paramList;
	CppConstructor*		cppCtorObj;
	CppDestructor*		cppDtorObj;
	CppMemInitList*		memInitList;
	CppInheritanceList*	inheritList;
	CppCompoundType		compoundType;
	unsigned short		ptrLevel;
	CppRefType			refType;
	unsigned int		attr;
	CppObjProtLevel		protLevel;

	CppExprList*		exprList;

	CppDefine*			hashDefine;
	CppUndef*			hashUndef;
	CppInclude*			hashInclude;
	CppHashIf*			hashIf;
	CppPragma*			hashPragma;

	CppBlankLine*		blankLine;
} YYSTYPE;
extern YYSTYPE yylval;

#endif
