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

#ifndef ACAPWINDOW_H
#define ACAPWINDOW_H

#include "IAdHostWindow.h"
class AcApWindowImp;

// Note: any class derives from AcApWindow is responsible of creating
// an AcApWindowImp instance for m_pImp
//
class AcApWindow : public IAdHostWindow
{
public:
    /// <summary> 
    /// Allows core to process a message before it has been handled
    /// by the host application. 
    /// </summary>
    /// <param name=message>
    /// The type of the message being sent. 
    /// </param>
    /// <param name=wParam>
    /// Message parameter, content is message dependent. 
    /// </param>
    /// <param name=lParam>
    /// Message parameter, content is message dependent.
    /// </param>
    /// <param name="lResult">
    /// Message dependent output results.
    /// </param>
    /// <returns>
    /// Returns true if the message was handled by core and should not be 
    /// dispatched to the application for normal handling. 
    /// </returns>
    /// <remarks>
    /// The messageId, lParam, wParam, and lparam values supported by this
    /// method are identical to those defined by Microsoft for windows
    /// messages. Applications will typically call this function for all
    /// messages received by the host prior to performing any message mapping
    /// or handling of the message in the host. 
    /// </remarks>
    ACCORE_PORT bool  preRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, Adesk::LongPtr& lResult);

    /// <summary> 
    /// Sends a message to the view for handling. 
    /// </summary>
    /// <param name=message>
    /// The type of the message being sent. 
    /// </param>
    /// <param name=wParam>
    /// Message parameter, content is message dependent. 
    /// </param>
    /// <param name=lParam>
    /// Message parameter, content is message dependent.
    /// </param>
    /// <param name="lResult">
    /// Message dependent output results.
    /// </param>
    /// <returns>
    /// Returns true if the message was handled by core in any way. Returns
    /// false if core does not handle this message. 
    /// </returns>
    /// <remarks>
    /// A routeMessage() call will be ignored if preRouteMessage() has not
    /// been called for the same message Id
    ///
    /// The messageId, lParam, wParam, and lparam values supported 
    /// by this method are identical to those defined by Microsoft 
    /// for windows messages. Applications typically call this method
    /// from their message handler for the message.
    /// </remarks>
    ACCORE_PORT bool     routeMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, Adesk::LongPtr& lResult);

    /// <summary> 
    /// Cleanup message information sent to the view in preRouteMessage(). 
    /// </summary>
    /// <param name=message>
    /// The type of the message being sent. 
    /// </param>
    /// <param name=wParam>
    /// Message parameter, content is message dependent. 
    /// </param>
    /// <param name=lParam>
    /// Message parameter, content is message dependent.
    /// </param>
    /// <param name="lResult">
    /// Message dependent output results.
    /// </param>
    /// <returns>
    /// Returns true if the same message has been sent in preRouteMessage();
    /// returns false otherwise. 
    /// </returns>
    /// <remarks>
    /// A preRouteMessage() call must be followed by postRouteMessage() with
    /// the same message
    /// </remarks>
    ACCORE_PORT bool postRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, Adesk::LongPtr& lResult);

protected:
    /// <summary>Initializes an instance of AcApWindow. any class derives from AcApWindow is responsible of creating
    /// an AcApWindowImp instance for m_pImp.</summary>
    ACCORE_PORT AcApWindow();

    /// <summary>Destroy an instance of AcApWindow. m_pImp will be deleted in this function.</summary>
    ACCORE_PORT virtual ~AcApWindow();

    /// <summary> 
    /// Allows sub-class to process a message before it has been handled
    /// by the host application. It's empty function in this class.
    /// </summary>
    /// <param name="message">
    /// The type of the message being sent. 
    /// </param>
    /// <param name="wParam">
    /// Message parameter, content is message dependent. 
    /// </param>
    /// <param name="lParam">
    /// Message parameter, content is message dependent.
    /// </param>
    /// <param name="lResult">
    /// Message dependent output results.
    /// </param>
    /// <returns>
    /// Always return false.
    /// </returns>
    /// <remarks>
    /// The messageId, lParam, wParam, and lparam values supported by this
    /// method are identical to those defined by Microsoft for windows
    /// messages. This function will be invoked at end of preRouteMessage if message
    /// is not handled by preRouteMessage function.
    /// </remarks>
    ACCORE_PORT virtual bool subPreRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, Adesk::LongPtr& lResult);

    /// <summary> 
    /// Sends a message to the sub-class for handling if it's not handled by 
    /// routeMessage. It's empty function in this class.
    /// </summary>
    /// <param name="message">
    /// The type of the message being sent. 
    /// </param>
    /// <param name="wParam">
    /// Message parameter, content is message dependent. 
    /// </param>
    /// <param name="lParam">
    /// Message parameter, content is message dependent.
    /// </param>
    /// <param name="lResult">
    /// Message dependent output results.
    /// </param>
    /// <returns>
    /// Always return false.
    /// </returns>
    /// <remarks>
    /// The messageId, lParam, wParam, and lparam values supported by this
    /// method are identical to those defined by Microsoft for windows
    /// messages. This function will be invoked at end of routeMessage if message
    /// is not handled by routeMessage function.
    /// </remarks>
    ACCORE_PORT virtual bool subRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, Adesk::LongPtr& lResult);

    /// <summary> 
    /// Cleanup message information sent to the sub-class.
    /// It's empty function in this class.
    /// </summary>
    /// <param name="message">
    /// The type of the message being sent. 
    /// </param>
    /// <param name="wParam">
    /// Message parameter, content is message dependent. 
    /// </param>
    /// <param name="lParam">
    /// Message parameter, content is message dependent.
    /// </param>
    /// <param name="lResult">
    /// Message dependent output results.
    /// </param>
    /// <returns>
    /// Always return false.
    /// </returns>
    /// <remarks>
    /// The messageId, lParam, wParam, and lparam values supported by this
    /// method are identical to those defined by Microsoft for windows
    /// messages. This function will be invoked at end of postRouteMessage if message
    /// is not handled by postRouteMessage function.
    /// </remarks>
    ACCORE_PORT virtual bool subPostRouteMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, Adesk::LongPtr& lResult);

    friend class AcApWindowImp;
    AcApWindowImp* m_pImp;
};

#endif //ACAPWINDOW_H
