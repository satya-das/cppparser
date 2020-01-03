/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkCanvasVirtualEnforcer_DEFINED
#  define SkCanvasVirtualEnforcer_DEFINED
#  include "include/core/SkCanvas.h"
// If you would ordinarily want to inherit from Base (eg SkCanvas, SkNWayCanvas), instead
// inherit from SkCanvasVirtualEnforcer<Base>, which will make the build fail if you forget
// to override one of SkCanvas' key virtual hooks.
template <typename Base>
class SkCanvasVirtualEnforcer : public Base
{
  using Base::Base;
protected:
  virtual void onDrawPaint(const SkPaint& paint) = 0;
  void onDrawBehind(const SkPaint&) override
  {
  }
  virtual void onDrawRect(const SkRect& rect, const SkPaint& paint) = 0;
  virtual void onDrawRRect(const SkRRect& rrect, const SkPaint& paint) = 0;
  virtual void onDrawDRRect(const SkRRect& outer, const SkRRect& inner, const SkPaint& paint) = 0;
  virtual void onDrawOval(const SkRect& rect, const SkPaint& paint) = 0;
  virtual void onDrawArc(const SkRect& rect, SkScalar startAngle, SkScalar sweepAngle, bool useCenter, const SkPaint& paint) = 0;
  virtual void onDrawPath(const SkPath& path, const SkPaint& paint) = 0;
  virtual void onDrawRegion(const SkRegion& region, const SkPaint& paint) = 0;
  virtual void onDrawTextBlob(const SkTextBlob* blob, SkScalar x, SkScalar y, const SkPaint& paint) = 0;
  virtual void onDrawPatch(const SkPoint cubics[12], const SkColor colors[4], const SkPoint texCoords[4], SkBlendMode mode, const SkPaint& paint) = 0;
  virtual void onDrawPoints(SkCanvas::PointMode mode, size_t count, const SkPoint pts[], const SkPaint& paint) = 0;
  virtual void onDrawVerticesObject(const SkVertices*, const SkVertices::Bone bones[], int boneCount, SkBlendMode, const SkPaint&) = 0;
  virtual void onDrawImage(const SkImage* image, SkScalar dx, SkScalar dy, const SkPaint* paint) = 0;
  virtual void onDrawImageRect(const SkImage* image, const SkRect* src, const SkRect& dst, const SkPaint* paint, SkCanvas::SrcRectConstraint constraint) = 0;
  virtual void onDrawImageNine(const SkImage* image, const SkIRect& center, const SkRect& dst, const SkPaint* paint) = 0;
  virtual void onDrawImageLattice(const SkImage* image, const SkCanvas::Lattice& lattice, const SkRect& dst, const SkPaint* paint) = 0;
#  ifdef SK_BUILD_FOR_ANDROID_FRAMEWORK
    // This is under active development for Chrome and not used in Android. Hold off on adding
    // implementations in Android's SkCanvas subclasses until this stabilizes.
  void onDrawEdgeAAQuad(const SkRect& rect, const SkPoint clip[4], SkCanvas::QuadAAFlags aaFlags, const SkColor4f& color, SkBlendMode mode) override
  {
  }
  void onDrawEdgeAAImageSet(const SkCanvas::ImageSetEntry imageSet[], int count, const SkPoint dstClips[], const SkMatrix preViewMatrices[], const SkPaint* paint, SkCanvas::SrcRectConstraint constraint) override
  {
  }
#  else 
  virtual void onDrawEdgeAAQuad(const SkRect& rect, const SkPoint clip[4], SkCanvas::QuadAAFlags aaFlags, const SkColor4f& color, SkBlendMode mode) = 0;
  virtual void onDrawEdgeAAImageSet(const SkCanvas::ImageSetEntry imageSet[], int count, const SkPoint dstClips[], const SkMatrix preViewMatrices[], const SkPaint* paint, SkCanvas::SrcRectConstraint constraint) = 0;
#  endif
  virtual void onDrawBitmap(const SkBitmap& bitmap, SkScalar dx, SkScalar dy, const SkPaint* paint) = 0;
  virtual void onDrawBitmapRect(const SkBitmap& bitmap, const SkRect* src, const SkRect& dst, const SkPaint* paint, SkCanvas::SrcRectConstraint constraint) = 0;
  virtual void onDrawBitmapNine(const SkBitmap& bitmap, const SkIRect& center, const SkRect& dst, const SkPaint* paint) = 0;
  virtual void onDrawBitmapLattice(const SkBitmap& bitmap, const SkCanvas::Lattice& lattice, const SkRect& dst, const SkPaint* paint) = 0;
  virtual void onDrawAtlas(const SkImage* atlas, const SkRSXform xform[], const SkRect rect[], const SkColor colors[], int count, SkBlendMode mode, const SkRect* cull, const SkPaint* paint) = 0;
  virtual void onDrawAnnotation(const SkRect& rect, const char key[], SkData* value) = 0;
  virtual void onDrawShadowRec(const SkPath&, const SkDrawShadowRec&) = 0;
  virtual void onDrawDrawable(SkDrawable* drawable, const SkMatrix* matrix) = 0;
  virtual void onDrawPicture(const SkPicture* picture, const SkMatrix* matrix, const SkPaint* paint) = 0;
};
#endif
