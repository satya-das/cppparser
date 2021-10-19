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

EnabledCodeDecision getCodeEnableInfo(const std::string& id)
{
  if (gUndefinedNames.count(id))
    return EnabledCodeDecision::kDisabled;

  const auto itr = gDefinedNames.find(id);
  if (itr != gDefinedNames.end())
  {
    if (itr->second)
      return EnabledCodeDecision::kEnabled;
    else
      return EnabledCodeDecision::kDisabled;
  }

  return EnabledCodeDecision::kNoInfo;
}
