/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_radbt.h
// Purpose:     XML resource handler for wxRadioButton
// Author:      Bob Mitchell
// Created:     2000/03/21
// Copyright:   (c) 2000 Bob Mitchell and Verant Interactive
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_RADBT_H_
#  define _WX_XH_RADBT_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_RADIOBTN
class WXDLLIMPEXP_XRC wxRadioButtonXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxRadioButtonXmlHandler);
public:
  wxRadioButtonXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
};
#  endif
#endif
