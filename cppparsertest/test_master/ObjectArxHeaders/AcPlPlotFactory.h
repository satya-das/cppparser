//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACPLPLOTFACTORY_H
#  define _ACPLPLOTFACTORY_H
//
//  AcPlPlotFactory   - makes plot engines
//
#  include "AcPl.h"
class AcPlPlotEngine;
class AcPlPlotFactory
{
public:
  enum PreviewEngineFlags
  {
    kShowPlot = 0x0001,
    kShowNextSheet = 0x0002,
    kShowPreviousSheet = 0x0004
  };
  ACPL_PORT static Acad::ErrorStatus createPublishEngine(AcPlPlotEngine * &pEngine);
  ACPL_PORT static Acad::ErrorStatus createPreviewEngine(AcPlPlotEngine*& pPreview, long nPreviewFlags = kShowPlot);
};
// Possible plotting system states
enum ProcessPlotState
{
  kNotPlotting = 0,
  kForegroundPlotting,
  kBackgroundPlotting,
                            // this process is the foreground process.
};
// Method for determining current state of the plotting subsystem
ACPL_PORT ProcessPlotState ADESK_STDCALL acplProcessPlotState();
#endif
