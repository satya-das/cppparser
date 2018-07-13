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
// DESCRIPTION:
//
// This file contains the extension to the standard set of primitive-
// type names that should be shared by all Autodesk developers, both
// in-house and third-party.  All new code and modules written in C++
// should use these type names along with those supplied by C++ itself
// (for example, int, long, float, double, etc.)
//
// Note that C++ 11 (and VC11) now provide standard fixed size integer types
// such as int16_t, int32_t, etc, and those are now used here. Developers
// are encouraged to migrate over to using the standard C++ types and
// the Adesk::Int* and UInt* types may eventually be deprecated.
//
// See adeskabb.h for abbreviations of the following names.

#ifndef   _ADESK_H
#define   _ADESK_H

#include <cstdint>             // int16_t, uint32_t, etc
#include <stddef.h>            // size_t
#include "AdAChar.h"            // ACHAR typedef

#define Adesk_Boolean_is_bool 1
#define Adesk_Int32_is_int 1


#pragma pack (push, 8)

#if defined(_MSC_VER)
#ifndef _ADESK_CROSS_PLATFORM_
    #define _ADESK_WINDOWS_ 1
#endif
#elif defined(__clang__)
#if defined(_ADESK_MAC_)
    #define __w64
#endif

#endif

#if (defined(_MSC_VER) && defined(_WIN64)) || (defined(__clang__) && defined(__LP64__))
#define _AC64 1
#endif

struct Adesk
{
    // The types Int8, Int16 and Int32 will be conditionally compiled
    // to guarantee that each one represents an integer type of exactly
    // 8, 16 and 32 bits respectively.    These are to be used only when
    // the EXACT size of the integer is critical.
    //
    // We also need to be sure to use the Adesk::Int32 and Adesk::UInt32
    // datatypes rather than a long now that we support OSX 64-bit builds.
    //
    // Unlike Windows-64, on OSX-64 , a long is 64-bits. Any code that
    // assumes sizeof(int) == sizeof(long) will potentially have bugs. The
    // fix is to consistently use Adesk::Int32 and Adesk::UInt32 in place
    // of longs so we can normalize this all between the two platforms.
    //
    typedef int8_t      Int8;
    typedef int16_t     Int16;

    //
    // The unsigned versions of the above types.
    //
    typedef uint8_t     UInt8;
    typedef uint16_t    UInt16;

    typedef int32_t     Int32;
    typedef uint32_t    UInt32;

    typedef int64_t     Int64;
    typedef uint64_t    UInt64;

    // Convenient abbreviations (use optionally).
    // Todo: consider removing these from adesk.h
    //
    typedef unsigned char  uchar;
    typedef unsigned short ushort;
    typedef unsigned int   uint;

    // integer/unsigned integers that can hold a pointer value.
    // These change size depending on the platform and should NEVER
    // be streamed out to permanent storage.
#if !defined(_WIN64) && !defined (_AC64)
    static_assert(sizeof(void *) == 4, "ptr size in 32-bit windows build?");
    typedef int32_t             LongPtr;
    typedef uint32_t            ULongPtr;
    typedef int32_t             IntPtr;
    typedef uint32_t            UIntPtr;
#else   // _WIN64 || _AC64

    static_assert(sizeof(void *) == 8, "ptr size in 64-bit build?");
    typedef int64_t             LongPtr;
    typedef uint64_t            ULongPtr;
    typedef int64_t             IntPtr;
    typedef uint64_t            UIntPtr;

#endif // _WIN64 || _AC64

    typedef LongPtr IntDbId;
    typedef IntPtr GsMarker;

    // Logical type (Note: never use int when Boolean is intended!)
    // Please transition from Boolean type to native bool..
    //
    typedef bool       Boolean;
    static const bool kFalse = false;
    static const bool kTrue = true;

    using Time64 = int64_t;
};

// Please transition from NULL macro to native nullptr..
#undef NULL
#define NULL 0

#ifdef _ADESK_MAC_
#ifdef nil
#undef nil
#endif
#define nil __DARWIN_NULL
#endif

#pragma pack (pop)

// Use ADESK_NO_VTABLE on base classes which:
//   1. have virtual methods
//   2. are never instantiated
//   3. have a ctor and/or a dtor
//   4. do not call any virtual methods in the ctor or dtor
// This allows the compiler to avoid assigning a vtable pointer at
// the top of the base class's ctor and dtor.  So the vtable itself
// and any methods it points to which aren't used elsewhere can be
// omitted by the linker and reduce overall space.
//
// Make sure though that the base class is never instantiated.  Making
// the ctor protected or using pure virtual methods can help with this.
//
#if defined(_MSC_VER)
    #define ADESK_NO_VTABLE           __declspec(novtable)
    #define ADESK_STDCALL             __stdcall
    #define ADESK_DEPRECATED          __declspec(deprecated)
    #define ADESK_DEPRECATED_MSG(MSG) __declspec(deprecated(MSG))
    #define ADESK_DATA_IMPORT         __declspec(dllimport)
    #define ADESK_PACK_BEGIN __pragma(pack(push,1))
    #define ADESK_PACK_END __pragma(pack(pop))
    #define ADESK_HIDDEN_SYMBOL //symbols are hidden by default with MSVC toolchain
#else 
    #define ADESK_NO_VTABLE

    // The GCC 4.0 compiler doesn't seem to support the stdcall attribute
    // for 64-bit builds. If we use it, we just get a ton of warnings
    // from the compiler mentioning that it isn't supported.
    #if defined(__LP64__) || defined(__clang__)
        #define ADESK_STDCALL
    #else
        #define ADESK_STDCALL         __attribute__((stdcall))   
    #endif // __LP64__
    
    #define ADESK_DEPRECATED          __attribute__((__deprecated__))
    #define ADESK_DEPRECATED_MSG(MSG) __attribute__((__deprecated__))
    #define ADESK_DATA_IMPORT         extern

    // Redefine __declspec(method) for gcc
    #define __declspec(method) __declspec_##method
    #define _declspec(method) __declspec_##method

    #define __declspec_selectany      __attribute__ ((__weak__))

    #define __declspec_dllexport      __attribute__ ((__visibility__("default")))
    #define __declspec_dllimport      

    #define __declspec_noinline       __attribute__ ((__noinline__))
    #define __declspec_noreturn       __attribute__ ((__noreturn__))
    #define __declspec_deprecated     __attribute__ ((__deprecated__))
    #define __declspec_novtable
    #define __declspec_allocate(name) __attribute__ ((section("__DATA," name)))
    #define ADESK_PACK_BEGIN
    #define ADESK_PACK_END __attribute__((packed))
    #define ADESK_HIDDEN_SYMBOL   __attribute__ ((visibility("hidden"))) 
#endif //_MSC_VER

#if defined(_MSC_EXTENSIONS) || defined (__clang__)
#define ADESK_OVERRIDE  override
    #if defined(_MSC_VER) && (_MSC_VER <= 1600) //VS2010 and earlier
        #define ADESK_SEALED sealed
    #else
#define ADESK_SEALED final
    #endif
#else //_MSC_EXTENSIONS
    #define ADESK_OVERRIDE
    #define ADESK_SEALED 
#endif //_MSC_EXTENSIONS

#define MIGRATION_ERRORS

#if defined(_MSC_VER) && defined (MIGRATION_ERRORS) || defined(__clang__)
    #define ADESK_SEALED_VIRTUAL virtual
    #if !defined(ADESK_SEALED)
        #define ADESK_SEALED sealed
    #endif //ADESK_SEALED
#else //MIGRATION_ERRORS
    #define ADESK_SEALED_VIRTUAL 
    #if !defined(ADESK_SEALED)
        #define ADESK_SEALED sealed
    #endif //ADESK_SEALED
#endif //MIGRATION_ERRORS

//
// Compiler indentification
//
#if defined(__INTEL_COMPILER) || defined (_MSC_VER)
    #define ADESK_FORCE_INLINE __forceinline
#else //__INTEL_COMPILER || _MSC_VER
    #define ADESK_FORCE_INLINE inline
#endif //__INTEL_COMPILER || _MSC_VER

#ifdef _ADESK_WINDOWS_
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, wchar_t)
#else
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, int)
#endif

#ifdef _ADESK_UNITTEST_
#ifdef ADESK_SEALED
    #undef ADESK_SEALED
#endif
#define ADESK_SEALED
#endif

#ifdef _MSC_VER
#define ADESK_UNREFED_PARAM(x) x
#elif defined(__clang__)
#define ADESK_UNREFED_PARAM(x) (void)(x);
#else
#error Unknown compiler.
#endif

#ifdef _MSC_VER
#define ADESK_UNREACHABLE __assume(false)
#elif defined(__clang__)
#define ADESK_UNREACHABLE __builtin_unreachable()
#else
#error Unknown compiler.
#endif

#endif //_ADESK_H
