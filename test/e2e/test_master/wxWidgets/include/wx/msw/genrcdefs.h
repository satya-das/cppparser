/*
 * Name:        wx/msw/genrcdefs.h
 * Purpose:     Emit preprocessor symbols into rcdefs.h for resource compiler
 * Author:      Mike Wetherell
 * Copyright:   (c) 2005 Mike Wetherell
 * Licence:     wxWindows licence
 */
#define EMIT(line)	 line
#ifdef _MSC_FULL_VER
#  if  _MSC_FULL_VER < 140040130
#  endif
#else 
#endif
#if  defined _M_AMD64 || defined __x86_64__
#endif
#if  defined _M_ARM || defined __arm__
#endif
#if  defined _M_ARM64 || defined __aarch64__
#endif
#if  defined _M_IA64 || defined __ia64__
#endif
#if  defined _M_IX86 || defined _X86_
#endif
#ifdef _M_PPC
#endif
#ifdef _M_SH
#endif
