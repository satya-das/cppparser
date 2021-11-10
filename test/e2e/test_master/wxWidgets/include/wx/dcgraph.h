/////////////////////////////////////////////////////////////////////////////
// Name:        wx/dcgraph.h
// Purpose:     graphics context device bridge header
// Author:      Stefan Csomor
// Modified by:
// Created:
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GRAPHICS_DC_H_
#  define _WX_GRAPHICS_DC_H_
#  if  wxUSE_GRAPHICS_CONTEXT
#    include "wx/dc.h"
#    include "wx/geometry.h"
#    include "wx/graphics.h"
class WXDLLIMPEXP_FWD_CORE wxWindowDC;
class WXDLLIMPEXP_CORE wxGCDC : public wxDC
{
public:
  wxGCDC(const wxWindowDC& dc);
  wxGCDC(const wxMemoryDC& dc);
#    if  wxUSE_PRINTING_ARCHITECTURE
  wxGCDC(const wxPrinterDC& dc);
#    endif
#    if  defined(__WXMSW__) && wxUSE_ENH_METAFILE
  wxGCDC(const wxEnhMetaFileDC& dc);
#    endif
  wxGCDC(wxGraphicsContext* context);
  wxGCDC();
  virtual ~wxGCDC();
    // override wxDC virtual functions to provide access to HDC associated with
    // this Graphics object (implemented in src/msw/graphics.cpp)
private:
  wxDECLARE_DYNAMIC_CLASS(wxGCDC);
  wxDECLARE_NO_COPY_CLASS(wxGCDC);
};
class WXDLLIMPEXP_CORE wxGCDCImpl : public wxDCImpl
{
public:
  wxGCDCImpl(wxDC* owner, const wxWindowDC& dc);
  wxGCDCImpl(wxDC* owner, const wxMemoryDC& dc);
#    if  wxUSE_PRINTING_ARCHITECTURE
  wxGCDCImpl(wxDC* owner, const wxPrinterDC& dc);
#    endif
#    if  defined(__WXMSW__) && wxUSE_ENH_METAFILE
  wxGCDCImpl(wxDC* owner, const wxEnhMetaFileDC& dc);
#    endif
    // Ctor using an existing graphics context given to wxGCDC ctor.
  wxGCDCImpl(wxDC* owner, wxGraphicsContext* context);
  wxGCDCImpl(wxDC* owner);
  virtual ~wxGCDCImpl();
    // implement base class pure virtuals
    // ----------------------------------
  void Clear() override;
  bool StartDoc(const wxString& message) override;
  void EndDoc() override;
  void StartPage() override;
  void EndPage() override;
    // flushing the content of this dc immediately onto screen
  void Flush() override;
  void SetFont(const wxFont& font) override;
  void SetPen(const wxPen& pen) override;
  void SetBrush(const wxBrush& brush) override;
  void SetBackground(const wxBrush& brush) override;
  void SetBackgroundMode(int mode) override;
#    if  wxUSE_PALETTE
  void SetPalette(const wxPalette& palette) override;
#    endif
  void DestroyClippingRegion() override;
  wxCoord GetCharHeight() const override;
  wxCoord GetCharWidth() const override;
  bool CanDrawBitmap() const override;
  bool CanGetTextExtent() const override;
  int GetDepth() const override;
  wxSize GetPPI() const override;
  void SetLogicalFunction(wxRasterOperationMode function) override;
  void SetTextForeground(const wxColour& colour) override;
  void SetTextBackground(const wxColour& colour) override;
  void ComputeScaleAndOrigin() override;
  wxGraphicsContext* GetGraphicsContext() const override
  {
    return m_graphicContext;
  }
  void SetGraphicsContext(wxGraphicsContext* ctx) override;
  void* GetHandle() const override;
#    if  wxUSE_DC_TRANSFORM_MATRIX
  bool CanUseTransformMatrix() const override;
  bool SetTransformMatrix(const wxAffineMatrix2D& matrix) override;
  wxAffineMatrix2D GetTransformMatrix() const override;
  void ResetTransformMatrix() override;
#    endif
    // coordinates conversions and transforms
  wxPoint DeviceToLogical(wxCoord x, wxCoord y) const override;
  wxPoint LogicalToDevice(wxCoord x, wxCoord y) const override;
  wxSize DeviceToLogicalRel(int x, int y) const override;
  wxSize LogicalToDeviceRel(int x, int y) const override;
    // the true implementations
  bool DoFloodFill(wxCoord x, wxCoord y, const wxColour& col, wxFloodFillStyle style = wxFLOOD_SURFACE) override;
  void DoGradientFillLinear(const wxRect& rect, const wxColour& initialColour, const wxColour& destColour, wxDirection nDirection = wxEAST) override;
  void DoGradientFillConcentric(const wxRect& rect, const wxColour& initialColour, const wxColour& destColour, const wxPoint& circleCenter) override;
  bool DoGetPixel(wxCoord x, wxCoord y, wxColour* col) const override;
  void DoDrawPoint(wxCoord x, wxCoord y) override;
#    if  wxUSE_SPLINES
  void DoDrawSpline(const wxPointList* points) override;
#    endif
  void DoDrawLine(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2) override;
  void DoDrawArc(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2, wxCoord xc, wxCoord yc) override;
  void DoDrawCheckMark(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoDrawEllipticArc(wxCoord x, wxCoord y, wxCoord w, wxCoord h, double sa, double ea) override;
  void DoDrawRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoDrawRoundedRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double radius) override;
  void DoDrawEllipse(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoCrossHair(wxCoord x, wxCoord y) override;
  void DoDrawIcon(const wxIcon& icon, wxCoord x, wxCoord y) override;
  void DoDrawBitmap(const wxBitmap& bmp, wxCoord x, wxCoord y, bool useMask = false) override;
  void DoDrawText(const wxString& text, wxCoord x, wxCoord y) override;
  void DoDrawRotatedText(const wxString& text, wxCoord x, wxCoord y, double angle) override;
  bool DoBlit(wxCoord xdest, wxCoord ydest, wxCoord width, wxCoord height, wxDC* source, wxCoord xsrc, wxCoord ysrc, wxRasterOperationMode rop = wxCOPY, bool useMask = false, wxCoord xsrcMask = -1, wxCoord ysrcMask = -1) override;
  bool DoStretchBlit(wxCoord xdest, wxCoord ydest, wxCoord dstWidth, wxCoord dstHeight, wxDC* source, wxCoord xsrc, wxCoord ysrc, wxCoord srcWidth, wxCoord srcHeight, wxRasterOperationMode = wxCOPY, bool useMask = false, wxCoord xsrcMask = wxDefaultCoord, wxCoord ysrcMask = wxDefaultCoord) override;
  void DoGetSize(int*, int*) const override;
  void DoGetSizeMM(int* width, int* height) const override;
  void DoDrawLines(int n, const wxPoint points[], wxCoord xoffset, wxCoord yoffset) override;
  void DoDrawPolygon(int n, const wxPoint points[], wxCoord xoffset, wxCoord yoffset, wxPolygonFillMode fillStyle = wxODDEVEN_RULE) override;
  void DoDrawPolyPolygon(int n, const int count[], const wxPoint points[], wxCoord xoffset, wxCoord yoffset, wxPolygonFillMode fillStyle) override;
  void DoSetDeviceClippingRegion(const wxRegion& region) override;
  void DoSetClippingRegion(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  bool DoGetClippingRect(wxRect& rect) const override;
  void DoGetTextExtent(const wxString& string, wxCoord* x, wxCoord* y, wxCoord* descent = NULL, wxCoord* externalLeading = NULL, const wxFont* theFont = NULL) const override;
  bool DoGetPartialTextExtents(const wxString& text, wxArrayInt& widths) const override;
    // update the internal clip box variables
  void UpdateClipBox();
protected:
    // unused int parameter distinguishes this version, which does not create a
    // wxGraphicsContext, in the expectation that the derived class will do it
  wxGCDCImpl(wxDC* owner, int);
    // scaling variables
  bool m_logicalFunctionSupported;
  wxGraphicsMatrix m_matrixOriginal;
  wxGraphicsMatrix m_matrixCurrent;
  wxGraphicsMatrix m_matrixCurrentInv;
#    if  wxUSE_DC_TRANSFORM_MATRIX
  wxAffineMatrix2D m_matrixExtTransform;
#    endif
  wxGraphicsContext* m_graphicContext;
  bool m_isClipBoxValid;
private:
    // This method only initializes trivial fields.
  void CommonInit();
    // This method initializes all fields (including those initialized by
    // CommonInit() as it calls it) and the given context, if non-null, which
    // is assumed to be newly created.
  void Init(wxGraphicsContext*);
    // This method initializes m_graphicContext, m_ok and m_matrixOriginal
    // fields, returns true if the context was valid.
  bool DoInitContext(wxGraphicsContext* ctx);
  wxDECLARE_CLASS(wxGCDCImpl);
  wxDECLARE_NO_COPY_CLASS(wxGCDCImpl);
};
#  endif
#endif
