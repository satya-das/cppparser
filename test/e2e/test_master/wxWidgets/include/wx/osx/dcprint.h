/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/dcprint.h
// Purpose:     wxPrinterDC class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_DCPRINT_H_
#  define _WX_DCPRINT_H_
#  include "wx/dc.h"
#  include "wx/dcgraph.h"
#  include "wx/cmndata.h"
class wxNativePrinterDC;
class WXDLLIMPEXP_CORE wxPrinterDCImpl : public wxGCDCImpl
{
#  if  wxUSE_PRINTING_ARCHITECTURE
public:
  wxPrinterDCImpl(wxPrinterDC* owner, const wxPrintData& printdata);
  virtual ~wxPrinterDCImpl();
  bool StartDoc(const wxString&) override;
  void EndDoc() override;
  void StartPage() override;
  void EndPage() override;
  wxRect GetPaperRect() const override;
  wxPrintData& GetPrintData()
  {
    return m_printData;
  }
  wxSize GetPPI() const override;
protected:
  void DoGetSize(int* width, int* height) const override;
  wxPrintData m_printData;
  wxNativePrinterDC* m_nativePrinterDC;
  wxDECLARE_CLASS(wxPrinterDC);
#  endif
};
#endif
    // _WX_DCPRINT_H_
