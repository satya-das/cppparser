/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/frame.h
// Purpose:     wxFrame class interface
// Author:      Peter Most
// Modified by:
// Created:     09.08.09
// Copyright:   (c) Peter Most
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_FRAME_H_
#  define _WX_QT_FRAME_H_
#  include "wx/frame.h"
class QMainWindow;
class QScrollArea;
class WXDLLIMPEXP_CORE wxFrame : public wxFrameBase
{
public:
  wxFrame()
  {
 Init();   }
  wxFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr))
  {

        Init();

        Create( parent, id, title, pos, size, style, name );
      }
  virtual ~wxFrame();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_FRAME_STYLE, const wxString& name = wxASCII_STR(wxFrameNameStr));
  void SetMenuBar(wxMenuBar* menubar) override;
  void SetStatusBar(wxStatusBar* statusBar) override;
  void SetToolBar(wxToolBar* toolbar) override;
  void SetWindowStyleFlag(long style) override;
  void AddChild(wxWindowBase* child) override;
  void RemoveChild(wxWindowBase* child) override;
  QMainWindow* GetQMainWindow() const;
  QScrollArea* QtGetScrollBarsContainer() const override;
protected:
  void DoGetClientSize(int* width, int* height) const override;
  void DoSetClientSize(int width, int height) override;
  QWidget* QtGetParentWidget() const override;
private:
    // Common part of all ctors.
  void Init()
  {
        m_qtToolBar = NULL;
    }
    // Currently active native toolbar.
  class QToolBar* m_qtToolBar;
  wxDECLARE_DYNAMIC_CLASS(wxFrame);
};
#endif
