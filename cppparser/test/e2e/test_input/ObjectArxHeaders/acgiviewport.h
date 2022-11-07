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

#pragma once

#include "acgienvironment.h"

class AcGiViewportTraits : public AcGiDrawableTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportTraits);
 
    virtual void setBackground(const AcDbObjectId backgroundId) = 0;
    virtual AcDbObjectId        background () const = 0;

    enum DefaultLightingType {
        kOneDistantLight = 0,
        kTwoDistantLights,
        kBackLighting,
    };
    virtual bool isDefaultLightingOn() const = 0;
    virtual void setDefaultLightingOn(bool on) = 0;
    virtual DefaultLightingType defaultLightingType() const = 0;
    virtual void setDefaultLightingType(DefaultLightingType typ) = 0;

    virtual void setAmbientLightColor(const AcCmColor& clr) = 0;
    virtual AcCmColor ambientLightColor() const = 0;

    virtual void setBrightness (double brightness) = 0;
    virtual double brightness() const = 0;

    virtual void setContrast (double contrast) = 0;
    virtual double contrast() const = 0;

    virtual void setRenderEnvironment (const AcDbObjectId renderEnvId) = 0;
    virtual AcDbObjectId renderEnvironment () const = 0;

    virtual void setRenderSettings (const AcDbObjectId renderSettingsId) = 0;
    virtual AcDbObjectId renderSettings () const = 0;

    /// <summary>
    /// Sets the tone operator parameters for this viewport.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiToneOperatorParameters object that contains the tone operator
    /// properties of this viewport.
    /// </param>
    virtual void setToneOperatorParameters(const AcGiToneOperatorParameters& params) = 0;

    /// <summary>
    /// Provides access to tone operator parameters for this viewport.
    /// </summary>
    ///
    /// <param name="params">
    /// An AcGiToneOperatorParameters object that contains the tone operator
    /// properties of this viewport.
    /// </param>
    virtual void toneOperatorParameters(AcGiToneOperatorParameters& params) const = 0;
};
