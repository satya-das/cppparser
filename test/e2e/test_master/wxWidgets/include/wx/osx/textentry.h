/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/textentry.h
// Purpose:     wxTextEntry class
// Author:      Stefan Csomor
// Modified by: Kevin Ollivier
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_OSX_TEXTENTRY_H_
#  define _WX_OSX_TEXTENTRY_H_
    // set this to 'true' if you want to use the 'classic' MLTE-based implementation
    // instead of the HIView-based implementation in 10.3 and upwards, the former
    // has more features (backgrounds etc.), but may show redraw artefacts and other
    // problems depending on your usage; hence, the default is 'false'.
#  define wxMAC_TEXTCONTROL_USE_MLTE	wxT("mac.textcontrol-use-mlte")
    // set this to 'true' if you want editable text controls to have spell checking turned
    // on by default, you can change this setting individually on a control using MacCheckSpelling
#  define wxMAC_TEXTCONTROL_USE_SPELL_CHECKER	wxT("mac.textcontrol-use-spell-checker")
#  include "wx/control.h"
// forward decl for wxListWidgetImpl implementation type.
class WXDLLIMPEXP_FWD_CORE wxTextWidgetImpl;
class WXDLLIMPEXP_CORE wxTextEntry : public wxTextEntryBase
{
public:
  wxTextEntry();
  virtual ~wxTextEntry();
  bool IsEditable() const override;
    // If the return values from and to are the same, there is no selection.
  void GetSelection(long* from, long* to) const override;
    // operations
    // ----------

    // editing
  void Clear() override;
  void Remove(long from, long to) override;
    // set the max number of characters which may be entered
    // in a single line text control
  void SetMaxLength(unsigned long len) override;
  void ForceUpper() override;
    // writing text inserts it at the current position;
    // appending always inserts it at the end
  void WriteText(const wxString& text) override;
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
  void SetEditable(bool editable) override;
  virtual bool SendMaxLenEvent();
    // set the grayed out hint text
  bool SetHint(const wxString& hint) override;
  wxString GetHint() const override;
    // Implementation
    // --------------
  virtual wxTextWidgetImpl* GetTextPeer() const;
  wxTextCompleter* OSXGetCompleter() const
  {
    return m_completer;
  }
protected:
  wxString DoGetValue() const override;
  bool DoAutoCompleteStrings(const wxArrayString& choices) override;
  bool DoAutoCompleteCustom(wxTextCompleter* completer) override;
    // The object providing auto-completions or NULL if none.
  wxTextCompleter* m_completer;
  bool m_editable;
  // need to make this public because of the current implementation via callbacks
  unsigned long m_maxLength;
private:
  wxString m_hintString;
};
#endif
