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
// Name:            AcFdUiFormatList.h
//
// Description:     
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AcFdUi.h"

class AcTcUiSystemInternals;


class ACFDUI_PORT CAcFdUiFormatList : public CAdUiListBox
{
	DECLARE_DYNAMIC(CAcFdUiFormatList)

public:
	CAcFdUiFormatList(void);
	virtual ~CAcFdUiFormatList(void);

    void			SetRootKey              (LPCTSTR pszKey);
    void			SetPersistency			(BOOL bPersist);
    CString			GetFormatType			(void) const;
    BOOL			SetFormatType			(LPCTSTR pszFormatType);
    int				GetCurrentFormat		(CString& sDisplayName, 
											 CString& sFormatString) const;
    BOOL			SetCurrentFormat		(LPCTSTR pszDisplayName, 
											 LPCTSTR pszFormatString);
    BOOL			Refresh					(void);

protected:
    afx_msg int     OnCreate                (LPCREATESTRUCT lpCreateStruct);
    afx_msg void 	OnDestroy				(void);

	DECLARE_MESSAGE_MAP()

protected:
    void            *   mpImpObj;

private:
    friend class AcFdUiSystemInternals;    
};
