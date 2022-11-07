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
  class UserData
  {
  public:
    virtual ~UserData() = default;
  };

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

  void userData(std::unique_ptr<UserData> data)
  {
    userData_ = std::move(data);
  }

  UserData* userData()
  {
    return userData_.get();
  }

  const UserData* userData() const
  {
    return userData_.get();
  }

protected:
  CppEntity(CppEntityType type)
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
  const CppEntityType       entityType_;
  const CppCompound*        owner_ {nullptr};
  std::unique_ptr<UserData> userData_;
};

} // namespace cppast

#endif /* D9FB86B4_AD61_4312_A3C5_A8286A3480F0 */
