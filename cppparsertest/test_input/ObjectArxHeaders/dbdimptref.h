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
// dimptref.h: Definition of AcDbPointRef and AcDbOsnapPointRef classes
//
// AcDbPointRef
//   AcDbOsnapPointRef
//
//
#ifndef AD_DIMREFPT_H
#define AD_DIMREFPT_H

typedef AcArray<AcDbFullSubentPath, AcArrayObjectCopyReallocator<AcDbFullSubentPath> >
    AcDbFullSubentPathArray;

typedef AcArray<AcDbHandle, AcArrayObjectCopyReallocator<AcDbHandle> >
    AcDbHandleArrayPtRef;

class AcDbPointRef : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbPointRef);

    enum OsnapType { 
        kOsnapNone         = 0,
        kOsnapEnd          = 1,
        kOsnapMid          = 2,
        kOsnapCen          = 3,
        kOsnapNode         = 4,
        kOsnapQuad         = 5, 
        kOsnapInt          = 6,
        kOsnapIns          = 7,
        kOsnapPerp         = 8,
        kOsnapTan          = 9,
        kOsnapNear         = 10,
        kOsnapApint        = 11,
        kOsnapStart        = 13
    };

	virtual AcDbPointRef& operator=(const AcDbPointRef& src);
    virtual Acad::ErrorStatus evalPoint(AcGePoint3d& pnt_wcs)=0; 
    virtual Acad::ErrorStatus getEntities(AcDbFullSubentPathArray& ents,
                              bool getLastPtRef = true) const=0;
    virtual bool              isGeomErased() const=0;
    virtual bool              isXrefObj(AcDbObjectIdArray& ids1,
                                        AcDbObjectIdArray& ids2,
                                        bool isMainObj = true) const=0;
    virtual Acad::ErrorStatus updateXrefSubentPath()=0;

    virtual Acad::ErrorStatus updateSubentPath(AcDbIdMapping& idMap)=0;

    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer,
                                           AcDbDatabase* pDb) const=0;
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer,
                                          AcDbDatabase* pDb)=0;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer,
                                           AcDbDatabase* pDb) const=0;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer,
                                          AcDbDatabase* pDb)=0;

    // Notification functions required by the AcRfGeom stuff
    //
    virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing) 
    {
        ADESK_UNREFED_PARAM(erasing);
        return Acad::eOk;
    }
    virtual Acad::ErrorStatus wblockClone(AcRxObject* pOwnerObject,
                                    AcDbObject*& pClonedObject,
                                    AcDbIdMapping& /*idMap*/,
                                    Adesk::Boolean isPrimary = Adesk::kTrue)
                                    const {
        ADESK_UNREFED_PARAM(pOwnerObject);
        ADESK_UNREFED_PARAM(pClonedObject);
        ADESK_UNREFED_PARAM(isPrimary);
        
        return Acad::eOk;
    }
    virtual Acad::ErrorStatus deepClone(AcRxObject* pOwnerObject,
                                    AcDbObject*& pClonedObject,
                                    AcDbIdMapping& /*idMap*/,
                                    Adesk::Boolean isPrimary = Adesk::kTrue)
                                    const {
        ADESK_UNREFED_PARAM(pOwnerObject);
        ADESK_UNREFED_PARAM(pClonedObject);
        ADESK_UNREFED_PARAM(isPrimary);
        
        return Acad::eOk;}
    virtual void              updateDueToMirror(bool inMirror = false)=0;

    // utility functions...
    // filing AcDbPointRef class
    static Acad::ErrorStatus  dwgInFields(AcDbDwgFiler* filer,
                                          AcDbDatabase* pDb,
                                          AcDbPointRef*& pPointRef);
    static Acad::ErrorStatus  dwgOutFields(AcDbDwgFiler* filer,
                                          AcDbDatabase* pDb,
                                          const AcDbPointRef* pPointRef);
    static Acad::ErrorStatus  dxfInFields(AcDbDxfFiler* filer,
                                          AcDbDatabase* pDb,
                                          AcDbPointRef*& pPointRef);
    static Acad::ErrorStatus  dxfOutFields(AcDbDxfFiler* filer,
                                          AcDbDatabase* pDb,
                                          const AcDbPointRef* pPointRef);
    // nested entities
    static AcDbEntity*        subentPtr(const AcDbFullSubentPath& objPath, 
                                        bool& isCloned, bool& reverseArc, bool& isStandAloneArc);
    static bool               calcTransform(const AcDbObjectIdArray& ids,
                                            AcGeMatrix3d& A_Ecs2Wcs);
    static AcGeMatrix3d       wcsToDcsMatrix(const AcDbViewport* pVPort);
    static AcGeMatrix3d       mswcsToPswcs(const AcDbViewport* pVPort);
};


class AcDbOsnapPointRef : public AcDbPointRef
{
public:
    ACRX_DECLARE_MEMBERS(AcDbOsnapPointRef);

    AcDbOsnapPointRef();
    AcDbOsnapPointRef(const AcGePoint3d& refPt);
    AcDbOsnapPointRef(AcDbPointRef::OsnapType osnapType, 
                      const AcDbFullSubentPath *objPath, 
                      const AcDbFullSubentPath *intObjPath = NULL,
                      const AcGePoint3d *refPt = NULL,
                      AcDbPointRef* lastPtRef = NULL);
	AcDbOsnapPointRef(const AcDbOsnapPointRef& src);
    virtual ~AcDbOsnapPointRef();

    virtual AcDbPointRef& operator= (const AcDbPointRef& src) override;
	AcDbOsnapPointRef& operator= (const AcDbOsnapPointRef& src);

    AcDbPointRef::OsnapType osnapType() const;
    Acad::ErrorStatus  setOsnapType(AcDbPointRef::OsnapType osnType);

    Acad::ErrorStatus  getIdPath(AcDbFullSubentPath& idPath) const;
    Acad::ErrorStatus  setIdPath(const AcDbFullSubentPath& idPath);

    Acad::ErrorStatus  getIntIdPath(AcDbFullSubentPath& intIdPath) const;
    Acad::ErrorStatus  setIntIdPath(const AcDbFullSubentPath& intIdPath);

    Acad::ErrorStatus  setLastPointRef(AcDbPointRef *ptRef);
    AcDbPointRef*      lastPointRef() const;

    Acad::ErrorStatus  setPoint(const AcGePoint3d& pt);
    AcGePoint3d        point() const;

    double             nearPointParam() const;
    Acad::ErrorStatus  setNearPointParam(double newVal);

    virtual bool       isGeomErased() const override;
    virtual bool       isXrefObj(AcDbObjectIdArray& ids1,
                                 AcDbObjectIdArray& ids2,
                                 bool isMainObj = true) const override;
    virtual Acad::ErrorStatus updateXrefSubentPath() override;
    virtual Acad::ErrorStatus updateSubentPath(AcDbIdMapping& idMap) override;
    virtual Acad::ErrorStatus evalPoint(AcGePoint3d &pt) override;

    virtual Acad::ErrorStatus getEntities(AcDbFullSubentPathArray& ents,
                                          bool getLastPtRef = true) const override;
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* pSrc) override;
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer,
                                          AcDbDatabase* pDb) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer,
                                           AcDbDatabase* pDb) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer,
                                          AcDbDatabase *pDb) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer,
                                           AcDbDatabase *pDb) const override;
    virtual void updateDueToMirror(bool inMirror = false) override;


    Acad::ErrorStatus  getXrefHandles(AcDbHandleArrayPtRef& xrefHandles) const;
    Acad::ErrorStatus  setXrefHandles(const AcDbHandleArrayPtRef& xrefHandles);

    Acad::ErrorStatus  getXrefIntHandles(AcDbHandleArrayPtRef& xrefHandles) const;
    Acad::ErrorStatus  setXrefIntHandles(const AcDbHandleArrayPtRef& xrefHandles);

    ACDBCORE2D_PORT Acad::ErrorStatus  evalPoint(AcDbPointRef::OsnapType ospType,
                                           const AcGePoint3d& lastPt,
                                           AcGePoint3d &pt);

protected:
    AcGePoint3d        nearPoint();
    double             findNearPointParam(const AcGePoint3d& pt) const;
    bool               getEllipseParams(double& sP, double& eP) const;
    bool               isTransSpatial(bool isMainObj = true) const;

    Acad::ErrorStatus  evalPointGuts(AcDbPointRef::OsnapType ospType,
                                     const AcGePoint3d& pickPt,
                                     const AcGePoint3d& lastPt,
                                     AcGePoint3d &pt);

    Acad::ErrorStatus  getIntPoints(const AcDbEntity* pEnt,
                                    const AcDbEntity* pIntEnt,
                                    AcDb::Intersect intType,
                                    AcGePoint3dArray& intPts,
                                    int gsMarker1 = 0,
                                    int gsMarker2 = 0) const;

    Acad::ErrorStatus  updateSubentPathGuts(AcDbFullSubentPath& path, 
                                            AcDbIdMapping&      idMap);

private:
    OsnapType          mOsnapType;
    AcDbFullSubentPath mObjPath;
    AcDbFullSubentPath mIntObjPath;
    double             mNearPointParam;
    AcGePoint3d        mPoint;
    AcDbPointRef*      mpLastPointRef;
    bool               mUpdateDueToMirror;

    // handle array is used for xref geometry that reside in external
    // database. We cannot use idArray because objectId is not persistent
    // after SAVE/OPEN round-tripping.
    // 
    AcDbHandleArrayPtRef    mHandleArray;
    AcDbHandleArrayPtRef    mIntHandleArray;
};

#endif /* _AD_DIMREFPT_H */
