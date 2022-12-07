// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BF43A660_E296_44E6_A59A_E7B777F92EEE
#define BF43A660_E296_44E6_A59A_E7B777F92EEE

#include <cstdint>

namespace cppast {

/**
 * @brief Member and inheritance access types.
 */
enum class CppAccessType : std::uint8_t
{
  PUBLIC,
  PRIVATE,
  PROTECTED
};

} // namespace cppast

#endif /* BF43A660_E296_44E6_A59A_E7B777F92EEE */
