///////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/textentry.h
// Purpose:     wxMSW-specific wxTextEntry implementation
// Author:      Vadim Zeitlin
// Created:     2007-09-26
// Copyright:   (c) 2007 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_TEXTENTRY_H_
#  define _WX_MSW_TEXTENTRY_H_
class wxTextAutoCompleteData;
// ----------------------------------------------------------------------------
// wxTextEntry: common part of wxComboBox and (single line) wxTextCtrl
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxTextEntry : public wxTextEntryBase
{
public:
  wxTextEntry();
  virtual ~wxTextEntry();
    // implement wxTextEntryBase pure virtual methods
  void WriteText(const wxString& text) override;
  void Remove(long from, long to) override;
  void Copy() override;
  void Cut() override;
  void Paste() override;
  void Undo() override;
  void Redo() override;
  bool CanUndo() const override;
  bool CanRedo() const override;
  void SetInsertionPoint(long pos) override;
  long GetInsertionPoint() const override;
  long GetLastPosition() const override;
  void SetSelection(long from, long to) override
  {
    DoSetSelection(from, to);
  }
  void GetSelection(long* from, long* to) const override;
  bool IsEditable() const override;
  void SetEditable(bool editable) override;
  void SetMaxLength(unsigned long len) override;
  void ForceUpper() override;
#  if  wxUSE_UXTHEME
  bool SetHint(const wxString& hint) override;
  wxString GetHint() const override;
#  endif
protected:
  wxString DoGetValue() const override;
    // this is really a hook for multiline text controls as the single line
    // ones don't need to ever scroll to show the selection but having it here
    // allows us to put Remove() in the base class
  enum
  {
    SetSel_NoScroll = 0,
    SetSel_Scroll = 1,
  };
  virtual void DoSetSelection(long from, long to, int flags = SetSel_Scroll);
    // margins functions
  bool DoSetMargins(const wxPoint& pt) override;
  wxPoint DoGetMargins() const override;
    // auto-completion uses COM under Windows so they won't work without
    // wxUSE_OLE as OleInitialize() is not called then
#  if  wxUSE_OLE
  bool DoAutoCompleteStrings(const wxArrayString& choices) override;
#    if  wxUSE_DYNLIB_CLASS
  bool DoAutoCompleteFileNames(int flags) override;
#    endif
  bool DoAutoCompleteCustom(wxTextCompleter* completer) override;
#  endif
    // Helper for wxTE_PROCESS_ENTER handling: activates the default button in
    // the dialog containing this control if any.
  bool ClickDefaultButtonIfPossible();
private:
    // implement this to return the HWND of the EDIT control
  virtual WXHWND GetEditHWND() const = 0;
#  if  wxUSE_OLE
    // This method is called to process special keys such as Return and Tab
    // before they're consumed by the auto-completer. Notice that it is only
    // called if we do need to process the key, i.e. if the corresponding
    // wxTE_PROCESS_XXX style is set in the associated object.
    //
    // It is not pure virtual because it won't get called if the derived class
    // doesn't use auto-completer, but it does need to be overridden if it can
    // be called and the default implementation asserts if this is not the case.
  virtual void MSWProcessSpecialKey(wxKeyEvent& event);
    // Get the auto-complete object creating it if necessary. Returns NULL if
    // creating it failed.
  wxTextAutoCompleteData* GetOrCreateCompleter();
    // Various auto-completion-related stuff, only used if any of AutoComplete()
    // methods are called. Use the function above to access it.
  wxTextAutoCompleteData* m_autoCompleteData;
    // It needs to call our GetEditableWindow() and GetEditHWND() methods.
  friend class wxTextAutoCompleteData;
#  endif
};
// We don't need the generic version.
#  define wxHAS_NATIVE_TEXT_FORCEUPPER
#endif
