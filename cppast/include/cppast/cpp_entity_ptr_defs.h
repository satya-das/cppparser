// Copyright (C) 2022 Satya Das and CppParser contributors
// SPDX-License-Identifier: MIT

#ifndef DEA5CCB5_8F0B_4F30_AB4B_4EA286F31C1C
#define DEA5CCB5_8F0B_4F30_AB4B_4EA286F31C1C

#include "cppast/helper/cpp_entity_ptr.h"

#include "cppast/cpp_entities.h"

namespace cppast {

using CppAsmBlockEPtr                 = helper::CppEntityPtr<CppAsmBlock>;
using CppBlobEPtr                     = helper::CppEntityPtr<CppBlob>;
using CppCompoundEPtr                 = helper::CppEntityPtr<CppCompound>;
using CppConstructorEPtr              = helper::CppEntityPtr<CppConstructor>;
using CppDestructorEPtr               = helper::CppEntityPtr<CppDestructor>;
using CppDocumentationCommentEPtr     = helper::CppEntityPtr<CppDocumentationComment>;
using CppDoWhileBlockEPtr             = helper::CppEntityPtr<CppDoWhileBlock>;
using CppEntityAccessSpecifierEPtr    = helper::CppEntityPtr<CppEntityAccessSpecifier>;
using CppEnumEPtr                     = helper::CppEntityPtr<CppEnum>;
using CppExprEPtr                     = helper::CppEntityPtr<CppExpression>;
using CppForBlockEPtr                 = helper::CppEntityPtr<CppForBlock>;
using CppForwardClassDeclEPtr         = helper::CppEntityPtr<CppForwardClassDecl>;
using CppFuncCtorBaseEPtr             = helper::CppEntityPtr<CppFuncCtorBase>;
using CppFuncLikeBaseEPtr             = helper::CppEntityPtr<CppFuncLikeBase>;
using CppFunctionEPtr                 = helper::CppEntityPtr<CppFunction>;
using CppFunctionBaseEPtr             = helper::CppEntityPtr<CppFunctionBase>;
using CppFunctionPointerEPtr          = helper::CppEntityPtr<CppFunctionPointer>;
using CppGotoStatementEPtr            = helper::CppEntityPtr<CppGotoStatement>;
using CppIfBlockEPtr                  = helper::CppEntityPtr<CppIfBlock>;
using CppLabelEPtr                    = helper::CppEntityPtr<CppLabel>;
using CppLambdaEPtr                   = helper::CppEntityPtr<CppLambda>;
using CppMacroCallEPtr                = helper::CppEntityPtr<CppMacroCall>;
using CppMacroDefinitionEPtr          = helper::CppEntityPtr<CppMacroDefinition>;
using CppNamespaceAliasEPtr           = helper::CppEntityPtr<CppNamespaceAlias>;
using CppPreprocessorConditionalEPtr  = helper::CppEntityPtr<CppPreprocessorConditional>;
using CppPreprocessorErrorEPtr        = helper::CppEntityPtr<CppPreprocessorError>;
using CppPreprocessorImportEPtr       = helper::CppEntityPtr<CppPreprocessorImport>;
using CppPreprocessorIncludeEPtr      = helper::CppEntityPtr<CppPreprocessorInclude>;
using CppPreprocessorPragmaEPtr       = helper::CppEntityPtr<CppPreprocessorPragma>;
using CppPreprocessorUndefEPtr        = helper::CppEntityPtr<CppPreprocessorUndef>;
using CppPreprocessorUnrecognizedEPtr = helper::CppEntityPtr<CppPreprocessorUnrecognized>;
using CppPreprocessorWarningEPtr      = helper::CppEntityPtr<CppPreprocessorWarning>;
using CppRangeForBlockEPtr            = helper::CppEntityPtr<CppRangeForBlock>;
using CppReturnStatementEPtr          = helper::CppEntityPtr<CppReturnStatement>;
using CppSwitchBlockEPtr              = helper::CppEntityPtr<CppSwitchBlock>;
using CppThrowStatementEPtr           = helper::CppEntityPtr<CppThrowStatement>;
using CppTryBlockEPtr                 = helper::CppEntityPtr<CppTryBlock>;
using CppTypeConverterEPtr            = helper::CppEntityPtr<CppTypeConverter>;
using CppTypedefListEPtr              = helper::CppEntityPtr<CppTypedefList>;
using CppTypedefNameEPtr              = helper::CppEntityPtr<CppTypedefName>;
using CppUsingDeclEPtr                = helper::CppEntityPtr<CppUsingDecl>;
using CppUsingNamespaceDeclEPtr       = helper::CppEntityPtr<CppUsingNamespaceDecl>;
using CppVarEPtr                      = helper::CppEntityPtr<CppVar>;
using CppVarDeclInListEPtr            = helper::CppEntityPtr<CppVarDeclInList>;
using CppVarListEPtr                  = helper::CppEntityPtr<CppVarList>;
using CppVarTypeEPtr                  = helper::CppEntityPtr<CppVarType>;
using CppWhileBlockEPtr               = helper::CppEntityPtr<CppWhileBlock>;

using CppConstAsmBlockEPtr                 = helper::CppEntityPtr<const CppAsmBlock>;
using CppConstBlobEPtr                     = helper::CppEntityPtr<const CppBlob>;
using CppConstCompoundEPtr                 = helper::CppEntityPtr<const CppCompound>;
using CppConstConstructorEPtr              = helper::CppEntityPtr<const CppConstructor>;
using CppConstDestructorEPtr               = helper::CppEntityPtr<const CppDestructor>;
using CppConstDocumentationCommentEPtr     = helper::CppEntityPtr<const CppDocumentationComment>;
using CppConstDoWhileBlockEPtr             = helper::CppEntityPtr<const CppDoWhileBlock>;
using CppConstCppEntityAccessSpecifierEPtr = helper::CppEntityPtr<const CppEntityAccessSpecifier>;
using CppConstEnumEPtr                     = helper::CppEntityPtr<const CppEnum>;
using CppConstExprEPtr                     = helper::CppEntityPtr<const CppExpression>;
using CppConstForBlockEPtr                 = helper::CppEntityPtr<const CppForBlock>;
using CppConstForwardClassDeclEPtr         = helper::CppEntityPtr<const CppForwardClassDecl>;
using CppConstFuncCtorBaseEPtr             = helper::CppEntityPtr<const CppFuncCtorBase>;
using CppConstFuncLikeBaseEPtr             = helper::CppEntityPtr<const CppFuncLikeBase>;
using CppConstFunctionEPtr                 = helper::CppEntityPtr<const CppFunction>;
using CppConstFunctionBaseEPtr             = helper::CppEntityPtr<const CppFunctionBase>;
using CppConstFunctionPointerEPtr          = helper::CppEntityPtr<const CppFunctionPointer>;
using CppConstIfBlockEPtr                  = helper::CppEntityPtr<const CppIfBlock>;
using CppConstLabelEPtr                    = helper::CppEntityPtr<const CppLabel>;
using CppConstLambdaEPtr                   = helper::CppEntityPtr<const CppLambda>;
using CppConstMacroCallEPtr                = helper::CppEntityPtr<const CppMacroCall>;
using CppConstMacroDefinitionEPtr          = helper::CppEntityPtr<const CppMacroDefinition>;
using CppConstNamespaceAliasEPtr           = helper::CppEntityPtr<const CppNamespaceAlias>;
using CppConstPreprocessorConditionalEPtr  = helper::CppEntityPtr<const CppPreprocessorConditional>;
using CppConstPreprocessorErrorEPtr        = helper::CppEntityPtr<const CppPreprocessorError>;
using CppConstPreprocessorImportEPtr       = helper::CppEntityPtr<const CppPreprocessorImport>;
using CppConstPreprocessorIncludeEPtr      = helper::CppEntityPtr<const CppPreprocessorInclude>;
using CppConstPreprocessorPragmaEPtr       = helper::CppEntityPtr<const CppPreprocessorPragma>;
using CppConstPreprocessorUndefEPtr        = helper::CppEntityPtr<const CppPreprocessorUndef>;
using CppConstPreprocessorUnrecognizedEPtr = helper::CppEntityPtr<const CppPreprocessorUnrecognized>;
using CppConstPreprocessorWarningEPtr      = helper::CppEntityPtr<const CppPreprocessorWarning>;
using CppConstRangeForBlockEPtr            = helper::CppEntityPtr<const CppRangeForBlock>;
using CppConstSwitchBlockEPtr              = helper::CppEntityPtr<const CppSwitchBlock>;
using CppConstTryBlockEPtr                 = helper::CppEntityPtr<const CppTryBlock>;
using CppConstTypeConverterEPtr            = helper::CppEntityPtr<const CppTypeConverter>;
using CppConstTypedefListEPtr              = helper::CppEntityPtr<const CppTypedefList>;
using CppConstTypedefNameEPtr              = helper::CppEntityPtr<const CppTypedefName>;
using CppConstUsingDeclEPtr                = helper::CppEntityPtr<const CppUsingDecl>;
using CppConstUsingNamespaceDeclEPtr       = helper::CppEntityPtr<const CppUsingNamespaceDecl>;
using CppConstVarEPtr                      = helper::CppEntityPtr<const CppVar>;
using CppConstVarDeclInListEPtr            = helper::CppEntityPtr<const CppVarDeclInList>;
using CppConstVarListEPtr                  = helper::CppEntityPtr<const CppVarList>;
using CppConstVarTypeEPtr                  = helper::CppEntityPtr<const CppVarType>;
using CppConstWhileBlockEPtr               = helper::CppEntityPtr<const CppWhileBlock>;

} // namespace cppast

#endif /* DEA5CCB5_8F0B_4F30_AB4B_4EA286F31C1C */
