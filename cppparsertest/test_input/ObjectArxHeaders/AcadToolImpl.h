//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

// ******************************************************************************************************************************************

/*
The AcadToolImpl class handles general AutoCAD Tool functionality by parsing the tool's type information at 
runtime to discover details about the custom interface.  This information is used to persist the tool via XML (ATC files), 
support the default property inspector for the tool properties, handle drag/drop notifications, and support
for Color and Layer property controls .  At the same time, the developer is free to override any
functionality handled by this class by implementing the necessary virtual functions.

Included in the class are helper functions to generate Catalogs, Palettes, Tool instances and Command Tools (see
notes below for details).

Directions for use:
1 - Generate a custom COM interface (ATL Simple Object) with the ATL Wizard.

2 - Create a bitmap icon resource in this module for iconic depiction of your tool.
The standard size for tool icons are 65x65.  Create a string-type resource ID for the resource ID.  e.g. "IDB_MYTOOLIMAGE"
set in the Visual Studio properties window for the image.

3 - Derive your class from AcadToolImpl, listing it just below CComCoClass in the declaration.

Add the template arguments for the AcadToolImpl class:

    <Child Class Name, Tool Interface Class, Tool CLSID, Tool's Name, Tool's Image resource name>

    Note:  Because they are template LPCWSTR arguments, the Tools Name and image name must be declared globally
    (but not statically) as WCHARs.  The best place to do this is in the Tool's .cpp file, declaring them as extern in
    the tools header, to avoid LNK2005.

4 - Remove the derivation for CComObjectRootEx and IDispatchImpl for this CoClass, leaving only CComCoClass and
AcadToolImpl.

    When steps 3 and 4 are done it should look like this (fictitious arguments):
    
    #include "AcadToolImpl.h"

    extern WCHAR szEmployeeName[MAX_PATH]; // Declared in the tools .cpp file
    extern WCHAR szEmployeeImage[MAX_PATH];// -   -

    class ATL_NO_VTABLE CEmployeeTool : 
        public CComCoClass<CEmployeeTool, &CLSID_EmployeeTool>,
        public AcadToolImpl<CEmployeeTool,IEmployeeTool, &CLSID_EmployeeTool,szEmployeeName,szEmployeeImage>
    {

5 - Remove the COM_MAP and all the COM_INTERFACE_ENTRY entries from the CoClass header.

6 - Add the properties you want your tool to represent to the COM object via the ATL Wizard to the CoClass and IDL.

Additionally, the AcadToolImpl class automatically supports the Color and Layer Combo Box ActiveX controls to include
these features in your tools, if you chose.  To support either of them, add them as members to your interface as the
following entries in your IDL:
    
    Color is a type VARIANT property
    Layer is a BSTR property

    Note:  They must have the property names 'Color' and 'Layer'.  The methods get/put_Color() and get/put_LayerColor()
    are implemented in this base class so you can remove the CoClass declaration and implementation  for these 
    members, or you can call the base-versions from your overrides.  For each control you want, you will need to add an
    entry to the prop-display MAP, outlined below.
    
    If you chose not to support these controls, just leave them out of your interface; no other work is needed.
    
7 - Add specific member variables, excluding 'Color' and 'Layer' (which are represented in this class) to represent these 
properties in the CoClass.  Implement the Get and Put methods to refer to these members.  For your reference, 'Color' and 'Layer'
are declared in this class as:

m_Color - AcCmColor
m_szLayer - WCHAR[512]

8 - Add the following MAP to the class definition.  These will allow you to add definitions for the AutoCAD-specific
ComboBoxes such as Color Layer and Linetype.  The BEGIN and END are required only:

BEGIN_PERPROPDISPLAY_MAP2()
END_PERPROPDISPLAY_MAP2()

9 - Add the following MAP to the class definition.  This map will allow you to
define global properties which can be modified in a Flyout Tool which will be applied
to all the custom tool instances in the package the Flyout Tool represents.

BEGIN_FLYOUT_SPECIFIC_MAP()
END_FLYOUT_SPECIFIC_MAP()

For each property you want to set as a global Flyout property, add the following
FLYOUT_ENTRY for the DISPID of the property.

FLYOUT_ENTRY(<DISPID>)

If you want to support any of the property controls available (see Step 6), add entries to the MAP with the same format as
outlined in 'Per-Property Customization in the Property Inspector' within the 'PropertyPalette API' section
of the ObjectARX online help.

Example of support for Color, Layer and Linetype Combo Box controls in the Tool:

BEGIN_PERPROPDISPLAY_MAP2()
        PROP_DISP_ENTRY2(5, "AcPEXCtl.AcPePropertyEditorColor.16", NULL, NULL, NULL, NULL, 0x000000ff, FALSE, 1, 0)
        PROP_DISP_ENTRY2(6, "AcPEXCtl.AcPePropertyEditorLayer.16", NULL, NULL, NULL, NULL, 0x000000ff, FALSE, 1, 0)
END_PERPROPDISPLAY_MAP2()

Note:  The first argument in this map is the DISPID for the corresponding control

10 - Implement GetResourceInstance().  This can be placed publicly in the child class' header file.

    virtual HINSTANCE GetResourceInstance()
    {
        return _AtlBaseModule.GetResourceInstance();
    }

11 - include actc_i.c to the StdAfx.cpp file.

    #include "actc_i.c"

11 - You can chose to override any virtual IAcadTool or IAcadStockTool method in the child class if needed.
Additional virtual functions are defined in the base class to handle execution, drag/drop and additional persistence support
for your tools.  The are:

    executeCallback()			- Called when the tool is run
    dropCallback()				- Called when a tool is created from dropping an entity on the palette
    LoadPropertyValue()	- Called to handle reading all or extra property data from XML
    SavePropertyValue()	- Called to handle writing all or extra property data to XML

executeCallback() will be called when the user runs the tool, but after the document is locked and a reentrant 
mutex is set.  This is where you define what the tool does.  A typical example would be to instantiate a Prompt
class (see the AsdkPromptBase class for details).

dropCallback() will be called when entities are dropped on the palette from a block table record.  An AcDbEntity
pointer is passed representing the dropped entity, which should be used to populate the properties of the newly 
created tool (which will be the *this* object since it's an overriden member).

Load/SavePropertyValue() is called when the framework is reading or writing (respectively) the
properties themselves to the ATC (XML) file for the tool.  Override these members if you need to persist extra
data along with the property values, or if you want to be solely responsible for how the tool is persisted.  
An example is with a boolean representing the Unspecified state (IPropertyUnspecified) for a special ComboBox
such as Color or Layer.  An index representing which control (DISPID) is being written is passed along with 
an XML DOM node pointer to read/write with.  Remember to call the base-class version of this method if you want
the base class to handle standard persistence of the property.

10 - Be certain to override the New function to handle instantiation of your member variables.  This should be done
here rather than within the constructor, as the framework handles creation of your tool itself.


Notes:

1)  This implementation class will automatically support properties of all VARIANT types supported in the
property inspector.  While the Color property is marshalled across as a VT_DISPATCH, this sample 
persists the color as a LONG since XML can't represent interface pointers.  This is handled in this class' version of 
Load/SavePropertyValue.
    
If you define properties in your tool interface of less frequently used types (e.g. a GUID), you may
need to override the Load/SavePropertyValue() method to convert to and from string to support them yourself.
So, if IXMLDOMAttributePtr::get_value(the method used internally to persist your properties) can't persist the types, you
will need to convert them to string or other type and persist them manually either with the 
Load/SavePropertyValue()or directly overriding Load() and Save() from the base class.

See IXMLDOMAttributePtr::get_value and set_value for details about what VARIANTS types can be persisted in XML with the DOM.

2)  Included as members in this class are functions to create ATC files based on your new tool.  The are:

CreateStockToolATC()		Creates the stock tool catalog, and a general tool catalog.
CreatePaletteATC()			Creates a Palette, and adds it to the catalog passed in.
CreateToolATC()				Creates an instance of your tool, placing it in the Palette passed in
CreateCommandToolATC()		Creates a command tool which executes the passed macro string.
CreateFlyoutToolATC()		Creates a Flyout Tool, which can contain packages of other tools
CreateShapeCatalogATC()		Creates a shape package which can be represented by a Flyout Tool.

A typical usage of these functions might be:

        CComObject<CEmployeeTool> tool;
        AcTcCatalog *pCatalog=tool.CreateStockToolATC(L"EmployeeCatalog");
        AcTcPalette *pPalette=tool.CreatePaletteATC(pCatalog,L"EmployeePalette");
        tool.CreateToolATC(pPalette);
        AcTcGetManager()->LoadCatalogs(); // Refresh the Palette in the AutoCAD UI.

The CreateToolATC and CreateFlyoutToolATC have optional arguments to override
the tool's name and image for each instance.  If not used, the values passed in as the
template arguments in the class declaration will be used.
        
Generally, these functions would only be used to create the catalog ATC files, but distribution of these files to end users would be
handled by an installer.


*/

#pragma once
#include "AcImportXml.h"
using namespace MSXML; 
#include "AcPExCtl.h"
#include "opmdialog.h"
#include "Ac64BitHelpers.h"

// This is to avoid including AcTcUi.h, which would require MFC...TODO, we need to remove the CTypedPtrArray dependency to fully
// remove the dependency on MFC here.  This should be done with an overloaded global function in AcTcUi...
typedef CTypedPtrArray<CPtrArray, AcTcCatalogItem*> AcTcCatalogItemArray;
BOOL AcTcUiFilterShapesDialog(AcTcCatalogItem* pPackage,
                                            AcTcCatalogItemArray* pActiveShapes,
                                            AcTcTool*& pCurrentShape,
                                            CWnd* pParentWnd);

// Ok.  Here is the explanation of these macros.  Since we need to implement the IPerPropertyDisplayImpl
// helper interface class here, we need to declare a static function which returns the static map defined
// by their macros.  However, since the user will declare the actual MAP in the child class, we must forward
// this call to the child using the template argument for the child.  Take a look at GetPerPropDisplayArray in
// this class.

struct PER_PROP_DISP_ENTRY2
{
    DISPID    m_dispid;
    LPCWSTR   m_ProgID;
    LPCWSTR   m_lpLeftIconRes;
    UINT      m_nLeftIconType;
    LPCWSTR   m_lpEllipsisBmpRes;
    UINT      m_nEllipsisBmpType;
    COLORREF  m_TextColor;
    bool      m_bFullView;
    DWORD     m_dwIntegralHeight;
    long      m_nWeight;
};

// These are basically equivalent to those defined in IPerPropertyDisplayImpl

// use this #define for the textcolor item in PROP_DISP_ENTRY in order to use the
// default UI label color in the UI; any other value for textcolor is treated
// as a COLORREF
#ifndef TEXTCOLOR_DEFAULT
#define TEXTCOLOR_DEFAULT 0x80000008
#endif  // TEXTCOLOR_DEFAULT

#define BEGIN_PERPROPDISPLAY_MAP2()                                                            \
    static PER_PROP_DISP_ENTRY2* GetPerPropDisplayArray2()                                    \
    {                                                                                        \
        static PER_PROP_DISP_ENTRY2 pPerPropDisplayArray[] =                                 \
        {
                                                                                            
#define PROP_DISP_ENTRY2(dispid, progid, lpLeftIconRes, lpLeftIconType,                        \
    lpEllipsisBmpRes, lpEllipsisBmpType, textcolor,                                          \
    bFullView, dwIntegralHeight, nWeight)                                                    \
        {dispid, progid, lpLeftIconRes, lpLeftIconType, lpEllipsisBmpRes,                    \
        lpEllipsisBmpType, textcolor, bFullView,                                             \
        dwIntegralHeight, nWeight},                                                            \
                                                                                            
#define END_PERPROPDISPLAY_MAP2()                                                            \
        {-1, NULL, NULL, (UINT)PICTYPE_UNINITIALIZED, NULL, (UINT)PICTYPE_UNINITIALIZED, TEXTCOLOR_DEFAULT, false, (DWORD)-1, -1}\
        };                                                                                    \
        return pPerPropDisplayArray;                                                        \
    }

struct PER_FLYOUT_ENTRY
{
    DISPID    dispid;
};


#define BEGIN_FLYOUT_SPECIFIC_MAP()\
    static PER_FLYOUT_ENTRY* GetFlyoutMap()\
    {\
        static PER_FLYOUT_ENTRY pFlyoutEntry[]=\
        {

#define FLYOUT_ENTRY(dispid)\
            {dispid},

#define END_FLYOUT_SPECIFIC_MAP()\
            {-1}\
        };\
        return pFlyoutEntry;\
    }
    


static void *pAcadToolImpl=NULL;// Used to refer to the instance that spawns the separate IOPMPropertyDialog instance

template <class TT,class T,const CLSID* pclsid,LPCWSTR szToolName,LPCWSTR szToolImage,const IID* piid = &__uuidof(T),const GUID* plibid = &CAtlModule::m_libid> 
class ATL_NO_VTABLE AcadToolImpl : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public IDispatchImpl<T, piid, plibid, /*wMajor =*/ 1, /*wMinor =*/ 0>,
    public IAcadTool,
    public IAcadTool2,
    public IAcadStockTool,
    public IDropTarget,
    public IPropertyUnspecified,
    public IPerPropertyDisplayImpl<AcadToolImpl<TT,T,pclsid,szToolName,szToolImage,piid,plibid> >,
    public IOPMPropertyExtension,
    public IAcadToolContextMenu,
    public IPerPropertyBrowsing,
    public IOPMPropertyDialog,
    public IAcadToolFlyoutShape
{
public:
    
    AcadToolImpl()
    {
        wcscpy_s(m_szLayer,L"0");
        wcscpy_s(m_FlyoutTools,L"\0");
        dispColor=dispLayer=0;
        m_bColorUnspecified=m_bLayerUnspecified=TRUE;
        m_hWndEditWindow=NULL;
        m_pToolProp=NULL;
        mcfAutoCAD = (CLIPFORMAT)::RegisterClipboardFormat(acedClipFormatName());
    }
    ~AcadToolImpl()
    {
        m_ToolMap.setLogicalLength(0);
    }

    static PER_PROP_DISP_ENTRY* GetPerPropDisplayArray()
    {
        return (PER_PROP_DISP_ENTRY*)TT::GetPerPropDisplayArray2();
    }
    
    AcCmColor m_Color;
    WCHAR m_szLayer[512]; // Represents a Layer combo box in the tool property inspector 
    DISPID dispColor,dispLayer,dispFlyout;
    HWND m_hWndEditWindow;
    CComPtr<IAcadToolProperties> m_pToolProp;
    bool m_bFlyout; // Is this tool a flyout tool?  (not persisted through IDispatch)
    GUID m_FlyoutPackageId;// If so, what is the ID of the package (also not persisted through IDispatch)
    GUID m_CurrentShapeId;// And what is the ID of the current shape within this package.
    WCHAR m_FlyoutTools[64];
    
BEGIN_COM_MAP(AcadToolImpl)
    COM_INTERFACE_ENTRY(T)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IAcadTool)
    COM_INTERFACE_ENTRY(IAcadStockTool)
    COM_INTERFACE_ENTRY(IDropTarget)
    COM_INTERFACE_ENTRY(IPropertyUnspecified)
    COM_INTERFACE_ENTRY(IPerPropertyDisplay)
    COM_INTERFACE_ENTRY(IOPMPropertyExtension)
    COM_INTERFACE_ENTRY(IAcadToolContextMenu)
    COM_INTERFACE_ENTRY(IPerPropertyBrowsing)
    COM_INTERFACE_ENTRY(IOPMPropertyDialog)
    COM_INTERFACE_ENTRY(IAcadToolFlyoutShape)
END_COM_MAP()


protected:
    // Default members:
    HWND m_hPreviewWnd;
    BOOL m_bColorUnspecified,m_bLayerUnspecified;

    struct TOOL_MAP_ENTRY
    {
        WCHAR szDesc[512];
        DISPID dispId;
    };
    AcArray<TOOL_MAP_ENTRY> m_ToolMap;
    CLIPFORMAT mcfAutoCAD;


public:

    // ************************************************************************************
    // IAcadStockTool member
public:
    STDMETHOD(CreateTool) (/*[out, retval]*/ IUnknown** ppTool)
    {
        // Return the interface pointer for the IAcadTool (which for us is this object).
        HRESULT hr=GetPropertyTypeInfo();
        return _InternalQueryInterface(IID_IAcadTool, (void**) ppTool);
    }

    // ************************************************************************************
    // IAcadTool members
public:
    STDMETHOD(get_EditMode) (/*[out, retval]*/ long* pVal)
    {
        // Default Edit Mode.
        *pVal = kEditDefault;
        return S_OK;
    }
    
    STDMETHOD(GetStockTool) (/*[out, retval]*/ IUnknown** ppToolClass)
    {
        // Get the Stock Tool for this Tool (which for us is this object).
        return _InternalQueryInterface(IID_IAcadStockTool, (void**) ppToolClass);
    }
    
    STDMETHOD(Load) (/*[in]*/ IUnknown* pXmlElement)
    {
        CComQIPtr<MSXML::IXMLDOMNode> pEntityNode=pXmlElement;
        
        if (pEntityNode == NULL)
            return E_INVALIDARG;

        MSXML::IXMLDOMNodePtr pAttributeNode,pChild;
        
        if(GetChildNode(pEntityNode, L"Tool",&pAttributeNode))
            // Load the Tool members, via the COM interface.
            for(int i=0;i<m_ToolMap.length();i++)
                if(GetChildNode(pAttributeNode, m_ToolMap.at(i).szDesc,&pChild))
                    LoadPropertyValue(pChild,i+1);
        return S_OK;
    } 

    STDMETHOD(LoadFromFlyout)(IUnknown* pXmlElement)
    {
        // This is equivalent to load, but we are limiting the properties we load here
        // based upon what the design of the tool specifies as global properties from a flyout tool with FLYOUT_ENTRY entries.

        CComQIPtr<MSXML::IXMLDOMNode> pEntityNode=pXmlElement;
        
        if (pEntityNode == NULL)
            return E_INVALIDARG;

        MSXML::IXMLDOMNodePtr pAttributeNode,pChild;

        PER_FLYOUT_ENTRY *pFlyoutMap=TT::GetFlyoutMap();	
        
        if(GetChildNode(pEntityNode, L"Tool",&pAttributeNode))
            // Load the Tool members, via the COM interface.
            for(int i=0;i<m_ToolMap.length();i++)
                if(GetChildNode(pAttributeNode, m_ToolMap.at(i).szDesc,&pChild))
                {
                    int ii=0;
                    bool bGlobalProp=false;
                    while(pFlyoutMap[ii].dispid!=-1)
                    {
                        if(pFlyoutMap[ii].dispid==i+1)
                        {
                            bGlobalProp=true;
                            break;
                        }
                        ii++;
                    }
                    if(bGlobalProp)
                        LoadPropertyValue(pChild,i+1);
                }
        return S_OK;
    }
    
    STDMETHOD(Save) (/*[in]*/ IUnknown* pXmlElement)
    {
        if (pXmlElement == NULL)
            return E_INVALIDARG;
        
        MSXML::IXMLDOMNodePtr pEntityNode,pChildNode,pToolNode;
        CComQIPtr<MSXML::IXMLDOMNode> pParentNode=pXmlElement;
        
        // Add child nodes within this node for us to populate.
        if(!GetChildNode(pParentNode,L"Tool",&pEntityNode))
            AddChildNode(pParentNode, L"Tool", MSXML::NODE_ELEMENT, &pEntityNode);
        
        // Save the Tools members, via the COM interface.
        for(int i=0;i<m_ToolMap.length();i++)
        {
            if(!GetChildNode(pEntityNode, m_ToolMap.at(i).szDesc,&pChildNode))
                AddChildNode(pEntityNode,m_ToolMap.at(i).szDesc,MSXML::NODE_ELEMENT,&pChildNode);
            SavePropertyValue(pChildNode,i+1);
        }
        return S_OK;
    }
    
    STDMETHOD(executeCallback)() {return E_NOTIMPL;}
    STDMETHOD(dropCallback)(AcDbEntity *pEntity){return E_NOTIMPL;}
        
    STDMETHOD(Execute) (/*[in]*/ LONG_PTR lFlag, /*[in]*/ DWORD_PTR /*HWND*/ hWnd, /*[in]*/ DWORD point, /*[in]*/ DWORD dwKeyState)
    {
        // This method is called when the user uses this tool.  Generally, this should ultimately place 
        // the content the tool represents into the drawing.  This can be done by directly placing the 
        // object in the block table record, or using the Running object command object (see the AsdkPromptBase class)
        // to jig the object.
        
        // Prevent multiple entries into this tool.
        static bool bExecuteMutex=false;
        if(bExecuteMutex)
            return S_OK;
        bExecuteMutex=true;
        
        // Set the focus to AutoCAD
        ::SetFocus(adsw_acadDocWnd());

        
        // Lock the document
        AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();
        if(!pDb)
            return E_FAIL;
        AcAxDocLock docLock( pDb, AcAxDocLock::kNormal );
        if(docLock.lockStatus() != Acad::eOk){
            return E_FAIL;
        }

        // If this tool is run within a shape package, we will want to apply the global properties
        // from the flyout (parent) tool here.  (This can't be done at load time :-((().
        AcTcTool *pFlyoutTool=NULL;
        if(GetFlyoutTool(pFlyoutTool))
        {
            // Apply properties from the parent tool here...
            CComPtr<IUnknown> pUnk;
            
            BOOL bRet = pFlyoutTool->GetToolData(&pUnk);
            LoadFromFlyout(pUnk);
        }
        
        wcscpy_s(m_FlyoutTools,L"");//Reset this each time the tool is run.
        
        executeCallback(); // Allow the Child class to handle execution directly.
        
        bExecuteMutex=false;
        
        return S_OK;
    }
    
    BOOL GetFlyoutTool(AcTcTool*& pFlyoutTool)
    {
        pFlyoutTool = NULL;

        if(!wcscmp(m_FlyoutTools,L"")){
            return FALSE;
        }

        GUID flyoutToolId;
        BOOL bRet = FALSE;

        // We always return first flyout tool. If there are multiple flyout 
        // tools assert as a warning so that the caller will know.
        
        bRet = GuidFromString(m_FlyoutTools, flyoutToolId);
    

        if (!bRet)
            // Invalid guid
            return FALSE;

        // Get the tool object from the manager
        AcTcManager* pMgr = AcTcGetManager();
        pFlyoutTool = (AcTcTool*) pMgr->FindItem(flyoutToolId);
        if (pFlyoutTool == NULL)
            return FALSE;

        if (pFlyoutTool->GetType() != kItemTool)
            return FALSE;

        // We need to enforce the fact that flyouts that allow the shapes to snarf into them
        // for their FLYOUT_SPECIFIC properties be the same type of tool...
        CComPtr<T> pThisTool;
        if(!SUCCEEDED(QueryInterface(*piid,(void**)&pThisTool)))
            return E_FAIL;
        
        return TRUE;
    }
    
    
    
    STDMETHOD(GetData) (/*[in]*/ VARIANT *pObjUnkArray, /*[in]*/ VARIANT *pDynUnkArray)
    {
        // The framework is going to edit this tool.  It needs to know which properties will be edited.
                
        CComPtr<IUnknown> pUnk;
        _InternalQueryInterface(IID_IUnknown, (void**) &pUnk);
        
        // GetUnknownArrays is a helper function which populates the args passed in here with arrays
        // of our static interface, and a NULL array for the dynamic properties, which this class doesn't define.
        GetUnknownArrays(1, &pUnk, pObjUnkArray, pDynUnkArray);
        return S_OK;
    }
    
    // If you want custom editing of your tool, handle these Edit methods (and return kEditCustom from get_EditMode).
    // Otherwise the framework will handle it for you (default for this example).
    STDMETHOD(BeginEdit) ()
    {
        return S_OK;
    }
    STDMETHOD (Edit) (/*[in]*/ IUnknown* pProp,/*[in]*/ LONG_PTR /*HWND*/ hWndParent, /*[out]*/ VARIANT_BOOL* pRet) 
    {
        m_hWndEditWindow=(HWND)hWndParent;	
        return S_OK;
    }
    STDMETHOD (EndEdit)(/*[in]*/ VARIANT_BOOL bEditCancelled){return E_NOTIMPL;}
    
    STDMETHOD (Dropped)(/*[in]*/ BSTR bstrUrl)
    {
        return E_NOTIMPL;
    }
    STDMETHOD(GetDropTarget) (/*[out, retval]*/ IUnknown** ppDropTarget)
    {
        // return our IDropTarget interface...
        return _InternalQueryInterface(IID_IDropTarget, (void**) ppDropTarget);
    }
    
    STDMETHOD (Refreshed)(/*[in]*/ BSTR bstrUrl)
    {
        return E_NOTIMPL;
    }
    STDMETHOD (SetEditorWindow)(/*[in]*/ LONG_PTR /*HWND*/ hWndEditor, /*[in]*/ IUnknown*	pPropInspector)
    {
        // Cache the preview window...not used in this default example.
        m_hPreviewWnd = (HWND) hWndEditor;
        return E_NOTIMPL;
    }
    
    STDMETHOD (ValidateEditChanges)()
    {
        // Called when the user edits the tool in the default editor.  Implement this to validate changes
        // made to your tools here.
        return E_NOTIMPL;
    }
    
    STDMETHOD(SetToolProperties) (/*[in]*/ IUnknown* pProp)
    {
        // Cache the tool properties object for later use.
        HRESULT hr = pProp->QueryInterface(IID_IAcadToolProperties, (void**) &m_pToolProp);
        if(!m_pToolProp)
            return E_FAIL;

        hr=m_pToolProp->get_ShapePackageId(&m_FlyoutPackageId);
        hr = m_pToolProp->get_CurrentShapeId(&m_CurrentShapeId);
        return S_OK;
    }
    
    STDMETHOD (GetToolProperties)(/*[out, retval]*/ IUnknown** pToolProp)
    {
        // Return the tool properties here...
        m_pToolProp->QueryInterface(IID_IAcadToolProperties,(void**)pToolProp);
        return S_OK;
    }
    
    STDMETHOD(New) ()
    {
        // You should really override this method, and initialize all your members.
        return E_NOTIMPL;
    }

    // IAcadTool2 members
    STDMETHOD(UpdateImage)(void)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(GetContextMenu) (/*[in]*/ INT_PTR nContextFlag, /*[in]*/ DWORD_PTR /*HMENU*/ hMenu, /*[in]*/ UINT idCmdFirst,/*[in]*/  UINT idCmdLast, /*[out, retval]*/ DWORD_PTR* pFlag){return E_NOTIMPL;}
    STDMETHOD(GetCommandString) (/*[in]*/ UINT idCmd, /*[out, retval]*/BSTR* pbstrHelpText){return E_NOTIMPL;}
    STDMETHOD(InvokeCommand) (/*[in]*/ UINT idCmd, /*[in]*/ DWORD_PTR /*HWND*/ hWnd){return E_NOTIMPL;}
    STDMETHOD(GetDragDropContextInfo) (/*[in]*/ IUnknown*	pIUnknown, /*[out]*/BSTR* pbstrText, /*[out]*/ DWORD* pFlag)
    {
        _bstr_t bstrName(szToolName);
        *pbstrText = bstrName.copy();
        return S_OK;
    }

    STDMETHOD(BeginMultipleEdit) (/*[in]*/ VARIANT tools, 
                                  /*[in]*/ VARIANT stockToolIds)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(EndMultipleEdit) (/*[in]*/ VARIANT tools, 
                                /*[in]*/ VARIANT stockToolIds,
                                /*[in]*/ VARIANT_BOOL bEditCancelled)
    {
        return E_NOTIMPL;
    }

    STDMETHOD (MultipleEdit) (/*[in]*/ VARIANT tools,
                              /*[in]*/ VARIANT stockToolIds, 
                              /*[in]*/ LONG_PTR /*HWND*/ hWndParent, 
                              /*[out]*/ VARIANT_BOOL* pRet)
    {
        return E_NOTIMPL;
    }


    // ************************************************************************************
    // IAcadToolContextMenu members - Override these if you need custom context menus
    
    STDMETHOD(Customize)(/* [in] */ int nContextFlag,
                            /* [in] */ DWORD_PTR hMenu,
                            /* [in] */ UINT idCmdFirst,
                        /* [in] */ UINT idCmdLast,
                        /* [in] */ GUID *pPaletteId,
                        /* [retval][out] */ DWORD *pFlag)
    {
        return E_NOTIMPL;
    }
    STDMETHOD(GetMenuHelp)( /* [in] */ UINT idCmd,
                            /* [retval][out] */ BSTR *pbstrHelpText)
    {
        return E_NOTIMPL;
    }
    
    STDMETHOD(InvokeMenuCommand)(/* [in] */ UINT idCmd,
                                    /* [in] */ GUID *pPaletteId,
                                    /* [in] */ DWORD_PTR hWnd,
                                    /* [retval][out] */ DWORD *pFlag)
    {
        return E_NOTIMPL;
    }

    // ************************************************************************************
    // IDropTarget members
    STDMETHOD(DragEnter) (/*[unique][in]*/ IDataObject __RPC_FAR *pDataObj, /*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect)
    {
        *pdwEffect = DROPEFFECT_COPY;
        return S_OK;
    }
    
    STDMETHOD(DragOver) (/*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect)
    {
        *pdwEffect = DROPEFFECT_COPY;
        return S_OK;
    }
    
    STDMETHOD(DragLeave) (void){return E_NOTIMPL;}
    STDMETHOD(Drop) (/*[unique][in]*/ IDataObject __RPC_FAR *pDataObj, /*[in]*/ DWORD grfKeyState, /*[in]*/ POINTL pt, /*[out][in]*/ DWORD __RPC_FAR *pdwEffect)
    {
        *pdwEffect = DROPEFFECT_COPY;

        COleDataObject data;
        data.Attach(pDataObj, FALSE);

        // This feature utilizes the AutoCAD Drag and Drop functionality, which uses the Windows System Clipboard.

        // First, get the clipboard info.
        ClipboardInfo clipInfo;
        if (!GetClipInfo(&data, &clipInfo))
            return E_FAIL;

        AcDbDatabase tempDb(false, true);
        Acad::ErrorStatus es = tempDb.readDwgFile(clipInfo.szTempFile);
        if (es != Acad::eOk)
            return E_FAIL;

        AcDbBlockTableRecordIterator *pItr = NULL;
        {
            AcDbBlockTableRecordPointer pBTR(ACDB_MODEL_SPACE,&tempDb,AcDb::kForRead);
            if(pBTR->newIterator(pItr)!=Acad::eOk)
                return E_FAIL;
        }

        AcDbEntity *pDropEntity=NULL;
        while(!pItr->done())
        {
            // The first entity in (the temporary) Model Space should be our entity...
            if(pItr->getEntity(pDropEntity, AcDb::kForRead)!=Acad::eOk)
            {
                delete pItr;
                return E_FAIL;
            }
            break;// we only need the first one...
            pItr->step();
        }
        delete pItr;

        if(pDropEntity==NULL)
            return E_FAIL;

        // Entities dropped from the editor generally should not have unspecified versions of these...
        m_bLayerUnspecified=FALSE;
        m_bColorUnspecified=FALSE;
                
        HRESULT hr=dropCallback(pDropEntity); // Allow the Child class to handle how the tools are created when content is dropped.
        pDropEntity->close();

        if(!SUCCEEDED(hr))
            return E_FAIL;

        // Now apply properties to the toolprop object...
        if (m_pToolProp != NULL) {
                                
            hr=m_pToolProp->put_Name(CComBSTR(szToolName));
            WCHAR modulePath[MAX_PATH];
            HINSTANCE hInst=_AtlBaseModule.GetResourceInstance();
            DWORD res=GetModuleFileName(hInst,modulePath,MAX_PATH);
            
            AcTcImage image;
            HBITMAP hBitmap=::LoadBitmap(_AtlBaseModule.GetResourceInstance(),szToolImage);
            image.Load(hBitmap);
            SIZE size;
            image.GetSize(&size);
                                    
            hr=m_pToolProp->SetImage(size.cx,size.cy,NULL,CComBSTR(szToolImage),CComBSTR(modulePath));
        }
        data.Detach();
        return hr;
    }

    // ************************************************************************************
    // IPropertyUnspecified Members
    STDMETHOD (IsValueUnspecified)(/*[in]*/ VARIANT varId, /*[out]*/ VARIANT_BOOL *pVal)
    {
        *pVal = VARIANT_FALSE;
        if (varId.ulVal == dispColor || varId.ulVal == dispLayer)
        {	if (varId.ulVal ==  dispColor && m_bColorUnspecified)	
                *pVal=VARIANT_TRUE;	
            if (varId.ulVal ==  dispLayer && m_bLayerUnspecified)	
                *pVal=VARIANT_TRUE;
        }
        return S_OK;
    }
    STDMETHOD (SetUnspecified)(/*[in]*/ VARIANT varId, /*[in]*/ VARIANT_BOOL bIsUnspecified)
    {
        if (varId.ulVal == dispColor)
            m_bColorUnspecified = (bIsUnspecified == VARIANT_TRUE ? true : false);
        else if (varId.ulVal == dispLayer)
            m_bLayerUnspecified = (bIsUnspecified == VARIANT_TRUE ? true : false);
        return S_OK;
    }
    
    STDMETHOD (IsUnspecifiedAllowed)(/*[in]*/ VARIANT varId, /*[out]*/ VARIANT_BOOL *pVal)
    {
        if (varId.ulVal == dispColor || varId.ulVal == dispLayer)
            *pVal=VARIANT_TRUE;	
        else
            *pVal = VARIANT_FALSE;
        return S_OK;
    }
    
    STDMETHOD (GetUnspecifiedString)(VARIANT,BSTR *str)
    {
        // Called to get the string which specifies an undefined value in these controls..
        _bstr_t unspecifiedString(L"*Unspecified*");
        *str = unspecifiedString.copy();
        return S_OK;
    }
    
    STDMETHOD(GetEllipsisBitMap) ( 
        /* [in] */ VARIANT varId,
        /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBitMap){return E_NOTIMPL;}
    
    STDMETHOD(GetPropHelpProc) ( 
        /* [in] */ VARIANT varId,
        /* [out] */ LONG __RPC_FAR *pHelpProc){return E_NOTIMPL;}
    
    // Extract the dropped data from the clipboard.
    BOOL GetClipInfo(COleDataObject* pDataObject, ClipboardInfo* pClipboardInfo)
    {
        CLIPFORMAT cFormat = mcfAutoCAD;

        if (!pDataObject->IsDataAvailable(cFormat)) {
            return FALSE;
        }

        STGMEDIUM stgMedium = { TYMED_HGLOBAL,  NULL };
        FORMATETC fmt = { cFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        BOOL bValid = pDataObject->GetData(cFormat, &stgMedium, &fmt);
        
        if (bValid && stgMedium.hGlobal != NULL) 
        {
            ClipboardInfo* pClipInfo=(ClipboardInfo*)::GlobalLock(stgMedium.hGlobal);

            // Copy all the data
            *pClipboardInfo = *pClipInfo;
            
            ::GlobalUnlock(stgMedium.hGlobal);
            ::ReleaseStgMedium(&stgMedium);
            return TRUE;
        }
        return FALSE;
    }
    
    virtual HRESULT GetPropertyTypeInfo()
    {
        // This is the function called to determine the DISPIDs and property names for the child class' interface so
        // they can be automatically supported.  These are stored in the TOOL_MAP.  It should only be called once per-creation.
        
        T *pITool;
        // Get IDispatch interface for object
        if (!SUCCEEDED(QueryInterface(*piid,(void**)&pITool)))
            return E_FAIL;
        // Find out if we have Type Info (we should have)
        unsigned int count = 0;
        if (!SUCCEEDED(pITool->GetTypeInfoCount(&count))) {
            pITool->Release();        
            return E_FAIL;
        }
        // If no Type Info, exit
        if (!count)
            return E_FAIL;// No properties to Jig ???
        // Get iTypeInfo interface for object for any locale
        CComPtr<ITypeInfo> pTypeInfo;
        if (!SUCCEEDED(pITool->GetTypeInfo(0, NULL, &pTypeInfo))) {
            pITool->Release();        
            return E_FAIL;
        }
        pITool->Release();        
        // Retrieve type attributes - to find number of methods for entity
        TYPEATTR * pTypeAttr;
        if (!SUCCEEDED(pTypeInfo->GetTypeAttr(&pTypeAttr)))
            return E_FAIL;
        int numFuncs = pTypeAttr->cFuncs;
        pTypeInfo->ReleaseTypeAttr(pTypeAttr);

        m_ToolMap.setLogicalLength(0);// Clear the array.
        
        // Iterate over all methods.
        for(int i = 0; i < numFuncs; i++)
        {
            //Get the function description
            FUNCDESC * pFuncDesc;
            if (!SUCCEEDED(pTypeInfo->GetFuncDesc(i, &pFuncDesc)))
                return E_FAIL;
            //Get the member ID
            MEMBERID memberID;
            memberID = pFuncDesc->memid;
            
            if(memberID < 1000) // Assumes the IDs below 1000 are the child class' methods
            {
                    UINT nReturnedNames; 
                    // Since the DISPID will be shared by both 'put' and 'get' functions, we will enter here twice for each property, though we
                    // only need to use one.  The 'get' version will have the VT_BYREF or'ed in the VARTYPE, 
                    // so we can chose to ignore this one to get the true type from the property 'put' version.
                    if(pFuncDesc->invkind==INVOKE_PROPERTYGET)
                        continue;
                    // This is equivalent to checking invkind...
                    //if(pFuncDesc->lprgelemdescParam[nReturnedNames-1].tdesc.vt & VT_BYREF)
                    //	continue;
                    
                    // Allocate one BSTR pointer array.
                    BSTR bstrNames[1] = {NULL};
                    if (!SUCCEEDED(pTypeInfo->GetNames(memberID, bstrNames, 1, &nReturnedNames)))
                        return E_FAIL;
                    if(nReturnedNames<1)
                        continue; // no need to delete the bstr array...since the size is zero...

                    CComBSTR bstrVal(bstrNames[0]);
                    COLE2T szName(bstrVal);
                    TOOL_MAP_ENTRY mapEntry;
                    wcscpy_s(mapEntry.szDesc,szName);
                    mapEntry.dispId=memberID;
                    m_ToolMap.append(mapEntry);

                    // Determine the Color and Layer DISPIDs.
                    if(!wcscmp(szName,L"Color"))
                        dispColor=memberID;
                    if(!wcscmp(szName,L"Layer"))
                        dispLayer=memberID;
                    if(!wcscmp(szName,L"Flyout"))
                        dispFlyout=memberID;

                    // Only one element array.
                    SysAllocString(bstrNames[0]);
            }
        }
        return S_OK;
    }

    HRESULT PutToolProperty(int index,VARIANT vValue)
    {
        // Places the property value to the tool instance from vValue via COM.

        // Note:  Here, index is 1 based, and should match the DISPIDs for each property.
        
        // index-1 is the index into the TOOL_MAP...vValue is the value to set.
        WORD wflags = DISPATCH_PROPERTYPUT;
        DISPID putid = DISPID_PROPERTYPUT;
        
        // Get IDispatch from the tool interface.
        CComPtr<IDispatch> pDisp;
        if(!SUCCEEDED(QueryInterface(*piid,(void**)&pDisp)))
            return E_FAIL;
        
        DISPPARAMS dispparams;
        
        dispparams.rgvarg = &vValue;
        dispparams.rgdispidNamedArgs= &putid;
        dispparams.cArgs = 1;      
        dispparams.cNamedArgs = 1;
        
        return pDisp->Invoke(m_ToolMap[index-1].dispId,
            IID_NULL,
            LOCALE_USER_DEFAULT, 
            wflags,
            &dispparams,
            NULL,NULL,NULL);
    }

    HRESULT GetToolProperty(int index,VARIANT& vValue)
    {
        // Note:  Here, index is 1 based, and should match the DISPIDs for each property.
        
        // Retrieves the property value from the tool instance, placing it into vValue.
        
        // Get IDispatch from the tool interface.
        CComPtr<IDispatch> pDisp;
        if(!SUCCEEDED(QueryInterface(*piid,(void**)&pDisp)))
            return E_FAIL;

        DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
        
        return pDisp->Invoke(
        m_ToolMap[index-1].dispId,
        IID_NULL,
        LOCALE_USER_DEFAULT,
        DISPATCH_PROPERTYGET,
        &dispparamsNoArgs, &vValue, NULL, NULL);
    }

    //IPerPropertyBrowsing
    STDMETHOD(GetDisplayString)(DISPID dispID,BSTR *pbstr)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(MapPropertyToPage)(DISPID dispID,CLSID *pCLSID)
    {
        if(dispID==dispFlyout)
        {
            *pCLSID=*pclsid;
            pAcadToolImpl=(void*)this;
            return S_OK;
        }
        else
            return E_NOTIMPL;
    }

    STDMETHOD(GetPredefinedStrings)(DISPID dispID,CALPOLESTR *pcaStringsOut,CADWORD *pcaCookiesOut)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(GetPredefinedValue)(DISPID dispID,DWORD dwCookie,VARIANT *pVarOut)
    {
        return E_NOTIMPL;
    }

    // *******************************************************************************************
    // IOPMPropertyDialog 
    STDMETHOD(DoModal)(BSTR* propValueString,AcDbObjectIdArray* ObjectIdArray)
    {
        IAcadToolProperties *pToolProp=GetThisToolsProperties();
        if(!pToolProp)
            return E_FAIL;
        
        AcTcManager* pMgr = AcTcGetManager();
        if (!pMgr)
            return E_FAIL;

        // Get the shape package
        //
        GUID id;
        pToolProp->get_ShapePackageId(&id);
                   
        AcTcCatalogItem* pShapeCatalog = pMgr->GetShapeCatalog();
        AcTcCatalogItem* pShapePackage=pShapeCatalog->FindInChildren(id);
                
        if (!pShapePackage)
            return E_FAIL;    

        // Get the activeshapes
        
        VARIANT varShapes;
        HRESULT hr = pToolProp->get_ActiveShapeIds(&varShapes);
        
        if(!(varShapes.vt & VT_ARRAY && varShapes.vt & VT_BSTR))
                return E_INVALIDARG;
        SAFEARRAY* sPt=varShapes.parray;

        if(SafeArrayGetDim(sPt)!=1)
            return E_INVALIDARG;

        long lLower,lUpper;
        SafeArrayGetLBound(sPt,1,&lLower);
        SafeArrayGetUBound(sPt,1,&lUpper);

        //AcTcCatalogItemArray activeShapes; 
        AcTcCatalogItemArray activeShapes;
        for(long i=lLower; i<=lUpper; i++) {
            VARIANT val;
            SafeArrayGetElement(sPt,&i,&val);
            GUID id;
            GuidFromString(CW2T(val.bstrVal), id);
                    
            AcTcCatalogItem* pItem = pShapePackage->FindInChildren(id, FALSE);        
            if (pItem == NULL)
                continue;
            if (pItem->GetType() == kItemTool)
                activeShapes.Add(pItem);            
        }

        // Get the current shape
        //
        GUID currentShapeId;
        hr = pToolProp->get_CurrentShapeId(&currentShapeId);
        AcTcTool* pCurrentShape = (AcTcTool*)pShapePackage->FindInChildren(currentShapeId, FALSE);
        
        // Display the filter shape dialog for the user to edit the 
        // active shapes
        if(!AcTcUiFilterShapesDialog(pShapePackage, &activeShapes,pCurrentShape, NULL))
            return E_FAIL;

        // Now replace the active shapes with those updated by the user.
        
        INT_PTR nCount = activeShapes.GetSize();
        
        SAFEARRAYBOUND rgsaBound;
        rgsaBound.lLbound = 0L;

        //Active shape size can't be more than 1M
        rgsaBound.cElements = AcIntPtrToInt(nCount);

        VariantClear(&varShapes);
        varShapes.vt = VT_ARRAY | VT_VARIANT;
        sPt=varShapes.parray;
        varShapes.parray = SafeArrayCreate(VT_VARIANT, 1, &rgsaBound);

        for (long i=0; i<nCount; i++) {
            AcTcCatalogItem* pItem = activeShapes[i];
            pItem->GetID(&id);
            VARIANT varGuid;
            varGuid.vt = VT_BSTR;
            varGuid.bstrVal=StringFromGuid(id);
            hr = SafeArrayPutElement(varShapes.parray, &i,&varGuid);
        }
        hr=pToolProp->put_ActiveShapeIds(&varShapes);

        return S_OK;
    }
    
    // IAcadToolFlyoutShape methods
    STDMETHOD(SetFlyoutTools) (/* [in] */ VARIANT* pFlyoutToolIds)
    {
        wcscpy_s(m_FlyoutTools,L"");
        if (pFlyoutToolIds == NULL)
            return S_OK;

        SAFEARRAY* saFlyoutToolIds=pFlyoutToolIds->parray;

        if(SafeArrayGetDim(saFlyoutToolIds)!=1)
            return E_INVALIDARG;

        long lLower,lUpper;
        SafeArrayGetLBound(saFlyoutToolIds,1,&lLower);
        SafeArrayGetUBound(saFlyoutToolIds,1,&lUpper);

        for(long i=lLower; i<=lUpper; i++) {
            VARIANT val;
            SafeArrayGetElement(saFlyoutToolIds,&i,&val);
            wcscpy_s(m_FlyoutTools,CW2T(val.bstrVal));
        }
        return S_OK;
    }

    // ************************************************************************************
    // IOPMPropertyExtension 
    STDMETHOD(Editable)(DISPID dispID,BOOL __RPC_FAR * bEditable)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(GetDisplayName)(DISPID dispID,BSTR * propName)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(ShowProperty)(DISPID dispID,BOOL * pShow)
    {
        // This is here to distiguish when a given tool instance is a flyout.  For Flyouts, we only want 
        // to edit properties which are called out in the child class with FLYOUT_ENTRYs.  In addition, we don't want to show the
        // Flyout option for non-flyout tools.
        *pShow=TRUE;

        IAcadToolProperties *pToolProp=GetThisToolsProperties();
        if(!pToolProp)
            return E_FAIL;
        
        VARIANT_BOOL vbFlyout;
        pToolProp->get_IsFlyoutEnabled(&vbFlyout);
        if(vbFlyout)
        {
            PER_FLYOUT_ENTRY *pFlyoutMap=TT::GetFlyoutMap();	
            
            for(int i=0;i<m_ToolMap.length();i++)
            {
                int ii=0;
                bool bGlobalProp=false;
                while(pFlyoutMap[ii].dispid!=-1)
                {
                    if(pFlyoutMap[ii].dispid==dispID)
                    {
                        bGlobalProp=true;
                        break;
                    }
                    ii++;
                }
                if(bGlobalProp)
                    *pShow=TRUE;
                else
                    *pShow=FALSE;
            }
        }
        else
            if(dispID==dispFlyout)
                *pShow=FALSE;
        
        return S_OK;
    }


    BOOL GuidFromString(LPWSTR pszGuid, GUID& id)
    {
        ZeroMemory(&id, sizeof(GUID));

        if (pszGuid == NULL)
            return FALSE;

        // Enclose the guid in braces if not enclosed already,
        // otherwise CLSIDFromString will fail.
        WCHAR tsFormatGuid[64]=L"{";
        if(wcslen(pszGuid) > 0 && pszGuid[0] !=L'{')
            wcscat_s(tsFormatGuid,pszGuid);
        if(wcslen(pszGuid) > 0 && pszGuid[wcslen(tsFormatGuid)-1] !=L'}')
            wcscat_s(tsFormatGuid,L"}");

        HRESULT hr = CLSIDFromString(CT2W(tsFormatGuid), &id);
        return SUCCEEDED(hr);
    }

    CComBSTR StringFromGuid(const GUID& id)
    {
        // If we use CComBSTR it crashes. Use LPOLESTR.
        LPOLESTR pbstrGuid = NULL;
        HRESULT hr = StringFromCLSID(id, &pbstrGuid);
        if (FAILED(hr) || pbstrGuid == NULL)
            return L"";

        CW2T   szVal(pbstrGuid);
        LPWSTR  sId(szVal);

        // Remove open and close braces from the guid
        sId=_wcsninc(sId,1);
        _wcsrev(sId);
        sId=_wcsninc(sId,1);
        _wcsrev(sId);

        CComBSTR bstr(sId);
        CoTaskMemFree(pbstrGuid);

        return bstr;
    }


    // Handling of the True Color Combo Box property here.
    STDMETHOD (get_Color)(VARIANT *pVar)
    {
        if (pVar == NULL)
            return E_FAIL;

        VariantInit(pVar);
        pVar->vt = VT_DISPATCH;
           
        CComQIPtr<IAcadAcCmColor> pIAcadAcCmColor;
        HRESULT hr = pIAcadAcCmColor.CoCreateInstance(CLSID_AcadAcCmColor);
        if (FAILED(hr) || !pIAcadAcCmColor)
            return E_FAIL;

        CComBSTR colorName(m_Color.colorName());
        CComBSTR bookName(m_Color.bookName());
        pIAcadAcCmColor->put_EntityColor(m_Color.color());
        pIAcadAcCmColor->SetNames(colorName, bookName);

        hr = pIAcadAcCmColor->QueryInterface(IID_IDispatch, (void**) &pVar->pdispVal);
        if(SUCCEEDED(hr))
            return S_OK;
        else
            return E_FAIL;
    }

    STDMETHOD (put_Color)(VARIANT pVar)
    {
        if (V_VT(&pVar) != VT_DISPATCH)
            return E_FAIL;

        if (pVar.pdispVal == NULL)
            return E_FAIL;

        HRESULT hr = S_OK;
        CComQIPtr<IAcadAcCmColor> pIAcadAcCmColor;
        hr =  pVar.pdispVal->QueryInterface(IID_IAcadAcCmColor, (void**) &pIAcadAcCmColor);
        if (FAILED(hr) || !pIAcadAcCmColor)
            return E_FAIL;


        BSTR colorName, bookName;
        long lEntityColor;
        colorName = bookName = NULL;
        lEntityColor = 0;
        
        hr = pIAcadAcCmColor->get_EntityColor(&lEntityColor);
        hr = pIAcadAcCmColor->get_ColorName(&colorName);
        hr = pIAcadAcCmColor->get_BookName(&bookName);
        
        m_Color.setColor(lEntityColor);
        m_Color.setNames(CW2T(colorName),CW2T(bookName));
        return S_OK;
    }

    // Handling the Layer Combo Box property here.
    STDMETHOD (get_Layer)(BSTR* pVal)
    {
        CComBSTR bStr(m_szLayer);
        bStr.CopyTo(pVal);
        return S_OK;
    }

    STDMETHOD (put_Layer)(BSTR newVal)
    {
        CComBSTR bStr(newVal);
        COLE2T szName(bStr);
        wcscpy_s(m_szLayer,szName);
        return S_OK;
    }

    STDMETHOD(put_Flyout)(BSTR var)
    {
        // Nothing to do here...
        return S_OK;
    }

    STDMETHOD(get_Flyout)(BSTR *pVar)
    {
        CComBSTR bstr(L"<Choose Commands>");
        bstr.CopyTo(pVar);
        return S_OK;
    }

    BOOL GetUnknownArrays(int nCount, 
                        IUnknown** pObjUnkArray, 
                        VARIANT* pStatUnkArray, 
                        VARIANT* pDynPMUnkArrays)
    {
        if (nCount < 1) 
            return FALSE;

        pStatUnkArray->vt = VT_ARRAY | VT_VARIANT;
        pDynPMUnkArrays->vt = VT_ARRAY | VT_VARIANT;

        SAFEARRAYBOUND rgsaBound;
        rgsaBound.lLbound = 0L;
        rgsaBound.cElements = nCount;

        pStatUnkArray->parray = SafeArrayCreate(VT_VARIANT, 1, &rgsaBound);
        pDynPMUnkArrays->parray = SafeArrayCreate(VT_VARIANT,1,&rgsaBound);
        
        HRESULT hr;
        try {
            for (long i = 0; i < nCount; i++)
            {
                VARIANT statVariant;
                VariantClear(&statVariant);
                statVariant.vt = VT_UNKNOWN;
                statVariant.punkVal=pObjUnkArray[i];
                hr = SafeArrayPutElement(pStatUnkArray->parray, &i, &statVariant);
                                
                VARIANT dynamicPMArray;
                VariantClear(&dynamicPMArray);
                dynamicPMArray.vt = VT_ARRAY | VT_VARIANT;
                SAFEARRAYBOUND dynamicBound;
                dynamicBound.lLbound = 0L;
                dynamicBound.cElements = 1L;
                dynamicPMArray.parray = SafeArrayCreate(VT_VARIANT, 1, &dynamicBound);
                
                VARIANT statVariant2;
                VariantClear(&statVariant2);
                statVariant2.vt = VT_UNKNOWN;
                statVariant2.punkVal=NULL;
                long bound=0;
                hr=SafeArrayPutElement(dynamicPMArray.parray, &bound,&statVariant2);

                hr=SafeArrayPutElement(pDynPMUnkArrays->parray, &i, &dynamicPMArray);
            }
        }
        catch(int)
		{
            return FALSE;
        }
        return TRUE;
    }

    // XML Persistence helper functions...

    BOOL GetAttribute(MSXML::IXMLDOMNode* pNode, 
                    LPCWSTR pszAttName, 
                    MSXML::IXMLDOMAttribute** ppChild)
    {
        if (ppChild == NULL)
            return FALSE;

        *ppChild = NULL;

        if (pNode == NULL || pszAttName == NULL)
            return FALSE;

        // Read the attributes of the item
        //
        MSXML::IXMLDOMNamedNodeMapPtr pAttributes;
        pNode->get_attributes(&pAttributes);
        if (pAttributes == NULL) {
            // Wrong node type...
            return FALSE;
        }

        long nCount;
        pAttributes->get_length(&nCount);
        if (nCount < 1) {
            return FALSE;
        }

        MSXML::IXMLDOMAttributePtr pAttr;
        pAttr = pAttributes->getNamedItem(_bstr_t(pszAttName));
        if (pAttr == NULL) {
            // The named attribute is not found
            return FALSE;
        }

        *ppChild = pAttr.GetInterfacePtr();

        // AddRef before returning
        if (*ppChild != NULL)
            (*ppChild)->AddRef();

        return TRUE;
    }

    BOOL GetChildNode(MSXML::IXMLDOMNode* pNode, 
                    LPCWSTR pszNodeName, 
                    MSXML::IXMLDOMNode** ppChild)
    {
        try {
            if (ppChild == NULL)
                return FALSE;

            *ppChild = NULL;

            if (pNode == NULL || pszNodeName == NULL)
                return FALSE;

            // Get the named child element from the list of children
            //
            MSXML::IXMLDOMNodeListPtr pChildren; 
            pNode->get_childNodes(&pChildren);
            if (pChildren == NULL) {
                return FALSE;
            }

            int nCount = pChildren->Getlength();
            if (nCount < 1) {
                // No children
                return FALSE;
            }

            for (long i=0; i<nCount; i++) {
                MSXML::IXMLDOMNodePtr pNode;
                pChildren->get_item(i, &pNode);
                CComBSTR bstrName;
                pNode->get_nodeName(&bstrName);

                COLE2T szName(bstrName);
                if(wcscmp(szName,pszNodeName) == 0) {
                    *ppChild = pNode.GetInterfacePtr();
                    // AddRef before returning
                    if (*ppChild != NULL)
                        (*ppChild)->AddRef();
                    return TRUE;
                }
            }
        } catch (_com_error  &e) {
            SetLastError(e.Error());
            return FALSE;
        } catch(...)
		{
            return FALSE;
        }
        // Named child not found
        return FALSE;
    }

    BOOL GetChildNodeValue(MSXML::IXMLDOMNode* pNode, 
                        LPCWSTR pszNodeName, 
                        LPWSTR pszValue)
    {
        try {
            if (pNode == NULL || pszNodeName == NULL)
                return FALSE;

            MSXML::IXMLDOMNodePtr pChild;
            if (!GetChildNode(pNode, pszNodeName, &pChild)) {
                // Child not found
                return FALSE;
            }

            CComVariant val;
            HRESULT hr = S_OK;
            if (pChild->hasChildNodes()) {
                // Get the text child and then get the value so that we can get the 
                // text whether the node has the text directly or as cdata.
                //
                MSXML::IXMLDOMNodePtr pText;
                pChild->get_firstChild(&pText);
            
                hr = pText->get_nodeValue(&val);

            } else {
                // Get the node value directly
                hr = pChild->get_nodeValue(&val);
            }

            if (FAILED(hr))
                return FALSE;

            if (val.vt != VT_NULL) {
                // Node value data type should be string
                if (val.vt != VT_BSTR)
                    return FALSE;

                pszValue = COLE2T(val.bstrVal);
            }
        } catch (_com_error  &e) {
            SetLastError(e.Error());
            return FALSE;
        } catch(...) {
            return FALSE;
        }
        return TRUE;
    }

    BOOL AddChildNode(MSXML::IXMLDOMNode* pNode, 
                LPCWSTR pszChildNodeName,
                short nNodeType,
                MSXML::IXMLDOMNode** ppChild
                )
    {

        try {
            if (ppChild == NULL)
                return FALSE;

            *ppChild = NULL;

            if (pNode == NULL || pszChildNodeName == NULL)
                return FALSE;

            MSXML::IXMLDOMDocumentPtr pDoc;
            MSXML::DOMNodeType type;
            pNode->get_nodeType(&type);
            if (type == MSXML::NODE_DOCUMENT)
                pDoc = pNode;
            else {
                pNode->get_ownerDocument(&pDoc);
                if (pDoc == NULL)
                    return FALSE;
            }

            _variant_t varType(nNodeType);
            _bstr_t varName(pszChildNodeName);
         
            MSXML::IXMLDOMNodePtr pNewNode = pDoc->createNode(varType, varName, L"");;
            *ppChild = pNewNode.GetInterfacePtr();
            // AddRef before returning
            if (*ppChild != NULL)
                (*ppChild)->AddRef();

            pNode->appendChild(*ppChild);
        } catch (_com_error  &e) {
            SetLastError(e.Error());
            return FALSE;
        } catch(...) {
            return FALSE;
        }
        return TRUE;
    }

    BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode,
                        LPCWSTR pszAttName,
                        VARIANT& var)
    {
        if (! pNode || !pszAttName)
            return FALSE;

        MSXML::IXMLDOMAttributePtr pAttr;
        if (!GetAttribute(pNode, pszAttName, &pAttr))
            return FALSE;

        HRESULT hr = pAttr->get_value(&var); // Retrieve the value into the VARIANT.  VT Type will be discovered automatically.
        return TRUE;
    }

    BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                        LPCWSTR pszAttName, 
                        long& lValue)
    {
        lValue = 0;

        if (pNode == NULL || pszAttName == NULL)
            return FALSE;

        MSXML::IXMLDOMAttributePtr pAttr;
        if (!GetAttribute(pNode, pszAttName, &pAttr))
            return FALSE;

        CComVariant val;
        HRESULT hr = pAttr->get_value(&val);

        if (val.vt == VT_BSTR) {
            lValue = _tstol(COLE2T(val.bstrVal));
        } else {
            lValue = val.lVal;
        }
        return TRUE;
    }

    template <size_t nSize> inline
    BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode,
        LPCWSTR pszAttName,
        WCHAR (&pszValue)[nSize]){
        return GetAttributeValue(pNode, pszAttName, pszValue, nSize);
    }

    BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                        LPCWSTR pszAttName, 
                        LPWSTR pszValue,
                        size_t nSize)
    {
        if (pNode == NULL || pszAttName == NULL)
            return FALSE;

        MSXML::IXMLDOMAttributePtr pAttr;
        if (!GetAttribute(pNode, pszAttName, &pAttr))
            return FALSE;

        CComVariant val;
        HRESULT hr = pAttr->get_value(&val);

        CComBSTR bstr(val.bstrVal);
        COLE2T szValue(bstr);
        
        wcscpy_s(pszValue, nSize, szValue);
        return TRUE;
    }

    BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                        LPCWSTR pszAttName, 
        short& sValue)
    {
        try {
            sValue = 0;

            if (pNode == NULL || pszAttName == NULL)
                return FALSE;

            MSXML::IXMLDOMAttributePtr pAttr;
            if (!GetAttribute(pNode, pszAttName, &pAttr))
                return FALSE;

            CComVariant val;
            HRESULT hr = pAttr->get_value(&val);

            if(val.vt == VT_BSTR){
                sValue = _tstoi(COLE2T(val.bstrVal));
            } else {
                sValue = 0;
            }
        } catch (_com_error  &e) {
            SetLastError(e.Error());
            return FALSE;
        } catch(...) {
            return FALSE;
        }

        return TRUE;
    }

    BOOL GetAttributeValue(MSXML::IXMLDOMNode* pNode, 
        LPCWSTR pszAttName, 
                        double& fValue)
    {
        try {
            fValue = 0.0;

            if (pNode == NULL || pszAttName == NULL)
                return FALSE;

            MSXML::IXMLDOMAttributePtr pAttr;
            if (!GetAttribute(pNode, pszAttName, &pAttr))
                return FALSE;

            CComVariant val;
            HRESULT hr = pAttr->get_value(&val);

            if(val.vt == VT_BSTR){
                fValue = _tstof(CW2T(val.bstrVal));
            } else {
                fValue = 0.0;
            }
        } catch (_com_error  &e) {
            SetLastError(e.Error());
            return FALSE;
        } catch(...) {
            return FALSE;
        }


        return TRUE;
    }

    inline BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                                LPCWSTR pszAttName, 
                                double fValue)
    {
        MSXML::IXMLDOMElementPtr pElement = pNode;

        if (pNode == NULL || pElement == NULL || pszAttName == NULL)
            return FALSE;

        CComVariant var(fValue);
        HRESULT hr = pElement->setAttribute(pszAttName, var);
        
        return SUCCEEDED(hr);
    }

    virtual BOOL LoadPropertyValue(MSXML::IXMLDOMNode* pNode, 
                                int index)
    {
        // Retrieves the indexed property value from XML, and marshals it via COM to the tool.
        
        VARIANT vValue;
        VariantInit(&vValue);

        // Note:  Here, index is 1 based, and should match the DISPIDs for each property.

        if(dispColor==index)
        {
            // XML doesn't support persisting Dispatch pointers, so we must persist the Color, ColorName and
            // BookName directly here.
            MSXML::IXMLDOMNodePtr pColorNode,pColorBookNode;
                            
            if(GetChildNode(pNode, L"TrueColor",&pColorNode))
            {
                // \ TrueColor
                if(GetChildNode(pColorNode,L"ColorValue",&pColorBookNode))
                {
                    // \TrueColor\colorValue
                    GetAttributeValue(pColorBookNode, L"Unspecified", (long&)m_bColorUnspecified);
                    long color;
                    GetAttributeValue(pColorBookNode, L"Color", color);
                    m_Color.setColor(color);
                }
                WCHAR sColorName[512]={_T("")},sColorBook[512]={_T("")};
                if(GetChildNode(pColorNode,_T("ColorName"),&pColorBookNode))
                    // \TrueColor\ColorName
                    GetAttributeValue(pColorBookNode, L"Color", sColorName);
                if(GetChildNode(pColorNode,L"ColorBook",&pColorBookNode))
                    // \TrueColor\ColorBook
                    GetAttributeValue(pColorBookNode, L"Color", sColorBook);
                
                // We could wrap this value in the VARIANT as a dispatch pointer, and pass it through,
                // but it would only ultimately set the m_Color variable as we do here next.  
                // The Dispatch pointer is only really important when we marshal the color back into 
                // the Property Inspector.
                const WCHAR* pNullName = NULL;
                m_Color.setNames( wcslen(sColorName) ? sColorName : pNullName, 
                    wcslen(sColorBook) ? sColorBook : pNullName);
            }
            return TRUE;
        }
        
        if(dispLayer == index) 
            GetAttributeValue(pNode, L"Unspecified", (long&)m_bLayerUnspecified);
        
        GetAttributeValue(pNode,L"PropertyValue",vValue); // Get the value from the XML file through the VARIANT.

        PutToolProperty(index,vValue);// Place the value into the member variable in the child interface.
        return TRUE;
    }

    virtual BOOL SavePropertyValue(MSXML::IXMLDOMNode* pNode,
                                int index)
    {
        // Sets the XML for the indexed property.
        
        VARIANT vValue;
        VariantInit(&vValue);
        HRESULT hr=GetToolProperty(index,vValue);

        // Note:  Here, index is 1 based, and should match the DISPIDs for each property.

        if(dispColor==index)
        {
            // XML doesn't support persisting Dispatch pointers, so we must persist the Color, ColorName and
            // BookName directly here.
            
            // \ TrueColor
            MSXML::IXMLDOMNodePtr pColorNode,pColorBookNode;
            if(!GetChildNode(pNode,L"TrueColor",&pColorNode))
                AddChildNode(pNode, L"TrueColor", MSXML::NODE_ELEMENT, &pColorNode);
            if (pColorNode == NULL)
                return FALSE;

            // \TrueColor \ColorValue
            if(!GetChildNode(pColorNode,L"ColorValue",&pColorBookNode))
                AddChildNode(pColorNode, L"ColorValue", MSXML::NODE_ELEMENT, &pColorBookNode);
            SetAttributeValue(pColorBookNode, L"Unspecified", (long&)m_bColorUnspecified);
            long color=m_Color.color();
            SetAttributeValue(pColorBookNode, L"Color",color);

            LPWSTR pColorName = (LPWSTR)m_Color.colorName();
            if (pColorName) 
            {
                // \TrueColor\ColorName
                if(!GetChildNode(pColorNode,L"ColorName",&pColorBookNode))			
                    AddChildNode(pColorNode, L"ColorName", MSXML::NODE_ELEMENT, &pColorBookNode);
                SetAttributeValue(pColorBookNode,L"Color",pColorName);
            }

            LPWSTR pBookName = (LPWSTR)m_Color.bookName();
            if(pBookName) 
            {
                // \TrueColor\ColorBook
                if(!GetChildNode(pColorNode,L"ColorBook",&pColorBookNode))
                    AddChildNode(pColorNode, L"ColorBook",MSXML::NODE_ELEMENT, &pColorBookNode);
                SetAttributeValue(pColorBookNode,L"Color",pBookName);
            }
            return TRUE;
        }
        
        // Set the unspecified state for the Layer control.
        if(dispLayer==index)
            SetAttributeValue(pNode, L"Unspecified", (long)m_bLayerUnspecified);
        
        return SetAttributeValue(pNode,L"PropertyValue",vValue); // Set the value in the XML file through the VARIANT.
    }

    BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                                LPCWSTR pszAttName, 
                                long lValue)
    {
        MSXML::IXMLDOMElementPtr pElement = pNode;

        if (pNode == NULL || pElement == NULL || pszAttName == NULL)
            return FALSE;

        CComVariant var(lValue);
        HRESULT hr = pElement->setAttribute(pszAttName, var);

        return SUCCEEDED(hr);
    }

    BOOL SetAttributeValue(MSXML::IXMLDOMNode *pNode,
                                LPCWSTR pszAttName,
                                VARIANT& var)
    {
        MSXML::IXMLDOMElementPtr pElement = pNode;

        if (pNode == NULL || pElement == NULL || pszAttName == NULL)
            return FALSE;

        HRESULT hr = pElement->setAttribute(pszAttName, &var);

        return SUCCEEDED(hr);
    }

    BOOL SetAttributeValue(MSXML::IXMLDOMNode* pNode, 
                                LPCWSTR pszAttName, 
                                LPWSTR pszValue)
    {
        MSXML::IXMLDOMElementPtr pElement = pNode;

        if (pNode == NULL || pElement == NULL || pszAttName == NULL)
            return FALSE;

        CComVariant var(pszValue);
        HRESULT hr = pElement->setAttribute(pszAttName, var);

        return SUCCEEDED(hr);
    }


    BOOL RemoveChildren(MSXML::IXMLDOMNode* pNode)
    {
        try {
            if (pNode == NULL)
                return FALSE;

            MSXML::IXMLDOMNodeListPtr pChildren; 
            HRESULT hr = pNode->get_childNodes(&pChildren);
            if ( FAILED(hr) || (pChildren == NULL))
                return FALSE;

            MSXML::IXMLDOMNodePtr pChildNode = pChildren->nextNode();
            for (; pChildNode != NULL; pChildNode = pChildren->nextNode()){
                MSXML::IXMLDOMNodePtr pRemove = pNode->removeChild(pChildNode);
                // Release it
                pRemove = NULL;
            }
        } catch (_com_error  &e) {
            SetLastError(e.Error());
            return FALSE;
        } catch(...) {
            return FALSE;
        }
        return TRUE;
    }

    // ******************************************************
	// Catalog, Palette and Tool creation helper functions...
    
    AcTcPalette *CreatePaletteATC(AcTcCatalog *pCatalog,LPWSTR szPaletteName)
    {
        GUID guid;
        
        // Create a Palette...
        
        if(!SUCCEEDED(CoCreateGuid(&guid)))
            return NULL;
        AcTcPalette *pPalette = new AcTcPalette;
		try
		{
			if(!pPalette->SetID(&guid))
				throw 0;
			if(!pPalette->SetName(szPaletteName))
				throw 0;
			if(-1 == pCatalog->AddChild(pPalette))
				throw 0;
		}
		catch (int)
		{
			delete pPalette;
			return NULL;
		}
		try
		{
			if(!pCatalog->SetToolTipText(szPaletteName))
				throw 0;
			if(!pCatalog->SetDescription(szPaletteName))
				throw 0;
			if(!AcTcGetManager()->SaveCatalogs())
				throw 0;
		}
		catch(int)
		{
			pCatalog->DeleteChild(pPalette);
			return NULL;
		}
        return pPalette;
    }

    AcTcTool *CreateToolATC(AcTcPackage *pPalette, LPCWSTR szToolNameOverride=NULL, 
        LPCWSTR szToolImageOverride=NULL,
        BOOL bImageFile=FALSE)
    {
        GUID guid;

        if(!SUCCEEDED(CoCreateGuid(&guid)))
            return NULL;

		// Add a tool to the palette.
        AcTcTool* pTool = new AcTcTool();
        try
		{
			if(!pTool->SetID(&guid))
				throw 0;
			if(!pTool->SetStockToolID(pclsid))
				throw 0;

			// Attach the tool icon to the tool...
			AcTcImage image;
			HBITMAP hBitmap=NULL;
			if(szToolImageOverride)
			{
				if(bImageFile)
					hBitmap=(HBITMAP)::LoadImage(
					NULL, szToolImageOverride, IMAGE_BITMAP,
					0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);          
				else
					hBitmap=::LoadBitmap(_AtlBaseModule.GetResourceInstance(),szToolImageOverride);
			}
			else
				hBitmap=::LoadBitmap(_AtlBaseModule.GetResourceInstance(),szToolImage);
			image.Load(hBitmap);
	        
			AcTcImageList *pList=pTool->GetImageList();
			if(!pList)
				throw 0;

			pList->Add(&image);
	            
			if(szToolNameOverride)
			{
				if(!pTool->SetName(szToolNameOverride))
					throw 0;
				if(!pTool->SetToolTipText(szToolNameOverride))
					throw 0;
				if(!pTool->SetDescription(szToolNameOverride))
					throw 0;
			}
			else
			{
				if(!pTool->SetName(szToolName))
					throw 0;
				if(!pTool->SetToolTipText(szToolName))
					throw 0;
				if(!pTool->SetDescription(szToolName))
					throw 0;
			}

			if(!pTool->SetToolType(AcTc::kToolNormal))
				throw 0;
	        
			// Coerce the tool to persist itself (via Save())
			IUnknown *pUnk=NULL;
			MSXML::IXMLDOMNode* pToolData;
			if(!pTool->GetToolData((IUnknown**)&pToolData))
				throw 0;
			if(!SUCCEEDED(GetPropertyTypeInfo()))
				throw 0;
			if(!SUCCEEDED(Save(pToolData)))
				throw 0;

			if(-1 == pPalette->AddChild(pTool))
				throw 0;

		}
		catch(int)
		{
			delete pTool;
			return NULL;
		}
        
		try
		{

			if(!AcTcGetManager()->SaveCatalogs())
				throw 0;
			if(!AcTcGetManager()->SaveCatalogs(AcTc::kShapeCatalog))// Save in case pPalette is a shape package.
				throw 0;
		}
		catch(int)
		{
			pPalette->DeleteChild(pTool);
			return NULL;
		}
        return pTool;
    }

    AcTcTool *CreateFlyoutToolATC(AcTcPackage *pPalette, AcTcPackage *pShapePackage, LPCWSTR szToolNameOverride=NULL)
    {
        GUID toolGUID;

        // Add a tool to the palette.
        AcTcTool* pTool = new AcTcTool();
		try
		{
			if(!SUCCEEDED(CoCreateGuid(&toolGUID)))
				throw 0;
			if(!pTool->SetID(&toolGUID))
				throw 0;
			if(!pTool->SetStockToolID(pclsid))
				throw 0;
			if(szToolNameOverride)
			{
				if(!pTool->SetName(szToolNameOverride))
					throw 0;
				if(!pTool->SetToolTipText(szToolNameOverride))
					throw 0;
				if(!pTool->SetDescription(szToolNameOverride))
					throw 0;
			}
			else
			{
				if(!pTool->SetName(szToolName))
					throw 0;
				if(!pTool->SetToolTipText(szToolName))
					throw 0;
				if(!pTool->SetDescription(szToolName))
					throw 0;
			}

			if(!pTool->SetToolType(AcTc::kToolFlyout))
				throw 0;
			if(!pTool->EnableFlyout(TRUE))
				throw 0;
	        
			if(!pTool->SetShapePackage(pShapePackage))
				throw 0;
	        
			// Coerce the tool to persist itself (via Save()) with the values set witin the New() override.
			IUnknown *pUnk=NULL;
			MSXML::IXMLDOMNode* pToolData;
			if(!pTool->GetToolData((IUnknown**)&pToolData))
				throw 0;
			if(!SUCCEEDED(GetPropertyTypeInfo()))
				throw 0;
			if(!SUCCEEDED(Save(pToolData)))
				throw 0;

			if(-1 == pPalette->AddChild(pTool))
				throw 0;
		}
		catch(int)
		{
			delete pTool;
			return NULL;
		}

		// APIs Exist to specify programatically which tools appear in the flyout list.  Here is a commented example
		// (This snippet simply adds all the tools in the shape package to the active list):
		/*
		AcTcTool *shapeToolsArray[32];
		for(int i=0;i<(pShapePackage->GetChildCount() )&& i<32;i++)
			shapeToolsArray[i]=(AcTcTool*)pShapePackage->GetChild(i);
		bResult=pTool->SetActiveShapes((AcTcCatalogItem**)shapeToolsArray,pShapePackage->GetChildCount());
                
		// We must now add the 'ActiveShapes' entries into the CustomData ATC section for the shape package with each tool's ID that we select.
		CComPtr<IUnknown> pCustomDataUnk;    
		MSXML::IXMLDOMNodePtr pChild;
		if( pShapePackage->GetCustomData(&pCustomDataUnk) )
		{
			CComQIPtr<MSXML::IXMLDOMNode> pCustomDataNode =pCustomDataUnk;
            
			MSXML::IXMLDOMNodePtr pActiveShape;
			//If the active shapes does not exist create one
			if(!GetChildNode(pCustomDataNode,L"ActiveShapes",&pActiveShape))
				AddChildNode(pCustomDataNode,L"ActiveShapes",MSXML::NODE_ELEMENT,&pActiveShape);
			for(int i=0;i<pShapePackage->GetChildCount();i++)
			{
				GUID shapeGUID;
				pShapePackage->GetChild(i)->GetID(&shapeGUID);
				CComVariant varGUID(shapeGUID);
				AddChildNode(pActiveShape,L"Shape",MSXML::NODE_ELEMENT,&pChild);
				SetAttributeValue(pChild,L"idValue",varGUID);
			}
		}
		*/
		try
		{
			if(!AcTcGetManager()->SaveCatalogs())
				throw 0;
			if(!AcTcGetManager()->SaveCatalogs(AcTc::kShapeCatalog))
				throw 0;
		}
		catch(int)
		{
			pPalette->DeleteChild(pTool);
			return NULL;
		}
        return pTool;
    }

    AcTcTool *CreateCommandToolATC(AcTcPackage *pPalette,LPWSTR szToolName,LPCWSTR szBitmapName, LPWSTR macroString)
    {
        // Add a basic COMMAND tool to the catalog to demonstrate how to create generic tools 
        // to run Acad commands.  Note, this does not require a COM object to use.
        
        GUID guid;
        BOOL bResult;

        AcTcTool *pTool = new AcTcTool();
		try
		{
			if(!SUCCEEDED(CoCreateGuid(&guid)))
				throw 0;
			if(!pTool->SetID(&guid))
				throw 0;
	        
			const GUID GenericStockToolId = {0x2ae7120b,0xcee4,0x47a5,{0x9b,0x50,0xef,0x9f,0x3a,0xde,0x24,0xac}};
			if(!pTool->SetStockToolID(&GenericStockToolId))
				throw 0;
			if(!pTool->SetName(szToolName))
				throw 0;
	        
			// Attach a separate tool icon to this tool.
			AcTcImage image;
			AcTcImageList *pList=pTool->GetImageList();	
			if(!pList)
				throw 0;
	        
			HBITMAP hBitmap=::LoadBitmap(_AtlBaseModule.GetResourceInstance(),szBitmapName);
	        
			bResult=image.Load(hBitmap);
			pList->Add(&image);
	            
			// Now add the entry to represents the string passed to the commandline when this tool is run.
			CComPtr<IUnknown>pToolDataUnk;
			MSXML::IXMLDOMNodePtr pToolData;
			if(pTool->GetToolData(&pToolDataUnk))
			{
				CComQIPtr<MSXML::IXMLDOMNode> pToolData=pToolDataUnk;
				RemoveChildren(pToolData);
				MSXML::IXMLDOMNodePtr pNode,pNodeText;
				if(TRUE == AddChildNode(pToolData, L"Macro", MSXML::NODE_ELEMENT, &pNode))
					if(TRUE == AddChildNode(pNode, L"", MSXML::NODE_CDATA_SECTION, &pNodeText))
						pNodeText->put_text(CComBSTR(macroString));
			}
			else
				throw 0;

			if(-1 == pPalette->AddChild(pTool))
				throw 0;
		}
		catch(int)
		{
			delete pTool;
			return NULL;
		}
        try
		{
			if(!AcTcGetManager()->SaveCatalogs())// AutoCAD will create the correct ATC files within the roamable profile folder.
				throw 0;
			if(!AcTcGetManager()->SaveCatalogs(AcTc::kShapeCatalog))
				throw 0;
		}
		catch(int)
		{
			pPalette->DeleteChild(pTool);
			return NULL;
		}
        return pTool;
    }

    AcTcCatalog *CreateStockToolATC(LPWSTR szCatalogName)
    {
        // Set the module handle so we can use the resources within this ARX for the tool icons.
        CAcModuleResourceOverride resourceOverride;
        
        GUID guid;

        // Create the stock tool catalog entry:
        AcTcStockTool *pStockTool=new AcTcStockTool;
		AcTcCatalog *pStockToolCatalog=new AcTcCatalog;
		try
		{
			if(!pStockTool->SetID(pclsid))
				throw 0;

			if(!pStockTool->SetComClassID(*pclsid))
				throw 0;

			// Set the module file name for the Stock Tool's COM interface object: modulePath set in initialize()...
			WCHAR modulePath[MAX_PATH];
			HINSTANCE hInst=_AtlBaseModule.GetResourceInstance();
			HMODULE moduleHandle=hInst;
			if(!moduleHandle)
				throw 0;

			GetModuleFileName(hInst,modulePath,MAX_PATH);
			if(!pStockTool->SetModuleFileName(modulePath))
				throw 0;
	            
			// Allow the framework to handle the StockTool now...
			if(-1 == pStockToolCatalog->AddChild(pStockTool))
				throw 0;
            else {
                // the catalog now owns this object and will delete it when
                // the catalog is deleted. So, we set pStockTool to nullptr
                // to prevent it being double deleted in the catch(int)s
                // below.
                //
                pStockTool = nullptr;
			}

			if(-1 == AcTcGetManager()->AddStockToolCatalog(pStockToolCatalog))
				throw 0;
		}
		catch(int)
		{
			delete pStockToolCatalog;
			delete pStockTool;
			return NULL;
		}
		AcTcCatalog *pCatalog=new AcTcCatalog;
		try
		{
			// Create the tool catalog entry.
			if(!SUCCEEDED(CoCreateGuid(&guid)))
				throw 0;
			if(!pCatalog->SetID(&guid))
				throw 0;
			if(!pCatalog->SetName(szCatalogName))
				throw 0;

			if(-1 ==AcTcGetManager()->AddCatalog(pCatalog))
				throw 0;

			if(!AcTcGetManager()->SaveCatalogs())
				throw 0;

			if(!AcTcGetManager()->SaveCatalogs(AcTc::kStockToolCatalog))
				throw 0;
		}
		catch(int)
		{
			delete pStockToolCatalog;
			delete pCatalog;
			return NULL;
		}

        return pCatalog;
    }

    AcTcPackage *CreateShapeCatalogATC(LPWSTR szShapeName)
    {
        AcTcManager *pManager = AcTcGetManager();
        AcTcCatalog *pShapesCatalog = NULL;
        if(pManager)
        {
            pShapesCatalog = (AcTcCatalog *)pManager->GetShapeCatalog();
            if(!pShapesCatalog)
                return NULL;
        }
        else
            return NULL;
        //if the package does not exist create one new package
        AcTcPackage *pPackage=GetCustomShapePackage(pShapesCatalog,szShapeName);
        if (NULL==pPackage)
        {
            pPackage = new AcTcPackage;
            try
			{
				if(!pPackage->SetName(szShapeName))
					throw 0;
				GUID shapeGuid;
				if(!SUCCEEDED(CoCreateGuid(&shapeGuid)))
					throw 0;
				if(!pPackage->SetID(&shapeGuid))
					throw 0;
				if(-1 == pShapesCatalog->AddChild(pPackage))
					throw 0;
			}
			catch(int)
			{
				delete pPackage;
				return NULL;
			}
        }
        if(!AcTcGetManager()->SaveCatalogs(AcTc::kShapeCatalog))
		{
			pShapesCatalog->DeleteChild(pPackage);
			return NULL;
		}
        return pPackage;
    }
    
    IAcadToolProperties* GetThisToolsProperties()
    {
        AcadToolImpl<TT,T,pclsid,szToolName,szToolImage>* pThisTool=(AcadToolImpl<TT,T,pclsid,szToolName,szToolImage>*)pAcadToolImpl;
        
        CComQIPtr<IAcadTool> pAcadTool(pThisTool);
        if (!pAcadTool)
            return NULL;  

        CComPtr<IUnknown> pUnkToolProp;
        HRESULT hr = pAcadTool->GetToolProperties(&pUnkToolProp);
        if (FAILED(hr)) 
            return NULL;

        CComQIPtr<IAcadToolProperties> pToolProp(pUnkToolProp);
        if(!pToolProp)
            return NULL;

        return pToolProp;
    }
    
    AcTcPackage* GetCustomShapePackage(AcTcCatalog *pCatalog,
                            LPCWSTR szPackageName)
    {
        if(!pCatalog)
            return NULL;
        AcTcPackage *pPackage = NULL;
        for(int i=0;i<pCatalog->GetChildCount();i++)
        {
            pPackage=(AcTcPackage *)pCatalog->GetChild(i);
            if(pPackage)
            {
                WCHAR szPackageNameEnum[128];
                pPackage->GetName(szPackageNameEnum,128);
                if(!wcscmp(szPackageName,szPackageNameEnum))
                    return pPackage;
            }
        }	
        return NULL;
    }
    AcTcPackage* GetCustomShapePackage(AcTcCatalog *pCatalog,
                            GUID szPackageID)
    {
        if(!pCatalog)
            return NULL;
        AcTcPackage *pPackage = NULL;
        for(int i=0;i<pCatalog->GetChildCount();i++)
        {
            pPackage=(AcTcPackage *)pCatalog->GetChild(i);
            if(pPackage)
            {
                GUID szPackageIdEnum;
                pPackage->GetID(szPackageIdEnum);
                if(IsEqualGuid(szPackageId,szPackageIdEnum))
                    return pPackage;
            }
        }	
        return NULL;
    }
};


