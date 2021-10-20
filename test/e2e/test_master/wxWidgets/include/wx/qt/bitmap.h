/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/bitmap.h
// Author:      Peter Most, Javier Torres, Mariano Reingart
// Copyright:   (c) 2010 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
#ifndef _WX_QT_BITMAP_H_
#  define _WX_QT_BITMAP_H_
class WXDLLIMPEXP_FWD_CORE wxPixelDataBase;
class WXDLLIMPEXP_FWD_CORE wxImage;
class WXDLLIMPEXP_FWD_CORE wxCursor;
class QImage;
class QPixmap;
class QBitmap;
class WXDLLIMPEXP_CORE wxBitmap : public wxBitmapBase
{
public:
  wxBitmap();
  wxBitmap(QPixmap pix);
  wxBitmap(const char bits[], int width, int height, int depth = 1);
  wxBitmap(int width, int height, int depth = wxBITMAP_SCREEN_DEPTH);
  wxBitmap(const wxSize& sz, int depth = wxBITMAP_SCREEN_DEPTH);
  wxBitmap(const char* const * bits);
  wxBitmap(const wxString& filename, wxBitmapType type = wxBITMAP_TYPE_XPM);
  wxBitmap(const wxImage& image, int depth = wxBITMAP_SCREEN_DEPTH, double scale = 1.0);
    // Convert from wxIcon / wxCursor
  wxBitmap(const wxIcon& icon)
  {
 CopyFromIcon(icon);
  }
  explicit wxBitmap(const wxCursor& cursor);
  static void InitStandardHandlers();
  bool Create(int width, int height, int depth = wxBITMAP_SCREEN_DEPTH) override;
  bool Create(const wxSize& sz, int depth = wxBITMAP_SCREEN_DEPTH) override;
  virtual bool Create(int width, int height, const wxDC&);
  int GetHeight() const override;
  int GetWidth() const override;
  int GetDepth() const override;
#  if  wxUSE_IMAGE
  wxImage ConvertToImage() const override;
#  endif
  wxMask* GetMask() const override;
  void SetMask(wxMask* mask) override;
  wxBitmap GetSubBitmap(const wxRect& rect) const override;
  bool SaveFile(const wxString& name, wxBitmapType type, const wxPalette* palette = NULL) const override;
  bool LoadFile(const wxString& name, wxBitmapType type = wxBITMAP_DEFAULT_TYPE) override;
#  if  wxUSE_PALETTE
  wxPalette* GetPalette() const override;
  void SetPalette(const wxPalette& palette) override;
#  endif
    // copies the contents and mask of the given (colour) icon to the bitmap
  bool CopyFromIcon(const wxIcon& icon) override;
    // implementation:
#  if  WXWIN_COMPATIBILITY_3_0
#  endif
  void* GetRawData(wxPixelDataBase& data, int bpp);
  void UngetRawData(wxPixelDataBase& data);
    // these functions are internal and shouldn't be used, they risk to
    // disappear in the future
  bool HasAlpha() const;
  QPixmap* GetHandle() const;
protected:
  wxGDIRefData* CreateGDIRefData() const override;
  wxGDIRefData* CloneGDIRefData(const wxGDIRefData* data) const override;
  wxDECLARE_DYNAMIC_CLASS(wxBitmap);
};
class WXDLLIMPEXP_CORE wxMask : public wxMaskBase
{
public:
  wxMask();
    // Copy constructor
  wxMask(const wxMask& mask);
  wxMask& operator=(const wxMask& mask);
    // Construct a mask from a bitmap and a colour indicating the transparent
    // area
  wxMask(const wxBitmap& bitmap, const wxColour& colour);
    // Construct a mask from a bitmap and a palette index indicating the
    // transparent area
  wxMask(const wxBitmap& bitmap, int paletteIndex);
    // Construct a mask from a mono bitmap (copies the bitmap).
  wxMask(const wxBitmap& bitmap);
  virtual ~wxMask();
  wxBitmap GetBitmap() const;
    // Implementation
  QBitmap* GetHandle() const;
protected:
    // this function is called from Create() to free the existing mask data
  void FreeData() override;
    // by the public wrappers
  bool InitFromColour(const wxBitmap& bitmap, const wxColour& colour) override;
  bool InitFromMonoBitmap(const wxBitmap& bitmap) override;
  wxDECLARE_DYNAMIC_CLASS(wxMask);
private:
  QBitmap* m_qtBitmap;
};
#endif
