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

namespace Autodesk { namespace RealityStudio { namespace SDK { namespace Interface { 
    class ARCSpatialFilter;
}}}};

class AcDbPointCloudDxfHandler;

/// <summary>
/// This class defines a cropping boundary for the AcDbPointCloudEx entity.
/// Each cropping boundary contains a plane which locates the boundary,
/// a cropping type, a flag indicating whether we want what is inside 
/// or outside the region, another flag indicating whether the results of 
/// this cropping boundary should be inverted.
/// </summary>
class ACDB_PORT AcDbPointCloudCrop
{
public:
    /// <summary>
    /// This enumeration defines the crop type (i.e., the shape of the cropping region).
    /// </summary>
    enum CropType
    {
        /// <summary>
        /// Undefined type
        /// </summary>
        kInvalid = 0,

        /// <summary>
        /// Rectangular type
        /// </summary>
        kRectangular,

        /// <summary>
        /// Polygonal type
        /// </summary>
        kPolygonal,

        /// <summary>
        /// Circle type
        /// </summary>
        kCircular
    };

public:
    /// <summary>
    /// Default constructor
    /// </summary>
    AcDbPointCloudCrop();

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="other"> the AcDbPointCloudCrop object that will be copied. </param>
    AcDbPointCloudCrop(const AcDbPointCloudCrop& other);

    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~AcDbPointCloudCrop();

    /// <summary>
    /// Equality operator.
    /// </summary>
    /// <param name="other"> the object to which this cropping region will be compared. </param>
    /// <returns>Returns true if the input object is the same as the current one, or false otherwise.</returns>
    bool operator == (const AcDbPointCloudCrop& other) const;

    /// <summary>
    /// Inequality operator.
    /// </summary>
    /// <param name="other"> the object to which this cropping region will be compared. </param>
    /// <returns>Returns true if the input object is not the same as the current one or false otherwise.</returns>
    bool operator != (const AcDbPointCloudCrop& other) const;

    /// <summary>
    /// Assignment operator.
    /// </summary>
    /// <param name="other"> the cropping region to which this object will be assiged. </param>
    /// <returns>Returns a reference of current object.</returns>
    AcDbPointCloudCrop& operator=(const AcDbPointCloudCrop& other);

    // AcDbEntity helpers used by AcDbPointCloudEx
    //

    /// <summary>
    /// Reads the cropping boundary information from a dwg pFiler.
    /// </summary>
    /// <param name="pFiler">Input filer to use</param>
    /// <returns>Returns Acad::eOk if successful or error code otherwise.</returns>
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler);

    /// <summary>
    /// Writes out the cropping boundary information to a dwg pFiler.
    /// </summary>
    /// <param name="pFiler">Output filer to use</param>
    /// <returns>Returns Acad::eOk if successful or error code otherwise.</returns>
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const;

    /// <summary>
    /// Reads the cropping boundary information via from a dxf pFiler. The flags that are passed in are
    /// essentially data IDs. 
    /// </summary>
    /// <param name="pFiler">Input filer to use</param>
    /// <param name="dxfInt8">Int8 flag used to read data to pFiler</param>
    /// <param name="dxfInt32">Int32 flag used to read data to pFile</param>
    /// <param name="dxfXCoord">XCoord flag used to read data to pFile</param>
    /// <param name="dxfNormalX">NormalX flag used to read data to pFile</param>
    /// <returns>Returns Acad::eOk if successful or error code otherwise.</returns>
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler , Adesk::Int16& dxfInt8, Adesk::Int16& dxfInt32, Adesk::Int16& dxfXCoord, Adesk::Int16& dxfNormalX);
    /// <summary>
    /// Writes out the cropping boundary information to a dxf pFiler. The flags that are passed in are
    /// essentially data IDs. 
    /// </summary>
    /// <param name="pFiler">Output filer to use</param>
    /// <param name="dxfInt8">Int8 flag used to write data to pFiler</param>
    /// <param name="dxfInt32">Int32 flag used to write data to pFile</param>
    /// <param name="dxfXCoord">XCoord flag used to write data to pFile</param>
    /// <param name="dxfNormalX">NormalX flag used to write data to pFile</param>
    /// <returns>Returns Acad::eOk if successful or error code otherwise.</returns>
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler, Adesk::Int16& dxfInt8, Adesk::Int16& dxfInt32, Adesk::Int16& dxfXCoord, Adesk::Int16& dxfNormalX) const;

    /// <summary>
    /// Converts the crop boundary to an ARCSpatialFilter, which are used by internal 
    /// data management classes.
    /// </summary>
    /// <returns>
    /// A pointer to an ARCSpatialFilter. The user needs to call the free() method
    /// to release it.
    /// </returns>
    /// <remarks> internal use </remarks>
    virtual Autodesk::RealityStudio::SDK::Interface::ARCSpatialFilter*  toSpatialFilter() const;

    /// <summary>
    /// Draws the cropping boundary in the point cloud's model coordinate system. This method
    /// is called by AcDbPointCloudEx::subWorldDraw().
    /// </summary>
    /// <param name="geom">
    /// The reference to AcGiGeometry that was given to AcDbPointCloudEx::subWorldDraw().
    /// </param>
    /// <remarks> internal use </remarks>
    virtual void                draw(AcGiGeometry& geom);

    /// <summary>
    /// Clears all cropping boundary information.
    /// </summary>
    void                        clear();

    /// <summary>
    /// Checks if this object represents a valid cropping boundary.
    /// </summary>
    /// <returns>
    /// Returns true if the cropping boundary is valid, or false otherwise.
    /// </returns>
    bool                        isValid() const;

    /// <summary>
    /// Gets the cropping boundary type for this object.
    /// </summary>
    /// <returns>
    /// Returns the type of point cloud crop.
    /// </returns>
    CropType                    type() const;

    /// <summary>
    /// Sets the cropping boundary type for this object.
    /// </summary>
    /// <param name="type"> type of point cloud crop </param>
    void                        setCropType(CropType type);

    /// <summary>
    /// Gets whether this cropping boundary is allowing points inside of itself or outside.
    /// </summary>
    /// <returns>
    /// Returns true if points inside this region are allowed, or false otherwise.
    /// </returns>
    bool                        isInside() const;

    /// <summary>
    /// Sets whether this cropping boundary is allowing points inside of itself or outside.
    /// The default value is inside.
    /// </summary>
    /// <param name="bInside">
    /// Whether to allow points inside this region.
    /// </param>
    void                        setInside(bool bInside);

    /// <summary>
    /// Gets whether this cropping region's results are to be inverted.
    /// </summary>
    /// <returns>
    /// Returns true if cropping result will be inverted, or false otherwise.
    /// </returns>
    bool                        isInverted() const;

    /// <summary>
    /// Sets whether this cropping region's results are to be inverted.
    /// </summary>
    /// <param name="toInvert">
    /// Whether to invert the cropping result.
    /// </param>
    /// <remarks>
    /// This property is used by AcDbPointCloudEx. 
    /// The user can add multiple cropping boundaries to a point cloud object. 
    /// Normally, all boundaries are resulted by intersection.
    /// If the flag is true, the results of all crop boundaries from the first
    /// added one until this current one will be reversed.
    /// </remarks>
    void                        setInvert(bool toInvert);

    /// <summary>
    /// Gets the plane on which this cropping boundary is defined.
    /// </summary>
    /// <param name="plane">
    /// The plane of this cropping boundary.
    /// </param>
    /// <returns>
    /// Returns true if getting the plane successfully, or false otherwise.
    /// </returns>
    bool                        getCropPlane(AcGePlane& plane);

    /// <summary>
    /// Sets the plane on which this cropping boundary is defined.
    /// </summary>
    /// <param name="plane">
    /// The plane of this cropping boundary.
    /// </param>
    void                        setCropPlane(const AcGePlane& plane);

    ///<summary>
    /// Returns the number of points that describe the cropping boundary.
    ///</summary>
    /// <returns>
    /// If the crop type is a rectangle, the count of points is 5, the first and last point are same.
    /// If the crop type is a polygonal, the count of points is more than 3.
    /// If the crop type is a circle, the count of points if 2.
    /// </returns>
    int                         length() const;

    /// <summary>
    /// Sets the points array for point cloud crop boundary.
    /// </summary>
    /// <param name="points">
    /// the array should include the start point for the type of rectangle and polygonal, for example: 
    /// Rectangle -- first corner point, 2nd, 3rd, 4th and first corner point again. 
    /// Polygonal -- 1st, 2nd, 3rd, and etc. points, and the last point is also 1st point again. 
    /// Circular, there are 2 points, center point and any point which is on the circle's circumference.
    /// </param>
    void                        set(const AcGePoint3dArray& points);

    /// <summary>
    /// Gets a reference to the internal array of the cropping boundary points.
    /// </summary>
    /// <returns>Returns a reference to the internal array.</returns>
    const AcGePoint3dArray&     get(); 

public:
    /// <summary>
    /// Sets the DXF handler for a rectangular crop. The previous handler will be released.
    /// The handler will be used to read dxf item data and deal with some errors.
    /// Also, this AcDbPointCloudCrop will be responsible for releasing its DXF handler.
    /// </summary>
    /// <param name="dxfHandler">The DXF handler.</param>
    /// <remarks> internal use </remarks>
    void                        setDxfHandler(AcDbPointCloudDxfHandler* dxfHandler);

private:
    // member variables
    CropType                    m_cropType;
    bool                        m_isInside;
    bool                        m_isInverted;
    AcGePlane                   m_cropPlane;
    AcGePoint3dArray            m_point3dArray;
    AcDbPointCloudDxfHandler*   m_dxfHandler;
};
