//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ADESK_H
#  define _ADESK_H
#  include <cstdint>
#  include <stddef.h>
#  include "AdAChar.h"
#  define Adesk_Boolean_is_bool	1
#  define Adesk_Int32_is_int	1
#  pragma  pack (push, 8)
#  if  defined(_MSC_VER)
#    ifndef _ADESK_CROSS_PLATFORM_
#      define _ADESK_WINDOWS_	1
#    endif
#  elif  defined(__clang__)
#    if  defined(_ADESK_MAC_)
#      define __w64
#    endif
#  endif
#  if  (defined(_MSC_VER) && defined(_WIN64)) || (defined(__clang__) && defined(__LP64__))
#    define _AC64	1
#  endif
struct Adesk
{
  typedef int8_t Int8;
  typedef int16_t Int16;
  typedef uint8_t UInt8;
  typedef uint16_t UInt16;
  typedef int32_t Int32;
  typedef uint32_t UInt32;
  typedef int64_t Int64;
  typedef uint64_t UInt64;
  typedef unsigned char uchar;
  typedef unsigned short ushort;
  typedef unsigned int uint;
#  if  !defined(_WIN64) && !defined (_AC64)
  static_assert(sizeof(void*) == 4, "ptr size in 32-bit windows build?");
  typedef int32_t LongPtr;
  typedef uint32_t ULongPtr;
  typedef int32_t IntPtr;
  typedef uint32_t UIntPtr;
#  else 
  static_assert(sizeof(void*) == 8, "ptr size in 64-bit build?");
  typedef int64_t LongPtr;
  typedef uint64_t ULongPtr;
  typedef int64_t IntPtr;
  typedef uint64_t UIntPtr;
#  endif
  typedef LongPtr IntDbId;
  typedef IntPtr GsMarker;
  typedef bool Boolean;
  static const bool kFalse = false;
  static const bool kTrue = true;
  using Time64 = int64_t;
};
#  undef NULL
#  define NULL	0
#  ifdef _ADESK_MAC_
#    ifdef nil
#      undef nil
#    endif
#    define nil	__DARWIN_NULL
#  endif
#  pragma  pack (pop)
#  if  defined(_MSC_VER)
#    define ADESK_NO_VTABLE	__declspec(novtable)
#    define ADESK_STDCALL	__stdcall
#    define ADESK_DEPRECATED	__declspec(deprecated)
#    define ADESK_DEPRECATED_MSG(MSG)	 __declspec(deprecated(MSG))
#    define ADESK_DATA_IMPORT	__declspec(dllimport)
#    define ADESK_PACK_BEGIN	__pragma(pack(push,1))
#    define ADESK_PACK_END	__pragma(pack(pop))
#    define ADESK_HIDDEN_SYMBOL
#  else 
#    define ADESK_NO_VTABLE
#    if  defined(__LP64__) || defined(__clang__)
#      define ADESK_STDCALL
#    else 
#      define ADESK_STDCALL
#    endif
#    define ADESK_DEPRECATED
#    define ADESK_DEPRECATED_MSG(MSG)	 __attribute__((__deprecated__))
#    define ADESK_DATA_IMPORT	extern
#    define __declspec(method)	 __declspec_##method
#    define _declspec(method)	 __declspec_##method
#    define __declspec_selectany
#    define __declspec_dllexport
#    define __declspec_dllimport
#    define __declspec_noinline
#    define __declspec_noreturn
#    define __declspec_deprecated
#    define __declspec_novtable
#    define __declspec_allocate(name)	 __attribute__ ((section("__DATA," name)))
#    define ADESK_PACK_BEGIN
#    define ADESK_PACK_END
#    define ADESK_HIDDEN_SYMBOL
#  endif
#  if  defined(_MSC_EXTENSIONS) || defined (__clang__)
#    define ADESK_OVERRIDE	override
#    if  defined(_MSC_VER) && (_MSC_VER <= 1600) //VS2010 and earlier
#      define ADESK_SEALED	sealed
#    else 
#      define ADESK_SEALED	final
#    endif
#  else 
#    define ADESK_OVERRIDE
#    define ADESK_SEALED
#  endif
#  define MIGRATION_ERRORS
#  if  defined(_MSC_VER) && defined (MIGRATION_ERRORS) || defined(__clang__)
#    define ADESK_SEALED_VIRTUAL	virtual
#    if  !defined(ADESK_SEALED)
#      define ADESK_SEALED	sealed
#    endif
#  else 
#    define ADESK_SEALED_VIRTUAL
#    if  !defined(ADESK_SEALED)
#      define ADESK_SEALED	sealed
#    endif
#  endif
#  if  defined(__INTEL_COMPILER) || defined (_MSC_VER)
#    define ADESK_FORCE_INLINE	__forceinline
#  else 
#    define ADESK_FORCE_INLINE	inline
#  endif
#  ifdef _ADESK_WINDOWS_
#    define VA_ARG_WCHAR(ap, t)	      va_arg(ap, wchar_t)
#  else 
#    define VA_ARG_WCHAR(ap, t)	      va_arg(ap, int)
#  endif
#  ifdef _ADESK_UNITTEST_
#    ifdef ADESK_SEALED
#      undef ADESK_SEALED
#    endif
#    define ADESK_SEALED
#  endif
#  ifdef _MSC_VER
#    define ADESK_UNREFED_PARAM(x)	 x
#  elif  defined(__clang__)
#    define ADESK_UNREFED_PARAM(x)	 (void)(x);
#  else 
#  endif
#  ifdef _MSC_VER
#    define ADESK_UNREACHABLE	__assume(false)
#  elif  defined(__clang__)
#    define ADESK_UNREACHABLE	__builtin_unreachable()
#  else 
#  endif
#endif
