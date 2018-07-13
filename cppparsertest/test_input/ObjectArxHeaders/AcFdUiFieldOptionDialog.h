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
// Name:            AcFdUiFieldOptionDialog.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdUi.h"
#include "AcFdUi.h"

class AcTcUiSystemInternals;
class CAcFdUiFieldDialog;
class CAcFdUiFieldDialogHook;
class CAcFdUiImpFieldDialog;
class AcDbField;


class ACFDUI_PORT CAcFdUiFieldOptionDialog : public CAdUiDialog
{
    friend CAcFdUiFieldDialog;
    friend CAcFdUiImpFieldDialog;

    DECLARE_DYNAMIC(CAcFdUiFieldOptionDialog)

public:
    CAcFdUiFieldOptionDialog(CAcFdUiFieldDialogHook* pDialogHook, CAcFdUiFieldDialog* pFieldDlg, 
        UINT nIDTemplate, HINSTANCE hDialogResource = NULL);
    virtual ~CAcFdUiFieldOptionDialog();

    CAcFdUiFieldDialogHook* GetFieldDialogHook(void) const;
    CAcFdUiFieldDialog* GetFieldDialog      (void) const;
    virtual BOOL    Create                  (CWnd* pParent);

public:
    // Base class overrides
    virtual BOOL    Create                  (LPCTSTR lpszTemplateName, 
                                             CWnd* pParent = NULL);
    virtual BOOL    Create                  (UINT nIDTemplate, 
                                             CWnd* pParent = NULL);

protected:
    virtual BOOL    OnSetActive             (void);
    virtual BOOL    OnKillActive            (void);
    virtual BOOL    OnFieldSelected         (UINT uNewFieldId);

protected:
    // Base class overrides
    virtual void    OnOK                    (void);
    virtual void    OnCancel                (void);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    afx_msg LRESULT OnFormatChanged         (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnBeginFormatExDialog   (WPARAM wParam, 
                                             LPARAM lParam);
    afx_msg LRESULT OnEndFormatExDialog     (WPARAM wParam, 
                                             LPARAM lParam);
    DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
