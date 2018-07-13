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
// AcDMMUtils.h

/// <summary>
/// This file describes the following objects
/// AcDMMWideString - a simple Unicode string class
/// AcDMMStringVec - a vector of AcDMMWideStrings
/// AcDMMNode - which encapsulates a w2d Node
/// AcDMMResourceInfo - which contains the description of one resource
/// AcDMMResourceVec - a vector of AcDMMResourceInfo objects
/// (file) to the added to the DWF page or to the ePlot global section
/// </summary>


#include "acarray.h"

#ifndef AcDMMUtils_h
#define AcDMMUtils_h

typedef const wchar_t * PCWIDESTR;
typedef wchar_t * PWIDESTR;

/////////////////////////////////////////////////////////////////////
// AcDMMWideString
/////////////////////////////////////////////////////////////////////

/// <summary>
/// a simple unicode string class
/// </summary>
///
/// <remarks>
/// Cheap Unicode string class.  No fancy use-counting.
/// Just meant to "look" like CString as far as we use it.
/// </remarks>
class AcDMMWideString
{
public:
    /// <summary>
    /// default constructor
    /// </summary>
    ///
    AcDMMWideString();

    /// <summary>
    /// copy constructor
    /// </summary>
    ///
    /// <param name="ws">
    /// the string to be copied into this
    /// </param>
    ///
    AcDMMWideString(const AcDMMWideString& ws);

    /// <summary>
    /// Constructs this from a pointer to a Unicode string
    /// </summary>
    ///
    /// <param name="pwsz">
    /// a pointer to the null terminated Unicode string from which this
    /// object shall be constructed.
    /// </param>
    ///
    AcDMMWideString(PCWIDESTR pwsz);

    /// <summary>
    /// destructor
    /// </summary>
    ///
    virtual ~AcDMMWideString();

    /// <summary>
    /// operator= for copying another AcDMMWideString
    /// </summary>
    ///
    /// <param name="ws">
    /// a const reference to the AcDMMWideString which is to be
    /// copied to this
    /// </param>
    ///
    /// <returns>
    /// a const reference to this
    /// </returns>
    ///
    const AcDMMWideString& operator= (const AcDMMWideString& ws);

    /// <summary>
    /// operator= for copying a null terminated Unicode string into this
    /// </summary>
    ///
    /// <param name ="pwsz">
    /// a const pointer to a null terminated Unicode string to be copied
    /// to this
    /// </param>
    ///
    /// <returns>
    /// a const reference to this
    /// </returns>
    ///
    const AcDMMWideString& operator= (PCWIDESTR pwsz);

    /// <summary>
    /// returns a const pointer to the Unicode string contained by this
    /// </summary>
    ///
    /// <returns>
    /// returns a const pointer to the Unicode string contained by this
    /// </returns>
    ///
    operator PCWIDESTR() const;

    /// <summary>
    /// deletes the contained Unicode string
    /// </summary>
    ///
    void   Empty();

    /// <summary>
    /// tells the caller if this contains an empty string
    /// </summary>
    ///
    /// <returns>
    /// returns true if this contains an empty string
    /// </returns>
    bool   IsEmpty() const;

    /// <summary>
    /// get the length of the contained string, in Unicode characters
    /// </summary>
    ///
    /// <returns>
    /// the length of the contained string, in Unicode characters
    /// </returns>
    ///
    unsigned GetLength() const;  // not size_t.  lengths are < 4G.

    /// <summary>
    /// concatenates a second AcDMMWideString to this one
    /// </summary>
    ///
    /// <param name="ws">
    /// the AcDMMWideString to concatenate with this one
    /// </param>
    ///
    /// <returns>
    /// a const reference to this
    /// </returns>
    const AcDMMWideString& operator+= (AcDMMWideString ws);

    friend AcDMMWideString operator+ 
        (const AcDMMWideString& wsLeft, wchar_t wch);
    friend AcDMMWideString operator+ 
        (wchar_t wch, const AcDMMWideString& wsRight);
    friend AcDMMWideString operator+ 
        (const AcDMMWideString& wsLeft, const AcDMMWideString& wsRight);

private:
    void Alloc(size_t iLen);
    void Alloc(PCWIDESTR pwsz,size_t iLen);
    void Alloc(PCWIDESTR pwsz);
    static void Release(PWIDESTR pwsz);
    void Release();

    void MoveChars(int iStartOffset,PCWIDESTR pwsz,size_t iChars);

    PWIDESTR  m_pData;
    unsigned  m_iLength;   // not using size_t.  lengths are < 4G.
};


inline void AcDMMWideString::MoveChars(int iStartOffset,
                                       PCWIDESTR pwsz, size_t iChars)
{
    const unsigned n32Chars = (unsigned)iChars;
    assert(n32Chars == iChars);
    assert(iStartOffset >=0);
    assert((unsigned)iStartOffset <= m_iLength);
    assert(iStartOffset + iChars <= m_iLength+1);

    memmove(m_pData+iStartOffset,
            pwsz,
            iChars * sizeof(wchar_t));
}



inline AcDMMWideString operator+ (const AcDMMWideString& wsLeft, wchar_t wch)
{
    AcDMMWideString wsRet;

    wsRet.Alloc(wsLeft.m_pData,wsLeft.GetLength()+1);
    wsRet.m_pData[wsLeft.GetLength()] = wch;
    wsRet.m_pData[wsLeft.GetLength()+1] = 0;

    return(wsRet);
}


inline AcDMMWideString operator+ (wchar_t wch, const AcDMMWideString& wsRight)
{
    AcDMMWideString wsRet;

    wsRet.Alloc(wsRight.GetLength()+1);
    wsRet.m_pData[0] = wch;
    wsRet.MoveChars(1,wsRight.m_pData,wsRight.GetLength()+1);

    return(wsRet);
}

inline AcDMMWideString operator+ (const AcDMMWideString& wsLeft, 
    const AcDMMWideString& wsRight)
{
    AcDMMWideString wsRet(wsLeft);
    wsRet += wsRight;
    return(wsRet);
}

inline const AcDMMWideString& AcDMMWideString::operator += (AcDMMWideString ws)
{
    if(!ws.IsEmpty()) {
        AcDMMWideString wsOldThis = *this;
        Empty();
        Alloc(wsOldThis.GetLength() + ws.GetLength());

        MoveChars(0,wsOldThis.m_pData,wsOldThis.GetLength());

        MoveChars(wsOldThis.GetLength(),ws.m_pData,ws.GetLength()+1);
    }

    return(*this);
}

inline AcDMMWideString::AcDMMWideString()
: m_pData(NULL),
  m_iLength(0)
{
}

inline AcDMMWideString::AcDMMWideString(const AcDMMWideString& ws)
: m_pData(NULL),
  m_iLength(0)
{
    Alloc(ws.m_pData? ws.m_pData: L"",ws.m_iLength);
}

inline AcDMMWideString::AcDMMWideString(PCWIDESTR pwsz)
: m_pData(NULL),
  m_iLength(0)
{
    Alloc(pwsz);
}

inline AcDMMWideString::~AcDMMWideString()
{
    Empty();
}

inline bool AcDMMWideString::IsEmpty() const
{
    return(m_iLength == 0);
}

inline void AcDMMWideString::Empty()
{
    if(m_pData)
        Release();

    m_iLength = 0;
}


inline AcDMMWideString::operator PCWIDESTR() const
{
    return(m_pData ? m_pData : L"");
}


inline const AcDMMWideString& AcDMMWideString::operator=
    (const AcDMMWideString& ws)
{
    Empty();
    m_iLength = ws.m_iLength;
    Alloc(ws.m_pData,ws.m_iLength);

    return(*this);
}

inline const AcDMMWideString& AcDMMWideString::operator= (PCWIDESTR pwsz)
{
    Empty();
    m_iLength = (unsigned)wcslen(pwsz);
    Alloc(pwsz,m_iLength);

    return(*this);
}

inline unsigned AcDMMWideString::GetLength() const
{
    return this->m_iLength;
}


inline void AcDMMWideString::Alloc(size_t iLen)
// Makes an allocation of the size indicated
{
    assert(m_pData == NULL);
    assert(iLen == (unsigned)iLen);
    m_iLength = (unsigned)iLen;
    m_pData = new wchar_t[m_iLength+1];
}

inline void AcDMMWideString::Alloc(PCWIDESTR pwsz,size_t iLen)
// Makes an allocation of the size indicated, copies that amount
{
    assert(m_pData == NULL);
    assert(pwsz != NULL);

    if(iLen > 0) {
        Alloc(iLen);
        MoveChars(0,pwsz,iLen+1);
    }
}

inline void AcDMMWideString::Alloc(PCWIDESTR pwsz)
// Makes an allocation, copies entire string
{
    assert(m_pData == NULL);
    assert(pwsz != NULL);
    if (pwsz == NULL)
        return;

    Alloc(pwsz,wcslen(pwsz));
}


inline void AcDMMWideString::Release(PWIDESTR pwsz)
// Static function: deallocates the backing store.
{
    if (pwsz)
        delete[] pwsz;
}


inline void AcDMMWideString::Release()
{
    Release(m_pData);
    m_pData = NULL;
    m_iLength = 0;
}

typedef AcArray<AcDMMWideString> AcDMMStringVec;

///////////////////////////////////////////////////////////////////////
/// class AcDMMNode
///////////////////////////////////////////////////////////////////////
/// <summary>
/// a lightweight object to hold the data needed to describe a Node in
/// a DWF w2d
/// </summary>
class AcDMMNode 
{
public:
    /// <summary>
    /// default constructor
    /// </summary>
    ///
    /// <remarks>
    /// creates an empty node with number 0
    /// </remarks>
    AcDMMNode()
    : m_nodeNumber(0),
      m_nodeName(NULL)
    {
    }

    /// <summary>
    /// constructs a node from a name and number
    /// </summary>
    ///
    /// <param name="number">
    /// The integer Node number.
    /// </param>
    ///
    /// <param name="name">
    /// a Unicode string defining the Node name
    /// </param>
    ///
    AcDMMNode(int number, wchar_t * name)
    {
        m_nodeNumber = number;
        if (NULL != name) {
            size_t nSize = ::wcslen(name) + 1;
            m_nodeName = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_nodeName, nSize, name);
            assert(err == 0);
        } else
            m_nodeName = NULL;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object to be copied
    /// </param>
    ///
    AcDMMNode(const AcDMMNode &src) 
    : m_nodeName(NULL)
    { 
        *this = src;
    }


    /// <summary>
    /// destructor
    /// </summary>
    ///
    ~AcDMMNode()
    {
        if (NULL != m_nodeName)
            delete [] m_nodeName;
    }

    /// <summary>
    /// accessor for the Node number
    /// </summary>
    ///
    /// <returns>
    /// the integer Node number
    /// </returns>
    int nodeNumber() const {return m_nodeNumber;};

    /// <summary>
    /// mutator for the Node number
    /// </summary>
    ///
    /// <param name="number">
    /// the integer value to assign as Node number
    /// </param>
    void SetNodeNumber(int number) {m_nodeNumber = number;};


    /// <summary>
    /// accessor for the Node name
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the null terminated Unicode Node name string
    /// </returns>
    const wchar_t * nodeName() const {return m_nodeName;};

    /// <summary>
    /// mutator for the Node name
    /// </summary>
    ///
    /// <param name="name">
    /// a const pointer to a Unicode string to be assigned as Node name
    /// </param>
    void SetNodeName(const wchar_t * name)
    {
        if (NULL != m_nodeName) {
            delete [] m_nodeName;
            m_nodeName = NULL;
        }
        if (NULL != name) {
            size_t nSize = ::wcslen(name) + 1;
            m_nodeName = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_nodeName, nSize, name);
            assert(err == 0);
        } else
            m_nodeName = NULL;
    }

    /// <summary>
    /// operator= also used by copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object whose values will be copied to this object
    /// </param>
    ///
    /// <returns>
    /// returns this object
    /// </returns>
    AcDMMNode & operator= (const AcDMMNode &src)
    {
        if (this == &src)
            return *this;

        SetNodeNumber(src.m_nodeNumber);
        SetNodeName(src.m_nodeName);
        return *this;
    }

private:
    int m_nodeNumber;
    wchar_t * m_nodeName;
};

/////////////////////////////////////////////////////////////////////////
// class AcDMMResourceInfo
/////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class describes a resource to be added to the DWF page or global 
/// section
/// The resource is an existing file which will be added to the zip
/// file and listed in the page descriptor as a page resource or added
/// to the ePlot global section as a global resource
/// </summary>
class AcDMMResourceInfo
{
public:
    /// <summary>
    /// the default constructor, creates an empty object
    /// </summary>
    AcDMMResourceInfo()
    : m_mime(NULL),
      m_role(NULL),
      m_path(NULL)
    {
    }

    /// <summary>
    /// creates an AcDMMResourceInfo object from 3 Unicode strings
    /// </summary>
    ///
    /// <param name="role">
    /// a null terminated Unicode string to be assigned to the role attribute
    /// This string describes the resource, e.g, "thumbnail", "font", etc.
    /// </param>
    ///
    /// <param name="mime">
    /// this is a null terminated Unicode strings to be assigned to the mime
    /// type attribute. 
    /// </param>
    ///
    /// <param name="path">
    /// This is a Unicode string holding the full path to the resource file
    /// </param>
    AcDMMResourceInfo(const wchar_t *role, const wchar_t *mime, 
        const wchar_t *path)
    {
        if (NULL != role) {
            size_t nSize = ::wcslen(role) + 1;
            m_role = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_role, nSize, role);
            assert(err == 0);
        } else
            m_role = NULL;

        if (NULL != mime) {
            size_t nSize = ::wcslen(mime) + 1;
            m_mime = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_mime, nSize, mime);
            assert(err == 0);
        } else
            m_mime = NULL;

        if (NULL != path) {
            size_t nSize = ::wcslen(path) + 1;
            m_path = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_path, nSize, path);
            assert(err == 0);
        } else
            m_path = NULL;
    }

    /// <summary>
    /// Copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object to be copied
    /// </param>
    ///
    AcDMMResourceInfo(const AcDMMResourceInfo & src) 
    : m_role(NULL),
      m_mime(NULL),
      m_path(NULL)
    {
        *this = src;
    }


    /// <summary>
    /// destructor
    /// </summary>    
    ~AcDMMResourceInfo()
    {
        if (NULL != m_role)
            delete [] m_role;
        if (NULL != m_mime)
            delete [] m_mime;
        if (NULL != m_path)
            delete [] m_path;
    }

    /// <summary>
    /// mutator for the Role attribute
    /// </summary>
    ///
    /// <param name="role">
    /// a const pointer to a Unicode string to be assigned as role
    /// </param>
    void SetRole(wchar_t * role)
    {
        if (NULL != m_role) {
            delete [] m_role;
            m_role = NULL;
        }
        if (NULL != role) {
            size_t nSize = ::wcslen(role) + 1;
            m_role = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_role, nSize, role);
            assert(err == 0);
        } else
            m_role = NULL;
    }

    /// <summary>
    /// mutator for the Role attribute
    /// </summary>
    ///
    /// <param name="role">
    /// a const pointer to a Unicode string to be assigned as role
    /// </param>
    void SetRole(const wchar_t * role)
    {
        if (NULL != m_role) {
            delete [] m_role;
            m_role = NULL;
        }
        if (NULL != role) {
            size_t nSize = ::wcslen(role) + 1;
            m_role = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_role, nSize, role);
            assert(err == 0);
        } else
            m_role = NULL;
    }

    /// <summary>
    /// accessor for the Role attribute
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the null terminated Unicode Node role string
    /// </returns>
    const wchar_t * GetRole() const {return m_role;};

    /// <summary>
    /// mutator for the Mime attribute
    /// </summary>
    ///
    /// <param name="mime">
    /// a const pointer to a Unicode string to be assigned as mime
    /// </param>
    void SetMime(wchar_t * mime)
    {
        if (NULL != m_mime) {
            delete [] m_mime;
            m_mime = NULL;
        }
        if (NULL != mime) {
            size_t nSize = ::wcslen(mime) + 1;
            m_mime = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_mime, nSize, mime);
            assert(err == 0);
        } else
            m_mime = NULL;
    }

    /// <summary>
    /// mutator for the Mime attribute
    /// </summary>
    ///
    /// <param name="mime">
    /// a const pointer to a Unicode string to be assigned as mime
    /// </param>
    void SetMime(const wchar_t * mime)
    {
        if (NULL != m_mime) {
            delete [] m_mime;
        }
        if (NULL != mime) {
            size_t nSize = ::wcslen(mime) + 1;
            m_mime = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_mime, nSize, mime);
            assert(err == 0);
        } else
            m_mime = NULL;
    }

    /// <summary>
    /// accessor for the Mime type attribute
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the null terminated Unicode mime type string
    /// </returns>
    const wchar_t * GetMime() const {return m_mime;};

    /// <summary>
    /// mutator for the Path attribute
    /// </summary>
    ///
    /// <param name="path">
    /// a const pointer to a Unicode string to be assigned as path to the
    /// resource file
    /// </param>
    void SetPath(wchar_t * path)
    {
        if (NULL != m_path) {
            delete [] m_path;
            m_path = NULL;
        }
        if (NULL != path) {
            size_t nSize = ::wcslen(path) + 1;
            m_path = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_path, nSize, path);
            assert(err == 0);
        } else
            m_path = NULL;
    }

    /// <summary>
    /// mutator for the Path attribute
    /// </summary>
    ///
    /// <param name="path">
    /// a const pointer to a Unicode string to be assigned as path to the
    /// resource file
    /// </param>
    void SetPath(const wchar_t * path)
    {
        if (NULL != m_path) {
            delete [] m_path;
            m_path = NULL;
        }
        if (NULL != path) {
            size_t nSize = ::wcslen(path) + 1;
            m_path = new wchar_t[nSize];
            errno_t err = ::wcscpy_s(m_path, nSize, path);
            assert(err == 0);
        } else
            m_path = NULL;
    }

    /// <summary>
    /// accessor for the path to the resource file
    /// </summary>
    ///
    /// <returns>
    /// a const pointer to the null terminated Unicode path string
    /// </returns>
    const wchar_t * GetPath() const {return m_path;};

    /// <summary>
    /// operator= also used by copy constructor
    /// </summary>
    ///
    /// <param name="src">
    /// the object whose values will be copied to this object
    /// </param>
    ///
    /// <returns>
    /// returns this object
    /// </returns>
    AcDMMResourceInfo& operator= (const AcDMMResourceInfo &src)
    {
        if (this == &src)
            return *this;

        SetRole(src.m_role);
        SetMime(src.m_mime);
        SetPath(src.m_path);
        return *this;
    }

private:
    wchar_t * m_role;
    wchar_t * m_mime;
    wchar_t * m_path; // full path to resource file   
};

typedef AcArray<AcDMMResourceInfo> AcDMMResourceVec;

#endif // AcDMMUtils_h
