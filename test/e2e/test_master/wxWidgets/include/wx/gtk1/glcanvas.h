/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk1/glcanvas.h
// Purpose:     wxGLCanvas, for using OpenGL/Mesa with wxWidgets and GTK
// Author:      Robert Roebling
// Modified by:
// Created:     17/8/98
// Copyright:   (c) Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GLCANVAS_H_
#  define _WX_GLCANVAS_H_
#  include "wx/unix/glx11.h"
//---------------------------------------------------------------------------
// wxGLCanvas
//---------------------------------------------------------------------------
class WXDLLIMPEXP_GL wxGLCanvas : public wxGLCanvasX11
{
public:
  wxGLCanvas(wxWindow* parent, const wxGLAttributes& dispAttrs, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const wxPalette& palette = wxNullPalette);
  explicit wxGLCanvas(wxWindow* parent, wxWindowID id = wxID_ANY, const int* attribList = NULL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const wxPalette& palette = wxNullPalette);
  bool Create(wxWindow* parent, const wxGLAttributes& dispAttrs, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const wxPalette& palette = wxNullPalette);
  bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxGLCanvasName, const int* attribList = NULL, const wxPalette& palette = wxNullPalette);
    // implement wxGLCanvasX11 methods
    // -------------------------------
  virtual unsigned long GetXWindow() const;
    // deprecated methods
    // ------------------
#  if  WXWIN_COMPATIBILITY_2_8
    // called from "realized" callback to create the implicit context if needed
  void GTKInitImplicitContext();
#  endif
    // implementation from now on
  virtual void OnInternalIdle();
  GtkWidget* m_glWidget;
#  if  WXWIN_COMPATIBILITY_2_8
  wxGLContext* m_sharedContext;
  wxGLCanvas* m_sharedContextOf;
  const bool m_createImplicitContext;
#  endif
  wxDECLARE_CLASS(wxGLCanvas);
};
#endif
