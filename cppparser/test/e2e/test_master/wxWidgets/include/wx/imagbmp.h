/////////////////////////////////////////////////////////////////////////////
// Name:        wx/imagbmp.h
// Purpose:     wxImage BMP, ICO, CUR and ANI handlers
// Author:      Robert Roebling, Chris Elliott
// Copyright:   (c) Robert Roebling, Chris Elliott
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_IMAGBMP_H_
#  define _WX_IMAGBMP_H_
#  include "wx/image.h"
// defines for saving the BMP file in different formats, Bits Per Pixel
// USE: wximage.SetOption( wxIMAGE_OPTION_BMP_FORMAT, wxBMP_xBPP );
#  define wxIMAGE_OPTION_BMP_FORMAT	wxString(wxT("wxBMP_FORMAT"))
// These two options are filled in upon reading CUR file and can (should) be
// specified when saving a CUR file - they define the hotspot of the cursor:
#  define wxIMAGE_OPTION_CUR_HOTSPOT_X	wxT("HotSpotX")
#  define wxIMAGE_OPTION_CUR_HOTSPOT_Y	wxT("HotSpotY")
enum
{
  wxBMP_24BPP = 24,
    //wxBMP_16BPP      = 16, // wxQuantize can only do 236 colors?
  wxBMP_8BPP = 8,
  wxBMP_8BPP_GREY = 9,
  wxBMP_8BPP_GRAY = wxBMP_8BPP_GREY,
  wxBMP_8BPP_RED = 10,
  wxBMP_8BPP_PALETTE = 11,
  wxBMP_4BPP = 4,
  wxBMP_1BPP = 1,
  wxBMP_1BPP_BW = 2,
};
// ----------------------------------------------------------------------------
// wxBMPHandler
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxBMPHandler : public wxImageHandler
{
public:
  wxBMPHandler()
  {
    m_name = wxT("Windows bitmap file");
    m_extension = wxT("bmp");
    m_type = wxBITMAP_TYPE_BMP;
    m_mime = wxT("image/x-bmp");
  }
#  if  wxUSE_STREAMS
  bool SaveFile(wxImage* image, wxOutputStream& stream, bool verbose = true) override;
  bool LoadFile(wxImage* image, wxInputStream& stream, bool verbose = true, int index = -1) override;
protected:
  bool DoCanRead(wxInputStream& stream) override;
  bool SaveDib(wxImage* image, wxOutputStream& stream, bool verbose, bool IsBmp, bool IsMask);
  bool DoLoadDib(wxImage* image, int width, int height, int bpp, int ncolors, int comp, wxFileOffset bmpOffset, wxInputStream& stream, bool verbose, bool IsBmp, bool hasPalette, int colEntrySize = 4);
  bool LoadDib(wxImage* image, wxInputStream& stream, bool verbose, bool IsBmp);
#  endif
private:
  wxDECLARE_DYNAMIC_CLASS(wxBMPHandler);
};
#  if  wxUSE_ICO_CUR
// ----------------------------------------------------------------------------
// wxICOHandler
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxICOHandler : public wxBMPHandler
{
public:
  wxICOHandler()
  {
    m_name = wxT("Windows icon file");
    m_extension = wxT("ico");
    m_type = wxBITMAP_TYPE_ICO;
    m_mime = wxT("image/x-ico");
  }
#    if  wxUSE_STREAMS
  bool SaveFile(wxImage* image, wxOutputStream& stream, bool verbose = true) override;
  bool LoadFile(wxImage* image, wxInputStream& stream, bool verbose = true, int index = -1) override;
  virtual bool DoLoadFile(wxImage* image, wxInputStream& stream, bool verbose, int index);
protected:
  int DoGetImageCount(wxInputStream& stream) override;
  bool DoCanRead(wxInputStream& stream) override;
#    endif
private:
  wxDECLARE_DYNAMIC_CLASS(wxICOHandler);
};
// ----------------------------------------------------------------------------
// wxCURHandler
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxCURHandler : public wxICOHandler
{
public:
  wxCURHandler()
  {
    m_name = wxT("Windows cursor file");
    m_extension = wxT("cur");
    m_type = wxBITMAP_TYPE_CUR;
    m_mime = wxT("image/x-cur");
  }
    // VS: This handler's meat is implemented inside wxICOHandler (the two
    //     formats are almost identical), but we hide this fact at
    //     the API level, since it is a mere implementation detail.
protected:
#    if  wxUSE_STREAMS
  bool DoCanRead(wxInputStream& stream) override;
#    endif
private:
  wxDECLARE_DYNAMIC_CLASS(wxCURHandler);
};
// ----------------------------------------------------------------------------
// wxANIHandler
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxANIHandler : public wxCURHandler
{
public:
  wxANIHandler()
  {
    m_name = wxT("Windows animated cursor file");
    m_extension = wxT("ani");
    m_type = wxBITMAP_TYPE_ANI;
    m_mime = wxT("image/x-ani");
  }
#    if  wxUSE_STREAMS
  bool SaveFile(wxImage*, wxOutputStream&, bool) override
  {
    return false;
  }
  bool LoadFile(wxImage* image, wxInputStream& stream, bool verbose = true, int index = -1) override;
protected:
  int DoGetImageCount(wxInputStream& stream) override;
  bool DoCanRead(wxInputStream& stream) override;
#    endif
private:
  wxDECLARE_DYNAMIC_CLASS(wxANIHandler);
};
#  endif
#endif
