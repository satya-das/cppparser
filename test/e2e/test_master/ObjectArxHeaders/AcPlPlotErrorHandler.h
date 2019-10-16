//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACPLPLOTERRORHANDLER_H
#  define ACPLPLOTERRORHANDLER_H
#  include "AcPlObject.h"
class AcPlSystemInternals;
class AcPlPlotErrorHandler : public AcPlObject
{
public:
  enum ErrorResult
  {
    kAbort,
    kRetry,
    kIgnore
  };
  enum Handler
  {
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
  ACPL_PORT virtual void infoMessage(const ACHAR* pMessage);
  ACPL_PORT virtual int messageBox(const ACHAR* pText, const ACHAR* pCaption, unsigned int uType, int defaultReturn);
  ACPL_PORT virtual void info(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT virtual ErrorResult warning(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT virtual void severeError(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT virtual ErrorResult error(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT virtual ErrorResult ariError(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT virtual void terminalError(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT virtual void logMessage(const ACHAR* pTitle, const ACHAR* pMsg);
  ACPL_PORT virtual bool takeResponsibility(Handler kind);
  ACPL_PORT virtual bool setLogHandle(const ACHAR* pFilePathName);
  ACPL_PORT virtual void setQuietMode(bool bQuiet);
  ACPL_PORT virtual void setLogMode(bool bLog);
  ACPL_PORT virtual bool quietMode() const;
  ACPL_PORT virtual bool logMode() const;
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
  ACPL_PORT void appInfoMessage(const ACHAR* pMessage);
  ACPL_PORT int appMessageBox(const ACHAR* pText, const ACHAR* pCaption, unsigned int uType, int defaultReturn);
  ACPL_PORT void appInfo(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT ErrorResult appWarning(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT void appSevereError(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT ErrorResult appError(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT ErrorResult appARIError(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT void appTerminalError(ULONG_PTR category, const unsigned int specific, const ACHAR* pLocation, const ACHAR* pContextData, const ACHAR* pRevision);
  ACPL_PORT void appLogMessage(const ACHAR* pTitle, const ACHAR* pMsg);
  ACPL_PORT bool appSetLogHandle(const ACHAR* pFilePathName);
};
#endif
