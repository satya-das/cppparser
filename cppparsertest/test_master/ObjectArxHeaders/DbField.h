//
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
// Name:            DbField.h
//
// Description:     AcDbObject derived API classes for fields. 
//                  Contains the following classes: 
//                      AcDbField
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "AdAChar.h"
#include "AcField.h"
#include "acstring.h"
class AcDbField;
typedef AcArray<AcDbField*> AcDbFieldArray;
//*************************************************************************
// AcFd
//*************************************************************************
typedef struct AcFd
{
    // Enum for acdbEvaluateFields
  enum EvalFields
  {
    kEvalRecursive = (0x1 << 0)
  };
    // Options for function acdbConvertFieldsToText()
  enum ConvertFieldToText
  {
    kConvertFieldToTextNone = 0,
    kEvaluateBeforeConversion = (0x1 << 0),
    kExcludeEvaluatorsInList = (0x1 << 1),
    kIgnoreEvaluatorVersion = (0x1 << 2)
  };
} AcFd;
//*************************************************************************
// AcHyperlink
//*************************************************************************
typedef struct AcHyperlink
{
  AcString msUrl;
  AcString msSubLocation;
  AcString msDescription;
  Adesk::Int32 mlFlag;
} AcHyperlink;
//*************************************************************************
// AcDbField
//*************************************************************************
class AcDbField : public AcDbObject
{
public:
  enum State
  {
    kInitialized = (0x1 << 0),
    kCompiled = (0x1 << 1),
    kModified = (0x1 << 2),
    kEvaluated = (0x1 << 3),
    kHasCache = (0x1 << 4),
    kHasFormattedString = (0x1 << 5)
  };
  enum EvalOption
  {
    kDisable = 0,
    kOnOpen = (0x1 << 0),
    kOnSave = (0x1 << 1),
    kOnPlot = (0x1 << 2),
    kOnEtransmit = (0x1 << 3),
    kOnRegen = (0x1 << 4),
    kOnDemand = (0x1 << 5),
    kAutomatic = (kOnOpen | kOnSave | kOnPlot | kOnEtransmit | kOnRegen | kOnDemand)
  };
  enum EvalContext
  {
    kOpen = (0x1 << 0),
    kSave = (0x1 << 1),
    kPlot = (0x1 << 2),
    kEtransmit = (0x1 << 3),
    kRegen = (0x1 << 4),
    kDemand = (0x1 << 5),
    kPreview = (0x1 << 6),
    kPlotPreview = (0x1 << 7)
  };
  enum EvalStatus
  {
    kNotYetEvaluated = (0x1 << 0),
    kSuccess = (0x1 << 1),
    kEvaluatorNotFound = (0x1 << 2),
    kSyntaxError = (0x1 << 3),
    kInvalidCode = (0x1 << 4),
    kInvalidContext = (0x1 << 5),
    kOtherError = (0x1 << 6)
  };
  enum FieldCodeFlag
  {
    kFieldCode = (0x1 << 0),
    kEvaluatedText = (0x1 << 1),
    kEvaluatedChildren = (0x1 << 2),
    kObjectReference = (0x1 << 3),
                                                // this field as object reference if this is not text field. Used only in getFieldCode().
    kAddMarkers = (0x1 << 4),
    kEscapeBackslash = (0x1 << 5),
    kStripOptions = (0x1 << 6),
    kPreserveFields = (0x1 << 7),
    kTextField = (0x1 << 8),
    kPreserveOptions = (0x1 << 9),
    kDetachChildren = (0x1 << 10),
                                                // Used only in setFieldCode().
    kChildObjectReference = (0x1 << 11),
                                                // Used only in getFieldCode().
    kForExpression = (0x1 << 12),
                                                // Get the value in a format which can be used in arithmatic expressions. Used only in getFieldCode().
  };
  enum FilingOption
  {
    kSkipFilingResult = (0x1 << 0)
  };
  ACDB_DECLARE_MEMBERS(AcDbField);
  ACDBCORE2D_PORT AcDbField(void);
  ACDBCORE2D_PORT AcDbField(const ACHAR* pszFieldCode, bool bTextField = false);
  ACDBCORE2D_PORT ~AcDbField();
  ACDBCORE2D_PORT Acad::ErrorStatus setInObject(AcDbObject* pObj, const ACHAR* pszPropName);
  ACDBCORE2D_PORT Acad::ErrorStatus postInDatabase(AcDbDatabase* pDb);
  ACDBCORE2D_PORT AcDbField::State state(void) const;
  ACDBCORE2D_PORT AcDbField::EvalStatus evaluationStatus(int* pnErrCode, AcString* pszErrMsg) const;
  AcDbField::EvalStatus evaluationStatus(int* pnErrCode) const;
  AcDbField::EvalStatus evaluationStatus() const;
  AcDbField::EvalStatus evaluationStatus(int* pnErrCode, ACHAR** pszErrMsg) const;
  ACDBCORE2D_PORT AcDbField::EvalOption evaluationOption(void) const;
  ACDBCORE2D_PORT Acad::ErrorStatus setEvaluationOption(AcDbField::EvalOption nEvalOption);
  ACDBCORE2D_PORT AcDbField::FilingOption filingOption(void) const;
  ACDBCORE2D_PORT Acad::ErrorStatus setFilingOption(AcDbField::FilingOption nOption);
  ACDBCORE2D_PORT const ACHAR* evaluatorId(void) const;
  ACDBCORE2D_PORT Acad::ErrorStatus setEvaluatorId(const ACHAR* pszEvaluatorId);
  bool isTextField(void) const;
  Acad::ErrorStatus convertToTextField(void);
  ACDBCORE2D_PORT const ACHAR* getFieldCode(AcDbField::FieldCodeFlag nFlag, AcArray<AcDbField*>* pChildFields = NULL, AcDb::OpenMode mode = AcDb::kForRead) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getFieldCode(AcString& sFieldCode, AcDbField::FieldCodeFlag nFlag, AcArray<AcDbField*>* pChildFields = nullptr, AcDb::OpenMode mode = AcDb::kForRead) const;
  Acad::ErrorStatus getFieldCode(ACHAR*& pszFieldCode, AcDbField::FieldCodeFlag nFlag, AcArray<AcDbField*>* pChildFields = nullptr, AcDb::OpenMode mode = AcDb::kForRead) const;
  ACDBCORE2D_PORT Acad::ErrorStatus setFieldCode(const ACHAR* pszFieldCode, AcDbField::FieldCodeFlag nFlag = (AcDbField::FieldCodeFlag) 0, AcDbFieldArray* pChildFields = NULL);
  ACDBCORE2D_PORT int childCount(void) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getChild(int iIndex, AcDbField*& pField, AcDb::OpenMode mode);
  ACDBCORE2D_PORT const ACHAR* getFormat(void) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getFormat(AcString& sFormat) const;
  Acad::ErrorStatus getFormat(ACHAR*& pszFormat) const;
  ACDBCORE2D_PORT Acad::ErrorStatus setFormat(const ACHAR* pszFormat);
  ACDBCORE2D_PORT Acad::ErrorStatus evaluate(int nContext, AcDbDatabase* pDb, int* pNumFound = NULL, int* pNumEvaluated = NULL);
  ACDBCORE2D_PORT AcValue::DataType dataType(void) const;
  ACDBCORE2D_PORT const ACHAR* getValue(void) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getValue(AcString& sValue) const;
  Acad::ErrorStatus getValue(ACHAR*& pszValue) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getValue(AcValue& value) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getValue(AcFdFieldValue& value) const;
  ACDBCORE2D_PORT bool hasHyperlink(void) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getHyperlink(AcHyperlink& hlink) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getHyperlink(AcString* psName, AcString* psDescription, AcString* psSubLocation, AcString* psDisplayString, Adesk::Int32* pFlag) const;
  Acad::ErrorStatus getHyperlink(ACHAR** pszName, ACHAR** pszDescription, ACHAR** pszSubLocation, ACHAR** pszDisplayString, Adesk::Int32* pFlag) const;
  ACDBCORE2D_PORT Acad::ErrorStatus setHyperlink(const AcHyperlink& hlink);
  ACDBCORE2D_PORT Acad::ErrorStatus setHyperlink(const ACHAR* pszName, const ACHAR* pszDescription, const ACHAR* pszSubLocation = NULL);
  ACDBCORE2D_PORT Acad::ErrorStatus setHyperlink(const ACHAR* pszName, const ACHAR* pszDescription, const ACHAR* pszSubLocation, Adesk::Int32 lFlag);
  ACDBCORE2D_PORT Acad::ErrorStatus removeHyperlink(void);
  ACDBCORE2D_PORT Acad::ErrorStatus getData(const ACHAR* pszKey, AcValue* pData) const;
  ACDBCORE2D_PORT Acad::ErrorStatus setData(const ACHAR* pszKey, const AcValue* pData);
  ACDBCORE2D_PORT Acad::ErrorStatus setData(const ACHAR* pszKey, const AcValue* pData, bool bRecursive);
    // Base class overrides
  ACDBCORE2D_PORT virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
  ACDBCORE2D_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
  ACDBCORE2D_PORT virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
  ACDBCORE2D_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
  ACDBCORE2D_PORT virtual Acad::ErrorStatus subClose() override;
};
// These two inlines exist because of the deprecated method taking ACHAR **.
// Otherwise we could use default params as in (int * pnErrCode = nullptr)
inline AcDbField::EvalStatus AcDbField::evaluationStatus(int* pnErrCode) const
{
  AcString* pNullStr = nullptr;
  return this->evaluationStatus(pnErrCode, pNullStr);
}
inline AcDbField::EvalStatus AcDbField::evaluationStatus() const
{
  return this->evaluationStatus(nullptr);
}
// this overload is deprecated. Please call the one taking AcString * arg
inline AcDbField::EvalStatus AcDbField::evaluationStatus(int* pnErrCode, ACHAR** pszErrMsg) const
{
  AcString sErrMsg;
  AcString* pErrMsgStr = pszErrMsg ? &sErrMsg : nullptr;
  const AcDbField::EvalStatus es = this->evaluationStatus(pnErrCode, pErrMsgStr);
  if (pszErrMsg != nullptr)
  {
    if (*pErrMsgStr == nullptr)
    {
      *pszErrMsg = nullptr;
    }
    else 
    {
      ::acutNewString(sErrMsg.kwszPtr(), *pszErrMsg);
    }
  }
  return es;
}
// this overload is deprecated. Please call the one taking AcString * arg
inline Acad::ErrorStatus AcDbField::getFieldCode(ACHAR*& pszFieldCode, AcDbField::FieldCodeFlag nFlag, AcArray<AcDbField*>* pChildFields, AcDb::OpenMode mode) const
{
  AcString sFieldCode;
  return ::acutAcStringToAChar(sFieldCode, pszFieldCode, this->getFieldCode(sFieldCode, nFlag, pChildFields, mode));
}
// this overload is deprecated. Please call the one taking AcString * arg
inline Acad::ErrorStatus AcDbField::getFormat(ACHAR*& pszFormat) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbField::getFormat, pszFormat);
}
// this overload is deprecated. Please call the one taking AcString * arg
inline Acad::ErrorStatus AcDbField::getValue(ACHAR*& pszValue) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbField::getValue, pszValue);
}
// this overload is deprecated. Please call the one taking AcString * args
inline Acad::ErrorStatus AcDbField::getHyperlink(ACHAR** pszName, ACHAR** pszDescription, ACHAR** pszSubLocation, ACHAR** pszDisplayString, Adesk::Int32* pFlag) const
{
  AcString sName, sDescription, sSubLocation, sDisplayString;
  const Acad::ErrorStatus es = this->getHyperlink(pszName == nullptr ? nullptr : &sName, pszDescription == nullptr ? nullptr : &sDescription, pszSubLocation == nullptr ? nullptr : &sSubLocation, pszDisplayString == nullptr ? nullptr : &sDisplayString, pFlag);
  if (pszName != nullptr)
  {
    *pszName = nullptr;
    if (es == Acad::eOk)
    {
      ::acutNewString(sName.kwszPtr(), *pszName);
    }
  }
  if (pszDescription != nullptr)
  {
    *pszDescription = nullptr;
    if (es == Acad::eOk)
    {
      ::acutNewString(sDescription.kwszPtr(), *pszDescription);
    }
  }
  if (pszSubLocation != nullptr)
  {
    *pszSubLocation = nullptr;
    if (es == Acad::eOk)
    {
      ::acutNewString(sSubLocation.kwszPtr(), *pszSubLocation);
    }
  }
  if (pszDisplayString != nullptr)
  {
    *pszDisplayString = nullptr;
    if (es == Acad::eOk)
    {
      ::acutNewString(sDisplayString.kwszPtr(), *pszDisplayString);
    }
  }
  return es;
}
//*************************************************************************
// Global exported functions
//*************************************************************************
ACDBCORE2D_PORT AcFdFieldEngine* acdbGetFieldEngine(void);
ACDBCORE2D_PORT bool acdbGetFieldMarkers(const ACHAR*& pszPrefix, const ACHAR*& pszSuffix);
ACDBCORE2D_PORT bool acdbHasFields(const ACHAR* pszText);
ACDBCORE2D_PORT bool acdbFindField(const ACHAR* pszText, int iSearchFrom, int& nStartPos, int& nEndPos);
ACDBCORE2D_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectId& objId, int nContext, const ACHAR* pszPropName = NULL, AcDbDatabase* pDb = NULL, AcFd::EvalFields nEvalFlag = AcFd::kEvalRecursive, int* pNumFound = NULL, int* pNumEvaluated = NULL);
ACDBCORE2D_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectId& objId, int nContext, const AcDbObjectIdArray* pFieldsToEvaluate, const ACHAR* pszEvaluatorId, AcDbDatabase* pDb, AcFd::EvalFields nEvalFlag, int* pNumFound, int* pNumEvaluated);
ACDBCORE2D_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectIdArray& objIds, int nContext, const ACHAR* pszPropName = NULL, AcDbDatabase* pDb = NULL, AcFd::EvalFields nEvalFlag = AcFd::kEvalRecursive, int* pNumFound = NULL, int* pNumEvaluated = NULL);
ACDBCORE2D_PORT Acad::ErrorStatus acdbEvaluateFields(const AcDbObjectIdArray& objIds, int nContext, const AcDbObjectIdArray* pFieldsToEvaluate, const ACHAR* pszEvaluatorId, AcDbDatabase* pDb, AcFd::EvalFields nEvalFlag, int* pNumFound, int* pNumEvaluated);
ACDBCORE2D_PORT Acad::ErrorStatus acdbConvertFieldsToText(AcDbDatabase* pDb, const AcStringArray* pEvalIds, AcFd::ConvertFieldToText nOption);
ACDBCORE2D_PORT Acad::ErrorStatus acdbConvertFieldsToText(const AcDbObjectIdArray& objIds, const AcStringArray* pEvalIds, AcFd::ConvertFieldToText nOption);
ACDBCORE2D_PORT Acad::ErrorStatus acdbMakeFieldCode(const ACHAR* pszFieldExpr, AcString& sFieldCode, const ACHAR* pszEvalId = nullptr, const ACHAR* pszFormat = nullptr, const AcHyperlink* pHyperlink = nullptr);
// This overload which allocates an ACHAR buf is deprecated.
// Please use the above overload taking AcString & arg instead
inline Acad::ErrorStatus acdbMakeFieldCode(const ACHAR* pszFieldExpr, ACHAR*& pszFieldCode, const ACHAR* pszEvalId, const ACHAR* pszFormat, const AcHyperlink* pHyperlink)
{
  AcString sFieldCode;
  return ::acutAcStringToAChar(sFieldCode, pszFieldCode, ::acdbMakeFieldCode(pszFieldExpr, sFieldCode, pszEvalId, pszFormat, pHyperlink));
}
