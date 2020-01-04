/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrPathStencilSettings_DEFINED
#  define GrPathStencilSettings_DEFINED
#  include "src/gpu/GrUserStencilSettings.h"
////////////////////////////////////////////////////////////////////////////////
// Stencil rules for paths

////// Even/Odd
static GrUserStencilSettings gEOStencilPass(GrUserStencilSettings::StaticInit<
        0xffff,
        GrUserStencilTest::kAlwaysIfInClip,
        0xffff,
        GrUserStencilOp::kInvert,
        GrUserStencilOp::kKeep,
        0xffff>());
// ok not to check clip b/c stencil pass only wrote inside clip
static GrUserStencilSettings gEOColorPass(GrUserStencilSettings::StaticInit<
        0x0000,
        GrUserStencilTest::kNotEqual,
        0xffff,
        GrUserStencilOp::kZero,
        GrUserStencilOp::kZero,
        0xffff>());
// have to check clip b/c outside clip will always be zero.
static GrUserStencilSettings gInvEOColorPass(GrUserStencilSettings::StaticInit<
        0x0000,
        GrUserStencilTest::kEqualIfInClip,
        0xffff,
        GrUserStencilOp::kZero,
        GrUserStencilOp::kZero,
        0xffff>());
////// Winding
static GrUserStencilSettings gWindStencilPass(GrUserStencilSettings::StaticInitSeparate<
        0xffff,                                0xffff,
        GrUserStencilTest::kAlwaysIfInClip,    GrUserStencilTest::kAlwaysIfInClip,
        0xffff,                                0xffff,
        GrUserStencilOp::kIncWrap,             GrUserStencilOp::kDecWrap,
        GrUserStencilOp::kKeep,                GrUserStencilOp::kKeep,
        0xffff,                                0xffff>());
static GrUserStencilSettings gWindColorPass(GrUserStencilSettings::StaticInit<
        0x0000,
        GrUserStencilTest::kLessIfInClip, // "0 < stencil" is equivalent to "0 != stencil".
        0xffff,
        GrUserStencilOp::kZero,
        GrUserStencilOp::kZero,
        0xffff>());
static GrUserStencilSettings gInvWindColorPass(GrUserStencilSettings::StaticInit<
        0x0000,
        GrUserStencilTest::kEqualIfInClip,
        0xffff,
        GrUserStencilOp::kZero,
        GrUserStencilOp::kZero,
        0xffff>());
////// Normal render to stencil

// Sometimes the default path renderer can draw a path directly to the stencil
// buffer without having to first resolve the interior / exterior.
static GrUserStencilSettings gDirectToStencil(GrUserStencilSettings::StaticInit<
        0x0000,
        GrUserStencilTest::kAlwaysIfInClip,
        0xffff,
        GrUserStencilOp::kZero,
        GrUserStencilOp::kIncMaybeClamp,
        0xffff>());
#endif
