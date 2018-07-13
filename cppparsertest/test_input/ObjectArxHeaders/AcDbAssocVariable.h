//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// CREATED BY: Jiri Kripac                                 April 2007
//
// DESCRIPTION:
//
// AcDbAssocVariable concrete action class. 
//
// Also declaration of AcDbAssocVariableValueProviderPE protocol extension
// class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocValueProviderPE.h"
#include "AcDbAssocAction.h"
#pragma pack (push, 8)


ACDBCORE2D_PORT AcString& dummyString();

/// <summary> <para>
/// AcDbAssocVariable keeps a name, value and expression. The name is an arbitrary
/// non-empty string but the client code sets rules that define valid variable names. 
/// </para> <para>
/// The expression is optional and is in the form of a string. An evaluator
/// id needs to be provided with each espression. It specifies which expression 
/// evaluator should be used to parse the expression. The expression can reference 
/// other objects that provide values, such as it can reference other variables. 
/// The AcDbAssocVariable then owns AcDbAssocValueDependencies on these referenced 
/// objects. If the expression string is empty, or if the expression string does 
/// not reference other objects, the variable is a constant.
/// </para> <para>
/// The variable value is a scalar value such as a double, int, point, or a string.
/// Currently only these four value types are supported.
/// </para> <para>
/// AcDbAssocVariable exposes AcDbAssocVariableValueProviderPE protocol extension 
/// that is used by other variables and generally by other actions that own 
/// AcDbAssocValueDependencies to obtain the value of the variable.
/// </para> <para>
/// The evaluate() method of the variable evaluates the expression using the
/// current values of the referenced symbols and sets the evaluated value.
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocVariable : public AcDbAssocAction
{
public:     
    ACRX_DECLARE_MEMBERS(AcDbAssocVariable);


    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocVariable(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> Returns the variable name which is an arbitrary string. </summary>
    /// <returns> The name of this variable. </returns>
    ///
    const AcString& name() const;

    /// <summary> Returns the  expression or an empty string if the variable is a constant. </summary>
    /// <returns> The expression or an empty string. </returns>
    ///
    const AcString& expression() const;

    const AcString& expression(bool convertSymbolNamesFromCanonicalForm) const;

    /// <summary> Returns the evaluated and cached value of the variable. </summary>
    /// <returns> The value of the variable. </returns>
    ///
    const AcDbEvalVariant& value() const;

    /// <summary> 
    /// Returns description of the variable which is an arbitrary string. It does
    /// not have any additional meaning and does not affect the expression 
    /// evaluation in any way. 
    /// </summary>
    /// <returns> The description or an empty string. </returns>
    ///
    const AcString& description() const;

    /// <summary> <para>
    /// Sets the name of the variable. It does not verify the name. 
    /// </para> <para>
    /// If the updateReferencingExpressions argument is true, it also finds 
    /// all expressions referencing this variable and changes them (changes 
    /// their strings) to reflect the new name of the variable.
    /// </para> </summary>
    /// <param name="newName"> New name of the variable. </param>
    /// <param name="updateReferencingExpressions"> 
    /// If true, it finds all expressions referencing this variable and changes 
    /// them (changes their strings) to reflect the new name of the variable.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setName(const AcString& newName, bool updateReferencingExpressions);

    /// <summary>
    /// Anonymous variable has name that is either empty or starts with "*".
    /// Anonymous variables are not shown in the PARAMETERS manager. They are
    /// used internally when there is a need to keep an expression (such as when
    /// a parameter of an action can be defined by an expression that may reference 
    /// other variables), but there is no need to reference this expression from
    /// any other object besides the "owner" of the expression (such as the action 
    /// whose parameter can be defined by an expression). The "owner" of the
    /// anonymous variable is responsible for its management, such as requesting
    /// it to be cloned when the "owner" is cloned, erasing the anonymous variable
    /// when the "owner" is erased, etc.
    /// </summary>
    /// <returns> Returns true if the variable is anonymous. </returns>
    ///
    bool isAnonymous() const;

    /// <summary> 
    /// Using this AcDbAssocVariable as the starting context, searches for an
    /// object with the given name. The initial implementation just searches 
    /// the AcDbAssocNetwork owning this variable, but later we may add more
    /// sophisticated searches, such as cross-network references, nested-network
    /// references, global references, etc. 
    /// </summary>
    /// <remarks>
    /// Currently the only named objects are AcDbAssocVariables, but there may 
    /// be more object types in the future. We may also in the future promote 
    /// this method to the base AcDbAssocAction class if we find more cases of
    /// named objects.
    /// </remarks>
    /// <param name="objectName"> The name of the searched-for object. </param>
    /// <param name="pObjectClass"> The class of the searched-for object (isKindOf() test is used). </param>
    /// <returns> AcDbObjectId of the found object or null AcDbObjectId if no object found. </returns>
    ///
    AcDbObjectId findObjectByName(const AcString&  objectName, 
                                  const AcRxClass* pObjectClass) const;

    /// <summary> <para>
    /// Validates the given nameToValidate, expressionToValidate or both, to see
    /// whether they can be used as name and/or expression for this variable. 
    /// If either string is empty, it is not validated and is assumed that the
    /// name and/or expression of this variable is not going to change.
    /// </para> <para>
    /// For nameToValidate it checks if it is a valid identifier and checks that 
    /// nameToValidate is not used as name of some other variable in the same 
    /// network as this variable belongs to.
    /// </para> <para>
    /// For expressionToValidate it performs syntactic checks of the expression, 
    /// including checks for references to undefined symbols and for cyclic 
    /// dependencies between symbols, but it does not evaluate the expression.
    /// </para> <para>
    /// If these common checks pass, it calls AcDbAssocVariableCallback::validateNameAndExpression() 
    /// so that the client code can perform additional validation, such as that
    /// a variable name is used as dimensional constraint name in no more than 
    /// one dimensional constraint.
    /// </para> </summary>
    /// <param name="nameToValidate"> The variable name to validate. May be null. </param>
    /// <param name="expressionToValidate"> The variable expression to validate. May be null. </param>
    /// <param name="errorMessage"> Error string if the name or expression is not valid, empty otherwise. </param>
    /// <returns> 
    /// Returns Acad::eOk if the name and/or expression can be set to this variable. 
    /// Otherwise it returns an ErrorStatus and errorMessage that explain the error. 
    /// </returns>
    ///
    Acad::ErrorStatus validateNameAndExpression(const AcString& nameToValidate, 
                                                const AcString& expressionToValidate,
                                                AcString&       errorMessage) const;

    /// <summary> 
    /// Sets the expression (may be an empty string if no expression). 
    /// The expression is syntactically checked but not evaluated.  
    /// </summary>
    /// <param name="newExpression"> New expression or an empty string. </param>
    /// <param name="evaluatorId"> String identifier of expression evaluator. 
    /// If empty, the default evaluator for current acad version will be used. 
    /// </param>
    /// <param name="checkForCyclicalDependencies"> 
    /// Checks that this variable is not referenced, either directly or indirectly,
    /// by the new expression. If it is referenced, it means there is a cyclical
    /// dependency between the variables.
    /// </param>
    /// <param name="updateDependenciesOnReferencedSymbols">  
    /// If true, it erases all existing AcDbAssocValueDependencies on the 
    /// symbols referenced by the previous expression and sets up new 
    /// AcDbAssocValueDependencies on the symbols referenced by the new 
    /// expression.
    /// <param name="errorMessage"> Error string if expression is syntactically invalid. </param>
    /// </param>
    /// <param name="silentMode"> Does not print a message when the expression is invalid. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///

    Acad::ErrorStatus setExpression(const AcString& newExpression, 
                                    const AcString& evaluatorId, 
                                    bool checkForCyclicalDependencies,
                                    bool updateDependenciesOnReferencedSymbols,
                                    AcString& errorMessage = dummyString(),
                                    bool silentMode = false);

    /// <summary> 
    /// Returns id of the expression evaluator that is used to parse the expression. 
    /// </summary>
    /// <returns> Id of the expression evaluator that is used to parse the expression. </returns>
    ///
    const AcString& evaluatorId() const;

    /// <summary> 
    /// Sets id of the expression evaluator that is going to be used to parse 
    /// the expression. An empty string means the default evaluator.
    /// </summary>
    /// <para name="evalId"> Id of the expression evauator. </para>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setEvaluatorId(const AcString& evalId);

    /// <summary>
    /// Sets the evaluated value. Notice that if the expression is not empty,
    /// this value will be overwritten the next time the expression is
    /// evaluated.
    /// </summary> 
    /// <param name="newValue"> New evaluated value. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValue(const AcDbEvalVariant& newValue);

    /// <summary>
    /// Sets description to the variable. Variable description is just an 
    /// optional text that does not affect the expression evaluation in any way.
    /// </summary> 
    /// <param name="newDescription"> New description to be set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setDescription(const AcString& newDescription);

    // These methods are currently intended for internal use only
    //
    bool     isMergeable          () const;
    bool     mustMerge            () const;
    AcString mergeableVariableName() const;
    void setIsMergeable(bool isMerg, bool mustMerg = false, const AcString& mergeableVariableName = AcString());

    /// <summary> <para>
    /// A helper method allowing to evaluate the expression at any time without 
    /// modifying the variable. It is a read-only method.
    /// </para> <para>
    /// Evaluates the expression based on the current values of the referenced
    /// symbols and returns it in evaluatedExpressionValue. If there is no
    /// expression, the stored value is returned. It does not change the stored 
    /// value, neither it changes the status of the variable. 
    /// </para> </summary> 
    /// <param name="evaluatedExpressionValue"> Returned evaluated value of the expression. </param>
    /// <param name="errorMessage"> Error string if expression evaluation has failed. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus evaluateExpression(AcDbEvalVariant& evaluatedExpressionValue,
                                         AcString&        errorMessage = dummyString()) const;

    /// <summary> <para>
    /// A helper method allowing to evaluate the expression at any time without 
    /// modifying the variable and by explicitly providing values of the referenced
    /// objects (variables). It is a read-only method, it does not change the value 
    /// of this or other variables, neither it changes the status of any variables.
    /// </para> <para>
    /// Evaluates the expression based on the provided values of the referenced 
    /// objects. The objectIds array is an array of ids of value-providing objects
    /// (such as AcDbAssocVariables) and objectValues is an array of provided 
    /// values of these objects. These arrays have the same lengths.
    /// </para> <para>
    /// If the id of this variable is already in objectIds array, the corresponding
    /// value from objectValues is returned. Otherwise it evaluates the expression
    /// of this variable. Anytime is comes across a symbol referenced by the 
    /// expression, it checks the objectIds array to see if the value of the object 
    /// is already known. If yes, it uses this value, otherwise expects that the 
    /// object is an AcDbAssocVariable, obtains its value by recursively calling 
    /// this method, and uses the returned value. After the value of a variable has 
    /// been obtained, the variable id and the just obtained value are added to 
    /// objectIds and objectValues arrays, so that if the same variable is encountered
    /// again, its value is used and not evaluated again.
    /// </para> <para>
    /// This method does not change the value of this or any other variable, neither 
    /// it changes the status of any variable. It does however append id-value
    /// pairs to the objectIds and objectValues arrays which are in/out arguments.
    /// </para> </summary> 
    /// <param name="objectIds"> 
    /// Array of ids of value-providing objects. It is an in/out argument. It is
    /// being appended during the evaluation with ids of the value-providing objects 
    /// whose values have been obtained (currently these objects are only 
    /// AcDbAssocVariables).
    /// </param>
    /// <param name="objectValues"> 
    /// Array of values of value-providing objects. It is an in/out argument. It is
    /// being appended during the evaluation with values of the value-providing objects 
    /// whose values have been obtained (currently these objects are only 
    /// AcDbAssocVariables).
    /// </param>
    /// <param name="evaluatedExpressionValue"> Returned evaluated value of the expression. </param>
    /// <param name="errorMessage"> Error string if expression evaluation has failed. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus evaluateExpression(AcDbObjectIdArray&        objectIds,    // in/out argument
                                         AcArray<AcDbEvalVariant>& objectValues, // in/out argument
                                         AcDbEvalVariant&          evaluatedExpressionValue,
                                         AcString&                 errorMessage = dummyString()) const;

    /// <summary>
    /// Evaluates the given expression in the context of the given AcDbAssocNetwork.
    /// </summary>
    static Acad::ErrorStatus evaluateExpression(const AcString&     expression,
                                                const AcString&     evaluatorId,
                                                const AcDbObjectId& networkId, // Provides context for the names
                                                AcDbEvalVariant&    evaluatedExpressionValue,
                                                AcString&           assignedToSymbolName,         
                                                AcString&           errorMessage = dummyString());

    /// <summary>
    /// See the explanation of AcDbAssocVariableCallback. Multiple global callbacks 
    /// can be registered and they apply to all AcDbAssocVariables.
    /// </summary>
    /// <param name="pCallback"> The callback to be registered. </param>
    ///
    static void addGlobalCallback(class AcDbAssocVariableCallback* pCallback);

    /// <summary>
    /// See the explanation of AcDbAssocVariableCallback. Multiple global callbacks 
    /// can be registered and they apply to all AcDbAssocVariables.
    /// </summary>
    /// <param name="pCallback"> The callback to be unregistered. </param>
    ///
    static void removeGlobalCallback(class AcDbAssocVariableCallback* pCallback);

    /// <summary>
    /// Returns a callback that is the collection of all callbacks registered by
    /// client code. This function is meant mostly for private use and there should
    /// not be much need for the client code to use it. Anyway, the client code
    /// must never delete or unregister the returned callback, or do anything with
    /// it except for calling its methods.
    /// </summary>
    /// <returns> 
    /// The global AcDbAssocVariable(Multi)Callback that keeps all the callbacks 
    /// registered by the client code. The returned pointer is never null.
    /// </returns>
    ///
    static class AcDbAssocVariableCallback* globalCallback();

}; // class AcDbAssocVariable


/// <summary>
/// Client code can register callback(s) derived from AcDbAssocVariableCallback 
/// that are then called when some events happen with AcDbAssocVariables. 
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocVariableCallback
{
public:
    AcDbAssocVariableCallback() {}
    virtual ~AcDbAssocVariableCallback() {}

    /// <summary>
    /// Allows client code to veto erasing a variable when the variable would 
    /// be erased because the dimensional constraint that uses the variable is
    /// erased and the variable is no more referenced.
    /// </summary>
    /// <param name="pVariable"> The AcDbAssocVariable that is to be erased. </param>
    /// <returns> 
    /// true == client code allows the variable to be erased. false == client code 
    /// vetoes the variable erase.
    ///</returns>
    ///
    virtual bool canBeErased(const AcDbAssocVariable* pVariable) = 0;

    /// <summary> 
    /// Called from AcDbAssocVariable::validateNameAndExpression(). It lets the 
    /// client code perform additional checks to decide if a given name and/or 
    /// expression are allowed to be used as a name and/or expression for the 
    /// given variable.
    /// </summary>
    /// <param name="pVariable"> The variable whose name and/or expression are being validated. </param>
    /// <param name="nameToValidate"> The variable name to validate. May be null. </param>
    /// <param name="expressionToValidate"> The variable expression to validate. May be null. </param>
    /// <param name="errorMessage"> Error string if the name or expression is not valid, empty otherwise. </param>
    /// <returns> 
    /// Returns Acad::eOk if the name and/or expression can be set to this variable. 
    /// Otherwise it returns an ErrorStatus and errorMessage that explain the error. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus validateNameAndExpression(const AcDbAssocVariable* pVariable,
                                                        const AcString&          nameToValidate, 
                                                        const AcString&          expressionToValidate,
                                                        AcString&                errorMessage) = 0;
};

#pragma pack (pop)


ACDBCORE2D_PORT void stringDefaultArgumentTest(AcString& str = dummyString());
