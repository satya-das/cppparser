/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_listbk.h
// Purpose:     XML resource handler for wxListbook
// Author:      Vaclav Slavik
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_LISTBK_H_
#  define _WX_XH_LISTBK_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_LISTBOOK
class WXDLLIMPEXP_FWD_CORE wxListbook;
class WXDLLIMPEXP_XRC wxListbookXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxListbookXmlHandler);
public:
  wxListbookXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  bool m_isInside;
  wxListbook* m_listbook;
};
#  endif
#endif
