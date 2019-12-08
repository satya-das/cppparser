/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrVkTypesPriv_DEFINED
#  define GrVkTypesPriv_DEFINED
#  include "include/core/SkRefCnt.h"
#  include "include/gpu/vk/GrVkTypes.h"
class GrVkImageLayout;
struct GrVkBackendSurfaceInfo
{
  GrVkBackendSurfaceInfo(GrVkImageInfo info, GrVkImageLayout* layout)
    : fImageInfo(info)
    , fLayout(layout)
  {
  }
  void cleanup();
  GrVkBackendSurfaceInfo& operator=(const GrVkBackendSurfaceInfo&);
  void assign(const GrVkBackendSurfaceInfo&, bool isValid);
  void setImageLayout(VkImageLayout layout);
  sk_sp<GrVkImageLayout> getGrVkImageLayout() const;
  GrVkImageInfo snapImageInfo() const;
  bool isProtected() const
  {
    return fImageInfo.fProtected == GrProtected::kYes;
  }
#  if  GR_TEST_UTILS
  bool operator==(const GrVkBackendSurfaceInfo& that) const;
#  endif
private:
  GrVkImageInfo fImageInfo;
  GrVkImageLayout* fLayout;
};
#endif
