/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/pen.h
// Author:      Peter Most, Javier Torres
// Copyright:   (c) Peter Most, Javier Torres
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_PEN_H_
#  define _WX_QT_PEN_H_
class QPen;
class WXDLLIMPEXP_CORE wxPen : public wxPenBase
{
public:
  wxPen();
  wxPen(const wxColour& colour, int width = 1, wxPenStyle style = wxPENSTYLE_SOLID);
  wxDEPRECATED_MSG("use wxPENSTYLE_XXX constants") wxPen(const wxColour& col, int width, int style);
  bool operator==(const wxPen& pen) const;
  bool operator!=(const wxPen& pen) const;
  void SetColour(const wxColour& col) override;
  void SetColour(unsigned char r, unsigned char g, unsigned char b) override;
  void SetWidth(int width) override;
  void SetStyle(wxPenStyle style) override;
  void SetStipple(const wxBitmap& stipple) override;
  void SetDashes(int nb_dashes, const wxDash* dash) override;
  void SetJoin(wxPenJoin join) override;
  void SetCap(wxPenCap cap) override;
  wxColour GetColour() const override;
  wxBitmap* GetStipple() const override;
  wxPenStyle GetStyle() const override;
  wxPenJoin GetJoin() const override;
  wxPenCap GetCap() const override;
  int GetWidth() const override;
  int GetDashes(wxDash** ptr) const override;
  wxDEPRECATED_MSG("use wxPENSTYLE_XXX constants") void SetStyle(int style)
  { SetStyle((wxPenStyle)style); }
  QPen GetHandle() const;
protected:
  wxGDIRefData* CreateGDIRefData() const override;
  wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const override;
  wxDECLARE_DYNAMIC_CLASS(wxPen);
};
#endif
