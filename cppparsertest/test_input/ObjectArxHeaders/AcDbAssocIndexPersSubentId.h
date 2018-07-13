//////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// AcDbAssocIndexPersSubentId and AcDbAssocExternalIndexPersSubentId
// concrete derived AcDbAssocPersSubentId classes.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "dbsubeid.h"
#include "AcDbAssocPersSubentId.h"
#pragma pack (push, 8)


/// <summary><para>
/// Concrete derived AcDbAssocPersSubentId class that keeps a simple unsigned 
/// integer index that can be interpreted in any way the client (i.e.  a concrete
/// AcDbAssocPersSubentIdPE protocol extension) wants to. 
/// </para><para>
/// This class is used as it is but also as base class for AcDbAssocAsmBasedEntityPersSubentId 
/// derived class and maybe more derived classes in the future. 
/// </para></summary>
///
class ACDBCORE2D_PORT AcDbAssocIndexPersSubentId : public AcDbAssocPersSubentId
{
#ifdef __GNUC__
    typedef AcDbAssocPersSubentId __super;
    static_assert((std::is_same<__super, AcDbAssocPersSubentId>::value), "Incorrect __super class");
#endif

public:
	ACRX_DECLARE_MEMBERS(AcDbAssocIndexPersSubentId);

    explicit AcDbAssocIndexPersSubentId(AcDb::SubentType subentType = AcDb::kNullSubentType, unsigned int index = 0);

    bool operator ==(const AcDbAssocIndexPersSubentId& other) const
    {
        return mSubentType == other.mSubentType && mIndex == other.mIndex;
    }

    bool operator <(const AcDbAssocIndexPersSubentId& other) const
    {
        return mSubentType != other.mSubentType ? mSubentType < other.mSubentType : mIndex < other.mIndex;
    }

    virtual AcDb::SubentType subentType(const AcDbEntity*, AcDbDatabase*) const override { return mSubentType; }

    virtual bool isNull() const override { return mSubentType == AcDb::kNullSubentType; }

    /// <summary><para>
    /// Writes the raw data of this class. It does not call the parent class
    /// AcDbAssocPersSubentId::dwg/dxfOutFields() that would write the class name.
    /// </para><para>
    /// This method must be used when serializing an AcDbAssocIndexPersSubentId
    /// that is an explicit data member, not a AcDbAssocPersSubentId* data member.
    /// The regular dwg/dxfInFields() can be used to read the data back.
    /// </para></summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::eOk. </returns>
    ///
    virtual Acad::ErrorStatus dwgOutFieldsData(AcDbDwgFiler* pFiler) const;

    /// <summary><para>
    /// Writes the raw data of this class. It does not call the parent class
    /// AcDbAssocPersSubentId::dwg/dxfOutFields() that would write the class name.
    /// </para><para>
    /// This method must be used when serializing an AcDbAssocIndexPersSubentId
    /// that is an explicit data member, not a AcDbAssocPersSubentId* data member.
    /// The regular dwg/dxfInFields() can be used to read the data back.
    /// </para></summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::eOk. </returns>
    ///
    virtual Acad::ErrorStatus dxfOutFieldsData(AcDbDxfFiler* pFiler) const;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

    /// <summary> The standard filing protocol. </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;

    // New methods

    unsigned int index() const { return mIndex; }

    void setSubentType(AcDb::SubentType subentType) { mSubentType = subentType; }
    void setIndex     (unsigned int newIndex)       { mIndex      = newIndex;   }

private:
    // For round-tripping via AcDbAssocSimplePersSubentId, encoding the
    // actual class type in subentType(), because it may only be in the range
    // of 0..3, so we have enough bits available to encode additional info.
    // Calls the virtual roundTripOffset() method to get the offset
    //
    int encodeActualClassInSubentType() const;

    static const int kRoundTripOffset = 1000000; // For this AcDbAssocIndexPersSubentId class
    virtual int roundTripOffset() const { return kRoundTripOffset; }

    friend void roundTripReadViaAcDbAssocSimplePersSubentId(AcDbAssocPersSubentId*&);

protected:
    AcDb::SubentType mSubentType;
    unsigned int     mIndex;

}; // class AcDbAssocIndexPersSubentId


/// <summary><para>
/// AcDbAssocPersSubentId returned by AcDAssocExternalPersSubentIdManager and 
/// AcDAssocExternalPersSubentIdHolder. It is identical to its base AcDbAssocIndexPersSubentId 
/// class but is of a different class, so that its purpose can be found-out by
/// checking the class. 
/// </para><para>
/// It is similar to AcDbAssocAsmBasedEntityPersSubentId that also is of a different
/// class because pers id collection and remapping needs to know which AcDbAssocPersSubentIds
/// are related to AcDbAssocPersSubentManager.
/// </para></summary>
///
class ACDBCORE2D_PORT AcDbAssocExternalIndexPersSubentId : public AcDbAssocIndexPersSubentId
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocExternalIndexPersSubentId);

    explicit AcDbAssocExternalIndexPersSubentId(AcDb::SubentType subentType = AcDb::kNullSubentType, unsigned int index = 0) 
      : AcDbAssocIndexPersSubentId(subentType, index) {}

private:
    // For round-tripping to older dwg file format versions via AcDbAssocSimplePersSubentId
    //
    static const int kRoundTripOffset = 2000000; // For this AcDbAssocExternalIndexPersSubentId class
    virtual int roundTripOffset() const override { return kRoundTripOffset; }

    friend void roundTripReadViaAcDbAssocSimplePersSubentId(AcDbAssocPersSubentId*&);

}; // class AcDbAssocExternalIndexPersSubentId

/// <summary>
/// Represents the persistent subentity id by an AcDbObjectId and a (persistent) 
/// unsigned integer index related to that AcDbObject. The index can be interpreted 
/// in any way the client (i.e.  a concrete AcDbAssocPersSubentIdPE protocol extension) 
/// wants to. 
/// </summary>
/// <remarks>
/// </remarks>
///
class ACDBCORE2D_PORT AcDbAssocObjectAndIndexPersSubentId : public AcDbAssocIndexPersSubentId
{
#ifdef __GNUC__
    typedef AcDbAssocIndexPersSubentId __super;
    static_assert((std::is_same<__super, AcDbAssocIndexPersSubentId>::value), "Incorrect __super class");
#endif

public:
	ACRX_DECLARE_MEMBERS(AcDbAssocObjectAndIndexPersSubentId);

    AcDbAssocObjectAndIndexPersSubentId() {}
    AcDbAssocObjectAndIndexPersSubentId(const AcDbObjectId& objId, AcDb::SubentType subentType, unsigned int index);

    bool operator ==(const AcDbAssocObjectAndIndexPersSubentId& other) const;
    bool operator  <(const AcDbAssocObjectAndIndexPersSubentId& other) const;

    AcDbObjectId objectId() const { return mObjectId; }

    void setObjectId(const AcDbObjectId& objId) { mObjectId = objId; }

    virtual Acad::ErrorStatus dwgOutFieldsData(AcDbDwgFiler*) const ADESK_OVERRIDE;
    virtual Acad::ErrorStatus dxfOutFieldsData(AcDbDxfFiler*) const ADESK_OVERRIDE;

    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const ADESK_OVERRIDE;
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* ) ADESK_OVERRIDE;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const ADESK_OVERRIDE;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* ) ADESK_OVERRIDE;

private:
    AcDbObjectId mObjectId;

}; // class AcDbAssocObjectAndIndexPersSubentId

#pragma pack (pop)


