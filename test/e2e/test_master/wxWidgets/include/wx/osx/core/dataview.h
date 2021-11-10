/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/core/dataview.h
// Purpose:     wxDataViewCtrl native implementation header for OSX
// Author:
// Copyright:   (c) 2009
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_DATAVIEWCTRL_CORE_H_
#  define _WX_DATAVIEWCTRL_CORE_H_
#  include "wx/dataview.h"
typedef wxWidgetImpl wxWidgetImplType;
// ---------------------------------------------------------
// Helper functions for dataview implementation on OSX
// ---------------------------------------------------------
wxWidgetImplType* CreateDataView(wxWindowMac* wxpeer, wxWindowMac* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, long extraStyle);
wxString ConcatenateDataViewItemValues(const wxDataViewCtrl* dataViewCtrlPtr, const wxDataViewItem& dataViewItem);
                                                                                                                   // and item TAB separated into a string and returns it

// ---------------------------------------------------------
// wxDataViewWidgetImpl
// Common interface of the native dataview implementation
// for the carbon and cocoa environment.
// ATTENTION
//  All methods assume that the passed column pointers are
//  valid (unless a NULL pointer is explicitly allowed
//  to be passed)!
// ATTENTION
// ---------------------------------------------------------
class WXDLLIMPEXP_CORE wxDataViewWidgetImpl
{
public:
 //
 // constructors / destructor
 //
  virtual ~wxDataViewWidgetImpl()
  {
  }
 //
 // column related methods
 //
  virtual bool ClearColumns() = 0;
  virtual bool DeleteColumn(wxDataViewColumn* columnPtr) = 0;
  virtual void DoSetExpanderColumn(const wxDataViewColumn* columnPtr) = 0;
  virtual wxDataViewColumn* GetColumn(unsigned int pos) const = 0;
  virtual int GetColumnPosition(const wxDataViewColumn* columnPtr) const = 0;
  virtual bool InsertColumn(unsigned int pos, wxDataViewColumn* columnPtr) = 0;
                                                                                                    // the method can assume that the column's owner is already set
  virtual void FitColumnWidthToContent(unsigned int pos) = 0;
 //
 // item related methods
 //
  virtual bool Add(const wxDataViewItem& parent, const wxDataViewItem& item) = 0;
  virtual bool Add(const wxDataViewItem& parent, const wxDataViewItemArray& items) = 0;
  virtual void Collapse(const wxDataViewItem& item) = 0;
  virtual void EnsureVisible(const wxDataViewItem& item, const wxDataViewColumn* columnPtr) = 0;
  virtual unsigned int GetCount() const = 0;
  virtual int GetCountPerPage() const = 0;
  virtual wxRect GetRectangle(const wxDataViewItem& item, const wxDataViewColumn* columnPtr) = 0;
  virtual wxDataViewItem GetTopItem() const = 0;
  virtual bool IsExpanded(const wxDataViewItem& item) const = 0;
  virtual bool Reload() = 0;
  virtual bool Remove(const wxDataViewItem& parent) = 0;
  virtual bool Update(const wxDataViewColumn* columnPtr) = 0;
  virtual bool Update(const wxDataViewItem& parent, const wxDataViewItem& item) = 0;
  virtual bool Update(const wxDataViewItem& parent, const wxDataViewItemArray& items) = 0;
 //
 // model related methods
 //
  virtual bool AssociateModel(wxDataViewModel* model) = 0;
 //
 // selection related methods
 //
  virtual wxDataViewItem GetCurrentItem() const = 0;
  virtual void SetCurrentItem(const wxDataViewItem& item) = 0;
  virtual wxDataViewColumn* GetCurrentColumn() const = 0;
  virtual int GetSelectedItemsCount() const = 0;
  virtual int GetSelections(wxDataViewItemArray& sel) const = 0;
  virtual bool IsSelected(const wxDataViewItem& item) const = 0;
  virtual void Select(const wxDataViewItem& item) = 0;
  virtual void Select(const wxDataViewItemArray& items) = 0;
  virtual void SelectAll() = 0;
  virtual void Unselect(const wxDataViewItem& item) = 0;
  virtual void UnselectAll() = 0;
 //
 // sorting related methods
 //
  virtual wxDataViewColumn* GetSortingColumn() const = 0;
  virtual void Resort() = 0;
 //
 // other methods
 //
  virtual void DoSetIndent(int indent) = 0;
  virtual void DoExpand(const wxDataViewItem& item, bool expandChildren) = 0;
  virtual void HitTest(const wxPoint& point, wxDataViewItem& item, wxDataViewColumn*& columnPtr) const = 0;
  virtual void SetRowHeight(int height) = 0;
  virtual void SetRowHeight(const wxDataViewItem& item, unsigned int height) = 0;
  virtual void OnSize() = 0;
  virtual void StartEditor(const wxDataViewItem& item, unsigned int column) = 0;
};
#endif
