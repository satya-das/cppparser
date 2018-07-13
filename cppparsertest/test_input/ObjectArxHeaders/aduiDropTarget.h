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
// Purpose:
// 
// Derives from COleDropTarget to implement drop target
// The palette set and palette creates this object as a member and calls 
// Register() to register itself as target window for drag and drop.
// Routes the drag messages to the registered window to let it handle the 
// drag messages.
// 
//////////////////////////////////////////////////////////////////////////////
#ifndef _ADUI_DROP_TARGET_H_
#define _ADUI_DROP_TARGET_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// These messages are for ***INTERNAL USE ONLY***
//Drag and drop messages to send to the target window
//
#define UM_ADUI_DRAGENTER				(WM_USER + 120)
#define UM_ADUI_DRAGOVER				(WM_USER + 121)
#define UM_ADUI_DRAGLEAVE				(WM_USER + 122)
#define UM_ADUI_DROP					(WM_USER + 123)
#define UM_ADUI_DROPEX					(WM_USER + 124)
#define UM_ADUI_DRAGSCROLL				(WM_USER + 125)

#ifndef _ADESK_MAC_

//Structure to hold the drag and drop data to be sent to the target window 
//while sending drag and drop messages 
//
typedef struct tagADUI_DRAGDATA
{
	// Pointer to the window the cursor is entering/leaving or currently over.
	CWnd				*	mpWnd;
	// Data object. Valid for UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER, 
	// UM_ADUI_DROP and UM_ADUI_DROPEX.
	COleDataObject		*	mpDataObject;
	// State of the modifier keys. This is a combination of any number of 
	// the following: MK_CONTROL, MK_SHIFT, MK_ALT, MK_LBUTTON, MK_MBUTTON,
	// and MK_RBUTTON. Valid for UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER.
	DWORD					mdwKeyState;
	// Current location of cursor in client co-ordinates. Valid for 
	// UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER, UM_ADUI_DROP and 
	// UM_ADUI_DROPEX
	POINTL					mPoint;
	// The drop effect that the user chose for the default drop operation 
	// based on the current key state. Valid for UM_ADUI_DROP and 
	// UM_ADUI_DROPEX.
	DROPEFFECT				mDropEffect;
	// List of the drop effects that the drop source supports. Valid for 
	// UM_ADUI_DROPEX
	DROPEFFECT				mDropList;

} ADUI_DRAGDATA,*PADUI_DRAGDATA;

// This class is for ***INTERNAL USE ONLY***
// CAdUiDropTarget class is used to make a window a drag and drop target. 
// Declare a member variable of this class in the CWnd derived class which 
// is to be made drop target and call CAdUiDropTarget::Register() to 
// register the window as drop target. The drag and drop messages received 
// by this object is routed back to the respective window which contains 
// this object as UM_ADUI_xxx messages. The drag and drop messages are 
// UM_ADUI_DRAGENTER, UM_ADUI_DRAGOVER, UM_ADUI_DRAGLEAVE, UM_ADUI_DROP, 
// UM_ADUI_DROPEX, UM_ADUI_DRAGSCROLL. All the messages except UM_ADUI_DRAGLEAVE 
// contain ADUI_DRAGDATA structure pointer as lParam. 
// Handle these messages in the window class and return appropriate return value.
//
#pragma warning(push)
#pragma warning(disable : 4275)
class CAdUiDropTarget : public COleDropTarget
{
public:
    CAdUiDropTarget();
    // For internal use only
    CAdUiDropTarget(int nId);
    ~CAdUiDropTarget();

    // For internal use only
    BOOL            SetTargetWindowForMessages(CWnd* pWnd);

protected:
    virtual DROPEFFECT 	OnDragEnter			(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DWORD dwKeyState, 
											 CPoint point);
    virtual DROPEFFECT 	OnDragOver			(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DWORD dwKeyState, 
											 CPoint point);
    virtual BOOL		OnDrop				(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DROPEFFECT 	dropEffect, 
											 CPoint point);
    virtual DROPEFFECT 	OnDropEx			(CWnd* pWnd, 
											 COleDataObject* pDataObject, 
											 DROPEFFECT dropDefault, 
											 DROPEFFECT dropList, 
											 CPoint point);
    virtual void		OnDragLeave			(CWnd* pWnd);
    virtual DROPEFFECT  OnDragScroll	    (CWnd* pWnd,
									         DWORD dwKeyState, 
										     CPoint point);

protected:
    DWORD		mdwKeyState;
    int                 mnId;
    CWnd            *   mpTargetWnd;
};
#pragma warning(pop)
#endif  // _ADESK_MAC_
#endif // _ADUI_DROP_TARGET_H_
