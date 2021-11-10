/////////////////////////////////////////////////////////////////////////////
// Name:        include/wx/msw/webview_edge.h
// Purpose:     wxMSW Edge Chromium wxWebView backend
// Author:      Markus Pingel
// Created:     2019-12-15
// Copyright:   (c) 2019 wxWidgets development team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef wxWebViewEdge_H
#  define wxWebViewEdge_H
#  include "wx/setup.h"
#  if  wxUSE_WEBVIEW && wxUSE_WEBVIEW_EDGE && defined(__WXMSW__)
#    include "wx/control.h"
#    include "wx/webview.h"
class wxWebViewEdgeImpl;
class WXDLLIMPEXP_WEBVIEW wxWebViewEdge : public wxWebView
{
public:
  wxWebViewEdge()
  {
  }
  wxWebViewEdge(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxWebViewNameStr)
  {
    Create(parent, id, url, pos, size, style, name);
  }
  ~wxWebViewEdge();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxWebViewNameStr) override;
  void LoadURL(const wxString& url) override;
  void LoadHistoryItem(wxSharedPtr<wxWebViewHistoryItem> item) override;
  wxVector<wxSharedPtr<wxWebViewHistoryItem> > GetBackwardHistory() override;
  wxVector<wxSharedPtr<wxWebViewHistoryItem> > GetForwardHistory() override;
  bool CanGoForward() const override;
  bool CanGoBack() const override;
  void GoBack() override;
  void GoForward() override;
  void ClearHistory() override;
  void EnableHistory(bool enable = true) override;
  void Stop() override;
  void Reload(wxWebViewReloadFlags flags = wxWEBVIEW_RELOAD_DEFAULT) override;
  wxString GetPageSource() const override;
  wxString GetPageText() const override;
  bool IsBusy() const override;
  wxString GetCurrentURL() const override;
  wxString GetCurrentTitle() const override;
  void SetZoomType(wxWebViewZoomType) override;
  wxWebViewZoomType GetZoomType() const override;
  bool CanSetZoomType(wxWebViewZoomType type) const override;
  void Print() override;
  wxWebViewZoom GetZoom() const override;
  float GetZoomFactor() const override;
  void SetZoom(wxWebViewZoom zoom) override;
  void SetZoomFactor(float zoom) override;
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
  void SelectAll() override;
  bool HasSelection() const override;
  void DeleteSelection() override;
  wxString GetSelectedText() const override;
  wxString GetSelectedSource() const override;
  void ClearSelection() override;
  void EnableContextMenu(bool enable = true) override;
  bool IsContextMenuEnabled() const override;
  void EnableAccessToDevTools(bool enable = true) override;
  bool IsAccessToDevToolsEnabled() const override;
  bool QueryCommandEnabled(const wxString& command) const;
  void ExecCommand(const wxString& command);
  bool RunScript(const wxString& javascript, wxString* output = NULL) override;
  void RegisterHandler(wxSharedPtr<wxWebViewHandler> handler) override;
  void* GetNativeBackend() const override;
protected:
  void DoSetPage(const wxString& html, const wxString& baseUrl) override;
private:
  wxWebViewEdgeImpl* m_impl;
  void OnSize(wxSizeEvent& event);
  void OnShow(wxShowEvent& event);
  bool RunScriptSync(const wxString& javascript, wxString* output = NULL);
  wxDECLARE_DYNAMIC_CLASS(wxWebViewEdge);
};
class WXDLLIMPEXP_WEBVIEW wxWebViewFactoryEdge : public wxWebViewFactory
{
public:
  wxWebView* Create() override
  {
    return new wxWebViewEdge;
  }
  wxWebView* Create(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxWebViewNameStr) override
  {
    return new wxWebViewEdge(parent, id, url, pos, size, style, name);
  }
  bool IsAvailable() override;
};
#  endif
#endif
