/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/statbmp.h
// Purpose:     wxStaticBitmap class for wxMSW
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_STATBMP_H_
#  define _WX_STATBMP_H_
#  include "wx/control.h"
#  include "wx/icon.h"
#  include "wx/bitmap.h"
WXDLLIMPEXP_CORE extern const char wxStaticBitmapNameStr[];
// a control showing an icon or a bitmap
class WXDLLIMPEXP_CORE wxStaticBitmap : public wxStaticBitmapBase
{
public:
  wxStaticBitmap()
  {
    Init();
  }
  wxStaticBitmap(wxWindow* parent, wxWindowID id, const wxGDIImage& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr))
  {
    Init();
    Create(parent, id, label, pos, size, style, name);
  }
  bool Create(wxWindow* parent, wxWindowID id, const wxGDIImage& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr));
  virtual ~wxStaticBitmap()
  {
    Free();
  }
  void SetIcon(const wxIcon& icon) override
  {
    SetImage (&icon);
  }
  void SetBitmap(const wxBitmap& bitmap) override
  {
    SetImage (&bitmap);
  }
  wxBitmap GetBitmap() const override;
  wxIcon GetIcon() const override;
  WXDWORD MSWGetStyle(long style, WXDWORD* exstyle) const override;
    // returns true if the platform should explicitly apply a theme border
  bool CanApplyThemeBorder() const override
  {
    return false;
  }
protected:
  wxSize DoGetBestClientSize() const override;
    // ctor/dtor helpers
  void Init();
  void Free();
    // true if icon/bitmap is valid
  bool ImageIsOk() const;
  void SetImage(const wxGDIImage* image);
  void SetImageNoCopy(wxGDIImage* image);
    // draw the bitmap ourselves here if the OS can't do it correctly (if it
    // can we leave it to it)
  void DoPaintManually(wxPaintEvent& event);
  void WXHandleSize(wxSizeEvent& event);
    // we can have either an icon or a bitmap
  bool m_isIcon;
  wxGDIImage* m_image;
    // handle used in last call to STM_SETIMAGE
  WXHANDLE m_currentHandle;
private:
    // Flag indicating whether we own m_currentHandle, i.e. should delete it.
  bool m_ownsCurrentHandle;
    // Replace the image at the native control level with the given HBITMAP or
    // HICON (which can be 0) and destroy the previous image if necessary.
  void MSWReplaceImageHandle(WXLPARAM handle);
    // Delete the current handle only if we own it.
  void DeleteCurrentHandleIfNeeded();
  wxDECLARE_DYNAMIC_CLASS(wxStaticBitmap);
  wxDECLARE_EVENT_TABLE();
  wxDECLARE_NO_COPY_CLASS(wxStaticBitmap);
};
#endif
    // _WX_STATBMP_H_
