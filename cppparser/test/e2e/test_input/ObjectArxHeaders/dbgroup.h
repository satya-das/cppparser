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
// dbgroup.h
//
// AcDbGroup
//
// Maintains an ordered collection of database objects with a related iterator.
// An iterator can be obtained via an existing AcDbGroup object with
// the newIterator() method.  See below for class descriptions for both
// AcDbGroup and AcDbGroupIterator.
//
// AcDbGroup objects are contained in a special group table (actually a
// dictionary).  This dictionary can be obtained like this:
//
//     AcDbDictionary* pGrpDict = 
//         acdbHostApplicationServices()->workingDatabase()->groupTable();
//
// The AcDbGroup constructor does not add the group to the group dictionary;
// this must be done explicitly, using the AcDbDictionary protocol.
//
// When an entity is erased, it is automatically removed from
// the groups that contain it.

#ifndef ACDB_DBGROUP_H
#define ACDB_DBGROUP_H

#include "dbmain.h"
#include "dbapserv.h"

#pragma pack(push, 8)

class AcDbGroupIterator;

class AcDbGroup: public  AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbGroup);
    AcDbGroup();
    AcDbGroup(const ACHAR * grpDesc, bool selectable = true);
    virtual ~AcDbGroup();

    AcDbGroupIterator*  newIterator();

    const ACHAR *       description() const;
    Acad::ErrorStatus   setDescription(const ACHAR * grpDesc);

    bool                isSelectable() const;
    Acad::ErrorStatus   setSelectable(bool selectable);

/// <summary>
/// Get the group's name. Allocates a buffer and sets caller's pointer to it.
/// </summary>
/// <returns> Acad::eOk if success, else an error code. </returns>
/// <remarks> Caller should free buffer when done.
///           Pointer is set to null on errors.
///           On errors, pName points to an empty string.
///           This method is deprecated. Callers should switch to one of the other
///           two overloads of getName().
/// </remarks>
///
    ACDBCORE2D_PORT
    Acad::ErrorStatus   getName(ACHAR *& pName) const;   // deprecated

/// <summary>
/// Get the group's name. Returns a pointer to an internal buffer.
/// </summary>
/// <returns> Acad::eOk if success, else an error code. </returns>
/// <remarks> Pointer is only valid until this group object is closed.
///           Caller should not free this pointer nor cast away its const-ness.
///           Pointer is set to null on errors.
///           On errors, pName points to an empty string.
///           On errors, pName points to an empty string.
/// </remarks>
///
    ACDBCORE2D_PORT
    Acad::ErrorStatus   getName(const ACHAR *& pName) const;

/// <summary>
/// Get the group's name into the caller's AcString.
/// </summary>
/// <returns> Acad::eOk if success, else an error code. </returns>
/// <remarks> AcString is set to empty on errors.
/// </remarks>
///
    ACDBCORE2D_PORT
    Acad::ErrorStatus   getName(AcString & sName) const;

/// <summary>
/// Return const pointer to the group's name. Equivalent to getName(const ACHAR * &pName).
/// </summary>
/// <returns> Acad::eOk if success, else an error code. </returns>
/// <remarks> Deprecated. Please call getName(const ACHAR * &pName) instead.
///           Returns null on errors.
/// </remarks>
///
    const wchar_t * name() const
    {
        const wchar_t *pName;
        if (this->getName(pName) != Acad::eOk)
            pName = nullptr;
        return pName;
    }

    Acad::ErrorStatus   setName(const ACHAR * newName);

    bool                isNotAccessible() const;

    bool                isAnonymous() const;
    Acad::ErrorStatus   setAnonymous();

    Acad::ErrorStatus   append(AcDbObjectId id);
    ACDBCORE2D_PORT
      Acad::ErrorStatus append(const AcDbObjectIdArray & ids);
    Acad::ErrorStatus   prepend(AcDbObjectId id);
    ACDBCORE2D_PORT
      Acad::ErrorStatus prepend(const AcDbObjectIdArray & ids);
    Acad::ErrorStatus   insertAt(Adesk::UInt32 idx, AcDbObjectId id);
    ACDBCORE2D_PORT
      Acad::ErrorStatus insertAt(Adesk::UInt32 idx, const AcDbObjectIdArray & ids);
    Acad::ErrorStatus   remove(AcDbObjectId id);
    Acad::ErrorStatus   removeAt(Adesk::UInt32 idx);
    ACDBCORE2D_PORT
      Acad::ErrorStatus remove(const AcDbObjectIdArray & ids);
    ACDBCORE2D_PORT
      Acad::ErrorStatus removeAt(Adesk::UInt32 idx, const AcDbObjectIdArray & ids);
    Acad::ErrorStatus   replace(AcDbObjectId oldId, AcDbObjectId newId);
    Acad::ErrorStatus   transfer(Adesk::UInt32 fromIndex, 
                                 Adesk::UInt32 toIndex, 
                                 Adesk::UInt32 numItems);

    Acad::ErrorStatus   clear();
    Adesk::UInt32       numEntities() const;
    bool                has(const AcDbEntity* pEntity) const;
    Adesk::UInt32       allEntityIds(AcDbObjectIdArray& ids) const;
    Acad::ErrorStatus   getIndex(AcDbObjectId id, Adesk::UInt32& idx) const;
    Acad::ErrorStatus   reverse();

    Acad::ErrorStatus   setColor(const AcCmColor& color);
    Acad::ErrorStatus   setColorIndex(Adesk::UInt16 color);
    Acad::ErrorStatus   setLayer(const ACHAR * newVal);
    Acad::ErrorStatus   setLayer(AcDbObjectId newVal);
    Acad::ErrorStatus   setLinetype(const ACHAR * newVal);
    Acad::ErrorStatus   setLinetype(AcDbObjectId newVal);
    Acad::ErrorStatus   setLinetypeScale(double newval);
    Acad::ErrorStatus   setVisibility(AcDb::Visibility newVal);
    Acad::ErrorStatus   setHighlight(bool newVal);

    Acad::ErrorStatus   setMaterial(const ACHAR * newVal);
    Acad::ErrorStatus   setMaterial(AcDbObjectId newVal);
    // Overridden methods from AcDbObject
    //
    virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* undoFiler,
                                               AcRxClass*    classObj) override;

    virtual Acad::ErrorStatus subClose() override;
    virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing) override;

    virtual void              erased(const AcDbObject* dbObj,
                                     Adesk::Boolean erasing) override;
    virtual void              goodbye(const AcDbObject* dbObj) override;

    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;

    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};


// The group iterator class.
//
class ADESK_NO_VTABLE AcDbGroupIterator: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGroupIterator);
    virtual ~AcDbGroupIterator() {}

    virtual Acad::ErrorStatus getObject(AcDbObject*& pObject,
        AcDb::OpenMode) = 0;
    virtual AcDbObjectId      objectId () const = 0;

    virtual bool              done     () const = 0;
    virtual bool              next     () = 0;

protected:
    AcDbGroupIterator() {}
};

#pragma pack(pop)

#endif
