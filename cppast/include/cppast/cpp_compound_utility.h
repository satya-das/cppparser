// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A00E589B_6B8A_49DC_8718_C511FCDE46CB
#define A00E589B_6B8A_49DC_8718_C511FCDE46CB

#include "cppast/cpp_compound.h"
#include "defs.h"

namespace cppast {

/**
 * @brief Get the vector of specific type of owned entities.
 *
 * @tparam _EntityClass Class type of owned entities.
 * @return std::vector of owned entities.
 */
template <typename _EntityClass>
inline std::vector<const _EntityClass*> GetOwnedEntities(const CppCompound& owner)
{
  std::vector<const _EntityClass*> result;
  owner.visit([&result](const _EntityClass& entity) {
    result.push_back(&entity);
    return true;
  });

  return result;
}

/**
 * @brief Get all the owned entities.
 *
 * @return std::vector of owned entities.
 */
inline std::vector<const CppEntity*> GetAllOwnedEntities(const CppCompound& owner)
{
  std::vector<const CppEntity*> result;
  owner.visitAll([&result](const CppEntity& entity) {
    result.push_back(&entity);
    return true;
  });

  return result;
}

} // namespace cppast

#endif /* A00E589B_6B8A_49DC_8718_C511FCDE46CB */
