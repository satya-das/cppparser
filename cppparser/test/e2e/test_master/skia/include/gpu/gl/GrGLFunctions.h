/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef GrGLFunctions_DEFINED
#  define GrGLFunctions_DEFINED
#  include <cstring>
#  include "include/gpu/gl/GrGLTypes.h"
#  include "include/private/SkTLogic.h"
extern "C" {
///////////////////////////////////////////////////////////////////////////////
  using GrGLActiveTextureFn = GrGLvoid (*) (GrGLenum texture);
;
  using GrGLAttachShaderFn = GrGLvoid (*) (GrGLuint program, GrGLuint shader);
;
  using GrGLBeginQueryFn = GrGLvoid (*) (GrGLenum target, GrGLuint id);
;
  using GrGLBindAttribLocationFn = GrGLvoid (*) (GrGLuint program, GrGLuint index, const char* name);
;
  using GrGLBindBufferFn = GrGLvoid (*) (GrGLenum target, GrGLuint buffer);
;
  using GrGLBindFramebufferFn = GrGLvoid (*) (GrGLenum target, GrGLuint framebuffer);
;
  using GrGLBindRenderbufferFn = GrGLvoid (*) (GrGLenum target, GrGLuint renderbuffer);
;
  using GrGLBindTextureFn = GrGLvoid (*) (GrGLenum target, GrGLuint texture);
;
  using GrGLBindFragDataLocationFn = GrGLvoid (*) (GrGLuint program, GrGLuint colorNumber, const GrGLchar* name);
;
  using GrGLBindFragDataLocationIndexedFn = GrGLvoid (*) (GrGLuint program, GrGLuint colorNumber, GrGLuint index, const GrGLchar* name);
;
  using GrGLBindSamplerFn = GrGLvoid (*) (GrGLuint unit, GrGLuint sampler);
;
  using GrGLBindVertexArrayFn = GrGLvoid (*) (GrGLuint array);
;
  using GrGLBlendBarrierFn = GrGLvoid (*) ();
;
  using GrGLBlendColorFn = GrGLvoid (*) (GrGLclampf red, GrGLclampf green, GrGLclampf blue, GrGLclampf alpha);
;
  using GrGLBlendEquationFn = GrGLvoid (*) (GrGLenum mode);
;
  using GrGLBlendFuncFn = GrGLvoid (*) (GrGLenum sfactor, GrGLenum dfactor);
;
  using GrGLBlitFramebufferFn = GrGLvoid (*) (GrGLint srcX0, GrGLint srcY0, GrGLint srcX1, GrGLint srcY1, GrGLint dstX0, GrGLint dstY0, GrGLint dstX1, GrGLint dstY1, GrGLbitfield mask, GrGLenum filter);
;
  using GrGLBufferDataFn = GrGLvoid (*) (GrGLenum target, GrGLsizeiptr size, const GrGLvoid* data, GrGLenum usage);
;
  using GrGLBufferSubDataFn = GrGLvoid (*) (GrGLenum target, GrGLintptr offset, GrGLsizeiptr size, const GrGLvoid* data);
;
  using GrGLCheckFramebufferStatusFn = GrGLenum (*) (GrGLenum target);
;
  using GrGLClearFn = GrGLvoid (*) (GrGLbitfield mask);
;
  using GrGLClearColorFn = GrGLvoid (*) (GrGLclampf red, GrGLclampf green, GrGLclampf blue, GrGLclampf alpha);
;
  using GrGLClearStencilFn = GrGLvoid (*) (GrGLint s);
;
  using GrGLClearTexImageFn = GrGLvoid (*) (GrGLuint texture, GrGLint level, GrGLenum format, GrGLenum type, const GrGLvoid* data);
;
  using GrGLClearTexSubImageFn = GrGLvoid (*) (GrGLuint texture, GrGLint level, GrGLint xoffset, GrGLint yoffset, GrGLint zoffset, GrGLsizei width, GrGLsizei height, GrGLsizei depth, GrGLenum format, GrGLenum type, const GrGLvoid* data);
;
  using GrGLColorMaskFn = GrGLvoid (*) (GrGLboolean red, GrGLboolean green, GrGLboolean blue, GrGLboolean alpha);
;
  using GrGLCompileShaderFn = GrGLvoid (*) (GrGLuint shader);
;
  using GrGLCompressedTexImage2DFn = GrGLvoid (*) (GrGLenum target, GrGLint level, GrGLenum internalformat, GrGLsizei width, GrGLsizei height, GrGLint border, GrGLsizei imageSize, const GrGLvoid* data);
;
  using GrGLCompressedTexSubImage2DFn = GrGLvoid (*) (GrGLenum target, GrGLint level, GrGLint xoffset, GrGLint yoffset, GrGLsizei width, GrGLsizei height, GrGLenum format, GrGLsizei imageSize, const GrGLvoid* data);
;
  using GrGLCopyTexSubImage2DFn = GrGLvoid (*) (GrGLenum target, GrGLint level, GrGLint xoffset, GrGLint yoffset, GrGLint x, GrGLint y, GrGLsizei width, GrGLsizei height);
;
  using GrGLCreateProgramFn = GrGLuint (*) ();
;
  using GrGLCreateShaderFn = GrGLuint (*) (GrGLenum type);
;
  using GrGLCullFaceFn = GrGLvoid (*) (GrGLenum mode);
;
  using GrGLDeleteBuffersFn = GrGLvoid (*) (GrGLsizei n, const GrGLuint* buffers);
;
  using GrGLDeleteFramebuffersFn = GrGLvoid (*) (GrGLsizei n, const GrGLuint* framebuffers);
;
  using GrGLDeleteProgramFn = GrGLvoid (*) (GrGLuint program);
;
  using GrGLDeleteQueriesFn = GrGLvoid (*) (GrGLsizei n, const GrGLuint* ids);
;
  using GrGLDeleteRenderbuffersFn = GrGLvoid (*) (GrGLsizei n, const GrGLuint* renderbuffers);
;
  using GrGLDeleteSamplersFn = GrGLvoid (*) (GrGLsizei count, const GrGLuint* samplers);
;
  using GrGLDeleteShaderFn = GrGLvoid (*) (GrGLuint shader);
;
  using GrGLDeleteTexturesFn = GrGLvoid (*) (GrGLsizei n, const GrGLuint* textures);
;
  using GrGLDeleteVertexArraysFn = GrGLvoid (*) (GrGLsizei n, const GrGLuint* arrays);
;
  using GrGLDepthMaskFn = GrGLvoid (*) (GrGLboolean flag);
;
  using GrGLDisableFn = GrGLvoid (*) (GrGLenum cap);
;
  using GrGLDisableVertexAttribArrayFn = GrGLvoid (*) (GrGLuint index);
;
  using GrGLDrawArraysFn = GrGLvoid (*) (GrGLenum mode, GrGLint first, GrGLsizei count);
;
  using GrGLDrawArraysInstancedFn = GrGLvoid (*) (GrGLenum mode, GrGLint first, GrGLsizei count, GrGLsizei primcount);
;
  using GrGLDrawArraysIndirectFn = GrGLvoid (*) (GrGLenum mode, const GrGLvoid* indirect);
;
  using GrGLDrawBufferFn = GrGLvoid (*) (GrGLenum mode);
;
  using GrGLDrawBuffersFn = GrGLvoid (*) (GrGLsizei n, const GrGLenum* bufs);
;
  using GrGLDrawElementsFn = GrGLvoid (*) (GrGLenum mode, GrGLsizei count, GrGLenum type, const GrGLvoid* indices);
;
  using GrGLDrawElementsInstancedFn = GrGLvoid (*) (GrGLenum mode, GrGLsizei count, GrGLenum type, const GrGLvoid* indices, GrGLsizei primcount);
;
  using GrGLDrawElementsIndirectFn = GrGLvoid (*) (GrGLenum mode, GrGLenum type, const GrGLvoid* indirect);
;
  using GrGLDrawRangeElementsFn = GrGLvoid (*) (GrGLenum mode, GrGLuint start, GrGLuint end, GrGLsizei count, GrGLenum type, const GrGLvoid* indices);
;
  using GrGLEnableFn = GrGLvoid (*) (GrGLenum cap);
;
  using GrGLEnableVertexAttribArrayFn = GrGLvoid (*) (GrGLuint index);
;
  using GrGLEndQueryFn = GrGLvoid (*) (GrGLenum target);
;
  using GrGLFinishFn = GrGLvoid (*) ();
;
  using GrGLFlushFn = GrGLvoid (*) ();
;
  using GrGLFlushMappedBufferRangeFn = GrGLvoid (*) (GrGLenum target, GrGLintptr offset, GrGLsizeiptr length);
;
  using GrGLFramebufferRenderbufferFn = GrGLvoid (*) (GrGLenum target, GrGLenum attachment, GrGLenum renderbuffertarget, GrGLuint renderbuffer);
;
  using GrGLFramebufferTexture2DFn = GrGLvoid (*) (GrGLenum target, GrGLenum attachment, GrGLenum textarget, GrGLuint texture, GrGLint level);
;
  using GrGLFramebufferTexture2DMultisampleFn = GrGLvoid (*) (GrGLenum target, GrGLenum attachment, GrGLenum textarget, GrGLuint texture, GrGLint level, GrGLsizei samples);
;
  using GrGLFrontFaceFn = GrGLvoid (*) (GrGLenum mode);
;
  using GrGLGenBuffersFn = GrGLvoid (*) (GrGLsizei n, GrGLuint* buffers);
;
  using GrGLGenFramebuffersFn = GrGLvoid (*) (GrGLsizei n, GrGLuint* framebuffers);
;
  using GrGLGenerateMipmapFn = GrGLvoid (*) (GrGLenum target);
;
  using GrGLGenQueriesFn = GrGLvoid (*) (GrGLsizei n, GrGLuint* ids);
;
  using GrGLGenRenderbuffersFn = GrGLvoid (*) (GrGLsizei n, GrGLuint* renderbuffers);
;
  using GrGLGenSamplersFn = GrGLvoid (*) (GrGLsizei count, GrGLuint* samplers);
;
  using GrGLGenTexturesFn = GrGLvoid (*) (GrGLsizei n, GrGLuint* textures);
;
  using GrGLGenVertexArraysFn = GrGLvoid (*) (GrGLsizei n, GrGLuint* arrays);
;
  using GrGLGetBufferParameterivFn = GrGLvoid (*) (GrGLenum target, GrGLenum pname, GrGLint* params);
;
  using GrGLGetErrorFn = GrGLenum (*) ();
;
  using GrGLGetFramebufferAttachmentParameterivFn = GrGLvoid (*) (GrGLenum target, GrGLenum attachment, GrGLenum pname, GrGLint* params);
;
  using GrGLGetIntegervFn = GrGLvoid (*) (GrGLenum pname, GrGLint* params);
;
  using GrGLGetMultisamplefvFn = GrGLvoid (*) (GrGLenum pname, GrGLuint index, GrGLfloat* val);
;
  using GrGLGetProgramBinaryFn = GrGLvoid (*) (GrGLuint program, GrGLsizei bufsize, GrGLsizei* length, GrGLenum* binaryFormat, void* binary);
;
  using GrGLGetProgramInfoLogFn = GrGLvoid (*) (GrGLuint program, GrGLsizei bufsize, GrGLsizei* length, char* infolog);
;
  using GrGLGetProgramivFn = GrGLvoid (*) (GrGLuint program, GrGLenum pname, GrGLint* params);
;
  using GrGLGetQueryivFn = GrGLvoid (*) (GrGLenum GLtarget, GrGLenum pname, GrGLint* params);
;
  using GrGLGetQueryObjecti64vFn = GrGLvoid (*) (GrGLuint id, GrGLenum pname, GrGLint64* params);
;
  using GrGLGetQueryObjectivFn = GrGLvoid (*) (GrGLuint id, GrGLenum pname, GrGLint* params);
;
  using GrGLGetQueryObjectui64vFn = GrGLvoid (*) (GrGLuint id, GrGLenum pname, GrGLuint64* params);
;
  using GrGLGetQueryObjectuivFn = GrGLvoid (*) (GrGLuint id, GrGLenum pname, GrGLuint* params);
;
  using GrGLGetRenderbufferParameterivFn = GrGLvoid (*) (GrGLenum target, GrGLenum pname, GrGLint* params);
;
  using GrGLGetShaderInfoLogFn = GrGLvoid (*) (GrGLuint shader, GrGLsizei bufsize, GrGLsizei* length, char* infolog);
;
  using GrGLGetShaderivFn = GrGLvoid (*) (GrGLuint shader, GrGLenum pname, GrGLint* params);
;
  using GrGLGetShaderPrecisionFormatFn = GrGLvoid (*) (GrGLenum shadertype, GrGLenum precisiontype, GrGLint* range, GrGLint* precision);
;
  using GrGLGetStringFn = const GrGLubyte* (*) (GrGLenum name);
;
  using GrGLGetStringiFn = const GrGLubyte* (*) (GrGLenum name, GrGLuint index);
;
  using GrGLGetTexLevelParameterivFn = GrGLvoid (*) (GrGLenum target, GrGLint level, GrGLenum pname, GrGLint* params);
;
  using GrGLGetUniformLocationFn = GrGLint (*) (GrGLuint program, const char* name);
;
  using GrGLInsertEventMarkerFn = GrGLvoid (*) (GrGLsizei length, const char* marker);
;
  using GrGLInvalidateBufferDataFn = GrGLvoid (*) (GrGLuint buffer);
;
  using GrGLInvalidateBufferSubDataFn = GrGLvoid (*) (GrGLuint buffer, GrGLintptr offset, GrGLsizeiptr length);
;
  using GrGLInvalidateFramebufferFn = GrGLvoid (*) (GrGLenum target, GrGLsizei numAttachments, const GrGLenum* attachments);
;
  using GrGLInvalidateSubFramebufferFn = GrGLvoid (*) (GrGLenum target, GrGLsizei numAttachments, const GrGLenum* attachments, GrGLint x, GrGLint y, GrGLsizei width, GrGLsizei height);
;
  using GrGLInvalidateTexImageFn = GrGLvoid (*) (GrGLuint texture, GrGLint level);
;
  using GrGLInvalidateTexSubImageFn = GrGLvoid (*) (GrGLuint texture, GrGLint level, GrGLint xoffset, GrGLint yoffset, GrGLint zoffset, GrGLsizei width, GrGLsizei height, GrGLsizei depth);
;
  using GrGLIsTextureFn = GrGLboolean (*) (GrGLuint texture);
;
  using GrGLLineWidthFn = GrGLvoid (*) (GrGLfloat width);
;
  using GrGLLinkProgramFn = GrGLvoid (*) (GrGLuint program);
;
  using GrGLMapBufferFn = GrGLvoid* (*) (GrGLenum target, GrGLenum access);
;
  using GrGLMapBufferRangeFn = GrGLvoid* (*) (GrGLenum target, GrGLintptr offset, GrGLsizeiptr length, GrGLbitfield access);
;
  using GrGLMapBufferSubDataFn = GrGLvoid* (*) (GrGLuint target, GrGLintptr offset, GrGLsizeiptr size, GrGLenum access);
;
  using GrGLMapTexSubImage2DFn = GrGLvoid* (*) (GrGLenum target, GrGLint level, GrGLint xoffset, GrGLint yoffset, GrGLsizei width, GrGLsizei height, GrGLenum format, GrGLenum type, GrGLenum access);
;
  using GrGLPixelStoreiFn = GrGLvoid (*) (GrGLenum pname, GrGLint param);
;
  using GrGLPolygonModeFn = GrGLvoid (*) (GrGLenum face, GrGLenum mode);
;
  using GrGLPopGroupMarkerFn = GrGLvoid (*) ();
;
  using GrGLProgramBinaryFn = GrGLvoid (*) (GrGLuint program, GrGLenum binaryFormat, void* binary, GrGLsizei length);
;
  using GrGLProgramParameteriFn = GrGLvoid (*) (GrGLuint program, GrGLenum pname, GrGLint value);
;
  using GrGLPushGroupMarkerFn = GrGLvoid (*) (GrGLsizei length, const char* marker);
;
  using GrGLQueryCounterFn = GrGLvoid (*) (GrGLuint id, GrGLenum target);
;
  using GrGLReadBufferFn = GrGLvoid (*) (GrGLenum src);
;
  using GrGLReadPixelsFn = GrGLvoid (*) (GrGLint x, GrGLint y, GrGLsizei width, GrGLsizei height, GrGLenum format, GrGLenum type, GrGLvoid* pixels);
;
  using GrGLRenderbufferStorageFn = GrGLvoid (*) (GrGLenum target, GrGLenum internalformat, GrGLsizei width, GrGLsizei height);
;
  using GrGLRenderbufferStorageMultisampleFn = GrGLvoid (*) (GrGLenum target, GrGLsizei samples, GrGLenum internalformat, GrGLsizei width, GrGLsizei height);
;
  using GrGLResolveMultisampleFramebufferFn = GrGLvoid (*) ();
;
  using GrGLSamplerParameteriFn = GrGLvoid (*) (GrGLuint sampler, GrGLenum pname, GrGLint params);
;
  using GrGLSamplerParameterivFn = GrGLvoid (*) (GrGLuint sampler, GrGLenum pname, const GrGLint* params);
;
  using GrGLScissorFn = GrGLvoid (*) (GrGLint x, GrGLint y, GrGLsizei width, GrGLsizei height);
;
// GL_CHROMIUM_bind_uniform_location
  using GrGLBindUniformLocationFn = GrGLvoid (*) (GrGLuint program, GrGLint location, const char* name);
;
  using GrGLShaderSourceFn = GrGLvoid (*) (GrGLuint shader, GrGLsizei count, const char* const * str, const GrGLint* length);
;
  using GrGLStencilFuncFn = GrGLvoid (*) (GrGLenum func, GrGLint ref, GrGLuint mask);
;
  using GrGLStencilFuncSeparateFn = GrGLvoid (*) (GrGLenum face, GrGLenum func, GrGLint ref, GrGLuint mask);
;
  using GrGLStencilMaskFn = GrGLvoid (*) (GrGLuint mask);
;
  using GrGLStencilMaskSeparateFn = GrGLvoid (*) (GrGLenum face, GrGLuint mask);
;
  using GrGLStencilOpFn = GrGLvoid (*) (GrGLenum fail, GrGLenum zfail, GrGLenum zpass);
;
  using GrGLStencilOpSeparateFn = GrGLvoid (*) (GrGLenum face, GrGLenum fail, GrGLenum zfail, GrGLenum zpass);
;
  using GrGLTexBufferFn = GrGLvoid (*) (GrGLenum target, GrGLenum internalformat, GrGLuint buffer);
;
  using GrGLTexBufferRangeFn = GrGLvoid (*) (GrGLenum target, GrGLenum internalformat, GrGLuint buffer, GrGLintptr offset, GrGLsizeiptr size);
;
  using GrGLTexImage2DFn = GrGLvoid (*) (GrGLenum target, GrGLint level, GrGLint internalformat, GrGLsizei width, GrGLsizei height, GrGLint border, GrGLenum format, GrGLenum type, const GrGLvoid* pixels);
;
  using GrGLTexParameterfFn = GrGLvoid (*) (GrGLenum target, GrGLenum pname, GrGLfloat param);
;
  using GrGLTexParameterfvFn = GrGLvoid (*) (GrGLenum target, GrGLenum pname, const GrGLfloat* params);
;
  using GrGLTexParameteriFn = GrGLvoid (*) (GrGLenum target, GrGLenum pname, GrGLint param);
;
  using GrGLTexParameterivFn = GrGLvoid (*) (GrGLenum target, GrGLenum pname, const GrGLint* params);
;
  using GrGLTexStorage2DFn = GrGLvoid (*) (GrGLenum target, GrGLsizei levels, GrGLenum internalformat, GrGLsizei width, GrGLsizei height);
;
  using GrGLDiscardFramebufferFn = GrGLvoid (*) (GrGLenum target, GrGLsizei numAttachments, const GrGLenum* attachments);
;
  using GrGLTexSubImage2DFn = GrGLvoid (*) (GrGLenum target, GrGLint level, GrGLint xoffset, GrGLint yoffset, GrGLsizei width, GrGLsizei height, GrGLenum format, GrGLenum type, const GrGLvoid* pixels);
;
  using GrGLTextureBarrierFn = GrGLvoid (*) ();
;
  using GrGLUniform1fFn = GrGLvoid (*) (GrGLint location, GrGLfloat v0);
;
  using GrGLUniform1iFn = GrGLvoid (*) (GrGLint location, GrGLint v0);
;
  using GrGLUniform1fvFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLfloat* v);
;
  using GrGLUniform1ivFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLint* v);
;
  using GrGLUniform2fFn = GrGLvoid (*) (GrGLint location, GrGLfloat v0, GrGLfloat v1);
;
  using GrGLUniform2iFn = GrGLvoid (*) (GrGLint location, GrGLint v0, GrGLint v1);
;
  using GrGLUniform2fvFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLfloat* v);
;
  using GrGLUniform2ivFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLint* v);
;
  using GrGLUniform3fFn = GrGLvoid (*) (GrGLint location, GrGLfloat v0, GrGLfloat v1, GrGLfloat v2);
;
  using GrGLUniform3iFn = GrGLvoid (*) (GrGLint location, GrGLint v0, GrGLint v1, GrGLint v2);
;
  using GrGLUniform3fvFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLfloat* v);
;
  using GrGLUniform3ivFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLint* v);
;
  using GrGLUniform4fFn = GrGLvoid (*) (GrGLint location, GrGLfloat v0, GrGLfloat v1, GrGLfloat v2, GrGLfloat v3);
;
  using GrGLUniform4iFn = GrGLvoid (*) (GrGLint location, GrGLint v0, GrGLint v1, GrGLint v2, GrGLint v3);
;
  using GrGLUniform4fvFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLfloat* v);
;
  using GrGLUniform4ivFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, const GrGLint* v);
;
  using GrGLUniformMatrix2fvFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, GrGLboolean transpose, const GrGLfloat* value);
;
  using GrGLUniformMatrix3fvFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, GrGLboolean transpose, const GrGLfloat* value);
;
  using GrGLUniformMatrix4fvFn = GrGLvoid (*) (GrGLint location, GrGLsizei count, GrGLboolean transpose, const GrGLfloat* value);
;
  using GrGLUnmapBufferFn = GrGLboolean (*) (GrGLenum target);
;
  using GrGLUnmapBufferSubDataFn = GrGLvoid (*) (const GrGLvoid* mem);
;
  using GrGLUnmapTexSubImage2DFn = GrGLvoid (*) (const GrGLvoid* mem);
;
  using GrGLUseProgramFn = GrGLvoid (*) (GrGLuint program);
;
  using GrGLVertexAttrib1fFn = GrGLvoid (*) (GrGLuint indx, const GrGLfloat value);
;
  using GrGLVertexAttrib2fvFn = GrGLvoid (*) (GrGLuint indx, const GrGLfloat* values);
;
  using GrGLVertexAttrib3fvFn = GrGLvoid (*) (GrGLuint indx, const GrGLfloat* values);
;
  using GrGLVertexAttrib4fvFn = GrGLvoid (*) (GrGLuint indx, const GrGLfloat* values);
;
  using GrGLVertexAttribDivisorFn = GrGLvoid (*) (GrGLuint index, GrGLuint divisor);
;
  using GrGLVertexAttribIPointerFn = GrGLvoid (*) (GrGLuint indx, GrGLint size, GrGLenum type, GrGLsizei stride, const GrGLvoid* ptr);
;
  using GrGLVertexAttribPointerFn = GrGLvoid (*) (GrGLuint indx, GrGLint size, GrGLenum type, GrGLboolean normalized, GrGLsizei stride, const GrGLvoid* ptr);
;
  using GrGLViewportFn = GrGLvoid (*) (GrGLint x, GrGLint y, GrGLsizei width, GrGLsizei height);
;
/* GL_NV_path_rendering */
  using GrGLMatrixLoadfFn = GrGLvoid (*) (GrGLenum matrixMode, const GrGLfloat* m);
;
  using GrGLMatrixLoadIdentityFn = GrGLvoid (*) (GrGLenum);
;
  using GrGLPathCommandsFn = GrGLvoid (*) (GrGLuint path, GrGLsizei numCommands, const GrGLubyte* commands, GrGLsizei numCoords, GrGLenum coordType, const GrGLvoid* coords);
;
  using GrGLPathParameteriFn = GrGLvoid (*) (GrGLuint path, GrGLenum pname, GrGLint value);
;
  using GrGLPathParameterfFn = GrGLvoid (*) (GrGLuint path, GrGLenum pname, GrGLfloat value);
;
  using GrGLGenPathsFn = GrGLuint (*) (GrGLsizei range);
;
  using GrGLDeletePathsFn = GrGLvoid (*) (GrGLuint path, GrGLsizei range);
;
  using GrGLIsPathFn = GrGLboolean (*) (GrGLuint path);
;
  using GrGLPathStencilFuncFn = GrGLvoid (*) (GrGLenum func, GrGLint ref, GrGLuint mask);
;
  using GrGLStencilFillPathFn = GrGLvoid (*) (GrGLuint path, GrGLenum fillMode, GrGLuint mask);
;
  using GrGLStencilStrokePathFn = GrGLvoid (*) (GrGLuint path, GrGLint reference, GrGLuint mask);
;
  using GrGLStencilFillPathInstancedFn = GrGLvoid (*) (GrGLsizei numPaths, GrGLenum pathNameType, const GrGLvoid* paths, GrGLuint pathBase, GrGLenum fillMode, GrGLuint mask, GrGLenum transformType, const GrGLfloat* transformValues);
;
  using GrGLStencilStrokePathInstancedFn = GrGLvoid (*) (GrGLsizei numPaths, GrGLenum pathNameType, const GrGLvoid* paths, GrGLuint pathBase, GrGLint reference, GrGLuint mask, GrGLenum transformType, const GrGLfloat* transformValues);
;
  using GrGLCoverFillPathFn = GrGLvoid (*) (GrGLuint path, GrGLenum coverMode);
;
  using GrGLCoverStrokePathFn = GrGLvoid (*) (GrGLuint name, GrGLenum coverMode);
;
  using GrGLCoverFillPathInstancedFn = GrGLvoid (*) (GrGLsizei numPaths, GrGLenum pathNameType, const GrGLvoid* paths, GrGLuint pathBase, GrGLenum coverMode, GrGLenum transformType, const GrGLfloat* transformValues);
;
  using GrGLCoverStrokePathInstancedFn = GrGLvoid (*) (GrGLsizei numPaths, GrGLenum pathNameType, const GrGLvoid* paths, GrGLuint pathBase, GrGLenum coverMode, GrGLenum transformType, const GrGLfloat* transformValues);
;
// NV_path_rendering v1.2
  using GrGLStencilThenCoverFillPathFn = GrGLvoid (*) (GrGLuint path, GrGLenum fillMode, GrGLuint mask, GrGLenum coverMode);
;
  using GrGLStencilThenCoverStrokePathFn = GrGLvoid (*) (GrGLuint path, GrGLint reference, GrGLuint mask, GrGLenum coverMode);
;
  using GrGLStencilThenCoverFillPathInstancedFn = GrGLvoid (*) (GrGLsizei numPaths, GrGLenum pathNameType, const GrGLvoid* paths, GrGLuint pathBase, GrGLenum fillMode, GrGLuint mask, GrGLenum coverMode, GrGLenum transformType, const GrGLfloat* transformValues);
;
  using GrGLStencilThenCoverStrokePathInstancedFn = GrGLvoid (*) (GrGLsizei numPaths, GrGLenum pathNameType, const GrGLvoid* paths, GrGLuint pathBase, GrGLint reference, GrGLuint mask, GrGLenum coverMode, GrGLenum transformType, const GrGLfloat* transformValues);
;
// NV_path_rendering v1.3
  using GrGLProgramPathFragmentInputGenFn = GrGLvoid (*) (GrGLuint program, GrGLint location, GrGLenum genMode, GrGLint components, const GrGLfloat* coeffs);
;
// CHROMIUM_path_rendering
  using GrGLBindFragmentInputLocationFn = GrGLvoid (*) (GrGLuint program, GrGLint location, const GrGLchar* name);
;
/* ARB_program_interface_query */
  using GrGLGetProgramResourceLocationFn = GrGLint (*) (GrGLuint program, GrGLenum programInterface, const GrGLchar* name);
;
/* GL_NV_framebuffer_mixed_samples */
  using GrGLCoverageModulationFn = GrGLvoid (*) (GrGLenum components);
;
/* EXT_multi_draw_indirect */
  using GrGLMultiDrawArraysIndirectFn = GrGLvoid (*) (GrGLenum mode, const GrGLvoid* indirect, GrGLsizei drawcount, GrGLsizei stride);
;
  using GrGLMultiDrawElementsIndirectFn = GrGLvoid (*) (GrGLenum mode, GrGLenum type, const GrGLvoid* indirect, GrGLsizei drawcount, GrGLsizei stride);
;
/* ARB_sync */
  using GrGLFenceSyncFn = GrGLsync (*) (GrGLenum condition, GrGLbitfield flags);
;
  using GrGLIsSyncFn = GrGLboolean (*) (GrGLsync sync);
;
  using GrGLClientWaitSyncFn = GrGLenum (*) (GrGLsync sync, GrGLbitfield flags, GrGLuint64 timeout);
;
  using GrGLWaitSyncFn = GrGLvoid (*) (GrGLsync sync, GrGLbitfield flags, GrGLuint64 timeout);
;
  using GrGLDeleteSyncFn = GrGLvoid (*) (GrGLsync sync);
;
/* ARB_internalformat_query */
  using GrGLGetInternalformativFn = GrGLvoid (*) (GrGLenum target, GrGLenum internalformat, GrGLenum pname, GrGLsizei bufSize, GrGLint* params);
;
/* KHR_debug */
  using GrGLDebugMessageControlFn = GrGLvoid (*) (GrGLenum source, GrGLenum type, GrGLenum severity, GrGLsizei count, const GrGLuint* ids, GrGLboolean enabled);
;
  using GrGLDebugMessageInsertFn = GrGLvoid (*) (GrGLenum source, GrGLenum type, GrGLuint id, GrGLenum severity, GrGLsizei length, const GrGLchar* buf);
;
  using GrGLDebugMessageCallbackFn = GrGLvoid (*) (GRGLDEBUGPROC callback, const GrGLvoid* userParam);
;
  using GrGLGetDebugMessageLogFn = GrGLuint (*) (GrGLuint count, GrGLsizei bufSize, GrGLenum* sources, GrGLenum* types, GrGLuint* ids, GrGLenum* severities, GrGLsizei* lengths, GrGLchar* messageLog);
;
  using GrGLPushDebugGroupFn = GrGLvoid (*) (GrGLenum source, GrGLuint id, GrGLsizei length, const GrGLchar* message);
;
  using GrGLPopDebugGroupFn = GrGLvoid (*) ();
;
  using GrGLObjectLabelFn = GrGLvoid (*) (GrGLenum identifier, GrGLuint name, GrGLsizei length, const GrGLchar* label);
;
/** EXT_window_rectangles */
  using GrGLWindowRectanglesFn = GrGLvoid (*) (GrGLenum mode, GrGLsizei count, const GrGLint box[]);
;
/** EGL functions */
  using GrEGLQueryStringFn = const char* (*) (GrEGLDisplay dpy, GrEGLint name);
;
  using GrEGLGetCurrentDisplayFn = GrEGLDisplay (*) ();
;
  using GrEGLCreateImageFn = GrEGLImage (*) (GrEGLDisplay dpy, GrEGLContext ctx, GrEGLenum target, GrEGLClientBuffer buffer, const GrEGLint* attrib_list);
;
  using GrEGLDestroyImageFn = GrEGLBoolean (*) (GrEGLDisplay dpy, GrEGLImage image);
;
  }
// This is a lighter-weight std::function, trying to reduce code size and compile time
// by only supporting the exact use cases we require.
template <typename T>
class GrGLFunction;
template <typename R, typename... Args>
class GrGLFunction<R GR_GL_FUNCTION_TYPE(Args...)>
{
public:
  using Fn = R (*) (Args...);
;
    // Construct empty.
  GrGLFunction();
  GrGLFunction(std::nullptr_t)
  {
  }
    // Construct from a simple function pointer.
  GrGLFunction(Fn* fn_ptr)
  {
    static_assert(sizeof(fn_ptr) <= sizeof(fBuf), "fBuf is too small");
    if (fn_ptr)
    {
      memcpy(fBuf, &fn_ptr, sizeof(fn_ptr));
    }
  }
    // Construct from a small closure.
  template <typename Closure>
  GrGLFunction(Closure closure)
    : GrGLFunction()
  {
    static_assert(sizeof(Closure) <= sizeof(fBuf), "fBuf is too small");
#  if  defined(__APPLE__)  // I am having serious trouble getting these to work with all STLs...
    static_assert(std::is_trivially_copyable<Closure>::value, "");
    static_assert(std::is_trivially_destructible<Closure>::value, "");
#  endif
    memcpy(fBuf, &closure, sizeof(closure));
  }
  R operator()(Args... args) const
  {
    SkASSERT(fCall);
    return fCall(fBuf, std::forward<Args>(args)...);
  }
  operator bool() const
  {
    return fCall != nullptr;
  }
  void reset()
  {
    fCall = nullptr;
  }
private:
  using Call = R (*) (const void* buf, Args...);
;
  Call* fCall = nullptr;
  size_t fBuf[4];
};
#endif
