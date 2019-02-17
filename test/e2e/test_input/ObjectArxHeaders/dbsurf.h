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
// DESCRIPTION:
//
// The AcDbSurface class is the interface class for representing
// ASM surfaces inside AutoCAD.  

#pragma once

#include "dbmain.h"
#include "dbsubeid.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "dbRevolveOptions.h"
#include "dbSweepOptions.h"
#include "dbLoftOptions.h"

#include "AcDbAssocGlobal.h"
#include "AcDbCompoundObjectId.h"

#pragma pack(push, 8)

class AcDbLoftProfile;
class AcDbBlendOptions;
class AcDbNurbSurface;
class AcDb3dProfile;
class AcDbRevolvedSurface;
class AcDbExtrudedSurface;
class AcDbSweptSurface;

class AcDbPathRef; // Pre-declare AcDbPathRef after removing including AcDbGeomRef.h

typedef AcArray<AcDbNurbSurface*> AcDbNurbSurfaceArray;

class AcDbSurface: public AcDbEntity
{
public:
    /// <summary> 
    /// Control the internal wireframe quilt display when the "edge mode" is 
    /// set to Isolines in any of the Visual Styles.
    /// </summary>
    ///
    enum WireframeType {
        /// <summary> 
        /// The quilt representation is controlled by the SURFV and SURFU
        /// at creation time for surfaces.
        /// </summary>
        ///
        kIsolines = 0,

        /// <summary> 
        /// The quilt representation is based on the projection of
        /// the knot structure of surface.
        /// </summary>
        ///
        kIsoparms = 1
    };

    /// <summary>
    /// Defines possible edge extension types as input for extendEdges or 
    /// createExtendSurface methods.
    /// </summary>
    ///
    enum EdgeExtensionType {
        /// <summary> Edges will be extended. </summary>
        kExtendEdge  = 0x000,
        /// <summary> Edges will be stretched. </summary>
        kStretchEdge = 0x001,
    };

    AcDbSurface();
    virtual ~AcDbSurface();
    ACDB_DECLARE_MEMBERS(AcDbSurface);

    // Create a swept surface from 2D entity with thickness
    // or a planar surface from a closed curve or a region.
    static Acad::ErrorStatus createFrom ( const AcDbEntity* pFromEntity,
                                          AcDbSurface*& pNewSurface );

    /// <summary> 
    /// Creates an extruded surface from the given profile using the specified options
    /// and adds the surface to the current database.
    /// </summary>
    /// <param name="pSweep"> 
    /// Input profile to be extruded.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges.
    /// </param>
    /// <param name="directionVec"> 
    /// Input direction of extrusion.  This vector must not be zero-length. 
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <param name="newExtrudedSurface"> 
    /// Pointer to the extruded surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createExtrudedSurface ( AcDb3dProfile *pSweep,
                                                               const AcGeVector3d& directionVec,
                                                               AcDbSweepOptions& sweepOptions,
                                                               AcDbExtrudedSurface*& newExtrudedSurface );

    /// <summary> 
    /// Creates an extruded surface from the given profile using the specified options
    /// and adds the surface to the current database.
    /// </summary>
    /// <param name="pSweep"> 
    /// Input profile to be extruded.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges.
    /// </param>
    /// <param name="directionVec"> 
    /// Input direction of extrusion.  This vector must not be zero-length. 
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether extruded surface associativity is enabled. 
    /// </param>
    /// <param name="newExtrudedSurfaceId"> 
    /// ObjectId to the extruded surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createExtrudedSurface ( AcDb3dProfile *pSweep,
                                                                    const AcGeVector3d& directionVec,
                                                                    AcDbSweepOptions& sweepOptions,
                                                                    bool  bAssociativeEnabled,
                                                                    AcDbObjectId& newExtrudedSurfaceId );

    /// <summary> 
    /// Creates a revolved surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pRev"> 
    /// Input profile to be revolved.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges. 
    /// </param>
    /// <param name="axisPnt"> 
    /// Any point on the axis of revolution. 
    /// </param>
    /// <param name="axisDir"> 
    /// Direction vector of the axis of revolution.  This vector must not be zero-length.  
    /// </param>
    /// <param name="revAngle"> 
    /// Angle through which the profile is to be revolved.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="startAngle"> 
    /// Starting angle of the profile.  If this parameter is 0.0 then the profile will
    /// be revolved from its current position.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="revolveOptions"> 
    /// Input revolve options. 
    /// </param>
    /// <param name="newRevolvedSurface"> 
    /// Pointer to new revolved surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createRevolvedSurface ( AcDb3dProfile *pRev,
                                                               const AcGePoint3d& axisPnt,
                                                               const AcGeVector3d& axisDir,
                                                               double revAngle, double startAngle,
                                                               AcDbRevolveOptions& revolveOptions,
                                                               AcDbRevolvedSurface*& newRevolvedSurface );


    /// <summary> 
    /// Creates a revolved surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pRev"> 
    /// Input profile to be revolved.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges. 
    /// </param>
    /// <param name="axisPnt"> 
    /// Any point on the axis of revolution. 
    /// </param>
    /// <param name="axisDir"> 
    /// Direction vector of the axis of revolution.  This vector must not be zero-length.  
    /// </param>
    /// <param name="revAngle"> 
    /// Angle through which the profile is to be revolved.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="startAngle"> 
    /// Starting angle of the profile.  If this parameter is 0.0 then the profile will
    /// be revolved from its current position.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="revolveOptions"> 
    /// Input revolve options. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether revolved surface associativity is enabled. 
    /// </param>
    /// <param name="newRevolvedSurface"> 
    /// Pointer to new revolved surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createRevolvedSurface ( AcDb3dProfile *pRev,
                                                                    const AcGePoint3d& axisPnt,
                                                                    const AcGeVector3d& axisDir,
                                                                    double revAngle, double startAngle,
                                                                    AcDbRevolveOptions& revolveOptions,
                                                                    bool  bAssociativeEnabled,
                                                                    AcDbObjectId& newSurfaceId );

    /// <summary> 
    /// Creates a revolved surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pRev"> 
    /// Input profile to be revolved.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges. 
    /// </param>
    /// <param name="pAxis"> 
    /// Profile which is either a line or a linear edge of a surface or solid.
    /// </param>
    /// <param name="flipAxisDirection"> 
    /// True if the direction of the axis should be taken in the opposite direction of
    /// the entity defined by pAxis.
    /// </param>
    /// <param name="revAngle"> 
    /// Angle through which the profile is to be revolved.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="startAngle"> 
    /// Starting angle of the profile.  If this parameter is 0.0 then the profile will
    /// be revolved from its current position.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="flipAxisDirection"> 
    /// This parameter is only relevant when pAxisEnt is non-null.
    /// In this case this parameter specifies 
    /// </param>
    /// <param name="revolveOptions"> 
    /// Input revolve options. 
    /// </param>
    /// <param name="newRevolvedSurface"> 
    /// Pointer to te new revolved surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createRevolvedSurface ( AcDb3dProfile *pRev,
                                                               AcDb3dProfile *pAxis,
                                                               bool flipAxisDirection,
                                                               double revAngle, double startAngle,
                                                               AcDbRevolveOptions& revolveOptions,
                                                               AcDbRevolvedSurface*& newRevolvedSurface );

    /// <summary> 
    /// Creates a revolved surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pRev"> 
    /// Input profile to be revolved.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges. 
    /// </param>
    /// <param name="pAxis"> 
    /// Profile which is either a line or a linear edge of a surface or solid.
    /// </param>
    /// <param name="flipAxisDirection"> 
    /// True if the direction of the axis should be taken in the opposite direction of
    /// the entity defined by pAxis.
    /// </param>
    /// <param name="revAngle"> 
    /// Angle through which the profile is to be revolved.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="startAngle"> 
    /// Starting angle of the profile.  If this parameter is 0.0 then the profile will
    /// be revolved from its current position.  This angle is taken to be
    /// counter-clockwise about the axis of revolution.
    /// </param>
    /// <param name="flipAxisDirection"> 
    /// This parameter is only relevant when pAxisEnt is non-null.
    /// In this case this parameter specifies 
    /// </param>
    /// <param name="revolveOptions"> 
    /// Input revolve options. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether revolved surface associativity is enabled. 
    /// </param>
    /// <param name="newRevolvedSurfaceId"> 
    /// ObjectId to te new revolved surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createRevolvedSurface ( AcDb3dProfile *pRev,
                                                                    AcDb3dProfile *pAxis,
                                                                    bool flipAxisDirection,
                                                                    double revAngle, double startAngle,
                                                                    AcDbRevolveOptions& revolveOptions,
                                                                    bool  bAssociativeEnabled,
                                                                    AcDbObjectId& newRevolvedSurfaceId );


    /// <summary> 
    /// Creates a swept surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pSweep"> 
    /// Input profile to be swept.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges. 
    /// </param>
    /// <param name="pPath"> 
    /// Input profile along which pSweep is to be swept.  This must be a curve or
    /// an edge.
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <param name="newSweptSurface"> 
    /// Pointer to the new swept surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createSweptSurface ( AcDb3dProfile *pSweep,
                                                            AcDb3dProfile *pPath,
                                                            AcDbSweepOptions& sweepOptions,
                                                            AcDbSweptSurface*& newSweptSurface);

    /// <summary> 
    /// Creates a swept surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pSweep"> 
    /// Input profile to be swept.  This may be an entity such as a curve or
    /// planar surface or it may be an edge or set of connected edges. 
    /// </param>
    /// <param name="pPath"> 
    /// Input profile along which pSweep is to be swept.  This must be a curve or
    /// an edge.
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether swept surface associativity is enabled. 
    /// </param>
    /// <param name="newSurfaceId"> 
    /// Object id of swept surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createSweptSurface ( AcDb3dProfile *pSweep,
                                                                 AcDb3dProfile *pPath,
                                                                 AcDbSweepOptions& sweepOptions,
                                                                 bool  bAssociativeEnabled,
                                                                 AcDbObjectId& newSurfaceId );

    /// <summary> 
    /// Creates a lofted surface from the given profiles using the specified options
    /// and adds it to the current database.  The cross sections, guides, and path
    /// may be entities such as curves or points, or they may be edges or sets of
    /// connected edges.  The cross sections must be either all open or all closed.
    /// If the cross sections are all closed, then this function will accept a point
    /// entity as the first and/or last list entry.  Each profile in the guides list
    /// must intersect each of the cross-section profiles, so the guides form a
    /// net-like structure with the cross-sections. Both the cross-section profiles
    /// and the guide profiles will lie on the resulting surface. If any guide profiles
    /// are passed in this list, then pPath should be null. If pPath is non-null, then
    /// the resulting surface will follow the shape of this profile as much as possible.
    /// This profile does not need to intersect the cross-section profiles and does not
    /// even need to be near the cross sections.
    /// </summary>
    /// <param name="crossSections"> 
    /// Input array of profiles to be used as cross sections for the lofting operation. 
    /// </param>
    /// <param name="guides"> 
    /// Input optional array of guide profiles. 
    /// </param>
    /// <param name="pPath"> 
    /// Input optional path profile. 
    /// </param>
    /// <param name="loftOptions"> 
    /// Input loft options. 
    /// </param>
    /// <param name="newSurface"> 
    ///Pointer to the new lofted surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createLoftedSurface ( const AcArray<AcDbLoftProfile*>& crossSections,
                                                             const AcArray<AcDbLoftProfile*>& guides,
                                                             AcDbLoftProfile *pPath, AcDbLoftOptions& loftOptions,
                                                             AcDbSurface*& newSurface );

    /// <summary> 
    /// Creates a lofted surface from the given profiles using the specified options
    /// and adds it to the current database.  The cross sections, guides, and path
    /// may be entities such as curves or points, or they may be edges or sets of
    /// connected edges.  The cross sections must be either all open or all closed.
    /// If the cross sections are all closed, then this function will accept a point
    /// entity as the first and/or last list entry.  Each profile in the guides list
    /// must intersect each of the cross-section profiles, so the guides form a
    /// net-like structure with the cross-sections. Both the cross-section profiles
    /// and the guide profiles will lie on the resulting surface. If any guide profiles
    /// are passed in this list, then pPath should be null. If pPath is non-null, then
    /// the resulting surface will follow the shape of this profile as much as possible.
    /// This profile does not need to intersect the cross-section profiles and does not
    /// even need to be near the cross sections.
    /// </summary>
    /// <param name="crossSections"> 
    /// Input array of profiles to be used as cross sections for the lofting operation. 
    /// </param>
    /// <param name="guides"> 
    /// Input optional array of guide profiles. 
    /// </param>
    /// <param name="pPath"> 
    /// Input optional path profile. 
    /// </param>
    /// <param name="loftOptions"> 
    /// Input loft options. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether lofted surface associativity is enabled. 
    /// </param>
    /// <param name="newSurfaceId"> 
    /// Object id of lofted surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createLoftedSurface ( const AcArray<AcDbLoftProfile*>& crossSections,
                                                                  const AcArray<AcDbLoftProfile*>& guides,
                                                                  AcDbLoftProfile *pPath, AcDbLoftOptions& loftOptions,
                                                                  bool  bAssociativeEnabled,
                                                                  AcDbObjectId& newSurfaceId );
	/// <summary> 
    /// Creates a network surface and adds it to the current database.
    /// A network surface is similar to a lofted surface where the u profiles are
    /// cross sections and the v profiles are guides.  But unlike the lofted surface,
    /// the v profiles do not need to intersect the u profiles.  If the two sets of 
    /// profiles do not all intersect then in general the profiles will not lie on
    /// the resulting surface.
    /// </summary>
    /// <param name="crossSections"> 
    /// Input array of u-direction profiles. 
    /// </param>
    /// <param name="guides"> 
    /// Input array of v-direction profiles. 
    /// </param>
    /// <param name="newSurface"> 
    /// Pointer to the new network surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createNetworkSurface ( const AcArray<AcDb3dProfile*>& uProfiles,
                                                              const AcArray<AcDb3dProfile*>& vProfiles,
                                                              AcDbSurface*& newSurface);

	/// <summary> 
    /// Creates a network surface and adds it to the current database.
    /// A network surface is similar to a lofted surface where the u profiles are
    /// cross sections and the v profiles are guides.  But unlike the lofted surface,
    /// the v profiles do not need to intersect the u profiles.  If the two sets of 
    /// profiles do not all intersect then in general the profiles will not lie on
    /// the resulting surface.
    /// </summary>
    /// <param name="crossSections"> 
    /// Input array of u-direction profiles. 
    /// </param>
    /// <param name="guides"> 
    /// Input array of v-direction profiles. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether network surface associativity is enabled. 
    /// </param>
    /// <param name="newSurfaceId"> 
    /// Object id of network surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createNetworkSurface ( const AcArray<AcDb3dProfile*>& uProfiles,
                                                              const AcArray<AcDb3dProfile*>& vProfiles,
                                                              bool  bAssociativeEnabled,
                                                              AcDbObjectId& newSurfaceId );

    /// <summary> 
    /// Create patch surface by specifying one of the following:
    ///   + edges which must form a closed loop. 
    ///   + profile curves which must form a closed loop
    /// The API doesn't support mixing the two yet.
    ///
    /// The constraintIds are optional which specify the objectID of curve or point 
    /// to be passed by the patch surface as constraint. 
    /// Continuity and bulge only apply to boundary edges, not the constraint curves.
    ///
    /// </summary>
    /// <param name="pathRef"> 
    /// Input edge reference which can be edges of entities or proflie curves 
    /// </param>
    /// <param name="constraintIds"> 
    /// Optional contrainted curve or point. 
    /// </param>
    /// <param name="continuity"> 
    /// Optional continuity for patch created with edges 
    /// </param>
    /// <param name="bulge"> 
    /// Optional bulge for patch created with edges
    /// </param>
    /// <param name="newSurface"> 
    /// Pointer to the new patch surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createPatchSurface ( const AcDbPathRef& pathRef,
                                                            const AcDbObjectIdArray& constraintIds,
                                                            int continuity,
                                                            double bulge,
                                                            AcDbSurface*& newSurface);


    /// <summary> 
    /// Create an associative patch surface by specifying one of the following:
    ///   + edges which must form a closed loop. 
    ///   + profile curves which must form a closed loop
    /// The API doesn't support mixing the two yet.
    ///
    /// The constraintIds are optional which specify the objectID of curve or point 
    /// to be passed by the patch surface as constraint. 
    /// Continuity and bulge only apply to boundary edges, not the constraint curves.
    ///
    /// </summary>
    /// <param name="pathRef"> 
    /// Input edge reference which can be edges of entities or proflie curves 
    /// </param>
    /// <param name="constraintIds"> 
    /// Optional contrainted curve or point. 
    /// </param>
    /// <param name="continuity"> 
    /// Optional continuity for patch created with edges 
    /// </param>
    /// <param name="bulge"> 
    /// Optional bulge for patch created with edges
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether patch surface associativity is enabled. 
    /// </param>
    /// <param name="newSurfaceId"> 
    /// Object id of patch surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createPatchSurface ( const AcDbPathRef& pathRef,
                                                                 const AcDbObjectIdArray& constraintIds,
                                                                 int continuity,
                                                                 double bulge,
                                                                 bool  bAssociativeEnabled,
                                                                 AcDbObjectId& newSurfaceId);

    /// <summary> 
    ///  Creates a blend surface from the given profiles using the specified options
    ///  and adds it to the current database. The startProfile and endProfile must
    ///  be edges or a set of connected edges. 
    /// </summary>
    /// <param name="startProfile"> 
    /// Input profile to be used as the start for blend operation. 
    /// </param>
    /// <param name="endProfile"> 
    /// Input profile to be used as the end for blend operation. 
    /// </param>
    /// <param name="blendOptions"> 
    /// Input blend options.
    /// </param>
    /// <param name="blendSurface"> 
    /// Pointer to the blend surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createBlendSurface ( AcDbLoftProfile* startProfile,
                                                            AcDbLoftProfile* endProfile,
                                                            AcDbBlendOptions* blendOptions, 
                                                            AcDbSurface*& blendSurface);


    /// <summary> 
    ///  Creates a blend surface from the given profiles using the specified options
    ///  and adds it to the current database. The startProfile and endProfile must
    ///  be edges or a set of connected edges. 
    /// </summary>
    /// <param name="startProfile"> 
    /// Input profile to be used as the start for blend operation. 
    /// </param>
    /// <param name="endProfile"> 
    /// Input profile to be used as the end for blend operation. 
    /// </param>
    /// <param name="blendOptions"> 
    /// Input blend options.
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether blend surface associativity is enabled. 
    /// </param>
    /// <param name="newSurfaceId"> 
    /// Object id of blend surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createBlendSurface ( AcDbLoftProfile* startProfile,
                                                                 AcDbLoftProfile* endProfile,
                                                                 AcDbBlendOptions* blendOptions,
                                                                 bool  bAssociativeEnabled,
                                                                 AcDbObjectId& blendSurfaceId);

    /// <summary> 
    ///  Creates a tangent surface between two surface edges with constant radius
    ///  and trim or no trim the original surfaces to it.
    /// </summary>
    /// <param name="surfId1"> 
    /// Input objectID of the first source surface.
    /// </param>
    /// <param name="pickPt1"> 
    /// Input 3D point specifying the side on the first source surface you want to  
    /// keep after filleting.
    /// </param>
    /// <param name="surfId2"> 
    /// Input objectID of the second source surface.
    /// </param>
    /// <param name="pickPt2"> 
    /// Input 3D point specifying the side on the second source surface you want to 
    /// keep after filleting.
    /// </param>
    /// <param name="radius"> 
    /// Input positive value specifying radius for fillet operation.
    /// </param>
    /// <param name="trimMode"> 
    /// Input flag specifying enum value of kTrimNone, kTrimFirst, kTrimSecond or 
    /// kTrimBoth. 
    /// </param>
    /// <param name="projDir"> 
    /// Input 3D vector specifying the projection (view) direction for pick points.
    /// This vector is used for calculation of the projection point on the source
    /// surfaces for pickPt1 and pickPt2. 
    /// </param>
    /// <param name="filletSurface"> 
    /// Pointer to the fillet surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createFilletSurface ( const AcDbObjectId& surfId1,
                                                             const AcGePoint3d& pickPt1,
                                                             const AcDbObjectId& surfId2,
                                                             const AcGePoint3d& pickPt2,
                                                             double radius,
                                                             AcDb::FilletTrimMode trimMode,
                                                             const AcGeVector3d& projDir,
                                                             AcDbSurface*& filletSurface);

    /// <summary> 
    ///  Creates a tangent surface between two surface edges with constant radius
    ///  and trim or no trim the original surfaces to it.
    /// </summary>
    /// <param name="surfId1"> 
    /// Input objectID of the first source surface.
    /// </param>
    /// <param name="pickPt1"> 
    /// Input 3D point specifying the side on the first source surface you want to  
    /// keep after filleting.
    /// </param>
    /// <param name="surfId2"> 
    /// Input objectID of the second source surface.
    /// </param>
    /// <param name="pickPt2"> 
    /// Input 3D point specifying the side on the second source surface you want to 
    /// keep after filleting.
    /// </param>
    /// <param name="radius"> 
    /// Input positive value specifying radius for fillet operation.
    /// </param>
    /// <param name="trimMode"> 
    /// Input flag specifying enum value of kTrimNone, kTrimFirst, kTrimSecond or 
    /// kTrimBoth. 
    /// </param>
    /// <param name="projDir"> 
    /// Input 3D vector specifying the projection (view) direction for pick points.
    /// This vector is used for calculation of the projection point on the source
    /// surfaces for pickPt1 and pickPt2. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether filltet surface associativity is enabled. 
    /// </param>
    /// <param name="newSurfaceId"> 
    /// Object id of fillet surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createFilletSurface ( const AcDbObjectId& surfId1,
                                                                  const AcGePoint3d& pickPt1,
                                                                  const AcDbObjectId& surfId2,
                                                                  const AcGePoint3d& pickPt2,
                                                                  double radius,
                                                                  AcDb::FilletTrimMode trimMode,
                                                                  const AcGeVector3d& projDir,
                                                                  bool  bAssociativeEnabled,
                                                                  AcDbObjectId& filletSurfaceId);

    /// <summary> 
    /// Creates an offset surface.
    /// </summary>
    /// <param name="pInputSurface"> 
    /// Original input surface to be offset. 
    /// </param>
    /// <param name="offsetDistance"> 
    /// Input distance to offset the input surface. 
    /// </param>
    /// <param name="offsetSurface"> 
    /// Pointer to the new offset surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createOffsetSurface ( AcDbEntity* pInputSurface,
                                                             double offsetDistance,
                                                             AcDbEntity*& offsetSurface);


    /// <summary> 
    /// Creates an offset surface and adds it to the current database.
    /// </summary>
    /// <param name="pInputSurface"> 
    /// Original input surface to be offset. 
    /// </param>
    /// <param name="offsetDistance"> 
    /// Input distance to offset the input surface. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether patch surface associativity is enabled. 
    /// </param>
    /// <param name="offsetSurfaceId"> 
    /// Object id of offset surface if created successfully. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createOffsetSurface ( AcDbEntity* pInputSurface,
                                                                  double offsetDistance,
                                                                  bool  bAssociativeEnabled,
                                                                  AcDbObjectId& offsetSurfaceId);

    /// <summary> 
    /// Creates an extend surface from the given set of edges from a surface
    /// and adds the surface to the current database. All input edges 
    /// should be connected and coming from same surface.
    /// </summary>
    /// <param name="sourceSurface">
    /// Surface id from which edges needs to be extended to create extend surface.
    /// </param>
    /// <param name="edges"> 
    /// Input full sub-entity paths of the edges, that needs to be extended.
    /// </param>
    /// <param name="extDist"> 
    /// Input distance by which surface needs to be extended.
    /// </param>
    /// <param name="extOption"> 
    /// Extension option, if edges needs to be extended or stretched.
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether extend surface associativity is enabled. 
    /// </param>
    /// <param name="newExtendSurfaceId"> 
    /// ObjectId to the extend surface if created successfully. 
    /// </param>
    /// <returns>
    /// Acad::eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus createExtendSurface ( AcDbObjectId sourceSurface, 
                                                             const AcArray<AcDbSubentId>& edges,  
                                                             double extDist, 
                                                             EdgeExtensionType extOption, 
                                                             bool  bAssociativeEnabled, 
                                                             AcDbObjectId& newExtendSurfaceId );
    
    
    /// <summary> 
    /// Trims a surface with given cutting surfaces/curves. A surface can be trimmed by other surfaces
    /// or curves. When curves are used, the actual trimming boundary is formed by projecting the curves
    /// onto the surface, so the additional information of project direction needs to be provided.
    /// </summary>
    /// <param name="blankSurfaceId"> 
    /// Original input surface to be trimmed. 
    /// </param>
    /// <param name="toolIds"> 
    /// array of ids of cutting entities that their bodies will be directly used to trim the 
    /// surface without further treatment such as projection. 
    /// </param>
    /// <param name="toolCurveIds"> 
    /// array of ids of cutting curves that will be used to trim the surface by first 
    /// projecting them to the surface 
    /// </param>
    /// <param name="projVectors"> 
    /// array of projection direction of each cutting curve in toolCurveIds, so the length of projVectors
    /// should be equal to the length of toolCurveIds
    /// </param>
    /// <param name="pickPoint"> 
    /// pick point that is used to specify which area of a surface should be trimmed. 
    /// </param>
    /// <param name="viewVector"> 
    /// when using pick point to find out which area to trim, caller should also specify the view direction
    /// which will be used form a ray starting from the pick point in the view direction and see which area
    /// is hit by the ray first. 
    /// </param>
    /// <param name="bAutoExtend"> 
    /// If this option is set then when a tool body consists of a single face with analytic geometry, 
    /// the underlying geometry will be extended as much as possible to make sure the surface is trimmed. 
    /// The tool body supplied will not be modified.
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether the surface trimming operation should be associative. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT static Acad::ErrorStatus trimSurface( const AcDbObjectId &blankSurfaceId, 
                                                    const AcDbObjectIdArray &toolIds,
                                                    const AcDbObjectIdArray &toolCurveIds, 
                                                    const AcArray<AcGeVector3d> projVectors,
                                                    const AcGePoint3d& pickPoint, 
                                                    const AcGeVector3d& viewVector,
                                                    bool bAutoExtend,
                                                    bool bAssociativeEnabled);

    // Convert planar surface to region.  Return separate region for each face.
    virtual Acad::ErrorStatus convertToRegion ( AcArray<AcDbEntity*>& regions );

    // Create a 3DSOLID by thickening the surface by a 
    // specified amount.
    virtual Acad::ErrorStatus thicken(double thickness,
        bool bBothSides, AcDb3dSolid*& pSolid) const;

    virtual Acad::ErrorStatus createInterferenceObjects(
        AcArray<AcDbEntity*>& interferenceObjects,
        AcDbEntity* pEntity, unsigned int flags ) const;

    virtual Acad::ErrorStatus booleanUnion(const AcDbSurface* pSurface2,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus booleanSubtract(const AcDbSurface* pSurface2,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus booleanSubtract(const AcDb3dSolid* pSolid,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus booleanIntersect(const AcDbSurface* pSurface2,
        AcArray<AcDbEntity*>& intersectionEntities);
    virtual Acad::ErrorStatus booleanIntersect(const AcDb3dSolid* pSolid,
        AcArray<AcDbEntity*>& intersectionEntities);
    virtual Acad::ErrorStatus imprintEntity(const AcDbEntity* pEntity);
    virtual Acad::ErrorStatus createSectionObjects(const AcGePlane& sectionPlane,
        AcArray<AcDbEntity*>& sectionObjects) const;
    virtual Acad::ErrorStatus sliceByPlane(const AcGePlane& slicePlane,
        AcDbSurface*& pNegHalfSurface, AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus sliceBySurface(
        const AcDbSurface* pSlicingSurface, AcDbSurface*& pNegHalfSurface,
        AcDbSurface*& pNewSurface);
    virtual Acad::ErrorStatus chamferEdges(
        const AcArray<AcDbSubentId *> &edgeSubentIds,
        const AcDbSubentId& baseFaceSubentId, 
        double baseDist, double otherDist);
    virtual Acad::ErrorStatus filletEdges(
        const AcArray<AcDbSubentId *> &edgeSubentIds,
        const AcGeDoubleArray& radius, 
        const AcGeDoubleArray& startSetback, 
        const AcGeDoubleArray& endSetback);

    /// <summary> 
    /// This method creates associative chamfers at the specified edges of the 
    /// surface based on input bAssociativeEnabled.
    /// </summary>
    /// <param name="edgeSubentIds"> 
    /// Input object ids of edges at which the chamfer will be applied.
    /// </param>
    /// <param name="baseFaceSubentId"> 
    /// Input object id of the base face where the chamfer will be applied.
    /// </param>
    /// <param name="baseDist"> 
    /// Input chamfer distance on the base face.
    /// </param>
    /// <param name="otherDist"> 
    /// Input chamfer distance on the other faces. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// A flag to indicate whether chamfer needs to be associative.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT Acad::ErrorStatus chamferEdges(
        const AcArray<AcDbSubentId *> &edgeSubentIds,
        const AcDbSubentId& baseFaceSubentId, 
        double baseDist, double otherDist, bool bAssociativeEnabled);

    /// <summary> 
    /// This method creates associative fillets at the specified edges of the 
    /// surface based on input bAssociativeEnabled.
    /// </summary>
    /// <param name="edgeSubentIds"> 
    /// Input object ids of the edges where the fillet will be applied.
    /// </param>
    /// <param name="radius"> 
    /// Input fillet radius. 
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// A flag to indicate whether chamfer needs to be associative.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT Acad::ErrorStatus filletEdges(
        const AcArray<AcDbSubentId *> &edgeSubentIds,
        double radius, bool bAssociativeEnabled);

    virtual Acad::ErrorStatus setSubentColor(const AcDbSubentId& subentId,
        const AcCmColor& color);
    virtual Acad::ErrorStatus getSubentColor(const AcDbSubentId& subentId,
        AcCmColor& color) const;

    virtual Acad::ErrorStatus setSubentMaterial(const AcDbSubentId& subentId,
        const AcDbObjectId& matId);
    virtual Acad::ErrorStatus getSubentMaterial(const AcDbSubentId& subentId,
        AcDbObjectId& matId) const;

    virtual Acad::ErrorStatus setSubentMaterialMapper(const AcDbSubentId& subentId,
        const AcGiMapper& mapper);
    virtual Acad::ErrorStatus getSubentMaterialMapper(const AcDbSubentId& subentId,
        AcGiMapper& mapper) const;

    virtual Acad::ErrorStatus getArea(double& area) const;

    ACDB_PORT virtual void dragStatus(const AcDb::DragStat) override;

    virtual void* ASMBodyCopy(bool bDeepCopy = false) const;        // INTERNAL USE ONLY
    virtual void const *      getLockedASMBody();                   // INTERNAL USE ONLY
    virtual void              unlockASMBody();                      // INTERNAL USE ONLY
    virtual void*             getLockedWritableASMBody();           // INTERNAL USE ONLY
    virtual void              commitWritableASMBody();              // INTERNAL USE ONLY
    virtual Acad::ErrorStatus setASMBody(const void* modelerBody);  // INTERNAL USE ONLY
    
    virtual AcDbSubentId internalSubentId(void* ent) const;          // INTERNAL USE ONLY
    virtual void* internalSubentPtr(const AcDbSubentId& id) const;   // INTERNAL USE ONLY

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;

    virtual Adesk::UInt16       uIsolineDensity() const;
    virtual Acad::ErrorStatus   setUIsolineDensity(Adesk::UInt16 numIsolines);

    virtual Adesk::UInt16       vIsolineDensity() const;
    virtual Acad::ErrorStatus   setVIsolineDensity(Adesk::UInt16 numIsolines);

    /// <summary> 
    /// Get WireframeType.
    /// </summary>
    /// <returns>
    /// WireframeType.
    /// </returns>
    ///
    ACDB_PORT WireframeType       getWireframeType() const;

    /// <summary> 
    /// Set WireframeType.
    /// </summary>
    /// <param name="type"> 
    /// WireframeType to set.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT Acad::ErrorStatus   setWireframeType(WireframeType type);

    /// <summary> 
    /// Return the perimeter of surface.
    /// </summary>
    /// <param name="perimeter"> 
    /// Perimeter of surface.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    ACDB_PORT Acad::ErrorStatus   getPerimeter(double& perimeter) const;
    
    // advanced surface methods
    //

    /// <summary> 
    /// Get creation action body ID.
    /// </summary>
    /// <returns>
    /// Creation action body id.
    /// </returns>
    ///
    AcDbObjectId ACDB_PORT creationActionBodyId() const;

    /// <summary>
    /// Get moddification action body IDs. 
    /// </summary>
    /// <param name="modificationActionBodyIds"> 
    /// An array to store the returned action body IDs.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ///
    Acad::ErrorStatus ACDB_PORT modificationActionBodyIds(AcDbObjectIdArray& modificationActionBodyIds) const;

    /// <summary>
    /// Extends the edges of this surface by mergeing the extended/stretched
    /// edges to existing surface.
    /// </summary>
    /// <param name="edges"> 
    /// Input full sub-entity paths of the edges, that needs to be extended.
    /// </param>
    /// <param name="extDist"> 
    /// Input distance by which surface needs to be extended.
    /// </param>
    /// <param name="extOption"> 
    /// Extension option, if edges needs to be extended or stretched.
    /// </param>
    /// <param name="bAssociativeEnabled"> 
    /// Specifies whether extend surface associativity is enabled. 
    /// </param>
    /// <returns>
    /// Acad::eOk if successful.
    /// </returns>
    ///
    ACDB_PORT Acad::ErrorStatus extendEdges(AcDbFullSubentPathArray& edges,  
        double extDist, EdgeExtensionType extOption, bool  bAssociativeEnabled);

    /// <summary>
    /// Ray test with the surface. This function will create a ray starting
    /// from rayBasePoint with ray direction defined by rayDir. The rayRadius
    /// defines the tolerance during the intersection check. The returned
    /// subentities could be faces/edges/vertices.
    /// </summary>
    /// <param name="rayBasePoint"> 
    /// Input base point of the ray.
    /// </param>
    /// <param name="rayDir"> 
    /// Input ray direction.
    /// </param>
    /// <param name="rayRadius"> 
    /// input tolerance during the intersection check.
    /// </param>
    /// <param name="subEntIds"> 
    /// Returned array including faces, edges and vertices.
    /// </param>
    /// <param name="parameters"> 
    /// Returned array of doubles indicating the intersection
    /// parameter on the ray with the returned subentities.
    /// The smaller of the parameter, the closer to the base point.
    /// </param>
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    Acad::ErrorStatus ACDB_PORT rayTest(const AcGePoint3d& rayBasePoint, const AcGeVector3d& rayDir,
                              double rayRadius, AcArray<AcDbSubentId>& subEntIds, AcGeDoubleArray& parameters) const;

    // TODO: need to add the work for multi-face body case.
    /// <summary>
    /// Convert to nurb surfaces. The caller should free the returned nurb surface.
    /// </summary>
    /// <param name="nsArray"> 
    /// The generated Nurb Surface array
    /// </param>
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    Acad::ErrorStatus ACDB_PORT convertToNurbSurface(AcDbNurbSurfaceArray& nsArray);

    // AcDbEntity override
    virtual Acad::ErrorStatus getPlane(AcGePlane& plane,
                                       AcDb::Planarity& planarity) const override;

protected:
    // AcDbEntity methods
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;

public:

    /// <summary>
    /// This method creates non-database resident entities
    /// by projecting the given entity along the projection direction
    /// to this surface.
    /// </summary>
    /// <param name="pEntityToProject">
    /// Pointer to the entity to be projected.
    /// </param>
    /// <param name="projectionDirection">
    /// Vector specifying the direction of the projection.
    /// </param>
    /// <param name="projectedEntities">
    /// Array of pointers to non-database resident entities created
    /// by the projection of the given entity along the projection
    /// direction to this 3D solid.
    /// </param>
    /// <returns>
    /// <para>Acad::eOk if successful.</para>
    /// <para>Acad::eInvalidInput if the given entity pointer is NULL or an unsupported type.</para>
    /// <para>Acad::eGeneralModelingFailure if the projection fails to generate valid results.</para>
    /// </returns>
    /// <remarks>When an AcDbPoint is given as the entity to be projected,
    /// the result of the projection will be an AcDbPoint representing
    /// the nearest point on the surface.
    /// </remarks>
    /// <example>
    /// <![CDATA[// Project a circle onto a box
    /// AcDbCircle* pCircle = new AcDbCircle(AcGePoint3d(3.0,3.0,7.0),AcGeVector3d(-0.537925, -0.651525, -0.534932), 1.0);
    /// // TODO: create planesurf from a circle
    /// pBox->createBox(20.0,20.0,1.0);
    /// AcArray<AcDbEntity*> projectedEntities;
    /// Acad::ErrorStatus es = pBox->projectOnToBody(pCircle,
    ///     AcGeVector3d(0.0,0.0,1.0), projectedEntities);]]>
    /// </example>
    /// <seealso cref="AcArray, AcDbPoint" />
    ///
    Acad::ErrorStatus projectOnToSurface(const AcDbEntity* pEntityToProject,
        const AcGeVector3d& projectionDirection,
        AcArray<AcDbEntity*>& projectedEntities) const;
        
    /// <summary>
    /// This method is used by AutoCAD to determine whether or not to use
    /// cached graphics for the object.  If the method returns true, then
    /// cached graphics will be used.  The default implementation is to
    /// return true. Only database resident entities can use graphics
    /// caching, so this method is not called for entities not in an AcDbDatabase.
    /// </summary>
    ACDB_PORT virtual bool usesGraphicsCache();
};
#pragma pack(pop)
