/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/dataview.h
// Purpose:     wxDataViewCtrl GTK+2 implementation header
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTKDATAVIEWCTRL_H_
#  define _WX_GTKDATAVIEWCTRL_H_
#  include "wx/list.h"
class WXDLLIMPEXP_FWD_CORE wxDataViewCtrlInternal;
struct _GtkTreePath;
// ---------------------------------------------------------
// wxDataViewColumn
// ---------------------------------------------------------
class WXDLLIMPEXP_CORE wxDataViewColumn : public wxDataViewColumnBase
{
public:
  wxDataViewColumn(const wxString& title, wxDataViewRenderer* renderer, unsigned int model_column, int width = wxDVC_DEFAULT_WIDTH, wxAlignment align = wxALIGN_CENTER, int flags = wxDATAVIEW_COL_RESIZABLE);
  wxDataViewColumn(const wxBitmap& bitmap, wxDataViewRenderer* renderer, unsigned int model_column, int width = wxDVC_DEFAULT_WIDTH, wxAlignment align = wxALIGN_CENTER, int flags = wxDATAVIEW_COL_RESIZABLE);
    // setters:
  void SetTitle(const wxString& title) override;
  void SetBitmap(const wxBitmap& bitmap) override;
  void SetOwner(wxDataViewCtrl* owner) override;
  void SetAlignment(wxAlignment align) override;
  void SetSortable(bool sortable) override;
  void SetSortOrder(bool ascending) override;
  void UnsetAsSortKey() override;
  void SetResizeable(bool resizable) override;
  void SetHidden(bool hidden) override;
  void SetMinWidth(int minWidth) override;
  void SetWidth(int width) override;
  void SetReorderable(bool reorderable) override;
  void SetFlags(int flags) override
  { SetIndividualFlags(flags); }
    // getters:
  wxString GetTitle() const override;
  wxAlignment GetAlignment() const override;
  bool IsSortable() const override;
  bool IsSortOrderAscending() const override;
  bool IsSortKey() const override;
  bool IsResizeable() const override;
  bool IsHidden() const override;
  int GetWidth() const override;
  int GetMinWidth() const override;
  bool IsReorderable() const override;
  int GetFlags() const override
  { return GetFromIndividualFlags(); }
    // implementation
  GtkWidget* GetGtkHandle() const
  { return m_column; }
private:
    // holds the GTK handle
  GtkWidget* m_column;
    // holds GTK handles for title/bitmap in the header
  GtkWidget* m_image;
  GtkWidget* m_label;
    // delayed connection to mouse events
  friend class wxDataViewCtrl;
  void OnInternalIdle();
  bool m_isConnected;
  void Init(wxAlignment align, int flags, int width);
};
WX_DECLARE_LIST_WITH_DECL(wxDataViewColumn, wxDataViewColumnList,
                          class WXDLLIMPEXP_CORE);
// ---------------------------------------------------------
// wxDataViewCtrl
// ---------------------------------------------------------
class WXDLLIMPEXP_CORE wxDataViewCtrl : public wxDataViewCtrlBase
{
public:
  wxDataViewCtrl()
  {

        Init();
      }
  wxDataViewCtrl(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxDataViewCtrlNameStr))
  {

        Init();

        Create(parent, id, pos, size, style, validator, name);
      }
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxDataViewCtrlNameStr));
  virtual ~wxDataViewCtrl();
  bool AssociateModel(wxDataViewModel* model) override;
  bool PrependColumn(wxDataViewColumn* col) override;
  bool AppendColumn(wxDataViewColumn* col) override;
  bool InsertColumn(unsigned int pos, wxDataViewColumn* col) override;
  unsigned int GetColumnCount() const override;
  wxDataViewColumn* GetColumn(unsigned int pos) const override;
  bool DeleteColumn(wxDataViewColumn* column) override;
  bool ClearColumns() override;
  int GetColumnPosition(const wxDataViewColumn* column) const override;
  wxDataViewColumn* GetSortingColumn() const override;
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
  void EditItem(const wxDataViewItem& item, const wxDataViewColumn* column) override;
  void Collapse(const wxDataViewItem& item) override;
  bool IsExpanded(const wxDataViewItem& item) const override;
  bool EnableDragSource(const wxDataFormat& format) override;
  bool EnableDropTarget(const wxDataFormat& format) override;
  wxDataViewColumn* GetCurrentColumn() const override;
  wxDataViewItem GetTopItem() const override;
  int GetCountPerPage() const override;
  static wxVisualAttributes GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);
  wxWindow* GetMainWindow()
  { return (wxWindow*) this; }
  GtkWidget* GtkGetTreeView()
  { return m_treeview; }
  wxDataViewCtrlInternal* GtkGetInternal()
  { return m_internal; }
    // Convert GTK path to our item. Returned item may be invalid if get_iter()
    // failed.
  wxDataViewItem GTKPathToItem(struct _GtkTreePath* path) const;
    // Return wxDataViewColumn matching the given GtkTreeViewColumn.
    //
    // If the input argument is NULL, return NULL too. Otherwise we must find
    // the matching column and assert if we didn't.
  wxDataViewColumn* GTKColumnToWX(GtkTreeViewColumn* gtk_col) const;
  void OnInternalIdle() override;
  int GTKGetUniformRowHeight() const
  { return m_uniformRowHeight; }
    // Simple RAII helper for disabling selection events during its lifetime.
  class SelectionEventsSuppressor
  {
  public:
    explicit SelectionEventsSuppressor(wxDataViewCtrl* ctrl)
      :  m_ctrl(ctrl)
        
      {

            m_ctrl->GtkDisableSelectionEvents();
              }
    ~SelectionEventsSuppressor()
    {

            m_ctrl->GtkEnableSelectionEvents();
            }
  private:
    wxDataViewCtrl* const m_ctrl;
  };
protected:
  void DoSetExpanderColumn() override;
  void DoSetIndent() override;
  void DoExpand(const wxDataViewItem& item, bool expandChildren) override;
  void DoApplyWidgetStyle(GtkRcStyle* style) override;
  GdkWindow* GTKGetWindow(wxArrayGdkWindows& windows) const override;
private:
  void Init();
  wxDataViewItem DoGetCurrentItem() const override;
  void DoSetCurrentItem(const wxDataViewItem& item) override;
  friend class wxDataViewCtrlDCImpl;
  friend class wxDataViewColumn;
  friend class wxDataViewCtrlInternal;
  GtkWidget* m_treeview;
  wxDataViewCtrlInternal* m_internal;
  wxDataViewColumnList m_cols;
  wxDataViewItem m_ensureVisibleDefered;
    // By default this is set to -1 and the height of the rows is determined by
    // GetRect() methods of the renderers but this can be set to a positive
    // value to force the height of all rows to the given value.
  int m_uniformRowHeight;
  void AddChildGTK(wxWindowGTK* child) override;
  void GtkEnableSelectionEvents();
  void GtkDisableSelectionEvents();
  wxDECLARE_DYNAMIC_CLASS(wxDataViewCtrl);
  wxDECLARE_NO_COPY_CLASS(wxDataViewCtrl);
};
#endif
