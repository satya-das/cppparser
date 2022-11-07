/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/dcmemory.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_DCMEMORY_H_
#  define _WX_GTK_DCMEMORY_H_
#  include "wx/dcmemory.h"
#  include "wx/gtk/dcclient.h"
//-----------------------------------------------------------------------------
// wxMemoryDCImpl
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxMemoryDCImpl : public wxWindowDCImpl
{
public:
  wxMemoryDCImpl(wxMemoryDC* owner);
  wxMemoryDCImpl(wxMemoryDC* owner, wxBitmap& bitmap);
  wxMemoryDCImpl(wxMemoryDC* owner, wxDC* dc);
  virtual ~wxMemoryDCImpl();
    // these get reimplemented for mono-bitmaps to behave
    // more like their Win32 couterparts. They now interpret
    // wxWHITE, wxWHITE_BRUSH and wxWHITE_PEN as drawing 0
    // and everything else as drawing 1.
  void SetPen(const wxPen& pen) override;
  void SetBrush(const wxBrush& brush) override;
  void SetBackground(const wxBrush& brush) override;
  void SetTextForeground(const wxColour& col) override;
  void SetTextBackground(const wxColour& col) override;
    // overridden from wxDCImpl
  void DoGetSize(int* width, int* height) const override;
  wxBitmap DoGetAsBitmap(const wxRect* subrect) const override;
  void* GetHandle() const override;
    // overridden for wxMemoryDC Impl
  void DoSelect(const wxBitmap& bitmap) override;
  const wxBitmap& GetSelectedBitmap() const override;
  wxBitmap& GetSelectedBitmap() override;
private:
  wxBitmap m_selected;
  void Init();
  wxDECLARE_ABSTRACT_CLASS(wxMemoryDCImpl);
};
#endif
    // _WX_GTK_DCMEMORY_H_
