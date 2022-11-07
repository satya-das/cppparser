///////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/private/textmeasure.h
// Purpose:     Generic wxTextMeasure declaration.
// Author:      Vadim Zeitlin
// Created:     2012-10-17
// Copyright:   (c) 1997-2012 wxWidgets team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GENERIC_PRIVATE_TEXTMEASURE_H_
#  define _WX_GENERIC_PRIVATE_TEXTMEASURE_H_
// ----------------------------------------------------------------------------
// wxTextMeasure for the platforms without native support.
// ----------------------------------------------------------------------------
class wxTextMeasure : public wxTextMeasureBase
{
public:
  explicit wxTextMeasure(const wxDC* dc, const wxFont* font = NULL)
    : wxTextMeasureBase(dc, font)
  {
  }
  explicit wxTextMeasure(const wxWindow* win, const wxFont* font = NULL)
    : wxTextMeasureBase(win, font)
  {
  }
protected:
  void DoGetTextExtent(const wxString& string, wxCoord* width, wxCoord* height, wxCoord* descent = NULL, wxCoord* externalLeading = NULL) override;
  bool DoGetPartialTextExtents(const wxString& text, wxArrayInt& widths, double scaleX) override;
  wxDECLARE_NO_COPY_CLASS(wxTextMeasure);
};
#endif
