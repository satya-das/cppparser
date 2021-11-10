/////////////////////////////////////////////////////////////////////////////
// Name:        include/wx/msw/webview_ie.h
// Purpose:     wxMSW IE wxWebView backend
// Author:      Marianne Gagnon
// Copyright:   (c) 2010 Marianne Gagnon, 2011 Steven Lamerton
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef wxWebViewIE_H
#  define wxWebViewIE_H
#  include "wx/setup.h"
#  if  wxUSE_WEBVIEW && wxUSE_WEBVIEW_IE && defined(__WXMSW__)
#    include "wx/webview.h"
#    include "wx/msw/ole/activex.h"
class wxWebViewIEImpl;
// Note that the highest emulation level may be used even when the
// corresponding browser version is not installed.
//
// Using FORCE options is not recommended, DEFAULT can be used to reset level
// to the system default.
//
// The value of the constants were taken from
//
//   https://msdn.microsoft.com/library/ee330730.aspx#browser_emulation
//
// and must not be changed.
enum wxWebViewIE_EmulationLevel {
    wxWEBVIEWIE_EMU_DEFAULT =    0,
    wxWEBVIEWIE_EMU_IE7 =        7000,
    wxWEBVIEWIE_EMU_IE8 =        8000,
    wxWEBVIEWIE_EMU_IE8_FORCE =  8888,
    wxWEBVIEWIE_EMU_IE9 =        9000,
    wxWEBVIEWIE_EMU_IE9_FORCE =  9999,
    wxWEBVIEWIE_EMU_IE10 =       10000,
    wxWEBVIEWIE_EMU_IE10_FORCE = 10001,
    wxWEBVIEWIE_EMU_IE11 =       11000,
    wxWEBVIEWIE_EMU_IE11_FORCE = 11001
};
class WXDLLIMPEXP_WEBVIEW wxWebViewIE : public wxWebView
{
public:
  wxWebViewIE()
  {
  }
  wxWebViewIE(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr))
  {
    Create(parent, id, url, pos, size, style, name);
  }
  ~wxWebViewIE();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr)) override;
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
  bool CanSetZoomType(wxWebViewZoomType) const override;
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
  bool RunScript(const wxString& javascript, wxString* output = NULL) override;
    //Virtual Filesystem Support
  void RegisterHandler(wxSharedPtr<wxWebViewHandler> handler) override;
  void* GetNativeBackend() const override;
    // ---- IE-specific methods

    // FIXME: I seem to be able to access remote webpages even in offline mode...
  bool IsOfflineMode();
  void SetOfflineMode(bool offline);
  wxWebViewZoom GetIETextZoom() const;
  void SetIETextZoom(wxWebViewZoom level);
  wxWebViewZoom GetIEOpticalZoom() const;
  int GetIEOpticalZoomFactor() const;
  void SetIEOpticalZoom(wxWebViewZoom level);
  void SetIEOpticalZoomFactor(int zoom);
  void onActiveXEvent(wxActiveXEvent& evt);
  void onEraseBg(wxEraseEvent&)
  {
  }
    // Switch to specific emulation level for the browser control to
    // ensure RunScript() and web pages work as designed and also change the
    // value of User-Agent header sent to web server.
  static bool MSWSetEmulationLevel(wxWebViewIE_EmulationLevel level = wxWEBVIEWIE_EMU_IE11);
    // This function is provided only for compatibility reasons, use
    // MSWSetEmulationLevel() in the new code instead.
  static bool MSWSetModernEmulationLevel(bool modernLevel = true)
  {
    return MSWSetEmulationLevel(modernLevel ? wxWEBVIEWIE_EMU_IE8 : wxWEBVIEWIE_EMU_DEFAULT);
  }
  wxDECLARE_EVENT_TABLE();
protected:
  void DoSetPage(const wxString& html, const wxString& baseUrl) override;
private:
  wxWebViewIEImpl* m_impl;
  wxDECLARE_DYNAMIC_CLASS(wxWebViewIE);
};
class WXDLLIMPEXP_WEBVIEW wxWebViewFactoryIE : public wxWebViewFactory
{
public:
  wxWebView* Create() override
  {
    return new wxWebViewIE;
  }
  wxWebView* Create(wxWindow* parent, wxWindowID id, const wxString& url = wxWebViewDefaultURLStr, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxWebViewNameStr)) override
  {
    return new wxWebViewIE(parent, id, url, pos, size, style, name);
  }
};
#  endif
#endif
