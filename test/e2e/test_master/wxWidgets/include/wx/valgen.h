/////////////////////////////////////////////////////////////////////////////
// Name:        wx/valgen.h
// Purpose:     wxGenericValidator class
// Author:      Kevin Smith
// Created:     Jan 22 1999
// Copyright:   (c) 1999 Julian Smart (assigned from Kevin)
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_VALGENH__
#  define _WX_VALGENH__
#  include "wx/validate.h"
#  if  wxUSE_VALIDATORS
class WXDLLIMPEXP_FWD_BASE wxDateTime;
class WXDLLIMPEXP_FWD_BASE wxFileName;
// ----------------------------------------------------------------------------
// wxGenericValidator performs data transfer between many standard controls and
// variables of the type corresponding to their values.
//
// It doesn't do any validation so its name is a slight misnomer.
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGenericValidator : public wxValidator
{
public:
    // Different constructors: each of them creates a validator which can only
    // be used with some controls, the comments before each constructor
    // indicate which ones:
        // wxCheckBox, wxRadioButton, wx(Bitmap)ToggleButton
  wxGenericValidator(bool* val);
        // wxChoice, wxGauge, wxRadioBox, wxScrollBar, wxSlider, wxSpinButton
  wxGenericValidator(int* val);
        // wxComboBox, wxTextCtrl, wxButton, wxStaticText (read-only)
  wxGenericValidator(wxString* val);
        // wxListBox, wxCheckListBox
  wxGenericValidator(wxArrayInt* val);
        // wxDatePickerCtrl
    wxGenericValidator(wxDateTime* val);
#endif // wxUSE_DATETIME
        // wxTextCtrl
  wxGenericValidator(wxFileName* val);
        // wxTextCtrl
  wxGenericValidator(float* val);
        // wxTextCtrl
  wxGenericValidator(double* val);
  wxGenericValidator(const wxGenericValidator& copyFrom);
  virtual ~wxGenericValidator()
  {
  }
    // Make a clone of this validator (or return NULL) - currently necessary
    // if you're passing a reference to a validator.
    // Another possibility is to always pass a pointer to a new validator
    // (so the calling code can use a copy constructor of the relevant class).
  wxObject* Clone() const override
  {
 return new wxGenericValidator(*this);
  }
  bool Copy(const wxGenericValidator& val);
    // Called when the value in the window must be validated: this is not used
    // by this class
  bool Validate(wxWindow*) override
  {
 return true;
  }
    // Called to transfer data to the window
  bool TransferToWindow() override;
    // Called to transfer data to the window
  bool TransferFromWindow() override;
protected:
  void Initialize();
  bool* m_pBool;
  int* m_pInt;
  wxString* m_pString;
  wxArrayInt* m_pArrayInt;
  wxFileName* m_pFileName;
  float* m_pFloat;
  double* m_pDouble;
  wxDECLARE_CLASS(wxGenericValidator);
  wxDECLARE_NO_ASSIGN_CLASS(wxGenericValidator);
};
#  endif
#endif
