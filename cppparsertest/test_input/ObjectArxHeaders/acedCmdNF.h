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

#include "acedinpt.h"
#include "acdocman.h"

// acedCmdNF.h:
// Fiberless variants of acedCommand and acedCmd
// plus supporting functions

#ifdef __cplusplus
    extern "C" {
#endif
#pragma pack (push, 8)

// acedFiberWorld:
// Returns
// true if $FIBERWORLD is 1, and
// false if $FIBERWORLD is 0
// On both Windows-based and Mac-based AutoCAD, by default returns "false"
//
ACAD_PORT bool acedFiberWorld();

//
// acedCommandS:  syntax-compatible replacement of acedCommand,
//                use for "full commands", not partial ones.
//                This command essentially begins with its own
//                private command line processor, initialized at
//                the "Command:" prompt.   The commands are executed
//                in the same manner as with acedCommand, except that
//                when the supplied input has all been executed,
//                the private command line processor is deleted
//                and the previous command line processor is unchanged
//                from when the call is made.   modality and
//                transparent "builtin" commands may not be nested.
//                
//
int             acedCommandS(int rtype, ...);

// acedCmdS
//
// Does the same thing with the same restructions as acedCommandS,
// with a resbuf chain rather than a veriable arguments list.
// Two more supplied parameters are intended for future use.
//
class AcApDocument;

int             acedCmdS(const resbuf*       rb,
               bool          forFutureUse  = false,
               AcApDocument* pForFutureUse = NULL);

// acedCommandC, acedCmdC:
// "coroutine" relationship with calling command processor.
// Queues up the resbuf chain for feeding to the
// calling command processor and stores the "returning"
// callback function pointer and data pointer.
// In the text here, they will be collectively
// referred to as "acedCmdC", which in fact is
// the common implementation.  "acedCmd" will represent
// the corresponding legacy command functions.
//
// After making call, caller must return from its 
// command (or defun/regfunc) entry
// point to allow the command processor to process the
// pending command input.  Once done with that input,
// AutoCAD will call pReturnFcn, with pReturnFcnParams
// passed in.
//
// There are some common rules for the use of both acedCmdC
// and acedCmd within a recognized application callback
// (specifically, these functions are only operative within
// specific AutoCAD contexts:
// - a command, registered in ARX via AcEdCommandStack::addCommand
// - a LISP invocation of a function registered via acedDefun
//   (and/or acedRegfunc).
// - a coroutine callback passed in from acedCmdC
// - Evaluation of LISP (command) statement evaluation.
// - builtin commands (plus AcEdCommand commands with the
//   ACRX_CMD_NONEWSTACK flag set).
// - Session Fiber Commands (or Application Execution Context)
// - Transparent commands, executed at an input prompt of another
//   command in progress (Regardless of builtin or ARX-registered)
// 
// 1. acedCmdC may be invoked from non-LISP calling contexts
//    regardless of the $FIBERWORLD
//    setting, (the exclusion from transparent commands remains).
//
//    From LISP contexts where acedInvoke() is active (i.e. acedDefun'ed
//    functions being called from LISP),
//    acedCmdC may only be invoked when $FIBERWORLD is 0.
//
//    acedCmd, in comparison, cannot be invoked unless $FIBERWORLD
//    is 1, if done, it will return an error status. It also
//    cannot be invoked from builtin commands, nor transparent commands.
//
//    Therefore, function logic running in an acedDefun/acedInvoke
//    context should test acedFiberWorld to determine whether
//    to run acedCmd or acedCmdC is permissible. Notice that
//    acedCmdS is safe to run in this context regardless of the
//    $FIBERWORLD setting.
//
// 2. While it is not a destination in one's migration,
//    Command and defun'ed function logic (but not coroutine callbacks,
//    described next) may invoke acedCmd any number of times,
//    but after making a call to acedCmdC, the function must
//    return without making a call to either acedCmdC nor acedCmd.
//    If such a call is made, the resbuf chain previously supplied
//    by acedCmdC will be replaced with the subsequent chain.
//    acedCmd will return an error status and take no action.
// 3. Coroutine continuation functions may call acedCmdC,
//    but use of acedCmd will return an error status
//    and no action.
// 2. acedCmdS may be used in any of these contexts (and many more)
//    and at any time within these contexts.
//    It is unobvious to invoke acedCmdS
//    after calling acedCmdC and before returning to have its
//    input procssed, since the acedCmdS will be executed
//    synchronously, but it would work.
// 3. Repeated calls to acedCmdC without returning for processing
//    in between will simply erase the earlier acedCmdC contents.
//    In other words, only one call will count before returning,
//    so don't bother making multiple calls.
// 4. Commands and LISP expressions which use different mixes of
//    acedCmd, acedCmdC and acedCmdS may invoke each other
//    without regard to the makeup of the other command/expression.
//    Command processor modality restrictions will still apply
//    such as no nesting of nontransparent commands nor transparent
//    commands.
//
// WARNING: support of these functions in logic operated through
//          invocation of functions registered via acedDefun
//          is incomplete in ACAD 2011.
//

typedef int (*AcEdCoroutineCallback)(void* pData);

ACAD_PORT int acedCommandC(AcEdCoroutineCallback pCallback,
                           void* pReturnFcnParms,
                           int rtype, ...);
ACAD_PORT int acedCmdC(AcEdCoroutineCallback pCallback,
                       void* pReturnFcnParms,
                       const struct resbuf *rb);

// acedPendingCmdCTokens
//
// This predicate should be checked immediately after calling
// acedInvoke from a function registered via acedDefun that
// has itself been invoked from LISP.  If it returns true, then
// the calling
// function should itself also immediately return RSRSLT, without
// necessarily establishing a return value.   The tokens will be
// processed, and either the calling function will be called back
// (see acedResumeInvocation below for determining if this is the
// case), or cancel will terminate the rest of the operation.
// Note that acedFiberWorld() must return true for acedCmdC
// to succeed in an acedInvoke context, and for this function to
// return true.
//
// Returns
// true  after a function has invoked acedCmdC
//       from a LISP context, and LISP has yet to return.
//       See preceding for how to proceed when true is returned.
// false when there are no pending comand tokens, in which
//       case the caller should proceed normally.
//      
ACAD_PORT bool acedPendingCmdCTokens();


// acedResumingInvocation
//
// Returns
// true  when in a function registered via acedDefun and/or acedRegFunc
//       and invoked from LISP that is being called back after a
//       previous invocation called acedCommandC or acedCmdC, (see
//       acedPendingCmdCTokens()), either directly or via a nested
//       invocation.
//       In this case, the function is responsible for
//       determining how to resume.   If, during its resumption,
//       acedCommandC or acedCmdC is invoked again, then after
//       returning to process those tokens, the function will be
//       "resumed" again, until no call to acedCommandC or acedCmdC
//       is made.  Because acedCommandC/acedCmdC can be invoked
//       regardless of the $FIBERWORLD state, this function can
//       also return true, in any case.
// false in all other conditions, including whenever acedFiberWorld()
//       is true.
//
ACAD_PORT bool acedResumingInvocation();

// acedCallBackOnCancel
//
// If you have made a call to acedCommandC or acedCmdC and wish to
// have your registered callback called when a CANCEL or other error occurs,
// call this function before returning.   If you don't call this function
// and a CANCEL or other error occurs, your callback will not be
// called, instead AutoCAD will directly cancel the command state.
//
ACAD_PORT void acedCallBackOnCancel();

// acedCmdCWasCancelled
//
// When your registered callback is called in response to a CANCEL or error,
// this function will return true, else it will return false.
//
ACAD_PORT bool acedCmdCWasCancelled();

#pragma pack (pop)
#ifdef __cplusplus
    }
#endif  /* __cplusplus */

// acedPendingFiberlessDocSwitch:
//
// pNextActiveDocument: Optional parameter to receive the next active document
// if the function returns true. Pass in NULL if the value is not needed.
// 
// Returns
// True if:
// - $FIBERWORLD is 0 and
// - a cancel is in progress and
// - a document switch has been requested but
//   hasn't occurred yet,
// 
// else false is returned.
//
// If a cancel happens at an input prompt and you
// want your command to continue in the new document,
// use something like AcApDocumentManager::sendStringToExecute
// to the new document to perpetuate control.
//
ACAD_PORT bool acedPendingFiberlessDocSwitch(AcApDocument** pNextActiveDocument = NULL);
