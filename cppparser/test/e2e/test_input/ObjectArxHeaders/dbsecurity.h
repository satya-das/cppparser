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
// DESCRIPTION: DWG Security - Parameters for encryption/decryption
//              and digital signatures
//

#ifndef __DBSECURITY_H_
#define __DBSECURITY_H_

class AcDbDate;


enum
{
    SECURITYPARAMS_ENCRYPT_DATA     = 0x00000001,
    SECURITYPARAMS_ENCRYPT_PROPS    = 0x00000002,

    SECURITYPARAMS_SIGN_DATA        = 0x00000010,
    SECURITYPARAMS_ADD_TIMESTAMP    = 0x00000020
};


enum
{
    SECURITYPARAMS_ALGID_RC4        = 0x00006801
};


struct SecurityParams
{
    unsigned long   cbSize;
    unsigned long   ulFlags;        // see enum above for flag values

    // data relevant to password protection
    wchar_t*        wszPassword;
    unsigned long   ulProvType;
    wchar_t*        wszProvName;
    unsigned long   ulAlgId;        // SECURITYPARAMS_ALGID_RC4
    unsigned long   ulKeyLength;

    // data relevant to digital signatures
    wchar_t*        wszCertSubject;
    wchar_t*        wszCertIssuer;
    wchar_t*        wszCertSerialNum;
    wchar_t*        wszComment;
    wchar_t*        wszTimeServer;
};


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following struct is for internal use only.                           //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

struct SignatureInfo
{
    unsigned long   cbSize;

    unsigned long   ulFlags;
    wchar_t*        wszCertSubject;
    wchar_t*        wszCertIssuer;
    wchar_t*        wszSubjectEMail;
    wchar_t*        wszCertSerialNum;
    wchar_t*        wszX500;
    AcDbDate*       pTimeCertNotBefore;
    AcDbDate*       pTimeCertNotAfter;
    wchar_t*        wszComment;
    wchar_t*        wszTimeServer;
    AcDbDate*       pTimestamp;
};


#endif  // __DBSECURITY_H_
