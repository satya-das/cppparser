/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkSurfaceCharacterization_DEFINED
#  define SkSurfaceCharacterization_DEFINED
#  include "include/gpu/GrTypes.h"
#  include "include/core/SkColorSpace.h"
#  include "include/core/SkRefCnt.h"
#  include "include/core/SkSurfaceProps.h"
class SkColorSpace;
#  if  SK_SUPPORT_GPU
#    include "include/gpu/GrBackendSurface.h"
// TODO: remove the GrContext.h include once Flutter is updated
#    include "include/gpu/GrContext.h"
#    include "include/gpu/GrContextThreadSafeProxy.h"
/** \class SkSurfaceCharacterization
    A surface characterization contains all the information Ganesh requires to makes its internal
    rendering decisions. When passed into a SkDeferredDisplayListRecorder it will copy the
    data and pass it on to the SkDeferredDisplayList if/when it is created. Note that both of
    those objects (the Recorder and the DisplayList) will take a ref on the
    GrContextThreadSafeProxy and SkColorSpace objects.
*/
class SK_API SkSurfaceCharacterization
{
public:
  enum class Textureable : bool {
 kNo = false, kYes = true
  };
  enum class MipMapped : bool {
 kNo = false, kYes = true
  };
  enum class UsesGLFBO0 : bool {
 kNo = false, kYes = true
  };
    // This flag indicates if the surface is wrapping a raw Vulkan secondary command buffer.
  enum class VulkanSecondaryCBCompatible : bool {
 kNo = false, kYes = true
  };
  SkSurfaceCharacterization()
    : fCacheMaxResourceBytes(0)
    , fOrigin(kBottomLeft_GrSurfaceOrigin)
    , fSampleCnt(0)
    , fIsTextureable(Textureable::kYes)
    , fIsMipMapped(MipMapped::kYes)
    , fUsesGLFBO0(UsesGLFBO0::kNo)
    , fVulkanSecondaryCBCompatible(VulkanSecondaryCBCompatible::kNo)
    , fIsProtected(GrProtected::kNo)
    , fSurfaceProps(0, kUnknown_SkPixelGeometry)
  {
  }
  SkSurfaceCharacterization(SkSurfaceCharacterization&&);
  SkSurfaceCharacterization& operator=(SkSurfaceCharacterization&&);
  SkSurfaceCharacterization(const SkSurfaceCharacterization&);
  SkSurfaceCharacterization& operator=(const SkSurfaceCharacterization& other);
  bool operator==(const SkSurfaceCharacterization& other) const;
  bool operator!=(const SkSurfaceCharacterization& other) const
  {
    return !(*this == other);
  }
    /*
     * Return a new surface characterization with the only difference being a different width
     * and height
     */
  SkSurfaceCharacterization createResized(int width, int height) const;
    /*
     * Return a new surface characterization with only a replaced color space
     */
  SkSurfaceCharacterization createColorSpace(sk_sp<SkColorSpace>) const;
  GrContextThreadSafeProxy* contextInfo() const
  {
    return fContextInfo.get();
  }
  sk_sp<GrContextThreadSafeProxy> refContextInfo() const
  {
    return fContextInfo;
  }
  size_t cacheMaxResourceBytes() const
  {
    return fCacheMaxResourceBytes;
  }
  bool isValid() const
  {
    return kUnknown_SkColorType != fImageInfo.colorType();
  }
  const SkImageInfo& imageInfo() const
  {
    return fImageInfo;
  }
  const GrBackendFormat& backendFormat() const
  {
    return fBackendFormat;
  }
  GrSurfaceOrigin origin() const
  {
    return fOrigin;
  }
  int width() const
  {
    return fImageInfo.width();
  }
  int height() const
  {
    return fImageInfo.height();
  }
  SkColorType colorType() const
  {
    return fImageInfo.colorType();
  }
  int sampleCount() const
  {
    return fSampleCnt;
  }
  bool isTextureable() const
  {
    return Textureable::kYes == fIsTextureable;
  }
  bool isMipMapped() const
  {
    return MipMapped::kYes == fIsMipMapped;
  }
  bool usesGLFBO0() const
  {
    return UsesGLFBO0::kYes == fUsesGLFBO0;
  }
  bool vulkanSecondaryCBCompatible() const
  {
    return VulkanSecondaryCBCompatible::kYes == fVulkanSecondaryCBCompatible;
  }
  GrProtected isProtected() const
  {
    return fIsProtected;
  }
  SkColorSpace* colorSpace() const
  {
    return fImageInfo.colorSpace();
  }
  sk_sp<SkColorSpace> refColorSpace() const
  {
    return fImageInfo.refColorSpace();
  }
  const SkSurfaceProps& surfaceProps() const
  {
    return fSurfaceProps;
  }
    // Is the provided backend texture compatible with this surface characterization?
  bool isCompatible(const GrBackendTexture&) const;
private:
  friend class SkSurface_Gpu;
  friend class GrVkSecondaryCBDrawContext;
  friend class GrContextThreadSafeProxy;
  friend class SkDeferredDisplayListRecorder;
  friend class SkSurface;
  SkSurfaceCharacterization(sk_sp<GrContextThreadSafeProxy> contextInfo, size_t cacheMaxResourceBytes, const SkImageInfo& ii, const GrBackendFormat& backendFormat, GrSurfaceOrigin origin, int sampleCnt, Textureable isTextureable, MipMapped isMipMapped, UsesGLFBO0 usesGLFBO0, VulkanSecondaryCBCompatible vulkanSecondaryCBCompatible, GrProtected isProtected, const SkSurfaceProps& surfaceProps)
    : fContextInfo(std::move(contextInfo))
    , fCacheMaxResourceBytes(cacheMaxResourceBytes)
    , fImageInfo(ii)
    , fBackendFormat(backendFormat)
    , fOrigin(origin)
    , fSampleCnt(sampleCnt)
    , fIsTextureable(isTextureable)
    , fIsMipMapped(isMipMapped)
    , fUsesGLFBO0(usesGLFBO0)
    , fVulkanSecondaryCBCompatible(vulkanSecondaryCBCompatible)
    , fIsProtected(isProtected)
    , fSurfaceProps(surfaceProps)
  {
  }
  void set(sk_sp<GrContextThreadSafeProxy> contextInfo, size_t cacheMaxResourceBytes, const SkImageInfo& ii, const GrBackendFormat& backendFormat, GrSurfaceOrigin origin, int sampleCnt, Textureable isTextureable, MipMapped isMipMapped, UsesGLFBO0 usesGLFBO0, VulkanSecondaryCBCompatible vulkanSecondaryCBCompatible, GrProtected isProtected, const SkSurfaceProps& surfaceProps)
  {
    SkASSERT(MipMapped::kNo == isMipMapped || Textureable::kYes == isTextureable);
    SkASSERT(Textureable::kNo == isTextureable || UsesGLFBO0::kNo == usesGLFBO0);
    SkASSERT(VulkanSecondaryCBCompatible::kNo == vulkanSecondaryCBCompatible || UsesGLFBO0::kNo == usesGLFBO0);
    SkASSERT(Textureable::kNo == isTextureable || VulkanSecondaryCBCompatible::kNo == vulkanSecondaryCBCompatible);
    fContextInfo = contextInfo;
    fCacheMaxResourceBytes = cacheMaxResourceBytes;
    fImageInfo = ii;
    fBackendFormat = backendFormat;
    fOrigin = origin;
    fSampleCnt = sampleCnt;
    fIsTextureable = isTextureable;
    fIsMipMapped = isMipMapped;
    fUsesGLFBO0 = usesGLFBO0;
    fVulkanSecondaryCBCompatible = vulkanSecondaryCBCompatible;
    fIsProtected = isProtected;
    fSurfaceProps = surfaceProps;
  }
  sk_sp<GrContextThreadSafeProxy> fContextInfo;
  size_t fCacheMaxResourceBytes;
  SkImageInfo fImageInfo;
  GrBackendFormat fBackendFormat;
  GrSurfaceOrigin fOrigin;
  int fSampleCnt;
  Textureable fIsTextureable;
  MipMapped fIsMipMapped;
  UsesGLFBO0 fUsesGLFBO0;
  VulkanSecondaryCBCompatible fVulkanSecondaryCBCompatible;
  GrProtected fIsProtected;
  SkSurfaceProps fSurfaceProps;
};
#  else 
class SK_API SkSurfaceCharacterization
{
public:
  SkSurfaceCharacterization()
    : fSurfaceProps(0, kUnknown_SkPixelGeometry)
  {
  }
  SkSurfaceCharacterization createResized(int width, int height) const
  {
    return *this;
  }
  SkSurfaceCharacterization createColorSpace(sk_sp<SkColorSpace>) const
  {
    return *this;
  }
  bool operator==(const SkSurfaceCharacterization& other) const
  {
    return false;
  }
  bool operator!=(const SkSurfaceCharacterization& other) const
  {
    return !(*this == other);
  }
  size_t cacheMaxResourceBytes() const
  {
    return 0;
  }
  bool isValid() const
  {
    return false;
  }
  int width() const
  {
    return 0;
  }
  int height() const
  {
    return 0;
  }
  int stencilCount() const
  {
    return 0;
  }
  bool isTextureable() const
  {
    return false;
  }
  bool isMipMapped() const
  {
    return false;
  }
  bool usesGLFBO0() const
  {
    return false;
  }
  bool vulkanSecondaryCBCompatible() const
  {
    return false;
  }
  SkColorSpace* colorSpace() const
  {
    return nullptr;
  }
  sk_sp<SkColorSpace> refColorSpace() const
  {
    return nullptr;
  }
  const SkSurfaceProps& surfaceProps() const
  {
    return fSurfaceProps;
  }
private:
  SkSurfaceProps fSurfaceProps;
};
#  endif
#endif
