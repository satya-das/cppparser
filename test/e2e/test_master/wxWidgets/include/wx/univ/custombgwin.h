///////////////////////////////////////////////////////////////////////////////
// Name:        wx/univ/custombgwin.h
// Purpose:     wxUniv implementation of wxCustomBackgroundWindow.
// Author:      Vadim Zeitlin
// Created:     2011-10-10
// Copyright:   (c) 2011 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_UNIV_CUSTOMBGWIN_H_
#  define _WX_UNIV_CUSTOMBGWIN_H_
// ----------------------------------------------------------------------------
// wxCustomBackgroundWindow
// ----------------------------------------------------------------------------
template <typename W>
class wxCustomBackgroundWindow : public W, public wxCustomBackgroundWindowBase
{
public:
  typedef W BaseWindowClass;
  wxCustomBackgroundWindow()
  {
  }
protected:
  void DoSetBackgroundBitmap(const wxBitmap& bmp) override
  {
        // We have support for background bitmap even at the base class level.
    BaseWindowClass::SetBackground(bmp, wxALIGN_NOT, wxTILE);
  }
  wxDECLARE_NO_COPY_TEMPLATE_CLASS(wxCustomBackgroundWindow, W);
};
#endif
