/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/filedirpicker.h
// Purpose:     wxFileButton, wxDirButton header
// Author:      Francesco Montorsi
// Modified by:
// Created:     14/4/2006
// Copyright:   (c) Francesco Montorsi
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_FILEPICKER_H_
#  define _WX_GTK_FILEPICKER_H_
// since GtkColorButton is available only for GTK+ >= 2.4,
// we need to use generic versions if we detect (at runtime)
// that GTK+ < 2.4
#  include "wx/generic/filepickerg.h"
//-----------------------------------------------------------------------------
// wxFileButton and wxDirButton shared code
// (cannot be a base class since they need to derive from wxGenericFileButton
//  and from wxGenericDirButton classes !)
//-----------------------------------------------------------------------------
#  define FILEDIRBTN_OVERRIDES	virtual wxWindow *GetDialogParent() wxOVERRIDE                            \
    {                                                                         \
        return NULL;                                                          \
    }                                                                         \
                                                                              \
    /* even if wx derive from wxGenericFileButton, i.e. from wxButton, our */ \
    /* native GTK+ widget does not derive from GtkButton thus *all* uses   */ \
    /* GTK_BUTTON(m_widget) macro done by wxButton must be bypassed to     */ \
    /* avoid bunch of GTK+ warnings like:                                  */ \
    /*      invalid cast from `GtkFileChooserButton' to  `GtkButton'       */ \
    /* so, override wxButton::GTKGetWindow and return NULL as GTK+ doesn't */ \
    /* give us access to the internal GdkWindow of a GtkFileChooserButton  */ \
protected:                                                                    \
    virtual GdkWindow *                                                       \
    GTKGetWindow(wxArrayGdkWindows& WXUNUSED(windows)) const wxOVERRIDE       \
        { return NULL; }
//-----------------------------------------------------------------------------
// wxFileButton
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxFileButton : public wxGenericFileButton
{
public:
  wxFileButton()
  {
    Init();
  }
  wxFileButton(wxWindow* parent, wxWindowID id, const wxString& label = wxASCII_STR(wxFilePickerWidgetLabel), const wxString& path = wxEmptyString, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxString& wildcard = wxASCII_STR(wxFileSelectorDefaultWildcardStr), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxFILEBTN_DEFAULT_STYLE, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxFilePickerWidgetNameStr))
  {
    Init();
    m_pickerStyle = style;
    Create(parent, id, label, path, message, wildcard, pos, size, style, validator, name);
  }
  virtual ~wxFileButton();
public:
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label = wxASCII_STR(wxFilePickerWidgetLabel), const wxString& path = wxEmptyString, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxString& wildcard = wxASCII_STR(wxFileSelectorDefaultWildcardStr), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxFilePickerWidgetNameStr));
    // event handler for the click
  void OnDialogOK(wxCommandEvent&);
  void SetPath(const wxString& str) override;
  void SetInitialDirectory(const wxString& dir) override;
    // see macro defined above
protected:
  wxDialog* m_dialog;
  void DoApplyWidgetStyle(GtkRcStyle*) override;
private:
    // common part of all ctors
  void Init()
  {
    m_dialog = NULL;
  }
  wxDECLARE_DYNAMIC_CLASS(wxFileButton);
};
//-----------------------------------------------------------------------------
// wxDirButton
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxDirButton : public wxGenericDirButton
{
public:
  wxDirButton()
  {
    Init();
  }
  wxDirButton(wxWindow* parent, wxWindowID id, const wxString& label = wxASCII_STR(wxFilePickerWidgetLabel), const wxString& path = wxEmptyString, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDIRBTN_DEFAULT_STYLE, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxFilePickerWidgetNameStr))
  {
    Init();
    m_pickerStyle = style;
    Create(parent, id, label, path, message, wxEmptyString, pos, size, style, validator, name);
  }
  virtual ~wxDirButton();
public:
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label = wxASCII_STR(wxFilePickerWidgetLabel), const wxString& path = wxEmptyString, const wxString& message = wxASCII_STR(wxFileSelectorPromptStr), const wxString& wildcard = wxASCII_STR(wxFileSelectorDefaultWildcardStr), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxFilePickerWidgetNameStr));
    // GtkFileChooserButton does not support GTK_FILE_CHOOSER_CREATE_FOLDER
    // thus we must ensure that the wxDD_DIR_MUST_EXIST style was given
  long GetDialogStyle() const override
  {
    return (wxGenericDirButton::GetDialogStyle() | wxDD_DIR_MUST_EXIST);
  }
  void SetPath(const wxString& str) override;
  void SetInitialDirectory(const wxString& dir) override;
    // see macro defined above
protected:
  wxDialog* m_dialog;
  void DoApplyWidgetStyle(GtkRcStyle*) override;
public:
  bool m_bIgnoreNextChange;
  void GTKUpdatePath(const char* gtkpath);
private:
  void Init()
  {
    m_dialog = NULL;
    m_bIgnoreNextChange = false;
  }
  wxDECLARE_DYNAMIC_CLASS(wxDirButton);
};
#  undef FILEDIRBTN_OVERRIDES
#endif
