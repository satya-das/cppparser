/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/frame.h
// Purpose:     wxFrame class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_FRAME_H_
#  define _WX_FRAME_H_
#  include "wx/toolbar.h"
#  include "wx/accel.h"
#  include "wx/icon.h"
class WXDLLIMPEXP_FWD_CORE wxMacToolTip;
class WXDLLIMPEXP_CORE wxFrame : public wxFrameBase
{
public:
    // construction
  wxFrame()
  {
   }
  wxFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr))
  {

        Create(parent, id, title, pos, size, style, name);
      }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr));
    // implementation only from now on
    // -------------------------------

    // get the origin of the client area (which may be different from (0, 0)
    // if the frame has a toolbar) in client coordinates
  wxPoint GetClientAreaOrigin() const override;
    // override some more virtuals
  bool Show(bool show = true) override;
  bool Enable(bool enable = true) override;
    // event handlers
  void OnActivate(wxActivateEvent& event);
  void OnSysColourChanged(wxSysColourChangedEvent& event);
    // Toolbar
#  if  wxUSE_TOOLBAR
  wxToolBar* CreateToolBar(long style = -1, wxWindowID id = -1, const wxString& name = wxASCII_STR(wxToolBarNameStr)) override;
  void SetToolBar(wxToolBar* toolbar) override;
#  endif
    // Status bar
#  if  wxUSE_STATUSBAR
  wxStatusBar* OnCreateStatusBar(int number = 1, long style = wxSTB_DEFAULT_STYLE, wxWindowID id = 0, const wxString& name = wxASCII_STR(wxStatusLineNameStr)) override;
#  endif
  void PositionBars();
    // internal response to size events
  void MacOnInternalSize() override
  { PositionBars(); }
#  if  wxUSE_TOOLBAR
protected:
  void PositionToolBar() override;
#  endif
#  if  wxUSE_STATUSBAR
  void PositionStatusBar() override;
#  endif
    // override base class virtuals
  void DoGetClientSize(int* width, int* height) const override;
  void DoSetClientSize(int width, int height) override;
#  if  wxUSE_MENUBAR
  void DetachMenuBar() override;
  void AttachMenuBar(wxMenuBar* menubar) override;
#  endif
  bool MacIsChildOfClientArea(const wxWindow* child) const override;
  wxDECLARE_EVENT_TABLE();
  wxDECLARE_DYNAMIC_CLASS(wxFrame);
};
#endif
    // _WX_FRAME_H_
