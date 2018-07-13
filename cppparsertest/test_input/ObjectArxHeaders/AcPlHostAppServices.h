//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//  DESCRIPTION:  Interface definition for Host Plot Services.
//
#ifndef ACPLHOSTAPPSERVICES_H
#define ACPLHOSTAPPSERVICES_H

class AcPlPlotLogger;
class AcadPlotInternalServices;



class ADESK_NO_VTABLE AcPlHostAppServices
{
public:
    enum PlotStatus {
        kSheetIdxAndName        = -5,
        kDisableCancelSheet     = -4,
        kDwfFilePlotted         = -3,
        kPlottingMsg            = -2,
        kNoPlotYet              = -1,
        kPlotStart              = 0,
        kViewPlotLog            = 1,
        kPlotSuccessful         = 2,
        kPlotHadErrors          = 3,
        kPlotHadSystemError     = 4,
        kViewPlottedFile        = 5,
        kViewFileWhenSuccessful = 6
    };

    virtual AcPlPlotLogger * getPlotLogger(void) = 0;
    virtual const AcadPlotInternalServices* acadInternalServices() = 0;

    virtual void updatePlotJobStatus(enum AcPlHostAppServices::PlotStatus nStatus, const ACHAR *szPlotMsg) = 0;
};

ACPL_PORT Acad::ErrorStatus AcPlSetHostAppServices(AcPlHostAppServices *pHostServices);
ACPL_PORT AcPlHostAppServices *AcPlGetHostAppServices();

#endif // ACPLHOSTAPPSERVICES_H
