///////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/dvrenderers.h
// Purpose:     All generic wxDataViewCtrl renderer classes
// Author:      Robert Roebling, Vadim Zeitlin
// Created:     2009-11-07 (extracted from wx/generic/dataview.h)
// Copyright:   (c) 2006 Robert Roebling
//              (c) 2009 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GENERIC_DVRENDERERS_H_
#  define _WX_GENERIC_DVRENDERERS_H_
// ---------------------------------------------------------
// wxDataViewCustomRenderer
// ---------------------------------------------------------
class WXDLLIMPEXP_ADV wxDataViewCustomRenderer : public wxDataViewRenderer
{
public:
  static wxString GetDefaultType()
  {
    return wxS("string");
  }
  wxDataViewCustomRenderer(const wxString& varianttype = GetDefaultType(), wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT, int align = wxDVR_DEFAULT_ALIGNMENT);
    // see the explanation of the following WXOnXXX() methods in wx/generic/dvrenderer.h
  bool WXActivateCell(const wxRect& cell, wxDataViewModel* model, const wxDataViewItem& item, unsigned int col, const wxMouseEvent* mouseEvent) override
  {
    return ActivateCell(cell, model, item, col, mouseEvent);
  }
#  if  wxUSE_ACCESSIBILITY
  wxString GetAccessibleDescription() const override;
#  endif
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewCustomRenderer);
};
// ---------------------------------------------------------
// wxDataViewTextRenderer
// ---------------------------------------------------------
class WXDLLIMPEXP_ADV wxDataViewTextRenderer : public wxDataViewRenderer
{
public:
  static wxString GetDefaultType()
  {
    return wxS("string");
  }
  wxDataViewTextRenderer(const wxString& varianttype = GetDefaultType(), wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT, int align = wxDVR_DEFAULT_ALIGNMENT);
  virtual ~wxDataViewTextRenderer();
#  if  wxUSE_MARKUP
  void EnableMarkup(bool enable = true);
#  endif
  bool SetValue(const wxVariant& value) override;
  bool GetValue(wxVariant& value) const override;
#  if  wxUSE_ACCESSIBILITY
  wxString GetAccessibleDescription() const override;
#  endif
  bool Render(wxRect cell, wxDC* dc, int state) override;
  wxSize GetSize() const override;
    // in-place editing
  bool HasEditorCtrl() const override;
  wxWindow* CreateEditorCtrl(wxWindow* parent, wxRect labelRect, const wxVariant& value) override;
  bool GetValueFromEditorCtrl(wxWindow* editor, wxVariant& value) override;
protected:
  wxString m_text;
#  if  wxUSE_MARKUP
private:
  class wxItemMarkupText* m_markupText;
#  endif
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewTextRenderer);
};
// ---------------------------------------------------------
// wxDataViewBitmapRenderer
// ---------------------------------------------------------
class WXDLLIMPEXP_ADV wxDataViewBitmapRenderer : public wxDataViewRenderer
{
public:
  static wxString GetDefaultType()
  {
    return wxS("wxBitmap");
  }
  wxDataViewBitmapRenderer(const wxString& varianttype = GetDefaultType(), wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT, int align = wxDVR_DEFAULT_ALIGNMENT);
  bool SetValue(const wxVariant& value) override;
  bool GetValue(wxVariant& value) const override;
#  if  wxUSE_ACCESSIBILITY
  wxString GetAccessibleDescription() const override;
#  endif
  bool Render(wxRect cell, wxDC* dc, int state) override;
  wxSize GetSize() const override;
private:
  wxIcon m_icon;
  wxBitmap m_bitmap;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewBitmapRenderer);
};
// ---------------------------------------------------------
// wxDataViewToggleRenderer
// ---------------------------------------------------------
class WXDLLIMPEXP_ADV wxDataViewToggleRenderer : public wxDataViewRenderer
{
public:
  static wxString GetDefaultType()
  {
    return wxS("bool");
  }
  wxDataViewToggleRenderer(const wxString& varianttype = GetDefaultType(), wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT, int align = wxDVR_DEFAULT_ALIGNMENT);
  void ShowAsRadio()
  {
    m_radio = true;
  }
  bool SetValue(const wxVariant& value) override;
  bool GetValue(wxVariant& value) const override;
#  if  wxUSE_ACCESSIBILITY
  wxString GetAccessibleDescription() const override;
#  endif
  bool Render(wxRect cell, wxDC* dc, int state) override;
  wxSize GetSize() const override;
    // Implementation only, don't use nor override
  bool WXActivateCell(const wxRect& cell, wxDataViewModel* model, const wxDataViewItem& item, unsigned int col, const wxMouseEvent* mouseEvent) override;
private:
  bool m_toggle;
  bool m_radio;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewToggleRenderer);
};
// ---------------------------------------------------------
// wxDataViewProgressRenderer
// ---------------------------------------------------------
class WXDLLIMPEXP_ADV wxDataViewProgressRenderer : public wxDataViewRenderer
{
public:
  static wxString GetDefaultType()
  {
    return wxS("long");
  }
  wxDataViewProgressRenderer(const wxString& label = wxEmptyString, const wxString& varianttype = GetDefaultType(), wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT, int align = wxDVR_DEFAULT_ALIGNMENT);
  bool SetValue(const wxVariant& value) override;
  bool GetValue(wxVariant& value) const override;
#  if  wxUSE_ACCESSIBILITY
  wxString GetAccessibleDescription() const override;
#  endif
  bool Render(wxRect cell, wxDC* dc, int state) override;
  wxSize GetSize() const override;
private:
  wxString m_label;
  int m_value;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewProgressRenderer);
};
// ---------------------------------------------------------
// wxDataViewIconTextRenderer
// ---------------------------------------------------------
class WXDLLIMPEXP_ADV wxDataViewIconTextRenderer : public wxDataViewRenderer
{
public:
  static wxString GetDefaultType()
  {
    return wxS("wxDataViewIconText");
  }
  wxDataViewIconTextRenderer(const wxString& varianttype = GetDefaultType(), wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT, int align = wxDVR_DEFAULT_ALIGNMENT);
  bool SetValue(const wxVariant& value) override;
  bool GetValue(wxVariant& value) const override;
#  if  wxUSE_ACCESSIBILITY
  wxString GetAccessibleDescription() const override;
#  endif
  bool Render(wxRect cell, wxDC* dc, int state) override;
  wxSize GetSize() const override;
  bool HasEditorCtrl() const override
  {
    return true;
  }
  wxWindow* CreateEditorCtrl(wxWindow* parent, wxRect labelRect, const wxVariant& value) override;
  bool GetValueFromEditorCtrl(wxWindow* editor, wxVariant& value) override;
private:
  wxDataViewIconText m_value;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewIconTextRenderer);
};
#endif
