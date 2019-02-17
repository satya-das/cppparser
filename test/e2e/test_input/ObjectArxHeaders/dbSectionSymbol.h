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


#pragma once

#include "dbViewSymbol.h"

#pragma pack (push, 8)


#ifndef ACSYNERGY_PORT
#define ACSYNERGY_PORT
#endif


class ACSYNERGY_PORT AcDbSectionSymbol : public AcDbViewSymbol
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSectionSymbol);

	/// <summary>
	/// Default constructor. 
	/// </summary>
	///
	/// <remarks>
	/// For internal use only.
	/// </remarks>
	///
	AcDbSectionSymbol();

    int               sectionPointsCount() const;
    void              getSectionPoints(AcGePoint3dArray &pts) const;
    Acad::ErrorStatus getSectionPointAt(int idx, AcGePoint3d& pt) const;
    Acad::ErrorStatus getBulgeAt(int idx, double& bulge) const;
    Acad::ErrorStatus getLabelNameAt(int idx, AcString& sName) const;
    Acad::ErrorStatus getLabelOffsetAt(int idx, AcGeVector3d& offset) const;
    void              getLabelOffsets(AcGeVector3dArray& offsets) const;
    bool              isViewDirectionLeft() const;
    bool              isHalfSection () const;

    // *** Internal-use-only methods ***
    Acad::ErrorStatus setSectionPoints(const AcGePoint3dArray& pts);
    Acad::ErrorStatus setSectionPoints(const AcGePoint3dArray& pts, const AcGeDoubleArray& bulges);
    Acad::ErrorStatus addSectionPoint(const AcGePoint3d& pt, double bulge = 0);
    Acad::ErrorStatus removeSectionPointAt(int idx);
    Acad::ErrorStatus setSectionPointAt(int idx, const AcGePoint3d& pt, double bulge = 0);
    void              clearSectionPoints();
    Acad::ErrorStatus setLabelNameAt(int idx, const ACHAR* pName);
    Acad::ErrorStatus setLabelNames(const AcArray<AcString>& names);
    Acad::ErrorStatus setLabelOffsetAt(int idx, const AcGeVector3d& offset);
    Acad::ErrorStatus setLabelOffsets(const AcGeVector3dArray& offsets);
    void              resetLabelOffsets(bool allOffsets = true);
    void              setViewDirectionLeft(bool bLeft);
    void              setIsHalfSection (bool bHalfSection);
    bool              flipDirection ();
};

#pragma pack (pop)
