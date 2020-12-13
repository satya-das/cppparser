/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/anybutton.h
// Purpose:     wxQT wxAnyButton class declaration
// Author:      Mariano Reingart
// Copyright:   (c) 2014 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_ANYBUTTON_H_
#  define _WX_QT_ANYBUTTON_H_
class QPushButton;
//-----------------------------------------------------------------------------
// wxAnyButton
//-----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxAnyButton : public wxAnyButtonBase
{
public:
  wxAnyButton();
    // implementation
    // --------------
  void SetLabel(const wxString& label) override;
  QWidget* GetHandle() const override;
    // implementation only
  void QtUpdateState();
  virtual int QtGetEventType() const = 0;
protected:
  wxBitmap DoGetBitmap(State state) const override;
  void DoSetBitmap(const wxBitmap& bitmap, State which) override;
  QPushButton* m_qtPushButton;
  void QtCreate(wxWindow* parent);
  void QtSetBitmap(const wxBitmap& bitmap);
private:
  State QtGetCurrentState() const;
  typedef wxAnyButtonBase base_type;
  wxBitmap m_bitmaps[State_Max];
  wxDECLARE_NO_COPY_CLASS(wxAnyButton);
};
#endif
