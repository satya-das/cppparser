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
// AcDbAssocDependency base class. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocGlobal.h"
#include "AcDbCompoundObjectId.h"
#pragma pack (push, 8)


/// <summary> <para>
/// AcDbAssocDependencies represent information about which AcDbAssocActions depend 
/// on or modify which AcDbObjects. This is how the associativity in the drawing is 
/// represented. Dependencies are owned by actions and are attached to the objects 
/// as persistent reactors. When the dependent-on object changes, it notifies the
/// dependency via the persistent reactor mechanism. The dependency checks 
/// whether the change is relevant, such as when the dependency is on an endpoint 
/// of a line but the color of the line changed, or the other endpoint changed, 
/// and if yes, it changes its status indicating that it needs to be evaluated, 
/// and also changes the status of the owning action indicating that it needs 
/// to be evaluated (and the action changes the status of the AcDbAssocNetwork 
/// that owns it).
/// </para> <para>
/// The base AcDbAssocDependency class can be used as it but there are also
/// provided a few concrete derived dependency classes that represent particular 
/// kinds of dependencies on particular objects or subobjects, such as 
/// on subentities (faces, edges, vertices) of geometric entities, on objects
/// that provide a numerical value, etc. For example, the dependency on a 
/// subentity of a geometric entity keeps AcDbAssocPersSubentId of the subentity
/// and the cached subentity geometry (such as the [x,y,z] of a vertex 
/// subentity, the AcDbCurve of an edge subentity, etc.). It can then check 
/// whether the subentity really changed by obtaining the subentity geometry 
/// from the geometric entity and comparing it with the cached geometry. If they 
/// are the same, the change notification is ignored.
/// </para> <para>
/// A better way to add a custom dependency class is to derive a custom 
/// AcDbAssocDependencyBody class (see comments at the AcDbAssocDependencyBody 
/// class) and make objects of this class owned by the parent AcDbAssocDependency 
/// objects. The relation between AcDbAssocDependency and AcDbAssocDependencyBody 
/// classes is analogous to the relation between AcDbAssocAction and AcDbAssocActionBody 
/// classes, so please read the comments at the AcDbAssocAction class for more 
/// information. In particular, the dependency  body is fully owned by its parent 
/// dependency, such as when the parent dependency is erased, it also erases the 
/// owned dependency body. 
/// </para> <para>
/// A more memory efficient way to implement custom dependency behavior is to 
/// use objects of the AcDbAssocDependency base class and let them delegate to 
/// the owning action (see the isDelegatingToOwningAction() property). The
/// AcDbAssocActionBody owned by the action owning the dependency then overrides 
/// methods like AcDbAssocActionBody::isRelevantDependencyChangeOverride() to 
/// implement the custom dependency behavior.
/// 
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocDependency : public AcDbObject
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocDependency);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocDependency(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Returns AcDbObjectId of an object of a class derived from 
    /// AcDbAssocDependencyBody, or a null id if no dependency body object
    /// has been set. The AcDbAssocDependencyBody object is owned by this 
    /// AcDbAssocDependency object and implements the body of the custom 
    /// dependency. See the comments at the AcDbAssocDependencyBody class for
    /// more information.
    /// </summary>
    /// <returns> 
    /// AcDbObjectId of an object of a class derived from AcDbAssocDependencyBody 
    /// or null id.
    /// </returns>
    ///
    AcDbObjectId dependencyBody() const;
    
    /// <summary> 
    /// Sets AcDbObjectId of an object of a class derived from 
    /// AcDbAssocDependencyBody. The AcDbAssocDependencyBody object becomes 
    /// owned by this AcDbAssocDependency object and implements the body of 
    /// the custom dependency. See the comments at the AcDbAssocDependencyBody 
    /// class for more information.
    /// </summary>
    /// <param name="dependencyBodyId"> 
    /// AcDbObjectId of an object of a class derived from AcDbAssocDependencyBody
    /// or null id. 
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setDependencyBody(const AcDbObjectId& dependencyBodyId);

    /// <summary> Get the current AcDbAssocStatus of this dependency. </summary>
    /// <returns> The AcDbAssocStatus of this dependency. </returns>
    ///
    AcDbAssocStatus status() const;

    /// <summary> <para>
    /// Sets the AcDbAssocStatus of the dependency. If the status is one of the 
    /// codes that indicate that the action owning the dependency will need to 
    /// be evaluated (the isEvaluationRequest() predicate  returns true for such
    /// a status), it can also notify the action owning the dependency to change 
    /// its status indicating that it needs to be evaluated. The action may change 
    /// its status and notify the network owning the action. The network may change 
    /// its status and notify its owning network, etc. until all the networks 
    /// in the hirearchy are notified that they contain an action that needs to
    /// be evaluated.
    /// </para> <para>
    /// If the new status satisfies the isEvaluationRequest() predicate and 
    /// evaluationRequestSeverityLevel() of the new status is lower than the 
    /// current evaluation request status of the dependency, the current higher 
    /// status of the dependency is kept and not overwritten by the new lower 
    /// status. Also, if the current status of the dependency satisfies the 
    /// isTobeSkipped() predicate, it is not overwritten by any new status that 
    /// isEvaluationRequest(). To change the dependency status in such a case, the 
    /// dependency status needs to be first changed to kIsUpToDateAssocStatus, 
    /// and after that it can be changed to an isEvaluationRequest() status.
    /// </para> </summary>
    /// <param name="newStatus"> The new AcDbAssocStatus of the dependency. </param>
    /// <param name="notifyOwningAction"> 
    /// If true, and the passed-in status indicates that the dependency needs to 
    /// be evaluated, the status of the AcDbAssocAction owning this dependency 
    /// is set to the same status (unless the action evaluation status is already 
    /// more severe than the new one). The action then notifies its owning network.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setStatus(AcDbAssocStatus newStatus, 
                                bool            notifyOwningAction = true);

    /// <summary>
    /// Returns true iff the AcDbAssocAction owning the dependency uses the 
    /// value of the dependent-on AcDbObject. It just returns the value of a bool 
    /// data member owned by AcDbAssocDependency. The default value of this flag 
    /// is false.
    /// </summary>
    /// <returns>
    /// <para> true  = Action uses the value of the dependent-on object. </para>
    /// <para> false = Action does not use the value of the dependent-on object. </para>
    /// </returns>
    ///
    bool isReadDependency() const;

    /// <summary>
    /// Returns true iff the AcDbAssocAction owning the dependency changes the 
    /// value of the dependent-on AcDbObject. It just returns the value of a bool 
    /// data member owned by AcDbAssocDependency. The default value of this flag 
    /// is false.
    /// </summary>
    /// <returns>
    /// <para> true  = Action changes the value of the dependent-on object. </para>
    /// <para> false = Action does not change the value of the dependent-on object. </para>
    /// </returns>
    ///
    bool isWriteDependency() const;

    /// <summary>
    /// Sets what isReadDependency() should return.
    /// </summary>
    /// <param name="yesNo"> Value that isReadDependency() should return. </param>
    ///
    void setIsReadDependency(bool yesNo);

    /// <summary>
    /// Sets what isWriteDependency() should return.
    /// </summary>
    /// <param name="yesNo"> Value that isWriteDependency() should return. </param>
    ///
    void setIsWriteDependency(bool yesNo);

    /// <summary> <para>
    /// Returns true iff the AcDbAssocAction owning the dependency requires the 
    /// dependent-on AcDbObject to be in the expected "object state" with 
    /// respect to the list of dependencies on the object, before the action can 
    /// be evaluated. 
    /// </para> <para>
    /// It means actions that own write-type dependencies on the object that 
    /// precede this dependency in the list of all dependencies on the object
    /// need to be evaluated, and actions owning write-type dependencies on the 
    /// object that follow this dependency in the list must not be evaluated. 
    /// This also means the object is in the object state just after evaluation
    /// of the immediately preceding action that modified the object but before 
    /// evaluation of the next action that would modify the object again and 
    /// bring it to the next object state.
    /// </para> <para>
    /// It just returns the value of a bool data member owned by AcDbAssocDependency. 
    /// The default value of this flag is true.
    /// </para> </summary>
    /// <returns>
    /// <para> 
    /// true = Dependency is object state dependent, i.e. its position in the 
    /// list of dependencies on the object matters.
    /// </para>
    /// <para> 
    /// false = Dependency is not object state dependent, i.e. its position in 
    /// the list of dependencies on the object matters.
    /// </para>
    /// </returns>
    ///
    bool isObjectStateDependent() const;

    /// <summary>
    /// Sets what isObjectStateDependent() should return. It just sets the bool 
    /// data member owned by AcDbAssocDependency.
    /// </summary>
    /// <param name="yesNo"> Value that isObjectStateDependent() should return. </param>
    ///
    void setIsObjectStateDependent(bool yesNo);

    /// <summary> <para>
    /// Returns order of the dependency, i.e. the order where it should be
    /// positioned in the list of all dependencies on an AcDbObject. Dependencies 
    /// with lower order() are positioned in the list before the dependencies 
    /// with higher order(). Dependencies with the same order() are ordered 
    /// based on how they were added to the object, the dependencies added 
    /// later are positioned after the dependencies added earlier.
    /// </para> <para>
    /// It just returns the value of an int data member owned by AcDbAssocDependency. 
    /// Default value of this data member is 0.
    /// </para> </summary>
    /// <returns>
    /// Order is any integer value stored in the dependency. The default 
    /// value is 0.
    /// </returns>
    ///
    int order() const;

    /// <summary>
    /// Sets what order() should return. It just sets the int data member owned 
    /// by AcDbAssocDependency. Notice that if a dependency has already been
    /// attached to an object by calling attachToObject(), calling setOrder() 
    /// does not reposition the dependency in the list and should not be done.
    /// </summary>
    /// <param name="yesNo"> Value that order() should return. </param>
    ///
    void setOrder(int newOrder);

    /// <summary> 
    /// Every dependency is owned (in the logical as well as in the AutoCAD 
    /// database sense) by an AcDbAssocAction.
    /// </summary>
    /// <returns> The owning AcDbAssocAction. </returns>
    ///
    AcDbObjectId owningAction() const { return ownerId(); }

    /// <summary> <para>
    /// Every dependency is owned (in the logical as well as in the AutoCAD 
    /// database sense) by an AcDbAssocAction. 
    /// </para> <para>
    /// This method should not be called directly, AcDbAssocAction::add/removeDependency() 
    /// should be used, which in turn calls setOwningAction(), but it does more.
    /// </para> </summary>
    /// <param name="actionId"> The AcDbAssocAction owning this dependency. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setOwningAction(const AcDbObjectId& actionId);

    /// <summary>
    /// A dependency is attached to the dependent-on AcDbObject as a persistent 
    /// reactor.
    /// </summary>
    /// <returns> 
    /// The AcDbObject this dependency is attached to, or AcDbObjectId::kNull
    /// if the dependency is not attached to any object.
    /// </returns>
    ///
    AcDbObjectId dependentOnObject() const;

    /// <summary>
    /// A dependency is attached as a persistent reactors to all objects of
    /// the AcDbCompoundObjectId. If the dependency does not use AcDbCompoundObjectId, 
    /// the returned AcDbCompoundObjectId is of the dependentOnObject() converted
    /// to an AcDbCompoundObjectId.
    /// </summary>
    /// <param name="compoundId"> 
    /// The AcDbCompoundObjectId, either directly kept in this dependency, or 
    /// created from the dependentOnObject() AcDbObjectId.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getDependentOnCompoundObject(AcDbCompoundObjectId& compoundId) const;

    /// <summary>
    /// Returns true if the dependency is using AcDbCompoundObjectId to depend 
    /// on the dependent-on-object.
    /// </summary>
    /// <returns> 
    /// True iff AcDbCompoundObjectId is used to identify the dependent-on-object.
    /// </returns>
    ///
    bool isDependentOnCompoundObject() const;

    /// <summary>
    /// All dependencies attached to the same AcDbObject are kept in a doubly-linked 
    /// list. The order in the list is determied by the order() property of the 
    /// dependencies in the list.
    /// </summary>
    /// <returns> 
    /// The previous dependency in the list of dependencies of an AcDbObject or
    /// AcDbObjectId::kNull if it is the first dependency in the list.
    /// </returns>
    ///
    AcDbObjectId prevDependencyOnObject() const;

    /// <summary>
    /// All dependencies attached to the same AcDbObject are kept in a doubly-linked 
    /// list. The order in the list is determied by the order() property of the 
    /// dependencies in the list.
    /// </summary>
    /// <returns> 
    /// The next dependency in the list of dependencies of an AcDbObject or
    /// AcDbObjectId::kNull if it is the last dependency in the list.
    /// </returns>
    ///
    AcDbObjectId nextDependencyOnObject() const;

    /// <summary>
    /// A dependency is attached to the dependent-on AcDbObject as a persistent 
    /// reactor, but it may also not be attached to any object. In this case 
    /// AcDbAssocDependency::dependentOnObject() returns AcDbObjectId::kNull.
    /// </summary>
    /// <returns> true iff the dependency it attached to an object. </returns>
    ///
    bool isAttachedToObject() const { return !dependentOnObject().isNull(); }

    /// <summary> <para>
    /// Attaches this dependency to a given AcDbCompoundObjectId as a persistent 
    /// reactor and also orders it to be at the correct position in the list
    /// of dependencies on the object, based on the dependency order(). The 
    /// dependency that is being attached must not be currently attached to 
    /// any object. 
    /// </para> <para>
    /// When the AcDbCompoundObjectId contains multiple ids, it attaches the 
    /// dependency to the AcDbCompoundObjectId::topId(), and also attaches this 
    /// dependency as a persistent reactor to all the other objects that the 
    /// AcDbCompoundObjectId references.
    /// </para> <para>
    /// The object may refuse dependencies being attached to it by deriving from 
    /// AcDbAssocDependencyPE AcRx protocol extension class, implementing the 
    /// allowsDependencies() predicate and attaching the protocol extension to 
    /// the object. In this case attachToObject() then returns eVetoed error status. 
    /// The client code should check the returned error status and do not assume 
    /// that it is always eOk. The AcDbAssocDependencyPE also allows the object
    /// to redirect the dependency attachment to another object by implementing
    /// the redirectDependencyAttachment() method.
    /// </para> </summary>
    /// <param name="compoundId"> The AcDbCompoundObjectId to attach the 
    /// dependency to. If regular AcDbObjectId is passed in, it is automatically 
    /// converted to AcDbCompoundObjectId.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus attachToObject(const AcDbCompoundObjectId& compoundId);

    /// <summary>
    /// Transfers the dependency from the current object to another object.
    /// It does it by first detaching it from its current object and then attaching
    /// to the new one. It is similar to calling detachFromObject() followed
    /// by attachToObject(), but it also redirects other information in the dependency,
    /// such as the AcDbAssocPersSubentId owned by AcDbAssocGeomDependency.
    /// </summary>
    ///
    Acad::ErrorStatus transferToObject(const AcDbCompoundObjectId& compoundId);

    /// <summary> 
    /// Returns current status of the dependentOnObject, can be eOk, 
    /// eNotInitializedYet or eInvalidObjectId.
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus dependentOnObjectStatus() const;

    /// <summary> 
    /// Detaches this dependency from the AcDbObject it is currently attached 
    /// to. It also detatches it from the list of persistent reactors of the
    /// dependent-on-object, and if the dependency is on a compound object,
    /// it detaches this dependency from the persistent reactor lists of all
    /// objects the dependency is currently attached to.
    /// </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus detachFromObject();

    /// <summary> <para>
    /// Updates the object the dependency depends on, based on the information
    /// the dependency obtains from the owning action. If the dependency owns 
    /// an AcDbAssocDependencyBody object, its updateDependentOnObject() method 
    /// is called, otherwise the default implementation of this method does 
    /// nothing. 
    /// </para> <para>
    /// The dependency object must be opened at least for read. This method is 
    /// not made "const" because it could potentially update some cache kept in 
    /// the dependency, but it is not expected to do so.
    /// </para> </summary>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus updateDependentOnObject();

    /// <summary> <para>
    /// Sets the dependent-on object of this dependency to be the given 
    /// AcDbCompoundObjectId.
    /// </para><para>
    /// Unlike attachToObject(), it does not add this dependency to the list of
    /// persistent reactors of the object. Therefore the dependency is in limbo,
    /// neither attached nor non-attached. To really attach this dependency 
    /// to an object after setDependentOnObject() has already been called with a
    /// non-null AcDbObjectId, setDependentOnObject() needs to be called first 
    /// with a null compoundId before attachToObject() is called.
    /// </para> <para>
    /// This method can mess-up the dependency and the client code should not
    /// have (m)any reasons to call it.
    /// </para> </summary>
    /// <param name="compoundId"> 
    /// The AcDbCompoundObjectId the dependency should depend-on (may be null).
    /// </param>
    ///
    void setDependentOnObject(const AcDbCompoundObjectId& compoundId);

    /// <summary> 
    /// Gets the first dependency on the given AcDbObject. Dependencies are attached 
    /// to AcDbObjects in the form of persistent reactors and are ordered on the
    /// object based on their order(). The first dependency in this ordered 
    /// list is returned.
    /// </summary> 
    /// <param name="pObject"> 
    /// The AcDbObject whose first dependency is requested. The object needs 
    /// to be open at least for read. 
    /// </param>
    /// <param name="firstDependencyId"> 
    /// The returned first dependency on the AcDbObject, or AcDbObjectId::kNull
    /// if there are no dependencies attached to the AcDbObject.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus getFirstDependencyOnObject(const AcDbObject* pObject, 
                                                        AcDbObjectId& firstDependencyId);

    /// <summary> 
    /// Gets all dependencies on the given AcDbObject. Dependencies are attached 
    /// to AcDbObjects in the form of persistent reactors and are ordered on the
    /// object based on their order(). The retuned array contains the dependencies
    /// properly ordered.
    /// </summary>
    /// <param name="pObject"> 
    /// The AcDbObject whose dependencies are requested. The object needs 
    /// to be open at least for read. 
    /// </param>
    /// <param name="readDependenciesWanted">  Read-type dependencies wanted. </param>
    /// <param name="writeDependenciesWanted"> Write-type dependencies wanted. </param>
    /// <param name="dependencyIds"> Returned AcDbObjectIds of the AcDbAssocDependencies. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus getDependenciesOnObject(const AcDbObject* pObject, 
                                                     bool readDependenciesWanted, 
                                                     bool writeDependenciesWanted,
                                                     AcDbObjectIdArray& dependencyIds);

    /// <summary> 
    /// Gets all dependencies on the given AcDbObject and notifies them about a
    /// change by setting their status. It notifies both the primary dependencies
    /// on the object (when the object is the dependentOnObject() of the dependency) 
    /// as well as secondary dependencies (when the object is one of the objects
    /// in the AcDbCompoundObjectId of the dependency).
    /// </summary>
    /// <param name="pObject"> 
    /// The AcDbObject whose dependencies are to be notified. The object needs 
    /// to be open at least for read. 
    /// </param>
    /// <param name="newStatus"> The new status to be set to the dependencies. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus notifyDependenciesOnObject(const AcDbObject* pObject,
                                                        AcDbAssocStatus   newStatus);

    /// <summary> <para>
    /// Returns whether some dependency methods delegate to the action that
    /// owns the dependency if the method is not directly implemented in the
    /// dependency or in the AcDbAssocDependencyBody object that the dependency
    /// may own. The default is true, i.e. the delegation takes place. 
    /// Examples of dependency methods that perform the delegation to the owning 
    /// action are methods like isRelevantChange(), hasCachedValue(), isEqualTo(),
    /// isDependentOnTheSameThingAs(), evaluate(), etc.
    /// </para> <para>
    /// The reason for this delegation is to give developers of custom actions
    /// more freedom in their choice where to keep the data related to the 
    /// dependencies owned by their custom actions, and to reduce the need
    /// to derive new dependency body classes.
    /// </para> </summary>
    /// <returns> 
    /// Returns whether some dependency methods delegate to the owning action.
    /// The default is yes, i.e. the dependencies do delegate.
    /// </returns>
    /// 
    bool isDelegatingToOwningAction() const;

    /// <summary> <para>
    /// Controls whether some dependency methods delegate to the action that
    /// owns the dependency if the method is not directly implemented in the
    /// dependency or in the AcDbAssocDependencyBody object that the dependency
    /// may own. The default is true, i.e. the delegation takes place. 
    /// Examples of dependency methods that perform the delegation to the owning 
    /// action are methods like isRelevantChange(), hasCachedValue(), isEqualTo(),
    /// isDependentOnTheSameThingAs(), evaluate(), etc.
    /// </para> <para>
    /// The reason for this delegation is to give developers of custom actions
    /// more freedom in their choice where to keep the data related to the 
    /// dependencies owned by their custom actions, and to reduce the need
    /// to derive new dependency body classes.
    /// </para> </summary>
    /// <param name="yesNo"> 
    /// Controls whether some dependency methods delegate to the owning action.
    /// The default is yes, i.e. the dependencies do delegate.
    /// </param>
    ///
    void setIsDelegatingToOwningAction(bool yesNo);

    /// <summary> <para>
    /// Returns true iff the dependency currently holds the cached value of the 
    /// "thing" it depends on. It does not necessarily mean that the cached value
    /// is current and the same as the current value of the dependent-on "thing". 
    /// If the thing changed, the cached value the dependency holds may still be 
    /// the previously cached value. But if the dependency status is 
    /// kIsUpToDateAssocStatus, the cached value should be in sync with the 
    /// "thing" the dependency depends on.
    /// </para> <para>
    /// The default implementation of this predicate calls the owning 
    /// action's AcDbAssocAction::hasDependencyCachedValue(), i.e. it delegates 
    /// the decision to the action that owns the dependency. This delegation 
    /// can be turned off by calling setIsDelegatingToOwningAction(false). The 
    /// default implementation of AcDbAssocAction::hasDependencyCachedValue(),
    /// or if there is delegation, returns false. 
    /// </para> <para>
    /// If the dependency owns an AcDbAssocDependencyBody object that overrides 
    /// the hasCachedValueOverride() predicate, this predicate is called and it 
    /// supersedes the default implementation.
    /// </para> </summary>
    /// <returns>
    /// Returns true iff the dependency holds a cached value. By default
    /// returns false.
    /// </returns>
    ///
    bool hasCachedValue() const;

    /// <summary> <para>
    /// This predicate returns true iff the dependent-on "thing" really changed 
    /// in such a way that the change is relevant to this particular dependency 
    /// type. For example, if the dependency is on a subentity of a geometric 
    /// entity, it should check whether the geometry of this subentity is really
    /// different from what it was before (such as by comparing it with the 
    /// cached geometry).
    /// </para> <para>
    /// Using this predicate it is possible to filter-out false or irrelevant
    /// change notifications and thus avoid unnecessary action reevaluations.
    /// When this predicate returns false, the change notification from the
    /// dependent-on object is ignored and the status of this dependency is
    /// not changed.
    /// </para> <para>
    /// The default implementation of this predicate calls the owning 
    /// action's AcDbAssocAction::isRelevantDependencyChange() predicate, i.e. 
    /// it delegates the decision to the action that owns the dependency. This 
    /// delegation can be turned off by calling setIsDelegatingToOwningAction(false).
    /// The default implementation of AcDbAssocAction::isRelevantDependencyChange(),
    /// or if there is no delegation, returns true.
    /// </para> <para>
    /// If the dependency owns an AcDbAssocDependencyBody object that overrides 
    /// the isRelevantChangeOverride() predicate, this predicate is called and it 
    /// supersedes the default implementation.
    /// </para> </summary>
    /// <returns> 
    /// <para> true  = The object change is relevant (default). </para>
    /// <para> false = The object change is irrelevant and can be ignored. </para>
    /// </returns>
    ///
    bool isRelevantChange() const;

    /// <summary>
    /// Dependencies can be notified about arbitrary events using the following 
    /// method.
    /// </summary>
    ///
    Acad::ErrorStatus notification(AcDbAssocNotificationData* pNotifData);

    /// <summary> <para>
    /// This method returns  true iff this dependency depends on exactly the 
    /// same "thing" (such as on the same subentity of the same entity) as the
    /// other dependency.
    /// </para> <para>
    /// The default implementation compares the AcDbObjectIds of the 
    /// two dependent-on objects and if they are not equal, returns false.
    /// Otherwise it calls the owning action's
    /// AcDbAssocAction::areDependenciesOnTheSameThing(), i.e. it 
    /// delegates the decision to the action that owns the dependency. This 
    /// delegation can be turned off by calling setIsDelegatingToOwningAction(false). 
    /// The default implementation of AcDbAssocAction::areDependenciesOnTheSameThing(),
    /// or if there is no delegation, returns true.
    /// returns true
    /// </para> <para>
    /// If the dependency owns an AcDbAssocDependencyBody object that overrides 
    /// the isDependentOnTheSameThingAsOverride() predicate, this predicate is 
    /// called and it supersedes the default implementation.
    /// </para> </summary>
    /// <param name="pOtherDependency"> The other dependency needs to be open for read. </param>
    /// <returns> 
    /// <para> true  = Both dependencies depend on exactly the same "thing". </para> 
    /// <para> false = They depend on different "things". </para> 
    /// </returns>
    ///
    bool isDependentOnTheSameThingAs(const AcDbAssocDependency* pOtherDependency) const;

    /// <summary>
    /// Returns true iff the dependent on object is read-only, i.e. the object
    /// is not allowed to be changed. The default implementation returns true
    /// if the dependent-on object is an AcDbEntity on locked layer, otherwise 
    /// it returns false.
    /// </summary>
    /// <returns> True the dependent-on object is not allowed to be changed. </returns>
    ///
    bool isDependentOnObjectReadOnly() const;

    /// <summary> <para>
    /// Compares this dependency with the given dependency and returns true if 
    /// and only if they are equal (whatever it means). Both dependencies need
    /// be open at least for read.
    /// </para> <para>
    /// The default implementation does some general tests and if they turn
    /// out that the dependencies are not equal, it returns false. Otherwise 
    /// it calls the owning action's AcDbAssocAction::areDependenciesEqual(),
    /// i.e. it delegates the decision to the action that owns the dependency.
    /// This delegation can be turned off by calling setIsDelegatingToOwningAction(false).
    /// The default implementation of AcDbAssocAction::areDependenciesEqual(), 
    /// or if there is no delegation, returns true. 
    /// </para> <para>
    /// If the dependency owns an AcDbAssocDependencyBody object that overrides 
    /// the isEqualToOverride() predicate, this predicate is called and it 
    /// supersedes the default implementation.
    /// </para> </summary>
    /// <param name="pOtherDependency"> The other dependency needs to be open for read. </param>
    /// <returns> True iff the two dependencies are equal. </returns>
    ///
    bool isEqualTo(const AcDbAssocDependency* pOtherDependency) const;

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

    /// <summary> <para>
    /// Called by the AcDbAssocAction::evaluateDependencies() to update the 
    /// "dirty" dependencies of the action. The custom dependency classes 
    /// can implement code to cache the dependent-on data in order to allow 
    /// filtering-out irrelevant notifications, or do some other work.
    /// </para> <para>
    /// The evalaute() method calls AcDbAssocDependencyBody::evaluateOverride() 
    /// to do the real work.
    /// </para> <para>
    /// If there is no owned dependency body object, the default implementation 
    /// calls AcDbAssocAction::evaluateDependency(), i.e. it delegates the work 
    /// to the action that owns the dependency. The default implementation of 
    /// AcDbAssocAction::evaluateDependency() just sets the dependency status 
    /// to kIsUpToDateAssocStatus. This delegation can be turned off by calling
    /// setIsDelegatingToOwningAction(false).
    /// </para> </summary>
    ///
    void evaluate();

    /// <summary> <para>
    /// Implementation of the persistent reactor notification callback. 
    /// </para> <para>
    /// If the dependency owns an AcDbAssocDependencyBody object, its 
    /// erasedOverride() method is called at the end of the default 
    /// implementation.
    /// </para> </summary>
    /// <param name="dbObj"> </param>
    /// <param name="isErasing"> </param>
    ///
    virtual void erased(const AcDbObject* dbObj, Adesk::Boolean isErasing = true) override;

    /// <summary> <para>
    /// Implementation of the persistent reactor notification callback. 
    /// </para> <para>
    /// If the dependency owns an AcDbAssocDependencyBody object, its 
    /// modifiedOverride() method is called at the end of the default 
    /// implementation.
    /// </para> </summary>
    /// <param name="dbObj"> </param>
    ///
    virtual void modified(const AcDbObject* dbObj) override;

    /// <summary> <para>
    /// Implementation of the persistent reactor notification callback. 
    /// </para> <para>
    /// If the dependency owns an AcDbAssocDependencyBody object, its
    /// clonedOverride() method is called. After that the owning action's 
    /// AcDbAssocAction::dependentObjectCloned() callback method is called 
    /// to notify the action that an object the action depends on has been 
    /// cloned.
    /// </para> </summary>
    /// <param name="pDbObj"> The original object. </param>
    /// <param name="pNewObj"> The newly created clone. </param>
    ///
    virtual void copied(const AcDbObject* pDbObj, const AcDbObject* pNewObj) override;

private:
    void setPrevDependencyOnObject(const AcDbObjectId& depId);
    void setNextDependencyOnObject(const AcDbObjectId& depId);

    friend class AcDbImpAssocDependency;
    friend class AcDbAssocDeepCloneRxEventReactor;
    friend class AcDbAssocDeepCloneData;

}; // class AcDbAssocDependency



/// <summary>
/// Allows to disable change notifications to AcDbAssocDependencies.
/// </summary> 
///
class ACDBCORE2D_PORT AcDbAssocDependencyNotificationDisabler
{
public: 
    explicit AcDbAssocDependencyNotificationDisabler(bool disableIt = true);
    ~AcDbAssocDependencyNotificationDisabler();
    static bool isDisabled();
private:
    const bool mPrev;
};


#pragma pack ( pop )
