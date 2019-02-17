//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
//   Declarations for various image classes:
//
//  CAdUiImage
//  CAdUiImageResource
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiImage_h
#define _aduiImage_h

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef _WINDOWS_           // From windows.h, AFX and MFC don't mix
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extension
#endif

// GDIPlus will not compile with our MACRO for "new", therefore we are saving off
// our macro while we compile GDIPlus, then set it back.
#pragma push_macro("new")
#undef new
#include <minmax.h>
#include <gdiplus.h>
#undef min
#undef max
#pragma pop_macro("new")

#include <WinDef.h>     //For definitions of HINSTANCE...etc if not already included
#include "aduiTheme.h"

#define ICON_16     16
#define ICON_32     32

///////////////////////////////////////////////////////////////////////////////
/// class CAdUiImage
///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Image class provides dark and light theme support to get dark or light theme
/// image resource. 
/// </summary>
class ADUI_PORT CAdUiImage
{
public:
    
    /// <summary> 
    /// Create a new CAdUiImage object.
    /// </summary>
    /// <param name="bIsThemed"> 
    /// If true, dark/light theme support for image resource. 
    /// </param>
    CAdUiImage(bool bIsThemed = false);

    /// <summary> 
    /// Create a new CAdUiImage object with resource file name.
    /// </summary>
    /// <param name="pFile"> 
    /// Image resource file name. 
    /// </param>
    /// <param name="bIsThemed"> 
    /// If true, dark/light theme support for image resource. 
    /// </param>
    CAdUiImage(LPCWSTR pFile, bool bIsThemed = false);
    
    /// <summary> 
    /// Create a new CAdUiImage object from bitmap handle.
    /// </summary>
    /// <param name="hbmp"> 
    /// Bitmap handle for creating new CAdUiImage class
    /// </param>
    /// <param name="format"> 
    /// Specify the image format. 
    /// </param>
    CAdUiImage(HBITMAP hbmp, Gdiplus::PixelFormat format);
    
    /// <summary>
    /// Destroys this CAdUiImage object.
    /// </summary>
    virtual ~CAdUiImage();

    /// <summary> 
    /// Set CAdUiImage resource empty.
    /// </summary>
    virtual void Empty();

    /// <summary> 
    /// Reload image resource. 
    /// If this class is themed CAdUiImage class, resource will be reloaded based on drak/light theme.
    /// </summary>
    virtual bool Reload();

    /// <summary> 
    /// Load image resource by resource file name. 
    /// </summary>
    /// <param name="pFile"> 
    /// Specify the resource file name.
    /// </param>
    /// <returns> 
    /// Reture true if load resource success. Otherwise, return false.
    /// </returns>
    bool Load(LPCWSTR pFile);

    /// <summary> 
    /// Get whether this object is themed.
    /// </summary>
    /// <returns> 
    /// whether this object is themed.
    /// </returns>
    bool IsThemed()                     { return m_bIsThemed; }

    /// <summary> 
    /// Set this object IsThemed flag.
    /// </summary>
    /// <param name="bIsThemed"> 
    /// If true, dark/light theme support for image resource.
    /// </param>
    void SetIsThemed(bool bIsThemed)    { m_bIsThemed = bIsThemed; }

    /// <summary> 
    /// Set CAdUiTheme that is used as current theme. 
    /// </summary>
    /// <param name="theme"> 
    /// Specify the new CAdUiTheme.
    /// </param>
    void SetTheme(const CAdUiTheme * theme); 

    /// <summary> 
    /// Get image width. 
    /// </summary>
    /// <returns> 
    /// Image width.
    /// </returns>
    unsigned int GetWidth() const;
    
    /// <summary> 
    /// Get iamge height.
    /// </summary>
    /// <returns> 
    /// Image height.
    /// </returns>
    unsigned int GetHeight() const;
    
    /// <summary> 
    /// Get Gdiplus::Bitmap pointer.
    /// </summary>
    /// <returns> 
    /// Gdiplus::Bitmap pointer.
    /// </returns>
    Gdiplus::Bitmap* GetBitmap() const   { return m_pBitmap; }

    /// <summary> 
    /// Set Gdiplus::Bitmap pointer.
    /// </summary>
    /// <param name="theme"> 
    /// Specify the new Gdiplus::Bitmap.
    /// </param>
    void SetBitmap(Gdiplus::Bitmap* pBitmap);

    /// <summary> 
    /// Draw current image resource. 
    /// </summary>
    /// <param name="pDC"> 
    /// Specify DC that used to draw image resource.
    /// </param>
    /// <param name="x"> 
    /// Start point x value.
    /// </param>
    /// <param name="y"> 
    /// Start point y value.
    /// </param>
    /// <param name="isDisabled"> 
    /// If true, draw image without colour.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool DrawImage(CDC* pDC, int x, int y, bool isDisabled = false);
    
    /// <summary> 
    /// Draw current image resource. 
    /// </summary>
    /// <param name="pDC"> 
    /// Specify DC that used to draw image resource.
    /// </param>
    /// <param name="x"> 
    /// Start point x value.
    /// </param>
    /// <param name="y"> 
    /// Start point y value.
    /// </param>
    /// <param name="width"> 
    /// Specify the image drawing width.
    /// </param>
    /// <param name="height"> 
    /// Specify the image drawing height.
    /// </param>
    /// <param name="isDisabled"> 
    /// If true, draw image without colour.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool DrawImage(CDC* pDC, int x, int y, int width, int height, bool isDisabled = false);
    
    /// <summary> 
    /// Draw current image resource. 
    /// </summary>
    /// <param name="pDC"> 
    /// Specify DC that used to draw image resource.
    /// </param>
    /// <param name="x"> 
    /// Start point x value.
    /// </param>
    /// <param name="y"> 
    /// Start point y value.
    /// </param>
    /// <param name="srcx"> 
    /// Integer that specifies the x-coordinate of the upper-left corner of the portion of the source image to be drawn.
    /// </param>
    /// <param name="srcy"> 
    /// Integer that specifies the y-coordinate of the upper-left corner of the portion of the source image to be drawn.
    /// </param>
    /// <param name="srcwidth"> 
    /// Integer that specifies the width of the portion of the source image to be drawn.
    /// </param>
    /// <param name="srcheight"> 
    /// Integer that specifies the height of the portion of the source image to be drawn.
    /// </param>
    /// <param name="isDisabled"> 
    /// If true, draw image without colour.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool DrawImage(CDC* pDC, int x, int y, int srcx, int srcy, int srcwidth, int srcheight, bool isDisabled = false);

    /// <summary> 
    /// Draw current image resource. 
    /// </summary>
    /// <param name="pDC"> 
    /// Specify DC that used to draw image resource.
    /// </param>
    /// <param name="x"> 
    /// Start point x value.
    /// </param>
    /// <param name="y"> 
    /// Start point y value.
    /// </param>
    /// <param name="width"> 
    /// Specify the image drawing width.
    /// </param>
    /// <param name="height"> 
    /// Specify the image drawing height.
    /// </param>
    /// <param name="srcx"> 
    /// Integer that specifies the x-coordinate of the upper-left corner of the portion of the source image to be drawn.
    /// </param>
    /// <param name="srcy"> 
    /// Integer that specifies the y-coordinate of the upper-left corner of the portion of the source image to be drawn.
    /// </param>
    /// <param name="srcwidth"> 
    /// Integer that specifies the width of the portion of the source image to be drawn.
    /// </param>
    /// <param name="srcheight"> 
    /// Integer that specifies the height of the portion of the source image to be drawn.
    /// </param>
    /// <param name="isDisabled"> 
    /// If true, draw image without colour.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool DrawImage(CDC* pDC, int x, int y, int width, int height, int srcx, int srcy, int srcwidth, int srcheight, bool isDisabled = false);

    /// <summary> 
    /// Get themed file name based on the orginal file name.
    /// </summary>
    /// <param name="pName"> 
    /// Specify the orginal file name.
    /// </param>
    /// <param name="pTheme"> 
    /// Specify the theme that is used to decide theme. 
    /// </param>
    /// <returns> 
    /// Reture themed file name based on the orginal file name. 
    /// </returns>
    static CString GetThemedFileName(LPCTSTR pName, const CAdUiTheme * pTheme = NULL);

protected:
    Gdiplus::Bitmap* m_pBitmap;
    bool m_bIsThemed;
    const CAdUiTheme* m_pTheme;
    CString m_name;

    /// <summary> 
    /// Return true, if the theme is dark.  
    /// </summary>
    /// <returns> 
    /// Return true, if the theme is dark.
    /// </returns>
    bool CAdUiImage::IsThemeDark() const;

    /// <summary> 
    /// Return true, if the current palette theme is dark.  
    /// </summary>
    /// <returns> 
    /// Return true, if the current palette theme is dark.
    /// </returns>
    static bool IsCurrentPaletteThemeDark();

private:
    void commonCtr(bool bIsThemed);
    void clear();
    void drawImage(CDC* pDC, int x, int y, int width, int height, int srcx, int srcy, int srcwidth, int srcheight, bool isDisabled);

    static unsigned int         g_instanceCount;
    static Gdiplus::GdiplusStartupInput  g_gdiplusStartupInput;
    static ULONG_PTR            g_gdiplusToken;

    // not allowed
    CAdUiImage(const CAdUiImage & image);
    CAdUiImage& operator=(const CAdUiImage & image);
};

///////////////////////////////////////////////////////////////////////////////
/// class CAdUiImageResource
///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Image class provides dark and light theme support to get dark or light theme
/// resource from resource ID string.
/// </summary>
class ADUI_PORT CAdUiImageResource : public CAdUiImage
{
protected:
    HGLOBAL m_hBuffer;
    UINT m_lightId;
    UINT m_darkId;
    LPCTSTR m_pType;
    CString m_strType;
    HMODULE m_hInst;

public:
    /// <summary> 
    /// Create a new object without resource.
    /// </summary>
    CAdUiImageResource();
    
    /// <summary> 
    /// Create a new CAdUiImageResource object.
    /// </summary>
    /// <param name="bIsThemed"> 
    /// If true, dark/light theme support for image resource. 
    /// </param>
    CAdUiImageResource(bool bIsThemed);

    /// <summary> 
    /// Create a new CAdUiImageResource object by resource ID string.
    /// </summary>
    /// <param name="pName"> 
    /// Specify the resource ID string. 
    /// </param>
    /// <param name="pType"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    /// <param name="bIsThemed"> 
    /// If true, dark/light theme support for image resource. 
    /// </param>
    CAdUiImageResource(LPCTSTR pName, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL, bool bIsThemed = false);

    /// <summary> 
    /// Create a new CAdUiImageResource object by resource ID.
    /// </summary>
    /// <param name="id"> 
    /// Specify the resource ID.
    /// </param>
    /// <param name="pType"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    CAdUiImageResource(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);

    /// <summary> 
    /// Create a new CAdUiImageResource object by resource ID.
    /// </summary>
    /// <param name="id"> 
    /// Specify the resource ID.
    /// </param>
    /// <param name="type"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    CAdUiImageResource(UINT id, UINT type, HMODULE hInst = NULL);

    /// <summary> 
    /// Create a new CAdUiImageResource object.
    /// </summary>
    /// <param name="lightId"> 
    /// Specify the light theme resource ID.
    /// </param>
    /// <param name="darkId"> 
    /// Specify the dark theme resource ID.
    /// </param>
    /// <param name="pType"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    CAdUiImageResource(UINT lightId, UINT darkId, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);

    /// <summary> 
    /// Create a new CAdUiImageResource object.
    /// </summary>
    /// <param name="lightId"> 
    /// Specify the light theme resource ID.
    /// </param>
    /// <param name="darkId"> 
    /// Specify the dark theme resource ID.
    /// </param>
    /// <param name="type"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    CAdUiImageResource(UINT lightId, UINT darkId, UINT type, HMODULE hInst = NULL);
    
    /// <summary>
    /// Destroys this CAdUiImageResource object.
    /// </summary>
    virtual ~CAdUiImageResource();

    /// <summary> 
    /// Set CAdUiImage resource empty.
    /// </summary>
    virtual void Empty();
    
    /// <summary> 
    /// Reload image resource. 
    /// If this class is themed CAdUiImage class, resource will be reloaded based on drak/light theme.
    /// </summary>
    virtual bool Reload();

    /// <summary> 
    /// Load resource by resource ID string.
    /// </summary>
    /// <param name="pName"> 
    /// Specify resource ID string.
    /// </param>
    /// <param name="pType"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool Load(LPCTSTR pName, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);

    /// <summary> 
    /// Load resource by resource ID.
    /// </summary>
    /// <param name="id"> 
    /// Specify resource ID.
    /// </param>
    /// <param name="pType"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool Load(UINT id, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);

    /// <summary> 
    /// Load resource by resource ID.
    /// </summary>
    /// <param name="id"> 
    /// Specify resource ID.
    /// </param>
    /// <param name="type"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool Load(UINT id, UINT type, HMODULE hInst = NULL);

    /// <summary> 
    /// Load resource by resource ID.
    /// </summary>
    /// <param name="lightId"> 
    /// Specify the light theme resource ID.
    /// </param>
    /// <param name="darkId"> 
    /// Specify the dark theme resource ID.
    /// </param>
    /// <param name="pType"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool Load(UINT lightId, UINT darkId, LPCTSTR pType = RT_RCDATA, HMODULE hInst = NULL);

    /// <summary> 
    /// Load resource by resource ID.
    /// </summary>
    /// <param name="lightId"> 
    /// Specify the light theme resource ID.
    /// </param>
    /// <param name="darkId"> 
    /// Specify the dark theme resource ID.
    /// </param>
    /// <param name="type"> 
    /// Specify the type of resource data.
    /// </param>
    /// <param name="hInst"> 
    /// Specify resource module handle.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>>
    bool Load(UINT lightId, UINT darkId, UINT type, HMODULE hInst = NULL);

    /// <summary> 
    /// Get themed file name based on the orginal file name.
    /// </summary>
    /// <param name="pName"> 
    /// Specify the orginal file name.
    /// </param>
    /// <param name="pTheme"> 
    /// Specify the theme that is used to decide theme. 
    /// </param>
    /// <returns> 
    /// Reture themed file name based on the orginal file name. 
    /// </returns>
    static CString GetThemedResourceName(LPCTSTR pName, const CAdUiTheme * pTheme = NULL);

private:
    bool loadIcon(LPCTSTR pName, HMODULE hInst = NULL);
    bool loadResource(LPCTSTR pName, LPCTSTR pType, HMODULE hInst);
    bool isPredefinedResourceType(LPCTSTR pType);
    bool isValidPredefinedResourceType(LPCTSTR pType);
    void saveType(LPCTSTR pType);

private:

    void clear();

    // not allowed
    CAdUiImageResource(const CAdUiImageResource & image);
    CAdUiImageResource& operator=(const CAdUiImageResource & image);
};

#endif  // _aduiImage_h
