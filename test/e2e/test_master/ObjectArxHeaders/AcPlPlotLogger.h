//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACPLPLOTLOGGER_H
#  define ACPLPLOTLOGGER_H
class ADESK_NO_VTABLE AcPlPlotLogger
{
public:
  AcPlPlotLogger()
  {
  }
  virtual ~AcPlPlotLogger()
  {
  }
  virtual Acad::ErrorStatus startJob(void) = 0;
  virtual Acad::ErrorStatus startSheet(void) = 0;
  virtual Acad::ErrorStatus logTerminalError(const ACHAR* pErrorString) = 0;
  virtual Acad::ErrorStatus logARIError(const ACHAR* pErrorString) = 0;
  virtual Acad::ErrorStatus logSevereError(const ACHAR* pErrorString) = 0;
  virtual Acad::ErrorStatus logError(const ACHAR* pErrorString) = 0;
  virtual Acad::ErrorStatus logWarning(const ACHAR* pWarningString) = 0;
  virtual Acad::ErrorStatus logMessage(const ACHAR* pMessageString) = 0;
  virtual Acad::ErrorStatus logInformation(const ACHAR* pMessageString) = 0;
  virtual Acad::ErrorStatus endSheet(void) = 0;
  virtual bool errorHasHappenedInSheet(void) const = 0;
  virtual bool warningHasHappenedInSheet(void) const = 0;
  virtual Acad::ErrorStatus endJob(void) = 0;
  virtual bool errorHasHappenedInJob(void) const = 0;
  virtual bool warningHasHappenedInJob(void) const = 0;
};
#endif
