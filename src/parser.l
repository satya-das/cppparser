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
#include "lexer-helper.h"
#include <iostream>

/// @{ Global data
LexerData g;

// Externally controlled data
// These do not get reset on change of input file
extern bool gParseEnumBodyAsBlob;
extern bool gParseFunctionBodyAsBlob;

extern std::set<std::string>        gMacroNames;
extern std::set<std::string>        gKnownApiDecorNames;
extern std::map<std::string, int>   gDefinedNames;
extern std::set<std::string>        gUndefinedNames;
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

int getLexerContext()
{
  return YYSTATE;
}

static void setOldYytext(const char* p)
{
  g.mOldYytext = p;
}

static void setCommentTokenizationState(TokenSetupFlag flag)
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

static void setupToken(const char* text, size_t len, TokenSetupFlag flag = TokenSetupFlag::DisableCommentTokenization)
{
  extern char* yyposn;
  yyposn = const_cast<char*>(text);
  yylval.str = makeCppToken(text, len);

  setCommentTokenizationState(flag);
}

static void setupToken(TokenSetupFlag flag = TokenSetupFlag::DisableCommentTokenization)
{
  setupToken(yytext, yyleng, flag);
}

static void setBlobToken(TokenSetupFlag flag = TokenSetupFlag::None)
{
  setupToken(g.mOldYytext, yytext+yyleng-g.mOldYytext, flag);
}

using YYLessProc = std::function<void(int)>;

// yyless is not available outside of lexing context.
// So, yylessfn is the callback that caller needs to pass
// that just calls yyless();
static void tokenizeBracketedContent(YYLessProc yylessfn)
{
  // yyinput() has bug (see https://github.com/westes/flex/pull/396)
  // So, I am exploiting yyless() by passing value bigger than yyleng.
  const auto savedlen = yyleng;
  const auto input = [&]() {
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
  setupToken();
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

static bool codeSegmentDependsOnMacroDefinition()
{
  return g.currentCodeEnablementInfo.macroDependentCodeEnablement != MacroDependentCodeEnablement::kNoInfo;
}

static void startNewMacroDependentParsing()
{
  if (codeSegmentDependsOnMacroDefinition()) {
    g.codeEnablementInfoStack.push_back(g.currentCodeEnablementInfo);
  }
  g.currentCodeEnablementInfo = {};
}

static void updateMacroDependence()
{
  if (!g.codeEnablementInfoStack.empty()) {
    g.currentCodeEnablementInfo = g.codeEnablementInfoStack.back();
    g.codeEnablementInfoStack.resize(g.codeEnablementInfoStack.size()-1);
  } else {
    g.currentCodeEnablementInfo = {};
  }
}

%}

%option never-interactive
%option stack
%option noyy_top_state
%option noyywrap

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
  setupToken();
  RETURN(tknName);
}

<ctxGeneral>"__declspec"{WS}*"("{WS}*{ID}{WS}*")" {
  LOG();
  setupToken();
  RETURN(tknApiDecor);
}

<ctxGeneral>__cdecl {
  LOG();
  setupToken();
  RETURN(tknApiDecor);
}

<ctxGeneral>__stdcall {
  LOG();
  setupToken();
  RETURN(tknApiDecor);
}

<ctxGeneral>afx_msg {
  LOG();
  setupToken();
  RETURN(tknApiDecor);
}

<ctxGeneral>"alignas"{WS}*"("{WS}*{ID}{WS}*")" {
  LOG();
  setupToken();
  RETURN(tknApiDecor);
}

<ctxGeneral>"alignas"{WS}*"("{WS}*{NUM}{WS}*")" {
  LOG();
  setupToken();
  RETURN(tknApiDecor);
}

<ctxGeneral>{ID} {
  LOG();
  if (gIgnorableMacroNames.count(yytext))
  {
    tokenizeBracketedContent([&](int l) { yyless(l); } );
    // Nothing to return. Just ignore
  }
  else
  {
    if (gMacroNames.count(yytext))
    {
      tokenizeBracketedContent([&](int l) { yyless(l); } );
      RETURN(tknMacro);
    }

    if (gKnownApiDecorNames.count(yytext))
    {
      setupToken();
      RETURN(tknApiDecor);
    }

    setupToken();
    auto itr = gRenamedKeywords.find(yylval.str);
    if (itr != gRenamedKeywords.end())
      return itr->second;
    RETURN(tknName);
  }
}

<ctxGeneral>")"{WSNL}*({FTA}{WSNL}*)*{WSNL}*"{" {
  LOG();
  if (gParseFunctionBodyAsBlob)
  {
    g.mFunctionBodyWillBeEncountered = true;
    g.mExpectedBracePosition = yytext + yyleng-1;
  }

  REJECT;
}

<ctxGeneral>")"{WSNL}*":"/{WSNL}{ID2}("("|"{") {
  LOG();
  if (gParseFunctionBodyAsBlob)
  {
    g.mMemInitListWillBeEncountered = true;
    g.mExpectedColonPosition = yytext + yyleng-1;
  }

  REJECT;
}

<ctxGeneral>asm/{TS} {
  LOG();
  tokenizeBracketedContent([&](int l) { yyless(l); } );
  RETURN(tknAsm);
}

<ctxGeneral>goto/{TS} {
  LOG();
  RETURN(tknGoto);
}

<ctxGeneral>signed|unsigned/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknNumSignSpec);
}

<ctxGeneral>long{WS}+long{WS}+int|long{WS}+long|long{WS}+int|long|int|short{WS}+int|short/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknInteger);
}

<ctxGeneral>__int8|__int16|__int32|__int64|__int128/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknInteger);
}

<ctxGeneral>char/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknChar);
}

<ctxGeneral>long{WS}+double|double/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknDouble);
}

<ctxGeneral>long{WS}+float|float/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknFloat);
}

<ctxGeneral>auto/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknAuto);
}

<ctxGeneral>typedef{TS}+ {
  LOG();
  setupToken();
  RETURN(tknTypedef);
}

<ctxGeneral>using{TS}+ {
  LOG();
  setupToken();
  RETURN(tknUsing);
}

<ctxGeneral>class/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknClass);
}

<ctxGeneral>namespace/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknNamespace);
}

<ctxGeneral>struct/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknStruct);
}

<ctxGeneral>union/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknUnion);
}

<ctxGeneral>enum/{WS}+(class{WS}+)?{ID}?({WS}*":"{WS}*{ID})?{WSNL}*"{" {
  LOG();
  setupToken();
  if (gParseEnumBodyAsBlob)
    g.mEnumBodyWillBeEncountered = true;
  RETURN(tknEnum);
}

<ctxGeneral>enum/{TS} {
  LOG();
  setupToken();
  RETURN(tknEnum);
}

<ctxGeneral>public/{WS}*":" {
  LOG();
  setupToken(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknPublic);
}

<ctxGeneral>public/{TS} {
  LOG();
  setupToken();
  RETURN(tknPublic);
}

<ctxGeneral>protected/{WS}*":" {
  LOG();
  setupToken(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknProtected);
}

<ctxGeneral>protected/{TS} {
  LOG();
  setupToken();
  RETURN(tknProtected);
}

<ctxGeneral>private/{WS}*":" {
  LOG();
  setupToken(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknPrivate);
}

<ctxGeneral>private/{TS} {
  LOG();
  setupToken();
  RETURN(tknPrivate);
}

<ctxGeneral>template/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknTemplate);
}

<ctxGeneral>typename/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknTypename);
}

<ctxGeneral>decltype/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknDecltype);
}

<ctxGeneral>^{WS}*"/*" {
  LOG();
  setOldYytext(yytext);
  BEGINCONTEXT(ctxFreeStandingBlockComment);
}

<*>"/*" {
  /*
  Ignore side comments for time being
  setOldYytext(yytext);
  */
  BEGINCONTEXT(ctxSideBlockComment);
}

<ctxFreeStandingBlockComment>[^*\n]*"*"+"/"/{WS}*{NL} {
  LOG();
  ENDCONTEXT();
  if (g.mTokenizeComment)
  {
    setupToken(g.mOldYytext, yytext+yyleng-g.mOldYytext, TokenSetupFlag::None);
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
    setupToken(g.mOldYytext, yytext+yyleng-g.mOldYytext, TokenSetupFlag::None);
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
    setupToken(TokenSetupFlag::None);
    RETURN(tknFreeStandingLineComment);
  }
}

<*>"//"[^\n]* {
  if (g.mTokenizeComment)
  {
    setupToken(TokenSetupFlag::None);
    // Ignore side comments for time being
    // RETURN(tknSideLineComment);
  }
}

<ctxGeneral>^{WS}*# {
  LOG();
  setupToken();
  BEGINCONTEXT(ctxPreprocessor);
  RETURN(tknPreProHash);
}

<ctxPreprocessor>define/{WS} {
  LOG();
  setupToken();
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
  setupToken();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  g.mDefLooksLike = kComplexDef;
  setOldYytext(yytext + yyleng);
  RETURN(tknName);
}

<ctxDefine>{ID}\(.*"...".*\) {
  LOG();
  setupToken();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  g.mDefLooksLike = kComplexDef;
  setOldYytext(yytext + yyleng);
  RETURN(tknName);
}

<ctxDefine>{ID} {
  LOG();
  setupToken();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  g.mDefLooksLike = kNoDef;
  setOldYytext(0);
  RETURN(tknName);
}

<ctxDefineDefn>{ID} {
  LOG();
  if(g.mDefLooksLike == kNoDef)
  {
    g.mDefLooksLike = kReDef;
    setOldYytext(yytext);
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
    if (g.mOldYytext == 0)
      setOldYytext(yytext);
    g.mDefLooksLike = kComplexDef;
  }
}

<ctxDefineDefn>{SL} {
  LOG();
  if(g.mDefLooksLike == kNoDef || g.mDefLooksLike == kStrLitDef || g.mDefLooksLike == kReDef)
  {
    g.mDefLooksLike = kStrLitDef;
    if(g.mOldYytext == 0)
      setOldYytext(yytext);
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
    setOldYytext(yytext);
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
    setOldYytext(yytext);
  }
  else
  { // It does not look like simple #define.
    g.mDefLooksLike = kComplexDef;
  }
}

<ctxDefineDefn>[^\t\r\n ] { // Any unrecognized character other than whitespace indicates a complex #define
  LOG();
  g.mDefLooksLike = kComplexDef;
  if(g.mOldYytext == 0)
    setOldYytext(yytext);
}

<ctxDefineDefn>{NL} {
  LOG();
  setupToken(g.mOldYytext, yytext-g.mOldYytext, TokenSetupFlag::ResetCommentTokenization);
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
  yyless((yyleng-1));
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
  setupToken(g.mOldYytext, yytext-g.mOldYytext, TokenSetupFlag::DisableCommentTokenization);
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
  setupToken();
  RETURN(tknUndef);
}

<ctxPreprocessor>include/{WS} {
  LOG();
  ENDCONTEXT();
  setupToken();
  BEGINCONTEXT(ctxInclude);
  RETURN(tknInclude);
}

<ctxPreprocessor>import/{WS} {
  LOG();
  ENDCONTEXT();
  setupToken();
  BEGINCONTEXT(ctxInclude);
  RETURN(tknImport);
}

<ctxInclude><.*> {
  LOG();
  setupToken();
  RETURN(tknStdHdrInclude);
}

<ctxInclude>{ID} {
  LOG();
  setupToken();
  RETURN(tknStdHdrInclude);
}

<ctxInclude>{NL} {
  LOG();
  setupToken(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxPreprocessor>if/{WS} {
  LOG();

  if (codeSegmentDependsOnMacroDefinition())
    g.currentCodeEnablementInfo.numHashIfInMacroDependentCode += 1;

  setupToken();
  setOldYytext(yytext+yyleng);
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknIf);
}

<ctxPreprocessor>ifdef/{WS} {
  LOG();

  if (codeSegmentDependsOnMacroDefinition())
    g.currentCodeEnablementInfo.numHashIfInMacroDependentCode += 1;

  setupToken();
  RETURN(tknIfDef);
}

<ctxPreprocessor>ifndef/{WS} {
  LOG();

  if (codeSegmentDependsOnMacroDefinition())
    g.currentCodeEnablementInfo.numHashIfInMacroDependentCode += 1;

  setupToken(TokenSetupFlag::ResetCommentTokenization);
  RETURN(tknIfNDef);
}

<ctxPreprocessor>else/{TS} {
  LOG();
  setupToken();
  RETURN(tknElse);
}

<ctxPreprocessor>elif/{WS} {
  LOG();
  setupToken();
  setOldYytext(yytext+yyleng);
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknElIf);
}

<ctxPreprocessor>endif/{TS} {
  LOG();

  if (!codeSegmentDependsOnMacroDefinition() || (g.currentCodeEnablementInfo.numHashIfInMacroDependentCode != 0)) {
    if (g.currentCodeEnablementInfo.numHashIfInMacroDependentCode)
      g.currentCodeEnablementInfo.numHashIfInMacroDependentCode -= 1;

    setupToken(TokenSetupFlag::ResetCommentTokenization);
    ENDCONTEXT();
    RETURN(tknEndIf);
  }
}

<ctxGeneral>^{WS}*#{WS}*if/{WS}+"0" {
  LOG();
  setOldYytext(yytext);
  BEGINCONTEXT(ctxDisabledCode);
  startNewMacroDependentParsing();
  
  g.currentCodeEnablementInfo.macroDependentCodeEnablement = MacroDependentCodeEnablement::kDisabled;
}

<ctxGeneral>^{WS}*"#"{WS}*"if"{WS}+{ID}{WS}*("//"|"/*")?{NL} {
  LOG();

  std::string id(yyleng, '\0');
  sscanf(yytext, " # if %[a-zA-Z0-9_]", id.data());
  id.resize(strlen(id.data()));
  const auto idVal = getIdValue(id);
  if (!idVal.has_value()) {
    REJECT;
  }
  LOG();

  startNewMacroDependentParsing();
  g.currentCodeEnablementInfo.macroDependentCodeEnablement = (idVal.value() != 0)
                                    ? MacroDependentCodeEnablement::kEnabled
                                    : MacroDependentCodeEnablement::kDisabled;

  if (g.currentCodeEnablementInfo.macroDependentCodeEnablement == MacroDependentCodeEnablement::kDisabled) {
    BEGINCONTEXT(ctxDisabledCode);
  }
}

<ctxGeneral>^{WS}*"#"{WS}*"if"{WS}+{ID}{WS}*">="{WS}*{NUM}{WS}*("//"|"/*")?{NL} {
  LOG();

  std::string id(yyleng, '\0');
  int n=0;
  sscanf(yytext, " # if %[a-zA-Z0-9_] >= %d", id.data(), &n);
  id.resize(strlen(id.data()));
  const auto idVal = getIdValue(id);
  if (!idVal.has_value()) {
    REJECT;
  }

  startNewMacroDependentParsing();
  g.currentCodeEnablementInfo.macroDependentCodeEnablement = (idVal.value() >= n)
                                    ? MacroDependentCodeEnablement::kEnabled
                                    : MacroDependentCodeEnablement::kDisabled;

  if (g.currentCodeEnablementInfo.macroDependentCodeEnablement == MacroDependentCodeEnablement::kDisabled) {
    BEGINCONTEXT(ctxDisabledCode);
  }
}

<ctxGeneral>^{WS}*#{WS}*if{WS}+"!"{ID}{WS}*("//"|"/*")?{NL} {
  LOG();

  std::string id(yyleng, '\0');
  sscanf(yytext, " # if ! %[a-zA-Z0-9_]", id.data());
  id.resize(strlen(id.data()));
  const auto idVal = getIdValue(id);

  if (!idVal.has_value()) {
    REJECT;
  }

  startNewMacroDependentParsing();
  g.currentCodeEnablementInfo.macroDependentCodeEnablement = (!idVal.has_value() || idVal.value() == 0)
                                    ? MacroDependentCodeEnablement::kEnabled
                                    : MacroDependentCodeEnablement::kDisabled;

  if (g.currentCodeEnablementInfo.macroDependentCodeEnablement == MacroDependentCodeEnablement::kDisabled) {
    LOG();
    BEGINCONTEXT(ctxDisabledCode);
  }
}

<ctxGeneral>^{WS}*#{WS}*ifdef{WS}+{ID} {
  LOG();

  std::string id(yyleng, '\0');
  sscanf(yytext, " # ifdef %[a-zA-Z0-9_]", id.data());
  id.resize(strlen(id.data()));

  const auto macroDefineInfo = getMacroDefineInfo(id);
  if (macroDefineInfo == MacroDefineInfo::kNoInfo) {
    REJECT;
  }

  startNewMacroDependentParsing();
  g.currentCodeEnablementInfo.macroDependentCodeEnablement = (macroDefineInfo == MacroDefineInfo::kDefined)
                                    ? MacroDependentCodeEnablement::kEnabled
                                    : MacroDependentCodeEnablement::kDisabled;

  if (g.currentCodeEnablementInfo.macroDependentCodeEnablement == MacroDependentCodeEnablement::kDisabled) {
    LOG();
    BEGINCONTEXT(ctxDisabledCode);
  }
}

<ctxGeneral>^{WS}*#{WS}*ifndef{WS}+{ID} {
  LOG();

  std::string id(yyleng, '\0');
  sscanf(yytext, " # ifndef %[a-zA-Z0-9_]", id.data());
  id.resize(strlen(id.data()));

  const auto macroDefineInfo = getMacroDefineInfo(id);
  if (macroDefineInfo == MacroDefineInfo::kNoInfo) {
    REJECT;
  }

  startNewMacroDependentParsing();
  g.currentCodeEnablementInfo.macroDependentCodeEnablement = (macroDefineInfo == MacroDefineInfo::kUndefined)
                                    ? MacroDependentCodeEnablement::kEnabled
                                    : MacroDependentCodeEnablement::kDisabled;

  if (g.currentCodeEnablementInfo.macroDependentCodeEnablement == MacroDependentCodeEnablement::kDisabled) {
    LOG();
    BEGINCONTEXT(ctxDisabledCode);
  }
}

<ctxGeneral,ctxDisabledCode>^{WS}*#{WS}*else{TS} {
  LOG();
  if (!codeSegmentDependsOnMacroDefinition()) {
    LOG();
    REJECT;
  }

  LOG();
  if (g.currentCodeEnablementInfo.numHashIfInMacroDependentCode == 0) {
    g.currentCodeEnablementInfo.macroDependentCodeEnablement = invert(g.currentCodeEnablementInfo.macroDependentCodeEnablement);
    if (g.currentCodeEnablementInfo.macroDependentCodeEnablement == MacroDependentCodeEnablement::kDisabled) {
      BEGINCONTEXT(ctxDisabledCode);
    } else {
      ENDCONTEXT();
    }
  }
}

<ctxDisabledCode>. {
  LOG();
}

<ctxDisabledCode>{NL} {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxDisabledCode>^{WS}*#{WS}*if {
  g.currentCodeEnablementInfo.numHashIfInMacroDependentCode += 1;
}

<*>^{WS}*#{WS}*endif[^\n]* {
  LOG();

  if (!codeSegmentDependsOnMacroDefinition()) {
    REJECT;
  }

  if ((g.currentCodeEnablementInfo.numHashIfInMacroDependentCode != 0) && (YYSTATE != ctxDisabledCode)) {
    REJECT;
  }

  if (g.currentCodeEnablementInfo.numHashIfInMacroDependentCode == 0) {
    updateMacroDependence();
    if (YYSTATE == ctxDisabledCode) {
      ENDCONTEXT();
      if (g.parseDisabledCodeAsBlob) {
        setBlobToken();
        RETURN(tknBlob);
      }
    }
  } else {
    g.currentCodeEnablementInfo.numHashIfInMacroDependentCode -= 1;
  }
}

<ctxPreprocessor>pragma/{WS} {
  LOG();
  setupToken();
  setOldYytext(yytext+yyleng);
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
  setupToken(g.mOldYytext, yytext-g.mOldYytext, TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
  RETURN(tknPreProDef);
}

<ctxPreprocessor>{NL} {
  LOG();
  setupToken(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxPreprocessor>error{WS}[^\n]*{NL} {
  LOG();
  setupToken(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
  RETURN(tknHashError);
}

<ctxPreprocessor>warning{WS}[^\n]*{NL} {
  LOG();
  setupToken(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  INCREMENT_INPUT_LINE_NUM();
  RETURN(tknHashWarning);
}

<ctxGeneral>"::" {
  LOG();
  setupToken();
  RETURN(tknScopeResOp);
}

<ctxGeneral>const/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknConst);
}

<ctxGeneral>constexpr/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknConstExpr);
}

<ctxGeneral>static/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknStatic);
}

<ctxGeneral>inline/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknInline);
}

<ctxGeneral>virtual/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknVirtual);
}

<ctxGeneral>override/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknOverride);
}

<ctxGeneral>final/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknFinal);
}

<ctxGeneral>noexcept/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknNoExcept);
}

<ctxGeneral>extern/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknExtern);
}

<ctxGeneral>explicit/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknExplicit);
}

<ctxGeneral>friend/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknFriend);
}

<ctxGeneral>"extern"{WS}+"\"C\"" {
  LOG();
  setupToken();
  RETURN(tknExternC);
}

<ctxGeneral>volatile/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknVolatile);
}

<ctxGeneral>mutable/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknMutable);
}

<ctxGeneral>new/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknNew);
}

<ctxGeneral>delete/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknDelete);
}

<ctxGeneral>default/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknDefault);
}

<ctxGeneral>return/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknReturn);
}

<ctxGeneral>if/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknIf);
}

<ctxGeneral>else/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknElse);
}

<ctxGeneral>for/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknFor);
}

<ctxGeneral>do/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknDo);
}

<ctxGeneral>while/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknWhile);
}

<ctxGeneral>switch/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknSwitch);
}

<ctxGeneral>case/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknCase);
}

<ctxGeneral>const_cast/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknConstCast);
}

<ctxGeneral>static_cast/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknStaticCast);
}

<ctxGeneral>dynamic_cast/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknDynamicCast);
}

<ctxGeneral>reinterpret_cast/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknReinterpretCast);
}

<ctxGeneral>try/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknTry);
}

<ctxGeneral>catch/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknCatch);
}

<ctxGeneral>throw/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknThrow);
}

<ctxGeneral>sizeof/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknSizeOf);
}

<ctxGeneral>operator/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknOperator);
}

<ctxGeneral>void/{TS}+ {
  LOG();
  setupToken();
  RETURN(tknVoid);
}

<ctxGeneral>"+=" {
  LOG();
  setupToken();
  RETURN(tknPlusEq);
}

<ctxGeneral>"-=" {
  LOG();
  setupToken();
  RETURN(tknMinusEq);
}

<ctxGeneral>"*=" {
  LOG();
  setupToken();
  RETURN(tknMulEq);
}

<ctxGeneral>"*=" {
  LOG();
  setupToken();
  RETURN(tknMulEq);
}

<ctxGeneral>"/=" {
  LOG();
  setupToken();
  RETURN(tknDivEq);
}

<ctxGeneral>"%=" {
  LOG();
  setupToken();
  RETURN(tknPerEq);
}

<ctxGeneral>"^=" {
  LOG();
  setupToken();
  RETURN(tknXorEq);
}

<ctxGeneral>"&=" {
  LOG();
  setupToken();
  RETURN(tknAndEq);
}

<ctxGeneral>"|=" {
  LOG();
  setupToken();
  RETURN(tknOrEq);
}

<ctxGeneral>"<<" {
  LOG();
  setupToken();
  RETURN(tknLShift);
}

<ctxGeneral>"<<=" {
  LOG();
  setupToken();
  RETURN(tknLShiftEq);
}

<ctxGeneral>">>=" {
  LOG();
  setupToken();
  RETURN(tknRShiftEq);
}

<ctxGeneral>"==" {
  LOG();
  setupToken();
  RETURN(tknCmpEq);
}

<ctxGeneral>"!=" {
  LOG();
  setupToken();
  RETURN(tknNotEq);
}

<ctxGeneral>"<=" {
  LOG();
  setupToken();
  RETURN(tknLessEq);
}

<ctxGeneral>">=" {
  LOG();
  setupToken();
  RETURN(tknGreaterEq);
}

<ctxGeneral>"<=>" {
  LOG();
  setupToken();
  RETURN(tkn3WayCmp);
}

<ctxGeneral>"&&" {
  LOG();
  setupToken();
  RETURN(tknAnd);
}

<ctxGeneral>"||" {
  LOG();
  setupToken();
  RETURN(tknOr);
}

<ctxGeneral>"++" {
  LOG();
  setupToken();
  RETURN(tknInc);
}

<ctxGeneral>"--" {
  LOG();
  setupToken();
  RETURN(tknDec);
}

<ctxGeneral>"->" {
  LOG();
  setupToken();
  RETURN(tknArrow);
}

<ctxGeneral>"->*" {
  LOG();
  setupToken();
  RETURN(tknArrowStar);
}

<ctxGeneral,ctxDefine>{NUM} {
  LOG();
  setupToken();
  RETURN(tknNumber);
}

<ctxGeneral>{DECNUMLIT}((e|E)[+-]?{DECNUMLIT})? {
  LOG();
  setupToken();
  RETURN(tknNumber);
}

<ctxGeneral,ctxInclude>{SL} {
  LOG();
  setupToken();
  RETURN(tknStrLit);
}

<ctxGeneral>(L)?{SL} {
  LOG();
  setupToken();
  RETURN(tknStrLit);
}

<ctxGeneral>(L)?{CL} {
  LOG();
  setupToken();
  RETURN(tknCharLit);
}

<ctxGeneral>"("|"[" {
  LOG();
  setupToken(TokenSetupFlag::DisableCommentTokenization);
  g.mBracketDepthStack.back() = g.mBracketDepthStack.back() + 1;
  RETURN(yytext[0]);
}

<ctxGeneral>")"|"]" {
  LOG();
  setupToken(TokenSetupFlag::None);
  g.mBracketDepthStack.back() = g.mBracketDepthStack.back() - 1;
  RETURN(yytext[0]);
}

<ctxGeneral>"{" {
  LOG();
  if (g.mEnumBodyWillBeEncountered)
  {
    g.mEnumBodyWillBeEncountered = false;
    BEGINCONTEXT(ctxEnumBody);
    setupToken(TokenSetupFlag::None);
    setOldYytext(yytext+1);
  }
  else if (g.mFunctionBodyWillBeEncountered && (yytext == g.mExpectedBracePosition))
  {

    g.mFunctionBodyWillBeEncountered = false;
    BEGINCONTEXT(ctxFunctionBody);
    setupToken(TokenSetupFlag::DisableCommentTokenization);
    setOldYytext(yytext+1);
  }
  else
  {

    g.mBracketDepthStack.push_back(0);
    setupToken(TokenSetupFlag::ResetCommentTokenization);
  }
  RETURN(yytext[0]);
}

<ctxGeneral>"}" {
  LOG();
  g.mBracketDepthStack.resize(g.mBracketDepthStack.size() - 1);
  setupToken(TokenSetupFlag::ResetCommentTokenization);
  RETURN(yytext[0]);
}

<ctxEnumBody>"}" {
  LOG();
  setupToken(TokenSetupFlag::None);
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
    setupToken(TokenSetupFlag::EnableCommentTokenization);
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
    setOldYytext(yytext+1);
    BEGINCONTEXT(ctxMemInitList);
  }
  setupToken(TokenSetupFlag::None);
  RETURN(yytext[0]);
}

<ctxMemInitList>({ID2}{WSNL}*)/"(" {
  LOG();
  g.mPossibleFuncImplStartBracePosition = findMatchedClosingBracket(yytext+yyleng, '(') + 1;
  yyless((g.mPossibleFuncImplStartBracePosition - yytext));
}

<ctxMemInitList>({ID2}{WSNL}*)/"{" {
  LOG();
  g.mPossibleFuncImplStartBracePosition = findMatchedClosingBracket(yytext+yyleng, '{') + 1;
  yyless((g.mPossibleFuncImplStartBracePosition - yytext));
}

<ctxMemInitList>^{WS}*"#"{WS}*"if"(.*)/{TS} {
  LOG();
}

<ctxMemInitList>^{WS}*"#"{WS}*"endif"/{TS} {
  LOG();
}

<ctxMemInitList>({NL}) {
  LOG();
  INCREMENT_INPUT_LINE_NUM();
}

<ctxMemInitList>(.) {
  LOG();
  if (yytext[0] == '\n')
  {
    INCREMENT_INPUT_LINE_NUM();
  }
  else if(yytext[0] == '{')
  {
    LOG();
    if (yytext+yyleng >= g.mPossibleFuncImplStartBracePosition)
    {
      LOG();
      ENDCONTEXT();
      g.mExpectedBracePosition = yytext;
      g.mFunctionBodyWillBeEncountered = true;
      yyless(0); // Return back the '{' to be processed
      setBlobToken();
      RETURN(tknBlob);
    }
  }
}

<ctxGeneral>; {
  LOG();
  setupToken();
  g.mTokenizeComment = true;
  RETURN(yytext[0]);
}

<ctxGeneral>, {
  LOG();
  setupToken(TokenSetupFlag::ResetCommentTokenization);
  RETURN(yytext[0]);
}

<ctxGeneral>\)|\]|#|=|\*|\+|-|\.|\/|\~|%|\^|&|\||\?|\! {
  LOG();
  setupToken();
  RETURN(yytext[0]);
}

<ctxGeneral>">" {
  LOG();
  setupToken();
  RETURN(tknGT);
}

<ctxGeneral>"<" {
  LOG();
  setupToken();
  RETURN(tknLT);
}

<ctxGeneral>\.\.\. {
  LOG();
  setupToken();
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
