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
// DESCRIPTION: Abstract base class for collections of AcDbObjectContext
//              objects

#ifndef ACDB_OBJECTCONTEXTCOLLECTION_H
#define ACDB_OBJECTCONTEXTCOLLECTION_H

#pragma once

#include "acdb.h"
#include "dbmain.h"
#include "AcString.h"
#include "dbObjContext.h"

#pragma pack (push, 8)

class AcDbObjectContextCollectionIterator;

////////////////////////////////////////////////////////////////////////
// class AcDbObjectContextCollection 
////////////////////////////////////////////////////////////////////////

/// <summary>
/// An interface to an application-defined collection of AcDbObjectContext
/// objects. 
/// </summary>
///
/// <remarks>
/// Applications implement this interface to define custom object contexts for
/// their context-sensitive objects. Applications must instantiate an instance
/// of the collection (typically one instance for each database) and register
/// it with the AcDbObjectContextCollectionManager for each AcDbDatabase which
/// needs to support the context type. Each context collection has state,
/// represented by the collection of contexts, the "current" context, and the
/// ability to lock or unlock context instances. 
/// </remarks>
///
class ADESK_NO_VTABLE AcDbObjectContextCollection: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectContextCollection);

    /// <summary>
    /// The name of the context collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns the name of the context collection.
    /// </returns>
    ///
    /// <remarks>
    /// Context collections must return a non-empty string from this method.
    /// The name of the collection is used to identify the collection to the
    /// manager, and to identify the kinds of context objects that may be added
    /// to the collection. (See also AcDbObjectContext::collectionName()).
    /// </remarks>
    virtual AcString            name() const = 0;

    /// <summary>
    /// The current context for the collection.
    /// </summary>
    ///
    /// <param name="pRequestingObject">
    /// A pointer to the AcDbObject requesting the current context,
    /// may be NULL.
    /// </param>
    ///
    /// <returns>
    /// Returns a pointer to a copy of the currently active context in 
    /// the collection, or NULL if there is no active context. 
    /// </returns>
    ///
    /// <remarks>
    /// Context collections support a single current context. Some collections
    /// may support business logic where, depending on the requesting object,
    /// the collection exposes a different current context than the one
    /// last specified via a call to setCurrentContext(). For example, 
    /// an application may attach data to custom objects which it uses to 
    /// determine the current context when the custom object is passed to this
    /// method.  Applications are responsible for deleting the returned object. 
    /// </remarks>
    ///
    virtual AcDbObjectContext*  currentContext(
                        const AcDbObject* pRequestingObject) const = 0;

    /// <summary>
    /// Sets the current context for the collection.
    /// </summary>
    ///
    /// <param name="pContext">
    /// A pointer to the context to make current for the collection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if the context is made current.
    /// </returns>
    ///
    /// <remarks>
    /// For a context to become active a context with the same identifier
    /// (AcDbObjectContext::uniqueIdentifier()) must be present in the
    /// collection. 
    /// </remarks>
    ///
    virtual Acad::ErrorStatus   setCurrentContext(
                                        const AcDbObjectContext* pContext) = 0;

    /// <summary>
    /// Adds a copy of a context to the collection.
    /// </summary>
    ///
    /// <param name="pContext">
    /// A pointer to the context to copy and add to the collection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Because the unique identifier of the collection resident contexts must
    /// be unique, the copied context added to the collection may be assigned
    /// a different identifier than the context it is copied from. 
    /// </remarks>
    virtual Acad::ErrorStatus   addContext(
                                        const AcDbObjectContext* pContext) = 0;

    // to set the currentContext() to NULL. 
    /// <summary>
    /// Removes a context from the collection.
    /// </summary>
    ///
    /// <param name="contextName">
    /// The name of the context to remove from the collection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if no such
    /// context exists in the collection. Returns Acad::eObjectIsReferenced if
    /// the scale is the current scale.
    /// </returns>
    ///
    /// <remarks> 
    /// The active context cannot be removed from a collection.
    /// </remarks>
    /// 
    virtual Acad::ErrorStatus   removeContext(
                                        const AcString& contextName) = 0;

    /// <summary>
    /// For internal use only.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// For internal use only.
    /// </remarks>
    virtual Acad::ErrorStatus   lockContext(
                                        const AcDbObjectContext* pContext) = 0;
    /// <summary>
    /// For internal use only.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// For internal use only.
    /// </remarks>
    virtual Acad::ErrorStatus   unlockContext() = 0;

    /// <summary>
    /// For internal use only.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the collection is locked. 
    /// </returns>
    /// 
    /// <remarks>
    /// For internal use only.
    /// </remarks>
    virtual bool                locked() const = 0;

    /// <summary>
    /// Gets a copy of a context with the specified name. 
    /// </summary>
    ///
    /// <param name="contextName">
    /// The name of the context to copy and return.
    /// </param>
    ///
    /// <returns>
    /// Returns a pointer to a copy of the specified context, or NULL if no
    /// such context exists in the collection.
    /// </returns>
    ///
    /// <remarks>
    /// Callers are responsible for freeing the copy of the context by calling
    /// delete on the returned pointer.
    /// </remarks>
    ///
    virtual AcDbObjectContext*  getContext(
                                        const AcString& contextName) const = 0;

    /// <summary>
    /// Determines whether a context with the specified name exists in the
    /// collection.
    /// </summary>
    ///
    /// <param name="contextName">
    /// The name of the context to find.
    /// </param>
    ///
    /// <returns>
    /// Returns true if a context with the specified name exists in the
    /// collection.
    /// </returns>
    ///
    virtual bool                hasContext(
                                        const AcString& contextName) const = 0;

    /// <summary>
    /// Returns a private iterator to the contexts in the collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns a pointer to an AcDbObjectContextCollectionIterator that callers
    /// can use to enumerate the contexts in the collection.
    /// </returns>
    ///
    /// <remarks>
    /// Callers are responsible for freeing the iterator when it is no longer 
    /// needed by calling delete on the returned pointer.
    /// </remarks>
    ///
    virtual AcDbObjectContextCollectionIterator* newIterator() const = 0;
};


////////////////////////////////////////////////////////////////////////
// class AcDbObjectContextCollectionIterator
////////////////////////////////////////////////////////////////////////

/// <summary>
/// An iterator iterface for AcDbObjectContext objects stored in an
/// AcDbObjectContextCollection.
/// </summary>
///
/// <remarks>
/// Callers obtain an iterator by calling
/// AcDbObjectContextCollection::newIterator(). Applications that provide
/// custom AcDbObjectContextCollection implementations must also implement this
/// interface in a custom iterator for their collection. 
/// </remarks>
///
class ADESK_NO_VTABLE AcDbObjectContextCollectionIterator : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbObjectContextCollectionIterator);
    
    /// <summary>
    /// Positions the iterator to the beginning of the collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    ///
    virtual Acad::ErrorStatus start() = 0;

    /// <summary>
    /// Positions the iterator to the next context in the collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the iterator was positioned to a context in the
    /// collection, or false if it has reached the end of the collection.
    /// </returns>
    virtual bool              next() = 0;

    /// <summary>
    /// Determines whether the iterator has reached the end of the collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if the iterator has reached the end of the collection.
    /// </returns>
    /// 
    virtual bool              done() const = 0;
    
    /// <summary> 
    /// Retrieves a copy of the context at the current position of the
    /// iterator. 
    /// </summary>
    ///
    /// <param name="pObjectContext">
    /// Pointer to a copy of the context at the current iterator position.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful and a copy of the context was returned. 
    /// </returns>
    ///
    /// <remarks>
    /// Callers are responsible for deleting the returned copy of the context
    /// by calling delete on the returned pointer when it is no longer needed. 
    /// </remarks>
    ///
    virtual Acad::ErrorStatus getContext(AcDbObjectContext*& pObjectContext) const = 0;
};
#pragma pack (pop)

#endif
