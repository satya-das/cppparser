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
// The AcDbRevolvedSurface class is the interface class for representing
// ASM revolved surfaces. 
 
#pragma once
#ifndef DBREVOLVEDSURF_H
#define DBREVOLVEDSURF_H

#include "dbsurf.h"

#pragma pack(push, 8)


class AcDbRevolvedSurface: public AcDbSurface
{
public:

    /// <summary> 
    /// Default constructor.
    /// </summary>
    AcDbRevolvedSurface ();

    /// <summary> 
    /// Destructor.
    /// </summary>
    virtual ~AcDbRevolvedSurface();

    ACDB_DECLARE_MEMBERS(AcDbRevolvedSurface);

    /// <summary> 
    /// Creates a revolved surface from the given profile using the specified options.
    /// </summary>
    /// <param name="pRevEnt"> 
    /// Input profile to be revolved.  This may be an entity such as a curve or
    /// surface or region.
    /// </param>
    /// <param name="axisPnt"> 
    /// Input point on the axis of revolution.  This may be any point on the
    /// axis line.
    /// </param>
    /// <param name="axisDir"> 
    /// Input direction vector of the axis of revolution.  This vector must not
    /// be zero-length.
    /// </param>
    /// <param name="revAngle"> 
    /// Input angle of revolution in radians.
    /// </param>
    /// <param name="startAngle"> 
    /// Input start angle in radians.  The profile will be rotated about this angle
    /// before starting the revolve.  If this angle is 0 then the profile will be
    /// revolved from its current position.
    /// </param>
    /// <param name="sweepOptions"> 
    /// Input sweep options. 
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus createRevolvedSurface ( AcDbEntity* pRevEnt,
        const AcGePoint3d& axisPnt, const AcGeVector3d& axisDir,
        double revAngle, double startAngle,
        AcDbRevolveOptions& revolveOptions );

    /// <summary> 
    /// Returns the entity that was revolved.
    /// </summary>
    /// <returns>
    /// Copy of the entity that was revolved to create the surface.  The caller
    /// should not delete this pointer or post it to the database.
    /// </returns>
    AcDbEntity*   getRevolveEntity () const;

    /// <summary> 
    /// Returns the data of the profile from which the surface was revolved.
    /// </summary>
    /// <returns>
    /// Profile data object.  The caller is responsible for deleting this
    /// pointer if it is not NULL.  If the surface was revolved from an edge
    /// of a surface or solid, then the returned profile object will only 
    /// contain the edge subent data if the surface is associative.
    /// Otherwise it will only contain the curve that was extracted from the
    /// edge.
    /// </returns>
    ACDB_PORT AcDb3dProfile* revolveProfile () const;

    /// <summary> 
    /// Returns point on the axis of revolution.
    /// </summary>
    /// <returns>
    /// Point on the axis of revolution.
    /// </returns>
    AcGePoint3d        getAxisPnt () const;

    /// <summary> 
    /// Set the point on the axis of revolution.
    /// </summary>
    /// <param name="pnt"> 
    /// Input point that the axis of revolution passes through.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setAxisPnt ( const AcGePoint3d& pnt );

    /// <summary> 
    /// Returns direction vector of the axis of revolution.
    /// </summary>
    /// <returns>
    /// Direction vector of the axis of revolution.
    /// </returns>
    AcGeVector3d       getAxisVec () const;

    /// <summary> 
    /// Set the direction vector of the axis of revolution.
    /// </summary>
    /// <param name="vec"> 
    /// Input direction vector of the axis of revolution.
    /// This vector must not be zero-length.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setAxisVec ( const AcGeVector3d& vec );

    /// <summary> 
    /// Returns the angle of revolution.
    /// </summary>
    /// <returns>
    /// Angle of revolution in radians.
    /// </returns>
    double             getRevolveAngle () const;

    /// <summary> 
    /// Set the angle of revolution.
    /// </summary>
    /// <param name="ang"> 
    /// Input angle of revolution in radians.
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setRevolveAngle ( double ang );

    /// <summary> 
    /// Returns the start angle.  The original profile was rotated by this angle
    /// about the axis of revolution before starting the revolve.
    /// </summary>
    /// <returns>
    /// Start angle in radians.
    /// </returns>
    double             getStartAngle () const;

    /// <summary> 
    /// Gets the options that were used to create the surface.
    /// </summary>
    /// <param name="revolveOptions"> 
    /// Output options that were used to create the surface. 
    /// </param>
    void               getRevolveOptions ( AcDbRevolveOptions& revolveOptions ) const;

    /// <summary> 
    /// Set the revolve options.
    /// </summary>
    /// <param name="revolveOptions"> 
    /// Input revolve options.  
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setRevolveOptions ( const AcDbRevolveOptions& revolveOptions );

    /// <summary> 
    /// Set the axis of revolution, revolve angle, and options.
    /// </summary>
    /// <param name="axisPnt"> 
    /// Input point that the axis of revolution passes through.
    /// </param>
    /// <param name="axisVec"> 
    /// Input direction vector of the axis of revolution.
    /// This vector must not be zero-length.
    /// </param>
    /// <param name="revAngle"> 
    /// Input angle of revolution in radians.
    /// </param>
    /// <param name="revolveOptions"> 
    /// Input revolve options.  
    /// </param>
    /// <returns>
    /// eOk if successful.
    /// </returns>
    Acad::ErrorStatus  setRevolve ( const AcGePoint3d& axisPnt, const AcGeVector3d& axisVec,
                                    double revAngle, const AcDbRevolveOptions& revolveOptions );

    // AcDbObject methods
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;
    
    virtual bool isDependent() const;

protected:
    // AcDbEntity methods
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
#pragma pack(pop)

#endif // DBREVOLVEDSURF_H
