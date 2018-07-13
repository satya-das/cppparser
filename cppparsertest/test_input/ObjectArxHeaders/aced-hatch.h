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
//  DESCRIPTION:  Header for Rx application definitions and C
//                access to AutoCAD Editor-specific services.
//
#pragma once
#ifndef   _ACED_HATCH_H
#define   _ACED_HATCH_H

enum AcHatchNotifier {
    kNobody           = 0x00,
    kImpHatch         = 0x01,
    kBoundary         = 0x02,
    kHatchAndBoundary = (kImpHatch | kBoundary),
    kAddScale         = 0x04
};

enum AcHatchEdReact
{
    kStartHatchWatcher = 1,
    kSwapHatchId,
    kUpRootHatchWatcher, 
    kDestroyHatchWatcher,
    kDisableNextStart,
    kRecomputeBoundary
};

#endif
 
