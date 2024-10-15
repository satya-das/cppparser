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
// DESCRIPTION: AcDbSortentsTable
//              In spite of the dated name, this class contains the
//              draw order information for a single AcDbBlockTableRecord,
//              including model space and the layouts.
//

#ifndef ACDB_SORTTAB_H
#define ACDB_SORTTAB_H 1

#include "dbmain.h"

class AcDbImpSortentsTable;

class AcDbSortentsTable : public AcDbObject
{

public:

    ACRX_DECLARE_MEMBERS(AcDbSortentsTable);

                        AcDbSortentsTable();
    virtual             ~AcDbSortentsTable();

    // getSortHandle
    // sortAs
    //
    // Given an input object id, returns the AcDbHandle that indicates the
    // draw order. Entities with lesser handle values are drawn before/behind
    // entities with higher handle values.  This handle, sometimes called its
    // "draw order sort key" may have nothing to
    // do with the object id, and may no longer even exist in the database.
    // Its numerical value is what is of use, not the object it points to.
    //
    // NOTE: getSortHandle is highly recommended for general use instead of
    //       sortAs, because getSortHandle always returns the correct draw
    //       order sort key, regardless of explicit sortents table residency.
    //
    // sortAs is published for historical reasons, and
    // returns false if the object id isn't explicitly in the data, in
    // which case the object id's own handle is its "draw order sort key".
    // Returns true if the object id has an explicitly assigned draw
    // order key.  Due to internal algorithms, sortAs cannot be relied upon
    // to return true or false reliably for a given object id.
    //
    Adesk::Boolean      sortAs(AcDbObjectId, AcDbHandle&) const;
    void                getSortHandle(AcDbObjectId id, AcDbHandle& h) const;


    // remove
    //
    // CAUTION: DO NOT USE!
    //          This function does nothing but return eInvalidInput.
    //          It remains only to prevent linker errors until
    //          the next API revision.
    //
    Acad::ErrorStatus   remove(AcDbObjectId);

    // moveToBottom, moveToTop
    //
    // Places all the entities specified in the input object id array at
    // the beginning or ending of the draw order.  The entities being moved
    // retain their relative draw order.
    //
    // Returns eInvalidInput if any input object id is not in the associated block.
    //         eDuplicateKey if any object id appears twice in the input array.
    //
    Acad::ErrorStatus   moveToBottom(const AcDbObjectIdArray& ar);
    Acad::ErrorStatus   moveToTop(const AcDbObjectIdArray& ar); 

    // moveAbove, moveBelow
    //
    // Places all the entities specified in the input object id array above or
    // below the specified "target" entity.  The entities being moved
    // retain their relative draw order.
    //
    //
    // Returns eInvalidInput if any input object id is not in the associated block.
    //         eDuplicateKey if any object id appears twice in the input array.
    //
    Acad::ErrorStatus   moveBelow(const AcDbObjectIdArray& ar,
                                  AcDbObjectId target);
    Acad::ErrorStatus   moveAbove(const AcDbObjectIdArray& ar,
                                  AcDbObjectId target);

    // swapOrder
    //
    // Swaps the draw order positions of the entities.
    //
    // Returns eInvalidInput if object id is not in the associated block.
    //
    Acad::ErrorStatus   swapOrder(AcDbObjectId, AcDbObjectId);

    // blockId and setBlockId
    //
    // These two members allow one to set or query the object id for the
    // associated block table record.
    //
    // setBlockId returns eInvalidInput if the input object id is invalid or
    // is not that of a block table record.
    //
    Acad::ErrorStatus   setBlockId(AcDbObjectId);
    AcDbObjectId        blockId() const;

    // firstEntityIsDrawnBeforeSecond
    //
    // Sets result to true if first is drawn before second.
    //
    // Returns eInvalidInput if any object id is not in the associated block.
    //
    Acad::ErrorStatus   firstEntityIsDrawnBeforeSecond(AcDbObjectId first,
                                                       AcDbObjectId second,
                                                       bool& result) const;

    // getFullDrawOrder
    //
    // Returns array of the block's content entity object ids 
    // appearing in the order which they would be drawn in.
    //
    // Caller supplies a presumably empty object id array, and
    // disposes of it after use.
    //
    // honorSortentsMask indicates when the output is influenced by the
    // specific bits of this table's host database's
    // AcDbDatabase::sortEnts() setting.  By default, sortEnts() is not
    // considered.  But if you pass in one or more sortents bits defined by
    // enum SortentsFlags in acdb.h, then if ANY of the corresponding bits
    // in sortEnts() is 0 (off), then the entities are returned in database
    // order. It is strongly recommended you pass in just 1 bit for a call. 
    //
    // ErrorStatus is eOk, unless we run out of memory.
    //
    Acad::ErrorStatus   getFullDrawOrder(AcDbObjectIdArray& ents,
                                         Adesk::UInt8 honorSortentsMask=0) const;

    // getRelativeDrawOrder
    //
    // Rearranges the object ids in the input array into their current
    // relative draw order.
    //
    // ar is the input and output array.
    //
    // honorSortents has the same effect as it does for getFullDrawOrder.
    //
    // Returns eInvalidInput if any object id is not in the associated block.
    //
    Acad::ErrorStatus   getRelativeDrawOrder(AcDbObjectIdArray& ar,
                                             Adesk::UInt8 honorSortentsMask=0) const;

    // setRelativeDrawOrder
    //
    // Takes the object ids in the input array and moves them in their current
    // associated draw order slots so that they are drawn in the specified order.
    // If you wish to move or consolidate the draw order slots of these object ids,
    // use the appropriate move*() member function to do so, either before or after
    // calling this member.
    //
    // Returns eInvalidInput if any object id is not in the associated block.
    //
    Acad::ErrorStatus   setRelativeDrawOrder(const AcDbObjectIdArray& ar);

    // Overridden AcDbObject members
    //
    virtual Acad::ErrorStatus   applyPartialUndo(AcDbDwgFiler*, AcRxClass*) override;
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler*) override;
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler*) const override;
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler*) override;
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler*) const override;
    virtual Acad::ErrorStatus   audit(AcDbAuditInfo* pAuditInfo) override;

private:
    friend class AcDbSystemInternals;
    AcDbImpSortentsTable*   mpImpObj;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

#endif // ACDB_SORTTAB_H
