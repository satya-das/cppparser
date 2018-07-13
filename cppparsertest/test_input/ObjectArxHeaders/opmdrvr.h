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
#ifndef _OPMDRVR_H
#define _OPMDRVR_H

// ICategorizeProperties methods
HRESULT AXAUTOEXP AcOpmMapPropertyToCategory(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispid, PROPCAT* ppropcat);
HRESULT AXAUTOEXP AcOpmGetCategoryName(IUnknown* pUnk, HINSTANCE hResInstance, ACAD_OPMPROPMAP_ENTRY* pMap, PROPCAT propcat, LCID lcid, BSTR* pbstrName);

// IAcPiCategorizeProperties methods
HRESULT AXAUTOEXP AcOpmGetCategoryName(IUnknown* pUnk, HINSTANCE hResInstance, CATEGORY_VECTOR & arr, PROPCAT propcat, LCID lcid, BSTR* pbstrName);
HRESULT AXAUTOEXP AcOpmGetCategoryCommandButtons(IUnknown *pUnk, HINSTANCE hResInstance, CATCMDBTN_VECTOR & arr, PROPCAT propcat, VARIANT *pCatCmdBtns);
HRESULT AXAUTOEXP AcOpmGetParentCategory(IUnknown *pUnk, CATEGORY_VECTOR & arr, PROPCAT propcat, PROPCAT *pParentCatID);
HRESULT AXAUTOEXP AcOpmGetCategoryWeight(IUnknown *pUnk, CATEGORY_VECTOR & arr, PROPCAT propcat, long *pCategoryWeight);
HRESULT AXAUTOEXP AcOpmGetCategoryDescription(IUnknown *pUnk, HINSTANCE hResInstance, CATEGORY_VECTOR & arr, PROPCAT propcat, LCID lcid, BSTR* pbstrDesc);

// IPerPropertyBrowsing methods
HRESULT AXAUTOEXP AcOpmGetDisplayString(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BSTR *pBstr);
HRESULT AXAUTOEXP AcOpmMapPropertyToPage(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, CLSID *pClsid);
HRESULT AXAUTOEXP AcOpmGetPredefinedStrings(IUnknown* pUnk, HINSTANCE hResInstance, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, CALPOLESTR *pCaStringsOut, CADWORD *pCaCookiesOut);
HRESULT AXAUTOEXP AcOpmGetPredefinedValue(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, DWORD dwCookie, VARIANT *pVarOut);
 
 // IOPMPropertyExtension methods
HRESULT AXAUTOEXP AcOpmGetDisplayName(IUnknown* pUnk, HINSTANCE hResInstance, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BSTR *pBstr);
HRESULT AXAUTOEXP AcOpmEditable(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BOOL __RPC_FAR *bEditable);
HRESULT AXAUTOEXP AcOpmShowProperty(IUnknown* pUnk, ACAD_OPMPROPMAP_ENTRY* pMap, DISPID dispID, BOOL *pShow);

 // IAcPiPropertyDisplay methods
HRESULT AXAUTOEXP AcOpmGetPropertyWeight(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, long *pPropertyWeight);
HRESULT AXAUTOEXP AcOpmIsPropFullView(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, VARIANT_BOOL *pbVisible, DWORD *pIntegralHeight);
HRESULT AXAUTOEXP AcOpmGetPropTextColor(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, OLE_COLOR *pTextColor);
HRESULT AXAUTOEXP AcOpmGetPropertyIcon(IUnknown *pUnk, HINSTANCE hResInstance, PROP_DISP_VECTOR & arr, VARIANT Id, IUnknown **ppIcon);
HRESULT AXAUTOEXP AcOpmGetCustomPropertyCtrl(IUnknown *pUnk, PROP_DISP_VECTOR & arr, VARIANT Id, LCID lcid, BSTR *psProdId);

// IAcPiPropCommandButtons methods
HRESULT AXAUTOEXP AcOpmGetCommandButtons(IUnknown *pUnk, HINSTANCE hResInstance, CMDBTN_VECTOR & arr, VARIANT *pCmdBtns);

#endif // _OPMDRVR_H
