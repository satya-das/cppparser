// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BF0AACF9_1254_4444_8198_D0A5232233C3
#define BF0AACF9_1254_4444_8198_D0A5232233C3

#include "cppast/cppast.h"
#include "cppwriter/cppindent.h"

#include <string>

namespace cppcodegen {

/**
 * Responsible for emitting C/C++ source from cppast data structure.
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
  virtual void emit(const cppast::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVar(const cppast::CppVar& varObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVarList(const cppast::CppVarList& varListObj,
                           std::ostream&             stm,
                           CppIndent                 indentation = CppIndent()) const;
  virtual void emitEnum(const cppast::CppEnum& enmObj,
                        std::ostream&          stm,
                        bool                   emitNewLine,
                        CppIndent              indentation = CppIndent()) const;
  virtual void emitTypedef(const cppast::CppTypedefName& typedefName,
                           std::ostream&                 stm,
                           CppIndent                     indentation = CppIndent()) const;
  virtual void emitUsingDecl(const cppast::CppUsingDecl& usingDecl,
                             std::ostream&               stm,
                             CppIndent                   indentation = CppIndent()) const;
  virtual void emitTypedefList(const cppast::CppTypedefList& typedefList,
                               std::ostream&                 stm,
                               CppIndent                     indentation = CppIndent()) const;
  virtual void emitFwdDecl(const cppast::CppForwardClassDecl& fwdClsDeclObj,
                           std::ostream&                      stm,
                           CppIndent                          indentation = CppIndent()) const;
  virtual void emitMacroCall(const cppast::CppMacroCall& macroCallObj,
                             std::ostream&               stm,
                             CppIndent                   indentation = CppIndent()) const;
  virtual void emitEntityAccessSpecifier(const cppast::CppEntityAccessSpecifier& entityAccessSpecifier,
                                         std::ostream&                           stm,
                                         CppIndent                               indentation = CppIndent(),
                                         bool                                    emitNewLine = true) const;
  virtual void emitCompound(const cppast::CppCompound& compoundObj,
                            std::ostream&              stm,
                            CppIndent                  indentation = CppIndent(),
                            bool                       emitNewLine = true) const;
  virtual void emitFunction(const cppast::CppFunction& funcObj,
                            std::ostream&              stm,
                            bool                       emitNewLine,
                            CppIndent                  indentation = CppIndent()) const;
  virtual void emitFunctionPtr(const cppast::CppFunctionPointer& funcPtrObj,
                               std::ostream&                     stm,
                               bool                              emitNewLine,
                               CppIndent                         indentation = CppIndent()) const;
  virtual void emitConstructor(const cppast::CppConstructor& ctorObj,
                               std::ostream&                 stm,
                               CppIndent                     indentation = CppIndent()) const;
  virtual void emitDestructor(const cppast::CppDestructor& dtorObj,
                              std::ostream&                stm,
                              CppIndent                    indentation = CppIndent()) const;
  virtual void emitTypeConverter(const cppast::CppTypeConverter& typeConverterObj,
                                 std::ostream&                   stm,
                                 CppIndent                       indentation = CppIndent()) const;
  virtual void emitDocComment(const cppast::CppDocumentationComment& docCommentObj,
                              std::ostream&                          stm,
                              CppIndent                              indentation = CppIndent()) const;

  virtual void emitExpr(const cppast::CppExpression& exprObj,
                        std::ostream&                stm,
                        CppIndent                    indentation = CppIndent()) const;
  virtual void emitDefine(const cppast::CppMacroDefinition& defineObj, std::ostream& stm) const;
  virtual void emitUndef(const cppast::CppPreprocessorUndef& undefObj, std::ostream& stm) const;
  virtual void emitInclude(const cppast::CppPreprocessorInclude& includeObj, std::ostream& stm) const;
  virtual void emitHashIf(const cppast::CppPreprocessorConditional& hashIfObj, std::ostream& stm) const;
  virtual void emitHashIf(cppast::PreprocessorConditionalType condType,
                          const std::string&                  cond,
                          std::ostream&                       stm) const;
  virtual void emitEndIf(std::ostream& stm) const;
  virtual void emitPragma(const cppast::CppPreprocessorPragma& pragmaObj, std::ostream& stm) const;
  virtual void emitBlob(const cppast::CppBlob& blobObj,
                        std::ostream&          stm,
                        bool                   formatLineStarts,
                        CppIndent              indentation) const;

  virtual void emitVarType(const cppast::CppVarType& varTypeObj, std::ostream& stm) const;
  virtual void emitParamList(const std::vector<const cppast::CppEntity*>& paramListObj, std::ostream& stm) const;

  virtual void emitIfBlock(const cppast::CppIfBlock& ifBlock,
                           std::ostream&             stm,
                           CppIndent                 indentation = CppIndent()) const;
  virtual void emitWhileBlock(const cppast::CppWhileBlock& whileBlock,
                              std::ostream&                stm,
                              CppIndent                    indentation = CppIndent()) const;
  virtual void emitDoBlock(const cppast::CppDoWhileBlock& doBlock,
                           std::ostream&                  stm,
                           CppIndent                      indentation = CppIndent()) const;
  virtual void emitForBlock(const cppast::CppForBlock& forBlock,
                            std::ostream&              stm,
                            CppIndent                  indentation = CppIndent()) const;
  virtual void emitSwitchBlock(const cppast::CppSwitchBlock& switchBlock,
                               std::ostream&                 stm,
                               CppIndent                     indentation = CppIndent()) const;

public:
  void emitVar(const cppast::CppVar& varObj, std::ostream& stm, bool skipName) const;
  void emitParamList(const std::vector<const cppast::CppEntity*>& paramListObj, std::ostream& stm, bool skipName) const;
  void emitFunctionPtr(const cppast::CppFunctionPointer& funcPtrObj,
                       std::ostream&                     stm,
                       bool                              skipName,
                       bool                              emitNewLine) const;
  void emitFunction(const cppast::CppFunction& funcObj, std::ostream& stm, bool skipParamName, bool emitNewLine) const;
  void emitConstructor(const cppast::CppConstructor& ctorObj, std::ostream& stm, bool skipParamName) const;
  void emitTemplSpec(const cppast::CppTemplateParams& templSpec, std::ostream& stm, CppIndent indentation) const;

private:
  void emit(const cppast::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation, bool noNewLine) const;
  void emitVar(const cppast::CppVar& varObj, std::ostream& stm, CppIndent indentation, bool skipName) const;
  void emitFunctionPtr(const cppast::CppFunctionPointer& funcPtrObj,
                       std::ostream&                     stm,
                       CppIndent                         indentation,
                       bool                              skipName,
                       bool                              emitNewLine) const;
  void emitFunction(const cppast::CppFunction& funcObj,
                    std::ostream&              stm,
                    CppIndent                  indentation,
                    bool                       skipName,
                    bool                       skipParamName,
                    bool                       emitNewLine) const;
  void emitConstructor(const cppast::CppConstructor& ctorObj,
                       std::ostream&                 stm,
                       CppIndent                     indentation,
                       bool                          skipParamName) const;

  void emitVarDecl(std::ostream& stm, const cppast::CppVarDecl& varDecl, bool skipName) const;

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

inline void CppWriter::emitVar(const cppast::CppVar& varObj, std::ostream& stm, bool skipName) const
{
  emitVar(varObj, stm, CppIndent(), skipName);
}

inline void CppWriter::emitFunctionPtr(const cppast::CppFunctionPointer& funcPtrObj,
                                       std::ostream&                     stm,
                                       bool                              skipName,
                                       bool                              emitNewLine) const
{
  if (funcPtrObj.attr() & cppast::CppIdentifierAttrib::kTypedef)
    return; // Typedef of funcptr without name makes no sense.
  emitFunction(funcPtrObj, stm, CppIndent(), skipName, skipName, emitNewLine);
}

inline void CppWriter::emitFunction(const cppast::CppFunction& funcObj,
                                    std::ostream&              stm,
                                    bool                       skipParamName,
                                    bool                       emitNewLine) const
{
  emitFunction(funcObj, stm, CppIndent(), false, skipParamName, emitNewLine);
}

inline void CppWriter::emitConstructor(const cppast::CppConstructor& ctorObj,
                                       std::ostream&                 stm,
                                       bool                          skipParamName) const
{
  emitConstructor(ctorObj, stm, CppIndent(), skipParamName);
}

inline std::ostream& operator<<(std::ostream& stm, const CppIndent& indentation)
{
  indentation.emit(stm);
  return stm;
}

inline std::ostream& operator<<(std::ostream& stm, cppast::CppAccessType accessType)
{
  switch (accessType)
  {
    case cppast::CppAccessType::PUBLIC:
      stm << "public";
      break;
    case cppast::CppAccessType::PROTECTED:
      stm << "protected";
      break;
    case cppast::CppAccessType::PRIVATE:
      stm << "private";
      break;

    default:
      break;
  }
  return stm;
}

inline std::ostream& operator<<(std::ostream& stm, cppast::CppCompoundType cmpndType)
{
  switch (cmpndType)
  {
    case cppast::CppCompoundType::NAMESPACE:
      stm << "namespace";
      break;
    case cppast::CppCompoundType::CLASS:
      stm << "class";
      break;
    case cppast::CppCompoundType::STRUCT:
      stm << "struct";
      break;
    case cppast::CppCompoundType::UNION:
      stm << "union";
      break;

    default:
      break;
  }
  return stm;
}

} // namespace cppcodegen

#endif /* BF0AACF9_1254_4444_8198_D0A5232233C3 */
