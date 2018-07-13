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

#ifndef _DYNPROPS_H
#define _DYNPROPS_H
#include "adesk.h"
#include "AdAChar.h"
#include "acdbport.h"
#include "dynprops-AcFilterablePropertyContext.h"

#ifdef _ADESK_WINDOWS_
// Notify caller that dynamic property change should notify command in progress
#define S_NOTIFYCMD MAKE_HRESULT(0,0,0x02)

interface IPropertyManager;
interface IDynamicProperty;
interface IPropertyManager2;
interface IDynamicProperty2;
interface IPropertySource;
//--------------------------
// OPMPerInstancePropertySources interface
// This class is implemented by AutoCAD and available through
// GET_OPM_PERINSTANCE_PROPERTY_SOURCES(). Once you have the OPMPerInstancePropertySource*
// you can either add your own property source via SetPropertySouceAt/AddObjectPropertySourceAt
// or use existing sources via GetPropertySourceAt/GetObjectPropertySourceAt.
//--------------------------
class OPMPerInstancePropertySources : public AcRxObject  
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(OPMPerInstancePropertySources, ACDB_PORT);
    virtual ~OPMPerInstancePropertySources(){}
    
    // Add a property source into the global name->source table
    virtual bool SetPropertySourceAt(const BSTR* pName, IPropertySource* pSource) = 0;
    // Get a property source from the global name->source table.
    // This is a real COM object so the pointer should be released
    // when it is no longer needed
    virtual IPropertySource* GetPropertySourceAt(const BSTR* pName) = 0;
    // Removes a property source from the global name->source table
    virtual bool RemovePropertySourceAt(const BSTR* pName) = 0;
    // Returns an array of property source names as a SafeArray of BSTRs.
    // Returned variant may be VT_EMPTY if no sources are defined. 
    virtual bool GetPropertySourceNames(VARIANT* pNames) = 0;
    
};

//--------------------------
// OPMPerInstancePropertyExtension interface
// This class is implemented by AutoCAD and available through
// GET_OPM_PERINSTANCE_EXTENSION_PROTOCOL(). Once you have the OPMPerInstancePropertyExtension*
// you can either add or remove property source names from the extension. 
//--------------------------
class OPMPerInstancePropertyExtension : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(OPMPerInstancePropertyExtension, ACDB_PORT);
    virtual ~OPMPerInstancePropertyExtension() {};
    // Adds a property source name 
    virtual bool AddObjectPropertySourceName(const BSTR* pName) = 0;
    // Removes a property source name
    virtual bool RemoveObjectPropertySourceName(const BSTR* pName) = 0;
    // Retrieves the property source names stored on the extension object. 
    // Returned variant may be VT_EMPTY if no sources are defined.
    virtual bool GetObjectPropertySourceNames(VARIANT* pNames) = 0;
};

//--------------------------
// OPMPerInstancePropertyExtensionFactory interface
// This class is implemented by AutoCAD and available through
// GET_OPM_PERINSTANCE_CREATE_PROTOCOL(). Once you have the OPMPerInstancePropertyExtensionFactory*
// you can access property instance extension objects by class name. 
//--------------------------
class OPMPerInstancePropertyExtensionFactory : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(OPMPerInstancePropertyExtensionFactory, ACDB_PORT);
    virtual ~OPMPerInstancePropertyExtensionFactory(){};
    // Retrieves the OPMPerInstancePropertyExtension instance per class. If the 
    // extension has not been added it creates it. Note that the factory manages
    // the lifetime of the extension object, so callers should not delete the memory
    // referenced by the returned pointer.
    virtual OPMPerInstancePropertyExtension* CreateOPMPerInstancePropertyExtension(AcRxClass* pClass) = 0;
};

// This macro returns a pointer to the global OPMPerInstancePropertyExtensionFactory.
#define GET_OPM_PERINSTANCE_CREATE_PROTOCOL() \
OPMPerInstancePropertyExtensionFactory::cast(AcDbDatabase::desc()->queryX(OPMPerInstancePropertyExtensionFactory::desc()))

// This macro returns a pointer to the global OPMPerInstancePropertySources object.
#define GET_OPM_PERINSTANCE_PROPERTY_SOURCES() \
OPMPerInstancePropertySources::cast(AcDbDatabase::desc()->queryX(OPMPerInstancePropertySources::desc()))

//This macro is the main entry point for getting the per instance property extension
//for a particular class. 
#define GET_OPM_PERINSTANCE_EXTENSION_PROTOCOL(pAcRxClass) \
GET_OPM_PERINSTANCE_CREATE_PROTOCOL()->CreateOPMPerInstancePropertyExtension(pAcRxClass)

//--------------------------
// OPMPropertyExtension interface
// This class is implemented by AutoCAD and available through
// GET_OPMEXTENSION_PROTOCOL(). Once you have the OPMPropertyExtension*
// you can either add your own property manager via SetPropertyManager
// or use the one provided by us via GetPropertyManager 
//--------------------------
class OPMPropertyExtension : public AcRxObject  
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(OPMPropertyExtension, ACDB_PORT);
    virtual ~OPMPropertyExtension(){}
    //Get the property manager for this extension, if one is not
    //available, it will be created. This is a real COM object so
    //you will need to release the IPropertyManager* when you 
    //are done with it.
    virtual IPropertyManager* GetPropertyManager() = 0;
    //This function allows you to provide your own property manager
    virtual void SetPropertyManager(IPropertyManager* pPropManager) = 0;
};


//--------------------------
// OPMPropertyExtension interface
// This class is implemented by AutoCAD and available through
// GET_OPMEXTENSION_CREATE_PROTOCOL. You can add property classes 
// by calling GET_OPMPROPERTY_MANAGER for a particular AcRxClass 
// to get the property manager for that class. 
// You can also enumerate the dynamic properties which have
// been added to that class as well as its base class(es) via 
// GetPropertyCount and GetPropertyClassArray
//--------------------------
class OPMPropertyExtensionFactory: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(OPMPropertyExtensionFactory, ACDB_PORT);
    virtual ~OPMPropertyExtensionFactory(){}

    //Retrieves the OPMPropertyExtension for the specified class, if the
    //extension has not been added before, it creates it. Note: the implementation
    //of this class manages the lifetime of OPMPropertyExtension, as such you don't 
    //need to delete them.
    virtual OPMPropertyExtension* CreateOPMObjectProtocol(AcRxClass* pClass, 
                                                             LONG lReserved = 0) = 0;
    
    virtual OPMPropertyExtension* CreateOPMCommandProtocol(const ACHAR * pGlobalCommand, 
                                                             LONG lReserved = 0) = 0;
    
    //gets the property manager for a particular command that been registered
    //with CreateOPMCommandProtocol. Returns TRUE if successful, FALSE if no
    //no manager for that command exists.
    virtual BOOL GetOPMManager(const ACHAR * pGlobalCommand, IPropertyManager** pManager) = 0;
    //Retrieves the total number of IDynamicProperty classes that have been
    //added to this class, including properties which have been added to 
    //base classes.
    virtual BOOL GetPropertyCount(AcRxClass* pClass, LONG* pPropCount) = 0;
    //Fills an array of CALLER ALLOCATED IDynamicPropety*s. The return value 
    //indicates the number of IDynamicProperty pointers actually written to 
    //the array. This *should* be the same as the value returned by 
    //GetPropertyCount
    virtual LONG GetPropertyClassArray(AcRxClass* pClass, 
                                       IDynamicProperty**  pPropertyArray) = 0; 
    //Retrieves the total number of IDynamicProperty*s (i.e cumulative count of 
    //total number of IDynamicProperty*s & IDynamicProperty2*s) classes that have been
    //added to this class, including properties which have been added to 
    //base classes.
    virtual BOOL GetPropertyCountEx(AcRxClass* pClass, LONG* pPropCount) = 0;
    //Fills an array of CALLER ALLOCATED IUnknown*s. The return value 
    //indicates the number of IUnknown*s (from which either IDynamicProperty 
    //or IDynamicProperty2 can be queried) pointers actually written to 
    //the array. This *should* be the same as the value returned by 
    //GetPropertyCount
    virtual LONG GetPropertyClassArray(AcRxClass* pClass, 
                                       IUnknown**  pPropertyArray) = 0; 
};

#define GET_OPMEXTENSION_CREATE_PROTOCOL() \
OPMPropertyExtensionFactory::cast(AcDbDatabase::desc()->queryX(OPMPropertyExtensionFactory::desc()))

//This macro is the main entry point for getting the property manager for a
//particular class. Note: This returns an IPropertyManager for the class which 
//must be released after it's used
#define GET_OPMPROPERTY_MANAGER(pAcRxClass) \
GET_OPMEXTENSION_CREATE_PROTOCOL()->CreateOPMObjectProtocol(pAcRxClass)->GetPropertyManager() 

//This macro allocates an OPMPropertyExtension and returns its property
//manager for a given global command name. Use it to register commands
//which wish to provide dynamic properties for the OPM.
//Note: This returns an IPropertyManager for the class which 
//must be released after it's used
#define GET_OPM_COMMAND_PROPERTY_MANAGER(pCommandName) \
GET_OPMEXTENSION_CREATE_PROTOCOL()->CreateOPMCommandProtocol(pCommandName)->GetPropertyManager() 

typedef BOOL (*OPMDIALOGPROC)(void);

const int MAX_OPMSTRLEN = 256;

DEFINE_GUID(IID_IDynamicPropertyNotify, 0x8B384028, 0xACA8, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA8-11d1-A2B4-080009DC639A")
IDynamicPropertyNotify : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicPropertyNotify methods ***
    
    // Call this when your property changes
    STDMETHOD(OnChanged)(THIS_ /*[in]*/IDynamicProperty* pDynamicProperty) PURE;
    // Call to get the current selection set OPM is working with, returns a SAFEARRAY 
    // of LONGs representing the objectIDs of the set, be sure to call VariantClear to cleanup
    STDMETHOD(GetCurrentSelectionSet)(THIS_ /*[out*/VARIANT* pSelection) PURE;
};

typedef IDynamicPropertyNotify FAR* LPDYNAMICPROPERTYNOTIFY;

DEFINE_GUID(IID_IDynamicPropertyNotify2, 0x975112b5, 0x5403, 0x4197, 0xaf, 0xb8, 0x90, 0xc6, 0xca, 0x73, 0xb9, 0xe1);

interface DECLSPEC_UUID("975112B5-5403-4197-AFB8-90C6CA73B9E1")
IDynamicPropertyNotify2 : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicPropertyNotify2 methods ***
    
    // Call this when your property changes
    // Either IDynamicProperty or IDynamicProperty2 will be queried from
    // the IUnknown pointer supplied.
    STDMETHOD(OnChanged)(THIS_ /*[in]*/IUnknown* pDynamicProperty) PURE;
    // Call to get the current selection set OPM is working with, returns a SAFEARRAY 
    // of IUnknowns representing the objects of the set, be sure to call VariantClear to cleanup
    STDMETHOD(GetCurrentSelectionSet)(THIS_ /*[out*/VARIANT* pSelection) PURE;
};

typedef IDynamicPropertyNotify2 FAR* LPDYNAMICPROPERTYNOTIFY2;

//--------------------------
// IDynamicProperty interface
// Implement this class to create dynamic properties for the OPM
// it defines the base set of property attributes as well as
// the name/type/data tuples. 
//--------------------------
// {8B384028-ACA9-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IDynamicProperty, 0x8B384028, 0xACA9, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA9-11d1-A2B4-080009DC639A")
IDynamicProperty : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicProperty methods ***
    //Unique property ID
    STDMETHOD(GetGUID)(THIS_ /*[out]*/GUID* propGUID) PURE;
    // Property display name
    STDMETHOD(GetDisplayName)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    // Show/Hide property in the OPM, for this object instance 
    STDMETHOD(IsPropertyEnabled)(THIS_ /*[in]*/LONG_PTR objectID,
                                      /*[out]*/BOOL* pbEnabled) PURE;
    // Is property showing but disabled
    STDMETHOD(IsPropertyReadOnly)(THIS_ /*[out]*/BOOL* pbReadonly) PURE;
    // Get the property description string
    STDMETHOD(GetDescription)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    
    // *** Basic property value information ***
    // OPM will typically display these in an edit field
    
    // optional: meta data representing property type name, ex. ACAD_ANGLE
    STDMETHOD(GetCurrentValueName)(THIS_ /*[out]*/BSTR* pbstrName) PURE;
    // What is the property type, ex. VT_R8
    STDMETHOD(GetCurrentValueType)(THIS_ /*[out]*/VARTYPE* pVarType) PURE;
    // Get the property value, passes the specific object we need the property
    // value for.
    STDMETHOD(GetCurrentValueData)(THIS_ /*in*/LONG_PTR objectID, 
                                      /*[out]*/VARIANT* pvarData) PURE;
    // Set the property value, passes the specific object we want to set the 
    // property value for
    STDMETHOD(SetCurrentValueData)(THIS_ /*[in]*/LONG_PTR objectID, 
                                         /*[in]*/const VARIANT varData) PURE;

    //*** Notifications ***
    //OPM passes its implementation of IDynamicPropertyNotify, you
    //cache it and call it to inform OPM your property has changed
    STDMETHOD(Connect)(THIS_ /*[in]*/IDynamicPropertyNotify* pSink) PURE;
    STDMETHOD(Disconnect)(THIS_ ) PURE;
};

typedef IDynamicProperty FAR* LPDYNAMICPROPERTY;

//--------------------------
// IDynamicProperty2 interface
// Implement this class to create dynamic properties for the PropertyPalette
// it defines the base set of property attributes as well as
// the name/type/data tuples. 
//--------------------------
// {9CAF41C2-CA86-4ffb-B05A-AC43C424D076}
DEFINE_GUID(IID_IDynamicProperty2, 0x9caf41c2, 0xca86, 0x4ffb, 0xb0, 0x5a, 0xac, 0x43, 0xc4, 0x24, 0xd0, 0x76);

interface DECLSPEC_UUID("9CAF41C2-CA86-4ffb-B05A-AC43C424D076")
IDynamicProperty2 : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicProperty2 methods ***
    //Unique property ID
    STDMETHOD(GetGUID)(THIS_ /*[out]*/GUID* propGUID) PURE;
    // Property display name
    STDMETHOD(GetDisplayName)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    // Show/Hide property in the OPM, for this object instance 
    STDMETHOD(IsPropertyEnabled)(THIS_ /*[in]*/IUnknown *pUnk,
                                      /*[out]*/BOOL* pbEnabled) PURE;
    // Is property showing but disabled
    STDMETHOD(IsPropertyReadOnly)(THIS_ /*[out]*/BOOL* pbReadonly) PURE;
    // Get the property description string
    STDMETHOD(GetDescription)(THIS_ /*[out]*/BSTR* bstrName) PURE;
    
    // *** Basic property value information ***
    // OPM will typically display these in an edit field
    
    // optional: meta data representing property type name, ex. ACAD_ANGLE
    STDMETHOD(GetCurrentValueName)(THIS_ /*[out]*/BSTR* pbstrName) PURE;
    // What is the property type, ex. VT_R8
    STDMETHOD(GetCurrentValueType)(THIS_ /*[out]*/VARTYPE* pVarType) PURE;
    // Get the property value, passes the specific object we need the property
    // value for.
    STDMETHOD(GetCurrentValueData)(THIS_ /*in*/IUnknown *pUnk, 
                                      /*[out]*/VARIANT* pvarData) PURE;
    // Set the property value, passes the specific object we want to set the 
    // property value for
    STDMETHOD(SetCurrentValueData)(THIS_ /*[in]*/IUnknown *pUnk, 
                                         /*[in]*/const VARIANT varData) PURE;

    //*** Notifications ***
    //OPM passes its implementation of IDynamicPropertyNotify, you
    //cache it and call it to inform OPM your property has changed
    STDMETHOD(Connect)(THIS_ /*[in]*/IDynamicPropertyNotify2* pSink) PURE;
    STDMETHOD(Disconnect)(THIS_ ) PURE;
};

typedef IDynamicProperty2 FAR* LPDYNAMICPROPERTY2;

const int DISPID_DYNAMIC = -23; //majic DISPID

//--------------------------
// IDynamicEnumProperty interface
// components can implement this interface to create an enumerated property
// which will usually be displayed as a drop-down list in the OPM
//--------------------------
// {8B384028-ACB1-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IDynamicEnumProperty, 0x8B384028, 0xACB1, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACB1-11d1-A2B4-080009DC639A")
IDynamicEnumProperty : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IDynamicEnumProperty methods ***    
    // *** Extended property value infomation ***
    // - for properties types which are enums or finite valued but dynamic
    // OPM will typically display these in a dropdown list
    
    // total number of values this property can have, or currently has
    STDMETHOD(GetNumPropertyValues)(THIS_ /*[out]*/LONG* numValues) PURE;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueName)(THIS_ /*in*/LONG index, 
                                   /*[out]*/BSTR* valueName) PURE;
    // called for each property value, 0-based indexed to GetNumPropertyValues()
    STDMETHOD(GetPropValueData)(THIS_ /*in*/LONG index, 
                                   /*[out]*/VARIANT* valueName) PURE;
};

typedef IDynamicEnumProperty FAR* LPDYNAMICENUMPROPERTY;

//--------------------------
// IDynamicDialogProperty interface
// components can implement this interface to support ellipsis
// button properties
//--------------------------
// {8B384028-ACB2-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IDynamicDialogProperty, 0x8B384028, 0xACB2, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACB2-11d1-A2B4-080009DC639A")
IDynamicDialogProperty : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // If implemented, OPM will call the function passed back here
    STDMETHOD(GetCustomDialogProc)(THIS_ /*[out]*/OPMDIALOGPROC* pDialogProc) PURE;
    // Or, pass us the name of the VBA macro to run to edit this property
    STDMETHOD(GetMacroName)(THIS_ /*[out]*/BSTR* bstrName) PURE;

};

typedef IDynamicDialogProperty FAR* LPDYNAMICDIALOGPROPERTY;

//--------------------------
// IPropertyManager interface
// This is the main property manager class. Use this to add your
// property classes for a given type of entity. You can get this interface
// using GET_AUTOMATION_PROTOCOL(pEnt)->GetPropertyManager().
//--------------------------
// {8B384028-ACA9-11d1-A2B4-080009DC639A}
DEFINE_GUID(IID_IPropertyManager, 0x8B384028, 0xACA9, 0x11d1, 0xA2, 0xB4, 0x08, 0x00, 0x09, 0xDC, 0x63, 0x9A);

interface DECLSPEC_UUID("8B384028-ACA9-11d1-A2B4-080009DC639A")
IPropertyManager : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IPropertyManager methods ***
    STDMETHOD(AddProperty)(THIS_ IDynamicProperty FAR* pProperty) PURE;
    STDMETHOD(RemoveProperty)(THIS_ IDynamicProperty FAR* pProperty) PURE;
    STDMETHOD(GetDynamicProperty)(THIS_ /*[in]*/LONG index,
                                     /*[out]*/IDynamicProperty ** pProperty) PURE;
    STDMETHOD(GetDynamicPropertyByName)(THIS_ /*[in]*/BSTR propName,
                                           /*[out]*/IDynamicProperty ** pProperty) PURE;
    STDMETHOD(GetDynamicPropertyCount)(THIS_ /*[out]*/LONG* count) PURE;
    //For COM Wrappers to generate dynamic property typeinfo
    STDMETHOD(GetDynamicClassInfo)(THIS_ /*[in]*/IUnknown* pObj,
                                        /*[out]*/ITypeInfo** pptiDynamic,
                                        /*[out]*/DWORD* dwCookie) PURE;
};

typedef IPropertyManager FAR* LPPROPERTYMANAGER;

//--------------------------
// IPropertyManager2 interface
// This is the main property manager class. Use this to add your
// property classes for a given type of IUnknown object. 
// You can get this interface using 
// CreateOPMIUnknownProtocol(ppUnk)->GetPropertyManager2().
//--------------------------
// {FABC1C70-1044-4aa0-BF8D-91FFF9052715}
DEFINE_GUID(IID_IPropertyManager2, 0xfabc1c70, 0x1044, 0x4aa0, 0xbf, 0x8d, 0x91, 0xff, 0xf9, 0x5, 0x27, 0x15);

interface DECLSPEC_UUID("FABC1C70-1044-4aa0-BF8D-91FFF9052715")
IPropertyManager2 : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IPropertyManager2 methods ***
    STDMETHOD(AddProperty)(THIS_ IUnknown FAR* pDynPropObj) PURE;
    STDMETHOD(RemoveProperty)(THIS_ IUnknown FAR* pDynPropObj) PURE;
    STDMETHOD(GetDynamicProperty)(THIS_ /*[in]*/LONG index,
                                     /*[out]*/IUnknown ** pDynPropObj) PURE;
    STDMETHOD(GetDynamicPropertyByName)(THIS_ /*[in]*/BSTR propName,
                                           /*[out]*/IUnknown ** pDynPropObj) PURE;
    STDMETHOD(GetDynamicPropertyCountEx)(THIS_ /*[out]*/LONG* count) PURE;
    //For COM Wrappers to generate dynamic property typeinfo
    STDMETHOD(GetDynamicClassInfo)(THIS_ /*[in]*/IUnknown* pObj,
                                        /*[out]*/ITypeInfo** pptiDynamic,
                                        /*[out]*/DWORD* dwCookie) PURE;
};

typedef IPropertyManager2 FAR* LPPROPERTYMANAGER2;

//----------------------------------------
// {61D0A8E3-C792-4956-8E96-594315B95902}
DEFINE_GUID(IID_IPropertySource, 0x61d0a8e3, 0xc792, 0x4956, 0x8e, 0x96, 0x59, 0x43, 0x15, 0xb9, 0x59, 0x2);

interface DECLSPEC_UUID("61D0A8E3-C792-4956-8E96-594315B95902")
IPropertySource : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****

    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // *** IPropertySource methods ***
    
    // Call this when your property changes
    STDMETHOD(get_Name)(THIS_ /*[out, retval]*/BSTR* pName) PURE;
    // Call to get the current selection set OPM is working with, returns a SAFEARRAY 
    // of LONGs representing the objectIDs of the set, be sure to call VariantClear to cleanup
    STDMETHOD(GetProperties)(THIS_ /*[in]*/IUnknown* pObject, /*[out, retval]*/VARIANT *pPropertyArray) PURE;
};

typedef IPropertySource FAR* LPPROPERTYSOURCE;


//--------------------------
//--------------------------
// The following 4 interfaces, IFilterableProperty, IFilterablePropertySource,
// IFilterableMultiplePropertySource, and IFilterableSubtypePropertySource are
// all used by the property filter customization framework.  In AutoCAD, the
// CUI dialog allows the user to specify properties that they would
// like to see with the "Quick Properties" and "Rollover tooltips" features for
// each entity type.
//
// An entity that implementes its properties in an instance specific way,
// will most likely need to implement on or more of these interfaces to attain
// desired behavior.
//--------------------------
//--------------------------

//--------------------------
// IFilterableProperty interface
//
// This interface can be used to specify whether a particular property should
// be visible or not for property filter customization.  This interface's
// method is not instance dependent, but rather works at the type level.
// 
// This interface should be implemented in cases where a property's appearance
// is normally instance dependent but the entity type would like to dictate
// that the property should always be or never be available in the property
// filter customization user interface.
//
// For static properties, this interface should be implemented on the entity's
// COM wrapper.  For dynamic properties, this interface should be implemented on
// on the implementer of the IDynamicProperty interface.
//--------------------------
// {c93b89f1-794a-458e-8b49-7ce8ec7f6dd8}
DEFINE_GUID(IID_IFilterableProperty, 0xc93b89f1, 0x794a, 0x458e, 0x8b, 0x49, 0x7c, 0xe8, 0xec, 0x7f, 0x6d, 0xd8);

interface DECLSPEC_UUID("c93b89f1-794a-458e-8b49-7ce8ec7f6dd8")
IFilterableProperty : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //
    // *** IFilterableProperty methods ***
    //

    // The "ShowFilterableProperty" method is used to dictate whether a
    // property should be visible in the property filter customization user
    // interface.  It is passed a DISPID of the property whose visibility is
    // being determined (which would normally be "DISPID_DYNAMIC" for dynamic
    // properties) and an AcFilterablePropertyContext that specifies whether
    // the framework is querying about appearance in the "Quick Properties"
    // customization user interface or for the "Rollover tooltips"
    // customization user interface.  A boolean value indicating whether or
    // not the property should be shown is returned via the "pbShow"
    // output parameter.
    STDMETHOD(ShowFilterableProperty)(THIS_ /*[in]*/DISPID dispID,
                                            /*[in]*/AcFilterablePropertyContext context,
                                            /*[out]*/BOOL* pbShow) PURE;
};

typedef IFilterableProperty FAR* LPFILTERABLEPROPERTY;

//--------------------------
// IFilterablePropertySource interface
//
// This interface can be used to make an IPropertySource implementation
// create dynamic properties for property filter customization in an
// instance independent way.
// 
// This interface should be implemented in cases where a property's creation
// is normally instance dependent but the entity type would like to dictate
// that the property should always be or never be available in the property filter
// customization user interface.  This interface's "GetFilterableProperties"
// method is very much like the IPropertySource::GetProperties" method.  The
// difference is that the "GetFilterableProperties" method is not passed the
// "IUnknown*" of an instance.
//
// This interface should be implemented on the implementer of the
// IPropertySource interface.
//--------------------------
// {79bbcf7a-9b42-4c83-802f-deafc45d1b9e}
DEFINE_GUID(IID_IFilterablePropertySource, 0x79bbcf7a, 0x9b42, 0x4c83, 0x80, 0x2f, 0xde, 0xaf, 0xc4, 0x5d, 0x1b, 0x9e);

interface DECLSPEC_UUID("79bbcf7a-9b42-4c83-802f-deafc45d1b9e")
IFilterablePropertySource : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //
    // *** IFilterablePropertySource methods ***
    //

    // The "GetFilterableProperties" method should create the dynamic
    // properties that should be included in the property filter
    // customization user interface for the IPropertySource implementation
    // that is implementing this interface.  As is the case for the
    // IPropertySource::GetProperties" method that this method is modelled
    // after, the properties are returned via the "pPropertyArray" output
    // parameter.
    STDMETHOD(GetFilterableProperties)(THIS_ /*[out, retval]*/VARIANT *pPropertyArray) PURE;
};

typedef IFilterablePropertySource FAR* LPFILTERABLEPROPERTYSOURCE;

//--------------------------
// IFilterableMultiplePropertySource interface
//
// This interface can be used to inform the property filter customization
// framework about dynamic properties that may be multiple in number, but
// should be handled as a single customizable element in the customization
// framework.  The "Attributes" property of the "Block Reference" entity is
// an example of a property like this.  A particular block reference may have
// no attributes, 1 attribute, or many attributes, and multiple attributes have
// varying property names that are not defined by the "Block Reference" entity
// type, but any "attribute" dynamic properties are all identified by the
// same GUID, and are represented in the property filter customization
// user interface by a single, generic item.
//
// This interface should be implemented on the implementer of the
// IPropertySource interface that serves up the "multiple" properties.
// 
//--------------------------
// {59f3c133-c394-4606-b17f-79bed20761cf}
DEFINE_GUID(IID_IFilterableMultiplePropertySource, 0x59f3c133, 0xc394, 0x4606, 0xb1, 0x7f, 0x79, 0xbe, 0xd2, 0x07, 0x61, 0xcf);

interface DECLSPEC_UUID("59f3c133-c394-4606-b17f-79bed20761cf")
IFilterableMultiplePropertySource : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //
    // *** IFilterableMultiplePropertySource methods ***
    //

    // The "GetMultipleProperties" method should create the dynamic
    // properties that should be included in the property filter
    // customization user interface for the IPropertySource implementation
    // that is implementing this interface.  As is the case for the
    // IPropertySource::GetProperties" method that this method is modelled
    // after, the properties are returned via the "pPropertyArray" output
    // parameter.  Any "multiple" properties returned should be just like
    // the actual properties they represent in terms of their GUIDs and the
    // categories they are contained in, but the property name of the property
    // returned should be the "generic" name that will appear in the property
    // filter customization user interface.
    STDMETHOD(GetMultipleProperties)(THIS_ /*[out]*/VARIANT *pPropertyArray) PURE;
};

typedef IFilterableMultiplePropertySource FAR* LPFILTERABLEMULTIPLEPROPERTYSOURCE;

//--------------------------
// IFilterableSubtypePropertySource interface
//
// This interface can be used to define entity "subtype"s.  The property
// filter customization user interface will present the "subtype"s as
// children of the entity type whose IPropertySource implementer has
// implemented this interface.  Only a single level of "subtype"s are allowed.
// The "subtype" mechanism for property filter customization does not support
// full heirarchies.
//
// An example of an entity with "subtype"s is the "3d SOlid" entity type.
// A "3d Solid" can be a primitive "subtype" like a box or a sphere, or it
// may be a generic "BREP" solid.  The set of subtypes defined by this
// interface must be complete.  That is, any instance of the entity whose
// IPropertySource implementation is implementing this interface must be
// identifiable as one of the "subtype"s defined.
//
// This interface should be implemented on the implementer of the
// IPropertySource interface that serves up the dynamic properties for the
// "subtype"s.
//--------------------------
// {79bbcf7a-9b42-4c83-802f-deafc45d1b9e}
DEFINE_GUID(IID_IFilterableSubtypePropertySource, 0xa441627c, 0xd20f, 0x429f, 0x82, 0x75, 0x86, 0xb9, 0x54, 0x70, 0x29, 0xf7);

interface DECLSPEC_UUID("a441627c-d20f-429f-8275-86b9547029f7")
IFilterableSubtypePropertySource : public IUnknown
{
    BEGIN_INTERFACE
    // *** IUnknown methods ****
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //
    // *** IFilterableSubtypePropertySource methods ***
    //

    // The "GetSubtypes" method returns an array of BSTR items that identify
    // each subtype defined by this interface implementation via the
    // "pSubtypeGUIDsArray" output parameter.  Each BSTR is
    // the string representation of a "subtype"s GUID.
    STDMETHOD(GetSubtypes)(THIS_ /*[out]*/VARIANT *pSubtypeGUIDsArray) PURE;

    // The "GetSubtypeName" returns the name of the "subtype" that's
    // identified by the GUID BSTR passed in via the "bstrSubtypeGUID"
    // parameter in a BSTR via the "bstrSubtypeName" output parameter.
    STDMETHOD(GetSubtypeName)(THIS_ /*[in]*/BSTR bstrSubtypeGUID,
                                    /*[out]*/BSTR* bstrSubtypeName) PURE;

    // The "GetSubtypeProperties" method should create the dynamic
    // properties for the given "subtype" whose GUID string is passed in via
    // the "bstrSubtypeGUID" input parameter that should be included in
    // the property filter customization user interface for the IPropertySource
    // implementation that is implementing this interface.  As is the case for
    // the IPropertySource::GetProperties" method that this method is modelled
    // after, the properties are returned via the "pPropertyArray" output
    // parameter.
    STDMETHOD(GetSubtypeProperties)(THIS_ /*[in]*/BSTR bstrSubtypeGUID,
                                          /*[out]*/VARIANT *pPropertyArray) PURE;

    // The "GetObjectSubtype" method is used to identify the "subtype" of the
    // entity instance whose IUknown* is passe in via the "pObject" input
    // parameter.  A BSTR representaion of the GUID of the subtype of the
    // passed instance is returned via the "bstrSubtypeGUID" output parameter.
    STDMETHOD(GetObjectSubtype)(THIS_ /*[in]*/IUnknown* pObject,
                                      /*[out]*/BSTR* bstrSubtypeGUID) PURE;
};

typedef IFilterableSubtypePropertySource FAR* LPFILTERABLESUBTYPEPROPERTYSOURCE;
#endif
#endif //_DYNPROPS_H
