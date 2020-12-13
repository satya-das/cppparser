/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/radiobox.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_RADIOBOX_H_
#  define _WX_GTK_RADIOBOX_H_
#  include "wx/bitmap.h"
class WXDLLIMPEXP_FWD_CORE wxGTKRadioButtonInfo;
#  include "wx/list.h"
WX_DECLARE_EXPORTED_LIST(wxGTKRadioButtonInfo, wxRadioBoxButtonsInfoList);
//-----------------------------------------------------------------------------
// wxRadioBox
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxRadioBox : public wxControl, public wxRadioBoxBase
{
public:
    // ctors and dtor
  wxRadioBox()
  {
  }
  wxRadioBox(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = (const wxString*) NULL, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr))
  {
    Create(parent, id, title, pos, size, n, choices, majorDim, style, val, name);
  }
  wxRadioBox(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr))
  {
    Create(parent, id, title, pos, size, choices, majorDim, style, val, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = (const wxString*) NULL, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr));
  virtual ~wxRadioBox();
    // implement wxItemContainerImmutable methods
  unsigned int GetCount() const override;
  wxString GetString(unsigned int n) const override;
  void SetString(unsigned int n, const wxString& s) override;
  void SetSelection(int n) override;
  int GetSelection() const override;
    // implement wxRadioBoxBase methods
  bool Show(unsigned int n, bool show = true) override;
  bool Enable(unsigned int n, bool enable = true) override;
  bool IsItemEnabled(unsigned int n) const override;
  bool IsItemShown(unsigned int n) const override;
    // override some base class methods to operate on radiobox itself too
  bool Show(bool show = true) override;
  bool Enable(bool enable = true) override;
  void SetLabel(const wxString& label) override;
  static wxVisualAttributes GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);
  int GetItemFromPoint(const wxPoint& pt) const override;
#  if  wxUSE_HELP
    // override virtual wxWindow::GetHelpTextAtPoint to use common platform independent
    // wxRadioBoxBase::DoGetHelpTextAtPoint from the platform independent
    // base class-interface wxRadioBoxBase.
  wxString GetHelpTextAtPoint(const wxPoint& pt, wxHelpEvent::Origin origin) const override
  {
    return wxRadioBoxBase::DoGetHelpTextAtPoint(this, pt, origin);
  }
#  endif
    // implementation
    // --------------
  void GtkDisableEvents();
  void GtkEnableEvents();
#  if  wxUSE_TOOLTIPS
  void GTKApplyToolTip(const char* tip) override;
#  endif
  wxRadioBoxButtonsInfoList m_buttonsInfo;
protected:
  wxBorder GetDefaultBorder() const override
  {
    return wxBORDER_NONE;
  }
#  if  wxUSE_TOOLTIPS
  void DoSetItemToolTip(unsigned int n, wxToolTip* tooltip) override;
#  endif
  void DoApplyWidgetStyle(GtkRcStyle* style) override;
  GdkWindow* GTKGetWindow(wxArrayGdkWindows& windows) const override;
  void DoEnable(bool enable) override;
  bool GTKNeedsToFilterSameWindowFocus() const override
  {
    return true;
  }
  bool GTKWidgetNeedsMnemonic() const override;
  void GTKWidgetDoSetMnemonic(GtkWidget* w) override;
  wxDECLARE_DYNAMIC_CLASS(wxRadioBox);
};
#endif
