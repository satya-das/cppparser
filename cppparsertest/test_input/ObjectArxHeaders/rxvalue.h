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
#include "acdbport.h"
#include "dbintar.h"
#include "rxvaluetype.h"
#include "rxmember.h"

template<typename ValueType>
ValueType* rxvalue_cast(AcRxValue* value) throw();
template<typename ValueType>
ValueType * rxenum_cast(AcRxValue * value) throw();

//*************************************************************************
// AcRxValue
//*************************************************************************
/// <summary>
/// This is a variant type, an instance of this class can hold any 
/// AcRxValueType.
/// </summary>
///
class AcRxValue
{
public:

    /// <summary>
    /// Default constructor, the value type is empty.
    /// </summary>
    ///
    AcRxValue() throw()
        :m_type(AcRxValueType::Desc<void>::value())
    {
        memset(&m_value,0,sizeof(m_value));
    }

    /// <summary>
    /// Copy constructor. Instantiates an object initialized to the same content as the input object.
    /// </summary>
    ///
    /// <param name="rhs">
    /// Another AcRxValue object.
    /// </param>
    ///
    AcRxValue(const AcRxValue& rhs) throw()
        :m_type(rhs.m_type)
    {
        init(rhs, false);
    }

    /// <summary>
    /// The object can be constructed using the type and value.
    /// For example, we can use this to create an enumerated type from an integer.
    ///
    /// </summary>
    ///
    /// <param name="type">
    /// The type of the object.
    /// </param>
    ///
    /// <param name="value">
    /// Input value of the object.
    /// </param>
    ///
    AcRxValue(const AcRxValueType& type, const AcRxValue& value) throw()
        :m_type(type)
    {
        init(value, false);
    }

    /// <summary>
    /// Assignment operator. Copies all the data from the input AcRxValue 
    /// object to this object.
    ///
    /// </summary>
    ///
    /// <param name="rhs">
    /// Input source AcRxValue object.
    /// </param>
    ///
    /// <returns>
    /// Returns const reference to this AcRxValue object.
    /// </returns>
    ///
    const AcRxValue& operator=(const AcRxValue& rhs) throw()
    {
        if (this == &rhs)
            return *this;
        if (type() != rhs.type()) 
        {
            if (!type().isBlittable())
                type().nonBlittable()->destruct(valuePtr());
            if (!isInlined() && rhs.isInlined())
                deallocate(m_value.m_ptr);
#pragma push_macro("new")
#undef new
            ::new ((Storage*)this) AcRxValue(rhs, !isInlined() && !rhs.isInlined()); 
#pragma pop_macro("new")
            return *this;
        }
        bool blittable = rhs.type().isBlittable();
        bool inlined = rhs.isInlined();
        if (blittable && inlined)
        {
            memcpy_s(this,sizeof(AcRxValue),&rhs,sizeof(AcRxValue));
            return *this;
        }
        /*
        inlined,non-blittable
        non-inlined, non-blittable
        non-inlined, blittable
        */
        if (inlined)
            type().nonBlittable()->assign(inlineValuePtr(),rhs.inlineValuePtr());
        else
            setNonInlineValue(rhs.nonInlineValuePtr(), blittable, true, true);
        return *this;
    }

    /// <summary>
    /// Destructor
    ///
    /// If the type is non-blittable then destructor of the type is called.
    /// </summary>
    ///
    ~AcRxValue() throw()
    {
        //if the type is non-blittable then we must call destructor
        if (!type().isBlittable())
            type().nonBlittable()->destruct(valuePtr());
        //finally free memory if necessary
        if (!isInlined())
            deallocate(m_value.m_ptr);
    }

    /// <summary>
    /// Returns the type of the value.
    /// </summary>
    ///
    /// <returns>
    /// Returns the type of the AcRxValue object.
    /// </returns>
    ///
    const AcRxValueType& type() const throw()
    {
        return m_type;
    }

    /// <summary>
    /// Returns true if the current value is empty.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the current value is empty; otherwise, returns false.
    /// </returns>
    ///
    bool isEmpty() const throw() {return *this == empty();}

    /// <summary>
    /// Returns a value that is empty.
    /// </summary>
    ///
    /// <returns>
    /// Returns const reference to an AcRxValue object that is empty.
    /// </returns>
    ///
    ACBASE_PORT static const AcRxValue& empty() throw();

    /// <summary>
    /// Returns true if the value is varying.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the value is varying; otherwise, returns false.
    /// </returns>
    ///
    bool isVaries() const throw() { return *this == varies();}

    /// <summary>
    /// Returns a value that has the type set to varies.
    /// </summary>
    ///
    /// <returns>
    /// Returns const reference to an AcRxValue object that has the type set to varies.
    /// </returns>
    ///
    ACBASE_PORT static const AcRxValue& varies() throw();

    /// <summary>
    /// This method can be used to obtain the string representation of the value.
    /// </summary>
    ///
    /// <param name="buffer">
    /// Output pointer to the buffer that receives the text.
    /// </param>
    ///
    /// <param name="sizeInACHARs">
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
    ACBASE_PORT int toString(ACHAR* buffer, size_t sizeInACHARs, AcRxValueType::StringFormat format=AcRxValueType::kStringFormatGlobal) const throw();

    /// <summary>
    /// Compares the value for equality with another AcRxValue.
    /// </summary>
    ///
    /// <param name="value">
    /// Input reference to an AcRxValue.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the values are same; otherwise, returns false.
    /// </returns>
    ///
    ACBASE_PORT bool operator==(const AcRxValue& value) const throw()
    {
        if (type()!=value.type())
            return false;
        return type().equalTo(valuePtr(), value.valuePtr());
    }


    /////////////////////////////////////////////////////////////////
    //MUST BE SPECIALIZED FOR NON BLITTABLE TYPES: 
    //The following 2 functions must be specialized for each supported 
    //type
    //
    //converting constructor: must be specialized for supported 
    //non-blittable types 

    /// <summary>
    /// Function template that can be used to create blittable types.
    /// This must be specialized for non-blittable types
    /// </summary>
    ///
    /// <param name="value">
    /// The type of the object.
    /// </param>
    ///
    template <typename ValueType>
    AcRxValue(const ValueType& value) throw()
        :m_type(AcRxValueType::Desc<ValueType>::value())
    {
        //this should have been specialized otherwise
        ACRXVALUE_ASSERT(m_type.isBlittable());
        initBlittable<sizeof(ValueType)<=24>(&value,sizeof(ValueType));
    }

    /// <summary>
    /// The function provides safe casting mechanism, returns NULL if the cast fails.
    /// </summary>
    ///
    /// <param name="value">
    /// Input pointer to the AcRxValue object.
    /// </param>
    ///
    /// <returns> Returns the object that was cast if successful; otherwise it returns NULL </returns>
    ///
    /// <remarks>
    /// Caller will need to check the return value to see if the cast was successful.
    /// </remarks>
    ///
    template<typename ValueType>
    friend ValueType* rxvalue_cast(AcRxValue* value) throw()
    {
        return value && AcRxValueType::Desc<ValueType>::value() == value->type()? (ValueType*)(value->valuePtr__<sizeof(ValueType)<=24>()) : 0;
    }

    /// <summary>
    /// The function provides safe casting mechanism for enum types, returns NULL if the cast fails.
    /// </summary>
    ///
    /// <param name="value">
    /// Input pointer to the AcRxValue object.
    /// </param>
    ///
    /// <returns> Returns the object that was cast if successful; otherwise it returns NULL </returns>
    ///
    /// <remarks>
    /// Caller will need to check the return value to see if the cast was successful.
    /// </remarks>
    ///
    template<typename ValueType>
    friend ValueType * rxenum_cast(AcRxValue * value) throw()
    {
        ACRXVALUE_ASSERT(value == NULL || value->isVaries() || value->type().isEnum());
        return value && 
               value->type().isEnum() && 
               AcRxValueType::Desc<ValueType>::value() == value->type().enumeration()->getAt(0).type() ? (ValueType*)(value->valuePtr__<sizeof(ValueType)<=24>()) : 0;
    }
    /////////////////////////////////////////////////////////////////
    //OPTIONALLY SPECIALIZED:
    //You might want to secialize the following templates (rare)
    /// <summary>
    /// The template function can be specialized if needed. Copies all the data from the input AcRxValue object to this object.
    /// </summary>
    ///
    /// <param name="rhs">
    /// Input source AcRxValue object.
    /// </param>
    ///
    /// <returns> Returns reference to this AcRxValue object. </returns>
    ///
     template<typename ValueType>
    AcRxValue& operator=(const ValueType & rhs) throw()
    {
        *this = AcRxValue(rhs);
        return *this;
    }

    /// <summary>
    /// The function provides safe casting mechanism, returns NULL if the cast fails.
    /// </summary>
    ///
    /// <param name="value">
    /// Input pointer to the AcRxValue object.
    /// </param>
    ///
    /// <returns> Returns the object that was cast if successful; otherwise it returns NULL </returns>
    ///
    /// <remarks>
    /// Caller will need to check the return value to see if the cast was successful.
    /// </remarks>
    ///
    template<typename ValueType>
    friend inline const ValueType * rxvalue_cast(const AcRxValue * value) throw()
    {
        return rxvalue_cast<ValueType>(const_cast<AcRxValue*>(value));
    }

    /// <summary>
    /// The function provides safe casting mechanism for enum types, returns NULL if the cast fails.
    /// </summary>
    ///
    /// <param name="value">
    /// Input pointer to the AcRxValue object.
    /// </param>
    ///
    /// <returns> Returns the object that was cast if successful; otherwise it returns NULL </returns>
    ///
    /// <remarks>
    /// Caller will need to check the return value to see if the cast was successful.
    /// </remarks>
    ///
    template<typename ValueType>
    friend inline const ValueType * rxenum_cast(const AcRxValue * value) throw()
    {
        return rxenum_cast<ValueType>(const_cast<AcRxValue*>(value));
    }

    /// <summary>
    /// The function can be used to get the AcRxValue from AcRxBoxedValue object.
    /// </summary>
    ///
    /// <returns> Returns pointer to AcRxValue object if successful; otherwise it returns NULL </returns>
    ///
    ACBASE_PORT static const AcRxValue* unbox(const AcRxObject* pO) throw();

    /// <summary>
    /// The function can be used to get the AcRxValue from AcRxBoxedValue object.
    /// </summary>
    ///
    /// <returns> Returns pointer to AcRxValue object if successful; otherwise it returns NULL </returns>
    ///
    ACBASE_PORT static AcRxValue* unbox(AcRxObject* pO) throw();

    /// <summary>
    /// The function can be used to obtain the AcRxEnumTag from this value. The 
    /// The value type must be an enum. 
    /// </summary>
    ///
    /// <returns> Returns pointer to the AcRxEnumTag object if successful, returns NULL on error. </returns>
    ///
    ACBASE_PORT const AcRxEnumTag* getEnumTag() const throw();

    /// <summary>
    /// The function can be used to serialize the AcRxValue out to a byte
    /// array.  The function delegates to the IAcRxNonBlittableType interface
    /// if the underlying type is not blittable.
    /// </summary>
    ///
    /// <param name="pByteArray"> 
    /// Returned pointer to buffer allocated by the function containing the serialized
    /// bytes of the value.
    /// </param>
    ///
    /// <param name="maxBytesToWrite">
    /// Input size of the pBytes array. On failure the function returns the number of 
    /// bytes needed in this parameter.
    /// </param>
    /// 
    /// <returns>
    /// Returns the number of bytes serialized out. The caller is responsible
    /// allocating the input array large enough to hold the value, and passing
    /// the size of the allocated array to this method. On error the method
    /// returns 0 and sets maxBytesToWrite to the size of the buffer required to
    /// hold the value.
    /// </returns>
    ACBASE_PORT size_t serializeOut(void* pBytes, size_t& maxBytesToWrite) const throw();

    /// <summary>
    /// The function can be used to serialize the AcRxValue in from a byte
    /// array.  The function delegates to the IAcRxNonBlittableType interface
    /// if the underlying type is not blittable. 
    /// </summary>
    ///
    /// <param name="pBytes">
    /// A pointer to the array of bytes to serialize the value from.
    /// </param>
    ///
    /// <param name="maxBytesToRead">
    /// The maximum number of bytest to read from pBytes. May be zero if the 
    /// size of the buffer is unknown.
    /// </param>
    ///
    /// <returns>
    /// Returns the number of bytes serialized in. 
    /// </returns>
    ACBASE_PORT size_t serializeIn(const void* pBytes, size_t maxBytesToRead) throw();

private:
#pragma region Implementation
    bool isInlined() const
    {
        return type().size() <= sizeof(m_value);
    }
    const void* nonInlineValuePtr() const { return m_value.m_ptr;}
    void* nonInlineValuePtr() { return m_value.m_ptr;}
    const void* inlineValuePtr() const {return &m_value;}
    void* inlineValuePtr() {return &m_value;}
    const void* valuePtr() const
    {
        if (isInlined())
            return inlineValuePtr();
        else
            return nonInlineValuePtr();
    }
    template <bool Inlined>
    void* valuePtr__();
    template <bool Inlined>
    void initBlittable(const void* value, size_t size);

    template<typename T, bool inlined>
    class InitNonBlittable
    {
    public:
        static void init(AcRxValue& rxValue, const T& value);
    };
    template<typename T>
    class InitNonBlittable<T, true>
    {
    public:
        static void init(AcRxValue& rxValue,const T& value);
    };
    template<typename T>
    class InitNonBlittable<T, false>
    {
    public:
        static void init(AcRxValue& rxValue,const T& value);
    };

    template <typename T>
    void initNonBlittable(const T& value)
    {
        InitNonBlittable<T, sizeof(value)<=sizeof(m_value) >::init(*this,value);
    }

    void init(const AcRxValue& rhs, bool realloc)
    {
        bool blittable = type().isBlittable();
        bool inlined = isInlined();
        if (blittable && inlined)
        {
            memcpy_s(&m_value,sizeof(m_value), &rhs.m_value,sizeof(m_value));
            return;
        }
        /*
        inlined,non-blittable
        non-inlined, non-blittable
        non-inlined, blittable
        */
        if (inlined)
            type().nonBlittable()->construct(inlineValuePtr(),rhs.inlineValuePtr());
        else
            setNonInlineValue(rhs.nonInlineValuePtr(), blittable, false, realloc);
    }
    void setNonInlineValue(const void* value, bool blittable, bool assignment, bool realloc)
    {
        ACRXVALUE_ASSERT(blittable == type().isBlittable());
        ACRXVALUE_ASSERT(!isInlined());
        unsigned int newSize = type().size();
        realloc = realloc || assignment;
        if (realloc)
            m_value.m_ptr = reallocate(newSize, m_value.m_ptr);
        else
            m_value.m_ptr = allocate(newSize);

        if (blittable)
            memcpy_s(nonInlineValuePtr(),newSize,value,newSize);
        else if (assignment)
            type().nonBlittable()->assign(nonInlineValuePtr(), value);
        else
            type().nonBlittable()->construct(nonInlineValuePtr(),value);
    }
    AcRxValue(const AcRxValue& rhs, bool realloc)
        :m_type(rhs.m_type)
    {
        init(rhs, realloc);
    }
    const AcRxValueType& m_type;
#ifndef _AC64
    int padding;    // just for padding on x86 Android, don't use it.
#endif
    union InlineStorage
    {
        double m_point[3];
        void* m_ptr;
        char  m_int8;
        short m_int16;
        int   m_int32;
        int64_t m_int64;
        float m_real32;
        double m_real64;
    } m_value;
    ACBASE_PORT void* allocate(size_t size) const;
    ACBASE_PORT void* reallocate(size_t size, void* p) const;
    ACBASE_PORT void  deallocate(void* p) const;

#pragma endregion
};
//each AcRxValue instance is 32 bytes long (on both 32 and 64 bit)

static_assert(sizeof(AcRxValue)==32, "Size mismatch.");

template<> 
struct AcRxValueType::Desc< const ACHAR* > 
{
    ACBASE_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<> 
struct AcRxValueType::Desc< const char* > 
{
    ACBASE_PORT static const AcRxValueType& value() throw();
    static void del();
};

template <>
inline AcRxValue::AcRxValue(const ACHAR* const & value) throw()
    :m_type(AcRxValueType::Desc<const ACHAR*>::value())
{
    memcpy_s(&m_value,sizeof(const ACHAR*), &value,sizeof(const ACHAR*));
}
template<>
inline AcRxValue& AcRxValue::operator=(const ACHAR* const & rhs) throw()
{
    *this = AcRxValue(rhs);
    return *this;
}
template<>
inline const ACHAR * const* rxvalue_cast<const ACHAR*>(const AcRxValue * value) throw()
{
    return value && AcRxValueType::Desc<const ACHAR*>::value() == value->type()? (const ACHAR* const*)&(value->m_value) : 0;
}

template<>
inline const void* rxvalue_cast<void>(const AcRxValue * value) throw()
{
    return value ? value->valuePtr() : 0;
}

template<>
inline void* AcRxValue::valuePtr__<true>()
{
    ACRXVALUE_ASSERT(isInlined());
    return inlineValuePtr();
}
template <>
inline void* AcRxValue::valuePtr__<false>()
{
    ACRXVALUE_ASSERT(!isInlined());
    return nonInlineValuePtr();
}

template <>
inline void AcRxValue::initBlittable<true>(const void* value, size_t size)
{
    ACRXVALUE_ASSERT(type().isBlittable());
    ACRXVALUE_ASSERT(isInlined());
    memcpy_s(inlineValuePtr(), size, value, size);
}
template <>
inline void AcRxValue::initBlittable<false>(const void* value, size_t size)
{
    ACRXVALUE_ASSERT(type().isBlittable());
    ACRXVALUE_ASSERT(!isInlined());
    m_value.m_ptr = allocate(size);
    memcpy_s(nonInlineValuePtr(),size,value,size);
}

template<typename T>
inline void AcRxValue::InitNonBlittable< T, true>::init(AcRxValue& rxValue, const T& value)
{
    //call global placement new defined above so that we can call copy constructor
    ::new ((Storage*)(rxValue.inlineValuePtr())) T(value);
}

template<typename T>
inline void AcRxValue::InitNonBlittable< T, false>::init(AcRxValue& rxValue, const T& value)
{
    rxValue.setNonInlineValue(&value,false,false, false);
}



//*************************************************************************
// AcRxBoxedValue
//*************************************************************************
/// <summary>
/// This is the base class for all boxed types. This class can be used to wrap 
/// the AcRxValue in an AcRxObject. There are instances where we need to treat the 
/// non-AcRxObject derived object as an AcRxObject. An example is querying the 
/// properties of AcGePoint3d which is a non-AcRxObject derived type. In this case we 
/// can box the AcGePoint3d value, pass the AcRxBoxedValue object that is obtained 
/// to the property engine to get its properties. 
/// </summary>
///
class AcRxBoxedValue : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxBoxedValue, ACBASE_PORT);
    
    /// <summary>
    /// Returns the value that is boxed. The derived class must implement this method.
    /// </summary>
    ///
    /// <returns>
    /// Returns const reference to an AcRxValue object.
    /// </returns>
    ///
    virtual const AcRxValue* value() const = 0;

    /// <summary>
    /// Returns the value that is boxed. The derived class must implement this method.
    /// </summary>
    ///
    /// <returns>
    /// Returns reference to an AcRxValue object.
    /// </returns>
    ///
    virtual AcRxValue* value() = 0;

    /// <summary>
    /// This function can be used to created heap resident instance of AcRxBoxedValue
    /// object.
    /// </summary>
    ///
    /// <param name="value">
    /// Reference to the AcRxValue object that needs to boxed.
    /// </param>
    ///
    /// <returns>
    /// Returns pointer to the AcRxBoxedValue object that was created on the heap.
    /// </returns>
    ///
    ACBASE_PORT static AcRxBoxedValue* newBoxedValueOnHeap(const AcRxValue& value);

    /// <summary>
    /// This function creates a clone of the object and returns a pointer to the clone. 
    /// If the function is not successful in creating the clone, then NULL is returned. 
    /// </summary>
    ///
    /// <returns>
    /// Returns pointer to the clone if successful; otherwise it returns NULL.
    /// </returns>
    ///
    ACBASE_PORT virtual AcRxObject*       clone() const ADESK_OVERRIDE;

    /// <summary>
    /// Copies the contents of other into this object, whenever feasible.
    /// </summary>
    ///
    /// <param name="other">
    /// Input pointer to object to copy from.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status.
    /// </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) ADESK_OVERRIDE;


    /// <summary>
    /// This method can be used to compare to boxed values.
    /// </summary>
    ///
    /// <param name="other">
    /// Input pointer to object to be compared with this object.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the values are same; otherwise, returns false.
    /// </returns>
    ///
    ACBASE_PORT virtual Adesk::Boolean    isEqualTo(const AcRxObject * other) const ADESK_OVERRIDE;

    /// <summary>
    /// For internal use only.
    /// </summary>
    ///
    ACBASE_PORT virtual AcRx::Ordering    comparedTo(const AcRxObject * other) const ADESK_OVERRIDE;

    ACBASE_PORT const AcRxObject* rxObject() const;
    ACBASE_PORT AcRxObject* rxObject();
};


//*************************************************************************
// AcRxBoxedValueOnStack
//*************************************************************************
/// <summary>
/// This class provides the functionality to create fast stack resident 
/// instances.
/// </summary>
///
class AcRxBoxedValueOnStack : public AcRxBoxedValue
{
    AcRxValue& m_value;
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxBoxedValueOnStack, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="value">
    /// Reference to the AcRxValue object that needs to boxed.
    /// </param>
    ///
    ACBASE_PORT AcRxBoxedValueOnStack(const AcRxValue& value);

    /// <summary>
    /// Returns the value that is boxed.
    /// </summary>
    ///
    /// <returns>
    /// Returns const reference to an AcRxValue object.
    /// </returns>
    ///
    ACBASE_PORT virtual const AcRxValue* value() const ADESK_OVERRIDE;

    /// <summary>
    /// Returns the value that is boxed.
    /// </summary>
    ///
    /// <returns>
    /// Returns reference to an AcRxValue object.
    /// </returns>
    ///
    ACBASE_PORT virtual AcRxValue* value() ADESK_OVERRIDE;
};

/////////////////////////////////////////////////////////////////////
//specializations
#pragma region AcString
class AcString;
//template<> 
//struct AcRxValueType::Desc<AcString> 
//{
//    ACBASE_PORT static const AcRxValueType& value() throw();
//    static void del();
//};
template<>
ACBASE_PORT AcRxValue::AcRxValue(const AcString& str) throw();
#pragma endregion


#pragma region AcGeMatrix3d
class AcGeMatrix3d;
template<> 
struct AcRxValueType::Desc<AcGeMatrix3d> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGeMatrix3d& m) throw();

template<>
ACDBCORE2D_PORT AcGeMatrix3d* rxvalue_cast<AcGeMatrix3d>(AcRxValue* value) throw();
#pragma endregion

#pragma region AcCmColor
class AcCmColor;

template<> 
struct AcRxValueType::Desc<AcCmColor> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcCmColor& clr) throw();
#pragma endregion

#pragma region AcDbDate
class AcDbDate;
template<> 
struct AcRxValueType::Desc<AcDbDate> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcDbDate& str) throw();
#pragma endregion

#pragma region AcUnderlayLayer
class AcUnderlayLayer;
template<> 
struct AcRxValueType::Desc<AcUnderlayLayer> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcUnderlayLayer& str) throw();
#pragma endregion

#pragma region AcGiMaterialColor
class AcGiMaterialColor;
template<> 
struct AcRxValueType::Desc<AcGiMaterialColor> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGiMaterialColor& clr) throw();
#pragma endregion

#pragma region AcGiMaterialMap
class AcGiMaterialMap;
template<> 
struct AcRxValueType::Desc<AcGiMaterialMap> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGiMaterialMap& clr) throw();
#pragma endregion

#pragma region AcDbSweepOptions
class AcDbSweepOptions;
template<> 
struct AcRxValueType::Desc<AcDbSweepOptions> 
{
    ACDB_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDB_PORT AcRxValue::AcRxValue(const AcDbSweepOptions& sweepOptions) throw();
#pragma endregion


#pragma region AcDbLoftOptions
class AcDbLoftOptions;
template<> 
struct AcRxValueType::Desc<AcDbLoftOptions> 
{
    ACDB_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDB_PORT AcRxValue::AcRxValue(const AcDbLoftOptions& loftOptions) throw();
#pragma endregion

#pragma region AcGiShadowParameters
class AcGiShadowParameters;
template<> 
struct AcRxValueType::Desc<AcGiShadowParameters> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGiShadowParameters& v) throw();
#pragma endregion

#pragma region AcGiSkyParameters
class AcGiSkyParameters;
template<> 
struct AcRxValueType::Desc<AcGiSkyParameters> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGiSkyParameters& v) throw();
#pragma endregion

#pragma region AcGiToneOperatorParameters
class AcGiToneOperatorParameters;
template<> 
struct AcRxValueType::Desc<AcGiToneOperatorParameters> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGiToneOperatorParameters& v) throw();
#pragma endregion

#pragma region AcGiPhotographicExposureParameters
class AcGiPhotographicExposureParameters;
template<> 
struct AcRxValueType::Desc<AcGiPhotographicExposureParameters> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGiPhotographicExposureParameters& v) throw();
#pragma endregion

#pragma region AcGiLightAttenuation
class AcGiLightAttenuation;
template<> 
struct AcRxValueType::Desc<AcGiLightAttenuation> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcGiLightAttenuation& v) throw();
#pragma endregion

#pragma region AcDbMText*
class AcDbMText;
template<> 
struct AcRxValueType::Desc<AcDbMText*> 
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(AcDbMText* const& pMText) throw();

template<>
ACDBCORE2D_PORT AcDbMText* const* rxvalue_cast<AcDbMText*>(const AcRxValue * value) throw();
#pragma endregion

#pragma region AcDbTableCellBlockReference
class AcDbTableCellBlockReference;
template<>
struct AcRxValueType::Desc<AcDbTableCellBlockReference>
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
	static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcDbTableCellBlockReference& tableCellBlkRef) throw();
#pragma endregion

#pragma region AcDbBlockParamValueSet
class AcDbBlockParamValueSet;
template<>
struct AcRxValueType::Desc<AcDbBlockParamValueSet>
{
    ACDB_PORT static const AcRxValueType& value() throw();
	static void del();
};

template<>
ACDB_PORT AcRxValue::AcRxValue(const AcDbBlockParamValueSet& blcParamValueSet) throw();
#pragma endregion

#pragma region AcDbBlkParamValueSetValuesArray
typedef AcArray<double> AcDbBlkParamValueSetValuesArray;
template<>
struct AcRxValueType::Desc<AcDbBlkParamValueSetValuesArray>
{
    ACDB_PORT static const AcRxValueType& value() throw();
	static void del();
};

template<>
ACDB_PORT AcRxValue::AcRxValue(const AcDbBlkParamValueSetValuesArray& blockParamValueSetArr) throw();
#pragma endregion

#pragma region AcDbIntArray
template<>
struct AcRxValueType::Desc<AcDbIntArray>
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
    static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcDbIntArray& intArr) throw();
#pragma endregion

#pragma region DimFillColor
struct DimFillColor;
template<>
struct AcRxValueType::Desc<DimFillColor>
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
	static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const DimFillColor& dimFillColor) throw();
#pragma endregion

#pragma region AcStringArray
typedef AcArray<AcString, AcArrayObjectCopyReallocator<AcString>> AcStringArray;
template<>
struct AcRxValueType::Desc<AcStringArray>
{
    ACDBCORE2D_PORT static const AcRxValueType& value() throw();
	static void del();
};

template<>
ACDBCORE2D_PORT AcRxValue::AcRxValue(const AcStringArray& stringArray) throw();
#pragma endregion