/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/statbmp.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_STATBMP_H_
#  define _WX_QT_STATBMP_H_
class QLabel;
class WXDLLIMPEXP_CORE wxStaticBitmap : public wxStaticBitmapBase
{
public:
  wxStaticBitmap();
  wxStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxStaticBitmapNameStr));
  void SetIcon(const wxIcon& icon) override;
  void SetBitmap(const wxBitmap& bitmap) override;
  wxBitmap GetBitmap() const override;
  wxIcon GetIcon() const override;
  QWidget* GetHandle() const override;
private:
  QLabel* m_qtLabel;
  wxDECLARE_DYNAMIC_CLASS(wxStaticBitmap);
};
#endif
