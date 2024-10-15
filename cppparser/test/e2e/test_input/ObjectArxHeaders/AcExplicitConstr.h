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

#pragma once
#include "AcGeomConstraint.h"
#pragma pack (push, 8)

/// <summary>
/// This class represents a dimensional constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It is the base class for all the kind of dimensional constraints.
/// </summary>
///
class ACDB_PORT AcExplicitConstraint : public AcGeomConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcExplicitConstraint);

  /// <summary> 
  /// Returns AcDbObjectId of the AcDbAssocValueDependency object referenced
  /// by this dimensional constraint.
  /// </summary>
  /// <returns> AcDbObjectId. </returns>
  ///
  AcDbObjectId valueDependencyId() const;

  /// <summary> 
  /// Returns AcDbObjectId of the dimension dependency object referenced
  /// by this dimensional constraint.
  /// </summary>
  /// <returns> AcDbObjectId. </returns>
  ///
  AcDbObjectId dimDependencyId() const;

  /// <summary> 
  /// Set the dimension dependency object referenced
  /// by this dimensional constraint.
  /// </summary>
  /// <param name="dimDependencyId">
  /// Input AcDbObjectId of the new dimension dependency object
  /// </param>
  /// <returns> Acad::eOk if successful </returns>
  ///
  Acad::ErrorStatus setDimDependencyId(const AcDbObjectId& dimDependencyId);

  /// <summary>
  /// Returns the value of the dimensional constraint measured from the
  /// distances/angles/radii of the constained geometries. It the constraint 
  /// is satisfied, it is the same value as the dimension value obtained from 
  /// the AcDbAssocVariable.
  /// </summary>
  ///
  Acad::ErrorStatus getMeasuredValue(double&) const;

protected:

  /// <summary> 
  /// Protected default constructor. 
  /// </summary>
  /// 
  AcExplicitConstraint(){};
};

/// <summary>
/// This class represents a distance constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained geometries (normally two points).
/// </summary>
///
class ACDB_PORT AcDistanceConstraint: public AcExplicitConstraint
{ 
public:
  ACRX_DECLARE_MEMBERS(AcDistanceConstraint);

  /// <summary>
  /// The direction type of this distance constraint. It is mainly used to 
  /// indicate how the distance between the two geometries are measured.
  /// </summary>
  ///
  enum DirectionType
  {
    /// <summary>
    /// Not directed distance.
    /// The minimum distance between the two geometries is measured.
    /// </summary>
    ///
    kNotDirected         = 0,

    /// <summary>
    /// Directed distance with fixed direction.
    /// The distance between the two geometries is measured along the fixed direction.
    /// </summary>
    ///
    kFixedDirection         ,

    /// <summary>
    /// Directed distance with relative direction.
    /// The distance between the two geometries is measured along the direction
    /// which is perpendicular to an existing constraint line.
    /// </summary>
    ///
    kPerpendicularToLine    ,

    /// <summary>
    /// Directed distance with relative direction.
    /// The distance between the two geometries is measured along the direction
    /// which is parallel to an existing constraint line.
    /// </summary>
    ///
    kParallelToLine
  };

  /// <summary> 
  /// Default constructor.
  /// The direction type is set to kNotDirected.
  /// </summary>
  /// 
  AcDistanceConstraint(bool bCreateImp = true);

  /// <summary> 
  /// Constructor.
  /// The direction type is set to kFixedDirection.
  /// </summary>
  /// <param name="direction">
  /// Input AcGeVector3d indicating the fixed direction which is used to
  /// measure the distance. The vector length must not be zero.
  /// </param>
  /// 
  AcDistanceConstraint(const AcGeVector3d& direction);

  /// <summary> 
  /// Constructor.
  /// The direction type is set to kPerpendicularToLine or kParallelToLine.
  /// </summary>
  /// <param name="consLineId">
  /// Input AcGraphNode::Id indicating the constrained line whose direction
  /// is used to measure the distance.
  /// </param>
  /// <param name="type">
  /// Input DirectionType indicating the direction type which must be either
  /// kPerpendicularToLine or kParallelToLine.
  /// </param>
  /// 
  AcDistanceConstraint(const AcGraphNode::Id consLineId, DirectionType type = kPerpendicularToLine);

  /// <summary>
  /// Returns the direction type of this distance constraint.
  /// </summary>
  /// <returns> Returns DirectionType. </returns>
  ///
  DirectionType directionType() const;

  /// <summary>
  /// Returns the fixed direction of this distance constraint.
  /// Only valid when the direction type is kFixedDirection.
  /// </summary>
  /// <returns> Returns AcGeVector3d. </returns>
  ///
  AcGeVector3d                    direction()           const;

  /// <summary>
  /// Returns the constrained line id.
  /// Only valid when the direction type is kPerpendicularToLine or kParallelToLine.
  /// </summary>
  /// <returns> Returns AcGraphNode::Id. </returns>
  ///
  AcGraphNode::Id         constrainedLineId()   const;
};

/// <summary>
/// This class represents a angle constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between two constrained lines.
/// </summary>
///
class ACDB_PORT AcAngleConstraint: public AcExplicitConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcAngleConstraint);

  /// <summary>
  /// The angle sector type of this angle constraint. It is used to 
  /// indicate how the angle between the two lines is measured.
  /// </summary>
  ///
  enum SectorType
  {
    /// <summary>
    /// The angle measured from the forward direction of line 1 to 
    /// the forward direction of line 2 anticlockwise.
    /// </summary>
    ///
    kParallelAntiClockwise = 0,

    /// <summary>
    /// The angle measured from the forward direction of line 1 to 
    /// the non forward direction of line 2 clockwise.
    /// </summary>
    ///
    kAntiParallelClockwise = 1,

    /// <summary>
    /// The angle measured from the forward direction of line 1 to 
    /// the forward direction of line 2 clockwise.
    /// </summary>
    ///
    kParallelClockwise = 2,

    /// <summary>
    /// The angle measured from the forward direction of line 1 to 
    /// the non forward direction of line 2 anticlockwise.
    /// </summary>
    ///
    kAntiParallelAntiClockwise = 3,    
  };

  /// <summary> 
  /// Default constructor.
  /// The angle sector type is set to kParallelAntiClockwise.
  /// </summary>
  /// 
  AcAngleConstraint(bool bCreateImp = true);

  /// <summary> 
  /// Constructor.
  /// </summary>
  /// <param name="type">
  /// Input SectorType indicating the angle sector which is used to
  /// measure the angle.
  /// </param>
  /// 
  AcAngleConstraint(AcAngleConstraint::SectorType type);

  /// <summary>
  /// Returns the angle sector type of this angle constraint.
  /// </summary>
  /// <returns> Returns SectorType. </returns>
  ///
  SectorType sectorType() const;

  /// <summary> <para>
  /// Sets a multiplier that is used to multiply angles obtained from 
  /// AcDbAssocValueDependencies that depend on AcDbAssocVariables to convert
  /// the angles to radians. It is needed because the expression evaluator used 
  /// by AcDbAssocVariables considers all angles to be in degrees. To convert
  /// from degrees to radians, the multiplier needs to be set to Pi/180.
  /// If no angle multiplier is set, the default is Pi/180.
  /// </para> <para>
  /// For now there is just one global multiplier so that AcDbAssocVariables 
  /// can store angles in degrees, not in radians.  It is just a stop gap 
  /// measure until we figure out how to handle units. 
  /// </para> </summary>
  /// <param name="multiplier"> The angle multiplication factor. </param>
  ///
  static void setAngleMultiplier(double multiplier);

  /// <summary> Returns the current angle multipiler. </summary>
  /// <returns> The current angle multipiler. The default is Pi/180.</returns>
  ///
  static double angleMultiplier();
};

/// <summary>
/// This class represents a angle constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied between 3 constrained points.
/// </summary>
///
class ACDB_PORT Ac3PointAngleConstraint: public AcAngleConstraint 
{ 
public:
  ACRX_DECLARE_MEMBERS(Ac3PointAngleConstraint);

  /// <summary> 
  /// Default constructor.
  /// The angle sector type is set to kParallelAntiClockwise.
  /// </summary>
  /// 
  Ac3PointAngleConstraint(bool bCreateImp = true);

  /// <summary> 
  /// Constructor.
  /// </summary>
  /// <param name="type">
  /// Input SectorType indicating the angle sector which is used to
  /// measure the angle.
  /// </param>
  /// 
  Ac3PointAngleConstraint(AcAngleConstraint::SectorType type);
};

/// <summary>
/// This class represents a radius or diameter constraint node in the owning AcDbAssoc2dConstraintGroup.
/// It can be applied on one circle(arc) or ellipse(bounded ellipse).
/// </summary>
///
class ACDB_PORT AcRadiusDiameterConstraint : public AcExplicitConstraint
{
public:
  ACRX_DECLARE_MEMBERS(AcRadiusDiameterConstraint);

  /// <summary>
  /// The constraint type of this constraint. It is used to 
  /// indicate whether radius or diameter is measured.
  /// </summary>
  ///
  enum RadiusDiameterConstrType
  { 
    /// <summary>
    /// The radius of a constrained circle or arc is measured.
    /// </summary>
    ///
    kCircleRadius   = 0,

    /// <summary>
    /// The diameter of a constrained circle or arc is measured.
    /// </summary>
    ///
    kCircleDiameter    ,

    /// <summary>
    /// The minor radius of a constrained (bounded) ellipse is measured.
    /// </summary>
    ///
    kMinorRadius       ,

    /// <summary>
    /// The major radius of a constrained (bounded) ellipse is measured.
    /// </summary>
    ///
    kMajorRadius
  }; 

  /// <summary> 
  /// Default constructor.
  /// The constraint type is set to kCircleRadius.
  /// </summary>
  /// 
  AcRadiusDiameterConstraint(bool bCreateImp = true);

  /// <summary> 
  /// Constructor.
  /// </summary>
  /// <param name="type">
  /// Input RadiusDiameterConstrType indicating the constraint type.
  /// </param>
  /// 
  AcRadiusDiameterConstraint(RadiusDiameterConstrType type);

  /// <summary>
  /// Returns the constraint type of this constraint.
  /// </summary>
  /// <returns> Returns RadiusDiameterConstrType. </returns>
  ///
  RadiusDiameterConstrType constrType() const;
};

#pragma pack (pop)
