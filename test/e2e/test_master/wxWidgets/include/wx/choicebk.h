///////////////////////////////////////////////////////////////////////////////
// Name:        wx/choicebk.h
// Purpose:     wxChoicebook: wxChoice and wxNotebook combination
// Author:      Vadim Zeitlin
// Modified by: Wlodzimierz ABX Skiba from wx/listbook.h
// Created:     15.09.04
// Copyright:   (c) Vadim Zeitlin, Wlodzimierz Skiba
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_CHOICEBOOK_H_
#  define _WX_CHOICEBOOK_H_
#  include "wx/defs.h"
#  if  wxUSE_CHOICEBOOK
#    include "wx/bookctrl.h"
#    include "wx/choice.h"
#    include "wx/containr.h"
class WXDLLIMPEXP_FWD_CORE wxChoice;
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_CORE, wxEVT_CHOICEBOOK_PAGE_CHANGED,  wxBookCtrlEvent );
wxDECLARE_EXPORTED_EVENT( WXDLLIMPEXP_CORE, wxEVT_CHOICEBOOK_PAGE_CHANGING, wxBookCtrlEvent );
// wxChoicebook flags
#    define wxCHB_DEFAULT	wxBK_DEFAULT
#    define wxCHB_TOP	wxBK_TOP
#    define wxCHB_BOTTOM	wxBK_BOTTOM
#    define wxCHB_LEFT	wxBK_LEFT
#    define wxCHB_RIGHT	wxBK_RIGHT
#    define wxCHB_ALIGN_MASK	wxBK_ALIGN_MASK
// ----------------------------------------------------------------------------
// wxChoicebook
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxChoicebook : public wxNavigationEnabled<wxBookCtrlBase>
{
public:
  wxChoicebook()
  {
  }
  wxChoicebook(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxEmptyString)
  {
    (void) Create(parent, id, pos, size, style, name);
  }
    // quasi ctor
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxEmptyString);
  bool SetPageText(size_t n, const wxString& strText) override;
  wxString GetPageText(size_t n) const override;
  int GetPageImage(size_t n) const override;
  bool SetPageImage(size_t n, int imageId) override;
  bool InsertPage(size_t n, wxWindow* page, const wxString& text, bool bSelect = false, int imageId = NO_IMAGE) override;
  int SetSelection(size_t n) override
  {
    return DoSetSelection(n, SetSelection_SendEvent);
  }
  int ChangeSelection(size_t n) override
  {
    return DoSetSelection(n);
  }
  void SetImageList(wxImageList* imageList) override;
  bool DeleteAllPages() override;
    // returns the choice control
  wxChoice* GetChoiceCtrl() const
  {
    return (wxChoice*) m_bookctrl;
  }
protected:
  void DoSetWindowVariant(wxWindowVariant variant) override;
  wxWindow* DoRemovePage(size_t page) override;
  void UpdateSelectedPage(size_t newsel) override
  {
    GetChoiceCtrl()->Select(newsel);
  }
  wxBookCtrlEvent* CreatePageChangingEvent() const override;
  void MakeChangedEvent(wxBookCtrlEvent& event) override;
    // event handlers
  void OnChoiceSelected(wxCommandEvent& event);
private:
  wxDECLARE_EVENT_TABLE();
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxChoicebook);
};
// ----------------------------------------------------------------------------
// choicebook event class and related stuff
// ----------------------------------------------------------------------------

// wxChoicebookEvent is obsolete and defined for compatibility only
#    define wxChoicebookEvent	wxBookCtrlEvent
typedef wxBookCtrlEventFunction wxChoicebookEventFunction;
#    define wxChoicebookEventHandler(func)	 wxBookCtrlEventHandler(func)
#    define EVT_CHOICEBOOK_PAGE_CHANGED(winid, fn)	 \
    wx__DECLARE_EVT1(wxEVT_CHOICEBOOK_PAGE_CHANGED, winid, wxBookCtrlEventHandler(fn))
#    define EVT_CHOICEBOOK_PAGE_CHANGING(winid, fn)	 \
    wx__DECLARE_EVT1(wxEVT_CHOICEBOOK_PAGE_CHANGING, winid, wxBookCtrlEventHandler(fn))
// old wxEVT_COMMAND_* constants
#    define wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGED	wxEVT_CHOICEBOOK_PAGE_CHANGED
#    define wxEVT_COMMAND_CHOICEBOOK_PAGE_CHANGING	wxEVT_CHOICEBOOK_PAGE_CHANGING
#  endif
#endif
