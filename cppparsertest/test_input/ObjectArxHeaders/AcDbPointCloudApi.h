
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

#include "gepnt3d.h"
#include "gevec3d.h"

/// <summary>
/// A data buffer that collects point data for a point cloud.
/// </summary>
class __declspec(novtable) IAcDbPointCloudDataBuffer
{
public:
    enum DataType
    {
        kIntensity      = 0x00000001,
        kClassification = 0x00000002,
        kColor          = 0x00000004,
        kNormal         = 0x00000008,
    };

    typedef Adesk::UInt8  RGBA[4];

    virtual ~IAcDbPointCloudDataBuffer() = 0 {};
    
    /// <summary>
    /// Returns the number of points in this buffer
    /// </summary>
    virtual Adesk::UInt64 numPoints() const = 0;

    /// <summary>
    /// Returns a pointer to the array of points
    /// </summary>
    virtual const AcGePoint3d* points() const = 0;

    /// <summary>
    /// Returns a pointer to the array of point normals, or NULL if not available
    /// </summary>
    virtual const AcGeVector3d* normals() const = 0;
    
    /// <summary>
    /// Returns the pointer to the array of point colors, or NULL if not available.
    /// Note that RGB corresponds to red, green, blue color values. The "A" value is reserved for internal usage.
    /// </summary>
    virtual const RGBA* colors() const  = 0;

    /// <summary>
    /// Returns the pointer to the array of point intensities, or NULL if not available
    /// </summary>
    virtual const Adesk::UInt8* intensity()  const = 0;

    /// <summary>
    /// Returns the pointer to the array of point classifications, or NULL if not available
    /// </summary>
    virtual const Adesk::UInt8* classifications() const = 0;

    /// <summary>
    /// Gives the matrix that transforms this buffer's points from its local coordinate system to WCS.
    /// </summary>
    virtual const AcGeMatrix3d& transform() const = 0;

    /// <summary>
    /// Releases this buffer's allocated memory.
    /// </summary>
    virtual void freeObject() = 0;

    /// <summary>
    /// Reserved for internal use. Do not call this method.
    /// </summary>
    virtual void* getBuffer() const = 0;
};


/// <summary>
/// Implement this interface to filter points based on point's coordinate.
/// Efficiency of the implementation of this interface can affect 
/// performance of the point cloud rendering.
/// </summary>
class __declspec(novtable) IAcDbPointCloudSpatialFilter
{
public:

    /// <summmary>
    /// Represents whether a given point is inside, outside, or in the edge of a filter.
    /// </summmary>
    enum FilterResult { FILTER_INSIDE = 0, FILTER_OUTSIDE, FILTER_INTERSECTS };

    /// <summmary>
    /// Destructor
    /// </summmary>
    virtual ~IAcDbPointCloudSpatialFilter() = 0 {};

    /// <summary>
    /// Tests whether an axis-aligned box is inside, outside or on the border of the volume of interest.
    /// </summary>
    /// <param name="min">Min coordinate value of the cell</param>
    /// <param name="max">Max coordinate value of the cell</param>
    ///
    /// <returns>
    /// FILTER_OUTSIDE -- the box is fully rejected (outside the volume of interest)
    /// FILTER_INSIDE -- the box is fully accepted (entire box is inside the volume of interest)
    /// FILTER_INTERSECTS -- the box partially belongs to the volume of interest.
    /// </returns>
    ///
    /// <remarks>
    /// Note: If your filter does not support individual point filtering, you
    /// should only returns FILTER_OUTSIDE or FILTER_OUTSIDE here.
    /// </remarks>
    virtual FilterResult testCell(const AcGePoint3d& min, const AcGePoint3d& max) const = 0;

    /// <summary>
    /// Tests if the point is inside the volume of interest
    /// </summary>
    /// <param name="point">coordinate value of the test point</param>
    ///
    /// <returns>
    /// FILTER_INSIDE  -- if it is accepted because it is inside the volume of interest.
    /// FILTER_OUTSIDE -- if it is rejected because it is outside the volume of interest.
    ///</returns>
    ///
    /// <remarks>
    /// Note: This function will be called once for every point in the cells that
    /// are intersected (testCell() returned FILTER_INTERSECTS) so it needs to be very fast.
    /// </remarks>
    virtual FilterResult testPoint(const AcGePoint3d& point) const = 0;

    /// <summmary>
    /// Creates a copy of this filter that represents the current filter's volume of interest
    /// after being transformed by the given transformation matrix.
    /// </summmary>
    /// <param name="mat">the transform matrix</param>
    /// <returns>
    /// Returns a transformed filter.
    /// </returns>
    virtual IAcDbPointCloudSpatialFilter* transformFilter(const AcGeMatrix3d& mat) const = 0;

    /// <summmary>
    /// Creates a clone of the filter and returns a pointer to the clone.
    /// The filter will always be cloned before it's used.
    /// The filter may be cloned multiple times if multithreaded filtering is enabled.
    /// cloned filters will be released by freeObject()
    /// </summmary>
    ///
    /// <returns>
    /// Returns a copy of the filter.
    /// </returns>
    virtual IAcDbPointCloudSpatialFilter* clone() const = 0;

    /// <summmary>
    /// Deletes the filter itself.
    /// Typically this would be implemented using 'delete this;'.
    /// </summmary>
    virtual void freeObject() = 0;

};

/// <summary>
/// This interface filters points based on point's attribute
/// The attributes include color, intensity, normal and classification.
/// Note that not all attributes may be available. The default value for these attributes are zero
/// Efficiency of the implementation of this interface can critically affect 
/// performance of the point cloud access queries.
/// </summary>
class __declspec(novtable) IAcDbPointCloudAttributeFilter
{
public:
    virtual ~IAcDbPointCloudAttributeFilter() = 0 {};

    /// <summmary>
    /// Checks if a point passes this filter.
    /// </summmary>
    /// <param name="rgba">The color. Note that only the RGB values are valid. The last A value is for internal use only</param>
    /// <param name="intensity">The intensity. Note that this value is not defined if the corresponding scan does not have intensity</param>
    /// <param name="normal">The surface normal. Note that normal value is not in WCS.</param>
    /// <param name="classification">The classification. If the corresponding scan does not have classification then this value is zero</param>
    virtual bool testPoint(const Adesk::UInt8 rgba[4], Adesk::UInt8 intensity, const float normal[3], Adesk::UInt8 classification) const = 0;

    /// <summmary>
    /// Creates a clone of the filter and returns a pointer to the clone.
    /// The filter will always be cloned before it's used.
    /// The filter may be cloned multiple times if multithreaded filtering is enabled.
    /// User should call freeObject() to release the memory when the cloned object is no longer needed.
    /// </summmary>
    ///
    /// <returns>
    /// Returns a copy of the filter.
    /// </returns>
    virtual IAcDbPointCloudAttributeFilter* clone() const = 0;

    /// <summmary>
    /// Creates a copy of this filter that represents the current filter's volume of interest
    /// after being transformed by the given transformation matrix.
    /// </summmary>
    /// <param name="mat">the transform matrix</param>
    /// <returns>
    /// Returns a transformed filter.
    /// </returns>
    virtual IAcDbPointCloudAttributeFilter* transformFilter(const AcGeMatrix3d& mat) const = 0;

    /// <summmary>
    /// Deletes the filter itself.
    /// Typically this would be implemented using 'delete this;'.
    /// </summmary>
    virtual void freeObject() = 0;
};

/// <summary>
/// This interface processes all point data inside of a point cloud.
/// </summary>
class __declspec(novtable) IAcDbPointCloudPointProcessor
{
public:
    enum ProcessSate
    {
        Abort,
        Continue
    };
    virtual ~IAcDbPointCloudPointProcessor() = 0 {};

    /// <description>
    /// Processes the point data inside the data buffer.
    /// </description>
    /// <param name="buffer">Data buffer containing the point data. Do NOT release the buffer.</param>
    /// <returns>
    /// Abort -- cancel the current processing.
    /// Continue -- continue to the next buffer.
    /// </returns>
    virtual ProcessSate process(const IAcDbPointCloudDataBuffer* buffer) = 0;
};