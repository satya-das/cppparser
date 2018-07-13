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
// DESCRIPTION: Exported AcDbMline Entity class
//  dbmline.h - multi-line entity

#ifndef AD_DBMLINE_H
#define AD_DBMLINE_H

#include "dbmain.h"

#pragma pack(push, 8)

struct Mline
{
    typedef Adesk::Int8 MlineJustification;
    enum {
        kTop        = 0,
        kZero       = 1,
        kBottom     = 2
    };
    enum {
        kOpen         = 0,
        kClosed       = 1,
        kMerged       = 2
    };
};

class AcGePlane;

class AcDbMline: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbMline);
    AcDbMline();
    virtual ~AcDbMline();

    Acad::ErrorStatus setStyle(const AcDbObjectId &newStyleId);
    AcDbObjectId      style() const;

    Acad::ErrorStatus setJustification(Mline::MlineJustification newJust);
    Mline::MlineJustification justification() const;

    Acad::ErrorStatus setScale(double newScale);
    double            scale() const;

    AcGeVector3d      normal            () const;
    Acad::ErrorStatus setNormal(const AcGeVector3d & newNormal);

    Acad::ErrorStatus appendSeg(const AcGePoint3d& newVertex);
    Acad::ErrorStatus removeLastSeg(AcGePoint3d& lastVertex);

    Acad::ErrorStatus moveVertexAt(int index, const AcGePoint3d& newPosition);

    Acad::ErrorStatus setClosedMline(bool closed);
    bool              closedMline() const;

    void              setSupressStartCaps(bool supressIt);
    bool              supressStartCaps() const;
    void              setSupressEndCaps(bool supressIt);
    bool              supressEndCaps() const;

    int               numVertices() const;
    int               element(const AcGePoint3d & pt) const;
    AcGePoint3d       vertexAt(int index) const;

    AcGeVector3d      axisAt(int index) const;
    AcGeVector3d      miterAt(int index) const;
    Acad::ErrorStatus getParametersAt(int index,
                                      AcGeVoidPointerArray& params) const;
    Acad::ErrorStatus setParametersAt(int index,
                                            AcGeVoidPointerArray& params);
    Acad::ErrorStatus getClosestPointTo(
                         const AcGePoint3d& givenPoint,
                         AcGePoint3d& pointOnCurve, 
                         bool extend,
                         bool excludeCaps = false) const;
    Acad::ErrorStatus getClosestPointTo(
                         const AcGePoint3d& givenPoint,
                         const AcGeVector3d& normal, 
                         AcGePoint3d& pointOnCurve,
                         bool extend,
                         bool excludeCaps = false) const;

    void              getPlane(AcGePlane&) const;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

#pragma pack(pop)

#endif
