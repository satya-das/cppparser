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

//
// This API extends AcGi to support transient.
//

#pragma once

#include "AcArray.h"

typedef enum{
    kAcGiMain = 0,
    kAcGiSprite,
    kAcGiDirectShortTerm,
    kAcGiHighlight,
    kAcGiDirectTopmost,
    kAcGiContrast,
    kAcGiDrawingModeCount
} AcGiTransientDrawingMode;
class AcGiDrawable;

class AcGiTransientManager
{
public:
    virtual             ~AcGiTransientManager   (void) { }

    virtual bool        addTransient            (AcGiDrawable* pDrawable,
                                                 AcGiTransientDrawingMode mode,
                                                 int subDrawingMode,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual bool        eraseTransient          (AcGiDrawable* pDrawable,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual bool        eraseTransients         (AcGiTransientDrawingMode mode,
                                                 int subDrawingMode,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual void        updateTransient         (AcGiDrawable* pDrawable,
                                                 const AcArray<int>& viewportNumbers)    = 0;

    virtual bool        addChildTransient       (AcGiDrawable * pDrawable, 
                                                 AcGiDrawable * pParentDrawable)         = 0;

    virtual bool        eraseChildTransient     (AcGiDrawable * pDrawable, 
                                                 AcGiDrawable * pParentDrawable)         = 0;

    virtual void        updateChildTransient    (AcGiDrawable * pDrawable, 
                                                 AcGiDrawable * pParentDrawable)         = 0; 

    virtual int         getFreeSubDrawingMode   (AcGiTransientDrawingMode mode,
                                                 int& subDrawingMode,
                                                 const AcArray<int>& viewportNumbers)    = 0;
};

AcGiTransientManager* acgiGetTransientManager();
void acgiSetTransientManager(AcGiTransientManager* transientManager);
