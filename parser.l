/*
The MIT License (MIT)

Copyright (c) 2014

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
IMPORTANT: This file contains code to tokenify the input using flex
For simplicity and ease of tracking error in input lexer's output is always a string (represented by CppToken).
Responsiblity of token synthesis is solely on parser.
For this very reason this file does not use any class that are defined in cppdom.h
*/

%{
#include "cppdom.h" // To shutup the compiler
#include "cppconst.h" // To shutup the compiler

#include "cpptoken.h"
#include "parser.tab.h"

static int gLog = 0;

  // Easy MACRO to quickly push current context and switch to another one.
#define BEGINCONTEXT(ctx) { \
  int prevState = YYSTATE;  \
  yy_push_state(ctx);       \
  if (gLog)                 \
    printf("@line#%d, pushed state=%d and started state=%d from source code line#%d\n", gLineNo, prevState, YYSTATE, __LINE__); \
}

#define ENDCONTEXT() {      \
  int prevState = YYSTATE;  \
  yy_pop_state();           \
  if (gLog)                 \
    printf("@line#%d, ended state=%d and starting state=%d from source code line#%d\n", gLineNo, prevState, YYSTATE, __LINE__); \
}

//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#  define fileno _fileno /* Avoid compiler warning for VS. */
#endif //#ifdef WIN32

extern int gLineNo;
const char* oyytext;

// Its a hack because it uses undocumented thing.
// Returns start of buffer pointer.
const char* get_start_of_buffer()
{
  if (YY_CURRENT_BUFFER)
	  return YY_CURRENT_BUFFER->yy_ch_buf;
  return nullptr;
}

int get_context()
{
  return YYSTATE;
}

inline void set_token_and_yyposn()
{
	extern char* yyposn;
	yyposn = yytext;
	yylval.str = makeCppToken(yytext, yyleng);
}

/*
Parsing of #define is complex. So we will try to parse simple #defines to know what it trys to define.
For any thing complex we will treat the entire definition as one BLOB.
*/
enum DefineLooksLike {
	kNoDef		= 0,
	kNumDef		= tknNumber, // #define is used to define a numeric constant.
	kStrLitDef	= tknStrLit, // #define is used to define a string literal.
	kCharLitDef	= tknCharLit, // #define is used to define a character literal.
	kReDef		= tknID, // #define is used to rename something, e.g. #define CALLTYPE __stdcall
	kComplexDef	= tknPreProDef, // It is something beyond our parser can comprehand.
};
DefineLooksLike gDefLooksLike;

extern "C"
{

	int yywrap()
	{
		return 1;
	}

}
%}

%option never-interactive
%option stack

/************************************************************************/

/*@ { Comonly used regular expressions. */

	/* White space */
WS	 [ \t]

	/* Token sparator */
TS	 [^_a-zA-Z0-9]

	/* C/C++ identifier */
ID	 [_a-zA-Z]+[_0-9a-zA-Z]*

	/* New line */
NL	 (\r\n|\r|\n)

	/* Number */
NUM  ([0-9]+((l|L|u|U)?|(\.[0-9]*)?))|\.[0-9]+|(0(x|X)[0-9a-fA-F]*)|0(x|X)[0-9a-zA-Z]+

	/* String literal */
SL   "\"".*"\""

	/* Char literal */
CL   "\'".*"\'"

/*@}*/

%x ctxGeneral
%x ctxDocBlockComment
%x ctxBlockComment

/* This context starts when # is encountered as first thing in line while state is ctxGeneral */
%x ctxPreprocessor

/* This context starts when include is encountered while state is ctxPreprocessor */
%x ctxInclude

/* This context starts when define is encountered while state is ctxPreprocessor */
%x ctxDefine

/* This context starts when definition name is found after #define */
%x ctxDefineDefn

/*
This context starts after #if, #elif, and #pragma to capture everyting till a new line is not found.
*/
%x ctxPreProBody

%%

<*>{WS}+ {
	/* Ignore white spaces */
}

<*>\\{WS}*{NL} {
	// We will always ignore line continuation character
	++gLineNo;
}

<ctxGeneral>^{WS}*{NL} {
	++gLineNo;
}

<ctxGeneral,ctxDocBlockComment>{NL} {
	++gLineNo;
}

<ctxGeneral,ctxPreprocessor>{ID} {
	set_token_and_yyposn();
	return tknID;
}

<ctxGeneral>signed|unsigned/{TS}+ {
	set_token_and_yyposn();
	return tknNumSignSpec;
}

<ctxGeneral>long/{TS}+ {
  set_token_and_yyposn();
  return tknLong;
}

<ctxGeneral>typedef{TS}+ {
	set_token_and_yyposn();
	return tknTypedef;
}

<ctxGeneral>class/{TS}+ {
	set_token_and_yyposn();
	return tknClass;
}

<ctxGeneral>namespace/{TS}+ {
	set_token_and_yyposn();
	return tknNamespace;
}

<ctxGeneral>struct/{TS}+ {
	set_token_and_yyposn();
	return tknStruct;
}

<ctxGeneral>union/{TS}+ {
	set_token_and_yyposn();
	return tknUnion;
}

<ctxGeneral>enum/{TS}+ {
	set_token_and_yyposn();
	return tknEnum;
}

<ctxGeneral>public/{TS}+ {
	set_token_and_yyposn();
	return tknPublic;
}

<ctxGeneral>protected/{TS}+ {
	set_token_and_yyposn();
	return tknProtected;
}

<ctxGeneral>private/{TS}+ {
	set_token_and_yyposn();
	return tknPrivate;
}

<ctxGeneral>template/{TS}+ {
	set_token_and_yyposn();
	return tknTemplate;
}

<ctxGeneral>typename/{TS}+ {
	set_token_and_yyposn();
	return tknTypename;
}

<ctxGeneral>^{WS}*"/*" {
	oyytext = yytext;
  BEGINCONTEXT(ctxDocBlockComment);
}

<ctxDocBlockComment>.*"*"+"/" {
	yylval.str = makeCppToken(oyytext, yytext+yyleng-oyytext);
  ENDCONTEXT(); /* Begin the same state we were before encountering comment. */
	return tknDocBlockComment;
}

<*>"/*" {
  BEGINCONTEXT(ctxBlockComment);
}
<ctxBlockComment,ctxDocBlockComment>[^*\n]* {
}
<ctxBlockComment,ctxDocBlockComment>[^*\n]*\n {
  ++gLineNo;
}
<ctxBlockComment,ctxDocBlockComment>{WS}*"*"+[^*/\n]* {
}
<ctxBlockComment,ctxDocBlockComment>{WS}*"*"+[^*/\n]*\n {
  ++gLineNo;
}
<ctxBlockComment>.*"*"+"/" {
  ENDCONTEXT(); /* Begin the same state we were before encountering comment. */
  /* Ignore block comment if it does not stand all alone */
}

<*>^{WS}*"//".* {
	set_token_and_yyposn();
	return tknDocLineComment;
}

<*>"//".* {
}

<ctxGeneral>^{WS}*# {
	set_token_and_yyposn();
	BEGINCONTEXT(ctxPreprocessor);
	return tknPreProHash;
}

<ctxPreprocessor>define/{WS} {
	set_token_and_yyposn();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefine);
	return tknDefine;

	/*
	Parsing of #define is tricky
	We want to know if #define is used to define simple constants.
	For all other cases it is OK to capture the entire block as one BLOB.
	An attempt to parse MACRO is difficult because we can have things like:
		#define GLUT_BITMAP_HELVETICA_18	((void*)8)
		In this case '(' is part of definition rather than used to specify parameter of MACRO.
	MACRO can be used to define partial expression like:
		#define BEGIN yy_start = 1 + 2 *
		So, if we want to parse the definition as an expression then that too will fail.
	Basically #define can be used in myriad ways which will be too difficult for us to parse.
	*/
}

<ctxDefine>{ID} {
	set_token_and_yyposn();
  ENDCONTEXT();
	BEGINCONTEXT(ctxDefineDefn);
	gDefLooksLike = kNoDef;
	oyytext = 0;
	return tknID;
}

<ctxDefineDefn>{ID} {
	if(gDefLooksLike == kNoDef)
	{
		gDefLooksLike = kReDef;
		oyytext = yytext;
	}
	else if(gDefLooksLike == kStrLitDef || gDefLooksLike == kReDef)
	{
		// Looks like string literal definition by concatination of different token
		// e.g. #define APP_NAME PROD_NAME VER_STR
		// Where PROD_NAME and VER_STR are already #defined as string literals.
		gDefLooksLike = kStrLitDef;
	}
	else
	{ // It does not look like simple #define.
		gDefLooksLike = kComplexDef;
	}
}

<ctxDefineDefn>{SL} {
	if(gDefLooksLike == kNoDef || gDefLooksLike == kStrLitDef || gDefLooksLike == kReDef)
	{
		gDefLooksLike = kStrLitDef;
		if(oyytext == 0)
			oyytext = yytext;
	}
	else
	{ // It does not look like simple #define.
		gDefLooksLike = kComplexDef;
	}
}

<ctxDefineDefn>{CL} {
	if(gDefLooksLike == kNoDef)
	{
		gDefLooksLike = kCharLitDef;
		oyytext = yytext;
	}
	else
	{ // It does not look like simple #define.
		gDefLooksLike = kComplexDef;
	}
}

<ctxDefineDefn>{NUM} {
	if(gDefLooksLike == kNoDef)
	{
		gDefLooksLike = kNumDef;
		oyytext = yytext;
	}
	else
	{ // It does not look like simple #define.
		gDefLooksLike = kComplexDef;
	}
}

<ctxDefineDefn>[^\t\r\n ] { // Any unrecognized character other than whitespace indicates a complex #define
	gDefLooksLike = kComplexDef;
	if(oyytext == 0)
		oyytext = yytext;
}

<ctxDefineDefn>{NL} {
	yylval.str = makeCppToken(oyytext, yytext-oyytext);
  ENDCONTEXT();
  ++gLineNo;
	if(gDefLooksLike != kNoDef)
		return gDefLooksLike;
}

<ctxDefineDefn>"//".*{NL} {
	/* Ignore line comment when it does not stand alone in a line. */
	// We are also ignoring the last new-line character
	// It is because we want the #define to conclude if C++ comment is present at the end of #define.
	yyless(yyleng-1);
}

<ctxPreprocessor>undef/{WS} {
	set_token_and_yyposn();
	return tknUndef;
}

<ctxPreprocessor>include/{WS} {
  ENDCONTEXT();
	set_token_and_yyposn();
	BEGINCONTEXT(ctxInclude);
	return tknInclude;
}

<ctxInclude><.*> {
	set_token_and_yyposn();
	return tknStdHdrInclude;
}

<ctxInclude>{NL} {
  ENDCONTEXT();
	++gLineNo;
}

<ctxPreprocessor>if/{WS} {
	set_token_and_yyposn();
	oyytext = yytext+yyleng;
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
	return tknIf;
}

<ctxPreprocessor>ifdef/{WS} {
	set_token_and_yyposn();
	return tknIfDef;
}

<ctxPreprocessor>ifndef/{WS} {
	set_token_and_yyposn();
	return tknIfNDef;
}

<ctxGeneral,ctxPreprocessor>else/{TS} {
	set_token_and_yyposn();
	return tknElse;
}

<ctxPreprocessor>elif/{WS} {
	set_token_and_yyposn();
	oyytext = yytext+yyleng;
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
	return tknElIf;
}

<ctxPreprocessor>endif/{TS} {
	set_token_and_yyposn();
	return tknEndIf;
}

<ctxPreprocessor>pragma/{WS} {
	set_token_and_yyposn();
	oyytext = yytext+yyleng;
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
	return tknPragma;
}

<ctxPreProBody>.* {
}

<ctxPreProBody>{NL} {
	yylval.str = makeCppToken(oyytext, yytext-oyytext);
  ENDCONTEXT();
	++gLineNo;
	return tknPreProDef;
}

<ctxPreprocessor>{NL} {
  ENDCONTEXT();
	++gLineNo;
}

<ctxGeneral>"::" {
	set_token_and_yyposn();
	return tknScopeResOp;
}

<ctxGeneral>const/{TS}+ {
	set_token_and_yyposn();
	return tknConst;
}

<ctxGeneral>static/{TS}+ {
	set_token_and_yyposn();
	return tknStatic;
}

<ctxGeneral>inline/{TS}+ {
	set_token_and_yyposn();
	return tknInline;
}

<ctxGeneral>virtual/{TS}+ {
	set_token_and_yyposn();
	return tknVirtual;
}

<ctxGeneral>override/{TS}+ {
	set_token_and_yyposn();
	return tknOverride;
}

<ctxGeneral>extern/{TS}+ {
	set_token_and_yyposn();
	return tknExtern;
}

<ctxGeneral>explicit/{TS}+ {
	set_token_and_yyposn();
	return tknExplicit;
}

<ctxGeneral>friend/{TS}+ {
	set_token_and_yyposn();
	return tknFriend;
}

<ctxGeneral>"extern"{WS}+"\"C\"" {
	set_token_and_yyposn();
	return tknExternC;
}

<ctxGeneral>volatile/{TS}+ {
  set_token_and_yyposn();
  return tknVolatile;
}

<ctxGeneral>new/{TS}+ {
	return tknNew;
}

<ctxGeneral>delete/{TS}+ {
	return tknDelete;
}

<ctxGeneral>return/{TS}+ {
	return tknReturn;
}

<ctxGeneral>if/{TS}+ {
	return tknIf;
}

<ctxGeneral>for/{TS}+ {
	return tknFor;
}

<ctxGeneral>do/{TS}+ {
	return tknDo;
}

<ctxGeneral>while/{TS}+ {
	return tknWhile;
}

<ctxGeneral>switch/{TS}+ {
	return tknSwitch;
}

<ctxGeneral>case/{TS}+ {
	return tknCase;
}

<ctxGeneral>const_cast/{TS}+ {
	return tknConstCast;
}

<ctxGeneral>static_cast/{TS}+ {
	return tknStaticCast;
}

<ctxGeneral>dynamic_cast/{TS}+ {
	return tknDynamicCast;
}

<ctxGeneral>reinterpret_cast/{TS}+ {
	return tknReinterpretCast;
}

<ctxGeneral>operator/{TS}+ {
	set_token_and_yyposn();
	return tknOperator;
}

<ctxGeneral>"+=" {
	set_token_and_yyposn();
	return tknPlusEq;
}

<ctxGeneral>"-=" {
	set_token_and_yyposn();
	return tknMinusEq;
}

<ctxGeneral>"*=" {
	set_token_and_yyposn();
	return tknMulEq;
}

<ctxGeneral>"*=" {
	set_token_and_yyposn();
	return tknMulEq;
}

<ctxGeneral>"/=" {
	set_token_and_yyposn();
	return tknDivEq;
}

<ctxGeneral>"%=" {
	set_token_and_yyposn();
	return tknPerEq;
}

<ctxGeneral>"^=" {
	set_token_and_yyposn();
	return tknXorEq;
}

<ctxGeneral>"&=" {
	set_token_and_yyposn();
	return tknAndEq;
}

<ctxGeneral>"|=" {
	set_token_and_yyposn();
	return tknOrEq;
}

<ctxGeneral>"<<" {
	set_token_and_yyposn();
	return tknLShift;
}

<ctxGeneral>">>" {
	set_token_and_yyposn();
	return tknRShift;
}

<ctxGeneral>"<<=" {
	set_token_and_yyposn();
	return tknLShiftEq;
}

<ctxGeneral>">>=" {
	set_token_and_yyposn();
	return tknRShiftEq;
}

<ctxGeneral>"==" {
	set_token_and_yyposn();
	return tknCmpEq;
}

<ctxGeneral>"!=" {
	set_token_and_yyposn();
	return tknNotEq;
}

<ctxGeneral>"<=" {
	set_token_and_yyposn();
	return tknLessEq;
}

<ctxGeneral>">=" {
	set_token_and_yyposn();
	return tknGreaterEq;
}

<ctxGeneral>"<=>" {
	set_token_and_yyposn();
	return tkn3WayCmp;
}

<ctxGeneral>"&&" {
	set_token_and_yyposn();
	return tknAnd;
}

<ctxGeneral>"||" {
	set_token_and_yyposn();
	return tknOr;
}

<ctxGeneral>"++" {
	set_token_and_yyposn();
	return tknInc;
}

<ctxGeneral>"--" {
	set_token_and_yyposn();
	return tknDec;
}

<ctxGeneral>"->" {
	set_token_and_yyposn();
	return tknArrow;
}

<ctxGeneral>"->*" {
	set_token_and_yyposn();
	return tknArrowStar;
}

<ctxGeneral,ctxDefine>{NUM} {
	set_token_and_yyposn();
	return tknNumber;
}

<ctxGeneral,ctxInclude>"\"".*"\"" {
	set_token_and_yyposn();
	return tknStrLit;
}

<ctxGeneral>"\'".*"\'" {
	set_token_and_yyposn();
	return tknCharLit;
}

<ctxGeneral>\(|\)|\{|\}|\[|\]|,|;|#|=|\*|\+|-|\.|\/|\~|\<|\>|&|\||:|\? {
	set_token_and_yyposn();
	return yytext[0];
}

<ctxGeneral>\.\.\. {
	set_token_and_yyposn();
	return tknEllipsis;
}

%%

static YY_BUFFER_STATE gParseBuffer = nullptr;
void setupScanBuffer(char* buf, size_t bufsize)
{
  gParseBuffer = yy_scan_buffer(buf, bufsize);
  gLineNo = 0;
  BEGINCONTEXT(ctxGeneral);
}

void cleanupScanBuffer()
{
  yy_delete_buffer(gParseBuffer);
  gParseBuffer = nullptr;
}

