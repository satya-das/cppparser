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
// This API extends AcGi to support stream draw functionality
//

#pragma once

#pragma pack(push, 8)

class AcGiDrawStreamImp;

typedef bool (*GraphicsUpdateProc)(const AcArray<AcGiDrawable*>& drawableArray);

///////////////////////////////////////////////////////////////////////////////
// class AcGiDrawStream
//
class ACDBCORE2D_PORT AcGiDrawStream : public AcGiDrawable
{
    friend class AcGiDrawStreamImp;

public:
    ACRX_DECLARE_MEMBERS(AcGiDrawStream);

    static bool build(const AcArray<AcGiDrawStream*>& streamArray, GraphicsUpdateProc lpFunc);

    AcGiDrawStream();
    AcGiDrawStream(const AcGiDrawable* pOwner);
   ~AcGiDrawStream();

    AcGiDrawable* getOwner() const;
    void setOwner(const AcGiDrawable* pOwner);
    bool isValid() const;

    bool serializeOut(IAcWriteStream* pOutput) const;
    bool serializeIn(IAcReadStream* pInput, AcDbDatabase* pDb = NULL);

    // Overridden methods from AcGiDrawable
    virtual Adesk::Boolean isPersistent() const ADESK_OVERRIDE;
    virtual AcDbObjectId id() const ADESK_OVERRIDE;
    virtual AcGiDrawable::DrawableType drawableType() const ADESK_OVERRIDE;
    virtual bool bounds(AcDbExtents& bounds) const ADESK_OVERRIDE;
    virtual void setDrawStream(AcGiDrawStream* pStream) ADESK_OVERRIDE;
    virtual AcGiDrawStream* drawStream() const ADESK_OVERRIDE;

protected:
    // Overridden methods from AcGiDrawable
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) ADESK_OVERRIDE;
    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* pWd) ADESK_OVERRIDE;
    virtual void subViewportDraw(AcGiViewportDraw* pVd) ADESK_OVERRIDE;
    virtual Adesk::UInt32 subViewportDrawLogicalFlags(AcGiViewportDraw* pVd) ADESK_OVERRIDE;

protected:
    AcGiDrawStreamImp* m_pImp;
};

#pragma pack(pop)
