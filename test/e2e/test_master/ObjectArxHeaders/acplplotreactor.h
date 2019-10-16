//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACPLPLOTREACTOR_H
#  define ACPLPLOTREACTOR_H
#  include "AdAChar.h"
#  include "AcPl.h"
#  include "AcPlObject.h"
class AcPlPlotInfo;
class AcPlPlotPageInfo;
class AcPlPlotProgress;
class ACPL_PORT AcPlPlotReactor : public AcRxObject
{
public:
  enum PlotType
  {
    kPlot,
    kPreview,
    kBackgroundPackaging,
    kBackgroundPlot
  };
  virtual void beginPlot(AcPlPlotProgress* pPlotProgress, PlotType type);
  virtual void beginDocument(AcPlPlotInfo& plotInfo, const ACHAR* pDocname, Adesk::Int32 nCopies = 1, bool bPlotToFile = false, const ACHAR* pFilename = NULL);
  virtual void beginPage(AcPlPlotPageInfo& pageInfo, AcPlPlotInfo& plotInfo, bool bLastPage);
  virtual void endPage(AcPlPlotProgress::SheetCancelStatus status);
  virtual void endDocument(AcPlPlotProgress::PlotCancelStatus status);
  virtual void endPlot(AcPlPlotProgress::PlotCancelStatus status);
  virtual void plotCancelled();
  virtual void pageCancelled();
  virtual ~AcPlPlotReactor();
protected:
  AcPlPlotReactor();
};
#endif
