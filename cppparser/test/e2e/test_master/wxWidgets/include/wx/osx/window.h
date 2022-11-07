/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/window.h
// Purpose:     wxWindowMac class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_WINDOW_H_
#  define _WX_WINDOW_H_
#  include "wx/brush.h"
#  include "wx/dc.h"
class WXDLLIMPEXP_FWD_CORE wxButton;
class WXDLLIMPEXP_FWD_CORE wxScrollBar;
class WXDLLIMPEXP_FWD_CORE wxPanel;
class WXDLLIMPEXP_FWD_CORE wxNonOwnedWindow;
#  if  wxOSX_USE_COCOA_OR_IPHONE
class WXDLLIMPEXP_FWD_CORE wxWidgetImpl;
typedef wxWidgetImpl wxOSXWidgetImpl;
#  endif
class WXDLLIMPEXP_CORE wxWindowMac : public wxWindowBase
{
  wxDECLARE_DYNAMIC_CLASS(wxWindowMac);
  friend class wxDC;
  friend class wxPaintDC;
public:
  wxWindowMac();
  wxWindowMac(wxWindowMac* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxPanelNameStr));
  virtual ~wxWindowMac();
  bool Create(wxWindowMac* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxPanelNameStr));
  void SendSizeEvent(int flags = 0) override;
    // implement base class pure virtuals
  void SetLabel(const wxString& label) override;
  wxString GetLabel() const override;
  void Raise() override;
  void Lower() override;
  bool Show(bool show = true) override;
  bool ShowWithEffect(wxShowEffect effect, unsigned timeout = 0) override
  {
    return OSXShowWithEffect(true, effect, timeout);
  }
  bool HideWithEffect(wxShowEffect effect, unsigned timeout = 0) override
  {
    return OSXShowWithEffect(false, effect, timeout);
  }
  void SetFocus() override;
  void WarpPointer(int x, int y) override;
  bool EnableTouchEvents(int eventsMask) override;
  void Refresh(bool eraseBackground = true, const wxRect* rect = NULL) override;
  void Update() override;
  void ClearBackground() override;
  bool SetCursor(const wxCursor& cursor) override;
  bool SetFont(const wxFont& font) override;
  bool SetBackgroundColour(const wxColour& colour) override;
  bool SetForegroundColour(const wxColour& colour) override;
  bool SetBackgroundStyle(wxBackgroundStyle style) override;
  bool IsTransparentBackgroundSupported(wxString* reason = NULL) const override;
  int GetCharHeight() const override;
  int GetCharWidth() const override;
  void SetScrollbar(int orient, int pos, int thumbVisible, int range, bool refresh = true) override;
  void SetScrollPos(int orient, int pos, bool refresh = true) override;
  int GetScrollPos(int orient) const override;
  int GetScrollThumb(int orient) const override;
  int GetScrollRange(int orient) const override;
  void ScrollWindow(int dx, int dy, const wxRect* rect = NULL) override;
  void AlwaysShowScrollbars(bool horz = true, bool vert = true) override;
  bool IsScrollbarAlwaysShown(int orient) const override
  {
    return orient == wxHORIZONTAL ? m_hScrollBarAlwaysShown : m_vScrollBarAlwaysShown;
  }
  bool Reparent(wxWindowBase* newParent) override;
#  if  wxUSE_HOTKEY && wxOSX_USE_COCOA_OR_CARBON
    // hot keys (system wide accelerators)
    // -----------------------------------
  bool RegisterHotKey(int hotkeyId, int modifiers, int keycode) override;
  bool UnregisterHotKey(int hotkeyId) override;
#  endif
  wxSize GetDPI() const override;
  double GetDPIScaleFactor() const override;
  void SetDropTarget(wxDropTarget* dropTarget) override;
    // implementation from now on
    // --------------------------
  void MacClientToRootWindow(int* x, int* y) const;
  void MacWindowToRootWindow(int* x, int* y) const;
  void MacRootWindowToWindow(int* x, int* y) const;
  virtual wxString MacGetToolTipString(wxPoint& where);
    // simple accessors
    // ----------------
  WXWidget GetHandle() const override;
  bool SetTransparent(wxByte alpha) override;
  bool CanSetTransparent() override;
  virtual wxByte GetTransparent() const;
    // event handlers
    // --------------
  void OnMouseEvent(wxMouseEvent& event);
  void OnDPIChanged(wxDPIChangedEvent& event);
  void MacOnScroll(wxScrollEvent& event);
  bool AcceptsFocus() const override;
  void EnableVisibleFocus(bool enabled) override;
  bool IsDoubleBuffered() const override
  {
    return true;
  }
  static long MacRemoveBordersFromStyle(long style);
    // For implementation purposes:
    // sometimes decorations make the client area smaller
  wxPoint GetClientAreaOrigin() const override;
  wxWindowMac* FindItem(long id) const;
  wxWindowMac* FindItemByHWND(WXHWND hWnd, bool controlOnly = false) const;
  virtual void TriggerScrollEvent(wxEventType scrollEvent);
    // this should not be overridden in classes above wxWindowMac
    // because it is called from its destructor via DeleteChildren
  void RemoveChild(wxWindowBase* child) override;
  virtual bool MacDoRedraw(long time);
  virtual void MacPaintChildrenBorders();
  virtual void MacPaintBorders(int left, int top);
  void MacPaintGrowBox();
    // invalidates the borders and focus area around the control;
    // must not be virtual as it will be called during destruction
  void MacInvalidateBorders();
  WXWindow MacGetTopLevelWindowRef() const;
  wxNonOwnedWindow* MacGetTopLevelWindow() const;
  virtual long MacGetWXBorderSize() const;
  virtual long MacGetLeftBorderSize() const;
  virtual long MacGetRightBorderSize() const;
  virtual long MacGetTopBorderSize() const;
  virtual long MacGetBottomBorderSize() const;
  virtual void MacSuperChangedPosition();
    // absolute coordinates of this window's root have changed
  virtual void MacTopLevelWindowChangedPosition();
  virtual void MacChildAdded();
  virtual void MacVisibilityChanged();
  virtual void MacEnabledStateChanged();
  virtual void MacHiliteChanged();
  virtual wxInt32 MacControlHit(WXEVENTHANDLERREF handler, WXEVENTREF event);
  bool MacIsReallyEnabled();
  bool MacIsReallyHilited();
  bool MacIsUserPane() const;
  virtual bool MacSetupCursor(const wxPoint& pt);
    // return the rectangle that would be visible of this control,
    // regardless whether controls are hidden
    // only taking into account clipping by parent windows
  const wxRect& MacGetClippedClientRect() const;
  const wxRect& MacGetClippedRect() const;
  const wxRect& MacGetClippedRectWithOuterStructure() const;
    // returns the visible region of this control in window ie non-client coordinates
  const wxRegion& MacGetVisibleRegion(bool includeOuterStructures = false);
    // returns true if children have to clipped to the content area
    // (e.g., scrolled windows)
  bool MacClipChildren() const
  {
    return m_clipChildren;
  }
  void MacSetClipChildren(bool clip)
  {
    m_clipChildren = clip;
  }
    // returns true if the grandchildren need to be clipped to the children's content area
    // (e.g., splitter windows)
  virtual bool MacClipGrandChildren() const
  {
    return false;
  }
  bool MacIsWindowScrollbar(const wxWindow* sb) const
  {
    return ((wxWindow*) m_hScrollBar == sb || (wxWindow*) m_vScrollBar == sb);
  }
  bool IsClientAreaChild(const wxWindow* child) const override
  {
    return !MacIsWindowScrollbar(child) && !((wxWindow*) m_growBox == child) && wxWindowBase::IsClientAreaChild(child);
  }
  void MacPostControlCreate(const wxPoint& pos, const wxSize& size);
  wxList& GetSubcontrols()
  {
    return m_subControls;
  }
    // translate wxWidgets coords into ones suitable
    // to be passed to CreateControl calls
    //
    // returns true if non-default coords are returned, false otherwise
  bool MacGetBoundsForControl(const wxPoint& pos, const wxSize& size, int& x, int& y, int& w, int& h, bool adjustForOrigin) const;
    // the 'true' OS level control for this wxWindow
  wxOSXWidgetImpl* GetPeer() const;
    // optimization to avoid creating a user pane in wxWindow::Create if we already know
    // we will replace it with our own peer
  void DontCreatePeer();
    // return true unless DontCreatePeer() had been called
  bool ShouldCreatePeer() const;
    // sets the native implementation wrapper, can replace an existing peer, use peer = NULL to
    // release existing peer
  void SetPeer(wxOSXWidgetImpl* peer);
    // wraps the already existing peer with the wrapper
  void SetWrappingPeer(wxOSXWidgetImpl* wrapper);
#  if  wxOSX_USE_COCOA_OR_IPHONE
    // the NSView or NSWindow of this window: can be used for both child and
    // non-owned windows
    //
    // this is useful for a few Cocoa function which can work with either views
    // or windows indiscriminately, e.g. for setting NSViewAnimationTargetKey
  virtual void* OSXGetViewOrWindow() const;
#  endif
  void* MacGetCGContextRef()
  {
    return m_cgContextRef;
  }
  void MacSetCGContextRef(void* cg)
  {
    m_cgContextRef = cg;
  }
    // osx specific event handling common for all osx-ports
  virtual bool OSXHandleClicked(double timestampsec);
  virtual bool OSXHandleKeyEvent(wxKeyEvent& event);
  virtual void OSXSimulateFocusEvents();
  bool IsNativeWindowWrapper() const
  {
    return m_isNativeWindowWrapper;
  }
  double GetContentScaleFactor() const override;
    // internal response to size events
  virtual void MacOnInternalSize()
  {
  }
    // Return the DPI corresponding to the given scale factor.
  static wxSize OSXMakeDPIFromScaleFactor(double scaleFactor);
protected:
    // For controls like radio buttons which are genuinely composite
  wxList m_subControls;
    // the peer object, allowing for cleaner API support
  void* m_cgContextRef;
    // cache the clipped rectangles within the window hierarchy
  void MacUpdateClippedRects() const;
  mutable bool m_cachedClippedRectValid;
  mutable wxRect m_cachedClippedRectWithOuterStructure;
  mutable wxRect m_cachedClippedRect;
  mutable wxRect m_cachedClippedClientRect;
  mutable wxRegion m_cachedClippedRegionWithOuterStructure;
  mutable wxRegion m_cachedClippedRegion;
  mutable wxRegion m_cachedClippedClientRegion;
    // insets of the mac control from the wx top left corner
  wxPoint m_macTopLeftInset;
  wxPoint m_macBottomRightInset;
  wxByte m_macAlpha;
  wxScrollBar* m_hScrollBar;
  wxScrollBar* m_vScrollBar;
  bool m_hScrollBarAlwaysShown;
  bool m_vScrollBarAlwaysShown;
  wxWindow* m_growBox;
  wxString m_label;
  bool m_isNativeWindowWrapper;
    // set to true if we do a sharp clip at the content area of this window
    // must be dynamic as eg a panel normally is not clipping precisely, but if
    // it becomes the target window of a scrolled window it has to...
  bool m_clipChildren;
  virtual bool MacIsChildOfClientArea(const wxWindow* child) const;
  bool MacHasScrollBarCorner() const;
  void MacCreateScrollBars(long style);
  void MacRepositionScrollBars();
  void MacUpdateControlFont();
    // implement the base class pure virtuals
  void DoGetTextExtent(const wxString& string, int* x, int* y, int* descent = NULL, int* externalLeading = NULL, const wxFont* theFont = NULL) const override;
  void DoEnable(bool enable) override;
#  if  wxUSE_MENUS
  bool DoPopupMenu(wxMenu* menu, int x, int y) override;
#  endif
  void DoFreeze() override;
  void DoThaw() override;
  wxSize DoGetBestSize() const override;
  virtual wxSize DoGetSizeFromClientSize(const wxSize& size) const;
  void DoClientToScreen(int* x, int* y) const override;
  void DoScreenToClient(int* x, int* y) const override;
  void DoGetPosition(int* x, int* y) const override;
  void DoGetSize(int* width, int* height) const override;
  void DoGetClientSize(int* width, int* height) const override;
  void DoSetSize(int x, int y, int width, int height, int sizeFlags = wxSIZE_AUTO) override;
  void DoSetClientSize(int width, int height) override;
  void DoCaptureMouse() override;
  void DoReleaseMouse() override;
    // move the window to the specified location and resize it: this is called
    // from both DoSetSize() and DoSetClientSize() and would usually just call
    // ::MoveWindow() except for composite controls which will want to arrange
    // themselves inside the given rectangle
  void DoMoveWindow(int x, int y, int width, int height) override;
  void DoSetWindowVariant(wxWindowVariant variant) override;
#  if  wxUSE_TOOLTIPS
  void DoSetToolTip(wxToolTip* tip) override;
#  endif
    // common part of Show/HideWithEffect()
  virtual bool OSXShowWithEffect(bool show, wxShowEffect effect, unsigned timeout);
private:
  wxOSXWidgetImpl* m_peer;
    // common part of all ctors
  void Init();
    // show/hide scrollbars as needed, common part of SetScrollbar() and
    // AlwaysShowScrollbars()
  void DoUpdateScrollbarVisibility();
  wxDECLARE_NO_COPY_CLASS(wxWindowMac);
  wxDECLARE_EVENT_TABLE();
};
#endif
