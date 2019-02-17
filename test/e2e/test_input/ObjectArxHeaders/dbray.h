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
// DESCRIPTION: Exported AcDbRay Entity class

#ifndef AD_DBRAY_H
#define AD_DBRAY_H 1

#include "dbmain.h"
#include "dbcurve.h"

#pragma pack(push, 8)

class AcGePoint3d;
class AcGeVector3d;

class AcDbRay: public AcDbCurve
{
public:
    AcDbRay();
    ~AcDbRay();
    ACDB_DECLARE_MEMBERS(AcDbRay);
    DBCURVE_METHODS

    Acad::ErrorStatus getOffsetCurvesGivenPlaneNormal(
        const AcGeVector3d& normal, double offsetDist,
        AcDbVoidPtrArray& offsetCurves) const override;
    
    AcGePoint3d  basePoint() const;
    void         setBasePoint(const AcGePoint3d& pt); 

    AcGeVector3d unitDir() const;
    void         setUnitDir(const AcGeVector3d& vec);

    ACDBCORE2D_PORT AcGePoint3d           secondPoint() const;
    ACDBCORE2D_PORT Acad::ErrorStatus		setSecondPoint(AcGePoint3d const & pt);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

inline Adesk::Boolean AcDbRay::isClosed() const      
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbRay::isPeriodic() const      
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbRay::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbRay::getStartParam(double& startParam) const
{
    startParam = 0.0;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDbRay::getEndParam(double& ) const
{
    // endParam for a Ray is positive infinity
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbRay::getEndPoint(AcGePoint3d& ) const 
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbRay::getSpline(AcDbSpline*& ) const 
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbRay::getArea(double& ) const 
{
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif
