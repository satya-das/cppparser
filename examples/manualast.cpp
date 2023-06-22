#include <boost/filesystem.hpp>
#include <iostream>

#include "cppobjfactory.h"
#include "cppparser.h"
#include "cppwriter.h"

int main(){
  CppParser     parser;
  CppWriter     cppWriter;
  CppObjFactory cppObjFactory;

  CppVarType     retType("void");
  const auto     fooFunc = cppObjFactory.CreateFunction(CppAccessType::kPublic, "FooFunc", &retType, nullptr, 0);
  CppCompoundPtr foosBlock(new CppCompound(CppCompoundType::kBlock));

  { // out[0] = in1[0] + in2[0];
    auto* arrayOutIndex0 = new CppExpr(CppExprAtom("out"), CppOperator::kArrayElem, CppExprAtom("0"));
    auto* arrayIn0Index0 = new CppExpr(CppExprAtom("in0"), CppOperator::kArrayElem, CppExprAtom("0"));
    auto* arrayIn1Index0 = new CppExpr(CppExprAtom("in1"), CppOperator::kArrayElem, CppExprAtom("0"));
    auto* additionExpr   = new CppExpr(arrayIn0Index0, CppOperator::kPlus, arrayIn1Index0);
    auto* assignExpr     = new CppExpr(arrayOutIndex0, CppOperator::kEqual, additionExpr);
    foosBlock->addMember(assignExpr);
  }

  { // int myVar = 1;
    auto* myVar = new CppVar(
      new CppVarType("int"),
      CppVarDecl("myVar", new CppExpr("1"), AssignType::kUsingEqual)
    );
    foosBlock->addMember(myVar);
  }

  { // int myVar = 1;
    auto* myVar = new CppVar(
      new CppVarType("float"),
      CppVarDecl("myPtr")
    );
    myVar->varType()->typeModifier().ptrLevel_ = 1;
    foosBlock->addMember(myVar);
  }

  { // myVar = 2;
    auto* myVar = new CppExpr(new CppExpr("myVar"), CppOperator::kEqual, new CppExpr("2"));
    foosBlock->addMember(myVar);
  }

  { // float myArray[100];
    auto *myArray = new CppVar(new CppVarType("float"), CppVarDecl("myArray"));
    myArray->addArraySize(new CppExpr("100"));
    foosBlock->addMember(myArray);
  }

  { // if(a==b | b==c){}else{}
    auto *bool1 = new CppExpr(new CppExpr("a"), CppOperator::kCmpEqual, new CppExpr("b"));
    auto *bool2 = new CppExpr(new CppExpr("b"), CppOperator::kCmpEqual, new CppExpr("c"));
    auto *boolVal = new CppExpr(bool1, CppOperator::kOr, bool2);
    auto *ifElse = new CppIfBlock(boolVal, new CppCompound(CppCompoundType::kBlock), new CppCompound(CppCompoundType::kBlock));
    foosBlock->addMember(ifElse);
  }

  { // for(int i=0; i<100; i++){}
    auto *start = new CppVar(new CppVarType("int"), CppVarDecl("i", new CppExpr("0"), AssignType::kUsingEqual));
    auto *stop = new CppExpr(new CppExpr("i"), CppOperator::kLess, new CppExpr("100"));
    auto *step = new CppExpr(new CppExpr("i"), CppOperator::kPostIncrement);

    auto *loop = new CppForBlock(start, stop, step, new CppCompound(CppCompoundType::kBlock));
    foosBlock->addMember(loop);
  }

  { //retval = myFunc(1, aa, myFunc(2));
    auto *paramChain1 = new CppExpr(new CppExpr("1"), CppOperator::kComma, new CppExpr("aa"));
    auto *funcCallParam = new CppExpr(new CppExpr("myFunc"), CppOperator::kFunctionCall, new CppExpr("2"));
    auto *paramChain2 = new CppExpr(paramChain1, CppOperator::kComma, funcCallParam);
    auto *funcCall = new CppExpr(new CppExpr("myFunc"), CppOperator::kFunctionCall, paramChain2);
    auto *retValAssign = new CppExpr(new CppExpr("retVal"), CppOperator::kEqual, funcCall);
    foosBlock->addMember(retValAssign);
  }

  { //int retval = myFunc(1, aa, myFunc(2));
    auto *paramChain1 = new CppExpr(new CppExpr("1"), CppOperator::kComma, new CppExpr("aa"));
    auto *funcCallParam = new CppExpr(new CppExpr("myFunc"), CppOperator::kFunctionCall, new CppExpr("2"));
    auto *paramChain2 = new CppExpr(paramChain1, CppOperator::kComma, funcCallParam);
    auto *funcCall = new CppExpr(new CppExpr("myFunc"), CppOperator::kFunctionCall, paramChain2);
    auto *retValVar = new CppVar(new CppVarType("int"), CppVarDecl("retVal", funcCall, AssignType::kUsingEqual));

    foosBlock->addMember(retValVar);
  }

  fooFunc->defn(foosBlock.get());

  std::ofstream ofStream("/tmp/T2.txt");
  cppWriter.emit(fooFunc, ofStream);
  std::cout << "Done." << std::endl;
}