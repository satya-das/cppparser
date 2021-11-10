/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/menu.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_MENU_H_
#  define _WX_QT_MENU_H_
class QMenu;
class QMenuBar;
class WXDLLIMPEXP_CORE wxMenu : public wxMenuBase
{
public:
  wxMenu(long style = 0);
  wxMenu(const wxString& title, long style = 0);
  virtual QMenu* GetHandle() const;
protected:
  wxMenuItem* DoAppend(wxMenuItem* item) override;
  wxMenuItem* DoInsert(size_t pos, wxMenuItem* item) override;
  wxMenuItem* DoRemove(wxMenuItem* item) override;
private:
  QMenu* m_qtMenu;
  wxDECLARE_DYNAMIC_CLASS(wxMenu);
};
class WXDLLIMPEXP_CORE wxMenuBar : public wxMenuBarBase
{
public:
  wxMenuBar();
  wxMenuBar(long style);
  wxMenuBar(size_t n, wxMenu* menus[], const wxString titles[], long style = 0);
  bool Append(wxMenu* menu, const wxString& title) override;
  bool Insert(size_t pos, wxMenu* menu, const wxString& title) override;
  wxMenu* Remove(size_t pos) override;
  void EnableTop(size_t pos, bool enable) override;
  bool IsEnabledTop(size_t pos) const override;
  void SetMenuLabel(size_t pos, const wxString& label) override;
  wxString GetMenuLabel(size_t pos) const override;
  QMenuBar* GetQMenuBar() const
  {
    return m_qtMenuBar;
  }
  QWidget* GetHandle() const override;
  void Attach(wxFrame* frame) override;
  void Detach() override;
private:
  QMenuBar* m_qtMenuBar;
  wxDECLARE_DYNAMIC_CLASS(wxMenuBar);
};
#endif
