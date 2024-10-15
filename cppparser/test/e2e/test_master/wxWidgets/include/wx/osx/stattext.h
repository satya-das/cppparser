/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/stattext.h
// Purpose:     wxStaticText class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_STATTEXT_H_
#  define _WX_STATTEXT_H_
class WXDLLIMPEXP_CORE wxStaticText : public wxStaticTextBase
{
public:
  wxStaticText()
  {
  }
  wxStaticText(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticTextNameStr))
  {
    Create(parent, id, label, pos, size, style, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticTextNameStr));
  // accessors
  void SetLabel(const wxString& str) override;
  bool SetFont(const wxFont& font) override;
  bool AcceptsFocus() const override
  {
    return false;
  }
protected:
  wxString WXGetVisibleLabel() const override;
  void WXSetVisibleLabel(const wxString& str) override;
  wxSize DoGetBestSize() const override;
#  if  wxUSE_MARKUP && wxOSX_USE_COCOA
  bool DoSetLabelMarkup(const wxString& markup) override;
#  endif
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxStaticText);
};
#endif
    // _WX_STATTEXT_H_
