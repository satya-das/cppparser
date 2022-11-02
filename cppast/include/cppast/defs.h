// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef ABC094B8_2D63_40B9_B3E3_42CB0A7E71E0
#define ABC094B8_2D63_40B9_B3E3_42CB0A7E71E0

#include <functional>

namespace CppAst {

/**
 * @brief A callable object that is called with visited object as parameter.
 *
 * @tparam T Type of object being visited.
 *
 * @note The callable should return true unless no more visit is needed.
 */
template <typename T>
using Visitor = std::function<bool(T)>;

} // namespace CppAst

#endif /* ABC094B8_2D63_40B9_B3E3_42CB0A7E71E0 */
