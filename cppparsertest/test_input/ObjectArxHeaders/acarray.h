#ifndef AC_ACARRAY_H
#define AC_ACARRAY_H
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
// acarray.h
//
// DESCRIPTION:
//
// This file contains the definition for a dynamic array, called
// AcArray<T,R>, of objects of type "T".
//
// "Dynamic array" means that the array can grow without bounds,
// unlike declaring an array of objects of type "T" in the
// usual manner.  For example declaring "T myArray[10]"
// is limited to holding only ten entries.
//
// In order to use the class AcArray<T,R>, you need to understand
// a couple of simple, yet key, concepts:
//
//     1) The logical length of the array.
//            - How many entries have been placed into the array,
//              initially always zero.
//     2) The physical length of the array.
//            - How many entries the array will hold before it
//              automatically "grows" larger.
//     3) The grow length of the array.
//            - How much the array will grow when required.
//
// The physical length of the array is the actual length of the
// physically allocated, but perhaps not fully used, array.
// As a point of clarification, the size in bytes of the array
// buffer for an array called `myArray' would be:
//
//     sizeOf(T) * myArray.physicalLength().
//
// The physical length of the array can be zero or any positive
// integer.
//
// The logical length of the array (or just the "length()") reflects
// how many elements of T have been placed into the array
// with, for example, append() or insertAt().  Many member-functions
// are only valid for indices that are greater than or equal to
// zero AND less than length().  For example, indexing into the
// array with the operator[] is only valid for indices in this range.
//
// You can explicitly set the logical length() to any value and
// if the physical length is not large enough the array will grow to
// that length.  Note that if the logical length is explicitly reset
// to a larger value, then all the entries from the old length up
// to the new length may contain garbage values, therefor they must be
// initialized explicitly.
//
// The logical length is always less than or equal to the physical
// length.  NOTE that the array ALWAYS starts out empty, i.e., the
// length() always starts at zero regardless of the initial physical
// length.
//
// If you add an element to the array causing the logical length
// to become greater than the physical length of the array then
// additional space is allocated to increase the physical length.
// The amount of the increase is the larger of: the current grow
// length, or double the current logical length if the space used 
// is less than 64k bytes, or the number items that will grow
// the total space by an additional 64k bytes.
//
// The grow length must be a positive number, that is, zero is an illegal
// grow length.
//
#include "PAL/api/c11_Annex_K.h"
#include <memory>
#include <stdlib.h>
#include <algorithm>
#include <type_traits>
#include "adesk.h"

#ifdef ASSERT
#define AC_ARRAY_ASSERT ASSERT
#elif defined assert
#define AC_ARRAY_ASSERT assert
#elif defined _ASSERTE
#define AC_ARRAY_ASSERT _ASSERTE
#else
#define AC_ARRAY_ASSERT(T)
#endif

#pragma pack (push, 8)
#pragma push_macro("new")
#pragma push_macro("delete")
#undef new
#undef delete

#define ACARRAY_GROWTH_THRESHOLD 0x10000

// Helper function for asserting that copy/move params are valid.
// Shouldn't generate any code in production builds
template <class T> void AcArrayValidateParams(bool bSameBuffer,
                                              T* pDest, size_t nBufLen,
                                              const T * pSource, size_t nCount)
{
    ADESK_UNREFED_PARAM(pDest);
    ADESK_UNREFED_PARAM(nBufLen);
    ADESK_UNREFED_PARAM(pSource);
    ADESK_UNREFED_PARAM(nCount);
    AC_ARRAY_ASSERT(nCount >= 0);
    AC_ARRAY_ASSERT(nCount <= nBufLen);
    AC_ARRAY_ASSERT(nCount < 0x40000000);   // 1G sanity check
    if (bSameBuffer) {
        // if moving within same buffer, we expect we're moving items "down", as
        // with a remove.
        AC_ARRAY_ASSERT(pSource > pDest);
    }
    else {
        // otherwise there should be no overlap ever.
        AC_ARRAY_ASSERT(pSource >= pDest + nBufLen || (pDest >= pSource + nCount));
    }
}

// If the contained class T can be safely copied by the memcpy operator you
// should use the AcArrayMemCopyReallocator template with the array.
// If the class you intend to contain requires the use of operator=() for
// the copying during reallocation you should use AcArrayObjectCopyReallocator
//
// The default copy behaviour is based on the is_trivial trait of the type T
//

// This reallocator assumes that we can just do a memcpy (or memmove) for all
// copying and moving operations
template <class T> class AcArrayMemCopyReallocator
{
public:
    static void copyItems(T* pDest, size_t nBufLen, const T * pSource, size_t nCount)
    {
        AcArrayValidateParams<T>(false, pDest, nBufLen, pSource, nCount);
        if (nCount > 0)
           memcpy_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
    }
    static void moveItems(T* pDest, size_t nBufLen, T * pSource, size_t nCount,
                          bool bSameBuffer)
    {
        AcArrayValidateParams<T>(bSameBuffer, pDest, nBufLen, pSource, nCount);
        if (nCount > 0) {
            // If bSameBuffer is true, then we are moving elements left or right in a buffer,
            // and so we have to do that in a safe way without clobbering source data.
            if (bSameBuffer)
                memmove_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
            else
                memcpy_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
        }
    }
};

// This reallocator copies and moves actual T objects, so assgt operators are called.
template <class T> class AcArrayObjectCopyReallocator
{
public:
    // Copy from source to existing items, using copy assignment operator
    static void copyItems(T* pDest, size_t nBufLen, const T * pSource, size_t nCount)
    {
        AcArrayValidateParams<T>(false, pDest, nBufLen, pSource, nCount);
        while (nCount--) {
            *pDest = *pSource;
            pDest++;
            pSource++;
        }
    }

    // Move from source to initialized items, using move assignment operator
    static void moveItems(T* pDest, size_t nBufLen, T * pSource, size_t nCount,
                          bool bSameBuffer)
    {
        AcArrayValidateParams<T>(bSameBuffer, pDest, nBufLen, pSource, nCount);
        while (nCount--) {
            *pDest = std::move(*pSource);
            pDest++;
            pSource++;
        }
    }
};

// define allocator type for passing as default arg to the AcArray template
template<typename T, bool>
struct AcArrayItemCopierSelector;

template<typename T>
struct AcArrayItemCopierSelector<T, false>
{
    typedef AcArrayObjectCopyReallocator<T> allocator;
};

template<typename T>
struct AcArrayItemCopierSelector<T, true>
{
    typedef AcArrayMemCopyReallocator<T> allocator;
};

template <typename T, typename R = typename AcArrayItemCopierSelector<T, std::is_trivial<T>::value>::allocator  > class AcArray
{

public:
    AcArray(int initPhysicalLength = 0, int initGrowLength = 8);
    AcArray(const AcArray<T,R>&);
    AcArray(AcArray<T,R>&&);
    ~AcArray();

    typedef T Type;
    typedef R Allocator;
  
    // Useful for validating that an AcArray uses the efficient copy method.
    // E.g.: static_assert(AcArray<MyType>::eUsesMemCopy, "AcArray<MyType> uses slow copy!");
    enum {eUsesMemCopy = std::is_same<R, AcArrayMemCopyReallocator<T> >::value};

    // Assignment and == operators.
    //
    AcArray<T,R>&         operator =  (const AcArray<T,R>&);
    AcArray<T,R>&         operator =  (AcArray<T,R>&&);
    bool                operator == (const AcArray<T,R>&) const;

    // Indexing into the array.
    //
    T&                  operator [] (int);
    const T &           operator [] (int) const;

    // More access to array-elements.
    //
    const T &             at          (int index) const;
          T &             at          (int index);
    AcArray<T,R>&         setAt       (int index, const T& value);
    AcArray<T,R>&         setAll      (const T& value);
    T&                  first       ();
    const T &           first       () const;
    T&                  last        ();
    const T &           last        () const;

    // Adding array-elements with copy semantics.
    //
    int                   append      (const T& value);
    AcArray<T,R>&         append      (const AcArray<T,R>& array);
    AcArray<T,R>&         insertAt    (int index, const T& value);

    // Adding array-elements with move semantics.
    //
    int                   append      (T&& value);
    int                   appendMove  (T& value);
    AcArray<T,R>&         appendMove  (AcArray<T,R>& array);
    AcArray<T,R>&         insertAt    (int index, T&& value);
    AcArray<T,R>&         insertAtMove(int index, T& value);

    // Removing array-elements.
    //
    AcArray<T,R>&         removeAt    (int index);
    bool                  remove      (const T& value, int start = 0);
    AcArray<T,R>&         removeFirst ();
    AcArray<T,R>&         removeLast  ();
    AcArray<T,R>&         removeAll   ();
    AcArray<T,R>&         removeSubArray (int startIndex, int endIndex);

    // Query about array-elements.
    //
    bool                contains    (const T& value, int start = 0) const;
    bool                find        (const T& value, int& foundAt,
                                     int start = 0) const;
    int                 find        (const T& value) const;
    int                 findFrom    (const T& value, int start) const;

    // Array length.
    //
    int                 length      () const; // Logical length.
    bool                isEmpty     () const;
    int                 logicalLength() const;
    AcArray<T,R>&       setLogicalLength(int);
    int                 physicalLength() const;
    AcArray<T,R>&       setPhysicalLength(int);

    // Automatic resizing.
    //
    int                 growLength  () const;
    AcArray<T,R>&         setGrowLength(int);

    // Utility.
    //
    AcArray<T,R>&         reverse     ();
    AcArray<T,R>&         swap        (int i1, int i2);

    // Treat as simple array of T.
    //
    const T*            asArrayPtr  () const;
    T*                  asArrayPtr  ();

    // begin() and end() methods return iterators which allow things like
    // range based for loops, std::sort, std::for_each etc to use AcArrays
    // E.g.: for (const auto & elt : arr) sum += elt; 
    //
    T * begin() { return mpArray; }
    T * end() { return mpArray + mLogicalLen; }

    const T * begin() const { return mpArray; }
    const T * end() const { return mpArray + mLogicalLen; }

protected:
    T*                  mpArray;
    int                 mPhysicalLen;// Actual buffer length.
    int                 mLogicalLen;// Number of items in the array.
    int                 mGrowLen;   // Buffer grows by this value.

    void                insertSpace(int nIndex);
    void                copyOtherIntoThis(const AcArray<T,R>& otherArray);
    void                moveOtherIntoThis(AcArray<T,R>& otherArray);
    bool                isValid     (int) const;
};

#pragma pack (pop)

#ifdef GE_LOCATED_NEW
#error AcArray.h doesn't expect GE_LOCATED_NEW!
#endif

#pragma pack (push, 8)

// Inline methods.

template <class T, class R> inline bool
AcArray<T,R>::contains(const T& value, int start) const
{ return this->findFrom(value, start) != -1; }

template <class T, class R> inline int
AcArray<T,R>::length() const
{ return mLogicalLen; }

template <class T, class R> inline bool
AcArray<T,R>::isEmpty() const
{ return mLogicalLen == 0; }

template <class T, class R> inline int
AcArray<T,R>::logicalLength() const
{ return mLogicalLen; }

template <class T, class R> inline int
AcArray<T,R>::physicalLength() const
{ return mPhysicalLen; }

template <class T, class R> inline int
AcArray<T,R>::growLength() const
{ return mGrowLen; }

template <class T, class R> inline const T*
AcArray<T,R>::asArrayPtr() const
{ return mpArray; }

template <class T, class R> inline T*
AcArray<T,R>::asArrayPtr()
{ return mpArray; }

template <class T, class R> inline bool
AcArray<T,R>::isValid(int i) const
{ return i >= 0 && i < mLogicalLen; }

template <class T, class R> inline T&
AcArray<T,R>::operator [] (int i)
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline const T&
AcArray<T,R>::operator [] (int i) const
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline T&
AcArray<T,R>::at(int i)
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline const T&
AcArray<T,R>::at(int i) const
{ AC_ARRAY_ASSERT(this->isValid(i)); return mpArray[i]; }

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::setAt(int i, const T& value)
{ AC_ARRAY_ASSERT(this->isValid(i)); mpArray[i] = value; return *this; }

template <class T, class R> inline T&
AcArray<T,R>::first()
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[0]; }

template <class T, class R> inline const T&
AcArray<T,R>::first() const
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[0]; }

template <class T, class R> inline T&
AcArray<T,R>::last()
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[mLogicalLen-1]; }

template <class T, class R> inline const T&
AcArray<T,R>::last() const
{ AC_ARRAY_ASSERT(!this->isEmpty()); return mpArray[mLogicalLen-1]; }

template <class T, class R> inline int
AcArray<T,R>::append(const T& value)
{ insertAt(mLogicalLen, value); return mLogicalLen-1; }

template <class T, class R> inline int AcArray<T,R>::append(T && value)
{
    return this->appendMove(value);
}

template <class T, class R> inline int
AcArray<T,R>::appendMove(T& value)
{
    this->insertAtMove(mLogicalLen, value);
    return this->mLogicalLen - 1;
}

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::removeFirst()
{ AC_ARRAY_ASSERT(!isEmpty()); return removeAt(0); }

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::removeLast()
{ 
    AC_ARRAY_ASSERT(!isEmpty());
    if (!isEmpty())
        mLogicalLen--;
    return *this;
}

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::removeAll()
{
    this->setLogicalLength(0);
    return *this;
}

template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::setGrowLength(int glen)
{ AC_ARRAY_ASSERT(glen > 0); mGrowLen = glen; return *this; }

template < class T, class R > inline
AcArray< T, R > ::AcArray(int physicalLength, int growLength)
: mpArray(nullptr),
  mPhysicalLen(0),
  mLogicalLen(0),
  mGrowLen(growLength)
{
    // Replacing is_pod with is_trivial. is_trivial should be a superset of is_pod
    static_assert(std::is_trivial<T>::value || !std::is_pod<T>::value, "is_pod but not is_trivial?");
    AC_ARRAY_ASSERT(mGrowLen > 0);
    AC_ARRAY_ASSERT(physicalLength >= 0);
    if (physicalLength > 0)
        this->setPhysicalLength(physicalLength);
}

// Copy ctor. Similar to copy assignment operator.
//
template <class T, class R> inline
AcArray<T,R>::AcArray(const AcArray<T,R>& src)
: mpArray(nullptr),     // First initialize ourselves to empty
  mPhysicalLen(0),
  mLogicalLen(0),
  mGrowLen(src.mGrowLen)
{
    this->copyOtherIntoThis(src);
    }

// Move ctor
template <class T, class R> inline
AcArray<T,R>::AcArray(AcArray<T,R>&& src)
: mpArray(nullptr),     // First initialize ourselves to empty
  mPhysicalLen(0),
  mLogicalLen(0),
  mGrowLen(src.mGrowLen)
{
    this->moveOtherIntoThis(src);
}

// Dtor
template <class T, class R> inline
AcArray<T,R>::~AcArray()
{
    this->setPhysicalLength(0); // frees up buffer
}

// Copy assignment operator.Similar to copy ctor
// The grow length of this array is not affected by this operation.
//
template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::operator = (const AcArray<T,R>& src)
{
    if (this != &src)
        this->copyOtherIntoThis(src);
                    return *this;
            }

// Move assignment operator
template <class T, class R> inline AcArray<T,R>&
AcArray<T,R>::operator = (AcArray<T,R>&& src)
{
    if (this != &src) {
        this->setPhysicalLength(0);     // destruct this one
        this->moveOtherIntoThis(src);
    }
    return *this;
}


// The equal to operator.  The equal to operator compares
// the data in two arrays.  If the logical length of the
// two arrays are the same and the corresponding entries of
// the two arrays are equal, true is returned. Otherwise,
// false is returned.
//
template <class T, class R> bool
AcArray<T,R>::operator == (const AcArray<T,R>& cpr) const
{
    if (mLogicalLen == cpr.mLogicalLen) {
        for (int i = 0; i < mLogicalLen; i++)
            if (mpArray[i] != cpr.mpArray[i])
                return false;
        return true;
    }
    return false;
}

// Sets all the elements within the logical-length of the array,
// (that is, elements 0..length()-1), to `value'.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::setAll(const T& value)
{
    for (int i = 0; i < mLogicalLen; i++) {
        mpArray[i] = value;
    }
    return *this;
}

// Appends the `otherArray' to the end of this array.  The logical length of
// this array will increase by the logical length of the `otherArray'.
// Special case: appending to self, where otherArray == this. That works,
// because otherArray.mpArray gets updated by setPhysicalLength.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::append(const AcArray<T,R>& otherArray)
{
    const int nOrigLogLen = this->mLogicalLen;
    // Save other array's original logical length in case we are appending to
    // ourselves. Then grow our logical (and physical, if necessary) length
    const int nOrigOtherLogLen = otherArray.mLogicalLen;
    this->setLogicalLength(nOrigLogLen + nOrigOtherLogLen);

    R::copyItems(mpArray + nOrigLogLen, mLogicalLen - nOrigLogLen,
                 otherArray.mpArray, nOrigOtherLogLen);
    
        return *this;
}

// Helper meethod called from copy ctor and copy asst oper
// Doesn't mess with this->mGrowLen
// this->mpArray is re-used, if it's big enough
template <class T, class R> inline void
AcArray<T,R>::copyOtherIntoThis(const AcArray<T,R>& otherArray)
{
    AC_ARRAY_ASSERT(this != &otherArray);
    // Create or grow our buffer if necessary to hold other array's contents
    this->setLogicalLength(otherArray.mLogicalLen);
    // It's okay to call copyItems with zero count
    R::copyItems(mpArray, mPhysicalLen, otherArray.mpArray, mLogicalLen);
}

// Helper meethod called from move ctor, move asst oper and appendMove
// Doesn't mess with this->mGrowLen
// Assumes this->mpArray has been destroyed (or not created yet)
template <class T, class R> inline void
AcArray<T,R>::moveOtherIntoThis(AcArray<T,R>& otherArray)
{
    AC_ARRAY_ASSERT(this != &otherArray);
    AC_ARRAY_ASSERT(this->mpArray == nullptr);  // make sure no leaks
    this->mpArray = otherArray.mpArray;
    this->mLogicalLen = otherArray.mLogicalLen;
    this->mPhysicalLen = otherArray.mPhysicalLen;
    otherArray.mpArray = nullptr;
    otherArray.mLogicalLen = 0;
    otherArray.mPhysicalLen = 0;
    otherArray.mGrowLen = 8;    // back to the default? (doesn't matter)
}

template <class T, class R> AcArray<T,R>&
AcArray<T,R>::appendMove(AcArray<T,R>& otherArray)
{
    // Can't move into ourselves!
    AC_ARRAY_ASSERT(this != &otherArray);
    if (this != &otherArray) {
        if (this->mLogicalLen == 0) {
            // Special case - if this one is empty, then it can simply take
            // over the entire buffer of the other one.
            this->setPhysicalLength(0);
            this->moveOtherIntoThis(otherArray);
        }
        else {
            const int nOrigLogLen = this->mLogicalLen;
            // Grow our logical (and physical, if necessary) length
            this->setLogicalLength(nOrigLogLen + otherArray.mLogicalLen);
    
            R::moveItems(mpArray + nOrigLogLen, mLogicalLen - nOrigLogLen,
                 otherArray.mpArray, otherArray.mLogicalLen, /*bSameBuffer*/false);
        }
    }
    return *this;
}

// Inserts `value' at `index'.  The value formerly at `index'
// gets moved to `index+1',  `index+1 gets moved to `index+2' and so on.
// Note that insertAt(length(), value) is equivalent to append(value).
// The logical length of the array will increase by one.  If the physical
// length is not long enough it will increase by the grow length (with the
// usual caveat about insufficient memory).
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::insertAt(int index, const T& value)
{
    AC_ARRAY_ASSERT(index >= 0);
    AC_ARRAY_ASSERT(index <= mLogicalLen);
    AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
    if (index < 0 || index > mLogicalLen)
        return *this;   // error
    if (index == mLogicalLen && mLogicalLen < mPhysicalLen) {
        mpArray[index] = value; // it's safe to immediately assign it
        mLogicalLen++;
    }
    else {
        // make a copy in case value is coming from this array!
        // Must be non-const so we can move out of it
        T tmp(value);
        this->insertSpace(index);
        mpArray[index] = std::move(tmp);
    }
        return *this;
}

template <class T, class R> AcArray<T,R>&
AcArray<T,R>::insertAt(int index, T && value)   // move semantics
{
    return this->insertAtMove(index, value);
}

template <class T, class R> AcArray<T,R>&
AcArray<T,R>::insertAtMove(int index, T& value)
{
    AC_ARRAY_ASSERT(index >= 0);
    AC_ARRAY_ASSERT(index <= mLogicalLen);
    AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
    if (index < 0 || index > mLogicalLen)
        return *this;   // error
    // If appending, and we don't need to grow the buffer, then it's easy
    if (index == mLogicalLen && mLogicalLen < mPhysicalLen) {
        mpArray[index] = std::move(value);
        mLogicalLen++;
    }
    else {
        // tmp is non-const, so we can move out of it
        T tmp(std::move(value));        // save the value, in case it's in our buffer
        this->insertSpace(index);
        mpArray[index] = std::move(tmp);
    }
    return *this;
    }

// helper for the insertAt() and insertAtMove() methods.
// called when we need to slide items up to make a hole, or when we want to
// append and the buffer is already maxed out
template <class T, class R> void AcArray<T,R>::insertSpace(int nIndex)
{
    // Grow logical (and maybe physical) buffer
    this->setLogicalLength(mLogicalLen + 1);

    if (nIndex < mLogicalLen - 1) {     // if not inserting at end
        AC_ARRAY_ASSERT(mLogicalLen >= 0);
        // Note: we don't call moveItems() here, because we're sliding items up.
        // moveItems() assumes we're sliding down, such as during remove.
        // Here, we need to start moving from the end and work our way down
        T* p = mpArray + mLogicalLen - 1;       // start at last item in the array
        T* const pSpace = mpArray + nIndex;     // points to the new space
        AC_ARRAY_ASSERT(p >= pSpace);
        do {
            // slide the items up to make a hole at nIndex
            // note: we use move semantics even when called from normal insertAt
            *p = std::move(*(p-1));     // slide the items up
        } while (--p != pSpace);
    }
}

// Removes the element at `index'.  The logical length will
// decrease by one.  `index' MUST BE within bounds.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::removeAt(int index)
{
    AC_ARRAY_ASSERT(isValid(index));
    AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
    AC_ARRAY_ASSERT(!isEmpty());
    if (isEmpty() || !isValid(index))
        return *this;

    // Shift array elements to the left if needed.
    //
    if (index < mLogicalLen - 1) {
        R::moveItems(mpArray + index, mPhysicalLen - index,
                     mpArray + index + 1, mLogicalLen - 1 - index,
                     /*bSameBuffer*/true);
    }
    mLogicalLen--;
    return *this;
}

// Removes all elements starting with 'startIndex' and ending with 'endIndex'
// The logical length will decrease by number of removed elements.
// Both `startIndex' and 'endIndex' MUST BE within bounds.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::removeSubArray(int startIndex, int endIndex)
{
    AC_ARRAY_ASSERT(isValid(startIndex));
    AC_ARRAY_ASSERT(startIndex <= endIndex);

    if ( endIndex >= mLogicalLen - 1) {
        mLogicalLen = startIndex;       // deleting to the right end
        return *this;
    }

    // We didn't delete the right end, so shift remaining elements down
    //
    const int kNumToRemove = endIndex + 1 - startIndex;
    const int kNumToShift = mLogicalLen - 1 - endIndex;
    AC_ARRAY_ASSERT(kNumToShift >= 1);
    R::moveItems(mpArray + startIndex, mPhysicalLen - startIndex,
                 mpArray + endIndex + 1, kNumToShift,
                 /*bSameBuffer*/true);
    mLogicalLen -= kNumToRemove;
    return *this;
}

// Returns true if and only if the array contains `value' from
// index `start' onwards.  Returns, in `index', the first location
// that contains `value'.  The search begins at position `start'.
// `start' is supplied with a default value of `0', i.e., the
// beginning of the array.
//
template <class T, class R> bool
AcArray<T,R>::find(const T& value, int& index, int start) const
{
    const int nFoundAt = this->findFrom(value, start);
    if (nFoundAt == -1)
        return false;
    index = nFoundAt;
    return true;
}

template <class T, class R> int
AcArray<T,R>::find(const T& value) const
{
    return this->findFrom(value, 0);   // search from the beginning
}

template <class T, class R> int
AcArray<T,R>::findFrom(const T& value, int start) const
{
    AC_ARRAY_ASSERT(start >= 0);
    if (start < 0)
        return -1;
    for (int i = start; i < this->mLogicalLen; i++) {
        if (mpArray[i] == value)
            return i;
    }
    return -1;
}

// Allows you to set the logical length of the array.
// If you try to set the logical length to be greater than
// the physical length, then the array is grown to a
// reasonable size (thus increasing both the logical length
// AND the physical length).
// Also, the physical length will grow in growth length
// steps.
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::setLogicalLength(int n)
{
    AC_ARRAY_ASSERT(n >= 0);
    if (n < 0)
        n = 0;  // avoid going negative
    AC_ARRAY_ASSERT(n < 0x40000000);    // 1G sanity check
    if (n > mPhysicalLen) {

        const int growth = (mPhysicalLen * sizeof(T)) < ACARRAY_GROWTH_THRESHOLD ?
            mPhysicalLen : ACARRAY_GROWTH_THRESHOLD / sizeof(T);

        int minSize = mPhysicalLen + std::max<int>(growth, mGrowLen);
        if ( n > minSize)
            minSize = n;
        setPhysicalLength(minSize);
    }
    mLogicalLen = n;
    AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
    return *this;
}

// Grows or shrinks the physical buffer by allocating a new buffer (if new size
// is not zero) and deleting the old buffer.
// Reduces logical length if it was previously > the new physical length.
// Uses move semantics to move old cells to corresponding new cells
// Uses placement new to initialize new cells above previous buffer length
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::setPhysicalLength(int n)
{
    AC_ARRAY_ASSERT(mPhysicalLen >= mLogicalLen);
    AC_ARRAY_ASSERT((mPhysicalLen == 0) == (mpArray == nullptr));
    AC_ARRAY_ASSERT(n >= 0);
    AC_ARRAY_ASSERT(n < 0x40000000);    // 1G sanity check
    if (n == mPhysicalLen || n < 0)
        return *this;   // nothing to do

    T* pOldArray = mpArray;
    const size_t nOldLen = mPhysicalLen;

    mPhysicalLen = n;   // could be growing or shrinking
    mpArray = nullptr;

    if (mPhysicalLen < mLogicalLen)
        mLogicalLen = mPhysicalLen;     // shrinking the array

    if (mPhysicalLen != 0) {
        // Allocate the new physical memory buffer.
        // This can cause an exception or return null, depending on set_new_handler 
        mpArray = static_cast<T *>(::operator new(sizeof(T) * mPhysicalLen));
        AC_ARRAY_ASSERT(mpArray != nullptr);
        if (mpArray == nullptr) {
            // If allocation failed, then set array to empty
            // Should we restore the previous buffer ptr and length values instead?
            mPhysicalLen = 0;
            mLogicalLen = 0;
        }
        else {
            // First do a placement new to initialize the new array items to
            // default value.
            // This should not generate any code if T doesn't have a default ctor
            // Note we don't say new(&mpArray[i]) because T may have an & operator
            // such as if it's a smart ptr class. See tfs bug 68838
            T *pNewBuf = mpArray;
            for (int i = 0; i < mPhysicalLen; i++, pNewBuf++)
                ::new(pNewBuf) T;       // placement new: calls default ctor

            // Now move the old values from the old buf to the new buf
            R::moveItems(mpArray, mPhysicalLen, pOldArray, mLogicalLen,
                         /*bSameBuffer*/false);   // move items (if any) to new buf
        }
    }

    // This for loop should not generate any code if T doesn't have a dtor
    for (size_t i = 0; i < nOldLen; i++)
        (pOldArray + i)->~T();   // placement delete: call the dtor

    // now free the raw memory
    ::operator delete(static_cast<void *>(pOldArray));

    return *this;
}

// Reverses the order of the array.  That is if you have two
// arrays, `a' and `b', then if you assign `a = b' then call
// `a.reverse()' then a[0] == b[n], a[1] == b[n-1],... a[n] == b[0].
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::reverse()
{
    for (int i = 0; i < mLogicalLen/2; i++) {
        // tmp is non-const, so we can move out of it
        T tmp = std::move(mpArray[i]);
        mpArray[i] = std::move(mpArray[mLogicalLen - 1 - i]);
        mpArray[mLogicalLen - 1 - i] = std::move(tmp);
    }
    return *this;
}

// Swaps the elements in `i1' and `i2'.
//
template <class T, class R> AcArray<T,R>&
AcArray<T,R>::swap(int i1, int i2)
{
    AC_ARRAY_ASSERT(isValid(i1));
    AC_ARRAY_ASSERT(isValid(i2));

    if (i1 == i2) return *this;

    // tmp is non-const, so we can move out of it
    T tmp = std::move(mpArray[i1]);
    mpArray[i1] = std::move(mpArray[i2]);
    mpArray[i2] = std::move(tmp);
    return *this;
}

// Returns true if and only if `value' was removed from the array from
// position `start' onwards.  Only the first occurrence of `value'
// is removed.  Calling this function is equivalent to doing a "find(),
// then "removeAt()".
//
template <class T, class R> bool
AcArray<T,R>::remove(const T& value, int start)
{
    const int i = this->findFrom(value, start);
    if (i == -1)
        return false;
    this->removeAt(i);
    return true;
}

#include "acarrayhelper.h"

#ifdef _Ac_String_h_
typedef
AcArray< AcString, AcArrayObjectCopyReallocator< AcString > > AcStringArray;
#endif


#pragma pop_macro("new")
#pragma pop_macro("delete")
#pragma pack (pop)
#endif
