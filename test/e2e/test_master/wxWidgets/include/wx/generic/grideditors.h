/////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/grideditors.h
// Purpose:     wxGridCellEditorEvtHandler and wxGrid editors
// Author:      Michael Bedward (based on code by Julian Smart, Robin Dunn)
// Modified by: Santiago Palacios
// Created:     1/08/1999
// Copyright:   (c) Michael Bedward
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GENERIC_GRID_EDITORS_H_
#  define _WX_GENERIC_GRID_EDITORS_H_
#  include "wx/defs.h"
#  if  wxUSE_GRID
#    include "wx/scopedptr.h"
class wxGridCellEditorEvtHandler : public wxEvtHandler
{
public:
  wxGridCellEditorEvtHandler(wxGrid* grid, wxGridCellEditor* editor)
    :  m_grid(grid),
          m_editor(editor),
          m_inSetFocus(false)
    
    {

        }
  void DismissEditor();
  void OnKillFocus(wxFocusEvent& event);
  void OnKeyDown(wxKeyEvent& event);
  void OnChar(wxKeyEvent& event);
  void SetInSetFocus(bool inSetFocus)
  { m_inSetFocus = inSetFocus; }
private:
  wxGrid* m_grid;
  wxGridCellEditor* m_editor;
    // Work around the fact that a focus kill event can be sent to
    // a combobox within a set focus event.
  bool m_inSetFocus;
  wxDECLARE_EVENT_TABLE();
  wxDECLARE_DYNAMIC_CLASS(wxGridCellEditorEvtHandler);
  wxDECLARE_NO_COPY_CLASS(wxGridCellEditorEvtHandler);
};
#    if  wxUSE_TEXTCTRL
// the editor for string/text data
class WXDLLIMPEXP_ADV wxGridCellTextEditor : public wxGridCellEditor
{
public:
  explicit wxGridCellTextEditor(size_t maxChars = 0);
  void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) override;
  void SetSize(const wxRect& rect) override;
  bool IsAcceptedKey(wxKeyEvent& event) override;
  void BeginEdit(int row, int col, wxGrid* grid) override;
  bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
  void ApplyEdit(int row, int col, wxGrid* grid) override;
  void Reset() override;
  void StartingKey(wxKeyEvent& event) override;
  void HandleReturn(wxKeyEvent& event) override;
    // parameters string format is "max_width"
  void SetParameters(const wxString& params) override;
#      if  wxUSE_VALIDATORS
  virtual void SetValidator(const wxValidator& validator);
#      endif
  wxGridCellEditor* Clone() const override;
    // added GetValue so we can get the value which is in the control
  wxString GetValue() const override;
protected:
  wxTextCtrl* Text() const
  { return (wxTextCtrl *)m_control; }
    // parts of our virtual functions reused by the derived classes
  void DoCreate(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler, long style = 0);
  void DoBeginEdit(const wxString& startValue);
  void DoReset(const wxString& startValue);
private:
  size_t m_maxChars;
#      if  wxUSE_VALIDATORS
  wxScopedPtr<wxValidator> m_validator;
#      endif
  wxString m_value;
  wxDECLARE_NO_COPY_CLASS(wxGridCellTextEditor);
};
// the editor for numeric (long) data
class WXDLLIMPEXP_ADV wxGridCellNumberEditor : public wxGridCellTextEditor
{
public:
    // allows to specify the range - if min == max == -1, no range checking is
    // done
  wxGridCellNumberEditor(int min = -1, int max = -1);
  void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) override;
  void SetSize(const wxRect& rect) override;
  bool IsAcceptedKey(wxKeyEvent& event) override;
  void BeginEdit(int row, int col, wxGrid* grid) override;
  bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
  void ApplyEdit(int row, int col, wxGrid* grid) override;
  void Reset() override;
  void StartingKey(wxKeyEvent& event) override;
    // parameters string format is "min,max"
  void SetParameters(const wxString& params) override;
  wxGridCellEditor* Clone() const override
  {
    return new wxGridCellNumberEditor(m_min, m_max);
  }
    // added GetValue so we can get the value which is in the control
  wxString GetValue() const override;
#      if  wxUSE_SPINCTRL
protected:
  wxSpinCtrl* Spin() const
  { return (wxSpinCtrl *)m_control; }
#      endif
    // if HasRange(), we use wxSpinCtrl - otherwise wxTextCtrl
  bool HasRange() const
  {
#if wxUSE_SPINCTRL
        return m_min != m_max;
#else
        return false;
#endif
    }
    // string representation of our value
  wxString GetString() const
  { return wxString::Format(wxT("%ld"), m_value); }
private:
  int m_min, m_max;
  long m_value;
  wxDECLARE_NO_COPY_CLASS(wxGridCellNumberEditor);
};
enum wxGridCellFloatFormat {
    // Decimal floating point (%f)
    wxGRID_FLOAT_FORMAT_FIXED      = 0x0010,

    // Scientific notation (mantise/exponent) using e character (%e)
    wxGRID_FLOAT_FORMAT_SCIENTIFIC = 0x0020,

    // Use the shorter of %e or %f (%g)
    wxGRID_FLOAT_FORMAT_COMPACT    = 0x0040,

    // To use in combination with one of the above formats (%F/%E/%G)
    wxGRID_FLOAT_FORMAT_UPPER      = 0x0080,

    // Format used by default.
    wxGRID_FLOAT_FORMAT_DEFAULT    = wxGRID_FLOAT_FORMAT_FIXED,

    // A mask to extract format from the combination of flags.
    wxGRID_FLOAT_FORMAT_MASK       = wxGRID_FLOAT_FORMAT_FIXED |
                                     wxGRID_FLOAT_FORMAT_SCIENTIFIC |
                                     wxGRID_FLOAT_FORMAT_COMPACT |
                                     wxGRID_FLOAT_FORMAT_UPPER
};
// the editor for floating point numbers (double) data
class WXDLLIMPEXP_ADV wxGridCellFloatEditor : public wxGridCellTextEditor
{
public:
  wxGridCellFloatEditor(int width = -1, int precision = -1, int format = wxGRID_FLOAT_FORMAT_DEFAULT);
  void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) override;
  bool IsAcceptedKey(wxKeyEvent& event) override;
  void BeginEdit(int row, int col, wxGrid* grid) override;
  bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
  void ApplyEdit(int row, int col, wxGrid* grid) override;
  void Reset() override;
  void StartingKey(wxKeyEvent& event) override;
  wxGridCellEditor* Clone() const override
  {
    return new wxGridCellFloatEditor(m_width, m_precision);
  }
    // parameters string format is "width[,precision[,format]]"
    // format to choose between f|e|g|E|G (f is used by default)
  void SetParameters(const wxString& params) override;
protected:
    // string representation of our value
  wxString GetString();
private:
  int m_width, m_precision;
  double m_value;
  int m_style;
  wxString m_format;
  wxDECLARE_NO_COPY_CLASS(wxGridCellFloatEditor);
};
#    endif
#    if  wxUSE_CHECKBOX
// the editor for boolean data
class WXDLLIMPEXP_ADV wxGridCellBoolEditor : public wxGridCellEditor
{
public:
  wxGridCellBoolEditor()
  {
   }
  wxGridActivationResult TryActivate(int row, int col, wxGrid* grid, const wxGridActivationSource& actSource) override;
  void DoActivate(int row, int col, wxGrid* grid) override;
  void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) override;
  void SetSize(const wxRect& rect) override;
  void Show(bool show, wxGridCellAttr* attr = NULL) override;
  bool IsAcceptedKey(wxKeyEvent& event) override;
  void BeginEdit(int row, int col, wxGrid* grid) override;
  bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
  void ApplyEdit(int row, int col, wxGrid* grid) override;
  void Reset() override;
  void StartingClick() override;
  void StartingKey(wxKeyEvent& event) override;
  wxGridCellEditor* Clone() const override
  {
    return new wxGridCellBoolEditor;
  }
    // added GetValue so we can get the value which is in the control, see
    // also UseStringValues()
  wxString GetValue() const override;
    // set the string values returned by GetValue() for the true and false
    // states, respectively
  static void UseStringValues(const wxString& valueTrue = wxT("1"), const wxString& valueFalse = wxEmptyString);
    // return true if the given string is equal to the string representation of
    // true value which we currently use
  static bool IsTrueValue(const wxString& value);
protected:
  wxCheckBox* CBox() const
  { return (wxCheckBox *)m_control; }
private:
    // These functions modify or use m_value.
  void SetValueFromGrid(int row, int col, wxGrid* grid);
  void SetGridFromValue(int row, int col, wxGrid* grid) const;
  wxString GetStringValue() const
  { return GetStringValue(m_value); }
  static wxString GetStringValue(bool value)
  { return ms_stringValues[value]; }
  bool m_value;
  static wxString ms_stringValues[2];
  wxDECLARE_NO_COPY_CLASS(wxGridCellBoolEditor);
};
#    endif
#    if  wxUSE_COMBOBOX
// the editor for string data allowing to choose from the list of strings
class WXDLLIMPEXP_ADV wxGridCellChoiceEditor : public wxGridCellEditor
{
public:
    // if !allowOthers, user can't type a string not in choices array
  wxGridCellChoiceEditor(size_t count = 0, const wxString choices[] = NULL, bool allowOthers = false);
  wxGridCellChoiceEditor(const wxArrayString& choices, bool allowOthers = false);
  void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) override;
  void SetSize(const wxRect& rect) override;
  void BeginEdit(int row, int col, wxGrid* grid) override;
  bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
  void ApplyEdit(int row, int col, wxGrid* grid) override;
  void Reset() override;
    // parameters string format is "item1[,item2[...,itemN]]"
  void SetParameters(const wxString& params) override;
  wxGridCellEditor* Clone() const override;
    // added GetValue so we can get the value which is in the control
  wxString GetValue() const override;
protected:
  wxComboBox* Combo() const
  { return (wxComboBox *)m_control; }
  void OnComboCloseUp(wxCommandEvent& evt);
  wxString m_value;
  wxArrayString m_choices;
  bool m_allowOthers;
  wxDECLARE_NO_COPY_CLASS(wxGridCellChoiceEditor);
};
#    endif
#    if  wxUSE_COMBOBOX
class WXDLLIMPEXP_ADV wxGridCellEnumEditor : public wxGridCellChoiceEditor
{
public:
  wxGridCellEnumEditor(const wxString& choices = wxEmptyString);
  virtual ~wxGridCellEnumEditor()
  {
  }
  wxGridCellEditor* Clone() const override;
  void BeginEdit(int row, int col, wxGrid* grid) override;
  bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
  void ApplyEdit(int row, int col, wxGrid* grid) override;
private:
  long m_index;
  wxDECLARE_NO_COPY_CLASS(wxGridCellEnumEditor);
};
#    endif
class WXDLLIMPEXP_ADV wxGridCellAutoWrapStringEditor : public wxGridCellTextEditor
{
public:
  wxGridCellAutoWrapStringEditor()
    :  wxGridCellTextEditor() 
    {
     }
  void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) override;
  wxGridCellEditor* Clone() const override
  {
    return new wxGridCellAutoWrapStringEditor;
  }
  wxDECLARE_NO_COPY_CLASS(wxGridCellAutoWrapStringEditor);
};
#    if  wxUSE_DATEPICKCTRL
class WXDLLIMPEXP_ADV wxGridCellDateEditor : public wxGridCellEditor
{
public:
  explicit wxGridCellDateEditor(const wxString& format = wxString());
  void SetParameters(const wxString& params) override;
  void Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler) override;
  void SetSize(const wxRect& rect) override;
  void BeginEdit(int row, int col, wxGrid* grid) override;
  bool EndEdit(int row, int col, const wxGrid* grid, const wxString& oldval, wxString* newval) override;
  void ApplyEdit(int row, int col, wxGrid* grid) override;
  void Reset() override;
  wxGridCellEditor* Clone() const override;
  wxString GetValue() const override;
protected:
  wxDatePickerCtrl* DatePicker() const;
private:
  wxDateTime m_value;
  wxString m_format;
  wxDECLARE_NO_COPY_CLASS(wxGridCellDateEditor);
};
#    endif
#  endif
#endif
