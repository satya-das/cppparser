//
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
#define _Ac_String_h_

#include "acbasedefs.h"
#include "adesk.h"
#include "AcHeapOpers.h"
#include "AdAChar.h"
#include "rxresource.h"
#include <cstdarg>

class AcDbHandle;
class AcRxResourceInstance;

// Notes:
// 1. All wchar_t arguments are assumed to be "widechar" Unicode values.
// 2. The pointer returned from utf8Ptr() and kwszPtr() is valid until the next time
//    AcString is modified.
// 3. Never cast away const from a pointer obtained by utf8Ptr() or kwszPtr() buffer, in order
//    to modify the buffer directly. These buffers may be shared by multiple AcString instances.
//    Instead, to operate on buffers directly, first call getBuffer() to obtain a pointer
// 4. Although utf8Ptr() is a const member function, it may reallocate the string's
//    internal buffer and thus invalidate pointers returned by a previous kwszPtr() call
//

class AcString : public AcHeapOperators
{
public:
    // Encoding type
    enum Encoding { Utf8 };

    //
    // Constructors and destructor
    //
    // Default ctor, initializes to empty string.
    ACBASE_PORT AcString();

    // Initialize with a single Unicode character
    // wch : input character
    ACBASE_PORT AcString(wchar_t wch);

    // Initialize from utf-8 string.
    // psz : input pointer to source string.
    ACBASE_PORT AcString(const char *psz, Encoding encoding);

    // Initialize from a Unicode string
    // wpsz : input pointer to zero terminated source string
    ACBASE_PORT AcString(const wchar_t *pwsz);

    // Initialize from a Unicode string
    // wpsz : input pointer to source
    // count: number of characters to use from the input string
    ACBASE_PORT AcString(const wchar_t *pwsz, unsigned int count);

    // Copy constructor
    // acs : input reference to an existing AcString object
    ACBASE_PORT AcString(const AcString & acs);

    // Move constructor
    // acs : input reference to an existing temp AcString object
    ACBASE_PORT AcString(AcString && acs);

    // Values for the nCtorFlags arg of the following constructor
    enum eFormat {
        kSigned = 0x0002,   // format the arg as signed int
        kUnSigned = 0x0003, // format the arg as unsigned int
        kHex = 0x0004  // format the arg as hex
    };

    // Multi-purpose constructor, takes an unsigned argument and
    // uses it either to load a resource string or to create a
    // numerical string (base 10 or hex).
    //
    // nCtorFlags : input flags, indicating type of construction
    // nArg : input argument value, interpreted according to flags
    
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
    ACBASE_PORT AcString(const AcDbHandle &h);
    /// <description>
    ///  Load String from resource instance
    /// </description>
    /// <param name="hDll">AxResourceInstance object to load string</param>
    /// <param name="nId">input id of the string resource in the specified resource dll</param>
    ACBASE_PORT AcString(const AcRxResourceInstance& hDll, unsigned int nId);

    // Destructor: frees up memory.
    ACBASE_PORT ~AcString();

    //
    // Querying methods
    //

    // Get a pointer to the current string as Unicode UTF-8.  This
    // pointer is only valid until the AcString object is modified!
    ACBASE_PORT const char * utf8Ptr() const;

    // Get a pointer to the current string (in Unicode).  This pointer
    // is only valid until this AcString object is next modified!
    const wchar_t * kwszPtr() const;

    // Get a pointer to the current string as a wchar_t pointer.
    // Pointer is only valid until this AcString is next modified.
    const wchar_t *  constPtr() const;
    const wchar_t * kTCharPtr() const;

    // Get a pointer to the current string in ACHARs.
    const ACHAR * kACharPtr() const;

    // Get a pointer to the current string (in Unicode).  Pointer
    // is valid only until this AcString is next modified.
    operator const wchar_t * () const;

    // Test whether the current string value is empty.  I.e.,
    // logical length is zero.
    bool isEmpty() const;

    // Return logical length of (i.e. number of characters in) the string.
    //
    ACBASE_PORT unsigned length() const;

    // Return length of the current string, in wchar_t units.
    // Deprecated. Please use length() instead
    unsigned tcharLength() const
    {
        return this->length();
    }

    // Returns the number of characters (not including the null terminator)
    // that this string can contain without growing its buffer
    // Note that capacity() is always >= length()
    ACBASE_PORT unsigned capacity() const;

    // Grows or (possibly) shrinks the buffer to match the requested capacity 
    // Shrink requests may be ignored, depending on current buffer size,
    // string length and refcount.
    // Returns true if the buffer was reallocated, false if not
    ACBASE_PORT bool reserve(unsigned nCapacity);

    // Returns true if all chars are in the ascii range: 0x20..0x7f
    ACBASE_PORT bool isAscii() const;

    //
    // Parsing methods.
    //
    enum {
        // Enum value allowing caller to specify how to handle errors
        // (invalid chars or overflow) during string parsing.
        kParseZero = 0,       // return zero on errors
        kParseMinus1 = 0x01,  // return -1 or ffff
        kParseAssert = 0x02,  // pop an assert in debug build
        kParseExcept = 0x04,  // throw an int exception
        kParseNoEmpty = 0x08, // treat empty string as error
        kParseDefault = (kParseAssert | kParseZero)
    };

    // Parse the current string as decimal, return a signed int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT int asDeci(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return a signed int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT int asHex(int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return an unsigned int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT unsigned int asUDeci(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return an unsigned int
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT unsigned int asUHex(int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return a signed int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT int64_t asDeci64(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return a signed int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT int64_t asHex64(int nFlags = kParseDefault) const;

    // Parse the current string as decimal, return an unsigned int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT Adesk::UInt64 asUDeci64(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal, return an unsigned int64
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT Adesk::UInt64 asUHex64(int nFlags = kParseDefault) const;

    // Parse the current string as hexadecimal.  Return the handle.
    // nFlags : input bits specifying how to do the parsing
    ACBASE_PORT AcDbHandle asAcDbHandle(int nFlags = kParseDefault) const;

    //
    // Find char/string/one of a string of chars, from front or back
    // Return the position (index) at which the character or substring
    // was found.
    //
    // The find methods which start at the end of the string return
    // an index relative to the front of the string.

    // Find a single char in the string.
    // ch : input char to search for
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
    ACBASE_PORT int find(const ACHAR *psz) const;

    // Find an AcString in the string.
    // acs : input string object to search for
    ACBASE_PORT int find(const AcString & acs) const;

    // Find any of a group of chars in the string.
    // psz : input pointer to string of chars to search for
    ACBASE_PORT int findOneOf(const ACHAR *psz) const;

    // Find last occurrence of a char in the string
    // ch : input char to search for
    int findRev(ACHAR ch) const;

    // Find last occurrence of any of a group of chars in the string
    // psz : input pointer to string of chars to search for
    ACBASE_PORT int findRev(const ACHAR *psz) const;

    // Find last occurrence of a group of chars in the string
    // psz : input ptr to the string of chars to search for
    ACBASE_PORT int findOneOfRev(const ACHAR *psz) const;

    // Find last occurrence of a string in the string
    // acs : input reference to the string to search for
    ACBASE_PORT int findRev(const AcString & acs) const;

    //
    // Extraction methods
    // Note: mid() and substr() are the same thing - we define both
    //       for compatibility with CString and std::string
    //
    // The input index arguments are byte indices into the string.

    /// <description>
    ///  Get a substring from the zero-based nStart position to the end of the string.
    /// </description>
    /// <param name="nStart">The zero-based start position of the substring to get.</param>
    /// <returns>
    /// return the substring
    /// </returns>
    AcString mid(int nStart) const;

    // Get a substring from the string.  (same as substr() method)
    // nStart : input index (in bytes) from the start of the string
    // nNumChars : input number of chars (not bytes) to retrieve.
    //             if nNumChars is -1, then return the rest of the string
    AcString mid(int nStart, int nNumChars) const;

    // Get a substring from the start of string.
    // nNumChars : input number of chars (not bytes) to retrieve.
    //             if nNumChars is -1, then return the rest of the string
    AcString substr(int numChars) const;

    // Get a substring from the string.  (same as mid() method)
    // nStart : input index (in bytes) from the start of the string
    // nNumChars : input number of chars (not bytes) to retrieve.
    //             if nNumChars is -1, then return the rest of the string
    ACBASE_PORT AcString substr(int nStart, int nNumChars) const;

    // Get a substring from the end of string.
    // nNumChars : input number of chars (not bytes) to retrieve.
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

    //
    // Assignment operators and methods
    //
    
    // assign a Unicode char to the string
    // wch : input char to assign
    AcString & assign(wchar_t wch);

    // assign a string of (ansi) chars to the string
    // psz : input pointer to the string of chars to assign
    // encoding: input Encoding type
   ACBASE_PORT  AcString & assign(const char *psz, Encoding encoding);

    // assign a string of Unicode chars to the string
    // pwsz : input pointer to the string of chars to assign
    ACBASE_PORT AcString & assign(const wchar_t *pwsz);

    // assign an AcString object to the string
    // acs : input reference to the AcString
    ACBASE_PORT AcString & assign(const AcString & acs);

    // assign an AcDbHandle object to the string (format it as hex)
    // h : input reference to the AcDbHandle object
    ACBASE_PORT AcString & assign(const AcDbHandle & h);

    // assign a Unicode char to the string
    // wch : input char to assign
    AcString & operator = (wchar_t wch);

    // assign a string of Unicode chars to the string
    // pwsz : input pointer to the string of chars to assign
    AcString & operator = (const wchar_t *pwsz);

    // assign an AcString object to the string
    // acs : input reference to the AcString
    AcString & operator = (const AcString & acs);

    // move a temp AcString object to the string
    // acs : input reference to the temp AcString
    ACBASE_PORT AcString & operator = (AcString && acs);

    // assign an AcDbHandle object to the string (format it as hex)
    // h : input reference to the AcDbHandle object
    AcString & operator = (const AcDbHandle & h);

    // Set the string to be empty.
    ACBASE_PORT AcString & setEmpty();

    // Set the string from a resource string
    // hDll : AxResourceInstance object to load string
    // nId : input id of the string resource in the specified resource dll
    ACBASE_PORT bool loadString(const AcRxResourceInstance& hDll, unsigned nId);

    // Format the string using "printf" rules.
    // pszFmt : input pointer to the printf format string
    ACBASE_PORT AcString & format (const ACHAR    *pszFmt,  ...);

    // Format the string using "printf" rules
    // pszFmt : input pointer to the printf format string
    // args : input variable args list, containing values to be formatted
    ACBASE_PORT AcString & formatV(const ACHAR   *pszFmt,  va_list args);

    /// <description>
    /// Append formated data to this string using "printf" rules
    /// </description>
    /// <param name="pszFmt">input pointer to the printf format string</param>
    /// <param name="args">input variable args list, containing values to be formatted</param>
    /// <returns> Reference to this AcString.</returns>
    ACBASE_PORT AcString & appendFormat(const ACHAR   *pszFmt, ...);

    //
    // Modifying operators and methods
    //

    // append a Unicode char to the end of the string
    // wch : input char to append
    AcString & operator += (wchar_t wch);

    // append a Unicode string to the end of the string
    // pwsz : input pointer to the Unicode string
    AcString & operator += (const wchar_t * pwsz);

    // append an AcString object to the end of the string
    // acs : input reference to the AcString
    AcString & operator += (const AcString & acs);

    // append a Unicode char to the end of the string
    // wch : input char to append
    AcString & append(wchar_t wch);

    // append a char string to the end of the string
    // psz : input pointer to the (ansi) char string
    // encoding: input Encoding type
    ACBASE_PORT AcString & append(const char *psz, Encoding encoding);

    // append a Unicode string to the end of the string
    // pwsz : input pointer to the Unicode string
    ACBASE_PORT AcString & append(const wchar_t *pwsz);

    // append an AcString object to the end of the string
    // acs : input reference to the AcString
    ACBASE_PORT AcString & append(const AcString & acs);

    // Catenation operators and methods  These are like append,
    // but they do not modify the current string.  They return a
    // new combined string.

    // Copy the string and append a Unicode char to it
    // ch : input char to append to the string copy
    AcString operator + (wchar_t wch) const;

    // Copy the string and append a string of Unicode chars to it
    // pwsz : input pointer to the string to append
    AcString operator + (const wchar_t * pwsz) const;

    // Copy the string and append an AcString to it
    // pwsz : input reference to the AcString to append
    AcString operator + (const AcString & acs) const;

    // Copy the string and append a Unicode char to it
    // ch : input char to append to the string copy
    AcString concat(wchar_t wch) const;

    // Copy the string and append a string of chars to it
    // psz : input pointer to the (ansi) string to append
    // encoding: input Encoding type
    ACBASE_PORT AcString concat(const char * psz, Encoding encoding) const;

    // Copy the string and append a string of Unicode chars to it
    // pwsz : input pointer to the string to append
    ACBASE_PORT AcString concat(const wchar_t * pwsz) const;

    // Copy the string and append an AcString to it
    // pwsz : input reference to the AcString to append
    ACBASE_PORT AcString concat(const AcString & acs) const;

    // These copy the current string and then insert the char or
    // string in front of it.  They're used by the global "+" operators.

    // Copy the string and insert a char in front of it
    // ch : input char to insert
    AcString precat(ACHAR ch) const;

    // Copy the string and insert a string of chars in front of it
    // psz : input pointer to the string of (ansi) chars to insert
    // encoding: input Encoding type
    ACBASE_PORT AcString precat(const char * psz, Encoding encoding) const;

    // Copy the string and insert a string of chars in front of it
    // psz : input pointer to the string of chars to insert
    ACBASE_PORT AcString precat(const wchar_t * psz) const;

    //
    // Comparison operators and methods
    // The int return value is -1, 0 or 1, indicating <, == or >
    //

    // Compare the string to a single Unicode char
    // wch : input char to compare to
    int  compare(wchar_t wch) const;

    // Compare the string to a string of (ansi) chars
    // psz : input pointer to the string of chars to compare to
    // encoding: input Encoding type
    ACBASE_PORT int  compare(const char *psz, Encoding encoding) const;

    // Compare the string to a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    ACBASE_PORT int  compare(const wchar_t *pwsz) const;

    // Compare the string to a string of Unicode chars
    // acs : input reference of the other AcString to compare to
    int  compare(const AcString & acs) const;


    /// <description>
    /// Compare the string to another string using collation
    /// </description>
    /// <param name="pwsz">input pointer to the string of chars to compare to</param>
    /// <returns>
    /// Zero if the strings are identical, <0 if this AcString object is less than lpsz, or >0 if this AcString object is greater than lpsz.
    /// </returns>
    ACBASE_PORT int  collate (const wchar_t *pwsz) const;
    
    /// <description>
    /// Compare the string to another AcString object using collation
    /// </description>
    /// <param name="acs">input AcString object to compare to </param>
    /// <returns>
    /// Zero if the strings are identical, <0 if this AcString object is less than acs, or >0 if this AcString object is greater than acs.
    /// </returns>
    int  collate(const AcString & acs) const;

    // Compare the string case-independently to a Unicode char
    // wch : input char to compare to
    int  compareNoCase(wchar_t wch) const;

    // Compare the string case-independently to a string of chars
    // psz : input pointer to the string of (ansi) chars to compare to
    // encoding: input Encoding type
    ACBASE_PORT int  compareNoCase(const char *psz, Encoding encoding) const;

    // Compare the string case-independently to a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    ACBASE_PORT int  compareNoCase(const wchar_t *pwsz) const;

    // Compare the string case-independently to another AcString
    // acs : input reference to the other AcString
    int  compareNoCase(const AcString & acs) const;

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
    ACBASE_PORT int collateNoCase(const wchar_t *psz) const;

    /// <description>
    /// Compare the string case-independently to another AcString
    /// </description>
    /// <param name="acs"> input reference to the other AcString to compare to </param>
    /// <returns>
    /// Zero if the strings are identical, <0 if this AcString object is less than acs, or >0 if this AcString object is greater than acs.
    /// </returns>
    int collateNoCase(const AcString& acs) const;

    // Compare the string for equality with a Unicode char
    // wch : input char to compare to
    bool operator == (wchar_t wch) const;

    // Compare the string for equality with a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator == (const wchar_t *pwsz) const;

    // Compare the string for equality with another AcString
    // acs : input reference to the other AcString
    bool operator == (const AcString & acs) const;

    // Compare the string for non-equality with a Unicode char
    // wch : input char to compare to
    bool operator != (wchar_t wch) const;

    // Compare the string for non-equality with a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator != (const wchar_t *pwsz) const;

    // Compare the string for non-equality with another AcString
    // acs : input reference to the other AcString
    bool operator != (const AcString & acs) const;

    // Compare the string for greater than a Unicode char
    // wch : input char to compare to
    bool operator >  (wchar_t wch) const;

    // Compare the string for greater than a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    bool operator >  (const wchar_t *pwsz) const;

    // Compare the string for greater than another AcString
    // acs : input reference to the other AcString
    bool operator >  (const AcString & acs) const;

    // Compare the string for greater than or equal to a Unicode char
    // wch : input char to compare to
    bool operator >= (wchar_t wch) const;

    // Compare the string for greater than/equal to a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator >= (const wchar_t *pwsz) const;

    // Compare the string for greater than or equal to another AcString
    // acs : input reference to the other AcString
    bool operator >= (const AcString & acs) const;

    // Compare the string for less than a Unicode char
    // wch : input char to compare to
    bool operator <  (wchar_t wch) const;

    // Compare the string for less than a string of Unicode chars
    // pwsz : input pointer to the string of chars to compare to
    bool operator <  (const wchar_t *pwsz) const;

    // Compare the string for less than another AcString
    // acs : input reference to the other AcString
    bool operator <  (const AcString & acs) const;

    // Compare the string for less than or equal to a Unicode char
    // wch : input char to compare to
    bool operator <= (wchar_t wch) const;

    // Compare the string for less than/equal to a string of Unicode chars
    // pwsz : input pointer to the string of chars
    bool operator <= (const wchar_t *pwsz) const;

    // Compare the string for less or equal to than another AcString
    // acs : input reference to the other AcString
    bool operator <= (const AcString & acs) const;

    // The match() methods return how many chars (not bytes) match
    // between two strings.  Not fully implemented yet (non-ascii
    // chars not supported yet).

    // Return the number of chars that match a string of chars
    // psz : input pointer to the string of (ansi) chars
    // encoding: input Encoding type
    ACBASE_PORT int  match(const char *psz, Encoding encoding) const;

    // Return the number of chars matching a string of Unicode chars
    // pwsz : input pointer to the string of chars
    ACBASE_PORT int  match(const wchar_t *pwsz) const;

    // Return the number of chars matching another AcString
    // acs : input reference to the other AcString
    ACBASE_PORT int  match(const AcString & acs) const;

    // Return number of chars case-independently matching a string of chars
    // psz : input pointer to the string of (ansi) chars
    // encoding: input Encoding type
    ACBASE_PORT int  matchNoCase(const char *psz, Encoding encoding) const;

    // Return number of chars case-indep'ly matching a string of Unicode chars
    // pwsz : input pointer to the string of chars
    ACBASE_PORT int  matchNoCase(const wchar_t *pwsz) const;

    // Return number of chars case-indep'ly matching another AcString
    // acs : input reference to the other AcString
    ACBASE_PORT int  matchNoCase(const AcString & acs) const;

    /// <description>
    /// Make the lower case letters ('a' ~ 'z') to upper case letters.
    /// </description>
    /// <returns> Reference to this AcString.</returns>
    ACBASE_PORT AcString & makeUpper();
    
    /// <description>
    /// Make the upper case letters ('A' ~ 'Z') to lower case letters.
    /// </description>
    /// <returns> Reference to this AcString.</returns>
    ACBASE_PORT AcString & makeLower();
    
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
    ACBASE_PORT AcString & trimLeft(wchar_t wch);

    /// <summary> Remove designated character wch from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> No-op if wch arg is null character.</remarks>
    ///
    ACBASE_PORT AcString & trimRight(wchar_t wch);

    /// <summary> Remove designated character wch from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> No-op if wch arg is null character.</remarks>
    ///
    ACBASE_PORT AcString & trim(wchar_t wch);

    /// <summary> Remove all whitespace characters from beginning of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
    AcString & trimLeft();

    /// <summary> Remove all designated characters from beginning of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is null.</remarks>
    ///
    ACBASE_PORT AcString & trimLeft(const wchar_t *pwszChars);

    /// <summary> Remove all whitespace characters from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
    AcString & trimRight();

    /// <summary> Remove all designated characters from the end of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is null.</remarks>
    ///
    ACBASE_PORT AcString & trimRight(const wchar_t *pwszChars);

    /// <summary> Remove all whitespace characters from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    ///
    AcString & trim();

    /// <summary> Remove all designated characters from both ends of the string.</summary>
    /// <returns> Reference to this AcString.</returns>
    /// <remarks> Trims whitespace if pwszChars arg is null.</remarks>
    ///
    ACBASE_PORT AcString & trim(const wchar_t *pwszChars);

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
    ACBASE_PORT AcString spanExcluding(const wchar_t *pwszChars) const;

#if  defined(_AFX) || defined (__OSX_WINAPI_UNIX_STRING_H__) || defined(__ATLSTR_H__)
    //
    // MFC CString-using methods.  The CStringA class is the ansi
    // code page based CString, while CStringW is Unicode based.
    // CString maps to one or the other depending on whether the
    // UNICODE preprocessor symbol is defined.
    //

    // Construct an AcString from a CStringW
    // csw : input reference to the CStringW
    AcString(const CStringW &csw);

    // Initialize this AcString from a CStringW
    // csw : input reference to the CStringW
    AcString & operator = (const CStringW &csw);

    // Append a CStringW to this AcString
    // csa : input reference to the CStringW
    AcString & operator += (const CStringW &csw);

    // Compare this string to a CStringW
    // csw : input reference to the CStringW
    int  compare(const CStringW & csw) const;

    // Compare this string case independently to a CStringW
    // csw : input reference to the CStringW
    int  compareNoCase(const CStringW & csw) const;

    // Compare for equality with a CStringW
    // csw : input reference to the CStringW
    bool operator == (const CStringW & ) const;

    // Compare for non-equality with a CStringW
    // csw : input reference to the CStringW
    bool operator != (const CStringW & ) const;

    // Compare for less than a CStringW
    // csw : input reference to the CStringW
    bool operator <  (const CStringW & ) const;

    // Compare for less than or equal to a CStringW
    // csw : input reference to the CStringW
    bool operator <= (const CStringW & ) const;

    // Compare for greater than a CStringW
    // csw : input reference to the CStringW
    bool operator >  (const CStringW & ) const;
    // Compare for greater than or equal to a CStringW
    // csw : input reference to the CStringW
    bool operator >= (const CStringW & ) const;

    // Return number of chars matching a CStringW
    // csw : input reference to the CStringW
    int  match(const CStringW & csw) const;

    // Return number of chars case-independently matching a CStringW
    // csw : input reference to the CStringW
    int  matchNoCase(const CStringW & csw) const;

#endif

    /// <description>
    /// Rplaces instances of the substring with instances of the new string 
    /// </description>
    /// <param name="pwszOld"> A pointer to a string containing the character to be replaced by lpszNew. </param>
    /// <param name="pwszNew"> A pointer to a string containing the character replacing lpszOld. </param>
    /// <returns>
    /// Return the number of replaced instances of the substring. Zero if the string is not changed.
    /// </returns>
    ACBASE_PORT  int replace(const wchar_t* pwszOld, const wchar_t* pwszNew);

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
    ACBASE_PORT bool   releaseBuffer(int nNewLength = -1);

private:

    friend class AcStringImp;
    wchar_t *m_wsz;
};


#ifdef AC_ACARRAY_H
typedef
AcArray< AcString, AcArrayObjectCopyReallocator< AcString > > AcStringArray;
#endif

//
// Global operators
//

// Compare an AcString and a Unicode char for equality
// wch : input char to compare
// acs : input reference to the AcString
bool operator == (wchar_t wch, const AcString & acs);

// Compare an AcString and a string of Unicode chars for equality
// pwsz : input char to the string of Unicode chars
// acs : input reference to the AcString
bool operator == (const wchar_t *pwsz, const AcString & acs);

// Compare an AcString and a Unicode char for non-equality
// wch : input char to compare
// acs : input reference to the AcString
bool operator != (wchar_t wch, const AcString & acs);

// Compare an AcString and a string of Unicode chars for non-equality
// pwsz : input char to the string of Unicode chars
// acs : input reference to the AcString
bool operator != (const wchar_t *pwsz, const AcString & acs);

// Return whether a Unicode char is greater than an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator >  (wchar_t wch, const AcString & acs);

// Return whether a string of Unicode chars is greater than an AcString
// pwsz : input pointer to the string of Unicode chars
// acs : input reference to the AcString
bool operator >  (const wchar_t *pwsz, const AcString & acs);

// Check for a Unicode char being greater than or equal to an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator >= (wchar_t wch, const AcString & acs);

// Check for a string of Unicode chars being greater than/equal to an AcString
// pwsz : input char to compare
// acs : input reference to the AcString
bool operator >= (const wchar_t *pwsz, const AcString & acs);

// Check for a Unicode char being less than an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator <  (wchar_t wch, const AcString & acs);

// Check for a string of Unicode chars being less than an AcString
// pwsz : input char to compare
// acs : input reference to the AcString
bool operator <  (const wchar_t *pwsz, const AcString & acs);

// Check for a Unicode char being less than or equal to an AcString
// wch : input char to compare
// acs : input reference to the AcString
bool operator <= (wchar_t wch, const AcString & acs);


// Check for a string of Unicode chars being less than/equal to an AcString
// pwsz : input char to compare
// acs : input reference to the AcString
bool operator <= (const wchar_t *pwsz, const AcString & acs);

// Copy an AcString and insert a Unicode char in front of it
// wch : input char to insert
AcString operator + (wchar_t wch, const AcString & acs);

// Copy an AcString and insert a string of Unicode chars in front of it
// pwsz : input pointer to the string of chars to insert
AcString operator + (const wchar_t *pwsz, const AcString & acs);

// Accessing inlines
//

inline AcString::operator const wchar_t *() const
{
    return this->kwszPtr();
}

inline const wchar_t * AcString::constPtr() const
{
    return this->kwszPtr();
}

inline const wchar_t * AcString::kTCharPtr() const
{
    return this->kwszPtr();
}

inline const ACHAR * AcString::kACharPtr() const
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

// Searching inlines
//
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

// Extraction inlines
//
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

inline AcString & AcString::trimLeft(wchar_t wch)
{
    const wchar_t wszChars[] = { wch, L'\0' };
    return this->trimLeft(wszChars);
}

inline AcString & AcString::trimLeft()
{
    return this->trimLeft(nullptr);     // trim whitespace
}

inline AcString & AcString::trimRight(wchar_t wch)
{
    const wchar_t wszChars[] = { wch, L'\0' };
    return this->trimRight(wszChars);
}

inline AcString & AcString::trimRight()
{
    return this->trimRight(nullptr);    // trim whitespace
}

inline AcString & AcString::trim(wchar_t wch)
{
    const wchar_t wszChars[] = { wch, L'\0' };
    return this->trim(wszChars);
}

inline AcString & AcString::trim()
{
    return this->trim(nullptr);         // trim whitespace
}

inline AcString & AcString::trim(const wchar_t *pwszChars)
{
    return this->trimRight(pwszChars).trimLeft(pwszChars);
}

// Assignment inlines
//

inline AcString & AcString::assign(wchar_t wch)
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->assign(wstr);
}


inline AcString & AcString::operator = (wchar_t wch)
{
    return this->assign(wch);
}

inline AcString & AcString::operator = (const wchar_t *pwsz)
{
    return this->assign(pwsz);
}

inline AcString & AcString::operator = (const AcString & acs)
{
    return this->assign(acs);
}

inline AcString & AcString::operator = (const AcDbHandle & h)
{
    return this->assign(h);
}

// Modifying inlines
//
inline AcString & AcString::operator += (wchar_t wch)
{
    return this->append(wch);
}

inline AcString & AcString::operator += (const wchar_t *pwsz)
{
    return this->append(pwsz);
}

inline AcString & AcString::operator += (const AcString & acs)
{
    return this->append(acs);
}

inline AcString & AcString::append(wchar_t wch)
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->append(wstr);
}

// Concatenation inlines
inline AcString AcString::operator + (wchar_t wch) const
{
    return this->concat(wch);
}

inline AcString AcString::operator + (const wchar_t * pwsz) const
{
    return this->concat(pwsz);
}

inline AcString AcString::operator + (const AcString & acs) const
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

// Comparison inlines
//

inline const wchar_t * AcString::kwszPtr() const
{
    return this->m_wsz; // this pointer is never null
}

inline int AcString::compare(wchar_t wch) const
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->compare(wstr);
}

inline int AcString::compare(const AcString & acs) const
{
    return this->compare(acs.kwszPtr());
}

inline int AcString::compareNoCase(wchar_t wch) const
{
    const wchar_t wstr[2] = {wch, L'\0'};
    return this->compareNoCase(wstr);
}

inline int AcString::compareNoCase(const AcString & acs) const
{
    return this->compareNoCase(acs.kwszPtr());
}

inline int AcString::collate(const AcString & acs) const
{
    return this->collate(acs.kwszPtr());
}

inline int AcString::collateNoCase(const AcString & acs) const
{
    return this->collateNoCase(acs.kwszPtr());
}

inline bool AcString::operator == (wchar_t wch) const
{
    return this->compare(wch) == 0;
}

inline bool AcString::operator == (const wchar_t *pwsz) const
{
    return this->compare(pwsz) == 0;
}

inline bool AcString::operator == (const AcString & acs) const
{
    return this->compare(acs) == 0;
}

inline bool AcString::operator != (wchar_t wch) const
{
    return this->compare(wch) != 0;
}

inline bool AcString::operator != (const wchar_t *pwsz) const
{
    return this->compare(pwsz) != 0;
}

inline bool AcString::operator != (const AcString & acs) const
{
    return this->compare(acs) != 0;
}

inline bool AcString::operator > (wchar_t wch) const
{
    return this->compare(wch) > 0;
}

inline bool AcString::operator > (const wchar_t *pwsz) const
{
    return this->compare(pwsz) > 0;
}

inline bool AcString::operator > (const AcString & acs) const
{
    return this->compare(acs) > 0;
}

inline bool AcString::operator >= (wchar_t wch) const
{
    return this->compare(wch) >= 0;
}

inline bool AcString::operator >= (const wchar_t *pwsz) const
{
    return this->compare(pwsz) >= 0;
}

inline bool AcString::operator >= (const AcString & acs) const
{
    return this->compare(acs) >= 0;
}

inline bool AcString::operator < (wchar_t wch) const
{
    return this->compare(wch) < 0;
}

inline bool AcString::operator < (const wchar_t *pwsz) const
{
    return this->compare(pwsz) < 0;
}

inline bool AcString::operator < (const AcString & acs) const
{
    return this->compare(acs) < 0;
}

inline bool AcString::operator <= (wchar_t wch) const
{
    return this->compare(wch) <= 0;
}

inline bool AcString::operator <= (const wchar_t *pwsz) const
{
    return this->compare(pwsz) <= 0;
}

inline bool AcString::operator <= (const AcString & acs) const
{
    return this->compare(acs) <= 0;
}

// Inline global operators

inline bool operator == (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) == 0;
}

inline bool operator == (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) == 0;
}

inline bool operator != (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) != 0;
}

inline bool operator != (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) != 0;
}

inline bool operator > (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) < 0;
}

inline bool operator > (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) < 0;
}

inline bool operator >= (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) <= 0;
}

inline bool operator >= (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) <= 0;
}

inline bool operator < (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) > 0;
}

inline bool operator < (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) > 0;
}

inline bool operator <= (wchar_t wch, const AcString & acs)
{
    return acs.compare(wch) >= 0;
}

inline bool operator <= (const wchar_t *pwsz, const AcString & acs)
{
    return acs.compare(pwsz) >= 0;
}

// These don't modify the AcString.  They return a copy.
inline AcString operator + (ACHAR ch, const AcString & acs)
{
    return acs.precat(ch);
}

inline AcString operator + (const wchar_t *pwsz, const AcString & acs)
{
    return acs.precat(pwsz);
}

inline bool AcString::equalsNoCase(const AcString& left, const AcString& right)
{
    return left.compareNoCase(right) == 0;
}

// Return a unique identifier (pointer) for the input string, to allow fast compares
// using pointer values instead of strings.
// Input strings are converted to lowercase, then are looked up in and stored in an
// internal map. So "ABC" and "abc" return the same AcUniqueString pointer.
// AcUniqueString pointers are valid for the process's lifetime
//
class AcUniqueString
{
public:
    ACBASE_PORT static const AcUniqueString *Intern(const wchar_t *);
};


// We can do inline operators that deal with CStrings, without getting
// into binary format dependencies.  Don't make these out-of-line
// functions, because then we'll have a dependency between our
// components and CString-using clients.
//
#if defined(_AFX) || defined(__OSX_WINAPI_UNIX_STRING_H__) || defined(__ATLSTR_H__)


inline AcString::AcString(const CStringW &csw) : AcString()
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    *this = pwsz;
}

inline AcString & AcString::operator=(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->assign(pwsz);
}

inline AcString & AcString::operator+=(const CStringW &csw)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->append(pwsz);
}

inline int AcString::compare(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->compare(pwsz);
}

inline int AcString::compareNoCase(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->compareNoCase(pwsz);
}

inline int AcString::match(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->match(pwsz);
}

inline int AcString::matchNoCase(const CStringW & csw) const
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return this->matchNoCase(pwsz);
}

inline bool AcString::operator == (const CStringW & csw) const
{
    return this->compare(csw) == 0;
}

inline bool AcString::operator != (const CStringW & csw) const
{
    return this->compare(csw) != 0;
}

inline bool AcString::operator > (const CStringW & csw) const
{
    return this->compare(csw) > 0;
}

inline bool AcString::operator >= (const CStringW & csw) const
{
    return this->compare(csw) >= 0;
}

inline bool AcString::operator < (const CStringW & csw) const
{
    return this->compare(csw) < 0;
}

inline bool AcString::operator <= (const CStringW & csw) const
{
    return this->compare(csw) <= 0;
}

#if defined(_AFX) && !defined(__cplusplus_cli)
// Global CString-related operators
inline bool operator == (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) == 0;
}

inline bool operator != (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) != 0;
}

inline bool operator >  (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) < 0;
}

inline bool operator >= (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) <= 0;
}

inline bool operator <  (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) > 0;
}

inline bool operator <= (const CStringW & csw, const AcString & acs)
{
    return acs.compare(csw) >= 0;
}

#ifndef DISABLE_CSTRING_PLUS_ACSTRING
inline AcString operator + (const CStringW & csw, const AcString & acs)
{
    const wchar_t *pwsz = (const wchar_t *)csw;
    return acs.precat(pwsz);
}
#endif

#endif

#endif // _AFX

#endif // !_Ac_String_h

