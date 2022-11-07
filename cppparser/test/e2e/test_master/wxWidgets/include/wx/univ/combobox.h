///////////////////////////////////////////////////////////////////////////////
// Name:        wx/univ/combobox.h
// Purpose:     the universal combobox
// Author:      Vadim Zeitlin
// Modified by:
// Created:     30.08.00
// Copyright:   (c) 2000 SciTech Software, Inc. (www.scitechsoft.com)
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_UNIV_COMBOBOX_H_
#  define _WX_UNIV_COMBOBOX_H_
#  include "wx/combo.h"
class WXDLLIMPEXP_FWD_CORE wxListBox;
// ----------------------------------------------------------------------------
// NB: some actions supported by this control are in wx/generic/combo.h
// ----------------------------------------------------------------------------

// choose the next/prev/specified (by numArg) item
#  define wxACTION_COMBOBOX_SELECT_NEXT	wxT("next")
#  define wxACTION_COMBOBOX_SELECT_PREV	wxT("prev")
#  define wxACTION_COMBOBOX_SELECT	wxT("select")
// ----------------------------------------------------------------------------
// wxComboBox: a combination of text control and a listbox
// ----------------------------------------------------------------------------

// NB: Normally we'd like wxComboBox to inherit from wxComboBoxBase, but here
//     we can't really do that since both wxComboBoxBase and wxComboCtrl inherit
//     from wxTextCtrl.
class WXDLLIMPEXP_CORE wxComboBox : public wxWindowWithItems<wxComboCtrl, wxItemContainer>
{
public:
    // ctors and such
  wxComboBox()
  {
    Init();
  }
  wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = (const wxString*) NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr))
  {
    Init();
    (void) Create(parent, id, value, pos, size, n, choices, style, validator, name);
  }
  wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = (const wxString*) NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr));
  virtual ~wxComboBox();
    // the wxUniversal-specific methods
    // --------------------------------

    // implement the combobox interface

    // wxTextCtrl methods
  wxString GetValue() const override
  {
    return DoGetValue();
  }
  void SetValue(const wxString& value) override;
  void WriteText(const wxString& value) override;
  void Copy() override;
  void Cut() override;
  void Paste() override;
  void SetInsertionPoint(long pos) override;
  void SetInsertionPointEnd() override;
  long GetInsertionPoint() const override;
  wxTextPos GetLastPosition() const override;
  void Replace(long from, long to, const wxString& value) override;
  void Remove(long from, long to) override;
  void SetSelection(long from, long to) override;
  void GetSelection(long* from, long* to) const override;
  void SetEditable(bool editable) override;
  bool IsEditable() const override;
  void Undo() override;
  void Redo() override;
  void SelectAll() override;
  bool CanCopy() const override;
  bool CanCut() const override;
  bool CanPaste() const override;
  bool CanUndo() const override;
  bool CanRedo() const override;
    // override these methods to disambiguate between two base classes versions
  void Clear() override
  {
    wxItemContainer::Clear();
  }
    // See wxComboBoxBase discussion of IsEmpty().
  bool IsListEmpty() const
  {
    return wxItemContainer::IsEmpty();
  }
  bool IsTextEmpty() const
  {
    return wxTextEntry::IsEmpty();
  }
    // wxControlWithItems methods
  void DoClear() override;
  void DoDeleteOneItem(unsigned int n) override;
  unsigned int GetCount() const override;
  wxString GetString(unsigned int n) const override;
  void SetString(unsigned int n, const wxString& s) override;
  int FindString(const wxString& s, bool bCase = false) const override;
  void SetSelection(int n) override;
  int GetSelection() const override;
  wxString GetStringSelection() const override;
    // we have our own input handler and our own actions
    // (but wxComboCtrl already handled Popup/Dismiss)
    /*
    virtual bool PerformAction(const wxControlAction& action,
                               long numArg = 0l,
                               const wxString& strArg = wxEmptyString);
    */
  static wxInputHandler* GetStdInputHandler(wxInputHandler* handlerDef);
  wxInputHandler* DoGetStdInputHandler(wxInputHandler* handlerDef) override
  {
    return GetStdInputHandler(handlerDef);
  }
    // we delegate our client data handling to wxListBox which we use for the
    // items, so override this and other methods dealing with the client data
  wxClientDataType GetClientDataType() const override;
  void SetClientDataType(wxClientDataType clientDataItemsType) override;
  const wxTextEntry* WXGetTextEntry() const override
  {
    return this;
  }
protected:
  int DoInsertItems(const wxArrayStringsAdapter& items, unsigned int pos, void** clientData, wxClientDataType type) override;
  void DoSetItemClientData(unsigned int n, void* clientData) override;
  void* DoGetItemClientData(unsigned int n) const override;
    // common part of all ctors
  void Init();
    // get the associated listbox
  wxListBox* GetLBox() const
  {
    return m_lbox;
  }
private:
    // implement wxTextEntry pure virtual method
  wxWindow* GetEditableWindow() override
  {
    return this;
  }
    // the popup listbox
  wxListBox* m_lbox;
    //wxDECLARE_EVENT_TABLE();
  wxDECLARE_DYNAMIC_CLASS(wxComboBox);
};
#endif
