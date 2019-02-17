#pragma once
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

//
// This API extends AcGi to support material definition and assignment
//

#include "AdAChar.h"
#include "acgi.h"
#pragma pack (push, 8)

#ifdef ACGIMATERIAL_IMPL
  #define ACGIMAT_IMPEXP __declspec(dllexport)
#else
  #define ACGIMAT_IMPEXP __declspec(dllimport)
#endif

class AcGiMaterialColor;
class AcGiMaterialMap;

class AcGiMaterialTraits : public AcGiNonEntityTraits
// 
// This class enables material definitions to be elaborated to 
// AcGi implementations
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMaterialTraits);

    enum IlluminationModel {
        kBlinnShader = 0,
        kMetalShader, 
    };

    enum ChannelFlags
    {
        kNone          = 0x00000,
        kUseDiffuse    = 0x00001,
        kUseSpecular   = 0x00002,
        kUseReflection = 0x00004,
        kUseOpacity    = 0x00008,
        kUseBump       = 0x00010,
        kUseRefraction = 0x00020,
        kUseNormalMap  = 0x00040,
        kUseAll        = (kUseDiffuse | kUseSpecular | kUseReflection 
                            | kUseOpacity | kUseBump | kUseRefraction
                            | kUseNormalMap),
    };

    enum Mode {
        kRealistic = 0,
        kAdvanced, 
    };

    enum LuminanceMode
    {
        kSelfIllumination = 0,
        kLuminance,
    };

    enum NormalMapMethod
    {
        kTangentSpace
    };

    enum GlobalIlluminationMode
    {
        kGlobalIlluminationNone,
        kGlobalIlluminationCast,
        kGlobalIlluminationReceive,
        kGlobalIlluminationCastAndReceive
    };

    enum FinalGatherMode
    {
        kFinalGatherNone,
        kFinalGatherCast,
        kFinalGatherReceive,
        kFinalGatherCastAndReceive
    };

    // Set material properties
    //
    virtual void setAmbient     (const AcGiMaterialColor & color)   = 0;
    virtual void setDiffuse     (const AcGiMaterialColor & color, 
                                 const AcGiMaterialMap & map)       = 0;
    virtual void setSpecular    (const AcGiMaterialColor & color, 
                                 const AcGiMaterialMap & map,
                                 double dGloss)                     = 0;
    virtual void setReflection  (const AcGiMaterialMap & map)       = 0;
    virtual void setOpacity     (double dPercentage, 
                                 const AcGiMaterialMap & map)       = 0;
    virtual void setBump        (const AcGiMaterialMap & map)       = 0;
    virtual void setRefraction  (double dIndex, 
                                 const AcGiMaterialMap & map)       = 0;
    virtual void setTranslucence(double value)                      = 0;
    virtual void setSelfIllumination(double value)                  = 0;
    virtual void setReflectivity(double value)                      = 0;
    virtual void setIlluminationModel(IlluminationModel model)      = 0;
    virtual void setChannelFlags(ChannelFlags flags)                = 0;
    virtual void setMode(Mode value)                                = 0;

    // Return material properties
    //
    virtual void ambient        (AcGiMaterialColor & color) const   = 0;
    virtual void diffuse        (AcGiMaterialColor & color, 
                                 AcGiMaterialMap & map) const       = 0;
    virtual void specular       (AcGiMaterialColor & color, 
                                 AcGiMaterialMap & map,
                                 double & dGloss) const             = 0;
    virtual void reflection     (AcGiMaterialMap & map) const       = 0;
    virtual void opacity        (double & dPercentage, 
                                 AcGiMaterialMap & map) const       = 0;
    virtual void bump           (AcGiMaterialMap & map) const       = 0;
    virtual void refraction     (double & dIndex, 
                                 AcGiMaterialMap & map) const       = 0;
    virtual double translucence() const                             = 0;
    virtual double selfIllumination() const                         = 0;
    virtual double reflectivity() const                             = 0;
    virtual IlluminationModel illuminationModel() const             = 0;
    virtual ChannelFlags channelFlags() const                       = 0;
    virtual Mode mode() const                                       = 0;

    // Set material properties
    //
    virtual void setColorBleedScale(double value)                   = 0;
    virtual void setIndirectBumpScale(double value)                 = 0;
    virtual void setReflectanceScale(double value)                  = 0;
    virtual void setTransmittanceScale(double value)                = 0;
    virtual void setTwoSided(bool value)                            = 0;
    virtual void setLuminanceMode(LuminanceMode value)              = 0;
    virtual void setLuminance(double value)                         = 0;
    virtual void setNormalMap(const AcGiMaterialMap & map, 
                              NormalMapMethod method, 
                              double strength)                      = 0;
    virtual void setGlobalIllumination(GlobalIlluminationMode mode) = 0;
    virtual void setFinalGather(FinalGatherMode mode)               = 0;

    // Get material properties
    //
    virtual double colorBleedScale() const                          = 0;
    virtual double indirectBumpScale() const                        = 0;
    virtual double reflectanceScale() const                         = 0;
    virtual double transmittanceScale() const                       = 0;
    virtual bool   twoSided() const                                 = 0;
    virtual LuminanceMode luminanceMode() const                     = 0;
    virtual double luminance() const                                = 0;
    virtual void normalMap(AcGiMaterialMap & map, 
                           NormalMapMethod &method, 
                           double &strength) const                  = 0;
    virtual GlobalIlluminationMode globalIllumination() const       = 0;
    virtual FinalGatherMode finalGather() const                     = 0;
};

class AcGiImpMaterialColor;

class AcGiMaterialColor: public AcRxObject
//
// This class defines material component colors by
// method, color value, and factor. 
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMaterialColor);

    enum Method {
        kInherit = 0,
        kOverride,     
    };

    ACGIMAT_IMPEXP static const AcGiMaterialColor kNull;

    AcGiMaterialColor             (void);
    virtual ~AcGiMaterialColor    (void);

    AcGiMaterialColor             (const AcGiMaterialColor &matColor);
    AcGiMaterialColor & operator= (const AcGiMaterialColor &matColor);
    bool                operator==(const AcGiMaterialColor &matColor)const;

    // Set properties of material color.
    //
    virtual void set       (const AcGiMaterialColor &matColor);
    virtual void setMethod (Method method);
    virtual void setFactor (double dFactor);
    virtual void setColor  (const AcCmEntityColor& color);

    // Return current settings.
    //
    virtual Method                  method (void) const;
    virtual double                  factor (void) const;
    virtual const AcCmEntityColor & color  (void) const;

private:
    AcGiImpMaterialColor * mpAcGiImpMaterialColor;
};


class AcGiMaterialTexture : public AcRxObject
//
// This class defines material texture 
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMaterialTexture);
    virtual bool operator==(const AcGiMaterialTexture & texture)const;
protected:
};

inline bool AcGiMaterialTexture::operator==(const AcGiMaterialTexture & texture) const {
        return (texture.isA() == isA());
}


class AcGiImageTexture : public AcGiMaterialTexture
//
// This class defines an image based material texture 
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiImageTexture);
};

class AcGiImpImageFileTexture;

class AcGiImageFileTexture : public AcGiImageTexture
//
// This class defines an image file based material texture 
//
{
    friend class AcGiImpImageFileTexture;
public:
    ACRX_DECLARE_MEMBERS(AcGiImageFileTexture);

    AcGiImageFileTexture             (void);
    virtual ~AcGiImageFileTexture    (void);

    AcGiImageFileTexture             (const AcGiImageFileTexture &texture);
    AcGiImageFileTexture & operator= (const AcGiImageFileTexture &texture);
    virtual bool operator==(const AcGiMaterialTexture & texture) const override;

    //AcRxObject protocol
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

    virtual void                setSourceFileName (const ACHAR * fileName);
    virtual const ACHAR *       sourceFileName    (void) const;
private:
    AcGiImpImageFileTexture * mpAcGiImpImageFileTexture;
};



class AcGiProceduralTexture : public AcGiMaterialTexture
//
// This class defines a procedural material texture 
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiProceduralTexture);

    enum Type
    {
        kWood = 0,
        kMarble,
        kGeneric,
    };
};


class AcGiGenericTexture : public AcGiProceduralTexture
//
// This class defines a generic material texture
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGenericTexture);

    AcGiGenericTexture              (void);
    virtual ~AcGiGenericTexture      (void);

    AcGiGenericTexture              (const AcGiGenericTexture &texture);
    AcGiGenericTexture & operator=  (const AcGiGenericTexture &texture);
    virtual bool         operator== (const AcGiMaterialTexture &texture) const override;

    //AcRxObject protocol
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

    // Generic Texture properties
    void            setDefinition   (const AcGiVariant& definition);
    AcGiVariant     definition      (void) const;
    void            definition      (AcGiVariant*& pDefinition);

protected:
    AcGiVariant     m_definition;
};




class AcGiImpWoodTexture;

class AcGiWoodTexture : public AcGiProceduralTexture
//
// This class defines a wood procedural material texture 
//
{
    friend class AcGiImpWoodTexture;
public:
    ACRX_DECLARE_MEMBERS(AcGiWoodTexture);

    AcGiWoodTexture             (void);
    virtual ~AcGiWoodTexture    (void);

    AcGiWoodTexture             (const AcGiWoodTexture &texture);
    AcGiWoodTexture & operator= (const AcGiWoodTexture &texture);
    virtual bool      operator==(const AcGiMaterialTexture & texture) const override;

    //AcRxObject protocol
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

    // wood properties
    virtual void setColor1      (const AcGiMaterialColor &woodColor1);
    virtual const AcGiMaterialColor & color1  (void) const;

    virtual void setColor2      (const AcGiMaterialColor &woodColor2);
    virtual const AcGiMaterialColor & color2  (void) const;

    virtual void setRadialNoise (double radialNoise);
    virtual double radialNoise  (void) const;

    virtual void setAxialNoise  (double axialNoise);
    virtual double axialNoise   (void) const;

    virtual void setGrainThickness  (double grainThickness);
    virtual double grainThickness   (void) const;

private:
    AcGiImpWoodTexture * mpAcGiImpWoodTexture;
};

class AcGiImpMarbleTexture;

class AcGiMarbleTexture : public AcGiProceduralTexture
//
// This class defines a marble procedural material texture 
//
{
    friend class AcGiImpMarbleTexture;
public:
    ACRX_DECLARE_MEMBERS(AcGiMarbleTexture);

    AcGiMarbleTexture             (void);
    virtual ~AcGiMarbleTexture    (void);

    AcGiMarbleTexture             (const AcGiMarbleTexture &texture);
    AcGiMarbleTexture & operator= (const AcGiMarbleTexture &texture);
    virtual bool        operator==(const AcGiMaterialTexture & texture) const override;

    //AcRxObject protocol
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;

    // marble properties
    virtual void setStoneColor     (const AcGiMaterialColor &stoneColor);
    virtual const AcGiMaterialColor & stoneColor  (void) const;

    virtual void setVeinColor      (const AcGiMaterialColor &veinColor);
    virtual const AcGiMaterialColor & veinColor  (void) const;

    virtual void setVeinSpacing    (double veinSpacing);
    virtual double veinSpacing     (void) const;

    virtual void setVeinWidth      (double veinWidth);
    virtual double veinWidth       (void) const;

private:
    AcGiImpMarbleTexture * mpAcGiImpMarbleTexture;
};


class AcGiMapper;
class AcGiImpMaterialMap;

class AcGiMaterialMap: public AcRxObject 
//
// This class defines material component maps by 
// source, blend factor, and mapper.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiMaterialMap);

    enum Source {
        kScene = 0,
        kFile,
        kProcedural
    };

    ///<summary>Material map filtering settings.</summary>
    enum Filter 
    {
        ///<summary>
        /// Uses the default filtering setting rather than explicitly setting a
        /// particular filtering type.
        ///</summary>
        kFilterDefault = 0,

        ///<summary>Explicitly disables filtering on this material map.</summary>
        kFilterNone
    };


    ACGIMAT_IMPEXP static const AcGiMaterialMap kNull;

    AcGiMaterialMap             (void);
    virtual ~AcGiMaterialMap    (void);

    AcGiMaterialMap             (const AcGiMaterialMap &matMap);
    AcGiMaterialMap & operator= (const AcGiMaterialMap &matMap);
    bool              operator==(const AcGiMaterialMap &matMap)const;

    // Set properties of material map.
    //
    virtual void set               (const AcGiMaterialMap &matMap);
    virtual void setSource         (Source source);
    // Deprecated: The setSourceFileName() method will be removed in a future
    // release. Instead, use the method of the same name in AcGiImageFileTexture.
    ADESK_DEPRECATED virtual void setSourceFileName (const ACHAR * fileName);
    virtual void setTexture        (const AcGiMaterialTexture * pTexture);
    virtual void setBlendFactor    (double blendFactor);
    virtual void setMapper         (const AcGiMapper &mapper);

    // Return current settings.
    //
    virtual Source                  source         (void) const;
    // Deprecated: The sourceFileName() method will be removed in a future
    // release. Instead, use the method of the same name in AcGiImageFileTexture.
    ADESK_DEPRECATED virtual const ACHAR * sourceFileName (void) const;
    virtual const AcGiMaterialTexture *  texture   (void) const;
    virtual double                  blendFactor    (void) const;
    virtual const AcGiMapper &      mapper         (void) const;


    ///<summary>
    /// Sets the filtering to use on the material map.  This may not be applicable
    /// to material maps which do not use filtering, such as procedural maps.
    ///</summary>
    ///<param name="filter">New filter setting.</param>
    ///<returns>Acad::eOk if the new filter can be set.</returns>
    ACGIMAT_IMPEXP Acad::ErrorStatus   setFilter   (Filter filter);
    
    ///<summary>
    ///<para>
    /// Returns he filtering to use on the material map.  This may not be applicable
    /// to material maps which do not use filtering, such as procedural maps.
    ///</para>
    ///<para>
    /// The default setting is kFilterDefault.
    ///</para>
    ///</summary>
    ///<returns>The current filter set on the material map object.</returns>
    ACGIMAT_IMPEXP Filter              filter      (void) const;

protected:
    AcGiImpMaterialMap * mpAcGiImpMaterialMap;
};
  
class AcGiImpMapper;

class AcGiMapper: public AcGiParameter 
//
// This class defines material component mappers by 
// projection, tiling, auto transform, and transform.
//
{
public:
    ACRX_DECLARE_MEMBERS_READWRITE(AcGiMapper, AcGiImpMapper);

    enum Projection {
        kInheritProjection = 0,
        kPlanar,
        kBox,
        kCylinder,
        kSphere
    };

    enum Tiling {
        kInheritTiling = 0,
        kTile,
        kCrop,
        kClamp,
        kMirror,
    };

    enum AutoTransform {
        kInheritAutoTransform = 0x0,
        kNone                 = 0x1,
        kObject               = 0x2,
        kModel                = 0x4
    };

    ACGIMAT_IMPEXP static const AcGiMapper kIdentity;

    AcGiMapper             (void);
    virtual ~AcGiMapper    (void);

    AcGiMapper             (const AcGiMapper &mapper);
    AcGiMapper & operator= (const AcGiMapper &mapper);
    bool         operator==(const AcGiMapper &mapper) const;
    bool         operator!=(const AcGiMapper &mapper) const 
    { 
        return !(*this == mapper); 
    };

    // Set properties of material mapper.
    //
    virtual                  void set               (const AcGiMapper &mapper);
    virtual                  void setProjection     (Projection projection);
    virtual                  void setAutoTransform  (AutoTransform autoTransform);
    virtual                  void setTransform      (const AcGeMatrix3d &transform);

    // Return current settings.
    //
    virtual                     Projection             projection    (void) const;
    virtual                     AutoTransform          autoTransform (void) const;
    virtual                     const AcGeMatrix3d&    transform     (void) const;

    // New properties for Spago
    void        setUTiling        (Tiling tiling);
    void        setVTiling        (Tiling tiling);
    Tiling      uTiling           (void) const;
    Tiling      vTiling           (void) const;
};

#pragma pack (pop)
