/*
 * Copyright 2013 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrBezierEffect_DEFINED
#  define GrBezierEffect_DEFINED
#  include "include/private/GrTypesPriv.h"
#  include "src/gpu/GrCaps.h"
#  include "src/gpu/GrGeometryProcessor.h"
#  include "src/gpu/GrProcessor.h"
class GrGLConicEffect;
class GrConicEffect : public GrGeometryProcessor
{
public:
  static sk_sp<GrGeometryProcessor> Make(const SkPMColor4f& color, const SkMatrix& viewMatrix, const GrClipEdgeType edgeType, const GrCaps& caps, const SkMatrix& localMatrix, bool usesLocalCoords, uint8_t coverage = 0xff)
  {
    switch(edgeType)
    {
      case GrClipEdgeType::kFillAA:
        if (!caps.shaderCaps()->shaderDerivativeSupport())
        {
          return nullptr;
        }
        return sk_sp<GrGeometryProcessor>(new GrConicEffect(color, viewMatrix, coverage, GrClipEdgeType::kFillAA, localMatrix, usesLocalCoords));
      case GrClipEdgeType::kHairlineAA:
        if (!caps.shaderCaps()->shaderDerivativeSupport())
        {
          return nullptr;
        }
        return sk_sp<GrGeometryProcessor>(new GrConicEffect(color, viewMatrix, coverage, GrClipEdgeType::kHairlineAA, localMatrix, usesLocalCoords));
      case GrClipEdgeType::kFillBW:
        return sk_sp<GrGeometryProcessor>(new GrConicEffect(color, viewMatrix, coverage, GrClipEdgeType::kFillBW, localMatrix, usesLocalCoords));
default:
      return nullptr;
  }
  }
  ~GrConicEffect();
  const char* name() const override
  {
    return "Conic";
  }
  inline const Attribute& inPosition() const
  {
    return kAttributes[0];
  }
  inline const Attribute& inConicCoeffs() const
  {
    return kAttributes[1];
  }
  inline bool isAntiAliased() const
  {
    return GrProcessorEdgeTypeIsAA(fEdgeType);
  }
  inline bool isFilled() const
  {
    return GrProcessorEdgeTypeIsFill(fEdgeType);
  }
  inline GrClipEdgeType getEdgeType() const
  {
    return fEdgeType;
  }
  const SkPMColor4f& color() const
  {
    return fColor;
  }
  const SkMatrix& viewMatrix() const
  {
    return fViewMatrix;
  }
  const SkMatrix& localMatrix() const
  {
    return fLocalMatrix;
  }
  bool usesLocalCoords() const
  {
    return fUsesLocalCoords;
  }
  uint8_t coverageScale() const
  {
    return fCoverageScale;
  }
  void getGLSLProcessorKey(const GrShaderCaps& caps, GrProcessorKeyBuilder* b) const override;
  GrGLSLPrimitiveProcessor* createGLSLInstance(const GrShaderCaps&) const override;
private:
  GrConicEffect(const SkPMColor4f&, const SkMatrix& viewMatrix, uint8_t coverage, GrClipEdgeType, const SkMatrix& localMatrix, bool usesLocalCoords);
  SkPMColor4f fColor;
  SkMatrix fViewMatrix;
  SkMatrix fLocalMatrix;
  bool fUsesLocalCoords;
  uint8_t fCoverageScale;
  GrClipEdgeType fEdgeType;
  static Attribute kAttributes[] = {{"inPosition", kFloat2_GrVertexAttribType, kFloat2_GrSLType}, {"inConicCoeffs", kFloat4_GrVertexAttribType, kHalf4_GrSLType}};
  GR_DECLARE_GEOMETRY_PROCESSOR_TEST
  typedef GrGeometryProcessor INHERITED;
};
///////////////////////////////////////////////////////////////////////////////
/**
 * The output of this effect is a hairline edge for quadratics.
 * Quadratic specified by 0=u^2-v canonical coords. u and v are the first
 * two components of the vertex attribute. At the three control points that define
 * the Quadratic, u, v have the values {0,0}, {1/2, 0}, and {1, 1} respectively.
 * Coverage for AA is min(0, 1-distance). 3rd & 4th cimponent unused.
 * Requires shader derivative instruction support.
 */
class GrGLQuadEffect;
class GrQuadEffect : public GrGeometryProcessor
{
public:
  static sk_sp<GrGeometryProcessor> Make(const SkPMColor4f& color, const SkMatrix& viewMatrix, const GrClipEdgeType edgeType, const GrCaps& caps, const SkMatrix& localMatrix, bool usesLocalCoords, uint8_t coverage = 0xff)
  {
    switch(edgeType)
    {
      case GrClipEdgeType::kFillAA:
        if (!caps.shaderCaps()->shaderDerivativeSupport())
        {
          return nullptr;
        }
        return sk_sp<GrGeometryProcessor>(new GrQuadEffect(color, viewMatrix, coverage, GrClipEdgeType::kFillAA, localMatrix, usesLocalCoords));
      case GrClipEdgeType::kHairlineAA:
        if (!caps.shaderCaps()->shaderDerivativeSupport())
        {
          return nullptr;
        }
        return sk_sp<GrGeometryProcessor>(new GrQuadEffect(color, viewMatrix, coverage, GrClipEdgeType::kHairlineAA, localMatrix, usesLocalCoords));
      case GrClipEdgeType::kFillBW:
        return sk_sp<GrGeometryProcessor>(new GrQuadEffect(color, viewMatrix, coverage, GrClipEdgeType::kFillBW, localMatrix, usesLocalCoords));
default:
      return nullptr;
  }
  }
  ~GrQuadEffect();
  const char* name() const override
  {
    return "Quad";
  }
  inline const Attribute& inPosition() const
  {
    return kAttributes[0];
  }
  inline const Attribute& inHairQuadEdge() const
  {
    return kAttributes[1];
  }
  inline bool isAntiAliased() const
  {
    return GrProcessorEdgeTypeIsAA(fEdgeType);
  }
  inline bool isFilled() const
  {
    return GrProcessorEdgeTypeIsFill(fEdgeType);
  }
  inline GrClipEdgeType getEdgeType() const
  {
    return fEdgeType;
  }
  const SkPMColor4f& color() const
  {
    return fColor;
  }
  const SkMatrix& viewMatrix() const
  {
    return fViewMatrix;
  }
  const SkMatrix& localMatrix() const
  {
    return fLocalMatrix;
  }
  bool usesLocalCoords() const
  {
    return fUsesLocalCoords;
  }
  uint8_t coverageScale() const
  {
    return fCoverageScale;
  }
  void getGLSLProcessorKey(const GrShaderCaps& caps, GrProcessorKeyBuilder* b) const override;
  GrGLSLPrimitiveProcessor* createGLSLInstance(const GrShaderCaps&) const override;
private:
  GrQuadEffect(const SkPMColor4f&, const SkMatrix& viewMatrix, uint8_t coverage, GrClipEdgeType, const SkMatrix& localMatrix, bool usesLocalCoords);
  SkPMColor4f fColor;
  SkMatrix fViewMatrix;
  SkMatrix fLocalMatrix;
  bool fUsesLocalCoords;
  uint8_t fCoverageScale;
  GrClipEdgeType fEdgeType;
  static Attribute kAttributes[] = {{"inPosition", kFloat2_GrVertexAttribType, kFloat2_GrSLType}, {"inHairQuadEdge", kFloat4_GrVertexAttribType, kHalf4_GrSLType}};
  GR_DECLARE_GEOMETRY_PROCESSOR_TEST
  typedef GrGeometryProcessor INHERITED;
};
#endif
