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
#ifndef _OPMEXT_H
#define _OPMEXT_H
#pragma pack (push, 8)

typedef struct  tagOPMLPOLESTR
    {
    ULONG cElems;
    /* [size_is] */ LPOLESTR __RPC_FAR *pElems;
    }	OPMLPOLESTR;

typedef struct tagOPMLPOLESTR __RPC_FAR *LPOPMLPOLESTR;

typedef struct  tagOPMDWORD
    {
    ULONG cElems;
    /* [size_is] */ DWORD __RPC_FAR *pElems;
    }	OPMDWORD;

typedef struct tagOPMDWORD __RPC_FAR *LPOPMDWORD;

// {1236EAA4-7715-11d1-A2DA-0060B06B2D46}
DEFINE_GUID(IID_IOPMPropertyExtension, 
0x1236eaa4, 0x7715, 0x11d1, 0xa2, 0xda, 0x0, 0x60, 0xb0, 0x6b, 0x2d, 0x46);
  
interface DECLSPEC_UUID("1236EAA4-7715-11d1-A2DA-0060B06B2D46") IOPMPropertyExtension : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //Implement this function to override the name of the property
    virtual HRESULT STDMETHODCALLTYPE GetDisplayName(
        /* [in] */ DISPID dispID,
        /* [out] */ BSTR * propName) = 0;

    //Override to make property read-only
    virtual HRESULT STDMETHODCALLTYPE Editable( 
        /* [in] */ DISPID dispID,
        /* [out] */ BOOL __RPC_FAR *bEditable) = 0;

    //Override to hide the property from display
    virtual HRESULT STDMETHODCALLTYPE ShowProperty(
        /* [in] */ DISPID dispID, 
        /* [out] */ BOOL *pShow) = 0;
};


// {5D535710-D49A-11d1-B616-0060B087E235}
DEFINE_GUID(IID_IOPMPropertyExpander, 
0x5d535710, 0xd49a, 0x11d1, 0xb6, 0x16, 0x0, 0x60, 0xb0, 0x87, 0xe2, 0x35);

interface DECLSPEC_UUID("5D535710-D49A-11d1-B616-0060B087E235") IOPMPropertyExpander : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetElementValue(
        /* [in] */ DISPID dispID,
        /* [in] */ DWORD dwCookie,
        /* [out] */ VARIANT * pVarOut) = 0;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE SetElementValue(
        /* [in] */ DISPID dispID,
        /* [in] */ DWORD dwCookie,
        /* [in] */ VARIANT VarIn) = 0;       

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetElementStrings( 
        /* [in] */ DISPID dispID,
        /* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
        /* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut) = 0;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetElementGrouping(
        /* [in] */ DISPID dispID,
        /* [out] */ short *groupingNumber) = 0;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetGroupCount(
        /* [in] */ DISPID dispID,
        /* [out] */ long *nGroupCnt) = 0;
};

// {D0F45FEB-71D5-44ea-B1A0-6E2F27B2085D}
DEFINE_GUID(IID_IOPMPropertyExpander2, 
0xd0f45feb, 0x71d5, 0x44ea, 0xb1, 0xa0, 0x6e, 0x2f, 0x27, 0xb2, 0x8, 0x5d);
interface DECLSPEC_UUID("d0f45feb-71d5-44ea-B1A0-6E2F27B2085D") IOPMPropertyExpander2 : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetElementValue(
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [in] */ DWORD dwCookie,
        /* [out] */ VARIANT * pVarOut) = 0;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE SetElementValue(
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [in] */ DWORD dwCookie,
        /* [in] */ VARIANT VarIn) = 0;       

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetElementStrings( 
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [out] */ OPMLPOLESTR __RPC_FAR *pCaStringsOut,
        /* [out] */ OPMDWORD __RPC_FAR *pCaCookiesOut) = 0;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetElementGrouping(
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [out] */ short *groupingNumber) = 0;

    //Used for property expansion (currently variant types)
    virtual HRESULT STDMETHODCALLTYPE GetGroupCount(
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [out] */ long *nGroupCnt) = 0;
};

// {4197114D-3CC4-413b-8AA3-7C7A05B62D3F}
DEFINE_GUID(IID_IOPMPropertyExpanderExpression, 
0x4197114d, 0x3cc4, 0x413b, 0x8a, 0xa3, 0x7c, 0x7a, 0x5, 0xb6, 0x2d, 0x3f);

interface DECLSPEC_UUID("4197114D-3CC4-413b-8AA3-7C7A05B62D3F") IOPMPropertyExpanderExpression : public IUnknown
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    virtual HRESULT STDMETHODCALLTYPE ExpressionAllowed(
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [in] */ DWORD dwCookie,
        /* [out] */ BOOL* pAllowed) = 0;

    virtual HRESULT STDMETHODCALLTYPE put_Expression(
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [in] */ DWORD dwCookie,
        /* [in] */ BSTR expression) = 0;

    virtual HRESULT STDMETHODCALLTYPE get_Expression(
        /* [in] */ DISPID dispID,
        /* [in] */ IUnknown * pUnk,
        /* [in] */ DWORD dwCookie,
        /* [out] */ BSTR* expression) = 0;
};

#pragma pack (pop)
#endif /* _OPMEXT_H */

