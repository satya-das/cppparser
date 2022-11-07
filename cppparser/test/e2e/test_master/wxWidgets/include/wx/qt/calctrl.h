/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/calctrl.h
// Purpose:     wxCalendarCtrl control implementation for wxQt
// Author:      Kolya Kosenko
// Created:     2010-05-12
// Copyright:   (c) 2010 Kolya Kosenko
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_CALCTRL_H_
#  define _WX_QT_CALCTRL_H_
#  include "wx/calctrl.h"
class QCalendarWidget;
class WXDLLIMPEXP_ADV wxCalendarCtrl : public wxCalendarCtrlBase
{
public:
  wxCalendarCtrl()
  {
    Init();
  }
  wxCalendarCtrl(wxWindow* parent, wxWindowID id, const wxDateTime& date = wxDefaultDateTime, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAL_SHOW_HOLIDAYS, const wxString& name = wxASCII_STR(wxCalendarNameStr))
  {
    Init();
    Create(parent, id, date, pos, size, style, name);
  }
  virtual ~wxCalendarCtrl();
  bool Create(wxWindow* parent, wxWindowID id, const wxDateTime& date = wxDefaultDateTime, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAL_SHOW_HOLIDAYS, const wxString& name = wxASCII_STR(wxCalendarNameStr));
  bool SetDate(const wxDateTime& date) override;
  wxDateTime GetDate() const override;
  bool SetDateRange(const wxDateTime& lowerdate = wxDefaultDateTime, const wxDateTime& upperdate = wxDefaultDateTime) override;
  bool GetDateRange(wxDateTime* lowerdate, wxDateTime* upperdate) const override;
  bool EnableMonthChange(bool enable = true) override;
  void Mark(size_t day, bool mark) override;
    // holidays colours
  void SetHoliday(size_t day) override;
  void SetHolidayColours(const wxColour& colFg, const wxColour& colBg) override;
  const wxColour& GetHolidayColourFg() const override
  {
    return m_colHolidayFg;
  }
  const wxColour& GetHolidayColourBg() const override
  {
    return m_colHolidayBg;
  }
    // header colours
  void SetHeaderColours(const wxColour& colFg, const wxColour& colBg) override;
  const wxColour& GetHeaderColourFg() const override
  {
    return m_colHeaderFg;
  }
  const wxColour& GetHeaderColourBg() const override
  {
    return m_colHeaderBg;
  }
    // day attributes
  wxCalendarDateAttr* GetAttr(size_t day) const override;
  void SetAttr(size_t day, wxCalendarDateAttr* attr) override;
  void ResetAttr(size_t day) override
  {
    SetAttr(day, NULL);
  }
  void SetWindowStyleFlag(long style) override;
  using wxCalendarCtrlBase::GenerateAllChangeEvents;
  QWidget* GetHandle() const override;
protected:
  void RefreshHolidays() override;
private:
  void Init();
  void UpdateStyle();
  QCalendarWidget* m_qtCalendar;
  wxColour m_colHeaderFg, m_colHeaderBg, m_colHolidayFg, m_colHolidayBg;
  wxCalendarDateAttr* m_attrs[31];
  wxDECLARE_DYNAMIC_CLASS(wxCalendarCtrl);
};
#endif
