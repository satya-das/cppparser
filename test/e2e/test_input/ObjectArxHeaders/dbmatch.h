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
// DBMATCH.H
//
// DESCRIPTION: AcDbMatchProperties Protocol extension abstract base class
//
// NOTE:
// Default implementation to be attached to AcDbEntity as a catch-all. This
// guarantees that this protocol extension will be found  for any entity so
// the search up the AcRxClass tree will not fail and abort AutoCAD.  
//

#ifndef ARX_DBMATCH_H
#define ARX_DBMATCH_H

#include "acdb.h"
#include "dbmain.h"

#pragma pack (push, 8)

class AcDbMatchProperties	: public AcRxObject
//
//  AcDbMatchProperties Protocol extension abstract base class. 
//
{
public:
    /// <summary>
    /// This is an enumeration of predefined settings used in 
    /// MatchProperties
    /// </summary>
    enum Flags {
        /// <summary>
        /// Color Flag
        /// </summary>
        kColorFlag     = 0x1,
        
        /// <summary>
        /// Layer Flag
        /// </summary>
        kLayerFlag     = 0x2,

        /// <summary>
        /// Linetype Flag
        /// </summary>
        kLtypeFlag     = 0x4,
        
        /// <summary>
        /// Thickness Flag
        /// </summary>
        kThicknessFlag = 0x8,

        /// <summary>
        /// Linetype Scale Flag
        /// </summary>
        kLtscaleFlag   = 0x10,

        /// <summary>
        /// Text Flag
        /// </summary>
        kTextFlag      = 0x20,

        /// <summary>
        /// Dimension Flag
        /// </summary>
        kDimensionFlag = 0x40,

        /// <summary>
        /// Hatch Flag
        /// </summary>
        kHatchFlag     = 0x80,

        /// <summary>
        /// Line weight Flag
        /// </summary>
        kLweightFlag   = 0x100,

        /// <summary>
        /// Plot style Flag
        /// </summary>
        kPlotstylenameFlag = 0x200,

        /// <summary>
        /// Polyline Flag
        /// </summary>
        kPolylineFlag  = 0x400,

        /// <summary>
        /// Viewport Flag
        /// </summary>
        kViewportFlag  = 0x800,

        /// <summary>
        /// Table Flag
        /// </summary>
        kTableFlag     = 0x1000,

        /// <summary>
        /// Material Flag
        /// </summary>
        kMaterialFlag  = 0x2000,

        /// <summary>
        /// Shadow Display Flag
        /// </summary>
        kShadowDisplayFlag    = 0x4000,

        /// <summary>
        /// Multileader Flag
        /// </summary>
        kMultileaderFlag      = 0x8000,

        /// <summary>
        /// Transparency Flag
        /// </summary>
        kTransparencyFlag     = 0x10000,

        /// <summary>
        /// Center Objects Flag
        /// Center object includes centermark and center line.
        /// </summary>
        kCenterObjectFlag     = 0x20000,

        /// <summary>
        /// All Flags are set.
        /// </summary>
        kSetAllFlagsOn = 0x3FFFF
    };

	ACRX_DECLARE_MEMBERS(AcDbMatchProperties);

	virtual void copyProperties(AcDbEntity* pSrcEntity, AcDbEntity* pTrgEntity,
								unsigned int flag) const  = 0;
};

#pragma pack (pop)

#endif

