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

#if !defined(AFX_INETSTRC_H__4D0B9A84_B226_11d1_A4B1_0060B0576A88__INCLUDED_)
#define AFX_INETSTRC_H__4D0B9A84_B226_11d1_A4B1_0060B0576A88__INCLUDED_

#pragma pack (push, 8)


// for status values, used as exception codes
//
namespace AcadInet
{
	const int StatusBase = 20000;
	enum Status
	{
		// eveything went through just fine
		//
		statusOk	= StatusBase,
		statusInCache,

		// File access
		//
		// ATTENTION: If you add a status code to this group, you must also add it to the method that
		//            maps actual return codes from file I/O-related exceptions or errors to one of 
		//            the following.
		//
		statusFileNotFound,						// CFileException::fileNotFound
		statusBadPath,							// CFileException::badPath
		statusTooManyOpenFiles,					// CFileException::tooManyOpenFiles
		statusFileAccessDenied,					// CFileException::accessDenied
		statusInvalidFileHandle,				// CFileException::invalidFile
		statusDirectoryFull,					// CFileException::directoryFull
		statusHardwareError,					// CFileException::hardIO
		statusSharingViolation,					// CFileException::sharingViolation
		statusDiskFull,							// CFileException::diskFull 
		statusFileGenericError,					// CFileException::generic

		// AcadInet-specific
		//
		statusValidURL,
		statusNotAnURL,							// Not a valid URL
		statusNoWinInet,						// Could not locate WININET.DLL on the system
		statusOldWinInet,						// an old version of WININET.DLL was found
		statusNoAcadInet,						// Could not locate ACADINET.DLL on the system
		statusNotImplemented,					// probably a result of ::GetProcAddress() failure
		statusProtocolNotSupported,				// gopher, mailto, etc.

		statusCreateInternetSessionFailed,		// CAcInternetSessionFactory::CreateSession() failed
		statusInternetSessionConnectFailed,
		statusInternetSessionOpenFailed,

		statusInvalidAccessType,				// something other than GENERIC_READ/WRITE
		statusFileOpenFailed,					// specifically, the OpenFile() method returned NULL
		statusHttpOpenRequestFailed,			// OpenRequest() returned 0
		statusUserCancelledTransfer,

		// WinInet-specific
		//
		// ATTENTION: If you add a status code to this group, you must also add it to the method that
		//            maps actual return codes from Internet transfer requests to one of the following.
		//
		statusHttpBadRequest,					// HTTP_STATUS_BAD_REQUEST         400 - invalid syntax
		statusHttpAccessDenied,					// HTTP_STATUS_DENIED              401 - access denied
		statusHttpPaymentRequired,				// HTTP_STATUS_PAYMENT_REQ         402 - payment required
		statusHttpRequestForbidden,				// HTTP_STATUS_FORBIDDEN           403 - request forbidden
		statusHttpObjectNotFound,				// HTTP_STATUS_NOT_FOUND           404 - object not found
		statusHttpBadMethod,					// HTTP_STATUS_BAD_METHOD          405 - method is not allowed
		statusHttpNoAcceptableResponse,			// HTTP_STATUS_NONE_ACCEPTABLE     406 - no response acceptable to client found
		statusHttpProxyAuthorizationRequired,	// HTTP_STATUS_PROXY_AUTH_REQ      407 - proxy authentication required
		statusHttpTimedOut,						// HTTP_STATUS_REQUEST_TIMEOUT     408 - server timed out waiting for request
		statusHttpConflict,						// HTTP_STATUS_CONFLICT            409 - user should resubmit with more info
		statusHttpResourceGone,					// HTTP_STATUS_GONE                410 - the resource is no longer available
		statusHttpLengthRequired,				// HTTP_STATUS_LENGTH_REQUIRED     411 - the server refused to accept request w/o a length
		statusHttpPreconditionFailure,			// HTTP_STATUS_PRECOND_FAILED      412 - precondition given in request failed
		statusHttpRequestTooLarge,				// HTTP_STATUS_REQUEST_TOO_LARGE   413 - request entity was too large
		statusHttpUriTooLong,					// HTTP_STATUS_URI_TOO_LONG        414 - request URI too long
		statusHttpUnsupportedMedia,				// HTTP_STATUS_UNSUPPORTED_MEDIA   415 - unsupported media type

		statusHttpServerError,					// HTTP_STATUS_SERVER_ERROR        500 - internal server error
		statusHttpNotSupported,					// HTTP_STATUS_NOT_SUPPORTED       501 - required not supported
		statusHttpBadGateway,					// HTTP_STATUS_BAD_GATEWAY         502 - error response received from gateway
		statusHttpServiceUnavailable,			// HTTP_STATUS_SERVICE_UNAVAIL     503 - temporarily overloaded
		statusHttpGatewayTimeout,				// HTTP_STATUS_GATEWAY_TIMEOUT     504 - timed out waiting for gateway
		statusHttpVersionNotSupported,			// HTTP_STATUS_VERSION_NOT_SUP     505 - HTTP version not supported

		statusInternetError,					// all other error codes

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
		TF_VALIDATE_URL		= 0x01,	// overrides all other flags: no transfer is done
		TF_DOWNLOAD_FILE	= 0x02,
		TF_UPLOAD_FILE		= 0x04,
		TF_IGNORE_CACHE		= 0x08	// applies to downloads only
	};
}


#pragma pack (pop)
#endif	// #define AFX_INETSTRC_H__4D0B9A84_B226_11d1_A4B1_0060B0576A88__INCLUDED_
