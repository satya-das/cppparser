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
//  DESCRIPTION:  Base class for client instantiable plot objects
//

#ifndef ACPLOBJECT_H
#define ACPLOBJECT_H

#include "rxobject.h"
#include "AcHeapOpers.h"
#include "acpl.h"

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
    AcPlObjectImp*  mpPlObjectImp;
};

// This macro is NOT intended for application-defined classes derived
// from AcPlObject when declaring their class header.  This macro declares
// an internally used form of constructor, which takes the
// AcPlSystemInternals* argument.  Rx applications should not define
// such constructors for their database object classes, but they should
// be ignored by the system anyway.
//
// Application-defined classes are advised to use the ACRX_DECLARE_MEMBERS
// macro instead, and to consult the documentation for related definitions.
//
#define ACPL_DECLARE_MEMBERS(CLASS_NAME) \
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

// Use this macro to define members of classes derived from AcPlObject
#define ACPL_DEFINE_MEMBERS(CLASS_NAME, BASE_CLASS) \
ACRX_NO_CONS_DEFINE_MEMBERS(CLASS_NAME, BASE_CLASS) \
CLASS_NAME::CLASS_NAME(AcPlSystemInternals* pInternals) \
: BASE_CLASS(pInternals) \
{ \
}
        
#endif // ACPLOBJECT_H
