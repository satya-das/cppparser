/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/cursor.h
// Purpose:     wxCursor class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_CURSOR_H_
#  define _WX_CURSOR_H_
#  include "wx/bitmap.h"
// Cursor
class WXDLLIMPEXP_CORE wxCursor : public wxCursorBase
{
public:
  wxCursor();
  wxCursor(const wxImage& image);
  wxCursor(const wxString& name, wxBitmapType type = wxCURSOR_DEFAULT_TYPE, int hotSpotX = 0, int hotSpotY = 0);
  wxCursor(wxStockCursor id)
  {
    InitFromStock(id);
  }
  virtual ~wxCursor();
  void MacInstall() const;
  void SetHCURSOR(WXHCURSOR cursor);
  WXHCURSOR GetHCURSOR() const;
protected:
  wxGDIRefData* CreateGDIRefData() const override;
  wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const override;
private:
  void InitFromStock(wxStockCursor);
  void CreateFromImage(const wxImage& image);
  wxDECLARE_DYNAMIC_CLASS(wxCursor);
};
#endif
