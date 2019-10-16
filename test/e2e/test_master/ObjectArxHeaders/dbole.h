//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBOLE_H
#  define AD_DBOLE_H
#  include "dbmain.h"
#  include "dbframe.h"
#  include "gepnt3d.h"
#  pragma  pack (push, 8)
class CRectangle3d
{
public:
  AcGePoint3d upLeft;
  AcGePoint3d upRight;
  AcGePoint3d lowLeft;
  AcGePoint3d lowRight;
};
bool operator==(const CRectangle3d& l, const CRectangle3d& r);
class COleClientItem;
class AcDbOleFrame : public AcDbFrame
{
  ACDB_DECLARE_MEMBERS(AcDbOleFrame);
public:
  AcDbOleFrame();
  virtual ~AcDbOleFrame();
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;
  virtual void* getOleObject(void) const;
  virtual void setOleObject(const void* pItem);
};
class AcDbOle2Frame : public AcDbOleFrame
{
  ACDB_DECLARE_MEMBERS(AcDbOle2Frame);
public:
  AcDbOle2Frame();
  virtual ~AcDbOle2Frame();
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;
  virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st) override;
  virtual void* getOleObject(void) const override;
  virtual void setOleObject(const void* pItem) override;
  void* getOleItemHost() const;
  COleClientItem* getOleClientItem(void) const;
  Acad::ErrorStatus setOleClientItem(const COleClientItem* pItem);
  virtual void getLocation(AcGePoint3d& point3d) const;
  void setLocation(const AcGePoint3d& point3d);
  virtual void position(CRectangle3d& rect3d) const;
  virtual void setPosition(const CRectangle3d& rect3d);
  virtual void position(RECT& rect) const;
  virtual void setPosition(const RECT& rect);
  virtual void getUserType(ACHAR* pszName, int nNameSize) const;
  ACDB_PORT Acad::ErrorStatus getUserType(AcString&) const;
  virtual int getType(void) const;
  virtual bool getLinkName(ACHAR* pszName, int nNameSize) const;
  ACDB_PORT Acad::ErrorStatus getLinkName(AcString&) const;
  ACDB_PORT bool isLinked() const;
  virtual bool getLinkPath(ACHAR* pszPath, int nPathSize) const;
  ACDB_PORT Acad::ErrorStatus getLinkPath(AcString&) const;
  virtual Adesk::UInt8 outputQuality() const;
  virtual void setOutputQuality(Adesk::UInt8);
  Adesk::Boolean autoOutputQuality() const;
  void setAutoOutputQuality(Adesk::UInt8);
  double rotation() const;
  Acad::ErrorStatus setRotation(const double rotation);
  double wcsWidth() const;
  Acad::ErrorStatus setWcsWidth(const double wcsWidth);
  double wcsHeight() const;
  Acad::ErrorStatus setWcsHeight(const double wcsHeight);
  double scaleWidth() const;
  Acad::ErrorStatus setScaleWidth(const double scaleWidth);
  double scaleHeight() const;
  Acad::ErrorStatus setScaleHeight(const double scaleHeight);
  Adesk::Boolean lockAspect() const;
  Acad::ErrorStatus setLockAspect(const Adesk::Boolean bLockAspect);
protected:
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#  pragma  pack (pop)
#endif
