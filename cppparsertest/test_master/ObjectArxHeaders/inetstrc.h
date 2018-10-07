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
// Name:    inetstrc.h
//
// Remarks:	AcadInet defines a namespace that enumerates most of the status 
//			codes returned from Internet-related operations.
//
//////////////////////////////////////////////////////////////////////////////
#if  !defined(AFX_INETSTRC_H__4D0B9A84_B226_11d1_A4B1_0060B0576A88__INCLUDED_)
#	define AFX_INETSTRC_H__4D0B9A84_B226_11d1_A4B1_0060B0576A88__INCLUDED_
#	pragma  pack (push, 8)
// for status values, used as exception codes
//
namespace AcadInet
{
	const int StatusBase = 20000;
	enum Status
	{
		// eveything went through just fine
		//
		statusOk = StatusBase,
		statusInCache,
		// File access
		//
		// ATTENTION: If you add a status code to this group, you must also add it to the method that
		//            maps actual return codes from file I/O-related exceptions or errors to one of 
		//            the following.
		//
		statusFileNotFound,
		statusBadPath,
		statusTooManyOpenFiles,
		statusFileAccessDenied,
		statusInvalidFileHandle,
		statusDirectoryFull,
		statusHardwareError,
		statusSharingViolation,
		statusDiskFull,
		statusFileGenericError,
		// AcadInet-specific
		//
		statusValidURL,
		statusNotAnURL,
		statusNoWinInet,
		statusOldWinInet,
		statusNoAcadInet,
		statusNotImplemented,
		statusProtocolNotSupported,
		statusCreateInternetSessionFailed,
		statusInternetSessionConnectFailed,
		statusInternetSessionOpenFailed,
		statusInvalidAccessType,
		statusFileOpenFailed,
		statusHttpOpenRequestFailed,
		statusUserCancelledTransfer,
		// WinInet-specific
		//
		// ATTENTION: If you add a status code to this group, you must also add it to the method that
		//            maps actual return codes from Internet transfer requests to one of the following.
		//
		statusHttpBadRequest,
		statusHttpAccessDenied,
		statusHttpPaymentRequired,
		statusHttpRequestForbidden,
		statusHttpObjectNotFound,
		statusHttpBadMethod,
		statusHttpNoAcceptableResponse,
		statusHttpProxyAuthorizationRequired,
		statusHttpTimedOut,
		statusHttpConflict,
		statusHttpResourceGone,
		statusHttpLengthRequired,
		statusHttpPreconditionFailure,
		statusHttpRequestTooLarge,
		statusHttpUriTooLong,
		statusHttpUnsupportedMedia,
		statusHttpServerError,
		statusHttpNotSupported,
		statusHttpBadGateway,
		statusHttpServiceUnavailable,
		statusHttpGatewayTimeout,
		statusHttpVersionNotSupported,
		statusInternetError,
		// corresponding to the MFC CException
		//
		statusGenericException,
		// all others
		//
		statusUnknownError
	};
}
// flags used in the invocation of CProxyInet::TransferFile(), and, correspondingly,
// in CAcadInetFacade::TransferFile()
//
namespace AcadInet
{
	enum
	{
		TF_VALIDATE_URL = 0x01,
		TF_DOWNLOAD_FILE = 0x02,
		TF_UPLOAD_FILE = 0x04,
		TF_IGNORE_CACHE = 0x08
	};
}
#	pragma  pack (pop)
#endif
