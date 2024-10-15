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
//  DESCRIPTION: Definitions for the AutoCAD native command definition
//               mechanism.
//

// NOTE: before adding any new command constants here,
// check with the undocumented ACRX_CMD_... constants
// defined in coresrc/command.cpp to make sure that
// there is no overlap.
//
// ARX command bits which are not exported yet, but which could
// be of use in the R13 time frame.  We should look at these in
// R14 to determine if they should be exported. BCH 10/3/95
// The value of ACRX_CMD_NOPAPERSPACE was changed from 0x10 to
// 0x40 by submission S049-JH2 because it conflicted with the
// value of ACRX_CMD_NOMULTIPLE.  JH 1/3/97.
//
#pragma once
#ifndef   _ACCMD_DEFS_H
#define   _ACCMD_DEFS_H

#define ACRX_CMD_MODAL              0x00000000
#define ACRX_CMD_TRANSPARENT        0x00000001
#define ACRX_CMD_USEPICKSET         0x00000002
#define ACRX_CMD_REDRAW	            0x00000004
#define ACRX_CMD_NOPERSPECTIVE      0x00000008 /* NOT allowed in perspective 
                                               views */
#define ACRX_CMD_NOMULTIPLE         0x00000010
#define ACRX_CMD_NOTILEMODE         0x00000020 // NOT allowed with TILEMODE == 1
#define ACRX_CMD_NOPAPERSPACE       0x00000040 // NOT allowed in Paperspace
// #define ACRX_CMD_PLOTONLY           0x00000080 // Obsolete

// It's used to let users know the command will be removed in next release or so.  
// Users should mitigate the change as soon as possible. The command is deprecated
// by un-defining it immediately after registering with the system.
// If users really need to use it, they can still use it by prefixing with "." or re-define it.
// .ETRANSMIT or redefine ETRANSMIT
#define ACRX_CMD_DEPRECATED         ACRX_CMD_UNDEFINED // Deprecate command           

#define ACRX_CMD_NOOEM              0x00000100
#define ACRX_CMD_UNDEFINED          0x00000200
#define ACRX_CMD_INPROGRESS         0x00000400
#define ACRX_CMD_DEFUN              0x00000800
#define ACRX_CMD_LISPASCMD          0x00001000 // For Internal use only
#define ACRX_CMD_PGPINIT            0x00002000 // For Internal use only: PGP initialize
#define ACRX_CMD_NONEWSTACK         0x00010000 // For internal use only
#define ACRX_CMD_NOINTERNALLOCK     0x00020000
#define ACRX_CMD_DOCREADLOCK        0x00080000 // not set = DOCWRITELOCK
#define ACRX_CMD_DOCEXCLUSIVELOCK   0x00100000 // not set = DOCSHAREDLOCK
#define ACRX_CMD_SESSION            0x00200000 /* Run cmd handler in the session
                                                  fiber */
#define ACRX_CMD_INTERRUPTIBLE      0x00400000 // Supports OPM display of command
                                               // properties
#define ACRX_CMD_NOHISTORY          0x00800000 // Command does not become default
#define ACRX_CMD_NO_UNDO_MARKER     0x01000000 // No Undo or Repeat presence.
#define ACRX_CMD_NOBEDIT            0x02000000 // blocked during a bedit session
#define ACRX_CMD_NOACTIONRECORDING  0x04000000 // Disallow Action Recording
#define ACRX_CMD_ACTIONMACRO        0x08000000 // Action Macro command
#define ACRX_CMD_RELAXASSOC         0x10000000 /* Allow relaxed network evaluation
                                                  during drag operation */
#define ACRX_CMD_CORE               0x20000000 // For internal use only 
#define ACRX_CMD_NOINFERCONSTRAINT  0x40000000 // Disallow Inferring constraints 
#define ACRX_CMD_TEMPSHOWDYNDIM     0x80000000 // Temporarily show dynamic dimensions for selected entities during this command


#define ACRX_MAX_CMDNAME_LEN  	64

#endif