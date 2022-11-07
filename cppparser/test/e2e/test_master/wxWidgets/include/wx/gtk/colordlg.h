/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/colordlg.h
// Purpose:     wxColourDialog
// Author:      Vaclav Slavik
// Modified by:
// Created:     2004/06/04
// Copyright:   (c) Vaclav Slavik, 2004
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_COLORDLG_H_
#  define _WX_GTK_COLORDLG_H_
#  include "wx/dialog.h"
class WXDLLIMPEXP_CORE wxColourDialog : public wxDialog
{
public:
  wxColourDialog()
  {
  }
  wxColourDialog(wxWindow* parent, const wxColourData* data = NULL);
  virtual ~wxColourDialog()
  {
  }
  bool Create(wxWindow* parent, const wxColourData* data = NULL);
  wxColourData& GetColourData()
  {
    return m_data;
  }
  int ShowModal() override;
protected:
    // implement some base class methods to do nothing to avoid asserts and
    // GTK warnings, since this is not a real wxDialog.
  void DoSetSize(int, int, int, int, int = wxSIZE_AUTO) override
  {
  }
  void DoMoveWindow(int, int, int, int) override
  {
  }
    // copy data between the dialog and m_colourData:
  void ColourDataToDialog();
  void DialogToColourData();
  wxColourData m_data;
  wxDECLARE_DYNAMIC_CLASS(wxColourDialog);
};
#endif
