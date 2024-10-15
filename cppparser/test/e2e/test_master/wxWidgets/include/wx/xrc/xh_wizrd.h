/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_wizrd.h
// Purpose:     XML resource handler for wxWizard
// Author:      Vaclav Slavik
// Created:     2003/03/02
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_WIZRD_H_
#  define _WX_XH_WIZRD_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_WIZARDDLG
class WXDLLIMPEXP_FWD_CORE wxWizard;
class WXDLLIMPEXP_FWD_CORE wxWizardPageSimple;
class WXDLLIMPEXP_XRC wxWizardXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxWizardXmlHandler);
public:
  wxWizardXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  wxWizard* m_wizard;
  wxWizardPageSimple* m_lastSimplePage;
};
#  endif
#endif
