/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/fontdlg.h
// Purpose:     wxFontDialog class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_FONTDLG_H_
#  define _WX_MSW_FONTDLG_H_
// ----------------------------------------------------------------------------
// wxFontDialog
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxFontDialog : public wxFontDialogBase
{
public:
  wxFontDialog()
    : wxFontDialogBase()
  {
  }
  wxFontDialog(wxWindow* parent)
    : wxFontDialogBase(parent)
  {
    Create(parent);
  }
  wxFontDialog(wxWindow* parent, const wxFontData& data)
    : wxFontDialogBase(parent, data)
  {
    Create(parent, data);
  }
  int ShowModal() override;
  void SetTitle(const wxString& title) override;
  wxString GetTitle() const override;
protected:
  wxString m_title;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxFontDialog);
};
#endif
    // _WX_MSW_FONTDLG_H_
