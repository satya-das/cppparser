//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license
//  agreement provided at the time of installation or download, or which
//  otherwise accompanies this software in either electronic or hard copy form.
//
//  AcString.h
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _Ac_String_h_
#  define _Ac_String_h_
#  include "acbasedefs.h"
#  include "adesk.h"
#  include "AcHeapOpers.h"
#  include "AdAChar.h"
#  include "rxresource.h"
#  include <cstdarg>
class AcDbHandle;
class AcRxResourceInstance;
class AcString : public AcHeapOperators
{
public:
  enum Encoding
  {
    Utf8
  };
  ACBASE_PORT AcString();
  ACBASE_PORT AcString(wchar_t wch);
  ACBASE_PORT AcString(const char* psz, Encoding encoding);
  ACBASE_PORT AcString(const wchar_t* pwsz);
  ACBASE_PORT AcString(const wchar_t* pwsz, unsigned int count);
  ACBASE_PORT AcString(const AcString& acs);
  ACBASE_PORT AcString(AcString&& acs);
  enum eFormat
  {
    kSigned = 0x0002,
    kUnSigned = 0x0003,
    kHex = 0x0004
  };
    /// <description>
    ///  Multi-purpose constructor, takes an unsigned argument and
    ///  uses it either to load a resource string or to create a
    ///  numerical string (base 10 or hex).
    /// </description>
    /// <param name="nCtorFlags">input flags, indicating type of construction</param>
    /// <param name="nArg">input argument value, interpreted according to flags</param>
  ACBASE_PORT AcString(eFormat nCtorFlags, unsigned nArg);
    /// <description>
    ///  repeat a character n times.
    /// </description>
    /// <param name="ch">character value</param>
    /// <param name="nRepeatTimes">repate times</param>
  ACBASE_PORT AcString(ACHAR ch, unsigned nRepeatTimes);
    /// <description>
    ///  Formats an AcDbHandle value in hex, as in: "a2f".
    /// </description>
    /// <param name="h">input reference to an acdb handle value</param>
  ACBASE_PORT AcString(const AcDbHandle& h);
    /// <description>
    ///  Load String from resource instance
    /// </description>
    /// <param name="hDll">AxResourceInstance object to load string</param>
    /// <param name="nId">input id of the string resource in the specified resource dll</param>
  ACBASE_PORT AcString(const AcRxResourceInstance& hDll, unsigned int nId);
  ACBASE_PORT ~AcString();
  ACBASE_PORT const char* utf8Ptr() const;
  const wchar_t* kwszPtr() const;
  const wchar_t* constPtr() const;
  const wchar_t* kTCharPtr() const;
  const ACHAR* kACharPtr() const;
  operator const wchar_t*() const;
  bool isEmpty() const;
  ACBASE_PORT unsigned length() const;
  unsigned tcharLength() const
  {
    return this->length();
  }
  ACBASE_PORT unsigned capacity() const;
  ACBASE_PORT bool reserve(unsigned nCapacity);
  ACBASE_PORT bool isAscii() const;
  enum
  {
    kParseZero = 0,
    kParseMinus1 = 0x01,
    kParseAssert = 0x02,
    kParseExcept = 0x04,
    kParseNoEmpty = 0x08,
    kParseDefault = (kParseAssert | kParseZero)
  };
  ACBASE_PORT int asDeci(int nFlags = kParseDefault) const;
  ACBASE_PORT int asHex(int nFlags = kParseDefault) const;
  ACBASE_PORT unsigned int asUDeci(int nFlags = kParseDefault) const;
  ACBASE_PORT unsigned int asUHex(int nFlags = kParseDefault) const;
  ACBASE_PORT int64_t asDeci64(int nFlags = kParseDefault) const;
  ACBASE_PORT int64_t asHex64(int nFlags = kParseDefault) const;
  ACBASE_PORT Adesk::UInt64 asUDeci64(int nFlags = kParseDefault) const;
  ACBASE_PORT Adesk::UInt64 asUHex64(int nFlags = kParseDefault) const;
  ACBASE_PORT AcDbHandle asAcDbHandle(int nFlags = kParseDefault) const;
  int find(ACHAR ch) const;
    /// <description>
    ///  Find a single char in the string.
    /// </description>
    /// <param name="ch">input char to search for</param>
    /// <param name="nStartFrom">first character to search</param>
    /// <returns>
    /// return the position of find result
    /// -1 indicates not found
    /// </returns>
  ACBASE_PORT int find(ACHAR ch, int nStartFrom) const;
    /// <description>
    ///  Find a substring in the string
    /// </description>
    /// <param name="psz">input string to search for</param>
    /// <returns>
    /// return the position of find result
    /// -1 indicates not found
    /// </returns>
  ACBASE_PORT int find(const ACHAR* psz) const;
  ACBASE_PORT int find(const AcString& acs) const;
  ACBASE_PORT int findOneOf(const ACHAR* psz) const;
  int findRev(ACHAR ch) const;
  ACBASE_PORT int findRev(const ACHAR* psz) const;
  ACBASE_PORT int findOneOfRev(const ACHAR* psz) const;
  ACBASE_PORT int findRev(const AcString& acs) const;
    /// <description>
    ///  Get a substring from the zero-based nStart position to the end of the string.
    /// </description>
    /// <param name="nStart">The zero-based start position of the substring to get.</param>
    /// <returns>
    /// return the substring
    /// </returns>
  AcString mid(int nStart) const;
  AcString mid(int nStart, int nNumChars) const;
  AcString substr(int numChars) const;
  ACBASE_PORT AcString substr(int nStart, int nNumChars) const;
  ACBASE_PORT AcString substrRev(int numChars) const;
    /// <description>
    /// Return a nNumChars length substring from the start of string.
    /// </description>
    /// <param name="nNumChars">The count of characters of the substring to get.</param>
    /// <returns>
    /// return the substring
    /// </returns>
  AcString left(int nNumChars) const;
    /// <description>
    /// Return a nNumChars length substring from the end of string.
    /// </description>
    /// <param name="nNumChars">The count of characters of the substring to get.</param>
    /// <returns>
    /// return the substring
    /// </returns>
  AcString right(int nNumChars) const;
  AcString& assign(wchar_t wch);
  ACBASE_PORT AcString& assign(const char* psz, Encoding encoding);
  ACBASE_PORT AcString& assign(const wchar_t* pwsz);
  ACBASE_PORT AcString& assign(const AcString& acs);
  ACBASE_PORT AcString& assign(const AcDbHandle& h);
  AcString& operator =(wchar_t wch);
  AcString& operator =(const wchar_t* pwsz);
  AcString& operator =(const AcString& acs);
  ACBASE_PORT AcString& operator =(AcString&& acs);
  AcString& operator =(const AcDbHandle& h);
  ACBASE_PORT AcString& setEmpty();
  ACBASE_PORT bool loadString(const AcRxResourceInstance& hDll, unsigned nId);
  ACBASE_PORT AcString& format(const ACHAR* pszFmt, ...);
  ACBASE_PORT AcString& formatV(const ACHAR* pszFmt, va_list args);
    /// <description>
    /// Append formated data to this string using "printf" rules
    /// </description>
    /// <param name="pszFmt">input pointer to the printf format string</param>
    /// <param name="args">input variable args list, containing values to be formatted</param>
    /// <returns> Reference to this AcString.</returns>
  ACBASE_PORT AcString& appendFormat(const ACHAR* pszFmt, ...);
  AcString& operator +=(wchar_t wch);
  AcString& operator +=(const wchar_t* pwsz);
  AcString& operator +=(const AcString& acs);
  AcString& append(wchar_t wch);
  ACBASE_PORT AcString& append(const char* psz, Encoding encoding);
  ACBASE_PORT AcString& append(const wchar_t* pwsz);
  ACBASE_PORT AcString& append(const AcString& acs);
  AcString operator +(wchar_t wch) const;
  AcString operator +(const wchar_t* pwsz) const;
  AcString operator +(const AcString& acs) const;
  AcString concat(wchar_t wch) const;
  ACBASE_PORT AcString concat(const char* psz, Encoding encoding) const;
  ACBASE_PORT AcString concat(const wchar_t* pwsz) const;
  ACBASE_PORT AcString concat(const AcString& acs) const;
  AcString precat(ACHAR ch) const;
  ACBASE_PORT AcString precat(const char* psz, Encoding encoding) const;
  ACBASE_PORT AcString precat(const wchar_t* psz) const;
  int compare(wchar_t wch) const;
  ACBASE_PORT int compare(const char* psz, Encoding encoding) const;
  ACBASE_PORT int compare(const wchar_t* pwsz) const;
  int compare(const AcString& acs) const;
    /// <description>
    /// Compare the string to another string using collation
    /// </description>
    /// <param name="pwsz">input pointer to the string of chars to compare to</param>
    /// <returns>
    /// Zero if the strings are identical, <0 if this AcString object is less than lpsz, or >0 if this AcString object is greater than lpsz.
    /// </returns>
  ACBASE_PORT int collate(const wchar_t* pwsz) const;
    /// <description>
    /// Compare the string to another AcString object using collation
    /// </description>
    /// <param name="acs">input AcString object to compare to </param>
    /// <returns>
    /// Zero if the strings are identical, <0 if this AcString object is less than acs, or >0 if this AcString object is greater than acs.
    /// </returns>
  int collate(const AcString& acs) const;
  int compareNoCase(wchar_t wch) const;
  ACBASE_PORT int compareNoCase(const char* psz, Encoding encoding) const;
  ACBASE_PORT int compareNoCase(const wchar_t* pwsz) const;
  int compareNoCase(const AcString& acs) const;
    /// <description>
    /// compares two AcStrings for equality, ignoring case
    /// useful as a comparator function for STL functions
    /// </description>
    /// <param name="left"> one AcString object </param>
    /// <param name="right"> another AcString object </param>
    /// <returns>
    /// return true if the strings are identical
    /// </returns>
  static bool equalsNoCase(const AcString& left, const AcString& right);
    /// <description>
    /// Compare the string case-independently to another string
    /// </description>
    /// <param name="psz">input pointer to the string of chars to compare to </param>
    /// <returns>
    /// Zero if the strings are identical, <0 if this AcString object is less than psz, or >0 if this AcString object is greater than psz.
    /// </returns>
  ACBASE_PORT int collateNoCase(const wchar_t* psz) const;
    /// <description>
    /// Compare the string case-independently to another AcString
    /// </description>
    /// <param name="acs"> input reference to the other AcString to compare to </param>
    /// <returns>
    /// Zero if the strings are identical, <0 if this AcString object is less than acs, or >0 if this AcString object is greater than acs.
    /// </returns>
  int collateNoCase(const AcString& acs) const;
  bool operator ==(wchar_t wch) const;
  bool operator ==(const wchar_t* pwsz) const;
  bool operator ==(const AcString& acs) const;
  bool operator !=(wchar_t wch) const;
  bool operator !=(const wchar_t* pwsz) const;
  bool operator !=(const AcString& acs) const;
  bool operator >(wchar_t wch) const;
  bool operator >(const wchar_t* pwsz) const;
  bool operator >(const AcString& acs) const;
  bool operator >=(wchar_t wch) const;
  bool operator >=(const wchar_t* pwsz) const;
  bool operator >=(const AcString& acs) const;
  bool operator <(wchar_t wch) const;
  bool operator <(const wchar_t* pwsz) const;
  bool operator <(const AcString& acs) const;
  bool operator <=(wchar_t wch) const;
  bool operator <=(const wchar_t* pwsz) const;
  bool operator <=(const AcString& acs) const;
  ACBASE_PORT int match(const char* psz, Encoding encoding) const;
  ACBASE_PORT int match(const wchar_t* pwsz) const;
  ACBASE_PORT int match(const AcString& acs) const;
  ACBASE_PORT int matchNoCase(const char* psz, Encoding encoding) const;
  ACBASE_PORT int matchNoCase(const wchar_t* pwsz) const;
  ACBASE_PORT int matchNoCase(const AcString& acs) const;
    /// <description>
    /// Make the lower case letters ('a' ~ 'z') to upper case letters.
    /// </description>
    /// <returns> Reference to this AcString.</returns>
  ACBASE_PORT AcString& makeUpper();
    /// <description>
    /// Make the upper case letters ('A' ~ 'Z') to lower case letters.
    /// </description>
    /// <returns> Reference to this AcString.</returns>
  ACBASE_PORT AcString& makeLower();
    /// <description>
    /// make the string reversed
    /// </description>
    /// <returns>
    /// </returns>
  ACBASE_PORT AcString& makeReverse();
    /// <summary> Remove designated character wch from beginning of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> No-op if wch arg is null character.</remarks>
    ///
  ACBASE_PORT AcString& trimLeft(wchar_t wch);
    /// <summary> Remove designated character wch from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> No-op if wch arg is null character.</remarks>
    ///
  ACBASE_PORT AcString& trimRight(wchar_t wch);
    /// <summary> Remove designated character wch from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> No-op if wch arg is null character.</remarks>
    ///
  ACBASE_PORT AcString& trim(wchar_t wch);
    /// <summary> Remove all whitespace characters from beginning of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
  AcString& trimLeft();
    /// <summary> Remove all designated characters from beginning of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is null.</remarks>
    ///
  ACBASE_PORT AcString& trimLeft(const wchar_t* pwszChars);
    /// <summary> Remove all whitespace characters from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
  AcString& trimRight();
    /// <summary> Remove all designated characters from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is null.</remarks>
    ///
  ACBASE_PORT AcString& trimRight(const wchar_t* pwszChars);
    /// <summary> Remove all whitespace characters from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
  AcString& trim();
    /// <summary> Remove all designated characters from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is null.</remarks>
    ///
  ACBASE_PORT AcString& trim(const wchar_t* pwszChars);
    /// <summary> Remove all occurrences of the specified character.
    /// <returns> Number of characters removed. Zero if the string was not changed.</returns>
    /// <remarks> Removes whitespace chars if wch arg is zero.</remarks>
    ///
  ACBASE_PORT int remove(wchar_t wch);
    /// <summary> Remove all occurrences of whitespace.
    /// <returns> Number of characters removed. Zero if the string was not changed.</returns>
    ///
  int remove()
  {
    return this->remove(0);
  }
    /// <summary> Extract substring up to the first instance of a designated character.</summary>
    /// <returns> AcString that contains the substring</returns>
    ///
  ACBASE_PORT AcString spanExcluding(const wchar_t* pwszChars) const;
#  if   defined(_AFX) || defined (__OSX_WINAPI_UNIX_STRING_H__) || defined(__ATLSTR_H__)
  AcString(const CStringW& csw);
  AcString& operator =(const CStringW& csw);
  AcString& operator +=(const CStringW& csw);
  int compare(const CStringW& csw) const;
  int compareNoCase(const CStringW& csw) const;
  bool operator ==(const CStringW&) const;
  bool operator !=(const CStringW&) const;
  bool operator <(const CStringW&) const;
  bool operator <=(const CStringW&) const;
  bool operator >(const CStringW&) const;
  bool operator >=(const CStringW&) const;
  int match(const CStringW& csw) const;
  int matchNoCase(const CStringW& csw) const;
#  endif
    /// <description>
    /// Rplaces instances of the substring with instances of the new string 
    /// </description>
    /// <param name="pwszOld"> A pointer to a string containing the character to be replaced by lpszNew. </param>
    /// <param name="pwszNew"> A pointer to a string containing the character replacing lpszOld. </param>
    /// <returns>
    /// Return the number of replaced instances of the substring. Zero if the string is not changed.
    /// </returns>
  ACBASE_PORT int replace(const wchar_t* pwszOld, const wchar_t* pwszNew);
    /// <description>
    /// Replace a character with another.
    /// </description>
    /// <param name="wchOld"> character that will be replaced </param>
    /// <param name="wchNew"> new character that will be replaced with </param>
    /// <returns>
    /// Return the number of replaced instances of the wchOld. Zero if the string is not changed.
    /// </returns>
  ACBASE_PORT int replace(wchar_t wchOld, wchar_t wchNew);
    /// <description>
    /// Deletes character(s) from a string starting with the character at given index.
    /// </description>
    /// <param name="iIndex"> start position to delete </param>
    /// <param name="nCount"> character number to be deleted </param>
    /// <returns>
    /// Return the length of the changed string.
    /// </returns>
  ACBASE_PORT int deleteAtIndex(int iIndex, int nCount = 1);
    /// <description>
    /// Finds the next token in a target string
    /// </description>
    /// <param name="pszTokens">A string containing token delimiters. The order of these delimiters is not important.</param>
    /// <param name="iStart">The zero-based index to begin the search.</param>
    /// <returns>
    /// return an AcString object containing the current token value.
    /// </returns>
  ACBASE_PORT AcString tokenize(const wchar_t* pszTokens, int& iStart);
    /// <description>
    /// Set the character at the given postion to the specified character.
    /// </description>
    /// <param name="nIndex">Zero-based postion of character in the string.</param>
    /// <param name="ch">The new character to replace the old one.</param>
    /// <returns>
    /// Return the AcString object after character is set
    /// </returns>
  ACBASE_PORT AcString& setAt(int nIndex, ACHAR ch);
    /// <description>
    /// Get one character at the given postion from the string.
    /// </description>
    /// <param name="nIndex">Zero-based postion of character in the string.</param>
    /// <returns> Return the character at the specified position in the string </returns>
    /// <remarks> Does NOT do range checking on the nIndex arg.
    ///           Results for out of range nIndex args are unpredictable.
    ///           Indexing via [] may also work, causing an implicit call to
    ///           the const wchar_t * operator
    /// </remarks>
  wchar_t getAt(int nIndex) const;
    /// <summary>
    /// Inserts a single character at the given index within the string.
    /// </summary>
    /// <param name="nIndex">The index of the character before which the insertion will take place.</param>
    /// <param name="ch">The character to be inserted.</param>
  ACBASE_PORT AcString& insert(int nIndex, wchar_t ch);
    /// <description>
    /// Inserts a substring at the given index within the string.
    /// </description>
    /// <param name="nIndex">The index of the character before which the insertion will take place.</param>
    /// <param name="ch">A pointer to the substring to be inserted.</param>
    /// <returns>
    /// Return the AcString object after substring is inserted
    /// </returns>
  ACBASE_PORT AcString& insert(int nIndex, const wchar_t* pwsz);
    /// <description>
    /// Returns a wchar_t pointer to the internal character buffer for the string object. 
    /// The returned buffer allows direct modification of string contents. If you use the
    /// pointer returned by getBuffer to change the string contents, you must call releaseBuffer
    /// before using any other non-const member functions. After calling the function, 
    /// it may reallocate the internal buffer to meet the input buffer size.
    /// So after call getBuffer function, it is invalid to call other AcString modified operations
    /// like utf8Ptr(), assign(), append() and so on.
    /// </description>
    /// <param name="nMinBufferLength">The minimum size of the character buffer in characters. 
    /// This value does not include space for a null terminator.
    /// If nMinBufferLength is less than current buffer size, then current buffer is returned.
    /// If it's greater than current buffer size, then the buffer is enlarged.
    /// </param>
    /// <returns>
    /// wchar_t pointer to the object’s (null-terminated) character buffer.
    /// Fails and returns nullptr if nMinBufferLength is < 0.
    /// </returns>
  ACBASE_PORT ACHAR* getBuffer(int nMinBufferLength = 0);
    /// <description>
    /// Use releaseBuffer() to end use of a buffer allocated by getBuffer function.
    /// The address returned by getBuffer is invalid after the call to releaseBuffer.
    /// </description>
    /// <param name="nMinBufferLength">The new length of the string in characters,
    /// not counting a null terminator.
    /// If the string is null-terminated, the -1 default value sets the string size to
    /// the current length of the string.
    /// It should be smaller than the buffer length specified when calling getBuffer function.
    /// </param>
    /// <returns>
    /// return true if succeed.
    /// </returns>
  ACBASE_PORT bool releaseBuffer(int nNewLength = -1);
private:
  friend class AcStringImp;
  wchar_t* m_wsz;
};
#  ifdef AC_ACARRAY_H
typedef AcArray< AcString, AcArrayObjectCopyReallocator< AcString > > AcStringArray;
#  endif
bool operator ==(wchar_t wch, const AcString& acs);
bool operator ==(const wchar_t* pwsz, const AcString& acs);
bool operator !=(wchar_t wch, const AcString& acs);
bool operator !=(const wchar_t* pwsz, const AcString& acs);
bool operator >(wchar_t wch, const AcString& acs);
bool operator >(const wchar_t* pwsz, const AcString& acs);
bool operator >=(wchar_t wch, const AcString& acs);
bool operator >=(const wchar_t* pwsz, const AcString& acs);
bool operator <(wchar_t wch, const AcString& acs);
bool operator <(const wchar_t* pwsz, const AcString& acs);
bool operator <=(wchar_t wch, const AcString& acs);
bool operator <=(const wchar_t* pwsz, const AcString& acs);
AcString operator +(wchar_t wch, const AcString& acs);
AcString operator +(const wchar_t* pwsz, const AcString& acs);
operator const wchar_t*() const
{
  return this->kwszPtr();
}
inline const wchar_t* AcString::constPtr() const
{
  return this->kwszPtr();
}
inline const wchar_t* AcString::kTCharPtr() const
{
  return this->kwszPtr();
}
inline const ACHAR* AcString::kACharPtr() const
{
  return this->kwszPtr();
}
inline bool AcString::isEmpty() const
{
  return this->m_wsz[0] == L'\0';
}
inline wchar_t AcString::getAt(int nIndex) const
{
  return this->m_wsz[nIndex];
}
inline int AcString::find(ACHAR ch) const
{
  const ACHAR str[2] = {ch, '\0'};
  return this->findOneOf(str);
}
inline int AcString::findRev(ACHAR ch) const
{
  const ACHAR str[2] = {ch, '\0'};
  return this->findOneOfRev(str);
}
inline AcString AcString::mid(int nStart, int nNumChars) const
{
  return this->substr(nStart, nNumChars);
}
inline AcString AcString::mid(int nStart) const
{
  return this->mid(nStart, -1);
}
inline AcString AcString::substr(int nNumChars) const
{
  return this->substr(0, nNumChars);
}
inline AcString AcString::left(int nNumChars) const
{
  return this->substr(nNumChars);
}
inline AcString AcString::right(int nNumChars) const
{
  return this->substrRev(nNumChars);
}
inline AcString& AcString::trimLeft(wchar_t wch)
{
  const wchar_t wszChars[] = {wch, L'\0'};
  return this->trimLeft(wszChars);
}
inline AcString& AcString::trimLeft()
{
  return this->trimLeft(nullptr);
}
inline AcString& AcString::trimRight(wchar_t wch)
{
  const wchar_t wszChars[] = {wch, L'\0'};
  return this->trimRight(wszChars);
}
inline AcString& AcString::trimRight()
{
  return this->trimRight(nullptr);
}
inline AcString& AcString::trim(wchar_t wch)
{
  const wchar_t wszChars[] = {wch, L'\0'};
  return this->trim(wszChars);
}
inline AcString& AcString::trim()
{
  return this->trim(nullptr);
}
inline AcString& AcString::trim(const wchar_t* pwszChars)
{
  return this->trimRight(pwszChars).trimLeft(pwszChars);
}
inline AcString& AcString::assign(wchar_t wch)
{
  const wchar_t wstr[2] = {wch, L'\0'};
  return this->assign(wstr);
}
inline AcString& AcString::operator =(wchar_t wch)
{
  return this->assign(wch);
}
inline AcString& AcString::operator =(const wchar_t* pwsz)
{
  return this->assign(pwsz);
}
inline AcString& AcString::operator =(const AcString& acs)
{
  return this->assign(acs);
}
inline AcString& AcString::operator =(const AcDbHandle& h)
{
  return this->assign(h);
}
inline AcString& AcString::operator +=(wchar_t wch)
{
  return this->append(wch);
}
inline AcString& AcString::operator +=(const wchar_t* pwsz)
{
  return this->append(pwsz);
}
inline AcString& AcString::operator +=(const AcString& acs)
{
  return this->append(acs);
}
inline AcString& AcString::append(wchar_t wch)
{
  const wchar_t wstr[2] = {wch, L'\0'};
  return this->append(wstr);
}
inline AcString AcString::operator +(wchar_t wch) const
{
  return this->concat(wch);
}
inline AcString AcString::operator +(const wchar_t* pwsz) const
{
  return this->concat(pwsz);
}
inline AcString AcString::operator +(const AcString& acs) const
{
  return this->concat(acs);
}
inline AcString AcString::concat(wchar_t wch) const
{
  const wchar_t wstr[2] = {wch, L'\0'};
  return this->concat(wstr);
}
inline AcString AcString::precat(wchar_t ch) const
{
  const wchar_t str[2] = {ch, '\0'};
  return this->precat(str);
}
inline const wchar_t* AcString::kwszPtr() const
{
  return this->m_wsz;
}
inline int AcString::compare(wchar_t wch) const
{
  const wchar_t wstr[2] = {wch, L'\0'};
  return this->compare(wstr);
}
inline int AcString::compare(const AcString& acs) const
{
  return this->compare(acs.kwszPtr());
}
inline int AcString::compareNoCase(wchar_t wch) const
{
  const wchar_t wstr[2] = {wch, L'\0'};
  return this->compareNoCase(wstr);
}
inline int AcString::compareNoCase(const AcString& acs) const
{
  return this->compareNoCase(acs.kwszPtr());
}
inline int AcString::collate(const AcString& acs) const
{
  return this->collate(acs.kwszPtr());
}
inline int AcString::collateNoCase(const AcString& acs) const
{
  return this->collateNoCase(acs.kwszPtr());
}
inline bool AcString::operator ==(wchar_t wch) const
{
  return this->compare(wch) == 0;
}
inline bool AcString::operator ==(const wchar_t* pwsz) const
{
  return this->compare(pwsz) == 0;
}
inline bool AcString::operator ==(const AcString& acs) const
{
  return this->compare(acs) == 0;
}
inline bool AcString::operator !=(wchar_t wch) const
{
  return this->compare(wch) != 0;
}
inline bool AcString::operator !=(const wchar_t* pwsz) const
{
  return this->compare(pwsz) != 0;
}
inline bool AcString::operator !=(const AcString& acs) const
{
  return this->compare(acs) != 0;
}
inline bool AcString::operator >(wchar_t wch) const
{
  return this->compare(wch) > 0;
}
inline bool AcString::operator >(const wchar_t* pwsz) const
{
  return this->compare(pwsz) > 0;
}
inline bool AcString::operator >(const AcString& acs) const
{
  return this->compare(acs) > 0;
}
inline bool AcString::operator >=(wchar_t wch) const
{
  return this->compare(wch) >= 0;
}
inline bool AcString::operator >=(const wchar_t* pwsz) const
{
  return this->compare(pwsz) >= 0;
}
inline bool AcString::operator >=(const AcString& acs) const
{
  return this->compare(acs) >= 0;
}
inline bool AcString::operator <(wchar_t wch) const
{
  return this->compare(wch) < 0;
}
inline bool AcString::operator <(const wchar_t* pwsz) const
{
  return this->compare(pwsz) < 0;
}
inline bool AcString::operator <(const AcString& acs) const
{
  return this->compare(acs) < 0;
}
inline bool AcString::operator <=(wchar_t wch) const
{
  return this->compare(wch) <= 0;
}
inline bool AcString::operator <=(const wchar_t* pwsz) const
{
  return this->compare(pwsz) <= 0;
}
inline bool AcString::operator <=(const AcString& acs) const
{
  return this->compare(acs) <= 0;
}
inline bool operator ==(wchar_t wch, const AcString& acs)
{
  return acs.compare(wch) == 0;
}
inline bool operator ==(const wchar_t* pwsz, const AcString& acs)
{
  return acs.compare(pwsz) == 0;
}
inline bool operator !=(wchar_t wch, const AcString& acs)
{
  return acs.compare(wch) != 0;
}
inline bool operator !=(const wchar_t* pwsz, const AcString& acs)
{
  return acs.compare(pwsz) != 0;
}
inline bool operator >(wchar_t wch, const AcString& acs)
{
  return acs.compare(wch) < 0;
}
inline bool operator >(const wchar_t* pwsz, const AcString& acs)
{
  return acs.compare(pwsz) < 0;
}
inline bool operator >=(wchar_t wch, const AcString& acs)
{
  return acs.compare(wch) <= 0;
}
inline bool operator >=(const wchar_t* pwsz, const AcString& acs)
{
  return acs.compare(pwsz) <= 0;
}
inline bool operator <(wchar_t wch, const AcString& acs)
{
  return acs.compare(wch) > 0;
}
inline bool operator <(const wchar_t* pwsz, const AcString& acs)
{
  return acs.compare(pwsz) > 0;
}
inline bool operator <=(wchar_t wch, const AcString& acs)
{
  return acs.compare(wch) >= 0;
}
inline bool operator <=(const wchar_t* pwsz, const AcString& acs)
{
  return acs.compare(pwsz) >= 0;
}
inline AcString operator +(ACHAR ch, const AcString& acs)
{
  return acs.precat(ch);
}
inline AcString operator +(const wchar_t* pwsz, const AcString& acs)
{
  return acs.precat(pwsz);
}
inline bool AcString::equalsNoCase(const AcString& left, const AcString& right)
{
  return left.compareNoCase(right) == 0;
}
class AcUniqueString
{
public:
  ACBASE_PORT static const AcUniqueString* Intern(const wchar_t*);
};
#  if  defined(_AFX) || defined(__OSX_WINAPI_UNIX_STRING_H__) || defined(__ATLSTR_H__)
inline AcString::AcString(const CStringW& csw)
  : AcString()
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  *this = pwsz;
}
inline AcString& AcString::operator=(const CStringW& csw)
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  return this->assign(pwsz);
}
inline AcString& AcString::operator+=(const CStringW& csw)
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  return this->append(pwsz);
}
inline int AcString::compare(const CStringW& csw) const
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  return this->compare(pwsz);
}
inline int AcString::compareNoCase(const CStringW& csw) const
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  return this->compareNoCase(pwsz);
}
inline int AcString::match(const CStringW& csw) const
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  return this->match(pwsz);
}
inline int AcString::matchNoCase(const CStringW& csw) const
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  return this->matchNoCase(pwsz);
}
inline bool AcString::operator ==(const CStringW& csw) const
{
  return this->compare(csw) == 0;
}
inline bool AcString::operator !=(const CStringW& csw) const
{
  return this->compare(csw) != 0;
}
inline bool AcString::operator >(const CStringW& csw) const
{
  return this->compare(csw) > 0;
}
inline bool AcString::operator >=(const CStringW& csw) const
{
  return this->compare(csw) >= 0;
}
inline bool AcString::operator <(const CStringW& csw) const
{
  return this->compare(csw) < 0;
}
inline bool AcString::operator <=(const CStringW& csw) const
{
  return this->compare(csw) <= 0;
}
#    if  defined(_AFX) && !defined(__cplusplus_cli)
inline bool operator ==(const CStringW& csw, const AcString& acs)
{
  return acs.compare(csw) == 0;
}
inline bool operator !=(const CStringW& csw, const AcString& acs)
{
  return acs.compare(csw) != 0;
}
inline bool operator >(const CStringW& csw, const AcString& acs)
{
  return acs.compare(csw) < 0;
}
inline bool operator >=(const CStringW& csw, const AcString& acs)
{
  return acs.compare(csw) <= 0;
}
inline bool operator <(const CStringW& csw, const AcString& acs)
{
  return acs.compare(csw) > 0;
}
inline bool operator <=(const CStringW& csw, const AcString& acs)
{
  return acs.compare(csw) >= 0;
}
#      ifndef DISABLE_CSTRING_PLUS_ACSTRING
inline AcString operator +(const CStringW& csw, const AcString& acs)
{
  const wchar_t* pwsz = (const wchar_t*) csw;
  return acs.precat(pwsz);
}
#      endif
#    endif
#  endif
#endif
