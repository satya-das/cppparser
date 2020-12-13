/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_animatctrl.h
// Purpose:     XML resource handler for wxAnimationCtrl
// Author:      Francesco Montorsi
// Created:     2006-10-15
// Copyright:   (c) 2006 Francesco Montorsi
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_ANIMATIONCTRL_H_
#  define _WX_XH_ANIMATIONCTRL_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_ANIMATIONCTRL
class WXDLLIMPEXP_XRC wxAnimationCtrlXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxAnimationCtrlXmlHandler);
public:
  wxAnimationCtrlXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
};
#  endif
#endif
