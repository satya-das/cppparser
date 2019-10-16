//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACGRADTHUMB_H
#  define _ACGRADTHUMB_H
#  include "dbcolor.h"
class CAcGradientThumbnailEngine
{
public:
  virtual ~CAcGradientThumbnailEngine()
  {
  }
  virtual Acad::ErrorStatus gradientThumbnailsSetRotation(double angle) = 0;
  virtual Acad::ErrorStatus gradientThumbnailsSetShift(bool bShifted) = 0;
  virtual Acad::ErrorStatus gradientThumbnailsSetStartColor(AcCmEntityColor startColor) = 0;
  virtual Acad::ErrorStatus gradientThumbnailsSetStopColor(AcCmEntityColor stopColor) = 0;
  virtual Acad::ErrorStatus gradientThumbnailsRender(void) = 0;
  virtual Acad::ErrorStatus gradientThumbnailsDrawBitmap(int gradientNumber, HDC hDC, int xPos, int yPos) = 0;
};
ACCORE_PORT CAcGradientThumbnailEngine* createGradientThumbnailEngine();
#endif
