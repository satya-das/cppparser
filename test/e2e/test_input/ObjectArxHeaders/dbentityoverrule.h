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

#include "rxoverrule.h"

#pragma pack (push, 8)

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbPropertiesOverrule overrules a subset of property related operations 
/// that AcDbEntity and AcDbObject class specifies. It is intended as a base 
/// class for clients who want to alter some or all behavior of a given 
/// AcDbEntity-derived or AcDbObject-derived class. At the base level, each 
/// default implementation simply calls the corresponding method in the target 
/// class.
/// </description>  
class AcDbPropertiesOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbPropertiesOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbPropertiesOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subList.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <remarks>
    /// The default implementation of AcDbPropertiesOverrule::list calls the 
    /// protected virtual AcDbEntity::subList method. 
    /// </remarks>                      
    ACDBCORE2D_PORT virtual void list(const AcDbEntity* pSubject);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbObject::subGetClassID.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbObject that this overrule is 
    /// applied against.</param>
    /// <param name="pClsid">Output corresponding COM wrapper class ID.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbPropertiesOverrule::getClassID calls 
    /// the protected virtual AcDbObject::subGetClassID method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getClassID(const AcDbObject* pSubject, CLSID* pClsid);
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbOsnapOverrule overrules a subset of osnap related operations that 
/// AcDbEntity class specifies. It is intended as a base class for clients who 
/// want to alter some or all behavior of a given AcDbEntity-derived class. At 
/// the base level, each default implementation simply calls the corresponding 
/// method in the target class.
/// </description> 
class AcDbOsnapOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbOsnapOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbOsnapOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetOsnapPoints.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="osnapMode">Input osnap mode being requested.</param>
    /// <param name="gsSelectionMark">Input GS marker of the subentity involved 
    /// in the object snap operation.</param>
    /// <param name="pickPoint">Input point (in WCS coordinates) picked during 
    /// the object snap operation.</param>
    /// <param name="lastPoint">Input point (in WCS coordinates) selected just 
    /// before pickPoint.</param>
    /// <param name="viewXform">Input transformation matrix to transform from 
    /// WCS to DCS.</param>
    /// <param name="snapPoints">Input pre-existing array to append osnap points 
    /// to (may already contain points); output with object snap points appended.
    /// </param>
    /// <param name="geomIds">Not in use.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbOsnapOverrule::getOsnapPoints calls 
    /// the protected virtual AcDbEntity::subGetOsnapPoints method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getOsnapPoints(
                                const AcDbEntity*   pSubject,
                                AcDb::OsnapMode     osnapMode,
                                Adesk::GsMarker     gsSelectionMark,
                                const AcGePoint3d&  pickPoint,
                                const AcGePoint3d&  lastPoint,
                                const AcGeMatrix3d& viewXform,
                                AcGePoint3dArray&   snapPoints,
                                AcDbIntArray &   geomIds);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetOsnapPoints.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="osnapMode">Input osnap mode being requested.</param>
    /// <param name="gsSelectionMark">Input GS marker of the subentity involved 
    /// in the object snap operation.</param>
    /// <param name="pickPoint">Input point (in WCS coordinates) picked during 
    /// the object snap operation.</param>
    /// <param name="lastPoint">Input point (in WCS coordinates) selected just 
    /// before pickPoint.</param>
    /// <param name="viewXform">Input transformation matrix to transform from 
    /// WCS to DCS.</param>
    /// <param name="snapPoints">Input pre-existing array to append osnap points 
    /// to (may already contain points); output with object snap points appended.
    /// </param>
    /// <param name="geomIds">Not in use.</param>
    /// <param name="insertionMat">Input block transformation.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbOsnapOverrule::getOsnapPoints calls 
    /// the protected virtual AcDbEntity::subGetOsnapPoints method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getOsnapPoints(
                                const AcDbEntity*   pSubject,
                                AcDb::OsnapMode     osnapMode,
                                Adesk::GsMarker     gsSelectionMark,
                                const AcGePoint3d&  pickPoint,
                                const AcGePoint3d&  lastPoint,
                                const AcGeMatrix3d& viewXform,
                                AcGePoint3dArray&   snapPoints,
                                AcDbIntArray &   geomIds,
                                const AcGeMatrix3d& insertionMat);

    ACDBCORE2D_PORT virtual bool isContentSnappable(const AcDbEntity*   pSubject);
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbTransformOverrule overrules a subset of transform related operations that 
/// AcDbEntity class specifies. It is intended as a base class for clients who 
/// want to alter some or all behavior of a given AcDbEntity-derived class. At 
/// the base level, each default implementation simply calls the corresponding 
/// method in the target class.
/// </description> 
class AcDbTransformOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbTransformOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbTransformOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subTransformBy.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="xform">For future use.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbTransformOverrule::transformBy calls 
    /// the protected virtual AcDbEntity::subTransformBy method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   transformBy(AcDbEntity* pSubject, const AcGeMatrix3d& xform);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetTransformedCopy.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="xform">Input matrix by which to transform the copy of the 
    /// entity.</param>
    /// <param name="pEnt">Input reference to an "empty" pointer; output pointing 
    /// to the transformed copy of the entity.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbTransformOverrule::getTransformedCopy 
    /// calls the protected virtual AcDbEntity::subGetTransformedCopy method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   getTransformedCopy(const AcDbEntity* pSubject, const AcGeMatrix3d& xform,
                                                            AcDbEntity*& pEnt);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subExplode.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="entitySet">Input array to contain pointers to new entities; 
    /// this array may already contain pointers from other entities' explode() 
    /// methods; output with all entities that result from exploding this entity, 
    /// appended to the array.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbTransformOverrule::explode calls 
    /// the protected virtual AcDbEntity::subExplode method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   explode(const AcDbEntity* pSubject, AcDbVoidPtrArray& entitySet);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subCloneMeForDragging.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <returns> Returns Adesk::kTrue indicating that a clone will be created 
    /// for the dragging operation.</returns>
    /// <remarks>
    /// The default implementation of AcDbTransformOverrule::cloneMeForDragging 
    /// calls the protected virtual AcDbEntity::subCloneMeForDragging method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Adesk::Boolean      cloneMeForDragging(AcDbEntity* pSubject);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subHideMeForDragging.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <returns> Returns true if the original object should be hidden while a 
    /// clone is being dragged.</returns>
    /// <remarks>
    /// The default implementation of AcDbTransformOverrule::hideMeForDragging calls 
    /// the protected virtual AcDbEntity::subHideMeForDragging method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual bool                hideMeForDragging(const AcDbEntity* pSubject);
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbGripOverrule overrules a subset of grip related operations that 
/// AcDbEntity class specifies. It is intended as a base class for clients who 
/// want to alter some or all behavior of a given AcDbEntity-derived class. At 
/// the base level, each default implementation simply calls the corresponding 
/// method in the target class.
/// </description>
class AcDbGripOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGripOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbGripOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetGripPoints.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="gripPoints">Input pre-existing array to append the grip 
    /// points to; output with the entity's grip points appended.</param>
    /// <param name="osnapModes">not currently in use.</param>
    /// <param name="geomIds">not currently in use.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbGripOverrule::getGripPoints calls the 
    /// protected virtual AcDbEntity::subGetGripPoints method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   getGripPoints(const AcDbEntity* pSubject, 
                                AcGePoint3dArray&  gripPoints,
                                AcDbIntArray &     osnapModes,
                                AcDbIntArray &  geomIds);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subMoveGripPointsAt.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="indices">Input array containing index values (which correspond 
    /// to grip points reported by the getGripPoints() method) that indicate which 
    /// grip points are currently "hot".</param>
    /// <param name="offset">Input vector (in WCS coordinates) indicating the 
    /// direction and magnitude that the grip points have been translated.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbGripOverrule::moveGripPointsAt calls the 
    /// protected virtual AcDbEntity::subMoveGripPointsAt method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   moveGripPointsAt(AcDbEntity* pSubject, 
                                    const AcDbIntArray & indices,
                                    const AcGeVector3d& offset);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetGripPoints.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="grips">Array of pointers to dynamically allocated AcDbGripData 
    /// objects, one for each grip point in the entity.</param>
    /// <param name="curViewUnitSize">Size, in pixels, of one drawing unit in the 
    /// current viewport.</param>
    /// <param name="gripSize">Current grip size, in pixels.</param>
    /// <param name="curViewDir">Vector describing the view direction in the 
    /// current viewport.</param>
    /// <param name="bitflags">Bitmap of one or more flags specified by the 
    /// GetGripPointsFlags enumeration.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbGripOverrule::getGripPoints calls the 
    /// protected virtual AcDbEntity::subGetGripPoints method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   getGripPoints(const AcDbEntity* pSubject,
                                                        AcDbGripDataPtrArray& grips,
                                                        const double curViewUnitSize, 
                                                        const int gripSize, 
                                                        const AcGeVector3d& curViewDir, 
                                                        const int bitflags);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subMoveGripPointsAt.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="gripAppData">Input array of pointers, one for each grip point 
    /// to be moved; these are the appData pointers from the AcDbGripData objects 
    /// for the grip points to be moved.</param>
    /// <param name="offset">Vector, in WCS coordinates, indicating the direction 
    /// and magnitude of the translation to be applied to the grips.</param>
    /// <param name="bitflags">Reserved for future use, currently zero.</param>
    /// <returns> Returns Acad::eOk if successful. </returns>
    /// <remarks>
    /// The default implementation of AcDbGripOverrule::moveGripPointsAt calls the 
    /// protected virtual AcDbEntity::subMoveGripPointsAt method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   moveGripPointsAt(AcDbEntity* pSubject,
                                            const AcDbVoidPtrArray& gripAppData,
                                            const AcGeVector3d& offset, 
                                            const int bitflags);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetStretchPoints.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="stretchPoints">Input pre-existing array to append the stretch 
    /// points to; output with the entity's stretch points appended.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbGripOverrule::getStretchPoints calls the 
    /// protected virtual AcDbEntity::subGetStretchPoints method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   getStretchPoints(const AcDbEntity* pSubject,
                                                           AcGePoint3dArray& stretchPoints);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subMoveStretchPointsAt.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="indices">Input array containing index values that indicate 
    /// which stretch points are being translated.</param>
    /// <param name="offset">Input vector (in WCS coordinates) indicating the 
    /// direction and magnitude that the stretch points have been translated.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbGripOverrule::moveStretchPointsAt calls 
    /// the protected virtual AcDbEntity::subMoveStretchPointsAt method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   moveStretchPointsAt(AcDbEntity* pSubject,
                                                              const AcDbIntArray & indices,
                                                              const AcGeVector3d& offset);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGripStatus.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="status">Value describing the status of the grip operation; 
    /// one of the values from the GripStatus enumeration.</param>
    /// <remarks>
    /// The default implementation of AcDbGripOverrule::gripStatus calls the 
    /// protected virtual AcDbEntity::subGripStatus method. 
    /// </remarks> 
    ACDBCORE2D_PORT  virtual void gripStatus(AcDbEntity* pSubject, const AcDb::GripStat status);
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbSubentityOverrule overrules a subset of subentity related operations that 
/// AcDbEntity class specifies. It is intended as a base class for clients who 
/// want to alter some or all behavior of a given AcDbEntity-derived class. At 
/// the base level, each default implementation simply calls the corresponding 
/// method in the target class.
/// </description>
class AcDbSubentityOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSubentityOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbSubentityOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subAddSubentPaths.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="newPaths">Input an array of AcDbFullSubentPath identifiers 
    /// to add to the entity.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::addSubentPaths calls 
    /// the protected virtual AcDbEntity::subAddSubentPaths method. 
    /// </remarks> 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus addSubentPaths(AcDbEntity* pSubject, const AcDbFullSubentPathArray& newPaths);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subDeleteSubentPaths.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="paths">Input an array of AcDbFullSubentPath identifiers to 
    /// delete from the entity.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::deleteSubentPaths calls 
    /// the protected virtual AcDbEntity::subDeleteSubentPaths method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus deleteSubentPaths(AcDbEntity* pSubject, const AcDbFullSubentPathArray& paths);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subTransformSubentPathsBy.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="paths">Input an array of one or more AcDbFullSubentPath 
    /// objects identifying the subentities to transform.</param>
    /// <param name="xform">Input the WCS transformation to apply to each of the 
    /// supplied subentities.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::transformSubentPathsBy 
    /// calls the protected virtual AcDbEntity::subTransformSubentPathsBy method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus transformSubentPathsBy(AcDbEntity* pSubject,
                                            const AcDbFullSubentPathArray& paths,
                                            const AcGeMatrix3d&            xform);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetGripPointsAtSubentPath.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="path">Input the AcDbFullSubentPath to the subentity.</param>
    /// <param name="grips">Output an array of pointers to dynamically allocated 
    /// AcDbGripData objects, one for each grip point in the subentity.</param>
    /// <param name="curViewUnitSize">Input size, in pixels, of one drawing unit 
    /// in the current viewport.</param>
    /// <param name="gripSize">Input current grip size, in pixels.</param>
    /// <param name="curViewDir">Input vector describing the view direction in 
    /// the current viewport.</param>
    /// <param name="bitflags">Input bitmap of one or more flags specified by the 
    /// GetGripPointsFlags enumeration.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::getGripPointsAtSubentPath 
    /// calls the protected virtual AcDbEntity::subGetGripPointsAtSubentPath method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getGripPointsAtSubentPath(
                                   const AcDbEntity*              pSubject,
                                   const AcDbFullSubentPath&      path,
                                   AcDbGripDataPtrArray&          grips,
                                   const double                   curViewUnitSize,
                                   const int                      gripSize,
                                   const AcGeVector3d&            curViewDir,
                                   const int                      bitflags);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subMoveGripPointsAtSubentPaths.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="paths">Input.</param>
    /// <param name="gripAppData">Input an array of pointers, one for each grip 
    /// point to be moved; these are the appData pointers from the AcDbGripData 
    /// objects for the grip points to be moved.</param>
    /// <param name="offset">Input the vector, in WCS coordinates, indicating the 
    /// direction and magnitude of the translation to be applied to the grips.</param>
    /// <param name="bitflags">Reserved for future use; currently zero.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::moveGripPointsAtSubentPaths 
    /// calls the protected virtual AcDbEntity::subMoveGripPointsAtSubentPaths method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus moveGripPointsAtSubentPaths(
                                    AcDbEntity*                    pSubject,
                                    const AcDbFullSubentPathArray& paths,
                                    const AcDbVoidPtrArray&        gripAppData,
                                    const AcGeVector3d&            offset,
                                    const int                      bitflags);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetSubentPathsAtGsMarker.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="type">Input subentity type desired; possible SubentTypes are 
    /// AcDb::kFaceSubentType, AcDb::kEdgeSubentType, AcDb::kVertexSubentType, 
    /// AcDb::kMlineSubentCache.</param>
    /// <param name="gsMark">Input GS marker representing a specific subentity 
    /// (typically obtained from ads_ssnamex()).</param>
    /// <param name="pickPoint">Input point (in WCS coordinates) picked during 
    /// selection of the entity (this point will be on or very near the desired 
    /// subentity) .</param>
    /// <param name="viewXform">Input transformation matrix to transform from WCS 
    /// to DCS.</param>
    /// <param name="numPaths">Output number of AcDbFullSubentPath objects in the 
    /// subentPaths array.</param>
    /// <param name="subentPaths">Output address of a dynamically allocated array 
    /// of one or more AcDbFullSubentPaths generated from the GS marker and other 
    /// information passed into this function.</param>
    /// <param name="numInserts">Input number of object IDs for AcDbBlockReferences 
    /// in entAndInsertStack (should be one less than the total number of entries 
    /// in entAndInsertStack because the first entry is the entity itself, which 
    /// is not a BlockReference). If the entity is directly owned by the model or 
    /// paper space BlockTableRecords, then leave this argument out so its default 
    /// of 0 will be used.</param>
    /// <param name="entAndInsertStack">Input array of objectIds of the objects 
    /// that are the nested containers of the subentity. The list is in order from 
    /// the "main" entity that the subentity is a part of, out to the outermost 
    /// AcDbBlockReference that is in model or paper space. If the entity is 
    /// itself directly owned by model or paper space, then leave this argument 
    /// out so that its default of NULL will be used.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::getSubentPathsAtGsMarker 
    /// calls the protected virtual AcDbEntity::subGetSubentPathsAtGsMarker method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual  Acad::ErrorStatus getSubentPathsAtGsMarker(
                                    const AcDbEntity*      pSubject,
                                    AcDb::SubentType       type,
                                    Adesk::GsMarker        gsMark, 
                                    const AcGePoint3d&     pickPoint,
                                    const AcGeMatrix3d&    viewXform, 
                                    int&                   numPaths,
                                    AcDbFullSubentPath*&   subentPaths, 
                                    int                    numInserts = 0,
                                    AcDbObjectId*          entAndInsertStack = NULL);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetGsMarkersAtSubentPath.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="subPath">Input AcDbFullSubentPath object that contains an 
    /// AcDbSubentId object with the information necessary to determine the 
    /// subentity (or subentities) for which the GS Marker(s) is requested.</param>
    /// <param name="gsMarkers">Output array with the GSMarker(s) for the subentity 
    /// (or subentities).</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::getGsMarkersAtSubentPath 
    /// calls the protected virtual AcDbEntity::subGetGsMarkersAtSubentPath method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual  Acad::ErrorStatus getGsMarkersAtSubentPath(
                                    const AcDbEntity*         pSubject,
                                    const AcDbFullSubentPath& subPath, 
                                    AcArray<Adesk::GsMarker>& gsMarkers);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subentPtr.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="id">Input AcDbFullSubentPath that identifies the subentity 
    /// to be copied.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::subentPtr calls the 
    /// protected virtual AcDbEntity::subentPtr method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual AcDbEntity* subentPtr(const AcDbEntity* pSubject, const AcDbFullSubentPath& id);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subentGripStatus.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="status">Input the status of the grip operation.</param>
    /// <param name="subentity">Input the subentity on the object whose grip 
    /// status changed.</param>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::subentGripStatus 
    /// calls the protected virtual AcDbEntity::subentGripStatus method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual void        subentGripStatus(
                                        AcDbEntity*               pSubject,
                                        const AcDb::GripStat      status,
                                        const AcDbFullSubentPath& subentity);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetCompoundObjectTransform.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="xMat">Output filled in with transformation matrix used for 
    /// nested objects.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::getCompoundObjectTransform 
    /// calls the protected virtual AcDbEntity::subGetCompoundObjectTransform method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getCompoundObjectTransform(const AcDbEntity* pSubject, AcGeMatrix3d & xMat);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetSubentPathGeomExtents.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="path">Input the path to the subentity.</param>
    /// <param name="extents">Output geometric extents, expressed in world 
    /// coordinates, of the subentity.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::getSubentPathGeomExtents 
    /// calls the protected virtual AcDbEntity::subGetSubentPathGeomExtents method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getSubentPathGeomExtents(const AcDbEntity* pSubject,
                                    const AcDbFullSubentPath& path, 
                                    AcDbExtents&              extents);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetSubentClassId.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="path">Input the path to the subentity.</param>
    /// <param name="clsId">Output a pointer to a CLSID structure whose contents 
    /// are set to the CLSID of the wrapper for the subentity.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbSubentityOverrule::getSubentClassId 
    /// calls the protected virtual AcDbEntity::subGetSubentClassId method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getSubentClassId(const AcDbEntity* pSubject,
                                    const AcDbFullSubentPath& path,
                                    CLSID*                    clsId);
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbHighlightOverrule overrules a subset of highlight related operations that 
/// AcDbEntity class specifies. It is intended as a base class for clients who 
/// want to alter some or all behavior of a given AcDbEntity-derived class. At 
/// the base level, each default implementation simply calls the corresponding 
/// method in the target class.
/// </description>
class AcDbHighlightOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbHighlightOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbHighlightOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subHighlight.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="subId">Input AcDbFullSubentPath that identifies the 
    /// subentity to highlight .</param>
    /// <param name="highlightAll">Input Boolean indicating whether to highlight 
    /// in all viewports.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbHighlightOverrule::highlight calls the 
    /// protected virtual AcDbEntity::subHighlight method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus highlight(
                                const AcDbEntity*      pSubject,
                                const AcDbFullSubentPath& subId = kNullSubent,
                                const Adesk::Boolean highlightAll = false);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subUnhighlight.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="subId">Input AcDbFullSubentPath that identifies the 
    /// subentity to highlight .</param>
    /// <param name="highlightAll">Input Boolean indicating whether to highlight 
    /// in all viewports.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbHighlightOverrule::unhighlight calls the 
    /// protected virtual AcDbEntity::subUnhighlight method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus unhighlight(
                                    const AcDbEntity*      pSubject,
                                    const AcDbFullSubentPath& subId = kNullSubent, 
                                    const Adesk::Boolean highlightAll = false);
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbHighlightStateOverrule overrules a subset of highlight style related
/// operations that AcDbEntity class specifies. It is intended as a base class
/// for clients who want to alter some or all behavior of a given
/// AcDbEntity-derived class. At the base level, each default implementation
/// simply calls the corresponding method in the target class.
/// </description>
class AcDbHighlightStateOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbHighlightStateOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbHighlightStateOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::pushHighlight.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="subId">Input AcDbFullSubentPath that identifies the 
    /// subentity to push highlight .</param>
    /// <param name="highlightStyle">Input AcGiHighlightStyle indicating
    /// highlight style.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbHighlightStateOverrule::pushHighlight calls
    /// the protected AcDbEntity::subPushHighlight method.
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus  pushHighlight(
                                    AcDbEntity*               pSubject,
                                    const AcDbFullSubentPath& subId,
                                    AcGiHighlightStyle        highlightStyle);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::popHighlight.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="subId">Input AcDbFullSubentPath that identifies the 
    /// subentity to pop highlight .</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbHighlightStateOverrule::popHighlight calls
    /// the protected AcDbEntity::subPopHighlight method.
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus  popHighlight(
                                    AcDbEntity*               pSubject,
                                    const AcDbFullSubentPath& subId);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::highlightState.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="subId">Input AcDbFullSubentPath that identifies the 
    /// subentity to get current highlight style.</param>
    /// <returns>Returns highlight style of input subent.</returns>
    /// <remarks>
    /// The default implementation of AcDbHighlightStateOverrule::highlightState calls
    /// the protected AcDbEntity::subHighlightState method.
    /// </remarks>
    ACDBCORE2D_PORT virtual AcGiHighlightStyle highlightState(
                                    AcDbEntity*               pSubject,
                                    const AcDbFullSubentPath& subId);
};

/// <property name="versionspecific" value="=18.1.0.0" />
/// 
/// <description>
/// AcDbVisibilityOverrule overrules a subset of visibility-related operations that 
/// AcDbEntity class specifies. It is intended as a base class for clients who 
/// want to alter some or all behavior of a given AcDbEntity-derived class. At 
/// the base level, each default implementation simply calls the corresponding 
/// method in the target class.
/// </description>
class AcDbVisibilityOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbVisibilityOverrule);

    /// <property name="versionspecific" value="=18.1.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>
    ACDBCORE2D_PORT AcDbVisibilityOverrule();

    /// <property name="versionspecific" value="=18.1.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subVisibility.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <returns>Returns the visibility state of the object or overrule.</returns>
    /// <remarks>
    /// The default implementation of AcDbVisibilityOverrule::visibility calls the 
    /// protected AcDbEntity::subVisibility method.
    /// </remarks>
    ACDBCORE2D_PORT virtual AcDb::Visibility visibility(const AcDbEntity* pSubject);

    /// <property name="versionspecific" value="=18.1.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subSetVisibility.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="newVal">The new visibility state.</param>
    /// <param name="doSubents">Pass in true if the new value should apply to 
    /// subentitites.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbVisibilityOverrule::setVisibility calls the 
    /// protected AcDbEntity::subSetVisibility method.
    /// </remarks>
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setVisibility(AcDbEntity* pSubject,
                                    AcDb::Visibility newVal,
                                    Adesk::Boolean doSubents = true);
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcDbGeometryOverrule overrules a subset of geometry related operations that 
/// AcDbEntity class specifies. It is intended as a base class for clients who 
/// want to alter some or all behavior of a given AcDbEntity-derived class. At 
/// the base level, each default implementation simply calls the corresponding 
/// method in the target class.
/// </description>
class AcDbGeometryOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGeometryOverrule);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Default Constructor.
    /// </description>  
    ACDBCORE2D_PORT AcDbGeometryOverrule();

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subIntersectWith.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="pEnt">Input entity with which "this" entity is to intersect.
    /// </param>
    /// <param name="intType">Input type of intersection requested.</param>
    /// <param name="points">Output with the points of intersection appended.</param>
    /// <param name="thisGsMarker">Input GS marker of subentity of "this" entity 
    /// that's involved in the intersection operation. Use the 0 default if not 
    /// applicable.</param>
    /// <param name="otherGsMarker">Input GS marker of subentity of the entity 
    /// pointed to by pEnt that's involved in the intersection operation. Use 
    /// the 0 default if not applicable.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbGeometryOverrule::intersectWith calls 
    /// the protected virtual AcDbEntity::subIntersectWith method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual  Acad::ErrorStatus intersectWith(
                                            const AcDbEntity* pSubject,
                                            const AcDbEntity* pEnt,
                                            AcDb::Intersect intType, 
                                            AcGePoint3dArray& points,
                                            Adesk::GsMarker thisGsMarker = 0, 
                                            Adesk::GsMarker otherGsMarker = 0);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subIntersectWith.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="pEnt">Input entity with which "this" entity is to intersect.
    /// </param>
    /// <param name="intType">Input type of intersection requested.</param>
    /// <param name="projPlane">Input projection plane for the apparent 
    /// intersection of the two entities.</param>
    /// <param name="points">Output with the points of intersection appended.</param>
    /// <param name="thisGsMarker">Input GS marker of subentity of "this" entity 
    /// that's involved in the intersection operation. Use the 0 default if not 
    /// applicable.</param>
    /// <param name="otherGsMarker">Input GS marker of subentity of the entity 
    /// pointed to by pEnt that's involved in the intersection operation. Use 
    /// the 0 default if not applicable.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbGeometryOverrule::intersectWith calls 
    /// the protected virtual AcDbEntity::subIntersectWith method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual  Acad::ErrorStatus intersectWith(
                                            const AcDbEntity* pSubject,
                                            const AcDbEntity* pEnt,
                                            AcDb::Intersect intType, 
                                            const AcGePlane& projPlane,
                                            AcGePoint3dArray& points, 
                                            Adesk::GsMarker thisGsMarker = 0,
                                            Adesk::GsMarker otherGsMarker = 0);

    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcDbEntity::subGetGeomExtents.
    /// </description>
    /// <param name="pSubject">Pointer to an AcDbEntity that this overrule is 
    /// applied against.</param>
    /// <param name="extents">Output entity's extents.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    /// <remarks>
    /// The default implementation of AcDbGeometryOverrule::getGeomExtents calls 
    /// the protected virtual AcDbEntity::subGetGeomExtents method. 
    /// </remarks>
    ACDBCORE2D_PORT virtual  Acad::ErrorStatus getGeomExtents(const AcDbEntity* pSubject, AcDbExtents& extents);
};

#pragma pack (pop)
