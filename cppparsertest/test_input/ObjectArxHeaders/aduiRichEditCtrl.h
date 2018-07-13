//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiRichEditCtrl_h
#define _aduiRichEditCtrl_h
#pragma pack (push, 8)

#pragma once

#include "AdAChar.h"

#ifndef _ADESK_MAC_
#pragma warning(push)
#pragma warning(disable : 4275)

class CAdUiRichEditCtrl;

class CAdUiRichEditThemeModReactor : public CAdUiThemeModifiedReactor  // INTERNAL USE ONLY
{
public:
    CAdUiRichEditThemeModReactor(CAdUiRichEditCtrl* pCtrl);  // INTERNAL USE ONLY

    /// <summary>
    /// Virtual method that receives the theme modification event.
    /// </summary>
    /// <param name="pTheme">
    /// The pointer to the theme that was modified.
    /// </param>
    /// <param name="element">
    /// A index of the theme element that was modified.
    /// </param>
    /// <remarks>
    /// This method is also called when the theme uses the active theme colors
    /// and the active theme is changed.  In that case, element = kUnknownElements
    /// </remarks>        
    virtual void ThemeModified(const CAdUiTheme * pTheme, AdUiThemeElement element);  // INTERNAL USE ONLY

private:
    CAdUiRichEditCtrl * m_pCtrl;
};

///////////////////////////////////////////////////////////
// class CAdUiRichEditCtrl
///////////////////////////////////////////////////////////
/// <summary>
/// This class is the CRichEditCtrl-derived control that
/// can be themed.
/// </summary>
class ADUI_PORT CAdUiRichEditCtrl: public CRichEditCtrl{
    friend class CAdUiRichEditThemeModReactor;  // INTERNAL USE ONLY
    
    DECLARE_DYNAMIC(CAdUiRichEditCtrl)

public:
                CAdUiRichEditCtrl (bool bIsThemed = false);
virtual         ~CAdUiRichEditCtrl ();

// Misc.
protected:

public:
        /// <summary>
        /// Clears the contents and frees memory.
        /// </summary>
        ///
        void clear();

        /// <summary>
        /// Method to set the background and text colors for the rich edit control (overridden 
        /// if themed).
        /// </summary>
        ///
        /// <param name="bgColor">
        /// Background control color.
        /// </param>
        ///
        /// <param name="textColor">
        /// Control text color.
        /// </param>
        ///
        void SetBackgroundAndTextColor(COLORREF bgColor, COLORREF textColor);

        /// <summary>
        /// Utility method that will append a string to content, optionally flagging it for 
        /// bold display.
        /// </summary>
        ///
        /// <param name="str">
        /// The string to append to the existing content.
        /// </param>
        ///
        /// <param name="bBoldFormat">
        /// Set to true if the string will be displayed bold, false otherwise.
        /// </param>
        ///
        void AppendString(CString& str, bool bBoldFormat);

        /// <summary>
        /// Streams the content in.
        /// </summary>
        ///
        void streamIn();

        /// <summary>
        /// Establishes control horizontal (left/right) and vertical (top/bottom) margins.
        /// </summary>
        ///
        /// <param name="horizontal">
        /// Left and right offsets used for margin.
        /// </param>
        ///
        /// <param name="vertical">
        /// Top and bottom offsets used for margin.
        /// </param>
        ///
        void SetMargins(int horizontal, int vertical);

        /// <summary>
        /// Obtain the horizontal (left and right) margin.
        /// </summary>
        ///
        /// <returns>
        /// Returns the horizontal margin for the control (left and right).
        /// </returns>
        ///
        int  GetHorizontalMargin();
    
        /// <summary>
        /// Obtain the vertical (top and bottom) margin.
        /// </summary>
        ///
        /// <returns>
        /// Returns the vertical margin for the control (top and bottom).
        /// </returns>
        ///
        int  GetVerticalMargin();
    
        /// <summary>
        /// Indicates whether this control was marked as themed.
        /// </summary>
        ///
        /// <returns>
        /// Returns true if themed, false otherwise.
        /// </returns>
        ///
        bool IsThemed() { return m_bIsThemed; };

        /// <summary>
        /// Sets the theme flag on the control.
        /// </summary>
        ///
        /// <param name="pTheme">
        /// Set to true if the control can be themed, false otherwise.
        /// </param>
        ///
        void SetIsThemed(bool isThemed);

        /// <summary>
        /// Sets the text title of the control.
        /// </summary>
        ///
        /// <param name="pszTitle">
        /// The text to set for the title.
        /// </param>
        ///
        void SetTitle(LPCTSTR pszTitle) {m_csTitle = pszTitle;} ;

        /// <summary>
        /// Virtual Windows PreTranslateMessage for handling rich edit control messages.
        /// </summary>
        ///
        /// <param name="pMsg">
        /// Pointer to MSG. See Windows documentation for more information.
        /// </param>
        ///
        /// <returns>
        /// Returns TRUE if the message was handled, FALSE otherwise.
        /// </returns>
        /// 
        virtual BOOL PreTranslateMessage(MSG* pMsg);
    
static  bool m_bInitOnce;
    
    // AdUi message handlers
protected:
     CWnd    *m_aduiParent;

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CAdUiRichEditCtrl)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CAdUiEdit)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEnLink(NMHDR *pNMHDR, LRESULT *pResult);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

    /// <summary>
    /// Virtual method that receives the theme modification event.
    /// </summary>
    /// <param name="element">
    /// A index of the theme element that was modified.
    /// </param>
    /// <remarks>
    /// This method is also called when the theme uses the active theme colors
    /// and the active theme is changed.  In that case, element = kUnknownElements
    /// </remarks>        
    virtual void ThemeModified(AdUiThemeElement element);

private:
    CString m_csTitle;
    CString m_csText;
    int     m_horizontalMargin;
    int     m_verticalMargin;
    bool    m_bIsThemed;
    CAdUiRichEditThemeModReactor    * m_pThemeModReactor;
    CAdUiTheme * m_pTheme;
    COLORREF mBackgroundColor;
    COLORREF mTextColor;
};


#pragma warning(pop)

#endif //_ADESK_MAC_
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif //_aduiRichEditCtrl_h

/////////////////////////////////////////////////////////////////////////////
