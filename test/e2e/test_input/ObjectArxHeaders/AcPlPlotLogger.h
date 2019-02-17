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
//  DESCRIPTION:  Interface for Plot Logging service.
//

#ifndef ACPLPLOTLOGGER_H
#define ACPLPLOTLOGGER_H

class ADESK_NO_VTABLE AcPlPlotLogger
{
public:

    AcPlPlotLogger(){};
    virtual ~AcPlPlotLogger(){};

    // informs the logging service that a job has started
    virtual Acad::ErrorStatus startJob(void) = 0;

    // informs the logging service that a sheet within a job has started
    virtual Acad::ErrorStatus startSheet(void) = 0;

    // log a terminal error
    virtual Acad::ErrorStatus logTerminalError(const ACHAR *pErrorString) = 0;

    // log an Abort, Retry, Ignore error
    virtual Acad::ErrorStatus logARIError(const ACHAR *pErrorString) = 0;

    // log a severe error
    virtual Acad::ErrorStatus logSevereError(const ACHAR *pErrorString) = 0;

    // log an error
    virtual Acad::ErrorStatus logError(const ACHAR *pErrorString) = 0;

    // log a warning
    virtual Acad::ErrorStatus logWarning(const ACHAR *pWarningString) = 0;


    // log a message
    virtual Acad::ErrorStatus logMessage(const ACHAR *pMessageString) = 0;

    // log an informational message
    virtual Acad::ErrorStatus logInformation(const ACHAR *pMessageString) = 0;

    // informs the logging service that a sheet within a job has ended
    virtual Acad::ErrorStatus endSheet(void) = 0;

    // returns whether an error was logged during the sheet
    virtual bool errorHasHappenedInSheet(void) const = 0;

    // returns whether a warning was logged during the sheet
    virtual bool warningHasHappenedInSheet(void) const = 0;

    // informs the logging service that a job has ended
    virtual Acad::ErrorStatus endJob(void) = 0;

    // returns whether an error was logged during the job
    virtual bool errorHasHappenedInJob(void) const = 0;

    // returns whether a warning was logged during the job
    virtual bool warningHasHappenedInJob(void) const = 0;
};

#endif // ACPLPLOTLOGGER_H
