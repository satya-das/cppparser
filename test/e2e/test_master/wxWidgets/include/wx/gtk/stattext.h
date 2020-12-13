/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/stattext.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_STATTEXT_H_
#  define _WX_GTK_STATTEXT_H_
//-----------------------------------------------------------------------------
// wxStaticText
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxStaticText : public wxStaticTextBase
{
public:
  wxStaticText();
  wxStaticText(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticTextNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticTextNameStr));
  void SetLabel(const wxString& label) override;
  bool SetFont(const wxFont& font) override;
  static wxVisualAttributes GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);
    // implementation
    // --------------
protected:
  bool GTKWidgetNeedsMnemonic() const override;
  void GTKWidgetDoSetMnemonic(GtkWidget* w) override;
  wxSize DoGetBestSize() const override;
  wxString WXGetVisibleLabel() const override;
  void WXSetVisibleLabel(const wxString& str) override;
#  if  wxUSE_MARKUP
  bool DoSetLabelMarkup(const wxString& markup) override;
#  endif
private:
    // Common part of SetLabel() and DoSetLabelMarkup().
  typedef void (*GTKLabelSetter) (GtkLabel*, const wxString&);
  void GTKDoSetLabel(GTKLabelSetter setter, const wxString& label);
  wxDECLARE_DYNAMIC_CLASS(wxStaticText);
};
#endif
    // _WX_GTK_STATTEXT_H_
