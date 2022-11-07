#ifndef B1A7BAF0_1D5C_4F41_9DF8_07895208C0BC
#define B1A7BAF0_1D5C_4F41_9DF8_07895208C0BC

#include <memory>

// TODO: run valgrind to check memory leaks

template <typename T>
std::unique_ptr<T> Ptr(T* p)
{
  return std::unique_ptr<T>(p);
}

template <typename T>
auto Obj(T* p)
{
  return std::move(*std::unique_ptr<T>(p));
}

#endif /* B1A7BAF0_1D5C_4F41_9DF8_07895208C0BC */
