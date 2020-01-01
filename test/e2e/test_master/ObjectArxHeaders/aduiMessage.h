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
#  define _aduiMessage_h
#  pragma  pack (push, 8)
#  pragma  once
/////////////////////////////////////////////////////////////////////////////
typedef enum
{
  kAdUiNotify_Nothing,
  kAdUiNotify_Generic,
  kAdUiNotify_AppMainWindow,
  kAdUiNotify_AppResourceInstance,
  kAdUiNotify_AutoLoad,
  kAdUiNotify_Reload,
  kAdUiNotify_GetTipSupport,
  kAdUiNotify_GetTipText,
  kAdUiNotify_GetTipRect,
  kAdUiNotify_HitTipRect,
  kAdUiNotify_DrawTip,
  kAdUiNotify_DrawTipText,
  kAdUiNotify_UpdateTip,
  kAdUiNotify_HideWindow,
  kAdUiNotify_ShowWindow,
  kAdUiNotify_RestoreFocus,
  kAdUiNotify_Change,
  kAdUiNotify_NotValid,
  kAdUiNotify_Valid,
  kAdUiNotify_Validate,
  kAdUiNotify_CommandState,
  kAdUiNotify_ModalState
} ADUI_NOTIFY;
typedef enum
{
  kAdUiReply_Nothing,
  kAdUiReply_Ok,
  kAdUiReply_NotValid,
  kAdUiReply_Valid,
  kAdUiReply_TextTip,
  kAdUiReply_ToolTip,
  kAdUiReply_DrawTip
} ADUI_REPLY;
typedef enum
{
  kAdUiCommand_Cancelled = -1,
  kAdUiCommand_Completed,
  kAdUiCommand_Begun
} ADUI_COMMAND_STATE;
typedef enum
{
  kAdUiModal_Begun = 1,
  kAdUiModal_Ended
} ADUI_MODAL_STATE;
/////////////////////////////////////////////////////////////////////////////
class ADUI_PORT CAdUiDrawTipText
{
public:
  CAdUiDrawTipText(CDC& dc, CRect& rect, CString& text);
  CDC& m_dc;
  CRect& m_rect;
  CString& m_text;
};
/////////////////////////////////////////////////////////////////////////////
const UINT ADUI_PORT AdUiMessage();
ADUI_NOTIFY ADUI_PORT AdUiNotification(WPARAM wp);
#  if  !defined(_WIN64) && !defined (_AC64)
ADUI_REPLY ADUI_PORT AdUiNotify(CWnd& w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
ADUI_REPLY ADUI_PORT AdUiNotify(CWnd* w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
#  else 
ADUI_REPLY ADUI_PORT AdUiNotify(CWnd& w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
ADUI_REPLY ADUI_PORT AdUiNotify(CWnd* w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
#  endif
UINT ADUI_PORT AdUiNotifyId(WPARAM wp);
#  if  !defined(_WIN64) && !defined (_AC64)
BOOL ADUI_PORT AdUiPostNotify(CWnd& w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
BOOL ADUI_PORT AdUiPostNotify(CWnd* w, UINT id, ADUI_NOTIFY n, DWORD_PTR lParam);
#  else 
BOOL ADUI_PORT AdUiPostNotify(CWnd& w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
BOOL ADUI_PORT AdUiPostNotify(CWnd* w, UINT id, ADUI_NOTIFY n, LPARAM lParam);
#  endif
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
#  pragma  pack (pop)
#endif
//////////////////////////////////////////////////////////////////////////////
