///////////////////////////////////////////////////////////////////////////////
// Name:        wx/aui/framemanager.h
// Purpose:     wxaui: wx advanced user interface - docking window manager
// Author:      Benjamin I. Williams
// Modified by:
// Created:     2005-05-17
// Copyright:   (C) Copyright 2005, Kirix Corporation, All Rights Reserved.
// Licence:     wxWindows Library Licence, Version 3.1
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_FRAMEMANAGER_H_
#  define _WX_FRAMEMANAGER_H_
// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#  include "wx/defs.h"
#  if  wxUSE_AUI
#    include "wx/dynarray.h"
#    include "wx/gdicmn.h"
#    include "wx/window.h"
#    include "wx/timer.h"
#    include "wx/sizer.h"
#    include "wx/bitmap.h"
enum wxAuiManagerDock {
    wxAUI_DOCK_NONE = 0,
    wxAUI_DOCK_TOP = 1,
    wxAUI_DOCK_RIGHT = 2,
    wxAUI_DOCK_BOTTOM = 3,
    wxAUI_DOCK_LEFT = 4,
    wxAUI_DOCK_CENTER = 5,
    wxAUI_DOCK_CENTRE = wxAUI_DOCK_CENTER
};
enum wxAuiManagerOption {
    wxAUI_MGR_ALLOW_FLOATING           = 1 << 0,
    wxAUI_MGR_ALLOW_ACTIVE_PANE        = 1 << 1,
    wxAUI_MGR_TRANSPARENT_DRAG         = 1 << 2,
    wxAUI_MGR_TRANSPARENT_HINT         = 1 << 3,
    wxAUI_MGR_VENETIAN_BLINDS_HINT     = 1 << 4,
    wxAUI_MGR_RECTANGLE_HINT           = 1 << 5,
    wxAUI_MGR_HINT_FADE                = 1 << 6,
    wxAUI_MGR_NO_VENETIAN_BLINDS_FADE  = 1 << 7,
    wxAUI_MGR_LIVE_RESIZE              = 1 << 8,

    wxAUI_MGR_DEFAULT = wxAUI_MGR_ALLOW_FLOATING |
                        wxAUI_MGR_TRANSPARENT_HINT |
                        wxAUI_MGR_HINT_FADE |
                        wxAUI_MGR_NO_VENETIAN_BLINDS_FADE
};
enum wxAuiPaneDockArtSetting {
    wxAUI_DOCKART_SASH_SIZE = 0,
    wxAUI_DOCKART_CAPTION_SIZE = 1,
    wxAUI_DOCKART_GRIPPER_SIZE = 2,
    wxAUI_DOCKART_PANE_BORDER_SIZE = 3,
    wxAUI_DOCKART_PANE_BUTTON_SIZE = 4,
    wxAUI_DOCKART_BACKGROUND_COLOUR = 5,
    wxAUI_DOCKART_SASH_COLOUR = 6,
    wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR = 7,
    wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR = 8,
    wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR = 9,
    wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR = 10,
    wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR = 11,
    wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR = 12,
    wxAUI_DOCKART_BORDER_COLOUR = 13,
    wxAUI_DOCKART_GRIPPER_COLOUR = 14,
    wxAUI_DOCKART_CAPTION_FONT = 15,
    wxAUI_DOCKART_GRADIENT_TYPE = 16
};
enum wxAuiPaneDockArtGradients {
    wxAUI_GRADIENT_NONE = 0,
    wxAUI_GRADIENT_VERTICAL = 1,
    wxAUI_GRADIENT_HORIZONTAL = 2
};
enum wxAuiPaneButtonState {
    wxAUI_BUTTON_STATE_NORMAL   = 0,
    wxAUI_BUTTON_STATE_HOVER    = 1 << 1,
    wxAUI_BUTTON_STATE_PRESSED  = 1 << 2,
    wxAUI_BUTTON_STATE_DISABLED = 1 << 3,
    wxAUI_BUTTON_STATE_HIDDEN   = 1 << 4,
    wxAUI_BUTTON_STATE_CHECKED  = 1 << 5
};
enum wxAuiButtonId {
    wxAUI_BUTTON_CLOSE = 101,
    wxAUI_BUTTON_MAXIMIZE_RESTORE = 102,
    wxAUI_BUTTON_MINIMIZE = 103,
    wxAUI_BUTTON_PIN = 104,
    wxAUI_BUTTON_OPTIONS = 105,
    wxAUI_BUTTON_WINDOWLIST = 106,
    wxAUI_BUTTON_LEFT = 107,
    wxAUI_BUTTON_RIGHT = 108,
    wxAUI_BUTTON_UP = 109,
    wxAUI_BUTTON_DOWN = 110,
    wxAUI_BUTTON_CUSTOM1 = 201,
    wxAUI_BUTTON_CUSTOM2 = 202,
    wxAUI_BUTTON_CUSTOM3 = 203
};
enum wxAuiPaneInsertLevel {
    wxAUI_INSERT_PANE = 0,
    wxAUI_INSERT_ROW = 1,
    wxAUI_INSERT_DOCK = 2
};
// forwards and array declarations
class wxAuiDockUIPart;
class wxAuiPaneInfo;
class wxAuiDockInfo;
class wxAuiDockArt;
class wxAuiManagerEvent;
WX_DECLARE_USER_EXPORTED_OBJARRAY(wxAuiDockInfo, wxAuiDockInfoArray, WXDLLIMPEXP_AUI);
WX_DECLARE_USER_EXPORTED_OBJARRAY(wxAuiDockUIPart, wxAuiDockUIPartArray, WXDLLIMPEXP_AUI);
WX_DECLARE_USER_EXPORTED_OBJARRAY(wxAuiPaneInfo, wxAuiPaneInfoArray, WXDLLIMPEXP_AUI);
WX_DEFINE_USER_EXPORTED_ARRAY_PTR(wxAuiPaneInfo*, wxAuiPaneInfoPtrArray, class WXDLLIMPEXP_AUI);
WX_DEFINE_USER_EXPORTED_ARRAY_PTR(wxAuiDockInfo*, wxAuiDockInfoPtrArray, class WXDLLIMPEXP_AUI);
WXDLLIMPEXP_AUI extern wxAuiDockInfo wxAuiNullDockInfo;
WXDLLIMPEXP_AUI extern wxAuiPaneInfo wxAuiNullPaneInfo;
class WXDLLIMPEXP_AUI wxAuiPaneInfo
{
public:
  wxAuiPaneInfo()
    : best_size(wxDefaultSize)
    , min_size(wxDefaultSize)
    , max_size(wxDefaultSize)
    , floating_pos(wxDefaultPosition)
    , floating_size(wxDefaultSize)
  {
    window = NULL;
    frame = NULL;
    state = 0;
    dock_direction = wxAUI_DOCK_LEFT;
    dock_layer = 0;
    dock_row = 0;
    dock_pos = 0;
    dock_proportion = 0;
    DefaultPane();
  }
  ~wxAuiPaneInfo()
  {
  }
    // Write the safe parts of a newly loaded PaneInfo structure "source" into "this"
    // used on loading perspectives etc.
  void SafeSet(wxAuiPaneInfo source)
  {
        // note source is not passed by reference so we can overwrite, to keep the
        // unsafe bits of "dest"
    source.window = window;
    source.frame = frame;
    wxCHECK_RET(source.IsValid(), "window settings and pane settings are incompatible");
        // now assign
    *this = source;
  }
  bool IsOk() const
  {
    return window != NULL;
  }
  bool IsFixed() const
  {
    return !HasFlag(optionResizable);
  }
  bool IsResizable() const
  {
    return HasFlag(optionResizable);
  }
  bool IsShown() const
  {
    return !HasFlag(optionHidden);
  }
  bool IsFloating() const
  {
    return HasFlag(optionFloating);
  }
  bool IsDocked() const
  {
    return !HasFlag(optionFloating);
  }
  bool IsToolbar() const
  {
    return HasFlag(optionToolbar);
  }
  bool IsTopDockable() const
  {
    return HasFlag(optionTopDockable);
  }
  bool IsBottomDockable() const
  {
    return HasFlag(optionBottomDockable);
  }
  bool IsLeftDockable() const
  {
    return HasFlag(optionLeftDockable);
  }
  bool IsRightDockable() const
  {
    return HasFlag(optionRightDockable);
  }
  bool IsDockable() const
  {
    return HasFlag(optionTopDockable | optionBottomDockable | optionLeftDockable | optionRightDockable);
  }
  bool IsFloatable() const
  {
    return HasFlag(optionFloatable);
  }
  bool IsMovable() const
  {
    return HasFlag(optionMovable);
  }
  bool IsDestroyOnClose() const
  {
    return HasFlag(optionDestroyOnClose);
  }
  bool IsMaximized() const
  {
    return HasFlag(optionMaximized);
  }
  bool HasCaption() const
  {
    return HasFlag(optionCaption);
  }
  bool HasGripper() const
  {
    return HasFlag(optionGripper);
  }
  bool HasBorder() const
  {
    return HasFlag(optionPaneBorder);
  }
  bool HasCloseButton() const
  {
    return HasFlag(buttonClose);
  }
  bool HasMaximizeButton() const
  {
    return HasFlag(buttonMaximize);
  }
  bool HasMinimizeButton() const
  {
    return HasFlag(buttonMinimize);
  }
  bool HasPinButton() const
  {
    return HasFlag(buttonPin);
  }
  bool HasGripperTop() const
  {
    return HasFlag(optionGripperTop);
  }
  wxAuiPaneInfo& Window(wxWindow* w)
  {
    wxAuiPaneInfo test(*this);
    test.window = w;
    wxCHECK_MSG(test.IsValid(), *this,
                    "window settings and pane settings are incompatible");
    *this = test;
    return *this;
  }
  wxAuiPaneInfo& Name(const wxString& n)
  {
    name = n;
    return *this;
  }
  wxAuiPaneInfo& Caption(const wxString& c)
  {
    caption = c;
    return *this;
  }
  wxAuiPaneInfo& Icon(const wxBitmap& b)
  {
    icon = b;
    return *this;
  }
  wxAuiPaneInfo& Left()
  {
    dock_direction = wxAUI_DOCK_LEFT;
    return *this;
  }
  wxAuiPaneInfo& Right()
  {
    dock_direction = wxAUI_DOCK_RIGHT;
    return *this;
  }
  wxAuiPaneInfo& Top()
  {
    dock_direction = wxAUI_DOCK_TOP;
    return *this;
  }
  wxAuiPaneInfo& Bottom()
  {
    dock_direction = wxAUI_DOCK_BOTTOM;
    return *this;
  }
  wxAuiPaneInfo& Center()
  {
    dock_direction = wxAUI_DOCK_CENTER;
    return *this;
  }
  wxAuiPaneInfo& Centre()
  {
    dock_direction = wxAUI_DOCK_CENTRE;
    return *this;
  }
  wxAuiPaneInfo& Direction(int direction)
  {
    dock_direction = direction;
    return *this;
  }
  wxAuiPaneInfo& Layer(int layer)
  {
    dock_layer = layer;
    return *this;
  }
  wxAuiPaneInfo& Row(int row)
  {
    dock_row = row;
    return *this;
  }
  wxAuiPaneInfo& Position(int pos)
  {
    dock_pos = pos;
    return *this;
  }
  wxAuiPaneInfo& BestSize(const wxSize& size)
  {
    best_size = size;
    return *this;
  }
  wxAuiPaneInfo& MinSize(const wxSize& size)
  {
    min_size = size;
    return *this;
  }
  wxAuiPaneInfo& MaxSize(const wxSize& size)
  {
    max_size = size;
    return *this;
  }
  wxAuiPaneInfo& BestSize(int x, int y)
  {
    best_size.Set(x, y);
    return *this;
  }
  wxAuiPaneInfo& MinSize(int x, int y)
  {
    min_size.Set(x, y);
    return *this;
  }
  wxAuiPaneInfo& MaxSize(int x, int y)
  {
    max_size.Set(x, y);
    return *this;
  }
  wxAuiPaneInfo& FloatingPosition(const wxPoint& pos)
  {
    floating_pos = pos;
    return *this;
  }
  wxAuiPaneInfo& FloatingPosition(int x, int y)
  {
    floating_pos.x = x;
    floating_pos.y = y;
    return *this;
  }
  wxAuiPaneInfo& FloatingSize(const wxSize& size)
  {
    floating_size = size;
    return *this;
  }
  wxAuiPaneInfo& FloatingSize(int x, int y)
  {
    floating_size.Set(x, y);
    return *this;
  }
  wxAuiPaneInfo& Fixed()
  {
    return SetFlag(optionResizable, false);
  }
  wxAuiPaneInfo& Resizable(bool resizable = true)
  {
    return SetFlag(optionResizable, resizable);
  }
  wxAuiPaneInfo& Dock()
  {
    return SetFlag(optionFloating, false);
  }
  wxAuiPaneInfo& Float()
  {
    return SetFlag(optionFloating, true);
  }
  wxAuiPaneInfo& Hide()
  {
    return SetFlag(optionHidden, true);
  }
  wxAuiPaneInfo& Show(bool show = true)
  {
    return SetFlag(optionHidden, !show);
  }
  wxAuiPaneInfo& CaptionVisible(bool visible = true)
  {
    return SetFlag(optionCaption, visible);
  }
  wxAuiPaneInfo& Maximize()
  {
    return SetFlag(optionMaximized, true);
  }
  wxAuiPaneInfo& Restore()
  {
    return SetFlag(optionMaximized, false);
  }
  wxAuiPaneInfo& PaneBorder(bool visible = true)
  {
    return SetFlag(optionPaneBorder, visible);
  }
  wxAuiPaneInfo& Gripper(bool visible = true)
  {
    return SetFlag(optionGripper, visible);
  }
  wxAuiPaneInfo& GripperTop(bool attop = true)
  {
    return SetFlag(optionGripperTop, attop);
  }
  wxAuiPaneInfo& CloseButton(bool visible = true)
  {
    return SetFlag(buttonClose, visible);
  }
  wxAuiPaneInfo& MaximizeButton(bool visible = true)
  {
    return SetFlag(buttonMaximize, visible);
  }
  wxAuiPaneInfo& MinimizeButton(bool visible = true)
  {
    return SetFlag(buttonMinimize, visible);
  }
  wxAuiPaneInfo& PinButton(bool visible = true)
  {
    return SetFlag(buttonPin, visible);
  }
  wxAuiPaneInfo& DestroyOnClose(bool b = true)
  {
    return SetFlag(optionDestroyOnClose, b);
  }
  wxAuiPaneInfo& TopDockable(bool b = true)
  {
    return SetFlag(optionTopDockable, b);
  }
  wxAuiPaneInfo& BottomDockable(bool b = true)
  {
    return SetFlag(optionBottomDockable, b);
  }
  wxAuiPaneInfo& LeftDockable(bool b = true)
  {
    return SetFlag(optionLeftDockable, b);
  }
  wxAuiPaneInfo& RightDockable(bool b = true)
  {
    return SetFlag(optionRightDockable, b);
  }
  wxAuiPaneInfo& Floatable(bool b = true)
  {
    return SetFlag(optionFloatable, b);
  }
  wxAuiPaneInfo& Movable(bool b = true)
  {
    return SetFlag(optionMovable, b);
  }
  wxAuiPaneInfo& DockFixed(bool b = true)
  {
    return SetFlag(optionDockFixed, b);
  }
  wxAuiPaneInfo& Dockable(bool b = true)
  {
    return TopDockable(b).BottomDockable(b).LeftDockable(b).RightDockable(b);
  }
  wxAuiPaneInfo& DefaultPane()
  {
    wxAuiPaneInfo test(*this);
    test.state |= optionTopDockable | optionBottomDockable | optionLeftDockable | optionRightDockable | optionFloatable | optionMovable | optionResizable | optionCaption | optionPaneBorder | buttonClose;
    wxCHECK_MSG(test.IsValid(), *this,
                    "window settings and pane settings are incompatible");
    *this = test;
    return *this;
  }
  wxAuiPaneInfo& CentrePane()
  {
    return CenterPane();
  }
  wxAuiPaneInfo& CenterPane()
  {
    state = 0;
    return Center().PaneBorder().Resizable();
  }
  wxAuiPaneInfo& ToolbarPane()
  {
    DefaultPane();
    state |= (optionToolbar | optionGripper);
    state &= ~(optionResizable | optionCaption);
    if (dock_layer == 0)
    {
      dock_layer = 10;
    }
    return *this;
  }
  wxAuiPaneInfo& SetFlag(int flag, bool option_state)
  {
    wxAuiPaneInfo test(*this);
    if (option_state)
    {
      test.state |= flag;
    }
    else 
    {
      test.state &= ~flag;
    }
    wxCHECK_MSG(test.IsValid(), *this,
                    "window settings and pane settings are incompatible");
    *this = test;
    return *this;
  }
  bool HasFlag(int flag) const
  {
    return (state & flag) != 0;
  }
public:
    // NOTE: You can add and subtract flags from this list,
    // but do not change the values of the flags, because
    // they are stored in a binary integer format in the
    // perspective string.  If you really need to change the
    // values around, you'll have to ensure backwards-compatibility
    // in the perspective loading code.
  enum wxAuiPaneState {
        optionFloating        = 1 << 0,
        optionHidden          = 1 << 1,
        optionLeftDockable    = 1 << 2,
        optionRightDockable   = 1 << 3,
        optionTopDockable     = 1 << 4,
        optionBottomDockable  = 1 << 5,
        optionFloatable       = 1 << 6,
        optionMovable         = 1 << 7,
        optionResizable       = 1 << 8,
        optionPaneBorder      = 1 << 9,
        optionCaption         = 1 << 10,
        optionGripper         = 1 << 11,
        optionDestroyOnClose  = 1 << 12,
        optionToolbar         = 1 << 13,
        optionActive          = 1 << 14,
        optionGripperTop      = 1 << 15,
        optionMaximized       = 1 << 16,
        optionDockFixed       = 1 << 17,

        buttonClose           = 1 << 21,
        buttonMaximize        = 1 << 22,
        buttonMinimize        = 1 << 23,
        buttonPin             = 1 << 24,

        buttonCustom1         = 1 << 26,
        buttonCustom2         = 1 << 27,
        buttonCustom3         = 1 << 28,

        savedHiddenState      = 1 << 30, // used internally
        actionPane            = 1u << 31  // used internally
  };
public:
  wxString name;
  wxString caption;
  wxBitmap icon;
  wxWindow* window;
  wxFrame* frame;
  unsigned int state;
  int dock_direction;
  int dock_layer;
  int dock_row;
  int dock_pos;
  wxSize best_size;
  wxSize min_size;
  wxSize max_size;
  wxPoint floating_pos;
  wxSize floating_size;
  int dock_proportion;
  wxRect rect;
  bool IsValid() const;
};
class WXDLLIMPEXP_FWD_AUI wxAuiFloatingFrame;
class WXDLLIMPEXP_AUI wxAuiManager : public wxEvtHandler
{
  friend class wxAuiFloatingFrame;
public:
  wxAuiManager(wxWindow* managedWnd = NULL, unsigned int flags = wxAUI_MGR_DEFAULT);
  virtual ~wxAuiManager();
  void UnInit();
  void SetFlags(unsigned int flags);
  unsigned int GetFlags() const;
  static bool AlwaysUsesLiveResize();
  bool HasLiveResize() const;
  void SetManagedWindow(wxWindow* managedWnd);
  wxWindow* GetManagedWindow() const;
  static wxAuiManager* GetManager(wxWindow* window);
  void SetArtProvider(wxAuiDockArt* artProvider);
  wxAuiDockArt* GetArtProvider() const;
  wxAuiPaneInfo& GetPane(wxWindow* window);
  wxAuiPaneInfo& GetPane(const wxString& name);
  wxAuiPaneInfoArray& GetAllPanes();
  bool AddPane(wxWindow* window, const wxAuiPaneInfo& paneInfo);
  bool AddPane(wxWindow* window, const wxAuiPaneInfo& paneInfo, const wxPoint& dropPos);
  bool AddPane(wxWindow* window, int direction = wxLEFT, const wxString& caption = wxEmptyString);
  bool InsertPane(wxWindow* window, const wxAuiPaneInfo& insertLocation, int insertLevel = wxAUI_INSERT_PANE);
  bool DetachPane(wxWindow* window);
  void Update();
  wxString SavePaneInfo(const wxAuiPaneInfo& pane);
  void LoadPaneInfo(wxString panePart, wxAuiPaneInfo& pane);
  wxString SavePerspective();
  bool LoadPerspective(const wxString& perspective, bool update = true);
  void SetDockSizeConstraint(double widthPct, double heightPct);
  void GetDockSizeConstraint(double* widthPct, double* heightPct) const;
  void ClosePane(wxAuiPaneInfo& paneInfo);
  void MaximizePane(wxAuiPaneInfo& paneInfo);
  void RestorePane(wxAuiPaneInfo& paneInfo);
  void RestoreMaximizedPane();
public:
  virtual wxAuiFloatingFrame* CreateFloatingFrame(wxWindow* parent, const wxAuiPaneInfo& p);
  virtual bool CanDockPanel(const wxAuiPaneInfo& p);
  void StartPaneDrag(wxWindow* paneWindow, const wxPoint& offset);
  wxRect CalculateHintRect(wxWindow* paneWindow, const wxPoint& pt, const wxPoint& offset);
  void DrawHintRect(wxWindow* paneWindow, const wxPoint& pt, const wxPoint& offset);
  virtual void ShowHint(const wxRect& rect);
  virtual void HideHint();
  void OnHintActivate(wxActivateEvent& event);
public:
    // deprecated -- please use SetManagedWindow() and
    // and GetManagedWindow() instead
protected:
  void UpdateHintWindowConfig();
  void DoFrameLayout();
  void LayoutAddPane(wxSizer* container, wxAuiDockInfo& dock, wxAuiPaneInfo& pane, wxAuiDockUIPartArray& uiparts, bool spacerOnly);
  void LayoutAddDock(wxSizer* container, wxAuiDockInfo& dock, wxAuiDockUIPartArray& uiParts, bool spacerOnly);
  wxSizer* LayoutAll(wxAuiPaneInfoArray& panes, wxAuiDockInfoArray& docks, wxAuiDockUIPartArray& uiParts, bool spacerOnly = false);
  virtual bool ProcessDockResult(wxAuiPaneInfo& target, const wxAuiPaneInfo& newPos);
  bool DoDrop(wxAuiDockInfoArray& docks, wxAuiPaneInfoArray& panes, wxAuiPaneInfo& drop, const wxPoint& pt, const wxPoint& actionOffset = wxPoint(0, 0));
  wxAuiDockUIPart* HitTest(int x, int y);
  wxAuiDockUIPart* GetPanePart(wxWindow* pane);
  int GetDockPixelOffset(wxAuiPaneInfo& test);
  void OnFloatingPaneMoveStart(wxWindow* window);
  void OnFloatingPaneMoving(wxWindow* window, wxDirection dir);
  void OnFloatingPaneMoved(wxWindow* window, wxDirection dir);
  void OnFloatingPaneActivated(wxWindow* window);
  void OnFloatingPaneClosed(wxWindow* window, wxCloseEvent& evt);
  void OnFloatingPaneResized(wxWindow* window, const wxRect& rect);
  void Render(wxDC* dc);
  void Repaint(wxDC* dc = NULL);
  void ProcessMgrEvent(wxAuiManagerEvent& event);
  void UpdateButtonOnScreen(wxAuiDockUIPart* buttonUiPart, const wxMouseEvent& event);
  void GetPanePositionsAndSizes(wxAuiDockInfo& dock, wxArrayInt& positions, wxArrayInt& sizes);
    /// Ends a resize action, or for live update, resizes the sash
  bool DoEndResizeAction(wxMouseEvent& event);
  void SetActivePane(wxWindow* active_pane);
public:
    // public events (which can be invoked externally)
  void OnRender(wxAuiManagerEvent& evt);
  void OnPaneButton(wxAuiManagerEvent& evt);
protected:
    // protected events
  void OnDestroy(wxWindowDestroyEvent& evt);
  void OnPaint(wxPaintEvent& evt);
  void OnEraseBackground(wxEraseEvent& evt);
  void OnSize(wxSizeEvent& evt);
  void OnSetCursor(wxSetCursorEvent& evt);
  void OnLeftDown(wxMouseEvent& evt);
  void OnLeftUp(wxMouseEvent& evt);
  void OnMotion(wxMouseEvent& evt);
  void OnCaptureLost(wxMouseCaptureLostEvent& evt);
  void OnLeaveWindow(wxMouseEvent& evt);
  void OnChildFocus(wxChildFocusEvent& evt);
  void OnHintFadeTimer(wxTimerEvent& evt);
  void OnFindManager(wxAuiManagerEvent& evt);
  void OnSysColourChanged(wxSysColourChangedEvent& event);
protected:
  enum
  {
    actionNone = 0,
    actionResize,
    actionClickButton,
    actionClickCaption,
    actionDragToolbarPane,
    actionDragFloatingPane,
  };
protected:
  wxWindow* m_frame;
  wxAuiDockArt* m_art;
  unsigned int m_flags;
  wxAuiPaneInfoArray m_panes;
  wxAuiDockInfoArray m_docks;
  wxAuiDockUIPartArray m_uiParts;
  int m_action;
  wxPoint m_actionStart;
  wxPoint m_actionOffset;
  wxAuiDockUIPart* m_actionPart;
  wxWindow* m_actionWindow;
  wxRect m_actionHintRect;
  wxRect m_lastRect;
  wxAuiDockUIPart* m_hoverButton;
  wxRect m_lastHint;
  wxPoint m_lastMouseMove;
  int m_currentDragItem;
  bool m_skipping;
  bool m_hasMaximized;
  double m_dockConstraintX;
  double m_dockConstraintY;
  wxFrame* m_hintWnd;
  wxTimer m_hintFadeTimer;
  wxByte m_hintFadeAmt;
  wxByte m_hintFadeMax;
  void* m_reserved;
  wxDECLARE_EVENT_TABLE();
  wxDECLARE_CLASS(wxAuiManager);
};
// event declarations/classes
class WXDLLIMPEXP_AUI wxAuiManagerEvent : public wxEvent
{
public:
  wxAuiManagerEvent(wxEventType type = wxEVT_NULL)
    : wxEvent(0, type)
  {
    manager = NULL;
    pane = NULL;
    button = 0;
    veto_flag = false;
    canveto_flag = true;
    dc = NULL;
  }
  wxEvent* Clone() const override
  {
    return new wxAuiManagerEvent(*this);
  }
  void SetManager(wxAuiManager* mgr)
  {
    manager = mgr;
  }
  void SetPane(wxAuiPaneInfo* p)
  {
    pane = p;
  }
  void SetButton(int b)
  {
    button = b;
  }
  void SetDC(wxDC* pdc)
  {
    dc = pdc;
  }
  wxAuiManager* GetManager() const
  {
    return manager;
  }
  wxAuiPaneInfo* GetPane() const
  {
    return pane;
  }
  int GetButton() const
  {
    return button;
  }
  wxDC* GetDC() const
  {
    return dc;
  }
  void Veto(bool veto = true)
  {
    veto_flag = veto;
  }
  bool GetVeto() const
  {
    return veto_flag;
  }
  void SetCanVeto(bool can_veto)
  {
    canveto_flag = can_veto;
  }
  bool CanVeto() const
  {
    return canveto_flag && veto_flag;
  }
public:
  wxAuiManager* manager;
  wxAuiPaneInfo* pane;
  int button;
  bool veto_flag;
  bool canveto_flag;
  wxDC* dc;
private:
  wxDECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxAuiManagerEvent);
};
class WXDLLIMPEXP_AUI wxAuiDockInfo
{
public:
  wxAuiDockInfo()
  {
    dock_direction = 0;
    dock_layer = 0;
    dock_row = 0;
    size = 0;
    min_size = 0;
    resizable = true;
    fixed = false;
    toolbar = false;
    reserved1 = false;
  }
  bool IsOk() const
  {
    return dock_direction != 0;
  }
  bool IsHorizontal() const
  {
    return dock_direction == wxAUI_DOCK_TOP || dock_direction == wxAUI_DOCK_BOTTOM;
  }
  bool IsVertical() const
  {
    return dock_direction == wxAUI_DOCK_LEFT || dock_direction == wxAUI_DOCK_RIGHT || dock_direction == wxAUI_DOCK_CENTER;
  }
public:
  wxAuiPaneInfoPtrArray panes;
  wxRect rect;
  int dock_direction;
  int dock_layer;
  int dock_row;
  int size;
  int min_size;
  bool resizable;
  bool toolbar;
  bool fixed;
                              // absolute coordinates as opposed to proportional
  bool reserved1;
};
class WXDLLIMPEXP_AUI wxAuiDockUIPart
{
public:
  enum
  {
    typeCaption,
    typeGripper,
    typeDock,
    typeDockSizer,
    typePane,
    typePaneSizer,
    typeBackground,
    typePaneBorder,
    typePaneButton,
  };
  int type;
  int orientation;
  wxAuiDockInfo* dock;
  wxAuiPaneInfo* pane;
  int button;
  wxSizer* cont_sizer;
  wxSizerItem* sizer_item;
  wxRect rect;
};
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_AUI, wxEVT_AUI_PANE_BUTTON, wxAuiManagerEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_AUI, wxEVT_AUI_PANE_CLOSE, wxAuiManagerEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_AUI, wxEVT_AUI_PANE_MAXIMIZE, wxAuiManagerEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_AUI, wxEVT_AUI_PANE_RESTORE, wxAuiManagerEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_AUI, wxEVT_AUI_PANE_ACTIVATED, wxAuiManagerEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_AUI, wxEVT_AUI_RENDER, wxAuiManagerEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_AUI, wxEVT_AUI_FIND_MANAGER, wxAuiManagerEvent );
typedef void (*wxAuiManagerEventFunction) (wxAuiManagerEvent&);
#    define wxAuiManagerEventHandler(func)	 \
    wxEVENT_HANDLER_CAST(wxAuiManagerEventFunction, func)
#    define EVT_AUI_PANE_BUTTON(func)	 \
   wx__DECLARE_EVT0(wxEVT_AUI_PANE_BUTTON, wxAuiManagerEventHandler(func))
#    define EVT_AUI_PANE_CLOSE(func)	 \
   wx__DECLARE_EVT0(wxEVT_AUI_PANE_CLOSE, wxAuiManagerEventHandler(func))
#    define EVT_AUI_PANE_MAXIMIZE(func)	 \
   wx__DECLARE_EVT0(wxEVT_AUI_PANE_MAXIMIZE, wxAuiManagerEventHandler(func))
#    define EVT_AUI_PANE_RESTORE(func)	 \
   wx__DECLARE_EVT0(wxEVT_AUI_PANE_RESTORE, wxAuiManagerEventHandler(func))
#    define EVT_AUI_PANE_ACTIVATED(func)	 \
   wx__DECLARE_EVT0(wxEVT_AUI_PANE_ACTIVATED, wxAuiManagerEventHandler(func))
#    define EVT_AUI_RENDER(func)	 \
   wx__DECLARE_EVT0(wxEVT_AUI_RENDER, wxAuiManagerEventHandler(func))
#    define EVT_AUI_FIND_MANAGER(func)	 \
   wx__DECLARE_EVT0(wxEVT_AUI_FIND_MANAGER, wxAuiManagerEventHandler(func))
#  endif
#endif
