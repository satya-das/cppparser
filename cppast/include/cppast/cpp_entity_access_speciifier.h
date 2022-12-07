// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef CE14BD07_311B_4042_8FEF_69F7E3AEE702
#define CE14BD07_311B_4042_8FEF_69F7E3AEE702

#include "cppast/cpp_access_type.h"
#include "cppast/cpp_entity.h"

namespace cppast {

class CppEntityAccessSpecifier : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::ENTITY_ACCESS_SPECIFIER;
  }

public:
  CppEntityAccessSpecifier(CppAccessType accessType)
    : CppEntity(EntityType())
    , accessType_(accessType)
  {
  }

public:
  CppAccessType type() const
  {
    return accessType_;
  }

private:
  CppAccessType accessType_;
};

} // namespace cppast

#endif /* CE14BD07_311B_4042_8FEF_69F7E3AEE702 */
