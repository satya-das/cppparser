// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef C9EFCA65_C9EF_406A_8025_AFF92923890D
#define C9EFCA65_C9EF_406A_8025_AFF92923890D

namespace cppast {

enum class CppEntityType
{
  DOCUMENTATION_COMMENT,

  PREPROCESSOR,
  ENTITY_ACCESS_SPECIFIER,
  COMPOUND,
  VAR_TYPE,
  VAR,
  VAR_LIST,
  TYPEDEF_DECL,
  TYPEDEF_DECL_LIST,
  NAMESPACE_ALIAS,
  USING_NAMESPACE,
  USING_DECL,
  ENUM,
  FORWARD_CLASS_DECL,
  FUNCTION,
  LAMBDA,
  CONSTRUCTOR,
  DESTRUCTOR,
  TYPE_CONVERTER,
  FUNCTION_PTR,
  EXPRESSION,
  GOTO_STATEMENT,
  RETURN_STATEMENT,
  THROW_STATEMENT,
  MACRO_CALL,
  ASM_BLOCK,
  LABEL,

  IF_BLOCK,
  FOR_BLOCK,
  RANGE_FOR_BLOCK,
  WHILE_BLOCK,
  DO_WHILE_BLOCK,
  SWITCH_BLOCK,
  TRY_BLOCK,

  BLOB,
};

}

#endif /* C9EFCA65_C9EF_406A_8025_AFF92923890D */
