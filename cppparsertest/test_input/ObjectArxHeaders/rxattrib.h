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

#pragma once
#include "acbasedefs.h"
#include "adesk.h"
#include "acadstrc.h"
#include "pimplapi.h"
#include "rxvalue.h"
#include "dbid.h"

class AcRxAttributeImp;
class AcRxAttributeCollectionImp;
class AcRxMember;
class AcRxPropertyBase;
//*************************************************************************
// AcRxAttribute
//*************************************************************************
/// <summary>
/// Abstract base class for all attribute classes
/// </summary>
///
class ADESK_NO_VTABLE AcRxAttribute : public Pimpl::ApiPart<AcRxObject, AcRxAttributeImp>
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxAttribute, ACBASE_PORT);

    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT virtual ~AcRxAttribute() = 0;
protected:
    ACBASE_PORT AcRxAttribute(AcRxAttributeImp*);
};


//*************************************************************************
// AcRxAttributeCollection
//*************************************************************************
/// <summary>
/// This class is a collection of AcRxAttribute objects
/// </summary>
///
class AcRxAttributeCollection : public Pimpl::ApiPart<void, AcRxAttributeCollectionImp>
{
public:
    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxAttributeCollection();

    /// <summary>
    /// This method returns the number of AcRxAttribute objects in the collection.
    /// </summary>
    ///
    /// <returns> The number of attributes in the collection </returns>
    ///
    ACBASE_PORT int count() const;

    /// <summary>
    /// This method returns a pointer to AcRxAttribute object at the passed 
    /// in index.
    /// </summary>
    ///
    /// <param name="index">
    /// Passed in index of interest
    /// </param>
    ///
    /// <returns> Returns a pointer to an AcRxAttribute object if successful, NULL on failure</returns>
    ///
    ACBASE_PORT const AcRxAttribute* getAt(int index) const;
    ACBASE_PORT AcRxAttribute* getAt(int index);
    /// <summary>
    /// This method returns a pointer to AcRxAttribute object of the type that 
    /// is passed. Using this method we can search for an atribute given the type.
    /// </summary>
    ///
    /// <param name="type">
    /// Input the class descriptor of the attribute.
    /// </param>
    ///
    /// <returns> Returns a pointer to an AcRxAttribute object if successful, NULL on failure </returns>
    ///
    ACBASE_PORT const AcRxAttribute* get(const AcRxClass* type) const;
    ACBASE_PORT AcRxAttribute* get(const AcRxClass* type);
    /// <summary>
    /// This method method adds the attribute object to the collection.
    ///
    /// </summary>
    ///
    /// <param name="attribute">
    /// Input attribute object to add to the collection
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful, otherwise, returns an AutoCAD error status</returns>
    ///
    ACBASE_PORT Acad::ErrorStatus add(const AcRxAttribute* attribute);

    /// <summary>
    /// This method method overides the attribute (adds it if it doesn't exist, or replaces if it already exists)
    ///
    /// </summary>
    ///
    /// <param name="attribute">
    /// Input attribute object to add to the collection
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful, otherwise, returns an AutoCAD error status</returns>
    ///
    ACBASE_PORT Acad::ErrorStatus override(const AcRxAttribute* attribute);

    /// <summary>
    /// This method method removes the attribute object from the collection.
    ///
    /// </summary>
    ///
    /// <param name="attribute">
    /// Input attribute object to be removed.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful, otherwise, returns an AutoCAD error status </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus remove(const AcRxAttribute* attribute);
};


//*************************************************************************
// AcRxResourceLoader
//*************************************************************************
/// <summary>
/// This is a protocol extension base class that is used to get the 
/// string from a resource.
/// </summary>
///
class ADESK_NO_VTABLE AcRxResourceLoader : public AcRxObject
{
    /// <summary>
    /// The derived class must override this method and return the resource string.
    ///
    /// </summary>
    ///
    /// <param name="id">
    /// Resource identifier
    /// </param>
    ///
    /// <param name="sourceHint">
    /// Caller may pass a hint that may be useful in locating the resource files, and 
    /// loading the resource.
    /// </param>
    ///
    /// <param name="result">
    /// Output reference to AcString object to receive the resource string. 
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    virtual Acad::ErrorStatus subLoadString(unsigned int id, unsigned int sourceHint, AcString& result) = 0;
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxResourceLoader, ACBASE_PORT);

    /// <summary>
    /// The function tries to load the resource string from the protocol extension 
    /// object attached to the input class.
    ///
    /// </summary>
    ///
    /// <param name="pClass">
    /// Input pointer to the AcRxObject that implements the AcRxResourceLoader protocol extension.
    /// </param>
    ///
    /// <param name="id">
    /// Resource identifier
    /// </param>
    ///
    /// <param name="sourceHint">
    /// Caller may pass a hint that may be useful in locating the resource files, and 
    /// loading the resource.
    /// </param>
    ///
    /// <param name="result">
    /// Output reference to AcString object to receive the resource string. 
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT static Acad::ErrorStatus loadString(const AcRxObject* pClass,unsigned int id, unsigned int sourceHint, AcString& result);
};

//*************************************************************************
// AcRxLocalizedNameAttribute
//*************************************************************************
/// <summary>
/// This class provides the resource identifier and the resource hint that 
/// is used to load the resource string. This attribute is used to get the 
/// localized name of an AcRxMember object.
/// </summary>
///
class AcRxLocalizedNameAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxLocalizedNameAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="id">
    /// Resource identifier
    /// </param>
    ///
    ACBASE_PORT AcRxLocalizedNameAttribute(unsigned int id);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="id">
    /// Resource identifier
    /// </param>
    ///
    /// <param name="sourceHint">
    /// Hint that may be useful in locating the resource file, and 
    /// loading the resource string.
    /// </param>
    ///
    ACBASE_PORT AcRxLocalizedNameAttribute(unsigned int id, unsigned int sourceHint);
    ACBASE_PORT static AcString getLocalizedName(const AcRxObject* pO);
    /// <summary>
    /// Returns the id passed to the constructor
    /// </summary>
    /// <returns> Returns the ide passed to the constructor </returns>
    //
    ACBASE_PORT unsigned int id() const;
    /// <summary>
    /// Returns the sourceHint passed to the constructor
    /// </summary>
    /// <seealso>AcRxResourceLoader</seealso>
    /// <returns> Returns the ide passed to the constructor </returns>
    //
    ACBASE_PORT unsigned int sourceHint() const;
    
};

//*************************************************************************
// AcRxLocalizedNameAttribute
//*************************************************************************
/// <summary>
/// This class provides the resource identifier and the resource hint that 
/// is used to load an alternative resource string. This attribute is used 
/// to get the localized name of an AcRxMember object. There are instances 
/// where a member name needs to be displayed using an alternate resource 
/// string. This attribute would be useful in those circumstances.
/// </summary>
///
class AcRxAlternateLocalizedNameAttribute : public AcRxLocalizedNameAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxAlternateLocalizedNameAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="id">
    /// Resource identifier
    /// </param>
    ///
    ACBASE_PORT AcRxAlternateLocalizedNameAttribute(unsigned int id);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="id">
    /// Resource identifier
    /// </param>
    ///
    /// <param name="sourceHint">
    /// Hint that may be useful in locating the resource file, and 
    /// loading the resource string.
    /// </param>
    ///
    ACBASE_PORT AcRxAlternateLocalizedNameAttribute(unsigned int id, unsigned int sourceHint);
};

//*************************************************************************
// AcRxUiPlacementAttribute
//*************************************************************************
/// <summary>
/// This class can be used to categorize a member object.
/// </summary>
///
class AcRxUiPlacementAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxUiPlacementAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="category">
    /// Name of the category
    /// </param>
    /// <param name="weight">
    /// The weight that is passed can be used to sort the members.
    /// </param>
    ///
    ACBASE_PORT AcRxUiPlacementAttribute(const ACHAR* category, unsigned int weight);

    /// <summary>
    /// Returns the name of the category
    /// </summary>
    /// <param name="member">
    /// Input pointer to a member object from which to get the category.
    /// </param>
    ///
    /// <returns> Returns const ACHAR* that points to the category name</returns>
    ///
    ACBASE_PORT static const ACHAR* getCategory(const AcRxObject* member);
    
    /// <summary>
    /// Returns the weight as specified by the AcRxUiPlacementAttribute
    /// for promoted properties it returns the calculated weight
    /// </summary>
    ///
    /// <param name="member">
    /// Input pointer to a member object from which to get the weight.
    /// </param>
    ///
    /// <returns> Returns the weight as a float </returns>
    ///
    ACBASE_PORT static float getWeight(const AcRxObject* member);
};

//*************************************************************************
// AcRxLMVAttribute
//*************************************************************************
/// <summary>
/// This class can be used to indicate that the member object should
/// be extracted for use in the LMV.
/// </summary>
class AcRxLMVAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxLMVAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxLMVAttribute();
};

//*************************************************************************
// AcRxDescriptionAttribute
//*************************************************************************
/// <summary>
/// This class can be used to describe a member object. The description can 
/// come from a resource file.
/// </summary>
///
class AcRxDescriptionAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDescriptionAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="desc">
    /// Description text
    /// </param>
    ///
    ACBASE_PORT AcRxDescriptionAttribute(const ACHAR* desc);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="id">
    /// Resource identifier of the description text
    /// </param>
    ///
    ACBASE_PORT AcRxDescriptionAttribute(unsigned int id);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="id">
    /// Resource identifier of the description text
    /// </param>
    ///
    /// <param name="sourceHint">
    /// Hint that may be useful in locating the resource file, and 
    /// loading the resource string.
    /// </param>
    ///
    ACBASE_PORT AcRxDescriptionAttribute(unsigned int id, unsigned int sourceHint);

    /// <summary>
    /// Returns the description string. The description string from a resource 
    /// file is returned, if the resource identifier is available.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input pointer to an AcRxObject (AcRxMember or AcRxClass) 
    /// for which to obtain the description
    /// </param>
    ///
    /// <returns> Returns the description as AcString </returns>
    ///
    ACBASE_PORT static AcString getDescription(const AcRxObject* pO);
    /// <summary>
    /// Returns the id passed to the constructor
    /// </summary>
    /// <returns> Returns the ide passed to the constructor </returns>
    //
    ACBASE_PORT unsigned int id() const;
    /// <summary>
    /// Returns the sourceHint passed to the constructor
    /// </summary>
    /// <seealso>AcRxResourceLoader</seealso>
    /// <returns> Returns the ide passed to the constructor </returns>
    //
    ACBASE_PORT unsigned int sourceHint() const;
};

typedef const AcRxPropertyBase* (*FindPropertyCallback)(const AcRxObject* pObject, const ACHAR* pszPropName);
typedef bool (*ConvertValueCallback)(const AcRxPropertyBase* pProperty, AcRxValue& value);

//*************************************************************************
// AcRxRefersToAttribute
//*************************************************************************
/// <summary>
/// This class can be used to provide additional information to describe the member. 
/// The common usecase is to set the path that refers to the container. For example 
/// the layer property can have the refers attribute set to /LayerTableId/Items, 
/// which indicates that it is an item in the LayerTable.
/// </summary>
///
class AcRxRefersToAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxRefersToAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="path">
    /// Input path.
    /// </param>
    ///
    ACBASE_PORT AcRxRefersToAttribute(const ACHAR* path);

    /// <summary>
    /// Returns the path that was specified in the constructor
    /// </summary>
    ///
    /// <returns> Returns const ACHAR* that points to the path </returns>
    ///
    ACBASE_PORT const ACHAR* path() const;

    /// <summary>
    /// Returns the last property in the path
    /// </summary>
    ACBASE_PORT static const AcRxPropertyBase* parseReference(const ACHAR* path, const AcRxObject* pObject, FindPropertyCallback find = NULL, ConvertValueCallback convert = NULL);
};

//*************************************************************************
// AcRxDisplayAsAttribute
//*************************************************************************
/// <summary>
/// This class can be used to inform that a member can be substituted 
/// by a different one. The common use case is to set this attribute on 
/// properties that return object id. A more meaningful property like the name 
/// can be displayed, instead of displaying the object id.
/// </summary>
///
class AcRxDisplayAsAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDisplayAsAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// Input member name
    /// </param>
    ///
    ACBASE_PORT AcRxDisplayAsAttribute(const ACHAR* name);

    /// <summary>
    /// Returns the name of the property that was specified in the constructor
    /// </summary>
    ///
    /// <returns> Returns const ACHAR* that points to the name </returns>
    ///
    ACBASE_PORT const ACHAR* path() const;

    /// <summary>
    /// Returns the display value of the property
    /// </summary>
    ///
    /// <param name="pAttr">
    /// Pointer to the AcRxDisplayAsAttribute instance
    /// </param>
    ///
    /// <param name="id">
    /// Input AcDbObjectId of entity to get property value from
    /// </param>
    ///
    /// <returns> Returns AcString that holds the value to display </returns>
    ///
    ACDB_PORT static AcString getDisplayValue(const AcRxDisplayAsAttribute* pAttr, const AcDbObjectId& id);
};

//*************************************************************************
// AcRxCOMAttribute
//*************************************************************************
/// <summary>
/// This class can be used to provide the COM name for a member incase it 
/// is different from the member name. This will be useful in areas of 
/// computation where a member is used instead of an equivalent COM property.
/// </summary>
///
class AcRxCOMAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxCOMAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// COM name
    /// </param>
    ///
    ACBASE_PORT AcRxCOMAttribute(const ACHAR* name);

    /// <summary>
    /// Returns the COM name that was specified in the constructor
    /// </summary>
    ///
    /// <returns> Returns const ACHAR* that points to the name </returns>
    ///
    ACBASE_PORT const ACHAR* name() const;
};

//*************************************************************************
// AcRxFilePathAttribute
//*************************************************************************
/// <summary>
/// This class can be used to indicate that the value of a member is a 
/// file path.
/// </summary>

class AcRxFilePathAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxFilePathAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxFilePathAttribute();
};

//*************************************************************************
// AcRxFlagsAttribute
//*************************************************************************
/// <summary>
/// This class can be used to indicate that the value of a member is 
/// a bitwise flag.
/// </summary>
///
class AcRxFlagsAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxFlagsAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxFlagsAttribute();
};

//*************************************************************************
// AcRxUnitTypeAttribute
//*************************************************************************
/// <summary>
/// This class can be used to indicate that the unit of a type
/// </summary>
///
class AcRxUnitTypeAttribute : public AcRxAttribute
{
public:
    enum UnitType
    {
        kUnitless           = 0,
        kDistance           = (0x1 << 0),
        kAngle              = (0x1 << 1),
        kArea               = (0x1 << 2),
        kVolume             = (0x1 << 3),
        kCurrency           = (0x1 << 4),
        kPercentage         = (0x1 << 5),
        kAngleNotTransformed = (0x1 << 16),
    };
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxUnitTypeAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="unitType">
    /// Input unit type
    /// </param>
    ///
    ACBASE_PORT AcRxUnitTypeAttribute(UnitType unitType);

    /// <summary>
    /// Returns the unit type that was specified in the constructor.
    /// </summary>
    ///
    /// <returns> Returns unit type as AcValue::UnitType </returns>
    ///
    ACBASE_PORT UnitType unitType() const;
};

//*************************************************************************
// AcRxGenerateDynamicPropertiesAttribute
//*************************************************************************
/// <summary>
/// This class can be used to indicate that the properties of an AcRxClass
/// or an individual AcRxProperty should have IDynamicProperty2 wrappers
/// generated for it whenever it is examined by COM property inspectors.
/// </summary>
class AcRxGenerateDynamicPropertiesAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxGenerateDynamicPropertiesAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxGenerateDynamicPropertiesAttribute();
};

//*************************************************************************
// AcRxUseDialogForReferredCollectionAttribute
//*************************************************************************
/// <summary>
/// This class can be used to indicate that a dialog is displayed for
/// the member.
/// </summary>
///
class AcRxUseDialogForReferredCollectionAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxUseDialogForReferredCollectionAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxUseDialogForReferredCollectionAttribute();
};

//*************************************************************************
//  AcRxUiCascadingContextMenuAttribute 
//*************************************************************************
/// <summary>
/// This class can be used to indicate that if a member is related to a 
/// context menu, the menu is cascading and may have sub-menus. Otherwise, 
/// the enum-based context menu generation logic will be used.
/// </summary>
///
class AcRxUiCascadingContextMenuAttribute: public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxUiCascadingContextMenuAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxUiCascadingContextMenuAttribute();
};

//*************************************************************************
// AcRxCumulativeAttribute
//*************************************************************************
/// <summary>
/// This class can be used to caculate the cumulative area for multiple selection.
/// </summary>
///
class AcRxCumulativeAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxCumulativeAttribute, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="type">
    /// Cumulative type, (area, length, etc)
    /// </param>
    ///
    ACBASE_PORT AcRxCumulativeAttribute(const ACHAR* type);

    /// <summary>
    /// Returns the type name that was specified in the constructor
    /// </summary>
    ///
    /// <returns> Returns const ACHAR* that points to the type </returns>
    ///
    ACBASE_PORT const ACHAR* type() const;
};

//*************************************************************************
// AcRxAffinityAttribute
//*************************************************************************
/// <summary>
/// This class can be used to identify the affinite and pass the array 
/// of AcRxObject into AcRxProperty::getValue as parameters.
/// </summary>
///
class AcRxAffinityAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxAffinityAttribute, ACBASE_PORT);
    
    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// Affinite name, (SelectionContext, etc)
    /// </param>
    ///
    ACBASE_PORT AcRxAffinityAttribute(const ACHAR* name);
    
    /// <summary>
    /// Returns the type name that was specified in the constructor
    /// </summary>
    ///
    /// <returns> Returns const ACHAR* that points to the name of affinite </returns>
    ///
    ACBASE_PORT const ACHAR* name() const;
};

class AcRxTypePromotionAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxTypePromotionAttribute, ACBASE_PORT);
    ACBASE_PORT AcRxTypePromotionAttribute(const ACHAR* properties);
    ACBASE_PORT const ACHAR* properties() const;
};

class AcRxDefaultValueAttribute : public AcRxAttribute
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDefaultValueAttribute, ACBASE_PORT);

    ACBASE_PORT AcRxDefaultValueAttribute(const AcRxValue& value);
    ACBASE_PORT const AcRxValue& value() const;
};
