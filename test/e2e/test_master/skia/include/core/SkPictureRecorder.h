/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPictureRecorder_DEFINED
#  define SkPictureRecorder_DEFINED
#  include "include/core/SkBBHFactory.h"
#  include "include/core/SkPicture.h"
#  include "include/core/SkRefCnt.h"
#  ifdef SK_BUILD_FOR_ANDROID_FRAMEWORK
namespace android
{
  class Picture;
}
#  endif
class GrContext;
class SkCanvas;
class SkDrawable;
class SkMiniRecorder;
class SkPictureRecord;
class SkRecord;
class SkRecorder;
class SK_API SkPictureRecorder
{
public:
  SkPictureRecorder();
  ~SkPictureRecorder();
  enum RecordFlags {
        // If you call drawPicture() or drawDrawable() on the recording canvas, this flag forces
        // that object to playback its contents immediately rather than reffing the object.
        kPlaybackDrawPicture_RecordFlag     = 1 << 0,
  };
  enum FinishFlags {

  };
    /** Returns the canvas that records the drawing commands.
        @param bounds the cull rect used when recording this picture. Any drawing the falls outside
                      of this rect is undefined, and may be drawn or it may not.
        @param bbhFactory factory to create desired acceleration structure
        @param recordFlags optional flags that control recording.
        @return the canvas.
    */
  SkCanvas* beginRecording(const SkRect& bounds, SkBBHFactory* bbhFactory = nullptr, uint32_t recordFlags = 0);
  SkCanvas* beginRecording(SkScalar width, SkScalar height, SkBBHFactory* bbhFactory = nullptr, uint32_t recordFlags = 0)
  {
    return this->beginRecording(SkRect::MakeWH(width, height), bbhFactory, recordFlags);
  }
    /** Returns the recording canvas if one is active, or NULL if recording is
        not active. This does not alter the refcnt on the canvas (if present).
    */
  SkCanvas* getRecordingCanvas();
    /**
     *  Signal that the caller is done recording. This invalidates the canvas returned by
     *  beginRecording/getRecordingCanvas. Ownership of the object is passed to the caller, who
     *  must call unref() when they are done using it.
     *
     *  The returned picture is immutable. If during recording drawables were added to the canvas,
     *  these will have been "drawn" into a recording canvas, so that this resulting picture will
     *  reflect their current state, but will not contain a live reference to the drawables
     *  themselves.
     */
  sk_sp<SkPicture> finishRecordingAsPicture(uint32_t endFlags = 0);
    /**
     *  Signal that the caller is done recording, and update the cull rect to use for bounding
     *  box hierarchy (BBH) generation. The behavior is the same as calling
     *  finishRecordingAsPicture(), except that this method updates the cull rect initially passed
     *  into beginRecording.
     *  @param cullRect the new culling rectangle to use as the overall bound for BBH generation
     *                  and subsequent culling operations.
     *  @return the picture containing the recorded content.
     */
  sk_sp<SkPicture> finishRecordingAsPictureWithCull(const SkRect& cullRect, uint32_t endFlags = 0);
    /**
     *  Signal that the caller is done recording. This invalidates the canvas returned by
     *  beginRecording/getRecordingCanvas. Ownership of the object is passed to the caller, who
     *  must call unref() when they are done using it.
     *
     *  Unlike finishRecordingAsPicture(), which returns an immutable picture, the returned drawable
     *  may contain live references to other drawables (if they were added to the recording canvas)
     *  and therefore this drawable will reflect the current state of those nested drawables anytime
     *  it is drawn or a new picture is snapped from it (by calling drawable->newPictureSnapshot()).
     */
  sk_sp<SkDrawable> finishRecordingAsDrawable(uint32_t endFlags = 0);
private:
  void reset();
    /** Replay the current (partially recorded) operation stream into
        canvas. This call doesn't close the current recording.
    */
#  ifdef SK_BUILD_FOR_ANDROID_FRAMEWORK
  friend class android::Picture;
#  endif
  friend class SkPictureRecorderReplayTester;
  void partialReplay(SkCanvas* canvas) const;
  bool fActivelyRecording;
  uint32_t fFlags;
  SkRect fCullRect;
  sk_sp<SkBBoxHierarchy> fBBH;
  std::unique_ptr<SkRecorder> fRecorder;
  sk_sp<SkRecord> fRecord;
  std::unique_ptr<SkMiniRecorder> fMiniRecorder;
  SkPictureRecorder(SkPictureRecorder&&) = delete;
  SkPictureRecorder& operator=(SkPictureRecorder&&);
};
#endif
