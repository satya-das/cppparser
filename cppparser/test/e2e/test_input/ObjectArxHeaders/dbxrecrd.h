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
// DESCRIPTION: AcDbXrecord class definition.

#ifndef ACDB_XRECORD_H
#define ACDB_XRECORD_H

#include "AdAChar.h"
#include "dbmain.h"

#define ACDB_XRECORD_CLASS          ACRX_T(/*MSG0*/"AcDbXrecord")
#define ACDB_XRECORD_ITERATOR_CLASS ACRX_T(/*MSG0*/"AcDbXrecordClass")

#pragma pack(push, 8)

class AcDbXrecord: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbXrecord);
    AcDbXrecord();
    virtual ~AcDbXrecord();

    // auxDb parameter only useded when working with
    // non-Database-resident instances.

    Acad::ErrorStatus rbChain(resbuf** ppRb, AcDbDatabase* auxDb = NULL) const;
    Acad::ErrorStatus setFromRbChain(const resbuf& pRb,
                                             AcDbDatabase* auxDb = NULL);
    ACDBCORE2D_PORT Acad::ErrorStatus appendRbChain(const resbuf& pRb);
    bool              isXlateReferences() const;
    void              setXlateReferences(bool translate);

    // Overridden methods from AcDbObject
    //
    virtual Acad::ErrorStatus subClose() override;
    virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;

    virtual AcDb::DuplicateRecordCloning mergeStyle() const override;
    virtual void  setMergeStyle(AcDb::DuplicateRecordCloning style);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbImpXrecordIterator;

class AcDbXrecordIterator: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbXrecordIterator);
 
    AcDbXrecordIterator(const AcDbXrecord* pXrecord);
    virtual ~AcDbXrecordIterator();

    void              start();
    bool              done() const;
    Acad::ErrorStatus next();
    int               curRestype() const;
    Acad::ErrorStatus getCurResbuf(resbuf& outItem, AcDbDatabase* db) const;
    ACDBCORE2D_PORT Acad::ErrorStatus modifyCurResbuf(const resbuf& item);
    ACDBCORE2D_PORT Acad::ErrorStatus insertRbChain(const resbuf& pRb);
    ACDBCORE2D_PORT Acad::ErrorStatus removeCurResbuf();

protected:
    AcDbXrecordIterator() {};
private:
    friend class AcDbXrecord;
    friend class AcDbImpXrecord;
    AcDbImpXrecordIterator* mpImpIter;
};

#pragma pack(pop)

#endif
