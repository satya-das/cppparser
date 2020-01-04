/*
 * Copyright 2019 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrSamplePatternDictionary_DEFINED
#  define GrSamplePatternDictionary_DEFINED
#  include "include/core/SkPoint.h"
#  include "include/private/SkTArray.h"
#  include <map>
class GrSamplePatternDictionary
{
public:
  static int kInvalidSamplePatternKey = -1;
  int findOrAssignSamplePatternKey(const SkTArray<SkPoint>& sampleLocations);
  const SkTArray<SkPoint>& retrieveSampleLocations(int samplePatternKey) const
  {
    return *fSampleLocationsArray[samplePatternKey];
  }
private:
  struct LessThan
  {
    bool operator()(const SkTArray<SkPoint>&, const SkTArray<SkPoint>&) const;
  };
  std::map<SkTArray<SkPoint>, int, LessThan> fSamplePatternKeyMap;
  SkTArray<const SkTArray<SkPoint>*> fSampleLocationsArray;
};
#endif
