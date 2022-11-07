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

#ifndef   _ADESKABB_H
#define   _ADESKABB_H

// DESCRIPTION:
//
// Legacy shorthand for Adesk types. These are no longer of much use, as native
// C++ has short type names like int16_t, uint32_t, etc.
// New code should not include this header
//
// Note:  All interface descriptions and API headers must use fully qualified
//        names.  That is, header files MUST NOT include this file and MUST NOT
//        use these abbreviations.  Projects should have the option of not
//        bringing these typedefs into their namespace.
//
// Note:  When this file is included in a source file, it MUST BE
//	  included AFTER all other include files (except possibly
//	  other abbreviation include files).
//	  For example:
//            #include "foo.h"
//            #include "bar.h"
//            #include "adeskabb.h" // <- Must be last!

#include "adesk.h"

// To be deprecated. Please use native types int8_t, uint16_t, etc
//
typedef Adesk::Int8	    Int8;       // int8_t
typedef Adesk::Int16	    Int16;      // int16_t
typedef Adesk::Int32	    Int32;      // int32_t
typedef Adesk::UInt8	    UInt8;      // uint8_t
typedef Adesk::UInt16	    UInt16;     // uint16_t
typedef Adesk::UInt32	    UInt32;     // uint32_t

typedef Adesk::uchar	    uchar;      // unsigned char
typedef Adesk::ushort	    ushort;     // unsigned short
typedef Adesk::uint	    uint;       // unsigned int

const bool kFalse = false;      // To be deprecated. Please use false and true
const bool kTrue = true;

#endif /* _ADESKABB_H */

