//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiComboBox_h
#define _aduiComboBox_h
#pragma pack (push, 8)

#pragma once

#ifndef _ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
// CAdUiComboBox window
//
// This is the main Combo Box itself
#pragma warning(push)
#pragma warning(disable : 4275)

class CAdUiComboBoxDraw;

class ADUI_PORT CAdUiComboBox : public CComboBox {
    DECLARE_DYNAMIC(CAdUiComboBox)

public:
                CAdUiComboBox ();
virtual         ~CAdUiComboBox ();

// Fixed MFC Routines
public:
        // Use GetLBString() to circumvent GetLBText() errors.
        void    GetLBString (int nIndex, CString& rString);

// Misc.
protected:
        CPoint  m_lastMousePoint;
        CRect   m_tipRect;
        CString m_sToolTipText;
        CAdUiComboBoxDraw* m_pDraw;
        CAdUiTheme* m_pTheme;

public:
static  bool    IsVistaTheme();
static  bool    IsInEdit(UINT nItemState);

virtual BOOL    Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
virtual BOOL    OnChildNotify(UINT, WPARAM, LPARAM, LRESULT*);
virtual void    DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
virtual void    MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

virtual void    GetContentExtent (LPCTSTR text, int& width, int& height);
        void    GetTextExtent (LPCTSTR text, int& width, int& height);
        BOOL    IsOwnerDraw ();
        BOOL    IsStatic ();

        /// <summary>
        /// Sets the CAdUiComboBoxDraw instance which is used to do owner draw
        /// </summary>
        /// <param name="pDraw">
        /// The pointer to the CAdUiComboBoxDraw instance
        /// </param>
        void    SetDraw(CAdUiComboBoxDraw* pDraw);

        /// <summary>
        /// Gets if the combo box has a themed look
        /// </summary>
        /// <returns>
        /// True if the combo box has a themed look or false otherwise
        /// </returns>
        bool    IsThemed() const;

        /// <summary>
        /// Sets if the combo box has a themed look
        /// </summary>
        /// <param name="bValue">
        /// True if the combo box has a themed look or false otherwise
        /// </param>
        void    SetIsThemed(bool bValue);

        /// <summary>
        /// Gets the theme used by the combo box
        /// </summary>
        /// <returns>
        /// The pointer to the CAdUiTheme instance used by the combo box
        /// </returns>
        CAdUiTheme* GetTheme() const;

        /// <summary>
        /// Sets the theme to be used by the combo box
        /// </summary>
        /// <param name="pTheme">
        /// The pointer to the CAdUiTheme instance
        /// </param>
        void SetTheme(CAdUiTheme* pTheme);

// AdUi message handlers
protected:
        CWnd    *m_aduiParent;

virtual ADUI_REPLY DoAdUiMessage (
                    ADUI_NOTIFY notifyCode, UINT controlId, LPARAM lParam
                );
virtual void    OnDrawTip (CDC& dc);
virtual BOOL    OnDrawTipText (CAdUiDrawTipText& dtt);
virtual ADUI_REPLY OnGetTipSupport (CPoint& p);
virtual BOOL    OnGetTipRect (CRect& r);
virtual BOOL    OnGetTipText (CString& text);
virtual BOOL    OnHitTipRect (CPoint& p);
public:
        CWnd    *GetAdUiParent ();
        void    SetAdUiParent (CWnd *w);

        CString  GetToolTipText      (void) const;
        BOOL     SetToolTipText      (const CString& sText);

// Subclassed controls
protected:
        bool    m_bAutoDeleteEBox       : 1;    // set to automatically delete
        bool    m_bAutoDeleteLBox       : 1;    //  the edit or listbox controls
        bool    m_bSubclassedControls   : 1;    // set when all children are found
        CAdUiEdit *m_pComboEBox;                // the child edit control (if any)
        CAdUiListBox *m_pComboLBox;             // the list box

public:
        CAdUiEdit *GetEditBox ();
        void    SetEditBox (CAdUiEdit *control, BOOL autoDelete);
        CAdUiListBox *GetListBox ();
        void    SetListBox (CAdUiListBox *control, BOOL autoDelete);

// Validation style for subclassed EditBox
public:
        DWORD   GetStyleMask ();
        BOOL    IsStyleMaskSet (DWORD mask);
        void    SetStyleMask (DWORD mask);

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiComboBox)
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    //{{AFX_MSG(CAdUiComboBox)
	afx_msg void OnPaint();
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    //}}AFX_MSG
    afx_msg LRESULT  OnGetToolTipText  (WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()
};

inline void CAdUiComboBox::SetDraw(CAdUiComboBoxDraw* pDraw)
{ 
    m_pDraw = pDraw;
}

inline CAdUiTheme* CAdUiComboBox::GetTheme() const
{
    return m_pTheme;
}

#pragma warning(pop)

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

/////////////////////////////////////////////////////////////////////////////
