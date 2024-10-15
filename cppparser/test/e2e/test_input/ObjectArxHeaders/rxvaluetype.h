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
#include "acbasedefs.h" //for ACBASE_PORT
#include <memory.h> //for memcpy
#include <type_traits>
#include "acutasrt.h"
#include "rxclass.h"

class AcRxProperty;
class AcRxValue;
#ifdef NDEBUG
#define ACRXVALUE_ASSERT(x)
#else
#define ACRXVALUE_ASSERT(x) if (!(x)) acutAssertMessage(ACRX_T(#x), ACRX_T(__FILE__), __LINE__, 0 ); else
#endif
//*************************************************************************
// IAcRxNonBlittableType
//*************************************************************************
/// <summary>
/// The object of the types that cannot be copied using memory copy operation 
/// are non blittable types. An object that implements this interface will 
/// need to be passed in the AcRxValueType constructor for these types. This 
/// object will be used for copying the object.
/// </summary>
///
class IAcRxNonBlittableType
{
public:
    /// <summary>
    /// The function is called to constructs the non blittable type object 
    /// from the source object.
    /// </summary>
    ///
    /// <param name="dest">
    /// Input pointer that stores the destination buffer.
    /// </param>
    ///
    /// <param name="source">
    /// Input pointer to the source object to copy from.
    /// </param>
    ///
    virtual void construct(void* dest, const void* source) const = 0;

    /// <summary>
    /// The function is called to copy the source object to the destination object.
    /// </summary>
    ///
    /// <param name="dest">
    /// Input pointer to the destination buffer.
    /// </param>
    ///
    /// <param name="source">
    /// Input pointer to the source object to copy from.
    /// </param>
    ///
    virtual void assign(void* dest, const void* source) const = 0;

    /// <summary>
    /// This is called to destroy the non blittable type object.
    /// </summary>
    ///
    /// <param name="instance">
    /// Pointer to the object that was created using the construct function.
    /// </param>
    ///
    virtual void destruct(const void* instance) const =0;
};


//*************************************************************************
// IAcRxNonBlittableType
//*************************************************************************
/// <summary>
/// All the enumerated types will need to pass an object that implements 
/// this interface in the constructor of AcRxValueType. This 
/// interface will be used to query the enumerators contained in the 
/// enumeration.
/// </summary>
///
class AcRxEnumTag;
class IAcRxEnumeration
{
public:
    /// <summary>
    /// Returns the number of enumerators in the enumeration.
    /// </summary>
    ///
    /// <returns> Returns the number of enumerators in the enumeration </returns>
    ///
    virtual int count() const = 0;

    /// <summary>
    /// Returns the tag at the specified index.
    /// </summary>
    ///
    /// <param name="index">
    /// Input zero-based index of the property value to get.
    /// </param>
    ///
    /// <returns> Returns a reference to AcRxEnumTag object at the specified index.</returns>
    ///
    virtual const AcRxEnumTag& getAt(int index) const = 0;
};


//*************************************************************************
// IAcRxReferenceType
//*************************************************************************
/// <summary>
/// This is useful for objects that implement open/close protocol like the 
/// AcDbObject. Object that implement the open/close protocol can pass an 
/// object that implements this interface in the constructor of AcRxValueType.
/// This interface is useful to get the object from the AcRxValue. For example
/// we can use this interface to get the AcDbObject from the AcRxValue that 
/// contains an AcDbObjectId.
/// </summary>
///
class IAcRxReferenceType
{
public:
    enum OpenMode          { kForRead           = 0,
                            kForWrite          = 1,
                            kForNotify         = 2 };
    /// <summary>
    /// Returns the object that is dereferenced.
    /// </summary>
    ///
    /// <param name="value">
    /// Reference to an AcRxValue object, that is used for dereferencing the object.
    /// </param>
    ///
    /// <param name="mode">
    /// Input mode in which to open the object.
    /// </param>
    ///
    /// <returns> Returns the AcRxObject if successful, otherwise, returns NULL.</returns>
    ///
    virtual AcRxObject* beginDereferencing(const AcRxValue& value, OpenMode mode) const = 0;

    /// <summary>
    /// Closes the dereferenced object. This function must be called for 
    /// any dereferenced object. The dereferenced object is invalid after 
    /// calling this function, and it should not be used.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input pointer to the dereferenced AcRxObject object that needs to be closed.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    virtual Acad::ErrorStatus endDereferencing(AcRxObject* pO) const = 0;
};

class IAcRxObjectValue
{
public:
    virtual const AcRxObject* getRxObject(const AcRxValue& value) const = 0;
};
//*************************************************************************
// AcRxValueType
//*************************************************************************
/// <summary>
/// AcRxValueType is the runtime type descriptor for a type. The AcRxValue 
/// object can be queried for its type. The members of AcRxValueType can 
/// be used to get information of the type. 
/// </summary>
///
class AcRxValueType :public AcRxClass
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxValueType, ACBASE_PORT);

    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT ~AcRxValueType();

    /// <summary>
    /// Compares the value type for equality with another AcRxValueType.
    /// </summary>
    ///
    /// <param name="rhs">
    /// Input reference to an AcRxValueType.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the types are same; otherwise, returns false.
    /// </returns>
    ///
    bool operator==(const AcRxValueType& rhs) const
    {
        return this == &rhs;
    }

    /// <summary>
    /// Returns false if the objects are equal, true if they are not equal.
    /// </summary>
    ///
    /// <param name="rhs">
    /// Input reference to an AcRxValueType to be tested for inequality.
    /// </param>
    ///
    /// <returns>
    /// Returns false if the objects are equal, true if they are not equal.
    /// </returns>
    ///
    bool operator!=(const AcRxValueType& rhs) const
    {
        return this != &rhs;
    }

    /// <summary>
    /// Throws a bad cast exception.
    /// </summary>
    ///
    ACBASE_PORT static __declspec(noreturn) void badCast();

    /// <summary>
    /// Returns the size of the type.
    /// </summary>
    ///
    /// <returns>
    /// Returns the size of the type in bytes.
    /// </returns>
    ///
    unsigned int size() const { return m_size;}

    /// <summary>
    /// Determines if the type is blittable. Blittable types can be safely copied with memcpy.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the type is blittable; otherwise, returns false.
    /// </returns>
    ///
    bool isBlittable() const { return m_pNonBlittable==0;}

    /// <summary>
    /// Determines if the type is an enum.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the type is an enum; otherwise, returns false.
    /// </returns>
    ///
    bool isEnum() const {return m_pEnum!=0;}

    /// <summary>
    /// Determines if the type is a reference type. If it supports IAcRxReferenceType.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if it is a reference type; otherwise, returns false.
    /// </returns>
    ///
    bool isReference() const { return m_pRef!=0;}

    /// <summary>
    /// Returns the object that implements IAcRxNonBlittableType, for a non blittable type.
    /// </summary>
    ///
    /// <returns>
    /// Returns pointer to an object that implements IAcRxNonBlittableType, for a non blittable type.
    /// </returns>
    ///
    const IAcRxNonBlittableType* nonBlittable() const {return m_pNonBlittable;}

    /// <summary>
    /// Returns the object that implements IAcRxEnumeration, for an enum type.
    /// </summary>
    ///
    /// <returns>
    /// Returns pointer to an object that implements IAcRxEnumeration, for an enum type.
    /// </returns>
    ///
    const IAcRxEnumeration* enumeration() const {return m_pEnum;}

    /// <summary>
    /// Returns the object that implements IAcRxReferenceType, for a reference type.
    /// </summary>
    ///
    /// <returns>
    /// Returns pointer to an object that implements IAcRxReferenceType, for a reference type.
    /// </returns>
    ///
    const IAcRxReferenceType* reference() const {return m_pRef;}

    const IAcRxObjectValue* rxObjectValue() const {return m_pRxObjValue;}
    /// <summary>
    /// StringFormat enums can be used to specify as to how the string needs to be 
    /// formatted in the toString function. If the string needs to be formatted 
    /// depending on the current locale.
    /// </summary>
    enum StringFormat
    {
        kStringFormatGlobal = 0,
        kStringFormatCurrent = 1,
    };

    /// <summary>
    /// This method can be used to obtain the string representation of the value.
    /// Normally there is no need to call this method, instead the toString 
    /// method of the AcRxValue can be called.
    /// </summary>
    ///
    /// <param name="instance">
    /// Input pointer to the buffer that stores the AcRxValue. 
    /// </param>
    ///
    /// <param name="buffer">
    /// Output pointer to the buffer that receives the text.
    /// </param>
    ///
    /// <param name="buffer">
    /// Input maximum number of characters to copy to the buffer, including the NULL character.
    /// </param>
    ///
    /// <param name="format">
    /// This information is used while formatting the text, if the string needs to be formatted 
    /// depending on the current locale.
    /// </param>
    ///
    /// <returns>
    /// Returns the number of characters that was written.
    /// </returns>
    ///
    int toString(const void* instance, ACHAR* buffer, size_t sizeInACHARs, StringFormat format) const
    {
        ACRXVALUE_ASSERT(instance!=NULL);
        if (instance==NULL)
            return -1;
        ACRXVALUE_ASSERT((sizeInACHARs==0) == (buffer==NULL));
        if ((sizeInACHARs==0) != (buffer==NULL))
            return -1;
        //buffer==NULL && size==0 means that we should calculate the required length
        //of the buffer and return it
        return subToString(instance, buffer, sizeInACHARs, format);
    }

    /// <summary>
    /// This method is used to compare two values.
    /// Normally there is no need to call this method, instead the equality 
    /// operator of the AcRxValue should be used.
    /// </summary>
    ///
    /// <param name="a">
    /// Input pointer to the buffer that stores the AcRxValue.
    /// </param>
    ///
    /// <param name="b">
    /// Input pointer to the buffer that stores the AcRxValue. 
    /// </param>
    ///
    /// <returns>
    /// Returns true if the values are same; otherwise, returns false.
    /// </returns>
    ///
    bool equalTo(const void* a, const void* b) const
    {
        ACRXVALUE_ASSERT(a!=NULL);
        if (a==NULL)
            return false;
        ACRXVALUE_ASSERT(b!=NULL);
        if (b==NULL)
            return false;
        return subEqualTo(a, b);
    }

    /// <summary>
    /// This class MUST BE specialized for supported types. It provides mapping from
    /// C++ type to AcRxValueType.
    /// </summary>
    template<typename ValueType>
    struct Desc
    {
        static const AcRxValueType& value() throw();
        static void del();
    };
protected:

    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
    /// </param>
    ///
    /// <param name="name">
    /// Name of the parent type if applicable.
    /// </param>
    ///
    /// <param name="nonBlittable">
    /// Reference to an object that implements IAcRxNonBlittableType for non blittable types. The 
    /// derived class will need to pass this object for non blittable types.
    /// </param>
    ///
    /// <param name="size">
    /// Size in bytes of the value described by the type. Should be less than 256.
    /// </param>
    ///
    /// <param name="memberConstruct">
    /// Pointer to the callback function. The type can implement members, which can be returned 
    /// in the callback function.
    /// </param>
    ///
    /// <param name="userData">
    /// This is an optional user defined data that is passed to the AcRxMemberCollectionConstructorPtr
    /// call back function.
    /// </param>
    ///
    ACBASE_PORT AcRxValueType(const ACHAR* name, const ACHAR* parent, const IAcRxNonBlittableType& nonBlittable, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);

    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
    /// </param>
    ///
    /// <param name="size">
    /// Size in bytes of the value described by the type. Should be less than 256.
    /// </param>
    ///
    /// <param name="memberConstruct">
    /// Pointer to the callback function. The type can implement members, which can be returned 
    /// in the callback function.
    /// </param>
    ///
    /// <param name="userData">
    /// This is an optional user defined data that is passed to the AcRxMemberCollectionConstructorPtr
    /// call back function.
    /// </param>
    ///
    ACBASE_PORT AcRxValueType(const ACHAR* name, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void *userData = NULL);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
    /// </param>
    ///
    /// <param name="nonBlittable">
    /// Reference to an object that implements IAcRxNonBlittableType for non blittable types. The 
    /// derived class will need to pass this object for non blittable types.
    /// </param>
    ///
    /// <param name="size">
    /// Size in bytes of the value described by the type. Should be less than 256.
    /// </param>
    ///
    /// <param name="memberConstruct">
    /// Pointer to the callback function. The type can implement members, which can be returned 
    /// in the callback function.
    /// </param>
    ///
    /// <param name="userData">
    /// This is an optional user defined data that is passed to the AcRxMemberCollectionConstructorPtr
    /// call back function.
    /// </param>
    ///
    ACBASE_PORT AcRxValueType(const ACHAR* name, const IAcRxNonBlittableType& pNonBlittable, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
    /// </param>
    ///
    /// <param name="pEnum">
    /// Reference to an object that implements IAcRxEnumeration for enum types. The 
    /// derived class will need to pass this object for an enum type.
    /// </param>
    ///
    /// <param name="size">
    /// Size in bytes of the value described by the type.
    /// </param>
    ///
    /// <param name="memberConstruct">
    /// Pointer to the callback function. The type can implement members, which can be returned 
    /// in the callback function.
    /// </param>
    ///
    /// <param name="userData">
    /// This is an optional user defined data that is passed to the AcRxMemberCollectionConstructorPtr
    /// call back function.
    /// </param>
    ///
    ACBASE_PORT AcRxValueType(const ACHAR* name, const IAcRxEnumeration& pEnum, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
    /// </param>
    ///
    /// <param name="pEnum">
    /// Reference to an object that implements IAcRxEnumeration for enum types. The 
    /// derived class will need to pass this object for an enum type.
    /// </param>
    ///
    /// <param name="nonBlittable">
    /// Reference to an object that implements IAcRxNonBlittableType for non blittable types. The 
    /// derived class will need to pass this object for non blittable types.
    /// </param>
    ///
    /// <param name="size">
    /// Size in bytes of the value described by the type. Should be less than 256.
    /// </param>
    ///
    /// <param name="memberConstruct">
    /// Pointer to the callback function. The type can implement members, which can be returned 
    /// in the callback function.
    /// </param>
    ///
    /// <param name="userData">
    /// This is an optional user defined data that is passed to the AcRxMemberCollectionConstructorPtr
    /// call back function.
    /// </param>
    ///
    ACBASE_PORT AcRxValueType(const ACHAR* name, const IAcRxEnumeration& pEnum, const IAcRxNonBlittableType& pNonBlittable, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);
    ACBASE_PORT AcRxValueType(const ACHAR* name, const IAcRxEnumeration* pEnum, const IAcRxNonBlittableType* pNonBlittable, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);
    /// <summary>
    /// Constructor.  This should only be used for types that are references or pointers.
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
    /// </param>
    ///
    /// <param name="pRef">
    /// Reference to an object that implements IAcRxReferenceType for reference types. The 
    /// derived class will need to pass this object for a reference type.
    /// </param>
    ///
    /// <param name="size">
    /// Size in bytes of the value described by the type. This should be sizeof() a pointer.
    /// </param>
    ///
    /// <param name="memberConstruct">
    /// Pointer to the callback function. The type can implement members, which can be returned 
    /// in the callback function.
    /// </param>
    ///
    /// <param name="userData">
    /// This is an optional user defined data that is passed to the AcRxMemberCollectionConstructorPtr
    /// call back function.
    /// </param>
    ///
    ACBASE_PORT AcRxValueType(const ACHAR* name, const IAcRxReferenceType& pRef, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
    /// </param>
    ///
    /// <param name="pRef">
    /// Reference to an object that implements IAcRxReferenceType for reference types. The 
    /// derived class will need to pass this object for a reference type.
    /// </param>
    ///
    /// <param name="nonBlittable">
    /// Reference to an object that implements IAcRxNonBlittableType for non blittable types. The 
    /// derived class will need to pass this object for non blittable types.
    /// </param>
    ///
    /// <param name="size">
    /// Size in bytes of the value described by the type. Should be less than 256.
    /// </param>
    ///
    /// <param name="memberConstruct">
    /// Pointer to the callback function. The type can implement members, which can be returned 
    /// in the callback function.
    /// </param>
    ///
    /// <param name="userData">
    /// This is an optional user defined data that is passed to the AcRxMemberCollectionConstructorPtr
    /// call back function.
    /// </param>
    ///
    ACBASE_PORT AcRxValueType(const ACHAR* name, const IAcRxObjectValue& rxObjValue, const IAcRxNonBlittableType& pNonBlittable, unsigned int size, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL);
private:
    virtual int subToString(const void* instance, ACHAR* buffer, size_t sizeInACHARs, StringFormat format) const = 0;
    virtual bool subEqualTo(const void* a, const void* b) const = 0;
    AcRxValueType(const AcRxValueType& rhs);
    AcRxValueType& operator=(const AcRxValueType& rhs);
    //members declared on the API-side of Pimpl for performance reasons (so that they can be inlined)
    IAcRxNonBlittableType* m_pNonBlittable;
    IAcRxEnumeration* m_pEnum;
    IAcRxReferenceType* m_pRef;
    IAcRxObjectValue* m_pRxObjValue;
    void* m_unused1; //for future use
    unsigned int m_size;

};

//specialization for 'no type'
template<> struct AcRxValueType::Desc<void> 
{
    ACBASE_PORT static const AcRxValueType& value() throw();
    static void del();
};

class Storage; //this class is never defined, only used in placement new/delete

//protect against shenanigans
#pragma push_macro("new")
#undef new
//define global placement new  so that we can call the constructor 
//(C++ does not allow calling the ctor directly)
inline void* operator new(size_t size, Storage* loc) { ADESK_UNREFED_PARAM(size); return loc;} //Unreferenced parameter
#pragma pop_macro("new")

#pragma push_macro("delete")
#undef delete
inline void operator delete(void* p, Storage* loc) { ADESK_UNREFED_PARAM(p); (loc); } //Unreferenced parameters
#pragma pop_macro("delete")

