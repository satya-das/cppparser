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
// DESCRIPTION: Exported protocol for AutoCAD's built in symbol
//      tables, their table  specific record types, and
//      their iterators.

#ifndef AD_DBLAYOUT_H
#define AD_DBLAYOUT_H

#include "dbmain.h"
#include "dbdict.h"
#include "AdAChar.h"
#include "dbplotsettings.h"

namespace Atil 
{
    class Image; // for Atil::Image
}

typedef struct tagBITMAPINFO BITMAPINFO;

#pragma pack(push, 8)

// Class definition for paperspace layout object

class AcDbLayout: public AcDbPlotSettings
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayout);

    AcDbLayout();
    virtual ~AcDbLayout     ();

    AcDbObjectId      
    getBlockTableRecordId   () const;

    virtual Acad::ErrorStatus 
    setBlockTableRecordId   (AcDbObjectId BlockTableRecordId);

    virtual Acad::ErrorStatus 
    addToLayoutDict         (AcDbDatabase *towhichDb,
                             AcDbObjectId BlockTableRecordId);

    ACDBCORE2D_PORT Acad::ErrorStatus 
    getLayoutName           (const ACHAR*& layoutName) const;

    ACDBCORE2D_PORT Acad::ErrorStatus getName(AcString & sName) const;

    Acad::ErrorStatus 
    getLayoutName           (ACHAR*& layoutName) const; // deprecated

    ACDBCORE2D_PORT virtual Acad::ErrorStatus setLayoutName (const ACHAR* layoutName);

    int               
    getTabOrder             () const;

    virtual void              
    setTabOrder             (int newOrder);

    bool
    getTabSelected          () const;

    virtual void              
    setTabSelected          (Adesk::Boolean tabSelected);

    AcDbObjectIdArray 
    getViewportArray        () const;

    /// <summary>
    /// This function provides BITMAP thumbnail of layout as output
    /// </summary>
    /// <param name="thumbnail"> A reference to a pointer of Bitmap thumbnail, containing header and pixels </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    ///
    Acad::ErrorStatus getThumbnail (BITMAPINFO*& thumbnail) const;

    /// <summary>
    /// This function sets BITMAP thumbnail into layout
    /// </summary>
    /// <param name="thumbnail"> A pointer of Bitmap thumbnail to be set into layout </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    ///
    Acad::ErrorStatus setThumbnail (const BITMAPINFO * thumbnail); 

    /// <summary>
    /// This function provides Atil::Image thumbnail of layout as output
    /// </summary>
    /// <param name="pPreviewImage"> A reference to the pointer of Atil::Image thumbnail </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus getPreviewImage(Atil::Image*& pPreviewImage) const;

    /// <summary>
    /// This functions sets Atil::Image thumbnail into layout
    /// </summary>
    /// <param name="pPreviewImage"> A pointer of Atil::Image thumbnail to be set into layout </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus setPreviewImage (const Atil::Image * pPreviewImage); 

    void
    getLimits (AcGePoint2d& limMin, AcGePoint2d& limMax) const;

    ACDBCORE2D_PORT void
    getLimits (AcDbExtents2d& extent) const;

    void
    getExtents (AcGePoint3d& extMin, AcGePoint3d& extMax) const;

    ACDBCORE2D_PORT void
    getExtents (AcDbExtents& extent) const;

    Acad::ErrorStatus
    initialize(AcDbObjectId* paperVportId = NULL);

    bool
    annoAllVisible() const;

    Acad::ErrorStatus
    setAnnoAllVisible(bool newVal);

protected:
    virtual Acad::ErrorStatus 
    subGetClassID              (CLSID* pClsid) const override;
};

// This overload is deprecated and will be removed. Please use the
// getName() method, taking an AcString & arg instead
//
inline Acad::ErrorStatus AcDbLayout::getLayoutName(ACHAR*& layoutName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbLayout::getName, layoutName);
}

#pragma pack(pop)

#endif
