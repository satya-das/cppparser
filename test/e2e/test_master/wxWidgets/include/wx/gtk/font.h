/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/font.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_FONT_H_
#  define _WX_GTK_FONT_H_
// ----------------------------------------------------------------------------
// wxFont
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxFont : public wxFontBase
{
public:
  wxFont()
  {
   }
  wxFont(const wxFontInfo& info);
  wxFont(const wxString& nativeFontInfoString)
  {

        Create(nativeFontInfoString);
      }
  wxFont(const wxNativeFontInfo& info);
  wxFont(int size, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {

        Create(size, family, style, weight, underlined, face, encoding);
      }
  wxFont(const wxSize& pixelSize, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {

        Create(10, family, style, weight, underlined, face, encoding);
        SetPixelSize(pixelSize);
      }
  bool Create(int size, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT);
    // wxGTK-specific
  bool Create(const wxString& fontname);
  virtual ~wxFont();
    // implement base class pure virtuals
  double GetFractionalPointSize() const override;
  wxFontStyle GetStyle() const override;
  int GetNumericWeight() const override;
  wxString GetFaceName() const override;
  bool GetUnderlined() const override;
  bool GetStrikethrough() const override;
  wxFontEncoding GetEncoding() const override;
  const wxNativeFontInfo* GetNativeFontInfo() const override;
  bool IsFixedWidth() const override;
  void SetFractionalPointSize(double pointSize) override;
  void SetFamily(wxFontFamily family) override;
  void SetStyle(wxFontStyle style) override;
  void SetNumericWeight(int weight) override;
  bool SetFaceName(const wxString& faceName) override;
  void SetUnderlined(bool underlined) override;
  void SetStrikethrough(bool strikethrough) override;
  void SetEncoding(wxFontEncoding encoding) override;
  wxDECLARE_COMMON_FONT_METHODS();
  wxDEPRECATED_MSG("use wxFONT{FAMILY,STYLE,WEIGHT}_XXX constants") wxFont(int size, int family, int style, int weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {

        (void)Create(size, (wxFontFamily)family, (wxFontStyle)style, (wxFontWeight)weight, underlined, face, encoding);
      }
    // Set Pango attributes in the specified layout. Currently only
    // underlined and strike-through attributes are handled by this function.
    //
    // If neither of them is specified, returns false, otherwise sets up the
    // attributes and returns true.
  bool GTKSetPangoAttrs(PangoLayout* layout) const;
protected:
  void DoSetNativeFontInfo(const wxNativeFontInfo& info) override;
  wxGDIRefData* CreateGDIRefData() const override;
  wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const override;
  wxFontFamily DoGetFamily() const override;
private:
  void Init();
  wxDECLARE_DYNAMIC_CLASS(wxFont);
};
#endif
