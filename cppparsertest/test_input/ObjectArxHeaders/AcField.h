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
// Name:            AcField.h
//
// Description:     AcRxObject derived API classes for fields. Contains 
//                  the following classes: 
//                      AcFdFieldEvaluator
//                      AcFdFieldEvaluatorLoader
//                      AcFdFieldEngine
//                      AcFdFieldResult
//                      AcFdFieldValue
//                      AcFdFieldReactor
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "adesk.h"
#include "AdAChar.h"
#include "AcValue.h"

class AcDbField;
class AcDbFieldCache;
class AcFdFieldResult;
class AcFdFieldEvaluator;
class AcFdFieldEvaluatorLoader;
class AcFdFieldEngine;
class AcFdFieldValue;
class AcFdImpFieldFormat;
class AcDbEvalVariant;


//*************************************************************************
// AcFdFieldEvaluator
//*************************************************************************

class AcFdFieldEvaluator : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldEvaluator);

    ACDBCORE2D_PORT AcFdFieldEvaluator(void);
    ACDBCORE2D_PORT virtual ~AcFdFieldEvaluator(void);

    ACDBCORE2D_PORT virtual const ACHAR * evaluatorId(void) const;
    ACDBCORE2D_PORT virtual const ACHAR * evaluatorId(AcDbField* pField);

    ACDBCORE2D_PORT virtual Acad::ErrorStatus initialize(AcDbField* pField); 
    ACDBCORE2D_PORT virtual Acad::ErrorStatus compile(AcDbField* pField, 
                                             AcDbDatabase* pDb,
                                             AcFdFieldResult* pResult);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus evaluate(AcDbField* pField, 
                                             int nContext, 
                                             AcDbDatabase* pDb, 
                                             AcFdFieldResult* pResult);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus format(AcDbField* pField, 
                                             AcString & sValue);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus format(AcDbField* pField, 
                                             ACHAR *& pszValue) final;  // deprecated inline

protected:
    AcFdFieldEvaluator(void*);

protected:
    void        *   mpImpObj;

private:
    friend class AcFdSystemInternals;
};

// This overload which allocates an ACHAR buffer is deprecated
// Please use the other overload which takes an AcString & arg
inline Acad::ErrorStatus AcFdFieldEvaluator::format(AcDbField* pField, 
                                                    ACHAR *& pszValue)
{
    AcString sValue;
    return ::acutAcStringToAChar(sValue, pszValue, this->format(pField, sValue));
}

//*************************************************************************
// AcFdFieldEvaluatorLoader
//*************************************************************************

class AcFdFieldEvaluatorLoader : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldEvaluatorLoader);

    ACDBCORE2D_PORT AcFdFieldEvaluatorLoader(void);
    ACDBCORE2D_PORT AcFdFieldEvaluatorLoader(void*);    
    ACDBCORE2D_PORT ~AcFdFieldEvaluatorLoader(void);

    ACDBCORE2D_PORT virtual AcFdFieldEvaluator* getEvaluator(
                                                const ACHAR * pszEvalId);
    ACDBCORE2D_PORT virtual AcFdFieldEvaluator * findEvaluator(AcDbField* pField, 
                                             const ACHAR *& pszEvalId);

protected:
    void        *   mpImpObj;

private:
    friend class AcFdSystemInternals;
};


//*************************************************************************
// AcFdFieldEngine
//*************************************************************************

class AcFdFieldEngine : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldEngine);

    ACDBCORE2D_PORT AcFdFieldEngine();
    ACDBCORE2D_PORT virtual ~AcFdFieldEngine();

    ACDBCORE2D_PORT Acad::ErrorStatus registerEvaluatorLoader(AcFdFieldEvaluatorLoader* pLoader);
    ACDBCORE2D_PORT Acad::ErrorStatus unregisterEvaluatorLoader(AcFdFieldEvaluatorLoader* pLoader);
    ACDBCORE2D_PORT int   evaluatorLoaderCount    (void) const;
    ACDBCORE2D_PORT AcFdFieldEvaluatorLoader * getEvaluatorLoader(int iIndex);
    ACDBCORE2D_PORT AcFdFieldEvaluator * getEvaluator (const ACHAR * pszEvalId);
    ACDBCORE2D_PORT AcFdFieldEvaluator * findEvaluator(AcDbField* pField, 
                                             const ACHAR *& pszEvalId);

protected:
    void        *   mpImpObj;

private:
    friend class AcFdSystemInternals;
};


//*************************************************************************
// AcFdFieldResult
//*************************************************************************

class AcFdFieldResult : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldResult);

    AcFdFieldResult(void);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setFieldValue(const AcValue* pValue);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setEvaluationStatus(int nStatus, 
                                             int dwErrCode = 0, 
                                             const ACHAR * pszMsg = NULL);
};


//*************************************************************************
// AcFdFieldValue
//*************************************************************************

class AcFdFieldValue : public AcValue
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldValue);
    
    ACDBCORE2D_PORT AcFdFieldValue(void);
    ACDBCORE2D_PORT AcFdFieldValue(AcFdFieldValue::DataType nDataType);
    ACDBCORE2D_PORT AcFdFieldValue(const AcFdFieldValue& value);
    ACDBCORE2D_PORT AcFdFieldValue(const ACHAR * pszValue);
    ACDBCORE2D_PORT AcFdFieldValue(Adesk::Int32 lValue);
    ACDBCORE2D_PORT AcFdFieldValue(double fValue);
    ACDBCORE2D_PORT AcFdFieldValue(const Adesk::Time64& date);
    ACDBCORE2D_PORT AcFdFieldValue(const std::tm& date);
    ACDBCORE2D_PORT AcFdFieldValue(const AcGePoint2d& pt);
    ACDBCORE2D_PORT AcFdFieldValue(double x, double y);
    ACDBCORE2D_PORT AcFdFieldValue(const AcGePoint3d& pt);
    ACDBCORE2D_PORT AcFdFieldValue(double x, double y, double z);
    ACDBCORE2D_PORT AcFdFieldValue(const AcDbObjectId& id);
    ACDBCORE2D_PORT AcFdFieldValue(const resbuf& rb);
    ACDBCORE2D_PORT AcFdFieldValue(const AcDbEvalVariant& evalVar);
    ACDB_PORT AcFdFieldValue(const VARIANT& var);
    ACDBCORE2D_PORT AcFdFieldValue(const void* pBuf, uint32_t dwBufSize);
};


//*************************************************************************
// AcFdFieldReactor
//*************************************************************************

class AcFdFieldReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcFdFieldReactor);

    ACDBCORE2D_PORT virtual Acad::ErrorStatus beginEvaluateFields(int nContext, 
                                             AcDbDatabase* pDb);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus endEvaluateFields(int nContext, 
                                             AcDbDatabase* pDb);
};

typedef AcArray<AcFdFieldReactor*> FieldReactors;


//*************************************************************************
// Global exported functions
//*************************************************************************

ACDBCORE2D_PORT Acad::ErrorStatus   acdbAddFieldReactor     (AcFdFieldReactor* pReactor);
ACDBCORE2D_PORT Acad::ErrorStatus   acdbRemoveFieldReactor  (AcFdFieldReactor* pReactor);
