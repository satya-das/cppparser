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
// dbObjectContextInterface.h
//
// DESCRIPTION: Protocol extension base class
//                AcDbObjectContextInterface
//

#pragma once
#pragma pack (push, 8)

#include "acdb.h"
#include "dbmain.h"

class AcDbObjectContext;

const ACDBCORE2D_PORT AcString& acdbAnnotationScaleCollectionName();

////////////////////////////////////////////////////////////////////////
// class AcDbObjectContextInterface
////////////////////////////////////////////////////////////////////////

/// <summary>
/// Abstract protocol extension interface class which allows supporting
/// context-specific behavior on an object.
/// </summary>
///
/// <remarks>
/// Custom objects provide an implementation of this interface and associate
/// with their AcRxClass to provide context-dependent object behavior. One
/// example of such behavior is annotation scalin where the context is the
/// current viewport scale, and where the custom object behavior for text is
/// the text height, orientation, and position. Applications can define other
/// context types (AcDbObjectContext custom classes), store them in custom
/// collections (AcDbObjectContextCollection). By implementing this interface,
/// custom objects expose information about which context types they support
/// and when context instances they participate in. 
/// </remarks>
///
class AcDbObjectContextInterface : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcDbObjectContextInterface);

    /// <summary>
    /// Determines if a particular context type is supported by the object. 
    /// </summary>
    ///
    /// <param name="pObject">
    /// The object supporting the collection.
    /// </param>
    ///
    /// <param name="collectionName">
    /// The name of the collection (context type) to test for support.
    /// </param>
    ///
    /// <returns>
    /// Returns "true" if the object supports context types with the specified
    /// name.
    /// </returns>
    /// 
    /// <remarks>
    /// Whether an object supports a collection type is different from whether
    /// the object currently participates in any contexts of that type. See
    /// also the hasContext() method. 
    /// </remarks>
    virtual bool supportsCollection ( 
                            const AcDbObject* pObject,
                            const AcString&   collectionName ) const = 0;

    /// <summary>
    /// Determines if an object is currently active in a partuclar context. 
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to an object supporting object contexts. 
    /// </param>
    ///
    /// <param name="context">
    /// The context to test.
    /// </param>
    ///
    /// <returns>
    /// Returns true if the object supports the context type and is currently
    /// active in the specified context instance.
    /// </returns>
    virtual bool hasContext ( const AcDbObject*        pObject,
                              const AcDbObjectContext& context ) const = 0;

    /// <summary>
    /// Adds a context to the list of active contexts for an object.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the object to make active in the context.
    /// </param>
    ///
    /// <param name="context">
    /// The context to make active for the object.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the
    /// object does not support the context type. Returns
    /// Acad::eDuplicateRecordName if a context with the specified name already
    /// exists. 
    /// </returns>
    ///
    virtual Acad::ErrorStatus addContext ( 
                                AcDbObject*              pObject,
                                const AcDbObjectContext& context ) const = 0;

    /// <summary>
    /// Removes a contextfrom the list of active contexts for an object.
    /// </summary>
    ///
    /// <param name="pObject">
    /// A pointer to the object to remove the context from.
    /// </param>
    ///
    /// <param name="context">
    /// The context to remove from the object.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the
    /// object does not support the context type. 
    /// </returns>
    ///    
    virtual Acad::ErrorStatus removeContext ( 
                                AcDbObject*              pObject,
                                const AcDbObjectContext& context ) const = 0;
};

#pragma pack (pop)

