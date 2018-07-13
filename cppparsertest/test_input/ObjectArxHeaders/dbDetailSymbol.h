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
#include "dbDetailViewStyle.h"

#pragma pack (push, 8)


#ifndef ACSYNERGY_PORT
#define ACSYNERGY_PORT
#endif


class ACSYNERGY_PORT AcDbDetailSymbol : public AcDbViewSymbol
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDetailSymbol);

	/// <summary>
	/// Default constructor. 
	/// </summary>
	///
	/// <remarks>
	/// For internal use only.
	/// </remarks>
	///
	AcDbDetailSymbol();

	enum BoundaryType
    {
        kCircularBoundary,
        kRectangularBoundary,
		kCustomBoundary
    };

	enum OverriddenProperty
	{
		kModelEdge            = 0x00000001,
        kIdentifierPosition   = 0x00000001 << 1,
	};

    BoundaryType					boundaryType () const;
	AcDbDetailViewStyle::ModelEdge	modelEdgeType() const;
	bool							isOverriddenProperty(AcDbDetailSymbol::OverriddenProperty property) const;
    bool							displayIdentifier() const;
    AcGePoint3d						origin () const;
    const AcGeVector3d&				direction () const;
    const AcGeVector2d&				boundarySize () const;
	const AcGePoint3d&				modelEdgeOrigin() const;
	double							owningViewScale () const;
    double							detailViewScale () const;
	const AcGeVector3d&				modelEdgeDirection () const;
	const AcGePoint3d				identifierPosition () const;

    ///////////////////////////////////////////////////////////////////////
    // *** Internal-use-only methods ***
    Acad::ErrorStatus				setBoundaryType (BoundaryType bndType);
	Acad::ErrorStatus				setModelEdgeType(AcDbDetailViewStyle::ModelEdge modelEdgeType);
    Acad::ErrorStatus				setPickPoints (const AcGePoint3dArray& pickPoints);
	Acad::ErrorStatus				setModelEdgeOrigin(const AcGePoint3d& pt);
	Acad::ErrorStatus				setOwningViewScale (double viewScale);
    Acad::ErrorStatus				setDetailViewScale (double viewScale);
    Acad::ErrorStatus				setModelEdgeDirection (const AcGeVector3d& dir);
    Acad::ErrorStatus				setIdentifierPosition (const AcGePoint3d& pt);
	Acad::ErrorStatus				initializeIdentifierPositionAt (const AcGePoint3d& pt);
    Acad::ErrorStatus				resetIdentifierPosition ();
    Acad::ErrorStatus				setDisplayIdentifier (const bool displayIdentifier);

    Acad::ErrorStatus				setOrigin (const AcGePoint3d& pt);
    Acad::ErrorStatus				setBoundarySize (const AcGeVector2d& size);

    Acad::ErrorStatus				modelEdgeBorderExtents(AcDbExtents& modelEdgeExtent)const;
};

#pragma pack (pop)
