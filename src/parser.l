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

#include "cpptoken.h"
#include "cppvarinit.h"
#include "parser.tab.h"

#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int gLexLog = 0;
/**
 * Comments can appear anywhere in a C/C++ program and unfortunately not all coments can be preserved.
 *
 * gTokenizeComment is a flag used to decide if we can tokenize comments.

 * For details of what kind of comments are preserved and what kind are lost, see file test/e2e/test_input/comment_test.h
 */
static bool gTokenizeComment = false;

using BracketDepthStack = std::vector<int>;
/**
 * We need to keep track of where we are inside the nest of brackets for knowing when we can tokenize comments.
 * Since we only want to preserve free standing comments and some side comments (in future improvements)
 * we need to always ignore comments that are inside square brackets, i.e. [].
 * We also need to ignore comments that are inside round brackets, i.e. (),
 * except when we are inside lambda which is being passed to a function as parameter:
 *    func([]() {
        // This comment should be preserved even when we are eventually inside a round bracket
      } // And this comment should be ignored
      ) // This one too;
 */
BracketDepthStack gBracketDepthStack = {0};

extern std::set<std::string>        gMacroNames;
extern std::set<std::string>        gKnownApiDecorNames;
extern std::set<std::string>        gIgnorableMacroNames;
extern std::map<std::string, int>   gRenamedKeywords;

  // Easy MACRO to quickly push current context and switch to another one.
#define BEGINCONTEXT(ctx) { \
  int prevState = YYSTATE;  \
  yy_push_state(ctx);       \
  if (gLexLog)                 \
    printf("@line#%d, pushed state=%d and started state=%d from source code line#%d\n", gLineNo, prevState, YYSTATE, __LINE__); \
}

#define ENDCONTEXT() {      \
  int prevState = YYSTATE;  \
  yy_pop_state();           \
  if (gLexLog)                 \
    printf("@line#%d, ended state=%d and starting state=%d from source code line#%d\n", gLineNo, prevState, YYSTATE, __LINE__); \
}

static int LogAndReturn(int ret, int codelinenum, int srclinenum)
{
  if (gLexLog)
  {
    printf("Lex Info: code-line#%d: returning token %d with value '%s' found @line#%d\n",
      codelinenum, ret, yytext, srclinenum);
  }
  return ret;
}

#define RETURN(ret)	return LogAndReturn(ret, __LINE__, gLineNo)

//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#  define fileno _fileno /* Avoid compiler warning for VS. */
#endif //#ifdef WIN32

extern int gLineNo;
const char* oyytext;

//@{ Flags to parse enum body as a blob
bool gEnumBodyWillBeEncountered = false;
//@}

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

enum class TokenSetupFlag
{
  None,
  DisableCommentTokenization,
  EnableCommentTokenization,
  ResetCommentTokenization
};

void setCommentTokenizationState(TokenSetupFlag flag)
{
  switch(flag)
  {
    case TokenSetupFlag::DisableCommentTokenization:
      gTokenizeComment = false;
      break;
    case TokenSetupFlag::EnableCommentTokenization:
      gTokenizeComment = true;
      break;
    case TokenSetupFlag::ResetCommentTokenization:
      gTokenizeComment = (!gBracketDepthStack.empty()) && (gBracketDepthStack.back() == 0);
      break;
    case TokenSetupFlag::None:
      // Nothing to do
      break;
  }
}

static void set_token_and_yyposn(const char* text, size_t len, TokenSetupFlag flag)
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
        ++gLineNo;
      }
    }
  }
  else
  {
    yylessfn(savedlen);
  }
  set_token_and_yyposn();
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

  /* Number */
NUM  ([0-9]+((l|L|u|U)*|(\.[0-9]*)?))|\.[0-9]+|(0(b|B)[01']*)|(0(x|X)[0-9a-fA-F]*)|0(x|X)[0-9a-zA-Z]+

DECNUMLIT  (([0-9]+(\.[0-9]*)?)|([0-9]*(\.[0-9]+)))(f|F)?

  /* String literal */
SL   \"([^"\\]|\\.)*\"

  /* Char literal */
CL   \'([^'\\]|\\.)\'

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

%%

<ctxGeneral>^{WS}*{NL} {
  ++gLineNo;
}

<ctxGeneral,ctxFreeStandingBlockComment,ctxSideBlockComment>{NL} {
  ++gLineNo;
}

<ctxPreprocessor>{ID} {
  set_token_and_yyposn();
  RETURN(tknID);
}

<ctxGeneral>__declspec {
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>alignas {
  set_token_and_yyposn();
  RETURN(tknApiDecor);
}

<ctxGeneral>{ID} {
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
    RETURN(tknID);
  }
}

<ctxGeneral>asm/{TS} {
  tokenize_bracketed_content([&](int l) { yyless(l); } );
  RETURN(tknAsm);
}

<ctxGeneral>signed|unsigned/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknNumSignSpec);
}

<ctxGeneral>long{WS}+long{WS}+int|long{WS}+long|long{WS}+int|long|int|short{WS}+int|short/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknInteger);
}

<ctxGeneral>__int8|__int16|__int32|__int64|__int128/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknInteger);
}

<ctxGeneral>char/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknChar);
}

<ctxGeneral>auto/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknAuto);
}

<ctxGeneral>typedef{TS}+ {
  set_token_and_yyposn();
  RETURN(tknTypedef);
}

<ctxGeneral>using{TS}+ {
  set_token_and_yyposn();
  RETURN(tknUsing);
}

<ctxGeneral>class/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknClass);
}

<ctxGeneral>namespace/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknNamespace);
}

<ctxGeneral>struct/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknStruct);
}

<ctxGeneral>union/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknUnion);
}

<ctxGeneral>enum/{WS}+(class{WS}+)?{ID}?({WS}*":"{WS}*{ID})?{WSNL}*"{" {
  set_token_and_yyposn();
  gEnumBodyWillBeEncountered = true;
  RETURN(tknEnum);
}

<ctxGeneral>enum/{TS} {
  set_token_and_yyposn();
  RETURN(tknEnum);
}

<ctxGeneral>public/{WS}*":" {
  set_token_and_yyposn(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknPublic);
}

<ctxGeneral>public/{TS} {
  set_token_and_yyposn();
  RETURN(tknPublic);
}

<ctxGeneral>protected/{WS}*":" {
  set_token_and_yyposn(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknProtected);
}

<ctxGeneral>protected/{TS} {
  set_token_and_yyposn();
  RETURN(tknProtected);
}

<ctxGeneral>private/{WS}*":" {
  set_token_and_yyposn(TokenSetupFlag::EnableCommentTokenization);
  RETURN(tknPrivate);
}

<ctxGeneral>private/{TS} {
  set_token_and_yyposn();
  RETURN(tknPrivate);
}

<ctxGeneral>template/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknTemplate);
}

<ctxGeneral>typename/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknTypename);
}

<ctxGeneral>decltype/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknDecltype);
}

<ctxGeneral>^{WS}*"/*" {
  oyytext = yytext;
  BEGINCONTEXT(ctxFreeStandingBlockComment);
}

<ctxGeneral>"/*" {
  oyytext = yytext;
  BEGINCONTEXT(ctxSideBlockComment);
}

<ctxFreeStandingBlockComment>[^*\n]*"*"+"/"/{WS}*{NL} {
  ENDCONTEXT();
  if (gTokenizeComment)
  {
    set_token_and_yyposn(oyytext, yytext+yyleng-oyytext, TokenSetupFlag::None);
    RETURN(tknFreeStandingBlockComment);
  }
}
<ctxFreeStandingBlockComment>[^*\n]*"*"+"/" {
  ENDCONTEXT();
}

<ctxSideBlockComment>[^*\n]*"*"+"/" {
  ENDCONTEXT();

  /*
  Ignore side comments for time being
  if (gTokenizeComment)
    set_token_and_yyposn(oyytext, yytext+yyleng-oyytext, TokenSetupFlag::None);
    RETURN(tknSideBlockComment);
  }
  */
}

<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>[^*\n]* {
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>[^*\n]*\n {
  ++gLineNo;
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>{WS}*"*"+[^*/\n]* {
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>{WS}*"*"+[^*/\n]*\n {
  ++gLineNo;
}
<ctxSideBlockComment,ctxFreeStandingBlockComment,ctxBlockCommentInsideMacroDefn>. {
}

<*>^{WS}*"//"[^\n]* {
  if (gTokenizeComment)
  {
    set_token_and_yyposn(TokenSetupFlag::None);
    RETURN(tknFreeStandingLineComment);
  }
}

<*>"//"[^\n]* {
  if (gTokenizeComment)
  {
    set_token_and_yyposn(TokenSetupFlag::None);
    // Ignore side comments for time being
    // RETURN(tknSideLineComment);
  }
}

<ctxGeneral>^{WS}*# {
  set_token_and_yyposn();
  BEGINCONTEXT(ctxPreprocessor);
  RETURN(tknPreProHash);
}

<ctxPreprocessor>define/{WS} {
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

<ctxDefine>{ID}\((({WS}*{ID}{WS}*,{WS}*)*{ID}{WS}*)*\) {
  set_token_and_yyposn();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  gDefLooksLike = kComplexDef;
  oyytext = yytext + yyleng;
  RETURN(tknID);
}

<ctxDefine>{ID} {
  set_token_and_yyposn();
  ENDCONTEXT();
  BEGINCONTEXT(ctxDefineDefn);
  gDefLooksLike = kNoDef;
  oyytext = 0;
  RETURN(tknID);
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
    if (oyytext == 0)
      oyytext = yytext;
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
  set_token_and_yyposn(oyytext, yytext-oyytext, TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  ++gLineNo;
  if(gDefLooksLike != kNoDef)
    RETURN(gDefLooksLike);
}

<ctxDefineDefn>"//".*{NL} {
  /* Ignore line comment when it does not stand alone in a line. */
  // We are also ignoring the last new-line character
  // It is because we want the #define to conclude if C++ comment is present at the end of #define.
  yyless(yyleng-1);
}

<ctxDefineDefn>{WS}*"/*"[^\n]*"*/"{WS}*/{NL} {
}

<ctxDefineDefn>{WS}*"/*" {
  BEGINCONTEXT(ctxBlockCommentInsideMacroDefn);
}

<ctxBlockCommentInsideMacroDefn>{NL} {
  set_token_and_yyposn(oyytext, yytext-oyytext, TokenSetupFlag::DisableCommentTokenization);
  ENDCONTEXT(); // End ctxBlockCommentInsideMacroDefn
  ENDCONTEXT(); // End ctxDefineDefn
  BEGINCONTEXT(ctxSideBlockComment);
  ++gLineNo;
  if(gDefLooksLike != kNoDef)
    RETURN(gDefLooksLike);
}

<ctxBlockCommentInsideMacroDefn>[^*\n]*"*"+"/" {
  ENDCONTEXT();
}

<ctxBlockCommentInsideMacroDefn>.*"*/"/{WS}*"\\"{WS}*{NL} {
  ENDCONTEXT();
}

<ctxBlockCommentInsideMacroDefn>.*"\\"{WS}*{NL} {
  ++gLineNo;
}

<ctxPreprocessor>undef/{WS} {
  set_token_and_yyposn();
  RETURN(tknUndef);
}

<ctxPreprocessor>include/{WS} {
  ENDCONTEXT();
  set_token_and_yyposn();
  BEGINCONTEXT(ctxInclude);
  RETURN(tknInclude);
}

<ctxPreprocessor>import/{WS} {
  ENDCONTEXT();
  set_token_and_yyposn();
  BEGINCONTEXT(ctxInclude);
  RETURN(tknImport);
}

<ctxInclude><.*> {
  set_token_and_yyposn();
  RETURN(tknStdHdrInclude);
}

<ctxInclude>{ID} {
  set_token_and_yyposn();
  RETURN(tknStdHdrInclude);
}

<ctxInclude>{NL} {
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  ++gLineNo;
}

<ctxPreprocessor>if/{WS} {
  set_token_and_yyposn();
  oyytext = yytext+yyleng;
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknIf);
}

<ctxPreprocessor>ifdef/{WS} {
  set_token_and_yyposn();
  RETURN(tknIfDef);
}

<ctxPreprocessor>ifndef/{WS} {
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  RETURN(tknIfNDef);
}

<ctxGeneral,ctxPreprocessor>else/{TS} {
  set_token_and_yyposn();
  RETURN(tknElse);
}

<ctxPreprocessor>elif/{WS} {
  set_token_and_yyposn();
  oyytext = yytext+yyleng;
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknElIf);
}

<ctxPreprocessor>endif/{TS} {
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  RETURN(tknEndIf);
}

<ctxPreprocessor>pragma/{WS} {
  set_token_and_yyposn();
  oyytext = yytext+yyleng;
  ENDCONTEXT();
  BEGINCONTEXT(ctxPreProBody);
  RETURN(tknPragma);
}

<ctxPreProBody>.*\\{WS}*{NL} {
  ++gLineNo;
}

<ctxPreProBody>.* {
}

<ctxPreProBody>{NL} {
  set_token_and_yyposn(oyytext, yytext-oyytext, TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  ++gLineNo;
  RETURN(tknPreProDef);
}

<ctxPreprocessor>{NL} {
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  ++gLineNo;
}

<ctxPreprocessor>error{WS}[^\n]*{NL} {
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  ENDCONTEXT();
  ++gLineNo;
  RETURN(tknHashError);
}

<ctxGeneral>"::" {
  set_token_and_yyposn();
  RETURN(tknScopeResOp);
}

<ctxGeneral>const/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknConst);
}

<ctxGeneral>constexpr/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknConstExpr);
}

<ctxGeneral>static/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknStatic);
}

<ctxGeneral>inline/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknInline);
}

<ctxGeneral>virtual/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknVirtual);
}

<ctxGeneral>override/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknOverride);
}

<ctxGeneral>final/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknFinal);
}

<ctxGeneral>noexcept/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknNoExcept);
}

<ctxGeneral>extern/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknExtern);
}

<ctxGeneral>explicit/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknExplicit);
}

<ctxGeneral>friend/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknFriend);
}

<ctxGeneral>"extern"{WS}+"\"C\"" {
  set_token_and_yyposn();
  RETURN(tknExternC);
}

<ctxGeneral>volatile/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknVolatile);
}

<ctxGeneral>new/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknNew);
}

<ctxGeneral>delete/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknDelete);
}

<ctxGeneral>default/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknDefault);
}

<ctxGeneral>return/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknReturn);
}

<ctxGeneral>if/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknIf);
}

<ctxGeneral>else/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknElse);
}

<ctxGeneral>for/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknFor);
}

<ctxGeneral>do/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknDo);
}

<ctxGeneral>while/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknWhile);
}

<ctxGeneral>switch/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknSwitch);
}

<ctxGeneral>case/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknCase);
}

<ctxGeneral>const_cast/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknConstCast);
}

<ctxGeneral>static_cast/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknStaticCast);
}

<ctxGeneral>dynamic_cast/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknDynamicCast);
}

<ctxGeneral>reinterpret_cast/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknReinterpretCast);
}

<ctxGeneral>try/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknTry);
}

<ctxGeneral>catch/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknCatch);
}

<ctxGeneral>throw/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknThrow);
}

<ctxGeneral>sizeof/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknSizeOf);
}

<ctxGeneral>operator/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknOperator);
}

<ctxGeneral>void/{TS}+ {
  set_token_and_yyposn();
  RETURN(tknVoid);
}

<ctxGeneral>"+=" {
  set_token_and_yyposn();
  RETURN(tknPlusEq);
}

<ctxGeneral>"-=" {
  set_token_and_yyposn();
  RETURN(tknMinusEq);
}

<ctxGeneral>"*=" {
  set_token_and_yyposn();
  RETURN(tknMulEq);
}

<ctxGeneral>"*=" {
  set_token_and_yyposn();
  RETURN(tknMulEq);
}

<ctxGeneral>"/=" {
  set_token_and_yyposn();
  RETURN(tknDivEq);
}

<ctxGeneral>"%=" {
  set_token_and_yyposn();
  RETURN(tknPerEq);
}

<ctxGeneral>"^=" {
  set_token_and_yyposn();
  RETURN(tknXorEq);
}

<ctxGeneral>"&=" {
  set_token_and_yyposn();
  RETURN(tknAndEq);
}

<ctxGeneral>"|=" {
  set_token_and_yyposn();
  RETURN(tknOrEq);
}

<ctxGeneral>"<<" {
  set_token_and_yyposn();
  RETURN(tknLShift);
}

<ctxGeneral>"<<=" {
  set_token_and_yyposn();
  RETURN(tknLShiftEq);
}

<ctxGeneral>">>=" {
  set_token_and_yyposn();
  RETURN(tknRShiftEq);
}

<ctxGeneral>"==" {
  set_token_and_yyposn();
  RETURN(tknCmpEq);
}

<ctxGeneral>"!=" {
  set_token_and_yyposn();
  RETURN(tknNotEq);
}

<ctxGeneral>"<=" {
  set_token_and_yyposn();
  RETURN(tknLessEq);
}

<ctxGeneral>">=" {
  set_token_and_yyposn();
  RETURN(tknGreaterEq);
}

<ctxGeneral>"<=>" {
  set_token_and_yyposn();
  RETURN(tkn3WayCmp);
}

<ctxGeneral>"&&" {
  set_token_and_yyposn();
  RETURN(tknAnd);
}

<ctxGeneral>"||" {
  set_token_and_yyposn();
  RETURN(tknOr);
}

<ctxGeneral>"++" {
  set_token_and_yyposn();
  RETURN(tknInc);
}

<ctxGeneral>"--" {
  set_token_and_yyposn();
  RETURN(tknDec);
}

<ctxGeneral>"->" {
  set_token_and_yyposn();
  RETURN(tknArrow);
}

<ctxGeneral>"->*" {
  set_token_and_yyposn();
  RETURN(tknArrowStar);
}

<ctxGeneral,ctxDefine>{NUM} {
  set_token_and_yyposn();
  RETURN(tknNumber);
}

<ctxGeneral>{DECNUMLIT}((e|E)[+-]?{DECNUMLIT})? {
  set_token_and_yyposn();
  RETURN(tknNumber);
}

<ctxGeneral,ctxInclude>{SL} {
  set_token_and_yyposn();
  RETURN(tknStrLit);
}

<ctxGeneral>(L)?{SL} {
  set_token_and_yyposn();
  RETURN(tknStrLit);
}

<ctxGeneral>(L)?{CL} {
  set_token_and_yyposn();
  RETURN(tknCharLit);
}

<ctxGeneral>\(|\[ {
  set_token_and_yyposn(TokenSetupFlag::DisableCommentTokenization);
  gBracketDepthStack.back() = gBracketDepthStack.back() + 1;
  RETURN(yytext[0]);
}

<ctxGeneral>")"|"]" {
  set_token_and_yyposn(TokenSetupFlag::None);
  gBracketDepthStack.back() = gBracketDepthStack.back() - 1;
  RETURN(yytext[0]);
}

<ctxGeneral>"{" {
  if (gEnumBodyWillBeEncountered)
  {
    gEnumBodyWillBeEncountered = false;
    BEGINCONTEXT(ctxEnumBody);
    set_token_and_yyposn(TokenSetupFlag::None);
    oyytext = yytext+1;
  }
  else
  {
    gBracketDepthStack.push_back(0);
    set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  }
  RETURN(yytext[0]);
}

<ctxEnumBody>"}" {
  set_token_and_yyposn(TokenSetupFlag::None);
  ENDCONTEXT();
  RETURN(yytext[0]);
}

<ctxEnumBody>[^\}\n]* {
  // printf("%s", yytext);
}

<ctxEnumBody>{NL} {
  ++gLineNo;
}

<ctxEnumBody>{NL}/"}" {
  ++gLineNo;
  set_token_and_yyposn(oyytext, yytext+yyleng-oyytext, TokenSetupFlag::None);
  RETURN(tknBlob);
}

<ctxEnumBody>([^\}\n]*|^{WS}*)/"}" {
  set_token_and_yyposn(oyytext, yytext+yyleng-oyytext, TokenSetupFlag::None);
  RETURN(tknBlob);
}

<ctxGeneral>\} {
  gBracketDepthStack.resize(gBracketDepthStack.size() - 1);
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  RETURN(yytext[0]);
}

<ctxGeneral>; {
  set_token_and_yyposn();
  gTokenizeComment = true;
  RETURN(yytext[0]);
}

<ctxGeneral>: {
  set_token_and_yyposn(TokenSetupFlag::None);
  RETURN(yytext[0]);
}

<ctxGeneral>, {
  set_token_and_yyposn(TokenSetupFlag::ResetCommentTokenization);
  RETURN(yytext[0]);
}

<ctxGeneral>\)|\]|#|=|\*|\+|-|\.|\/|\~|%|\^|&|\||\?|\! {
  set_token_and_yyposn();
  RETURN(yytext[0]);
}

<ctxGeneral>">" {
  set_token_and_yyposn();
  RETURN(tknGT);
}

<ctxGeneral>"<" {
  set_token_and_yyposn();
  RETURN(tknLT);
}

<ctxGeneral>\.\.\. {
  set_token_and_yyposn();
  RETURN(tknEllipsis);
}

<*>{WS}+ {
  /* Ignore white spaces */
}

<*>\\{WS}*{NL} {
  // We will always ignore line continuation character
  ++gLineNo;
}

<*>__attribute__{WS}*\(\(.*\)\) {
  /* Ignore as of now */
}

%%

static YY_BUFFER_STATE gParseBuffer = nullptr;
void setupScanBuffer(char* buf, size_t bufsize)
{
  gParseBuffer = yy_scan_buffer(buf, bufsize);
  gLineNo = 0;
  oyytext = buf;
  gTokenizeComment = true;
  gEnumBodyWillBeEncountered = false;
  BEGINCONTEXT(ctxGeneral);
}

void cleanupScanBuffer()
{
  yy_delete_buffer(gParseBuffer);
  gParseBuffer = nullptr;
  gTokenizeComment = true;
}
