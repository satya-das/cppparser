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
// DESCRIPTION:  Class header for AcDbOleFrame & AcDbOle2Frame, 
//               OLE 2 Container (Client) Feature for Windows/NT
//
//    AcDbEntity
//        AcDbOleFrame
//            AcDbOle2Frame  
//
//    AcDbOleFrame supports 1) non-OLE platform and 2) pre-R13 C4 OLE 1
//    storage and retrieval only.  It doesn't support OLE object
//    display or activation.  It stores
//    binary data in lists that can be scanned later using the DbId.
//    AcDbOle2Frame supports OLE 2 objects.  For non-OLE platforms,
//    the virtual methods are not overridden, so the storage methods
//    in AcDbOleFrame are used instead.  

#ifndef AD_DBOLE_H
#define AD_DBOLE_H

#include "dbmain.h"
#include "dbframe.h"
#include "gepnt3d.h"

#pragma pack (push, 8)

class CRectangle3d
{
public:
    AcGePoint3d upLeft;
    AcGePoint3d upRight;
    AcGePoint3d lowLeft;
    AcGePoint3d lowRight;
};

bool operator==(const CRectangle3d&l, const CRectangle3d&r);

class COleClientItem;

class AcDbOleFrame: public AcDbFrame
{
public:
    ACDB_DECLARE_MEMBERS(AcDbOleFrame);

    AcDbOleFrame();
    virtual ~AcDbOleFrame();

    // --- AcDbObject Protocol

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;

    // OLE Specific Methods
    virtual void* getOleObject(void) const;
    virtual void setOleObject(const void *pItem);

protected:
};
 

class AcDbOle2Frame: public AcDbOleFrame
{
public:
    ACDB_DECLARE_MEMBERS(AcDbOle2Frame);
    AcDbOle2Frame();
    virtual ~AcDbOle2Frame();

    // --- AcDbObject Protocol

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;

    // --- AcDbEntity Protocol


    virtual void                saveAs(AcGiWorldDraw* mode, AcDb::SaveType st) override;

    // OLE Specific Methods
    // Get pointer to MFC COleClientItem class.
    // WARNING: in RealDWG host applications, the void* points to an
    // object that wraps the COleClientItem not to the COleClientItem
    // itself.
    //
    virtual void* getOleObject(void) const override;
    virtual void setOleObject(const void *pItem) override;

    void* getOleItemHost() const;

    // These two methods will work for all host applications.
    // The set method will only work on an AcDbOle2Frame entity that is
    // already owned by a BlockTableRecord and that has its layer set. 
    //
    COleClientItem* getOleClientItem(void) const;
    Acad::ErrorStatus setOleClientItem(const COleClientItem* pItem);

    // Upper left corner of OLE object, world coordinates
    //
    virtual void getLocation(AcGePoint3d& point3d) const;

    // Change the location by passing new upper left corner 
    // of OLE object, world coordinates
    void setLocation(const AcGePoint3d& point3d);

    // Get world coords of the four corners of OLE object.
    //
    virtual void position(CRectangle3d& rect3d) const;
    
    // Set world coords of the four corners of OLE object.
    //
    virtual void setPosition(const CRectangle3d& rect3d);

    // Get GDI device coords of the four corners of OLE object
    // for the current viewport.
    //
    virtual void position(RECT& rect) const;

    // Set coords according to the GDI device coords of the four corners of OLE object
    // for the current viewport.
    //
    virtual void setPosition(const RECT& rect);

    // Description, such as "Paintbrush Bitmap".
    // See MFC COleClientItem::GetUserType().
    //
    virtual void getUserType(ACHAR * pszName, int nNameSize) const;
    ACDB_PORT Acad::ErrorStatus getUserType(AcString &) const;

    // Linked, embedded, or static.  See MFC COleClientItem::GetType().
    //   1 OT_LINK       The OLE item is a link.
    //   2 OT_EMBEDDED   The OLE item is embedded.
    //   3 OT_STATIC     The OLE item is static, that is, it contains only 
    //                   presentation data, not native data, and thus cannot be edited.
    //
    virtual int getType(void) const;

    // If this is a linked object, get the file and item name
    // to which it is linked.
    // Example:  C:\My Documents\link.xls!Sheet1!R5C3:R8C3
    //

    virtual bool getLinkName(ACHAR * pszName, int nNameSize) const;
    ACDB_PORT Acad::ErrorStatus getLinkName(AcString &) const;

    ACDB_PORT bool isLinked() const;
    // Get path name of linked object, without the item name.
    // Example:
    //   GetLinkName: C:\My Documents\link.xls!Sheet1!R5C3:R8C3
    //   GetLinkPath: C:\My Documents\link.xls
    //
    virtual bool getLinkPath(ACHAR * pszPath, int nPathSize) const;
    ACDB_PORT Acad::ErrorStatus getLinkPath(AcString &) const;

    // Output quality affects the color depth and resolution at which
    // the OLE object is plotted.  
    virtual Adesk::UInt8 outputQuality() const;
    virtual void setOutputQuality(Adesk::UInt8);

    // If the Plot Quality is chosen as "Automatically Select" in the OPM,
    // a plot quality is internally chosen according to the application
    Adesk::Boolean autoOutputQuality() const;
    void setAutoOutputQuality(Adesk::UInt8);

    // OLE Objects can be rotated any angle similar to raster objects.  This
    // value may be changed by virtue of a change via the OPM, or by the 
    // ROTATE command
    double rotation() const;
    Acad::ErrorStatus setRotation(const double rotation);

    // wcsWidth and wcsHeight represent the actual width and height of the OLE
    // object, expressed in AutoCAD world coords.  These values may be affected
    // by changes in the actual coordinates of the object during a manipulation
    // command such as STRETCH, via grip editing resulting in a resizing 
    // operation, or by changing the scale of the object via OPM scale 
    // properties or the the Text size dialog
    double wcsWidth() const;
    Acad::ErrorStatus setWcsWidth(const double wcsWidth);

    double wcsHeight() const;
    Acad::ErrorStatus setWcsHeight(const double wcsHeight);

    // scaleWidth and scaleHeight represent the current object scale, 
    // relative to the original scale from the default Text Size to
    // AutoCAD units scale.  These are expressed as a *percentage* of
    // the original scale.  These values may be affected by changes 
    // in the actual coordinates of the object during a manipulation command
    // such as STRETCH, via grip editing, resulting in a resizing operation,
    // or by changing the width/height of the object via OPM width/height
    // properties or the Text Size dialog.
    double scaleWidth() const;
    Acad::ErrorStatus setScaleWidth(const double scaleWidth);

    double scaleHeight() const;
    Acad::ErrorStatus setScaleHeight(const double scaleHeight);

    // The Lock Aspect Ratio property affects the behavior of the OLE
    // object when its size is changed.  It can be set to Yes or No;
    // the default value is Yes - locked.  This means that when a new
    // value is entered for the object's Width, Height, Scale width 
    // or Scale height, both the width and the height change uniformly.
    Adesk::Boolean lockAspect() const;
    Acad::ErrorStatus setLockAspect(const Adesk::Boolean bLockAspect);

protected:
    // Get corresponding COM wrapper class ID
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

#pragma pack (pop)

#endif  // AD_DBOLE_H_
