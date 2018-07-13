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
// Name:            AcFdUiFieldDialog.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "adui.h"
#include "AcFdUi.h"
#include "acui.h"

class AcFdUiSystemInternals;
class CAcFdUiFieldOptionDialog;
class CAcFdUiImpFieldDialog;


// Field dialog context flags
#define ACFDUI_FD_CREATE_FIELD         1
#define ACFDUI_FD_EDIT_FIELD           2


class ACFDUI_PORT CAcFdUiFieldDialog : public CAcUiDialog
{
    friend CAcFdUiImpFieldDialog;

    DECLARE_DYNAMIC(CAcFdUiFieldDialog)

public:
    CAcFdUiFieldDialog(CWnd* pParent = NULL);
    virtual ~CAcFdUiFieldDialog();

    INT_PTR         DoModal                 (AcDbField*& pField, 
                                             BOOL bEdit, 
                                             AcDbDatabase* pDb);
    AcDbField   *   GetFieldToEdit          (void) const;
    BOOL            SetFieldCodeReadOnly    (BOOL bReadOnly = TRUE);
    CString         GetFieldCode            (void) const;
    BOOL            SetFieldCode            (LPCTSTR pszExpr);
    BOOL            IsFieldCodeDirty        (void);
    CEdit       *   GetFieldCodeEditCtrl    (void);
    BOOL            GetCurrentField         (UINT* pFieldId, 
                                             UINT* pCatId) const;
    BOOL            SelectField             (UINT uFieldId, 
                                             UINT uCatId);
    CAcFdUiFieldOptionDialog* GetOptionDialog(void) const;

public:
    // Base class overrides
    void            BeginEditorCommand      (void);
    void            CompleteEditorCommand   (BOOL restoreDialogs = TRUE);
    void            CancelEditorCommand     (void);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

protected:
    virtual BOOL    OnInitDialog            (void);
    virtual void    OnOK                    (void);
    virtual void    OnCancel                (void);

    afx_msg void    OnCbnSelChangeCategoryList(void);
    afx_msg void    OnLbnSelChangeFieldNameList(void);
    afx_msg void    OnEnChangeFieldCode     (void);
    afx_msg void    OnDialogHelp            (void);
    afx_msg LRESULT OnFormatChanged         (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnBeginFormatExDialog   (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnEndFormatExDialog     (WPARAM wParam, 
                                             LPARAM lParam);

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
