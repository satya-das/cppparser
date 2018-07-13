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
// FILE: dimassoc.h
//
// DESCRIPTION: Declaration for Dimension Associativity API 
//              and AcDbDimAssoc class.

#ifndef AD_DBDIMASSOC_H
#define AD_DBDIMASSOC_H

#include "dbmain.h"

class AcDb2LineAngularDimension;
class AcDb3PointAngularDimension;
class AcDbAlignedDimension;
class AcDbArcDimension;
class AcDbDiametricDimension;
class AcDbLeader;
class AcDbMLeader;
class AcDbOrdinateDimension;
class AcDbPointRef;
class AcDbRadialDimension;
class AcDbRadialDimensionLarge;
class AcDbRotatedDimension;

// Exported AcDbDimAssoc class and some global APIs for external use.

// Class declaration for AcDbDimAssoc
//
class AcDbDimAssoc : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDimAssoc);
    //ACRX_DECLARE_MEMBERS(AcDbDimAssoc);

    enum { kMaxPointRefs = 4 };

    enum PointType {
        kXline1Point      = 0,
        kXline2Point      = 1,
        kOriginPoint      = 0,
        kDefiningPoint    = 1,
        kXline1Start      = 0,
        kXline1End        = 1,
        kXline2Start      = 2,
        kXline2End        = 3,
        kVertexPoint      = 2,
        kChordPoint       = 0,
        kCenterPoint      = 1,
        kFarChordPoint    = 1,
        kOverrideCenterPoint   = 2,
        kAngLineStart     = 2,
        kJogPoint         = 3,
        kAngLineEnd       = 3,
        kLeaderPoint      = 0
    };

    enum AssocFlags {
        kFirstPointRef     = 1,
        kSecondPointRef    = 2,
        kThirdPointRef     = 4,
        kFourthPointRef    = 8
    };

    enum RotatedDimType {
        kUnknown       = 0,
        kParallel      = 1,
        kPerpendicular = 2
    };

    AcDbDimAssoc();
    virtual ~AcDbDimAssoc();
    AcDbObjectId dimObjId() const;
    Acad::ErrorStatus setDimObjId(const AcDbObjectId& dimId);
    Acad::ErrorStatus setAssocFlag(int ptType, bool value);
    void setAssocFlag(int assocFlg);
    bool assocFlag(int ptType) const;
    int assocFlag(void);
    Acad::ErrorStatus setPointRef(int ptType, AcDbPointRef* ptRef);
    const AcDbPointRef *pointRef(int ptType) const;
    Acad::ErrorStatus setRotatedDimType(RotatedDimType dimType);
    RotatedDimType    rotatedDimType() const;
    Acad::ErrorStatus addToPointRefReactor();
    Acad::ErrorStatus addToDimensionReactor(bool isAdd = true);
    Acad::ErrorStatus removePointRef(int ptType);
    Acad::ErrorStatus updateDimension(bool update = true, bool skipReactors = false);
    Acad::ErrorStatus removeAssociativity(bool force = true);
    bool              isTransSpatial() const;
    Acad::ErrorStatus setTransSpatial(bool value);
    Acad::ErrorStatus startCmdWatcher();

    Acad::ErrorStatus startOopsWatcher(bool bAddAll = true);
    void              removeOopsWatcher(void);
    Acad::ErrorStatus restoreAssocFromOopsWatcher(void);
    bool              hasOopsWatcher(void) const;
    Acad::ErrorStatus post(AcDbObjectId dimId, 
                           AcDbObjectId& dimAssocId, 
                           bool isActive = true);
    Acad::ErrorStatus getDimAssocGeomIds(AcDbObjectIdArray& geomIds) const;
    bool              isAllGeomErased() const;

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler*) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler*) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const override;
    virtual void modifiedGraphics(const AcDbEntity* pObj) override;

    virtual Acad::ErrorStatus swapReferences (const AcDbIdMapping& idMap) override;


    Acad::ErrorStatus updateFillet(const AcDbObjectIdArray& ids);
    Acad::ErrorStatus updateAssociativity(const AcDbObjectIdArray& ids);
    Acad::ErrorStatus updateXrefSubentPath();
    Acad::ErrorStatus updateSubentPath(AcDbIdMapping& idMap);
    void updateDueToMirror(bool wasInMirror);

protected:
    Acad::ErrorStatus   setPointRefReactor  (int ptType, 
                                             bool isAdd = true);
    Acad::ErrorStatus   removeDimExtDict    (void);
    bool                isPointBetweenRays  (const AcGePoint3d& vertex, 
                                             const AcGePoint3d& firstPt, 
                                             const AcGePoint3d& secondPt, 
                                             const AcGePoint3d& angPt,
                                             const AcGeVector3d& normal);
    Acad::ErrorStatus   updateDimension     (AcDbRotatedDimension* pRotDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbAlignedDimension* pAlnDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbRadialDimension* pRadDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbRadialDimensionLarge* pRadDimLarge, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbDiametricDimension* pDiaDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDb2LineAngularDimension* pA2Dim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDb3PointAngularDimension* pA3Dim,
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbOrdinateDimension* pOrdDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbArcDimension* pArcDim, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbLeader* pLeader, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimension     (AcDbMLeader* pMLeader, 
                                             AcGePoint3d* pNewPts, 
                                             bool bUpdate = true);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDbRotatedDimension* pAlnDim, 
                                             const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d* kpNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDbAlignedDimension* pAlnDim, 
                                             const AcGePoint3d* pOldPts, 
                                             const AcGePoint3d* pNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDb2LineAngularDimension* pA2Dim, 
                                             const AcGePoint3d* pOldPts, 
                                             const AcGePoint3d* pNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDb3PointAngularDimension* pA3Dim, 
                                             const AcGePoint3d* pOldPts, 
                                             const AcGePoint3d* pNewPts);
    Acad::ErrorStatus   updateDimLineAndTextLocation(AcDbArcDimension* pArcDim, 
                                             const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d* kpNewPts);
    Acad::ErrorStatus   calculate3PointAngDimArcLocation(const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d& kOldArcPt, 
                                             const AcGePoint3d& kOldTextPt, 
                                             const AcGePoint3d* kpNewPts, 
                                             const AcGeVector3d& normal, 
                                             AcGePoint3d& newArcPt, 
                                             AcGePoint3d& newTextPt);
    Acad::ErrorStatus   calculate2LineAngDimArcLocation(const AcGePoint3d* kpOldPts, 
                                             const AcGePoint3d& kOldArcPt, 
                                             const AcGePoint3d& kOldTextPt, 
                                             const AcGePoint3d* kpNewPts, 
                                             const AcGeVector3d& kNormal, 
                                             AcGePoint3d& newArcPt, 
                                             AcGePoint3d& newTextPt);
};

// Post pDimAssoc object to database in the extension 
// dictionary of the given dimension.
//
Acad::ErrorStatus
acdbPostDimAssoc(AcDbObjectId dimId, AcDbDimAssoc* pDimAssoc, 
                 AcDbObjectId& dimAssocId, bool isActive = true);

// Perform forced update for the given associative dimension.
// 
Acad::ErrorStatus
acdbUpdateDimension(AcDbObjectId dimId);

// Perform forced update for the all dimensions in the database (DIMREGEN)
// 
Acad::ErrorStatus
acdbUpdateAllDimensions(AcDbDatabase* pDb);

// Get the AcDbDimAssoc objectId from the given dimension.
//
Acad::ErrorStatus
acdbGetDimAssocId(AcDbObjectId dimId, AcDbObjectId& dimAssocId);

// Get the AcDbDimAssoc objectId from the geometry in 
// AcDbPointRef object.
//
Acad::ErrorStatus
acdbGetDimAssocIds(AcDbObjectId entId, AcDbObjectIdArray& dimAssocIds);

// Verify whether the given idPath is a trans-spatial path
//
bool
acdbIsTransSpatial(const AcDbFullSubentPath& idPath);

/// Get the object id of the annotation action body associated to
/// idDim. Annotations include dimension, leader, and mleader. If 
/// such associativity does not exist, returns Acad::eNotApplicable.
/// 
ACDBCORE2D_PORT Acad::ErrorStatus
acdbGetAssocAnnotationActionBody(const AcDbObjectId& idDim,
                                 AcDbObjectId& idActionBody
                                );

// Get all non-associative annotations in model space or paper space.
// The annotations may include dimension, leader, mleader, and any custom
// objects which have AcDbAnnoMonitorPE implemented.
//
ACDBCORE2D_PORT Acad::ErrorStatus 
acdbGetNonAssocAnnotations(AcDbDatabase* pDb, bool isPaperSpace, AcDbObjectId& blockId,
                           AcDbObjectIdArray& annoIds, bool ignoreOffOrFrozenLayers = false);

// Check if the specified pEnt resides in a block or external reference.
//
ACDBCORE2D_PORT bool
acdbIsEntityInBlockOrXref(const AcDbEntity* pEnt);

// Check if ANNOMONITOR sysvar is ON or OFF
//
ACDBCORE2D_PORT bool 
acdbIsAnnoMonitorOn();

// Check if associativity alert icon is disabled for the specified pEnt.
// pEnt can be AbDbDimension, AcDbMLeader or AcDbLeader
//
ACDBCORE2D_PORT bool 
acdbIsAssociativityAlertIconDisabled(AcDbEntity *pEnt);

// Disable or enable the associativity alert icon for the specified pEnt.
// pEnt can be AbDbDimension, AcDbMLeader or AcDbLeader
//
ACDBCORE2D_PORT bool 
acdbDisableAssociativityAlertIcon(AcDbEntity *pEnt, bool disable);

// Check if the specified pObj is associative or not. pObj can be
// AcDbDimension, AcDbMLeader or AcDbLeader
//
ACDBCORE2D_PORT bool 
acdbIsAssociativeAnnotation(AcDbObject* pObj, bool* pIsPartialAssoc = NULL);

class AcDbAnnoAlertDisabler
{
public:
    ACDBCORE2D_PORT AcDbAnnoAlertDisabler(const AcDbObjectId& objId);
    ACDBCORE2D_PORT ~AcDbAnnoAlertDisabler();
private:
    AcDbObjectId m_objId;
};

// Get the associativity override nValue for the specified pObj.
// nValue =  0: non-associative
// nValue =  1: associative
//
ACDBCORE2D_PORT bool
acdbGetAssociativityOverride(AcDbEntity *pEnt, int& nValue);
                      
// Set the associativity override for the specified pObj.
// nValue =  0: non-associative
// nValue =  1: associative
// nValue = -1: clean up override xData and use default associativity
//
ACDBCORE2D_PORT bool
acdbSetAssociativityOverride(AcDbEntity *pEnt, int nValue); 

#endif  //  AD_DBDIMASSOC_H
