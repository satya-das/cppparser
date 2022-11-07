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
// CREATED BY: Jiri Kripac                                 October 2009
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocGlobal.h" 
#include "gemat3d.h"
#include "AcDbCompoundObjectId.h"
#pragma pack (push, 8)



/// <summary><para>
/// Base class for the concrete derived classes like AcDbFaceRef, AcDbEdgeRef, 
/// AcDbVertexRef, and AcDbPathRef. These are simple classes that keep a reference 
/// to a subentity of an entity and can represent this subentity information in 
/// various ways. They are used mainly to pass around information about geometry 
/// of a subentity or of an entity, not to keep this information.
/// </para><para>
/// The subentity references are non-presistent. Anytime the referenced entity 
/// is changed or re-evaluated, the subentity reference becomes invalid.
/// Persistent references can be established using AcDbAssocEdgeActionParam, 
/// AcDbAssocPathActionParam, AcDbAssocVertexActionParam, or directly using 
/// AcDbAssocGeomDependencies.
/// </para></summary>
///
class ACDBCORE2D_PORT AcDbGeomRef : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGeomRef);

    virtual ~AcDbGeomRef() {}

    /// <summary> Resets the contents of the AcDbGeomRef to empty. </summary>
    ///
    virtual void reset() = 0;

    /// <summary> Checks is the contents of this AcDbGeomRef is valid. </summary>
    ///
    virtual bool isValid() const = 0;

    /// <summary> 
    /// Checks if the AcDbGeomRef is empty, i.e. not referencing any entity,
    /// subentity, and not holding any constant geometry. 
    /// </summary>
    ///
    virtual bool isEmpty() const = 0;

    /// <summary> 
    /// Creates a new non-database resident AcDbEntity from the data the AcDbGeomRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the entity after it is no more needed. 
    /// </summary>
    ///
    virtual AcDbEntity* createEntity() const = 0;

    /// <summary> 
    /// If the AcDbGeomRef references some entities and also caches the constant
    /// geometry, this method evaluates the current geometry from the referenced
    /// entities and caches it in the constant geometry.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() = 0;
};


/// <summary><para>
/// Base class for AcDbFaceRef, AcDbEdgeRef and AcDbVertexRef. It keeps an 
/// AcDbCompoundObjectId of an AcDbEntity and AcDbSubentId of a subentity of 
/// this entity.
/// </para></summary>
///
class ACDBCORE2D_PORT AcDbSubentRef : public AcDbGeomRef
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSubentRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbSubentRef() {}

    /// <summary> The constructor sets data members of the AcDbSubentRef. </summary>
    ///
    explicit AcDbSubentRef(const AcDbCompoundObjectId&, const AcDbSubentId& = kNullSubentId); 

    AcDbSubentRef& operator =(const AcDbSubentRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;

    virtual void reset() override;
    virtual bool isEmpty() const override { return mEntityId.isEmpty(); }

    /// <summary> 
    /// Returns the AcDbCompoundObjectId of the entity that the AcDbSubentRef references.
    /// May be empty if a derived class holds constant geometry and does not 
    /// reference any existing AcDbEntity.
    /// </summary>
    ///
    virtual const AcDbCompoundObjectId& entity() const;

    /// <summary> 
    /// Returns the AcDbSubentId in an AcDbEntity that the AcDbSubentRef references. 
    /// May be null if whole AcDbEntity is referenced.
    /// </summary>
    ///
    virtual AcDbSubentId subentId() const;

    /// <summary> 
    /// Creates an AcDbEntity from the subentity of the entity.
    /// </summary>
    ///
    virtual AcDbEntity* createEntity() const override;

    /// <summary>
    /// No cached constant geoemtry held in AcDbSubentRef base class.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() override { return Acad::eOk; }

protected:

    /// <summary> Sets mEntity data member. </summary>
    ///
    void setEntity(const AcDbCompoundObjectId& entityId) { mEntityId = entityId; }

    /// <summary> Sets mSubentId data member. </summary>
    ///
    void setSubent(const AcDbSubentId& subentId) { mSubentId = subentId; }

    /// <summary> Sets mEntity and mSubentId data members. </summary>
    ///
    void setFromSubentPath(const AcDbFullSubentPath&);

private:
    AcDbCompoundObjectId mEntityId;
    AcDbSubentId         mSubentId;
};


/// <summary>
/// Reference to a face. It can either be represented by a face AcDbSubentId of 
/// an ASM-based AcDbEntity (AcDbSurface, AcDb3dSolid, AcDbRegion) or by
/// a constant ASM BODY and the AcDbSubentId then specifies the index of the 
/// face in the constant ASM BODY.
/// </summary>
///
class ACDBCORE2D_PORT AcDbFaceRef : public AcDbSubentRef
{
#ifdef __GNUC__
private:
    typedef AcDbSubentRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbFaceRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbFaceRef();
    AcDbFaceRef(const AcDbFaceRef&);
    virtual ~AcDbFaceRef();

    /// <summary> 
    /// The constructor sets the data members of the AcDbFaceRef. The provided
    /// ASM BODY is not copied, the caller is responsible for providing a copy,
    /// if needed.
    /// </summary>
    ///
    explicit AcDbFaceRef(const AcDbCompoundObjectId&, const AcDbSubentId& = kNullSubentId, class BODY* = NULL); 

    AcDbFaceRef& operator =(const AcDbFaceRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;

    virtual void reset() override;
    virtual bool isValid() const override;
    virtual bool isEmpty() const override { return __super::isEmpty() && mpAsmBody == NULL; }

    /// <summary> 
    /// Returns the ASM BODY that the AcDbFaceRef may hold. It does not return a 
    /// copy of the ASM BODY, therefore the client code needs to make a copy if 
    /// it needs to do any modifications to this ASM BODY.
    /// </summary>
    ///
    class BODY* asmBody() const { return mpAsmBody; }    

    /// <summary> 
    /// Creates a new non-database resident AcDbEntity from the data the AcDbFaceRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the entity after it is no more needed. 
    /// </summary>
    ///
    virtual AcDbEntity* createEntity() const override;

    /// <summary>
    /// For now this method does nothing.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() override { return Acad::eOk; }

private:
    class BODY* mpAsmBody;
};


/// <summary><para>
/// Reference to an edge, i.e. a subentity whose geometry is a simple curve. 
/// </para><para>
/// It may either be the whole entity that itself is a single curve, kEdgeSubentType 
/// subentity of an entity, or a constant AcGeCurve3d. Notice that this reference
/// is generally non-persistent, because it uses transient AcDbSubentId. 
/// </para><para>
/// The option to reference the whole entity is questionable and has been provided
/// just for the compatibility with old code that takes the whole entity. We should 
/// probably always represent edges by kEdgeSubentType subentities of entities, even
/// if the whole entity is just a single edge, such as line, arc, or circle.
/// </para></summary>
///
class ACDBCORE2D_PORT AcDbEdgeRef : public AcDbSubentRef
{
#ifdef __GNUC__
    typedef AcDbSubentRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbEdgeRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbEdgeRef();
    AcDbEdgeRef(const AcDbEdgeRef&);
    virtual ~AcDbEdgeRef();

    /// <summary> The constructor sets the data members of the AcDbEdgeRef. </summary>
    ///
    explicit AcDbEdgeRef(const AcDbCompoundObjectId&, 
                         const AcDbSubentId& edgeSubentId = kNullSubentId, 
                         const AcDbSubentId& faceSubentId = kNullSubentId, 
                         const AcGeCurve3d* pCurve        = NULL);

    /// <summary> 
    /// Creates AcDbEdgeRef from an entity in a block table record
    /// and referenced via a path of block inserts.
    /// </summary>
    ///
    explicit AcDbEdgeRef(const AcDbFullSubentPath&);  

    /// <summary> 
    /// The constructor makes the AcDbEdgeRef keep the AcDbObjectId of the given 
    /// AcDbEntity. Moreover, if the entity is derived from AcDbCurve, it obtains 
    /// a copy of the AcGeCurve3d and keeps in it the AcDbEdgeRef.
    /// </summary>
    ///
    explicit AcDbEdgeRef(const AcDbEntity* pEntity);  

    /// <summary> 
    /// The constructor makes the AcDbEdgeRef keep the AcGeCurve3d.
    /// </summary>
    ///
    explicit AcDbEdgeRef(const AcGeCurve3d* pGeCurve);

    AcDbEdgeRef& operator =(const AcDbEdgeRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;

    virtual void reset() override;
    virtual bool isValid() const override;
    virtual bool isEmpty() const override { return __super::isEmpty() && mpCurve == NULL; }

    /// <summary> 
    /// The AcDbEdgeRef can also hold AcDbSubentId of a face subentity. The face
    /// needs to bounded by the referenced edge subentity. The additional face 
    /// information is needed in cases like when an edge shared by two adjacent 
    /// faces is referenced and used for a smooth blend operation. It needs to
    /// be known which face to use to create the smooth blend to.
    ///</summary>
    ///
    void setFaceSubentity(const AcDbSubentId& faceSubentId);

    /// <summary> 
    /// Returns the optional face AcDbSubentId of one of the faces adjacent to the
    /// referenced edge.
    /// </summary>
    ///
    AcDbSubentId faceSubentId() const { return mFaceSubentId; }

    /// <summary> 
    /// Returns the constant AcGeCurve3d* that the AcDbEdgeRef may hold.
    /// </summary>
    ///
    const AcGeCurve3d* curve() const { return mpCurve; } 

    /// <summary> 
    /// Evaluates the curve from the referenced entity geometry. If no entity 
    /// is referenced, returns the cached curve. The caller is responsible for
    /// deleting the returned AcGeCurve3d*
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateCurve(AcGeCurve3d*&) const;

    /// <summary> 
    /// Creates a new non-database resident AcDbEntity from then data the AcDbEdgeRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the entity after it is no more needed. 
    /// </summary>
    ///
    virtual AcDbEntity* createEntity() const override;

    /// <summary> 
    /// Calls evaluateCurve() and replaces the current constant AcGeCurve3d* with the
    /// newly evaluated curve.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() override;

private:

    // Deletes the previously stored AcGeCurve3d and sets the constant AcGeCurve3d 
    // in the AcDbEdgeRef to be a copy of the provided curve. It is allowed to 
    // pass NULL for the pCurve. 
    //
    // This method is private because we hope it will not be needed by the client 
    // code. We want to keep AcDbGeomRef methods read-only so that these classes
    // do not overgrow their original purpose of simple container classes. If needed, 
    // the client code can usually make a new AcDbGeomRef from the existing one instead 
    // of changing the existing one
    //
    void setCurve(const AcGeCurve3d* pCurve);

    AcDbSubentId mFaceSubentId;
    AcGeCurve3d* mpCurve;
};


/// <summary>
/// Reference to a vertex, i.e. a subentity whose geometry is a point. It may 
/// either be whole AcDbPoint entity, kVertexSubentType subentity of an entity, or 
/// a constant AcGePoint3d. Notice that this reference is generally non-persistent, 
/// because it uses transient AcDbSubentId. 
/// </summary>
///
class ACDBCORE2D_PORT AcDbVertexRef : public AcDbSubentRef
{
#ifdef __GNUC__
private:
    typedef AcDbSubentRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbVertexRef);

    /// <summary><para>
    /// An implied vertex ref is a special point on another AcDbGeomRef.
    /// </para><para>
    /// Currently we only have implied vertex ref types for the most common case of 
    /// special points on an AcDbEdgeRef. I am not sure if we should keep extending this 
    /// mechanism in the future. Other mechanisms, such as derivation from AcDbVertexRef, 
    /// should be used for more specialized and/or less common cases. 
    /// </para></summary>
    /// 
    enum ImpliedType
    {
        kExplicitVertex, // Not an implied vertex (the vertex is directly specified)
        kUnknownType,
        kEdgeStart,
        kEdgeEnd,
        kEdgeMid,
        kEdgeCenter,
        kEdgeSplineControlPoint,
        kEdgeSplineFitPoint,
    };

    /// <summary> Default constructor. </summary>
    ///
    AcDbVertexRef();
    AcDbVertexRef(const AcDbVertexRef&);
    virtual ~AcDbVertexRef();

    /// <summary> The constructor sets the data members of the AcDbEdgeRef. </summary>
    ///
    explicit AcDbVertexRef(const AcDbCompoundObjectId&, const AcDbSubentId& = kNullSubentId, const AcGePoint3d& = AcGePoint3d::kOrigin);

    /// <summary> 
    /// Creates AcDbVertexRef from an entity in a block table record
    /// and referenced via a path of block inserts.
    /// </summary>
    ///
    explicit AcDbVertexRef(const AcDbFullSubentPath&);

    /// <summary> 
    /// The constructor makes the AcDbVertexRef keep the AcDbObjectId of the given 
    /// AcDbEntity. Moreover, if the entity is derived from AcDbPoint, it keeps 
    /// its AcGePoint3d as AcGePoint3d.
    /// </summary>
    ///
    explicit AcDbVertexRef(const AcDbEntity*);

    /// <summary> 
    /// The constructor makes the AcDbVertexRef keep the AcGePoint3d.
    /// </summary>
    ///
    explicit AcDbVertexRef(const AcGePoint3d&);

    /// <summary>
    /// Constructor for creating implied vertex refs, i.e. a vertex being defined 
    /// as being a special point on an AcDbEdgeRef. See more comments at the 
    /// ImpliedType enum.
    /// </summary>
    ///
    explicit AcDbVertexRef(ImpliedType, const AcDbEdgeRef& edgeRef, int controlOrFitPointIndex = 0, const AcGePoint3d& = AcGePoint3d::kOrigin);

    AcDbVertexRef& operator =(const AcDbVertexRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;

    virtual void reset() override;
    virtual bool isValid() const override;

    /// <summary> 
    /// If referencedRef() is not NULL, returns its AcDbCompoundObjectId, otherwise 
    /// returns AcDbCompoundObjectId from the base-class AcDbSubentRef.
    /// </summary>
    ///
    virtual const AcDbCompoundObjectId& entity() const override;

    /// <summary> 
    /// If referencedRef() is not NULL, returns kNussSubentId, otherwise returns 
    /// AcDbSubentId from the base-class AcDbSubentRef.
    ///
    /// TODO Jiri kripac:
    /// The semantics of this method is questionable and should be revisited
    /// because an implied vertex does identify a subentity, but there is no 
    /// simple AcDbSubentId for it.
    /// </summary>
    ///
    virtual AcDbSubentId subentId() const override;

    /// <summary> 
    /// The following are for implied vertex refs (see more comments comments 
    /// at ImpliedType enum). The returned referenced AcDbGeomRef is currently 
    /// always an AcDbEdgeRef but we want to keep the protocol general.
    /// </summary>
    ///
    ImpliedType        impliedType()   const { return mImpliedType;    }
    const AcDbGeomRef* referencedRef() const { return mpReferencedRef; }
    int                index()         const { return mIndex;          }

    /// <summary> 
    /// Returns the AcGePoint3d directly held in the AcDbVertexRef. 
    /// </summary>
    ///
    AcGePoint3d point() const;

    /// <summary> 
    /// Evaluates the point from the referenced geometry. If no geometry, 
    /// returns the cached point coordinates.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluatePoint(AcGePoint3d&) const;

    /// <summary> 
    /// Creates a new non-database resident AcDbPoint from then data the AcDbVertexRef
    /// holds, and returns it to the caller. The caller is responsible for deleting 
    /// the AcDbPoint after it is no more needed. 
    /// </summary>
    ///
    class AcDbEntity* createEntity() const override;

    /// <summary> 
    /// Calls evaluatePoint() and replaces the current constant AcGePoint3d with the
    /// newly evaluated point.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() override;

private:

    // Deletes the previously stored mpReferencedRef and sets it to be a copy
    // of the provided AcDbGeomRef. It is allowed to pass NULL for the AcDbGeomRef
    //
    void setReferencedRef(const AcDbGeomRef*);

    // The following are only used when the vertex is an implied vertex on
    // some other AcDbSubentRef (i.e. when mType is not kExplicitVertex)
    //
    ImpliedType        mImpliedType;
    const AcDbGeomRef* mpReferencedRef;
    int                mIndex; // Currently only used to indicate spline control/fit point index

    AcGePoint3d  mPoint; 
};


/// <summary>
/// Reference to a path, which is just a sequence of edges. If the path has an 
/// array of edges which happen to be connected at their end points, it will try 
/// to concatenate the curves into one composite curve.
/// </summary>
///
class ACDBCORE2D_PORT AcDbPathRef : public AcDbGeomRef
{
public:
    ACRX_DECLARE_MEMBERS(AcDbPathRef);

    /// <summary> Default constructor. </summary>
    ///
    AcDbPathRef();
    AcDbPathRef(const AcDbPathRef&);

    /// <summary> 
    /// Creates an AcDbPathRef from a sequence of AcDbEdgeRefs.
    /// </summary>
    ///
    explicit AcDbPathRef(const AcArray<AcDbEdgeRef>&);

    /// <summary> 
    /// Constructor an AcDbPathRef that is a sequence of connected edges.
    /// </summary>
    /// <param name="edgeSubentPathArr"> 
    /// Subent paths of the edges that make up the path. 
    /// </param>
    /// <param name="faceSubentPathArr"> 
    /// Optional subent paths of the faces for each edge.  The number of elements in
    /// this array must be 0 or be the same as the number of elements in
    /// edgeSubentPathArr. 
    /// </param>
   AcDbPathRef(const AcDbFullSubentPathArray& edgeSubentPathArr,
               const AcDbFullSubentPathArray& faceSubentPathArr);

    virtual ~AcDbPathRef();

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;

    virtual void reset() override;
    virtual bool isValid() const override;
    virtual bool isEmpty() const override;

    /// <summary> Sets the AcDbPathRef from a sequence of AcDbEdgeRefs. </summary>
    ///
    void setEdgeRefs(const AcArray<AcDbEdgeRef>& edges);

    /// <summary> 
    /// Returns an array of AcDbEntities created from the individual AcDbEdgeRefs
    /// in the path. If concatenate is true, it tries to concatenate them.
    /// </summary>
    ///
    Acad::ErrorStatus getEntityArray(AcArray<AcDbEntity*>& entities, bool concatenate) const;

    /// <summary> Returns the array of AcDbEdgeRefs kept in the AcDbPathRef. </summary>
    ///
    const AcArray<AcDbEdgeRef>& edgeRefs() const { return mEdgeRefs; }

    /// <summary> Returns true if the geometry of the path is equal to the geometry of the given curve. </summary>
    ///
    bool isEqualTo(const AcGeCurve3d*);

    /// <summary> 
    /// Returns true if all elements of the path are references to entities, i.e.
    /// they are not constant geometries.
    /// </summary>
    ///
    bool isReferencePath();

    virtual AcDbEntity* createEntity() const override;

    /// <summary> 
    /// Calls evaluateAndCacheGeometry() on all the owned AcDbEdgeRefs.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() override;

private:
    AcArray<AcDbEdgeRef> mEdgeRefs;
};


/// <summary>
/// Arbitrary 3D vector, of any length.
/// </summary>
/// <remarks> For internal use only. </remarks>
///
class ACDBCORE2D_PORT AcDbVectorRef : public AcDbGeomRef
{
#ifdef __GNUC__
private:    
    typedef AcDbGeomRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbVectorRef);

    explicit AcDbVectorRef();

    explicit AcDbVectorRef(const AcDbVectorRef&);

    explicit AcDbVectorRef(const AcGeVector3d&);

    virtual ~AcDbVectorRef();

    AcDbVectorRef& operator = (const AcDbVectorRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;

    virtual void reset() override;
    virtual bool isValid() const override;
    virtual bool isEmpty() const override;

    const AcGeVector3d vector() const { return mVector; }

    void set(const AcGeVector3d&);

    /// <summary> 
    /// TBD
    /// </summary>
    ///
    virtual AcDbEntity* createEntity() const override;

    /// <summary> 
    /// TBD
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() override;

private:

    AcGeVector3d mVector;
};


/// <summary>
/// Coordinate system, actually an arbitrary matrix. The axes do not need to be
/// unit lengths, perpendicular, or form right-hand coord system (may be mirrored).
/// </summary>
/// <remarks> For internal use only. </remarks>
///
class ACDBCORE2D_PORT AcDbCoordSystemRef : public AcDbGeomRef
{
#ifdef __GNUC__
    typedef AcDbGeomRef __super;
#endif
public:
    ACRX_DECLARE_MEMBERS(AcDbCoordSystemRef);

    explicit AcDbCoordSystemRef();

    explicit AcDbCoordSystemRef(const AcDbCoordSystemRef&);

    explicit AcDbCoordSystemRef(const AcGeMatrix3d&);

    explicit AcDbCoordSystemRef(const AcDbCompoundObjectId&, const AcGeMatrix3d&); 

    explicit AcDbCoordSystemRef(const AcArray<AcDbSubentRef*>&);

    virtual ~AcDbCoordSystemRef();

    AcDbCoordSystemRef& operator = (const AcDbCoordSystemRef&);

    virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;

    virtual void reset() override;
    virtual bool isValid() const override;
    virtual bool isEmpty() const override;

    const AcGeMatrix3d&            coordSystem() const { return mCoordSystem; }
    const AcDbCompoundObjectId&    entityId   () const { return mEntityId;    }
    const AcArray<AcDbSubentRef*>& subentRefs () const { return mSubentRefs;  }

    void set(const AcGeMatrix3d&);
    void set(const AcDbCompoundObjectId&);
    void set(const AcArray<AcDbSubentRef*>&);

    /// <summary> 
    /// There is no AcDbEntity created from AcDbCoordSystemRef. 
    /// </summary>
    ///
    virtual AcDbEntity* createEntity() const override { return NULL; }

    /// <summary> 
    /// Calls evaluateAndCacheGeometry on all owned AcDbSubentRefs and then updates
    /// the cached coordinate system.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateAndCacheGeometry() override;

private:

    AcGeMatrix3d            mCoordSystem;
    AcDbCompoundObjectId    mEntityId;
    AcArray<AcDbSubentRef*> mSubentRefs;
};

#pragma pack (pop)

