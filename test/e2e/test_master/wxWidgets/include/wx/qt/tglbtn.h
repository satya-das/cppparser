/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/tglbtn.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_TGLBTN_H_
#  define _WX_QT_TGLBTN_H_
#  include "wx/tglbtn.h"
class WXDLLIMPEXP_CORE wxToggleButton : public wxToggleButtonBase
{
public:
  wxToggleButton();
  wxToggleButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  void SetValue(bool state) override;
  bool GetValue() const override;
    // implementation only
  int QtGetEventType() const override
  {
    return wxEVT_TOGGLEBUTTON;
  }
  wxDECLARE_DYNAMIC_CLASS(wxToggleButton);
};
class WXDLLIMPEXP_CORE wxBitmapToggleButton : public wxToggleButton
{
public:
  wxBitmapToggleButton();
  wxBitmapToggleButton(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  wxDECLARE_DYNAMIC_CLASS(wxBitmapToggleButton);
};
#endif
