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
// 04/07/98: Alan Quinton: Creation
#ifndef _OPMDIALOG_H
#define _OPMDIALOG_H

/////////////////////////////////////////////////////////////////////
// IOPMPropertyDialog
/////////////////////////////////////////////////////////////////////
DEFINE_GUID(IID_IOPMPropertyDialog, 0x8B384029, 0xACB0, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384029-ACB0-11D1-A2B4-080009DC639A") IOPMPropertyDialog : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IOPMPropertyDialog methods ***
    STDMETHOD(DoModal)(THIS_ /*[in/out]*/ BSTR* propValueString, /*[in]*/AcDbObjectIdArray* ObjectIdArray) PURE;
};

typedef IOPMPropertyDialog FAR* LPPROPERTYDIALOG;

/////////////////////////////////////////////////////////////////////
// IOPMPropertyDialog2
/////////////////////////////////////////////////////////////////////
// {9F82F13D-C850-444a-980C-B5EDC6679F4A}
DEFINE_GUID(IID_IOPMPropertyDialog2, 0x9f82f13d, 0xc850, 0x444a, 0x98, 0xc, 0xb5, 0xed, 0xc6, 0x67, 0x9f, 0x4a);

interface DECLSPEC_UUID("9F82F13D-C850-444A-980C-B5EDC6679F4A")  IOPMPropertyDialog2 : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IOPMPropertyDialog2 methods ***
    STDMETHOD(DoModal)(THIS_ /*[in/out]*/ BSTR* propValueString, /*[in]*/VARIANT ObjectUnknownArray) PURE;
};

typedef IOPMPropertyDialog2 FAR* LPPROPERTYDIALOG2;

#endif //_OPMDIALOG_H
