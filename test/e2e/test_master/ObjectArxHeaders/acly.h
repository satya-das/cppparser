//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _AC_LY_H
#  define _AC_LY_H
#  include "AdAChar.h"
#  include "acadstrc.h"
#  include "acarray.h"
#  include "dbsymtb.h"
#  include "dbxrecrd.h"
class AcLySystemInternals;
class AcLyRelExpr
{
public:
  virtual ~AcLyRelExpr()
  {
  }
  virtual const ACHAR* getVariable() const = 0;
  virtual const ACHAR* getConstant() const = 0;
};
class AcLyAndExpr
{
public:
  virtual ~AcLyAndExpr()
  {
  }
  virtual const AcArray<AcLyRelExpr*>& getRelExprs() const = 0;
};
//(a AND b) OR (c AND d) OR (e AND f)
class AcLyBoolExpr
{
public:
  virtual ~AcLyBoolExpr()
  {
  }
  virtual const AcArray<AcLyAndExpr*>& getAndExprs() const = 0;
};
#  ifndef HIMAGELIST
struct _IMAGELIST;
typedef struct _IMAGELIST* HIMAGELIST;
#  endif
class AcLyLayerFilter : public AcRxObject, public AcHeapOperators
{
public:
  ACRX_DECLARE_MEMBERS(AcLyLayerFilter);
  AcLyLayerFilter();
  virtual ~AcLyLayerFilter();
  virtual const ACHAR* name() const;
  virtual Acad::ErrorStatus setName(const ACHAR*);
  virtual bool allowRename() const;
  virtual Acad::ErrorStatus getImages(HIMAGELIST& imageList, Adesk::UInt32& normalImage, Adesk::UInt32& selected) const;
  virtual AcLyLayerFilter* parent() const;
  virtual const AcArray<AcLyLayerFilter*>& getNestedFilters() const;
  virtual Acad::ErrorStatus addNested(AcLyLayerFilter* filter);
  virtual Acad::ErrorStatus removeNested(AcLyLayerFilter* filter);
  virtual Acad::ErrorStatus generateNested();
  virtual bool dynamicallyGenerated() const;
  virtual bool allowNested() const;
  virtual bool allowDelete() const;
  virtual bool isProxy() const;
  virtual bool isIdFilter() const;
  virtual bool filter(AcDbLayerTableRecord* layer) const;
  enum DialogResult
  {
    kOk = 0,
    kCancel = 1,
    kUseDefault = 2
  };
  virtual DialogResult showEditor();
  virtual const ACHAR* filterExpression() const;
  virtual Acad::ErrorStatus setFilterExpression(const ACHAR* expr);
  virtual const AcLyBoolExpr* filterExpressionTree() const;
    /*
    BNF for the valid boolean expression we evaluate
    <bool_expr>::= <bool_expr> or <and_expr> | <and_expr>
    <and_expr>::=<and_expr> and <rel_expr> | <rel_expr>
    <rel_expr>::=<variable><rel_op><constant> 
    <rel_op>::= == | !=
    <constant>::=A-Z0-9*?~@.,-
    <variable>::=#A-Z0-9
    */
  virtual bool compareTo(const AcLyLayerFilter* pOther) const;
  virtual Acad::ErrorStatus readFrom(AcDbDxfFiler* filer);
  virtual Acad::ErrorStatus writeTo(AcDbDxfFiler* pFiler) const;
private:
  void* mp_impObj;
  friend class AcLySystemInternals;
protected:
  AcLyLayerFilter(AcLySystemInternals*);
};
class AcLyLayerGroup : public AcLyLayerFilter
{
public:
  ACRX_DECLARE_MEMBERS(AcLyLayerGroup);
  AcLyLayerGroup();
  virtual Acad::ErrorStatus addLayerId(const AcDbObjectId& id);
  virtual Acad::ErrorStatus removeLayerId(const AcDbObjectId& id);
  virtual const AcDbObjectIdArray& layerIds() const;
protected:
  AcLyLayerGroup(AcLySystemInternals*);
};
class AcLyLayerFilterManager
{
public:
  virtual ~AcLyLayerFilterManager()
  {
  }
  virtual Acad::ErrorStatus getFilters(AcLyLayerFilter*& pRoot, AcLyLayerFilter*& pCurrent) = 0;
  virtual Acad::ErrorStatus setFilters(const AcLyLayerFilter* pRoot, const AcLyLayerFilter* pCurrent) = 0;
};
AcLyLayerFilterManager* aclyGetLayerFilterManager(AcDbDatabase* pDb);
#endif
