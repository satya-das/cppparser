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

#include "dbmain.h"
#include "acgimaterial.h"

#pragma pack (push, 8)

class AcDbMaterial : public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbMaterial);
    
    AcDbMaterial();
    virtual ~AcDbMaterial();

    // AcDbMaterial protocol
    //
    virtual Acad::ErrorStatus   setName (const ACHAR * pName);
    virtual const ACHAR *       name    (void) const;

    virtual Acad::ErrorStatus   setDescription(const ACHAR * pDescription);
    virtual const ACHAR *       description(void) const;

    virtual void setAmbient     (const AcGiMaterialColor & color);
    virtual void ambient        (AcGiMaterialColor & color) const;

    virtual void setDiffuse     (const AcGiMaterialColor & color,
                                 const AcGiMaterialMap & map);
    virtual void diffuse        (AcGiMaterialColor & color, 
                                 AcGiMaterialMap & map) const;

    virtual void setSpecular    (const AcGiMaterialColor & color,
                                 const AcGiMaterialMap & map,
                                 double dGloss);
    virtual void specular       (AcGiMaterialColor & color,
                                 AcGiMaterialMap & map,
                                 double & dGloss) const;

    virtual void setReflection  (const AcGiMaterialMap & map);
    virtual void reflection     (AcGiMaterialMap & map) const;

    virtual void setOpacity     (double dPercentage,
                                 const AcGiMaterialMap & map);
    virtual void opacity        (double & dPercentage,
                                 AcGiMaterialMap & map) const;

    virtual void setBump        (const AcGiMaterialMap & map);
    virtual void bump           (AcGiMaterialMap & map) const;

    virtual void setRefraction  (double dIndex,
                                 const AcGiMaterialMap & map);
    virtual void refraction     (double & dIndex,
                                 AcGiMaterialMap & map) const;

    virtual double translucence() const;
    virtual Acad::ErrorStatus setTranslucence(double value);

    virtual double selfIllumination() const;
    virtual Acad::ErrorStatus setSelfIllumination(double value);

    virtual double reflectivity() const;
    virtual Acad::ErrorStatus setReflectivity(double value);

    virtual AcGiMaterialTraits::IlluminationModel illuminationModel() const;
    virtual Acad::ErrorStatus setIlluminationModel(AcGiMaterialTraits::IlluminationModel model);

    virtual AcGiMaterialTraits::ChannelFlags channelFlags() const;
    virtual Acad::ErrorStatus setChannelFlags(AcGiMaterialTraits::ChannelFlags value);

    virtual AcGiMaterialTraits::Mode mode() const;
    virtual Acad::ErrorStatus setMode(AcGiMaterialTraits::Mode value);

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const override;
    virtual AcGiDrawable*     drawable     (void) override;

    // AcDbMaterial protocol, new material properties for Spago
    double              colorBleedScale         () const;
    Acad::ErrorStatus   setColorBleedScale      (double value);

    double              indirectBumpScale       () const;
    Acad::ErrorStatus   setIndirectBumpScale    (double value);

    double              reflectanceScale        () const;
    Acad::ErrorStatus   setReflectanceScale     (double value);

    double              transmittanceScale      () const;
    Acad::ErrorStatus   setTransmittanceScale   (double value);
    
    Adesk::Boolean      twoSided                () const;
    Acad::ErrorStatus   setTwoSided             (Adesk::Boolean value);
    
    AcGiMaterialTraits::LuminanceMode luminanceMode () const;
    Acad::ErrorStatus   setLuminanceMode        (AcGiMaterialTraits::LuminanceMode value);

    double              luminance               () const;
    Acad::ErrorStatus   setLuminance            (double value);

    double              shininess               () const;
    Acad::ErrorStatus   setShininess            (double value);

    Acad::ErrorStatus   normalMap               (AcGiMaterialMap & map, 
                                                 AcGiMaterialTraits::NormalMapMethod & method, 
                                                 double & strength) const;
    Acad::ErrorStatus   setNormalMap            (const AcGiMaterialMap & map, 
                                                 AcGiMaterialTraits::NormalMapMethod method, 
                                                 double strength);

    Adesk::Boolean      isAnonymous             () const;
    Acad::ErrorStatus   setAnonymous            (Adesk::Boolean isAnonymous);

    AcGiMaterialTraits::GlobalIlluminationMode globalIllumination() const;
    void                setGlobalIllumination   (AcGiMaterialTraits::GlobalIlluminationMode mode);

    AcGiMaterialTraits::FinalGatherMode        finalGather() const;
    void                setFinalGather          (AcGiMaterialTraits::FinalGatherMode mode);

    bool                isRenamable             () const;

    // WARNING: Caller must **NOT** delete the returned pointer.
    //
    void* getAdskMaterialData();

    // WARNING: If bCacheIt == true, then AcDbMaterial takes over responsibility for
    //          deleting pMatObj and caller must ensure that nothing else deletes it.
    //
    Acad::ErrorStatus setAdskMaterialData(const void* pMatObj, bool bCacheIt = false);

    void clearAdskMaterialCache();

    enum MaterialFlags {
        kNone               = 0,
        kIsLegacy           = 0x1,
        kIsModifiedIsValid  = 0x2,
        kIsModified         = 0x4,
        kIsModifiedAndValid = 0x6  // kIsModifiedIsValid | kIsModified
    };

    Acad::ErrorStatus getAdskMaterialFlags(MaterialFlags& flags) const;
    Acad::ErrorStatus setAdskMaterialFlags(MaterialFlags flags);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

#pragma pack (pop)


