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
#include "acdbport.h"
#include "dbmain.h"
#include "rxboiler.h"
#include "gepnt3d.h"
#include "gevec3d.h"
#include "AcString.h"

#pragma pack (push, 8)

class AcDbMText;

/// <summary>
/// the AcDbGeoPositionMarker class represents a Geographical location aware marker object with label
/// </summary>
///
class ACDBCORE2D_PORT AcDbGeoPositionMarker : public AcDbEntity
{
public:

    enum TextAlignmentType {
        /// <summary>
        /// Left-justifies text in the MText.
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kLeftAlignment = 0,
        /// <summary>
        /// Centers text in MText.
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kCenterAlignment = 1,
        /// <summary>
        /// Right-justifies text in MText.
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kRightAlignment = 2
    };

    ACRX_DECLARE_MEMBERS(AcDbGeoPositionMarker);

    AcDbGeoPositionMarker();
    AcDbGeoPositionMarker(const AcGePoint3d &position, double radius, double landingGap);


    /// <summary> Get/Set Insertion point of the position marker. </summary>
    ///
    AcGePoint3d          position() const;
    Acad::ErrorStatus    setPosition(const AcGePoint3d &position);

    /// <summary> Get/Set radius of the position marker. </summary>
    ///
    double               radius() const;
    Acad::ErrorStatus    setRadius(double radius);

    /// <summary> Get/Set position marker text label. </summary>
    ///
    AcString             text() const;
    Acad::ErrorStatus    setText(const AcString& text);

    /// <summary> Get/Set position marker MText label. </summary>
    ///
    AcDbMText*           mtext() const;
    Acad::ErrorStatus    setMText(const AcDbMText* pMText);

    /// <summary> Get/Set the visibility of the MText label. </summary>
    ///
    bool                 mtextVisible() const;
    Acad::ErrorStatus    setMTextVisible(bool visible);

    /// <summary> Get/Set landing gap of the position marker. </summary>
    ///
    double               landingGap() const;
    Acad::ErrorStatus    setLandingGap(double landingGap);

    /// <summary> Get/Set label text frame enabling. </summary>
    ///
    bool                 enableFrameText() const;
    Acad::ErrorStatus    setEnableFrameText(bool enableFrameText);

    /// <summary> Get/Set label text alignment type. </summary>
    ///
    TextAlignmentType    textAlignmentType() const;
    Acad::ErrorStatus    setTextAlignmentType(TextAlignmentType textAlignmentType);

    /// <summary> Get/Set the notes. </summary>
    ///
    AcString             notes() const;
    Acad::ErrorStatus    setNotes(const AcString& notes);

    /// <summary> Get/Set the Geographical location of the position marker. </summary>
    ///
    AcGePoint3d          geoPosition() const;
    Acad::ErrorStatus    setGeoPosition(const AcGePoint3d &position);
    Acad::ErrorStatus    latLonAlt(double &lat, double &lon, double &alt) const;
    Acad::ErrorStatus    setLatLonAlt(double lat, double lon, double alt);

    /// <summary> The normal of the position marker. </summary>
    ///
    AcGeVector3d        normal() const;

    /// <summary> The text style Object ID of the position marker text. </summary>
    ///
    AcDbObjectId        textStyle() const;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

#pragma pack (pop)
