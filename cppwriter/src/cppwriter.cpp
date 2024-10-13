// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#include "cppwriter/cppwriter.h"

#include "cppast/cppast.h"

namespace cppcodegen {

namespace {

static void emitAttribute(std::uint32_t attr, std::ostream& stm)
{
  if (attr & cppast::CppIdentifierAttrib::kStatic)
    stm << "static ";
  else if (attr & cppast::CppIdentifierAttrib::kExtern)
    stm << "extern ";
  else if (attr & cppast::CppIdentifierAttrib::kExternC)
    stm << "extern C ";

  if (attr & cppast::CppIdentifierAttrib::kConst)
    stm << "const ";
  if (attr & cppast::CppIdentifierAttrib::kConstExpr)
    stm << "constexpr ";
  if (attr & cppast::CppIdentifierAttrib::kVolatile)
    stm << "volatile ";
  if (attr & cppast::CppIdentifierAttrib::kMutable)
    stm << "mutable ";
}

static void emitTypeModifier(const cppast::CppTypeModifier& modifier, std::ostream& stm)
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
  if (modifier.refType_ == cppast::CppRefType::BY_REF)
    stm << '&';
  else if (modifier.refType_ == cppast::CppRefType::RVAL_REF)
    stm << "&&";
}

} // namespace

void CppWriter::emit(const cppast::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation) const
{
  return emit(cppEntity, stm, indentation, false);
}

void CppWriter::emit(const cppast::CppEntity& cppEntity, std::ostream& stm, CppIndent indentation, bool noNewLine) const
{
  switch (cppEntity.entityType())
  {
    case cppast::CppEntityType::PREPROCESSOR_DEFINE:
      return emitDefine((const cppast::CppMacroDefinition&) cppEntity, stm);
    case cppast::CppEntityType::PREPROCESSOR_UNDEF:
      return emitUndef((const cppast::CppPreprocessorUndef&) cppEntity, stm);
    case cppast::CppEntityType::PREPROCESSOR_INCLUDE:
      return emitInclude((const cppast::CppPreprocessorInclude&) cppEntity, stm);
    case cppast::CppEntityType::PREPROCESSOR_CONDITIONAL:
      return emitHashIf((const cppast::CppPreprocessorConditional&) cppEntity, stm);
    case cppast::CppEntityType::PREPROCESSOR_PRAGMA:
      return emitPragma((const cppast::CppPreprocessorPragma&) cppEntity, stm);

    case cppast::CppEntityType::VAR_TYPE:
      return emitVarType((const cppast::CppVarType&) cppEntity, stm);
    case cppast::CppEntityType::VAR:
    {
      emitVar((const cppast::CppVar&) cppEntity, stm, indentation);
      if (!noNewLine)
        stm << ";\n";
      return;
    }
    case cppast::CppEntityType::VAR_LIST:
      return emitVarList((const cppast::CppVarList&) cppEntity, stm, indentation);
    case cppast::CppEntityType::ENUM:
      return emitEnum((const cppast::CppEnum&) cppEntity, stm, !noNewLine, indentation);
    case cppast::CppEntityType::DOCUMENTATION_COMMENT:
      return emitDocComment((const cppast::CppDocumentationComment&) cppEntity, stm, indentation);
    case cppast::CppEntityType::USING_DECL:
      return emitUsingDecl((const cppast::CppUsingDecl&) cppEntity, stm, indentation);
    case cppast::CppEntityType::TYPEDEF_DECL:
      return emitTypedef((const cppast::CppTypedefName&) cppEntity, stm, indentation);
    case cppast::CppEntityType::TYPEDEF_DECL_LIST:
      return emitTypedefList((const cppast::CppTypedefList&) cppEntity, stm, indentation);
    case cppast::CppEntityType::ENTITY_ACCESS_SPECIFIER:
      return emitEntityAccessSpecifier(
        (const cppast::CppEntityAccessSpecifier&) cppEntity, stm, indentation, !noNewLine);
    case cppast::CppEntityType::COMPOUND:
      return emitCompound((const cppast::CppCompound&) cppEntity, stm, indentation, !noNewLine);
    case cppast::CppEntityType::FORWARD_CLASS_DECL:
      return emitFwdDecl((const cppast::CppForwardClassDecl&) cppEntity, stm, indentation);
    case cppast::CppEntityType::FUNCTION:
      return emitFunction((const cppast::CppFunction&) cppEntity, stm, !noNewLine, indentation);
    case cppast::CppEntityType::CONSTRUCTOR:
      return emitConstructor((const cppast::CppConstructor&) cppEntity, stm, indentation);
    case cppast::CppEntityType::DESTRUCTOR:
      return emitDestructor((const cppast::CppDestructor&) cppEntity, stm, indentation);
    case cppast::CppEntityType::TYPE_CONVERTER:
      return emitTypeConverter((const cppast::CppTypeConverter&) cppEntity, stm, indentation);
    case cppast::CppEntityType::FUNCTION_PTR:
      return emitFunctionPtr((const cppast::CppFunctionPointer&) cppEntity, stm, !noNewLine, indentation);
    case cppast::CppEntityType::IF_BLOCK:
      return emitIfBlock((const cppast::CppIfBlock&) cppEntity, stm, indentation);
    case cppast::CppEntityType::WHILE_BLOCK:
      return emitWhileBlock((const cppast::CppWhileBlock&) cppEntity, stm, indentation);
    case cppast::CppEntityType::DO_WHILE_BLOCK:
      return emitDoBlock((const cppast::CppDoWhileBlock&) cppEntity, stm, indentation);
    case cppast::CppEntityType::FOR_BLOCK:
      return emitForBlock((const cppast::CppForBlock&) cppEntity, stm, indentation);
    case cppast::CppEntityType::EXPRESSION:
      emitExpr((const cppast::CppExpression&) cppEntity, stm, indentation);
      if (!noNewLine)
        stm << ";\n";
      break;
    case cppast::CppEntityType::SWITCH_BLOCK:
      return emitSwitchBlock(static_cast<const cppast::CppSwitchBlock&>(cppEntity), stm, indentation);
    case cppast::CppEntityType::MACRO_CALL:
      return emitMacroCall(static_cast<const cppast::CppMacroCall&>(cppEntity), stm, indentation);

    case cppast::CppEntityType::BLOB:
      return emitBlob((const cppast::CppBlob&) cppEntity, stm, true, indentation);

    default:
      break;
  }
}

void CppWriter::emitDefine(const cppast::CppMacroDefinition& defObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "define " << defObj.name();
  if (!defObj.definition().empty())
  {
    const auto firstNonSpaceCharPos =
      std::find_if(defObj.definition().begin(), defObj.definition().end(), [](char c) { return !std::isspace(c); });
    if (firstNonSpaceCharPos != defObj.definition().end())
    {
      if (*firstNonSpaceCharPos != '(')
        stm << '\t';
      stm << defObj.definition();
    }
  }
  stm << '\n';
}

void CppWriter::emitUndef(const cppast::CppPreprocessorUndef& undefObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "undef " << undefObj.name() << '\n';
}

void CppWriter::emitInclude(const cppast::CppPreprocessorInclude& includeObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "include " << includeObj.name() << '\n';
}
void CppWriter::emitHashIf(const cppast::CppPreprocessorConditional& hashIfObj, std::ostream& stm) const
{
  emitHashIf(hashIfObj.conditionalType(), hashIfObj.condition(), stm);
}

void CppWriter::emitEndIf(std::ostream& stm) const
{
  stm << '#' << --preproIndent_ << "endif\n";
}

void CppWriter::emitHashIf(cppast::PreprocessorConditionalType condType,
                           const std::string&                  cond,
                           std::ostream&                       stm) const
{
  switch (condType)
  {
    case cppast::PreprocessorConditionalType::IF:
      stm << '#' << preproIndent_ << "if " << cond << '\n';
      ++preproIndent_;
      break;

    case cppast::PreprocessorConditionalType::IFDEF:
      stm << '#' << preproIndent_ << "ifdef " << cond << '\n';
      ++preproIndent_;
      break;

    case cppast::PreprocessorConditionalType::IFNDEF:
      stm << '#' << preproIndent_ << "ifndef " << cond << '\n';
      ++preproIndent_;
      break;

    case cppast::PreprocessorConditionalType::ELIF:
      stm << '#' << --preproIndent_ << "elif " << cond << '\n';
      ++preproIndent_;
      break;

    case cppast::PreprocessorConditionalType::ELSE:
      stm << '#' << --preproIndent_ << "else " << cond << '\n';
      ++preproIndent_;
      break;

    case cppast::PreprocessorConditionalType::ENDIF:
      emitEndIf(stm);
      break;
  }
}

void CppWriter::emitPragma(const cppast::CppPreprocessorPragma& pragmaObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "pragma " << pragmaObj.definition() << '\n';
}

void CppWriter::emitBlob(const cppast::CppBlob& blobObj,
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

void CppWriter::emitVarType(const cppast::CppVarType& varTypeObj, std::ostream& stm) const
{
  const auto attr = varTypeObj.typeAttr() | (isConst(varTypeObj) ? cppast::CppIdentifierAttrib::kConst : 0);
  emitAttribute(attr, stm);
  if (varTypeObj.compound())
    emit(*varTypeObj.compound(), stm, CppIndent(), true);
  else
    stm << varTypeObj.baseType();
  const auto&                   origTypeModifier = varTypeObj.typeModifier();
  const cppast::CppTypeModifier typeModifier {
    origTypeModifier.refType_, origTypeModifier.ptrLevel_, origTypeModifier.constBits_ & ~1};
  emitTypeModifier(typeModifier, stm);
  if (varTypeObj.parameterPack())
    stm << "...";
}

void CppWriter::emitVar(const cppast::CppVar& varObj, std::ostream& stm, CppIndent indentation) const
{
  if (varObj.isTemplated())
    emitTemplSpec(varObj.templateSpecification().value(), stm, indentation);
  emitVar(varObj, stm, indentation, false);
}

void CppWriter::emitExpressions(const std::vector<std::unique_ptr<const cppast::CppExpression>>& exprs,
                                std::ostream&                                                    stm) const
{
  const char* sep = "";
  for (size_t i = 0; i < exprs.size(); ++i)
  {
    stm << sep;
    emitExpr(*exprs[i], stm);
    sep = ", ";
  }
}

void CppWriter::emitVarDecl(std::ostream& stm, const cppast::CppVarDecl& varDecl, bool skipName) const
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

  if (!varDecl.isInitialized())
    return;

  if (varDecl.initializeType() == cppast::CppVarInitializeType::USING_EQUAL)
  {
    stm << " = ";
    emit(*varDecl.assignValue(), stm, CppIndent(), true);
  }
  else if (varDecl.initializeType() == cppast::CppVarInitializeType::DIRECT_CONSTRUCTOR_CALL)
  {
    stm << (varDecl.directConstructorCallStyle() == cppast::CppConstructorCallStyle::USING_BRACES) ? '{' : '(';
    emitExpressions(varDecl.constructorCallArgs(), stm);
    stm << (varDecl.directConstructorCallStyle() == cppast::CppConstructorCallStyle::USING_BRACES) ? '}' : ')';
  }
}

void CppWriter::emitVar(const cppast::CppVar& varObj, std::ostream& stm, CppIndent indentation, bool skipName) const
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

void CppWriter::emitVarList(const cppast::CppVarList& varListObj, std::ostream& stm, CppIndent indentation) const
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

void CppWriter::emitEnum(const cppast::CppEnum& enmObj,
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
    const auto blob = cppast::CppConstBlobEPtr(enmObj.itemList().front().nonConstEntity());
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
        if (enmItem.isNonConstEntity())
        {
          emit(*enmItem.nonConstEntity(), stm, indentation);
        }
        else
        {
          stm << indentation << enmItem.name();
          const auto val = enmItem.val();
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

void CppWriter::emitTypedef(const cppast::CppTypedefName& typedefName, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << "typedef ";
  emitVar(*typedefName.var(), stm);
  stm << ";\n";
}

void CppWriter::emitUsingDecl(const cppast::CppUsingDecl& usingDecl, std::ostream& stm, CppIndent indentation) const
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

void CppWriter::emitTypedefList(const cppast::CppTypedefList& typedefList,
                                std::ostream&                 stm,
                                CppIndent                     indentation) const
{
  stm << indentation << "typedef ";
  emitVarList(typedefList.varList(), stm);
}

void CppWriter::emitFwdDecl(const cppast::CppForwardClassDecl& fwdDeclObj,
                            std::ostream&                      stm,
                            CppIndent                          indentation) const
{
  if (fwdDeclObj.isTemplated())
    emitTemplSpec(fwdDeclObj.templateSpecification().value(), stm, indentation);
  stm << indentation;
  if (fwdDeclObj.attr() & cppast::CppIdentifierAttrib::kFriend)
    stm << "friend ";
  if (fwdDeclObj.compoundType() != cppast::CppCompoundType::UNKNOWN)
    stm << fwdDeclObj.compoundType() << ' ';
  if (!fwdDeclObj.apidecor().empty())
    stm << fwdDeclObj.apidecor() << ' ';
  stm << fwdDeclObj.name() << ";\n";
}

void CppWriter::emitMacroCall(const cppast::CppMacroCall& macroCallObj, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << macroCallObj.macroCall() << '\n';
}

void CppWriter::emitTemplSpec(const cppast::CppTemplateParams& templSpec,
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
      if (const auto varType = cppast::CppConstVarTypeEPtr(param.paramType()))
        emitVarType(*varType, stm);
      else if (const auto funcPtr = cppast::CppConstFunctionPointerEPtr(param.paramType()))
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

void CppWriter::emitEntityAccessSpecifier(const cppast::CppEntityAccessSpecifier& entityAccessSpecifier,
                                          std::ostream&                           stm,
                                          CppIndent                               indentation,
                                          bool                                    emitNewLine) const
{
  stm << --indentation << entityAccessSpecifier.type() << ":\n";
}

void CppWriter::emitCompound(const cppast::CppCompound& compoundObj,
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
    if (compoundObj.hasAttr(cppast::CppIdentifierAttrib::kFinal))
      stm << " final";
  }
  if (!compoundObj.inheritanceList().empty())
  {
    ++indentation;
    char sep = ':';
    stm << ' ';
    for (const auto& inheritanceInfo : compoundObj.inheritanceList())
    {
      stm << sep;
      if (inheritanceInfo.inhType.has_value())
      {
        stm << ' ' << inheritanceInfo.inhType.value();
      }
      stm << ' ' << inheritanceInfo.baseName;
      sep = ',';
    }
    --indentation;
  }
  if (isNamespaceLike(compoundObj))
    stm << '\n' << indentation++ << "{\n";
  else if (compoundObj.compoundType() == cppast::CppCompoundType::EXTERN_C_BLOCK)
    stm << indentation++ << "extern \"C\" {\n";

  compoundObj.visitAll([&](const cppast::CppEntity& memObj) {
    emit(memObj, stm, indentation);
    if (memObj.entityType() == cppast::CppBlob::EntityType())
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
  else if (compoundObj.compoundType() == cppast::CppCompoundType::EXTERN_C_BLOCK)
    stm << indentation << "}\n";
}

void CppWriter::emitParamList(const std::vector<const cppast::CppEntity*>& paramListObj, std::ostream& stm) const
{
  emitParamList(paramListObj, stm, false);
}

void CppWriter::emitParamList(const std::vector<const cppast::CppEntity*>& paramListObj,
                              std::ostream&                                stm,
                              bool                                         skipParamName) const
{
  const char* sep = "";
  for (const auto& param : paramListObj)
  {
    stm << sep;
    sep = ", ";
    switch (param->entityType())
    {
      case cppast::CppEntityType::VAR:
        emitVar(*static_cast<const cppast::CppVar*>(param), stm, CppIndent(), skipParamName);
        break;
      case cppast::CppEntityType::FUNCTION_PTR:
        emitFunctionPtr(*static_cast<const cppast::CppFunctionPointer*>(param), stm, skipParamName);
        break;
      default:
        assert(false);
    }
  }
}

void CppWriter::emitFunction(const cppast::CppFunction& funcObj,
                             std::ostream&              stm,
                             CppIndent                  indentation,
                             bool                       skipName,
                             bool                       skipParamName,
                             bool                       emitNewLine) const
{
  if (funcObj.isTemplated())
    emitTemplSpec(funcObj.templateSpecification().value(), stm, indentation);

  if ((funcObj.attr() & (cppast::CppIdentifierAttrib::kFuncParam | cppast::CppIdentifierAttrib::kTypedef)) == 0)
    stm << indentation;
  if (!funcObj.decor1().empty())
    stm << funcObj.decor1() << ' ';
  if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kStatic))
    stm << "static ";
  else if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kExtern))
    stm << "extern ";
  else if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kVirtual)
           && !(funcObj.hasAttr(cppast::CppIdentifierAttrib::kOverride)
                || funcObj.hasAttr(cppast::CppIdentifierAttrib::kFinal)))
    stm << "virtual ";
  else if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kInline))
    stm << "inline ";
  else if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kExplicit))
    stm << "explicit ";
  else if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kFriend))
    stm << "friend ";
  if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kConstExpr))
    stm << "constexpr ";
  if (funcObj.hasAttr(cppast::CppIdentifierAttrib::kTrailingRet))
    stm << "auto";
  else if (funcObj.returnType())
    emitVarType(*funcObj.returnType(), stm);
  if (funcObj.entityType() == cppast::CppEntityType::FUNCTION_PTR)
    stm << " (";
  else
    stm << ' ';
  if (!funcObj.decor2().empty())
    stm << funcObj.decor2() << ' ';
  if (funcObj.entityType() == cppast::CppEntityType::FUNCTION_PTR)
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
  const auto params = GetAllParams(funcObj);
  if (!params.empty())
    emitParamList(params, stm, skipParamName);
  stm << ')';

  if ((funcObj.attr() & cppast::CppIdentifierAttrib::kConst) == cppast::CppIdentifierAttrib::kConst)
    stm << " const";
  if ((funcObj.attr() & cppast::CppIdentifierAttrib::kPureVirtual) == cppast::CppIdentifierAttrib::kPureVirtual)
    stm << " = 0";
  else if ((funcObj.attr() & cppast::CppIdentifierAttrib::kOverride) == cppast::CppIdentifierAttrib::kOverride)
    stm << " override";
  else if ((funcObj.attr() & cppast::CppIdentifierAttrib::kFinal) == cppast::CppIdentifierAttrib::kFinal)
    stm << " final";

  if (funcObj.attr() & cppast::CppIdentifierAttrib::kTrailingRet)
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
    //   emitBlob((const cppast::CppBlob&) defn->members().front(), stm, false, indentation);
    //   stm << '\n' << --indentation << "}\n";
    // }
    // else
    {
      stm << '\n' << indentation++ << "{\n";
      emitCompound(*funcObj.defn(), stm, indentation);
      stm << --indentation << "}\n";
    }
  }
  else if (emitNewLine && ((funcObj.attr() & cppast::CppIdentifierAttrib::kFuncParam) == 0))
  {
    stm << ";\n";
  }
}

void CppWriter::emitFunction(const cppast::CppFunction& funcObj,
                             std::ostream&              stm,
                             bool                       emitNewLine,
                             CppIndent                  indentation) const
{
  return emitFunction(funcObj, stm, indentation, false, false, emitNewLine);
}

void CppWriter::emitFunctionPtr(const cppast::CppFunctionPointer& funcPtrObj,
                                std::ostream&                     stm,
                                bool                              emitNewLine,
                                CppIndent                         indentation) const
{
  if (funcPtrObj.attr() & cppast::CppIdentifierAttrib::kTypedef)
    stm << indentation << "typedef ";
  emitFunction((const cppast::CppFunction&) funcPtrObj, stm, emitNewLine, indentation);
}

void CppWriter::emitConstructor(const cppast::CppConstructor& ctorObj,
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
  if (ctorObj.attr() & cppast::CppIdentifierAttrib::kInline)
    stm << "inline ";
  else if (ctorObj.attr() & cppast::CppIdentifierAttrib::kExplicit)
    stm << "explicit ";
  stm << ctorObj.name();
  stm << '(';
  const auto params = GetAllParams(ctorObj);
  if (!params.empty())
    emitParamList(params, stm, skipParamName);
  stm << ')';
  if (!skipParamName && ctorObj.hasMemberInitList())
  {
    char sep = ':';
    ++indentation;
    for (const auto& memInit : ctorObj.memberInits())
    {
      stm << '\n';
      stm << indentation << sep << ' ' << memInit.memberName;
      const auto& memberInitInfo = memInit.memberInitInfo;
      stm << ((memberInitInfo.style == cppast::CppConstructorCallStyle::USING_BRACES) ? '{' : '(');
      emitExpressions(memberInitInfo.args, stm);
      stm << ((memberInitInfo.style == cppast::CppConstructorCallStyle::USING_BRACES) ? '}' : ')');
      sep = ',';
    }
    --indentation;
  }
  if (!skipParamName && ctorObj.defn())
  {
    stm << '\n' << indentation++ << "{\n";
    emitCompound(*ctorObj.defn(), stm, indentation);
    stm << --indentation << "}\n";
  }
  else
  {
    if (isDeleted(ctorObj))
      stm << " = delete";
    stm << ";\n";
  }
}

void CppWriter::emitConstructor(const cppast::CppConstructor& ctorObj, std::ostream& stm, CppIndent indentation) const
{
  emitConstructor(ctorObj, stm, indentation, false);
}

void CppWriter::emitDestructor(const cppast::CppDestructor& dtorObj, std::ostream& stm, CppIndent indentation) const
{
  if (dtorObj.isTemplated())
    emitTemplSpec(dtorObj.templateSpecification().value(), stm, indentation);
  stm << indentation;
  if (!dtorObj.decor1().empty())
    stm << dtorObj.decor1() << ' ';
  if (dtorObj.attr() & cppast::CppIdentifierAttrib::kInline)
    stm << "inline ";
  else if (dtorObj.attr() & cppast::CppIdentifierAttrib::kExplicit)
    stm << "explicit ";
  else if (dtorObj.attr() & cppast::CppIdentifierAttrib::kVirtual)
    stm << "virtual ";
  stm << dtorObj.name() << "()";

  if (dtorObj.defn())
  {
    stm << '\n' << indentation++ << "{\n";
    emitCompound(*dtorObj.defn(), stm, indentation);
    stm << --indentation << "}\n";
  }
  else
  {
    stm << ";\n";
  }
}

void CppWriter::emitTypeConverter(const cppast::CppTypeConverter& typeConverterObj,
                                  std::ostream&                   stm,
                                  CppIndent                       indentation) const
{
  if (typeConverterObj.isTemplated())
    emitTemplSpec(typeConverterObj.templateSpecification().value(), stm, indentation);
  stm << indentation << "operator ";
  emitVarType(*typeConverterObj.targetType(), stm);
  stm << "()";
  if (typeConverterObj.attr() & cppast::CppIdentifierAttrib::kConst)
    stm << " const";
  if (typeConverterObj.attr() & cppast::CppIdentifierAttrib::kConstExpr)
    stm << " constexpr";
  if (typeConverterObj.defn())
  {
    stm << '\n';
    stm << indentation << "{\n";
    ++indentation;
    emitCompound(*typeConverterObj.defn(), stm, indentation);
    --indentation;
    stm << indentation << "}\n";
  }
  else
  {
    stm << ";\n";
  }
}

void CppWriter::emitDocComment(const cppast::CppDocumentationComment& docCommentObj,
                               std::ostream&                          stm,
                               CppIndent                              indentation) const
{
  stm << docCommentObj.str() << '\n';
}

inline void emitOperator(std::ostream& stm, cppast::CppOperator op)
{
  switch (op)
  {
    case cppast::CppOperator::kUnaryMinus:
      stm << '-';
      break;
    case cppast::CppOperator::kBitToggle:
      stm << '~';
      break;
    case cppast::CppOperator::kLogNot:
      stm << '!';
      break;
    case cppast::CppOperator::kDerefer:
      stm << '*';
      break;
    case cppast::CppOperator::kRefer:
      stm << '&';
      break;
    case cppast::CppOperator::kPreIncrement:
    case cppast::CppOperator::kPostIncrement:
      stm << "++";
      break;
    case cppast::CppOperator::kPreDecrement:
    case cppast::CppOperator::kPostDecrement:
      stm << "--";
      break;
    case cppast::CppOperator::kPlus:
      stm << '+';
      break;
    case cppast::CppOperator::kMinus:
      stm << '-';
      break;
    case cppast::CppOperator::kMul:
      stm << '*';
      break;
    case cppast::CppOperator::kDiv:
      stm << '/';
      break;
    case cppast::CppOperator::kPercent:
      stm << '%';
      break;
    case cppast::CppOperator::kAnd:
      stm << "&&";
      break;
    case cppast::CppOperator::kOr:
      stm << "||";
      break;
    case cppast::CppOperator::kBitAnd:
      stm << '&';
      break;
    case cppast::CppOperator::kBitOr:
      stm << '|';
      break;
    case cppast::CppOperator::kXor:
      stm << '^';
      break;
    case cppast::CppOperator::kEqual:
      stm << '=';
      break;
    case cppast::CppOperator::kLess:
      stm << '<';
      break;
    case cppast::CppOperator::kGreater:
      stm << '>';
      break;
    case cppast::CppOperator::kPlusEqual:
      stm << "+=";
      break;
    case cppast::CppOperator::kMinusEqual:
      stm << "-=";
      break;
    case cppast::CppOperator::kMulEqual:
      stm << "*=";
      break;
    case cppast::CppOperator::kDivEqual:
      stm << "/=";
      break;
    case cppast::CppOperator::kPerEqual:
      stm << "%=";
      break;
    case cppast::CppOperator::kXorEqual:
      stm << "^=";
      break;
    case cppast::CppOperator::kAndEqual:
      stm << "&=";
      break;
    case cppast::CppOperator::kOrEqual:
      stm << "|=";
      break;
    case cppast::CppOperator::kLeftShift:
      stm << "<<";
      break;
    case cppast::CppOperator::kRightShift:
      stm << ">>";
      break;
    case cppast::CppOperator::kLShiftEqual:
      stm << "<<=";
      break;
    case cppast::CppOperator::kRShiftEqual:
      stm << ">>=";
      break;
    case cppast::CppOperator::kCmpEqual:
      stm << "==";
      break;
    case cppast::CppOperator::kNotEqual:
      stm << "!=";
      break;
    case cppast::CppOperator::kLessEqual:
      stm << "<=";
      break;
    case cppast::CppOperator::kGreaterEqual:
      stm << ">=";
      break;
    case cppast::CppOperator::k3WayCmp:
      stm << "<=>";
      break;
    case cppast::CppOperator::kComma:
      stm << ',';
      break;
    case cppast::CppOperator::kDot:
      stm << '.';
      break;
    case cppast::CppOperator::kArrow:
      stm << "->";
      break;
    case cppast::CppOperator::kArrowStar:
      stm << ".*";
      break;

    default:
      break;
  }
}

void CppWriter::emitIfBlock(const cppast::CppIfBlock& ifBlock, std::ostream& stm, CppIndent indentation) const
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

void CppWriter::emitWhileBlock(const cppast::CppWhileBlock& whileBlock, std::ostream& stm, CppIndent indentation) const
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

void CppWriter::emitDoBlock(const cppast::CppDoWhileBlock& doBlock, std::ostream& stm, CppIndent indentation) const
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

void CppWriter::emitForBlock(const cppast::CppForBlock& forBlock, std::ostream& stm, CppIndent indentation) const
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

void CppWriter::emitSwitchBlock(const cppast::CppSwitchBlock& switchBlock,
                                std::ostream&                 stm,
                                CppIndent                     indentation) const
{
  stm << indentation << "switch(";
  emitExpr(*switchBlock.condition(), stm);
  stm << ")\n";
  stm << indentation++ << "{\n";
  for (const auto& caseStmt : switchBlock.body())
  {
    if (caseStmt.caseExpr())
    {
      stm << indentation++ << "case ";
      emitExpr(*caseStmt.caseExpr(), stm);
      stm << ":\n";
    }
    else
    {
      stm << "default:\n";
    }
    if (caseStmt.body())
      emitCompound(*caseStmt.body(), stm, indentation);
    --indentation;
  }
  stm << --indentation << "}\n";
}

void CppWriter::emitMonomialExpr(const cppast::CppMonomialExpr& expr, std::ostream& stm) const
{
  // clang-format off
  switch(expr.oper())
  {
  case cppast::CppUnaryOperator::UNARY_PLUS           : stm << "+" ; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::UNARY_MINUS          : stm << "-" ; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::PREFIX_INCREMENT     : stm << "++"; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::PREFIX_DECREMENT     : stm << "--"; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::BIT_TOGGLE           : stm << "~" ; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::LOGICAL_NOT          : stm << "!" ; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::DEREFER              : stm << "*" ; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::REFER                : stm << "&" ; emitExpr(expr.term(), stm); break;

  case cppast::CppUnaryOperator::POSTFIX_INCREMENT    : emitExpr(expr.term(), stm); stm << "++"; break;
  case cppast::CppUnaryOperator::POSTFIX_DECREMENT    : emitExpr(expr.term(), stm); stm << "--"; break;

  case cppast::CppUnaryOperator::VARIADIC             : emitExpr(expr.term(), stm); stm << "..."; break;

  case cppast::CppUnaryOperator::NEW                  : stm << "new "       ; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::DELETE               : stm << "delete "    ; emitExpr(expr.term(), stm); break;
  case cppast::CppUnaryOperator::DELETE_AARAY         : stm << "delete[] "  ; emitExpr(expr.term(), stm); break;

  case cppast::CppUnaryOperator::PARENTHESIZE         : stm << '('          ; emitExpr(expr.term(), stm); stm << ')'; break;
  case cppast::CppUnaryOperator::SIZE_OF              : stm << "siezeof("   ; emitExpr(expr.term(), stm); stm << ')'; break;
  case cppast::CppUnaryOperator::VARIADIC_SIZE_OF     : stm << "sizeof...(" ; emitExpr(expr.term(), stm); stm << ')'; break;
  }
  // clang-format on
}

void CppWriter::emitAtomicExpr(const cppast::CppAtomicExpression& expr, std::ostream& stm) const
{
  switch (expr.atomicExpressionType())
  {
    case cppast::CppAtomicExpressionType::STRING_LITERAL:
      emitStringLiteralExpr(static_cast<const cppast::CppStringLiteralExpr&>(expr), stm);
      break;
    case cppast::CppAtomicExpressionType::CHAR_LITERAL:
      emitCharLiteralExpr(static_cast<const cppast::CppCharLiteralExpr&>(expr), stm);
      break;
    case cppast::CppAtomicExpressionType::NUMBER_LITEREL:
      emitNumberLiteralExpr(static_cast<const cppast::CppNumberLiteralExpr&>(expr), stm);
      break;
    case cppast::CppAtomicExpressionType::NAME:
      emitNameExpr(static_cast<const cppast::CppNameExpr&>(expr), stm);
      break;
    case cppast::CppAtomicExpressionType::VARTYPE:
      emitVartypeExpr(static_cast<const cppast::CppVartypeExpression&>(expr), stm);
      break;
    case cppast::CppAtomicExpressionType::LAMBDA:
      emitLambdaExpr(static_cast<const cppast::CppLambdaExpr&>(expr), stm);
      break;
  }
}

void CppWriter::emitStringLiteralExpr(const cppast::CppStringLiteralExpr& expr, std::ostream& stm) const
{
  stm << expr.value();
}
void CppWriter::emitCharLiteralExpr(const cppast::CppCharLiteralExpr& expr, std::ostream& stm) const
{
  stm << expr.value();
}
void CppWriter::emitNumberLiteralExpr(const cppast::CppNumberLiteralExpr& expr, std::ostream& stm) const
{
  stm << expr.value();
}
void CppWriter::emitNameExpr(const cppast::CppNameExpr& expr, std::ostream& stm) const
{
  stm << expr.value();
}
void CppWriter::emitVartypeExpr(const cppast::CppVartypeExpression& expr, std::ostream& stm) const
{
  emitVarType(expr.value(), stm);
}
void CppWriter::emitLambdaExpr(const cppast::CppLambdaExpr& expr, std::ostream& stm) const
{
  // emitLambda(expr.value(), stm);
}

void CppWriter::emitBinomialExpr(const cppast::CppBinomialExpr& expr, std::ostream& stm) const
{
  // clang-format off
  switch (expr.oper())
  {
  case cppast::CppBinaryOperator::PLUS:                     emitExpr(expr.term1(), stm); stm << " + "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::MINUS:                    emitExpr(expr.term1(), stm); stm << " - "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::MUL:                      emitExpr(expr.term1(), stm); stm << " * "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::DIV:                      emitExpr(expr.term1(), stm); stm << " / "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::PERCENT:                  emitExpr(expr.term1(), stm); stm << " % "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::AND:                      emitExpr(expr.term1(), stm); stm << " & "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::OR:                       emitExpr(expr.term1(), stm); stm << " | "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::XOR:                      emitExpr(expr.term1(), stm); stm << " ^ "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::ASSIGN:                   emitExpr(expr.term1(), stm); stm << " = "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::LESS:                     emitExpr(expr.term1(), stm); stm << " < "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::GREATER:                  emitExpr(expr.term1(), stm); stm << " > "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::COMMA:                    emitExpr(expr.term1(), stm); stm << " , "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::DOT:                      emitExpr(expr.term1(), stm); stm << " . "; emitExpr(expr.term2(), stm); break;

  case cppast::CppBinaryOperator::LOGICAL_AND:              emitExpr(expr.term1(), stm); stm << " && "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::LOGICAL_OR:               emitExpr(expr.term1(), stm); stm << " || "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::PLUS_ASSIGN:              emitExpr(expr.term1(), stm); stm << " += "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::MINUS_ASSIGN:             emitExpr(expr.term1(), stm); stm << " -= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::MUL_ASSIGN:               emitExpr(expr.term1(), stm); stm << " *= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::DIV_ASSIGN:               emitExpr(expr.term1(), stm); stm << " /= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::PERCENT_ASSIGN:           emitExpr(expr.term1(), stm); stm << " %= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::XOR_ASSIGN:               emitExpr(expr.term1(), stm); stm << " ^= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::AND_ASSIGN:               emitExpr(expr.term1(), stm); stm << " &= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::OR_ASSIGN:                emitExpr(expr.term1(), stm); stm << " |= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::LEFT_SHIFT:               emitExpr(expr.term1(), stm); stm << " << "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::INSERTION:                emitExpr(expr.term1(), stm); stm << " << "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::RIGHT_SHIFT:              emitExpr(expr.term1(), stm); stm << " >> "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::EXTRACTION:               emitExpr(expr.term1(), stm); stm << " >> "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::EQUAL:                    emitExpr(expr.term1(), stm); stm << " == "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::NOT_EQUAL:                emitExpr(expr.term1(), stm); stm << " != "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::LESS_EQUAL:               emitExpr(expr.term1(), stm); stm << " <= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::GREATER_EQUAL:            emitExpr(expr.term1(), stm); stm << " >= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::ARROW:                    emitExpr(expr.term1(), stm); stm << " -> "; emitExpr(expr.term2(), stm); break;

  case cppast::CppBinaryOperator::LOGICAL_AND_ASSIGN:       emitExpr(expr.term1(), stm); stm << " &&= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::LOGICAL_OR_ASSIGN:        emitExpr(expr.term1(), stm); stm << " ||= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::LSHIFT_ASSIGN:            emitExpr(expr.term1(), stm); stm << " <<= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::RSHIFT_ASSIGN:            emitExpr(expr.term1(), stm); stm << " >>= "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::THREE_WAY_CMP:            emitExpr(expr.term1(), stm); stm << " <=> "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::ARROW_STAR:               emitExpr(expr.term1(), stm); stm << " ->* "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::ARRAY_INDEX:              emitExpr(expr.term1(), stm); stm << '['; emitExpr(expr.term2(), stm); stm << ']'; break;

  case cppast::CppBinaryOperator::PLACEMENT_NEW:        stm << "new (";   emitExpr(expr.term1(), stm); stm << ") "; emitExpr(expr.term2(), stm); break;
  case cppast::CppBinaryOperator::GLOBAL_PLACEMENT_NEW: stm << "::new ("; emitExpr(expr.term1(), stm); stm << ") "; emitExpr(expr.term2(), stm); break;

  case cppast::CppBinaryOperator::USER_LITERAL: emitExpr(expr.term1(), stm); emitExpr(expr.term2(), stm); break;
  }
  // clang-format on
}

void CppWriter::emitTrinomialExpr(const cppast::CppTrinomialExpr& expr, std::ostream& stm) const
{
  switch (expr.oper())
  {
    case cppast::CppTernaryOperator::CONDITIONAL:
      emitExpr(expr.term1(), stm);
      stm << " ? ";
      emitExpr(expr.term2(), stm);
      stm << " : ";
      emitExpr(expr.term3(), stm);
  }
}

void CppWriter::emitFuncCallExpr(const cppast::CppFunctionCallExpr& expr, std::ostream& stm) const
{
  emitExpr(expr.function(), stm);
  stm << '(';
  const char* sep = "";
  for (size_t i = 0; i < expr.numArgs(); ++i)
  {
    stm << sep;
    emitExpr(expr.arg(i), stm);
    sep = ", ";
  }
  stm << ')';
}

void CppWriter::emitUniformInitializerExpr(const cppast::CppUniformInitializerExpr& expr, std::ostream& stm) const
{
  stm << expr.name();
  stm << '{';
  const char* sep = "";
  for (size_t i = 0; i < expr.numArgs(); ++i)
  {
    stm << sep;
    emitExpr(expr.arg(i), stm);
    sep = ", ";
  }
  stm << '}';
}

void CppWriter::emitInitializerListExpr(const cppast::CppInitializerListExpr& expr, std::ostream& stm) const
{
  stm << '{';
  const char* sep = "";
  for (size_t i = 0; i < expr.numArgs(); ++i)
  {
    stm << sep;
    emitExpr(expr.arg(i), stm);
    sep = ", ";
  }
  stm << '}';
}

void CppWriter::emitCStyleTypecastExpr(const cppast::CppCStyleTypecastExpr& expr, std::ostream& stm) const
{
  stm << "(";
  emitVarType(expr.targetType(), stm);
  stm << ")";
  emitExpr(expr.inputExpresion(), stm);
}
void CppWriter::emitFunctionStyleTypecastExpr(const cppast::CppFunctionStyleTypecastExpr& expr, std::ostream& stm) const
{
  emitVarType(expr.targetType(), stm);
  stm << ">(";
  emitExpr(expr.inputExpresion(), stm);
  stm << ')';
}
void CppWriter::emitStaticCastExpr(const cppast::CppStaticCastExpr& expr, std::ostream& stm) const
{
  stm << "static_cast<";
  emitVarType(expr.targetType(), stm);
  stm << ">(";
  emitExpr(expr.inputExpresion(), stm);
  stm << ')';
}
void CppWriter::emitConstCastExpr(const cppast::CppConstCastExpr& expr, std::ostream& stm) const
{
  stm << "const_cast<";
  emitVarType(expr.targetType(), stm);
  stm << ">(";
  emitExpr(expr.inputExpresion(), stm);
  stm << ')';
}
void CppWriter::emitDynamiCastExpr(const cppast::CppDynamiCastExpr& expr, std::ostream& stm) const
{
  stm << "dynamic_cast<";
  emitVarType(expr.targetType(), stm);
  stm << ">(";
  emitExpr(expr.inputExpresion(), stm);
  stm << ')';
}
void CppWriter::emitReinterpretCastExpr(const cppast::CppReinterpretCastExpr& expr, std::ostream& stm) const
{
  stm << "reinterpret_cast<";
  emitVarType(expr.targetType(), stm);
  stm << ">(";
  emitExpr(expr.inputExpresion(), stm);
  stm << ')';
}

void CppWriter::emitExpr(const cppast::CppExpression& expr, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation;
  switch (expr.expressionType())
  {
    case cppast::CppExpressionType::ATOMIC:
      emitAtomicExpr(static_cast<const cppast::CppAtomicExpression&>(expr), stm);
      break;
    case cppast::CppExpressionType::MONOMIAL:
      emitMonomialExpr(static_cast<const cppast::CppMonomialExpr&>(expr), stm);
      break;
    case cppast::CppExpressionType::BINOMIAL:
      emitBinomialExpr(static_cast<const cppast::CppBinomialExpr&>(expr), stm);
      break;
    case cppast::CppExpressionType::TRINOMIAL:
      emitTrinomialExpr(static_cast<const cppast::CppTrinomialExpr&>(expr), stm);
      break;
    case cppast::CppExpressionType::FUNCTION_CALL:
      emitFuncCallExpr(static_cast<const cppast::CppFunctionCallExpr&>(expr), stm);
      break;
    case cppast::CppExpressionType::UNIFORM_INITIALIZER:
      emitUniformInitializerExpr(static_cast<const cppast::CppUniformInitializerExpr&>(expr), stm);
      break;
    case cppast::CppExpressionType::INITIALIZER_LIST:
      emitInitializerListExpr(static_cast<const cppast::CppInitializerListExpr&>(expr), stm);
      break;
    case cppast::CppExpressionType::TYPECAST:
      break;
  }
}

} // namespace cppcodegen
