/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/print.h
// Author:      Anthony Bretaudeau
// Purpose:     GTK printing support
// Created:     2007-08-25
// Copyright:   (c) Anthony Bretaudeau
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_PRINT_H_
#  define _WX_GTK_PRINT_H_
#  include "wx/defs.h"
#  if  wxUSE_GTKPRINT
#    include "wx/print.h"
#    include "wx/printdlg.h"
#    include "wx/prntbase.h"
#    include "wx/dc.h"
typedef struct _GtkPrintOperation GtkPrintOperation;
typedef struct _GtkPrintContext GtkPrintContext;
typedef struct _GtkPrintSettings GtkPrintSettings;
typedef struct _GtkPageSetup GtkPageSetup;
typedef struct _cairo cairo_t;
//----------------------------------------------------------------------------
// wxGtkPrintFactory
//----------------------------------------------------------------------------
class wxGtkPrintFactory : public wxPrintFactory
{
public:
  wxPrinterBase* CreatePrinter(wxPrintDialogData* data) override;
  wxPrintPreviewBase* CreatePrintPreview(wxPrintout* preview, wxPrintout* printout = NULL, wxPrintDialogData* data = NULL) override;
  wxPrintPreviewBase* CreatePrintPreview(wxPrintout* preview, wxPrintout* printout, wxPrintData* data) override;
  wxPrintDialogBase* CreatePrintDialog(wxWindow* parent, wxPrintDialogData* data = NULL) override;
  wxPrintDialogBase* CreatePrintDialog(wxWindow* parent, wxPrintData* data) override;
  wxPageSetupDialogBase* CreatePageSetupDialog(wxWindow* parent, wxPageSetupDialogData* data = NULL) override;
  wxDCImpl* CreatePrinterDCImpl(wxPrinterDC* owner, const wxPrintData& data) override;
  bool HasPrintSetupDialog() override;
  wxDialog* CreatePrintSetupDialog(wxWindow* parent, wxPrintData* data) override;
  bool HasOwnPrintToFile() override;
  bool HasPrinterLine() override;
  wxString CreatePrinterLine() override;
  bool HasStatusLine() override;
  wxString CreateStatusLine() override;
  wxPrintNativeDataBase* CreatePrintNativeData() override;
};
//----------------------------------------------------------------------------
// wxGtkPrintDialog
//----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGtkPrintDialog : public wxPrintDialogBase
{
public:
  wxGtkPrintDialog(wxWindow* parent, wxPrintDialogData* data = NULL);
  wxGtkPrintDialog(wxWindow* parent, wxPrintData* data);
  virtual ~wxGtkPrintDialog();
  wxPrintData& GetPrintData() override
  {
 return m_printDialogData.GetPrintData();
  }
  wxPrintDialogData& GetPrintDialogData() override
  {
 return m_printDialogData;
  }
  wxDC* GetPrintDC() override;
  int ShowModal() override;
  bool Validate() override
  {
 return true;
  }
  bool TransferDataToWindow() override
  {
 return true;
  }
  bool TransferDataFromWindow() override
  {
 return true;
  }
  void SetShowDialog(bool show)
  {
 m_showDialog = show;
  }
  bool GetShowDialog()
  {
 return m_showDialog;
  }
protected:
    // Implement some base class methods to do nothing to avoid asserts and
    // GTK warnings, since this is not a real wxDialog.
  void DoSetSize(int, int, int, int, int = wxSIZE_AUTO) override
  {
  }
  void DoMoveWindow(int, int, int, int) override
  {
  }
private:
  wxPrintDialogData m_printDialogData;
  wxWindow* m_parent;
  bool m_showDialog;
  wxDECLARE_DYNAMIC_CLASS(wxGtkPrintDialog);
};
//----------------------------------------------------------------------------
// wxGtkPageSetupDialog
//----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGtkPageSetupDialog : public wxPageSetupDialogBase
{
public:
  wxGtkPageSetupDialog(wxWindow* parent, wxPageSetupDialogData* data = NULL);
  virtual ~wxGtkPageSetupDialog();
  wxPageSetupDialogData& GetPageSetupDialogData() override
  {
 return m_pageDialogData;
  }
  int ShowModal() override;
  bool Validate() override
  {
 return true;
  }
  bool TransferDataToWindow() override
  {
 return true;
  }
  bool TransferDataFromWindow() override
  {
 return true;
  }
protected:
    // Implement some base class methods to do nothing to avoid asserts and
    // GTK warnings, since this is not a real wxDialog.
  void DoSetSize(int, int, int, int, int = wxSIZE_AUTO) override
  {
  }
  void DoMoveWindow(int, int, int, int) override
  {
  }
private:
  wxPageSetupDialogData m_pageDialogData;
  wxWindow* m_parent;
  wxDECLARE_DYNAMIC_CLASS(wxGtkPageSetupDialog);
};
//----------------------------------------------------------------------------
// wxGtkPrinter
//----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGtkPrinter : public wxPrinterBase
{
public:
  wxGtkPrinter(wxPrintDialogData* data = NULL);
  virtual ~wxGtkPrinter();
  bool Print(wxWindow* parent, wxPrintout* printout, bool prompt = true) override;
  wxDC* PrintDialog(wxWindow* parent) override;
  bool Setup(wxWindow* parent) override;
  GtkPrintContext* GetPrintContext()
  {
 return m_gpc;
  }
  void SetPrintContext(GtkPrintContext* context)
  {
m_gpc = context;
  }
  void BeginPrint(wxPrintout* printout, GtkPrintOperation* operation, GtkPrintContext* context);
  void DrawPage(wxPrintout* printout, GtkPrintOperation* operation, GtkPrintContext* context, int page_nr);
private:
  GtkPrintContext* m_gpc;
  wxDC* m_dc;
  wxDECLARE_DYNAMIC_CLASS(wxGtkPrinter);
  wxDECLARE_NO_COPY_CLASS(wxGtkPrinter);
};
//----------------------------------------------------------------------------
// wxGtkPrintNativeData
//----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGtkPrintNativeData : public wxPrintNativeDataBase
{
public:
  wxGtkPrintNativeData();
  virtual ~wxGtkPrintNativeData();
  bool TransferTo(wxPrintData& data) override;
  bool TransferFrom(const wxPrintData& data) override;
  bool Ok() const override
  {
 return IsOk();
  }
  bool IsOk() const override
  {
 return true;
  }
  GtkPrintSettings* GetPrintConfig()
  {
 return m_config;
  }
  void SetPrintConfig(GtkPrintSettings* config);
  GtkPrintOperation* GetPrintJob()
  {
 return m_job;
  }
  void SetPrintJob(GtkPrintOperation* job);
  GtkPrintContext* GetPrintContext()
  {
 return m_context;
  }
  void SetPrintContext(GtkPrintContext* context)
  {
m_context = context;
  }
  GtkPageSetup* GetPageSetupFromSettings(GtkPrintSettings* settings);
  void SetPageSetupToSettings(GtkPrintSettings* settings, GtkPageSetup* page_setup);
private:
    // NB: m_config is created and owned by us, but the other objects are not
    //     and their accessors don't change their ref count.
  GtkPrintSettings* m_config;
  GtkPrintOperation* m_job;
  GtkPrintContext* m_context;
  wxDECLARE_DYNAMIC_CLASS(wxGtkPrintNativeData);
};
//-----------------------------------------------------------------------------
// wxGtkPrinterDC
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGtkPrinterDCImpl : public wxDCImpl
{
public:
  wxGtkPrinterDCImpl(wxPrinterDC* owner, const wxPrintData& data);
  virtual ~wxGtkPrinterDCImpl();
  bool Ok() const
  {
 return IsOk();
  }
  bool IsOk() const override;
  void* GetCairoContext() const override;
  void* GetHandle() const override;
  bool CanDrawBitmap() const override
  {
 return true;
  }
  void Clear() override;
  void SetFont(const wxFont& font) override;
  void SetPen(const wxPen& pen) override;
  void SetBrush(const wxBrush& brush) override;
  void SetLogicalFunction(wxRasterOperationMode function) override;
  void SetBackground(const wxBrush& brush) override;
  void DestroyClippingRegion() override;
  bool StartDoc(const wxString& message) override;
  void EndDoc() override;
  void StartPage() override;
  void EndPage() override;
  wxCoord GetCharHeight() const override;
  wxCoord GetCharWidth() const override;
  bool CanGetTextExtent() const override
  {
 return true;
  }
  wxSize GetPPI() const override;
  int GetDepth() const override
  {
 return 24;
  }
  void SetBackgroundMode(int mode) override;
#    if  wxUSE_PALETTE
  void SetPalette(const wxPalette&) override
  {

  }
#    endif
  void SetResolution(int ppi);
    // overridden for wxPrinterDC Impl
  int GetResolution() const override;
  wxRect GetPaperRect() const override;
protected:
  bool DoFloodFill(wxCoord x1, wxCoord y1, const wxColour& col, wxFloodFillStyle style = wxFLOOD_SURFACE) override;
  void DoGradientFillConcentric(const wxRect& rect, const wxColour& initialColour, const wxColour& destColour, const wxPoint& circleCenter) override;
  void DoGradientFillLinear(const wxRect& rect, const wxColour& initialColour, const wxColour& destColour, wxDirection nDirection = wxEAST) override;
  bool DoGetPixel(wxCoord x1, wxCoord y1, wxColour* col) const override;
  void DoDrawLine(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2) override;
  void DoCrossHair(wxCoord x, wxCoord y) override;
  void DoDrawArc(wxCoord x1, wxCoord y1, wxCoord x2, wxCoord y2, wxCoord xc, wxCoord yc) override;
  void DoDrawEllipticArc(wxCoord x, wxCoord y, wxCoord w, wxCoord h, double sa, double ea) override;
  void DoDrawPoint(wxCoord x, wxCoord y) override;
  void DoDrawLines(int n, const wxPoint points[], wxCoord xoffset = 0, wxCoord yoffset = 0) override;
  void DoDrawPolygon(int n, const wxPoint points[], wxCoord xoffset = 0, wxCoord yoffset = 0, wxPolygonFillMode fillStyle = wxODDEVEN_RULE) override;
  void DoDrawPolyPolygon(int n, const int count[], const wxPoint points[], wxCoord xoffset = 0, wxCoord yoffset = 0, wxPolygonFillMode fillStyle = wxODDEVEN_RULE) override;
  void DoDrawRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoDrawRoundedRectangle(wxCoord x, wxCoord y, wxCoord width, wxCoord height, double radius = 20.0) override;
  void DoDrawEllipse(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
#    if  wxUSE_SPLINES
  void DoDrawSpline(const wxPointList* points) override;
#    endif
  bool DoBlit(wxCoord xdest, wxCoord ydest, wxCoord width, wxCoord height, wxDC* source, wxCoord xsrc, wxCoord ysrc, wxRasterOperationMode rop = wxCOPY, bool useMask = false, wxCoord xsrcMask = wxDefaultCoord, wxCoord ysrcMask = wxDefaultCoord) override;
  void DoDrawIcon(const wxIcon& icon, wxCoord x, wxCoord y) override;
  void DoDrawBitmap(const wxBitmap& bitmap, wxCoord x, wxCoord y, bool useMask = false) override;
  void DoDrawText(const wxString& text, wxCoord x, wxCoord y) override;
  void DoDrawRotatedText(const wxString& text, wxCoord x, wxCoord y, double angle) override;
  void DoSetClippingRegion(wxCoord x, wxCoord y, wxCoord width, wxCoord height) override;
  void DoSetDeviceClippingRegion(const wxRegion&) override
  {
        wxFAIL_MSG( "not implemented" );
  }
  void DoGetTextExtent(const wxString& string, wxCoord* x, wxCoord* y, wxCoord* descent = NULL, wxCoord* externalLeading = NULL, const wxFont* theFont = NULL) const override;
  bool DoGetPartialTextExtents(const wxString& text, wxArrayInt& widths) const override;
  void DoGetSize(int* width, int* height) const override;
  void DoGetSizeMM(int* width, int* height) const override;
  wxPrintData& GetPrintData()
  {
 return m_printData;
  }
  void SetPrintData(const wxPrintData& data);
private:
  wxPrintData m_printData;
  PangoContext* m_context;
  PangoLayout* m_layout;
  PangoFontDescription* m_fontdesc;
  cairo_t* m_cairo;
  unsigned char m_currentRed;
  unsigned char m_currentGreen;
  unsigned char m_currentBlue;
  unsigned char m_currentAlpha;
  GtkPrintContext* m_gpc;
  int m_resolution;
  double m_PS2DEV;
  double m_DEV2PS;
  wxDECLARE_DYNAMIC_CLASS(wxGtkPrinterDCImpl);
  wxDECLARE_NO_COPY_CLASS(wxGtkPrinterDCImpl);
};
// ----------------------------------------------------------------------------
// wxGtkPrintPreview: programmer creates an object of this class to preview a
// wxPrintout.
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxGtkPrintPreview : public wxPrintPreviewBase
{
public:
  wxGtkPrintPreview(wxPrintout* printout, wxPrintout* printoutForPrinting = NULL, wxPrintDialogData* data = NULL);
  wxGtkPrintPreview(wxPrintout* printout, wxPrintout* printoutForPrinting, wxPrintData* data);
  virtual ~wxGtkPrintPreview();
  bool Print(bool interactive) override;
  void DetermineScaling() override;
private:
  void Init(wxPrintout* printout, wxPrintout* printoutForPrinting, wxPrintData* data);
    // resolution to use in DPI
  int m_resolution;
  wxDECLARE_CLASS(wxGtkPrintPreview);
};
#  endif
#endif
