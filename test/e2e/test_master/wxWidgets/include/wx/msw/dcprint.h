/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/dcprint.h
// Purpose:     wxPrinterDC class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_DCPRINT_H_
#  define _WX_MSW_DCPRINT_H_
#  if  wxUSE_PRINTING_ARCHITECTURE
#    include "wx/dcprint.h"
#    include "wx/cmndata.h"
#    include "wx/msw/dc.h"
// ------------------------------------------------------------------------
//    wxPrinterDCImpl
//
class WXDLLIMPEXP_CORE wxPrinterDCImpl : public wxMSWDCImpl
{
public:
    // Create from print data
  wxPrinterDCImpl(wxPrinterDC* owner, const wxPrintData& data);
  wxPrinterDCImpl(wxPrinterDC* owner, WXHDC theDC);
    // override some base class virtuals
  bool StartDoc(const wxString& message) override;
  void EndDoc() override;
  void StartPage() override;
  void EndPage() override;
  wxRect GetPaperRect() const override;
protected:
  void DoDrawBitmap(const wxBitmap& bmp, wxCoord x, wxCoord y, bool useMask = false) override;
  bool DoBlit(wxCoord xdest, wxCoord ydest, wxCoord width, wxCoord height, wxDC* source, wxCoord xsrc, wxCoord ysrc, wxRasterOperationMode rop = wxCOPY, bool useMask = false, wxCoord xsrcMask = wxDefaultCoord, wxCoord ysrcMask = wxDefaultCoord) override;
  void DoGetSize(int* w, int* h) const override
  {
    GetDeviceSize(w, h);
  }
    // init the dc
  void Init();
  wxPrintData m_printData;
private:
  wxDECLARE_CLASS(wxPrinterDCImpl);
  wxDECLARE_NO_COPY_CLASS(wxPrinterDCImpl);
};
// Gets an HDC for the specified printer configuration
WXHDC WXDLLIMPEXP_CORE wxGetPrinterDC(const wxPrintData& data);
// ------------------------------------------------------------------------
//    wxPrinterDCromHDC
//
class WXDLLIMPEXP_CORE wxPrinterDCFromHDC : public wxPrinterDC
{
public:
  wxPrinterDCFromHDC(WXHDC theDC)
    : wxPrinterDC(new wxPrinterDCImpl(this, theDC))
  {
  }
};
#  endif
#endif
