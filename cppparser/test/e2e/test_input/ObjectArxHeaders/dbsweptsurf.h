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
// The AcDbSweptSurface class is the interface class for representing
// ASM swept surfaces.  

#pragma once
#ifndef DBSWEPTSURF_H
#define DBSWEPTSURF_H

#include "dbsurf.h"

#pragma pack(push, 8)


class AcDbSweptSurface: public AcDbSurface
{
public:

    /// <summary> 
    /// Default constructor.
    /// </summary>
    AcDbSweptSurface ();

    /// <summary> 
    /// Destructor.
    /// </summary>
    virtual ~AcDbSweptSurface();

    ACDB_DECLARE_MEMBERS(AcDbSweptSurface);

    /// <summary> 
    /// Creates a swept surface from the given profile along the
    /// specified path using the specified options.
    /// </summary>
    /// <param name="pSweepEnt"> 
    /// Input profile to be swept.  This may be an entity such as a curve or
    /// surface or region.
    /// </param>
    /// <param name="pPathEnt"> 
    /// Input path along which sweep profile is to be swept.  This entity must
    /// be a curve.
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus createSweptSurface ( AcDbEntity* pSweepEnt,
        AcDbEntity* pPathEnt, AcDbSweepOptions& sweepOptions );

    /// <summary> 
    /// Returns the entity that was swept.
    /// </summary>
    /// <returns>
    /// Copy of the entity that was swept to create the surface.  The caller
    /// should not delete this pointer or post it to the database.
    /// </returns>
    AcDbEntity*   getSweepEntity () const;

    /// <summary> 
    /// Returns the path entity that the sweep entity was swept along.
    /// </summary>
    /// <returns>
    /// Copy of the path entity. The caller should not delete this
    /// pointer or post it to the database.
    /// </returns>
    AcDbEntity*   getPathEntity () const;

    /// <summary> 
    /// Returns the data of the profile from which the surface was swept.
    /// </summary>
    /// <returns>
    /// Profile data object.  The caller is responsible for deleting this
    /// pointer if it is not NULL.  If the surface was swept from an edge
    /// of a surface or solid, then the returned profile object will only 
    /// contain the edge subent data if the surface is associative.
    /// Otherwise it will only contain the curve that was extracted from the
    /// edge.
    /// </returns>
    ACDB_PORT AcDb3dProfile* sweepProfile () const;

    /// <summary> 
    /// Returns the data of the profile of the path along which the sweep
    /// profile was swept.
    /// </summary>
    /// <returns>
    /// Profile data object.  The caller is responsible for deleting this
    /// pointer if it is not NULL.  If the surface was created by sweeping
    /// along an edge of a surface or solid, then the returned profile object
    /// will only contain the edge subent data if the surface is associative.
    /// Otherwise it will only contain the curve that was extracted from the
    /// edge.
    /// </returns>
    ACDB_PORT AcDb3dProfile* pathProfile () const;

    /// <summary> 
    /// Gets the options that were used to create the surface.
    /// </summary>
    /// <param name="sweepOptions"> 
    /// Output options that were used to create the surface. 
    /// </param>
    void               getSweepOptions ( AcDbSweepOptions& sweepOptions ) const;

    /// <summary> 
    /// Set the sweep options.
    /// </summary>
    /// <param name="sweepOptions"> 
    /// Input sweep options.  
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setSweepOptions ( const AcDbSweepOptions& sweepOptions );

    /// <summary> 
    /// Returns the length of the path curve.
    /// </summary>
    /// <returns>
    /// Length of the path curve.
    /// </returns>
    Acad::ErrorStatus  getPathLength ( double& len ) const;

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

#endif // DBSWEPTSURF_H
