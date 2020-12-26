/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkOpAngle_DEFINED
#  define SkOpAngle_DEFINED
#  include "src/pathops/SkLineParameters.h"
#  include "src/pathops/SkPathOpsCurve.h"
#  if  DEBUG_ANGLE
#    include "include/core/SkString.h"
#  endif
class SkOpContour;
class SkOpPtT;
class SkOpSegment;
class SkOpSpanBase;
class SkOpSpan;
class SkOpAngle
{
public:
  enum IncludeType {
        kUnaryWinding,
        kUnaryXor,
        kBinarySingle,
        kBinaryOpp,
    };
  const SkOpAngle* debugAngle(int id) const;
  const SkOpCoincidence* debugCoincidence() const;
  SkOpContour* debugContour(int id) const;
  int debugID() const
  {
        return SkDEBUGRELEASE(fID, -1);
    }
#  if  DEBUG_SORT
  void debugLoop() const;
#  endif
#  if  DEBUG_ANGLE
  bool debugCheckCoincidence() const
  { return fCheckCoincidence; }
  void debugCheckNearCoincidence() const;
  SkString debugPart() const;
#  endif
  const SkOpPtT* debugPtT(int id) const;
  const SkOpSegment* debugSegment(int id) const;
  int debugSign() const;
  const SkOpSpanBase* debugSpan(int id) const;
  void debugValidate() const;
  void debugValidateNext() const;
  double distEndRatio(double dist) const;
    // available to testing only
  void dump() const;
  void dumpCurves() const;
  void dumpLoop() const;
  void dumpOne(bool functionHeader) const;
  void dumpTo(const SkOpSegment* fromSeg, const SkOpAngle*) const;
  void dumpTest() const;
  SkOpSpanBase* end() const
  {
        return fEnd;
    }
  bool insert(SkOpAngle*);
  SkOpSpanBase* lastMarked() const;
  bool loopContains(const SkOpAngle*) const;
  int loopCount() const;
  SkOpAngle* next() const
  {
        return fNext;
    }
  SkOpAngle* previous() const;
  SkOpSegment* segment() const;
  void set(SkOpSpanBase* start, SkOpSpanBase* end);
  void setLastMarked(SkOpSpanBase* marked)
  {
        fLastMarked = marked;
    }
  SkOpSpanBase* start() const
  {
        return fStart;
    }
  SkOpSpan* starter();
  bool tangentsAmbiguous() const
  {
        return fTangentsAmbiguous;
    }
  bool unorderable() const
  {
        return fUnorderable;
    }
private:
  bool after(SkOpAngle* test);
  void alignmentSameSide(const SkOpAngle* test, int* order) const;
  bool checkCrossesZero() const;
  bool checkParallel(SkOpAngle*);
  bool computeSector();
  int convexHullOverlaps(const SkOpAngle*);
  bool endToSide(const SkOpAngle* rh, bool* inside) const;
  bool endsIntersect(SkOpAngle*);
  int findSector(SkPath::Verb verb, double x, double y) const;
  SkOpGlobalState* globalState() const;
  int lineOnOneSide(const SkDPoint& origin, const SkDVector& line, const SkOpAngle* test, bool useOriginal) const;
  int lineOnOneSide(const SkOpAngle* test, bool useOriginal);
  int linesOnOriginalSide(const SkOpAngle* test);
  bool merge(SkOpAngle*);
  double midT() const;
  bool midToSide(const SkOpAngle* rh, bool* inside) const;
  bool oppositePlanes(const SkOpAngle* rh) const;
  int orderable(SkOpAngle* rh);
  void setSector();
  void setSpans();
  bool tangentsDiverge(const SkOpAngle* rh, double s0xt0);
  SkDCurve fOriginalCurvePart;
  SkDCurveSweep fPart;
  double fSide;
  SkLineParameters fTangentHalf;
  SkOpAngle* fNext;
  SkOpSpanBase* fLastMarked;
  SkOpSpanBase* fStart;
  SkOpSpanBase* fEnd;
  SkOpSpanBase* fComputedEnd;
  int fSectorMask;
  int8_t fSectorStart;
  int8_t fSectorEnd;
  bool fUnorderable;
  bool fComputeSector;
  bool fComputedSector;
  bool fCheckCoincidence;
  bool fTangentsAmbiguous;
  friend class PathOpsAngleTester;
};
#endif
