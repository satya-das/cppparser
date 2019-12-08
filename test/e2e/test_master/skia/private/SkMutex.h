/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkMutex_DEFINED
#  define SkMutex_DEFINED
#  include "include/core/SkTypes.h"
#  include "include/private/SkMacros.h"
#  include "include/private/SkSemaphore.h"
#  include "include/private/SkThreadAnnotations.h"
#  include "include/private/SkThreadID.h"
class SK_CAPABILITY("mutex") SkMutex
{
public:
  SkMutex();
  void acquire()
  {
    fSemaphore.wait();
    SkDEBUGCODE(fOwner = SkGetThreadID();)
  }
  void release()
  {
    this->assertHeld();
    SkDEBUGCODE(fOwner = kIllegalThreadID;)
    fSemaphore.signal();
  }
  void assertHeld()
  {
    SkASSERT(fOwner == SkGetThreadID());
  }
private:
  SkSemaphore fSemaphore{1};
  SkDEBUGCODE(SkThreadID fOwner{kIllegalThreadID};)
};
class SK_SCOPED_CAPABILITY SkAutoMutexExclusive
{
public:
  SkAutoMutexExclusive(SkMutex& mutex)
    : fMutex(mutex)
  {
    fMutex.acquire();
  }
  ~SkAutoMutexExclusive()
  {
    fMutex.release();
  }
private:
  SkMutex& fMutex;
};
#  define SkAutoMutexExclusive	(...) SK_REQUIRE_LOCAL_VAR(SkAutoMutexExclusive)
#endif
