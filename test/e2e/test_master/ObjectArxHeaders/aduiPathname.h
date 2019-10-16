//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "adesk.h"
#include "acbasedefs.h"
#include "aduipathenums.h"
#include "AcString.h"
#include <cstdio>
#pragma  pack (push, 8)
#ifndef _ADESK_MAC_
#  define MAX_PATH	260
#endif
class CAdUiVolumeDescriptor;
AcString GetDriveForRoottypePath(const CAdUiVolumeDescriptor* const);
bool WasAbsoluteHelper(path_category pc);
bool IsValidOnColon(const AcString* work);
namespace Autodesk
{
  namespace AutoCAD
  {
    namespace PAL
    {
      namespace FileIO
      {
        class File;
      }
    }
  }
}
APIDOCER extern const ACHAR kBackslash = 0;
__declspec(selectany) extern const ACHAR kColon = ACRX_T(':');
__declspec(selectany) extern const ACHAR kDoubleQuote = ACRX_T('"');
__declspec(selectany) extern const ACHAR kEOS = ACRX_T('\0');
__declspec(selectany) extern const ACHAR kPeriod = ACRX_T('.');
__declspec(selectany) extern const ACHAR kSlash = ACRX_T('/');
__declspec(selectany) extern const ACHAR kSpace = ACRX_T(' ');
__declspec(selectany) extern const ACHAR kAsterisk = ACRX_T('*');
__declspec(selectany) extern const ACHAR kQuestionmark = ACRX_T('?');
__declspec(selectany) extern const ACHAR kZero = ACRX_T('0');
class ACBASE_PORT CAdUiPathname
{
  friend void GetDisplayNameHelper(const CAdUiPathname* pPathName, AcString& strResult, int maxchars);
  friend CAdUiVolumeDescriptor* NewVolDescriptorHelper(const CAdUiPathname* pPathName, const AcString& vol_name);
  friend bool IsPathValid(CAdUiPathname* pPathName, const CAdUiPathname* rel_path, const AcString* work);
  friend void HandleSpecialPath(CAdUiPathname* pPathName, const CAdUiPathname* rel_path, AcString* work, int index, bool wildcard_ok);
  friend bool IsValidOnColon(const AcString* work);
  friend void SetupVolForRoottypePath(CAdUiPathname* pPathName, const CAdUiPathname* pRelPath, const wchar_t* pPathStr);
  friend AcString GetDriveForRoottypePath(const CAdUiVolumeDescriptor*);
  friend bool WasAbsoluteHelper(path_category pc);
public:
  CAdUiPathname(void);
  CAdUiPathname(const CAdUiPathname&);
  virtual ~CAdUiPathname();
  void Empty(void);
  virtual PathErr Parse(const wchar_t*, bool wildcard_ok = false);
  PathErr ParseRelative(const wchar_t* name, const CAdUiPathname* relpath, bool wildcard_ok = false);
  bool ParseAndOSFind(const wchar_t*);
  const CAdUiPathname& operator=(const CAdUiPathname& pathSrc);
  const CAdUiPathname& operator=(const CAdUiPathname* pathSrc);
  bool GetUniqueName(CAdUiPathname&, bool alwaysMangle = false) const;
  void GetFilename(AcString&) const;
  void GetExtension(AcString&) const;
  void GetBasename(AcString&) const;
  void GetParent(CAdUiPathname&) const;
  PathErr Trim(void);
  PathErr TrimSlash(void);
  PathErr TrimComponent(void);
  PathErr Append(const wchar_t*);
  PathErr AppendSlash(void);
  PathErr AppendComponent(const wchar_t*);
  PathErr AddExtensionAlways(const wchar_t*);
  PathErr AddExtensionIfNoMatch(const wchar_t*);
  PathErr ReplaceExtensionAlways(const wchar_t*);
  PathErr ReplaceExtensionIfNoMatch(const wchar_t*);
  void RemoveExtensionAlways(void);
  void RemoveExtensionIfMatch(const wchar_t*);
  void BaseToLower(void);
  void BaseToUpper(void);
  void RemoveSpaces(void);
  void GetDisplayName(AcString& strResult, int maxchars) const;
  const wchar_t* GetPathString(void) const;
  bool GetFullPath(AcString&) const;
  bool GetFullPath(wchar_t* pBuf, size_t strBuffLen) const;
  template <size_t nBufLen>
  inline bool GetFullPath(wchar_t (& buf)[nBufLen]) const
  {
    return this->GetFullPath(buf, nBufLen);
  }
  void GetFullUNCPath(AcString&) const;
  bool IsPath(void) const;
  bool IsEmpty(void) const;
  path_type GetPathType(void) const;
  const CAdUiVolumeDescriptor* GetVolumeDescriptor(void) const;
  bool PathMatch(const CAdUiPathname*) const;
  bool PathMatch(const wchar_t*) const;
  bool Exists(void);
  bool VerifyExtension(const wchar_t* extlist) const;
  bool HadPrefix(void) const;
  bool WasAbsolute(void) const;
  bool WasRoot(void) const;
  ADESK_DEPRECATED bool Open(FILE** fdp, const ACHAR* openmode);
        /// <summary>
        /// Try to open a file in read-only mode
        /// </summary>
        /// <param name="">Input File to open</param>
        /// <returns>Return true if the open succeeded, false otherwise.</returns>
  bool OpenReadOnly(Autodesk::AutoCAD::PAL::FileIO::File&);
        /// <summary>
        /// Try to open a file in write mode
        /// </summary>
        /// <param name="">Input File to open</param>
        /// <returns>Return true if the open succeeded, false otherwise.</returns>
  bool OpenWriteOnly(Autodesk::AutoCAD::PAL::FileIO::File&);
  bool Rename(const ACHAR* newname);
  bool Remove(void);
  path_status Status();
protected:
  path_type m_this_type;
  const CAdUiVolumeDescriptor* m_pvolume;
  AcString* m_pathbuffer;
  AcString* m_relpath;
  path_category m_path_cat;
  ACHAR m_separator;
  bool m_had_prefix;
  const CAdUiVolumeDescriptor* FindVolumeDescriptor(const AcString& vol_name) const;
  const CAdUiVolumeDescriptor* NewVolDescriptor(const AcString& vol_name) const;
  FS_TYPE GetFileSystem(AcString& vol_name) const;
  inline bool IsDeviceName(const AcString& str) const;
  static void Unquote(AcString&);
  ACHAR GetSeparator(void) const;
  virtual void AssignCopy(const CAdUiPathname&);
  static ACHAR GetLastCharacter(const AcString&);
private:
  void GetFirstExtInList(const wchar_t*, AcString&) const;
  void lstrncpy_x(wchar_t* dest, size_t destLen, const wchar_t* src, int nchars) const;
  void StripSpaces(AcString& work);
  void GetAttributes(const AcString* path, const AcString* relpath, path_type* this_type);
};
inline CAdUiPathname::CAdUiPathname(const CAdUiPathname& pathSrc)
{
  m_pathbuffer = nullptr;
  m_relpath = nullptr;
  AssignCopy(pathSrc);
}
inline path_type CAdUiPathname::GetPathType(void) const
{
  return m_this_type;
}
inline bool CAdUiPathname::IsPath(void) const
{
  return ((m_this_type == FILE_PATH) || (m_this_type == DIR_PATH) || (m_this_type == NEW_PATH) || (m_this_type == WC_PATH));
}
inline bool CAdUiPathname::IsEmpty(void) const
{
  return (m_this_type == NO_PATH);
}
inline const CAdUiVolumeDescriptor* CAdUiPathname::GetVolumeDescriptor(void) const
{
  return m_pvolume;
}
inline bool CAdUiPathname::HadPrefix(void) const
{
  return m_had_prefix;
}
inline const CAdUiPathname& CAdUiPathname::operator=(const CAdUiPathname& pathSrc)
{
  AssignCopy(pathSrc);
  return *this;
}
inline const CAdUiPathname& CAdUiPathname::operator=(const CAdUiPathname* pathSrc)
{
  AssignCopy ( *pathSrc);
  return *this;
}
inline bool CAdUiPathname::WasRoot(void) const
{
  return (m_path_cat == ROOT_TYPE);
}
#pragma  pack (pop)
