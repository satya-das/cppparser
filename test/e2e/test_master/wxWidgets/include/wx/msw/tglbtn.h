/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/tglbtn.h
// Purpose:     Declaration of the wxToggleButton class, which implements a
//              toggle button under wxMSW.
// Author:      John Norris, minor changes by Axel Schlueter
// Modified by:
// Created:     08.02.01
// Copyright:   (c) 2000 Johnny C. Norris II
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_TOGGLEBUTTON_H_
#  define _WX_TOGGLEBUTTON_H_
#  include "wx/bitmap.h"
// Checkbox item (single checkbox)
class WXDLLIMPEXP_CORE wxToggleButton : public wxToggleButtonBase
{
public:
  wxToggleButton()
  {
 Init();
  }
  wxToggleButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr))
  {
        Create(parent, id, label, pos, size, style, validator, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  void SetValue(bool value) override;
  bool GetValue() const override;
  bool MSWCommand(WXUINT param, WXWORD id) override;
  void Command(wxCommandEvent& event) override;
    // returns true if the platform should explicitly apply a theme border
  bool CanApplyThemeBorder() const override
  {
 return false;
  }
protected:
  wxBorder GetDefaultBorder() const override
  {
 return wxBORDER_NONE;
  }
  WXDWORD MSWGetStyle(long flags, WXDWORD* exstyle = NULL) const override;
  bool MSWIsPushed() const override;
  void Init();
    // current state of the button (when owner-drawn)
  bool m_state;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxToggleButton);
};
//-----------------------------------------------------------------------------
// wxBitmapToggleButton
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxBitmapToggleButton : public wxToggleButton
{
public:
    // construction/destruction
  wxBitmapToggleButton()
  {
  }
  wxBitmapToggleButton(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr))
  {
        Create(parent, id, label, pos, size, style, validator, name);
  }
    // Create the control
  bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
    // deprecated synonym for SetBitmapLabel()
  void SetLabel(const wxString& label) override
  {
 wxToggleButton::SetLabel(label);
  }
private:
  wxDECLARE_DYNAMIC_CLASS(wxBitmapToggleButton);
};
#endif
