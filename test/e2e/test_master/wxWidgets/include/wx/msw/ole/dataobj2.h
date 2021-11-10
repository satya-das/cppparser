///////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/ole/dataobj2.h
// Purpose:     second part of platform specific wxDataObject header -
//              declarations of predefined wxDataObjectSimple-derived classes
// Author:      Vadim Zeitlin
// Modified by:
// Created:     21.10.99
// Copyright:   (c) 1999 Vadim Zeitlin <zeitlin@dptmaths.ens-cachan.fr>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_MSW_OLE_DATAOBJ2_H
#  define _WX_MSW_OLE_DATAOBJ2_H
// ----------------------------------------------------------------------------
// wxBitmapDataObject is a specialization of wxDataObject for bitmap data
//
// NB: in fact, under MSW we support CF_DIB (and not CF_BITMAP) clipboard
//     format and we also provide wxBitmapDataObject2 for CF_BITMAP (which is
//     rarely used). This is ugly, but I haven't found a solution for it yet.
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxBitmapDataObject : public wxBitmapDataObjectBase
{
public:
    // ctors
  wxBitmapDataObject(const wxBitmap& bitmap = wxNullBitmap)
    : wxBitmapDataObjectBase(bitmap)
  {
    SetFormat(wxDF_DIB);
    m_data = NULL;
  }
    // implement base class pure virtuals
  size_t GetDataSize() const override;
  bool GetDataHere(void* buf) const override;
  bool SetData(size_t len, const void* buf) override;
  size_t GetDataSize(const wxDataFormat&) const override
  {
    return GetDataSize();
  }
  bool GetDataHere(const wxDataFormat&, void* buf) const override
  {
    return GetDataHere(buf);
  }
  bool SetData(const wxDataFormat&, size_t len, const void* buf) override
  {
    return SetData(len, buf);
  }
private:
    // the DIB data
  void* m_data;
  wxDECLARE_NO_COPY_CLASS(wxBitmapDataObject);
};
// ----------------------------------------------------------------------------
// wxBitmapDataObject2 - a data object for CF_BITMAP
//
// FIXME did I already mention it was ugly?
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxBitmapDataObject2 : public wxBitmapDataObjectBase
{
public:
    // ctors
  wxBitmapDataObject2(const wxBitmap& bitmap = wxNullBitmap)
    : wxBitmapDataObjectBase(bitmap)
  {
  }
    // implement base class pure virtuals
  size_t GetDataSize() const override;
  bool GetDataHere(void* buf) const override;
  bool SetData(size_t len, const void* buf) override;
  size_t GetDataSize(const wxDataFormat&) const override
  {
    return GetDataSize();
  }
  bool GetDataHere(const wxDataFormat&, void* buf) const override
  {
    return GetDataHere(buf);
  }
  bool SetData(const wxDataFormat&, size_t len, const void* buf) override
  {
    return SetData(len, buf);
  }
private:
  wxDECLARE_NO_COPY_CLASS(wxBitmapDataObject2);
};
// ----------------------------------------------------------------------------
// wxFileDataObject - data object for CF_HDROP
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxFileDataObject : public wxFileDataObjectBase
{
public:
  wxFileDataObject()
  {
  }
    // implement base class pure virtuals
  bool SetData(size_t len, const void* buf) override;
  size_t GetDataSize() const override;
  bool GetDataHere(void* pData) const override;
  virtual void AddFile(const wxString& file);
  size_t GetDataSize(const wxDataFormat&) const override
  {
    return GetDataSize();
  }
  bool GetDataHere(const wxDataFormat&, void* buf) const override
  {
    return GetDataHere(buf);
  }
  bool SetData(const wxDataFormat&, size_t len, const void* buf) override
  {
    return SetData(len, buf);
  }
private:
  wxDECLARE_NO_COPY_CLASS(wxFileDataObject);
};
// ----------------------------------------------------------------------------
// wxURLDataObject: data object for URLs
// ----------------------------------------------------------------------------
class WXDLLIMPEXP_CORE wxURLDataObject : public wxDataObjectComposite
{
public:
    // initialize with URL in ctor or use SetURL later
  wxURLDataObject(const wxString& url = wxEmptyString);
    // return the URL as string
  wxString GetURL() const;
    // Set a string as the URL in the data object
  void SetURL(const wxString& url);
    // override to set m_textFormat
  bool SetData(const wxDataFormat& format, size_t len, const void* buf) override;
private:
    // last data object we got data in
  wxDataObjectSimple* m_dataObjectLast;
  wxDECLARE_NO_COPY_CLASS(wxURLDataObject);
};
#endif
