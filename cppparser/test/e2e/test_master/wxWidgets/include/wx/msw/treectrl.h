/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/treectrl.h
// Purpose:     wxTreeCtrl class
// Author:      Julian Smart
// Modified by: Vadim Zeitlin to be less MSW-specific on 10/10/98
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_TREECTRL_H_
#  define _WX_MSW_TREECTRL_H_
// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------
#  if  wxUSE_TREECTRL
#    include "wx/textctrl.h"
#    include "wx/dynarray.h"
#    include "wx/treebase.h"
#    include "wx/hashmap.h"
#    ifdef __GNUWIN32__
    // Cygwin windows.h defines these identifiers
#      undef GetFirstChild
#      undef GetNextSibling
#    endif
// fwd decl
class WXDLLIMPEXP_FWD_CORE wxImageList;
class WXDLLIMPEXP_FWD_CORE wxDragImage;
struct WXDLLIMPEXP_FWD_CORE wxTreeViewItem;
// hash storing attributes for our items
class wxItemAttr;
WX_DECLARE_EXPORTED_VOIDPTR_HASH_MAP(wxItemAttr *, wxMapTreeAttr);
// ----------------------------------------------------------------------------
// wxTreeCtrl
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxTreeCtrl : public wxTreeCtrlBase
{
public:
    // creation
    // --------
  wxTreeCtrl()
  {
    Init();
  }
  wxTreeCtrl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTreeCtrlNameStr))
  {
    Create(parent, id, pos, size, style, validator, name);
  }
  virtual ~wxTreeCtrl();
  bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTreeCtrlNameStr));
    // implement base class pure virtuals
    // ----------------------------------
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
    // item status inquiries
    // ---------------------
  bool IsVisible(const wxTreeItemId& item) const override;
  bool ItemHasChildren(const wxTreeItemId& item) const override;
  bool IsExpanded(const wxTreeItemId& item) const override;
  bool IsSelected(const wxTreeItemId& item) const override;
  bool IsBold(const wxTreeItemId& item) const override;
  size_t GetChildrenCount(const wxTreeItemId& item, bool recursively = true) const override;
    // navigation
    // ----------
  wxTreeItemId GetRootItem() const override;
  wxTreeItemId GetSelection() const override;
  size_t GetSelections(wxArrayTreeItemIds& selections) const override;
  wxTreeItemId GetFocusedItem() const override;
  void ClearFocusedItem() override;
  void SetFocusedItem(const wxTreeItemId& item) override;
  wxTreeItemId GetItemParent(const wxTreeItemId& item) const override;
  wxTreeItemId GetFirstChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const override;
  wxTreeItemId GetNextChild(const wxTreeItemId& item, wxTreeItemIdValue& cookie) const override;
  wxTreeItemId GetLastChild(const wxTreeItemId& item) const override;
  wxTreeItemId GetNextSibling(const wxTreeItemId& item) const override;
  wxTreeItemId GetPrevSibling(const wxTreeItemId& item) const override;
  wxTreeItemId GetFirstVisibleItem() const override;
  wxTreeItemId GetNextVisible(const wxTreeItemId& item) const override;
  wxTreeItemId GetPrevVisible(const wxTreeItemId& item) const override;
    // operations
    // ----------
  wxTreeItemId AddRoot(const wxString& text, int image = -1, int selectedImage = -1, wxTreeItemData* data = NULL) override;
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
  wxTextCtrl* EditLabel(const wxTreeItemId& item, wxClassInfo* textCtrlClass = wxCLASSINFO(wxTextCtrl)) override;
  wxTextCtrl* GetEditControl() const override;
  void EndEditLabel(const wxTreeItemId&, bool discardChanges = false) override
  {
    DoEndEditLabel(discardChanges);
  }
  void SortChildren(const wxTreeItemId& item) override;
  bool GetBoundingRect(const wxTreeItemId& item, wxRect& rect, bool textOnly = false) const override;
    // implementation
    // --------------
  wxVisualAttributes GetDefaultAttributes() const override
  {
    return GetClassDefaultAttributes(GetWindowVariant());
  }
  static wxVisualAttributes GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);
  WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override;
  WXLRESULT MSWDefWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override;
  bool MSWCommand(WXUINT param, WXWORD id) override;
  bool MSWOnNotify(int idCtrl, WXLPARAM lParam, WXLPARAM* result) override;
  bool MSWShouldPreProcessMessage(WXMSG* msg) override;
    // override some base class virtuals
  bool SetBackgroundColour(const wxColour& colour) override;
  bool SetForegroundColour(const wxColour& colour) override;
    // returns true if the platform should explicitly apply a theme border
  bool CanApplyThemeBorder() const override
  {
    return false;
  }
  bool IsDoubleBuffered() const override;
  void SetDoubleBuffered(bool on) override;
protected:
    // Implement "update locking" in a custom way for this control.
  void DoFreeze() override;
  void DoThaw() override;
  bool MSWShouldSetDefaultFont() const override
  {
    return false;
  }
    // SetImageList helper
  void SetAnyImageList(wxImageList* imageList, int which);
    // refresh a single item
  void RefreshItem(const wxTreeItemId& item);
    // end edit label
  void DoEndEditLabel(bool discardChanges = false);
  int DoGetItemState(const wxTreeItemId& item) const override;
  void DoSetItemState(const wxTreeItemId& item, int state) override;
  wxTreeItemId DoInsertItem(const wxTreeItemId& parent, size_t pos, const wxString& text, int image, int selectedImage, wxTreeItemData* data) override;
  wxTreeItemId DoInsertAfter(const wxTreeItemId& parent, const wxTreeItemId& idPrevious, const wxString& text, int image = -1, int selImage = -1, wxTreeItemData* data = NULL) override;
  wxTreeItemId DoTreeHitTest(const wxPoint& point, int& flags) const override;
    // obtain the user data for the lParam member of TV_ITEM
  class wxTreeItemParam* GetItemParam(const wxTreeItemId& item) const;
    // update the event to include the items client data and pass it to
    // HandleWindowEvent(), return true if it processed it
  bool HandleTreeEvent(wxTreeEvent& event) const;
    // pass the event to HandleTreeEvent() and return true if the event was
    // either unprocessed or not vetoed
  bool IsTreeEventAllowed(wxTreeEvent& event) const
  {
    return !HandleTreeEvent(event) || event.IsAllowed();
  }
    // generate a wxEVT_KEY_DOWN event from the specified WPARAM/LPARAM values
    // having the same meaning as for WM_KEYDOWN, return true if it was
    // processed
  bool MSWHandleTreeKeyDownEvent(WXWPARAM wParam, WXLPARAM lParam);
    // handle a key event in a multi-selection control, should be only called
    // for keys which can be used to change the selection
    //
    // return true if the key was processed, false otherwise
  bool MSWHandleSelectionKey(unsigned vkey);
  void MSWUpdateFontOnDPIChange(const wxSize& newDPI) override;
    // data used only while editing the item label:
  wxTextCtrl* m_textCtrl;
  wxTreeItemId m_idEdited;
private:
    // the common part of all ctors
  void Init();
    // helper functions
  bool DoGetItem(wxTreeViewItem* tvItem) const;
  void DoSetItem(wxTreeViewItem* tvItem);
  void DoExpand(const wxTreeItemId& item, int flag);
  void DoSelectItem(const wxTreeItemId& item, bool select = true);
  void DoUnselectItem(const wxTreeItemId& item);
  void DoToggleItemSelection(const wxTreeItemId& item);
  void DoUnselectAll();
  void DoSelectChildren(const wxTreeItemId& parent);
  void DeleteTextCtrl();
    // return true if the item is the hidden root one (i.e. it's the root item
    // and the tree has wxTR_HIDE_ROOT style)
  bool IsHiddenRoot(const wxTreeItemId& item) const;
    // check if the given flags (taken from TV_HITTESTINFO structure)
    // indicate a position "on item": this is less trivial than just checking
    // for TVHT_ONITEM because we consider that points to the left and right of
    // item text are also "on item" when wxTR_FULL_ROW_HIGHLIGHT is used as the
    // item visually spans the entire breadth of the window then
  bool MSWIsOnItem(unsigned flags) const;
    // Delete the given item from the native control.
  bool MSWDeleteItem(const wxTreeItemId& item);
    // the hash storing the items attributes (indexed by item ids)
  wxMapTreeAttr m_attrs;
    // true if the hash above is not empty
  bool m_hasAnyAttr;
#    if  wxUSE_DRAGIMAGE
    // used for dragging
  wxDragImage* m_dragImage;
#    endif
    // Virtual root item, if wxTR_HIDE_ROOT is set.
  void* m_pVirtualRoot;
    // Item to call EnsureVisible() on when the tree is thawed, if necessary.
  wxTreeItemId m_htEnsureVisibleOnThaw;
    // the starting item for selection with Shift
  wxTreeItemId m_htSelStart, m_htClickedItem;
  wxPoint m_ptClick;
    // whether dragging has started
  bool m_dragStarted;
    // whether focus was lost between subsequent clicks of a single item
  bool m_focusLost;
    // set when we are changing selection ourselves (only used in multi
    // selection mode)
  bool m_changingSelection;
    // whether we need to trigger a state image click event
  bool m_triggerStateImageClick;
    // whether we need to deselect other items on mouse up
  bool m_mouseUpDeselect;
  friend class wxTreeItemIndirectData;
  friend class wxTreeSortHelper;
  wxDECLARE_DYNAMIC_CLASS(wxTreeCtrl);
  wxDECLARE_NO_COPY_CLASS(wxTreeCtrl);
};
#  endif
#endif
