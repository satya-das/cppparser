/*
 * Copyright 2018 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrVkVulkan_DEFINED
#  define GrVkVulkan_DEFINED
#  include "include/core/SkTypes.h"
#  if  SKIA_IMPLEMENTATION || !defined(SK_VULKAN)
#    include "include/third_party/vulkan/vulkan/vulkan_core.h"
#  else 
#    include <vulkan/vulkan_core.h>
#  endif
#  ifdef SK_BUILD_FOR_ANDROID
#    if  SKIA_IMPLEMENTATION || !defined(SK_VULKAN)
#      include "include/third_party/vulkan/vulkan/vulkan_android.h"
#    else 
#      include <vulkan/vulkan_android.h>
#    endif
#  endif
#endif
