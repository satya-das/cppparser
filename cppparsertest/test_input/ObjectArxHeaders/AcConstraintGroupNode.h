//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcGraphNode.h"
#pragma pack (push, 8)

// Forward class declarations.
//
class AcImpConstraintGroupNode;
class AcDbImpAssoc2dConstraintGroup;
class AcDbAssoc2dConstraintGroupUtil;

/// <summary> <para>
/// This class represents a node owned by AcDbAssoc2dConstraintGroup.
/// Usually a node is connected with multiple other nodes and the connection  
/// between two nodes is not directed. 
/// </para> <para>
/// A AcConstraintGroupNode object should always be created and deleted through
/// higher level APIs and the memory pointed by it is internal held and should 
/// never be released by user directly.
/// </para>
/// </summary>
///
class ACDB_PORT AcConstraintGroupNode : public AcGraphNode
{
public:
  ACRX_DECLARE_MEMBERS(AcConstraintGroupNode);

  /// <summary> Default destructor. </summary>
  ///
  virtual ~AcConstraintGroupNode();

  /// <summary> 
  /// This function returns the AcDbObjectId of its owning AcDbAssoc2dConstraintGroup. 
  /// If this node has not been added into a AcDbAssoc2dConstraintGroup, AcDbObjectId::kNull
  /// is returned. 
  /// </summary>
  /// <returns> AcDbObjectId. </returns>
  ///
  AcDbObjectId owningConstraintGroupId()const;

protected:

  /// <summary> Protected default constructor. </summary>
  /// 
  AcConstraintGroupNode();

  friend class AcDbImpAssoc2dConstraintGroup;
  friend class AcDbAssoc2dConstraintGroupEvalHelper;
  friend class AcDbAssoc2dConstaintGroupCloningHelper;
};

#pragma pack (pop)
