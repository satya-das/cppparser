/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_listb.h
// Purpose:     XML resource handler for wxListbox
// Author:      Bob Mitchell & Vaclav Slavik
// Created:     2000/07/29
// Copyright:   (c) 2000 Bob Mitchell & Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_LISTB_H_
#  define _WX_XH_LISTB_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_LISTBOX
class WXDLLIMPEXP_XRC wxListBoxXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxListBoxXmlHandler);
public:
  wxListBoxXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  bool m_insideBox;
  wxArrayString strList;
};
#  endif
#endif
