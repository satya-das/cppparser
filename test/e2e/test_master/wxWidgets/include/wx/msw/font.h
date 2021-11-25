/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/font.h
// Purpose:     wxFont class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_FONT_H_
#  define _WX_FONT_H_
#  include "wx/gdicmn.h"
// ----------------------------------------------------------------------------
// wxFont
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxFont : public wxFontBase
{
public:
    // ctors and such
  wxFont()
  {
  }
  wxFont(const wxFontInfo& info);
  wxFont(int size, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {
    Create(size, family, style, weight, underlined, face, encoding);
  }
  bool Create(int size, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {
    return DoCreate(InfoFromLegacyParams(size, family, style, weight, underlined, face, encoding));
  }
  wxFont(const wxSize& pixelSize, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {
    (void) Create(pixelSize, family, style, weight, underlined, face, encoding);
  }
  wxFont(const wxNativeFontInfo& info, WXHFONT hFont = NULL)
  {
    Create(info, hFont);
  }
  wxFont(const wxString& fontDesc);
  bool Create(const wxSize& pixelSize, wxFontFamily family, wxFontStyle style, wxFontWeight weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {
    return DoCreate(InfoFromLegacyParams(pixelSize, family, style, weight, underlined, face, encoding));
  }
  bool Create(const wxNativeFontInfo& info, WXHFONT hFont = NULL);
  virtual ~wxFont();
    // implement base class pure virtuals
  double GetFractionalPointSize() const override;
  wxSize GetPixelSize() const override;
  bool IsUsingSizeInPixels() const override;
  wxFontStyle GetStyle() const override;
  int GetNumericWeight() const override;
  bool GetUnderlined() const override;
  bool GetStrikethrough() const override;
  wxString GetFaceName() const override;
  wxFontEncoding GetEncoding() const override;
  const wxNativeFontInfo* GetNativeFontInfo() const override;
  void SetFractionalPointSize(double pointSize) override;
  void SetPixelSize(const wxSize& pixelSize) override;
  void SetFamily(wxFontFamily family) override;
  void SetStyle(wxFontStyle style) override;
  void SetNumericWeight(int weight) override;
  bool SetFaceName(const wxString& faceName) override;
  void SetUnderlined(bool underlined) override;
  void SetStrikethrough(bool strikethrough) override;
  void SetEncoding(wxFontEncoding encoding) override;
  wxDECLARE_COMMON_FONT_METHODS();
  bool IsFixedWidth() const override;
    // MSW needs to modify the font object when the DPI of the window it
    // is used with changes, this function can be used to do it.
    //
    // This method is not considered to be part of wxWidgets public API.
  void WXAdjustToPPI(const wxSize& ppi);
  wxDEPRECATED_MSG("use wxFONT{FAMILY,STYLE,WEIGHT}_XXX constants ie: wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD") wxFont(int size, int family, int style, int weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {
    (void) Create(size, (wxFontFamily) family, (wxFontStyle) style, (wxFontWeight) weight, underlined, face, encoding);
  }
  wxDEPRECATED_MSG("use wxFONT{FAMILY,STYLE,WEIGHT}_XXX constants ie: wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD") wxFont(const wxSize& pixelSize, int family, int style, int weight, bool underlined = false, const wxString& face = wxEmptyString, wxFontEncoding encoding = wxFONTENCODING_DEFAULT)
  {
    (void) Create(pixelSize, (wxFontFamily) family, (wxFontStyle) style, (wxFontWeight) weight, underlined, face, encoding);
  }
    // implementation only from now on
    // -------------------------------
  bool IsFree() const override;
  bool RealizeResource() override;
  WXHANDLE GetResourceHandle() const override;
  bool FreeResource(bool force = false) override;
    // for consistency with other wxMSW classes
  WXHFONT GetHFONT() const;
protected:
    // Common helper of overloaded Create() methods.
  bool DoCreate(const wxFontInfo& info);
  void DoSetNativeFontInfo(const wxNativeFontInfo& info) override;
  wxFontFamily DoGetFamily() const override;
    // implement wxObject virtuals which are used by AllocExclusive()
  wxGDIRefData* CreateGDIRefData() const override;
  wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const override;
private:
  wxDECLARE_DYNAMIC_CLASS(wxFont);
};
#endif
