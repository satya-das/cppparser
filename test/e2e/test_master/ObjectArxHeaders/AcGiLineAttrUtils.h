//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "acdb.h"
class AcGiLineAttrUtils
{
public:
  static char acgiLineWeightToIndex(AcDb::LineWeight lw);
  static AcDb::LineWeight acgiIndexToLineWeight(char index);
};
