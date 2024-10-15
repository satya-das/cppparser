/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_comboctrl.h
// Purpose:     XML resource handler for wxComboBox
// Author:      Jaakko Salli
// Created:     2009/01/25
// Copyright:   (c) 2009 Jaakko Salli
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_COMBOCTRL_H_
#  define _WX_XH_COMBOCTRL_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_COMBOCTRL
class WXDLLIMPEXP_XRC wxComboCtrlXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxComboCtrlXmlHandler);
public:
  wxComboCtrlXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
};
#  endif
#endif
