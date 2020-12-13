/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/app.h
// Purpose:     wxApp definition for wxGTK
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling, Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_APP_H_
#  define _WX_GTK_APP_H_
//-----------------------------------------------------------------------------
// classes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// wxApp
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxApp : public wxAppBase
{
public:
  wxApp();
  virtual ~wxApp();
    /* override for altering the way wxGTK initializes the GUI
     * (palette/visual/colorcube). under wxMSW, OnInitGui() does nothing by
     * default. when overriding this method, the code in it is likely to be
     * platform dependent, otherwise use OnInit(). */
  bool SetNativeTheme(const wxString& theme) override;
  bool OnInitGui() override;
    // override base class (pure) virtuals
  void WakeUpIdle() override;
  bool Initialize(int& argc, wxChar** argv) override;
  void CleanUp() override;
  void OnAssertFailure(const wxChar* file, int line, const wxChar* func, const wxChar* cond, const wxChar* msg) override;
    // GTK-specific methods
    // -------------------

    // this can be overridden to return a specific visual to be used for GTK+
    // instead of the default one (it's used by wxGLApp)
    //
    // must return XVisualInfo pointer (it is not freed by caller)
  virtual void* GetXVisualInfo()
  {
    return NULL;
  }
    // Check if we're using a global menu. Currently this is only true when
    // running under Ubuntu Unity and global menu is not disabled.
    //
    // This is mostly used in the implementation in order to work around
    // various bugs arising due to this.
  static bool GTKIsUsingGlobalMenu();
    // implementation only from now on
    // -------------------------------

    // check for pending events, without interference from our idle source
  bool EventsPending();
  bool DoIdle();
private:
    // true if we're inside an assert modal dialog
  bool m_isInAssert;
#  if  wxUSE_THREADS
  wxMutex m_idleMutex;
#  endif
  unsigned m_idleSourceId;
  wxDECLARE_DYNAMIC_CLASS(wxApp);
};
#endif
