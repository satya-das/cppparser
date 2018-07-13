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
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "dbmain.h"
#include "AcString.h"

#pragma pack (push, 8)

#ifndef ACSYNERGY_PORT
#define ACSYNERGY_PORT
#endif


class AcDbImpViewSymbol;
class AcRxSymbolSketch;
class AcDbAssocViewSymbolConstrGrpPE;

//
class ACSYNERGY_PORT AcDbViewSymbol : public AcDbEntity
{
    friend class AcDbViewSymbolSystemInternals;
public:
    ACRX_DECLARE_MEMBERS(AcDbViewSymbol);

    virtual ~AcDbViewSymbol();

    AcDbObjectId                symbolStyleId() const;
    void                        setSymbolStyleId(const AcDbObjectId& styleId);

    double                      scale() const;
    void                        setScale(double val);

    Acad::ErrorStatus           getIdentifier(ACHAR*& pszName) const;
    Acad::ErrorStatus           getIdentifier(AcString& sName) const;
    Acad::ErrorStatus           setIdentifier(const AcString& sName);


    // Internal use only methods:
    AcDbObjectId                owningViewRep() const;
    void                        setOwningViewRep(const AcDbObjectId& owner);
    Acad::ErrorStatus           createDefinition(AcRxSymbolSketch* pSketchObject);
    Acad::ErrorStatus           exportSymbolGeometry(AcArray<AcGeCurve3d*>& geomArr, const AcDbObjectId& viewRepId);
    Acad::ErrorStatus           setSymbolGeometry(const AcDbObjectIdArray& entIds);
    Acad::ErrorStatus           setSymbolGeometry(const AcArray<AcDbObject*>& entities);
	Acad::ErrorStatus			updateDefinition();


    // AcGiDrawable protocols
    virtual Adesk::Boolean      subWorldDraw(AcGiWorldDraw* pWd);

    // AcDbObject protocols
    virtual Acad::ErrorStatus   subErase(Adesk::Boolean erasing);
    void                        objectClosed(const AcDbObjectId dbObjId);
    virtual Acad::ErrorStatus   subClose ();

    virtual void                subSetDatabaseDefaults(AcDbDatabase* pDb);

    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo);

    virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;

    virtual Acad::ErrorStatus   subGetOsnapPoints(AcDb::OsnapMode     osnapMode,
                                                  INT_PTR             gsSelMarkPtr,
                                                  const AcGePoint3d&  pickPoint,
                                                  const AcGePoint3d&  lastPoint,
                                                  const AcGeMatrix3d& viewXform,
                                                  AcGePoint3dArray&   snapPoints,
                                                  AcDbIntArray&       geomIds) const;

    virtual Acad::ErrorStatus   subTransformBy(const AcGeMatrix3d& xform);

    virtual void                subGripStatus(const AcDb::GripStat status);
    virtual Acad::ErrorStatus   subGetGripPoints(AcDbGripDataPtrArray& grips, 
                                                 const double curViewUnitSize, 
                                                 const int gripSize, 
                                                 const AcGeVector3d& curViewDir, 
                                                 const int bitflags) const;
    virtual Acad::ErrorStatus   subMoveGripPointsAt(const AcDbVoidPtrArray& gripAppData,
                                                 const AcGeVector3d& offset, 
                                                 const int bitflags);

    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const;

    virtual void                subList() const;

    virtual void                saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);

protected:
    // Makes AcDbViewSymbol an abstract class.
    AcDbViewSymbol();

private:

    friend class AcDbAssocViewSymbolConstrGrpPE;
	AcDbImpViewSymbol*          mpImpSymbol;
};

#pragma pack (pop)
