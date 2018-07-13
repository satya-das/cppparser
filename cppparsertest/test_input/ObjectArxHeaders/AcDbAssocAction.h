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
// CREATED BY: Jiri Kripac                                 March 2007
//
// DESCRIPTION:
//
// AcDbAssocAction base class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocGlobal.h"
#include "dbEval.h"
#include "AcValue.h"
#pragma pack (push, 8)


/// <summary> <para>
/// Any object that wants to exhibit associative behavior, i.e. be automatically 
/// evaluated by the associative mechanism when objects it depends on change, 
/// needs to be derived from an AcDbAssocActionBody class (see comments at the
/// AcDbAssocActionBody class) and owned by a parent AcDbAssocAction object. The 
/// action body is fully owned by its parent action, such as when the parent 
/// action is erased, it also erases the owned action body. 
/// </para> <para>
/// The AcDbAssocAction class itself does not have virtual methods that could be 
/// overridden, therefore it is not possible for external developers to derive 
/// directly from the AcDbAssocAction class and override its methods. Internal 
/// AutoCAD developers can derive from the AcDbImpAssocAction class and override 
/// its virtual methods, but it should only be done when there is no possibility 
/// that objects of the derived action classes could become proxies.
/// </para> <para>
/// Each action is owned by an AcDbAssocNetwork that itself is an action, 
/// therefore hirearchical associative structures can be represented. 
/// </para> <para>
/// The main protocol of the AcDbAssocAction class is the evaluate() method that
/// calls the evaluateOverride() method of the owned AcDbAssocActionBody object. 
/// </para> <para>
/// Actions own AcDbAssocDependency objects that allow the actions to depend on
/// arbitrary AcDbObjects. This is how the connectivity in the network is 
/// represented. When objects the dependencies depend on change, the dependencies 
/// are notified, actions owning the dependencies are notified and also the 
/// hierarchy of the networks owning the actions is notified. This notification 
/// just changes AcDbAssocStatus of the dependencies and of the actions/networks
/// to "dirty", it does not trigger any action evaluation. 
/// </para> <para>
/// The actual action evaluation happens when the client code calls the evalaute()
/// method on the top-level network. This automatically evaluates all the actions 
/// the network owns that need to be evaluated because they depend, either 
/// directly or transitively, on objects that changed. If an action modifies an
/// object (has a write-dependency on it) and there is another action that uses
/// the modified object (has read-dependency on it), then, if the first action
/// is evaluated, the second action also needs to be transitively evaluated. 
/// </para> <para>
/// The flow of information is as follows:
/// </para> <para>
///
///   Object1 --ReadDep--> Action1 --WriteDep1--> Object2 --ReadDep--> Action2 ...
///
/// <para> </para>
/// Notice that an action may depend on multiple objects and may modify multiple 
/// other objects. The network forms a directed acyclic graph. The evalution 
/// algoritm makes sure that all actions that need to be evaluated are evaluated 
/// and that the evaluation happens in the correct order so that every action
/// is evaluated only after all other actions that modify objects this action
/// depends on have already been evaluated (the situation is actually litle 
/// bit more complex, there are other aspects controlling the evaluation order).
/// </para> <para>
/// The AcDbAssocManager::evaluateTopLevelNetwork() static method should be used 
/// to evaluate the top-level network of the database. It will collect and 
/// evaluate all the actions that need to be evaluated. Explicit evaluation of 
/// the individual sub-networks is not recommended.
///
/// </para> <para>
/// Actions may own action parameters that allow custom action body classes keep
/// and access their data in a uniform an high-level manner. Instead of each concrete 
/// custom action body devising its own way how to keep its data, they the data 
/// is uniformly stored in the form of AcDbAssocActionParam(eters), and for simple 
/// numerical values, in the form of value action parameters. The action parameters 
/// take care of keeping the data in various ways and provide the current values 
/// to the action body anytime the action body requests them. The custom action 
/// body does not even need to implement code to serialize and clone its data, 
/// because the data is owned and managed by the parent AcDbAssocAction. 
/// See the AcDbAssocActionParam class and derived classes for more details.
/// </para><para>
/// Another advantage of keeping the action body data in action parameters is that 
/// it is possible to write code that traverses and inspects the action body data 
/// in a generic way, without knowing anything about the action body itself.
/// </para><para>
/// AcDbAssocAction owns an array of AcDbAssocActionParams and an array of value 
/// action parameters. The AcDbAssocActionParams and the value action parameters 
/// are completely independent of each other. 
/// </para><para>
/// The value action parameter represents a named array of numerical values, such 
/// as a doubles, ints, strings or vectors. Usually the array will contain only 
/// a single element, but generally it con contain any number of elements. 
/// The value parameter name is a case-sensitive string. 
/// </para><para>
/// Each individual value may either be a constant, or defined by an expression. 
/// When it is defined by an expression, the value parameter keeps AcDbObjectId 
/// of a read-only AcDbAssocValueDependency (the dependency is owned by the 
/// parent AcDbAssocAction) on an anonymous AcDbAssocVariable that keeps the 
/// expression and provides the input value for the value parameter. This anonymous 
/// variable is exclusively managed by the value parameter who is responsible for 
/// its creation, deletion, copy, etc.
/// </para><para>
/// If the user enters the expression in the form of "name=expression", the
/// automatically created AcDbAssocVariable is assigned the given "name" instead
/// of being anonymous, i.e. with empty name. If the variable has explicit name,
/// it apperars in the parameters manager and can be referenced by other expressions
/// as any other variable. However, it is still completely managed by the value 
/// parameter who takes care of the variable deletion, copy, etc. 
/// </para></summary>
///
class ACDBCORE2D_PORT AcDbAssocAction : public AcDbObject
{
public:     
    ACRX_DECLARE_MEMBERS(AcDbAssocAction);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocAction(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Returns AcDbObjectId of an object of a class derived from 
    /// AcDbAssocActionBody, or a null id if no action body object has been set.
    /// The AcDbAssocActionBody object is owned by this AcDbAssocAction object 
    /// and implements the body of the custom action. See the comments at 
    /// the AcDbAssocActionBody class for more information.
    /// </summary>
    /// <returns> 
    /// AcDbObjectId of an object of a class derived from AcDbAssocActionBody 
    /// or null id.
    /// </returns>
    ///
    AcDbObjectId actionBody() const;

    /// <summary> 
    /// Takes an AcDbObjectId of an AcDbAssocAction and returns AcDbObjectId of 
    /// an object of a class derived from AcDbAssocActionBody, or a null id if 
    /// the action does not have any action body. This is just a shortcut allowing
    /// to deal with AcDbObjectId of an action without having to open it first.
    /// </summary>
    /// <param name="actionId"> 
    /// AcDbObjectId of an object of a class derived from AcDbAssocAction.
    /// </param>
    /// <returns> 
    /// AcDbObjectId of an object of a class derived from AcDbAssocActionBody 
    /// or null id.
    /// </returns>
    ///
    static AcDbObjectId actionBody(const AcDbObjectId& actionId);

    /// <summary> 
    /// Sets AcDbObjectId of an object of a class derived from AcDbAssocActionBody. 
    /// The AcDbAssocActionBody object becomes owned by this AcDbAssocAction 
    /// object and implements the body of the custom action. See the comments
    /// at the AcDbAssocActionBody class for more information.
    /// </summary>
    /// <param name="actionBodyId"> 
    /// AcDbObjectId of an object of a class derived from AcDbAssocActionBody
    /// or null id. 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setActionBody(const AcDbObjectId& actionBodyId);

    /// <summary> 
    /// If the action body is a proxy, the action is not evaluatable.
    /// </summary>
    /// <returns> True if the action is not evaluatable, false otherwise. </returns>
    ///
    bool isActionBodyAProxy() const;

    /// <summary> Gets the current AcDbAssocStatus of this action. </summary>
    /// <returns> The AcDbAssocStatus of this action. </returns>
    ///
    AcDbAssocStatus status() const;

    /// <summary> <para>
    /// Sets the AcDbAssocStatus of the action. If the status is one of the codes
    /// that indicate that the action will need to be evaluated (the 
    /// isEvaluationRequest() predicate returns true for such a status), but the 
    /// current status of the action is not that it would need to be evaluated, 
    /// it propagates this status up to the AcDbAssocNetwork owning the action, 
    /// and higher in the network hierarchy to the network owning this network, 
    /// etc, so that all owning networks know that they contain an action that 
    /// needs to be evaluated. 
    /// </para> <para>
    /// If the new status isEvaluationRequest() and evaluationRequestSeverityLevel() 
    /// of the new status is lower than the current evaluation request status of 
    /// the action, the current higher status of the action is kept and not 
    /// overwritten by the new lower status. Also, if the current status of the 
    /// action isTobeSkipped(), it is not overwritten by any new status that 
    /// isEvaluationRequest(). To change the action status in such a case, the 
    /// action status needs to be first changed to kIsUpToDateAssocStatus, and 
    /// after that it can be changed to an isEvaluationRequest() status.
    /// </para> </summary>
    /// <param name="newStatus"> The new AcDbAssocStatus of the action. </param>
    /// <param name="notifyOwningNetwork"> 
    /// If true, and the passed-in status indicates that the action needs to be
    /// evaluated, the status of the AcDbAssocNetwork owning this dependency is 
    /// set to the same status (unless the network evaluation status is already 
    /// more severe than the new one).
    /// </param>
    /// <param name="setInOwnedActions">
    /// If true, and this action owns some other actions (such as AcDbAssocNetwork
    /// owns actions), the status is also set in all owned actions (both directly
    /// owned and recursively owned).
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setStatus(AcDbAssocStatus newStatus, 
                                bool            notifyOwningNetwork = true,
                                bool            setInOwnedActions   = false);

    /// <summary> <para>
    /// Every action except for the topmost AcDbAssocNetwork is "logically" owned 
    /// by a single AcDbAssocNetwork. 
    /// </para> <para>
    /// This network may also be the "physical" database owner of the action 
    /// (the network has hard-ownership id of the action), but the "physical" 
    /// owner may also be some other object. For example, for networks attached 
    /// to AcDbBlockTableRecords, the "logical" owner is the top-level network of 
    /// the whole database but the "physical" database owner is the subdictionary 
    /// of the extension dictionary of the AcBdBlockTableRecord.
    /// </para> </summary>
    /// <returns> The logically owning AScDbAssocNetwork or AcDbObjectId::kNull 
    /// if it is the topmost AcDbAssocNetwork.
    /// </returns>
    ///
    AcDbObjectId owningNetwork() const;

    /// <summary> <para>
    /// Every action except for the topmost AcDbAssocNetwork is logically owned 
    /// by a single AcDbAssocNetwork. 
    /// </para> <para>
    /// This network may also be the "physical" database owner of the action 
    /// (the network has hard-ownership id of the action), but the "physical" 
    /// owner may also be some other object. For example, for networks attached 
    /// to AcDbBlockTableRecords, the "logical" owner is the top-level network of 
    /// the whole database but the "physical" database owner is the subdictionary 
    /// of the extension dictionary of the AcBdBlockTableRecord.
    /// </para> <para>
    /// This method should not be called directly, AcDbAssocNetwork::add/removeAction() 
    /// should be used, which in turn calls setOwningNetwork(), but it does more.
    /// </para> </summary>
    /// <param name="networkId"> The AcDbAssocNetwork logically owning this action. </param>
    /// <param name="alsoSetAsDatabaseOwner"> Make the network the database owner of this action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setOwningNetwork(const AcDbObjectId& networkId, bool alsoSetAsDatabaseOwner);

    /// <summary> <para>
    /// Gets AcDbAssocDependencies of this action. The default implementation 
    /// obtains all dependencies owned by the base action class and selects the 
    /// ones based on the required read/write type.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides the
    /// getDependenciesOverride() method, this method is called and it 
    /// supersedes the default implementation. It allows the custom action body 
    /// classes to control which dependencies to return and which not to mention.
    /// </para> </summary>
    /// <param name="readDependenciesWanted">  Read-type dependencies wanted. </param>
    /// <param name="writeDependenciesWanted"> Write-type dependencies wanted. </param>
    /// <param name="dependencyIds"> Returned AcDbObjectIds of AcDbAssocDependencies. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getDependencies(bool readDependenciesWanted, 
                                      bool writeDependenciesWanted,
                                      AcDbObjectIdArray& dependencyIds) const;

    /// <summary>
    /// Adds the given AcDbAssocDependency to this action. The dependency may 
    /// either become owned by this action (if setThisActionAsOwningAction is true) 
    /// which is the most common case, or just referenced by this action.
    /// </summary>
    /// <param name="dependencyId"> 
    /// AcDbObjectId of the AcDbAssocDependency being added to this action. 
    /// </param>
    /// <param name="setThisActionAsOwningAction"> 
    /// If true, sets this action to be the database owner of the dependency. 
    /// In this case the dependency must not be already owned by any other action.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addDependency(const AcDbObjectId& dependencyId, 
                                    bool                setThisActionAsOwningAction = true);

    /// <summary>
    /// Utility method that creates a new AcDbAssocDependency of the given pDependencyClass,
    /// possibly owning an AcDbAssocDependencyBody of the given pDependencyBodyClass,
    /// adds it to the database and to this action.
    /// </summary>
    /// <param name="pDependencyClass"> Type of the dependency to create, NULL means the base AcDbAssocDependency. </param>
    /// <param name="pDependencyBodyClass"> Type of the dependency body to create, NULL means no dependency body. </param>
    /// <param name="isReadDep"> The created dependency is a read dependency. </param>
    /// <param name="isReadDep"> The created dependency is a write dependency. </param>
    /// <param name="order"> The dependency order. </param>
    /// <param name="dependencyId"> AcDbObjectId of the newly created dependency. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addDependency(AcRxClass*    pDependencyClass,
                                    AcRxClass*    pDependencyBodyClass,
                                    bool          isReadDep,
                                    bool          isWriteDep,
                                    int           order,
                                    AcDbObjectId& dependencyId);

    /// <summary>
    /// Removes the given AcDbAssocDependency from this action.
    /// </summary>
    /// <param name="dependencyId"> 
    /// AcDbObjectId of the AcDbAssocDependency being removed from this action.
    /// </param>
    /// <param name="alsoEraseIt"> Erases the dependency after removing it. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeDependency(const AcDbObjectId& dependencyId, 
                                       bool                alsoEraseIt);

    /// <summary> <para>
    /// Removes all AcDbAssocDependencies kept in the vector of dependencies
    /// of this action and optionally also erases them.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides
    /// the removeAllDependenciesOverride() method, this method is called 
    /// to notify about the dependencies being removed. This happens after 
    /// all the dependencies have already been removed.
    /// </para> </summary>
    /// <param name="alsoEraseThem"> Erase the AcDbAssocDependencies after removing them. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeAllDependencies(bool alsoEraseThem);

    /// <summary> <para>
    /// Get AcDbObjects that this action depends on or modifies. The default 
    /// implementation collects all object on which the action has 
    /// AcDbAssocDependencies.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides the
    /// getDependentObjectsOverride() method, this method is called and it 
    /// supersedes the default implementation. It allows the custom action body 
    /// classes to control which objects to return and which not to mention,
    /// but usually there is no need to override this method, the default
    /// implementation that traverses all the dependencies of the action should
    /// suffice.
    /// </para> </summary>
    /// <param name="readDependenciesWanted">  Dependent-on objects wanted. </param>
    /// <param name="writeDependenciesWanted"> Modified objects wanted. </param>
    /// <param name="objectIds"> Returned AcDbObjectIds of the AcDbObjects. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getDependentObjects(bool readDependenciesWanted,
                                          bool writeDependenciesWanted,
                                          AcDbObjectIdArray& objectIds) const;

    /// <summary> <para>
    /// Checks whether the given AcDbAssocDependency is owned by this action,
    /// either directly, or if this action is a network, is owned by an action 
    /// owned by the network. 
    /// </para> <para>
    /// The default implementation first makes a quick check whether the 
    /// ownerId() of the dependency is the objectId() of this action. If not
    /// and it is a network, it calls getDependencies() and checks if the 
    /// dependency is one of the returned ones. The second check is generic
    /// and applicable to any action, but it has not been used as the default 
    /// implementation for any action because it is more expensive.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the isOwnedDependencyOverride() predicate, this predicate is called
    /// and it supersedes the default implementation. 
    /// </para> </summary>
    /// <param name="pDependency"> 
    /// The dependency that is checked whether it is owned by this action. 
    /// Needs to be open at least for read.
    /// </param>
    /// <returns> True iff the given dependency is owned by this action. </returns>
    ///
    bool isOwnedDependency(const AcDbAssocDependency* pDependency) const;

    /// <summary> <para>
    /// Checks whether the given AcDbAssocDependency, owned by this action, 
    /// is external to this action, i.e. it depends on an AcDbObject that is 
    /// not this action and is not owned by this action (when the action is 
    /// a network). Also, when the dependency does not depend on any object, 
    /// it is considered external.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the isExternalDependencyOverride() predicate, this predicate is called
    /// and it supersedes the default implementation. 
    /// </para> </summary>
    /// <param name="pDependency"> 
    /// The dependency that is checked whether it is external. Needs to be open 
    /// at least for read.
    /// </param>
    /// <returns> True iff the given dependency is external to this action. </returns>
    ///
    bool isExternalDependency(const AcDbAssocDependency* pDependency) const;

    /// <summary> <para>
    /// Delegated from the owned dependency's AcDbAssocDependency::isRelevantChange() 
    /// predicate. It allows the owning action, instead of the dependency itself, 
    /// to decide whether the object change is relevant to that particular 
    /// dependency. The default implementation just returns true.
    /// </para> <para>
    /// This way the data (usually the cached value) that is needed to decide 
    /// whether an object change is relevant to a particular dependency type
    /// or not, can be stored either in the dependency itself or in the action 
    /// that owns it, based on what is more convenient for each particular 
    /// action or dependency type.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the isRelevantDependencyChangeOverride() predicate, this predicate is
    /// called instead of just returning true.
    /// </para> </summary>
    /// <param name="pDependency"> 
    /// The dependency that is checked whether the change in the object it 
    /// depends on is relevant or not. It needs to be open at least for read.
    /// </param>
    /// <returns> 
    /// Returns iff the dependency change is relevant. The default 
    /// implementation returns true. 
    /// </returns>
    ///
    bool isRelevantDependencyChange(const AcDbAssocDependency* pDependency) const;

    /// <summary> <para>
    /// Delegated from the owned dependency's AcDbAssocDependency::hasCachedValue() 
    /// predicate. It allows the owning action, instead of the dependency itself, 
    /// to decide whether the dependency has a cached value. The default 
    /// implementation just returns false.
    /// </para> <para>
    /// This way the the cached value can be stored either in the dependency 
    /// itself or in the action that owns it, based on what is more convenient 
    /// for each particular action or dependency type.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the hasDependencyCachedValueOverride() predicate, this predicate is 
    /// called instead of just returning false.
    /// </para> </summary>
    /// <param name="pDependency"> 
    /// The dependency that is checked whether it has cached value. It needs to 
    /// be open at least for read.
    /// </param>
    /// <returns> 
    /// Returns true if the dependency has a cached value, false otherwise. The default 
    /// implementation returns false. 
    /// </returns>
    ///
    bool hasDependencyCachedValue(const AcDbAssocDependency* pDependency) const;

    /// <summary> <para>
    /// Delegated from the owned dependency's AcDbAssocDependency::isDependentOnTheSameThingAs() 
    /// predicate. It allows the owning action, instead of the dependency itself, 
    /// to decide whether the two depedencies depend on the same thing. The default 
    /// implementation just returns true.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the isDependentOnTheSameThingOveride() predicate, this predicate is 
    /// called instead of just returning true.
    /// </para> </summary>
    /// <param name="pDependency1"> 
    /// The dependency owned by this action. It needs to be open at least for read.
    /// </param>
    /// <param name="pDependency2"> 
    /// Another dependency. It needs to be open at least for read.
    /// </param>
    /// <returns> 
    /// Returns true if the two dependencies depend on the same "thing", false otherwise. 
    /// The default implementation returns false. 
    /// </returns>
    ///
    bool areDependenciesOnTheSameThing(const AcDbAssocDependency* pDependency1, 
                                       const AcDbAssocDependency* pDependency2) const;

    /// <summary> <para>
    /// Delegated from he owned dependency's AcDbAssocDependency::isEqualTo() 
    /// predicate. It allows the owning action, instead of the dependency itself, 
    /// to decide whether the two dependencies are equal. The default 
    /// implementation just returns false.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the areDependenciesEqualOveride() predicate, this predicate is called
    /// instead of just returning false.
    /// </para> </summary>
    /// <param name="pDependency1"> 
    /// The dependency owned by this action. It needs to be open at least for read.
    /// </param>
    /// <param name="pDependency2"> 
    /// Another dependency. It needs to be open at least for read.
    /// </param>
    /// <returns> 
    /// Returns true if the two dependencies are "equal", false otherwise. The 
    /// default implementation returns false. 
    /// </returns>
    ///
    bool areDependenciesEqual(const AcDbAssocDependency* pDependency1, 
                              const AcDbAssocDependency* pDependency2) const;

    /// <summary>
    /// General mechanism by which an action can be notified about events.
    /// </summary>
    ///
    Acad::ErrorStatus notification(AcDbAssocNotificationData* pNotifData);

    /// <summary> <para>
    /// Called from the owned dependency's AcDbAssocDependency::copied() 
    /// persistent reactor callback. It notifies the owning action about the fact 
    /// that an object the action has a dependency on has been cloned. The cloning
    /// may be just shallow clone, not necessarily deep or wblock clone.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the dependentObjectClonedOverride() callback, this callback is called.
    /// </para> </summary>
    /// <param name="pDependency">
    /// The AcDbAssocDependency on the AcDbObject that has been cloned.
    /// </param>
    /// <param name="pDbObj"> The original object. </param>
    /// <param name="pNewObj"> The newly created clone. </param>
    ///
    void dependentObjectCloned(const AcDbAssocDependency* pDependency, 
                               const AcDbObject*          pDbObj, 
                               const AcDbObject*          pNewObj);

    /// <summary> <para>
    /// Called just before the end of the main deep-cloning loop (before
    /// AcRxEventReactor::beginDeepCloneXlation() reactor notification), when 
    /// the objects have already been cloned but their ids haven't been translated 
    /// yet. 
    /// </para> <para>
    /// It asks the actions who have AcDbAssocDependencies on some objects 
    /// that have been cloned, whether the actions want to add some more objects 
    /// to deep clone. The actions can then report more objects to be deep cloned 
    /// and the main cloning loop then continues with deep cloning these additional 
    /// objects. If it caused more objects to be cloned, the actions that have 
    /// dependencies on these newly cloned objects are asked and may add yet more 
    /// objects to clone. This process continues until no more objects are cloned.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the addMoreObjectsToDeepCloneOverride() callback, this callback is called.
    /// </para> </summary>
    /// <param name="idMap"> The AcDbIdMapping of the current deep cloning session. </param>
    /// <param name="additionalObjectsToClone"> 
    /// Additional objects that the action also wants to deep clone. It is legal
    /// to add objects that have already been cloned; they will be ignored 
    /// and not cloned again.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addMoreObjectsToDeepClone(AcDbIdMapping& idMap, 
                                                AcDbObjectIdArray& additionalObjectsToClone) const;

    /// <summary> <para>
    /// Called from AcRxEventReactor::endDeepClone() reactor notification method 
    /// (ids of the clones have already been translated) to inform the source 
    /// actions that they have been cloned, so that they can update the clones 
    /// or do some other work that it needed. Notice that the source action can 
    /// obtain its clone by consulting the provided AcDbIdMapping.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the postProcessAfterDeepCloneOverride() callback, this callback is called.
    /// </para> </summary>
    /// <param name="idMap"> The AcDbIdMapping of the current deep cloning session. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus postProcessAfterDeepClone(AcDbIdMapping& idMap); 

    /// <summary> <para>
    /// Called from AcRxEventReactor::cancelDeepClone() reactor notification 
    /// method. Notice that the source action can obtain its clone by consulting 
    /// the provided AcDbIdMapping.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the postProcessAfterDeepCloneCancelOverride() callback, this callback is 
    /// called, but it may usually be safer not to override this callback and 
    /// just do nothing.
    /// </para> </summary>
    /// <param name="idMap"> The AcDbIdMapping of the current deep cloning session. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus postProcessAfterDeepCloneCancel(AcDbIdMapping& idMap); 

    /// <summary> <para>
    /// Predicate that returns true iff the system is currently evaluating an
    /// action or a network of actions. 
    /// </para> <para>
    /// Notice that when action evaluation is in progress, dependency notifications 
    /// are disabled. When an object that has dependencies attached to itself is 
    /// changed, the dependencies ignore this notification and consequently also 
    /// do not notify the actions owning the dependencies. This is necessary because 
    /// otherwise if one action evaluation modified some objects, the dependencies 
    /// on these objects would be notified and the status of other actions owning 
    /// these dependencies would be changed, requesting the actions to be evaluated
    /// again. This would lead to infinite loops.
    /// </para> </summary>
    /// <returns> True iff action evaluation is in progress. </returns>
    ///
    bool isActionEvaluationInProgress() const;

    /// <summary> 
    /// Returns the current AcDbAssocEvaluationCallback set by the 
    /// AcDbAssocAction::evaluate() call, or NULL if no action evaluation 
    /// is in progress. Notice that when action evaluation is in progress, there 
    /// always is a non-NULL AcDbAssocEvaluationCallback.
    /// </summary>
    /// <returns> The current AcDbAssocEvaluationCallback or NULL. </returns>
    ///
    AcDbAssocEvaluationCallback* currentEvaluationCallback() const;

    /// <summary>
    /// This method needs to be called from the client code evaluateOverride() 
    /// method, usually after the client code inspected the dependencies, found 
    /// which changed, which were on erased objects, etc. It gets all dependencies 
    /// of the action and evaluates the ones that need to be evaluated, i.e. 
    /// dependencies for which isEvaluationRequest(pDep->status()) == true.
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus evaluateDependencies();

    /// <summary> <para>
    /// Delegated from the owned dependency's AcDbAssocDependency::evaluateOverride()
    /// method. It allows the owning action, instead of the dependency itself, 
    /// to do the work. The default implementation just sets the dependency status 
    /// to kIsUpToDateAssocStatus.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the evaluateDependencyOverride() method, this method is called to do the 
    /// work.
    /// </para> </summary>
    /// <param name="pDependency"> 
    /// The dependency that is to be evaluated. It needs to be open at least 
    /// for read. 
    /// </param>
    ///
    void evaluateDependency(AcDbAssocDependency* pDependency);

    /// <summary> <para>
    /// This callback is called from AcDbAssocDependency::setStatus(..., true) 
    /// and notifies the action owning the dependency that the status of the 
    /// dependency has just been changed. The dependency is still open for 
    /// write and already has the new status.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the ownedDependencyStatusChangedOverride() method, it is called after
    /// the default implementation in the AcDbAssocAction class has been performed. 
    /// However, there should usually be no need to override this method.
    /// </para> </summary>
    /// <param name="pOwnedDependency"> The dependency whose status has just been changed. </param>
    /// <param name="previousStatus"> Previous status of the dependency. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus ownedDependencyStatusChanged(AcDbAssocDependency* pOwnedDependency, 
                                                   AcDbAssocStatus      previousStatus);

    /// <summary>
    /// Notifes the action that the owner of the action was transformed, such as
    /// that all entities in the AcDbBlockTableRecord owning the network that owns 
    /// the action were transformed.
    /// </summary>
    /// <param name="transform"> The provided transformation matrix. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus transformActionBy(const AcGeMatrix3d& transform);

    /// <summary> <para>
    /// Compares this action with the given action and returns true if and only
    /// if they are equal (whatever it means). Both actions need to be open at
    /// least for read.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the isEqualToOverride() predicate, this predicate is called.
    /// </para> </summary>
    /// <param name="pOtherAction"> The other action needs to be open for read. </param>
    /// <returns> True iff the two actions are equal. </returns>
    ///
    bool isEqualTo(const AcDbAssocAction* pOtherAction) const;

    /// <summary> <para>
    /// This method provides default implementation suitable for most 
    /// circumstances, but actions may override it to define their special 
    /// behavior.
    /// </para> <para>
    /// It is called when an AcDbAssocNetwork is evaluated during which it 
    /// sequentially evaluates all the actions in the network that need to be 
    /// evaluated. The evaluation algorithm first collects all actions that 
    /// need to be evaluated and then evaluates them based on their evaluation 
    /// priority by querying the actions.
    /// </para> <para>
    /// The action should return a positive priority number if it can be 
    /// evaluated and a negative number if it cannot. Higher positive priority
    /// numbers mean that the action should be evaluated sooner, ahead of actions 
    /// with lower positive priority. The negative numbers mean how much the 
    /// action cannot be evaluated. The smaller the number, the less the action 
    /// can be evaluated (such as when no action can be evaluated, the actions 
    /// with least negative priorities are evaluated to break the loop and maybe
    /// enable other actions to be evaluated). Priority 0 means that the priority 
    /// cannot be determined at this time.
    /// </para> <para>
    /// The default implementation returns kCanBeEvaluatedAssocEvaluationPriority
    ///  + evaluationRequestSeverityLevel(status()) if the action can be evaluated 
    /// because it only depends on objects that are results of actions that have 
    /// already been evaluated (actually the rules are little bit more complex), 
    /// and kCannotBeEvaluatedAssocEvaluationPriority if the action cannot be 
    /// evaluated because it depends on some objects that are result of some 
    /// not-yet evaluated actions.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides 
    /// the evaluationPriorityOverride() method, this method is called and it 
    /// supersedes the default implementation. 
    /// </para> </summary>
    /// <returns> 
    /// Priority greater than 0 means action can be evaluated, priority less 
    /// than 0 means action cannot be evaluated. Priority 0 mens that it cannot 
    /// be determined at this time.
    /// </returns>
    ///
    AcDbAssocEvaluationPriority evaluationPriority() const;

    /// <summary> <para>
    /// Lets the action report all other actions that need to be evaluated because 
    /// this action is evaluated. It is repeatedly used to transitively collect 
    /// all actions that need to be evaluated, before an associative network is 
    /// evaluated. This action needs to be open at least for read and it needs
    /// to require to be evaluated: isEvaluationRequest(pAction->status()) == true.
    /// </para> <para>
    /// The default implementation checks dependencies of this action and then
    /// dependencies of other actions on the objects this action depends on,
    /// and reports all dependencies of other actions that need to be evaluated. 
    /// This default implementation will suffice in most cases. The derived 
    /// action classes can add their own logic, but they should also always call
    /// the base class implementation.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object that overrides the
    /// getDependentActionsToEvaluateOverride() method, this method is called 
    /// and it supersedes the default implementation. 
    /// </para> </summary>
    /// <param name="pActionsToEvaluateCallback"> 
    /// The method uses this callback to report other AcDbAssocActions, 
    /// AcDbAssocDependencies and arbitrary AcDbObjects that should also be 
    /// scheduled to evaluate when this action is evaluated.
    /// </param>
    ///
    void getDependentActionsToEvaluate(AcDbActionsToEvaluateCallback* pActionsToEvaluateCallback) const;

    /// <summary> <para>
    /// This method is called by the client code to evaluate an action or an
    /// associative network. It is the crux of the whole associative mechanism.
    /// </para> <para>
    /// It evaluates the action based on the current values of the objects the 
    /// action depends on (the action has read-dependencies on these objects), 
    /// changes the objects that depend on this action (the action has write-
    /// dependencies on these objects) and sets the status of the action to 
    /// kIsUpToDateAssocStatus or to kFailedToEvaluateAssocStatus.
    /// </para> <para>
    /// If the action owns an AcDbAssocActionBody object, its evaluateOverride() 
    /// method is called to do the real work. For internal classes it is also 
    /// possible to directly override the AcDbImpAssocAction::evaluateOverride() 
    /// method.
    /// </para> <para>
    /// AcDbAssocAction::evaluateDependencies() should be called from inside of 
    /// the overridden evaluateOverride() method of a class derived from 
    /// AcDbAssocActionBody or AcDbImpAssocAction to evaluate the dependencies 
    /// that need to be evaluated. See the description at the evaluateDependencies() 
    /// method.
    /// </para> <para>
    /// While the action is being evaluated, it calls methods of the 
    /// currentEvaluationCallback() to inform the client code about the 
    /// evaluation. See the definition of AcDbAssocEvaluationCallback for 
    /// more details.
    ///
    /// </para> <para>
    /// The sequence of events is as follows:
    /// </para> <para>
    /// - Calls AcDbAssocEvaluationCallback::beginActionEvaluation().
    /// </para> <para>
    /// - Marks that action evaluation is in progress and sets the passed-in
    ///   AcDbAssocEvaluationCallback as the current evaluation callback. It
    ///   can then be obtained by other methods that are being invoked during 
    ///   the evaluation by calling currentEvaluationCallback().
    /// </para> <para>
    /// - Checks whether the action needs to be evaluated. Does not evaluate if not.
    /// </para> <para>
    /// - Calls AcDbImpAssocAction::evaluateOverride() to do the work. This calls
    ///   the AcDbAssocActionBody::evaluateOverride() method if the action owns
    ///   an action body object. The AcDbImpAssocAction::evaluateOverride() can
    ///   also be directly overridden in the internal classes.
    /// </para> <para>
    /// - Calls AcDbAssocEvaluationCallback::endActionEvaluation().
    /// </para> </summary>
    ///
    /// <param name="pEvaluationCallback"> 
    /// While the action is being evaluated, it calls methods of the callback
    /// object to inform the client code about the evaluation. The callback pointer 
    /// must not be NULL. See the definition of AcDbAssocEvaluationCallback 
    /// for more details.
    /// </param>
    ///
    void evaluate(AcDbAssocEvaluationCallback* pEvaluationCallback);

    /// <summary> <para>
    /// Starting from this AcDbAssocAction, checks this AcDbAssocAction and its 
    /// owners (in "physical" AutoCAD database object owhership sense) until an 
    /// AcDbAssocNetwork is encountered whose "database" owner is not another 
    /// AcDbAssocNetwork. Then finds an inverse of AcDbAssocNetwork::getInstanceFromObject(), 
    /// i.e. finds the AcDbObject for which getInstanceFromObject() method returns 
    /// the AcDbAssocNetwork.
    /// </para> </summary> 
    /// <returns> 
    /// AcDbObjectId of the AcDbObject owning an AcDbAssocNetwork that
    /// owns this AcDbAssocAction.
    /// </returns>
    ///
    AcDbObjectId objectThatOwnsNetworkInstance() const;

    /// <summary> 
    /// This function is called to notify the action when a there is a drag 
    /// operation in progress and some objects the action depends on, either
    /// directly or indirectly, are being dragged. 
    /// </summary> 
    /// <param name="status"> See the AcDb::DragStat enum. </param>
    ///
    void dragStatus(const AcDb::DragStat status);

    /// <summary>
    /// A static method to get all actions depending on the given AcDbObject
    /// (these actions have AcDbAssocDependencies on this object).
    /// </summary>
    /// <param name="pObject"> 
    /// The AcDbObject whose actions are requested. The object needs to be open
    /// at least for read.
    /// </param>
    /// <param name="readDependenciesWanted">  Actions that depend-on the object wanted. </param>
    /// <param name="writeDependenciesWanted"> Actions that modify the object wanted. </param>
    /// <param name="actionIds"> Returned AcDbObjectIds of the AcDbAssocActions. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus getActionsDependentOnObject(const AcDbObject* pObject,
                                                         bool readDependenciesWanted,
                                                         bool writeDependenciesWanted,                                   
                                                         AcDbObjectIdArray& actionIds);

    /// <summary><para>
    /// Detaches the write-dependencies on the object from the object and marks
    /// the dependencies with kErasedAssocStatus. It does it in the reverse order,
    /// starting from the last write dependency on the object and ending with the
    /// first. It calls removeActionsControllingObjectOverride() on the individual 
    /// action bodies of the object, so that they can do their own work, instead
    /// of the default handling that just detaches the write-dependencies from 
    /// the object and sets their status to kErasedAssocStatus.
    /// </para><para>
    /// The evaluation algorithm will later evaluate the actions owning these 
    /// dependencies with kErasedAssocStatus, and the evaluateOverride() method 
    /// of these actions may either change or erase these actions.
    /// </para><para>
    /// This call may create a new object, copy some contents from objectToRemoveActionsFrom
    /// to this newly created object, do swapIdWith() with objectToRemoveActionsFrom
    /// and then erase objectToRemoveActionsFrom. This is currently happening
    /// for the AcDbExtrudedRevolved/SweptLoftedSurface entities that may be this
    /// way 'converted' to a base AcDbSurface entities.
    /// </para></summary>
    /// <param name="readOnlyDependencyHandling">
    /// <para>
    ///  0 ... Keep all read-only dependencies, let them still depend on the object,
    ///        or redirect them to another object, if provided. Dependencies on 
    ///        intermediate (not last) object state will then depend on the last 
    ///        (and only) object state of the object, which may produce incorrect 
    ///        results in some cases.
    /// </para><para>
    ///  1 ... Keep read-only dependencies only if they depend on the last object 
    ///        state of the object, or redirect them to another object, if provided.
    ///        Dependencies that depend on intermediate object states of the object
    ///        are detached.
    /// </para><para>
    ///  2 ... Detach all dependencies on the object.
    /// </para></param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus removeActionsControllingObject(
        const AcDbObjectId& objectToRemoveActionsFrom, 
        int                 readOnlyDependencyHandling = 0, 
        const AcDbObjectId& objectToRedirectReadOnlyDependenciesTo = AcDbObjectId::kNull);

    /// <summary> <para>
    /// Finds actions that need to be evaluated when the given action is evaluated, 
    /// and changes their status to a evaluation request status, so that they will 
    /// be evaluated. Does not do a transitive closure of all such actions, only
    /// the actions that directly relate to the given action are visited.
    /// </para><para>
    /// This method needs to be called, for example, before an action is going 
    /// to be erased. If it were not called and the action was just erased, the 
    /// other actions that should be evaluated would not be marked to evaluate 
    /// and would not be evaluated.
    /// </para><para>
    /// This method should not be called when action evaluation is already in progress, 
    /// because it is too late, all actions that need to be evaluated have already 
    /// been marked to evaluate. 
    /// </para></summary>
    ///
    static Acad::ErrorStatus markDependentActionsToEvaluate(const AcDbObjectId& actionId);

    /// <summary>
    /// Returns true if and only if there is an action with a write-dependency
    /// on the given AcDbObject and the action status is not isToBeSkipped().
    /// </summary>
    /// <remarks> This method is for internal use only. </remarks>
    /// <param name="pObject"> AcDbObject whose actions are checked. </param>
    /// <returns> True if and only if there is an active action on the object. </returns>
    ///
    static bool doesObjectHaveActiveActions(const AcDbObject* pObject);

    /// <summary> 
    /// Removes all owned AcDbAssocActionParams, optionally also erasing them. 
    /// </summary>
    /// <param name="alsoEraseThem">  
    /// If true, the owned AcDbAssocActionParams are also erased. Otherwise they
    /// are just detached so that this action body is not their database owner.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeAllParams(bool alsoEraseThem);

    /// <summary> Returns then number of the owned AcDbAssocActionParams. </summary>
    /// <returns> Number of the owned AcDbAssocActionParameters. </returns>
    ///
    int paramCount() const;

    /// <summary> 
    /// Returns an array of the owned AcDbAssocActionParams. 
    /// </summary>
    /// <returns> 
    /// Array of the owned AcDbAssocActionParams. Notice that it returns a 
    /// const reference to an internal array. The client code must not hold on 
    /// to this array and should make a copy of the array if it is doing anything 
    /// more than just momentarily accessing its elements.
    /// </returns>
    ///
    const AcDbObjectIdArray& ownedParams() const;

    /// <summary> 
    /// Adds a new AcDbAssocActionParam. This AcDbAssocAction  becomes the database 
    /// owner of this action parameter.
    /// </summary>
    /// <param name="paramId"> 
    /// AcDbObjectId of the action parameter being added. If the action parameter 
    /// is already owned by this AcDbAssocAction, it it just returns its existing 
    /// index in the array and does not add it again. 
    ///</param>
    /// <param name="paramIndex"> 
    /// Returned index of the newly added action parameter. If the parameter is 
    /// already owned by this AcDbAssocAction, its existing index is returned.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addParam(const AcDbObjectId& paramId, int& paramIndex);

    /// <summary> 
    /// Utility methods that creates a new AcDbAssocActionParam of the given 
    /// pParamClass and with the given paramName and adds it to the database and 
    /// to this AcDbAssocAction. 
    /// </summary>
    /// <param name="paramName"> Name of the action parameter to create. </param>
    /// <param name="pParamClass"> Type of the action parameter to create. </param>
    /// <param name="paramId"> AcDbObjectId of the newly created action parameter. </param>
    /// <param name="paramIndex"> Index of the newly created action parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addParam(const AcString& paramName, AcRxClass* pParamClass, AcDbObjectId& paramId, int& paramIndex); 

    /// <summary> 
    /// Removes the AcDbAssocActionParam, optionally also erasing it. 
    /// </summary>
    /// <param name="paramId"> AcDbObjectId of the action parameter to remove. </param>
    /// <param name="alsoEraseIt">  
    /// If true, the owned action parameter is also erased. Otherwise it is just
    /// detached so that this AcDbAssocAction is not its database owner.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeParam(const AcDbObjectId& paramId, bool alsoEraseIt); 

    /// <summary> 
    /// Returns all owned AcDbAssocActionParams with the given name. Notice that
    /// more than one action parameter may have the same name. The parameters are 
    /// always returned in the same order which is the order the parameters were 
    /// added to the action. Thus, an array of action parameters can easily 
    /// be represented by multiple action parameters with the same name.
    /// </summary>
    /// <param name="paramName">  The name of the action parameter. </param>
    /// <returns> All owned action parameters with the given name. </returns>
    ///
    const AcDbObjectIdArray& paramsAtName(const AcString& paramName) const;

    /// <summary> 
    /// Returns an owned AcDbAssocActionParam specified by its name and optional 
    /// index among all parameters with the same name. The default index 0 means
    /// the first parameter with the given name is returned.
    /// </summary>
    /// <param name="paramName"> The name of the action parameter. </param>
    /// <param name="index"> Index among all parameters with the same name. </param>
    /// <returns> The owned action parameter or a null AcDbObjectId if not found. </returns>
    ///
    AcDbObjectId paramAtName(const AcString& paramName, int index = 0) const;

    /// <summary> 
    /// Returns an owned AcDbAssocActionParam in the array of all action parameters 
    /// owned by this AcDbAssocAction.
    /// </summary>
    /// <param name="paramIndex"> Index in the array of all action parameters. </param>
    /// <returns> The owned action parameter or a null AcDbObjectId if not found. </returns>
    ///
    AcDbObjectId paramAtIndex(int paramIndex) const;

    /// <summary> 
    /// Returns names of all owned value action parameters. The names of the value
    /// action parameters are arbitrary case-sensitive strings but must be unique.
    /// </summary>
    /// <param name="paramNames"> Names of all owned value action parameters. </param>
    ///
    void ownedValueParamNames(AcArray<AcString>& paramNames) const;

    /// <summary> 
    /// Obtains arrays of values, expressions and evaluatorIds for a given value 
    /// action parameter. The arrays can be of any length, but in most cases they 
    /// will be of length 1, meaning that the value action parameter keeps a single 
    /// value, not an array of values. All three returned arrays are of the same 
    /// length. If there is no expression for a particular array element, the 
    /// expression string and the evaluatorId are empty strings.
    /// </summary>
    /// <param name="paramName">    The name of the value action parameter. </param>
    /// <param name="values">       The returned array of values. </param>
    /// <param name="expressions">  The returned array ox expressions. </param>
    /// <param name="evaluatorIds"> The returned array of evaluatorIds. </param>
    /// <returns> 
    /// If a value action parameter with the given name is not found, returns Acad::eNullPtr.
    /// </returns>
    ///
    Acad::ErrorStatus getValueParamArray(const AcString&           paramName,
                                         AcArray<AcDbEvalVariant>& values,
                                         AcArray<AcString>&        expressions, 
                                         AcArray<AcString>&        evaluatorIds) const;

    /// <summary> 
    /// The same as getValueParamArray() but returns just the valueIndex's element 
    /// of the returned array.
    /// </summary>
    /// <param name="paramName">    The name of the value action parameter. </param>
    /// <param name="values">       The returned values. </param>
    /// <param name="expressions">  The returned expression. </param>
    /// <param name="evaluatorIds"> The returned evaluatorId. </param>
    /// <param name="valueIndex">   Index of the array element. </param>
    /// <returns> 
    /// If a value action parameter with the given name is not found, returns 
    /// Acad::eNullPtr. If the valueIndex is out of range, returns Acad::eInvalidIndex.
    /// </returns>
    ///
    Acad::ErrorStatus getValueParam(const AcString&  paramName,
                                    AcDbEvalVariant& value,
                                    AcString&        expression, 
                                    AcString&        evaluatorId, 
                                    int              valueIndex = 0) const;

    /// <summary><para> 
    /// Sets arrays of values, expressions and evaluatorIds for a given value 
    /// action parameter. The arrays can be of any length, but in most cases they 
    /// will be of length 1, meaning that the value action parameter keeps a single 
    /// value, not an array of values. All three arrays must be of the same length. 
    /// If there is no expression for a particular array element, the expression 
    /// string and the evaluatorId must be empty strings. 
    /// </para><para>
    /// If the user enters the expression in the form of "name=expression", the
    /// automatically created AcDbAssocVariable is assigned the given "name",
    /// apperars in the parameters manager and can be referenced by other 
    /// expressions as any other variable. If the expression is in the form
    /// "expression", an anonymous variable is created that cannot be referenced
    /// and is not visible in the parameters manager.
    /// </para><para>
    /// If a value parameter of the given name does not exist, it is created.
    /// Otherwise the existing value parameter is used.
    /// </para></summary>
    /// <param name="paramName">     The name of the value action parameter. </param>
    /// <param name="values">        The array of values to set. </param>
    /// <param name="expressions">   The array of expressions to set. </param>
    /// <param name="evaluatorIds">  The array of evaluatorIds to set. </param>
    /// <param name="errorMessages"> The returned array of error messages for the individual expressions. </param>
    /// <param name="silentMode">    Do not print error message if the expression string is invalid. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParamArray(const AcString&                 paramName,
                                         const AcArray<AcDbEvalVariant>& values,
                                         const AcArray<AcString>&        expressions,
                                         const AcArray<AcString>&        evaluatorIds,
                                         AcArray<AcString>&              errorMessages,
                                         bool                            silentMode);

    /// <summary><para>
    /// The same as setValueParamArray() but sets just the valueIndex's element. 
    /// If the existing array is shorter that ther given valueIndex, the array
    /// is extended to cover the valueIndex's element. 
    /// </para><para>
    /// If a value parameter of the given name does not exist, it is created.
    /// Otherwise the existing value parameter is used.
    /// </para><para>
    /// </para></summary>
    /// <param name="paramName">     The name of the value action parameter. </param>
    /// <param name="values">        The value to set. </param>
    /// <param name="expressions">   The expression to set. </param>
    /// <param name="evaluatorIds">  The evaluatorId to set. </param>
    /// <param name="errorMessages"> The returned message for the expressions. </param>
    /// <param name="silentMode">    Do not print error message if the expression string is invalid. </param>
    /// <param name="valueIndex">    Index of the array element to set. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParam(const AcString&        paramName,
                                    const AcDbEvalVariant& value,
                                    const AcString&        expression,
                                    const AcString&        evaluatorId,
                                    AcString&              errorMessage,
                                    bool                   silentMode,
                                    int                    valueIndex = 0);

    /// <summary> Returns AcValue::UnitType of the value parameter. </summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <returns> The AcValue::UnitType of the value parameter. </returns>
    ///
    AcValue::UnitType valueParamUnitType(const AcString& paramName) const;

    /// <summary> Sets the AcValue::UnitType of the value parameter. </summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <param name="unitType"> AcValue::UnitType. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParamUnitType(const AcString& paramName, AcValue::UnitType unitType);

    /// <summary> 
    /// Removes the value parameter and also erases the corresponding AcDbAssocVariables, 
    /// if there are any. 
    /// </summary>
    /// <param name="paramName"> The name of the value action parameter to remove. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeValueParam(const AcString& paramName); 

    /// <summary><para>
    /// Each individual value of a value action parameter may either be a constant, 
    /// or defined by an expression. When it is defined by an expression, the value 
    /// action parameter keeps AcDbObjectId of a read-only AcDbAssocValueDependency 
    /// (the dependency is owned by the parent AcDbAssocAction) on an AcDbAssocVariable 
    /// that keeps the expression and provides the input value for the value 
    /// action parameter. This variable is exclusively managed by the value parameter 
    /// who is responsible for its creation, deletion, copy, etc.
    /// </para><para>
    /// If the user enters the expression in the form of "name=expression", this
    /// automatically created AcDbAssocVariable is assigned the given "name",
    /// apperars in the parameters manager and can be referenced by other 
    /// expressions as any other variable. If the expression is in the form
    /// "expression", an anonymous variable is created that cannot be referenced
    /// and is not visible in the parameters manager.    
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <param name="variableIds"> 
    /// Returned array of AcDbAssocVariables for all the values of the value action 
    /// parameter with the given name. If a value is a constant and does not have 
    /// a corresponding AcDbAssocVariable, AcDbObjectId::kNull is returned for 
    /// that array element.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus valueParamInputVariables(const AcString& paramName, AcDbObjectIdArray& variableIds) const;

    /// <summary><para>
    /// The value parameter can keep AcDbObjectId of an "output" dependency (of 
    /// any kind) on a controlled object. The value parameter (expected to have 
    /// just a single value) then becomes "linked" with the named "property" of 
    /// the controlled object. 
    /// </para><para>
    /// The property name is the name of the value parameter. The "property" 
    /// of the controlled object is accessed via the AcDbAssocValueProviderPE 
    /// protocol extension that the controlled object must expose. The setValue() 
    /// method of the protocol extension is then called to set the "property" of 
    /// the controlled object to be the same as the current value of the value 
    /// parameter. The getValue() method of the protocol extension is then called
    /// to obtain the current value of the "property" of the controlled object and 
    /// set it to the value parameter.
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <param name="controlledObjectDepId"> 
    /// An existing AcDbAssocDependency (or a derived class) on the AcDbObject 
    /// controlled by this value parameter. The dependency is owned by the action
    /// that owns this AcDbAssocAction.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setValueParamControlledObjectDep(const AcString& paramName, const AcDbObjectId& controlledObjectDepId);

    /// <summary><para>
    /// Updates the "propery" of the controlled object from the current value of 
    /// a value action parameter.
    /// </para><para>
    /// See setValueParamControlledObjectDep() for information about how to 
    /// link value action parameters with named properties of controlled objects.
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus updateValueParamControlledObject(const AcString& paramName) const;

    /// <summary><para>
    /// Updates the value of the value action parameter from the current value of
    /// a named "property" of the controlled object.
    /// </para><para>
    /// See setValueParamControlledObjectDep() for information about how to 
    /// link value action parameters with named properties of controlled objects.
    /// </para></summary>
    /// <param name="paramName"> The name of the value action parameter. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus updateValueParamFromControlledObject(const AcString& paramName);

    /// <summary><para>
    /// Updates named properties of all objects that are linked with value action 
    /// paramerters.
    /// </para><para>
    /// See setValueParamControlledObjectDep() for information about how to 
    /// link value action parameters with named properties of controlled objects.
    /// </para></summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus updateAllObjectsControlledByValueParams() const;

    /// <summary>
    /// Transforms all constant geometries in all owned AcDbAssocParam(eters). 
    /// Example of a constant geometry is an AcGeCurve3d* in AcDbAssocEdgeActionParam
    /// or AcGePoint3d in AcDbAssocVertexActionParam.
    /// </summary>
    /// <param name="transform">
    /// Transformation to be applied to all constant geometries in the owned 
    /// AcDbAssocActionParams.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus transformAllConstantGeometryParams(const AcGeMatrix3d& transform);

    /// <summary>
    /// Scales values of all value action parameters whose units indicate they 
    /// represent distances. If the value is defined by an expression, the expression 
    /// is replaced with a constant value. 
    /// </summary>
    /// <param name="scaleFactor">
    /// Scaling factor to be applied to all distance value action parameters.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus scaleAllDistanceValueParams(double scaleFactor);

    friend class AcDbImpAssocAction;

}; // class AcDbAssocAction

#pragma pack (pop)

