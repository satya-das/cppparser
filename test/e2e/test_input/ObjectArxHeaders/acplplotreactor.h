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
//  DESCRIPTION:  Header for Document and Document Manager Classes.
//

#ifndef ACPLPLOTREACTOR_H
#define ACPLPLOTREACTOR_H

#include "AdAChar.h"
#include "AcPl.h"
#include "AcPlObject.h"

class AcPlPlotInfo;
class AcPlPlotPageInfo;
class AcPlPlotProgress;

class ACPL_PORT AcPlPlotReactor : public AcRxObject // API
{
public:

    // Plot Type
    enum PlotType {
        kPlot,
        kPreview,
        kBackgroundPackaging,
        kBackgroundPlot
    };

    // Notification for begin of plot
    virtual void beginPlot(AcPlPlotProgress* pPlotProgress, PlotType type);

    // Notification for beginning of an document
    virtual void beginDocument(AcPlPlotInfo& plotInfo,
                                         const ACHAR * pDocname,
                               Adesk::Int32 nCopies = 1,
                               bool bPlotToFile = false,
                               const ACHAR * pFilename = NULL);

    // Notification for begin page
    virtual void beginPage(AcPlPlotPageInfo& pageInfo, AcPlPlotInfo& plotInfo,
                           bool bLastPage);
    
    // Notification for end page
    virtual void endPage(AcPlPlotProgress::SheetCancelStatus status);

    // Notification for end of an document
    virtual void endDocument(AcPlPlotProgress::PlotCancelStatus status);

    // Notification that plot has ended
    virtual void endPlot(AcPlPlotProgress::PlotCancelStatus status);

    // Notification that plot was cancelled
    virtual void plotCancelled();

    // Notification that page was cancelled
    virtual void pageCancelled();

    // Destructor
    virtual ~AcPlPlotReactor();
    
protected:
    AcPlPlotReactor();
};

#endif // ACPLPLOTREACTOR_H
