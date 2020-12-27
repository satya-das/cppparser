/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/checkbox.h
// Purpose:     wxCheckBox class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_CHECKBOX_H_
#  define _WX_CHECKBOX_H_
#  include "wx/msw/ownerdrawnbutton.h"
// Checkbox item (single checkbox)
class WXDLLIMPEXP_CORE wxCheckBox : public wxMSWOwnerDrawnButton<wxCheckBoxBase>
{
public:
  wxCheckBox()
    :  m_state(wxCHK_UNCHECKED) 
    {
     }
  wxCheckBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr))
  {

        Create(parent, id, label, pos, size, style, validator, name);
      }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  void SetValue(bool value) override;
  bool GetValue() const override;
    // override some base class virtuals
  void SetLabel(const wxString& label) override;
  void SetTransparentPartColour(const wxColour& col) override
  {
        SetBackgroundColour(col);
    }
  bool MSWCommand(WXUINT param, WXWORD id) override;
  void Command(wxCommandEvent& event) override;
    // returns true if the platform should explicitly apply a theme border
  bool CanApplyThemeBorder() const override
  { return false; }
    // implementation only from now on
  WXDWORD MSWGetStyle(long flags, WXDWORD* exstyle = NULL) const override;
protected:
  wxSize DoGetBestClientSize() const override;
  void DoSet3StateValue(wxCheckBoxState value) override;
  wxCheckBoxState DoGet3StateValue() const override;
    // Implement wxMSWOwnerDrawnButtonBase methods.
  int MSWGetButtonStyle() const override;
  void MSWOnButtonResetOwnerDrawn() override;
  int MSWGetButtonCheckedFlag() const override;
  void MSWDrawButtonBitmap(wxDC& dc, const wxRect& rect, int flags) override;
private:
    // common part of all ctors
  void Init();
    // current state of the checkbox
  wxCheckBoxState m_state;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxCheckBox);
};
#endif
