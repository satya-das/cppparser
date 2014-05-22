#ifndef _yacc_defines_h_
#define _yacc_defines_h_

#define tknID 257
#define tknStrLit 258
#define tknCharLit 259
#define tknNumber 260
#define tknTypedef 261
#define tknPreProDef 262
#define tknClass 263
#define tknStruct 264
#define tknUnion 265
#define tknNamespace 266
#define tknDocBlockComment 267
#define tknDocLineComment 268
#define tknScopeResOp 269
#define tknNumSignSpec 270
#define tknPublic 271
#define tknProtected 272
#define tknPrivate 273
#define tknExternC 274
#define tknUnRecogPrePro 275
#define tknStdHdrInclude 276
#define tknPragma 277
#define tknConst 278
#define tknStatic 279
#define tknExtern 280
#define tknVirtual 281
#define tknInline 282
#define tknExplicit 283
#define tknFriend 284
#define tknPreProHash 285
#define tknDefine 286
#define tknUndef 287
#define tknInclude 288
#define tknIf 289
#define tknIfDef 290
#define tknIfNDef 291
#define tknElse 292
#define tknElIf 293
#define tknEndIf 294
#define tknNew 295
#define tknDelete 296
#define tknReturn 297
#define tknVarArg 298
#define tknBlankLine 299
#define CMPEQUAL 300
#define ARROW 301
#define PREFIX 302
#define POSTFIX 303
#define PTRDECL 304
#define REFDECL 305
#define CTORDECL 306
#define DTORDECL 307
#define YYERRCODE 256

typedef union {
	CppToken			str;
	CppObj*				cppObj;
	CppVar*				cppVarObj;
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
