/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/bmpcbox.h
// Purpose:     wxBitmapComboBox
// Author:      Jaakko Salli
// Created:     2008-05-19
// Copyright:   (c) 2008 Jaakko Salli
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_GTK_BMPCBOX_H_
#  define _WX_GTK_BMPCBOX_H_
#  include "wx/combobox.h"
// ----------------------------------------------------------------------------
// wxBitmapComboBox: a wxComboBox that allows images to be shown
// in front of string items.
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_ADV wxBitmapComboBox : public wxComboBox, public wxBitmapComboBoxBase
{
public:
    // ctors and such
  wxBitmapComboBox()
    :  wxComboBox(), wxBitmapComboBoxBase()
    
    {

        Init();
        }
  wxBitmapComboBox(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& value = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, int n = 0, const wxString choices[] = NULL, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxBitmapComboBoxNameStr))
    :  wxComboBox(),
          wxBitmapComboBoxBase()
    
    {

        Init();

        (void)Create(parent, id, value, pos, size, n,
                     choices, style, validator, name);
        }
  wxBitmapComboBox(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxBitmapComboBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, int n, const wxString choices[], long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxBitmapComboBoxNameStr));
  bool Create(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, const wxArrayString& choices, long style = 0, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxASCII_STR(wxBitmapComboBoxNameStr));
  virtual ~wxBitmapComboBox();
    // Sets the image for the given item.
  void SetItemBitmap(unsigned int n, const wxBitmap& bitmap) override;
    // Returns the image of the item with the given index.
  wxBitmap GetItemBitmap(unsigned int n) const override;
    // Returns size of the image used in list
  wxSize GetBitmapSize() const override
  {
        return m_bitmapSize;
    }
    // Adds item with image to the end of the combo box.
  int Append(const wxString& item, const wxBitmap& bitmap = wxNullBitmap);
  int Append(const wxString& item, const wxBitmap& bitmap, void* clientData);
  int Append(const wxString& item, const wxBitmap& bitmap, wxClientData* clientData);
    // Inserts item with image into the list before pos. Not valid for wxCB_SORT
    // styles, use Append instead.
  int Insert(const wxString& item, const wxBitmap& bitmap, unsigned int pos);
  int Insert(const wxString& item, const wxBitmap& bitmap, unsigned int pos, void* clientData);
  int Insert(const wxString& item, const wxBitmap& bitmap, unsigned int pos, wxClientData* clientData);
    // Override some wxTextEntry interface.
  void WriteText(const wxString& value) override;
  wxString GetValue() const override;
  void Remove(long from, long to) override;
  void SetInsertionPoint(long pos) override;
  long GetInsertionPoint() const override;
  long GetLastPosition() const override;
  void SetSelection(long from, long to) override;
  void GetSelection(long* from, long* to) const override;
  void SetSelection(int n) override
  { wxComboBox::SetSelection(n); }
  int GetSelection() const override
  { return wxComboBox::GetSelection(); }
  bool IsEditable() const override;
  void SetEditable(bool editable) override;
  GtkWidget* GetConnectWidget() override;
protected:
  GdkWindow* GTKGetWindow(wxArrayGdkWindows& windows) const override;
  void GTKCreateComboBoxWidget() override;
  void GTKInsertComboBoxTextItem(unsigned int n, const wxString& text) override;
  wxSize DoGetBestSize() const override;
  wxSize m_bitmapSize;
  int m_bitmapCellIndex;
private:
  void Init();
  wxDECLARE_DYNAMIC_CLASS(wxBitmapComboBox);
};
#endif
