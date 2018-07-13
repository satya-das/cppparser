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
// Written by Cyrille Fauvel
// Autodesk Developer Technical Services

//-----------------------------------------------------------------------------
#pragma once

#include "rxdefs.h"
#include "rxdlinkr.h"

class AcRxClass;

//-----------------------------------------------------------------------------
#define _RXST(a) _ACRX_T(a)

//-----------------------------------------------------------------------------
struct _DBX_REGISTER_OBJECT_ENTRY {
    AcRxClass* (*desc) () ;
    void (*rxInit) () ;
    bool bRegistered ;
} ;

#pragma section("DBXCUSTOBJ$__a", read, shared)
#pragma section("DBXCUSTOBJ$__z", read, shared)
#pragma section("DBXCUSTOBJ$__m", read, shared)

#ifndef _ADESK_MAC_
#define DBXCUSTOBJ_FIRST_ENTRYNAME "DBXCUSTOBJ$__a"
#else
#define DBXCUSTOBJ_FIRST_ENTRYNAME "DBXCUSTOBJ$__m"
#endif
#define DBXCUSTOBJ_LAST_ENTRYNAME "DBXCUSTOBJ$__z"

extern "C" {
    __declspec(selectany) __declspec(allocate(DBXCUSTOBJ_FIRST_ENTRYNAME)) _DBX_REGISTER_OBJECT_ENTRY* __pDbxCustObjMapEntryFirst =NULL ;
    __declspec(selectany) __declspec(allocate(DBXCUSTOBJ_LAST_ENTRYNAME)) _DBX_REGISTER_OBJECT_ENTRY* __pDbxCustObjMapEntryLast =NULL ;
}


#ifndef _ADESK_MAC_
#if defined(_WIN64) || defined(_AC64)
#define ACDB_REGISTER_OBJECT_ENTRY_PRAGMA(classname) __pragma(comment(linker, "/include:__pDbxCustObjMap_" #classname)) ;
#else
#define ACDB_REGISTER_OBJECT_ENTRY_PRAGMA(classname) __pragma(comment(linker, "/include:___pDbxCustObjMap_" #classname)) ;
#endif
#else
#define ACDB_REGISTER_OBJECT_ENTRY_PRAGMA(classname)
#endif


#define ACDB_REGISTER_OBJECT_ENTRY_AUTO(classname) \
    __declspec(selectany) _DBX_REGISTER_OBJECT_ENTRY __DbxCustObjMap_##classname = { classname::desc, classname::rxInit } ; \
    extern "C" __declspec(allocate("DBXCUSTOBJ$__m")) __declspec(selectany) _DBX_REGISTER_OBJECT_ENTRY* __pDbxCustObjMap_##classname = &__DbxCustObjMap_##classname ; \
    ACDB_REGISTER_OBJECT_ENTRY_PRAGMA(classname)

//-----------------------------------------------------------------------------
#define DISPATCH_PKTMSG(pktmsg) case AcRx::pktmsg: return (On_ ##pktmsg (pkt))

extern HINSTANCE _hdllInstance ;

//-----------------------------------------------------------------------------
class AcRxDbxApp {

protected:
    HINSTANCE m_hdllInstance ;
    bool m_bUnlocked ;
    bool m_bMDIAware ;

public:
    AcRxDbxApp () : m_hdllInstance(NULL), m_bUnlocked(true), m_bMDIAware(true) {}

    virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		//- Save the module instance
		m_hdllInstance =_hdllInstance ;
        //----- Unlock application, so user can unload it
        if ( m_bUnlocked == true )
            acrxDynamicLinker->unlockApplication (pkt) ;
        //----- Register the application as MDI capable in ACAD environment
        if ( m_bMDIAware == true )
            acrxDynamicLinker->registerAppMDIAware (pkt) ;
        //----- Self-register application components such as
        //----- COM server / Custom entity registry information, ...
        RegisterServerComponents () ;
        //----- Register ObjectDBX custom classes
        int nDbxCustObjCount =0 ;
        _DBX_REGISTER_OBJECT_ENTRY **ppDbxCustObjMapEntryFirst =&__pDbxCustObjMapEntryFirst + 1 ;
        _DBX_REGISTER_OBJECT_ENTRY **ppDbxCustObjMapEntryLast =&__pDbxCustObjMapEntryLast ;
        for ( _DBX_REGISTER_OBJECT_ENTRY **ppEntry =ppDbxCustObjMapEntryFirst ; ppEntry < ppDbxCustObjMapEntryLast ; ppEntry++ ) {
            if ( *ppEntry != NULL ) {
                nDbxCustObjCount++ ;
                (*ppEntry)->rxInit () ;
                (*ppEntry)->bRegistered =true ;
            }
        }
        if ( nDbxCustObjCount > 0 )
            acrxBuildClassHierarchy () ;
        return (AcRx::kRetOK) ;
    }
    virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
        _DBX_REGISTER_OBJECT_ENTRY **ppDbxCustObjMapEntryFirst =&__pDbxCustObjMapEntryFirst + 1 ;
        _DBX_REGISTER_OBJECT_ENTRY **ppDbxCustObjMapEntryLast =&__pDbxCustObjMapEntryLast ;
        for ( _DBX_REGISTER_OBJECT_ENTRY **ppEntry =ppDbxCustObjMapEntryFirst ; ppEntry < ppDbxCustObjMapEntryLast ; ppEntry++ ) {
            if ( *ppEntry != NULL && (*ppEntry)->bRegistered == true )
                DeleteClassAndDescendant (ppEntry) ;
        }
        return (AcRx::kRetOK) ;
    }
    virtual AcRx::AppRetCode On_kLoadDwgMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kUnloadDwgMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kInvkSubrMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kCfgMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kEndMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kQuitMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kSaveMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kDependencyMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kNoDependencyMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kOleUnloadAppMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kPreQuitMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kInitDialogMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kEndDialogMsg (void *pkt) { return (AcRx::kRetOK) ; }
    virtual AcRx::AppRetCode On_kNullMsg (void *pkt) { return (AcRx::kRetOK) ; }

    AcRx::AppRetCode acrxEntryPoint (AcRx::AppMsgCode msg, void *pkt) {
        switch ( msg ) {
            DISPATCH_PKTMSG (kInitAppMsg) ;
            DISPATCH_PKTMSG (kUnloadAppMsg) ;
            DISPATCH_PKTMSG (kLoadDwgMsg) ;
            DISPATCH_PKTMSG (kUnloadDwgMsg) ;
            DISPATCH_PKTMSG (kInvkSubrMsg) ;
            DISPATCH_PKTMSG (kCfgMsg) ;
            DISPATCH_PKTMSG (kEndMsg) ;
            DISPATCH_PKTMSG (kQuitMsg) ;
            DISPATCH_PKTMSG (kSaveMsg) ;
            DISPATCH_PKTMSG (kDependencyMsg) ;
            DISPATCH_PKTMSG (kNoDependencyMsg) ;
            DISPATCH_PKTMSG (kOleUnloadAppMsg) ;
            DISPATCH_PKTMSG (kPreQuitMsg) ;
            DISPATCH_PKTMSG (kInitDialogMsg) ;
            DISPATCH_PKTMSG (kEndDialogMsg) ;
            DISPATCH_PKTMSG (kNullMsg) ;
        }
        return (AcRx::kRetOK) ;
    }

    virtual void RegisterServerComponents () = 0 ;
    HINSTANCE &GetModuleInstance () { return (m_hdllInstance) ; }

private:
    void DeleteClassAndDescendant (_DBX_REGISTER_OBJECT_ENTRY **ppEntry) {
        _DBX_REGISTER_OBJECT_ENTRY **ppDbxCustObjMapEntryFirst =&__pDbxCustObjMapEntryFirst + 1 ;
        _DBX_REGISTER_OBJECT_ENTRY **ppDbxCustObjMapEntryLast =&__pDbxCustObjMapEntryLast ;
        for ( _DBX_REGISTER_OBJECT_ENTRY **ppEntry2 =ppDbxCustObjMapEntryFirst ; ppEntry2 < ppDbxCustObjMapEntryLast ; ppEntry2++ ) {
            if ( *ppEntry2 != NULL && *ppEntry2 != *ppEntry && (*ppEntry2)->bRegistered == true ) {
                if ( (*ppEntry2)->desc ()->myParent () == (*ppEntry)->desc () )
                    DeleteClassAndDescendant (ppEntry2) ;
            }
        }
        deleteAcRxClass ((*ppEntry)->desc ()) ;
        (*ppEntry)->bRegistered =false ;
    }
} ;

//-----------------------------------------------------------------------------
AcRxDbxApp *acrxGetApp () ;

#define IMPLEMENT_ARX_ENTRYPOINT_STD(classname) \
	HINSTANCE _hdllInstance =NULL ; \
    class classname entryPointObject ; \
    AcRxDbxApp *acrxGetApp () { return (&entryPointObject) ; } \
    extern "C" AcRx::AppRetCode __declspec(dllexport) acrxEntryPoint (AcRx::AppMsgCode msg, void *pkt) { \
        return (entryPointObject.acrxEntryPoint (msg, pkt)) ; \
    }

//#define _hdllInstance \
//	acrxGetApp ()->GetModuleInstance ()
//extern HINSTANCE _hdllInstance ;

//-----------------------------------------------------------------------------
#define IMPLEMENT_ARX_ENTRYPOINT_CLR(classname) IMPLEMENT_ARX_ENTRYPOINT_STD(classname)
#define IMPLEMENT_ARX_ENTRYPOINT(classname) IMPLEMENT_ARX_ENTRYPOINT_STD(classname)

//- This line allows us to get rid of the .def file in ARX projects
#if !defined(_WIN64) && !defined (_AC64)
#pragma comment(linker, "/export:_acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif
