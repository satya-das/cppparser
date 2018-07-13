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
#include "rxmember.h"

#define AXRES_RESOURCE_HINT 0
#define ACAXTLB_RESOURCE_HINT 1
#define ACAUTHENTITIESTLB_RESOURCE_HINT 2
#define ACOPMRES_RESOURCE_HINT 3
#define ACSCENERES_RESOURCE_HINT 4


class AcRxValue;
class AcRxValueType;
class AcRxClass;
class AcRxObject;
class AcRxAttributeCollection;
class AcRxPropertyBaseImp;
class AcRxValueIteratorImp;
class AcRxPropertyIteratorImp;
class AcRxPropertyQueryContextImp;
class AcRxPropertyQueryEngineImp;
class AcRxDictionaryPropertyImp;
class AcRxPropertyImp;
class AcRxCollectionPropertyImp;
class AcRxIndexedPropertyImp;

//*************************************************************************
// AcRxPropertyBase
//*************************************************************************
/// <summary>
/// This is the common base class for all the property class.
/// </summary>
///
class AcRxPropertyBase : public AcRxMember
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxPropertyBase, ACBASE_PORT);

    /// <summary>
    /// This method can be used to check if the property is a readonly property.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that has the property.
    /// </param>
    ///
    /// <returns> Returns true if the property is readonly, otherwise returns false</returns>
    ///
    ACBASE_PORT bool isReadOnly(const AcRxObject* pO) const;
protected:
    ACBASE_PORT ~AcRxPropertyBase();
    ACBASE_PORT AcRxPropertyBase(AcRxPropertyBaseImp*);
};

//*************************************************************************
// AcRxProperty
//*************************************************************************
/// <summary>
/// This is class encapsulates the property of an object. The class can be 
/// used to get and set a property value of an object.
/// </summary>
///
class AcRxProperty : public AcRxPropertyBase
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxProperty, ACBASE_PORT);

    /// <summary>
    /// The method can be used to get the property value from an object.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="value">
    /// Input reference to an AcRxValue object, to receive the value. 
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus getValue(const AcRxObject* pO, AcRxValue& value) const;

    /// <summary>
    /// The method can be used to set the property value to an object.
    ///
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value to be set. 
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus setValue(AcRxObject* pO, const AcRxValue& value) const;

protected:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT ~AcRxProperty();
    /// <summary>
    /// Protected constructor for derived class.
    /// </summary>
    ///
    /// <param name="name">
    /// Input the name of the property.
    /// </param>
    ///
    /// <param name="type">
    /// Const reference to the type of the property. 
    /// </param>
    ///
    /// <param name="owner">Optional. It can be used to set the owner of the property. 
    /// </param>
    ///
    ACBASE_PORT  AcRxProperty(const ACHAR* name, const AcRxValueType& type, const AcRxObject* owner=NULL) throw();

    /// <summary>
    /// Derived class can override this function to supply the property value.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="value">
    /// Input reference to an AcRxValue object, to receive the value. 
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subGetValue(const AcRxObject* pO, AcRxValue& value) const;

    /// <summary>
    /// Derived class can override this function to set the property value to the object.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value to be set.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subSetValue(AcRxObject* pO, const AcRxValue& value) const;

    friend class AcRxPropertyImp;
    friend class AcRxPropertyOverrule;
    AcRxProperty(AcRxPropertyImp*);
};

//*************************************************************************
// AcRxPropertyOverrule
//*************************************************************************
/// <summary>
/// Overrule that allows clients to modify the behavior of an existing property
/// at runtime.
/// </summary>
///
class AcRxPropertyOverrule : public AcRxMemberOverrule
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxPropertyOverrule, ACBASE_PORT);
    /// <summary>
    /// Allows overruling the getValue method of a property
    /// </summary>
    ///
    /// <param name="pProp">
    /// Overruled subject
    /// </param>
    /// <param name="pO">
    /// Object whose property is being retrieved
    /// </param>
    /// <param name="value">
    /// out parameter, value retrieved
    /// </param>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus getValue(const AcRxProperty* pProp, const AcRxObject* pO, AcRxValue& value) const ;
    /// <summary>
    /// Allows overruling the setValue method of a property
    /// </summary>
    ///
    /// <param name="pProp">
    /// Overruled subject
    /// </param>
    /// <param name="pO">
    /// Object whose property is being set
    /// </param>
    /// <param name="value">
    /// Value being set
    /// </param>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus setValue(const AcRxProperty* pProp, AcRxObject* pO, const AcRxValue& value) const ;
};

//*************************************************************************
// AcRxPromotingQueryContext
//*************************************************************************
/// <summary>
/// This class implements a context that can be passed to the query engine. 
/// If this context is passed to the query engine while querying properties, 
/// then the child properties will appear on the same level as the parent 
/// property.
/// </summary>
///
class AcRxPromotingQueryContext: public AcRxMemberQueryContext
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxPromotingQueryContext, ACBASE_PORT);
};

//*************************************************************************
// AcRxValueIterator
//*************************************************************************
/// <summary>
/// This class provides the ability to iterate through all the property 
/// values.
/// </summary>
///
class AcRxValueIterator : public Pimpl::ApiPart<void,AcRxValueIteratorImp>
{
public:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT virtual ~AcRxValueIterator();

    /// <summary>
    /// The function reports whether the iterator has iterated to the end. 
    /// </summary>
    ///
    /// <returns> 
    /// It returns true if it has reached the end, otherwise it returns false.
    /// </returns>
    ///
    ACBASE_PORT virtual bool done();

    /// <summary>
    /// Positions the iterator to the next value in the structure.
    /// </summary>
    ///
    /// <returns> 
    /// Returns true if and only if the iterator is not done.
    /// </returns>
    ///
    ACBASE_PORT virtual bool next();

    /// <summary>
    /// The function tries to return the value at the iterator's 
    /// current location.
    /// </summary>
    ///
    /// <returns> 
    /// Returns an AcRxValue if successful, otherwise it returns an empty value.
    /// </returns>
    ///
    ACBASE_PORT virtual AcRxValue current() const;
protected:

    /// <summary>
    /// Protected constructor for derived class.
    /// </summary>
    ///
    ACBASE_PORT AcRxValueIterator();
private:
    friend class AcRxValueIteratorImp;
    AcRxValueIterator(AcRxValueIteratorImp*);
};

//*************************************************************************
// AcRxCollectionProperty
//*************************************************************************
/// <summary>
/// This class encapsulates collection of properties.
/// </summary>
///
class AcRxCollectionProperty : public AcRxPropertyBase
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxCollectionProperty, ACBASE_PORT);

    /// <summary>
    /// The method returns a value iterator. 
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <returns> 
    /// Returns pointer to an AcRxValueIterator object if successful, otherwise returns NULL 
    /// </returns>
    ///
    ACBASE_PORT AcRxValueIterator* newValueIterator(const AcRxObject* pO) const;

    /// <summary>
    /// The method can be used to get the number of properties in the collection.
    ///
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="count">
    /// Input reference to an integer, to receive the value.
    /// </param>
    ///
    /// <returns>
    /// It returns true if the count can be returned, otherwise it returns false.
    /// </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus tryGetCount(const AcRxObject* pO, int& count) const;
protected:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT ~AcRxCollectionProperty();
    /// <summary>
    /// The derived class can override this method and return pointer to 
    /// AcRxValueIterator object.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <returns> Returns pointer to an AcRxValueIterator if successful, otherwise returns NULL </returns>
    ///
    ACBASE_PORT virtual AcRxValueIterator* subNewValueIterator(const AcRxObject* pO) const;

    /// <summary>
    /// The derived class can override this method and return the number of 
    /// properties in the collection.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="count">
    /// Input reference to an integer, to receive the value.
    /// </param>
    ///
    /// <returns> 
    /// It returns true if the count can be returned, otherwise it returns false.
    /// </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subTryGetCount(const AcRxObject* pO, int& count) const;

    /// <summary>
    /// Protected constructor for derived class.
    /// </summary>
    /// <param name="name">
    /// Input the name of the property.
    /// </param>
    ///
    /// <param name="type">
    /// Const reference to the type of the property. 
    /// </param>
    ///
    /// <param name="owner">
    /// Optional parameter that can be used to set the owner of the property. 
    /// </param>
    ///
    ACBASE_PORT AcRxCollectionProperty(const ACHAR* name, const AcRxValueType& type, const AcRxObject* owner = NULL);

    friend class AcRxCollectionPropertyImp;
    friend class AcRxCollectionPropertyOverrule;
    AcRxCollectionProperty(AcRxCollectionPropertyImp* pImp);
};

//*************************************************************************
// AcRxCollectionPropertyOverrule
//*************************************************************************
/// <summary>
/// Overrule that allows clients to modify the behavior of an existing property
/// at runtime.
/// </summary>
///
class AcRxCollectionPropertyOverrule : public AcRxMemberOverrule
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxCollectionPropertyOverrule, ACBASE_PORT);
    ACBASE_PORT virtual AcRxValueIterator* newValueIterator(const AcRxCollectionProperty* pProp, const AcRxObject* pO) const;
    ACBASE_PORT virtual Acad::ErrorStatus tryGetCount(const AcRxCollectionProperty* pProp, const AcRxObject* pO, int& count) const;
};
//*************************************************************************
// AcRxIndexedProperty
//*************************************************************************
/// <summary>
/// This class encapsulates collection of property values. The value can be 
/// queried using a specific index.
/// </summary>
///
class AcRxIndexedProperty : public AcRxCollectionProperty
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxIndexedProperty, ACBASE_PORT);

    /// <summary>
    /// The method can be used to get the property value at the specified index.
    ///
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index of the property value to get.
    /// </param>
    ///
    /// <param name="value">
    /// Input reference to an AcRxValue object, to receive the value. 
    /// </param>
    ///
    /// <returns> 
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus getValue(const AcRxObject* pO, int index, AcRxValue& value) const;

    /// <summary>
    /// The method can be used to set the property value at the specified index.
    ///
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index of the property value to set.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value to be set. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus setValue(AcRxObject* pO, int index, const AcRxValue& value) const;

    /// <summary>
    /// The method can be used to insert the property value at the specified index.
    ///
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index where the value needs to be inserted.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus insertValue(AcRxObject* pO, int index, const AcRxValue& value) const;

    /// <summary>
    /// The method can be used to remove the value from the collection.
    ///
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index where the value needs to be inserted.
    /// </param>
    ///
    /// <returns> 
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus removeValue(AcRxObject* pO, int index) const;
protected:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT ~AcRxIndexedProperty();
    /// <summary>
    /// Derived class will need to override this method to return the value
    /// at the specified index.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index where the value needs to be inserted.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    virtual Acad::ErrorStatus subGetValue(const AcRxObject* pO, int index, AcRxValue& value) const;

    /// <summary>
    /// Derived class will need to override this method to set the property value 
    /// at the specified index.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index of the property value to set.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value to be set. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subSetValue(AcRxObject* pO, int index, const AcRxValue& value) const;

    /// <summary>
    /// Derived class will need to override this method to insert the property value 
    /// at the specified index.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index where the value needs to be inserted.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value. 
    /// </param>
    ///
    /// <returns> 
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subInsertValue(AcRxObject* pO, int index, const AcRxValue& value) const;

    /// <summary>
    /// Derived class will need to override this method to remove the value 
    /// at the specified index.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="index">
    /// Input zero-based index where the value needs to be inserted.
    /// </param>
    ///
    /// <returns> 
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subRemoveValue(AcRxObject* pO, int index) const;

    /// <summary>
    /// Protected constructor for derived class.
    /// </summary>
    /// <param name="name">
    /// Input the name of the property.
    /// </param>
    ///
    /// <param name="type">
    /// Const reference to the type of the property. 
    /// </param>
    ///
    /// <param name="owner">
    /// Optional parameter that can be used to set the owner of the property. 
    /// </param>
    ///
    ACBASE_PORT AcRxIndexedProperty(const ACHAR* name, const AcRxValueType& type, const AcRxObject* owner= NULL);
private:
    friend class AcRxIndexedPropertyImp;
    AcRxIndexedProperty(AcRxIndexedPropertyImp* pImp);

};

//*************************************************************************
// AcRxIndexedProperty
//*************************************************************************
/// <summary>
/// This class encapsulates collection of property values. The value can be 
/// queried using a key associated with the value.
/// </summary>
///
class AcRxDictionaryProperty : public AcRxCollectionProperty
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxDictionaryProperty, ACBASE_PORT);

    /// <summary>
    /// The method gets the value associated with the specified key.
    ///
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="key">
    /// Input key of the value to get.
    /// </param>
    ///
    /// <param name="value">
    /// Input reference to an AcRxValue object, to receive the value. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus getValue(const AcRxObject* pO, const ACHAR* key, AcRxValue& value) const;

    /// <summary>
    /// The method sets the value associated with the specified key.
    ///
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="key">
    /// Input key of the value to set.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value to be set. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus setValue(AcRxObject* pO, const ACHAR* key, const AcRxValue& value) const;

protected:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT ~AcRxDictionaryProperty();
    /// <summary>
    /// Derived class will need to override this method to return the value
    /// associated with the key.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="key">
    /// Input key of the value to get.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subGetValue(const AcRxObject* pO, const ACHAR* key, AcRxValue& value) const;

    /// <summary>
    /// Derived class will need to override this method to set the property value 
    /// associated with the key.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, that the property is applicable.
    /// </param>
    ///
    /// <param name="key">
    /// Input key of the value to set.
    /// </param>
    ///
    /// <param name="value">
    /// Const reference to an AcRxValue object containing the value to be set. 
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subSetValue(AcRxObject* pO, const ACHAR* key, const AcRxValue& value) const;

    /// <summary>
    /// Protected constructor for derived class.
    /// </summary>
    /// <param name="name">
    /// Input the name of the property.
    /// </param>
    ///
    /// <param name="type">
    /// Const reference to the type of the property. 
    /// </param>
    ///
    /// <param name="owner">
    /// Optional parameter that can be used to set the owner of the property. 
    /// </param>
    ///
    ACBASE_PORT AcRxDictionaryProperty(const ACHAR* name, const AcRxValueType& type, const AcRxObject* owner=NULL);

private:
    friend class AcRxDictionaryPropertyImp;
    AcRxDictionaryProperty(AcRxDictionaryPropertyImp* pImp);
};
