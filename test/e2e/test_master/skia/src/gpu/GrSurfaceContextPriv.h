/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrSurfaceContextPriv_DEFINED
#  define GrSurfaceContextPriv_DEFINED
#  include "src/gpu/GrSurfaceContext.h"
class GrSurfaceContextPriv
{
public:
  GrRecordingContext* getContext()
  {
    return fSurfaceContext->fContext;
  }
private:
  explicit GrSurfaceContextPriv(GrSurfaceContext* surfaceContext)
    : fSurfaceContext(surfaceContext)
  {
  }
  GrSurfaceContextPriv(const GrSurfaceContextPriv&)
  {
  }
  GrSurfaceContextPriv& operator=(const GrSurfaceContextPriv&);
    // No taking addresses of this type.
  const GrSurfaceContextPriv* operator&() const;
  GrSurfaceContextPriv* operator&();
  GrSurfaceContext* fSurfaceContext;
  friend class GrSurfaceContext;
};
inline GrSurfaceContextPriv GrSurfaceContext::surfPriv()
{
  return GrSurfaceContextPriv(this);
}
inline const GrSurfaceContextPriv GrSurfaceContext::surfPriv() const
{
  return GrSurfaceContextPriv(const_cast<GrSurfaceContext*>(this));
}
#endif
