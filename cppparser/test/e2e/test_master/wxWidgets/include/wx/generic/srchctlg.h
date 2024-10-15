/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/srchctlg.h
// Purpose:     generic wxSearchCtrl class
// Author:      Vince Harron
// Created:     2006-02-19
// Copyright:   Vince Harron
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GENERIC_SEARCHCTRL_H_
#  define _WX_GENERIC_SEARCHCTRL_H_
#  if  wxUSE_SEARCHCTRL
#    include "wx/bitmap.h"
class WXDLLIMPEXP_FWD_CORE wxSearchButton;
class WXDLLIMPEXP_FWD_CORE wxSearchTextCtrl;
// ----------------------------------------------------------------------------
// wxSearchCtrl is a combination of wxTextCtrl and wxSearchButton
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxSearchCtrl : public wxSearchCtrlBase
{
public:
    // creation
    // --------
  wxSearchCtrl();
  wxSearchCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxSearchCtrlNameStr));
  virtual ~wxSearchCtrl();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxSearchCtrlNameStr));
#    if  wxUSE_MENUS
    // get/set search button menu
    // --------------------------
  void SetMenu(wxMenu* menu) override;
  wxMenu* GetMenu() override;
#    endif
    // get/set search options
    // ----------------------
  void ShowSearchButton(bool show) override;
  bool IsSearchButtonVisible() const override;
  void ShowCancelButton(bool show) override;
  bool IsCancelButtonVisible() const override;
  void SetDescriptiveText(const wxString& text) override;
  wxString GetDescriptiveText() const override;
    // accessors
    // ---------
  wxString GetRange(long from, long to) const override;
  int GetLineLength(long lineNo) const override;
  wxString GetLineText(long lineNo) const override;
  int GetNumberOfLines() const override;
  bool IsModified() const override;
  bool IsEditable() const override;
    // more readable flag testing methods
  virtual bool IsSingleLine() const;
  virtual bool IsMultiLine() const;
    // If the return values from and to are the same, there is no selection.
  void GetSelection(long* from, long* to) const override;
  wxString GetStringSelection() const override;
    // operations
    // ----------
  void ChangeValue(const wxString& value) override;
    // editing
  void Clear() override;
  void Replace(long from, long to, const wxString& value) override;
  void Remove(long from, long to) override;
    // load/save the controls contents from/to the file
  virtual bool LoadFile(const wxString& file);
  virtual bool SaveFile(const wxString& file = wxEmptyString);
    // sets/clears the dirty flag
  void MarkDirty() override;
  void DiscardEdits() override;
    // set the max number of characters which may be entered in a single line
    // text control
  void SetMaxLength(unsigned long) override;
    // writing text inserts it at the current position, appending always
    // inserts it at the end
  void WriteText(const wxString& text) override;
  void AppendText(const wxString& text) override;
    // insert the character which would have resulted from this key event,
    // return true if anything has been inserted
  virtual bool EmulateKeyPress(const wxKeyEvent& event);
    // text control under some platforms supports the text styles: these
    // methods allow to apply the given text style to the given selection or to
    // set/get the style which will be used for all appended text
  bool SetStyle(long start, long end, const wxTextAttr& style) override;
  bool GetStyle(long position, wxTextAttr& style) override;
  bool SetDefaultStyle(const wxTextAttr& style) override;
  const wxTextAttr& GetDefaultStyle() const override;
    // translate between the position (which is just an index in the text ctrl
    // considering all its contents as a single strings) and (x, y) coordinates
    // which represent column and line.
  long XYToPosition(long x, long y) const override;
  bool PositionToXY(long pos, long* x, long* y) const override;
  void ShowPosition(long pos) override;
    // find the character at position given in pixels
    //
    // NB: pt is in device coords (not adjusted for the client area origin nor
    //     scrolling)
  wxTextCtrlHitTestResult HitTest(const wxPoint& pt, long* pos) const override;
  wxTextCtrlHitTestResult HitTest(const wxPoint& pt, wxTextCoord* col, wxTextCoord* row) const override;
    // Clipboard operations
  void Copy() override;
  void Cut() override;
  void Paste() override;
  bool CanCopy() const override;
  bool CanCut() const override;
  bool CanPaste() const override;
    // Undo/redo
  void Undo() override;
  void Redo() override;
  bool CanUndo() const override;
  bool CanRedo() const override;
    // Insertion point
  void SetInsertionPoint(long pos) override;
  void SetInsertionPointEnd() override;
  long GetInsertionPoint() const override;
  wxTextPos GetLastPosition() const override;
  void SetSelection(long from, long to) override;
  void SelectAll() override;
  void SetEditable(bool editable) override;
    // Autocomplete
  bool DoAutoCompleteStrings(const wxArrayString& choices) override;
  bool DoAutoCompleteFileNames(int flags) override;
  bool DoAutoCompleteCustom(wxTextCompleter* completer) override;
  bool ShouldInheritColours() const override;
    // wxWindow overrides
  bool SetFont(const wxFont& font) override;
  bool SetBackgroundColour(const wxColour& colour) override;
    // search control generic only
  void SetSearchBitmap(const wxBitmap& bitmap);
  void SetCancelBitmap(const wxBitmap& bitmap);
#    if  wxUSE_MENUS
  void SetSearchMenuBitmap(const wxBitmap& bitmap);
#    endif
protected:
  void DoSetValue(const wxString& value, int flags) override;
  wxString DoGetValue() const override;
  bool DoLoadFile(const wxString& file, int fileType) override;
  bool DoSaveFile(const wxString& file, int fileType) override;
    // override the base class virtuals involved into geometry calculations
  wxSize DoGetBestClientSize() const override;
  virtual void RecalcBitmaps();
  void Init();
  virtual wxBitmap RenderSearchBitmap(int x, int y, bool renderDrop);
  virtual wxBitmap RenderCancelBitmap(int x, int y);
  void OnCancelButton(wxCommandEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnDPIChanged(wxDPIChangedEvent& event);
  bool HasMenu() const
  {
#    if  wxUSE_MENUS
    return m_menu != NULL;
#    else 
    return false;
#    endif
  }
private:
  friend class wxSearchButton;
    // Implement pure virtual function inherited from wxCompositeWindow.
  wxWindowList GetCompositeWindowParts() const override;
    // Position the child controls using the current window size.
  void LayoutControls();
#    if  wxUSE_MENUS
  void PopupSearchMenu();
#    endif
    // the subcontrols
  wxSearchTextCtrl* m_text;
  wxSearchButton* m_searchButton;
  wxSearchButton* m_cancelButton;
#    if  wxUSE_MENUS
  wxMenu* m_menu;
#    endif
  bool m_searchBitmapUser;
  bool m_cancelBitmapUser;
#    if  wxUSE_MENUS
  bool m_searchMenuBitmapUser;
#    endif
  wxBitmap m_searchBitmap;
  wxBitmap m_cancelBitmap;
#    if  wxUSE_MENUS
  wxBitmap m_searchMenuBitmap;
#    endif
private:
  wxDECLARE_DYNAMIC_CLASS(wxSearchCtrl);
  wxDECLARE_EVENT_TABLE();
};
#  endif
#endif
