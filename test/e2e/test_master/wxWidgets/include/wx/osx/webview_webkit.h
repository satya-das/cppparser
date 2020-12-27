/////////////////////////////////////////////////////////////////////////////
// Name:        include/wx/osx/webkit.h
// Purpose:     wxWebViewWebKit - embeddable web kit control,
//                             OS X implementation of web view component
// Author:      Jethro Grassie / Kevin Ollivier / Marianne Gagnon
// Modified by:
// Created:     2004-4-16
// Copyright:   (c) Jethro Grassie / Kevin Ollivier / Marianne Gagnon
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_WEBKIT_H
#  define _WX_WEBKIT_H
#  include "wx/defs.h"
#  if  wxUSE_WEBVIEW && wxUSE_WEBVIEW_WEBKIT && defined(__WXOSX__)
#    include "wx/control.h"
#    include "wx/webview.h"
#    include "wx/osx/core/objcid.h"
// ----------------------------------------------------------------------------
// Web Kit Control
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_WEBVIEW wxWebViewWebKit : public wxWebView
{
  wxDECLARE_DYNAMIC_CLASS(wxWebViewWebKit);
public:
  wxWebViewWebKit()
  {
  }
  wxWebViewWebKit(wxWindow* parent, wxWindowID winID = wxID_ANY, const wxString& strURL = wxASCII_STR(wxWebViewDefaultURLStr), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr))
  {

        Create(parent, winID, strURL, pos, size, style, name);
      }
  bool Create(wxWindow* parent, wxWindowID winID = wxID_ANY, const wxString& strURL = wxASCII_STR(wxWebViewDefaultURLStr), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr)) override;
  virtual ~wxWebViewWebKit();
  bool CanGoBack() const override;
  bool CanGoForward() const override;
  void GoBack() override;
  void GoForward() override;
  void Reload(wxWebViewReloadFlags flags = wxWEBVIEW_RELOAD_DEFAULT) override;
  void Stop() override;
  wxString GetPageSource() const override;
  wxString GetPageText() const override;
  void Print() override;
  void LoadURL(const wxString& url) override;
  wxString GetCurrentURL() const override;
  wxString GetCurrentTitle() const override;
  wxWebViewZoom GetZoom() const override;
  float GetZoomFactor() const override;
  void SetZoom(wxWebViewZoom zoom) override;
  void SetZoomFactor(float zoom) override;
  void SetZoomType(wxWebViewZoomType zoomType) override;
  wxWebViewZoomType GetZoomType() const override;
  bool CanSetZoomType(wxWebViewZoomType type) const override;
  bool IsBusy() const override
  { return m_busy; }
    //History functions
  void ClearHistory() override;
  void EnableHistory(bool enable = true) override;
  wxVector<wxSharedPtr<wxWebViewHistoryItem> > GetBackwardHistory() override;
  wxVector<wxSharedPtr<wxWebViewHistoryItem> > GetForwardHistory() override;
  void LoadHistoryItem(wxSharedPtr<wxWebViewHistoryItem> item) override;
    //Undo / redo functionality
  bool CanUndo() const override;
  bool CanRedo() const override;
  void Undo() override;
  void Redo() override;
    //Find function
  long Find(const wxString& text, int flags = wxWEBVIEW_FIND_DEFAULT) override
  {
        wxUnusedVar(text);
        wxUnusedVar(flags);
        return wxNOT_FOUND;
    }
    //Clipboard functions
  bool CanCut() const override
  { return true; }
  bool CanCopy() const override
  { return true; }
  bool CanPaste() const override
  { return true; }
  void Cut() override;
  void Copy() override;
  void Paste() override;
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
  void* GetNativeBackend() const override
  { return m_webView; }
    // ---- methods not from the parent (common) interface
  bool CanGetPageSource() const;
  void SetScrollPos(int pos);
  int GetScrollPos();
  bool CanIncreaseTextSize() const;
  void IncreaseTextSize();
  bool CanDecreaseTextSize() const;
  void DecreaseTextSize();
  float GetWebkitZoom() const;
  void SetWebkitZoom(float zoom);
    // don't hide base class virtuals
  void SetScrollPos(int orient, int pos, bool refresh = true) override
  { return wxControl::SetScrollPos(orient, pos, refresh); }
  int GetScrollPos(int orient) const override
  { return wxControl::GetScrollPos(orient); }
    //we need to resize the webview when the control size changes
  void OnSize(wxSizeEvent& event);
  void OnMove(wxMoveEvent& event);
  void OnMouseEvents(wxMouseEvent& event);
  bool m_busy;
  bool m_nextNavigationIsNewWindow;
protected:
  void DoSetPage(const wxString& html, const wxString& baseUrl) override;
  wxDECLARE_EVENT_TABLE();
  void MacVisibilityChanged() override;
private:
  wxWindow* m_parent;
  wxWindowID m_windowID;
  wxString m_pageTitle;
  OSXWebViewPtr m_webView;
  WX_NSObject m_loadDelegate;
  WX_NSObject m_policyDelegate;
  WX_NSObject m_UIDelegate;
    // we may use this later to setup our own mouse events,
    // so leave it in for now.
  void* m_webKitCtrlEventHandler;
};
class WXDLLIMPEXP_WEBVIEW wxWebViewFactoryWebKit : public wxWebViewFactory
{
public:
  virtual wxWebView* Create()
  { return new wxWebViewWebKit; }
  virtual wxWebView* Create(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr))
  { return new wxWebViewWebKit(parent, id, url, pos, size, style, name); }
};
#  endif
#endif
