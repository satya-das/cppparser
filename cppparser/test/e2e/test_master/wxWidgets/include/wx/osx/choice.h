/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/choice.h
// Purpose:     wxChoice class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_CHOICE_H_
#  define _WX_CHOICE_H_
#  include "wx/control.h"
#  include "wx/dynarray.h"
#  include "wx/arrstr.h"
WX_DEFINE_ARRAY( char * , wxChoiceDataArray ) ;
// Choice item
class WXDLLIMPEXP_CORE wxChoice : public wxChoiceBase
{
  wxDECLARE_DYNAMIC_CLASS(wxChoice);
public:
  wxChoice()
    : m_strings()
    , m_datas()
  {
  }
  virtual ~wxChoice();
  wxChoice(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxChoiceNameStr))
  {
    Create(parent, id, pos, size, n, choices, style, validator, name);
  }
  wxChoice(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxChoiceNameStr))
  {
    Create(parent, id, pos, size, choices, style, validator, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxChoiceNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxChoiceNameStr));
  unsigned int GetCount() const override;
  int GetSelection() const override;
  void SetSelection(int n) override;
  int FindString(const wxString& s, bool bCase = false) const override;
  wxString GetString(unsigned int n) const override;
  void SetString(unsigned int pos, const wxString& s) override;
    // osx specific event handling common for all osx-ports
  bool OSXHandleClicked(double timestampsec) override;
protected:
  void DoDeleteOneItem(unsigned int n) override;
  void DoClear() override;
  wxSize DoGetBestSize() const override;
  int DoInsertItems(const wxArrayStringsAdapter& items, unsigned int pos, void** clientData, wxClientDataType type) override;
  void DoSetItemClientData(unsigned int n, void* clientData) override;
  void* DoGetItemClientData(unsigned int n) const override;
  wxArrayString m_strings;
  wxChoiceDataArray m_datas;
private:
    // This should be called when the number of items in the control changes.
  void DoAfterItemCountChange();
};
#endif
    // _WX_CHOICE_H_
