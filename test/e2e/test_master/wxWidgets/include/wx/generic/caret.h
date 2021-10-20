///////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/caret.h
// Purpose:     generic wxCaret class
// Author:      Vadim Zeitlin (original code by Robert Roebling)
// Modified by:
// Created:     25.05.99
// Copyright:   (c) wxWidgets team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_CARET_H_
#  define _WX_CARET_H_
#  include "wx/timer.h"
#  include "wx/dc.h"
#  include "wx/overlay.h"
#  ifdef wxHAS_NATIVE_OVERLAY
#    define wxHAS_CARET_USING_OVERLAYS
#  endif
class WXDLLIMPEXP_FWD_CORE wxCaret;
class WXDLLIMPEXP_CORE wxCaretTimer : public wxTimer
{
public:
  wxCaretTimer(wxCaret* caret);
  void Notify() override;
private:
  wxCaret* m_caret;
};
class WXDLLIMPEXP_CORE wxCaret : public wxCaretBase
{
public:
    // ctors
    // -----
        // default - use Create()
  wxCaret()
    :  m_timer(this)
  {
 InitGeneric();
  }
        // creates a block caret associated with the given window
  wxCaret(wxWindowBase* window, int width, int height)
    :  wxCaretBase(window, width, height), m_timer(this)
  {
 InitGeneric();
  }
  wxCaret(wxWindowBase* window, const wxSize& size)
    :  wxCaretBase(window, size), m_timer(this)
  {
 InitGeneric();
  }
  virtual ~wxCaret();
    // implementation
    // --------------

    // called by wxWindow (not using the event tables)
  void OnSetFocus() override;
  void OnKillFocus() override;
    // called by wxCaretTimer
  void OnTimer();
protected:
  void DoShow() override;
  void DoHide() override;
  void DoMove() override;
  void DoSize() override;
    // blink the caret once
  void Blink();
    // refresh the caret
  void Refresh();
    // draw the caret on the given DC
  void DoDraw(wxDC* dc, wxWindow* win);
private:
    // GTK specific initialization
  void InitGeneric();
#  ifdef wxHAS_CARET_USING_OVERLAYS
    // the overlay for displaying the caret
  wxOverlay m_overlay;
#  else 
    // the bitmap holding the part of window hidden by the caret when it was
    // at (m_xOld, m_yOld)
  wxBitmap m_bmpUnderCaret;
  int m_xOld, m_yOld;
#  endif
  wxCaretTimer m_timer;
  bool m_blinkedOut, m_hasFocus;
};
#endif
