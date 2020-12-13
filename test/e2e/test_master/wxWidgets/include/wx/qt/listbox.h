/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/listbox.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_LISTBOX_H_
#  define _WX_QT_LISTBOX_H_
class QListWidget;
class QModelIndex;
class QScrollArea;
class WXDLLIMPEXP_CORE wxListBox : public wxListBoxBase
{
public:
  wxListBox();
  wxListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  wxListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  virtual ~wxListBox();
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  bool IsSelected(int n) const override;
  int GetSelections(wxArrayInt& aSelections) const override;
  unsigned int GetCount() const override;
  wxString GetString(unsigned int n) const override;
  void SetString(unsigned int n, const wxString& s) override;
  int GetSelection() const override;
  QWidget* GetHandle() const override;
  void QtSendEvent(wxEventType evtType, int rowIndex, bool selected);
protected:
  void DoSetFirstItem(int n) override;
  void DoSetSelection(int n, bool select) override;
  int DoInsertItems(const wxArrayStringsAdapter& items, unsigned int pos, void** clientData, wxClientDataType type) override;
  int DoInsertOneItem(const wxString& item, unsigned int pos) override;
  void DoSetItemClientData(unsigned int n, void* clientData) override;
  void* DoGetItemClientData(unsigned int n) const override;
  void DoClear() override;
  void DoDeleteOneItem(unsigned int pos) override;
  QScrollArea* QtGetScrollBarsContainer() const override;
#  if  wxUSE_CHECKLISTBOX
  bool m_hasCheckBoxes;
#  endif
  QListWidget* m_qtListWidget;
private:
  virtual void Init();
    // Common part of both Create() overloads.
  void DoCreate(wxWindow* parent, long style);
  void UnSelectAll();
  wxDECLARE_DYNAMIC_CLASS(wxListBox);
};
#endif
