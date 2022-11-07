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
// Global definitions needed across the whole Associative Framework. 
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning (disable: 4996)
#include "AcDbCore2dDefs.h"
#include "acdb.h"
#include "gepnt3d.h"
#pragma pack (push, 8)


// Forward class declarations of the main classes of the Associative Framework.
//
class AcDbAssocAction;
class AcDbAssocActionBody;
class AcDbAssocNetwork;
class AcDbAssocDependency;
class AcDbAssocDependencyBody;
class AcDbAssocGeomDependency;
class AcDbAssoc2dConstraintGroup;
class AcDbAssocPersSubentId;
class AcDbAssocSimplePersSubentId;
class AcDbAssocSingleEdgePersSubentId;
class AcDbAssocIndexPersSubentId;
class AcDbAssocExternalIndexPersSubentId;
class AcDbAssocPersSubentIdPE;
class AcDbAssocVariable;
class AcDbAssocValueDependency;
class AcDbAssocValueProviderPE;
class AcDbEvalContext;
class AcDbAssocPersSubentManager;
class AcDbAssocPersSubentManagerPE;
class AcDbAssocPersSubentManagerCloner;
class AcDbAssocNotificationData;

namespace PersSubentNaming
{
	class AnnotationData;
    class PersSubentManager;
}

// ASM entities
//
class ENTITY;
class COEDGE;
class EDGE;
class LOOP;
class FACE;
class SHELL;
class LUMP;
class BODY;
typedef AcArray<BODY*>            AcDbAsmBodyArray;
typedef AcArray<ENTITY*>          AcDbAsmEntityArray;
typedef AcArray<EDGE*>            AcDbAsmEdgeArray;
typedef AcArray<FACE*>            AcDbAsmFaceArray;
typedef AcArray<AcDbAsmEdgeArray> AcDbAsmEdgeArray2d;


/// <summary>
/// The status of AcDbAssocActions and AcDbAssocDependencies. In case of an
/// action it relates to the action itself, in case of a dependency it relates
/// to the object the dependency depends on.
/// </summary>
///
enum AcDbAssocStatus
{
    /// <summary> Everything is in sync. </summary> 
    kIsUpToDateAssocStatus = 0,

    /// <summary> Explicitly changed (such as by the user). </summary> 
    kChangedDirectlyAssocStatus,

    /// <summary> Changed indirectly due to something else changed. </summary> 
    kChangedTransitivelyAssocStatus,

    /// <summary> No real change, only forces to evaluate. </summary> 
    kChangedNoDifferenceAssocStatus, 

    /// <summary> Action failed to evaluate but evaluation continues. 
    /// Otherwise identical to kIsUpToDateAssocStatus. </summary> 
    kFailedToEvaluateAssocStatus,

    /// <summary> Dependent-on object erased or action is to be erased. </summary> 
    kErasedAssocStatus,

    /// <summary> Action evaluation suppressed, treated as if evaluated. </summary> 
    kSuppressedAssocStatus,  

    /// <summary> Dependent-on object is un-resolved (e.g the xref is unloaded). </summary> 
    kUnresolvedAssocStatus,  
};


/// <summary>
/// Returns the severity level (positive integer) of those status values that
/// indicate a request for an AcDbAssocAction or an AcDbAssocDependency to be
/// evaluated, or 0 if the status does not indicate an evaluation request.
/// Higher numbers mean more "severe" requests to evaluate.
/// </summary>
/// <param name="status"> The AcDbAssocStatus. </param>
/// <returns> 
/// Evaluation request severity level (positive integer) if or 0 if not a 
/// request to evaluate.
/// </returns>
///
inline int evaluationRequestSeverityLevel(AcDbAssocStatus status)
{
    switch (status)
    {
    case kChangedDirectlyAssocStatus:
        return 3;
    case kChangedTransitivelyAssocStatus:
        return 2;
    case kChangedNoDifferenceAssocStatus:
        return 1;
    default:
        return 0; // Not a request to evaluate
    }
}


/// <summary>
/// Returns true for the AcDbAssocStatus values that are a request for an 
/// AcDbAssocAction or AcDbAssocDependency to be evaluated, and false for 
/// other AcDbAssocStatus values.
/// </summary>
/// <param name="status"> The AcDbAssocStatus. </param>
/// <returns> 
/// Returns true iff the value of the AcDbAssocStatus indicates that an 
/// AcDbAssocAction or AcDbAssocDependency needs to be evaluated.
/// </returns>
///
inline bool isEvaluationRequest(AcDbAssocStatus status)
{
    return evaluationRequestSeverityLevel(status) > 0;
}


/// <summary>
/// Returns true iff the AcDbAssocStatus indicates that the action or dependency 
/// should be skipped and treated as it it were not there.
/// </summary>
/// <param name="status"> The AcDbAssocStatus. </param>
/// <returns> 
/// Returns true iff the AcDbAssocStatus indicates that the action or dependency 
/// should be skipped and treated as it it were not there.
/// </returns>
///
inline bool isToBeSkipped(AcDbAssocStatus status)
{
    return status == kErasedAssocStatus || status == kSuppressedAssocStatus;
}


/// <summary>
/// Negative numbers mean that an AcDbAssocAction cannot be evaluated at this 
/// time, positive numbers mean that the action can now be evaluated. Higher 
/// positive priority numbers mean that the action should be evaluated sooner, 
/// ahead of actions with lower positive priority. The negative numbers mean 
/// how much the action cannot be evaluated. The smaller the number, the less 
/// the action can be evaluated.
/// </summary>
///
enum AcDbAssocEvaluationPriority
{
    /// <summary> Default "can not be evaluated" priority. </summary>
    kCannotBeEvaluatedAssocEvaluationPriority = -1000,

    /// <summary> The action evaluatability cannot be determined at this time. </summary>
    kCannotDermineAssocEvaluationPriority = 0,

    /// <summary> Default "can be evaluated" priority. </summary>
    kCanBeEvaluatedAssocEvaluationPriority = 1000,
};


/// <summary>
/// At the beginning of AcDbAssocActionBody::evaluateOverride() implementation, 
/// the custom code needs to query the mode in which it should evaluate itself. 
/// </summary>
///
enum AcDbAssocEvaluationMode
{
    /// <summary> <para> 
    /// The standard action evaluation mode in which the objects the action 
    /// depends-on via write-dependencies are modified so that they satisfy 
    /// the requirements imposed on them by the action. 
    /// </para> <para>
    /// If this cannot be achieved, the action needs to report an error and 
    /// set its status to kFailedToEvaluateAssocStatus or possibly to 
    /// kErasedAssocStatus (if it wants itself to be erased.)
    /// </para> </summary>
    ///
    kModifyObjectsAssocEvaluationMode,

    /// <summary> <para> 
    /// The action evaluation mode in which the action is modified so that it 
    /// satisfies the objects the action depends on. The objects are not 
    /// modified, the internal data in the action or its dependencies are. An
    /// example is an AcDbAssoc2dConstraintGroup action that may remove the 
    /// constraints that are not satisfied by the current geometry configuration.
    /// </para> <para>
    /// If this cannot be achieved, the action needs to report an error and 
    /// set its status to kFailedToEvaluateAssocStatus or possibly to 
    /// kErasedAssocStatus (if it wants itself to be erased.)
    /// </para> </summary>
    ///
    kModifyActionAssocEvaluationMode,
};


/// <summary>
/// While in the middle of evaluation, the action may inquire the client code 
/// whether the evaluation is happening from inside of the dragging loop and 
/// at which stage the dragging is.
/// </summary>
///
enum AcDbAssocDraggingState
{
    /// <summary> Not inside the dragging loop. </summary>
    kNotDraggingAssocDraggingState,

    /// <summary> The first drag sample of the dragging loop. </summary>
    kFirstSampleAssocDraggingState,

    /// <summary> An intemediate drag sample of the dragging loop. </summary>
    kIntermediateSampleAssocDraggingState,

    /// <summary> The last drag sample of the dragging loop. </summary>
    kLastSampleAssocDraggingState,
};


/// <summary>
/// Information about what type of transformation (which AutoCAD command) has 
/// been performed with the entities before the actions that have dependencies
/// on these entities are evaluated.
/// </summary>
///
enum AcDbAssocTransformationType
{
    /// <summary> Transformation type not specified. </summary>
    kNotSpecified,

    /// <summary> Geometries have been changed through strech command. </summary>
    kStretch,

    /// <summary> Geometries have been changed through rotate command. </summary>
    kRotate,

    /// <summary> Geometries have been changed through move command. </summary>
    kMove,
};


/// <summary> <para>
/// A mechanism for AcDbAssocActions to notify about the progress of evaluation, 
/// to report success or failure, notify about which objects the action is
/// going to use and modify, to allow the evaluation to be cancelled by the
/// client, etc.
/// </para> <para>
/// Pointer to an object of AcDbAssocEvaluationCallback class in a mandatory
/// argument to the AcDbAssocAction::evaluate() method. AcDbAssocManager manages 
/// an ordered collection of global AcDbAssocEvaluationCallbacks grouped in an
/// AcDbAssocEvaluationMultiCallback. AcDbAssocManager::evaluateTopLevelNetwork() 
/// passes this multi-callback to the AcDbAssocAction::evaluate() method of the 
/// top-level network.
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocEvaluationCallback
{
public:

    /// <summary> Default constructor. </summary>
    AcDbAssocEvaluationCallback() {}

    /// <summary> Virtual destructor. </summary>
    virtual ~AcDbAssocEvaluationCallback() {}

    /// <summary> 
    /// The action needs to call this method at the beginning of the evaluate()
    /// code to obtain the mode in which it should evaluate itself. 
    /// The default implementation returns kModifyObjectsEvaluationMode.
    /// </summary>
    /// <returns> The requested evaluation mode. </returns>
    ///
    virtual AcDbAssocEvaluationMode evaluationMode() const { return kModifyObjectsAssocEvaluationMode; }

    /// <summary> 
    /// The action informs that it is starting its evaluation. This callback 
    /// is issued at the beginning of AcDbAssocAction::evaluate() call 
    /// and should not be issued from the individual evaluateOverride() method 
    /// calls. The action is open for write when this callback is issued.
    /// </summary>
    /// <param name="pAction"> The action that is being evaluated. </param>
    ///
    virtual void beginActionEvaluation(AcDbAssocAction* pAction) = 0;

    /// <summary> 
    /// The action informs that it has finished its evaluation. This callback
    /// is issued at the end of AcDbAssocAction::evaluate() call 
    /// and should not be issued from the individual evaluate() method calls.
    /// The action is open for write when this callback is issued.
    /// </summary>
    /// <param name="pAction"> The action that is being evaluated. </param>
    ///
    virtual void endActionEvaluation(AcDbAssocAction* pAction) = 0;

    /// <summary> 
    /// The action informs that an error happened during its evaluation. It does
    /// not need to inform if no error happened. The action may also inform about 
    /// which object caused the failure, giving its id, pointer or both, and 
    /// provide arbitrary additional info.
    /// </summary>
    /// <param name="pAction"> The action that is being evaluated. </param>
    /// <param name="errorStatus"> Action evaluation error status. </param>
    /// <param name="objectId"> The failed object id (such as of an AcDbAssocDependency). </param>
    /// <param name="pObject"> The failed object pointer (such as of an AcDbAssocDependency). </param>
    /// <param name="pErrorInfo"> Additional info about the error. </param>
    ///
    virtual void setActionEvaluationErrorStatus(AcDbAssocAction*    pAction,
                                                Acad::ErrorStatus   errorStatus,
                                                const AcDbObjectId& objectId   = AcDbObjectId::kNull,
                                                AcDbObject*         pObject    = NULL,
                                                void*               pErrorInfo = NULL) = 0;

    /// <summary> <para>
    /// The action informs that it is going to use or modify an AcDbObject. The 
    /// action issues this callback just before it opens the object for read or 
    /// write. 
    /// <para> </para>
    /// The custom evaluation callback code may pass back a pointer to a 
    /// substitute AcDbObject. If it happens, the action should use or modify this 
    /// substitute object instead of the original object. The substitute object 
    /// is expected to already be correctly open for read or write (if it is a 
    /// database-resident object), the action does not need to open or close it. 
    /// Also, the substitute object may possibly be a non-database-resident 
    /// object and the action should be ok with it.
    /// <para> </para>
    /// This allows the custom evaluation callback code to redirect the action 
    /// evaluation to use or modify other objects than the action depends on. 
    /// A common example is dragging, when the action may be redirected to use 
    /// and modify temporary non-database resident clones of the original objects. 
    /// The custom evaluation callback code creates non-database resident clones 
    /// of any relevant AcDbEnities when notified by the action that the action 
    /// is going to modify them, and the action then modifies these temporary 
    /// clones. The modified clones are then drawn and discarded, the original 
    /// objects remain untouched. 
    /// <para> </para>
    /// There is an AcDbAssocObjectPointer template class that is
    /// modelled after AcDbObjectPointer template class and that simplifies
    /// the client action evaluation code that needs to perform this redirection.
    /// The AcDbAssocObjectPointer constructor automatically calls
    /// the beginActionEvaluationUsingObject() method and the destructor calls
    /// the endActionEvaluationUsingObject() method. All the client code needs
    /// to do is to use this template class and then use the AcDbObject pointer
    /// this template class provides. The pointer will point either to the 
    /// original database-resident object or to the substitute object, if the 
    /// evaluation is in progress and the client evaluation callback provided 
    /// a substitute object.
    /// </para> </summary>
    /// <param name="pAction"> The action that is being evaluated. </param>
    /// <param name="objectId"> The AcDbObject that is going to be used or modified by the action. </param>
    /// <param name="objectIsGoingToBeUsed"> The object contents is going to be used. </param>
    /// <param name="objectIsGoingToBeModified"> The object contents is going to be modified. </param>
    /// <param name="pSubstituteObject"> 
    /// An AcDbObject optionally provided by the custom evaluation callback code. 
    /// The custom evaluation callback code should not assign NULL to this output 
    /// argument if it does not want to provide a substitute object. It should 
    /// only assign a non-NULL pointer if it intends to provide a substitute object.
    /// </param>
    ///
    virtual void 
    beginActionEvaluationUsingObject(AcDbAssocAction*    pAction, 
                                     const AcDbObjectId& objectId, 
                                     bool                objectIsGoingToBeUsed,
                                     bool                objectIsGoingToBeModified,
                                     AcDbObject*&        pSubstituteObject) = 0;

    /// <summary> 
    /// The action informs that it is done with using or modifying an AcDbObject. 
    /// The action issues this callback just before it closes the object. If the 
    /// object is a substitute object provided by the client code, the action 
    /// does not close it.
    /// </summary>
    /// <param name="pAction"> The action that is being evaluated. </param>
    /// <param name="objectId"> 
    /// The same AcDbObjectId that has been previously passed to the matching
    /// beginActionEvaluationUsingObject() callback.
    /// </param>
    /// <param name="pObject"> 
    /// The object that has been used or modified by the action. It may be NULL
    /// if the original object couldn't be opened or if the substitute object 
    /// was not of the expected type.
    /// </param>
    ///
    virtual void endActionEvaluationUsingObject(AcDbAssocAction*    pAction, 
                                                const AcDbObjectId& objectId, 
                                                AcDbObject*         pObject) = 0;

    /// <summary> <para>
    /// Called during the network evaluation to notify that all actions that need to
    /// be evaluated have been marked to evaluate. This concludes the first phase of
    /// the evaluation process. After this notification all the marked actions are 
    /// then sequentially evaluated. 
    /// </para><para>
    /// The notification is only issued once, for the top-level network that is being 
    /// evaluated, not for the individual subnetworks of the top-level network.
    /// </para></summary>
    /// <param name="pNetwork"> AcDbAssocNetwork whose all actions that need to 
    /// be evaluated have been marked to evaluate. 
    /// </param>
    ///
    virtual void allDependentActionsMarkedToEvaluate(AcDbAssocNetwork* /*pNetwork*/) {
    }

    /// <summary> 
    /// The action may inquire the client code whether the evaluation is 
    /// happening from inside of the dragging loop and at which stage the 
    /// dragging is. The custom evaluation callback code may provide this 
    /// information by implementing this callback.
    /// </summary>
    /// <returns> Returns the dragging state. </returns>
    ///
    virtual AcDbAssocDraggingState draggingState() const { return kNotDraggingAssocDraggingState; }

    /// <summary> <para>
    /// The custom evaluation callback code can request that the action evaluation 
    /// should be cancelled by implementing this callback predicate. The 
    /// AcDbAssocAction::evaluate() method checks this predicate just after 
    /// issuing the beginActionEvaluation() callback, i.e. just before the action 
    /// evaluateOverride() method is called. If a whole associative network is 
    /// evaluated, this predicate is also checked after evaluating each action 
    /// in the network to see if the network evaluation should continue. Custom 
    /// actions can freely add their own calls to check this predicate, 
    /// particularly if the action evaluation is time consuming. 
    /// </para> <para>
    /// Once this predicate returns true, requesting the evaluation to be 
    /// cancelled, it should keep returning true, to make sure the evaluation
    /// of the whole associative network is cancelled.
    /// </para> <para>
    /// When the evaluation is cancelled, the status of the not-yet evaluated 
    /// actions/networks stays unchanged. The status of the actions/networks 
    /// that have already been evaluated also stays unchanged, i.e. there is no
    /// roll-back of the already made changes. 
    /// </para> <para>
    /// This predicate should be used to cancel the evaluation of the whole
    /// associative network, not to selectively control the evaluation of the
    /// individual actions. To selectively enable/disable the evaluation of 
    /// individual actions, the beginActionEvaluation() callback can bse used. 
    /// Inside this callback the client code can change the status of the action 
    /// being evaluated to a status that is not an evaluation request, such as 
    /// change it to kSuppressedAssocStatus, kFailedToEvaluateAssocStatus, 
    /// kIsUpToDateAssocStatus, and the action is then not going to be evaluated.
    /// </para> </summary>
    /// <returns> Returns true iff the evaluation should be cancelled. </returns>
    ///
    virtual bool cancelActionEvaluation() { return false; }

    /// <summary> 
    /// Allows the custom evaluation callback code to pass arbitrary data 
    /// to the actions that are being evaluated. The default implementation 
    /// returns NULL.
    /// </summary> 
    /// <returns> Pointer to AcDbEvalContext or NULL. </returns>
    ///
    virtual AcDbEvalContext* getAdditionalData() const { return NULL; }

    /// <summary> 
    /// Allows the custom evaluation callback code to pass information about what 
    /// type of transformation (which AutoCAD command) has been performed with 
    /// the entities prior to action evaluation. The default implementation 
    /// returns kNotSpecified.
    /// </summary> 
    /// <returns> AcDbAssocTransformationType. </returns>
    ///
    virtual AcDbAssocTransformationType getTransformationType() const { return kNotSpecified; }

}; // class AcDbAssocEvaluationCallback


/// <summary>
/// Returns true iff in the middle of dragging and the AcDbAssocDraggingState 
/// indicates that the dragger is providing substitute non-database resident
/// objects that are clones of the original database-resident objects.
/// </summary>
/// <param name="pEvaluationCallback"> 
/// The current AcDbAssocEvaluationCallback. NULL pointer is allowed.
/// </param>
///
inline bool isDraggingProvidingSubstituteObjects(const AcDbAssocEvaluationCallback* pEvaluationCallback)
{
    if (pEvaluationCallback == NULL)
        return false;

    const AcDbAssocDraggingState draggingState = pEvaluationCallback->draggingState();

    return draggingState == kFirstSampleAssocDraggingState || 
           draggingState == kIntermediateSampleAssocDraggingState;
}


/// <summary>
/// This callback is used by AcDbAssocAction::getDependentActionsToEvaluate() 
/// method to inform about other actions, dependencies or arbitrary objects that 
/// should also be evaluated because they depend on the given action that is to 
/// be evaluated.
/// </summary>
///
class ACDBCORE2D_PORT AcDbActionsToEvaluateCallback
{
public:
    /// <summary> Default constructor. </summary>
    AcDbActionsToEvaluateCallback() {}

    /// <summary> Virtual destructor. </summary>
    virtual ~AcDbActionsToEvaluateCallback() {}

    /// <summary> <para>
    /// This callback method is called by AcDbAssocAction::getDependentActionsToEvaluate().
    /// It is a mechanism by which getDependentActionsToEvaluate() informs that 
    /// an AcDbAssocAction, AcDbAssocDependency, or an AcDbObject needs to be 
    /// evaluated and suggests new status for them that the callback implementation 
    /// should set. If the given AcDbObjectId is not of an action or of a dependency, 
    /// but of an arbitrary AcDbObject, the callback implementation should simply 
    /// recursively call needsToEvaluate() for all dependencies on that object.
    /// </para> <para>
    /// This callback does not need to be implemented by the client code. The 
    /// Associative Framework evaluation mechanism provides a default implementation 
    /// that it uses when calculating a transitive closure of all actions that 
    /// need to be evaluated.
    /// </para> </summary>
    /// <param name="objectId"> 
    /// AcDbObjectId of an AcDbAssocAction, AcDbAssocDependency or an arbitrary 
    /// AcDbObject that needs to be evaluated. 
    /// </param>
    /// <param name="newStatus"> 
    /// The new evaluation request status of the action or dependency. If it
    /// is not an evaluation request, the needsToEvaluate() implementation 
    /// should not change the status of the action or dependency.
    /// </param>
    /// <param name="ownedActionsAlso"> 
    /// If the action that needs to evaluate is an AcDbAssocNetwork, this argument
    /// controls whether all the actions owned by the network also need to be 
    /// evaluated. The caller usually passes true.
    /// </param>
    ///
    virtual void needsToEvaluate(const AcDbObjectId& objectId, 
                                 AcDbAssocStatus     newStatus,
                                 bool                ownedActionsAlso = true) = 0;

}; // class AcDbActionsToEvaluateCallback


/// <summary> <para> 
/// This is mostly for internal use.
/// </para> <para>
/// A way to tell the API class constructor whether it should create the 
/// corresponding imp object derived from AcDbImpObject, or whether the derived 
/// API class constructor is going to create its derived imp object.
/// </para> <para>
/// When the base class constructor is called from the derived class 
/// constructor, the AcDbAssocCreateImpObject argument should be passed as 
/// kAcDbAssocDoNotCreateImpObject so that the base class does not create an 
/// imp object, the derived class constructor will create its own derived-class 
/// imp object. When the base class constructor is called by client code in 
/// order to create a concrete object, the AcDbAssocCreateImpObject argument 
/// should be passed as kAcDbAssocCreateImpObject, or omitted, and the constructor
/// will then create the corresponding imp object.
/// </para> </summary>
///
enum ACDBCORE2D_PORT AcDbAssocCreateImpObject
{
    /// <summary> The API class should create the corresponding imp object. </summary> 
    kAcDbAssocCreateImpObject = 0,

    /// <summary> The API class should not create the corresponding imp object. </summary> 
    kAcDbAssocDoNotCreateImpObject = 1,
};


// The following typedefs are ids used by AcDbAssocPersSubentManager
//
typedef unsigned                       AcDbPersElemId;
typedef AcDbPersElemId                 AcDbPersStepId;
typedef AcDbPersElemId                 AcDbPersSubentId;
typedef AcArray<AcDbPersElemId>        AcDbPersElemIdArray;
typedef AcArray<AcDbPersStepId>        AcDbPersStepIdArray;
typedef AcArray<AcDbPersSubentId>      AcDbPersSubentIdArray;
typedef AcArray<AcDbPersElemIdArray>   AcDbPersElemIdArray2d;

const AcDbPersElemId kAcDbPersNullId = 0;

// For debugging. When a network, action or dependency in the top-level network 
// or any of its subnetworks has some integrity issues, it asserts and returns 
// not eOk. It mainly checks general integrity issues, not issues specific to 
// the particular action body types
//
ACDBCORE2D_PORT Acad::ErrorStatus checkTopLevelNetworkIntegrity(const AcDbDatabase*);


/// <summary> Dimensional constraint type. </summary>
///
enum AcDbAssocConstraintType
{
    /// <summary> None Associate Constraint </summary>
    kNoneAssocConstraintType = 0,
    /// <summary> Distance Associate Constraint </summary>
    kDistanceAssocConstraintType,
    /// <summary> Horizontal Distance Associate Constraint </summary>
    kHorizontalDistanceAssocConstraintType,
    /// <summary> Vertical Distance Associate Constraint </summary>
    kVerticalDistanceAssocConstraintType,
    /// <summary> AcAngleConstraint::kParallelAntiClockwise Associate Constraint </summary>
    kAngle0AssocConstraintType,
    /// <summary> AcAngleConstraint::kAntiParallelClockwise Associate Constraint </summary>
    kAngle1AssocConstraintType,
    /// <summary> AcAngleConstraint::kParallelClockwise Associate Constraint </summary>
    kAngle2AssocConstraintType,
    /// <summary> AcAngleConstraint::kAntiParallelAntiClockwise Associate Constraint </summary>
    kAngle3AssocConstraintType,
    /// <summary> Radius Associate Constraint </summary>
    kRadiusAssocConstraintType,
    /// <summary> Diameter Associate Constraint </summary>
    kDiameterAssocConstraintType,
};


class AcGeCurve3d;

/// <summary>
/// A simple class that just keeps geometry of a vertex or edge subentity.
/// </summary>
/// <remarks>
/// Notice that no copy constructor, assignment operator or destructor are 
/// implemented that would manage the referenced curve. The AcDbSubentGeometry
/// is not the owner of the curve, it just references it.
/// </remarks>
///
class ACDBCORE2D_PORT AcDbSubentGeometry
{
public:
    /// <summary> Default constructor. </summary>
    AcDbSubentGeometry() : mSubentType(AcDb::kNullSubentType), mpCurve(NULL) {}

    /// <summary> Constructor initializing with a vertex subentity. </summary>
    /// <param name="pnt"> The coordinates of the point subentity. </param>
    ///
    AcDbSubentGeometry(const AcGePoint3d& pnt)
        : mSubentType(AcDb::kVertexSubentType), mPoint(pnt), mpCurve(NULL) {}

    /// <summary> Constructor initializing with an edge subnetity. </summary>
    /// <param  name="pCurve"> The curve is not owned by this AcDbSubentGeometry. </param>
    ///
    AcDbSubentGeometry(AcGeCurve3d* pCurve)
        : mSubentType(AcDb::kEdgeSubentType), mpCurve(pCurve) {}

    /// <summary> Returns AcDb::SubentType of the subentity. </summary>
    /// <returns> AcDb::SubentType. </returns>
    ///
    AcDb::SubentType type() const { return mSubentType; }

    /// <summary> Returns coordinates of the vertex subentity. </summary>
    /// <returns> Coordinates of the vertex subentity. </returns>
    ///
    AcGePoint3d point() const { return mPoint; }

    /// <summary> Returns pointer to the curve of the edge subentity. </summary>
    /// <returns> Pointer to the curve of the edge subentity. The curve is not
    /// owned by this AcDbSubentGeometry. </returns>
    ///
    AcGeCurve3d* curve() const { return mpCurve; }

private:
    AcDb::SubentType mSubentType;
    AcGePoint3d      mPoint;
    AcGeCurve3d*     mpCurve;
};


class AcString;
class AcDbEvalVariant;

// For expressions used in AcDbAssocVariables (for internal use)

ACDBCORE2D_PORT bool acdbIsExpressionAConstant(const AcString& expression, AcDbEvalVariant& val);
ACDBCORE2D_PORT bool acdbIsExpressionANegativeConstant(const AcString& expression);
ACDBCORE2D_PORT bool acdbIsIdentifier(const AcString& name);

#pragma pack (pop)

