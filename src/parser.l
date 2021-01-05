/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

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

/* clang-format off */

/*
IMPORTANT: This file contains code to tokenify the input using flex
For simplicity and ease of tracking error in input lexer's output is always a string (represented by CppToken).
Responsiblity of token synthesis is solely on parser.
For this very reason this file does not use any class that are defined in cppast.h
*/

%{
#include "cppast.h" // To shutup the compiler
#include "cppconst.h" // To shutup the compiler

// C++17 causes problem when register is used and flex uses register in generated code
#define register

#include "cpptoken.h"
#include "cppvarinit.h"
#include "parser.l.h"

#include <iostream>

/// @{ Global data
LexerData g;

// Externally controlled data
// These do not get reset on change of input file
extern bool gParseEnumBodyAsBlob;
extern bool gParseFunctionBodyAsBlob;

extern std::set<std::string>        gMacroNames;
extern std::set<std::string>        gKnownApiDecorNames;
extern std::set<std::string>        gIgnorableMacroNames;
extern std::map<std::string, int>   gRenamedKeywords;
/// @}

const char* contextNameFromState(int ctx);

  // Easy MACRO to quickly push current context and switch to another one.
#define BEGINCONTEXT(ctx) { \
  int prevState = YYSTATE;  \
  yy_push_state(ctx);       \
  if (g.mLexLog)                 \
    printf("parser.l line#%4d: pushed %s(%d) and started %s(%d) from input-line#%d\n", __LINE__, contextNameFromState(prevState), prevState, contextNameFromState(YYSTATE), YYSTATE, g.mLineNo); \
}

#define ENDCONTEXT() {      \
  int prevState = YYSTATE;  \
  yy_pop_state();           \
  if (g.mLexLog)                 \
    printf("parser.l line#%4d: ended %s(%d) and starting %s(%d) from input-line#%d\n", __LINE__, contextNameFromState(prevState), prevState, contextNameFromState(YYSTATE), YYSTATE, g.mLineNo); \
}

static int LogAndReturn(int ret, int codelinenum, int srclinenum)
{
  if (g.mLexLog)
  {
    printf("parser.l line#%4d: returning token %d with value '%s' found @input-line#%d\n",
      codelinenum, ret, yytext, srclinenum);
  }
  return ret;
}

static void Log(int codelinenum, int srclinenum)
{
  if (g.mLexLog)
  {
    printf("parser.l line#%4d and input line#%d\n",
      codelinenum, srclinenum);
  }
}

#define RETURN(ret)	return LogAndReturn(ret, __LINE__, g.mLineNo)
#define LOG() Log(__LINE__, g.mLineNo)
#define INCREMENT_INPUT_LINE_NUM() \
{\
  if (g.mLexLog)  \
  { \
    printf("parser.l line#%4d: Incrementing g.mLineNo, found @input-line#%d\n", __LINE__, g.mLineNo); \
  } \
  ++g.mLineNo;  \
}

//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#  define fileno _fileno /* Avoid compiler warning for VS. */
#endif //#ifdef WIN32

int get_context()
{
  return YYSTATE;
}

void set_oyytext(const char* p)
{
  g.oyytext = p;
}

void setCommentTokenizationState(TokenSetupFlag flag)
{
  switch(flag)
  {
    case TokenSetupFlag::DisableCommentTokenization:
      g.mTokenizeComment = false;
      break;
    case TokenSetupFlag::EnableCommentTokenization:
      g.mTokenizeComment = true;
      break;
    case TokenSetupFlag::ResetCommentTokenization:
      g.mTokenizeComment = (!g.mBracketDepthStack.empty()) && (g.mBracketDepthStack.back() == 0);
      break;
    case TokenSetupFlag::None:
      // Nothing to do
      break;
  }
}

static void set_token_and_yyposn(const char* text, size_t len, TokenSetupFlag flag = TokenSetupFlag::DisableCommentTokenization)
{
  extern char* yyposn;
  yyposn = const_cast<char*>(text);
  yylval.str = makeCppToken(text, len);

  setCommentTokenizationState(flag);
}

static void set_token_and_yyposn(TokenSetupFlag flag = TokenSetupFlag::DisableCommentTokenization)
{
  set_token_and_yyposn(yytext, yyleng, flag);
}

void setBlobToken(TokenSetupFlag flag = TokenSetupFlag::None)
{
  set_token_and_yyposn(g.oyytext, yytext+yyleng-g.oyytext, flag);
}

using YYLessProc = std::function<void(int)>;

// yyless is not available outside of lexing context.
// So, yylessfn is the callback that caller needs to pass
// that just calls yyless();
static void tokenize_bracketed_content(YYLessProc yylessfn)
{
  // yyinput() has bug (see https://github.com/westes/flex/pull/396)
  // So, I am exploiting yyless() by passing value bigger than yyleng.
  auto savedlen = yyleng;
  auto input = [&]() {
    yylessfn(yyleng+1);
    return yytext[yyleng-1];
  };
  int c = 0;
  while (isspace(c = input()))
    ;
  if (c == '(')
  {
    int openBracket = 1;
    for (c = input(); openBracket && (c != EOF); c = input())
    {
      if (c == '(')
      {
        ++openBracket;
      }
      else if (c == ')')
      {
        --openBracket;
        if (!openBracket)
          break;
      }
      else if (c == '\n')
      {
        INCREMENT_INPUT_LINE_NUM();
      }
    }
  }
  else
  {
    yylessfn(savedlen);
  }
  set_token_and_yyposn();
}

static const char* findMatchedClosingBracket(const char* start, char openingBracketType = '(')
{
  const char openingBracket = (openingBracketType != '{') ? '(' : '{';
  const char closingBracket = (openingBracket == '{') ? '}' : ')';

  // Since '(' / '{' should be used in trailing context, it's location will contain '\0'
  assert(*start == '\0');
  auto end = g.mInputBuffer + g.mInputBufferSize;
  int openBracket = 1;
  for (auto p = start+1; p != end; ++p)
  {
    if (*p == openingBracket)
    {
      ++openBracket;
    }
    else if (*p == closingBracket)
    {
      --openBracket;
      if (!openBracket)
        return p;
    }
  }

  return end;
}

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
%option noyy_top_state

/************************************************************************/

/*@ { Comonly used regular expressions. */

/* White space. It doesn't account for new line which is tracked seperately
     so that we can count line number for reporting error precisely */
WS	 [ \t]

/* New line */
NL	 (\r\n|\r|\n)

/* White space or new line chars. Should only be used in trainling context so that
  new lines are always get tracked. */
WSNL " "|\r\n|\r|\n|\t

/* Token sparator */
TS	 [^_a-zA-Z0-9]

/* C/C++ identifier */
ID	 [_a-zA-Z]+[_0-9a-zA-Z]*

ID2  ({ID}"::"{WS}*)*{ID}

/* Number */
NUM  ([0-9]+((l|L|u|U)*|(\.[0-9]*)?))|\.[0-9]+|(0(b|B)[01']*)|(0(x|X)[0-9a-fA-F]*)|0(x|X)[0-9a-zA-Z]+

DECNUMLIT  (([0-9]+(\.[0-9]*)?)|([0-9]*(\.[0-9]+)))(f|F)?

/* String literal */
SL   "\""([^"\\]|\\.)*\"

/* Char literal */
CL   \'([^'\\]|\\.)*\'

/* Comma separated parameter list */
CSP (({WS}*{ID}{WS}*,{WS}*)*{ID}{WS}*)*

/* Function Trailing Attributes. Should be only used in trailing context.*/
FTA ("const"|"final"|"override"|{ID})

/*@}*/

%x ctxGeneral
%x ctxFreeStandingBlockComment
%x ctxSideBlockComment
%x ctxBlockCommentInsideMacroDefn

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

/* When we are inside enum body */
%x ctxEnumBody

/* When we are inside function implementation body */
%x ctxFunctionBody

/* Code within and including '#if 0 ... #endif'
   Also includes (TO BE IMPLEMENTED) the following cases:
    '#if undefined_macro ... #endif',
    '#ifdef undefined_macro ... #endif',
    '#ifndef defined_macro ... #endif'
*/
%x ctxDisabledCode

%x ctxMemInitList

%%

<ctxGeneral>^{WS}*{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxGeneral,ctxFreeStandingBlockComment,ctxSideBlockComment>{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxPreprocessor>{ID} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknName);
}

<ctxGeneral>"__declspec"{WS}*"("{WS}*{ID}{WS}*")" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>__cdecl {
  LOG();
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>__stdcall {
  LOG();
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>afx_msg {
  LOG();
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>"alignas"{WS}*"("{WS}*{ID}{WS}*")" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>"alignas"{WS}*"("{WS}*{NUM}{WS}*")" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>{ID} {
  LOG();
  if (gIgnorableMacroNames.count(yytext))
  {
    tokenize_bracketed_content([&](int l) { yyless(l); } );
    // Nothing to return. Just ignore
  }
  else
  {
    if (gMacroNames.count(yytext))
    {
      tokenize_bracketed_content([&](int l) { yyless(l); } );
      RETURN(tknMacro);
    }

    if (gKnownApiDecorNames.count(yytext))
    {
      tokenize_bracketed_content([&](int l) { yyless(l); } );
      RETURN(tknApiDecor);
    }

    set_token_and_yyposn();
    auto itr = gRenamedKeywords.find(yylval.str);
    if (itr != gRenamedKeywords.end())
      return itr->second;
    RETURN(tknName);
  }
}

<ctxGeneral>"?"[^?]*":" {
  LOG();
  if (gParseFunctionBodyAsBlob)
    g.mNotAMemInitColon = yytext+yyleng-1;
  REJECT;
}

<ctxGeneral>")"{WSNL}*({FTA}{WSNL}*)*{WSNL}*("{"|":") {
  LOG();
  if (gParseFunctionBodyAsBlob)
  {
    if (yytext[yyleng-1] == '{')
    {
      g.mFunctionBodyWillBeEncountered = true;
      g.mExpectedBracePosition = yytext + yyleng-1;
    }
    else if ((yytext[yyleng-1] == ':') && (g.mNotAMemInitColon != (yytext+yyleng-1)))
    {
      g.mMemInitListWillBeEncountered = true;
      g.mExpectedColonPosition = yytext + yyleng-1;
    }
  }

  REJECT;
}

<ctxGeneral>asm/{TS} {
  LOG();
  tokenize_bracketed_content([&](int l) { yyless(l); } );
  RETURN(tknAsm);
}

<ctxGeneral>signed|unsigned/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknNumSignSpec);
}

<ctxGeneral>long{WS}+long{WS}+int|long{WS}+long|long{WS}+int|long|int|short{WS}+int|short/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknInteger);
}

<ctxGeneral>__int8|__int16|__int32|__int64|__int128/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknInteger);
}

<ctxGeneral>char/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknChar);
}

<ctxGeneral>long{WS}+double|double/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDouble);
}

<ctxGeneral>long{WS}+float|float/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknFloat);
}

<ctxGeneral>auto/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknAuto);
}

<ctxGeneral>typedef{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknTypedef);
}

<ctxGeneral>using{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknUsing);
}

<ctxGeneral>class/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknClass);
}

<ctxGeneral>namespace/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknNamespace);
}

<ctxGeneral>struct/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknStruct);
}

<ctxGeneral>union/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknUnion);
}

<ctxGeneral>enum/{WS}+(class{WS}+)?{ID}?({WS}*":"{WS}*{ID})?{WSNL}*"{" {
  LOG();
  set_token_and_yyposn();
  if (gParseEnumBodyAsBlob)
    g.mEnumBodyWillBeEncountered = true;
  RETURN(tknEnum);
}

<ctxGeneral>enum/{TS} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknEnum);
}

<ctxGeneral>public/{WS}*":" {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknPublic);
}

<ctxGeneral>public/{TS} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknPublic);
}

<ctxGeneral>protected/{WS}*":" {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknProtected);
}

<ctxGeneral>protected/{TS} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknProtected);
}

<ctxGeneral>private/{WS}*":" {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknPrivate);
}

<ctxGeneral>private/{TS} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknPrivate);
}

<ctxGeneral>template/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknTemplate);
}

<ctxGeneral>typename/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknTypename);
}

<ctxGeneral>decltype/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDecltype);
}

<ctxGeneral>^{WS}*"/*" {
  LOG();
  set_oyytext(yytext);
  BEGINCONTEXT(ctxFreeStandingBlockComment);
}

<*>"/*" {
  /*
  Ignore side comments for time being
  set_oyytext(yytext);
  */
  BEGINCONTEXT(ctxSideBlockComment);
}

<ctxFreeStandingBlockComment>[^*\n]*"*"+"/"/{WS}*{NL} {
  LOG();
  ENDCONTEXT();
  if (g.mTokenizeComment)
  {
    set_token_and_yyposn(g.oyytext, yytext+yyleng-g.oyytext, TokenSetupFlag::None);
    RETURN(tknFreeStandingBlockComment);
  }
}
<ctxFreeStandingBlockComment>[^*\n]*"*"+"/" {
  LOG();
  ENDCONTEXT();
}

<ctxSideBlockComment>[^*\n]*"*"+"/" {
  LOG();
  ENDCONTEXT();

  /*
  Ignore side comments for time being
  if (g.mTokenizeComment)
    set_token_and_yyposn(g.oyytext, yytext+yyleng-g.oyytext, TokenSetupFlag::None);
    RETURN(tknSideBlockComment);
  }
  */
}

<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>[^*\n]* {
  LOG();
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>[^*\n]*\n {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>{WS}*"*"+[^*/\n]* {
  LOG();
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>{WS}*"*"+[^*/\n]*\n {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>. {
  LOG();
}

<*>^{WS}*"//"[^\n]* {
  if (g.mTokenizeComment)
  {
    set_token_and_yyposn(TokenSetupFlag::None);
    RETURN(tknFreeStandingLineComment);
  }
}

<*>"//"[^\n]* {
  if (g.mTokenizeComment)
  {
    set_token_and_yyposn(TokenSetupFlag::None);
    // Ignore side comments for time being
    // RETURN(tknSideLineComment);
  }
}

<ctxGeneral>^{WS}*# {
  LOG();
  set_token_and_yyposn();
  BEGINCONTEXT(ctxPreprocessor);
  RETURN(tknPreProHash);
}

<ctxPreprocessor>define/{WS} {
  LOG();
  set_token_and_yyposn();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefine);
  RETURN(tknDefine);

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

<ctxDefine>{ID}\({CSP}\) {
  LOG();
  set_token_and_yyposn();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  g.mDefLooksLike = kComplexDef;
  set_oyytext(yytext + yyleng);
  RETURN(tknName);
}

<ctxDefine>{ID}\(.*"...".*\) {
  LOG();
  set_token_and_yyposn();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  g.mDefLooksLike = kComplexDef;
  set_oyytext(yytext + yyleng);
  RETURN(tknName);
}

<ctxDefine>{ID} {
  LOG();
  set_token_and_yyposn();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  g.mDefLooksLike = kNoDef;
  set_oyytext(0);
  RETURN(tknName);
}

<ctxDefineDefn>{ID} {
  LOG();
  if(g.mDefLooksLike == kNoDef)
  {
    g.mDefLooksLike = kReDef;
    set_oyytext(yytext);
  }
  else if(g.mDefLooksLike == kStrLitDef || g.mDefLooksLike == kReDef)
  {
    // Looks like string literal definition by concatination of different token
    // e.g. #define APP_NAME PROD_NAME VER_STR
    // Where PROD_NAME and VER_STR are already #defined as string literals.
    g.mDefLooksLike = kStrLitDef;
  }
  else
  { // It does not look like simple #define.
    if (g.oyytext == 0)
      set_oyytext(yytext);
    g.mDefLooksLike = kComplexDef;
  }
}

<ctxDefineDefn>{SL} {
  LOG();
  if(g.mDefLooksLike == kNoDef || g.mDefLooksLike == kStrLitDef || g.mDefLooksLike == kReDef)
  {
    g.mDefLooksLike = kStrLitDef;
    if(g.oyytext == 0)
      set_oyytext(yytext);
  }
  else
  { // It does not look like simple #define.
    g.mDefLooksLike = kComplexDef;
  }
}

<ctxDefineDefn>{CL} {
  LOG();
  if(g.mDefLooksLike == kNoDef)
  {
    g.mDefLooksLike = kCharLitDef;
    set_oyytext(yytext);
  }
  else
  { // It does not look like simple #define.
    g.mDefLooksLike = kComplexDef;
  }
}

<ctxDefineDefn>{NUM} {
  LOG();
  if(g.mDefLooksLike == kNoDef)
  {
    g.mDefLooksLike = kNumDef;
    set_oyytext(yytext);
  }
  else
  { // It does not look like simple #define.
    g.mDefLooksLike = kComplexDef;
  }
}

<ctxDefineDefn>[^\t\r\n ] { // Any unrecognized character other than whitespace indicates a complex #define
  LOG();
  g.mDefLooksLike = kComplexDef;
  if(g.oyytext == 0)
    set_oyytext(yytext);
}

<ctxDefineDefn>{NL} {
  LOG();
  set_token_and_yyposn(g.oyytext, yytext-g.oyytext, TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
  if(g.mDefLooksLike != kNoDef)
    RETURN(g.mDefLooksLike);
}

<ctxDefineDefn>"//".*{NL} {
  LOG();
  /* Ignore line comment when it does not stand alone in a line. */
  // We are also ignoring the last new-line character
  // It is because we want the #define to conclude if C++ comment is present at the end of #define.
  yyless(yyleng-1);
}

<ctxDefineDefn>{WS}*"/*"[^\n]*"*/"{WS}*/{NL} {
  LOG();
}

<ctxDefineDefn>{WS}*"/*" {
  LOG();
  BEGINCONTEXT(ctxBlockCommentInsideMacroDefn);
}

<ctxBlockCommentInsideMacroDefn>{NL} {
  LOG();
  set_token_and_yyposn(g.oyytext, yytext-g.oyytext, TokenSetupFlag::DisableCommentTokenization);
  ENDCONTEXT(); // End ctxBlockCommentInsideMacroDefn
  ENDCONTEXT(); // End ctxDefineDefn
  BEGINCONTEXT(ctxSideBlockComment);
  INCREMENT_INPUT_LINE_NUM();
  if(g.mDefLooksLike != kNoDef)
    RETURN(g.mDefLooksLike);
}

<ctxBlockCommentInsideMacroDefn>[^*\n]*"*"+"/" {
  LOG();
  ENDCONTEXT();
}

<ctxBlockCommentInsideMacroDefn>.*"*/"/{WS}*"\\"{WS}*{NL} {
  LOG();
  ENDCONTEXT();
}

<ctxBlockCommentInsideMacroDefn>.*"\\"{WS}*{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxPreprocessor>undef/{WS} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknUndef);
}

<ctxPreprocessor>include/{WS} {
  LOG();
  ENDCONTEXT();
  set_token_and_yyposn();
  BEGINCONTEXT(ctxInclude);
  RETURN(tknInclude);
}

<ctxPreprocessor>import/{WS} {
  LOG();
  ENDCONTEXT();
  set_token_and_yyposn();
  BEGINCONTEXT(ctxInclude);
  RETURN(tknImport);
}

<ctxInclude><.*> {
  LOG();
  set_token_and_yyposn();
  RETURN(tknStdHdrInclude);
}

<ctxInclude>{ID} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknStdHdrInclude);
}

<ctxInclude>{NL} {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxPreprocessor>if/{WS} {
  LOG();
  set_token_and_yyposn();
  set_oyytext(yytext+yyleng);
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknIf);
}

<ctxPreprocessor>ifdef/{WS} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknIfDef);
}

<ctxPreprocessor>ifndef/{WS} {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  RETURN(tknIfNDef);
}

<ctxGeneral,ctxPreprocessor>else/{TS} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknElse);
}

<ctxPreprocessor>elif/{WS} {
  LOG();
  set_token_and_yyposn();
  set_oyytext(yytext+yyleng);
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknElIf);
}

<ctxPreprocessor>endif/{TS} {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  RETURN(tknEndIf);
}

<ctxGeneral>^{WS}*#{WS}*if/{WS}*"0" {
  LOG();
  set_oyytext(yytext);
  BEGINCONTEXT(ctxDisabledCode);
}

<ctxDisabledCode>. {
  LOG();
}

<ctxDisabledCode>{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxDisabledCode>^{WS}*#{WS}*endif[^\n]* {
  LOG();
  ENDCONTEXT();
  setBlobToken();
  RETURN(tknBlob);
}

<ctxPreprocessor>pragma/{WS} {
  LOG();
  set_token_and_yyposn();
  set_oyytext(yytext+yyleng);
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknPragma);
}

<ctxPreProBody>.*\\{WS}*{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxPreProBody>.* {
  LOG();
}

<ctxPreProBody>{NL} {
  LOG();
  set_token_and_yyposn(g.oyytext, yytext-g.oyytext, TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
  RETURN(tknPreProDef);
}

<ctxPreprocessor>{NL} {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxPreprocessor>error{WS}[^\n]*{NL} {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
  RETURN(tknHashError);
}

<ctxPreprocessor>warning{WS}[^\n]*{NL} {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
  RETURN(tknHashWarning);
}

<ctxGeneral>"::" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknScopeResOp);
}

<ctxGeneral>const/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknConst);
}

<ctxGeneral>constexpr/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknConstExpr);
}

<ctxGeneral>static/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknStatic);
}

<ctxGeneral>inline/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknInline);
}

<ctxGeneral>virtual/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknVirtual);
}

<ctxGeneral>override/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknOverride);
}

<ctxGeneral>final/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknFinal);
}

<ctxGeneral>noexcept/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknNoExcept);
}

<ctxGeneral>extern/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknExtern);
}

<ctxGeneral>explicit/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknExplicit);
}

<ctxGeneral>friend/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknFriend);
}

<ctxGeneral>"extern"{WS}+"\"C\"" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknExternC);
}

<ctxGeneral>volatile/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknVolatile);
}

<ctxGeneral>mutable/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknMutable);
}

<ctxGeneral>new/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknNew);
}

<ctxGeneral>delete/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDelete);
}

<ctxGeneral>default/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDefault);
}

<ctxGeneral>return/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknReturn);
}

<ctxGeneral>if/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknIf);
}

<ctxGeneral>else/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknElse);
}

<ctxGeneral>for/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknFor);
}

<ctxGeneral>do/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDo);
}

<ctxGeneral>while/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknWhile);
}

<ctxGeneral>switch/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknSwitch);
}

<ctxGeneral>case/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknCase);
}

<ctxGeneral>const_cast/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknConstCast);
}

<ctxGeneral>static_cast/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknStaticCast);
}

<ctxGeneral>dynamic_cast/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDynamicCast);
}

<ctxGeneral>reinterpret_cast/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknReinterpretCast);
}

<ctxGeneral>try/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknTry);
}

<ctxGeneral>catch/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknCatch);
}

<ctxGeneral>throw/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknThrow);
}

<ctxGeneral>sizeof/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknSizeOf);
}

<ctxGeneral>operator/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknOperator);
}

<ctxGeneral>void/{TS}+ {
  LOG();
  set_token_and_yyposn();
  RETURN(tknVoid);
}

<ctxGeneral>"+=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknPlusEq);
}

<ctxGeneral>"-=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknMinusEq);
}

<ctxGeneral>"*=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknMulEq);
}

<ctxGeneral>"*=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknMulEq);
}

<ctxGeneral>"/=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDivEq);
}

<ctxGeneral>"%=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknPerEq);
}

<ctxGeneral>"^=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknXorEq);
}

<ctxGeneral>"&=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknAndEq);
}

<ctxGeneral>"|=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknOrEq);
}

<ctxGeneral>"<<" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknLShift);
}

<ctxGeneral>"<<=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknLShiftEq);
}

<ctxGeneral>">>=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknRShiftEq);
}

<ctxGeneral>"==" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknCmpEq);
}

<ctxGeneral>"!=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknNotEq);
}

<ctxGeneral>"<=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknLessEq);
}

<ctxGeneral>">=" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknGreaterEq);
}

<ctxGeneral>"<=>" {
  LOG();
  set_token_and_yyposn();
  RETURN(tkn3WayCmp);
}

<ctxGeneral>"&&" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknAnd);
}

<ctxGeneral>"||" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknOr);
}

<ctxGeneral>"++" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknInc);
}

<ctxGeneral>"--" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknDec);
}

<ctxGeneral>"->" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknArrow);
}

<ctxGeneral>"->*" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknArrowStar);
}

<ctxGeneral,ctxDefine>{NUM} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknNumber);
}

<ctxGeneral>{DECNUMLIT}((e|E)[+-]?{DECNUMLIT})? {
  LOG();
  set_token_and_yyposn();
  RETURN(tknNumber);
}

<ctxGeneral,ctxInclude>{SL} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknStrLit);
}

<ctxGeneral>(L)?{SL} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknStrLit);
}

<ctxGeneral>(L)?{CL} {
  LOG();
  set_token_and_yyposn();
  RETURN(tknCharLit);
}

<ctxGeneral>"("|"[" {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::DisableCommentTokenization);
  g.mBracketDepthStack.back() = g.mBracketDepthStack.back() + 1;
  RETURN(yytext[0]);
}

<ctxGeneral>")"|"]" {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::None);
  g.mBracketDepthStack.back() = g.mBracketDepthStack.back() - 1;
  RETURN(yytext[0]);
}

<ctxGeneral>"{" {
  LOG();
  if (g.mEnumBodyWillBeEncountered)
  {
    g.mEnumBodyWillBeEncountered = false;
    BEGINCONTEXT(ctxEnumBody);
    set_token_and_yyposn(TokenSetupFlag::None);
    set_oyytext(yytext+1);
  }
  else if (g.mFunctionBodyWillBeEncountered && (yytext == g.mExpectedBracePosition))
  {

    g.mFunctionBodyWillBeEncountered = false;
    BEGINCONTEXT(ctxFunctionBody);
    set_token_and_yyposn(TokenSetupFlag::DisableCommentTokenization);
    set_oyytext(yytext+1);
  }
  else
  {

    g.mBracketDepthStack.push_back(0);
    set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  }
  RETURN(yytext[0]);
}

<ctxGeneral>"}" {
  LOG();
  g.mBracketDepthStack.resize(g.mBracketDepthStack.size() - 1);
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  RETURN(yytext[0]);
}

<ctxEnumBody>"}" {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::None);
  ENDCONTEXT();
  RETURN(yytext[0]);
}

<ctxEnumBody>[^\}\n]* {
  LOG();
  // printf("%s", yytext);
}

<ctxEnumBody>{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxEnumBody>{NL}/"}" {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
  setBlobToken();
  RETURN(tknBlob);
}

<ctxEnumBody>([^\}\n]*|^{WS}*)/"}" {
  LOG();
  setBlobToken();
  RETURN(tknBlob);
}

<ctxFunctionBody>"{" {
  LOG();
  ++g.mNestedCurlyBracketDepth;
}

<ctxFunctionBody>"}" {
  LOG();
  if (g.mNestedCurlyBracketDepth == 0)
  {
    ENDCONTEXT();
    set_token_and_yyposn(TokenSetupFlag::EnableCommentTokenization);
    RETURN(yytext[0]);
  }
  else
  {
    --g.mNestedCurlyBracketDepth;
  }
}

<ctxFunctionBody>{NL}/"}" {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
  if (g.mNestedCurlyBracketDepth == 0)
  {
    setBlobToken();
    RETURN(tknBlob);
  }
}

<ctxFunctionBody>([^{}\n]|{WS}*)/"}" {
  LOG();
  if (g.mNestedCurlyBracketDepth == 0)
  {
    setBlobToken();
    RETURN(tknBlob);
  }
}

<ctxFunctionBody>{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxFunctionBody>. {
  LOG();
  // printf("%s", yytext);
}

<ctxGeneral>":" {
  LOG();
  if (g.mMemInitListWillBeEncountered && (g.mExpectedColonPosition == yytext))
  {

    g.mMemInitListWillBeEncountered = false;
    set_oyytext(yytext+1);
    BEGINCONTEXT(ctxMemInitList);
  }
  set_token_and_yyposn(TokenSetupFlag::None);
  RETURN(yytext[0]);
}

<ctxMemInitList>({ID2}{WSNL}*)/"(" {
  LOG();
  g.mPossibleFuncImplStartBracePosition = findMatchedClosingBracket(yytext+yyleng, '(') + 1;
}

<ctxMemInitList>({ID2}{WSNL}*)/"{" {
  LOG();
  g.mPossibleFuncImplStartBracePosition = findMatchedClosingBracket(yytext+yyleng, '{') + 1;
}

<ctxMemInitList>(.) {
  LOG();
  // Just ignore
}

<ctxMemInitList>({NL}) {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxMemInitList>([^a-zA-Z_]*|{NL})/"{" {
  LOG();

  if (yytext[0] == '\n')
    INCREMENT_INPUT_LINE_NUM();

  if (yytext+yyleng >= g.mPossibleFuncImplStartBracePosition)
  {
    ENDCONTEXT();
    g.mExpectedBracePosition = yytext+yyleng;
    g.mFunctionBodyWillBeEncountered = true;
    setBlobToken();
    RETURN(tknBlob);
  }
}

<ctxGeneral>; {
  LOG();
  set_token_and_yyposn();
  g.mTokenizeComment = true;
  RETURN(yytext[0]);
}

<ctxGeneral>, {
  LOG();
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  RETURN(yytext[0]);
}

<ctxGeneral>\)|\]|#|=|\*|\+|-|\.|\/|\~|%|\^|&|\||\?|\! {
  LOG();
  set_token_and_yyposn();
  RETURN(yytext[0]);
}

<ctxGeneral>">" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknGT);
}

<ctxGeneral>"<" {
  LOG();
  set_token_and_yyposn();
  RETURN(tknLT);
}

<ctxGeneral>\.\.\. {
  LOG();
  set_token_and_yyposn();
  RETURN(tknEllipsis);
}

<*>{WS}+ {
  /* Ignore white spaces */
}

<*>\\{WS}*{NL} {
  // We will always ignore line continuation character
  INCREMENT_INPUT_LINE_NUM();
}

<*>__attribute__{WS}*\(\(.*\)\) {
  /* Ignore as of now */
}

%%

const char* contextNameFromState(int ctx)
{
  switch (ctx) {
    case INITIAL :
      return "INITIAL";
    case ctxGeneral :
      return "ctxGeneral";
    case ctxFreeStandingBlockComment :
      return "ctxFreeStandingBlockComment";
    case ctxSideBlockComment :
      return "ctxSideBlockComment";
    case ctxBlockCommentInsideMacroDefn :
      return "ctxBlockCommentInsideMacroDefn";
    case ctxPreprocessor :
      return "ctxPreprocessor";
    case ctxInclude :
      return "ctxInclude";
    case ctxDefine :
      return "ctxDefine";
    case ctxDefineDefn :
      return "ctxDefineDefn";
    case ctxPreProBody :
      return "ctxPreProBody";
    case ctxEnumBody :
      return "ctxEnumBody";
    case ctxFunctionBody :
      return "ctxFunctionBody";
    case ctxDisabledCode :
      return "ctxDisabledCode";
    case ctxMemInitList :
      return "ctxMemInitList";
  }

  return "UNKNOWNCONTEXT";
}

static YY_BUFFER_STATE gParseBuffer = nullptr;
void setupScanBuffer(char* buf, size_t bufsize)
{
  gParseBuffer = yy_scan_buffer(buf, bufsize);
  g = LexerData();

  BEGIN(ctxGeneral);
}

void cleanupScanBuffer()
{
  yy_delete_buffer(gParseBuffer);
  gParseBuffer = nullptr;

  g = LexerData();
}
