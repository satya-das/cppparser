//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//----- Defines
//-----     #pragma warning(disable: 4786)
//----- in your precompiled header to get rid of this warning
//-----------------------------------------------------------------------------
#include "acdocman.h"
#include <map>

//-----------------------------------------------------------------------------
template <class T> class AcApDataManager : public AcApDocManagerReactor {

public:
	AcApDataManager () {
		acDocManager->addReactor (this) ;
	}
	~AcApDataManager () {
		if ( acDocManager != NULL )
			acDocManager->removeReactor (this) ;
	}
	virtual void documentToBeDestroyed (AcApDocument *pDoc) {
		m_dataMap.erase (pDoc) ;
	}

	T &docData (AcApDocument *pDoc) {
		if ( m_dataMap.find(pDoc) == m_dataMap.end () )
			return (m_dataMap[pDoc]) ;
		return ((*(m_dataMap.find(pDoc))).second) ;
	}
	T &docData () {
		return (docData (acDocManager->curDocument ())) ;
	}

private:
	std::map<AcApDocument *, T> m_dataMap ;
} ;
