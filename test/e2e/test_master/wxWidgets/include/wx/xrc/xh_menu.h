/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_menu.h
// Purpose:     XML resource handler for menus/menubars
// Author:      Vaclav Slavik
// Created:     2000/03/05
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_MENU_H_
#  define _WX_XH_MENU_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_MENUS
class WXDLLIMPEXP_XRC wxMenuXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxMenuXmlHandler);
public:
  wxMenuXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  bool m_insideMenu;
};
class WXDLLIMPEXP_XRC wxMenuBarXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxMenuBarXmlHandler);
public:
  wxMenuBarXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
};
#  endif
#endif
