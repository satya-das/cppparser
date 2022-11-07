/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/checklst.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_CHECKLST_H_
#  define _WX_QT_CHECKLST_H_
class WXDLLIMPEXP_CORE wxCheckListBox : public wxCheckListBoxBase
{
public:
  wxCheckListBox();
  wxCheckListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int nStrings = 0, const wxString* choices = (const wxString*) NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  wxCheckListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  virtual ~wxCheckListBox();
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  bool IsChecked(unsigned int item) const override;
  void Check(unsigned int item, bool check = true) override;
private:
  void Init() override;
  wxDECLARE_DYNAMIC_CLASS(wxCheckListBox);
};
#endif
