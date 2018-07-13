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
//
// AcDbIndex is the base class for all index implementations.
//
// These indexes are associated with Block Spaces, and can be used
// to perform an efficient filtered traversal of the block.
//

#ifndef AD_DBINDEX_H
#define AD_DBINDEX_H

#include "dbmain.h"

#pragma pack(push, 8)


class AcDbIndexIterator;
class AcDbFilter;
class AcDbIndexUpdateData;
class AcDbBlockChangeIterator;
class AcDbFilteredBlockIterator;
class AcDbFilter;
class AcDbImpDatabase;
class AcDbBlockTableRecord;
class AcDbBlockChangeIterator;
class AcDbIndexUpdateData;

class AcDbIndex : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbIndex);

    AcDbIndex();
    virtual ~AcDbIndex();

    virtual AcDbFilteredBlockIterator* 
                  newIterator(const AcDbFilter* pFilter) const;

    virtual Acad::ErrorStatus rebuildFull(AcDbIndexUpdateData* pIdxData);
 
    virtual AcDbObjectId objectBeingIndexedId()  const;

    void           setLastUpdatedAt(const AcDbDate& time);
    AcDbDate       lastUpdatedAt() const;

    // Same as above two methods, but time vals are universal, not local.
    //
    void           setLastUpdatedAtU(const AcDbDate& time);
    AcDbDate       lastUpdatedAtU() const;

    Adesk::Boolean isUptoDate   () const;  

protected:
    // Invoked by the AcIndexFilterManager::updateIndexes(), when
    // only modifications are being registered. This is not 
    // exposed since all the Index objects need to be updated 
    // when modifications are being propagated.

    virtual Acad::ErrorStatus rebuildModified(AcDbBlockChangeIterator* iter);

    friend class AcDbImpIndex;
    friend Acad::ErrorStatus processBTRIndexObjects(
                                   AcDbBlockTableRecord* pBTR,
                                   int indexCtlVal,
                                   AcDbBlockChangeIterator* pBlkChgIter,
                                   AcDbIndexUpdateData*     pIdxUpdData);
};



class AcDbFilteredBlockIterator
{
public:
    AcDbFilteredBlockIterator()          {}
    virtual ~AcDbFilteredBlockIterator() {}

    virtual Acad::ErrorStatus start()               = 0;
    virtual AcDbObjectId      next()                = 0;
    virtual AcDbObjectId      id() const            = 0;
    virtual Acad::ErrorStatus seek(AcDbObjectId id) = 0;


    // Methods used for handling multiple index object based filters.

    virtual double estimatedHitFraction() const             = 0;
    virtual Acad::ErrorStatus accepts(AcDbObjectId id, 
                      Adesk::Boolean& idPassesFilter) const = 0;

    // Defaults to false
    // 
    virtual Adesk::Boolean    buffersForComposition() const;
    virtual Acad::ErrorStatus addToBuffer(AcDbObjectId id);
};



class AcDbCompositeFilteredBlockIterator
{
private:
    AcDbCompositeFilteredBlockIterator(
        const AcDbCompositeFilteredBlockIterator& copyFrom);

protected:
    AcDbCompositeFilteredBlockIterator() {}

public:
    virtual ~AcDbCompositeFilteredBlockIterator() {}

    virtual Acad::ErrorStatus init(AcDbFilter* const * ppFilters,
                                   int numFilters,
                                   const AcDbBlockTableRecord* pBtr) = 0;

    virtual Acad::ErrorStatus start()    = 0;
    virtual AcDbObjectId      next()     = 0;
    virtual AcDbObjectId      id() const = 0;

    virtual Acad::ErrorStatus seek(AcDbObjectId id)  = 0;
    static AcDbCompositeFilteredBlockIterator* newIterator();
};


class AcDbBlockTableRecord;
class AcDbBlockReference;

namespace AcDbIndexFilterManager
{
    // Updates all indexes in the Block Table.
    //
    Acad::ErrorStatus updateIndexes(AcDbDatabase* pDb);

    // Block Table Record Index access methods.
  
    Acad::ErrorStatus addIndex    (AcDbBlockTableRecord* pBTR,
                                   AcDbIndex*            pIndex);

    Acad::ErrorStatus removeIndex (AcDbBlockTableRecord* pBTR, 
                                   const AcRxClass*      key);

    Acad::ErrorStatus getIndex(const AcDbBlockTableRecord* pBTR,
                               const AcRxClass* key, 
                               AcDb::OpenMode readOrWrite,
                               AcDbIndex*& pIndex);

    Acad::ErrorStatus getIndex(const AcDbBlockTableRecord* pBTR,
                               int index,
                               AcDb::OpenMode readOrWrite,
                               AcDbIndex*& pIndex);

    int numIndexes(const AcDbBlockTableRecord* pBtr);


    // Block Reference Filter access methods.

    Acad::ErrorStatus addFilter(AcDbBlockReference* pBlkRef,
                                AcDbFilter*         pFilter);

    Acad::ErrorStatus removeFilter(AcDbBlockReference* pBlkRef,
                                   const AcRxClass*    key);

    Acad::ErrorStatus getFilter(const AcDbBlockReference* pRef,
                                const AcRxClass*          key,       
                                AcDb::OpenMode readOrWrite,
                                AcDbFilter*&   pFilter);
    
    Acad::ErrorStatus getFilter(const AcDbBlockReference* pRef,
                                int index,
                                AcDb::OpenMode readOrWrite,
                                AcDbFilter*& pFilter);

    int  numFilters(const AcDbBlockReference* pBlkRef);
};



class AcDbHandleTable;
class AcDbHandleTableIterator;


// Is a form of an alternate table of ids, primarily modified ones 
// during partial index update.
//
class AcDbIndexUpdateData 
{
    public:
        
        enum UpdateFlags 
        {                      // kModified and kDeleted are READ ONLY.
            kModified   = 1,   //
            kDeleted    = 2,   // kDeleted is somewhat redundant with  AcDbObject::isErased()
                               // except that it also accounts for uncreated
                               // objects, and does not force an object to be
                               // paged in.
                
                               // These two are writable. They are for application use.
            kProcessed  = 4,   // kProcessed can be used to avoid rexamining an id.
            kUnknownKey = 8    // kUnknownKey is used, for example, to denote unknown
                               // extents when building the spatial index.
                
                               // The remaining bits can be used by applications as
                               // they wish.  (Bits 3- 7).
        };
        
        Acad::ErrorStatus addId      (AcDbObjectId id);
        
        // Bits kModified and kDeleted are never changed by this method, since
        // they refer to the db state of the object. The kProcessed bit and
        // kUnknownKey are for specific Index (layer and spatial) processing.
        //
        Acad::ErrorStatus setIdFlags (AcDbObjectId id, Adesk::UInt8 flags);
        
        Acad::ErrorStatus setIdData  (AcDbObjectId id, Adesk::ULongPtr data);
        
        Acad::ErrorStatus getIdData       (AcDbObjectId id, Adesk::ULongPtr& data)  const;
        Acad::ErrorStatus getIdFlags      (AcDbObjectId id, Adesk::UInt8&  flags) const;       
        Acad::ErrorStatus getFlagsAndData (AcDbObjectId   id, 
                                           Adesk::UInt8&  flags, 
                                           Adesk::ULongPtr& data) const;

    private:
        AcDbIndexUpdateData();
        ~AcDbIndexUpdateData();

        AcDbIndexUpdateData(const AcDbIndexUpdateData&);

        AcDbHandleTable* mpTable;

        friend class AcDbIndexUpdateDataIterator;
        friend class AcDbImpDatabase;
};



class AcDbIndexUpdateDataIterator
{
    public:
        AcDbIndexUpdateDataIterator  (const AcDbIndexUpdateData* p);
        ~AcDbIndexUpdateDataIterator ();

        void start   ();
        void next    ();
        bool done    ();

        Acad::ErrorStatus currentData (AcDbObjectId&  id, 
                                       Adesk::UInt8&  flags, 
                                       Adesk::ULongPtr& data) const;
 
    private:
        AcDbHandleTableIterator* mpIter;
};



// Iterates over only changed entities inside a block table record.
//
class AcDbBlockChangeIterator
{
private:
    AcDbBlockChangeIterator();
    AcDbBlockChangeIterator(const AcDbBlockChangeIterator&);

    AcDbBlockChangeIterator (AcDbObjectId         btrId,
                             AcDbIndexUpdateData* pIdxUpdData);
    ~AcDbBlockChangeIterator();
    
public:
    void         start ();
    AcDbObjectId id    () const;
    void         next  ();
    bool         done  ();              

    // Utility to get at this data without having to go through
    // the updateData() method.
    //
    Acad::ErrorStatus    curIdInfo    (AcDbObjectId&  id,
                                       Adesk::UInt8&  flags, 
                                       Adesk::ULongPtr& data) const;

    Acad::ErrorStatus    setCurIdInfo (Adesk::UInt8   flags,  
                                       Adesk::ULongPtr data);

    AcDbIndexUpdateData* updateData () const;

    void clearProcessedFlags();


private:
    AcDbIndexUpdateData*         mpIds;
    AcDbObjectId                 mBTRId;

    AcDbIndexUpdateDataIterator* mpIter;

    friend class AcDbImpDatabase;
};


#pragma pack(pop)

#endif // AD_DBINDEX_H
