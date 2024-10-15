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
//  DESCRIPTION:  
//
//  Interface and classes that implements pickfirst based sub selection
//  and 'picking in space' for entities in a pickfirst set through
//  using a callback mechanism with the AcEdInputPointManager and
//  a specific kind of AcEdInputContextReactor.

#pragma once

#include "acedinpt.h"

// Typedef mapping old name to new name
typedef AcDbFullSubentPathArray AcSubentPathArray;

class AcGiViewport;

// This is the main class which contains all the implementation for
// 'pick in space' hit testing and 'sub-entity-selection' based on
// callbacks from the AcEdInputPointManager. This is a Filter class,
// i.e. needs to be registered with the AcEdInputPointManager
// through addSubSelectFilter(), and likewise removed by 
// removeSubSelectFilter() when the application is unloaded.
// 
// For each type of entity that supports this kind of sub-selection
// it is expected that they will derive a concrete SubSelect filter
// from AcEdSSetSubSelectFilter, and implement the necessary methods
// indicated below.
//
class AcEdSubSelectFilter
{
public:
    virtual ~AcEdSubSelectFilter() { }

    enum SubSelectStatus
    {
        kSubSelectionNone = 0,  // No selection found
        kSubSelectionAugment,   // Add to the pickfirst set
        kSubSelectionExclusive, // Remove other entities from the pickfirst set
        kSubSelectAll           // Select the full entity        
    };

    /**
     * Gets called by the AcEdInputPointManager instance when
     * the Filter is registered. This method is used to determine
     * which Filter to call back for doing 'pick in face' selection
     * for a candidate entity in the pickfirst set or ssget.
     *
     * In case of multiple filters registering themselves for the
     * same class, the first one wins.
     *
     * The internal tests use isKindOf(), i.e. derivation, to check
     * if a filter applies to a candidate entity or not.
     *
     * @param   clsIds  list of classes associated with the filter.
     *
     * @returns eOk if successful.
     */
    virtual Acad::ErrorStatus subSelectClassList(AcArray<AcRxClass*>& clsIds)
    { return Acad::eOk; }


    // The following three methods do the subselection and sub-highlight.

    /**
     * This method is used to ask the application to do the actual
     * hit test, testing for the point in an entity.
     *
     * 
     * @param   wvpt    world pick point
     * 
     * @param   wvwdir   world view direction (-z axis of view coord system)
     *
     * @param   wvwxdir  world x axis direction of view coordinate system
     *
     * @param   wxaper  aperture x rectangle side in world unit. Centered at
     *                  the pick point
     *
     * @param   wyaper  aperture y rectangle side in world unit. Centered at
     *                  the pick point
     *
     *
     * @param   flags   AcEdSSGetFlags for the current selection operation
     *
     * @param   pEnt    AcDbEntity that is to be tested.
     *
     * @returns true if point is in the entity.
     */
    virtual bool selectEntity(
            const AcGePoint3d&  wvpt, 
            const AcGeVector3d& wvwdir,
            const AcGeVector3d& wvwxdir,
            double              wxaper,
            double              wyaper,
            Adesk::Int32        flags,
            const AcGiViewport* pCurVp,
            AcDbEntity*         pEnt) const
    { return false; }

    /**
     * If the above method, i.e. hitTestEntity() returns true, 
     * then createSubSelect() will be invoked by the Input Point Manager,
     * requesting a list of sub-selections that will get highlighted.
     *
     * @param   wpt1    corner1 of box in world coordinates
     *
     * @param   wpt2    corner2 of box in world coordinates 
     *
     * @param   wvdir   world view direction
     *
     * @param   wvwxdir  world Xaxis direction of view coordinate system
     *
     * @param   wxaper  aperture x rectangle side in world unit. Centered at
     *                  the pick point
     *
     * @param   wyaper  aperture y rectangle side in world unit. Centered at
     *                  the pick point
     *
     * @param   seltype one of AcDb::kCrossing or AcDb::kWindow.
     * 
     * @param   bAugment if true, add to current subselection instead of
     *                   replacing it.
     *
     * @param   bIsInPickfirst if true - the entity is already in the pickfirst
     *                  set. If false, the pickfirst logic will attempt
     *                  to subselect the entity directly if desired.
     *
     * @param   bEvery  True if all possible sub-entities should be returned
     * 
     * @param   pCurVP  current viewport in which selection is occurring
     * 
     * @param   pEnt    Entity to be sub-select tested against
     *
     * @param   paths   Result set of subentity paths.
     *
     * @result one of kSubSelectionNone, kSubSelectionAugment,
     *         kSubSelectionExclusive. kSubSelectionExclusive
     *         will remove any other selection in the pickfirst
     *         set, while kSubSelectionAugment will not change
     *         existing contents of the set.
     */
    virtual SubSelectStatus subSelectEntity(
            const AcGePoint3d&        wpt1,
            const AcGePoint3d&        wpt2,
            const AcGeVector3d&       wvwdir,
            const AcGeVector3d&       wvwxdir,
            double                    wxaper,
            double                    wyaper,                             
            AcDb::SelectType          seltype,
            bool                      bAugment,
            bool                      bIsInPickfirstSet,
            bool                      bEvery,
            const AcGiViewport*       pCurVP,
            AcDbEntity*               pEnt,
            AcDbFullSubentPathArray&  paths)
    { return kSubSelectionNone; }

    /**
     * If hitTestEntity() returns true then createSubSelect() will be invoked
     * by the Input Point Manager, requesting a list of sub-selections that
     * will get highlighted. This overload gets called after the preceding
     * signature if the preceding method returns kSubSelectNone.
     *
     * @param   pResbuf result buffer chain describing the selection criteria
     *                  of the same form as returned by acedSSNameEx.
     *
     * @param   bAugment if true, add to current subselection instead of
     *                   replacing it.
     *
     * @param   bIsInPickfirst if true - the entity is already in the pickfirst
     *                  set. If false, the pickfirst logic will attempt
     *                  to subselect the entity directly if desired.
     *
     * @param   bEvery  if true return all possible sub-entities. 
     * 
     * @param   pCurVP  current viewport in which selection is occurring
     * 
     * @param   pEnt    Entity to be sub-select tested against
     *
     * @param   paths   Result set of subentity paths.
     *
     * @result one of kSubSelectionNone, kSubSelectionAugment,
     *         kSubSelectionExclusive. kSubSelectionExclusive
     *         will remove any other selection in the pickfirst
     *         set, while kSubSelectionAugment will not change
     *         existing contents of the set.
     */

    virtual SubSelectStatus subSelectEntity(
            const resbuf*             pResbuf,
            bool                      bAugment,
            bool                      bIsInPickfirstSet,
            bool                      bEvery,
            const AcGiViewport*       pCurVP,
            AcDbEntity*               pEnt,
            AcDbFullSubentPathArray&  paths)
    { return kSubSelectionNone; }

    /**
     * Invoked to re-select, if necessary, based on the current entity
     * sub-selection state. Where the state is remembered is really upto
     * the Filter/Entity implementation.
     *
     * If the entity needs to have its sub-selection recomputed, this
     * method should modify paths to reflect the correct new subselection.
     * If the entity does not need to make any changes, paths will be left
     * alone.
     * 
     * @param pEnt   the entity whose subselection is being refreshed
     *
     * @param paths  the current list of Full Subent paths that reflect the
     *               current subselection state of the entity. This is both
     *               and input and output argument. The entity can modify this
     *               to reflect the true subentity paths for its current
     *               subselection state. Else it can leave them alone.
     *
     * @returns   true if the entity altered the paths argument. False if not
     */
    virtual bool reSubSelectEntity(AcDbEntity* pEnt,
            AcDbFullSubentPathArray& paths)
    { return false; }
    /**
     * In case the sub-selection is cancelled, the reactor is notified
     * by this method. Typical uses of this filter include tracking
     * sub selection state within the reactor. So this method says
     * to clear that state.
     *
     * @param    id    entity whose state is to be cancelled.
     *
     * @returns true if the entity was actually sub-selected.
     */
    virtual bool cancelSubSelect(AcDbEntity* pEnt)
    { return false; }

    /**
     * Similar method to cancelSubSelect, except - all entities
     * have been un-subselected, and the filter must take
     * appropriate action
     *
     * @returns true if an entity was actually sub-selected.
     */
    virtual bool cancelAllSubSelect()
    { return false; }


    /**
     * React to keyboard input - and take appropriate action,
     * if necessary. This is invoked only for the currently active filters.
     *
     * @param wMsg  windows message, one of
     *              WM_SYSKEYDOWN
     *              WM_SYSKEYUP
     *              WM_KEYDOWN
     *              WM_KEYUP
     *              WM_CHAR
     *              etc.
     *              
     * @param char  character typed
     *
     * @param rptcnt repetition count
     *
     * @param flags  windows flags (see OnKeyDown())
     *
     * @returns true if message was intercepted and no more processing
     *   by other filters must happen. False if it is ok for the controlling
     *   logic to invoke other filters' onKeyDown() message handling.
     */
    virtual bool onKey(Adesk::UInt32 wMsg, unsigned int nChar, 
            unsigned int rptCnt, unsigned int flags)
    { return false; }


    /**
     * @returns true if the entity is subselected.
     */
    virtual bool isSubSelected(AcDbEntity* pEnt) const
    { return false; }

};

