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
// Name:            AdCharFmt.h
//
// Description:     Enums and utility functions for dealing with
//                  various char formats (ansi, utf-8, etc)
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "adesk.h"
#include "casuppress.h"
#pragma warning(push, 4)

#ifdef ASSERT
#define AdCharFmt_Assert ASSERT
#elif defined assert
#define AdCharFmt_Assert assert
#elif defined _ASSERTE
#define AdCharFmt_Assert _ASSERTE
#else
#define AdCharFmt_Assert(x)
#endif
#include "acbasedefs.h"
#include "PAL/api/codepgid.h"
#include <stddef.h>

class AdCharFormatter
{
  public:
    enum {
        kUnknown = 0, 
        kAnsi, 
        // kAnsiCIF,   should this be a separate type?
        kUtf8,
        kUtf16LE, 
        kUtf16BE,
        kUtf32LE,
        kUtf32BE
    };
    AdCharFormatter(unsigned nFormat, bool bUseCIF, bool bExpandLF) :
                    mnFormat(nFormat), mbUseCIF(bUseCIF),
                    mbExpandLF(bExpandLF)
    {
        // doesn't make sense to ask for CIF with non-ansi format
        AdCharFmt_Assert(this->mbUseCIF == false || this->mnFormat == kAnsi);
    }

    // by default, we assume ansi and we *do* expand lfs into cr-lf
    AdCharFormatter() : mnFormat(kAnsi), mbUseCIF(false),
                        mbExpandLF(true) {}

    // This function assumes you are passing it the first four
    // bytes of the input file for examination.
    static unsigned lookupBOM(unsigned nBom)
    {
        if ((nBom & 0x00ffffff) == 0xbfbbef)
            return kUtf8;
        if ((nBom & 0x0000ffff) == 0xfeff)
            return kUtf16LE;
        if ((nBom & 0x0000ffff) == 0xfffe)
            return kUtf16BE;
        if (nBom == 0x0000feff)
            return kUtf32LE;
        if (nBom == 0xfffe0000)
            return kUtf32BE;
        return kUnknown;
    }

    // Writes the BOM for the given format into the dword and returns
    // its length.
    static int getBOM(unsigned &nBom, unsigned nFmt)
    {
        if (nFmt == kUtf8) {
            nBom = 0xbfbbef;
            return 3;
        }
        else if (nFmt == kUtf16LE) {
            nBom = 0xfeff;
            return 2;
        }
        else if (nFmt == kUtf16BE) {
            nBom = 0xfffe;
            return 2;
        }
        else if (nFmt == kUtf32LE) {
            nBom = 0x0000feff;
            return 4;
        }
        else if (nFmt == kUtf32BE) {
            nBom = 0xfffe0000;
            return 4;
        }
        else {
            AdCharFmt_Assert(nFmt == kUnknown || nFmt == kAnsi);
            return 0;   // ansi or unknown
        }
    }

    // Inserts 7 CIF chars of the form "\U+xxxx" into the destination
    // buffer.  Assumes there is room in the buffer.  Does *not*
    // append a null terminator.
    template <class ChType> static void putCIF(wchar_t wch, ChType *pDest)
    {
        pDest[0] = '\\';
        pDest[1] = 'U';
        pDest[2] = '+';
        for (int i = 0; i < 4; i++) {
            const ChType n = (ChType)(wch & 0xf); // Lowest 4 bits
            pDest[6 - i] = (n <= 9) ? ('0' + n) : ('A' - 10 + n);
            wch >>= 4;
        }
    }

    // Non-static methods for getting and setting local state.
    //
    bool getUseCIF() const { return this->mbUseCIF; }
    bool getExpandLF() const { return this->mbExpandLF; }
    unsigned getFormat() const { return this->mnFormat; }

    bool setUseCIF(bool bUseCIF) {
        const bool bOldUseCIF = this->mbUseCIF;
        this->mbUseCIF = bUseCIF;
        return bOldUseCIF;
    }
    bool setExpandLF(bool bExpandLF) {
        const bool bOldExpandLF = this->mbExpandLF;
        this->mbExpandLF = bExpandLF;
        return bOldExpandLF;
    }
    unsigned setFormat(unsigned nFormat) {
        const unsigned nOldFormat = this->mnFormat;
        this->mnFormat = nFormat;
        return nOldFormat;
    }

    // Static method to get length of a widechar string.
    static unsigned wcsLength(const wchar_t * pStr)
    {
        unsigned nLen = 0;
        while (*pStr != L'\0') {
            nLen++;
            pStr++;
        }
        return nLen;
    }

    // Static method
    // Requires dest buf is 2 chars for ansi, 4 for utf-8, 7 for ansi+CIF
    // Returns number of bytes put into buffer.
    static ACBASE_PORT unsigned wcharToAnsiOrUtf8(wchar_t wch, char *pDestBuf,
        unsigned nDestBufSize,
        bool bToAnsi,
        bool bUseCIF, bool bExpandLF);

    // static method to output utf-16
    static ACBASE_PORT unsigned wcharToUtf16(wchar_t wch,
        char * pDestBuf,
        unsigned nDestBufSize,
        bool bLittleEndian,
        bool bExpandLF);

    // Non-static method.  Uses local state info.
    // Returns number of bytes put into buffer.  Returns 0 if error.
    unsigned wcharToBytes(wchar_t wch, char *pDestBuf,
                          unsigned nDestBufSize) const
    {
        if (this->mnFormat == kAnsi || this->mnFormat == kUtf8)
            return wcharToAnsiOrUtf8(wch, pDestBuf, nDestBufSize,
                                     this->mnFormat == kAnsi,
                                     this->mbUseCIF, this->mbExpandLF);
        else if (this->mnFormat == kUtf16LE || this->mnFormat == kUtf16BE) {
            AdCharFmt_Assert(!this->mbUseCIF);
            return wcharToUtf16(wch, pDestBuf, nDestBufSize,
                                this->mnFormat == kUtf16LE,
                                this->mbExpandLF);
        }
        else {
            AdCharFmt_Assert(!this->mbUseCIF);
            AdCharFmt_Assert(nDestBufSize >= 4);
            AdCharFmt_Assert(this->mnFormat == kUtf32LE ||
                             this->mnFormat == kUtf32BE);
            AdCharFmt_Assert(this->mnFormat != kUtf32LE); // not implemented!
            AdCharFmt_Assert(this->mnFormat != kUtf32BE); // not implemented!
            return 0;
        }
    }

    template <class ChType> static bool isHex(ChType ch)
    {
        // true if in range 0..9, a..f or A..F
        return (ch >= '0' && ch <= '9') ||
               (ch >= 'A' && ch <= 'F') ||
               (ch >= 'a' && ch <= 'f');
    }

    template <class ChType> static bool isHex(ChType ch, unsigned &uVal)
    {
        if (ch >= '0' && ch <= '9') {
            uVal = ch - '0';
            AdCharFmt_Assert(uVal <= 9);
            return true;
        }
        if (ch >= 'A' && ch <= 'F') {
            uVal = ch - 'A' + 10;
            AdCharFmt_Assert(uVal >= 10);
            AdCharFmt_Assert(uVal <= 15);
            return true;
        }
        if (ch >= 'a' && ch <= 'f') {
            uVal = ch - 'a' + 10;
            AdCharFmt_Assert(uVal >= 10);
            AdCharFmt_Assert(uVal <= 15);
            return true;
        }
        return false;
    }

    // Static method. 
    // Returns true if pSrcBuf contains a CIF sequence, or false otherwise.
    // Assumes the string is null terminated
    template <class ChType> static bool isCIFString(const ChType *pSrcBuf)
    {
        AdCharFmt_Assert(pSrcBuf != NULL);

        // look for \U+xxxx
        if (pSrcBuf[0] == '\\' &&
                (pSrcBuf[1] == 'U' || pSrcBuf[1] == 'u') && 
                pSrcBuf[2] == '+' && 
                isHex<ChType>(pSrcBuf[3])  && 
                isHex<ChType>(pSrcBuf[4])  && 
                isHex<ChType>(pSrcBuf[5])  && 
                isHex<ChType>(pSrcBuf[6]))
            return true;

        return false;
    }

    // Takes a string length arg instead of assuming it's null terminated
    template <class ChType> static bool isCIFString(
                    const ChType *pSrcBuf, unsigned nSrcBufSize)
    {
        AdCharFmt_Assert(pSrcBuf != NULL);
        AdCharFmt_Assert(nSrcBufSize > 0);
        if(nSrcBufSize < 7)
            return false;
        return isCIFString<ChType>(pSrcBuf);
    }

    // Static method. Parse a wide character from a CIF string.
    // Returns true if parsing is successful, or false otherwise.
    template <class ChType> static bool parseCIF(
                        const ChType *pSrcBuf, wchar_t &wch)
    {
        AdCharFmt_Assert(pSrcBuf != NULL);
        if(pSrcBuf == NULL)
            return false;

        // look for "\U+"
        if (pSrcBuf[0] != '\\' || (pSrcBuf[1] != 'U' && pSrcBuf[1] != 'u') || pSrcBuf[2] != '+')
            return false;

        // look for 4 hex digits
        unsigned uVal;
        if (!isHex<ChType>(pSrcBuf[3], uVal))
            return false;
        wch = (wchar_t)(uVal << 12);
        if (!isHex<ChType>(pSrcBuf[4], uVal))
            return false;
        wch |= (wchar_t)(uVal << 8);
        if (!isHex<ChType>(pSrcBuf[5], uVal))
            return false;
        wch |= (wchar_t)(uVal << 4);
        if (!isHex<ChType>(pSrcBuf[6], uVal))
            return false;
        wch |= (wchar_t)uVal;

        return true;
    }

    // Static method. 
    // Returns true if pSrcBuf contains a MIF sequence, or false otherwise.
    // Assumes the string is null terminated
    template <class ChType> static bool isMIFString(const ChType *pSrcBuf)
    {
        AdCharFmt_Assert(pSrcBuf != NULL);

        // look for \M+nxxyy, where n is 1..5, x and y are hex digits
        if (pSrcBuf[0] == '\\' &&
                (pSrcBuf[1] == 'M' || pSrcBuf[1] == 'm')  && 
                pSrcBuf[2] == '+'  && 
                pSrcBuf[3] >= '1'  && 
                pSrcBuf[3] <= '5'  && 
                isHex<ChType>(pSrcBuf[4])  && 
                isHex<ChType>(pSrcBuf[5])  && 
                isHex<ChType>(pSrcBuf[6])  && 
                isHex<ChType>(pSrcBuf[7]))
            return true;

        return false;
    }

    // Takes a string length arg instead of assuming it's null terminated
    template <class ChType> static bool isMIFString(const ChType *pSrcBuf,
                unsigned nSrcBufSize)
    {
        AdCharFmt_Assert(pSrcBuf != NULL);
        AdCharFmt_Assert(nSrcBufSize > 0);
        if(nSrcBufSize < 8)
            return false;
        return isMIFString<ChType>(pSrcBuf);
    }

    static unsigned winCodePageFromMIFIndex(unsigned nIdx)
    {
        return nIdx == 1 ? 932 :
               nIdx == 2 ? 950 :
               nIdx == 3 ? 949 :
               nIdx == 4 ? 1361 :
               nIdx == 5 ? 936 : 0;
    }

    static code_page_id codePageIdFromMIFIndex(uint8_t nIdx)
    {
        return nIdx == 1 ? code_page_id::CODE_PAGE_DOS932 :
            nIdx == 2 ? code_page_id::CODE_PAGE_BIG5 :
            nIdx == 3 ? code_page_id::CODE_PAGE_KSC5601 :
            nIdx == 4 ? code_page_id::CODE_PAGE_JOHAB :
            nIdx == 5 ? code_page_id::CODE_PAGE_GB2312 : code_page_id::CODE_PAGE_CURRENT;
    }

    static unsigned char MIFIndexFromWinCodePage(unsigned nCodePage)
    {
        return nCodePage == 932 ? 1 :
               nCodePage == 950 ? 2 :
               nCodePage == 949 ? 3 :
               nCodePage == 1361 ? 4 :
               nCodePage == 936 ? 5 : 0;
    }

    static uint8_t MIFIndexFromCodePageId(code_page_id codePageId)
    {
        switch (codePageId) {
        case code_page_id::CODE_PAGE_DOS932:
        case code_page_id::CODE_PAGE_ANSI_932:
            return 1;
        case code_page_id::CODE_PAGE_BIG5:
        case code_page_id::CODE_PAGE_ANSI_950:
            return 2;
        case code_page_id::CODE_PAGE_KSC5601:
        case code_page_id::CODE_PAGE_ANSI_949:
            return 3;
        case code_page_id::CODE_PAGE_JOHAB:
        case code_page_id::CODE_PAGE_ANSI_1361:
            return 4;
        case code_page_id::CODE_PAGE_GB2312:
        case code_page_id::CODE_PAGE_ANSI_936:
            return 5;
        default:
            return 0;
        }
    }

    // To be obsoleted.
    // The public API is retained. But will be obsolted. Use putMIF() the code_page_id version instead.
    // Assumes output buffer is at least 8 chars.  Returns true
    // if widechar converted to MIF, false otherwise.
    
    template <class ChType> ADESK_DEPRECATED static bool putMIF(wchar_t wch,
                                ChType *pMbOut, unsigned nWinCodePage)
    {
        const unsigned char nMIFIndex = MIFIndexFromWinCodePage(nWinCodePage);
        if (nMIFIndex == 0)
            return false;
        AdCharFmt_Assert(nMIFIndex >= 1);
        AdCharFmt_Assert(nMIFIndex <= 5);
        char mbBuf[2];
        const int nMbChars = isNativeToCodePage(wch, nWinCodePage, mbBuf, 2);
        if (nMbChars == 0)
            return false;
        if (nMbChars == 1) {
            mbBuf[1] = mbBuf[0];  // put '0' followed by the char
            mbBuf[0] = 0;
        }
        AdCharFmt_Assert(nMbChars <= 2);
        pMbOut[0] = '\\';
        pMbOut[1] = 'M';
        pMbOut[2] = '+';
        pMbOut[3] = '0' + nMIFIndex;
        unsigned nNibs[4];
        nNibs[0] = mbBuf[0] >> 4;
        nNibs[1] = mbBuf[0];
        nNibs[2] = mbBuf[1] >> 4;
        nNibs[3] = mbBuf[1];
        for (int i = 0; i < 4; i++) {
            const ChType n = (ChType)(nNibs[i] & 0xf); // Lowest 4 bits
            pMbOut[4 + i] = (n <= 9) ? ('0' + n) : ('A' - 10 + n);
        }
        return true;
    }

    // Assumes output buffer is at least 8 chars.  Returns true
    // if widechar converted to MIF, false otherwise.
    template <class ChType> static bool putMIF(wchar_t wch,
        ChType *pMbOut, code_page_id codePageId)
    {
        const auto nMIFIndex = MIFIndexFromCodePageId(codePageId);
        if (nMIFIndex == 0)
            return false;
        AdCharFmt_Assert(nMIFIndex >= 1);
        AdCharFmt_Assert(nMIFIndex <= 5);
        char mbBuf[2];
        const int nMbChars = isNativeToCodePageId(wch, codePageId, mbBuf, 2);
        if (nMbChars == 0)
            return false;
        if (nMbChars == 1) {
            mbBuf[1] = mbBuf[0];  // put '0' followed by the char
            mbBuf[0] = 0;
        }
        AdCharFmt_Assert(nMbChars <= 2);
        pMbOut[0] = '\\';
        pMbOut[1] = 'M';
        pMbOut[2] = '+';
        pMbOut[3] = '0' + nMIFIndex;
        unsigned nNibs[4];
        nNibs[0] = mbBuf[0] >> 4;
        nNibs[1] = mbBuf[0];
        nNibs[2] = mbBuf[1] >> 4;
        nNibs[3] = mbBuf[1];
        for (int i = 0; i < 4; i++) {
            const ChType n = (ChType)(nNibs[i] & 0xf); // Lowest 4 bits
            pMbOut[4 + i] = (n <= 9) ? ('0' + n) : ('A' - 10 + n);
        }
        return true;
    }

    // Returns 0 if input char doesn't represent a valid MIF codepage
    template <class ChType> static unsigned getMIFCodePage(ChType ch)
    {
        return
                ch == '1' ?  932  :  // Shift-JIS (Japanese)
                ch == '2' ?  950  :  // Big-5 (Traditional Chinese)
                ch == '3' ?  949  :  // KS C-5601-1987 (Wansung)
                ch == '4' ? 1361  :  // KS C-5601-1992 (Johab)
                ch == '5' ?  936  :  // GB 2312-80 (Simplified Chinese)
                0;
    }

    // Returns 0 if input char doesn't represent a valid MIF codepage
    template <class ChType> static code_page_id getMIFCodePageId(ChType ch)
    {
        return
            ch == '1' ? code_page_id::CODE_PAGE_DOS932 :  // Shift-JIS (Japanese)
            ch == '2' ? code_page_id::CODE_PAGE_BIG5 :  // Big-5 (Traditional Chinese)
            ch == '3' ? code_page_id::CODE_PAGE_KSC5601 :  // KS C-5601-1987 (Wansung)
            ch == '4' ? code_page_id::CODE_PAGE_JOHAB :  // KS C-5601-1992 (Johab)
            ch == '5' ? code_page_id::CODE_PAGE_GB2312 :  // GB 2312-80 (Simplified Chinese)
            code_page_id::CODE_PAGE_UNDEFINED;
    }

    // Static method. Parse a wide character from a MIF string.
    // Returns true if parsing is successful, or false otherwise.
    template <class ChType> static bool parseMIF(const ChType *pSrcBuf,
                                                 wchar_t &wch)
    {
        // Convert the given MIF sequence \M+xyyzz to wide character. 
        // x represents the index into the code page array, and yy 
        // represents the lower order byte in a DBCS character, where 
        // zz represents the higher order byte in a DBCS character.

        AdCharFmt_Assert(pSrcBuf != NULL);
        if (pSrcBuf == NULL)
            return false;

        if (pSrcBuf[0] != '\\' || (pSrcBuf[1] != 'M' && pSrcBuf[1] != 'm') || pSrcBuf[2] != '+')
            return false;

        const auto codePageId = getMIFCodePageId<ChType>(pSrcBuf[3]);
        if (code_page_id::CODE_PAGE_UNDEFINED == codePageId)
            return false;       // didn't get a code page

        char mbBuf[2];
        unsigned uVal;
        if (!isHex<ChType>(pSrcBuf[4], uVal))
            return false;
        mbBuf[0] = (char)(uVal << 4);   // leading byte's high nibble
        if (!isHex<ChType>(pSrcBuf[5], uVal))
            return false;
        mbBuf[0] |= (char)uVal;       // leading byte's low nibble

        if (!isHex<ChType>(pSrcBuf[6], uVal))
            return false;
        mbBuf[1] = (char)(uVal << 4);   // trailing byte's high nibble
        if (!isHex<ChType>(pSrcBuf[7], uVal))
            return false;
        mbBuf[1] |= (char)(uVal);       // trailing byte's low nibble

        // If leading byte is zero, then it's a single byte ansi char
        // That is, "\M+n00xx" is treated as a single byte char.
        //
        // Note, if we get "\M+nxx00", then it will translate xx
        // as a single byte char (if possible) and then will
        // append a null terminator.
        //
        if (mbBuf[0] == 0) {
            mbBuf[0] = mbBuf[1];
            mbBuf[1] = 0;
        }

        extern bool convertMBStringToOneWideChar(code_page_id codePageId, char* mbBuf, int mbLen, wchar_t& wch);
        return convertMBStringToOneWideChar(codePageId, mbBuf, mbBuf[1] == 0 ? 1 : 2, wch);
    }

    // To be obsoleted.
    // The public API is retained. But will be obsolted. Use isNativeToCodePageId() instead.
    //
    // Static method. Determine if a given wide character is native 
    // to the given code page value.
    //
    // Note: if pChNative is non-null, it should be pointing to a
    // char buff, in case the native char is double-byte.
    // If the pChNative is null, it will return the length of the buffer
    // it needs to convert this wch to MBCS.
    //
    // Return value:
    // This method returns number of bytes in the equivalent MBCS 
    // character. If the return value is zero, wch is not native to 
    // code page specified by nCodePage parameter. If the return value is -1,
    // The destination buffer length is not enough.
    // 
    static ACBASE_PORT int isNativeToCodePage(wchar_t wch,  // Input wide char.
                                             unsigned nCodePage,     // Code page, can be CP_ACP
                                             char *pChNative,
                                             int bufferLen); // Equivalent ansi char(s).

    // Static method. Determine if a given wide character is native 
    // to the given code_page_id value.
    //
    // Note: if pChNative is non-null, it should be pointing to a
    // char buff, in case the native char is double-byte.
    // If the pChNative is null, it will return the length of the buffer
    // it needs to convert this wch to MBCS.
    //
    // Return value:
    // This method returns number of bytes in the equivalent MBCS 
    // character. If the return value is zero, wch is not native to 
    // code page specified by nCodePage parameter. If the return value is -1,
    // The destination buffer length is not enough.
    // 
    static ACBASE_PORT int isNativeToCodePageId(wchar_t wch,  // Input wide char.
                                               code_page_id codePageId,     // Code page id, can be code_page_id::CODE_PAGE_CURRENT/*CP_ACP*/
                                               char *pChNative,   // Equivalent ansi char(s).
                                               int bufferLen);

    // Static method. Converts a given wide character string into 
    // its ANSI/CIF equivalent. 
    // This method returns the number of characters written to the 
    // szDst buffer. If szDst is NULL, the return value indicates 
    // the size of destination buffer required for the conversion, 
    // in number of characters (including NULL character).
    static ACBASE_PORT int wcharNonNativeToCIF(const wchar_t *szSrc,   // Source wide string.
                                              wchar_t *szDst,         // Destination Ansi CIF buffer.
                                              size_t cchDstSize,         // Destination buffer size (chars).
                                              bool b2byteCharToCIF = false); //sometimes it is required to Convert non-single byte characters to CIF, no matter it is native or not.


    // Static helper method to convert existing CIF sequences in a 
    // wide string back to their native equivalent. 
    // 
    // Parameters:
    //  - szSrc: Source wide string that might contain CIF sequence 
    //           to be converted. This parameter cannot be NULL.
    //  - szDst: Destination wide string buffer where output is to 
    //           be written. If szDst is NULL and cchDstSize is a 
    //           negative value, resulting string will be written 
    //           to szSrc instead. If szDst is NULL and cchDstSize 
    //           is zero, required buffer size in characters is 
    //           returned. If szDst is not NULL, cchDstSize must be 
    //           greater than zero.
    //  - cchDstSize: Size of szDst buffer in number of wide chars.
    //                See description for 'szDst' for more details.
    // 
    // Return value:
    //  - If szDst is not NULL and cchDstSize is greater than zero, 
    //    the return value indicates the number of wide characters 
    //    written to szDst.
    //  - If szDst is NULL and cchDstSize is negative, the return 
    //    value is the number of wide characters written to szSrc.
    //  - If szDst is NULL and cchDstSize is zero, the return value 
    //    is buffer size required (in characters) for conversion.
    // 
    static int wcharFromCIFMIF(
        const wchar_t *szSrc, // Source input CIF string.
        wchar_t *szDst, // Destination wide buffer.
        int cchDstSize) // Destination buffer size (chars).
    {
        AdCharFmt_Assert(szSrc != NULL);
        AdCharFmt_Assert(szDst == NULL || cchDstSize > 0);
        AdCharFmt_Assert(szDst != NULL || cchDstSize <= 0);
        if (szSrc == NULL)
            return 0; // Ignorable assert.
        if (szDst != NULL && cchDstSize <= 0)
            return 0; // Ignorable assert.
        if (szDst == NULL && cchDstSize > 0)
            return 0; // Ignorable assert.

        int cchWritten = 0;
        const wchar_t *lpReadPtr  = szSrc; // Read pointer.
        wchar_t *lpWritePtr = szDst; // Write pointer.
        wchar_t *lpWriteEnd = szDst + cchDstSize;

        if (szDst == NULL && cchDstSize < 0) // Write to szSrc.
        {
            lpWritePtr = const_cast<wchar_t *>(szSrc);
            lpWriteEnd = NULL;   // result will always fit in dest
        }

        for (;;) {
            if (lpWritePtr && lpWriteEnd && lpWritePtr >= lpWriteEnd)
                break; // Ran out of writing space.

            const wchar_t wch = *lpReadPtr;
            wchar_t wchOut;
            if (parseCIF<wchar_t>(lpReadPtr, wchOut))
                lpReadPtr += 7; // Skip CIF sequence.
            else if (parseMIF<wchar_t>(lpReadPtr, wchOut))
                lpReadPtr += 8; // Skip MIF sequence.
            else {
                wchOut = wch;
                lpReadPtr++;    // Next input character.
            }

            if (lpWritePtr != NULL)
                *lpWritePtr++ = wchOut;

            cchWritten++;       // One more char output
            if (wch == 0)
                break;          // end of input string
        }

        return cchWritten;
    }

    // Static method. Converts a given wide character string into 
    // its ANSI/RTF equivalent. For an example, Unicode character 
    // 0x65e5 (26085) will be formatted to ANSI string "\u26085?".
    // 
    // Parameters:
    // - codePageId: Code page id value that the conversion is based on.
    // - szSrc: Source wide string to be converted.
    // - cchSrcLen: Source wide string length, in the number of 
    //              wide characters (excluding the NULL character). 
    //              If szSrc is a null terminated string, this 
    //              parameter can be -1.
    // - szDst: Destination ANSI/RTF output buffer. If this argument 
    //          is NULL, the required buffer size (in bytes) will be 
    //          returned through pcbDstSize argument (include NULL).
    // - pcbDstSize: Size of szDst buffer in terms of bytes. After 
    //               conversion is done, this value will be number 
    //               of bytes written out to szDst buffer including 
    //               the null-terminating character. 
    //               If szDst is NULL, caller can determine required 
    //               output buffer size from this parameter.
    // 
    // Return value:
    // This method returns the number of wide characters from szSrc 
    // that have been processed (not including the NULL terminating 
    // character) and output to szDst. 
    // 
    static int wcharNonNativeToRTF(
        code_page_id codePageId,     // Conversion code page id.
        const wchar_t *szSrc,   // Source wide string.
        int cchSrcLen,          // Source length, in wide characters.
        char *szDst,            // RTF (ANSI) output buffer.
        int *pcbDstSize)        // Output buffer size, in bytes.
    {
        AdCharFmt_Assert(szSrc != NULL);
        AdCharFmt_Assert(pcbDstSize != NULL);
        AdCharFmt_Assert(cchSrcLen >= -1);
        AdCharFmt_Assert(cchSrcLen < 0x1000000);  // 16M sanity check
        if (szSrc == NULL || pcbDstSize == NULL)
            return 0; // Ignorable assert.
        if (cchSrcLen < -1)
            return 0; // Ignorable assert.
        AdCharFmt_Assert(szDst == NULL || *pcbDstSize > 0);
        if (szDst != NULL && *pcbDstSize <= 0)
            return 0; // Ignorable assert.

        int cbWritten = 0;
        int cchProcessed = 0;
        for (;;) {
            if (cchSrcLen >= 0) {   // if caller passed in the src len
                AdCharFmt_Assert(cchProcessed <= cchSrcLen);
                if (cchProcessed >= cchSrcLen)
                    break;      // we did that many chars, now we're done
            }
            char szAnsiBuf[2];
            const wchar_t wch = szSrc[cchProcessed];
            if (wch == L'\0') {
                // We don't expect caller to pass us a SrcLen that
                // exceeds the length of the string.
                if (cchSrcLen < 0)
                    break;      // got the null terminator, we're done
            }
            const int cbAnsiSize = isNativeToCodePageId(
                wch, codePageId, szAnsiBuf, 2);

            AdCharFmt_Assert(cbAnsiSize >= 0);
            AdCharFmt_Assert(cbAnsiSize <= 2);
            if (cbAnsiSize > 0) { // Native to code page value.
                if (szDst) {
                    if (cbWritten + cbAnsiSize >= *pcbDstSize)
                        break; // Not enough space for writing.
                    szDst[cbWritten] = szAnsiBuf[0];
                    if (cbAnsiSize > 1)
                        szDst[cbWritten+1] = szAnsiBuf[1];
                }
                cbWritten += cbAnsiSize;
            }
            else { // Non-native character, convert it!
                unsigned short nValue = wch;
                AdCharFmt_Assert(nValue >= 128);
                int nDigits = 3; // For "\,u,?" characters.
                if (nValue < 1000)       nDigits += 3;
                else if (nValue < 10000) nDigits += 4;
                else                     nDigits += 5;

                if (szDst) {
                    if (cbWritten + nDigits >= *pcbDstSize)
                        break; // Not enough space for writing.
                    szDst[cbWritten + 0] = '\\';
                    szDst[cbWritten + 1] = 'u';
                    int i = cbWritten + nDigits - 1;
                    szDst[i] = '?';     // trailing char
                    do {
                        AdCharFmt_Assert(i > cbWritten + 1);
                        i--;
                        szDst[i] = (char)((nValue % 10) + '0');
                        nValue /= 10;
                    } while (nValue != 0);
                    AdCharFmt_Assert(i == cbWritten + 2);  // after the 'u'
                }
                cbWritten += nDigits;
            }
            cchProcessed++; // One wide character processed.
        }

        // Null-terminate the destination buffer only when the source 
        // buffer length is not specified (i.e. it is null-terminated), 
        // otherwise, the number of bytes written into szBuf can be 
        // determined through the argument pcbDstSize.
        // 
        *pcbDstSize = cbWritten; // Not including Null-terminator.
        if (cchSrcLen < 0) {
            if (szDst) szDst[cbWritten] = 0; // Null-terminate output.
            *pcbDstSize = cbWritten + 1;     // Bytes written.
        }
        return cchProcessed;         // Wide characters processed.
    }

  private:
    unsigned mnFormat;
    bool mbUseCIF;
    bool mbExpandLF;
};

#pragma warning(pop)

