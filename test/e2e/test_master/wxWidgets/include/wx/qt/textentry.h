/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/textentry.h
// Author:      Peter Most, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_TEXTENTRY_H_
#  define _WX_QT_TEXTENTRY_H_
class WXDLLIMPEXP_CORE wxTextEntry : public wxTextEntryBase
{
public:
  wxTextEntry();
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
  void SetSelection(long from, long to) override;
  void GetSelection(long* from, long* to) const override;
  bool IsEditable() const override;
  void SetEditable(bool editable) override;
protected:
  wxString DoGetValue() const override;
  void DoSetValue(const wxString& value, int flags = 0) override;
  wxWindow* GetEditableWindow() override;
};
#endif
