/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_toolbk.h
// Purpose:     XML resource handler for wxToolbook
// Author:      Andrea Zanellato
// Created:     2009/12/12
// Copyright:   (c) 2010 wxWidgets development team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_TOOLBK_H_
#  define _WX_XH_TOOLBK_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_TOOLBOOK
class WXDLLIMPEXP_FWD_CORE wxToolbook;
class WXDLLIMPEXP_XRC wxToolbookXmlHandler : public wxXmlResourceHandler
{
public:
  wxToolbookXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  bool m_isInside;
  wxToolbook* m_toolbook;
  wxDECLARE_DYNAMIC_CLASS(wxToolbookXmlHandler);
};
#  endif
#endif
