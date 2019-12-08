/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include "include/core/SkRefCnt.h"
#include "include/gpu/gl/GrGLTypes.h"
#ifndef GrGLTypesPriv_DEFINED
#  define GrGLTypesPriv_DEFINED
static int kGrGLFormatCount = static_cast<int>(GrGLFormat::kLast) + 1;
class GrGLTextureParameters : public SkNVRefCnt<GrGLTextureParameters>
{
  using ResetTimestamp = uint64_t;
public:
  GrGLTextureParameters();
  struct SamplerOverriddenState
  {
    SamplerOverriddenState();
    void invalidate();
    GrGLenum fMinFilter;
    GrGLenum fMagFilter;
    GrGLenum fWrapS;
    GrGLenum fWrapT;
    GrGLfloat fMinLOD;
    GrGLfloat fMaxLOD;
    bool fBorderColorInvalid;
  };
  struct NonsamplerState
  {
    NonsamplerState();
    void invalidate();
    uint32_t fSwizzleKey;
    GrGLint fBaseMipMapLevel;
    GrGLint fMaxMipMapLevel;
  };
  void invalidate();
  ResetTimestamp resetTimestamp() const
  {
    return fResetTimestamp;
  }
  const SamplerOverriddenState& samplerOverriddenState() const
  {
    return fSamplerOverriddenState;
  }
  const NonsamplerState& nonsamplerState() const
  {
    return fNonsamplerState;
  }
  void set(const SamplerOverriddenState* samplerState, const NonsamplerState& nonsamplerState, ResetTimestamp currTimestamp);
private:
  static ResetTimestamp kExpiredTimestamp = 0;
  SamplerOverriddenState fSamplerOverriddenState;
  NonsamplerState fNonsamplerState;
  ResetTimestamp fResetTimestamp = kExpiredTimestamp;
};
class GrGLBackendTextureInfo
{
public:
  GrGLBackendTextureInfo(const GrGLTextureInfo& info, GrGLTextureParameters* params)
    : fInfo(info)
    , fParams(params)
  {
  }
  GrGLBackendTextureInfo(const GrGLBackendTextureInfo&) = delete;
  GrGLBackendTextureInfo& operator=(const GrGLBackendTextureInfo&);
  const GrGLTextureInfo& info() const
  {
    return fInfo;
  }
  GrGLTextureParameters* parameters() const
  {
    return fParams;
  }
  sk_sp<GrGLTextureParameters> refParameters() const
  {
    return sk_ref_sp(fParams);
  }
  void cleanup();
  void assign(const GrGLBackendTextureInfo&, bool thisIsValid);
private:
  GrGLTextureInfo fInfo;
  GrGLTextureParameters* fParams;
};
#endif
