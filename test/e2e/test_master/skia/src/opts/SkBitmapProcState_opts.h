/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkBitmapProcState_opts_DEFINED
#  define SkBitmapProcState_opts_DEFINED
#  include "include/private/SkVx.h"
#  include "src/core/SkBitmapProcState.h"
#  include "src/core/SkMSAN.h"
// SkBitmapProcState optimized Shader, Sample, or Matrix procs.
//
// Only S32_alpha_D32_filter_DX exploits instructions beyond
// our common baseline SSE2/NEON instruction sets, so that's
// all that lives here.
//
// The rest are scattershot at the moment but I want to get them
// all migrated to be normal code inside SkBitmapProcState.cpp.
#  if  SK_CPU_SSE_LEVEL >= SK_CPU_SSE_LEVEL_SSE2
#    include <immintrin.h>
#  elif  defined(SK_ARM_HAS_NEON)
#    include <arm_neon.h>
#  endif
namespace SK_OPTS_NS
{
// This same basic packing scheme is used throughout the file.
  template <typename U32, typename Out>
  static void decode_packed_coordinates_and_weight(U32 packed, Out* v0, Out* v1, Out* w)
  {
    *v0 = (packed >> 18);
    *v1 = (packed & 0x3fff);
    *w = (packed >> 14) & 0xf;
  }
#  if  1 && SK_CPU_SSE_LEVEL >= SK_CPU_SSE_LEVEL_AVX2
  inline void S32_alpha_D32_filter_DX(const SkBitmapProcState& s, const uint32_t* xy, int count, uint32_t* colors)
  {
    SkASSERT(count > 0 && colors != nullptr);
    SkASSERT(s.fFilterQuality != kNone_SkFilterQuality);
    SkASSERT(kN32_SkColorType == s.fPixmap.colorType());
    SkASSERT(s.fAlphaScale <= 256);
        // In a _DX variant only X varies; all samples share y0/y1 coordinates and wy weight.
    int y0, y1, wy;
    decode_packed_coordinates_and_weight(*xy++, &y0, &y1, &wy);
    const uint32_t* row0 = s.fPixmap.addr32(0, y0);
    const uint32_t* row1 = s.fPixmap.addr32(0, y1);
    auto bilerp = ;
    while (count >= 8)
    {
      bilerp(skvx::Vec<8,uint32_t>::Load(xy)).store(colors);
      xy += 8;
      colors += 8;
      count -= 8;
    }
    if (count > 0)
    {
      __m256i active = skvx::bit_pun<__m256i>(count > skvx::Vec<8,int>(0, 1, 2, 3, 4, 5, 6, 7)), coords, pixels;
      bilerp(skvx::bit_pun<skvx::Vec<8,uint32_t>>(coords)).store(&pixels);
      _mm256_maskstore_epi32((int*) colors, active, pixels);
      sk_msan_mark_initialized(colors, colors + count, "MSAN still doesn't understand AVX2 mask loads and stores.");
    }
  }
#  elif  1 && SK_CPU_SSE_LEVEL >= SK_CPU_SSE_LEVEL_SSSE3
  inline void S32_alpha_D32_filter_DX(const SkBitmapProcState& s, const uint32_t* xy, int count, uint32_t* colors)
  {
    SkASSERT(count > 0 && colors != nullptr);
    SkASSERT(s.fFilterQuality != kNone_SkFilterQuality);
    SkASSERT(kN32_SkColorType == s.fPixmap.colorType());
    SkASSERT(s.fAlphaScale <= 256);
        // interpolate_in_x() is the crux of the SSSE3 implementation,
        // interpolating in X for up to two output pixels (A and B) using _mm_maddubs_epi16().
    auto interpolate_in_x = ;
        // Interpolate {A0..A3} --> output pixel A, and {B0..B3} --> output pixel B.
        // Returns two pixels, with each color channel in a 16-bit lane of the __m128i.
    auto interpolate_in_x_and_y = ;
        // We're in _DX mode here, so we're only varying in X.
        // That means the first entry of xy is our constant pair of Y coordinates and weight in Y.
        // All the other entries in xy will be pairs of X coordinates and the X weight.
    int y0, y1, wy;
    decode_packed_coordinates_and_weight(*xy++, &y0, &y1, &wy);
    auto row0 = (const uint32_t*) ((const uint8_t*) s.fPixmap.addr() + y0 * s.fPixmap.rowBytes()), row1;
    while (count >= 4)
    {
            // We can really get going, loading 4 X-pairs at a time to produce 4 output pixels.
      int x0[4];
      int x1[4];
      __m128i wx;
            // decode_packed_coordinates_and_weight(), 4x.
      __m128i packed = _mm_loadu_si128((const __m128i*) xy);
      _mm_storeu_si128((__m128i*) x0, _mm_srli_epi32(packed, 18));
      _mm_storeu_si128((__m128i*) x1, _mm_and_si128(packed, _mm_set1_epi32(0x3fff)));
      wx = _mm_and_si128(_mm_srli_epi32(packed, 14), _mm_set1_epi32(0xf));
            // Splat each x weight 4x (for each color channel) as wr for pixels on the right at x1,
            // and sixteen minus that as wl for pixels on the left at x0.
      __m128i wr = _mm_shuffle_epi8(wx, _mm_setr_epi8(0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12)), wl;
            // We need to interlace wl and wr for _mm_maddubs_epi16().
      __m128i interlaced_x_weights_AB = _mm_unpacklo_epi8(wl, wr), interlaced_x_weights_CD;
      enum { A,B,C,D };
            // interpolate_in_x_and_y() can produce two output pixels (A and B) at a time
            // from eight input pixels {A0..A3} and {B0..B3}, arranged in a 2x2 grid for each.
      __m128i AB = interpolate_in_x_and_y(row0[x0[A]], row0[x1[A]], row1[x0[A]], row1[x1[A]], row0[x0[B]], row0[x1[B]], row1[x0[B]], row1[x1[B]], interlaced_x_weights_AB, wy);
            // Once more with the other half of the x-weights for two more pixels C,D.
      __m128i CD = interpolate_in_x_and_y(row0[x0[C]], row0[x1[C]], row1[x0[C]], row1[x1[C]], row0[x0[D]], row0[x1[D]], row1[x0[D]], row1[x1[D]], interlaced_x_weights_CD, wy);
            // Scale by alpha, pack back together to 8-bit lanes, and write out four pixels!
      _mm_storeu_si128((__m128i*) colors, _mm_packus_epi16(AB, CD));
      xy += 4;
      colors += 4;
      count -= 4;
    }
    while (count-- > 0)
    {
            // This is exactly the same flow as the count >= 4 loop above, but writing one pixel.
      int x0, x1, wx;
      decode_packed_coordinates_and_weight(*xy++, &x0, &x1, &wx);
            // As above, splat out wx four times as wr, and sixteen minus that as wl.
      __m128i wr = _mm_set1_epi8(wx), wl;
      __m128i interlaced_x_weights = _mm_unpacklo_epi8(wl, wr);
      __m128i A = interpolate_in_x_and_y(row0[x0], row0[x1], row1[x0], row1[x1], 0, 0, 0, 0, interlaced_x_weights, wy);
      *colors++ = _mm_cvtsi128_si32(_mm_packus_epi16(A, _mm_setzero_si128()));
    }
  }
#  elif  1 && SK_CPU_SSE_LEVEL >= SK_CPU_SSE_LEVEL_SSE2
  inline void S32_alpha_D32_filter_DX(const SkBitmapProcState& s, const uint32_t* xy, int count, uint32_t* colors)
  {
    SkASSERT(count > 0 && colors != nullptr);
    SkASSERT(s.fFilterQuality != kNone_SkFilterQuality);
    SkASSERT(kN32_SkColorType == s.fPixmap.colorType());
    SkASSERT(s.fAlphaScale <= 256);
    int y0, y1, wy;
    decode_packed_coordinates_and_weight(*xy++, &y0, &y1, &wy);
    auto row0 = (const uint32_t*) ((const char*) s.fPixmap.addr() + y0 * s.fPixmap.rowBytes()), row1;
        // We'll put one pixel in the low 4 16-bit lanes to line up with wy,
        // and another in the upper 4 16-bit lanes to line up with 16 - wy.
    const __m128i allY = _mm_unpacklo_epi64(_mm_set1_epi16(wy), _mm_set1_epi16(16 - wy));
    while (count-- > 0)
    {
      int x0, x1, wx;
      decode_packed_coordinates_and_weight(*xy++, &x0, &x1, &wx);
            // Load the 4 pixels we're interpolating, in this grid:
            //    | tl  tr |
            //    | bl  br |
      const __m128i tl = _mm_cvtsi32_si128(row0[x0]), tr, bl, br;
            // We want to calculate a sum of 4 pixels weighted in two directions:
            //
            //  sum = tl * (16-wy) * (16-wx)
            //      + bl * (   wy) * (16-wx)
            //      + tr * (16-wy) * (   wx)
            //      + br * (   wy) * (   wx)
            //
            // (Notice top --> 16-wy, bottom --> wy, left --> 16-wx, right --> wx.)
            //
            // We've already prepared allY as a vector containing [wy, 16-wy] as a way
            // to apply those y-direction weights.  So we'll start on the x-direction
            // first, grouping into left and right halves, lined up with allY:
            //
            //     L = [bl, tl]
            //     R = [br, tr]
            //
            //   sum = horizontalSum( allY * (L*(16-wx) + R*wx) )
            //
            // Rewriting that one more step, we can replace a multiply with a shift:
            //
            //   sum = horizontalSum( allY * (16*L + (R-L)*wx) )
            //
            // That's how we'll actually do this math.
      __m128i L = _mm_unpacklo_epi8(_mm_unpacklo_epi32(bl, tl), _mm_setzero_si128()), R;
      __m128i inner = _mm_add_epi16(_mm_slli_epi16(L, 4), _mm_mullo_epi16(_mm_sub_epi16(R, L), _mm_set1_epi16(wx)));
      __m128i sum_in_x = _mm_mullo_epi16(inner, allY);
            // sum = horizontalSum( ... )
      __m128i sum = _mm_add_epi16(sum_in_x, _mm_srli_si128(sum_in_x, 8));
            // Get back to [0,255] by dividing by maximum weight 16x16 = 256.
      sum = _mm_srli_epi16(sum, 8);
      if (s.fAlphaScale < 256)
      {
                // Scale by alpha, which is in [0,256].
        sum = _mm_mullo_epi16(sum, _mm_set1_epi16(s.fAlphaScale));
        sum = _mm_srli_epi16(sum, 8);
      }
            // Pack back into 8-bit values and store.
      *colors++ = _mm_cvtsi128_si32(_mm_packus_epi16(sum, _mm_setzero_si128()));
    }
  }
#  else 
    // The NEON code only actually differs from the portable code in the
    // filtering step after we've loaded all four pixels we want to bilerp.
#    if  defined(SK_ARM_HAS_NEON)
  static void filter_and_scale_by_alpha(unsigned x, unsigned y, SkPMColor a00, SkPMColor a01, SkPMColor a10, SkPMColor a11, SkPMColor* dst, uint16_t scale)
  {
    uint8x8_t vy, vconst16_8, v16_y, vres;
    uint16x4_t vx, vconst16_16, v16_x, tmp, vscale;
    uint32x2_t va0, va1;
    uint16x8_t tmp1, tmp2;
    vy = vdup_n_u8(y);
    vconst16_8 = vmov_n_u8(16);
    v16_y = vsub_u8(vconst16_8, vy);
    va0 = vdup_n_u32(a00);
    va1 = vdup_n_u32(a10);
    va0 = vset_lane_u32(a01, va0, 1);
    va1 = vset_lane_u32(a11, va1, 1);
    tmp1 = vmull_u8(vreinterpret_u8_u32(va0), v16_y);
    tmp2 = vmull_u8(vreinterpret_u8_u32(va1), vy);
    vx = vdup_n_u16(x);
    vconst16_16 = vmov_n_u16(16);
    v16_x = vsub_u16(vconst16_16, vx);
    tmp = vmul_u16(vget_high_u16(tmp1), vx);
    tmp = vmla_u16(tmp, vget_high_u16(tmp2), vx);
    tmp = vmla_u16(tmp, vget_low_u16(tmp1), v16_x);
    tmp = vmla_u16(tmp, vget_low_u16(tmp2), v16_x);
    if (scale < 256)
    {
      vscale = vdup_n_u16(scale);
      tmp = vshr_n_u16(tmp, 8);
      tmp = vmul_u16(tmp, vscale);
    }
    vres = vshrn_n_u16(vcombine_u16(tmp, vcreate_u16(0)), 8);
    vst1_lane_u32(dst, vreinterpret_u32_u8(vres), 0);
  }
#    else 
  static void filter_and_scale_by_alpha(unsigned x, unsigned y, SkPMColor a00, SkPMColor a01, SkPMColor a10, SkPMColor a11, SkPMColor* dstColor, unsigned alphaScale)
  {
    SkASSERT((unsigned) x <= 0xF);
    SkASSERT((unsigned) y <= 0xF);
    SkASSERT(alphaScale <= 256);
    int xy = x * y;
    const uint32_t mask = 0xFF00FF;
    int scale = 256 - 16 * y - 16 * x + xy;
    uint32_t lo = (a00 & mask) * scale;
    uint32_t hi = ((a00 >> 8) & mask) * scale;
    scale = 16 * x - xy;
    lo += (a01 & mask) * scale;
    hi += ((a01 >> 8) & mask) * scale;
    scale = 16 * y - xy;
    lo += (a10 & mask) * scale;
    hi += ((a10 >> 8) & mask) * scale;
    lo += (a11 & mask) * xy;
    hi += ((a11 >> 8) & mask) * xy;
    if (alphaScale < 256)
    {
      lo = ((lo >> 8) & mask) * alphaScale;
      hi = ((hi >> 8) & mask) * alphaScale;
    }
    *dstColor = ((lo >> 8) & mask) | (hi & ~mask);
  }
#    endif
  inline void S32_alpha_D32_filter_DX(const SkBitmapProcState& s, const uint32_t* xy, int count, SkPMColor* colors)
  {
    SkASSERT(count > 0 && colors != nullptr);
    SkASSERT(s.fFilterQuality != kNone_SkFilterQuality);
    SkASSERT(4 == s.fPixmap.info().bytesPerPixel());
    SkASSERT(s.fAlphaScale <= 256);
    int y0, y1, wy;
    decode_packed_coordinates_and_weight(*xy++, &y0, &y1, &wy);
    auto row0 = (const uint32_t*) ((const char*) s.fPixmap.addr() + y0 * s.fPixmap.rowBytes()), row1;
    while (count-- > 0)
    {
      int x0, x1, wx;
      decode_packed_coordinates_and_weight(*xy++, &x0, &x1, &wx);
      filter_and_scale_by_alpha(wx, wy, row0[x0], row0[x1], row1[x0], row1[x1], colors++, s.fAlphaScale);
    }
  }
#  endif
}
#endif
