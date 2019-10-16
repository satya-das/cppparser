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
#pragma  pack (push, 8)
class AFILE;
class CAcUiPathname : public CAdUiPathname
{
public:
  ACCORE_PORT CAcUiPathname(void);
  ACCORE_PORT CAcUiPathname(const CAcUiPathname&);
  ACCORE_PORT virtual ~CAcUiPathname();
  ACCORE_PORT virtual PathErr Parse(const wchar_t*, bool wildcard_ok = false) override;
  ACCORE_PORT int Status(void);
  ACCORE_PORT bool Open(AFILE** fdp, const wchar_t* openmode);
  const CAcUiPathname& operator=(const CAcUiPathname& pathSrc);
  const CAcUiPathname& operator=(const CAcUiPathname* pathSrc);
protected:
  ACCORE_PORT virtual void AssignCopy(const CAcUiPathname&);
};
inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname& pathSrc)
{
  AssignCopy(pathSrc);
  return *this;
}
inline const CAcUiPathname& CAcUiPathname::operator=(const CAcUiPathname* pathSrc)
{
  AssignCopy ( *pathSrc);
  return *this;
}
#pragma  pack (pop)
