///////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/apptrait.h
// Purpose:     class implementing wxAppTraits for MSW
// Author:      Vadim Zeitlin
// Modified by:
// Created:     21.06.2003
// Copyright:   (c) 2003 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_APPTRAIT_H_
#  define _WX_MSW_APPTRAIT_H_
// ----------------------------------------------------------------------------
// wxGUI/ConsoleAppTraits: must derive from wxAppTraits, not wxAppTraitsBase
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_BASE wxConsoleAppTraits : public wxConsoleAppTraitsBase
{
public:
  wxEventLoopBase* CreateEventLoop() override;
  void* BeforeChildWaitLoop() override;
  void AfterChildWaitLoop(void* data) override;
#  if  wxUSE_TIMER
  wxTimerImpl* CreateTimerImpl(wxTimer* timer) override;
#  endif
#  if  wxUSE_THREADS
  bool DoMessageFromThreadWait() override;
  WXDWORD WaitForThread(WXHANDLE hThread, int flags) override;
#  endif
  bool CanUseStderr() override
  {
    return true;
  }
  bool WriteToStderr(const wxString& text) override;
};
#  if  wxUSE_GUI
#    if  defined(__WXMSW__)
class WXDLLIMPEXP_CORE wxGUIAppTraits : public wxGUIAppTraitsBase
{
public:
  wxEventLoopBase* CreateEventLoop() override;
  void* BeforeChildWaitLoop() override;
  void AfterChildWaitLoop(void* data) override;
#      if  wxUSE_TIMER
  wxTimerImpl* CreateTimerImpl(wxTimer* timer) override;
#      endif
#      if  wxUSE_THREADS
  bool DoMessageFromThreadWait() override;
  WXDWORD WaitForThread(WXHANDLE hThread, int flags) override;
#      endif
  wxPortId GetToolkitVersion(int* majVer = NULL, int* minVer = NULL, int* microVer = NULL) const override;
  bool CanUseStderr() override;
  bool WriteToStderr(const wxString& text) override;
};
#    elif  defined(__WXGTK__)
class WXDLLIMPEXP_CORE wxGUIAppTraits : public wxGUIAppTraitsBase
{
public:
  virtual wxEventLoopBase* CreateEventLoop();
  virtual void* BeforeChildWaitLoop()
  { return NULL; }
  virtual void AfterChildWaitLoop(void*)
  { }
#      if  wxUSE_TIMER
  virtual wxTimerImpl* CreateTimerImpl(wxTimer* timer);
#      endif
#      if  wxUSE_THREADS && defined(__WXGTK20__)
  virtual void MutexGuiEnter();
  virtual void MutexGuiLeave();
#      endif
#      if  wxUSE_THREADS
  virtual bool DoMessageFromThreadWait()
  { return true; }
  virtual WXDWORD WaitForThread(WXHANDLE hThread, int)
  { return DoSimpleWaitForThread(hThread); }
#      endif
  virtual wxPortId GetToolkitVersion(int* majVer = NULL, int* minVer = NULL, int* microVer = NULL) const;
  virtual bool CanUseStderr()
  { return false; }
  virtual bool WriteToStderr(const wxString&)
  { return false; }
};
#    elif  defined(__WXQT__)
class WXDLLIMPEXP_CORE wxGUIAppTraits : public wxGUIAppTraitsBase
{
public:
  virtual wxEventLoopBase* CreateEventLoop();
  virtual void* BeforeChildWaitLoop()
  { return NULL; }
  virtual void AfterChildWaitLoop(void*)
  { }
#      if  wxUSE_TIMER
  virtual wxTimerImpl* CreateTimerImpl(wxTimer* timer);
#      endif
#      if  wxUSE_THREADS
  virtual bool DoMessageFromThreadWait()
  { return true; }
  virtual WXDWORD WaitForThread(WXHANDLE hThread, int)
  { return DoSimpleWaitForThread(hThread); }
#      endif
  virtual wxPortId GetToolkitVersion(int* majVer = NULL, int* minVer = NULL, int* microVer = NULL) const;
  virtual bool CanUseStderr()
  { return false; }
  virtual bool WriteToStderr(const wxString&)
  { return false; }
};
#    endif
#  endif
#endif
