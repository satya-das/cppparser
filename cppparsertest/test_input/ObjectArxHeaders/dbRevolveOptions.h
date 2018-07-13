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
// DESCRIPTION:
//
// The AcDbRevolveOptions class is used for setting options that are
// passed to createRevolvedSurface() and revolveFace().  

#pragma once
#ifndef DBREVOLVEOPTIONS_H
#define DBREVOLVEOPTIONS_H

#include "dbmain.h"
#include "gepnt3d.h"
#include "gevec3d.h"

#pragma pack(push, 8)


// Utility class for setting options used by createRevolvedSurface().
class AcDbRevolveOptions
{
public:
    AcDbRevolveOptions ();
    AcDbRevolveOptions ( const AcDbRevolveOptions& src );
    ~AcDbRevolveOptions ();

    // Assignment operator.
    AcDbRevolveOptions& operator = ( const AcDbRevolveOptions& src );

    // Get/set draft angle.
    double  draftAngle () const;
    void  setDraftAngle ( double ang );

    // Get/set twist angle.
    double  twistAngle () const;
    void  setTwistAngle ( double ang );

    // Get/set close to axis option.
    bool  closeToAxis () const;
    void  setCloseToAxis ( bool val );

    // Utility functions.
    Acad::ErrorStatus  checkRevolveCurve ( AcDbEntity* pRevEnt,
        const AcGePoint3d& axisPnt, const AcGeVector3d& axisDir,
        bool& closed, bool& endPointsOnAxis, bool& planar,
        bool displayErrorMessages = false );

private:
    void *mpImpRevolveOptions;
    friend class AcDbImpRevolveOptions;
};
#pragma pack(pop)

#endif // DBREVOLVEOPTIONS_H
