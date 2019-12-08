/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkDeferredDisplayList_DEFINED
#  define SkDeferredDisplayList_DEFINED
#  include "include/core/SkRefCnt.h"
#  include "include/core/SkSurfaceCharacterization.h"
#  include "include/core/SkTypes.h"
class SkDeferredDisplayListPriv;
#  if  SK_SUPPORT_GPU
#    include "include/private/SkTArray.h"
#    include <map>
class GrRenderTask;
class GrRenderTargetProxy;
struct GrCCPerOpsTaskPaths;
#  endif
/*
 * This class contains pre-processed gpu operations that can be replayed into
 * an SkSurface via draw(SkDeferredDisplayList*).
 *
 * TODO: we probably need to expose this class so users can query it for memory usage.
 */
class SkDeferredDisplayList
{
#  if  SK_SUPPORT_GPU
public:
  class SK_API LazyProxyData : public SkRefCnt
  {
  public:
    GrRenderTargetProxy* fReplayDest = nullptr;
  };
#  else 
  class SK_API LazyProxyData : public SkRefCnt
  {
  };
#  endif
  SK_API SkDeferredDisplayList(const SkSurfaceCharacterization& characterization, sk_sp<LazyProxyData>);
  SK_API ~SkDeferredDisplayList();
  SK_API const SkSurfaceCharacterization& characterization() const
  {
    return fCharacterization;
  }
  SkDeferredDisplayListPriv priv();
  const SkDeferredDisplayListPriv priv() const;
private:
  friend class GrDrawingManager;
  friend class SkDeferredDisplayListRecorder;
  friend class SkDeferredDisplayListPriv;
  const SkSurfaceCharacterization fCharacterization;
#  if  SK_SUPPORT_GPU
  using PendingPathsMap = std::map<uint32_t, sk_sp<GrCCPerOpsTaskPaths>>;
  SkTArray<sk_sp<GrRenderTask>> fRenderTasks;
  PendingPathsMap fPendingPaths;
#  endif
  sk_sp<LazyProxyData> fLazyProxyData;
};
#endif
