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

#ifndef ACDB_ANNOTATIONSCALE_H
#define ACDB_ANNOTATIONSCALE_H

#pragma once
#pragma pack(push, 8)

#include "dbObjContext.h"


class AcDbImpAnnotationScale;

////////////////////////////////////////////////////////////////////////
// class AcDbAnnotationScale
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class represents a single annotation scale defined in a drawing
/// in the form of an object context. Objects of this class are obtained 
/// from the "ACDB_ANNOTATIONSCALES" context collection. 
/// </summary>
///
class AcDbAnnotationScale : public AcDbObjectContext, public AcHeapOperators
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAnnotationScale);

    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    AcDbAnnotationScale ();

    /// <summary>
    /// Destructor.  Performs any necessary cleanup of the context data.
    /// </summary>
    ///
    virtual ~AcDbAnnotationScale ();

    /// <summary>
    /// The name of the annotation scale.
    /// </summary>
    /// 
    /// <param name="name">
    /// Output parameter containing the name of the annotation scale.
    /// </param>
    /// 
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    /// 
    /// <remarks>
    /// The name of an annotation scale may appear in user interface components
    /// visile to the user, and may change if the user renames the scale. 
    /// Applications should not identify contexts by name internally but should
    /// use the context ID, which is guaranteed to be unique and invariant over
    /// time. 
    /// </remarks>
    virtual Acad::ErrorStatus getName (AcString& name) const override;

    /// <summary>
    /// Sets the name of the annotation scale. 
    /// </summary>
    /// 
    /// <param name="name">
    /// New name of the annotation scale.
    /// </param>
    /// 
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    ///
    /// <remarks>
    /// Annotation scale names are not guaranteed to be unique.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus setName (const AcString& name) override;

    /// <summary>
    /// The unique annotation scale identifier
    /// </summary>
    ///
    /// <returns>
    /// Returns the annotation scale identifier.
    /// </returns>
    /// 
    /// <remarks>
    /// The unique identifier is invariant for the lifetime of this
    /// object and is unique amongst all annotation scale context instances.
    /// </remarks>
    ///

    virtual Adesk::LongPtr uniqueIdentifier () const override;

    /// <summary>
    /// The name of the annotation scale collection. 
    /// </summary>
    ///
    /// <returns>
    /// Returns the name of the annotation scale collection. 
    /// </returns>
    ///
    /// <remarks>
    /// Annotation scales are stored in an AcDbContextCollection named by the
    /// string returned by this method.
    /// </remarks>    
    ///
    virtual AcString collectionName () const override;

    /// <summary>
    /// Copies the annotation scale context data into this scale instance. 
    /// </summary>
    /// 
    /// <param name="pOther">
    /// A pointer to the annotation scale context object to copy.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::ErrorStatus Acad::eOk for success, otherwise an error
    /// return value Acad::eInvalidInput if the parameter passed is null or
    /// if the parameter passed is not of the correct type.
    /// </returns>
    ///
    virtual Acad::ErrorStatus copyFrom ( const AcRxObject *pOther) override;

    /// <summary>
    /// The paper units portion of the annotation scale. 
    /// </summary>
    ///
    /// <param name="dPaperUnits">
    /// The paper positive non-zero units value for the scale. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks> 
    /// Annotation scales are described as a ratio of paper units to drawing
    /// units. For example a scale of 1 inch = 1 foot has a paper units scale
    /// of 1.0, and a drawing units scale of 12.0, for an effective scale of
    /// 0.083.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus getPaperUnits (double& dPaperUnits) const;
    
    /// <summary>
    /// Sets the paper units portion of the annotation scale. 
    /// </summary>
    ///
    /// <param name="dPaperUnits">
    /// The new paper units value for the scale. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks> 
    /// The paper units must be positive and non-zero. Annotation scales are
    /// described as a ratio of paper units to drawing units. For example a
    /// scale of 1 inch = 1 foot has a paper units scale of 1.0, and a drawing
    /// units scale of 12.0, for an effective scale of 0.083.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus setPaperUnits (double dPaperUnits);

    /// <summary>
    /// The drawing units portion of the annotation scale. 
    /// </summary>
    ///
    /// <param name="dDrawingUnits">
    /// The positive, non-zero drawing units value for the scale. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks> 
    /// Annotation scales are described as a ratio of paper units to drawing
    /// units. For example a scale of 1 inch = 1 foot has a paper units scale
    /// of 1.0, and a drawing units scale of 12.0, for an effective scale of
    /// 0.083.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus getDrawingUnits (double&  dDrawingUnits) const;
    
    /// <summary>
    /// Sets the drawing units portion of the annotation scale. 
    /// </summary>
    ///
    /// <param name="dDrawingUnits">
    /// The drawing units value for the scale.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks> 
    /// The drawing units must be positive and non-zero. Annotation scales are
    /// described as a ratio of paper units to drawing units. For example a
    /// scale of 1 inch = 1 foot has a paper units scale of 1.0, and a drawing
    /// units scale of 12.0, for an effective scale of 0.083.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus setDrawingUnits (const double dDrawingUnits);

    /// <summary>
    /// Gets the annotation scale factor.
    /// </summary>
    ///
    /// <param name="dScale">
    /// The annotation scale factor.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks> 
    /// Annotation scales are described as a ratio of paper units to drawing
    /// units. For example a scale of 1 inch = 1 foot has a paper units scale
    /// of 1.0, and a drawing units scale of 12.0, for a scale factor of
    /// 0.083.
    /// </remarks>
    ///
    virtual Acad::ErrorStatus getScale (double& dScale) const;

    /// <summary>
    /// Determies whether the scale is temporarily stored in the drawing. 
    /// </summary>
    ///
    /// <param name="bTemporary">
    /// Return parameter indicating whether the scale object is temporarily
    /// stored in the drawing. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// The annotation scale collection in a drawing can contain temporary
    /// scale entries. These scale entries typically exist because attached
    /// XREF objects in the drawing have dependencies on scales that are not
    /// directly referenced by other objects in the drawing. Applications
    /// should not persist references to temporary scales, as other operations
    /// (for exampe detaching an XREF) may remove temporary scales from the
    /// collection. Temporary scales are not filed out to a drawing when it is
    /// saved. 
    /// </remarks>
    virtual Acad::ErrorStatus  getIsTemporaryScale (bool& bTemporary) const;

    /// <summary>
    /// Determies whether the given id matches the scale id. 
    /// </summary>
    ///
    /// <param name="id">
    /// id which is to be compared to the scale id
    /// </param>
    ///
    /// <returns>
    /// Return true if the input id matches the scale id
    /// </returns>
    ///
    /// <remarks>
    /// This function can be used in place of direct comparison of the
    /// uniqueIdentifier property to determine if two instances of the
    /// class are referring to the same underlying scale instance. When
    /// an XREF has been attached it is possible for two instances of this
    /// class to have different unique identifiers but refer to the same
    /// underlying scale instance.
    /// </remarks>
    virtual bool matchScaleId(Adesk::LongPtr id) const;
protected:
    AcDbImpAnnotationScale* mpImp;
    friend class AcDbSystemInternals;
    AcDbAnnotationScale ( bool );

};

// Notification of Annotation Scale change.
class ACDBCORE2D_PORT AcDbAnnotationScaleReactor: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAnnotationScaleReactor);

    virtual void annotationScaleChanged (const AcDbDatabase* pDb,
                                         const AcDbViewport* pVP, 
                                         const AcDbAnnotationScale* pScale,
                                         const bool bInitializing);
};

// Add an AcDbAnnotationScaleReactor reactor.
ACDBCORE2D_PORT bool acdbAddAnnotationScaleReactor(AcDbAnnotationScaleReactor *pReactor);

// Remove an AcDbAnnotationScaleReactor reactor.
ACDBCORE2D_PORT bool acdbRemoveAnnotationScaleReactor(AcDbAnnotationScaleReactor *pReactor);

#pragma pack(pop)

#endif
