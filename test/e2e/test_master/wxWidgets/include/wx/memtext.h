///////////////////////////////////////////////////////////////////////////////
// Name:        wx/memtext.h
// Purpose:     wxMemoryText allows to use wxTextBuffer without a file
// Created:     14.11.01
// Author:      Morten Hanssen
// Copyright:   (c) 2001 Morten Hanssen
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MEMTEXT_H
#  define _WX_MEMTEXT_H
#  include "wx/defs.h"
// there is no separate setting for wxMemoryText, it's smallish anyhow
#  if  wxUSE_TEXTBUFFER
// ----------------------------------------------------------------------------
// wxMemoryText
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_BASE wxMemoryText : public wxTextBuffer
{
public:
    // Constructors.
  wxMemoryText()
  {

  }
  wxMemoryText(const wxString& name)
    :  wxTextBuffer(name)
  {

  }
protected:
  bool OnExists() const override
  {
 return false;
  }
  bool OnOpen(const wxString&, wxTextBufferOpenMode) override
  {
 return true;
  }
  bool OnClose() override
  {
 return true;
  }
  bool OnRead(const wxMBConv&) override
  {
 return true;
  }
  bool OnWrite(wxTextFileType, const wxMBConv& = wxMBConvUTF8()) override
  {
 return true;
  }
  wxDECLARE_NO_COPY_CLASS(wxMemoryText);
};
#  endif
#endif
