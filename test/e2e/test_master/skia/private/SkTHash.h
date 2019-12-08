/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkTHash_DEFINED
#  define SkTHash_DEFINED
#  include "include/core/SkTypes.h"
#  include "include/private/SkChecksum.h"
#  include "include/private/SkTemplates.h"
#  include <new>
template <typename T, typename K, typename Traits  = T>
class SkTHashTable
{
public:
  SkTHashTable()
    : fCount(0)
    , fCapacity(0)
  {
  }
  SkTHashTable(SkTHashTable&& other)
    : fCount(other.fCount)
    , fCapacity(other.fCapacity)
    , fSlots(std::move(other.fSlots))
  {
    other.fCount = other.fCapacity = 0;
  }
  SkTHashTable& operator=(SkTHashTable&& other)
  {
    if (this != &other)
    {
      this->~SkTHashTable();
      this  SkTHashTable(std::move(other));
    }
    return *this;
  }
  void reset()
  {
    *this = SkTHashTable();
  }
  int count() const
  {
    return fCount;
  }
  size_t approxBytesUsed() const
  {
    return fCapacity * sizeof(Slot);
  }
  T* set(T val)
  {
    if (4 * fCount >= 3 * fCapacity)
    {
      this->resize(fCapacity > 0 ? fCapacity * 2 : 4);
    }
    return this->uncheckedSet(std::move(val));
  }
  T* find(const K& key) const
  {
    uint32_t hash = Hash(key);
    int index = hash & (fCapacity - 1);
    for (int n = 0; n < fCapacity; n++)
    {
      Slot& s = fSlots[index];
      if (s.empty())
      {
        return nullptr;
      }
      if (hash == s.hash && key == Traits::GetKey(s.val))
      {
        return &s.val;
      }
      index = this->next(index);
    }
    SkASSERT(fCapacity == 0);
    return nullptr;
  }
  T findOrNull(const K& key) const
  {
    if (T * p = this->find(key))
    {
      return *p;
    }
    return nullptr;
  }
  void remove(const K& key)
  {
    SkASSERT(this->find(key));
    uint32_t hash = Hash(key);
    int index = hash & (fCapacity - 1);
    for (int n = 0; n < fCapacity; n++)
    {
      Slot& s = fSlots[index];
      SkASSERT(!s.empty());
      if (hash == s.hash && key == Traits::GetKey(s.val))
      {
        fCount--;
        break;
      }
      index = this->next(index);
    }
    for (;;)
    {
      Slot& emptySlot = fSlots[index];
      int emptyIndex = index;
      int originalIndex;
      do
      {
        index = this->next(index);
        Slot& s = fSlots[index];
        if (s.empty())
        {
          emptySlot = Slot();
          return ;
        }
        originalIndex = s.hash & (fCapacity - 1);
      } while ((index <= originalIndex && originalIndex < emptyIndex) || (originalIndex < emptyIndex && emptyIndex < index) || (emptyIndex < index && index <= originalIndex));
      Slot& moveFrom = fSlots[index];
      emptySlot = std::move(moveFrom);
    }
  }
  template <typename Fn>
  void foreach(Fn&& fn)
  {
    for (int i = 0; i < fCapacity; i++)
    {
      if (!fSlots[i].empty())
      {
        fn(&fSlots[i].val);
      }
    }
  }
  template <typename Fn>
  void foreach(Fn&& fn) const
  {
    for (int i = 0; i < fCapacity; i++)
    {
      if (!fSlots[i].empty())
      {
        fn(fSlots[i].val);
      }
    }
  }
private:
  T* uncheckedSet(T&& val)
  {
    const K& key = Traits::GetKey(val);
    uint32_t hash = Hash(key);
    int index = hash & (fCapacity - 1);
    for (int n = 0; n < fCapacity; n++)
    {
      Slot& s = fSlots[index];
      if (s.empty())
      {
        s.val = std::move(val);
        s.hash = hash;
        fCount++;
        return &s.val;
      }
      if (hash == s.hash && key == Traits::GetKey(s.val))
      {
        s.val = std::move(val);
        return &s.val;
      }
      index = this->next(index);
    }
    SkASSERT(false);
    return nullptr;
  }
  void resize(int capacity)
  {
    int oldCapacity = fCapacity;
    SkDEBUGCODE(int oldCount = fCount);
    fCount = 0;
    fCapacity = capacity;
    SkAutoTArray<Slot> oldSlots = std::move(fSlots);
    fSlots = SkAutoTArray<Slot>(capacity);
    for (int i = 0; i < oldCapacity; i++)
    {
      Slot& s = oldSlots[i];
      if (!s.empty())
      {
        this->uncheckedSet(std::move(s.val));
      }
    }
    SkASSERT(fCount == oldCount);
  }
  int next(int index) const
  {
    index--;
    if (index < 0)
    {
      index += fCapacity;
    }
    return index;
  }
  static uint32_t Hash(const K& key)
  {
    uint32_t hash = Traits::Hash(key) & 0xffffffff;
    return hash ? hash : 1;
  }
  struct Slot
  {
    Slot()
      : val()
      , hash(0)
    {
    }
    Slot(T&& v, uint32_t h)
      : val(std::move(v))
      , hash(h)
    {
    }
    Slot(Slot&& o)
    {
      *this = std::move(o);
    }
    Slot& operator=(Slot&& o)
    {
      val = std::move(o.val);
      hash = o.hash;
      return *this;
    }
    bool empty() const
    {
      return this->hash == 0;
    }
    T val;
    uint32_t hash;
  };
  int fCount, fCapacity;
  SkAutoTArray<Slot> fSlots;
  SkTHashTable(const SkTHashTable&) = delete;
  SkTHashTable& operator=(const SkTHashTable&);
};
template <typename K, typename V, typename HashK  = SkGoodHash>
class SkTHashMap
{
public:
  SkTHashMap()
  {
  }
  SkTHashMap(SkTHashMap&&);
  SkTHashMap& operator=(SkTHashMap&&);
  void reset()
  {
    fTable.reset();
  }
  int count() const
  {
    return fTable.count();
  }
  size_t approxBytesUsed() const
  {
    return fTable.approxBytesUsed();
  }
  V* set(K key, V val)
  {
    Pair* out = fTable.set({std::move(key), std::move(val)});
    return &out->val;
  }
  V* find(const K& key) const
  {
    if (Pair * p = fTable.find(key))
    {
      return &p->val;
    }
    return nullptr;
  }
  void remove(const K& key)
  {
    SkASSERT(this->find(key));
    fTable.remove(key);
  }
  template <typename Fn>
  void foreach(Fn&& fn)
  {
    fTable.foreach();
  }
  template <typename Fn>
  void foreach(Fn&& fn) const
  {
    fTable.foreach();
  }
private:
  struct Pair
  {
    K key;
    V val;
    static const K& GetKey(const Pair& p)
    {
      return p.key;
    }
    static auto Hash(const K& key)
    {
      return HashK()(key);
    }
  };
  SkTHashTable<Pair, K> fTable;
  SkTHashMap(const SkTHashMap&) = delete;
  SkTHashMap& operator=(const SkTHashMap&);
};
template <typename T, typename HashT  = SkGoodHash>
class SkTHashSet
{
public:
  SkTHashSet()
  {
  }
  SkTHashSet(SkTHashSet&&);
  SkTHashSet& operator=(SkTHashSet&&);
  void reset()
  {
    fTable.reset();
  }
  int count() const
  {
    return fTable.count();
  }
  bool empty() const
  {
    return fTable.count() == 0;
  }
  size_t approxBytesUsed() const
  {
    return fTable.approxBytesUsed();
  }
  void add(T item)
  {
    fTable.set(std::move(item));
  }
  bool contains(const T& item) const
  {
    return SkToBool(this->find(item));
  }
  const T* find(const T& item) const
  {
    return fTable.find(item);
  }
  void remove(const T& item)
  {
    SkASSERT(this->contains(item));
    fTable.remove(item);
  }
  template <typename Fn>
  void foreach(Fn&& fn) const
  {
    fTable.foreach(fn);
  }
private:
  struct Traits
  {
    static const T& GetKey(const T& item)
    {
      return item;
    }
    static auto Hash(const T& item)
    {
      return HashT()(item);
    }
  };
  SkTHashTable<T, T, Traits> fTable;
  SkTHashSet(const SkTHashSet&) = delete;
  SkTHashSet& operator=(const SkTHashSet&);
};
#endif
