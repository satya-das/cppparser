/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/textctrl.h
// Author:      Mariano Reingart, Peter Most
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_TEXTCTRL_H_
#  define _WX_QT_TEXTCTRL_H_
class QScrollArea;
class wxQtEdit;
class WXDLLIMPEXP_CORE wxTextCtrl : public wxTextCtrlBase
{
public:
  wxTextCtrl();
  wxTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTextCtrlNameStr));
  virtual ~wxTextCtrl();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTextCtrlNameStr));
  int GetLineLength(long lineNo) const override;
  wxString GetLineText(long lineNo) const override;
  int GetNumberOfLines() const override;
  bool IsModified() const override;
  void MarkDirty() override;
  void DiscardEdits() override;
  bool SetStyle(long start, long end, const wxTextAttr& style) override;
  bool GetStyle(long position, wxTextAttr& style) override;
  bool SetDefaultStyle(const wxTextAttr& style) override;
  long XYToPosition(long x, long y) const override;
  bool PositionToXY(long pos, long* x, long* y) const override;
  void ShowPosition(long pos) override;
  void SetInsertionPoint(long pos) override;
  long GetInsertionPoint() const override;
  void SetSelection(long from, long to) override;
  void GetSelection(long* from, long* to) const override;
  wxString DoGetValue() const override;
  void DoSetValue(const wxString& text, int flags = 0) override;
  void WriteText(const wxString& text) override;
  QWidget* GetHandle() const override;
protected:
  wxSize DoGetBestSize() const override;
  bool DoLoadFile(const wxString& file, int fileType) override;
  bool DoSaveFile(const wxString& file, int fileType) override;
  QScrollArea* QtGetScrollBarsContainer() const override;
private:
  wxQtEdit* m_qtEdit;
  wxDECLARE_DYNAMIC_CLASS(wxTextCtrl);
};
#endif
