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

#ifndef __DBWIPE_H__
#define __DBWIPE_H__

#ifdef _DBWIPEOBJ_
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP
#endif

#include "imgdef.h"
#include "imgent.h"

namespace Atil
{
    class Image;
};

#define WIPEOUTOBJSERVICE	/*NOXLATE*/ACRX_T("WipeOut")

/////////////////////////////////////////////////////////////////////////////
// AcDbWipeout class
//
#pragma warning(push)
#pragma warning( disable : 4275 ) 
class DLLIMPEXP AcDbWipeout : public AcDbRasterImage
{
public:
    ACRX_DECLARE_MEMBERS(AcDbWipeout);

                                AcDbWipeout();

    // AcDbEntity overrides
    //
    virtual AcRxObject*         clone() const override;

// AcDbRasterImage overwritten methods.

    virtual AcGeVector2d        imageSize(Adesk::Boolean bGetCachedValue = Adesk::kFalse) const override;
    AcGiSentScanLines*          getScanLines(const AcGiRequestScanLines& req) const override;
	Adesk::Boolean				isClipped() const;
	virtual void				setDisplayOpt(
                                    ImageDisplayOpt option, 
                                    Adesk::Boolean bValue
                                ) override;
	virtual Adesk::Boolean		isSetDisplayOpt(ImageDisplayOpt option) const override;

	virtual Acad::ErrorStatus	setBrightness( Adesk::Int8 value ) override;
	virtual Adesk::Int8			brightness() const override;
	
	virtual Acad::ErrorStatus	setContrast( Adesk::Int8 value ) override;
	virtual Adesk::Int8			contrast() const override;

	virtual Acad::ErrorStatus	setFade( Adesk::Int8 value ) override;
	virtual Adesk::Int8			fade() const override;

    virtual AcGeVector2d        scale() const override;

// Wipeout specific functions

    Acad::ErrorStatus           append(AcDbObjectId& id);
    static Acad::ErrorStatus    createImageDefinition();
    static Acad::ErrorStatus    fitPointsToImage(
                                    AcGePoint2dArray& pointArray,
                                    AcGePoint2d& minPoint,
                                    double& scale,
                                    Adesk::Boolean bFlipY = Adesk::kFalse);
    Adesk::Boolean              frame() const;

protected:
    virtual Adesk::Boolean      subWorldDraw(AcGiWorldDraw* mode) override;
    virtual void                subViewportDraw(AcGiViewportDraw* mode) override;

    virtual void                subList() const override;

    virtual Acad::ErrorStatus   subMoveGripPointsAt(
                                   const AcDbVoidPtrArray& gripAppData,
                                   const AcGeVector3d& offset, 
                                   const int bitflags) override;
    virtual Acad::ErrorStatus   subMoveGripPointsAt(
                                   const AcDbIntArray& indices,
                                   const AcGeVector3d&     offset) override;
    virtual Acad::ErrorStatus   subTransformBy(
                                    const AcGeMatrix3d& xform) override;
    virtual Acad::ErrorStatus   subGetTransformedCopy(
                                    const AcGeMatrix3d& xform,
                                    AcDbEntity*& ent
                                ) const override;
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
    virtual Adesk::UInt32       subSetAttributes (AcGiDrawableTraits * traits) override;

private:
    Adesk::Boolean              isHighlighted() const;

    void                        getPlane(AcGeBoundedPlane& boundedPlane) const;
    AcGeMatrix2d                fastMatrixInvert(const AcGeMatrix2d& m) const;
    void                        drawFrame(
                                    AcGiViewportDraw* mode,
                                    const AcGePoint3dArray& verts) const;
    Acad::ErrorStatus           setDcToScreen(
                                    const AcGePoint2d& lowerLeft,
                                    const AcGePoint2d& upperRight,
                                    int width,
                                    int height,
                                    AcGeMatrix2d& dcToScreen) const;
    void                        setFrameExtents(
                                    AcGiWorldDraw* mode,
                                    const AcGePoint3dArray& verts) const;


    bool                        drawFilledPloygon(  AcGiViewportDraw* mode, 
                                                    const AcGePoint3dArray& verts) const;
    bool                        IsSelfIntersecting( const AcGePoint3dArray& verts) const;

    Adesk::Boolean              isFrameVisible(Adesk::Boolean bPlotting = Adesk::kFalse) const;

public:
    static long                 mImageData;
private:
    Adesk::Boolean              mHighlight;

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 does not properly support array new and delete.
    // It tends to call the wrong delete operator and to not call
    // the dtors on all elements in the array.  So we make them
    // private in order to prevent usage of them.
    //
    void *operator new[](size_t nSize) throw() { return 0;}
    void operator delete[](void *p) {};
    void *operator new[](size_t nSize, const char *file, int line) throw() { return 0;}
};
#pragma warning(pop)
#endif //__DBWIPE_H__
