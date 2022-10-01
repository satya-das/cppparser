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

/**
 * @file Finds matching closed angle bracket.
 *
 * It is helpful in tockenizing '<' and '>' used in template definition and usage.
 */

/* clang-format off */

%{
// C++17 causes problem when register is used and flex uses register in generated code
#define register


  // Easy MACRO to quickly push current context and switch to another one.
#define BEGINCONTEXT(ctx) { \
  yy_push_state(ctx);       \
}

#define ENDCONTEXT() {      \
  yy_pop_state();           \
}

//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
#  define fileno _fileno /* Avoid compiler warning for VS. */
#endif //#ifdef WIN32

namespace {

struct {
  int nestedRoundBracket = 0;
  int nestedAngleBracket = 0;
  int nestedCurlyBracket = 0;
} g;

const char* gStartBuffer = nullptr;

using YYSTYPE = const char*;

}

%}

%option never-interactive
%option stack
%option noyy_top_state
%option noyywrap
%option prefix="yy2"
%option bison-bridge

/************************************************************************/

/*@ { Comonly used regular expressions. */

/* New line */
NL	 (\r\n|\r|\n)

/*@}*/

%x ctxGeneral
%x ctxCStyleComment

%%

<*>"/*" {
  /*
  Ignore side comments for time being
  setOldYytext(yytext);
  */
  BEGINCONTEXT(ctxCStyleComment);
}

<ctxCStyleComment>.|{NL} {
}

<ctxCStyleComment>[^*\n]*"*"+"/" {
  ENDCONTEXT();
}

<ctxGeneral>"//".*{NL} {
}

<ctxGeneral>">" {
  if ((g.nestedRoundBracket == 0) &&
      (g.nestedCurlyBracket == 0)) {
    *yylval = yytext;
    if (g.nestedAngleBracket == 0) {
      return 1;
    } else {
      g.nestedAngleBracket--;
    }
  }
}

<ctxGeneral>";" {
  if ((g.nestedRoundBracket == 0) &&
      (g.nestedCurlyBracket == 0)) {
    return 1;
  }
}

<ctxGeneral>"<" {
  g.nestedAngleBracket++;
}

<ctxGeneral>"(" {
  g.nestedRoundBracket++;
}

<ctxGeneral>"{" {
  g.nestedCurlyBracket++;
}

<ctxGeneral>")" {
  g.nestedRoundBracket--;
  if (g.nestedRoundBracket < 0) {
    return 1;
  }
}

<ctxGeneral>"}" {
  g.nestedCurlyBracket--;
  if (g.nestedCurlyBracket < 0) {
    return 1;
  }
}

<ctxGeneral>. {
}

%%

#include <cassert>

const char* findMatchedClosingAngleBracket(char* s, const char* end)
{
  gStartBuffer = s;
  assert((s[0] == '<') || (s[0] == '\0'));
  const auto scanBuffer = yy_scan_buffer(s+1, end - s-1);
  const char* result = nullptr;
  BEGIN(ctxGeneral);
  yylex(&result);

  // HACKish code starts
  char emptyBuf[] = {'\0', '\0'};
  // yy_scan_buffer ensures that the previous buffer is restored to its original state
  const auto emptyScanBuffer = yy_scan_buffer(emptyBuf, sizeof(emptyBuf));
  yy_delete_buffer(scanBuffer);
  yy_delete_buffer(emptyScanBuffer);
  // HACKish code ends

  return result;
}
