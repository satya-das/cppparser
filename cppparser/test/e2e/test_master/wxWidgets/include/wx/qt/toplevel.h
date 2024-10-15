///////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/toplevel.h
// Purpose:     declares wxTopLevelWindowNative class
// Author:      Peter Most, Javier Torres, Mariano Reingart
// Copyright:   (c) 2009 wxWidgets dev team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_TOPLEVEL_H_
#  define _WX_QT_TOPLEVEL_H_
class WXDLLIMPEXP_CORE wxTopLevelWindowQt : public wxTopLevelWindowBase
{
public:
  wxTopLevelWindowQt();
  wxTopLevelWindowQt(wxWindow* parent, wxWindowID winid, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr));
  bool Show(bool show = true) override;
  void Maximize(bool maximize = true) override;
  void Restore() override;
  void Iconize(bool iconize = true) override;
  bool IsMaximized() const override;
  bool IsIconized() const override;
  bool ShowFullScreen(bool show, long style = wxFULLSCREEN_ALL) override;
  bool IsFullScreen() const override;
  void SetTitle(const wxString& title) override;
  wxString GetTitle() const override;
  void SetIcons(const wxIconBundle& icons) override;
    // Styles
  void SetWindowStyleFlag(long style) override;
  long GetWindowStyleFlag() const override;
};
#endif
