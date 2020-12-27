///////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/statbmpg.h
// Purpose:     wxGenericStaticBitmap header
// Author:      Marcin Wojdyr, Stefan Csomor
// Created:     2008-06-16
// Copyright:   wxWidgets developers
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GENERIC_STATBMP_H_
#  define _WX_GENERIC_STATBMP_H_
#  include "wx/statbmp.h"
class WXDLLIMPEXP_CORE wxGenericStaticBitmap : public wxStaticBitmapBase
{
public:
  wxGenericStaticBitmap()
  {
  }
  wxGenericStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr))
  {

            Create(parent, id, bitmap, pos, size, style, name);
      }
  bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr));
  void SetBitmap(const wxBitmap& bitmap) override
  {
        m_bitmap = bitmap;
        SetInitialSize(GetBitmapSize());
        Refresh();
    }
  wxBitmap GetBitmap() const override
  { return m_bitmap; }
  void SetIcon(const wxIcon& icon) override
  {
        m_bitmap.CopyFromIcon(icon);
        SetInitialSize(GetBitmapSize());
        Refresh();
    }
#  if  defined(__WXGTK20__) || defined(__WXMAC__)
    // icons and bitmaps are really the same thing in wxGTK and wxMac
  wxIcon GetIcon() const override
  { return (const wxIcon &)m_bitmap; }
#  endif
  void SetScaleMode(ScaleMode scaleMode) override
  {
        m_scaleMode = scaleMode;
        Refresh();
    }
  ScaleMode GetScaleMode() const override
  { return m_scaleMode; }
private:
  wxSize GetBitmapSize()
  {
        return m_bitmap.IsOk() ? m_bitmap.GetScaledSize()
                               : wxSize(16, 16); // this is completely arbitrary
    }
  void OnPaint(wxPaintEvent& event);
  wxBitmap m_bitmap;
  ScaleMode m_scaleMode;
  wxDECLARE_DYNAMIC_CLASS(wxGenericStaticBitmap);
};
#endif
