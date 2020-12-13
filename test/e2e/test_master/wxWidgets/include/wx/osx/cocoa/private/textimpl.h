/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/cocoa/private/textimpl.h
// Purpose:     textcontrol implementation classes that have to be exposed
// Author:      Stefan Csomor
// Modified by:
// Created:     03/02/99
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_OSX_COCOA_PRIVATE_TEXTIMPL_H_
#  define _WX_OSX_COCOA_PRIVATE_TEXTIMPL_H_
#  include "wx/combobox.h"
#  include "wx/osx/private.h"
class wxTextEntryFormatter;
class wxNSTextBase : public wxWidgetCocoaImpl, public wxTextWidgetImpl
{
public:
  wxNSTextBase(wxTextCtrl* text, WXWidget w)
    : wxWidgetCocoaImpl(text, w)
    , wxTextWidgetImpl(text)
  {
  }
  wxNSTextBase(wxWindow* wxPeer, wxTextEntry* entry, WXWidget w)
    : wxWidgetCocoaImpl(wxPeer, w)
    , wxTextWidgetImpl(entry)
  {
  }
  virtual ~wxNSTextBase()
  {
  }
  bool ShouldHandleKeyNavigation(const wxKeyEvent& event) const override;
  void SetInitialLabel(const wxString&, wxFontEncoding) override
  {
        // Don't do anything here, text controls don't have any label and
        // setting it would overwrite the string value set when creating it.
  }
};
// implementation exposed, so that search control can pull it
class wxNSTextFieldControl : public wxNSTextBase
{
public:
    // wxNSTextFieldControl must always be associated with a wxTextEntry. If
    // it's associated with a wxTextCtrl then we can get the associated entry
    // from it but otherwise the second ctor should be used to explicitly pass
    // us the entry.
  wxNSTextFieldControl(wxTextCtrl* text, WXWidget w);
  wxNSTextFieldControl(wxWindow* wxPeer, wxTextEntry* entry, WXWidget w);
  virtual ~wxNSTextFieldControl();
  bool CanClipMaxLength() const override
  {
    return true;
  }
  void SetMaxLength(unsigned long len) override;
  bool CanForceUpper() override
  {
    return true;
  }
  void ForceUpper() override;
  wxString GetStringValue() const override;
  void SetStringValue(const wxString& str) override;
  void Copy() override;
  void Cut() override;
  void Paste() override;
  bool CanPaste() const override;
  void SetEditable(bool editable) override;
  long GetLastPosition() const override;
  void GetSelection(long* from, long* to) const override;
  void SetSelection(long from, long to) override;
  bool PositionToXY(long pos, long* x, long* y) const override;
  long XYToPosition(long x, long y) const override;
  void ShowPosition(long pos) override;
  void WriteText(const wxString& str) override;
  bool HasOwnContextMenu() const override
  {
    return true;
  }
  bool SetHint(const wxString& hint) override;
  void SetJustification() override;
  void controlAction(WXWidget slf, void* _cmd, void* sender) override;
  bool becomeFirstResponder(WXWidget slf, void* _cmd) override;
  bool resignFirstResponder(WXWidget slf, void* _cmd) override;
  virtual void SetInternalSelection(long from, long to);
  virtual void UpdateInternalSelectionFromEditor(wxNSTextFieldEditor* editor);
protected:
  NSTextField* m_textField;
  long m_selStart;
  long m_selEnd;
private:
    // Common part of both ctors.
  void Init(WXWidget w);
    // Get our formatter, creating it if necessary.
  wxTextEntryFormatter* GetFormatter();
};
class wxNSTextViewControl : public wxNSTextBase
{
public:
  wxNSTextViewControl(wxTextCtrl* wxPeer, WXWidget w, long style);
  virtual ~wxNSTextViewControl();
  void insertText(NSString* text, WXWidget slf, void* _cmd) override;
  wxString GetStringValue() const override;
  void SetStringValue(const wxString& str) override;
  void Copy() override;
  void Cut() override;
  void Paste() override;
  bool CanPaste() const override;
  void SetEditable(bool editable) override;
  long GetLastPosition() const override;
  void GetSelection(long* from, long* to) const override;
  void SetSelection(long from, long to) override;
  bool PositionToXY(long pos, long* x, long* y) const override;
  long XYToPosition(long x, long y) const override;
  void ShowPosition(long pos) override;
  void WriteText(const wxString& str) override;
  void SetFont(const wxFont& font) override;
  bool GetStyle(long position, wxTextAttr& style) override;
  void SetStyle(long start, long end, const wxTextAttr& style) override;
  bool CanFocus() const override;
  bool HasOwnContextMenu() const override
  {
    return true;
  }
  void CheckSpelling(bool check) override;
  void EnableAutomaticQuoteSubstitution(bool enable) override;
  void EnableAutomaticDashSubstitution(bool enable) override;
  wxSize GetBestSize() const override;
  void SetJustification() override;
  void controlTextDidChange() override;
protected:
  void DoUpdateTextStyle();
  NSScrollView* m_scrollView;
  NSTextView* m_textView;
  bool m_useCharWrapping;
};
class wxNSComboBoxControl : public wxNSTextFieldControl, public wxComboWidgetImpl
{
public:
  wxNSComboBoxControl(wxComboBox* wxPeer, WXWidget w);
  virtual ~wxNSComboBoxControl();
  virtual int GetSelectedItem() const;
  virtual void SetSelectedItem(int item);
  virtual int GetNumberOfItems() const;
  virtual void InsertItem(int pos, const wxString& item);
  virtual void RemoveItem(int pos);
  virtual void Clear();
  virtual wxString GetStringAtIndex(int pos) const;
  virtual int FindString(const wxString& text) const;
  virtual void Popup();
  virtual void Dismiss();
  virtual void SetEditable(bool editable);
  virtual void mouseEvent(WX_NSEvent event, WXWidget slf, void* _cmd);
private:
  NSComboBox* m_comboBox;
};
#endif
