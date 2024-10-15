//
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
#define AD_RXOBJECT_H 1

#include "acbasedefs.h"
#include "adesk.h"
#include "rxdefs.h"
#include "rxboiler.h"
#include "acadstrc.h"
#include "acdbport.h"
#include "AcDbCore2dDefs.h"

#pragma pack (push, 8)


class ADESK_NO_VTABLE AcRxObject
{
public:
    virtual ~AcRxObject();

    ACBASE_PORT static AcRxClass*         desc();

    // All objects in the Rx system are by definition AcRxObjects, so we do not
    // call isDerivedFrom() here as we do with other derived class's cast() methods.
    // See ACRX_DECLARE_MEMBERS_EXPIMP() in rxboiler.h
    // The cast() methods also cast away const-ness, for historical reasons
    //
    static AcRxObject * cast(const AcRxObject * inPtr)
    {
        return const_cast<AcRxObject *>(inPtr);
    }

    // Defined in rxclass.h
    inline bool               isKindOf(const AcRxClass * aClass) const;

    ACBASE_PORT AcRxObject*               queryX(const AcRxClass* protocolClass) const;

    // Deprecated: The x() method will be removed in a future release.
    // Please use queryX() instead.
    //
    ACBASE_PORT AcRxObject*               x(const AcRxClass* protocolClass) const;

    // isA() is normally overridden by derived classes.
    // See ACRX_DECLARE_MEMBERS_EXPIMP() and ACRX_DEFINE_MEMBERS() in rxboiler.h
    ACBASE_PORT virtual AcRxClass*        isA() const;
    
    ACBASE_PORT virtual AcRxObject*       clone() const;

    // Base class implementation of copyFrom() calls fatalError() func
    ACBASE_PORT virtual Acad::ErrorStatus copyFrom(const AcRxObject* other);

    ACBASE_PORT virtual bool              isEqualTo(const AcRxObject * other) const;
    ACBASE_PORT virtual AcRx::Ordering    comparedTo(const AcRxObject * other) const;
    
protected:
    // AcRxQueryXOverrule related
    friend class                          AcRxQueryXOverrule;
    ACBASE_PORT virtual AcRxObject*       subQueryX(const AcRxClass* protocolClass) const;

    ACBASE_PORT AcRxObject();
};

// Performance note: it might not make sense to make virtual methods
// inline, but dtors are an exception to the rule.  Derived objects'
// dtors will call this dtor explicitly, so inlining works.
//
inline AcRxObject::~AcRxObject()
{
}

#pragma pack (pop)

#include "rxclass.h"

#define ACRX_PE_PTR(RxObj,PEClass) PEClass::cast(RxObj-> \
                                            queryX(PEClass::desc()))

// Deprecated: The ACRX_X_CALL macro will be removed in a future
// release.  Please use ACRX_PE_PTR() instead.
//
#define ACRX_X_CALL(RxObj,PEClass) PEClass::cast(RxObj->x(PEClass::desc()))

#include "rxdict.h"

#endif

