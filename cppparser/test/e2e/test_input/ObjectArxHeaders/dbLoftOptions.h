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
// The AcDbSurface class is the interface class for representing
// ASM surfaces inside AutoCAD.  

#pragma once

#ifndef DBLOFTOPTIONS_H
#define DBLOFTOPTIONS_H

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"

#pragma pack(push, 8)


// Utility class for setting options used by createLoftedSurface().
class AcDbLoftOptions
{
public:
    AcDbLoftOptions ();
    AcDbLoftOptions ( const AcDbLoftOptions& src );
    ~AcDbLoftOptions ();

    // Assignment operator.
    AcDbLoftOptions& operator = ( const AcDbLoftOptions& src );
    bool             operator == (const AcDbLoftOptions&) const;

    enum NormalOption {
            kNoNormal,
            kFirstNormal,
            kLastNormal,
            kEndsNormal,
            kAllNormal,
            kUseDraftAngles
    };

    // Get/set start draft angle.
    double  draftStart () const;
    void  setDraftStart ( double ang );

    // Get/set end draft angle.
    double  draftEnd () const;
    void  setDraftEnd ( double ang );

    // Get/set start draft magnitude.
    double  draftStartMag () const;
    void  setDraftStartMag ( double val );

    // Get/set end draft magnitude.
    double  draftEndMag () const;
    void  setDraftEndMag ( double val );

    // Get/set arc-length parameterization.
    bool  arcLengthParam () const;
    void  setArcLengthParam ( bool val );

    // Get/set twist option.
    bool  noTwist () const;
    void  setNoTwist ( bool val );

    // Get/set align option.
    bool  alignDirection () const;
    void  setAlignDirection ( bool val );

    // Get/set simplify option.
    bool  simplify () const;
    void  setSimplify ( bool val );

    // Get/set closed option.
    bool  closed () const;
    void  setClosed ( bool val );

    // Get/set periodic option.
    bool  periodic () const;
    void  setPeriodic ( bool val );

    // Get/set ruled option.
    bool  ruled () const;
    void  setRuled ( bool val );

    // Get/set virtual guide option.
    bool  virtualGuide () const;
    void  setVirtualGuide ( bool val );

    // Get/set plane normal option.
    AcDbLoftOptions::NormalOption  normal () const;
    void  setNormal ( AcDbLoftOptions::NormalOption val );

    // Set loft options from current values of system variables.
    Acad::ErrorStatus  setOptionsFromSysvars ();

    // Set system variables from loft options.
    Acad::ErrorStatus  setSysvarsFromOptions ();

    // Check for valid combinations of options.
    Acad::ErrorStatus  checkOptions ( bool displayErrorMessages = false  );

    // Utility functions.
    Acad::ErrorStatus checkLoftCurves (
        AcArray<AcDbEntity*>& crossSectionCurves,
        AcArray<AcDbEntity*>& guideCurves,
        AcDbEntity* pPathCurve,
        bool& allOpen, bool& allClosed, bool& allPlanar,
        bool displayErrorMessages = false );
    Acad::ErrorStatus checkCrossSectionCurves (
        AcArray<AcDbEntity*>& crossSectionCurves,
        bool& allOpen, bool& allClosed, bool& allPlanar,
        bool displayErrorMessages = false );
    Acad::ErrorStatus checkGuideCurves ( AcArray<AcDbEntity*>& guideCurves,
                                         bool displayErrorMessages = false );
    Acad::ErrorStatus checkPathCurve ( AcDbEntity *pPathCurve,
                                       bool displayErrorMessages = false );

private:
    void *mpImpLoftOptions;
    friend class AcDbImpLoftOptions;
};

#pragma pack(pop)

#endif // DBLOFTOPTIONS_H
