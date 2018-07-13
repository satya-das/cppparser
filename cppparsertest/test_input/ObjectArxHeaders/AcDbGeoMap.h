//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "dbents.h"
#include "imgvars.h"
#include "imgent.h"
#include "AcDbGeoTypes.h"

#pragma pack (push, 8)
#pragma warning(push)
#pragma warning(disable : 4275) // warning C4275: non dll-interface class 'AcDbRasterImage' used as base for dll-interface class 'AcDbGeoMap'

class GeoMapImp;


#ifdef  ACGEOLOCATIONOBJ_API
#  define ACGEOLOCATIONOBJ_PORT  __declspec(dllexport)
#else
#  define ACGEOLOCATIONOBJ_PORT
#endif


/// <summary>
/// the AcDbGeoMap class represents an embedded raster image which is captured from a portion of LiveMap
/// </summary>
///
class ACGEOLOCATIONOBJ_PORT AcDbGeoMap : public AcDbRasterImage
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGeoMap);

	/// <summary> Default constructor. For internal use only. </summary>
	///
	AcDbGeoMap();
    AcDbGeoMap(AcGeoMapType mapType, AcGeoMapResolution resolution, unsigned int levelOfDetail);
    AcDbGeoMap(AcDbObjectId viewportId, bool isViewportSpecific);

	/// <summary> Destructor. </summary>
	///
    virtual ~AcDbGeoMap();

public:
	// AcDbGeoMap protocol

	/// <summary> Returns the bottom left corner point of the image frame. </summary>
	///
    AcGePoint3d					bottomLeftPt() const;
	/// <summary> Returns the height of the image frame. </summary>
	///
	double						height() const;
	/// <summary> Returns the width of the image frame. </summary>
	///
    double						width() const;    

	/// <summary> Returns the bottom left corner of the embeded image. </summary>
	///
	AcGePoint3d					imageBottomLeftPt() const;
	/// <summary> Returns the height of the embeded image. </summary>
	///
	double						imageHeight() const;
	/// <summary> Returns the width of the embeded image. </summary>
	///
	double						imageWidth() const;

	/// <summary> 
	/// The resolution of the image that apply on top of LOD. 
	/// </summary>
	///
    /// <returns> Returns the current resolution of the map image, an enumerated value. </returns>
	///
    AcGeoMapResolution			resolution() const;

	/// <summary> 
	/// Sets the resolution for this map image. 
	/// </summary>
	///
    /// <param name="resolution">
    /// An enumerated value as resolution
    /// </param>
	///
    /// <returns> Returns Acad::eOk if a valid resolution is passed in. </returns>
	///
    Acad::ErrorStatus			setResolution(AcGeoMapResolution resolution);

	/// <summary> 
	/// Map Level Of Details (Zoom level) at the point of captured. Update will reset this value.
	/// </summary>
	///
    /// <returns> Returns an unsigned integer number for the level of details. </returns>
	///
	unsigned int				LOD() const; // 

	/// <summary> The map type of the map image. </summary>
	///
	///
    /// <returns> Returns the current map type of the map image, an enumerated value. </returns>
	///
	AcGeoMapType				mapType() const;

	/// <summary> 
	/// Sets the map type for this map image. 
	/// </summary>
	///
    /// <param name="mapType">
    /// An enumerated value as map type
    /// </param>
	///
    /// <returns> Returns Acad::eOk if a valid map type is passed in. </returns>
	///
    Acad::ErrorStatus			setMapType(AcGeoMapType mapType);

	/// <summary> 
	/// A flag to indicate whether the image is up to date.
	/// </summary>
	///
    /// <returns> Returns true if the last update failed. </returns>
	///
	///
	Adesk::Boolean				isOutOfDate() const;

	/// <summary> 
	/// Update the embeded image by re-capturing the live map
	/// Returns true if the last update failed
	/// </summary>
	///
    /// <param name="bReset">
    /// Input Boolean to indicate whether to recapture the image in optimal resolution to the screen.
	/// If true, the LOD will be recalculated and resolution will be reset to optimal
    /// </param>
    /// <returns>Returns true if successful.</returns>
	///
	Adesk::Boolean				updateMapImage(Adesk::Boolean bReset = Adesk::kFalse);

    // AcDbObject protocol
    Acad::ErrorStatus			dwgInFields(AcDbDwgFiler* pFiler) override;
    Acad::ErrorStatus			dwgOutFields(AcDbDwgFiler* pFiler) const override;
    Acad::ErrorStatus			dxfInFields(AcDbDxfFiler* pFiler) override;
    Acad::ErrorStatus			dxfOutFields(AcDbDxfFiler* pFiler) const override;
    Acad::ErrorStatus           subErase(Adesk::Boolean erasing) override;

	virtual Acad::ErrorStatus	applyPartialUndo(
									AcDbDwgFiler* undoFiler,
                                    AcRxClass*    classObj
									) override;

    // AcDbEntity protocol
    Acad::ErrorStatus			subGetOsnapPoints(
									AcDb::OsnapMode osnapMode, 
									Adesk::GsMarker gsSelectionMark, 
									const AcGePoint3d& pickPoint, 
									const AcGePoint3d& lastPoint, 
									const AcGeMatrix3d& viewXform, 
									AcGePoint3dArray& snapPoints, 
									AcDbIntArray& geomIds
									) const override;
    Acad::ErrorStatus			subGetGripPoints(
									AcDbGripDataPtrArray& grips, 
									const double curViewUnitSize, 
									const int gripSize, 
									const AcGeVector3d& curViewDir, 
									const int bitflags
									) const override;
    Acad::ErrorStatus			subGetGripPoints(
									AcGePoint3dArray& gripPoints, 
									AcDbIntArray& osnapModes, 
									AcDbIntArray& geomIds
									) const override;
	Acad::ErrorStatus			subMoveGripPointsAt(
									const AcDbVoidPtrArray& gripAppData, 
									const AcGeVector3d& offset, 
									const int bitflags
									) override;
    Acad::ErrorStatus			subTransformBy(const AcGeMatrix3d& xform) override;
    Acad::ErrorStatus           subIntersectWith(
                                    const AcDbEntity*   ent,
                                    AcDb::Intersect     intType,
                                    AcGePoint3dArray&   points,
                                    Adesk::GsMarker     thisGsMarker  = 0,
                                    Adesk::GsMarker     otherGsMarker = 0
                                    ) const override;

	Acad::ErrorStatus			subMoveGripPointsAt(
									const AcDbIntArray & indices, 
									const AcGeVector3d& offset
									) override;

    Acad::ErrorStatus           subIntersectWith(
                                    const AcDbEntity*   ent,
                                    AcDb::Intersect     intType,
                                    const AcGePlane&    projPlane,
                                    AcGePoint3dArray&   points,
                                    Adesk::GsMarker     thisGsMarker  = 0,
                                    Adesk::GsMarker     otherGsMarker = 0
                                    ) const override;

    // AcDbImage protocol
    AcGiSentScanLines*			getScanLines(const AcGiRequestScanLines& req) const override;
    Adesk::Boolean				freeScanLines(AcGiSentScanLines* pSSL) const override;

    // AcDbRasterImage protocol
    AcDbObjectId				imageDefId() const override;

	/// <summary> 
	/// Given an empty array, this function adds the image frame vertices to represent the four corners of the image.  
	/// </summary>
	///
    /// <param name="verts"> Returns a 3D point array of 4 corners </param>
	///
    Acad::ErrorStatus			getVertices(AcGePoint3dArray& verts) const override;
	// bGetCachedValue is required by override but has no effect
    AcGeVector2d				imageSize(Adesk::Boolean bGetCachedValue = Adesk::kFalse) const override;
    const AcGePoint2dArray&		clipBoundary() const override;

	/// <summary> 
	/// Given an empty array, this function adds the embeded image vertices to represent the four corners of the image.  
	/// </summary>
	///
    /// <param name="verts"> Returns a 3D point array of 4 corners </param>
	///
    Acad::ErrorStatus			getImageVertices(AcGePoint3dArray& verts) const;

    Acad::ErrorStatus			setBrightness( Adesk::Int8 value ) override;
	/// <summary> Returns the current brightness value of the image. </summary>
	///
    Adesk::Int8					brightness() const override;

    Acad::ErrorStatus			setContrast( Adesk::Int8 value ) override;
	/// <summary> Returns the current contrast value of the image. </summary>
	///
    Adesk::Int8					contrast() const override;

    Acad::ErrorStatus			setFade( Adesk::Int8 value ) override;
	/// <summary> Returns the current fade value of the image. </summary>
	///
    Adesk::Int8					fade() const override;

    void                        getOrientation(
									AcGePoint3d& origin,
									AcGeVector3d& u,
									AcGeVector3d& v
									) const override;

protected:
    // AcDbObject protocol
    Adesk::UInt32				subSetAttributes(AcGiDrawableTraits* pTraits) override;
    Adesk::Boolean				subWorldDraw(AcGiWorldDraw* pWorldDraw) override;
    void						subViewportDraw(AcGiViewportDraw* pViewportDraw) override;
    virtual void				subList() const override;

    // AcDbEntity protocol
    Acad::ErrorStatus			subGetGeomExtents(AcDbExtents& extents) const override;
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;

private:
    GeoMapImp*					m_pImp;

    friend class				AcDbGeoMapSystemInternals;


    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbRasterImage.
    // error C2248: 'AcDbRasterImage::operator delete[]' : cannot access private member declared in class 'AcDbRasterImage'
    void *operator new[](size_t nSize) { return (void*)0;}
    void operator delete[](void *p) {};
    void *operator new[](size_t nSize, const char *file, int line) { return (void*)0;}

#ifdef _ADESK_MAC_
private:
    typedef AcDbRasterImage __super;
#endif

};

#pragma warning(pop)
#pragma pack (pop)
