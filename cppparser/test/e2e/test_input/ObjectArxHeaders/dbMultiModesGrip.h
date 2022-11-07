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
//  dbMultiModesGrip.h - public header file for AcDbMultiModesGripPE API
//

#ifndef _DBMULTIMODESGRIP_H
#define _DBMULTIMODESGRIP_H

#include "acdb.h"
#include "dbmain.h"
#include "acstring.h"
#pragma pack (push, 8)

////////////////////////////////////////////////////////////////////////
// class AcDbMultiModesGripPE (abstract)
////////////////////////////////////////////////////////////////////////

/// <summary>
/// The protocol extension interface that specifies how, when implemented and
/// registered as a protocol extension to an AcDbEntity derived class, to 
/// communicate with the grip editing complex for information on what alternatives
/// it can provide to stretching grip points. These alternatives are represented 
/// as an array of modes (of type AcDbMultiModesGripPE::GripMode). The grip editing
/// complex will be responsible for querying all available modes, interacting with user
/// to set the current mode or switching between modes, and either proceeding with dragging
/// a grip (if the current mode's action type is kDragOn), or calling moveGripPointsAt 
/// once (if the current mode's action type is kImmediate), or executing a command 
/// (if the current mode's action type is kCommand). Clients who implement 
/// AcDbMultiModesGripPE are responsible to maintain the "current" mode and provide
/// runtime behavior for any given mode.
/// </summary>
///
/// <remarks>
/// On hovering a warm grip, the AutoCAD grip complex querys the grip'ed
/// object for this protocol exetension and retrieve available modes. The
/// current mode can be set during warm grip stage through a multi-mode
/// UI or during hot grip editing, through Ctrl-cycling or context menu 
/// selection.
///
/// Client who implements this PE for a given object type (AcDbEntity derived)
/// should either own the object type so it can directly make its moveGripPointsAt 
/// mode-aware, or should overrule the object's runtime moveGripPointsAt behavior
/// through AcDbGripOverrule.
/// </remarks>
///

class ADESK_NO_VTABLE AcDbMultiModesGripPE  :  public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbMultiModesGripPE);

    /// <summary>
    /// The type of a grip.
    /// </summary>
    enum GripType 
    { 
        /// <summary>
        /// The primary grip. Always shown if host's GRIPS variable is not 0;
        /// </summary>
        kPrimary,

        /// <summary>
        /// The secondary grip. Only shown when host's GRIPS variable is 2;
        /// </summary>
        kSecondary 
    };

    /// <summary>
    /// The numerical identifier of a grip mode.
    /// </summary>
    enum GripModeIdentifier
    {
        /// <summary>
        /// Default
        /// </summary>
        kNone = 0,

        /// <summary>
        /// Stretch at the grip point
        /// </summary>
        kMove,

        /// <summary>
        /// The start of custom mode types.
        /// All custom mode types should be larger than this value.
        /// </summary>
        kCustomStart = 100,
    };

    /// <summary>
    /// The type of actions the grip editing complex takes when a mode
    /// is becoming current.
    /// </summary>
    enum GripActionType
    {
        /// <summary>
        /// Instructs the grip editor to proceed with dragging. The mode
        /// specific behavior is determined by object's moveGripPointsAt
        /// current mode awareness.
        /// </summary>
        kDragOn = 0,

        /// <summary>
        /// Instructs the grip editor to call moveGripPointsAt once and
        /// end dragging sequence.
        /// </summary>
        kImmediate,

        /// <summary>
        /// External command, specified as GripMode::CommandString, is called.
        /// </summary>
        kCommand,
    };

    /// <summary>
    /// The type of canvas cursor can be specified for each mode.
    /// </summary>
    enum GripCursorType
    {
        /// <summary>
        /// No cursor change, using default.
        /// </summary>
        kcNone = 0,

        /// <summary>
        /// Default cursor combined with a plus sign.
        /// </summary>
        kcCrosshairPlus,         
        
        /// <summary>
        /// Default cursor combined with a minus sign.
        /// </summary>
        kcCrosshairMinus,

        /// <summary>
        /// Default cursor combined with a curve sign.
        /// </summary>        
        kcCrosshairCurve,

        /// <summary>
        /// Default cursor combined with a straight line sign.
        /// </summary>
        kcCrosshairLine,      
        
        /// <summary>
        /// Default cursor combined with an angle sign. For future use.
        /// </summary>
        kcCrosshairAngle,      
    };

    /// <summary>
    /// The type that contains all information to present a single mode.
    /// </summary>
    struct GripMode
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        GripMode();

        /// <summary>
        /// The unique identifier among the collection of modes this PE implements. 
        /// </summary>
        unsigned int    Mode;

        /// <summary>
        /// The display string of this mode in various UI elements (including haver menu and object context menu).
        /// </summary>
        AcString        DisplayString;

        /// <summary>
        /// The string tool tip of this mode. (For future use.)
        /// </summary>
        AcString        ToolTip;

        /// <summary>
        /// The command line version of display string for this mode.
        /// </summary>
        AcString        CLIDisplayString;

        /// <summary>
        /// The command line prompt string when this mode is switched as current.
        /// </summary>
        AcString        CLIPromptString;

        /// <summary>
        /// The command line keyword list associated to CLIPromptString.
        /// </summary>
        AcString        CLIKeywordList;

        /// <summary>
        /// The type of cursor this mode uses.
        /// </summary>
        GripCursorType  CursorType;

        /// <summary>
        /// The action type of this mode uses.
        /// </summary>
        GripActionType  ActionType;

        /// <summary>
        /// Optional. If the action type is kCommand, the command used for this mode.
        /// </summary>
        AcString        CommandString;
    };

    /// <summary>
    /// Queries an object, on a given grip point, for the available modes it provides. It also
    /// returns the mode that is current.
    /// </summary>
    /// <param name="pThis"> 
    /// The AcDbEntity whose modes are requested. The object needs to be open
    /// at least for read.
    /// </param>
    /// <param name="pGripData"> The grip whose modes are requested. </param>
    /// <param name="modes"> The returned array of availabe modes. </param>
    /// <param name="curMode"> The returned identifier of current mode. </param>
    /// <returns> true if successful. </returns>
    ///
    virtual bool getGripModes(AcDbEntity* pThis, 
                              AcDbGripData* pGripData, 
                              AcArray<GripMode>& modes, 
                              unsigned int& curMode) const = 0;
   
    /// <summary>
    /// Gets the current mode identifier.
    /// </summary>
    /// <param name="pThis"> The AcDbEntity whose current mode id is requested. </param>
    /// <param name="pGripData"> The grip whose mode id is requested. </param>
    /// <returns> The returned identifier of current mode. </returns>
    ///
    virtual unsigned int mode(AcDbEntity* pThis, AcDbGripData* pGripData) const = 0;

    /// <summary>
    /// Gets the current mode.
    /// </summary>
    /// <param name="pThis"> The AcDbEntity whose current mode is requested. </param>
    /// <param name="pGripData"> The grip whose mode is requested. </param>
    /// <returns> The mode object which is current. </returns>
    ///
    virtual GripMode modeEx(AcDbEntity* pThis, AcDbGripData* pGripData) const = 0;

    /// <summary>
    /// Sets the current mode.
    /// </summary>
    /// <param name="pThis"> The AcDbEntity whose current mode is to be set current. </param>
    /// <param name="pGripData"> The grip whose current mode is to be set current. </param>
    /// <param name="newMode"> The numerical identifier for the new current mode. </param>
    /// <returns> true of successful. </returns>
    ///
    virtual bool setMode(AcDbEntity* pThis, AcDbGripData* pGripData, unsigned int newMode) = 0;

    /// <summary>
    /// Gets the grip type of a given grip.
    /// </summary>
    /// <param name="pThis"> The AcDbEntity whose grip type is requested. </param>
    /// <param name="pGripData"> The grip whose grip type is requested. </param>
    /// <returns> The grip type of the grip. </returns>
    ///
    virtual GripType gripType(AcDbEntity* pThis, AcDbGripData* pGripData) const = 0;

    /// <summary>
    /// resets current mode to default (up to each concrate class to say what is the default).
    /// </summary>
    /// <param name="pThis"> The AcDbEntity whose current mode is reset to default. </param>
    virtual void reset(AcDbEntity* pThis) = 0;
};

inline AcDbMultiModesGripPE::GripMode::GripMode()
        : Mode(AcDbMultiModesGripPE::kMove)
        , ActionType(kDragOn)
        , CursorType(kcNone)
{
}

#pragma pack (pop)

#endif  // _DBMULTIMODESGRIP_H

