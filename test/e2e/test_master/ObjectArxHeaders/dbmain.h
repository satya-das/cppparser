//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBMAIN_H
#  define AD_DBMAIN_H
#  include <stddef.h>
#  include "adesk.h"
#  include "gepnt2d.h"
#  include "gepnt3d.h"
#  include "AcHeapOpers.h"
#  include "rxobject.h"
#  include "rxdlinkr.h"
#  include "rxiter.h"
#  include "rxditer.h"
#  include "rxsrvice.h"
#  include "dbboiler.h"
#  include "dbptrar.h"
#  include "dbcolor.h"
#  include "dbidar.h"
#  include "drawable.h"
#  include "dbsecurity.h"
#  include "AcString.h"
class AcCmEntityColor;
class AcCmColor;
class AcDbBlockBegin;
class AcDbBlockEnd;
class AcDbDatabase;
class AcDbDatabaseIterator;
class AcDbDatabaseReactor;
class AcDbEntity;
class AcDbEntityReactor;
class AcDbImpDatabase;
class AcDbImpObject;
class AcDbObject;
class AcDbObjectReactor;
class AcDbSpaceIterator;
class AcDbSystemInternals;
class AcDbXObject;
class AcDbBlockReference;
class AcDbSymbolTable;
class AcDbBlockTable;
class AcDbBlockTableRecord;
class AcDbLayerTable;
class AcDbTextStyleTable;
class AcDbLinetypeTable;
class AcDbAbstractViewTable;
class AcDbViewTable;
class AcDbUCSTable;
class AcDbViewportTable;
class AcDbRegAppTable;
class AcDbDimStyleTable;
class AcDbDimStyleTableRecord;
class AcDbIdMapping;
class AcDbDictionary;
class AcDbDictionaryWithDefault;
class AcDbMline;
class AcDbMlineStyle;
class AcDbCurve;
class AcDbEllipse;
class AcDbSpline;
class AcDbRegion;
class AcDb3dSolid;
class AcDbBody;
class AcDbDate;
class AcDbExtents;
class AcDbAuditInfo;
class AcDbUndoController;
class AcDbTransactionManager;
class AcDbSpatialFilter;
class AcDbLayerFilter;
class AcGeMatrix2d;
class AcGeVector3d;
class AcGsNode;
class AcGsModel;
class AcGiContext;
class AcDbObjectIdGraph;
class AcDbLayerStateManager;
class AcDwgFileHandle;
class AcDbTableStyle;
class AcFdFieldValue;
class AcDbField;
class AcDbSectionManager;
class AcDbDataLinkManager;
class AcGiMapper;
class AcDbAnnotationScale;
class IAcReadStream;
class IAcWriteStream;
Acad::ErrorStatus acutNewString(const ACHAR* pInput, ACHAR*& pOutput);
namespace Atil
{
  class Image;
}
#  include "acdb.h"
#  include "dbhandle.h"
#  include "dbfiler.h"
#  include "ads_db.h"
#  include "gept3dar.h"
#  include "dbintar.h"
#  include "dbsubeid.h"
#  include "dbaudita.h"
#  include "acgidefs.h"
#  include "AcArray.h"
#  pragma  pack(push, 8)
class AcLocale;
struct _GUID;
typedef struct _GUID CLSID;
class AcDbGripData;
typedef AcArray<AcDbGripData*, AcArrayMemCopyReallocator<AcDbGripData*> > AcDbGripDataPtrArray;
typedef AcArray<AcDbFullSubentPath, AcArrayObjectCopyReallocator<AcDbFullSubentPath> > AcDbFullSubentPathArray;
extern const AcDbFullSubentPath kNullSubent;
AcDb::DwgDataType acdbGroupCodeToType(AcDb::DxfCode pCode);
void acdbFreeResBufContents(resbuf* pField);
ACDBCORE2D_PORT AcDbObjectId acdbPersistentReactorObjectId(const void* pSomething);
inline bool acdbIsPersistentReactor(const void* pSomething)
{
  return !::acdbPersistentReactorObjectId(pSomething).isNull();
}
ACDB_PORT bool acdbDisplayPreviewFromDwg(const ACHAR* pszDwgfilename, void* pPreviewWnd, const Adesk::UInt32* pBgColor = nullptr);
bool acdbIsCustomObject(const AcDbObjectId& id);
/// <summary>
/// This function opens an AcDbObject for read, write or notify access
/// </summary>
/// <param name="pObj"> A reference to a pointer to the Object. Set to null on errors</param>
/// <param name="id"> The id of the object to open.</param>
/// <param name="mode"> Whether to open the object for read, write or notify access</param>
/// <param name="openErased"> If true, then open the object even when it is erased</param>
/// <param name="pClass"> The expected type of the object. If null, then any object type is
///              accepted. Else eWrongType is returned if the object is not derived from
///              the passed in AcRxClass type.</param>
/// <returns> Returns Acad::eOk if the object is opened successfully, otherwise an error code.</returns>
/// <remarks> If your pObj pointer variable is not of type AcDbObject *, then do NOT cast
///           it to type (AcDbObject * &) when calling this function. Just pass your
///           variable as is and the template override defined below will be invoked
/// </remarks>
///
ACDBCORE2D_PORT Acad::ErrorStatus acdbOpenObject(AcDbObject*& pObj, AcDbObjectId id, AcDb::OpenMode mode, bool openErased, const AcRxClass* pClass);
/// <summary>
/// This function opens an AcDbObject for read, write or notify access
/// </summary>
/// <param name="pObj"> A reference to a pointer to the Object. Set to null on errors</param>
/// <param name="id"> The id of the object to open.</param>
/// <param name="pfDesc"> Pointer to an AcRxClass's static desc method</param>
/// <param name="mode"> Whether to open the object for read, write or notify access</param>
/// <param name="openErased"> If true, then open the object even when it is erased</param>
/// <returns> Returns Acad::eOk if the object is opened successfully, otherwise an error code.</returns>
/// <remarks> This is the worker function for the acdbOpenObject template func.
///           Returns Acad::eNullPtr error if pfDesc is null.
/// </remarks>
///
ACDBCORE2D_PORT Acad::ErrorStatus acdbOpenObject(AcDbObject*& pObj, AcDbObjectId id, AcRxClass* (*pfDesc) (), AcDb::OpenMode mode, bool openErased);
inline Acad::ErrorStatus acdbOpenAcDbObject(AcDbObject*& pObj, AcDbObjectId id, AcDb::OpenMode mode, bool openErasedObject = false)
{
  return ::acdbOpenObject(pObj, id, mode, openErasedObject, nullptr);
}
/// <summary>
/// This template function opens an AcDbObject for read, write or notify access
/// </summary>
/// <param name="pObj"> A reference to a pointer to the Object. Set to null on errors</param>
/// <param name="id"> The id of the object to open.</param>
/// <param name="mode"> Whether to open the object for read, write or notify access</param>
/// <param name="openErased"> If true, then open the object even when it is erased</param>
/// <returns> Returns Acad::eOk if the object is opened successfully, otherwise an error code.</returns>
///
template <typename T_OBJECT>
inline Acad::ErrorStatus acdbOpenObject(T_OBJECT*& pObj, AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false)
{
  return ::acdbOpenObject((AcDbObject*&) pObj, id, &T_OBJECT::desc, mode, openErased);
}
inline Acad::ErrorStatus acdbOpenObject(AcDbObject*& pObj, AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false)
{
  return ::acdbOpenObject(pObj, id, mode, openErased, nullptr);
}
ACDBCORE2D_PORT Acad::ErrorStatus acdbOpenObject(AcDbEntity*& pEnt, AcDbObjectId id, AcDb::OpenMode mode = AcDb::kForRead, bool openErased = false);
inline Acad::ErrorStatus acdbOpenAcDbEntity(AcDbEntity*& pEnt, AcDbObjectId id, AcDb::OpenMode mode, bool openErasedEntity = false)
{
  return ::acdbOpenObject(pEnt, id, mode, openErasedEntity);
}
Acad::ErrorStatus acdbResurrectMeNow(const AcDbObjectId& id);
Acad::ErrorStatus acdbGetAdsName(ads_name& objName, AcDbObjectId objId);
Acad::ErrorStatus acdbGetObjectId(AcDbObjectId& objId, const ads_name objName);
Acad::ErrorStatus acdbValKey(const ads_name lname);
Acad::ErrorStatus acdbSetReferenced(AcDbObjectId objId);
/// <summary>
// Get the array of currently active Databases
/// </summary>
/// <returns> Reference to a const AcArray of AcDbDatabase pointers.</returns>
/// <remarks> Can be used to validate an AcDbDatabase pointer </remarks>
///
ACDBCORE2D_PORT const AcArray<AcDbDatabase *>& acdbActiveDatabaseArray();
class AcDbViewTableRecord;
class AcDbViewport;
class AcDbObjectContextManager;
Acad::ErrorStatus acdbLoadMlineStyleFile(const ACHAR* sname, const ACHAR* fname);
Acad::ErrorStatus acdbLoadLineTypeFile(const ACHAR* ltname, const ACHAR* fname, AcDbDatabase* pDb);
void* acdbAlloc(size_t);
void* acdbRealloc(void*, size_t);
void acdbFree(void*);
ACDB_PORT void acdbInitialize();
ACDB_PORT void acdbTerminate();
/// <summary>
/// This call controls which language resources RealDWG will attempt to load and use.
/// </summary>
/// <param name="loc">input locale value</param>
/// <returns>Returns Acad::eOk if successful.</returns>
ACDBCORE2D_PORT Acad::ErrorStatus acdbValidateSetup(const AcLocale& loc);
Acad::ErrorStatus acdbCleanUp();
const ACHAR* acdbOriginalXrefFullPathFor(const AcDbDatabase*);
AcGiContext* acdbSetDefaultAcGiContext(AcGiContext*);
Acad::ErrorStatus acdbGetThumbnailBitmapFromDxfFile(const ACHAR* filename, void*& pBitmap);
class AcDbDatabase : public AcRxObject, public AcHeapOperators
{
public:
  ACRX_DECLARE_MEMBERS(AcDbDatabase);
  ACDBCORE2D_PORT AcDbDatabase(bool buildDefaultDrawing = true, bool noDocument = false);
  ACDBCORE2D_PORT virtual ~AcDbDatabase();
    /// <summary>
    /// Find out if this Database is in the process of being destroyed
    /// </summary>
    /// <returns> true if this Database's destructor has been called, false otherwise </returns>
    ///
  ACDBCORE2D_PORT bool isBeingDestroyed() const;
    /// <summary>
    /// Adds a currently non-resident AcDbObject to this database.
    /// </summary>
    /// <param name="id"> Receives the object's new id on success, else null </param>
    /// <param name="pObj"> Pointer to an object which is not yet database resident</param>
    /// <returns> eOk on success, otherwise an error code </returns>
    /// <remarks> Does not set the object's owner, and does not close the object
    ///           Fails with eWrongObjectType if *pObj derives from AcDbEntity
    /// </remarks>
    ///
  ACDBCORE2D_PORT Acad::ErrorStatus addAcDbObject(AcDbObjectId& id, AcDbObject* pObj);
  ACDBCORE2D_PORT Acad::ErrorStatus addAcDbObject(AcDbObject* pObj);
  static Acad::ErrorStatus markObjectNonPersistent(AcDbObjectId id, bool value);
  static bool isObjectNonPersistent(AcDbObjectId id);
  Acad::ErrorStatus getBlockTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getLayerTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getTextStyleTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getLinetypeTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getViewTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getUCSTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getViewportTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getRegAppTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getDimStyleTable(AcDbSymbolTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbBlockTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbLayerTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbTextStyleTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbLinetypeTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbViewTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbUCSTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbViewportTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbRegAppTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getSymbolTable(AcDbDimStyleTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getGroupDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getMLStyleDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getLayoutDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getPlotStyleNameDictionary(AcDbDictionaryWithDefault*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getMaterialDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getVisualStyleDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getColorDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getScaleListDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getNamedObjectsDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getBlockTable(AcDbBlockTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getLayerTable(AcDbLayerTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getTextStyleTable(AcDbTextStyleTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getLinetypeTable(AcDbLinetypeTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getViewTable(AcDbViewTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getUCSTable(AcDbUCSTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getViewportTable(AcDbViewportTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getRegAppTable(AcDbRegAppTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getDimStyleTable(AcDbDimStyleTable*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  Acad::ErrorStatus getPlotSettingsDictionary(AcDbDictionary*& pTable, AcDb::OpenMode mode = AcDb::kForRead);
  AcDbObjectId getSectionManager(void) const;
  Acad::ErrorStatus getSectionManager(AcDbSectionManager*& pMgr, AcDb::OpenMode mode = AcDb::kForRead) const;
  AcDbObjectId dataLinkDictionaryId(void) const;
  Acad::ErrorStatus getDataLinkDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  AcDbDataLinkManager* getDataLinkManager(void) const;
  Acad::ErrorStatus updateDataLink(AcDb::UpdateDirection nDir, AcDb::UpdateOption nOption);
  ACDBCORE2D_PORT AcDbObjectId blockTableId() const;
  ACDBCORE2D_PORT AcDbObjectId layerTableId() const;
  ACDBCORE2D_PORT AcDbObjectId textStyleTableId() const;
  ACDBCORE2D_PORT AcDbObjectId linetypeTableId() const;
  ACDBCORE2D_PORT AcDbObjectId viewTableId() const;
  ACDBCORE2D_PORT AcDbObjectId UCSTableId() const;
  ACDBCORE2D_PORT AcDbObjectId viewportTableId() const;
  ACDBCORE2D_PORT AcDbObjectId regAppTableId() const;
  ACDBCORE2D_PORT AcDbObjectId dimStyleTableId() const;
  ACDBCORE2D_PORT AcDbObjectId mLStyleDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId groupDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId layoutDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId plotStyleNameDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId materialDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId visualStyleDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId colorDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId scaleListDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId namedObjectsDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId plotSettingsDictionaryId() const;
  template <typename TableType>
  AcDbObjectId getSymbolTableId() const;
  AcDbObjectId layerZero() const;
  AcDbObjectId continuousLinetype() const;
  AcDbObjectId byLayerLinetype() const;
  AcDbObjectId byBlockLinetype() const;
  AcDbObjectId globalMaterial() const;
  AcDbObjectId byLayerMaterial() const;
  AcDbObjectId byBlockMaterial() const;
  AcDbObjectId paperSpaceVportId() const;
  AcDbObjectId currentSpaceId() const;
  Acad::ErrorStatus reclaimMemoryFromErasedObjects(const AcDbObjectIdArray& erasedObjects);
  Acad::ErrorStatus purge(AcDbObjectIdArray& ids);
  Acad::ErrorStatus purge(AcDbObjectIdGraph& idGraph);
  Acad::ErrorStatus countHardReferences(const AcDbObjectIdArray& ids, Adesk::UInt32* pCount);
  Acad::ErrorStatus getAcDbObjectId(AcDbObjectId& retId, bool createIfNotFound, const AcDbHandle& objHandle, Adesk::UInt32 xRefId = 0);
  const ACHAR* classDxfName(const AcRxClass* pClass);
  bool hasClass(const AcRxClass* pClass) const;
  enum OpenMode
  {
    kForReadAndReadShare = 1,
    kForReadAndWriteNoShare = 2,
    kForReadAndAllShare = 3,
    kTryForReadShare = 4
  };
  ACDBCORE2D_PORT Acad::ErrorStatus readDwgFile(const ACHAR* fileName, OpenMode shmode = kForReadAndReadShare, bool bAllowCPConversion = false, const wchar_t* wszPassword = nullptr);
  ACDBCORE2D_PORT Acad::ErrorStatus readDwgFile(AcDwgFileHandle* pDwgFile, bool bAllowCPConversion = false, const wchar_t* wszPassword = nullptr);
    /// <summary>
    /// Returns true if this database was read in from a dwg file on disk
    /// and there were read errors, but they were not significant enough to
    /// cause readDwgFile() to return an error.
    /// NOTE: closeInput() should be called before using this function to
    ///       be sure that all objects in the drawing have been read in.
    /// </summary>
  ACDBCORE2D_PORT bool needsRecovery() const;
  ACDBCORE2D_PORT void setFullSaveRequired();
  inline Acad::ErrorStatus saveAs(const ACHAR* fileName, const SecurityParams* pSecParams = 0)
  {
    return saveAs(fileName, true, AcDb::kDHL_CURRENT, pSecParams);
  }
  ACDBCORE2D_PORT Acad::ErrorStatus saveAs(const ACHAR* fileName, const bool bBakAndRename, const AcDb::AcDbDwgVersion dwgVer = AcDb::kDHL_CURRENT, const SecurityParams* pSecParams = 0);
  ACDBCORE2D_PORT Acad::ErrorStatus saveAs(AcDwgFileHandle* pOutputFiler, const SecurityParams* pSecParams = 0, bool crashing = false);
  Acad::ErrorStatus save();
  Acad::ErrorStatus dxfIn(const ACHAR* dxfFilename, const ACHAR* logFilename = nullptr);
  Acad::ErrorStatus dxfIn(IAcReadStream* pInputStream, const ACHAR* logFilename = nullptr);
  Acad::ErrorStatus dxfOut(const ACHAR* fileName, int precision = 16, AcDb::AcDbDwgVersion dwgVer = AcDb::kDHL_CURRENT, bool saveThumbnailImage = false);
    /// <summary>
    /// If a drawing file is associated with this AcDbDatabase, then this function forces
    /// an immediate read of all necessary information from the file into the AcDbDatabase
    /// object and disconnects the file from the AcDbDatabase.
    /// 
    /// If bCloseFile is true, the drawing file will be closed when it has been fully
    /// read into, and disconnected from, the AcDbDatabase.  If bCloseFile is false,
    /// then the drawing file will still be disconnected from the AcDbDatabase, but
    /// the drawing file will remain open until the host application session ends.
    /// Passing true for this argument is recommended.
    /// 
    /// This function will only execute once per AcDbDatabase, so multiple calls will
    /// have no effect after the first call.
    /// 
    /// WARNING:  This function should only be called on AcDbDatabases that your
    ///           application has created and read in from a dwg file using
    ///           AcDbDatabase::readDwgFile().
    ///
    /// This method is mainly for internal use and does not normally need to be called.
    /// AcDbObjects are automatically brought into memory as needed by acdbOpenObject() etc.
    ///
    /// </summary>
    /// <param name="bCloseFile">Input bool indicating whether to close the drawing file</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
  Acad::ErrorStatus closeInput(bool bCloseFile);
  int approxNumObjects() const;
  Adesk::Int32 numberOfSaves() const;
  const ACHAR* originalFileName() const;
  AcDb::AcDbDwgVersion lastSavedAsVersion() const;
  AcDb::AcDbDwgVersion originalFileVersion() const;
  AcDb::AcDbDwgVersion originalFileSavedByVersion() const;
  AcDb::MaintenanceReleaseVersion lastSavedAsMaintenanceVersion() const;
  AcDb::MaintenanceReleaseVersion originalFileMaintenanceVersion() const;
  AcDb::MaintenanceReleaseVersion originalFileSavedByMaintenanceVersion() const;
  AcDwgFileHandle* inputFiler() const;
#  ifdef _ADESK_MAC_
  AcDwgFileHandle* outputFiler() const;
#  endif
  Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb, const AcDbObjectIdArray& outObjIds, const AcGePoint3d& basePoint);
  Acad::ErrorStatus wblock(AcDbDatabase* pOutputDb, const AcDbObjectIdArray& outObjIds, const AcGePoint3d& basePoint, AcDb::DuplicateRecordCloning drc);
  Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb, AcDbObjectId blockId);
  Acad::ErrorStatus wblock(AcDbDatabase*& pOutputDb);
  void forceWblockDatabaseCopy();
  Acad::ErrorStatus insert(AcDbObjectId& blockId, const ACHAR* pBlockName, AcDbDatabase* pDb, bool preserveSourceDatabase = true);
  Acad::ErrorStatus insert(const AcGeMatrix3d& xform, AcDbDatabase* pDb, bool preserveSourceDatabase = true);
  Acad::ErrorStatus insert(AcDbObjectId& blockId, const ACHAR* pSourceBlockName, const ACHAR* pDestinationBlockName, AcDbDatabase* pDb, bool preserveSourceDatabase = true);
  ACDBCORE2D_PORT Acad::ErrorStatus deepCloneObjects(const AcDbObjectIdArray& objectIds, const AcDbObjectId& owner, AcDbIdMapping& idMap, bool deferXlation = false);
  ACDBCORE2D_PORT Acad::ErrorStatus wblockCloneObjects(const AcDbObjectIdArray& objectIds, const AcDbObjectId& owner, AcDbIdMapping& idMap, AcDb::DuplicateRecordCloning drc, bool deferXlation = false);
  void abortDeepClone(AcDbIdMapping& idMap);
  ACDBCORE2D_PORT Acad::ErrorStatus addReactor(AcDbDatabaseReactor* pReactor) const;
  ACDBCORE2D_PORT Acad::ErrorStatus removeReactor(AcDbDatabaseReactor* pReactor) const;
  Acad::ErrorStatus auditXData(AcDbAuditInfo* pInfo);
  AcDbUndoController* undoController() const;
  void disableUndoRecording(bool disable);
  bool undoRecording() const;
  AcDbTransactionManager* transactionManager() const;
  AcDb::MaintenanceReleaseVersion maintenanceReleaseVersion() const
  {
    return AcDb::kMReleaseCurrent;
  }
  Acad::ErrorStatus restoreOriginalXrefSymbols();
  Acad::ErrorStatus restoreForwardingXrefSymbols();
  AcDbObjectId xrefBlockId() const;
    /// <summary>
    /// This function provides BITMAP thumbnail of database as return value
    /// </summary>
    /// <returns> This will return BITMAP thumbnail in void* buffer for database </returns>
    ///
  void* thumbnailBitmap() const;
    /// <summary>
    /// This function sets BITMAP thumbnail into database
    /// </summary>
    /// <param name="pBmp"> A pointer of Bitmap thumbnail to be set into database </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    ///
  Acad::ErrorStatus setThumbnailBitmap(void* pBmp);
    /// <summary>
    /// This function provides Atil::Image thumbnail of database as output
    /// </summary>
    /// <param name="pPreviewImage"> A reference to the pointer of Atil::Image thumbnail </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
  Acad::ErrorStatus thumbnailImage(Atil::Image*& pPreviewImage) const;
    /// <summary>
    /// This functions sets Atil::Image thumbnail into database
    /// </summary>
    /// <param name="pPreviewImage"> A pointer of Atil::Image thumbnail to be set into database </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
  Acad::ErrorStatus setThumbnailImage(const Atil::Image* pPreviewImage);
  bool retainOriginalThumbnailBitmap() const;
  void setRetainOriginalThumbnailBitmap(bool retain);
  bool setSecurityParams(const SecurityParams* pSecParams, bool bSetDbMod = true);
  const SecurityParams* cloneSecurityParams();
  static void disposeSecurityParams(const SecurityParams* pSecParams);
  bool dimaso() const;
  Acad::ErrorStatus setDimaso(bool aso);
  bool dimsho() const;
  Acad::ErrorStatus setDimsho(bool sho);
  bool plinegen() const;
  Acad::ErrorStatus setPlinegen(bool gen);
  bool orthomode() const;
  Acad::ErrorStatus setOrthomode(bool mode);
  bool regenmode() const;
  Acad::ErrorStatus setRegenmode(bool mode);
  bool fillmode() const;
  Acad::ErrorStatus setFillmode(bool mode);
  bool qtextmode() const;
  Acad::ErrorStatus setQtextmode(bool mode);
  bool psltscale() const;
  Acad::ErrorStatus setPsltscale(bool scale);
  bool limcheck() const;
  Acad::ErrorStatus setLimcheck(bool check);
  bool blipmode() const;
  Acad::ErrorStatus setBlipmode(bool mode);
  Adesk::Int16 saveproxygraphics() const;
  Acad::ErrorStatus setSaveproxygraphics(Adesk::Int16 saveimg);
  Adesk::Int16 delUsedObj() const;
  Acad::ErrorStatus setDelUsedObj(Adesk::Int16 deleteObj);
  bool dispSilh() const;
  Acad::ErrorStatus setDispSilh(bool silh);
  bool plineEllipse() const;
  Acad::ErrorStatus setPlineEllipse(bool pline);
  bool usrtimer() const;
  Acad::ErrorStatus setUsrtimer(bool timer);
  bool skpoly() const;
  Acad::ErrorStatus setSkpoly(bool asPoly);
  bool angdir() const;
  Acad::ErrorStatus setAngdir(bool dir);
  bool splframe() const;
  Acad::ErrorStatus setSplframe(bool disp);
  Adesk::UInt8 xclipFrame() const;
  Acad::ErrorStatus setXclipFrame(Adesk::UInt8 disp);
  bool attreq() const;
  Acad::ErrorStatus setAttreq(bool req);
  bool attdia() const;
  Acad::ErrorStatus setAttdia(bool dia);
  bool mirrtext() const;
  Acad::ErrorStatus setMirrtext(bool mirror);
  bool worldview() const;
  Acad::ErrorStatus setWorldview(bool view);
  bool tilemode() const;
  Acad::ErrorStatus setTilemode(bool mode);
  bool plimcheck() const;
  Acad::ErrorStatus setPlimcheck(bool check);
  bool visretain() const;
  Acad::ErrorStatus setVisretain(bool retain);
  Adesk::Int16 dragmode() const;
  Acad::ErrorStatus setDragmode(Adesk::Int16 mode);
  Adesk::Int16 treedepth() const;
  Acad::ErrorStatus setTreedepth(Adesk::Int16 depth);
  Adesk::Int16 lunits() const;
  Acad::ErrorStatus setLunits(Adesk::Int16 lunits);
  Adesk::Int16 luprec() const;
  Acad::ErrorStatus setLuprec(Adesk::Int16 prec);
  Adesk::Int16 aunits() const;
  Acad::ErrorStatus setAunits(Adesk::Int16 aunits);
  Adesk::Int16 auprec() const;
  Acad::ErrorStatus setAuprec(Adesk::Int16 auprec);
  Adesk::Int16 attmode() const;
  Acad::ErrorStatus setAttmode(Adesk::Int16 mode);
  Adesk::Int16 coords() const;
  Acad::ErrorStatus setCoords(Adesk::Int16 coords);
  Adesk::Int16 pdmode() const;
  Acad::ErrorStatus setPdmode(Adesk::Int16 mode);
  Adesk::Int16 pickstyle() const;
  Acad::ErrorStatus setPickstyle(Adesk::Int16 style);
  Adesk::Int16 useri1() const;
  Acad::ErrorStatus setUseri1(Adesk::Int16 val);
  Adesk::Int16 useri2() const;
  Acad::ErrorStatus setUseri2(Adesk::Int16 val);
  Adesk::Int16 useri3() const;
  Acad::ErrorStatus setUseri3(Adesk::Int16 val);
  Adesk::Int16 useri4() const;
  Acad::ErrorStatus setUseri4(Adesk::Int16 val);
  Adesk::Int16 useri5() const;
  Acad::ErrorStatus setUseri5(Adesk::Int16 val);
  Adesk::Int16 splinesegs() const;
  Acad::ErrorStatus setSplinesegs(Adesk::Int16 segs);
  Adesk::Int16 surfu() const;
  Acad::ErrorStatus setSurfu(Adesk::Int16 u);
  Adesk::Int16 surfv() const;
  Acad::ErrorStatus setSurfv(Adesk::Int16 v);
  Adesk::Int16 surftype() const;
  Acad::ErrorStatus setSurftype(Adesk::Int16 type);
  Adesk::Int16 surftab1() const;
  Acad::ErrorStatus setSurftab1(Adesk::Int16 tab1);
  Adesk::Int16 surftab2() const;
  Acad::ErrorStatus setSurftab2(Adesk::Int16 tab2);
  Adesk::Int16 splinetype() const;
  Acad::ErrorStatus setSplinetype(Adesk::Int16 type);
  Adesk::Int16 shadedge() const;
  Acad::ErrorStatus setShadedge(Adesk::Int16 mode);
  Adesk::Int16 shadedif() const;
  Acad::ErrorStatus setShadedif(Adesk::Int16 dif);
  AcDb::MeasurementValue measurement() const;
  Acad::ErrorStatus setMeasurement(AcDb::MeasurementValue type);
  Adesk::Int16 unitmode() const;
  Acad::ErrorStatus setUnitmode(Adesk::Int16 mode);
  Adesk::Int16 maxactvp() const;
  Acad::ErrorStatus setMaxactvp(Adesk::Int16 max);
  Adesk::Int16 isolines() const;
  Acad::ErrorStatus setIsolines(Adesk::Int16 isolines);
  Adesk::UInt8 dwfframe() const;
  Acad::ErrorStatus setDwfframe(Adesk::UInt8);
  Adesk::UInt8 dgnframe() const;
  Acad::ErrorStatus setDgnframe(Adesk::UInt8);
  Adesk::Int8 pdfframe() const;
  Acad::ErrorStatus setPdfframe(Adesk::Int8 val);
  double ltscale() const;
  Acad::ErrorStatus setLtscale(double scale);
  double textsize() const;
  Acad::ErrorStatus setTextsize(double size);
  double tracewid() const;
  Acad::ErrorStatus setTracewid(double width);
  double sketchinc() const;
  Acad::ErrorStatus setSketchinc(double inc);
  double filletrad() const;
  Acad::ErrorStatus setFilletrad(double radius);
  double thickness() const;
  Acad::ErrorStatus setThickness(double thickness);
  AcDb::LineWeight celweight() const;
  Acad::ErrorStatus setCelweight(AcDb::LineWeight weight);
  static bool isValidLineWeight(int weight);
  static AcDb::LineWeight getNearestLineWeight(int weight);
  AcDb::EndCaps endCaps() const;
  Acad::ErrorStatus setEndCaps(AcDb::EndCaps type);
  AcDb::JoinStyle joinStyle() const;
  Acad::ErrorStatus setJoinStyle(AcDb::JoinStyle style);
  bool lineWeightDisplay() const;
  Acad::ErrorStatus setLineWeightDisplay(bool display);
  bool xrefEditEnabled() const;
  Acad::ErrorStatus setXrefEditEnabled(bool enable);
  bool oleStartUp() const;
  Acad::ErrorStatus setOleStartUp(bool val);
  double angbase() const;
  Acad::ErrorStatus setAngbase(double angle);
  double pdsize() const;
  Acad::ErrorStatus setPdsize(double size);
  double plinewid() const;
  Acad::ErrorStatus setPlinewid(double width);
  double userr1() const;
  Acad::ErrorStatus setUserr1(double val);
  double userr2() const;
  Acad::ErrorStatus setUserr2(double val);
  double userr3() const;
  Acad::ErrorStatus setUserr3(double val);
  double userr4() const;
  Acad::ErrorStatus setUserr4(double val);
  double userr5() const;
  Acad::ErrorStatus setUserr5(double val);
  double chamfera() const;
  Acad::ErrorStatus setChamfera(double val);
  double chamferb() const;
  Acad::ErrorStatus setChamferb(double val);
  double chamferc() const;
  Acad::ErrorStatus setChamferc(double val);
  double chamferd() const;
  Acad::ErrorStatus setChamferd(double val);
  double facetres() const;
  Acad::ErrorStatus setFacetres(double facetres);
  double get3dDwfPrec() const;
  Acad::ErrorStatus set3dDwfPrec(double DwfPrec);
  ACDBCORE2D_PORT Acad::ErrorStatus getMenu(AcString& sMenuName) const;
  Acad::ErrorStatus getMenu(ACHAR*& pOutput) const;
  bool hpInherit() const;
  Acad::ErrorStatus setHpInherit(const bool inherit);
  AcGePoint2d hpOrigin() const;
  Acad::ErrorStatus setHpOrigin(const AcGePoint2d& origin);
  const AcDbDate tdcreate() const;
  const AcDbDate tdupdate() const;
  const AcDbDate tducreate() const;
  const AcDbDate tduupdate() const;
  const AcDbDate tdindwg() const;
  const AcDbDate tdusrtimer() const;
  Acad::ErrorStatus resetTimes();
  AcCmColor cecolor() const;
  Acad::ErrorStatus setCecolor(const AcCmColor& color);
  AcCmTransparency cetransparency() const;
  Acad::ErrorStatus setCetransparency(const AcCmTransparency& transparency);
  AcDbHandle handseed() const;
  Acad::ErrorStatus setHandseed(const AcDbHandle& handle);
  AcDbObjectId clayer() const;
  Acad::ErrorStatus setClayer(AcDbObjectId objId);
  AcDb::PlotStyleNameType getCePlotStyleNameId(AcDbObjectId& id) const;
  Acad::ErrorStatus setCePlotStyleName(AcDb::PlotStyleNameType, AcDbObjectId newId = AcDbObjectId::kNull);
  AcDbObjectId textstyle() const;
  Acad::ErrorStatus setTextstyle(AcDbObjectId objId);
  AcDbObjectId celtype() const;
  Acad::ErrorStatus setCeltype(AcDbObjectId objId);
  AcDbObjectId cmaterial() const;
  Acad::ErrorStatus setCmaterial(AcDbObjectId objId);
  AcDbObjectId dimstyle() const;
  Acad::ErrorStatus setDimstyle(AcDbObjectId styleId);
  Acad::ErrorStatus getDimstyleData(AcDbDimStyleTableRecord*& pRec) const;
  Acad::ErrorStatus getDimstyleChildData(const AcRxClass* pDimClass, AcDbDimStyleTableRecord*& pRec, AcDbObjectId& style) const;
  AcDbObjectId getDimstyleChildId(const AcRxClass* pDimClass, AcDbObjectId& parentStyle) const;
  AcDbObjectId getDimstyleParentId(AcDbObjectId& childStyle) const;
  Acad::ErrorStatus setDimstyleData(AcDbDimStyleTableRecord* pRec);
  Acad::ErrorStatus setDimstyleData(AcDbObjectId id);
  AcDbObjectId cmlstyleID() const;
  Acad::ErrorStatus setCmlstyleID(AcDbObjectId objId);
  Adesk::Int16 cmljust() const;
  Acad::ErrorStatus setCmljust(Adesk::Int16 just);
  double cmlscale() const;
  Acad::ErrorStatus setCmlscale(double scale);
  double celtscale() const;
  Acad::ErrorStatus setCeltscale(double scale);
  AcGePoint3d pinsbase() const;
  Acad::ErrorStatus setPinsbase(const AcGePoint3d& base);
  AcGePoint3d pextmin() const;
  AcGePoint3d pextmax() const;
  Acad::ErrorStatus setPextmin(const AcGePoint3d& min);
  Acad::ErrorStatus setPextmax(const AcGePoint3d& max);
  AcGePoint2d plimmin() const;
  Acad::ErrorStatus setPlimmin(const AcGePoint2d& min);
  AcGePoint2d plimmax() const;
  Acad::ErrorStatus setPlimmax(const AcGePoint2d& max);
  double pelevation() const;
  Acad::ErrorStatus setPelevation(double elev);
  AcGePoint3d pucsorg() const;
  AcGeVector3d pucsxdir() const;
  AcGeVector3d pucsydir() const;
  ACDBCORE2D_PORT Acad::ErrorStatus setPucs(const AcGePoint3d& ucsOrigin, const AcGeVector3d& ucsXDir, const AcGeVector3d& ucsYDir);
  AcDbObjectId pucsname() const;
  ACDBCORE2D_PORT Acad::ErrorStatus setPucsname(const AcDbObjectId& ucsRecId);
  AcDbObjectId pucsBase() const;
  Acad::ErrorStatus setPucsBase(const AcDbObjectId& ucsid);
  AcGePoint3d worldPucsBaseOrigin(AcDb::OrthographicView orthoView) const;
  Acad::ErrorStatus setWorldPucsBaseOrigin(const AcGePoint3d& origin, AcDb::OrthographicView orthoView);
  bool isPucsOrthographic(AcDb::OrthographicView& orthoView) const;
  double cameraHeight() const;
  Acad::ErrorStatus setCameraHeight(const double cameraHeight);
  double lensLength() const;
  Acad::ErrorStatus setLensLength(const double lensLength);
  bool cameraDisplay() const;
  Acad::ErrorStatus setCameraDisplay(const bool cameraDisplay);
  double stepsPerSec() const;
  Acad::ErrorStatus setStepsPerSec(double stepsPerSec);
  double stepSize() const;
  Acad::ErrorStatus setStepSize(double stepSize);
  bool realWorldScale() const;
  Acad::ErrorStatus setRealWorldScale(const bool realWorldScale);
  AcGePoint3d insbase() const;
  Acad::ErrorStatus setInsbase(const AcGePoint3d& base);
  AcGePoint3d extmin() const;
  AcGePoint3d extmax() const;
  Acad::ErrorStatus updateExt(bool doBestFit = false);
  Acad::ErrorStatus setExtmin(const AcGePoint3d& min);
  Acad::ErrorStatus setExtmax(const AcGePoint3d& max);
  AcGePoint2d limmin() const;
  Acad::ErrorStatus setLimmin(const AcGePoint2d& min);
  AcGePoint2d limmax() const;
  Acad::ErrorStatus setLimmax(const AcGePoint2d& max);
  double elevation() const;
  Acad::ErrorStatus setElevation(double elev);
  AcGePoint3d ucsorg() const;
  AcGeVector3d ucsxdir() const;
  AcGeVector3d ucsydir() const;
  ACDBCORE2D_PORT Acad::ErrorStatus setUcs(const AcGePoint3d& ucsOrigin, const AcGeVector3d& ucsXDir, const AcGeVector3d& ucsYDir);
  AcDbObjectId ucsname() const;
  ACDBCORE2D_PORT Acad::ErrorStatus setUcsname(const AcDbObjectId& ucsRecId);
  AcDbObjectId ucsBase() const;
  Acad::ErrorStatus setUcsBase(AcDbObjectId ucsid);
  AcGePoint3d worldUcsBaseOrigin(AcDb::OrthographicView orthoView) const;
  Acad::ErrorStatus setWorldUcsBaseOrigin(const AcGePoint3d& origin, AcDb::OrthographicView orthoView);
  bool isUcsOrthographic(AcDb::OrthographicView& orthoView) const;
/// <summary>
/// This function returns the EMR drawing setting.  0 is not EMR drawing; 1 is EMR drawing.
/// The EMR flag gets set when a drawing is  saved in a EMR (Student Version) product. 
/// </summary>
  bool isEMR() const;
#  undef DBDIMVAR_H
#  include "dbdimvar.h"
  Acad::ErrorStatus getDimpost(ACHAR*& pOutput) const;
  Acad::ErrorStatus getDimapost(ACHAR*& pOutput) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getDimblk(AcString& sOutput) const;
  Acad::ErrorStatus getDimblk(ACHAR*& pOutput) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getDimblk1(AcString& sOutput) const;
  Acad::ErrorStatus getDimblk1(ACHAR*& pOutput) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getDimblk2(AcString& sOutput) const;
  Acad::ErrorStatus getDimblk2(ACHAR*& pOutput) const;
  int dimfit() const;
  int dimunit() const;
  Acad::ErrorStatus setDimfit(int fit);
  Acad::ErrorStatus setDimunit(int unit);
  Acad::ErrorStatus getDimRecentStyleList(AcDbObjectIdArray& objIds) const;
  Acad::ErrorStatus loadLineTypeFile(const ACHAR* ltn, const ACHAR* filename);
  ACDBCORE2D_PORT Acad::ErrorStatus getProjectName(AcString& sProjectName) const;
  Acad::ErrorStatus getProjectName(ACHAR*& pOutput) const;
  Acad::ErrorStatus setProjectName(const ACHAR*);
  ACDBCORE2D_PORT Acad::ErrorStatus getHyperlinkBase(AcString& sHyperlinkBase) const;
  Acad::ErrorStatus getHyperlinkBase(ACHAR*& pOutput) const;
  Acad::ErrorStatus setHyperlinkBase(const ACHAR*);
  ACDBCORE2D_PORT Acad::ErrorStatus getStyleSheet(AcString& sStyleSheet) const;
  Acad::ErrorStatus getStyleSheet(ACHAR*& pOutput) const;
  Acad::ErrorStatus setStyleSheet(const ACHAR*);
  Acad::ErrorStatus getFilename(const ACHAR*& pOutput) const;
  bool isPartiallyOpened() const;
  Acad::ErrorStatus applyPartialOpenFilters(const AcDbSpatialFilter* pSpatialFilter, const AcDbLayerFilter* pLayerFilter);
  void disablePartialOpen();
  ACDBCORE2D_PORT Acad::ErrorStatus getFingerprintGuid(AcString& guidString) const;
  Acad::ErrorStatus getFingerprintGuid(ACHAR*& guidString) const;
  Acad::ErrorStatus setFingerprintGuid(const ACHAR* pNewGuid);
  ACDBCORE2D_PORT Acad::ErrorStatus getVersionGuid(AcString& guidString) const;
  Acad::ErrorStatus getVersionGuid(ACHAR*& guidString) const;
  Acad::ErrorStatus setVersionGuid(const ACHAR* pNewGuid);
  int tstackalign() const;
  Acad::ErrorStatus setTStackAlign(int val);
  int tstacksize() const;
  Acad::ErrorStatus setTStackSize(int val);
  AcDb::UnitsValue insunits() const;
  Acad::ErrorStatus setInsunits(const AcDb::UnitsValue units);
  bool plotStyleMode() const;
  double viewportScaleDefault() const;
  Acad::ErrorStatus setViewportScaleDefault(double newDefaultVPScale);
  bool dwgFileWasSavedByAutodeskSoftware() const;
  AcDbLayerStateManager* getLayerStateManager() const;
  AcDbObjectContextManager* objectContextManager() const;
  Adesk::UInt8 sortEnts() const;
  Acad::ErrorStatus setSortEnts(Adesk::UInt8 sortEnts);
  Adesk::UInt8 drawOrderCtl() const;
  Acad::ErrorStatus setDrawOrderCtl(Adesk::UInt8 val);
  Adesk::UInt8 dimAssoc() const;
  Acad::ErrorStatus setDimAssoc(Adesk::UInt8 val);
  Adesk::UInt8 hideText() const;
  Acad::ErrorStatus setHideText(Adesk::UInt8 val);
  Adesk::UInt8 haloGap() const;
  Acad::ErrorStatus setHaloGap(Adesk::UInt8 val);
  Adesk::UInt16 obscuredColor() const;
  Acad::ErrorStatus setObscuredColor(Adesk::UInt16 val);
  Adesk::UInt8 obscuredLineType() const;
  Acad::ErrorStatus setObscuredLineType(Adesk::UInt8 val);
  Adesk::UInt8 intersectDisplay() const;
  Acad::ErrorStatus setIntersectDisplay(Adesk::UInt8 val);
  Adesk::UInt16 intersectColor() const;
  Acad::ErrorStatus setIntersectColor(Adesk::UInt16 val);
  Acad::ErrorStatus getTableStyleDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  AcDbObjectId tableStyleDictionaryId() const;
  AcDbObjectId tablestyle() const;
  Acad::ErrorStatus setTablestyle(AcDbObjectId objId);
  Acad::ErrorStatus getMLeaderStyleDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  AcDbObjectId mleaderStyleDictionaryId() const;
  AcDbObjectId mleaderstyle() const;
  Acad::ErrorStatus setMLeaderstyle(AcDbObjectId objId);
  ACDBCORE2D_PORT Acad::ErrorStatus getDetailViewStyleDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  ACDBCORE2D_PORT AcDbObjectId detailViewStyleDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId detailViewStyle() const;
  ACDBCORE2D_PORT Acad::ErrorStatus setDetailViewStyle(AcDbObjectId objId);
  ACDBCORE2D_PORT Acad::ErrorStatus getSectionViewStyleDictionary(AcDbDictionary*& pDict, AcDb::OpenMode mode = AcDb::kForRead);
  ACDBCORE2D_PORT AcDbObjectId sectionViewStyleDictionaryId() const;
  ACDBCORE2D_PORT AcDbObjectId sectionViewStyle() const;
  ACDBCORE2D_PORT Acad::ErrorStatus setSectionViewStyle(AcDbObjectId objId);
  Acad::ErrorStatus evaluateFields(int nContext, const ACHAR* pszPropName = nullptr, AcDbDatabase* pDb = nullptr, int* pNumFound = nullptr, int* pNumEvaluated = nullptr);
  Acad::ErrorStatus getViewportArray(AcDbObjectIdArray& vportIds, bool bGetPaperspaceVports = true) const;
  Acad::ErrorStatus getVisualStyleList(AcArray<const ACHAR*>& vstyleList);
  Adesk::UInt8 solidHist() const;
  Acad::ErrorStatus setSolidHist(Adesk::UInt8 val);
  Adesk::UInt8 showHist() const;
  Acad::ErrorStatus setShowHist(Adesk::UInt8 val);
  double psolWidth() const;
  Acad::ErrorStatus setPsolWidth(double width);
  double psolHeight() const;
  Acad::ErrorStatus setPsolHeight(double height);
  Adesk::UInt16 loftParam() const;
  Acad::ErrorStatus setLoftParam(Adesk::UInt16 flags);
  Adesk::UInt8 loftNormals() const;
  Acad::ErrorStatus setLoftNormals(Adesk::UInt8 value);
  double loftAng1() const;
  Acad::ErrorStatus setLoftAng1(double ang1);
  double loftAng2() const;
  Acad::ErrorStatus setLoftAng2(double ang2);
  double loftMag1() const;
  Acad::ErrorStatus setLoftMag1(double mag1);
  double loftMag2() const;
  Acad::ErrorStatus setLoftMag2(double mag2);
  double latitude() const;
  Acad::ErrorStatus setLatitude(double lat);
  double longitude() const;
  Acad::ErrorStatus setLongitude(double lng);
  double northDirection() const;
  Acad::ErrorStatus setNorthDirection(double northdir);
  AcDb::TimeZone timeZone() const;
  Acad::ErrorStatus setTimeZone(AcDb::TimeZone tz);
  Acad::ErrorStatus getTimeZoneInfo(AcDb::TimeZone tz, double& offset, AcString& desc) const;
  Acad::ErrorStatus setTimeZoneAsUtcOffset(double offset);
  bool geoMarkerVisibility() const;
  Acad::ErrorStatus setGeoMarkerVisibility(bool value);
  ACDBCORE2D_PORT AcString geoCoordinateSystemId() const;
  Adesk::UInt8 lightGlyphDisplay() const;
  Acad::ErrorStatus setLightGlyphDisplay(Adesk::UInt8 val);
  Adesk::UInt8 tileModeLightSynch() const;
  Acad::ErrorStatus setTileModeLightSynch(Adesk::UInt8 val);
  AcCmColor interfereColor() const;
  Acad::ErrorStatus setInterfereColor(const AcCmColor& color);
  AcDbObjectId interfereObjVisStyle() const;
  Acad::ErrorStatus setInterfereObjVisStyle(AcDbObjectId id);
  AcDbObjectId interfereVpVisStyle() const;
  Acad::ErrorStatus setInterfereVpVisStyle(AcDbObjectId id);
  AcDbObjectId dragVisStyle() const;
  Acad::ErrorStatus setDragVisStyle(AcDbObjectId id);
  Adesk::UInt8 cshadow() const;
  Acad::ErrorStatus setCshadow(Adesk::UInt8 val);
  double shadowPlaneLocation() const;
  Acad::ErrorStatus setShadowPlaneLocation(double val);
  AcDbAnnotationScale* cannoscale() const;
  Acad::ErrorStatus setCannoscale(AcDbAnnotationScale*);
  bool annoAllVisible() const;
  Acad::ErrorStatus setAnnoAllVisible(bool allvis);
  bool annotativeDwg() const;
  Acad::ErrorStatus setAnnotativeDwg(bool anno);
  bool msltscale() const;
  Acad::ErrorStatus setMsltscale(bool val);
  Adesk::UInt8 lightingUnits() const;
  Acad::ErrorStatus setLightingUnits(Adesk::UInt8 val);
  bool lightsInBlocks() const;
  Acad::ErrorStatus setLightsInBlocks(bool val);
  Adesk::Int16 dxeVal() const;
  Acad::ErrorStatus setDxeVal(Adesk::Int16 val);
  double mleaderscale() const;
  Acad::ErrorStatus setMLeaderscale(double scale);
  Adesk::Int16 cDynDisplayMode() const;
  Acad::ErrorStatus setCDynDisplayMode(Adesk::Int16 val);
  Adesk::Int16 previewType() const;
  Acad::ErrorStatus setPreviewType(Adesk::Int16 val);
  Adesk::UInt8 indexctl() const;
  Acad::ErrorStatus setIndexctl(Adesk::UInt8 val);
  Adesk::UInt8 layerEval() const;
  Acad::ErrorStatus setLayerEval(Adesk::UInt8 val);
  Adesk::Int16 layerNotify() const;
  Acad::ErrorStatus setLayerNotify(Adesk::Int16 val);
  double msOleScale() const;
  Acad::ErrorStatus setMsOleScale(double val);
  Adesk::UInt8 updateThumbnail() const;
  Acad::ErrorStatus setUpdateThumbnail(Adesk::UInt8 val);
  enum EraseMask
  {
    kZeroLengthCurve = 0x01,
    kEmptyText = 0x02,
    kAllEmptyObj = 0xFFFFFFFF
  };
  Adesk::UInt32 eraseEmptyObjects(const Adesk::UInt32 flags);
  Adesk::UInt32 countEmptyObjects(const Adesk::UInt32 flags);
private:
  friend class AcDbSystemInternals;
  AcDbImpDatabase* mpImpDb = nullptr;
  AcDbDatabase(const AcDbDatabase&) = delete;
  AcDbDatabase& operator =(const AcDbDatabase&);
};
template <typename ObjType>
inline Acad::ErrorStatus acutGetAcStringConvertToAChar(const ObjType* pObj, Acad::ErrorStatus (*pFunc) (AcString&) const, ACHAR*& pOutput)
{
  AcString sOutput;
  const Acad::ErrorStatus es = (pObj->*pFunc)(sOutput);
  if (es != Acad::eOk)
  {
    pOutput = nullptr;
    return es;
  }
  return ::acutNewString(sOutput.kwszPtr(), pOutput);
}
template <typename ObjType>
inline ACHAR* acutGetAcStringConvertToAChar(const ObjType* pObj, Acad::ErrorStatus (*pFunc) (AcString&) const)
{
  AcString sOutput;
  const Acad::ErrorStatus es = (pObj->*pFunc)(sOutput);
  ACHAR* pRet = nullptr;
  if (es == Acad::eOk)
  {
    ::acutNewString(sOutput.kwszPtr(), pRet);
  }
  return pRet;
}
inline ACHAR* acutAcStringToAChar(const AcString& s, Acad::ErrorStatus es)
{
  ACHAR* pBuf = nullptr;
  if (es == Acad::eOk)
  {
    ::acutNewString(s.kwszPtr(), pBuf);
  }
  return pBuf;
}
inline Acad::ErrorStatus acutAcStringToAChar(const AcString& s, ACHAR*& pBuf, Acad::ErrorStatus es)
{
  pBuf = nullptr;
  if (es != Acad::eOk)
  {
    return es;
  }
  return ::acutNewString(s.kwszPtr(), pBuf);
}
inline Acad::ErrorStatus AcDbDatabase::getDimpost(ACHAR*& pOutput) const
{
  return ::acutNewString(this->dimpost(), pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getDimapost(ACHAR*& pOutput) const
{
  return ::acutNewString(this->dimapost(), pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getDimblk(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getDimblk, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getDimblk1(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getDimblk1, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getDimblk2(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getDimblk2, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getMenu(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getMenu, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getProjectName(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getProjectName, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getHyperlinkBase(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getHyperlinkBase, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getStyleSheet(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getStyleSheet, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getFingerprintGuid(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getFingerprintGuid, pOutput);
}
inline Acad::ErrorStatus AcDbDatabase::getVersionGuid(ACHAR*& pOutput) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbDatabase::getVersionGuid, pOutput);
}
inline Acad::ErrorStatus acdbSaveAs2004(AcDbDatabase* pDb, const ACHAR* fileName)
{
  return pDb->saveAs(fileName, false, AcDb::kDHL_1800);
}
inline Acad::ErrorStatus acdbSaveAs2000(AcDbDatabase* pDb, const ACHAR* fileName)
{
  return pDb->saveAs(fileName, false, AcDb::kDHL_1015);
}
inline Acad::ErrorStatus acdbSaveAsR14(AcDbDatabase* pDb, const ACHAR* fileName)
{
  return pDb->saveAs(fileName, false, AcDb::kDHL_1014);
}
inline Acad::ErrorStatus acdbDxfOutAs2004(AcDbDatabase* pDb, const ACHAR* fileName, const int precision = 16)
{
  return pDb->dxfOut(fileName, precision, AcDb::kDHL_1800);
}
inline Acad::ErrorStatus acdbDxfOutAs2000(AcDbDatabase* pDb, const ACHAR* fileName, const int precision = 16)
{
  return pDb->dxfOut(fileName, precision, AcDb::kDHL_1015);
}
inline Acad::ErrorStatus acdbDxfOutAsR12(AcDbDatabase* pDb, const ACHAR* fileName, const int precision = 16)
{
  return pDb->dxfOut(fileName, precision, AcDb::kDHL_1009);
}
class AcDbObjectIterator : public AcRxObject, public AcHeapOperators
{
public:
  ACRX_DECLARE_MEMBERS(AcDbObjectIterator);
  virtual ~AcDbObjectIterator();
  bool done() const;
  void step(bool backwards = false, bool skipDeleted = true);
  void setPosition(AcDbEntity* pEnt);
  void setPosition(AcDbObjectId pObj);
  void start(bool atEnd = false);
  AcDbEntity* entity();
  AcDbObjectId objectId();
private:
  friend class AcDbSystemInternals;
  AcDbObjectIterator();
  AcDbSpaceIterator* mpImpIterator = nullptr;
};
class ADESK_NO_VTABLE AcDbObject : public AcGiDrawable, public AcHeapOperators
{
  ACDB_DECLARE_MEMBERS(AcDbObject);
public:
  virtual ~AcDbObject();
  AcDbObjectId objectId() const;
  AcDbObjectId ownerId() const;
  virtual Acad::ErrorStatus setOwnerId(AcDbObjectId objId);
  void getAcDbHandle(AcDbHandle& handle) const;
  AcDbDatabase* database() const;
  Acad::ErrorStatus createExtensionDictionary();
  AcDbObjectId extensionDictionary() const;
  Acad::ErrorStatus releaseExtensionDictionary();
  Acad::ErrorStatus upgradeOpen();
  Acad::ErrorStatus upgradeFromNotify(Adesk::Boolean& wasWritable);
  Acad::ErrorStatus downgradeOpen();
  Acad::ErrorStatus downgradeToNotify(Adesk::Boolean wasWritable);
  virtual Acad::ErrorStatus subOpen(AcDb::OpenMode mode);
  Acad::ErrorStatus cancel();
  virtual Acad::ErrorStatus subCancel();
  Acad::ErrorStatus close();
  Acad::ErrorStatus closeAndPage(Adesk::Boolean onlyWhenClean = true);
  virtual Acad::ErrorStatus subClose();
  Acad::ErrorStatus erase(Adesk::Boolean erasing = true);
  virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing);
  Acad::ErrorStatus handOverTo(AcDbObject* newObject, Adesk::Boolean keepXData = true, Adesk::Boolean keepExtDict = true);
  virtual Acad::ErrorStatus subHandOverTo(AcDbObject* newObject);
  Acad::ErrorStatus swapIdWith(AcDbObjectId otherId, Adesk::Boolean swapXdata = false, Adesk::Boolean swapExtDict = false);
  virtual Acad::ErrorStatus subSwapIdWith(AcDbObjectId otherId, Adesk::Boolean swapXdata = false, Adesk::Boolean swapExtDict = false);
  virtual Acad::ErrorStatus swapReferences(const AcDbIdMapping& idMap);
  virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);
  Acad::ErrorStatus dwgIn(AcDbDwgFiler* pFiler);
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
  Acad::ErrorStatus dwgOut(AcDbDwgFiler* pFiler) const;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
  Acad::ErrorStatus dxfIn(AcDbDxfFiler* pFiler);
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
    /// <summary>
    /// This function does some internal bookkeeping, calls the object's AcDbObject::dxfOutFields()
    /// function, and then uses bAllXdata and pRegAppIds to determine what, if any xdata should be
    /// written out. If bAllXdata == true, then all xdata is written out. If bAllXdata == false and
    /// pRegAppIds == nullptr or points to an empty array, then no xdata is written out.  If
    /// bAllXdata == false and pRegAppIds points to a non-empty array, then the xdata (if any) for
    /// those regapp objectIds is written out.
    /// </summary>
    /// <param name="pFiler">Input pointer to DXF filer to be used for this filing operation</param>    
    /// <param name="bAllXdata">Input bool to specify whether or not all xdata should be written out</param>
    /// <param name="pRegAppIds">Input pointer to array of regapp objectIds</param>    
    /// <returns>Returns the filer's status, which is Acad::eOk if successful.</returns>    
  ACDBCORE2D_PORT Acad::ErrorStatus dxfOut(AcDbDxfFiler* pFiler, bool bAllXdata, const AcDbObjectIdArray* pRegAppIds) const;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
  virtual AcDb::DuplicateRecordCloning mergeStyle() const;
  virtual resbuf* xData(const ACHAR* regappName = nullptr) const;
  virtual Acad::ErrorStatus setXData(const resbuf* xdata);
  Acad::ErrorStatus xDataTransformBy(const AcGeMatrix3d& xform);
  Acad::ErrorStatus setBinaryData(const ACHAR* key, Adesk::Int32 size, const char* data);
  Acad::ErrorStatus getBinaryData(const ACHAR* key, Adesk::Int32& size, char*& data) const;
  Adesk::Boolean isEraseStatusToggled() const;
  Adesk::Boolean isErased() const;
  Adesk::Boolean isReadEnabled() const;
  Adesk::Boolean isWriteEnabled() const;
  Adesk::Boolean isNotifyEnabled() const;
  Adesk::Boolean isModified() const;
  Adesk::Boolean isModifiedXData() const;
  Adesk::Boolean isModifiedGraphics() const;
  Adesk::Boolean isNewObject() const;
  Adesk::Boolean isNotifying() const;
  Adesk::Boolean isUndoing() const;
  Adesk::Boolean isCancelling() const;
  Adesk::Boolean isReallyClosing() const;
  Adesk::Boolean isTransactionResident() const;
  Adesk::Boolean isAProxy() const;
  void assertReadEnabled() const;
  void assertWriteEnabled(Adesk::Boolean autoUndo = true, Adesk::Boolean recordModified = true);
  void assertNotifyEnabled() const;
  bool isUndoRecordingDisabled() const;
  void disableUndoRecording(Adesk::Boolean disable);
  AcDbDwgFiler* undoFiler();
  virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* undoFiler, AcRxClass* classObj);
/// <summary>
/// Adds a non-persistent reactor to the currently open object
/// </summary>
/// <returns> Returns Acad::eOk if the reactor is added successfully.
///           Returns eNullObjectPointer if incoming argument is null.
///           Returns eInvalidInput if incoming argument is not a valid pointer.
///           Returns eDuplicateKey if reactor is already attached to this object.
/// </returns>
/// <remarks> Current object may be open for notify, read or write. </remarks>
///
  ACDBCORE2D_PORT Acad::ErrorStatus addReactor(AcDbObjectReactor* pReactor) const;
/// <summary>
/// Removes the non-persistent reactor from the currently open object
/// </summary>
/// <returns> Returns Acad::eOk if the reactor is removed successfully.
///           Returns eNullObjectPointer if incoming argument is null.
///           Returns eInvalidInput if incoming argument is not a valid pointer.
///           Returns eKeyNotFound if reactor is not attached to this object.
/// </returns>
/// <remarks> Current object may be open for notify, read or write. </remarks>
///
  ACDBCORE2D_PORT Acad::ErrorStatus removeReactor(AcDbObjectReactor* pReactor) const;
/// <summary>
/// Adds a persistent reactor to the currently open object
/// </summary>
/// <returns> Returns Acad::eOk if the reactor is added successfully.
///           Returns eNullObjectId if id argument is null.
///           Returns eInvalidInput if id argument does not have valid format.
///           Returns eWrongDatabase if id argument is not in same database as object.
///           Returns eSelfReference if id argument is same as this object's.
///           Returns eDuplicateKey if reactor is already attached to this object.
/// </returns>
/// <remarks> Current object must be open for write. </remarks>
///
  ACDBCORE2D_PORT Acad::ErrorStatus addPersistentReactor(AcDbObjectId objId);
/// <summary>
/// Removes the persistent reactor from the currently open object
/// </summary>
/// <returns> Returns Acad::eOk if the reactor is removed successfully.
///           Returns eNullObjectId if id argument is null.
///           Returns eInvalidInput if id argument does not have valid format.
///           Returns eWasNotifying if object is open for notify but not for write.
///           Returns eKeyNotFound if reactor id is not attached to this object.
/// </returns>
/// <remarks> Current object must be open for write. </remarks>
///
  ACDBCORE2D_PORT Acad::ErrorStatus removePersistentReactor(AcDbObjectId objId);
  ACDBCORE2D_PORT bool hasReactor(const AcDbObjectReactor* pReactor) const;
  ACDBCORE2D_PORT bool hasPersistentReactor(AcDbObjectId objId) const;
  ACDBCORE2D_PORT const AcDbVoidPtrArray* reactors() const;
  virtual void recvPropagateModify(const AcDbObject* subObj);
  virtual void xmitPropagateModify() const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus deepClone(AcDbObject* pOwnerObject, AcDbObject*& pClonedObject, AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus wblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const;
  void setAcDbObjectIdsInFlux();
  Adesk::Boolean isAcDbObjectIdsInFlux() const;
  virtual void cancelled(const AcDbObject* dbObj);
  virtual void copied(const AcDbObject* dbObj, const AcDbObject* newObj);
  virtual void erased(const AcDbObject* dbObj, Adesk::Boolean bErasing);
  virtual void goodbye(const AcDbObject* dbObj);
  virtual void openedForModify(const AcDbObject* dbObj);
  virtual void modified(const AcDbObject* dbObj);
  virtual void subObjModified(const AcDbObject* dbObj, const AcDbObject* subObj);
  virtual void modifyUndone(const AcDbObject* dbObj);
  virtual void modifiedXData(const AcDbObject* dbObj);
  virtual void unappended(const AcDbObject* dbObj);
  virtual void reappended(const AcDbObject* dbObj);
  virtual void objectClosed(const AcDbObjectId objId);
  virtual void modifiedGraphics(const AcDbEntity* dbEnt);
  virtual AcRxObject* clone() const override;
  virtual Acad::ErrorStatus copyFrom(const AcRxObject* pSrc) override;
  bool hasSaveVersionOverride();
  void setHasSaveVersionOverride(bool bSetIt);
  virtual Acad::ErrorStatus getObjectSaveVersion(const AcDbDwgFiler* pFiler, AcDb::AcDbDwgVersion& ver, AcDb::MaintenanceReleaseVersion& maintVer);
  virtual Acad::ErrorStatus getObjectSaveVersion(const AcDbDxfFiler* pFiler, AcDb::AcDbDwgVersion& ver, AcDb::MaintenanceReleaseVersion& maintVer);
  Acad::ErrorStatus getObjectBirthVersion(AcDb::AcDbDwgVersion& ver, AcDb::MaintenanceReleaseVersion& maintVer);
  virtual Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver, AcDbObject*& replaceObj, AcDbObjectId& replaceId, Adesk::Boolean& exchangeXData);
  virtual AcGiDrawable* drawable();
  virtual Adesk::Boolean isPersistent() const override;
  virtual AcDbObjectId id() const override;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getClassID(CLSID* pClsid) const;
  bool hasFields(void) const;
  Acad::ErrorStatus getField(const ACHAR* pszPropName, AcDbObjectId& fieldId) const;
  Acad::ErrorStatus getField(const ACHAR* pszPropName, AcDbField*& pField, AcDb::OpenMode mode = AcDb::kForRead) const;
  virtual Acad::ErrorStatus setField(const ACHAR* pszPropName, AcDbField* pField, AcDbObjectId& fieldId);
  virtual Acad::ErrorStatus removeField(AcDbObjectId fieldId);
  virtual Acad::ErrorStatus removeField(const ACHAR* pszPropName, AcDbObjectId& returnId);
  virtual Acad::ErrorStatus removeField(const ACHAR* pszPropName);
  AcDbObjectId getFieldDictionary(void) const;
  Acad::ErrorStatus getFieldDictionary(AcDbDictionary*& pFieldDict, AcDb::OpenMode mode = AcDb::kForRead) const;
protected:
  AcDbObject();
  virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) override;
  virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* pWd) override;
  virtual void subViewportDraw(AcGiViewportDraw* pVd) override;
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;
  virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwnerObject, AcDbObject*& pClonedObject, AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const;
  virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const;
private:
  friend class AcDbPropertiesOverrule;
  friend class AcDbObjectOverrule;
  AcDbImpObject* mpImpObject = nullptr;
  AcDbObject(const AcDbObject&) = delete;
  AcDbObject& operator =(const AcDbObject&);
};
class ADESK_NO_VTABLE AcDbXObject : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbXObject);
  virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);
  Acad::ErrorStatus dwgIn(AcDbDwgFiler* pFiler);
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
  Acad::ErrorStatus dwgOut(AcDbDwgFiler* pFiler) const;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
  Acad::ErrorStatus dxfIn(AcDbDxfFiler* pFiler);
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
  Acad::ErrorStatus dxfOut(AcDbDxfFiler* pFiler) const;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
protected:
  AcDbXObject();
};
class AcCmComplexColor : public AcDbXObject
{
public:
  ACRX_DECLARE_MEMBERS(AcCmComplexColor);
  virtual AcCmComplexColor* incReference();
  virtual void decReference();
  virtual Acad::ErrorStatus getDescription(AcString& desc) const;
  virtual Acad::ErrorStatus getDescription(ACHAR*& desc) const final;
  virtual Acad::ErrorStatus getExplanation(AcString& expl) const;
  virtual Acad::ErrorStatus getExplanation(ACHAR*& expl) const final;
  virtual AcCmEntityColor::ColorMethod colorMethod() const;
  virtual Acad::ErrorStatus setColorMethod(AcCmEntityColor::ColorMethod eColorMethod);
  virtual bool isByColor() const;
  virtual bool isByLayer() const;
  virtual bool isByBlock() const;
  virtual bool isByACI() const;
  virtual bool isByPen() const;
  virtual bool isForeground() const;
  virtual Adesk::UInt32 color() const;
  virtual Acad::ErrorStatus setColor(Adesk::UInt32 color);
  virtual Acad::ErrorStatus setRGB(Adesk::UInt8 red, Adesk::UInt8 green, Adesk::UInt8 blue);
  virtual Acad::ErrorStatus setRed(Adesk::UInt8 red);
  virtual Acad::ErrorStatus setGreen(Adesk::UInt8 green);
  virtual Acad::ErrorStatus setBlue(Adesk::UInt8 blue);
  virtual Adesk::UInt8 red() const;
  virtual Adesk::UInt8 green() const;
  virtual Adesk::UInt8 blue() const;
  virtual Adesk::UInt16 colorIndex() const;
  virtual Acad::ErrorStatus setColorIndex(Adesk::UInt16 colorIndex);
  virtual Adesk::UInt16 penIndex() const;
  virtual Acad::ErrorStatus setPenIndex(Adesk::UInt16 penIndex);
  virtual Acad::ErrorStatus copyFrom(const AcRxObject*) override;
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
  virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;
private:
  Adesk::UInt16 refCount = 0;
  AcCmEntityColor mColor;
};
inline Acad::ErrorStatus AcCmComplexColor::getDescription(ACHAR*& desc) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcCmComplexColor::getDescription, desc);
}
inline Acad::ErrorStatus AcCmComplexColor::getExplanation(ACHAR*& expl) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcCmComplexColor::getExplanation, expl);
}
class AcCmColor : public AcCmColorBase
{
public:
  AcCmColor();
  AcCmColor(const AcCmColor&);
  AcCmColor(const AcCmColorBase&);
  AcCmColor& operator=(const AcCmColor& inputColor);
  AcCmColor& operator=(const AcCmColorBase& inputColor);
  virtual ~AcCmColor();
  bool operator ==(const AcCmColor& color) const;
  bool operator !=(const AcCmColor& color) const;
  bool operator ==(const AcCmColorBase& color) const;
  bool operator !=(const AcCmColorBase& color) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getDescription(AcString& desc) const;
  Acad::ErrorStatus getDescription(ACHAR*& desc) const;
  ACDBCORE2D_PORT Acad::ErrorStatus getExplanation(AcString& expl) const;
  Acad::ErrorStatus getExplanation(ACHAR*& expl) const;
  virtual AcCmEntityColor::ColorMethod colorMethod() const override;
  virtual Acad::ErrorStatus setColorMethod(AcCmEntityColor::ColorMethod eColorMethod) override;
  virtual bool isByColor() const override;
  virtual bool isByLayer() const override;
  virtual bool isByBlock() const override;
  virtual bool isByACI() const override;
  virtual bool isByPen() const override;
  virtual bool isForeground() const override;
  bool isNone() const;
  virtual Adesk::UInt32 color() const override;
  virtual Acad::ErrorStatus setColor(Adesk::UInt32 color) override;
  virtual Acad::ErrorStatus setRGB(Adesk::UInt8 red, Adesk::UInt8 green, Adesk::UInt8 blue) override;
  virtual Acad::ErrorStatus setRed(Adesk::UInt8 red) override;
  virtual Acad::ErrorStatus setGreen(Adesk::UInt8 green) override;
  virtual Acad::ErrorStatus setBlue(Adesk::UInt8 blue) override;
  virtual Adesk::UInt8 red() const override;
  virtual Adesk::UInt8 green() const override;
  virtual Adesk::UInt8 blue() const override;
  virtual Adesk::UInt16 colorIndex() const override;
  virtual Acad::ErrorStatus setColorIndex(Adesk::UInt16 colorIndex) override;
  virtual Adesk::UInt16 penIndex() const override;
  virtual Acad::ErrorStatus setPenIndex(Adesk::UInt16 penIndex) override;
  virtual Acad::ErrorStatus setNames(const ACHAR* colorName, const ACHAR* bookName = nullptr) override;
  virtual const ACHAR* colorName(void) const override;
  virtual const ACHAR* bookName(void) const override;
  virtual const ACHAR* colorNameForDisplay(void) override;
  virtual bool hasColorName(void) const override;
  virtual bool hasBookName(void) const override;
  AcCmEntityColor entityColor(void) const;
  int dictionaryKeyLength(void) const;
  Acad::ErrorStatus getDictionaryKey(AcString& sKey) const;
  Acad::ErrorStatus getDictionaryKey(ACHAR* pKey, size_t nLen) const;
  Acad::ErrorStatus setNamesFromDictionaryKey(const ACHAR* pKey);
  Acad::ErrorStatus dwgIn(AcDbDwgFiler* pInputFiler);
  Acad::ErrorStatus dwgOut(AcDbDwgFiler* pOutputFiler) const;
  Acad::ErrorStatus dxfIn(AcDbDxfFiler* pFiler, int groupCodeOffset = 0);
  Acad::ErrorStatus dxfOut(AcDbDxfFiler* pFiler, int groupCodeOffset = 0) const;
  Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);
  Acad::ErrorStatus serializeOut(void* pBuff, int* pBuflen, AcDb::AcDbDwgVersion ver = AcDb::kDHL_CURRENT) const;
  Acad::ErrorStatus serializeIn(const void* pBuff, int* pBuflen);
  static const Adesk::UInt16 MaxColorIndex;
  Acad::ErrorStatus dwgInAsTrueColor(AcDbDwgFiler* pInputFiler);
  Acad::ErrorStatus dwgOutAsTrueColor(AcDbDwgFiler* pOutputFiler) const;
private:
  enum NameFlags
  {
    kNoNames = 0x00,
    kHasColorName = 0x01,
    kHasBookName = 0x02
  };
  static const Adesk::UInt16 ComplexColorFlag;
  AcCmEntityColor::RGBM mRGBM;
  AcString msColorName;
  AcString msBookName;
  Adesk::UInt8 mNameFlags = 0;
};
inline Acad::ErrorStatus AcCmColor::getDescription(ACHAR*& desc) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcCmColor::getDescription, desc);
}
inline Acad::ErrorStatus AcCmColor::getExplanation(ACHAR*& expl) const
{
  return ::acutGetAcStringConvertToAChar(this, &AcCmColor::getExplanation, expl);
}
class ACDBCORE2D_PORT AcCmHSB
{
public:
  AcCmHSB();
  AcCmHSB(Adesk::UInt16 hue, Adesk::UInt8 saturation, Adesk::UInt8 brightness);
  AcCmHSB(const AcCmHSB&);
  AcCmHSB& operator=(const AcCmHSB& inputColor);
  virtual ~AcCmHSB();
  bool operator ==(const AcCmHSB& color) const;
  bool operator !=(const AcCmHSB& color) const;
  virtual Adesk::UInt32 value() const;
  virtual Acad::ErrorStatus rgbToHSB(Adesk::UInt8 r, Adesk::UInt8 g, Adesk::UInt8 b);
  virtual Acad::ErrorStatus hsbToRGB(Adesk::UInt8* r, Adesk::UInt8* g, Adesk::UInt8* b);
  virtual Acad::ErrorStatus setHSB(Adesk::UInt32 value);
  virtual Acad::ErrorStatus setHSB(Adesk::UInt16 hue, Adesk::UInt8 saturation, Adesk::UInt8 brightness);
  virtual Acad::ErrorStatus setHSB(double hue, double saturation, double brightness);
  virtual Acad::ErrorStatus setHue(Adesk::UInt16 hue);
  virtual Acad::ErrorStatus setHue(double hue);
  virtual Acad::ErrorStatus setSaturation(Adesk::UInt8 saturation);
  virtual Acad::ErrorStatus setSaturation(double saturation);
  virtual Acad::ErrorStatus setBrightness(Adesk::UInt8 brightness);
  virtual Acad::ErrorStatus setBrightness(double brightness);
  virtual Adesk::UInt16 hue() const;
  virtual Adesk::UInt8 saturation() const;
  virtual Adesk::UInt8 brightness() const;
private:
  Adesk::UInt32 mHSB = 0;
};
Acad::ErrorStatus accmGetColorFromACIName(AcCmColor& clr, const ACHAR* pInput);
Acad::ErrorStatus accmGetColorFromRGBName(AcCmColor& clr, const ACHAR* pInput);
Acad::ErrorStatus ACDBCORE2D_PORT accmGetFromHSBName(AcCmHSB& hsb, const ACHAR* pInput);
Acad::ErrorStatus accmGetColorFromColorBookName(AcCmColor& clr, const ACHAR* pBookName, const ACHAR* pColorName);
void accmGetLocalizedColorNames(const ACHAR* colors[9]);
class AcDbColor : public AcDbObject
{
  ACDB_DECLARE_MEMBERS(AcDbColor);
public:
  AcDbColor();
  virtual ~AcDbColor();
  void getColor(AcCmColor& color) const;
  void setColor(const AcCmColor& color);
  const AcCmEntityColor& entityColor(void) const;
  virtual Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver, AcDbObject*& replaceObj, AcDbObjectId& replaceId, Adesk::Boolean& exchangeXData) override;
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
private:
  AcCmColor m_color;
  AcCmEntityColor m_ecol;
protected:
  virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, AcDbIdMapping& idMap, Adesk::Boolean isPrimary = true) const override;
};
class ADESK_NO_VTABLE AcDbEntity : public AcDbObject
{
  ACDB_DECLARE_MEMBERS(AcDbEntity);
public:
  virtual ~AcDbEntity();
  AcDbObjectId blockId() const;
  AcCmColor color() const;
  ACDBCORE2D_PORT virtual Acad::ErrorStatus setColor(const AcCmColor& color, bool doSubents, AcDbDatabase* pDb);
  virtual Acad::ErrorStatus setColor(const AcCmColor& color, bool doSubents = true) final;
  Adesk::UInt16 colorIndex() const;
  virtual Acad::ErrorStatus setColorIndex(Adesk::UInt16 color, Adesk::Boolean doSubents = true);
  AcCmEntityColor entityColor() const;
  AcCmTransparency transparency() const;
  virtual Acad::ErrorStatus setTransparency(const AcCmTransparency& trans, Adesk::Boolean doSubents = true);
  ACDBCORE2D_PORT Acad::ErrorStatus plotStyleName(AcString& sName) const;
  ACHAR* plotStyleName() const;
  AcDb::PlotStyleNameType getPlotStyleNameId(AcDbObjectId& id) const;
  virtual Acad::ErrorStatus setPlotStyleName(const ACHAR* newName, Adesk::Boolean doSubents = true);
  virtual Acad::ErrorStatus setPlotStyleName(AcDb::PlotStyleNameType, AcDbObjectId newId = AcDbObjectId::kNull, Adesk::Boolean doSubents = true);
  ACDBCORE2D_PORT Acad::ErrorStatus layer(AcString& sName) const;
  ACHAR* layer() const;
  AcDbObjectId layerId() const;
  virtual Acad::ErrorStatus setLayer(const ACHAR* newVal, Adesk::Boolean doSubents = true, bool allowHiddenLayer = false);
  virtual Acad::ErrorStatus setLayer(AcDbObjectId newVal, Adesk::Boolean doSubents = true, bool allowHiddenLayer = false);
  ACDBCORE2D_PORT Acad::ErrorStatus linetype(AcString& sName) const;
  ACHAR* linetype() const;
  AcDbObjectId linetypeId() const;
  virtual Acad::ErrorStatus setLinetype(const ACHAR* newVal, Adesk::Boolean doSubents = true);
  virtual Acad::ErrorStatus setLinetype(AcDbObjectId newVal, Adesk::Boolean doSubents = true);
  ACDBCORE2D_PORT Acad::ErrorStatus material(AcString& sName) const;
  ACHAR* material() const;
  AcDbObjectId materialId() const;
  virtual Acad::ErrorStatus setMaterial(const ACHAR* newVal, Adesk::Boolean doSubents = true);
  virtual Acad::ErrorStatus setMaterial(AcDbObjectId newVal, Adesk::Boolean doSubents = true);
    /// <summary>
    /// Enumerates the visual style types that can be set into an entity.
    /// </summary>
  enum VisualStyleType
  {
        /// <summary>
        /// Full visual style, defines the overall visual style of the entity.
        /// </summary>
    kFullVisualStyle,
        /// <summary>
        /// Optional face-only visual style which can vary independently of 
        /// the full visual style.
        /// </summary>
    kFaceVisualStyle,
        /// <summary>
        /// Optional edge-only visual style which can vary independently of
        /// the full visual style.
        /// </summary>
    kEdgeVisualStyle
  };
    /// <summary>
    /// Sets visual styles for the entity.  
    /// </summary>
    /// <param name="visualStyleId">
    /// Input AcDbObjectId of the AcDbVisualStyle
    /// </param>    
    /// <param name="vsType">
    /// Input VisualStyleType of the visual style type to set.
    /// </param>    
    /// <param name="doSubents">
    /// Input bool, if true applies this visual style to all sub entities.  
    /// </param>    
  virtual Acad::ErrorStatus setVisualStyle(AcDbObjectId visualStyleId, VisualStyleType vsType = kFullVisualStyle, Adesk::Boolean doSubents = true);
    /// <summary>
    /// Gets the visual styles from the entity.
    /// </summary>
    /// <param name="vsType">
    /// Input VisualStyleType of the visual style type to retrieve.
    /// </param>    
    /// <returns>
    /// AcDbObjectId of the visual style.
    /// </returns>    
  AcDbObjectId visualStyleId(VisualStyleType vsType = kFullVisualStyle) const;
  virtual Acad::ErrorStatus getMaterialMapper(AcGiMapper& mapper) const;
  virtual Acad::ErrorStatus setMaterialMapper(const AcGiMapper& mapper, Adesk::Boolean doSubents = true);
  double linetypeScale() const;
  virtual Acad::ErrorStatus setLinetypeScale(double newval, Adesk::Boolean doSubents = true);
  AcDb::Visibility visibility() const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus setVisibility(AcDb::Visibility newVal, Adesk::Boolean doSubents = true);
  AcDb::LineWeight lineWeight() const;
  virtual Acad::ErrorStatus setLineWeight(AcDb::LineWeight newVal, Adesk::Boolean doSubents = true);
  virtual AcDb::CollisionType collisionType() const;
  virtual bool castShadows() const;
  virtual void setCastShadows(bool newVal);
  virtual bool receiveShadows() const;
  virtual void setReceiveShadows(bool newVal);
  Acad::ErrorStatus setPropertiesFrom(const AcDbEntity* pEntity, Adesk::Boolean doSubents = true);
  virtual Adesk::Boolean isPlanar() const
  {
    return false;
  }
  virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const
  {
    return Acad::eNotApplicable;
  }
  virtual void getEcs(AcGeMatrix3d& retVal) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus addSubentPaths(const AcDbFullSubentPathArray& newPaths);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus deleteSubentPaths(const AcDbFullSubentPathArray& paths);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getSubentClassId(const AcDbFullSubentPath& path, CLSID* clsId) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus transformSubentPathsBy(const AcDbFullSubentPathArray& paths, const AcGeMatrix3d& xform);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getGripPointsAtSubentPath(const AcDbFullSubentPath& path, AcDbGripDataPtrArray& grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d& curViewDir, const int bitflags) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus moveGripPointsAtSubentPaths(const AcDbFullSubentPathArray& paths, const AcDbVoidPtrArray& gripAppData, const AcGeVector3d& offset, const int bitflags);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getSubentPathGeomExtents(const AcDbFullSubentPath& path, AcDbExtents& extents) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getSubentPathsAtGsMarker(AcDb::SubentType type, Adesk::GsMarker gsMark, const AcGePoint3d& pickPoint, const AcGeMatrix3d& viewXform, int& numPaths, AcDbFullSubentPath*& subentPaths, int numInserts = 0, AcDbObjectId* entAndInsertStack = nullptr) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getGsMarkersAtSubentPath(const AcDbFullSubentPath& subPath, AcArray<Adesk::GsMarker>& gsMarkers) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus highlight(const AcDbFullSubentPath& subId = kNullSubent, const Adesk::Boolean highlightAll = false) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus unhighlight(const AcDbFullSubentPath& subId = kNullSubent, const Adesk::Boolean highlightAll = false) const;
  ACDBCORE2D_PORT_VIRTUAL AcDbEntity* subentPtr(const AcDbFullSubentPath& id) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark, const AcGePoint3d& pickPoint, const AcGePoint3d& lastPoint, const AcGeMatrix3d& viewXform, AcGePoint3dArray& snapPoints, AcDbIntArray& geomIds) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark, const AcGePoint3d& pickPoint, const AcGePoint3d& lastPoint, const AcGeMatrix3d& viewXform, AcGePoint3dArray& snapPoints, AcDbIntArray& geomIds, const AcGeMatrix3d& insertionMat) const;
  ACDBCORE2D_PORT_VIRTUAL bool isContentSnappable() const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getGripPoints(AcGePoint3dArray& gripPoints, AcDbIntArray& osnapModes, AcDbIntArray& geomIds) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getGripPoints(AcDbGripDataPtrArray& grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d& curViewDir, const int bitflags) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus moveGripPointsAt(const AcDbVoidPtrArray& gripAppData, const AcGeVector3d& offset, const int bitflags);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getStretchPoints(AcGePoint3dArray& stretchPoints) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus moveStretchPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus intersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, const AcGePlane& projPlane, AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;
  Acad::ErrorStatus boundingBoxIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker, Adesk::GsMarker otherGsMarker) const;
  Acad::ErrorStatus boundingBoxIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, const AcGePlane& projPlane, AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker, Adesk::GsMarker otherGsMarker) const;
  ACDBCORE2D_PORT_VIRTUAL void list() const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getTransformedCopy(const AcGeMatrix3d& xform, AcDbEntity*& pEnt) const;
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;
  void recordGraphicsModified(Adesk::Boolean setModified = true);
  Acad::ErrorStatus draw();
  virtual void saveAs(AcGiWorldDraw* mode, AcDb::SaveType st);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getCompoundObjectTransform(AcGeMatrix3d& xMat) const;
  void setDatabaseDefaults();
  void setDatabaseDefaults(AcDbDatabase* pDb);
  virtual void subSetDatabaseDefaults(AcDbDatabase* pDb);
  virtual Acad::ErrorStatus applyPartialUndo(AcDbDwgFiler* undoFiler, AcRxClass* classObj) override;
  virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo) override;
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
  virtual AcGiDrawable* drawable() override;
  virtual bool bounds(AcDbExtents& bounds) const override;
  ACDBCORE2D_PORT_VIRTUAL Adesk::Boolean cloneMeForDragging();
  ACDBCORE2D_PORT_VIRTUAL bool hideMeForDragging() const;
  virtual void dragStatus(const AcDb::DragStat status);
  ACDBCORE2D_PORT_VIRTUAL void gripStatus(const AcDb::GripStat status);
  ACDBCORE2D_PORT_VIRTUAL void subentGripStatus(const AcDb::GripStat status, const AcDbFullSubentPath& subentity);
  ACDBCORE2D_PORT_VIRTUAL Acad::ErrorStatus getGripEntityUCS(const void* pGripAppData, AcGeVector3d& normalVec, AcGePoint3d& origin, AcGeVector3d& xAxis) const;
protected:
  AcDbEntity();
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
  virtual void subList() const;
  virtual Acad::ErrorStatus subGetOsnapPoints(AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark, const AcGePoint3d& pickPoint, const AcGePoint3d& lastPoint, const AcGeMatrix3d& viewXform, AcGePoint3dArray& snapPoints, AcDbIntArray& geomIds) const;
  virtual Acad::ErrorStatus subGetOsnapPoints(AcDb::OsnapMode osnapMode, Adesk::GsMarker gsSelectionMark, const AcGePoint3d& pickPoint, const AcGePoint3d& lastPoint, const AcGeMatrix3d& viewXform, AcGePoint3dArray& snapPoints, AcDbIntArray& geomIds, const AcGeMatrix3d& insertionMat) const;
  virtual bool subIsContentSnappable() const;
  virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);
  virtual Acad::ErrorStatus subGetTransformedCopy(const AcGeMatrix3d& xform, AcDbEntity*& pEnt) const;
  virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const;
  virtual Adesk::Boolean subCloneMeForDragging();
  virtual bool subHideMeForDragging() const;
  virtual Acad::ErrorStatus subGetGripPoints(AcGePoint3dArray& gripPoints, AcDbIntArray& osnapModes, AcDbIntArray& geomIds) const;
  virtual Acad::ErrorStatus subGetGripPoints(AcDbGripDataPtrArray& grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d& curViewDir, const int bitflags) const;
  virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset);
  virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbVoidPtrArray& gripAppData, const AcGeVector3d& offset, const int bitflags);
  virtual Acad::ErrorStatus subGetStretchPoints(AcGePoint3dArray& stretchPoints) const;
  virtual Acad::ErrorStatus subMoveStretchPointsAt(const AcDbIntArray& indices, const AcGeVector3d& offset);
  virtual Acad::ErrorStatus subGetGeomExtents(AcDbExtents& extents) const;
  virtual Acad::ErrorStatus subGetSubentClassId(const AcDbFullSubentPath& path, CLSID* clsId) const;
  virtual Acad::ErrorStatus subAddSubentPaths(const AcDbFullSubentPathArray& newPaths);
  virtual Acad::ErrorStatus subDeleteSubentPaths(const AcDbFullSubentPathArray& paths);
  virtual Acad::ErrorStatus subTransformSubentPathsBy(const AcDbFullSubentPathArray& paths, const AcGeMatrix3d& xform);
  virtual Acad::ErrorStatus subGetGripPointsAtSubentPath(const AcDbFullSubentPath& path, AcDbGripDataPtrArray& grips, const double curViewUnitSize, const int gripSize, const AcGeVector3d& curViewDir, const int bitflags) const;
  virtual Acad::ErrorStatus subMoveGripPointsAtSubentPaths(const AcDbFullSubentPathArray& paths, const AcDbVoidPtrArray& gripAppData, const AcGeVector3d& offset, const int bitflags);
  virtual Acad::ErrorStatus subGetSubentPathGeomExtents(const AcDbFullSubentPath& path, AcDbExtents& extents) const;
  virtual Acad::ErrorStatus subGetSubentPathsAtGsMarker(AcDb::SubentType type, Adesk::GsMarker gsMark, const AcGePoint3d& pickPoint, const AcGeMatrix3d& viewXform, int& numPaths, AcDbFullSubentPath*& subentPaths, int numInserts = 0, AcDbObjectId* entAndInsertStack = nullptr) const;
  virtual Acad::ErrorStatus subGetGsMarkersAtSubentPath(const AcDbFullSubentPath& subPath, AcArray<Adesk::GsMarker>& gsMarkers) const;
  virtual AcDbEntity* subSubentPtr(const AcDbFullSubentPath& id) const;
  virtual void subGripStatus(const AcDb::GripStat status);
  virtual void subSubentGripStatus(const AcDb::GripStat status, const AcDbFullSubentPath& subentity);
  virtual Acad::ErrorStatus subHighlight(const AcDbFullSubentPath& subId = kNullSubent, const Adesk::Boolean highlightAll = false) const;
  virtual Acad::ErrorStatus subUnhighlight(const AcDbFullSubentPath& subId = kNullSubent, const Adesk::Boolean highlightAll = false) const;
  ACDBCORE2D_PORT virtual AcDb::Visibility subVisibility() const;
  ACDBCORE2D_PORT virtual Acad::ErrorStatus subSetVisibility(AcDb::Visibility newVal, Adesk::Boolean doSubents = true);
  virtual Acad::ErrorStatus subIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;
  virtual Acad::ErrorStatus subIntersectWith(const AcDbEntity* pEnt, AcDb::Intersect intType, const AcGePlane& projPlane, AcGePoint3dArray& points, Adesk::GsMarker thisGsMarker = 0, Adesk::GsMarker otherGsMarker = 0) const;
  virtual Acad::ErrorStatus subGetGripEntityUCS(const void* pGripAppData, AcGeVector3d& normalVec, AcGePoint3d& origin, AcGeVector3d& xAxis) const;
  virtual Acad::ErrorStatus subGetCompoundObjectTransform(AcGeMatrix3d& xMat) const;
  friend class AcDbPropertiesOverrule;
  friend class AcDbOsnapOverrule;
  friend class AcDbTransformOverrule;
  friend class AcDbGripOverrule;
  friend class AcDbSubentityOverrule;
  friend class AcDbHighlightOverrule;
  friend class AcDbHighlightStateOverrule;
  friend class AcDbVisibilityOverrule;
  friend class AcDbGeometryOverrule;
  friend class AcDbGripEntityOverrule;
public:
  Acad::ErrorStatus pushHighlight(const AcDbFullSubentPath& subId, AcGiHighlightStyle highlightStyle);
  Acad::ErrorStatus popHighlight(const AcDbFullSubentPath& subId);
  AcGiHighlightStyle highlightState(const AcDbFullSubentPath& subId);
protected:
  ACDBCORE2D_PORT virtual Acad::ErrorStatus subPushHighlight(const AcDbFullSubentPath& subId, AcGiHighlightStyle highlightStyle);
  ACDBCORE2D_PORT virtual Acad::ErrorStatus subPopHighlight(const AcDbFullSubentPath& subId);
  ACDBCORE2D_PORT virtual AcGiHighlightStyle subHighlightState(const AcDbFullSubentPath& subId);
  AcDbEntity(const AcDbEntity&) = delete;
  AcDbEntity& operator =(const AcDbEntity&);
};
inline AcDbEntity::~AcDbEntity()
{
}
inline ACHAR* AcDbEntity::plotStyleName() const
{
  AcString sName;
  return ::acutAcStringToAChar(sName, this->plotStyleName(sName));
}
inline ACHAR* AcDbEntity::layer() const
{
  AcString sName;
  return ::acutAcStringToAChar(sName, this->layer(sName));
}
inline ACHAR* AcDbEntity::linetype() const
{
  AcString sName;
  return ::acutAcStringToAChar(sName, this->linetype(sName));
}
inline ACHAR* AcDbEntity::material() const
{
  AcString sName;
  return ::acutAcStringToAChar(sName, this->material(sName));
}
class ADESK_NO_VTABLE AcDbObjectReactor : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbObjectReactor);
  virtual void cancelled(const AcDbObject* dbObj);
  virtual void copied(const AcDbObject* dbObj, const AcDbObject* newObj);
  virtual void erased(const AcDbObject* dbObj, Adesk::Boolean bErasing);
  virtual void goodbye(const AcDbObject* dbObj);
  virtual void openedForModify(const AcDbObject* dbObj);
  virtual void modified(const AcDbObject* dbObj);
  virtual void subObjModified(const AcDbObject* dbObj, const AcDbObject* subObj);
  virtual void modifyUndone(const AcDbObject* dbObj);
  virtual void modifiedXData(const AcDbObject* dbObj);
  virtual void unappended(const AcDbObject* dbObj);
  virtual void reappended(const AcDbObject* dbObj);
  virtual void objectClosed(const AcDbObjectId objId);
protected:
  AcDbObjectReactor();
};
class ADESK_NO_VTABLE AcDbEntityReactor : public AcDbObjectReactor
{
public:
  ACRX_DECLARE_MEMBERS(AcDbEntityReactor);
  virtual void modifiedGraphics(const AcDbEntity* dbObj);
  virtual void dragCloneToBeDeleted(const AcDbEntity* pOriginalObj, const AcDbEntity* pClone);
protected:
  AcDbEntityReactor();
};
class ADESK_NO_VTABLE AcDbDatabaseReactor : public AcRxObject
{
public:
  ACRX_DECLARE_MEMBERS(AcDbDatabaseReactor);
  virtual void objectAppended(const AcDbDatabase* dwg, const AcDbObject* dbObj);
  virtual void objectUnAppended(const AcDbDatabase* dwg, const AcDbObject* dbObj);
  virtual void objectReAppended(const AcDbDatabase* dwg, const AcDbObject* dbObj);
  virtual void objectOpenedForModify(const AcDbDatabase* dwg, const AcDbObject* dbObj);
  virtual void objectModified(const AcDbDatabase* dwg, const AcDbObject* dbObj);
  virtual void objectErased(const AcDbDatabase* dwg, const AcDbObject* dbObj, Adesk::Boolean bErased);
  virtual void headerSysVarWillChange(const AcDbDatabase* dwg, const ACHAR* name);
  virtual void headerSysVarChanged(const AcDbDatabase* dwg, const ACHAR* name, Adesk::Boolean bSuccess);
  virtual void proxyResurrectionCompleted(const AcDbDatabase* dwg, const ACHAR* appname, AcDbObjectIdArray& objects);
  virtual void goodbye(const AcDbDatabase* dwg);
};
class AcDbExtents2d : public AcHeapOperators
{
public:
  AcDbExtents2d();
  AcDbExtents2d(const AcDbExtents2d& src);
  AcDbExtents2d(const AcGePoint2d& min, const AcGePoint2d& max);
  AcGePoint2d minPoint() const
  {
    return mMinPoint;
  }
  AcGePoint2d maxPoint() const
  {
    return mMaxPoint;
  }
  Acad::ErrorStatus set(const AcGePoint2d& min, const AcGePoint2d& max);
  void addPoint(const AcGePoint2d& pt);
  void addExt(const AcDbExtents2d& src);
  void expandBy(const AcGeVector2d& vec);
  void transformBy(const AcGeMatrix2d& mat);
  bool operator==(const AcDbExtents2d& other);
private:
  AcGePoint2d mMinPoint;
  AcGePoint2d mMaxPoint;
};
class AcDbExtents : public AcHeapOperators
{
public:
  AcDbExtents();
  AcDbExtents(const AcDbExtents& src);
  AcDbExtents(const AcGePoint3d& min, const AcGePoint3d& max);
  AcGePoint3d minPoint() const
  {
    return mMinPoint;
  }
  AcGePoint3d maxPoint() const
  {
    return mMaxPoint;
  }
  Acad::ErrorStatus set(const AcGePoint3d& min, const AcGePoint3d& max);
  void addPoint(const AcGePoint3d& pt);
  void addExt(const AcDbExtents& src);
  Acad::ErrorStatus addBlockExt(AcDbBlockTableRecord* pBTR);
  void expandBy(const AcGeVector3d& vec);
  void transformBy(const AcGeMatrix3d& mat);
  bool operator==(const AcDbExtents& other);
private:
  AcGePoint3d mMinPoint;
  AcGePoint3d mMaxPoint;
};
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbBlockTable>() const
{
  return this->blockTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbLayerTable>() const
{
  return this->layerTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbTextStyleTable>() const
{
  return this->textStyleTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbLinetypeTable>() const
{
  return this->linetypeTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbViewTable>() const
{
  return this->viewTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbUCSTable>() const
{
  return this->UCSTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbViewportTable>() const
{
  return this->viewportTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbRegAppTable>() const
{
  return this->regAppTableId();
}
template <>
inline AcDbObjectId AcDbDatabase::getSymbolTableId<AcDbDimStyleTable>() const
{
  return this->dimStyleTableId();
}
inline Acad::ErrorStatus AcDbDatabase::getBlockTable(AcDbBlockTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getLayerTable(AcDbLayerTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getTextStyleTable(AcDbTextStyleTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getLinetypeTable(AcDbLinetypeTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getViewTable(AcDbViewTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getUCSTable(AcDbUCSTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getViewportTable(AcDbViewportTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getRegAppTable(AcDbRegAppTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
inline Acad::ErrorStatus AcDbDatabase::getDimStyleTable(AcDbDimStyleTable*& pTable, AcDb::OpenMode mode)
{
  return getSymbolTable(pTable, mode);
}
/////////////////////////////////////////////////////////////////////////
#  define AC_SRCH_BLOCK	0x01
#  define AC_SRCH_DIM_TEXT	0x02
#  define AC_SRCH_TEXT	0x04
#  define AC_SRCH_LINK_DESC	0x08
#  define AC_SRCH_LINK_URL	0x10
#  define AC_SRCH_MATCH_CASE	0x20
#  define AC_SRCH_WHOLE_WORD	0x40
#  define AC_SRCH_DEFAULT	0x1F
bool acdbTextFind(AcDbDatabase* pDatabase, AcDbObjectIdArray& resultSet, const ACHAR* findString, const ACHAR* replaceString = nullptr, Adesk::UInt8 searchOptions = AC_SRCH_DEFAULT, const AcDbObjectIdArray& selSet = 0);
#  pragma  pack(pop)
#endif
