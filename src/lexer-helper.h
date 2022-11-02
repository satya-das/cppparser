#ifndef EF4ACF9B_9D2E_4947_A8CD_17D2F1A6B363
#define EF4ACF9B_9D2E_4947_A8CD_17D2F1A6B363

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

MacroDefineInfo getMacroDefineInfo(const std::string& id);

std::optional<int> getIdValue(const std::string& id);

#endif /* EF4ACF9B_9D2E_4947_A8CD_17D2F1A6B363 */
