/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/listbox.h
// Purpose:     wxListBox class declaration
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_LISTBOX_H_
#  define _WX_GTK_LISTBOX_H_
struct _wxTreeEntry;
struct _GtkTreeIter;
//-----------------------------------------------------------------------------
// wxListBox
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxListBox : public wxListBoxBase
{
public:
    // ctors and such
  wxListBox()
  {
    Init();
  }
  wxListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = (const wxString*) NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr))
  {
    Init();
    Create(parent, id, pos, size, n, choices, style, validator, name);
  }
  wxListBox(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr))
  {
    Init();
    Create(parent, id, pos, size, choices, style, validator, name);
  }
  virtual ~wxListBox();
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = (const wxString*) NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxListBoxNameStr));
  unsigned int GetCount() const override;
  wxString GetString(unsigned int n) const override;
  void SetString(unsigned int n, const wxString& s) override;
  int FindString(const wxString& s, bool bCase = false) const override;
  bool IsSelected(int n) const override;
  int GetSelection() const override;
  int GetSelections(wxArrayInt& aSelections) const override;
  void EnsureVisible(int n) override;
  int GetTopItem() const override;
  int GetCountPerPage() const override;
  void Update() override;
  static wxVisualAttributes GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);
    // implementation from now on
  GtkWidget* GetConnectWidget() override;
  struct _GtkTreeView* m_treeview;
  struct _GtkListStore* m_liststore;
#  if  wxUSE_CHECKLISTBOX
  bool m_hasCheckBoxes;
#  endif
  struct _wxTreeEntry* GTKGetEntry(unsigned pos) const;
  void GTKDisableEvents();
  void GTKEnableEvents();
  void GTKOnSelectionChanged();
  void GTKOnActivated(int item);
protected:
  void DoClear() override;
  void DoDeleteOneItem(unsigned int n) override;
  wxSize DoGetBestSize() const override;
  void DoApplyWidgetStyle(GtkRcStyle* style) override;
  GdkWindow* GTKGetWindow(wxArrayGdkWindows& windows) const override;
  void DoSetSelection(int n, bool select) override;
  int DoInsertItems(const wxArrayStringsAdapter& items, unsigned int pos, void** clientData, wxClientDataType type) override;
  int DoInsertOneItem(const wxString& item, unsigned int pos) override;
  void DoSetFirstItem(int n) override;
  void DoSetItemClientData(unsigned int n, void* clientData) override;
  void* DoGetItemClientData(unsigned int n) const override;
  int DoListHitTest(const wxPoint& point) const override;
    // get the iterator for the given index, returns false if invalid
  bool GTKGetIteratorFor(unsigned pos, _GtkTreeIter* iter) const;
    // get the index for the given iterator, return wxNOT_FOUND on failure
  int GTKGetIndexFor(_GtkTreeIter& iter) const;
    // common part of DoSetFirstItem() and EnsureVisible()
  void DoScrollToCell(int n, float alignY, float alignX);
private:
  void Init();
  wxDECLARE_DYNAMIC_CLASS(wxListBox);
};
#endif
