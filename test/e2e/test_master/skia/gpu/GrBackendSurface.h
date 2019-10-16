/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrBackendSurface_DEFINED
#  define GrBackendSurface_DEFINED
#  include "include/gpu/GrTypes.h"
#  include "include/gpu/gl/GrGLTypes.h"
#  include "include/gpu/mock/GrMockTypes.h"
#  include "include/gpu/vk/GrVkTypes.h"
#  include "include/private/GrGLTypesPriv.h"
#  include "include/private/GrVkTypesPriv.h"
#  ifdef SK_DAWN
#    include "include/gpu/dawn/GrDawnTypes.h"
#  endif
class GrVkImageLayout;
class GrGLTextureParameters;
#  ifdef SK_DAWN
#    include "dawn/dawncpp.h"
#  endif
#  ifdef SK_METAL
#    include "include/gpu/mtl/GrMtlTypes.h"
#  endif
#  if  GR_TEST_UTILS
class SkString;
#  endif
#  if  !SK_SUPPORT_GPU
class SK_API GrBackendTexture
{
public:
  GrBackendTexture()
  {
  }
  bool isValid() const
  {
    return false;
  }
};
class SK_API GrBackendRenderTarget
{
public:
  GrBackendRenderTarget()
  {
  }
  bool isValid() const
  {
    return false;
  }
};
#  else 
enum class GrGLFormat;
class SK_API GrBackendFormat
{
public:
  GrBackendFormat()
  {
  }
  GrBackendFormat(const GrBackendFormat& src);
  static GrBackendFormat MakeGL(GrGLenum format, GrGLenum target)
  {
    return GrBackendFormat(format, target);
  }
  static GrBackendFormat MakeVk(VkFormat format)
  {
    return GrBackendFormat(format, GrVkYcbcrConversionInfo());
  }
  static GrBackendFormat MakeVk(const GrVkYcbcrConversionInfo& ycbcrInfo);
#    ifdef SK_DAWN
  static GrBackendFormat MakeDawn(dawn::TextureFormat format)
  {
    return GrBackendFormat(format);
  }
#    endif
#    ifdef SK_METAL
  static GrBackendFormat MakeMtl(GrMTLPixelFormat format)
  {
    return GrBackendFormat(format);
  }
#    endif
  static GrBackendFormat MakeMock(GrColorType colorType)
  {
    return GrBackendFormat(colorType);
  }
  bool operator==(const GrBackendFormat& that) const;
  bool operator!=(const GrBackendFormat& that) const
  {
    return !(*this == that);
  }
  GrBackendApi backend() const
  {
    return fBackend;
  }
  GrTextureType textureType() const
  {
    return fTextureType;
  }
    /**
     * If the backend API is GL this gets the format as a GrGLFormat. Otherwise, returns
     * GrGLFormat::kUnknown.
     */
  GrGLFormat asGLFormat() const;
    /**
     * If the backend API is Vulkan this gets the format as a VkFormat and returns true. Otherwise,
     * returns false.
     */
  bool asVkFormat(VkFormat*) const;
  const GrVkYcbcrConversionInfo* getVkYcbcrConversionInfo() const;
#    ifdef SK_DAWN
    /**
     * If the backend API is Dawn this gets the format as a dawn::TextureFormat and returns true.
     * Otherwise, returns false.
     */
  bool asDawnFormat(dawn::TextureFormat*) const;
#    endif
#    ifdef SK_METAL
    /**
     * If the backend API is Metal this gets the format as a GrMtlPixelFormat. Otherwise,
     * Otherwise, returns MTLPixelFormatInvalid.
     */
  GrMTLPixelFormat asMtlFormat() const;
#    endif
    /**
     * If the backend API is Mock this gets the format as a GrColorType. Otherwise, returns
     * GrColorType::kUnknown.
     */
  GrColorType asMockColorType() const;
  GrBackendFormat makeTexture2D() const;
  bool isValid() const
  {
    return fValid;
  }
#    if  GR_TEST_UTILS
  SkString toStr() const;
#    endif
private:
  GrBackendFormat(GrGLenum format, GrGLenum target);
  GrBackendFormat(const VkFormat vkFormat, const GrVkYcbcrConversionInfo&);
#    ifdef SK_DAWN
  GrBackendFormat(dawn::TextureFormat format);
#    endif
#    ifdef SK_METAL
  GrBackendFormat(const GrMTLPixelFormat mtlFormat);
#    endif
  GrBackendFormat(GrColorType colorType);
  GrBackendApi fBackend = GrBackendApi::kMock;
  bool fValid = false;
  union 
  {
    GrGLenum fGLFormat;
    struct 
{
  VkFormat fFormat;
  GrVkYcbcrConversionInfo fYcbcrConversionInfo;
} fVk;
#    ifdef SK_DAWN
    dawn::TextureFormat fDawnFormat;
#    endif
#    ifdef SK_METAL
    GrMTLPixelFormat fMtlFormat;
#    endif
    GrColorType fMockColorType;
  };
  GrTextureType fTextureType = GrTextureType::kNone;
};
class SK_API GrBackendTexture
{
public:
  GrBackendTexture()
    : fIsValid(false)
  {
  }
  GrBackendTexture(int width, int height, GrMipMapped, const GrGLTextureInfo& glInfo);
  GrBackendTexture(int width, int height, const GrVkImageInfo& vkInfo);
#    ifdef SK_METAL
  GrBackendTexture(int width, int height, GrMipMapped, const GrMtlTextureInfo& mtlInfo);
#    endif
#    ifdef SK_DAWN
  GrBackendTexture(int width, int height, const GrDawnImageInfo& dawnInfo);
#    endif
  GrBackendTexture(int width, int height, GrMipMapped, const GrMockTextureInfo& mockInfo);
  GrBackendTexture(const GrBackendTexture& that);
  ~GrBackendTexture();
  GrBackendTexture& operator=(const GrBackendTexture& that);
  int width() const
  {
    return fWidth;
  }
  int height() const
  {
    return fHeight;
  }
  bool hasMipMaps() const
  {
    return GrMipMapped::kYes == fMipMapped;
  }
  GrBackendApi backend() const
  {
    return fBackend;
  }
  bool getGLTextureInfo(GrGLTextureInfo*) const;
  void glTextureParametersModified();
#    ifdef SK_DAWN
  bool getDawnImageInfo(GrDawnImageInfo*) const;
#    endif
  bool getVkImageInfo(GrVkImageInfo*) const;
  void setVkImageLayout(VkImageLayout);
#    ifdef SK_METAL
  bool getMtlTextureInfo(GrMtlTextureInfo*) const;
#    endif
  GrBackendFormat getBackendFormat() const;
  bool getMockTextureInfo(GrMockTextureInfo*) const;
  bool isProtected() const;
  bool isValid() const
  {
    return fIsValid;
  }
  bool isSameTexture(const GrBackendTexture&);
#    if  GR_TEST_UTILS
  static bool TestingOnly_Equals(const GrBackendTexture&, const GrBackendTexture&);
#    endif
#    ifdef SK_GL
private:
  friend class GrGLTexture;
  friend class GrGLGpu;
  GrBackendTexture(int width, int height, GrMipMapped, const GrGLTextureInfo, sk_sp<GrGLTextureParameters>);
  sk_sp<GrGLTextureParameters> getGLTextureParams() const;
#    endif
#    ifdef SK_VULKAN
  friend class GrVkTexture;
  friend class GrVkGpu;
  GrBackendTexture(int width, int height, const GrVkImageInfo& vkInfo, sk_sp<GrVkImageLayout> layout);
  sk_sp<GrVkImageLayout> getGrVkImageLayout() const;
#    endif
  void cleanup();
  bool fIsValid;
  int fWidth;
  int fHeight;
  GrMipMapped fMipMapped;
  GrBackendApi fBackend;
  union 
  {
#    ifdef SK_GL
    GrGLBackendTextureInfo fGLInfo;
#    endif
    GrVkBackendSurfaceInfo fVkInfo;
    GrMockTextureInfo fMockInfo;
  };
#    ifdef SK_METAL
  GrMtlTextureInfo fMtlInfo;
#    endif
#    ifdef SK_DAWN
  GrDawnImageInfo fDawnInfo;
#    endif
};
class SK_API GrBackendRenderTarget
{
public:
  GrBackendRenderTarget()
    : fIsValid(false)
  {
  }
  GrBackendRenderTarget(int width, int height, int sampleCnt, int stencilBits, const GrGLFramebufferInfo& glInfo);
#    ifdef SK_DAWN
  GrBackendRenderTarget(int width, int height, int sampleCnt, int stencilBits, const GrDawnImageInfo& dawnInfo);
#    endif
    /** Deprecated, use version that does not take stencil bits. */
  GrBackendRenderTarget(int width, int height, int sampleCnt, int stencilBits, const GrVkImageInfo& vkInfo);
  GrBackendRenderTarget(int width, int height, int sampleCnt, const GrVkImageInfo& vkInfo);
#    ifdef SK_METAL
  GrBackendRenderTarget(int width, int height, int sampleCnt, const GrMtlTextureInfo& mtlInfo);
#    endif
  GrBackendRenderTarget(int width, int height, int sampleCnt, int stencilBits, const GrMockRenderTargetInfo& mockInfo);
  ~GrBackendRenderTarget();
  GrBackendRenderTarget(const GrBackendRenderTarget& that);
  GrBackendRenderTarget& operator=(const GrBackendRenderTarget&);
  int width() const
  {
    return fWidth;
  }
  int height() const
  {
    return fHeight;
  }
  int sampleCnt() const
  {
    return fSampleCnt;
  }
  int stencilBits() const
  {
    return fStencilBits;
  }
  GrBackendApi backend() const
  {
    return fBackend;
  }
  bool getGLFramebufferInfo(GrGLFramebufferInfo*) const;
#    ifdef SK_DAWN
  bool getDawnImageInfo(GrDawnImageInfo*) const;
#    endif
  bool getVkImageInfo(GrVkImageInfo*) const;
  void setVkImageLayout(VkImageLayout);
#    ifdef SK_METAL
  bool getMtlTextureInfo(GrMtlTextureInfo*) const;
#    endif
  GrBackendFormat getBackendFormat() const;
  bool getMockRenderTargetInfo(GrMockRenderTargetInfo*) const;
  bool isProtected() const;
  bool isValid() const
  {
    return fIsValid;
  }
#    if  GR_TEST_UTILS
  static bool TestingOnly_Equals(const GrBackendRenderTarget&, const GrBackendRenderTarget&);
#    endif
private:
  friend class GrVkGpu;
  sk_sp<GrVkImageLayout> getGrVkImageLayout() const;
  friend class GrVkRenderTarget;
  GrBackendRenderTarget(int width, int height, int sampleCnt, const GrVkImageInfo& vkInfo, sk_sp<GrVkImageLayout> layout);
  void cleanup();
  bool fIsValid;
  int fWidth;
  int fHeight;
  int fSampleCnt;
  int fStencilBits;
  GrBackendApi fBackend;
  union 
  {
#    ifdef SK_GL
    GrGLFramebufferInfo fGLInfo;
#    endif
    GrVkBackendSurfaceInfo fVkInfo;
    GrMockRenderTargetInfo fMockInfo;
  };
#    ifdef SK_METAL
  GrMtlTextureInfo fMtlInfo;
#    endif
#    ifdef SK_DAWN
  GrDawnImageInfo fDawnInfo;
#    endif
};
#  endif
#endif
