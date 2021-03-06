/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrSweepGradientLayout.fp; do not modify.
 **************************************************************************************************/
#ifndef GrSweepGradientLayout_DEFINED
#  define GrSweepGradientLayout_DEFINED
#  include "include/core/SkTypes.h"
#  include "src/gpu/gradients/GrGradientShader.h"
#  include "src/shaders/gradients/SkSweepGradient.h"
#  include "src/gpu/GrCoordTransform.h"
#  include "src/gpu/GrFragmentProcessor.h"
class GrSweepGradientLayout : public GrFragmentProcessor
{
public:
  static std::unique_ptr<GrFragmentProcessor> Make(const SkSweepGradient& gradient, const GrFPArgs& args);
  GrSweepGradientLayout(const GrSweepGradientLayout& src);
  std::unique_ptr<GrFragmentProcessor> clone() const override;
  const char* name() const override
  {
    return "SweepGradientLayout";
  }
  GrCoordTransform fCoordTransform0;
  SkMatrix44 gradientMatrix;
  float bias;
  float scale;
private:
  GrSweepGradientLayout(SkMatrix44 gradientMatrix, float bias, float scale)
    : INHERITED(kGrSweepGradientLayout_ClassID, (OptimizationFlags) kPreservesOpaqueInput_OptimizationFlag)
    , fCoordTransform0(gradientMatrix)
    , gradientMatrix(gradientMatrix)
    , bias(bias)
    , scale(scale)
  {
    this->addCoordTransform(&fCoordTransform0);
  }
  GrGLSLFragmentProcessor* onCreateGLSLInstance() const override;
  void onGetGLSLProcessorKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
  bool onIsEqual(const GrFragmentProcessor&) const override;
  GR_DECLARE_FRAGMENT_PROCESSOR_TEST
  typedef GrFragmentProcessor INHERITED;
};
#endif
