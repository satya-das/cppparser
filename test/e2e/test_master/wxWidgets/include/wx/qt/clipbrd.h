/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/toolbar.h
// Author:      Sean D'Epagnier
// Copyright:   (c) Sean D'Epagnier 2014
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_CLIPBRD_H_
#  define _WX_QT_CLIPBRD_H_
#  include "wx/weakref.h"
class QtClipBoardSignalHandler;
class WXDLLIMPEXP_CORE wxClipboard : public wxClipboardBase
{
public:
  wxClipboard();
  ~wxClipboard();
  bool Open() override;
  void Close() override;
  bool IsOpened() const override;
  bool AddData(wxDataObject* data) override;
  bool SetData(wxDataObject* data) override;
  bool GetData(wxDataObject& data) override;
  void Clear() override;
  bool IsSupported(const wxDataFormat& format) override;
  bool IsSupportedAsync(wxEvtHandler* sink) override;
private:
  friend class QtClipBoardSignalHandler;
  int Mode();
  QtClipBoardSignalHandler* m_SignalHandler;
  wxEvtHandlerRef m_sink;
  bool m_open;
  wxDECLARE_DYNAMIC_CLASS(wxClipboard);
};
#endif
