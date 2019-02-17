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

#pragma once

#include "acbasedefs.h"
#include "adesk.h"
#include "acadstrc.h"
#include "pimplapi.h"
#include "AcString.h"
#include "AcArray.h"
#include "rxoverrule.h"

class AcRxMemberImp;
class AcRxMemberCollectionImp;
class AcRxValue;
class AcRxValueType;
class AcRxAttributeCollection;
class AcRxMemberIteratorImp;
class AcRxMemberQueryContextImp;
class AcRxMemberQueryEngineImp;
class AcRxPromotingQueryContext;

//*************************************************************************
// AcRxMember
//*************************************************************************
/// <summary>
/// Base class for all members. Encapsulates common member properties and 
/// behavior.
/// </summary>
///
class AcRxMember : public Pimpl::ApiPart<AcRxObject, AcRxMemberImp>
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxMember, ACBASE_PORT);

    /// <summary>
    /// Returns the name of the member
    /// </summary>
    ///
    /// <returns>
    /// Returns const ACHAR* that points to the name 
    /// </returns>
    ///
    ACBASE_PORT const ACHAR* name() const throw();

    /// <summary>
    /// Returns the localized name of the member, if any.
    /// </summary>
    ///
    /// <returns>
    /// Returns AcString object that contains the name 
    /// </returns>
    ///
    ACBASE_PORT AcString localName() const throw();

    /// <summary>
    /// Returns the type of the member.
    /// </summary>
    ///
    /// <returns>
    /// Returns const reference to an AcRxValueType object 
    /// </returns>
    ///
    ACBASE_PORT const AcRxValueType& type()const throw();

    /// <summary>
    /// Returns the immutable collection of attributes for this member.
    /// </summary>
    ///
    /// <returns>
    /// Returns const reference to an AcRxAttributeCollection object 
    /// </returns>
    ///
    ACBASE_PORT const AcRxAttributeCollection& attributes() const throw();

    /// <summary>
    /// Returns the collection of attributes for this member.
    /// </summary>
    ///
    /// <returns>
    /// Returns reference to an AcRxAttributeCollection object 
    /// </returns>
    ///
    ACBASE_PORT AcRxAttributeCollection& attributes() throw();

    /// <summary>
    /// Returns the owner of this member.
    /// </summary>
    ///
    /// <returns>
    /// Returns pointer to an AcRxObject if it has an owner, otherwise it returns NULL 
    /// </returns>
    ///
    ACBASE_PORT const AcRxObject* owner() const throw();

    /// <summary>
    /// Returns the children of this member.
    /// </summary>
    ///
    /// <returns>
    /// Returns pointer to an AcArray object if it has children 
    /// </returns>
    ///
    ACBASE_PORT const AcArray<const AcRxMember*>* children() const throw();

    /// <summary>
    /// deletes the member passed in and sends "goodbye" notification via AcRxMemberReactor.
    /// </summary>
    ///
    ACBASE_PORT static void deleteMember(const AcRxMember* pMember) throw();

#pragma push_macro("new")
#undef new
    /// <summary>
    /// new operator
    /// </summary>
    ACBASE_PORT static void* operator new(size_t size);
    /// <summary>
    /// debug new operator
    /// </summary>
    ACBASE_PORT static void* operator new(size_t size, const char *pFName, int nLine);
#pragma pop_macro("new")
protected:
    friend class AcRxMemberImp;
    ACBASE_PORT virtual ~AcRxMember() throw();
    ACBASE_PORT AcRxMember(AcRxMemberImp*) throw();

    /// <summary>
    /// The function returns the localized name of the member, if any.
    /// Derived class can override function to provide custom implementation.
    /// </summary>
    ///
    /// <returns>
    /// Returns AcString object that contains the name 
    /// </returns>
    ///
    ACBASE_PORT virtual AcString subLocalName() const;

    /// <summary>
    /// The function returns the children of the member.
    /// The difference between subChildren and subChildrenEx is in memory management. 
    /// Derived class can override function to provide custom implementation. The changes to the children array
	/// are cached after the initial call and the derived class will not have a chance to modify the array 
	/// on subsequent calls to children()
	/// The default implementation calls subChildren first. If that method returns Acad::eNotApplicable,
	/// then subChildrenEx is called. 
    /// </summary>
    ///
    /// <param name="children">
    /// Input reference to an AcArray object, to receive the children. 
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subChildren(AcArray<const AcRxMember*>& children) const;
#ifndef __GNUC__
protected:
#else
public:
#endif
#pragma push_macro("delete")
#undef delete
    //protected delete operators so that client code is forced to delete AcRxMember objects
    //using deleteMember above.
    ACBASE_PORT static void operator delete(void *p);
    ACBASE_PORT static void operator delete(void *p, const char *pFName, int nLine);
    ACBASE_PORT static void operator delete[](void *p);
    ACBASE_PORT static void operator delete[](void *p, const char *pFName, int nLine);
#pragma pop_macro("delete")    
private:
#pragma push_macro("new")
#undef new
    //made private so that arrays cannot be created.
    static void* operator new[](size_t size);
    static void* operator new[](size_t size, const char *pFName, int nLine);
#pragma pop_macro("new")    

    /// <summary>
    /// The function returns the children of the member.
    /// The difference between subChildren and subChildrenEx is in memory management. 
    /// Derived classes that override this function are responsible for managing the pChildren 
	/// array - allocationg and deleting. the base class will not hold on to the array and will not call it 
	//  for every invocation of children()
	/// The default implementation calls subChildren first. If that method returns Acad::eNotApplicable,
	/// the subChildrenEx is called. 
	///
	/// </summary>
    ///
    /// <param name="children">
    /// Output reference to an AcArray object, that contains the children. 
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT virtual Acad::ErrorStatus subChildrenEx(AcArray<const AcRxMember*>*& pChildren) const;
};

//*************************************************************************
// AcRxEnumTag
//*************************************************************************
/// <summary>
/// This class is used to store the enumeration constant value.
/// </summary>
///
class AcRxEnumTag : public AcRxMember
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxEnumTag, ACBASE_PORT);
    /// <summary>
    /// Constructor
    /// </summary>
    ///
    /// <param name="name">
    /// The text that is used for the string representation of the constant.
    /// </param>
    ///
    /// <param name="value">
    /// The value of the enumeration constant.
    /// </param>
    ///
    ACBASE_PORT AcRxEnumTag(const ACHAR* name, const AcRxValue& value) throw();

    /// <summary>
    /// Returns the value of the enumeration constant.
    /// </summary>
    ///
    /// <returns>
    /// Returns const reference to an AcRxValue value 
    /// </returns>
    ///
    ACBASE_PORT const AcRxValue& value() const;

    /// <summary>
    /// Returns a localized string representation of the 
    /// enumeration constant, if available. If the member has 
    /// alternate localized name attribute, then it tries to return
    /// the alternate localized string representation using the 
    /// AcRxAlternateLocalizedNameAttribute information.
    /// </summary>
    ///
    /// <returns>
    /// Returns AcString object that contains the name 
    /// </returns>
    ///
    ACBASE_PORT AcString alternateLocalName() const;
protected:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT ~AcRxEnumTag();
    /// <summary>
    /// Derived class can override this method to provide custom implementation.
    /// </summary>
    ///
    /// <returns>
    /// Returns AcString object that contains the name 
    /// </returns>
    ///
    ACBASE_PORT virtual AcString subAlternateLocalName() const;
};

//*************************************************************************
// AcRxMemberCollection
//*************************************************************************
/// <summary>
/// This class is a collection of AcRxMember objects.
/// </summary>
///
class AcRxMemberCollection : public Pimpl::ApiPart<void, AcRxMemberCollectionImp>
{
public:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT virtual ~AcRxMemberCollection();

    /// <summary>
    /// Returns the number of members in the collection.
    /// </summary>
    ///
    /// <returns>
    /// Returns the number of AcRxMember objects in the collection 
    /// </returns>
    ///
    virtual int count() const;

    /// <summary>
    /// This method returns a member at the passed in index.
    /// </summary>
    ///
    /// <param name="index">
    /// Passed in index of interest
    /// </param>
    ///
    /// <returns>
    /// Returns a pointer to AcRxMember object at the passed in index.
    /// </returns>
    ///
    virtual AcRxMember* getAt(int index) const;

protected:
    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxMemberCollection();

private:
    friend class AcRxMemberCollectionImp;
    AcRxMemberCollection(AcRxMemberCollectionImp* pImp);
};

//*************************************************************************
// AcRxMemberCollectionBuilder
//*************************************************************************
/// <summary>
/// This class can be used to return collection of AcRxMember objects
/// </summary>
///
class AcRxMemberCollectionBuilder : public Pimpl::ApiPart<void, AcRxMemberCollectionImp>
{
public:
    /// <summary>
    /// This method adds the AcRxMember object to the AcRxMemberCollectionBuilder
    /// object collection.
    /// </summary>
    ///
    /// <param name="member">
    /// Input member object to add to the collection
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus add(AcRxMember* member);

    /// <summary>
    /// returns the owner of the collection
    /// </summary>
    ACBASE_PORT const AcRxClass* owner() const;
private:
    friend class AcRxMemberCollectionImp;
    AcRxMemberCollectionBuilder(AcRxMemberCollectionImp*, const AcRxClass* owner);
    ~AcRxMemberCollectionBuilder();
    const AcRxClass* m_owner;
};


//*************************************************************************
// AcRxMemberIterator
//*************************************************************************
/// <summary>
/// This class provides the ability to iterate through all AcRxMember objects 
/// of an object
/// </summary>
///
class AcRxMemberIterator : public Pimpl::ApiPart<void, AcRxMemberIteratorImp>
{
public:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT virtual ~AcRxMemberIterator();

    /// <summary>
    /// The function reports whether the iterator has iterated to the end.
    /// </summary>
    ///
    /// <returns> 
    /// It returns true if it has reached the end, otherwise it returns false.
    /// </returns>
    ///
    ACBASE_PORT virtual bool done();

    /// <summary>
    /// Positions the iterator to the next object in the structure. 
    /// </summary>
    ///
    /// <returns> 
    /// Returns true if and only if the iterator is not done.
    /// </returns>
    ///
    ACBASE_PORT virtual bool next();

    /// <summary>
    /// The function tries to return the value at the iterator's 
    /// current location.
    /// </summary>
    ///
    /// <returns> 
    /// Returns a pointer to AcRxMember if successful, otherwise it returns NULL.
    /// </returns>
    ///
    ACBASE_PORT virtual AcRxMember* current() const;

    /// <summary>
    /// Returns a member identified by the name.
    /// </summary>
    ///
    /// <param name="name">
    /// Input the name that identifies the member to find.
    /// </param>
    ///
    /// <returns> 
    /// Returns the pointer to AcRxMember identified by the string name, or NULL 
    /// if there is no such AcRxMember with the name.
    /// </returns>
    ///
    ACBASE_PORT virtual AcRxMember* find(const ACHAR* name) const;

protected:
    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxMemberIterator();

private:
    friend class AcRxMemberIteratorImp;
    AcRxMemberIterator(AcRxMemberIteratorImp*);
};


//*************************************************************************
// AcRxMemberQueryContext
//*************************************************************************
/// <summary>
/// This class provides other contextual data about the query to influence 
/// the set of members. The derived classes can implement their own context 
/// and return the members relevant to the context. 
/// </summary>
///
class AcRxMemberQueryContext : public Pimpl::ApiPart<AcRxObject, AcRxMemberQueryContextImp>
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxMemberQueryContext, ACBASE_PORT);

    /// <summary>
    /// This method is called by AcRxMemberQueryEngine::newMemberIterator to 
    /// get the members relevant to the context.
    /// </summary>
    ///
    /// <param name="facets">
    /// Input set of classes for which to get the members.
    /// </param>
    ///
    /// <returns> 
    /// Returns the pointer to AcRxMemberIterator if there are members, otherwise it returns NULL.
    /// </returns>
    ///
    ACBASE_PORT AcRxMemberIterator* newMemberIterator(const AcArray<const AcRxClass*>& facets) const;

protected:
    friend class AcRxMemberQueryContextImp;

    /// <summary>
    /// Constructor
    /// </summary>
    ///
    ACBASE_PORT AcRxMemberQueryContext();

    /// <summary>
    /// Destructor
    /// </summary>
    ///
    ACBASE_PORT virtual ~AcRxMemberQueryContext();

    /// <summary>
    /// The derived class must override this method and return the members 
    /// appropriate to the context.
    /// </summary>
    ///
    /// <param name="facets">
    /// Input reference to an AcArray object, to receive the facets. 
    /// </param>
    ///
    /// <returns> 
    /// Returns pointer to AcRxMemberIterator if there are members; otherwise, returns NULL.
    /// </returns>
    ///
    virtual AcRxMemberIterator* subNewMemberIterator(const AcArray<const AcRxClass*>& facets) const = 0;
};


//*************************************************************************
// AcRxFacetProvider
//*************************************************************************
/// <summary>
/// Abstract base class for all facet providers. The class provides a mechanism 
/// to supply additional members for a given class in a given context. The 
/// derived class can register as a facet provider using AcRxMemberQueryEngine 
/// engine. The engine will call getFacets with the object whose members are 
/// being queried, along with the context. The class can add the facet objects 
/// that supply the additional members to the facet collection that is passed.
/// </summary>
///
class AcRxFacetProvider : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxFacetProvider, ACBASE_PORT);

    /// <summary>
    /// This method is called by AcRxMemberQueryEngine everytime AcRxMemberQueryEngine::newMemberIterator
    /// is called. The derived class can add the facets that supply additional 
    /// members in a given context, to the passed collection.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object, which is queried for its members.
    /// </param>
    ///
    /// <param name="pContext">
    /// Input query context object. 
    /// </param>
    ///
    /// <param name="facets">
    /// Reference to the facet collection. The class can add facets that 
    /// supply additonal members.
    /// </param>
    ///
    virtual void getFacets(const AcRxObject* pO, const AcRxMemberQueryContext* pContext, AcArray<const AcRxClass*>& facets) = 0;
};


//*************************************************************************
// AcRxMemberReactor
//*************************************************************************
/// <summary>
/// The AcRxMemberReactor can be used to get AcRxMember notifications, like 
/// when the member is destroyed.
/// </summary>
///
class AcRxMemberReactor
{
public:
    /// <summary>
    /// Destructor
    /// </summary>
    ///
    virtual ~AcRxMemberReactor() {}

    /// <summary>
    /// This function is invoked when the member is being deleted from memory.
    /// </summary>
    ///
    /// <param name="pMember">
    /// Passed in const pointer to the object being destroyed.
    /// </param>
    ///
	virtual void goodbye(const AcRxMember* pMember) { (pMember); }//Unreferenced parameter
};


//*************************************************************************
// AcRxMemberQueryEngine
//*************************************************************************
/// <summary>
/// The AcRxMemberQueryEngine object is used to query the members and register the 
/// facet providers. This class is a singleton with a static method that returns 
/// a global instance of the object.
/// </summary>
///
class AcRxMemberQueryEngine: public Pimpl::ApiPart<void, AcRxMemberQueryEngineImp>
{
public:
    /// <summary>
    /// Returns the singleton object
    /// </summary>
    ///
    /// <returns> 
    /// Returns pointer to an AcRxMemberQueryEngine if successful, otherwise returns NULL.
    /// </returns>
    ///
    ACBASE_PORT static AcRxMemberQueryEngine* theEngine();

    /// <summary>
    /// This method can be used to find an AcRxMember of an object using the name.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object that need to be searched for the member.
    /// </param>
    ///
    /// <param name="name">
    /// Input the name of the member to find.
    /// </param>
    ///
    /// <param name="pContext">
    /// Optional. Input the context data that is used to query the member.
    /// </param>
    ///
    /// <returns> 
    /// Returns pointer to an AcRxMember if successful, otherwise returns NULL.
    /// </returns>
    ///
    ACBASE_PORT AcRxMember* find(const AcRxObject* pO, const ACHAR* name, const AcRxMemberQueryContext* pContext = NULL) const;

    /// <summary>
    /// This method can be used to get the members of an object.
    /// </summary>
    ///
    /// <param name="pO">
    /// Input object to query for members.
    /// </param>
    ///
    /// <param name="pContext">
    /// Optional. Input the context data that is used to query the members.
    /// </param>
    ///
    /// <returns> 
    /// Returns pointer to AcRxMemberIterator if there are members, otherwise returns NULL.
    /// </returns>
    ///
    ACBASE_PORT AcRxMemberIterator* newMemberIterator(const AcRxObject* pO, const AcRxMemberQueryContext* pContext = NULL) const;

    /// <summary>
    /// This method can be used to query the defaultContext that can be 
    /// used to query for members.
    /// </summary>
    ///
    /// <returns> 
    /// Returns pointer to AcRxMemberQueryContext.
    /// </returns>
    ///
    ACBASE_PORT const AcRxMemberQueryContext* defaultContext();

    /// <summary>
    /// This method can be used to query the promotingContext that can be 
    /// used to query for members. The promoting context can be used when 
    /// certain members need to be promoted with respect to certain other 
    /// members. For example using the promoting context we can get 
    /// three promoted members Start X, Start Y and Start Z, instead of 
    /// a StartPoint member. 
    /// </summary>
    ///
    /// <returns> 
    /// Returns pointer to AcRxPromotingQueryContext.
    /// </returns>
    ///
    ACBASE_PORT const AcRxPromotingQueryContext* promotingContext();

    /// <summary>
    /// This method can be be used to add a facet provider. 
    /// </summary>
    ///
    /// <param name="pProvider">
    /// Input facet provider that is to be added.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus addFacetProvider(AcRxFacetProvider* pProvider);

    /// <summary>
    /// This method can be be used to remove a facet provider. 
    /// </summary>
    ///
    /// <param name="pProvider">
    /// Input facet provider that is to be removed.
    /// </param>
    ///
    /// <returns> Returns Acad::eOk if successful; otherwise, returns an AutoCAD error status. </returns>
    ///
    ACBASE_PORT Acad::ErrorStatus removeFacetProvider(AcRxFacetProvider* pProvider);

    /// <summary>
    /// Adds AcRxMemberReactor reactor
    /// </summary>
    ///
    /// <param name="pReactor">
    /// Input AcRxMemberReactor to add
    /// </param>
    ///
    ACBASE_PORT void addReactor(AcRxMemberReactor* pReactor);

    /// <summary>
    /// Removes AcRxMemberReactor reactor
    /// </summary>
    ///
    /// <param name="pReactor">
    /// Input AcRxMemberReactor to remove
    /// </param>
    ///
    ACBASE_PORT void removeReactor(AcRxMemberReactor* pReactor);

private:
    friend class AcRxMemberQueryEngineImp;
    AcRxMemberQueryEngine(AcRxMemberQueryEngineImp*);
    ~AcRxMemberQueryEngine();

};

/// <summary>
/// Base class for overrules for AcRxMember.
/// </summary>
///
class AcRxMemberOverrule : public AcRxOverruleBase
{
public:
    //Utility class to store a member, overrule pair
    struct Record
    {
        AcRxMember* m_pMember;
        AcRxMemberOverrule* m_pOverrule;
        Record()
            :m_pMember(NULL)
            ,m_pOverrule(NULL) {}
        Record(AcRxMember* pMember, AcRxMemberOverrule* pOverrule)
            :m_pMember(pMember)
            ,m_pOverrule(pOverrule) {}
    };
    ACRX_DECLARE_MEMBERS_EXPIMP(AcRxMemberOverrule, ACBASE_PORT);
    /// <summary>
    /// Adds an overrule for the specified member.
    /// </summary>
    ///
    /// <param name="pOverruledSubject">
    /// The member whose behavior is to be modified.
    /// </param>
    /// <param name="pOverrule">
    /// The overrule object to be added.
    /// </param>
    /// <param name="bAddAtLast">
    /// Parameter the determines what order the overrules are executed. Normally, the last overrule
    /// to be added is the one to be executed first.
    /// </param>
    ///
    ACBASE_PORT static Acad::ErrorStatus addOverrule(AcRxMember* pOverruledSubject, AcRxMemberOverrule* pOverrule, bool bAddAtLast = false);
    /// <summary>
    /// Removes an overrule from the specified member.
    /// </summary>
    ///
    /// <param name="pOverruledSubject">
    /// The member from which to remove the overrule from.
    /// </param>
    /// <param name="pOverrule">
    /// The overrule object to be removed.
    /// </param>
    ///
    ACBASE_PORT static Acad::ErrorStatus removeOverrule( AcRxMember* pOverruledSubject, AcRxMemberOverrule* pOverrule);
    /// <summary>
    /// Removes overrules
    /// </summary>
    ///
    /// <param name="overrules">
    /// Member, overrule pairs to remove.
    /// </param>
    ///
    ACBASE_PORT static Acad::ErrorStatus removeOverrules(const AcArray<Record>& overrules);
};
