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
// Name:            AcFStream.h
//
// Description:     Wrapper classes for std:ofstream and std::ifstream.
//
//////////////////////////////////////////////////////////////////////////////

// Note: 1. this header should be included *after* fstream headers
//        

#pragma once

#ifdef ASSERT
#define AcFStream_Assert ASSERT
#elif defined assert
#define AcFStream_Assert assert
#else
#define AcFStream_Assert(T)
#endif

class AcIfstream : public std::wifstream {
public:
    AcIfstream() {};
    AcIfstream(const wchar_t *pName);

    void open(const wchar_t *pName);
    void open(const wchar_t *pName, ios_base::openmode nMode);
};

class AcOfstream : public std::wofstream {
public:
    AcOfstream() {};
    AcOfstream(const wchar_t *pName);

    void open(const wchar_t *pName);
    void open(const wchar_t *pName, ios_base::openmode nMode);
};

inline AcIfstream::AcIfstream(const wchar_t *pName)
{
    this->open(pName);
}

inline AcOfstream::AcOfstream(const wchar_t *pName)
{
    this->open(pName);
}

inline const std::locale& AcFStream_curLocale()
{
    // Only set LC_NUMERIC, because we don't want it to start
    // formatting numbers with comma separators, etc
    static const std::locale loc(std::locale(), std::locale::classic(), LC_NUMERIC);
    return loc;
}

inline void AcIfstream::open(const wchar_t *pName)
{
#ifndef  _ADESK_MAC_
    this->std::wifstream::open(pName);
    this->imbue(AcFStream_curLocale());
#else
    STUB_WARNING(AcIfstream::open);
#endif
}

inline void AcIfstream::open(const wchar_t *pName, ios_base::openmode nMode)
{
#ifndef  _ADESK_MAC_
    this->std::wifstream::open(pName, nMode);
    this->imbue(AcFStream_curLocale());
#else
     STUB_WARNING(AcIfstream::open);
#endif
}

inline void AcOfstream::open(const wchar_t *pName)
{
#ifndef  _ADESK_MAC_
    this->std::wofstream::open(pName);
    this->imbue(AcFStream_curLocale());
#else
    STUB_WARNING(AcOfstream::open);
#endif
}

inline void AcOfstream::open(const wchar_t *pName, ios_base::openmode nMode)
{
#ifndef  _ADESK_MAC_
    this->std::wofstream::open(pName, nMode);
    this->imbue(AcFStream_curLocale());
#else
    STUB_WARNING(AcOfstream::open);
#endif
}


