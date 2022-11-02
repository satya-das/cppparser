// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppwriter/cppwriter.h"

#include "cppast/cpp_compound_info_accessor.h"
#include "cppast/cpp_entity_info_accessor.h"
#include "cppast/cpp_func_info_accessor.h"
#include "cppast/cpp_var_info_accessor.h"

//////////////////////////////////////////////////////////////////////////

namespace {

static void emitAttribute(std::uint32_t attr, std::ostream& stm)
{
  if (attr & CppAst::CppIdentifierAttrib::kStatic)
    stm << "static ";
  else if (attr & CppAst::CppIdentifierAttrib::kExtern)
    stm << "extern ";
  else if (attr & CppAst::CppIdentifierAttrib::kExternC)
    stm << "extern C ";

  if (attr & CppAst::CppIdentifierAttrib::kConst)
    stm << "const ";
  if (attr & CppAst::CppIdentifierAttrib::kConstExpr)
    stm << "constexpr ";
  if (attr & CppAst::CppIdentifierAttrib::kVolatile)
    stm << "volatile ";
  if (attr & CppAst::CppIdentifierAttrib::kMutable)
    stm << "mutable ";
}

static void emitTypeModifier(const CppAst::CppTypeModifier& modifier, std::ostream& stm)
{
  std::uint8_t constBit = 0;
  for (constBit = 0; constBit < modifier.ptrLevel_; ++constBit)
  {
    if (modifier.constBits_ & (1 << constBit))
      stm << " const ";
    stm << "*";
  }
  if (modifier.constBits_ & (1 << constBit))
    stm << " const";
  if (modifier.refType_ == CppAst::CppRefType::BY_REF)
    stm << '&';
  else if (modifier.refType_ == CppAst::CppRefType::RVAL_REF)
    stm << "&&";
}

} // namespace

void CppWriter::emit(const CppAst::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation) const
{
  return emit(cppEntity, stm, indentation, false);
}

void CppWriter::emit(const CppAst::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation, bool noNewLine) const
{
  switch (cppEntity.entityType())
  {
    case CppAst::CppEntityType::PREPROCESSOR_DEFINE:
      return emitDefine((const CppAst::CppMacroDefinition&) cppEntity, stm);
    case CppAst::CppEntityType::PREPROCESSOR_UNDEF:
      return emitUndef((const CppAst::CppPreprocessorUndef&) cppEntity, stm);
    case CppAst::CppEntityType::PREPROCESSOR_INCLUDE:
      return emitInclude((const CppAst::CppPreprocessorInclude&) cppEntity, stm);
    case CppAst::CppEntityType::PREPROCESSOR_CONDITIONAL:
      return emitHashIf((const CppAst::CppPreprocessorConditional&) cppEntity, stm);
    case CppAst::CppEntityType::PREPROCESSOR_PRAGMA:
      return emitPragma((const CppAst::CppPreprocessorPragma&) cppEntity, stm);

    case CppAst::CppEntityType::VAR_TYPE:
      return emitVarType((const CppAst::CppVarType&) cppEntity, stm);
    case CppAst::CppEntityType::VAR:
    {
      emitVar((const CppAst::CppVar&) cppEntity, stm, indentation);
      if (!noNewLine)
        stm << ";\n";
      return;
    }
    case CppAst::CppEntityType::VAR_LIST:
      return emitVarList((const CppAst::CppVarList&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::ENUM:
      return emitEnum((const CppAst::CppEnum&) cppEntity, stm, !noNewLine, indentation);
    case CppAst::CppEntityType::DOCUMENTATION_COMMENT:
      return emitDocComment((const CppAst::CppDocumentationComment&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::USING_DECL:
      return emitUsingDecl((const CppAst::CppUsingDecl&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::TYPEDEF_DECL:
      return emitTypedef((const CppAst::CppTypedefName&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::TYPEDEF_DECL_LIST:
      return emitTypedefList((const CppAst::CppTypedefList&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::COMPOUND:
      return emitCompound((const CppAst::CppCompound&) cppEntity, stm, indentation, !noNewLine);
    case CppAst::CppEntityType::FORWARD_CLASS_DECL:
      return emitFwdDecl((const CppAst::CppForwardClassDecl&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::FUNCTION:
      return emitFunction((const CppAst::CppFunction&) cppEntity, stm, !noNewLine, indentation);
    case CppAst::CppEntityType::CONSTRUCTOR:
      return emitConstructor((const CppAst::CppConstructor&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::DESTRUCTOR:
      return emitDestructor((const CppAst::CppDestructor&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::TYPE_CONVERTER:
      return emitTypeConverter((const CppAst::CppTypeConverter&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::FUNCTION_PTR:
      return emitFunctionPtr((const CppAst::CppFunctionPointer&) cppEntity, stm, !noNewLine, indentation);
    case CppAst::CppEntityType::IF_BLOCK:
      return emitIfBlock((const CppAst::CppIfBlock&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::WHILE_BLOCK:
      return emitWhileBlock((const CppAst::CppWhileBlock&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::DO_WHILE_BLOCK:
      return emitDoBlock((const CppAst::CppDoWhileBlock&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::FOR_BLOCK:
      return emitForBlock((const CppAst::CppForBlock&) cppEntity, stm, indentation);
    case CppAst::CppEntityType::EXPRESSION:
      emitExpr((const CppAst::CppExpr&) cppEntity, stm, indentation);
      if (!noNewLine)
        stm << ";\n";
      break;
    case CppAst::CppEntityType::SWITCH_BLOCK:
      return emitSwitchBlock(static_cast<const CppAst::CppSwitchBlock&>(cppEntity), stm, indentation);
    case CppAst::CppEntityType::MACRO_CALL:
      return emitMacroCall(static_cast<const CppAst::CppMacroCall&>(cppEntity), stm, indentation);

    case CppAst::CppEntityType::BLOB:
      return emitBlob((const CppAst::CppBlob&) cppEntity, stm, true, indentation);

    default:
      break;
  }
}

void CppWriter::emitDefine(const CppAst::CppMacroDefinition& defObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "define " << defObj.name();
  if (!defObj.Definition().empty())
  {
    const auto firstNonSpaceCharPos =
      std::find_if(defObj.Definition().begin(), defObj.Definition().end(), [](char c) { return !std::isspace(c); });
    if (firstNonSpaceCharPos != defObj.Definition().end())
    {
      if (*firstNonSpaceCharPos != '(')
        stm << '\t';
      stm << defObj.Definition();
    }
  }
  stm << '\n';
}

void CppWriter::emitUndef(const CppAst::CppPreprocessorUndef& undefObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "undef " << undefObj.name() << '\n';
}

void CppWriter::emitInclude(const CppAst::CppPreprocessorInclude& includeObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "include " << includeObj.name() << '\n';
}
void CppWriter::emitHashIf(const CppAst::CppPreprocessorConditional& hashIfObj, std::ostream& stm) const
{
  emitHashIf(hashIfObj.ConditionalType(), hashIfObj.condition(), stm);
}

void CppWriter::emitEndIf(std::ostream& stm) const
{
  stm << '#' << --preproIndent_ << "endif\n";
}

void CppWriter::emitHashIf(CppAst::PreprocessorConditionalType condType,
                           const std::string&                  cond,
                           std::ostream&                       stm) const
{
  switch (condType)
  {
    case CppAst::PreprocessorConditionalType::IF:
      stm << '#' << preproIndent_ << "if " << cond << '\n';
      ++preproIndent_;
      break;

    case CppAst::PreprocessorConditionalType::IFDEF:
      stm << '#' << preproIndent_ << "ifdef " << cond << '\n';
      ++preproIndent_;
      break;

    case CppAst::PreprocessorConditionalType::IFNDEF:
      stm << '#' << preproIndent_ << "ifndef " << cond << '\n';
      ++preproIndent_;
      break;

    case CppAst::PreprocessorConditionalType::ELIF:
      stm << '#' << --preproIndent_ << "elif " << cond << '\n';
      ++preproIndent_;
      break;

    case CppAst::PreprocessorConditionalType::ELSE:
      stm << '#' << --preproIndent_ << "else " << cond << '\n';
      ++preproIndent_;
      break;

    case CppAst::PreprocessorConditionalType::ENDIF:
      emitEndIf(stm);
      break;
  }
}

void CppWriter::emitPragma(const CppAst::CppPreprocessorPragma& pragmaObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "pragma " << pragmaObj.Definition() << '\n';
}

void CppWriter::emitBlob(const CppAst::CppBlob& blobObj,
                         std::ostream&          stm,
                         bool                   formatLineStarts,
                         CppIndent              indentation) const
{
  // if (formatLineStarts)
  // {
  //   bool startOfLine = false;
  //   for (const auto ch : blobObj.blob_)
  //   {
  //     if (startOfLine)
  //     {
  //       if ((ch == ' ') || (ch == '\t'))
  //         continue;
  //       else if (ch != '\n')
  //         stm << indentation;
  //     }

  //     stm << ch;
  //     startOfLine = (ch == '\n');
  //   }
  // }
  // else
  {
    stm << blobObj.Blob();
  }
}

void CppWriter::emitVarType(const CppAst::CppVarType& varTypeObj, std::ostream& stm) const
{
  const auto attr = varTypeObj.typeAttr() | (isConst(varTypeObj) ? CppAst::CppIdentifierAttrib::kConst : 0);
  emitAttribute(attr, stm);
  if (varTypeObj.compound())
    emit(*varTypeObj.compound(), stm, CppIndent(), true);
  else
    stm << varTypeObj.baseType();
  const auto&                   origTypeModifier = varTypeObj.typeModifier();
  const CppAst::CppTypeModifier typeModifier {
    origTypeModifier.refType_, origTypeModifier.ptrLevel_, origTypeModifier.constBits_ & ~1};
  emitTypeModifier(typeModifier, stm);
  if (varTypeObj.ParameterPack())
    stm << "...";
}

void CppWriter::emitVar(const CppAst::CppVar& varObj, std::ostream& stm, CppIndent indentation) const
{
  if (varObj.isTemplated())
    emitTemplSpec(varObj.templateSpecification().value(), stm, indentation);
  emitVar(varObj, stm, indentation, false);
}

void CppWriter::emitVarDecl(std::ostream& stm, const CppAst::CppVarDecl& varDecl, bool skipName) const
{
  if (!skipName && !varDecl.name().empty())
    stm << varDecl.name();
  for (const auto& arrSize : varDecl.arraySizes())
  {
    stm << '[';
    if (arrSize)
      emitExpr(*arrSize, stm);
    stm << ']';
  }
  if (varDecl.assignType() == CppAst::AssignType::USING_EQUAL)
  {
    stm << " = ";
    emit(*varDecl.assignValue(), stm, CppIndent(), true);
  }
  else if (varDecl.assignType() == CppAst::AssignType::USING_PARENTHESES)
  {
    stm << '(';
    if (varDecl.assignValue())
      emit(*varDecl.assignValue(), stm, CppIndent(), true);
    stm << ')';
  }
  else if (varDecl.assignType() == CppAst::AssignType::USING_BRACES)
  {
    stm << '{';
    if (varDecl.assignValue())
      emit(*varDecl.assignValue(), stm, CppIndent(), true);
    stm << '}';
  }
}

void CppWriter::emitVar(const CppAst::CppVar& varObj, std::ostream& stm, CppIndent indentation, bool skipName) const
{
  stm << indentation;
  if (!varObj.apidecor().empty())
  {
    stm << varObj.apidecor() << ' ';
  }
  emitVarType(varObj.varType(), stm);
  if (!skipName && !varObj.name().empty())
    stm << ' ';
  emitVarDecl(stm, varObj.varDecl(), skipName);
}

void CppWriter::emitVarList(const CppAst::CppVarList& varListObj, std::ostream& stm, CppIndent indentation) const
{
  emitVar(*varListObj.firstVar(), stm, indentation);
  auto& varDeclList = varListObj.varDeclList();
  for (size_t i = 0; i < varDeclList.size(); ++i)
  {
    stm << ", ";
    const auto& decl = varDeclList[i];
    emitTypeModifier(decl, stm);
    emitVarDecl(stm, decl, false);
  }

  stm << ";\n";
}

void CppWriter::emitEnum(const CppAst::CppEnum& enmObj,
                         std::ostream&          stm,
                         bool                   emitNewLine,
                         CppIndent              indentation) const
{
  stm << indentation << "enum";
  if (enmObj.isClass())
    stm << " class";
  if (!enmObj.name().empty())
    stm << ' ' << enmObj.name();
  if (!enmObj.underlyingType().empty())
    stm << " : " << enmObj.underlyingType();
  if (!enmObj.itemList().empty())
  {
    const auto* blob = cpp_entity_cast<const CppAst::CppBlob*>(enmObj.itemList().front().val());
    if (blob)
    {
      stm << " {\n";
      emitBlob(*blob, stm, false, indentation);
      stm << '\n' << indentation << '}';
    }
    else
    {
      stm << '\n';
      stm << indentation++ << "{\n";
      for (const auto& enmItem : enmObj.itemList())
      {
        if (!enmItem.isConstEnumItem())
        {
          emit(*enmItem.val(), stm, indentation);
        }
        else
        {
          stm << indentation << enmItem.name();
          const auto* val = cpp_entity_cast<const CppAst::CppExpr*>(enmItem.val());
          if (val)
          {
            stm << " = ";
            emitExpr(*val, stm);
          }
          stm << ",\n";
        }
      }
      stm << --indentation << "}";
    }
  }
  if (emitNewLine)
    stm << ";\n";
}

void CppWriter::emitTypedef(const CppAst::CppTypedefName& typedefName, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << "typedef ";
  emitVar(*typedefName.var(), stm);
  stm << ";\n";
}

void CppWriter::emitUsingDecl(const CppAst::CppUsingDecl& usingDecl, std::ostream& stm, CppIndent indentation) const
{
  if (usingDecl.isTemplated())
    emitTemplSpec(usingDecl.templateSpecification().value(), stm, indentation);
  stm << indentation << "using " << usingDecl.name();
  if (usingDecl.definition())
  {
    stm << " = ";
    emit(*usingDecl.definition(), stm);
  }
  stm << ";\n";
}

void CppWriter::emitTypedefList(const CppAst::CppTypedefList& typedefList,
                                std::ostream&                 stm,
                                CppIndent                     indentation) const
{
  stm << indentation << "typedef ";
  emitVarList(typedefList.varList(), stm);
}

void CppWriter::emitFwdDecl(const CppAst::CppForwardClassDecl& fwdDeclObj,
                            std::ostream&                      stm,
                            CppIndent                          indentation) const
{
  if (fwdDeclObj.isTemplated())
    emitTemplSpec(fwdDeclObj.templateSpecification().value(), stm, indentation);
  stm << indentation;
  if (fwdDeclObj.attr() & CppAst::CppIdentifierAttrib::kFriend)
    stm << "friend ";
  if (fwdDeclObj.compoundType() != CppAst::CppCompoundType::UNKNOWN)
    stm << fwdDeclObj.compoundType() << ' ';
  if (!fwdDeclObj.apidecor().empty())
    stm << fwdDeclObj.apidecor() << ' ';
  stm << fwdDeclObj.name() << ";\n";
}

void CppWriter::emitMacroCall(const CppAst::CppMacroCall& macroCallObj, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << macroCallObj.macroCall_ << '\n';
}

void CppWriter::emitTemplSpec(const CppAst::CppTemplateParams& templSpec,
                              std::ostream&                    stm,
                              CppIndent                        indentation) const
{
  stm << indentation << "template <";
  const char* sep = "";
  for (const auto& param : templSpec)
  {
    stm << sep;
    if (param.paramType())
    {
      if (const auto* varType = cpp_entity_cast<const CppAst::CppVarType*>(param.paramType()))
        emitVarType(*varType, stm);
      else if (const auto* funcPtr = cpp_entity_cast<const CppAst::CppFunctionPointer*>(param.paramType()))
        emitFunctionPtr(*funcPtr, stm, false);
      stm << ' ';
    }
    else
    {
      stm << "typename ";
    }
    stm << param.paramName();
    if (param.defaultArg())
    {
      stm << " = ";
      emit(*param.defaultArg(), stm, CppIndent(), true);
    }
    sep = ", ";
  }
  stm << ">\n";
}

void CppWriter::emitCompound(const CppAst::CppCompound& compoundObj,
                             std::ostream&              stm,
                             CppIndent                  indentation,
                             bool                       emitNewLine) const
{
  if (isNamespaceLike(compoundObj))
  {
    if (compoundObj.isTemplated())
    {
      emitTemplSpec(compoundObj.templateSpecification().value(), stm, indentation);
    }
    stm << indentation << compoundObj.compoundType() << ' ';
    if (!compoundObj.apidecor().empty())
      stm << compoundObj.apidecor() << ' ';
    stm << compoundObj.name();
    if (compoundObj.hasAttr(CppAst::CppIdentifierAttrib::kFinal))
      stm << " final";
  }
  if (!compoundObj.inheritanceList().empty())
  {
    ++indentation;
    char sep = ':';
    stm << ' ';
    for (const auto& inheritanceInfo : compoundObj.inheritanceList())
    {
      stm << sep << ' ' << inheritanceInfo.inhType << ' ' << inheritanceInfo.baseName;
      sep = ',';
    }
    --indentation;
  }
  if (isNamespaceLike(compoundObj))
    stm << '\n' << indentation++ << "{\n";
  else if (compoundObj.compoundType() == CppAst::CppCompoundType::EXTERN_C_BLOCK)
    stm << indentation++ << "extern \"C\" {\n";

  compoundObj.visitAll([&](const CppAst::CppEntity& memObj) {
    emit(memObj, stm, indentation);
    if (memObj.entityType() == CppAst::CppBlob::EntityType())
      stm << '\n';

    return true;
  });

  if (isNamespaceLike(compoundObj))
  {
    stm << --indentation;
    stm << '}';
    if (emitNewLine)
    {
      if (isClassLike(compoundObj))
        stm << ';';
      stm << '\n';
    }
  }
  else if (compoundObj.compoundType() == CppAst::CppCompoundType::EXTERN_C_BLOCK)
    stm << indentation << "}\n";
}

void CppWriter::emitParamList(const std::vector<std::unique_ptr<CppAst::CppEntity>>& paramListObj,
                              std::ostream&                                          stm) const
{
  emitParamList(paramListObj, stm, false);
}

void CppWriter::emitParamList(const std::vector<std::unique_ptr<CppAst::CppEntity>>& paramListObj,
                              std::ostream&                                          stm,
                              bool                                                   skipParamName) const
{
  const char* sep = "";
  for (const auto& param : paramListObj)
  {
    stm << sep;
    sep = ", ";
    switch (param->entityType())
    {
      case CppAst::CppEntityType::VAR:
        emitVar(*static_cast<const CppAst::CppVar*>(param.get()), stm, CppIndent(), skipParamName);
        break;
      case CppAst::CppEntityType::FUNCTION_PTR:
        emitFunctionPtr(*static_cast<const CppAst::CppFunctionPointer*>(param.get()), stm, skipParamName);
        break;
      default:
        assert(false);
    }
  }
}

void CppWriter::emitFunction(const CppAst::CppFunction& funcObj,
                             std::ostream&              stm,
                             CppIndent                  indentation,
                             bool                       skipName,
                             bool                       skipParamName,
                             bool                       emitNewLine) const
{
  if (funcObj.isTemplated())
    emitTemplSpec(funcObj.templateSpecification().value(), stm, indentation);

  if ((funcObj.attr() & (CppAst::CppIdentifierAttrib::kFuncParam | CppAst::CppIdentifierAttrib::kTypedef)) == 0)
    stm << indentation;
  if (!funcObj.decor1().empty())
    stm << funcObj.decor1() << ' ';
  if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kStatic))
    stm << "static ";
  else if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kExtern))
    stm << "extern ";
  else if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kVirtual)
           && !(funcObj.hasAttr(CppAst::CppIdentifierAttrib::kOverride)
                || funcObj.hasAttr(CppAst::CppIdentifierAttrib::kFinal)))
    stm << "virtual ";
  else if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kInline))
    stm << "inline ";
  else if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kExplicit))
    stm << "explicit ";
  else if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kFriend))
    stm << "friend ";
  if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kConstExpr))
    stm << "constexpr ";
  if (funcObj.hasAttr(CppAst::CppIdentifierAttrib::kTrailingRet))
    stm << "auto";
  else if (funcObj.returnType())
    emitVarType(*funcObj.returnType(), stm);
  if (funcObj.entityType() == CppAst::CppEntityType::FUNCTION_PTR)
    stm << " (";
  else
    stm << ' ';
  if (!funcObj.decor2().empty())
    stm << funcObj.decor2() << ' ';
  if (funcObj.entityType() == CppAst::CppEntityType::FUNCTION_PTR)
  {
    stm << '*';
    if (!skipName)
      stm << funcObj.name() << ") ";
  }
  else if (!skipName)
  {
    stm << funcObj.name();
  }
  stm << '(';
  if (!funcObj.params().empty())
    emitParamList(funcObj.params(), stm, skipParamName);
  stm << ')';

  if ((funcObj.attr() & CppAst::CppIdentifierAttrib::kConst) == CppAst::CppIdentifierAttrib::kConst)
    stm << " const";
  if ((funcObj.attr() & CppAst::CppIdentifierAttrib::kPureVirtual) == CppAst::CppIdentifierAttrib::kPureVirtual)
    stm << " = 0";
  else if ((funcObj.attr() & CppAst::CppIdentifierAttrib::kOverride) == CppAst::CppIdentifierAttrib::kOverride)
    stm << " override";
  else if ((funcObj.attr() & CppAst::CppIdentifierAttrib::kFinal) == CppAst::CppIdentifierAttrib::kFinal)
    stm << " final";

  if (funcObj.attr() & CppAst::CppIdentifierAttrib::kTrailingRet)
  {
    stm << " . ";
    emitVarType(*funcObj.returnType(), stm);
  }
  if (!skipParamName && funcObj.defn() && (getEmittingType() != kHeader))
  {
    // const auto defn = funcObj.defn();
    // if (defn->hasASingleBlobMember())
    // {
    //   stm << '\n' << indentation++ << "{\n";
    //   emitBlob((const CppAst::CppBlob&) defn->members().front(), stm, false, indentation);
    //   stm << '\n' << --indentation << "}\n";
    // }
    // else
    {
      stm << '\n' << indentation++ << "{\n";
      emitCompound(*funcObj.defn(), stm, indentation);
      stm << --indentation << "}\n";
    }
  }
  else if (emitNewLine && ((funcObj.attr() & CppAst::CppIdentifierAttrib::kFuncParam) == 0))
  {
    stm << ";\n";
  }
}

void CppWriter::emitFunction(const CppAst::CppFunction& funcObj,
                             std::ostream&              stm,
                             bool                       emitNewLine,
                             CppIndent                  indentation) const
{
  return emitFunction(funcObj, stm, indentation, false, false, emitNewLine);
}

void CppWriter::emitFunctionPtr(const CppAst::CppFunctionPointer& funcPtrObj,
                                std::ostream&                     stm,
                                bool                              emitNewLine,
                                CppIndent                         indentation) const
{
  if (funcPtrObj.attr() & CppAst::CppIdentifierAttrib::kTypedef)
    stm << indentation << "typedef ";
  emitFunction((const CppAst::CppFunction&) funcPtrObj, stm, emitNewLine, indentation);
}

void CppWriter::emitConstructor(const CppAst::CppConstructor& ctorObj,
                                std::ostream&                 stm,
                                CppIndent                     indentation,
                                bool                          skipParamName) const
{
  if (ctorObj.isTemplated())
  {
    emitTemplSpec(ctorObj.templateSpecification().value(), stm, indentation);
  }
  stm << indentation;
  if (!ctorObj.decor1().empty())
    stm << ctorObj.decor1() << ' ';
  if (ctorObj.attr() & CppAst::CppIdentifierAttrib::kInline)
    stm << "inline ";
  else if (ctorObj.attr() & CppAst::CppIdentifierAttrib::kExplicit)
    stm << "explicit ";
  stm << ctorObj.name();
  stm << '(';
  if (!ctorObj.params().empty())
    emitParamList(ctorObj.params(), stm, skipParamName);
  stm << ')';
  if (!skipParamName && ctorObj.memInits_.memInitList)
  {
    char sep = ':';
    ++indentation;
    if (ctorObj.memInits_.memInitListIsABlob_)
    {
      stm << '\n';
      stm << indentation << sep << ' ';
      emitBlob(ctorObj.memInits_.blob, stm, true, indentation.resetted());
    }
    else
    {
      for (const auto& memInit : *(ctorObj.memInits_.memInitList))
      {
        stm << '\n';
        stm << indentation << sep << ' ' << memInit.first << '(';
        emitExpr(memInit.second, stm);
        stm << ')';
        sep = ',';
      }
    }
    --indentation;
  }
  if (!skipParamName && ctorObj.defn())
  {
    stm << '\n' << indentation++ << "{\n";
    emitCompound(ctorObj.defn(), stm, indentation);
    stm << --indentation << "}\n";
  }
  else
  {
    if (isDeleted(ctorObj))
      stm << " = delete";
    stm << ";\n";
  }
}

void CppWriter::emitConstructor(const CppAst::CppConstructor& ctorObj, std::ostream& stm, CppIndent indentation) const
{
  emitConstructor(ctorObj, stm, indentation, false);
}

void CppWriter::emitDestructor(const CppAst::CppDestructor& dtorObj, std::ostream& stm, CppIndent indentation) const
{
  if (dtorObj.isTemplated())
    emitTemplSpec(dtorObj.templateSpecification().value(), stm, indentation);
  stm << indentation;
  if (!dtorObj.decor1().empty())
    stm << dtorObj.decor1() << ' ';
  if (dtorObj.attr() & CppAst::CppIdentifierAttrib::kInline)
    stm << "inline ";
  else if (dtorObj.attr() & CppAst::CppIdentifierAttrib::kExplicit)
    stm << "explicit ";
  else if (dtorObj.attr() & CppAst::CppIdentifierAttrib::kVirtual)
    stm << "virtual ";
  stm << dtorObj.name() << "()";

  if (dtorObj.defn())
  {
    stm << '\n' << indentation++ << "{\n";
    emitCompound(dtorObj.defn(), stm, indentation);
    stm << --indentation << "}\n";
  }
  else
  {
    stm << ";\n";
  }
}

void CppWriter::emitTypeConverter(const CppAst::CppTypeConverter& typeConverterObj,
                                  std::ostream&                   stm,
                                  CppIndent                       indentation) const
{
  if (typeConverterObj.isTemplated())
    emitTemplSpec(typeConverterObj.templateSpecification().value(), stm, indentation);
  stm << indentation << "operator ";
  emitVarType(typeConverterObj.to_, stm);
  stm << "()";
  if (typeConverterObj.attr() & CppAst::CppIdentifierAttrib::kConst)
    stm << " const";
  if (typeConverterObj.attr() & CppAst::CppIdentifierAttrib::kConstExpr)
    stm << " constexpr";
  if (typeConverterObj.defn())
  {
    stm << '\n';
    stm << indentation << "{\n";
    ++indentation;
    emitCompound(typeConverterObj.defn(), stm, indentation);
    --indentation;
    stm << indentation << "}\n";
  }
  else
  {
    stm << ";\n";
  }
}

void CppWriter::emitDocComment(const CppAst::CppDocumentationComment& docCommentObj,
                               std::ostream&                          stm,
                               CppIndent                              indentation) const
{
  stm << docCommentObj.str() << '\n';
}

inline void emitOperator(std::ostream& stm, CppOperator op)
{
  switch (op)
  {
    case CppAst::CppOperator::kUnaryMinus:
      stm << '-';
      break;
    case CppAst::CppOperator::kBitToggle:
      stm << '~';
      break;
    case CppAst::CppOperator::kLogNot:
      stm << '!';
      break;
    case CppAst::CppOperator::kDerefer:
      stm << '*';
      break;
    case CppAst::CppOperator::kRefer:
      stm << '&';
      break;
    case CppAst::CppOperator::kPreIncrement:
    case CppAst::CppOperator::kPostIncrement:
      stm << "++";
      break;
    case CppAst::CppOperator::kPreDecrement:
    case CppAst::CppOperator::kPostDecrement:
      stm << "--";
      break;
    case CppAst::CppOperator::kPlus:
      stm << '+';
      break;
    case CppAst::CppOperator::kMinus:
      stm << '-';
      break;
    case CppAst::CppOperator::kMul:
      stm << '*';
      break;
    case CppAst::CppOperator::kDiv:
      stm << '/';
      break;
    case CppAst::CppOperator::kPercent:
      stm << '%';
      break;
    case CppAst::CppOperator::kAnd:
      stm << "&&";
      break;
    case CppAst::CppOperator::kOr:
      stm << "||";
      break;
    case CppAst::CppOperator::kBitAnd:
      stm << '&';
      break;
    case CppAst::CppOperator::kBitOr:
      stm << '|';
      break;
    case CppAst::CppOperator::kXor:
      stm << '^';
      break;
    case CppAst::CppOperator::kEqual:
      stm << '=';
      break;
    case CppAst::CppOperator::kLess:
      stm << '<';
      break;
    case CppAst::CppOperator::kGreater:
      stm << '>';
      break;
    case CppAst::CppOperator::kPlusEqual:
      stm << "+=";
      break;
    case CppAst::CppOperator::kMinusEqual:
      stm << "-=";
      break;
    case CppAst::CppOperator::kMulEqual:
      stm << "*=";
      break;
    case CppAst::CppOperator::kDivEqual:
      stm << "/=";
      break;
    case CppAst::CppOperator::kPerEqual:
      stm << "%=";
      break;
    case CppAst::CppOperator::kXorEqual:
      stm << "^=";
      break;
    case CppAst::CppOperator::kAndEqual:
      stm << "&=";
      break;
    case CppAst::CppOperator::kOrEqual:
      stm << "|=";
      break;
    case CppAst::CppOperator::kLeftShift:
      stm << "<<";
      break;
    case CppAst::CppOperator::kRightShift:
      stm << ">>";
      break;
    case CppAst::CppOperator::kLShiftEqual:
      stm << "<<=";
      break;
    case CppAst::CppOperator::kRShiftEqual:
      stm << ">>=";
      break;
    case CppAst::CppOperator::kCmpEqual:
      stm << "==";
      break;
    case CppAst::CppOperator::kNotEqual:
      stm << "!=";
      break;
    case CppAst::CppOperator::kLessEqual:
      stm << "<=";
      break;
    case CppAst::CppOperator::kGreaterEqual:
      stm << ">=";
      break;
    case CppAst::CppOperator::k3WayCmp:
      stm << "<=>";
      break;
    case CppAst::CppOperator::kComma:
      stm << ',';
      break;
    case CppAst::CppOperator::kDot:
      stm << '.';
      break;
    case CppAst::CppOperator::kArrow:
      stm << ".";
      break;
    case CppAst::CppOperator::kArrowStar:
      stm << ".*";
      break;

    default:
      break;
  }
}

void CppWriter::emitExprAtom(const CppAst::CppExprAtom& exprAtm, std::ostream& stm, CppIndent indentation) const
{
  switch (exprAtm.type)
  {
    case CppAst::CppExprAtom::kAtom:
      stm << *(exprAtm.atom);
      break;
    case CppAst::CppExprAtom::kExpr:
      emitExpr(*exprAtm.expr, stm);
      break;
    case CppAst::CppExprAtom::VAR_TYPE:
      emitVarType(*exprAtm.varType, stm);

    default:
      break;
  }
}

void CppWriter::emitExpr(const CppAst::CppExpr& exprObj, std::ostream& stm, CppIndent indentation) const
{
  if (exprObj == NULL)
    return;
  stm << indentation;
  if (exprObj.flags_ & CppAst::CppExpr::kReturn)
    stm << "return ";
  if (exprObj.flags_ & CppAst::CppExpr::kThrow)
    stm << "throw ";
  if (exprObj.flags_ & CppAst::CppExpr::kInitializer)
    stm << "{";
  if (exprObj.flags_ & CppAst::CppExpr::kBracketed)
    stm << '(';
  if (exprObj.flags_ & CppAst::CppExpr::kNew)
    stm << "new ";
  if (exprObj.flags_ & CppAst::CppExpr::kSizeOf)
    stm << "sizeof(";
  else if (exprObj.flags_ & CppAst::CppExpr::kDelete)
    stm << "delete ";
  else if (exprObj.flags_ & CppAst::CppExpr::kDeleteArray)
    stm << "delete[] ";
  if (exprObj.oper_ == CppAst::CppOperator::kNone)
  {
    emitExprAtom(exprObj.expr1_, stm);
  }
  else if (exprObj.oper_ > CppAst::CppOperator::kUnariPrefixOperatorStart
           && exprObj.oper_ < CppAst::CppOperator::kUnariSufixOperatorStart)
  {
    emitOperator(stm, exprObj.oper_);
    emitExprAtom(exprObj.expr1_, stm);
  }
  else if (exprObj.oper_ > CppAst::CppOperator::kUnariSufixOperatorStart
           && exprObj.oper_ < CppAst::CppOperator::kBinaryOperatorStart)
  {
    emitExprAtom(exprObj.expr1_, stm);
    emitOperator(stm, exprObj.oper_);
  }
  else if (exprObj.oper_ > CppAst::CppOperator::kBinaryOperatorStart
           && exprObj.oper_ < CppAst::CppOperator::kDerefOperatorStart)
  {
    emitExprAtom(exprObj.expr1_, stm);
    if (exprObj.oper_ != CppAst::CppOperator::kComma)
      stm << ' ';
    emitOperator(stm, exprObj.oper_);
    stm << ' ';
    emitExprAtom(exprObj.expr2_, stm);
  }
  else if (exprObj.oper_ > CppAst::CppOperator::kDerefOperatorStart
           && exprObj.oper_ < CppAst::CppOperator::kSpecialOperations)
  {
    emitExprAtom(exprObj.expr1_, stm);
    emitOperator(stm, exprObj.oper_);
    emitExprAtom(exprObj.expr2_, stm);
  }
  else if (exprObj.oper_ == CppAst::CppOperator::kFunctionCall)
  {
    emitExprAtom(exprObj.expr1_, stm);
    stm << '(';
    emitExprAtom(exprObj.expr2_, stm);
    stm << ')';
  }
  else if (exprObj.oper_ == CppAst::CppOperator::kUniformInitCall)
  {
    emitExprAtom(exprObj.expr1_, stm);
    stm << '{';
    emitExprAtom(exprObj.expr2_, stm);
    stm << '}';
  }
  else if (exprObj.oper_ == CppAst::CppOperator::kArrayElem)
  {
    emitExprAtom(exprObj.expr1_, stm);
    stm << '[';
    emitExprAtom(exprObj.expr2_, stm);
    stm << ']';
  }
  else if (exprObj.oper_ == CppAst::CppOperator::kCStyleCast)
  {
    stm << '(';
    emitExprAtom(exprObj.expr1_, stm);
    stm << ") ";
    emitExprAtom(exprObj.expr2_, stm);
  }
  else if (exprObj.oper_ >= CppAst::CppOperator::kConstCast && exprObj.oper_ <= CppAst::CppOperator::kReinterpretCast)
  {
    if (exprObj.oper_ == CppAst::CppOperator::kConstCast)
      stm << "const_cast";
    else if (exprObj.oper_ == CppAst::CppOperator::kStaticCast)
      stm << "static_cast";
    else if (exprObj.oper_ == CppAst::CppOperator::kDynamicCast)
      stm << "dynamic_cast";
    else if (exprObj.oper_ == CppAst::CppOperator::kReinterpretCast)
      stm << "reinterpret_cast";
    stm << '<';
    emitExprAtom(exprObj.expr1_, stm);
    stm << ">(";
    emitExprAtom(exprObj.expr2_, stm);
    stm << ')';
  }
  else if (exprObj.oper_ == CppAst::CppOperator::kTertiaryOperator)
  {
    emitExprAtom(exprObj.expr1_, stm);
    stm << " ? ";
    emitExprAtom(exprObj.expr2_, stm);
    stm << " : ";
    emitExprAtom(exprObj.expr3_, stm);
  }
  else if (exprObj.oper_ == CppAst::CppOperator::kPlacementNew)
  {
    stm << "new (";
    emitExprAtom(exprObj.expr1_, stm);
    stm << ") ";
    emitExprAtom(exprObj.expr2_, stm);
  }

  if (exprObj.flags_ & CppAst::CppExpr::kBracketed)
    stm << ')';
  if (exprObj.flags_ & CppAst::CppExpr::kInitializer)
    stm << "}";
  if (exprObj.flags_ & CppAst::CppExpr::kSizeOf)
    stm << ')';

  if (exprObj.flags_ & CppAst::CppExpr::kVariadicPack)
    stm << "...";
}

void CppWriter::emitIfBlock(const CppAst::CppIfBlock& ifBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation;
  stm << "if (";
  emit(*ifBlock.condition(), stm, CppIndent(), true);
  stm << ")\n";
  stm << indentation << "{\n";
  ++indentation;
  if (ifBlock.body())
    emit(*ifBlock.body(), stm, indentation);
  --indentation;
  stm << indentation << "}\n";
  if (ifBlock.elsePart())
  {
    stm << indentation << "else \n";
    stm << indentation << "{\n";
    ++indentation;
    emit(*ifBlock.elsePart(), stm, indentation);
    --indentation;
    stm << indentation << "}\n";
  }
}

void CppWriter::emitWhileBlock(const CppAst::CppWhileBlock& whileBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation;
  stm << "while (";
  emit(*whileBlock.condition(), stm, CppIndent(), true);
  stm << ")\n";
  stm << indentation << "{\n";
  ++indentation;
  if (whileBlock.body())
    emit(*whileBlock.body(), stm, indentation);
  --indentation;
  stm << indentation << "}\n";
}

void CppWriter::emitDoBlock(const CppAst::CppDoWhileBlock& doBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << "do\n";
  stm << indentation << "{\n";
  ++indentation;
  if (doBlock.body())
    emit(*doBlock.body(), stm, indentation);
  --indentation;
  stm << indentation << "} while (";
  emit(*doBlock.condition(), stm, CppIndent(), true);
  stm << ");\n";
}

void CppWriter::emitForBlock(const CppAst::CppForBlock& forBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << "for (";
  if (forBlock.start())
    emit(*forBlock.start(), stm, CppIndent(), true);
  stm << ';';
  if (forBlock.stop())
  {
    stm << ' ';
    emitExpr(*forBlock.stop(), stm);
  }
  stm << ';';
  if (forBlock.step())
  {
    stm << ' ';
    emitExpr(*forBlock.step(), stm);
  }
  stm << ")\n";
  stm << indentation << "{\n";
  ++indentation;
  if (forBlock.body())
    emit(*forBlock.body(), stm, indentation);
  --indentation;
  stm << indentation << "}\n";
}

void CppWriter::emitSwitchBlock(const CppAst::CppSwitchBlock& switchBlock,
                                std::ostream&                 stm,
                                CppIndent                     indentation) const
{
  stm << indentation << "switch(";
  emitExpr(*switchBlock.condition(), stm);
  stm << ")\n";
  stm << indentation++ << "{\n";
  for (const auto& caseStmt : *(switchBlock.body()))
  {
    if (caseStmt.case_)
    {
      stm << indentation++ << "case ";
      emitExpr(caseStmt.case_, stm);
      stm << ":\n";
    }
    else
    {
      stm << "default:\n";
    }
    if (caseStmt.body())
      emitCompound(caseStmt.body(), stm, indentation);
    --indentation;
  }
  stm << --indentation << "}\n";
}
