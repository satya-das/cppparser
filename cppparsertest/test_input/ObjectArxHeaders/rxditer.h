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
// DESCRIPTION:  header file for class RxDictIterator
// This is a layer of commonality between the two iterators needed for
// RxIDDictionary; RxDictSkipListIterator, and RxDictArrayIterator.

#ifndef _RXDITER_H
#define _RXDITER_H 1

#include "rxobject.h"
#include "rxiter.h"
#include "AdAChar.h"
#pragma pack (push, 8)

class AcRxDictionaryIterator: public AcRxIterator
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDictionaryIterator, ACBASE_PORT);

    virtual const ACHAR * key   () const = 0;
    virtual AcRxObject*   object() const override = 0;
    virtual Adesk::UInt32 id    () const = 0;
};

#pragma pack (pop)
#endif
