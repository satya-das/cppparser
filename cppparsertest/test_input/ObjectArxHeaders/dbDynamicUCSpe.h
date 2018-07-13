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
// dbDynamicUCSPE.H
//
// DESCRIPTION: AcDbDynamicUCSPE Protocol extension abstract base class
//
#include "acdb.h"
#include "dbmain.h"

#pragma once
#pragma pack (push, 8)

//
//  AcDbDynamicUCSPE Protocol extension abstract base class. 
//
class AcDbDynamicUCSPE	: public AcRxObject
{
public:
    enum Flags {
        kDefault     = 0x00,
    };

	ACRX_DECLARE_MEMBERS(AcDbDynamicUCSPE);

    // Contract:
    // The implementer is expected to populate the result array 
    // with one or more AcGePlane objects and return Acad::eOk if successful.
    // Populate distToEdge with the distance from the point to the edge of the subent.  
    // This value is used when the subent is not to be highlighted unless the
    // distance is >= the current aperture value.  If the implementer doesn't
    // care about aperture tolerance, return this as a negative value and it
    // will be duly ignored.
    //
    // Expected failure codes are Acad::eNotImplementedYet or Acad::eNotApplicable.
    // Return Acad::eWrongObjectType if the object under the cursor is unsupported.
    // Return Acad::eWrongSubentityType if the subent under the cursor is unsupported.
    //
    virtual Acad::ErrorStatus 
        getCandidatePlanes(AcArray<AcGePlane>& results,
                            double &distToEdge,
                            double &objWidth,
                            double &objHeight,
                            AcDbEntity* pEnt,
                            const AcDbSubentId& subentId,
                            const AcGePlane& viewplane,
                            AcDbDynamicUCSPE::Flags flags = kDefault //reserved
                            ) const = 0;
};

//
//  Version 2 of DUCS Protocol extension abstract base class. 
//  Support planes on none sub-entities
//  Support owner draw of plane hightlighting
//  For the time being, point cloud object uses this.
//
class CPoint;
class AcDbNonSubEntDynamicUCSPE : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcDbNonSubEntDynamicUCSPE, ACDBCORE2D_PORT);

    // Contract:
    // For get the dynamic UCS plane for the cursor location
    virtual Acad::ErrorStatus
        getCandidatePlane(
            AcDbEntity* Ent,   // INPUT: the point cloud object itself
            const CPoint& pt,        // INPUT: Cursor location in window screen coordinate
            AcGePlane &result,       // OUT: Currently only one plane is supported (the nearest plane is decided by point cloud object itself)
            double &distToEdge,      // OUT: Distance from cursor to plane boundary (to calculate aperture box)
            double &objWidth,        // OUT: width of the plane extent (needed for grid snapping adjustment)
            double &objHeight,       // OUT: height of plane extent (needed for grid snapping adjustment)
            void*& context           // OUT: an per object defined context (for later highlight and de-highlight notification data picky-back), this is also used to uniquely identify one UCS plane.(like GSMarker) Such that the caller will know a new plane is detected
            ) = 0;

    // Contract:
    // Let the point cloud object to render a custom visual feedback on screen to indicate the dynamic UCS plane
    virtual Acad::ErrorStatus
            highlightPlane(
            AcDbEntity* Ent,   // INPUT: the point cloud object itself
            void* context            // INPUT: the context returned from getCandidatePlane()
            ) = 0;

    // Contract:
    // Let the point cloud object to stop rendering(clearing) the visual feedback
    virtual Acad::ErrorStatus
        dehighlightPlane(
            AcDbEntity* Ent,   // INPUT: the point cloud object itself
            void* context            // INPUT: the context returned from getCandidatePlane()
            ) = 0;
};
#pragma pack (pop)


