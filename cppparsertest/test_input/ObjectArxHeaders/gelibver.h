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
// DESCRIPTION:
//
// This  file  contains  the  functionality for managing versions of 
// gelib.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef AC_GELIBVERSION_H
#define AC_GELIBVERSION_H

#include "adesk.h"
#include "gedll.h"
#pragma pack (push, 8)

// Current image version.
//
#define IMAGE_MAJOR_VER          2
#define IMAGE_MINOR_VER          0
#define IMAGE_CORRECTIVE_VER     0
#define IMAGE_INTERNAL_VER       0

class 
AcGeLibVersion {
public:
    // Constructors.
    //
    GE_DLLEXPIMPORT AcGeLibVersion();
    GE_DLLEXPIMPORT AcGeLibVersion(const AcGeLibVersion&);
    GE_DLLEXPIMPORT AcGeLibVersion(Adesk::UInt8 major, Adesk::UInt8 minor,
                   Adesk::UInt8 corrective,
                   Adesk::UInt8 internal_version);

    // Inquiry functions.
    //
    GE_DLLEXPIMPORT Adesk::UInt8     majorVersion        () const;
    GE_DLLEXPIMPORT Adesk::UInt8     minorVersion        () const;
    GE_DLLEXPIMPORT Adesk::UInt8     correctiveVersion   () const;
    GE_DLLEXPIMPORT Adesk::UInt8     schemaVersion       () const;

    // Set functions.
    //
    GE_DLLEXPIMPORT AcGeLibVersion&     setMajorVersion        (Adesk::UInt8 val);
    GE_DLLEXPIMPORT AcGeLibVersion&     setMinorVersion        (Adesk::UInt8 val);
    GE_DLLEXPIMPORT AcGeLibVersion&     setCorrectiveVersion   (Adesk::UInt8 val);
    GE_DLLEXPIMPORT AcGeLibVersion&     setSchemaVersion       (Adesk::UInt8 val);

    // Comparisons
    //
    GE_DLLEXPIMPORT Adesk::Boolean operator ==      (const AcGeLibVersion&) const;
    GE_DLLEXPIMPORT Adesk::Boolean operator !=      (const AcGeLibVersion&) const;
    GE_DLLEXPIMPORT Adesk::Boolean operator <       (const AcGeLibVersion&) const;
    GE_DLLEXPIMPORT Adesk::Boolean operator <=      (const AcGeLibVersion&) const;
    GE_DLLEXPIMPORT Adesk::Boolean operator >       (const AcGeLibVersion&) const;
    GE_DLLEXPIMPORT Adesk::Boolean operator >=      (const AcGeLibVersion&) const;

    // Relased version objects.
    // gelib release 0 --- End of 1995.
    //
    GE_DLLDATAEXIMP static const AcGeLibVersion kRelease0_95;

    // gelib r14 release.
    //
    GE_DLLDATAEXIMP static const AcGeLibVersion kReleaseSed;

    // gelib r15 release.
    //
    GE_DLLDATAEXIMP static const AcGeLibVersion kReleaseTah;

private:
    Adesk::UInt8   mVersion[10];
};

#pragma pack (pop)
#endif
