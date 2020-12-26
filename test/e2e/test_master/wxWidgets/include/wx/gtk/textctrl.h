/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/textctrl.h
// Purpose:
// Author:      Robert Roebling
// Created:     01/02/97
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_TEXTCTRL_H_
#  define _WX_GTK_TEXTCTRL_H_
typedef struct _GtkTextMark GtkTextMark;
//-----------------------------------------------------------------------------
// wxTextCtrl
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxTextCtrl : public wxTextCtrlBase
{
public:
  wxTextCtrl()
  {
 Init();   }
  wxTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTextCtrlNameStr));
  virtual ~wxTextCtrl();
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxTextCtrlNameStr));
    // implement base class pure virtuals
    // ----------------------------------
  void WriteText(const wxString& text) override;
  wxString GetValue() const override;
  virtual bool IsEmpty() const;
  int GetLineLength(long lineNo) const override;
  wxString GetLineText(long lineNo) const override;
  int GetNumberOfLines() const override;
  bool IsModified() const override;
  bool IsEditable() const override;
  void GetSelection(long* from, long* to) const override;
  void Remove(long from, long to) override;
  void MarkDirty() override;
  void DiscardEdits() override;
  bool SetStyle(long start, long end, const wxTextAttr& style) override;
  bool GetStyle(long position, wxTextAttr& style) override;
    // translate between the position (which is just an index in the text ctrl
    // considering all its contents as a single strings) and (x, y) coordinates
    // which represent column and line.
  long XYToPosition(long x, long y) const override;
  bool PositionToXY(long pos, long* x, long* y) const override;
  void ShowPosition(long pos) override;
  wxTextCtrlHitTestResult HitTest(const wxPoint& pt, long* pos) const override;
  wxTextCtrlHitTestResult HitTest(const wxPoint& pt, wxTextCoord* col, wxTextCoord* row) const override
  {
    return wxTextCtrlBase::HitTest(pt, col, row);
  }
    // Clipboard operations
  void Copy() override;
  void Cut() override;
  void Paste() override;
    // Insertion point
  void SetInsertionPoint(long pos) override;
  long GetInsertionPoint() const override;
  wxTextPos GetLastPosition() const override;
  void SetSelection(long from, long to) override;
  void SetEditable(bool editable) override;
    // Overridden wxWindow methods
  void SetWindowStyleFlag(long style) override;
    // Implementation from now on
  void OnDropFiles(wxDropFilesEvent& event);
  void OnChar(wxKeyEvent& event);
  void OnCut(wxCommandEvent& event);
  void OnCopy(wxCommandEvent& event);
  void OnPaste(wxCommandEvent& event);
  void OnUndo(wxCommandEvent& event);
  void OnRedo(wxCommandEvent& event);
  void OnUpdateCut(wxUpdateUIEvent& event);
  void OnUpdateCopy(wxUpdateUIEvent& event);
  void OnUpdatePaste(wxUpdateUIEvent& event);
  void OnUpdateUndo(wxUpdateUIEvent& event);
  void OnUpdateRedo(wxUpdateUIEvent& event);
  bool SetFont(const wxFont& font) override;
  bool SetForegroundColour(const wxColour& colour) override;
  bool SetBackgroundColour(const wxColour& colour) override;
  GtkWidget* GetConnectWidget() override;
  void SetUpdateFont(bool)
  { }
    // implementation only from now on

    // tell the control to ignore next text changed signal
  void IgnoreNextTextUpdate(int n = 1)
  { m_countUpdatesToIgnore = n; }
    // should we ignore the changed signal? always resets the flag
  bool IgnoreTextUpdate();
    // call this to indicate that the control is about to be changed
    // programmatically and so m_modified flag shouldn't be set
  void DontMarkDirtyOnNextChange()
  { m_dontMarkDirty = true; }
    // should we mark the control as dirty? always resets the flag
  bool MarkDirtyOnChange();
    // always let GTK have mouse release events for multiline controls
  bool GTKProcessEvent(wxEvent& event) const override;
  static wxVisualAttributes GetClassDefaultAttributes(wxWindowVariant variant = wxWINDOW_VARIANT_NORMAL);
  void GTKOnTextChanged() override;
  void GTKAfterLayout();
protected:
    // overridden wxWindow virtual methods
  wxSize DoGetBestSize() const override;
  void DoApplyWidgetStyle(GtkRcStyle* style) override;
  GdkWindow* GTKGetWindow(wxArrayGdkWindows& windows) const override;
  wxSize DoGetSizeFromTextSize(int xlen, int ylen = -1) const override;
  void DoFreeze() override;
  void DoThaw() override;
  void DoEnable(bool enable) override;
    // Widgets that use the style->base colour for the BG colour should
    // override this and return true.
  bool UseGTKStyleBase() const override
  {
    return true;
  }
  wxString DoGetValue() const override;
    // Override this to use either GtkEntry or GtkTextView IME depending on the
    // kind of control we are.
  int GTKIMFilterKeypress(GdkEventKey* event) const override;
  wxPoint DoPositionToCoords(long pos) const override;
    // wrappers hiding the differences between functions doing the same thing
    // for GtkTextView and GtkEntry (all of them use current window style to
    // set the given characteristic)
  void GTKSetEditable();
  void GTKSetVisibility();
  void GTKSetActivatesDefault();
  void GTKSetWrapMode();
  void GTKSetJustification();
private:
  void Init();
    // overridden wxTextEntry virtual methods
  GtkEditable* GetEditable() const override;
  GtkEntry* GetEntry() const override;
    // change the font for everything in this control
  void ChangeFontGlobally();
    // get the encoding which is used in this control: this looks at our font
    // and default style but not the current style (i.e. the style for the
    // current position); returns wxFONTENCODING_SYSTEM if we have no specific
    // encoding
  wxFontEncoding GetTextEncoding() const;
    // returns either m_text or m_buffer depending on whether the control is
    // single- or multi-line; convenient for the GTK+ functions which work with
    // both
  void* GetTextObject() const override
  {
    return IsMultiLine() ? static_cast<void*>(m_buffer) : static_cast<void*>(m_text);
  }
    // the widget used for single line controls
  GtkWidget* m_text;
  bool m_modified;
  bool m_dontMarkDirty;
  int m_countUpdatesToIgnore;
    // Our text buffer. Convenient, and holds the buffer while using
    // a dummy one when frozen
  GtkTextBuffer* m_buffer;
  GtkTextMark* m_showPositionDefer;
  GSList* m_anonymousMarkList;
  unsigned m_afterLayoutId;
    // For wxTE_AUTO_URL
  void OnUrlMouseEvent(wxMouseEvent&);
  wxDECLARE_EVENT_TABLE();
  wxDECLARE_DYNAMIC_CLASS(wxTextCtrl);
};
#endif
