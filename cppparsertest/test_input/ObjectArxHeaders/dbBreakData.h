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

#include "dbmain.h"

#pragma pack (push, 8)

class AcDbBreakPointRef;

class AcDbBreakData : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBreakData);

    AcDbBreakData();
    virtual ~AcDbBreakData();
    
    AcDbObjectId dimObjId() const;
    Acad::ErrorStatus setDimObjId(const AcDbObjectId& dimId);

    Acad::ErrorStatus addBreakPointRef(AcDbBreakPointRef* ptRef);
    Acad::ErrorStatus getBreakPointRef(int lineIndex, 
                              AcArray<AcDbBreakPointRef*>& ptRefs) const;
    Acad::ErrorStatus getBreakPointRef(AcArray<AcDbBreakPointRef*>& ptRefs) const;
    Acad::ErrorStatus deleteAllBreakPointRefs();
    Acad::ErrorStatus removeAssociativity(bool force = true);
    Acad::ErrorStatus postToDb(AcDbObjectId& breakObjId);
    Acad::ErrorStatus eraseFromDb(void); 

    //********************************************************************
    // Overridden methods from AcDbObject
    //********************************************************************
    //
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const override;

    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const override;

    virtual void  modifiedGraphics(const AcDbEntity* pEnt) override;

    //********************************************************************
    //  APIs for Internal use only
    //********************************************************************
    //
    Acad::ErrorStatus updateAssociativity(const AcDbObjectIdArray& ids, int cmdType);
};

class AcDbBreakPointRef : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBreakPointRef);

    enum BreakPointType { 
        kDynamic           = 0,
        kStatic            = 1,
        kStatic2Point      = 2
    };

    AcDbBreakPointRef();
    virtual ~AcDbBreakPointRef();

    AcDbBreakPointRef::BreakPointType pointType() const;
    Acad::ErrorStatus setPointType(AcDbBreakPointRef::BreakPointType newVal);
    Adesk::Int32 lineIndex() const;
    Acad::ErrorStatus setLineIndex(Adesk::Int32 index);
    AcGePoint3d breakPoint() const;
    Acad::ErrorStatus setBreakPoint(const AcGePoint3d& pt);
    AcGePoint3d breakPoint2() const;
    Acad::ErrorStatus setBreakPoint2(const AcGePoint3d& pt);
    Acad::ErrorStatus getBreakPointId(AcDbFullSubentPath& idPath) const;
    Acad::ErrorStatus setBreakPointId(const AcDbFullSubentPath& idPath);
    AcDbEntity *subentPtr() const;
    Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt,
                                    AcGePoint3dArray& points,
                                    AcGePoint3dArray& textBoxPts);
 
    //********************************************************************
    // Overridden methods from AcDbObject
    //********************************************************************
    //
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const override;

    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const override;
};

//************************************************************************
//  Global API functions 
//************************************************************************
//
Acad::ErrorStatus acdbGetBreakSubentIndex(AcDbEntity* pEnt,
                                     const AcGePoint3d& pickPt, 
                                     const AcGeVector3d& viewDir, 
                                     int& subentIndex,
                                     AcGePoint3d& ptOnEnt,
                                     const AcGeTol& tol = AcGeContext::gTol);

#pragma pack (pop)

