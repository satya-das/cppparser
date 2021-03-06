/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrSurfaceProxyPriv_DEFINED
#  define GrSurfaceProxyPriv_DEFINED
#  include "src/gpu/GrSurfaceProxy.h"
#  include "src/gpu/GrResourceProvider.h"
/** Class that adds methods to GrSurfaceProxy that are only intended for use internal to Skia.
    This class is purely a privileged window into GrSurfaceProxy. It should never have additional
    data members or virtual methods. */
class GrSurfaceProxyPriv
{
public:
  void computeScratchKey(GrScratchKey* key) const
  {
    return fProxy->computeScratchKey(key);
  }
    // Create a GrSurface-derived class that meets the requirements (i.e, desc, renderability)
    // of the GrSurfaceProxy.
  sk_sp<GrSurface> createSurface(GrResourceProvider* resourceProvider) const
  {
    return fProxy->createSurface(resourceProvider);
  }
    // Assign this proxy the provided GrSurface as its backing surface
  void assign(sk_sp<GrSurface> surface)
  {
    fProxy->assign(std::move(surface));
  }
    // Don't abuse this call!!!!!!!
  bool isExact() const
  {
    return SkBackingFit::kExact == fProxy->fFit;
  }
    // Don't. Just don't.
  void exactify(bool allocatedCaseOnly);
  void setLazySize(int width, int height)
  {
    fProxy->setLazySize(width, height);
  }
  bool doLazyInstantiation(GrResourceProvider*);
  static bool SK_WARN_UNUSED_RESULT AttachStencilIfNeeded(GrResourceProvider*, GrSurface*, int minStencilSampleCount);
private:
  explicit GrSurfaceProxyPriv(GrSurfaceProxy* proxy)
    : fProxy(proxy)
  {
  }
  GrSurfaceProxyPriv(const GrSurfaceProxyPriv&)
  {
  }
  GrSurfaceProxyPriv& operator=(const GrSurfaceProxyPriv&);
    // No taking addresses of this type.
  const GrSurfaceProxyPriv* operator&() const;
  GrSurfaceProxyPriv* operator&();
  GrSurfaceProxy* fProxy;
  friend class GrSurfaceProxy;
};
inline GrSurfaceProxyPriv GrSurfaceProxy::priv()
{
  return GrSurfaceProxyPriv(this);
}
inline const GrSurfaceProxyPriv GrSurfaceProxy::priv() const
{
  return GrSurfaceProxyPriv(const_cast<GrSurfaceProxy*>(this));
}
#endif
