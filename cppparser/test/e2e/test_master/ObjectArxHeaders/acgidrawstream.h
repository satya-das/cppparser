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
#pragma  once
#pragma  pack(push, 8)
class AcGiDrawStreamImp;
typedef bool (*GraphicsUpdateProc) (const AcArray<AcGiDrawable*>& drawableArray);
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
  Adesk::Boolean isPersistent() const override;
  AcDbObjectId id() const override;
  AcGiDrawable::DrawableType drawableType() const override;
  bool bounds(AcDbExtents& bounds) const override;
  void setDrawStream(AcGiDrawStream* pStream) override;
  AcGiDrawStream* drawStream() const override;
protected:
    // Overridden methods from AcGiDrawable
  Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) override;
  Adesk::Boolean subWorldDraw(AcGiWorldDraw* pWd) override;
  void subViewportDraw(AcGiViewportDraw* pVd) override;
  Adesk::UInt32 subViewportDrawLogicalFlags(AcGiViewportDraw* pVd) override;
protected:
  AcGiDrawStreamImp* m_pImp;
};
#pragma  pack(pop)
