/////////////////////////////////////////////////////////////////////////////
// Name:        wx/imagpcx.h
// Purpose:     wxImage PCX handler
// Author:      Guillermo Rodriguez Garcia <guille@iies.es>
// Copyright:   (c) 1999 Guillermo Rodriguez Garcia
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_IMAGPCX_H_
#  define _WX_IMAGPCX_H_
#  include "wx/image.h"
//-----------------------------------------------------------------------------
// wxPCXHandler
//-----------------------------------------------------------------------------
#  if  wxUSE_PCX
class WXDLLIMPEXP_CORE wxPCXHandler : public wxImageHandler
{
public:
  inline wxPCXHandler()
  {
    m_name = wxT("PCX file");
    m_extension = wxT("pcx");
    m_type = wxBITMAP_TYPE_PCX;
    m_mime = wxT("image/pcx");
  }
#    if  wxUSE_STREAMS
  bool LoadFile(wxImage* image, wxInputStream& stream, bool verbose = true, int index = -1) override;
  bool SaveFile(wxImage* image, wxOutputStream& stream, bool verbose = true) override;
protected:
  bool DoCanRead(wxInputStream& stream) override;
#    endif
private:
  wxDECLARE_DYNAMIC_CLASS(wxPCXHandler);
};
#  endif
#endif
  // _WX_IMAGPCX_H_
