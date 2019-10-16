//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACPLOBJECT_H
#  define ACPLOBJECT_H
#  include "rxobject.h"
#  include "AcHeapOpers.h"
#  include "acpl.h"
class AcPlObjectImp;
class AcPlSystemInternals;
class ADESK_NO_VTABLE AcPlObject : public AcRxObject, public AcHeapOperators
{
public:
  ACRX_DECLARE_MEMBERS(AcPlObject);
  ACPL_PORT virtual ~AcPlObject();
protected:
  AcPlObject();
  AcPlObject(AcPlSystemInternals*);
private:
  friend class AcPlSystemInternals;
  AcPlObjectImp* mpPlObjectImp;
};
#  define ACPL_DECLARE_MEMBERS(CLASS_NAME)	 \
private: \
    friend class AcPlSystemInternals; \
protected: \
    CLASS_NAME(AcPlSystemInternals*); \
public: \
    ACPL_PORT virtual AcRxClass* isA() const; \
    ACPL_PORT static AcRxClass* gpDesc; \
    ACPL_PORT static AcRxClass* desc(); \
    ACPL_PORT static CLASS_NAME* cast(const AcRxObject* inPtr) \
        { return ((inPtr == NULL) || !inPtr->isKindOf(CLASS_NAME::desc())) \
          ? NULL : (CLASS_NAME*)inPtr; }; \
    ACPL_PORT static void rxInit(); \
    ACPL_PORT static void rxInit(AppNameChangeFuncPtr);
#  define ACPL_DEFINE_MEMBERS(CLASS_NAME, BASE_CLASS)	 \
ACRX_NO_CONS_DEFINE_MEMBERS(CLASS_NAME, BASE_CLASS) \
CLASS_NAME::CLASS_NAME(AcPlSystemInternals* pInternals) \
: BASE_CLASS(pInternals) \
{ \
}
#endif
