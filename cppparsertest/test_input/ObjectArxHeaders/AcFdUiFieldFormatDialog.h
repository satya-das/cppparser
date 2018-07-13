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
// Name:            AcFdUiFieldFormatDialog.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcFdUiFormatDialog.h"


class ACFDUI_PORT CAcFdUiFieldFormatDialog : public CAcFdUiFormatDialog
{
	DECLARE_DYNAMIC(CAcFdUiFieldFormatDialog)

    CAcFdUiFieldFormatDialog(CWnd* pParent, BOOL bNew);
};
