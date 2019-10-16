/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrVkBackendContext_DEFINED
#  define GrVkBackendContext_DEFINED
#  include "include/core/SkRefCnt.h"
#  include "include/gpu/vk/GrVkMemoryAllocator.h"
#  include "include/gpu/vk/GrVkTypes.h"
class GrVkExtensions;
enum GrVkExtensionFlags
{
  kEXT_debug_report_GrVkExtensionFlag = 0x0001,
  kNV_glsl_shader_GrVkExtensionFlag = 0x0002,
  kKHR_surface_GrVkExtensionFlag = 0x0004,
  kKHR_swapchain_GrVkExtensionFlag = 0x0008,
  kKHR_win32_surface_GrVkExtensionFlag = 0x0010,
  kKHR_android_surface_GrVkExtensionFlag = 0x0020,
  kKHR_xcb_surface_GrVkExtensionFlag = 0x0040
};
enum GrVkFeatureFlags
{
  kGeometryShader_GrVkFeatureFlag = 0x0001,
  kDualSrcBlend_GrVkFeatureFlag = 0x0002,
  kSampleRateShading_GrVkFeatureFlag = 0x0004
};
struct VkPhysicalDeviceFeatures2;
struct SK_API GrVkBackendContext
{
  VkInstance fInstance;
  VkPhysicalDevice fPhysicalDevice;
  VkDevice fDevice;
  VkQueue fQueue;
  uint32_t fGraphicsQueueIndex;
  uint32_t fMinAPIVersion;
  uint32_t fInstanceVersion = 0;
  uint32_t fMaxAPIVersion = 0;
  uint32_t fExtensions = 0;
  const GrVkExtensions* fVkExtensions = nullptr;
  uint32_t fFeatures;
  const VkPhysicalDeviceFeatures* fDeviceFeatures = nullptr;
  const VkPhysicalDeviceFeatures2* fDeviceFeatures2 = nullptr;
  sk_sp<GrVkMemoryAllocator> fMemoryAllocator;
  GrVkGetProc fGetProc = nullptr;
  bool fOwnsInstanceAndDevice = false;
  GrProtected fProtectedContext = GrProtected::kNo;
};
#endif
