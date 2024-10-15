// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

/**
 * @file Internal interface for lexer and parser APIs.
 */

#ifndef BD166B6E_821D_49A3_9593_70C58C59558D
#define BD166B6E_821D_49A3_9593_70C58C59558D

#include <functional>

#include "cppast/cppast.h"

using ErrorHandler =
  std::function<void(const char* errLineText, size_t lineNum, size_t errorStartPos, int lexerContext)>;

void setErrorHandler(ErrorHandler errorHandler);
void resetErrorHandler();

std::unique_ptr<cppast::CppCompound> parseStream(char* stm, size_t stmSize);

#endif /* BD166B6E_821D_49A3_9593_70C58C59558D */
