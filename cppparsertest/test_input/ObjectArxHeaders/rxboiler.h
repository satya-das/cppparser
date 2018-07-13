//
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
//
// DESCRIPTION: ARX Class Boilerplate Macros

#ifndef AC_RXBOILER_H
#define AC_RXBOILER_H

#include "AdAChar.h"
#include "rxnames.h"
#include "acbasedefs.h"
#pragma pack (push, 8)

class AcRxClass;
// Look up the class name in the AcRx class dictionary
ACBASE_PORT AcRxClass * acrxFindAcRxClass(const ACHAR *pClassName);

// ACRX_DECLARE_MEMBERS(CLASS_NAME)
//
// Use this macro to declare the member-functions "isA()", "desc()"
// and "cast()" for the class "CLASS_NAME" which is derived (at some
// level) from AcRxObject.  Declaring these functions is required for
// the class to participate in the AcRxObject runtime type identification
// mechanism.
//
// Note that you don't have to declare the class member-functions "isA()",
// "desc()" and "cast()" (i.e., this macro isn't needed) if you don't need
// to distinguish a class at runtime any further than one of its Rx-defined
// base classes.
//
// The static "rxInit()" function and the static "gpDesc" pointer, also
// declared by this macro, exist to allow us to implement the methods
// "isA()", "desc()" and "cast()".  The macros ACRX_DEFINE_MEMBERS()
// and ACRX_xxx_DEFINE_MEMBERS() allow you to define the various
// functions and static variables declared with this macro.
//
// This macro MUST BE used inside the "public" section of the class
// declaration.  For example, use it like this:
//
//     class Foo : public AcRxObject
//     {
//     public:
//         ACRX_DECLARE_MEMBERS(Foo);
//         ...etc...
//     };
//
#define ACRX_AUTO_INIT_QUEUE_EXPR(CLASS_NAME) acrxQueueClassForInitialization(&CLASS_NAME::gpDesc, &CLASS_NAME::rxInit)

#ifdef ACRX_AUTO_INIT //define this if you want auto initialization of AcRxClass-es in your DLL
#define ACRX_AUTO_INIT_DEFAULT(CLASS_NAME) ACRX_AUTO_INIT_QUEUE_EXPR(CLASS_NAME)
#else
#define ACRX_AUTO_INIT_DEFAULT(CLASS_NAME) nullptr
#endif


#define ACRX_DEFINE_GPDESC(CLASS_NAME, AUTOINIT) \
    AcRxClass* CLASS_NAME::gpDesc = AUTOINIT(CLASS_NAME);


#define ACRX_DECLARE_GPDESC(CLASS_NAME) \
    static AcRxClass* gpDesc; 

class AcRxObject;
template <typename T>
static AcRxObject* acrxInstantiateClass() { return new T();}

#define ACRX_DECLARE_MEMBERS_EXPIMP(CLASS_NAME, EXPIMP) \
    friend AcRxObject* ::acrxInstantiateClass<CLASS_NAME>(); \
    EXPIMP virtual AcRxClass* isA() const ADESK_OVERRIDE; \
    ACRX_DECLARE_GPDESC(CLASS_NAME); \
    EXPIMP static AcRxClass* desc(); \
    static CLASS_NAME* cast(const AcRxObject* inPtr) \
        { return ((inPtr == NULL) || !inPtr->isKindOf(CLASS_NAME::desc())) \
          ? NULL : (CLASS_NAME*)inPtr; }; \
    static void rxInit(); \
    static void rxInit(AppNameChangeFuncPtr)

#define ACRX_EMPTY

#define ACRX_DECLARE_MEMBERS(CLASS_NAME) \
    ACRX_DECLARE_MEMBERS_EXPIMP(CLASS_NAME, ACRX_EMPTY )

// ACRX_DEFINE_MEMBERS(CLASS_NAME)
//
// Use this macro to define the member functions declared with
// the ACRX_DECLARE_MEMBERS() macro.
//
// This macro does not create the associated AcRxClass object; that is
// the responsibility of a service implementation, i.e., the "rxInit()"
// static member-function declared by the ACRX_DECLARE_MEMBERS() macro.
//
// The ACRX_xxx_DEFINE_MEMBERS() macros defined below use this macro,
// as well as provide alternate definitions for the "rxInit()" function.
//
#define ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, AUTOINIT) \
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

#define ACRX_DEFINE_MEMBERS(CLASS_NAME) \
ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, ACRX_AUTO_INIT_DEFAULT)

// ACRX_NO_CONS_DEFINE_MEMBERS()
// ACRX_CONS_DEFINE_MEMBERS()
// ACRX_DXF_DEFINE_MEMBERS()
//
// These macros are similar to the ACRX_DEFINE_MEMBERS() macro,
// except they also provide implementations for the static "rxInit()"
// function.
//
// The differences between the three macros are manifested in how
// the AcRxClass object responds to AcRxClass::create() and
// AcRxClass::dxfName() member functions.
//
// ACRX_NO_CONS_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS)
//
//       For abstract classes and desired concrete classes, for
//       which no pseudo-constructor function is associated with
//       its AcRxClass object.  For example, a class with a
//       protected/private default constructor should use
//       this macro.  <ClassName>::desc()->create()
//       returns NULL for AcRxClass objects defined this way.
//       The class has no direct DWG or DXF file representation.
//
// ACRX_CONS_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS)
//
//       For concrete classes with a meaningful default constructor.
//       Causes <ClassName::desc()->create() to return an instance of the
//       object created with its default constructor. Causes
//       <ClassName::desc()->dxfName() to return NULL.
//
// ACRX_DXF_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS,PROXY_FLAGS,DXF_NAME,APP)
//
//       For classes directly instantiated in DWG and DXF,
//       <ClassName::desc()->create() returns an instance of the
//       object created with its default constructor.
//       <ClassName::desc()->dxfName() defines a string that
//       the AutoCAD database queries as the preferred DXF
//       "object type" name.
//
// ACRX_STATIC_CHECK(CLASS_NAME)
//       Helper macro used by the various rxInit() implementations.
//       It makes sure that the static varible gpDesc is appropriately
//       reinitialized when necessary.
//       Note that this macro does a return from the current function
//       if gpDesc is already initialized.
#include "AdAChar.h"

extern "C" void ACBASE_PORT acrx_abort (const ACHAR * format, ...);
#define ACRX_STATIC_CHECK(CLASS_NAME) \
    if (gpDesc!=nullptr) { \
        AcRxClass *pClass = ::acrxFindAcRxClass(ACRX_T(#CLASS_NAME)); \
        if (pClass) { \
            if (gpDesc == pClass) \
                return; \
            else \
                acrx_abort(ACRX_T(/*MSGO*/"Class mismatch")); \
        } \
    }

#define ACRX_NO_CONS_DEFINE_MEMBERS_WORKER(AUTOINIT,CLASS_NAME,PARENT_CLASS) \
ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, AUTOINIT); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS)); \
}

#define ACRX_NO_CONS_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS) \
ACRX_NO_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_DEFAULT,CLASS_NAME, PARENT_CLASS)

#define ACRX_NO_CONS_DEFINE_MEMBERS_AUTO(CLASS_NAME,PARENT_CLASS) \
ACRX_NO_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_QUEUE_EXPR, CLASS_NAME,PARENT_CLASS)

#define ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_WORKER(AUTOINIT, CLASS_NAME,PARENT_CLASS, MAKEPROPS) \
ACRX_DEFINE_MEMBERS(CLASS_NAME); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        0, 0, 0, \
        0, 0, 0, 0, MAKEPROPS); \
}
#define ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES(CLASS_NAME,PARENT_CLASS, MAKEPROPS) \
ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_WORKER(ACRX_AUTO_INIT_DEFAULT, CLASS_NAME,PARENT_CLASS, MAKEPROPS)

#define ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_AUTO(CLASS_NAME,PARENT_CLASS, MAKEPROPS) \
ACRX_NO_CONS_DEFINE_MEMBERS_WITH_PROPERTIES_WORKER(ACRX_AUTO_INIT_QUEUE_EXPR, CLASS_NAME,PARENT_CLASS, MAKEPROPS)

#define ACRX_CONS_DEFINE_MEMBERS_WORKER(AUTOINIT, CLASS_NAME,PARENT_CLASS,VERNO) \
ACRX_DEFINE_MEMBERS_WORKER(CLASS_NAME, AUTOINIT); \
void CLASS_NAME::rxInit() { \
    ACRX_STATIC_CHECK(CLASS_NAME); \
    gpDesc = newAcRxClass(ACRX_T(#CLASS_NAME), ACRX_T(#PARENT_CLASS), \
        VERNO, &acrxInstantiateClass<CLASS_NAME>); \
}
#define ACRX_CONS_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS,VERNO) \
ACRX_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_DEFAULT, CLASS_NAME, PARENT_CLASS, VERNO)

#define ACRX_CONS_DEFINE_MEMBERS_AUTO(CLASS_NAME,PARENT_CLASS,VERNO) \
ACRX_CONS_DEFINE_MEMBERS_WORKER(ACRX_AUTO_INIT_QUEUE_EXPR, CLASS_NAME, PARENT_CLASS, VERNO)

#define ACRX_DXF_DEFINE_MEMBERS(CLASS_NAME,PARENT_CLASS,DWG_VERSION,\
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

#define ACRX_DXF_DEFINE_MEMBERS_WITH_PROPERTIES(CLASS_NAME,PARENT_CLASS,DWG_VERSION,\
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
#pragma pack (pop)
#endif
