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
// DESCRIPTION: Exported class for underlay references in dwg file - AcDbUnderlayReference

#ifndef ACDB_DBUNDERLAYREF_H
#define ACDB_DBUNDERLAYREF_H

#pragma once

#include "dbmain.h"
#include "acstring.h"

#pragma pack (push, 8)

class AcUnderlayLayer;

/// <summary>
/// Abstract class that represents underlays in the drawing. Underlays are similar to raster images
/// but their content is snappable. An AcDbUnderlayReference must reference compatible an AcDbUnderlayDefinition.
/// The AcDbUnderlayRefernece is responsible for the placement of the content within the drawing while AcDbUnderlayDefinition
/// handles the linkage to the underlay content. 
/// Instances of AcDbUnderlayReference derived concrete classes are inserted in a block table record.
/// Instances of AcDbUnderlayDefinition derived concrete classes are inserted into a dictionay off of the named object dictionary.
/// </summary>
class ADESK_NO_VTABLE AcDbUnderlayReference: public AcDbEntity
{
public:
    ACDB_DECLARE_MEMBERS(AcDbUnderlayReference);
    /// <summary>
    /// Destroys the reference.
    /// </summary>
    virtual ~AcDbUnderlayReference() = 0;
    /// <summary>
    /// Gets the position of underlay in WCS (or block space coordinates if the reference is part of a block).
    /// </summary>
    /// <returns>Returns the position of underlay in WCS (or block space coordinates if the reference is part of a block).</returns>
    AcGePoint3d       position() const;
    /// <summary>
    /// Sets the position of underlay in WCS (or block space coordinates if the reference is part of a block).
    /// </summary>
    /// <param name="position">New position value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setPosition(const AcGePoint3d& position);
    /// <summary>
    /// Gets the scale factors used to scale the underlay. Most underlays only allow uniform scaling.
    /// </summary>
    /// <returns>Returns the scale factors used to scale the underlay.</returns>
    AcGeScale3d       scaleFactors() const;
    /// <summary>
    /// Sets the scale factors used to scale the underlay. Most underlays only allow uniform scaling.
    /// </summary>
    /// <param name="scale">New scale value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setScaleFactors(const AcGeScale3d& scale);
    /// <summary>
    /// Gets the rotation value around the axis defined by the point returned by position() and the vector returned by normal().
    /// </summary>
    /// <returns>Returns the rotation value of the underlay.</returns>
    double            rotation() const;
    /// <summary>
    /// Sets the rotation value around the axis defined by the point returned by position() and the vector returned by normal().
    /// </summary>
    /// <param name="rotation">New rotation value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setRotation(double rotation);
    /// <summary>
    /// Gets the normal of the underlay.
    /// </summary>
    /// <returns>Returns the normal of the underlay.</returns>
    AcGeVector3d      normal() const;
    /// <summary>
    /// Sets the normal of the underlay.
    /// </summary>
    /// <param name="normal">New normal value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setNormal(const AcGeVector3d& normal);
    /// <summary>
    /// Gets the transformation matrix from underlay coordinate system to world coordinate system (or block space coordinates if the underlay is part of a block).
    /// the transformation is defined by position(), normal() and rotatation().
    /// </summary>
    /// <returns>Returns the model to WCS transformation of the underlay.</returns>
    AcGeMatrix3d transform() const;
    /// <summary>
    /// Sets the trnsformation matrix of the underlay. 
    /// The translation component of <paramref name="transform"/> will be used to set the position property.
    /// The rotation component of <paramref name="transform"/> will be used to set the rotation property.
    /// The scale component of <paramref name="transform"/> will be used to set the scale property.
    /// </summary>
    /// <param name="transform">New transformation matrix.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setTransform(const AcGeMatrix3d& transform);
    /// <summary>
    /// Gets the object id of the AcDbUnderlayDefinition that this underlay references.
    /// </summary>
    /// <returns>Returns the object id of the AcDbUnderlayDefinition that this underlay references.</returns>
    AcDbObjectId      definitionId() const;
    /// <summary>
    /// Sets the model to world transformation matrix of the underlay. 
    /// The translation component of <paramref name="transform"/> will be used to set the position property.
    /// The rotation component of <paramref name="transform"/> will be used to set the rotation property.
    /// The scale component of <paramref name="transform"/> will be used to set the scale property.
    /// </summary>
    /// <param name="id">New transformation matrix.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setDefinitionId(AcDbObjectId id);

    ACDBCORE2D_PORT Acad::ErrorStatus  setWidth(double width);

    ACDBCORE2D_PORT Acad::ErrorStatus  width(double& width) const;

    ACDBCORE2D_PORT Acad::ErrorStatus  setHeight(double width);

    ACDBCORE2D_PORT Acad::ErrorStatus  height(double& width) const;

	/// <summary>
    /// Gets the clip boundary of the underlay. The boundary is defined in model coordinates. (i.e. One must use
    /// the transformation matrix return by tranform() to obtain WCS points.)
    /// </summary>
    /// <returns>Gets the clip boundary of the underlay.</returns>
    const AcGePoint2dArray&  clipBoundary() const;
    /// <summary>
    /// Sets the clip boundary of the underlay. The boundary is defined in model coordinates. (i.e. Given WCS points one must use
    /// the inverse of the transformation matrix return by tranform() to obtain points that can be passed to this function.)
    /// </summary>
    /// <param name="clipBoundary">New clip boundary. An array describing self interfecting polyline is not allowed. 
    /// An array of two points is allowed and is treated as the minimum, maximum point of a rectangle.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus        setClipBoundary(const AcGePoint2dArray& clipBoundary);
    /// <summary>
    /// Gets a boolean indicating whether the clip boundary should be used.
    /// </summary>
    /// <returns>Returns a boolean indicating whether the clip boundary should be used.</returns>
	bool                     isClipped() const;
    /// <summary>
    /// Sets a boolean indicating whether the clip boundary should be used.
    /// </summary>
    /// <param name="value">New value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus        setIsClipped(bool value);
    /// <summary>
    /// Gets the contrast value for the underlay ([0-100]).
    /// </summary>
    /// <returns>Returns the contrast value for the underlay ([0-100]).</returns>
    Adesk::UInt8      contrast() const;
    /// <summary>
    /// Sets the contrast value for the underlay ([0-100]).
    /// </summary>
    /// <param name="value">New value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setContrast(Adesk::UInt8 value);
    /// <summary>
    /// Gets the fade value for the underlay ([0-100]).
    /// </summary>
    /// <returns>Returns the fade value for the underlay ([0-100]).</returns>
    Adesk::UInt8      fade() const;
    /// <summary>
    /// Sets the fade value for the underlay ([0-100]).
    /// </summary>
    /// <param name="value">New value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setFade(Adesk::UInt8 value);
    /// <summary>
    /// Gets a value indicating whether the underlay content is shown. This variable governs the visibilty of the underlay content not its frame or clipping boundary.
    /// </summary>
    /// <returns>Returns a value indicating whether the underlay content is shown.</returns>
    bool              isOn() const;
    /// <summary>
    /// Sets a value indicating whether the underlay content is shown. This variable governs the visibilty of the underlay content not its frame or clipping boundary.
    /// </summary>
    /// <param name="value">New value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setIsOn(bool value);
    /// <summary>
    /// Gets a value indicating whether the underlay content is shown monochrome. 
    /// </summary>
    /// <returns>Returns a value indicating whether the underlay content is shown monochrome.</returns>
    bool              isMonochrome() const;
    /// <summary>
    /// Sets a value indicating whether the underlay content is shown monochrome. 
    /// </summary>
    /// <param name="value">New value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setIsMonochrome(bool value);
    /// <summary>
    /// Gets a value indicating whether the dwf content is adjusted for the current background color. Not all underlay types observe
    /// this setting.
    /// </summary>
    /// <returns>Returns a value indicating whether the underlay content is adjusted for the current background color.</returns>
    bool              isAdjustedForBackground() const;
    /// <summary>
    /// Sets a value indicating whether the underlay content is adjusted for the current background color. Not all underlay types observe
    /// this setting.
    /// </summary>
    /// <param name="value">New value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setIsAdjustedForBackground(bool value);
    /// <summary>
    /// Gets a value indicating whether frame of the underlay is visible on screen.
    /// </summary>
    /// <returns>returns true if the frame is visible</returns>
    virtual bool isFrameVisible() const;
    /// <summary>
    /// Gets a value indicating whether frame of the underlay is visible in a plot.
    /// </summary>
    /// <returns>returns true if the frame is visible</returns>
    virtual bool isFramePlottable() const;
    /// <summary>
    /// Gets number of layers for this underlay
    /// </summary>
    /// <returns>returns 0 if underlay has no layer information.</returns>
    Adesk::UInt32 underlayLayerCount() const;
    /// <summary>
    /// Get Underlay layer information (layer name and layer on/off state)
    /// for the layer at given index
    /// </summary>
    /// <returns>Returns Acad::eOk if successful</returns>
    Acad::ErrorStatus getUnderlayLayer(int index, AcUnderlayLayer& layer) const;
    /// <summary>
    /// Get Underlay layer information (layer name and layer on/off state)
    /// for the layer name passed in
    /// </summary>
    /// <returns>Returns Acad::eOk if successful</returns>
    Acad::ErrorStatus setUnderlayLayer(int index, const AcUnderlayLayer& layer);
    /// <summary>
    /// Gets lower limit of the legal contrast values.
    /// </summary>
    /// <returns>returns lower limit of the legal contrast values.</returns>
    static Adesk::UInt8 contrastLowerLimit();
    /// <summary>
    /// Gets upper limit of the legal contrast values.
    /// </summary>
    /// <returns>returns upper limit of the legal contrast values.</returns>
    static Adesk::UInt8 contrastUpperLimit();
    /// <summary>
    /// Gets default contrast value.
    /// </summary>
    /// <returns>Returnss default contrast value.</returns>
    static Adesk::UInt8 contrastDefault();
    /// <summary>
    /// Gets lower limit of the legal fade values.
    /// </summary>
    /// <returns>returns lower limit of the legal fade values.</returns>
    static Adesk::UInt8 fadeLowerLimit();
    /// <summary>
    /// Gets upper limit of the legal fade values.
    /// </summary>
    /// <returns>returns upper limit of the legal fade values.</returns>
    static Adesk::UInt8 fadeUpperLimit();
    /// <summary>
    /// Gets default fade value.
    /// </summary>
    /// <returns>Returnss default fade value.</returns>
    static Adesk::UInt8 fadeDefault();
    /// <summary>
    /// Check if clip is inverted.
    /// </summary>
    /// <returns>Returns true if inverted.</returns>
    bool isClipInverted() const;
    /// <summary>
    /// Set if clip is inverted.
    /// </summary>
    /// <param name="value">New value.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setClipInverted(bool value);
    /// <summary>
    /// Generate the clip boundary from a polyline.
    /// </summary>
    /// <param name="polyId">Polyline ID</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus generateClipBoundaryFromPline(AcDbObjectId polyId);
};

/// <summary>
/// Represents DWF underlays in the drawing. Underlays are similar to raster images
/// but their content is snappable.
/// </summary>
class AcDbDwfReference: public AcDbUnderlayReference
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDwfReference);
    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbDwfReference();
    /// <summary>
    /// Destroys the reference.
    /// </summary>
    virtual ~AcDbDwfReference();

protected:
    /// <summary>
    /// Overridden from AcDbEntity
    /// </summary>
    /// <param name="pClsid">See AcDbEntity::getClassID()</param>
    /// <returns>See AcDbEntity::getClassID()</returns>
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

/// <summary>
/// Represents DGN underlays in the drawing. Underlays are similar to raster images
/// but their content is snappable.
/// </summary>
class AcDbDgnReference: public AcDbUnderlayReference
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDgnReference);
    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbDgnReference();
    /// <summary>
    /// Destroys the reference.
    /// </summary>
    virtual ~AcDbDgnReference();

    void setXrefDepth(int depth);

protected:
    /// <summary>
    /// Overridden from AcDbEntity
    /// </summary>
    /// <param name="pClsid">See AcDbEntity::getClassID()</param>
    /// <returns>See AcDbEntity::getClassID()</returns>
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbPdfReference: public AcDbUnderlayReference
{
public:
    ACDB_DECLARE_MEMBERS(AcDbPdfReference);
    /// <summary>
    /// Default constructor.
    /// </summary>
    ACDBCORE2D_PORT AcDbPdfReference();
    /// <summary>
    /// Destroys the reference.
    /// </summary>
    ACDBCORE2D_PORT virtual ~AcDbPdfReference();
protected:
    /// <summary>
    /// Overridden from AcDbEntity
    /// </summary>
    /// <param name="pClsid">See AcDbEntity::getClassID()</param>
    /// <returns>See AcDbEntity::getClassID()</returns>
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
public:
    /// <summary>
    /// Gets default contrast value.
    /// </summary>
    /// <returns>Returnss default contrast value.</returns>
    static Adesk::UInt8 contrastDefault();
    /// <summary>
    /// Gets default fade value.
    /// </summary>
    /// <returns>Returnss default fade value.</returns>
    static Adesk::UInt8 fadeDefault();
};

#pragma pack (pop)

#endif
