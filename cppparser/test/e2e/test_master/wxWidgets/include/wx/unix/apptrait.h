///////////////////////////////////////////////////////////////////////////////
// Name:        wx/unix/apptrait.h
// Purpose:     standard implementations of wxAppTraits for Unix
// Author:      Vadim Zeitlin
// Modified by:
// Created:     23.06.2003
// Copyright:   (c) 2003 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_UNIX_APPTRAIT_H_
#  define _WX_UNIX_APPTRAIT_H_
// ----------------------------------------------------------------------------
// wxGUI/ConsoleAppTraits: must derive from wxAppTraits, not wxAppTraitsBase
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_BASE wxConsoleAppTraits : public wxConsoleAppTraitsBase
{
public:
#  if  wxUSE_CONSOLE_EVENTLOOP
  wxEventLoopBase* CreateEventLoop() override;
#  endif
#  if  wxUSE_TIMER
  wxTimerImpl* CreateTimerImpl(wxTimer* timer) override;
#  endif
};
#  if  wxUSE_GUI
// GTK+ and Motif integrate sockets and child processes monitoring directly in
// their main loop, the other Unix ports do it at wxEventLoop level and so use
// the non-GUI traits and don't need anything here
//
// TODO: Should we use XtAddInput() for wxX11 too? Or, vice versa, if there is
//       no advantage in doing this compared to the generic way currently used
//       by wxX11, should we continue to use GTK/Motif-specific stuff?
#    if  defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXQT__)
#      define wxHAS_GUI_FDIOMANAGER
#      define wxHAS_GUI_PROCESS_CALLBACKS
#    endif
#    if  defined(__WXMAC__)
#      define wxHAS_GUI_PROCESS_CALLBACKS
#      define wxHAS_GUI_SOCKET_MANAGER
#    endif
class WXDLLIMPEXP_CORE wxGUIAppTraits : public wxGUIAppTraitsBase
{
public:
  wxEventLoopBase* CreateEventLoop() override;
  int WaitForChild(wxExecuteData& execData) override;
#    if  wxUSE_TIMER
  wxTimerImpl* CreateTimerImpl(wxTimer* timer) override;
#    endif
#    if  wxUSE_THREADS && defined(__WXGTK20__)
  void MutexGuiEnter() override;
  void MutexGuiLeave() override;
#    endif
  wxPortId GetToolkitVersion(int* majVer = NULL, int* minVer = NULL, int* microVer = NULL) const override;
#    ifdef __WXGTK20__
  wxString GetDesktopEnvironment() const override;
#    endif
#    if  defined(__WXGTK20__)
  bool ShowAssertDialog(const wxString& msg) override;
#    endif
#    ifdef wxHAS_GUI_SOCKET_MANAGER
  wxSocketManager* GetSocketManager() override;
#    endif
#    ifdef wxHAS_GUI_FDIOMANAGER
  wxFDIOManager* GetFDIOManager() override;
#    endif
#    if  wxUSE_EVENTLOOP_SOURCE
  wxEventLoopSourcesManagerBase* GetEventLoopSourcesManager() override;
#    endif
};
#  endif
#endif
