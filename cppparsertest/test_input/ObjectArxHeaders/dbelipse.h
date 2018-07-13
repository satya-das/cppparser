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
// The AcDbEllipse class represents both a full ellipse and an elliptical
// arc. The parametrization of the ellipse is the vector equation
//
//         P(O) = A * cos(O) + B * sin(O)
// 
// where A and B are the semi major and minor axes respectively.

#ifndef GEOMENT_DBELIPSE_H
#define GEOMENT_DBELIPSE_H
#include "gegbl.h"
#include "dbmain.h"
#include "dbcurve.h"

#pragma pack(push, 8)

class AcDbEllipse: public  AcDbCurve
{
public:
    AcDbEllipse();
    AcDbEllipse(const AcGePoint3d&  center,
                const AcGeVector3d& unitNormal,
                const AcGeVector3d& majorAxis,
                double              radiusRatio,
                double              startAngle = 0.0,
                double              endAngle   = 6.28318530717958647692);
    virtual ~AcDbEllipse();
    ACDB_DECLARE_MEMBERS(AcDbEllipse);

    AcGePoint3d center() const;
    Acad::ErrorStatus setCenter(const AcGePoint3d& center);

    AcGeVector3d normal() const;
    AcGeVector3d majorAxis() const;
    AcGeVector3d minorAxis() const;
    ACDBCORE2D_PORT double majorRadius() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setMajorRadius(double);
    ACDBCORE2D_PORT double minorRadius() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setMinorRadius(double);

    double radiusRatio() const;
    Acad::ErrorStatus setRadiusRatio(double ratio);

    double startAngle() const;
    Acad::ErrorStatus setStartAngle(double startAngle);    

    double endAngle() const;
    Acad::ErrorStatus setEndAngle(double endAngle);

    Acad::ErrorStatus setStartParam(double startParam);
    Acad::ErrorStatus setEndParam(double endParam);

    double paramAtAngle(double angle) const;
    double angleAtParam(double param) const;

    Acad::ErrorStatus get(AcGePoint3d& center, AcGeVector3d& unitNormal,
        AcGeVector3d& majorAxis, double& radiusRatio, double& startAngle,
        double& endAngle) const;

    Acad::ErrorStatus set(const AcGePoint3d& center,
        const AcGeVector3d& unitNormal, const AcGeVector3d& majorAxis,
        double radiusRatio, double startAngle = 0.0,
        double endAngle = 6.28318530717958647692);

    Adesk::Boolean isNull() const;
  
    DBCURVE_METHODS

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;

};

#pragma pack(pop)

#endif
