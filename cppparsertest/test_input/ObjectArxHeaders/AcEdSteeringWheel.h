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
// Name:            AcEdSteeringWheel.h
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "acgs.h"
#include "dbNavSettings.h"

class AcEdSteeringWheelReactor;
class AcEdSteeringWheel;

AcEdSteeringWheel* acedCreateSteeringWheel ();
void acedDestroySteeringWheel(AcEdSteeringWheel* pWheel);

///////////////////////////////////////////////////////////////////////////////
//
// Interface AcEdSteeringWheel
//
class AcEdSteeringWheel
{
public:
    enum WheelType
    {
        kExterior = 0,		///< View Object Wheel.
        kInterior,			///< Tour Buiding Wheel.
        kFull,				///< Full Navigation Wheel.
        k2D,                ///< 2D Steering Wheel.
        kMini,		        ///< Mini View Object Wheel.
        kMiniOther,	        ///< Mini Tour Building Wheel.
        kMiniEight,	        ///< Mini Full Navigation Wheel.

        kTotalCount,		///< Total number of SteeringWheel types.
        kWheelNone			///< Marks a disabled SteeringWheel.
    };

    enum MenuType
    {
        // Steering Wheel Menus
        kMenuNone = 0,
        kMenuInterior,
        kMenuExterior,
        kMenuFull,
        kMenu2D
    };

    // Message handlers
    virtual void    onKeyDown     (UINT nChar, UINT nRepCount, UINT nFlags) = 0;
    virtual void    onKeyUp       (UINT nChar, UINT nRepCount, UINT nFlags) = 0;
    virtual bool    onMouseWheel  (UINT nFlags, short zDelta, POINT pt) = 0;
    virtual void    onMouseMove   (UINT nFlags, POINT pt) = 0;
    virtual void    onLButtonUp   (UINT nFlags, POINT pt) = 0;
    virtual void    onLButtonDown (UINT nFlags, POINT pt) = 0;
    virtual void    onRButtonUp   (UINT nFlags, POINT pt) = 0;
    virtual void    onRButtonDown (UINT nFlags, POINT pt) = 0;
    virtual void    onMButtonDown (UINT nFlags, POINT pt) = 0;
    virtual void    onMButtonUp (UINT nFlags, POINT pt) = 0;

    virtual void    setHomeCamera (const AcDbHomeView& home) = 0;
    virtual bool    setLargeWheelOpacity  (int nOpacity) = 0;
    virtual int     getLargeWheelOpacity  () = 0;
    virtual bool    setMiniWheelOpacity  (int nOpacity) = 0;
    virtual int     getMiniWheelOpacity  () = 0;
    virtual bool    setWalkSpeed(double speed) = 0;
    virtual double  getWalkSpeed() = 0;
    virtual bool    setActiveWheel(WheelType type) = 0;
    virtual WheelType   getActiveWheel() = 0;
    virtual void    enableWheel (bool enable) = 0;
    virtual bool    isWheelEnabled() = 0;

    virtual AcGsModel * getModel() = 0;
    virtual AcGsView *  getView()  = 0;
    virtual HWND        getDeviceHandle() = 0;

    virtual bool    attachView      (HWND hDevice, AcGsView* pGsView) = 0;
    virtual void    detachView      () = 0;

    virtual void    addReactor  (AcEdSteeringWheelReactor* pReactor) = 0;
    virtual void    removeReactor(AcEdSteeringWheelReactor* pReactor) = 0;

};

///////////////////////////////////////////////////////////////////////////////
//
// Interface AcEdSteeringWheelReactor
//
class AcEdSteeringWheelReactor
{
public:
    virtual void    modifyContextMenu(HMENU hMenu) = 0;
    virtual void    onSetCursor(HCURSOR hCursor) = 0;
    virtual void    onBeginOperation() = 0;
    virtual void    onEndOperation() = 0;
    virtual void    onBeginShot() = 0;
    virtual void    onEndShot() = 0;
    virtual void    onClose() = 0;
};
