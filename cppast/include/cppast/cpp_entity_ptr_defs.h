// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DEA5CCB5_8F0B_4F30_AB4B_4EA286F31C1C
#define DEA5CCB5_8F0B_4F30_AB4B_4EA286F31C1C

#include "cppast/helper/cpp_entity_ptr.h"

#include "cppast/cpp_entities.h"

namespace cppast {

using CppAsmBlockEPtr                  = helper::CppEntityPtr<CppAsmBlock>;
using CppAtomicExprEPtr                = helper::CppEntityPtr<CppAtomicExpr>;
using CppBinomialExprEPtr              = helper::CppEntityPtr<CppBinomialExpr>;
using CppBlobEPtr                      = helper::CppEntityPtr<CppBlob>;
using CppCharLiteralExprEPtr           = helper::CppEntityPtr<CppCharLiteralExpr>;
using CppCompoundEPtr                  = helper::CppEntityPtr<CppCompound>;
using CppConstCastExprEPtr             = helper::CppEntityPtr<CppConstCastExpr>;
using CppConstructorEPtr               = helper::CppEntityPtr<CppConstructor>;
using CppCStyleTypecastExprEPtr        = helper::CppEntityPtr<CppCStyleTypecastExpr>;
using CppDestructorEPtr                = helper::CppEntityPtr<CppDestructor>;
using CppDocumentationCommentEPtr      = helper::CppEntityPtr<CppDocumentationComment>;
using CppDoWhileBlockEPtr              = helper::CppEntityPtr<CppDoWhileBlock>;
using CppDynamiCastExprEPtr            = helper::CppEntityPtr<CppDynamiCastExpr>;
using CppEntityEPtr                    = helper::CppEntityPtr<CppEntity>;
using CppEntityAccessSpecifierEPtr     = helper::CppEntityPtr<CppEntityAccessSpecifier>;
using CppEnumEPtr                      = helper::CppEntityPtr<CppEnum>;
using CppExpressionEPtr                = helper::CppEntityPtr<CppExpression>;
using CppForBlockEPtr                  = helper::CppEntityPtr<CppForBlock>;
using CppForwardClassDeclEPtr          = helper::CppEntityPtr<CppForwardClassDecl>;
using CppFunctionEPtr                  = helper::CppEntityPtr<CppFunction>;
using CppFunctionCallExprEPtr          = helper::CppEntityPtr<CppFunctionCallExpr>;
using CppFunctionPointerEPtr           = helper::CppEntityPtr<CppFunctionPointer>;
using CppFunctionStyleTypecastExprEPtr = helper::CppEntityPtr<CppFunctionStyleTypecastExpr>;
using CppGotoStatementEPtr             = helper::CppEntityPtr<CppGotoStatement>;
using CppIfBlockEPtr                   = helper::CppEntityPtr<CppIfBlock>;
using CppInitializerListExprEPtr       = helper::CppEntityPtr<CppInitializerListExpr>;
using CppLabelEPtr                     = helper::CppEntityPtr<CppLabel>;
using CppLambdaEPtr                    = helper::CppEntityPtr<CppLambda>;
using CppLambdaExprEPtr                = helper::CppEntityPtr<CppLambdaExpr>;
using CppMacroCallEPtr                 = helper::CppEntityPtr<CppMacroCall>;
using CppMonomialExprEPtr              = helper::CppEntityPtr<CppMonomialExpr>;
using CppNameExprEPtr                  = helper::CppEntityPtr<CppNameExpr>;
using CppNamespaceAliasEPtr            = helper::CppEntityPtr<CppNamespaceAlias>;
using CppNumberLiteralExprEPtr         = helper::CppEntityPtr<CppNumberLiteralExpr>;
using CppPreprocessorEPtr              = helper::CppEntityPtr<CppPreprocessor>;
using CppPreprocessorConditionalEPtr   = helper::CppEntityPtr<CppPreprocessorConditional>;
using CppPreprocessorDefineEPtr        = helper::CppEntityPtr<CppPreprocessorDefine>;
using CppPreprocessorErrorEPtr         = helper::CppEntityPtr<CppPreprocessorError>;
using CppPreprocessorImportEPtr        = helper::CppEntityPtr<CppPreprocessorImport>;
using CppPreprocessorIncludeEPtr       = helper::CppEntityPtr<CppPreprocessorInclude>;
using CppPreprocessorPragmaEPtr        = helper::CppEntityPtr<CppPreprocessorPragma>;
using CppPreprocessorUndefEPtr         = helper::CppEntityPtr<CppPreprocessorUndef>;
using CppPreprocessorUnrecognizedEPtr  = helper::CppEntityPtr<CppPreprocessorUnrecognized>;
using CppPreprocessorWarningEPtr       = helper::CppEntityPtr<CppPreprocessorWarning>;
using CppRangeForBlockEPtr             = helper::CppEntityPtr<CppRangeForBlock>;
using CppReinterpretCastExprEPtr       = helper::CppEntityPtr<CppReinterpretCastExpr>;
using CppReturnStatementEPtr           = helper::CppEntityPtr<CppReturnStatement>;
using CppStaticCastExprEPtr            = helper::CppEntityPtr<CppStaticCastExpr>;
using CppStringLiteralExprEPtr         = helper::CppEntityPtr<CppStringLiteralExpr>;
using CppSwitchBlockEPtr               = helper::CppEntityPtr<CppSwitchBlock>;
using CppThrowStatementEPtr            = helper::CppEntityPtr<CppThrowStatement>;
using CppTrinomialExprEPtr             = helper::CppEntityPtr<CppTrinomialExpr>;
using CppTryBlockEPtr                  = helper::CppEntityPtr<CppTryBlock>;
using CppTypecastExprEPtr              = helper::CppEntityPtr<CppTypecastExpr>;
using CppTypeConverterEPtr             = helper::CppEntityPtr<CppTypeConverter>;
using CppTypedefListEPtr               = helper::CppEntityPtr<CppTypedefList>;
using CppTypedefNameEPtr               = helper::CppEntityPtr<CppTypedefName>;
using CppUniformInitializerExprEPtr    = helper::CppEntityPtr<CppUniformInitializerExpr>;
using CppUsingDeclEPtr                 = helper::CppEntityPtr<CppUsingDecl>;
using CppUsingNamespaceDeclEPtr        = helper::CppEntityPtr<CppUsingNamespaceDecl>;
using CppVarEPtr                       = helper::CppEntityPtr<CppVar>;
using CppVarDeclInListEPtr             = helper::CppEntityPtr<CppVarDeclInList>;
using CppVarListEPtr                   = helper::CppEntityPtr<CppVarList>;
using CppVarTypeEPtr                   = helper::CppEntityPtr<CppVarType>;
using CppVartypeExprEPtr               = helper::CppEntityPtr<CppVartypeExpr>;
using CppWhileBlockEPtr                = helper::CppEntityPtr<CppWhileBlock>;

using CppConstAsmBlockEPtr                  = helper::CppEntityPtr<const CppAsmBlock>;
using CppConstAtomicExprEPtr                = helper::CppEntityPtr<const CppAtomicExpr>;
using CppConstBinomialExprEPtr              = helper::CppEntityPtr<const CppBinomialExpr>;
using CppConstBlobEPtr                      = helper::CppEntityPtr<const CppBlob>;
using CppConstCharLiteralExprEPtr           = helper::CppEntityPtr<const CppCharLiteralExpr>;
using CppConstCompoundEPtr                  = helper::CppEntityPtr<const CppCompound>;
using CppConstConstCastExprEPtr             = helper::CppEntityPtr<const CppConstCastExpr>;
using CppConstConstructorEPtr               = helper::CppEntityPtr<const CppConstructor>;
using CppConstCStyleTypecastExprEPtr        = helper::CppEntityPtr<const CppCStyleTypecastExpr>;
using CppConstDestructorEPtr                = helper::CppEntityPtr<const CppDestructor>;
using CppConstDocumentationCommentEPtr      = helper::CppEntityPtr<const CppDocumentationComment>;
using CppConstDoWhileBlockEPtr              = helper::CppEntityPtr<const CppDoWhileBlock>;
using CppConstDynamiCastExprEPtr            = helper::CppEntityPtr<const CppDynamiCastExpr>;
using CppConstEntityEPtr                    = helper::CppEntityPtr<const CppEntity>;
using CppConstEntityAccessSpecifierEPtr     = helper::CppEntityPtr<const CppEntityAccessSpecifier>;
using CppConstEnumEPtr                      = helper::CppEntityPtr<const CppEnum>;
using CppConstExpressionEPtr                = helper::CppEntityPtr<const CppExpression>;
using CppConstForBlockEPtr                  = helper::CppEntityPtr<const CppForBlock>;
using CppConstForwardClassDeclEPtr          = helper::CppEntityPtr<const CppForwardClassDecl>;
using CppConstFunctionEPtr                  = helper::CppEntityPtr<const CppFunction>;
using CppConstFunctionCallExprEPtr          = helper::CppEntityPtr<const CppFunctionCallExpr>;
using CppConstFunctionPointerEPtr           = helper::CppEntityPtr<const CppFunctionPointer>;
using CppConstFunctionStyleTypecastExprEPtr = helper::CppEntityPtr<const CppFunctionStyleTypecastExpr>;
using CppConstGotoStatementEPtr             = helper::CppEntityPtr<const CppGotoStatement>;
using CppConstIfBlockEPtr                   = helper::CppEntityPtr<const CppIfBlock>;
using CppConstInitializerListExprEPtr       = helper::CppEntityPtr<const CppInitializerListExpr>;
using CppConstLabelEPtr                     = helper::CppEntityPtr<const CppLabel>;
using CppConstLambdaEPtr                    = helper::CppEntityPtr<const CppLambda>;
using CppConstLambdaExprEPtr                = helper::CppEntityPtr<const CppLambdaExpr>;
using CppConstMacroCallEPtr                 = helper::CppEntityPtr<const CppMacroCall>;
using CppConstMonomialExprEPtr              = helper::CppEntityPtr<const CppMonomialExpr>;
using CppConstNameExprEPtr                  = helper::CppEntityPtr<const CppNameExpr>;
using CppConstNamespaceAliasEPtr            = helper::CppEntityPtr<const CppNamespaceAlias>;
using CppConstNumberLiteralExprEPtr         = helper::CppEntityPtr<const CppNumberLiteralExpr>;
using CppConstPreprocessorEPtr              = helper::CppEntityPtr<const CppPreprocessor>;
using CppConstPreprocessorConditionalEPtr   = helper::CppEntityPtr<const CppPreprocessorConditional>;
using CppConstPreprocessorDefineEPtr        = helper::CppEntityPtr<const CppPreprocessorDefine>;
using CppConstPreprocessorErrorEPtr         = helper::CppEntityPtr<const CppPreprocessorError>;
using CppConstPreprocessorImportEPtr        = helper::CppEntityPtr<const CppPreprocessorImport>;
using CppConstPreprocessorIncludeEPtr       = helper::CppEntityPtr<const CppPreprocessorInclude>;
using CppConstPreprocessorPragmaEPtr        = helper::CppEntityPtr<const CppPreprocessorPragma>;
using CppConstPreprocessorUndefEPtr         = helper::CppEntityPtr<const CppPreprocessorUndef>;
using CppConstPreprocessorUnrecognizedEPtr  = helper::CppEntityPtr<const CppPreprocessorUnrecognized>;
using CppConstPreprocessorWarningEPtr       = helper::CppEntityPtr<const CppPreprocessorWarning>;
using CppConstRangeForBlockEPtr             = helper::CppEntityPtr<const CppRangeForBlock>;
using CppConstReinterpretCastExprEPtr       = helper::CppEntityPtr<const CppReinterpretCastExpr>;
using CppConstReturnStatementEPtr           = helper::CppEntityPtr<const CppReturnStatement>;
using CppConstStaticCastExprEPtr            = helper::CppEntityPtr<const CppStaticCastExpr>;
using CppConstStringLiteralExprEPtr         = helper::CppEntityPtr<const CppStringLiteralExpr>;
using CppConstSwitchBlockEPtr               = helper::CppEntityPtr<const CppSwitchBlock>;
using CppConstThrowStatementEPtr            = helper::CppEntityPtr<const CppThrowStatement>;
using CppConstTrinomialExprEPtr             = helper::CppEntityPtr<const CppTrinomialExpr>;
using CppConstTryBlockEPtr                  = helper::CppEntityPtr<const CppTryBlock>;
using CppConstTypecastExprEPtr              = helper::CppEntityPtr<const CppTypecastExpr>;
using CppConstTypeConverterEPtr             = helper::CppEntityPtr<const CppTypeConverter>;
using CppConstTypedefListEPtr               = helper::CppEntityPtr<const CppTypedefList>;
using CppConstTypedefNameEPtr               = helper::CppEntityPtr<const CppTypedefName>;
using CppConstUniformInitializerExprEPtr    = helper::CppEntityPtr<const CppUniformInitializerExpr>;
using CppConstUsingDeclEPtr                 = helper::CppEntityPtr<const CppUsingDecl>;
using CppConstUsingNamespaceDeclEPtr        = helper::CppEntityPtr<const CppUsingNamespaceDecl>;
using CppConstVarEPtr                       = helper::CppEntityPtr<const CppVar>;
using CppConstVarDeclInListEPtr             = helper::CppEntityPtr<const CppVarDeclInList>;
using CppConstVarListEPtr                   = helper::CppEntityPtr<const CppVarList>;
using CppConstVarTypeEPtr                   = helper::CppEntityPtr<const CppVarType>;
using CppConstVartypeExprEPtr               = helper::CppEntityPtr<const CppVartypeExpr>;
using CppConstWhileBlockEPtr                = helper::CppEntityPtr<const CppWhileBlock>;

} // namespace cppast

#endif /* DEA5CCB5_8F0B_4F30_AB4B_4EA286F31C1C */
