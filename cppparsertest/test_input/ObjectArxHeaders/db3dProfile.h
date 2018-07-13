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
//
// DESCRIPTION:
//
// The AcDb3dProfile class is used to encapsulate profile information for
// certain commands such as EXTRUDE, REVOLVE, SWEEP, and LOFT. 
 
#pragma once
#ifndef DB3DPROFILE_H
#define DB3DPROFILE_H

#include "dbsurf.h"
#include "AcDbGeomRef.h"

class AcDb3dProfileData;

#pragma pack(push, 8)


/// <summary> <para>
/// This class is used to represent a 3d profile that can be used as input to
/// functions such as createExtrudedSurface(), createRevolvedSurface(), and
/// createSweptSurface().  An object of this class can represent an entity
/// such as a curve or a region, or it can represent an edge or a set of edges
/// that form a connected chain.
/// </para> </summary>
///
class ACDB_PORT AcDb3dProfile : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDb3dProfile);

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDb3dProfile ();

    /// <summary> 
    /// Constructor for a profile that is an entity such as a curve or region.
    /// </summary>
    /// <param name="pEntity"> 
    /// Pointer to an AcDbEntity that is to be used as a profile to create
    /// a surface such as an extrusion or loft. 
    /// </param>
    AcDb3dProfile ( AcDbEntity *pEntity );

    /// <summary> 
    /// Constructor for a profile that is a face.  The profile will consist of
    /// the outer edges of the face.
    /// </summary>
    /// <param name="faceSubentPath"> 
    /// Subent path of the face. 
    /// </param>
    AcDb3dProfile ( const AcDbFullSubentPath& faceSubentPath );

    /// <summary> 
    /// Constructor for a profile that is a path.
    /// </summary>
    /// <param name="pathRef"> 
    /// reference to the path
    /// </param>
    AcDb3dProfile ( const AcDbPathRef & pathRef);

    /// <summary> 
    /// Constructor for a profile that is a vertex
    /// </summary>
    /// <param name="vertexRef"> 
    /// reference to the vertex
    /// </param>
    AcDb3dProfile ( const AcDbVertexRef & vertexRef);

    /// <summary> 
    /// Copy constructor.
    /// </summary>
    /// <param name="src"> 
    /// Source object to be copied. 
    /// </param>
    AcDb3dProfile ( const AcDb3dProfile& src );

    /// <summary> 
    /// Destructor.
    /// </summary>
    virtual ~AcDb3dProfile();

    /// <summary> 
    /// Copies the contents of input object into this object.
    /// </summary>
    /// <param name="src"> 
    /// Source object to be copied.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus copyFrom ( const AcRxObject *src ) override;

    /// <summary> 
    /// Returns the profile entity.  If the profile is for an edge or set of
    /// edges then the returned entity will be an AcDbCurve of the edge or edges.
    /// The caller should not delete this pointer or post it to the database.
    /// </summary>
    /// <returns>
    /// Profile entity. The caller should not delete this pointer.
    /// </returns>
    AcDbEntity*  entity () const;

    /// <summary> 
    /// Returns the path reference of the edge if the profile is an edge or
    /// set of edges.  If the profile is not an edge or set of edges, pathRef will be
    /// empty and eInvalidInput will be returned
    /// </summary>
    /// <param name="pathRef"> 
    /// path reference of the edge(s) 
    /// </param>
    /// <returns>
    /// Acad::ErrorStatus
    /// </returns>
    Acad::ErrorStatus getPathRef( AcDbPathRef &pathRef ) const;

    /// <summary> 
    /// Returns the vertex reference of the vertex if the profile is a vertex.
    /// If the profile is not an edge or set of edges, vertexRef will be
    /// empty and eInvalidInput will be returned
    /// </summary>
    /// <param name="vertexRef"> 
    /// vertex reference 
    /// </param>
    /// <returns>
    /// Acad::ErrorStatus
    /// </returns>
    Acad::ErrorStatus getVertexRef( AcDbVertexRef &vertexRef ) const;

    /// <summary> 
    /// Converts profile into new profiles that are of a type that can be used for
    /// extrude, revolve, sweep, or loft operations.  The converted profiles are returned in
    /// the output array.  If this profile is of type AcDbTrace, AcDbSolid, or AcDbFace then
    /// the converted profile will be for a region.  If this profile is of type
    /// AcDb3dPolyline and the profile is linear or whose 'Fit' property is quadratic or
    /// cubic then the converted profile will be a line or a spline.
    /// </summary>
    /// <param name="explodeMultiFaceRegions"> 
    /// If this profile is of type AcDbSurface or AcDbRegion and has more than one face,
    /// then we explode to get multiple surface or region profiles that each have only
    /// one face. 
    /// </param>
    /// <param name="convertSurfaceToEdges"> 
    /// If this profile is a face or is of type AcDbSurface, AcDbRegion, AcDbTrace,
    /// AcDbSolid, or AcDbFace then we convert to an edge profile that is defined by
    /// the surface or region edges.
    /// </param>
    /// <param name="nonPlanarOnly"> 
    /// This parameter is only relevant when convertSurfaceToEdges is set to true.
    /// If this parameter is true then only non-planar surfaces will be converted to
    /// edge profiles.  Regions and planar surfaces will not be converted.
    /// </param>
    /// <param name="outerLoopOnly"> 
    /// This parameter is only relevant when convertSurfaceToEdges is set to true.
    /// If this parameter is true then only the outer loop of the surface or region
    /// will be converted to an edge profile.
    /// </param>
    /// <param name="convertedProfileArr"> 
    /// Output list of converted profiles.  The caller is responsible for
    /// deleting the objects in this list.
    /// </param>
    /// <returns>
    /// eOk if successful.  Even when this function returns eOk, it is possible for
    /// the output list to be empty depending on the profile type and the values of
    /// the other parameters.
    /// </returns>
    Acad::ErrorStatus  convertProfile ( bool explodeMultiFaceRegions, bool convertSurfaceToEdges,
                                        bool nonPlanarOnly, bool outerLoopOnly,
                                        AcArray<AcDb3dProfile*>& convertedProfileArr ) const;

    static AcDb3dProfile* convertProfile(const AcArray<AcDbPathRef>&);
    /// <summary> 
    /// Set the profile to a path.
    /// </summary>
    /// <param name="pathRef"> 
    /// reference to the path
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus set ( const AcDbPathRef &pathRef );

    /// <summary> 
    /// Set the profile to a vertex.
    /// </summary>
    /// <param name="vertexRef"> 
    /// reference to the vertex
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus set ( const AcDbVertexRef &vertexRef );

    /// <summary> 
    /// Set the profile to an entity such as a curve or region.
    /// </summary>
    /// <param name="pEntity"> 
    /// Pointer to an AcDbEntity that is to be used as a profile to create
    /// a surface such as an extrusion or loft. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus set ( AcDbEntity *pEntity );

    /// <summary> 
    /// Return whether the profile forms a closed loop.
    /// </summary>
    /// <returns>
    /// True if profile is closed, false otherwise.
    /// </returns>
    bool  isClosed () const;

    /// <summary> 
    /// Return whether the profile is planar.
    /// </summary>
    /// <returns>
    /// True if profile is planar, false otherwise.
    /// </returns>
    bool  isPlanar () const;

    /// <summary> 
    /// Return whether the profile is an edge or face.
    /// </summary>
    /// <returns>
    /// True if profile is an edge or face, false otherwise.
    /// </returns>
    bool  isSubent () const;

    /// <summary> 
    /// Return whether the profile is a face.
    /// </summary>
    /// <returns>
    /// True if profile is a face, false otherwise.
    /// </returns>
    bool  isFace () const;

    /// <summary> 
    /// Return whether the profile is an edge.
    /// </summary>
    /// <returns>
    /// True if profile is an edge, false otherwise.
    /// </returns>
    bool  isEdge () const;

    /// <summary> 
    /// Return whether the profile is valid and may be used to
    /// create a surface.
    /// </summary>
    /// <returns>
    /// True if profile is a valid entity, edge, or face.
    /// </returns>
    bool  isValid () const;

    /// <summary> 
    /// Merge connected sets of profiles into one or more profiles.
    /// </summary>
    /// <param name="profileArr"> 
    /// Input array of profiles that are to be merged.
    /// </param>
    /// <param name="mergeEdges"> 
    /// If this parameter is false then any edge profiles in the input array will
    /// not be merged and will be copied directly to the ouput array.
    /// </param>
    /// <param name="mergeCurves"> 
    /// If this parameter is false then any curve profiles in the input array will
    /// not be merged and will be copied directly to the ouput array.
    /// </param>
    /// <param name="mergedProfileArr"> 
    /// Output array of merged profiles.  The caller is responsible for deleting all
    /// objects that are returned in this array.
    /// </param>
    /// <returns>
    /// eOk if successful.  
    /// </returns>
    static Acad::ErrorStatus mergeProfiles ( const AcArray<AcDb3dProfile*>& profileArr,
                                             bool mergeEdges, bool mergeCurves,
                                             AcArray<AcDb3dProfile*>& mergedProfileArr );
    
    /// <summary> 
    /// Assignment operator.
    /// </summary>
    /// <param name="src"> 
    /// Source object to be copied. 
    /// </param>
    /// <returns>
    /// Reference to this object.  
    /// </returns>
    AcDb3dProfile& operator = ( const AcDb3dProfile& src );

private:
    friend class AcDb3dProfileData;
    friend class AcDbLoftProfile;

    AcDb3dProfileData *mProfileData;
};


/// <summary> <para>
/// This class is used to represent a profile that can be used as input to
/// createLoftedSurface().  An object of this class can represent an entity
/// such as a curve or a region, or it can represent an edge or a set of edges
/// that form a connected chain.  This class also maintains continuity data
/// if the profile is for an edge or point and the profile is the first or
/// last profile of the loft.
/// </para> </summary>
///
class ACDB_PORT AcDbLoftProfile : public AcDb3dProfile
{
public:

    ACRX_DECLARE_MEMBERS(AcDbLoftProfile);

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbLoftProfile ();

    /// <summary> 
    /// Constructor for a profile that is an entity such as a curve or region.
    /// </summary>
    /// <param name="pEntity"> 
    /// Pointer to an AcDbEntity that is to be used as a profile to create
    /// a surface such as an extrusion or loft. 
    /// </param>
    AcDbLoftProfile ( AcDbEntity *pEntity );

    /// <summary> 
    /// Constructor for a profile that is an edge or a sequence of connected
    /// edges.
    /// </summary>
    /// <param name="pathRef"> 
    /// Subent paths of the edges that make up the profile. 
    /// </param>
    AcDbLoftProfile ( const AcDbPathRef & pathRef);

    /// <summary> 
    /// Constructor for a profile that is a point.
    /// </summary>
    /// <param name="pnt"> 
    /// An AcGePoint3d that is to be used as a profile to create
    /// a surface such as an extrusion or loft. 
    /// </param>
    AcDbLoftProfile ( const AcGePoint3d& pnt );

    /// <summary> 
    /// Copy constructor.
    /// </summary>
    /// <param name="src"> 
    /// Source object to be copied. 
    /// </param>
    AcDbLoftProfile ( const AcDbLoftProfile& src );

    /// <summary> 
    /// Copies the contents of input object into this object.
    /// </summary>
    /// <param name="src"> 
    /// Source object to be copied.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus copyFrom ( const AcRxObject *src ) override;

    /// <summary> 
    /// Return the continuity for the profile: 0, 1, or 2, which
    /// corresponds to a continuity of G0, G1, or G2.  By default, the
    /// continuity is 1 unless it has been explicitly set to another
    /// value.
    /// </summary>
    /// <returns>
    /// Continuity for the profile: 0, 1, or 2, which
    /// corresponds to a continuity of G0, G1, or G2.
    /// </returns>
    Adesk::Int16  continuity () const;

    /// <summary> 
    /// Set the continuity for the profile.
    /// </summary>
    /// <param name="value"> 
    /// Must be 0, 1, or 2, which corresponds to a continuity of
    /// G0, G1, or G2. 
    /// </param>
    void          setContinuity ( Adesk::Int16 value );

    /// <summary> 
    /// Return the magnitude of the takeoff vector if the continuity is
    /// 1 or 2.  By default, this value is 0.5 unless it has been
    /// explicitly set to another value.
    /// </summary>
    /// <returns>
    /// Magnitude of the takeoff vector.
    /// </returns>
    double        magnitude () const;

    /// <summary> 
    /// Set the magnitude of the takeoff vector for the profile if
    /// the continuity is 1 or 2.
    /// </summary>
    /// <param name="value"> 
    /// Magnitude of takeoff vector. 
    /// </param>
    void          setMagnitude ( double value );
    
    /// <summary> 
    /// Assignment operator.
    /// </summary>
    /// <param name="src"> 
    /// Source object to be copied. 
    /// </param>
    /// <returns>
    /// Reference to this object.
    /// </returns>
    AcDbLoftProfile& operator = ( const AcDbLoftProfile& src );
    
    /// <summary> 
    /// Assignment operator.  Copies the entity and edge data from the
    /// input object, but does not change the continuity or magnitude.
    /// </summary>
    /// <param name="src"> 
    /// Source object to be copied. 
    /// </param>
    /// <returns>
    /// Reference to this object.
    /// </returns>
    AcDbLoftProfile& operator = ( const AcDb3dProfile& src );
};

#pragma pack(pop)
#endif // DB3DPROFILE_H
