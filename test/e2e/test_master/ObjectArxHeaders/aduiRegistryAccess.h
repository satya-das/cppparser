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
#  define _aduiRegistryAccess_h
#  pragma  pack (push, 8)
#  if  _MSC_VER >= 1000
#    pragma  once
#  endif
#  ifdef ACUTIL_INTERNAL
#    include "fake_windows_accore.h"
#    ifdef ADUI_PORT
#      undef ADUI_PORT
#    endif
#    ifdef ACCORE_BUILD
#      define ADUI_PORT	__declspec(dllexport)
#    else 
#      define ADUI_PORT
#    endif
#  endif
#  ifndef ADUI_PORT
#    define ADUI_PORT
#  endif
//////////////////////////////////////////////////////////////////////////////
class ADUI_PORT CAdUiRegistryAccess
{
public:
  CAdUiRegistryAccess();
  CAdUiRegistryAccess(HKEY hKey, const CString& sSubkey);
  virtual ~CAdUiRegistryAccess();
  operator HKEY() const;
  virtual BOOL Open(HKEY hKey, const CString& sSubkey);
  virtual void Close();
  BOOL IsOpen();
  BOOL EnumKeyNames(DWORD dwEntryIndex, CString& sKeyName);
  BOOL EnumValueNames(DWORD dwEntryIndex, CString& sValueName, LPDWORD lpdwType = NULL);
  DWORD ValueType(const CString& sValueName, LPDWORD lpdwSize = NULL);
  CString GetString(const CString& sValueName);
  DWORD GetDWord(const CString& sValueName);
  DWORD GetDWordWithDefaultValue(const CString& sValueName, DWORD dwDefault);
  BOOL GetBinary(const CString& sValueName, LPBYTE pbData, DWORD& dwSize);
protected:
  void CommonConstruction();
  HKEY m_hKey;
  CString m_sSubkey;
};
class ADUI_PORT CAdUiRegistryWriteAccess : public CAdUiRegistryAccess
{
public:
  CAdUiRegistryWriteAccess();
  CAdUiRegistryWriteAccess(HKEY hKey, const CString& sSubkey);
  virtual ~CAdUiRegistryWriteAccess();
  virtual BOOL Open(HKEY hKey, const CString& sSubkey);
  BOOL SetString(const CString& cValueName, const CString& sValue);
  BOOL SetDWord(const CString& sValueName, DWORD dwValue);
  BOOL SetBinary(const CString& sValueName, const BYTE* pbData, DWORD dwLen);
};
class ADUI_PORT CAdUiRegistryDeleteAccess : public CAdUiRegistryWriteAccess
{
public:
  CAdUiRegistryDeleteAccess();
  CAdUiRegistryDeleteAccess(HKEY hKey, const CString& sSubkey);
  virtual ~CAdUiRegistryDeleteAccess();
  BOOL DeleteValue(const CString& sValueName);
  BOOL DeleteAllValues();
  BOOL DeleteKey(const CString& sKeyName);
  BOOL DeleteKeyAndSubkeys(const CString& sKeyName);
  BOOL DeleteAllKeys();
};
//////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#  pragma  pack (pop)
#endif
//////////////////////////////////////////////////////////////////////////////
