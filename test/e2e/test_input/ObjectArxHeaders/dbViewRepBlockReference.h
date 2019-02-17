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

#pragma once
#pragma pack (push, 8)

#ifndef ACSYNERGY_PORT
#define ACSYNERGY_PORT
#endif

class AcDbImpViewRepBlockReference;

class ACSYNERGY_PORT AcDbViewRepBlockReference : public AcDbBlockReference
{
    friend class AcDbViewRepBlockReferenceInternals;

public:
    ACRX_DECLARE_MEMBERS(AcDbViewRepBlockReference);
    virtual ~AcDbViewRepBlockReference();

    AcDbObjectId                        ownerViewportId() const;


    // AcRxObject Protocol
    virtual Acad::ErrorStatus           copyFrom(const AcRxObject* pSrc) override;

    // AcDbObject methods
    virtual Acad::ErrorStatus           dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus           dwgInFields(AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus           dxfOutFields(AcDbDxfFiler* pFiler) const override;
    virtual Acad::ErrorStatus           dxfInFields(AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus           audit(AcDbAuditInfo* pAuditInfo) override;

    // AcDbEntity methods
    virtual void                        saveAs(AcGiWorldDraw* mode, AcDb::SaveType st) override;
    virtual Acad::ErrorStatus           subGetGeomExtents(AcDbExtents& extents) const override;
    virtual Acad::ErrorStatus           subGetGsMarkersAtSubentPath(
                                            const AcDbFullSubentPath& subPath, 
                                            AcArray<Adesk::GsMarker>& gsMarkers) const override;

    // AcDbBlockReference methods
    virtual AcGePoint3d                 position() const override;

protected:
    // AcDbObject methods
    virtual Adesk::Boolean              subWorldDraw(AcGiWorldDraw* mode) override;
    virtual void                        subViewportDraw(AcGiViewportDraw* pVd) override;
    virtual Acad::ErrorStatus           subTransformBy(const AcGeMatrix3d& xform) override;

    virtual  Acad::ErrorStatus          subPushHighlight  (const AcDbFullSubentPath& subId,
                                                           AcGiHighlightStyle        highlightStyle) override;
    virtual  Acad::ErrorStatus          subPopHighlight   (const AcDbFullSubentPath& subId) override;


public: 
    // internal use only methods
    AcDbViewRepBlockReference();
    AcDbViewRepBlockReference(const AcGePoint3d& position, AcDbObjectId blockTableRecord);
    void                                setOwnerViewportId(const AcDbObjectId& viewportId);

private:
    AcDbImpViewRepBlockReference*       getImpObject();
    AcDbImpViewRepBlockReference*       mpAcDbImpViewRepBlockReference;
};

#pragma pack (pop)
