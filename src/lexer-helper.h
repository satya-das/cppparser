#pragma once

#include <cassert>
#include <optional>
#include <string>

#include "parser.l.h"

inline MacroDependentCodeEnablement invert(MacroDependentCodeEnablement enabledCodeDecision)
{
  switch (enabledCodeDecision)
  {
    case MacroDependentCodeEnablement::kNoInfo:
      return MacroDependentCodeEnablement::kNoInfo;
    case MacroDependentCodeEnablement::kDisabled:
      return MacroDependentCodeEnablement::kEnabled;
    case MacroDependentCodeEnablement::kEnabled:
      return MacroDependentCodeEnablement::kDisabled;
  }

  assert(false && "We should never be here.");
  return MacroDependentCodeEnablement::kNoInfo;
}

MacroDependentCodeEnablement getCodeEnableInfo(const std::string& id, bool negate);

std::optional<int> getIdValue(const std::string& id);