
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
// ========= xgraph.h:  AcDbXrefGraph classes ================ 
//
//    This header defines classes:
//
// AcDbXrefGraph - a derived class for representing Xrefs
// AcDbXrefGraphNode - each node represents one Xref database
//
//    An AcDbXrefGraph is a representation of the relationship between a
//    host drawing, its Xref'ed drawings, and any nested Xref drawings.
//    Each database, or Xref BLock Table Record is represented by an
//    AcDbXrefGraphNode in the graph.  The host drawing is always the
//    rootNode.  Each reference is represented by an edge in the graph,
//    and can be queried for by calling AcDbGraphNode::in(idx) for who
//    is referencing this node, and AcDbGraphNode::out(idx) for who this
//    node references.
//
//    Detection for circular references is done by internally creating
//    a duplicate set of references in each node and then triming away
//    all leaf nodes, which terminate without circularity.  If any nodes
//    remain in the duplicate graph, those nodes exist in a cycle.
//    AcDbGraph::findCycles() is used to set up the internal cycle
//    information and enable several query methods to return information
//    about any cycles found.
//
//

#ifndef AD_XGRAPH_H
#define AD_XGRAPH_H 1

#include "graph.h"
#include "AdAChar.h"

#pragma pack (push, 8)

// =====================================
//      Xref Graph Classes
// =====================================


class AcDbXrefGraphNode : public AcDbGraphNode
{
public:
    AcDbXrefGraphNode(const ACHAR * pName = NULL,
        const AcDbObjectId& btrId = AcDbObjectId::kNull,
        AcDbDatabase* pDb = NULL,
        AcDb::XrefStatus status = AcDb::kXrfResolved);
    virtual ~AcDbXrefGraphNode();

    const ACHAR * name() const;
    AcDbObjectId btrId() const;
    AcDbDatabase* database() const;

    Acad::ErrorStatus setName(const ACHAR * pName);
    void setBtrId(const AcDbObjectId& id);
    void setDatabase(AcDbDatabase* pDb);

    bool isNested() const;

    AcDb::XrefStatus xrefStatus() const;
    void setXrefStatus(AcDb::XrefStatus stat);

    AcDb::XrefNotificationStatus xrefNotificationStatus() const;
    void setXrefNotificationStatus(AcDb::XrefNotificationStatus stat);

    void*   xData() { return mpxdata; }
    void    setxData(void *pXData) { mpxdata = pXData; }

    Acad::ErrorStatus xrefReadSubstatus() const;

private:
    void* mpxdata; // since data already used!
    ACHAR * mpName;
    AcDbObjectId mBtrId;
    // AcDbDatabase* uses base class data() member
    AcDb::XrefStatus mStatus;
    AcDb::XrefNotificationStatus mNotifyStatus;
};


class AcDbXrefGraph : public AcDbGraph
{
public:
    AcDbXrefGraph(AcDbXrefGraphNode* pHostDwg = NULL);
    virtual ~AcDbXrefGraph();

    AcDbXrefGraphNode* xrefNode(const ACHAR * pName) const;
    AcDbXrefGraphNode* xrefNode(AcDbObjectId btrId) const;
    AcDbXrefGraphNode* xrefNode(const AcDbDatabase* pDb) const;

    AcDbXrefGraphNode* xrefNode(int idx) const;
    AcDbXrefGraphNode*  hostDwg() const;

    Adesk::Boolean markUnresolvedTrees ();

    // cycle detection
    virtual Adesk::Boolean findCycles(AcDbGraphNode* pStart = NULL);
};



// =====================================
//      General Utility functions
// =====================================

// Acad.lib only -- Not for use in ObjectDBX
//
Acad::ErrorStatus acedGetCurDwgXrefGraph(AcDbXrefGraph&,
    Adesk::Boolean includeGhosts = Adesk::kFalse);


// =====================================
//      Inline methods
// =====================================

// AcDbXrefGraphNode inlines ...

inline const ACHAR * AcDbXrefGraphNode::name() const { return mpName; }
inline AcDbObjectId AcDbXrefGraphNode::btrId() const { return mBtrId; }
inline AcDbDatabase* AcDbXrefGraphNode::database() const
     { return (AcDbDatabase*)data(); }

inline void AcDbXrefGraphNode::setBtrId(const AcDbObjectId& id)
    { mBtrId = id; }
inline void AcDbXrefGraphNode::setDatabase(AcDbDatabase* pDb)
    { setData(pDb); }

inline bool AcDbXrefGraphNode::isNested() const
    { return !isMarkedAs(kFirstLevel); }

inline AcDb::XrefStatus AcDbXrefGraphNode::xrefStatus() const
    { return mStatus; }
inline void AcDbXrefGraphNode::setXrefStatus(AcDb::XrefStatus stat)
    { mStatus = stat; }
inline AcDb::XrefNotificationStatus
AcDbXrefGraphNode::xrefNotificationStatus() const
    { return mNotifyStatus; }
inline void AcDbXrefGraphNode::setXrefNotificationStatus(
    AcDb::XrefNotificationStatus stat)
    { mNotifyStatus = stat; }


// AcDbXrefGraph inlines ...

inline AcDbXrefGraphNode* AcDbXrefGraph::xrefNode(int idx) const
    { return (AcDbXrefGraphNode*)node(idx); }

inline AcDbXrefGraphNode* AcDbXrefGraph::hostDwg() const
    { return (AcDbXrefGraphNode*)rootNode(); }


#pragma pack (pop)

#endif

