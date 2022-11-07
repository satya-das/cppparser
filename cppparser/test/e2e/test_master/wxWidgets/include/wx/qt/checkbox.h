/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/checkbox.h
// Author:      Peter Most, Sean D'Epagnier, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_CHECKBOX_H_
#  define _WX_QT_CHECKBOX_H_
class QCheckBox;
class WXDLLIMPEXP_CORE wxCheckBox : public wxCheckBoxBase
{
public:
  wxCheckBox();
  wxCheckBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCheckBoxNameStr));
  void SetValue(bool value) override;
  bool GetValue() const override;
  void SetLabel(const wxString& label) override;
  wxString GetLabel() const override;
  QWidget* GetHandle() const override;
protected:
  void DoSet3StateValue(wxCheckBoxState state) override;
  wxCheckBoxState DoGet3StateValue() const override;
private:
  QCheckBox* m_qtCheckBox;
  wxDECLARE_DYNAMIC_CLASS(wxCheckBox);
};
#endif
