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


#ifndef __ACDBDETAILVIEWSTYLE_H__
#define __ACDBDETAILVIEWSTYLE_H__

#pragma once
#include "dbModelDocViewStyle.h"

class ACDBCORE2D_PORT AcDbDetailViewStyle : public AcDbModelDocViewStyle
{
public:
	/// <summary>
	/// Enumeration defining label and identifier placement
	/// </summary>
	enum IdentifierPlacement {
		kOutsideBoundary=0,
        kOutsideBoundaryWithLeader,
        kOnBoundary,
        kOnBoundaryWithLeader,
	};

    enum ModelEdge {
        kSmooth = 0,
        kSmoothWithBorder,
        kSmoothWithConnectionLine,
        kJagged,
    };


    AcDbDetailViewStyle();
    ~AcDbDetailViewStyle();
    ACDB_DECLARE_MEMBERS(AcDbDetailViewStyle);

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
    /// Returns the offset between arrow line and extension line.
    /// The value is relative in range &lt0, 1&gt, where 0 means that
    /// arrow touches extension line at beginning and 1.0 means
    /// means that arrow touches the extension line at the end.
    /// </summary>
    ///
    /// <returns>
    /// Returns the offset between arrow line and extension line in
    /// relative form.
    /// </returns>
    double identifierOffset () const;

    /// <summary>
    /// Sets the offset between arrow line and extension line.
    /// The value is relative in range &lt0, 1&gt, where 0 means that
    /// arrow touches extension line at beginning and 1.0 means
    /// means that arrow touches the extension line at the end.
    /// </summary>
    ///
    /// <returns>
    /// Sets the offset between arrow line and extension line in relative
    /// form.
    /// </returns>
    Acad::ErrorStatus setIdentifierOffset (double offset);

    /// <summary>
    /// Returns the label and identifier placement flags.
    /// </summary>
    ///
    /// <returns>
    /// Returns the bit coded flags defining label and identifier placement.
    /// </returns>
    AcDbDetailViewStyle::IdentifierPlacement identifierPlacement () const;

    /// <summary>
    /// Sets the label and identifier placement flags.
    /// Use bit coded flags defined by identifierPlacement enumeration.
    /// </summary>
    ///
    /// <param name="placement">
    /// Bit coded flags defining label and identifier placement.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setIdentifierPlacement (AcDbDetailViewStyle::IdentifierPlacement placement);

    /// <summary>
    /// Returns the objectId of arrow start symbol.
    /// </summary>
    ///
    /// <returns>
    /// Returns the objectId of arrow start symbol.
    /// </returns>
    AcDbObjectId      arrowSymbolId () const;

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
    Acad::ErrorStatus setArrowSymbolId (const AcDbObjectId &arrowSymbolId);

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
    /// Returns boolean value indicating if to show arrowheads.
    /// </summary>
    ///
    /// <returns>
    /// true if to show arrowheads is on, false otherwise.
    /// </returns>
    bool              showArrows () const;
    Acad::ErrorStatus setShowArrows (bool bValue);

    /// <summary>
    /// Returns the line weight of Boundary line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the line weight of Boundary line.
    /// </returns>
    AcDb::LineWeight  boundaryLineWeight () const;

    /// <summary>
    /// Sets the Boundary line to use specified line weight.
    /// </summary>
    ///
    /// <param name="color">
    /// Line weight to use.for Boundary.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBoundaryLineWeight (AcDb::LineWeight lineweight);

    /// <summary>
    /// Returns the color of Boundary line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of Boundary line.
    /// </returns>
    AcCmColor         boundaryLineColor () const;

    /// <summary>
    /// Sets the Boundary line to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for Boundary.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBoundaryLineColor (const AcCmColor& color);

    /// <summary>
    /// Returns the linetype objectId of Boundary line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the linetype objectId of Boundary line.
    /// </returns>
    AcDbObjectId      boundaryLineTypeId () const;

    /// <summary>
    /// Sets the Boundary line to use specified linetype.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of the linetype to use.for Boundary.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBoundaryLineTypeId (const AcDbObjectId &objId);

    /// <summary>
    /// Returns the line weight of Connection line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the line weight of Connection line.
    /// </returns>
    AcDb::LineWeight  connectionLineWeight () const;

    /// <summary>
    /// Sets the Connection line to use specified line weight.
    /// </summary>
    ///
    /// <param name="color">
    /// Line weight to use.for Connection.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setConnectionLineWeight (AcDb::LineWeight lineweight);

    /// <summary>
    /// Returns the color of Connection line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of Connection line.
    /// </returns>
    AcCmColor         connectionLineColor () const;

    /// <summary>
    /// Sets the Connection line to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for Connection.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setConnectionLineColor (const AcCmColor& color);

    /// <summary>
    /// Returns the linetype objectId of Connection line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the linetype objectId of Connection line.
    /// </returns>
    AcDbObjectId      connectionLineTypeId () const;

    /// <summary>
    /// Sets the Connection line to use specified linetype.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of the linetype to use.for Connection.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setConnectionLineTypeId (const AcDbObjectId &objId);

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
    /// The master field including child fields are also copied to view style's field.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setViewLabelPattern (const ACHAR* pattern,
                                           const AcDbField *pField = NULL);

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
    /// Returns the label and model edge flags.
    /// </summary>
    ///
    /// <returns>
    /// Returns the bit coded flags defining label and identifier placement.
    /// </returns>
    AcDbDetailViewStyle::ModelEdge modelEdge () const;

    /// <summary>
    /// Sets the label and identifier placement flags.
    /// Use bit coded flags defined by modelEdge enumeration.
    /// </summary>
    ///
    /// <param name="placement">
    /// Bit coded flags defining label and identifier placement.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setModelEdge (AcDbDetailViewStyle::ModelEdge placement);


    /// <summary>
    /// Returns the line weight of Border line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the line weight of Border line.
    /// </returns>
    AcDb::LineWeight  borderLineWeight () const;

    /// <summary>
    /// Sets the Border line to use specified line weight.
    /// </summary>
    ///
    /// <param name="color">
    /// Line weight to use.for Border.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBorderLineWeight (AcDb::LineWeight lineweight);

    /// <summary>
    /// Returns the color of Border line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the color of Border line.
    /// </returns>
    AcCmColor         borderLineColor () const;

    /// <summary>
    /// Sets the Border line to use specified color.
    /// </summary>
    ///
    /// <param name="color">
    /// Color to use for Border.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBorderLineColor (const AcCmColor& color);

    /// <summary>
    /// Returns the linetype objectId of Border line.
    /// </summary>
    ///
    /// <returns>
    /// Returns the linetype objectId of Border line.
    /// </returns>
    AcDbObjectId      borderLineTypeId () const;

    /// <summary>
    /// Sets the Border line to use specified linetype.
    /// </summary>
    ///
    /// <param name="objId">
    /// ObjectId of the linetype to use.for Border.line
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if Successful
    /// </returns>
    Acad::ErrorStatus setBorderLineTypeId (const AcDbObjectId &objId);

protected:
    // For internal use only
    virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwner, AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;
    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwner, AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;
};

#endif //__ACDBDETAILVIEWSTYLE_H__
