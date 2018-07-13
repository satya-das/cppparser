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
// The AcDbLoftedSurface class is the interface class for representing
// ASM lofted surfaces. 
 
#pragma once

#ifndef DBLOFTEDSURF_H
#define DBLOFTEDSURF_H

#include "dbsurf.h"
#include "db3dProfile.h"

#pragma pack(push, 8)


class AcDbLoftedSurface: public AcDbSurface
{
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbLoftedSurface ();

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbLoftedSurface();

    ACDB_DECLARE_MEMBERS(AcDbLoftedSurface);

    /// <summary> 
    /// Creates a lofted surface from the given curves using the specified options.
    /// The curves must be either all open or all closed. If the curves are all closed,
    /// then this function will accept a point entity as the first and/or last list entry.
    /// Each curve in the guideCurves list must intersect each of the cross-section curves,
    /// so the guide curves form a net-like structure with the cross-section curves.
    /// Both the cross-section curves and the guide curves will lie on the resulting surface.
    /// If any guide curves are passed in this list, then pPathCurve should be null.
    /// If pPathCurve is non-null, then the resulting surface will follow the shape of this
    /// curve as much as possible. This curve does not need to intersect the cross-section
    /// curves and does not even need to be near the cross sections.
    /// If this parameter is non-null, then guideCurves should be an empty list. 
    /// </summary>
    /// <param name="crossSectionCurves"> 
    /// Input array of curve entities to be used as cross sections for the lofting operation. 
    /// </param>
    /// <param name="guideCurves"> 
    /// Input optional array of guide curves. 
    /// </param>
    /// <param name="pPathCurve"> 
    /// Input optional path curve. 
    /// </param>
    /// <param name="loftOptions"> 
    /// Input loft options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus createLoftedSurface (
        AcArray<AcDbEntity*>& crossSectionCurves,
        AcArray<AcDbEntity*>& guideCurves,
        AcDbEntity* pPathCurve, AcDbLoftOptions& loftOptions );

    /// <summary> 
    /// Return the number of cross sections for the surface.
    /// </summary>
    /// <returns>
    /// Number of cross sections.
    /// </returns>
    int           numCrossSections () const;

    /// <summary> 
    /// Returns the cross section entity at zero-based index.  If the cross section
    /// is for an edge or set of edges then the edge curve will be returned.
    /// The caller should not delete this pointer.
    /// </summary>
    /// <param name="idx"> 
    /// Input index of cross section. 
    /// </param>
    /// <returns>
    /// Cross section entity.  The caller should not delete this pointer.
    /// </returns>
    AcDbEntity*   getCrossSection ( int idx ) const;

    /// <summary> 
    /// Return the number of guides for the surface.
    /// </summary>
    /// <returns>
    /// Number of guides.
    /// </returns>
    int           numGuideCurves () const;

    /// <summary> 
    /// Returns the guide curve at zero-based index.  If the guide
    /// is for an edge or set of edges then the edge curve will be returned.
    /// The caller should not delete this pointer.
    /// </summary>
    /// <param name="idx"> 
    /// Input index of guide curve. 
    /// </param>
    /// <returns>
    /// Pointer to guide curve.  The caller should not delete this pointer.
    /// </returns>
    AcDbEntity*   getGuideCurve ( int idx ) const;

    /// <summary> 
    /// Returns the path curve of the surface, or null if no path profile was
    /// used to create the surface.  If the path is for an edge or set of edges
    /// then the edge curve will be returned.
    /// The caller should not delete this pointer.
    /// </summary>
    /// <returns>
    /// Pointer to path entity.  The caller should not delete this pointer.
    /// </returns>
    AcDbEntity*   getPathEntity () const;

    /// <summary> 
    /// Gets the loft options used to create this surface.
    /// </summary>
    /// <param name="loftOptions"> 
    /// Output loft options. 
    /// </param>
    void          getLoftOptions ( AcDbLoftOptions& loftOptions ) const;

    /// <summary> 
    /// Returns the cross section profile at zero-based index.  The returned
    /// object contains the cross section entity and edge data if the profile is
    /// for an edge or set of edges, and also contains the continuity and 
    /// takeoff vector magnitude if idx references the first or last profile.
    /// The caller is responsible for deleting the returned pointer.
    /// </summary>
    /// <param name="idx"> 
    /// Input index of cross section. 
    /// </param>
    /// <returns>
    /// Cross section profile.  The caller is responsible for deleting the returned pointer.
    /// </returns>
    ACDB_PORT AcDbLoftProfile*  crossSection ( int idx ) const;

    /// <summary> 
    /// Returns list of cross section profiles that were used to create the surface.
    /// The returned objects contain the cross section entity and edge data if the
    /// profile is for an edge or set of edges, and also contains the continuity and 
    /// takeoff vector magnitude for the first and last profiles.
    /// The caller is responsible for deleting all pointers in the output list.
    /// </summary>
    /// <param name="crossSections"> 
    /// Output list of cross section profiles. 
    /// </param>
    /// <returns>
    /// Cross section profile.  The caller is responsible for deleting the returned pointer.
    /// </returns>
    ACDB_PORT void              getCrossSections ( AcArray<AcDbLoftProfile*>& crossSections ) const;

    /// <summary> 
    /// Returns the guide profile at zero-based index.  The returned
    /// object contains the guide entity and edge data if the profile is
    /// for an edge or set of edges.  The caller is responsible for deleting the
    /// returned pointer.
    /// </summary>
    /// <param name="idx"> 
    /// Input index of guide. 
    /// </param>
    /// <returns>
    /// Guide profile.  The caller is responsible for deleting the returned pointer.
    /// </returns>
    ACDB_PORT AcDbLoftProfile*  guide ( int idx ) const;

    /// <summary> 
    /// Returns list of guide profiles that were used to create the surface.
    /// The returned objects contain the guide entity and edge data if the
    /// profile is for an edge or set of edges. The caller is responsible for
    /// deleting all pointers in the output list.
    /// </summary>
    /// <param name="guides"> 
    /// Output list of guide profiles. 
    /// </param>
    /// <returns>
    /// Guide profile.  The caller is responsible for deleting the returned pointer.
    /// </returns>
    ACDB_PORT void              getGuides ( AcArray<AcDbLoftProfile*>& guides ) const;

    /// <summary> 
    /// Returns the path profile that was used to create the surface, or null if
    /// no path was used.  The returned object contains the guide entity and edge data
    /// if the profile is for an edge or set of edges.  The caller is responsible for
    /// deleting the returned pointer.
    /// </summary>
    /// <returns>
    /// Path profile, or null if no path was used to create the surface.
    /// The caller is responsible for deleting the returned pointer.
    /// </returns>
    ACDB_PORT AcDbLoftProfile*  path () const;

    /// <summary> 
    /// Returns the continuity at the first profile.
    /// </summary>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then continuity at first cross section will be
    /// returned, otherwise continuity at first guide will be returned. 
    /// </param>
    /// <returns>
    /// 0, 1, or 2 which corresponds to G0, G1, or G2.
    /// </returns>
    ACDB_PORT int               startContinuity ( bool isCrossSection = true ) const;

    /// <summary> 
    /// Returns the continuity at the last profile.
    /// </summary>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then continuity at last cross section will be
    /// returned, otherwise continuity at last guide will be returned. 
    /// </param>
    /// <returns>
    /// 0, 1, or 2 which corresponds to G0, G1, or G2.
    /// </returns>
    ACDB_PORT int               endContinuity ( bool isCrossSection = true ) const;

    /// <summary> 
    /// Returns the magnitude of the surface takeoff vector at the
    /// first profile.
    /// </summary>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then magnitude at first cross section will be
    /// returned, otherwise magnitude at first guide will be returned. 
    /// </param>
    /// <returns>
    /// Magnitude of the surface takeoff vector at the first profile.
    /// </returns>
    ACDB_PORT double            startMagnitude ( bool isCrossSection = true ) const;

    /// <summary> 
    /// Returns the magnitude of the surface takeoff vector at the
    /// last profile.
    /// </summary>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then magnitude at last cross section will be
    /// returned, otherwise magnitude at last guide will be returned. 
    /// </param>
    /// <returns>
    /// Magnitude of the surface takeoff vector at the first profile.
    /// </returns>
    ACDB_PORT double            endMagnitude ( bool isCrossSection = true ) const;

    /// <summary> 
    /// Sets the continuity at the first profile and recreates the surface.
    /// </summary>
    /// <param name="val"> 
    /// Input new continuity (must be 0, 1, or 2). 
    /// </param>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then continuity at first cross section will be
    /// set, otherwise continuity at first guide will be set. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ACDB_PORT Acad::ErrorStatus setStartContinuity ( int val, bool isCrossSection = true );

    /// <summary> 
    /// Sets the continuity at the last profile and recreates the surface.
    /// </summary>
    /// <param name="val"> 
    /// Input new continuity (must be 0, 1, or 2). 
    /// </param>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then continuity at last cross section will be
    /// set, otherwise continuity at last guide will be set. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ACDB_PORT Acad::ErrorStatus setEndContinuity ( int val, bool isCrossSection = true );

    /// <summary> 
    /// Sets the magnitude of the surface takeoff vector at the
    /// first profile and recreates the surface.
    /// </summary>
    /// <param name="val"> 
    /// Input new magnitude (must be non-negative).
    /// </param>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then magnitude at first cross section will be
    /// set, otherwise magnitude at first guide will be set. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ACDB_PORT Acad::ErrorStatus setStartMagnitude ( double val, bool isCrossSection = true );

    /// <summary> 
    /// Sets the magnitude of the surface takeoff vector at the
    /// last profile and recreates the surface.
    /// </summary>
    /// <param name="val"> 
    /// Input new magnitude (must be non-negative).
    /// </param>
    /// <param name="isCrossSection"> 
    /// Input parameter - if true then magnitude at last cross section will be
    /// set, otherwise magnitude at last guide will be set. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ACDB_PORT Acad::ErrorStatus setEndMagnitude ( double val, bool isCrossSection = true );

    /// <summary> 
    /// Sets new loft options and recreates the surface.
    /// </summary>
    /// <param name="guides"> 
    /// Input new loft options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    ACDB_PORT Acad::ErrorStatus setLoftOptions ( const AcDbLoftOptions& loftOptions );

    /// <summary> This enum represents the type of lofted surface. </summary>
    enum LoftSurfaceType
    {
        /// <summary> Created from createLoftedSurface(). </summary>
        kLoftSurf,
        /// <summary> Created from createBlendSurface(). </summary>
        kLoftBlendSurf,
        /// <summary> Created from createNetworkSurface(). </summary>
        kLoftNetworkSurf
    }; 

    /// <summary> 
    /// Returns the type of lofted surface.
    /// </summary>
    /// <returns>
    /// Loft surface type:  ordinary loft, blend, or network.
    /// </returns>
    ACDB_PORT AcDbLoftedSurface::LoftSurfaceType  loftSurfaceType () const;

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;

    virtual bool isDependent() const;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#pragma pack(pop)

#endif // DBLOFTEDSURF_H
