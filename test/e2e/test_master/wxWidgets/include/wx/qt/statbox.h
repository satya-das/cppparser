/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/statbox.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_STATBOX_H_
#  define _WX_QT_STATBOX_H_
class QGroupBox;
class WXDLLIMPEXP_CORE wxStaticBox : public wxStaticBoxBase
{
public:
  wxStaticBox();
  wxStaticBox(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBoxNameStr));
  void GetBordersForSizer(int* borderTop, int* borderOther) const override;
  QWidget* GetHandle() const override;
  void SetLabel(const wxString& label) override;
  wxString GetLabel() const override;
private:
  QGroupBox* m_qtGroupBox;
  wxDECLARE_DYNAMIC_CLASS( wxStaticBox );
};
#endif
