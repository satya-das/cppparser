//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   

#pragma once
#include "rxmember.h"
#include "rxvalue.h"
#include "AcArray.h"

template<typename ValueType>
class AcRxValueTypePOD : public AcRxValueType
{
public:
    /// <summary>
    /// Constructor. sizeof(ValueType) should be less than 256 bytes.
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the type.
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
    AcRxValueTypePOD(const ACHAR* name, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL):AcRxValueType(name,sizeof(ValueType), memberConstruct, userData) {}

    /// <summary>
    /// Constructor.
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
    AcRxValueTypePOD(const ACHAR* name, const IAcRxEnumeration& pEnum, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL):AcRxValueType(name,pEnum, sizeof(ValueType), memberConstruct, userData) {}
    
    /// <summary>
    /// Constructor.  This should only be used for ValueTypes that are references or pointers (i.e. sizeof(ValueType) == sizeof(void*)).
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
    AcRxValueTypePOD(const ACHAR* name, const IAcRxReferenceType& pRef, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL):AcRxValueType(name,pRef, sizeof(ValueType), memberConstruct, userData) {}
    
    virtual int subToString(const void* instance, ACHAR* buffer, size_t sizeInACHARs, AcRxValueType::StringFormat format) const ADESK_OVERRIDE;
    virtual bool subEqualTo(const void* a, const void* b) const ADESK_OVERRIDE;
};

#ifdef __GNUC__
template<typename ValueType>
int AcRxValueTypePOD<ValueType>::subToString(const void* instance, ACHAR* buffer, size_t sizeInACHARs, AcRxValueType::StringFormat format) const
{
    return -1;
}
template<typename ValueType>
bool AcRxValueTypePOD<ValueType>::subEqualTo(const void* a, const void* b) const
{
    return false;    
}
#endif

#pragma warning(push)
//Disable warning about 'unsafe' use of 'this' pointer. It is actually safe here because 
//we simply store the pointer and don't try to use it immediately.
//
#pragma warning(disable: 4355) 
template<typename ValueType>
class AcRxEnumType : public AcRxValueTypePOD<ValueType>, public IAcRxEnumeration
{
    AcArray<const AcRxEnumTag*> m_tags;
public:
    AcRxEnumType(const ACHAR* name, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL)
        :AcRxValueTypePOD<ValueType>(name,*this, memberConstruct, userData) {}
    ~AcRxEnumType()
    {
        for (int i=m_tags.length()-1;i>=0;i--)
            AcRxMember::deleteMember(m_tags[i]);
    }
    virtual int count() const ADESK_OVERRIDE
    {
        return m_tags.length();
    }
    virtual const AcRxEnumTag& getAt(int i) const ADESK_OVERRIDE
    {
        return *m_tags[i];
    }
    void append(AcRxEnumTag& tag)
    {
        m_tags.append(&tag);
        void acdbImpSetOwnerForEnumTag(const AcRxClass*, AcRxEnumTag*);
        acdbImpSetOwnerForEnumTag(this, &tag);
    }
#ifdef __GNUC__
    virtual int subToString(const void* instance, ACHAR* buffer, size_t sizeInACHARs, AcRxValueType::StringFormat format) const ADESK_OVERRIDE;
    virtual bool subEqualTo(const void* a, const void* b) const ADESK_OVERRIDE;
#endif    
};
#pragma warning(pop)

template<typename T>
class AcRxNonBlittableType : public AcRxValueType
{
    class NonBlittable : public IAcRxNonBlittableType
    {
        virtual void construct(void* dest, const void* source) const ADESK_OVERRIDE
        {
            ::new ((AcRxValue*)dest) T(*(T*)source);
        }
        virtual void assign(void* dest, const void* source) const ADESK_OVERRIDE
        {
            ((T*)dest)->operator =(*(T*)source);
        }
        virtual void destruct(const void* instance) const ADESK_OVERRIDE
        {
            ((T*)instance)->~T();
        }
    } m_nonBlittable;
    virtual int subToString(const void* instance, ACHAR* buffer, size_t sizeInACHARs, AcRxValueType::StringFormat format) const ADESK_OVERRIDE;
    virtual bool subEqualTo(const void* a, const void* b) const ADESK_OVERRIDE;
public:
    AcRxNonBlittableType(const ACHAR* name, const ACHAR* parent, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL):AcRxValueType(name, parent, m_nonBlittable,  sizeof(T), memberConstruct, userData) {}
    AcRxNonBlittableType(const ACHAR* name, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL):AcRxValueType(name,m_nonBlittable,  sizeof(T), memberConstruct, userData) {}
    AcRxNonBlittableType(const ACHAR* name, const IAcRxEnumeration& enumeration, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL):AcRxValueType(name, enumeration, m_nonBlittable, sizeof(T), memberConstruct, userData){}
    AcRxNonBlittableType(const ACHAR* name, const IAcRxObjectValue& rxObjValue, AcRxMemberCollectionConstructorPtr memberConstruct, void* userData = NULL):AcRxValueType(name, rxObjValue, m_nonBlittable, sizeof(T), memberConstruct, userData){}
};

