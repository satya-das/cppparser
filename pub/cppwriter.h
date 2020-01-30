/*
   The MIT License (MIT)

   Copyright (c) 2018 Satya Das

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

#pragma once

#include "cppast.h"
#include "cppindent.h"

#include <string>

//////////////////////////////////////////////////////////////////////////

/**
 * Responsible for emitting C/C++ source from CppAst data structure.
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
    kRaw,    ///< No intelligence is applied and things are emitted as is.
    kHeader, ///< No function definition is emitted unless it is explicitly inline
    kSource  ///< No method declaration is emitted unless it is part of the class that is defined in the same file.
  };
  void         setEmittingType(EmittingType type);
  EmittingType getEmittingType() const;

public:
public:
  // This only delegate to other emit() method based on type.
  virtual void emit(const CppObj* cppObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVar(const CppVar* varObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVarList(const CppVarList* varListObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitEnum(const CppEnum* enmObj,
                        std::ostream&  stm,
                        bool           emitNewLine,
                        CppIndent      indentation = CppIndent()) const;
  virtual void emitTypedef(const CppTypedefName* typedefName,
                           std::ostream&         stm,
                           CppIndent             indentation = CppIndent()) const;
  virtual void emitUsingDecl(const CppUsingDecl* usingDecl,
                             std::ostream&       stm,
                             CppIndent           indentation = CppIndent()) const;
  virtual void emitTypedefList(const CppTypedefList* typedefList,
                               std::ostream&         stm,
                               CppIndent             indentation = CppIndent()) const;
  virtual void emitFwdDecl(const CppFwdClsDecl* fwdClsDeclObj,
                           std::ostream&        stm,
                           CppIndent            indentation = CppIndent()) const;
  virtual void emitMacroCall(const CppMacroCall* macroCallObj,
                             std::ostream&       stm,
                             CppIndent           indentation = CppIndent()) const;
  virtual void emitCompound(const CppCompound* compoundObj,
                            std::ostream&      stm,
                            CppIndent          indentation = CppIndent(),
                            bool               emitNewLine = true) const;
  virtual void emitFunction(const CppFunction* funcObj,
                            std::ostream&      stm,
                            bool               emitNewLine,
                            CppIndent          indentation = CppIndent()) const;
  virtual void emitFunctionPtr(const CppFunctionPointer* funcPtrObj,
                               std::ostream&             stm,
                               bool                      emitNewLine,
                               CppIndent                 indentation = CppIndent()) const;
  virtual void emitConstructor(const CppConstructor* ctorObj,
                               std::ostream&         stm,
                               CppIndent             indentation = CppIndent()) const;
  virtual void emitDestructor(const CppDestructor* dtorObj,
                              std::ostream&        stm,
                              CppIndent            indentation = CppIndent()) const;
  virtual void emitTypeConverter(const CppTypeConverter* typeConverterObj,
                                 std::ostream&           stm,
                                 CppIndent               indentation = CppIndent()) const;
  virtual void emitDocComment(const CppDocComment* docCommentObj,
                              std::ostream&        stm,
                              CppIndent            indentation = CppIndent()) const;

  virtual void emitExpr(const CppExpr* exprObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitDefine(const CppDefine* defineObj, std::ostream& stm) const;
  virtual void emitUndef(const CppUndef* undefObj, std::ostream& stm) const;
  virtual void emitInclude(const CppInclude* includeObj, std::ostream& stm) const;
  virtual void emitHashIf(const CppHashIf* hashIfObj, std::ostream& stm) const;
  virtual void emitHashIf(CppHashIf::CondType condType, const std::string& cond, std::ostream& stm) const;
  virtual void emitEndIf(std::ostream& stm) const;
  virtual void emitPragma(const CppPragma* pragmaObj, std::ostream& stm) const;
  virtual void emitBlob(const CppBlob* blobObj, std::ostream& stm) const;

  virtual void emitVarType(const CppVarType* varTypeObj, std::ostream& stm) const;
  virtual void emitParamList(const CppParamVector* paramListObj, std::ostream& stm) const;
  virtual void emitExprAtom(const CppExprAtom& exprObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;

  virtual void emitIfBlock(const CppIfBlock* ifBlock, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitWhileBlock(const CppWhileBlock* whileBlock,
                              std::ostream&        stm,
                              CppIndent            indentation = CppIndent()) const;
  virtual void emitDoBlock(const CppDoWhileBlock* doBlock,
                           std::ostream&          stm,
                           CppIndent              indentation = CppIndent()) const;
  virtual void emitForBlock(const CppForBlock* forBlock, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitSwitchBlock(const CppSwitchBlock* switchBlock,
                               std::ostream&         stm,
                               CppIndent             indentation = CppIndent()) const;

public:
  void emitVar(const CppVar* varObj, std::ostream& stm, bool skipName) const;
  void emitParamList(const CppParamVector* paramListObj, std::ostream& stm, bool skipName) const;
  void emitFunctionPtr(const CppFunctionPointer* funcPtrObj, std::ostream& stm, bool skipName, bool emitNewLine) const;
  void emitFunction(const CppFunction* funcObj, std::ostream& stm, bool skipParamName, bool emitNewLine) const;
  void emitConstructor(const CppConstructor* ctorObj, std::ostream& stm, bool skipParamName) const;

private:
  void emit(const CppObj* cppObj, std::ostream& stm, CppIndent indentation, bool noNewLine) const;
  void emitVar(const CppVar* varObj, std::ostream& stm, CppIndent indentation, bool skipName) const;
  void emitFunctionPtr(const CppFunctionPointer* funcPtrObj,
                       std::ostream&             stm,
                       CppIndent                 indentation,
                       bool                      skipName,
                       bool                      emitNewLine) const;
  void emitFunction(const CppFunction* funcObj,
                    std::ostream&      stm,
                    CppIndent          indentation,
                    bool               skipName,
                    bool               skipParamName,
                    bool               emitNewLine) const;
  void emitConstructor(const CppConstructor* ctorObj,
                       std::ostream&         stm,
                       CppIndent             indentation,
                       bool                  skipParamName) const;

  void emitTemplSpec(const CppTemplateParamList* templSpec, std::ostream& stm, CppIndent indentation) const;
  void emitVarDecl(std::ostream& stm, const CppVarDecl& varDecl, bool skipName) const;

private:
  mutable CppIndent preproIndent_;

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

inline void CppWriter::emitFunctionPtr(const CppFunctionPointer* funcPtrObj,
                                       std::ostream&             stm,
                                       bool                      skipName,
                                       bool                      emitNewLine) const
{
  if (funcPtrObj->attr() & kTypedef)
    return; // Typedef of funcptr without name makes no sense.
  emitFunction(funcPtrObj, stm, CppIndent(), skipName, skipName, emitNewLine);
}

inline void CppWriter::emitFunction(const CppFunction* funcObj,
                                    std::ostream&      stm,
                                    bool               skipParamName,
                                    bool               emitNewLine) const
{
  emitFunction(funcObj, stm, CppIndent(), false, skipParamName, emitNewLine);
}

inline void CppWriter::emitConstructor(const CppConstructor* ctorObj, std::ostream& stm, bool skipParamName) const
{
  emitConstructor(ctorObj, stm, CppIndent(), skipParamName);
}

inline std::ostream& operator<<(std::ostream& stm, const CppIndent& indentation)
{
  indentation.emit(stm);
  return stm;
}

inline std::ostream& operator<<(std::ostream& stm, CppAccessType accessType)
{
  switch (accessType)
  {
    case CppAccessType::kPublic:
      stm << "public";
      break;
    case CppAccessType::kProtected:
      stm << "protected";
      break;
    case CppAccessType::kPrivate:
      stm << "private";
      break;

    default:
      break;
  }
  return stm;
}

inline std::ostream& operator<<(std::ostream& stm, CppCompoundType cmpndType)
{
  switch (cmpndType)
  {
    case CppCompoundType::kNamespace:
      stm << "namespace";
      break;
    case CppCompoundType::kClass:
      stm << "class";
      break;
    case CppCompoundType::kStruct:
      stm << "struct";
      break;
    case CppCompoundType::kUnion:
      stm << "union";
      break;

    default:
      break;
  }
  return stm;
}
