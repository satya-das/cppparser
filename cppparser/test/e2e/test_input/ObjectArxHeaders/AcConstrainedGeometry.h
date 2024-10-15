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
#include "AcDbAssocPersSubentIdPE.h"
#include "AcConstraintGroupNode.h"
#include "AcGeomConstraint.h"
#include "genurb3d.h"
#include "acdb.h"
#pragma pack (push, 8)

class AcConstrainedRigidSet;


/// <summary>
/// This class represents a constrained geometry node in the owning AcDbAssoc2dConstraintGroup.
/// It is the base class for all the kind of supported geometries. 
/// </summary>
///
class ACDB_PORT AcConstrainedGeometry :  public AcConstraintGroupNode
{
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedGeometry);

  /// <summary> 
  /// Returns Boolean indicating if this constrained geometry is read-only --
  /// cannot be modified or transformed, in other words, it is fixed. 
  /// </summary>
  /// <returns> Boolean. </returns>
  ///
  virtual bool isReadOnly() const;

  /// <summary> 
  /// Returns AcDbObjectId of the AcDbAssocGeomDependency object referenced
  /// by this constrained geometry. It maybe Null for some kind of constrained geometry. 
  /// </summary>
  /// <returns> AcDbObjectId. </returns>
  ///
  AcDbObjectId geomDependencyId() const;

  /// <summary> 
  /// Returns pointer to owning AcConstrainedRigidSet object which this constrained geometry
  /// belongs to. One constrained geometry can only stay in one rigid set.
  /// If this geometry is not in a rigid set, NULL is returned. 
  /// </summary>
  /// <returns> pointer to AcConstrainedRigidSet. </returns>
  ///
  AcConstrainedRigidSet* getOwningRigidSet() const;

  // Get the list of Constraints referencing this constrained geometry
  /// <summary> 
  /// Returns the array of pointer to AcGeomConstraint objects which 
  /// reference this constrained geometry. For a bounded line, arc or
  /// bounded ellipse, the array also contains the Coincident constraints
  /// between its implicit points and this constrained geometry.
  /// </summary>
  /// <returns> Return Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getConnectedConstraints(AcArray<AcGeomConstraint*>& apConstraints) const;

  /// <summary> 
  /// Returns the array of pointer to AcGeomConstraint objects between this constrained geometry
  /// and the other constrained geometry pOtherConsGeom.
  /// </summary>
  /// <param name="pOtherConsGeom"> 
  /// The pointer to the other AcConstrainedGeometry object.
  /// </param>
  /// <param name="apConstraints"> 
  /// The returned array of pointer to AcGeomConstraint objects.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getCommonConstraints(AcConstrainedGeometry* pOtherConsGeom, AcArray<AcGeomConstraint*>& apConstraints) const;

  /// <summary> 
  /// Returns the array of pointer to AcConstrainedGeometry objects to which 
  /// this constrained geometry is indirectly connected through the common constraints.
  /// </summary>
  /// <param name="apConsGeoms"> 
  /// The returned array of pointer to AcConstrainedGeometry objects.
  /// </param>
  /// <returns> Returns Acad::eOk if successful. </returns>
  ///
  Acad::ErrorStatus getConnectedGeometries(AcArray<AcConstrainedGeometry*>& apConsGeoms) const;

  /// <summary> 
  /// Returns an array of AcDbFullSubentPaths of the subentities of the AutoCAD
  /// AcDbEntities that correspond to this constrained geometry. Notice that the
  /// output argument is an array, because there may be more than one subentity
  /// corresponding to the AcConstrainedGeometry, but in the great majority of 
  /// cases there will be exactly one subentity.
  /// </summary>
  /// <param name="subentPaths"> 
  /// The returned array of AcDbFullSubentPaths, usually containing exactly one item.
  /// </param>
  ///
  Acad::ErrorStatus getFullSubentPaths(AcDbFullSubentPathArray& subentPaths) const;

protected:

  /// <summary> Protected default constructor. </summary>
  /// 
  AcConstrainedGeometry();
};

/// <summary>
/// This class represents a constrained point node in the owning AcDbAssoc2dConstraintGroup.
/// Usually It holds a reference to a AcDbAssocGeomDependency object which may be
/// the insertion point of a block reference or a grip point of a custom entity.
/// </summary>
///
class ACDB_PORT AcConstrainedPoint: public AcConstrainedGeometry 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedPoint);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  /// <param name="bCreateImp">
  /// Input Boolean indicating whether the implementation object should be created.
  /// The default value is true.
  /// </param>
  ///
  explicit AcConstrainedPoint(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained line is holding on.
  /// </param>
  ///
  AcConstrainedPoint(AcDbObjectId geomDependencyId);

  /// <summary> 
  /// Returns the point position.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  virtual AcGePoint3d point() const ;
}; 

/// <summary><para>
/// This class represents a constrained implicit point node in the owning AcDbAssoc2dConstraintGroup.
/// A constrained implicit point is always associated with a constrained curve, it may the start point,
/// end point, center point or define point (only valid for spline control point now) of the curve.
/// </para><para>
/// A constrained implicit point does not hold a reference to a AcDbAssocGeomDependency object.
/// </para></summary>
///
class ACDB_PORT AcConstrainedImplicitPoint: public AcConstrainedPoint 
{
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedImplicitPoint);

  /// <summary> Default constructor. </summary>
  /// 
  explicit AcConstrainedImplicitPoint(bool bCreateImp = true);

  /// <summary> 
  /// Constructor. 
  /// </summary>
  /// <param name="constrCurvId">
  /// Input Id indicating the constrained curve to which
  /// this implicit point belongs.
  /// </param>
  /// <param name="ptype">
  /// Input ImplicitPointType indicating the type of this implicit point.
  /// </param>
  /// <param name="index">
  /// Input int indicating the define point index of this implicit point.
  /// It is only valid when the point type is kDefineImplicit.
  /// Default value is -1 (invalid index).
  /// </param>
  ///
  AcConstrainedImplicitPoint(AcGraphNode::Id constrCurvId, AcDb::ImplicitPointType ptype, int index = -1);

  /// <summary> 
  /// Returns the type of this implicit point.
  /// </summary>
  /// <returns> ImplicitPointType. </returns>
  ///
  AcDb::ImplicitPointType       pointType()  const;

  /// <summary> 
  /// Returns the define point index of this implicit point.
  /// </summary>
  /// <returns> When the point type is not kDefineImplicit, -1 is returned. </returns>
  ///
  int                     pointIndex() const;

  /// <summary> 
  /// Returns Id of the constrained curve to which
  /// this implicit point belongs.
  /// </summary>
  /// <returns> AcGraphNode::Id. </returns>
  ///
  AcGraphNode::Id constrainedCurveId() const;

  /// <summary> 
  /// Returns the point position.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  virtual AcGePoint3d point() const override;
};

/// <summary>
/// This class represents a constrained curve node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedCurve :  public AcConstrainedGeometry
{
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedCurve);

  /// <summary>
  /// Returns true if this constrained curve is bounded. 
  /// </summary>
  /// <returns> true for bounded curve, otherwise false. </returns>
  ///
  virtual bool isBounded() const;

  /// <summary><para> 
  /// Returns the array of pointer to AcConstrainedImplicitPoint objects which 
  /// belong to this constrained curve.
  /// </para><para>
  /// An unbounded line (xline) does not have constrained implicit point.
  /// </para></summary>
  /// <param name="apImplicitPoints"> 
  /// The returned array of pointer to AcConstrainedImplicitPoint objects.
  /// </param>
  /// <returns> void. </returns>
  ///
  virtual void getConstrainedImplicitPoints(AcArray<AcConstrainedImplicitPoint*>& apImplicitPoints) const;

protected:

  /// <summary> Protected default constructor. </summary>
  /// 
  explicit AcConstrainedCurve(){}
};

/// <summary>
/// This class represents a constrained unbounded line node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedLine: public AcConstrainedCurve 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedLine);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  /// <param name="bCreateImp">
  /// Input Boolean indicating whether the implementation object should be created.
  /// The default value is true.
  /// </param>
  ///
  explicit AcConstrainedLine(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained line is holding on.
  /// </param>
  ///
  AcConstrainedLine(AcDbObjectId geomDependencyId);

  /// <summary> 
  /// Returns an arbitrary point on the unbounded line. 
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d pointOnLine() const;

  /// <summary> 
  /// Returns direction unit vector of the unbounded line. 
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGeVector3d. </returns>
  ///
  AcGeVector3d direction() const;
}; 

/// <summary>
/// This class represents a constrained unbounded construction line node in the owning AcDbAssoc2dConstraintGroup.
/// It does not take any initial value and its position is decided by the constraints applied on it.
/// </summary>
///
class ACDB_PORT AcConstrainedConstructionLine: public AcConstrainedLine 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedConstructionLine);

protected:

  /// <summary> Protected default constructor. </summary>
  /// 
  explicit AcConstrainedConstructionLine();
};

/// <summary>
/// This class represents a constrained unbounded construction line node in the owning AcDbAssoc2dConstraintGroup.
/// Internally it is made coincident to two AcConstrainedPoint objects.
/// </summary>
///
class ACDB_PORT AcConstrained2PointsConstructionLine: public AcConstrainedConstructionLine 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrained2PointsConstructionLine);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  ///
  explicit AcConstrained2PointsConstructionLine(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="point1">
  /// Input first 3D point.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </param>
  /// <param name="point2">
  /// Input second 3D point.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </param>
  ///
  explicit AcConstrained2PointsConstructionLine(const AcGePoint3d& point1, const AcGePoint3d& point2);
};

/// <summary>
/// This class represents a constrained datum unbounded line node in the owning AcDbAssoc2dConstraintGroup.
/// It is read-only and for reference as datum line, e.g. X datum line and Y datum line.
/// </summary>
///
class ACDB_PORT AcConstrainedDatumLine: public AcConstrainedConstructionLine 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedDatumLine);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  ///
  explicit AcConstrainedDatumLine(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="pointOnLine">
  /// Input any 3D point.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </param>
  /// <param name="direction">
  /// Input any 3D vector(must not be zero length).
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </param>
  ///
  explicit AcConstrainedDatumLine(const AcGePoint3d& pointOnLine, const AcGeVector3d& direction);
};

/// <summary>
/// This class represents a constrained bounded line node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedBoundedLine: public AcConstrainedLine
{
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedBoundedLine);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  ///
  explicit AcConstrainedBoundedLine(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained line is holding on.
  /// </param>
  /// <param name="bRay">
  /// Input Boolean indicating whether this bounded line is a ray.
  /// </param>
  ///
  explicit AcConstrainedBoundedLine(AcDbObjectId geomDependencyId, bool bRay);

  /// <summary> 
  /// Returns Boolean indicating whether this bounded line is a ray - a partially bounded
  /// line. In the case that this returns true, the start point represents the
  /// single bounding point, and the ray is considered to point away from this
  /// point in the direction specified by direction(). 
  /// </summary>
  /// <returns> Returns true if it is a ray. </returns>
  ///
  bool isRay() const;

  /// <summary> 
  /// Returns the start point of the bounded line. 
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d startPoint() const;

  /// <summary> 
  /// Returns the start point of the bounded line. It is invalid for ray.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d endPoint() const;

  /// <summary> 
  /// Returns the mid point of the bounded line. It is invalid for ray.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d midPoint() const;
};

/// <summary>
/// This class represents a constrained circle node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedCircle: public AcConstrainedCurve 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedCircle);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  /// <param name="bCreateImp">
  /// Input Boolean indicating whether the implementation object should be created.
  /// The default value is true.
  /// </param>
  ///
  explicit AcConstrainedCircle(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained circle is holding on.
  /// </param>
  ///
  explicit AcConstrainedCircle(AcDbObjectId geomDependencyId);

  /// <summary> 
  /// Returns the radius of the constrained circle.
  /// </summary>
  /// <returns> double. </returns>
  ///
  double radius() const; 

  /// <summary> 
  /// Returns the center point of the constrained circle.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d centerPoint() const;
}; 

/// <summary>
/// This class represents a constrained arc node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedArc: public AcConstrainedCircle 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedArc);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  ///
  explicit AcConstrainedArc(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained arc is holding on.
  /// </param>
  ///
  explicit AcConstrainedArc(AcDbObjectId geomDependencyId);

  /// <summary> 
  /// Returns the start point of the constrained arc.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d startPoint() const;

  /// <summary> 
  /// Returns the end point of the constrained arc.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d endPoint() const;

  /// <summary> 
  /// Returns the mid point of the constrained arc.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d midPoint() const;
};

/// <summary>
/// This class represents a constrained ellipse node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedEllipse: public AcConstrainedCurve 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedEllipse);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  /// <param name="bCreateImp">
  /// Input Boolean indicating whether the implementation object should be created.
  /// The default value is true.
  /// </param>
  ///
  explicit AcConstrainedEllipse(bool bCreateImp = true); 

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained ellipse is holding on.
  /// </param>
  ///
  explicit AcConstrainedEllipse(AcDbObjectId geomDependencyId);

  /// <summary> 
  /// Returns direction unit vector of the major axis of the constrained ellipse.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGeVector3d. </returns>
  ///
  AcGeVector3d direction() const; 

  /// <summary> 
  /// Returns major radius of the constrained ellipse.
  /// The major radius may be smaller than minor radius, this is different from AcGeEllipArc3d.
  /// </summary>
  /// <returns> double. </returns>
  ///
  double majorRadius() const; 

  /// <summary> 
  /// Returns minor radius of the constrained ellipse.
  /// The minor radius may be larger than major radius, this is different from AcGeEllipArc3d.
  /// </summary>
  /// <returns> double. </returns>
  ///
  double minorRadius() const;

  /// <summary> 
  /// Returns the center point of the constrained ellipse.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d centerPoint() const;
};

/// <summary>
/// This class represents a constrained ellipse arc node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedBoundedEllipse : public AcConstrainedEllipse
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedBoundedEllipse);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  ///
  explicit AcConstrainedBoundedEllipse(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained bounded ellipse is holding on.
  /// </param>
  ///
  explicit AcConstrainedBoundedEllipse(AcDbObjectId geomDependencyId);

  /// <summary> 
  /// Returns the start point of the constrained bounded ellipse.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d startPoint() const;

  /// <summary> 
  /// Returns the end point of the constrained bounded ellipse.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d endPoint() const;
};

/// <summary>
/// This class represents a constrained NURBS spline node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedSpline: public AcConstrainedCurve 
{ 
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedSpline);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  ///
  explicit AcConstrainedSpline(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId indicating the AcDbAssocGeomDependency object
  /// to which this constrained spline is holding on.
  /// </param>
  /// <param name="spline">
  /// Input AcGeNurbCurve3d indicating the AcGe representation of this constrained spline
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </param>
  ///
  explicit AcConstrainedSpline(AcDbObjectId geomDependencyId, const AcGeNurbCurve3d& spline);

  /// <summary> 
  /// Returns the AcGeNurbCurve3d representation of the constrained spline.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGeNurbCurve3d. </returns>
  ///
  const AcGeNurbCurve3d nurbSpline() const;

  /// <summary> 
  /// Returns the number of define point of the constrained spline.
  /// Currently, only spline control points are supported. For closed
  /// spline, the number of define point is number of control point minus 1.
  /// </summary>
  /// <returns> int. </returns>
  ///
  int numOfDefinePoints() const;

  /// <summary> 
  /// Returns the define point of the constrained spline.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGePoint3d. </returns>
  ///
  AcGePoint3d definePointAt(int index) const;
};

/// <summary>
/// This class represents a constrained rigid set node in the owning AcDbAssoc2dConstraintGroup.
/// </summary>
///
class ACDB_PORT AcConstrainedRigidSet : public AcConstrainedGeometry
{
public:
  ACRX_DECLARE_MEMBERS(AcConstrainedRigidSet);

  /// <summary> 
  /// Default constructor.
  /// </summary>
  ///
  explicit AcConstrainedRigidSet(bool bCreateImp = true);

  /// <summary> 
  /// constructor.
  /// </summary>
  /// <param name="bScalable">
  /// Input boolean indicating whether this rigid set can be uniformly scaled or not.
  /// </param>
  /// <param name="trans">
  /// Input AcGeMatrix3d indicating the initial transform of this rigid set
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </param>
  ///
  explicit AcConstrainedRigidSet(bool bScalable, const AcGeMatrix3d& trans);

  /// <summary> 
  /// Returns the number of constrained geometries contained.
  /// </summary>
  /// <returns> int. </returns>
  ///
  int                      numOfConstrainedGeoms() const;

  /// <summary> 
  /// Returns pointer to the constrained geometry.
  /// </summary>
  /// <returns> AcConstrainedGeometry*. </returns>
  ///
  AcConstrainedGeometry*   getConstrainedGeomAt(int index) const;

  /// <summary> 
  /// Returns transform of this rigid set.
  /// Relative to the work plane of the owning AcDbAssoc2dConstraintGroup object.
  /// </summary>
  /// <returns> AcGeMatrix3d. </returns>
  ///
  AcGeMatrix3d             transform() const;
};


// For internal use only

/// <summary>
/// Information about the geometric transformation applied to geometric entities 
/// and/or their subentities. For internal use only.
/// </summary>
///
struct ACDB_PORT AcDbAssocTransInfo
{
    /// <summary> The geometric transformation type. </summary>
    enum TransType
    {
        /// <summary> Translation and/or rotation. </summary>
        kGeneral = 0,

        /// <summary> Scaling and/or translation. </summary>
        kScaling,

        /// <summary> Circle radius change only. </summary>
        kRadius,

        /// <summary> Ellipse major radius change only. </summary>
        kMajorRadius,

        /// <summary> Ellipse minor radius change only. </summary>
        kMinorRadius,

        /// <summary> Radius fixed. </summary>
        kFixedRadius,

        /// <summary> Geometry fixed. </summary>
        kFixed,

        /// <summary> Geometry fixed only when possible. </summary>
        kFixWhenPossible,

        /// <summary> Not a valid transformation type. </summary>
        kNone,
    };

    /// <summary> Default constructor. </summary>
    /// 
    AcDbAssocTransInfo() : mRadius(-1.0), mTransType(kGeneral)
    {}

    /// <summary> The type of the transformation applied to the entity or sub-entity. </summary>
    ///
    TransType mTransType;

    /// <summary>
    /// The transformation matrix applied to the entity or sub-entity.
    /// It is only valid when the mTransType is NOT kRadius, kMajorRadius or kMinorRadius.
    /// It is relative to the world coordinate system.
    /// </summary>
    ///
    AcGeMatrix3d mTrans;

    /// <summary>
    /// The radius value to be applied to the entity or sub-entity.
    /// It is only valid when the mTransType is kRadius, kMajorRadius or kMinorRadius.
    /// </summary>
    ///
    double mRadius;
};


/// <summary>
/// The Dragging information of the constrained geometry. For internal use only.
/// </summary>
///
struct ACDB_PORT AcConstrainedGeometryDraggingInfo : public AcDbAssocTransInfo
{
    /// <summary>
    /// The AcDbFullSubentPathArray of the constrained geometries which
    /// share the same transformation.
    /// </summary>
    ///
    AcDbFullSubentPathArray maGeomFullSubentPaths;

    /// <summary>
    /// The actual constrained geometries which are being changed
    /// maGeomFullSubentPaths will be ignored if it is not empty
    /// </summary>
    ///
    AcArray<AcConstrainedGeometry *> maDraggingGeometries;

    /// <summary>
    /// INTERNAL USE ONLY
    /// </summary>
    ///
    static const AcString& getKey();
};

#pragma pack (pop)
