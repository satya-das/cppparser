/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/dataview.h
// Purpose:     wxDataViewCtrl generic implementation header
// Author:      Robert Roebling
// Modified By: Bo Yang
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef __GENERICDATAVIEWCTRLH__
#  define __GENERICDATAVIEWCTRLH__
#  include "wx/defs.h"
#  include "wx/object.h"
#  include "wx/control.h"
#  include "wx/scrolwin.h"
#  include "wx/icon.h"
#  include "wx/vector.h"
#  if  wxUSE_ACCESSIBILITY
#    include "wx/access.h"
#  endif
class WXDLLIMPEXP_FWD_CORE wxDataViewMainWindow;
class WXDLLIMPEXP_FWD_CORE wxDataViewHeaderWindow;
#  if  wxUSE_ACCESSIBILITY
class WXDLLIMPEXP_FWD_CORE wxDataViewCtrlAccessible;
#  endif
// ---------------------------------------------------------
// wxDataViewColumn
// ---------------------------------------------------------
class WXDLLIMPEXP_CORE wxDataViewColumn : public wxDataViewColumnBase
{
public:
  wxDataViewColumn(const wxString& title, wxDataViewRenderer* renderer, unsigned int model_column, int width = wxDVC_DEFAULT_WIDTH, wxAlignment align = wxALIGN_CENTER, int flags = wxDATAVIEW_COL_RESIZABLE)
    :  wxDataViewColumnBase(renderer, model_column),
          m_title(title)
    
    {

        Init(width, align, flags);
        }
  wxDataViewColumn(const wxBitmap& bitmap, wxDataViewRenderer* renderer, unsigned int model_column, int width = wxDVC_DEFAULT_WIDTH, wxAlignment align = wxALIGN_CENTER, int flags = wxDATAVIEW_COL_RESIZABLE)
    :  wxDataViewColumnBase(bitmap, renderer, model_column)
    
    {

        Init(width, align, flags);
        }
    // implement wxHeaderColumnBase methods
  void SetTitle(const wxString& title) override
  {
        m_title = title;
        UpdateWidth();
    }
  wxString GetTitle() const override
  {
        return m_title;
    }
  void SetWidth(int width) override
  {
        // Call the actual update method, used for both automatic and "manual"
        // width changes.
        WXUpdateWidth(width);

        // Do remember the last explicitly set width: this is used to prevent
        // UpdateColumnSizes() from resizing the last column to be smaller than
        // this size.
        m_manuallySetWidth = width;
    }
  int GetWidth() const override;
  void SetMinWidth(int minWidth) override
  {
        m_minWidth = minWidth;
        UpdateWidth();
    }
  int GetMinWidth() const override
  {
        return m_minWidth;
    }
  void SetAlignment(wxAlignment align) override
  {
        m_align = align;
        UpdateDisplay();
    }
  wxAlignment GetAlignment() const override
  {
        return m_align;
    }
  void SetFlags(int flags) override
  {
        m_flags = flags;
        UpdateDisplay();
    }
  int GetFlags() const override
  {
        return m_flags;
    }
  bool IsSortKey() const override
  {
        return m_sort;
    }
  void UnsetAsSortKey() override;
  void SetSortOrder(bool ascending) override;
  bool IsSortOrderAscending() const override
  {
        return m_sortAscending;
    }
  void SetBitmap(const wxBitmap& bitmap) override
  {
        wxDataViewColumnBase::SetBitmap(bitmap);
        UpdateWidth();
    }
    // This method is specific to the generic implementation and is used only
    // by wxWidgets itself.
  void WXUpdateWidth(int width)
  {
        if ( width == m_width )
            return;

        m_width = width;
        UpdateWidth();
    }
    // This method is also internal and called when the column is resized by
    // user interactively.
  void WXOnResize(int width);
  int WXGetSpecifiedWidth() const override;
private:
    // common part of all ctors
  void Init(int width, wxAlignment align, int flags);
    // These methods forward to wxDataViewCtrl::OnColumnChange() and
    // OnColumnWidthChange() respectively, i.e. the latter is stronger than the
    // former.
  void UpdateDisplay();
  void UpdateWidth();
    // Return the effective value corresponding to the given width, handling
    // its negative values such as wxCOL_WIDTH_DEFAULT.
  int DoGetEffectiveWidth(int width) const;
  wxString m_title;
  int m_width, m_manuallySetWidth, m_minWidth;
  wxAlignment m_align;
  int m_flags;
  bool m_sort, m_sortAscending;
  friend class wxDataViewHeaderWindowBase;
  friend class wxDataViewHeaderWindow;
  friend class wxDataViewHeaderWindowMSW;
};
// ---------------------------------------------------------
// wxDataViewCtrl
// ---------------------------------------------------------
class WXDLLIMPEXP_CORE wxDataViewCtrl : public wxDataViewCtrlBase, public wxScrollHelper
{
  friend class wxDataViewMainWindow;
  friend class wxDataViewHeaderWindowBase;
  friend class wxDataViewHeaderWindow;
  friend class wxDataViewHeaderWindowMSW;
  friend class wxDataViewColumn;
#  if  wxUSE_ACCESSIBILITY
  friend class wxDataViewCtrlAccessible;
#  endif
public:
  wxDataViewCtrl()
    :  wxScrollHelper(this)
    
    {

        Init();
        }
  wxDataViewCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxDataViewCtrlNameStr))
    :  wxScrollHelper(this)
    
    {

        Create(parent, id, pos, size, style, validator, name);
        }
  virtual ~wxDataViewCtrl();
  void Init();
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxDataViewCtrlNameStr));
  bool AssociateModel(wxDataViewModel* model) override;
  bool AppendColumn(wxDataViewColumn* col) override;
  bool PrependColumn(wxDataViewColumn* col) override;
  bool InsertColumn(unsigned int pos, wxDataViewColumn* col) override;
  void DoSetExpanderColumn() override;
  void DoSetIndent() override;
  unsigned int GetColumnCount() const override;
  wxDataViewColumn* GetColumn(unsigned int pos) const override;
  bool DeleteColumn(wxDataViewColumn* column) override;
  bool ClearColumns() override;
  int GetColumnPosition(const wxDataViewColumn* column) const override;
  wxDataViewColumn* GetSortingColumn() const override;
  wxVector<wxDataViewColumn *> GetSortingColumns() const override;
  wxDataViewItem GetTopItem() const override;
  int GetCountPerPage() const override;
  int GetSelectedItemsCount() const override;
  int GetSelections(wxDataViewItemArray& sel) const override;
  void SetSelections(const wxDataViewItemArray& sel) override;
  void Select(const wxDataViewItem& item) override;
  void Unselect(const wxDataViewItem& item) override;
  bool IsSelected(const wxDataViewItem& item) const override;
  void SelectAll() override;
  void UnselectAll() override;
  void EnsureVisible(const wxDataViewItem& item, const wxDataViewColumn* column = NULL) override;
  void HitTest(const wxPoint& point, wxDataViewItem& item, wxDataViewColumn*& column) const override;
  wxRect GetItemRect(const wxDataViewItem& item, const wxDataViewColumn* column = NULL) const override;
  bool SetRowHeight(int rowHeight) override;
  void Collapse(const wxDataViewItem& item) override;
  bool IsExpanded(const wxDataViewItem& item) const override;
  void SetFocus() override;
  bool SetFont(const wxFont& font) override;
#  if  wxUSE_ACCESSIBILITY
  bool Show(bool show = true) override;
  void SetName(const wxString& name) override;
  bool Reparent(wxWindowBase* newParent) override;
#  endif
  bool Enable(bool enable = true) override;
  bool AllowMultiColumnSort(bool allow) override;
  bool IsMultiColumnSortAllowed() const override
  { return m_allowMultiColumnSort; }
  void ToggleSortByColumn(int column) override;
#  if  wxUSE_DRAG_AND_DROP
  bool EnableDragSource(const wxDataFormat& format) override;
  bool EnableDropTarget(const wxDataFormat& format) override;
#  endif
  wxBorder GetDefaultBorder() const override;
  void EditItem(const wxDataViewItem& item, const wxDataViewColumn* column) override;
  bool SetHeaderAttr(const wxItemAttr& attr) override;
  bool SetAlternateRowColour(const wxColour& colour) override;
    // This method is specific to generic wxDataViewCtrl implementation and
    // should not be used in portable code.
  wxColour GetAlternateRowColour() const
  { return m_alternateRowColour; }
    // The returned pointer is null if the control has wxDV_NO_HEADER style.
    //
    // This method is only available in the generic versions.
  wxHeaderCtrl* GenericGetHeader() const;
protected:
  void EnsureVisibleRowCol(int row, int column);
    // Notice that row here may be invalid (i.e. >= GetRowCount()), this is not
    // an error and this function simply returns an invalid item in this case.
  wxDataViewItem GetItemByRow(unsigned int row) const;
  int GetRowByItem(const wxDataViewItem& item) const;
    // Mark the column as being used or not for sorting.
  void UseColumnForSorting(int idx);
  void DontUseColumnForSorting(int idx);
    // Return true if the given column is sorted
  bool IsColumnSorted(int idx) const;
    // Reset all columns currently used for sorting.
  void ResetAllSortColumns();
  void DoEnableSystemTheme(bool enable, wxWindow* window) override;
  void OnDPIChanged(wxDPIChangedEvent& event);
public:
    // returns the "best" width for the idx-th column
  unsigned int GetBestColumnWidth(int idx) const;
    // called by header window after reorder
  void ColumnMoved(wxDataViewColumn* col, unsigned int new_pos);
    // update the display after a change to an individual column
  void OnColumnChange(unsigned int idx);
    // update after the column width changes due to interactive resizing
  void OnColumnResized();
    // update after the column width changes because of e.g. title or bitmap
    // change, invalidates the column best width and calls OnColumnChange()
  void OnColumnWidthChange(unsigned int idx);
    // update after a change to the number of columns
  void OnColumnsCountChanged();
  wxWindow* GetMainWindow()
  { return (wxWindow*) m_clientArea; }
    // return the index of the given column in m_cols
  int GetColumnIndex(const wxDataViewColumn* column) const;
    // Return the index of the column having the given model index.
  int GetModelColumnIndex(unsigned int model_column) const;
    // return the column displayed at the given position in the control
  wxDataViewColumn* GetColumnAt(unsigned int pos) const;
  wxDataViewColumn* GetCurrentColumn() const override;
  void OnInternalIdle() override;
#  if  wxUSE_ACCESSIBILITY
  wxAccessible* CreateAccessible() override;
#  endif
private:
  wxDataViewItem DoGetCurrentItem() const override;
  void DoSetCurrentItem(const wxDataViewItem& item) override;
  void DoExpand(const wxDataViewItem& item, bool expandChildren) override;
  void InvalidateColBestWidths();
  void InvalidateColBestWidth(int idx);
  void UpdateColWidths();
  void DoClearColumns();
  wxVector<wxDataViewColumn*> m_cols;
    // cached column best widths information, values are for
    // respective columns from m_cols and the arrays have same size
  struct CachedColWidthInfo
  {
    CachedColWidthInfo()
      :  width(0), dirty(true) 
      {
      }
    int width;
    bool dirty;
  };
  wxVector<CachedColWidthInfo> m_colsBestWidths;
    // This indicates that at least one entry in m_colsBestWidths has 'dirty'
    // flag set. It's cheaper to check one flag in OnInternalIdle() than to
    // iterate over m_colsBestWidths to check if anything needs to be done.
  bool m_colsDirty;
  wxDataViewModelNotifier* m_notifier;
  wxDataViewMainWindow* m_clientArea;
  wxDataViewHeaderWindow* m_headerArea;
    // user defined color to draw row lines, may be invalid
  wxColour m_alternateRowColour;
    // columns indices used for sorting, empty if nothing is sorted
  wxVector<int> m_sortingColumnIdxs;
    // if true, allow sorting by more than one column
  bool m_allowMultiColumnSort;
  void OnSize(wxSizeEvent& event);
  wxSize GetSizeAvailableForScrollTarget(const wxSize& size) override;
    // we need to return a special WM_GETDLGCODE value to process just the
    // arrows but let the other navigation characters through
#  ifdef __WXMSW__
  WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override;
#  endif
  WX_FORWARD_TO_SCROLL_HELPER()
  wxDECLARE_DYNAMIC_CLASS(wxDataViewCtrl);
  wxDECLARE_NO_COPY_CLASS(wxDataViewCtrl);
  wxDECLARE_EVENT_TABLE();
};
#  if  wxUSE_ACCESSIBILITY
//-----------------------------------------------------------------------------
// wxDataViewCtrlAccessible
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxDataViewCtrlAccessible : public wxWindowAccessible
{
public:
  wxDataViewCtrlAccessible(wxDataViewCtrl* win);
  virtual ~wxDataViewCtrlAccessible()
  {
  }
  wxAccStatus HitTest(const wxPoint& pt, int* childId, wxAccessible** childObject) override;
  wxAccStatus GetLocation(wxRect& rect, int elementId) override;
  wxAccStatus Navigate(wxNavDir navDir, int fromId, int* toId, wxAccessible** toObject) override;
  wxAccStatus GetName(int childId, wxString* name) override;
  wxAccStatus GetChildCount(int* childCount) override;
  wxAccStatus GetChild(int childId, wxAccessible** child) override;
    // wxWindowAccessible::GetParent() implementation is enough.
    // virtual wxAccStatus GetParent(wxAccessible** parent) wxOVERRIDE;
  wxAccStatus DoDefaultAction(int childId) override;
  wxAccStatus GetDefaultAction(int childId, wxString* actionName) override;
  wxAccStatus GetDescription(int childId, wxString* description) override;
  wxAccStatus GetHelpText(int childId, wxString* helpText) override;
  wxAccStatus GetKeyboardShortcut(int childId, wxString* shortcut) override;
  wxAccStatus GetRole(int childId, wxAccRole* role) override;
  wxAccStatus GetState(int childId, long* state) override;
  wxAccStatus GetValue(int childId, wxString* strValue) override;
  wxAccStatus Select(int childId, wxAccSelectionFlags selectFlags) override;
  wxAccStatus GetFocus(int* childId, wxAccessible** child) override;
  wxAccStatus GetSelections(wxVariant* selections) override;
};
#  endif
#endif
