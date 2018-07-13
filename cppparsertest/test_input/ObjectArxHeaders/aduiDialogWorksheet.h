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
// *****************************
// *** FOR INTERNAL USE ONLY ***
// *****************************
//
#ifndef ADUIDLGWORKSHEET_H
#define ADUIDLGWORKSHEET_H

// CAdUiDialogWorksheet.h : header file
//

// forward reference
class CAdUiWorksheetDraw;


///////////////////////////////////////////////////////////////////////////////
//
//  Introduction:
//
//  Basics:
//
//
//  Include File:
//  AdUiDialogWorksheet.h
//
///////////////////////////////////////////////////////////////////////////////

class ADUI_PORT CAdUiDialogWorksheet : public CAdUiDialog
{
    friend class CAdUiWorksheetThemeModReactor;  // INTERNAL USE ONLY

    DECLARE_DYNAMIC(CAdUiDialogWorksheet);
    
// Construction
public:
    virtual ~CAdUiDialogWorksheet();

    /// <summary>
    /// Gets the theme being used
    /// </summary>
    /// <returns>
    /// The pointer to the CAdUiTheme instance being used
    /// </returns>
    CAdUiTheme * GetTheme() const;

    /// <summary>
    /// Sets the theme to be used
    /// </summary>
    /// <param name="pTheme">
    /// The pointer to the CAdUiTheme instance
    /// </param>
    /// <returns>
    /// The current theme being used
    /// </returns>
    CAdUiTheme * SetTheme(CAdUiTheme *pTheme);

    static CAdUiWorksheetDraw * SetDefaultDraw(CAdUiWorksheetDraw * pDraw);
    void SetDraw(const CAdUiWorksheetDraw * pDraw);

    /// <summary>
    /// Virtual method that receives the theme modification event.
    /// </summary>
    /// <param name="element">
    /// A index of the theme element that was modified.
    /// </param>
    /// <remarks>
    /// This method is also called when the theme uses the active theme colors
    /// and the active theme is changed.  In that case, element = kUnknownElements
    /// </remarks>        
    virtual void ThemeModified(AdUiThemeElement element);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAdUiDialogWorksheet)
    public:
    virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
                          int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU nIDorHMenu, 
                          LPVOID lpParam = NULL);
    virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
                          const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
    virtual BOOL DestroyWindow();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    virtual BOOL OnInitDialog();
    protected:
    virtual void PostNcDestroy();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

protected:
    HICON m_hIcon;

    CAdUiDialogWorksheet(UINT ID, CWnd* pParent = NULL, HINSTANCE hResInst = NULL);   // standard constructor
    CAdUiDialogWorksheet(UINT ID, const CAdUiWorksheetDraw & draw, CWnd* pParent = NULL, HINSTANCE hResInst = NULL);

    // Generated message map functions
    //{{AFX_MSG(CAdUiDialogWorksheet)
    afx_msg void OnDestroy();
    afx_msg void OnClose();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC *pDC);
    afx_msg void OnIconEraseBkgnd(CDC* pDC);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
    afx_msg void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
    afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
    afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
    afx_msg void OnMouseMove(UINT nHitTest,CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    afx_msg BOOL OnNcActivate(BOOL bActive);
    afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
    afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnNcDestroy();
#if _MSC_VER<1400
    afx_msg UINT OnNcHitTest(CPoint point);
#else
    afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
    afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
    afx_msg void OnNcMButtonDblClk(UINT nHitTest, CPoint point);
    afx_msg void OnNcMButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnNcMButtonUp(UINT nHitTest, CPoint point);
    afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
    afx_msg void OnNcPaint();
    afx_msg void OnNcRButtonDblClk(UINT nHitTest, CPoint point);
    afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    
// Implementation
    static CAdUiWorksheetDraw * s_pDefaultDraw;             // the current default draw object
    static CAdUiWorksheetDraw * s_PlatformDefaultDraw;      // the default draw object if no one setup a default draw yet
    CAdUiWorksheetDraw * m_pDraw;                           // the draw object for this dialog

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADUIDLGWORKSHEET_H__2D0C1B1B_5604_4C1B_9BD9_CC5C88A79CB6__INCLUDED_)
