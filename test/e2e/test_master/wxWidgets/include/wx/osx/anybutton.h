/////////////////////////////////////////////////////////////////////////////
// Name:        anybutton.h
// Purpose:     wxAnyButton class
// Author:      Stefan Csomor
// Created:     1998-01-01 (extracted from button.h)
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_OSX_ANYBUTTON_H_
#  define _WX_OSX_ANYBUTTON_H_
// Any button
class WXDLLIMPEXP_CORE wxAnyButton : public wxAnyButtonBase
{
public:
  wxAnyButton()
  {
  }
  static wxSize GetDefaultSize();
  void SetLabel(const wxString& label) override;
protected:
  wxSize DoGetBestSize() const override;
  void OnEnterWindow(wxMouseEvent& event);
  void OnLeaveWindow(wxMouseEvent& event);
  wxBitmap DoGetBitmap(State which) const override;
  void DoSetBitmap(const wxBitmap& bitmap, State which) override;
  void DoSetBitmapPosition(wxDirection dir) override;
  void DoSetBitmapMargins(int x, int y) override
  {
        m_marginX = x;
        m_marginY = y;
        InvalidateBestSize();
  }
#  if  wxUSE_MARKUP && wxOSX_USE_COCOA
  bool DoSetLabelMarkup(const wxString& markup) override;
#  endif
    // the margins around the bitmap
  int m_marginX;
  int m_marginY;
    // the bitmaps for the different state of the buttons, all of them may be
    // invalid and the button only shows a bitmap at all if State_Normal bitmap
    // is valid
  wxBitmap m_bitmaps[State_Max];
  wxDECLARE_NO_COPY_CLASS(wxAnyButton);
  wxDECLARE_EVENT_TABLE();
};
#endif
