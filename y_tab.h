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
#define tknInline 283
#define tknExplicit 284
#define tknFriend 285
#define tknPreProHash 286
#define tknDefine 287
#define tknUndef 288
#define tknInclude 289
#define tknIf 290
#define tknIfDef 291
#define tknIfNDef 292
#define tknElse 293
#define tknElIf 294
#define tknEndIf 295
#define tknNew 296
#define tknDelete 297
#define tknReturn 298
#define tknVarArg 299
#define tknBlankLine 300
#define CMPEQUAL 301
#define ARROW 302
#define PREFIX 303
#define POSTFIX 304
#define PTRDECL 305
#define REFDECL 306
#define CTORDECL 307
#define DTORDECL 308
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
