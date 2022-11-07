/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/cursor.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_CURSOR_H_
#  define _WX_GTK_CURSOR_H_
class WXDLLIMPEXP_FWD_CORE wxImage;
//-----------------------------------------------------------------------------
// wxCursor
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxCursor : public wxCursorBase
{
public:
  wxCursor();
  wxCursor(wxStockCursor id)
  {
    InitFromStock(id);
  }
#  if  wxUSE_IMAGE
  wxCursor(const wxImage& image);
  wxCursor(const wxString& name, wxBitmapType type = wxCURSOR_DEFAULT_TYPE, int hotSpotX = 0, int hotSpotY = 0);
#  endif
  wxCursor(const char bits[], int width, int height, int hotSpotX = -1, int hotSpotY = -1, const char maskBits[] = NULL, const wxColour* fg = NULL, const wxColour* bg = NULL);
  wxPoint GetHotSpot() const override;
  virtual ~wxCursor();
    // implementation
  GdkCursor* GetCursor() const;
protected:
  void InitFromStock(wxStockCursor);
#  if  wxUSE_IMAGE
  void InitFromImage(const wxImage& image);
#  endif
  wxGDIRefData* CreateGDIRefData() const override;
  wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const override;
private:
  wxDECLARE_DYNAMIC_CLASS(wxCursor);
};
#endif
