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

MacroDefineInfo GetMacroDefineInfo(const std::string& id)
{
  if (gUndefinedNames.count(id))
    return MacroDefineInfo::kUndefined;

  if (gDefinedNames.count(id))
    return MacroDefineInfo::kDefined;

  return MacroDefineInfo::kNoInfo;
}

std::optional<int> GetIdValue(const std::string& id)
{
  if (gUndefinedNames.count(id))
    return std::nullopt;

  const auto itr = gDefinedNames.find(id);
  if (itr == gDefinedNames.end())
    return std::nullopt;

  return itr->second;
}
