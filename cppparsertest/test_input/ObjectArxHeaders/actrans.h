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
//  DESCRIPTION: Header for Transaction Modeler.

#ifndef   _ACTRANS_H
#define   _ACTRANS_H

#include "rxnames.h"
#include "aced.h"
#include "dbptrar.h"
#include "dbtrans.h"
#include "acdocman.h"
#pragma pack (push, 8)


class AcTransactionManager: public AcDbTransactionManager 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcTransactionManager);

    virtual Acad::ErrorStatus   enableGraphicsFlush(bool doEnable) = 0;
    virtual void                flushGraphics() = 0; 
};

inline AcTransactionManager* acTransactionManagerPtr()
{
    AcApDocument* pDoc = acDocManager->curDocument();
    return pDoc ? pDoc->transactionManager() : NULL;
}

#define actrTransactionManager  acTransactionManagerPtr()

#pragma pack (pop)
#endif
