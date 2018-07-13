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

#ifndef __ACDBSECTIONVIEWSTYLE_H__
#define __ACDBSECTIONVIEWSTYLE_H__

#pragma once
#include "dbModelDocViewStyle.h"

#pragma pack (push, 8)

class ACDBCORE2D_PORT AcDbSectionViewStyle : public AcDbModelDocViewStyle
{
public:
    /// <summary>
    /// Enumeration defining identifier position type
    /// </summary>
    enum IdentifierPosition {
        kEndCuttingPlane             = 0,
        kAboveDirectionArrowLine     = 1,
        kAboveDirectionArrowSymbol   = 2,
        kStartDirectionArrow         = 3,
        kEndDirectionArrow           = 4,
    };

    /// <summary>
    /// Enumeration defining identifier position type
    /// </summary>
    enum ArrowDirection {
        kTowardsCuttingPlane    = 0,
        kAwayFromCuttingPlane   = 1,
    };

    AcDbSectionViewStyle();
    ~AcDbSectionViewStyle();
    ACDB_DECLARE_MEMBERS(AcDbSectionViewStyle);
   
    /// <summary>
    /// Returns the text style objectId of the identifier.
    /// </summary>
    ///
    /// <returns>
    /// Returns the text style objectId of the identifier.
    /// </returns>
    AcDbObjectId      identifierStyleId () const;

    /// <summary>
    /// Sets the identifier to use specified text style.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of text style to use for the identifier.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setIdentifierStyleId (const AcDbObjectId &objId);

    /// <summary>
    /// Returns the color of the identifier.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of the identifier.
    /// </returns>
    AcCmColor         identifierColor () const;

    /// <summary>
    /// Sets the identifier to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for the identifier.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setIdentifierColor (const AcCmColor& color);

    /// <summary>
    /// Returns the height of the identifier.
    /// </summary>
    ///
    /// <returns>
    /// Returns the height of the identifier.
    /// </returns>
    double            identifierHeight () const;

    /// <summary>
    /// Sets the text height the identifier.
    /// </summary>
    ///
    /// <param name="height">
    /// Text height to use for the identifier.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setIdentifierHeight (double height);

    /// <summary>
    /// Returns the identifier exclude characters.
    /// </summary>
    ///
    /// <returns>
    /// Returns the identifier exclude characters.
    /// </returns>
    const ACHAR *     identifierExcludeCharacters () const;

    /// <summary>
    /// Sets the identifer exclude characters.
    /// </summary>
    ///
    /// <param name="str">
    /// Exclude characters separated by comma. 
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful or Acad::eInvalidInput
    /// if the format is incorrect or there are invalid characters.
    /// </returns>
    Acad::ErrorStatus setIdentifierExcludeCharacters (const ACHAR* str);

    /// <summary>
    /// Returns the objectId of arrow start symbol.
    /// </summary>
    ///
    /// <returns>
    /// Returns the objectId of arrow start symbol.
    /// </returns>
    AcDbObjectId      arrowStartSymbolId () const;

    /// <summary>
    /// Sets the arrow start symbol to use specified block table record.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of block table record to use for arrow start symbol
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setArrowStartSymbolId (const AcDbObjectId &arrowSymbolId);

    /// <summary>
    /// Returns the objectId of arrow end symbol.
    /// </summary>
    ///
    /// <returns>
    /// Returns the objectId of arrow end symbol.
    /// </returns>
    AcDbObjectId      arrowEndSymbolId () const;

    /// <summary>
    /// Sets the arrow end symbol to use specified block table record.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of block table record to use for arrow end symbol
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setArrowEndSymbolId (const AcDbObjectId &arrowSymbolId);

    /// <summary>
    /// Returns the color of arrow symbol.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of arrow symbol.
    /// </returns>
    AcCmColor         arrowSymbolColor () const;

    /// <summary>
    /// Sets the arrow symbol to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for arrow symbol
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setArrowSymbolColor (const AcCmColor& color);

    /// <summary>
    /// Returns the size of arrow symbol.
    /// </summary>
    ///
    /// <returns>
    /// Returns the size of arrow symbol.
    /// </returns>
    double            arrowSymbolSize () const;

    /// <summary>
    /// Sets the size of arrow symbol.
    /// </summary>
    ///
    /// <param name="size">
    /// Size of arrow symbol
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setArrowSymbolSize (double size);

    /// <summary>
    /// Returns the extension length of arrow symbol.
    /// </summary>
    ///
    /// <returns>
    /// Returns the extension length of arrow symbol.
    /// </returns>
    double            arrowSymbolExtensionLength () const;

    /// <summary>
    /// Sets the extension length of arrow symbol.
    /// </summary>
    ///
    /// <param name="length">
    /// Extension length of arrow symbol
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setArrowSymbolExtensionLength (double length);

    /// <summary>
    /// Returns the line weight of plane line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the line weight of plane line.
    /// </returns>
    AcDb::LineWeight  planeLineWeight () const;

    /// <summary>
    /// Sets the plane line to use specified line weight.
    /// </summary>
    ///
    /// <param name="color">
    /// Line weight to use.for plane.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setPlaneLineWeight (AcDb::LineWeight lineweight);

    /// <summary>
    /// Returns the color of plane line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of plane line.
    /// </returns>
    AcCmColor         planeLineColor () const;

    /// <summary>
    /// Sets the plane line to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for plane.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setPlaneLineColor (const AcCmColor& color);

    /// <summary>
    /// Returns the linetype objectId of plane line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the linetype objectId of plane line.
    /// </returns>
    AcDbObjectId      planeLineTypeId () const;

    /// <summary>
    /// Sets the plane line to use specified linetype.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of the linetype to use.for plane.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setPlaneLineTypeId (const AcDbObjectId &objId);

    /// <summary>
    /// Returns the color of bend line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of bend line.
    /// </returns>
    AcCmColor         bendLineColor () const;

    /// <summary>
    /// Sets the bend line to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for bend.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBendLineColor (const AcCmColor& color);

    /// <summary>
    /// Returns the line weight of bend line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the line weight of bend line.
    /// </returns>
    AcDb::LineWeight  bendLineWeight () const;

    /// <summary>
    /// Sets the bend line to use specified line weight.
    /// </summary>
    ///
    /// <param name="color">
    /// Line weight to use.for bend.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBendLineWeight (AcDb::LineWeight lineweight);

    /// <summary>
    /// Returns the linetype objectId of bend line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the linetype objectId of bend line.
    /// </returns>
    AcDbObjectId      bendLineTypeId () const;

    /// <summary>
    /// Sets the bend line to use specified linetype.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of the linetype to use.for bend.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBendLineTypeId (const AcDbObjectId &objId);

    /// <summary>
    /// Returns the length of bend line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the length of bend line.
    /// </returns>
    double            bendLineLength () const;

    /// <summary>
    /// Sets the length of bend line.
    /// </summary>
    ///
    /// <param name="length">
    /// length of bend line.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBendLineLength (double length);

    /// <summary>
    /// Returns the length of end line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the length of end line.
    /// </returns>
    double            endLineLength () const;

    /// <summary>
    /// Sets the length of end line.
    /// </summary>
    ///
    /// <param name="length">
    /// length of end line.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setEndLineLength (double length);

    /// <summary>
    /// Returns the text style objectId of view label.
    /// </summary>
    ///
    /// <returns>
    /// Returns the text style objectId of view label.
    /// </returns>
    AcDbObjectId      viewLabelTextStyleId () const;

    /// <summary>
    /// Sets the text style of the view label text.
    /// </summary>
    ///
    /// <param name="objId">
    /// length of end and bend line.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewLabelTextStyleId (const AcDbObjectId &objId);

    /// <summary>
    /// Returns the color of view label.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of view label.
    /// </returns>
    AcCmColor         viewLabelTextColor () const;

    /// <summary>
    /// Sets the view label to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for view label
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewLabelTextColor (const AcCmColor& color);

    /// <summary>
    /// Returns the text height of view label.
    /// </summary>
    ///
    /// <returns>
    /// Returns the text height of view label.
    /// </returns>
    double            viewLabelTextHeight () const;
    Acad::ErrorStatus setViewLabelTextHeight (double height);

    /// <summary>
    /// Returns the offset of view label.
    /// </summary>
    ///
    /// <returns>
    /// Returns the offset of view label.
    /// </returns>
    double            viewLabelOffset () const;

    /// <summary>
    /// Sets the offset for view label.
    /// </summary>
    ///
    /// <param name="offset">
    /// offset for view label
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewLabelOffset (double offset);

    /// <summary>
    /// Returns the attachment of view label.
    /// </summary>
    ///
    /// <returns>
    /// Returns the attachment of view label.
    /// </returns>
    AcDbModelDocViewStyle::AttachmentPoint viewLabelAttachment () const;

    /// <summary>
    /// Sets the attachment for view label.
    /// </summary>
    ///
    /// <param name="attachment">
    /// attachment of view label
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewLabelAttachment (AcDbModelDocViewStyle::AttachmentPoint attachment);

    /// <summary>
    /// Returns the text alignment of view label.
    /// </summary>
    ///
    /// <returns>
    /// Returns the text alignment of view label.
    /// </returns>
    AcDbModelDocViewStyle::TextAlignment viewLabelAlignment () const;

    /// <summary>
    /// Sets the text alignment for view label.
    /// </summary>
    ///
    /// <param name="attachment">
    /// text alignment for view label
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewLabelAlignment (AcDbModelDocViewStyle::TextAlignment alignment);

    /// <summary>
    /// Returns the pattern of view label.
    /// </summary>
    ///
    /// <returns>
    /// Returns the pattern of view label.
    /// </returns>
    const ACHAR *     viewLabelPattern () const;

    /// <summary>
    /// Gets the pattern for view label. If 'pField' parameter is specified and label
    /// pattern is currently using fields, the master field will be copied to 'pField'
    /// including child fields.
    /// </summary>
    ///
    /// <param name="pattern">
    /// pattern for view label
    /// </param>
    /// <param name="pField">
    /// If this optional parameter is specified and the pattern label is currently
    /// using fields, the master field will be copied to 'pField'. Child fields
    /// are also copied.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus getViewLabelPattern (AcString &pattern,
                                           AcDbField *pField = NULL) const;

    /// <summary>
    /// Sets the pattern for view label. If 'pField' parameter is specified and
    /// contains child fields, then label pattern will be acquired from the field.
    /// Otherwise 'pattern' is used.
    /// </summary>
    ///
    /// <param name="pattern"> pattern for view label
    /// </param>
    /// <param name="pField">
    /// If 'pField' parameter is specified and contains child fields, then label
    /// pattern will be acquired from the field, rather than from 'pattern'.
    /// The field including child fields are also copied to view style's field.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewLabelPattern (const ACHAR* pattern,
                                           const AcDbField *pField = NULL);

    /// <summary>
    /// Returns the hatch pattern.
    /// </summary>
    ///
    /// <returns>
    /// Returns the hatch pattern.
    /// </returns>
    const ACHAR *     hatchPattern () const;

    /// <summary>
    /// Sets the hatch pattern.
    /// </summary>
    ///
    /// <param name="pattern">
    /// hatch pattern
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setHatchPattern (const ACHAR* pattern);

    /// <summary>
    /// Returns the color of hatch.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of hatch.
    /// </returns>
    AcCmColor         hatchColor () const;

    /// <summary>
    /// Sets the hatch to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for hatch
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setHatchColor (const AcCmColor& color);

    /// <summary>
    /// Returns the background color of hatch.
    /// </summary>
    ///
    /// <returns>
    /// Returns the background color of hatch.
    /// </returns>
    AcCmColor         hatchBackgroundColor () const;

    /// <summary>
    /// Sets the hatch to use specified background color.
    /// </summary>
    ///
    /// <param name="color">
    /// Background color to use.for hatch
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setHatchBackgroundColor (const AcCmColor& color);

    /// <summary>
    /// Returns the scale of hatch.
    /// </summary>
    ///
    /// <returns>
    /// Returns the scale of hatch.
    /// </returns>
    double            hatchScale () const;

    /// <summary>
    /// Sets the hatch scale.
    /// </summary>
    ///
    /// <param name="scale">
    /// hatch scale
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setHatchScale (double scale);

    /// <summary>
    /// Returns the array of applicable hatch angles.
    /// </summary>
    ///
    /// <returns>
    /// Returns the array of hatch angle.
    /// </returns>
    const AcArray<double>& hatchAngles () const;

    /// <summary>
    /// Sets the hatch angle array.
    /// </summary>
    ///
    /// <param name="angleArray">
    /// hatch angle array
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setHatchAngles (const AcArray<double>& angleArray);

    /// <summary>
    /// Sets the hatch to use specified transparency.
    /// </summary>
    ///
    /// <param name="transparency">
    /// Transparency to use for hatch
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setHatchTransparency (const AcCmTransparency& transparency);

    /// <summary>
    /// Returns the transparency of hatch.
    /// </summary>
    ///
    /// <returns>
    /// Returns the transparency of hatch.
    /// </returns>
    AcCmTransparency  hatchTransparency () const;


    /// <summary>
    /// Returns boolean value indicating if continuous labeling
    /// is in use.
    /// </summary>
    ///
    /// <returns>
    /// true if continuous labeling is in use, false otherwise.
    /// </returns>
    bool              isContinuousLabeling () const;
    Acad::ErrorStatus setContinuousLabeling (bool bValue);

    /// <summary>
    /// Returns boolean value indicating if to show arrowheads.
    /// </summary>
    ///
    /// <returns>
    /// true if to show arrowheads is on, false otherwise.
    /// </returns>
    bool              showArrowheads () const;
    Acad::ErrorStatus setShowArrowheads (bool bValue);

    /// <summary>
    /// Returns boolean value indicating if to show view label.
    /// </summary>
    ///
    /// <returns>
    /// true if to show view label is on, false otherwise.
    /// </returns>
    bool              showViewLabel () const;
    Acad::ErrorStatus setShowViewLabel (bool bValue);

    /// <summary>
    /// Returns boolean value indicating if to show all plane lines.
    /// </summary>
    ///
    /// <returns>
    /// true if to show all plane lines is on, false otherwise.
    /// </returns>
    bool              showAllPlaneLines () const;
    Acad::ErrorStatus setShowAllPlaneLines (bool bValue);

    /// <summary>
    /// Returns boolean value indicating if to show identifiers
    //  at all bends.
    /// </summary>
    ///
    /// <returns>
    /// true if to show identifiers at all bends, false otherwise.
    /// </returns>
    bool              showAllBendIndentifiers () const;
    Acad::ErrorStatus setShowAllBendIndentifiers (bool bValue);

    /// <summary>
    /// Returns boolean value indicating if to show end and bend lines.
    /// </summary>
    ///
    /// <returns>
    /// true if to show end and bend lines, false otherwise.
    /// </returns>
    bool              showEndAndBendLines () const;
    Acad::ErrorStatus setShowEndAndBendLines (bool bValue);

    /// <summary>
    /// Returns boolean value indicating if to show hatching.
    /// </summary>
    ///
    /// <returns>
    /// true if to show hatching, false otherwise.
    /// </returns>
    bool              showHatching () const;
    Acad::ErrorStatus setShowHatching (bool bValue);


    /// <summary>
    /// Checks whether identifier exclude character string is in correct format
    /// and contains valid characters.
    /// </summary>
    ///
    /// <param name="str">
    /// Identifier exclude character string. Currently the identifer exclude character
    /// string should contain capital letters from English alphabet separated
    /// by comma.
    /// </param>
    ///
    /// <returns>
    /// Return true identifier exclude character string is in correct format
    /// and contains valid characters
    /// </returns>
    static bool       validateIdentifierExcludeCharacters (const ACHAR* str);


    /// <summary>
    /// </summary>
    ///
    /// <returns>
    /// </returns>
    AcDbSectionViewStyle::IdentifierPosition viewIdentifierPosition () const;

    /// <summary>
    /// </summary>
    ///
    /// <param name="type">
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewIdentifierPosition (AcDbSectionViewStyle::IdentifierPosition type);


    /// <summary>
    /// </summary>
    ///
    /// <returns>
    /// </returns>
    double viewIdentifierOffset () const;

    /// <summary>
    /// </summary>
    ///
    /// <param name="type">
    /// </param>
    ///
    /// <returns>
    /// </returns>
    Acad::ErrorStatus setViewIdentifierOffset (double offset);


    /// <summary>
    /// </summary>
    ///
    /// <returns>
    /// </returns>
    AcDbSectionViewStyle::ArrowDirection arrowPosition () const;

    /// <summary>
    /// </summary>
    ///
    /// <param name="type">
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setArrowPosition (AcDbSectionViewStyle::ArrowDirection type);

    /// <summary>
    /// Returns the Overshoot of end line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the Overshoot of end line.
    /// </returns>
    double            endLineOvershoot () const;

    /// <summary>
    /// Sets the Overshoot of End line.
    /// </summary>
    ///
    /// <param name="length">
    /// Overshoot of End line.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setEndLineOvershoot (double length);

protected:
    // For internal use only
    virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwner, AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;
    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwner, AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;
};

#pragma pack (pop)

#endif // __ACDBSECTIONVIEWSTYLE_H__
