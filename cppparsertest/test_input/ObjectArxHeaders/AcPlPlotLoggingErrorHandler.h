//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ACPLPLOTLOGGINGERRORHANDLER_H
#define ACPLPLOTLOGGINGERRORHANDLER_H

class AcPlPlotLogger;
class AcPlSystenInternals;

class AcPlPlotLoggingErrorHandler : public AcPlPlotErrorHandler
{
public:
    ACPL_PORT AcPlPlotLoggingErrorHandler();
    ACPL_PORT AcPlPlotLoggingErrorHandler(AcPlPlotLogger *);
    ACPL_PORT virtual ~AcPlPlotLoggingErrorHandler();

    ACPL_DECLARE_MEMBERS(AcPlPlotLoggingErrorHandler);

public:

    ACPL_PORT virtual void infoMessage(const ACHAR *pMessage);

    ACPL_PORT virtual int messageBox(const ACHAR *pText, 
                                     const ACHAR *pCaption,
                                     unsigned int uType, 
                                     int defaultReturn);

    //info error handler.
    ACPL_PORT virtual void info(ULONG_PTR category, 
                                const unsigned int specific,
                                const ACHAR *pLocation, 
                                const ACHAR *pContextData,
                                const ACHAR *pRevision);

    //warning error handler.
    ACPL_PORT virtual ErrorResult warning(ULONG_PTR category, 
                                          const unsigned int specific,
                                          const ACHAR *pLocation,
                                          const ACHAR *pContextData, 
                                          const ACHAR *pRevision);

    //Severe handler
    ACPL_PORT virtual void severeError(ULONG_PTR category, 
                                       const unsigned int specific, 
                                       const ACHAR *pLocation, 
                                       const ACHAR *pContextData, 
                                       const ACHAR *pRevision);

    //Error handler
    ACPL_PORT virtual ErrorResult error(ULONG_PTR category,
                                        const unsigned int specific, 
                                        const ACHAR *pLocation, 
                                        const ACHAR *pContextData, 
                                        const ACHAR *pRevision);

    //Abort/Retry/Ignore handler
    ACPL_PORT virtual ErrorResult ariError(ULONG_PTR category,
                                           const unsigned int specific,
                                           const ACHAR *pLocation,
                                           const ACHAR *pContextData,
                                           const ACHAR *pRevision);

    // Terminal error handler
    ACPL_PORT virtual void terminalError(ULONG_PTR category,
                                         const unsigned int specific,
                                         const ACHAR *pLocation,
                                         const ACHAR *pContextData,
                                         const ACHAR *pRevision);

    // log a message to the log file
    ACPL_PORT virtual void logMessage(const ACHAR *pTitle, const ACHAR *pMsg);

};

#endif // ACPLPLOTLOGGINGERRORHANDLER_H
