/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/collpaneg.h
// Purpose:     wxGenericCollapsiblePane
// Author:      Francesco Montorsi
// Modified by:
// Created:     8/10/2006
// Copyright:   (c) Francesco Montorsi
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_COLLAPSABLE_PANE_H_GENERIC_
#  define _WX_COLLAPSABLE_PANE_H_GENERIC_
// forward declared
class WXDLLIMPEXP_FWD_CORE wxCollapsibleHeaderCtrl;
#  include "wx/containr.h"
// ----------------------------------------------------------------------------
// wxGenericCollapsiblePane
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGenericCollapsiblePane : public wxNavigationEnabled<wxCollapsiblePaneBase>
{
public:
  wxGenericCollapsiblePane()
  {
 Init();   }
  wxGenericCollapsiblePane(wxWindow* parent, wxWindowID winid, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCP_DEFAULT_STYLE, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCollapsiblePaneNameStr))
  {

        Init();

        Create(parent, winid, label, pos, size, style, val, name);
      }
  virtual ~wxGenericCollapsiblePane();
  bool Create(wxWindow* parent, wxWindowID winid, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCP_DEFAULT_STYLE, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxCollapsiblePaneNameStr));
    // public wxCollapsiblePane API
  void Collapse(bool collapse = true) override;
  void SetLabel(const wxString& label) override;
  bool IsCollapsed() const override
  { return m_pPane==NULL || !m_pPane->IsShown(); }
  wxWindow* GetPane() const override
  { return m_pPane; }
  wxString GetLabel() const override;
  bool Layout() override;
    // for the generic collapsible pane only:
  wxControl* GetControlWidget() const
  { return (wxControl*)m_pButton; }
    // implementation only, don't use
  void OnStateChange(const wxSize& sizeNew);
protected:
    // overridden methods
  wxSize DoGetBestClientSize() const override;
  int GetBorder() const;
    // child controls
  wxCollapsibleHeaderCtrl* m_pButton;
  wxWindow* m_pPane;
  wxSizer* m_sz;
private:
  void Init();
    // event handlers
  void OnButton(wxCommandEvent& ev);
  void OnSize(wxSizeEvent& ev);
  wxDECLARE_DYNAMIC_CLASS(wxGenericCollapsiblePane);
  wxDECLARE_EVENT_TABLE();
};
#endif
