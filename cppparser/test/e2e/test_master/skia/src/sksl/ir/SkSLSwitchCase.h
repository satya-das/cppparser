/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SKSL_SWITCHCASE
#  define SKSL_SWITCHCASE
#  include "src/sksl/ir/SkSLExpression.h"
#  include "src/sksl/ir/SkSLStatement.h"
namespace SkSL
{
/**
 * A single case of a 'switch' statement.
 */
  struct SwitchCase : public Statement
  {
    SwitchCase(int offset, std::unique_ptr<Expression> value, std::vector<std::unique_ptr<Statement>> statements)
      : INHERITED(offset, kSwitch_Kind)
      , fValue(std::move(value))
      , fStatements(std::move(statements))
    {
    }
    std::unique_ptr<Statement> clone() const override
    {
      std::vector<std::unique_ptr<Statement>> cloned;
      return std::unique_ptr<Statement>(new SwitchCase(fOffset, fValue ? fValue->clone() : nullptr, std::move(cloned)));
    }
    String description() const override
    {
      String result;
      if (fValue)
      {
        result.appendf("case %s:\n", fValue->description().c_str());
      }
      else 
      {
        result += "default:\n";
      }
      return result;
    }
    // null value implies "default" case
    std::unique_ptr<Expression> fValue;
    std::vector<std::unique_ptr<Statement>> fStatements;
    typedef Statement INHERITED;
  };
}
#endif
