/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_aui.h
// Purpose:     XRC resource handler for wxAUI
// Author:      Andrea Zanellato, Steve Lamerton (wxAuiNotebook)
// Created:     2011-09-18
// Copyright:   (c) 2011 wxWidgets Team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_AUI_H_
#  define _WX_XH_AUI_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_AUI
#    include "wx/vector.h"
class WXDLLIMPEXP_FWD_AUI wxAuiManager;
class WXDLLIMPEXP_FWD_AUI wxAuiNotebook;
class WXDLLIMPEXP_AUI wxAuiXmlHandler : public wxXmlResourceHandler
{
public:
  wxAuiXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
    // Returns the wxAuiManager for the specified window
  wxAuiManager* GetAuiManager(wxWindow* managed) const;
private:
    // Used to UnInit() the wxAuiManager before destroying its managed window
  void OnManagedWindowClose(wxWindowDestroyEvent& event);
  typedef wxVector<wxAuiManager*> Managers;
  Managers m_managers;
  wxAuiManager* m_manager;
  wxWindow* m_window;
  wxAuiNotebook* m_notebook;
  bool m_mgrInside;
  bool m_anbInside;
  wxDECLARE_DYNAMIC_CLASS(wxAuiXmlHandler);
};
#  endif
#endif
