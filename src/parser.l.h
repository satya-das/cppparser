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

#pragma once

#include "cpptoken.h"
#include "cppvarinit.h"
#include "parser.tab.h"

#include <functional>
#include <map>
#include <set>
#include <vector>

/*
Parsing of #define is complex. So we will try to parse simple #defines to know what it trys to define.
For any thing complex we will treat the entire definition as one BLOB.
*/
enum DefineLooksLike
{
  kNoDef      = 0,
  kNumDef     = tknNumber,    // #define is used to define a numeric constant.
  kStrLitDef  = tknStrLit,    // #define is used to define a string literal.
  kCharLitDef = tknCharLit,   // #define is used to define a character literal.
  kReDef      = tknName,      // #define is used to rename something, e.g. #define CALLTYPE __stdcall
  kComplexDef = tknPreProDef, // It is something beyond our parser can comprehand.
};

enum class TokenSetupFlag
{
  None,
  DisableCommentTokenization,
  EnableCommentTokenization,
  ResetCommentTokenization
};

enum class MacroDefineInfo
{
  kNoInfo,
  kDefined,
  kUndefined
};

enum class MacroDependentCodeEnablement
{
  kNoInfo,
  kDisabled,
  kEnabled
};

struct CodeEnablementInfo
{
  MacroDependentCodeEnablement macroDependentCodeEnablement = MacroDependentCodeEnablement::kNoInfo;
  /**
   * Counting of # to keep track of when we need to consider the code outside of disabled segment.
   * For example, when the parsing is outside of "#if 0 ... #endif" segment.
   */
  int numHashIfInMacroDependentCode = 0;
};

using CodeEnablementInfoStack = std::vector<CodeEnablementInfo>;
using BracketDepthStack       = std::vector<int>;

struct LexerData
{
  int mLexLog = 0;
  int mLineNo = 1;

  const char* mInputBuffer     = nullptr;
  size_t      mInputBufferSize = 0;

  const char* mOldYytext = nullptr;

  //@{ Flags to parse enum body as a blob
  bool mEnumBodyWillBeEncountered = false;
  //@}

  //@{ Flags to parse function body as a blob
  const char* mNotAMemInitColon                   = nullptr;
  bool        mFunctionBodyWillBeEncountered      = false;
  bool        mMemInitListWillBeEncountered       = false;
  const char* mExpectedBracePosition              = nullptr;
  const char* mExpectedColonPosition              = nullptr;
  const char* mPossibleFuncImplStartBracePosition = nullptr;
  //@}

  /**
   * Comments can appear anywhere in a C/C++ program and unfortunately not all coments can be preserved.
   *
   * mTokenizeComment is a flag used to decide if we can tokenize comments.

   * For details of what kind of comments are preserved and what kind are lost, see file
   test/e2e/test_input/comment_test.h
   */
  bool mTokenizeComment = true;

  /**
   * We need to keep track of where we are inside the nest of brackets for knowing when we can tokenize comments.
   * Since we only want to preserve free standing comments and some side comments (in future improvements)
   * we need to always ignore comments that are inside square brackets, i.e. [].
   * We also need to ignore comments that are inside round brackets, i.e. (),
   * except when we are inside lambda which is being passed to a function as parameter:
   *    func([]() {
          // This comment should be preserved even when we are eventually inside a round bracket
          } // And this comment should be ignored
        ); // This one too
   */
  BracketDepthStack mBracketDepthStack = {0};

  /**
   * It is currently used for parsing function body as a blob.
   */
  int mNestedCurlyBracketDepth = 0;

  DefineLooksLike mDefLooksLike = DefineLooksLike::kNoDef;

  CodeEnablementInfoStack codeEnablementInfoStack;
  CodeEnablementInfo      currentCodeEnablementInfo;

  bool parseDisabledCodeAsBlob             = false;
  bool codeSegmentDependsOnMacroDefinition = false;
};
