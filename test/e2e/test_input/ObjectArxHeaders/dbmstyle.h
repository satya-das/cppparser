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

#ifndef AD_DBMLINESTYLE_H
#define AD_DBMLINESTYLE_H

#include "dbmain.h"
#include "AdAChar.h"

#pragma pack (push, 8)

#define MSTYLE_NAME_LENGTH 32
#define MSTYLE_DESCRIPTION_LENGTH 256
#define LTYPE_LENGTH 32
#define MLINE_MAX_ELEMENTS 16

// 10 degrees
//
#define MIN_ANGLE (10.0 * PI / 180.0)

// 170 degrees
//
#define MAX_ANGLE (170.0 * PI / 180.0)

#define MSTYLE_DXF_FILL_ON           (0x1)
#define MSTYLE_DXF_SHOW_MITERS       (0x2)
#define MSTYLE_DXF_START_SQUARE_CAP  (0x10)
#define MSTYLE_DXF_START_INNER_ARCS  (0x20)
#define MSTYLE_DXF_START_ROUND_CAP   (0x40)
#define MSTYLE_DXF_END_SQUARE_CAP    (0x100)
#define MSTYLE_DXF_END_INNER_ARCS    (0x200)
#define MSTYLE_DXF_END_ROUND_CAP     (0x400)
#define MSTYLE_DXF_JUST_TOP          (0x1000)
#define MSTYLE_DXF_JUST_ZERO         (0x2000)
#define MSTYLE_DXF_JUST_BOT          (0x4000)

class AcDbMlineStyle: public  AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbMlineStyle);
    AcDbMlineStyle();
    virtual ~AcDbMlineStyle();

    void              initMlineStyle();
    void              set(const AcDbMlineStyle & src, 
                          bool checkIfReferenced = true);

    Acad::ErrorStatus setDescription(const ACHAR * description);
    const ACHAR*       description() const;

    Acad::ErrorStatus setName(const ACHAR * name);
    const ACHAR*       name() const;

    void              setShowMiters(bool showThem);
    bool              showMiters() const;

    void              setStartSquareCap(bool showIt);
    bool              startSquareCap() const;

    void              setStartRoundCap(bool showIt);
    bool              startRoundCap() const;

    void              setStartInnerArcs(bool showThem);
    bool              startInnerArcs() const;

    void              setEndSquareCap(bool showIt);
    bool              endSquareCap() const;

    void              setEndRoundCap(bool showIt);
    bool              endRoundCap() const;

    void              setEndInnerArcs(bool showThem);
    bool              endInnerArcs() const;

    Acad::ErrorStatus setFillColor(const AcCmColor& color);
    const AcCmColor&  fillColor() const;

    void              setFilled(bool onOff);
    bool              filled() const;

    Acad::ErrorStatus setStartAngle(double ang);
    double            startAngle() const;

    Acad::ErrorStatus setEndAngle(double ang);
    double            endAngle() const;

    Acad::ErrorStatus addElement(int& index, double offset,
                                 const AcCmColor &color,
                                 AcDbObjectId linetypeId,
                                 bool checkIfReferenced = true);
    Acad::ErrorStatus removeElementAt(int elem);

    int numElements() const;

    Acad::ErrorStatus setElement(int & elem, double offset,
                                 const AcCmColor &color,
                                 AcDbObjectId linetypeId);

    Acad::ErrorStatus getElementAt(int elem, double& offset,
                                   AcCmColor & color,
                                   AcDbObjectId & linetypeId) const;

    // --- AcDbObject Protocol
    //
    virtual Acad::ErrorStatus subErase     (Adesk::Boolean pErasing = true) override;
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* filer) const override;

    // --- AcRxObject Protocol
    //
    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other) override;

};

#pragma pack (pop)

#endif
