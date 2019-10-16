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
// Name:            AcFdUtil.h
//
// Description:     Header for global methods exported from AcFdEval 
//                  module
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "adesk.h"
#include "AdAChar.h"
#include "AcCell.h"
#ifdef ACFD_API
#  define ACFD_PORT	__declspec(dllexport)
#else 
#  define ACFD_PORT
#endif
typedef Adesk::UInt32 AcDbEvalNodeId;
namespace AcFdEval
{
  enum ObjectFieldOption
  {
    kObjFieldNone = 0,
    kObjFieldUnresolvedBlockRef = (0x1 << 0),
    kObjFieldApplyBlockTransform = (0x1 << 1),
    kObjFieldUnresolvedObjectRef = (0x1 << 2)
  };
  enum SheetSetFieldOption
  {
    kSheetSetNone = 0,
    kSheetSetHyperlink = (0x1 << 0),
    kSheetSetUnresolvedComponent = (0x1 << 1)
  };
  enum ExpressionFieldOption
  {
    kExprFieldNone = 0,
    kExprFieldSum = (0x1 << 0),
    kExprFieldAverage = (0x1 << 1),
    kExprFieldCount = (0x1 << 2),
    kExprFieldCell = (0x1 << 3),
    kExprFieldEquation = (0x1 << 4)
  };
}
struct IAcSmDatabase;
struct IAcSmSheetSet;
struct IAcSmComponent;
struct AcHyperlink;
ACFD_PORT bool AcFdMakeFieldCode(const AcDbObjectId& objId, AcDbEvalNodeId blockParamId, const ACHAR* pszPropOrConnectionName, AcFdEval::ObjectFieldOption nOption, const ACHAR* pszFormat, AcHyperlink* pHyperlink, AcString& pszFieldCode);
Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);
inline bool AcFdMakeFieldCode(const AcDbObjectId& objId, AcDbEvalNodeId blockParamId, const ACHAR* pszPropOrConnectionName, AcFdEval::ObjectFieldOption nOption, const ACHAR* pszFormat, AcHyperlink* pHyperlink, ACHAR*& pszFieldCode)
{
  AcString sFieldCode;
  const bool bRet = ::AcFdMakeFieldCode(objId, blockParamId, pszPropOrConnectionName, nOption, pszFormat, pHyperlink, sFieldCode);
  pszFieldCode = nullptr;
  if (bRet)
  {
    ::acutNewString(sFieldCode.kwszPtr(), pszFieldCode);
  }
  return bRet;
}
ACFD_PORT bool AcFdMakeFieldCode(IAcSmDatabase* pSmDb, IAcSmSheetSet* pSmSheetSet, IAcSmComponent* pSmComp, const ACHAR* pszCompName, const ACHAR* pszPropName, AcFdEval::SheetSetFieldOption nOption, const ACHAR* pszFormat, AcString& pszFieldCode);
inline bool AcFdMakeFieldCode(IAcSmDatabase* pSmDb, IAcSmSheetSet* pSmSheetSet, IAcSmComponent* pSmComp, const ACHAR* pszCompName, const ACHAR* pszPropName, AcFdEval::SheetSetFieldOption nOption, const ACHAR* pszFormat, ACHAR*& pszFieldCode)
{
  AcString sFieldCode;
  const bool bRet = ::AcFdMakeFieldCode(pSmDb, pSmSheetSet, pSmComp, pszCompName, pszPropName, nOption, pszFormat, sFieldCode);
  pszFieldCode = nullptr;
  if (bRet)
  {
    ::acutNewString(sFieldCode.kwszPtr(), pszFieldCode);
  }
  return bRet;
}
ACFD_PORT bool AcFdMakeFieldCode(const AcDbObjectId& tableId, const AcDbObjectId& targetTableId, AcFdEval::ExpressionFieldOption nOption, const AcCellRangeArray& cellRanges, const ACHAR* pszFormat, AcHyperlink* pHyperlink, AcString& sFieldCode);
inline bool AcFdMakeFieldCode(const AcDbObjectId& tableId, const AcDbObjectId& targetTableId, AcFdEval::ExpressionFieldOption nOption, const AcCellRangeArray& cellRanges, const ACHAR* pszFormat, AcHyperlink* pHyperlink, ACHAR*& pszFieldCode)
{
  AcString sFieldCode;
  const bool bRet = ::AcFdMakeFieldCode(tableId, targetTableId, nOption, cellRanges, pszFormat, pHyperlink, sFieldCode);
  pszFieldCode = nullptr;
  if (bRet)
  {
    ::acutNewString(sFieldCode.kwszPtr(), pszFieldCode);
  }
  return bRet;
}
ACFD_PORT bool AcFdExtractData(AcDbField* pField, AcString& sSheetSetFile, AcString& sSheetSetId, AcString& sCompName, AcString& sCompId, AcString& sPropName);
inline bool AcFdExtractData(AcDbField* pField, ACHAR*& pszSheetSetFile, ACHAR*& pszSheetSetId, ACHAR*& pszCompName, ACHAR*& pszCompId, ACHAR*& pszPropName)
{
  AcString sSheetSetFile, sSheetSetId, sCompName, sCompId, sPropName;
  const bool bRet = ::AcFdExtractData(pField, sSheetSetFile, sSheetSetId, sCompName, sCompId, sPropName);
  if (!bRet)
  {
    pszSheetSetFile = pszSheetSetId = pszCompName = pszCompId = pszPropName = nullptr;
  }
  else 
  {
    ::acutNewString(sSheetSetFile, pszSheetSetFile);
    ::acutNewString(sSheetSetId, pszSheetSetId);
    ::acutNewString(sCompName, pszCompName);
    ::acutNewString(sCompId, pszCompId);
    ::acutNewString(sPropName, pszPropName);
  }
  return bRet;
}
ACFD_PORT bool AcFdExtractData(AcDbField* pField, AcDbObjectId& objId, AcString& sPropName);
inline bool AcFdExtractData(AcDbField* pField, AcDbObjectId& objId, ACHAR*& pszPropName)
{
  AcString sPropName;
  const bool bRet = ::AcFdExtractData(pField, objId, sPropName);
  pszPropName = nullptr;
  if (bRet)
  {
    ::acutNewString(sPropName.kwszPtr(), pszPropName);
  }
  return bRet;
}
