/////////////////////////////////////////////////////////////////////////////
// Name:        wx/imaggif.h
// Purpose:     wxImage GIF handler
// Author:      Vaclav Slavik, Guillermo Rodriguez Garcia, Gershon Elber, Troels K
// Copyright:   (c) 1999-2011 Vaclav Slavik, Guillermo Rodriguez Garcia, Gershon Elber, Troels K
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_IMAGGIF_H_
#  define _WX_IMAGGIF_H_
#  include "wx/image.h"
//-----------------------------------------------------------------------------
// wxGIFHandler
//-----------------------------------------------------------------------------
#  if  wxUSE_GIF
#    define wxIMAGE_OPTION_GIF_COMMENT	wxT("GifComment")
#    define wxIMAGE_OPTION_GIF_TRANSPARENCY	wxS("Transparency")
#    define wxIMAGE_OPTION_GIF_TRANSPARENCY_HIGHLIGHT	wxS("Highlight")
#    define wxIMAGE_OPTION_GIF_TRANSPARENCY_UNCHANGED	wxS("Unchanged")
struct wxRGB;
struct GifHashTableType;
class WXDLLIMPEXP_FWD_CORE wxImageArray;
class WXDLLIMPEXP_CORE wxGIFHandler : public wxImageHandler
{
public:
  inline wxGIFHandler()
  {

        m_name = wxT("GIF file");
        m_extension = wxT("gif");
        m_type = wxBITMAP_TYPE_GIF;
        m_mime = wxT("image/gif");
        m_hashTable = NULL;
      }
#    if  wxUSE_STREAMS
  bool LoadFile(wxImage* image, wxInputStream& stream, bool verbose = true, int index = -1) override;
  bool SaveFile(wxImage* image, wxOutputStream& stream, bool verbose = true) override;
    // Save animated gif
  bool SaveAnimation(const wxImageArray& images, wxOutputStream* stream, bool verbose = true, int delayMilliSecs = 1000);
protected:
  int DoGetImageCount(wxInputStream& stream) override;
  bool DoCanRead(wxInputStream& stream) override;
  bool DoSaveFile(const wxImage&, wxOutputStream*, bool verbose, bool first, int delayMilliSecs, bool loop, const wxRGB* pal, int palCount, int mask_index);
#    endif
    // Declarations for saving
  unsigned long m_crntShiftDWord;
  int m_pixelCount;
  struct GifHashTableType* m_hashTable;
  wxInt16 m_EOFCode, m_clearCode, m_runningCode, m_runningBits, m_maxCode1, m_crntCode, m_crntShiftState;
  wxUint8 m_LZBuf[256];
  bool InitHashTable();
  void ClearHashTable();
  void InsertHashTable(unsigned long key, int code);
  int ExistsHashTable(unsigned long key);
#    if  wxUSE_STREAMS
  bool CompressOutput(wxOutputStream*, int code);
  bool SetupCompress(wxOutputStream*, int bpp);
  bool CompressLine(wxOutputStream*, const wxUint8* line, int lineLen);
#    endif
  wxDECLARE_DYNAMIC_CLASS(wxGIFHandler);
};
#  endif
#endif
