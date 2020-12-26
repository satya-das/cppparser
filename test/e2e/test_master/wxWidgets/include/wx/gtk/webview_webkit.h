/////////////////////////////////////////////////////////////////////////////
// Name:        include/gtk/wx/webview.h
// Purpose:     GTK webkit backend for web view component
// Author:      Robert Roebling, Marianne Gagnon
// Copyright:   (c) 2010 Marianne Gagnon, 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_WEBKITCTRL_H_
#  define _WX_GTK_WEBKITCTRL_H_
#  include "wx/defs.h"
// NOTE: this header is used for both the WebKit1 and WebKit2 implementations
#  if  wxUSE_WEBVIEW && (wxUSE_WEBVIEW_WEBKIT || wxUSE_WEBVIEW_WEBKIT2) && defined(__WXGTK__)
#    include "wx/sharedptr.h"
#    include "wx/webview.h"
#    if  wxUSE_WEBVIEW_WEBKIT2
#      include <glib.h>
#      include <gio/gio.h>
#    endif
typedef struct _WebKitWebView WebKitWebView;
//-----------------------------------------------------------------------------
// wxWebViewWebKit
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_WEBVIEW wxWebViewWebKit : public wxWebView
{
public:
  wxWebViewWebKit();
  wxWebViewWebKit(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr))
  {

        Create(parent, id, url, pos, size, style, name);
      }
  bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr)) override;
  virtual ~wxWebViewWebKit();
  bool Enable(bool enable = true) override;
    // implementation
    // --------------
  static wxVisualAttributes GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);
  void Stop() override;
  void LoadURL(const wxString& url) override;
  void GoBack() override;
  void GoForward() override;
  void Reload(wxWebViewReloadFlags flags = wxWEBVIEW_RELOAD_DEFAULT) override;
  bool CanGoBack() const override;
  bool CanGoForward() const override;
  void ClearHistory() override;
  void EnableContextMenu(bool enable = true) override;
  void EnableHistory(bool enable = true) override;
  wxVector<wxSharedPtr<wxWebViewHistoryItem> > GetBackwardHistory() override;
  wxVector<wxSharedPtr<wxWebViewHistoryItem> > GetForwardHistory() override;
  void LoadHistoryItem(wxSharedPtr<wxWebViewHistoryItem> item) override;
  wxString GetCurrentURL() const override;
  wxString GetCurrentTitle() const override;
  wxString GetPageSource() const override;
  wxString GetPageText() const override;
  void Print() override;
  bool IsBusy() const override;
  void SetZoomType(wxWebViewZoomType) override;
  wxWebViewZoomType GetZoomType() const override;
  bool CanSetZoomType(wxWebViewZoomType) const override;
  wxWebViewZoom GetZoom() const override;
  float GetZoomFactor() const override;
  void SetZoom(wxWebViewZoom) override;
  void SetZoomFactor(float) override;
    //Clipboard functions
  bool CanCut() const override;
  bool CanCopy() const override;
  bool CanPaste() const override;
  void Cut() override;
  void Copy() override;
  void Paste() override;
    //Undo / redo functionality
  bool CanUndo() const override;
  bool CanRedo() const override;
  void Undo() override;
  void Redo() override;
    //Find function
  long Find(const wxString& text, int flags = wxWEBVIEW_FIND_DEFAULT) override;
    //Editing functions
  void SetEditable(bool enable = true) override;
  bool IsEditable() const override;
    //Selection
  void DeleteSelection() override;
  bool HasSelection() const override;
  void SelectAll() override;
  wxString GetSelectedText() const override;
  wxString GetSelectedSource() const override;
  void ClearSelection() override;
  bool RunScript(const wxString& javascript, wxString* output = NULL) override;
    //Virtual Filesystem Support
  void RegisterHandler(wxSharedPtr<wxWebViewHandler> handler) override;
  virtual wxVector<wxSharedPtr<wxWebViewHandler> > GetHandlers()
  { return m_handlerList; }
  void* GetNativeBackend() const override
  {
    return m_web_view;
  }
    /** TODO: check if this can be made private
     * The native control has a getter to check for busy state, but except in
     * very recent versions of webkit this getter doesn't say everything we need
     * (namely it seems to stay indefinitely busy when loading is cancelled by
     * user)
     */
  bool m_busy;
  wxString m_vfsurl;
    //We use this flag to stop recursion when we load a page from the navigation
    //callback, mainly when loading a VFS page
  bool m_guard;
    //This flag is use to indicate when a navigation event is the result of a
    //create-web-view signal and so we need to send a new window event
  bool m_creating;
protected:
  void DoSetPage(const wxString& html, const wxString& baseUrl) override;
  GdkWindow* GTKGetWindow(wxArrayGdkWindows& windows) const override;
private:
  void ZoomIn();
  void ZoomOut();
  void SetWebkitZoom(float level);
  float GetWebkitZoom() const;
    //Find helper function
  void FindClear();
    // focus event handler: calls GTKUpdateBitmap()
  void GTKOnFocus(wxFocusEvent& event);
#    if  wxUSE_WEBVIEW_WEBKIT2
  bool CanExecuteEditingCommand(const gchar* command) const;
  void SetupWebExtensionServer();
  GDBusProxy* GetExtensionProxy() const;
  bool RunScriptSync(const wxString& javascript, wxString* output = NULL);
#    endif
  WebKitWebView* m_web_view;
  int m_historyLimit;
  wxVector<wxSharedPtr<wxWebViewHandler> > m_handlerList;
    //variables used for Find()
  int m_findFlags;
  wxString m_findText;
  int m_findPosition;
  int m_findCount;
#    if  wxUSE_WEBVIEW_WEBKIT2
    //Used for webkit2 extension
  GDBusServer* m_dbusServer;
  GDBusProxy* m_extension;
#    endif
  wxDECLARE_DYNAMIC_CLASS(wxWebViewWebKit);
};
class WXDLLIMPEXP_WEBVIEW wxWebViewFactoryWebKit : public wxWebViewFactory
{
public:
  wxWebView* Create() override
  {
    return new wxWebViewWebKit;
  }
  wxWebView* Create(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr)) override
  {
    return new wxWebViewWebKit(parent, id, url, pos, size, style, name);
  }
};
#  endif
#endif
