///////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/window.h
// Purpose:     wxWindow class
// Author:      Peter Most, Javier Torres, Mariano Reingart
// Copyright:   (c) 2009 wxWidgets dev team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_WINDOW_H_
#  define _WX_QT_WINDOW_H_
class QShortcut;
template <typename T>
class QList;
class QWidget;
class QScrollArea;
class QScrollBar;
class QPicture;
class QPainter;
class QPaintEvent;
class QResizeEvent;
class QWheelEvent;
class QKeyEvent;
class QMouseEvent;
class QEvent;
class QMoveEvent;
class QEvent;
class QEvent;
class QCloseEvent;
class QContextMenuEvent;
class QFocusEvent;
class WXDLLIMPEXP_FWD_CORE wxScrollBar;
class WXDLLIMPEXP_FWD_CORE wxQtShortcutHandler;
/* wxQt specific notes:
 *
 * Remember to implement the Qt object getters on all subclasses:
 *  - GetHandle() returns the Qt object
 *  - QtGetScrollBarsContainer() returns the widget where scrollbars are placed
 * For example, for wxFrame, GetHandle() is the QMainWindow,
 * QtGetScrollBarsContainer() is the central widget and QtGetContainer() is a widget
 * in a layout inside the central widget that also contains the scrollbars.
 * Return 0 from QtGetScrollBarsContainer() to disable SetScrollBar() and friends
 * for wxWindow subclasses.
 *
 *
 * Event handling is achieved by using the template class wxQtEventForwarder
 * found in winevent_qt.(h|cpp) to send all Qt events here to QtHandleXXXEvent()
 * methods. All these methods receive the Qt event and the handler. This is
 * done because events of the containers (the scrolled part of the window) are
 * sent to the same wxWindow instance, that must be able to differentiate them
 * as some events need different handling (paintEvent) depending on that.
 * We pass the QWidget pointer to all event handlers for consistency.
 */
class WXDLLIMPEXP_CORE wxWindowQt : public wxWindowBase
{
public:
  wxWindowQt();
  ~wxWindowQt();
  wxWindowQt(wxWindowQt* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxPanelNameStr));
  bool Create(wxWindowQt* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxPanelNameStr));
    // Used by all window classes in the widget creation process.
  void PostCreation(bool generic = true);
  void AddChild(wxWindowBase* child) override;
  bool Show(bool show = true) override;
  void SetLabel(const wxString& label) override;
  wxString GetLabel() const override;
  void DoEnable(bool enable) override;
  void SetFocus() override;
    // Parent/Child:
  static void QtReparent(QWidget* child, QWidget* parent);
  bool Reparent(wxWindowBase* newParent) override;
    // Z-order
  void Raise() override;
  void Lower() override;
    // move the mouse to the specified position
  void WarpPointer(int x, int y) override;
  void Update() override;
  void Refresh(bool eraseBackground = true, const wxRect* rect = (const wxRect*) NULL) override;
  bool SetCursor(const wxCursor& cursor) override;
  bool SetFont(const wxFont& font) override;
    // get the (average) character size for the current font
  int GetCharHeight() const override;
  int GetCharWidth() const override;
  void SetScrollbar(int orient, int pos, int thumbvisible, int range, bool refresh = true) override;
  void SetScrollPos(int orient, int pos, bool refresh = true) override;
  int GetScrollPos(int orient) const override;
  int GetScrollThumb(int orient) const override;
  int GetScrollRange(int orient) const override;
        // scroll window to the specified position
  void ScrollWindow(int dx, int dy, const wxRect* rect = NULL) override;
    // Styles
  void SetWindowStyleFlag(long style) override;
  void SetExtraStyle(long exStyle) override;
  bool SetBackgroundStyle(wxBackgroundStyle style) override;
  bool IsTransparentBackgroundSupported(wxString* reason = NULL) const override;
  bool SetTransparent(wxByte alpha) override;
  bool CanSetTransparent() override
  {
    return true;
  }
  bool SetBackgroundColour(const wxColour& colour) override;
  bool SetForegroundColour(const wxColour& colour) override;
  QWidget* GetHandle() const override;
  void SetDropTarget(wxDropTarget* dropTarget) override;
#  if  wxUSE_ACCEL
    // accelerators
    // ------------
  void SetAcceleratorTable(const wxAcceleratorTable& accel) override;
#  endif
    // wxQt implementation internals:

    // Caller maintains ownership of pict - window will NOT delete it
  void QtSetPicture(QPicture* pict);
  QPainter* QtGetPainter();
  virtual bool QtHandlePaintEvent(QWidget* handler, QPaintEvent* event);
  virtual bool QtHandleResizeEvent(QWidget* handler, QResizeEvent* event);
  virtual bool QtHandleWheelEvent(QWidget* handler, QWheelEvent* event);
  virtual bool QtHandleKeyEvent(QWidget* handler, QKeyEvent* event);
  virtual bool QtHandleMouseEvent(QWidget* handler, QMouseEvent* event);
  virtual bool QtHandleEnterEvent(QWidget* handler, QEvent* event);
  virtual bool QtHandleMoveEvent(QWidget* handler, QMoveEvent* event);
  virtual bool QtHandleShowEvent(QWidget* handler, QEvent* event);
  virtual bool QtHandleChangeEvent(QWidget* handler, QEvent* event);
  virtual bool QtHandleCloseEvent(QWidget* handler, QCloseEvent* event);
  virtual bool QtHandleContextMenuEvent(QWidget* handler, QContextMenuEvent* event);
  virtual bool QtHandleFocusEvent(QWidget* handler, QFocusEvent* event);
  static void QtStoreWindowPointer(QWidget* widget, const wxWindowQt* window);
  static wxWindowQt* QtRetrieveWindowPointer(const QWidget* widget);
  static void QtSendSetCursorEvent(wxWindowQt* win, wxPoint posClient);
#  if  wxUSE_ACCEL
  virtual void QtHandleShortcut(int command);
#  endif
  virtual QScrollArea* QtGetScrollBarsContainer() const;
#  if  wxUSE_TOOLTIPS
    // applies tooltip to the widget.
  virtual void QtApplyToolTip(const wxString& text);
#  endif
protected:
  void DoGetTextExtent(const wxString& string, int* x, int* y, int* descent = NULL, int* externalLeading = NULL, const wxFont* font = NULL) const override;
    // coordinates translation
  void DoClientToScreen(int* x, int* y) const override;
  void DoScreenToClient(int* x, int* y) const override;
    // capture/release the mouse, used by Capture/ReleaseMouse()
  void DoCaptureMouse() override;
  void DoReleaseMouse() override;
    // retrieve the position/size of the window
  void DoGetPosition(int* x, int* y) const override;
  void DoSetSize(int x, int y, int width, int height, int sizeFlags = wxSIZE_AUTO) override;
  void DoGetSize(int* width, int* height) const override;
    // same as DoSetSize() for the client size
  void DoSetClientSize(int width, int height) override;
  void DoGetClientSize(int* width, int* height) const override;
  void DoMoveWindow(int x, int y, int width, int height) override;
#  if  wxUSE_TOOLTIPS
  void DoSetToolTip(wxToolTip* tip) override;
#  endif
#  if  wxUSE_MENUS
  bool DoPopupMenu(wxMenu* menu, int x, int y) override;
#  endif
    // Return the parent to use for children being reparented to us: this is
    // overridden in wxFrame to use its central widget rather than the frame
    // itself.
  virtual QWidget* QtGetParentWidget() const
  {
    return GetHandle();
  }
  QWidget* m_qtWindow;
private:
  void Init();
  QScrollArea* m_qtContainer;
  QScrollBar* m_horzScrollBar;
  QScrollBar* m_vertScrollBar;
    // Return the viewport of m_qtContainer, if it's used, or just m_qtWindow.
    //
    // Always returns non-null pointer if the window has been already created.
  QWidget* QtGetClientWidget() const;
  QScrollBar* QtGetScrollBar(int orientation) const;
  QScrollBar* QtSetScrollBar(int orientation, QScrollBar* scrollBar = NULL);
  bool QtSetBackgroundStyle();
  QPicture* m_qtPicture;
  wxScopedPtr<QPainter> m_qtPainter;
  bool m_mouseInside;
#  if  wxUSE_ACCEL
  wxVector<QShortcut*> m_qtShortcuts;
  wxScopedPtr<wxQtShortcutHandler> m_qtShortcutHandler;
  bool m_processingShortcut;
#  endif
  wxDECLARE_DYNAMIC_CLASS_NO_COPY( wxWindowQt );
};
#endif
