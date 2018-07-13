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

#ifndef _AC_LY_H
#define _AC_LY_H

#include "AdAChar.h"
#include "acadstrc.h"
#include "acarray.h"
#include "dbsymtb.h"
#include "dbxrecrd.h"

class AcLySystemInternals;

//Filter parse tree API (read-only)
//
//represents an relational expression of the form:
//variable OP constant
//where OP is either the equality operator (==) or the LIKE 
//operator
//
class AcLyRelExpr 
{
public:
    virtual ~AcLyRelExpr() { }

    virtual const ACHAR * getVariable() const = 0;
    virtual const ACHAR * getConstant() const = 0;
};

//represents a term of the form:
//a AND b
class AcLyAndExpr 
{
public:
    virtual ~AcLyAndExpr() { }
    virtual const AcArray<AcLyRelExpr*>& getRelExprs() const = 0;
};

//represents an expression of the form:
//(a AND b) OR (c AND d) OR (e AND f)
class AcLyBoolExpr 
{
public:
    virtual ~AcLyBoolExpr() { }
    virtual const AcArray<AcLyAndExpr*>& getAndExprs() const = 0;
};

#ifndef HIMAGELIST
struct _IMAGELIST;
typedef struct _IMAGELIST* HIMAGELIST;
#endif

//Main filter API. All layer filters implement this interface.
class AcLyLayerFilter : public AcRxObject, public AcHeapOperators
{
public:
    ACRX_DECLARE_MEMBERS(AcLyLayerFilter);
    AcLyLayerFilter ();
    virtual ~AcLyLayerFilter ();

    //persistent name of filter, some filters may not allow
    //renaming ("All", "Xref", etc.)
    virtual const ACHAR * name() const;
    virtual Acad::ErrorStatus setName(const ACHAR *);
    virtual bool allowRename() const;

    virtual Acad::ErrorStatus getImages(HIMAGELIST& imageList, Adesk::UInt32& normalImage, Adesk::UInt32& selected) const;

    virtual AcLyLayerFilter* parent() const;

    //nested filter manipulation
    virtual const AcArray<AcLyLayerFilter*>& getNestedFilters() const;
    virtual Acad::ErrorStatus addNested(AcLyLayerFilter* filter);
    virtual Acad::ErrorStatus removeNested(AcLyLayerFilter* filter);

    //some filters generate nested filters automatically (xref, standard)
    //the following api will be called on filters after they are loaded to allow 
    //them to regenerate their nested filters
    virtual Acad::ErrorStatus generateNested();

    //returns true if this filter was dynamically generated i.e.
    //it doesn't persist on its own
    virtual bool dynamicallyGenerated() const;

    //returns true if this filter can have nested filters
    virtual bool allowNested() const;

    //returns true if this filter can be removed
    virtual bool allowDelete() const;

    //return true if this filter is a proxy for an
    //unknown filter (we are not going to show these on the UI)
    virtual bool isProxy() const;

    //groups are id filters, i.e. filters on layer id.
    virtual bool isIdFilter() const;
    
    //returns true if the given layer is "visible" with this filter
    //false otherwise
    virtual bool filter(AcDbLayerTableRecord* layer) const;

    //called by host application to show an editor window for the filter.
    //Display the editor as child of the active popup window
    //Return kUseDefault if you want to instruct the host application to
    //display the default filter dialog.
    enum DialogResult {kOk = 0, kCancel=1, kUseDefault = 2};
    virtual  DialogResult showEditor();

    virtual const ACHAR * filterExpression() const;
    virtual Acad::ErrorStatus setFilterExpression(const ACHAR * expr);

    //returns a simple expression tree for this filter
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

    //returns true if this and pOther will allow the same
    //layers
    virtual bool compareTo(const AcLyLayerFilter* pOther) const;

    //persistence support
    //
    //read/write native data, we use a dxf filer to decouple the filter
    //from the underlying xrecod. This is necessary to support custom filter
    //types.
    virtual Acad::ErrorStatus readFrom(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus writeTo(AcDbDxfFiler* pFiler) const;

private:
    void *mp_impObj;
    friend class AcLySystemInternals;

protected:
    AcLyLayerFilter(AcLySystemInternals*);
};


class AcLyLayerGroup : public AcLyLayerFilter
{
public:
    ACRX_DECLARE_MEMBERS(AcLyLayerGroup);
    AcLyLayerGroup();

    virtual Acad::ErrorStatus        addLayerId    (const AcDbObjectId& id);
    virtual Acad::ErrorStatus        removeLayerId (const AcDbObjectId& id);
    virtual const AcDbObjectIdArray& layerIds      () const;

protected:
    AcLyLayerGroup(AcLySystemInternals*);
};


class AcLyLayerFilterManager
{
public:
    virtual ~AcLyLayerFilterManager() { }

    //reads the filters from the database this manager belongs to, and returns
    //the root filter in pRoot.
    //The caller is responsible for deleting  the filters
    //by calling delete pRoot;
    virtual Acad::ErrorStatus getFilters(AcLyLayerFilter*& pRoot, AcLyLayerFilter*& pCurrent) = 0;
    //writes the filters pointer by pRoot into the current
    //database, call the various writeTo methods on each filter
    virtual Acad::ErrorStatus setFilters( const AcLyLayerFilter* pRoot, const AcLyLayerFilter* pCurrent) = 0;
};

//returns the filter manager for the given database
AcLyLayerFilterManager* aclyGetLayerFilterManager(AcDbDatabase* pDb);

#endif  // _AC_LY_H
