/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrAHardwareBufferImageGenerator_DEFINED
#  define GrAHardwareBufferImageGenerator_DEFINED
#  include "include/core/SkImageGenerator.h"
#  include "include/private/GrTypesPriv.h"
class GrGpuResource;
extern "C" {
  typedef struct AHardwareBuffer AHardwareBuffer;
  }
class GrAHardwareBufferImageGenerator : public SkImageGenerator
{
public:
  static std::unique_ptr<SkImageGenerator> Make(AHardwareBuffer*, SkAlphaType, sk_sp<SkColorSpace>, GrSurfaceOrigin);
  ~GrAHardwareBufferImageGenerator();
  static void DeleteGLTexture(void* ctx);
protected:
  bool onIsValid(GrContext*) const override;
  TexGenType onCanGenerateTexture() const override
  {
    return TexGenType::kCheap;
  }
  sk_sp<GrTextureProxy> onGenerateTexture(GrRecordingContext*, const SkImageInfo&, const SkIPoint&, bool willNeedMipMaps) override;
private:
  GrAHardwareBufferImageGenerator(const SkImageInfo&, AHardwareBuffer*, SkAlphaType, bool isProtectedContent, uint32_t bufferFormat, GrSurfaceOrigin surfaceOrigin);
  sk_sp<GrTextureProxy> makeProxy(GrRecordingContext* context);
  void releaseTextureRef();
  static void ReleaseRefHelper_TextureReleaseProc(void* ctx);
  AHardwareBuffer* fHardwareBuffer;
  uint32_t fBufferFormat;
  const bool fIsProtectedContent;
  GrSurfaceOrigin fSurfaceOrigin;
  typedef SkImageGenerator INHERITED;
};
#endif
