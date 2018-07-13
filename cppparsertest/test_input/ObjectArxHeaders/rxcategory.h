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

#pragma once

#include "acbasedefs.h"
#include "adesk.h"
#include "acadstrc.h"
#include "pimplapi.h"

/// <summary>
/// Provides hierarchical information about property categorization to UI
/// clients. AcRxCategory instances can be referenced by name from
/// AcRxCategoryAttributes attached to AcRxProperty instances. The position of
/// an AcRxCategory instance in the global AcRxCategory tree can be used by
/// clients to determine the location of the property relative to other
/// properties when realized in a UI (such as a property browser).
/// AcRxAttributes can be attached to application-supplied AcRxCategory
/// instances to provide additional information about the AcRxCategory,
/// including descriptions, localized category names, relative weighting, etc. 
/// </summary>
class AcRxCategory : public AcRxMember
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxCategory, ACBASE_PORT);

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="name">
    /// The name of the category.
    /// </param>
    /// <param name="pOwner">
    /// A pointer to the owning category, must be non-NULL.
    /// </param>
    /// <remarks>
    /// Child category lifetimes are determined by the lifetime of their owner.
    /// When a category is freed all of its children are also freed. 
    /// </remarks>
    ACBASE_PORT AcRxCategory(const ACHAR* name, AcRxCategory* pOwner) throw();

   
    /// <summary>
    /// Removes a child category from an owning category.
    /// </summary>
    /// <param name="pChildCategory>
    /// A pointer to the child category to remove. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful. Returns Acad::eKeyNotFound if the
    /// child could not be found on this object. 
    /// </returns>
    ACBASE_PORT Acad::ErrorStatus removeChild(AcRxCategory* pChildCategory);

    /// <summary>
    /// Recursively finds the first descendant category with the specified
    /// name.
    /// </summary>
    /// <param name="name">
    /// The name of the descendant category to find. 
    /// </param>
    /// <returns>
    /// A pointer to the category. NULL if no matching category was found.
    /// </returns>
    /// <remarks>
    /// The search uses a bread-first recursive traversal of the category tree
    /// beneath the referenced category. The first descendant with a matching
    /// name is returned to the caller. 
    /// </remarks>
    ACBASE_PORT AcRxCategory* findDescendant(const ACHAR* name) const;

    /// <summary>
    /// The special, global root category node. All application-supplied
    /// categories should be added to the root category or one of its
    /// descendants. 
    /// </summary>
    ACBASE_PORT static AcRxCategory* rootCategory(); 
private:
    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor frees all children categories.
    /// <remarks>
    ACBASE_PORT virtual ~AcRxCategory();
};

ACBASE_PORT Acad::ErrorStatus
acdbGetLegacyCategoryId(const AcRxCategory* pCategory, int& legacyId);

ACBASE_PORT Acad::ErrorStatus
acdbSetLegacyCategoryId(AcRxCategory* pCategory, int legacyId);