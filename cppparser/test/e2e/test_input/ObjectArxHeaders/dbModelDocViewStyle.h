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
#ifndef __ACDBMODELDOCVIEWSTYLE_H__
#define __ACDBMODELDOCVIEWSTYLE_H__

#pragma once
#include "acdbport.h"
#include "dbmain.h"
#include "dbmtext.h"
#include "AcString.h"

class AcDbImpModelDocViewStyle;

class ACDBCORE2D_PORT AcDbModelDocViewStyle : public AcDbObject
{
protected:
    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    /// <remarks> 
    /// Default constructor is protected since AcDbModelDocViewStyle
    /// is abstract class. This constructor can be invoked only
    /// from constructor of derived class.
    /// </remarks>
    ///
    AcDbModelDocViewStyle();

public:
    ACDB_DECLARE_MEMBERS(AcDbModelDocViewStyle);

    /// <summary>
    /// Enumeration defining attachment point for label
    /// </summary>
    enum AttachmentPoint {
        kAboveView    = 0,
        kBelowView    = 1,
    };

    /// <summary>
    /// Enumeration defining label text alignment
    /// </summary>
    enum TextAlignment {
        kTextAlignmentLeft   = 0,
        kTextAlignmentCenter = 1,
        kTextAlignmentRight  = 2,
    };

    /// <summary>
    /// Default destructor.
    /// </summary>
    ///
    /// <remarks> 
    /// Default destructor.
    /// </remarks>
    ///
    virtual ~AcDbModelDocViewStyle() = 0;

    /// <summary>
    /// Get the name of AcDbModelDocViewStyle
    /// </summary>
    ///
    /// <param name="pszName">
    /// Output the name of AcDbModelDocViewStyle
    /// </param>
    ///
    /// <returns>
    /// Return Acae::eOk if Successful
    /// </returns>
    virtual Acad::ErrorStatus getName(ACHAR*& pszName) const final;     // deprecated

    /// <summary>
    /// Get the name of AcDbModelDocViewStyle
    /// </summary>
    ///
    /// <param name="strName">
    /// Output the name of AcDbModelDocViewStyle
    /// </param>
    ///
    /// <returns>
    /// Return Acae::eOk if Successful
    /// </returns>
    virtual Acad::ErrorStatus getName(AcString& strName) const;

    /// <summary>
    /// Set the name of AcDbModelDocViewStyle
    /// </summary>
    ///
    /// <param name="pszName">
    /// Input the name of AcDbModelDocViewStyle
    /// </param>
    ///
    /// <returns>
    /// Return Acae::eOk if Successful
    /// </returns>
    virtual Acad::ErrorStatus setName(const ACHAR * pszName);

    /// <summary>
    /// Return the pointer to a string containing the description of this view style.
    /// </summary>
    ///
    /// <returns>
    /// Return the pointer to a string containing the description of this view style.
    /// </returns>
    virtual const ACHAR* description(void) const;

    /// <summary>
    /// Get the description of AcDbModelDocViewStyle
    /// </summary>
    ///
    /// <param name="strDescription">
    /// Output the description of AcDbModelDocViewStyle
    /// </param>
    virtual void getDescription(AcString& strDescription) const;

    /// <summary>
    /// Set the pointer to a string containing the description of this view style.
    /// </summary>
    ///
    /// <param name="pszDescription">
    /// Input the pointer to a string containing the description of this view style.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus setDescription(const ACHAR * pszDescription);

    /// <summary>
    /// This function sets the object properties to the default values
    /// of the database indicated by pDb. If pDb == NULL, then the
    /// current database in the AutoCAD editor is used.
    /// </summary>
    ///
    /// <param name="pDb">
    /// Input database whose defaults will be used to set the values
    /// of the entity  
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    void setDatabaseDefaults(AcDbDatabase* pDb);

    /// <summary>
    /// Add this object into database.
    /// </summary>
    ///
    /// <param name="pDb">
    /// Pointer of the database which will hold the style
    /// </param>
    /// <param name="styleName">
    /// Name of the view style
    /// </param>
    /// <param name="viewStyleId">
    /// Output the AcDbObjectId of this object posted into database
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus postViewStyleToDb (AcDbDatabase* pDb, const ACHAR* styleName, AcDbObjectId &viewStyleId);

    /// <summary>
    /// Indicate whether properties were changed.
    /// </summary>
    ///
    /// <returns>
    /// Return true if properties were changed; otherwise, returns false.
    /// </returns>
    bool              isModifiedForRecompute() const;

    /// <summary>
    /// Returns default view name based on index for 1 it returns A, for 2 B, ...AA, AB, ....
    /// </summary>
    ///
    /// <param name="names">
    /// Returned available view names.
    /// </param>
    /// <param name="idx">
    /// Requested index of default name.
    /// </param>
    ///
    /// <returns>
    /// Return view name
    /// </returns>
    AcString          defaultViewName(int index) const;

    /// <summary>
    /// Checks whether label name is valid.
    /// </summary>
    ///
    /// <param name="pName">
    /// Label name to check.
    /// </param>
    ///
    /// <returns>
    /// Return true if name is valid label string
    /// </returns>
    bool              isViewNameValid(const ACHAR* pName) const;

    /// <summary>
    /// Calculate position of view label. This function receives bounding box
    /// of the view, attachment and offset and then calculate position of the text.
    /// </summary>
    ///
    /// <param name="offsetVector">Calculated offset vector.
    /// </param>
    /// <param name="textAlignment">text alignment to be set to view label.
    /// </param>
    /// <param name="attachment">Used attachment together with offset parameter
    /// defines position with respect to bounding box. 
    /// </param>
    /// <param name="offset">Offset for view lable together with attachment parameter
    /// defines position with respect to bounding box. 
    /// </param>
    /// <param name="minPt">Left lower corner of view's bounding box. 
    /// </param>
    /// <param name="maxPt">Right upper corner of view's bounding box. 
    /// </param>
    /// <returns>
    /// Offset position of view label defines relative position to alignment point
    /// on bounding box.
    /// </returns>
    static AcGePoint3d calculateViewLabelPosition  (AcGeVector2d &offsetVector,
                                                    AcDbMText::AttachmentPoint &textAlignment,
                                                    AcDbModelDocViewStyle::AttachmentPoint attachment,
                                                    double offset,
                                                    const AcGePoint3d &minPt,
                                                    const AcGePoint3d &maxPt);

    /// <summary>
    /// Set view label to initial position. This function receives bounding box
    /// of the view, attachment and offset and then calculate position of the text
    /// and sets the text to this position.
    /// </summary>
    ///
    /// <param name="pMText">Pointer to MText object to be positioned.
    /// </param>
    /// <param name="attachment">Used attachment together with offset parameter
    /// defines position with respect to bounding box. 
    /// </param>
    /// <param name="offset">Offset for view lable together with attachment parameter
    /// defines position with respect to bounding box. 
    /// </param>
    /// <param name="minPt">Left lower corner of view's bounding box. 
    /// </param>
    /// <param name="maxPt">Right upper corner of view's bounding box. 
    /// </param>
    /// <returns>
    /// Offset position of view label defines relative position to alignment point
    /// on bounding box.
    /// </returns>
    static AcGeVector2d setViewLabelPosition   (AcDbMText *pMText,
                                                AcDbModelDocViewStyle::AttachmentPoint attachment,
                                                double offset,
                                                const AcGePoint3d &minPt,
                                                const AcGePoint3d &maxPt);

    /// <summary>
    /// Updates view label's position. This function receives bounding box
    /// of the view, attachment and offset and then calculate position of the text
    /// and sets the text to this position.
    /// </summary>
    ///
    /// <param name="pMText">Pointer to MText object to be positioned.
    /// </param>
    /// <param name="attachment">Used attachment together with offset parameter
    /// defines position with respect to bounding box. 
    /// </param>
    /// <param name="offset">Offset for view lable together with attachment parameter
    /// defines position with respect to bounding box. 
    /// </param>
    /// <param name="minPt">Left lower corner of view's bounding box. 
    /// </param>
    /// <param name="maxPt">Right upper corner of view's bounding box. 
    /// </param>
    /// <returns>
    /// Offset position of view label defines relative position to alignment point
    /// on bounding box.
    /// </returns>
    static AcGeVector2d updateViewLabelPosition(AcDbMText *pMText,
                                                AcDbModelDocViewStyle::AttachmentPoint &attachment,
                                                const AcGePoint3d &minPt,
                                                const AcGePoint3d &maxPt);

protected:
    // For internal use only
    //
    virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwner, AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;
    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwner, AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;

private:
    friend class AcDbImpModelDocViewStyle;
};

// deprecated method. Please use the overload taking AcString & arg
inline Acad::ErrorStatus AcDbModelDocViewStyle::getName(ACHAR*& pName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbModelDocViewStyle::getName, pName);
}
#endif // __ACDBMODELDOCVIEWSTYLE_H__

