// SPDX-License-Identifier: MIT

#ifndef D17C0DD7_F5C5_49E7_A73F_70FF5F368E70
#define D17C0DD7_F5C5_49E7_A73F_70FF5F368E70

#include "cppast/cpp_entity.h"
#include "cppast/cpp_type_modifier.h"

namespace cppast {

class CppStructuredBindingVarsDecl : public CppEntity
{
public:
  static constexpr auto EntityType()
  {
    return CppEntityType::STRUCTURED_BINDING_VARS_DECL;
  }

public:
  CppStructuredBindingVarsDecl(CppTypeModifier typeModifier, std::vector<std::string> names, std::unique_ptr<const CppExpression> initializer)
    : CppEntity(EntityType())
    , names_(std::move(names))
  {
  }

private:
    std::vector<std::string> names_;
    std::unique_ptr<const CppExpression> initializer_;
    
};

} // namespace cppast


#endif /* D17C0DD7_F5C5_49E7_A73F_70FF5F368E70 */
