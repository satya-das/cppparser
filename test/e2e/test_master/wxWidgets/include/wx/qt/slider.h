/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/slider.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_SLIDER_H_
#  define _WX_QT_SLIDER_H_
class QSlider;
class WXDLLIMPEXP_CORE wxSlider : public wxSliderBase
{
public:
  wxSlider();
  wxSlider(wxWindow* parent, wxWindowID id, int value, int minValue, int maxValue, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSL_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxSliderNameStr));
  bool Create(wxWindow* parent, wxWindowID id, int value, int minValue, int maxValue, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSL_HORIZONTAL, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxSliderNameStr));
  int GetValue() const override;
  void SetValue(int value) override;
  void SetRange(int minValue, int maxValue) override;
  int GetMin() const override;
  int GetMax() const override;
  void DoSetTickFreq(int freq) override;
  int GetTickFreq() const override;
  void SetLineSize(int lineSize) override;
  void SetPageSize(int pageSize) override;
  int GetLineSize() const override;
  int GetPageSize() const override;
  void SetThumbLength(int lenPixels) override;
  int GetThumbLength() const override;
  QWidget* GetHandle() const override;
private:
  QSlider* m_qtSlider;
  wxDECLARE_DYNAMIC_CLASS(wxSlider);
};
#endif
