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
// Purpose:
//
// A palette set is a frame which holds one or more palettes.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef _ADUI_PALETTE_SET_H_
#define _ADUI_PALETTE_SET_H_

#include <afxtempl.h>
#include "AcColorThemeEnum.h"

class CAdUiPalette;
class CAdUiImpPaletteSet;

// Palette Set Styles
#define PSS_AUTO_ROLLUP                  0x00000002 // Support automatic roll-up when the pin is up. 
#define PSS_PROPERTIES_MENU              0x00000004 // Display properties button in the caption to edit palette properties.
#define PSS_CLOSE_BUTTON                 0x00000008 // Support "close" button in caption
#define PSS_EDIT_NAME                    0x00000010 // Support editing of palette set name through in-place editing
#define PSS_SNAP                         0x00000020 // Support snapping to application, screen, and other palette sets
#define PSS_SINGLE_PALETTE_TAB           0x00000040 // Tab visibility for palette set containing a single palette.
#define PSS_USE_SINGLE_PALETTE_TAB_NAME  0x00000080 // Use palette name in paletee set title bar for single palette set.
#define PSS_SINGLE_ROW_HORZ_DOCK         0x00000200 // INTERNAL USE
#define PSS_NOTIFY                       0x00000400 // INTERNAL USE
#define PSS_SINGLE_ROW_NOVERTRESIZE      0x00000800 // INTERNAL USE
#define PSS_SINGLE_COL_VERT_DOCK         0x00001000 // INTERNAL USE
#define PSS_NO_ROLLUP_BUTTON             0x00002000 // Do not display Roll Up botton in the caption
#define PSS_NO_ICON                      0x00004000 // Do not display Icon in the caption
#define PSS_NO_TITLEBAR                  0x00008000 // INTERNAL USE
#define PSS_AUTO_ROLLUP_PAUSE_ON_MODAL_DIALOG 0x00010000    //  INERNAL USE


// INTERNAL USE ONLY

// Palette Set Hit Test constants
#define ADUI_HT_CAPTION                             1 // Title bar
#define ADUI_HT_OPTION_BUTTON                       2 // Option button
#define ADUI_HT_ROLLUP_BUTTON                       3 // Roll up button
#define ADUI_HT_CLOSE_BUTTON                        4 // Close button
#define ADUI_HT_GRIP                                5 // Grip area
#define ADUI_HT_TABS                                6 // One of the tabs
#define ADUI_HT_PALETTE                             7 // Client area of the palette set which is also the palette area.
#define ADUI_HT_TAB_OVERFLOW                        8 // Tab overflow indicator
#define ADUI_HT_PALETTESET                          9 // Client area of the palette set which is NOT also the palette area.


#ifndef _ADESK_MAC_
#pragma warning(push)
#pragma warning(disable : 4275)
/////////////////////////////////////////////////////////////////////////////
//
// class CAdUiPaletteSet
//
class ADUI_PORT CAdUiPaletteSet : public CAdUiDockControlBar
{
    friend class CAdUiImpPaletteSet;
    friend class CAdUiPaletteSetDockFrame;
    friend class CAdUiAnchorBar;
    friend class CAdUiPalette;
    friend class CAdUiDockDragContext;
    DECLARE_DYNCREATE(CAdUiPaletteSet);

public:
    CAdUiPaletteSet(int nStyle = 0);
    virtual ~CAdUiPaletteSet();

    BOOL Create(LPCTSTR strTitle, DWORD dwStyle, const RECT &rect,
                CWnd *pwndParent,
                DWORD dwPaletteSetStyle = PSS_PROPERTIES_MENU | PSS_AUTO_ROLLUP | PSS_CLOSE_BUTTON | PSS_SNAP);

    // Returns the palette set style. 
    DWORD GetPaletteSetStyle();
    // Sets the palette set style. dwStyle is a bit flag. 
    void SetPaletteSetStyle(DWORD dwStyle);

    // Style access methods
    BOOL AutoRollupStyle();
    BOOL PropertiesMenuStyle();
    BOOL CloseButtonStyle();
    BOOL SinglePaletteTabStyle();
    BOOL UseSinglePaletteTabNameStyle();
    BOOL EditNameStyle();
    BOOL SnapStyle();
    BOOL ShowRollupButtonStyle();
    BOOL ShowIconStyle();

    // Returns the palette set name.
    CString GetName();
    // Sets the palette set name.
    BOOL SetName(LPCTSTR pszName);

    /// <summary>
    /// Gets the theme being used by the palette set
    /// </summary>
    /// <returns>
    /// The pointer to the CAdUiTheme instance being used
    /// </returns>
    CAdUiTheme* GetTheme();

    /// <summary>
    /// Sets the theme to be used by the palette set
    /// </summary>
    /// <param name="pTheme">
    /// The pointer to the CAdUiTheme instance
    /// </param>
    /// <returns>
    /// The current theme being used by the palette set
    /// </returns>
    CAdUiTheme* SetTheme(CAdUiTheme* pTheme);

    // Returns the current opacity. 
    int GetOpacity() const;
    // Sets the opacity of the palette set. Value Range: 0 to 100. 
    // 0 is fully transparent and 100 is opaque.
    BOOL SetOpacity(int nOpacity);    
    int GetRolloverOpacity() const;
    BOOL SetRolloverOpacity(int nOpacity);
    
    static int GetGlobalOpacity();
    static BOOL SetGlobalOpacity(int nOpacity);
    static int GetGlobalRolloverOpacity ();
    static BOOL SetGlobalRolloverOpacity(int nOpacity);
    static BOOL IsGlobalOpacitiesApplied();
    static void ApplyGlobalOpacities(BOOL bApply);
    
    // Returns the currently active palette. 
    CAdUiPalette* GetActivePalette();
    int GetActivePaletteTabIndex();
    // Sets the specified palette as active
    BOOL SetActivePalette (CAdUiPalette* pPalette);
    BOOL SetActivePalette (int nPaletteIndex);

    // Enables auto roll-up so that the palette set is collapsed 
    // to display only the title bar until the user passes mouse 
    // over the title bar.  If bSet is false disables auto roll-up 
    // and the palette set is always shown.
    BOOL SetAutoRollup(BOOL bSet = TRUE);

    // Returns TRUE if auto roll-up is enabled.
    BOOL GetAutoRollup();

    // Trigger a roll out of the palette set, if auto-rollup is on,
    // and the palette set is not docked
    // if bTmp is true, we use the holdopen delay value before rolling back in
    void RollOut(bool bDelay = false);
    // Trigger a roll up of the palette set, if auto-rollup is on,
    // and the palette set is not docked
    void RollUp();

    //Appends the palette to the palette set
    int AddPalette(CAdUiPalette* pPalette);
    // Inserts a palette at the specified (zero-based) index. 
    int InsertPalette(int iIndex, CAdUiPalette* pPalette);
    // Removes the palette from the palette set
    BOOL RemovePalette(CAdUiPalette* pPalette);
    BOOL RemovePalette(int nPaletteIndex);
    // Returns the number of palettes in the palette set.
    int GetPaletteCount();
    // Retrieve a palette associated with a particular tab index
    CAdUiPalette * GetPalette(int nIndex);
    // Find the tab index of a palette.  Returns -1 if the palette is not in
    // this palette set.
    int GetTabIndex(CAdUiPalette* pPalette);

    // Retrieve the full size of the palette set window rectangle (even if it's
    // currently rolled-up, this will return the full "unrolled" size
    void GetFullRect(CRect & rect);

    // Returns the non-client size
    BOOL GetNonClientSize(CSize& size); // INTERNAL USE ONLY

    // Loads the data from xml file 
    virtual BOOL Load(IUnknown* pUnk);
    // Saves the data to xml file
    virtual BOOL Save(IUnknown* pUnk);

    // Returns TRUE if the palette set window is "rolled up"
    BOOL RolledUp();

    // AdUiTitleBarLocation
    typedef enum {
        kLeft = 0,
        kRight
    } AdUiTitleBarLocation ;

    // Returns enum specifiying title bar location
    AdUiTitleBarLocation TitleBarLocation();

    // Set the title bar location
    void SetTitleBarLocation(AdUiTitleBarLocation loc);

    // Notify that the title bar location (left or right) has been updated.
    virtual void TitleBarLocationUpdated(AdUiTitleBarLocation /*newLoc*/) {}

    // Update palette set's tab display (like when a palette name is updated)
    void UpdateTabs();

    // Enable docking
    void EnableDocking(DWORD dwDockStyle);

    // Called when the editing of the palette set name using in-place editing is completed
    // Return of TRUE means the name is valid.
    virtual BOOL NameEditValidation(CEdit* pEdit);

    // Retrieve the font for the palette set window.  (Not necessarily the same as
    // CWnd::GetFont() due to the palette set's use of themes.)
    CFont   *  GetWindowFont();
    
    //CAdUiAnchorBar* AnchorDock();
protected:
    // In-place editing of palette set name.
    virtual void EditName();
    // Determines which part of the palette set, if any, is at a specified position.
    BOOL HitTest(CPoint pt, UINT& nFlag, DWORD& dwData);
    // Called by the palette set before the context menu of the palette set is 
    // displayed in response to right clicking on the palette set, to give you 
    // the opportunity to add your own context menu options, and/or to remove 
    // the existing default menu options.  If nHitFlag indicates a tab area
    // hit, then the third parameter will provide the palette index of the tab
    // which has been clicked on.
    virtual BOOL AddContextMenuItems(CMenu * pMenu, int nHitFlag, int nRightClkTab = 0);
    // Return FALSE to indicate that the palette should not give up focus,
    // TRUE to indicate that the palette doesn't need focus.
    virtual bool CanFrameworkTakeFocus();
    // Called by the palette set framework to determine size constraints.
    // Override these methods to provide minimum and maximum palette set sizes.
    virtual void GetMinimumSize(CSize& size);
    virtual void GetMaximumSize(CSize& size);
    // Methods that a derived palette set class can override to reserve vertical space
    // in the palette set client area for palette set use (thereby decreasing the
    // palette set client area given to the palettes.
    virtual int GetTopReservedHeight();
    virtual int GetBottomReservedHeight();
    // Derived palette set class can override this method to get notification
    // when a palette is added
    virtual void PaletteAdded(CAdUiPalette* /*pPalette*/) {}
    // Derived palette set class can override this method to get notification
    // when a palette is removed
    virtual void PaletteRemoved(CAdUiPalette* /*pPalette*/) {}
    // Derived palette set class can override this method to get notification
    // when a palette is activated
    virtual void PaletteActivated(CAdUiPalette* /*pActivated*/,
                                  CAdUiPalette* /*pDeactivated*/) {}
    // Derived palette set class can override this method to get notification
    // when the "AutoRollup" state changes
    virtual void AutoRollupChanged(BOOL /*bAutoRollupIsOn*/) {}

    virtual void OnTabDrag(CPtrArray & arrayPalettes);  // INTERNAL USE ONLY

    // When a palette set is docked, a "grabber bar" is drawn within the window's
    // client area.  This can cause problems for positioning palette set elements.
    // Use this method to get the adjusted palette set client rect.  For example,
    // if the palette set is docked on the side of the application frame, this method
    // will return a rect whose top coordinate is 13 rather than 0.  Palette set
    // elements should be positioned within this "adjusted" client rect.
    void GetAdjustedClientRect(CRect & rect);

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

    virtual void OnContextMenu(CWnd* pWnd, CPoint pos);  // INTERNAL USE ONLY
    
    /// <summary>
    /// Helper method to inform all palettes of a theme change; should be called from
    /// overridden ThemeModified() if the palette set wishes to inform the palettes
    /// it owns of a theme change
    /// </summary>
    void SendThemeModifiedToPalettes();

    //{{AFX_VIRTUAL(CAdUiPaletteSet)
public:
    virtual BOOL PreTranslateMessage(MSG * msg);
    //}}AFX_VIRTUAL

    static bool SetGlobalTransparency(UINT flag); // INTERNAL USE ONLY
    static UINT GetGlobalTransparency(); // INTERNAL USE ONLY
    bool SetAllowTransparency(CString key, bool bDefault); // INTERNAL USE ONLY
    
    void OnTogglePin(); // INTERNAL USE ONLY

    /// <summary>
    /// Returns the icon for the current palette theme and the specified size.
    /// </summary>
    ///
    /// <param name="bBigIcon">
    /// Specifies whether the desired icon is for the large or
    /// small size. Defaults to the small size.
    /// </param>
    ///
    /// <returns>
    /// Returns the icon for the current palette theme and specified size.
    /// </returns>
    ///
    HICON GetThemedIcon(bool bBigIcon = false) const;

    /// <summary>
    /// Sets the icon for the specified theme and size.
    /// </summary>
    ///
    /// <param name="hIcon">
    /// The specified icon.
    /// </param>
    /// <param name="theme">
    /// Specifies the theme to which the specified icon applies. 
    /// Defaults to eAcadLightTheme.
    /// </param>
    /// <param name="bBigIcon">
    /// Specifies whether the specified icon applies to the large or
    /// small size. Defaults to the small size.
    /// </param>
    ///
    /// <returns>
    /// Returns the previous value of the specified icon.
    /// </returns>
    ///
    HICON SetThemedIcon(HICON hIcon, AcColorThemeEnum theme = eAcadLightTheme, bool bBigIcon = false);

protected:
    //{{AFX_MSG(CAdUiPaletteSet)
    afx_msg int     OnCreate(LPCREATESTRUCT lpCs);
    afx_msg void    OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL    OnEraseBkgnd(CDC *pdc);
    afx_msg void    OnLButtonDown(UINT nFlags, CPoint pt);
    afx_msg void    OnLButtonUp(UINT nFlags, CPoint pt);
    afx_msg void    OnLButtonDblClk(UINT nFlags, CPoint pt);
    afx_msg void    OnMouseMove(UINT nFlags, CPoint pt);
    afx_msg LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
#if _MSC_VER<1400
    afx_msg UINT OnNcHitTest(CPoint point);
#else
    afx_msg LRESULT OnNcHitTest(CPoint point);
#endif
    afx_msg void    OnNcPaint();
    afx_msg void    OnPaint();
    afx_msg void    OnSetFocus(CWnd * pOldWnd);
    afx_msg void    OnActivate( UINT nState, CWnd* pWndOther, BOOL bMinimized );
    afx_msg void    OnWindowPosChanging (WINDOWPOS* lpwndpos);
    afx_msg void    OnWindowPosChanged (WINDOWPOS FAR* lpwndpos);
    afx_msg LRESULT OnFloatStatus(WPARAM wParam, LPARAM lParam); // INTERNAL USE ONLY
    afx_msg LRESULT OnBeginNameEdit(WPARAM, LPARAM);  // INTERNAL USE ONLY
    afx_msg LRESULT OnEndNameEdit(WPARAM, LPARAM);  // INTERNAL USE ONLY
    afx_msg void    OnMenuClose(); // INTERNAL USE ONLY
    afx_msg void    OnMenuMove(); // INTERNAL USE ONLY
    afx_msg void    OnMenuSize(); // INTERNAL USE ONLY
    afx_msg void    OnOptionTranslucency(); // INTERNAL USE ONLY
    afx_msg void    EditPaletteName(); // INTERNAL USE ONLY
    afx_msg LRESULT OnGetPaletteCount(WPARAM wParam,LPARAM lParam);// INTERNAL USE ONLY
    afx_msg LRESULT OnGetPaletteName(WPARAM wParam,LPARAM lParam);// INTERNAL USE ONLY
    afx_msg LRESULT OnSetPaletteActive(WPARAM wParam,LPARAM lParam);// INTERNAL USE ONLY
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
    CAdUiImpPaletteSet * m_pImpPS;
};

#pragma warning(pop)
#endif  // _ADESK_MAC_
#endif // _ADUI_PALETTE_SET_H_
