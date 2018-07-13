//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiCoupledGroupCtrl_h
#define _aduiCoupledGroupCtrl_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
/// CAdUiCoupledGroupCtrl class dervies from CWnd and provides functionality
/// to host two controls separated by the splitterbar and takes care of 
/// resizing the hosted controls when they are resized using the splitter bar
///

#pragma warning(push)
#pragma warning(disable : 4275)

class CAdUiGroupCtrl;
class CAdUiTheme;

#define ADUI_DEFAULT_TREE_TO_DETAILS_RATIO  0.4

/// <summary>
/// CAdUiCoupledGroupCtrl class dervies from CWnd and provides functionality
/// to host two controls separated by the splitterbar and takes care of 
/// resizing the hosted controls when they are resized using the splitter bar.
/// </summary>
///
class ADUI_PORT CAdUiCoupledGroupCtrl : public CWnd {

    DECLARE_DYNAMIC(CAdUiCoupledGroupCtrl);

// Construction
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    CAdUiCoupledGroupCtrl();
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~CAdUiCoupledGroupCtrl();

public:
// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAdUiCoupledGroupCtrl)
    //}}AFX_VIRTUAL

// Implementation
public:
    /// <summary>
    /// Given two CAdUiGroupCtrl pointers, hosts them in the coupled group with
    /// a splitter bar in between.
    /// </summary>
    ///
    /// <param name="pAdUiTopWnd">
    /// Input pointer to the CAdUiGroupCtrl which will be hosted in the top 
    /// window of the coupled group.
    /// </param>
    /// <param name="pAdUiBottomWnd">
    /// Input pointer to the CAdUiGroupCtrl which will be hosted in the bottom
    /// window of the coupled group.
    /// </param>
    ///
    virtual void AddCouple(CAdUiGroupCtrl * pAdUiTopWnd, 
                           CAdUiGroupCtrl * pAdUiBottomWnd);

    /// <summary>
    /// Given two CWnd pointers, hosts them in the coupled group with
    /// a splitter bar in between.
    /// </summary>
    ///
    /// <param name="pWndTop">
    /// Input pointer to the CWnd which will be hosted in the top window of the
    /// coupled group.
    /// </param>
    /// <param name="pWndBottom">
    /// Input pointer to the CWnd which will be hosted in the bottom window 
    /// of the coupled group.
    /// </param>
    ///
    virtual void AddCouple(CWnd* pWndTop, CWnd* pWndBottom);

    /// <summary>
    /// Given a CAdUiGroupCtrl and CWnd pointers, hosts them in the coupled 
    /// group with a splitter bar in between.
    /// </summary>
    ///
    /// <param name="pAdUiTopWnd">
    /// Input pointer to the CAdUiGroupCtrl which will be hosted in the top 
    /// window of the coupled group.
    /// </param>
    /// <param name="pWndBottom">
    /// Input pointer to the CWnd which will be hosted in the bottom window 
    /// of the coupled group.
    /// </param>
    ///
    virtual void AddCouple(CAdUiGroupCtrl* pAdUiTopWnd, CWnd* pWndBottom);

    /// <summary>
    /// Given a CWnd and CAdUiGroupCtrl pointers, hosts them in the coupled 
    /// group with a splitter bar in between.
    /// </summary>
    ///
    /// <param name="pWndTop">
    /// Input pointer to the CAdUiGroupCtrl which will be hosted in the top 
    /// window of the coupled group.
    /// </param>
    /// <param name="pAdUiBottomWnd">
    /// Input pointer to the CAdUiGroupCtrl which will be hosted in the bottom
    /// window of the coupled group.
    /// </param>
    ///
    virtual void AddCouple(CWnd* pWndTop, CAdUiGroupCtrl* pAdUiBottomWnd);

    /// <summary>
    /// Input pointer to the CWnd that needs to be minimized or maximized.
    /// </summary>
    ///
    /// <param name="pWnd">
    /// Input pointer to the CAdUiGroupCtrl which will be hosted in the top 
    /// window of the coupled group.
    /// </param>
    /// <param name="bMinimized">
    /// true to minimize or false to maximize the window .
    /// </param>
    ///
    virtual void MinMaxOneChild(CWnd* pWnd, bool bMinimized);

    // properties

    /// <summary>
    /// Returns the current ratio between the top window and whole window.
    /// </summary>
    /// <returns>
    /// Returns a double value. The ratio between the top window and the 
    /// whole window of the coupled group. 
    /// </returns>
    ///
    double GetTopToWholeRatio() const { return m_topToWholeRatio; }
    /// <summary>
    /// Sets the top to whole coupled group control ratio, which controls 
    /// the top and bottom window control sizes.
    /// </summary>
    ///
    /// <param name="topToWholeRatio">
    /// Input double value that controls top and bottom window sizes in the
    /// coupled group control.
    /// </param>
    ///
    void SetTopToWholeRatio(double topToWholeRatio);

    /// <summary>
    /// Controls the display of the splitter control.
    /// </summary>
    ///
    /// <param name="bSplitterEnabled">
    /// Input parameter to hide or show the splitter control.
    /// </param>
    /// <remarks>
    /// Splitter control is displayed when the bSplitterEnabled is set
    /// to true and hidden when set to false. The default value is set
    /// to true.
    /// </remarks>
    ///
    void SetSplitterEnabled(bool bSplitterEnabled) {
        m_bSplitterEnabled = bSplitterEnabled;
    }

    /// <summary>
    /// Returns true or false based on whether the splitter is enabled
    /// or not.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if splitter is enabled and false if it is not enabled.
    /// </returns>
    ///
    bool GetSplitterEnabled() {
        return m_bSplitterEnabled;
    }
    /// <summary>
    /// Gets the theme used by the coupled group control
    /// </summary>
    ///
    /// <returns>
    /// Pointer to the theme used by the coupled group control
    /// </returns>
    ///
    CAdUiTheme* GetTheme() const;

    /// <summary>
    /// Sets the theme for the coupled group control to the current palette
    /// background color and draws the splitter control with the current 
    /// border color.
    /// </summary>
    ///
    /// <param name="pTheme">
    /// Input parameter to a CAdUiTheme pointer, whose theme colors will be 
    /// used to draw the coupled group control.
    /// </param>
    ///
    void SetTheme(CAdUiTheme* pTheme);

    // Generated message map functions
protected:
    //{{AFX_MSG(CAdUiCoupledGroupCtrl)
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnPaint();
    afx_msg void OnMouseMove( UINT nFlags, CPoint );
    afx_msg void OnLButtonDown( UINT nFlags, CPoint );
    afx_msg void OnLButtonUp( UINT nFlags, CPoint );
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
    void ResizeChildren( int cx, int cy );
    bool ValidateCtrls();
    bool IsAnyCtrlMinimizedOrIconic();

// Attributes
protected:
    COLORREF m_crNCBackground;
    COLORREF m_crSplitter;
    CBrush   m_bkBrush;

protected:
    CAdUiGroupCtrl* m_pAdUiTopWnd;
    CAdUiGroupCtrl* m_pAdUiBottomWnd;
    CWnd*           m_pTopWnd;
    CWnd*           m_pBottomWnd;
    double          m_topToWholeRatio;
    bool            m_bDragging;
    bool            m_bSplitterEnabled;
    CPoint          m_ptLast;
    CRect           m_rtSpace;
    CAdUiTheme*     m_pTheme;
};

#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
