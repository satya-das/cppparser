/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/dcclient.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTKDCCLIENT_H_
#  define _WX_GTKDCCLIENT_H_
#  include "wx/gtk/dc.h"
//-----------------------------------------------------------------------------
// wxWindowDCImpl
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxWindowDCImpl : public wxGTKDCImpl
{
public:
  wxWindowDCImpl(wxDC* owner);
  wxWindowDCImpl(wxDC* owner, wxWindow* win);
  virtual ~wxWindowDCImpl();
  bool CanDrawBitmap() const override
  {
 return true;
  }
  bool CanGetTextExtent() const override
  {
 return true;
  }
  void DoGetSize(int* width, int* height) const override;
  bool DoFloodFill(wxCoord x, wxCoord y, const wxColour& col, wxFloodFillStyle style = wxFLOOD_SURFACE) override;
  bool DoGetPixel(wxCoord x1, wxCoord y1, wxColour* col) const override;
  void DoDrawLine(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2) override;
  void DoCrossHair(wxCoord x, wxCoord y) override;
  void DoDrawArc(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2, wxCoord xc, wxCoord yc) override;
  void DoDrawEllipticArc(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double sa, double ea) override;
  void DoDrawPoint(wxCoord x, wxCoord y) override;
  void DoDrawLines(int n, const wxPoint points[], wxCoord xoffset, wxCoord yoffset) override;
  void DoDrawPolygon(int n, const wxPoint points[], wxCoord xoffset, wxCoord yoffset, wxPolygonFillMode fillStyle = wxODDEVEN_RULE) override;
  void DoDrawRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoDrawRoundedRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double radius = 20.0) override;
  void DoDrawEllipse(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoDrawIcon(const wxIcon& icon, wxCoord x, wxCoord y) override;
  void DoDrawBitmap(const wxBitmap& bitmap, wxCoord x, wxCoord y, bool useMask = false) override;
  bool DoBlit(wxCoord xdest, wxCoord ydest, wxCoord width, wxCoord height, wxDC* source, wxCoord xsrc, wxCoord ysrc, wxRasterOperationMode logical_func = wxCOPY, bool useMask = false, wxCoord xsrcMask = -1, wxCoord ysrcMask = -1) override;
  void DoDrawText(const wxString& text, wxCoord x, wxCoord y) override;
  void DoDrawRotatedText(const wxString& text, wxCoord x, wxCoord y, double angle) override;
  void DoGetTextExtent(const wxString& string, wxCoord* width, wxCoord* height, wxCoord* descent = NULL, wxCoord* externalLeading = NULL, const wxFont* theFont = NULL) const override;
  bool DoGetPartialTextExtents(const wxString& text, wxArrayInt& widths) const override;
  void DoSetClippingRegion(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoSetDeviceClippingRegion(const wxRegion& region) override;
  bool DoGetClippingRect(wxRect& rect) const override;
  wxCoord GetCharWidth() const override;
  wxCoord GetCharHeight() const override;
  void Clear() override;
  void SetFont(const wxFont& font) override;
  void SetPen(const wxPen& pen) override;
  void SetBrush(const wxBrush& brush) override;
  void SetBackground(const wxBrush& brush) override;
  void SetLogicalFunction(wxRasterOperationMode function) override;
  void SetTextForeground(const wxColour& col) override;
  void SetTextBackground(const wxColour& col) override;
  void SetBackgroundMode(int mode) override;
#  if  wxUSE_PALETTE
  void SetPalette(const wxPalette& palette) override;
#  endif
  void DestroyClippingRegion() override;
    // Resolution in pixels per logical inch
  wxSize GetPPI() const override;
  int GetDepth() const override;
    // overridden here for RTL
  void SetDeviceOrigin(wxCoord x, wxCoord y) override;
  void SetAxisOrientation(bool xLeftRight, bool yBottomUp) override;
// protected:
    // implementation
    // --------------
  GdkWindow* m_gdkwindow;
  GdkGC* m_penGC;
  GdkGC* m_brushGC;
  GdkGC* m_textGC;
  GdkGC* m_bgGC;
  GdkColormap* m_cmap;
  bool m_isScreenDC;
  wxRegion m_currentClippingRegion;
  wxRegion m_paintClippingRegion;
  bool m_isClipBoxValid;
    // PangoContext stuff for GTK 2.0
  PangoContext* m_context;
  PangoLayout* m_layout;
  PangoFontDescription* m_fontdesc;
  void SetUpDC(bool ismem = false);
  void Destroy();
  void ComputeScaleAndOrigin() override;
  GdkWindow* GetGDKWindow() const override
  {
 return m_gdkwindow;
  }
    // Update the internal clip box variables
  void UpdateClipBox();
private:
  void DrawingSetup(GdkGC*& gc, bool& originChanged);
  GdkPixmap* MonoToColor(GdkPixmap* monoPixmap, int x, int y, int w, int h) const;
  wxDECLARE_ABSTRACT_CLASS(wxWindowDCImpl);
};
//-----------------------------------------------------------------------------
// wxClientDCImpl
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxClientDCImpl : public wxWindowDCImpl
{
public:
  wxClientDCImpl(wxDC* owner);
  wxClientDCImpl(wxDC* owner, wxWindow* win);
  void DoGetSize(int* width, int* height) const override;
  wxDECLARE_ABSTRACT_CLASS(wxClientDCImpl);
};
//-----------------------------------------------------------------------------
// wxPaintDCImpl
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxPaintDCImpl : public wxClientDCImpl
{
public:
  wxPaintDCImpl(wxDC* owner);
  wxPaintDCImpl(wxDC* owner, wxWindow* win);
  wxDECLARE_ABSTRACT_CLASS(wxPaintDCImpl);
};
#endif
