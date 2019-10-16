//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  rxobject.h
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_RXOBJECT_H
#  define AD_RXOBJECT_H	1
#  include "acbasedefs.h"
#  include "adesk.h"
#  include "rxdefs.h"
#  include "rxboiler.h"
#  include "acadstrc.h"
#  include "acdbport.h"
#  include "AcDbCore2dDefs.h"
#  pragma  pack (push, 8)
class ADESK_NO_VTABLE AcRxObject
{
public:
  virtual ~AcRxObject();
  ACBASE_PORT static AcRxClass* desc();
  static AcRxObject* cast(const AcRxObject* inPtr)
  {
    return const_cast<AcRxObject*>(inPtr);
  }
  inline bool isKindOf(const AcRxClass* aClass) const;
  ACBASE_PORT AcRxObject* queryX(const AcRxClass* protocolClass) const;
  ACBASE_PORT AcRxObject* x(const AcRxClass* protocolClass) const;
  ACBASE_PORT virtual AcRxClass* isA() const;
  ACBASE_PORT virtual AcRxObject* clone() const;
  ACBASE_PORT virtual Acad::ErrorStatus copyFrom(const AcRxObject* other);
  ACBASE_PORT virtual bool isEqualTo(const AcRxObject* other) const;
  ACBASE_PORT virtual AcRx::Ordering comparedTo(const AcRxObject* other) const;
protected:
  friend class AcRxQueryXOverrule;
  ACBASE_PORT virtual AcRxObject* subQueryX(const AcRxClass* protocolClass) const;
  ACBASE_PORT AcRxObject();
};
inline AcRxObject::~AcRxObject()
{
}
#  pragma  pack (pop)
#  include "rxclass.h"
#  define ACRX_PE_PTR(RxObj,PEClass)	 PEClass::cast(RxObj-> \
                                            queryX(PEClass::desc()))
#  define ACRX_X_CALL(RxObj,PEClass)	 PEClass::cast(RxObj->x(PEClass::desc()))
#  include "rxdict.h"
#endif
