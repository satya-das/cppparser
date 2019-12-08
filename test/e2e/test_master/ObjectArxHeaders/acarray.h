#ifndef AC_ACARRAY_H
#  define AC_ACARRAY_H
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#  include "PAL/api/c11_Annex_K.h"
#  include <memory>
#  include <stdlib.h>
#  include <algorithm>
#  include <type_traits>
#  include "adesk.h"
#  ifdef ASSERT
#    define AC_ARRAY_ASSERT	ASSERT
#  elif  defined assert
#    define AC_ARRAY_ASSERT	assert
#  elif  defined _ASSERTE
#    define AC_ARRAY_ASSERT	_ASSERTE
#  else 
#    define AC_ARRAY_ASSERT(T)
#  endif
#  pragma  pack (push, 8)
#  pragma  push_macro("new")
#  pragma  push_macro("delete")
#  undef new
#  undef delete
#  define ACARRAY_GROWTH_THRESHOLD	0x10000
template <typename T>
void AcArrayValidateParams(bool bSameBuffer, T* pDest, size_t nBufLen, const T* pSource, size_t nCount)
{
  ADESK_UNREFED_PARAM(pDest);
  ADESK_UNREFED_PARAM(nBufLen);
  ADESK_UNREFED_PARAM(pSource);
  ADESK_UNREFED_PARAM(nCount);
  AC_ARRAY_ASSERT(nCount >= 0);
  AC_ARRAY_ASSERT(nCount <= nBufLen);
  AC_ARRAY_ASSERT(nCount < 0x40000000);
  if (bSameBuffer)
  {
    AC_ARRAY_ASSERT(pSource > pDest);
  }
  else 
  {
    AC_ARRAY_ASSERT(pSource >= pDest + nBufLen || (pDest >= pSource + nCount));
  }
}
template <typename T>
class AcArrayMemCopyReallocator
{
public:
  static void copyItems(T* pDest, size_t nBufLen, const T* pSource, size_t nCount)
  {
    AcArrayValidateParams<T>(false, pDest, nBufLen, pSource, nCount);
    if (nCount > 0)
    {
      memcpy_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
    }
  }
  static void moveItems(T* pDest, size_t nBufLen, T* pSource, size_t nCount, bool bSameBuffer)
  {
    AcArrayValidateParams<T>(bSameBuffer, pDest, nBufLen, pSource, nCount);
    if (nCount > 0)
    {
      if (bSameBuffer)
      {
        memmove_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
      }
      else 
      {
        memcpy_s(pDest, nBufLen * sizeof(T), pSource, nCount * sizeof(T));
      }
    }
  }
};
template <typename T>
class AcArrayObjectCopyReallocator
{
public:
  static void copyItems(T* pDest, size_t nBufLen, const T* pSource, size_t nCount)
  {
    AcArrayValidateParams<T>(false, pDest, nBufLen, pSource, nCount);
    while (nCount--)
    {
      *pDest = *pSource;
      pDest++;
      pSource++;
    }
  }
  static void moveItems(T* pDest, size_t nBufLen, T* pSource, size_t nCount, bool bSameBuffer)
  {
    AcArrayValidateParams<T>(bSameBuffer, pDest, nBufLen, pSource, nCount);
    while (nCount--)
    {
      *pDest = std::move(*pSource);
      pDest++;
      pSource++;
    }
  }
};
template <typename T, bool >
struct AcArrayItemCopierSelector;
template <typename T>
struct AcArrayItemCopierSelector<T, false>
{
  typedef AcArrayObjectCopyReallocator<T> allocator;
};
template <typename T>
struct AcArrayItemCopierSelector<T, true>
{
  typedef AcArrayMemCopyReallocator<T> allocator;
};
template <typename T>
using AcArrayAllocator = typename AcArrayItemCopierSelector<T, std::is_trivial<T>::value>::allocator;
template <typename T, typename R  = AcArrayAllocator<T>>
class AcArray
{
public:
  AcArray(int initPhysicalLength = 0, int initGrowLength = 8);
  AcArray(const AcArray<T,R>&);
  AcArray(AcArray<T,R>&&);
  ~AcArray();
  typedef T Type;
  typedef R Allocator;
  enum
  {
    eUsesMemCopy = std::is_same<R, AcArrayMemCopyReallocator<T> >::value
  };
  AcArray<T,R>& operator =(const AcArray<T,R>&);
  AcArray<T,R>& operator =(AcArray<T,R>&&);
  bool operator ==(const AcArray<T,R>&) const;
  T& operator [](int);
  const T& operator [](int) const;
  const T& at(int index) const;
  T& at(int index);
  AcArray<T,R>& setAt(int index, const T& value);
  AcArray<T,R>& setAll(const T& value);
  T& first();
  const T& first() const;
  T& last();
  const T& last() const;
  int append(const T& value);
  AcArray<T,R>& append(const AcArray<T,R>& array);
  AcArray<T,R>& insertAt(int index, const T& value);
  int append(T&& value);
  int appendMove(T& value);
  AcArray<T,R>& appendMove(AcArray < T, R > &array);
  AcArray<T,R>& insertAt(int index, T&& value);
  AcArray<T,R>& insertAtMove(int index, T& value);
  AcArray<T,R>& removeAt(int index);
  bool remove(const T& value, int start = 0);
  AcArray<T,R>& removeFirst();
  AcArray<T,R>& removeLast();
  AcArray<T,R>& removeAll();
  AcArray<T,R>& removeSubArray(int startIndex, int endIndex);
  bool contains(const T& value, int start = 0) const;
  bool find(const T& value, int& foundAt, int start = 0) const;
  int find(const T& value) const;
  int findFrom(const T& value, int start) const;
  int length() const;
  bool isEmpty() const;
  int logicalLength() const;
  AcArray<T,R>& setLogicalLength(int);
  int physicalLength() const;
  AcArray<T,R>& setPhysicalLength(int);
  int growLength() const;
  AcArray<T,R>& setGrowLength(int);
  AcArray<T,R>& reverse();
  AcArray<T,R>& swap(int i1, int i2);
  const T* asArrayPtr() const;
  T* asArrayPtr();
  T* begin()
  {
    return mpArray;
  }
  T* end()
  {
    return mpArray + mLogicalLen;
  }
  const T* begin() const
  {
    return mpArray;
  }
  const T* end() const
  {
    return mpArray + mLogicalLen;
  }
protected:
  T* mpArray;
  int mPhysicalLen;
  int mLogicalLen;
  int mGrowLen;
  void insertSpace(int nIndex);
  void copyOtherIntoThis(const AcArray<T,R>& otherArray);
  void moveOtherIntoThis(AcArray < T, R > &otherArray);
  bool isValid(int) const;
};
#  pragma  pack (pop)
#  ifdef GE_LOCATED_NEW
#  endif
#  pragma  pack (push, 8)
template <typename T, typename R>
inline bool AcArray<T,R>::contains(const T& value, int start) const
{
  return this->findFrom(value, start) != -1;
}
template <typename T, typename R>
inline int AcArray<T,R>::length() const
{
  return mLogicalLen;
}
template <typename T, typename R>
inline bool AcArray<T,R>::isEmpty() const
{
  return mLogicalLen == 0;
}
template <typename T, typename R>
inline int AcArray<T,R>::logicalLength() const
{
  return mLogicalLen;
}
template <typename T, typename R>
inline int AcArray<T,R>::physicalLength() const
{
  return mPhysicalLen;
}
template <typename T, typename R>
inline int AcArray<T,R>::growLength() const
{
  return mGrowLen;
}
template <typename T, typename R>
inline const T* AcArray<T,R>::asArrayPtr() const
{
  return mpArray;
}
template <typename T, typename R>
inline T* AcArray<T,R>::asArrayPtr()
{
  return mpArray;
}
template <typename T, typename R>
inline bool AcArray<T,R>::isValid(int i) const
{
  return i >= 0 && i < mLogicalLen;
}
template <typename T, typename R>
inline T& AcArray<T,R>::operator [](int i)
{
  AC_ARRAY_ASSERT(this->isValid(i));
  return mpArray[i];
}
template <typename T, typename R>
inline const T& AcArray<T,R>::operator [](int i) const
{
  AC_ARRAY_ASSERT(this->isValid(i));
  return mpArray[i];
}
template <typename T, typename R>
inline T& AcArray<T,R>::at(int i)
{
  AC_ARRAY_ASSERT(this->isValid(i));
  return mpArray[i];
}
template <typename T, typename R>
inline const T& AcArray<T,R>::at(int i) const
{
  AC_ARRAY_ASSERT(this->isValid(i));
  return mpArray[i];
}
template <typename T, typename R>
inline AcArray<T,R>& AcArray<T,R>::setAt(int i, const T& value)
{
  AC_ARRAY_ASSERT(this->isValid(i));
  mpArray[i] = value;
  return *this;
}
template <typename T, typename R>
inline T& AcArray<T,R>::first()
{
  AC_ARRAY_ASSERT(!this->isEmpty());
  return mpArray[0];
}
template <typename T, typename R>
inline const T& AcArray<T,R>::first() const
{
  AC_ARRAY_ASSERT(!this->isEmpty());
  return mpArray[0];
}
template <typename T, typename R>
inline T& AcArray<T,R>::last()
{
  AC_ARRAY_ASSERT(!this->isEmpty());
  return mpArray[mLogicalLen - 1];
}
template <typename T, typename R>
inline const T& AcArray<T,R>::last() const
{
  AC_ARRAY_ASSERT(!this->isEmpty());
  return mpArray[mLogicalLen - 1];
}
template <typename T, typename R>
inline int AcArray<T,R>::append(const T& value)
{
  insertAt(mLogicalLen, value);
  return mLogicalLen - 1;
}
template <typename T, typename R>
inline int AcArray<T,R>::append(T&& value)
{
  return this->appendMove(value);
}
template <typename T, typename R>
inline int AcArray<T,R>::appendMove(T& value)
{
  this->insertAtMove(mLogicalLen, value);
  return this->mLogicalLen - 1;
}
template <typename T, typename R>
inline AcArray<T,R>& AcArray<T,R>::removeFirst()
{
  AC_ARRAY_ASSERT(!isEmpty());
  return removeAt(0);
}
template <typename T, typename R>
inline AcArray<T,R>& AcArray<T,R>::removeLast()
{
  AC_ARRAY_ASSERT(!isEmpty());
  if (!isEmpty())
  {
    mLogicalLen--;
  }
  return *this;
}
template <typename T, typename R>
inline AcArray<T,R>& AcArray<T,R>::removeAll()
{
  this->setLogicalLength(0);
  return *this;
}
template <typename T, typename R>
inline AcArray<T,R>& AcArray<T,R>::setGrowLength(int glen)
{
  AC_ARRAY_ASSERT(glen > 0);
  mGrowLen = glen;
  return *this;
}
template <typename T, typename R>
inline AcArray< T, R > ::AcArray(int physicalLength, int growLength)
  : mpArray(nullptr)
  , mPhysicalLen(0)
  , mLogicalLen(0)
  , mGrowLen(growLength)
{
  static_assert(std::is_trivial<T>::value || !std::is_pod<T>::value, "is_pod but not is_trivial?");
  AC_ARRAY_ASSERT(mGrowLen > 0);
  AC_ARRAY_ASSERT(physicalLength >= 0);
  if (physicalLength > 0)
  {
    this->setPhysicalLength(physicalLength);
  }
}
template <typename T, typename R>
inline AcArray<T,R>::AcArray(const AcArray<T,R>& src)
  : mpArray(nullptr)
  , mPhysicalLen(0)
  , mLogicalLen(0)
  , mGrowLen(src.mGrowLen)
{
  this->copyOtherIntoThis(src);
}
template <typename T, typename R>
inline AcArray<T,R>::AcArray(AcArray<T,R>&& src)
  : mpArray(nullptr)
  , mPhysicalLen(0)
  , mLogicalLen(0)
  , mGrowLen(src.mGrowLen)
{
  this->moveOtherIntoThis(src);
}
template <typename T, typename R>
inline AcArray<T,R>::~AcArray()
{
  this->setPhysicalLength(0);
}
template <typename T, typename R>
inline AcArray<T,R>& AcArray<T,R>::operator =(const AcArray<T,R>& src)
{
  if (this != &src)
  {
    this->copyOtherIntoThis(src);
  }
  return *this;
}
template <typename T, typename R>
inline AcArray<T,R>& AcArray<T,R>::operator =(AcArray<T,R>&& src)
{
  if (this != &src)
  {
    this->setPhysicalLength(0);
    this->moveOtherIntoThis(src);
  }
  return *this;
}
template <typename T, typename R>
bool AcArray<T,R>::operator ==(const AcArray<T,R>& cpr) const
{
  if (mLogicalLen == cpr.mLogicalLen)
  {
    for (int i = 0; i < mLogicalLen; i++)
    {
      if (mpArray[i] != cpr.mpArray[i])
      {
        return false;
      }
    }
    return true;
  }
  return false;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::setAll(const T& value)
{
  for (int i = 0; i < mLogicalLen; i++)
  {
    mpArray[i] = value;
  }
  return *this;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::append(const AcArray<T,R>& otherArray)
{
  const int nOrigLogLen = this->mLogicalLen;
  const int nOrigOtherLogLen = otherArray.mLogicalLen;
  this->setLogicalLength(nOrigLogLen + nOrigOtherLogLen);
  R::copyItems(mpArray + nOrigLogLen, mLogicalLen - nOrigLogLen, otherArray.mpArray, nOrigOtherLogLen);
  return *this;
}
template <typename T, typename R>
inline void AcArray<T,R>::copyOtherIntoThis(const AcArray<T,R>& otherArray)
{
  AC_ARRAY_ASSERT(this != &otherArray);
  this->setLogicalLength(otherArray.mLogicalLen);
  R::copyItems(mpArray, mPhysicalLen, otherArray.mpArray, mLogicalLen);
}
template <typename T, typename R>
inline void AcArray<T,R>::moveOtherIntoThis(AcArray<T,R>& otherArray)
{
  AC_ARRAY_ASSERT(this != &otherArray);
  AC_ARRAY_ASSERT(this->mpArray == nullptr);
  this->mpArray = otherArray.mpArray;
  this->mLogicalLen = otherArray.mLogicalLen;
  this->mPhysicalLen = otherArray.mPhysicalLen;
  otherArray.mpArray = nullptr;
  otherArray.mLogicalLen = 0;
  otherArray.mPhysicalLen = 0;
  otherArray.mGrowLen = 8;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::appendMove(AcArray<T,R>& otherArray)
{
  AC_ARRAY_ASSERT(this != &otherArray);
  if (this != &otherArray)
  {
    if (this->mLogicalLen == 0)
    {
      this->setPhysicalLength(0);
      this->moveOtherIntoThis(otherArray);
    }
    else 
    {
      const int nOrigLogLen = this->mLogicalLen;
      this->setLogicalLength(nOrigLogLen + otherArray.mLogicalLen);
      R::moveItems(mpArray + nOrigLogLen, mLogicalLen - nOrigLogLen, otherArray.mpArray, otherArray.mLogicalLen, false);
    }
  }
  return *this;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::insertAt(int index, const T& value)
{
  AC_ARRAY_ASSERT(index >= 0);
  AC_ARRAY_ASSERT(index <= mLogicalLen);
  AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
  if (index < 0 || index > mLogicalLen)
  {
    return *this;
  }
  if (index == mLogicalLen && mLogicalLen < mPhysicalLen)
  {
    mpArray[index] = value;
    mLogicalLen++;
  }
  else 
  {
    T tmp(value);
    this->insertSpace(index);
    mpArray[index] = std::move(tmp);
  }
  return *this;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::insertAt(int index, T&& value)
{
  return this->insertAtMove(index, value);
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::insertAtMove(int index, T& value)
{
  AC_ARRAY_ASSERT(index >= 0);
  AC_ARRAY_ASSERT(index <= mLogicalLen);
  AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
  if (index < 0 || index > mLogicalLen)
  {
    return *this;
  }
  if (index == mLogicalLen && mLogicalLen < mPhysicalLen)
  {
    mpArray[index] = std::move(value);
    mLogicalLen++;
  }
  else 
  {
    T tmp(std::move(value));
    this->insertSpace(index);
    mpArray[index] = std::move(tmp);
  }
  return *this;
}
template <typename T, typename R>
void AcArray<T,R>::insertSpace(int nIndex)
{
  this->setLogicalLength(mLogicalLen + 1);
  if (nIndex < mLogicalLen - 1)
  {
    AC_ARRAY_ASSERT(mLogicalLen >= 0);
    T* p = mpArray + mLogicalLen - 1;
    T* const pSpace = mpArray + nIndex;
    AC_ARRAY_ASSERT(p >= pSpace);
    do
    {
      *p = std::move(*(p - 1));
    } while (--p != pSpace);
  }
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::removeAt(int index)
{
  AC_ARRAY_ASSERT(isValid(index));
  AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
  AC_ARRAY_ASSERT(!isEmpty());
  if (isEmpty() || !isValid(index))
  {
    return *this;
  }
  if (index < mLogicalLen - 1)
  {
    R::moveItems(mpArray + index, mPhysicalLen - index, mpArray + index + 1, mLogicalLen - 1 - index, true);
  }
  mLogicalLen--;
  return *this;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::removeSubArray(int startIndex, int endIndex)
{
  AC_ARRAY_ASSERT(isValid(startIndex));
  AC_ARRAY_ASSERT(startIndex <= endIndex);
  if (endIndex >= mLogicalLen - 1)
  {
    mLogicalLen = startIndex;
    return *this;
  }
  const int kNumToRemove = endIndex + 1 - startIndex;
  const int kNumToShift = mLogicalLen - 1 - endIndex;
  AC_ARRAY_ASSERT(kNumToShift >= 1);
  R::moveItems(mpArray + startIndex, mPhysicalLen - startIndex, mpArray + endIndex + 1, kNumToShift, true);
  mLogicalLen -= kNumToRemove;
  return *this;
}
template <typename T, typename R>
bool AcArray<T,R>::find(const T& value, int& index, int start) const
{
  const int nFoundAt = this->findFrom(value, start);
  if (nFoundAt == -1)
  {
    return false;
  }
  index = nFoundAt;
  return true;
}
template <typename T, typename R>
int AcArray<T,R>::find(const T& value) const
{
  return this->findFrom(value, 0);
}
template <typename T, typename R>
int AcArray<T,R>::findFrom(const T& value, int start) const
{
  AC_ARRAY_ASSERT(start >= 0);
  if (start < 0)
  {
    return -1;
  }
  for (int i = start; i < this->mLogicalLen; i++)
  {
    if (mpArray[i] == value)
    {
      return i;
    }
  }
  return -1;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::setLogicalLength(int n)
{
  AC_ARRAY_ASSERT(n >= 0);
  if (n < 0)
  {
    n = 0;
  }
  AC_ARRAY_ASSERT(n < 0x40000000);
  if (n > mPhysicalLen)
  {
    const int growth = (mPhysicalLen * sizeof(T)) < ACARRAY_GROWTH_THRESHOLD ? mPhysicalLen : ACARRAY_GROWTH_THRESHOLD / sizeof(T);
    int minSize = mPhysicalLen + std::max<int>(growth, mGrowLen);
    if (n > minSize)
    {
      minSize = n;
    }
    setPhysicalLength(minSize);
  }
  mLogicalLen = n;
  AC_ARRAY_ASSERT(mLogicalLen <= mPhysicalLen);
  return *this;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::setPhysicalLength(int n)
{
  AC_ARRAY_ASSERT(mPhysicalLen >= mLogicalLen);
  AC_ARRAY_ASSERT((mPhysicalLen == 0) == (mpArray == nullptr));
  AC_ARRAY_ASSERT(n >= 0);
  AC_ARRAY_ASSERT(n < 0x40000000);
  if (n == mPhysicalLen || n < 0)
  {
    return *this;
  }
  T* pOldArray = mpArray;
  const size_t nOldLen = mPhysicalLen;
  mPhysicalLen = n;
  mpArray = nullptr;
  if (mPhysicalLen < mLogicalLen)
  {
    mLogicalLen = mPhysicalLen;
  }
  if (mPhysicalLen != 0)
  {
    mpArray = static_cast<T*>(::operator new(sizeof(T) * mPhysicalLen));
    AC_ARRAY_ASSERT(mpArray != nullptr);
    if (mpArray == nullptr)
    {
      mPhysicalLen = 0;
      mLogicalLen = 0;
    }
    else 
    {
      T* pNewBuf = mpArray;
      for (int i = 0; i < mPhysicalLen; i++)
      {
        pNewBuf++  T;
      }
      R::moveItems(mpArray, mPhysicalLen, pOldArray, mLogicalLen, false);
    }
  }
  for (size_t i = 0; i < nOldLen; i++)
  {
    (pOldArray + i)->~T();
  }
  ::operator delete(static_cast<void*>(pOldArray));
  return *this;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::reverse()
{
  for (int i = 0; i < mLogicalLen / 2; i++)
  {
    T tmp = std::move(mpArray[i]);
    mpArray[i] = std::move(mpArray[mLogicalLen - 1 - i]);
    mpArray[mLogicalLen - 1 - i] = std::move(tmp);
  }
  return *this;
}
template <typename T, typename R>
AcArray<T,R>& AcArray<T,R>::swap(int i1, int i2)
{
  AC_ARRAY_ASSERT(isValid(i1));
  AC_ARRAY_ASSERT(isValid(i2));
  if (i1 == i2)
  {
    return *this;
  }
  T tmp = std::move(mpArray[i1]);
  mpArray[i1] = std::move(mpArray[i2]);
  mpArray[i2] = std::move(tmp);
  return *this;
}
template <typename T, typename R>
bool AcArray<T,R>::remove(const T& value, int start)
{
  const int i = this->findFrom(value, start);
  if (i == -1)
  {
    return false;
  }
  this->removeAt(i);
  return true;
}
#  include "acarrayhelper.h"
#  ifdef _Ac_String_h_
typedef AcArray< AcString, AcArrayObjectCopyReallocator< AcString > > AcStringArray;
#  endif
#  pragma  pop_macro("new")
#  pragma  pop_macro("delete")
#  pragma  pack (pop)
#endif
