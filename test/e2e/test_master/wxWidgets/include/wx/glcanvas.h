/////////////////////////////////////////////////////////////////////////////
// Name:        wx/glcanvas.h
// Purpose:     wxGLCanvas base header
// Author:      Julian Smart
// Modified by:
// Created:
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GLCANVAS_H_BASE_
#  define _WX_GLCANVAS_H_BASE_
#  include "wx/defs.h"
#  if  wxUSE_GLCANVAS
#    include "wx/app.h"
#    include "wx/palette.h"
#    include "wx/window.h"
class WXDLLIMPEXP_FWD_GL wxGLCanvas;
class WXDLLIMPEXP_FWD_GL wxGLContext;
// ----------------------------------------------------------------------------
// Constants for attributes list
// ----------------------------------------------------------------------------

// Notice that not all implementation support options such as stereo, auxiliary
// buffers, alpha channel, and accumulator buffer, use IsDisplaySupported() to
// check for individual attributes support.
enum
{
  WX_GL_RGBA = 1,
  WX_GL_BUFFER_SIZE,
  WX_GL_LEVEL,
  WX_GL_DOUBLEBUFFER,
  WX_GL_STEREO,
  WX_GL_AUX_BUFFERS,
  WX_GL_MIN_RED,
  WX_GL_MIN_GREEN,
  WX_GL_MIN_BLUE,
  WX_GL_MIN_ALPHA,
  WX_GL_DEPTH_SIZE,
  WX_GL_STENCIL_SIZE,
  WX_GL_MIN_ACCUM_RED,
  WX_GL_MIN_ACCUM_GREEN,
  WX_GL_MIN_ACCUM_BLUE,
  WX_GL_MIN_ACCUM_ALPHA,
  WX_GL_SAMPLE_BUFFERS,
  WX_GL_SAMPLES,
  WX_GL_FRAMEBUFFER_SRGB,
    // Context attributes
  WX_GL_CORE_PROFILE,
  WX_GL_MAJOR_VERSION,
  WX_GL_MINOR_VERSION,
  wx_GL_COMPAT_PROFILE,
  WX_GL_FORWARD_COMPAT,
  WX_GL_ES2,
  WX_GL_DEBUG,
  WX_GL_ROBUST_ACCESS,
  WX_GL_NO_RESET_NOTIFY,
  WX_GL_LOSE_ON_RESET,
  WX_GL_RESET_ISOLATION,
  WX_GL_RELEASE_FLUSH,
  WX_GL_RELEASE_NONE
};
#    define wxGLCanvasName	wxT("GLCanvas")
// ----------------------------------------------------------------------------
// wxGLAttribsBase: OpenGL rendering attributes
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLAttribsBase
{
public:
  wxGLAttribsBase()
  {
 Reset();
  }
    // Setters
  void AddAttribute(int attribute)
  {
 m_GLValues.push_back(attribute);
  }
    // Search for searchVal and combine the next value with combineVal
  void AddAttribBits(int searchVal, int combineVal);
    // ARB functions necessity
  void SetNeedsARB(bool needsARB = true)
  {
 m_needsARB = needsARB;
  }
    // Delete contents
  void Reset()
  {
        m_GLValues.clear();
        m_needsARB = false;
  }
    // Accessors
  const int* GetGLAttrs() const
  {
        return (m_GLValues.empty() || !m_GLValues[0]) ? NULL : &*m_GLValues.begin();
  }
  int GetSize() const
  {
 return (int)(m_GLValues.size());
  }
    // ARB function (e.g. wglCreateContextAttribsARB) is needed
  bool NeedsARB() const
  {
 return m_needsARB;
  }
private:
  wxVector<int> m_GLValues;
  bool m_needsARB;
};
// ----------------------------------------------------------------------------
// wxGLContextAttrs: OpenGL rendering context attributes
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLContextAttrs : public wxGLAttribsBase
{
public:
    // Setters, allowing chained calls
  wxGLContextAttrs& CoreProfile();
  wxGLContextAttrs& MajorVersion(int val);
  wxGLContextAttrs& MinorVersion(int val);
  wxGLContextAttrs& OGLVersion(int vmayor, int vminor)
  {
 return MajorVersion(vmayor).MinorVersion(vminor);
  }
  wxGLContextAttrs& CompatibilityProfile();
  wxGLContextAttrs& ForwardCompatible();
  wxGLContextAttrs& ES2();
  wxGLContextAttrs& DebugCtx();
  wxGLContextAttrs& Robust();
  wxGLContextAttrs& NoResetNotify();
  wxGLContextAttrs& LoseOnReset();
  wxGLContextAttrs& ResetIsolation();
  wxGLContextAttrs& ReleaseFlush(int val = 1);
  wxGLContextAttrs& PlatformDefaults();
  void EndList();
    // Currently only used for X11 context creation
  bool x11Direct;
  bool renderTypeRGBA;
};
// ----------------------------------------------------------------------------
// wxGLAttributes: canvas configuration
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLAttributes : public wxGLAttribsBase
{
public:
    // Setters, allowing chained calls
  wxGLAttributes& RGBA();
  wxGLAttributes& BufferSize(int val);
  wxGLAttributes& Level(int val);
  wxGLAttributes& DoubleBuffer();
  wxGLAttributes& Stereo();
  wxGLAttributes& AuxBuffers(int val);
  wxGLAttributes& MinRGBA(int mRed, int mGreen, int mBlue, int mAlpha);
  wxGLAttributes& Depth(int val);
  wxGLAttributes& Stencil(int val);
  wxGLAttributes& MinAcumRGBA(int mRed, int mGreen, int mBlue, int mAlpha);
  wxGLAttributes& PlatformDefaults();
  wxGLAttributes& Defaults();
  wxGLAttributes& SampleBuffers(int val);
  wxGLAttributes& Samplers(int val);
  wxGLAttributes& FrameBuffersRGB();
  void EndList();
    // This function is undocumented and can not be chained on purpose!
    // To keep backwards compatibility with versions before wx3.1 we add here
    // the default values used in those versions for the case of NULL list.
  void AddDefaultsForWXBefore31();
};
// ----------------------------------------------------------------------------
// wxGLContextBase: OpenGL rendering context
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLContextBase : public wxObject
{
public:
//  The derived class should provide a ctor with this signature:
//
//  wxGLContext(wxGLCanvas *win,
//              const wxGLContext *other = NULL,
//              const wxGLContextAttrs *ctxAttrs = NULL);

    // set this context as the current one
  virtual bool SetCurrent(const wxGLCanvas& win) const = 0;
  bool IsOK()
  {
 return m_isOk;
  }
protected:
  bool m_isOk;
};
// ----------------------------------------------------------------------------
// wxGLCanvasBase: window which can be used for OpenGL rendering
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLCanvasBase : public wxWindow
{
public:
    // default ctor doesn't initialize the window, use Create() later
  wxGLCanvasBase();
  virtual ~wxGLCanvasBase();
    /*
       The derived class should provide a ctor with this signature:

    wxGLCanvas(wxWindow *parent,
               const wxGLAttributes& dispAttrs,
               wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const wxPalette& palette = wxNullPalette);
     */

    // operations
    // ----------

    // set the given context associated with this window as the current one
  bool SetCurrent(const wxGLContext& context) const;
    // flush the back buffer (if we have it)
  virtual bool SwapBuffers() = 0;
    // accessors
    // ---------

    // check if the given attributes are supported without creating a canvas
  static bool IsDisplaySupported(const wxGLAttributes& dispAttrs);
  static bool IsDisplaySupported(const int* attribList);
#    if  wxUSE_PALETTE
  const wxPalette* GetPalette() const
  {
 return &m_palette;
  }
#    endif
    // miscellaneous helper functions
    // ------------------------------

    // call glcolor() for the colour with the given name, return false if
    // colour not found
  bool SetColour(const wxString& colour);
    // return true if the extension with given name is supported
    //
    // notice that while this function is implemented for all of GLX, WGL and
    // AGL the extensions names are usually not the same for different
    // platforms and so the code using it still usually uses conditional
    // compilation
  static bool IsExtensionSupported(const char* extension);
    // Get the wxGLContextAttrs object filled with the context-related values
    // of the list of attributes passed at ctor when no wxGLAttributes is used
    // as a parameter
  wxGLContextAttrs& GetGLCTXAttrs()
  {
 return m_GLCTXAttrs;
  }
    // deprecated methods using the implicit wxGLContext
#    if  WXWIN_COMPATIBILITY_2_8
#    endif
#    ifdef __WXUNIVERSAL__
    // resolve the conflict with wxWindowUniv::SetCurrent()
  virtual bool SetCurrent(bool doit)
  {
 return wxWindow::SetCurrent(doit);
  }
#    endif
protected:
    // override this to implement SetColour() in GL_INDEX_MODE
    // (currently only implemented in wxX11 and wxMotif ports)
  virtual int GetColourIndex(const wxColour&)
  {
 return -1;
  }
    // check if the given extension name is present in the space-separated list
    // of extensions supported by the current implementation such as returned
    // by glXQueryExtensionsString() or glGetString(GL_EXTENSIONS)
  static bool IsExtensionInList(const char* list, const char* extension);
    // For the case of "int* attribList" at ctor is != 0
  wxGLContextAttrs m_GLCTXAttrs;
    // Extract pixel format and context attributes.
    // Return false if an unknown attribute is found.
  static bool ParseAttribList(const int* attribList, wxGLAttributes& dispAttrs, wxGLContextAttrs* ctxAttrs = NULL);
#    if  wxUSE_PALETTE
    // create default palette if we're not using RGBA mode
    // (not supported in most ports)
  virtual wxPalette CreateDefaultPalette()
  {
 return wxNullPalette;
  }
  wxPalette m_palette;
#    endif
#    if  WXWIN_COMPATIBILITY_2_8
  wxGLContext* m_glContext;
#    endif
};
// ----------------------------------------------------------------------------
// wxGLApp: a special wxApp subclass for OpenGL applications which must be used
//          to select a visual compatible with the given attributes
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLAppBase : public wxApp
{
public:
  wxGLAppBase()
    :  wxApp()
  {

  }
    // use this in the constructor of the user-derived wxGLApp class to
    // determine if an OpenGL rendering context with these attributes
    // is available - returns true if so, false if not.
  virtual bool InitGLVisual(const int* attribList) = 0;
};
#    if  defined(__WXMSW__)
#      include "wx/msw/glcanvas.h"
#    elif  defined(__WXMOTIF__) || defined(__WXX11__)
#      include "wx/x11/glcanvas.h"
#    elif  defined(__WXGTK20__)
#      include "wx/gtk/glcanvas.h"
#    elif  defined(__WXGTK__)
#      include "wx/gtk1/glcanvas.h"
#    elif  defined(__WXMAC__)
#      include "wx/osx/glcanvas.h"
#    elif  defined(__WXQT__)
#      include "wx/qt/glcanvas.h"
#    else 
#    endif
// wxMac and wxMSW don't need anything extra in wxGLAppBase, so declare it here
#    ifndef wxGL_APP_DEFINED
class WXDLLIMPEXP_GL wxGLApp : public wxGLAppBase
{
public:
  wxGLApp()
    :  wxGLAppBase()
  {

  }
  bool InitGLVisual(const int* attribList) override;
private:
  wxDECLARE_DYNAMIC_CLASS(wxGLApp);
};
#    endif
// ----------------------------------------------------------------------------
// wxGLAPI: an API wrapper that allows the use of 'old' APIs even on OpenGL
// platforms that don't support it natively anymore, if the APIs are available
// it's a mere redirect
// ----------------------------------------------------------------------------
#    ifndef wxUSE_OPENGL_EMULATION
#      define wxUSE_OPENGL_EMULATION	0
#    endif
class WXDLLIMPEXP_GL wxGLAPI : public wxObject
{
public:
  wxGLAPI();
  ~wxGLAPI();
  static void glFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
  static void glBegin(GLenum mode);
  static void glTexCoord2f(GLfloat s, GLfloat t);
  static void glVertex3f(GLfloat x, GLfloat y, GLfloat z);
  static void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz);
  static void glColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
  static void glColor3f(GLfloat r, GLfloat g, GLfloat b);
  static void glEnd();
};
#  endif
#endif
