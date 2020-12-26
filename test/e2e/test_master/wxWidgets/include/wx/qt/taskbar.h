/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/taskbar.h
// Author:      Peter Most
// Copyright:   (c) Peter Most
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_TASKBAR_H_
#  define _WX_QT_TASKBAR_H_
class QSystemTrayIcon;
class WXDLLIMPEXP_ADV wxTaskBarIcon : public wxTaskBarIconBase
{
public:
  wxTaskBarIcon(wxTaskBarIconType iconType = wxTBI_DEFAULT_TYPE);
  virtual ~wxTaskBarIcon();
    // Accessors
  bool IsOk() const
  { return false; }
  bool IsIconInstalled() const
  { return false; }
    // Operations
  bool SetIcon(const wxIcon& icon, const wxString& tooltip = wxEmptyString) override;
  bool RemoveIcon() override;
  bool PopupMenu(wxMenu* menu) override;
private:
  QSystemTrayIcon* m_qtSystemTrayIcon;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxTaskBarIcon);
};
#endif
