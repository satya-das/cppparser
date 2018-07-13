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
//  DESCRIPTION:  Header for Document and Document Manager Classes.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef ACDOCMAN_H
#define ACDOCMAN_H
#include "adesk.h"
#include "accoredefs.h"
#include "acdb.h"
#include "acadstrc.h"   // Acad struct
#include "rxobject.h"   // AcRxObject
#include "rxboiler.h"   // ACRX_DECLARE_MEMBERS

#include "AcApDocLockMode.h"

#pragma pack (push, 8)

class AcTransactionManager;
class AcDbDatabase;
class CDocument;
class AcEdInputPointManager;
class AcApStatusBar;
class AcApPlotReactor;
class AcRxIterator;
class AcApCommandLineEditor;

struct IDispatch;

// Name of Registered Service Object for constructing AutoCAD-specific
// instances.
//
#define AC_DOCUMENT_MANAGER_OBJ ACRX_T("AcApDocManager")

class AcLispAppInfo
{
public:
    static const int MaxPath = 260;
    ACHAR appFileName[MaxPath];
    bool bUnloadable;
};

class AcApView;
class IAcApDocumentHost;
class ADESK_NO_VTABLE AcApDocument : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcApDocument);

    // Returns the full path and filename of the database
    //
    virtual const ACHAR*       fileName() const = 0;

    // Returns the associated MFC CDocument object 
    //
    virtual CDocument* cDoc() const = 0;

    virtual AcTransactionManager* transactionManager() const = 0;

    virtual AcDbDatabase*     database() const = 0;

    // These enum numbers are not random, but correspond to the
    // following formula:
    // enum value = (Release # - 12) * 4 + (0 for dwg, 1 for dxf, 2 for dwt,
    // 3 for dws, 4 for xml).  (and xml is obsolete)
    //
     enum SaveFormat {
        kUnknown = -1,      // Invalid format
        kR12_dxf = 1,       // AutoCAD R12/LT2 DXF (*.dxf)

        kR13_dwg = 4,       // AutoCAD R13/LT95 Drawing (*.dwg)
        kR13_dxf = 5,       // AutoCAD R13/LT95 DXF (*.dxf)

        kR14_dwg = 8,       // AutoCAD R14/LT97 Drawing (*.dwg)
        kR14_dxf = 9,       // AutoCAD R14/LT97 DXF (*.dxf)

        k2000_dwg = 12,      // AutoCAD 2000 Drawing (*.dwg)
        k2000_dxf = 13,      // AutoCAD 2000 DXF (*.dxf)
        k2000_Template = 14, // 2000 Drawing Template File (*.dwt)
        k2000_Standard = 15, // 2000(+) Drawing Standard File (*.dws)
        k2000_xml = 16,      // 2000(+) = DesignXML v1.0 File (*.xml)

        k2004_dwg = 24,      // AutoCAD 2004 Drawing (*.dwg)
        k2004_dxf = 25,      // AutoCAD 2004 DXF (*.dxf)
        k2004_Template = 26, // AutoCAD 2004 Template File (*.dwt)
        k2004_Standard = 27, // 2004 Drawing Standard File (*.dws)

        k2007_dwg = 36,      // AutoCAD 2007 Drawing (*.dwg)
        k2007_dxf = 37,      // AutoCAD 2007 DXF (*.dxf)
        k2007_Template = 38, // AutoCAD 2007 Template File (*.dwt)
        k2007_Standard = 39, // 2007 Drawing Standard File (*.dws)

        k2010_dwg = 48,      // AutoCAD 2010 Drawing (*.dwg)
        k2010_dxf = 49,      // AutoCAD 2010 DXF (*.dxf)
        k2010_Template = 50, // AutoCAD 2010 Template File (*.dwt)
        k2010_Standard = 51, // 2010 Drawing Standard File (*.dws)

        k2013_dwg = 60,      // AutoCAD 2013 Drawing (*.dwg)
        k2013_dxf = 61,      // AutoCAD 2013 DXF (*.dxf)
        k2013_Template = 62, // AutoCAD 2013 Template File (*.dwt)
        k2013_Standard = 63, // 2013 Drawing Standard File (*.dws)

        k2018_dwg = 64,      // AutoCAD 2018 Drawing (*.dwg)
        k2018_dxf = 65,      // AutoCAD 2018 DXF (*.dxf)
        k2018_Template = 66, // AutoCAD 2018 Template File (*.dwt)
        k2018_Standard = 67, // 2018 Drawing Standard File (*.dws)

        kNative = k2018_dwg,  // Current dwg version is 2018
        kNative_Template = k2018_Template  //Current dwt version is 2018
     };

    virtual SaveFormat formatForSave() const = 0;

    ACCORE_PORT static Acad::ErrorStatus getDwgVersionFromSaveFormat(
        SaveFormat docFormat,
        AcDb::AcDbDwgVersion& dwgVer,
        AcDb::MaintenanceReleaseVersion& dwgMaintVer);

    virtual AcAp::DocLockMode lockMode(bool bIncludeMyLocks =
                                           false) const = 0;
    virtual AcAp::DocLockMode myLockMode() const = 0;

    // Is there a command, lisp, script, or ARX command active 
    virtual bool    isQuiescent() const = 0;

    // Return the document's context pointer 
    virtual void * contextPtr() const = 0;

    // Return the document's input point manager
    virtual AcEdInputPointManager* inputPointManager() = 0;

    // Return the documents Window title
    virtual const ACHAR * docTitle() const = 0;
    ACCORE_PORT void setDocTitle(const ACHAR* title);

    // Returns a pointer to the IDispatch object associated with the CDocument object
    virtual IDispatch * GetIDispatch(bool bAddRef) = 0;

    // Return TRUE if the document is read only else false
    virtual bool isReadOnly() const = 0;

    // Access to the list of loaded Lisp applications
    virtual int GetCountOfLispList() const = 0;
    virtual AcLispAppInfo* GetItemOfLispList(int nIndex) const = 0;

    // Return the drawing status bar
    virtual AcApStatusBar* drawingStatusBar() const = 0;

    // return whether command input is currently inactive
    virtual bool isCommandInputInactive() const = 0;
    
    // Push/pop the current value of $DBMOD.  Non-virtual is intentional.
    void              pushDbmod();
    Acad::ErrorStatus popDbmod();

    // Convert the document status from read only to write if possible.
    //
    Acad::ErrorStatus upgradeDocOpen();

    // Convert the document status from writeable to read only.
    // If bPromptForSave is true - and the drawing is modified (based on dbmod)
    // the user is prompted to save the drawing. If bPromptForSave is
    // false and the drawing has been modified, an error is returned.
    //
    Acad::ErrorStatus downgradeDocOpen(bool bPromptForSave);

     ///<summary>
    ///Retrieves the one and only view associated with this document.
    ///</summary>
    ACCORE_PORT AcApView*       view() const;
    ACCORE_PORT AcApCommandLineEditor* commandLineEditor() const;
    ACCORE_PORT void            setHost(IAcApDocumentHost* pHost);

    ACCORE_PORT bool isNamedDrawing() const;
};

// These two functions are to be deprecated
Acad::ErrorStatus acedUpgradeDocOpen();
Acad::ErrorStatus acedDowngradeDocOpen(bool bPromptForSave);

class ADESK_NO_VTABLE AcApDocManagerReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcApDocManagerReactor);

    // Fired when a document is first instantiated no database is available.
    virtual void              documentCreateStarted(AcApDocument* pDocCreating);
    // Fired when a document has been successfully created replaces kLoadDwgMsg.
    virtual void              documentCreated(AcApDocument* pDocCreating);
    // Fired when a document is about to be destroyed replaces kUnloadDwgMsg
    virtual void              documentToBeDestroyed(AcApDocument* pDocToDestroy);
    // Fired when a document is completely destroyed
    virtual void              documentDestroyed(const ACHAR* fileName);
    // Fired when a user action has cancelled a documents creation.
    // Only fired in MDI mode and after a documentCreateStarted
    virtual void              documentCreateCanceled(AcApDocument* pDocCreateCancelled);


    virtual void              documentLockModeWillChange(AcApDocument* ,
                                         AcAp::DocLockMode myCurrentMode,
                                         AcAp::DocLockMode myNewMode,
                                         AcAp::DocLockMode currentMode,
                                         const ACHAR* pGlobalCmdName);
    virtual void              documentLockModeChangeVetoed(AcApDocument* ,
                                         const ACHAR* pGlobalCmdName);
    virtual void              documentLockModeChanged(AcApDocument* ,
                                         AcAp::DocLockMode myPreviousMode,
                                         AcAp::DocLockMode myCurrentMode,
                                         AcAp::DocLockMode currentMode,
                                         const ACHAR* pGlobalCmdName);

    virtual void              documentBecameCurrent(AcApDocument* );
 
    // This reactor is fired PRIOR to a document becoming activated NOTE: The document
    // context will not be set yet see also documentActivated()
    virtual void              documentToBeActivated(AcApDocument* pActivatingDoc );
    // Parallel to documentToBeActivated
    virtual void              documentToBeDeactivated(AcApDocument* pDeActivatedDoc );

    // Notify  of changes caused by disableDocumentActivation() or enableDocumentActivation().
    // bActivation == TRUE when document activation is enabled FALSE when disabled.
    virtual void              documentActivationModified(bool bActivation);

    // This reactor is fired once a document has been activated and its context
    // successfully switched. NOTE: There are situations where document is
    // "activated" outside the normal UI user interaction. See also documentToBeActivated
    virtual void              documentActivated(AcApDocument* pActivatedDoc);

    virtual void              documentTitleUpdated(AcApDocument*) {}

protected:
    AcApDocManagerReactor() : mVeto(0) {}
    Acad::ErrorStatus         veto();

private:
    Adesk::Int8               mVeto;

friend class AcApDocImpManager;
};

class ADESK_NO_VTABLE AcApDocumentIterator : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcApDocumentIterator);

    virtual bool    done() const = 0;
    virtual void              step() = 0;
    virtual AcApDocument*       document() = 0;
};

class IAcApDocManagerHost;

class ADESK_NO_VTABLE AcApDocManager : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcApDocManager);

    // curDocument() returns the document having current context.
    // mdiActiveDocument() returns the MDI active document.
    // curDocument() and mdiActiveDocument() can be different.
    // You can call curDocument() to make a document "current" 
    // without actually activating it. After finish your AcDbDatabase
    // operation under the temporary current document, call
    // setCurDocument(acDocManager->mdiActiveDocument())
    // to reset the MDI active document as the current document.
    virtual AcApDocument*       curDocument() const = 0;
    virtual AcApDocument*       mdiActiveDocument() const = 0;

    virtual bool    isApplicationContext() const = 0;

    virtual AcApDocument*       document(const AcDbDatabase* ) const = 0;

    virtual Acad::ErrorStatus lockDocument(AcApDocument* pDoc,
                                   AcAp::DocLockMode = AcAp::kWrite,
                                   const ACHAR* pGlobalCmdName = NULL,
                                   const ACHAR* pLocalCmdName = NULL,
                                   bool prompt = true) = 0;
    virtual Acad::ErrorStatus unlockDocument(AcApDocument* pDoc) = 0;

    virtual AcApDocumentIterator* newAcApDocumentIterator() = 0;

    virtual void              addReactor(AcApDocManagerReactor* ) = 0;
    virtual void              removeReactor(AcApDocManagerReactor* ) = 0;

    virtual Acad::ErrorStatus setDefaultFormatForSave(
                                AcApDocument::SaveFormat format) = 0;
 
    virtual AcApDocument::SaveFormat defaultFormatForSave() const = 0;
    
    //          Allows an external application running under the Application context
    //          to make a document "current" without actually activating it.
    //          This current state is only valid during the context of the function
    //          calling this API. This enables safe manipulation of a documents
    //          data without the document actually being the top most or
    //          active document. 
    //          The default parameters "mode" and "activate" allow document locking
    //          and activation to occur. These are shortcuts to allow several
    //          steps to be accomplished with a single API and can also
    //          be accomplished with the individual API calls.  
    virtual Acad::ErrorStatus setCurDocument(AcApDocument* pDoc,
                                   AcAp::DocLockMode = AcAp::kNone,
                                   bool activate = false) = 0;
    // Activate target document
    virtual Acad::ErrorStatus activateDocument(AcApDocument* pAcTargetDocument,
                                               bool bPassScript = false) = 0;

    // Send string to target document to execute by default
    // activate document. Allow the string to be executed as soon as
    // possible if "bActivate" is false" and "bWrapUpInactiveDoc" is true.
    // "bEchoString" determines whether the sent string is echoed on the
    // command line.
    virtual Acad::ErrorStatus sendStringToExecute(AcApDocument* pAcTargetDocument,
                                       const ACHAR * pszExecute,
                                       bool bActivate = true,
                                       bool bWrapUpInactiveDoc = false,
                                       bool bEchoString = true) = 0;    

    // These two member functions allow synchronous access to NEW OPEN
    // They may only be called from the application context 
    // See also executeInApplicationContext() These APIs only
    // function in MDI mode.
    virtual Acad::ErrorStatus appContextNewDocument(const ACHAR *pszTemplateName) = 0;
    virtual Acad::ErrorStatus appContextOpenDocument(const ACHAR *pszDrawingName) = 0;
    virtual Acad::ErrorStatus appContextRecoverDocument(const ACHAR *pszDrawingName) = 0;

    //exactly the same as appContextNewDocument (including preconditions) but prompts for template name
    ACCORE_PORT Acad::ErrorStatus appContextPromptNewDocument();
    //exactly the same as appContextOpenDocument (including preconditions) but prompts for drawing name
    ACCORE_PORT Acad::ErrorStatus appContextPromptOpenDocument();
    // Caution:  This function immediately destroys the active document and
    // a lot of related data, so beware what you reference after calling.
    // It can only be invoked from the application context.
    ACCORE_PORT Acad::ErrorStatus appContextCloseDocument(AcApDocument* pDoc);

    struct DocOpenParams {
        union { // drawing file name
            const ACHAR * mpszFileName;
            const wchar_t * mpwszFileName;
        };
        union { // layout or view name, or handle string
            const ACHAR * mpszViewName;
            const wchar_t * mpwszViewName;
            const double * mpCoords;    // or world coords to zoom to
        };
        enum InitialViewType : unsigned char
        {     
            kUnknown = 0,             // not used
            kDefaultView = 1,         // open in last saved view
            kLayoutName = 2,          // specify layout by name
            kViewName = 3,            // specify view by name
            kLayoutHandle = 4,        // specify layout by acdb handle
            kViewHandle = 5,          // specify view by acdb handle
            kViewWorldCoords = 6
        };
        InitialViewType mnInitialViewType;
        enum {  kDisallowReadOnly       = 0x01,
                kRequireReadOnly        = 0x02,
                kFileNameArgIsUnicode   = 0x04,
                kViewNameArgIsUnicode   = 0x08,
                kUseUIOnErrors          = 0x10,
                kOwnerControlled        = 0x20,
                kUseUI                  = 0x40 }; // allow popup/confirmation messages
        int  mnFlags;       // open it as readonly, etc
        const wchar_t * mpwszPassword;
        void  * mpOwnerData;
        void  * mpUnused;
        int  mnUnused;
        const wchar_t * mpwszTitle;
    };

    // Open a drawing and switch to the layout or view specified, if any.
    virtual Acad::ErrorStatus appContextOpenDocument(const DocOpenParams *pParams) = 0;

    // These three member functions provide standard, full user interaction,
    // to the NEW OPEN and CLOSE commands. They are asynchronous so if called
    // from a document context they will suspend the currently executing routine
    // until the orginal document context is re-activated. 
    virtual Acad::ErrorStatus newDocument() = 0;
    virtual Acad::ErrorStatus openDocument() = 0;
    virtual Acad::ErrorStatus closeDocument(AcApDocument* pAcTargetDocument) = 0;

    // Return the state of the documents input buffer in characters pending.
    // A return value of zero indicates the document is not "currently"
    // processing. Used only in conjunction with sendStringToExecute()
    // for automated testing purposes. Return -1 if error
    virtual int    inputPending(AcApDocument* pAcTargetDocument) = 0;

    // APIs to allow control of whether a user can activate another
    // document. May be used by commands that process for long periods of time
    // and wish to allow special cancelation checking without the chance
    // the user might be able to activate another document.
    // Aplications MUST be sure to restore activation when complete.
    // Attempts to disable or enable when already in the requested state
    // will return an error
    virtual Acad::ErrorStatus disableDocumentActivation() = 0;
    virtual Acad::ErrorStatus enableDocumentActivation() = 0;
    virtual bool isDocumentActivationEnabled() = 0;

    // Allows a void function() to be called from the application context
    virtual void executeInApplicationContext(void (*procAddr)(void *), void *pData ) const = 0;
    ///<summary>
    /// Allows anonymous code execution in command context (same as registering a command
    /// and calling sendStringToExecute to invoke it.). The command will be executed in the context
    /// of the mdi active document. The callback function will be called when the system has a chance to
    /// execute a command. This, at minimum, means that the caller of beginExecuteInCommandContext
    /// (i.e. your code) must return to its caller. All outstanding commands will be cancelled before
    /// the callback function is invoked.
    ///</summary>
    ///<param name="procAddr"> Required. The name of the callback function to be called. </param>
    ///<param name="pData" > Optional. Pointer to the data that will be passed to the callback.
    /// It is the caller's responsibility to make sure that the pointer remains valid until the 
    /// callback is called. </param>
    ///<returns> 
    /// Acad::eOk : if the request is successfully queued.
    /// Acad::eInvalidContext: if the call is made while AcApDocManager::isApplicationContext()==false.
    /// Acad::eInvalidInput: if procAddr is NULL.
    /// Acad::eNoDocument: if the call is made while AcApDocManager::mdiActiveDocument() == NULL.
    ///</returns>
    ACCORE_PORT Acad::ErrorStatus beginExecuteInCommandContext(void (*procAddr)(void *), void *pData);

    ///<summary>
    /// Allows anonymous code execution in application context (same as registering a message
    /// and posting that message). The callback function will be called when the system has a chance to
    /// execute a message.
    /// Unlike executeInApplicationContext, this function is always asynchronous (i.e. the callback won't
    /// execute until after caller has returned to the main message loop.)
    ///</summary>
    ///<param name="procAddr"> Required. The name of the callback function to be called. </param>
    ///<param name="pData" > Optional. Pointer to the data that will be passed to the callback.
    /// It is the caller's responsibility to make sure that the pointer remains valid until the 
    /// callback is called. </param>
    ///<returns> 
    /// Acad::eOk : if the request is successfully queued.
    /// Acad::eInvalidInput: if procAddr is NULL.
    ///</returns>
    ACCORE_PORT Acad::ErrorStatus beginExecuteInApplicationContext(void(*procAddr)(void *), void *pData);

    // Return the number of currently open documents
    virtual int documentCount() const = 0;

    // Handle setting/saving/restoring of resouce file handles
    // pushAcadResourceHandle pushes the current resource
    // handle onto the current document's resource handle stack and makes
    // AutoCAD's resource file current.  popResourceHandle makes the
    // resource file handle on top of the stack current and removes it from
    // the stack.


    virtual void pushAcadResourceHandle() = 0;
    virtual void popResourceHandle() = 0;
    // Causes a document waiting for input to return to the caller 
    virtual Acad::ErrorStatus sendModelessInterrupt(AcApDocument* pAcTargetDocument) = 0;

    ACCORE_PORT void setHost(IAcApDocManagerHost* pHost);
};


ACCORE_PORT AcApDocManager* acDocManagerPtr();
#define acDocManager acDocManagerPtr()

inline AcApDocument* curDoc() { return ::acDocManager->curDocument(); }

#pragma pack (pop)
#endif // ACDOCMAND_H

