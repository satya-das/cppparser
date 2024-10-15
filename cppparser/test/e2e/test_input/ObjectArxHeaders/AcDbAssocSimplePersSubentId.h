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
// CREATED BY: Jiri Kripac                                 March 2007
//
// DESCRIPTION:
//
// AcDbAssocSimplePersSubentId concrete derived class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acarray.h"
#include "dbsubeid.h"
#include "AcDbAssocPersSubentId.h"
#pragma pack (push, 8)

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)  (P)
#endif


/// <summary>
/// The concrete derived AcDbAssocPersSubentId class that simply keeps the
/// AcDbSubentId when it is persistent and does not change.
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocSimplePersSubentId : public AcDbAssocPersSubentId
{
public:
	ACRX_DECLARE_MEMBERS(AcDbAssocSimplePersSubentId);

    /// <summary>
    /// Constructor. Just keeps the given AcDbSubentId.
    /// </summary>
    explicit AcDbAssocSimplePersSubentId(AcDbSubentId subentId = kNullSubentId) : mSubentId(subentId) {}

    /// <summary>
    /// Returns number 1 if not null or 0 if null.
    /// </summary>
    /// <param  name="pEntity">   Not used. </param>
    /// <param  name="pDatabase"> Not used. </param>
    /// <returns> Returns count 1 or 0. </returns>
    ///
    virtual int transientSubentCount(const AcDbEntity* pEntity, AcDbDatabase* pDatabase) const override {
        UNREFERENCED_PARAMETER(pEntity);
        UNREFERENCED_PARAMETER(pDatabase);
        return !isNull() ? 1 : 0; 
    }

    /// <summary> Returns the type of the stored AcDbSubentId. </summary>
    /// <param  name="pEntity">   Not used. </param>
    /// <param  name="pDatabase"> Not used. </param>
    /// <returns> AcDb::SubentType. </returns>
    ///
    virtual AcDb::SubentType subentType(const AcDbEntity* pEntity, AcDbDatabase* pDatabase) const override {
        UNREFERENCED_PARAMETER(pEntity);
        UNREFERENCED_PARAMETER(pDatabase);
        return mSubentId.type(); 
    }

    /// <summary> Returns the stored AcDbSubentId. </summary>
    /// <returns> The stored AcDbSubentId. </returns>
    ///
    virtual AcDbSubentId subentId(const AcDbEntity*) const { return mSubentId; }

    /// <summary> 
    /// Returns true iff the AcDbSubentId stored in this AcDbAssocSimplePersSubentId is null.
    /// </summary>
    /// <returns> True iff the stored AcDbSubentId is null. </returns>
    ///
    virtual bool isNull() const override
    {
        return mSubentId.type() == AcDb::kNullSubentType;
    }

    /// <summary>
    /// Returns true iff this and the other AcDbAssocSimplePersSubentId reference
    /// exactly the same subentity of the same entity. It simply compares the 
    /// stored AcDbSubentIds.
    /// </summary>
    /// <param name="pEntity">   Not used. </param>
    /// <param name="pDatabase"> Not used. </param>
    /// <param  name="pOther"> The other AcDbAssocSimplePersSubentId. </param>
    /// <returns> True iff this and the other AcDbAssocSimplePersSubentId are equal. </returns>
    ///
    virtual bool isEqualTo(const AcDbEntity* pEntity, AcDbDatabase* pDatabase, const AcDbAssocPersSubentId* pOther) const override;

    /// <summary> Sets an AcDbSubentId to this AcDbAssocSimplePersSubentId. </summary>
    /// <param  name="newSubentId"> The input AcDbSubentId to set. </param>
    ///
    void setSubentId(const AcDbSubentId& newSubentId) { mSubentId = newSubentId; }

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

    /// <summary> The standard protocol. </summary>
    /// <param  name="pAuditInfo"> See the AcDbAuditInfo documentation. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;

private:

    AcDbSubentId mSubentId;

}; // class AcDbAssocSimplePersSubentId

#pragma pack (pop)


