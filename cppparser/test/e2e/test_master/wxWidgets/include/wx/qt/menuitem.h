/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/menuitem.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_MENUITEM_H_
#  define _WX_QT_MENUITEM_H_
#  include "wx/menuitem.h"
#  include "wx/bitmap.h"
class QAction;
class wxQtAction;
class WXDLLIMPEXP_FWD_CORE wxMenu;
class WXDLLIMPEXP_CORE wxMenuItem : public wxMenuItemBase
{
public:
  wxMenuItem(wxMenu* parentMenu = NULL, int id = wxID_SEPARATOR, const wxString& text = wxEmptyString, const wxString& help = wxEmptyString, wxItemKind kind = wxITEM_NORMAL, wxMenu* subMenu = NULL);
  void SetItemLabel(const wxString& str) override;
  void SetCheckable(bool checkable) override;
  void Enable(bool enable = true) override;
  bool IsEnabled() const override;
  void Check(bool check = true) override;
  bool IsChecked() const override;
  virtual void SetBitmap(const wxBitmap& bitmap);
  virtual const wxBitmap& GetBitmap() const
  {
    return m_bitmap;
  }
  virtual QAction* GetHandle() const;
private:
    // Qt is using an action instead of a menu item.
  wxQtAction* m_qtAction;
  wxBitmap m_bitmap;
  wxDECLARE_DYNAMIC_CLASS( wxMenuItem );
};
#endif
