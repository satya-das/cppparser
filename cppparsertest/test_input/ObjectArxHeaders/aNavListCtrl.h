//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _ANavListCtrl_h
#define _ANavListCtrl_h

#pragma once


class  CNavListCtrl;

class CNavDropSource : public COleDropSource
{
public:
    CNavDropSource();       

    CNavListCtrl* m_pListCtrl;

    // Overrides
    SCODE GiveFeedback(DROPEFFECT dropEffect);
};


class ANAV_PORT CNavListCtrl : public CAdUiListCtrl {
public:
    CNavListCtrl ();

// ClassWizard-controlled
public:
    //{{AFX_VIRTUAL(CNavListCtrl)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CNavListCtrl)
    afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
    //}}AFX_MSG
    afx_msg LRESULT OnHandleDrag(UINT_PTR pDataSource, LPARAM nSelectedItem);
    DECLARE_MESSAGE_MAP()

    CImageList* m_pDragImage;
    CNavDropSource m_dropSource;

};

#endif // _ANavListCtrl_h
