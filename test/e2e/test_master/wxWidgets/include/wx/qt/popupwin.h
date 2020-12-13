/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/popupwin.h
// Author:      Peter Most
// Copyright:   (c) Peter Most
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_POPUPWIN_H_
#  define _WX_QT_POPUPWIN_H_
class WXDLLIMPEXP_CORE wxPopupWindow : public wxPopupWindowBase
{
public:
  wxPopupWindow();
  wxPopupWindow(wxWindow* parent, int flags = wxBORDER_NONE);
  wxDECLARE_DYNAMIC_CLASS(wxPopupWindow);
};
#endif
