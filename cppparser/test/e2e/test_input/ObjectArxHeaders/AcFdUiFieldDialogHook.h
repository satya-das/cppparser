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
// Name:            AcFdUiFieldDialogHook.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AcFdUi.h"
#include "DbField.h"
#include <afxtempl.h>


class AcTcUiSystemInternals;
class CAcFdUiFieldDialog;
class CAcFdUiFieldOptionDialog;
class CAcFdUiImpFieldDialog;
class CAcFdUiFieldDialogHook;


typedef CTypedPtrArray<CPtrArray, CAcFdUiFieldDialogHook*>  AcFdUiFieldDialogHookArray;


class ACFDUI_PORT CAcFdUiFieldDialogHook : public CObject
{
public:
    CAcFdUiFieldDialogHook(void);
    ~CAcFdUiFieldDialogHook(void);

    // For internal use only
    virtual BOOL    CreateInstance          (CAcFdUiFieldDialogHook*& pHook);

    virtual int     GetEvaluatorIds         (CStringArray& evalIds);
    virtual BOOL    BeginFieldDialog        (CAcFdUiFieldDialog* pFieldDlg, 
                                             AcDbDatabase* pDb, 
                                             int nContext);
    virtual BOOL    EndFieldDialog          (int nRet);
    virtual BOOL    SetFieldToEdit          (AcDbField* pField);
    AcDbDatabase *  GetDatabase             (void) const;
    virtual BOOL    GetCategoryNames        (UINT uMinUnusedCatId,
                                             CStringArray& catNames, 
                                             CUIntArray& catIds);
    virtual BOOL    GetFieldNames           (UINT uCatId, 
                                             UINT uMinUnusedFieldId,
                                             CStringArray& fieldNames, 
                                             CUIntArray& fieldIds,
                                             BOOL& bSort);
    virtual BOOL    GetOptionDialog         (UINT uFieldId, 
                                             CAcFdUiFieldOptionDialog*& pOptionDlg);
    virtual CString GetPreview              (LPCTSTR pszFormatType, 
                                             LPCTSTR pszFormat);
    virtual BOOL    UpdateFieldCode         (void);
    virtual BOOL    OnFieldSelected         (UINT uFieldId);
    virtual BOOL    CreateField             (UINT uFieldId, 
                                             AcDbField*& pField);

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;
};

