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
//  dbappgrip.h
//    
//  AcRxObject
//    AcRxProtocolReactor
//      AcDbAppEntityGrips
//
//
//  DESCRIPTION:
//
//  This file contains classes that define a framework for extending the grips
//  provided by existing AcDbEntities using an AcRxProtocolReactor.  ObjectDBX
//  calls the reactor methods when elaborating the grip points for an entity
//  Applications implement this protocol extension to provide custom grips for
//  entities. 
//
//  
#pragma once

#include "dbmain.h"

#include "rxprotevnt.h"


#pragma pack(push, 8)

////////////////////////////////////////////////////////////////////////
// class AcDbAppEntityGrips
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class allows applications to provide custom grips for entities provide
/// custom grips for entities without deriving from the entity class (i.e.
/// without providing a custom object). 
/// </summary>
///
/// <remarks>
/// Currently only called when elaborating grips for an AcDbBlockReference.
/// </remarks>
///
class AcDbAppEntityGrips : public AcRxProtocolReactor
{
public:

    ACRX_DECLARE_MEMBERS(AcDbAppEntityGrips);

    /// <summary>
    /// Returns the application-defined grip points for an entity. 
    /// </summary>
    ///
    /// <param name="grips">
    /// Array of pointers to dynamically allocated AcDbGripData objects, one
    /// for each grip point in the entity.
    /// </param>
    /// <param name="curViewUnitSize">
    /// The size, in pixels, of one drawing unit in the current viewport.
    /// </param>
    /// <param name="gripSize">
    /// The current grip size, in pixels.
    /// </param>
    /// <param name="curViewDir">
    /// A vector describing the view direction in the current viewport.
    /// </param>
    /// <param name="bitflags">
    /// Bitmap of one or more flags specified by the GetGripPointsFlags
    /// enumeration.
    /// </param>
    /// <param name="pEntity">
    /// Pointer to the AcDbEntity to get grips for.
    /// </param>
    /// 
    /// <returns>
    /// Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Grips returned by all applications are appended to the entity's own
    /// grips. See also AcDbEntity::getGripPoints().
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus getGripPoints (
                                        AcDbGripDataPtrArray& grips,
                                        const double          curViewUnitSize, 
                                        const int             gripSize, 
                                        const AcGeVector3d&   curViewDir, 
                                        const int             bitflags,
                                        AcDbEntity*           pEntity) = 0;
 
   
    /// <summary>
    /// Moves a grip point returned by a previous call to
    /// <c>AcDbAppEntityGrips::getGripPoints()</c>.
    /// </summary>
    ///
    /// <param name="gripAppData">
    /// Input array of pointers, one for each grip point to be moved; these are
    /// the appData pointers from the AcDbGripData objects for the grip points
    /// to be moved.
    /// </param>
    /// <param name="offset">
    /// A vector, in WCS coordinates, indicating the direction and magnitude of
    /// the translation to be applied to the grips.
    /// </param>
    /// <param name="bitflags">
    /// Reserved for future use, currently zero.
    /// </param>
    /// <param name="pEntity">
    /// Pointer to the AcDbEntity to move grips on. 
    /// </param>
    /// 
    /// <returns>
    /// Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// See also AcDbEntity::moveGripPointsAt().
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus moveGripPointsAt (
                         const AcDbVoidPtrArray&        gripAppData, 
                         const AcGeVector3d&            offset,
                         const int                      bitflags,
                         AcDbEntity*                    pEntity) = 0;

    /// <summary>
    /// Grip status callback function.
    /// </summary>
    ///
    /// <param name="status">
    /// The new AcDb::GripStat status.
    /// </param>
    /// <param name="pEntity">
    /// Pointer to the AcDbEntity whose grips the status is for.
    /// </param>
    /// 
    /// <remarks>
    /// This function is called with a status value of kGripsToBeDeleted when
    /// the grips returned by a prior call to
    /// <c>AcDbAppEntityGrips::getGripPoints()</c> are about to be deleted in
    /// the host  application. This notification allows for any required
    /// resource management tasks such  as the deletion of AppData data
    /// associated with any AcDbGripData structures.
    /// </remarks>
    ///
    virtual void gripStatus(const AcDb::GripStat status,
                            AcDbEntity*          pEntity) = 0;
};

////////////////////////////////////////////////////////////////////////
// class AcDbBlockInsertionPoints
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class allows applications to elaborate different insertion points for
/// blocks. 
/// </summary>
///
class AcDbBlockInsertionPoints :  public AcRxProtocolReactor
{
    public:

        ACRX_DECLARE_MEMBERS(AcDbBlockInsertionPoints);

        /// <summary>
        /// Returns the application-defined insertion points for a block.
        /// </summary>
        ///
        /// <param name="pBlock">
        /// A pointer to the block whose insertion points should be elaborated. 
        /// </param>
        /// <param name="pBlkRef">
        /// A pointer to the block reference whose insertion points should be elaborated.
        /// The application can choose to use pBlkRef instead of pBlock, if the block is
        /// being dragged and insertion points or alignment angles change dynamically.
        /// </param>
        /// <param name="insPts">
        /// An array of AcGePoint3d objects, one for each insertion point. The
        /// returned points should be in the coordinate system of the block. 
        /// </param>
        /// <param name="alignmentDirections">
        /// An array of AcGeVector3d objects, one for each insertion point. The
        /// returned vectors describe the alignment direction for the block
        /// when the insertion point passes over other geometry in the drawing. 
        /// </param>
        /// 
        /// <returns>
        /// Acad::eOk if successful.
        /// </returns>
        ///
        /// <remarks>
        /// Any application-defined insertion points supplement the default
        /// insertion point for a block. Some commands (e.g. INSERT) allow
        /// users to cycle through the insertion points of a block when placing
        /// it in a drawing.
        /// Some commands (e.g. INSERT) use the alignment vector for a grip to
        /// automatically rotate the block as it is being dragged for insertion
        /// when the cursor passes over other entities in the drawing. If the
        /// alignment vector for a block is non-zero, when the block passes
        /// over other geometry in the drawing the block is rotated about the
        /// insertion point to make the alignment direction parallel to the
        /// normal of the entity under the cursor at the point closest to the
        /// cursor on the entity. 
        /// The size of the returned arrays must be the same.
        /// </remarks>
        virtual Acad::ErrorStatus getInsertionPoints (
                        const AcDbBlockTableRecord* pBlock,
                        const AcDbBlockReference*   pBlkRef,
                        AcGePoint3dArray&           insPts,
                        AcGeVector3dArray&          alignmentDirections) = 0;
};
#pragma pack(pop)
