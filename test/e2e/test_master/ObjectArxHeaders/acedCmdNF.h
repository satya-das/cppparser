//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "acedinpt.h"
#include "acdocman.h"
#ifdef __cplusplus
extern "C" {
#endif
#pragma  pack (push, 8)
  ACAD_PORT bool acedFiberWorld();
  int acedCommandS(int rtype, ...);
  class AcApDocument;
  int acedCmdS(const resbuf* rb, bool forFutureUse = false, AcApDocument* pForFutureUse = NULL);
  typedef int (*AcEdCoroutineCallback) (void* pData);
  ACAD_PORT int acedCommandC(AcEdCoroutineCallback pCallback, void* pReturnFcnParms, int rtype, ...);
  ACAD_PORT int acedCmdC(AcEdCoroutineCallback pCallback, void* pReturnFcnParms, const struct resbuf* rb);
  ACAD_PORT bool acedPendingCmdCTokens();
  ACAD_PORT bool acedResumingInvocation();
  ACAD_PORT void acedCallBackOnCancel();
  ACAD_PORT bool acedCmdCWasCancelled();
#pragma  pack (pop)
#ifdef __cplusplus
  }
#endif
ACAD_PORT bool acedPendingFiberlessDocSwitch(AcApDocument** pNextActiveDocument = NULL);
