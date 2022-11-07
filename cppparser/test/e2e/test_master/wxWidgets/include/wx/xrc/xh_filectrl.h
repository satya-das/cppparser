/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_filectrl.h
// Purpose:     XML resource handler for wxFileCtrl
// Author:      Kinaou Hervé
// Created:     2009-05-11
// Copyright:   (c) 2009 wxWidgets development team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_FILECTRL_H_
#  define _WX_XH_FILECTRL_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_FILECTRL
class WXDLLIMPEXP_XRC wxFileCtrlXmlHandler : public wxXmlResourceHandler
{
public:
  wxFileCtrlXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  wxDECLARE_DYNAMIC_CLASS(wxFileCtrlXmlHandler);
};
#  endif
#endif
