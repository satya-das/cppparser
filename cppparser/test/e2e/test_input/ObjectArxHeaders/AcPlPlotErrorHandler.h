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
//  DESCRIPTION:  Interface for Plot Error Handler.
//
#ifndef ACPLPLOTERRORHANDLER_H
#define ACPLPLOTERRORHANDLER_H

#include "AcPlObject.h"

class AcPlSystemInternals;

class AcPlPlotErrorHandler : public AcPlObject
{
public:
    enum ErrorResult {
        kAbort,
        kRetry,
        kIgnore
    };
    enum Handler {
        kInfo,
        kWarning,
        kError,
        kARI,
        kSevere,
        kTerminal,
        kNone 
    };

    ACPL_PORT AcPlPlotErrorHandler();
    ACPL_PORT ~AcPlPlotErrorHandler();

    ACPL_DECLARE_MEMBERS(AcPlPlotErrorHandler);

public:
    // Start of functions which may delegate to the application handler.
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

    // End of functions which may delegate to the application handler


    // true if this error handler takes responsibility for a class of errors
    ACPL_PORT virtual bool takeResponsibility(Handler kind) ;

    // set the log file name
    ACPL_PORT virtual bool setLogHandle(const ACHAR *pFilePathName) ;

    // set quiet mode
    ACPL_PORT virtual void setQuietMode(bool bQuiet);

    // set error logging mode
    ACPL_PORT virtual void setLogMode(bool bLog);

    // get the quiet mode of this error handler
    ACPL_PORT virtual bool quietMode() const;

    // get the logging mode of this error handler
    ACPL_PORT virtual bool logMode() const;

    // OEM strings : product, program, and company

    ACPL_PORT void getProductString(ACHAR*& pProductString) const;
    ACPL_PORT void getProgramString(ACHAR*& pProgramString) const;
    ACPL_PORT void getCompanyString(ACHAR*& pCompanyString) const;

    ACPL_PORT virtual const ACHAR* warningTitle() const;
    ACPL_PORT virtual const ACHAR* severeTitle() const;
    ACPL_PORT virtual const ACHAR* errorTitle() const;
    ACPL_PORT virtual const ACHAR* ariTitle() const;
    ACPL_PORT virtual const ACHAR* terminalTitle() const;
    ACPL_PORT virtual const ACHAR* infoTitle() const;

protected:

    // The following parent functions call the corresponding function on the 
    // link handler.
    // If no link handler exists, their behavior is undefined.
    // These functions exist as a service to potential child classes.

    ACPL_PORT void appInfoMessage(const ACHAR *pMessage);

    ACPL_PORT int appMessageBox(const ACHAR *pText, 
                                const ACHAR *pCaption,
                                unsigned int uType, 
                                int defaultReturn);

    //info error handler.
    ACPL_PORT void appInfo(ULONG_PTR category, 
                           const unsigned int specific,
                           const ACHAR *pLocation, 
                           const ACHAR *pContextData,
                           const ACHAR *pRevision);

    //warning error handler.
    ACPL_PORT ErrorResult appWarning(ULONG_PTR category,
                                     const unsigned int specific,
                                     const ACHAR *pLocation,
                                     const ACHAR *pContextData,
                                     const ACHAR *pRevision);

    //Severe handler
    ACPL_PORT void appSevereError(ULONG_PTR category,
                                  const unsigned int specific,
                                  const ACHAR *pLocation,
                                  const ACHAR *pContextData,
                                  const ACHAR *pRevision);

    //Error handler
    ACPL_PORT ErrorResult appError(ULONG_PTR category,
                                   const unsigned int specific,
                                   const ACHAR *pLocation,
                                   const ACHAR *pContextData,
                                   const ACHAR *pRevision);

    //Abort/Retry/Ignore handler
    ACPL_PORT ErrorResult appARIError(ULONG_PTR category,
                                      const unsigned int specific,
                                      const ACHAR *pLocation,
                                      const ACHAR *pContextData,
                                      const ACHAR *pRevision);

    // Terminal error handler
    ACPL_PORT void appTerminalError(ULONG_PTR category,
                                    const unsigned int specific,
                                    const ACHAR *pLocation,
                                    const ACHAR *pContextData,
                                    const ACHAR *pRevision);

    // log a message to the log file
    ACPL_PORT void appLogMessage(const ACHAR *pTitle, const ACHAR *pMsg);

    ACPL_PORT bool appSetLogHandle(const ACHAR *pFilePathName);
};

#endif // ACPLPLOTERRORHANDLER_H
