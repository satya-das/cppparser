#include "lexer-helper.h"

#include <map>
#include <set>
#include <string>

extern std::set<std::string>      gMacroNames;
extern std::set<std::string>      gKnownApiDecorNames;
extern std::map<std::string, int> gDefinedNames;
extern std::set<std::string>      gUndefinedNames;
extern std::set<std::string>      gIgnorableMacroNames;
extern std::map<std::string, int> gRenamedKeywords;

MacroDependentCodeEnablement getCodeEnableInfo(const std::string& id, bool negate)
{
  if (gUndefinedNames.count(id))
    return negate ? MacroDependentCodeEnablement::kEnabled : MacroDependentCodeEnablement::kDisabled;

  const auto itr = gDefinedNames.find(id);
  if (itr != gDefinedNames.end())
  {
    if (itr->second)
      return negate ? MacroDependentCodeEnablement::kDisabled : MacroDependentCodeEnablement::kEnabled;
    else
      return negate ? MacroDependentCodeEnablement::kEnabled : MacroDependentCodeEnablement::kDisabled;
  }

  return MacroDependentCodeEnablement::kNoInfo;
}

std::optional<int> getIdValue(const std::string& id)
{
  if (gUndefinedNames.count(id))
    return std::nullopt;

  const auto itr = gDefinedNames.find(id);
  if (itr == gDefinedNames.end())
    return std::nullopt;

  return itr->second;
}
