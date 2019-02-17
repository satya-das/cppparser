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
// Name:            AcFdUi.h
//
// Description:     Header for global methods exported from AcFdUi module
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef  ACFD_API
#  define   ACFDUI_PORT  __declspec(dllexport)
#else
#  define   ACFDUI_PORT  
#endif


class CAcFdUiFieldManager;
class AcDbField;
class AcDbDatabase;


// Category ids
#define ACFDUI_CATEGORY_ID_ALL              -1


// Verticals and other applications can use category ids starting from 
// this
#define ACFDUI_CATID_USER_FIRST             1000


// Verticals and other applications can use field ids starting from this
#define ACFDUI_FIELDID_USER_FIRST           50000


// Exported public functions
//
ACFDUI_PORT CAcFdUiFieldManager* AcFdUiGetFieldManager(void);
ACFDUI_PORT int AcFdUiInvokeFieldDialog(AcDbField*& pNewField, 
                                        BOOL bEdit,
                                        AcDbDatabase* pDb,
                                        CWnd* pParent = NULL);
