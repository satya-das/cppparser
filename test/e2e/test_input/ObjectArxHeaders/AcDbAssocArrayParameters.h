//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// CREATED BY: Sharad Jaiswal                            March 2010
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "rxobject.h"
#include "AcDbAssocArrayItem.h"

class AcDbArrayGripAppData;
class AcDbImpAssocArrayParameters;
class AcDbGeomRef;

/// <summary><para>
/// AcDbAssocArrayParameters class provides interface to manipulate array 
/// parameters. Its derived classes implement logic for providing array item
/// transforms as well as grip manipulation. AcDbAssocArrayActionBody owns
/// the object of this class and uses its methods to evaluate the entire array.
/// This class can also be used by UI module to access parameters or provide
/// jigging effect.
/// </para><para>
/// This class provides two kinds of parameters, value params and geometry 
/// params.
/// </para></summary>
/// <remarks> Deriving from this class is not supported. </remarks>
///
class ACDB_PORT AcDbAssocArrayParameters : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocArrayParameters);

    /// <summary> Default destructor. </summary>
    /// 
    virtual ~AcDbAssocArrayParameters(void);

    /// <summary><para> 
    /// Sets value, expression and evaluatorId for a given value action parameter
    /// If there is no expression for the parameter, the expression string and 
    /// the evaluatorId must be empty strings. 
    /// </para><para>
    /// If the user enters the expression in the form of "name=expression", the
    /// automatically created AcDbAssocVariable is assigned the given "name",
    /// apperars in the parameters manager and can be referenced by other 
    /// expressions as any other variable. If the expression is in the form
    /// "expression", an anonymous variable is created that cannot be referenced
    /// and is not visible in the parameters manager.
    /// </para><para>
    /// If a value parameter of the given name does not exist, it is created.
    /// Otherwise the existing value parameter is used.
    /// </para><para>
    /// This method does not do any validation on given value or expression
    /// so should not be directly used to modify array parameters.
    /// This method is for derived parameter classes to set their validated value.
    /// </para></summary>
    /// <param name="paramName">    The name of the value action parameter. </param>
    /// <param name="value">        The value to set. </param>
    /// <param name="expression">   The expression to set. </param>
    /// <param name="evaluatorId">  The evaluatorId to set. </param>
    /// <param name="errorMessage"> The returned error message for the individual expression. </param>
    /// <param name="pUnitType">    The unit type to set. If it is NULL, the default value is AcValue::kUnitless</param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParam(const AcString&        paramName,
                                    const AcDbEvalVariant& value,
                                    const AcString&        expression,
                                    const AcString&        evaluatorId,
                                    AcString&              errorMessage,
                                    AcValue::UnitType*     pUnitType = NULL);

    /// <summary> 
    /// Obtains value, expression and evaluatorId for a given value action param
    /// owned by this parameter. If there is no expression for a particular param,
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="paramName">   The name of the value action parameter. </param>
    /// <param name="value">       The returned value. </param>
    /// <param name="expression">  The returned expression. </param>
    /// <param name="evaluatorId"> The returned evaluatorId. </param>
    /// <param name="unitType">    The returned unit type. </param>
    /// <returns> 
    /// If a value action parameter with the given name is not found, returns Acad::eNotInGroup.
    /// </returns>
    ///
    Acad::ErrorStatus getValueParam(const AcString&  paramName,
                                    AcDbEvalVariant& value,
                                    AcString&        expression,
                                    AcString&        evaluatorId,
                                    AcValue::UnitType& unitType) const;

    /// <summary><para> 
    /// Sets a pointer to AcDbGeomRef for a given geometry action parameter
    /// such as AcDbAssocVertexActionParam, AcDbAssocPathActionParam or
    /// AcDbAssocFaceActionParam etc.
    /// </para><para>
    /// If a geometry parameter of the given name does not exist, it is created.
    /// Otherwise the existing geometry parameter is used.
    /// </para></summary>
    /// <param name="paramName"> The name of the geometry action parameter.
    /// </param>
    /// <param name="pGeomRef">  The geometry reference to set. </param>
    /// <param name="paramId">   The returned object id of geometry action 
    /// parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setGeomParam(const AcString&   paramName,
                                   const AcDbGeomRef* pGeomRef,
                                   AcDbObjectId&     paramId);

    /// <summary> 
    /// Obtains pointer to AcDbGeomRef for a given geometry action parameter
    /// owned by this parameter. 
    /// The returned AcDbGeomRef* should be deleted by caller after use.
    /// </summary>
    /// <param name="paramName"> The name of the geometry action parameter. 
    /// </param>
    /// <param name="pGeomRef">  The returned geometry reference. </param>
    /// <param name="paramId">   The returned object id of geometry action 
    /// parameter. </param>
    /// <returns> 
    /// If a geometry action parameter with the given name is not found, returns Acad::eNotInGroup.
    /// </returns>
    ///
    Acad::ErrorStatus getGeomParam(const AcString&   paramName,
                                   AcDbGeomRef*&     pGeomRef,
                                   AcDbObjectId&     paramId) const;

    /// <summary> 
    /// Returns names of all owned value action parameters. The names of the value
    /// action parameters are arbitrary case-sensitive strings but must be unique.
    /// </summary>
    /// <param name="paramNames"> Names of all owned value action parameters. </param>
    ///
    void ownedValueParamNames(AcArray<AcString>& paramNames) const;

    /// <summary> 
    /// Returns names of all owned geometry action parameters. The names of the geometry
    /// action parameters are arbitrary case-sensitive strings but must be unique.
    /// </summary>
    /// <param name="paramNames"> Names of all owned geometry action parameters. </param>
    ///
    void ownedGeomParamNames(AcArray<AcString>& paramNames) const;

    /// <summary> 
    /// Sets input AcDbAssocArrayActionBody as owner. When owner is not set the
    /// parameters are locally cached with this object. Once it is set all the
    /// value action params and geometry action params are transferred to owning
    /// action. Once owner is set, it can't be changed any more.
    /// </summary>
    /// <param name="pOwner"> The assoc array action to be set as owner. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setOwner(class AcDbAssocArrayActionBody* pOwner);

    /// <summary> 
    /// Gets the owner AcDbAssocArrayActionBody pointer for read.
    /// </summary>
    /// <returns> Pointer to AcDbAssocArrayActionBody. </returns>
    ///
    const AcDbAssocArrayActionBody* owner() const;

    /// <summary> 
    /// Gets the owner AcDbAssocArrayActionBody pointer for write.
    /// </summary>
    /// <returns> Pointer to AcDbAssocArrayActionBody. </returns>
    ///
    AcDbAssocArrayActionBody* owner();

    /// <summary> 
    /// Copies the parameters from other object. The input object must be of the 
    /// class.
    /// </summary>
    /// <param name="other"> The other input parameter to be copied from. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other);

    /// <summary> <para>
    /// Obtains list of items patterned by the set of owned parameters. Each
    /// parameters class uses its own logic based on owned value as well as 
    /// geometry parameters to define a set of items to be patterned as array.
    /// </para><para>
    /// The owning AcDbAssocArrayActionBody calls this method while evaluating
    /// the array to update transforms of each item in the array. The caller
    /// may pass its current list of items for update. The input list can be
    /// modified by this implementation to cater change in value parameters
    /// controlling number of items in various directions.
    /// </para></summary>
    /// <param name="items"> The updated list of items. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getItems(AcArray<AcDbAssocArrayItem*>& items) const = 0;

    /// <summary>
    /// Obtains position as well as orientation of an item at given spatial 
    /// index specified by the locator.
    /// </summary>
    /// <param name="locator">  The input item locator or spatial index. </param>
    /// <param name="position"> The returned positon of the item whose location is
    /// indicated by the input locator. </param>
    /// <param name="xform">    The returned orientation transform of the item.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getItemPosition(const AcDbItemLocator& locator, 
        AcGePoint3d& position, AcGeMatrix3d& xform) const = 0;


    /// <summary>
    /// Obtains canonical form of given item locator. The given locator may be
    /// counted wrt start or end, but the returned canonical form is always
    /// counted from start of the array pattern.
    /// </summary>
    /// <param name="locator">  The input item locator or spatial index. </param>
    /// <returns> Canonical form of input locator. </returns>
    ///
    virtual AcDbItemLocator getCanonicalForm(const AcDbItemLocator& locator) const = 0;
    
    /// <summary>
    /// Obtains grip data based on the grip mode. The default implementation 
    /// returns Acad::eNotImplementedYet error code. The UI code calls this
    /// method to get grip data for specific grip mode. Caller needs to delete
    /// allocated memory for pGrip.
    /// </summary>
    /// <param name="mode">  The input grip mode. </param>
    /// <param name="pGrip"> The returned grip data for input grip mode. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getGripPointAt(unsigned int mode, AcDbArrayGripAppData* &pGrip) const;

    
    /// <summary>
    /// Obtains all grips supported by this parameters class. This method will be 
    /// called when system wants to show grips of the array controlled by its
    /// owner array action. The default implementation doesn't return any grip.
    /// The caller needs to delete allocated memory for grips.
    /// </summary>
    /// <param name="grips"> The returned list of grips provided by this 
    /// parameters class. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getGripPoints(AcArray<AcDbArrayGripAppData*>& grips) const;

    /// <summary>
    /// This method is responsible for updating value action params based on
    /// a particular grip movement. Default implementation doesn't do anything.
    /// </summary>
    /// <param name="pGrip"> The input grip data that is being moved with given 
    /// offset. </param>
    /// <param name="offset"> The input offset vector with which grip is moved.
    /// </param>
    /// <param name="modificationBit"> The returned flag to indicate any
    /// parameter modification. If given offset doesn't modify this object the
    /// returned value will be zero. </param>
    /// <returns> Acad::eOwnerToBeTransformed if this call needs to be handled
    /// by owner, Acad::ErrorStatus otherwise. </returns>
    ///
    virtual Acad::ErrorStatus moveGripPointAt(const AcDbArrayGripAppData* pGrip,
                                              const AcGeVector3d &offset, 
                                              int& modificationBit);

    /// <summary>
    /// Obtains all stretch points supported by this parameters class. This method will be 
    /// called when system wants to stretch of the array controlled by its
    /// owner array action. The default implementation doesn't return any stretch points.
    /// </summary>
    /// <param name="stretchPoints"> The returned list of stretch points provided by this 
    /// parameters class. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus getStretchPoints(AcGePoint3dArray& stretchPoints);

protected:
    friend class AcDbImpAssocArrayParameters;
    explicit AcDbAssocArrayParameters(AcDbImpAssocArrayParameters* pSelf = NULL);
    AcDbImpAssocArrayParameters* mpSelf;
};
