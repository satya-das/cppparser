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

#ifndef AD_DBDIMDATA_H
#define AD_DBDIMDATA_H

#include "acdb.h"
#include "acarray.h"
#include "dbdim.h"

class AcDbDimData;

typedef AcArray<AcDbDimData*> AcDbDimDataPtrArray;
typedef AcGeVector3d (*DimDataSetValueFuncPtr) (AcDbDimData* pThis,
                                        AcDbEntity* pEnt, 
                                        double newValue,
                                        const AcGeVector3d& offset);
// DimDataSetCustomStringFuncPtr is the callback function signature for AcDbDimData::setCustomStringFunc
typedef AcGeVector3d (*DimDataSetCustomStringFuncPtr) (AcDbDimData* pThis,
                                        AcDbEntity* pEnt, 
                                        const ACHAR* pCustomString,
                                        const AcGeVector3d& offset);
class AcDbDimData
{
public:
    enum DimDataFlags {
        kDimEditable           = 0x1,
        kDimInvisible          = 0x2,
        kDimFocal              = 0x4,
        kDimHideIfValueIsZero  = 0x8,
        kDimEmptyData          = 0x10, //For constraint-unlock support
        kDimResultantLength    = 0x20,
        kDimDeltaLength        = 0x40,
        kDimResultantAngle     = 0x80,
        kDimDeltaAngle         = 0x100,
        kDimRadius             = 0x200,
        kDimCustomValue        = 0x400,
        kDimConstrained        = 0x800,
        kDimCustomString       = 0x1000

    };

    AcDbDimData();
    AcDbDimData(AcDbDimension* pDim, 
                DimDataSetValueFuncPtr setDimFunc = NULL,
                unsigned int bitFlags = 0,
                void* appData = NULL,
                DimDataSetCustomStringFuncPtr setCustomStringFunc = NULL);

    ~AcDbDimData();

    AcDbDimData(const AcDbDimData&);
    AcDbDimData&  operator = (const AcDbDimData&);
    AcDbDimension* dimension() const;
    Acad::ErrorStatus setDimension(AcDbDimension* pDim);
    AcDbObjectId ownerId() const;
    Acad::ErrorStatus setOwnerId(const AcDbObjectId& objId);
    unsigned int bitFlags() const;
    Acad::ErrorStatus setBitFlags(unsigned int flags);
    bool isDimFocal() const;
    Acad::ErrorStatus setDimFocal(bool focal);
    bool isDimEditable() const;
    Acad::ErrorStatus setDimEditable(bool editable);
    bool isDimInvisible() const;
    Acad::ErrorStatus setDimInvisible(bool invisible);
    bool isDimHideIfValueIsZero() const;
    Acad::ErrorStatus setDimHideIfValueIsZero(bool hide);
    void *appData() const;
    Acad::ErrorStatus setAppData(void* appData);
    DimDataSetValueFuncPtr dimValueFunc() const;
    Acad::ErrorStatus setDimValueFunc(DimDataSetValueFuncPtr funcPtr);
    DimDataSetCustomStringFuncPtr customStringFunc() const;
    Acad::ErrorStatus setCustomStringFunc(DimDataSetCustomStringFuncPtr funcPtr);
    bool isDimResultantLength() const;
    Acad::ErrorStatus setDimResultantLength(bool bValue);
    bool isDimDeltaLength() const;
    Acad::ErrorStatus setDimDeltaLength(bool bValue);
    bool isDimResultantAngle() const;
    Acad::ErrorStatus setDimResultantAngle(bool bValue);
    bool isDimDeltaAngle() const;
    Acad::ErrorStatus setDimDeltaAngle(bool bValue);
    bool isDimRadius() const;
    Acad::ErrorStatus setDimRadius(bool bValue);
    bool isCustomDimValue() const;
    Acad::ErrorStatus setCustomDimValue(bool custom);
    bool isConstrained() const;
    Acad::ErrorStatus setConstrain(bool bValue);
    bool isCustomString() const;
    Acad::ErrorStatus setCustomString(bool bValue);

private:
    AcDbDimension*      mpDim;
    AcDbObjectId        mOwnerId;
    unsigned int        mBitFlags;
    DimDataSetValueFuncPtr  mpSetDimValueFunc;
    void*               mpAppData;
    DimDataSetCustomStringFuncPtr  mpSetCustomStringFunc;
};

typedef AcArray<AcDbDimData> AcDbDimDataArray;

inline AcDbDimData::AcDbDimData() : 
    mpDim(NULL), 
    mBitFlags(0),
    mpSetDimValueFunc(NULL),
    mpAppData (NULL),
    mpSetCustomStringFunc(NULL)
{
}

inline AcDbDimData::AcDbDimData(AcDbDimension* pDim, 
                   DimDataSetValueFuncPtr setValueFunc,
                   unsigned int bitFlags,
                   void* appData,
                   DimDataSetCustomStringFuncPtr setCustomStringFunc) :
    mpDim(pDim),
    mBitFlags(bitFlags),
    mpSetDimValueFunc(setValueFunc),
    mpAppData(appData),
    mpSetCustomStringFunc(setCustomStringFunc)
{
}

inline AcDbDimData::AcDbDimData(const AcDbDimData& src)
{
    *this = src;
}

inline AcDbDimData::~AcDbDimData()
{
    if (mpDim) 
        delete mpDim;
}

inline AcDbDimData& AcDbDimData::operator = (const AcDbDimData& src)
{
    if (this == &src)
        return *this;

    mpDim = (AcDbDimension*)src.dimension()->clone();
    mOwnerId = src.ownerId();
    mpSetDimValueFunc = src.dimValueFunc();
    mpSetCustomStringFunc = src.customStringFunc();
    mBitFlags = src.bitFlags();
    mpAppData = src.appData();
    return *this;
}

inline AcDbDimension*
AcDbDimData::dimension() const
{
    return mpDim;
}

inline Acad::ErrorStatus
AcDbDimData::setDimension(AcDbDimension* pDim)
{
    mpDim = pDim;
    return Acad::eOk;
}

inline AcDbObjectId
AcDbDimData::ownerId() const
{
    return mOwnerId;
}

inline Acad::ErrorStatus
AcDbDimData::setOwnerId(const AcDbObjectId& objId)
{
    mOwnerId = objId;
    return Acad::eOk;
}

inline unsigned int 
AcDbDimData::bitFlags() const
{
    return mBitFlags;
}

inline Acad::ErrorStatus
AcDbDimData::setBitFlags(unsigned int flags)
{
    mBitFlags = flags;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimFocal() const
{
    return !!(mBitFlags & kDimFocal);
}

inline Acad::ErrorStatus
AcDbDimData::setDimFocal(bool focal)
{
    if (focal)
        mBitFlags |= kDimFocal;
    else
        mBitFlags &= ~kDimFocal;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimEditable() const
{
    return !!(mBitFlags & kDimEditable);
}

inline Acad::ErrorStatus
AcDbDimData::setDimEditable(bool editable)
{
    if (editable)
        mBitFlags |= kDimEditable;
    else
        mBitFlags &= ~kDimEditable;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimInvisible() const
{
    return !!(mBitFlags & kDimInvisible);
}

inline Acad::ErrorStatus
AcDbDimData::setDimInvisible(bool invisible)
{
    if (invisible)
        mBitFlags |= kDimInvisible;
    else
        mBitFlags &= ~kDimInvisible;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimHideIfValueIsZero() const
{
    return !!(mBitFlags & kDimHideIfValueIsZero);
}

inline Acad::ErrorStatus
AcDbDimData::setDimHideIfValueIsZero(bool hide)
{
    if (hide)
        mBitFlags |= kDimHideIfValueIsZero;
    else
        mBitFlags &= ~kDimHideIfValueIsZero;
    return Acad::eOk;
}

inline bool
AcDbDimData::isDimResultantLength() const
{
    return !!(mBitFlags & kDimResultantLength);
}

inline Acad::ErrorStatus
AcDbDimData::setDimResultantLength(bool bValue)
{
    if (bValue)
        mBitFlags |= kDimResultantLength;
    else
        mBitFlags &= ~kDimResultantLength;
    return Acad::eOk;
}
inline bool
AcDbDimData::isDimDeltaLength() const
{
    return !!(mBitFlags & kDimDeltaLength);
}

inline Acad::ErrorStatus
AcDbDimData::setDimDeltaLength(bool bValue)
{
    if (bValue)
        mBitFlags |= kDimDeltaLength;
    else
        mBitFlags &= ~kDimDeltaLength;
    return Acad::eOk;
}
inline bool
AcDbDimData::isDimResultantAngle() const
{
    return !!(mBitFlags & kDimResultantAngle);
}

inline Acad::ErrorStatus
AcDbDimData::setDimResultantAngle(bool bValue)
{
    if (bValue)
        mBitFlags |= kDimResultantAngle;
    else
        mBitFlags &= ~kDimResultantAngle;
    return Acad::eOk;
}
inline bool
AcDbDimData::isDimDeltaAngle() const
{
    return !!(mBitFlags & kDimDeltaAngle);
}

inline Acad::ErrorStatus
AcDbDimData::setDimDeltaAngle(bool bValue)
{
    if (bValue)
        mBitFlags |= kDimDeltaAngle;
    else
        mBitFlags &= ~kDimDeltaAngle;
    return Acad::eOk;
}
inline bool
AcDbDimData::isDimRadius() const
{
    return !!(mBitFlags & kDimRadius);
}

inline Acad::ErrorStatus
AcDbDimData::setDimRadius(bool bValue)
{
    if (bValue)
        mBitFlags |= kDimRadius;
    else
        mBitFlags &= ~kDimRadius;
    return Acad::eOk;
}

inline bool
AcDbDimData::isCustomDimValue() const
{
    return !!(mBitFlags & kDimCustomValue);
}

inline Acad::ErrorStatus
AcDbDimData::setCustomDimValue(bool custom)
{
    if (custom)
        mBitFlags |= kDimCustomValue;
    else
        mBitFlags &= ~kDimCustomValue;
    return Acad::eOk;
}

inline bool
AcDbDimData::isConstrained() const
{
    return !!(mBitFlags & kDimConstrained);
}

inline Acad::ErrorStatus
AcDbDimData::setConstrain(bool bValue)
{
    if (bValue)
        mBitFlags |= kDimConstrained;
    else
        mBitFlags &= ~kDimConstrained;
    return Acad::eOk;
}

inline bool
AcDbDimData::isCustomString() const
{
    return !!(mBitFlags & kDimCustomString);
}

inline Acad::ErrorStatus
AcDbDimData::setCustomString(bool bValue)
{
    if (bValue)
        mBitFlags |= kDimCustomString;
    else
        mBitFlags &= ~kDimCustomString;
    return Acad::eOk;
}

inline void*
AcDbDimData::appData() const
{
    return mpAppData;
}

inline Acad::ErrorStatus
AcDbDimData::setAppData(void* appData)
{
    mpAppData = appData;
    return Acad::eOk;
}

inline DimDataSetValueFuncPtr
AcDbDimData::dimValueFunc() const
{
    return mpSetDimValueFunc;
}

inline Acad::ErrorStatus
AcDbDimData::setDimValueFunc(DimDataSetValueFuncPtr funcPtr)
{
    mpSetDimValueFunc = funcPtr;
    return Acad::eOk;
}

inline DimDataSetCustomStringFuncPtr
AcDbDimData::customStringFunc() const
{
    return mpSetCustomStringFunc;
}

inline Acad::ErrorStatus
AcDbDimData::setCustomStringFunc(DimDataSetCustomStringFuncPtr funcPtr)
{
    mpSetCustomStringFunc = funcPtr;
    return Acad::eOk;
}

#endif // AD_DBDIMDATA_H



