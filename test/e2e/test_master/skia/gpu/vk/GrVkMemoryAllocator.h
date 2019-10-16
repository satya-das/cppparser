/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrVkMemoryAllocator_DEFINED
#  define GrVkMemoryAllocator_DEFINED
#  include "include/core/SkRefCnt.h"
#  include "include/gpu/GrTypes.h"
#  include "include/gpu/vk/GrVkTypes.h"
class GrVkMemoryAllocator : public SkRefCnt
{
public:
  enum class AllocationPropertyFlags
  {
    kNone = 0,
    kDedicatedAllocation = 0x1,
    kLazyAllocation = 0x2,
    kPersistentlyMapped = 0x4,
    kProtected = 0x8
  };
  GR_DECL_BITFIELD_CLASS_OPS_FRIENDS(AllocationPropertyFlags);
  enum class BufferUsage
  {
    kGpuOnly,
    kCpuOnly,
    kCpuWritesGpuReads,
    kGpuWritesCpuReads
  };
  virtual bool allocateMemoryForImage(VkImage image, AllocationPropertyFlags flags, GrVkBackendMemory*) = 0;
  virtual bool allocateMemoryForBuffer(VkBuffer buffer, BufferUsage usage, AllocationPropertyFlags flags, GrVkBackendMemory*) = 0;
  virtual void getAllocInfo(const GrVkBackendMemory&, GrVkAlloc*) const = 0;
  virtual void* mapMemory(const GrVkBackendMemory&) = 0;
  virtual void unmapMemory(const GrVkBackendMemory&) = 0;
  virtual void flushMappedMemory(const GrVkBackendMemory&, VkDeviceSize offset, VkDeviceSize size) = 0;
  virtual void invalidateMappedMemory(const GrVkBackendMemory&, VkDeviceSize offset, VkDeviceSize size) = 0;
  virtual void freeMemory(const GrVkBackendMemory&) = 0;
  virtual uint64_t totalUsedMemory() const = 0;
  virtual uint64_t totalAllocatedMemory() const = 0;
};
GR_MAKE_BITFIELD_CLASS_OPS(GrVkMemoryAllocator::AllocationPropertyFlags)
#endif
