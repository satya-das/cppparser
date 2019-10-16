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
// DESCRIPTION
//
//  This file provides two useful classes for developers of MFC extensions
// to AutoCAD (ARX applications in particular). There is no source file
// correponding to this file; the classes should be implemented in the DLL
// that includes this file (a task simplified by using the provided macros).
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _AcExtensionModule_h
#  define _AcExtensionModule_h
#  if  _MSC_VER >= 1000
#    pragma  once
#  endif
/////////////////////////////////////////////////////////////////////////////
class CAcExtensionModule
{
public:
  CAcExtensionModule();
  ~CAcExtensionModule();
protected:
  BOOL m_bAttached;
  HINSTANCE m_hDefaultResource;
  HINSTANCE m_hModuleResource;
#  ifndef _ADESK_MAC_
  AFX_EXTENSION_MODULE m_module;
#  endif
public:
  BOOL Attached();
  HINSTANCE DefaultResourceInstance();
  HINSTANCE ModuleResourceInstance();
  BOOL AttachInstance(HINSTANCE hInst);
  void DetachInstance();
};
inline CAcExtensionModule::CAcExtensionModule()
  : m_bAttached(FALSE)
  , m_hDefaultResource(NULL)
  , m_hModuleResource(NULL)
{
#  ifndef _ADESK_MAC_
  m_module.bInitialized = FALSE;
  m_module.hModule = NULL;
  m_module.hResource = NULL;
  m_module.pFirstSharedClass = NULL;
  m_module.pFirstSharedFactory = NULL;
#  endif
}
inline CAcExtensionModule::~CAcExtensionModule()
{
}
inline BOOL CAcExtensionModule::Attached()
{
  return m_bAttached;
}
inline BOOL CAcExtensionModule::AttachInstance(HINSTANCE hInst)
{
  if (m_bAttached)
  {
    return FALSE;
  }
#  ifndef _ADESK_MAC_
  m_bAttached = AfxInitExtensionModule(m_module, hInst);
#  else 
  m_bAttached = true;
#  endif
  if (m_bAttached)
  {
    m_hDefaultResource = AfxGetResourceHandle();
    m_hModuleResource = hInst;
#  ifndef _ADESK_MAC_
    new CDynLinkLibrary(m_module);
#  endif
  }
  return m_bAttached;
}
inline HINSTANCE CAcExtensionModule::DefaultResourceInstance()
{
  return m_hDefaultResource;
}
inline void CAcExtensionModule::DetachInstance()
{
  if (m_bAttached)
  {
#  ifndef _ADESK_MAC_
    AfxTermExtensionModule(m_module);
#  endif
    m_bAttached = FALSE;
  }
}
inline HINSTANCE CAcExtensionModule::ModuleResourceInstance()
{
  return m_hModuleResource;
}
/////////////////////////////////////////////////////////////////////////////
class CAcModuleResourceOverride
{
public:
  CAcModuleResourceOverride();
  CAcModuleResourceOverride(HINSTANCE hInst);
  ~CAcModuleResourceOverride();
  static HINSTANCE ResourceInstance()
  {
    return m_extensionModule.ModuleResourceInstance();
  }
private:
  static CAcExtensionModule& m_extensionModule;
  HINSTANCE m_previousResourceInstance;
};
inline CAcModuleResourceOverride::CAcModuleResourceOverride()
  : CAcModuleResourceOverride(NULL)
{
}
inline CAcModuleResourceOverride::CAcModuleResourceOverride(HINSTANCE hInst)
{
  m_previousResourceInstance = AfxGetResourceHandle();
  HINSTANCE hInstanceToSet = m_extensionModule.ModuleResourceInstance();
  if (hInst)
  {
    hInstanceToSet = hInst;
  }
  AfxSetResourceHandle(hInstanceToSet);
}
inline CAcModuleResourceOverride::~CAcModuleResourceOverride()
{
  ASSERT(m_previousResourceInstance);
  AfxSetResourceHandle(m_previousResourceInstance);
  m_previousResourceInstance = NULL;
}
/////////////////////////////////////////////////////////////////////////////
#  define AC_DECLARE_EXTENSION_MODULE(exm)	        \
    extern CAcExtensionModule exm;
#  define AC_IMPLEMENT_EXTENSION_MODULE(exm)	      \
    CAcExtensionModule exm;                     \
    CAcExtensionModule& CAcModuleResourceOverride::m_extensionModule = exm;
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#endif
