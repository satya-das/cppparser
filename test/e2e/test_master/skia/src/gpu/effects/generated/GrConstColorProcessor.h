/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/**************************************************************************************************
 *** This file was autogenerated from GrConstColorProcessor.fp; do not modify.
 **************************************************************************************************/
#ifndef GrConstColorProcessor_DEFINED
#  define GrConstColorProcessor_DEFINED
#  include "include/core/SkTypes.h"
#  include "src/gpu/GrCoordTransform.h"
#  include "src/gpu/GrFragmentProcessor.h"
class GrConstColorProcessor : public GrFragmentProcessor
{
public:
  enum class InputMode {
 kIgnore = 0, kLast = 2, kModulateA = 2, kModulateRGBA = 1
  };
  static const int kInputModeCnt = (int) InputMode::kLast + 1;
  static OptimizationFlags OptFlags(const SkPMColor4f& color, InputMode mode)
  {
    OptimizationFlags flags = kConstantOutputForConstantInput_OptimizationFlag;
    if (mode != InputMode::kIgnore)
    {
      flags |= kCompatibleWithCoverageAsAlpha_OptimizationFlag;
    }
    if (color.isOpaque())
    {
      flags |= kPreservesOpaqueInput_OptimizationFlag;
    }
    return flags;
  }
  SkPMColor4f constantOutputForConstantInput(const SkPMColor4f& input) const override
  {
    switch(mode)
    {
      case InputMode::kIgnore:
        return color;
      case InputMode::kModulateA:
        return color * input.fA;
      case InputMode::kModulateRGBA:
        return color * input;
    }
    SK_ABORT("Unexpected mode");
  }
  static std::unique_ptr<GrFragmentProcessor> Make(SkPMColor4f color, InputMode mode)
  {
    return std::unique_ptr<GrFragmentProcessor>(new GrConstColorProcessor(color, mode));
  }
  GrConstColorProcessor(const GrConstColorProcessor& src);
  std::unique_ptr<GrFragmentProcessor> clone() const override;
  const char* name() const override
  {
    return "ConstColorProcessor";
  }
  SkPMColor4f color;
  InputMode mode;
private:
  GrConstColorProcessor(SkPMColor4f color, InputMode mode)
    : INHERITED(kGrConstColorProcessor_ClassID, (OptimizationFlags) OptFlags(color, mode))
    , color(color)
    , mode(mode)
  {
  }
  GrGLSLFragmentProcessor* onCreateGLSLInstance() const override;
  void onGetGLSLProcessorKey(const GrShaderCaps&, GrProcessorKeyBuilder*) const override;
  bool onIsEqual(const GrFragmentProcessor&) const override;
  GR_DECLARE_FRAGMENT_PROCESSOR_TEST
  typedef GrFragmentProcessor INHERITED;
};
#endif
