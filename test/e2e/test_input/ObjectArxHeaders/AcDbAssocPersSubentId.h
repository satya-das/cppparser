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
// AcDbAssocPersSubentId pure virtual base class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "acdb.h"
#pragma pack (push, 8)


/// <summary> <para>
/// Abstract base class used to persistently identify an AcDbSubentId of an 
/// AcDbEntity. Unlike AcDbSubentId that is transient and may change when the 
/// entity is modified, reevaluated, or similar, the AcDbAssocPersSubentId 
/// identifies the subentity in such a way that it is always possible to obtain 
/// the corresponding subentities (if they still exist), even after the entity 
/// has been edited or reevaluated any number of times.
/// </para> <para>
/// The base AcDbAssocPersSubentId class is an abstract base class. Concrete 
/// AcDbEntity classes need their own way how to represent a persistent 
/// identitfication of their subentities. Therefore there are derived 
/// AcDbAssocPersSubentId classes that keep the persistent identitifcation of
/// the subentities of particular entity types. The simplest one is the
/// AcDbAssocSimplePersSubentId derived class that just keeps the AcDbSubentId 
/// in case it can be relied on that it does not change.
/// </para> <para>
/// The AcRx protocol extension classes derived from AcDbAssocPersSubentIdPE
/// base class provide mapping from transient AcDbSubentId to the persistent
/// AcDbAssocPersSubentId, they allow to create new AcDbAssocPersSubentIds from
/// given AcDbSubentIds. The AcDbAssocPersSubentId provides mapping in the 
/// opposite direction, from AcDbAssocPersSubentIds to AcDbSubentIds.
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocPersSubentId : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDbAssocPersSubentId);

    /// <summary> Default constructor. </summary>
    AcDbAssocPersSubentId() {}

    /// <summary> Virtual destructor. </summary>
    virtual ~AcDbAssocPersSubentId() {}


    /// <summary><para>
    /// The default implementation just calls AcDbAssocPersSubentIdPE::releasePersSubent(),
    /// passing the given AcDbEntity* and this AcDbAssocPersSubentId as input arguments. 
    /// The given AcDbDatabase* argument is ignored.
    /// </para><para>
    /// The reason for having release() method on AcDbAssocPersSubentId is to be able to
    /// release data associated with the AcDbAssocPersSubentId even if the AcDbEntity
    /// is no more available and therefore AcDbAssocPersSubentIdPE cannot be obtained
    /// and used. Derived AcDbAssocPersSubentId classes may override the release()
    /// method to release data associated with the AcDbAssocPersSubentId using the
    /// AcDbDatabase* argument. An example is AcDbAssocAsmBasedEntityPersSubentId that
    /// needs to know the AcDbDatabase* to obtain the singleton AcDbAssocPersSubentManager
    /// object but does not need to know the AcDbEntity*.
    /// <param name="pEntity"> 
    /// The entity must be open for write, but usually no changes to the 
    /// entity will be made (usually no assertWriteEnabled() will be called).
    /// </param>
    /// <param  name="pDatabase"> 
    /// AcDbDatabase of the AcDbEntity that the AcDbAssocPersSubentId references. It is 
    /// used when the pEntity argument is NULL or the AcDbEntity is not database resident. 
    /// NULL may be passed for pDatabase if pEntity is not NULL and is a database-resident 
    /// entity.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus release(AcDbEntity* pEntity, AcDbDatabase* pDatabase) const;

    /// <summary> <para>
    /// Mapping: AcDbAssocPersSubentId --> AcDbSubentId(s)
    /// </para> <para>
    /// Obtains all AcDbSubentIds corresponding to this AcDbAssocPersSubentId.
    /// </para> </summary>
    /// <remarks>
    /// Notice that one AcDbAssocPersSubentId may correspond to none, one or more than
    /// one AcDbSubentId, because the entity may have changed and there may not be 
    /// just a single subentity corresponding to the original subentity identified 
    /// by this AcDbAssocPersSubentId. The default implementation just calls the
    /// AcDbAssocPersSubentIdPE::getTransientSubentIds() method.
    /// </remarks>
    /// <param  name="pEntity"> The entity needs to be open for read. </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param  name="subents"> The returned AcDbSubentIds. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getTransientSubentIds(const AcDbEntity*      pEntity,
                                                    AcDbDatabase*          pDatabase,
                                                    AcArray<AcDbSubentId>& subents) const;


    /// <summary> Returns the type of the subentity. </summary>
    /// <param  name="pEntity"> The entity needs to be open for read. </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <returns> AcDb::SubentType. </returns>
    ///
    virtual AcDb::SubentType subentType(const AcDbEntity* pEntity, 
                                        AcDbDatabase*     pDatabase) const = 0;

    /// <summary> 
    /// Returns the number of transient AcDbSubentIds corresponding to this 
    /// AcDbAssocPersSubentId. The default implementation just calls 
    /// getTransientSubentIds() and returns their count which usually is 1.
    /// </summary>
    /// <param  name="pEntity"> The entity needs to be open for read. </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <returns> 
    /// Number of transient AcDbSubentIds corresponding to this AcDbAssocPersSubentId. 
    /// </returns>
    ///
    virtual int transientSubentCount(const AcDbEntity* pEntity,
                                     AcDbDatabase*     pDatabase) const;

    /// <summary> 
    /// Returns true iff this AcDbAssocPersSubentId is null, i.e. not referencing
    /// and subentity of any entity. It is logically slightly different from when
    /// getTransientSubentIds() returns no AcDbSubentIds. In the latter case the
    /// AcDbAssocPersSubentId may reference some subentities, but they may have
    /// been deleted, changed, or similar. 
    /// </summary>
    /// <returns> True iff this AcDbAssocPersSubentId is null. </returns>
    ///
    virtual bool isNull() const = 0;

    /// <summary>
    /// Returns true iff this and the other AcDbAssocPersSubentId reference
    /// exactly the same subentity of the same entity.
    /// </summary>
    /// <param  name="pEntity"> 
    /// The entity owning the subentities of this and the other AcDbAssocPersSubentId. 
    /// </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <param  name="pOther"> The other AcDbAssocPersSubentId. </param>
    /// <returns> True iff this and the other AcDbAssocPersSubentId are equal. </returns>
    ///
    virtual bool isEqualTo(const AcDbEntity*            pEntity, 
                           AcDbDatabase*                pDatabase,
                           const AcDbAssocPersSubentId* pOther) const;

    /// <summary> <para>
    /// Notifies this AcDbAssocPersSubentId that the entity has been mirrored
    /// and that the AcDbAssocPersSubentId may possibly need to update itself
    /// to identify the same subentity in the mirrored entity as it identified
    /// before the entity has been mirrored.
    /// </para> <para>
    /// The default implementation obtains AcDbAssocPersSubentIdPE from the 
    /// mirrored entity and calls AcDbAssocPersSubentIdPE::mirrorPersSubent()
    /// that does all the work. By default the "work" is a no-op, except for
    /// some entity types, such as AcDbArc and its AcDbAssocArcPersSubentIdPE
    /// protocol extension class.
    /// </para> </summary>
    /// <param  name="pMirroredEntity"> 
    /// The entity that has been mirrored. It needs to be open for read.
    /// </param>
    /// <param name="pDatabase"> 
    /// The database that the AcDbAssocPersSubentId belongs to. It may be a different 
    /// database than the database of the given AcDbEntity when the entity is in an XREF 
    /// database but the AcDbAssocPersSubentId is owned by an object in the host database. 
    /// If the database pointer is NULL, the database of the entity is used.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus mirror(const AcDbEntity* pMirroredEntity,
                                     AcDbDatabase*     pDatabase);

    /// <summary>
    /// A static method that reads the class identification of the actual 
    /// AcDbAssocPersSubentId-derived class, creates an object of this derived
    /// class and calls dwgInFields() on it.
    /// </summary>
    /// <param  name="pDatabase"> 
    /// AcDbDatabase that is going to own the AcDbAssocPersSubentId.
    /// </param>
    /// <param  name="pFiler"> 
    /// The filer to read the data from. The first data is the class identification.
    /// </param>
    /// <param  name="pCreatedPersSubentId"> 
    /// This is an in/out argument used to return the created and filled-in object 
    /// of an AcDbAssocPersSubentId-derived class. If the pCreatedPersSubentId 
    /// is passed in as not NULL, the code tries to reuse the existing object, 
    /// if it is of the expected derived class. If it is passed in as NULL or 
    /// is not of the expected derived type, it creates a new object (deleting 
    /// the existing one, if any).
    /// /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    //
    static Acad::ErrorStatus 
    createObjectAndDwgInFields(AcDbDatabase*           pDatabase,
                               AcDbDwgFiler*           pFiler, 
                               AcDbAssocPersSubentId*& pCreatedPersSubentId);

    /// <summary>
    /// A static method that reads the class identification of the actual 
    /// AcDbAssocPersSubentId-derived class, creates an object of this derived
    /// class and calls dxfInFields() on it.
    /// </summary>
    /// <param  name="pFiler"> 
    /// The filer to read the data from. The first data is the class identification.
    /// </param>
    /// <param  name="pCreatedPersSubentId"> 
    /// This is an in/out argument used to return the created and filled-in object 
    /// of an AcDbAssocPersSubentId-derived class. If the pCreatedPersSubentId 
    /// is passed in as not NULL, the code tries to reuse the existing object, 
    /// if it is of the expected derived class. If it is passed in as NULL or 
    /// is not of the expected derived type, it creates a new object (deleting 
    /// the existing one, if any).
    /// /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    //
    static Acad::ErrorStatus 
    createObjectAndDxfInFields(AcDbDxfFiler*           pFiler, 
                               AcDbAssocPersSubentId*& pCreatedPersSubentId);

    /// <summary>
    /// The standard filing protocol. The AcDbAssocPersSubentId base class
    /// implementation writes-out the actual class identification so that 
    /// it is possible to create an object of the same class when the data is 
    /// read back in (this happens in createObjectAndDwgInFields()).
    /// </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;

    /// <summary>
    /// The standard filing protocol. The AcDbAssocPersSubentId base class
    /// implementation does nothing and doesn't therefore need to be called
    /// from the derived classes.
    /// </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);

    /// <summary>
    /// The standard filing protocol. The AcDbAssocPersSubentId base class
    /// implementation writes-out the actual class identification so that 
    /// it is possible to create an object of the same class when the data is 
    /// read back in (this happens in createObjectAndDxfInFields()).
    /// </summary>
    /// <param  name="pFiler"> The filer to write the object data to. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;

    /// <summary>
    /// The standard filing protocol. The AcDbAssocPersSubentId base class
    /// implementation does nothing and doesn't therefore need to be called 
    /// from the derived classes.
    /// </summary>
    /// <param  name="pFiler"> The filer to read the object data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);

    /// <summary> The standard protocol. </summary>
    /// <param  name="pAuditInfo"> See the AcDbAuditInfo documentation. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus audit(AcDbAuditInfo* /*pAuditInfo*/) { 
        return Acad::eOk; 
    }

    /// <summary>Standard protocol for copying of data from source as defined
    /// in AcRxObject. Don't use this for cross database copying</summary>
    /// <param  name="pSource"> Source object to copy data from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* pSource) override;

}; // class AcDbAssocPersSubentId


#pragma pack (pop)


