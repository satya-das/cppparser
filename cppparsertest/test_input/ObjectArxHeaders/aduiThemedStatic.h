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
// AdUiThemedStatic.h : header file
//
//
// DESCRIPTION:
//
////////////////////////////////////////////////////////////////////////////
// Architectural notes
// 

#if !defined(_ADUITHEMEDSTATIC_H__)
#define _ADUITHEMEDSTATIC_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////////////////////////////////////////////////////////////
/// class CAdUiThemedStatic
///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// AdUiThemedStatic class is a static control that respects the
/// specified theme for when drawing its background and contents.
/// </summary>
class ADUI_PORT CAdUiThemedStatic : public CStatic
{
    DECLARE_DYNAMIC(CAdUiThemedStatic)
public:
    /// <summary>
    /// Default constructor
    /// Creates a AdUiThemedStatic object. The text and
    /// the background colors from the PALETTE_SET_THEME
    /// will be used to draw its contents.
    /// </summary>
    CAdUiThemedStatic();

    /// <summary>
    /// Creates a new AdUiThemedStatic object with theme name 
    /// The text and the background colors from the PALETTE_SET_THEME
    /// will be used to draw its contents.
    /// </summary>
    /// <param name="themeName"> 
    /// Specify themeName string.
    /// </param>
    CAdUiThemedStatic(const CString & themeName);

    /// <summary>
    /// Destructor - Destroys this AdUiThemedStatic object.
    /// </summary>
    virtual ~CAdUiThemedStatic();

    /// <summary> 
    /// Get mThemeName value.
    /// </summary>
    /// <returns> 
    /// Reture mThemeName. 
    /// </returns>
    CString GetThemeName() const;

    /// <summary> 
    /// Set mThemeName value.
    /// </summary>
    /// <param name="themeName"> 
    /// Specify themeName string.
    /// </param>
    /// <returns> 
    /// If success, return true. Otherwise, return false.
    /// </returns>
    bool SetThemeName(const CString & themeName);

    /// <summary> 
    /// Auto scale the bitmap, and associate the new bitmap with the static control.
    /// </summary>
    /// <param name="hBitmap"> 
    /// Specify the original HBITMAP. 
    /// </param>
    /// <returns> 
    /// Return the bitmap that was previously associated with the static control, or NULL.
    /// </returns>
    HBITMAP SetBitmap(HBITMAP hBitmap);

    /// <summary> 
    /// Auto scale the icon, and associate the new icon with the static control.
    /// </summary>
    /// <param name="hIcon"> 
    /// Specify the original icon. 
    /// </param>
    /// <returns> 
    /// Return the icon that was previously associated with the static control, or NULL.
    /// </returns>
    HICON SetIcon(HICON hIcon);

    /// <summary> 
    /// Inherit the PreSubclassWindow,to autoscale the image before show it.
    /// </summary>
    virtual void PreSubclassWindow();

protected:
    /// <summary> 
    /// Initialize the associated bitmap or icon.
    /// </summary>
    void Initialize();

    /// <summary> 
    /// The framework calls this member function when a child control is about to be drawn.
    /// </summary>
    /// <param name="pDC"> 
    /// Contains a pointer to the display context.
    /// </param>
    /// <param name="nCtlColor">
    /// Specify the type of control.
    /// </param>
    /// <returns> 
    /// return a handle to the brush that is to be used for painting the control background.
    /// </returns>
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    CString mThemeName;             // defaults to PALETTE_SET_THEME
    CBrush mBackgroundBrush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ADUITHEMEDSTATIC_H__)

