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
//  acutmem.h - General memory allocation functions.
//
//  DESCRIPTION:
//
//  The following functions are used to handle string values and memory
//  returned to or from (or passed into) the ObjectARX API.  Function
//  acutNewString() makes a copy of a string and returns an error status.
//  Function acutUpdString() performs the same job as acutNewString(),
//  except that it first frees any string already pointed to by the
//  output argument.  acutDelString() frees up a string allocated by
//  acutNewString() or acutUpdString() if the input pointer is non
//  NULL and then sets the pointer to NULL.
//

#ifndef _ACUTMEM_H
#define _ACUTMEM_H

#include "acadstrc.h"   // Acad::ErrorStatus
#include "adesk.h"      // Adesk::Int32
#include "AdAChar.h"    // ACHAR
#include "AcDbCore2dDefs.h"     // ACDBCORE2D_PORT
#pragma pack (push, 8)

Acad::ErrorStatus acutNewBuffer(void *&pOutput, size_t size);

/// <summary>
/// Allocates a character buffer for containing a raw string
/// </summary>
/// <param name="pOutput"> Returns a pointer to the buffer. Undefined on errors</param>
/// <param name="nNumChars"> The size (in ACHARs) of the buffer to be allocated.</param>
/// <returns> Returns Acad::eOk if the buffer is allocated successfully, otherwise an error code.</returns>
/// <remarks> Caller should include space for null terminator in nNumChars</remarks>
/// <remarks> Buffer contents are uninitialized</remarks>
/// <remarks> Fails if requested nNumChars is <= 0 or > 512M</remarks>
Acad::ErrorStatus acutNewString(ACHAR *&pOutput, Adesk::Int32 nNumChars);

Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);
Acad::ErrorStatus acutUpdString(const ACHAR* pInput, ACHAR*& pOutput);
void acutDelBuffer(void *& pBuffer);

inline Acad::ErrorStatus acutNewBuffer(char *&pOutput, size_t size)
{
    return ::acutNewBuffer((void * &)pOutput, size);
}

inline void acutDelBuffer(char *& pString)
{
    ::acutDelBuffer((void * &)pString);
}

inline void acutDelString(char *& pString)
{
    ::acutDelBuffer((void * &)pString);
}

inline void acutDelString(wchar_t *& pString)
{
    ::acutDelBuffer((void * &)pString);
}

#pragma pack (pop)

/// <summary>
/// Copies the input string into the output buffer.
/// </summary>
/// <param name="pInput">Pointer to the source string</param>
/// <param name="pOutput">Pointer to the destination buffer</param>
/// <param name="nOutputSize">Number of characters that can fit in the destination buffer</param>
/// <returns> Returns Acad::eOk if the copy succeeds.
///           Returns Acad::eInvalidParameter if any input args are null or zero
///           Returns Acad::eBufferTooSmall if the string doesn't fit in the buffer
//
/// <remarks> nOutputSize must be >= wcslen(pInput) + 1</remarks>
//
ACDBCORE2D_PORT Acad::ErrorStatus
acutCopyStringToBuffer(const ACHAR * pInput, ACHAR * pOutput, size_t nOutputSize);

#endif // _ACUTMEM_H
