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
// DESCRIPTION: 
// Classes for recording and retrieving render settings and render history.
//
// AcDbRenderSettings
// AcDbMentalRayRenderSettings
// AcDbRapidRTRenderSettings
// AcDbRenderGlobal
// AcDbRenderEntry
//

#pragma once

#include "AcGiEnvironment.h"

#ifdef SCENEDLLIMPEXP
#undef SCENEDLLIMPEXP
#endif
#ifdef SCENEOE
#define SCENEDLLIMPEXP __declspec( dllexport )
#else
// NOTE: Don't use __declspec( dllimport ) here, to avoid having vtables
// allocated in the client DLL instead of the server DLL.
#define SCENEDLLIMPEXP //__declspec( dllimport )
#endif

class AcDbImpRenderSettings;
class AcDbImpRenderEnvironment;
class AcDbImpRapidRTRenderEnvironment;
class AcDbImpRenderGlobal;
class AcDbImpMentalRayRenderSettings;

/// <summary>
/// Container for all properties relating to a generic high-fidelity renderer.
/// A dictionary of these objects is resident in the database, in the named
/// object dictionary as ACAD_RENDER_SETTINGS. 
/// In the user interface, the contents of this
/// dictionary correspond to user-defined render presets (not predefined
/// presets).  For Postrio, these are actually AcDbMentalRayRenderSettings
/// objects.
///
/// The active render settings is stored separately in the named object dictionary
/// as ACAD_RENDER_ACTIVE_SETTINGS.
/// </summary>
class SCENEDLLIMPEXP AcDbRenderSettings : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbRenderSettings);

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbRenderSettings();

    /// <summary>
    /// Constructor with non-default AcDbImpRenderSettings
    /// </summary>
    AcDbRenderSettings(AcDbImpRenderSettings*);

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbRenderSettings();

    virtual AcGiDrawable* drawable() override;

    /// <summary>
    /// Sets the name of the render settings.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if a name with valid characters is provided.
    /// </returns>
    ///
    /// <remarks>
    /// This function does not check for duplicate names for render settings.
    /// </remarks>
    Acad::ErrorStatus setName(const AcString& strName);

    /// <summary>
    /// The user-defined name of the render settings.
    /// </summary>
    AcString name() const;

    /// <summary>
    /// Sets the description of the render settings.
    /// </summary>
    void setDescription(const AcString& strDes);

    /// <summary>
    /// The user-specified description of the render settings.
    /// </summary>
    AcString description() const;

    /// <summary>
    /// Sets the DisplayIndex of the render settings.
    /// DisplayIndex is used to determine the displaying order in the UI
    /// of the render settings stored in a dictionary.
    /// Render settings are displayed in the order from the smallest index to the largest.
    /// The indices can be negative and need not to form a contiguous sequence.
    /// DisplayIndex is not meant to be used as an Id.
    /// </summary>
    void setDisplayIndex(int idx);

    /// <summary>
    /// The DisplayIndex of the render settings.
    /// </summary>
    int displayIndex() const;

    /// <summary>
    /// Sets whether per-object materials are used.
    /// </summary>
    ///
    /// <remarks>
    /// If set to false, the global material is used for all objects.  The
    /// default value is true.
    /// </remarks>
    void setMaterialsEnabled(bool bEnabled);

    /// <summary>
    /// Whether per-object materials are used.
    /// </summary>
    bool materialsEnabled() const;

    /// <summary>
    /// Sets the method used for sampling (filtering) image textures.
    /// </summary>
    ///
    /// <remarks>
    /// This does not apply to procedural textures.  The default value is
    /// kMedium.
    /// </remarks>
    void setTextureSampling(bool bSampling);

    /// <summary>
    /// The method used for sampling (filtering) image textures.
    /// </summary>
    bool textureSampling() const;

    /// <summary>
    /// Whether back-facing faces are rendered.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is true.
    /// </remarks>
    void setBackFacesEnabled(bool bEnabled);

    /// <summary>
    /// Whether back-facing faces are rendered.
    /// </summary>
    bool backFacesEnabled() const;

    /// <summary>
    /// Sets whether shadows are cast.
    /// Does not apply to RapidRT
    /// </summary>
    ///
    /// <remarks>
    /// The default value is true.
    /// </remarks>
    void setShadowsEnabled(bool bEnabled);

    /// <summary>
    /// Whether shadows are cast.
    /// </summary>
    bool shadowsEnabled() const;

    /// <summary>
    /// Sets the full file name on disk of the preview image.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the file name is valid.
    /// </returns>
    ///
    /// <remarks>
    /// If a blank name is provided, no preview image is associated with the
    /// render settings.  The default value is blank.
    /// </remarks>
    Acad::ErrorStatus setPreviewImageFileName(const AcString& strFileName);

    /// <summary>
    /// The full file name on disk of the preview image.
    /// </summary>
    AcString previewImageFileName() const;

    /// <summary>
    /// Sets whether the diagnostic (checker) background is used for rendering.
    /// </summary>
    ///
    /// <remarks>
    /// If enabled, the diagnostic background overrides any user-defined
    /// background, such as a gradient.  The default value is false.
    /// </remarks>
    void setDiagnosticBackgroundEnabled(bool bEnabled);

    /// <summary>
    /// Whether the diagnostic (checker) background is used for rendering.
    /// </summary>
    bool diagnosticBackgroundEnabled() const;

    /// <summary>
    /// Set whether the settings are predefined or not
    /// </summary>
    Acad::ErrorStatus setIsPredefined(bool bPredefined);

    /// <summary>
    /// Whether the settings are predefined or not
    /// </summary>
    bool isPredefined() const;

    // AcDbObject functions
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

    virtual bool operator==(const AcDbRenderSettings& settings);

protected:
    // AcGiDrawable functions
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) override;
    AcDbImpRenderSettings* mpImp;
};

/// <summary>
/// Container for all properties relating to the mental ray renderer.  See
/// the base class AcDbRenderSettings for more information.
/// </summary>
class SCENEDLLIMPEXP AcDbMentalRayRenderSettings : public AcDbRenderSettings
{
public:
    ACRX_DECLARE_MEMBERS(AcDbMentalRayRenderSettings);

    /// <summary>
    /// Constructor.
    /// </summary>
    AcDbMentalRayRenderSettings();

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbMentalRayRenderSettings();

    /// <summary>
    /// Sets the minimum and maximum numbers of samples to take when shading a
    /// pixel during rendering.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if valid sampling values are provided.
    /// </returns>
    ///
    /// <param name="iMin">
    /// The minimum sampling rate, in the range -3 to 5.  Values less than zero
    /// enable subsampling.  -3 corresponds to one sample for every 64 pixel
    /// (1/64) and 5 corresponds to 1024 samples per pixel.  iMin must be less
    /// than or equal to iMax.  The default value is -1.
    /// </param>
    ///
    /// <param name="iMax">
    /// The maximum sampling rate, in the range -3 to 5.  The default value is
    /// 0.  See iMin for details.
    /// </param>
    Acad::ErrorStatus setSampling(int iMin, int iMax);

    /// <summary>
    /// The minimum and maximum numbers of samples to take when shading a
    /// pixel during rendering.
    /// </summary>
    void sampling(int& iMin, int& iMax) const;

    /// <summary>
    /// Sets the filtering parameters for combining multiple samples into a
    /// single pixel color.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if valid filtering parameters are provided.
    /// </returns>
    ///
    /// <param name="eFilter">
    /// The filtering method (kernel) used to combine samples into a pixel
    /// color.  The default value is kBox.
    /// </param>
    ///
    /// <param name="fWidth">
    /// The width of the filter area, in the range 0.0 to 8.0, in pixels.  The
    /// default is 1.0.
    /// </param>
    ///
    /// <param name="fHeight">
    /// The height of the filter area, in the range 0.0 to 8.0, in pixels.  The
    /// default is 1.0.
    /// </param>
    Acad::ErrorStatus setSamplingFilter(AcGiMrFilter eFilter, double fWidth,
        double fHeight);

    /// <summary>
    /// The filtering parameters for combining multiple samples into a single
    /// pixel color.
    /// </summary>
    void SamplingFilter(AcGiMrFilter& eFilter, double& fWidth, double& fHeight)
        const;

    /// <summary>
    /// Sets the threshold above which further samples will be taken, per-color
    /// channel.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if valid values are provided for each color channel.
    /// </returns>
    ///
    /// <remarks>
    /// Each color channel value can be in the range 0.0 to 1.0.  The default
    /// is 0.1 for each color channel.
    /// </remarks>
    Acad::ErrorStatus setSamplingContrastColor(float r, float g, float b,
        float a);

    /// <summary>
    /// The threshold above which further samples will be taken, per-color
    /// channel.
    /// </summary>
    void samplingContrastColor(float& r, float& g, float& b, float& a) const;

    /// <summary>
    /// Sets the method used to compute ray-traced shadows.
    /// </summary>
    ///
    /// <remarks>
    /// This only affects lights using ray-traced shadows.  The default value
    /// is kSimple.
    /// </remarks>
    void setShadowMode(AcGiMrShadowMode eShadowMode);

    /// <summary>
    /// The method used to compute ray-traced shadows.
    /// </summary>
    AcGiMrShadowMode shadowMode() const;

    /// <summary>
    /// Whether shadow maps are computed.
    /// </summary>
    ///
    /// <remarks>
    /// This only affects lights using mapped shadows.  The default value is
    /// true.
    /// </remarks>
    void setShadowMapsEnabled(bool bEnabled);

    /// <summary>
    /// Whether shadow maps are computed.
    /// </summary>
    bool shadowMapsEnabled() const;

    /// <summary>
    /// Whether ray-tracing is performed.
    /// </summary>
    ///
    /// <remarks>
    /// If ray-tracing is disabled, various effects such as reflection and
    /// refraction will not be computed.  The default value is true.
    /// </remarks>
    void setRayTracingEnabled(bool bEnabled);

    /// <summary>
    /// Whether ray-tracing is performed.
    /// </summary>
    bool rayTracingEnabled() const;

    /// <summary>
    /// Sets the maximum trace depth (recursion level) for rays.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the ray trace depth values are valid.
    /// </returns>
    ///
    /// <param name="iReflection">
    /// The maximum recursion level of reflection rays, greater than or equal
    /// to 0.  The default value is 2.
    /// </param>
    ///
    /// <param name="iRefraction">
    /// The maximum recursion level of refraction rays, greater than or equal
    /// to 0.  The default value is 2.
    /// </param>
    ///
    /// <param name="iSum">
    /// The maximum recursion level of reflection and refraction rays,
    /// combined.  The default value is 4.
    /// </param>
    Acad::ErrorStatus setRayTraceDepth(int iReflection, int iRefraction,
        int iSum);

    /// <summary>
    /// The maximum trace depth (recursion level) for rays.
    /// </summary>
    void rayTraceDepth(int& iReflection, int& iRefraction, int& iSum) const;

    /// <summary>
    /// Whether global illumination (using photon mapping) is computed.
    /// </summary>
    ///
    /// <remarks>
    /// Global illumination allows for indirect illumination effects such as
    /// color-bleeding.  The default value is false.
    /// </remarks>
    void setGlobalIlluminationEnabled(bool bEnabled);

    /// <summary>
    /// Whether global illumination (using photon mapping) is computed.
    /// </summary>
    bool globalIlluminationEnabled() const;

    /// <summary>
    /// Sets the maximum number of photons near a render sample point to use
    /// for computing global illumination.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the photon count value is valid.
    /// </returns>
    ///
    /// <remarks>
    /// The indicated number of photons around each render sample are used to
    /// to compute global illumination at that point, within the area defined
    /// by setGIPhotonRadius().  This value must be must be greater than zero.
    /// The default value is 500.
    /// </remarks>
    Acad::ErrorStatus setGISampleCount(int iNum);

    /// <summary>
    /// The maximum number of photons near a render sample point to use for
    /// computing global illumination.
    /// </summary>
    int giSampleCount() const;

    /// <summary>
    /// Whether the user-defined photon sampling radius is used.
    /// </summary>
    ///
    /// <remarks>
    /// If the photon sampling radius is not used, a default radius based on
    /// the model extents is used.  The default value is false.
    /// </remarks>
    void setGISampleRadiusEnabled(bool bEnabled);

    /// <summary>
    /// Whether the user-defined photon sampling radius is used.
    /// </summary>
    bool giSampleRadiusEnabled() const;

    /// <summary>
    /// Sets the radius of the area used to sample photons for global
    /// illumination.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the radius value is valid.
    /// </returns>
    ///
    /// <remarks>
    /// The indicated area around each render sample is searched for photons,
    /// up to the number of photons specified by setGIPhotonCount().  The
    /// radius is in model units, and must be greater than or equal to zero.
    /// The default value is 1.0.
    /// </remarks>
    Acad::ErrorStatus setGISampleRadius(double fRadius);

    /// <summary>
    /// The radius of the area used to sample photons for global illumination.
    /// </summary>
    double giSampleRadius() const;

    /// <summary>
    /// Sets the average number of GI photons to shoot for each light.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the photon count value is valid.
    /// </returns>
    ///
    /// <remarks>
    /// This value must be greater than zero.  The default value is 10000.
    /// </remarks>
    Acad::ErrorStatus setGIPhotonsPerLight(int iNum);

    /// <summary>
    /// The average number of GI photons to shoot for each light.
    /// </summary>
    int giPhotonsPerLight() const;

    /// <summary>
    /// Sets the maximum trace depth (recursion level) for photon.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the photon trace depth values are valid.
    /// </returns>
    ///
    /// <param name="iReflection">
    /// The maximum recursion level of reflected photons, greater than or equal
    /// to 0.  The default value is 5.
    /// </param>
    ///
    /// <param name="iRefraction">
    /// The maximum recursion level of refracted photons, greater than or equal
    /// to 0.  The default value is 5.
    /// </param>
    ///
    /// <param name="iSum">
    /// The maximum recursion level of reflected and refracted photon,
    /// combined.  The default value is 5.
    /// </param>
    Acad::ErrorStatus setPhotonTraceDepth(int iReflection, int iRefraction,
        int iSum);

    /// <summary>
    /// The maximum trace depth (recursion level) for photons.
    /// </summary>
    void photonTraceDepth(int& iReflection, int& iRefraction, int& iSum) const;

    /// <summary>
    /// Whether final gathering is applied.
    /// </summary>
    ///
    /// <remarks>
    /// Final gathering allows for indirect illumination effects such as
    /// color-bleeding, and can be combined with global illumination to enhance
    /// the effect of GI.  The default value is false.
    /// </remarks>
    void setFinalGatheringEnabled(bool bEnabled);

    /// <summary>
    /// Whether final gathering is applied.
    /// </summary>
    bool finalGatheringEnabled() const;

    /// <summary>
    /// Whether final gathering is applied.
    /// </summary>
    ///
    /// <remarks>
    /// Final gathering allows for indirect illumination effects such as
    /// color-bleeding, and can be combined with global illumination to enhance
    /// the effect of GI.  The default value is 
    /// AcGiMrFinalGatheringMode::krFinalGatherAuto.
    /// </remarks>
    Acad::ErrorStatus setFinalGatheringMode(AcGiMrFinalGatheringMode mode);

    /// <summary>
    /// Whether final gathering is applied.
    /// </summary>
    AcGiMrFinalGatheringMode finalGatheringMode() const;

    /// <summary>
    /// Sets the number of final gather rays to be used for each final gather
    /// point.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the final gather ray count count value is valid.
    /// </returns>
    ///
    /// <remarks>
    /// The indicated number of rays are shot into the scene for each final
    /// gather point to compute indirect illumination.  This value must be must
    /// be greater than zero.  The default value is 1000.
    /// </remarks>
    Acad::ErrorStatus setFGRayCount(int iNum);

    /// <summary>
    /// Sets the number of final gather rays to be used for each final gather
    /// point.
    /// </summary>
    int fgRayCount() const;

    /// <summary>
    /// Sets the flags indicating the user-defined final gathering sampling
    /// radii are used, and what units they are defined in.
    /// </summary>
    ///
    /// <param name="bMin">
    /// The flag indicating whether the user-defined minimum radius is used,
    /// otherwise a default radius is applied.  The default value is false.
    /// </param>
    ///
    /// <param name="bMax">
    /// The flag indicating whether the user-defined maximum radius is used,
    /// otherwise a default radius is applied.  The default value is false.
    /// </param>
    ///
    /// <param name="bPixels">
    /// The flag indicating whether the user-defined radii are in pixel units.
    /// The default value is false.
    /// </param>
    void setFGRadiusState(bool bMin, bool bMax, bool bPixels);

    /// <summary>
    /// The flags indicating the user-defined final gathering sampling radii
    /// are used, and what units they are defined in.
    /// </summary>
    void fgSampleRadiusState(bool& bMin, bool& bMax, bool& bPixels) const;

    /// <summary>
    /// Sets the minimum and maximum radii of the area used to sample final
    /// gather points to compute indirect illumination.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the radius values are valid.
    /// </returns>
    ///
    /// <param name="fMin">
    /// The minimum final gather sample radius, in units defined by
    /// setFGRadiusState().  This value must be less than or equal to fMax, and
    /// greater than zero.  The default values are 0.1 for model units and 0.5
    /// for pixel units.
    /// </param>
    ///
    /// <param name="fMax">
    /// The maximum final gather sample radius, in units defined by
    /// setFGRadiusState().  This value must be greater than or equal to fMin,
    /// and greater than zero.  The default values are 1.0 for model units and
    /// 5.0 for pixel units.
    /// </param>
    Acad::ErrorStatus setFGSampleRadius(double fMin, double fMax);

    /// <summary>
    /// The minimum and maximum radii of the area used to sample final gather
    /// points to compute indirect illumination.
    /// </summary>
    void fgSampleRadius(double& fMin, double& fMax) const;

    /// <summary>
    /// Sets a physical scale factor to use with lights that are not physically based.
    /// Physical scale may be necessary to set to a non-default value when rendering
    /// with self-illuminating materials or extremely bright photometric lights in
    /// order to approximate the eye's response to the scene.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the luminance value is valid.
    /// </returns>
    ///
    /// <param name="fLuminance">
    /// The physical scale factor to use with lights that are not physically based.
    /// </param>
    ///
    /// <remarks>
    /// This value must be greater than zero and less than or equal to 200000.0.
    /// The default value is 1500.0.
    /// </remarks>
    Acad::ErrorStatus setLightLuminanceScale(double fLuminance);

    /// <summary>
    /// The physical scale factor to use with lights that are not physically based.
    /// </summary>
    double lightLuminanceScale() const;

    /// <summary>
    /// Sets the magnitude of indirect illumination. 
    /// This parameter will effectively provide a global way to adjust the effect of GI.
    /// It multiplies the flux of every light as it pertains to photon emission.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the parameter value is valid.
    /// </returns>
    ///
    /// <remarks>
    /// This value must be greater than zero.  The default value is 1.0.
    /// </remarks>
    Acad::ErrorStatus setEnergyMultiplier(float fScale);

    /// <summary>
    /// The magnitude of indirect illumination.
    /// </summary>
    float energyMultiplier() const;

    /// <summary>
    /// Sets the mode for rendering diagnostic images.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is krOff.
    /// </remarks>
    void setDiagnosticMode(AcGiMrDiagnosticMode eDiagnosticMode);

    /// <summary>
    /// The mode for rendering diagnostic images.
    /// </summary>
    AcGiMrDiagnosticMode diagnosticMode() const;

    /// <summary>
    /// Set the coordinate system to use for the diagnostic grid including
    /// the distance between grid lines (size).
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the specified grid size is valid.
    /// </returns>
    ///
    /// <remarks>
    /// The grid size must be greater than zero.  The default mode is krObject
    /// and size is 10.0.
    /// </remarks>
    Acad::ErrorStatus setDiagnosticGridMode(
        AcGiMrDiagnosticGridMode eDiagnosticGridMode, float fSize);

    /// <summary>
    /// The coordinate system to use for the diagnostic grid including
    /// the distance between grid lines (size).
    /// </summary>
    void diagnosticGridMode(
        AcGiMrDiagnosticGridMode& eDiagnosticGridMode, float& fSize) const;

    /// <summary>
    /// Sets the type of photon information to visualize with the photon
    /// diagnostic mode.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is krDensity.
    /// </remarks>
    void setDiagnosticPhotonMode(
        AcGiMrDiagnosticPhotonMode eDiagnosticPhotonMode);

    /// <summary>
    /// The type of photon information to visualize with the photon diagnostic
    /// mode.
    /// </summary>
    AcGiMrDiagnosticPhotonMode diagnosticPhotonMode() const;

    /// <summary>
    /// Sets the samples diagnostic mode.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is false(off).
    /// </remarks>
    void setDiagnosticSamplesMode(bool bDiagnosticSamplesMode);

    /// <summary>
    /// The samples diagnostic mode.
    /// </summary>
    bool diagnosticSamplesMode() const;

    /// <summary>
    /// Sets the type of BSP information to visualize with the BSP diagnostic mode.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is krDepth.
    /// </remarks>
    void setDiagnosticBSPMode(AcGiMrDiagnosticBSPMode eDiagnosticBSPMode);
    
    /// <summary>
    /// The type of BSP information to visualize with the BSP diagnostic mode.
    /// </summary>
    AcGiMrDiagnosticBSPMode diagnosticBSPMode() const;

    /// <summary>
    /// Sets whether to export an MI file after rendering.
    /// </summary>
    ///
    /// <remarks>
    /// If set to true, the file name specified with setExportMIFileName() is
    /// used to save the MI file.  The default value is false.
    /// </remarks>
    void setExportMIEnabled(bool bEnabled);

    /// <summary>
    /// Whether to export an MI file after rendering.
    /// </summary>
    bool exportMIEnabled() const;

    /// <summary>
    /// Set the export to mi mode.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is AcGiMrExportMIMode::krExportMIOff.
    /// </remarks>
    Acad::ErrorStatus setExportMIMode(AcGiMrExportMIMode eExportMIMode);

    /// <summary>
    /// The export to mi mode.
    /// </summary>
    AcGiMrExportMIMode exportMIMode() const;

    /// <summary>
    /// Sets full file name on disk to use for an exported MI file.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the file name is valid.
    /// </returns>
    ///
    /// <remarks>
    /// The default value is blank.
    /// </remarks>
    Acad::ErrorStatus setExportMIFileName(const AcString& strFileName);
    
    /// <summary>
    /// The full file name on disk to use for an exported MI file.
    /// </summary>
    AcString exportMIFileName() const;

    /// <summary>
    /// Sets the size of the image tiles to use when rendering.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the tile size is valid.
    /// </returns>
    ///
    /// <remarks>
    /// Smaller values increase rendering time, but provide more frequent
    /// updates during rendering.The size must be in the range 4 to 512, and
    /// has a default value of 32.
    /// </remarks>
    Acad::ErrorStatus setTileSize(int iTileSize);

    /// <summary>
    /// The size of the image tiles to use when rendering.
    /// </summary>
    int tileSize() const;

    /// <summary>
    /// Sets the sequence (order) used to render image tiles.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is krHilbert.
    /// </remarks>
    void setTileOrder(AcGiMrTileOrder eTileOrder);

    /// <summary>
    /// The sequence (order) used to render image tiles.
    /// </summary>
    AcGiMrTileOrder tileOrder() const;

    /// <summary>
    /// Sets the maximum amount of memory (in MB) that the renderer will
    /// allocate for rendering.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the memory limit is valid.
    /// </returns>
    ///
    /// <remarks>
    /// After the memory limit is reached, the renderer will begin making
    /// performance tradeoffs to stay under the memory limit.  The memory limit
    /// must be at least 128 MB, and the default value is 1048 MB.
    /// </remarks>
    Acad::ErrorStatus setMemoryLimit(int iMemoryLimit);

    /// <summary>
    /// The maximum amount of memory (in MB) that the renderer will allocate
    /// for rendering.
    /// </summary>
    int memoryLimit() const;

    /// <summary>
    /// The shadow sampling multiplier for area lights.
    /// </summary>
    enum ShadowSamplingMultiplier {
        /// <summary>
        /// Zero.
        /// </summary>
        kSamplingMultiplierZero = 0,
        /// <summary>
        /// One-eighth.
        /// </summary>
        kSamplingMultiplierOneEighth,
        /// <summary>
        /// One-fourth.
        /// </summary>
        kSamplingMultiplierOneFourth,
        /// <summary>
        /// One-half.
        /// </summary>
        kSamplingMultiplierOneHalf,
        /// <summary>
        /// One.
        /// </summary>
        kSamplingMultiplierOne,
        /// <summary>
        /// Two.
        /// </summary>
        kSamplingMultiplierTwo
    };

    /// <summary>
    /// Specifies the shadow sampling multiplier for area lights.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is ShadowSamplingMultiplier::kSamplingMultiplierOne.
    /// </remarks>
    Acad::ErrorStatus setShadowSamplingMultiplier(
        AcDbMentalRayRenderSettings::ShadowSamplingMultiplier multiplier);

    /// <summary>
    /// The shadow sampling multiplier for area lights.
    /// </summary>
    AcDbMentalRayRenderSettings::ShadowSamplingMultiplier shadowSamplingMultiplier() const;

    // AcDbObject functions
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

	virtual bool operator==(const AcDbMentalRayRenderSettings& settings);

	Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

protected:
    // AcGiDrawable functions
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) override;

private:
    friend class AcDbImpMentalRayRenderSettings;
    Adesk::UInt32 baseSetAttributes(AcGiDrawableTraits* pTraits);
	AcDbImpMentalRayRenderSettings* mpImpMentalRay;
};

/// <summary>
/// Container for all properties relating to the rapid RT renderer.  See
/// the base class AcDbRenderSettings for more information.
/// </summary>
class SCENEDLLIMPEXP AcDbRapidRTRenderSettings : public AcDbRenderSettings
{
public:
	ACRX_DECLARE_MEMBERS(AcDbRapidRTRenderSettings);

	/// <summary>
	/// Render, Target Quit Condition
	/// </summary>
	enum RenderTarget
	{
        /// <summary>
	    /// By Render Level (iteration)
	    /// </summary>
		krLevel    = 0,
        /// <summary>
	    /// By Render Time
	    /// </summary>
		krTime     = 1,
        /// <summary>
	    /// Until user abort
	    /// </summary>
        krInfinite = 2
	};

	/// <summary>
	/// Constructor.
	/// </summary>
	AcDbRapidRTRenderSettings();

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~AcDbRapidRTRenderSettings();

	/// <summary>
	/// Set the render target of the RapidRT render settings.
	/// </summary>
	Acad::ErrorStatus setRenderTarget(RenderTarget target);

	/// <summary>
	/// Get the render target of the RapidRT render settings.
	/// </summary>
	RenderTarget renderTarget() const;

	/// <summary>
	/// Set the render level of the RapidRT render settings.
	/// </summary>
	Acad::ErrorStatus setRenderLevel(int level);

	/// <summary>
	/// Get the render level of the RapidRT render settings.
	/// </summary>
	int renderLevel() const;

	/// <summary>
	/// Set the render time of the RapidRT render settings.
	/// </summary>
	Acad::ErrorStatus setRenderTime(int time);

	/// <summary>
	/// Get the render time of the RapidRT render settings.
	/// </summary>
	int renderTime() const;

	/// <summary>
	/// Set the render lighting model of the RapidRT render settings.
	/// </summary>
	Acad::ErrorStatus setLightingModel(AcGiLightingMode model);

	/// <summary>
	/// Get the render lighting model of the RapidRT render settings.
	/// </summary>
	AcGiLightingMode lightingModel() const;

	/// <summary>
	/// Set the filter type of the RapidRT render settings.
	/// </summary>
	Acad::ErrorStatus setFilterType(AcGiFilterType type);

	/// <summary>
	/// Get the filter type of the RapidRT render settings.
	/// </summary>
	AcGiFilterType filterType() const;

	/// <summary>
	/// Set the filter width of the RapidRT render settings.
	/// </summary>
	Acad::ErrorStatus setFilterWidth(float width);

	/// <summary>
	/// Get the filter width of the RapidRT render settings.
	/// </summary>
	float filterWidth() const;

	/// <summary>
	/// Set the filter height of the RapidRT render settings.
	/// </summary>
	Acad::ErrorStatus setFilterHeight(float height);

	/// <summary>
	/// Get the filter height of the RapidRT render settings.
	/// </summary>
	float filterHeight() const;

	// AcDbObject functions
	virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
	virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
	virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
	virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

	virtual bool operator==(const AcDbRapidRTRenderSettings& settings);

	/// <summary>
	/// Copy all the render settings from an AcDbRapidRTRenderSettings object.
	/// </summary>
	Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

	virtual Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver, AcDbObject*& replaceObj,
		AcDbObjectId& replaceId, Adesk::Boolean& exchangeXData) override;

protected:
	// AcGiDrawable functions
	virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) override;
};

/// <summary>
/// Container for environment-related properties, including fog / depth cue and
/// the global environment image.  One and only one of these objects is
/// resident in the database, in the named object dictionary as ACAD_RENDER_ENVIRONMENT.
/// </summary>
class SCENEDLLIMPEXP AcDbRenderEnvironment : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbRenderEnvironment);
    
    /// <summary>
    /// Constructor.
    /// </summary>
    AcDbRenderEnvironment();
    
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbRenderEnvironment();

    virtual AcGiDrawable* drawable() override;

    /// <summary>
    /// Sets whether a fog effect is applied to the rendered image.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is false.
    /// </remarks>
    void setFogEnabled(bool bEnable);

    /// <summary>
    /// Whether a fog effect is applied to the rendered image.
    /// </summary>
    bool fogEnabled() const;

    /// <summary>
    /// Sets whether the fog affects the background.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is false.
    /// </remarks>
    void setFogBackgroundEnabled(bool bEnable);

    /// <summary>
    /// Whether the fog affects the background.
    /// </summary>
    bool fogBackgroundEnabled() const;

    /// <summary>
    /// Sets the color of the fog effect.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is medium gray: 128, 128, 128.
    /// </remarks>
    void setFogColor(const AcCmEntityColor& color);

    /// <summary>
    /// The color of the fog effect.
    /// </summary>
    AcCmEntityColor fogColor() const;

    /// <summary>
    /// Sets the density of the fog effect.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the density values are valid.
    /// </returns>
    ///
    /// <param name="dNear">
    /// The density of the fog at the near distance specified with
    /// setDistances(), expressed as a percentage in the range 0.0 to 100.0.
    /// The value must be less than or equal to the density at the far
    /// distance.  The default value is 0.0 (no fog).
    /// </param>
    ///
    /// <param name="dFar">
    /// The density of the fog at the far distance specified with
    /// setDistances(), expressed as a percentage in the range 0.0 to 100.0.
    /// The value must be greater than or equal to the density at the near
    /// distance.  The default value is 100.0 (opaque fog).
    /// </param>
    Acad::ErrorStatus setFogDensity(double dNear, double dFar);

    /// <summary>
    /// The density of the fog effect.
    /// </summary>
    void fogDensity(double& dNear, double& dFar) const;

    /// <summary>
    /// Sets the near and far distances of the fog effect.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the distances are valid.
    /// </returns>
    ///
    /// <param name="dNear">
    /// The near distance of the fog, expressed as a percentage of the distance
    /// between the camera and the far clipping plane.  The value must be in
    /// the range 0.0 to 100.0, and must be less than or equal to the far
    /// distance.  The default value is 0.0 (at the camera).
    /// </param>
    ///
    /// <param name="dFar">
    /// The far distance of the fog, expressed as a percentage of the distance
    /// between the camera and the far clipping plane.  The value must be in
    /// the range 0.0 to 100.0, and must be greater than or equal to the near
    /// distance.  The default value is 100.0 (at the far clipping plane).
    /// </param>
    Acad::ErrorStatus setDistances(double dNear, double dFar);

    /// <summary>
    /// The near and far distances of the fog effect.
    /// </summary>
    void distances(double& dNear, double& dFar) const;

    /// <summary>
    /// Sets whether to use an image for the environment.
    /// </summary>
    ///
    /// <remarks>
    /// If set to true, the file name specified with
    /// setEnvironmentImageFileName() is used as the environment image.  The
    /// The default value is false.
    /// </remarks>
    void setEnvironmentImageEnabled(bool bEnabled);

    /// <summary>
    /// Whether to use an image for the environment.
    /// </summary>
    bool environmentImageEnabled() const;

    /// <summary>
    /// Sets the full file name on disk of the environment image.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the file name is valid.
    /// </returns>
    ///
    /// <remarks>
    /// The default value is blank.
    /// </remarks>
    Acad::ErrorStatus setEnvironmentImageFileName(const AcString& strFileName);

    /// <summary>
    /// The full file name on disk of the environment image.
    /// </summary>
    AcString environmentImageFileName() const;

    // AcDbObject functions
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

	virtual bool operator==(const AcDbRenderEnvironment& environment);

protected:
    // AcGiDrawable functions
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) override;
    AcDbImpRenderEnvironment* mpImp;
};

/// <summary>
/// Container for all global rendering properties.  One and only one of these
/// objects is resident in the database, in the named object dictionary as
/// ACAD_RENDER_GLOBAL.
/// </summary>
class SCENEDLLIMPEXP AcDbRenderGlobal : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbRenderGlobal);
    
    /// <summary>
    /// The available types of view content to render (render procedures).
    /// </summary>
    enum Procedure
    {
        /// <summary>
        /// Render the complete contents of the view.
        /// </summary>
        krView = 0,

        /// <summary>
        /// Render only the user-defined rectangular region of the view.
        /// </summary>
        krCrop,

        /// <summary>
        /// Render only the selected objects in the view.
        /// Deprecated for RapidRT
        /// </summary>
        krSelected
    };

    /// <summary>
    /// The available output targets for rendering.
    /// </summary>
    enum Destination
    {
        /// <summary>
        /// The rendered image appears in the separate Render window.
        /// </summary>
        krWindow = 0,

        /// <summary>
        /// The rendered image appears directly in the current viewport.
        /// </summary>
        krViewport
    };

    /// <summary>
    /// Constructor.
    /// </summary>
    AcDbRenderGlobal();

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbRenderGlobal();

	/// <summary>
    /// Sets the type of view content to render (the procedure) and the desired
    /// output target for rendering.
    /// </summary>
    ///
    /// <remarks>
    /// The default values are krView and krWindow.
    /// </remarks>
    void setProcedureAndDestination(Procedure eProcedure,
        Destination eDestination);

    /// <summary>
    /// The type of view content to render (the procedure) and the desired
    /// output target for rendering.
    /// </summary>
    void procedureAndDestination(Procedure& eProcedure,
        Destination& eDestination) const;

    /// <summary>
    /// Internal Use Only. Please use setProcedureAndDestination()
    /// for instead.
    ///
    /// Sets the type of view content to render (the procedure).
    /// </summary>
    ///
    /// <remarks>
    /// The default value is krView.
    /// </remarks>
    Acad::ErrorStatus setProcedure(Procedure eProcedure);

    /// <summary>
    /// Internal Use Only. Please use procedureAndDestination()
    /// for instead.
    ///
    /// The type of view content to render (the procedure).
    /// </summary>
    Procedure procedure();

    /// <summary>
    /// Internal Use Only. Please use setProcedureAndDestination()
    /// for instead.
    ///
    /// Sets the type of the desired output target for rendering.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is krWindow.
    /// </remarks>
    Acad::ErrorStatus setDestination(Destination eDestination);
    
    /// <summary>
    /// Internal Use Only. Please use procedureAndDestination()
    /// for instead.
    ///
    /// The type of the desired output target for rendering.
    /// </summary>
    Destination destination();

    /// <summary>
    /// Sets whether to save an image on disk after rendering.
    /// </summary>
    ///
    /// <remarks>
    /// If set to true, the file name specified with setSaveFileName() is used
    /// to save the image.  The default value is false.
    /// </remarks>
    void setSaveEnabled(bool bEnabled);

    /// <summary>
    /// Whether to save an image on disk after rendering.
    /// </summary>
    bool saveEnabled() const;

    /// <summary>
    /// Sets the full file name on disk with which to save the rendered image.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the file name is valid.
    /// </returns>
    ///
    /// <remarks>
    /// The default value is blank.
    /// </remarks>
    Acad::ErrorStatus setSaveFileName(const AcString& strFileName);

    /// <summary>
    /// The full file name on disk with which to save the rendered image.
    /// </summary>
    AcString saveFileName() const;

    /// <summary>
    /// Sets the dimensions of the rendered image.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the dimensions are valid.
    /// </returns>
    ///
    /// <remarks>
    /// Each dimension must be in the range 1 to 4096.  The default values are
    /// 640 and 480.
    /// </remarks>
    Acad::ErrorStatus setDimensions(int w, int h);

    /// <summary>
    /// The dimensions of the rendered image.
    /// </summary>
    void dimensions(int& w, int& h) const;

    /// <summary>
    /// Sets whether predefined (factory) presets appear before the user-
    /// defined presets in the user interface.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is true.
    /// </remarks>
    void setPredefinedPresetsFirst(bool bPredefinedPresetsFirst);

    /// <summary>
    /// Whether predefined (factory) presets appear before the user-defined
    /// presets in the user interface.
    /// </summary>
    bool predefinedPresetsFirst() const;
    
    /// <summary>
    /// Sets whether settings / statistics are displayed in the user interface
    /// with the higher level of detail.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is true.
    /// </remarks>
    void setHighInfoLevel(bool bHighInfoLevel);

    /// <summary>
    /// Whether settings / statistics are displayed in the user interface with
    /// the higher level of detail.
    /// </summary>
    bool highInfoLevel() const;

    /// <summary>
    /// Sets the exposure control type.
    /// </summary>
    ///
    /// <remarks>
    /// The default value is AcGiMrExposureType::krAutomatic.
    /// </remarks>
    Acad::ErrorStatus setExposureType(AcGiMrExposureType type);

    /// <summary>
    /// The exposure control type.
    /// </summary>
    AcGiMrExposureType exposureType() const;
    
    // AcDbObject functions
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

    Acad::ErrorStatus copyFrom( const AcRxObject* other ) override;

private:
    AcDbImpRenderGlobal* mpImp;

public:
    bool operator==(const AcDbRenderGlobal& global);
    AcString dimensionName() const;
};
