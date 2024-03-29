/////////////////////////////////////////////////////////////////////////////
// Name:        wx/imagiff.h
// Purpose:     wxImage handler for Amiga IFF images
// Author:      Steffen Gutmann
// Copyright:   (c) Steffen Gutmann, 2002
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_IMAGE_IFF_H_
#  define _WX_IMAGE_IFF_H_
#  include "wx/image.h"
//-----------------------------------------------------------------------------
// wxIFFHandler
//-----------------------------------------------------------------------------
#  if  wxUSE_IMAGE && wxUSE_IFF
class WXDLLIMPEXP_CORE wxIFFHandler : public wxImageHandler
{
public:
  wxIFFHandler()
  {
    m_name = wxT("IFF file");
    m_extension = wxT("iff");
    m_type = wxBITMAP_TYPE_IFF;
    m_mime = wxT("image/x-iff");
  }
#    if  wxUSE_STREAMS
  bool LoadFile(wxImage* image, wxInputStream& stream, bool verbose = true, int index = -1) override;
  bool SaveFile(wxImage* image, wxOutputStream& stream, bool verbose = true) override;
protected:
  bool DoCanRead(wxInputStream& stream) override;
#    endif
  wxDECLARE_DYNAMIC_CLASS(wxIFFHandler);
};
#  endif
#endif
