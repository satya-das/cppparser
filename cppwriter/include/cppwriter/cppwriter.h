// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef BF0AACF9_1254_4444_8198_D0A5232233C3
#define BF0AACF9_1254_4444_8198_D0A5232233C3

#include "cppast/cppast.h"
#include "cppwriter/cppindent.h"

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
  virtual void emit(const CppAst::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVar(const CppAst::CppVar& varObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitVarList(const CppAst::CppVarList& varListObj,
                           std::ostream&             stm,
                           CppIndent                 indentation = CppIndent()) const;
  virtual void emitEnum(const CppAst::CppEnum& enmObj,
                        std::ostream&          stm,
                        bool                   emitNewLine,
                        CppIndent              indentation = CppIndent()) const;
  virtual void emitTypedef(const CppAst::CppTypedefName& typedefName,
                           std::ostream&                 stm,
                           CppIndent                     indentation = CppIndent()) const;
  virtual void emitUsingDecl(const CppAst::CppUsingDecl& usingDecl,
                             std::ostream&               stm,
                             CppIndent                   indentation = CppIndent()) const;
  virtual void emitTypedefList(const CppAst::CppTypedefList& typedefList,
                               std::ostream&                 stm,
                               CppIndent                     indentation = CppIndent()) const;
  virtual void emitFwdDecl(const CppAst::CppForwardClassDecl& fwdClsDeclObj,
                           std::ostream&                      stm,
                           CppIndent                          indentation = CppIndent()) const;
  virtual void emitMacroCall(const CppAst::CppMacroCall& macroCallObj,
                             std::ostream&               stm,
                             CppIndent                   indentation = CppIndent()) const;
  virtual void emitCompound(const CppAst::CppCompound& compoundObj,
                            std::ostream&              stm,
                            CppIndent                  indentation = CppIndent(),
                            bool                       emitNewLine = true) const;
  virtual void emitFunction(const CppAst::CppFunction& funcObj,
                            std::ostream&              stm,
                            bool                       emitNewLine,
                            CppIndent                  indentation = CppIndent()) const;
  virtual void emitFunctionPtr(const CppAst::CppFunctionPointer& funcPtrObj,
                               std::ostream&                     stm,
                               bool                              emitNewLine,
                               CppIndent                         indentation = CppIndent()) const;
  virtual void emitConstructor(const CppAst::CppConstructor& ctorObj,
                               std::ostream&                 stm,
                               CppIndent                     indentation = CppIndent()) const;
  virtual void emitDestructor(const CppAst::CppDestructor& dtorObj,
                              std::ostream&                stm,
                              CppIndent                    indentation = CppIndent()) const;
  virtual void emitTypeConverter(const CppAst::CppTypeConverter& typeConverterObj,
                                 std::ostream&                   stm,
                                 CppIndent                       indentation = CppIndent()) const;
  virtual void emitDocComment(const CppAst::CppDocumentationComment& docCommentObj,
                              std::ostream&                          stm,
                              CppIndent                              indentation = CppIndent()) const;

  virtual void emitExpr(const CppAst::CppExpr& exprObj, std::ostream& stm, CppIndent indentation = CppIndent()) const;
  virtual void emitDefine(const CppAst::CppMacroDefinition& defineObj, std::ostream& stm) const;
  virtual void emitUndef(const CppAst::CppPreprocessorUndef& undefObj, std::ostream& stm) const;
  virtual void emitInclude(const CppAst::CppPreprocessorInclude& includeObj, std::ostream& stm) const;
  virtual void emitHashIf(const CppAst::CppPreprocessorConditional& hashIfObj, std::ostream& stm) const;
  virtual void emitHashIf(CppAst::PreprocessorConditionalType condType,
                          const std::string&                  cond,
                          std::ostream&                       stm) const;
  virtual void emitEndIf(std::ostream& stm) const;
  virtual void emitPragma(const CppAst::CppPreprocessorPragma& pragmaObj, std::ostream& stm) const;
  virtual void emitBlob(const CppAst::CppBlob& blobObj,
                        std::ostream&          stm,
                        bool                   formatLineStarts,
                        CppIndent              indentation) const;

  virtual void emitVarType(const CppAst::CppVarType& varTypeObj, std::ostream& stm) const;
  virtual void emitParamList(const std::vector<std::unique_ptr<CppAst::CppEntity>>& paramListObj,
                             std::ostream&                                          stm) const;
  virtual void emitExprAtom(const CppAst::CppExprAtom& exprObj,
                            std::ostream&              stm,
                            CppIndent                  indentation = CppIndent()) const;

  virtual void emitIfBlock(const CppAst::CppIfBlock& ifBlock,
                           std::ostream&             stm,
                           CppIndent                 indentation = CppIndent()) const;
  virtual void emitWhileBlock(const CppAst::CppWhileBlock& whileBlock,
                              std::ostream&                stm,
                              CppIndent                    indentation = CppIndent()) const;
  virtual void emitDoBlock(const CppAst::CppDoWhileBlock& doBlock,
                           std::ostream&                  stm,
                           CppIndent                      indentation = CppIndent()) const;
  virtual void emitForBlock(const CppAst::CppForBlock& forBlock,
                            std::ostream&              stm,
                            CppIndent                  indentation = CppIndent()) const;
  virtual void emitSwitchBlock(const CppAst::CppSwitchBlock& switchBlock,
                               std::ostream&                 stm,
                               CppIndent                     indentation = CppIndent()) const;

public:
  void emitVar(const CppAst::CppVar& varObj, std::ostream& stm, bool skipName) const;
  void emitParamList(const std::vector<std::unique_ptr<CppAst::CppEntity>>& paramListObj,
                     std::ostream&                                          stm,
                     bool                                                   skipName) const;
  void emitFunctionPtr(const CppAst::CppFunctionPointer& funcPtrObj,
                       std::ostream&                     stm,
                       bool                              skipName,
                       bool                              emitNewLine) const;
  void emitFunction(const CppAst::CppFunction& funcObj, std::ostream& stm, bool skipParamName, bool emitNewLine) const;
  void emitConstructor(const CppAst::CppConstructor& ctorObj, std::ostream& stm, bool skipParamName) const;
  void emitTemplSpec(const CppAst::CppTemplateParams& templSpec, std::ostream& stm, CppIndent indentation) const;

private:
  void emit(const CppAst::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation, bool noNewLine) const;
  void emitVar(const CppAst::CppVar& varObj, std::ostream& stm, CppIndent indentation, bool skipName) const;
  void emitFunctionPtr(const CppAst::CppFunctionPointer& funcPtrObj,
                       std::ostream&                     stm,
                       CppIndent                         indentation,
                       bool                              skipName,
                       bool                              emitNewLine) const;
  void emitFunction(const CppAst::CppFunction& funcObj,
                    std::ostream&              stm,
                    CppIndent                  indentation,
                    bool                       skipName,
                    bool                       skipParamName,
                    bool                       emitNewLine) const;
  void emitConstructor(const CppAst::CppConstructor& ctorObj,
                       std::ostream&                 stm,
                       CppIndent                     indentation,
                       bool                          skipParamName) const;

  void emitVarDecl(std::ostream& stm, const CppAst::CppVarDecl& varDecl, bool skipName) const;

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

inline void CppWriter::emitVar(const CppAst::CppVar& varObj, std::ostream& stm, bool skipName) const
{
  emitVar(varObj, stm, CppIndent(), skipName);
}

inline void CppWriter::emitFunctionPtr(const CppAst::CppFunctionPointer& funcPtrObj,
                                       std::ostream&                     stm,
                                       bool                              skipName,
                                       bool                              emitNewLine) const
{
  if (funcPtrObj.attr() & CppAst::CppIdentifierAttrib::kTypedef)
    return; // Typedef of funcptr without name makes no sense.
  emitFunction(funcPtrObj, stm, CppIndent(), skipName, skipName, emitNewLine);
}

inline void CppWriter::emitFunction(const CppAst::CppFunction& funcObj,
                                    std::ostream&              stm,
                                    bool                       skipParamName,
                                    bool                       emitNewLine) const
{
  emitFunction(funcObj, stm, CppIndent(), false, skipParamName, emitNewLine);
}

inline void CppWriter::emitConstructor(const CppAst::CppConstructor& ctorObj,
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

inline std::ostream& operator<<(std::ostream& stm, CppAst::CppAccessType accessType)
{
  switch (accessType)
  {
    case CppAst::CppAccessType::PUBLIC:
      stm << "public";
      break;
    case CppAst::CppAccessType::PROTECTED:
      stm << "protected";
      break;
    case CppAst::CppAccessType::PRIVATE:
      stm << "private";
      break;

    default:
      break;
  }
  return stm;
}

inline std::ostream& operator<<(std::ostream& stm, CppAst::CppCompoundType cmpndType)
{
  switch (cmpndType)
  {
    case CppAst::CppCompoundType::NAMESPACE:
      stm << "namespace";
      break;
    case CppAst::CppCompoundType::CLASS:
      stm << "class";
      break;
    case CppAst::CppCompoundType::STRUCT:
      stm << "struct";
      break;
    case CppAst::CppCompoundType::UNION:
      stm << "union";
      break;

    default:
      break;
  }
  return stm;
}

#endif /* BF0AACF9_1254_4444_8198_D0A5232233C3 */
