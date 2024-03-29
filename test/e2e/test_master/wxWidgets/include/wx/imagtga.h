/////////////////////////////////////////////////////////////////////////////
// Name:        wx/imagtga.h
// Purpose:     wxImage TGA handler
// Author:      Seth Jackson
// Copyright:   (c) 2005 Seth Jackson
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_IMAGTGA_H_
#  define _WX_IMAGTGA_H_
#  include "wx/image.h"
//-----------------------------------------------------------------------------
// wxTGAHandler
//-----------------------------------------------------------------------------
#  if  wxUSE_TGA
class WXDLLIMPEXP_CORE wxTGAHandler : public wxImageHandler
{
public:
  wxTGAHandler()
  {
    m_name = wxT("TGA file");
    m_extension = wxT("tga");
    m_altExtensions.Add(wxT("tpic"));
    m_type = wxBITMAP_TYPE_TGA;
    m_mime = wxT("image/tga");
  }
#    if  wxUSE_STREAMS
  bool LoadFile(wxImage* image, wxInputStream& stream, bool verbose = true, int index = -1) override;
  bool SaveFile(wxImage* image, wxOutputStream& stream, bool verbose = true) override;
protected:
  bool DoCanRead(wxInputStream& stream) override;
#    endif
  wxDECLARE_DYNAMIC_CLASS(wxTGAHandler);
};
#  endif
#endif
