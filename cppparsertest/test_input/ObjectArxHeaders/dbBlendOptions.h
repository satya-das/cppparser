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
// The AcDbBlendOptions class is used to encapsulate options for
// blend surface.

#pragma once

#ifndef DBBLENDOPTIONS_H
#define DBBLENDOPTIONS_H

#include "acdb.h"

#pragma pack(push, 8)

/// <summary>Utility class to specify options for blend surface. </summary>
///
class ACDB_PORT AcDbBlendOptions
{
public:
    /// <summary> Default constructor. </summary>
    ///
    AcDbBlendOptions ();

    /// <summary> Default destructor. </summary>
    ///
    ~AcDbBlendOptions ();

    /// <summary>
    ///   <para>The drive mode property defines which section(s) "drive" the creation of the planes </para>
    ///   <para>containing the planar guides. Any of the two input sections can be selected for </para>
    ///   <para>that role, or both of them can be used at the same time (the default value). </para>
    ///   <para>The implementation uses the driving sections in conjunction with the coplanar point </para>
    ///   <para>and direction (if supplied).</para>
    /// </summary>
    ///
    enum DriveModeType {
        kDriveModeFirst  = 0,
        kDriveModeSecond = 1,
        kDriveModeBoth   = 2
    };

    /// <summary>Assignment operator for AcDbBlendOptions.</summary>
    /// <param name="src">Input specifying source AcDbBlendOptions object</param>
    /// <returns>Return AcDbBlendOptions object</returns>
    ///
    AcDbBlendOptions& operator = ( const AcDbBlendOptions& src );

    /// <summary>
    ///   <para>The simplify option allows the application to replace the output ASM procedural </para>
    ///   <para>blend spline surface with an analytic surface, but only if the analytic surface </para>
    ///   <para>is an exact match. This option is enabled by default.</para>
    /// </summary>
    /// <returns>Return true or false. The default value is true. </returns>
    ///
    bool  simplify () const;

    /// <summary>
    ///   <para>The simplify option allows the application to replace the output ASM procedural </para>
    ///   <para>blend spline surface with an analytic surface, but only if the analytic surface </para>
    ///   <para>is an exact match. This option is enabled by default.</para>
    /// </summary>
    /// <param name="val"> Input specifying true or false </param>
    /// <returns> Return Acad::eOk if successful. </returns>
    Acad::ErrorStatus  setSimplify ( bool val );

    /// <summary>
    ///   <para>The solid option allows the implementation to stitch the output surface to the </para>
    ///   <para>input section curves in order to produce a solid body. This function is reserved </para>
    ///   <para>for future use.  Currently, blend surface always output an surface.  It cannot </para>
    ///   <para>output solid.</para>
    /// </summary>
    /// <returns>Return true or false.</returns>
    ///
    bool  solid () const;

    /// <summary>
    ///   <para>The solid option allows the implementation to stitch the output surface to the </para>
    ///   <para>input section curves in order to produce a solid body. This function is reserved </para>
    ///   <para>for future use.  Currently, blend surface always output an surface.  It cannot </para>
    ///   <para>output solid.</para>
    /// </summary>
    /// <param name="val">Input specifying true or false</param>
    /// <returns>Return Acad::eOk if successful.</returns>
    ///
    Acad::ErrorStatus  setSolid ( bool val );

    /// <summary>
    ///   <para>The quality option controls how many planar curves (aka planar guides) blending </para>
    ///   <para>between the input sections are made by the implementation to constrain the </para>
    ///   <para>output surface. More planar guides will result in a blend surface that has a </para>
    ///   <para>better shape; however, the representation of the surface becomes more complex </para>
    ///   <para>which results in larger storage requirements and larger evaluation times. The </para>
    ///   <para>default value is 5. The value of 0 has a special meaning: In this case the </para>
    ///   <para>output surface will coincide with the standard loft output for the same input </para>
    ///   <para>sections and might have a significantly different shape from the surface </para>
    ///   <para>produced for a quality value >=1.</para>
    /// </summary>
    /// <returns>Return an unsigned integer</returns>
    ///
    unsigned int  quality () const;

    /// <summary>
    ///   <para>The quality option controls how many planar curves (aka planar guides) blending </para>
    ///   <para>between the input sections are made by the implementation to constrain the </para>
    ///   <para>output surface. More planar guides will result in a blend surface that has a </para>
    ///   <para>better shape; however, the representation of the surface becomes more complex </para>
    ///   <para>which results in larger storage requirements and larger evaluation times. The </para>
    ///   <para>default value is 5. The value of 0 has a special meaning: In this case the </para>
    ///   <para>output surface will coincide with the standard loft output for the same input </para>
    ///   <para>sections and might have a significantly different shape from the surface </para>
    ///   <para>produced for a quality value >=1.</para>
    /// </summary>
    /// <param name="val">Input specifying a non-negative integer value for quality</param>
    /// <returns>Return Acad::eOk if successful</returns>
    ///
    Acad::ErrorStatus  setQuality ( unsigned int val );

    /// <summary>
    ///   <para>The coplanar point is an optional property that can be supplied to constrain the </para>
    ///   <para>set of planes containing the planar guides made by the implementation. If set, </para>
    ///   <para>all guide planes will contain it. By default no coplanar point is set. This </para>
    ///   <para>option is useful in conjunction with the coplanar direction option to define an </para>
    ///   <para>axis contained by all guide planes. An example where such an axis is useful is a </para>
    ///   <para>blend operation between involving a cone: The customer application might prefer </para>
    ///   <para>that all guides planes to contain the cone axis.</para>
    /// </summary>
    /// <returns>Return an AcGePoint3d point</returns>
    ///
    AcGePoint3d*  coplanarPoint () const;

    /// <summary>
    ///   <para>The coplanar point is an optional property that can be supplied to constrain the </para>
    ///   <para>set of planes containing the planar guides made by the implementation. If set, </para>
    ///   <para>all guide planes will contain it. By default no coplanar point is set. This </para>
    ///   <para>option is useful in conjunction with the coplanar direction option to define an </para>
    ///   <para>axis contained by all guide planes. An example where such an axis is useful is a </para>
    ///   <para>blend operation between involving a cone: The customer application might prefer </para>
    ///   <para>that all guides planes to contain the cone axis.</para>
    /// </summary>
    /// <param name="pPt">Input specifying an AcGePoint3d point</param>
    /// <returns>Return Acad::eOk if successful</returns>
    ///
    Acad::ErrorStatus  setCoplanarPoint ( const AcGePoint3d* pPt );

    /// <summary>
    ///   <para>The coplanar direction is an optional property that can be supplied to constrain </para>
    ///   <para>the set of planes containing the planar guides made by the implementation. If </para>
    ///   <para>set, all guide planes will contain it (i.e. are parallel to it). By default no </para>
    ///   <para>coplanar direction is set.</para>
    /// </summary>
    /// <returns>Return an AcGeVector3d vector</returns>
    ///
    AcGeVector3d*  coplanarDirection () const;

    /// <summary>
    ///   <para>The coplanar direction is an optional property that can be supplied to constrain </para>
    ///   <para>the set of planes containing the planar guides made by the implementation. If </para>
    ///   <para>set, all guide planes will contain it (i.e. are parallel to it). By default no </para>
    ///   <para>coplanar direction is set.</para>
    /// </summary>
    /// <param name="pDir">Input specifying AcGeVector3d vector for coplanar direction</param>
    /// <returns>Return Acad::eOk if successful</returns>
    ///
    Acad::ErrorStatus  setCoplanarDirection ( const AcGeVector3d* pDir );

    /// <summary>
    ///   <para>The drive mode property defines which section(s) "drive" the creation of the </para>
    ///   <para>planes containing the planar guides. Any of the two input sections can be </para>
    ///   <para>selected for that role, or both of them can be used at the same time (the </para>
    ///   <para>default value). The implementation uses the driving sections in conjunction with </para>
    ///   <para>the coplanar point and direction (if supplied).</para>
    /// </summary>
    /// <returns>Return 0,1 or 2 representing kDriveModeFirst, kDriveModeSecond or DriveModeBoth respectively.</returns>
    ///
    AcDbBlendOptions::DriveModeType  driveMode () const;

    /// <summary>
    ///   <para>The drive mode property defines which section(s) "drive" the creation of the </para>
    ///   <para>planes containing the planar guides. Any of the two input sections can be </para>
    ///   <para>selected for that role, or both of them can be used at the same time (the </para>
    ///   <para>default value). The implementation uses the driving sections in conjunction with </para>
    ///   <para>the coplanar point and direction (if supplied).</para>
    /// </summary>
    /// <param name="val">Input integer of value 0, 1, or 2 representing kDriveModeFirst, kDriveModeSecond or DriveModeBoth respectively.</param>
    /// <returns>Return Acad::eOk if successful</returns>
    ///
    Acad::ErrorStatus  setDriveMode( AcDbBlendOptions::DriveModeType val );

private:
    void *mpImpBlendOptions;
    friend class AcDbImpBlendOptions;
};

#pragma pack(pop)

#endif // DBBLENDOPTIONS_H
