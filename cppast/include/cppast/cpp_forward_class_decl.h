// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef A69CD04B_3287_4606_9871_35F46730C08F
#define A69CD04B_3287_4606_9871_35F46730C08F

#include "cppast/cpp_compound.h"
#include "cppast/cpp_entity.h"
#include "cppast/cpp_templatable_entity.h"

namespace cppast {

class CppForwardClassDecl : public CppEntity, public CppTemplatableEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::FORWARD_CLASS_DECL;
  }

public:
  CppForwardClassDecl(std::string name, std::string apidecor, CppCompoundType cmpType = CppCompoundType::UNKNOWN)
    : CppEntity(EntityType())
    , compoundType_(cmpType)
    , name_(std::move(name))
    , apidecor_(std::move(apidecor))
    , attr_(0)
  {
  }

  CppForwardClassDecl(std::string name, CppCompoundType cmpType = CppCompoundType::UNKNOWN)
    : CppForwardClassDecl(name, std::string(), cmpType)
  {
  }

public:
  CppCompoundType compoundType() const
  {
    return compoundType_;
  }

  const std::string& name() const
  {
    return name_;
  }

  const std::string& apidecor() const
  {
    return apidecor_;
  }

  std::uint32_t attr() const
  {
    return attr_;
  }
  void addAttr(std::uint32_t attr)
  {
    attr_ |= attr;
  }

private:
  const CppCompoundType compoundType_;
  const std::string     name_;
  const std::string     apidecor_;
  std::uint32_t         attr_ {0};
};

} // namespace cppast

#endif /* A69CD04B_3287_4606_9871_35F46730C08F */
