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
// This file contains the class AcGeFileIO - a utility class that 
// performs file IO.

#ifndef AC_GEFILEIO_H
#define AC_GEFILEIO_H     

#include "acadstrc.h"
#include "gegbl.h"
#include "gedll.h"
#include "gept2dar.h"
#include "gevc2dar.h"
#include "gept3dar.h"
#include "gevc3dar.h"
#include "gedblar.h"
#include "geintarr.h"
#pragma pack (push, 8)
     
class AcGeEntity2d;
class AcGeEntity3d;
class AcGePoint2d;
class AcGeVector2d;
class AcGeMatrix2d;
class AcGeScale2d;
class AcGePoint3d;
class AcGeVector3d;
class AcGeMatrix3d;
class AcGeScale3d;
class AcGeTol;
class AcGeInterval;
class AcGeKnotVector;
class AcGeCurveBoundary;
class AcGePosition2d;
class AcGePointOnCurve2d;
class AcGeLine2d;
class AcGeLineSeg2d;
class AcGeRay2d;
class AcGeCircArc2d;
class AcGeEllipArc2d;
class AcGeExternalCurve2d;
class AcGeCubicSplineCurve2d;
class AcGeCompositeCurve2d;
class AcGeOffsetCurve2d;
class AcGeNurbCurve2d;
class AcGePolyline2d;
class AcGePosition3d;
class AcGePointOnCurve3d;
class AcGePointOnSurface;
class AcGeLine3d;
class AcGeRay3d;
class AcGeLineSeg3d;
class AcGePlane;
class AcGeBoundedPlane;
class AcGeBoundBlock2d;
class AcGeBoundBlock3d;
class AcGeCircArc3d;
class AcGeEllipArc3d;
class AcGeCubicSplineCurve3d;
class AcGeCompositeCurve3d;
class AcGeOffsetCurve3d;
class AcGeNurbCurve3d;
class AcGePolyline3d;
class AcGeAugPolyline3d;
class AcGeExternalCurve3d;
class AcGeSurface;
class AcGeCone;
class AcGeCylinder;
class AcGeTorus;
class AcGeExternalSurface;
class AcGeOffsetSurface;
class AcGeNurbSurface;
class AcGeExternalBoundedSurface;
class AcGeSphere;
class AcGeCurveCurveInt2d;
class AcGeCurveCurveInt3d;
class AcGeEllipCone;
     
class AcGeFiler;
class AcGeLibVersion;
     
     
class 
AcGeFileIO
{
public:
     
 // Write out to file
 //
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePoint2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeVector2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeMatrix2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeScale2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePoint2dArray&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeVector2dArray&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePoint3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeVector3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeMatrix3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeScale3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePoint3dArray&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeVector3dArray&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeTol&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeInterval&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeKnotVector&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeDoubleArray&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler* filer, const AcGeIntArray& ent,
                                const AcGeLibVersion& version);
 GX_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCurveBoundary&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePosition2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePointOnCurve2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeLine2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeLineSeg2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeRay2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCircArc2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeEllipArc2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeExternalCurve2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCubicSplineCurve2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCompositeCurve2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeOffsetCurve2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeNurbCurve2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePolyline2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePosition3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePointOnCurve3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePointOnSurface&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeLine3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeRay3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeLineSeg3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePlane&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeBoundedPlane&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCircArc3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeEllipArc3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCubicSplineCurve3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCompositeCurve3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeOffsetCurve3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeNurbCurve3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGePolyline3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeAugPolyline3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeExternalCurve3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCone&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCylinder&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeTorus&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeExternalSurface&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeOffsetSurface&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeNurbSurface&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeExternalBoundedSurface&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeSphere&,
                             const AcGeLibVersion& = AcGe::gLibVersion);

 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeBoundBlock2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);

 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeBoundBlock3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);

 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCurveCurveInt2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);

 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeCurveCurveInt3d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);

 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeLibVersion&);

 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus outFields(AcGeFiler*, const AcGeEllipCone&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
     
 // Read in from file
 //
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePoint2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeVector2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeMatrix2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeScale2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePoint2dArray&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeVector2dArray&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePoint3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeVector3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeMatrix3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeScale3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePoint3dArray&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeVector3dArray&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeTol&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeInterval&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeKnotVector&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeDoubleArray&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static
 Acad::ErrorStatus inFields(AcGeFiler* filer, AcGeIntArray& ent,
                                const AcGeLibVersion& version);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCurveBoundary&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePosition2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePointOnCurve2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeLine2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeLineSeg2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeRay2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCircArc2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeEllipArc2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeExternalCurve2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCubicSplineCurve2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCompositeCurve2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeOffsetCurve2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeNurbCurve2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePolyline2d&,
                             const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePosition3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePointOnCurve3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePointOnSurface&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeLine3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeRay3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeLineSeg3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePlane&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeBoundedPlane&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCircArc3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeEllipArc3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCubicSplineCurve3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCompositeCurve3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeOffsetCurve3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeNurbCurve3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGePolyline3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeAugPolyline3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeExternalCurve3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCone&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCylinder&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeTorus&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeExternalSurface&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeOffsetSurface&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeNurbSurface&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeExternalBoundedSurface&,
                            const AcGeLibVersion& = AcGe::gLibVersion);
 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeSphere&,
                            const AcGeLibVersion& = AcGe::gLibVersion);

 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeBoundBlock2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);

 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeBoundBlock3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);

 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCurveCurveInt2d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);

 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeCurveCurveInt3d&,
                            const AcGeLibVersion& = AcGe::gLibVersion);

 GX_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeEllipCone&,
                            const AcGeLibVersion& = AcGe::gLibVersion);

 // There is no version on a version object.
 //
 GE_DLLEXPIMPORT static 
 Acad::ErrorStatus inFields(AcGeFiler*, AcGeLibVersion&);
     
private:
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus writeBoolean(AcGeFiler*, Adesk::Boolean,
                                const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus readBoolean(AcGeFiler*, Adesk::Boolean*,
                               const AcGeLibVersion&);
    static
    Acad::ErrorStatus writeBool(AcGeFiler*, bool,
                                const AcGeLibVersion&);
    static
    Acad::ErrorStatus readBool(AcGeFiler*, bool*,
                               const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus writeLong(AcGeFiler*, Adesk::Int32,
                             const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus readLong(AcGeFiler*, Adesk::Int32*,
                            const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus writeDouble(AcGeFiler*, double,
                             const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus readDouble(AcGeFiler*, double*,
                              const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus writePoint2d(AcGeFiler*, const AcGePoint2d&,
                                const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus readPoint2d(AcGeFiler*, AcGePoint2d*,
                               const AcGeLibVersion&);
    static
    Acad::ErrorStatus writeVector2d(AcGeFiler*, const AcGeVector2d&,
                                 const AcGeLibVersion&);
    static
    Acad::ErrorStatus readVector2d(AcGeFiler*, AcGeVector2d*,
                                const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus writePoint3d(AcGeFiler*, const AcGePoint3d&,
                                const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus readPoint3d(AcGeFiler*, AcGePoint3d*,
                               const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus writeVector3d(AcGeFiler*, const AcGeVector3d&,
                                 const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus readVector3d(AcGeFiler*, AcGeVector3d*,
                                const AcGeLibVersion&);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus writeAcGeSurface(AcGeFiler*, const AcGeSurface&,
                                    const AcGeLibVersion& version);
    GE_DLLEXPIMPORT static
    Acad::ErrorStatus readAcGeSurface(AcGeFiler*, AcGeSurface&,
                                   const AcGeLibVersion& version);
    static
    Acad::ErrorStatus writeAcGeEntity2d(AcGeFiler* filer,
	            const AcGeEntity2d& ent, const AcGeLibVersion& version);
	static
    Acad::ErrorStatus readAcGeEntity2d(AcGeFiler* filer, AcGeEntity2d*& ent,
	            AcGe::EntityId id, const AcGeLibVersion& version);
    static
    Acad::ErrorStatus writeAcGeEntity3d(AcGeFiler* filer,
	            const AcGeEntity3d& ent, const AcGeLibVersion& version);
    static
    Acad::ErrorStatus readAcGeEntity3d(AcGeFiler* filer, AcGeEntity3d*& ent,
	            AcGe::EntityId id, const AcGeLibVersion& version);

    static
    Acad::ErrorStatus writeBytes(AcGeFiler* filer, const void* buf,
                                 Adesk::UInt32 len, const AcGeLibVersion& version);
    static
    Acad::ErrorStatus readBytes(AcGeFiler* filer, void* buf,
                                Adesk::UInt32 len, const AcGeLibVersion& version);

	friend class AcGeEllipArcParamOffset;

};
     
#pragma pack (pop)
#endif
