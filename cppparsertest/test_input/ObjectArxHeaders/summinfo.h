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
//
//  DESCRIPTION:  Header for Summary Info API
//

#ifndef _SUMMINFO_H_
#define _SUMMINFO_H_

#include "rxobject.h"
#include "AcString.h"

#pragma pack (push, 8)

// Note that this class is an AcRxObject, not an AcDbObject.
// Rather than doing open() and close() calls on it, we do get
// and put operations on a database, passing instances of this
// class as values.
//
class ADESK_NO_VTABLE AcDbDatabaseSummaryInfo : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDatabaseSummaryInfo);

    virtual Acad::ErrorStatus getTitle(AcString & title) const = 0;
    virtual Acad::ErrorStatus setTitle(const ACHAR* title) = 0;

    virtual Acad::ErrorStatus getSubject(AcString & subject) const = 0;
    virtual Acad::ErrorStatus setSubject(const ACHAR* subject) = 0;

    virtual Acad::ErrorStatus getAuthor(AcString & author) const = 0;
    virtual Acad::ErrorStatus setAuthor(const ACHAR* author) = 0;

    virtual Acad::ErrorStatus getKeywords(AcString & keywordlist) const = 0;
    virtual Acad::ErrorStatus setKeywords(const ACHAR* keywordlist) = 0;

    virtual Acad::ErrorStatus getComments(AcString & comments) const = 0;
    virtual Acad::ErrorStatus setComments(const ACHAR* comments) = 0;

    virtual Acad::ErrorStatus getLastSavedBy(AcString & lastSavedBy) const = 0;
    virtual Acad::ErrorStatus setLastSavedBy(const ACHAR* lastSavedBy) = 0;

    virtual Acad::ErrorStatus getRevisionNumber(AcString & revisionNumber) const = 0;
    virtual Acad::ErrorStatus setRevisionNumber(const ACHAR* revisionNumber) = 0;

    virtual Acad::ErrorStatus getHyperlinkBase(AcString & HyperlinkBase) const = 0;
    virtual Acad::ErrorStatus setHyperlinkBase(const ACHAR* HyperlinkBase) = 0;

    virtual int numCustomInfo() const = 0;

    virtual Acad::ErrorStatus addCustomSummaryInfo(const ACHAR* key, const ACHAR* value ) = 0;

    virtual Acad::ErrorStatus deleteCustomSummaryInfo(int index) = 0;
    virtual Acad::ErrorStatus deleteCustomSummaryInfo(const ACHAR* key) = 0;

    virtual Acad::ErrorStatus getCustomSummaryInfo(int index, AcString & key,
                                                   AcString & value ) const = 0;

    virtual Acad::ErrorStatus setCustomSummaryInfo (int index, const ACHAR* key,
                               const ACHAR *value ) = 0;

    virtual Acad::ErrorStatus getCustomSummaryInfo(const ACHAR *customInfoKey,
                                                   AcString & value ) const = 0;

    virtual Acad::ErrorStatus setCustomSummaryInfo (const ACHAR *customInfoKey,
                               const ACHAR *value ) = 0;

    // Note: database() may become obsolete in a future release.
    //
    virtual AcDbDatabase* database() const = 0; 

    // These overloads are deprecated and will be removed in a future release.
    // Please use the overloads taking AcString & args instead.
    //
    virtual Acad::ErrorStatus getTitle(ACHAR*& title) const final;
    virtual Acad::ErrorStatus getSubject(ACHAR*& subject) const final;
    virtual Acad::ErrorStatus getAuthor(ACHAR*& author) const final;
    virtual Acad::ErrorStatus getKeywords(ACHAR*& keywordlist) const final;
    virtual Acad::ErrorStatus getComments(ACHAR*& comments) const final;
    virtual Acad::ErrorStatus getLastSavedBy(ACHAR*& lastSavedBy) const final;
    virtual Acad::ErrorStatus getRevisionNumber(ACHAR*& revisionNumber) const final;
    virtual Acad::ErrorStatus getHyperlinkBase(ACHAR*& HyperlinkBase) const final;
    virtual Acad::ErrorStatus getCustomSummaryInfo(int index, ACHAR*& key,
                                                   ACHAR *& value ) const final;
    virtual Acad::ErrorStatus getCustomSummaryInfo(const ACHAR *customInfoKey,
                                                   ACHAR *& value ) const final;

    virtual ~AcDbDatabaseSummaryInfo() {};
  protected:
    AcDbDatabaseSummaryInfo();
  private:
    // Helper method for shimming legacy methods to new ones. Will be
    // removed along with old deprecated methods.
    typedef Acad::ErrorStatus (AcDbDatabaseSummaryInfo::*GetPropAcString)(AcString &) const;
    Acad::ErrorStatus getACharString(GetPropAcString pMeth, ACHAR * & rpBuf) const;
};

/// -- Begin Deprecated Functions --
//
Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);

inline Acad::ErrorStatus
        AcDbDatabaseSummaryInfo::getACharString(GetPropAcString pMeth, ACHAR * & rpBuf) const
{
    rpBuf = nullptr;
    AcString sTemp;
    const Acad::ErrorStatus es = (this->*pMeth)(sTemp);
    if (es == Acad::eOk)
        ::acutNewString(sTemp.constPtr(), rpBuf);
    return es;
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getTitle(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getTitle, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getSubject(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getSubject, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getAuthor(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getAuthor, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getKeywords(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getKeywords, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getComments(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getComments, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getLastSavedBy(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getLastSavedBy, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getRevisionNumber(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getRevisionNumber, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getHyperlinkBase(ACHAR*& title) const
{
    return this->getACharString(&AcDbDatabaseSummaryInfo::getHyperlinkBase, title);
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getCustomSummaryInfo(int index,
                                        ACHAR*& key, ACHAR *& value ) const
{
    AcString sKey, sValue;
    const Acad::ErrorStatus es = this->getCustomSummaryInfo(index, sKey, sValue);
    if (es == Acad::eOk) {
        ::acutNewString(sKey.constPtr(), key);
        ::acutNewString(sValue.constPtr(), value);
    }
    else
        key = value = nullptr;
    return es;
}

inline Acad::ErrorStatus AcDbDatabaseSummaryInfo::getCustomSummaryInfo(const ACHAR *customInfoKey,
                                                   ACHAR *& value ) const
{
    AcString sValue;
    const Acad::ErrorStatus es = this->getCustomSummaryInfo(customInfoKey, sValue);
    if (es == Acad::eOk)
        ::acutNewString(sValue.constPtr(), value);
    else
        value = nullptr;
    return es;
}

//
/// -- End Deprecated Functions --

ACDBCORE2D_PORT Acad::ErrorStatus acdbGetSummaryInfo(
                                 AcDbDatabase* pDb, 
                                 AcDbDatabaseSummaryInfo*& pInfo);

ACDBCORE2D_PORT Acad::ErrorStatus acdbPutSummaryInfo(
                                const AcDbDatabaseSummaryInfo* pInfo,
                                AcDbDatabase *pDb);


ACDBCORE2D_PORT Acad::ErrorStatus acdbValidateCustomSummaryInfoKey(
                                const wchar_t* key, 
                                const AcDbDatabaseSummaryInfo* pInfo = NULL);

// Note: this acdbPutSummaryInfo() overload which does not take a
// database argument may become obsolete in a future release.
//
inline Acad::ErrorStatus acdbPutSummaryInfo(
                                const AcDbDatabaseSummaryInfo* pInfo)
{
    return ::acdbPutSummaryInfo(pInfo, pInfo->database());
}


//
class ADESK_NO_VTABLE AcDbSummaryInfoReactor {
public:
    virtual void summaryInfoHasChanged(
                     const AcDbDatabase* ,
                     const AcDbDatabaseSummaryInfo* ) {
    };
    virtual ~AcDbSummaryInfoReactor() {};
};

// Original code doesn't include double quotation mark in the invalid characters, which might 
// be a bug. We decide to include " here, but need to check if this will trigger any
// compatibility problem with existing drawings.
#define ACDB_SUMMINFO_INVALID_CHARACTERS   L"<>/\\\":;?*|,=`"

class ADESK_NO_VTABLE AcDbSummaryInfoManager {
public:
    virtual void  addReactor(AcDbSummaryInfoReactor* pReact) = 0;
    virtual void  removeReactor(AcDbSummaryInfoReactor* pReact) = 0;
};

// Stand-alone function to return the manager
//

ACDBCORE2D_PORT AcDbSummaryInfoManager* acdbSummaryInfoManager();

#pragma pack (pop)
#endif // _SUMMINFO_H_


