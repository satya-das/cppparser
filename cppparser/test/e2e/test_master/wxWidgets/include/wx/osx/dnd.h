///////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/dnd.h
// Purpose:     Declaration of the wxDropTarget, wxDropSource class etc.
// Author:      Stefan Csomor
// Copyright:   (c) 1998 Stefan Csomor
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_DND_H_
#  define _WX_DND_H_
#  include "wx/defs.h"
#  include "wx/object.h"
#  include "wx/string.h"
#  include "wx/string.h"
#  include "wx/dataobj.h"
#  include "wx/cursor.h"
//-------------------------------------------------------------------------
// classes
//-------------------------------------------------------------------------
class WXDLLIMPEXP_FWD_CORE wxWindow;
class WXDLLIMPEXP_FWD_CORE wxDropTarget;
class WXDLLIMPEXP_FWD_CORE wxTextDropTarget;
class WXDLLIMPEXP_FWD_CORE wxFileDropTarget;
class WXDLLIMPEXP_FWD_CORE wxDropSource;
class WXDLLIMPEXP_FWD_CORE wxOSXDataSource;
// ----------------------------------------------------------------------------
// macros
// ----------------------------------------------------------------------------

// this macro may be used instead for wxDropSource ctor arguments: it will use
// the icon 'name' from an XPM file under GTK, but will expand to something
// else under MSW. If you don't use it, you will have to use #ifdef in the
// application code.
#  define wxDROP_ICON(X)	   wxCursor(X##_xpm)
//-------------------------------------------------------------------------
// wxDropTarget
//-------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxDropTarget : public wxDropTargetBase
{
public:
  wxDropTarget(wxDataObject* dataObject = NULL);
  wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def) override;
  bool OnDrop(wxCoord x, wxCoord y) override;
  wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def) override;
  bool GetData() override;
    // NOTE: This is needed by the generic wxDataViewCtrl, not sure how to implement.
  virtual wxDataFormat GetMatchingPair();
  bool CurrentDragHasSupportedFormat();
  void SetCurrentDragSource(wxOSXDataSource* dragpasteboard)
  {
    m_currentDragPasteboard = dragpasteboard;
  }
protected:
  wxOSXDataSource* m_currentDragPasteboard;
};
//-------------------------------------------------------------------------
// wxDropSource
//-------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxDropSource : public wxDropSourceBase
{
public:
    // ctors: if you use default ctor you must call SetData() later!
    //
    // NB: the "wxWindow *win" parameter is unused and is here only for wxGTK
    //     compatibility, as well as both icon parameters
  wxDropSource(wxWindow* win = NULL, const wxCursor& cursorCopy = wxNullCursor, const wxCursor& cursorMove = wxNullCursor, const wxCursor& cursorStop = wxNullCursor);
    /* constructor for setting one data object */
  wxDropSource(wxDataObject& data, wxWindow* win, const wxCursor& cursorCopy = wxNullCursor, const wxCursor& cursorMove = wxNullCursor, const wxCursor& cursorStop = wxNullCursor);
  virtual ~wxDropSource();
    // do it (call this in response to a mouse button press, for example)
    // params: if bAllowMove is false, data can be only copied
  wxDragResult DoDragDrop(int flags = wxDrag_CopyOnly) override;
  wxWindow* GetWindow()
  {
    return m_window;
  }
  void SetCurrentDragPasteboard(void* dragpasteboard)
  {
    m_currentDragPasteboard = dragpasteboard;
  }
  bool MacInstallDefaultCursor(wxDragResult effect);
  static wxDropSource* GetCurrentDropSource();
protected:
  wxWindow* m_window;
  void* m_currentDragPasteboard;
};
#endif
   //_WX_DND_H_
