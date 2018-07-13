//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Directions for use:
//
// Derive from the AsdkPromptBase class in a separate cpp/h set. The arguments to the 
// template function are:
//
//		AsdkPromptBase<WrapperInterface, &WrapperCLSID>
//
//		e.g.: 
//		class CEmployeePromptClass : public AsdkPromptBase<IEmployeeWrap, &CLSID_EmployeeWrap>
//
//
// Within the child class definition, create the PROMPT_MAP. Example:
//
//	BEGIN_PROMPT_MAP(CChildClassName)
//		PROMPT_ENTRY("Cube", DISPID_CUBE, RTLONG, IDS_CUBE_DEFAULT, IDS_CUBE_PROMPT_STRING, false)
//		PROMPT_ENTRY("Id", DISPID_ID, RTLONG, IDS_ID_DEFAULT, IDS_ID_PROMPT_STRING, false)
//	END_PROMPT_MAP
//
//
// The format for the PROMPT_ENTRY is:
//	PROMPT_ENTRY(
//		L"DESCRIPTION",		- String describing the entry
//		DISPID,					- The DISPID for this property in the wrapper
//		PROMPT_TYPE,			- The type of input expected within the command loop
//		DEFAULT_VALUE,			- A string indicating the default (for arrays, separate by comma e.g. "10,10,10")
//		COMMANDLINE_PROMPT,		- String to prompt the user at the commandline
//		JIG-ABLE_PROPERTY)		- Boolean indicating whether to use an acedGetXXX() or a Jig to retrieve this property value
//
//	PROMPT_ENTRY_INITGET(
//		L"DESCRIPTION",		- String describing the entry
//		DISPID,					- The DISPID for this property in the wrapper
//		PROMPT_TYPE,			- The type of input expected within the command loop
//		INITGET,				- Specify initget value
//		KEYWORDS,				- A string specifying the keywords to use in initget
//		DEFAULT_VALUE,			- A string indicating the default (for arrays, separate by comma e.g. "10,10,10")
//		COMMANDLINE_PROMPT,		- String to prompt the user at the commandline
//		JIG-ABLE_PROPERTY)		- Boolean indicating whether to use an acedGetXXX() or a Jig to retrieve this property value
//
//	PROMPT_ENTRY_SYMBOL(
//		L"DESCRIPTION",		- String describing the entry
//		DISPID,					- The DISPID for this property in the wrapper
//		DEFAULT_VALUE,			- A string indicating the default (for arrays, separate by comma e.g. "10,10,10")
//		COMMANDLINE_PROMPT,		- String to prompt the user at the commandline
//		JIG-ABLE_PROPERTY)		- Boolean indicating whether to use an acedGetXXX() or a Jig to retrieve this property value
//
//
// PROMPTTYPE can be one of the following (defined in adscodes.h)
//		RTREAL, RTPOINT, RTSHORT, RTANG, RTSTR, RT3DPOINT, RTLONG, RTENAME
//
//
// Now define the DEFINE_SAMPLER macro to specify the type of input allowed
// (see AcEdJig::sampler for details)
//		Example:
//			DEFINE_SAMPLER(
//				AcEdJig::kCrosshair,
//				(UserInputControls)(kNullResponseAccepted| kAccept3dCoordinates));
//
// Finally, provide an implementation for GetResourceHandle(). In this function 
// return the resource handle where the prompt class can find string definition 
// defined in the prompt MAP
//
//		virtual HINSTANCE GetResourceInstance ()
//
//
// Instantiation:
//
// To use the new prompt object, create a command using ACRX_CMD_INTERRUPTIBLE 
// flag to support modeless operation. Instantiate the prompt child 
// within the command using CComObject (to implement IUnknown), and 
// call promptLoop():
//
//		CComObject<CEmployeePromptClass> prompt ;
//		prompt.promptLoop () ;
//
// promptLoop() returns the AcDbObjectId of the value appended to the 
// database upon completion of the command. You may modify this entity 
// using this id as necessary after the promptLoop() has completed.
//
//
// Customization by using the callbacks:
//			
// Virtual callbacks are defined to allow customization beyond the MAP. They are:
//
// virtual void constructorCallback ()
//	- Called only once after initial construction.
//
// virtual int promptCallback (int index)
//	- Called in a loop to proceed with data acquisition prompt for types
//	  which aren't supported by the AsdkPromptBase class. Or in case you want to 
//	  provide the data acquisition prompt yourself.
//	  Returning RTINPUTTRUNCATED tells the prompt class to proceed with the MAP
//	  definition. Returning any other value like: RTCAN / RTNORM / RTKWORD / ...
//	  tells the prompt class that you proceeded data acquisition prompt yourself.
//
// virtual AcEdJig::DragStatus samplerCallback (int index, bool &compareChange)
//	- Called in a loop to proceed with data acquisition for types which aren't
//	  supported by the AsdkPromptBase class. Or in case you want to provide the 
//	  data acquisition yourself.
//	  Returning kOther tells the prompt class to proceed with the MAP
//	  definition. Returning any other value like: kCancel / kNormal / kNoChange / ...
//	  tells the prompt class that you proceeded data yourself.
//
// virtual bool updateCallback (int index)
//	- Called in a loop to update entity after data acquisition.
//	  Returning false tells the prompt class to proceed with the default implementation.
//	  Returning true means you did it yourself.
//
// virtual bool keywordCallback (int index, TCHAR *kword, void *value)
//	- Called by the framework to proceed with keywords.
//	  Returning true tells the prompt class you proceeded the keyword and that
//	  you might have change the 'value'
//
//		JIG-ABLE_PROPERTY == true, kword is a AcEdJig::DragStatus* and not a string!
//			PROMPT_TYPE == RTREAL		value is a double*
//			PROMPT_TYPE == RTPOINT		value is an AcGePoint2d*
//			PROMPT_TYPE == RTSHORT			<impossible>
//			PROMPT_TYPE == RTANG		value is a double*
//			PROMPT_TYPE == RTSTR		value is a TCHAR*
//			PROMPT_TYPE == RT3DPOINT	value is an AcGePoint3d*
//			PROMPT_TYPE == RTLONG			<impossible>
//			PROMPT_TYPE == RTENAME			<impossible>
//
//		JIG-ABLE_PROPERTY == false, kword is a TCHAR* containing the specified keyword
//			PROMPT_TYPE == RTREAL		value is a double*
//			PROMPT_TYPE == RTPOINT		value is an ads_point
//			PROMPT_TYPE == RTSHORT		value is an int*
//			PROMPT_TYPE == RTANG		value is a double*
//			PROMPT_TYPE == RTSTR		value is a TCHAR*
//			PROMPT_TYPE == RT3DPOINT	value is an ads_point
//			PROMPT_TYPE == RTLONG		value is an int*
//			PROMPT_TYPE == RTENAME		value is an ads_name
//
// virtual bool defaultValueCallback (int index, LPWSTR szDefaultVal)
//	- Called by the prompt class to let application specifying a default value.
//	  Value is stored in the szDefaultVal parameter and must not exceed 132 characters
//	  including the null character.
//	  Returning false tells the prompt class to use the MAP definition. Returning true
//	  tells the prompt class you provided a value which will be used as the default value.
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include <string.h>
#include "dbjig.h"
#include "adscodes.h"

//-----------------------------------------------------------------------------
#define IDR_ASDKPROMPTBASE	700

//-----------------------------------------------------------------------------
BOOL acedSetIUnknownForCurrentCommand (const LPUNKNOWN) ;

//-----------------------------------------------------------------------------
struct PROMPT_MAP_ENTRY {
	LPCWSTR m_szDesc ;
	DISPID m_dispId ;
	int m_promptType ;
	int m_cronly ;
	int m_nInitget ;
	UINT m_nKeywords ;
	UINT m_nDefaultValue ;
	UINT m_nPrompt ;
	bool m_bJigThisProperty ;
	bool m_bGotThisProperty ;
	VARTYPE m_paramType ;
	VARIANT m_vValue ;
} ;

//-----------------------------------------------------------------------------
template <typename T, const GUID *TCLSIDWrapper>
class ATL_NO_VTABLE AsdkPromptBase :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<AsdkPromptBase<T,TCLSIDWrapper>, NULL>,
	public IPropertyNotifySink,
	public AcEdJig
{

protected:
	CComPtr<T> m_pWrapperObject ;
	CLSID m_CLSID_ObjectWrapper ;
	AcDbObject *m_pDbrObject ;
	DWORD m_dConnectionID ;
	CComQIPtr<IAcadBaseObject2> m_pBaseObj ;
	CComPtr<IConnectionPoint> m_pConPt ;
	AcDbDatabase *m_pDb ;
	AcApDocument *m_pDoc ;

	AcGePoint3d m_cursor3dPos, m_pos3d ;
	AcGePoint2d m_cursorPos, m_pos ;
	double m_cursorDist, m_dist ;
	double m_cursorAngle, m_angle ;
	TCHAR *m_szCursorString, *m_szString ;

	AcEdJig::CursorType m_jigCursorType ;
	AcEdJig::UserInputControls m_jigUserInputControls ;

	volatile LONG m_cRef ;

protected:
	AsdkPromptBase () : AcEdJig (),
		m_cursor3dPos(), m_pos3d(), m_cursorPos(), m_pos(),
		m_cursorDist(0), m_dist(0), m_cursorAngle(0), m_angle(0),
		m_szCursorString(NULL), m_szString(NULL)
	{
		//- Assigned here because CLSID_ObjectWrapper is used outside the class definition 
		//- in the macro defined for the child class constructor...
		m_CLSID_ObjectWrapper =*TCLSIDWrapper ;
	}

	virtual ~AsdkPromptBase () {}
	
	DECLARE_REGISTRY_RESOURCEID(IDR_ASDKPROMPTBASE) 
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(AsdkPromptBase)
		COM_INTERFACE_ENTRY(IPropertyNotifySink)
	END_COM_MAP() 

	HRESULT FinalConstruct () { return (S_OK) ; }
	void FinalRelease () {}
	virtual HINSTANCE GetResourceInstance () =0 ;
	void SetDocument (AcApDocument *pDoc) { m_pDoc =pDoc ; }

	//- Prompt MAP
	int GetPromptMapSize () {
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;
		int i =0 ;
		while ( pPromptMap [i].m_szDesc )
			i++ ;
		return (i) ;
	}
	virtual PROMPT_MAP_ENTRY *GetPromptMap () =0 ;

	//- Property callbacks for custom types
	virtual VARTYPE propertyTypeCallback (int index, VARTYPE varType) { return (varType) ; }
	virtual void setProperty (int index, VARIANT &var, long val) {
		if ( V_VT(&var) == VT_I4 )
			V_I4(&var) =val ;
		else if ( V_VT(&var) == VT_I2 )
			V_I2(&var) =static_cast<short>(val) ;
	}
	virtual void setProperty (int index, VARIANT &var, short val) {
		if ( V_VT(&var) == VT_I4 )
			V_I4(&var) =static_cast<long>(val) ;
		else if ( V_VT(&var) == VT_I2 )
			V_I2(&var) =val ;
	}
	virtual void setProperty (int index, VARIANT &var, double val) {
		if ( V_VT(&var) == VT_R8 )
			V_R8(&var) =val ;
		else if ( V_VT(&var) == VT_R4 )
			V_R4(&var) =static_cast<float>(val) ;
	}
	virtual void setProperty (int index, VARIANT &var, float val) {
		if ( V_VT(&var) == VT_R8 )
			V_R8(&var) =static_cast<double>(val) ;
		else if ( V_VT(&var) == VT_R4 )
			V_R4(&var) =val ;
	}
	virtual void setProperty (int index, VARIANT &var, TCHAR *val) {
		V_BSTR(&var) =_bstr_t (val).copy () ;
	}
	virtual void setProperty (int index, VARIANT &var, AcGePoint3d &val) {
		AcAxPoint3d pt (val) ;
		pt.setVariant (var) ; //- VT_ARRAY | VT_R8
	}
	virtual void setProperty (int index, VARIANT &var, AcGePoint2d &val) {
		AcAxPoint2d pt (val) ;
		pt.setVariant (var) ; //- VT_ARRAY | VT_R8
	}

	//- Property - COM
	HRESULT GetPropertyTypeInfo () {
		//- This function will grep the wrapper's type library to obtain the property type information for each DISPID we place in the map.  It 
		//- will use this information to pass the values we jig to and from the wrapper.  This function is called only once during construction, before
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;
		//- Find out if we have Type Info (we should have)
		unsigned int count =0 ;
		if ( !SUCCEEDED(m_pWrapperObject->GetTypeInfoCount (&count)) )
			return (E_FAIL) ;
		//- If no Type Info, exit
		if ( !count )
			return (E_FAIL) ; //- No properties to Jig ???
		//- Get iTypeInfo interface for object for any locale
		CComPtr<ITypeInfo> pTypeInfo ;
		if ( !SUCCEEDED (m_pWrapperObject->GetTypeInfo (0, NULL, &pTypeInfo)) )
			return (E_FAIL) ;
		//- Retrieve type attributes - to find number of methods for entity
		TYPEATTR *pTypeAttr ;
		if ( !SUCCEEDED (pTypeInfo->GetTypeAttr (&pTypeAttr)) )
			return (E_FAIL) ;
		int numFuncs =pTypeAttr->cFuncs ;
		pTypeInfo->ReleaseTypeAttr (pTypeAttr) ;
		//- Iterate over all methods.
		for ( int i =0 ; i < numFuncs ; i++ ) {
			//- Get the function description
			FUNCDESC *pFuncDesc ;
			if ( !SUCCEEDED (pTypeInfo->GetFuncDesc (i, &pFuncDesc)) )
				return (E_FAIL) ;
			//- Get the member ID
			MEMBERID memberID ;
			memberID =pFuncDesc->memid ;
			int ii =0 ;
			for ( int ii =0 ; ii < GetPromptMapSize () ; ii++ ) { 
				if ( memberID == pPromptMap [ii].m_dispId ) {
					UINT nNamesArraySize =pFuncDesc->cParams + 1, nReturnedNames ;
					BSTR *pBstrNames =new BSTR [nNamesArraySize] ;
					if ( !SUCCEEDED (pTypeInfo->GetNames (memberID, pBstrNames, nNamesArraySize, &nReturnedNames)) )
						return (E_FAIL) ;
					delete [] pBstrNames ;
					if ( nReturnedNames < 1 )
						continue ;
					//- Since the DISPID will be shared by both 'put' and 'get' functions, we will enter here twice for each property, though we
					//- only need to use one.  The 'get' version will have the VT_BYREF or'ed in the VARTYPE, 
					//- so we can chose to ignore this one to get the true type from the property 'put' version.
					if ( pFuncDesc->invkind == INVOKE_PROPERTYGET )
						continue ;
					//- This is equivalent to checking invkind...
					//if ( pFuncDesc->lprgelemdescParam [nReturnedNames - 1].tdesc.vt & VT_BYREF )
					//	continue ;

					//- For properties, we assume a single argument, which means we should expect two names in this list, the property name
					//- and the single parameter.  However, MIDL will many times lop off the name, which means we should just assume the parameter
					//- type is the last in this list, hence nReturnedNames-1.
					//pPromptMap [ii].m_paramType =pFuncDesc->lprgelemdescParam [nReturnedNames - 1].tdesc.vt ;
					pPromptMap [ii].m_paramType =propertyTypeCallback (ii, pFuncDesc->lprgelemdescParam [nReturnedNames - 1].tdesc.vt) ;
				}
			}
		}
		return (S_OK) ;
	}

	HRESULT PutProperty (int index) {
		static bool bDontLoop =false ;
		WORD wflags =DISPATCH_PROPERTYPUT ;
		DISPID putid =DISPID_PROPERTYPUT ;

		CComPtr<IDispatch> pDisp ;
		m_pWrapperObject.QueryInterface (&pDisp) ;
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;

		//- Careful acedGetPoint() and acquirePoint() returns point is UCS
		//- Usually COM wrapper properties are set to work in WCS
		//- Therefore we need to convert coordiantes from UCS to WCS
		//switch ( pPromptMap [index].m_promptType ) {
		//	case RTPOINT: {
		//		AcAxPoint2d pt (pPromptMap [index].m_vValue) ;
		//		AcGePoint3d pt3d (pt.x, pt.y, 0) ;
		//		acdbUcs2Wcs (asDblArray (pt3d), asDblArray (pt3d), false) ;
		//		pt =pt3d.convert2d (AcGePlane ()) ;
		//		pt.setVariant (pPromptMap [index].m_vValue) ;
		//		break ;
		//	}
		//	case RT3DPOINT: {
		//		AcAxPoint3d pt (pPromptMap [index].m_vValue) ;
		//		acdbUcs2Wcs (asDblArray (pt), asDblArray (pt), false) ;
		//		pt.setVariant (pPromptMap [index].m_vValue) ;
		//		break ;
		//	}
		//}

		DISPPARAMS dispparams ;
		dispparams.rgvarg =&pPromptMap [index].m_vValue ;
		dispparams.rgdispidNamedArgs =&putid ;
		dispparams.cArgs =1 ;
		dispparams.cNamedArgs =1 ;
		HRESULT hr=pDisp->Invoke (
			pPromptMap [index].m_dispId, IID_NULL, LOCALE_USER_DEFAULT,
			wflags, &dispparams, NULL, NULL, NULL
		) ;
		if ( hr != S_OK && !bDontLoop ) {
			bDontLoop =true ;
			setPropertyDefault (index) ;
			bDontLoop =false ;
		}
		return (hr) ;
	}

	//- Property events
	STDMETHODIMP OnChanged (DISPID dispId) {
		PROMPT_MAP_ENTRY *pPromptMap=GetPromptMap () ;
		int i =0 ;
		while ( pPromptMap [i].m_szDesc ) {
			if ( dispId == pPromptMap [i].m_dispId ) {
				pPromptMap [i].m_bGotThisProperty =true ;
				break ;
			}
			i++ ;
		}
		if ( m_pDoc != NULL )
			acDocManager->sendModelessInterrupt (m_pDoc) ;
		return (S_OK) ;
	}

	STDMETHODIMP OnRequestEdit (DISPID dispID) { return (S_OK) ; }

	//- Property
	virtual void setPropertyDefaults (int index =-1) {
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;
		if ( index == -1) {
			for ( int i =0 ; pPromptMap [i].m_szDesc ; i++ )
				setPropertyDefault (i) ;
		} else {
			setPropertyDefault (index) ;
		}
	}
	void setPropertyDefault (int i) {
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;
		pPromptMap [i].m_vValue.vt =pPromptMap [i].m_paramType ;
		TCHAR szDefaultValue [256] ;
		if ( defaultValueCallback (i, szDefaultValue) == false )
			LoadString (pPromptMap [i].m_nDefaultValue, szDefaultValue) ;
		switch ( pPromptMap [i].m_paramType ) {
			case VT_I4:
				//pPromptMap [i].m_vValue.lVal =_ttol (szDefaultValue) ;
				setProperty (i, pPromptMap [i].m_vValue, _ttol (szDefaultValue)) ;
				break;
			case VT_I2:
				//pPromptMap [i].m_vValue.iVal =static_cast<short>(_ttoi (szDefaultValue)) ;
				setProperty (i, pPromptMap [i].m_vValue, static_cast<short>(_ttoi (szDefaultValue))) ;
				break;
			case VT_ARRAY | VT_R8: {
				TCHAR seps [] =L" ," ;
				TCHAR szDefault [MAX_PATH] ;
				wcscpy (szDefault, szDefaultValue) ;
				AcGePoint3d defPt ;
				TCHAR *token =wcstok (szDefault, seps) ;
				for ( long index =0 ; token ; index++ ) {
					if ( index < 3 )
						defPt [index] =_tstof (token) ;
					token =wcstok (NULL, seps) ;
				}
				//AcAxPoint3d pt (defPt) ;
				//pt.setVariant (pPromptMap [i].m_vValue) ;
				setProperty (i, pPromptMap [i].m_vValue, defPt) ;
				break ;
			}
			case VT_BSTR:
				//pPromptMap [i].m_vValue.bstrVal =_bstr_t (szDefaultValue).copy () ;
				setProperty (i, pPromptMap [i].m_vValue, szDefaultValue) ;
				break ;
			case VT_R8:
				//pPromptMap [i].m_vValue.dblVal =_tstof (szDefaultValue) ;
				setProperty (i, pPromptMap [i].m_vValue, _tstof (szDefaultValue)) ;
				break ;
			case VT_R4:
				//pPromptMap [i].m_vValue.fltVal =static_cast<float>(_tstof (szDefaultValue)) ;
				setProperty (i, pPromptMap [i].m_vValue, static_cast<float>(_tstof (szDefaultValue))) ;
				break ;
		}
		if ( pPromptMap [i].m_dispId )
			PutProperty (i) ;
		pPromptMap [i].m_bGotThisProperty =false ;
	}

	//- AcEdJig
	virtual void initSampler () =0 ;

	virtual AcEdJig::DragStatus sampler () {
		setSpecialCursorType (m_jigCursorType) ;
		setUserInputControls (m_jigUserInputControls) ;
		AcEdJig::DragStatus stat =AcEdJig::kCancel ;
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;
		int i =0 ;
		while ( pPromptMap [i].m_szDesc ) {
			if ( pPromptMap [i].m_bJigThisProperty && !pPromptMap [i].m_bGotThisProperty ) {
				bool compareChange =false ;
				if ( pPromptMap [i].m_nKeywords != 0 ) {
					TCHAR szKeywords [256] ;
					LoadString (pPromptMap [i].m_nKeywords, szKeywords) ;
					setKeywordList (szKeywords) ;
				}
				stat =samplerCallback (i, compareChange) ;
				if ( stat >= AcEdJig::kKW1 )
					keywordCallback (i, (TCHAR *)&stat, NULL) ;
				if ( stat == AcEdJig::kOther ) {
					switch ( pPromptMap [i].m_promptType ) {
						case RTPOINT: {
							AcGePoint3d pos ;
							stat =acquirePoint (pos) ;
							m_cursorPos.x =pos.x ;
							m_cursorPos.y =pos.y ;
							if ( stat >= AcEdJig::kKW1 )
								keywordCallback (i, (TCHAR *)&stat, &m_pos) ;
							compareChange =(m_cursorPos.isEqualTo (m_pos) ? true : false) ;
							break ;
						}
						case RT3DPOINT:
							stat =acquirePoint (m_cursor3dPos) ;
							if ( stat >= AcEdJig::kKW1 )
								keywordCallback (i, (TCHAR *)&stat, &m_cursor3dPos) ;
							compareChange =(m_cursor3dPos.isEqualTo (m_pos3d) ? true : false) ;
							break ;
						case RTREAL:
							stat =acquireDist (m_cursorDist) ;
							if ( stat >= AcEdJig::kKW1 )
								keywordCallback (i, (TCHAR *)&stat, &m_cursorDist) ;
							compareChange =(m_cursorDist != m_dist) ;
							break ;
						case RTANG:
							stat =acquireAngle (m_cursorAngle) ;
							if ( stat >= AcEdJig::kKW1 )
								keywordCallback (i, (TCHAR *)&stat, &m_cursorAngle) ;
							compareChange =(m_cursorAngle != m_angle) ;
							break ;
						case RTSTR:
							stat =acquireString (m_szCursorString) ;
							if ( stat >= AcEdJig::kKW1 )
								keywordCallback (i, (TCHAR *)&stat, &m_szCursorString) ;
							compareChange =(m_szCursorString != m_szString) ;
							break ;
					}
					if ( stat == AcEdJig::kNull )
						pPromptMap [i].m_bGotThisProperty =true ;
				}
				if ( stat == AcEdJig::kCancel )
					return (stat) ;
				if ( !compareChange ) {
					//RXTRACE ("AsdkPromptBase::sampler - !compareChange, stat = %d\n", stat) ;
					return (stat == AcEdJig::kNull ? stat : AcEdJig::kNoChange) ;
				} else {
					m_pos =m_cursorPos ;
					m_pos3d =m_cursor3dPos ;
					m_dist =m_cursorDist ;
					m_angle =m_cursorAngle ;
					m_szString =m_szCursorString ;
					//RXTRACE ("AsdkPromptBase::sampler - stat = %d\n", stat) ;
					return (stat) ;
				}
			}
			i++ ;
		}
		return (stat) ;
	}

	virtual AcDbEntity *entity () const { 
		if ( m_pDbrObject == NULL )
			m_pBaseObj->GetObject ((AcDbObject *&)m_pDbrObject) ;
		return ((AcDbEntity *)m_pDbrObject) ;
	}

	virtual Adesk::Boolean update () {
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;
		for ( int i =0 ; pPromptMap [i].m_szDesc ; i++ ) { 
			if ( pPromptMap [i].m_bJigThisProperty && !pPromptMap [i].m_bGotThisProperty ) {
				if ( updateCallback (i) == false ) {
					switch ( pPromptMap [i].m_promptType ) {
						case RTPOINT: {
							//AcAxPoint2d pt (m_cursorPos) ;
							//pt.setVariant (pPromptMap [i].m_vValue) ;
							setProperty (i, pPromptMap [i].m_vValue, m_cursorPos) ;
							break ;
						}
						case RT3DPOINT: {
							//AcAxPoint3d pt (m_cursor3dPos) ;
							//pt.setVariant (pPromptMap [i].m_vValue) ;
							setProperty (i, pPromptMap [i].m_vValue, m_cursor3dPos) ;
							break ;
						}
						case RTREAL:
							//pPromptMap [i].m_vValue.dblVal =m_cursorDist ;
							setProperty (i, pPromptMap [i].m_vValue, m_cursorDist) ;
							break ;
						case RTANG:
							//pPromptMap [i].m_vValue.dblVal =m_cursorAngle ;
							setProperty (i, pPromptMap [i].m_vValue, m_cursorAngle) ;
							break ;
						case RTSTR:
							//pPromptMap [i].m_vValue.bstrVal =_bstr_t (m_szCursorString) ;
							setProperty (i, pPromptMap [i].m_vValue, m_szCursorString) ;
							break ;
						default:
							acutPrintf (L"Type %s not handled by Jig mechanism!\n", pPromptMap [i].m_szDesc) ;
							break ;
					}
					PutProperty (i) ;
					pPromptMap [i].m_bGotThisProperty =false ;
					break ;
				}
			}
		}
		return (Adesk::kTrue) ;
	}

	//- Callbacks
	virtual void constructorCallback () {}
	virtual int promptCallback (int index) { return (RTINPUTTRUNCATED) ; } //- Return RTCAN to cancel the prompt. Return RTNORM to prevent the MAP entry
	virtual AcEdJig::DragStatus samplerCallback (int index, bool &compareChange) { return (kOther) ; } //- Return different value to skip the MAP entry
	virtual bool updateCallback (int index) { return (false) ; } //- Return true to skip the MAP entry
	virtual bool keywordCallback (int index, TCHAR *kword, void *value) { return (false) ; }
	virtual bool defaultValueCallback (int index, LPWSTR szDefaultVal) { return (false) ; }

	//- Utility
	int LoadString (UINT uID, LPWSTR szString, int nBufferMax =255) {
		int ret =0 ;
		*szString =L'\0' ;
		if ( uID != 0 && uID != (UINT)-1 )
			ret =::LoadString (GetResourceInstance (), uID, szString, nBufferMax) ;
		return (ret) ;
	}

	LPCWSTR BuildPromptString (int index) {
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;

		static TCHAR szPrompt [256] ;
		LoadString (pPromptMap [index].m_nPrompt, szPrompt) ;

		TCHAR szDefaultVal [256] ;
		*szDefaultVal =L'\0' ;
		if ( defaultValueCallback (index, szDefaultVal) == false )
			LoadString (pPromptMap [index].m_nDefaultValue, szDefaultVal) ;
		if ( *szDefaultVal != L'\0' ) {
			wcscat (szPrompt, L" <") ;
			wcscat (szPrompt, szDefaultVal) ;
			wcscat (szPrompt, L">") ;
		}
		wcscat (szPrompt, L": ") ;
		return (szPrompt) ;
	}

public:
	virtual AcDbObjectId promptLoop () { 
		setPropertyDefaults (-1) ;
		//- The szDefaultValue member of the map may need to be altered to reflect
		//- the desired default values.  We need to check these, and populate the variant in each
		//- map entry with these values each time we run the loop.
		DragStatus stat =kNormal ;
		int retval =RTNORM ;
		PROMPT_MAP_ENTRY *pPromptMap =GetPromptMap () ;
		int i =0 ;
		while ( true ) {
			bool done =true ;
			while ( pPromptMap [i].m_szDesc ) { 
				if ( !pPromptMap [i].m_bJigThisProperty && !pPromptMap [i].m_bGotThisProperty ) {
					done =false ;
					retval =promptCallback (i) ;
					if ( retval == RTCAN )
						break ;
					if ( retval == RTINPUTTRUNCATED ) { //- return RTINPUTTRUNCATED to use the defaults
						TCHAR szKeyword [133] ;
						if ( pPromptMap [i].m_nKeywords != 0 ) {
							LoadString (pPromptMap [i].m_nKeywords, szKeyword, 132) ;
							acedInitGet (pPromptMap [i].m_nInitget, szKeyword) ;
						}
						LPCWSTR szPrompt =BuildPromptString (i) ;
						switch ( pPromptMap [i].m_promptType ) {
							case RTPOINT: {
								ads_point point ;
								retval =acedGetPoint (NULL, szPrompt, point) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, point) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									AcGePoint2d pt2d (point [X], point [Y]) ;
									//AcAxPoint2d vPt (pt2d) ;
									//vPt.setVariant (pPromptMap [i].m_vValue) ;
									setProperty (i, pPromptMap [i].m_vValue, pt2d) ;
									PutProperty (i) ;
								}
								break ;
							}
							case RT3DPOINT: {
								ads_point point ;
								retval =acedGetPoint (NULL, szPrompt, point) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, point) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									AcGePoint3d pt3d (point [0], point [1], point [2]) ;
									//AcAxPoint3d vPt (pt3d) ;
									//vPt.setVariant (pPromptMap [i].m_vValue) ;
									setProperty (i, pPromptMap [i].m_vValue, pt3d) ;
									PutProperty (i) ;
								}
								break ;
							}
							case RTREAL: {
								double dist =0 ;
								retval =acedGetReal (szPrompt, &dist) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, &dist) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									//pPromptMap [i].m_vValue.dblVal =dist ;
									setProperty (i, pPromptMap [i].m_vValue, dist) ;
									PutProperty (i) ;
								}
								break ;
							}
							case RTANG: {
								double angle =0 ;
								retval =acedGetAngle (NULL, szPrompt, &angle) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, &angle) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									//pPromptMap [i].m_vValue.dblVal =angle ;
									setProperty (i, pPromptMap [i].m_vValue, angle) ;
									PutProperty (i) ;
								}
								break ;
							}
							case RTSTR: {
								TCHAR szBuffer [132] ;
								*szBuffer =L'\0' ;
								retval =acedGetString (pPromptMap [i].m_cronly, szPrompt, szBuffer) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, szBuffer) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									if ( wcslen (szBuffer) ) //- No zero length strings...
										//pPromptMap [i].m_vValue.bstrVal =_bstr_t (szBuffer) ;
										setProperty (i, pPromptMap [i].m_vValue, szBuffer) ;
									PutProperty (i) ;
								} 
								break ;
							}
							case RTLONG: {
								int _int =0 ;
								retval =acedGetInt (szPrompt, &_int) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, &_int) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									//pPromptMap [i].m_vValue.lVal =static_cast<LONG>(_int) ;
									setProperty (i, pPromptMap [i].m_vValue, static_cast<long>(_int)) ;
									PutProperty (i) ;
								}
								break ;
							}
							case RTSHORT: {
								int _int =0 ;
								retval =acedGetInt (szPrompt, &_int) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, &_int) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									//pPromptMap [i].m_vValue.iVal =static_cast<SHORT>(_int) ;
									setProperty (i, pPromptMap [i].m_vValue, static_cast<short>(_int)) ;
									PutProperty (i) ;
								}
								break ;
							}
							case RTENAME: {
								ads_name ename ;
								ads_point pt ;
								retval =acedEntSel (szPrompt, ename, pt) ;
								if ( retval == RTKWORD ) {
									acedGetInput (szKeyword) ;
									if ( keywordCallback (i, szKeyword, ename) == true )
										retval =RTNORM ;
								}
								if ( retval == RTNORM ) {
									//pPromptMap [i].m_vValue.lVal =static_cast<LONG>(ename [0]) ;
									setProperty (i, pPromptMap [i].m_vValue, static_cast<long>(ename [0])) ;
									PutProperty (i) ;
								}
								break ;
							}
						}
					}
					if ( retval == RTNONE )
						pPromptMap [i].m_bGotThisProperty =true ;
					if ( retval == RTCAN ) {
						done =true ;
						break ;
					}
					if ( pPromptMap [i].m_bGotThisProperty == true )
						i++ ;
				} else {
					i++ ;
				}
			} 
			if ( done )
				break ;
			else
				i =0 ;
		} 
		if ( retval == RTCAN )
			return (AcDbObjectId::kNull) ;
		i =0 ;
		while ( true ) {
			bool done =true ;
			while( pPromptMap [i].m_szDesc ) {
				if ( pPromptMap [i].m_bJigThisProperty && !pPromptMap [i].m_bGotThisProperty ) {
					done =false ;
					retval =promptCallback (i) ;
					if ( retval == RTINPUTTRUNCATED ) {
						setDispPrompt (BuildPromptString (i)) ;
						stat =drag () ;
						if ( stat == AcEdJig::kNormal ) {
							switch ( pPromptMap [i].m_promptType ) {
								case RTPOINT: {
									//AcAxPoint2d pos (m_cursorPos) ;
									//pos.setVariant (pPromptMap [i].m_vValue) ;
									setProperty (i, pPromptMap [i].m_vValue, m_cursorPos) ;
									PutProperty (i) ;
									break ;
								}
								case RT3DPOINT: {
									//AcAxPoint3d pos (m_cursor3dPos) ;
									//pos.setVariant (pPromptMap [i].m_vValue) ;
									setProperty (i, pPromptMap [i].m_vValue, m_cursor3dPos) ;
									PutProperty (i) ;
									break ;
								}
								case RTREAL:
									//pPromptMap [i].m_vValue.dblVal =m_cursorDist ;
									setProperty (i, pPromptMap [i].m_vValue, m_cursorDist) ;
									PutProperty (i) ;
									break ;
								case RTANG:
									//pPromptMap [i].m_vValue.dblVal =m_cursorAngle ;
									setProperty (i, pPromptMap [i].m_vValue, m_cursorAngle) ;
									PutProperty (i) ;
									break ;
								case RTSTR:
									//pPromptMap [i].m_vValue.bstrVal =_bstr_t (m_szCursorString) ;
									setProperty (i, pPromptMap [i].m_vValue, m_szCursorString) ;
									PutProperty (i) ;
									break ;
							}
						}
						if ( stat == AcEdJig::kCancel ) {
							done =true ;
							break ;
						}
					}
					if ( retval == RTCAN || retval == AcEdJig::kCancel ) {
						stat =AcEdJig::kCancel ;
						done =true ;
						break ;
					}
					if ( pPromptMap [i].m_bGotThisProperty == true )
						i++ ;
				} else {
					i++ ;
				}
			}
			if ( done )
				break ;
			else
				i =0 ;
		}
		if ( stat != AcEdJig::kCancel ) {
			if ( m_pBaseObj )
				m_pBaseObj->GetObject (m_pDbrObject) ;
			return (append ()) ;
		}
		return (AcDbObjectId::kNull) ;
	}
} ;

//-----------------------------------------------------------------------------
#define BEGIN_PROMPT_MAP(CLASSNAME) \
	public: \
	CLASSNAME () { \
		HRESULT hr =S_OK ; \
		if ( FAILED(hr =m_pWrapperObject.CoCreateInstance (m_CLSID_ObjectWrapper)) ) { \
			acutPrintf (L"Unable to Create Wrapper Class\n") ; \
			throw hr ; \
		} \
		m_pBaseObj =m_pWrapperObject ; \
		if ( FAILED (hr =m_pBaseObj->CreateObject ()) ) \
			throw hr ; \
		SetDocument (curDoc ()) ; \
		CComPtr<IUnknown> pUnkCmd ; \
		hr =QueryInterface (IID_IUnknown, (void **)&pUnkCmd) ; \
		if ( FAILED(hr) ) \
			throw hr ; \
		CComQIPtr<IConnectionPointContainer> pPtContainer ; \
		pPtContainer =m_pWrapperObject ; \
		hr =pPtContainer->FindConnectionPoint (IID_IPropertyNotifySink, &m_pConPt) ; \
		if ( FAILED(hr) ) \
			throw hr ; \
		\
		if ( FAILED(hr =GetPropertyTypeInfo ()) ) { \
			acutPrintf (L"Unable to Obtain Correct Type Information from the Wrapper Class\n") ; \
			throw hr ; \
		} \
		if ( FAILED(hr =m_pConPt->Advise (pUnkCmd, &m_dConnectionID)) ) \
			throw hr ; \
		\
		BOOL bRet =acedSetIUnknownForCurrentCommand (m_pWrapperObject) ; \
		m_pDb =acdbHostApplicationServices ()->workingDatabase () ; \
		\
		AcDbObject *pObj =NULL ; \
		m_pBaseObj->GetObject (pObj) ; \
		m_pDbrObject =pObj ; \
		AcDbEntity *pEnt=(AcDbEntity *)AcDbEntity::cast (pObj) ; \
		if ( pEnt ) \
			pEnt->setDatabaseDefaults () ; \
		m_pBaseObj->SetObject (pObj) ; \
		constructorCallback () ; \
		initSampler () ; \
	} \
	~CLASSNAME () { \
		m_pConPt->Unadvise (m_dConnectionID) ; \
		if ( m_pBaseObj ) \
			m_pBaseObj->GetObject (m_pDbrObject) ; \
	} \
	HRESULT STDMETHODCALLTYPE QueryInterface (REFIID refiid, void **ppv) { \
		if ( refiid == IID_IUnknown || refiid == IID_IPropertyNotifySink ) \
			*ppv =this ; \
		else \
			return (E_NOINTERFACE) ; \
		static_cast<IUnknown *>(this)->AddRef () ; \
		return (S_OK) ; \
	} \
	ULONG STDMETHODCALLTYPE AddRef () { \
		return (InterlockedIncrement (&m_cRef)) ; \
	} \
	ULONG STDMETHODCALLTYPE Release () { \
		ULONG ul =InterlockedDecrement (&m_cRef) ; \
		return (ul) ; \
	} \
	virtual PROMPT_MAP_ENTRY* GetPromptMap () { \
		static PROMPT_MAP_ENTRY pPromptMap [] = {

//-----------------------------------------------------------------------------
#define PROMPT_ENTRY(szDesc,dispId,promptType,defaultValueId,promptId,bJigThisProperty) \
	{ szDesc, dispId, promptType, 1, 0, 0, defaultValueId, promptId, bJigThisProperty },

#define PROMPT_ENTRY_INITGET(szDesc,dispId,promptType,initget,keywordsId,defaultValueId,promptId,bJigThisProperty) \
	{ szDesc, dispId, promptType, 1, initget, keywordsId, defaultValueId, promptId, bJigThisProperty },

#define PROMPT_ENTRY_SYMBOL(szDesc,dispId,defaultValueId,promptId,bJigThisProperty) \
	{ szDesc, dispId, RTSTR, 0, 0, 0, defaultValueId, promptId, bJigThisProperty },

//-----------------------------------------------------------------------------
#define END_PROMPT_MAP \
			{ NULL, 0, 0, 0, 0, 0, 0, false, false, VT_EMPTY } \
		} ; \
		return (pPromptMap) ; \
	}

//-----------------------------------------------------------------------------
#define DEFINE_SAMPLER(CURSORTYPE,USERINPUTCONTROLS) \
	virtual void initSampler () { \
		m_jigCursorType =CURSORTYPE ; \
		m_jigUserInputControls =USERINPUTCONTROLS ; \
	}
	