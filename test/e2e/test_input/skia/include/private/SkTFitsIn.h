template <typename D, typename S>
typename std::enable_if<(std::is_integral<S>::value || std::is_enum<S>::value) &&
                        (std::is_integral<D>::value || std::is_enum<D>::value), bool>::type
f(S src) {}
