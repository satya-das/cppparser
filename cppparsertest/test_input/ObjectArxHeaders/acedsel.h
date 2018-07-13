//
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
// DESCRIPTION: Definition of Selection-related AcEd constructs, which
//              currently consists solely of the AcEdSolidSubentitySelector.
//

#ifndef _ACEDSEL_H
#define _ACEDSEL_H

#include "AcArray.h"
#include "acadstrc.h"   // Acad struct
#include "acgitransient.h"
#pragma pack (push, 8)

class AcDbObjectId;
class AcDbSubentId;
class AcEdSelectedTransientImp;
class AcGsDCRect;

class AcEdSolidSubentitySelector
{
public:
    AcEdSolidSubentitySelector();
    ~AcEdSolidSubentitySelector();

    Acad::ErrorStatus selectFaces(AcDbObjectId& selectedSolidId, 
        AcArray<AcDbSubentId *>& faceSet);
};

class AcEdSelectedTransient
{
public:
    AcEdSelectedTransient();
    AcEdSelectedTransient(const AcEdSelectedTransient& source);
    AcEdSelectedTransient& operator=(const AcEdSelectedTransient& source);
    ~AcEdSelectedTransient();

    AcGiDrawable* parent();
    AcGiDrawable* drawable();
    Adesk::GsMarker marker();
    AcGiTransientDrawingMode mode();
    int subDrawingMode();

protected:
    AcEdSelectedTransientImp* mImp;
    friend class AcEdTransientSelectionInternals;
};

//This function returns all transients that draw any geometry inside the pickbox. 
Acad::ErrorStatus acedSelectTransients(const AcGsDCRect& rect,
                                       int viewportNumber,
                                       AcArray<AcEdSelectedTransient>& result);


#pragma pack (pop)
#endif // _ACEDSEL_H
