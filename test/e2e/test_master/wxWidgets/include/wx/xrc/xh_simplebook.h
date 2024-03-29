/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_simplebook.h
// Purpose:     XML resource handler for wxSimplebook
// Author:      Vadim Zeitlin
// Created:     2014-08-05
// Copyright:   (c) 2014 Vadim Zeitlin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_SIMPLEBOOK_H_
#  define _WX_XH_SIMPLEBOOK_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_BOOKCTRL
class wxSimplebook;
class WXDLLIMPEXP_XRC wxSimplebookXmlHandler : public wxXmlResourceHandler
{
public:
  wxSimplebookXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  bool m_isInside;
  wxSimplebook* m_simplebook;
  wxDECLARE_DYNAMIC_CLASS(wxSimplebookXmlHandler);
};
#  endif
#endif
