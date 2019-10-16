/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrGLConfig_chrome_DEFINED
#  define GrGLConfig_chrome_DEFINED
#  define GR_GL_CHECK_ERROR_START	0
#  define GR_GL_CHECK_ALLOC_WITH_GET_ERROR	0
#  if  !defined(GR_GL_IGNORE_ES3_MSAA)
#    define GR_GL_IGNORE_ES3_MSAA	1
#  endif
#endif
