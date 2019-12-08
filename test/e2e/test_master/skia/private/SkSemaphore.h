/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkSemaphore_DEFINED
#  define SkSemaphore_DEFINED
#  include "include/core/SkTypes.h"
#  include "include/private/SkOnce.h"
#  include <atomic>
class SkSemaphore
{
public:
  SkSemaphore(int count = 0)
    : fCount(count)
    , fOSSemaphore(nullptr)
  {
  }
  ~SkSemaphore();
  void signal(int n = 1);
  void wait();
  bool try_wait();
private:
  struct OSSemaphore;
  void osSignal(int n);
  void osWait();
  std::atomic<int> fCount;
  SkOnce fOSSemaphoreOnce;
  OSSemaphore* fOSSemaphore;
};
inline void SkSemaphore::signal(int n)
{
  int prev = fCount.fetch_add(n, std::memory_order_release);
  int toSignal = SkTMin(-prev, n);
  if (toSignal > 0)
  {
    this->osSignal(toSignal);
  }
}
inline void SkSemaphore::wait()
{
  if (fCount.fetch_sub(1, std::memory_order_acquire) <= 0)
  {
    this->osWait();
  }
}
#endif
