///////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/toplevel.h
// Purpose:     wxTopLevelWindowMac is the Mac implementation of wxTLW
// Author:      Stefan Csomor
// Modified by:
// Created:     20.09.01
// Copyright:   (c) 2001 Stefan Csomor
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_TOPLEVEL_H_
#  define _WX_MSW_TOPLEVEL_H_
// ----------------------------------------------------------------------------
// wxTopLevelWindowMac
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxTopLevelWindowMac : public wxTopLevelWindowBase
{
public:
    // constructors and such
  wxTopLevelWindowMac()
  {
    Init();
  }
  wxTopLevelWindowMac(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr))
  {
    Init();
    (void) Create(parent, id, title, pos, size, style, name);
  }
  virtual ~wxTopLevelWindowMac();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr));
  bool Create(wxWindow* parent, WXWindow nativeWindow);
  bool Destroy() override;
  wxPoint GetClientAreaOrigin() const override;
    // Attracts the users attention to this window if the application is
    // inactive (should be called when a background event occurs)
  void RequestUserAttention(int flags = wxUSER_ATTENTION_INFO) override;
    // implement base class pure virtuals
  void Maximize(bool maximize = true) override;
  bool IsMaximized() const override;
  void Iconize(bool iconize = true) override;
  bool IsIconized() const override;
  void Restore() override;
  bool IsActive() override;
  void ShowWithoutActivating() override;
  bool EnableFullScreenView(bool enable = true) override;
  bool ShowFullScreen(bool show, long style = wxFULLSCREEN_ALL) override;
  bool IsFullScreen() const override;
    // implementation from now on
    // --------------------------
  void SetTitle(const wxString& title) override;
  wxString GetTitle() const override;
    // EnableCloseButton(false) used to disable the "Close"
    // button on the title bar
  bool EnableCloseButton(bool enable = true) override;
  bool EnableMaximizeButton(bool enable = true) override;
  bool EnableMinimizeButton(bool enable = true) override;
  void SetLabel(const wxString& label) override
  {
    SetTitle(label);
  }
  wxString GetLabel() const override
  {
    return GetTitle();
  }
  void OSXSetModified(bool modified) override;
  bool OSXIsModified() const override;
  void SetRepresentedFilename(const wxString& filename) override;
    // do *not* call this to iconize the frame, this is a private function!
  void OSXSetIconizeState(bool iconic);
protected:
    // common part of all ctors
  void Init();
    // is the frame currently iconized?
  bool m_iconized;
    // should the frame be maximized when it will be shown? set by Maximize()
    // when it is called while the frame is hidden
  bool m_maximizeOnShow;
  wxDECLARE_EVENT_TABLE();
};
#endif
