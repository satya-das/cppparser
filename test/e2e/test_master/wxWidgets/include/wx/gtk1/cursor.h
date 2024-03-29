/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk1/cursor.h
// Purpose:
// Author:      Robert Roebling
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef __GTKCURSORH__
#  define __GTKCURSORH__
#  include "wx/gdicmn.h"
#  if  wxUSE_IMAGE
#    include "wx/image.h"
#  endif
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
#  endif
  wxCursor(const char bits[], int width, int height, int hotSpotX = -1, int hotSpotY = -1, const char maskBits[] = NULL, const wxColour* fg = NULL, const wxColour* bg = NULL);
    /* WARNING: the following ctor is missing:

        wxCursor(const wxString& name,
                wxBitmapType type = wxCURSOR_DEFAULT_TYPE,
                int hotSpotX = 0, int hotSpotY = 0);
    */
  virtual ~wxCursor();
    // implementation
  GdkCursor* GetCursor() const;
protected:
  void InitFromStock(wxStockCursor);
  virtual wxGDIRefData* CreateGDIRefData() const;
  virtual wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const;
private:
  wxDECLARE_DYNAMIC_CLASS(wxCursor);
};
#endif
