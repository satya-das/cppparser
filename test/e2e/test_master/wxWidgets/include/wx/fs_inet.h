/////////////////////////////////////////////////////////////////////////////
// Name:        wx/fs_inet.h
// Purpose:     HTTP and FTP file system
// Author:      Vaclav Slavik
// Copyright:   (c) 1999 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_FS_INET_H_
#  define _WX_FS_INET_H_
#  include "wx/defs.h"
#  if  wxUSE_FILESYSTEM && wxUSE_FS_INET && wxUSE_STREAMS && wxUSE_SOCKETS
#    include "wx/filesys.h"
// ----------------------------------------------------------------------------
// wxInternetFSHandler
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_NET wxInternetFSHandler : public wxFileSystemHandler
{
public:
  bool CanOpen(const wxString& location) override;
  wxFSFile* OpenFile(wxFileSystem& fs, const wxString& location) override;
};
#  endif
  // wxUSE_FILESYSTEM && wxUSE_FS_INET && wxUSE_STREAMS && wxUSE_SOCKETS
#endif
