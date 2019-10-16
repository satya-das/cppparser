/*
 * Copyright (C) 2014 Google Inc. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkEventTracer_DEFINED
#  define SkEventTracer_DEFINED
#  include "include/core/SkTypes.h"
class SK_API SkEventTracer
{
public:
  typedef uint64_t Handle;
    /**
     * If this is the first call to SetInstance or GetInstance then the passed instance is
     * installed and true is returned. Otherwise, false is returned. In either case ownership of the
     * tracer is transferred and it will be deleted when no longer needed.
     */
  static bool SetInstance(SkEventTracer*);
    /**
     * Gets the event tracer. If this is the first call to SetInstance or GetIntance then a default
     * event tracer is installed and returned.
     */
  static SkEventTracer* GetInstance();
  virtual ~SkEventTracer()
  {
  }
  enum CategoryGroupEnabledFlags
  {
    kEnabledForRecording_CategoryGroupEnabledFlags = 1 << 0,
    kEnabledForMonitoring_CategoryGroupEnabledFlags = 1 << 1,
    kEnabledForEventCallback_CategoryGroupEnabledFlags = 1 << 2
  };
  virtual const uint8_t* getCategoryGroupEnabled(const char* name) = 0;
  virtual const char* getCategoryGroupName(const uint8_t* categoryEnabledFlag) = 0;
  virtual SkEventTracer::Handle addTraceEvent(char phase, const uint8_t* categoryEnabledFlag, const char* name, uint64_t id, int32_t numArgs, const char** argNames, const uint8_t* argTypes, const uint64_t* argValues, uint8_t flags) = 0;
  virtual void updateTraceEventDuration(const uint8_t* categoryEnabledFlag, const char* name, SkEventTracer::Handle handle) = 0;
};
#endif
