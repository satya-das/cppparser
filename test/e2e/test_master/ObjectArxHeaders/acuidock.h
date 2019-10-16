//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _acuiDock_h
#  define _acuiDock_h
#  pragma  pack (push, 8)
#  if  _MSC_VER >= 1000
#    pragma  once
#  endif
/////////////////////////////////////////////////////////////////////////////
class ACUI_PORT CAcUiDockFrame : public CAdUiDockFrame
{
  DECLARE_DYNCREATE(CAcUiDockFrame);
public:
  CAcUiDockFrame();
  virtual ~CAcUiDockFrame();
	//{{AFX_VIRTUAL(CAcUiDockFrame)
	//}}AFX_VIRTUAL
protected:
    //{{AFX_MSG(CAcUiDockFrame)
  afx_msg LRESULT OnACADKeepFocus(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
class ACUI_PORT CAcUiDockControlBar : public CAdUiDockControlBar
{
  DECLARE_DYNCREATE(CAcUiDockControlBar);
public:
  CAcUiDockControlBar()
  {
  }
protected:
  virtual bool CanFrameworkTakeFocus();
};
#  ifndef NEW_PALETTE
/////////////////////////////////////////////////////////////////////////////
class ACUI_PORT CAcUiPaletteSetDockFrame : public CAdUiPaletteSetDockFrame
{
  DECLARE_DYNCREATE(CAcUiPaletteSetDockFrame);
public:
  CAcUiPaletteSetDockFrame();
  virtual ~CAcUiPaletteSetDockFrame();
	//{{AFX_VIRTUAL(CAcUiPaletteSetDockFrame)
	//}}AFX_VIRTUAL
protected:
    //{{AFX_MSG(CAcUiPaletteSetDockFrame)
  afx_msg LRESULT OnACADKeepFocus(WPARAM wParam, LPARAM lParam);
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
    //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
#  endif
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#  pragma  pack (pop)
#endif
//////////////////////////////////////////////////////////////////////////////
