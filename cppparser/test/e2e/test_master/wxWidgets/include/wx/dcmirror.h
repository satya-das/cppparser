///////////////////////////////////////////////////////////////////////////////
// Name:        wx/dcmirror.h
// Purpose:     wxMirrorDC class
// Author:      Vadim Zeitlin
// Modified by:
// Created:     21.07.2003
// Copyright:   (c) 2003 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_DCMIRROR_H_
#  define _WX_DCMIRROR_H_
#  include "wx/dc.h"
// ----------------------------------------------------------------------------
// wxMirrorDC allows to write the same code for horz/vertical layout
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxMirrorDCImpl : public wxDCImpl
{
public:
    // constructs a mirror DC associated with the given real DC
    //
    // if mirror parameter is true, all vertical and horizontal coordinates are
    // exchanged, otherwise this class behaves in exactly the same way as a
    // plain DC
  wxMirrorDCImpl(wxDC* owner, wxDCImpl& dc, bool mirror)
    : wxDCImpl(owner)
    , m_dc(dc)
  {
    m_mirror = mirror;
  }
    // wxDCBase operations
  void Clear() override
  {
    m_dc.Clear();
  }
  void SetFont(const wxFont& font) override
  {
    m_dc.SetFont(font);
  }
  void SetPen(const wxPen& pen) override
  {
    m_dc.SetPen(pen);
  }
  void SetBrush(const wxBrush& brush) override
  {
    m_dc.SetBrush(brush);
  }
  void SetBackground(const wxBrush& brush) override
  {
    m_dc.SetBackground(brush);
  }
  void SetBackgroundMode(int mode) override
  {
    m_dc.SetBackgroundMode(mode);
  }
#  if  wxUSE_PALETTE
  void SetPalette(const wxPalette& palette) override
  {
    m_dc.SetPalette(palette);
  }
#  endif
  void DestroyClippingRegion() override
  {
    m_dc.DestroyClippingRegion();
  }
  wxCoord GetCharHeight() const override
  {
    return m_dc.GetCharHeight();
  }
  wxCoord GetCharWidth() const override
  {
    return m_dc.GetCharWidth();
  }
  bool CanDrawBitmap() const override
  {
    return m_dc.CanDrawBitmap();
  }
  bool CanGetTextExtent() const override
  {
    return m_dc.CanGetTextExtent();
  }
  int GetDepth() const override
  {
    return m_dc.GetDepth();
  }
  wxSize GetPPI() const override
  {
    return m_dc.GetPPI();
  }
  bool IsOk() const override
  {
    return m_dc.IsOk();
  }
  void SetMapMode(wxMappingMode mode) override
  {
    m_dc.SetMapMode(mode);
  }
  void SetUserScale(double x, double y) override
  {
    m_dc.SetUserScale(GetX(x, y), GetY(x, y));
  }
  void SetLogicalOrigin(wxCoord x, wxCoord y) override
  {
    m_dc.SetLogicalOrigin(GetX(x, y), GetY(x, y));
  }
  void SetDeviceOrigin(wxCoord x, wxCoord y) override
  {
    m_dc.SetDeviceOrigin(GetX(x, y), GetY(x, y));
  }
  void SetAxisOrientation(bool xLeftRight, bool yBottomUp) override
  {
    m_dc.SetAxisOrientation(GetX(xLeftRight, yBottomUp), GetY(xLeftRight, yBottomUp));
  }
  void SetLogicalFunction(wxRasterOperationMode function) override
  {
    m_dc.SetLogicalFunction(function);
  }
  void* GetHandle() const override
  {
    return m_dc.GetHandle();
  }
protected:
    // returns x and y if not mirroring or y and x if mirroring
  wxCoord GetX(wxCoord x, wxCoord y) const
  {
    return m_mirror ? y : x;
  }
  wxCoord GetY(wxCoord x, wxCoord y) const
  {
    return m_mirror ? x : y;
  }
  double GetX(double x, double y) const
  {
    return m_mirror ? y : x;
  }
  double GetY(double x, double y) const
  {
    return m_mirror ? x : y;
  }
  bool GetX(bool x, bool y) const
  {
    return m_mirror ? y : x;
  }
  bool GetY(bool x, bool y) const
  {
    return m_mirror ? x : y;
  }
    // same thing but for pointers
  wxCoord* GetX(wxCoord* x, wxCoord* y) const
  {
    return m_mirror ? y : x;
  }
  wxCoord* GetY(wxCoord* x, wxCoord* y) const
  {
    return m_mirror ? x : y;
  }
    // exchange x and y components of all points in the array if necessary
  wxPoint* Mirror(int n, const wxPoint*& points) const
  {
    wxPoint* points_alloc = NULL;
    if (m_mirror)
    {
      points_alloc = new wxPoint[n];
      for (int i = 0; i < n; i++)
      {
        points_alloc[i].x = points[i].y;
        points_alloc[i].y = points[i].x;
      }
      points = points_alloc;
    }
    return points_alloc;
  }
    // wxDCBase functions
  bool DoFloodFill(wxCoord x, wxCoord y, const wxColour& col, wxFloodFillStyle style = wxFLOOD_SURFACE) override
  {
    return m_dc.DoFloodFill(GetX(x, y), GetY(x, y), col, style);
  }
  bool DoGetPixel(wxCoord x, wxCoord y, wxColour* col) const override
  {
    return m_dc.DoGetPixel(GetX(x, y), GetY(x, y), col);
  }
  void DoDrawPoint(wxCoord x, wxCoord y) override
  {
    m_dc.DoDrawPoint(GetX(x, y), GetY(x, y));
  }
  void DoDrawLine(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2) override
  {
    m_dc.DoDrawLine(GetX(x1, y1), GetY(x1, y1), GetX(x2, y2), GetY(x2, y2));
  }
  void DoDrawArc(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2, wxCoord xc, wxCoord yc) override
  {
    wxFAIL_MSG( wxT("this is probably wrong") );
    m_dc.DoDrawArc(GetX(x1, y1), GetY(x1, y1), GetX(x2, y2), GetY(x2, y2), xc, yc);
  }
  void DoDrawCheckMark(wxCoord x, wxCoord y, wxCoord w, wxCoord h) override
  {
    m_dc.DoDrawCheckMark(GetX(x, y), GetY(x, y), GetX(w, h), GetY(w, h));
  }
  void DoDrawEllipticArc(wxCoord x, wxCoord y, wxCoord w, wxCoord h, double sa, double ea) override
  {
    wxFAIL_MSG( wxT("this is probably wrong") );
    m_dc.DoDrawEllipticArc(GetX(x, y), GetY(x, y), GetX(w, h), GetY(w, h), sa, ea);
  }
  void DoDrawRectangle(wxCoord x, wxCoord y, wxCoord w, wxCoord h) override
  {
    m_dc.DoDrawRectangle(GetX(x, y), GetY(x, y), GetX(w, h), GetY(w, h));
  }
  void DoDrawRoundedRectangle(wxCoord x, wxCoord y, wxCoord w, wxCoord h, double radius) override
  {
    m_dc.DoDrawRoundedRectangle(GetX(x, y), GetY(x, y), GetX(w, h), GetY(w, h), radius);
  }
  void DoDrawEllipse(wxCoord x, wxCoord y, wxCoord w, wxCoord h) override
  {
    m_dc.DoDrawEllipse(GetX(x, y), GetY(x, y), GetX(w, h), GetY(w, h));
  }
  void DoCrossHair(wxCoord x, wxCoord y) override
  {
    m_dc.DoCrossHair(GetX(x, y), GetY(x, y));
  }
  void DoDrawIcon(const wxIcon& icon, wxCoord x, wxCoord y) override
  {
    m_dc.DoDrawIcon(icon, GetX(x, y), GetY(x, y));
  }
  void DoDrawBitmap(const wxBitmap& bmp, wxCoord x, wxCoord y, bool useMask = false) override
  {
    m_dc.DoDrawBitmap(bmp, GetX(x, y), GetY(x, y), useMask);
  }
  void DoDrawText(const wxString& text, wxCoord x, wxCoord y) override
  {
        // this is never mirrored
    m_dc.DoDrawText(text, x, y);
  }
  void DoDrawRotatedText(const wxString& text, wxCoord x, wxCoord y, double angle) override
  {
        // this is never mirrored
    m_dc.DoDrawRotatedText(text, x, y, angle);
  }
  bool DoBlit(wxCoord xdest, wxCoord ydest, wxCoord w, wxCoord h, wxDC* source, wxCoord xsrc, wxCoord ysrc, wxRasterOperationMode rop = wxCOPY, bool useMask = false, wxCoord xsrcMask = wxDefaultCoord, wxCoord ysrcMask = wxDefaultCoord) override
  {
    return m_dc.DoBlit(GetX(xdest, ydest), GetY(xdest, ydest), GetX(w, h), GetY(w, h), source, GetX(xsrc, ysrc), GetY(xsrc, ysrc), rop, useMask, GetX(xsrcMask, ysrcMask), GetX(xsrcMask, ysrcMask));
  }
  void DoGetSize(int* w, int* h) const override
  {
    m_dc.DoGetSize(GetX(w, h), GetY(w, h));
  }
  void DoGetSizeMM(int* w, int* h) const override
  {
    m_dc.DoGetSizeMM(GetX(w, h), GetY(w, h));
  }
  void DoDrawLines(int n, const wxPoint points[], wxCoord xoffset, wxCoord yoffset) override
  {
    wxPoint* points_alloc = Mirror(n, points);
    m_dc.DoDrawLines(n, points, GetX(xoffset, yoffset), GetY(xoffset, yoffset));
    delete[] points_alloc;
  }
  void DoDrawPolygon(int n, const wxPoint points[], wxCoord xoffset, wxCoord yoffset, wxPolygonFillMode fillStyle = wxODDEVEN_RULE) override
  {
    wxPoint* points_alloc = Mirror(n, points);
    m_dc.DoDrawPolygon(n, points, GetX(xoffset, yoffset), GetY(xoffset, yoffset), fillStyle);
    delete[] points_alloc;
  }
  void DoSetDeviceClippingRegion(const wxRegion&) override
  {
    wxFAIL_MSG( wxT("not implemented") );
  }
  void DoSetClippingRegion(wxCoord x, wxCoord y, wxCoord w, wxCoord h) override
  {
    m_dc.DoSetClippingRegion(GetX(x, y), GetY(x, y), GetX(w, h), GetY(w, h));
  }
  void DoGetTextExtent(const wxString& string, wxCoord* x, wxCoord* y, wxCoord* descent = NULL, wxCoord* externalLeading = NULL, const wxFont* theFont = NULL) const override
  {
        // never mirrored
    m_dc.DoGetTextExtent(string, x, y, descent, externalLeading, theFont);
  }
private:
  wxDCImpl& m_dc;
  bool m_mirror;
  wxDECLARE_NO_COPY_CLASS(wxMirrorDCImpl);
};
class WXDLLIMPEXP_CORE wxMirrorDC : public wxDC
{
public:
  wxMirrorDC(wxDC& dc, bool mirror)
    : wxDC(new wxMirrorDCImpl(this, *dc.GetImpl(), mirror))
  {
    m_mirror = mirror;
  }
    // helper functions which may be useful for the users of this class
  wxSize Reflect(const wxSize& sizeOrig)
  {
    return m_mirror ? wxSize(sizeOrig.y, sizeOrig.x) : sizeOrig;
  }
private:
  bool m_mirror;
  wxDECLARE_NO_COPY_CLASS(wxMirrorDC);
};
#endif
