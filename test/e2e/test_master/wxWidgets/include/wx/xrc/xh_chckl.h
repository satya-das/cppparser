/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_chckl.h
// Purpose:     XML resource handler for wxCheckListBox
// Author:      Bob Mitchell
// Created:     2000/03/21
// Copyright:   (c) 2000 Bob Mitchell and Verant Interactive
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_CHCKL_H_
#  define _WX_XH_CHCKL_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_CHECKLISTBOX
class WXDLLIMPEXP_XRC wxCheckListBoxXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxCheckListBoxXmlHandler);
public:
  wxCheckListBoxXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  bool m_insideBox;
  wxArrayString strList;
};
#  endif
#endif
