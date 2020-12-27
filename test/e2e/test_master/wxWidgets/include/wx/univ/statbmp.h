/////////////////////////////////////////////////////////////////////////////
// Name:        wx/univ/statbmp.h
// Purpose:     wxStaticBitmap class for wxUniversal
// Author:      Vadim Zeitlin
// Modified by:
// Created:     25.08.00
// Copyright:   (c) 2000 SciTech Software, Inc. (www.scitechsoft.com)
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_UNIV_STATBMP_H_
#  define _WX_UNIV_STATBMP_H_
#  include "wx/bitmap.h"
// ----------------------------------------------------------------------------
// wxStaticBitmap
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxStaticBitmap : public wxStaticBitmapBase
{
public:
  wxStaticBitmap()
  {

      }
  wxStaticBitmap(wxWindow* parent, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0)
  {

        Create(parent, wxID_ANY, label, pos, size, style);
      }
  wxStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr))
  {

        Create(parent, id, label, pos, size, style, name);
      }
  bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr));
  void SetBitmap(const wxBitmap& bitmap) override;
  void SetIcon(const wxIcon& icon) override;
  wxBitmap GetBitmap() const override
  { return m_bitmap; }
  wxIcon GetIcon() const override;
  bool HasTransparentBackground() override
  { return true; }
protected:
  void DoDraw(wxControlRenderer* renderer) override;
private:
    // the bitmap which we show
  wxBitmap m_bitmap;
  wxDECLARE_DYNAMIC_CLASS(wxStaticBitmap);
};
#endif
