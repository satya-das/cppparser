//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiDock_h
#define _aduiDock_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxpriv.h>                    // For CDockBar and CMiniDockFrameWnd
#include "AdAChar.h"
#pragma pack (push, 8)
class CPaletteSetTooltip;
class CAdUiDockFrame;
class CAdUiDockControlBar;

//////////////////////////////////////////////////////////////////////////////

#define ADUI_DOCK_POSITION_TOOL_KEY     ADUI_XML_DOCK_TOOL_INFO
#define ADUI_DOCK_STARTUP_TOOL_KEY      ADUI_XML_DOCK_STARTUP_INFO
#define ADUI_XML_ROOT                   ACRX_T("AdUiTools")
#define ADUI_XML_DOCK_TOOL_INFO         ACRX_T("ToolsInfo")
#define ADUI_XML_DOCK_TOOL              ACRX_T("Tool")
#define ADUI_XML_DOCK_TOOL_CLSID        ACRX_T("CLSID")
#define ADUI_XML_DOCK_STARTUP_INFO      ACRX_T("StartupInfo")
#define ADUI_XML_DOCK_STARTUP_TOOL_NAME ACRX_T("ToolName")
#define ADUI_XML_DOCK_STARTUP_CMD_NAME  ACRX_T("Command")

#define ID_ADUI_ALLOWDOCK           0x1001
#define ID_ADUI_HIDEBAR             0x1002

#define ADUI_DOCK_CS_DESTROY_ON_CLOSE  0x01    // closing the floating window closes the control bar
#define ADUI_DOCK_CS_STDMOUSECLICKS    0x02    // standard mouse handling for the menu

#define ADUI_DOCK_NF_SIZECHANGED       0x01
#define ADUI_DOCK_NF_STATECHANGED      0x02
#define ADUI_DOCK_NF_FRAMECHANGED      0x02

#define WM_ACAD_DOCKBAR_ROLLED_UP  (WM_USER+37)  // From "winacad.h"
#define WM_ACAD_DOCKBAR_ROLLED_OUT (WM_USER+38)  // From "winacad.h"

//////////////////////////////////////////////////////////////////////////////

#pragma warning(push)
#ifndef _ADESK_MAC_

#pragma warning(disable : 4275)

/////////////////////////////////////////////////////////////////////////////
// CAdUiDockControlBarThemeModReactor class

class CAdUiDockControlBarThemeModReactor : public CAdUiThemeModifiedReactor  // INTERNAL USE ONLY
{
public:
    CAdUiDockControlBarThemeModReactor(CAdUiDockControlBar* pDockControlBar);
    virtual void ThemeModified(const CAdUiTheme * pTheme, AdUiThemeElement element);
    void SetDockControlBar(CAdUiDockControlBar* pDockControlBar);

private:
    CAdUiDockControlBar * m_pDockControlBar;
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiDockControlBar class

class ADUI_PORT CAdUiDockControlBar : public CControlBar
{
    friend class CAdUiDockFrame;
    friend class CAdUiPaletteSetDockFrame;
    friend class CAdUiDockDragContext;
    friend class CAdUiDockBar;
    friend class CAdUiImpPaletteSet;
    friend class CAdUiDockBarMutator;
    friend class CAdUiDockControlBarThemeModReactor; // INTERNAL USE ONLY

// Attributes
private:
    static CObArray * m_paBars;                     // array of dynamically allocated bars
    CSize             m_FloatSize;                  // size when docked
    CSize             m_HorzDockSize;               // size when docked horizontal
    CSize             m_VertDockSize;               // size when docked vertical
    CPoint            m_FloatingPosition;           // floating position
    bool              m_bAllowDockingMenuItemState; // allow docking menu item state
    int               m_Style;                      // style flags
    CSize             m_PrevSize;
    BOOL              m_bPrevFloating;
    CAdUiBitmapButton m_closeBtn;
    CAdUiBitmapButton m_pinBtn;
    CLSID             m_ID;
    bool              m_bShowCloseButton;           // Show and draw close button on docked bar

    static int        m_nLastBarID;
    static bool       m_bToolsRestartMode;      // Boolean variable to signal start/end of
                                                // restarting of tools (usually set/cleared 
                                                // by the the application during startup.

    // variables which reflect persisted dock/float rect for the controlbar 
    // across application sessions
    CRect             m_PersistedDockRect;      
    CRect             m_PersistedFloatRect;

private:
    void        SetDockFlag (DWORD dwStyle);
    void        Resized (int cx, int cy, BOOL bFloating, int flags);
    LRESULT     AddMenuItems (WPARAM wParam, LPARAM lParam);
    static void RemoveBars ();
    void        OnUpdateCmdUI (CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
    void        PaintBar (CDC *pDC);
    void        Draw3DRect (CDC *pDC, LPRECT lpRect, CPen *pPenGray);
    LRESULT     WindowProc (UINT nMsg, WPARAM wParam, LPARAM lParam);
    void        LoadDefaultLocation(UINT nOrientation, RECT *pSizeFloating);

public:
    CAdUiDockControlBar (int nStyle = ADUI_DOCK_CS_STDMOUSECLICKS);

    BOOL Create (CWnd * pParent, LPCTSTR lpszTitle, UINT nID,
                 DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
                 const RECT & rect = CFrameWnd::rectDefault);
    BOOL Create (LPCTSTR lpszClassName, LPCTSTR lpszWindowName,
                 DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
                 UINT nID, CCreateContext* pContext = NULL);
    
    void EnableDocking (DWORD dwDockStyle);
    void TileInRow ();
    BOOL IsFloating ();

    void DockControlBar (UINT nOrientation, RECT *pRect);
    void RestoreControlBar (UINT nPreferredOrientation = AFX_IDW_DOCKBAR_LEFT,
                            CRect *pSizeFloating = NULL);

    void InitFloatingPosition (CRect *pSizeFloating);
    void GetFloatingRect (CRect *pFloatingPos);

    // access methods which returns the cached dock/float
    // rect which would have persisted in the fixed profile
    // across autocad sessions. 
    void GetPersistedDockingRect(CRect *pDockRect);
    void GetPersistedFloatingRect(CRect *pFloatRect);

    // Get/Set methods to signal begining and end of
    // restarting of tools. Set and cleared by the 
    // application to position controlbars inside
    // one of the four dockbars during the application
    // startup.
    static void SetToolsRestartMode ( bool bMode );
    static bool GetToolsRestartMode (  );

    void SetAllowDockingMenuItemState(bool bState) { m_bAllowDockingMenuItemState = bState; }
    bool AllowDockingMenuItemState() { return m_bAllowDockingMenuItemState; }

    void SetToolID (CLSID* pCLSID);
    CLSID* GetToolID () { return &m_ID; }
    DWORD GetDockStyle () { return m_dwDockStyle; }

    // Called in response to the application's query to take the focus back.
    // Default implementation returns false, keeping the focus in the tool window.
    virtual bool CanFrameworkTakeFocus () { return false; }

    // Loads the data from xml file 
    virtual BOOL Load(IUnknown* pUnk);
    // Saves the data to xml file
    virtual BOOL Save(IUnknown* pUnk);

    virtual CSize CalcFixedLayout (BOOL bStretch, BOOL bHorz);

    bool Anchored();
    bool Anchored(bool bHiddenReturnsLastState);

    static bool ShowPalettes();
    static bool HidePalettes();

    bool AdjustVertDockedBarHeight(int nHeight);

    /// <summary>
    /// Gets the theme being used
    /// </summary>
    /// <returns>
    /// The pointer to the CAdUiTheme instance being used
    /// </returns>
    CAdUiTheme* GetTheme();

    /// <summary>
    /// Sets the theme to be used
    /// </summary>
    /// <param name="pTheme">
    /// The pointer to the CAdUiTheme instance
    /// </param>
    /// <returns>
    /// The current theme being used
    /// </returns>
    CAdUiTheme* SetTheme(CAdUiTheme* pTheme);

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

    // Returns the title bar width/height
    LONG GetTitleBarSize();

    // Get/Sets horizontal/vertical dock size
    const CSize& GetHorzDockSize() { return m_HorzDockSize; }            // INTERNAL USE ONLY
    const CSize& GetVertDockSize() { return m_VertDockSize; }            // INTERNAL USE ONLY
    void SetHorzDockSize(const CSize& size) { m_HorzDockSize = size; }   // INTERNAL USE ONLY
    void SetVertDockSize(const CSize& size) { m_VertDockSize = size; }   // INTERNAL USE ONLY

#ifdef _DEBUG
    void AssertValid() const;
#endif

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAdUiDockControlBar)
protected:
    virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam);
    //}}AFX_VIRTUAL

public:
    virtual ~CAdUiDockControlBar();

protected:
    enum {
        btnWidth    = 12,
        btnHeight   = 12,
        idCloseBtn  = 10001,
        idPinBtn    = 10002
    };

protected:
    // windows message handlers
    //{{AFX_MSG(CAdUiDockControlBar)
    afx_msg void OnWindowPosChanged (WINDOWPOS FAR* lpwndpos);
    afx_msg BOOL OnEraseBkgnd (CDC* pDC);
    afx_msg void OnAllowDock ();
    afx_msg void OnAnchor ();
    afx_msg void OnAnchorLeft();
    afx_msg void OnAnchorRight();
    afx_msg void OnHideBar ();
    afx_msg void OnContextMenu (CWnd* pWnd, CPoint point);
    afx_msg int  OnCreate (LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint ();
    //afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    //}}AFX_MSG


protected:
    void GetUsedRect (CRect& rect);
    void ShowCloseButton (bool bShow) { m_bShowCloseButton = bShow; };
    bool CloseButtonVisible () { return m_bShowCloseButton; };
    void RepositionOrHideButtons ();
    static LRESULT CALLBACK MouseProc (int nCode, WPARAM wParam, LPARAM lParam);

    // Overridable functions
    virtual void PaintControlBar (CDC *pDC);
    virtual BOOL CreateControlBar (LPCREATESTRUCT lpCreateStruct);
    virtual void SizeChanged (CRect * /*lpRect*/, BOOL /*bFloating*/, int /*flags*/) {}
    virtual bool OnClosing ();
    virtual void GetFloatingMinSize (long *pnMinWidth, long *pnMinHeight);
    virtual BOOL AddCustomMenuItems(LPARAM hMenu); 
    virtual void OnUserSizing (UINT /*nSide*/, LPRECT /*pRect*/) {};
    
    DECLARE_DYNAMIC (CAdUiDockControlBar)
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiDockFrame window

class ADUI_PORT CAdUiDockFrame : public CMiniDockFrameWnd   // INTERNAL USE ONLY 
{
    DECLARE_DYNCREATE (CAdUiDockFrame)

public:
                CAdUiDockFrame ();

// Docking frame
public:
        enum ContainedBarType { Unknown, Standard, AdskBar } ;

        enum ContainedBarType GetContainedBarType ();
protected:
        enum ContainedBarType m_nContainedBarType;
        bool m_bZOrderChanged;

        bool CanFrameworkTakeFocus ();
        void ForceChildRepaint ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiDockFrame)
    protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiDockFrame)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnClose();
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint pt);
#if _MSC_VER<1400
    afx_msg UINT OnNcHitTest(CPoint point);
#else
    afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
    afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
    afx_msg void OnWindowPosChanging (WINDOWPOS* lpwndpos);
    afx_msg void OnPaint ();
    afx_msg void OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI);
    afx_msg void OnSizing (UINT nSide, LPRECT pRect);
    //}}AFX_MSG

    bool CanAutoCADTakeFocus ();

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CAdUiPaletteSetDockFrame window

class ADUI_PORT CAdUiPaletteSetDockFrame : public CMiniDockFrameWnd   // INTERNAL USE ONLY 
{
    friend class CAdUiImpPaletteSet;
    friend class CAdUiDockDragContext;
    friend class CAdUiDockBarMutator;
    friend class CAdUiAnchorBar;

    DECLARE_DYNCREATE (CAdUiPaletteSetDockFrame)

public:
    CAdUiPaletteSetDockFrame ();
    virtual ~CAdUiPaletteSetDockFrame ();

    virtual BOOL Create(CWnd* pParent, DWORD dwBarStyle);
    static bool HidePalettes();
    static bool ShowPalettes();

    // Docking frame
public:
    enum ContainedBarType { Unknown, Standard, AdskBar } ;

    enum ContainedBarType GetContainedBarType ();

    void SetAutoRollup(BOOL bSet);
    virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);

    // AdUiTitleBarLocation
    typedef enum {
        kLeft = 0,
        kRight
    } AdUiTitleBarLocation ;

    // Returns enum specifiying title bar location
    CAdUiPaletteSetDockFrame::AdUiTitleBarLocation TitleBarLocation();
    void SetTitleBarLocation(CAdUiPaletteSetDockFrame::AdUiTitleBarLocation);

protected:
    enum ContainedBarType m_nContainedBarType;
    bool m_bZOrderChanged;

    bool CanFrameworkTakeFocus ();
    void ForceChildRepaint ();

    /// <summary>
    /// Updates the themed UI elements.  This method should be called in a themed
    /// environment after a theme switch.
    /// </summary>
    void UpdateThemeElements();

    // ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiPaletteSetDockFrame)
    protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    //}}AFX_VIRTUAL
    
protected:
    virtual BOOL PreTranslateMessage(MSG * msg);

    //{{AFX_MSG(CAdUiPaletteSetDockFrame)
    afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void    OnDestroy();
    afx_msg void    OnSize(UINT nType, int cx, int cy);
    afx_msg void    OnClose();
    afx_msg void    OnLButtonDown(UINT nHitTest, CPoint pt);
    afx_msg void    OnNcLButtonDown(UINT nHitTest, CPoint pt);
    afx_msg void    OnNcRButtonDown(UINT nHitTest, CPoint pt);
    afx_msg void    OnNcRButtonUp(UINT nHitTest, CPoint pt);
    afx_msg void    OnNcLButtonUp(UINT nHitTest, CPoint pt);
#if _MSC_VER<1400
    afx_msg UINT OnNcHitTest(CPoint point);
#else
    afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
    afx_msg void    OnMouseMove(UINT nHitTest, CPoint pt);
    afx_msg void    OnNcMouseMove(UINT nHitTest, CPoint pt);
    afx_msg int     OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
    afx_msg void    OnWindowPosChanging (WINDOWPOS* lpwndpos);
    afx_msg void    OnPaint ();
    afx_msg void    OnNcPaint ();
    afx_msg LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
    afx_msg void    OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized );
    afx_msg BOOL    OnNcActivate(BOOL bActive);
    afx_msg void    OnGetMinMaxInfo (MINMAXINFO FAR* lpMMI);
    afx_msg void    OnSizing (UINT nSide, LPRECT pRect);
    afx_msg void    OnShowWindow( BOOL bShow, UINT nStatus );
    afx_msg BOOL    OnSetCursor(CWnd *pwnd, UINT nHitTest, UINT msg);
    afx_msg void    OnSetFocus(CWnd * pOldWnd);
    afx_msg void    OnTimer(UINT_PTR nIdEvent);
    afx_msg void    OnContextMenu(CWnd* pWnd, CPoint pos);
    afx_msg BOOL    OnEraseBkgnd(CDC* pDC);
    afx_msg LRESULT OnEnterSizeMove(WPARAM, LPARAM);
    afx_msg LRESULT OnExitSizeMove(WPARAM, LPARAM);
    afx_msg void    OnSettingChange( UINT uFlags, LPCTSTR lpszSection );
    //}}AFX_MSG

    // Handler for UM_ADUI_DRAG_ENTER.
    virtual LRESULT OnDragEnter(WPARAM wParam, LPARAM lParam);
    // Handler for UM_ADUI_DRAG_OVER.
    virtual LRESULT OnDragOver(WPARAM wParam, LPARAM lParam);
    // Handler for UM_ADUI_DROP.
    virtual LRESULT OnDrop(WPARAM wParam, LPARAM lParam);
    // Handler for UM_ADUI_DROP_EX.
    virtual LRESULT OnDropEx(WPARAM wParam, LPARAM lParam);
    // Handler for UM_ADUI_DRAG_LEAVE.
    virtual LRESULT OnDragLeave(WPARAM wParam, LPARAM lParam);
    // Handler for UM_ADUI_DRAGSCROLL 
    virtual LRESULT  OnDragScroll(WPARAM wParam, LPARAM lParam);

    bool CanAutoCADTakeFocus ();

    // Determines which part of the palette set, if any, is at a specified position.
    BOOL HitTest(CPoint pt, UINT& nFlag, DWORD& dwData);

    CAdUiPaletteSet* GetPaletteSet();

    DECLARE_MESSAGE_MAP()

private:

    enum AdUiSkBtnItems {
        kBtnUnknown     = -1,
        kBtnPushPin     = 0,
        kBtnOptionMenu  = 1,
        kBtnClose       = 2,
        kBtnIcon        = 3,
    };

    enum AdUiSkIds {
        kRollupTimerId = 0x3011,
        kRolloutTimerId = 0x3012,
        kCursorCheckTimerId = 0x3013
    };

    enum AdUiSkUiFlags {
        kImgListUnpinnedLeft        = 0,
        kImgListUnpinnedRight       = 1,
        kImgListPinnedLeft          = 2,
        kImgListPinnedRight         = 3, 
        kImgListOptionMenuLeft      = 4,
        kImgListOptionMenuRight     = 5,
        kImgListClose               = 6,
        kImgList_Count              = 7,
    };

    void ncPaint(UINT nPtFlags);
    void windowToNonClient(CRect & rect);
    void nonclientToWindow(CRect & rect);
    void getRegion(CRgn & rgn);
    void getBorderRects(CRect & rectTop, CRect & rectBottom, CRect & rectSide);
    int getMetrics(UINT nItem);
    void getWndCaptionRect(CRect & rect);
    void getWndStatusRect(CRect & rect);
    void getWndSizerRect(CRect & rect);
    void getButtonItemRect(AdUiSkBtnItems eBtn, CRect & rect);
    void GetNonClientSize(CSize& size);
    int  GetTopGrabbableHeight();
    void SnapToRect(CRect & rect, WINDOWPOS * pWndpos,
                    int nPaletteWidth, int nPaletteHeight,
                    bool bSnapInside, bool bSnapOutside);
    void InitFonts();
    BOOL isImgListItemValid(int nItem);
    // Called when the options menu button in the palette set is clicked
    void OnOptionsMenu();
    // Called by the OnContextMenu() handler if the right click is in the
    // caption area.
    void OnSystemMenu(CPoint pos);

    bool btnPress(AdUiSkBtnItems eBtn, LPPOINT pt);

    //helpers for the btnPress method
    void btnPressOptionMenu();
    void btnPressPushPin();
    void btnPressClose();

    void setWindowRgn();

    void    doDrawCaption(CDC *pDC);    
    void    doDrawStatus(CDC *pDC);
    void    doDrawBorder(CDC* pDC);
    void    doDrawButton(CDC *pDC, AdUiSkBtnItems btnItem, BOOL bErase = false);
    void    doEraseBackground(CDC *pDC, const CRect & rect, BOOL bErase);
    void    doButtonBlt(CDC *pDC,int nImage, CRect &rcBtn);

    void        displayTip(LPPOINT pt);

    void        SetRollupDelay();
    DWORD       GetRollupDelay() {
        return m_bDelayRolledOut ? m_nHoldopenDelay : m_nRollupDelay; }
    void        SetRolloutDelay();
    DWORD       GetRolloutDelay() { return m_nRolloutDelay; }

    void        RollOut(CPoint * pPt, bool bDelay = false);
    void        rollupDlg(BOOL bRollup = TRUE);
    void        SetRolloutTimer();
    void        SetRollupTimer();
    bool        shouldWindowBeRolledUp( CWnd* pWndUnderCursor, CAdUiPaletteSet& ps) const;

    // Returns TRUE if the palette set window is "rolled up"
    BOOL RolledUp() { return (! m_rectSize.IsRectEmpty()); }
    CRect m_rectSize;                     // Store the full dialog size (when rolled)
    CSize m_sizeShadow;
    CRect m_rectCaptionText;
    CImageList m_imgListGui;
    CImageList m_imgListIcon;
    DWORD m_dwUiTransientFlags;
    bool  m_bRolloutTimerSet;
    bool  m_bRollupTimerSet;
    static DWORD m_nRollupDelay;
    static DWORD m_nRolloutDelay;
    static DWORD m_nHoldopenDelay;
    CPaletteSetTooltip* m_pToolTip; // not used
    BOOL  m_bAllowSnapping;
    CAdUiDropTarget* m_pDropTarget;
    AdUiTitleBarLocation m_orphanTitleBarLoc;
    bool m_bUserEnteredAutoHideMode;
    CRect m_rectWorkArea;
    bool m_bDelayRolledOut;
};

#endif // _ADESK_MAC_
#pragma warning(pop)

/////////////////////////////////////////////////////////////////////////////

void ADUI_PORT AdUiSaveDockingToolPositions (); // INTERNAL USE ONLY 
void ADUI_PORT AdUiShowDockControlBars (bool bShow); // INTERNAL USE ONLY
bool ADUI_PORT AdUiRegisterDockingTool (                                // INTERNAL USE ONLY 
    LPCTSTR lpszToolName, LPCTSTR lpszCommand, UINT nToolbarID
);
bool ADUI_PORT AdUiRegisterTool (
    LPCTSTR lpszToolName, LPCTSTR lpszCommand, CLSID* pID
);

ADUI_PORT CRuntimeClass* AdUiSetFloatingFrameClass(CRuntimeClass* pNewClass);

ADUI_PORT void AdUiRegisterFloatingFrameClassAddress(CRuntimeClass** pClass);
ADUI_PORT void AdUiRegisterPaletteSetFloatingFrameClass(CRuntimeClass* pClass); // INTERNAL USE ONLY
ADUI_PORT CRuntimeClass* AdUiGetRegisteredPaletteSetFloatingFrameClass(void);

typedef HRESULT ADUI_LOADFN(IUnknown** ppAdUiRootNode);
typedef HRESULT ADUI_SAVEFN(IUnknown* pAdUiRootNode);

#ifndef _ADESK_MAC_
void ADUI_PORT AdUiEnableDocking (                                      // INTERNAL USE ONLY 
    CFrameWnd *pFrame, DWORD dwDockStyle, ADUI_LOADFN* pLoadFcn, ADUI_SAVEFN* pSaveFcn);

// INTERNAL USE ONLY
class ADUI_PORT CAdUiPaletteSetDockSite {
public:
    void Initialize(CControlBar* pBar, CSize* pDesiredSize, DWORD dwDockStyle);
    CRect* CanDock(const CPoint& pMousePos);
    bool DockControlBar(CControlBar* pBar);
private:
    DWORD           m_dwDockStyle;
    CControlBar*    m_pBar;
    CAdUiDockBar*   m_pTargetDockBar;
    CFrameWnd*      m_pDockSite;
    
    CRect m_rectDragDock;
    CRect m_rectDragHorz;
    CRect m_rectDragHorzAlone;

};
#endif // _ADESK_MAC_

bool ADUI_PORT CanStealFocusFromDockedWindow ();                        // INTERNAL USE ONLY 
void ADUI_PORT GetSystemVirtualScreen(RECT &rect);        // INTERNAL USE ONLY

void ADUI_PORT AdUiEnableDockControlBars(BOOL bEnable, CStringArray* pToolIds = NULL); // INTERNAL USE ONLY
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif
