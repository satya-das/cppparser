/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_spin.h
// Purpose:     XML resource handler for wxSpinButton, wxSpinCtrl, wxSpinCtrlDouble
// Author:      Bob Mitchell
// Created:     2000/03/21
// Copyright:   (c) 2000 Bob Mitchell and Verant Interactive
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_SPIN_H_
#  define _WX_XH_SPIN_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC
#    if  wxUSE_SPINBTN
class WXDLLIMPEXP_XRC wxSpinButtonXmlHandler : public wxXmlResourceHandler
{
public:
  wxSpinButtonXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
  wxDECLARE_DYNAMIC_CLASS(wxSpinButtonXmlHandler);
};
#    endif
#    if  wxUSE_SPINCTRL
class WXDLLIMPEXP_XRC wxSpinCtrlXmlHandler : public wxXmlResourceHandler
{
public:
  wxSpinCtrlXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
  wxDECLARE_DYNAMIC_CLASS(wxSpinCtrlXmlHandler);
};
class WXDLLIMPEXP_XRC wxSpinCtrlDoubleXmlHandler : public wxXmlResourceHandler
{
public:
  wxSpinCtrlDoubleXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
  wxDECLARE_DYNAMIC_CLASS(wxSpinCtrlDoubleXmlHandler);
};
#    endif
#  endif
#endif
