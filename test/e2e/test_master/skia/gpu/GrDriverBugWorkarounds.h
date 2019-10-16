/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrDriverBugWorkarounds_DEFINED
#  define GrDriverBugWorkarounds_DEFINED
#  ifdef SK_GPU_WORKAROUNDS_HEADER
#    include SK_GPU_WORKAROUNDS_HEADER
#  else 
#    include "include/gpu/GrDriverBugWorkaroundsAutogen.h"
#  endif
#  include "include/core/SkTypes.h"
#  include <stdint.h>
#  include <vector>
enum GrDriverBugWorkaroundType
{
  ADD_AND_TRUE_TO_LOOP_CONDITION,
  DISABLE_BLEND_EQUATION_ADVANCED,
  DISABLE_DISCARD_FRAMEBUFFER,
  DISABLE_TEXTURE_STORAGE,
  DISALLOW_LARGE_INSTANCED_DRAW,
  EMULATE_ABS_INT_FUNCTION,
  FLUSH_ON_FRAMEBUFFER_CHANGE,
  GL_CLEAR_BROKEN,
  MAX_FRAGMENT_UNIFORM_VECTORS_32,
  MAX_MSAA_SAMPLE_COUNT_4,
  MAX_TEXTURE_SIZE_LIMIT_4096,
  PACK_PARAMETERS_WORKAROUND_WITH_PACK_BUFFER,
  REMOVE_POW_WITH_CONSTANT_EXPONENT,
  RESTORE_SCISSOR_ON_FBO_CHANGE,
  REWRITE_DO_WHILE_LOOPS,
  UNBIND_ATTACHMENTS_ON_BOUND_RENDER_FBO_DELETE,
  UNFOLD_SHORT_CIRCUIT_AS_TERNARY_OPERATION,
  NUMBER_OF_GPU_DRIVER_BUG_WORKAROUND_TYPES
};
class SK_API GrDriverBugWorkarounds
{
public:
  GrDriverBugWorkarounds();
  explicit GrDriverBugWorkarounds(const std::vector<int32_t>& workarounds);
  GrDriverBugWorkarounds& operator=(const GrDriverBugWorkarounds&);
  void applyOverrides(const GrDriverBugWorkarounds& workarounds);
  ~GrDriverBugWorkarounds();
#  define type	, name) bool name = false;
  GPU_DRIVER_BUG_WORKAROUNDS(GPU_OP)
#  undef GPU_OP
};
#endif
