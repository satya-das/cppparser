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

#pragma once

#include "acgi.h"
#pragma pack (push, 8)

class AcGiImpLinetypeEngine;

class AcGiLinetypeEngine : public AcRxObject 
{
public:
    ACRX_DECLARE_MEMBERS(AcGiLinetypeEngine);

    AcGiLinetypeEngine();
    virtual ~AcGiLinetypeEngine();

    // Tessellate the polyline with linetype applied, through world draw
    virtual Acad::ErrorStatus tessellate (bool                 bIsArc,
                                          bool                 bIsCircle,
                                          const Adesk::UInt32  nPoints,
                                          const AcGePoint3d  * pVertexList,
                                          AcGiWorldDraw *      pWorldDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale,
                                          const AcGeVector3d * pNormal,
                                          bool                 plineGen = false);

    // Tessellate the polyline with linetype applied, through viewport draw
    virtual Acad::ErrorStatus tessellate (bool                 bIsArc,
                                          bool                 bIsCircle,
                                          const Adesk::UInt32  nPoints,
                                          const AcGePoint3d  * pVertexList,
                                          AcGiViewportDraw *   pViewportDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale,
                                          const AcGeVector3d * pNormal,
                                          bool                 plineGen = false);

    virtual Acad::ErrorStatus tessellate (const AcGeCircArc3d& arcSeg,
                                          const AcGeMatrix3d&  ecsMat,
                                          double               startWidth,
                                          double               endWidth,
                                          AcGiCommonDraw *     pDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale,
                                          double               thick);

    virtual Acad::ErrorStatus tessellate (const AcGeLineSeg3d& lineSeg,
                                          const AcGeMatrix3d&  ecsMat,
                                          double               startWidth,
                                          double               endWidth,
                                          AcGiCommonDraw *     pDraw,
                                          const AcDbObjectId   linetypeId,
                                          double               linetypeScale);

private:
    AcGiImpLinetypeEngine * mpAcGiImpLinetypeEngine;
};

#pragma pack (pop)
