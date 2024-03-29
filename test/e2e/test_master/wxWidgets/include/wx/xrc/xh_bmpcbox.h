/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_bmpcbox.h
// Purpose:     XML resource handler for wxBitmapComboBox
// Author:      Jaakko Salli
// Created:     Sep-10-2006
// Copyright:   (c) 2006 Jaakko Salli
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_XH_BMPCBOX_H_
#  define _WX_XH_BMPCBOX_H_
#  include "wx/xrc/xmlres.h"
#  if  wxUSE_XRC && wxUSE_BITMAPCOMBOBOX
class WXDLLIMPEXP_FWD_CORE wxBitmapComboBox;
class WXDLLIMPEXP_XRC wxBitmapComboBoxXmlHandler : public wxXmlResourceHandler
{
  wxDECLARE_DYNAMIC_CLASS(wxBitmapComboBoxXmlHandler);
public:
  wxBitmapComboBoxXmlHandler();
  wxObject* DoCreateResource() override;
  bool CanHandle(wxXmlNode* node) override;
private:
  wxBitmapComboBox* m_combobox;
  bool m_isInside;
};
#  endif
#endif
