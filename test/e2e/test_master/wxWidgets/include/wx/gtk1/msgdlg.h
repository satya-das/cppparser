/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk1/msgdlg.h
// Purpose:     wxMessageDialog for GTK+2
// Author:      Vaclav Slavik
// Modified by:
// Created:     2003/02/28
// Copyright:   (c) Vaclav Slavik, 2003
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef __MSGDLG_H__
#  define __MSGDLG_H__
#  include "wx/defs.h"
#  include "wx/dialog.h"
// type is an 'or' (|) of wxOK, wxCANCEL, wxYES_NO
// Returns wxYES/NO/OK/CANCEL
WXDLLIMPEXP_CORE extern const wxChar wxMessageBoxCaptionStr[];
class WXDLLIMPEXP_CORE wxMessageDialog : public wxDialog, public wxMessageDialogBase
{
public:
  wxMessageDialog(wxWindow* parent, const wxString& message, const wxString& caption = wxMessageBoxCaptionStr, long style = wxOK | wxCENTRE, const wxPoint& pos = wxDefaultPosition);
  virtual ~wxMessageDialog();
  int ShowModal();
  virtual bool Show(bool = true)
  {
 return false;
  }
protected:
    // implement some base class methods to do nothing to avoid asserts and
    // GTK warnings, since this is not a real wxDialog.
  virtual void DoSetSize(int, int, int, int, int = wxSIZE_AUTO)
  {
  }
  virtual void DoMoveWindow(int, int, int, int)
  {
  }
private:
  wxString m_caption;
  wxString m_message;
  wxDECLARE_DYNAMIC_CLASS(wxMessageDialog);
};
#endif
