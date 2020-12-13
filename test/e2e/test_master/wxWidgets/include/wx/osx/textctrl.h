/////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/textctrl.h
// Purpose:     wxTextCtrl class
// Author:      Stefan Csomor
// Modified by:
// Created:     1998-01-01
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_TEXTCTRL_H_
#  define _WX_TEXTCTRL_H_
#  if  wxUSE_SYSTEM_OPTIONS
    // set this to 'true' if you want to use the 'classic' MLTE-based implementation
    // instead of the HIView-based implementation in 10.3 and upwards, the former
    // has more features (backgrounds etc.), but may show redraw artefacts and other
    // problems depending on your usage; hence, the default is 'false'.
#    define wxMAC_TEXTCONTROL_USE_MLTE	wxT("mac.textcontrol-use-mlte")
    // set this to 'true' if you want editable text controls to have spell checking turned
    // on by default, you can change this setting individually on a control using MacCheckSpelling
#    define wxMAC_TEXTCONTROL_USE_SPELL_CHECKER	wxT("mac.textcontrol-use-spell-checker")
#  endif
#  include "wx/control.h"
#  include "wx/textctrl.h"
class WXDLLIMPEXP_CORE wxTextCtrl : public wxTextCtrlBase
{
  wxDECLARE_DYNAMIC_CLASS(wxTextCtrl);
public:
  wxTextCtrl()
  {
    Init();
  }
  wxTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTextCtrlNameStr))
  {
    Init();
    Create(parent, id, value, pos, size, style, validator, name);
  }
  virtual ~wxTextCtrl();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTextCtrlNameStr));
    // accessors
    // ---------
  int GetLineLength(long lineNo) const override;
  wxString GetLineText(long lineNo) const override;
  int GetNumberOfLines() const override;
  bool IsModified() const override;
    // operations
    // ----------


    // sets/clears the dirty flag
  void MarkDirty() override;
  void DiscardEdits() override;
    // text control under some platforms supports the text styles: these
    // methods apply the given text style to the given selection or to
    // set/get the style which will be used for all appended text
  bool SetFont(const wxFont& font) override;
  bool GetStyle(long position, wxTextAttr& style) override;
  bool SetStyle(long start, long end, const wxTextAttr& style) override;
  bool SetDefaultStyle(const wxTextAttr& style) override;
    // translate between the position (which is just an index into the textctrl
    // considering all its contents as a single strings) and (x, y) coordinates
    // which represent column and line.
  long XYToPosition(long x, long y) const override;
  bool PositionToXY(long pos, long* x, long* y) const override;
  void ShowPosition(long pos) override;
    // overrides so that we can send text updated events
  void Copy() override;
  void Cut() override;
  void Paste() override;
    // Implementation
    // --------------
  void Command(wxCommandEvent& event) override;
  void SetWindowStyleFlag(long style) override;
    // callbacks
  void OnDropFiles(wxDropFilesEvent& event);
  void OnChar(wxKeyEvent& event);
  void OnKeyDown(wxKeyEvent& event);
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
  void OnContextMenu(wxContextMenuEvent& event);
  bool MacSetupCursor(const wxPoint& pt) override;
  void MacVisibilityChanged() override;
  void MacSuperChangedPosition() override;
  virtual void MacCheckSpelling(bool check);
  void OSXEnableAutomaticQuoteSubstitution(bool enable);
  void OSXEnableAutomaticDashSubstitution(bool enable);
  void OSXDisableAllSmartSubstitutions();
protected:
    // common part of all ctors
  void Init();
  wxSize DoGetBestSize() const override;
  wxSize DoGetSizeFromTextSize(int xlen, int ylen) const override;
    // flag is set to true when the user edits the controls contents
  bool m_dirty;
  void EnableTextChangedEvents(bool) override
  {
        // nothing to do here as the events are never generated when we change
        // the controls value programmatically anyhow
  }
private:
  wxMenu* m_privateContextMenu;
  wxDECLARE_EVENT_TABLE();
};
#endif
