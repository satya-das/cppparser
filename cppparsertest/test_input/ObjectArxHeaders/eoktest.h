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

#pragma once

//   Macros for asserting and checking whether an Acad::ErrorStatus is eOk.
//
//   eOkVerify always checks for whether the expression is eOk and
//   returns TRUE if it is, FALSE if it isn't.
//
//   In addition, in debug builds, eOkVerify puts up a message box when
//   the expression does not equal eOk.
//
//   You might be thinking it would be nice to have an eOkAssert()
//   macro, which doesn't evaluate the expression in release builds,
//   similar to the ASSERT macro.  That would avoid the overhead of
//   computing the boolean result when it's not needed.  But this
//   seemed dangerous, in that it would be easy for someone to put
//   needed code inside eOkAssert, and that code would not get called
//   in release builds.  Also, the compiler already "optimizes out"
//   expressions whose results are not used.  So eOkVerify() doesn't
//   add overhead in release builds anyway.
#include "adesk.h"
#include "acadstrc.h"
#include "acestext.h"
#include "acutasrt.h"

#ifdef NDEBUG

#define eOkTest(x) ((x) == Acad::eOk)
#define eOkCheck(x) (x)
#define eOkVerify(x) ((x) == Acad::eOk)

#else   // else not NDEBUG

// For use by eoktest.h only!
inline Acad::ErrorStatus eOkCheck_imp(
    const ACHAR *condition,
    const ACHAR *fname,
    int         lineno,
    Acad::ErrorStatus es)
{
    if (es != Acad::eOk) {
        acutAssertMessage(condition, fname, lineno,
                          acadErrorStatusText(es));
    }
    return es;
}

/// <summary>
/// Evaluates to true if value is Acad::eOk, otherwise evaluates to false.
/// </summary>
#define eOkTest(x) ((x) == Acad::eOk)

/// <summary>
/// Asserts if value is not Acad::eOk.  Evaluates to the value.
/// </summary>
#define eOkCheck(x) eOkCheck_imp(ACRX_T(# x), ACRX_T(__FILE__), __LINE__, (x))

/// <summary>
/// Asserts if value is not Acad::eOk.  Evaluates to true if value is Acad::eOk
/// otherwise evalutes to false.
/// </summary>
#define eOkVerify(x) (eOkCheck(x) == Acad::eOk)

#endif // NDEBUG
