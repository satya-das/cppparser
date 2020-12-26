///////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/menuitem.h
// Purpose:     wxMenuItem class
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTKMENUITEM_H_
#  define _WX_GTKMENUITEM_H_
#  include "wx/bitmap.h"
//-----------------------------------------------------------------------------
// wxMenuItem
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxMenuItem : public wxMenuItemBase
{
public:
  wxMenuItem(wxMenu* parentMenu = NULL, int id = wxID_SEPARATOR, const wxString& text = wxEmptyString, const wxString& help = wxEmptyString, wxItemKind kind = wxITEM_NORMAL, wxMenu* subMenu = NULL);
  virtual ~wxMenuItem();
    // implement base class virtuals
  void SetItemLabel(const wxString& str) override;
  void Enable(bool enable = true) override;
  void Check(bool check = true) override;
  bool IsChecked() const override;
  virtual void SetBitmap(const wxBitmap& bitmap);
  virtual const wxBitmap& GetBitmap() const
  { return m_bitmap; }
    // implementation
  void SetMenuItem(GtkWidget* menuItem);
  GtkWidget* GetMenuItem() const
  { return m_menuItem; }
  void SetGtkLabel();
#  if  WXWIN_COMPATIBILITY_2_8
    // compatibility only, don't use in new code
#  endif
private:
  wxBitmap m_bitmap;
  GtkWidget* m_menuItem;
  wxDECLARE_DYNAMIC_CLASS(wxMenuItem);
};
#endif
