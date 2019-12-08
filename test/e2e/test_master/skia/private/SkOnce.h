/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkOnce_DEFINED
#  define SkOnce_DEFINED
#  include <atomic>
#  include <utility>
class SkOnce
{
public:
  SkOnce();
  template <typename Fn, typename... Args>
  void operator()(Fn&& fn, Args&& args)
  {
    auto state = fState.load(std::memory_order_acquire);
    if (state == Done)
    {
      return ;
    }
    if (state == NotStarted && fState.compare_exchange_strong(state, Claimed, std::memory_order_relaxed, std::memory_order_relaxed))
    {
      fn(std::forward<Args>(args));
      return fState.store(Done, std::memory_order_release);
    }
    while (fState.load(std::memory_order_acquire) != Done)
    {
    }
  }
private:
  enum State : uint8_t
  {
    NotStarted,
    Claimed,
    Done
  };
  std::atomic<uint8_t> fState{NotStarted};
};
#endif
