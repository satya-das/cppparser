/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/toolbar.h
// Purpose:     wxToolBar class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_TOOLBAR_H_
#  define _WX_TOOLBAR_H_
#  if  wxUSE_TOOLBAR
#    include "wx/tbarbase.h"
#    include "wx/dynarray.h"
class WXDLLIMPEXP_CORE wxToolBar : public wxToolBarBase
{
  wxDECLARE_DYNAMIC_CLASS(wxToolBar);
public:
  /*
   * Public interface
   */
  wxToolBar()
  {
 Init();   }
  wxToolBar(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTB_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxToolBarNameStr))
  {

    Init();
    Create(parent, id, pos, size, style, name);
    }
  virtual ~wxToolBar();
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTB_DEFAULT_STYLE, const wxString& name = wxASCII_STR(wxToolBarNameStr));
  void SetWindowStyleFlag(long style) override;
  bool Destroy() override;
    // override/implement base class virtuals
  wxToolBarToolBase* FindToolForPosition(wxCoord x, wxCoord y) const override;
#    ifndef __WXOSX_IPHONE__
  bool Show(bool show = true) override;
  bool IsShown() const override;
#    endif
  bool Realize() override;
  void SetToolBitmapSize(const wxSize& size) override;
  wxSize GetToolSize() const override;
  void SetRows(int nRows) override;
  void SetToolNormalBitmap(int id, const wxBitmap& bitmap) override;
  void SetToolDisabledBitmap(int id, const wxBitmap& bitmap) override;
#    ifndef __WXOSX_IPHONE__
    // Add all the buttons
  wxString MacGetToolTipString(wxPoint& where) override;
  void OnPaint(wxPaintEvent& event);
  void OnMouse(wxMouseEvent& event);
  void MacSuperChangedPosition() override;
#    endif
#    if  wxOSX_USE_NATIVE_TOOLBAR
    // make all tools selectable
  void OSXSetSelectableTools(bool set);
  void OSXSelectTool(int toolId);
  bool MacInstallNativeToolbar(bool usesNative);
  void MacUninstallNativeToolbar();
  bool MacWantsNativeToolbar();
  bool MacTopLevelHasNativeToolbar(bool* ownToolbarInstalled) const;
#    endif
  wxToolBarToolBase* CreateTool(int id, const wxString& label, const wxBitmap& bmpNormal, const wxBitmap& bmpDisabled = wxNullBitmap, wxItemKind kind = wxITEM_NORMAL, wxObject* clientData = NULL, const wxString& shortHelp = wxEmptyString, const wxString& longHelp = wxEmptyString) override;
  wxToolBarToolBase* CreateTool(wxControl* control, const wxString& label) override;
protected:
    // common part of all ctors
  void Init();
  void DoLayout();
  void DoSetSize(int x, int y, int width, int height, int sizeFlags) override;
#    ifndef __WXOSX_IPHONE__
  void DoGetSize(int* width, int* height) const override;
  wxSize DoGetBestSize() const override;
#    endif
#    ifdef __WXOSX_COCOA__
  void DoGetPosition(int* x, int* y) const override;
#    endif
  bool DoInsertTool(size_t pos, wxToolBarToolBase* tool) override;
  bool DoDeleteTool(size_t pos, wxToolBarToolBase* tool) override;
  void DoEnableTool(wxToolBarToolBase* tool, bool enable) override;
  void DoToggleTool(wxToolBarToolBase* tool, bool toggle) override;
  void DoSetToggle(wxToolBarToolBase* tool, bool toggle) override;
  wxDECLARE_EVENT_TABLE();
#    if  wxOSX_USE_NATIVE_TOOLBAR
  bool m_macUsesNativeToolbar;
  void* m_macToolbar;
#    endif
#    ifdef __WXOSX_IPHONE__
  WX_UIView m_macToolbar;
#    endif
};
#  endif
#endif
    // _WX_TOOLBAR_H_
