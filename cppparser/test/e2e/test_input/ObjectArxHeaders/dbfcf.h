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
//
// DESCRIPTION:
//
// The AcDbFcf class represents a geometric tolerance as defined by
// ANSI Y14.5

#ifndef DBFCF_H
#define DBFCF_H

#include "dbmain.h"
#include "AcDbCore2dDefs.h"     // for ACDBCORE2D_PORT

#pragma pack(push, 8)

class AcDbFcf: public  AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbFcf);
                              AcDbFcf();
                              AcDbFcf(const ACHAR *, const AcGePoint3d&,
                              const AcGeVector3d&, const AcGeVector3d&);
    virtual ~AcDbFcf();

    // Geometric or visual properties.
    
    enum whichLine {kAll = -1};
    virtual void              setText          (const ACHAR *);
/// <summary>
/// Returns a single requested text line from the tolerance frame, or all lines.
/// </summary>
/// <param name="sText"> Reference to string object that receives the text string value.</param>
/// <param name="lineNo"> Input line number (0 based) of desired text line, or kAll.</param>
/// <returns> Returns Acad::eOk if success, eOutOfRange if line number is too high.</returns>
/// <remarks> When a single line is requested, the returned string does not include the
///           trailing newline ('\n') char.
///           When all lines are requested (kAll), the returned string contains the newline
///           chars that are between the lines.
///           The overload which returns ACHAR * allocates a buffer which the caller is
///           expected to free up. This overload is deprecated and will be removed in a
///           future release.
/// </remarks>
///
    ACDBCORE2D_PORT virtual Acad::ErrorStatus text(AcString & sText, int lineNo = kAll) const;
    virtual ACHAR *           text             (int lineNo = kAll) const final; // deprecated
    virtual void              setLocation      (const AcGePoint3d&);
    virtual AcGePoint3d       location         () const;
    virtual void              setOrientation   (const AcGeVector3d& norm,
                                                const AcGeVector3d& dir);
    virtual AcGeVector3d normal()    const;
    virtual AcGeVector3d direction() const;
    
    virtual void getBoundingPoints(AcGePoint3dArray&) const;
    virtual void getBoundingPline(AcGePoint3dArray&)  const;
    
    virtual void              setDimensionStyle(AcDbHardPointerId);
    virtual AcDbHardPointerId dimensionStyle() const;
    
    Acad::ErrorStatus   getDimstyleData(AcDbDimStyleTableRecord*& pRecord) const;
    Acad::ErrorStatus   setDimstyleData(AcDbDimStyleTableRecord* pNewData);
    Acad::ErrorStatus   setDimstyleData(AcDbObjectId newDataId);

    virtual void        setDimVars();

    // Dimension variable get methods in alphabetic order:
    //
    AcCmColor      dimclrd () const;
    AcCmColor      dimclrt () const;
    double         dimgap  () const;
    double         dimscale() const;
    AcDbObjectId   dimtxsty() const;
    double         dimtxt  () const;

    // Dimension variable set methods in alphabetic order:
    //
    Acad::ErrorStatus setDimclrd (AcCmColor&     val);
    Acad::ErrorStatus setDimclrt (AcCmColor&     val);
    Acad::ErrorStatus setDimgap  (double         val);
    Acad::ErrorStatus setDimscale(double         val);
    Acad::ErrorStatus setDimtxsty(AcDbObjectId   val);
    Acad::ErrorStatus setDimtxt  (double         val);

protected:
    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;

};

#pragma pack(pop)

// This overload is deprecated. Please use the one that takes an AcString & arg
// Note: returns null if line number is out of range
inline ACHAR * AcDbFcf::text(int lineNo) const
{
    AcString sText;
    if (this->text(sText, lineNo) == Acad::eOutOfRange)
        return nullptr;         // the line number requested was too high
    ACHAR *pRet = nullptr;
    ::acutNewString(sText.kwszPtr(), pRet);
    return pRet;
}
#endif

