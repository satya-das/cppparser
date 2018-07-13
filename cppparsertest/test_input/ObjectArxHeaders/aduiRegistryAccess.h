//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiRegistryAccess_h
#define _aduiRegistryAccess_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// This file is also built as part of accore.dll separately from the rest of
// AdUi.  To do so, we can only use a part of MFC, so a little tweaking is
// needed.
// 
#ifdef ACUTIL_INTERNAL
#include "fake_windows_accore.h"
#ifdef ADUI_PORT
#undef ADUI_PORT
#endif
#ifdef ACCORE_BUILD
#define ADUI_PORT __declspec(dllexport)
#else
#define ADUI_PORT
#endif
#endif

#ifndef ADUI_PORT
#define ADUI_PORT
#endif
//////////////////////////////////////////////////////////////////////////////
// Note: These classes are for INTERNAL USE ONLY and may be slated for removal.

class ADUI_PORT CAdUiRegistryAccess // pure virtual class?
{
public:
    // Construction/destruction:
    CAdUiRegistryAccess();
    CAdUiRegistryAccess(HKEY hKey,const CString& sSubkey); // Implicitly opens
    virtual ~CAdUiRegistryAccess();

    // Allows this class to be used anywhere an HKEY is valid...
    operator HKEY() const;

    // Access control: Opens to (another) key.
    virtual BOOL Open(HKEY hKey,const CString &sSubkey);
    virtual void Close();
    BOOL IsOpen();

    // Enumeration mechanism:
    BOOL EnumKeyNames(DWORD dwEntryIndex,CString& sKeyName);
    BOOL EnumValueNames(DWORD dwEntryIndex,CString& sValueName,LPDWORD lpdwType = NULL); // throw CMemoryException*;
    // Note: 1) Enumerate from 0 up to end, or from end back to 0.
    //       2) do not alter the key or value being enumerated during the enumeration
    // (These are caveats presented by the underlying API calls...)

    // returns REG_... types, or REG_NONE if the key doesn't exist.
    DWORD   ValueType(const CString& sValueName,LPDWORD lpdwSize = NULL);

    // GetAccess:
    CString GetString(const CString& sValueName); // throw CMemoryException*;

    // NOTE that GetDWord returns 0 on failure! It also returns 0
    // if the value is indeed 0. BEWARE USING THIS FUNCTION!
    DWORD   GetDWord(const CString&  sValueName);

    // Note: If the value doesn't exist, dwDefault will be returned instead of 0.
    DWORD   GetDWordWithDefaultValue(const CString &sValueName, DWORD dwDefault);

    BOOL    GetBinary(const CString& sValueName, LPBYTE pbData, DWORD& dwSize);

protected:
    // Derivation for write permission can override this:
    void CommonConstruction();

    HKEY    m_hKey;
    CString m_sSubkey;

};

class ADUI_PORT CAdUiRegistryWriteAccess: public CAdUiRegistryAccess
// Adds write capabilities to the registry access object;
//
// Remember: do not write to keys or values during
// an enumeration loop...  (Registry API limitation)
{
public:
    // Construction/destruction:
    CAdUiRegistryWriteAccess();
    CAdUiRegistryWriteAccess(HKEY hKey,const CString& sSubkey);
    virtual ~CAdUiRegistryWriteAccess();

    virtual BOOL Open(HKEY hKey,const CString& sSubkey);

    BOOL    SetString(const CString& cValueName, const CString& sValue); // throw CMemoryException*;
    BOOL    SetDWord(const CString&  sValueName, DWORD dwValue);
    BOOL    SetBinary(const CString& sValueName, const BYTE* pbData, DWORD dwLen);
};

class ADUI_PORT CAdUiRegistryDeleteAccess: public CAdUiRegistryWriteAccess
//
// Adds deletion capabilities to the registry access object.
// Deliberately left as a derived class (rather than folded
// into the Write class, because of the potential harm
// possible by accidental use.
//
// Remember: do not delete or write to keys or values during
// an enumeration loop...  (Registry API limitation)
//
{
public:
    CAdUiRegistryDeleteAccess();
    CAdUiRegistryDeleteAccess(HKEY hKey,const CString& sSubkey);
    virtual ~CAdUiRegistryDeleteAccess();

    // Deletes a specific value
    BOOL    DeleteValue(const CString& sValueName);

    // Deletes all values under this key
    BOOL    DeleteAllValues();

    // Deletes a specific subkey; (note: in Win95, this is the same as below)
    BOOL    DeleteKey(const CString&  sKeyName);

    // Deletes a specific subkey, and all sub-keys beneath it (needed in NT)
    BOOL    DeleteKeyAndSubkeys(const CString&  sKeyName); // recursive

    // Deletes all subkeys in the current key; like "del *.* /s" is to DOS (dangerous!)
    BOOL    DeleteAllKeys(); // recursive

};

//////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
