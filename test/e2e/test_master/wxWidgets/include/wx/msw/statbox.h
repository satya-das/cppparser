/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/statbox.h
// Purpose:     wxStaticBox class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_STATBOX_H_
#  define _WX_MSW_STATBOX_H_
#  include "wx/compositewin.h"
// Group box
class WXDLLIMPEXP_CORE wxStaticBox : public wxCompositeWindowSettersOnly<wxStaticBoxBase>
{
public:
  wxStaticBox()
    :  wxCompositeWindowSettersOnly<wxStaticBoxBase>()
    
    {

        }
  wxStaticBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBoxNameStr))
    :  wxCompositeWindowSettersOnly<wxStaticBoxBase>()
    
    {

        Create(parent, id, label, pos, size, style, name);
        }
  wxStaticBox(wxWindow* parent, wxWindowID id, wxWindow* label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBoxNameStr))
    :  wxCompositeWindowSettersOnly<wxStaticBoxBase>()
    
    {

        Create(parent, id, label, pos, size, style, name);
        }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, wxWindow* label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBoxNameStr));
    /// Implementation only
  void GetBordersForSizer(int* borderTop, int* borderOther) const override;
  bool SetBackgroundColour(const wxColour& colour) override;
  bool SetFont(const wxFont& font) override;
  WXDWORD MSWGetStyle(long style, WXDWORD* exstyle) const override;
    // returns true if the platform should explicitly apply a theme border
  bool CanApplyThemeBorder() const override
  { return false; }
protected:
  wxSize DoGetBestSize() const override;
public:
  WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override;
protected:
  wxWindowList GetCompositeWindowParts() const override;
    // return the region with all the windows inside this static box excluded
  virtual WXHRGN MSWGetRegionWithoutChildren();
    // remove the parts which are painted by static box itself from the given
    // region which is embedded in a rectangle (0, 0)-(w, h)
  virtual void MSWGetRegionWithoutSelf(WXHRGN hrgn, int w, int h);
    // paint the given rectangle with our background brush/colour
  virtual void PaintBackground(wxDC& dc, const struct tagRECT& rc);
    // paint the foreground of the static box
  virtual void PaintForeground(wxDC& dc, const struct tagRECT& rc);
  void OnPaint(wxPaintEvent& event);
private:
  void PositionLabelWindow();
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxStaticBox);
};
// Indicate that we have the ctor overload taking wxWindow as label.
#  define wxHAS_WINDOW_LABEL_IN_STATIC_BOX
#endif
