//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// DESCRIPTION
//
//   Declarations to support AdUi registered messages.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _aduiMessage_h
#define _aduiMessage_h
#pragma pack (push, 8)

#pragma once

/////////////////////////////////////////////////////////////////////////////
// AdUi registered message
//
//  Notifications are usually sent via SendMessage() as follows:
//      message     set to the registered message, AdUiMessage().
//      wParam      HIWORD is ADUI_NOTIFY code, LOWORD varies with notification
//                  but is usually a control's ID (may be 0).
//      lParam      usually points to notification-specific data, may be NULL.
//
//  Handlers are expected to respond by at least returning an ADUI_REPLY,
//  where kAdUiReply_Nothing indicates the message was ignored, kAdUiReply_Ok
//  is a general-purpose acknowledgement that the notification was handled.

typedef enum {
    // Nothing: never sent, ignore it, it's a rogue notification.
    kAdUiNotify_Nothing,

    // Generic: provided to support application-specific messaging.
    //  Expects to process generic wParam, lParam and reply, as described above.
    kAdUiNotify_Generic,

    // Application's Main Window:
    //  lParam points to a CWnd pointer that will receive the application's
    // main window.
    kAdUiNotify_AppMainWindow,

    // Application's Resource Instance:
    //  lParam points to an HINSTANCE that will receive the handle of the
    // module containing the application's resources.
    kAdUiNotify_AppResourceInstance,

    // AutoLoad or Reload:
    //  For Reload lParam is an LPCTSTR identifying a resource, for AutoLoad
    //  lParam is 0. Reply Ok if the control is sucessfully initialized (or
    //  re-initialized).
    kAdUiNotify_AutoLoad,
    kAdUiNotify_Reload,

    // GetTipSupport: request for tool-tip support.
    //  A control receives this request to determine what kind of tool tip
    //  should be displayed. If processed, the control responds with an
    //  appropriate ADUI_REPLY code. lParam is a pointer to a CPoint
    //  containing the cursor's current position on the display.
    kAdUiNotify_GetTipSupport,

    // GetTipText: request for tool-tip text.
    //  lParam is a pointer to a CString to receive the text, initially
    //  empty. Reply Ok, optionally setting the text. If the returned
    //  text is empty the message is deemed to be handled and the tool
    //  tip will be suppressed. A dialog usually sends this to a control
    //  and if ignored, attempts to process it itself.
    kAdUiNotify_GetTipText,

    // Get Tip Placement:
    //  lParam is a pointer to a CRect to receive display co-ordinates for
    //  a tool-tip. Set the rectangle and reply Ok to have the control
    //  receive DrawTip.
    kAdUiNotify_GetTipRect,

    // Query if in item rectangle related to Tip:
    //  lParam is a pointer to a CPoint containing the cursor's current
    //  position on the display, usually within a tip window. Return Ok if
    //  the position is still within the visible part of the item related
    //  to the tip. Otherwise, the sender assumes the tip can be removed.
    kAdUiNotify_HitTipRect,

    // Draw Tip:
    //  lParam is a pointer to a CDC. The control should render tip data in
    // the DC.
    kAdUiNotify_DrawTip,

    // Draw Tip Text:
    //  lParam is a pointer to a CAdUiDrawTipText. The control should set up
    // the DC passed in the object and possibly render the text. Returning
    // Ok indicates the request was fully handled, otherwise the caller
    // (usually a tip window) will draw the text.
    kAdUiNotify_DrawTipText,

    // Update Tip:
    //  A control may send this to its container when the pointer moves over
    // the control. The container may respond by sending GetTipSupport or by
    // executing its normal tool-tip processing. lParam should be a pointer
    // to the control's CWnd.
    kAdUiNotify_UpdateTip,

    // Hide or Show window:
    //  Sent to a dialog to hide or restore the window and it's parents.
    kAdUiNotify_HideWindow,
    kAdUiNotify_ShowWindow,

    // Restore focus:
    //  wParam LOWORD is a control ID. "Smart" controls often validate their
    //  contents on WM_KILLFOCUS. If not valid the control may want to keep
    //  focus. Problem is that WM_KILLFOCUS is usually sent after focus has
    //  been scheduled for some other window. A control may post this to its
    //  container which should respond by setting focus back to the control
    //  (assuming the container is still active).
    kAdUiNotify_RestoreFocus,

    // Content changed:
    //  A control send this notification to its container when the control's
    // content has changed. The container is free to handle this as it sees
    // fit. The reply is usually ignored.
    kAdUiNotify_Change,

    // NotValid content:
    //  A control send this notification to its container upon determining
    // that it contains non-valid data. The container is free to handle this
    // as it sees fit, possibly by disabling other controls (ex. OK button).
    // The reply is ignored.
    kAdUiNotify_NotValid,

    // Valid content:
    //  A control send this notification to its container upon determining
    // that it contains valid data. The container is free to handle this as
    // it sees fit, possibly by enabling other controls. The reply is ignored.
    kAdUiNotify_Valid,

    // Validate: request to validate content.
    //  A control that receives this notification should determine if it
    // contains valid data. If so it replies Valid, otherwise NotValid.
    // A container that processes this notification will usually inspect
    // each control. If any replies NotValid the container should reply
    // NotValid, and valid otherwise. Controls that handle this message do
    // not need to notify Valid/NotValid during processing (the reply code
    // is sufficient).
    kAdUiNotify_Validate,

    // Command state:
    //  LParam is a ADUI_COMMAND_STATE code. This notification is passed to
    // a dialog and it's parents to inform about the state of a command in
    // progress in the drawing editor.
    kAdUiNotify_CommandState,

    // Modal state:
    // LParam is a ADUI_MODAL_STATE code. This notification is passed to 
    // a dialog and it's parents to inform about the state of the dialog
    // whether it is starting or ending.
    kAdUiNotify_ModalState,
} ADUI_NOTIFY;

typedef enum {
    // Nothing: implies notification wasn't processed.
    kAdUiReply_Nothing,

    // Ok: implies notification has been handled.
    kAdUiReply_Ok,

    // NotValid:
    //  Recipient of a Validate request replies that (some) content is
    // not valid.
    kAdUiReply_NotValid,

    // Valid:
    //  Recipient of a Validate request replies that all content is either
    // valid or in an indeterminate state (assumed to be valid). In other
    // words, there is no content that is definitely "not valid" (yeech).
    kAdUiReply_Valid,

    // TextTip:
    //  Recipient of a GetTipSupport request replies that a standard text-tip
    // should be displayed. The sender will issue a GetTipRect to position a
    // text tip and then send GetTipText to obtain the tip text. DrawTipText
    // will be sent to prepare a DC and optionally draw the tip text.
    kAdUiReply_TextTip,

    // ToolTip:
    //  Recipient of a GetTipSupport request replies that a standard tool-tip
    // should be displayed. The sender will issue a GetTipText request to
    // obtain the tip text.
    kAdUiReply_ToolTip,

    // DrawTip:
    //  Recipient of a GetTipSupport request replies that an owner-drawn tip
    // should be displayed. The sender will issue a GetTipRect to position a
    // text tip and then send DrawTip to render the tip.
    kAdUiReply_DrawTip,

} ADUI_REPLY;

typedef enum {
    // Cancelled: notes that a command in the drawing editor was cancelled.
    kAdUiCommand_Cancelled = -1,

    // Completed: notes that a command in the drawing editor finished OK.
    //  This also represents a default state (i.e. when no commands have been
    // issued, aka kAdUiCommand_None).
    kAdUiCommand_Completed,

    // Begun: notes that a command in the drawing editor has started.
    kAdUiCommand_Begun,

} ADUI_COMMAND_STATE;

typedef enum {
    // Begun: notifies that modal dialog is started.
    kAdUiModal_Begun = 1,

    // Ended: notifies that modal dialog is ended.
    kAdUiModal_Ended,
} ADUI_MODAL_STATE;

/////////////////////////////////////////////////////////////////////////////
// Draw Tip Text packet

class ADUI_PORT CAdUiDrawTipText {
public:
                CAdUiDrawTipText (CDC& dc, CRect& rect, CString& text);

public:
        CDC&    m_dc;
        CRect&  m_rect;
        CString& m_text;
};

/////////////////////////////////////////////////////////////////////////////

const UINT ADUI_PORT AdUiMessage ();

ADUI_NOTIFY ADUI_PORT AdUiNotification (WPARAM wp);

#if !defined(_WIN64) && !defined (_AC64)
ADUI_REPLY ADUI_PORT AdUiNotify (CWnd& w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
ADUI_REPLY ADUI_PORT AdUiNotify (CWnd* w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
#else
ADUI_REPLY ADUI_PORT AdUiNotify (CWnd& w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
ADUI_REPLY ADUI_PORT AdUiNotify (CWnd* w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
#endif

UINT ADUI_PORT AdUiNotifyId (WPARAM wp);

#if !defined(_WIN64) && !defined (_AC64)
BOOL ADUI_PORT AdUiPostNotify (CWnd& w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
BOOL ADUI_PORT AdUiPostNotify (CWnd* w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
#else
BOOL ADUI_PORT AdUiPostNotify (CWnd& w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
BOOL ADUI_PORT AdUiPostNotify (CWnd* w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
#endif

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#pragma pack (pop)
#endif

//////////////////////////////////////////////////////////////////////////////
