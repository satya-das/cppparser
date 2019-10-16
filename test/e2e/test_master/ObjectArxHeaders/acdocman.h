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
#  define ACDOCMAN_H
#  include "adesk.h"
#  include "accoredefs.h"
#  include "acdb.h"
#  include "acadstrc.h"
#  include "rxobject.h"
#  include "rxboiler.h"
#  include "AcApDocLockMode.h"
#  pragma  pack (push, 8)
class AcTransactionManager;
class AcDbDatabase;
class CDocument;
class AcEdInputPointManager;
class AcApStatusBar;
class AcApPlotReactor;
class AcRxIterator;
class AcApCommandLineEditor;
struct IDispatch;
#  define AC_DOCUMENT_MANAGER_OBJ	ACRX_T("AcApDocManager")
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
  virtual const ACHAR* fileName() const = 0;
  virtual CDocument* cDoc() const = 0;
  virtual AcTransactionManager* transactionManager() const = 0;
  virtual AcDbDatabase* database() const = 0;
  enum SaveFormat
  {
    kUnknown = -1,
    kR12_dxf = 1,
    kR13_dwg = 4,
    kR13_dxf = 5,
    kR14_dwg = 8,
    kR14_dxf = 9,
    k2000_dwg = 12,
    k2000_dxf = 13,
    k2000_Template = 14,
    k2000_Standard = 15,
    k2000_xml = 16,
    k2004_dwg = 24,
    k2004_dxf = 25,
    k2004_Template = 26,
    k2004_Standard = 27,
    k2007_dwg = 36,
    k2007_dxf = 37,
    k2007_Template = 38,
    k2007_Standard = 39,
    k2010_dwg = 48,
    k2010_dxf = 49,
    k2010_Template = 50,
    k2010_Standard = 51,
    k2013_dwg = 60,
    k2013_dxf = 61,
    k2013_Template = 62,
    k2013_Standard = 63,
    k2018_dwg = 64,
    k2018_dxf = 65,
    k2018_Template = 66,
    k2018_Standard = 67,
    kNative = k2018_dwg,
    kNative_Template = k2018_Template
  };
  virtual SaveFormat formatForSave() const = 0;
  ACCORE_PORT static Acad::ErrorStatus getDwgVersionFromSaveFormat(SaveFormat docFormat, AcDb::AcDbDwgVersion& dwgVer, AcDb::MaintenanceReleaseVersion& dwgMaintVer);
  virtual AcAp::DocLockMode lockMode(bool bIncludeMyLocks = false) const = 0;
  virtual AcAp::DocLockMode myLockMode() const = 0;
  virtual bool isQuiescent() const = 0;
  virtual void* contextPtr() const = 0;
  virtual AcEdInputPointManager* inputPointManager() = 0;
  virtual const ACHAR* docTitle() const = 0;
  ACCORE_PORT void setDocTitle(const ACHAR* title);
  virtual IDispatch* GetIDispatch(bool bAddRef) = 0;
  virtual bool isReadOnly() const = 0;
  virtual int GetCountOfLispList() const = 0;
  virtual AcLispAppInfo* GetItemOfLispList(int nIndex) const = 0;
  virtual AcApStatusBar* drawingStatusBar() const = 0;
  virtual bool isCommandInputInactive() const = 0;
  void pushDbmod();
  Acad::ErrorStatus popDbmod();
  Acad::ErrorStatus upgradeDocOpen();
  Acad::ErrorStatus downgradeDocOpen(bool bPromptForSave);
     ///<summary>
    ///Retrieves the one and only view associated with this document.
    ///</summary>
  ACCORE_PORT AcApView* view() const;
  ACCORE_PORT AcApCommandLineEditor* commandLineEditor() const;
  ACCORE_PORT void setHost(IAcApDocumentHost* pHost);
  ACCORE_PORT bool isNamedDrawing() const;
};
Acad::ErrorStatus acedUpgradeDocOpen();
Acad::ErrorStatus acedDowngradeDocOpen(bool bPromptForSave);
class ADESK_NO_VTABLE AcApDocManagerReactor : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcApDocManagerReactor);
  virtual void documentCreateStarted(AcApDocument* pDocCreating);
  virtual void documentCreated(AcApDocument* pDocCreating);
  virtual void documentToBeDestroyed(AcApDocument* pDocToDestroy);
  virtual void documentDestroyed(const ACHAR* fileName);
  virtual void documentCreateCanceled(AcApDocument* pDocCreateCancelled);
  virtual void documentLockModeWillChange(AcApDocument*, AcAp::DocLockMode myCurrentMode, AcAp::DocLockMode myNewMode, AcAp::DocLockMode currentMode, const ACHAR* pGlobalCmdName);
  virtual void documentLockModeChangeVetoed(AcApDocument*, const ACHAR* pGlobalCmdName);
  virtual void documentLockModeChanged(AcApDocument*, AcAp::DocLockMode myPreviousMode, AcAp::DocLockMode myCurrentMode, AcAp::DocLockMode currentMode, const ACHAR* pGlobalCmdName);
  virtual void documentBecameCurrent(AcApDocument*);
  virtual void documentToBeActivated(AcApDocument* pActivatingDoc);
  virtual void documentToBeDeactivated(AcApDocument* pDeActivatedDoc);
  virtual void documentActivationModified(bool bActivation);
  virtual void documentActivated(AcApDocument* pActivatedDoc);
  virtual void documentTitleUpdated(AcApDocument*)
  {
  }
protected:
  AcApDocManagerReactor()
    : mVeto(0)
  {
  }
  Acad::ErrorStatus veto();
private:
  Adesk::Int8 mVeto;
  friend class AcApDocImpManager;
};
class ADESK_NO_VTABLE AcApDocumentIterator : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcApDocumentIterator);
  virtual bool done() const = 0;
  virtual void step() = 0;
  virtual AcApDocument* document() = 0;
};
class IAcApDocManagerHost;
class ADESK_NO_VTABLE AcApDocManager : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcApDocManager);
  virtual AcApDocument* curDocument() const = 0;
  virtual AcApDocument* mdiActiveDocument() const = 0;
  virtual bool isApplicationContext() const = 0;
  virtual AcApDocument* document(const AcDbDatabase*) const = 0;
  virtual Acad::ErrorStatus lockDocument(AcApDocument* pDoc, AcAp::DocLockMode = AcAp::kWrite, const ACHAR* pGlobalCmdName = NULL, const ACHAR* pLocalCmdName = NULL, bool prompt = true) = 0;
  virtual Acad::ErrorStatus unlockDocument(AcApDocument* pDoc) = 0;
  virtual AcApDocumentIterator* newAcApDocumentIterator() = 0;
  virtual void addReactor(AcApDocManagerReactor*) = 0;
  virtual void removeReactor(AcApDocManagerReactor*) = 0;
  virtual Acad::ErrorStatus setDefaultFormatForSave(AcApDocument::SaveFormat format) = 0;
  virtual AcApDocument::SaveFormat defaultFormatForSave() const = 0;
  virtual Acad::ErrorStatus setCurDocument(AcApDocument* pDoc, AcAp::DocLockMode = AcAp::kNone, bool activate = false) = 0;
  virtual Acad::ErrorStatus activateDocument(AcApDocument* pAcTargetDocument, bool bPassScript = false) = 0;
  virtual Acad::ErrorStatus sendStringToExecute(AcApDocument* pAcTargetDocument, const ACHAR* pszExecute, bool bActivate = true, bool bWrapUpInactiveDoc = false, bool bEchoString = true) = 0;
  virtual Acad::ErrorStatus appContextNewDocument(const ACHAR* pszTemplateName) = 0;
  virtual Acad::ErrorStatus appContextOpenDocument(const ACHAR* pszDrawingName) = 0;
  virtual Acad::ErrorStatus appContextRecoverDocument(const ACHAR* pszDrawingName) = 0;
  ACCORE_PORT Acad::ErrorStatus appContextPromptNewDocument();
  ACCORE_PORT Acad::ErrorStatus appContextPromptOpenDocument();
  ACCORE_PORT Acad::ErrorStatus appContextCloseDocument(AcApDocument* pDoc);
  struct DocOpenParams
  {
    union 
    {
      const ACHAR* mpszFileName;
      const wchar_t* mpwszFileName;
    };
    union 
    {
      const ACHAR* mpszViewName;
      const wchar_t* mpwszViewName;
      const double* mpCoords;
    };
    enum InitialViewType : unsigned char
    {
      kUnknown = 0,
      kDefaultView = 1,
      kLayoutName = 2,
      kViewName = 3,
      kLayoutHandle = 4,
      kViewHandle = 5,
      kViewWorldCoords = 6
    };
    InitialViewType mnInitialViewType;
    enum
    {
      kDisallowReadOnly = 0x01,
      kRequireReadOnly = 0x02,
      kFileNameArgIsUnicode = 0x04,
      kViewNameArgIsUnicode = 0x08,
      kUseUIOnErrors = 0x10,
      kOwnerControlled = 0x20,
      kUseUI = 0x40
    };
    int mnFlags;
    const wchar_t* mpwszPassword;
    void* mpOwnerData;
    void* mpUnused;
    int mnUnused;
    const wchar_t* mpwszTitle;
  };
  virtual Acad::ErrorStatus appContextOpenDocument(const DocOpenParams* pParams) = 0;
  virtual Acad::ErrorStatus newDocument() = 0;
  virtual Acad::ErrorStatus openDocument() = 0;
  virtual Acad::ErrorStatus closeDocument(AcApDocument* pAcTargetDocument) = 0;
  virtual int inputPending(AcApDocument* pAcTargetDocument) = 0;
  virtual Acad::ErrorStatus disableDocumentActivation() = 0;
  virtual Acad::ErrorStatus enableDocumentActivation() = 0;
  virtual bool isDocumentActivationEnabled() = 0;
  virtual void executeInApplicationContext(void (*procAddr) (void*), void* pData) const = 0;
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
  ACCORE_PORT Acad::ErrorStatus beginExecuteInCommandContext(void (*procAddr) (void*), void* pData);
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
  ACCORE_PORT Acad::ErrorStatus beginExecuteInApplicationContext(void (*procAddr) (void*), void* pData);
  virtual int documentCount() const = 0;
  virtual void pushAcadResourceHandle() = 0;
  virtual void popResourceHandle() = 0;
  virtual Acad::ErrorStatus sendModelessInterrupt(AcApDocument* pAcTargetDocument) = 0;
  ACCORE_PORT void setHost(IAcApDocManagerHost* pHost);
};
ACCORE_PORT AcApDocManager* acDocManagerPtr();
#  define acDocManager	acDocManagerPtr()
inline AcApDocument* curDoc()
{
  return ::acDocManager->curDocument();
}
#  pragma  pack (pop)
#endif
