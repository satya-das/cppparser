/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/notebook.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_NOTEBOOK_H_
#  define _WX_QT_NOTEBOOK_H_
class QTabWidget;
class WXDLLIMPEXP_CORE wxNotebook : public wxNotebookBase
{
public:
  wxNotebook();
  wxNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxNotebookNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxASCII_STR(wxNotebookNameStr));
  void SetPadding(const wxSize& padding) override;
  void SetTabSize(const wxSize& sz) override;
  bool SetPageText(size_t n, const wxString& strText) override;
  wxString GetPageText(size_t n) const override;
  int GetPageImage(size_t n) const override;
  bool SetPageImage(size_t n, int imageId) override;
  bool InsertPage(size_t n, wxWindow* page, const wxString& text, bool bSelect = false, int imageId = -1) override;
  wxSize CalcSizeFromPage(const wxSize& sizePage) const override;
  int SetSelection(size_t nPage) override;
  int ChangeSelection(size_t nPage) override;
  bool DeleteAllPages() override;
  QWidget* GetHandle() const override;
protected:
  wxWindow* DoRemovePage(size_t page) override;
private:
  QTabWidget* m_qtTabWidget;
    // internal array to store imageId for each page:
  wxVector<int> m_images;
  wxDECLARE_DYNAMIC_CLASS(wxNotebook);
};
#endif
