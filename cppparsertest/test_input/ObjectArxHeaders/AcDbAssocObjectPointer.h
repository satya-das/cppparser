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
//
// CREATED BY: Jiri Kripac                                 September 2007
//
// DESCRIPTION:
//
// Template class AcDbAssocObjectPointer.
//
//////////////////////////////////////////////////////////////////////////////

#include "dbobjptr2.h"
#include "AcDbAssocActionBody.h"
#include "AcDbAssocDependencyBody.h"
#pragma pack (push, 8)


/// <summary> <para>
/// When an action is being evaluated and needs to use or modify an existing
/// object it has a dependency on, the client code is given an option to control
/// which object the action is actually going to use or modify. The client code 
/// can provide a substitute object instead of the original object by implementing
/// the AcDbAssocEvaluationCallback::beginActionEvaluationUsingObject() callback
/// method. This way the action evaluation can be redirected to use or modify 
/// another object (see the comments at the AcDbAssocEvaluationCallback class).
/// </para> <para>
/// The AcDbAssocObjectPointer template class, modelled after AcDbObjectPointer 
/// template class, simplifies the action evaluation code that needs to respect 
/// this possible redirection. The AcDbAssocObjectPointer constructor automatically 
/// calls the AcDbAssocEvaluationCallback::beginActionEvaluationUsingObject() 
/// method and the destructor calls the 
/// AcDbAssocEvaluationCallback::endActionEvaluationUsingObject() method. 
/// </para> <para>
/// All the custom action evaluation code needs to do is to use this template 
/// class and then use the AcDbObject pointer this template class provides. The 
/// pointer will point either to the original database-resident object whose 
/// AcDbObjectId has been provided, or to a substitute object, if the evaluation 
/// is in progress and the client evaluation callback provided a substitute object.
/// </para> <para>
/// There are several overloaded constructors that simplify the usage of this
/// class from an AcDbAssocAction, AcDbAssocActionBody, AcDbAssocDependency or
/// AcDbAssocDependencyBody. The constuctor that does not take an action, action 
/// body, dependency or dependency body argument uses the currently evaluated 
/// action, if in the middle of evaluation. This is probably the most convenient
/// constructor to use.
/// </para> <para>
/// There are also constructors that take ACDB_CLASS*. They can be used to pass 
/// the given ACDB_CLASS* object to the client callback code. The constructor
/// calls AcDbAssocEvaluationCallback::beginActionEvaluationUsingObject() 
/// callback method, passing null AcDbObjectId and passing the given ACDB_CLASS*
/// object as the pSubstituteObject argument. The callback method should then 
/// treat this argument as an input agrument, i.e. the it should not change it. 
/// The destructor calls AcDbAssocEvaluationCallback::endActionEvaluationUsingObject() 
/// callback method, passing null AcDbObjectId and passing the given ACDB_CLASS* 
/// object as the pObject argument. 
/// </para> </summary>
///
template<class ACDB_CLASS> class AcDbAssocObjectPointer
{
public:

    /// <summary> Constructor. If in the middle of evaluation, uses the currently evaluated action. </summary>
    /// <param name="objectId"> AcDbObjectId of the object that should be opened. </param>
    /// <param name="openMode"> AcDb::kForRead, AcDb::kForWrite, AcDb::kForNotify. </param>
    /// <param name="openErased"> Opens the object even if it is erased. </param>
    /// <param name="openOnLockedLayer"> Opens the object even on the locked layer. </param>
    ///
    AcDbAssocObjectPointer(
        AcDbObjectId                   objectId,
        AcDb::OpenMode                 openMode,
        bool                           openErased = false,
        bool                           openOnLockedLayer = false);

    /// <summary> Constructor. </summary>
    /// <param name="pActionBeingEvaluated"> The action that is just being evaluated. </param>
    /// <param name="objectId"> AcDbObjectId of the object that should be opened. </param>
    /// <param name="openMode"> AcDb::kForRead, AcDb::kForWrite, AcDb::kForNotify. </param>
    /// <param name="openErased"> Opens the object even if it is erased. </param>
    /// <param name="openOnLockedLayer"> Opens the object even on the locked layer. </param>
    ///
    AcDbAssocObjectPointer(
        AcDbAssocAction*               pActionBeingEvaluated, 
        AcDbObjectId                   objectId,
        AcDb::OpenMode                 openMode,
        bool                           openErased = false,
        bool                           openOnLockedLayer = false);

    /// <summary> Constructor. </summary>
    /// <param name="pActionBodyBeingEvaluated"> The body of action that is just being evaluated. </param>
    /// <param name="objectId"> AcDbObjectId of the object that should be opened. </param>
    /// <param name="openMode"> AcDb::kForRead, AcDb::kForWrite, AcDb::kForNotify. </param>
    /// <param name="openErased"> Opens the object even if it is erased. </param>
    /// <param name="openOnLockedLayer"> Opens the object even on the locked layer. </param>
    ///
    AcDbAssocObjectPointer(
        const AcDbAssocActionBody*     pActionBodyBeingEvaluated, 
        AcDbObjectId                   objectId,
        AcDb::OpenMode                 openMode,
        bool                           openErased = false,
        bool                           openOnLockedLayer = false);

    /// <summary> Constructor. </summary>
    /// <param name="pDependencyBeingEvaluated"> The dependency whose action is just being evaluated. </param>
    /// <param name="objectId"> AcDbObjectId of the object that should be opened. </param>
    /// <param name="openMode"> AcDb::kForRead, AcDb::kForWrite, AcDb::kForNotify. </param>
    /// <param name="openErased"> Opens the object even if it is erased. </param>
    /// <param name="openOnLockedLayer"> Opens the object even on the locked layer. </param>
    ///
    AcDbAssocObjectPointer(
        const AcDbAssocDependency*     pDependencyBeingEvaluated, 
        AcDbObjectId                   objectId,
        AcDb::OpenMode                 openMode,
        bool                           openErased = false,
        bool                           openOnLockedLayer = false);

    /// <summary> Constructor. </summary>
    /// <param name="pDependencyBodyBeingEvaluated"> The body of dependency whose action is just being evaluated. </param>
    /// <param name="objectId"> AcDbObjectId of the object that should be opened. </param>
    /// <param name="openMode"> AcDb::kForRead, AcDb::kForWrite, AcDb::kForNotify. </param>
    /// <param name="openErased"> Opens the object even if it is erased. </param>
    /// <param name="openOnLockedLayer"> Opens the object even on the locked layer. </param>
    ///
    AcDbAssocObjectPointer(
        const AcDbAssocDependencyBody* pDependencyBodyBeingEvaluated, 
        AcDbObjectId                   objectId,
        AcDb::OpenMode                 openMode,
        bool                           openErased = false,
        bool                           openOnLockedLayer = false);

    /// <summary> Constructor. </summary>
    /// <param name="pActionBeingEvaluated"> The action that is just being evaluated. </param>
    /// <param name="pObject"> Existing AcDbObject that is passed as input argument 
    /// to the client callback code. See the class summary for more details. </param>
    ///
    AcDbAssocObjectPointer(
        AcDbAssocAction*               pActionBeingEvaluated, 
        ACDB_CLASS*                    pObject);

    /// <summary> Constructor. </summary>
    /// <param name="pActionBodyBeingEvaluated"> The body of action that is just being evaluated. </param>
    /// <param name="pObject"> Existing AcDbObject that is passed as input argument 
    /// to the client callback code. See the class summary for more details. </param>
    ///
    AcDbAssocObjectPointer(
        const AcDbAssocActionBody*     pActionBodyBeingEvaluated, 
        ACDB_CLASS*                    pObject);

    /// <summary> Destructor. </summary>
    ///
    ~AcDbAssocObjectPointer();

    /// <summary> Gets the open status of the associated object. </summary>
    /// <returns> Returns the open status of the associated object. </returns>
    ///
    Acad::ErrorStatus openStatus() const;

    /// <summary> Gets whether there is a substitute object. </summary>
    /// <returns> Returns true if the substitute object exists. </returns>
    ///
    bool isSubstituteObject() const { return mpSubstituteObject != NULL; }

    /// <summary> Gets the constant pointer of the associated object. </summary>
    /// <returns> Returns the constant pointer of the associated object. </returns>
    ///
    const ACDB_CLASS* operator->() const { return mpObject; }

    /// <summary> Gets the pointer of the associated object. </summary>
    /// <returns> Returns the pointer of the associated object. </returns>
    ///
    ACDB_CLASS* operator->() { return mpObject; }

    /// <summary> Gets the constant pointer of the associated object. </summary>
    ///
    operator const ACDB_CLASS*() const { return mpObject; }

    /// <summary> Gets the pointer of the associated object. </summary>
    ///
    operator ACDB_CLASS*() { return mpObject; }

private:

    AcDbAssocAction* const               mpActionBeingEvaluated;
    const AcDbAssocActionBody* const     mpActionBodyBeingEvaluated;
    const AcDbAssocDependency* const     mpDependencyBeingEvaluated;
    const AcDbAssocDependencyBody* const mpDependencyBodyBeingEvaluated;
    const AcDbObjectId                   mObjectId;
    AcDbSmartObjectPointer<ACDB_CLASS>   mObjectPtr;
    ACDB_CLASS*                          mpObject;
    AcDbObject*                          mpSubstituteObject;
    Acad::ErrorStatus                    mSubstituteObjectErrorStatus;

private:
    /// <summary> set up the associated object. </summary>
    ///
    void setup(AcDbAssocAction* pActionBeingEvaluated, 
        AcDb::OpenMode   openMode,
        bool             openErased,
        bool             openOnLockedLayer);

    /// <summary> Constructor. Disabled </summary>
    ///
    AcDbAssocObjectPointer();

    /// <summary> Constructor. Disabled </summary>
    ///
    AcDbAssocObjectPointer(const AcDbAssocObjectPointer&);

    /// <summary> Overrides the operator = . Disabled </summary>
    ///
    AcDbAssocObjectPointer& operator = (const AcDbAssocObjectPointer&);

}; // template class AcDbAssocObjectPointer


ACDBCORE2D_PORT AcDbAssocAction* acdbAssocGetCurrentlyEvaluatedActionPointer(const AcDbDatabase*);


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::AcDbAssocObjectPointer(

    AcDbObjectId      objectId,
    AcDb::OpenMode    openMode,
    bool              openErased ,
    bool              openOnLockedLayer)

  : mpActionBeingEvaluated        (acdbAssocGetCurrentlyEvaluatedActionPointer(objectId.database())), 
    mpActionBodyBeingEvaluated    (NULL), 
    mpDependencyBeingEvaluated    (NULL), 
    mpDependencyBodyBeingEvaluated(NULL), 
    mObjectId                     (objectId),
    mpObject                      (NULL), 
    mpSubstituteObject            (NULL),
    mSubstituteObjectErrorStatus  (Acad::eNullObjectId)
{
    setup(mpActionBeingEvaluated, openMode, openErased, openOnLockedLayer);
}


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::AcDbAssocObjectPointer(

    AcDbAssocAction*  pActionBeingEvaluated, 
    AcDbObjectId      objectId,
    AcDb::OpenMode    openMode,
    bool              openErased ,
    bool              openOnLockedLayer)

  : mpActionBeingEvaluated        (pActionBeingEvaluated), 
    mpActionBodyBeingEvaluated    (NULL), 
    mpDependencyBeingEvaluated    (NULL), 
    mpDependencyBodyBeingEvaluated(NULL), 
    mObjectId                     (objectId),
    mpObject                      (NULL), 
    mpSubstituteObject            (NULL),
    mSubstituteObjectErrorStatus  (Acad::eNullObjectId)
{
    setup(pActionBeingEvaluated, openMode, openErased, openOnLockedLayer);
}


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::AcDbAssocObjectPointer(

    const AcDbAssocActionBody* pActionBodyBeingEvaluated, 
    AcDbObjectId               objectId,
    AcDb::OpenMode             openMode,
    bool                       openErased  ,
    bool                       openOnLockedLayer  )

  : mpActionBeingEvaluated        (NULL), 
    mpActionBodyBeingEvaluated    (pActionBodyBeingEvaluated), 
    mpDependencyBeingEvaluated    (NULL), 
    mpDependencyBodyBeingEvaluated(NULL), 
    mObjectId                     (objectId),
    mpObject                      (NULL), 
    mpSubstituteObject            (NULL),
    mSubstituteObjectErrorStatus  (Acad::eNullObjectId)
{
#ifdef ASSERT
    ASSERT(mpActionBodyBeingEvaluated != NULL);
#endif
    AcDbSmartObjectPointer<AcDbAssocAction> pActionBeingEvaluated;

    if (mpActionBodyBeingEvaluated != NULL)
    {
        pActionBeingEvaluated.open(mpActionBodyBeingEvaluated->parentAction(), AcDb::kForRead, true);
    }

    setup(pActionBeingEvaluated, openMode, openErased, openOnLockedLayer);
}


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::AcDbAssocObjectPointer(

    const AcDbAssocDependency* pDependencyBeingEvaluated, 
    AcDbObjectId               objectId,
    AcDb::OpenMode             openMode,
    bool                       openErased  ,
    bool                       openOnLockedLayer  )

  : mpActionBeingEvaluated        (NULL), 
    mpActionBodyBeingEvaluated    (NULL), 
    mpDependencyBeingEvaluated    (pDependencyBeingEvaluated), 
    mpDependencyBodyBeingEvaluated(NULL), 
    mObjectId                     (objectId),
    mpObject                      (NULL), 
    mpSubstituteObject            (NULL),
    mSubstituteObjectErrorStatus  (Acad::eNullObjectId)
{
#ifdef ASSERT
    ASSERT(mpDependencyBeingEvaluated != NULL);
#endif
    AcDbSmartObjectPointer<AcDbAssocAction> pActionBeingEvaluated;

    if (mpDependencyBeingEvaluated != NULL)
    {
        pActionBeingEvaluated.open(mpDependencyBeingEvaluated->owningAction(), AcDb::kForRead, true);
    }

    setup(pActionBeingEvaluated, openMode, openErased, openOnLockedLayer);
}


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::AcDbAssocObjectPointer(

    const AcDbAssocDependencyBody* pDependencyBodyBeingEvaluated, 
    AcDbObjectId                   objectId,
    AcDb::OpenMode                 openMode,
    bool                           openErased ,
    bool                           openOnLockedLayer)

  : mpActionBeingEvaluated        (NULL), 
    mpActionBodyBeingEvaluated    (NULL), 
    mpDependencyBeingEvaluated    (NULL), 
    mpDependencyBodyBeingEvaluated(pDependencyBodyBeingEvaluated), 
    mObjectId                     (objectId),
    mpObject                      (NULL), 
    mpSubstituteObject            (NULL),
    mSubstituteObjectErrorStatus  (Acad::eNullObjectId)
{
#ifdef ASSERT
    ASSERT(mpDependencyBodyBeingEvaluated != NULL);
#endif
    AcDbSmartObjectPointer<AcDbAssocAction> pActionBeingEvaluated;

    if (mpDependencyBodyBeingEvaluated != NULL)
    {
        AcDbSmartObjectPointer<AcDbAssocDependency> 
            pDependencyBeingEvaluated(mpDependencyBodyBeingEvaluated->parentDependency(), AcDb::kForRead, true);

        if (pDependencyBeingEvaluated.openStatus() == Acad::eOk)
        {
            pActionBeingEvaluated.open(pDependencyBeingEvaluated->owningAction(), AcDb::kForRead, true);
        }
    }

    setup(pActionBeingEvaluated, openMode, openErased, openOnLockedLayer);
}


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::AcDbAssocObjectPointer(

    AcDbAssocAction* pActionBeingEvaluated, 
    ACDB_CLASS*      pObject)

  : mpActionBeingEvaluated        (pActionBeingEvaluated), 
    mpActionBodyBeingEvaluated    (NULL), 
    mpDependencyBeingEvaluated    (NULL), 
    mpDependencyBodyBeingEvaluated(NULL), 
    mObjectId                     (AcDbObjectId::kNull),
    mpObject                      (pObject), 
    mpSubstituteObject            (pObject),
    mSubstituteObjectErrorStatus  (pObject != NULL ? Acad::eOk : Acad::eNullObjectId)
{
#ifdef ASSERT
    ASSERT(mpActionBeingEvaluated != NULL);
#endif
    if (pActionBeingEvaluated != NULL)
    {
        AcDbAssocEvaluationCallback* const pCallback 
            = pActionBeingEvaluated->currentEvaluationCallback();

        if (pCallback != NULL)
        {
            AcDbObject* pInputObject = pObject;

            pCallback->beginActionEvaluationUsingObject(pActionBeingEvaluated, 
                AcDbObjectId::kNull, 
                true, 
                true, 
                pInputObject);

            // If the passed-in objectId is null, the callback should treat 
            // its pSubstituteObject argument as an input argument and should 
            // not change its value
            //
#ifdef ASSERT
            ASSERT(pInputObject == pObject);
#endif
        }
    }
}


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::AcDbAssocObjectPointer(

    const AcDbAssocActionBody* pActionBodyBeingEvaluated, 
    ACDB_CLASS*                pObject)

    : mpActionBeingEvaluated        (NULL), 
    mpActionBodyBeingEvaluated    (pActionBodyBeingEvaluated), 
    mpDependencyBeingEvaluated    (NULL),
    mpDependencyBodyBeingEvaluated(NULL), 
    mObjectId                     (AcDbObjectId::kNull),
    mpObject                      (pObject), 
    mpSubstituteObject            (pObject),
    mSubstituteObjectErrorStatus  (pObject != NULL ? Acad::eOk : Acad::eNullObjectId)
{
#ifdef ASSERT
    ASSERT(mpActionBodyBeingEvaluated != NULL);
#endif
    if (mpActionBodyBeingEvaluated != NULL)
    {
        AcDbSmartObjectPointer<AcDbAssocAction> 
            pActionBeingEvaluated(mpActionBodyBeingEvaluated->parentAction(), 
            AcDb::kForRead, true);

        if (pActionBeingEvaluated != NULL)
        {
            AcDbAssocEvaluationCallback* const pCallback 
                = pActionBeingEvaluated->currentEvaluationCallback();

            if (pCallback != NULL)
            {
                AcDbObject* pInputObject = pObject;

                pCallback->beginActionEvaluationUsingObject(pActionBeingEvaluated, 
                    AcDbObjectId::kNull, 
                    true, 
                    true, 
                    pInputObject);

                // If the passed-in objectId is null, the callback should treat 
                // its pSubstituteObject argument as an input argument and should 
                // not change its value
                //
#ifdef ASSERT
                ASSERT(pInputObject == pObject);
#endif
            }
        }
    }
}


template<class ACDB_CLASS> inline 
void AcDbAssocObjectPointer<ACDB_CLASS>::setup(

    AcDbAssocAction* pActionBeingEvaluated, 
    AcDb::OpenMode   openMode,
    bool             openErased,
    bool             openOnLockedLayer)
{
    mpObject                     = NULL;
    mpSubstituteObject           = NULL;
    mSubstituteObjectErrorStatus = Acad::eNullObjectId;

    if (mObjectId.isNull())
        return;

    if (pActionBeingEvaluated != NULL)
    {
        AcDbAssocEvaluationCallback* const pCallback 
            = pActionBeingEvaluated->currentEvaluationCallback();

        if (pCallback != NULL)
        {
            pCallback->beginActionEvaluationUsingObject(pActionBeingEvaluated, 
                mObjectId, 
                true, 
                openMode == AcDb::kForWrite, 
                mpSubstituteObject);

            if (mpSubstituteObject != NULL)
            {
                mpObject                     = ACDB_CLASS::cast(mpSubstituteObject);
                mSubstituteObjectErrorStatus = mpObject != NULL ? Acad::eOk : Acad::eNotThatKindOfClass;
            }
        }
    }

    if (mpSubstituteObject == NULL)
    {
        if (mObjectPtr.open(mObjectId, openMode, openErased, openOnLockedLayer) == Acad::eOk)
        {
            mpObject = mObjectPtr;
#ifdef ASSERT
            ASSERT(mpObject != NULL);
#endif
        }
    }
}


template<class ACDB_CLASS> inline
AcDbAssocObjectPointer<ACDB_CLASS>::~AcDbAssocObjectPointer()
{
    if (mObjectId.isNull() && mpSubstituteObject == NULL)
        return; // There is no referenced object

    if (mpActionBeingEvaluated != NULL)
    {
        AcDbAssocEvaluationCallback* const pCallback 
            = mpActionBeingEvaluated->currentEvaluationCallback();

        if (pCallback != NULL)
        {
            pCallback->endActionEvaluationUsingObject(mpActionBeingEvaluated, mObjectId, mpObject);
        }
    }
    else
    {
        AcDbSmartObjectPointer<AcDbAssocAction> pActionBeingEvaluated;

        if (mpActionBodyBeingEvaluated != NULL)
        {
            pActionBeingEvaluated.open(mpActionBodyBeingEvaluated->parentAction(), AcDb::kForRead, true);
        }
        else if (mpDependencyBeingEvaluated != NULL)
        {
            pActionBeingEvaluated.open(mpDependencyBeingEvaluated->owningAction(), AcDb::kForRead, true);
        }
        else if (mpDependencyBodyBeingEvaluated != NULL)
        {
            AcDbSmartObjectPointer<AcDbAssocDependency> 
                pDependencyBeingEvaluated(mpDependencyBodyBeingEvaluated->parentDependency(), AcDb::kForRead, true);

            if (pDependencyBeingEvaluated.openStatus() == Acad::eOk)
            {
                pActionBeingEvaluated.open(pDependencyBeingEvaluated->owningAction(), AcDb::kForRead, true);
            }
        }

        if (pActionBeingEvaluated.openStatus() == Acad::eOk)
        {
            AcDbAssocEvaluationCallback* const pCallback 
                = pActionBeingEvaluated->currentEvaluationCallback();

            if (pCallback != NULL)
            {
                pCallback->endActionEvaluationUsingObject(pActionBeingEvaluated, mObjectId, mpObject);
            }
        }
    }
}


template<class ACDB_CLASS> inline 
Acad::ErrorStatus AcDbAssocObjectPointer<ACDB_CLASS>::openStatus() const
{
    return mpSubstituteObject != NULL ? mSubstituteObjectErrorStatus : mObjectPtr.openStatus();
}

#pragma pack (pop)
