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
// DESCRIPTION:
//
// AcDbAssoc2dConstraintGroup class. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocAction.h"
#include "AcConstraintGroupNode.h"
#include "AcConstrainedGeometry.h"
#include "AcGeomConstraint.h"
#include "AcExplicitConstr.h"
#pragma pack (push, 8)

class AcAutoConstrainEvaluationCallback;

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)  (P)
#endif

/// <summary> <para>
/// The AcDbAssoc2dConstraintGroup class represents a set of geometric constraint 
/// relations between subentities of geometric entities. All the geometries must
/// lie in a single plane. 
/// </para> <para>
/// The AcDbAssoc2dConstraintGroup object owns the constraints that are derived 
/// from the AcGeomConstraint class, and "proxies" of the constrained geometried, 
/// derived from AcConstrainedGeometry class. AcConstrainedGeometries often 
/// refer to subentities of AutoCAD entities and the AcDbAssoc2dConstraintGroup 
/// owns AcDbAssocGeomDepedencies on these entities. It also owns 
/// AcDbAssocValueDependencies on the AcDbAssocVariables that are the values of 
/// dimensional constraints (represented by classes derived from AcExplicitConstraint).
/// </para> <para>
/// If the dimensional constraint has a graphical representation, such as in the 
/// form of an AcDbDimension entity, the AcExplicitConstraint also owns 
/// AcdbAssocDependency owning an object derived from AcDbAssocDimDependencyBody 
/// that facilitates the interaction between the AcExplicitConstraint, the 
/// AcDbAssocVariable keeping the value of the dimensional constraint, and the 
/// AcDbDimension (or other object/entity) that serves as a graphical representation 
/// of the dimensional constraint.
/// </para> <para>
/// The evaluate() method of this action takes the current properties of the 
/// referenced geometries and the current values of the variables referenced by 
/// AcExplicitConstraints. Then it invokes a constraint solver that finds new 
/// positions and shapes of the constrained geometries so that they satisfy the 
/// constraints. Finally the referenced geometries are updated to their new 
/// positions and shapes. The evaluate method call may fail if a solution 
/// satisfying all the constraints can not be found.
/// </para> </summary>
///
class ACDB_PORT AcDbAssoc2dConstraintGroup : public AcDbAssocAction
{
public:
  ACRX_DECLARE_MEMBERS(AcDbAssoc2dConstraintGroup);

  /// <summary> The solution status of this constraint group. </summary>
  ///
  enum SolutionStatus
  {
    /// <summary>
    /// All constrained geometries are fully constrained.
    /// The degree of freedom of the entire model is 0.
    /// </summary>
    ///
    kWellDefined = 0,

    /// <summary>
    /// Some or all constrained geometries are under constrained.
    /// The degree of freedom of the entire model is larger than 0.
    /// </summary>
    ///
    kUnderConstrained,

    /// <summary>
    /// Some or all constrained geometries are over constrained.
    /// Normally this is because duplicate or redundant constraints are added.
    /// </summary>
    ///
    kOverConstrained,

    /// <summary>
    /// Some or all constrained geometries/constraints are inconsistent.
    /// Normally this is because invalid constraints are added.
    /// For example, two lines are made both parallel and perpendicular.
    /// </summary>
    ///
    kInconsistent,

    /// <summary>
    /// Some or all constrained geometries/constraints are not evaluated.
    /// Normally this means new constrained geometries or constraints are
    /// added since last evaluation.
    /// </summary>
    ///
    kNotEvaluated,

    /// <summary>
    /// Not able to get the solution status.
    /// Normally this means fatal errors.
    /// </summary>
    ///
    kNotAvailable,

    /// <summary>
    /// Evaluation produced result that may be considered valid by DCM but is
    /// rejected by the client code, such as when degenerate geometry was created
    /// and the client code does not want to accept it.
    /// </summary>
    ///
    kRejectedByClient,
  };

  /// <summary>
  /// Default constructor.
  /// </summary>
  /// <param name="plane">
  /// Input AcGePlane of the newly created constraint group object.
  /// Default value is AcGePlane::kXYPlane.
  /// </param>
  ///
  AcDbAssoc2dConstraintGroup(const AcGePlane& plane = AcGePlane::kXYPlane);

  /// <summary> 
  /// Gets the work plane of this constraint group. This work plane defines the 
  /// mapping from the internal coordinate system of the constraint group in which 
  /// AcConstrainedGeometries and AcGeomConstraints are represented, to the world 
  /// coordinate system in which the referenced constrained AcDbEntities are 
  /// represented.
  /// </summary>
  /// <returns> AcGePlane </returns>
  ///
  const AcGePlane getWorkPlane() const;

  /// <summary> 
  /// Sets the work plane of this constraint group. This API 
  /// re-initializes all AcConstrainedGeometry objects owned by it.
  /// It is important to transform the constrained entities to the
  /// new work plane before this API is called, otherwise, some
  /// constraints might be erased during the next evaluation
  /// </summary>
  /// <param name="newPlane"> The given new work plane. </param>
  /// <returns> void </returns>
  ///
  void setWorkPlane(const AcGePlane& newPlane);

  /// <summary> 
  /// Transforms the work plane of the constraint group by the rigid motion
  /// component of the transformation matrix. If the transformation matrix also 
  /// contains a uniform scaling factor, it removes all AcExplicitConstraint nodes.
  /// If the transformation matrix contains a general component, it removes all
  /// AcGeomConstraint nodes.
  /// </summary>
  /// <param name="transform"> The given transformation matrix. </param>
  /// <returns> Returns Acad::eOk. </returns>
  ///
  Acad::ErrorStatus transformActionBy(const AcGeMatrix3d& transform); 

  /// <summary> 
  /// Get the remaining DOF (Degree of Freedom) of this constraint group.
  /// It includes the positional DOF of a well-defined model. 
  /// </summary>
  /// <returns>int</returns>
  ///
  int getDOF();

  /// <summary> 
  /// Get the solution evaluation status of this constraint group.
  /// Normally this method should only be called after an evaluation
  /// </summary>
  /// <param name="bAlsoCheckForConstraints">
  /// Input boolean indicating if need to check constraints.
  /// Default value is true.
  /// </param>
  /// <returns>SolutionStatus</returns>
  ///
  SolutionStatus solutionStatus(bool bAlsoCheckForConstraints = true) const;

  /// <summary> 
  /// Get the evaluation status of the passed in constrained geometry.
  /// Normally this method should only be called after an evaluation
  /// </summary>
  /// <param name="pConsGeom">
  /// Input pointer to AcConstrainedGeometry indicating the constrained
  /// geometry object to be checked.
  /// </param>
  /// <returns>SolutionStatus</returns>
  ///
  SolutionStatus geometryStatus(const AcConstrainedGeometry* pConsGeom) const;

  /// <summary> 
  /// Get the evaluation status of the passed in constraint.
  /// </summary>
  /// <param name="pConstraint">
  /// Input pointer to AcGeomConstraint indicating the constraint object to be checked.
  /// </param>
  /// <returns>SolutionStatus</returns>
  ///
  SolutionStatus constraintStatus(const AcGeomConstraint* pConstraint) const;

  /// <summary> 
  /// Create and add a new AcConstrainedGeometry object into this constraint group.
  /// Caller should not cache the pointer returned for future use.
  /// instead caller may cache the node id of AcConstrainedGeometry.
  /// <seealso cref="AcConstraintGroupNode::nodeId"/>
  /// </summary>
  /// <param name="subentPath">
  /// Input AcDbFullSubentPath  of the constrained entity, down to the subentity level.
  /// Only AcDb::kEdgeSubentType and AcDb::kVertexSubentType are valid subent types.
  /// The vertex subent must NOT be edge vertex.
  /// </param>
  /// <param name="pConsGeom">
  /// Output pointer to AcConstrainedGeometry.
  /// If the corresponding constrained geometry is already there, pConsGeom is set to 
  /// point to the existing AcConstrainedGeometry object and Acad::eAlreadyInGroup returned.
  /// If the constrained geometry is not created successfully, pConsGeom is set to NULL.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus addConstrainedGeometry(const AcDbFullSubentPath& subentPath, AcConstrainedGeometry*& pConsGeom);

  /// <summary> 
  /// Delete an existing AcConstrainedGeometry object which is internally held.
  /// This function also remove and erase the AcDbAssocGeomDependency object
  /// from this constraint group action.
  /// </summary>
  /// <param name="geomDependencyId">
  /// Input AcDbObjectId of the AcDbAssocGeomDependency object. 
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus deleteConstrainedGeometry(const AcDbObjectId& geomDependencyId);

  /// <summary> 
  /// Get pointer to the corresponding internally held AcConstrainedGeometry.
  /// The pointer returned might be temporary and caller should not cache it
  /// for future use, instead caller may cache the node id of AcConstrainedGeometry.
  /// <seealso cref="AcConstraintGroupNode::nodeId"/>
  /// </summary>
  /// <param name="fullSubentPath">
  /// Input AcDbFullSubentPath of the constrained entity, down to the subentity level.
  /// Only vertex or edge subentity type can be passed in, otherwise Acad::eInvalidInput returned
  /// </param>
  /// <param name="pConsGeom">
  /// Output pointer to AcConstrainedGeometry.
  /// If the constrained geometry is not found, pConsGeom is set to NULL.
  /// </param>
  /// <param name="bCreateArcLineMid">
  /// Input Boolean indicating if create implicit midpoint of arc or line segment if it is not there.
  /// Default value is false.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus getConstrainedGeometry(const AcDbFullSubentPath& fullSubentPath,
                                           AcConstrainedGeometry*&   pConsGeom,
                                           bool bCreateArcLineMid = false);

  /// <summary> 
  /// Get pointer to the corresponding internally held AcConstrainedGeometry.
  /// The pointer returned might be temporary and caller should not cache it
  /// for future use, instead caller may cache the node id of AcConstrainedGeometry.
  /// <seealso cref="AcConstraintGroupNode::nodeId"/>
  /// </summary>
  /// <param name="pGeomDependency">
  /// Input pointer to AcDbAssocGeomDependency of the constrained entity.
  /// The AcDbAssocGeomDependency object maybe transient, in other words,
  /// not added into the database yet.
  /// </param>
  /// <param name="pConsGeom">
  /// Output pointer to AcConstrainedGeometry.
  /// If the constrained geometry is not found, pConsGeom is set to NULL.
  /// </param>
  /// <param name="pPtType">
  /// Input pointer to ImplicitPointType indicating the implicit
  /// point type of a constrained curve. Only present when caller want to retrieve the
  /// AcConstrainedImplicitPoint of a AcConstrainedCurve.
  /// Default value is NULL.
  /// </param>
  /// <param name="defPtIndex">
  /// Input integer index of define points of a parametric curve. Currently only control points
  /// of a spline are supported. It is only valid when the implicit point type is kDefineImplicit.
  /// Default value is -1(invalid index value).
  /// </param>
  /// <param name="bCreateArcLineMid">
  /// Input Boolean indicating if create implicit midpoint of arc or line segment if it is not there.
  /// Default value is false.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus getConstrainedGeometry(const AcDbAssocGeomDependency* pGeomDependency,
                                           AcConstrainedGeometry*&   pConsGeom,
                                           AcDb::ImplicitPointType* pPtType = NULL,
                                           int defPtIndex = -1,
                                           bool bCreateArcLineMid = false);

  /// <summary> 
  /// Get all AcConstrainedGeometry objects in this constraint group,
  /// including AcConstraintImplicitPoint objects which are associated
  /// with corresponding AcConstrainedCurve objects.
  /// </summary>
  /// <param name="aConstGeom">
  /// Output AcArray of the AcConstrainedGeometry objects. 
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus getConstrainedGeometries(AcArray<AcConstrainedGeometry*>& aConstGeom) const;

  /// <summary> 
  /// Create and add a geometrical constraint into this constraint group.
  /// </summary>
  /// <param name="type">
  /// Input AcGeomConstraint::GeomConstraintType indicating the type of constraint to be created. 
  /// </param>
  /// <param name="aPaths">
  /// Input AcArray of the AcDbFullSubentPath which can be mapped to AcConstrainedGeometry. 
  /// </param>
  /// <param name="ppNewConstraint">
  /// Output pointer to AcGeomConstraint* pointing the newly created AcGeomConstraint object.
  /// Default value is NULL.
  /// </param>
  /// <param name="pUCSCoord">
  /// Optionally input pointer to AcGeMatrix3d which is used as UCS coordinate. This parameter
  /// is only used when Horizontal or Vertical constraint is applied
  /// Default value is NULL.
  /// </param>
  /// <returns>
  /// Returns Acad::eOk if successful.
  /// Returns Acad::eFailedToAddConstraint if the constraint cannot be added in because of
  /// over-constrained or inconsistent model.
  /// Returns Acad::eAlreadyInGroup if a same type of constraint is already there.
  /// Returns Acad::eInvalidInput or Acad::eNotApplicable for other errors.
  /// </returns>
  ///
  Acad::ErrorStatus addGeometricalConstraint(AcGeomConstraint::GeomConstraintType type, 
                                             const AcDbFullSubentPathArray& aPaths,
                                             AcGeomConstraint** ppNewConstraint  = NULL,
                                             const AcGeMatrix3d* pUCSCoord = NULL);

  /// <summary> 
  /// Create and add a geometrical constraint into this constraint group.
  /// </summary>
  /// <param name="type">
  /// Input AcGeomConstraint::GeomConstraintType indicating the type of constraint to be created. 
  /// </param>
  /// <param name="apConsGeoms">
  /// Input AcArray of the AcConstrainedGeometry. 
  /// </param>
  /// <param name="ppNewConstraint">
  /// Output pointer to AcGeomConstraint* pointing the newly created AcGeomConstraint object.
  /// Default value is NULL.
  /// </param>
  /// <param name="pUCSCoord">
  /// Optionally input pointer to AcGeMatrix3d which is used as UCS coordinate. This parameter
  /// is only used when Horizontal or Vertical constraint is applied
  /// Default value is NULL.
  /// </param>
  /// <returns>
  /// Returns Acad::eOk if successful.
  /// Returns Acad::eFailedToAddConstraint if the constraint cannot be added in because of
  /// over-constrained or inconsistent model.
  /// Returns Acad::eAlreadyInGroup if a same type of constraint is already there.
  /// Returns Acad::eInvalidInput or Acad::eNotApplicable for other errors.
  /// </returns>
  ///
  Acad::ErrorStatus addGeometricalConstraint(AcGeomConstraint::GeomConstraintType type,
                                             const AcArray<AcConstrainedGeometry*>& apConsGeoms,
                                             AcGeomConstraint** ppNewConstraint  = NULL,
                                             const AcGeMatrix3d* pUCSCoord = NULL);

  /// <summary> 
  /// Create and add a distance constraint into this constraint group.
  /// </summary>
  /// <param name="pConsGeom1">
  /// Input pointer to the first AcConstrainedGeometry object.
  /// </param>
  /// <param name="pConsGeom2">
  /// Input pointer to the second AcConstrainedGeometry object.
  /// </param>
  /// <param name="directionType">
  /// Input AcDistanceConstraint::DirectionType indicating the direction type
  /// of the distance constraint to be created.
  /// </param>
  /// <param name="valueDependencyId">
  /// Input object id of the value dependency object. 
  /// </param>
  /// <param name="pFixedDirection">
  /// Input pointer to AcGeVector3d indicating the fixed direction of 
  /// the distance constraint to be created. It will be used only when
  /// the directionType is kFixedDirection.
  /// Relative to the World Coordinate System.
  /// </param>
  /// <param name="pDirectionLine">
  /// Input pointer to AcConstrainedLine object indicating the relative
  /// direction of the distance constraint to be created. It will be used only 
  /// when the directionType is kPerpendicularToLine or kParallelToLine.
  /// </param>
  /// <param name="ppNewDisConstraint">
  /// Output pointer to AcDistanceConstraint* pointing the newly created AcDistanceConstraint object.
  /// Default value is NULL.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus addDistanceConstraint(AcConstrainedGeometry* pConsGeom1,
                                          AcConstrainedGeometry* pConsGeom2,
                                          AcDistanceConstraint::DirectionType directionType,
                                          AcDbObjectId valueDependencyId,
                                          AcDbObjectId dimDependencyId, // May be null
                                          const AcGeVector3d* pFixedDirection = NULL,
                                          const AcConstrainedLine* pDirectionLine = NULL,
                                          AcDistanceConstraint** ppNewDisConstraint = NULL);

  /// <summary> 
  /// Create and add an angle constraint into this constraint group.
  /// </summary>
  /// <param name="pConsLine1">
  /// Input pointer to AcConstrainedLine object 
  /// </param>
  /// <param name="pConsLine2">
  /// Input pointer to AcConstrainedLine object 
  /// </param>
  /// <param name="sectorType">
  /// Input AcAngleConstraint::SectorType indicating the angle sector to measure. 
  /// </param>
  /// <param name="valueDependencyId">
  /// Input object id of the value dependency object. 
  /// </param>
  /// <param name="dimDependencyId">
  /// Input object id of the dimension dependency object. 
  /// </param>
  /// <param name="ppNewAngConstraint">
  /// Output pointer to AcAngleConstraint* pointing the newly created AcAngleConstraint object.
  /// Default value is NULL.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus addAngleConstraint(AcConstrainedLine* pConsLine1,
                                       AcConstrainedLine* pConsLine2,
                                       AcAngleConstraint::SectorType sectorType,
                                       AcDbObjectId valueDependencyId,
                                       AcDbObjectId dimDependencyId, // May be null
                                       AcAngleConstraint** ppNewAngConstraint = NULL);

  /// <summary> 
  /// Create and add a 3point angle constraint into this constraint group.
  /// </summary>
  /// <param name="pConsPoint1">
  /// Input pointer of the first (angle) point which must be a kind of
  /// AcConstraintPoint 
  /// </param>
  /// <param name="pConsPoint2">
  /// Input pointer of the second point which must be a kind of
  /// AcConstraintPoint 
  /// </param>
  /// <param name="pConsPoint3">
  /// Input pointer of the third point which must be a kind of
  /// AcConstraintPoint 
  /// </param>
  /// <param name="sectorType">
  /// Input AcAngleConstraint::SectorType indicating the angle sector to measure. 
  /// </param>
  /// <param name="valueDependencyId">
  /// Input object id of the value dependency object. 
  /// </param>
  /// <param name="dimDependencyId">
  /// Input object id of the dimension dependency object. 
  /// </param>
  /// <param name="ppNewAngConstraint">
  /// Output pointer to Ac3PointAngleConstraint* pointing the newly created Ac3PointAngleConstraint object.
  /// Default value is NULL.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  Acad::ErrorStatus add3PointAngleConstraint(AcConstrainedPoint* pConsPoint1,
                                       AcConstrainedPoint* pConsPoint2,
                                       AcConstrainedPoint* pConsPoint3,
                                       AcAngleConstraint::SectorType sectorType,
                                       AcDbObjectId valueDependencyId,
                                       AcDbObjectId dimDependencyId, // May be null
                                       Ac3PointAngleConstraint** ppNewAngConstraint = NULL);
  /// <summary> 
  /// Create and add a radius or diameter constraint into this constraint group.
  /// </summary>
  /// <param name="pConsGeom">
  /// Input pointer to AcConstrainedGeometry object which must be a kind of
  /// AcConstrainedCircle or AcConstrainedEllipse.
  /// </param>
  /// <param name="type">
  /// Input AcRadiusDiameterConstraint::RadiusDiameterConstrType indicating the type of constraint to be created. 
  /// </param>
  /// <param name="valueDependencyId">
  /// Input object id of the value dependency object. 
  /// </param>
  /// <param name="ppNewRadDiaConstraint">
  /// Output pointer to AcRadiusDiameterConstraint* pointing the newly created AcRadiusDiameterConstraint object.
  /// Default value is NULL.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus addRadiusDiameterConstraint(AcConstrainedGeometry* pConsGeom,
                                                AcRadiusDiameterConstraint::RadiusDiameterConstrType type,
                                                AcDbObjectId valueDependencyId,
                                                AcDbObjectId dimDependencyId, // May be null
                                                AcRadiusDiameterConstraint** ppNewRadDiaConstraint = NULL);

  /// <summary> 
  /// Delete an existing AcGeomConstraint object which is internally held.
  /// </summary>
  /// <param name="pGeomConst">
  /// Input AcGeomConstraint indicating the constraint to be deleted.
  /// If pGeomConst is owned by a composite constraint, Acad::eInvalidInput is returned.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus deleteConstraint(AcGeomConstraint* pGeomConst);

  /// <summary> 
  /// Get all AcGeomConstraint objects in this constraint group,
  /// including topological and dimensional constraints
  /// </summary>
  /// <param name="apConstraints">
  /// Output AcArray of the AcGeomConstraint objects. 
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus getConstraints(AcArray<AcGeomConstraint*>& apConstraints) const;

  /// <summary> 
  /// define constraints that can be added to an under-constrained model.
  /// </summary>
  /// <param name="aPaths">
  /// List of subentites which are to be constrained automatically.
  /// </param>
  /// <param name="tol">
  /// Reference to AcGeTol to define distance tolerance as well as angle tolerance.
  /// AcGeTol::equalPoint() defines distance tolerance and AcGeTol::equalVector()
  /// defines angle tolerance. Angle tolerance is in radians of angle.
  /// </param>
  /// <param name="pCallback">
  /// Pointer to autoconstraint evaluation callback. This callback will implement constraint
  /// priority and priority override.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  /// 
  Acad::ErrorStatus autoConstrain(const AcDbFullSubentPathArray& aPaths,
                                  const AcGeTol& tol,
                                  AcAutoConstrainEvaluationCallback* pCallback);

  /// <summary> 
  /// Get all AcDbAssocGeomDependency objects which are connected by constraints.
  /// </summary>
  /// <param name="srcGeomDependencyIds">
  /// Input AcDbObjectIdArray indicating the source AcDbAssocGeomDependency objects. 
  /// </param>
  /// <param name="allConnectedGeomDependencyIds">
  /// Output AcDbObjectIdArray indicating the all the connected AcDbAssocGeomDependency objects.
  /// It contains all the source AcDbAssocGeomDependency objects.
  /// </param>
  /// <returns>Returns Acad::eOk if successful.</returns>
  ///
  Acad::ErrorStatus getAllConnectedGeomDependencies(const AcDbObjectIdArray& srcGeomDependencyIds,
                                                    AcDbObjectIdArray& allConnectedGeomDependencyIds) const;

  /// <summary> 
  /// Get pointer to AcConstraintGroupNode object.
  /// </summary>
  /// <param name="nodeId">
  /// Input id of AcGraphNode. 
  /// </param>
  /// <returns>Returns pointer to AcConstraintGroupNode if successful, otherwise NULL</returns>
  ///
  AcConstraintGroupNode* getGroupNodePtr(const AcGraphNode::Id nodeId) const;

  /// <summary> 
  /// Regenerate the internal dimension system.
  /// For internal use only.
  /// </summary>
  /// <returns>Returns void</returns>
  ///
  void regenDimensionSystem();

  /// <summary>
  /// Called by the client code to inform the constraint group that dependent 
  /// entity for <paramref name="pGeomDependency"/> has been mirrored. The 
  /// constraint group then mirrors the implicit points for the constrained 
  /// curve for the given geom dependency. For the majority of constrained curves
  /// it is just a no-op, but for some curves (such as for AcConstrainedArc) 
  /// the implicit points needs to be actually updated. 
  /// </summary>
  /// <param name="pGeomDependency">Pointer to AcDbAssocGeomDependency for which
  /// implicit point needs to be updated for mirror action. </param>
  /// <returns> Acad::ErrorStatus. </returns>
  ///
  Acad::ErrorStatus geometryMirrored(AcDbAssocGeomDependency* pGeomDependency);
  
  /// <summary>
  /// See the explanation of AcDbAssoc2dConstraintCallback. Multiple global callbacks 
  /// can be registered and they apply to all AcDbAssoc2dConstraintGroup.
  /// </summary>
  /// <param name="pCallback"> The callback to be registered. </param>
  ///
  static void addGlobalCallback(class AcDbAssoc2dConstraintCallback* pCallback);

  /// <summary>
  /// See the explanation of AcDbAssoc2dConstraintCallback. Multiple global callbacks 
  /// can be registered and they apply to all AcDbAssoc2dConstraintGroup.
  /// </summary>
  /// <param name="pCallback"> The callback to be unregistered. </param>
  ///
  static void removeGlobalCallback(class AcDbAssoc2dConstraintCallback* pCallback);

  /// <summary>
  /// Returns a callback that is the collection of all callbacks registered by
  /// client code. This function is meant mostly for private use and there should
  /// not be much need for the client code to use it. Anyway, the client code
  /// must never delete or unregister the returned callback, or do anything with
  /// it except for calling its methods.
  /// </summary>
  /// <returns> 
  /// The global AcDbAssocVariable(Multi)Callback that keeps all the callbacks 
  /// registered by the client code. The returned pointer is never null.
  /// </returns>
  ///
  static class AcDbAssoc2dConstraintCallback* globalCallback();

  /// <summary><para>
  /// Primarily for internal use only.
  /// <summary><para>
  /// Sets a global flag not to check constraints that are being added. This 
  /// optimization is primarily intended for the scenario when multiple constraints
  /// are being added one-by-one and the constraints are known to be valid.
  /// The constraint group is still evaluated after the constraints have been 
  /// added. To suppress this evaluation, temporarily set the status of the 
  /// constraint group to kSuppressedAssocStatus to prevent its evaluation,
  /// and un-suppress the constraint group after all constraints have been added.
  /// </para><para>
  /// To unsuppress a constraint group and evaluate it, its status needs to be 
  /// first set to kIsUpToDateAssocStatus and then to kChangedDirectlyAssocStatus.
  /// </para></summary>
  /// 
  static void setDoNotCheckNewlyAddedConstraints(bool doNotCheck);

  static bool doNotCheckNewlyAddedConstraints();

}; // class AcDbAssoc2dConstraintGroup


/// <summary>
/// Client code can register callback(s) derived from AcDbAssoc2dConstraintCallback 
/// that are then called when some events happen with AcDbAssoc2dConstraintGroup. 
/// </summary>
///
class AcDbAssoc2dConstraintCallback
{
public:
    /// <summary>Default constructor. </summary>
    ///
    AcDbAssoc2dConstraintCallback() {}

    /// <summary>Destructor. </summary>
    ///
    virtual ~AcDbAssoc2dConstraintCallback() {}

    /// <summary>
    /// Allows client code to veto erasing a dimension constraint when a 
    /// dimension constraint is not satisfied and being erased during relax 
    /// evaluation of 2d constraint group. If this method returns true then this 
    /// dimension constraint is converted to a reference dimension, client needs 
    /// to update variable value with it's measured value.
    /// </summary>
    /// <param name="pConstraint"> The dimension constraint that is to be   
    /// erased. </param>
    /// <returns> 
    /// true == client code allows the constraint to be converted to reference
    /// or driven constraint. false == client code allows the constraint to be
    /// erased.
    /// </returns>
    ///
    virtual bool canBeRelaxed(const class AcExplicitConstraint* pConstraint)
    {
        UNREFERENCED_PARAMETER(pConstraint);
        return false;
    }

    /// <summary>
    /// This function will be called when a constraint is
    /// deactivated/reactivated. This notification takes place when
    /// AcExplicitConstraint::deactivate() or
    /// AcExplicitConstraint::reactivate() is invoked.
    /// </summary>
    /// <param name="bDeactivated"> indicated whether to deactivate or 
    /// reactivate the constraint </param>
    /// <param name="pConstraint"> The constraint that is to be
    /// activated/deactivated. </param>
    ///
    virtual void constraintDeactivated(const AcExplicitConstraint *pConstraint,
                                       bool bDeactivated = true) {
        UNREFERENCED_PARAMETER(pConstraint);
        UNREFERENCED_PARAMETER(bDeactivated);
    }
};


/// <summary>
/// Client needs to implement this callback to provide constraint priorities
/// and priority override for autconstraint evaluation.
/// </summary>
///
class ACDB_PORT AcAutoConstrainEvaluationCallback
{
    friend class AcDbImpAssoc2dConstraintGroup;
    friend class AcAutoConstraintEvalManager;
public:
  virtual ~AcAutoConstrainEvaluationCallback() { }

  /// <summary> 
  /// This function will be called when system finds a possible constraint between given set of
  /// constrained geometries. This function expects to get an override to increase, decrease or
  /// maintain the priority for the given constraint condition.
  /// </summary>
  /// <param name="type">
  /// Geometric constraint type that is possible between given set of constrained geometry.
  /// </param>
  /// <param name="geometries">
  /// List of constrained geometry, which are potential candidate for provided constraint type.
  /// User may
  /// </param>
  /// <param name="priority">
  /// Priority for the given constraint. Application may modify it by increasing or decreasing 
  /// the priority, a negative value means constraint should not be applied between the given
  /// geometries. Higher value of priority means this contraint will be given preference over
  /// other possible constraint and will be applied earlier.</param>
  ///
  virtual void getConstraintPriorityOverride(AcGeomConstraint::GeomConstraintType type, 
        const AcArray<const AcConstrainedGeometry*>& geometries, int& priority) const
  {
      UNREFERENCED_PARAMETER(type);
      UNREFERENCED_PARAMETER(geometries);
      UNREFERENCED_PARAMETER(priority);
      return; //No override.
  }

  /// <summary>
  /// define order of the constraints type in which it can be used for autoConstrain.
  /// </summary>
  /// <param name="constraintList">
  /// List of constraint types to be considered for autoConstrain in decending order
  /// of priority. Constraint type not present in the list will not be considered 
  /// for autoconstraint.
  /// </param>
  /// 
  virtual void getAutoConstrainPriority(AcArray<AcGeomConstraint::GeomConstraintType>& constraintList) const
  {
      constraintList.setLogicalLength(0);
      for(int type = (int)AcGeomConstraint::kHorizontal;
          type < (int)AcGeomConstraint::kEqualRadius; ++type)
      {
          constraintList.append((AcGeomConstraint::GeomConstraintType)type);
      }
  }

  /// <summary>
  /// Checks if evaluation is canecelled by caller. If this function returns
  /// true the autoconstraint evaluation from DCM will be cancelled.
  /// </summary>
  /// <returns>
  /// True to cancel the evaluation else False.
  /// </returns>
  /// 
  virtual bool isEvaluationCancelled() { return false; }

  /// <summary>
  /// Returns list of constraints found by autoconstraint evaluation.
  /// </summary>
  /// <param name="pConstraints"> Pointer to array of constraints, to return 
  /// list of constraints found by autoconstraint evaluation. This parameter 
  /// can be NULL if caller doesn't want list of constraints.</param>
  /// <returns>
  /// Number of constraints found by autoconstraint evaluation.
  /// </returns>
  /// 
  int getTotalConstraints(AcArray<AcGeomConstraint*>* pConstraints) const;

private:  
  /// <summary>Returns mask for DCM autoconstrain evaluation. This function is
  /// is for internal use only.</summary>
  /// <returns>mask for DCM autoconstrain evaluation.</returns>
  int getAutoConstraintMask() const;

  /// <summary>Validates autoconstraint data. This function is
  /// is for internal use only.</summary>
  /// <param name="pData">Data for validation.</param>
  void validate(void* pData);

  /// <summarry> Checks if the constraint is of the given constraint type.
  /// </summary>
  /// <param name="type">GeomConstraint type for check.</param>
  /// <param name="pConstraint">Pointer to GeomConstraint which needs to be 
  /// checked for given <paramref name="type"/>.</param>
  /// <returns> true, if valid constraint type, else false.<returns>
  bool isValidConstraintType(AcGeomConstraint::GeomConstraintType type,
        const AcGeomConstraint* pConstraint) const;

  /// <summary>This method is called by AcAutoConstraintEvalManager to notify 
  /// the callback for constraint added event.</summary>
  /// <param name="pNewCons">Pointer to the constraint that has been added.</param>
  void constraintAdded(AcGeomConstraint* pNewCons);

private:
    AcArray<AcGeomConstraint*> mConstraints;
};

#pragma pack (pop)

