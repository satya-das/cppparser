/////////////////////////////////////////////////////////////////////////////// 
// Copyright ?2006, Open Design Alliance Inc. ("Open Design")  
//  
// This software is owned by Open Design, and may only be incorporated into  
// application programs owned by members of Open Design subject to a signed  
// Membership Agreement and Supplemental Software License Agreement with  
// Open Design. The structure and organization of this Software are the valuable  
// trade secrets of Open Design and its suppliers. The Software is also protected  
// by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement  
// with their copyright notices: 
// 
//      DWGdirect ?2006 by Open Design Alliance Inc. All rights reserved.  
// 
// By use of this software, you acknowledge and accept the terms of this  
// agreement. 
/////////////////////////////////////////////////////////////////////////////// 
#ifndef _ODRXOBJECT_INCLUDED_
#	define _ODRXOBJECT_INCLUDED_
#	include "DD_PackPush.h"
#	include "RootExport.h"
#	include "OdHeap.h"
#	include "OdArrayPreDef.h"
#	include "OdString.h"
class OdRxClass;
class OdRxObject;
class OdRxModule;
enum OdRxObjMod
{
	kOdRxObjAttach
};
/** Description: 
    Declares the RunTime Type Identification functions required by OdRxObject objects. 
     
    Remarks: 
    Any class derived from OdRxObject should include this macro in its class declarations, 
    passing its own name. 
*/
#	define ODRX_DECLARE_MEMBERS	(ClassName)\ 
public:                                                                                              \ 
                                                                                                     \ 
  /** Description: Casts the specified pointer to an ClassName SmartPointer. **/                      \ 
  static OdSmartPtr<ClassName> cast(const OdRxObject* pObj)                                          \ 
  {                                                                                                  \ 
    if (pObj)                                                                                        \ 
      return OdSmartPtr<ClassName>(((ClassName*)pObj->queryX(ClassName::desc())), kOdRxObjAttach);   \ 
    return (ClassName*)0;                                                                            \ 
  }                                                                                                  \ 
                                                                                                     \ 
  static OdRxClass* g_pDesc;                                                                         \ 
                                                                                                     \ 
  /** Description: Returns the static OdRxClass description object associated with this object. **/  \ 
  /** Note: This function is for use only when the class type of this object is known.          **/  \ 
  /** If the class type of this object is unknown, use instead isA().                           **/  \ 
  static OdRxClass* desc();                                                                   \ 
                                                                                                     \ 
  /** Description: Returns the OdRxClass description instance associated with this object.      **/  \ 
  /** Note: This function is for use only when the class type of this object is unknown.        **/  \ 
  /** If the class type of this object is known, use instead desc().                            **/  \ 
  virtual OdRxClass* isA() const;                                                                    \ 
                                                                                                     \ 
  /** Description: Returns the Protocol Extension object for this object.        **/                 \ 
  /** Remarks: Return null if there is no Protocol Extension object is found.    **/                 \ 
  virtual OdRxObject* queryX(const OdRxClass* protocolClass) const;                                  \ 
                                                                                                     \ 
  /** Description: Creates a new instance of this object type.                   **/                 \ 
  /** Remarks: Returns a SmartPointer to the new instance.                       **/                 \ 
  static OdRxObjectPtr pseudoConstructor();                                                          \ 
                                                                                                     \ 
  /** Description: Creates a new instance of this object type.                   **/                 \ 
  /** Remarks: Returns a SmartPointer to the new instance.                       **/                 \ 
   static OdSmartPtr<ClassName> createObject()                                                       \ 
  { if (!desc()) throw OdError(eNotInitializedYet); return desc()->create(); }                       \ 
                                                                                                     \ 
  /** Description: Registers ClassName with DWGdirect.                           **/                 \ 
  static void rxInit();                                                                              \ 
                                                                                                     \ 
  /* Description: Unregisters ClassName with DWGdirect.                          **/                 \ 
  static void rxUninit() 
/** Description: 
    Casts a null pointer to the specified class. 
*/
#	define EMPTY_CONSTR	(ClassName)(ClassName*)0 
/** Description  
    Creates a new instance of the specified class, and returns a SmartPointer to the instance. 
     
    Remarks:  
    The new object's reference count is set 0. 
*/
#	define NEWOBJ_CONSTR	(ClassName) OdSmartPtr<ClassName>(new ClassName, kOdRxObjAttach) 
/** Description: 
    Defines Runtime Type Identification functions for OdRxObject objects. 
*/
#	define ODRX_DEFINE_RTTI_MEMBERS	(ClassName,ParentClass)                                              \ 
                                                                                                     \ 
OdRxClass* ClassName::g_pDesc = 0;                                                                   \ 
OdRxClass* ClassName::desc(){ return g_pDesc; }                                                      \ 
OdRxClass* ClassName::isA() const { return g_pDesc; }                                                \ 
                                                                                                     \ 
OdRxObject* ClassName::queryX(const OdRxClass* pClass) const                                         \ 
{ return ::odQueryXImpl<ClassName,ParentClass >(this, pClass); } 
/* 
  Description: 
  Defines initialization functions for OdObjecobjects. 
*/
#	define ODRX_DEFINE_INIT_MEMBERS	(ClassName,ParentClass,pseudoConsFn, DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName) \ 
                                                                                                     \ 
/* Registers this class with DWGdirect.                                         */                   \ 
void ClassName::rxInit()                                                                             \ 
{                                                                                                    \ 
  if (!ClassName::g_pDesc) {                                                                         \ 
    ClassName::g_pDesc = ::newOdRxClass(szDWGClassName,ParentClass::desc(),                          \ 
    pseudoConsFn,DwgVer,MaintVer,nProxyFlags,szDxfName,szAppName);                                   \ 
  } else {                                                                                           \ 
    ODA_ASSERT(("Class ["#ClassName"] is already initialized.",0));                                  \ 
    throw OdError(eExtendedError);                                                                   \ 
  }                                                                                                  \ 
}                                                                                                    \ 
                                                                                                     \ 
/* Unregisters this class with DWGdirect.                                       */                   \ 
void ClassName::rxUninit()                                                                           \ 
{                                                                                                    \ 
  if (ClassName::g_pDesc) {                                                                          \ 
    ::deleteOdRxClass(ClassName::g_pDesc);                                                           \ 
    ClassName::g_pDesc = 0;                                                                          \ 
  } else {                                                                                           \ 
    ODA_ASSERT(("Class ["#ClassName"] is not initialized yet.",0));                                  \ 
    throw OdError(eNotInitializedYet);                                                               \ 
  }                                                                                                  \ 
} 
/** Description: 
    Defines a Pseudoconstructor for ClassName. 
*/
#	define ODRX_DEFINE_PSEUDOCONSTRUCTOR	(ClassName,DOCREATE)                                            \ 
                                                                                                     \ 
OdRxObjectPtr ClassName::pseudoConstructor() { return OdRxObjectPtr(DOCREATE(ClassName)); } 
/** Description: 
    Defines Runtime Type Identification and initialization functions for OdRxObject objects. 
*/
#	define ODRX_DEFINE_MEMBERS2	(ClassName,ParentClass,pseudoConsFn,DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName) \ 
                                                                                                     \ 
ODRX_DEFINE_RTTI_MEMBERS(ClassName,ParentClass)                                                      \ 
                                                                                                     \ 
ODRX_DEFINE_INIT_MEMBERS(ClassName,ParentClass,pseudoConsFn,                                         \ 
    DwgVer,MaintVer,nProxyFlags, szDWGClassName,szDxfName,szAppName) 
#	define ODRX_DEFINE_MEMBERS	(ClassName,ParentClass,DOCREATE,DwgVer,MaintVer, nProxyFlags,szDWGClassName,szDxfName,szAppName)\ 
                                                                                                     \ 
ODRX_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,                             \ 
  DwgVer,MaintVer,nProxyFlags,szDWGClassName,szDxfName,szAppName)                                    \ 
                                                                                                     \ 
ODRX_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE) 
#	define ODRX_NO_CONS_DEFINE_MEMBERS_ALTNAME	(ClassName,ParentClass,szClassName)                       \ 
                                                                                                     \ 
ODRX_DEFINE_MEMBERS2(ClassName,ParentClass,0,0,0,0,szClassName,OdString::kEmpty,OdString::kEmpty)                \ 
                                                                                                     \ 
ODRX_DEFINE_PSEUDOCONSTRUCTOR(ClassName,EMPTY_CONSTR) 
#	define ODRX_NO_CONS_DEFINE_MEMBERS	(ClassName,ParentClass)                                           \ 
                                                                                                     \ 
ODRX_NO_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,DD_T(#ClassName)) 
#	define ODRX_CONS_DEFINE_MEMBERS_ALTNAME	(ClassName,ParentClass,szClassName,DOCREATE)                 \ 
                                                                                                     \ 
ODRX_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,0,0,0,szClassName,OdString::kEmpty,OdString::kEmpty) \ 
                                                                                                     \ 
ODRX_DEFINE_PSEUDOCONSTRUCTOR(ClassName,DOCREATE) 
#	define ODRX_CONS_DEFINE_MEMBERS	(ClassName,ParentClass,DOCREATE)                                     \ 
                                                                                                     \ 
ODRX_CONS_DEFINE_MEMBERS_ALTNAME(ClassName,ParentClass,DD_T(#ClassName),DOCREATE) 
#	define ODRX_DXF_DEFINE_MEMBERS	(ClassName,ParentClass,DOCREATE,DwgVer,MaintVer, nProxyFlags,DxfName,AppName)    \ 
                                                                                                                \ 
ODRX_DEFINE_MEMBERS(ClassName,ParentClass,DOCREATE,                                                             \ 
    DwgVer,MaintVer,nProxyFlags,DD_T(#ClassName),DD_T(#DxfName),DD_T(#AppName)) 
#	define ODRX_DXF_CONS_DEFINE_MEMBERS	(ClassName,ParentClass,DwgVer,MaintVer,nProxyFlags,DxfName,AppName)    \ 
                                                                                                           \ 
ODRX_DEFINE_MEMBERS2(ClassName,ParentClass,ClassName::pseudoConstructor,                                   \ 
    DwgVer,MaintVer,nProxyFlags,DD_T(#ClassName),DD_T(#DxfName),DD_T(#AppName))                                              \ 
                                                                                                           \ 
ODRX_DEFINE_PSEUDOCONSTRUCTOR(ClassName,NEWOBJ_CONSTR) 
/** Description: 
 
    {group:DD_Namespaces} 
*/
namespace OdRx
{
	enum Ordering
	{
		kLessThan = -1,
		kEqual = 0,
		kGreaterThan = 1,
		kNotOrderable = 2
	};
}
/** Description: 
    This class implements SmartPointers for instances of OdRxObject. 
 
    Library: 
    Db 
     
    Remarks: 
    SmartPointers relieve the programmer 
    of having to determine when objects are no longer needed, or having to delete 
    them at that time. 
 
    Each object referenced by a SmartPointer (henceforth 'referenced object')  
    maintains a reference count; i.e., how many SmartPointers are referencing it.      
    When the reference count reaches zero, the referenced object is deleted. 
 
     
    {group:OdRx_Classes}  
*/
class OdRxObjectPtr
{
	OdRxObject* m_pObject;
  /** Description: 
    Increments the reference count of the referenced object. 
  */
	inline void internalAddRef();
  /** Description: 
    Assigns the specifed object to this SmartPointer object.   
       
    Remarks: 
    The reference count of the specified object is incremented. 
 
    If this SmartPointer is currently referencing another object, that object  
    is released prior to the assignment.   
 
    Arguments: 
    pObject (I) Pointer to the object to be assigned. 
  */
	void assign(const OdRxObject* pObject)
	{
		if (m_pObject != pObject)
		{
			release();
			m_pObject = (OdRxObject*) pObject;
			internalAddRef();
		}
		else 
		{
		}
	}
public:
  /** Description: 
    Arguments: 
    pSource (I) Pointer to the object to be assigned to the new SmartPointer object. 
 
    Remarks: 
    If pSource is specified, the specified object is assigned to this SmartPointer object. 
     
    Remarks: 
    If OdRxObjMod is specified, the reference count of the referenced object  
    is *not* incremented.  
  */
	OdRxObjectPtr()
		: m_pObject(0)
	{
	}
	OdRxObjectPtr(const OdRxObject* pSource, OdRxObjMod)
		: m_pObject(const_cast<OdRxObject*>(pSource))
	{
	}
	OdRxObjectPtr(const OdRxObject* pSource)
		: m_pObject((OdRxObject*) pSource)
	{
		internalAddRef();
	}
	OdRxObjectPtr(const OdRxObjectPtr& pSource)
		: m_pObject((OdRxObject*) pSource.get())
	{
		internalAddRef();
	}
  /** Description: 
    Assigns the specifed object to this SmartPointer object.   
       
    Arguments: 
    pObject (I) Pointer to the object to be assigned. 
 
    Remarks: 
    The reference count of the specified object is not incremented. 
 
    If this SmartPointer is currently referencing another object, that object  
    is released prior to the assignment. 
  */
	void attach(const OdRxObject* pObject)
	{
		release();
		m_pObject = (OdRxObject*) pObject;
	}
  /** 
    Remarks: 
    Decrements the reference count of the object referenced by this 
    SmartPointer object. 
 
    When the reference count reaches zero, the referenced object is deleted. 
  */
	~OdRxObjectPtr()
	{
		release();
	}
  /** Description: 
    Releases this SmartPointer's reference to the referenced object. 
     
    Remarks: 
    Decrements the reference count of the referenced object.  
     
    When the reference count reaches zero, the referenced object is deleted. 
  */
	inline void release();
  /** Description: 
    Releases this SmartPointer's reference to the referenced object. 
       
    Remarks: 
    Returns the object referenced by this SmartPointer object. 
     
    The referenced object's reference count is not modified. 
  */
	OdRxObject* detach()
	{
		OdRxObject* res = m_pObject;
		m_pObject = 0;
		return res;
	}
  /** 
    Remarks: 
    The reference count of the referenced object is incremented. 
       
    If this SmartPointer is currently referencing another object, that object  
    is released prior to the assignment.   
  */
	OdRxObjectPtr& operator =(const OdRxObjectPtr& source)
	{
		assign(source);
		return *this;
	}
	OdRxObjectPtr& operator =(const OdRxObject* source)
	{
		assign(source);
		return *this;
	}
  /** Description: 
    Returns the referenced object. 
 
    Remarks: 
    This SmartPointer maintains its reference to the referenced object. 
     
    The reference count of the referenced object is unchanged. 
  */
	OdRxObject* get()
	{
		return m_pObject;
	}
	const OdRxObject* get() const
	{
		return m_pObject;
	}
  /** Description: 
    Returns the referenced object. 
       
    Remarks: 
    The reference count of the referenced object is unchanged. 
  */
	OdRxObject* operator ->()
	{
		return m_pObject;
	}
	const OdRxObject* operator ->() const
	{
		return m_pObject;
	}
#	ifdef ODA_GCC_2_95
  /** Description: 
    Returns the referenced object. 
     
    Remarks: 
    This SmartPointer maintains its reference to the referenced object. 
     
    The reference count of the referenced object is unchanged. 
 
    Remarks: 
    This non-standard form is used to eliminate a large number of compiler 
    warnings produced by GCC 2.95.X (GCC 3.X no longer produces these warnings). 
  */
	operator OdRxObject*() const
	{
		return m_pObject;
	}
#	else 
  /** Description: 
    Returns the referenced object. 
     
    Remarks: 
    This SmartPointer maintains its reference to the referenced object. 
     
    The reference count of the referenced object is unchanged. 
  */
	operator OdRxObject*()
	{
		return m_pObject;
	}
	operator const OdRxObject*() const
	{
		return m_pObject;
	}
#	endif
	bool operator==(const OdRxObject* pObject) const
	{
		return (m_pObject == pObject);
	}
	bool operator!=(const OdRxObject* pObject) const
	{
		return (m_pObject != pObject);
	}
  /** Description: 
    Returns true if and only if this SmartPointer contains a null reference. 
  */
	bool isNull() const
	{
		return m_pObject == 0;
	}
};
/** Description: 
    This class is the base class for all OdRxObject objects that  
    require Runtime Type Identification. 
 
    {group:OdRx_Classes}  
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdRxObject
{
  /** Note: 
      Assignment operator prohibited. 
  */
	OdRxObject(const OdRxObject&);
  /** Note: 
      Copy operator prohibited. 
  */
	OdRxObject& operator =(const OdRxObject&);
protected:
  /** Description: 
      Protects derived OdRxObject objects from direct use of new and delete.  
  */
	ODRX_HEAP_OPERATORS();
public:
	OdRxObject()
	{
	}
	virtual ~OdRxObject();
  /** Description: 
    Returns a pointer this object if this object can be converted to the specified class. 
 
    Arguments: 
    pClass (I) A pointer to the class to which this object is to be converted. 
       
    Remarks: 
    If the object cannot be converted, a null pointer is returned. 
    The user must release() this object, if the returned pointer is not null. 
  */
	virtual OdRxObject* queryX(const OdRxClass* pClass) const;
  /** Description: 
    Returns a pointer this object if this object can be converted to the specified class, 
    or throws an exception if it cannot. 
 
    Arguments: 
    pClass (I) A pointer to the class to which this object is to be converted. 
 
    Throws: 
    @table 
    Exception             Cause 
    eNotThatKindOfClass   Cannot convert to the specified class. 
    eInvalidInput         pClass is null 
 
  */
	virtual OdRxObject* x(const OdRxClass* pClass) const;
  /** Description: 
    Casts the specified *pointer* to a SmartPointer and returns the SmartPointer object. 
 
    Arguments: 
    pointer (I) Pointer to be cast. 
  */
	static OdRxObjectPtr cast(const OdRxObject* pointer)
	{
		OdRxObjectPtr pRes;
		if (pointer)
		{
			pRes.attach(pointer->queryX(desc()));
		}
		else 
		{
		}
		return pRes;
	}
  /** Description: Returns the static OdRxClass description object associated with this object. **/
  /** Note: This function is for use only when the class type of this object is known.          **/
  /** If the class type of this object is unknown, use instead isA().                           **/
	static OdRxClass* desc();
  /** Description: Returns the OdRxClass description instance associated with this object.      **/
  /** Note: This function is for use only when the class type of this object is unknown.        **/
  /** If the class type of this object is known, use instead desc().                            **/
	virtual OdRxClass* isA() const;
  /** Description: 
    Increments the reference count for this object. 
  */
	virtual void addRef() = 0;
  /** Description: 
    Decrements the reference count for this object. 
     
    Remarks: 
    When the reference count reaches zero, the referenced object is deleted. 
  */
	virtual void release() = 0;
  /** Description: 
      Returns the reference count for this object.  
  */
	virtual long numRefs() const;
   /** 
    Description: 
    Returns true if and only if this object is an instance of the specified class or 
    a subclass of the specified class. 
 
    Arguments: 
    pClass (I) Pointer to the class to test.  
  */
	bool isKindOf(const OdRxClass* pClass) const
	{
		OdRxObjectPtr pRes;
		pRes.attach(queryX(pClass));
		return (!pRes.isNull());
	}
  /** Description: 
    Creates a *clone* of this object, and returns a pointer to the *clone*. 
  */
	virtual OdRxObjectPtr clone() const;
  /* 
    Description: 
    Copies the contents of the specified object into this object. 
     
    Arguments: 
    pSource (I) Pointer to the source object. 
     
    Note: 
    The default implementation of this function does nothing but throw an eNotApplicable exception.  
     
    Throws: 
    @table 
    Exception     
    eNotApplicable 
    
 */
	virtual void copyFrom(const OdRxObject* pSource);
  /** Description: 
    Compares another object to this one in a manner similar to strcmp().  
 
    Arguments: 
    pOther (I) Pointer the object to be compared. 
     
    Remarks: 
    comparedTo() returns one of the following: 
     
    @table 
    Name                           Value     Description. 
    OdRx::kLessThan                -1        This object < Other Object 
    OdRx::kLessThanEqual            0         This object == Other Object 
    OdRx::kLessThanGreaterThan      1         This object > Other Object 
    OdRx::kLessThanNotOrderable     2         This class is not orderable. 
    
    Note: 
    The default implementation of this function returns OdRx::kNotOrderable.  
  */
	virtual OdRx ::Ordering comparedTo(const OdRxObject* pOther) const;
  /** 
    Description: 
    Returns true if and only if the specified object is equal to this one. 
 
    Arguments: 
    pOther (I) Pointer to the object to be compared. 
 
  */
	virtual bool isEqualTo(const OdRxObject* pOther) const;
};
void OdRxObjectPtr ::internalAddRef()
{
	if (m_pObject)
	{
		m_pObject->addRef();
	}
	else 
	{
	}
}
void OdRxObjectPtr ::release()
{
	if (m_pObject)
	{
		m_pObject->release();
		m_pObject = NULL;
	}
	else 
	{
	}
}
#	include "SmartPtr.h"
/** Description: 
    Defines OdPseudoConstructorType as a function pointer type. 
     
    Remarks: 
    Functions pointed to by OdPseudoConstructorType  
    take no arguments and construct instances of 
    classes derived from OdRxObject; 
    hence the name PseudoConstructorType. 
*/
typedef OdRxObjectPtr (*OdPseudoConstructorType) ();
/** Description: 
    Contains runtime information about OdRxObject or classes derived from it.   
     
    Remarks: 
    A pointer to an OdRxClass instance can be obtained for an OdRxObject class by calling  
    the OdRxObject::desc() function. 
 
    {group:OdRx_Classes}  
*/
class ODRX_ABSTRACT FIRSTDLL_EXPORT OdRxClass : public OdRxObject
{
protected:
	OdRxClass();
	ODRX_DECLARE_MEMBERS(OdRxClass);
public:
  /** Description: 
    Creates the Protocol Extension for the specified OdRxClass. 
 
    Arguments: 
    pProtocolClass (I) Pointer to the Protocol Extension class. 
    pProtocolObject (I) Pointer to the Protocol Extension Object. 
 
    Remarks: 
    Returns a SmartPointer to the Protocol Extension. 
 
    Note: 
    The default implementation of  this object does nothing but return a 
    null pointer, and asserts in debug mode. It will be 
    fully implemented in a future *release*. 
  */
	virtual OdRxObjectPtr addX(OdRxClass* pProtocolClass, OdRxObject* pProtocolObject);
  /** Description: 
    Returns the Protocol Extension for the specified 
    Protocol extension class. 
 
    Arguments: 
    pProtocolClass (I) Pointer to the Protocol Extension class. 
 
    Remarks: 
    Returns a SmartPointer to the Protocol Extension. 
 
    Note: 
    The default implementation of this object does nothing but 
    assert in debug mode, and return a null pointer. 
    It will be fully implemented in a future *release*. 
  */
	virtual OdRxObjectPtr getX(const OdRxClass* pProtocolClass);
  /** Description: 
    Deletes the Protocol Extension for the specified Protocol Extension class. 
 
    Remarks: 
    Returns the Protocol Extension Object. 
 
    Arguments: 
    pProtocolClass (I) Pointer to the Protocol Extension class. 
 
    Note: 
    As currently implemented, this function does nothing but 
    assert in debug mode, and return a null pointer. 
    It will be fully implemented in a future *release*. 
  */
	virtual OdRxObjectPtr delX(OdRxClass* pProtocolClass);
  /** Description: 
    Creates a new instance of the C++ class represented by this OdRxClass. 
 
    Remarks: 
    Returns a SmartPointer to the newly created class. 
  */
	virtual OdRxObjectPtr create() const = 0;
  /** Description: 
    Returns the application *name* associated with this OdRxClass. 
  */
	virtual const OdString appName() const = 0;
  /** Description: 
    Returns the DXF *name* for this OdRxClass.   
  */
	virtual const OdString dxfName() const = 0;
  /** Description: 
    Returns the *name* of the C++ class represented by this OdRxClass. 
  */
	virtual const OdString name() const = 0;
  /** Description: 
    Returns the DWG maintenance versions for this OdRxClass. 
 
    Arguments: 
    pMaintReleaseVer (I) Pointer to the MaintReleaseVer to receive the maintenance release version. 
 
    Remarks: 
    The maintenance release version is returned if and only if pMaintReleaseVer != NULL.  
  */
	virtual OdDb ::DwgVersion getClassVersion(OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const = 0;
  /** Description: 
    Returns the proxy flags for this OdRxClass. 
  */
	virtual OdUInt32 proxyFlags() const = 0;
  /** Description: 
    Returns true if and only if this object is an instance of the specified class or 
    a subclass of the specified class. 
 
    Arguments: 
    pClass (I) Pointer to the class to test.  
  */
	virtual bool isDerivedFrom(const OdRxClass* pClass) const;
  /** Description: 
    Returns the parent of this OdRxClass. 
  */
	virtual OdRxClass* myParent() const = 0;
  /** Description: 
    Returns the OdRxModule in which the class is resides. 
 
    Note: 
    The default implementation of this function returns a null pointer.  
  */
	virtual OdRxModule* module() const = 0;
  /** 
    Description: 
    Returns the PseudoConstructor of this OdRxClass. 
  */
	virtual OdPseudoConstructorType constructor();
  /** 
    Description: 
    Sets the PseudoConstructor for this OdRxClass. 
 
    Arguments: 
    pseudoConstr (I) PseudoConstructor. 
  */
	virtual void setConstructor(OdPseudoConstructorType psuedoConstr) = 0;
};
/** Description: 
    This template class is a specialization of the OdSmartPtr class template for OdRxClass object pointers. 
*/
typedef OdSmartPtr<OdRxClass> OdRxClassPtr;
template <class Class, class Parent>
OdRxObject* odQueryXImpl(const Class* pThis, const OdRxClass* pClass)
{
	OdRxObject* pObj = 0;
	if (pClass == Class::desc())
	{
		pObj = (OdRxObject*) pThis;
		pObj->addRef();
	}
	else 
	{
		pObj = Class::desc()->getX(pClass).detach();
		if (!pObj)
		{
			pObj = pThis->Parent::queryX(pClass);
		}
		else 
		{
		}
	}
	return pObj;
}
FIRSTDLL_EXPORT OdRxObjectPtr odrxCreateObject(const OdString& szClassName);
FIRSTDLL_EXPORT OdRxClass* newOdRxClass(const OdString& szClassName, OdRxClass* pBaseClass, OdPseudoConstructorType pConstr = 0, int DwgVer = 0, int MaintVer = 0, int nProxyFlags = 0, const OdString& szDxfName = "", const OdString& szAppName = "");
FIRSTDLL_EXPORT void deleteOdRxClass(OdRxClass* pClass);
/** Description: 
    This template class is a specialization of the OdArray class template for OdRx object pointers. 
*/
typedef OdArray<OdRxObjectPtr> OdRxObjectPtrArray;
#	include "DD_PackPop.h"
#endif
