//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// Purpose:
//
// Encapsulates the theme of the UI elements. It contains the colors of 
// different elements of the window, fonts, etc. The palette and other 
// window classes can get the UI look from this theme. The theme can contain 
// different set of values for different UI windows. For example it can have 
// one set of colors and fonts for all the dialogs and another set of colors 
// and fonts for all the palettes
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ADUI_THEME_H_
#define _ADUI_THEME_H_
#include "adesk.h"
#ifdef _ADESK_WINDOWS_
#include <afxtempl.h>
#include "AdAChar.h"
#include "AcColorThemeEnum.h"

class CAcColorTheme;

#define PROPERTY_PALETTE_THEME  ACRX_T(/*MSG0*/"PropertyPalette")
#define TOOL_PALETTE_THEME      ACRX_T(/*MSG0*/"ToolPalette")
#define OWNDERDRAW_BUTTON_THEME ACRX_T(/*MSG0*/"OwnerDrawButton")
#define DIALOG_WORKSHEET_THEME  ACRX_T(/*MSG0*/"DialogWorksheet")
#define PALETTE_SET_THEME       ACRX_T(/*MSG0*/"PaletteSet")
#define DESIGN_CENTER_THEME     ACRX_T(/*MSG0*/"DesignCenter")   // Constant theme for all apps, dom't override
#define TOOL_PANEL_THEME        ACRX_T(/*MSG0*/"ToolPanel")
#define DOCKBAR_THEME           ACRX_T(/*MSG0*/"DockBar")   
#define DOCKCONTROLBAR_THEME    ACRX_T(/*MSG0*/"DockControlBar")   
#define ANCHORBAR_THEME         ACRX_T(/*MSG0*/"AnchorBar")   
#define ACTIVE_THEME            ACRX_T(/*MSG0*/"ACTIVETHEME")
#define DIALOG_THEME            ACRX_T(/*MSG0*/"DIALOGTHEME")


typedef enum {
    
    kUnknownElements = -1,

    // Theme fonts
    kPaletteFontCaption,
    kPaletteFontTab,
    kPaletteFontToolTip,
    kPaletteFont,
    kWorksheetFont,
    kWorksheetFontCaption,
    kInspectorItemFont,
    kInspectorRootFont,

    // Theme colors

    // Palette Set Colors
    kPaletteBackground,
    kPaletteCaptionBackground,
    kPaletteCaptionInactive,
    kPaletteCaptionText,
    kPaletteCaptionInactiveText,
    kPaletteTabText,
    kPaletteTabBackground,
    kPaletteBorder,
    kPaletteTabShadow,
    kPaletteTabHighlight,
    kPaletteTabTextHilite,
    kPaletteTabSelectHilite,
    kPaletteToolTip,
    kPaletteToolTipText,
    kPaletteButtonText,
    kPaletteButtonTextDisabled,
    kPaletteButtonBorder,
    kPaletteItemText,
    kPaletteScrollBackground,
    kPaletteScrollThumb,
    kPaletteScrollArrow,

    // Worksheets
    kWorksheetBackground,
    kWorksheetCaptionBackground,
    kWorksheetCaptionText,
    kWorksheet3DBtnShadow,
    kWorksheetButtonText,
    kWorksheetButtonTextDisabled,
    kWorksheetScrollBackground,
    kWorksheetScrollThumb,
    kWorksheetBorder,
    kWorksheetGripHighlight,

    // Property Inspectors
    kInspector,
    kInspectorTop,
    kInspectorCat,
    kInspectorItem,
    kInspectorBorder,
    kInspectorBorderItem,
    kInspectorTextTop,
    kInspectorTextCat,
    kInspectorTextItem,
    kInspectorTextLabel,
    kInspectorFGHighlight,
    kInspectorBGHighlight,
    kInspector3dShadow,
    kInspectorControl,
    kInspectorCatChevron1,
    kInspectorCatChevron2,
    kInspectorSubChevron,
    kInspectorCellHighlight,

    // Panel Colors
    kPanelBackground,
    kPanelSashBackground,
    kPanelBorder,

    //General control colors
    kControlBorder,
    kControlBackground,  
    kDisabledControlBorder,
    kControlSupport,
    kControlHighlight,
    kControlActiveOuterBorder,
    kControlErrorOuterBorder,
    kControlActiveText,
    kControlText,
    kControlInactiveText,

    // Extra Palette Set Colors
    kPaletteFrameInnerBorder,
    kPaletteFrameOuterBorder,
    kPaletteFrameBackground,
    kPaletteFrameShadow,
    kInspectorTopGradient1,
    kInspectorTopGradient2,
    kPaletteScrollBackgroundBorder,
    kPaletteScrollBackgroundGradient1,
    kPaletteScrollBackgroundGradient2,
    kPaletteScrollSliderInactive,
    kPaletteScrollSliderActiveOuterBorder,
    kPaletteScrollSliderActiveOuterGradient1,
    kPaletteScrollSliderActiveOuterGradient2,
    kPaletteScrollSliderActiveOuterGradient3,
    kPaletteScrollSliderActiveOuterGradient4,
    kPaletteScrollSliderActiveInnerGradient1,
    kPaletteScrollSliderActiveInnerGradient2,
    kInspectorClosedOuterBorder,
    kInspectorOpenOuterBorder,
    kInspectorInnerBorder,
    kPaletteColumnHeaderBackground,
    kPaletteHyperlinkText,
    kPaletteTreeOrListBackground,

    // Anchor Bar Colors
    kAnchorBarOuterBorder,
    kAnchorBarEmbossRightBottom,
    kAnchorBarEmbossLeftTop,
    kAnchorBarInnerHighlight,
    kAnchorBarGradient1,
    kAnchorBarGradient2,
    kAnchorBarActiveTitleBackground,
    kAnchorBarCaptionText,

    // Other Colors
    kGrabBarDotDark,
    kGrabBarDotLight,
    kControlBarTitleBackground,

    
    // Application Frame Window Colors
    kAppFrameBorder,
    kAppFrameOuterBorder,
    kAppFrameAFGradientTop,
    kAppFrameAFGradientBottom,
    // Application Frame Caption area
    kAppFrameCaptionActiveGradientTop,
    kAppFrameCaptionActiveGradientBottom,
    kAppFrameCaptionInActiveGradientTop,
    kAppFrameCaptionInActiveGradientBottom,
    kAppFrameCaptionOuterBorder,
    kAppFrameCaptionInnerBorder,
    // Application Frame Quick Access Toolbar
    kAppFrameQATGradientTop,
    kAppFrameQATGradientBottom,
    kAppFrameQATOuterBorder,
    kAppFrameQATInnerBorder,

    kAppFrameQATButtonsBorder,
    kAppFrameQATButtonsRolloverBorder,
    kAppFrameQATButtonsClickBorder,
    kAppFrameQATFlyoutButtonText,

    // Application Frame Menu Browser Button
    kAppFrameBigMBBGradientFillTop,          
    kAppFrameBigMBBGradientFillMiddleUpper,  
    kAppFrameBigMBBGradientFillMiddleLower,  
    kAppFrameBigMBBGradientFillBottom,       

    kAppFrameSmallMBBGradientFillTop,        
    kAppFrameSmallMBBGradientFillMiddleUpper,
    kAppFrameSmallMBBGradientFillMiddleLower,
    kAppFrameSmallMBBGradientFillBottom,     

    // Application Frame Document name text
    kAppFrameDocNameProductNameText,
    kAppFrameDocNameFileNameText,
    kAppFrameDocNameInactiveProductNameText,
    kAppFrameDocNameInactiveFileNameText,
    // Application Frame Menu Bar
    kAppFrameMenuBarMenuText,
    kAppFrameMenuBarMenuHighlightText,
    kAppFrameMenuBarMenuDeHighlightText,
    kAppFrameMenuBarRolloverBorder,
    kAppFrameMenuBarRolloverFill,
    kAppFrameMenuBarClickBorder,
    kAppFrameMenuBarClickFill,
    // Application Frame application window control buttons
    kAppFrameAppWindowControlButtonsRolloverGradientBorderTop,
    kAppFrameAppWindowControlButtonsRolloverGradientBorderMiddle,
    kAppFrameAppWindowControlButtonsRolloverGradientBorderBottom,
    kAppFrameAppWindowControlButtonsRolloverGradientFillTop,
    kAppFrameAppWindowControlButtonsRolloverGradientFillMiddleUpper,
    kAppFrameAppWindowControlButtonsRolloverGradientFillMiddleLower,
    kAppFrameAppWindowControlButtonsRolloverGradientFillBottom,
    kAppFrameAppWindowControlButtonsClickGradientBorderTop,
    kAppFrameAppWindowControlButtonsClickGradientBorderMiddle,
    kAppFrameAppWindowControlButtonsClickGradientBorderBottom,
    kAppFrameAppWindowControlButtonsClickGradientFillTop,
    kAppFrameAppWindowControlButtonsClickGradientFillMiddleUpper,
    kAppFrameAppWindowControlButtonsClickGradientFillMiddleLower,
    kAppFrameAppWindowControlButtonsClickGradientFillBottom,
    // Application Frame Info Center Toggle Button color
    kAppFrameInfoCenterToggleButtonText,
    // Application Frame Zero Doc state background
    kAppFrameZeroDocBackgroundGradientTop,
    kAppFrameZeroDocBackgroundGradientBottom,

    //Status bar colors.
    kStatusBarPaneUnSelectedTopGradient,
    kStatusBarPaneUnSelectedBottomGradient,
    kStatusBarPaneRolloverGradient1,
    kStatusBarPaneRolloverGradient2,
    kStatusBarPaneRolloverGradient3,
    kStatusBarPaneRolloverGradient4,
    kStatusBarPaneSelectionGradient1,
    kStatusBarPaneSelectionGradient2,
    kStatusBarPaneSelectionGradient3,
    kStatusBarPaneSelectionGradient4,
    kStatusBarPaneBorder1,
    kStatusBarPaneBorder2,
    kStatusBarBkGrdBorder,
    kStatusBarBkGrdInnerLine,
    kStatusBarBkGrdTopGradient,
    kStatusBarBkGrdBottomGradient,

    //Toolbar specific colors
    kToolbarGripDarkDot,
    kToolbarGripLightDot,
    kToolbarGripBackground,
    kToolbarBorder,
    kToolbarBackground,
    kToolbarRolloverBorder,
	kToolbarCloseButton,

    //Square Button colors
    kSquareButtonHoverBorder,
    kSquareButtonHoverHighlight,
    kSquareButtonHoverBackgroundTop,
    kSquareButtonHoverBackgroundBottom,
    kSquareButtonClickBorder,
    kSquareButtonClickHighlight,
    kSquareButtonClickBackgroundTop,
    kSquareButtonClickBackgroundBottom,

    //Combo box colors
    kComboBoxBackgroundTop,
    kComboBoxBackgroundBottom,
    kComboBoxActiveBackgroundTop,
    kComboBoxActiveBackgroundBottom,
    kComboBoxArrow,
    kComboBoxArrowShadow,
    kComboBoxHoverText,
    kComboBoxSelectText,
    kComboBoxHoverBackgroundTop,
    kComboBoxHoverBackgroundBottom,
    kComboBoxSelectBackgroundTop,
    kComboBoxSelectBackgroundBottom,
    kComboBoxHoverSelectHighlight,

    //Spin control colors
    kSpinControlHighlight,
    kSpinControlBorder,
    kSpinControlClickBackgroundTop,
    kSpinControlClickBackgroundBottom,
    kSpinControlBackgroundTop,
    kSpinControlBackgroundBottom,
    
    //Text input colors
    kTextInputInnerShadow,
    kTextInputActiveBackgroundTop,
    kTextInputActiveBackgroundBottom,
    kTextInputActiveHighlight,
    kTextInputActiveText,
    kTextInputActiveBorder,

    //splitter control colors
    kCategoryExpander,
    kCategoryExpanderShadow,
    kGroupGrip,
    kGroupGripShadow,
    kCategoryBackground,
    kCategoryBorder,
    kCategoryActiveText,

    //List box colors
    kListBoxHoverBackgroundTop,
    kListBoxHoverBackgroundBottom,
    kListBoxHoverBorder,
    kListBoxClickBackgroundTop,
    kListBoxClickBackgroundBottom,
    kListBoxClickBorder,
    kListBoxSelectBackgroundTop,
    kListBoxSelectBackgroundBottom,
    kListBoxSelectBorder,
    kListBoxSelectHoverBackgroundTop,
    kListBoxSelectHoverBackgroundBottom,
    kListBoxSelectHoverBorder,
    kListBoxInnerShadow,
    kListBoxSelectText,

    //Tree and List control colors
    kTreeControlLine

} AdUiThemeElement;

/// <summary>
/// CAdUiThemeModifiedReactor is a reactor class which receives theme-modified notifications
/// from CAdUiTheme
/// </summary>
class CAdUiThemeModifiedReactor
{
public:
    /// <summary>
    /// Virtual method that receives the theme modification event.
    /// </summary>
    /// <param name="pTheme">
    /// The pointer to the theme that was modified.
    /// </param>
    /// <param name="element">
    /// A index of the theme element that was modified.
    /// </param>
    /// <remarks>
    /// This method is also called when the theme uses the active theme colors
    /// and the active theme is changed.  In that case, element = kUnknownElements
    /// </remarks>        
    virtual void ThemeModified(const CAdUiTheme * pTheme, AdUiThemeElement element) = 0;
};


/// <summary>
/// CAdUiTheme class is collection of ARGB Color, font, and other data for various
/// UI elements of an application (e.g. AutoCAD). Using various methods on this class, 
/// a client can query for various types of UI data for the current theme or change them.
/// </summary>
class ADUI_PORT CAdUiTheme
{
    friend class CAdUiThemeManager;

public:
    /// <summary>
    /// Gets the RGB color of the specified display element. 
    /// </summary>
    /// <param name="nDisplayElement">
    /// Input display element for a theme color
    /// </param>
    /// <returns>
    /// A RBG color in COLORREF format
    /// </returns>
    COLORREF GetColor (AdUiThemeElement nDisplayElement) const;

    /// <summary>
    /// Gets the ARGB color of the specified display element. 
    /// </summary>
    /// <param name="nDisplayElement">
    /// Input display element for a theme color
    /// </param>
    /// <returns>
    /// A color in ARGB format
    /// </returns>
    DWORD GetARGBColor(AdUiThemeElement nDisplayElement) const;

    /// <summary>
    /// Sets the RGB color of the specified display element. 
    /// </summary>
    /// <param name="nDisplayElement">
    /// Input display element for a theme color
    /// </param>
    /// <param name="crColor">
    /// Input RBG color in COLORREF format
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL SetColor(AdUiThemeElement nDisplayElement, COLORREF crColor);

    /// <summary>
    /// Sets the ARGB color of the specified display element. 
    /// </summary>
    /// <param name="nDisplayElement">
    /// Input display element for a theme color
    /// </param>
    /// <param name="dColor">
    /// Input color in ARGB format
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL SetARGBColor(AdUiThemeElement nDisplayElement, DWORD dColor);

    /// <summary>
    /// Sets the font of the specified display element. 
    /// </summary>
    /// <param name="nDisplayElement">
    /// Input display element for a font
    /// </param>
    /// <param name="plf">
    /// Input pointer to a LOGFONT object.  System font is used if the input is a NULL pointer.
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL SetFont(AdUiThemeElement nDisplayElement, LOGFONT *plf = NULL);

    /// <summary>
    /// Gets the font of the specified display element as a LOGFONT pointer
    /// </summary>
    /// <param name="nDisplayElement">
    /// Input display element for a font
    /// </param>
    /// <param name="plf">
    /// Output pointer to a LOGFONT object.
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL GetFont(AdUiThemeElement nDisplayElement, LOGFONT *plf) const;

    /// <summary>
    /// Gets the font of the specified display element as a CFont object
    /// </summary>
    /// <param name="nDisplayElement">
    /// Input display element for a font
    /// </param>
    /// <param name="pFont">
    /// Output pointer to a pFont object.
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL GetFont(AdUiThemeElement nDisplayElement, CFont *& pFont) const;

    /// <summary>
    /// Gets the stored DWORD data of the specified display element
    /// </summary>
    /// <param name="nElement">
    /// Input index of a display element
    /// </param>
    /// <param name="dwData">
    /// Output DWORD data
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL GetData(int nElement, DWORD& dwData) const;

    /// <summary>
    /// Stores DWORD data of the specified display element in the theme
    /// </summary>
    /// <param name="nElement">
    /// Input index of a display element
    /// </param>
    /// <param name="dwData">
    /// Input DWORD data
    /// </param>
    void SetData(int nElement, const DWORD& dwData);

    /// <summary>
    /// Gets the stored CString data of the specified display element
    /// </summary>
    /// <param name="nElement">
    /// Input index of a display element
    /// </param>
    /// <param name="sData">
    /// Output CString data
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL GetData(int nElement, CString& sData) const;

    /// <summary>
    /// Stores CString data of the specified display element in the theme
    /// </summary>
    /// <param name="nElement">
    /// Input index of a display element
    /// </param>
    /// <param name="sData">
    /// Input CString data
    /// </param>
    void SetData(int nElement, const CString& sData);

    /// <summary>
    /// Gets the stored data pointer of the specified display element
    /// </summary>
    /// <param name="nElement">
    /// Input index of a display element
    /// </param>
    /// <returns>
    /// A void type data pointer
    /// </returns>
    void* GetDataPtr(int nElement) const;

    /// <summary>
    /// Stores data of the specified display element in the theme as a void data pointer
    /// </summary>
    /// <param name="nElement">
    /// Input index of a display element
    /// </param>
    /// <param name="pData">
    /// Input data pointer
    /// </param>
    void SetDataPtr(int nElement, void* pData);

    /// <summary>
    /// Registers a reactor for a theme client to obtain theme-modified notifications
    /// </summary>
    /// <param name="pReactor">
    /// Input pointer to the reactor instance
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL RegisterReactor(CAdUiThemeModifiedReactor * pReactor);

    /// <summary>
    /// Unregisters a reactor for a theme client to stop obtaining theme-modified notifications
    /// </summary>
    /// <param name="pReactor">
    /// Input pointer to the reactor instance
    /// </param>
    /// <returns>
    /// TRUE if successful or FALSE otherwise
    /// </returns>
    BOOL UnregisterReactor(CAdUiThemeModifiedReactor * pReactor);

    /// <summary>
    /// Temporarily suspends sending theme-modified notifications to its reactors.  Call this
    /// method before making changes to a theme if the reactors do not need to know about these
    /// changes.  Call ResumeModifiedNotifications after all changes are made.
    /// </summary>
    void SuspendModifiedNotifications() { m_nModNotificationsSuspended++; }

    /// <summary>
    /// Resumes sending theme-modified notifications to its reactors
    /// </summary>
    void ResumeModifiedNotifications();

    /// <summary>
    /// Sends a theme-modified notification to its theme reactors with kUnknownElements
    /// </summary>
    void SendModifiedNotification() const;

    /// <summary>
    /// Gets if the theme uses the colors of the current active theme
    /// </summary>
    /// <returns>
    /// If the theme uses the colors of the current active theme
    /// </returns>
    bool UsesActiveThemeColors() const { return m_pColorTheme == NULL; }

    /// <summary>
    /// Gets if the theme has a dark color scheme.  This method can help to determine which
    /// image is to be used for the theme, if there are two images for the same UI element
    /// </summary>
    /// <returns>
    /// If the theme has a dark color scheme
    /// </returns>
    bool IsDark() const;

    /// <summary>
    /// Increments the reference count of the theme so that the theme will not be deleted
    /// </summary>
    /// <remarks>
    /// The CAdUiThemeManager::ReleaseTheme(CAdUiTheme*) method can be used to decrement
    /// the reference count of a theme if it is no longer needed by the client code.
    /// </remarks>
    void IncrementRefCount() { m_nRefCount++; }

    // assignment operator
    CAdUiTheme& operator=(const CAdUiTheme& Theme);

    // utility methods

    /// <summary>
    /// Does alpha blending of a translucent foreground color with an opaque background color
    /// to produce a new opaque foreground color.
    /// </summary>
    /// <param name="fgColor">
    /// Input translucent foreground color in ARGB format
    /// </param>
    /// <param name="bgColor">
    /// Input opaque background color in COLORREF format
    /// </param>
    /// <returns>
    /// An opaque foreground color in COLORREF format
    /// </returns>
    static COLORREF GetRGBForeColor(DWORD fgColor, COLORREF bgColor);

private:
    CAdUiTheme();
    CAdUiTheme(const CAcColorTheme & colorTheme, AcColorThemeEnum themeType);
    virtual ~CAdUiTheme();
    void commonInitialize();
    void SetColorTheme(const CAcColorTheme& colorTheme, AcColorThemeEnum themeType);
    void InitializeFont(LOGFONT & sourceLF, LOGFONT & destLF, int fontType = 0);
    void InitializeFontsForDialog();

    void SendThemeModifiedNotifications(AdUiThemeElement nElement) const;

    void CheckXP();
    
    // Are XP themes supported (FUTURE USE!)
    BOOL UsesXP() { return m_bUsesXPThemes; };

    void DecrementRefCount() { m_nRefCount--; }
    int RefCount() { return m_nRefCount; }

    int    m_nRefCount;
    CTypedPtrArray<CPtrArray, CAdUiThemeModifiedReactor*> m_arrayModReactors;
    int m_nModNotificationsSuspended;
    CMap<int, int, DWORD, DWORD> m_mapDwordValues;
    CMap<int, int, CString, CString> m_mapStringValues;
    CMap<int, int, void*, void*> m_mapPointerValues;

    LOGFONT             m_lfWorksheet;
    LOGFONT             m_lfWorksheetCaption;
    LOGFONT             m_lfPaletteCaption;
    LOGFONT             m_lfInspectorItem;
    LOGFONT             m_lfInspectorRoot;
    LOGFONT             m_lfPaletteTab;
    LOGFONT             m_lfPalette;
    LOGFONT             m_lfPaletteToolTip;

    CAcColorTheme*      m_pColorTheme;
    AcColorThemeEnum    m_themeType;

    BOOL                m_bUsesXPThemes;    
};

#endif // _ADESK_WINDOWS_
#endif // ifndef _ADUI_THEME_H_

