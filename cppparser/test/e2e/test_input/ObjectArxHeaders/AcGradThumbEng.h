//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// 
//  DESCRIPTION:  Definition of CAcGradientThumbEngine
//                
//

#ifndef     _ACGRADTHUMB_H
#define     _ACGRADTHUMB_H

#include "dbcolor.h"

// CAcGradientThumbnailEngine defines the interface to the gradient thumbnail generation engine.
//
// Use the function createGradientThumbnailEngine() to get a pointer to an instace of the engine.
//
// When finished with the engine the pointer returned by createGradientThumbnailEngine() should be deleted
//
class CAcGradientThumbnailEngine
{
    public:
        virtual ~CAcGradientThumbnailEngine() {};

        virtual Acad::ErrorStatus gradientThumbnailsSetRotation( double angle ) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsSetShift( bool bShifted ) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsSetStartColor( AcCmEntityColor startColor ) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsSetStopColor( AcCmEntityColor stopColor ) = 0;

        virtual Acad::ErrorStatus gradientThumbnailsRender(void) = 0;
        virtual Acad::ErrorStatus gradientThumbnailsDrawBitmap( int gradientNumber, HDC hDC, int xPos, int yPos ) = 0;

};

ACCORE_PORT CAcGradientThumbnailEngine *createGradientThumbnailEngine();


#endif // _ACGRADTHUMB_H
