// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C4E2066E_031F_423A_A520_CF9D288E957D
#define C4E2066E_031F_423A_A520_CF9D288E957D

#include "defs.h"

// TODO: Put this file somewhere else, if at all it is needed in CppParser project.

namespace CppAst {

class CppHeaderFile;

/**
 * A C++ program is identified by a set of header and source files.
 */
class CppProgram
{
public:
  std::vector<const CppHeaderFile*> GetAllHeaderFiles() const;
};

} // namespace CppAst

#endif /* C4E2066E_031F_423A_A520_CF9D288E957D */
