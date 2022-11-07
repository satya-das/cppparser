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
// AcDbAssocNetwork concrete class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcString.h"
#include "AcDbAssocAction.h"
#pragma pack (push, 8)


/// <summary> <para>
/// The AcDbAssocNetwork class keeps a network of AcDbAssocActions. Notice that 
/// it is derived from AcDbAssocAction, therefore it also behaves as an individual
/// AcDbAssocAction. It means as a whole network can depend on other objects via
/// its AcDbAssocDependencies or be owned by a higher-level AcDbAssocNetwork, 
/// allowing to create hierarchical associative structures.
/// </para> <para>
/// The AcDbAssocDependencies between AcDbAssocActions in the AcDbAssocNetwork 
/// define how the actions are tied together, how they depend on objects and on 
/// each other. For example, if one action modifies (writes) an object and 
/// another action uses (reads) the object, then the second action depends on 
/// the first one and the second action needs to be evaluated only after the 
/// first action has been evaluated. 
/// </para> </summary>
///
class ACDBCORE2D_PORT AcDbAssocNetwork : public AcDbAssocAction
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocNetwork);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject explanation. </param>
    ///
    explicit AcDbAssocNetwork(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary>
    /// Returns reference to the *internal* array of AcDbObjectIds of all owned
    /// AcDbAssocActions. If used for anything more than just a simple iteration,
    /// or when there is any chance that some actions may be added/removed, 
    /// you need to make a copy of this array FIRST, because the array may change.
    /// </summary>
    /// <returns> 
    /// Reference to the internal array of AcDbObjectIds of the owned AcDbAssocActions. 
    /// </returns>
    ///
    const AcDbObjectIdArray& getActions() const;

    /// <summary>
    /// Returns reference to the *internal* array of AcDbObjectIds of owned
    /// AcDbAssocActions whose AcDbAssocStatus indicates that they need to be 
    /// evaluated. If used for anything more than just a simple iteration,
    /// or when there is any chance that some actions may be added/removed, 
    /// you need to make a copy of this array FIRST, because the array may change.
    /// Even changing the status of an action may cause the action to be added
    /// or removed to/from the array.
    /// </summary>
    /// <returns> 
    /// Reference to the internal array of AcDbObjectIds of the owned 
    /// AcDbAssocActions that need to be evaluated.
    /// </returns>
    ///
    const AcDbObjectIdArray& getActionsToEvaluate() const;

    /// <summary> <para>
    /// Adds an AcDbAssocAction to be owned by this network. The action being
    /// added must not be owned by any network. Every action except for the topmost 
    /// AcDbAssocNetwork is "logically" owned by a single AcDbAssocNetwork. 
    /// </para> <para>
    /// The network becomes the "logical" owner of the action. It may also become 
    /// the "physical" database owner of the action (the network has hard-ownership 
    /// id of the action), but the "physical" owner may be some other object. 
    /// For example, for networks attached to AcDbBlockTableRecords, the "logical" 
    /// owner is the top-level network of the whole database but the "physical" 
    /// database owner is the subdictionary of the extension dictionary of the 
    /// AcBdBlockTableRecord.
    /// </para> </summary>
    /// <param name="actionId"> AcDbAssocAction being added to the network. </param>
    /// <param name="alsoSetAsDatabaseOwner"> Make this network the database owner of the action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addAction(const AcDbObjectId& actionId, bool alsoSetAsDatabaseOwner);

    /// <summary> 
    /// Removes an AcDbAssocAction from the network and optionally erases it.
    /// The action being removed must be owned by this network.
    /// </summary>
    /// <param name="actionId"> AcDbAssocAction being removed from the network. </param>
    /// <param name="alsoEraseIt"> Erase the action after removing it. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeAction(const AcDbObjectId& actionId, bool alsoEraseIt);

    /// <summary> <para>
    /// Adds the given AcDbAssocActions to be owned by this network. The actions 
    /// being added must not be owned by any network.
    /// </para> <para>
    /// The network becomes the "logical" owner of the action. It may also become 
    /// the "physical" database owner of the actions (the network has hard-ownership 
    /// id of the actions), but the "physical" owner may be some other object. 
    /// For example, for networks attached to AcDbBlockTableRecords, the "logical" 
    /// owner is the top-level network of the whole database but the "physical" 
    /// database owner is the subdictionary of the extension dictionary of the 
    /// AcBdBlockTableRecord.
    /// </para> </summary>
    /// <param name="actionIds"> AcDbAssocActions being added to the network. </param>
    /// <param name="alsoSetAsDatabaseOwner"> Make this network the database owner of the actions. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addActions(const AcDbObjectIdArray& actionIds, bool alsoSetAsDatabaseOwner);

    /// <summary> 
    /// Removes all AcDbAssocActions from the network and optionally erases them. 
    /// The network will become empty.
    /// </summary>
    /// <param name="alsoEraseThem"> Erase the actions after removing them. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeAllActions(bool alsoEraseThem);

    /// <summary>
    /// This callback is called from AcDbAssocAction::setStatus(..., true) 
    /// and notifies the network owing the action that the status of the 
    /// action has just been changed. The action is still open for write and
    /// already has the new status.
    /// </summary>
    /// <param name="pOwnedAction"> The action whose status has just been changed. </param>
    /// <param name="previousStatus"> Previous status of the action. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus ownedActionStatusChanged(AcDbAssocAction* pOwnedAction, 
                                               AcDbAssocStatus  previousStatus);

    /// <summary> <para>
    /// Returns AcDbObjectId of the AcDbAssocNetwork owned by the given 
    /// database, optionally creating a new one if it does not exist yet. 
    /// Returns AcDbObjectId::kNull if the network cannot be obtained. 
    /// </para> <para>
    /// The network is owned by a special sub-dictionary owned by the named 
    /// object dictionary of the database.
    /// </para> </summary>
    /// <param name="pDatabase"> AcDbDatabase owning the network. </param>
    /// <param name="createIfDoesNotExist"> 
    /// If it does not exist yet, create a new subdictionary under the named object 
    /// dictionary of the database. Create an AcDbAssocNetwork and make it owned
    /// by this newly created subdictionary. 
    /// </param>
    /// <param name="dictionaryKey"> 
    /// The name of the sub-dictionary under which the network belongs.
    /// If no key name is given, the default "ACAD_ASSOCNETWORK" key is used.
    /// </param>
    /// <returns> AcDbObjectId of the existing or newly created AcDbAssocNetwork. </returns>
    ///
    static AcDbObjectId getInstanceFromDatabase(AcDbDatabase*   pDatabase,
                                                bool            createIfDoesNotExist,
                                                const AcString& dictionaryKey = ACRX_T(""));

    /// <summary> <para>
    /// Returns AcDbObjectId of the AcDbAssocNetwork owned by the extension 
    /// dictionary of the given AcDbObject, optionally creating a new one if it 
    /// does not exist yet. Returns AcDbObjectId::kNull if the network cannot be 
    /// obtained.
    /// </para> <para>
    /// The network is owned by a special sub-dictionary owned by the extension
    /// dictionary of the given object.
    /// </para> </summary> 
    /// <param name="owningObjectId"> 
    /// The AcDbObject owning the sub-dictionary that owns the AcDbAssocNetwork. 
    /// </param>
    /// <param name="createIfDoesNotExist"> 
    /// If it does not exist yet, create a new subdictionary of the extension 
    /// dictionary of the object. Create an AcDbAssocNetwork and make it owned 
    /// by this newly created subdictionary.     
    /// </param>
    /// <param name="addToTopLevelNetwork"> 
    /// If the network is newly created, it also adds it to the the top-level
    /// network of the database that owns the owningObjectId. It has no effect 
    /// if the network already exists or if createIfDoesNotExist is false.
    /// </param>
    /// <param name="dictionaryKey"> 
    /// The name of the sub-dictionary under which the network belongs.
    /// If no key name is given, the default "ACAD_ASSOCNETWORK" key is used.
    /// </param>
    /// <returns> AcDbObjectId of the existing or newly created AcDbAssocNetwork. </returns>
    ///
    static AcDbObjectId getInstanceFromObject(const AcDbObjectId& owningObjectId,
                                              bool                createIfDoesNotExist,
                                              bool                addToTopLevelNetwork = true,
                                              const AcString&     dictionaryKey        = ACRX_T(""));

    /// <summary> 
    /// Removes the network and the sub-dictionary that owns it from the extension 
    /// dictionary of the object.
    /// </summary> 
    /// <param name="owningObjectId"> 
    /// The AcDbObject whose extension dictionary owns the sub-dictionary that 
    /// owns the AcDbAssocNetwork. 
    /// </param>
    /// <param name="alsoEraseIt"> Erase the network after removing it.
    /// </param>
    /// <param name="dictionaryKey"> 
    /// The name of the sub-dictionary under which the network belongs.
    /// If no key name is given, the default "ACAD_ASSOCNETWORK" key is used.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus removeInstanceFromObject(const AcDbObjectId& owningObjectId,
                                                      bool                alsoEraseIt,
                                                      const AcString&     dictionaryKey = ACRX_T(""));

    /// <summary> 
    /// Removes the network and the sub-dictionary that owns it from the named 
    /// object dictionary of the database.
    /// </summary> 
    /// <param name="owningObjectId"> 
    /// The database whose named object dictionary owns the sub-dictionary that 
    /// owns the AcDbAssocNetwork. 
    /// </param>
    /// <param name="alsoEraseIt"> Erase the network after removing it.
    /// </param>
    /// <param name="dictionaryKey"> 
    /// The name of the sub-dictionary under which the network belongs.
    /// If no key name is given, the default "ACAD_ASSOCNETWORK" key is used.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    static Acad::ErrorStatus removeInstanceFromDatabase(AcDbDatabase*   pDatabase,
                                                        bool            alsoEraseIt,
                                                        const AcString& dictionaryKey = ACRX_T(""));

}; // class AcDbAssocNetwork


/// <summary>
/// A simple class to iterate over all AcDbAssocActions of an AcDbAssocNetwork.
/// <code>
/// AcDbSmartObjectPointer<AcDbAssocNetwork> pNetwork(assocNetworkId, AcDb::kForRead);
///
/// if (!eOkVerify(pNetwork.openStatus()))
/// {
///     // Cannot open the network ...
/// }
/// 
/// AcDbAssocNetworkIterator iter(pNetwork);
///
/// while (iter.moveNext())
/// {
///     const AcDbObjectId actionId = iter.current();
///     AcDbSmartObjectPointer<AcDbAssocAction> pAction(actionId, AcDb::kForRead);
///     // Process pAction ...
/// }
/// </code>
/// </summary>
///
class ACDBCORE2D_PORT AcDbAssocNetworkIterator
{
public:
    /// <summary> 
    /// Creates an iterator allowing to sequentially access all AcDbAssocActions
    /// of the given AcDbAssocNetwork. The iterator is initially positioned 
    /// before the first action in the network. During the iteration no actions
    /// may be added/removed to/from the network.
    /// </summary>
    ///
    explicit AcDbAssocNetworkIterator(const AcDbAssocNetwork* pNetwork) 
        : mpNetwork(pNetwork), mIndex(-1) 
    {
#ifdef ASSERT
        ASSERT(mpNetwork != NULL);
#endif
    }

    /// <summary>
    /// Returns the current element the iterator is pointing to, or 
    /// AcDbObjectId::kNull if the iteration hasn't started yet or the 
    /// iteration is over.
    /// </summary> 
    /// <returns> The current AcDbAssocAction or null. </returns>
    ///
    AcDbObjectId current() const 
    { 
        if (mpNetwork != NULL && 0 <= mIndex && mIndex < mpNetwork->getActions().length())
        {
            return mpNetwork->getActions()[mIndex]; 
        }
        else
        {
#ifdef ASSERT
            ASSERT(false);
#endif
            return AcDbObjectId::kNull;
        }
    }

    /// <summary>
    /// Advances the iterator to the next AcDbAssocAction in the network. 
    /// </summary> 
    /// <returns> 
    /// Returns true if advanced to the next AcDbAssocAction, false if no more 
    /// AcDbAssocAction in the network. 
    /// </returns>
    ///
    bool moveNext() 
    { 
        return mpNetwork != NULL ? ++mIndex < mpNetwork->getActions().length() : false;
    }

    /// <summary>
    /// Position the iterator before the first action in the network.
    /// </summary> 
    ///
    void reset() { mIndex = -1; }

private:
    const AcDbAssocNetwork* const mpNetwork;
    int                           mIndex;
}; // class AcDbAssocNetworkIterator


#pragma pack (pop)


