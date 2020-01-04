/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkColorTable_DEFINED
#  define SkColorTable_DEFINED
#  include "include/core/SkColor.h"
#  include "include/core/SkRefCnt.h"
class SkColorTable : public SkRefCnt
{
public:
    /** Copy up to 256 colors into a new SkColorTable.
     */
  SkColorTable(const SkPMColor colors[], int count);
  ~SkColorTable();
    /** Returns the number of colors in the table.
     */
  int count() const
  {
    return fCount;
  }
    /** Returns the specified color from the table. In the debug build, this asserts that
     *  the index is in range (0 <= index < count).
     */
  SkPMColor operator[](int index) const
  {
    SkASSERT(fColors != nullptr && (unsigned) index < (unsigned) fCount);
    return fColors[index];
  }
    /** Return the array of colors for reading. */
  const SkPMColor* readColors() const
  {
    return fColors;
  }
private:
  SkPMColor* fColors;
  int fCount;
  typedef SkRefCnt INHERITED;
};
#endif
