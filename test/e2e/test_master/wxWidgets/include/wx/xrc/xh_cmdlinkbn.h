/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_cmdlinkbn.h
// Purpose:     XML resource handler for command link buttons
// Author:      Kinaou Herve
// Created:     2010-10-20
// Copyright:   (c) 2010 wxWidgets development team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_CMDLINKBN_H_
#  define _WX_XH_CMDLINKBN_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_COMMANDLINKBUTTON
class WXDLLIMPEXP_XRC wxCommandLinkButtonXmlHandler : public wxXmlResourceHandler
{
public:
  wxCommandLinkButtonXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  wxDECLARE_DYNAMIC_CLASS(wxCommandLinkButtonXmlHandler);
};
#  endif
#endif
