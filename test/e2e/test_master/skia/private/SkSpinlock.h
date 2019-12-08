/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkSpinlock_DEFINED
#  define SkSpinlock_DEFINED
#  include "include/core/SkTypes.h"
#  include "include/private/SkThreadAnnotations.h"
#  include <atomic>
class SkSpinlock
{
public:
  SkSpinlock();
  void acquire()
  {
    if (fLocked.exchange(true, std::memory_order_acquire))
    {
      this->contendedAcquire();
    }
  }
  bool tryAcquire()
  {
    if (fLocked.exchange(true, std::memory_order_acquire))
    {
      return false;
    }
    return true;
  }
  void release()
  {
    fLocked.store(false, std::memory_order_release);
  }
private:
  SK_API void contendedAcquire();
  std::atomic<bool> fLocked{false};
};
class SK_SCOPED_CAPABILITY SkAutoSpinlock
{
public:
  SkAutoSpinlock(SkSpinlock& mutex)
    : fSpinlock(mutex)
  {
    fSpinlock.acquire();
  }
  ~SkAutoSpinlock()
  {
    fSpinlock.release();
  }
private:
  SkSpinlock& fSpinlock;
};
#endif
