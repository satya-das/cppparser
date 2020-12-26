///////////////////////////////////////////////////////////////////////////////
// Name:        wx/univ/button.h
// Purpose:     wxButton for wxUniversal
// Author:      Vadim Zeitlin
// Modified by:
// Created:     15.08.00
// Copyright:   (c) 2000 SciTech Software, Inc. (www.scitechsoft.com)
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_UNIV_BUTTON_H_
#  define _WX_UNIV_BUTTON_H_
#  include "wx/bitmap.h"
// ----------------------------------------------------------------------------
// the actions supported by this control
// ----------------------------------------------------------------------------
//checkbox.cpp needed it, so not move it to anybutton.h
#  define wxACTION_BUTTON_TOGGLE	wxT("toggle")    // press/release the button
#  define wxACTION_BUTTON_PRESS	wxT("press")     // press the button
#  define wxACTION_BUTTON_RELEASE	wxT("release")   // release the button
#  define wxACTION_BUTTON_CLICK	wxT("click")     // generate button click event
// ----------------------------------------------------------------------------
// wxButton: a push button
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxButton : public wxButtonBase
{
public:
  wxButton()
  {
 Init();   }
  wxButton(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxString& label = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxButtonNameStr))
  {

        Init();

        Create(parent, id, bitmap, label, pos, size, style, validator, name);
      }
  wxButton(wxWindow* parent, wxWindowID id, const wxString& label = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxButtonNameStr))
  {

        Init();

        Create(parent, id, label, pos, size, style, validator, name);
      }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxButtonNameStr))
  {
        return Create(parent, id, wxNullBitmap, label,
                      pos, size, style, validator, name);
    }
  bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxString& label = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxButtonNameStr));
  virtual ~wxButton();
  wxWindow* SetDefault() override;
  bool IsPressed() const override
  {
    return m_isPressed;
  }
  bool IsDefault() const override
  {
    return m_isDefault;
  }
    // wxButton actions
  void Click() override;
  bool CanBeHighlighted() const override
  {
    return true;
  }
protected:
  void DoSetBitmap(const wxBitmap& bitmap, State which) override;
  wxBitmap DoGetBitmap(State which) const override;
  void DoSetBitmapMargins(wxCoord x, wxCoord y) override;
    // common part of all ctors
  void Init();
  wxDECLARE_DYNAMIC_CLASS(wxButton);
};
#endif
