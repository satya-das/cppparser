/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/dcmemory.h
// Purpose:     wxMemoryDC class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_DCMEMORY_H_
#  define _WX_DCMEMORY_H_
#  include "wx/osx/dcclient.h"
class WXDLLIMPEXP_CORE wxMemoryDCImpl : public wxPaintDCImpl
{
public:
  wxMemoryDCImpl(wxMemoryDC* owner);
  wxMemoryDCImpl(wxMemoryDC* owner, wxBitmap& bitmap);
  wxMemoryDCImpl(wxMemoryDC* owner, wxDC* dc);
  virtual ~wxMemoryDCImpl();
  void DoGetSize(int* width, int* height) const override;
  wxBitmap DoGetAsBitmap(const wxRect* subrect) const override
  {
    return subrect == NULL ? GetSelectedBitmap() : GetSelectedBitmap().GetSubBitmap(*subrect);
  }
  void DoSelect(const wxBitmap& bitmap) override;
  const wxBitmap& GetSelectedBitmap() const override
  {
    return m_selected;
  }
  wxBitmap& GetSelectedBitmap() override
  {
    return m_selected;
  }
private:
  void Init();
  wxBitmap m_selected;
  wxDECLARE_CLASS(wxMemoryDCImpl);
  wxDECLARE_NO_COPY_CLASS(wxMemoryDCImpl);
};
#endif
    // _WX_DCMEMORY_H_
