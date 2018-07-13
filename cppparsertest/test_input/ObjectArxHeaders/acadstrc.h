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
// acadstrc.h:   definition of struct Acad which contains the
//               ErrorStatus enumerated type values

#ifndef AD_ACADSTRC_H
#define AD_ACADSTRC_H 1

#pragma pack (push, 8)

#define eNotImplemented eNotImplementedYet

struct Acad
{
    enum ErrorStatus       { eOk                        =  0,

                             eNotImplementedYet         =  1,
                             eNotApplicable             =  2,
                             eInvalidInput              =  3,
                             eAmbiguousInput            =  4,
                             eAmbiguousOutput           =  5,
                             eOutOfMemory               =  6,
                             eBufferTooSmall            =  7,
                             eInvalidOpenState          =  8,
                             eEntityInInactiveLayout    =  9,

                             eHandleExists              = 10,
                             eNullHandle                = 11,
                             eBrokenHandle              = 12,
                             eUnknownHandle             = 13,
                             eHandleInUse               = 14,
                             eNullObjectPointer         = 15,
                             eNullObjectId              = 16,
                             eNullBlockName             = 17,
                             eContainerNotEmpty         = 18,
                             
                             eNullEntityPointer         = 20,
                             eIllegalEntityType         = 21,
                             eKeyNotFound               = 22,
                             eDuplicateKey              = 23,
                             eInvalidIndex              = 24,
                             eDuplicateIndex            = 25,
                             eAlreadyInDb               = 26,
                             eOutOfDisk                 = 27,
                             eDeletedEntry              = 28,
                             eNegativeValueNotAllowed   = 29,
                             eInvalidExtents            = 30,
                             eInvalidAdsName            = 31,
                             eInvalidSymbolTableName    = 32,
                             eInvalidKey                = 33,
                             eWrongObjectType           = 34,
                             eWrongDatabase             = 35,
                             eObjectToBeDeleted         = 36,
                             eInvalidDwgVersion         = 37,
                             eAnonymousEntry            = 38,
                             eIllegalReplacement        = 39,

                             eEndOfObject               = 40,
                             eEndOfFile                 = 41,
                             eIsReading                 = 42,
                             eIsWriting                 = 43,
                             eNotOpenForRead            = 44,
                             eNotOpenForWrite           = 45,
                             eNotThatKindOfClass        = 46,
                             eInvalidBlockName          = 47,
                             eMissingDxfField           = 48,
                             eDuplicateDxfField         = 49,

                             eInvalidDxfCode            = 50,
                             eInvalidResBuf     = 51,
                             eBadDxfSequence            = 52,
                             eFilerError                = 53,
                             eVertexAfterFace           = 54,
                             eInvalidFaceVertexIndex    = 55,
                             eInvalidMeshVertexIndex    = 56,
                             eOtherObjectsBusy          = 57,
                             eMustFirstAddBlockToDb     = 58,
                             eCannotNestBlockDefs       = 59,

                             eDwgRecoveredOK            = 60,
                             eDwgNotRecoverable         = 61,
                             eDxfPartiallyRead          = 62,
                             eDxfReadAborted            = 63,
                             eDxbPartiallyRead          = 64,
                             eDwgCRCDoesNotMatch        = 65,
                             eDwgSentinelDoesNotMatch   = 66,
                             eDwgObjectImproperlyRead   = 67,
                             eNoInputFiler              = 68,
                             eDwgNeedsAFullSave         = 69,
                             
                             eDxbReadAborted            = 70,
                             eFileLockedByACAD          = 71,
                             eFileAccessErr             = 72,
                             eFileSystemErr             = 73,
                             eFileInternalErr           = 74,
                             eFileTooManyOpen           = 75,
                             eFileNotFound              = 76,
                             eDwkLockFileFound          = 77,
                             
                             eWasErased                 = 80,
                             ePermanentlyErased         = 81,
                             eWasOpenForRead            = 82,
                             eWasOpenForWrite           = 83,
                             eWasOpenForUndo            = 84,
                             eWasNotifying              = 85,
                             eWasOpenForNotify          = 86,
                             eOnLockedLayer             = 87,
                             eMustOpenThruOwner         = 88,
                             eSubentitiesStillOpen      = 89,
                             
                             eAtMaxReaders              = 90,
                             eIsWriteProtected          = 91,
                             eIsXRefObject              = 92,
                             eNotAnEntity               = 93,
                             eHadMultipleReaders        = 94,
                             eDuplicateRecordName       = 95,
                             eXRefDependent             = 96,
                             eSelfReference             = 97,
                             eMissingSymbolTable        = 98,
                             eMissingSymbolTableRec     = 99,

                             eWasNotOpenForWrite        = 100,
                             eCloseWasNotifying         = 101,
                             eCloseModifyAborted        = 102,
                             eClosePartialFailure       = 103,
                             eCloseFailObjectDamaged    = 104,
                             eCannotBeErasedByCaller    = 105,
                             eCannotBeResurrected       = 106,
                             eWasNotErased              = 107,

                             eInsertAfter               = 110,
                             
                             eFixedAllErrors            = 120,
                             eLeftErrorsUnfixed         = 122,
                             eUnrecoverableErrors       = 123,
                             eNoDatabase                = 124,
                             eXdataSizeExceeded         = 125,
                             eRegappIdNotFound          = 126,
                             eRepeatEntity              = 127,
                             eRecordNotInTable          = 128,
                             eIteratorDone              = 129,
                             eNullIterator              = 130,
                             eNotInBlock                = 131,
                             eOwnerNotInDatabase        = 132,
                             eOwnerNotOpenForRead       = 133,
                             eOwnerNotOpenForWrite      = 134,
                             eExplodeBeforeTransform    = 135,
                             eCannotScaleNonUniformly   = 136,
                             eNotInDatabase             = 137,
                             eNotCurrentDatabase        = 138,
                             eIsAnEntity                = 139,

                             eCannotChangeActiveViewport = 140,
                             eNotInPaperspace           = 141,
                             eCommandWasInProgress      = 142,
                             
                             eGeneralModelingFailure    = 150,
                             eOutOfRange                = 151,
                             eNonCoplanarGeometry       = 152,
                             eDegenerateGeometry        = 153,
                             eInvalidAxis               = 154,
                             ePointNotOnEntity          = 155,
                             eSingularPoint             = 156,
                             eInvalidOffset             = 157,
                             eNonPlanarEntity           = 158,
                             eCannotExplodeEntity       = 159,

                             eStringTooLong             = 160,
                             eInvalidSymTableFlag       = 161,
                             eUndefinedLineType         = 162,
                             eInvalidTextStyle          = 163,
                             eTooFewLineTypeElements    = 164,
                             eTooManyLineTypeElements   = 165,
                             eExcessiveItemCount        = 166,
                             eIgnoredLinetypeRedef      = 167,
                             eBadUCS                    = 168,
                             eBadPaperspaceView         = 169,

                             eSomeInputDataLeftUnread   = 170,
                             eNoInternalSpace           = 171,
                             eInvalidDimStyle           = 172,
                             eInvalidLayer              = 173,

                             eUserBreak                 = 180,
                             eUserUnloaded              = 181,

                             eDwgNeedsRecovery          = 190,
                             eDeleteEntity              = 191,
                             eInvalidFix                = 192,
                             eFSMError                  = 193,
                             
                             eBadLayerName              = 200,
                             eLayerGroupCodeMissing     = 201,
                             eBadColorIndex             = 202,
                             eBadLinetypeName           = 203,
                             eBadLinetypeScale          = 204,
                             eBadVisibilityValue        = 205,
                             eProperClassSeparatorExpected = 206,
                             eBadLineWeightValue        = 207,
                             eBadColor                  = 208,
                             eBadMaterialName           = 209,

                             ePagerError                = 210,
                             eOutOfPagerMemory          = 211,
                             ePagerWriteError           = 212,
                             eWasNotForwarding          = 213,
                             
                             eInvalidIdMap              = 220,
                             eInvalidOwnerObject        = 221,
                             eOwnerNotSet               = 222,
                             
                             eWrongSubentityType        = 230,
                             eTooManyVertices           = 231,
                             eTooFewVertices            = 232,
                             
                             eNoActiveTransactions      = 250,
                             eNotTopTransaction         = 251,
                             eTransactionOpenWhileCommandEnded =  252,
                             eInProcessOfCommitting     = 253,
                             eNotNewlyCreated           = 254,
                             eLongTransReferenceError   = 255,
                             eNoWorkSet                 = 256,
                             
                             eAlreadyInGroup            = 260,
                             eNotInGroup                = 261,
                             eAlreadyInferred           = 262,

                             eInvalidREFIID             = 290,
                             eInvalidNormal             = 291,
                             eInvalidStyle              = 292,

                             eCannotRestoreFromAcisFile = 300,
                             eMakeMeProxy               = 301,
                             eNLSFileNotAvailable       = 302,
                             eNotAllowedForThisProxy    = 303,
                             eNotClonedPrimaryProxy     = 304,

                             eNotSupportedInDwgApi      = 310,
                             ePolyWidthLost             = 311,
                             eNullExtents               = 312,
                             eBadDwgHeader              = 314,

                             eLockViolation             = 320,
                             eLockConflict              = 321,
                             eDatabaseObjectsOpen       = 322,
                             eLockChangeInProgress      = 323,

                             eVetoed                    = 325,

                             eNoDocument                = 330,
                             eNotFromThisDocument       = 331,
                             eLISPActive                = 332,
                             eTargetDocNotQuiescent     = 333,
                             eDocumentSwitchDisabled    = 334,
                             eInvalidContext            = 335, 

                             eCreateFailed              = 337,
                             eCreateInvalidName         = 338,
                             eSetFailed                 = 340,
                             eDelDoesNotExist           = 342,
                             eDelIsModelSpace           = 343,
                             eDelLastLayout             = 344,
                             eDelUnableToSetCurrent     = 345,
                             eDelUnableToFind           = 346,
                             eRenameDoesNotExist        = 348,
                             eRenameIsModelSpace        = 349,
                             eRenameInvalidLayoutName   = 350,
                             eRenameLayoutAlreadyExists = 351, 
                             eRenameInvalidName         = 352, 
                             eCopyDoesNotExist          = 354,
                             eCopyIsModelSpace          = 355,
                             eCopyFailed                = 356,
                             eCopyInvalidName           = 357,
                             eCopyNameExists            = 358,

                             eProfileDoesNotExist       = 359,
                             eInvalidFileExtension      = 360,
                             eInvalidProfileName        = 361,
                             eFileExists                = 362,     
                             eProfileIsInUse            = 363,
                             eCantOpenFile              = 364,
                             eNoFileName                = 365,
                             eRegistryAccessError       = 366,
                             eRegistryCreateError       = 367,

                             eBadDxfFile                = 368,
                             eUnknownDxfFileFormat      = 369,
                             eMissingDxfSection         = 370,
                             eInvalidDxfSectionName     = 371,
                             eNotDxfHeaderGroupCode     = 372,
                             eUndefinedDxfGroupCode     = 373,
                             eNotInitializedYet         = 374,
                             eInvalidDxf2dPoint         = 375,
                             eInvalidDxf3dPoint         = 376,
                             eBadlyNestedAppData        = 378,
                             eIncompleteBlockDefinition = 379,
                             eIncompleteComplexObject   = 380,
                             eBlockDefInEntitySection   = 381,
                             eNoBlockBegin              = 382,
                             eDuplicateLayerName        = 383,
                             eBadPlotStyleName          = 384,
                             eDuplicateBlockName        = 385,
                             eBadPlotStyleType          = 386,
                             eBadPlotStyleNameHandle    = 387,
                             eUndefineShapeName         = 388,
                             eDuplicateBlockDefinition  = 389,
                             eMissingBlockName          = 390,
                             eBinaryDataSizeExceeded    = 391,
                             eObjectIsReferenced        = 392,
                             eNoThumbnailBitmap         = 393,
                             eGuidNoAddress             = 394,

                             eMustBe0to2                = 395,    // setDimxxx() returns
                             eMustBe0to3                = 396,
                             eMustBe0to4                = 397,
                             eMustBe0to5                = 398,
                             eMustBe0to8                = 399,
                             eMustBe1to8                = 400,
                             eMustBe1to15               = 401,
                             eMustBePositive            = 402,
                             eMustBeNonNegative         = 403,
                             eMustBeNonZero             = 404,
                             eMustBe1to6                = 405,

                             eNoPlotStyleTranslationTable   = 406,
                             ePlotStyleInColorDependentMode = 407,
                             eMaxLayouts                = 408,
                             eNoClassId                 = 409,

                             eUndoOperationNotAvailable = 410,
                             eUndoNoGroupBegin          = 411,
                             
                             eHatchTooDense             = 420,

                             eOpenFileCancelled         = 430,
                             eNotHandled                = 431,
                             eMakeMeProxyAndResurrect   = 432,
                             eFileSharingViolation      = 433,
                             eUnsupportedFileFormat     = 434,
                             eObsoleteFileFormat        = 435,
                             eFileMissingSections       = 436,
                             eRepeatedDwgRead           = 437,
                             eSilentOpenFileCancelled   = 438,

                             eWrongCellType             = 440,
                             eCannotChangeColumnType    = 441,
                             eRowsMustMatchColumns      = 442,

                             eNullNodeId                = 450,
                             eNoNodeActive              = 451,
                             eGraphContainsProxies      = 452,

                             eDwgShareDemandLoad        = 500,
                             eDwgShareReadAccess        = 501,
                             eDwgShareWriteAccess       = 502,

                             // Plot
                             eLoadFailed                = 503,
                             eDeviceNotFound            = 504,
                             eNoCurrentConfig           = 505,
                             eNullPtr                   = 506,
                             eNoLayout                  = 507,
                             eIncompatiblePlotSettings  = 508,
                             eNonePlotDevice            = 509,
                             eNoMatchingMedia           = 510,
                             eInvalidView               = 511,
                             eInvalidWindowArea         = 512,
                             eInvalidPlotArea           = 513,
                             eCustomSizeNotPossible     = 514,
                             ePageCancelled             = 515,
                             ePlotCancelled             = 516,
                             eInvalidEngineState        = 517,
                             ePlotAlreadyStarted        = 518,
                             eNoErrorHandler            = 519,
                             eInvalidPlotInfo           = 520,
                             eNumberOfCopiesNotSupported = 521,
                             eLayoutNotCurrent          = 522,
                             eGraphicsNotGenerated      = 523,
                             eCannotPlotToFile          = 524,
                             eMustPlotToFile            = 525,
                             eNotMultiPageCapable       = 526,
                             eBackgroundPlotInProgress   = 527,
                             eNotShownInPropertyPalette  = 528,

                             // Sub Selection for Table Object
                             //
                             eSubSelectionSetEmpty      = 550,

                             // Geometric Modeling 
                             eNoIntersections           = 551,
                             eEmbeddedIntersections     = 552,

                             // Layer property overrides
                             //
                             eNoOverride                = 570,
                             eNoStoredOverrides         = 571,
                             eUnableToRetrieveOverrides = 572,
                             eUnableToStoreOverrides    = 573,
                             eUnableToRemoveOverrides   = 574,

                             // Layer Reconciliation
                             //
                             eNoStoredReconcileStatus         = 580,
                             eUnableToStoreReconcileStatus    = 581,

                             // View Association
                             //
                             eInvalidObjectId               = 600,
                             eInvalidXrefObjectId           = 601,
                             eNoViewAssociation             = 602,
                             eNoLabelBlock                  = 603,
                             eUnableToSetViewAssociation    = 604,
                             eUnableToGetViewAssociation    = 605,
                             eUnableToSetLabelBlock         = 606,
                             eUnableToGetLabelBlock         = 607,
                             eUnableToRemoveAssociation     = 608,
                             eUnableToSyncModelView         = 609,

                             // Data links
                             eDataLinkAdapterNotFound           = 650,
                             eDataLinkInvalidAdapterId          = 651,
                             eDataLinkNotFound                  = 652,
                             eDataLinkBadConnectionString       = 653,
                             eDataLinkNotUpdatedYet             = 654,
                             eDataLinkSourceNotFound            = 655,
                             eDataLinkConnectionFailed          = 656,
                             eDataLinkSourceUpdateNotAllowed    = 657,
                             eDataLinkSourceIsWriteProtected    = 658,
                             eDataLinkExcelNotFound             = 659,
                             eDataLinkOtherError                = 660,

                             // Xref notification
                             //
                             eXrefReloaded                   = 700,
                             eXrefReloadImpossibleAtThisTime = 701,

                             // DWG Security
                             //
                             eSecInitializationFailure      = 1001,
                             eSecErrorReadingFile           = 1002,
                             eSecErrorWritingFile           = 1003,
                             //
                             // Status codes specific to Digital Signatures
                             //
                             eSecInvalidDigitalID           = 1101,
                             eSecErrorGeneratingTimestamp   = 1102,
                             eSecErrorComputingSignature    = 1103,
                             eSecErrorWritingSignature      = 1104,
                             //
                             // Status codes specific to password-based protection
                             //
                             eSecErrorEncryptingData        = 1201,
                             eSecErrorCipherNotSupported    = 1202,
                             eSecErrorDecryptingData        = 1203,

                             eNoAcDbHostApplication         = 1300,
                             eNoUnderlayHost                = 1301,


                             // Status codes for Point Cloud indexing
                             ePCUnknown                     = 1400,
                             ePCLargeData                   = 1401,
                             ePCUnknownFileType             = 1402,
                             ePCFileNotFound                = 1403,
                             ePCFileNotCreated              = 1404,
                             ePCFileNotOpened               = 1405,
                             ePCFileNotClosed               = 1406,
                             ePCFileNotWritten              = 1407,
                             ePCFileWrongFormat             = 1408,
                             ePCFileDataSelectorInvalid     = 1409,
                             ePCCoordSysReprojectFail       = 1410,
                             ePCDiskSpaceTooSmall           = 1411,
                             ePCThreadTerminated            = 1412,
                             ePCFileNotErased               = 1413,
                             ePCCoordSysAssignFail          = 1414,
                             ePCLastImporterUnfinished      = 1415,
                             ePCNoEngineInfo                = 1416,
                             ePCInProgress                  = 1417,


                             // BEGIN: Internet-related status codes

                             // eveything went through just fine
                             //
                             eInetBase                  = 20000,
                             eInetOk                    = eInetBase,
                             eInetInCache,  // file already downloaded
                             
                             // File access
                             // 
                             eInetFileNotFound,     // CFileException::fileNotFound
                             eInetBadPath,          // CFileException::badPath
                             eInetTooManyOpenFiles, // CFileException::tooManyOpenFiles
                             eInetFileAccessDenied, // CFileException::accessDenied
                             eInetInvalidFileHandle,// CFileException::invalidFile
                             eInetDirectoryFull,    // CFileException::directoryFull
                             eInetHardwareError,    // CFileException::hardIO
                             eInetSharingViolation, // CFileException::sharingViolation
                             eInetDiskFull,         // CFileException::diskFull 
                             eInetFileGenericError, // CFileException::generic
                             
                             // AcadInet-specific
                             //
                             eInetValidURL,
                             eInetNotAnURL,         // Not a valid URL
                             eInetNoWinInet,        // Could not locate WININET.DLL on the system
                             eInetOldWinInet,       // an old version of WININET.DLL was found
                             eInetNoAcadInet,       // Could not locate ACADINET.DLL on the system
                             eInetNotImplemented,   // probably a result of ::GetProcAddress() failure
                             eInetProtocolNotSupported,// gopher, mailto, etc.
                             
                             eInetCreateInternetSessionFailed,  // CAcInternetSessionFactory::CreateSession() failed
                             eInetInternetSessionConnectFailed,
                             eInetInternetSessionOpenFailed,
                             
                             eInetInvalidAccessType,    // something other than a download/upload request
                             eInetFileOpenFailed,       // specifically, the OpenFile() method returned NULL
                             eInetHttpOpenRequestFailed,// OpenRequest() returned 0
                             eInetUserCancelledTransfer,
                             
                             // WinInet-specific
                             //
                             eInetHttpBadRequest,                   // HTTP_STATUS_BAD_REQUEST         400 - invalid syntax
                             eInetHttpAccessDenied,                 // HTTP_STATUS_DENIED              401 - access denied
                             eInetHttpPaymentRequired,              // HTTP_STATUS_PAYMENT_REQ         402 - payment required
                             eInetHttpRequestForbidden,             // HTTP_STATUS_FORBIDDEN           403 - request forbidden
                             eInetHttpObjectNotFound,               // HTTP_STATUS_NOT_FOUND           404 - object not found
                             eInetHttpBadMethod,                    // HTTP_STATUS_BAD_METHOD          405 - method is not allowed
                             eInetHttpNoAcceptableResponse,         // HTTP_STATUS_NONE_ACCEPTABLE     406 - no response acceptable to client found
                             eInetHttpProxyAuthorizationRequired,   // HTTP_STATUS_PROXY_AUTH_REQ      407 - proxy authentication required
                             eInetHttpTimedOut,                     // HTTP_STATUS_REQUEST_TIMEOUT     408 - server timed out waiting for request
                             eInetHttpConflict,                     // HTTP_STATUS_CONFLICT            409 - user should resubmit with more info
                             eInetHttpResourceGone,                 // HTTP_STATUS_GONE                410 - the resource is no longer available
                             eInetHttpLengthRequired,               // HTTP_STATUS_LENGTH_REQUIRED     411 - the server refused to accept request w/o a length
                             eInetHttpPreconditionFailure,          // HTTP_STATUS_PRECOND_FAILED      412 - precondition given in request failed
                             eInetHttpRequestTooLarge,              // HTTP_STATUS_REQUEST_TOO_LARGE   413 - request entity was too large
                             eInetHttpUriTooLong,                   // HTTP_STATUS_URI_TOO_LONG        414 - request URI too long
                             eInetHttpUnsupportedMedia,             // HTTP_STATUS_UNSUPPORTED_MEDIA   415 - unsupported media type
                             
                             eInetHttpServerError,                  // HTTP_STATUS_SERVER_ERROR        500 - internal server error
                             eInetHttpNotSupported,                 // HTTP_STATUS_NOT_SUPPORTED       501 - required not supported
                             eInetHttpBadGateway,                   // HTTP_STATUS_BAD_GATEWAY         502 - error response received from gateway
                             eInetHttpServiceUnavailable,           // HTTP_STATUS_SERVICE_UNAVAIL     503 - temporarily overloaded
                             eInetHttpGatewayTimeout,               // HTTP_STATUS_GATEWAY_TIMEOUT     504 - timed out waiting for gateway
                             eInetHttpVersionNotSupported,          // HTTP_STATUS_VERSION_NOT_SUP     505 - HTTP version not supported
                             
                             eInetInternetError,                    // all other error codes
                             
                             // corresponding to the MFC CException
                             //
                             eInetGenericException,
                             
                             // all others
                             //
                             eInetUnknownError,
                             
                             // END: Internet-related status codes

                             // AcDbCustomOsnapManager specific
                             eAlreadyActive,
                             eAlreadyInactive,
                             // End AcDbCustomOsnapManager specific

                             // AcDbEval
                             eGraphEdgeNotFound,
                             eGraphNodeNotFound,
                             eGraphNodeAlreadyExists,
                             eGraphEdgeAlreadyExists,
                             eGraphCyclesFound,

                             // AcDbBlockRepresentation
                             eAlreadyHasRepresentation,
                             eNoRepresentation,

                             // solid chamfer/fillet
                             eFailedToSetEdgeChamfers,
                             eNoConnectedBlendSet,
                             eFailedToBlend,
                             eFailedToSetEdgeRounds,
                             eFailedToSetVertexRounds,

                             // visual styles
                             eVSNotFound,
                             eVSTrue,
                             eVSFalse,
                             eVSAlreadyExists,
                             eVSOneOffCreated,
                             eVSAPIOnlyValues,
                             eVSIsInUse,
                             eVSIsAcadDefault,

                             // solid history evaluation
                             eEmptyOperand,
                             eNoEntitiesFromPersistentIds,
                             eFailedCurveCheck,
                             eMaxNodes,

                             //Associative Network related errors.
                             eFailedToEvaluate,
                             eFailedToEvaluateDependents,
                             eInvalidExpression,
                             eCyclicDependency,
                             eInconsistentConstraint,
                             eOverDefinedConstraint,
                             eAllInSameRigidSet,
                             eInvalidParameterName,
                             eReferencedInEquation,
                             eEntityRestricedInDOF,

                             // large object support
                             eDataTooLarge,
                             eNearSizeLimit,

                             // string user parameters
                             eStringNotAllowedInExpression,
                             eTooManyActiveCommands,

                             // parametric surface
                             eUnableToTrimLastPiece,
                             eUnableToTrimSurface,
                             
                             eModifyingAssociativeEntity,
                             eModifyingDimensionWithExpression,

                             eDependentOnObjectErased,
                             eSelfIntersecting,
                             eNotOnBoundary,
                             eNotConnected,
                             eNoInputPath,
                             eNotAssociative,

                             // ASM G1 discontinuity error 
                             eNotG1Continuous,
                             eOwnerToBeTransformed,
                             eMustBeInteger,
                             eMustBePositiveInteger,

                             // Associative Array
                             eChangedAgainstAssociativity,
                             eItemCountChanged,

                             // AdIntImgServices error
                             eGetAdIntImgServicesFailed,

                             // Atil::Image error
                             eReadImageBufferFailed,
                             eWriteImageBufferFailed,
                             eGetImageBytesFailed,
                             eGetImageDIBFailed,
                             eConvertImageFormatFailed,

                             // get preview image error
                             eGetPreviewImageFailed,
                             eInvalidPreviewImage,

                             // Live Preview error
                             eDelayMore,
                             ePreviewFailed,
                             eAbortPreview,
                             eEndPreview,
                             eNoPreviewContext,

                             // Cloud error
                             eFileNotInCloud,
                           };

    // The following enums represent bits in a "history" value, which indicates
    // what all point filters had an effect on the point on a particular
    // system event.
    //
    // The bits are independent from one another, except:
    // - only one flag out of eOrtho and ePolarAng will be returned at any
    //   given callout.
    // - If eNotDigitizer is set, then none of the following will ever be
    //   set:  eGripped, eCartSnapped, eOrtho, eCyclingPt
    //   but the rest of the flags are independent.  In eNotDigitizer events,
    //   the rawPoint, postGrippedPoint, cartesianSnappedPoint and orthoPoint
    //   values will all be identical.
    // - (history & eCoordPending) is really an mask for any of the 3 coordinate
    //   point enums directly preceding it.
    enum PointHistory     {   eTablet      = 0x0001, // !eTablet implies window
                                                     // cursor tracking, as opposed
                                                     // to tablet mode.
                              eNotDigitizer= 0x0002, // Implies rawPoint was typed,
                                                     // at keyboard or fed by
                                                     // by program or script or
                                                     // menu macro expansion or
                                                     // digitizer pick event;
                                                     // anything but digitizer
                                                     // motion.
                              eLastPt     = 0x0004,  // indicates lastPoint is
                                                     // valid.
                              eGripped    = 0x008,   // Fell into grip gravity
                              eCartSnapped= 0x0010,  // Snap mode on ("old"
                                                     // cartesian snap, that is.)
                              eOrtho      = 0x0020,  // Ortho on
                              eCyclingPt  = 0x0040,  // indicates caller is
                                                     // "cycling" so this is not
                                                     // the necessarily the
                                                     // "best" osnap/alignment
                                                     // computation.
                              eOsnapped   = 0x0080,  // Osnap did something
                              ePolarAngle = 0x0100,  // Polar Snap on
                              eAligned    = 0x0400,  // AutoAlign did something

                              eAppFiltered = 0x0800, // If a point filter is
                                                     // registered (only monitors
                                                     // will get this bit).

                              eForcedPick = 0x1000,  // "Forced Picking" is enabled
                              ePickMask   = 0xE000,  // AND mask to strip out "pick
                                                     // mode" bits to compare with
                                                     // eDidNotPick,
                                                     // eUsedPickBox and
                                                     // eUsedOsnapBox as enums.
                                                     // more of the 7 values may
                                                     // be used in the future.
                              eDidNotPick = 0x0000,  // No picking was done, i.e.
                                                     // !eForcedPick & no OSNAP
                                                     // was performed.

                              eUsedPickBox = 0x2000, // "Forced picking" used Pick
                                                     // box. used as enum within
                              eUsedOsnapBox = 0x4000,// "Forced picking" used OSNAP
                                                     // box.
                              ePickAborted  = 0x8000,// If picking of the
                                                     // apertureEntities has been
                                                     // aborted because of out-
                                                     // stating mouse move messages
                                                     // in AutoCAD's message queue.
                              eXPending   = 0x10000, // XCoord Pending
                              eYPending   = 0x20000, // YCoord Pending
                              eZPending   = 0x40000, // ZCoord Pending
                              eCoordPending =
                                            0x70000, // Mask for preceding
                                                     // pending coordinate bits.
                              eFromKeyboard =
                                            0x80000, // Coordinate has been typed
                                                     // in by the user
                              eNotInteractive =
                                           0x100000, // Coordinate came from script,
                                                     // menu macro expansion, a LISP
                                                     // (command) call or ads_command().
                              eDirectDistance = 
                                           0x200000, // Direct Distance has been input
                                                     // for a point
                              eGizmoConstrainted = 
                                           0x400000, // Gizmo constraint has been used
                                                     // on the point
    };

    // Acad::PromptStatus
    //
    // Define an enum sequence
    // in the image of the RT* return statuses defined in ADSCODES.H.
    // In fact, these values can be directly interchanged with ads_get*()
    // function return statuses, except for eDirect as noted below.
    // I suggest it be scoped in class Acad, which
    // also scopes ErrorStatus.
    //
    enum PromptStatus {
        eNone     =  5000,
        eModeless =  5027,
        eNormal   =  5100,
        eError    = -5001,
        eCancel   = -5002,
        eRejected = -5003,
        eFailed   = -5004,
        eKeyword  = -5005,
        eDirect   = -5999    // Passed to endGetPoint if the getpoint was
                             // nested within another geometric value prompt,
                             // (such as angle) and the entered response was
                             // such a value rather than a point.
    };

};

#pragma pack (pop)
#endif 
