/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/srchctrl.h
// Purpose:     wxSearchCtrl class - native
// Author:      Kettab Ali
// Created:     2019-12-23
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_SEARCHCTRL_H_
#  define _WX_GTK_SEARCHCTRL_H_
#  if  wxUSE_SEARCHCTRL
// ----------------------------------------------------------------------------
// wxSearchCtrl
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxSearchCtrl : public wxSearchCtrlBase
{
public:
    // creation
    // --------
  wxSearchCtrl()
    : wxSearchCtrlBase()
  {
    Init();
  }
  wxSearchCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxSearchCtrlNameStr))
    : wxSearchCtrlBase()
  {
    Init();
    Create(parent, id, value, pos, size, style, validator, name);
  }
  virtual ~wxSearchCtrl();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxSearchCtrlNameStr));
#    if  wxUSE_MENUS
    // get/set search button menu
    // --------------------------
  void SetMenu(wxMenu* menu) override;
  wxMenu* GetMenu() override;
#    endif
    // get/set search options
    // ----------------------
  void ShowSearchButton(bool show) override;
  bool IsSearchButtonVisible() const override;
  void ShowCancelButton(bool show) override;
  bool IsCancelButtonVisible() const override;
  void SetDescriptiveText(const wxString& text) override;
  wxString GetDescriptiveText() const override;
  void Clear() override;
#    if  wxUSE_MENUS
  void PopupSearchMenu();
#    endif
private:
    // From wxTextEntry:
  GtkEditable* GetEditable() const override;
  void Init();
  void GTKCreateSearchEntryWidget();
    // Event handlers
  void OnChar(wxKeyEvent& event);
  void OnText(wxCommandEvent& event);
  void OnTextEnter(wxCommandEvent& event);
  bool HasMenu() const
  {
#    if  wxUSE_MENUS
    return m_menu != NULL;
#    else 
    return false;
#    endif
  }
private:
  GtkEntry* GetEntry() const override
  {
    return m_entry;
  }
  GtkEntry* m_entry;
#    if  wxUSE_MENUS
  wxMenu* m_menu;
#    endif
  bool m_cancelButtonVisible;
  wxDECLARE_DYNAMIC_CLASS(wxSearchCtrl);
  wxDECLARE_EVENT_TABLE();
};
#  endif
#endif
