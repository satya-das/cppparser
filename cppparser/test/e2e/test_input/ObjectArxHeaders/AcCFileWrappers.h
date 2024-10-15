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
// Name:            AcCFileWrappers.h
//
// Description:     Wrapper classes for CFile and CStdioFile.  Expose all
//                  of the underlying classes, and override the Read,
//                  Write, ReadString and WriteString methods.
//
//////////////////////////////////////////////////////////////////////////////

// Note: 1. this header should be included *after* mfc headers
//       2. there is a duplicate copy of this header file in heidi\source\heidi,
//          please update the copy in heidi whenever this file gets updated.
//        

#pragma once
#pragma warning(push, 4)

#include "AdCharFmt.h"
#include "adesk.h"

#ifdef ASSERT
#define AcCFile_Assert ASSERT
#elif defined assert
#define AcCFile_Assert assert
#elif defined _ASSERTE
#define AcCFile_Assert _ASSERTE
#else
#define AcCFile_Assert(x)
#endif

// forward declarations
#ifdef UNICODE
void acByteSwap(wchar_t &wch);
void acWriteWCharToCFile(wchar_t wch, CFile *pFile, unsigned nFmt, bool bUseCIF);
bool acReadCIFFromCFile(CFile *pCFile, wchar_t &wch);
bool acReadAnsiCharFromCFile(CFile *pCFile, wchar_t &wch, AdCharFormatter *pChFmtr);
bool acReadUtf8CharFromCFile(CFile *pCFile, wchar_t &wch, AdCharFormatter *pChFmtr);
bool acReadUtf16CharFromCFile(CFile *pCFile, wchar_t &wch, AdCharFormatter *pChFmtr);
#endif
unsigned acCheckCFileCharFormat(CFile *pCFile);

// Used by AcCFile and AcCStdioFile
class AcOutputBufMgr
{
  public:
    AcOutputBufMgr();
    ~AcOutputBufMgr();
    bool attachBuffer(void *pBuffer, unsigned nBufSize);
    bool detachBuffer();
    bool hasBuffer() const;
    unsigned byteCount() const;
    void * pointer() const;
    void * requestBytes(unsigned nBytesNeeded);
    unsigned takeBytes(unsigned nBytesUsed);
    bool     reset();
  private:
    void * mpBuffer;
    unsigned mnBufSize;     // total size of the buffer, in bytes
    unsigned mnByteCount;   // how many bytes are in the buffer now
    unsigned mnBytesRequested;
};

inline AcOutputBufMgr::AcOutputBufMgr()
        : mpBuffer(NULL), mnBufSize(0), mnByteCount(0), mnBytesRequested(0)
{
}

inline AcOutputBufMgr::~AcOutputBufMgr()
{
    AcCFile_Assert(this->mnByteCount == 0);  // should be flushed by now
    AcCFile_Assert(this->mnBytesRequested == 0);
}

inline bool AcOutputBufMgr::hasBuffer() const
{
    return this->mpBuffer != NULL;
}

inline unsigned AcOutputBufMgr::byteCount() const
{
    return this->mnByteCount;
}

inline void * AcOutputBufMgr::pointer() const
{
    return this->mpBuffer;
}

inline bool AcOutputBufMgr::attachBuffer(void *pBuffer, unsigned nBufSize)
{
    AcCFile_Assert(pBuffer != NULL);
    AcCFile_Assert(nBufSize > 2);
    AcCFile_Assert(nBufSize < 0x10000000);  // 256M sanity check
    AcCFile_Assert(this->mpBuffer == NULL);
    AcCFile_Assert(this->mnBufSize == 0);
    AcCFile_Assert(this->mnByteCount == 0);
    AcCFile_Assert(this->mnBytesRequested == 0);
    if (this->mpBuffer != NULL || pBuffer == NULL)
        return false;   // bad input or unexpected call
    this->mpBuffer = pBuffer;
    this->mnBufSize = nBufSize;
    return true;        // success
}

inline bool AcOutputBufMgr::detachBuffer()
{
    AcCFile_Assert(this->mpBuffer != NULL);
    AcCFile_Assert(this->mnBufSize != 0);
    AcCFile_Assert(this->mnByteCount == 0);  // should be flushed by now
    AcCFile_Assert(this->mnBytesRequested == 0);
    if (this->mpBuffer == NULL || this->mnByteCount != 0
                               || this->mnBytesRequested != 0)
        return false;   // no buffer to release, or it's still busy
    this->mpBuffer = NULL;
    this->mnBufSize = 0;
    return true;        // success
}

// client requests the pointer and says how many bytes he may need
inline void * AcOutputBufMgr::requestBytes(unsigned nBytesNeeded)
{
    AcCFile_Assert(this->hasBuffer());  // better have a buffer!
    AcCFile_Assert(this->mnBytesRequested == 0);
    if (!this->hasBuffer() || this->mnBytesRequested != 0)
        return NULL;    // no buffering, or buffer already reserved
    AcCFile_Assert(this->mnBufSize >= 2);
    AcCFile_Assert(this->mnByteCount <= this->mnBufSize);
    AcCFile_Assert(nBytesNeeded >= 1);
    AcCFile_Assert(nBytesNeeded < this->mnBufSize);
    if (nBytesNeeded < 1 || nBytesNeeded >= this->mnBufSize)
        return NULL;    // invalid reserved size request
    if (this->mnByteCount + nBytesNeeded > this->mnBufSize)
        return NULL;    // buffer is full, needs to be flushed
    this->mnBytesRequested = nBytesNeeded;

    // return next free slot in the buffer
    return reinterpret_cast<char *>(this->mpBuffer) + this->mnByteCount;
}

// client tells us how many bytes he used, and we return how many
// bytes are left in the buffer.
inline unsigned AcOutputBufMgr::takeBytes(unsigned nBytesUsed)
{
    AcCFile_Assert(this->hasBuffer());  // better have a buffer!
    AcCFile_Assert(this->mnBytesRequested != 0);
    AcCFile_Assert(this->mnBytesRequested >= nBytesUsed);
    if (!this->hasBuffer() || this->mnBytesRequested < nBytesUsed)
        return 0;       // no buffering, or trying to release too much
    this->mnBytesRequested = 0;
    this->mnByteCount += nBytesUsed;
    ASSERT(this->mnByteCount <= this->mnBufSize);
    return this->mnBufSize - this->mnByteCount; // return how many bytes left
}

inline bool AcOutputBufMgr::reset()
{
    AcCFile_Assert(this->hasBuffer());  // better have a buffer!
    AcCFile_Assert(this->mnBytesRequested == 0);
    if (!this->hasBuffer() || this->mnBytesRequested != 0)
        return false;   // no buffer, or unmatched request
    this->mnByteCount = 0;
    return true;        // mission accomplished
}

class AcCFile : public CFile
{
public:
    // declare compatible ctors and dtor
    AcCFile();
    AcCFile(HANDLE hFile);
    AcCFile(LPCTSTR lpszFileName, UINT nOpenFlags);
    virtual ~AcCFile();

    // Override the base filing operations
    virtual UINT Read(void *lpBuf, UINT nCount);
    virtual void Write(const void *lpBuf, UINT nCount);

    // And add our own overloads
    virtual UINT Read(LPTSTR lpBuf, UINT nCount);
    virtual void Write(LPCTSTR pString, UINT nCount);  // write string
    virtual void Write(LPCTSTR pString);   // write null terminated string

    // Format related methods
    unsigned getCharFormat() const { return this->mChFmtr.getFormat(); }
    unsigned setCharFormat(unsigned nFmt) {
            return this->mChFmtr.setFormat(nFmt); }
    bool getUseCIF() const { return this->mChFmtr.getUseCIF(); }
    bool setUseCIF(bool bUseCIF) {
            return this->mChFmtr.setUseCIF(bUseCIF); }
    bool getExpandLF() const { return this->mChFmtr.getExpandLF(); }
    bool setExpandLF(bool bExpandLF) {
            return this->mChFmtr.setExpandLF(bExpandLF); }

    bool readBOM();
    bool writeBOM();

    // Buffering methods, for performance.  Client can provide a buffer
    // for output, so that a minimum number of writes to the underlying
    // file are done.  This helps greatly when writing across a high
    // latency network.
    //
    bool attachBuffer(void *pBuffer, unsigned nBufSize);
    bool detachBuffer();
    bool flushBytes();
    bool hasBuffer() const;

  private:
    AdCharFormatter mChFmtr;
    AcOutputBufMgr mOutputBufMgr;
};

#ifdef _ADESK_WINDOWS_
class AcCStdioFile : public CStdioFile
{
public:
    // declare compatible ctors and dtor
    AcCStdioFile();
    AcCStdioFile(FILE* pOpenStream);
    AcCStdioFile(LPCTSTR lpszFileName, UINT nOpenFlags);
    virtual ~AcCStdioFile();

    // Override the string filing operations
    virtual void WriteString(LPCTSTR lpsz);
    virtual LPTSTR ReadString(LPTSTR lpsz, UINT nMax);
    virtual BOOL ReadString(CString& rString);

    // Format related methdos
    unsigned getCharFormat() const { return this->mChFmtr.getFormat(); }
    unsigned setCharFormat(unsigned nFmt) {
            return this->mChFmtr.setFormat(nFmt); }
    bool getUseCIF() const { return this->mChFmtr.getUseCIF(); }
    bool setUseCIF(bool bUseCIF) {
            return this->mChFmtr.setUseCIF(bUseCIF); }
    bool getExpandLF() const { return this->mChFmtr.getExpandLF(); }
    bool setExpandLF(bool bExpandLF) {
            return this->mChFmtr.setExpandLF(bExpandLF); }

    bool readBOM();
    bool writeBOM();

    // Buffering methods, for performance.  Client can provide a buffer
    // for output, so that a minimum number of writes to the underlying
    // file are done.  This helps greatly when writing across a high
    // latency network.
    //
    bool attachBuffer(void *pBuffer, unsigned nBufSize);
    bool detachBuffer();
    bool flushBytes();
    bool hasBuffer() const;

  private:
    AdCharFormatter mChFmtr;
    AcOutputBufMgr mOutputBufMgr;
};
#endif //_ADESK_WINDOWS_ MAC_PORT

// This is the helper function to determine file type of the 
// currently opened CFile. It is compiled both under MBCS and 
// UNICODE builds.  If no BOM is present, we return kAnsi.
inline unsigned acCheckCFileCharFormat(CFile *pCFile)
{
    AcCFile_Assert(pCFile != NULL);
    AcCFile_Assert((pCFile->m_hFile) != (CFile::hFileNull));

    // Skip type check for too small files.
    const int nLength = (int) pCFile->GetLength();
    if(nLength <= 3)
        return AdCharFormatter::kAnsi;

    // Backup current file pointer position.
    // Note: we might want to require that this method be called right
    // after open, when the file pointer is still 0.  And then we
    // could leave the file pointer positioned after the BOM on return.
    //
    const ULONGLONG ullPrevPos = pCFile->GetPosition();
    pCFile->Seek(0L, SEEK_SET);

    DWORD dwMagicCode = 0; // Read file header (BOM), if any.

    // Note: if file is not opened for read, this will throw
    // an exception.
    pCFile->Read(&dwMagicCode, 4);

    // Restore file pointer position.
    pCFile->Seek(ullPrevPos, SEEK_SET);

    // Note: if we found a BOM, we might want to seek beyond
    // it, so caller doesn't run into it.

    // Determine file's char type by header.
    const unsigned nCharFmt = AdCharFormatter::lookupBOM(dwMagicCode);
    return (nCharFmt == AdCharFormatter::kUnknown) ?
            AdCharFormatter::kAnsi : nCharFmt;
}

// CFile never expands LFs (you can't open a CFile with
// typeBinary mode).  So callers won't be expecting it
// to happen.  They can override this behavior by calling
// AcCFile::setExpandLF(true) if they want to.
inline AcCFile::AcCFile()
        : mChFmtr(AdCharFormatter::kAnsi,
                  false,      // useCIF
                  false)      // expandLF
{
    this->mChFmtr.setExpandLF(false);
}

inline AcCFile::AcCFile(HANDLE hFile)
        : CFile(hFile),
          mChFmtr(AdCharFormatter::kAnsi,
                  false,      // useCIF
                  false)      // expandLF
{
}

inline AcCFile::AcCFile(LPCTSTR lpszFileName, UINT nOpenFlags)
        : CFile(lpszFileName, nOpenFlags),
          mChFmtr(AdCharFormatter::kAnsi,
                  false,      // useCIF
                  false)      // expandLF
{
}

inline AcCFile::~AcCFile()
{
}

#ifdef UNICODE
inline void acWriteWCharToCFile(wchar_t wch, CFile *pFile,
                                const AdCharFormatter &charFmt)
{
    char chBuf[8];  // CIF is 7 bytes, utf-32 cr-lf might be 8
    const int nBytes = charFmt.wcharToBytes(wch, chBuf,
                                            sizeof(chBuf));
    AcCFile_Assert(nBytes >= 1);
    AcCFile_Assert(nBytes <= 8);
    pFile->Write(chBuf, nBytes);
}
#endif

inline void AcCFile::Write(const void * lpBuf, UINT nCount)
{
    this->CFile::Write(lpBuf, nCount);
}

inline void AcCFile::Write(LPCTSTR lpBuf, UINT nCount)
{
    AcCFile_Assert(nCount < 0x1000000);  // 16M sanity check
#ifndef UNICODE
    this->CFile::Write(lpBuf, nCount);
#else
    const bool bHasBuffer = this->hasBuffer();
    for (unsigned i = 0; i < nCount; i++) {
        if (!bHasBuffer)
            ::acWriteWCharToCFile(lpBuf[i], this, this->mChFmtr);
        else {
            // worst case is 8 bytes (utf-32 cr-lf)
            const int kReservedSize = 8;
            void *pOutBuf = this->mOutputBufMgr.requestBytes(kReservedSize);
            const int nBytes = this->mChFmtr.wcharToBytes(lpBuf[i],
                                        reinterpret_cast<char *>(pOutBuf),
                                        kReservedSize);
            AcCFile_Assert(nBytes >= 1);
            AcCFile_Assert(nBytes <= kReservedSize);
            const unsigned nBytesLeft = this->mOutputBufMgr.takeBytes(nBytes);
            if (nBytesLeft <= kReservedSize)
                this->flushBytes();
        }
    }
#endif
}

inline void AcCFile::Write(LPCTSTR lpBuf)
{
#ifndef UNICODE
    // Unfortunately, hard cast is needed to change size_t 
    // to UINT to avoid new 64-bit compatible warnings.
    this->Write(lpBuf, (UINT)strlen(lpBuf));
#else
    this->Write(lpBuf, AdCharFormatter::wcsLength(lpBuf));
#endif
}

inline UINT AcCFile::Read(void * lpBuf, UINT nCount)
{
    return this->CFile::Read(lpBuf, nCount);
}

inline bool AcCFile::readBOM()
{
    const ULONGLONG dwPosition = this->GetPosition();
    AcCFile_Assert(dwPosition == 0);
    if (dwPosition != 0)
        return false; // Can't do this unless we're at start of file.

    unsigned short nVal;
    if (this->Read(&nVal, 2) == 2) {
        if (nVal == 0xfeff) {
            this->setCharFormat(AdCharFormatter::kUtf16LE);
            return true;
        }
        if (nVal == 0xfffe) {
            this->setCharFormat(AdCharFormatter::kUtf16BE);
            return true;
        }
        if (nVal == 0xbbef) {
            unsigned char nByte3;
            if (this->Read(&nByte3, 1) == 1) {
                if (nByte3 == 0xbf) {
                    this->setCharFormat(AdCharFormatter::kUtf8);
                    return true;
                }
            }
        }
        else if (nVal == 0 || nVal == 0xfeff) {
            unsigned nVal2;
            if (this->Read(&nVal2, 2) == 2) {
                if (nVal == 0 && nVal2 == 0xfffe) {
                    this->setCharFormat(AdCharFormatter::kUtf32BE);
                    return true;
                }
                else if (nVal == 0xfeff && nVal2 == 0) {
                    this->setCharFormat(AdCharFormatter::kUtf32LE);
                    return true;
                }
            }
        }
    }

    // If got here, then no BOM found, so reset 
    // to file beginning. Leave format what it was.
    this->SeekToBegin();
    return false;
}

inline bool AcCFile::writeBOM()
{
    AcCFile_Assert((this->m_hFile) != CFile::hFileNull);
    if ((this->m_hFile) == CFile::hFileNull)
        return false; // There must be an associated file.

    const ULONGLONG dwPosition = this->GetPosition();
    AcCFile_Assert(dwPosition == 0);
    if (dwPosition != 0)
        return false; // Can't do this unless we're at start of file.

    unsigned nBom = 0;
    const int cbBomSize = AdCharFormatter::getBOM(nBom, 
                                this->getCharFormat());
    if (cbBomSize == 0) // AdcharFormatter::getBOM would
        return false;   // have brought up an assertion.

    this->Write(&nBom, cbBomSize);
    return true;
}

inline bool AcCFile::attachBuffer(void *pBuffer, unsigned nBufSize)
{
    return this->mOutputBufMgr.attachBuffer(pBuffer, nBufSize);
}

inline bool AcCFile::detachBuffer()
{
    return this->mOutputBufMgr.detachBuffer();
}

inline bool AcCFile::hasBuffer() const
{
    return this->mOutputBufMgr.hasBuffer();
}

inline bool AcCFile::flushBytes()
{
    AcCFile_Assert(this->hasBuffer());
    if (!this->hasBuffer())
        return false;
    const unsigned nBytes = this->mOutputBufMgr.byteCount();
    if (nBytes != 0) {
        const void *pBuf = this->mOutputBufMgr.pointer();
        this->Write(pBuf, nBytes);
    }
    this->mOutputBufMgr.reset();
    return true;
}

#ifdef UNICODE
inline void acByteSwap(wchar_t &wch)
{
    // the &-ing is probably unnecessary, but it doesn't hurt
    const wchar_t lobits = (wch >> 8) & 0x00ff;
    const wchar_t hibits = (wch << 8) & 0xff00;
    wch = lobits | hibits;
}

inline bool acReadCIFFromCFile(CFile *pCFile, wchar_t &wch)
{
    // leading slash has already been read.  See if we can read
    // a \U+xxxx or \M+nxxyy sequence.
    const ULONGLONG nCurPos = pCFile->GetPosition();
    char chbuf[9];
    chbuf[0] = '\\';    // set up for formatting function
    // try reading 6 more, assuming its CIF.  If it looks like
    // MIF, then read one more.
    const unsigned nCharRead = pCFile->Read(chbuf+1, 1);
    AcCFile_Assert(nCharRead <= 1);
    if (nCharRead == 1) {
        if (chbuf[1] == 'U' || chbuf[1] == 'u') {
            // read five more chars, to get "+xxxx"
            const unsigned nMoreCharsRead = pCFile->Read(chbuf+2, 5);
            AcCFile_Assert(nMoreCharsRead <= 5);
            chbuf[2 + nMoreCharsRead] = 0;   // null terminate it
            if (AdCharFormatter::isCIFString(chbuf))
                if (AdCharFormatter::parseCIF(chbuf, wch))
                    return true;
        }
        else if (chbuf[1] == 'M' || chbuf[1] == 'm') {
            // read six more chars, to get "+nxxyy"
            const unsigned nMoreCharsRead = pCFile->Read(chbuf+2, 6);
            AcCFile_Assert(nMoreCharsRead <= 6);
            chbuf[2 + nMoreCharsRead] = 0;   // null terminate it
            if (AdCharFormatter::isCIFString(chbuf))
                if (AdCharFormatter::parseCIF(chbuf, wch))
                    return true;
        }
    }
    // If got here, then no MIF or CIF
    pCFile->Seek(nCurPos, SEEK_SET);   // restore file pointer
    return false;       // no CIF found
}

inline bool acReadAnsiCharFromCFile(CFile *pCFile, wchar_t &wch, AdCharFormatter *pChFmtr)
{
    char chbuf[2];
    const bool bUseCIF = pChFmtr->getUseCIF();
    // Note: we are here calling the Read method which takes a
    // void * argument.  If pCFile is an AcCFile object, then
    // we end up in AcCFile::Read, which then calls CFile::Read.
    // If pCFile is an AcCStdioFile, then we end up in
    // CFile::Read immediately.
    //
    // Note also about Read(): if the file is open as a text
    // file, then \r\n are automatically converted to \n.  But
    // if file is opened as binary, then the \r and \n come
    // back separately.  That is probably not desired by the caller,
    // but that's the way it work.  If they don't like it, they
    // should open the file as text.
    //
    const int nCharsRead = pCFile->Read(chbuf, 1);
    if (nCharsRead <= 0)
        return false;   // probably end of file
    AcCFile_Assert(nCharsRead == 1);
	
    if (chbuf[0] >= 0 && static_cast<unsigned char>(chbuf[0]) <= 0x7f) {
        wch = chbuf[0];
        if (chbuf[0] == '\r' && pChFmtr->getExpandLF()) {
            unsigned char newLine = 0;
            const int nBytesRead = pCFile->Read(&newLine, 1);
            if (nBytesRead < 1)     // '\r' at the end of file...
                return true;        // ... weird but we'll take it.
            if (newLine != '\n') {  // Not a new line character!
                pCFile->Seek(-1L, CFile::current);
                return true;        // Return '\r' as it is...
            }
            wch = L'\n'; // Translated to new line character.
        }
        if (chbuf[0] == '\\' && bUseCIF && acReadCIFFromCFile(pCFile, wch))
            return true;    // wch has the native char gotten from CIF
        return true;
    }
    bool bDoubleByte = false;
    if (::IsDBCSLeadByte(chbuf[0])) {
        const int nTrailingCharsRead = pCFile->Read(chbuf+1, 1);
        AcCFile_Assert(nTrailingCharsRead == 1);
        if (nTrailingCharsRead != 1) {
            // malformed file, ends halfway through a doublebyte char!
            // should we throw an exception?
            return false;
        }
        bDoubleByte = true;
    }
    const int nConverted = ::MultiByteToWideChar(
                        CP_ACP,
                        0,      // flags
                        chbuf,
                        bDoubleByte ? 2 : 1,
                        &wch,
                        1);
    AcCFile_Assert(nConverted == 1);
    if (nConverted != 1) {
        // error condition?
    }
    return true;
}

inline bool acReadUtf8CharFromCFile(CFile *pCFile, 
                                    wchar_t &wch, 
                                    AdCharFormatter *pChFmtr)
{
    char chbuf[4];
    wch = 0;

    // Note: UTF-8 encodes a single character in 1 to 4 bytes. 
    // The following bit patterns in the first byte determine the 
    // length of bytes that a particular character was encoded in:
    // 
    // 0xxxxxxx (0x7F): Character that takes up one byte.
    // 110xxxxx (0xC0): Character that takes up two bytes.
    // 1110xxxx (0xE0): Character that takes up tree bytes.
    // 11110xxx (0xF0): Character that takes up four bytes.
    //

    unsigned nCharsRead = pCFile->Read(chbuf, 1);
    if (nCharsRead <= 0)
        return false;   // probably end of file
    AcCFile_Assert(nCharsRead == 1);

    unsigned nByteCount = 1;
    unsigned char firstByte = (unsigned char) chbuf[0];

    // Characters that taking up one byte.
    if (!(firstByte & 0x80)) // Highest bit not set.
    {
        wch = (wchar_t) firstByte;
        if (firstByte == '\r' && pChFmtr->getExpandLF()) {
            unsigned char newLine = 0;
            const int nBytesRead = pCFile->Read(&newLine, 1);
            if (nBytesRead < 1)     // '\r' at the end of file...
                return true;        // ... weird but we'll take it.
            if (newLine != '\n') {  // Not a new line character?
                pCFile->Seek(-1L, CFile::current);
                return true;        // Return '\r' as it is...
            }
            wch = L'\n'; // Translated to new line character.
        }
        return true;
    }

    // Characters that taking up multiple bytes. Note the sequence 
    // of checking for these bits is important, always start with 
    // 0xF0 and later move on to a lower value. (For an example the 
    // case of 0xF0, it will be true for all these test cases.)
    if ((firstByte & 0xF0) == 0xF0)
        nByteCount = 4;
    else if ((firstByte & 0xE0) == 0xE0)
        nByteCount = 3;
    else if ((firstByte & 0xC0) == 0xC0)
        nByteCount = 2;

    // Read the remaining bytes to complete the character.
    if(nByteCount > 1)
    {
        nCharsRead = pCFile->Read(&chbuf[1], nByteCount - 1);
        AcCFile_Assert(nCharsRead >= 1);
        AcCFile_Assert(nCharsRead == (nByteCount - 1));
    }

    const int nConverted = ::MultiByteToWideChar(
                                CP_UTF8, 
                                0, 
                                chbuf, 
                                nByteCount, 
                                &wch, 
                                1);

    // Unicode: If we frequently encounter ill-formed UTF8 file, 
    // we might want to consider returning false instead of bringing 
    // up an assertion.
    AcCFile_Assert(nConverted == 1);
    if (nConverted != 1) {
        // error condition?
    }
    return true;
}

inline bool acReadUtf16CharFromCFile(CFile *pCFile, 
                                     wchar_t &wch, 
                                     AdCharFormatter *pChFmtr)
{
    AcCFile_Assert(pChFmtr != NULL);
    const int nCharsRead = pCFile->Read(&wch, 2);
    if (nCharsRead < 2) {
        wch = 0;        // (or we could set it to -1)
        return false;   // Probably end of file.
    }

    AcCFile_Assert(nCharsRead == 2);
    const unsigned nFileFormat = pChFmtr->getFormat();

    // Perform a byte swap for Big Endian case.
    if (nFileFormat == AdCharFormatter::kUtf16BE)
        acByteSwap(wch);

    // New line expansion expected, read next wchar_t.
    if (wch == L'\r' && pChFmtr->getExpandLF()) {
        wchar_t wchNewLine = 0;
        const int nBytesRead = pCFile->Read(&wchNewLine, 2);
        if (nBytesRead < 2) // '\r' at the end of file?
            return true;    // Weird, but we'll take it as it is.
        if (nFileFormat == AdCharFormatter::kUtf16BE)
            acByteSwap(wchNewLine);
        if (wchNewLine != '\n') { // Not a new line? Back-off!
            pCFile->Seek(-2L, CFile::current);
            return true; // Take '\r' as it is.
        }
        wch = '\n'; // Translated to new line.
        return true;
    }

    return true;
}
#endif

inline UINT AcCFile::Read(LPTSTR lpBuf, UINT nCount)
{
#ifndef UNICODE
    return this->CFile::Read(lpBuf, nCount);
#else
    // read a char at a time, converting to unicode and
    // appending to the buffer or CString
    UINT nDestIndex = 0;
    for (;;) {
        AcCFile_Assert(nDestIndex <= nCount);
        if (nDestIndex == nCount)
            break;
        wchar_t wch = 0;
        bool bReadOk = false;
        switch(this->mChFmtr.getFormat())
        {
          case AdCharFormatter::kAnsi:
            bReadOk = ::acReadAnsiCharFromCFile(this, wch, &(this->mChFmtr)); 
            break;
          case AdCharFormatter::kUtf8:
            bReadOk = ::acReadUtf8CharFromCFile(this, wch, &(this->mChFmtr));
            break;
          case AdCharFormatter::kUtf16LE:
          case AdCharFormatter::kUtf16BE:
            bReadOk = ::acReadUtf16CharFromCFile(this, wch, &(this->mChFmtr));
            break;
        }

        if (!bReadOk)
            break;  // end of file or error
        lpBuf[nDestIndex] = wch;
        nDestIndex++;
    }
    return nDestIndex;   // also is number of wchars read
#endif
}

#ifdef _ADESK_WINDOWS_
// CStdioFile::Write() will expand LFs if the file is open
// as typeText.  It will leave them unexpanded if it's open
// as typeBinary.  Since we send our chars to this Write()
// method, the LF expansion is handled for us and we want to
// disable our own LF expansion.  Thus, expandLF is set to false.
//
inline AcCStdioFile::AcCStdioFile()
        : mChFmtr(AdCharFormatter::kAnsi,
                  true,       // useCIF
                  false)      // expandLF
{
}

inline AcCStdioFile::AcCStdioFile(FILE* pOpenStream)
        : CStdioFile(pOpenStream),
          mChFmtr(AdCharFormatter::kAnsi,
                  true,       // useCIF
                  false)      // expandLF
{
}

inline AcCStdioFile::AcCStdioFile(LPCTSTR lpszFileName, UINT nOpenFlags)
        : CStdioFile(lpszFileName, nOpenFlags),
          mChFmtr(AdCharFormatter::kAnsi,
                  true,       // useCIF
                  false)      // expandLF
{
}

inline AcCStdioFile::~AcCStdioFile()
{
}

inline void AcCStdioFile::WriteString(LPCTSTR lpsz)
{
#ifndef UNICODE
    this->CStdioFile::WriteString(lpsz);
#else
    const bool bHasBuffer = this->hasBuffer();
    for (;;) {
        const wchar_t wch = *lpsz;
        if (wch == L'\0')
            break;
        if (!bHasBuffer)
            ::acWriteWCharToCFile(wch, this, this->mChFmtr);
        else {
            // worst case is 8 bytes (utf-32 cr-lf)
            const int kReservedSize = 8;
            void *pOutBuf = this->mOutputBufMgr.requestBytes(kReservedSize);
            const int nBytes = this->mChFmtr.wcharToBytes(wch,
                                        reinterpret_cast<char *>(pOutBuf),
                                        kReservedSize);
            AcCFile_Assert(nBytes >= 1);
            AcCFile_Assert(nBytes <= kReservedSize);
            const unsigned nBytesLeft = this->mOutputBufMgr.takeBytes(nBytes);
            if (nBytesLeft <= kReservedSize)
                this->flushBytes();
        }
        lpsz++;
    }
                              
#endif
}

// nMax is the maximum number of characters to read, not counting
// the null terminator.  This method always appends a null terminator.
// Thus, nMax should be one less than the size of the Buffer.
inline LPTSTR AcCStdioFile::ReadString(LPTSTR lpsz, UINT nMax)
{
#ifndef UNICODE
    return this->CStdioFile::ReadString(lpsz, nMax);
#else
    AcCFile_Assert(lpsz != NULL);
    AcCFile_Assert(nMax >= 1);
    if (nMax < 1)
        return NULL;

    // read a char at a time, converting to unicode and
    // appending to the buffer
    bool bGotAnyData = false;
    UINT nDestIndex = 0;
    for (;;) {
        AcCFile_Assert(nDestIndex < nMax - 1);
        if (nDestIndex >= nMax - 1)
            break; // -1 for null character.
        wchar_t wch = 0;
        bool bReadOk = false;
        switch(this->mChFmtr.getFormat())
        {
          case AdCharFormatter::kAnsi:
            bReadOk = ::acReadAnsiCharFromCFile(this, wch, &(this->mChFmtr)); 
            break;
          case AdCharFormatter::kUtf8:
            bReadOk = ::acReadUtf8CharFromCFile(this, wch, &(this->mChFmtr));
            break;
          case AdCharFormatter::kUtf16LE:
          case AdCharFormatter::kUtf16BE:
            bReadOk = ::acReadUtf16CharFromCFile(this, wch, &(this->mChFmtr));
            break;
        }

        if (!bReadOk)
            break;  // end of file or error
        lpsz[nDestIndex] = wch;
        nDestIndex++;
        bGotAnyData = true;
        if (wch == L'\n' || nDestIndex >= nMax - 1)
            break;      // buffer is full
    }
    AcCFile_Assert(nDestIndex < nMax);
    lpsz[nDestIndex] = 0;  // null terminate it
    return bGotAnyData ? lpsz : NULL;
#endif
}

inline BOOL AcCStdioFile::ReadString(CString& rString)
{
#ifndef UNICODE
    return this->CStdioFile::ReadString(rString);
#else
    rString.Empty();

    // read a char at a time, converting to unicode and
    // appending to the CString
    bool bGotAnyData = false;
    for (;;) {
        wchar_t wch = 0;
        bool bReadOk = false;
        switch(this->mChFmtr.getFormat())
        {
          case AdCharFormatter::kAnsi:
            bReadOk = ::acReadAnsiCharFromCFile(this, wch, &(this->mChFmtr));
            break;
          case AdCharFormatter::kUtf8:
            bReadOk = ::acReadUtf8CharFromCFile(this, wch, &(this->mChFmtr));
            break;
          case AdCharFormatter::kUtf16LE:
          case AdCharFormatter::kUtf16BE:
            bReadOk = ::acReadUtf16CharFromCFile(this, wch, &(this->mChFmtr));
            break;
        }

        if (!bReadOk)
            break; // end of file or error
        bGotAnyData = true;   // at least one char was read
        if (wch == L'\n')
            break;   // the newline doesn't go into the CString
        rString.AppendChar(wch);
    }
    return bGotAnyData;
#endif
}

inline bool AcCStdioFile::readBOM()
{
    const ULONGLONG dwPosition = this->GetPosition();
    AcCFile_Assert(dwPosition == 0);
    if (dwPosition != 0)
        return false; // Can't do this unless we're at start of file.

    unsigned short nVal;
    if (this->Read(&nVal, 2) == 2) {
        if (nVal == 0xfeff) {
            this->setCharFormat(AdCharFormatter::kUtf16LE);
            return true;
        }
        if (nVal == 0xfffe) {
            this->setCharFormat(AdCharFormatter::kUtf16BE);
            return true;
        }
        if (nVal == 0xbbef) {
            unsigned char nByte3;
            if (this->Read(&nByte3, 1) == 1) {
                if (nByte3 == 0xbf) {
                    this->setCharFormat(AdCharFormatter::kUtf8);
                    return true;
                }
            }
        }
        else if (nVal == 0 || nVal == 0xfeff) {
            unsigned nVal2;
            if (this->Read(&nVal2, 2) == 2) {
                if (nVal == 0 && nVal2 == 0xfffe) {
                    this->setCharFormat(AdCharFormatter::kUtf32BE);
                    return true;
                }
                else if (nVal == 0xfeff && nVal2 == 0) {
                    this->setCharFormat(AdCharFormatter::kUtf32LE);
                    return true;
                }
            }
        }
    }

    // If got here, then no BOM found, so reset 
    // to file beginning. Leave format what it was.
    this->SeekToBegin();
    return false;
}

inline bool AcCStdioFile::writeBOM()
{
    AcCFile_Assert((this->m_hFile) != CFile::hFileNull);
    if ((this->m_hFile) == CFile::hFileNull)
        return false; // There must be an associated file.

    const ULONGLONG dwPosition = this->GetPosition();
    AcCFile_Assert(dwPosition == 0);
    if (dwPosition != 0)
        return false; // Can't do this unless we're at start of file.

    unsigned nBom = 0;
    const int cbBomSize = AdCharFormatter::getBOM(nBom, 
                                this->getCharFormat());
    if (cbBomSize == 0) // AdcharFormatter::getBOM would
        return false;   // have brought up an assertion.

    this->Write(&nBom, cbBomSize);
    return true;
}

inline bool AcCStdioFile::attachBuffer(void *pBuffer, unsigned nBufSize)
{
    return this->mOutputBufMgr.attachBuffer(pBuffer, nBufSize);
}

inline bool AcCStdioFile::detachBuffer()
{
    return this->mOutputBufMgr.detachBuffer();
}

inline bool AcCStdioFile::hasBuffer() const
{
    return this->mOutputBufMgr.hasBuffer();
}

inline bool AcCStdioFile::flushBytes()
{
    AcCFile_Assert(this->hasBuffer());
    if (!this->hasBuffer())
        return false;
    const unsigned nBytes = this->mOutputBufMgr.byteCount();
    if (nBytes != 0) {
        const void *pBuf = this->mOutputBufMgr.pointer();
        this->Write(pBuf, nBytes);
    }
    this->mOutputBufMgr.reset();
    return true;
}
#endif //_ADESK_WINDOWS_ MAC_PORT
#pragma warning(pop)

