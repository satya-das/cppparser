///////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/statusbr.h
// Purpose:     native implementation of wxStatusBar.
//              Optional: can use generic version instead.
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_STATBAR_H_
#  define _WX_STATBAR_H_
class WXDLLIMPEXP_CORE wxStatusBarMac : public wxStatusBarGeneric
{
public:
  wxStatusBarMac();
  wxStatusBarMac(wxWindow* parent, wxWindowID id = wxID_ANY, long style = wxSTB_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxStatusBarNameStr));
  virtual ~wxStatusBarMac();
  bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, long style = wxSTB_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxStatusBarNameStr));
    // Implementation
  void MacHiliteChanged() override;
  void OnPaint(wxPaintEvent& event);
protected:
  void DrawFieldText(wxDC& dc, const wxRect& rc, int i, int textHeight) override;
  void DrawField(wxDC& dc, int i, int textHeight) override;
  void DoUpdateStatusText(int number = 0) override;
  void InitColours() override;
private:
  wxColour m_textActive, m_textInactive, m_bgActiveFrom, m_bgActiveTo, m_borderActive, m_borderInactive;
  wxDECLARE_DYNAMIC_CLASS(wxStatusBarMac);
  wxDECLARE_EVENT_TABLE();
};
#endif
