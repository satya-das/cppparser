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
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

#define     ASITRYSET   IncreaseGlobalAccount(0); try
#define     ASICATCHALL catch (int ASITRYCODE)
#define     ASITRYDEL   DecreaseGlobalAccount(0);
#define     ASITHROW(x) if( CheckGlobalAccount(0) ) throw((int)(x))
#pragma pack (push, 8)

DLLScope int IncreaseGlobalAccount(int ind);
DLLScope int DecreaseGlobalAccount(int ind);
DLLScope int CheckGlobalAccount(int ind);
#pragma pack (pop)
