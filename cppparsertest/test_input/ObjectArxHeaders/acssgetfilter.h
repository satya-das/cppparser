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
//  ssgetfilter.h - Header file for AcEdSelectionSetService and AcEdSSGetFilter
//

#ifndef _SSGETFILTER_H
#define _SSGETFILTER_H
#include "acedinpt.h"  // AcEdInputContextReactor

class AcApDocument;


class AcEdSelectionSetService
{
public:
    virtual ~AcEdSelectionSetService() {}

    virtual Acad::ErrorStatus ssNameX(
        bool bIsSubSelectionIndex,
        int index,
        resbuf*& result) = 0;
    
    virtual Acad::ErrorStatus ssNameSubentityX(
        bool bIsSubSelectionIndex,
        int index,
        int subentityIndex,
        resbuf*& result) = 0;

    virtual Acad::ErrorStatus ssNameSubentities(
        bool bIsSubSelectionIndex,
        int index,
        AcDbFullSubentPathArray& subEntities) = 0;
        
    virtual Acad::ErrorStatus add(
        resbuf *ssnameXList,
        const AcDbFullSubentPath *pPath = NULL,
        const AcDbObjectId* pEntselSubent = NULL) = 0;

    virtual Acad::ErrorStatus addSubentity(
        resbuf *ssnameXList,
        const AcDbFullSubentPath& subEntity) = 0;

    virtual Acad::ErrorStatus remove(
        int index) = 0;

    virtual Acad::ErrorStatus removeSubentity(
        int entityIndex,
        int subEntityIndex) = 0; 

    virtual Acad::ErrorStatus highlight(
        int subSelectionIndex,
        const AcDbFullSubentPath& path) = 0;

    virtual int subSelectionMode() = 0;

    virtual Acad::ErrorStatus getSubSelectionPoints(
        AcGePoint3dArray& points) = 0;

    virtual Acad::ErrorStatus add(
        const AcArray<resbuf *>& ssnameXList,
        const AcArray<AcDbFullSubentPath *> *pPath,
        bool bAddsAreUnique) = 0;

    virtual Acad::ErrorStatus addSubentities(
        resbuf * ssnameXList,
        const AcArray<AcDbFullSubentPath>& subEntities,
        bool bAddsAreUnique) = 0;

    virtual Acad::ErrorStatus remove(
        const AcArray<int>& indices) = 0;

    virtual Acad::ErrorStatus removeSubentities(
        int entityIndex,
        const AcArray<int>& subEntityIndices) = 0;
};

typedef AcArray<AcDbIntArray, AcArrayObjectCopyReallocator<AcDbIntArray> > 
    AcDbArrayIntArray;

class AcEdSSGetFilter: public AcEdInputContextReactor
{
public:

    virtual void
    ssgetAddFilter(
        int ssgetFlags,
        AcEdSelectionSetService &service,
        const AcDbObjectIdArray& selectionSet,
        const AcDbObjectIdArray& subSelectionSet)
    { 
        ADESK_UNREFED_PARAM(ssgetFlags);
        ADESK_UNREFED_PARAM(service);
        ADESK_UNREFED_PARAM(selectionSet);
        ADESK_UNREFED_PARAM(subSelectionSet);
    }

    virtual void
    ssgetRemoveFilter(
        int ssgetFlags,
        AcEdSelectionSetService &service,
        const AcDbObjectIdArray& selectionSet,
        const AcDbObjectIdArray& subSelectionSet,
        AcDbIntArray& removeIndexes,
        AcDbArrayIntArray& removeSubentIndexes)
    { 
        ADESK_UNREFED_PARAM(ssgetFlags);
        ADESK_UNREFED_PARAM(service);
        ADESK_UNREFED_PARAM(selectionSet);
        ADESK_UNREFED_PARAM(subSelectionSet);
        ADESK_UNREFED_PARAM(removeIndexes);
        ADESK_UNREFED_PARAM(removeSubentIndexes);}

    virtual void
    ssgetAddFailed(
        int ssgetFlags,
        int ssgetMode,
        AcEdSelectionSetService &service,
        const AcDbObjectIdArray& selectionSet,
        resbuf *rbPoints)
    {
        ADESK_UNREFED_PARAM(ssgetFlags);
        ADESK_UNREFED_PARAM(ssgetMode);
        ADESK_UNREFED_PARAM(service);
        ADESK_UNREFED_PARAM(selectionSet);
        ADESK_UNREFED_PARAM(rbPoints);
    }

    virtual void
    ssgetRemoveFailed(
        int ssgetFlags,
        int ssgetMode,
        AcEdSelectionSetService &service,
        const AcDbObjectIdArray& selectionSet,
        resbuf *rbPoints,
        AcDbIntArray& removeIndexes,
        AcDbArrayIntArray& removeSubentIndexes)
    {
        ADESK_UNREFED_PARAM(ssgetFlags);
        ADESK_UNREFED_PARAM(ssgetMode);
        ADESK_UNREFED_PARAM(service);
        ADESK_UNREFED_PARAM(selectionSet);
        ADESK_UNREFED_PARAM(rbPoints);
        ADESK_UNREFED_PARAM(removeIndexes);
        ADESK_UNREFED_PARAM(removeSubentIndexes);
    }

    virtual void
    endSSGet(
        Acad::PromptStatus returnStatus,
        int ssgetFlags,
        AcEdSelectionSetService &service,
        const AcDbObjectIdArray& selectionSet)
    {
        ADESK_UNREFED_PARAM(returnStatus);
        ADESK_UNREFED_PARAM(ssgetFlags);
        ADESK_UNREFED_PARAM(service);
        ADESK_UNREFED_PARAM(selectionSet);
    }

    virtual void
    endEntsel(
        Acad::PromptStatus       returnStatus,
        const AcDbObjectId&      pickedEntity,
        const AcGePoint3d&       pickedPoint,
        AcEdSelectionSetService& service)
    {
        ADESK_UNREFED_PARAM(returnStatus);
        ADESK_UNREFED_PARAM(pickedEntity);
        ADESK_UNREFED_PARAM(pickedPoint);
        ADESK_UNREFED_PARAM(service);
    }
};


Acad::ErrorStatus addSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter *pFilter);

Acad::ErrorStatus removeSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter *pFilter);

// please note this function had been using the Windows type boolean
// for the flag parameter. it has been replaced not with type bool
// as you might expect, but with the underlying  intrinsic type to
// avoid changing the exported mangled name
Acad::ErrorStatus setAllowDuplicateSelection(
                        AcApDocument *pDoc, unsigned char flag);

bool              duplicateSelectionsAllowed(AcApDocument *pDoc);


namespace AcEdSSGet {

enum AcEdSSGetFlags {
    kNormal         =   0,
    kPickPoints     =   1,
    kDuplicates     =   2,
    kNestedEntities =   4,
    kSubEntities    =   8,
    kSinglePick     =  16,
    kPickfirstSet   =  32,
    kPreviousSet    =  64,
    kSubSelection   = 128,
    kUndo           = 256,
    kFailedPickAuto = 512,
    kCommandPreview = 1024,
    kAllViewports   = 2048,
    kForBoxPick     = 4096,
    kPreSelectionHilite = 8192
};

enum AcEdSSGetModes {
    kWin = 1,   //  (Window spec)
    kCross,     //  (Crossing spec)
    kBox,       //  (Box spec)
    kLast,      //  (Last)
    kEntity,    //  (Explicit entity name)
    kAll,       //  (Select all)
    kFence,     //  (Fence Selection)
    kCPoly,     //  (Crossing Poly)
    kWPoly,     //  (Window Poly)
    kPick,      //  (Single pick)
    kEvery,     //  (every entity on single pick)
    kXten,      //  (ssget "X")
    kGroup,     //  (selection set from "group" specification)
    kPrevious,  //  (previous selectionset)
    kMultiple,  //  (Multiple keyword)
};

};

class AcEdSSGetFilter2 : public AcEdSSGetFilter
{
public:

    virtual void
    ssgetRolloverFilter(
        const AcDbFullSubentPath &subEntityPath, 
        AcDbFullSubentPath &highlightPath)
    {
        ADESK_UNREFED_PARAM(subEntityPath);
        ADESK_UNREFED_PARAM(highlightPath);
    }
};

Acad::ErrorStatus addSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter2 *pFilter);

Acad::ErrorStatus removeSSgetFilterInputContextReactor(
                        AcApDocument *pDoc, AcEdSSGetFilter2 *pFilter);

class AcEdSSGetFilter3 : public AcEdSSGetFilter
{
public:

    virtual void
    ssgetRolloverFilter(
        const AcDbFullSubentPath &subEntityPath, 
        AcDbFullSubentPathArray &highlightPaths)
    {
        ADESK_UNREFED_PARAM(subEntityPath);
        ADESK_UNREFED_PARAM(highlightPaths);
    }
};

Acad::ErrorStatus addSSgetFilterInputContextReactor(
    AcApDocument *pDoc, AcEdSSGetFilter3 *pFilter);
Acad::ErrorStatus removeSSgetFilterInputContextReactor(
    AcApDocument *pDoc, AcEdSSGetFilter3 *pFilter);


class AcEdSSGetFilter4 : public AcEdSSGetFilter
{
public:
   virtual void
    endNEntsel(
        Acad::PromptStatus       returnStatus,
        const AcDbObjectId&      pickedEntity,
        const AcGePoint3d&       pickedPoint,
        ads_point                xformres[4], 
        struct resbuf **         refstkres,
        AcEdSelectionSetService& service)
    {
        ADESK_UNREFED_PARAM(returnStatus);
        ADESK_UNREFED_PARAM(pickedEntity);
        ADESK_UNREFED_PARAM(pickedPoint);
        ADESK_UNREFED_PARAM(xformres);
        ADESK_UNREFED_PARAM(refstkres);
        ADESK_UNREFED_PARAM(service);
        }

   virtual void beginSSGetCustomKeywordCallback(const ACHAR* ) {};
   virtual void endSSGetCustomKeywordCallback(const ACHAR* ) {};

};

Acad::ErrorStatus addSSgetFilterInputContextReactor(
    AcApDocument *pDoc, AcEdSSGetFilter4 *pFilter);
Acad::ErrorStatus removeSSgetFilterInputContextReactor(
    AcApDocument *pDoc, AcEdSSGetFilter4 *pFilter);


class AcEdSubSelectFilterService
{
public:

    virtual Acad::ErrorStatus ssNameX(
        bool bIsSubSelectionIndex,
        int index,
        resbuf*& result) = 0;
    
    virtual Acad::ErrorStatus add(
        resbuf *ssnameXList,
        const AcDbFullSubentPath& path) = 0;

    virtual Acad::ErrorStatus remove(
        bool bIsSubSelectionIndex,
        int index) = 0;
};

class AcEdSSGetSubSelectFilter : public AcEdInputContextReactor
{
public:

    virtual Acad::ErrorStatus 
        getSubentPathsAtGsMarker(
            AcDbEntity*                    pEnt, 
            bool                           bAdding,
            const AcDbFullSubentPathArray& selectedPaths,
            AcDb::SubentType               type,
            Adesk::GsMarker                gsMark, 
            const AcGePoint3d&             pickPoint,
            const AcGeMatrix3d&            viewXForm,
            int&                           numPaths,
            AcDbFullSubentPath*&           subentPaths,
            int                            numInserts,
            AcDbObjectId*                  entAndInsertStack) = 0;
    
    virtual Acad::ErrorStatus 
        subSelectClassList(AcArray<AcRxClass*>& classes) = 0;

    virtual void
        ssgetAddFilter(
            int                            ssgetFlags,
            AcEdSubSelectFilterService&    service,
            const AcDbObjectId&            object,
            const AcDbFullSubentPathArray& selectedPaths,
            const AcDbFullSubentPathArray& addedPaths) = 0;

    virtual void
        ssgetRemoveFilter(
            int                            ssgetFlags, 
            AcEdSubSelectFilterService&    service,
            const AcDbObjectId&            object,
            const AcDbFullSubentPathArray& selectedPaths,
            const AcDbFullSubentPathArray& removedPaths) = 0;
};

Acad::ErrorStatus addSSgetFilterInputContextReactor(
                        AcApDocument             *pDoc, 
                        AcEdSSGetSubSelectFilter *pFilter);

Acad::ErrorStatus removeSSgetFilterInputContextReactor(
                        AcApDocument             *pDoc, 
                        AcEdSSGetSubSelectFilter *pFilter);

#endif  // _SSGETFILTER_H

