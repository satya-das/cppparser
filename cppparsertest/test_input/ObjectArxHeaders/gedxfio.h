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
// DESCRIPTION:
//
// This file contains the class AcGeDxfIO - an utility class that
// performs DXF file IO.

#ifndef AC_GEDXFIO_H
#define AC_GEDXFIO_H


#include "gefileio.h"
#include "gelibver.h"
#pragma pack (push, 8)

class AcDbDxfFiler;

class
AcGeDxfIO
{
public:

    // Write to file
    //
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeMatrix2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeScale2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint2dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector2dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeMatrix3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeScale3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePoint3dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeVector3dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeTol&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeInterval&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeKnotVector&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeDoubleArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeIntArray&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveBoundary&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePosition2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLine2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLineSeg2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeRay2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCircArc2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipArc2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCubicSplineCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbCurve2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCompositeCurve2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePolyline2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePosition3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePointOnSurface&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLine3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeRay3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeLineSeg3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePlane&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundedPlane&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCircArc3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipArc3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCubicSplineCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbCurve3d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCompositeCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGePolyline3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeAugPolyline3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalCurve3d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCone&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCylinder&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeTorus&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeExternalSurface&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeOffsetSurface&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeNurbSurface&);
    GE_DLLEXPIMPORT static
   Acad::ErrorStatus outFields(AcDbDxfFiler*,const AcGeExternalBoundedSurface&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeSphere&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundBlock2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeBoundBlock3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveCurveInt2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeCurveCurveInt3d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus outFields(AcDbDxfFiler*, const AcGeEllipCone&);

    // Read from file
    //
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeMatrix2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeScale2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint2dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector2dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeMatrix3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeScale3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePoint3dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeVector3dArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeTol&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeInterval&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeKnotVector&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeDoubleArray&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeIntArray&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveBoundary&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePosition2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLine2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLineSeg2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeRay2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCircArc2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipArc2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCubicSplineCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCompositeCurve2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetCurve2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePolyline2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePosition3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePointOnSurface&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLine3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeRay3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeLineSeg3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePlane&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundedPlane&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCircArc3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipArc3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCubicSplineCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbCurve3d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCompositeCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGePolyline3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeAugPolyline3d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalCurve3d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCone&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCylinder&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeTorus&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalSurface&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeOffsetSurface&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeNurbSurface&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeExternalBoundedSurface&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeSphere&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundBlock2d&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeBoundBlock3d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveCurveInt2d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeCurveCurveInt3d&);
    GX_DLLEXPIMPORT static
    Acad::ErrorStatus inFields(AcDbDxfFiler*, AcGeEllipCone&);

    GE_DLLDATAEXIMP static const AcGeLibVersion  AcGeDxfIOVersion;
};


#pragma pack (pop)
#endif
