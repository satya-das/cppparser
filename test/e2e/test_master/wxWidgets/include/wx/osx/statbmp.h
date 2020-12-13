#ifndef _WX_STATBMP_H_
#  define _WX_STATBMP_H_
#  include "wx/statbmp.h"
class WXDLLIMPEXP_CORE wxStaticBitmap : public wxStaticBitmapBase
{
public:
  wxStaticBitmap()
  {
  }
  wxStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr))
  {
    Create(parent, id, bitmap, pos, size, style, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr));
  void SetBitmap(const wxBitmap& bitmap) override;
  wxBitmap GetBitmap() const override
  {
    return m_bitmap;
  }
  void SetIcon(const wxIcon& icon) override
  {
    wxBitmap bmp;
    bmp.CopyFromIcon(icon);
    SetBitmap(bmp);
  }
#  if  defined(__WXGTK20__) || defined(__WXMAC__)
    // icons and bitmaps are really the same thing in wxGTK and wxMac
  wxIcon GetIcon() const override
  {
    return (const wxIcon&) m_bitmap;
  }
#  endif
  void SetScaleMode(ScaleMode scaleMode) override;
  ScaleMode GetScaleMode() const override
  {
    return m_scaleMode;
  }
private:
  wxSize GetBitmapSize()
  {
    return m_bitmap.IsOk() ? m_bitmap.GetScaledSize() : wxSize(16, 16);
  }
  void OnPaint(wxPaintEvent& event);
  wxBitmap m_bitmap;
  ScaleMode m_scaleMode;
  wxDECLARE_DYNAMIC_CLASS(wxStaticBitmap);
};
#endif
