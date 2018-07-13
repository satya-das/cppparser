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
//  DESCRIPTION:  Header for Long Transaction Manager.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef   _LTRANSMAN_H
#define   _LTRANSMAN_H

#include "rxnames.h"
#include "dbidar.h"
#pragma pack (push, 8)

class AcDbLongTransaction;
class AcDbDatabase;
class AcDbIdMapping;
class AcApDocument;

#define AC_LONG_TRANSACTION_MANAGER_OBJ ACRX_T("AcApLongTransactionManager")

class AcApLongTransactionReactor: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcApLongTransactionReactor);

    // To identify and connect this notification with the deepClone
    // notifications, AcDbLongTransactionWorkSet::activeIdMap()
    // will return the cloning idMap.  CheckOut and CheckIn, for
    // the same transaction, will use different maps.  
    //
    virtual void beginCheckOut        (AcDbLongTransaction& ,
                                       AcDbObjectIdArray& originList);
    virtual void endCheckOut          (AcDbLongTransaction& );
    virtual void beginCheckIn         (AcDbLongTransaction& );
    virtual void endCheckIn           (AcDbLongTransaction& );
    virtual void abortLongTransaction (AcDbLongTransaction& );

protected:
    Acad::ErrorStatus veto ();  // beginCheckOut() can be vetoed

private:
    Adesk::UInt8 mVeto;

friend class AcApImpLongTransactionManager;
};

class AcApLongTransactionManager: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcApLongTransactionManager);

    virtual Acad::ErrorStatus   checkOut(
                                   AcDbObjectId& transId,
                                   AcDbObjectIdArray& objList,
                                   AcDbObjectId toBlock,
                                   AcDbIdMapping& errorMap,
                                   AcDbObjectId lockBlkRef = 
                                       AcDbObjectId::kNull) = 0;

    virtual Acad::ErrorStatus   checkIn  (
                                   AcDbObjectId transId,
                                   AcDbIdMapping& errorMap,
                                   bool keepObjs = false) = 0;

    virtual Acad::ErrorStatus   abortLongTransaction(
                                   AcDbObjectId transId,
                                   bool keepObjs = false) = 0;

    virtual AcDbObjectId        currentLongTransactionFor(
                                   const AcApDocument* pDoc) const = 0;

    virtual void                addReactor(AcApLongTransactionReactor*) = 0;
    virtual void                removeReactor(AcApLongTransactionReactor*) = 0;

    // For filtering classes out of Long Transactions
    //
    virtual Acad::ErrorStatus   addClassFilter (AcRxClass* ) = 0;
    virtual bool                isFiltered (AcRxClass* ) const = 0;
};

extern AcApLongTransactionManager* acapLongTransactionManagerPtr();
#define acapLongTransactionManager  acapLongTransactionManagerPtr()

#pragma pack (pop)
#endif  // !_LTRANSMAN_H
