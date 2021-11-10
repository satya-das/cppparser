/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/font.h
// Author:      Peter Most, Javier Torres, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_FONT_H_
#  define _WX_QT_FONT_H_
class QFont;
class WXDLLIMPEXP_CORE wxFont : public wxFontBase
{
public:
  wxFont();
  wxFont(const wxFontInfo& info);
  wxFont(const wxString& nativeFontInfoString);
  wxFont(const wxNativeFontInfo& info);
  wxFont(const QFont& font);
  wxFont(int size, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT);
  wxFont(const wxSize& pixelSize, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT);
  wxDEPRECATED_MSG("use wxFONT{FAMILY,STYLE,WEIGHT}_XXX constants")
  wxFont(int size, int family, int style, int weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT);
  bool Create(wxSize size, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT);
    // accessors: get the font characteristics
  int GetPointSize() const override;
  double GetFractionalPointSize() const override;
  wxSize GetPixelSize() const override;
  wxFontStyle GetStyle() const override;
  int GetNumericWeight() const override;
  bool GetUnderlined() const override;
  wxString GetFaceName() const override;
  wxFontEncoding GetEncoding() const override;
  const wxNativeFontInfo* GetNativeFontInfo() const override;
  bool GetStrikethrough() const override;
    // change the font characteristics
  void SetFractionalPointSize(double pointSize) override;
  void SetPixelSize(const wxSize& pixelSize) override;
  void SetFamily(wxFontFamily family) override;
  void SetStyle(wxFontStyle style) override;
  void SetNumericWeight(int weight) override;
  bool SetFaceName(const wxString& facename) override;
  void SetUnderlined(bool underlined) override;
  void SetStrikethrough(bool strikethrough) override;
  void SetEncoding(wxFontEncoding encoding) override;
  wxDECLARE_COMMON_FONT_METHODS();
  virtual QFont GetHandle() const;
protected:
  wxGDIRefData* CreateGDIRefData() const override;
  wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const override;
  wxFontFamily DoGetFamily() const override;
  void DoSetNativeFontInfo(const wxNativeFontInfo& info) override;
  wxDECLARE_DYNAMIC_CLASS(wxFont);
};
#endif
