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
//  AcPublishReactors.h - Reactors File
//
#ifndef _ACPUBLISHREACTORS_H
#define _ACPUBLISHREACTORS_H

#include "rxobject.h"
#include "AcArray.h"
#include "AcPlDSDData.h"
#include "AcPlDSDEntry.h"
#include "AcDMMUtils.h"
#include "AcDMMEPlotProperty.h"
#include "AcPlPlotErrorHandler.h"
#include "AcPlPlotLogger.h"

// Classes defined in this header file:
class AcPublishReactorManager;
class AcPublishReactor;
class AcPublishReactorInfo;

class AcPublishBeginJobInfo;
class AcPublishSheetInfo;

/// <summary>
/// A container class for a name value pair to be stored in a client's
/// private data area of the DSD file
class AcNameValuePair
{
public:

    /// <summary>
    /// default constructor
    /// </summary>
    ///
    /// <remarks>
    /// creates an empty name value pair
    /// </remarks>
    AcNameValuePair() 
    {
        m_pName = NULL;
        m_pValue = NULL;
    };

    /// <summary>
    /// destructor
    /// </summary>
    ///
    ~AcNameValuePair() 
    {
        if (NULL != m_pName)
            delete [] m_pName;
        if (NULL != m_pValue)
            delete [] m_pValue;
    };

    /// <summary>
    /// constructs a name value pair from a name and a value
    /// </summary>
    ///
    /// <param name="name">
    /// a string defining the name, a null-terminated mbcs string
    /// </param>
    ///
    /// <param name="value">
    /// The value string, a null-terminated msbcs string.
    /// </param>
    ///
    AcNameValuePair(const ACHAR *name, const ACHAR *value)
    {
        if (NULL != name) {
            size_t nSize = ::wcslen(name) + 1;
            m_pName = new ACHAR[nSize];
            errno_t err = ::wcscpy_s(m_pName, nSize, name);
            assert(err == 0);
        } else
            m_pName = NULL;
        
        if (NULL != value) {
            size_t nSize = ::wcslen(value) + 1;
            m_pValue = new ACHAR[nSize];
            errno_t err = ::wcscpy_s(m_pValue, nSize, value);
            assert(err == 0);
        } else
            m_pValue = NULL;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object to be copied
    /// </param>
    ///
    AcNameValuePair(const AcNameValuePair &src)
    : m_pName(NULL),
      m_pValue(NULL)
    {
        *this = src;
    }    

    /// <summary>
    /// accessor for the item name
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the null terminated mbcs name string
    /// </returns>
    const ACHAR * name() const {return m_pName;};


    /// <summary>
    /// accessor for the item value
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the null terminated mbcs value string
    /// </returns>
    const ACHAR * value() const {return m_pValue;};

    /// <summary>
    /// mutator for the item name
    /// </summary>
    ///
    /// <param name="name">
    /// a const pointer to an mbcs string to be assigned as item name
    /// </param>
    void setName(const ACHAR * name)
    {
        if (NULL != m_pName)
            delete [] m_pName;
        if (NULL != name) {
            size_t nSize = ::wcslen(name) + 1;
            m_pName = new ACHAR[nSize];
            errno_t err = ::wcscpy_s(m_pName, nSize, name);
            assert(err == 0);
        } else
            m_pName = NULL;
    }

    /// <summary>
    /// mutator for the item value
    /// </summary>
    ///
    /// <param name="value">
    /// a const pointer to an mbcs string to be assigned as item value
    /// </param>
    void setValue(const ACHAR * value)
    {
        if (NULL != m_pValue)
            delete [] m_pValue;
        if (NULL != value) {
            size_t nSize = ::wcslen(value) + 1;
            m_pValue = new ACHAR[nSize];
            errno_t err = ::wcscpy_s(m_pValue, nSize, value);
            assert(err == 0);
        } else
            m_pValue = NULL;
    }


    /// <summary>
    /// operator= also used by copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object whose values will be copied to this object
    /// </param>
    ///
    /// <returns>
    /// returns this object
    /// </returns>
    AcNameValuePair & operator= (const AcNameValuePair &src)
    {
        if (this == &src)
            return *this;

        setName(src.m_pName);
        setValue(src.m_pValue);
        return *this;
    }

private:
    // TODO: Should we upgrade to use XML instead of INI?
    //
    ACHAR * m_pName;
    ACHAR * m_pValue;    
};

typedef AcArray<AcNameValuePair> AcNameValuePairVec;

/// <summary>
/// This class is the context information supplied by the 
/// OnAboutToBeginBackgroundPublishing notifier of AcPublishReactor. 
/// You do not need to construct this class. This is handed to the 
/// OnAboutToBeginBackgroundPublishing method.
/// </summary>
class AcPublishBeforeJobInfo
{
public:

    /// <summary>
    /// default constructor
    /// </summary>
    ///
    /// <remarks>
    /// creates an empty AcPublishBeforeJobInfo. Clients do not
    /// construct this object, it is created by the DMM and handed
    /// to their reactors
    /// </remarks>
    AcPublishBeforeJobInfo() {};

    /// <summary>
    /// destructor
    /// </summary>
    ///
    virtual ~AcPublishBeforeJobInfo() {};

    /// <summary>
    /// read only accesss to the DSD object
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the DSD object for this publish job
    /// </returns>
    virtual const AcPlDSDData * GetDSDData() = 0;

    /// <summary>
    /// read/write access to the client's private DSD data
    /// </summary>
    ///
    /// <param name="sectionName">
    /// the name the client assigned to its private DSD data section
    /// as a null terminated mbcs string.
    /// </param>
    ///
    /// <returns>
    /// returns empty AcNameValuePairVec, if section not found, 
    /// otherwise this returns a const AcNameValuePairVec object with
    /// name value pairs for the section requested.
    /// </returns>
    virtual const AcNameValuePairVec 
        GetPrivateData(const ACHAR * sectionName) = 0;

    /// <summary>
    /// replaces a section of the same name
    /// will fail if it attempts to replace a "recognized" section of
    /// standard DSD data
    /// returns true on success, false on error
    /// </summary>
    ///
    /// <param name="sectionName">
    /// the name the client assigned to its private DSD data section
    /// as a null terminated mbcs string.
    /// </param>
    ///
    ///
    /// <param name="nameValuePairVec">
    /// Vector of name and value pairs that clients want to update in their
    /// section in the dsd file
    /// </param>
    ///
    /// <returns>
    /// returns true if section data is updated in the dsd data object
    /// successfully, otherwise returns false.
    /// </returns>
    virtual bool WritePrivateSection(const ACHAR * sectionName, 
        const AcNameValuePairVec nameValuePairVec) = 0;

    // bool for bg/fg (this isn't in public dsd data)
    virtual bool JobWillPublishInBackground() = 0;    
};

/// <summary>
/// This class is the context information supplied by the 
/// OnAboutToBeginPublishing  notifier of AcPublishReactor. 
/// You do not need to construct this class. This is handed to the 
/// OnAboutToBeginPublishing  method.
/// </summary>
class AcPublishBeginJobInfo
{
public:

    /// <summary>
    /// default constructor
    /// </summary>
    ///
    /// <remarks>
    /// creates an empty AcPublishBeginJobInfo. Clients do not
    /// construct this object, it is created by the DMM and handed
    /// to their reactors
    /// </remarks>
    AcPublishBeginJobInfo() {};

    /// <summary>
    /// destructor
    /// </summary>
    ///
    virtual ~AcPublishBeginJobInfo() {};

    /// <summary>
    /// read only accesss to the DSD object
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the DSD object for this publish job
    /// </returns>
    virtual const AcPlDSDData * GetDSDData() = 0;

    /// <summary>
    /// read/write access to the client's private DSD data
    /// </summary>
    ///
    /// <param name="sectionName">
    /// the name the client assigned to its private DSD data section
    /// as a null terminated mbcs string.
    /// </param>
    ///
    /// <returns>
    /// returns empty AcNameValuePairVec, if section not found, 
    /// otherwise this returns a const AcNameValuePairVec object with
    /// name value pairs for the section requested.
    /// </returns>
    virtual const AcNameValuePairVec 
        GetPrivateData(const ACHAR * sectionName) = 0;

    /// <summary>
    /// replaces a section of the same name
    /// will fail if it attempts to replace a "recognized" section of
    /// standard DSD data
    /// returns true on success, false on error
    /// </summary>
    ///
    /// <param name="sectionName">
    /// the name the client assigned to its private DSD data section
    /// as a null terminated mbcs string.
    /// </param>
    ///
    ///
    /// <param name="nameValuePairVec">
    /// Vector of name and value pairs that clients want to update in their
    /// section in the dsd file
    /// </param>
    ///
    /// <returns>
    /// returns true if section data is updated in the dsd data object
    /// successfully, otherwise returns false.
    /// </returns>
    virtual bool WritePrivateSection(const ACHAR * sectionName, 
        const AcNameValuePairVec nameValuePairVec) = 0;

    // bool for bg/fg (this isn't in public dsd data)
    virtual bool JobWillPublishInBackground() = 0;    

    // plot logger
    /// <summary>
    /// provides access to the plot logger object
    /// </summary>
    ///
    /// <returns>
    /// a pointer to the plot logger used by Publish
    /// </returns>
    ///
    /// <remarks>
    /// clients don't need to create or destroy this object
    /// </remarks>
    virtual AcPlPlotLogger * GetPlotLogger() = 0;
};

/// <summary>
/// This class is the context information supplied by the 
/// OnBeginPublishingSheet notifier of AcPublishReactor. You do not need to
/// construct this class. This is handed to the OnBeginPublishingSheet method.
/// </summary>
class AcPublishSheetInfo
{
public:
    /// <summary>
    /// default constructor
    /// </summary>
    ///
    /// <remarks>
    /// creates an empty AcPublishSheetInfo. Clients do not
    /// construct this object, it is created by the DMM and handed
    /// to their reactors
    /// </remarks>
    AcPublishSheetInfo() {};

    /// <summary>
    /// destructor
    /// </summary>
    ///
    virtual ~AcPublishSheetInfo() {};

    /// <summary>
    /// This provides some details about the sheet which is about to
    /// be plotted.
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to a DSD Entry object describing the sheet
    /// </returns>
    virtual const AcPlDSDEntry * GetDSDEntry() = 0;

    /// <summary>
    /// supplies the unique sheet Id (GUID)
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the GUID string for this sheet
    /// </returns>
    virtual const ACHAR * GetUniqueId() = 0;

    /// <summary>
    /// provides access to the plot logger object
    /// </summary>
    ///
    /// <returns>
    /// a pointer to the plot logger used by Publish
    /// </returns>
    ///
    /// <remarks>
    /// clients don't need to create or destroy this object
    /// </remarks>
    virtual AcPlPlotLogger * GetPlotLogger() = 0;
};

/// <summary>
/// This class is the context information supplied by the OnBeginAggregation 
/// notifier of AcPublishReactor. You do not need to construct this class. 
/// This is handed to the OnBeginAggregation method.
/// </summary>
class AcPublishAggregationInfo
{
    // this is context data for the AboutToBeginAggregation notifier
    // it allows clients to add ePlot global properties and resources
    // to the DWF
public:
    /// <summary>
    /// default constructor
    /// </summary>
    ///
    /// <remarks>
    /// creates an empty AcPublishAggregationInfo. Clients do not
    /// construct this object, it is created by the DMM and handed
    /// to their reactors
    /// </remarks>
    AcPublishAggregationInfo() {};

    /// <summary>
    /// destructor
    /// </summary>
    ///
    virtual ~AcPublishAggregationInfo() {};

    /// <summary>
    /// This allows clients to add a list of global properties
    /// to the DWF file's EPlot global section
    /// </summary>
    ///
    /// <param name="props">
    /// a vector of AcDMMEPlotProperties
    /// </param>
    ///
    virtual void AddGlobalProperties(AcDMMEPlotPropertyVec props) = 0;

    /// <summary>
    /// This allows clients to add a list of global resources (files)
    /// to the DWF file
    /// </summary>
    ///
    /// <param name="resources">
    /// a vector of AcDMMResourceInfo objects which include a mime
    /// type, role and a full path to the resource to be added
    /// </param>
    ///
    virtual void AddGlobalResources(AcDMMResourceVec resources) = 0;

    /// <summary>
    /// provides access to the plot logger object
    /// </summary>
    ///
    /// <returns>
    /// a pointer to the plot logger used by Publish
    /// </returns>
    ///
    /// <remarks>
    /// clients don't need to create or destroy this object
    /// </remarks>
    virtual AcPlPlotLogger * GetPlotLogger() = 0;

    /// <summary>
    /// supplies the full path to the final DWF file
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the full path to the final DWF file
    /// </returns>
    virtual const ACHAR* dwfFileName() = 0;

    /// <summary>
    /// supplies the password, if any, needed to open the DWF file
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the password, if any, needed to open the DWF file
    /// </returns>
    virtual const ACHAR* dwfPassword() = 0;
};


/////////////////////////////////////////////////////////////
/// class AcPublishReactorInfo;
/////////////////////////////////////////////////////////////
/// <summary>
/// This class is the context information supplied by the 
/// OnAboutToEndPublishing, OnAboutToMoveFile and OnEndPublish notifiers of 
/// AcPublishRector. You do not need to construct this class. This is handed 
/// to the OnAboutToEndPublishing, OnAboutToMoveFile and OnEndPublish methods.
/// </summary>
class AcPublishReactorInfo
{
public:
    /// <summary>
    /// default constructor
    /// clients don't need to construct this class, it is handed
    /// to their reactors
    /// </summary>
    AcPublishReactorInfo() {};

    /// <summary>
    /// destructor
    /// </summary>
    virtual ~AcPublishReactorInfo() {};

    /// <summary>
    /// supplies the full path to the final DWF file
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the full path to the final DWF file
    /// </returns>
    virtual const ACHAR* dwfFileName() = 0;

    /// <summary>
    /// supplies the full path to the temporary DWF file for this page
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the full path to the temporary DWF file for this 
    /// page
    /// </returns>
    virtual const ACHAR* tempDwfFileName() = 0;

    /// <summary>
    /// supplies the password, if any, needed to open the DWF file
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the password, if any, needed to open the DWF file
    /// </returns>
    virtual const ACHAR* dwfPassword() = 0;

    /// <summary>
    /// is this job being published to multisheet DWF?
    /// </summary>
    ///
    /// <returns>
    /// true if this job is being published to multisheet DWF.
    /// </returns>
    ///
    virtual bool isMultiSheetDwf() = 0;
};



/////////////////////////////////////////////////////////////
/// class AcPublishReactor
/////////////////////////////////////////////////////////////
/// <summary>
/// clients who desire notifications of key Publish events
/// will derive from this class and implement their own reactors
/// </summary>
///
/// <example>
/// <![CDATA[Client side implementation:
/// 
/// The following need to be done to use these API's to get the reactor 
/// notifications from AcPublish module:
/// 
/// 1)  Include the header file: AcPublishReactors.h (in global\inc\arxsdk 
///     directory)
/// 2)  Override the class AcPublishReactors:
/// e.g.
/// 
/// class AcTestReactor : public AcPublishReactor
/// {
/// public:
///     // Brackets the entire plot operation; useful for initialization
///     // and discriminating between various databases
///     void OnAboutToBeginBackgroundPublishing(AcPublishBeforeJobInfo *pInfo);
///     void OnAboutToBeginPublishing(AcPublishBeginJobInfo *pInfo);
///     void OnBeginSheet(AcPublishSheetInfo *pInfo);
///     void OnBeginAggregation(AcPublishAggregationInfo *pInfo);
///     void OnAboutToEndPublishing(AcPublishReactorInfo *pInfo);
///     void OnAboutToMoveFile(AcPublishReactorInfo *pInfo);
///     void OnEndPublish(AcPublishReactorInfo *pInfo);
///     void OnCancelledOrFailedPublishing(AcPublishReactorInfo *pInfo);
/// 
///     // Public d'tor
///     virtual ~AcTestReactor() {};
/// 
///     AcTestReactor() {};
/// }; 
/// 
/// Implement the methods OnAboutToBeginPublishing(). to do your processing. 
/// If you need the final dwf file name, you can get it from the 
/// AcPublishReactorInfo "pInfo" object using the method dwfFileName().
/// 
/// 3)  Use the two global methods AcGlobAddPublishReactor() and 
/// AcGlobRemovePublishReactor() to add and remove your AcTestReactor instance.
/// typedef void (* ACGLOBADDPUBLISHREACTOR) (AcTestReactor*);
/// typedef void (* ACGLOBREMOVEPUBLISHREACTOR) (AcTestReactor*);
/// 
/// 4)  The way you can do the step 3 is as follows:
/// 
/// a)  First check to see if the AcPublish.crx is loaded or not. This you can 
/// do by doing the following:
/// 
/// if(!acrxServiceIsRegistered(/*MSG0*/"AdskPublish")) {
///     acrxLoadModule(/*MSG0*/"AcPublish.crx", false, false);
/// }
/// 
/// b)  Once the AcPublish.crx module is loaded, do the following:
/// 
/// HINSTANCE hInst = ::GetModuleHandle(/*MSG0*/"AcPublish.crx");
/// if ((hInst)) {
///      
///    ACGLOBADDPUBLISHREACTOR pAcGlobAddPublishReactor = 
///  (ACGLOBADDPUBLISHREACTOR)GetProcAddress(hInst,                    
///  /*MSG0*/"AcGlobAddPublishReactor");
/// 
///    pAcGlobRemovePublishReactor = 
///        (ACGLOBREMOVEPUBLISHREACTOR)GetProcAddress(
///        hInst, /*MSG0*/"AcGlobRemovePublishReactor");
/// 
///    if (pAcGlobAddPublishReactor != NULL)
///        pAcGlobAddPublishReactor(&testReactor);
/// }
/// c)  Similarly, when unloading your app, you need to make sure to call
/// "remove reactor".
/// 
/// NOTE: It is the clients (who are hooking themselves to the AcPublish 
/// reactor notifiers) responsibility to make sure AcPublish.crx is loaded 
/// and unloaded and addReactor() and removeReactor() calls are made.]]>
/// </example>

class AcPublishReactor : public AcRxObject
{
public:
    /// <summary>
    /// Brackets the entire plot operation; useful for initialization
    /// and discriminating between various databases
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishBeforeJobInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    virtual void OnAboutToBeginBackgroundPublishing(AcPublishBeforeJobInfo 
        *pInfo);

    /// <summary>
    /// Brackets the entire plot operation; useful for initialization
    /// and discriminating between various databases
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishBeginJobInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    virtual void OnAboutToBeginPublishing(AcPublishBeginJobInfo *pInfo);

    /// <summary>
    /// Brackets the entire plot operation; useful for initialization
    /// and discriminating between various databases
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishBeginSheetInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    virtual void OnBeginPublishingSheet(AcPublishSheetInfo *pInfo);

    /// <summary>
    /// This notification is sent after all of the temporary DWF files
    /// for the job have been plotted and aggregation into a single
    /// multisheet DWF is about to begin.
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishAggregationInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    /// <remarks>
    /// If the job is being published to multiple single page DWF files and
    /// not to multipage DWF, then this notification will be received
    /// once for each page, just before the password is applied.
    /// </remarks>
    ///
    virtual void OnBeginAggregation(AcPublishAggregationInfo *pInfo);


    /// <summary>
    /// This notification is sent when the publish job is about to end.
    /// This might be due to cancellation or an error, or it might be
    /// after successful aggregation of a multipage DWF 
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishReactorInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    /// <remarks>
    /// If the job is being published to multiple single page DWF files and
    /// not to multipage DWF, it is sent after all if the single page DWF
    /// files have been published.
    /// </remarks>
    ///
    virtual void OnAboutToEndPublishing(AcPublishReactorInfo *pInfo);

    /// <summary>
    /// This notification is sent after a multipage DWF has been aggregated
    /// but before the temporary DWF file have been moved to its final
    /// destination.
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishReactorInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    /// <remarks>
    /// If the job is being published to multiple single page DWF files and
    /// not to multipage DWF, then this notification will be received
    /// once for each page, just before the single page file is moved to
    /// its final destination.
    /// </remarks>
    ///
    virtual void OnAboutToMoveFile(AcPublishReactorInfo *pInfo);

    /// <summary>
    /// This notification is sent at the end of the Publish job
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishReactorInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    virtual void OnEndPublish(AcPublishReactorInfo *pInfo);

    /// <summary>
    /// This notification is sent if the job is being cancelled or
    /// aborted due to user input or due to an error
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishReactorInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// </param>
    ///
    virtual void OnCancelledOrFailedPublishing(AcPublishReactorInfo *pInfo);

    /// <summary>
    /// Public d'tor
    /// </summary>
    virtual ~AcPublishReactor() {};

protected:
    /// <summary>
    /// Protected constructor; you must derive to instantiate one
    /// of these.
    /// </summary>
    AcPublishReactor() {};
};

/*
// Base class inlines for OnBegin and OnEnd methods:
// This is the default behavior for methods you chose 
// not to implement in your overriden reactor classes.
*/
inline void 
    AcPublishReactor::OnAboutToBeginBackgroundPublishing(AcPublishBeforeJobInfo
    *pInfo) {};

inline void 
    AcPublishReactor::OnAboutToBeginPublishing(AcPublishBeginJobInfo *pInfo) {};

inline void 
    AcPublishReactor::OnBeginPublishingSheet(AcPublishSheetInfo *pInfo) {};

inline void 
    AcPublishReactor::OnBeginAggregation(AcPublishAggregationInfo *pInfo) {};

inline void 
    AcPublishReactor::OnAboutToEndPublishing(AcPublishReactorInfo *pInfo) {};

inline void 
    AcPublishReactor::OnAboutToMoveFile(AcPublishReactorInfo *pInfo) {};

inline void 
    AcPublishReactor::OnEndPublish(AcPublishReactorInfo *pInfo) {};

inline void 
    AcPublishReactor::OnCancelledOrFailedPublishing(AcPublishReactorInfo 
    *pInfo) {};

// Global functions to add and remove reactors that clients call

/// <summary>
/// global function clients should call to add a reactor
/// </summary>
///
/// <param name="pReactor">
/// a pointer to the reactor the client has derived and instantiated
/// </param>
///
void AcGlobAddPublishReactor(AcPublishReactor *pReactor);

/// <summary>
/// global function clients should call to remove a reactor
/// </summary>
///
/// <param name="pReactor">
/// a pointer to the reactor the client has derived and instantiated and
/// previously added
/// </param>
///
void AcGlobRemovePublishReactor(AcPublishReactor *pReactor);

typedef void (__cdecl * ACGLOBADDPUBLISHREACTOR)(AcPublishReactor * pReactor);
typedef void (__cdecl * ACGLOBREMOVEPUBLISHREACTOR)(AcPublishReactor * pReactor);

#endif//_ACPUBLISHREACTORS_H

