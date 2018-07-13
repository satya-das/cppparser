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
// DESCRIPTION:
//
//   Declarations for various button classes:
//
// CAdUiOwnerDrawButton
//     - A basic owner-draw button.
//   CAdUiBitmapButton
//       - A simple bitmap button.
//     CAdUiBitmapStatic
//         - A bitmap button that defaults to behaving like a static.
//       CAdUiDropSite
//           - A static bitmap that enables Drag&Drop by default.
//     CAdUiToolButton
//         - A bitmap button that enables tool button display by default.
//    CAdUiThemedDropDownBitmapButton
//        A bitmap button that have a drop down menu.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiButton_h
#define _aduiButton_h
#pragma pack (push, 8)

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "AdUiTheme.h"

#ifndef _ADESK_MAC_

class CAdUiOwnerDrawButton;
class CAdUiTrackButtonDraw;

class CAdUiODButtonThemeModReactor : public CAdUiThemeModifiedReactor  // INTERNAL USE ONLY
{
public:
    CAdUiODButtonThemeModReactor(CAdUiOwnerDrawButton* pBtn);  // INTERNAL USE ONLY
    virtual void ThemeModified(const CAdUiTheme * pTheme, AdUiThemeElement element);  // INTERNAL USE ONLY

private:
    CAdUiOwnerDrawButton * m_pBtn;
};


/////////////////////////////////////////////////////////////////////////////
// CAdUiOwnerDrawButton
#pragma warning(push)
#pragma warning(disable : 4275)
class ADUI_PORT CAdUiOwnerDrawButton : public CButton {
    friend class CAdUiODButtonThemeModReactor;  // INTERNAL USE ONLY

    DECLARE_DYNAMIC(CAdUiOwnerDrawButton)

public:
                CAdUiOwnerDrawButton ();
    virtual     ~CAdUiOwnerDrawButton ();

protected:
    CPoint  m_lastMousePoint;
    CRect   m_tipRect;
    CAdUiTheme * m_pTheme;

// AdUi message handler
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

    virtual void    SetTracking(BOOL b) { m_bIsTrackButton = !!b; };

    /// <summary>
    /// Sets the theme to be used by the owner draw button
    /// </summary>
    /// <param name="pTheme">
    /// Input pointer to the CAdUiTheme instance
    /// </param>
    /// <returns>
    /// The current theme used by the owner draw button
    /// </returns>
    virtual CAdUiTheme * SetTheme(CAdUiTheme *pTheme);

// Owner Draw routines
protected:
    static const UINT_PTR m_timerEvent;
            bool    m_bEnableDragDrop   : 1;
            bool    m_bEnableFastDraw   : 1;
            bool    m_bEnablePointedAt  : 1;
            bool    m_bIsPointedAt      : 1;
            bool    m_bIsStatic         : 1;
            bool    m_bIsToolButton     : 1;
            bool    m_bIsTrackButton    : 1;
            UINT_PTR  m_timerId;

            // members added for XP look and feel
            int     m_nPartId;
            int     m_nStateId;
            UINT    m_uEdge;
            BOOL    m_bMouseHover;

    virtual void    DrawBorder(CDC *pDC,CRect &r,COLORREF cr);
    virtual void    DrawHotBorder();
    virtual void    DrawButton(
                        CDC& dc, int w, int h,
                        BOOL isDefault,
                        BOOL isDisabled,
                        BOOL isSelected,
                        BOOL isFocused
                    );
    virtual void    DrawPushButtonBorder (
                        CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected
                    );
    virtual void    DrawToolButtonBorder (
                        CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused
                    );
            void    DrawTransparentBitmap (
                        CDC& dc,
                        CBitmap& bmp,
                        int x, int y, int w, int h,
                        BOOL isDisabled
                    );
            void    DrawContentText (
                        CDC& dc,
                        CString sText,
                        CRect& rcText,
                        BOOL isDisabled
                    );
            BOOL    GetIsPointedAt ();
            void    SetIsPointedAt (BOOL isPointedAt);
    virtual BOOL    OnAutoLoad ();
    virtual void    OnDragDrop (HDROP hDropInfo);
    virtual void    OnPointedAt (BOOL isPointedAt);
    virtual BOOL    OnReload (LPCTSTR strResId);
            void    StartTimer (DWORD ms=50);
            void    StopTimer ();

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

public:
    BOOL    AutoLoad ();
    BOOL    GetEnableDragDrop ();
    void    SetEnableDragDrop (BOOL allow);
    BOOL    GetEnableFastDraw ();
    void    SetEnableFastDraw (BOOL allow);
    BOOL    GetEnablePointedAt ();
    void    SetEnablePointedAt (BOOL allow);
    BOOL    GetIsStatic ();
    void    SetIsStatic (BOOL isStatic);
    BOOL    GetIsToolButton ();
    void    SetIsToolButton (BOOL isToolButton);
    BOOL    Reload (LPCTSTR strResId);

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiOwnerDrawButton)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiOwnerDrawButton)
    afx_msg LRESULT OnAdUiMessage (WPARAM wParam, LPARAM lParam);
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg UINT OnGetDlgCode();
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
    afx_msg void OnNcDestroy();
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy( );
    afx_msg LRESULT OnThemeChanged(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
protected:
	HANDLE GetVisualStylesTheme() {return m_hVS;}
private:
    CAdUiODButtonThemeModReactor* m_pThemeModReactor;  // INTERNAL USE ONLY
	HANDLE    m_hVS;               // INTERNAL USE ONLY
};
#pragma warning(pop)
/////////////////////////////////////////////////////////////////////////////
// CAdUiBitmapButton

class ADUI_PORT CAdUiBitmapButton : public CAdUiOwnerDrawButton 
{
    DECLARE_DYNAMIC(CAdUiBitmapButton)

    friend class CAdUiImpBitmapButton;
public:
    CAdUiBitmapButton ();
    virtual ~CAdUiBitmapButton ();

    enum Constants
    {
        ThemedSize = 24,
    };

    BOOL GetAutoSizeToBitmap ();
    void SetAutoSizeToBitmap (BOOL autoSizeToBitmap);
    void SizeToBitmap ();
    bool SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);

    /// <summary>
    /// Gets if the bitmap button has a themed look
    /// </summary>
    /// <returns>
    /// True if the bitmap button has a themed look or false otherwise
    /// </returns>
    virtual BOOL IsThemed() const;

    /// <summary>
    /// Sets if the bitmap button has a themed look
    /// </summary>
    /// <param name="isThemed">
    /// True if the bitmap button has a themed look or false otherwise
    /// </param>
    virtual void SetIsThemed(BOOL isThemed);

    /// <summary>
    /// Enables or disables the themed hover and/or click state
    /// </summary>
    /// <param name="bEnableHover">
    /// Specify if the themed hover state should be enabled
    /// </param>
    /// <param name="bEnableClick">
    /// Specify if the themed click state should be enabled
    /// </param>
    virtual void EnableThemedState(BOOL bEnableHover, BOOL bEnableClick);
    
    /// <summary>
    /// Sets the theme to be used by the bitmap button
    /// </summary>
    /// <param name="pTheme">
    /// Input pointer to the CAdUiTheme instance
    /// </param>
    /// <returns>
    /// The current theme used by the bitmap button
    /// </returns>
    virtual CAdUiTheme * SetTheme(CAdUiTheme *pTheme);

    /// <summary>
    /// Overrides the theme element to be used as the backgrounnd color in the
    /// themed draw.  The default background color is the palette background color.
    /// </summary>
    /// <param name="nElement">
    /// Input new theme element to be used as the themed background color
    /// </param>
    virtual void SetThemeBackground(AdUiThemeElement nElement);

    enum ImageDrawStyle
    {
        kImageDrawStyle_Default              = 0x0,
        kImageDrawStyle_Static               = 0x1,
        kImageDrawStyle_Center               = 0x2,
        kImageDrawStyle_Stretch_BtnSize      = 0x3,
    };

    /// <summary>
    /// Gets the image drawing style.
    /// </summary>
    /// <returns>
    /// ImageDrawStyle specify how the image is drawn.
    /// </returns>
    ImageDrawStyle GetImageDrawStyle() const;

    /// <summary>
    /// Sets how the image is drawn on button.
    /// </summary>
    /// <param name="style">
    /// kImageDrawStyle_Default, the image is drawn at default bitmap offset without stretch.
    /// kImageDrawStyle_Static, the image is drawn at (0, 0) without stretch.
    /// kImageDrawStyle_Center, the image is drawn at the center of the button without stretch.
    /// kImageDrawStyle_Stretch_BtnSize, the image is stretched to the button client rect.
    /// </param>
    void SetImageDrawStyle(ImageDrawStyle style);

    BOOL LoadBitmap (LPCTSTR strResId);

protected:
    // Owner Draw routines
    virtual void  DrawButton(CDC& dc, int w, int h,
                             BOOL isDefault,
                             BOOL isDisabled,
                             BOOL isSelected,
                             BOOL isFocused);
    virtual void DrawButtonImage(CDC* pDC, const CRect& rect, BOOL isSelected, BOOL isDisabled);
    virtual void DrawFocusMark(CDC* pDC, CRect& rect, BOOL isDefault, BOOL isSelected, BOOL isFocused);
    virtual BOOL OnAutoLoad ();
    virtual BOOL OnReload (LPCTSTR strResId);

    /// <summary>
    /// Draws the button with a themed look.  It is called from the DrawButton() method
    /// when IsThemed() returns true.
    /// </summary>
    /// <param name="dc">
    /// Input device context to draw the control 
    /// </param>
    /// <param name="x">
    /// Input x coordinate in pixels of the upper-left corner of the rectangle for the control 
    /// </param>
    /// <param name="y">
    /// Input y coordinate in pixels of the upper-left corner of the rectangle for the control 
    /// </param>
    /// <param name="width">
    /// Input width in pixels of the rectangle for the control 
    /// </param>
    /// <param name="height">
    /// Input height in pixels of the rectangle for the control 
    /// </param>
    /// <param name="statusId">
    /// Input status ID of the control.  It is a windows PUSHBUTTON state such as PBS_NORMAL 
    /// </param>
    virtual void DrawThemedButton(CDC& dc, int x, int y, int width, int height, int statusId);

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

    // Bitmap Button routines
    enum ImageType
    {
        kImageType_Undefined,
        kImageType_Bitmap,
        kImageType_Icon,
        kImageType_RCDATA
    };

    /// <summary>
    /// Loads an icon resource to be used as the button image 
    /// </summary>
    /// <param name="strResId">
    /// Input resouce ID of the icon
    /// </param>
    /// <param name="hInst">
    /// Input handle of the application or DLL that will provide the resouce.
    /// If hInst is NULL, no resource swapping is attempted, otherwise the
    /// indicated module's resources will be used to provide the icon.
    /// </param>
    /// <returns>
    /// TRUE if strResId is not empty and the icon is successfully loaded;
    /// FALSE Otherwise.
    /// </returns>
    BOOL LoadIconResource(LPCTSTR strResId, HINSTANCE hInst = NULL);

    /// <summary>
    /// Loads an RCDATA resource to be used as the button image 
    /// </summary>
    /// <param name="strResId">
    /// Input resouce ID of the RCDATA
    /// </param>
    /// <param name="hInst">
    /// Input handle of the application or DLL that will provide the resouce.
    /// If hInst is NULL, no resource swapping is attempted, otherwise the
    /// indicated module's resources will be used to provide the RCDATA.
    /// </param>
    /// <returns>
    /// TRUE if strResId is not empty and the RCDATA is successfully loaded;
    /// FALSE Otherwise.
    /// </returns>
    BOOL LoadRCDATAResource(LPCTSTR strResId, HINSTANCE hInst = NULL);

    BOOL LoadBitmapResource (LPCTSTR strResId, CBitmap& bmp, HINSTANCE hInst = NULL);

    virtual BOOL OnLoadBitmap (LPCTSTR strResId);

    /// <summary>
    /// Clears the image resouces and the cached resource ID if the parameter bClearResId is true.
    /// </summary>
    /// <param name="bClearResId">
    /// Specify if the cached resource ID should be cleared as well
    /// </param>
    void ClearImages(bool bClearResId = false);

    /// <summary>
    /// Calculates the size of the image 
    /// </summary>
    void CalcBitmapSize();

    /// <summary>
    /// Saves the image resource ID and type, and caluclate the size of the image
    /// </summary>
    /// <param name="strResId">
    /// Input resouce ID of the image resource
    /// </param>
    /// <param name="type">
    /// Input type of the image resource
    /// </param>
    void SaveAndCalcSize(LPCTSTR strResId, ImageType type);

    BOOL    m_bAutoSizeToBitmap;
    CBitmap m_bmp;
    void *  m_image;
    CString m_bmpResId;
    int     m_bmpHeight;
    int     m_bmpWidth;
    int     m_bmpX;
    int     m_bmpY;
    int     m_focusRectOffset;
    BOOL    m_isThemed;
    BOOL    m_enableThemedHoverState;
    BOOL    m_enableThemedClickState;
    AdUiThemeElement m_backgroundElement; 
    ImageType m_imageType;
    ImageDrawStyle m_imageDrawStyle;

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiBitmapButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiBitmapButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiBitmapStatic

class ADUI_PORT CAdUiBitmapStatic : public CAdUiBitmapButton {
    DECLARE_DYNAMIC(CAdUiBitmapStatic)

public:
                CAdUiBitmapStatic ();
virtual         ~CAdUiBitmapStatic ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiBitmapStatic)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiBitmapStatic)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiDropSite

class ADUI_PORT CAdUiDropSite : public CAdUiBitmapStatic {
    DECLARE_DYNAMIC(CAdUiDropSite)

public:
                CAdUiDropSite ();
virtual         ~CAdUiDropSite ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiDropSite)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiDropSite)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiToolButton

class ADUI_PORT CAdUiToolButton : public CAdUiBitmapButton {
    DECLARE_DYNAMIC(CAdUiToolButton)

public:
                CAdUiToolButton ();
virtual         ~CAdUiToolButton ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiToolButton)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiToolButton)
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiTrackButton

class ADUI_PORT CAdUiTrackButton : public CAdUiOwnerDrawButton {
    DECLARE_DYNAMIC(CAdUiTrackButton)

public:
                CAdUiTrackButton();
                CAdUiTrackButton(const CAdUiTrackButtonDraw & pDraw);
virtual         ~CAdUiTrackButton();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiTrackButton)
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    //}}AFX_VIRTUAL

    /// <summary>
    /// Gets the theme used by the track button
    /// </summary>
    /// <returns>
    /// The pointer to the CAdUiTheme instance used by the track button
    /// </returns>
    virtual CAdUiTheme * GetTheme() const;

    /// <summary>
    /// Sets the theme to be used by the track button
    /// </summary>
    /// <param name="pTheme">
    /// Input pointer to the CAdUiTheme instance
    /// </param>
    /// <returns>
    /// The current theme used by the track button
    /// </returns>
    virtual CAdUiTheme * SetTheme(CAdUiTheme *pTheme);

    static  CAdUiTrackButtonDraw * SetDefaultDraw(CAdUiTrackButtonDraw * pDraw);
            CAdUiTrackButtonDraw * SetDraw(CAdUiTrackButtonDraw * pDraw);

    virtual void    SetTracking(BOOL b);

protected:
    virtual void    DrawButton(
                        CDC& dc, int w, int h,
                        BOOL isDefault,
                        BOOL isDisabled,
                        BOOL isSelected,
                        BOOL isFocused
                    );
    virtual void    DrawBorder(CDC *pDC,CRect &r,COLORREF cr);
    virtual void    DrawHotBorder();
    virtual void    DrawPushButtonBorder (CDC& dc, CRect& rButton, BOOL isDefault, BOOL isSelected);
    virtual void    DrawToolButtonBorder (CDC& dc, CRect& rButton, BOOL isSelected, BOOL isFocused);

    virtual ADUI_REPLY OnGetTipSupport (CPoint& p);

    //{{AFX_MSG(CAdUiTrackButton)
    afx_msg void OnNcPaint();
    afx_msg void OnPaint();
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    virtual void releaseDraw();

// Implementation
private:
    static CAdUiTrackButtonDraw * s_pDefaultDraw;
    CAdUiTrackButtonDraw * m_pDraw;

};

class ADUI_PORT CAdUiBitmapTextButton : public CAdUiBitmapButton // Internal Use!
{
    friend class CAdUiImpBitmapButton;
    DECLARE_DYNAMIC(CAdUiBitmapTextButton)
public:
    enum ButtonType
    {
        kBitmap = 0x1,
        kText = 0x2,
    };

    enum BitmapLocation
    {
        kLeft = 0x1,
        kTop = 0x2,
        kRight = 0x4,
        kBottom = 0x8,
    };

	enum ButtonStyle
	{
		kButtonStyleNone  = 0,
		kButtonStyleFlat  = 0x1,
		kButtonStyleCheck = 0x2,

		kButtonHCenter     = 0x00000300,
		kButtonVCenter    = 0x00000C00,
	};
 
public:
    CAdUiBitmapTextButton();
    virtual ~CAdUiBitmapTextButton();

    // Owner Draw routines
protected:
    virtual void DrawButton(
        CDC& dc, int w, int h,
        BOOL isDefault,
        BOOL isDisabled,
        BOOL isSelected,
        BOOL isFocused
        );
    virtual BOOL OnAutoLoad ();
    virtual BOOL OnReload (LPCTSTR strResId);
    virtual BOOL OnLoadBitmap (LPCTSTR strResId);

public:
    BOOL                GetAutoSizeToContent ();
    void                SetAutoSizeToContent (BOOL autoSizeToContent);
    void                SizeToContent ();
    void                SetContentOffsets(int nBorderOffset, 
                                                    int nFocusRectOffset);
    UINT                GetButtonType();
    UINT                GetBitmapLocation();
    UINT                SetButtonType(UINT btnType);
    UINT                SetBitmapLocation(UINT imgPos);
	
	ButtonStyle			GetBitmapTextButtonStyle() const;
	void				SetBitmapTextButtonStyle(ButtonStyle nBtnStyle);

    DECLARE_MESSAGE_MAP()
public:
    BOOL				GetAutoSizeToBitmap ();
    void				SetAutoSizeToBitmap (BOOL autoSizeToBitmap);
    void				SizeToBitmap ();
    void				SetBitmapOffsets(int nBorderOffset, int nFocusRectOffset);
	
	void				SetBkColor(COLORREF);
	void				SetBorderColor(COLORREF);

	void				SetCheck(int nCheck);
	int					GetCheck();

	HICON				SetIcon(HICON hIcon, BOOL bRedraw = TRUE);
	HICON				GetIcon() const;
	HBITMAP				SetBitmap(HBITMAP hBitmap, BOOL bRedraw = TRUE);
	HBITMAP				GetBitmap() const;
private:
    void*               mpImpObj;
};

/////////////////////////////////////////////////////////////////////////////
// CAdUiDropDownBitmapButton
/// <summary>
/// CAdUiThemedDropDownBitmapButton is an owner-draw button that incorporates a
/// combobox-like drop-down/pop-up button. The control's display is partitioned
/// between a main button (occupying the left half) and a menu button (on the right).
/// When the control detects a click, the parent will be notified as usual.
/// The parent may inspect the control to determine if the main button or
/// the menu button was clicked. After processing the click notification the
/// parent should call ClearClick() to reset the control's state. The control
/// will send a BN_CLICKED notification when it encounters a Down Arrow key
/// press (similar to the standard combobox keyboard handling).
///
/// The menu portion of the button can be turned off.
/// </summary>
class ADUI_PORT CAdUiThemedDropDownBitmapButton : public CAdUiBitmapButton
{
    DECLARE_DYNAMIC(CAdUiThemedDropDownBitmapButton)
public:
    enum
    {
        BitmapButtonSize = 24,
        MenuButtonWidth = 15,
    };
    CAdUiThemedDropDownBitmapButton();
    virtual ~CAdUiThemedDropDownBitmapButton();

    /// <summary>
    /// Gets if the main button is selected
    /// </summary>
    /// <returns>
    /// TRUE if the main button is selected or FALSE otherwise
    /// </returns>
    BOOL            GetMainButtonSelected ();

    /// <summary>
    /// Sets if the main button is selected
    /// </summary>
    /// <param name="selected">
    /// TRUE if the main button is selected or FALSE otherwise
    /// </param>
    void            SetMainButtonSelected (BOOL selected);

    /// <summary>
    /// Gets if the menu button is selected
    /// </summary>
    /// <returns>
    /// TRUE if the menu button is selected or FALSE otherwise
    /// </returns>
    BOOL            GetMenuButtonSelected ();

    /// <summary>
    /// Sets if the menu button is selected
    /// </summary>
    /// <param name="selected">
    /// TRUE if the menu button is selected or FALSE otherwise
    /// </param>
    void            SetMenuButtonSelected (BOOL selected);
    
    /// <summary>
    /// Clears the selection state of both the main button and the menu button
    /// </summary>
    void            ClearClick ();

    /// <summary>
    /// Gets the width of the menu button
    /// </summary>
    /// <returns>
    /// The menu button width in pixels
    /// </returns>
    virtual int     GetMenuButtonWidth ();

    /// <summary>
    /// Sets the width of the menu button
    /// </summary>
    /// <param name="width">
    /// The menu button width in pixels
    /// </param>
    /// <returns>
    /// True if successful or false otherwise
    /// </returns>
    virtual bool    SetMenuButtonWidth(int width);

protected:
    BOOL    m_bMainButtonSelected;              //flag whether button part is selected.
    BOOL    m_bMenuButtonSelected;              //flag whether button part is selected.
    int     m_menuButtonWidth;                  //menu button width.

protected:
    /// <summary>
    /// This routine is called from the inherited DrawItem() to handle painting of the control.
    /// </summary>
    /// <param name="dc">
    /// Input device context to draw the control 
    /// </param>
    /// <param name="w">
    /// Input width in pixels of the rectangle for the control 
    /// </param>
    /// <param name="h">
    /// Input height in pixels of the rectangle for the control 
    /// </param>
    /// <param name="isDefault">
    /// Input Boolean indicating whether the control should appear as a default pushbutton  
    /// </param>
    /// <param name="isDisabled">
    /// Input Boolean indicating whether the control should appear disabled  
    /// </param>
    /// <param name="isSelected">
    /// Input Boolean indicating whether the control should appear selected (in other words, pressed) 
    /// </param>
    /// <param name="isFocused">
    /// Input Boolean indicating whether the control should appear to have keyboard focus    
    /// </param>
    virtual void DrawButton(CDC& dc, int w, int h, BOOL isDefault, BOOL isDisabled, BOOL isSelected, BOOL isFocused);

    //{{AFX_MSG(CAdUiDropDownBitmapButton)
    afx_msg void OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKillFocus (CWnd *pNewWnd);
    afx_msg void OnLButtonDown (UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp (UINT nFlags, CPoint point);
    afx_msg void OnSysKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

#endif //_ADESK_MAC_

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
