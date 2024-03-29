/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_infobar.h
// Purpose:     XML resource handler for wxInfoBar
// Author:      Ilya Sinitsyn
// Created:     2019-09-25
// Copyright:   (c) 2019 TT-Solutions SARL
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_INFOBAR_H_
#  define _WX_XH_INFOBAR_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_INFOBAR
class WXDLLIMPEXP_XRC wxInfoBarXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxInfoBarXmlHandler);
public:
  wxInfoBarXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  wxShowEffect GetShowEffect(const wxString& param);
  bool m_insideBar;
  wxString m_effectNames[wxSHOW_EFFECT_MAX];
};
#  endif
#endif
