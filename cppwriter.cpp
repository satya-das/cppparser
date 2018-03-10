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

#include "cppwriter.h"

//////////////////////////////////////////////////////////////////////////

void CppWriter::emit(const CppObj* cppObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  switch (cppObj->objType_)
  {
  case CppObj::kBlankLine:
    return emitBlankLines	((CppBlankLine*)	cppObj, stm);
  case CppObj::kHashDefine:
    return emitDefine		((CppDefine*)		cppObj, stm);
  case CppObj::kHashUndef:
    return emitUndef		((CppUndef*)		cppObj, stm);
  case CppObj::kHashInclude:
    return emitInclude		((CppInclude*)		cppObj, stm);
  case CppObj::kHashIf:
    return emitHashIf		((CppHashIf*)		cppObj,	stm);
  case CppObj::kHashPragma:
    return emitPragma		((CppPragma*)		cppObj,	stm);

  case CppObj::kVar:
    return emitVar			((CppVar*)			cppObj, stm, indentation);
  case CppObj::kVarList:
    return emitVarList		((CppVarList*)		cppObj, stm, indentation);
  case CppObj::kEnum:
    return emitEnum			((CppEnum*)			cppObj, stm, indentation);
  case CppObj::kDocComment:
    return emitDocComment	((CppDocComment*)	cppObj, stm, indentation);
  case CppObj::kTypedef:
    return emitTypedef		((CppTypedef*)		cppObj, stm, indentation);
  case CppObj::kCompound:
    return emitCompound		((CppCompound*)		cppObj, stm, indentation);
  case CppObj::kFwdClsDecl:
    return emitFwdDecl		((CppFwdClsDecl*)	cppObj, stm, indentation);
  case CppObj::kFunction:
    return emitFunction		((CppFunction*)		cppObj, stm, indentation);
  case CppObj::kConstructor:
    return emitConstructor	((CppConstructor*)	cppObj, stm, indentation);
  case CppObj::kDestructor:
    return emitDestructor	((CppDestructor*)	cppObj, stm, indentation);
  case CppObj::kFunctionPtr:
    return emitFunctionPtr	((CppFunctionPtr*)	cppObj, stm, indentation);
  case CppObj::kIfBlock:
    return emitIfBlock      ((CppIfBlock*) cppObj, stm, indentation);
  case CppObj::kWhileBlock:
    return emitWhileBlock   ((CppWhileBlock*) cppObj, stm, indentation);
  case CppObj::kDoWhileBlock:
    return emitDoBlock      ((CppDoWhileBlock*) cppObj, stm, indentation);
  case CppObj::kForBlock:
    return emitForBlock      ((CppForBlock*) cppObj, stm, indentation);
  case CppObj::kExpression:
    emitExpr((CppExpr*) cppObj, stm, indentation);
    stm << ";\n";
    break;

  case CppObj::kBlob:
    return emitBlob((CppBlob*) cppObj, stm);
  }
}

void CppWriter::emitBlankLines(const CppBlankLine* blankLineObj, std::ostream& stm) const
{
  for (int i = 0; i < blankLineObj->numLines_; ++i)
    stm << '\n';
}

void CppWriter::emitDefine(const CppDefine* defObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "define " << defObj->name_;
  if (!defObj->defn_.empty())
    stm << '\t' << defObj->defn_;
  stm << '\n';
}

void CppWriter::emitUndef(const CppUndef* undefObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "undef " << undefObj->name_ << '\n';
}

void CppWriter::emitInclude(const CppInclude* includeObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "include " << includeObj->name_ << '\n';
}

void CppWriter::emitHashIf(const CppHashIf* hashIfObj, std::ostream& stm) const
{
  switch (hashIfObj->condType_)
  {
  case CppHashIf::kIf:
    stm << '#' << preproIndent_ << "if " << hashIfObj->cond_ << '\n';
    ++preproIndent_;
    break;

  case CppHashIf::kIfDef:
    stm << '#' << preproIndent_ << "ifdef " << hashIfObj->cond_ << '\n';
    ++preproIndent_;
    break;

  case CppHashIf::kIfNDef:
    stm << '#' << preproIndent_ << "ifndef " << hashIfObj->cond_ << '\n';
    ++preproIndent_;
    break;

  case CppHashIf::kElIf:
    stm << '#' << --preproIndent_ << "elif " << hashIfObj->cond_ << '\n';
    ++preproIndent_;
    break;

  case CppHashIf::kElse:
    stm << '#' << --preproIndent_ << "else " << hashIfObj->cond_ << '\n';
    ++preproIndent_;
    break;

  case CppHashIf::kEndIf:
    stm << '#' << --preproIndent_ << "endif\n";
    break;
  }
}

void CppWriter::emitPragma(const CppPragma* pragmaObj, std::ostream& stm) const
{
  stm << '#' << preproIndent_ << "pragma " << pragmaObj->defn_ << '\n';
}

void CppWriter::emitBlob(const CppBlob* blobObj, std::ostream& stm) const
{
  stm << blobObj->blob_;
}

void CppWriter::emitVarType(const CppVarType* varTypeObj, std::ostream& stm) const
{
  if (varTypeObj->typeAttr_&kConst)
    stm << "const ";

  stm << varTypeObj->baseType_;
  for (unsigned short ptrLevel = 0; ptrLevel < varTypeObj->ptrLevel_; ++ptrLevel)
    stm << '*';
  if (varTypeObj->refType_ == kByRef)
    stm << '&';
  else if (varTypeObj->refType_ == kRValRef)
    stm << "&&";
  if (varTypeObj->typeAttr_&kArray)
  {
    stm << '[';
    if (varTypeObj->arraySize_)
      emitExpr(varTypeObj->arraySize_, stm);
    stm << ']';
  }
}

void CppWriter::emitVar(const CppVar* varObj, std::ostream& stm, CppIndent indentation) const
{
  emitVar(varObj, stm, indentation, false);
}

void CppWriter::emitVar(const CppVar* varObj, std::ostream& stm, CppIndent indentation, bool skipName) const
{
  if ((varObj->varAttr_&kFuncParam) == 0)
  {
    stm << indentation;
    if (varObj->typeAttr_&kStatic)
      stm << "static ";
    else if (varObj->typeAttr_&kExtern)
      stm << "extern ";
    if (!varObj->apidocer_.empty())
    {
      stm << varObj->apidocer_ << ' ';
    }
  }
  emitVarType((CppVarType*) varObj, stm);

  if (varObj->varAttr_&kConst)
    stm << " const";

  if (!skipName && !varObj->name_.empty())
    stm << ' ' << varObj->name_;
  if (varObj->varAttr_&kArray)
  {
    stm << '[';
    if (varObj->arraySize_)
      emitExpr(varObj->arraySize_, stm);
    stm << ']';
  }
  if (varObj->assign_)
  {
    stm << " = ";
    emitExpr(varObj->assign_, stm);
  }
  if ((varObj->varAttr_&kFuncParam) == 0 && !skipName && !varObj->name_.empty())
    stm << ";\n";
}

void CppWriter::emitVarList(const CppVarList* varListObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  for (CppVarObjList::const_iterator varItr = varListObj->varlist_.begin(); varItr != varListObj->varlist_.end(); ++varItr)
    emitVar(*varItr, stm, indentation);
}

void CppWriter::emitEnum(const CppEnum* enmObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  stm << indentation << "enum";
  if (enmObj->isClass_)
    stm << " class";
  if (!enmObj->name_.empty())
    stm << ' ' << enmObj->name_;
  if (!enmObj->underlyingType_.empty())
    stm << " : " << enmObj->underlyingType_;
  if (enmObj->itemList_)
  {
    stm << "\n{\n" << indentation++;
    for (CppEnumItemList::const_iterator itmItr = enmObj->itemList_->begin(); itmItr != enmObj->itemList_->end(); ++itmItr)
    {
      CppEnumItem* enmItem = *itmItr;
      if (enmItem->name_.empty())
        emit(enmItem->anyItem_, stm, indentation);
      else
      {
        stm << indentation << enmItem->name_;
        if (enmItem->val_)
        {
          stm << " = ";
          emitExpr(enmItem->val_, stm);
        }
        stm << ",\n";
      }
    }
    stm << --indentation << "}";
  }
  stm << ";\n";
}

void CppWriter::emitTypedef(const CppTypedef* typedefObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  stm << indentation << "typedef ";
  emitVarType((CppVarType*) typedefObj, stm);
  for (std::list<std::string>::const_iterator namItr = typedefObj->names_.begin(); namItr != typedefObj->names_.end(); ++namItr)
  {
    if (namItr != typedefObj->names_.begin())
      stm << ',';
    stm << ' ' << *namItr;
  }
  stm << ";\n";
}

void CppWriter::emitFwdDecl(const CppFwdClsDecl* fwdDeclObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  stm << indentation << fwdDeclObj->cmpType_ << ' ' << fwdDeclObj->name_ << ";\n";
}

void CppWriter::emitCompound(const CppCompound* compoundObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  if (compoundObj->compoundType_&kNamespace)
  {
    stm << indentation << compoundObj->compoundType_ << ' ';
    if (!compoundObj->apidocer_.empty())
      stm << compoundObj->apidocer_ << ' ';
    stm << compoundObj->name_;
  }
  if (compoundObj->inheritList_)
  {
    ++indentation;
    char sep = ':';
    stm << ' ';
    for (CppInheritanceList::const_iterator inhItr = compoundObj->inheritList_->begin(); inhItr != compoundObj->inheritList_->end(); ++inhItr)
    {
      stm << sep << ' ' << inhItr->inhType << ' ' << inhItr->baseName;
      sep = ',';
    }
    --indentation;
  }
  if (compoundObj->compoundType_&kNamespace)
    stm << indentation++ << "\n{\n";
  else if (compoundObj->compoundType_ == kExternCBlock)
    stm << indentation << "extern \"C\" {\n";

  CppObjProtLevel lastProtLevel = kUnknownProt;
  for (CppObjArray::const_iterator memItr = compoundObj->members_.begin(); memItr != compoundObj->members_.end(); ++memItr)
  {
    CppObj* memObj = *memItr;
    if (memObj->prot_ != kUnknownProt && lastProtLevel != memObj->prot_)
    {
      stm << --indentation << memObj->prot_ << ':' << '\n';
      lastProtLevel = memObj->prot_;
      ++indentation;
    }
    emit(memObj, stm, indentation);
  }
  if (compoundObj->compoundType_&kNamespace)
    stm << --indentation << "};\n";
  else if (compoundObj->compoundType_ == kExternCBlock)
    stm << indentation << "}\n";
}

void CppWriter::emitParamList(const CppParamList*		paramListObj, std::ostream& stm) const
{
  emitParamList(paramListObj, stm, false);
}

void CppWriter::emitParamList(const CppParamList* paramListObj, std::ostream& stm, bool skipParamName) const
{
  for (auto prmItr = paramListObj->begin(); prmItr != paramListObj->end(); ++prmItr)
  {
    if (prmItr != paramListObj->begin())
      stm << ", ";
    CppVarOrFuncPtrType param = *prmItr;
    switch (param.cppObj->objType_)
    {
    case CppObj::kVar: emitVar(param.varObj, stm, CppIndent(), skipParamName);
      break;
    case CppObj::kFunctionPtr: emitFunctionPtr(param.funcPtr, stm, skipParamName);
      break;
    default:
      assert(false);
    }
  }
}

void CppWriter::emitFunction(const CppFunction* funcObj, std::ostream& stm, CppIndent indentation, bool skipName, bool skipParamName) const
{
  if ((funcObj->attr_&(kFuncParam|kTypedef)) == 0)
    stm << indentation;
  if (funcObj->attr_&kStatic)
    stm << "static ";
  else if (funcObj->attr_&kExtern)
    stm << "extern ";
  else if (funcObj->attr_&kVirtual)
    stm << "virtual ";
  else if (funcObj->attr_&kInline)
    stm << "inline ";
  else if (funcObj->attr_&kExplicit)
    stm << "explicit ";
  else if (funcObj->attr_&kFriend)
    stm << "friend ";
  if (!funcObj->docer1_.empty())
    stm << funcObj->docer1_ << ' ';
  emitVarType(funcObj->retType_, stm);
  if (funcObj->objType_ == CppObj::kFunctionPtr)
    stm << " (";
  else
    stm << ' ';
  if (!funcObj->docer2_.empty())
    stm << funcObj->docer2_ << ' ';
  if (funcObj->objType_ == CppObj::kFunctionPtr)
  {
    stm << '*';
    if (!skipName)
      stm << funcObj->name_ << ") ";
  }
  else if (!skipName)
  {
    stm << funcObj->name_;
  }
  stm << '(';
  if (funcObj->params_)
    emitParamList(funcObj->params_, stm, skipParamName);
  stm << ')';

  if ((funcObj->attr_&kConst) == kConst)
    stm << " const";
  if ((funcObj->attr_&kPureVirtual) == kPureVirtual)
    stm << " = 0";
  if (!skipParamName && funcObj->defn_ && !((getEmittingType()==kHeader) || funcObj->attr_ & kInline))
  {
    stm << '\n' << indentation++ << "{\n";
    emitCompound(funcObj->defn_, stm, indentation);
    stm << --indentation << "}\n";
  }
  else if ((funcObj->attr_&kFuncParam) == 0)
  {
    stm << ";\n";
  }
}

void CppWriter::emitFunction(const CppFunction* funcObj, std::ostream& stm, CppIndent indentation) const
{
  return emitFunction(funcObj, stm, indentation, false, false);
}

void CppWriter::emitFunctionPtr(const CppFunctionPtr* funcPtrObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  if (funcPtrObj->attr_&kTypedef)
    stm << indentation << "typedef ";
  emitFunction((CppFunction*) funcPtrObj, stm, indentation);
}

void CppWriter::emitConstructor(const CppConstructor* ctorObj, std::ostream& stm, CppIndent indentation, bool skipParamName) const
{
  stm << indentation;
  if (ctorObj->attr_&kInline)
    stm << "inline ";
  else if (ctorObj->attr_&kExplicit)
    stm << "explicit ";
  stm << ctorObj->name_;
  stm << '(';
  if (ctorObj->params_)
    emitParamList(ctorObj->params_, stm, skipParamName);
  stm << ')';
  if (!skipParamName && ctorObj->memInitList_)
  {
    char sep = ':';
    ++indentation;
    for (CppMemInitList::const_iterator memInitItr = ctorObj->memInitList_->begin(); memInitItr != ctorObj->memInitList_->end(); ++memInitItr)
    {
      stm << sep << ' ' << memInitItr->first << '(';
      emitExpr(memInitItr->second, stm);
      stm << ")\n";
      sep = ',';
    }
    --indentation;
  }
  if (!skipParamName && ctorObj->defn_)
  {
    stm << '\n' << ++indentation << '{';
    emitCompound(ctorObj->defn_, stm, indentation);
    stm << '\n' << --indentation << '}';
  }
  else
  {
    stm << ";\n";
  }
}

void CppWriter::emitConstructor(const CppConstructor*	ctorObj, std::ostream& stm, CppIndent indentation) const
{
  emitConstructor(ctorObj, stm, indentation, false);
}

void CppWriter::emitDestructor(const CppDestructor* dtorObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  stm << indentation;
  if (dtorObj->attr_&kInline)
    stm << "inline ";
  else if (dtorObj->attr_&kExplicit)
    stm << "explicit ";
  else if (dtorObj->attr_&kVirtual)
    stm << "virtual ";
  stm << dtorObj->name_ << "()";

  if (dtorObj->defn_)
  {
    stm << '\n' << indentation++ << "{\n";
    emitCompound(dtorObj->defn_, stm, indentation);
    stm << --indentation << "}\n";
  }
  else
  {
    stm << ";\n";
  }
}

void CppWriter::emitDocComment(const CppDocComment* docCommentObj, std::ostream& stm, CppIndent indentation /* = CppIndent()*/) const
{
  stm << docCommentObj->doc_ << '\n';
}

inline std::ostream& operator <<(std::ostream& stm, CppOperType op)
{
  switch (op)
  {
  case kUnaryMinus:
    stm << '-';
    break;
  case kBitToggle	:
    stm << '~';
    break;
  case kLogNot	:
    stm << '!';
    break;
  case kDerefer	:
    stm << '*';
    break;
  case kRefer		:
    stm << '&';
    break;
  case kPreIncrement		:
  case kPostIncrement		:
    stm << "++";
    break;
  case kPreDecrement		:
  case kPostDecrement		:
    stm << "--";
    break;
  case kPlus		:
    stm << '+';
    break;
  case kMinus		:
    stm << '-';
    break;
  case kMul		:
    stm << '*';
    break;
  case kDiv		:
    stm << '/';
    break;
  case kPercent		:
    stm << '%';
    break;
  case kAnd	:
    stm << "&&";
    break;
  case kOr	:
    stm << "||";
    break;
  case kBitAnd	:
    stm << '&';
    break;
  case kBitOr		:
    stm << '|';
    break;
  case kXor		:
    stm << '^';
    break;
  case kEqual		:
    stm << '=';
    break;
  case kLess :
    stm << '<';
    break;
  case kGreater :
    stm << '>';
    break;
  case kPlusEqual	:
    stm << "+=";
    break;
  case kMinusEqual	:
    stm << "-=";
    break;
  case kMulEqual	:
    stm << "*=";
    break;
  case kDivEqual	:
    stm << "/=";
    break;
  case kPerEqual	:
    stm << "%=";
    break;
  case kXorEqual	:
    stm << "^=";
    break;
  case kAndEqual	:
    stm << "&=";
    break;
  case kOrEqual	:
    stm << "|=";
    break;
  case kLeftShift:
    stm << "<<";
    break;
  case kRightShift:
    stm << ">>";
    break;
  case kLShiftEqual:
    stm << "<<=";
    break;
  case kRShiftEqual:
    stm << ">>=";
    break;
  case kCmpEqual	:
    stm << "==";
    break;
  case kNotEqual	:
    stm << "!=";
    break;
  case kLessEqual :
    stm << "<=";
    break;
  case kGreaterEqual :
    stm << ">=";
    break;
  case k3WayCmp	:
    stm << "<=>";
    break;
  case kComma		:
    stm << ',';
    break;
  case kDot		:
    stm << '.';
    break;
  case kArrow		:
    stm << "->";
    break;
  case kArrowStar		:
    stm << "->*";
    break;
  }

  return stm;
}

void CppWriter::emitExprAtom(const CppExprAtom& exprAtm, std::ostream& stm, CppIndent indentation /*= CppIndent()*/) const
{
  switch (exprAtm.type)
  {
  case CppExprAtom::kAtom:
    stm << *(exprAtm.atom);
    break;
  case CppExprAtom::kExpr:
    emitExpr(exprAtm.expr, stm);
    break;
  case CppExprAtom::kExprList:
    emitExprList(exprAtm.list, stm, ++indentation);
    break;
  }
}

void CppWriter::emitExprList(const CppExprList* exprList, std::ostream& stm, CppIndent indentation /*= CppIndent()*/) const
{
  if (exprList && !exprList->empty())
  {
    CppExprList::const_iterator exprItr = exprList->begin();
    CppExpr* expr = *exprItr;
    if (expr->flags_&CppExpr::kInitializer)
      stm << '\n' << ++indentation;
    emitExpr(expr, stm);
    for (++exprItr; exprItr != exprList->end(); ++exprItr)
    {
      expr = *exprItr;
      stm << ", ";
      if (expr->flags_&CppExpr::kInitializer)
        stm << '\n' << indentation;
      emitExpr(expr, stm);
    }
    if (expr->flags_&CppExpr::kInitializer)
      stm << '\n' << --indentation;
  }
}

void CppWriter::emitExpr(const CppExpr* exprObj, std::ostream& stm, CppIndent indentation /*= CppIndent()*/) const
{
  if (exprObj == NULL) return;
  stm << indentation;
  if (exprObj->flags_ & CppExpr::kReturn)
    stm << "return ";
  if (exprObj->flags_ & CppExpr::kInitializer)
    stm << "{";
  if (exprObj->flags_ & CppExpr::kBracketed)
    stm << '(';
  if (exprObj->flags_ & CppExpr::kNew)
    stm << "new ";
  else if (exprObj->flags_ & CppExpr::kDelete)
    stm << "delete ";
  else if (exprObj->flags_ & CppExpr::kDeleteArray)
    stm << "delete[] ";
  if (exprObj->oper_ == kNone)
  {
    emitExprAtom(exprObj->expr1_, stm);
  }
  else if (exprObj->oper_ > kUnariPrefixOperatorStart && exprObj->oper_ < kUnariSufixOperatorStart)
  {
    stm << exprObj->oper_;
    emitExprAtom(exprObj->expr1_, stm);
  }
  else if (exprObj->oper_ > kUnariSufixOperatorStart && exprObj->oper_ < kBinaryOperatorStart)
  {
    emitExprAtom(exprObj->expr1_, stm);
    stm << exprObj->oper_;
  }
  else if (exprObj->oper_ > kBinaryOperatorStart && exprObj->oper_ < kSpecialOperations)
  {
    emitExprAtom(exprObj->expr1_, stm);
    stm << ' ' << exprObj->oper_ << ' ';
    emitExprAtom(exprObj->expr2_, stm);
  }
  else if (exprObj->oper_ == kFunctionCall)
  {
    emitExprAtom(exprObj->expr1_, stm);
    stm << '(';
    emitExprAtom(exprObj->expr2_, stm);
    stm << ')';
  }
  else if (exprObj->oper_ == kArrayElem)
  {
    emitExprAtom(exprObj->expr1_, stm);
    stm << '[';
    emitExprAtom(exprObj->expr2_, stm);
    stm << ']';
  }

  if (exprObj->flags_ & CppExpr::kBracketed)
    stm << ')';
  if (exprObj->flags_ & CppExpr::kInitializer)
    stm << "}";
}

void CppWriter::emitIfBlock(const CppIfBlock* ifBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation;
  stm << "if (";
  emitExpr(ifBlock->cond_, stm);
  stm << ")\n";
  stm << indentation << "{\n";
  ++indentation;
  if (ifBlock->body_)
    emit(ifBlock->body_, stm, indentation);
  --indentation;
  stm << indentation << "}\n";
}

void CppWriter::emitWhileBlock(const CppWhileBlock* whileBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation;
  stm << "while (";
  emitExpr(whileBlock->cond_, stm);
  stm << ")\n";
  stm << indentation << "{\n";
  ++indentation;
  if (whileBlock->body_)
    emit(whileBlock->body_, stm, indentation);
  --indentation;
  stm << indentation << "}\n";
}

void CppWriter::emitDoBlock(const CppDoWhileBlock* doBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << "do\n";
  stm << indentation << "{\n";
  ++indentation;
  if (doBlock->body_)
    emit(doBlock->body_, stm, indentation);
  --indentation;
  stm << indentation << "} while (";
  emitExpr(doBlock->cond_, stm);
  stm << ");\n";
}

void CppWriter::emitForBlock(const CppForBlock* forBlock, std::ostream& stm, CppIndent indentation) const
{
  stm << indentation << "for (";
  if (forBlock->start_)
    emitExpr(forBlock->start_, stm);
  stm << ';';
  if (forBlock->stop_)
  {
    stm << ' ';
    emitExpr(forBlock->stop_, stm);
  }
  stm << ';';
  if (forBlock->step_)
  {
    stm << ' ';
    emitExpr(forBlock->step_, stm);
  }
  stm << ")\n";
  stm << indentation << "{\n";
  ++indentation;
  if (forBlock->body_)
    emit(forBlock->body_, stm, indentation);
  --indentation;
  stm << indentation << "}\n";
}
