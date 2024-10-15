//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

class CAcUiNavDialog;

typedef void (*FileDiaCallbackFuncPtr)(CAcUiNavDialog*);

ACAD_PORT void acedRegisterNavDialogCallbackFunction(FileDiaCallbackFuncPtr funcPtr);
ACAD_PORT void acedUnregisterNavDialogCallbackFunction(FileDiaCallbackFuncPtr funcPtr);

