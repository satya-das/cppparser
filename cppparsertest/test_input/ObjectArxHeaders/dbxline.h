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
// DESCRIPTION: Exported AcDbXline Entity class

#ifndef AD_DBXLINE_H
#define AD_DBXLINE_H 1

#include "dbmain.h"
#include "dbcurve.h"

#pragma pack(push, 8)

class AcGePoint3d;
class AcGeVector3d;

class AcDbXline: public AcDbCurve
{
public:
    AcDbXline();
    ~AcDbXline();
    ACDB_DECLARE_MEMBERS(AcDbXline);
    DBCURVE_METHODS

    Acad::ErrorStatus getOffsetCurvesGivenPlaneNormal(
        const AcGeVector3d& normal, double offsetDist,
        AcDbVoidPtrArray& offsetCurves) const override;
    
    AcGePoint3d  basePoint() const;
    void         setBasePoint(const AcGePoint3d& pt); 

    AcGeVector3d unitDir() const;
    void         setUnitDir(const AcGeVector3d& vec);

    ACDBCORE2D_PORT AcGePoint3d               secondPoint() const;
    ACDBCORE2D_PORT Acad::ErrorStatus		setSecondPoint(AcGePoint3d const & pt);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

inline Adesk::Boolean AcDbXline::isClosed() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbXline::isPeriodic() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbXline::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbXline::getStartParam(double&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getEndParam(double&) const
{
    // endParam for an Xline is positive infinity
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getStartPoint(AcGePoint3d&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getEndPoint(AcGePoint3d&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getSpline(AcDbSpline*&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::extend(double /*newParam*/)
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::extend(Adesk::Boolean, const AcGePoint3d&)
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbXline::getArea(double&) const
{
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif

