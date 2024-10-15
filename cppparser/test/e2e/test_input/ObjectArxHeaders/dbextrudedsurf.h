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
// The AcDbExtrudedSurface class is the interface class for representing
// ASM extruded surfaces.  

#pragma once
#ifndef DBEXTRUDEDSURF_H
#define DBEXTRUDEDSURF_H

#include "dbsurf.h"

#pragma pack(push, 8)


class AcDbExtrudedSurface: public AcDbSurface
{
public:

    /// <summary> 
    /// Default constructor.
    /// </summary>
    AcDbExtrudedSurface ();

    /// <summary> 
    /// Destructor.
    /// </summary>
    virtual ~AcDbExtrudedSurface();

    ACDB_DECLARE_MEMBERS(AcDbExtrudedSurface);

    /// <summary> 
    /// Creates an extruded surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pSweep"> 
    /// Input profile to be extruded.  This may be an entity such as a curve or
    /// surface or region.
    /// </param>
    /// <param name="directionVec"> 
    /// Input vector that defines the direction and height of the extrusion.
    /// This vector must not be zero-length. 
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus createExtrudedSurface ( AcDbEntity* pSweepEnt,
        const AcGeVector3d& directionVec, AcDbSweepOptions& sweepOptions );

    /// <summary> 
    /// Returns the entity that was extruded.
    /// </summary>
    /// <returns>
    /// Copy of the entity that was extruded to create the surface.  The caller
    /// should not delete this pointer or post it to the database.
    /// </returns>
    AcDbEntity*    getSweepEntity () const;

    /// <summary> 
    /// Returns the data of the profile from which the surface was extruded.
    /// </summary>
    /// <returns>
    /// Profile data object.  The caller is responsible for deleting this
    /// pointer if it is not NULL.  If the surface was extruded from an edge
    /// of a surface or solid, then the returned profile object will only 
    /// contain the edge subent data if the surface is associative.
    /// Otherwise it will only contain the curve that was extracted from the
    /// edge.
    /// </returns>
    ACDB_PORT AcDb3dProfile* sweepProfile () const;

    /// <summary> 
    /// Returns the extrusion vector.
    /// </summary>
    /// <returns>
    /// Vector in which the profile was extruded to create the surface.
    /// The extrusion height is equal to the length of this vector.
    /// </returns>
    AcGeVector3d       getSweepVec () const;

    /// <summary> 
    /// Set the extrusion vector of the surface.
    /// </summary>
    /// <param name="sweepVec"> 
    /// Input vector that defines the direction and length of the extrusion. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setSweepVec ( const AcGeVector3d& sweepVec );

    /// <summary> 
    /// Returns the extrusion height.
    /// </summary>
    /// <returns>
    /// Extrusion height.
    /// </returns>
    double             getHeight () const;

    /// <summary> 
    /// Set the extrusion height.
    /// </summary>
    /// <param name="height"> 
    /// Input extrusion height. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setHeight ( double height );

    /// <summary> 
    /// Gets the options that were used to create the surface.
    /// </summary>
    /// <param name="sweepOptions"> 
    /// Output options that were used to create the surface. 
    /// </param>
    void               getSweepOptions ( AcDbSweepOptions& sweepOptions ) const;

    /// <summary> 
    /// Set the extrusion options.
    /// </summary>
    /// <param name="sweepOptions"> 
    /// Input sweep options.  
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setSweepOptions ( const AcDbSweepOptions& sweepOptions );

    /// <summary> 
    /// Set the extrusion vector and options.
    /// </summary>
    /// <param name="sweepVec"> 
    /// Input vector that defines the direction and length of the extrusion. 
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setExtrude ( const AcGeVector3d& sweepVec,
                                    const AcDbSweepOptions& sweepOptions );

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;
    
    virtual bool isDependent () const;

protected:
    // AcDbEntity methods
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#pragma pack(pop)

#endif // DBEXTRUDEDSURF_H
