/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkSafe_math_DEFINED
#  define SkSafe_math_DEFINED
#  if  defined(_MSC_VER) && !defined(_INC_MATH)
#    define __inline	static __inline
#    include <math.h>
#    undef __inline
#    if  !defined(_INC_MATH)
#    endif
#    define INC_MATH_IS_SAFE_NOW
#  else 
#    include <math.h>
#  endif
#endif
