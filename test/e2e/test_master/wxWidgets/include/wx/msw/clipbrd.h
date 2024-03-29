/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/clipbrd.h
// Purpose:     wxClipboad class and clipboard functions for MSW
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_CLIPBRD_H_
#  define _WX_CLIPBRD_H_
#  if  wxUSE_CLIPBOARD
// These functions superseded by wxClipboard, but retained in order to
// implement wxClipboard, and for compatibility.

// open/close the clipboard
WXDLLIMPEXP_CORE bool wxOpenClipboard();
WXDLLIMPEXP_CORE bool wxIsClipboardOpened();
#    define wxClipboardOpen	wxIsClipboardOpened
WXDLLIMPEXP_CORE bool wxCloseClipboard();
// get/set data
WXDLLIMPEXP_CORE bool wxEmptyClipboard();
#    if  !wxUSE_OLE
WXDLLIMPEXP_CORE bool wxSetClipboardData(wxDataFormat dataFormat, const void* data, int width = 0, int height = 0);
#    endif
// clipboard formats
WXDLLIMPEXP_CORE bool wxIsClipboardFormatAvailable(wxDataFormat dataFormat);
WXDLLIMPEXP_CORE wxDataFormat wxEnumClipboardFormats(wxDataFormat dataFormat);
WXDLLIMPEXP_CORE int wxRegisterClipboardFormat(wxChar* formatName);
WXDLLIMPEXP_CORE bool wxGetClipboardFormatName(wxDataFormat dataFormat, wxChar* formatName, int maxCount);
//-----------------------------------------------------------------------------
// wxClipboard
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxClipboard : public wxClipboardBase
{
public:
  wxClipboard();
  virtual ~wxClipboard();
    // open the clipboard before SetData() and GetData()
  bool Open() override;
    // close the clipboard after SetData() and GetData()
  void Close() override;
    // query whether the clipboard is opened
  bool IsOpened() const override;
    // set the clipboard data. all other formats will be deleted.
  bool SetData(wxDataObject* data) override;
    // add to the clipboard data.
  bool AddData(wxDataObject* data) override;
    // ask if data in correct format is available
  bool IsSupported(const wxDataFormat& format) override;
    // fill data with data on the clipboard (if available)
  bool GetData(wxDataObject& data) override;
    // clears wxTheClipboard and the system's clipboard if possible
  void Clear() override;
    // flushes the clipboard: this means that the data which is currently on
    // clipboard will stay available even after the application exits (possibly
    // eating memory), otherwise the clipboard will be emptied on exit
  bool Flush() override;
private:
  IDataObject* m_lastDataObject;
  bool m_isOpened;
  wxDECLARE_DYNAMIC_CLASS(wxClipboard);
};
#  endif
#endif
