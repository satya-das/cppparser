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
//
// DESCRIPTION:
//
// The AcDbSweepOptions class is used for setting options that are
// passed to createSweptSurface() and sweepFace().  

#pragma once
#ifndef DBSWEEPOPTIONS_H
#define DBSWEEPOPTIONS_H

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"

#pragma pack(push, 8)


// Utility class for setting options used by createSweptSurface().
class AcDbSweepOptions
{
public:
    AcDbSweepOptions ();
    AcDbSweepOptions ( const AcDbSweepOptions& src );
    ~AcDbSweepOptions ();

    // Assignment operator.
    AcDbSweepOptions& operator = ( const AcDbSweepOptions& src );
    bool              operator == (const AcDbSweepOptions&) const;

    enum AlignOption {
            kNoAlignment,
            kAlignSweepEntityToPath,
            kTranslateSweepEntityToPath,
            kTranslatePathToSweepEntity
            
    };

    enum MiterOption {
            kDefaultMiter,
            kOldMiter,
            kNewMiter,
            kCrimpMiter,
            kBendMiter
    };

    // Get/set draft angle.
    double  draftAngle () const;
    void  setDraftAngle ( double ang );

    // Get/set start draft distance.
    double  startDraftDist () const;
    void  setStartDraftDist ( double val );

    // Get/set end draft distance.
    double  endDraftDist () const;
    void  setEndDraftDist ( double val );

    // Get/set twist angle.
    double  twistAngle () const;
    void  setTwistAngle ( double ang );

    // Get/set scale factor.
    double  scaleFactor () const;
    void  setScaleFactor ( double val );

    // Get/set align angle.
    double  alignAngle () const;
    void  setAlignAngle ( double ang );

    // Get/set align option.
    AcDbSweepOptions::AlignOption  align () const;
    void  setAlign ( AcDbSweepOptions::AlignOption val );

    // Get/set miter option.
    AcDbSweepOptions::MiterOption  miterOption () const;
    void  setMiterOption ( AcDbSweepOptions::MiterOption val );

    // Get/set whether to align to start or end of curve.
    bool  alignStart () const;
    void  setAlignStart ( bool val );

    // Get/set base point for alignment.
    AcGePoint3d  basePoint () const;
    void  setBasePoint ( AcGePoint3d& pnt );

    // Get/set bank option.
    bool  bank () const;
    void  setBank ( bool val );

    // Get/set self-intersection check option.
    // Warning: turning off this check may result in the creation of
    // a self-intersecting surface or solid.
    bool  checkIntersections () const;
    void  setCheckIntersections ( bool val );

    // Get/set reference vector for controlling twist.
    AcGeVector3d  twistRefVec () const;
    void  setTwistRefVec ( const AcGeVector3d& vec );

    // Get/set coordinate system for sweep entity.
    bool  getSweepEntityTransform ( AcGeMatrix3d& mat );
    void  setSweepEntityTransform ( AcGeMatrix3d& mat ); 
    Acad::ErrorStatus  setSweepEntityTransform ( AcArray<AcDbEntity*>& sweepEntities,
                                                 bool displayErrorMessages = false );

    // Get/set coordinate system at start/end of path curve.  If path entity transform is
    // computed from the path entity geometry (by calling the second
    // setPathEntityTransform() below), then the sweep entity transform should be
    // set before making this call.
    bool  getPathEntityTransform ( AcGeMatrix3d& mat );
    void  setPathEntityTransform ( AcGeMatrix3d& mat ); 
    Acad::ErrorStatus  setPathEntityTransform ( AcDbEntity *pPathEnt,
                                                bool displayErrorMessages = false );

    // Check for valid sweep entity.  Returns planarity of input entity.
    // If planarity is kPlanar, then pnt and vec will be set to a point on the
    // plane and the plane normal of the entity.  If planarity is kLinear, then
    // pnt and vec will be set to a point on the line and the line direction of
    // the entity.
    Acad::ErrorStatus  checkSweepCurve ( AcDbEntity *pSweepEnt,
        AcDb::Planarity& planarity, AcGePoint3d& pnt, AcGeVector3d& vec,
        bool& closed, double& approxArcLen, bool displayErrorMessages = false );

    // Check for valid path entity.
    Acad::ErrorStatus  checkPathCurve ( AcDbEntity *pPathEnt,
                                        bool displayErrorMessages = false );

private:
    void *mpImpSweepOptions;
    friend class AcDbImpSweepOptions;
};
#pragma pack(pop)

#endif // DBSWEEPOPTIONS_H
