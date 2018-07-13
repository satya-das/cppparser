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
// ========= idgraph.h:  AcDbObjectIdGraph classes ================ 
//
//    This header defines classes:
//
//	AcDbObjectIdGraph - a derived class for representing object references
//	AcDbObjectIdGraphNode - each node represents an object id
//
//

#ifndef AD_IDGRAPH_H
#define AD_IDGRAPH_H 1

#include "graph.h"
#include "dbidmap.h"

#pragma pack (push, 8)

// =====================================
//      Object Id Graph Classes
// =====================================


class AcDbObjectIdGraphNode : public AcDbGraphNode
{
public:
    AcDbObjectIdGraphNode(const AcDbObjectId id);
    virtual ~AcDbObjectIdGraphNode();

    AcDbObjectId           id           () const;

private:

    AcDbObjectId        mId;
};


class AcDbObjectIdGraph : public AcDbGraph
{
public:
    AcDbObjectIdGraph();
    virtual ~AcDbObjectIdGraph();

    Acad::ErrorStatus       addNode     (AcDbObjectIdGraphNode *);
    Acad::ErrorStatus       delNode     (AcDbObjectIdGraphNode *);
    AcDbObjectIdGraphNode*  findNode    (const AcDbObjectId) const;
    AcDbObjectIdGraphNode*  idNode      (int idx) const;


private:
    AcDbIdMapping       mIdNodeMap;
};
// =====================================
//      Inline methods
// =====================================

// AcDbObjectIdGraphNode inlines

inline AcDbObjectId AcDbObjectIdGraphNode::id() const
    {return mId; }


// AcDbObjectId inlines ...

inline AcDbObjectIdGraphNode* AcDbObjectIdGraph::idNode(int idx) const
    { return (AcDbObjectIdGraphNode*)node(idx); }

#pragma pack (pop)

#endif

