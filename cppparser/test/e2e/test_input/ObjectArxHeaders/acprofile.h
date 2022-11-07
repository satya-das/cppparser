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


#ifndef   _ACPROFILE_H__
#define   _ACPROFILE_H__

#include "acarray.h"
#include "AdAChar.h"
#include "acprofile-reactor.h"
#pragma pack (push, 8)

class AcApProfileStorage;

typedef AcArray<ACHAR *> AcApProfileNameArray;

class AcApProfileManager 
{
    public:
        virtual ~AcApProfileManager() { }

        virtual void ProfileRegistryKey(ACHAR *& strRegProfileKey,
                                        const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileStorage(AcApProfileStorage*& pStore,
                                        const ACHAR * strProfileName, 
                                        BOOL bCreateIfNotExists = TRUE)=0;
        virtual Acad::ErrorStatus FixedProfileStorage(AcApProfileStorage*& pStore, 
                                        BOOL bCreateIfNotExists = TRUE)=0;

        virtual int ProfileListNames(AcApProfileNameArray& nameList)=0;

        virtual Acad::ErrorStatus ProfileExport(const ACHAR * strProfileName,
                                                const ACHAR * exportFileName)=0;

        virtual Acad::ErrorStatus ProfileImport(const ACHAR * strProfileName,
                                                const ACHAR * importFileName,
                                                const ACHAR * profileDescription,
                                                Adesk::Boolean bImportPathInfo)=0; 

        virtual Acad::ErrorStatus ProfileDelete(const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileReset(const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileSetCurrent(const ACHAR * strProfileName)=0;

        virtual Acad::ErrorStatus ProfileCopy(const ACHAR * newProfileName,
                                              const ACHAR * oldProfileName,
                                              const ACHAR * newProfileDesc)=0;

        virtual Acad::ErrorStatus ProfileRename(const ACHAR * newProfileName,
                                                const ACHAR * oldProfileName,
                                                const ACHAR * newProfileDesc)=0;

        virtual void addReactor(AcApProfileManagerReactor* ) = 0;
        virtual void removeReactor(AcApProfileManagerReactor* ) = 0;

};

AcApProfileManager* acProfileManagerPtr();
#define acProfileManager acProfileManagerPtr()

class AcApProfileStorage
{
    public:
        virtual ~AcApProfileStorage() {}
        virtual Acad::ErrorStatus CreateNode(const ACHAR * pszNodePath, 
            IUnknown*& pUnknown) = 0;
        virtual Acad::ErrorStatus GetNode(const ACHAR * pszNodePath, 
            IUnknown*& pUnknown) = 0;
        virtual Acad::ErrorStatus ReplaceNode(const ACHAR * pszNodePath, 
            IUnknown* pUnknown) = 0;
        virtual Acad::ErrorStatus DeleteNode(const ACHAR * pszNodePath) = 0;
        virtual Acad::ErrorStatus GetStorageFile(AcString& pszFile) = 0;
        virtual Acad::ErrorStatus Save(void) = 0;
};


#pragma pack (pop)
#endif // _ACPROFILE_H__
