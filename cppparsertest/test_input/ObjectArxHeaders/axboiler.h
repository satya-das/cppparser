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
//
// AXBOILER.H
//
// Interface declarations for the AutoCAD Automation API +
// common object/entity manipulation functions.
//

#ifndef __AXBOILER_H_
#define __AXBOILER_H_

#include "adesk.h"      // Adesk::IntDbId
#ifndef AXAUTOEXP
#ifdef AXAUTO_DLL
    #define AXAUTOEXP __declspec(dllexport)
#else
    #define AXAUTOEXP __declspec(dllimport)
#endif
#endif

#include "axobjref.h"

#ifdef _ADESK_WINDOWS_
DEFINE_GUID(IID_IAcadBaseObject, 
0x5f3c54c0, 0x49e1, 0x11cf, 0x93, 0xd5, 0x8, 0x0, 0x9, 0x9e, 0xb3, 0xb7);

/* Definition of interface: IAcadBaseObject */
#undef INTERFACE
#define INTERFACE IAcadBaseObject

interface DECLSPEC_UUID("5F3C54C0-49E1-11cf-93D5-0800099EB3B7") 
IAcadBaseObject : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcadBaseObject methods */
    STDMETHOD(SetObjectId)(THIS_ AcDbObjectId& objId, 
                           AcDbObjectId ownerId = AcDbObjectId::kNull, 
                           ACHAR* keyName = NULL) PURE;
    STDMETHOD(GetObjectId)(THIS_ AcDbObjectId* objId) PURE;
    STDMETHOD(Clone)(THIS_ AcDbObjectId ownerId, LPUNKNOWN* pUnkClone) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
    STDMETHOD(NullObjectId)(THIS) PURE;
    STDMETHOD(OnModified)(THIS) PURE;
};

typedef IAcadBaseObject* LPACADBASEOBJECT;

// {ADAAAEC4-C7FE-11d5-8D60-0010830243CE}
DEFINE_GUID(IID_IAcadBaseObject2,
0xadaaaec4, 0xc7fe, 0x11d5, 0x8d, 0x60, 0x0, 0x10, 0x83, 0x2, 0x43, 0xce);

/* Definition of interface: IAcadBaseObject2 */

interface DECLSPEC_UUID("ADAAAEC4-C7FE-11d5-8D60-0010830243CE") 
IAcadBaseObject2 : public IUnknown       
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcadBaseObject2 methods */
    STDMETHOD(ForceDbResident)(THIS_ VARIANT_BOOL* forceDbResident) PURE;
    STDMETHOD(AddToDb)(THIS_ AcDbObjectId& objId, 
                       AcDbObjectId ownerId = AcDbObjectId::kNull,
                       ACHAR* keyName = NULL) PURE;
    STDMETHOD(CreateObject)(THIS_ AcDbObjectId ownerId = AcDbObjectId::kNull,
                            ACHAR* keyName = NULL) PURE;
    STDMETHOD(ObjectExists)(THIS_ VARIANT_BOOL* objectExists) PURE;
    STDMETHOD(SetObject)(THIS_ AcDbObject*& pObj) PURE;
    STDMETHOD(GetObject)(THIS_ AcDbObject*& pObj) PURE;
    STDMETHOD(OnModified)(THIS_ DISPID = DISPID_UNKNOWN) PURE;
};

typedef IAcadBaseObject2* LPACADBASEOBJECT2;

DEFINE_GUID(IID_IRetrieveApplication, 
0x765b4640, 0x664a, 0x11cf, 0x93, 0xf3, 0x8, 0x0, 0x9, 0x9e, 0xb3, 0xb7);

/* Definition of interface: IRetrieveApplication */
interface DECLSPEC_UUID("765B4640-664A-11cf-93F3-0800099EB3B7") 
IRetrieveApplication : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IRetrieveApplication methods */
    STDMETHOD(SetApplicationObject)(THIS_ LPDISPATCH pAppDisp) PURE;
    STDMETHOD(GetApplicationObject)(THIS_ LPDISPATCH* pAppDisp) PURE;
};

typedef IRetrieveApplication* LPRETRIEVEAPPLICATION;

DEFINE_GUID(IID_IAcadBaseDatabase, 
0xcb1488c4, 0x2bec, 0x11d2, 0xb6, 0x7b, 0x0, 0x60, 0xb0, 0x87, 0xe2, 0x35);

/* Definition of interface: IAcadBaseDatabase */
interface DECLSPEC_UUID("CB1488C4-2BEC-11d2-B67B-0060B087E235") 
IAcadBaseDatabase : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcadBaseObject methods */
    STDMETHOD(SetDatabase)(THIS_ AcDbDatabase*& pDb) PURE;
    STDMETHOD(GetDatabase)(THIS_ AcDbDatabase** pDb) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
};

typedef IAcadBaseDatabase* LPACADBASEDATABASE;

DEFINE_GUID(IID_IIMetaColorSuppressor, 
0xbd1c37b2, 0x9020, 0x43ad, 0x99, 0xd4, 0x25, 0x91, 0x6a, 0x4b, 0xfb, 0xc);

/* Definition of interface: IMetaColorSuppressor */
interface DECLSPEC_UUID("BD1C37B2-9020-43ad-99D4-25916A4BFB0C")
IMetaColorSuppressor : public IUnknown
{
    /* IAcadAcCmColorAccess methods */
    STDMETHOD(GetSuppressor)(THIS_ bool* val) PURE;
    STDMETHOD(SetSuppressor)(THIS_ bool val) PURE;
};

typedef IMetaColorSuppressor* LPMETACOLORSUPPRESSOR;

DEFINE_GUID(IID_IAcadAcCmColorAccess,
0xf74f68db, 0x8f24, 0x4e74, 0xb1, 0x4d, 0x9b, 0xf4, 0xfe, 0x27, 0x7b, 0xd3);

/* Definition of interface: IAcadAcCmColorRetrieve */
#undef INTERFACE
#define INTERFACE IAcadAcCmColorAccess

interface DECLSPEC_UUID("F74F68DB-8F24-4e74-B14D-9BF4FE277BD3")
IAcadAcCmColorAccess : public IUnknown
{
    /* IAcadAcCmColorAccess methods */
    STDMETHOD(GetAcCmColor)(THIS_ AcCmColor* clr) PURE;
    STDMETHOD(SetAcCmColor)(THIS_ AcCmColor* clr) PURE;
};

typedef IAcadAcCmColorAccess* LPACADACCMCOLORACCESS;

/* Definition of interface: IAcadBaseSubEntity */
DEFINE_GUID(IID_IAcadBaseSubEntity, 
0xb374d885, 0xeece, 0x4138, 0x8c, 0x82, 0x3f, 0xb2, 0xc, 0x53, 0x87, 0x88);

#undef INTERFACE
#define INTERFACE IAcadBaseSubEntity

interface DECLSPEC_UUID("B374D885-EECE-4138-8C82-3FB20C538788") 
IAcadBaseSubEntity : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    /* IAcadBaseSubEntity methods */
    STDMETHOD(OnModified)() PURE;
    STDMETHOD(SetFullSubEntPath)(THIS_ AcDbFullSubentPath& subentPath) PURE; 
    STDMETHOD(GetFullSubEntPath)(THIS_ AcDbFullSubentPath* subentPath) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
};

typedef IAcadBaseSubEntity* LPACADSUBENTITY;

//
// Common object/entity helper functions
//
HRESULT AXAUTOEXP 
AcAxErase(AcDbObjectId& objId);

HRESULT AXAUTOEXP 
AcAxSetXData(AcDbObjectId& objId, VARIANT type, VARIANT data);

HRESULT AXAUTOEXP 
AcAxGetXData(AcDbObjectId& objId, BSTR bstrName, VARIANT* type, VARIANT* data);

HRESULT AXAUTOEXP 
AcAxGetObjectName(AcDbObjectId& objId, BSTR* pName);

HRESULT AXAUTOEXP 
AcAxGetHandle(AcDbObjectId& objId, BSTR* pHandle);

HRESULT AXAUTOEXP 
AcAxGetColor(AcDbObjectId& objId, AcColor* pColor);

HRESULT AXAUTOEXP 
AcAxPutColor(AcDbObjectId& objId, AcColor color);

HRESULT AXAUTOEXP
AcAxGetTrueColor(AcDbObjectId& objId, IAcadAcCmColor** pColor);

HRESULT AXAUTOEXP 
AcAxPutTrueColor(AcDbObjectId& objId, IAcadAcCmColor* color);

HRESULT AXAUTOEXP 
AcAxGetLayer(AcDbObjectId& objId, BSTR* pLayer);

HRESULT AXAUTOEXP 
AcAxPutLayer(AcDbObjectId& objId, BSTR layer);

HRESULT AXAUTOEXP 
AcAxGetLinetype(AcDbObjectId& objId, BSTR* pLinetype);

HRESULT AXAUTOEXP 
AcAxPutLinetype(AcDbObjectId& objId, BSTR linetype);

HRESULT AXAUTOEXP 
AcAxGetTransparency(AcDbObjectId& objId, BSTR* pTransparency);

HRESULT AXAUTOEXP 
AcAxPutTransparency(AcDbObjectId& objId, BSTR transparency);

HRESULT AXAUTOEXP 
AcAxGetShadowDisplay(AcDbObjectId& objId, AcShadowDisplayType* pShadowDisplay);

HRESULT AXAUTOEXP 
AcAxPutShadowDisplay(AcDbObjectId& objId, AcShadowDisplayType shadowDisplay);

HRESULT AXAUTOEXP 
AcAxEnableShadowDisplay(AcDbObjectId& objId, bool* pEnabled);

HRESULT AXAUTOEXP 
AcAxGetMaterial(AcDbObjectId& objId, BSTR* pMaterial);

HRESULT AXAUTOEXP 
AcAxPutMaterial(AcDbObjectId& objId, BSTR material);

HRESULT AXAUTOEXP 
AcAxGetLinetypeScale(AcDbObjectId& objId, double* pLinetypeScale);

HRESULT AXAUTOEXP 
AcAxPutLinetypeScale(AcDbObjectId& objId, double linetypeScale);

HRESULT AXAUTOEXP 
AcAxGetVisible(AcDbObjectId& objId, VARIANT_BOOL* pVisible);

HRESULT AXAUTOEXP 
AcAxPutVisible(AcDbObjectId& objId, VARIANT_BOOL visible);

HRESULT AXAUTOEXP 
AcAxArrayPolar(AcDbObjectId& objId, LPDISPATCH pAppDisp, int numObjs, 
               double fillAngle, VARIANT basePoint, VARIANT* pArrayObjs);

HRESULT AXAUTOEXP 
AcAxArrayRectangular(AcDbObjectId& objId, LPDISPATCH pAppDisp, int numRows, 
                     int numCols, int numLvls, double disRows, double disCols,
                     double disLvls, VARIANT* pArrayObjs);

HRESULT AXAUTOEXP 
AcAxHighlight(AcDbObjectId& objId, VARIANT_BOOL bHighlight);

HRESULT AXAUTOEXP 
AcAxCopy(AcDbObjectId& objId, LPDISPATCH pAppDisp, LPDISPATCH* pCopyObj, 
         AcDbObjectId ownerId = AcDbObjectId::kNull);

HRESULT AXAUTOEXP 
AcAxMove(AcDbObjectId& objId, VARIANT fromPoint, VARIANT toPoint);

HRESULT AXAUTOEXP 
AcAxRotate(AcDbObjectId& objId, VARIANT basePoint, double rotationAngle);

HRESULT AXAUTOEXP 
AcAxRotate3D(AcDbObjectId& objId, VARIANT point1, VARIANT point2, 
             double rotationAngle);

HRESULT AXAUTOEXP 
AcAxMirror(AcDbObjectId& objId, LPDISPATCH pAppDisp, VARIANT point1, 
           VARIANT point2, LPDISPATCH* pMirrorObj);

HRESULT AXAUTOEXP 
AcAxMirror3D(AcDbObjectId& objId, LPDISPATCH pAppDisp, VARIANT point1, 
             VARIANT point2, VARIANT point3, LPDISPATCH* pMirrorObj);

HRESULT AXAUTOEXP 
AcAxScaleEntity(AcDbObjectId& objId, VARIANT basePoint, double scaleFactor);

HRESULT AXAUTOEXP 
AcAxTransformBy(AcDbObjectId& objId, VARIANT transMatrix);

HRESULT AXAUTOEXP 
AcAxUpdate(AcDbObjectId& objId);

HRESULT AXAUTOEXP 
AcAxGetBoundingBox(AcDbObjectId& objId, VARIANT* minPoint, VARIANT* maxPoint);

HRESULT AXAUTOEXP 
AcAxIntersectWith(AcDbObjectId& objId, LPDISPATCH pEntity, 
                  AcExtendOption option, VARIANT* intPoints);

HRESULT AXAUTOEXP 
AcAxGetPlotStyleName(AcDbObjectId& objId, BSTR* plotStyleName);

HRESULT AXAUTOEXP 
AcAxPutPlotStyleName(AcDbObjectId& objId, BSTR plotStyleName);

HRESULT AXAUTOEXP 
AcAxGetLineWeight(AcDbObjectId& objId, ACAD_LWEIGHT* lineWeight);

HRESULT AXAUTOEXP 
AcAxPutLineWeight(AcDbObjectId& objId, ACAD_LWEIGHT lineWeight);

HRESULT AXAUTOEXP 
AcAxGetHyperlinks(AcDbObjectId& objId, LPDISPATCH pAppDisp, 
                  IAcadHyperlinks** pHyperlinks);

HRESULT AXAUTOEXP 
AcAxHasExtensionDictionary(AcDbObjectId& objId, VARIANT_BOOL* bHasDictionary);

HRESULT AXAUTOEXP 
AcAxGetExtensionDictionary(AcDbObjectId& objId, LPDISPATCH pAppDisp, 
                           IAcadDictionary** pExtDictionary);

HRESULT AXAUTOEXP 
AcAxGetDatabase(AcDbDatabase* pDb, LPDISPATCH pAppDisp, LPDISPATCH* pDisp);

HRESULT AXAUTOEXP
AcAxGetOwnerId(AcDbObjectId& objId, Adesk::IntDbId * pOwnerId); 

#if defined(_WIN64) || defined(_AC64)
Adesk::Int32 AXAUTOEXP
AcAxGetObjectId32(const Adesk::IntDbId& objId); 

Adesk::IntDbId AXAUTOEXP
AcAxGetObjectId64(const Adesk::Int32& objId);  
#endif

//
// Utility functions
//
HRESULT AXAUTOEXP
RaiseAcAXException(REFGUID iid, HRESULT hRes, DWORD dwException, ...);

HRESULT  AXAUTOEXP
RaiseArxException(REFGUID iid, HRESULT hRes, Acad::ErrorStatus es);

HRESULT AXAUTOEXP
AcAxGetIUnknownOfObject(LPUNKNOWN* ppUnk, AcDbObjectId& objId, LPDISPATCH pApp);

HRESULT AXAUTOEXP
AcAxGetIUnknownOfObject(LPUNKNOWN* ppUnk, AcDbObject* pObj, LPDISPATCH pApp);

//
// Common object/entity helper functions using abstract AcAxObjectRef 
// instead of AcDbObjectId. Not all methods support non-database resident
// objects and return error codes when called on objects without ObjectIds.
//
HRESULT AXAUTOEXP 
AcAxErase(AcAxObjectRef& objRef);

HRESULT AXAUTOEXP 
AcAxSetXData(AcAxObjectRef& objRef, VARIANT type, VARIANT data);

HRESULT AXAUTOEXP 
AcAxGetXData(AcAxObjectRef& objRef, BSTR bstrName, VARIANT* type, VARIANT* data);

HRESULT AXAUTOEXP 
AcAxGetObjectName(AcAxObjectRef& objRef, BSTR* pName);

HRESULT AXAUTOEXP 
AcAxGetHandle(AcAxObjectRef& objRef, BSTR* pHandle);

HRESULT AXAUTOEXP 
AcAxGetColor(AcAxObjectRef& objRef, AcColor* pColor);

HRESULT AXAUTOEXP 
AcAxPutColor(AcAxObjectRef& objRef, AcColor color);

HRESULT AXAUTOEXP
AcAxGetTrueColor(AcAxObjectRef& objRef, IAcadAcCmColor** pColor); 
                                                                  
HRESULT AXAUTOEXP                                                 
AcAxPutTrueColor(AcAxObjectRef& objRef, IAcadAcCmColor* color);   

HRESULT AXAUTOEXP 
AcAxGetLayer(AcAxObjectRef& objRef, BSTR* pLayer);

HRESULT AXAUTOEXP 
AcAxPutLayer(AcAxObjectRef& objRef, BSTR layer);

HRESULT AXAUTOEXP 
AcAxGetLinetype(AcAxObjectRef& objRef, BSTR* pLinetype);

HRESULT AXAUTOEXP 
AcAxPutLinetype(AcAxObjectRef& objRef, BSTR linetype);

HRESULT AXAUTOEXP 
AcAxGetTransparency(AcAxObjectRef& objRef, BSTR* pTransparency);

HRESULT AXAUTOEXP 
AcAxPutTransparency(AcAxObjectRef& objRef, BSTR transparency);

HRESULT AXAUTOEXP 
AcAxGetMaterial(AcAxObjectRef& objRef, BSTR* pMaterial);

HRESULT AXAUTOEXP 
AcAxPutMaterial(AcAxObjectRef& objRef, BSTR material);

HRESULT AXAUTOEXP 
AcAxGetLinetypeScale(AcAxObjectRef& objRef, double* pLinetypeScale);

HRESULT AXAUTOEXP 
AcAxPutLinetypeScale(AcAxObjectRef& objRef, double linetypeScale);

HRESULT AXAUTOEXP 
AcAxGetShadowDisplay(AcAxObjectRef& objRef, AcShadowDisplayType* pShadowDisplay);

HRESULT AXAUTOEXP 
AcAxPutShadowDisplay(AcAxObjectRef& objRef, AcShadowDisplayType shadowDisplay);

HRESULT AXAUTOEXP 
AcAxEnableShadowDisplay(AcAxObjectRef& objRef, bool* pEnabled);

HRESULT AXAUTOEXP 
AcAxGetVisible(AcAxObjectRef& objRef, VARIANT_BOOL* pVisible);

HRESULT AXAUTOEXP 
AcAxPutVisible(AcAxObjectRef& objRef, VARIANT_BOOL visible);

HRESULT AXAUTOEXP 
AcAxArrayPolar(AcAxObjectRef& objRef, LPDISPATCH pAppDisp, int numObjs, 
               double fillAngle, VARIANT basePoint, VARIANT* pArrayObjs);

HRESULT AXAUTOEXP 
AcAxArrayRectangular(AcAxObjectRef& objRef, LPDISPATCH pAppDisp, int numRows, 
                     int numCols, int numLvls, double disRows, double disCols,
                     double disLvls, VARIANT* pArrayObjs);

HRESULT AXAUTOEXP 
AcAxHighlight(AcAxObjectRef& objRef, VARIANT_BOOL bHighlight);

HRESULT AXAUTOEXP 
AcAxCopy(AcAxObjectRef& objRef, LPDISPATCH pAppDisp, LPDISPATCH* pCopyObj, 
         AcDbObjectId ownerId = AcDbObjectId::kNull);
HRESULT AXAUTOEXP 
AcAxMove(AcAxObjectRef& objRef, VARIANT fromPoint, VARIANT toPoint);

HRESULT AXAUTOEXP 
AcAxRotate(AcAxObjectRef& objRef, VARIANT basePoint, double rotationAngle);

HRESULT AXAUTOEXP 
AcAxRotate3D(AcAxObjectRef& objRef, VARIANT point1, VARIANT point2, 
             double rotationAngle);

HRESULT AXAUTOEXP 
AcAxMirror(AcAxObjectRef& objRef, LPDISPATCH pAppDisp, VARIANT point1, 
           VARIANT point2, LPDISPATCH* pMirrorObj);

HRESULT AXAUTOEXP 
AcAxMirror3D(AcAxObjectRef& objRef, LPDISPATCH pAppDisp, VARIANT point1, 
             VARIANT point2, VARIANT point3, LPDISPATCH* pMirrorObj);

HRESULT AXAUTOEXP 
AcAxScaleEntity(AcAxObjectRef& objRef, VARIANT basePoint, double scaleFactor);

HRESULT AXAUTOEXP 
AcAxTransformBy(AcAxObjectRef& objRef, VARIANT transMatrix);

HRESULT AXAUTOEXP 
AcAxUpdate(AcAxObjectRef& objRef);

HRESULT AXAUTOEXP 
AcAxGetBoundingBox(AcAxObjectRef& objRef, VARIANT* minPoint, VARIANT* maxPoint);

HRESULT AXAUTOEXP 
AcAxIntersectWith(AcAxObjectRef& objRef, LPDISPATCH pEntity, 
                  AcExtendOption option, VARIANT* intPoints);

HRESULT AXAUTOEXP 
AcAxGetPlotStyleName(AcAxObjectRef& objRef, BSTR* plotStyleName);

HRESULT AXAUTOEXP 
AcAxPutPlotStyleName(AcAxObjectRef& objRef, BSTR plotStyleName);

HRESULT AXAUTOEXP 
AcAxGetLineWeight(AcAxObjectRef& objRef, ACAD_LWEIGHT* lineWeight);

HRESULT AXAUTOEXP 
AcAxPutLineWeight(AcAxObjectRef& objRef, ACAD_LWEIGHT lineWeight);

HRESULT AXAUTOEXP 
AcAxGetHyperlinks(AcAxObjectRef& objRef, LPDISPATCH pAppDisp, 
                  IAcadHyperlinks** pHyperlinks);

HRESULT AXAUTOEXP 
AcAxHasExtensionDictionary(AcAxObjectRef& objRef, VARIANT_BOOL* bHasDictionary);

HRESULT AXAUTOEXP 
AcAxGetExtensionDictionary(AcAxObjectRef& objRef, LPDISPATCH pAppDisp, 
                           IAcadDictionary** pExtDictionary);
HRESULT AXAUTOEXP
AcAxGetOwnerId(AcAxObjectRef& objRef, Adesk::IntDbId * pOwnerId); 

HRESULT AXAUTOEXP
AcAxGet_UIsolineDensity(AcDbObjectId& objId, long* density);

HRESULT AXAUTOEXP
AcAxPut_UIsolineDensity(AcDbObjectId& objId, long density);

HRESULT AXAUTOEXP
AcAxGet_VIsolineDensity(AcDbObjectId& objId, long* density);

HRESULT AXAUTOEXP
AcAxPut_VIsolineDensity(AcDbObjectId& objId, long density);

HRESULT AXAUTOEXP
AcAxGet_WireframeType(AcDbObjectId& objId, AcWireframeType *type);

HRESULT AXAUTOEXP
AcAxPut_WireframeType(AcDbObjectId& objId, AcWireframeType type);

HRESULT AXAUTOEXP
AcAxGetMaintainAssociativity(AcDbObjectId& objId, int *maintainAssoc);

HRESULT AXAUTOEXP
AcAxPutMaintainAssociativity(AcDbObjectId& objId, int maintainAssoc);

HRESULT AXAUTOEXP
AcAxGetShowAssociativity(AcDbObjectId& objId, VARIANT_BOOL* bEnabled);

HRESULT AXAUTOEXP
AcAxPutShowAssociativity(AcDbObjectId& objId, VARIANT_BOOL bEnabled);

HRESULT AXAUTOEXP
AcAxGetEdgeExtensionDistances(AcDbObjectId& objId, VARIANT *extDistances);

HRESULT AXAUTOEXP
AcAxPutEdgeExtensionDistances(AcDbObjectId& objId, VARIANT extDistances);

HRESULT AXAUTOEXP
AcAxGetSurfTrimAssociativity(AcDbObjectId& objId, VARIANT *associative);

HRESULT AXAUTOEXP
AcAxPutSurfTrimAssociativity(AcDbObjectId& objId, VARIANT associative);

#else

DEFINE_GUID(IID_IAcadBaseObject, 
            0x5f3c54c0, 0x49e1, 0x11cf, 0x93, 0xd5, 0x8, 0x0, 0x9, 0x9e, 0xb3, 0xb7);

/* Definition of interface: IAcadBaseObject */
#undef INTERFACE
#define INTERFACE IAcadBaseObject

//interface DECLSPEC_UUID("5F3C54C0-49E1-11cf-93D5-0800099EB3B7") 
interface IAcadBaseObject : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    
    /* IAcadBaseObject methods */
    STDMETHOD(SetObjectId)(THIS_ AcDbObjectId& objId, 
                           AcDbObjectId ownerId = AcDbObjectId::kNull, 
                           ACHAR* keyName = NULL) PURE;
    STDMETHOD(GetObjectId)(THIS_ AcDbObjectId* objId) PURE;
    STDMETHOD(Clone)(THIS_ AcDbObjectId ownerId, LPUNKNOWN* pUnkClone) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
    STDMETHOD(NullObjectId)(THIS) PURE;
    STDMETHOD(OnModified)(THIS) PURE;
};

typedef IAcadBaseObject* LPACADBASEOBJECT;


// {ADAAAEC4-C7FE-11d5-8D60-0010830243CE}
DEFINE_GUID(IID_IAcadBaseObject2,
            0xadaaaec4, 0xc7fe, 0x11d5, 0x8d, 0x60, 0x0, 0x10, 0x83, 0x2, 0x43, 0xce);

/* Definition of interface: IAcadBaseObject2 */

//interface DECLSPEC_UUID("ADAAAEC4-C7FE-11d5-8D60-0010830243CE") 
interface IAcadBaseObject2 : public IUnknown       
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    
    /* IAcadBaseObject2 methods */
    STDMETHOD(ForceDbResident)(THIS_ VARIANT_BOOL* forceDbResident) PURE;
    STDMETHOD(AddToDb)(THIS_ AcDbObjectId& objId, 
                       AcDbObjectId ownerId = AcDbObjectId::kNull,
                       ACHAR* keyName = NULL) PURE;
    STDMETHOD(CreateObject)(THIS_ AcDbObjectId ownerId = AcDbObjectId::kNull,
                            ACHAR* keyName = NULL) PURE;
    STDMETHOD(ObjectExists)(THIS_ VARIANT_BOOL* objectExists) PURE;
    STDMETHOD(SetObject)(THIS_ AcDbObject*& pObj) PURE;
    STDMETHOD(GetObject)(THIS_ AcDbObject*& pObj) PURE;
    STDMETHOD(OnModified)(THIS_ DISPID = DISPID_UNKNOWN) PURE;
};

typedef IAcadBaseObject2* LPACADBASEOBJECT2;

DEFINE_GUID(IID_IAcadBaseDatabase, 
            0xcb1488c4, 0x2bec, 0x11d2, 0xb6, 0x7b, 0x0, 0x60, 0xb0, 0x87, 0xe2, 0x35);

/* Definition of interface: IAcadBaseDatabase */
// interface DECLSPEC_UUID("CB1488C4-2BEC-11d2-B67B-0060B087E235") 
interface IAcadBaseDatabase : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;
    
    /* IAcadBaseObject methods */
    STDMETHOD(SetDatabase)(THIS_ AcDbDatabase*& pDb) PURE;
    STDMETHOD(GetDatabase)(THIS_ AcDbDatabase** pDb) PURE;
    STDMETHOD(GetClassID)(THIS_ CLSID& clsid) PURE;
};

typedef IAcadBaseDatabase* LPACADBASEDATABASE;

// Common object/entity helper functions are found in axdbUtilities for
// the Mac product

#endif // _ADESK_WINDOWS_

#endif
