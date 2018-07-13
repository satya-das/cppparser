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
// DESCRIPTION: API Abstract class for "Curve" entities.

#ifndef AD_DBCURVE_H
#define AD_DBCURVE_H

#include "dbmain.h"
#include "gept3dar.h"
#include "gedblar.h"
#include "geplane.h"
#include "dbptrar.h"

class AcDbSpline;

#pragma pack(push, 8)

class ADESK_NO_VTABLE AcDbCurve: public AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbCurve);

    virtual ~AcDbCurve();

    // Curve property tests.
    //
    virtual Adesk::Boolean    isClosed     () const;      
    virtual Adesk::Boolean    isPeriodic   () const;      

    // Get planar and start/end geometric properties.
    //
    virtual Acad::ErrorStatus getStartParam(double&) const;
    virtual Acad::ErrorStatus getEndParam  (double&) const;
    virtual Acad::ErrorStatus getStartPoint(AcGePoint3d&) const;
    virtual Acad::ErrorStatus getEndPoint  (AcGePoint3d&) const;

    // Conversions to/from parametric/world/distance.
    //
    virtual Acad::ErrorStatus getPointAtParam(double, AcGePoint3d&) const;
    virtual Acad::ErrorStatus getParamAtPoint(const AcGePoint3d&, double&)const;
    virtual Acad::ErrorStatus getDistAtParam (double param, double& dist) const;
    virtual Acad::ErrorStatus getParamAtDist (double dist, double& param) const;
    virtual Acad::ErrorStatus getDistAtPoint (const AcGePoint3d&, double&)const;
    virtual Acad::ErrorStatus getPointAtDist (double, AcGePoint3d&) const;

    // Derivative information.
    //
    virtual Acad::ErrorStatus getFirstDeriv  (double param,
                                              AcGeVector3d& firstDeriv) const;
    virtual Acad::ErrorStatus getFirstDeriv  (const AcGePoint3d&,
                                              AcGeVector3d& firstDeriv) const;
    virtual Acad::ErrorStatus getSecondDeriv (double param,
                                              AcGeVector3d& secDeriv) const;
    virtual Acad::ErrorStatus getSecondDeriv (const AcGePoint3d&,
                                              AcGeVector3d& secDeriv) const;

    // Closest point on curve.
    //
    virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d& givenPnt,
                                                AcGePoint3d& pointOnCurve,
                                                Adesk::Boolean extend
                                                = Adesk::kFalse) const;
    virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d& givenPnt,
                                                const AcGeVector3d& direction,
                                                AcGePoint3d& pointOnCurve,
                                                Adesk::Boolean extend
                                                = Adesk::kFalse) const;

    // Get a projected copy of the curve.
    //
    virtual Acad::ErrorStatus getOrthoProjectedCurve(const AcGePlane&,
                                                AcDbCurve*& projCrv) const;
    virtual Acad::ErrorStatus getProjectedCurve(const AcGePlane&,
                                                const AcGeVector3d& projDir,
                                                AcDbCurve*& projCrv) const;

    // Get offset, spline and split copies of the curve.
    //
    virtual Acad::ErrorStatus getOffsetCurves(double offsetDist,
                                          AcDbVoidPtrArray& offsetCurves) const;
    virtual Acad::ErrorStatus getOffsetCurvesGivenPlaneNormal(
        const AcGeVector3d& normal, double offsetDist,
        AcDbVoidPtrArray& offsetCurves) const;
    virtual Acad::ErrorStatus getSpline      (AcDbSpline*& spline) const;
    virtual Acad::ErrorStatus getSplitCurves (const AcGeDoubleArray& params,
                                         AcDbVoidPtrArray& curveSegments) const;
    virtual Acad::ErrorStatus getSplitCurves (const AcGePoint3dArray& points,
                                         AcDbVoidPtrArray& curveSegments) const;

    // Extend the curve.
    //
    virtual Acad::ErrorStatus extend(double newParam);
    virtual Acad::ErrorStatus extend(Adesk::Boolean extendStart,
                                     const AcGePoint3d& toPoint);

    // Area calculation.
    //
    virtual Acad::ErrorStatus getArea(double&) const;

    // Reverse the curve.
    //
    virtual Acad::ErrorStatus reverseCurve();

    /// <summary>
    /// This function returns an AcGeCurve3d that is geometrically identical to
    /// this AcDbCurve.
    /// </summary>
    /// <param name="pGeCurve">Output pointer to an AcGeCurve3d object that is
    /// geometrically identical to this AcDbCurve.  The caller of this function
    /// is responsible for deleting this AcGeCurve3d object.</param>
    /// <param name="tol">Optional input tolerance.</param>
    /// <returns>Returns eOk if successful.</returns>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus  getAcGeCurve ( AcGeCurve3d*& pGeCurve,
                                                        const AcGeTol& tol = AcGeContext::gTol ) const;

    /// <summary>
    /// This function takes an AcGeCurve3d and returns an AcDbCurve that is
    /// geometrically identical to the AcGeCurve3d.
    /// </summary>
    /// <param name="geCurve">Input reference to an AcGeCurve3d.</param>
    /// <param name="pDbCurve">Output pointer to an AcDbCurve object that is
    /// geometrically identical to geCurve.  The caller of this function is
    /// responsible for deleting this AcDbCurve object or adding it to the
    /// database.</param>
    /// <param name="normal">Optional normal vector.  If this parameter is 
    /// supplied then it must be a valid vector that is perpendicular to the
    /// input geCurve, and this vector will become the normal vector of
    /// the output pDbCurve.  If this parameter is not supplied, then this
    /// function will compute the normal vector itself.</param>
    /// <param name="tol">Optional input tolerance.</param>
    /// <returns>Returns eOk if successful.</returns>
    ACDBCORE2D_PORT static  Acad::ErrorStatus  createFromAcGeCurve ( const AcGeCurve3d& geCurve, AcDbCurve*& pDbCurve,
                                                               AcGeVector3d *normal = NULL,
                                                               const AcGeTol& tol = AcGeContext::gTol );

    /// <summary>
    /// This function takes an AcGeCurve3d and sets this AcDbCurve to be
    /// geometrically identical to the AcGeCurve3d.
    /// </summary>
    /// <param name="geCurve">Input reference to an AcGeCurve3d.</param>
    /// <param name="normal">Optional normal vector.  If this parameter is 
    /// supplied then it must be a valid vector that is perpendicular to the
    /// input geCurve, and this vector will become the normal vector of
    /// the output pDbCurve.  If this parameter is not supplied, then this
    /// function will compute the normal vector itself.</param>
    /// <param name="tol">Optional input tolerance.</param>
    /// <returns>Returns eOk if successful.</returns>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus  setFromAcGeCurve ( const AcGeCurve3d& geCurve,
                                                            AcGeVector3d *normal = NULL,
                                                            const AcGeTol& tol = AcGeContext::gTol );

protected:
    AcDbCurve();
};

// Protocols of AcDbCurve available in macro from.

#define DBCURVE_METHODS \
virtual Adesk::Boolean isClosed() const ADESK_OVERRIDE; \
virtual Adesk::Boolean isPeriodic() const ADESK_OVERRIDE; \
virtual Adesk::Boolean isPlanar() const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getStartParam(double&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getEndParam(double&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getStartPoint(AcGePoint3d&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getEndPoint(AcGePoint3d&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getPointAtParam(double, AcGePoint3d&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getParamAtPoint(const AcGePoint3d&, double&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getDistAtParam(double, double&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getParamAtDist(double, double&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getDistAtPoint(const AcGePoint3d&, double&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getPointAtDist(double, AcGePoint3d&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getFirstDeriv(double, AcGeVector3d&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getFirstDeriv(const AcGePoint3d&,AcGeVector3d&)const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getSecondDeriv(double, AcGeVector3d&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getSecondDeriv(const AcGePoint3d&, \
                              AcGeVector3d&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d&, AcGePoint3d&, \
                              Adesk::Boolean = Adesk::kFalse) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getClosestPointTo(const AcGePoint3d&, \
                              const AcGeVector3d&, AcGePoint3d&, \
                              Adesk::Boolean = Adesk::kFalse) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getOrthoProjectedCurve(const AcGePlane&, \
                              AcDbCurve*&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getProjectedCurve(const AcGePlane&, \
                              const AcGeVector3d&, AcDbCurve*&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getOffsetCurves(double, AcDbVoidPtrArray&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getSpline(AcDbSpline*&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getSplitCurves(const AcGeDoubleArray&, \
                              AcDbVoidPtrArray& curveSegments) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getSplitCurves(const AcGePoint3dArray&, \
                              AcDbVoidPtrArray&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus extend(double) ADESK_OVERRIDE; \
virtual Acad::ErrorStatus extend(Adesk::Boolean, const AcGePoint3d&) ADESK_OVERRIDE; \
virtual Acad::ErrorStatus getArea(double&) const ADESK_OVERRIDE; \
virtual Acad::ErrorStatus reverseCurve() ADESK_OVERRIDE; \
ACDBCORE2D_PORT virtual Acad::ErrorStatus getAcGeCurve ( AcGeCurve3d*& pGeCurve, \
                                                   const AcGeTol& tol = AcGeContext::gTol ) const ADESK_OVERRIDE; \
ACDBCORE2D_PORT virtual Acad::ErrorStatus setFromAcGeCurve ( const AcGeCurve3d& geCurve, \
                                                       AcGeVector3d *normal = NULL, \
                                                       const AcGeTol& tol = AcGeContext::gTol ) ADESK_OVERRIDE;

#pragma pack(pop)

#endif
