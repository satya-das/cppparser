//
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
// AcDbFilter is the base class for all Filter implementations.
//
// An AcDbFilter object can be associated with a block reference, and,
// if the corresponding Block has the equivalent AcDbIndex, a filtered
// traversal of the block can be performed.
//

#ifndef AD_DBFILTER_H
#define AD_DBFILTER_H

#include "dbmain.h"

#pragma pack (push, 8)

class AcDbFilteredBlockIterator;

class AcDbFilter: public  AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbFilter);
	     AcDbFilter();
    virtual ~AcDbFilter();

    virtual AcRxClass* indexClass() const;
};

#pragma pack (pop)

#endif // AD_DBFILTER_H
