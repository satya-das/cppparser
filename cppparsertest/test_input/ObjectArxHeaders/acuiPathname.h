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


#pragma once

#pragma pack (push, 8)


//Forward declarations.
class AFILE;

class CAcUiPathname : public CAdUiPathname {

public:

// methods
        // constructor (initializes private data)
        ACCORE_PORT CAcUiPathname(void);
        ACCORE_PORT CAcUiPathname(const CAcUiPathname&);

        // destructor (frees allocated storage)
        ACCORE_PORT virtual ~CAcUiPathname(void);

        // parse a string, validate the format and fill in the data
        //  This routine actually calls ParseRelative with the
        //  current document path (if any) or the current application
        //  path as the relative path.
        ACCORE_PORT virtual PathErr Parse(const wchar_t*, bool wildcard_ok = false ) override;

        // check status for the path
        //  the returned values are defined in aduipathenums.h
        ACCORE_PORT int Status(void);

        // takes a path and tries to open it.  Return TRUE if
        //  the open succeeded, FALSE otherwise.  Note that
        //  these routines set the current directory to the
        //  appropriate place before opening, and reset it
        //  afterward.
        ACCORE_PORT bool Open(AFILE** fdp, const wchar_t *openmode);

        // create an assignment operator that does the right thing.
        const CAcUiPathname& operator=(const CAcUiPathname& pathSrc);
        const CAcUiPathname& operator=(const CAcUiPathname* pathSrc);
        
protected:
        // the guts of the assignment operator
        ACCORE_PORT virtual void AssignCopy( const CAcUiPathname& );
    
};

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname& pathSrc)
{
    AssignCopy( pathSrc);

    return *this;
}

inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname* pathSrc)
{
    AssignCopy( *pathSrc);

    return *this;
}

#pragma pack (pop)

