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
// 
//  rxprotevnt.h
//    
//     AcRxObject
//       AcRxProtocolReactor
//       AcRxProtocolReactorIterator
//       AcRxProtocolReactorList
//       AcRxProtocolReactorListIterator
//       AcRxProtocolReactorManager
//       AcRxProtocolReactorManagerFactory
//
//  DESCRIPTION:
//
//  The classes in this file comprise a framework for attaching reactor-like
//  objects to AcRx classes via the AcRx protoocol extension mechanism. Unlike
//  normal protocol extensions, there may be more than one object implementing
//  an event interface for a given event class on a single AcRx object. 
//
//  The classes in this file allow define the base reactor class which is a simple 
//  base class for run time type identification. 
//
//  Applications derive from specific reactor classes and attach an instance of
//  their objects implementing the reactor to a specific AcRx class via the
//  AcRxprotocolReactorManager.
//
//  The AcRxProtocolReactor framework manages the reactors as follows:
//
//  AcRxClass
//    -> AcRxProtocolReactorManager (at most 1 per AcRx class)
//       -> AcRxProtocolReactorList (any number, 
//                                   indexed by AcRxProtocolReactor class)
//           -> AcRxProtocolReactor (any number)
//
//  Note that the framework does not manage the allocation/deallocation of the
//  reactors themselves. Applications must allocate reactors, add them a
//  reactor list associated with one (or more) classes. Before unloading
//  applications should remove the reactors from the reactor lists and free the
//  associated memory. Applications typically do the allocation when loaded and
//  deallocation when unloaded but the actual timing is left up to the
//  applications. 


#pragma once

#include "rxdefs.h"
#include "acadstrc.h"

#pragma pack (push, 8)


class AcRxProtocolReactor;
class AcRxProtocolReactorIterator;
class AcRxProtocolReactorList;
class AcRxProtocolReactorListIterator;
class AcRxProtocolReactorManager;
class AcRxProtocolReactorManagerFactory;


////////////////////// AcRxProtocolReactor class //////////////////////////////
//

/// <summary>
/// The base class for all protocol reactors. All protocol reactor classes
/// must derive from this class. 
/// </summary>
class ADESK_NO_VTABLE AcRxProtocolReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxProtocolReactor);
};


////////////////////// AcRxProtocolReactorIterator class //////////////////////
//

/// <summary>
/// An iterator for enumerating AcRxProtocolReactors in an
/// AcRxProtocolReactorList. 
/// </summary>
///
/// <remarks>
/// Instances of this class are returned by
/// <c>AcRxProtocolReactorList::newIterator()</c>.
/// </remarks>
///
class ADESK_NO_VTABLE AcRxProtocolReactorIterator : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxProtocolReactorIterator);

    // The AcRxClass of the AcRxProtocolReactors returned by the
    // iterator.
    
    /// <summary>
    /// Returns the AcRxClass type returned by the iterator.
    /// </summary>
    ///
    /// <returns>
    /// A pointer to the AcRxClass type.
    /// </returns>
    ///
    virtual AcRxClass* reactorClass () const = 0;


    /// <summary>
    /// Rewinds the iterator to the beginning of the list.
    /// </summary>
    /// 
    virtual void start() = 0; 

    /// <summary>
    /// Advances the iterator to the next item in the list.
    /// </summary>
    ///
    /// <returns>
    /// True if there are more items in the list, false if the iterator has
    /// reached the end of the list.
    /// </returns>
    ///
    virtual bool next () = 0;

    /// <summary>
    /// Determines whether the iterator has reached the end of the list.
    /// </summary>
    ///
    /// <returns>
    /// True if there are more items in the list, false if the iterator has
    /// reached the end of the list.
    /// </returns>
    ///
    virtual bool done () const = 0;

    /// <summary>
    /// Returns the AcRxProtocolReactor at the current iterator position.
    /// </summary>
    ///
    /// <returns>
    /// Returns a pointer to the AcRxProtocolReactor at the current iterator
    /// position.
    /// </returns>
    ///
    virtual AcRxProtocolReactor* object () const = 0;
};


////////////////////// AcRxProtocolReactorList class //////////////////////////
//

/// <summary>
/// A simple collection of AcRxProtocolReactors. 
/// </summary>
///
/// <remarks>
/// Instances of this class contain a single kind of AcRxProtocolReactor.
/// Collections of this class are associated with an AcRxClass through the
/// protocol reactor framework and the AcRxProtocolReactorManager class.
/// </remarks>
///
class ADESK_NO_VTABLE AcRxProtocolReactorList : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxProtocolReactorList);

    /// <summary>
    /// Returns the AcRxClass type returned by the iterator.
    /// </summary>
    ///
    /// <returns>
    /// A pointer to the AcRxClass type.
    /// </returns>
    virtual AcRxClass* reactorClass() const = 0;

    /// <summary>
    /// Adds a reactor to the collection. 
    /// </summary>
    ///
    /// <param name="pReactor">
    /// A pointer to the reactor to add to the collection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eWrongObjectType if 
    /// <paramref name="pReactor"/> is not a kind of <c>reactorClass()</c>.
    /// </returns>
    ///
    virtual Acad::ErrorStatus addReactor   (AcRxProtocolReactor* pReactor) = 0;

    /// <summary>
    /// Removes a reactor from the collection.
    /// </summary>
    ///
    /// <param name="pReactor">
    /// A pointer to the reactor to remove from the collection.
    /// </param>
    ///
    virtual void              removeReactor(AcRxProtocolReactor* pReactor) = 0;

    /// <summary>
    /// Obtains an iterator on the contents of the list.
    /// </summary>
    ///
    /// <returns>
    /// A pointer to an AcRxProtocolReactorIterator that can be used to
    /// enumerate the contents of the list.
    /// </returns>
    ///
    /// <remarks>
    /// Callers are responsible for deleting the returned iterator. 
    /// </remarks>
    ///
    virtual AcRxProtocolReactorIterator* newIterator () const = 0;
};


////////////////////// AcRxProtocolReactorListIterator class //////////////////
//

/// <summary>
/// An iterator for enumerating AcRxProtocolReactorLists in an
/// AcRxProtocolReactorManager. 
/// </summary>
///
/// <remarks>
/// Instances of this class are returned by
/// <c>AcRxProtocolReactorManager::newIterator()</c>.
/// </remarks>
///
class ADESK_NO_VTABLE AcRxProtocolReactorListIterator : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxProtocolReactorListIterator);

    /// <summary>
    /// Rewinds the iterator to the beginning of the list.
    /// </summary>
    /// 
    virtual void start() = 0; 

    /// <summary>
    /// Advances the iterator to the next item in the list.
    /// </summary>
    ///
    /// <returns>
    /// True if there are more items in the list, false if the iterator has
    /// reached the end of the list.
    /// </returns>
    ///
    virtual bool next () = 0;

    /// <summary>
    /// Determines whether the iterator has reached the end of the list.
    /// </summary>
    ///
    /// <returns>
    /// True if there are more items in the list, false if the iterator has
    /// reached the end of the list.
    /// </returns>
    ///
    virtual bool done () const = 0;

    /// <summary>
    /// Returns the AcRxProtocolReactorList at the current iterator position.
    /// </summary>
    ///
    /// <returns>
    /// Returns a pointer to the AcRxProtocolReactorList at the current
    /// iterator position.
    /// </returns>
    ///
    virtual AcRxProtocolReactorList* object () const = 0;
};


////////////////////// AcRxProtocolReactorManager class ///////////////////////
//

/// <summary> 
/// Container class for a collection of AcRxProtocolReactorLists.
/// </summary>
///
/// <remarks>
/// Instances of AcRxProtocolReactorManagers are associated to AcRxClasses at
/// runtime using the protocol extension framework. Instances of this class
/// allow multiple kinds of AcRxProtocolReactors to be associated with a single
/// AcRxClass. 
/// </remarks>
///
class ADESK_NO_VTABLE AcRxProtocolReactorManager: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcRxProtocolReactorManager);
    
    /// <summary>
    /// Returns an AcRxProtocolReactorList for a specific reactor class.
    /// </summary>
    ///
    /// <param name="pReactorClass">
    /// A pointer to the AcRxClass of the reactor managed by the returned list. 
    /// </param>
    ///
    /// <returns>
    /// A pointer to the AcRxProtocolReactorList.
    /// </returns>
    ///
    /// <remarks>
    /// If a list for the reactor class does not exist a new one is created and
    /// returned.
    /// </remarks>
    /// 
    virtual AcRxProtocolReactorList* createReactorList (
                                         AcRxClass* pReactorClass) = 0;

    /// <summary>
    /// Returns an iterator for all of the AcRxProtocolReactorLists instances
    /// contained in the manager. 
    /// </summary>
    ///
    /// <returns>
    /// A pointer to a new AcRxProtocolReactorListIterator that can be used to
    /// enumerate the AcRxProtocolReactorList instances contained in the
    /// manager. 
    /// </returns>
    ///
    /// <remarks>
    /// Callers are responsible for deleting the returned iterator. 
    /// </remarks>
    ///
    virtual AcRxProtocolReactorListIterator* newIterator () const = 0;
};

////////////////////// AcRxProtocolReactorManagerFactory class ////////////////
//

/// <summary>
/// A factory class for obtaining the single AcRxProtocolReactorManager
/// associated
/// </summary>
///
class ADESK_NO_VTABLE AcRxProtocolReactorManagerFactory : public AcRxService
{
public:
    ACRX_DECLARE_MEMBERS(AcRxProtocolReactorManagerFactory);

    /// <summary>
    /// Returns the reactor manager for the specified AcRxClass.
    /// </summary>
    ///
    /// <param name="pRxClass">
    /// A pointer to the AcRxClass with the associated
    /// AcRxProtocolReactorManager.
    /// </param>
    /// 
    /// <returns>
    /// A pointer to the AcRxProtocolReactorManager associated with <paramref
    /// name="pRxClass"/>.
    /// </returns>
    ///
    /// <remarks>
    /// If an AcRxProtocolReactorManager is not associated with the specified
    /// class a new one is created and returned to the caller.
    /// </remarks>
    ///
    virtual AcRxProtocolReactorManager* createReactorManager (
                                        AcRxClass* pRxClass) const = 0;
};

/////////////////////// Macros ////////////////////////////////////////////////
// The following macros facilitate access to framework classes.

// acrxProtocolReactors macro
// Returns a poitner to the global AcRxProtocolReactorManagerFactory instance. 
//

#define acrxProtocolReactors \
AcRxProtocolReactorManagerFactory::cast(acrxServiceDictionary-> \
                                        at(ACRX_PROTOCOL_REACTOR_MANAGER))

// ACRX_PROTOCOL_REACTOR_MANAGER_AT(acrxClass)
// Returns a pointer to the AcRxProtocolReactorManager associated with the 
// specified acrxClass.
//

#define ACRX_PROTOCOL_REACTOR_MANAGER_AT(acrxClass) \
acrxProtocolReactors->createReactorManager(acrxClass)

// ACRX_PROTOCOL_REACTOR_LIST(acrxClass, reactorClass)
// Returns a pointer to the AcRxProtocolReactorList associated with the 
// specified acrxClass and containing zero or more reactorClass instances.
//

#define ACRX_PROTOCOL_REACTOR_LIST_AT(acrxClass, reactorClass) \
    ACRX_PROTOCOL_REACTOR_MANAGER_AT(acrxClass)->createReactorList(reactorClass)

#pragma pack (pop)
