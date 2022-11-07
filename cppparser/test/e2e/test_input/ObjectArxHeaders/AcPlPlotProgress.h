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
//  DESCRIPTION:  Header for AcPlPlotProgress.
//

#ifndef ACPLPLOTPROGRESS_H
#define ACPLPLOTPROGRESS_H

#include "AdAChar.h"
#include "AcPl.h"

class AcPlPlotProgressDialog;

class ADESK_NO_VTABLE AcPlPlotProgress
{
public:

    enum SheetCancelStatus {
        kSheetContinue,
        kSheetCanceledByCancelButton,
        kSheetCanceledByCancelAllButton,
        kSheetCanceledByCaller,
        kSheetCancelStatusCount
    };

    enum PlotCancelStatus {
        kPlotContinue,
        kPlotCanceledByCaller,
        kPlotCanceledByCancelAllButton,
        kPlotCancelStatusCount
    };

    virtual bool isPlotCancelled() const = 0;
    virtual void setPlotCancelStatus(PlotCancelStatus Cancel) = 0;
    virtual PlotCancelStatus plotCancelStatus() const = 0;

    virtual void setPlotProgressRange(int nLower, int nUpper) = 0;
    virtual void getPlotProgressRange(int &nLower, int &nUpper) const = 0;

    virtual void setPlotProgressPos(int nPos) = 0;
    virtual int  plotProgressPos() const = 0;

    virtual bool isSheetCancelled() const = 0;
    virtual void setSheetCancelStatus(SheetCancelStatus Cancel) = 0;
    virtual SheetCancelStatus sheetCancelStatus() const = 0;

    virtual void setSheetProgressRange(int nLower, int nUpper) = 0;
    virtual void getSheetProgressRange(int &nLower, int &nUpper) const = 0;

    virtual void setSheetProgressPos(int nPos) = 0;
    virtual int  sheetProgressPos() const = 0;

    virtual bool setIsVisible(bool bVisible) = 0;
    virtual bool isVisible() const = 0;

    virtual bool setStatusMsgString(const ACHAR *pMsg) = 0;
    virtual bool getStatusMsgString(ACHAR *& pMsg) const = 0;

    virtual void heartbeat(void) = 0;
};

typedef void (*ACPLPLTPRGHELPPROC)(AcPlPlotProgressDialog *pAcPlPlotProgressDialog);

class AcPlPlotProgressDialog : public AcPlPlotProgress 
{
public:
    enum PlotMSGIndex {
        kDialogTitle,
        kSheetName,
        kSheetNameToolTip,
        kStatus,
        kSheetProgressCaption,
        kSheetSetProgressCaption,
        kMsgCancelling,
        kMsgCancellingCurrent,
        kCancelSheetBtnMsg,
        kCancelJobBtnMsg,
        kMsgCount
    };

    virtual bool onBeginPlot() = 0;
    virtual bool onEndPlot() = 0;

    virtual bool onBeginSheet() = 0;
    virtual bool onEndSheet() = 0;

    virtual bool setPlotMsgString(PlotMSGIndex index, const ACHAR *pMsg) = 0;
    virtual bool getPlotMsgString(PlotMSGIndex index, ACHAR *& pMsg) const = 0;
    
    virtual bool isSingleSheetPlot() const = 0;

    virtual void destroy() = 0;
};

ACPL_PORT AcPlPlotProgressDialog* ADESK_STDCALL
acplCreatePlotProgressDialog( HWND hParent, 
                          bool bPreview = false, 
                          int nSheets = 1,
                          ACPLPLTPRGHELPPROC hlpProc = NULL,
                          bool bShowCancelSheetButton = true);

#endif // ACPLPLOTPROGRESS_H
