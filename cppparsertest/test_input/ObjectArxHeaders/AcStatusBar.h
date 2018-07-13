//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _ACSTATUSBAR_H
#define _ACSTATUSBAR_H 1

#pragma pack (push, 8)

// enable this to get deprecation warning
// #define NEW_STATUS_BAR

#ifdef NEW_STATUS_BAR
#define SB_DEPRECATED __declspec(deprecated)
#else
#define SB_DEPRECATED
#endif

#ifndef ACAD_PORT
#define ACAD_PORT
#endif

#include "acdocman.h"
#include "adesk.h"

class CMenu;

class AcStatusBarItem
{
public:
    AcStatusBarItem();
    ACAD_PORT AcStatusBarItem(const CString& strId, bool isTrayItem); // NEW
    virtual ~AcStatusBarItem();

    ACAD_PORT bool IsTrayItem() const;          // NEW
    ACAD_PORT const CString& GetName() const;   // NEW

    virtual BOOL SetIcon(HICON hIcon);
    virtual HICON GetIcon() const;

    virtual BOOL SetToolTipText(const CString& strText);
    virtual BOOL GetToolTipText(CString& strText) const;

    SB_DEPRECATED virtual BOOL QueryToolTipText(CString& strText) const;

    virtual void Enable(BOOL bValue);
    virtual BOOL IsEnabled();

    virtual void SetVisible(BOOL bIsVisible);
    virtual BOOL IsVisible();

    virtual void OnLButtonDown(UINT nFlags, CPoint point);
    virtual void OnRButtonDown(UINT nFlags, CPoint point);
    virtual void OnLButtonDblClk(UINT nFlags, CPoint point);

    virtual void OnDelete();

    SB_DEPRECATED virtual BOOL ClientToScreen(LPPOINT lpPoint);
    SB_DEPRECATED virtual BOOL ClientToScreen(LPRECT lpRect);

    SB_DEPRECATED virtual BOOL ScreenToClient(LPPOINT lpPoint);
    SB_DEPRECATED virtual BOOL ScreenToClient(LPRECT lpRect);

    virtual UINT DisplayContextMenu(CMenu& menu, CPoint point);

    SB_DEPRECATED virtual BOOL ShowTraySettingsDialog();

    //////////////////////////////////////////////////////////////////////////////
    // Note: These methods are for INTERNAL USE ONLY.  Using these methods may
    //       adversely affect application functionality
    SB_DEPRECATED virtual void SetContentChanged(BOOL bChanged) {m_bContentChanged = bChanged;}
    SB_DEPRECATED virtual BOOL ContentChanged() const {return m_bContentChanged;}

    SB_DEPRECATED virtual void SetVisibilityChanged(BOOL bChanged) {m_bVisibilityChanged = bChanged;}
    SB_DEPRECATED virtual BOOL VisibilityChanged() const {return m_bVisibilityChanged;}

    SB_DEPRECATED virtual void SetInternalData(void* pData, BOOL bForDocSwitch = FALSE);
    SB_DEPRECATED virtual void* GetInternalData(BOOL bForDocSwitch = TRUE) const;
    void*   GetData();

    ACAD_PORT int GetID() const;
    ACAD_PORT void SetID(int id);

    ACAD_PORT CString& GetActiveImageState() const;
    ACAD_PORT void SetActiveImageState(const CString& strActiveImageState);

   // End INTERNAL USE ONLY.
    //////////////////////////////////////////////////////////////////////////////
private:
    HICON           m_hIcon;
    CString         m_strToolTipText;
    BOOL            m_bEnabled;
    BOOL            m_bVisible;
    BOOL            m_bContentChanged;
    BOOL            m_bVisibilityChanged;
    void*           m_pData;
    void*           m_pDocSwitchData;
};

#define ACSB_NOBORDERS  (1<<0) // Deprecated
#define ACSB_INACTIVE   (1<<1)
#define ACSB_STRETCH    (1<<2) // Deprecated
#define ACSB_ACTIVE     (1<<3)
#define ACSB_COMMAND    (1<<4) // Deprecated
#define ACSB_POPUP      (1<<5)
#define ACSB_DIVIDER    (1<<6)
#define ACSB_SUBDIVIDER (1<<7)
#define ACSB_INDETERMINATE  (1<<8)  // Internal Use
#define ACSB_ONETIME    (1<<9)      // Internal Use

//Deprecated styles.
#define ACSB_POPOUT     ACSB_INACTIVE
#define ACSB_NORMAL     ACSB_ACTIVE

class AcPane : public AcStatusBarItem
{
public:
    AcPane();
    ACAD_PORT AcPane(const CString& strId); // NEW
    virtual ~AcPane();

    virtual BOOL SetIcon(HICON hIcon);
    virtual HICON GetIcon() const;

    virtual BOOL SetText(const CString& strText);
    virtual BOOL GetText(CString& strText) const;

    virtual BOOL SetStyle(int nStyle);
    virtual int GetStyle() const;

    virtual BOOL SetMinWidth(int cxWidth);
    virtual int GetMinWidth();

    virtual BOOL SetMaxWidth(int cxWidth);
    virtual int GetMaxWidth();

    ACAD_PORT virtual BOOL SetPaneName(const CString& strName);
    ACAD_PORT virtual BOOL GetPaneName(CString& strName) const;

    ACAD_PORT virtual BOOL SetRegistryKey(const CString& strRegistryKey);
    ACAD_PORT virtual BOOL GetRegistryKey(CString& strRegistryKey) const;

    virtual UINT DisplayPopupPaneMenu(CMenu& menu);

private:
    CString m_strText;
    int     m_nStyle;
    int     m_cxMinWidth;
    int     m_cxMaxWidth;
    CString m_strName;
    CString m_strRegistryKey;
};

typedef void (*AcTrayItemAnimationCallbackFunc)(void *, int);
typedef void *AcTrayItemAnimationCallbackData;

//////////////////////////////////////////////////////////////////////////////
// Note: This class is for INTERNAL USE ONLY.  Using this class may
//       adversely affect application functionality

class AcTrayItemAnimationControl
{
public:
    SB_DEPRECATED AcTrayItemAnimationControl();
    SB_DEPRECATED AcTrayItemAnimationControl(const CString& strGIFFile);
    SB_DEPRECATED AcTrayItemAnimationControl(HBITMAP hBitmap);
    SB_DEPRECATED ~AcTrayItemAnimationControl();

    SB_DEPRECATED void SetBitmap(HBITMAP hBitmap) { m_hBitmap = hBitmap; }
    SB_DEPRECATED void SetGIFFile(const CString& strGIFFile) { m_strGIFFile = strGIFFile; }
    SB_DEPRECATED void SetGIFResourceData(HGLOBAL hGlobal, DWORD dwSize) { m_hGifGlobal = hGlobal; m_dwGifSize = dwSize; };
    SB_DEPRECATED void SetDuration(int nDurationInSeconds) { m_nDurationInSeconds = nDurationInSeconds; }
    SB_DEPRECATED void SetNewIcon(HICON hNewIcon) { m_hNewIcon = hNewIcon; }
    SB_DEPRECATED void SetCallback(AcTrayItemAnimationCallbackFunc pCallbackFunc, AcTrayItemAnimationCallbackData pCallbackData)
    {
        m_pCallbackFunc = pCallbackFunc;
        m_pCallbackData = pCallbackData;
    }

    SB_DEPRECATED HBITMAP GetBitmap() const { return m_hBitmap; };
    SB_DEPRECATED const CString& GetGIFFile() const { return m_strGIFFile; };
    SB_DEPRECATED void GetGIFResourceData(HGLOBAL &hGlobal, DWORD &dwSize) const { hGlobal = m_hGifGlobal; dwSize = m_dwGifSize;};
    SB_DEPRECATED int GetDuration() const { return m_nDurationInSeconds; }
    SB_DEPRECATED HICON GetNewIcon() const { return m_hNewIcon; };
    SB_DEPRECATED AcTrayItemAnimationCallbackFunc GetCallbackFunc() const { return m_pCallbackFunc; }
    SB_DEPRECATED AcTrayItemAnimationCallbackData GetCallbackData() const { return m_pCallbackData; }

    enum
    {
        ANIMATION_ERROR_NO_CREATE,
        ANIMATION_ERROR_NO_ICONS,
        ANIMATION_KILLED,
        ANIMATION_FINISHED,
    };

private:
    void InitDefault()
    {
        m_pCallbackFunc = 0;
        m_pCallbackData = 0;
        m_nDurationInSeconds = 5;
        m_hNewIcon = 0;
    }

    HBITMAP                         m_hBitmap;
    HGLOBAL                         m_hGifGlobal;
    DWORD                           m_dwGifSize;
    CString                         m_strGIFFile;
    int                             m_nDurationInSeconds;
    HICON                           m_hNewIcon;
    AcTrayItemAnimationCallbackFunc m_pCallbackFunc;
    AcTrayItemAnimationCallbackData m_pCallbackData;
};
// End INTERNAL USE ONLY.
//////////////////////////////////////////////////////////////////////////////

typedef void (*AcTrayItemBubbleWindowCallbackFunc)(void *, int);
typedef void *AcTrayItemBubbleWindowCallbackData;

class AcTrayItemBubbleWindowControl
{
public:
    AcTrayItemBubbleWindowControl();
    ACAD_PORT AcTrayItemBubbleWindowControl(
            const CString& strTitle,
            const CString& strText,
            const CString& strHyperText = ACRX_T(""),
            const CString& strHyperLink = ACRX_T(""),
            const CString& strText2 = ACRX_T("")
            );
    ~AcTrayItemBubbleWindowControl();

    void SetIconType(int nIconType)         { m_nIconType = nIconType; }
    void SetTitle(const CString& strTitle)  { m_strTitle = strTitle; }
    void SetText(const CString& strText)    { m_strText = strText; }
    void SetHyperText(const CString& strHyperText) { m_strHyperText = strHyperText; }
    void SetHyperLink(const CString& strHyperLink) { m_strHyperLink = strHyperLink; }
    void SetText2(const CString& strText2)  { m_strText2 = strText2; }
    void SetCallback(AcTrayItemBubbleWindowCallbackFunc pCallbackFunc, AcTrayItemBubbleWindowCallbackData pCallbackData = 0)
    {
        m_pCallbackFunc = pCallbackFunc;
        m_pCallbackData = pCallbackData;
    }

    int GetIconType() const { return m_nIconType; };
    const CString& GetTitle() const { return m_strTitle; }
    const CString& GetText() const { return m_strText; }
    const CString& GetHyperText() const { return m_strHyperText; }
    const CString& GetHyperLink() const { return m_strHyperLink; }
    const CString& GetText2() const { return m_strText2; }
    AcTrayItemBubbleWindowCallbackFunc GetCallbackFunc() const { return m_pCallbackFunc; }
    AcTrayItemBubbleWindowCallbackData GetCallbackData() const { return m_pCallbackData; }

    enum
    {
        BUBBLE_WINDOW_ICON_NONE,
        BUBBLE_WINDOW_ICON_INFORMATION,
        BUBBLE_WINDOW_ICON_CRITICAL,
        BUBBLE_WINDOW_ICON_WARNING,
    };

    enum
    {
        BUBBLE_WINDOW_ERROR_NO_CREATE,
        BUBBLE_WINDOW_ERROR_NO_ICONS,
        BUBBLE_WINDOW_ERROR_NO_NOTIFICATIONS,
        BUBBLE_WINDOW_CLOSE,
        BUBBLE_WINDOW_TIME_OUT,
        BUBBLE_WINDOW_HYPERLINK_CLICK,
        BUBBLE_WINDOW_DOCUMENT_DEACTIVATED
    };

private:
    void InitDefault()
    {
        m_pCallbackFunc = 0;
        m_pCallbackData = 0;
        m_nIconType = BUBBLE_WINDOW_ICON_INFORMATION;
    }

    int                                 m_nIconType;
    CString                             m_strTitle;
    CString                             m_strText;
    CString                             m_strHyperText;
    CString                             m_strHyperLink;
    CString                             m_strText2;
    AcTrayItemBubbleWindowCallbackFunc  m_pCallbackFunc;
    AcTrayItemBubbleWindowCallbackData  m_pCallbackData;
};

class AcRxValue;
class AcTrayItem : public AcStatusBarItem
{
public:
    AcTrayItem();
    ACAD_PORT AcTrayItem(const CString& strId);
    virtual ~AcTrayItem();

    virtual BOOL SetIcon(HICON hIcon);
    virtual HICON GetIcon() const;

	
    virtual BOOL ShowBubbleWindow(AcTrayItemBubbleWindowControl* pBubbleWindowControl);
    virtual AcTrayItemBubbleWindowControl* GetBubbleWindowControl() const;

    virtual BOOL CloseAllBubbleWindows();

    ACAD_PORT void GoToState(const CString& state, AcRxValue* parameter = NULL);

    //////////////////////////////////////////////////////////////////////////////
    // Note: These methods are for INTERNAL USE ONLY.  Using these methods may
    //       adversely affect application functionality
    SB_DEPRECATED BOOL PlayAnimation(AcTrayItemAnimationControl* pAnimationControl);
    SB_DEPRECATED void StopAnimation();
    SB_DEPRECATED AcTrayItemAnimationControl* GetAnimationControl() const;
    // End INTERNAL USE ONLY.
    //////////////////////////////////////////////////////////////////////////////


private:
    AcTrayItemAnimationControl      m_AnimationControl;
    AcTrayItemAnimationControl      *m_pAnimationControl;

    AcTrayItemBubbleWindowControl   m_BubbleWindowControl;
    AcTrayItemBubbleWindowControl   *m_pBubbleWindowControl;
};

enum AcDefaultPane
{
    ACSBPANE_APP_MODEMACRO,
    ACSBPANE_APP_CURSORCOORD,
    ACSBPANE_APP_SNAP,
    ACSBPANE_APP_GRID,
    ACSBPANE_APP_ORTHO,
    ACSBPANE_APP_POLAR,
    ACSBPANE_APP_OTRACK,
    ACSBPANE_APP_LINEWEIGHT,
    ACSBPANE_APP_PAPERMODEL,
        ACSBPANE_APP_PAPER,
        ACSBPANE_APP_MODEL,
    ACSBPANE_APP_OSNAP,
    ACSBPANE_APP_FLOAT,
    ACSBPANE_APP_TABLET,
    ACSBPANE_APP_SPACER,
    ACSBPANE_APP_VPMAX_PREV,
    ACSBPANE_APP_VPMAX,
    ACSBPANE_APP_VPMAX_NEXT,
    ACSBPANE_APP_DYNINPUT,
    ACSBPANE_APP_DYNAMICUCS,
    ACSBPANE_APP_LAYOUTMODELICONS,
        ACSBPANE_APP_MODEL_ICON,
        ACSBPANE_APP_LAYOUT_ICON,
        ACSBPANE_APP_LAYOUTMORE_ICON, // Deprecated: This define will be removed in a future release
    
    ACSBPANE_APP_ALL,
        ACSBPANE_ANNO_STRETCH,
        ACSBPANE_ANNO_AUTOSCALE,
        ACSBPANE_ANNO_VIEWPORT_SCALE_LABEL, // Deprecated: This define will be removed in a future release
        ACSBPANE_ANNO_VIEWPORT_SCALE,
        ACSBPANE_ANNO_VIEWPORT_LOCK_STATE,
        ACSBPANE_ANNO_ANNOTATION_SCALE_LABEL, // Deprecated: This define will be removed in a future release
        ACSBPANE_ANNO_ANNOTATION_SCALE,
        ACSBPANE_ANNO_ANNO_ALL_VISIBLE,
        ACSBPANE_ANNO_EMPTY,
    ACSBPANE_APP_STRETCH,
    ACSBPANE_APP_WORKSPACE,
    ACSBPANE_APP_WORKSPACE_LOCK,
    ACSBPANE_APP_QPROPERTIES,
    ACSBPANE_ANNO_SYNCHSCALES,

    ACSBPANE_APP_QV_LAYOUTS,
    ACSBPANE_APP_QV_DRAWINGS,
    ACSBPANE_APP_QV_SPACER,        // Deprecated: This define will be removed in a future release
    ACSBPANE_APP_QV_PAN,           // Deprecated: This define will be removed in a future release
    ACSBPANE_APP_QV_ZOOM,          // Deprecated: This define will be removed in a future release
    ACSBPANE_APP_QV_STEERINGWHEEL, // Deprecated: This define will be removed in a future release
    ACSBPANE_APP_QV_SHOWMOTION,    // Deprecated: This define will be removed in a future release
    ACSBPANE_APP_QV_ANNO_SPACER,
    ACSBPANE_APP_3DOSNAP,
    ACSBPANE_APP_WORKSPACE_PERFORMANCE,
    ACSBPANE_APP_SELECTIONCYCLING,

    ACSBPANE_APP_TRANSPARENCY,
    ACSBPANE_APP_INFER,
    ACSBPANE_APP_ANNOMONITOR,

    ACSBPANE_APP_SELECTION_FILTER,
    ACSBPANE_APP_GIZMO,
    ACSBPANE_APP_UNITS,
    ACSBPANE_APP_GEO_SPACER,
    ACSBPANE_APP_GEO_MARKERVISIBILITY,
    ACSBPANE_APP_GEO_COORDSYS,
    ACSBPANE_APP_ISODRAFT,
    ACSBPANE_APP_HARDWAREACCELERATION,   // It's added from AcWindows.dll

    ACSBPANE_APP_ADD_CLEANSCREEN,        // It's added from AcWindows.dll into additional panes
    ACSBPANE_APP_ADD_CUSTOMIZATION       // It's added from AcWindows.dll into additional panes
};

class AcApStatusBar
{
public:
    virtual BOOL Insert(int nIndex, AcPane* pPane, BOOL bUpdate = TRUE) = 0;
    virtual BOOL Insert(int nIndex, AcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;

    virtual BOOL Remove(AcPane* pPane, BOOL bUpdate = TRUE) = 0;
    virtual BOOL Remove(AcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;
    virtual BOOL Remove(int nIndex, BOOL bTrayItem = FALSE, BOOL bUpdate = TRUE) = 0;

    virtual BOOL RemoveAllPanes(BOOL bUpdate = TRUE) = 0;

    virtual int Add(AcPane* pPane, BOOL bUpdate = TRUE) = 0;
    virtual int Add(AcTrayItem* pTrayItem, BOOL bUpdate = TRUE) = 0;

    SB_DEPRECATED virtual void Update() = 0;

    virtual int GetIndex(AcPane* pPane) const = 0;
    virtual int GetIndex(AcTrayItem* pTrayItem) const = 0;
    virtual int GetIndex(int nID, BOOL bTrayItem = FALSE) const = 0;

    SB_DEPRECATED virtual int GetID(AcPane* pPane) const = 0;
    SB_DEPRECATED virtual int GetID(AcTrayItem* pTrayItem) const = 0;
    SB_DEPRECATED virtual int GetID(int nIndex, BOOL bTrayItem = FALSE) const = 0;

    virtual int GetPaneCount() const = 0;

    virtual AcPane* GetPane(int nIndex) = 0;

    virtual int GetTrayItemCount() const = 0;

    virtual AcTrayItem* GetTrayItem(int nIndex) = 0;

    virtual BOOL RemoveAllTrayIcons(BOOL bUpdate = TRUE) = 0;

    SB_DEPRECATED virtual BOOL ClientToScreen(LPPOINT lpPoint) = 0;
    SB_DEPRECATED virtual BOOL ClientToScreen(LPRECT lpRect) = 0;

    SB_DEPRECATED virtual BOOL ScreenToClient(LPPOINT lpPoint) = 0;
    SB_DEPRECATED virtual BOOL ScreenToClient(LPRECT lpRect) = 0;

    SB_DEPRECATED virtual int GetTextWidth(const CString& strText) const = 0;

    virtual UINT DisplayContextMenu(CMenu& menu, CPoint point) = 0;
    virtual UINT DisplayPopupPaneMenu(AcPane* pPane, CMenu& menu) = 0;

    SB_DEPRECATED virtual BOOL GetTraySettingsShowIcons() const = 0;
    SB_DEPRECATED virtual BOOL GetTraySettingsShowNotifications() const = 0;

    SB_DEPRECATED virtual void ShowStatusBarMenuIcon(BOOL bShow) = 0;

    SB_DEPRECATED virtual BOOL SetStatusBarMenuItem(AcPane* pPane) = 0;

    SB_DEPRECATED virtual void ShowCleanScreenIcon(BOOL bShow) = 0;
    SB_DEPRECATED virtual BOOL RemoveCleanScreenIcon() = 0;

    SB_DEPRECATED virtual BOOL ShowTraySettingsDialog() = 0;

    SB_DEPRECATED virtual AcPane* GetDefaultPane(AcDefaultPane nPane) = 0;
    SB_DEPRECATED virtual BOOL RemoveDefaultPane(AcDefaultPane nPane, BOOL bUpdate = TRUE) = 0;

    virtual BOOL CloseAllBubbleWindows(AcTrayItem* pTrayItem) = 0;

};

class AcStatusBarMenuItem
{
public:

    enum AcStatusBarType {
        kApplicationStatusBar  = 0,
        kDrawingStatusBar = 1
    };

    SB_DEPRECATED AcStatusBarMenuItem();
    SB_DEPRECATED virtual ~AcStatusBarMenuItem();

    SB_DEPRECATED virtual BOOL    CustomizeMenu       (AcStatusBarType nType,
                                         CMenu* pMenu,
                                         UINT nStartCmdId,
                                         UINT nEndCmdId);

    SB_DEPRECATED virtual BOOL    InvokeMenuCommand   (AcStatusBarType nType,
                                         UINT nCmdId);
};

#pragma pack (pop)
#endif // ACSTATUSBAR_H

