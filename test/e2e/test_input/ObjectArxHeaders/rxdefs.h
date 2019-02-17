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
//
#ifndef   _RXDEFS_H_
#define   _RXDEFS_H_

#include "adesk.h"
#pragma pack (push, 8)

// Deprecated: please use nullptr instead of NULLFCN
#define NULLFCN nullptr

#define ACRX_ULONG_MAX 0xFFFFFFFF

#define ACRX_ASCII_MAX 255  /* Same as UCHAR_MAX in <limits.h> */
#define ACRX_EOS 0          /* End of String Indicator */

// AcRx:  typedef and enum namespace scoping struct.

struct AcRx {

    typedef void (*FcnPtr) ();

    enum         DictIterType { kDictSorted   = 0,
                                kDictCollated = 1 };

    enum         Ordering     { kLessThan     = -1,
                                kEqual        = 0,
                                kGreaterThan  = 1,
                                kNotOrderable = 2 };

    enum         AppMsgCode   { kNullMsg         = 0,
                                kInitAppMsg      = 1,
                                kUnloadAppMsg    = 2,
                                kLoadDwgMsg      = 3,
                                kUnloadDwgMsg    = 4,
                                kInvkSubrMsg     = 5,
                                kCfgMsg          = 6,
                                kEndMsg          = 7,
                                kQuitMsg         = 8,
                                kSaveMsg         = 9,
                                kDependencyMsg   = 10,
                                kNoDependencyMsg = 11,
                                kOleUnloadAppMsg = 12,
                                kPreQuitMsg      = 13,
                                kInitDialogMsg   = 14,
                                kEndDialogMsg    = 15,                                
                                kSuspendMsg      = 16,
                                kInitTabGroupMsg = 17,
                                kEndTabGroupMsg  = 18};                                
        

    enum        AppRetCode   { kRetOK          = 0,
                                kRetError       = 3 };
};

/* These messages are replaced by kLoadDwgMsg, and kUnloadDgwMsg.
 */
#ifndef kLoadADSMsg
#define kLoadADSMsg kLoadDwgMsg
#define kUnloadADSMsg kUnloadDwgMsg
#endif

class AcRxClass;
typedef void (*AppNameChangeFuncPtr)(const AcRxClass* classObj,
                ACHAR *& newAppName, int saveVer);

#pragma pack (pop)

#endif
