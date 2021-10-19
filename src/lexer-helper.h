#pragma once

#include <string>

enum class EnabledCodeDecision
{
  kNoInfo,
  kDisabled,
  kEnabled
};

EnabledCodeDecision getCodeEnableInfo(const std::string& id);
