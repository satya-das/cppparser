/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/treectrl.h
// Author:      Peter Most
// Copyright:   (c) Peter Most
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_TREECTRL_H_
#  define _WX_QT_TREECTRL_H_
class wxQTreeWidget;
class WXDLLIMPEXP_CORE wxTreeCtrl : public wxTreeCtrlBase
{
public:
  wxTreeCtrl();
  wxTreeCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTreeCtrlNameStr));
  virtual ~wxTreeCtrl();
  bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTreeCtrlNameStr));
  unsigned int GetCount() const override;
  unsigned int GetIndent() const override;
  void SetIndent(unsigned int indent) override;
  void SetImageList(wxImageList* imageList) override;
  void SetStateImageList(wxImageList* imageList) override;
  wxString GetItemText(const wxTreeItemId& item) const override;
  int GetItemImage(const wxTreeItemId& item, wxTreeItemIcon which = wxTreeItemIcon_Normal) const override;
  wxTreeItemData* GetItemData(const wxTreeItemId& item) const override;
  wxColour GetItemTextColour(const wxTreeItemId& item) const override;
  wxColour GetItemBackgroundColour(const wxTreeItemId& item) const override;
  wxFont GetItemFont(const wxTreeItemId& item) const override;
  void SetItemText(const wxTreeItemId& item, const wxString& text) override;
  void SetItemImage(const wxTreeItemId& item, int image, wxTreeItemIcon which = wxTreeItemIcon_Normal) override;
  void SetItemData(const wxTreeItemId& item, wxTreeItemData* data) override;
  void SetItemHasChildren(const wxTreeItemId& item, bool has = true) override;
  void SetItemBold(const wxTreeItemId& item, bool bold = true) override;
  void SetItemDropHighlight(const wxTreeItemId& item, bool highlight = true) override;
  void SetItemTextColour(const wxTreeItemId& item, const wxColour& col) override;
  void SetItemBackgroundColour(const wxTreeItemId& item, const wxColour& col) override;
  void SetItemFont(const wxTreeItemId& item, const wxFont& font) override;
  bool IsVisible(const wxTreeItemId& item) const override;
  bool ItemHasChildren(const wxTreeItemId& item) const override;
  bool IsExpanded(const wxTreeItemId& item) const override;
  bool IsSelected(const wxTreeItemId& item) const override;
  bool IsBold(const wxTreeItemId& item) const override;
  size_t GetChildrenCount(const wxTreeItemId& item, bool recursively = true) const override;
  wxTreeItemId GetRootItem() const override;
  wxTreeItemId GetSelection() const override;
  size_t GetSelections(wxArrayTreeItemIds& selections) const override;
  void SetFocusedItem(const wxTreeItemId& item) override;
  void ClearFocusedItem() override;
  wxTreeItemId GetFocusedItem() const override;
  wxTreeItemId GetItemParent(const wxTreeItemId& item) const override;
  wxTreeItemId GetFirstChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const override;
  wxTreeItemId GetNextChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const override;
  wxTreeItemId GetLastChild(const wxTreeItemId& item) const override;
  wxTreeItemId GetNextSibling(const wxTreeItemId& item) const override;
  wxTreeItemId GetPrevSibling(const wxTreeItemId& item) const override;
  wxTreeItemId GetFirstVisibleItem() const override;
  wxTreeItemId GetNextVisible(const wxTreeItemId& item) const override;
  wxTreeItemId GetPrevVisible(const wxTreeItemId& item) const override;
  wxTreeItemId AddRoot(const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL) override;
  void Delete(const wxTreeItemId& item) override;
  void DeleteChildren(const wxTreeItemId& item) override;
  void DeleteAllItems() override;
  void Expand(const wxTreeItemId& item) override;
  void Collapse(const wxTreeItemId& item) override;
  void CollapseAndReset(const wxTreeItemId& item) override;
  void Toggle(const wxTreeItemId& item) override;
  void Unselect() override;
  void UnselectAll() override;
  void SelectItem(const wxTreeItemId& item, bool select = true) override;
  void SelectChildren(const wxTreeItemId& parent) override;
  void EnsureVisible(const wxTreeItemId& item) override;
  void ScrollTo(const wxTreeItemId& item) override;
  wxTextCtrl* EditLabel(const wxTreeItemId& item, wxClassInfo* textCtrlClass = CLASSINFO(wxTextCtrl)) override;
  wxTextCtrl* GetEditControl() const override;
  void EndEditLabel(const wxTreeItemId& item, bool discardChanges = false) override;
  void SortChildren(const wxTreeItemId& item) override;
  bool GetBoundingRect(const wxTreeItemId& item, wxRect& rect, bool textOnly = false) const override;
  void SetWindowStyleFlag(long styles) override;
  QWidget* GetHandle() const override;
protected:
  int DoGetItemState(const wxTreeItemId& item) const override;
  void DoSetItemState(const wxTreeItemId& item, int state) override;
  wxTreeItemId DoInsertItem(const wxTreeItemId& parent, size_t pos, const wxString& text, int image, int selImage, wxTreeItemData* data) override;
  wxTreeItemId DoInsertAfter(const wxTreeItemId& parent, const wxTreeItemId& idPrevious, const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL) override;
  wxTreeItemId DoTreeHitTest(const wxPoint& point, int& flags) const override;
private:
  void SendDeleteEvent(const wxTreeItemId& item);
  wxTreeItemId GetNext(const wxTreeItemId& item) const;
  wxQTreeWidget* m_qtTreeWidget;
  wxDECLARE_DYNAMIC_CLASS(wxTreeCtrl);
};
#endif
