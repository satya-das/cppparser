/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/filedlg.h
// Author:      Sean D'Epagnier
// Copyright:   (c) 2014 Sean D'Epagnier
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_FILEDLG_H_
#  define _WX_QT_FILEDLG_H_
class QFileDialog;
class WXDLLIMPEXP_CORE wxFileDialog : public wxFileDialogBase
{
public:
  wxFileDialog()
  {
   }
  wxFileDialog(wxWindow* parent, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxString& defaultDir = wxEmptyString, const wxString& defaultFile = wxEmptyString, const wxString& wildCard = wxASCII_STR(wxFileSelectorDefaultWildcardStr), long style = wxFD_DEFAULT_STYLE, const wxPoint& pos = wxDefaultPosition, const wxSize& sz = wxDefaultSize, const wxString& name = wxASCII_STR(wxFileDialogNameStr));
  bool Create(wxWindow* parent, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxString& defaultDir = wxEmptyString, const wxString& defaultFile = wxEmptyString, const wxString& wildCard = wxASCII_STR(wxFileSelectorDefaultWildcardStr), long style = wxFD_DEFAULT_STYLE, const wxPoint& pos = wxDefaultPosition, const wxSize& sz = wxDefaultSize, const wxString& name = wxASCII_STR(wxFileDialogNameStr));
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
  bool SupportsExtraControl() const override
  {
    return true;
  }
  virtual QFileDialog* GetQFileDialog() const;
  wxDECLARE_DYNAMIC_CLASS(wxFileDialog);
};
#endif
