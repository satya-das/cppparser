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
// AcDbAssocManager class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcString.h"
#include "AcDbAssocGlobal.h"
#pragma pack (push, 8)
#pragma warning( push )
#pragma warning( disable : 4275 ) //suppress compilation warning 4275
                                  //"An exported class was derived from 
                                  // a class that was not exported"

/// <summary> <para>
/// This class currently just contains static methods to evaluate the top-level
/// network of a given database and to add/remove global evaluation callbacks.
/// </para> <para>
/// There is currently no need to create an object of AcDbAssocManager class and 
/// add it to the database, but this object is still derived from AcDbObject,
/// in case in the future there is a need to have a database-resident instance
/// of AcDbAssocManager class that might keep additional data.
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocManager : public AcDbObject
{
public:     
    ACRX_DECLARE_MEMBERS(AcDbAssocManager);

    /// <summary> Default constructor. </summary>
    ///
    AcDbAssocManager();

    /// <summary><para>
    /// Evaluates the top-level AcDbAssocNetwork of the given database, using the
    /// global evaluation callback. The top-level network owns subnetworks, such 
    /// as subnetworks owned by the individual AcDbBlockTableRecords. Notice that 
    /// the top-level network owns its subentworks in logical sense, but not 
    /// necessarily in AutoCAD database ownership sense. See addAction() and
    /// getInstanceFromObject() methods of AcDbAssocNetwork class for more details.
    /// </para><para>
    /// Evaluating the top-level network evaluates all the subnetworks that need 
    /// to be evaluated.
    /// </para><para>
    /// When a sub-network owned by an AcDbBlockTableRecord becomes empty, i.e. 
    /// containing no actions, is is erased at the end of the evaluation of the 
    /// top-level network. Also, when the top-level network becomes empty, it is
    /// erased. When an AcDbAssoc2dConstraintGroup becomes empty, i.e. not having 
    /// any dependencies on AcDbEntities, it is erased at the end of its evaluation.
    /// </para><para>
    /// The client code needs to explicitly evaluate the top-level network when
    /// it adds several new actions in a row. When an action is added, and the 
    /// action depends on another action that has just been added to the network, 
    /// the network should be evaluated before adding the next action. The reason 
    /// is that the action being added may need some information that is calculated 
    /// by evaluating the other action that has already been added to the network. 
    /// If the other action is not evaluated, the action being added will not have 
    /// this information available and may not be connect correctly to and interact 
    /// correctly with the other action.
    /// </para><para>
    /// In most other cases the client code does not need to evaluate the top-level
    /// network explicitly. It is happening automatically on document lock mode 
    /// change and also during dragging, on every drag sample.
    /// </para></summary>
    /// <param name="pDatabase"> Database whose top-level network is to be evaluated. </param>
    /// <param name="pCallback"> Optional AcDbAssocEvaluationCallback that is 
    /// added to the global callback before the evaluation and removed after the
    /// evaluation is completed. </param>
    /// <param name="callbackOrder"> Order of the optional AcDbAssocEvaluationCallback. </param>
    /// <returns> Returns true if any evaluation happened, false otherwise. </returns>
    ///
    static bool evaluateTopLevelNetwork(AcDbDatabase*                pDatabase,
                                        AcDbAssocEvaluationCallback* pCallback     = NULL, 
                                        int                          callbackOrder = 0);

    /// <summary> <para>
    /// Returns the global AcDbAssocEvaluationCallback that is used while dragging,
    /// when evaluating the top-level associative network on document lock mode 
    /// change, or anytime AcDbAssocManager::evaluateTopLevelNetwork() is explicitly 
    /// called by the client code. 
    /// </para> <para>
    /// It is actually an object of AcDbAssocEvaluationMultiCallback class 
    /// (this class is currently not exposed, but may be expossed if needed) 
    /// that keeps a vector of AcDbAssocEvaluationCallbacks and sequentially calls 
    /// all the individual callbacks. The returned AcDbAssocEvaluationMultiCallback
    /// object must not be modified or deleted by the caller.
    /// </para> <para>
    /// During dragging, the dragging evaluation callback is temporarily inserted 
    /// into this global multi-callback with order 0 and is removed after the 
    /// dragging is finished.
    /// </para> </summary>
    /// <returns> The global AcDbAssocEvaluationMultiCallback object. </returns>
    ///
    static AcDbAssocEvaluationCallback* globalEvaluationMultiCallback();

    /// <summary>
    /// Adds the given user-provided AcDbAssocEvaluationCallback to the global 
    /// AcDbAssocEvaluationMultiCallback.
    /// </summary>
    /// <param name="pCallback"> 
    /// The user-provided evaluation callback. The callback does not become owned 
    /// by the global AcDbAssocEvaluationMultiCallback, it is just referenced by it.
    /// </param>
    /// <param name="order"> 
    /// Specifies the ordering of the user-provided callbacks in the global
    /// AcDbAssocEvaluationMultiCallback. The lower-order callbacks are called
    /// before the higher-order callbacks. The drag callback is inserted with
    /// order 0, i.e. callbacks with negative order will be called before 
    /// it and callbacks with positive order will be called after it.
    /// </param>
    /// <returns> 
    /// Acad::eInvalidInput if pCallback pointer is NULL, otherwise Acad::eOk.
    /// </returns>
    ///
    static Acad::ErrorStatus addGlobalEvaluationCallback(AcDbAssocEvaluationCallback* pCallback, int order);

    /// <summary>
    /// Removes the given user-provided evaluation callback from the global 
    /// AcDbAssocEvaluationMultiCallback.
    /// </summary>
    /// <param name="pCallback"> 
    /// The user-provided evaluation callback to be removed.
    /// </param>
    /// <returns> 
    /// Acad::eInvalidInput if pCallback pointer not found in the global 
    /// AcDbAssocEvaluationMultiCallback, otherwise Acad::eOk.
    /// </returns>
    ///
    static Acad::ErrorStatus removeGlobalEvaluationCallback(AcDbAssocEvaluationCallback* pCallback);

    /// <summary>
    /// Returns all evaluation callbacks kept in the global AcDbAssocEvaluationMultiCallback.
    /// </summary>
    /// <param name="callbacks"> The returned evaluation callbacks. </param>
    /// <param name="orders"> The returned evaluation callback orders. </param>
    ///
    static void getGlobalEvaluationCallbacks(AcArray<AcDbAssocEvaluationCallback*>& callbacks,
                                             AcArray<int>&                          orders);

    /// <summary>
    /// Returns true if action evaluation is currently in progress for the given
    /// database.
    /// </summary>
    ///
    static bool isActionEvaluationInProgress(const AcDbDatabase*);

    /// <summary><para>
    /// Allows the custom action body's evaluateOverride() code or any other code to request 
    /// one more evaluation of the top-level network of a database, even if the top-level network 
    /// is already currently being evaluated, all actions to evaluate have already been transitively 
    /// collected, and are currently being evaluated. It does it by waiting till the current top-level 
    /// network evaluation has been completed, setting the requested newStatus of the actions and
    /// dependencies by calling AcDbAssocAction/Dependency::setStatus() on them, and evaluating the 
    /// same top-level network again. 
    /// </para><para>
    /// The objectId may be of an action (the most common case), dependency, or of an arbitrary object. 
    /// The meaning is the same as in AcDbActionsToEvaluateCallback::needsToEvaluate() callback method,
    /// i.e. if it is an arbitrary object, not an action or a dependency, it calls setStatus() on
    /// all dependencies on that object.
    /// </para><para>
    /// The newStatus needs to be one of kChangedDirectlyAssocStatus, kChangedTransitivelyAssocStatus, 
    /// or kChangedNoDifferenceAssocStatus. If it is kErasedAssocStatus, the action, dependency or
    /// object is erased before the top-level network is evaluated again.
    /// </para><para>
    /// If not in the middle of evaluation of the top level network of the same database as is the 
    /// database of the objectId, this call just directly sets the status of the action or dependency,
    /// or of all dependencies on the objects, if objectId is of an arbitrary object. It does not
    /// trigger the top-level network evaluation of the database, but the status of actions and 
    /// dependencies has been changed, so that when the top-level network evaluation happens later,
    /// these actions will get evaluated.
    /// </para><para>
    /// Eventually this method might get called automatically anytime AcDbAssocAction/Dependency::setStatus() 
    /// is called in the middle of evaluation of the same database, and newStatus is an evaluation 
    /// request or kErasedAssocStatus. But until it happens automatically, it is up to the client code 
    /// to explicitly call this method when needed, to trigger one more evaluation of the same 
    /// top-level network as is currently being evaluated.
    /// </para></summary>
    ///
    static Acad::ErrorStatus requestToEvaluate(const AcDbObjectId& objectId, 
                                               AcDbAssocStatus     newStatus        = kChangedDirectlyAssocStatus,
                                               bool                ownedActionsAlso = true);

    /// <summary>
    /// Returns the current AcDbAssocEvaluationCallback if action evaluation is in
    /// progress for the given database, or NULL otherwise.
    /// </summary>
    ///
    static AcDbAssocEvaluationCallback* getCurrentEvaluationCallback(const AcDbDatabase*);

    /// <summary>
    /// Returns true iff the given database has some associative data, in particular
    /// if there is a global AcDbAssocNetwork for the whole database. See the
    /// related AcDbAssocNetwork::getInstanceFromDatabase() method.
    /// </summary>
    ///
    static bool hasAssocNetwork(const AcDbDatabase* pDatabase);

    /// <summary>
    /// Returns the action of the given database that is currently being evaluated,
    /// or AcDbObjectId::kNull is no evaluation of the top-level network of the database 
    /// is happening.
    /// </summary>
    ///
    static AcDbObjectId currentlyEvaluatedAction(const AcDbDatabase*);

    /// <summary>
    /// Audits the associative data in the database and tries to fix the errors
    /// that might have happened during round-trip, due to lazy-erase, etc.
    /// </summary>
    /// <param name="pDatabase"> AcDbDatabase whose associative data is to be audited. </param>
    /// <param name="traverseWholeDatabase"> If true, all objects in the database
    /// are visited and checked, and therefore loaded into memory. </param>
    ///
    static Acad::ErrorStatus auditAssociativeData(AcDbDatabase* pDatabase, bool traverseWholeDatabase);

    /// <summary><para> 
    /// If the given database is a host database, sets an internal flag indicating
    /// that AcDbAssocActions in the host database may need to sync-up with changed 
    /// objects in changed XREF database(s). If the given database is an XREF database, 
    /// sets an internal flag indicating that that AcDbAssocActions in the host database 
    /// need to unconditionally sync up with objects in this XREF database. It also sets 
    /// the flag in the host database.
    /// </para?<para>
    /// This method is automatically called during XREF attach, XREF reload and other 
    /// XREF-releated operations during which contents of XREFs may change. This method
    /// generally does not need to be called by client code.
    /// </para></summary>
    /// <param name="pDatabase"> Host or XREF database. </param>
    ///
    static Acad::ErrorStatus markSyncUpWithXrefsNeeded(AcDbDatabase* pDatabase);

    /// <summary>
    /// If the given host database does not have a flag set indicating that it may 
    /// need to sync-up with changed XREFs (see markSyncUpWithXrefsNeeded() mthod), 
    /// this method does nothing and returns. Otherwise it visits all BTRs in the 
    /// host database that represent XREF databases. If associative data in the host 
    /// database are out-of-sync with the current version of the XREF database, 
    /// marks all dependencies of AcDbAssocActions in the host database on objects 
    /// in the XREF database with kChangedDirectlyAssocStatus so that these actions 
    /// later evaluate and sync-up with objects in the current version of the 
    /// XREF database.
    /// <remarks>
    /// As this operation is trivial when no sync-up with XREFs is needed, 
    /// it may be called frequently w/o any performance penalty. It is called
    /// during every evaluation triggered by a document lock mode change, roughly
    /// corresponding to the beginning and end of every command.
    /// </remarks>
    /// </summary>
    /// <param name="pHostDatabase"> Host database. XREF databases are ignored. </param>
    ///
    static Acad::ErrorStatus syncUpWithXrefs(AcDbDatabase* pHostDatabase);

    /// <summary>
    /// This is an internal method that initializes the Associative Framework 
    /// subsystem. Must be called before the subsystem is first used and may 
    /// safely be called more than once. There is no need for the client code
    /// to call this method.
    /// </summary>
    /// <returns> Should always return Acad::eOk. </returns>
    ///
    static Acad::ErrorStatus initialize();

    /// <summary>
    /// This is an internal method that uninitializes the Associative Framework 
    /// subsystem during AutoCAD shutdown. Client code must not call this method.
    /// </summary>
    ///
    static void uninitialize();
    
    /// <summary>
    /// Enable/disable the progress meter while evaluating the top-level network.
    /// Once set, it stays enabled/disabled for all evaluations of all databases,
    /// until it is set again.
    /// </summary>
    /// <param name="enableIt"> Enable or disable the prgress meter. </param>
    /// <param name="progressLabel"> Text label to display. </param>
    ///
    static void enableProgressMeter(bool enableIt, const AcString& progressLabel = AcString());

}; // class AcDbAssocManager


/// <summary>
/// The constructor disables or enables all top-level network evaluations for the 
/// given database. The destructor reverts back to the previous state. By default
/// the database evaluations are enabled and there should not be many reasons to
/// forcefully disable all evaluations. 
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocNetworkEvaluationDisabler
{
public:
    explicit AcDbAssocNetworkEvaluationDisabler(AcDbDatabase*, bool disableIt = true);
    ~AcDbAssocNetworkEvaluationDisabler();
    static bool isDisabled(const AcDbDatabase*);

private:
    AcDbDatabase* mpDatabase;
    bool          mPreviouslyDisabled;
};

#pragma warning( pop ) 
#pragma pack (pop)

