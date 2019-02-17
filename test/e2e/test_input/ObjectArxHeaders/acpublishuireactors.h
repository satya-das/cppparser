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
//  AcPublishUIReactors.h - Reactors File
//


#ifndef _ACPUBLISHUIREACTORS_H
#define _ACPUBLISHUIREACTORS_H

#include "AdAChar.h"
#include "AcPublishReactors.h"
#include "rxobject.h"
#include "acarray.h"
#include "AcPlDSDData.h"


#include "AcPublishReactors.h"

/// <summary>
/// This class is the context information supplied by the 
/// OnInitPublishOptionsDialog notifier of AcPublishUIReactor. You do not need
/// to construct this class. This is handed to the 
/// OnInitPublishOptionsDialog method.
/// </summary>
class AcPublishUIReactorInfo
{
public:

    /// <summary>
    /// default constructor
    /// </summary>
    ///
    /// <remarks>
    /// creates an empty AcPublishBeforeJobInfo. Clients do not
    /// construct this object, it is created by the Publishing app
    /// and handed to their reactors
    /// </remarks>
    AcPublishUIReactorInfo() {};

    /// <summary>
    /// destructor
    /// </summary>
    ///
    virtual ~AcPublishUIReactorInfo() {};

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


////////////////////////////////////////////////////////////////////
/// class AcPublishUIReactor
////////////////////////////////////////////////////////////////////
/// <summary>
/// Gives you notification for AcPublish Options UI events
/// </summary>
class AcPublishUIReactor : public AcRxObject
{
public:
    /// <summary>
    /// Event Fired just when the Publish Options dialog is about 
    /// to be displayed. Gives users of this reactor to add their
    /// own controls to the property inspector that is passed to 
    /// them via the IUnknown. This allows clients to add UI for
    /// the configuration of their metadata publication options. The
    /// results of this UI can be communicated in the Unrecognized Data section
    /// of the DSD object.
    /// </summary>
    ///
    /// <param name="pUnk">
    /// This "out" parameter provides access to the COM API for 
    /// CDWFDataPropertyManager in the Publish Options dialog. This derives 
    /// from IPropertyManager and IPropertyManager2. You can QueryInterface
    /// on it to get the PropertytManager which is documented in dynprops.h
    /// </param>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishUIReactorInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// to set or get their private section data
    /// </param>
    ///
    virtual void OnInitPublishOptionsDialog(IUnknown **pUnk, 
                                            AcPublishUIReactorInfo *pInfo);

    /// <summary>
    /// Event Fired just when the Export to DWF/PDF Publish Options dialog 
    /// is about to be displayed. Gives users of this reactor to add their
    /// own controls to the property inspector that is passed to 
    /// them via the IUnknown. This allows clients to add UI for
    /// the configuration of their metadata publication options. The
    /// results of this UI can be communicated in the registry of KEY
    /// @ HKEY_CURRENT_USER\...\Dialogs\AcQuickPublishOpts
    /// </summary>
    ///
    /// <param name="pUnk">
    /// This "out" parameter provides access to the COM API for 
    /// CDWFDataPropertyManager in the Publish Options dialog. This derives 
    /// from IPropertyManager and IPropertyManager2. You can QueryInterface
    /// on it to get the PropertytManager which is documented in dynprops.h
    /// </param>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishUIReactorInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// to set or get their private section data
    /// The parameter is reserved for the future, now it is not used.
    /// </param>
    ///
    virtual void OnInitExportOptionsDialog(IUnknown **pUnk,
                                            AcPublishUIReactorInfo *pInfo);

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Envent Fired just when Read/Save options from/to Registry 
    /// @ HKEY_CURRENT_USER\...\Dialogs\AcQuickPublishOpts
    /// </summary>
    /// <returns>
    /// </returns>
    /// <param name="lpszRegRoot">
    /// This parameter is the root path of KEY @ Software\...\Dialogs\AcQuickPublishOpts
    /// </param>
    /// <param name="bIsReadRegistry">
    /// true, read options data from registry
    /// false, save options data to registy
    /// </param>
    virtual void PersistenceRegistryForExportOptionsDialog(const ACHAR* lpszRegRoot,
                                                        bool bIsReadRegistry = true);

    /// <summary>
    /// Event Fired just when the Auto Publish Settings dialog is about 
    /// to be displayed. Gives users of this reactor to add their
    /// own controls to the property inspector that is passed to 
    /// them via the IUnknown. This allows clients to add UI for
    /// the configuration of their metadata publication options. The
    /// results of this UI can be communicated in the registry of KEY 
    /// @ HKEY_CURRENT_USER\...\Dialogs\AcAutoPublishOpts
    /// </summary>
    ///
    /// <param name="pUnk">
    /// This "out" parameter provides access to the COM API for 
    /// CDWFDataPropertyManager in the Publish Options dialog. This derives 
    /// from IPropertyManager and IPropertyManager2. You can QueryInterface
    /// on it to get the PropertytManager which is documented in dynprops.h
    /// </param>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcPublishUIReactorInfo object is supplied to
    /// the client reactor, providing context information and methods
    /// to set or get their private section data
    /// The parameter is reserved for the future, now it is not used.
    /// </param>
    ///
    virtual void OnInitAutoPublishSettingsDialog(IUnknown **pUnk,
                                                AcPublishUIReactorInfo *pInfo);

    ////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Envent Fired just when Read/Save options from/to Registry 
    /// @ HKEY_CURRENT_USER\...\Dialogs\AcAutoPublishOpts
    /// </summary>
    /// <returns>
    /// </returns>
    /// <param name="lpszRegRoot">
    /// This parameter is the root path of KEY @ Software\...\Dialogs\AcAutoPublishOpts
    /// </param>
    /// <param name="bIsReadRegistry">
    /// true, read options data from registry
    /// false, save options data to registy
    /// </param>
    virtual void PersistenceRegistryForAutoPublishDialog(const ACHAR* lpszRegRoot,
                                                        bool bIsReadRegistry = true);

    /// <summary>
    /// Public d'tor
    /// </summary>
    virtual ~AcPublishUIReactor() {};

protected:
    /// <summary>
    /// Protected constructor; you must derive to instantiate one
    /// of these.
    /// </summary>
    AcPublishUIReactor() {};
};


/*
// Base class inlines for AcPublish UI events
*/
inline void 
AcPublishUIReactor::OnInitPublishOptionsDialog(IUnknown **pUnk,
                                               AcPublishUIReactorInfo *pInfo)
{
}

inline void
AcPublishUIReactor::OnInitExportOptionsDialog(IUnknown **pUnk,
                                                AcPublishUIReactorInfo *pInfo)
{
}

inline void
AcPublishUIReactor::PersistenceRegistryForExportOptionsDialog(const ACHAR* lpszRegRoot,
                                                             bool bIsReadRegistry)
{
}

inline void
AcPublishUIReactor::OnInitAutoPublishSettingsDialog(IUnknown **pUnk,
                                                    AcPublishUIReactorInfo *pInfo)
{
}

inline void
AcPublishUIReactor::PersistenceRegistryForAutoPublishDialog(const ACHAR* lpszRegRoot,
                                                            bool bIsReadRegistry)
{
}


////////////////////////////////////////////////////////////////////
/// class AcPublishUIReactor2
////////////////////////////////////////////////////////////////////
/// <summary>
/// AcPublishUIReactor2 is used to extend the implementation of AcPublishUIReactor
/// while maintaining binary compatibility.
/// AcPublishUIReactor expose PersistenceRegistryForPubishOptionsDialog method to 
/// read/save options for AcPublishDlg
/// </summary>
class AcPublishUIReactor2 : public AcPublishUIReactor
{
public:
    ////////////////////////////////////////////////////////////////////////////////
    /// <summary>
    /// Envent Fired just when Read/Save options from/to Registry 
    /// @ HKEY_CURRENT_USER\...\Dialogs\AcPublishDlg
    /// </summary>
    /// <returns>
    /// </returns>
    /// <param name="lpszRegRoot">
    /// This parameter is the root path of KEY @ Software\...\Dialogs\AcPublishDlg
    /// </param>
    /// <param name="bIsReadRegistry">
    /// true, read options data from registry
    /// false, save options data to registy
    virtual void PersistenceRegistryForPubishOptionsDialog(const ACHAR* lpszRegRoot,
        bool bIsReadRegistry = true) {}

    /// <summary>
    /// Public d'tor
    /// </summary>
    virtual ~AcPublishUIReactor2() {}

protected:
    /// <summary>
    /// Protected constructor; you must derive to instantiate one
    /// of these.
    /// </summary>
    AcPublishUIReactor2() {}
};


// Global functions to add and remove reactors that clients call for 
// AcPublish UI reactor notifications

/// <summary>
/// global function clients should call to add a reactor
/// </summary>
///
/// <param name="pReactor">
/// a pointer to the reactor the client has derived and instantiated
/// </param>
///
void AcGlobAddPublishUIReactor(AcPublishUIReactor *pReactor);

/// <summary>
/// global function clients should call to remove a reactor
/// </summary>
///
/// <param name="pReactor">
/// a pointer to the reactor the client has derived and instantiated and
/// previously added
/// </param>
///
void AcGlobRemovePublishUIReactor(AcPublishUIReactor *pReactor);

typedef void (__cdecl * ACGLOBADDPUBLISHUIREACTOR)(AcPublishUIReactor * pReactor);
typedef void (__cdecl * ACGLOBREMOVEPUBLISHUIREACTOR)(AcPublishUIReactor * pReactor);


#endif//_ACPUBLISHUIREACTORS_H

