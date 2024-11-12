// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef D9FB86B4_AD61_4312_A3C5_A8286A3480F0
#define D9FB86B4_AD61_4312_A3C5_A8286A3480F0

#include "cppast/cpp_attribute_specifier_sequence_container.h"
#include "cppast/cpp_entity_type.h"
#include "cppast/defs.h"

#include <functional>
#include <memory>

namespace cppast {

class CppCompound;

/**
 * Base class of all C++ entities.
 */
class CppEntity : public CppAttributeSpecifierSequenceContainer
{
public:
public:
  virtual ~CppEntity() = default;

public:
  CppEntityType entityType() const
  {
    return entityType_;
  }

  const CppCompound* owner() const
  {
    return owner_;
  }

protected:
  explicit CppEntity(CppEntityType type)
    : entityType_(type)
  {
  }

private:
  void owner(const CppCompound& ownerEntity)
  {
    owner_ = &ownerEntity;
  }

  friend class CppCompound;

private:
  const CppEntityType entityType_;
  const CppCompound*  owner_ {nullptr};
};

} // namespace cppast

#endif /* D9FB86B4_AD61_4312_A3C5_A8286A3480F0 */
