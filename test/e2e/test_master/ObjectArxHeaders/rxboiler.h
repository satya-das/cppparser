////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  rxboiler.h
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AC_RXBOILER_H
#  define AC_RXBOILER_H
#  include "AdAChar.h"
#  include "rxnames.h"
#  include "acbasedefs.h"
#  pragma  pack (push, 8)
class AcRxClass;
ACBASE_PORT AcRxClass* acrxFindAcRxClass(const ACHAR* pClassName);
#  define ACRX_AUTO_INIT_QUEUE_EXPR(CLASS_NAME)	 acrxQueueClassForInitialization(&CLASS_NAME::gpDesc, &CLASS_NAME::rxInit)
#  ifdef ACRX_AUTO_INIT
#    define ACRX_AUTO_INIT_DEFAULT(CLASS_NAME)	 ACRX_AUTO_INIT_QUEUE_EXPR(CLASS_NAME)
#  else 
#    define ACRX_AUTO_INIT_DEFAULT(CLASS_NAME)	 nullptr
#  endif
#  define ACRX_DEFINE_GPDESC(CLASS_NAME, AUTOINIT)	 \
    AcRxClass* CLASS_NAME::gpDesc = AUTOINIT(CLASS_NAME);
#  define ACRX_DECLARE_GPDESC(CLASS_NAME)	 \
    static AcRxClass* gpDesc; 
class AcRxObject;
template <typename T>
static AcRxObject* acrxInstantiateClass()
{
  return new T();
}
#  define ACRX_DECLARE_MEMBERS_EXPIMP(CLASS_NAME, EXPIMP)	 \
    friend AcRxObject* ::acrxInstantiateClass<CLASS_NAME>(); \
    EXPIMP virtual AcRxClass* isA() const override; \
    ACRX_DECLARE_GPDESC(CLASS_NAME); \
    EXPIMP static AcRxClass* desc(); \
    static CLASS_NAME* cast(const AcRxObject* inPtr) \
        { return ((inPtr == NULL) || !inPtr->isKindOf(CLASS_NAME::desc())) \
          ? NULL : (CLASS_NAME*)inPtr; }; \
    static void rxInit(); \
    static void rxInit(AppNameChangeFuncPtr)
#  define ACRX_EMPTY
#  define ACRX_DECLARE_MEMBERS(CLASS_NAME)	 \
    ACRX_DECLARE_MEMBERS_EXPIMP(CLASS_NAME, ACRX_EMPTY )
#  define ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, AUTOINIT)	 \
AcRxClass* CLASS_NAME::desc() \
{ \
    if (gpDesc == nullptr) \
        gpDesc = ::acrxFindAcRxClass(ACRX_T(#CLASS_NAME)); \
    return gpDesc; \
} \
AcRxClass* CLASS_NAME::isA() const \
{ \
    if (gpDesc == nullptr) \
        gpDesc = ::acrxFindAcRxClass(ACRX_T(#CLASS_NAME)); \
    return gpDesc; \
} \
ACRX_DEFINE_GPDESC(CLASS_NAME, AUTOINIT)
#  define ACRX_DEFINE_MEMBERS(CLASS_NAME)	 \
ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, ACRX_AUTO_INIT_DEFAULT)
#  include "AdAChar.h"
void ACBASE_PORT acrx_abort(const ACHAR* format, ...);
#  define ACRX_STATIC_CHECK(CLASS_NAME)	 \
    if (gpDesc!=nullptr) { \
        AcRxClass *pClass = ::acrxFindAcRxClass(ACRX_T(#CLASS_NAME)); \
        if (pClass) { \
            if (gpDesc == pClass) \
                return; \
            else \
                acrx_abort(ACRX_T(/*MSGO*/"Class mismatch")); \
        } \
    }
#  define ACRX_NO_CONS_DEFINE_MEMBERS_WORKER(AUTOINIT,CLASS_NAME,PARENT_CLASS)	 \
ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, AUTOINIT); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS)); \
}
#  define ACRX_NO_CONS_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS)	 \
ACRX_NO_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_DEFAULT,CLASS_NAME, PARENT_CLASS)
#  define ACRX_NO_CONS_DEFINE_MEMBERS_AUTO(CLASS_NAME,PARENT_CLASS)	 \
ACRX_NO_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_QUEUE_EXPR, CLASS_NAME,PARENT_CLASS)
#  define ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_WORKER(AUTOINIT, CLASS_NAME,PARENT_CLASS, MAKEPROPS)	 \
ACRX_DEFINE_MEMBERS(CLASS_NAME); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        0, 0, 0, \
        0, 0, 0, 0, MAKEPROPS); \
}
#  define ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES(CLASS_NAME,PARENT_CLASS, MAKEPROPS)	 \
ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_WORKER(ACRX_AUTO_INIT_DEFAULT, CLASS_NAME,PARENT_CLASS, MAKEPROPS)
#  define ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_AUTO(CLASS_NAME,PARENT_CLASS, MAKEPROPS)	 \
ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_WORKER(ACRX_AUTO_INIT_QUEUE_EXPR, CLASS_NAME,PARENT_CLASS, MAKEPROPS)
#  define ACRX_CONS_DEFINE_MEMBERS_WORKER(AUTOINIT, CLASS_NAME,PARENT_CLASS,VERNO)	 \
ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, AUTOINIT); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        VERNO, &acrxInstantiateClass<CLASS_NAME>); \
}
#  define ACRX_CONS_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS,VERNO)	 \
ACRX_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_DEFAULT, CLASS_NAME, PARENT_CLASS, VERNO)
#  define ACRX_CONS_DEFINE_MEMBERS_AUTO(CLASS_NAME,PARENT_CLASS,VERNO)	 \
ACRX_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_QUEUE_EXPR, CLASS_NAME, PARENT_CLASS, VERNO)
#  define ACRX_DXF_DEFINE_MEMBERS	(CLASS_NAME,PARENT_CLASS,DWG_VERSION,\
              MAINTENANCE_VERSION,PROXY_FLAGS,DXF_NAME,APP) \
ACRX_DEFINE_MEMBERS(CLASS_NAME); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        DWG_VERSION,MAINTENANCE_VERSION,PROXY_FLAGS, \
        &acrxInstantiateClass<CLASS_NAME>, ACRX_T(#DXF_NAME), ACRX_T(#APP)); \
} \
void CLASS_NAME::rxInit(AppNameChangeFuncPtr ptr) { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        DWG_VERSION,MAINTENANCE_VERSION,PROXY_FLAGS, \
        &acrxInstantiateClass<CLASS_NAME>, ACRX_T(#DXF_NAME), ACRX_T(#APP), ptr); \
}
#  define ACRX_DXF_DEFINE_MEMBERS_WITH_PROPERTIES	(CLASS_NAME,PARENT_CLASS,DWG_VERSION,\
              MAINTENANCE_VERSION,PROXY_FLAGS,DXF_NAME,APP, MAKEPROPS) \
ACRX_DEFINE_MEMBERS(CLASS_NAME); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        DWG_VERSION,MAINTENANCE_VERSION,PROXY_FLAGS, \
        &acrxInstantiateClass<CLASS_NAME>, ACRX_T(#DXF_NAME), ACRX_T(#APP), NULL, MAKEPROPS); \
} \
void CLASS_NAME::rxInit(AppNameChangeFuncPtr ptr) { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        DWG_VERSION,MAINTENANCE_VERSION,PROXY_FLAGS, \
        &acrxInstantiateClass<CLASS_NAME>, ACRX_T(#DXF_NAME), ACRX_T(#APP), ptr, MAKEPROPS); \
}
#  pragma  pack (pop)
#endif
