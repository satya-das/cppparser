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
// acdbabb.h: Abbreviations for definitions in acdb.h
// 2/21/94: Up to date with respect to acdb.h


#ifdef AD_ACDBABBES_H
// This file should only be included by .cpp files.  If it's
// included twice, we assume it's because it is being included
// by .h file(s), and so we complain.
#error "acdbabbES.h included more than once!  Is it included by a .h file?"
#endif

#define AD_ACDBABBES_H 1

#include "acadstrc.h"   // Acad struct
#include "acdb.h"       // AcDb struct

typedef Acad::ErrorStatus       ErrorStatus;

typedef AcDb::OpenMode          OpenMode;
typedef AcDb::OsnapMode         OsnapMode;
typedef AcDb::CoordAxis         CoordAxis;
typedef AcDb::CoordSystem       CoordSystem;
typedef AcDb::Intersect         Intersect;
typedef AcDb::Visibility        Visibility;
typedef AcDb::SaveType          SaveType;
typedef AcDb::DxfCode           DxfCode;
typedef AcDb::DwgDataType       DwgDataType;
typedef AcDb::TextHorzMode      TextHorzMode;
typedef AcDb::TextVertMode      TextVertMode;
typedef AcDb::LineSpacingStyle  LineSpacingStyle;
typedef AcDb::Planarity         Planarity;
typedef AcDb::PointIndex        PointIndex;
typedef AcDb::EdgeIndex         EdgeIndex;
typedef AcDb::Poly2dType        Poly2dType;
typedef AcDb::Poly3dType        Poly3dType;
typedef AcDb::PolyMeshType      PolyMeshType;
typedef AcDb::Vertex2dType      Vertex2dType;
typedef AcDb::Vertex3dType      Vertex3dType;
typedef AcDb::SpaceValueType    SpaceValueType;
typedef AcDb::BoolOperType      BoolOperType;
typedef AcDb::SubentType        SubentType;
typedef AcDb::GeomId            GeomId;
typedef AcDb::GeomType          GeomType;
typedef AcDb::OrthographicView  OrthographicView;

// Acad::ErrorStatus

const Acad::ErrorStatus eOk = Acad::eOk;
const Acad::ErrorStatus eNotImplementedYet = Acad::eNotImplementedYet;
const Acad::ErrorStatus eNotApplicable = Acad::eNotApplicable;
const Acad::ErrorStatus eInvalidInput = Acad::eInvalidInput;
const Acad::ErrorStatus eAmbiguousInput = Acad::eAmbiguousInput;
const Acad::ErrorStatus eAmbiguousOutput = Acad::eAmbiguousOutput;
const Acad::ErrorStatus eOutOfMemory = Acad::eOutOfMemory;
const Acad::ErrorStatus eBufferTooSmall = Acad::eBufferTooSmall;
const Acad::ErrorStatus eInvalidOpenState = Acad::eInvalidOpenState;
const Acad::ErrorStatus eEntityInInactiveLayout
    = Acad::eEntityInInactiveLayout;
const Acad::ErrorStatus eHandleExists = Acad::eHandleExists;
const Acad::ErrorStatus eNullHandle = Acad::eNullHandle;
const Acad::ErrorStatus eBrokenHandle = Acad::eBrokenHandle;
const Acad::ErrorStatus eUnknownHandle = Acad::eUnknownHandle;
const Acad::ErrorStatus eHandleInUse = Acad::eHandleInUse;
const Acad::ErrorStatus eNullObjectPointer = Acad::eNullObjectPointer;
const Acad::ErrorStatus eNullObjectId = Acad::eNullObjectId;
const Acad::ErrorStatus eNullBlockName = Acad::eNullBlockName;
const Acad::ErrorStatus eContainerNotEmpty = Acad::eContainerNotEmpty;
const Acad::ErrorStatus eNullEntityPointer = Acad::eNullEntityPointer;
const Acad::ErrorStatus eIllegalEntityType = Acad::eIllegalEntityType;
const Acad::ErrorStatus eKeyNotFound = Acad::eKeyNotFound;
const Acad::ErrorStatus eDuplicateKey = Acad::eDuplicateKey;
const Acad::ErrorStatus eInvalidIndex = Acad::eInvalidIndex;
const Acad::ErrorStatus eDuplicateIndex = Acad::eDuplicateIndex;
const Acad::ErrorStatus eAlreadyInDb = Acad::eAlreadyInDb;
const Acad::ErrorStatus eOutOfDisk = Acad::eOutOfDisk;
const Acad::ErrorStatus eDeletedEntry = Acad::eDeletedEntry;
const Acad::ErrorStatus eNegativeValueNotAllowed 
    = Acad::eNegativeValueNotAllowed;
const Acad::ErrorStatus eInvalidExtents = Acad::eInvalidExtents;
const Acad::ErrorStatus eInvalidAdsName = Acad::eInvalidAdsName;
const Acad::ErrorStatus eInvalidKey = Acad::eInvalidKey;
const Acad::ErrorStatus eEndOfObject = Acad::eEndOfObject;
const Acad::ErrorStatus eEndOfFile = Acad::eEndOfFile;
const Acad::ErrorStatus eObjectToBeDeleted = Acad::eObjectToBeDeleted;
const Acad::ErrorStatus eInvalidDwgVersion = Acad::eInvalidDwgVersion;
const Acad::ErrorStatus eAnonymousEntry = Acad::eAnonymousEntry;
const Acad::ErrorStatus eIllegalReplacement = Acad::eIllegalReplacement;
const Acad::ErrorStatus eIsReading = Acad::eIsReading;
const Acad::ErrorStatus eIsWriting = Acad::eIsWriting;
const Acad::ErrorStatus eNotOpenForRead = Acad::eNotOpenForRead;
const Acad::ErrorStatus eNotOpenForWrite = Acad::eNotOpenForWrite;
const Acad::ErrorStatus eNotThatKindOfClass = Acad::eNotThatKindOfClass;
const Acad::ErrorStatus eInvalidDxfCode = Acad::eInvalidDxfCode;
const Acad::ErrorStatus eInvalidResBuf = Acad::eInvalidResBuf;
const Acad::ErrorStatus eBadDxfSequence = Acad::eBadDxfSequence;
const Acad::ErrorStatus eInvalidBlockName = Acad::eInvalidBlockName;
const Acad::ErrorStatus eMissingDxfField  = Acad::eMissingDxfField;
const Acad::ErrorStatus eDuplicateDxfField = Acad::eDuplicateDxfField;
const Acad::ErrorStatus eFilerError = Acad::eFilerError;
const Acad::ErrorStatus eVertexAfterFace = Acad::eVertexAfterFace;
const Acad::ErrorStatus eInvalidFaceVertexIndex = Acad::eInvalidFaceVertexIndex;
const Acad::ErrorStatus eInvalidMeshVertexIndex = Acad::eInvalidMeshVertexIndex;
const Acad::ErrorStatus eOtherObjectsBusy = Acad::eOtherObjectsBusy;
const Acad::ErrorStatus eMustFirstAddBlockToDb = Acad::eMustFirstAddBlockToDb;
const Acad::ErrorStatus eCannotNestBlockDefs = Acad::eCannotNestBlockDefs;
const Acad::ErrorStatus eDwgRecoveredOK = Acad::eDwgRecoveredOK;
const Acad::ErrorStatus eDwgNotRecoverable = Acad::eDwgNotRecoverable;
const Acad::ErrorStatus eDwgNeedsRecovery = Acad::eDwgNeedsRecovery;
const Acad::ErrorStatus eDeleteEntity = Acad::eDeleteEntity;
const Acad::ErrorStatus eInvalidFix = Acad::eInvalidFix;
const Acad::ErrorStatus eFSMError = Acad::eFSMError;
const Acad::ErrorStatus eDxfPartiallyRead = Acad::eDxfPartiallyRead;
const Acad::ErrorStatus eMissingSymbolTable = Acad::eMissingSymbolTable;
const Acad::ErrorStatus eMissingSymbolTableRec = Acad::eMissingSymbolTableRec;
const Acad::ErrorStatus eDwgCRCDoesNotMatch = Acad::eDwgCRCDoesNotMatch;
const Acad::ErrorStatus eDwgSentinelDoesNotMatch 
    = Acad::eDwgSentinelDoesNotMatch;
const Acad::ErrorStatus eDwgObjectImproperlyRead 
    = Acad::eDwgObjectImproperlyRead;
const Acad::ErrorStatus eNoInputFiler = Acad::eNoInputFiler;
const Acad::ErrorStatus eDwgNeedsAFullSave = Acad::eDwgNeedsAFullSave;
const Acad::ErrorStatus eDxfReadAborted = Acad::eDxfReadAborted;
const Acad::ErrorStatus eDxbPartiallyRead = Acad::eDxbPartiallyRead;
const Acad::ErrorStatus eDxbReadAborted = Acad::eDxbReadAborted;
const Acad::ErrorStatus eFileLockedByACAD = Acad::eFileLockedByACAD;
const Acad::ErrorStatus eFileAccessErr = Acad::eFileAccessErr;
const Acad::ErrorStatus eFileSystemErr = Acad::eFileSystemErr;
const Acad::ErrorStatus eFileInternalErr = Acad::eFileInternalErr;
const Acad::ErrorStatus eFileNotFound = Acad::eFileNotFound;
const Acad::ErrorStatus eDwgShareDemandLoad = Acad::eDwgShareDemandLoad;
const Acad::ErrorStatus eDwgShareReadAccess = Acad::eDwgShareReadAccess;
const Acad::ErrorStatus eDwgShareWriteAccess = Acad::eDwgShareWriteAccess;
const Acad::ErrorStatus eDwkLockFileFound = Acad::eDwkLockFileFound;
const Acad::ErrorStatus eWasErased = Acad::eWasErased;
const Acad::ErrorStatus eWasNotErased = Acad::eWasNotErased;
const Acad::ErrorStatus ePermanentlyErased = Acad::ePermanentlyErased;
const Acad::ErrorStatus eWasOpenForRead = Acad::eWasOpenForRead;
const Acad::ErrorStatus eWasOpenForWrite = Acad::eWasOpenForWrite;
const Acad::ErrorStatus eWasOpenForUndo = Acad::eWasOpenForUndo;
const Acad::ErrorStatus eWasNotifying = Acad::eWasNotifying;
const Acad::ErrorStatus eWasOpenForNotify = Acad::eWasOpenForNotify;
const Acad::ErrorStatus eOnLockedLayer = Acad::eOnLockedLayer;
const Acad::ErrorStatus eMustOpenThruOwner = Acad::eMustOpenThruOwner;
const Acad::ErrorStatus eSubentitiesStillOpen = Acad::eSubentitiesStillOpen;
const Acad::ErrorStatus eAtMaxReaders = Acad::eAtMaxReaders;
const Acad::ErrorStatus eIsWriteProtected = Acad::eIsWriteProtected;
const Acad::ErrorStatus eIsXRefObject = Acad::eIsXRefObject;
const Acad::ErrorStatus eNotAnEntity = Acad::eNotAnEntity;
const Acad::ErrorStatus eHadMultipleReaders = Acad::eHadMultipleReaders;
const Acad::ErrorStatus eWasNotOpenForWrite = Acad::eWasNotOpenForWrite;
const Acad::ErrorStatus eCloseWasNotifying = Acad::eCloseWasNotifying;
const Acad::ErrorStatus eCloseModifyAborted = Acad::eCloseModifyAborted;
const Acad::ErrorStatus eClosePartialFailure = Acad::eClosePartialFailure;
const Acad::ErrorStatus eCannotBeErasedByCaller = Acad::eCannotBeErasedByCaller;
const Acad::ErrorStatus eFixedAllErrors = Acad::eFixedAllErrors;
const Acad::ErrorStatus eLeftErrorsUnfixed = Acad::eLeftErrorsUnfixed;
const Acad::ErrorStatus eUnrecoverableErrors = Acad::eUnrecoverableErrors;
const Acad::ErrorStatus eNoDatabase = Acad::eNoDatabase;
const Acad::ErrorStatus eXdataSizeExceeded = Acad::eXdataSizeExceeded;
const Acad::ErrorStatus eRegappIdNotFound = Acad::eRegappIdNotFound;
const Acad::ErrorStatus eRepeatEntity = Acad::eRepeatEntity;
const Acad::ErrorStatus eRecordNotInTable = Acad::eRecordNotInTable;
const Acad::ErrorStatus eIteratorDone = Acad::eIteratorDone;
const Acad::ErrorStatus eNotInBlock = Acad::eNotInBlock;
const Acad::ErrorStatus eGeneralModelingFailure = Acad::eGeneralModelingFailure;
const Acad::ErrorStatus eOutOfRange = Acad::eOutOfRange;
const Acad::ErrorStatus eNonCoplanarGeometry = Acad::eNonCoplanarGeometry;
const Acad::ErrorStatus eDegenerateGeometry  = Acad::eDegenerateGeometry;
const Acad::ErrorStatus eOwnerNotInDatabase = Acad::eOwnerNotInDatabase;
const Acad::ErrorStatus eOwnerNotOpenForRead = Acad::eOwnerNotOpenForRead;
const Acad::ErrorStatus eOwnerNotOpenForWrite = Acad::eOwnerNotOpenForWrite;
const Acad::ErrorStatus eExplodeBeforeTransform = Acad::eExplodeBeforeTransform;
const Acad::ErrorStatus eCannotScaleNonUniformly 
    = Acad::eCannotScaleNonUniformly;
const Acad::ErrorStatus eNotInDatabase = Acad::eNotInDatabase;
const Acad::ErrorStatus eNotCurrentDatabase = Acad::eNotCurrentDatabase;
const Acad::ErrorStatus eIsAnEntity = Acad::eIsAnEntity;
const Acad::ErrorStatus eCannotChangeActiveViewport 
    = Acad::eCannotChangeActiveViewport;
const Acad::ErrorStatus eNotInPaperspace = Acad::eNotInPaperspace;
const Acad::ErrorStatus eCommandWasInProgress = Acad::eCommandWasInProgress;
const Acad::ErrorStatus eInvalidAxis  = Acad::eInvalidAxis;
const Acad::ErrorStatus ePointNotOnEntity  = Acad::ePointNotOnEntity;
const Acad::ErrorStatus eSingularPoint  = Acad::eSingularPoint;
const Acad::ErrorStatus eInvalidOffset = Acad::eInvalidOffset;
const Acad::ErrorStatus eStringTooLong  = Acad::eStringTooLong;
const Acad::ErrorStatus eNullIterator = Acad::eNullIterator;
const Acad::ErrorStatus eInvalidSymbolTableName = Acad::eInvalidSymbolTableName;
const Acad::ErrorStatus eDuplicateRecordName = Acad::eDuplicateRecordName;
const Acad::ErrorStatus eXRefDependent = Acad::eXRefDependent;
const Acad::ErrorStatus eSelfReference = Acad::eSelfReference;
const Acad::ErrorStatus eWrongDatabase = Acad::eWrongDatabase;
const Acad::ErrorStatus eWrongObjectType = Acad::eWrongObjectType;
const Acad::ErrorStatus eInvalidSymTableFlag = Acad::eInvalidSymTableFlag;
const Acad::ErrorStatus eUndefinedLineType = Acad::eUndefinedLineType;
const Acad::ErrorStatus eInvalidTextStyle = Acad::eInvalidTextStyle;
const Acad::ErrorStatus eTooFewLineTypeElements = Acad::eTooFewLineTypeElements;
const Acad::ErrorStatus eTooManyLineTypeElements 
    = Acad::eTooManyLineTypeElements;
const Acad::ErrorStatus eExcessiveItemCount = Acad::eExcessiveItemCount;
const Acad::ErrorStatus eIgnoredLinetypeRedef = Acad::eIgnoredLinetypeRedef;
const Acad::ErrorStatus eBadUCS = Acad::eBadUCS;
const Acad::ErrorStatus eBadPaperspaceView = Acad::eBadPaperspaceView;
const Acad::ErrorStatus eSomeInputDataLeftUnread=Acad::eSomeInputDataLeftUnread;
const Acad::ErrorStatus eNoInternalSpace=Acad::eNoInternalSpace;
const Acad::ErrorStatus eInvalidDimStyle = Acad::eInvalidDimStyle;
const Acad::ErrorStatus eInvalidLayer = Acad::eInvalidLayer;
const Acad::ErrorStatus eUserBreak = Acad::eUserBreak;
const Acad::ErrorStatus eBadLayerName = Acad::eBadLayerName;
const Acad::ErrorStatus eLayerGroupCodeMissing = Acad::eLayerGroupCodeMissing;
const Acad::ErrorStatus eBadColorIndex = Acad::eBadColorIndex;
const Acad::ErrorStatus eBadColor = Acad::eBadColor;
const Acad::ErrorStatus eBadLinetypeName = Acad::eBadLinetypeName;
const Acad::ErrorStatus eBadLinetypeScale = Acad::eBadLinetypeScale;
const Acad::ErrorStatus eBadVisibilityValue = Acad::eBadVisibilityValue;
const Acad::ErrorStatus eProperClassSeparatorExpected 
    = Acad::eProperClassSeparatorExpected;
const Acad::ErrorStatus eBadMaterialName = Acad::eBadMaterialName;
const Acad::ErrorStatus ePagerError = Acad::ePagerError;
const Acad::ErrorStatus eOutOfPagerMemory = Acad::eOutOfPagerMemory;
const Acad::ErrorStatus ePagerWriteError = Acad::ePagerWriteError;
const Acad::ErrorStatus eWasNotForwarding = Acad::eWasNotForwarding;
const Acad::ErrorStatus eInvalidIdMap = Acad::eInvalidIdMap;
const Acad::ErrorStatus eInvalidOwnerObject = Acad::eInvalidOwnerObject;
const Acad::ErrorStatus eOwnerNotSet = Acad::eOwnerNotSet;
const Acad::ErrorStatus eNoActiveTransactions = Acad::eNoActiveTransactions; 
const Acad::ErrorStatus eNotTopTransaction = Acad::eNotTopTransaction; 
const Acad::ErrorStatus eTransactionOpenWhileCommandEnded 
    = Acad::eTransactionOpenWhileCommandEnded;
const Acad::ErrorStatus eInProcessOfCommitting 
    = Acad::eInProcessOfCommitting;
const Acad::ErrorStatus eNotNewlyCreated = Acad::eNotNewlyCreated;
const Acad::ErrorStatus eLongTransReferenceError 
    = Acad::eLongTransReferenceError;
const Acad::ErrorStatus eNoWorkSet = Acad::eNoWorkSet;
const Acad::ErrorStatus eAlreadyInGroup = Acad::eAlreadyInGroup;
const Acad::ErrorStatus eNotInGroup = Acad::eNotInGroup;
const Acad::ErrorStatus eWrongSubentityType = Acad::eWrongSubentityType;
const Acad::ErrorStatus eInvalidStyle = Acad::eInvalidStyle;
const Acad::ErrorStatus eCannotRestoreFromAcisFile 
    = Acad::eCannotRestoreFromAcisFile;
const Acad::ErrorStatus eNonPlanarEntity = Acad::eNonPlanarEntity;
const Acad::ErrorStatus eCannotExplodeEntity = Acad::eCannotExplodeEntity;
const Acad::ErrorStatus ePolyWidthLost = Acad::ePolyWidthLost;
const Acad::ErrorStatus eNullExtents = Acad::eNullExtents;

const Acad::ErrorStatus eLockViolation = Acad::eLockViolation;
const Acad::ErrorStatus eLockConflict = Acad::eLockConflict;
const Acad::ErrorStatus eDatabaseObjectsOpen = Acad::eDatabaseObjectsOpen;
const Acad::ErrorStatus eLockChangeInProgress = Acad::eLockChangeInProgress;

const Acad::ErrorStatus eVetoed = Acad::eVetoed;
const Acad::ErrorStatus eXrefReloaded = Acad::eXrefReloaded;
const Acad::ErrorStatus eXrefReloadImpossibleAtThisTime = Acad::eXrefReloadImpossibleAtThisTime;

const Acad::ErrorStatus eNoDocument = Acad::eNoDocument;
const Acad::ErrorStatus eNotFromThisDocument = Acad::eNotFromThisDocument;
const Acad::ErrorStatus eLISPActive = Acad::eLISPActive;
const Acad::ErrorStatus eTargetDocNotQuiescent = Acad::eTargetDocNotQuiescent;
const Acad::ErrorStatus eDocumentSwitchDisabled = Acad::eDocumentSwitchDisabled;
const Acad::ErrorStatus eInvalidContext = Acad::eInvalidContext;

const Acad::ErrorStatus eProfileDoesNotExist = Acad::eProfileDoesNotExist;
const Acad::ErrorStatus eInvalidFileExtension= Acad::eInvalidFileExtension;
const Acad::ErrorStatus eInvalidProfileName  = Acad::eInvalidProfileName;
const Acad::ErrorStatus eFileExists          = Acad::eFileExists;     
const Acad::ErrorStatus eProfileIsInUse      = Acad::eProfileIsInUse;
const Acad::ErrorStatus eCantOpenFile        = Acad::eCantOpenFile;
const Acad::ErrorStatus eNoFileName          = Acad::eNoFileName;
const Acad::ErrorStatus eRegistryAccessError = Acad::eRegistryAccessError;
const Acad::ErrorStatus eRegistryCreateError = Acad::eRegistryCreateError;

const Acad::ErrorStatus eBadDxfFile = Acad::eBadDxfFile;
const Acad::ErrorStatus eUnknownDxfFileFormat = Acad::eUnknownDxfFileFormat;
const Acad::ErrorStatus eMissingDxfSection = Acad::eMissingDxfSection;
const Acad::ErrorStatus eInvalidDxfSectionName = Acad::eInvalidDxfSectionName;
const Acad::ErrorStatus eNotDxfHeaderGroupCode = Acad::eNotDxfHeaderGroupCode;
const Acad::ErrorStatus eUndefinedDxfGroupCode = Acad::eUndefinedDxfGroupCode;
const Acad::ErrorStatus eNotInitializedYet = Acad::eNotInitializedYet;
const Acad::ErrorStatus eInvalidDxf2dPoint = Acad::eInvalidDxf2dPoint;
const Acad::ErrorStatus eInvalidDxf3dPoint = Acad::eInvalidDxf3dPoint;
const Acad::ErrorStatus eBadlyNestedAppData  = Acad::eBadlyNestedAppData;
const Acad::ErrorStatus eIncompleteBlockDefinition = Acad::eIncompleteBlockDefinition;
const Acad::ErrorStatus eIncompleteComplexObject = Acad::eIncompleteComplexObject;
const Acad::ErrorStatus eBlockDefInEntitySection = Acad::eBlockDefInEntitySection;
const Acad::ErrorStatus eNoBlockBegin = Acad::eNoBlockBegin;
const Acad::ErrorStatus eDuplicateLayerName = Acad::eDuplicateLayerName;
const Acad::ErrorStatus eDuplicateBlockName = Acad::eDuplicateBlockName;
const Acad::ErrorStatus eBadPlotStyleName = Acad::eBadPlotStyleName;
const Acad::ErrorStatus eBadPlotStyleType = Acad::eBadPlotStyleType;
const Acad::ErrorStatus eBadPlotStyleNameHandle = Acad::eBadPlotStyleNameHandle;
const Acad::ErrorStatus eUndefineShapeName = Acad::eUndefineShapeName;
const Acad::ErrorStatus eDuplicateBlockDefinition = Acad::eDuplicateBlockDefinition;
const Acad::ErrorStatus eMissingBlockName = Acad::eMissingBlockName;
const Acad::ErrorStatus eBinaryDataSizeExceeded = Acad::eBinaryDataSizeExceeded;
const Acad::ErrorStatus eHatchTooDense = Acad::eHatchTooDense;


const Acad::ErrorStatus eUndoOperationNotAvailable = Acad::eUndoOperationNotAvailable;
const Acad::ErrorStatus eUndoNoGroupBegin = Acad::eUndoNoGroupBegin;

const Acad::ErrorStatus eObjectIsReferenced = Acad::eObjectIsReferenced;
const Acad::ErrorStatus eNoThumbnailBitmap = Acad::eNoThumbnailBitmap;
const Acad::ErrorStatus eGuidNoAddress = Acad::eGuidNoAddress;
const Acad::ErrorStatus eNoPlotStyleTranslationTable = Acad::eNoPlotStyleTranslationTable;

const Acad::ErrorStatus ePlotStyleInColorDependentMode = Acad::ePlotStyleInColorDependentMode;
const Acad::ErrorStatus eNoClassId = Acad::eNoClassId;
const Acad::ErrorStatus eMaxLayouts = Acad::eMaxLayouts;

const Acad::ErrorStatus eWrongCellType = Acad::eWrongCellType;
const Acad::ErrorStatus eCannotChangeColumnType = Acad::eCannotChangeColumnType;
const Acad::ErrorStatus eRowsMustMatchColumns = Acad::eRowsMustMatchColumns;

const Acad::ErrorStatus eNullNodeId = Acad::eNullNodeId;
const Acad::ErrorStatus eNoNodeActive = Acad::eNoNodeActive;
const Acad::ErrorStatus eGraphContainsProxies = Acad::eGraphContainsProxies;

const Acad::ErrorStatus eLoadFailed = Acad::eLoadFailed;
const Acad::ErrorStatus eDeviceNotFound = Acad::eDeviceNotFound;
const Acad::ErrorStatus eNoCurrentConfig = Acad::eNoCurrentConfig;
const Acad::ErrorStatus eNullPtr = Acad::eNullPtr;
const Acad::ErrorStatus eNoLayout = Acad::eNoLayout;
const Acad::ErrorStatus eIncompatiblePlotSettings = Acad::eIncompatiblePlotSettings;
const Acad::ErrorStatus eNonePlotDevice = Acad::eNonePlotDevice;
const Acad::ErrorStatus eNoMatchingMedia = Acad::eNoMatchingMedia;
const Acad::ErrorStatus eInvalidView = Acad::eInvalidView;
const Acad::ErrorStatus eInvalidWindowArea = Acad::eInvalidWindowArea;
const Acad::ErrorStatus eInvalidPlotArea = Acad::eInvalidPlotArea;
const Acad::ErrorStatus eCustomSizeNotPossible = Acad::eCustomSizeNotPossible;

const Acad::ErrorStatus ePageCancelled = Acad::ePageCancelled;
const Acad::ErrorStatus ePlotCancelled = Acad::ePlotCancelled;
const Acad::ErrorStatus eInvalidEngineState = Acad::eInvalidEngineState;
const Acad::ErrorStatus ePlotAlreadyStarted = Acad::ePlotAlreadyStarted;
const Acad::ErrorStatus eNoErrorHandler = Acad::eNoErrorHandler;
const Acad::ErrorStatus eInvalidPlotInfo = Acad::eInvalidPlotInfo;
const Acad::ErrorStatus eNumberOfCopiesNotSupported = Acad::eNumberOfCopiesNotSupported;
const Acad::ErrorStatus eLayoutNotCurrent = Acad::eLayoutNotCurrent;
const Acad::ErrorStatus eGraphicsNotGenerated = Acad::eGraphicsNotGenerated;
const Acad::ErrorStatus eCannotPlotToFile = Acad::eCannotPlotToFile;
const Acad::ErrorStatus eMustPlotToFile = Acad::eMustPlotToFile;
const Acad::ErrorStatus eBackgroundPlotInProgress = Acad::eBackgroundPlotInProgress;

const Acad::ErrorStatus eInvalidObjectId = Acad::eInvalidObjectId;
const Acad::ErrorStatus eInvalidXrefObjectId = Acad::eInvalidXrefObjectId;
const Acad::ErrorStatus eNoViewAssociation = Acad::eNoViewAssociation;
const Acad::ErrorStatus eNoLabelBlock = Acad::eNoLabelBlock;
const Acad::ErrorStatus eUnableToSetViewAssociation = Acad::eUnableToSetViewAssociation;
const Acad::ErrorStatus eUnableToGetViewAssociation = Acad::eUnableToGetViewAssociation;
const Acad::ErrorStatus eUnableToSetLabelBlock = Acad::eUnableToSetLabelBlock;
const Acad::ErrorStatus eUnableToGetLabelBlock = Acad::eUnableToGetLabelBlock;
const Acad::ErrorStatus eUnableToRemoveAssociation = Acad::eUnableToRemoveAssociation;
const Acad::ErrorStatus eUnableToSyncModelView = Acad::eUnableToSyncModelView;

const Acad::ErrorStatus eSubSelectionSetEmpty = Acad::eSubSelectionSetEmpty;
const Acad::ErrorStatus eGraphEdgeNotFound = Acad::eGraphEdgeNotFound;
const Acad::ErrorStatus eGraphNodeNotFound = Acad::eGraphNodeNotFound;
const Acad::ErrorStatus eGraphNodeAlreadyExists = Acad::eGraphNodeAlreadyExists;
const Acad::ErrorStatus eGraphEdgeAlreadyExists = Acad::eGraphEdgeAlreadyExists;
const Acad::ErrorStatus eGraphCyclesFound = Acad::eGraphCyclesFound;

const Acad::ErrorStatus eAlreadyHasRepresentation = 
                                        Acad::eAlreadyHasRepresentation;
const Acad::ErrorStatus eNoRepresentation = Acad::eNoRepresentation;
const Acad::ErrorStatus eNoIntersections = Acad::eNoIntersections;
const Acad::ErrorStatus eEmbeddedIntersections = Acad::eEmbeddedIntersections;

// solid chamfer/fillet
const Acad::ErrorStatus eFailedToSetEdgeChamfers = Acad::eFailedToSetEdgeChamfers;
const Acad::ErrorStatus eNoConnectedBlendSet = Acad::eNoConnectedBlendSet;
const Acad::ErrorStatus eFailedToBlend = Acad::eFailedToBlend;
const Acad::ErrorStatus eFailedToSetEdgeRounds = Acad::eFailedToSetEdgeRounds;
const Acad::ErrorStatus eFailedToSetVertexRounds = Acad::eFailedToSetVertexRounds;

//Associative Network related errors.
const Acad::ErrorStatus eFailedToEvaluate = Acad::eFailedToEvaluate;
const Acad::ErrorStatus eFailedToEvaluateDependents = Acad::eFailedToEvaluateDependents;
const Acad::ErrorStatus eInvalidExpression = Acad::eInvalidExpression;
const Acad::ErrorStatus eCyclicDependency = Acad::eCyclicDependency;
const Acad::ErrorStatus eInconsistentConstraint = Acad::eInconsistentConstraint;
const Acad::ErrorStatus eOverDefinedConstraint = Acad::eOverDefinedConstraint;
const Acad::ErrorStatus eInvalidParameterName = Acad::eInvalidParameterName;
const Acad::ErrorStatus eReferencedInEquation = Acad::eReferencedInEquation;

// string user parameters
const Acad::ErrorStatus eStringNotAllowedInExpression = Acad::eStringNotAllowedInExpression;
const Acad::ErrorStatus eTooManyActiveCommands = Acad::eTooManyActiveCommands;

// parametric surface
const Acad::ErrorStatus eUnableToTrimLastPiece = Acad::eUnableToTrimLastPiece;
const Acad::ErrorStatus eUnableToTrimSurface = Acad::eUnableToTrimSurface;

const Acad::ErrorStatus eModifyingAssociativeEntity = Acad::eModifyingAssociativeEntity;
const Acad::ErrorStatus eModifyingDimensionWithExpression = Acad::eModifyingDimensionWithExpression;

const Acad::ErrorStatus eDependentOnObjectErased = Acad::eDependentOnObjectErased;
const Acad::ErrorStatus eSelfIntersecting = Acad::eSelfIntersecting;
const Acad::ErrorStatus eNotOnBoundary = Acad::eNotOnBoundary;
const Acad::ErrorStatus eNotConnected = Acad::eNotConnected;
const Acad::ErrorStatus eNoInputPath = Acad::eNoInputPath;
const Acad::ErrorStatus eNotAssociative = Acad::eNotAssociative;
const Acad::ErrorStatus eNotG1Continuous = Acad::eNotG1Continuous;

// Associative Array 
const Acad::ErrorStatus eChangedAgainstAssociativity = Acad::eChangedAgainstAssociativity;

