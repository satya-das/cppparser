//////////////////////////////////////////////////////////////////////////////
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
#include "dbents.h"
#include "AcPointCloudItem.h"

class PointCloudExImp;
class AcDbPointCloudCrop;
class AcDbPointCloudExLimitBox;
class PointCloudPerfMonitor;

class IAcDbPointCloudAttributeFilter;
class IAcDbPointCloudDataBuffer;
class IAcDbPointCloudPointProcessor;
class IAcDbPointCloudSpatialFilter;
class IAcDbPointCloudAttributeFilter;

class AcPointCloudExtractedCylinder;

class AcDbPointCloudCropStateManager;
//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// The AcDbPointCloudEx entity (or "point cloud extension entity") works with the
/// AcDbPointCloudDefEx object (or "point cloud extension definition object") to
/// manage point cloud data inside AutoCAD. The relationship between
/// these two classes is much like the relationship between an AutoCAD block
/// definition object and a block reference entity.
/// 
/// The AcDbPointCloudEx entity is a drawable, selectable AutoCAD entity that 
/// places point cloud data in model or paper space at a particular location
/// and orientation, and with a particular scale. It also contains crop boundaries,
/// scan and region visibilities, stylization types, color mapping schemes, a limit box, 
/// and other typical AcDbEntity properties, like layer.
/// 
/// 
/// The AcDbPointCloudEx entity cannot be used by itself. It must be linked to
/// an AcDbPointCloudDefEx object by calling AcDbPointCloudEx::setPointCloudDefExId().
/// Furthermore, an AcDbPointCloudDefReactorEx must be constructed and linked to each
/// AcDbPointCloudEx entity and AcDbPointCloudDefEx object.
/// 
/// </summary>
class ACDB_PORT AcDbPointCloudEx : public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcDbPointCloudEx);
    /// <summary>
    /// Constructor.
    /// </summary>
    AcDbPointCloudEx();

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbPointCloudEx();

public:
    // AcDbObject Overrides
    //
    // erase
    /// <summary>
    /// Called from within erase() before anything else is done.
    /// </summary>
    /// <param name="erasing">
    /// A copy of the erasing argument that was passed into the erase()
    /// function call that triggered this subErase() call.
    /// </param>
    /// <returns>
    /// The default implementation is to return Acad::eOk. However, when
    /// overridden in custom classes, it provides a hook into the erase 
    /// operation. If it returns anything other than Acad::eOk, then the 
    /// erase operation is immediately terminated.
    /// </returns>
    virtual Acad::ErrorStatus       subErase(Adesk::Boolean erasing);

    // Filing
    /// <summary>
    /// This function is called by dwgIn(). Its purpose is to allow the object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The pointer to a filer to use to read in the object's data, which was passed in to dwgIn().
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dwgInFields(AcDbDwgFiler* pFiler) ADESK_OVERRIDE;

    /// <summary>
    /// This function is called by dwgOut(). Its purpose is to allow the object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The pointer to filer to use to write out the object's data, which was passed in to dwgOut(). 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dwgOutFields(AcDbDwgFiler* pFiler) const ADESK_OVERRIDE;

    /// <summary>
    /// This function is called by dxfIn(). Its purpose is to allow the object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The pointer to filer to use to read in the object's data, which was passed in to dwfIn(). 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dxfInFields(AcDbDxfFiler* pFiler) ADESK_OVERRIDE;

    /// <summary>
    /// This function is called by dxfOut(). Its purpose is to allow the object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// The pointer to filer to use to write out the object's data, which was passed into dwfOut(). 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       dxfOutFields(AcDbDxfFiler* pFiler) const ADESK_OVERRIDE;

    /// <summary>
    /// This function is called by swapIdWith() before anything else is done. 
    /// It provides a hook into the swapIdWith operation. 
    /// </summary>
    /// <param name="otherId">
    /// Object id of the object that is swapping IDs with another. 
    /// </param>
    /// <param name="swapXdata">
    /// Input boolean that indicates whether or not the extended entity data will be swapped. 
    /// </param>
    /// <param name="swapExtDict">
    /// Input boolean that indicates whether or not the extension dictionaries will be swapped.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       subSwapIdWith(AcDbObjectId otherId,
                                                Adesk::Boolean swapXdata = false,
                                                Adesk::Boolean swapExtDict = false) ADESK_OVERRIDE;

    /// <summary>
    /// Copy the contents of the "other" parameter into this messaged object, whenever feasible.
    /// </summary>
    /// <param name="pObj">
    /// Input pointer to object to copy from.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       copyFrom(const AcRxObject* pObj);

public:
    // AcDbEntity Overrides
    //
    /// <summary>
    /// Get the ECS matrix from this entity.
    /// </summary>
    /// <param name="retVal">
    /// The output ECS matrix.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual void                    getEcs(AcGeMatrix3d& retVal) const ADESK_OVERRIDE;

    /// <summary>
    /// The function is called when a drag operation involving this entity is starting,
    /// ending, or aborting.
    /// </summary>
    /// <param name="status">
    /// Provides information about what is happening with the drag operation.
    /// </param>
    virtual void                    dragStatus(const AcDb::DragStat status) ADESK_OVERRIDE;

protected:
    // AcDbEntity Overrides
    //
    /// <summary>
    /// Override the virtual function for AcDbEnity::list().
    /// </summary>
    virtual void                    subList() const ADESK_OVERRIDE;

    /// <summary>
    /// Get the unique class id for this entity.
    /// </summary>
    /// <param name="pClsid">
    /// The output class id.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       subGetClassID(CLSID* pClsid) const ADESK_OVERRIDE;

    /// <summary>
    /// Override the virtual function for AcDbEnity::getGeomExtents().
    /// </summary>
    /// <param name="extents">
    /// The output extents.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       subGetGeomExtents(AcDbExtents& extents) const ADESK_OVERRIDE;

    // AcDbOsnapOverrule
    //
    /// <summary>
    /// Override the virtual function for AcDbEnity::isContentSnappable().
    /// </summary>
    /// <returns>
    /// Returns true if this entity can be snapped to, otherwise false.
    /// </returns>
    virtual bool                    subIsContentSnappable() const ADESK_OVERRIDE;

    // AcGiDrawable interface
    //
    /// <summary>
    /// Override the virtual function for the drawing of point cloud.
    /// </summary>
    /// <param name="mode">
    /// For generating graphics in model coordinates.
    /// </param>
    /// <returns>
    /// Returns true if successful.
    /// </returns>
    virtual Adesk::Boolean          subWorldDraw(AcGiWorldDraw* mode) ADESK_OVERRIDE;

    /// <summary>
    /// Override the virtual function for AcDbEntity::transformBy().
    /// </summary>
    /// <param name="xform">
    /// The input transform matrix.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus       subTransformBy(const AcGeMatrix3d& xform) ADESK_OVERRIDE;

public:
    // AcDbPointCloudDefEx specific protocol
    //

    /// <summary>
    /// Sets the ID of the AcDbPointCloudDefEx object containing the point cloud data file.
    /// Internal Use.
    /// </summary>
    /// <param name="defExId">
    /// The object id of AcDbPointCloudDefEx which will be set.
    /// </param>
    void                            setPointCloudDefExId(const AcDbObjectId& defExId);

    /// <summary>
    /// Returns the ID of a point cloud extension definition object.
    /// </summary>
    AcDbObjectId                    pointCloudDefExId() const;

    /// <summary>
    /// Sets the ID of a persistent reactor.
    /// Each AcDbPointCloudEx entity must have a persistent reactor attached to
    /// the AcDbPointCloudDefEx object it is using. When a new AcDbPointCloudEx
    /// entity is created, an AcDbPointCloudDefReactorEx must also be
    /// created and added to the database, and also added to the AcDbPointCloudDefEx
    /// object's list of persistent reactors. Then the entity must be informed
    /// of the reactor to use, which is the purpose of this function. The 
    /// AcDbPointCloudEx entity then becomes the owner of the reactor object.
    /// </summary>
    /// <param name="reactorId">
    /// The object id of AcDbPointCloudDefReactorEx which will be set.
    /// </param>
    void                            setReactorId(const AcDbObjectId& reactorId);

    /// <summary>
    /// Returns the ID of a point cloud extension entity's reactor.
    /// </summary>
    AcDbObjectId                    reactorId() const;

    // PointCloud routines
    //

    /// <summary>
    /// Returns whether the attached point cloud is locked or not.
    /// </summary>
    bool                            locked()const;

    /// <summary>
    /// Sets whether an attached point cloud can be moved, scaled,
    /// rotated, or cropped.
    /// </summary>
    /// <param name="locked">
    /// True if the entity is locked, else false.
    /// </param>
    void                            setLocked(bool locked);

    /// <summary>
    /// Returns the scale factor of the point cloud.
    /// </summary>
    double                          scale() const;

    /// <summary>
    /// Sets the scale factor of the point cloud.
    /// The user may give a customized scale, while the point cloud may have a unit factor based on current drawing.
    /// The input scale factor is the product of the customized scale and the unit factor.
    /// </summary>
    /// <param name="val">
    /// The scale factor to be set.
    /// </param>
    /// <returns> 
    /// Returns Acad::eOk if set successfully. If point cloud is locked, this function will return Acad::eNotApplicable.
    /// </returns>
    Acad::ErrorStatus               setScale(double val);

    /// <summary>
    /// Returns the rotation angle of the point cloud
    /// in the current UCS.
    /// </summary>
    double                          rotation() const;

    /// <summary>
    /// Specifies the rotation angle of the point cloud
    /// in the current UCS.
    /// </summary>
    /// <param name="val">
    /// The rotation angle to be set.
    /// </param>
    /// <returns> 
    /// Returns Acad::eOk if set successfully. If point cloud is locked, this function will return Acad::eNotApplicable.
    /// </returns>
    Acad::ErrorStatus               setRotation(double val);

    /// <summary>
    /// Returns the location in the drawing where the base point of the point
    /// cloud is attached.
    /// </summary>
    AcGePoint3d                     location() const;

    /// <summary>
    /// Specifies the location in the drawing where the base point of the point
    /// cloud is attached.
    /// </summary>
    /// <param name="pt">
    /// The location point to be set.
    /// </param>
	/// <returns> 
    /// Returns Acad::eOk if successful. If point cloud is locked, this function will return Acad::eNotApplicable.
    /// </returns>
    Acad::ErrorStatus               setLocation(const AcGePoint3d& pt);

    /// <summary>
    /// Returns the non-translated native 3D extent of the point cloud in ECS, 
    /// which is taken from point cloud data file directly.
    /// </summary>
    /// <param name="extents">
    /// The non-translated native 3D extent of the point cloud in ECS.
    /// </param>
    void                            getNativeCloudExtent(AcDbExtents& extents) const;

    /// <summary>
    /// Gets the expected visible point count after frustum culling, that is
    /// the raw point number that is being loaded in the background.
    /// It is larger than or equal to the real point count that is currently loaded in
    /// memory and displayed on screen.
    /// Internal Use.
    /// </summary>
    /// <remarks>
    /// NOTES: The count is updated after each frame is drawn.
    /// </remarks>
    unsigned int                    getVisiblePointCount() const;

    /// <summary>
    /// Gets the visible point count loaded in memory for a given view,
    /// that is the visible points being loaded in memory based on 
    /// last frustum culling result. 
    /// This count is larger than or equal to the point count displayed on screen, 
    /// and less than the raw visible point count after frustum culling.
    /// Internal Use.
    /// </summary>
    /// <remarks>
    /// NOTES: The count is updated after each frame drawing.
    /// </remarks>
    unsigned int                    getLoadedVisiblePointCount() const;

    /// <summary>
    /// Gets the visible point count displayed on screen, it's the actual points
    /// being considered for rendering, which based on the visible point count loaded in 
    /// memory, but is reduced by the points being filtered by cropping. 
    /// This count does not include points that are hidden by the limit-box or deleted regions.
    /// Internal Use.
    /// </summary>
    /// <remarks>
    /// NOTES: The count is updated after each drawn frame.
    /// </remarks>
    unsigned int                    getDisplayedVisiblePointCount() const;

    /// <summary>
    /// This function gets a pointer to the performance monitor for the current 
    /// point cloud entity.
    /// Internal Use.
    /// </summary>
    PointCloudPerfMonitor*          getPointCloudPerfMonitor();

    /// <summary>
    /// This function sets the active path name of the externally referenced
    /// point cloud file. Once the path name is validated, this function
    /// initializes the point cloud's data members, like extent, scan and region
    /// visibilities, limit box, etc.
    /// Internal Use.
    /// </summary>
    /// <param name="strActiveFileName">
    /// The active path name of the externally referenced point cloud file.
    /// </param>
    /// <returns> 
    /// Returns true if set successfully, otherwise returns false. If point cloud name is NULL, it will return false.
    /// </returns>
    bool                            setActiveFileName(const wchar_t* strActiveFileName);

    /// <summary>
    /// Returns the path name of the actual file being currently used to define
    /// the point cloud.
    /// </summary>
    /// <param name="strActiveFileName">
    /// The active path name of the externally referenced point cloud file.
    /// </param>
    bool                            getActiveFileName(AcString& strActiveFileName) const;

    /// <summary>
    /// Returns the name of this point cloud extension entity.
    /// </summary>
    AcString                        getPointCloudName() const;

    /// <summary>
    /// Specifies a unique name for this point cloud extension entity in the current
    /// drawing.
    /// </summary>
    /// <param name="name">
    /// The point cloud name to be set.
    /// </param>
    /// <returns> 
    /// Returns Acad::eOk if set successfully, otherwise returns Acad::eNotApplicable. 
    /// If point cloud name is NULL, it will return Acad::eNull.
    /// </returns>
    Acad::ErrorStatus               setPointCloudName(const AcString& name);


    // cropping boundary methods
    // 

    /// <summary>
    /// Returns the number of cropping boundaries that are set on this entity.
    /// </summary>
    int                             getCroppingCount() const;

    /// <summary>
    /// Returns a cropping boundary by index, for editing.
    /// Requires that the AcDbPointCloudEx be open for writing.
    /// </summary>
    /// <param name="index">
    /// The cropping boundary's index.
    /// </param>
    /// <returns> Returns the cropping boudary at the given index. Returns NULL if index is out of range of (0 ~ cropping count). </returns>
    AcDbPointCloudCrop*             getPointCloudCropping(int index);

    /// <summary>
    /// Returns a cropping boundary index for read only.
    /// Requires that the AcDbPointCloudEx be open for reading.
    /// </summary>
    /// <param name="index">
    /// The cropping boundary' index.
    /// </param>
    /// <returns> Returns the cropping boudary at the given index. Returns NULL if index is out of range of (0 ~ cropping count). </returns>
    const AcDbPointCloudCrop*       getPointCloudCroppingConst(int index) const;

    /// <summary>
    /// Adds a new cropping boundary to this point cloud entity.
    /// </summary>
    /// <param name="cropping">
    /// An AcDbPointCloudCrop object which is to be added.
    /// </param>
    void                            addCroppingBoundary(const AcDbPointCloudCrop& cropping);

    /// <summary>
    /// Removes all cropping boundaries on this point cloud entity.
    /// </summary>
    /// <returns> Returns Acad::eOk if successful or Acad::eNotApplicable otherwise. </returns>
    Acad::ErrorStatus               clearCropping();

    /// <summary>
    /// Removes most recently added cropping boundary from this point cloud entity.
    /// </summary>
    /// <returns> Returns Acad::eOk if successful or Acad::eNotApplicable otherwise. </returns>
    Acad::ErrorStatus               removeLastCropping();

    /// <summary>
    /// Gets whether cropping on this entity is currently inverted.
    /// </summary>
    /// <returns> Returns true if cropping is inverted, or false if cropping is not inverted. </returns>
    bool                            getCroppingInvert() const;

    /// <summary>
    /// Sets whether or not cropping is currently inverted on this entity.
    /// </summary>
    /// <param name="invert">
    /// true: invert current cropping, false: don't invert.
    /// </param>
    /// <returns> Returns Acad::eOk if successful or Acad::eNotApplicable otherwise. </returns>
    Acad::ErrorStatus               setCroppingInvert(bool invert);

    /// <summary>
    /// Sets whether or not the point cloud is currently creating cropping boundary.
    /// Generally, AutoCAD draws a boundary box for the point cloud during dragging as preview.
    /// But when the point cloud is creating cropping boundary, it is also in dragging mode. 
    /// Then AutoCAD doesn't need to draw the boundary box.
    /// The default value is false.
    /// Internal Use.
    /// </summary>
    /// <param name="bCreating">
    /// Returns true if this entity is creating a crop region (e.g., we should not create a cropping boundary).
    /// Else, returns false.
    /// </param>
    void                            setInCreatingCroppingMode(bool  bCreating);

    /// <summary>
    /// Gets whether or not this entity should show the cropped point cloud.
    /// </summary>
    /// <remarks>
    /// If true, the point cloud's cropping region should be used to filter out displayed points. 
    /// If false, all points should be displayed, regardless of any cropping regions.
    /// </remarks>
    bool                            showCropped() const;

    /// <summary>
    /// Sets whether or not this entity should show the cropped point cloud.
    /// </summary>
    /// <param name="bShowCropped">
    /// If true, the point cloud's cropping region will be used to filter out displayed points. 
    /// If false, all points will be displayed, regardless of any cropping regions.
    /// </param>
    /// <returns> Returns Acad::eOk only. </returns>
    Acad::ErrorStatus               setShowCropped(bool bShowCropped);


    // Stylization
    //

    /// <summary>
    /// This enumeration defines stylization mode that is used when displaying this point cloud entity.
    /// </summary>
    enum StylizationType
    {
        /// <summary>
        /// Colors each point based on the colors defined in the scan data.
        /// </summary>
        kTrueColor      = 1,

        /// <summary>
        /// Assigns all points the color that is defined for the object (AutoCAD's
        /// object color property).
        /// </summary>
        kSingleColor,

        /// <summary>
        /// Colors each point based on the surface normal of that point. AutoCAD
        /// uses a default hard-coded color scheme for the normals by default.
        /// If the point cloud doesn't have normals, returns Acad::eNotApplicable.
        /// </summary>
        kNormalRamp,

        /// <summary>
        /// Colors each point based on the Z (height) value of that point. AutoCAD
        /// uses a default Full color spectrum color scheme by default whose
        /// range is mapped to the lowest and highest intensity values of the
        /// point cloud object(s).
        /// </summary>
        kHeightRamp,

        /// <summary>
        /// Colors each point based on the Intensity value of the point, as defined
        /// in the scan data).
        /// AutoCAD uses a default full-color spectrum color scheme by default
        /// whose range is mapped to the lowest and highest intensity values 
        /// of the point cloud object(s).
        /// </summary>
        kIntensityRamp,

        /// <summary>
        /// Colors each points based on the classification that is assigned to it in the scan data.
        /// AutoCAD uses a default color scheme for LAS classification values.
        /// </summary>
        kClassificationRamp
    };

    /// <summary>
    /// Sets the stylization mode to be used when displaying this point cloud entity.
    /// See the documentation for StylizationType for the different types of stylization.
    /// 
    /// </summary>
    /// <param name="type">
    /// The stylization type to be set.
    /// </param>
    /// <returns> Returns Acad::eOk if successful or Acad::eNotApplicable otherwise. </returns>
    Acad::ErrorStatus               setStylizationType(StylizationType type);

    /// <summary>
    /// Returns the stylization mode that is used when displaying this point cloud entity.
    /// </summary>
    StylizationType                 stylizationType() const;


    // color scheme
    //

    /// <summary>
    /// Returns the current color scheme name that corresponds to the current stylization mode.
    /// This property only applies when the point cloud is being displayed using a stylization mode
    /// that has a color ramp.
    /// This method returns an empty string if the stylization mode is not kIntensityRamp, 
    /// kHeightRamp, or kClassificationRamp.
    /// </summary>
    /// <returns>
    /// Returns the GUID of current color scheme, or an empty string if no color 
    /// scheme applies to the current stylization mode.
    /// </returns>
    AcString                        getCurrentColorScheme() const;

    /// <summary>
    /// Sets the current color scheme based on stylization mode in use.
    /// This property only applies when the point cloud is being displayed using a stylization mode
    /// that has a color ramp.
    /// </summary>
    /// <param name="guid">
    /// Indicates the GUID of a color scheme to be set.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; Acad::eInvalidInput if name is empty;
    /// Acad::eNotApplicable if the stylization mode is not kIntensityRamp, 
    /// kHeightRamp, or kClassificationRamp.
    /// </returns>
    Acad::ErrorStatus               setCurrentColorScheme(const AcString& guid);

    /// <summary>
    /// Returns the color scheme name based on the given stylization mode.
    /// This property only applies when the point cloud is being displayed using a stylization mode
    /// that has a color ramp.
    /// Returns an empty string if the stylization mode is not kIntensityRamp, 
    /// kHeightRamp, or kClassificationRamp.
    /// </summary>
    /// <param name="type">
    /// Indicates a stylization type.
    /// </param>
    /// <returns>
    /// Returns the GUID of corresponding color scheme.
    /// </returns>
    AcString                        getColorSchemeForStylization(StylizationType type) const;

    /// <summary>
    /// Sets the current color scheme based on the given stylization mode. 
    /// This property only applies when the point cloud is being displayed using a stylization mode
    /// that has a color ramp.
    /// If the color scheme guid doesn't exist, the color scheme will not take effect.
    /// </summary>
    /// <param name="guid">
    /// Indicates the GUID of a color scheme to be set.
    /// </param>
    /// <param name="type">
    /// Indicates a stylization type.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; Acad::eInvalidInput if name is empty;
    /// Acad::eNotApplicable if the stylization mode is not kIntensityRamp, 
    /// kHeightRamp, or kClassificationRamp.
    /// </returns>
    Acad::ErrorStatus               setColorSchemeForStylization(const AcString& guid, StylizationType type);

    /// <summary>
    /// This enumeration defines the display options for the points which are
    /// out of intensity/elevation range.
    /// </summary>
    enum DispOptionOutOfRange
    {
        /// <summary>
        /// Uses a maximum color in the color ramp for the points which are
        /// higher than the intensity/elevation range, and
        /// a minimum color in the color ramp for the points which are
        /// lower than the intensity/elevation range.
        /// </summary>
        kUseMinMaxColors = 0,

        /// <summary>
        /// Uses the RGB scan color for the points which are out of 
        /// intensity/elevation range.
        /// </summary>
        kUseRGBScanColors,

        /// <summary>
        /// Hide points that are outside of intensity/elevation range.
        /// </summary>
        kHidePoints
    };


    // Colormap - Intensity
    // 

    /// <summary>
    /// Color schemes can be treated as distinct bands or as gradients. This function indicates 
    /// whether or not the intensity color scheme is being displayed as a gradient.
    /// </summary>
    bool                            showIntensityAsGradient() const;

    /// <summary>
    /// Color schemes can be treated as distinct bands or as gradients. This function allows the user to set
    /// whether or not the intensity color scheme is being displayed as a gradient.
    /// The default value is true.
    /// </summary>
    /// <param name="b">
    /// true: colors in the referenced intensity color scheme are applied as a gradient.
    /// false: otherwise.
    /// </param>
    void                            setShowIntensityAsGradient(bool b);

    /// <summary>
    /// Returns the minimum value of the current intensity colorization range.
    /// </summary>
    Adesk::Int32                    minIntensity() const;

    /// <summary>
    /// Returns the maximum value of the current intensity colorization range.
    /// 
    /// </summary>
    Adesk::Int32                    maxIntensity() const;

    /// <summary>
    /// Sets the range (min/max values) of the current intensity colorization range.
    /// </summary>
    /// <param name="min">
    /// The minimal value of intensity.
    /// </param>
    /// <param name="max">
    /// The maximal value of intensity.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful or Acad::eInvalidInput if minimal value is larger than or equal to maximal value.
    /// </returns>
    Acad::ErrorStatus               setMinMaxIntensity(int min, int max);

    /// <summary>
    /// Returns the current display option for the points which are out of
    /// intensity range.
    /// </summary>
    /// <returns>
    /// Returns the current display option for the points whose intensity are out of range.
    /// </returns>
    DispOptionOutOfRange            intensityOutOfRangeBehavior() const;

    /// <summary>
    /// Sets the display option for the points whose intensity are out of range.
    /// The default value is kUseRGBScanColors.
    /// </summary>
    /// <param name="dispOp">
    /// The display option to be set.
    /// </param>
    void                            setIntensityOutOfRangeBehavior(DispOptionOutOfRange dispOp);

    // Colormap - Elevation
    // 

    /// <summary>
    /// Color schemes can be treated as distinct bands or as gradients. This function indicates
    /// whether or not the elevation color scheme is being displayed as a gradient.
    /// </summary>
    bool                            showElevationAsGradient() const;

    /// <summary>
    /// Color schemes can be treated as distinct bands or as gradients. This function allows the user to set
    /// whether or not the elevation color scheme is being displayed as a gradient.
    /// The default value is true.
    /// </summary>
    /// <param name="b">
    /// true: colors in the referenced elevation color scheme are applied as a gradient.
    /// false: otherwise.
    /// </param>
    void                            setShowElevationAsGradient(bool b);

    /// <summary>
    /// Returns the minimum value of the elevation colorization range.
    /// </summary>
    double                          minElevation() const;

    /// <summary>
    /// Returns the maximum value of the elevation colorization range.
    /// </summary>
    double                          maxElevation() const;

    /// <summary>
    /// Sets the range (min/max values) of the elevation colorization range.
    /// </summary>
    /// <param name="min">
    /// The minimal value of elevation.
    /// </param>
    /// <param name="max">
    /// The maximal value of elevation.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful or Acad::eInvalidInput if minimal value is larger than or equal to maximal value.
    /// </returns>
    Acad::ErrorStatus               setMinMaxElevation(double min, double max);

    /// <summary>
    /// Returns whether or not the elevation range update dynamically as the
    /// extents of the limit box change.
    /// </summary>
    /// <returns>
    /// true: the color range is fixed by user's input for each elevation.
    /// false: the color range is dynamically changed based on the extents of limit box.
    /// </returns>
    bool                            elevationApplyToFixedRange() const;

    /// <summary>
    /// Sets whether or not the elevation range updates dynamically as the 
    /// extents of the limit box change.
    /// The default value is true.
    /// </summary>
    /// <param name="val">
    /// true: the color range is fixed by user's input for each elevation.
    /// false: the color range is dynamically changed based on the extents of limit box.
    /// </param>
    void                            setElevationApplyToFixedRange(bool val);

    /// <summary>
    /// Returns the current display option for any points which are out of
    /// elevation range.
    /// </summary>
    DispOptionOutOfRange            elevationOutOfRangeBehavior() const;

    /// <summary>
    /// Sets the display option for any points which are out of elevation range.
    /// The default value is kUseRGBScanColors.
    /// </summary>
    /// <param name="dispOp">
    /// The display option to be set.
    /// </param>
    void                            setElevationOutOfRangeBehavior(DispOptionOutOfRange dispOp);


    // limit box
    //

    /// <summary>
    /// Returns the limit box of this point cloud entity.
    /// Internal Use.
    /// </summary>
    /// <param name="limitBox">
    /// The AcDbPointCloudExLimitBox object to be got.
    /// </param>
    void                            getLimitBox(AcDbPointCloudExLimitBox& limitBox) const;

    /// <summary>
    /// Sets the limit box of this point cloud entity.
    /// Internal Use.
    /// </summary>
    /// <param name="limitBox">
    /// The limit box to be set.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk only.
    /// </returns>
    Acad::ErrorStatus               setLimitBox(const AcDbPointCloudExLimitBox& limitBox);

    /// <summary>
    /// Resets the limit box to default extents.
    /// Internal Use.
    /// </summary>
    void                            resetLimitBox();

    /// <summary>
    /// Sets whether or not the points on the limit box boundary will be
    /// highlighted.
    /// Internal Use.
    /// </summary>
    /// <param name="val">
    /// true: the points on the limit box boundary will be highlighted.
    /// false: the points on the limit box boundary will not be highlighted.
    /// </param>
    void                            setHighlightLimitboxBoundary(bool val);


    // Point cloud data (AcPointCloudItem)
    //

    /// <summary>
    /// Get the list of AcPointCloudItems, which includes the scan items and region items.
    /// </summary>
    const AcPointCloudItemArray*    getPointCloudDataList() const;

    /// <summary>
    /// Gets a scan item by the scan GUID in the point cloud.
    /// </summary>
    /// <param name="scanGuid">
    /// The given scan GUID so a corresponding scan item will return.
    /// </param>
    AcPointCloudItem*               findScanItem(const AcString& scanGuid);

    /// <summary>
    /// Gets the region item by its ID in the point cloud.
    /// The region ID is stored in the RCP file.
    /// </summary>
    /// <param name="regionId">
    /// The region ID to be returned.
    /// </param>
    AcPointCloudItem*               findRegionItem(int regionId);

    /// <summary>
    /// Sets whether or not a scan is visible.
    /// This method does nothing if the scan guid doesn't exist.
    /// </summary>
    /// <param name="scanGuid">
    /// The scan GUID.
    /// </param>
    /// <param name="bVisible">
    /// Whether or not the scan is visible.
    /// </param>
    void                            setScanVisibility(const AcString& scanGuid, bool bVisible);

    /// <summary>
    /// Sets whether or not all scans are visible.
    /// </summary>
    /// <param name="bVisible">
    /// The visibility of all scans.
    /// </param>
    void                            setAllScansVisibility(bool bVisible);

    /// <summary>
    /// Sets whether or not a specified region is visible. 
    /// This function can be used to set visibility of any region, or to points that
    /// are not assigned to any region.
    /// If the given region ID is outside of the range of valid region IDs, there is no change.
    /// </summary>
    /// <param name="regionId">
    /// The region ID.
    /// </param>
    /// <param name="bVisible">
    /// The region's visibility.
    /// </param>
    void                            setRegionVisibility(int regionId, bool bVisible);

    /// <summary>
    /// Sets whether or not all regions are visible.
    /// </summary>
    /// <param name="bVisible"> 
    /// The visibility for all regions.
    /// </param>
    /// <param name="includeUnassigned"> true or false, whether or not set the bVisible to unassigned points </param>
    void                            setAllRegionsVisibility(bool bVisible, bool includeUnassigned = false);

    /// <summary>
    /// Sets whether or not all scans which are related to
    /// a region are visible.
    /// </summary>
    /// <param name="regionId">
    /// The region ID.
    /// </param>
    /// <param name="bVisible">
    /// The visibility of all related scans.
    /// </param>
    void                            setAllScansVisibilityByRegion(int regionId, bool bVisible);

    /// <summary>
    /// Gets the origin location and extents of a scan item specified the scan guid.
    /// </summary>
    /// <param name="scanGuid">
    /// The scan GUID.
    /// </param>
    /// <param name="origin">
    /// The scan origin as return value.
    /// </param>
    /// <param name="extent">
    /// The scan extent as return value.
    /// </param>
    /// <returns> Returns true if successful or false if the scan item can't be found. </returns>
    bool                            getScanViewInfo(const AcString& scanGuid, AcGePoint3d& origin, AcDbExtents& extent) const;

    /// <summary>
    /// Resets the visibility of all scans and regions.
    /// Internal Use.
    /// </summary>
    void                            resetScanRegionVisibility();

    /// <summary>
    /// Sets whether all scans in this point cloud entity are highlighted.
    /// </summary>
    /// <param name="bHighlight">
    /// true : highlights scans ;
    /// false : unhighlights scans ;
    /// </param>
    void                            setAllScanHighlight(bool bHighlight);

    /// <summary>
    /// Sets whether all regions in the point cloud entity are highlighted. There is a separate
    /// value in this method for points that are not assigned to any region.
    /// </summary>
    /// <param name="bHighlight">
    /// true    : highlights regions
    /// false   : unhighlights regions
    /// </param>
    /// <param name="bIncludeUnassignedPoints">
    /// true : operation will affect unassigned points ;
    /// false : operation will *NOT* affect unassigned points ;
    /// </param>    
    void                            setAllRegionHighlight(bool bHighlight, bool bIncludeUnassignedPoints = false);

    /// <summary>
    /// Sets the geographical coordinate system to point cloud
    /// </summary>
    /// <param name="useDrawingGeo">
    /// true: apply the geographical coordinate system of current drawing, and ignore the given 'geoCS' parameter;
    /// false: apply the given 'geoCS' to this point cloud;
    /// </param>    
    /// <param name="geoCS">
    /// the name of geographical coordinate system.
    /// if it is empty, it will clear the coordinate system of this point cloud.
    /// </param>
    /// <remarks> internal use </remarks>
    void                            applyGeoLocation(bool useDrawingGeo = false, const AcString& geoCS = _T(/*MSG0*/""));

    /// <summary>
    /// Updates the geographical coordinate system of this point cloud.
    /// </summary>
    /// <remarks>internal usage</remarks>
    void                            updateGeoLocation();

    /// <summary>
    /// Clears the geographical coordinate system of this point cloud.
    /// </summary>
    void                            clearGeoLocation();

    /// <summary>
    /// Specify whether the point cloud is geographically located.
    /// </summary>
    bool                            geolocate() const;


    /// <summary>
    /// This enumeration describes the the snapping operations that can be done with point clouds
    /// </summary>
    enum PointCloudOSnapMode
    {
        /// <summary>
        /// Node - Snaps to closest point in the point cloud
        /// </summary>
        kOsModePNod     = 0,
        /// <summary>
        /// Nearest - Snaps to nearest point on a planar segment
        /// </summary>
        kOsModePNea     = 1,
        /// <summary>
        /// Perpendicular - Snaps perpendicular to the nearest planar segment
        /// </summary>
        kOsModePPer     = 2,
        /// <summary>
        /// Edge Nearest - Snaps to nearest point on an edge (intersection of 2 planes)
        /// </summary>
        kOsModePEdgeNea = 3,
        /// <summary>
        /// Edge Perpendicular - Snaps perpendicular to an edge (intersection of 2 planes)
        /// </summary>
        kOsModePEdgePer = 4,
        /// <summary>
        /// Intersection - Snaps to intersection point of section line vectors
        /// </summary>
        kOsModePInt     = 5,
        /// <summary>
        /// Centerline - Snaps to nearest point on centerline of cylinder
        /// </summary>
        kOsModePCL      = 6,
        /// <summary>
        /// Node - Snaps to corner (intersection of 3 planes) in the point cloud
        /// </summary>
        kOsModePCorner  = 7
    };

    /// <summary>
    /// This function uses the provided snapMode, pickPoint, and lastPoint
    /// to determine all appropriate osnap points for the point cloud.
    /// Internal Use.
    /// </summary>
    /// <param name="snapMode">
    /// Input osnap mode to be used
    /// </param>
    /// <param name="pickPoint">
    /// Input point (in WCS coordinates) picked during the object snap operation
    /// </param>
    /// <param name="lastPoint">
    /// Input point (in WCS coordinates) selected just before pickPoint 
    /// </param>
    /// <param name="viewXform">
    /// Input transformation matrix to transform from WCS to DCS 
    /// </param>
    /// <param name="snapPoints">
    /// Input pre-existing array to append osnap points to (may already contain points);
    /// output with object snap points appended
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidView if the current view cannot be retrieved.
    /// Returns Acad::ePointNotOnEntity if there is no point available.
    /// Returns Acad::eInvalidInput if the inputs are illegal.
    /// Returns Acad::eNotApplicable if the current snap mode does not apply to this entity.
    /// </returns>
    Acad::ErrorStatus               getCustomOsnapInfo(PointCloudOSnapMode snapMode,
                                                    const AcGePoint3d& pickPoint,
                                                    const AcGePoint3d& lastPoint,
                                                    const AcGeMatrix3d& viewXform, 
                                                    AcArray<AcGePoint3d>& snapPoints);

    /// <summary>
    /// Fills a given buffer with point data by specifying how many point you want and the spatial and attribute filters.
    /// </summary>
    /// <param name="pointData">
    /// Output parameter for a pointer to a IAcDbPointCloudDataBuffer upon successful return. 
    /// The caller should release the buffer by calling freeObject()
    /// after consuming the buffer
    /// </param>
    /// <param name="pointCount">
    /// How many points you want (approximate amount, the actual point number returned will not be the exact amount)
    /// </param>
    /// <param name="pSpatialFilter">
    /// The spatial filter you want to exclude points (NULL if no filtering is needed)
    /// </param>
    /// <param name="pAttributeFilter">
    /// The attribute filter you want to exclude points (NULL if no filtering is needed)
    /// </param>
    /// <param name="dataTypes">
    /// A combination of IAcDbPointCloudDataBuffer::DataType to specify the data you want to consume.
    /// </param>
    /// <param name="maxPointLimitation">
    /// The maximum amount of points the function will return (cannot execeed 0x1000000)
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input pointCount or maxPointLimitation is invalid.
    /// Returns Acad::ePCFileNotOpened if the scan file is not found or not open.
    /// Returns Acad::eBadVisibilityValue if there is no scan visble.
    /// Returns Acad::eOutOfMemory if the calculation consumes too much.
    /// Returns Acad::ePCUnknown otherwise.
    /// </returns>
    Acad::ErrorStatus getPointDataByPointCount(IAcDbPointCloudDataBuffer*& pointData, Adesk::UInt32 pointCount,
         IAcDbPointCloudSpatialFilter* pSpatialFilter, IAcDbPointCloudAttributeFilter* pAttributeFilter, Adesk::UInt32 dataTypes, Adesk::UInt32 maxPointLimitation) const;
    
    /// <summary>
    /// Processes all data in the point cloud using the spatial filter.
    /// </summary>
    /// <param name="processor">
    /// The IAcDbPointCloudPointProcessor that will be called during the point traversal 
    /// </param>
    /// <param name="pSpatialFilter">
    /// The spatial filter you want to exclude points (NULL if no filtering is needed)
    /// </param>
    /// <param name="dataTypes">
    /// A combination of IAcDbPointCloudDataBuffer::DataType to specify the data you want to consume
    /// </param>
    /// <param name="LODLevel">
    /// The level of detail level, value should be between 1-100. Note: the actual supported LOD depends on the scan files.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input processor or LODLevel is invalid.
    /// Returns Acad::ePCFileNotOpened if the scan file is not found or not open.
    /// Returns Acad::eBadVisibilityValue if there is no scan visble.
    /// Returns Acad::ePCUnknown otherwise.
    /// </returns>
    Acad::ErrorStatus traverseAllPointData(IAcDbPointCloudPointProcessor* processor,IAcDbPointCloudSpatialFilter* pSpatialFilter, Adesk::UInt32 dataTypes, int LODLevel) const;

    /// <summary>
    /// Adds a custom spatial filter to the point. Points that are excluded by this filter will not be rendered.
    /// </summary>
    /// <param name="pFilter">
    /// The spatial filter that you want add.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input pFilter is invalid.
    /// </returns>
    Acad::ErrorStatus  addSpatialFilter(IAcDbPointCloudSpatialFilter* pFilter);

    /// <summary>
    /// Removes a custom spatial filter that was previously added with addSpatialFilter().
    /// </summary>
    /// <param name="pFilter">
    /// The spatial filter to be removed.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input pFilter is invalid.
    /// </returns>
    Acad::ErrorStatus  removeSpatialFilter(IAcDbPointCloudSpatialFilter* pFilter);

    /// <summary>
    /// Remove all custom spatial filters previously added with addSpatialFilter().
    /// </summary>
    void  clearSpatialFilters();

    /// <summary>
    /// Adds a custom attribute filter. Points that are excluded by this filter will not be rendered.
    /// </summary>
    /// <param name="pFilter">
    /// The attribute filter that you want to add.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input pFilter is invalid.
    /// </returns>
    Acad::ErrorStatus  addAttributeFilter(IAcDbPointCloudAttributeFilter* pFilter);
	
    /// <summary>
    /// Removes a custom attribute filter previously added with addAttributeFilter().
    /// </summary>
    /// <param name="pFilter">
    /// The attribute filter that you have added previously with addAttributeFilter().
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input pFilter is invalid.
    /// </returns>
    Acad::ErrorStatus  removeAttributeFilter(IAcDbPointCloudAttributeFilter* pFilter);

    /// <summary>
    /// Removes all custom attribute filters that were previously added with addAttributeFilter().
    /// </summary>
    void  clearAttributeFilters();

    /// <summary>
    /// Finds any plane or point at the specified view coordinate(). 
    /// This method will return true if it finds a point or a plane.
    /// If the output is a plane, this method will append three points to the given
    /// points array. If the output is a single point, then just that one point
    /// will be appended to the given points array.
    /// </summary>
    /// <param name="viewXform">
    /// Matrix that transforms coordinates from WCS to DCS 
    /// </param>
    /// <param name="pickPt">
    /// Input point in world coordinates.
    /// </param>
    /// <param name="points">
    /// The array to which to append points. .
    /// </param>
    /// <returns>
    /// Returns true if successfully, otherwise, return false.
    /// </returns>
    /// <remarks> internal use </remarks>
    bool  getPlaneOrPointAt(const AcGeMatrix3d & viewXform, const AcGePoint3d & pickPt, AcArray<AcGePoint3d> & points);

    /// <summary>
    /// Finds any plane at the specified view coordinate. 
    /// This method will return true if it finds a plane.
    /// The output is an array of plane boundary vertices.
    /// </summary>
    /// <param name="viewXform">
    /// Matrix that transforms coordinates from WCS to DCS 
    /// </param>
    /// <param name="pickPt">
    /// Input point in world coordinates.
    /// </param>
    /// <param name="points">
    /// The array of plane boundary vertices to which to append points.
    /// </param>
    /// <returns>
    /// Returns true if successfully, otherwise, return false.
    /// </returns>
    bool  getPlaneBoundaryAt(const AcGeMatrix3d& viewXform, const AcGePoint3d& pickPt, AcGePoint3dArray& arrPlaneVertices);

    /// <summary>
    /// For internal use only.
    /// </summary>
    void * getQuery();

    /// <summary>
    /// Get object to world transform including ecs and block transform.
    /// </summary>
    /// <param name="mat">
    /// The transform matrix.
    /// </param>
    void objectToWorldMatrix(AcGeMatrix3d& mat) const;

    /// <summary>
    /// Get candidate planes for dynamic UCS detection purpose.
    /// </summary>
    /// <param name="pt">
    /// Cursor location in window screen coordinate.
    /// </param>
    /// <param name="result">
    /// The plane detected (the nearest plane is decided by point cloud object itself.
    /// </param>
    /// <param name="distToEdge">
    /// Distance from cursor to plane boundary (to calculate aperture box.
    /// </param>
    /// <param name="objWidth">
    /// width of the plane extent (needed for grid snapping adjustment.
    /// </param>
    /// <param name="objHeight">
    /// height of plane extent (needed for grid snapping adjustment).
    /// </param>
    /// <param name="context">
    /// an per object defined context (for later highlight and de-highlight notification data picky-back).
    /// </param>
    Acad::ErrorStatus getCandidatePlane(const class CPoint& pt, AcGePlane &result, double &distToEdge, double &objWidth, double &objHeight, void*& context) const;

    /// <summary>
    /// Finds any cylinder at the specified view coordinate. 
    /// This method will return true if it finds a cylinder.
    /// </summary>
    /// <param name="viewXform">
    /// Matrix that transforms coordinates from WCS to DCS 
    /// </param>
    /// <param name="pickPt">
    /// Input point in world coordinates.
    /// </param>
    /// <param name="origin">
    /// The origin of the cylinder, in ECS.
    /// </param>
    /// <param name="axis">
    /// The axis of the cylinder, in ECS.
    /// </param>
    /// <param name="height">
    /// The height of the cylinder.
    /// </param>
    /// <param name="radius">
    /// The radius of the cylinder.
    /// </param>
    /// <returns>
    /// Returns eOk if successfully.
    /// </returns>
    Acad::ErrorStatus  getCylinderAt(const AcGeMatrix3d& viewXform, const AcGePoint3d& pickPt, AcGePoint3d& origin, AcGeVector3d& axis, double& height, double& radius);

    /// <summary>
    /// Get the const crop states manager. From this class you can access the getter properties 
    // of crop state.
    /// </summary>
    /// <returns>
    /// Returns const AcDbPointCloudCropStateManager pointer.
    /// </returns>
    const AcDbPointCloudCropStateManager* cropStatesManagerConst() const;
    /// <summary>
    /// Get the crop states manager. From this class you can access the getter and setter properties of crop state.
    /// Don't free or delete this pointer.
    /// </summary>
    /// <returns>
    /// Returns AcDbPointCloudCropStateManager pointer.
    /// </returns>
    AcDbPointCloudCropStateManager* cropStatesManager();

    /// <summary>
    /// Gets minimal distance precision
    /// </summary>
    /// <param name="minDistPrecision">
    /// The output param of minimal distance precision.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if success, eNotApplicable if fail. 
    /// </returns>
    Acad::ErrorStatus getMinDistPrecision(double& minDistPrecision) const;

    /// <summary>
    /// Gets Point data by precision
    /// </summary>
    /// <param name="pointData">
    /// output the point data
    /// </param>
    /// <param name="distPrecision">
    /// distance precision
    /// </param>
    /// <param name="pSpatialFilter">
    /// Spatial filter
    /// </param>
    /// <param name="pAttributeFilter">
    /// Attribute filter
    /// </param>
    /// <param name="dataTypes">
    /// data type
    /// </param>
    /// <param name="maxPointLimitation">
    /// max point limitation
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if success, eNotApplicable if fail. 
    /// </returns>
    Acad::ErrorStatus getPointDataByPrecision(IAcDbPointCloudDataBuffer*& pointData, double distPrecision, IAcDbPointCloudSpatialFilter* pSpatialFilter = NULL,
        IAcDbPointCloudAttributeFilter* pAttributeFilter = NULL, Adesk::UInt32 dataTypes = 0, Adesk::UInt32 maxPointLimitation = 1000000uLL) const;

    /// <summary>
    /// Gets the estimated point count by precision
    /// </summary>
    /// <param name="pointCount">
    /// output the point count
    /// </param>
    /// <param name="distPrecision">
    /// distance precision
    /// </param>
    /// <param name="pSpatialFilter">
    /// Spatial filter
    /// </param>
    /// <param name="pAttributeFilter">
    /// Attribute filter
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if success, eNotApplicable if fail. 
    /// </returns>
    Acad::ErrorStatus getEstimatedPointCountByPrecision(unsigned long long &pointCount, double distPrecision, IAcDbPointCloudSpatialFilter* pSpatialFilter = NULL, IAcDbPointCloudAttributeFilter* pAttributeFilter = NULL) const;

    /// <summary>
    /// This member function is used to control behavior for custom objects and entities when saving to previous formats.
    /// Custom objects can decompose themselves into other objects and can add additional xdata to the objects created. 
    /// The default implementation of this function sets replaceObj to NULL and replaceid to AcDbObjectId::kNull so that
    /// no decomposition is done. If this is overridden, the custom object can create any number of new objects.
    /// It has to return one of them as a replacement object and the original is subsequently deleted by ObjectARX. 
    /// The function can either return an AcDbObjectId in replaceId or it can return an AcDbObject* in replaceObj. 
    /// If the object pointer is returned, ObjectARX adds the entity to the database. Only one of replaceObj or replaceId should be returned.
    /// In both cases ObjectARX transfers the objectId from the original to the replacement so that inter-object references are maintained. 
    /// If decomposeForSave() is overridden in an custom object, the exchangeXData argument should be set by the new 
    /// implementation of decomposeForSave to indicate to ObjectARX whether or not to transfer xdata from the original to the replacement.
    /// If the custom object's implementation of decomposeForSave() does not add any new xdata, and decomposeForSave() returns with 
    /// exchangeXData set to Adesk::kTrue, then ObjectARX transfers all existing xdata from the original object to the replacement. 
    /// If exchangeXData is set to Adesk::kFalse, then the existing xdata is left with the original object. 
    /// exchangeXData is set to Adesk::kTrue in the internal implementation so the default behavior will be to transfer xdata. 
    /// Overriding this method will allow the application to handle the xdata transfer itself or let ObjectARX handle it. 
    /// If the custom object's implementation of decomposeForSave() adds any xdata to the replacement, then it must also deal with 
    /// transferring all xdata from the original to the replacement if that xdata is to be preserved. 
    /// It should set exchangeXData to Adesk::kFalse to indicate that ObjectARX is not to transfer any xdata. 
    /// It is not possible for the implementation of decomposeForSave() to add new xdata to the replacement object and then
    /// return with exchangeXData == Adesk::kTrue in order to have ObjectARX transfer the existing xdata from the original to the replacement. 
    /// If this is done, then the result is the loss of all the xdata added inside decomposeForSave(). 
    /// </summary>
    /// <param name="ver">
    /// Input DWG version being saved to 
    /// </param>
    /// <param name="replaceObj ">
    /// Output pointing to the non-database-resident object to be used as the replacement for the object this method is called on.
    /// Use this only for non-database-resident replacement object.
    /// </param>
    /// <param name="replaceId ">
    /// Output object ID of the object to be used as the replacement for the object this method is called on.
    /// Use this only for database-resident replacement object.
    /// </param>
    /// <param name="exchangeXData ">
    /// Output Boolean indicating whether or not ObjectARX should transfer xdata 
    /// </param>
    /// <returns>
    /// This function should return Acad::eOk if successful. Any other return status terminates the operation.
    /// </returns>
    Acad::ErrorStatus  decomposeForSave(AcDb::AcDbDwgVersion ver, AcDbObject*& replaceObj, AcDbObjectId& replaceId,Adesk::Boolean& exchangeXData);
    /// <summary>
    /// Finds any cylinder at the specified view coordinate. 
    /// This method will return true if it finds a cylinder.
    /// </summary>
    /// <param name="viewXform">
    /// Matrix that transforms coordinates from WCS to DCS 
    /// </param>
    /// <param name="pickPt">
    /// Input point in world coordinates.
    /// </param>
    /// <param name="extractedCylinder">
    /// The extracted cylinder data (transformed from Recap data format to our own)
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successfully, otherwise, return false.
    /// </returns>
    Acad::ErrorStatus getCylinderAt(const AcGeMatrix3d& viewXform, const AcGePoint3d& pickPt, AcPointCloudExtractedCylinder& extractedCylinder);

    /// <summary>
    /// Given a point in WCS, get the belonging scan and segment index that contains this point
    /// <param name="ptInWCS">
    /// Input point in world coordinates.
    /// </param>
    /// <param name="scanGuid">
    /// Output the scan GUID that contains this point.
    /// </param>
    /// <param name="segmentIndex">
    /// Output the index of the segment that contains this point.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successfully.
    /// </returns>
    Acad::ErrorStatus  detectPointBelonger(const AcGePoint3d& ptInWCS, AcString& scanGuid, Adesk::UInt16& segmentIndex) const;

    /// <summary>
    /// Given the scan and segment index, get a point data buffer with an expected point number.
    /// <param name="pointData">
    /// Output parameter for a pointer to a IAcDbPointCloudDataBuffer upon successful return. 
    /// Note that only point coordinates are returned in the buffer.
    /// The caller should release the buffer by calling freeObject()
    /// after consuming the buffer
    /// </param>
    /// <param name="scanGuid">
    /// Input the scan GUID.
    /// </param>
    /// <param name="segmentIndex">
    /// Input the segment index.
    /// </param>
    /// <param name="nExpectedCount">
    /// The expected amount of points the function will return.
    /// The actual amount depends on the segment size.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successfully.
    /// </returns>
    Acad::ErrorStatus  getPointDataBySegment(IAcDbPointCloudDataBuffer*& pointData, const AcString& scanGuid, Adesk::UInt16 nSegmentIndex, Adesk::UInt32 nExpectedCount) const;

    /// <summary>
    /// Fills a given buffer with point data by specifying how many point you want and the spatial and attribute filters.
    /// This method does not consider view dependent filters and scan visiblity settings.
    /// </summary>
    /// <param name="pointData">
    /// Output parameter for a pointer to a IAcDbPointCloudDataBuffer upon successful return. 
    /// The caller should release the buffer by calling freeObject()
    /// after consuming the buffer
    /// </param>
    /// <param name="arrScanGuids">
    /// Specify an array of scan GUIDs which whose points will be returned.
    /// </param>
    /// <param name="pointCount">
    /// How many points you want (approximate amount, the actual point number returned will not be the exact amount)
    /// </param>
    /// <param name="pSpatialFilter">
    /// The spatial filter you want to exclude points (NULL if no filtering is needed)
    /// </param>
    /// <param name="pAttributeFilter">
    /// The attribute filter you want to exclude points (NULL if no filtering is needed)
    /// </param>
    /// <param name="dataTypes">
    /// A combination of IAcDbPointCloudDataBuffer::DataType to specify the data you want to consume.
    /// </param>
    /// <param name="maxPointLimitation">
    /// The maximum amount of points the function will return (cannot execeed 0x1000000)
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input pointCount or maxPointLimitation is invalid.
    /// Returns Acad::ePCFileNotOpened if the scan file is not found or not open.
    /// Returns Acad::eOutOfMemory if the calculation consumes too much.
    /// Returns Acad::ePCUnknown otherwise.
    /// </returns>
    Acad::ErrorStatus  getPointDataByPointCount(IAcDbPointCloudDataBuffer*& pointData, Adesk::UInt32 pointCount, const AcArray<AcString>& arrScanGuids, IAcDbPointCloudSpatialFilter* pSpatialFilter,
                         IAcDbPointCloudAttributeFilter* pAttributeFilter, Adesk::UInt32 dataTypes, Adesk::UInt32 maxPointLimitation) const;

    /// <summary>
    /// Processes all data in the point cloud using the spatial filter.
    /// This method does not consider view dependent filters and scan visiblity.
    /// </summary>
    /// <param name="processor">
    /// The IAcDbPointCloudPointProcessor that will be called during the point traversal 
    /// </param>
    /// <param name="pSpatialFilter">
    /// The spatial filter you want to exclude points (NULL if no filtering is needed)
    /// </param>
    /// <param name="dataTypes">
    /// A combination of IAcDbPointCloudDataBuffer::DataType to specify the data you want to consume
    /// </param>
    /// <param name="LODLevel">
    /// The level of detail level, value should be between 1-100. Note: the actual supported LOD depends on the scan files.
    /// </param>
    /// <param name="arrScanGuids">
    /// Specify an array of scan GUIDs which whose points will be returned.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eInvalidInput if the input processor or LODLevel is invalid.
    /// Returns Acad::ePCFileNotOpened if the scan file is not found or not open.
    /// Returns Acad::ePCUnknown otherwise.
    /// </returns>
    Acad::ErrorStatus  traverseAllPointData(IAcDbPointCloudPointProcessor* processor, IAcDbPointCloudSpatialFilter* pSpatialFilter, Adesk::UInt32 dataTypes, int LODLevel, const AcArray<AcString>& arrScanGuids) const;
	
private:
    PointCloudExImp*        m_pImp;

    friend class AcDbPointCloudCropStateManagerImp;
};
