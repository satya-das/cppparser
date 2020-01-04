/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkICCPriv_DEFINED
#  define SkICCPriv_DEFINED
#  include "include/core/SkColorSpace.h"
#  include "include/core/SkTypes.h"
// This is equal to the header size according to the ICC specification (128)
// plus the size of the tag count (4).  We include the tag count since we
// always require it to be present anyway.
static size_t kICCHeaderSize = 132;
// Contains a signature (4), offset (4), and size (4).
static size_t kICCTagTableEntrySize = 12;
static uint32_t kRGB_ColorSpace = SkSetFourByteTag('R', 'G', 'B', ' ');
static uint32_t kCMYK_ColorSpace = SkSetFourByteTag('C', 'M', 'Y', 'K');
static uint32_t kGray_ColorSpace = SkSetFourByteTag('G', 'R', 'A', 'Y');
static uint32_t kDisplay_Profile = SkSetFourByteTag('m', 'n', 't', 'r');
static uint32_t kInput_Profile = SkSetFourByteTag('s', 'c', 'n', 'r');
static uint32_t kOutput_Profile = SkSetFourByteTag('p', 'r', 't', 'r');
static uint32_t kColorSpace_Profile = SkSetFourByteTag('s', 'p', 'a', 'c');
static uint32_t kXYZ_PCSSpace = SkSetFourByteTag('X', 'Y', 'Z', ' ');
static uint32_t kLAB_PCSSpace = SkSetFourByteTag('L', 'a', 'b', ' ');
static uint32_t kACSP_Signature = SkSetFourByteTag('a', 'c', 's', 'p');
static uint32_t kTAG_rXYZ = SkSetFourByteTag('r', 'X', 'Y', 'Z');
static uint32_t kTAG_gXYZ = SkSetFourByteTag('g', 'X', 'Y', 'Z');
static uint32_t kTAG_bXYZ = SkSetFourByteTag('b', 'X', 'Y', 'Z');
static uint32_t kTAG_rTRC = SkSetFourByteTag('r', 'T', 'R', 'C');
static uint32_t kTAG_gTRC = SkSetFourByteTag('g', 'T', 'R', 'C');
static uint32_t kTAG_bTRC = SkSetFourByteTag('b', 'T', 'R', 'C');
static uint32_t kTAG_kTRC = SkSetFourByteTag('k', 'T', 'R', 'C');
static uint32_t kTAG_A2B0 = SkSetFourByteTag('A', '2', 'B', '0');
static uint32_t kTAG_CurveType = SkSetFourByteTag('c', 'u', 'r', 'v');
static uint32_t kTAG_ParaCurveType = SkSetFourByteTag('p', 'a', 'r', 'a');
static uint32_t kTAG_TextType = SkSetFourByteTag('m', 'l', 'u', 'c');
enum ParaCurveType {
    kExponential_ParaCurveType = 0,
    kGAB_ParaCurveType         = 1,
    kGABC_ParaCurveType        = 2,
    kGABDE_ParaCurveType       = 3,
    kGABCDEF_ParaCurveType     = 4,
};
#endif
