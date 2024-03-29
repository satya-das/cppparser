///////////////////////////////////////////////////////////////////////////////
// Name:        wx/textfile.h
// Purpose:     class wxTextFile to work with text files of _small_ size
//              (file is fully loaded in memory) and which understands CR/LF
//              differences between platforms.
// Author:      Vadim Zeitlin
// Modified by:
// Created:     03.04.98
// Copyright:   (c) 1998 Vadim Zeitlin <zeitlin@dptmaths.ens-cachan.fr>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_TEXTFILE_H
#  define _WX_TEXTFILE_H
#  include "wx/defs.h"
#  include "wx/textbuf.h"
#  if  wxUSE_TEXTFILE
#    include "wx/file.h"
// ----------------------------------------------------------------------------
// wxTextFile
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_BASE wxTextFile : public wxTextBuffer
{
public:
    // constructors
  wxTextFile()
  {
  }
  wxTextFile(const wxString& strFileName);
protected:
    // implement the base class pure virtuals
  bool OnExists() const override;
  bool OnOpen(const wxString& strBufferName, wxTextBufferOpenMode openMode) override;
  bool OnClose() override;
  bool OnRead(const wxMBConv& conv) override;
  bool OnWrite(wxTextFileType typeNew, const wxMBConv& conv) override;
private:
  wxFile m_file;
  wxDECLARE_NO_COPY_CLASS(wxTextFile);
};
#  else 
// old code relies on the static methods of wxTextFile being always available
// and they still are available in wxTextBuffer (even if !wxUSE_TEXTBUFFER), so
// make it possible to use them in a backwards compatible way
typedef wxTextBuffer wxTextFile;
#  endif
#endif
