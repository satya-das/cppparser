//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
// This computer source code and related instructions and comments
// are the unpublished confidential and proprietary information of
// Autodesk, Inc. and are protected under applicable copyright and
// trade secret law.  They may not be disclosed to, copied or used
// by any third party without the prior written consent of Autodesk, Inc.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _IDVER_H
#  define _IDVER_H
#  include "id.h"
#  ifndef AC_BLDENV
#    define ACADV_BLDMAJOR	0   /*BuildMajor*/
#    define ACADV_BLDMINOR	0   /*BuildMinor*/
#    define ACADV_BLDBRANCH	0   /*BuildBranch*/
#    define ACADV_BLDSTREAM	O   /*BuildStream*/
#  else 
#    include "_idver.h"
#  endif
#  define VALUE2STR(x)	 #x
#  define ID2STR(a)	 ID2STR__1(a)
#  define ID2STR__1(a)	 VALUE2STR(a)
#  define ACADV_RCFILEVER1	ACADV_RELMAJOR
#  define ACADV_RCFILEVER2	ACADV_RELMINOR
#  define ACADV_RCFILEVER3	ACADV_BLDMAJOR
#  define ACADV_RCFILEVER4	ACADV_BLDMINOR
#  define ACADV_RCFILEVER5	ACADV_BLDBRANCH
#  define ACADV_RCFILEVER1_CORRECTION	(6 + ACADV_RCFILEVER1)
#  define ACADV_RCFILEVERSTR	ID2STR(ACADV_RCFILEVER1) "." \
                ID2STR(ACADV_RCFILEVER2) "." \
                ID2STR(ACADV_RCFILEVER3) "." \
                ID2STR(ACADV_RCFILEVER5) "." \
                ID2STR(ACADV_RCFILEVER4)
#  define ACADV_PRODVERSION	"R" ACADV_RCFILEVERSTR
#  if  defined(_MSC_VER) || defined(UNICODE)
#    define ACADV_VERNUM	ACRX_T(ID2STR(ACADV_BLDSTREAM)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDMAJOR)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDBRANCH)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_BLDMINOR))
#  else 
#    define ACADV_VERNUM	ID2STR(ACADV_BLDSTREAM) "." \
                     ID2STR(ACADV_BLDMAJOR) "." \
                     ID2STR(ACADV_BLDBRANCH) "." \
                     ID2STR(ACADV_BLDMINOR)
#  endif
#  if  defined(_MSC_VER) || defined(UNICODE)
#    define ACADV_VERNAME	ACRX_T(ID2STR(ACADV_RELMAJOR)) ACRX_T(".") \
                      ACRX_T(ID2STR(ACADV_RELMINOR))
#  else 
#    define ACADV_VERNAME	ID2STR(ACADV_RELMAJOR) "." \
                      ID2STR(ACADV_RELMINOR)
#  endif
#  if  defined(PRODUCTION)
#    define ACADV_VERFULL	ACADV_VERNAME
#  else 
#    define ACADV_VERFULL	ACADV_VERNUM
#  endif
#  define ACADV_BLDVERSTR	ACADV_VERNUM
#  define ACAD_COPYRIGHT	"Copyright 2018 Autodesk, Inc.  All rights reserved."
#  define ACAD_COPYRIGHT_YEAR	"2018"
#  define ACAD_TLBVERSION_MAJOR	1
#  define ACAD_TLBVERSION_MINOR	0
#  define ACAD_TLBVERSION	ACAD_TLBVERSION_MAJOR.ACAD_TLBVERSION_MINOR
#  ifdef _MSC_VER
#    define ACAD_TLBVERSIONSTR	ACRX_T(ID2STR(ACAD_TLBVERSION_MAJOR)) ACRX_T(".") \
                                ACRX_T(ID2STR(ACAD_TLBVERSION_MINOR))
#  else 
#    define ACAD_TLBVERSIONSTR	ID2STR(ACAD_TLBVERSION_MAJOR) "." \
                                ID2STR(ACAD_TLBVERSION_MINOR)
#  endif
#  define ACDB_TLBVERSION_MAJOR	1
#  define ACDB_TLBVERSION_MINOR	0
#  define ACDB_TLBVERSION	ACDB_TLBVERSION_MAJOR.ACDB_TLBVERSION_MINOR
#  ifdef _MSC_VER
#    define ACDB_TLBVERSIONSTR	ACRX_T(ID2STR(ACDB_TLBVERSION_MAJOR)) ACRX_T(".") \
                                ACRX_T(ID2STR(ACDB_TLBVERSION_MINOR))
#  else 
#    define ACDB_TLBVERSIONSTR	ID2STR(ACDB_TLBVERSION_MAJOR) "." \
                                ID2STR(ACDB_TLBVERSION_MINOR)
#  endif
#endif
