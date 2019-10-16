//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACHAPI_H
#  define ACHAPI_H	1
#  include "AdAchar.h"
#  include "acdbcore2ddefs.h"
#  pragma  pack (push, 8)
///////////////////////////////////////////////////////////////////////////////
// Hyperlink Object
///////////////////////////////////////////////////////////////////////////////
class AcDbHyperlink
{
public:
  AcDbHyperlink()
  {
  }
  virtual ~AcDbHyperlink()
  {
  }
  enum HLinkFlags
  {
    kUndefined = 0,
    kConvertDwgToDwf = 0x1
  };
  virtual const ACHAR* name() const = 0;
  virtual void setName(const ACHAR* cName) = 0;
  virtual const ACHAR* description() const = 0;
  virtual void setDescription(const ACHAR* cDescription) = 0;
  virtual const ACHAR* subLocation() const = 0;
  virtual void setSubLocation(const ACHAR* cSubLocation) = 0;
  virtual const ACHAR* getDisplayString() const = 0;
  virtual bool isOutermostContainer() const = 0;
  virtual const int getNestedLevel() const = 0;
  virtual const Adesk::Int32 flags() const;
  virtual void setFlags(const Adesk::Int32 lFlags);
};
inline const Adesk::Int32 AcDbHyperlink::flags() const
{
  return AcDbHyperlink::kUndefined;
}
inline void AcDbHyperlink::setFlags(const Adesk::Int32 lFlags)
{
  ADESK_UNREFED_PARAM(lFlags);
}
///////////////////////////////////////////////////////////////////////////////
// Hyperlink Collection
///////////////////////////////////////////////////////////////////////////////
class AcDbHyperlinkCollection
{
public:
  AcDbHyperlinkCollection()
  {
  }
  virtual ~AcDbHyperlinkCollection()
  {
  }
  virtual void addHead(const ACHAR* sName, const ACHAR* sDescription, const ACHAR* sSubLocation = NULL) = 0;
  virtual void addTail(const ACHAR* sName, const ACHAR* sDescription, const ACHAR* sSubLocation = NULL) = 0;
  virtual void addAt(const int nIndex, const ACHAR* sName, const ACHAR* sDescription, const ACHAR* sSubLocation = NULL) = 0;
  ACDBCORE2D_PORT void addAt(int index, const AcDbHyperlink* pHLink);
  virtual void removeHead() = 0;
  virtual void removeTail() = 0;
  virtual void removeAt(const int nIndex) = 0;
  virtual int count() const = 0;
  virtual AcDbHyperlink* item(const int nIndex) const = 0;
};
///////////////////////////////////////////////////////////////////////////////
//  Hyperlink Protocol Extension
///////////////////////////////////////////////////////////////////////////////
class AcDbEntityHyperlinkPE : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbEntityHyperlinkPE);
  virtual Acad::ErrorStatus getHyperlinkCollection(AcDbObject* pObj, AcDbHyperlinkCollection*& pcHCL, bool bOneOnly = false, bool bIgnoreBlockDefinition = true) = 0;
  virtual Acad::ErrorStatus getHyperlinkCollection(const AcArray<AcDbObjectId>*& idContainers, AcDbHyperlinkCollection*& pcHCL, bool bOneOnly = false, bool bIgnoreBlockDefinition = true) = 0;
  virtual Acad::ErrorStatus setHyperlinkCollection(AcDbObject* pObj, AcDbHyperlinkCollection* pcHCL) = 0;
  virtual Acad::ErrorStatus getHyperlinkCount(AcDbObject* pObj, unsigned int& nCount, bool bIgnoreBlockDefinition = true) = 0;
  virtual Acad::ErrorStatus getHyperlinkCount(const AcArray<AcDbObjectId>*& idContainers, unsigned int& nCount, bool bIgnoreBlockDefinition = true) = 0;
  virtual Acad::ErrorStatus hasHyperlink(AcDbObject* pObj, bool& bHasHyperlink, bool bIgnoreBlockDefinition = true) = 0;
  virtual Acad::ErrorStatus hasHyperlink(const AcArray<AcDbObjectId>*& idContainers, bool& bHasHyperlink, bool bIgnoreBlockDefinition = true) = 0;
};
#  define HAPI_SERVICE	ACRX_T("AcadHyperlinks")
#  pragma  pack (pop)
#endif
