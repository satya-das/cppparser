/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/radiobut.h
// Purpose:     wxRadioButton class
// Author:      Stefan Csomor
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_RADIOBUT_H_
#  define _WX_RADIOBUT_H_
class WXDLLIMPEXP_CORE wxRadioButton : public wxRadioButtonBase
{
  wxDECLARE_DYNAMIC_CLASS(wxRadioButton);
public:
  wxRadioButton()
  {
  }
  wxRadioButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioButtonNameStr))
  {
    Create(parent, id, label, pos, size, style, validator, name);
  }
  virtual ~wxRadioButton();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioButtonNameStr));
  void SetValue(bool val) override;
  bool GetValue() const override;
    // implementation
  void Command(wxCommandEvent& event) override;
  wxRadioButton* AddInCycle(wxRadioButton* cycle);
  void RemoveFromCycle();
  wxRadioButton* NextInCycle()
  {
    return m_cycle;
  }
    // osx specific event handling common for all osx-ports
  bool OSXHandleClicked(double timestampsec) override;
protected:
  wxRadioButton* m_cycle;
};
// Not implemented
#endif
    // _WX_RADIOBUT_H_
