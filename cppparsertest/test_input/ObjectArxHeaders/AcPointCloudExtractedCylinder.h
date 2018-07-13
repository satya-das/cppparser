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

#include <memory>

class AcPointCloudExtractedCylinderImp;

/// <summary>
/// This class wrap the data structure of a cylinder which is extracted 
/// from point cloud segment and it is used for preview 
/// </summary>
class ACDB_PORT AcPointCloudExtractedCylinder
{
public:
    AcPointCloudExtractedCylinder();
    AcPointCloudExtractedCylinder(double radius, double height, AcGeVector3d axis = AcGeVector3d::kZAxis, AcGePoint3d origin = AcGePoint3d::kOrigin);
    virtual ~AcPointCloudExtractedCylinder();

    AcPointCloudExtractedCylinder(const AcPointCloudExtractedCylinder& o);
    bool operator == (const AcPointCloudExtractedCylinder& o) const;
    bool operator != (const AcPointCloudExtractedCylinder& o) const;
    AcPointCloudExtractedCylinder& operator = (const AcPointCloudExtractedCylinder& o);

    const static AcPointCloudExtractedCylinder kInvalid;

public:
    /// <summary>
    /// Checks if the current extracted cylinder object is valid
    /// </summary>
    /// <returns>
    /// Returns true if it is valid, otherwise return false.
    /// </returns>
    bool isValid() const;

    /// <summary>
    /// Clears all the data of the cylinder.
    /// after calling it, the cylinder is set to AcPointCloudExtractedCylinder::kInvalid
    /// </summary>
    void clear();

    /// <summary>
    /// Gets center line's vector of the cylinder
    /// </summary>
    /// <returns>
    /// Returns axis of cylinder
    /// </returns>
    AcGeVector3d getAxis() const;

    /// <summary>
    /// Sets center line's vector of the cylinder
    /// </summary>
    /// <param name="axis">
    /// Value of axis
    /// </param>    
    void setAxis(AcGeVector3d axis);

    /// <summary>
    /// Gets origin point which locates on the bottom of the cylinder
    /// </summary>
    /// <returns>
    /// Returns value of origin point.
    /// </returns>
    AcGePoint3d getOrigin() const;

    /// <summary>
    /// Sets origin point which locates on the bottom of the cylinder.
    /// </summary>
    /// <param name="origin">
    /// Value of origin point
    /// </param>
    void setOrigin(AcGePoint3d origin);

    /// <summary>
    /// Gets the height of the cylinder.
    /// </summary>
    /// <returns>
    /// Returns value of the height.
    /// </returns>
    double getHeight() const;

    /// <summary>
    /// Sets the height of the cylinder.
    /// </summary>
    /// <param name="height">
    /// Value of height
    /// </param>
    void setHeight(double height);

    /// <summary>
    /// Gets the radius of the cylinder.
    /// </summary>
    /// <returns>
    /// Returns the value of radius.
    /// </returns>
    double getRadius() const;

    /// <summary>
    /// Sets the radius of the cylinder.
    /// </summary>
    /// <param name="radius">
    /// Value of radius
    /// </param>
    void setRadius(double radius);

private: 
    std::unique_ptr<AcPointCloudExtractedCylinderImp> m_pImp;
};