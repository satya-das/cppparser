/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/filedlg.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTKFILEDLG_H_
#  define _WX_GTKFILEDLG_H_
#  include "wx/gtk/filectrl.h"
//-------------------------------------------------------------------------
// wxFileDialog
//-------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxFileDialog : public wxFileDialogBase
{
public:
  wxFileDialog()
  {
   }
  wxFileDialog(wxWindow* parent, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxString& defaultDir = wxEmptyString, const wxString& defaultFile = wxEmptyString, const wxString& wildCard = wxASCII_STR(wxFileSelectorDefaultWildcardStr), long style = wxFD_DEFAULT_STYLE, const wxPoint& pos = wxDefaultPosition, const wxSize& sz = wxDefaultSize, const wxString& name = wxASCII_STR(wxFileDialogNameStr));
  bool Create(wxWindow* parent, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxString& defaultDir = wxEmptyString, const wxString& defaultFile = wxEmptyString, const wxString& wildCard = wxASCII_STR(wxFileSelectorDefaultWildcardStr), long style = wxFD_DEFAULT_STYLE, const wxPoint& pos = wxDefaultPosition, const wxSize& sz = wxDefaultSize, const wxString& name = wxASCII_STR(wxFileDialogNameStr));
  virtual ~wxFileDialog();
  wxString GetPath() const override;
  void GetPaths(wxArrayString& paths) const override;
  wxString GetFilename() const override;
  void GetFilenames(wxArrayString& files) const override;
  int GetFilterIndex() const override;
  void SetMessage(const wxString& message) override;
  void SetPath(const wxString& path) override;
  void SetDirectory(const wxString& dir) override;
  void SetFilename(const wxString& name) override;
  void SetWildcard(const wxString& wildCard) override;
  void SetFilterIndex(int filterIndex) override;
  int ShowModal() override;
  bool SupportsExtraControl() const override
  {
    return true;
  }
    // Implementation only.
  void GTKSelectionChanged(const wxString& filename);
protected:
    // override this from wxTLW since the native
    // form doesn't have any m_wxwindow
  void DoSetSize(int x, int y, int width, int height, int sizeFlags = wxSIZE_AUTO) override;
private:
  void OnFakeOk(wxCommandEvent& event);
  void OnSize(wxSizeEvent&);
  void AddChildGTK(wxWindowGTK* child) override;
  wxGtkFileChooser m_fc;
  wxDECLARE_DYNAMIC_CLASS(wxFileDialog);
  wxDECLARE_EVENT_TABLE();
};
#endif
