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
// CREATED BY: Jiri Kripac                                 August 2007
//
// DESCRIPTION:
//
// AcDbAssocActionBody abstract base class for deriving custom action body
// classes.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocAction.h"
#include "dbEval.h"
#include "AcValue.h"
#pragma pack (push, 8)


/// <summary> <para>
/// Abstract base class for deriving custom action body classes that implement
/// functionality of custom actions.
/// </para> <para>
/// An object of a class derived from the AcDbAssocActionBody class is always 
/// owned by a parent AcDbAssocAction object. The AcDbAssocAction object has 
/// an AcDbHardOwnershipId on it and the AcDbAssocActionBody::ownerId() of the 
/// object returns the AcDbObjectId of its parent AcDbAssocAction object. 
/// </para> <para>
/// Therefore a custom action object (in the logical sense of the word "object") 
/// is always represented by a pair of physical AcDbObjects: 
///
///  - The parent action object of the AcDbAssocAction class (or possibly, but
///    less commonly, of a derived class).
///  - The action body object of a custom class derived from the 
///    AcDbAssocActionBody abstract base class.
///
/// </para> <para>
/// This factoring out of the functionality of the custom actions into separate 
/// classes derived from the AcDbAssocActionBody class, instead of deriving the 
/// custom action classes directly from the AcDbAssocAction class, allows
/// better handling of the situations when the application code that implements 
/// the custom action behavior is not available. Only the custom object of the
/// AcDbAssocActionBody-derived class will become a proxy, but its parent 
/// AcDbAssocAction object will always be available and the associative mechanism
/// can still function to some extent.
/// </para> <para>
/// The abstract AcDbAssocActionBody base class defines a set of virtual methods 
/// named xxxxxxOverride() that correspond to methods named xxxxxx() in the parent
/// AcDbAssocAction class. When a method xxxxxx() is called on the parent action 
/// object and the action object owns an action body object, the corresponding 
/// xxxxxxOverride() method on the action body object is called and it either 
/// supersedes or amends the default xxxxxx() implementation, depending on the 
/// particular method. 
/// </para> <para>
/// If the action object does not own an action body object or if the action 
/// body object does not override the xxxxxxOverride() method, the default
/// implementation in the parent action object is performed. Also, when the 
/// custom action body object becomes a proxy because its application code
/// is not available, the parent action method just performs its default 
/// implementation.
/// </para> <para>
/// Custom action body classes derived from the AcDbAssocActionBody class 
/// implement their behavior by overriding the appropriate xxxxxxOverride() 
/// methods. Only the evaluateOverride() method must always be overridden in 
/// the custom classes. If not overridden, the other xxxxxxOverride() methods 
/// will do nothing and the default implementation in the parent AcDbAssocAction 
/// object will be performed. This may be the appropriate behavior in most cases.
/// </para> <para>
/// The custom action body classes also need to serialize their data. When 
/// serializing AcDbObjectIds of the AcDbAssocDependencies, these should be 
/// serialized as AcDbHardPointerIds, not as AcDbHardOwnershipIds, because the 
/// AcDbAssocDependencies are owned (in the AutoCAD database sense) by the 
/// parent AcDbAssocAction object, not by the custom action body object. 
/// </para> <para>
/// Because each AcDbAssocActionBody object is owned by its parent 
/// AcDbAssocAction object, erasing the parent AcDbAssocAction object also 
/// erases the owned AcDbAssocActionBody object. There is no need to erase
/// AcDbAssocActionBody objects explicitly.
/// </para> </summary> 
///
class ACDBCORE2D_PORT AcDbAssocActionBody : public AcDbObject
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocActionBody);

    explicit AcDbAssocActionBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);
    virtual ~AcDbAssocActionBody();

    /// <summary>
    /// Returns AcDbObjectId of the parent AcDbAssocAction that owns this 
    /// action body object.
    /// </summary>
    ///
    AcDbObjectId parentAction() const { return ownerId(); }

    /// <summary>
    /// Returns AcDbObjectId of the parent AcDbAssocAction that owns the given  
    /// action body object.
    /// </summary>
    ///
    static AcDbObjectId parentAction(const AcDbObjectId& actionBodyId);

    // The following non-virtual methods are just shortcuts that just forward 
    // to the parent AcDbAssocAction class, to save some typing for the
    // implementers of the derived custom action body classes

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbAssocStatus status() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus setStatus(AcDbAssocStatus newStatus, 
                                bool            notifyOwningNetwork = true,
                                bool            setInOwnedActions   = false) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbObjectId owningNetwork() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus getDependencies(bool readDependenciesWanted, 
                                      bool writeDependenciesWanted,
                                      AcDbObjectIdArray& dependencyIds) const; 

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus addDependency(const AcDbObjectId& dependencyId, 
                                    bool                setThisActionAsOwningAction = true) const; 

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus addDependency(AcRxClass*    pDependencyClass,
                                    AcRxClass*    pDependencyBodyClass,
                                    bool          isReadDep,
                                    bool          isWriteDep,
                                    int           order,
                                    AcDbObjectId& dependencyId) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus removeDependency(const AcDbObjectId& dependencyId, 
                                       bool                alsoEraseIt) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus removeAllDependencies(bool alsoEraseThem) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus evaluateDependencies() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    bool isActionEvaluationInProgress() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbAssocEvaluationCallback* currentEvaluationCallback() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus removeAllParams(bool alsoEraseThem) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    int paramCount() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    const AcDbObjectIdArray& ownedParams() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus addParam(const AcDbObjectId& paramId, int& paramIndex) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus addParam(const AcString& paramName, AcRxClass* pParamClass, AcDbObjectId& paramId, int& paramIndex) const; 

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus removeParam(const AcDbObjectId& paramId, bool alsoEraseIt) const; 

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    const AcDbObjectIdArray& paramsAtName(const AcString& paramName) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbObjectId paramAtName(const AcString& paramName, int index = 0) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcDbObjectId paramAtIndex(int paramIndex) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    void ownedValueParamNames(AcArray<AcString>& paramNames) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus getValueParamArray(const AcString&           paramName,
                                         AcArray<AcDbEvalVariant>& values,
                                         AcArray<AcString>&        expressions, 
                                         AcArray<AcString>&        evaluatorIds) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus getValueParam(const AcString&  paramName,
                                    AcDbEvalVariant& value,
                                    AcString&        expression, 
                                    AcString&        evaluatorId, 
                                    int              valueIndex = 0) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus setValueParamArray(const AcString&                 paramName,
                                         const AcArray<AcDbEvalVariant>& values,
                                         const AcArray<AcString>&        expressions,
                                         const AcArray<AcString>&        evaluatorIds,
                                         AcArray<AcString>&              errorMessages,
                                         bool                            silentMode) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus setValueParam(const AcString&        paramName,
                                    const AcDbEvalVariant& value,
                                    const AcString&        expression,
                                    const AcString&        evaluatorId,
                                    AcString&              errorMessage,
                                    bool                   silentMode,
                                    int                    valueIndex = 0) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    AcValue::UnitType valueParamUnitType(const AcString& paramName) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus setValueParamUnitType(const AcString& paramName, AcValue::UnitType unitType) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus removeValueParam(const AcString& paramName) const; 

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus valueParamInputVariables(const AcString& paramName, AcDbObjectIdArray& variableIds) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus setValueParamControlledObjectDep(const AcString& paramName, const AcDbObjectId& controlledObjectDepId) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus updateValueParamControlledObject(const AcString& paramName) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus updateValueParamFromControlledObject(const AcString& paramName) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus updateAllObjectsControlledByValueParams() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus transformAllConstantGeometryParams(const AcGeMatrix3d& transform) const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocAction that 
    /// owns this action body object.
    /// </summary>
    ///
    Acad::ErrorStatus scaleAllDistanceValueParams(double scaleFactor) const;

    /// <summary>
    /// Utility function that returns true if the action owns any dependency whose
    /// status is kErasedAssocStatus or whose dependent-on object cannot be
    /// opened. AcDbAssocValueDependencies are ignored.
    /// </summary>
    ///
    bool hasAnyErasedOrBrokenDependencies() const;

    /// <summary> <para>
    /// Utility function that creates AcDbAssocAction and AcDbAssocActionBody
    /// of the required class, makes the action own the action body and posts 
    /// both to the database of the given objectId. 
    /// </para> <para>
    /// It uses the objectId to find the network to add the newly created action
    /// to. If the objectId is of an AcDbAssocNetwork, this network is used.
    /// If the objectId is of an AcDbBlockTableRecord or of an entity owned by 
    /// a AcDbBlockTableRecord, adds the newly created action to the network of 
    /// the AcDbBlockTableRecord.
    /// </para> </summary>
    ///
    static Acad::ErrorStatus createActionAndActionBodyAndPostToDatabase(
        AcRxClass*          pActionBodyClass,
        const AcDbObjectId& objectId,
        AcDbObjectId&       createdActionId,
        AcDbObjectId&       createdActionBodyId);

    /// <summary>
    /// Utility static method that returns all action bodies of all actions that 
    /// have the requested type of dependencies on the given object. Notice that
    /// There may be no more than a single action that has a write-only dependency 
    /// on the object, that is why the pWriteOnlyActionBodyId is a pointer to a 
    /// single AcDbObjectId, not to an AcDbObjectIdArray. If any of the pointers
    /// are NULL, the type of action bodies are not returned.
    /// </summary>
    ///
    static Acad::ErrorStatus getActionBodiesOnObject(const AcDbObject*  pObject,
                                                     bool               ignoreInternalActions,
                                                     bool               ignoreSuppressedActions,
                                                     AcDbObjectId*      pWriteOnlyActionBodyId,
                                                     AcDbObjectIdArray* pReadWriteActionBodyIds,
                                                     AcDbObjectIdArray* pReadOnlyActionBodyIds = NULL);

public: 
    
    // Virtual methods that can be overridden by the derived classes

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. This method has to be overridden and
    /// this is how the behavior of custom actions is implemented.
    /// </summary>
    ///
    virtual void evaluateOverride() = 0;

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus getDependenciesOverride(bool readDependenciesWanted, 
                                                      bool writeDependenciesWanted,
                                                      AcDbObjectIdArray& dependencyIds) const
    { 
        ADESK_UNREFED_PARAM(readDependenciesWanted);
        ADESK_UNREFED_PARAM(writeDependenciesWanted);
        ADESK_UNREFED_PARAM(dependencyIds);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus getDependentObjectsOverride(bool readDependenciesWanted,
                                                          bool writeDependenciesWanted,
                                                          AcDbObjectIdArray& objectIds) const
    {
        ADESK_UNREFED_PARAM(readDependenciesWanted);
        ADESK_UNREFED_PARAM(writeDependenciesWanted);
        ADESK_UNREFED_PARAM(objectIds);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus removeAllDependenciesOverride(bool alsoEraseThem)
    { 
        ADESK_UNREFED_PARAM(alsoEraseThem);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isOwnedDependencyOverride(const AcDbAssocDependency* pDependency, 
                                                        bool& isOwnedDependency) const
    { 
        ADESK_UNREFED_PARAM(pDependency);
        ADESK_UNREFED_PARAM(isOwnedDependency);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isExternalDependencyOverride(const AcDbAssocDependency* pDependency, 
                                                           bool& isExternalDependency) const
    { 
        ADESK_UNREFED_PARAM(pDependency);
        ADESK_UNREFED_PARAM(isExternalDependency);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus hasDependencyCachedValueOverride(const AcDbAssocDependency* pDependency,
                                                               bool& hasDepCachedValue) const
    { 
        ADESK_UNREFED_PARAM(pDependency);
        ADESK_UNREFED_PARAM(hasDepCachedValue);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isRelevantDependencyChangeOverride(const AcDbAssocDependency* pDependency,
                                                                 bool& isRelevantDepChange) const
    { 
        ADESK_UNREFED_PARAM(pDependency);
        ADESK_UNREFED_PARAM(isRelevantDepChange);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus areDependenciesOnTheSameThingOverride(const AcDbAssocDependency* pDependency1,
                                                                    const AcDbAssocDependency* pDependency2,
                                                                    bool& areDependentOnSameThing) const
    { 
        ADESK_UNREFED_PARAM(pDependency1);
        ADESK_UNREFED_PARAM(pDependency2);
        ADESK_UNREFED_PARAM(areDependentOnSameThing);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus areDependenciesEqualOverride(const AcDbAssocDependency* pDependency1,
                                                           const AcDbAssocDependency* pDependency2,
                                                           bool& areEqual) const
    {
        ADESK_UNREFED_PARAM(pDependency1);
        ADESK_UNREFED_PARAM(pDependency2);
        ADESK_UNREFED_PARAM(areEqual);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluateDependencyOverride(AcDbAssocDependency* pDependency)
    {
        ADESK_UNREFED_PARAM(pDependency);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus dependentObjectClonedOverride(const AcDbAssocDependency* pDependency, 
                                                            const AcDbObject*          pDbObj, 
                                                            const AcDbObject*          pNewObj)
    { 
        ADESK_UNREFED_PARAM(pDependency);
        ADESK_UNREFED_PARAM(pDbObj);
        ADESK_UNREFED_PARAM(pNewObj);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus addMoreObjectsToDeepCloneOverride(AcDbIdMapping& /*idMap*/, 
                                                                AcDbObjectIdArray& /*additionalObjectsToClone*/) const
    { 
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus postProcessAfterDeepCloneOverride(AcDbIdMapping& /*idMap*/) 
    { 
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus postProcessAfterDeepCloneCancelOverride(AcDbIdMapping& /*idMap*/)
    { 
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus ownedDependencyStatusChangedOverride(AcDbAssocDependency* pOwnedDependency, 
                                                                   AcDbAssocStatus      previousStatus)
    { 
        ADESK_UNREFED_PARAM(pOwnedDependency);
        ADESK_UNREFED_PARAM(previousStatus);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isEqualToOverride(const AcDbAssocAction* pOtherAction, bool& isEqual) const
    {
        ADESK_UNREFED_PARAM(pOtherAction);
        ADESK_UNREFED_PARAM(isEqual);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus evaluationPriorityOverride(AcDbAssocEvaluationPriority& priority) const
    {
        ADESK_UNREFED_PARAM(priority);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus getDependentActionsToEvaluateOverride(AcDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const
    {
        ADESK_UNREFED_PARAM(pActionsToEvaluateCallback);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus transformActionByOverride(const AcGeMatrix3d&)
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocAction class 
    /// that owns this action body object. It does not need to be overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus dragStatusOverride(const AcDb::DragStat status)
    {
        ADESK_UNREFED_PARAM(status);
        return Acad::eNotImplemented; 
    }

    /// <summary><para>
    /// This method may be overridden in derived action body clases.
    /// </para><para>    
    /// The AcDbAssocAction::removeActionsControllingObject() method notifies all
    /// action bodies that have a write-dependency on the controlled object by 
    /// calling this method. The individual action bodies then can do some work 
    /// before they are detached from the controlled object, or can even not let 
    /// themselves be detached. 
    /// </para><para>    
    /// It this method returns Acad::eOk, AcDbAssocAction::removeActionsControllingObject() 
    /// will not detach the action from the controlled object, expecting the 
    /// action body to do it by itself. If not overridden, this method returns 
    /// Acad::eNotImplemented, indicating that AcDbAssocAction::removeActionsControllingObject() 
    /// should detach the action from the controlled object.
    /// </para></summary>
    /// <param name="pControlledObject">
    /// An AcDbObject for which AcDbAssocAction::removeActionsControllingObject()
    /// is being called. This action body has a write-dependency on this object.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus removeActionsControllingObjectOverride(AcDbObject* pControlledObject)
    {
        ADESK_UNREFED_PARAM(pControlledObject);
        return Acad::eNotImplemented;
    }

    /// <summary><para>
    /// Called from AcDbAssocManager::auditAssociativeData() after file open and possibly
    /// after some other scenarios when the associative data may need to be audited and fixed-up.
    /// At this time custom code may also initialize internal chaches that were not saved to dwg/dxf 
    /// file, or do some other work.
    /// </para><para> 
    /// The action body may request the parent action to be erased by setting kErasedAssocStatus
    /// to parentActionHandling output argument. Setting kChangedDirectlyAssocStatus to
    /// parentActionHandling will make the parent action evaluate after the audit of all 
    /// actions has been completed.
    /// </para><para> 
    /// An example of possible and inevitable inconsistencies is when the drawing was modified 
    /// in an AutoCAD release that didn't have code for the action, the action body was a proxy
    /// and therefore didn't react to notifications and didn't evaluate.
    /// </para><para> 
    /// Another example of possible and inevitable ininconsistencies are references to objects 
    /// that are not in the database any more because their owning objects were erased, the 
    /// drawing was then saved, and these objects with erased owners were not saved to 
    /// database. No notifications happen about the erase of these objects because they were 
    /// not actually erased, so the actions cannot know that these objects are not in the database 
    /// any more and may still hold AcDbObjectIds of these "lazily-erased" objects. 
    /// </para><para>    
    /// Before auditAssociativeDataOverride() is called, the system performs overall 
    /// checks and fixes for cases like a dependency depending on a non-existent object,
    /// checks proper links between network, action, action body, action parameters, and 
    /// dependencies, etc., so that these general checks do not need to be performed by
    /// the custom code.
    /// </para></summary>
    ///
    virtual void auditAssociativeDataOverride(AcDbAssocStatus& parentActionHandling);

    /// <summary>
    /// General notification that the action body can receive. The information 
    /// about the notification is passed in an AcDbAssocNotificationData object. 
    /// </summary>
    /// <remarks> For internal use only. </remarks>
    /// <param name="pNotificationData"> 
    /// Pointer to an AcDbAssocNotificationData object. The action body should check 
    /// the type of the AcDbAssocNotificationData object, cast it to that type, 
    /// and obtain the notification information from it.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus notificationOverride(class AcDbAssocNotificationData* pNotificationData);

    /// <summary>
    /// Using this method the action body reveals its AcDbStepIds and AcDbPersSubentIds
    /// to the AcDbAssocPersSubentManager.
    /// </summary>
    /// <remarks> For internal use only. </remarks>
    /// <param name="stepIds">       The array of returned AcDbPersStepIds.    </param>
    /// <param name="persSubentIds"> The array of returned  AcDbPersSubentIds. </param>
    ///
    virtual Acad::ErrorStatus collectPersSubentNamingDataOverride(AcDbPersStepIdArray&   stepIds, 
                                                                  AcDbPersSubentIdArray& persSubentIds) const;

    /// <summary>
    /// Using this method the action body asks the AcDbAssocPersSubentManager 
    /// to remap its AcDbPersStepIds and PersSubentIds after the action body 
    /// has been cloned.
    /// </summary>
    /// <remarks> For internal use only. </remarks>
    /// <param name="pCloner"> 
    /// AcDbAssocPersSubentManagerCloner that the action body uses to remap 
    /// its AcDbPersStepIds and PersSubentIds.
    /// </param>
    //
    virtual Acad::ErrorStatus clonePersSubentNamingDataOverride(class AcDbAssocPersSubentManagerCloner* pCloner);

}; // class AcDbAssocActionBody


/// <summary>
/// Just to be able to specify output AcString parameters by default value.
/// </summary>
///
ACDBCORE2D_PORT AcString& dummyString();

#pragma pack (pop)

