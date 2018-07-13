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
// acgiLightTraits.h
//
//   AcRxObject
//     AcGiSubEntityTraits
//       AcGiDrawableTraits
//         AcGiNonEntityTraits
//
//           AcGiLightTraits
//             AcGiStandardLightTraits
//               AcGiPointLightTraits
//               AcGiSpotLightTraits
//               AcGiDistantLightTraits
//             AcGiPhotometricLightTraits
//     AcGiShadowParameters
//     AcGiLightAttenuation
//     AcGiSkyParameters
//
//
// DESCRIPTION:
//
// This API extends AcGi to support light and illumination definition.
// Light entities pass their illumination information along to the graphics
// system and renderer through the AcGiLightTraits interfaces.
//

#pragma once

#include "acgi.h"

#pragma pack (push, 8)


////////////////////////////////////////////////////////////////////////
// class AcGiLightTraits
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Parent class for interfaces passed to AcDbLight objects in the
/// implementation of setAttributes(). The light first down-casts the
/// traits class to the specific type, specified earlier in the addLight()
/// call. It then sets specific light properties.
///
/// This class derives (indirectly) from AcGiDrawableTraits, as that is what
/// is passed into AcGiDrawable::setAttributes().
///
/// Lights on frozen layers will not be processed; their light will not
/// illuminate the model.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class should not rely on any
/// default values.
/// </remarks>
///
class AcGiLightTraits : public AcGiNonEntityTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiLightTraits);

    /// <summary>
    /// Turns the light on or off in the viewport or render. If the light
    /// is off, the other properties here may simply be ignored. However,
    /// lights that are turned off may still "draw" graphics for display
    /// in the viewport.
    ///
    /// Lights on frozen layers are not processed at all, so your light
    /// object does not have to check that condition.
    /// </summary>
    ///
    /// <param name="on">
    /// If true, the light is "turned on".
    /// </param>
    virtual void setOn(bool on) = 0;

    /// <summary>
    /// Light on/off state.
    /// </summary>
    ///
    /// <returns>
    /// True if the light is on.
    /// </returns>
    virtual bool isOn() const = 0;
};

////////////////////////////////////////////////////////////////////////
// class AcGiShadowParameters
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Container class for all shadow-related light properties.
/// </summary>
///
class AcGiShadowParameters : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiShadowParameters);

    AcGiShadowParameters();
    virtual ~AcGiShadowParameters();

    bool operator==(const AcGiShadowParameters& params) const;

    /// <summary>
    /// Turns shadow casting from this light on and off.
    /// </summary>
    ///
    /// <param name="on">
    /// If true, this light casts shadows.
    /// </param>
    virtual void setShadowsOn(bool on);

    /// <summary>
    /// Does the light cast shadows?
    /// </summary>
    ///
    /// <returns>
    /// True if the light casts shadows.
    /// </returns>
    virtual bool shadowsOn() const;

    /// <summary>
    /// The method used to calculate shadows.
    /// </summary>
    enum ShadowType {
        /// <summary>
        /// Shadows are calculated using a ray-trace algorithm.
        /// </summary>
        kShadowsRayTraced = 0,
        /// <summary>
        /// Shadow maps are created for each light.
        /// </summary>
        kShadowMaps,
        /// <summary>
        /// The area-sampled shadow algorithm models the effect of
        /// extended light sources which typically exhibit penumbra.
        /// </summary>
        kAreaSampled
    };

    /// <summary>
    /// Sets the method used to calculate shadows cast by this light.
    /// </summary>
    ///
    /// <param name="typ">
    /// One of: kShadowsRayTraced, kShadowMaps
    /// </param>
    ///
    /// <remarks>
    /// When shadows are ray-traced, shadow map size and softness parameters
    /// are ignored.
    /// </remarks>
    virtual void setShadowType(ShadowType typ);

    /// <summary>
    /// The method used to calculate shadows cast by this light.
    /// </summary>
    ///
    /// <returns>
    /// One of: kShadowsRayTraced, kShadowMaps
    /// </returns>
    virtual ShadowType shadowType() const;

    /// <summary>
    /// Sets the shadow map size, in pixels. Larger numbers produce more 
    /// accurate shadows, but require more memory and take longer to render.
    /// </summary>
    ///
    /// <param name="sz">
    /// Valid values are 64, 128, 256, 512, 1024, 2048, and 4096.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid size is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual bool setShadowMapSize(Adesk::UInt16 sz);

    /// <summary>
    /// The size of the shadow map, in pixels.
    /// </summary>
    ///
    /// <returns>
    /// The size of the shadow map, in pixels.
    /// Should be one of: 64, 128, 256, 512, 1024, 2048, or 4096.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual Adesk::UInt16 shadowMapSize() const;

    /// <summary>
    /// Sets the softness (or fuzziness) of shadow-mapped shadows. The value
    /// represents the number of pixels at the edge of the shadow that are 
    /// blended into the underlying image.
    /// </summary>
    ///
    /// <param name="soft">
    /// The value can range from 1 to 10.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid softness value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual bool setShadowMapSoftness(Adesk::UInt8 soft);

    /// <summary>
    /// The softness (or fuzziness) of the edge of the shadow. The value
    /// represents the number of pixels at the edge of the shadow that are
    /// blended into the underlying image.
    /// </summary>
    ///
    /// <returns>
    /// The number of pixels at the edge of the shadow to blend.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kShadowMaps.
    /// </remarks>
    virtual Adesk::UInt8 shadowMapSoftness() const;

    /// <summary>
    /// Sets the number of shadow rays to shoot for the light.  This 
    /// controls the softness of sampled shadows.
    /// </summary>
    ///
    /// <param name="samples">
    /// The number of shadow rays to shoot for the light.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid sample size is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kAreaSampled.
    /// </remarks>
    virtual bool setShadowSamples(Adesk::UInt16 samples);

    /// <summary>
    /// The number of shadow rays to shoot for the light.
    /// </summary>
    ///
    /// <returns>
    /// The number of shadow rays to shoot for the light.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kAreaSampled.
    /// </remarks>
    virtual Adesk::UInt16 shadowSamples() const;

    /// <summary>
    /// Determines if the light shape is visible in the rendering.
    /// </summary>
    ///
    /// <param name="on">
    /// If true, the light shape will be visible in the rendering.
    /// </param>
    virtual void setShapeVisibility(bool visible);

    /// <summary>
    /// Is the light visible in the rendering?
    /// </summary>
    ///
    /// <returns>
    /// True if the light shape is visible in the rendering.
    /// </returns>
    virtual bool shapeVisibility() const;

    /// <summary>
    /// The shape of the extended light source.
    /// </summary>
    enum ExtendedLightShape {
        /// <summary>
        /// Linear lamps (communicated to mental ray as degenerate rectangles).
        /// </summary>
        kLinear = 0,
        /// <summary>
        /// Rectangular extended light source.
        /// </summary>
        kRectangle,
        /// <summary>
        /// Disk-shaped extended light source.
        /// </summary>
        kDisk,
        /// <summary>
        /// Cylindrical extended light source.
        /// </summary>
        kCylinder,
        /// <summary>
        /// Spherical extended light source.
        /// </summary>
        kSphere
    };

    /// <summary>
    /// Sets the shape of the extended light source.
    /// </summary>
    ///
    /// <param name="shape">
    /// One of: kRectangle, kDisk, kCylinder, kSphere, kLinear, kWeb
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid shape is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kAreaSampled.
    /// </remarks>
    virtual bool setExtendedLightShape(ExtendedLightShape shape);

    /// <summary>
    /// The shape of the extended light source.
    /// </summary>
    ///
    /// <returns>
    /// One of: kRectangle, kDisk, kCylinder, kSphere, kLinear, kWeb
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kAreaSampled.
    /// </remarks>
    virtual ExtendedLightShape extendedLightShape() const;

    /// <summary>
    /// Sets the length of the extended light source.
    /// </summary>
    ///
    /// <param name="length">
    /// The length of the extended light source.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid length is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kAreaSampled and
    /// extended light source shape is kLinear, kRectangle or kCylinder.
    /// </remarks>
    virtual bool setExtendedLightLength(double length);

    /// <summary>
    /// The length of the extended light source.
    /// </summary>
    ///
    /// <returns>
    /// The length of the extended light source.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kAreaSampled and extended 
    /// light source shape is kLinear, kRectangle or kCylinder.
    /// </remarks>
    virtual double extendedLightLength() const;

    /// <summary>
    /// Sets the width of the extended light source.
    /// </summary>
    ///
    /// <param name="width">
    /// The width of the extended light source.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid width is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kAreaSampled and
    /// extended light source shape is kRectangle.
    /// </remarks>
    virtual bool setExtendedLightWidth(double width);

    /// <summary>
    /// The width of the extended light source.
    /// </summary>
    ///
    /// <returns>
    /// The width of the extended light source.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kAreaSampled and
    /// extended light source shape is kRectangle.
    /// </remarks>
    virtual double extendedLightWidth() const;

    /// <summary>
    /// Sets the radius of the extended light source.
    /// </summary>
    ///
    /// <param name="radius">
    /// The radius of the extended light source.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid radius is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kAreaSampled and
    /// extended light source shape is kDisk, kCylinder or kSphere.
    /// </remarks>
    virtual bool setExtendedLightRadius(double radius);

    /// <summary>
    /// The radius of the extended light source.
    /// </summary>
    ///
    /// <returns>
    /// The radius of the extended light source.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kAreaSampled and
    /// extended light source shape is kDisk, kCylinder or kSphere.
    /// </remarks>
    virtual double extendedLightRadius() const;

protected:

    bool                mShadowsOn;
    ShadowType          mShadowType;
    Adesk::UInt16       mShadowMapSize;
    Adesk::UInt8        mShadowMapSoftness;
    Adesk::UInt16       mShadowSamples;
    bool                mbShapeVisibility;
    ExtendedLightShape  mExtLightShape;
    double              mExtLightLength;
    double              mExtLightWidth;
    double              mExtLightRadius;
};

////////////////////////////////////////////////////////////////////////
// class AcGiLightAttenuation
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Container class for light attenuation parameters.
/// </summary>
///
class AcGiLightAttenuation : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiLightAttenuation);

    AcGiLightAttenuation();
    virtual ~AcGiLightAttenuation();

    bool operator==(const AcGiLightAttenuation& atten) const;

    /// <summary>
    /// The type of attenuation, or decay, for this light. This only applies
    /// to point and spot lights. Distant lights always have no attenuation.
    /// </summary>
    enum AttenuationType {
        /// <summary>
        /// No attenuation; emitted light has the same brightness (intensity)
        /// regardless of the distance to the source.
        /// </summary>
        kNone = 0,
        /// <summary>
        /// Sets attenuation to be the inverse of the linear distance from the
        /// light. 
        /// </summary>
        kInverseLinear,
        /// <summary>
        /// Sets attenuation to be the inverse of the square of the distance
        /// from the light. 
        /// </summary>
        kInverseSquare
    };

    /// <summary>
    /// Sets the attenuation type for the light.
    /// </summary>
    ///
    /// <param name="typ">
    /// One of: kNone, kInverseLinear, kInverseSquare
    /// </param>
    virtual void setAttenuationType(AttenuationType typ);

    /// <summary>
    /// The attenuation type for the light.
    /// </summary>
    ///
    /// <returns>
    /// One of: kNone, kInverseLinear, kInverseSquare
    /// </returns>
    virtual AttenuationType attenuationType() const;

    /// <summary>
    /// Turns on and off application of any attenuation limits.
    /// </summary>
    ///
    /// <param name="on">
    /// If true, both start and end limits will be used.
    /// </param>
    virtual void setUseLimits(bool on);

    /// <summary>
    /// Are the start and end limits used by this light?
    /// </summary>
    ///
    /// <returns>
    /// True if start and end attenuation limits are used.
    /// </returns>
    virtual bool useLimits() const;

    /// <summary>
    /// Sets the distances (a range) from the light source where emitted light
    /// affects the model.
    /// </summary>
    ///
    /// <param name="startlim">
    /// The distance from the light source where light begins to affect the
    /// model; objects closer than this are not affected by the light.
    /// </param>
    /// <param name="endlim">
    /// The distance from the light source beyond which the light has no affect.
    /// </param>
    ///
    /// <remarks>
    /// Start limit must be less than end limit, and both numbers must
    /// greater than or equal to zero.
    /// </remarks>
    virtual void setLimits(double startlim, double endlim);

    /// <summary>
    /// The distance from the light source where light begins to affect the
    /// model; objects closer than this are not affected by the light.
    /// </summary>
    ///
    /// <returns>
    /// A distance.
    /// </returns>
    virtual double startLimit() const;

    /// <summary>
    /// The distance from the light source beyond which the light has no affect.
    /// </summary>
    ///
    /// <returns>
    /// A distance.
    /// </returns>
    virtual double endLimit() const;

private:
    AttenuationType mAttenType;
    bool            mUseAttenLimits;
    double          mAttenStartLimit;
    double          mAttenEndLimit;
};

////////////////////////////////////////////////////////////////////////
// class AcGiSkyParameters
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Container class for all sky-related sun properties.
/// </summary>
///
class AcGiSkyParameters : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiSkyParameters);

    AcGiSkyParameters();
    virtual ~AcGiSkyParameters();

    bool operator==(const AcGiSkyParameters& params) const;

    /// <summary>
    /// Enables computation of skylight illumination.
    /// </summary>
    ///
    /// <param name="enable">
    /// If true, skylight illumination will be computed.
    /// </param>
    void setIllumination(bool enable)   { return setIlluminationImp(enable); }

    /// <summary>
    /// Should skylight illumination be calculated?
    /// </summary>
    ///
    /// <returns>
    /// True if skylight illumination will be computed.
    /// </returns>
    bool illumination() const { return illuminationImp(); }

    /// <summary>
    /// Sets the intensity factor which determines the level of 
    /// non-physical modulation of skylight.
    /// </summary>
    ///
    /// <param name="intensity">
    /// The intensity factor for skylight.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid intensity factor is passed in.
    /// </returns>
    bool setIntensityFactor(double intensity)   { return setIntensityFactorImp(intensity); }

    /// <summary>
    /// The intensity factor which determines the level of 
    /// non-physical modulation of skylight.
    /// </summary>
    ///
    /// <returns>
    /// The instensity factor for skylight.
    /// </returns>
    double intensityFactor() const { return intensityFactorImp(); }

    /// <summary>
    /// Specifies turbidity or atmosphere.
    /// </summary>
    ///
    /// <param name="haze">
    /// The turbidity or atmosphere value.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid atmosphere value is passed in.
    /// </returns>
    bool setHaze(double haze) { return setHazeImp(haze); }

    /// <summary>
    /// The turbidity or atmosphere value.
    /// </summary>
    ///
    /// <returns>
    /// The turbidity or atmosphere value.
    /// </returns>
    double haze() const { return hazeImp(); }

    /// <summary>
    /// Sets the world-space height of the horizon plane.
    /// </summary>
    ///
    /// <param name="height">
    /// The world-space height of the horizon plane.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid height is passed in.
    /// </returns>
    bool setHorizonHeight(double height) { return setHorizonHeightImp(height); }

    /// <summary>
    /// The world-space height of the horizon plane.
    /// </summary>
    ///
    /// <returns>
    /// The world-space height of the horizon plane.
    /// </returns>
    double horizonHeight() const    { return horizonHeightImp(); }

    /// <summary>
    /// Sets the amount of blurring between ground plane and sky.
    /// </summary>
    ///
    /// <param name="blur">
    /// The amount of blurring between ground plane and sky.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid blur amount is passed in.
    /// </returns>
    bool setHorizonBlur(double blur) { return setHorizonBlurImp(blur); }

    /// <summary>
    /// The amount of blurring between ground plane and sky.
    /// </summary>
    ///
    /// <returns>
    /// The amount of blurring between ground plane and sky.
    /// </returns>
    double horizonBlur() const { return horizonBlurImp(); }

    /// <summary>
    /// Sets the color of the ground plane.
    /// </summary>
    ///
    /// <param name="color">
    /// The color of the ground plane. AcCmColor supports all color models
    /// within AutoCAD, including color book colors.
    /// </param>
    void setGroundColor(const AcCmColor& color) { return setGroundColorImp(color); }

    /// <summary>
    /// The color of the ground plane.
    /// </summary>
    ///
    /// <returns>
    /// The color of the ground plane.
    /// </returns>
    AcCmColor groundColor() const { return groundColorImp(); }

    /// <summary>
    /// Sets the color of the night sky.
    /// </summary>
    ///
    /// <param name="color">
    /// The color of the night sky. AcCmColor supports all color models
    /// within AutoCAD, including color book colors.
    /// </param>
    void setNightColor(const AcCmColor& color) { setNightColorImp(color); }

    /// <summary>
    /// The color of the night sky.
    /// </summary>
    ///
    /// <returns>
    /// The color of the night sky.
    /// </returns>
    AcCmColor nightColor() const    { return nightColorImp(); }

    /// <summary>
    /// Specifies whether aerial perspective is applied.
    /// </summary>
    ///
    /// <param name="apply">
    /// If true, aerial perspective is applied.
    /// </param>
    void setAerialPerspective(bool apply) { setAerialPerspectiveImp(apply); }

    /// <summary>
    /// Should aerial perspective be applied?
    /// </summary>
    ///
    /// <returns>
    /// True if aerial perspective is applied.
    /// </returns>
    bool aerialPerspective() const { return aerialPerspectiveImp(); }

    /// <summary>
    /// Sets the distance at which 10% haze occlusion results.
    /// </summary>
    ///
    /// <param name="distance">
    /// The distance at which 10% haze occlusion results.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid distance is passed in.
    /// </returns>
    bool setVisibilityDistance(double distance) { return setVisibilityDistanceImp(distance); }

    /// <summary>
    /// The distance at which 10% haze occlusion results.
    /// </summary>
    ///
    /// <returns>
    /// The distance at which 10% haze occlusion results.
    /// </returns>
    double visibilityDistance() const { return visibilityDistanceImp(); }

    /// <summary>
    /// Sets the scale of the sun disk (1.0 = correct size).
    /// </summary>
    ///
    /// <param name="scale">
    /// The scale of the sun disk (1.0 = correct size).
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid scale is passed in.
    /// </returns>
    bool setDiskScale(double scale) { return setDiskScaleImp(scale); }

    /// <summary>
    /// The scale of the sun disk (1.0 = correct size).
    /// </summary>
    ///
    /// <returns>
    /// The scale of the sun disk (1.0 = correct size).
    /// </returns>
    double diskScale() const { return diskScaleImp(); }

    /// <summary>
    /// Sets the intensity of the sun glow.
    /// </summary>
    ///
    /// <param name="intensity">
    /// The intensity of the sun glow.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid intensity value is passed in.
    /// </returns>
    bool setGlowIntensity (double intensity) { return setGlowIntensityImp(intensity); }

    /// <summary>
    /// The intensity of the sun glow.
    /// </summary>
    ///
    /// <returns>
    /// The intensity of the sun glow.
    /// </returns>
    double glowIntensity() const { return glowIntensityImp(); }

    /// <summary>
    /// Sets the intensity of the sun disk.
    /// </summary>
    ///
    /// <param name="intensity">
    /// The intensity of the sun disk.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid intensity value is passed in.
    /// </returns>
    bool setDiskIntensity(double intensity) { return setDiskIntensityImp(intensity); }

    /// <summary>
    /// The intensity of the sun disk.
    /// </summary>
    ///
    /// <returns>
    /// The intensity of the sun disk.
    /// </returns>
    double diskIntensity() const { return diskIntensityImp(); }

    /// <summary>
    /// Sets the number of samples to take on the solar disk.
    /// </summary>
    ///
    /// <param name="samples">
    /// The number of samples to take on the solar disk.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a valid sample size is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if shadow type is kAreaSampled.
    /// </remarks>
    bool setSolarDiskSamples(Adesk::UInt16 samples) { return setSolarDiskSamplesImp(samples); }

    /// <summary>
    /// The number of samples to take on the solar disk.
    /// </summary>
    ///
    /// <returns>
    /// The number of samples to take on the solar disk.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if shadow type is kAreaSampled.
    /// </remarks>
    Adesk::UInt16 solarDiskSamples() const { return solarDiskSamplesImp(); }

    /// <summary>
    /// For internal use only.
    /// </summary>
    bool setSunDirection(const AcGeVector3d& sundir) { return setSunDirectionImp(sundir); }

    /// <summary>
    /// Gets the direction (vector) of the sun's light rays.
    /// </summary>
    ///
    /// <returns>
    /// The direction vector of sunlight, from the Sun to the model.
    /// </returns>
    const AcGeVector3d& sunDirection() const { return sunDirectionImp(); }
    
    /// <summary>
    /// Sets the red-blue shift on the sky.  This provides control on the "redness" of the
    /// sky.  The default of 0.0 is physically accurate.  A minimum value of -1.0 will produce
    /// a extremely blue sky, whereas the maximum value of 1.0 will produce an extremely
    /// red sky.
    /// </summary>
    /// <returns>
    /// Returns true if the input value is in the valid range of -1.0 to 1.0.  Returns
    /// false otherwise.
    /// </returns>
    bool setRedBlueShift (double redBlueShift)  { return setRedBlueShiftImp(redBlueShift); }


    /// <summary>
    /// Returns the red-blue shift on the sky.  This provides control on the "redness" of the
    /// sky.  The default of 0.0 is physically accurate.  A minimum value of -1.0 will produce
    /// a extremely blue sky, whereas the maximum value of 1.0 will produce an extremely
    /// red sky.
    /// </summary>
    /// <returns>
    /// Returns the currently set value.
    /// </returns>
    double redBlueShift  (void) const           { return redBlueShiftImp(); }


    /// <summary>
    /// Artificially modifies the sky's saturation level.  The minimum value of 0.0 will produce
    /// a extreme of black and white whereas the maximum value of 2.0 will produce highly boosted
    /// saturation.
    /// </summary>
    /// <returns>
    /// Returns true if the input value is in the valid range of 0.0 to 2.0.  Returns
    /// false otherwise.
    /// </returns>
    bool setSaturation (double saturation)      { return setSaturationImp(saturation); }

    /// <summary>
    /// Returns the the sky's saturation level.  The minimum value of 0.0 will produce
    /// a extreme of black and white whereas the maximum value of 2.0 will produce highly boosted
    /// saturation.
    /// </summary>
    /// <returns>
    /// Returns the currently set value.
    /// </returns>
    double saturation (void) const              { return saturationImp(); }

protected:
    virtual void setIlluminationImp (bool enable);
    virtual bool illuminationImp (void) const;

    virtual bool setIntensityFactorImp (double intensity);
    virtual double intensityFactorImp () const;

    virtual bool setHazeImp (double haze);
    virtual double hazeImp (void) const;

    virtual bool setHorizonHeightImp        (double height);
    virtual double horizonHeightImp (void) const;

    virtual bool setHorizonBlurImp (double blur);
    virtual double horizonBlurImp () const;

    virtual void setGroundColorImp (const AcCmColor& color);
    virtual AcCmColor groundColorImp () const;

    virtual void setNightColorImp (const AcCmColor& color);
    virtual AcCmColor nightColorImp () const;

    virtual void setAerialPerspectiveImp (bool apply);
    virtual bool aerialPerspectiveImp () const;

    virtual bool setVisibilityDistanceImp (double distance);
    virtual double visibilityDistanceImp () const;

    virtual bool setDiskScaleImp (double scale);
    virtual double diskScaleImp () const;

    virtual bool setGlowIntensityImp (double intensity);
    virtual double glowIntensityImp () const;

    virtual bool setDiskIntensityImp (double intensity);
    virtual double diskIntensityImp () const;

    virtual bool setSolarDiskSamplesImp (Adesk::UInt16 samples);
    virtual Adesk::UInt16 solarDiskSamplesImp (void) const;

    virtual bool  setSunDirectionImp (const AcGeVector3d& sundir);
    virtual const AcGeVector3d& sunDirectionImp (void) const;

    virtual bool setRedBlueShiftImp  (double redBlueShift);
    virtual double  redBlueShiftImp (void) const;

    virtual bool setSaturationImp (double saturation);
    virtual double  saturationImp (void) const;

private:
    bool            mStatus;
    double          mIntensityFactor;
    double          mHaze;
    double          mHorizonHeight;
    double          mHorizonBlur;
    AcCmColor       mGroundColor;
    AcCmColor       mNightColor;
    bool            mAerialPerspective;
    double          mVisibilityDistance;
    double          mDiskScale;
    double          mGlowIntensity;
    double          mDiskIntensity;
    Adesk::UInt16   mSolarDiskSamples;
    AcGeVector3d    mSunDirection;
    double          mRedBlueShift;
    double          mSaturation;
};

////////////////////////////////////////////////////////////////////////
// class AcGiStandardLightTraits
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This intermediate class represents a standard, or non-photometric light.
/// It defines properties common to all non-photometric lights.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
///
class AcGiStandardLightTraits : public AcGiLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiStandardLightTraits);

    /// <summary>
    /// Sets the intensity of the light. Intensity must be greater than or equal
    /// to zero. A value of 0.0 turns the light off.
    /// </summary>
    ///
    /// <param name="inten">
    /// The intensity, or brightness, of the light. A value of 0.0 effectively
    /// turns the light off.
    /// </param>
    virtual void setIntensity(double inten) = 0;

    /// <summary>
    /// The intensity of the light.
    /// </summary>
    ///
    /// <returns>
    /// Light intensity. The value will always be greater than or equal to zero.
    /// </returns>
    virtual double intensity() const = 0;

    /// <summary>
    /// Sets the color of the light.
    /// </summary>
    ///
    /// <param name="color">
    /// The color of the emitted light. AcCmColor supports all color models
    /// within AutoCAD, including color book colors.
    /// </param>
    virtual void setLightColor(const AcCmColor& color) = 0;

    /// <summary>
    /// The color of the light.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of emitted light.
    /// </returns>
    virtual AcCmColor lightColor() const = 0;

    /// <summary>
    /// Sets the shadow parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// The AcGiShadowParameters object that defines the way shadows are cast from this light.
    /// </param>
    virtual void setShadowParameters(const AcGiShadowParameters& params) = 0;

    /// <summary>
    /// Provides access to shadow parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiShadowParameters object that will contain the current shadow 
    /// properties of this light.
    /// </param>
    virtual void shadowParameters(AcGiShadowParameters& params) const = 0;
};


////////////////////////////////////////////////////////////////////////
// class AcGiPointLightTraits
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class represents a point light source, whose light is emitted in all
/// directions.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
class AcGiPointLightTraits : public AcGiStandardLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiPointLightTraits);

    /// <summary>
    /// Sets the position of the light source. The coordinate space is defined
    /// by the current context.
    /// </summary>
    ///
    /// <param name="pos">
    /// The position of the light source.
    /// </param>
    virtual void setPosition(const AcGePoint3d& pos) = 0;

    /// <summary>
    /// The position of the light source, in the coordinate space of the
    /// current context.
    /// </summary>
    ///
    /// <returns>
    /// The position as an AcGePoint3d.
    /// </returns>
    virtual AcGePoint3d position() const = 0;

    /// <summary>
    /// Provides access to attenuation parameters for this light.
    /// </summary>
    ///
    /// <param name="atten">
    /// An AcGiLightAttenuation object that will contain the current attenuation
    /// parameters of this light. 
    /// </param>
    virtual void lightAttenuation(AcGiLightAttenuation& atten) const = 0;

    /// <summary>
    /// Sets the attenuation parameters of this point light.
    /// </summary>
    ///
    /// <param name="atten">
    /// The AcGiLightAttenuation object that defines the way light attenuates from this light.
    /// </param>
    virtual void setAttenuation(const AcGiLightAttenuation& atten) = 0;


    /// <summary>
    /// Sets the physical intensity of the light in candela.
    /// </summary>
    ///
    /// <param name="physicalIntensity">
    /// The physical intensity of the light in candela.
    /// </param>
    virtual void setPhysicalIntensity(double physicalIntensity) = 0;

    /// <summary>
    /// The physical intensity of the light in candela.
    /// </summary>
    ///
    /// <returns>
    /// The physical intensity of the light in candela.
    /// </returns>
    virtual double physicalIntensity() const = 0;
    
    /// <summary>
    /// Sets the corresponding RGB color for the light's lamp color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Input RGB value for the light's lamp color.
    /// </param>
    ///
    /// <remarks>
    /// This value can only be modified if lamp color type is kCustom.  If
    /// lamp color type is set to kKelvin or kPreset, the RGB color is
    /// predetermined; therefore, the RGB color cannot be modifed in
    /// either case.
    /// </remarks>
    virtual void setLampColor (const AcGiColorRGB& rgbColor) = 0;

    /// <summary>
    /// The RGB value for the light's lamp color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Output RGB value for the light's lamp color.
    /// </param>
    virtual void lampColor (AcGiColorRGB& rgbColor) const = 0;

    /// <summary>
    /// Indicates whether or not the light has a target.  If this is set to
    /// false, the targetLocation() is effectively ignored.
    /// </summary>
    ///
    /// <param name="bHasTarget">
    /// Indicates whether or not the light has a target.
    /// </param>
    virtual void setHasTarget (bool bHasTarget) = 0;

    /// <summary>
    /// Indicates whether or not the light has a target.  If this is set to
    /// false, the targetLocation() is effectively ignored.
    /// </summary>
    ///
    /// <returns>
    /// Whether or not the light has a target.
    /// </returns>
    virtual bool hasTarget (void) const = 0;

    /// <summary>
    /// Sets the location of the target point for the light. This, in
    /// combination with the position, determine the direction that the 
    /// light is "pointing". The coordinate space for this point is defined by
    /// the current context.
    /// </summary>
    ///
    /// <param name="loc">
    /// Location (point) of the light's target. It should not be exactly
    /// the same as the position.
    /// </param>
    virtual void setTargetLocation(const AcGePoint3d& loc) = 0;

    /// <summary>
    /// The location (position) towards which the light is pointing, in 
    /// the coordinate space of the current context.
    /// </summary>
    ///
    /// <returns>
    /// The location as an AcGePoint3d.
    /// </returns>
    virtual AcGePoint3d targetLocation() const = 0;
};


////////////////////////////////////////////////////////////////////////
// class AcGiSpotLightTraits
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class represents a spot light source, whose light is emitted in a
/// specific direction, and has an associated "light cone".
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
class AcGiSpotLightTraits : public AcGiStandardLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiSpotLightTraits);

    /// <summary>
    /// Sets the position of the light source. The coordinate space is defined
    /// by the current context.
    /// </summary>
    ///
    /// <param name="pos">
    /// The position of the light source.
    /// </param>
    virtual void setPosition(const AcGePoint3d& pos) = 0;

    /// <summary>
    /// The position of the light source, in the coordinate space of the
    /// current context.
    /// </summary>
    ///
    /// <returns>
    /// The position as an AcGePoint3d.
    /// </returns>
    virtual AcGePoint3d position() const = 0;

    /// <summary>
    /// Sets the location of the target point for a spot light. This, in
    /// combination with the position, determine the direction that the spot
    /// light is "pointing". The coordinate space for this point is defined by
    /// the current context.
    /// </summary>
    ///
    /// <param name="loc">
    /// Location (point) of the spot light's target. It should not be exactly
    /// the same as the position.
    /// </param>
    virtual void setTargetLocation(const AcGePoint3d& loc) = 0;

    /// <summary>
    /// The location (position) towards which the spot light is pointing, in 
    /// the coordinate space of the current context.
    /// </summary>
    ///
    /// <returns>
    /// The location as an AcGePoint3d.
    /// </returns>
    virtual AcGePoint3d targetLocation() const = 0;

    /// <summary>
    /// Sets the hotspot and falloff angles.
    ///
    /// The region between the hotspot and falloff angles is sometimes 
    /// referred to as the rapid decay area.
    ///
    /// The greater the difference between the hotspot and falloff angles,
    /// the softer the edge of the light beam. If the hotspot and falloff 
    /// angles are equal, the edge of the light beam is sharp. Both values
    /// can range from 0 to 160 degrees. You cannot set the hotspot angle
    /// to be greater than the falloff angle.
    /// </summary>
    ///
    /// <param name="hotspot">
    /// The hotspot cone angle, in radians. Defines the brightest part of the
    /// spot light beam. Must be smaller than or equal to the falloff.
    /// </param>
    /// <param name="falloff">
    /// The falloff cone angle, in radians. Defines the full cone of light. This
    /// is also known as the field angle. Must be larger than or equal to the
    /// hotspot.
    /// </param>
    ///
    /// <returns>
    /// Returns true if valid angles are passed in.
    /// </returns>
    virtual bool setHotspotAndFalloff(double hotspot, double falloff) = 0;

    /// <summary>
    /// The hotspot angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The hotspot angle, in radians.
    /// </returns>
    virtual double hotspot() const = 0;

    /// <summary>
    /// The falloff angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The falloff angle, in radians.
    /// </returns>
    virtual double falloff() const = 0;

    /// <summary>
    /// Provides access to attenuation parameters for this light.
    /// </summary>
    ///
    /// <param name="atten">
    /// An AcGiLightAttenuation object that will contain the current attenuation
    /// parameters of this light. 
    /// </param>
    virtual void lightAttenuation(AcGiLightAttenuation& atten) const = 0;

    /// <summary>
    /// Sets the attenuation parameters of this spot light.
    /// </summary>
    ///
    /// <param name="atten">
    /// The AcGiLightAttenuation object that defines the way light attenuates from this light.
    /// </param>
    virtual void setAttenuation(const AcGiLightAttenuation& atten) = 0;

    /// <summary>
    /// Sets the physical intensity of the light in candela.
    /// </summary>
    ///
    /// <param name="physicalIntensity">
    /// The physical intensity of the light in candela.
    /// </param>
    virtual void setPhysicalIntensity(double physicalIntensity) = 0;

    /// <summary>
    /// The physical intensity of the light in candela.
    /// </summary>
    ///
    /// <returns>
    /// The physical intensity of the light in candela.
    /// </returns>
    virtual double physicalIntensity() const = 0;
    
    /// <summary>
    /// Sets the corresponding RGB color for the light's lamp color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Input RGB value for the light's lamp color.
    /// </param>
    ///
    /// <remarks>
    /// This value can only be modified if lamp color type is kCustom.  If
    /// lamp color type is set to kKelvin or kPreset, the RGB color is
    /// predetermined; therefore, the RGB color cannot be modifed in
    /// either case.
    /// </remarks>
    virtual void setLampColor (const AcGiColorRGB& rgbColor) = 0;

    /// <summary>
    /// The RGB value for the light's lamp color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Output RGB value for the light's lamp color.
    /// </param>
    virtual void lampColor (AcGiColorRGB& rgbColor) const = 0;
};

////////////////////////////////////////////////////////////////////////
// class AcGiDistantLightTraits
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class represents a distant light source, whose light is emitted in
/// parallel rays, with an infinite distance between the light source and
/// the model.
/// </summary>
///
/// <remarks>
/// A light passing it's properties to this class shouldn't rely on any
/// default values.
/// </remarks>
class AcGiDistantLightTraits : public AcGiStandardLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiDistantLightTraits);

    /// <summary>
    /// Sets the direction the light rays travel in. This vector is in the
    /// direction of the light rays (from light to model).
    /// </summary>
    ///
    /// <param name="vec">
    /// The vector for the light rays.
    /// </param>
    ///
    /// <remarks>
    /// This same interface is used for the sun; all of the other parameters
    /// used to set the location of the sun, such as latitude, longitude, date,
    /// and time, boil down to a vector, which is sent to the graphics system
    /// through this method.
    /// </remarks>
    virtual void setLightDirection(const AcGeVector3d& vec) = 0;

    /// <summary>
    /// The direction (vector) that the light rays travel in.
    /// </summary>
    ///
    /// <returns>
    /// The direction, as a vector; the positive direction of this vector is
    /// from light to model.
    /// </returns>
    virtual AcGeVector3d lightDirection() const = 0;

    /// <summary>
    /// Tells the system to render this distant light as sunlight. Some
    /// rendering systems use special algorithms to render sunlight, as its
    /// intensity is so high.
    /// </summary>
    ///
    /// <param name="isSunlight">
    /// If true, this distant light may be rendered as sunlight.
    /// </param>
    virtual void setIsSunlight(bool isSunlight) = 0;

    /// <summary>
    /// Does this distant light represent sunlight?
    /// </summary>
    ///
    /// <returns>
    /// True if the light will be rendered as sunlight.
    /// </returns>
    virtual bool isSunlight() const = 0;

    /// <summary>
    /// Sets the physical intensity of the light in candela.
    /// </summary>
    ///
    /// <param name="physicalIntensity">
    /// The physical intensity of the light in candela.
    /// </param>
    virtual void setPhysicalIntensity(double physicalIntensity) = 0;

    /// <summary>
    /// The physical intensity of the light in candela.
    /// </summary>
    ///
    /// <returns>
    /// The physical intensity of the light in candela.
    /// </returns>
    virtual double physicalIntensity() const = 0;
    
    /// <summary>
    /// Sets the corresponding RGB color for the light's lamp color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Input RGB value for the light's lamp color.
    /// </param>
    ///
    /// <remarks>
    /// This value can only be modified if lamp color type is kCustom.  If
    /// lamp color type is set to kKelvin or kPreset, the RGB color is
    /// predetermined; therefore, the RGB color cannot be modifed in
    /// either case.
    /// </remarks>
    virtual void setLampColor (const AcGiColorRGB& rgbColor) = 0;

    /// <summary>
    /// The RGB value for the light's lamp color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Output RGB value for the light's lamp color.
    /// </param>
    virtual void lampColor (AcGiColorRGB& rgbColor) const = 0;

    /// <summary>
    /// Sets the sky parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiSkyParameters object that contains the sky properties of this light.
    /// </param>
    virtual void setSkyParameters(const AcGiSkyParameters& params) = 0;

    /// <summary>
    /// Provides access to sky parameters for this light.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiSkyParameters object that contains the sky properties of this light.
    /// </param>
    virtual void skyParameters(AcGiSkyParameters& params) const = 0;
};


////////////////////////////////////////////////////////////////////////
// class AcGiWebLightTraits
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Extended distant light interface allowing for photometric traits.
/// </summary>
///
class AcGiWebLightTraits : public AcGiPointLightTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiWebLightTraits);

    /// <summary>
    /// Types of web files
    /// </summary>
    enum WebFileType
    {
        /// <summary>
        /// Type C web file
        /// </summary>
        kTypeC = 1,

        /// <summary>
        /// Type B web file
        /// </summary>
        kTypeB = 2,

        /// <summary>
        /// Type A web file
        /// </summary>
        kTypeA = 3
    };

    /// <summary>
    /// Types of symmetry in the web file
    /// </summary>
    enum WebSymmetry
    {
        /// <summary>
        /// No symmetry
        /// </summary>
        kNoSymmetry = 0,
        
        /// <summary>
        /// Symmetric about the XZ plane
        /// </summary>
        kSingleSymmetry = 1,
        
        /// <summary>
        /// Symmetric about the XZ and YZ planes
        /// </summary>
        kDoubleSymmetry = 2,

        /// <summary>
        /// Symmetric about the Z axis
        /// </summary>
        kAxialSymmetry = 3,
    };

    /// <summary>
    /// Sets the path to the file containing the light's goniometric
    /// data (i.e. Illuminating Engineering Society or IES file).  Only 
    /// applies to photometric lights.
    /// </summary>
    ///
    /// <param name="webFile">
    /// Input ACHAR* const pointer to the light's IES file.
    /// </param>
    virtual void setWebFile(const ACHAR* webFile) = 0;
    
    /// <summary>
    /// The path to the file containing the light's goniometric
    /// data (i.e. Illuminating Engineering Society or IES file).
    /// </summary>
    ///
    /// <param name="webFile">
    /// Output ACHAR* const pointer to the light's IES file.
    /// </param>
    virtual void webFile(AcString& webFile) const = 0;

    /// <summary>
    /// Sets the rotation offset (specified in XYZ Euler angles) used to 
    /// orient the goniometric data relative to the light orientation.
    /// </summary>
    ///
    /// <param name="rotation">
    /// Input rotation offset specified in XYZ Euler angles.
    /// </param>
    virtual void setWebRotation(AcGeVector3d rotation) = 0;
    
    /// <summary>
    /// The rotation offset (specified in XYZ Euler angles) used to 
    /// orient the goniometric data relative to the light orientation.
    /// </summary>
    ///
    /// <param name="rotation">
    /// Output rotation offset specified in XYZ Euler angles.
    /// </param>
    virtual void webRotation(AcGeVector3d& rotation) const = 0;

    /// <summary>
    /// Explicitly set the flux value in lumens for the web light.
    /// </summary>
    ///
    /// <param name="flux">
    /// The explicit flux value in lumens for the web light.
    /// </param>
    virtual void setWebFlux(double flux) const = 0;

    /// <summary>
    /// Returns the flux value in lumens set for the web light.
    /// </summary>
    ///
    /// <returns>
    /// The flux value set for the web light in lumens.
    /// </returns>
    virtual double webFlux() const = 0;

    /// <summary>
    /// Sets the type of web file which was set by setWebFile().
    /// </summary>
    ///
    /// <param name="type">
    /// The type of the web file specified by setWebFile().
    /// </param>
    virtual void setWebFileType (WebFileType type) = 0;

    /// <summary>
    /// Returns the type of web file.
    /// </summary>
    ///
    /// <returns>
    /// The type of web file.
    /// </returns>
    virtual WebFileType webFileType (void) const = 0;

    /// <summary>
    /// Sets the symmetry of web file which was set by setWebFile().
    /// </summary>
    ///
    /// <param name="symmetry">
    /// The symmetry of the web file specified by setWebFile().
    /// </param>
    virtual void setWebSymmetry (WebSymmetry symmetry) = 0;
    
    /// <summary>
    /// Returns the type of symmetry in the web file.
    /// </summary>
    ///
    /// <returns>
    /// The type of symmetry in the web file.
    /// </returns>
    virtual WebSymmetry webSymmetry (void) const = 0;

    /// <summary>
    /// This method sets a flag to indicate that the IES file based web light is a bilaterally symmetric luminaire
    /// that exhibits symmetry about the 90 to 270 degree plane.  In this case, in the corresponding IES file, 
    /// the first value for the horizontal angle will be 90 degrees and the last value for the horizontal angle
    /// will be 270 degrees.  This method can be used to establish the web light as having this characteristic, 
    /// such that any special processing that should apply to this type of web light can be conditioned upon this
    /// flag.  For more information, consult the following publication, which describes the IES file format 
    /// standard in full:
    /// 
    /// IESNA LM-63-95,
    /// IESNA Standard File Format for Electronic Transfer of Photometric Data,
    /// By the IESNA (Illuminating Engineering Socety of North America) Computer Committee.
    /// </summary>
    ///
    /// <param name="symmetry">
    /// The value of the horizontal angle 90 to 270 flag for the web file 
    /// specified by setWebFile().
    /// </param>
    virtual void setWebHorzAng90to270 (bool bIs90to270) = 0;
    
    /// <summary>
    /// Returns whether the horizontal angle 90 to 270 flag is set.
    /// </summary>
    ///
    /// <returns>
    /// The setting of the horizontal angle 90 to 270 flag.
    /// </returns>
    virtual bool webHorzAng90to270 (void) const = 0;
};

#pragma pack (pop)
