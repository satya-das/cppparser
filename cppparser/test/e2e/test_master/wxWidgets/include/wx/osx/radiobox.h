/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/radiobox.h
// Purpose:     wxRadioBox class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_RADIOBOX_H_
#  define _WX_RADIOBOX_H_
#  include "wx/containr.h"
// List box item
class WXDLLIMPEXP_FWD_CORE wxBitmap;
class WXDLLIMPEXP_FWD_CORE wxRadioButton;
class WXDLLIMPEXP_CORE wxRadioBox : public wxNavigationEnabled<wxControl>, public wxRadioBoxBase
{
  wxDECLARE_DYNAMIC_CLASS(wxRadioBox);
public:
// Constructors & destructor
  wxRadioBox();
  wxRadioBox(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr))
  {
    Create(parent, id, title, pos, size, n, choices, majorDim, style, val, name);
  }
  wxRadioBox(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr))
  {
    Create(parent, id, title, pos, size, choices, majorDim, style, val, name);
  }
  virtual ~wxRadioBox();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, int majorDim = 0, long style = wxRA_SPECIFY_COLS, const wxValidator& val = wxDefaultValidator, const wxString& name = wxASCII_STR(wxRadioBoxNameStr));
    // Enabling
  bool Enable(bool enable = true) override;
  bool Enable(unsigned int item, bool enable = true) override;
  bool IsItemEnabled(unsigned int item) const override;
    // Showing
  bool Show(bool show = true) override;
  bool Show(unsigned int item, bool show = true) override;
  bool IsItemShown(unsigned int item) const override;
    // Specific functions (in wxWidgets2 reference)
  void SetSelection(int item) override;
  int GetSelection() const override;
  unsigned int GetCount() const override
  {
    return m_noItems;
  }
  wxString GetString(unsigned int item) const override;
  void SetString(unsigned int item, const wxString& label) override;
    // protect native font of box
  bool SetFont(const wxFont& font) override;
// Other external functions
  void Command(wxCommandEvent& event) override;
  void SetFocus() override;
// Other variable access functions
  int GetNumberOfRowsOrCols() const
  {
    return m_noRowsOrCols;
  }
  void SetNumberOfRowsOrCols(int n)
  {
    m_noRowsOrCols = n;
  }
  void OnRadioButton(wxCommandEvent& event);
protected:
    // resolve ambiguity in base classes
  wxBorder GetDefaultBorder() const override
  {
    return wxRadioBoxBase::GetDefaultBorder();
  }
  wxRadioButton* m_radioButtonCycle;
  unsigned int m_noItems;
  int m_noRowsOrCols;
// Internal functions
  wxSize DoGetBestSize() const override;
  void DoSetSize(int x, int y, int width, int height, int sizeFlags = wxSIZE_AUTO) override;
  wxDECLARE_EVENT_TABLE();
};
#endif
    // _WX_RADIOBOX_H_