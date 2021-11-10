/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/combobox.h
// Purpose:     wxComboBox class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_COMBOBOX_H_
#  define _WX_COMBOBOX_H_
#  include "wx/containr.h"
#  include "wx/choice.h"
#  include "wx/textctrl.h"
WX_DEFINE_ARRAY( char * , wxComboBoxDataArray ) ;
// forward declaration of private implementation classes
class wxComboBoxText;
class wxComboBoxChoice;
class wxComboWidgetImpl;
// Combobox item
class WXDLLIMPEXP_CORE wxComboBox : public wxWindowWithItems<
                wxControl,
                wxComboBoxBase>
{
  wxDECLARE_DYNAMIC_CLASS(wxComboBox);
public:
  virtual ~wxComboBox();
    // callback functions
  virtual void DelegateTextChanged(const wxString& value);
  virtual void DelegateChoice(const wxString& value);
  wxComboBox()
  {
  }
  wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr))
  {
    Create(parent, id, value, pos, size, n, choices, style, validator, name);
  }
  wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr))
  {
    Create(parent, id, value, pos, size, choices, style, validator, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr));
  int GetSelection() const override;
  void GetSelection(long* from, long* to) const override;
  void SetSelection(int n) override;
  void SetSelection(long from, long to) override;
  int FindString(const wxString& s, bool bCase = false) const override;
  wxString GetString(unsigned int n) const override;
  wxString GetStringSelection() const override;
  void SetString(unsigned int n, const wxString& s) override;
  unsigned int GetCount() const override;
  void SetValue(const wxString& value) override;
// these methods are provided by wxTextEntry for the native impl.
#  if  wxOSX_USE_COCOA
  void Popup() override;
  void Dismiss() override;
#  endif
  const wxTextEntry* WXGetTextEntry() const override
  {
    return this;
  }
    // osx specific event handling common for all osx-ports
  bool OSXHandleClicked(double timestampsec) override;
#  if  wxOSX_USE_COCOA
  wxComboWidgetImpl* GetComboPeer() const;
#  endif
protected:
    // List functions
  void DoDeleteOneItem(unsigned int n) override;
  void DoClear() override;
    // wxTextEntry functions
  wxWindow* GetEditableWindow() override
  {
    return this;
  }
    // override the base class virtuals involved in geometry calculations
  wxSize DoGetBestSize() const override;
  int DoInsertItems(const wxArrayStringsAdapter& items, unsigned int pos, void** clientData, wxClientDataType type) override;
  void DoSetItemClientData(unsigned int n, void* clientData) override;
  void* DoGetItemClientData(unsigned int n) const override;
  void EnableTextChangedEvents(bool enable) override;
    // callbacks
  void OnChar(wxKeyEvent& event);
  void OnKeyDown(wxKeyEvent& event);
    // the subcontrols
  wxComboBoxText* m_text;
  wxComboBoxChoice* m_choice;
  wxComboBoxDataArray m_datas;
private:
  wxDECLARE_EVENT_TABLE();
};
#endif
