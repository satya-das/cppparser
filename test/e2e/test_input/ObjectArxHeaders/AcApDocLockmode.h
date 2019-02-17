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
//  DESCRIPTION:  Header for Document and Document Manager Classes.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACAPDOCLOCKMODE_H
#define ACAPDOCLOCKMODE_H

#pragma pack (push, 8)
struct AcAp {

    // The value order of this enum is important - and determines
    // the level of locking.  Also, kWrite and kProtectedAutoWrite
    // share a common bit - so that (mode & kWrite) will be true
    // for either lock mode.
    //
    enum DocLockMode   {   kNone               = 0x00,
                           kAutoWrite          = 0x01,
                           kNotLocked          = 0x02,
                           kWrite              = 0x04,
                           kProtectedAutoWrite = 0x14,
                           kRead               = 0x20,
                           kXWrite             = 0x40  };
};
#pragma pack (pop)

#endif // ACAPDOCLOCKMODE_H

