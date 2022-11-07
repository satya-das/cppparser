///////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/dvrenderer.h
// Purpose:     wxDataViewRenderer for OS X wxDataViewCtrl implementations
// Author:      Vadim Zeitlin
// Created:     2009-11-07 (extracted from wx/osx/dataview.h)
// Copyright:   (c) 2009 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_OSX_DVRENDERER_H_
#  define _WX_OSX_DVRENDERER_H_
class wxDataViewRendererNativeData;
// ----------------------------------------------------------------------------
// wxDataViewRenderer
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_ADV wxDataViewRenderer : public wxDataViewRendererBase
{
public:
    // constructors / destructor
    // -------------------------
  wxDataViewRenderer(const wxString& varianttype, wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT, int align = wxDVR_DEFAULT_ALIGNMENT);
  virtual ~wxDataViewRenderer();
    // inherited methods from wxDataViewRendererBase
    // ---------------------------------------------
  int GetAlignment() const override
  {
    return m_alignment;
  }
  wxDataViewCellMode GetMode() const override
  {
    return m_mode;
  }
  bool GetValue(wxVariant& value) const override
  {
    value = m_value;
    return true;
  }
    // NB: in Carbon this is always identical to the header alignment
  void SetAlignment(int align) override;
  void SetMode(wxDataViewCellMode mode) override;
  bool SetValue(const wxVariant& newValue) override
  {
    m_value = newValue;
    return true;
  }
  void EnableEllipsize(wxEllipsizeMode mode = wxELLIPSIZE_MIDDLE) override;
  wxEllipsizeMode GetEllipsizeMode() const override;
    // implementation
    // --------------
  const wxVariant& GetValue() const
  {
    return m_value;
  }
  wxDataViewRendererNativeData* GetNativeData() const
  {
    return m_NativeDataPtr;
  }
    // a call to the native data browser function to render the data;
    // returns true if the data value could be rendered, false otherwise
  virtual bool MacRender() = 0;
  void SetNativeData(wxDataViewRendererNativeData* newNativeDataPtr);
  void OSXUpdateAlignment();
#  if  wxOSX_USE_COCOA
    // called when a value was edited by user
  virtual void OSXOnCellChanged(NSObject* value, const wxDataViewItem& item, unsigned col);
protected:
  void SetAttr(const wxDataViewItemAttr& attr) override;
  void SetEnabled(bool enabled) override;
#  else 
  void SetAttr(const wxDataViewItemAttr&) override
  {
  }
  void SetEnabled(bool) override
  {
  }
#  endif
  bool IsHighlighted() const override;
private:
    // contains the alignment flags
  int m_alignment;
    // storing the mode that determines how the cell is going to be shown
  wxDataViewCellMode m_mode;
    // data used by implementation of the native renderer
  wxDataViewRendererNativeData* m_NativeDataPtr;
    // value that is going to be rendered
  wxVariant m_value;
  wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewRenderer);
};
#endif
