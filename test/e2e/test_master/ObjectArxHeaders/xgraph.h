//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_XGRAPH_H
#  define AD_XGRAPH_H	1
#  include "graph.h"
#  include "AdAChar.h"
#  pragma  pack (push, 8)
class AcDbXrefGraphNode : public AcDbGraphNode
{
public:
  AcDbXrefGraphNode(const ACHAR* pName = NULL, const AcDbObjectId& btrId = AcDbObjectId::kNull, AcDbDatabase* pDb = NULL, AcDb::XrefStatus status = AcDb::kXrfResolved);
  virtual ~AcDbXrefGraphNode();
  const ACHAR* name() const;
  AcDbObjectId btrId() const;
  AcDbDatabase* database() const;
  Acad::ErrorStatus setName(const ACHAR* pName);
  void setBtrId(const AcDbObjectId& id);
  void setDatabase(AcDbDatabase* pDb);
  bool isNested() const;
  AcDb::XrefStatus xrefStatus() const;
  void setXrefStatus(AcDb::XrefStatus stat);
  AcDb::XrefNotificationStatus xrefNotificationStatus() const;
  void setXrefNotificationStatus(AcDb::XrefNotificationStatus stat);
  void* xData()
  {
    return mpxdata;
  }
  void setxData(void* pXData)
  {
    mpxdata = pXData;
  }
  Acad::ErrorStatus xrefReadSubstatus() const;
private:
  void* mpxdata;
  ACHAR* mpName;
  AcDbObjectId mBtrId;
  AcDb::XrefStatus mStatus;
  AcDb::XrefNotificationStatus mNotifyStatus;
};
class AcDbXrefGraph : public AcDbGraph
{
public:
  AcDbXrefGraph(AcDbXrefGraphNode* pHostDwg = NULL);
  virtual ~AcDbXrefGraph();
  AcDbXrefGraphNode* xrefNode(const ACHAR* pName) const;
  AcDbXrefGraphNode* xrefNode(AcDbObjectId btrId) const;
  AcDbXrefGraphNode* xrefNode(const AcDbDatabase* pDb) const;
  AcDbXrefGraphNode* xrefNode(int idx) const;
  AcDbXrefGraphNode* hostDwg() const;
  Adesk::Boolean markUnresolvedTrees();
  virtual Adesk::Boolean findCycles(AcDbGraphNode* pStart = NULL);
};
Acad::ErrorStatus acedGetCurDwgXrefGraph(AcDbXrefGraph&, Adesk::Boolean includeGhosts = Adesk::kFalse);
inline const ACHAR* AcDbXrefGraphNode::name() const
{
  return mpName;
}
inline AcDbObjectId AcDbXrefGraphNode::btrId() const
{
  return mBtrId;
}
inline AcDbDatabase* AcDbXrefGraphNode::database() const
{
  return (AcDbDatabase*) data();
}
inline void AcDbXrefGraphNode::setBtrId(const AcDbObjectId& id)
{
  mBtrId = id;
}
inline void AcDbXrefGraphNode::setDatabase(AcDbDatabase* pDb)
{
  setData(pDb);
}
inline bool AcDbXrefGraphNode::isNested() const
{
  return !isMarkedAs(kFirstLevel);
}
inline AcDb::XrefStatus AcDbXrefGraphNode::xrefStatus() const
{
  return mStatus;
}
inline void AcDbXrefGraphNode::setXrefStatus(AcDb::XrefStatus stat)
{
  mStatus = stat;
}
inline AcDb::XrefNotificationStatus AcDbXrefGraphNode::xrefNotificationStatus() const
{
  return mNotifyStatus;
}
inline void AcDbXrefGraphNode::setXrefNotificationStatus(AcDb::XrefNotificationStatus stat)
{
  mNotifyStatus = stat;
}
inline AcDbXrefGraphNode* AcDbXrefGraph::xrefNode(int idx) const
{
  return (AcDbXrefGraphNode*) node(idx);
}
inline AcDbXrefGraphNode* AcDbXrefGraph::hostDwg() const
{
  return (AcDbXrefGraphNode*) rootNode();
}
#  pragma  pack (pop)
#endif
