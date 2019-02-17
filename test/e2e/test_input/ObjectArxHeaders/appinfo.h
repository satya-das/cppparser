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
// appinfo.h
//
// DESCRIPTION: Definition of class AcadAppInfo.  Used as part of the
//              unknown command demand load notification mechanism.
#pragma once
#ifndef _appinfo_h
#define _appinfo_h 1

#include "rxobject.h"
#include "AdAChar.h"
#include "rxdlinkr.h"

#pragma pack (push, 8)

class AcadAppInfoImp;

class AcadAppInfo: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcadAppInfo);

    enum CmdStatus {
        kNoAction    = 0,
        kRetry       = 1,
        kShowMsg     = 2,
        kNoModule    = 3
    };
    enum MgdType {
        kUnManaged   = 0,
        kManaged     = 1,
        kJavaScript  = 2
    };
    /// <summary>
    /// Optimization flags that can be passed to readFromRegistry
    /// </summary>
    enum ReadFlags
    {
        /// <summary>
        /// no optimization (default behavior)
        /// </summary>
        kNone = 0, 
        /// <summary>
        /// skip findFile, moduleName will return the string as found in the registry
        /// </summary>
        kSkipFindFileForModuleName = 1 
    };
    typedef AcadAppInfo::CmdStatus (*LoaderFunPtr)(void *);

    AcadAppInfo();
    virtual ~AcadAppInfo();

    const ACHAR *appName() const;
    void setAppName(const ACHAR *);

    const ACHAR *moduleName() const;
    void setModuleName(const ACHAR *);

    const ACHAR *appDesc() const;
    void setAppDesc(const ACHAR *);

    bool appImplements(const ACHAR *) const;
    
    AcadAppInfo::MgdType managed() const;
    void setManaged(AcadAppInfo::MgdType mgdType);

    ACDB_PORT AcadApp::ErrorStatus writeToRegistry();

    AcadApp::ErrorStatus readFromRegistry();
    /// <summary>
    /// Reads persistent storage and populates this instance. You must
    /// call setAppName prior to calling this function.
    /// </summary>
    ACDBCORE2D_PORT AcadApp::ErrorStatus readFromRegistry(ReadFlags flags);
    ACDBCORE2D_PORT AcadApp::ErrorStatus delFromRegistry();

    AcadAppInfo::CmdStatus runAppLoader();
    void setAppLoader(LoaderFunPtr);

    ACDBCORE2D_PORT AcadApp::LoadReasons loadReason() const;
    void setLoadReason(AcadApp::LoadReasons);
    AcadApp::ErrorStatus status() const;

    AcadApp::ErrorStatus writeGroupNameToRegistry(const ACHAR* group);

    AcadApp::ErrorStatus writeCommandNameToRegistry(const ACHAR* globalCmdName,
                                                    const ACHAR* localCmdName);
    
protected:
    AcadAppInfoImp * mpImp;
};

#pragma pack (pop)
//#endif /* defined (__cplusplus) */
#endif /* _appinfo_h */

