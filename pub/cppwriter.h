/*
The MIT License (MIT)

Copyright (c) 2014

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __CPPPARSER_CPPWRITER_H__
#define __CPPPARSER_CPPWRITER_H__

#include "cppdom.h"
#include "cppindent.h"

#include <string>

//////////////////////////////////////////////////////////////////////////

/**
 * Responsible for emitting C/C++ source from CppDom data structure.
 * Implementation of emitting various C/C++ objects should never change
 * the style of code generated. Addition of new functionality and bug fixes
 * are allowed but care must be taken not to change the style of emitted code.
 */
class CppWriter
{
public:
  CppWriter();

  enum EmittingType
  {
    kRaw,		///< No intelligence is applied and things are emitted as is.
    kHeader,	///< No function definition is emitted unless it is explicitly inline
    kSource		///< No method declaration is emitted unless it is part of the class that is defined in the same file.
  };
  void			setEmittingType(EmittingType type);
  EmittingType	getEmittingType() const;

public:

public:
  // This only delegate to other emit() method based on type.
  virtual void emit			      (const CppObj*				  cppObj,			  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVar		    (const CppVar*				  varObj,			  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVarList	  (const CppVarList*			varListObj,		std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitEnum		    (const CppEnum*				  enmObj,			  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitTypedef	  (const CppTypedef*			typedefObj,		std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitFwdDecl	  (const CppFwdClsDecl*		fwdClsDeclObj,std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitCompound	  (const CppCompound*		  compoundObj,	std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitFunction	  (const CppFunction*			funcObj,		  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitFunctionPtr(const CppFunctionPtr*	funcPtrObj,		std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitConstructor(const CppConstructor*	ctorObj,		  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitDestructor	(const CppDestructor*		dtorObj,		  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitDocComment	(const CppDocComment*		docCommentObj,std::ostream& stm, CppIndent indentation = CppIndent()) const;

  virtual void emitExpr		    (const CppExpr*				  exprObj,		  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitBlankLines	(const CppBlankLine*		blankLineObj,	std::ostream& stm) const;
  virtual void emitDefine		  (const CppDefine*			  defineObj,		std::ostream& stm) const;
  virtual void emitUndef		  (const CppUndef*			  undefObj,		  std::ostream& stm) const;
  virtual void emitInclude	  (const CppInclude*			includeObj,		std::ostream& stm) const;
  virtual void emitHashIf		  (const CppHashIf*			  hashIfObj,		std::ostream& stm) const;
  virtual void emitPragma		  (const CppPragma*			  pragmaObj,		std::ostream& stm) const;
  virtual void emitBlob		    (const CppBlob*				  blobObj,		  std::ostream& stm) const;

  virtual void emitVarType	  (const CppVarType*			varTypeObj,		std::ostream& stm) const;
  virtual void emitParamList  (const CppParamList*		paramListObj,	std::ostream& stm) const;
  virtual void emitExprAtom	  (const CppExprAtom&			exprObj,		  std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitExprList	  (const CppExprList*			exprList,		  std::ostream& stm, CppIndent indentation = CppIndent()) const;

public:
  void emitVar        (const CppVar*				  varObj,       std::ostream& stm, bool skipName) const;
  void emitParamList  (const CppParamList*		paramListObj, std::ostream& stm, bool skipName) const;
  void emitFunctionPtr(const CppFunctionPtr*	funcPtrObj,   std::ostream& stm, bool skipName) const;
  void emitFunction   (const CppFunction*			funcObj,      std::ostream& stm, bool skipParamName) const;
  void emitConstructor(const CppConstructor*	ctorObj,      std::ostream& stm, bool skipParamName) const;

private:
  void emitVar        (const CppVar*				  varObj,       std::ostream& stm, CppIndent indentation, bool skipName) const;
  void emitFunctionPtr(const CppFunctionPtr*	funcPtrObj,   std::ostream& stm, CppIndent indentation, bool skipName) const;
  void emitFunction   (const CppFunction*			funcObj,      std::ostream& stm, CppIndent indentation, bool skipName, bool skipParamName) const;
  void emitConstructor(const CppConstructor*	ctorObj,      std::ostream& stm, CppIndent indentation, bool skipParamName) const;

private:
  mutable CppIndent	preproIndent_;

  EmittingType emittingType_;
};

inline CppWriter::CppWriter()
  : emittingType_(kRaw)
{
}

inline void CppWriter::setEmittingType(EmittingType emittingType)
{
  emittingType_ = emittingType;
}

inline CppWriter::EmittingType CppWriter::getEmittingType() const
{
  return emittingType_;
}

inline void CppWriter::emitVar(const CppVar* varObj, std::ostream& stm, bool skipName) const
{
  emitVar(varObj, stm, CppIndent(), skipName);
}

inline void CppWriter::emitFunctionPtr(const CppFunctionPtr* funcPtrObj, std::ostream& stm, bool skipName) const
{
  if (funcPtrObj->attr_&kTypedef)
    return; // Typedef of funcptr without name makes no sense.
  emitFunction(funcPtrObj, stm, CppIndent(), skipName, skipName);
}

inline void CppWriter::emitFunction(const CppFunction* funcObj, std::ostream& stm, bool skipParamName) const
{
  emitFunction(funcObj, stm, CppIndent(), false, skipParamName);
}

inline void CppWriter::emitConstructor(const CppConstructor* ctorObj, std::ostream& stm, bool skipParamName) const
{
  emitConstructor(ctorObj, stm, CppIndent(), skipParamName);
}

inline std::ostream& operator <<(std::ostream& stm, const CppIndent& indentation)
{
  indentation.emit(stm);
  return stm;
}

inline std::ostream& operator <<(std::ostream& stm, CppObjProtLevel prot)
{
  switch (prot)
  {
  case kPublic    :
    stm << "public";
    break;
  case kProtected :
    stm << "protected";
    break;
  case kPrivate   :
    stm << "private";
    break;
  }
  return stm;
}

inline std::ostream& operator <<(std::ostream& stm, CppCompoundType cmpndType)
{
  switch (cmpndType)
  {
  case kNamespace :
    stm << "namespace";
    break;
  case kClass     :
    stm << "class";
    break;
  case kStruct    :
    stm << "struct";
    break;
  case kUnion     :
    stm << "union";
    break;
  }
  return stm;
}

#endif //__CPPPARSER_CPPWRITER_H__
