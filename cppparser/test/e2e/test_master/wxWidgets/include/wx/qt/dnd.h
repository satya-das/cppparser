/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/dnd.h
// Author:      Peter Most
// Copyright:   (c) Peter Most
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_DND_H_
#  define _WX_QT_DND_H_
#  define wxDROP_ICON(name)	   wxCursor(name##_xpm)
class WXDLLIMPEXP_CORE wxDropTarget : public wxDropTargetBase
{
public:
  wxDropTarget(wxDataObject* dataObject = NULL);
  virtual ~wxDropTarget();
  bool OnDrop(wxCoord x, wxCoord y) override;
  wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def) override;
  bool GetData() override;
  wxDataFormat GetMatchingPair();
  void ConnectTo(QWidget* widget);
  void Disconnect();
private:
  class Impl;
  Impl* m_pImpl;
};
class WXDLLIMPEXP_CORE wxDropSource : public wxDropSourceBase
{
public:
  wxDropSource(wxWindow* win = NULL, const wxCursor& copy = wxNullCursor, const wxCursor& move = wxNullCursor, const wxCursor& none = wxNullCursor);
  wxDropSource(wxDataObject& data, wxWindow* win, const wxCursor& copy = wxNullCursor, const wxCursor& move = wxNullCursor, const wxCursor& none = wxNullCursor);
  wxDragResult DoDragDrop(int flags = wxDrag_CopyOnly) override;
private:
  wxWindow* m_parentWindow;
};
#endif
