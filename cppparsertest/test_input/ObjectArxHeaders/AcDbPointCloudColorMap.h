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

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// The AcPointCloudColorSchemeCollectionReactor object is an abstract class
/// that gets notified when a AcDbPointCloudColorMap is changed.
/// 
/// </summary>
class ACDB_PORT AcPointCloudColorSchemeCollectionReactor
{
public:
    /// <summary>
    /// This callback function gets called after AcDbPointCloudColorMap is changed
    /// while colorMap is opened with write access.
    /// Do not close the colorMap object that is given to this function.
    /// </summary>
    /// <param name="colorMap">The AcDbPointCloudColorMap that is being changed.</param>
    virtual void PointCloudColorSchemeCollectionChanged(class AcDbPointCloudColorMap* colorMap) = 0;
    
    //////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Destructor 
    /// </summary>
    virtual ~AcPointCloudColorSchemeCollectionReactor();
};

class PointCloudColorMapImp;

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// The AcDbPointCloudColorRamp class represents an intensity or elevation color ramp
/// </summary>
class ACDB_PORT AcDbPointCloudColorRamp
{
public:

    //////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbPointCloudColorRamp();

    //////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Destructor 
    /// </summary>
    ~AcDbPointCloudColorRamp();
    
    /// <summary>
    /// Get the number of colors in this color ramp
    /// </summary>
    /// <returns> Returns The number of colors in this color ramp. </returns>
    Adesk::Int32            numColors() const;

    /// <summary>
    /// Set the number of colors in this color ramp
    /// </summary>
    /// <param name="count">The color count.</param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// If count is not between the minimum number (2) and maximum number (25), returns Acad::eInvalidInput.
    /// </returns>
    /// <remarks>
    /// NOTES: The minimum number is 2, the maximum number of colors is 25.
    /// </remarks>
    Acad::ErrorStatus       setNumColors(Adesk::Int32 count);

    /// <summary>
    /// Gets the color definition at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <returns> the color definition. </returns>
    AcCmEntityColor         color(int c) const;

    /// <summary>
    /// Sets the color definition at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <param name="color">The color definition.</param>
    void                    setColor(int c, AcCmEntityColor color);

    /// <summary>
    /// Gets the visibility of a color at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <returns> Returns whether the color is visible or not. </returns>
    bool                    visibility(int c) const;

    /// <summary>
    /// Sets the visibility of a color at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <param name="visibility">Specifies whether the color is visible or not.</param>
    void                    setVisibility(int c, bool visibility);

    /// <summary>
    /// Copies the color ramp definition from the given ramp.
    /// </summary>
    /// <param name="source">The color ramp to copy from.</param>
    void                    setFrom(const AcDbPointCloudColorRamp* source);

    /// <summary>
    /// Gets the name of this ramp.
    /// </summary>
    /// <returns> Returns the name of the ramp. </returns>
    const AcString          name() const;

    /// <summary>
    /// Set the name of this ramp.
    /// </summary>
    /// <param name="name">The color ramp name.</param>
    /// <returns>
    /// Returns Acad::eOk if successful or Acad::eInvalidInput otherwise.
    /// </returns>
    Acad::ErrorStatus       setName(const AcString& name);

private:
friend class PointCloudColorMapImp;
    Acad::ErrorStatus       dwgOutFields(AcDbDwgFiler* pFiler) const;
    Acad::ErrorStatus       dwgInFields(AcDbDwgFiler* pFiler);
    Acad::ErrorStatus       dxfOutFields(AcDbDxfFiler* pFiler) const;
    Acad::ErrorStatus       dxfInFields(AcDbDxfFiler* pFiler);
	
    class PointCloudColorRampImp* pImpl;
};

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// The AcDbPointCloudClassificationColorRamp class represents a classification color ramp
/// </summary>
class ACDB_PORT AcDbPointCloudClassificationColorRamp
{
public:

    //////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Default constructor for an AcDbPointCloudClassificationColorRamp.
    /// </summary>
    AcDbPointCloudClassificationColorRamp();

    //////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Destructor 
    /// </summary>
    ~AcDbPointCloudClassificationColorRamp();

    /// <summary>
    /// Gets the number of colors in this color ramp
    /// </summary>
    /// <returns> Returns number of colors in this color ramp. </returns>
    Adesk::Int32            numColors() const;

    /// <summary>
    /// Gets the color definition at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <returns> the color definition. </returns>
    AcCmEntityColor         color(int c) const;

    /// <summary>
    /// Sets the color definition at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <param name="color">The color definition.</param>
    void                    setColor(int c, AcCmEntityColor color);

    /// <summary>
    /// Gets the visibility of the color at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <returns> the color visibility. </returns>
    bool                    visibility(int c) const;

    /// <summary>
    /// Sets the visibility of the color at a given index.
    /// </summary>
    /// <param name="c">The index of the color.</param>
    /// <param name="visibility">Specifies whether the color is visible or not.</param>
    void                    setVisibility(int c, bool visibility);

    /// <summary>
    /// Copies the color ramp definition from a given ramp.
    /// </summary>
    /// <param name="source">The color ramp to copy from.</param>
    void                    setFrom(const AcDbPointCloudClassificationColorRamp* source);

    /// <summary>
    /// Get the name of this ramp
    /// </summary>
    /// <returns> Returns the name of the ramp. </returns>
    const AcString          name() const;

    /// <summary>
    /// Set the name of this ramp
    /// </summary>
    /// <param name="name">The color ramp name.</param>
    /// <returns>
    /// Returns Acad::eOk if successful or Acad::eInvalidInput otherwise.
    /// </returns>
    Acad::ErrorStatus       setName(const AcString& name);

private:
friend class PointCloudColorMapImp;
    Acad::ErrorStatus       dwgOutFields(AcDbDwgFiler* pFiler) const;
    Acad::ErrorStatus       dwgInFields(AcDbDwgFiler* pFiler);
    Acad::ErrorStatus       dxfOutFields(AcDbDxfFiler* pFiler) const;
    Acad::ErrorStatus       dxfInFields(AcDbDxfFiler* pFiler);
	
    class PointCloudClassificationColorRampImp* pImpl;
};

/// <summary>
/// The AcDbPointCloudColorMap class stores all color map ramp definitions.
/// There is only one AcDbPointCloudColorMap object per database.
/// The user can use getColorMap() to retrieve the AcDbPointCloudColorMap object.
/// There are two kinds of color ramps:
/// intensity or elevation color ramps (which are used when the point cloud is stylized by intensity or elevation), 
/// and classification color ramps (which are used when the point cloud is stylized by classification).
/// The color ramps are indexed by GUIDs inside the AcDbPointCloudColorMap object,
/// and point clouds reference these ramps by GUIDs.
/// </summary>
class ACDB_PORT AcDbPointCloudColorMap : public AcDbObject
{
friend class PointCloudColorMapImp;
friend class AcDbPointCloudMgr;

    static const Adesk::UInt16  kCurrentObjectVersion;

public:
    ACRX_DECLARE_MEMBERS(AcDbPointCloudColorMap);

    /// <summary>
    /// Gets the color map object for the given point cloud. Do not use the constructors directly.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if successful or Acad::eInvalidInput otherwise.
    /// </returns>
    /// <param name="id">Output for the AcDbObjectId of the color map object.</param>
    /// <param name="pDb">The database to be searched.</param>
    /// <param name="bCreateIfNone">Whether to create a new color map if none exists.</param>
    static Acad::ErrorStatus getColorMap(AcDbObjectId& id, AcDbDatabase* pDb, bool bCreateIfNone = true);

    //////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Destructor 
    /// </summary>
    virtual ~AcDbPointCloudColorMap();

    /// <summary>
    /// Registers a AcPointCloudColorSchemeCollectionReactor, which will be notified when the color map ramps are changed.
    /// </summary>
    /// <param name="pReactor">The AcPointCloudColorSchemeCollectionReactor to add.</param>
    void                            addColorSchemeCollectionReactor(AcPointCloudColorSchemeCollectionReactor* pReactor);

    /// <summary>
    /// Removes a AcPointCloudColorSchemeCollectionReactor.
    /// </summary>
    /// <param name="pReactor">The AcPointCloudColorSchemeCollectionReactor to remove.</param>
    void                            removeColorSchemeCollectionReactor(AcPointCloudColorSchemeCollectionReactor* pReactor);

    /// <summary>
    /// Forcefully notifies all of the  AcPointCloudColorSchemeCollectionReactor objects.
    /// </summary>
    void                            notifyColorSchemeCollectionChanged() const;

    // Intensity

    /// <summary>
    /// Gets the default intensity color scheme's GUID.
    /// </summary>
    /// <returns> Returns the default intensity color scheme's GUID. </returns>
    const AcString                  defaultIntensityColorScheme() const;

    /// <summary>
    /// Sets the default intensity color scheme's GUID
    /// </summary>
    /// <param name="GUID">The the default intensity color scheme's GUID .</param>
    /// <returns> Returns true upon success. </returns>
    bool                            setDefaultIntensityColorScheme(const AcString GUID);

    // Elevation

    /// <summary>
    /// Gets the default elevation color scheme's GUID
    /// </summary>
    /// <returns> Returns the default elevation color scheme's GUID. </returns>
    const AcString                  defaultElevationColorScheme() const;

    /// <summary>
    /// Sets the default elevation color scheme's GUID
    /// </summary>
    /// <param name="GUID">The default elevation color scheme's GUID .</param>
    /// <returns> Returns true upon success. </returns>
    bool                            setDefaultElevationColorScheme(const AcString GUID);

    // Classification

    /// <summary>
    /// Gets the default classification color scheme's GUID
    /// </summary>
    /// <returns> Returns default classification color scheme's GUID. </returns>
    const AcString                  defaultClassificationColorScheme() const;

    /// <summary>
    /// Sets the default classification color scheme's GUID
    /// </summary>
    /// <param name="GUID">The default classification color scheme's GUID.</param>
    /// <returns> Returns true upon success. </returns>
    bool                            setDefaultClassificationColorScheme(const AcString GUID);

    // Color Schemes

    /// <summary>
    /// Gets the complete list of GUIDs for each intensity and elevation color scheme in this map.
    /// </summary>
    /// <returns> Returns the list of intensity and elevation color scheme's GUIDs in this map. </returns>
    AcArray<AcString>               colorSchemeGUIDs() const;

    /// <summary>
    /// Given a GUID, gets the color ramp definition.
    /// </summary>
    /// <param name="GUID">The color scheme GUID.</param>
    /// <param name="target">The color ramp definition.</param>
    /// <returns> Returns true upon success. </returns>
    bool                            colorScheme(const wchar_t* GUID, AcDbPointCloudColorRamp& target) const;

    /// <summary>
    /// Tests whether a color scheme with the GUID exists or not.
    /// </summary>
    /// <param name="GUID">The color scheme GUID.</param>
    /// <returns> Returns true if the color scheme exists. </returns>
    bool                            hasColorScheme(const wchar_t* GUID) const;

    /// <summary>
    /// Sets the definition of an intensity or elevation color ramp for the given the GUID.
    /// </summary>
    /// <param name="GUID">The color scheme's GUID.</param>
    /// <param name="source">The color ramp definition.</param>
    /// <returns> Returns true upon success. </returns>
    bool                            setColorScheme(const wchar_t* GUID, const AcDbPointCloudColorRamp& source);

    /// <summary>
    /// Deletes the color scheme with the given GUID.
    /// </summary>
    /// <param name="GUID">The color scheme's GUID.</param>
    /// <returns> Returns true upon success. </returns>
    bool                            deleteColorScheme(const wchar_t* GUID);

    /// <summary>
    /// Gets the complete list of GUIDs for all classification color schemes in this map.
    /// </summary>
    /// <returns> Returns the list of classification color scheme GUIDs. </returns>
    AcArray<AcString>               classificationSchemeGUIDs() const;

    /// <summary>
    /// Given a GUID, gets the classification color ramp definition. 
    /// </summary>
    /// <param name="GUID">The color scheme's GUID.</param>
    /// <param name="target">The color ramp definition.</param>
    /// <returns> Returns true upon success. </returns>
    bool                            classificationScheme(const wchar_t* GUID, AcDbPointCloudClassificationColorRamp& target) const;

    /// <summary>
    /// Tests whether the classification color scheme with the GUID exists or not.
    /// </summary>
    /// <param name="GUID">The color scheme's GUID.</param>
    /// <returns> Returns true if the color scheme exists. </returns>
    bool                            hasClassificationScheme(const wchar_t* GUID) const;

    /// <summary>
    /// Sets the given color scheme with the given GUID.
    /// </summary>
    /// <param name="GUID">The color scheme's GUID.</param>
    /// <param name="source">The color ramp definition.</param>
    /// <returns> Returns true upon success. </returns>
    bool                            setClassificationScheme(const wchar_t* GUID, const AcDbPointCloudClassificationColorRamp& source);

    /// <summary>
    /// Deletes the classification color ramp for the given GUID.
    /// </summary>
    /// <param name="GUID">The color scheme's GUID.</param>
    /// <returns> Returns true upon success. </returns>
    bool                            deleteClassificationScheme(const wchar_t* GUID);

    /// <summary>
    /// Get a list of intensity or elevation color ramps that are being used by any point cloud.
    /// </summary>
    /// <param name="GUIDs">Output parameter for the color schemes' GUIDs that are in use.</param>
    void                            getColorSchemeInUse(AcArray<AcString>& GUIDs) const;

    /// <summary>
    /// Get a list of classification color ramps that are being used by any point cloud.
    /// </summary>
    /// <param name="GUIDs">Output parameter for the color schemes' GUIDs that are in use.</param>
    void                            getClassificationColorSchemeInUse(AcArray<AcString>& GUIDs) const;

    /// <summary>
    /// This function is called by dwgIn(). Its purpose is to allow this object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The filer to use to read in the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dwgInFields(AcDbDwgFiler* pFiler) override;

    /// <summary>
    /// This function is called by dwgOut(). Its purpose is to allow this object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The filer to use to write out the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dwgOutFields(AcDbDwgFiler* pFiler) const override;

    /// <summary>
    /// This function is called by dxfIn(). Its purpose is to allow this object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The filer to use to read in the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dxfInFields(AcDbDxfFiler* pFiler) override;

    /// <summary>
    /// This function is called by dxfOut(). Its purpose is to allow this object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The filer to use to write out the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dxfOutFields(AcDbDxfFiler* pFiler) const override;

    /// <summary>
    /// Called from within the close() method, before anything else is done.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk when closing can be done successfully. However, 
    /// if this method returns anything other than Acad::eOk,then the 
    /// close operation is immediately terminated.
    /// </returns>
    virtual Acad::ErrorStatus       subClose() override;

private:
    AcDbPointCloudColorMap();
    AcDbPointCloudColorMap(bool initializeDefaults);
    PointCloudColorMapImp *pImpl;
};
