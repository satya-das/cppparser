//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_GRAPH_H
#  define AD_GRAPH_H	1
#  include "dbmain.h"
#  pragma  pack (push, 8)
class AcDbGraph;
class AcDbGraphNode : public AcHeapOperators
{
  friend class AcDbGraph;
public:
  AcDbGraphNode(void* pData = NULL);
  virtual ~AcDbGraphNode();
  enum Flags
  {
    kNone = 0x00,
    kVisited = 0x01,
    kOutsideRefed = 0x02,
    kSelected = 0x04,
    kInList = 0x08,
    kListAll = 0x0E,
    kFirstLevel = 0x10,
    kUnresTree = 0x20,
    kAll = 0x2F
  };
  void* data() const;
  void setData(void*);
  int numOut() const;
  int numIn() const;
  AcDbGraphNode* in(int) const;
  AcDbGraphNode* out(int) const;
  Acad::ErrorStatus addRefTo(AcDbGraphNode*);
  Acad::ErrorStatus removeRefTo(AcDbGraphNode*);
  Acad::ErrorStatus disconnectAll();
  AcDbGraph* owner() const;
  bool isMarkedAs(Adesk::UInt8 flags) const;
  Acad::ErrorStatus markAs(Adesk::UInt8 flags);
  Acad::ErrorStatus clear(Adesk::UInt8 flags);
  Acad::ErrorStatus markTree(Adesk::UInt8 flags, AcDbVoidPtrArray* = NULL);
  int numCycleOut() const;
  int numCycleIn() const;
  AcDbGraphNode* cycleIn(int) const;
  AcDbGraphNode* cycleOut(int) const;
  AcDbGraphNode* nextCycleNode() const;
  bool isCycleNode() const;
  void setEdgeGrowthRate(int outEdgeRate, int inEdgeRate);
private:
  AcDbGraphNode(const AcDbGraphNode&);
  AcDbGraphNode& operator =(const AcDbGraphNode&);
  AcDbVoidPtrArray mOutgoing;
  AcDbVoidPtrArray mIncoming;
  void* mpData;
  void setFirstLevel(Adesk::Boolean);
  Adesk::UInt8 mFlags;
  Acad::ErrorStatus setOwner(AcDbGraph*);
  Acad::ErrorStatus resetCycles();
  Acad::ErrorStatus removeCycleRefTo(AcDbGraphNode*);
  Acad::ErrorStatus clearCycles();
  AcDbGraph* mpOwner;
  AcDbVoidPtrArray* mpCycleOut;
  AcDbVoidPtrArray* mpCycleIn;
};
class AcDbGraph : public AcHeapOperators
{
  friend class AcDbGraphNode;
public:
  AcDbGraph(AcDbGraphNode* pRoot = NULL);
  virtual ~AcDbGraph();
  AcDbGraphNode* node(int index) const;
  AcDbGraphNode* rootNode() const;
  int numNodes() const;
  bool isEmpty() const;
  Acad::ErrorStatus addNode(AcDbGraphNode*);
  Acad::ErrorStatus addEdge(AcDbGraphNode* pFrom, AcDbGraphNode* pTo);
  Acad::ErrorStatus delNode(AcDbGraphNode*);
  void reset();
  void clearAll(Adesk::UInt8 flags);
  void getOutgoing(AcDbVoidPtrArray&);
  virtual Adesk::Boolean findCycles(AcDbGraphNode* pStart = NULL);
  Acad::ErrorStatus breakCycleEdge(AcDbGraphNode* pFrom, AcDbGraphNode* pTo);
  void setNodeGrowthRate(int rate);
protected:
  Acad::ErrorStatus clearAllCycles();
private:
  AcDbGraph(const AcDbGraph&);
  AcDbGraph& operator =(const AcDbGraph&);
  AcDbVoidPtrArray mNodes;
  AcDbVoidPtrArray* mpCycleNodes;
  void setDirty();
  bool mDirty;
};
class AcDbGraphStack : public AcHeapOperators
{
public:
  AcDbGraphStack(int initPhysicalLength = 0, int initGrowLength = 8);
  ~AcDbGraphStack();
  Acad::ErrorStatus push(AcDbGraphNode*);
  AcDbGraphNode* pop();
  AcDbGraphNode* top() const;
  bool isEmpty() const;
private:
  AcDbVoidPtrArray mStack;
};
inline void* AcDbGraphNode::data() const
{
  return mpData;
}
inline void AcDbGraphNode::setData(void* pData)
{
  mpData = pData;
}
inline int AcDbGraphNode::numOut() const
{
  return mOutgoing.length();
}
inline int AcDbGraphNode::numIn() const
{
  return mIncoming.length();
}
inline AcDbGraphNode* AcDbGraphNode::in(int idx) const
{
  return (AcDbGraphNode*) mIncoming.at(idx);
}
inline AcDbGraphNode* AcDbGraphNode::out(int idx) const
{
  return (AcDbGraphNode*) mOutgoing.at(idx);
}
inline bool AcDbGraphNode::isMarkedAs(Adesk::UInt8 flag) const
{
  return (this->mFlags & flag) != 0;
}
inline AcDbGraph* AcDbGraphNode::owner() const
{
  return mpOwner;
}
inline Acad::ErrorStatus AcDbGraphNode::setOwner(AcDbGraph* pOwn)
{
  assert(!mpOwner);
  if (mpOwner)
  {
    return Acad::eInvalidOwnerObject;
  }
  mpOwner = pOwn;
  return Acad::eOk;
}
inline int AcDbGraphNode::numCycleOut() const
{
  return mpCycleOut == NULL ? 0 : mpCycleOut->length();
}
inline int AcDbGraphNode::numCycleIn() const
{
  return mpCycleIn == NULL ? 0 : mpCycleIn->length();
}
inline AcDbGraphNode* AcDbGraphNode::cycleOut(int idx) const
{
  return (AcDbGraphNode*) (mpCycleOut == NULL ? NULL : mpCycleOut->at(idx));
}
inline AcDbGraphNode* AcDbGraphNode::cycleIn(int idx) const
{
  return (AcDbGraphNode*) (mpCycleIn == NULL ? NULL : mpCycleIn->at(idx));
}
inline AcDbGraphNode* AcDbGraphNode::nextCycleNode() const
{
  assert(mpCycleOut != NULL);
  return cycleOut(0);
}
inline bool AcDbGraphNode::isCycleNode() const
{
  return mpCycleIn != NULL || mpCycleOut != NULL;
}
inline int AcDbGraph::numNodes() const
{
  return mNodes.length();
}
inline AcDbGraphNode* AcDbGraph::node(int idx) const
{
  return (AcDbGraphNode*) mNodes.at(idx);
}
inline AcDbGraphNode* AcDbGraph::rootNode() const
{
  return (numNodes() > 0) ? node(0) : NULL;
}
inline bool AcDbGraph::isEmpty() const
{
  return numNodes() == 0;
}
inline void AcDbGraph::setDirty()
{
  mDirty = true;
}
inline bool AcDbGraphStack::isEmpty() const
{
  return mStack.isEmpty();
}
inline AcDbGraphNode* AcDbGraphStack::top() const
{
  return isEmpty() ? NULL : (AcDbGraphNode*) mStack.last();
}
#  pragma  pack (pop)
#endif
