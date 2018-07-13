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
//  dbosnap2.h - header file for custom osnap api
//

#ifndef _DBOSNAP2_H
#define _DBOSNAP2_H

#include "dbosnap.h"

class AcDbCustomOsnapMode2 : public AcDbCustomOsnapMode{
public:
    /// <summary>
    /// This method is called to get an icon that will be displayed on osnap 
    /// right-clicking menu.
    /// AutoCAD will not close this handle, you can cache it and destroy
    /// the icon resource in destructor.
    /// </summary>
    ///
    /// <returns>
    /// Returns a handle to an icon. The icon you supply should be in size of 16*16.
    /// </returns>
    virtual HICON menuIcon()
    {
        return NULL;
    }

    /// <summary>
    /// This method is called to get an icon that will be displayed on osnap 
    /// right-clicking menu for dark theme.
    /// AutoCAD will not close this handle, you can cache it and destroy
    /// the icon resource in destructor.
    /// </summary>
    ///
    /// <returns>
    /// Returns a handle to an icon. The icon you supply should be in size of 16*16.
    /// </returns>
    virtual HICON menuIconForDarkTheme()
    {
        return NULL;
    }

    /// <summary>
    /// This method is called to get a string used for displaying on osnap 
    /// right-clicking menu.
    /// </summary>
    /// <returns>
    /// Returns Custom OSNAP mode display string.
    /// </returns>
    virtual const ACHAR * displayString()
    {
        return localModeString();
    }
};

#endif // _DBOSNAP2_H
