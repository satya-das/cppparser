/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkExecutor_DEFINED
#  define SkExecutor_DEFINED
#  include <functional>
#  include <memory>
#  include "include/core/SkTypes.h"
class SK_API SkExecutor
{
public:
  virtual ~SkExecutor();
  static std::unique_ptr<SkExecutor> MakeFIFOThreadPool(int threads = 0);
  static std::unique_ptr<SkExecutor> MakeLIFOThreadPool(int threads = 0);
  static SkExecutor& GetDefault();
  static void SetDefault(SkExecutor*);
  virtual void add(std::function<void(void)>) = 0;
  virtual void borrow()
  {
  }
};
#endif
