
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

/// <summary>
///  helper class to get/set XRef layer overrides
/// </summary>

class ACDBCORE2D_PORT AcXRefLayerPropertyOverride
{
public:

    /// <summary>
    /// This enum type indicates which Xref layer property is overridden in the host drawing 
    /// It can be used to get/set specific property override of Xref layer
    /// The corresponding value of sysvar "VISRETAINMODE" is listed as below also
    /// </summary>
    enum XRefLayerPropertyOverrideType
    {
        On           = 0,    //VISRETAINMODE = 1
        Freeze       = 1,    //VISRETAINMODE = 2
        Lock         = 2,    //VISRETAINMODE = 4
        Plot         = 3,    //VISRETAINMODE = 8
        Color        = 4,    //VISRETAINMODE = 16
        Linetype     = 5,    //VISRETAINMODE = 32
        Lineweight   = 6,    //VISRETAINMODE = 64
        Transparency = 7,    //VISRETAINMODE = 128
        PlotStyle    = 8,    //VISRETAINMODE = 256
        NewVPFreeze  = 9,    //VISRETAINMODE = 512
        Description  = 10    //VISRETAINMODE = 1024
    };


    /// <summary>
    /// This function is to check whether the Xref layer property is overridden or not in host drawing.
    /// If xdata flag is not found in the Xref layer, we will use Xref cache to compare the layer property from Xref and current layer property in host drawing,
    /// and take it as overridden if they are different.
    /// If xdata is already added, then the bit coded data in xdata will be parsed to check whether the specified property is overridden or not
    /// </summary>
    /// <param name="hostLayerId">
    /// The XRef layer record id in host drawing
    /// </param>
    /// <param name="property">
    /// the enum value specifing which property to query
    /// </param>
    /// <returns>
    /// Returns true if the given property is overridden in XRef layer (in host drawing)
    /// </returns>
    static bool hasXRefLayerOverride(const AcDbObjectId& hostLayerId, XRefLayerPropertyOverrideType property);

    /// <summary>
    /// Shortcut of hasXrefLayerOverride, return true if any Xref layer property override found in the Xref layer
    /// </summary>
    /// <param name="hostLayerId">
    /// The XRef layer record id in host drawing
    /// </param>
    /// <returns>
    /// return true if any XRef layer property override found in the layer
    /// </returns>

    static bool hasAnyXRefLayerOverrides(const AcDbObjectId& hostLayerId);

    /// <summary>
    /// Shortcut of hasXrefLayerOverride, return true if any Xref layer property override found in the host drawing
    /// </summary>
    /// <param name="pHostDb">
    /// The pointer to host drawing's database
    /// </param>
    /// <returns>
    /// return true if any XRef layer property override found in the host drawing
    /// </returns>

    static bool hasAnyXRefLayerOverrides(AcDbDatabase* pHostDb);

    /// <summary>
    /// Check whether the external reference has layer overrides
    /// </summary>
    /// <param name="pRef">
    /// The pointer to xref block reference
    /// </param>
    /// <returns>
    /// return true if the external reference has layer overrides
    /// </returns>

    static bool hasXRefLayerOverride(AcDbBlockReference* pRef);

    /// <summary>
    /// This function is set which layer property is overridden in a Xref layer (in host drawing)
    /// the flag is saved in xdata of Xref layer with in the host drawing
    /// </summary>
    /// <param name="layerId">
    /// The XRef layer record id in host drawing
    /// </param>
    /// <param name="property">
    /// the enum value indicating which property to set
    /// </param>
    /// <returns>
    /// return Acad::eOk if override is successfully added
    /// </returns>
    static Acad::ErrorStatus addXRefLayerOverride(const AcDbObjectId& hostLayerId, XRefLayerPropertyOverrideType property);

    /// <summary>
    /// This function is to turn off the flag in XRef layer indicating which layer property will be overridden
    /// </summary>
    /// <param name="layerId">
    /// The XRef layer record id in host drawing
    /// </param>
    /// <param name="property">
    /// the enum value indicating which property to remove
    /// </param>
    /// <returns>
    /// return Acad::eOk if override is successfully removed
    /// </returns>

    static Acad::ErrorStatus removeXRefLayerOverride(const AcDbObjectId& hostLayerId, XRefLayerPropertyOverrideType property);


	/// <summary>
	/// shortcut of removeXRefLayerOverrides, remove specified layer property override in the whole drawing
	/// </summary>
	/// <param name="pHostDb">
	/// The pointer to host drawing's database
	/// </param>
	/// <param name="property">
	/// the enum value indicating which property to remove
	/// </param>
	/// <returns>
	/// return Acad::eOk if override is successfully removed
	/// </returns>

	static Acad::ErrorStatus removeXRefLayerOverride(AcDbDatabase* pHostDb, XRefLayerPropertyOverrideType property);


	/// <summary>
    /// Shortcut of removeXRefLayerOverride, remove all XRef layer property overrides
    /// </summary>
    /// <param name="layerId">
    /// The XRef layer record id in host drawing
    /// </param>
    /// <returns>
    /// return Acad::eOk if all overrides of this layer are successfully removed
    /// </returns>
    static Acad::ErrorStatus removeXRefLayerOverrides(const AcDbObjectId& hostLayerId);


    /// <summary>
    /// shortcut of removeXRefLayerOverride, remove all XRef layer property overrides in the whole drawing
    /// </summary>
    /// <param name="pHostDb">
    /// The pointer to host drawing's database
    /// </param>
    /// <returns>
    /// return Acad::eOk if all overrides of this layer are successfully removed
    /// </returns>

    static Acad::ErrorStatus removeXRefLayerOverrides(AcDbDatabase* pHostDb);

    /// <summary>
    /// To enable Xref layer override recording
    /// if override recording is enabled, then any modification on Xref layer property will be automatically marked as an override,
    /// including both cases that it's modified by objectARX API and UI command, 
    /// For example layer edited in UI like layer manager dialog or "-layer" in command line
    /// or modified with AcDbLayerTableRecord APIs.
    /// Note: by default the Xref override recording is enabled
    /// </summary>

    static void enableXRefLayerPropertyOverrideRecording();

    /// <summary>
    /// To disable XRef layer override recording
    /// if override recording is disabled, then the modification on XRef layer property will *not* be automatically marked as an override
    /// xdata flag will *not* be added for this layer property in layer table record's xdata
    /// note: by default the xref override recording is enabled
    /// </summary>

    static void disableXRefLayerPropertyOverrideRecording();

    /// <summary>
    /// To check whether XRef layer override recording is enabled
    /// If override recording is enabled, then any modification on Xref layer property will be automatically marked as an override
    /// </summary>
    /// <returns>
    /// return true if XRef layer override recording is enabled, otherwise return false
    /// </returns>
    static bool isXRefLayerPropertyOverrideRecordingEnabled();


};

