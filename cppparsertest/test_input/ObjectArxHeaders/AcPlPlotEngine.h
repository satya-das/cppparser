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
//  AcPlPlotPageInfo      - interface for prescan info
//  AcPlPreviewEngine     - interface with plotting pipeline for previewing
//  AcPlPlotEngine        - interface with plotting pipeline for plotting
//

#ifndef   _ACPLPLOTENGINE_H
#define   _ACPLPLOTENGINE_H

#include "AdAChar.h"
#include "AcPl.h"
#include "AcPlObject.h"

class AcViewport;
class PlotEnvironment;
class AcPlPlotProgress;
class AcPlPlotInfo;
class AcDbPlotSettings;
class AcPlPlotConfig;

// Status values for ACPL_PREVIEWENDPLOT
enum PreviewStatus {
    kNormal = 0,
    kPlot,
    kCancel,
    kNext,
    kPrevious
};

// Struct ACPL_PREVIEWENDPLOT, in/out parameter modified by AcPlPlotEngine::endPlot()
// if the engine was created with AcPlPlotFactory::createPreviewEngine.
struct ACPL_PREVIEWENDPLOT {
    PreviewStatus nStatus;
};

class AcPlPlotPageInfo : public AcPlObject
{
    ACPL_DECLARE_MEMBERS(AcPlPlotPageInfo);

public:
    ACPL_PORT AcPlPlotPageInfo();
    ACPL_PORT virtual ~AcPlPlotPageInfo();

    ACPL_PORT Adesk::Int32 entityCount() const;
    ACPL_PORT Adesk::Int32 rasterCount() const;
    ACPL_PORT Adesk::Int32 oleObjectCount() const;
    ACPL_PORT Adesk::Int32 gradientCount() const;
    ACPL_PORT Adesk::Int32 shadedViewportType() const;
};

class ADESK_NO_VTABLE AcPlPlotEngine {
public:
    virtual Acad::ErrorStatus beginPlot(AcPlPlotProgress* pPlotProgress, void* pParams = NULL);
    virtual Acad::ErrorStatus endPlot(void* pParams = NULL);
    
    // This plotInfo must not be deleted until endDocument().
    virtual Acad::ErrorStatus beginDocument(AcPlPlotInfo& plotInfo, 
                                            const ACHAR * pDocname,
                                            void *pParams = NULL,
                                            Adesk::Int32 nCopies = 1, 
                                            bool bPlotToFile = false, 
                                            const ACHAR * pFileName = NULL);
    virtual Acad::ErrorStatus endDocument(void* pParams = NULL);
    
    // This plotInfo may be the same as for beginDocument().
    virtual Acad::ErrorStatus beginPage(AcPlPlotPageInfo& pageInfo, 
                                        AcPlPlotInfo& plotInfo, 
                                        bool bLastPage, 
                                        void* pParams = NULL);
    virtual Acad::ErrorStatus endPage(void* pParams = NULL);
    
    virtual Acad::ErrorStatus beginGenerateGraphics(void* pParams = NULL);
    virtual Acad::ErrorStatus beginGenerateGraphics(AcViewport*& pViewport, void* pParams = NULL);
    virtual Acad::ErrorStatus endGenerateGraphics(void* pParams = NULL);
    
    virtual void destroy();
    virtual bool isBackgroundPackaging() const;
};


#endif // _ACPLPLOTENGINE_H
