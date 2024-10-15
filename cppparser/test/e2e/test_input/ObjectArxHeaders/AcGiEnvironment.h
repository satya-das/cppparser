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
// This API extends AcGi to support backgrounds, environmental objects
// and render settings
//
#pragma once

#include "acgi.h"
#include "AcGiLightTraits.h"
#pragma pack (push, 8)

#ifdef ACGIENVIRONMENT_IMPL
#define ACGIENV_IMPEXP __declspec(dllexport)
#else
#define ACGIENV_IMPEXP __declspec(dllimport)
#endif


class ACDBCORE2D_PORT AcGiSolidBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables solid background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiSolidBackgroundTraits);

    // solid background
    virtual void            setColorSolid           (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorSolid              (void) const            = 0;
};

class ACDBCORE2D_PORT AcGiGradientBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables gradient background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGradientBackgroundTraits);

    virtual void            setColorTop             (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorTop                (void) const           = 0;
    virtual void            setColorMiddle          (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorMiddle             (void) const           = 0;
    virtual void            setColorBottom          (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorBottom             (void) const           = 0;
    virtual void            setHorizon              (double horizon)       = 0;
    virtual double          horizon                 (void) const           = 0;
    virtual void            setHeight               (double height)        = 0;
    virtual double          height                  (void) const           = 0;
    virtual void            setRotation             (double rotation)      = 0;
    virtual double          rotation                (void) const           = 0;
};

class ACDBCORE2D_PORT AcGiImageBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables image background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiImageBackgroundTraits);

    virtual void            setImageFilename        (const ACHAR* filename) = 0;
    virtual const ACHAR *   imageFilename           (void) const           = 0;
    virtual void            setFitToScreen          (bool bFitToScreen)    = 0;
    virtual bool            fitToScreen             (void) const           = 0;
    virtual void            setMaintainAspectRatio  (bool bMaintainAspectRatio) = 0;
    virtual bool            maintainAspectRatio     (void) const           = 0;
    virtual void            setUseTiling            (bool bUseTiling)      = 0;
    virtual bool            useTiling               (void) const           = 0;
    virtual void            setXOffset              (double xOffset)       = 0;
    virtual double          xOffset                 (void) const           = 0;
    virtual void            setYOffset              (double yOffset)       = 0;
    virtual double          yOffset                 (void) const           = 0;
    virtual void            setXScale               (double xScale)        = 0;
    virtual double          xScale                  (void) const           = 0;
    virtual void            setYScale               (double yScale)        = 0;
    virtual double          yScale                  (void) const           = 0;
};

class ACDBCORE2D_PORT AcGiGroundPlaneBackgroundTraits : public AcGiNonEntityTraits
// 
// This class enables ground plane background definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGroundPlaneBackgroundTraits);

    virtual void            setColorSkyZenith       (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorSkyZenith          (void) const           = 0;
    virtual void            setColorSkyHorizon      (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorSkyHorizon         (void) const           = 0;
    virtual void            setColorUndergroundHorizon  (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorUndergroundHorizon     (void) const           = 0;
    virtual void            setColorUndergroundAzimuth  (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorUndergroundAzimuth     (void) const           = 0;
    virtual void            setColorGroundPlaneNear (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorGroundPlaneNear    (void) const           = 0;
    virtual void            setColorGroundPlaneFar  (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor colorGroundPlaneFar     (void) const           = 0;
};

/// <summary>
/// This class enables sky background definitions to be elaborated to 
/// AcGi implementations.
/// </summary>
///
class ACDBCORE2D_PORT AcGiSkyBackgroundTraits : public AcGiNonEntityTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiSkyBackgroundTraits);

    /// <summary>
    /// Sets the sky parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiSkyParameters object that contains the sky properties used
    /// by this background.
    /// </param>
    virtual void setSkyParameters(const AcGiSkyParameters& params) = 0;

    /// <summary>
    /// Provides access to sky parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiSkyParameters object that contains the sky properties used
    /// by this background.
    /// </param>
    virtual void skyParameters(AcGiSkyParameters& params) const = 0;
};

/// <summary>
/// This class enables IBL background definitions to be elaborated to 
/// AcGi implementations.
/// </summary>
///
class ACDBCORE2D_PORT AcGiIBLBackgroundTraits : public AcGiNonEntityTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiIBLBackgroundTraits);

    /// <summary>
    /// Sets whether IBL is currently active
    /// </summary>
    /// <param name="name">
    /// True if active
    /// </param>
    virtual void            setEnable               (const bool bEnable)    = 0;
    /// <summary>
    /// Gets whether IBL is currently active
    /// </summary>
    /// <returns>
    /// True if active
    /// </returns>
    virtual bool            enable                  (void) const            = 0;
    /// <summary>
    /// Sets the image used for IBL
    /// </summary>
    /// <param name="name">
    /// Name of IBL image
    /// </param>
    virtual void            setIBLImageName         (const AcString& name)  = 0;
    /// <summary>
    /// Gets the image used for IBL
    /// </summary>
    /// <returns>
    /// Name of IBL image
    /// </returns>
    virtual AcString        IBLImageName            (void) const            = 0;
    /// <summary>
    /// Sets the rotation value for the IBL image
    /// -180 to 180 degrees
    /// </summary>
    /// <param name="rotation">
    /// Rotation value in degrees (-180 to 180)
    /// </param>
    virtual void            setRotation             (const double rotation) = 0;
    /// <summary>
    /// Gets the rotation value for the IBL image
    /// </summary>
    /// <returns>
    /// Rotation value in degrees
    /// </returns>
    virtual double          rotation                (void) const            = 0;
    /// <summary>
    /// Sets whether to display the IBL image as the background
    /// </summary>
    /// <param name="bdisplay">
    /// Set to true to display IBL image in background
    /// </param>
    virtual void            setDisplayImage         (const bool bdisplay)   = 0;
    /// <summary>
    /// Gets whether to display the IBL image as the background
    /// </summary>
    /// <returns>
    /// True if IBL image is to be displayed as background
    /// </returns>
    virtual bool            displayImage            (void) const            = 0;
    /// <summary>
    /// Sets the background to display when DisplayImage is set to false
    /// Limited to 2D backgrounds only - Solid, Gradient, Image
    /// </summary>
    /// <param name="bg">
    /// Background db Id
    /// </param>
    virtual void            setSecondaryBackground  (const AcDbObjectId bg) = 0;
    /// <summary>
    /// Gets the background to display when DisplayImage is set to false
    /// </summary>
    /// <returns>
    /// Background db Id
    /// </returns>
    virtual AcDbObjectId    secondaryBackground     (void) const            = 0;
};

class AcGiMaterialTexture;

class ACDBCORE2D_PORT AcGiRenderEnvironmentTraits : public AcGiNonEntityTraits
// 
// This class enables render environment definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiRenderEnvironmentTraits);

    virtual void            setEnable               (const bool bEnable)    = 0;
    virtual bool            enable                  (void) const            = 0;
    virtual void            setIsBackground         (const bool bEnable)    = 0;
    virtual bool            isBackground            (void) const            = 0;
    virtual void            setFogColor             (const AcCmEntityColor & color) = 0;
    virtual AcCmEntityColor fogColor                (void) const            = 0;
    virtual void            setNearDistance         (const double nearDist) = 0;
    virtual double          nearDistance            (void) const            = 0;
    virtual void            setFarDistance          (const double farDist)  = 0;
    virtual double          farDistance             (void) const            = 0;
    virtual void            setNearPercentage       (const double nearPct)  = 0;
    virtual double          nearPercentage          (void) const            = 0;
    virtual void            setFarPercentage        (const double farPct)   = 0;
    virtual double          farPercentage           (void) const            = 0;
    virtual void            setEnvironmentMap       (const AcGiMaterialTexture * map) = 0;
    virtual AcGiMaterialTexture * environmentMap    (void) const = 0;
};

class ACDBCORE2D_PORT AcGiRenderSettingsTraits : public AcGiNonEntityTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiRenderSettingsTraits);

    virtual void setMaterialEnabled(bool enabled) = 0;
    virtual bool materialEnabled() const = 0;

    virtual void setTextureSampling(bool enabled) = 0;
    virtual bool textureSampling() const = 0;

    virtual void setBackFacesEnabled(bool enabled) = 0;
    virtual bool backFacesEnabled() const = 0;

    virtual void setShadowsEnabled(bool enabled) = 0;
    virtual bool shadowsEnabled() const = 0;

    virtual void setDiagnosticBackgroundEnabled(bool enabled) = 0;
    virtual bool diagnosticBackgroundEnabled() const = 0;

    // Model scale relative to meters. For example, if model is drawn in mm,
    // scaleFactor is 0.001.
    virtual void            setModelScaleFactor     (double scaleFactor)    = 0;
    virtual double          modelScaleFactor        (void) const            = 0;
};

// The available filtering methods (kernels) used to combine samples into
// a pixel color.
//
typedef enum {
    krBox = 0,
    krTriangle,
    krGauss,
    krMitchell,
    krLanczos
} AcGiMrFilter;

// The available methods for computing ray-traced shadows.
// 
typedef enum {
    krSimple = 0,
    krSorted,
    krSegments
} AcGiMrShadowMode;

typedef enum {
    krOff = 0,
    krGrid,
    krPhoton,
    krSamples,
    krBSP
} AcGiMrDiagnosticMode;

typedef enum {
    krObject = 0,
    krWorld,
    krCamera
} AcGiMrDiagnosticGridMode;

typedef enum {
    krDensity = 0,
    krIrradiance
} AcGiMrDiagnosticPhotonMode;

typedef enum {
    krDepth = 0,
    krSize
} AcGiMrDiagnosticBSPMode;

typedef enum {
    krHilbert = 0,
    krSpiral,
    krLeftToRight,
    krRightToLeft,
    krTopToBottom,
    krBottomToTop
} AcGiMrTileOrder;

typedef enum {
    krAutomatic = 0,
    krLogarithmic
} AcGiMrExposureType;

typedef enum {
    krFinalGatherOff = 0,
    krFinalGatherOn,
    krFinalGatherAuto
} AcGiMrFinalGatheringMode;

typedef enum {
    krExportMIOff = 0,
    krExportMIWithRender,
    krExportMIOnly
} AcGiMrExportMIMode;

class ACDBCORE2D_PORT AcGiMentalRayRenderSettingsTraits : public AcGiRenderSettingsTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMentalRayRenderSettingsTraits);

    virtual void setSampling(int min, int max) = 0;
    virtual void sampling(int& min, int& max) const = 0;

    virtual void setSamplingFilter(AcGiMrFilter filter, double width, double height) = 0;
    virtual void SamplingFilter(AcGiMrFilter& filter, double& width, double& height) const = 0;

    virtual void setSamplingContrastColor(float r, float g, float b, float a) = 0;
    virtual void samplingContrastColor(float& r, float& g, float& b, float& a) const = 0;

    virtual void setShadowMode(AcGiMrShadowMode mode) = 0;
    virtual AcGiMrShadowMode shadowMode() const = 0;
    
    virtual void setShadowMapEnabled(bool enabled) = 0;
    virtual bool shadowMapEnabled() const = 0;
    
    virtual void setRayTraceEnabled(bool enabled) = 0;
    virtual bool rayTraceEnabled() const = 0;
    
    virtual void setRayTraceDepth(int reflection, int refraction, int sum) = 0;
    virtual void rayTraceDepth(int& reflection, int& refraction, int& sum) const = 0;

    virtual void setGlobalIlluminationEnabled(bool enabled) = 0;
    virtual bool globalIlluminationEnabled() const = 0;
    
    virtual void setGISampleCount(int num) = 0;
    virtual int giSampleCount() const = 0;
    
    virtual void setGISampleRadiusEnabled(bool enabled) = 0;
    virtual bool giSampleRadiusEnabled() const = 0;
    
    virtual void setGISampleRadius(double radius) = 0;
    virtual double giSampleRadius() const = 0;

    virtual void setGIPhotonsPerLight(int num) = 0;
    virtual int giPhotonsPerLight() const = 0;
    
    virtual void setPhotonTraceDepth(int reflection, int refraction, int sum) = 0;
    virtual void photonTraceDepth(int& reflection, int& refraction, int& sum) const = 0;
    
    virtual void setFinalGatheringEnabled(bool enabled) = 0;
    virtual bool finalGatheringEnabled() const = 0;
    
    virtual void setFGRayCount(int num) = 0;
    virtual int fgRayCount() const = 0;

    virtual void setFGRadiusState(bool bMin, bool bMax, bool bPixels) = 0;
    virtual void fgSampleRadiusState(bool& bMin, bool& bMax, bool& bPixels) = 0;
    
    virtual void setFGSampleRadius(double min, double max) = 0;
    virtual void fgSampleRadius(double& min, double& max) const = 0;
    
    virtual void setLightLuminanceScale(double luminance) = 0;
    virtual double lightLuminanceScale() const = 0;
    
    virtual void setDiagnosticMode(AcGiMrDiagnosticMode mode) = 0;
    virtual AcGiMrDiagnosticMode diagnosticMode() const = 0;

    virtual void setDiagnosticGridMode(AcGiMrDiagnosticGridMode mode, float fSize) = 0;
    virtual void diagnosticGridMode(AcGiMrDiagnosticGridMode& mode, float& fSize) const = 0;

    virtual void setDiagnosticPhotonMode(AcGiMrDiagnosticPhotonMode mode) = 0;
    virtual AcGiMrDiagnosticPhotonMode diagnosticPhotonMode() const = 0;
    
    virtual void setDiagnosticBSPMode(AcGiMrDiagnosticBSPMode mode) = 0;
    virtual AcGiMrDiagnosticBSPMode diagnosticBSPMode() const = 0;
    
    virtual void setExportMIEnabled(bool enabled) = 0;
    virtual bool exportMIEnabled() const = 0;
    
    virtual void setExportMIFileName(const ACHAR* miName) = 0;
    virtual const ACHAR* exportMIFileName() const = 0;

    virtual void setTileSize(int size) = 0;
    virtual int tileSize() const = 0;

    virtual void setTileOrder(AcGiMrTileOrder order) = 0;
    virtual AcGiMrTileOrder tileOrder() const = 0;

    virtual void setMemoryLimit(int limit) = 0;
    virtual int memoryLimit() const = 0;

    virtual void setEnergyMultiplier(float fScale) = 0;
    virtual float energyMultiplier() const = 0;

    virtual void setProgressMonitor(void* pMonitor) = 0;
    virtual const void* progressMonitor(void) const = 0;

    virtual void setExposureType(AcGiMrExposureType type) = 0;
    virtual AcGiMrExposureType exposureType() const = 0;

    virtual void setFinalGatheringMode(AcGiMrFinalGatheringMode mode) = 0;
    virtual AcGiMrFinalGatheringMode finalGatheringMode() const = 0;

    virtual void setShadowSamplingMultiplier(double multiplier) = 0;
    virtual double shadowSamplingMultiplier() const = 0;

    virtual void setExportMIMode(AcGiMrExportMIMode mode) = 0;
    virtual AcGiMrExportMIMode exportMIMode() const = 0;
};

/// <summary>
/// Render Quit Conditions
/// </summary>
typedef enum
{
    /// <summary>
    /// Use render iteration as a quit condition
    /// The corresponding render level value needs to be set
    /// </summary>
    krEQuitByRenderLevel = 0,
    /// <summary>
    /// Use render time as a quit condition
    /// The corresponding target render time needs to be set
    /// </summary>
    krEQuitByRenderTime
}AcGiQuitCondition;

/// <summary>
/// Lighting Mode.
/// </summary>
typedef enum
{
    /// <summary>
    /// Global illumination off.
    /// Glossy reflection and refraction off.
    /// Simplified strategy for reflections/refractions to reduce noise.
    /// The trade off is that reflections and refractions may be less accurate compared to the Basic and Advanced lighting modes.
    /// </summary>
    krESimplistic = 0,
    /// <summary>
    /// Global illumination (indirect diffuse lighting) on.
    /// Glossy reflection and refraction off.
    /// </summary>
    krEBasic,
    /// <summary>
    /// Global illumination (indirect diffuse lighting) on.
    /// Glossy reflection and refraction on.
    /// </summary>
    krEAdvanced
}AcGiLightingMode;

/// <summary>
/// Filter Type.
/// </summary>
typedef enum 
{
    /// <summary>
    /// Box filter type
    /// Default size: 1.0
    /// </summary>
    krEBox = 0,
    /// <summary>
    /// Triangle filter type
    /// Default size: 2.0
    /// </summary>
    krETriangle,
    /// <summary>
    /// Gaussian filter type
    /// Default size: 3.0
    /// </summary>
    krEGaussian,
    /// <summary>
    /// Lanczos filter type
    /// Default size: 4.0
    /// </summary>
    krELanczos,
    /// <summary>
    /// Mitchell filter type
    /// Default size: 4.0
    /// </summary>
    krEMitchell
}AcGiFilterType;

/// <summary>
/// Abstract interface class that controls all the rendering settings.
/// </summary>
class ACDBCORE2D_PORT AcGiRapidRTRenderSettingsTraits : public AcGiNonEntityTraits 
{
public:
    ACRX_DECLARE_MEMBERS(AcGiRapidRTRenderSettingsTraits);

    /// <summary>
    /// Two general options are provided to control the rendering quality. 
    /// One is by rendering time, the other by rendering level. 
    /// For either option, the bigger value set, the better quality we can get, which also means longer rendering time. 
    /// This function is to set the option.
    /// /summary>
    /// <param name="quitCondition">Set the quit condition that controls the rendering option, either by time or by level. </param>
    /// <returns>void</returns>
    virtual void setQuitCondition(AcGiQuitCondition quitCondition) = 0;
    /// <summary>Get the quit condition</summary>
    /// <returns>Return the quit condition</returns>
    virtual AcGiQuitCondition quitCondition() const = 0;

    /// <summary>
    /// If choosing to use the option of render time to control render quality, we can use this function to set the desired rendering time.
    /// </summary>
    /// <param name="renderTime">Desired render time to be set, which is by second. The range is from 1 minute to 1440 minutes.</param>
    /// <returns>void</returns>
    virtual void setDesiredRenderTime(int renderTime) = 0;
    /// <summary>Get the desired render time.</summary>
    /// <returns>Return the desired render time.</returns>
    virtual int desiredRenderTime() const = 0;

    /// <summary>If choosing to use the option of render level to control render quality, we can use this function to set the desired rendering level.</summary>
    /// <param name="renderLevel">Desired render level to be set. The range is from 1 to 50.</param>
    /// <returns>void</returns>
    virtual void setDesiredRenderLevel(int renderLevel) = 0;
    /// <summary>Get the desired render level.</summary>
    /// <returns>Return the desired render level.</returns>
    virtual int desiredRenderLevel() const = 0;

    /// <summary>
    /// Turn on basic lighting or advanced lighting according the lighting mode set. 
    /// Basic lighting uses ambient occlusion and a simpler model for ambient light and IBL. 
    /// Advanced lighting uses full global illumination and a more advanced model for ambient light and IBL.
    /// </summary>
    /// <param name="mode">Desired lighting mode to be set.</param>
    /// <returns>void</returns>
    virtual void setLightingMode(AcGiLightingMode mode) = 0;
    /// <summary>Get the lighting mode being set.</summary>
    /// <returns>Return the lighting mode being set.</returns>
    virtual AcGiLightingMode lightingMode() const = 0;

    /// <summary>
    /// Set the filter type applied to the image samples when super sampling. Different filter type favors different filter width / height.
    /// </summary>
    /// <param name="filterInfo">Filter type to be set.</param>
    /// <returns>void</returns>
    virtual void setFilterType(AcGiFilterType filterInfo) = 0;
    /// <summary>Get the current filter type.</summary>
    /// <returns>Return the current filter type.</returns>
    virtual AcGiFilterType filterType() const = 0;

    /// <summary>
    /// Sets the filter width. 1.0 means one pixel (image sample).
    /// Recommended default sizes: box = 1.0, triangle = 2.0, Gaussian = 3.0, Lanczos = 4.0, Mitchell = 4.0
    /// </summary>
    /// <param name="width">Filter width to be set.</param>
    /// <returns>void</returns>
    virtual void setFilterWidth(float width) = 0;
    /// <summary>Get the current filter width.</summary>
    /// <returns>Return the current filter width.</returns>
    virtual float filterWidth() const = 0;

    /// <summary>
    /// Sets the filter height. 1.0 means one pixel (image sample).
    /// Recommended default sizes: box = 1.0, triangle = 2.0, Gaussian = 3.0, Lanczos = 4.0, Mitchell = 4.0
    /// </summary>
    /// <param name="height">Filter height to be set.</param>
    /// <returns>void</returns>
    virtual void setFilterHeight(float height) = 0;
    /// <summary>
    /// Get the current filter height
    /// </summary>
    /// <returns>Current filter height</returns>
    virtual float filterHeight() const = 0;
};

/// <summary>
/// Container class for all tone operator parameters.
/// </summary>
///
class ACDBCORE2D_PORT AcGiToneOperatorParameters : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiToneOperatorParameters);

    AcGiToneOperatorParameters();
    virtual ~AcGiToneOperatorParameters();

    AcGiToneOperatorParameters& operator=(const AcGiToneOperatorParameters& params);
    bool operator==(const AcGiToneOperatorParameters& params) const;

    /// <summary>
    /// Indicates whether or not the tone operator is active.
    /// </summary>
    ///
    /// <param name="active">
    /// If true, the tone operator is active.
    /// </param>
    virtual void setIsActive(bool active);

    /// <summary>
    /// Is the tone operator active?
    /// </summary>
    ///
    /// <returns>
    /// True if the tone operator is active.
    /// </returns>
    virtual bool isActive() const;

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual void setChromaticAdaptation(bool enable);

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual bool chromaticAdaptation() const;
    
    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual void setColorDifferentiation(bool enable);

    /// <summary>
    /// Reserved for future use.
    /// </summary>
    virtual bool colorDifferentiation() const;

    /// <summary>
    /// Sets the reference white color
    /// </summary>
    /// <param name="color">Reference White</param>
    virtual void setWhiteColor(const AcCmColor& color);

    /// <summary>
    /// Gets the reference white color
    /// </summary>
    virtual AcCmColor whiteColor() const;
    
    /// <summary>
    /// Specifies if the background should be processed by exposure control at render time.
    /// </summary>
    ///
    /// <param name="processBG">
    /// Set to true to enable background processing, otherwise false.
    /// </param>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual void setProcessBackground(bool processBG);

    /// <summary>
    /// Is background processing enabled?
    /// </summary>
    ///
    /// <returns>
    /// True if background processing is enabled.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual bool processBackground() const;

    /// <summary>
    /// Sets the brightness for the tone operator.
    /// </summary>
    ///
    /// <param name="brightness">
    /// The brightness for the tone operator.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid brightness value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setBrightness(double brightness);

    /// <summary>
    /// The brightness for the tone operator.
    /// </summary>
    ///
    /// <returns>
    /// The brightness for the tone operator.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual double brightness() const;

    /// <summary>
    /// Sets the contrast for the tone operator.
    /// </summary>
    ///
    /// <param name="contrast">
    /// The contrast for the tone operator.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid contrast value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setContrast(double contrast);

    /// <summary>
    /// The contrast for the tone operator.
    /// </summary>
    ///
    /// <returns>
    /// The contrast for the tone operator.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual double contrast() const;

    /// <summary>
    /// Sets the mid tones for the tone operator.
    /// </summary>
    ///
    /// <param name="midTones">
    /// The mid tones for the tone operator.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid midtones value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setMidTones(double midTones);

    /// <summary>
    /// The mid tones for the tone operator.
    /// </summary>
    ///
    /// <returns>
    /// The mid tones for the tone operator.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual double midTones() const;
    
    /// <summary>
    /// The exterior daylight mode.
    /// </summary>
    enum ExteriorDaylightMode {
        /// <summary>
        /// Off.
        /// </summary>
        kDaylightOff = 0,
        /// <summary>
        /// On.
        /// </summary>
        kDaylightOn,
        /// <summary>
        /// Auto - key off of the sun/sky background status.
        /// </summary>
        kDaylightAuto
    };

    /// <summary>
    /// Indicates whether or not exterior daylight is enabled.
    /// </summary>
    ///
    /// <param name="mode">
    /// If kDaylightOff, daylight is disabled. If kDaylightOn, daylight is enabled.  If kDaylightAuto, exterior daylight is enabled if a sky background or a sun light is enabled.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid exterior daylight mode is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if the tone operator is active.
    /// </remarks>
    virtual bool setExteriorDaylight(ExteriorDaylightMode mode);

    /// <summary>
    /// Is exterior daylight enabled?
    /// </summary>
    ///
    /// <returns>
    /// True if exterior daylight is enabled.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if the tone operator is active.
    /// </remarks>
    virtual ExteriorDaylightMode exteriorDaylight() const;
    
    /// <summary>
    /// Copies member data from source object
    /// </summary>
    ///
    /// <returns>
    /// Acad::eOk if copy is successful
    /// </returns>
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

private:
    bool                    mbIsActive;
    bool                    mbChromaticAdaptation;
    bool                    mbColorDifferentiation;
    AcCmColor               mWhiteColor;
    bool                    mbProcessBackground;
    double                  mBrightness;
    double                  mContrast;
    double                  mMidTones;
    ExteriorDaylightMode    mExteriorDaylight;
};

/// <summary>
/// Container class for all photographic exposure parameters.
/// </summary>
/// <remarks>
/// Properties defined here used by RENDERENGINE=1. 
/// Base class properties used by RENDERENGINE=0.
/// </remarks>
class ACDBCORE2D_PORT AcGiPhotographicExposureParameters : public AcGiToneOperatorParameters
{
public:
    ACRX_DECLARE_MEMBERS(AcGiPhotographicExposureParameters);

    AcGiPhotographicExposureParameters();
    virtual ~AcGiPhotographicExposureParameters();

    AcGiPhotographicExposureParameters& operator=(const AcGiPhotographicExposureParameters& params);
    bool operator==(const AcGiPhotographicExposureParameters& params) const;
    /// <summary>
    /// Sets Exposure Value for photographic exposure parameters.
    /// This value is a combination of a camera's shutter speed (exposure time) and f-number (depth of field) 
    /// and determines the amount of motion blur in a scene.
    /// </summary>
    ///
    /// <param name="exposure">
    /// Exposure Value for photographic exposure parameters.
    /// </param>
    bool setExposure(double exposure);

    /// <summary>
    /// Gets Exposure for photographic exposure parameters.
    /// </summary>
    ///
    /// <returns>
    /// Exposure for photographic exposure parameters
    /// </returns>
    double exposure(void) const;

    /// <summary>
    /// Sets White Point for photographic exposure parameters in Kelvins
    /// Affects the chromaticity of a scene
    /// </summary>
    ///
    /// <param name="whitePoint">
    /// Temperature of White Point in Kelvins
    /// </param>
    bool setWhitePoint(double whitePoint);

    /// <summary>
    /// Gets White Point for photographic exposure parameters
    /// </summary>
    ///
    /// <returns>
    /// Temperature of White Point in Kelvins
    /// </returns>
    double whitePoint(void) const;

    /// <summary>
    /// Sets exact brightness and updates exposure calculated from brightness
    /// </summary>
    virtual bool setBrightness                  (double)                     override;

    /// <summary>
    /// Copies member data from source object
    /// </summary>
    ///
    /// <returns>
    /// Acad::eOk if copy is successful
    /// </returns>
    virtual Acad::ErrorStatus copyFrom          (const AcRxObject*)     override;

public:
    /// <summary>
    /// Converts EV to a calibrated Brightness value
    /// </summary>
    /// <param name="exp">Exposure Value</param>
    /// <returns>Brightness value</returns>
    static double convertExposureToBrightness  (double exp);
    /// <summary>
    /// Converts Brightness value to EV
    /// </summary>
    /// <param name="brt">Brightness Value</param>
    /// <returns>Exposure value</returns>
    static double convertBrightnessToExposure  (double brt);

private:
    double                    mExposure;
    double                    mWhitePoint;
};

#pragma pack (pop)
