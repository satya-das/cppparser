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
// AdUiToolBarCtrl.h : header file
//
//
// DESCRIPTION:
//
////////////////////////////////////////////////////////////////////////////
// Architectural notes
// 

#if !defined(_ADUITOOLBARCTRL_H__)
#define _ADUITOOLBARCTRL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ADUI_TBSTYLE_AUTOSTRETCH 0x00080000

///////////////////////////////////////////////////////////////////////////////
/// class CAdUiToolBarCtrl
///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// CAdUiToolBarCtrl class is a toolbar control that supports automatic scaling when button images are added.
/// </summary>
/// <remarks>
/// For automatic scaling to work, the control must have been created with the <c>ADUI_TBSTYLE_AUTOSTRETCH</c> style.
/// </remarks>
class ADUI_PORT CAdUiToolBarCtrl : public CToolBarCtrl
{
    DECLARE_DYNAMIC(CAdUiToolBarCtrl)
public:
    /// <summary>
    /// Constructs a CAdUiToolBarCtrl object.
    /// </summary>
    CAdUiToolBarCtrl();

    /// <summary>
    /// Destroys this CAdUiToolBarCtrl object.
    /// </summary>
    virtual ~CAdUiToolBarCtrl();

    /// <summary>
    /// Adds one or more button images to the list of button images stored in the toolbar control.
    /// </summary>
    /// <param name="nNumButtons">Number of button images in the bitmap.</param>
    /// <param name="nBitmapID">Resource identifier of the bitmap that contains the button image or images to add.</param>
    /// <returns>Zero-based index of the first new image if successful; otherwise -1.</returns>
    int AddBitmap(int nNumButtons, UINT nBitmapID);

    /// <summary>
    /// Adds one or more button images to the list of button images stored in the toolbar control.
    /// </summary>
    /// <param name="nNumButtons">Number of button images in the bitmap.</param>
    /// <param name="pBitmap">Pointer to the CBitmap object that contains the button image or images to add.</param>
    /// <returns>Zero-based index of the first new image if successful; otherwise -1.</returns>
    int AddBitmap(int nNumButtons, CBitmap* pBitmap);

protected:
    //{{AFX_MSG
    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    CBitmap *m_pBmp;
    void UpdateBitmap(const CBitmap& bmp);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_ADUITOOLBARCTRL_H__)

