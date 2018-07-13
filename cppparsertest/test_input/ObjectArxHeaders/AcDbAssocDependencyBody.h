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
// CREATED BY: Jiri Kripac                                 August 2007
//
// DESCRIPTION:
//
// AcDbAssocDependencyBody abstract base class for deriving custom dependency
// body classes.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocDependency.h"
#pragma pack (push, 8)


/// <summary> <para>
/// Abstract base class for deriving custom dependency body classes that implement
/// functionality of custom dependencies.
/// </para> <para>
/// An object of a class derived from the AcDbAssocDependencyBody class is always 
/// owned by a parent AcDbAssocDependency object. The AcDbAssocDependency object has 
/// an AcDbHardOwnershipId on it and the AcDbAssocDependencyBody::ownerId() of the 
/// object returns the AcDbObjectId of its parent AcDbAssocDependency object. 
/// </para> <para>
/// Therefore a custom dependency object (in the logical sense of the word "object") 
/// is always represented by a pair of physical AcDbObjects: 
///
///  - The parent dependency object of the AcDbAssocDependency class (or possibly, but
///    less commonly, of a derived class).
///  - The dependency body object of a custom class derived from the 
///    AcDbAssocDependencyBody abstract base class.
///
/// </para> <para>
/// This factoring out of the functionality of the custom dependencies into separate 
/// classes derived from the AcDbAssocDependencyBody class, instead of deriving the 
/// custom dependency classes directly from the AcDbAssocDependency class, allows
/// better handling of the situations when the application code that implements 
/// the custom dependency behavior is not available. Only the custom object of the
/// AcDbAssocDependencyBody-derived class will become a proxy, but its parent 
/// AcDbAssocDependency object will always be available and the associative mechanism
/// can still function to some extent.
/// </para> <para>
/// The abstract AcDbAssocDependencyBody base class defines a set of virtual methods 
/// named xxxxxxOverride() that correspond to methods named xxxxxx() in the parent
/// AcDbAssocDependency class. When a method xxxxxx() is called on the parent dependency 
/// object and the dependency object owns an dependency body object, the corresponding 
/// xxxxxxOverride() method on the dependency body object is called and it either 
/// supersedes or amends the default xxxxxx() implementation, depending on the 
/// particular method. 
/// </para> <para>
/// If the dependency object does not own an dependency body object or if the 
/// dependency body object does not override the xxxxxxOverride() method, the default
/// implementation in the parent dependency object is performed. Also, when the 
/// custom dependency body object becomes a proxy because its application code
/// is not available, the parent dependency method just performs its default 
/// implementation.
/// </para> <para>
/// Custom dependency body classes derived from the AcDbAssocDependencyBody class 
/// implement their behavior by overriding the appropriate xxxxxxOverride() 
/// methods. Only the evaluateOverride() method must always be overridden in 
/// the custom classes. If not overridden, the other xxxxxxOverride() methods will 
/// do nothing and the default implementation in the parent AcDbAssocDependency 
/// object will be performed. This may be the appropriate behavior in most 
/// cases.
/// </para> <para>
/// Because each AcDbAssocDependencyBody object is owned by its parent 
/// AcDbAssocDependency object, erasing the parent AcDbAssocDependency object
/// also erases the owned AcDbAssocDependencyBody object. There is no need to 
/// erase AcDbAssocDependencyBody objects explicitly.
/// </para> </summary> 
///
class ACDBCORE2D_PORT AcDbAssocDependencyBody : public AcDbObject
{
public: 
    ACRX_DECLARE_MEMBERS(AcDbAssocDependencyBody);

    explicit AcDbAssocDependencyBody(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);
    virtual ~AcDbAssocDependencyBody();

    /// <summary>
    /// Returns AcDbObjectId of the parent AcDbAssocDependency that owns this 
    /// dependency body object.
    /// </summary>
    ///
    AcDbObjectId parentDependency() const { return ownerId(); }

    // The following non-virtual methods are just shortcuts that just forward 
    // to the parent AcDbAssocDependency class, to save some typing for the
    // implementers of the derived custom dependency body classes

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocDependency that
    /// owns this dependency body object.
    /// </summary>
    ///
    AcDbAssocStatus status() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocDependency that
    /// owns this dependency body object.
    /// </summary>
    ///
    Acad::ErrorStatus setStatus(AcDbAssocStatus newStatus, 
                                bool notifyOwningAction = true);

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocDependency that
    /// owns this dependency body object.
    /// </summary>
    ///
    AcDbObjectId owningAction() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocDependency that
    /// owns this dependency body object.
    /// </summary>
    ///
    AcDbObjectId dependentOnObject() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocDependency that
    /// owns this dependency body object.
    /// </summary>
    ///
    bool isAttachedToObject() const { return !dependentOnObject().isNull(); }

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocDependency that
    /// owns this dependency body object.
    /// </summary>
    ///
    bool isActionEvaluationInProgress() const;

    /// <summary>
    /// Just a shortcut, calls the method on the parent AcDbAssocDependency that
    /// owns this dependency body object.
    /// </summary>
    ///
    AcDbAssocEvaluationCallback* currentEvaluationCallback() const;

public: 
    
    // Virtual methods that can be overridden by the derived classes

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocDependency 
    /// class that owns this dependency body object. It has to be overridden.
    /// </summary>
    ///
    virtual void evaluateOverride() = 0;

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocDependency 
    /// class that owns this dependency body object. It does not need to be 
    /// overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus updateDependentOnObjectOverride()
    { return Acad::eNotImplemented; }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocDependency 
    /// class that owns this dependency body object. It does not need to be 
    /// overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus hasCachedValueOverride(bool& hasCachedVal) const
    { 
        ADESK_UNREFED_PARAM(hasCachedVal);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocDependency 
    /// class that owns this dependency body object. It does not need to be 
    /// overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isRelevantChangeOverride(bool& isRelevChange) const
    {
        ADESK_UNREFED_PARAM(isRelevChange);
        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocDependency 
    /// class that owns this dependency body object. It does not need to be 
    /// overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isDependentOnTheSameThingAsOverride(const AcDbAssocDependency* pOtherDependency, 
                                                                  bool& isDependentOnSameThing) const
    { 
        ADESK_UNREFED_PARAM(pOtherDependency);
        ADESK_UNREFED_PARAM(isDependentOnSameThing);

        return Acad::eNotImplemented; 
    }

    /// <summary>
    /// Called from the corresponding method of the parent AcDbAssocDependency 
    /// class that owns this dependency body object. It does not need to be 
    /// overridden.
    /// </summary>
    ///
    virtual Acad::ErrorStatus isEqualToOverride(const AcDbAssocDependency* pOtherDependency, bool& isEqual) const
    { 
        ADESK_UNREFED_PARAM(pOtherDependency);
        ADESK_UNREFED_PARAM(isEqual);
        return Acad::eNotImplemented;
    }

    /// <summary>
    /// Called from the corresponding persistent reactor callback method of the 
    /// parent AcDbAssocDependency class that owns this dependency body object. 
    /// It does not need to be overridden.
    /// </summary>
    ///
    virtual void erasedOverride(const AcDbObject* pDbObj, Adesk::Boolean isErasing)
    {
        ADESK_UNREFED_PARAM(pDbObj);
        ADESK_UNREFED_PARAM(isErasing);
    }

    /// <summary>
    /// Called from the modified() persistent reactor callback method of the 
    /// parent AcDbAssocDependency class that owns this dependency body object. 
    /// It does not need to be overridden.
    /// </summary>
    ///
    virtual void modifiedOverride(const AcDbObject* pDbObj) 
    {
        ADESK_UNREFED_PARAM(pDbObj);
    }

    /// <summary>
    /// Called from the copied() persistent reactor callback method of the 
    /// parent AcDbAssocDependency class that owns this dependency body object. 
    /// It does not need to be overridden.
    /// </summary>
    ///
    virtual void clonedOverride(const AcDbObject* pDbObj, const AcDbObject* pNewObj)
    {
        ADESK_UNREFED_PARAM(pDbObj);
        ADESK_UNREFED_PARAM(pNewObj);
    }

    /// <summary><para>
    /// Called from AcDbAssocManager::auditAssociativeData() after file open and possibly
    /// after some other scenarios when the associative data may need to be audited and fixed-up.
    /// At this time custom code may also initialize internal chaches that were not saved to dwg/dxf 
    /// file, or do some other work.
    /// </para><para> 
    /// The dependency body may request the parent action to be erased by setting kErasedAssocStatus
    /// to parentActionHandling output argument. Setting kChangedDirectlyAssocStatus to
    /// parentActionHandling will make the parent action evaluate after the audit of all 
    /// actions has been completed.
    /// </para><para> 
    /// An example of possible and inevitable inconsistencies is when the drawing was modified 
    /// in an AutoCAD release that didn't have code for the action, the action body was a proxy
    /// and therefore didn't react to notifications and didn't evaluate.
    /// </para><para> 
    /// Another example of possible and inevitable ininconsistencies are references to objects 
    /// that are not in the database any more because their owning objects were erased, the 
    /// drawing was then saved, and these objects with erased owners were not saved to 
    /// database. No notifications happen about the erase of these objects because they were 
    /// not actually erased, so the actions cannot know that these objects are not in the database 
    /// any more and may still hold AcDbObjectIds of these "lazily-erased" objects. 
    /// </para><para>    
    /// Before auditAssociativeDataOverride() is called, the system performs overall 
    /// checks and fixes for cases like a dependency depending on a non-existent object,
    /// checks proper links between network, action, action body, action parameters, and 
    /// dependencies, etc., so that these general checks do not need to be performed by
    /// the custom code.
    /// </para></summary>
    ///
    virtual void auditAssociativeDataOverride(AcDbAssocStatus& parentActionHandling);

}; // class AcDbAssocDependencyBody


#pragma pack (pop)


