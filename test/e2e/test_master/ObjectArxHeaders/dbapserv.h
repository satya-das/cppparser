//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AcDbHostApplicationServices_INC
#  define AcDbHostApplicationServices_INC
#  include "adesk.h"
#  include "acdb.h"
#  include "acarray.h"
#  include "AcString.h"
#  include "PAL/api/codepgid.h"
#  include "acdlflagbits.h"
#  include "inetstrc.h"
#  include "rxdlinkr.h"
#  include "PAL/api/product_flavors.h"
#  include "PAL/api/aclocale.h"
#  pragma  pack (push, 8)
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
enum AcSDIValues
{
  kMDIEnabled = 0,
  kSDIUserEnforced,
  kSDIAppEnforced,
  kSDIUserAndAppEnforced
};
class AcDbHostApplicationProgressMeter
{
public:
  AcDbHostApplicationProgressMeter();
  virtual ~AcDbHostApplicationProgressMeter();
  virtual void start(const ACHAR* displayString = NULL);
  virtual void stop();
  virtual void meterProgress();
  virtual void setLimit(int max);
};
typedef Acad::ErrorStatus (*SELECTFILEPROC) (short* userCancel, ACHAR*& chosenPath, void* h, const int nFlags, const ACHAR* prompt, const ACHAR* dir, const ACHAR* name, const ACHAR* type, int* pnChoice, bool* pbReadOnly, const ACHAR* pszWSTags, AcStringArray* pReserved);
typedef Acad::ErrorStatus (*REMAPPROC) (ACHAR*& newName, const ACHAR* filename, int context, void* pReserved);
typedef void (*MAPFILENOTIFYPROC) (const ACHAR* filename, const ACHAR* newName, int context, void* pReserved);
class AcString;
class ADESK_NO_VTABLE AcDbHostApplicationServices : public AcRxObject
{
  friend class AcadInternalServices;
public:
  ACRX_DECLARE_MEMBERS(AcDbHostApplicationServices);
  ACDBCORE2D_PORT AcDbHostApplicationServices(int createGlobals = 1);
  ACDBCORE2D_PORT virtual ~AcDbHostApplicationServices();
  enum FindFileHint
  {
    kDefault = 0,
    kFontFile,
    kCompiledShapeFile,
    kTrueTypeFontFile,
    kEmbeddedImageFile,
    kXRefDrawing,
    kPatternFile,
    kARXApplication,
    kFontMapFile,
    kUnderlayFile,
    kDataLinkFile,
    kPhotometricWebFile,
    kMaterialMapFile,
    kCloudOrProjectFile
  };
  enum RemapFileContext
  {
    kDrawingOpen,
    kXrefResolution,
    kRasterResolution,
    kAfterXrefResolution
  };
private:
  virtual Acad::ErrorStatus findFile(ACHAR* pcFullPathOut, int nBufferLength, const ACHAR* pcFilename, AcDbDatabase* pDb = NULL, AcDbHostApplicationServices::FindFileHint hint = kDefault) = 0;
public:
  ACDBCORE2D_PORT Acad::ErrorStatus findFile(AcString& fileOut, const ACHAR* pcFilename, AcDbDatabase* pDb = nullptr, AcDbHostApplicationServices::FindFileHint hint = AcDbHostApplicationServices::kDefault);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getRoamableRootFolder(const ACHAR*& folder);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getLocalRootFolder(const ACHAR*& folder);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getAllUsersRootFolder(const ACHAR*& folder);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getGraphicsCacheFolder(const ACHAR*& folder);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus selectFile(short* userCancel, ACHAR*& chosenPath, void* h, const int nFlags, const ACHAR* prompt, const ACHAR* dir, const ACHAR* name, const ACHAR* type, int* pnChoice, bool* pbReadOnly, const ACHAR* pszWSTags, AcStringArray* pReserved);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus registerSelectFileCallback(const ACHAR* appName, SELECTFILEPROC proc, bool unRegister = false, bool asPrimary = false);
  ACDBCORE2D_PORT virtual const ACHAR* primaryClientForSelectFileCallback();
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getRegisteredSelectFileClients(AcArray<const ACHAR *>& clients);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus mapFile(ACHAR*& newName, const ACHAR* filename, int context, void* pReserved);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus registerMapFileCallback(const ACHAR* appName, REMAPPROC proc, bool unRegister = false, bool asPrimary = false);
  ACDBCORE2D_PORT virtual const ACHAR* primaryClientForMapFileCallback();
  ACDBCORE2D_PORT virtual bool setMapFlag(bool setIt);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getRegisteredFileMapClients(AcArray<const ACHAR *>& clients);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus registerMapFileNotification(const ACHAR* appName, MAPFILENOTIFYPROC, bool unRegister = false);
  ACDBCORE2D_PORT virtual void fatalError(const ACHAR* format, ...);
  ACDBCORE2D_PORT virtual void reportUnhandledArxException(const ACHAR* pExceptionDescription, const ACHAR* pAppName);
  ACDBCORE2D_PORT virtual Adesk::Boolean userBreak(bool updCtrlsWhenEnteringIdle = true) const;
  ACDBCORE2D_PORT virtual void displayChar(ACHAR c) const;
  ACDBCORE2D_PORT virtual void displayString(const ACHAR* string, int count) const;
  ACDBCORE2D_PORT virtual Adesk::Boolean readyToDisplayMessages();
  ACDBCORE2D_PORT virtual void enableMessageDisplay(Adesk::Boolean);
  ACDBCORE2D_PORT virtual Adesk::Boolean doFullCRCCheck();
  ACDBCORE2D_PORT virtual unsigned int getTempPath(Adesk::UInt32 lBufferSize, ACHAR* pcBuffer);
  ACDBCORE2D_PORT AcString getTempPath();
  ACDBCORE2D_PORT virtual const ACHAR* getEnv(const ACHAR* var);
  ACDBCORE2D_PORT virtual AcDbHostApplicationProgressMeter* newProgressMeter();
  ACDBCORE2D_PORT void setWorkingProgressMeter(AcDbHostApplicationProgressMeter* pNewMeter);
  ACDBCORE2D_PORT virtual AcDbAbstractClipBoundaryDefinition* newClipBoundaryRectangular();
  ACDBCORE2D_PORT virtual AcDbAbstractClipBoundaryDefinition* newClipBoundaryPolygonal();
  ACDBCORE2D_PORT virtual ClipBoundaryArray* newClipBoundaryArray();
  AcDbDatabase* workingDatabase() const;
  ACDBCORE2D_PORT void setWorkingDatabase(AcDbDatabase* pDatabase);
  ACDBCORE2D_PORT virtual AcDbUndoController* defaultUndoController();
  ACDBCORE2D_PORT void setDefaultUndoController(AcDbUndoController* pUndoCtrl);
  virtual AcDbTransactionManager* workingTransactionManager();
  void setWorkingTransactionManager(AcDbTransactionManager* pTM);
  ACDBCORE2D_PORT virtual AcDbGlobals* createWorkingGlobals();
  ACDBCORE2D_PORT AcDbGlobals* workingGlobals() const;
  ACDBCORE2D_PORT void setWorkingGlobals(AcDbGlobals* pGlobals);
  ACDBCORE2D_PORT AcDbAppSystemVariables* workingAppSysvars() const;
  ACDBCORE2D_PORT void setWorkingAppSysvars(AcDbAppSystemVariables* pSysvars);
  ACDBCORE2D_PORT virtual const ACHAR* program();
  ACDBCORE2D_PORT virtual const ACHAR* product();
  ACDBCORE2D_PORT virtual const ACHAR* companyName();
  ACDBCORE2D_PORT virtual const ProdIdCode prodcode();
  ACDBCORE2D_PORT virtual const ACHAR* releaseMajorMinorString();
  ACDBCORE2D_PORT virtual int releaseMajorVersion();
  ACDBCORE2D_PORT virtual int releaseMinorVersion();
  ACDBCORE2D_PORT virtual const ACHAR* versionString();
  ACDBCORE2D_PORT virtual const ACHAR* getMachineRegistryProductRootKey();
  ACDBCORE2D_PORT virtual const ACHAR* getUserRegistryProductRootKey();
  ACDBCORE2D_PORT virtual const ACHAR* releaseMarketVersion();
  ACDBCORE2D_PORT virtual AcLocale getProductLocale();
  ACDBCORE2D_PORT virtual bool supportsMultiRedo() const;
  enum ModelerFlavor
  {
    kModelerFull = 0,
    kModelerRegionsOnly = 1,
    kModelerObjectsOnly = 2
  };
  ACDBCORE2D_PORT virtual ModelerFlavor getModelerFlavor() const;
  ACDBCORE2D_PORT code_page_id getSystemCodePage() const;
  ACDBCORE2D_PORT virtual AcadInternalServices* acadInternalServices();
  ACDBCORE2D_PORT void* acadInternalGetvar(const ACHAR* name);
  ACDBCORE2D_PORT virtual bool isURL(const ACHAR* pszURL) const;
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
  ACDBCORE2D_PORT virtual bool isRemoteFile(const ACHAR* pszLocalFile, ACHAR* pszURL, size_t nUrlLen) const;
  template <size_t N>
  bool isRemoteFile(const ACHAR* pszLocalFile, ACHAR (&pszURL)[N]) const
  {
    return isRemoteFile(pszLocalFile, pszURL, N);
  }
  ACDBCORE2D_PORT bool isRemoteFile(const ACHAR* pszLocalFile, AcString& strUrl);
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
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getRemoteFile(const ACHAR* pszURL, ACHAR* pszLocalFile, size_t nLocalFileLen, bool bIgnoreCache) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getRemoteFile(const ACHAR* pszURL, AcString& strLocalFile, bool bIgnoreCache) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getRemoteFile(const ACHAR* pszURL, AcString& strLocalFile)
  {
    return this->getRemoteFile(pszURL, strLocalFile, false);
  }
  template <size_t N>
  Acad::ErrorStatus getRemoteFile(const ACHAR* pszURL, ACHAR (&pszLocalFile)[N]) const
  {
    return this->getRemoteFile(pszURL, pszLocalFile, N, false);
  }
  ACDBCORE2D_PORT virtual Acad::ErrorStatus putRemoteFile(const ACHAR* pszURL, const ACHAR* pszLocalFile) const;
  ACDBCORE2D_PORT virtual Adesk::Boolean launchBrowserDialog(ACHAR* pszSelectedURL, size_t selectedUrlLen, const ACHAR* pszDialogTitle, const ACHAR* pszOpenButtonCaption, const ACHAR* pszStartURL, const ACHAR* pszRegistryRootKey = 0, Adesk::Boolean bOpenButtonAlwaysEnabled = Adesk::kFalse) const;
  template <size_t N>
  Adesk::Boolean launchBrowserDialog(ACHAR (&pszSelectedURL)[N], const ACHAR* pszDialogTitle, const ACHAR* pszOpenButtonCaption, const ACHAR* pszStartURL, const ACHAR* pszRegistryRootKey = 0, Adesk::Boolean bOpenButtonAlwaysEnabled = Adesk::kFalse) const
  {
    return launchBrowserDialog(pszSelectedURL, N, pszDialogTitle, pszOpenButtonCaption, pszStartURL, pszRegistryRootKey, bOpenButtonAlwaysEnabled);
  }
  ACDBCORE2D_PORT virtual void drawOleOwnerDrawItem(COleClientItem* pItem, Adesk::LongPtr hdc, Adesk::Int32 left, Adesk::Int32 top, Adesk::Int32 right, Adesk::Int32 bottom);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus getNewOleClientItem(COleClientItem*& pItem);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus serializeOleItem(COleClientItem* pItem, CArchive*);
  ACDBCORE2D_PORT virtual Adesk::Boolean _entToWorldTransform(double normal[3], flagmat* tran);
  ACDBCORE2D_PORT virtual void terminateScript();
  ACDBCORE2D_PORT virtual Adesk::Boolean getSubstituteFont(ACHAR** pFileName, const ACHAR* prompt, int type, int fontAlt);
  virtual Adesk::Boolean getSubstituteFont(ACHAR** pFileName, ACHAR* prompt, int type, int fontAlt) final
  {
    const ACHAR* pConstPrompt = prompt;
    return this->getSubstituteFont(pFileName, pConstPrompt, type, fontAlt);
  }
  ACDBCORE2D_PORT virtual void alert(const ACHAR* string) const;
  ACDBCORE2D_PORT virtual void auditPrintReport(AcDbAuditInfo* pAuditInfo, const ACHAR* line, int both) const;
  ACDBCORE2D_PORT virtual const ACHAR* getAlternateFontName() const;
  ACDBCORE2D_PORT virtual const ACHAR* getFontMapFileName() const;
  ACDBCORE2D_PORT virtual bool cacheSymbolIndices() const;
  ACDBCORE2D_PORT virtual AcDbPlotSettingsValidator* plotSettingsValidator() const;
  ACDBCORE2D_PORT virtual AcDbLayoutManager* layoutManager() const;
  ACDBCORE2D_PORT virtual bool loadApp(const ACHAR* appName, AcadApp::LoadReasons why, bool printit, bool asCmd);
  ACDBCORE2D_PORT virtual bool getDefaultPlotCfgInfo(ACHAR* plotDeviceName, size_t nDevNameLen, ACHAR* plotStyleName, size_t nStyleNameLen);
  template <size_t nDevLen, size_t nStyleLen>
  bool getDefaultPlotCfgInfo(ACHAR (&devName)[nDevLen], ACHAR (&styleName)[nStyleLen])
  {
    return getDefaultPlotCfgInfo(devName, nDevLen, styleName, nStyleLen);
  }
  ACDBCORE2D_PORT void getDefaultPlotCfgInfo(AcString& devName, AcString& styleName);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus signingComplete(Acad::ErrorStatus es, const ACHAR* msg, bool* result);
  enum PasswordOptions
  {
    kPasswordOptionDefault = 0,
    kPasswordOptionUpperCase = 1,
    kPasswordOptionIsExternalReference = 2
  };
  ACDBCORE2D_PORT virtual bool getPassword(const ACHAR* dwgName, PasswordOptions options, wchar_t* password, const size_t bufSize);
    /// <summary>
    /// This function is called internally by host applications such as AutoCAD and other ObjectARX applications 
    /// (via the readDwgFile() and acedSyncFileOpen() functions) to display a password-request dialog box. 
    /// </summary>
    /// <param name="dwgName">Name of the drawing file that is requiring a password </param>
    /// <param name="options">Boolean indicating whether dwgName refers to an xref'd drawing </param>
    /// <param name="password">Return password obtained from the user </param>
    /// <returns>Return true if succeed, false otherwise.</returns>
  bool getPassword(const ACHAR* dwgName, AcDbHostApplicationServices::PasswordOptions options, AcString& password);
  ACDBCORE2D_PORT virtual void usedPasswordFromCacheMsg(const ACHAR* dwgName);
  ACDBCORE2D_PORT virtual void missingCryptoProviderMsg();
  ACDBCORE2D_PORT virtual const ACHAR* getColorBookLocation() const;
  ACDBCORE2D_PORT AcPwdCache* getPasswordCache() const;
  ACDBCORE2D_PORT virtual short getKeyState(int nVirtKey) const;
  enum RequiredVersionFlags
  {
    kNoOpen = 0,
    kReadOnly = 1,
    kWriteAllowed = 2
  };
  ACDBCORE2D_PORT virtual bool requiredVersionNotAvailable(AcDbHostApplicationServices::RequiredVersionFlags flags, AcDbDatabase* pDb) const;
  ACDBCORE2D_PORT virtual bool notifyCorruptDrawingFoundOnOpen(AcDbObjectId id, Acad::ErrorStatus es);
  ACDBCORE2D_PORT virtual AcadInternalServices2* acadInternalServices2();
protected:
  Acad::ErrorStatus mapInetStatusToAcadStatus(const AcadInet::Status status) const;
  void* mp_sessionVars = nullptr;
  void acadInternalSetvar(const ACHAR* name, void* var);
private:
  AcDbDatabase* mpWorkingDatabase = nullptr;
  AcDbUndoController* mpDefaultUndoController = nullptr;
  AcDbTransactionManager* mpWorkingTransactionManager = nullptr;
  AcDbGlobals* mpWorkingGlobals = nullptr;
  AcDbAppSystemVariables* mpWorkingAppSysvars = nullptr;
  code_page_id m_eSystemCodePage = code_page_id::CODE_PAGE_UNDEFINED;
  bool mbDisplayMessages = true;
  AcPwdCache* mpPasswordCache = nullptr;
};
ACDBCORE2D_PORT Acad::ErrorStatus acdbSetHostApplicationServices(AcDbHostApplicationServices* pServices);
ACDBCORE2D_PORT AcDbHostApplicationServices* acdbHostApplicationServices();
ACDBCORE2D_PORT Acad::ErrorStatus acdbSendInitialDwgFileOpenComplete(AcDbDatabase* pDb);
extern AcDbGlobals* getDefaultGlobals();
inline AcDbGlobals* AcDbHostApplicationServices::workingGlobals() const
{
  return mpWorkingGlobals ? mpWorkingGlobals : getDefaultGlobals();
}
inline code_page_id AcDbHostApplicationServices::getSystemCodePage() const
{
  return this->m_eSystemCodePage;
}
inline AcDbTransactionManager* AcDbHostApplicationServices::workingTransactionManager()
{
  return mpWorkingTransactionManager;
}
inline AcDbDatabase* AcDbHostApplicationServices::workingDatabase() const
{
  return mpWorkingDatabase;
}
inline AcDbAppSystemVariables* AcDbHostApplicationServices::workingAppSysvars() const
{
  return mpWorkingAppSysvars;
}
inline void AcDbHostApplicationServices::setWorkingAppSysvars(AcDbAppSystemVariables* pSysvars)
{
  mpWorkingAppSysvars = pSysvars;
}
inline AcPwdCache* AcDbHostApplicationServices::getPasswordCache() const
{
  return mpPasswordCache;
}
void acdbTriggerAcadOctTreeReclassification();
Acad::ErrorStatus acdbSetBreak3dQueueForRegen(bool);
class ADESK_NO_VTABLE AcDbPasswordedFile
{
protected:
  virtual Acad::ErrorStatus tryPassword(const wchar_t* wzPassword) = 0;
  virtual const ACHAR* getFullPath() = 0;
public:
  Acad::ErrorStatus open(const wchar_t* wszPassword, AcDbHostApplicationServices::PasswordOptions options);
};
#  pragma  pack (pop)
#endif
