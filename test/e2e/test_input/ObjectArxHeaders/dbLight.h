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
//-----------------------------------------------------------------------------
//----- AcDbLight.h : Declaration of the AcDbLight class
//-----------------------------------------------------------------------------
// DESCRIPTION:
//
// This API extends AcDb to support creation of the light objects (SpotLight, PointLight, and the DistantLight)

//   AcDbEntity
//      AcDbLight
//          AcDbPointLight
//          AcDbSpotLight
//          AcDbDistantLight


#pragma once
#include "dbmain.h"
#include "dbents.h"
#pragma warning( disable: 4275 4251 )
#ifdef SCENEOE
#define LIGHTDLLIMPEXP __declspec(dllexport)
#else
//----- Note: we don't use __declspec(dllimport) here, because of the
//----- "local vtable" problem with msvc. If you use __declspec(dllimport),
//----- then, when a client dll does a new on the class, the object's
//----- vtable pointer points to a vtable allocated in that client
//----- dll. If the client dll then passes the object to another dll,
//----- and the client dll is then unloaded, the vtable becomes invalid
//----- and any virtual calls on the object will access invalid memory.
//-----
//----- By not using __declspec(dllimport), we guarantee that the
//----- vtable is allocated in the server dll during the ctor and the
//----- client dll does not overwrite the vtable pointer after calling
//----- the ctor. And, since we expect the server dll to remain in
//----- memory indefinitely, there is no problem with vtables unexpectedly
//----- going away.
#define LIGHTDLLIMPEXP
#endif

#include "AcGiLightTraits.h"
//-----------------------------------------------------------------------------

//forward declaration of the imp class
class AcDbImpLight;

/// <summary>
/// Container for all properties relating to a generic light.
/// A dictionary of these objects is resident in the database, in the named
/// object dictionary as ACAD_LIGHTS.  They are indexed by the name
/// of the setting objects.  In the user interface, the contents of this
/// dictionary correspond to user-defined light properties (displayed on a
/// property palette accessible by selection of the light using a variety of
/// methods.
/// </summary>
class LIGHTDLLIMPEXP AcDbLight : public AcDbEntity
{
public:
    ACRX_DECLARE_MEMBERS(AcDbLight);
    
private:
    static Adesk::UInt32 kCurrentVersionNumber ;
public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbLight ();
    /// <summary>
    /// Destructor.
    /// </summary>
    ~AcDbLight();

    virtual Acad::ErrorStatus subClose() override;

    //----- AcDbEntity protocols
    //- Dwg Filing protocol
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler *pFiler) const override;
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler *pFiler) override;

    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;

    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

    virtual Acad::ErrorStatus decomposeForSave(
            AcDb::AcDbDwgVersion ver,
            AcDbObject*& replaceObj, 
            AcDbObjectId& replaceId, 
            Adesk::Boolean& exchangeXData) override;

    //----- AcDbEntity protocols
    //- Graphics protocol
    virtual AcGiDrawable::DrawableType    drawableType() const override;
    virtual bool castShadows() const override;
    virtual void setCastShadows(bool newVal) override;
    virtual bool receiveShadows() const override;
    virtual void setReceiveShadows(bool newVal) override;

    virtual Acad::ErrorStatus copyFrom (const AcRxObject* other) override;

    /// <summary>
    /// Gets the name of the Light object.
    /// </summary>
    ///
    /// <returns>
    /// Returns the name of the light object.
    /// </returns>
    virtual const AcString& name() const;

    /// <summary>
    /// Sets the name of the light object.
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the light object.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the name is valid.
    /// </returns>
    virtual Acad::ErrorStatus setName(const AcString & name);

    /// <summary>
    /// Gets the type of Light object.
    /// </summary>
    ///
    /// <returns>
    /// Returns the type of the light object. Possible values are: SpotLight, PointLight and DistantLight.
    /// </returns>
    virtual AcGiDrawable::DrawableType lightType() const;

    /// <summary>
    /// Sets the type of the light object.
    /// </summary>
    ///
    /// <param name="type">
    /// Light object type.  Possible choices are: SpotLight, PointLight and DistantLight.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the type is valid.
    /// </returns>
    virtual Acad::ErrorStatus setLightType(AcGiDrawable::DrawableType type);

    /// <summary>
    /// Gets the Light on/off state.
    /// </summary>
    ///
    /// <returns>
    /// True if the light is on.
    /// </returns>
    virtual  bool isOn() const;

    /// <summary>
    /// Sets whether the Light is On/Off.
    /// </summary>
    ///
    /// <param name="value">
    /// If true, the light is on.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk.
    /// </returns>
    virtual Acad::ErrorStatus setOn(bool value);

    /// <summary>
    /// Gets the plottable state of the light.
    /// </summary>
    ///
    /// <returns>
    /// True if the light is plottable.
    /// </returns>
    virtual bool isPlottable() const;

    /// <summary>
    /// Sets the plottable state of the light.
    /// </summary>
    ///
    /// <param name="plot">
    /// If true, the light is plottable.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk.
    /// </returns>
    virtual Acad::ErrorStatus setIsPlottable(bool plot);

    /// <summary>
    /// Gets the emitted color of the light.
    /// </summary>
    ///
    /// <returns>
    /// The light color.
    /// </returns>  
    virtual const AcCmColor& lightColor() const;

    /// <summary>
    /// Sets the emitted light color.
    /// </summary>
    ///
    /// <param name="color">
    /// The color of the emitted light.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the color is valid.
    /// </returns>
    virtual Acad::ErrorStatus setLightColor(const AcCmColor& color);
    
    
    /// <summary>
    /// Gets the light intensity.
    /// </summary>
    ///
    /// <returns>
    /// The light intensity.  A value of 0.0 indicates 
    /// that the light is off. 
    /// </returns>
    virtual double intensity() const;

    /// <summary>
    /// Sets the light intensity.
    /// </summary>
    /// <param name="intensity">
    /// The intensity of the light. A value of 0.0 
    /// turns the light off.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid intensity value is passed in.
    /// </returns>
    virtual Acad::ErrorStatus setIntensity(double intensity);


    /// <summary>
    /// Sets the light attenuation:attenuation type, use limits, start limits, end limits
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if the attenuation parameters are valid.
    /// </returns>
    virtual void setLightAttenuation(const AcGiLightAttenuation& params);

    /// <summary>
    /// Gets the light attenuation:attenuation type, use limits, start limits, end limits
    /// </summary>
    ///
    /// <returns>
    /// The light attenuation:attenuation type, use limits, start limits, end limits
    /// </returns>
    virtual const AcGiLightAttenuation& lightAttenuation() const;

    /// <summary>
    /// Sets the position of the light source. The coordinate space is defined
    /// by the current context.
    /// </summary>
    ///
    /// <param name="pos">
    /// Sets the position of the light source.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the operation is successful.
    /// </returns>
    virtual Acad::ErrorStatus setPosition(const AcGePoint3d& pos);

    /// <summary>
    /// Gets the position of the light source, in the coordinate space of the
    /// current context. (WCS)
    /// </summary>
    ///
    /// <returns>
    /// The light source position.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot and point light types only.
    /// </remarks>
    virtual const AcGePoint3d& position() const;
    
    /// <summary>
    /// Gets the position of the light target location, in the coordinate space of the
    /// current context. (WCS)
    /// </summary>
    ///
    /// <returns>
    /// The light target position.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual const AcGePoint3d& targetLocation() const;

    /// <summary>
    /// Sets the position of the light target location, in the coordinate space of the
    /// current context. (WCS)
    /// </summary>
    ///
    /// <returns>
    /// Acad::eOk if the operation is successful.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual Acad::ErrorStatus setTargetLocation(const AcGePoint3d& newVal);
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
    /// Returns Acad::eOk always.
    /// Note that the method automatically adjusts invalid values for the hotspot and falloff angles.
    /// See Remarks for details.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.  
    /// The method automatically adjusts the hotspot and falloff angle to be within acceptable ranges as follows:
    ///
    /// If new Hotspot angle != current Hotspot Angle and new Hotspot >= current Falloff, new Falloff angle is changed to (new Hotspot + 1 degree)
    /// If new Falloff angle != current Falloff Angle and new Falloff <= current Hotspot, new hotspot angle is changed to (new Falloff - 1 degree) 
    /// If new Hotspot Angle > 159 degrees, it is set to 159 degrees.
    /// If new Falloff Angle > 160 degrees, it is set to 160 degrees.
    /// If new Hotspot Angle < 0 degrees, it is set to 0 degrees.
    /// If new Falloff Angle < 1 degree, it is set to 1 degrees.
    ///
    /// Note that all checks (and any adjustments) are executed in sequence during every call to the method.


    /// </remarks>
    virtual Acad::ErrorStatus setHotspotAndFalloff(double hotspot, double falloff);

    /// <summary>
    /// Gets the hotspot angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The hotspot angle, in radians.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual double hotspotAngle() const;
    
    /// <summary>
    /// The falloff angle of this spot light.
    /// </summary>
    ///
    /// <returns>
    /// The falloff angle, in radians.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for spot light type only.
    /// </remarks>
    virtual double falloffAngle() const;

    /// <summary>
    /// Gets the direction (vector) that the rays of a distant light travel in.
    /// </summary>
    ///
    /// <returns>
    /// The direction, as a vector; the positive direction of this vector is
    /// from light to object.
    /// </returns>
    ///
    /// <remarks>
    /// Valid for distant light type only.
    /// </remarks>
    virtual const AcGeVector3d& lightDirection() const;

    /// <summary>
    /// Sets the direction the light rays of a distant light travel in. This vector is in the
    /// direction of the light rays (from light to object).
    /// </summary>
    ///
    /// <param name="lightvec">
    /// The vector for the light rays.
    /// </param>
    ///
    /// <remarks>
    /// Valid for distant light type only.
    /// </remarks>
    virtual Acad::ErrorStatus setLightDirection(const AcGeVector3d& lightvec);
    
    /// <summary>
    /// The physical intensity method.
    /// </summary>
    enum PhysicalIntensityMethod {
        /// <summary>
        /// Peak intensity.
        /// </summary>
        kPeakIntensity = 0,
        /// <summary>
        /// Flux.
        /// </summary>
        kFlux,
        /// <summary>
        /// Illuminance.
        /// </summary>
        kIlluminance
    };

    /// <summary>
    /// Gets the physical intensity method of the light.  This indicates
    /// how the physical intensity of the light is specified, either 
    /// by peak intensity, flux, or illuminance.
    /// </summary>
    ///
    /// <returns>
    /// The physical intensity method of the light.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    AcDbLight::PhysicalIntensityMethod physicalIntensityMethod() const;

    /// <summary>
    /// Sets the physical intensity method of the light.  This indicates
    /// how the physical intensity of the light is specified, either 
    /// by peak intensity, flux, or illuminance.
    /// </summary>
    ///
    /// <param name="metohd">
    /// The physical intensity method of the light.
    /// </param>
    ///
    /// <returns>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if light type is kWebLight.
    /// </remarks>
    Acad::ErrorStatus setPhysicalIntensityMethod(AcDbLight::PhysicalIntensityMethod method);

    /// <summary>
    /// Gets the physical intensity of the light.  The units are based on
    /// the physical intensity method (i.e. candela if kPeakIntensity,
    /// lumen if kFlux, lux if kIlluminance).
    /// </summary>
    ///
    /// <returns>
    /// The physical intensity of the light.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    double physicalIntensity() const;
    
    /// <summary>
    /// Sets the physical intensity of the light.  The units are based on
    /// the physical intensity method (i.e. candela if kPeakIntensity,
    /// lumen if kFlux, lux if kIlluminance).
    /// </summary>
    ///
    /// <param name="physicalIntensity">
    /// The physical intensity of the light.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid physcial intensity value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus setPhysicalIntensity(double physicalIntensity);

    /// <summary>
    /// Gets the illuminance distance of the light.
    /// </summary>
    ///
    /// <returns>
    /// The illuminance distance of the light.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International) and
    /// physcial intensity method is kIlluminance.
    /// </remarks>
    double illuminanceDistance() const;

    /// <summary>
    /// Sets the illuminance distance of the light.
    /// </summary>
    ///
    /// <param name="distance">
    /// The illuminance distance of the light.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid illuminance distance value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International) and
    /// physcial intensity method is kIlluminance.
    /// </remarks>
    Acad::ErrorStatus setIlluminanceDistance(double distance);

    /// <summary>
    /// The lamp color type of the light.
    /// </summary>
    enum LampColorType {
        /// <summary>
        /// Color specified as a Kelvin color temperature.
        /// </summary>
        kKelvin = 0,
        /// <summary>
        /// Color specified as a preset lamp color.
        /// </summary>
        kPreset
    };

    /// <summary>
    /// Gets the lamp color type of the light.  This indicates how the lamp
    /// color of the light is specified, either as a Kelvin color temperature
    /// or a preset lamp color.
    /// </summary>
    ///
    /// <returns>
    /// The lamp color type of the light.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    AcDbLight::LampColorType lampColorType() const;

    /// <summary>
    /// Sets the lamp color type of the light.  This indicates how the lamp
    /// color of the light is specified, either as a Kelvin color temperature
    /// or a preset lamp color.
    /// </summary>
    ///
    /// <param name="colorType">
    /// The lamp color type of the light.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid color type value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus setLampColorType(AcDbLight::LampColorType colorType);
    
    /// <summary>
    /// Gets the Kelvin color tempature of the light.
    /// </summary>
    ///
    /// <returns>
    /// The Kelvin color temperature of the light.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International) and 
    /// lamp color type is kKelvin.
    /// </remarks>
    double lampColorTemp() const;

    /// <summary>
    /// Sets the Kelvin color tempature of the light.
    /// </summary>
    ///
    /// <param name="colorTemp">
    /// The Kelvin color temperature of the light.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid color temperature value is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International) and 
    /// lamp color type is kKelvin.
    /// </remarks>
    Acad::ErrorStatus setLampColorTemp(double colorTemp);
    
    /// <summary>
    /// The preset lamp color of the light.
    /// </summary>
    enum LampColorPreset {
        /// <summary>
        /// D65White lamp color.
        /// </summary>
        kD65White = 0,
        /// <summary>
        /// Fluorescent lamp color.
        /// </summary>
        kFluorescent,
        /// <summary>
        /// Cool White lamp color.
        /// </summary>
        kCoolWhite,
        /// <summary>
        /// White Fluorescent lamp color.
        /// </summary>
        kWhiteFluorescent,
        /// <summary>
        /// Daylight Fluorescent lamp color.
        /// </summary>
        kDaylightFluorescent,
        /// <summary>
        /// Incandescent lamp color.
        /// </summary>
        kIncandescent,
        /// <summary>
        /// Xenon lamp color.
        /// </summary>
        kXenon,
        /// <summary>
        /// Halogen lamp color.
        /// </summary>
        kHalogen,
        /// <summary>
        /// Quartz lamp color.
        /// </summary>
        kQuartz,
        /// <summary>
        /// Metal Halide lamp color.
        /// </summary>
        kMetalHalide,
        /// <summary>
        /// Mercury lamp color.
        /// </summary>
        kMercury,
        /// <summary>
        /// Phosphor Mercury lamp color.
        /// </summary>
        kPhosphorMercury,
        /// <summary>
        /// High Pressure Sodium lamp color.
        /// </summary>
        kHighPressureSodium,
        /// <summary>
        /// Low Pressure Sodium lamp color.
        /// </summary>
        kLowPressureSodium,
        /// <summary>
        /// Custom lamp color.
        /// </summary>
        kCustom
    };

    /// <summary>
    /// Gets the preset lamp color of the light.
    /// </summary>
    ///
    /// <returns>
    /// The preset lamp color of the light.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International) and
    /// lamp color type is kPreset.
    /// </remarks>
    AcDbLight::LampColorPreset lampColorPreset() const;

    /// <summary>
    /// Sets the preset lamp color of the light.
    /// </summary>
    ///
    /// <param name="colorPreset">
    /// The preset lamp color of the light.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid AcDbLight::ColorPreset enum value is 
    /// passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International) and
    /// lamp color type is kPreset.
    /// </remarks>
    Acad::ErrorStatus setLampColorPreset(AcDbLight::LampColorPreset colorPreset);
    
    /// <summary>
    /// Gets the RGB value for the light's lamp color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Output RGB value for the light's lamp color.
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the lamp color information 
    /// could not be retrieved.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus lampColorRGB(AcGiColorRGB& rgbColor) const;

    // <summary>
    /// Sets the corresponding RGB color for the light's preset lamp color.  
    /// This value only applies if the light's color type is ColorType::kPreset.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Input RGB value for the light's lamp color.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid RGB color is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International) and
    /// lamp color type is kCustom.  If lamp color type is set to kKelvin or 
    /// kPreset, the RGB color is predetermined; therefore, the RGB color 
    /// cannot be modifed in either case.
    /// </remarks>
    Acad::ErrorStatus setLampColorRGB(AcGiColorRGB rgbColor);
    
    /// <summary>
    /// Gets the final color of the light.  This is determined by a
    /// combination of the Lamp color and the Filter Color.
    /// </summary>
    ///
    /// <param name="rgbColor">
    /// Output RGB value for the light's final color, where x is red[0,1],
    /// y is green[0,1] and z is blue[0,1].
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the light's color 
    /// information could not be retrieved.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus resultingColor(AcCmColor& rgbColor) const;

    /// <summary>
    /// Gets the path to the file containing the light's goniometric
    /// data (e.g. Illuminating Engineering Society or IES file).
    /// </summary>
    ///
    /// <param name="webFile">
    /// Output string to the light's web file.
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the web file information 
    /// could not be retrieved.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus webFile(AcString& webFile) const;

    /// <summary>
    /// Sets the path to the file containing the light's goniometric
    /// data (e.g. Illuminating Engineering Society or IES file).
    /// </summary>
    ///
    /// <param name="webFile">
    /// Input ACHAR* const pointer to the light's web file.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid web file path is passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus setWebFile(const ACHAR* webFile);
    
    /// <summary>
    /// Gets the rotation offset (specified in XYZ Euler angles) used to 
    /// orient the goniometric data relative to the light orientation.
    /// </summary>
    ///
    /// <param name="rotation">
    /// Output rotation offset specified in XYZ Euler angles.
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the web rotation information 
    /// could not be retrieved.
    /// </returns>
    ///
    /// <remarks>
    /// Only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus webRotation(AcGeVector3d& rotation) const;

    /// <summary>
    /// Sets the rotation offset (specified in XYZ Euler angles) used to 
    /// orient the goniometric data relative to the light orientation.
    /// </summary>
    ///
    /// <param name="rotation">
    /// Input rotation offset specified in XYZ Euler angles.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if a valid rotation angles are passed in.
    /// </returns>
    ///
    /// <remarks>
    /// This value only applies if LIGHTINGUNITS is set to photometric
    /// lighting units (i.e. 1 for American or 2 for International).
    /// </remarks>
    Acad::ErrorStatus setWebRotation(AcGeVector3d rotation);

    /// <summary>
    /// Is a target grip displayed for orienting the light?
    /// </summary>
    ///
    /// <returns>
    /// True if the light displays a target grip.
    /// </returns>
    bool hasTarget() const;
    
    /// <summary>
    /// Determines if the light displays a target grip for orienting
    /// the light.
    /// </summary>
    ///
    /// <param name="hasTarget">
    /// If true, the light will display a target grip.
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the hasTarget information 
    /// could not be set.
    /// </returns>
    Acad::ErrorStatus setHasTarget(bool hasTarget);

    /// <summary>
    /// Gets the shadow parameters:shadow type, mapsize, softness, on/off,
    /// area-sampled shadow parameters
    /// </summary>
    ///
    /// <param name="params">
    /// Output shadow parameters:shadow type, mapsize, softness, on/off,
    /// area-sampled shadow parameters
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the shadow parameter information 
    /// could not be retrieved.
    /// </returns>
    Acad::ErrorStatus shadowParameters(AcGiShadowParameters& params) const;

    /// <summary>
    /// Sets the shadow parameters: shadows on/off, shadow type, mapsize, softness,
    /// area-sampled shadow parameters
    /// </summary>
    ///
    /// <param name="params">
    /// Input shadow parameters:shadow type, mapsize, softness, on/off,
    /// area-sampled shadow parameters
    /// </param>
    ///
    /// <returns>
    /// Returns eOk on success. Returns an error if the shadow parameter information 
    /// could not be set, or if any of the values passed in are invalid.
    /// </returns>
    Acad::ErrorStatus setShadowParameters(const AcGiShadowParameters& params);

    /// <summary>
    /// Glyph Display type
    /// </summary>
    enum GlyphDisplayType {
        /// <summary>
        /// Auto. 
        /// </summary>
        kGlyphDisplayAuto = 0,
        /// <summary>
        /// On.
        /// </summary>
        kGlyphDisplayOn,
        /// <summary>
        /// Off.
        /// </summary>
        kGlyphDisplayOff
    };
    
    /// <summary>
    /// Gets the display state of the light glyph.
    /// </summary>
    ///
    /// <returns>
    /// Glyph display type.
    /// </returns>
    GlyphDisplayType glyphDisplay() const;

    /// <summary>
    /// Sets the display state of the light glyph.
    /// </summary>
    ///
    /// <param name="type">
    /// The type of the display state of the light glyph.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk.
    /// </returns>
    Acad::ErrorStatus setGlyphDisplay(GlyphDisplayType type);

protected:
    //----- AcDbEntity protocols
    //- Graphics protocol
    virtual void subViewportDraw (AcGiViewportDraw *mode) override;
    virtual Adesk::Boolean subWorldDraw (AcGiWorldDraw *mode) override;
    virtual Adesk::UInt32  subSetAttributes(AcGiDrawableTraits* pTraits) override;

    virtual Acad::ErrorStatus   subGetOsnapPoints(
                                        AcDb::OsnapMode     osnapMode,
                                        Adesk::GsMarker     gsSelectionMark,
                                        const AcGePoint3d&  pickPoint,
                                        const AcGePoint3d&  lastPoint,
                                        const AcGeMatrix3d& viewXform,
                                        AcGePoint3dArray&   snapPoints,
                                        AcDbIntArray &   geomIds) const override;

    virtual Acad::ErrorStatus   subGetOsnapPoints(
                                        AcDb::OsnapMode     osnapMode,
                                        Adesk::GsMarker     gsSelectionMark,
                                        const AcGePoint3d&  pickPoint,
                                        const AcGePoint3d&  lastPoint,
                                        const AcGeMatrix3d& viewXform,
                                        AcGePoint3dArray&   snapPoints,
                                        AcDbIntArray &   geomIds,
                                        const AcGeMatrix3d& insertionMat) const override;

    
    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform) override;

    virtual Acad::ErrorStatus subGetTransformedCopy(const AcGeMatrix3d & xform,AcDbEntity *& pEnt) const override;

    virtual void subList() const override;

    virtual Acad::ErrorStatus subGetGripPoints (AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d &curViewDir, const int bitflags) const override;

    virtual Acad::ErrorStatus subMoveGripPointsAt (const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset, const int bitflags) override;

    
    virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwner,AcDbObject*& pClonedObject,
                                        AcDbIdMapping& idMap,Adesk::Boolean isPrimary = true) const override;

    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, 
                                        AcDbIdMapping& idMap, Adesk::Boolean isPrimary /* = true */) const override;

    
    virtual Acad::ErrorStatus subHighlight(const AcDbFullSubentPath& subId, 
        const Adesk::Boolean highlightAll) const override;

    virtual Acad::ErrorStatus subUnhighlight(const AcDbFullSubentPath& subId, 
        const Adesk::Boolean highlightAll) const override;

    
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
    virtual Acad::ErrorStatus subGetGeomExtents(AcDbExtents& extents) const override;
private:
    friend class AcDbImpLight;
    Adesk::UInt32 baseSetAttributes(AcGiDrawableTraits* pTraits);
    Acad::ErrorStatus baseDeepClone(AcDbObject* pOwner,AcDbObject*& pClonedObject,
                                    AcDbIdMapping& idMap,Adesk::Boolean isPrimary) const;
    Acad::ErrorStatus baseWblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, 
                                      AcDbIdMapping& idMap, Adesk::Boolean isPrimary) const;
    Acad::ErrorStatus baseHighlight(const AcDbFullSubentPath& subId, 
                                    const Adesk::Boolean highlightAll) const;
    Acad::ErrorStatus baseUnhighlight(const AcDbFullSubentPath& subId, 
                                      const Adesk::Boolean highlightAll) const;

    AcDbImpLight * mpAcDbImpLight;
    bool mSelected;
};






