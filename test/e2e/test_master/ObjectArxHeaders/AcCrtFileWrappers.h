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
// Name:            AcCrtFileWrappers.h
//
// Description:     Wrapper classes for clib FILE functions
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#include "PAL/API/def.h"
#include "stdio.h"
#include "AdCharFmt.h"
#include "casuppress.h"
#include <cstdarg>
#include "acbasedefs.h"
#pragma  warning(push)
#pragma  warning(disable:4996)
#ifdef ASSERT
#  define AcFILE_Assert	ASSERT
#elif  defined assert
#  define AcFILE_Assert	assert
#elif  defined _ASSERTE
#  define AcFILE_Assert	_ASSERTE
#else 
#  define AcFILE_Assert(T)
#endif
class AcFILE
{
public:
  AcFILE()
    : mpFILE(NULL)
    , mChFmtr(AdCharFormatter::kAnsi, false, false)
  {
  }
  AcFILE(FILE* pFILE)
    : mpFILE(pFILE)
    , mChFmtr(AdCharFormatter::kAnsi, false, false)
  {
  }
  ~AcFILE()
  {
    AcFILE_Assert(this->mpFILE == NULL);
  }
  ACBASE_PORT FILE* fopen(const wchar_t* pName, const wchar_t* pMode);
  ACBASE_PORT FILE* fsopen(const wchar_t* pName, const wchar_t* pMode, int shflag);
  void attach(FILE* pFILE);
  FILE* detach();
  int fclose();
  int fputs(const wchar_t* pStr);
  wchar_t* fgets(wchar_t* pBuf, int nChars);
  ACBASE_PORT int fprintf(const wchar_t* pFmtStr, ...);
  ACBASE_PORT int vfprintf(const wchar_t* pFmtStr, va_list va);
  int fscanf(const wchar_t* pFmtStr, ...);
  int fputc(wchar_t c);
  int ungetc(wchar_t c);
  ACBASE_PORT int fgetc();
  bool isOpen() const
  {
    return this->mpFILE != NULL;
  }
  FILE* pFILE() const
  {
    return this->mpFILE;
  }
  unsigned getCharFormat() const
  {
    return this->mChFmtr.getFormat();
  }
  unsigned setCharFormat(unsigned nFmt)
  {
    return this->mChFmtr.setFormat(nFmt);
  }
  bool getUseCIF() const
  {
    return this->mChFmtr.getUseCIF();
  }
  bool setUseCIF(bool bUseCIF)
  {
    return this->mChFmtr.setUseCIF(bUseCIF);
  }
  bool getExpandLF() const
  {
    return this->mChFmtr.getExpandLF();
  }
  bool setExpandLF(bool bExpandLF)
  {
    return this->mChFmtr.setExpandLF(bExpandLF);
  }
  bool readBOM();
  bool writeBOM();
private:
  bool parseAnsiOrCIF(wchar_t& wch);
  bool parseUtf8(wchar_t& wch);
  bool parseUtf16(wchar_t& wch);
  int fputsWorker(const wchar_t* pSrc, int nOptions);
  FILE* mpFILE;
  AdCharFormatter mChFmtr;
};
inline void AcFILE::attach(FILE* pFILE)
{
  AcFILE_Assert(this->mpFILE == NULL);
  this->mpFILE = pFILE;
}
inline FILE* AcFILE::detach()
{
  FILE* pRet = this->mpFILE;
  this->mpFILE = NULL;
  return pRet;
}
inline int AcFILE::fclose()
{
  int nRet = 0;
  if (this->mpFILE != NULL)
  {
    nRet = ::fclose(this->mpFILE);
    this->mpFILE = NULL;
  }
  return nRet;
}
inline int AcFILE::fputs(const wchar_t* pStr)
{
  AcFILE_Assert(this->mpFILE != NULL);
  return fputsWorker(pStr, 0);
}
inline wchar_t* AcFILE::fgets(wchar_t* pBuf, int nChars)
{
  AcFILE_Assert(this->mpFILE != NULL);
  AcFILE_Assert(nChars > 1);
  wchar_t* pSavePtr = pBuf;
  for (;;)
  {
    if (nChars <= 1)
    {
      break;
    }
    const int ch = this->fgetc();
    if (ch == EOF)
    {
      break;
    }
    AcFILE_Assert((ch & ~0xffff) == 0);
    AcFILE_Assert((wchar_t) ch == ch);
    *pSavePtr = (wchar_t) ch;
    pSavePtr++;
    if (ch == '\n')
    {
      break;
    }
    nChars--;
  }
  *pSavePtr = 0;
  if (pSavePtr == pBuf)
  {
    return NULL;
  }
  return pBuf;
}
ADESK_DEPRECATED inline int AcFILE::fscanf(const wchar_t* pFmtStr, ...)
{
  AcFILE_Assert(this->mpFILE != NULL);
  pFmtStr = NULL;
  AcFILE_Assert(false);
  return -1;
}
inline int AcFILE::fputc(wchar_t c)
{
  AcFILE_Assert(this->mpFILE != NULL);
  char chBuf[8];
  const unsigned nBytes = this->mChFmtr.wcharToBytes(c, chBuf, sizeof(chBuf));
  AcFILE_Assert(nBytes >= 1);
  AcFILE_Assert(nBytes <= 8);
  const unsigned nNumWrote = (unsigned) fwrite(chBuf, 1, nBytes, this->mpFILE);
  if (nNumWrote == nBytes)
  {
    return c;
  }
  else 
  {
    return -1;
  }
}
inline int AcFILE::ungetc(wchar_t c)
{
  AcFILE_Assert(this->mpFILE != NULL);
  char chBuf[8];
  const unsigned nBytes = this->mChFmtr.wcharToBytes(c, chBuf, sizeof(chBuf));
  AcFILE_Assert(nBytes >= 1);
  AcFILE_Assert(nBytes <= 8);
  if (nBytes == 1 && ::ungetc(chBuf[0], this->mpFILE) == chBuf[0])
  {
    return c;
  }
  else 
  {
    return -1;
  }
}
inline bool AcFILE::readBOM()
{
  AcFILE_Assert(this->mpFILE != NULL);
  const long lFilePos = ::ftell(this->mpFILE);
  AcFILE_Assert(lFilePos == 0L);
  if (lFilePos != 0L)
  {
    return false;
  }
  unsigned short nVal;
  if (::fread(&nVal, 1, 2, this->mpFILE) == 2)
  {
    if (nVal == 0xfeff)
    {
      this->setCharFormat(AdCharFormatter::kUtf16LE);
      return true;
    }
    if (nVal == 0xfffe)
    {
      this->setCharFormat(AdCharFormatter::kUtf16BE);
      return true;
    }
    if (nVal == 0xbbef)
    {
      unsigned char nByte3;
      if (::fread(&nByte3, 1, 1, this->mpFILE) == 1)
      {
        if (nByte3 == 0xbf)
        {
          this->setCharFormat(AdCharFormatter::kUtf8);
          return true;
        }
      }
    }
    else 
    {
      if (nVal == 0 || nVal == 0xfeff)
      {
        unsigned nVal2;
        if (::fread(&nVal2, 1, 2, this->mpFILE) == 2)
        {
          if (nVal == 0 && nVal2 == 0xfffe)
          {
            this->setCharFormat(AdCharFormatter::kUtf32BE);
            return true;
          }
          else 
          {
            if (nVal == 0xfeff && nVal2 == 0)
            {
              this->setCharFormat(AdCharFormatter::kUtf32LE);
              return true;
            }
          }
        }
      }
    }
  }
  ::rewind(this->mpFILE);
  return false;
}
inline bool AcFILE::writeBOM()
{
  AcFILE_Assert(this->mpFILE != NULL);
  if (this->mpFILE == NULL)
  {
    return false;
  }
  const long lFilePos = ::ftell(this->mpFILE);
  AcFILE_Assert(lFilePos == 0L);
  if (lFilePos != 0L)
  {
    return false;
  }
  unsigned nBom = 0;
  const int cbBomSize = AdCharFormatter::getBOM(nBom, this->getCharFormat());
  if (cbBomSize == 0)
  {
    return false;
  }
  const int cbWritten = (int) ::fwrite(&nBom, 1, cbBomSize, this->mpFILE);
  AcFILE_Assert(cbWritten == cbBomSize);
  if (cbWritten != cbBomSize)
  {
    ::rewind(this->mpFILE);
    return false;
  }
  return true;
}
inline bool AcFILE::parseUtf16(wchar_t& wch)
{
  wchar_t wchLocal = 0;
  int nBytesRead = (int) ::fread(&wchLocal, 1, 2, this->mpFILE);
  if (nBytesRead <= 0)
  {
    return false;
  }
  const unsigned nFormat = this->mChFmtr.getFormat();
  if (nFormat == AdCharFormatter::kUtf16BE)
  {
    wchLocal = (wchLocal >> 8) | (wchLocal << 8);
  }
  wch = wchLocal;
  if (wchLocal == L'\r' && mChFmtr.getExpandLF())
  {
    wchar_t wchNewLine = L'\n';
    nBytesRead = (int) ::fread(&wchNewLine, 1, 2, this->mpFILE);
    if (nBytesRead <= 0)
    {
      return true;
    }
    if (nFormat == AdCharFormatter::kUtf16BE)
    {
      wchNewLine = (wchNewLine >> 8) | (wchNewLine << 8);
    }
    if (wchNewLine != L'\n')
    {
      ::fseek(this->mpFILE, -2L, SEEK_CUR);
      return true;
    }
    wch = L'\n';
  }
  return true;
}
inline int AcFILE::fputsWorker(const wchar_t* pSrc, int nOptions)
{
  AcFILE_Assert(this->mpFILE != NULL);
  AcFILE_Assert(pSrc != NULL);
  int nNumInput = 0;
  for (;;)
  {
    const wchar_t wch = *pSrc;
    if (wch == 0)
    {
      break;
    }
    char chBuf[8];
    const unsigned nBytes = this->mChFmtr.wcharToBytes(wch, chBuf, sizeof(chBuf));
    AcFILE_Assert(nBytes >= 1);
    AcFILE_Assert(nBytes <= 8);
    const unsigned nNumWrote = (unsigned) fwrite(chBuf, 1, nBytes, this->mpFILE);
    if (nNumWrote != nBytes)
    {
      return -1;
    }
    nNumInput++;
    pSrc++;
  }
  if (nOptions == 0)
  {
    return 0;
  }
  else 
  {
    if (nOptions == 1)
    {
      return nNumInput;
    }
    else 
    {
      AcFILE_Assert(false);
    }
  }
  return -1;
}
#pragma  warning(pop) 
