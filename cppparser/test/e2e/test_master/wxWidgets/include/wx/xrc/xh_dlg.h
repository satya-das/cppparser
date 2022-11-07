/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_dlg.h
// Purpose:     XML resource handler for dialogs
// Author:      Vaclav Slavik
// Created:     2000/03/05
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_DLG_H_
#  define _WX_XH_DLG_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC
class WXDLLIMPEXP_XRC wxDialogXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxDialogXmlHandler);
public:
  wxDialogXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
};
#  endif
#endif
