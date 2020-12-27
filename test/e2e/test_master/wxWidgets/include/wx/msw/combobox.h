/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/combobox.h
// Purpose:     wxComboBox class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_COMBOBOX_H_
#  define _WX_COMBOBOX_H_
#  include "wx/choice.h"
#  include "wx/textentry.h"
#  if  wxUSE_COMBOBOX
// ----------------------------------------------------------------------------
// Combobox control
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxComboBox : public wxChoice, public wxTextEntry
{
public:
  wxComboBox()
  {
 Init();   }
  wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr))
  {

        Init();
        Create(parent, id, value, pos, size, n, choices, style, validator, name);

      }
  wxComboBox(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr))
  {

        Init();

        Create(parent, id, value, pos, size, choices, style, validator, name);
      }
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxComboBoxNameStr));
    // See wxComboBoxBase discussion of IsEmpty().
  bool IsListEmpty() const
  { return wxItemContainer::IsEmpty(); }
  bool IsTextEmpty() const
  { return wxTextEntry::IsEmpty(); }
    // resolve ambiguities among virtual functions inherited from both base
    // classes
  void Clear() override;
  wxString GetValue() const override;
  void SetValue(const wxString& value) override;
  wxString GetStringSelection() const override
  { return wxChoice::GetStringSelection(); }
  virtual void Popup()
  { MSWDoPopupOrDismiss(true); }
  virtual void Dismiss()
  { MSWDoPopupOrDismiss(false); }
  void SetSelection(int n) override
  { wxChoice::SetSelection(n); }
  void SetSelection(long from, long to) override
  { wxTextEntry::SetSelection(from, to); }
  int GetSelection() const override
  { return wxChoice::GetSelection(); }
  bool ContainsHWND(WXHWND hWnd) const override;
  void GetSelection(long* from, long* to) const override;
  bool IsEditable() const override;
    // implementation only from now on
  bool MSWCommand(WXUINT param, WXWORD id) override;
  bool MSWProcessEditMsg(WXUINT msg, WXWPARAM wParam, WXLPARAM lParam);
  WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) override;
  bool MSWShouldPreProcessMessage(WXMSG* pMsg) override;
    // Standard event handling
  void OnCut(wxCommandEvent& event);
  void OnCopy(wxCommandEvent& event);
  void OnPaste(wxCommandEvent& event);
  void OnUndo(wxCommandEvent& event);
  void OnRedo(wxCommandEvent& event);
  void OnDelete(wxCommandEvent& event);
  void OnSelectAll(wxCommandEvent& event);
  void OnUpdateCut(wxUpdateUIEvent& event);
  void OnUpdateCopy(wxUpdateUIEvent& event);
  void OnUpdatePaste(wxUpdateUIEvent& event);
  void OnUpdateUndo(wxUpdateUIEvent& event);
  void OnUpdateRedo(wxUpdateUIEvent& event);
  void OnUpdateDelete(wxUpdateUIEvent& event);
  void OnUpdateSelectAll(wxUpdateUIEvent& event);
  WXDWORD MSWGetStyle(long style, WXDWORD* exstyle) const override;
#    if  wxUSE_UXTHEME
    // override wxTextEntry method to work around Windows bug
  bool SetHint(const wxString& hint) override;
#    endif
  void SetLayoutDirection(wxLayoutDirection dir) override;
  const wxTextEntry* WXGetTextEntry() const override
  { return this; }
#    if  wxUSE_TOOLTIPS
protected:
  void DoSetToolTip(wxToolTip* tip) override;
#    endif
  wxSize DoGetSizeFromTextSize(int xlen, int ylen = -1) const override;
    // Override this one to avoid eating events from our popup listbox.
  wxWindow* MSWFindItem(long id, WXHWND hWnd) const override;
    // this is the implementation of GetEditHWND() which can also be used when
    // we don't have the edit control, it simply returns NULL then
    //
    // try not to use this function unless absolutely necessary (as in the
    // message handling code where the edit control might not be created yet
    // for the messages we receive during the control creation) as normally
    // just testing for IsEditable() and using GetEditHWND() should be enough
  WXHWND GetEditHWNDIfAvailable() const;
  void EnableTextChangedEvents(bool enable) override
  {
        m_allowTextEvents = enable;
    }
private:
    // there are the overridden wxTextEntry methods which should only be called
    // when we do have an edit control so they assert if this is not the case
  wxWindow* GetEditableWindow() override;
  WXHWND GetEditHWND() const override;
    // Common part of MSWProcessEditMsg() and MSWProcessSpecialKey(), return
    // true if the key was processed.
  bool MSWProcessEditSpecialKey(WXWPARAM vkey);
#    if  wxUSE_OLE
  void MSWProcessSpecialKey(wxKeyEvent& event) override;
#    endif
    // common part of all ctors
  void Init()
  {
        m_allowTextEvents = true;
    }
    // normally true, false if text events are currently disabled
  bool m_allowTextEvents;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxComboBox);
  wxDECLARE_EVENT_TABLE();
};
#  endif
#endif
