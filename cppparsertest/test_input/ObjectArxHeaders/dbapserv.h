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
//  DESCRIPTION:  
//
//  AcDbHostApplicationServices provides a mechanism for a client of 
//  AcDb.dll to provide runtime information to the database engine.
//  For example when the database (or a dll client) needs to find
//  a specific file, the services can dictate the search that will
//  be followed.
// 
//  A client application (.exe) (there can be only one 'application' 
//  client) in a given session may chose to override the default services
//  with their own custom version implementation.
//

#ifndef AcDbHostApplicationServices_INC
#define AcDbHostApplicationServices_INC

#include "adesk.h"
#include "acdb.h"
#include "acarray.h"
#include "AcString.h"
#include "PAL/api/codepgid.h"
#include "acdlflagbits.h"

// Internet-related status codes
#include "inetstrc.h"
#include "rxdlinkr.h"
#include "PAL/api/product_flavors.h"
#include "PAL/api/aclocale.h"
#pragma pack (push, 8)

class AcadInternalServices;
class AcadInternalServices2;
class AcDbAppSystemVariables;
class AcDbAuditInfo;
class AcDbDatabase;
class AcDbGlobals;
class AcDbObjectId;
class AcDbTransactionManager;
class AcDbUndoController;
class CArchive;
class COleClientItem;
struct flagmat;

class AcDbAbstractClipBoundaryDefinition;
class ClipBoundaryArray;

class AcDbPlotSettingsValidator;
class AcDbLayoutManager;
class AcPwdCache;

enum  AcSDIValues {
    kMDIEnabled = 0,
    kSDIUserEnforced,
    kSDIAppEnforced,
    kSDIUserAndAppEnforced
};


class AcDbHostApplicationProgressMeter {
public:
    AcDbHostApplicationProgressMeter();
    virtual ~AcDbHostApplicationProgressMeter();

    virtual void start(const ACHAR * displayString = NULL);
    virtual void stop();
    
    virtual void meterProgress();

    virtual void setLimit(int max);

};

typedef Acad::ErrorStatus (*SELECTFILEPROC )(/*[out]*/ short *userCancel, 
                                             /*[out]*/ ACHAR *& chosenPath,
                                             void* h, // HWND
                                             const int nFlags,
                                             const ACHAR * prompt,
                                             const ACHAR * dir,
                                             const ACHAR * name,
                                             const ACHAR * type,
                                             int* pnChoice,
                                             bool* pbReadOnly,
                                             const ACHAR * pszWSTags,
                                             AcStringArray* pReserved);

typedef Acad::ErrorStatus (* REMAPPROC) (/*[out]*/ ACHAR *& newName,
                                         const ACHAR * filename,
                                         int context,
                                         void* pReserved);

typedef void (* MAPFILENOTIFYPROC) (const ACHAR * filename,
                                    const ACHAR * newName,
                                    int context,
                                    void* pReserved);

class AcString;

class ADESK_NO_VTABLE AcDbHostApplicationServices : public AcRxObject
{
    friend class AcadInternalServices;
public:    
    ACRX_DECLARE_MEMBERS(AcDbHostApplicationServices);
    ACDBCORE2D_PORT AcDbHostApplicationServices( int createGlobals = 1 );
    ACDBCORE2D_PORT virtual ~AcDbHostApplicationServices();

    enum FindFileHint
    {
        kDefault = 0,
        kFontFile,              // Could be either
        kCompiledShapeFile,     // shx
        kTrueTypeFontFile,      // ttf
        kEmbeddedImageFile,
        kXRefDrawing,
        kPatternFile,
        kARXApplication,
        kFontMapFile,
        kUnderlayFile,
        kDataLinkFile,
        kPhotometricWebFile,
        kMaterialMapFile,
        kCloudOrProjectFile,
    };
    
    enum RemapFileContext
    {
        kDrawingOpen,
        kXrefResolution,
        kRasterResolution,
        kAfterXrefResolution
    };

    // When a file path is required
    //
private:
    virtual Acad::ErrorStatus findFile(ACHAR * pcFullPathOut,
                 int   nBufferLength,
                 const ACHAR * pcFilename,
                 AcDbDatabase * pDb = NULL, // When this search 
                                            // is related to a db
                 AcDbHostApplicationServices::FindFileHint hint = kDefault) = 0;
public:
    ACDBCORE2D_PORT Acad::ErrorStatus findFile(AcString& fileOut,
        const ACHAR * pcFilename,
        AcDbDatabase * pDb = nullptr, // When this search 
                                      // is related to a db
        AcDbHostApplicationServices::FindFileHint hint = AcDbHostApplicationServices::kDefault);


    // These two functions return the full path to the root folder where roamable/local 
    // customizable files were installed. The default implementation is to return the
    // directory where the EXE is located.  These methods can be overridden by DBX
    // applications for their own install structure.  Note that the user may have 
    // reconfigured the location of some of the customizable files using the Options 
    // Dialog, therefore these functions should not be used to locate all customizable 
    // files. To locate customizable files either use the findFile function or the 
    // appropriate system variable for the given file type. 
    //
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getRoamableRootFolder(const ACHAR *& folder);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getLocalRootFolder(const ACHAR *& folder);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getAllUsersRootFolder(const ACHAR*& folder);

    // Returns the full path of the graphics cache files folder. The default path 
    // <localroot>\GraphicsCache.
    //
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getGraphicsCacheFolder(const ACHAR *& folder);

    // Select File APIs
    ACDBCORE2D_PORT virtual Acad::ErrorStatus selectFile(short *userCancel,
                                                   ACHAR *& chosenPath,
                                                   void* h, // HWND
                                                   const int nFlags,
                                                   const ACHAR * prompt,
                                                   const ACHAR * dir,
                                                   const ACHAR * name,
                                                   const ACHAR * type,
                                                   int* pnChoice,
                                                   bool* pbReadOnly,
                                                   const ACHAR * pszWSTags,
                                                   AcStringArray* pReserved) ;
    ACDBCORE2D_PORT virtual Acad::ErrorStatus registerSelectFileCallback(const ACHAR * appName,
                                                   SELECTFILEPROC proc, 
                                                   bool unRegister = false, 
                                                   bool asPrimary  = false);
    ACDBCORE2D_PORT virtual const ACHAR *     primaryClientForSelectFileCallback();
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getRegisteredSelectFileClients(
                                                   AcArray<const ACHAR *>& clients);

    // File remapping
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   mapFile(/*out*/ ACHAR *& newName,
                                                const ACHAR * filename,
                                                int context,
                                                void* pReserved);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   registerMapFileCallback(const ACHAR * appName,
                                                REMAPPROC  proc,
                                                bool unRegister = false, 
                                                bool asPrimary  = false);
    ACDBCORE2D_PORT virtual const ACHAR *       primaryClientForMapFileCallback();
    ACDBCORE2D_PORT virtual bool                setMapFlag(bool setIt);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   getRegisteredFileMapClients(
                                                AcArray<const ACHAR *>& clients);
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   registerMapFileNotification(const ACHAR * appName,
                                                MAPFILENOTIFYPROC,
                                                bool unRegister = false);

    // When a fatal error is encountered this function may be called
    // to notify you.
    //
    ACDBCORE2D_PORT virtual void fatalError(const ACHAR *format, ...);

    // Called when an unhandled exception occurs in an arx command or message.
    //
    ACDBCORE2D_PORT virtual void reportUnhandledArxException(const ACHAR* pExceptionDescription, const ACHAR *pAppName);

    // The equivalent of ads_usrbrk()
    //
    ACDBCORE2D_PORT virtual Adesk::Boolean userBreak(bool updCtrlsWhenEnteringIdle = true) const;

    ACDBCORE2D_PORT virtual void displayChar(ACHAR c) const;
    ACDBCORE2D_PORT virtual void displayString(const ACHAR* string, int count) const;

    // This function will be called to check if the application
    // wants to show text messages. Default implementation is always 
    // returning true;
    ACDBCORE2D_PORT virtual Adesk::Boolean readyToDisplayMessages();

    // This function can be used to used to programmatically change the
    // state of readyToDisplayMessages.  
    ACDBCORE2D_PORT virtual void enableMessageDisplay(Adesk::Boolean);

    // Instructs the system to run fulltime CRC checking on database
    // filing operations.
    ACDBCORE2D_PORT virtual Adesk::Boolean doFullCRCCheck();

    // Indicates where temporary files are to be located.
    // If the function succeeds, the return value is the length, in ACHARs, of the string copied to pcBuffer, not including the terminating null character.
    // If the return value is greater than lBufferSize, the return value is the length, in ACHARs, of the buffer required to hold the path.
    // If the function fails, the return value is zero.
    // Notice: This function is not exactly same as WINAPI GetTempPath. If tempPath length (not including terminating null character) is same as lBufferSize,
    // it returns lBufferSize+1 and doesn't modify pcBuffer.
    ACDBCORE2D_PORT virtual unsigned int getTempPath(Adesk::UInt32 lBufferSize,
                                                ACHAR* pcBuffer);

    ACDBCORE2D_PORT AcString getTempPath();

    // gets the value of a command switch, or an environment variable, or
    // registry entry (the search is in that order).  This is the same
    // behavior as the LISP (getenv) function).  Default implementation
    // is to return NULL.
    //
    ACDBCORE2D_PORT virtual const ACHAR* getEnv(const ACHAR * var);

    // Whenever AcDb.dll needs to instantiate a progress meter, it will
    // call this method.
    // If you want to create your own progress meter, derive from
    // AcDbHostApplicationProgressMeter, and override this method to
    // to return a progress meter of your derived type.
    //
    ACDBCORE2D_PORT virtual AcDbHostApplicationProgressMeter* newProgressMeter();

    // In other cases, AcDb.dll expects to make use of one global
    // instance of a progress meter that is always available.  To
    // set that progress meter to one of your own type, instantiate
    // your meter and pass it to the following function.
    ACDBCORE2D_PORT void setWorkingProgressMeter(AcDbHostApplicationProgressMeter* pNewMeter);

    ACDBCORE2D_PORT virtual AcDbAbstractClipBoundaryDefinition* newClipBoundaryRectangular();
    ACDBCORE2D_PORT virtual AcDbAbstractClipBoundaryDefinition* newClipBoundaryPolygonal();
    ACDBCORE2D_PORT virtual ClipBoundaryArray* newClipBoundaryArray();

    // Should point to a viable database.  The application is free to
    // reset this according to its need.  Some entites will require
    // access to information within a database in order to function
    // properly when they are not yet database-resident.
    //
    AcDbDatabase* workingDatabase() const;
    ACDBCORE2D_PORT void setWorkingDatabase(AcDbDatabase* pDatabase);

    ACDBCORE2D_PORT virtual AcDbUndoController* defaultUndoController();
    ACDBCORE2D_PORT void setDefaultUndoController(AcDbUndoController* pUndoCtrl);

    virtual AcDbTransactionManager* workingTransactionManager();
    void setWorkingTransactionManager(AcDbTransactionManager* pTM);

    ACDBCORE2D_PORT virtual AcDbGlobals * createWorkingGlobals();
    ACDBCORE2D_PORT AcDbGlobals * workingGlobals() const;
    ACDBCORE2D_PORT void setWorkingGlobals(AcDbGlobals* pGlobals);
    
    ACDBCORE2D_PORT AcDbAppSystemVariables * workingAppSysvars() const;
    ACDBCORE2D_PORT void setWorkingAppSysvars(AcDbAppSystemVariables* pSysvars);

    ACDBCORE2D_PORT virtual const ACHAR * program ();
    ACDBCORE2D_PORT virtual const ACHAR * product ();
    ACDBCORE2D_PORT virtual const ACHAR * companyName();
    ACDBCORE2D_PORT virtual const ProdIdCode prodcode();
    ACDBCORE2D_PORT virtual const ACHAR * releaseMajorMinorString();
    ACDBCORE2D_PORT virtual int   releaseMajorVersion();
    ACDBCORE2D_PORT virtual int   releaseMinorVersion();
    ACDBCORE2D_PORT virtual const ACHAR * versionString();
    ACDBCORE2D_PORT virtual const ACHAR * getMachineRegistryProductRootKey ();
    ACDBCORE2D_PORT virtual const ACHAR * getUserRegistryProductRootKey ();
    ACDBCORE2D_PORT virtual const ACHAR* releaseMarketVersion();
    ACDBCORE2D_PORT virtual AcLocale  getProductLocale() ;
    ACDBCORE2D_PORT virtual bool  supportsMultiRedo() const;
    enum ModelerFlavor {kModelerFull=0, kModelerRegionsOnly=1, kModelerObjectsOnly=2};
    ACDBCORE2D_PORT  virtual ModelerFlavor  getModelerFlavor() const;

    ACDBCORE2D_PORT code_page_id getSystemCodePage() const;

    ACDBCORE2D_PORT virtual AcadInternalServices* acadInternalServices();

    ACDBCORE2D_PORT void * acadInternalGetvar (const ACHAR *name);

    // BEGIN: Internet-related services

    // Determine whether a given string ('pszURL') is a valid URL.
    //
    ACDBCORE2D_PORT virtual bool isURL(const ACHAR * pszURL) const;

    /// <summary>
    /// This method is the inverse of the isURL method. It provides a mapping 
    /// from a local file to the corresponding URL that the file was downloaded from.
    /// The URL, if any, is returned via second parameter.
    /// </summary>
    /// <param name="pszLocalFile">input dwg name</param>
    /// <param name="pszURL">ptr to buffer to receive the URL, if any</param>
    /// <param name="nUrlLen">size of the buffer, in ACHARs</param>
    /// <returns>Return true if this is a remote file, false otherwise.</returns>
    /// <remarks>Sets buffer to empty when returning false. Also sets buffer
    ///          to empty if full URL does not fit in the buffer.
    ///          Clients should call the overload taking AcString & arg
    /// </remarks>
    ACDBCORE2D_PORT
    virtual bool isRemoteFile(const ACHAR * pszLocalFile,
                              ACHAR * pszURL, size_t nUrlLen) const;

    // Helper overload for clients using fixed size buffers.
    // Clients hould call the below overload taking AcString & arg instead
    template<size_t N> bool isRemoteFile(const ACHAR * pszLocalFile,
                                         ACHAR (&pszURL)[N]) const
    {
        return isRemoteFile(pszLocalFile, pszURL, N);
    }

    // This overload calls the virtual overload.
    //
    ACDBCORE2D_PORT bool isRemoteFile(const ACHAR * pszLocalFile, AcString& strUrl);


    /// <summary>
    /// Download a resource (file) identified by the URL 'pszURL' to a local
    /// file, and return its name in the buffer pointed to by 'pszLocalFile.' 
    /// </summary>
    /// <param name="pszURL">input URL</param>
    /// <param name="pszLocalFile">buffer which receives local file name </param>
    /// <param name="nLocalFileLen">size in ACHARs of buffer </param>
    /// <param name="bIgnoreCache">forces a new download if true </param>
    /// <returns>Returns Acad::eOk or Acad::eInetOk if successful.
    ///          Returns Acad::eBufferTooSmall if local path doesn't fit in buffer
    /// </returns>
    /// <remarks>Sets buffer to empty when returning an error.
    ///          Clients should call the overload taking AcString & arg
    /// </remarks>
    ///
    ACDBCORE2D_PORT
    virtual Acad::ErrorStatus getRemoteFile(const ACHAR * pszURL, ACHAR * pszLocalFile, 
                                            size_t nLocalFileLen, 
                                            bool bIgnoreCache) const;

    // This overload calls the above virtual overload. Clients should call this one
    // because it does not require a fixed size buffer which may end up being too small
    ACDBCORE2D_PORT
    Acad::ErrorStatus getRemoteFile(const ACHAR * pszURL, AcString& strLocalFile,
                                    bool bIgnoreCache) const;

    // Helper overload, to be removed..
    ACDBCORE2D_PORT
    Acad::ErrorStatus getRemoteFile(const ACHAR * pszURL, AcString& strLocalFile)
    {
        return this->getRemoteFile(pszURL, strLocalFile, false);
    }

    // Helper template for callers passing fixed size arrays.
    // The above overload taking AcString & arg is recommended
    template<size_t N> Acad::ErrorStatus getRemoteFile(const ACHAR * pszURL,
                                                ACHAR (&pszLocalFile)[N]) const
    {
        return this->getRemoteFile(pszURL, pszLocalFile, N, /*bIgnoreCache*/false);
    }
    // Upload a local resource (file) identified by the pathname 'pszLocalFile'
    // to the remote location specified by the URL 'pszURL.'
    //
    ACDBCORE2D_PORT virtual Acad::ErrorStatus putRemoteFile(const ACHAR * pszURL,
        const ACHAR * pszLocalFile) const;

    // Launch the Web Browser dialog that allows the user to navigate to any 
    // site and select a URL. The selected URL is returned in 'pszSelectedURL,' 
    // which must point to a buffer large enough to hold the return value. 
    // 'pszDialogTitle' and 'pszOpenButtonCaption' allow developers to supply 
    // text for the dialog title and the button caption, that is more 
    // meaningful in the context in which the dialog is being invoked. The 
    // parameter 'pszStartURL' is a URL that the Web Browser uses as its start 
    // page. The fifth argument is optional, and identifies the product root 
    // key under which the Web Browser dialog's size and position information 
    // is stored for persistence across sessions.
    // The last parameter determines whether the user can select HTML links
    // in addition to files that are "downloadable."
    //
    ACDBCORE2D_PORT
    virtual Adesk::Boolean launchBrowserDialog(
                 ACHAR *          pszSelectedURL,
                 size_t           selectedUrlLen,
                 const ACHAR *    pszDialogTitle,
                 const ACHAR *    pszOpenButtonCaption,
                 const ACHAR *    pszStartURL, 
                 const ACHAR *    pszRegistryRootKey = 0,
                 Adesk::Boolean bOpenButtonAlwaysEnabled = Adesk::kFalse) const;
    
    template<size_t N> Adesk::Boolean launchBrowserDialog(
                 ACHAR          (&pszSelectedURL)[N],
                 const ACHAR *    pszDialogTitle,
                 const ACHAR *    pszOpenButtonCaption,
                 const ACHAR *    pszStartURL, 
                 const ACHAR *    pszRegistryRootKey = 0,
                 Adesk::Boolean bOpenButtonAlwaysEnabled = Adesk::kFalse) const
    {
        return launchBrowserDialog(pszSelectedURL,N,pszDialogTitle,
                                   pszOpenButtonCaption,pszStartURL,
                                   pszRegistryRootKey,bOpenButtonAlwaysEnabled);
    }

    // OLE Embedded Objects 
    // Draw OLE object using given HDC, objectID and rectangle in screen 
    // coordinate.
    //
    ACDBCORE2D_PORT virtual void drawOleOwnerDrawItem(COleClientItem* pItem,
                                      Adesk::LongPtr hdc, 
                                      Adesk::Int32 left, Adesk::Int32 top, Adesk::Int32 right, Adesk::Int32 bottom);

    // Get COleClientItem from Host application.
    ACDBCORE2D_PORT virtual Acad::ErrorStatus getNewOleClientItem(COleClientItem*& pItem);

    // Called by AcDb when it needs to translate an OLE embedded object.
    ACDBCORE2D_PORT virtual Acad::ErrorStatus serializeOleItem(COleClientItem* pItem,
        CArchive*);

    // This method is renamed from entToWorldTransform() because it is for
    // Internal Use only and will be removed in future.
    // 
    ACDBCORE2D_PORT virtual Adesk::Boolean _entToWorldTransform(double normal[3],
                                                flagmat *tran);

    ACDBCORE2D_PORT  virtual void terminateScript(); // end any running scripts

    // get substitute font for unfound font
    ACDBCORE2D_PORT  virtual Adesk::Boolean getSubstituteFont(ACHAR **pFileName,
                                             const ACHAR *prompt, 
                                             int type, int fontAlt); 
    // Legacy method with non-const prompt arg and final modifier.
    // Derived classes should override the above method, not this one.
    // This method will go away in the future..
    virtual Adesk::Boolean getSubstituteFont(ACHAR **pFileName,
                                             ACHAR *prompt, 
                                             int type, int fontAlt) final
    {
        const ACHAR *pConstPrompt = prompt;
        return this->getSubstituteFont(pFileName, pConstPrompt, type, fontAlt);
    }
    ACDBCORE2D_PORT virtual void alert(const ACHAR * string) const;

    ACDBCORE2D_PORT virtual void auditPrintReport(AcDbAuditInfo * pAuditInfo,
                                             const ACHAR *    line,
                                             int             both) const;

    ACDBCORE2D_PORT  virtual const ACHAR * getAlternateFontName() const;

    ACDBCORE2D_PORT  virtual const ACHAR * getFontMapFileName() const;

    ACDBCORE2D_PORT  virtual bool cacheSymbolIndices() const;

    ACDBCORE2D_PORT virtual AcDbPlotSettingsValidator* plotSettingsValidator() const;
    ACDBCORE2D_PORT virtual AcDbLayoutManager* layoutManager() const;
    ACDBCORE2D_PORT virtual bool loadApp(const ACHAR * appName,
                         AcadApp::LoadReasons why, 
                         bool printit, 
                         bool asCmd);
    // Clients should call the below overload taking an AcString & arg
    ACDBCORE2D_PORT  virtual bool getDefaultPlotCfgInfo(ACHAR * plotDeviceName, size_t nDevNameLen,
                                                 ACHAR * plotStyleName, size_t nStyleNameLen); 
    // helper template method for fixed size C arrays
    template<size_t nDevLen, size_t nStyleLen> bool getDefaultPlotCfgInfo(
                        ACHAR (&devName)[nDevLen], ACHAR (&styleName)[nStyleLen])
    {
        return getDefaultPlotCfgInfo(devName, nDevLen, styleName, nStyleLen);
    }

    // Clients should call this overload
    ACDBCORE2D_PORT void getDefaultPlotCfgInfo(AcString& devName, AcString& styleName);
    
    // BEGIN: DWG Security-related services
    ACDBCORE2D_PORT virtual Acad::ErrorStatus signingComplete(Acad::ErrorStatus es,
                                              const ACHAR * msg,
                                              bool* result);

    enum PasswordOptions {kPasswordOptionDefault = 0, kPasswordOptionUpperCase =1, kPasswordOptionIsExternalReference = 2};
    ACDBCORE2D_PORT virtual bool getPassword(const ACHAR * dwgName,
                             PasswordOptions options,
                             wchar_t *password, 
                             const size_t bufSize);

    /// <summary>
    /// This function is called internally by host applications such as AutoCAD and other ObjectARX applications 
    /// (via the readDwgFile() and acedSyncFileOpen() functions) to display a password-request dialog box. 
    /// </summary>
    /// <param name="dwgName">Name of the drawing file that is requiring a password </param>
    /// <param name="options">Boolean indicating whether dwgName refers to an xref'd drawing </param>
    /// <param name="password">Return password obtained from the user </param>
    /// <returns>Return true if succeed, false otherwise.</returns>
    bool getPassword(const ACHAR * dwgName,
        AcDbHostApplicationServices::PasswordOptions options,
        AcString& password);


    ACDBCORE2D_PORT virtual void usedPasswordFromCacheMsg(const ACHAR *dwgName);
    ACDBCORE2D_PORT virtual void missingCryptoProviderMsg();

    ACDBCORE2D_PORT virtual const ACHAR * getColorBookLocation() const;

    ACDBCORE2D_PORT AcPwdCache * getPasswordCache() const;

    ACDBCORE2D_PORT virtual short getKeyState(int nVirtKey) const;

    enum RequiredVersionFlags {
        kNoOpen       = 0,
        kReadOnly     = 1,
        kWriteAllowed = 2
    };

    ACDBCORE2D_PORT virtual bool requiredVersionNotAvailable(AcDbHostApplicationServices::RequiredVersionFlags flags,
        AcDbDatabase* pDb) const;

    // Called when an attempt is made to read in a corrupt drawing.
    // Return true if your application has handled the error and wishes
    // to continue. If false is returned, fatalError() will be called,
    // and your application must then shut down.
    ACDBCORE2D_PORT virtual bool notifyCorruptDrawingFoundOnOpen(AcDbObjectId id, Acad::ErrorStatus es);

    ACDBCORE2D_PORT virtual AcadInternalServices2* acadInternalServices2();

protected:
    
    // This method is used by the Internet-related methods of all classes that
    // derive from AcDbHostApplicationServices, to map a status code returned by
    // an Internet operation to an Acad::ErrorStatus value.
    //
    Acad::ErrorStatus mapInetStatusToAcadStatus(
        const AcadInet::Status status) const;

    // END: Internet-related services

protected:

    void * mp_sessionVars = nullptr;

    void acadInternalSetvar (const ACHAR *name, void * var);

private:
    // NOTES:
    // As session-specific globals are gathered up during the AcDb.DLL and
    // MDI projects, if the DB requires them, they should be contained here,
    // and appropriate get/set methods created above.  References to those 
    // globals should be replaced by references to methods on this class or 
    // a derived class.  This header will ship with Tahoe Unplugged, but not 
    // Tahoe ARX.  These comments to be deleted before FCS.

    AcDbDatabase* mpWorkingDatabase = nullptr;
    AcDbUndoController* mpDefaultUndoController = nullptr;
    AcDbTransactionManager* mpWorkingTransactionManager = nullptr;
    AcDbGlobals * mpWorkingGlobals = nullptr;
    AcDbAppSystemVariables * mpWorkingAppSysvars = nullptr;

    code_page_id m_eSystemCodePage = code_page_id::CODE_PAGE_UNDEFINED;
                                // Formerly "system_code_page".
                                // Moved from module xstring.cpp.
    bool mbDisplayMessages = true;

    AcPwdCache * mpPasswordCache = nullptr;
};

// Use this method to replace the default services, you should do this 
// early on, in the InitInstance of your application for example.
//
ACDBCORE2D_PORT Acad::ErrorStatus acdbSetHostApplicationServices(AcDbHostApplicationServices * pServices);

// Use this method to access the services
//
ACDBCORE2D_PORT AcDbHostApplicationServices * acdbHostApplicationServices();

// A host application would use this function to send notification to
// clients, e.g. Object Enablers, when it's done reading the initial
// set of objects from a dwg file. This is different from what 
// readDwgFile() would read. readDwgFile() reads the basic set,
// but a host application would, depending on the functionality it's
// implementing, read some more objects, and let everyone know that
// it's done. 
//
ACDBCORE2D_PORT Acad::ErrorStatus acdbSendInitialDwgFileOpenComplete(AcDbDatabase* pDb);

extern AcDbGlobals* getDefaultGlobals();

inline AcDbGlobals *
AcDbHostApplicationServices::workingGlobals() const
{
    return mpWorkingGlobals ? mpWorkingGlobals : getDefaultGlobals();
}

inline code_page_id
AcDbHostApplicationServices::getSystemCodePage() const
{
    return this->m_eSystemCodePage;
}

inline AcDbTransactionManager *
AcDbHostApplicationServices::workingTransactionManager()
{
    return mpWorkingTransactionManager;
}

inline AcDbDatabase *
AcDbHostApplicationServices::workingDatabase() const
{
    return mpWorkingDatabase;
}

inline AcDbAppSystemVariables * 
AcDbHostApplicationServices::workingAppSysvars() const
{
    return mpWorkingAppSysvars;
}

inline void 
AcDbHostApplicationServices::setWorkingAppSysvars(AcDbAppSystemVariables* pSysvars)
{
    mpWorkingAppSysvars = pSysvars;
}

inline AcPwdCache * 
AcDbHostApplicationServices::getPasswordCache() const
{
    return mpPasswordCache;
}

// acdbTriggerAcadOctTreeReclassification
//
// *** For Internal Use Only ***
// 
void acdbTriggerAcadOctTreeReclassification();

// acdbSetBreak3dQueueForRegen
//
// *** For Internal Use Only ***
// 
Acad::ErrorStatus acdbSetBreak3dQueueForRegen(bool);


//Derived classes are expected to override tryPassword and cache a
//file moniker (file name, file handle etc.) during construction so
//they can try the passwords passed to tryPassword. 
// Here are the possible conditions for wszPassword:
// NULL     = check the password cache first then prompt for password
// "value"  = try the supplied value then the cache but don't prompt for another password if it fails
// ""       = skip the cache and the prompt and just fail if encrypted
class ADESK_NO_VTABLE AcDbPasswordedFile
{
protected:
    virtual Acad::ErrorStatus tryPassword(const wchar_t* wzPassword) = 0;
    virtual const ACHAR* getFullPath() = 0;
public:
    Acad::ErrorStatus open(const wchar_t* wszPassword, AcDbHostApplicationServices::PasswordOptions options);
};

#pragma pack (pop)

#endif


