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
// Name:            rxregsvc.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _RXREGSVC_H
#  define _RXREGSVC_H	1
#  include "rxdlinkr.h"
#  include "adesk.h"
#  include "AcArray.h"
#  include "PAL/api/AcLocale.h"
#  pragma  pack (push, 8)
bool acrxLoadModule(const ACHAR* moduleName, bool printit, bool asCmd = false);
bool acrxLoadApp(const ACHAR* appname, bool asCmd = false);
bool acrxUnloadModule(const ACHAR* moduleName, bool asCmd = false);
bool acrxUnloadApp(const ACHAR* appName, bool asCmd = false);
ACDBCORE2D_PORT AcArray<wchar_t *>* acrxLoadedApps();
ACDBCORE2D_PORT bool acrxLoadAutoloadApps(const ACHAR* appname);
ACDBCORE2D_PORT bool acrxUnloadAutoloadApps(const ACHAR* appname);
ACDBCORE2D_PORT bool acrxAppIsLoaded(const ACHAR* pAppName);
const ACHAR* acrxObjectDBXRegistryKey();
/// <summary>
/// This function returns product locale
/// </summary>
/// <returns>Return product locale.</returns>
ACDBCORE2D_PORT AcLocale acrxProductLocale();
ACDBCORE2D_PORT AcadApp::ErrorStatus acrxRegisterApp(AcadApp::LoadReasons alr, const ACHAR* logicalName);
ACDBCORE2D_PORT AcadApp::ErrorStatus acrxUnregisterApp(const ACHAR* logicalname);
void* acrxGetServiceSymbolAddr(const ACHAR* serviceName, const ACHAR* symbol);
void* acrxRegisterService(const ACHAR* serviceName);
bool acrxServiceIsRegistered(const ACHAR* serviceName);
bool acrxUnlockApplication(void* appId);
bool acrxApplicationIsLocked(const ACHAR* modulename);
bool acrxLockApplication(void* appId);
bool acrxIsAppMDIAware(const ACHAR* moduleName);
bool acrxRegisterAppMDIAware(void* appId);
bool acrxRegisterAppNotMDIAware(void* appId);
#  pragma  pack (pop)
#endif
