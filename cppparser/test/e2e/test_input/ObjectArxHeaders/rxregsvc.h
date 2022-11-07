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
#ifndef   _RXREGSVC_H
#define   _RXREGSVC_H 1

#include "rxdlinkr.h"
#include "adesk.h"
#include "AcArray.h"
#include "PAL/api/AcLocale.h"
#pragma pack (push, 8)

// Load a module, given its file name. 
//
bool acrxLoadModule(const ACHAR * moduleName, bool printit, bool asCmd=false);

// Load an app, given its logical app name. 
//
bool acrxLoadApp(const ACHAR * appname, bool asCmd=false);

// UnLoad a module, given its file name. Module's services and classes are 
// queried for dependencies.  If all module elements have no dependencies, 
// then unload can proceed.
//
bool acrxUnloadModule(const ACHAR * moduleName, bool asCmd=false);

// UnLoad an app, given its logical app name.
//
bool acrxUnloadApp(const ACHAR * appName, bool asCmd=false);

// Return an array containing names of applications
// that are currently loaded.  Caller must delete the names
// and the array afterwards.  See acrxAppIsLoaded(), if that's
// all you want to use this for.
//
ACDBCORE2D_PORT AcArray<wchar_t *> * acrxLoadedApps();


// Given its logical app name, load all its auto loaded components
// In the demand loaded registry setting, there is a subkey "AutoloadApps"
// that developers can add to put their app to be loaded when the other
// application is loaded. 
//
// %ProductRegRoot%\Applications\SomeApp\AutoloadApps
//
// For example:
// HCKU\..\%ProductRegRoot%\Applications\EtransmitEngine\AutoloadApps
//      AcStETransmit           
ACDBCORE2D_PORT bool acrxLoadAutoloadApps(const ACHAR * appname);

// Given its logical app name, unload all its auto loaded components
// In the demand loaded registry setting, there is a subkey "AutoloadApps"
// that developers can add to put their app to be loaded when the other
// application is loaded. 
//
// %ProductRegRoot%\Applications\SomeApp\AutoloadApps
//
ACDBCORE2D_PORT bool acrxUnloadAutoloadApps(const ACHAR * appname);



// Find out if an app is loaded.  Name is case independent
// but must include the extension (.arx etc).
//
ACDBCORE2D_PORT bool acrxAppIsLoaded(const ACHAR  *pAppName);

// Return a const string containing the ObjectDBX Registry root,
// e.g. Software\Autodesk\ObjectDBX\R15.0
//
const ACHAR * acrxObjectDBXRegistryKey();

/// <summary>
/// This function returns product locale
/// </summary>
/// <returns>Return product locale.</returns>
ACDBCORE2D_PORT AcLocale acrxProductLocale();

// Write an entry to the NT/WIN95 system registry for this app.
// Returns:
// AcadApp::eOk if success.
// AcadApp::eKeyExists if entry already exists and can't be over written.
// AcadApp::eRejected if the write could not be completed.
//
ACDBCORE2D_PORT
AcadApp::ErrorStatus acrxRegisterApp(AcadApp::LoadReasons alr,
        const ACHAR  *logicalName);

// Remove app entry from the NT/WIN95 system registry.
// Returns:
// AcadApp::eOk if success.
// AcadApp::eRejected if entry cannot be removed.
// AcadApp::eKeyNotFound if entry cannot be found.
//
ACDBCORE2D_PORT
AcadApp::ErrorStatus acrxUnregisterApp(const ACHAR  *logicalname);

// return a void * representing a handle to the module that
// registered the service, NIL if service is not present.
//
// For be use in C API libraries to link up stub entry points with
// real ones.  C++ libraries can use this function as well. 
//
void * acrxGetServiceSymbolAddr(const ACHAR * serviceName, const ACHAR * symbol);

// Tell system that the service represented by serviceName string is
// present in this module.  The system registers an instance
// of AcRxService with this name, for internal use.  
//
void* acrxRegisterService(const ACHAR * serviceName);

// Return boolean indicating whether named service is registered
// and present in the system. 
//
bool acrxServiceIsRegistered(const ACHAR * serviceName);


// Unlocks an application to enable it from being unloaded in mid-session.
// The default is that applications are locked, and hence unloadable in
// mid-session. The appId argument is the Id passed in as a void* during
// the AcRx::kInitAppMsg call back when the application is loaded. Return
// of non-zero means success.
//
bool acrxUnlockApplication(void* appId);

// Returns non-zero if the specified app is locked.
//
bool acrxApplicationIsLocked(const ACHAR * modulename);

// Symmetric to acrxUnlockApplication. Locks it, and hence prevents it from
// being unloaded in mid-session. Return of non-zero means success.
//
bool acrxLockApplication(void* appId);

// acrxApplicationsIsMDIAware() 
// Retruns non-zero if application has registered itself as MDI aware during its kInitApp msg
//
bool acrxIsAppMDIAware(const ACHAR  * moduleName);

// acrxSetApplicationMDIAware() 
// Register Application as MDI aware default is NOT MDI aware
//
bool acrxRegisterAppMDIAware(void* appId);

// acrxSetApplicationNotMDIAware() 
// ARX application is NOT MDI aware this is the default.
//
bool acrxRegisterAppNotMDIAware(void* appId);


#pragma pack (pop)
#endif
