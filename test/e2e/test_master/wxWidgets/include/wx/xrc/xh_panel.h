/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_panel.h
// Purpose:     XML resource handler for wxPanel
// Author:      Vaclav Slavik
// Created:     2000/03/05
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_PANEL_H_
#  define _WX_XH_PANEL_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC
class WXDLLIMPEXP_XRC wxPanelXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxPanelXmlHandler);
public:
  wxPanelXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
};
#  endif
#endif
