//
/////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
//
//  truetypetext.h - General-purpose TrueType functions
//
//  DESCRIPTION:
//
//  This header file contains declarations of general-purpose truetype text
//  functions provided with the AcUtil library and DLL.
//
#ifndef _TRUETYPETEXT_H_
#  define _TRUETYPETEXT_H_
#  define UC_DEGREE_SYMBOL	0x00B0
#  define UC_PLUSMINUS_SYMBOL	0x00B1
#  define UC_PHI_SYMBOL	0x00D8  // The Character 'phi' (substitute for diameter)
#  define UC_DIAMETER_SYMBOL	0x2205  // Most fonts do not have this.
typedef void (*LineSegmentCallback) (const AcGePoint3d&, const AcGePoint3d&, const void*);
struct TextParams
{
  double height;
  double width_scale;
  double oblique_angle;
  double rotation_angle;
  double spacing;
  short flags;
};
class Scores
{
private:
  int m_overline;
  int m_underline;
  int m_strikethrough;
  AcGePoint3d m_position;
  AcGePoint3d m_over_point[2];
  AcGePoint3d m_under_point[2];
  AcGePoint3d m_strikethrough_point[2];
  AcGePoint3d m_bbox[4];
  const TextParams* m_pTextParams;
  LineSegmentCallback m_pLineSegmentCB;
  void* m_pAction;
  AcGiContext* m_pContext;
#  define ON	1
#  define OFF	0
public:
  Scores(AcGiContext* pContext, const TextParams* pTextParams, LineSegmentCallback pLineSegment, void* pAction);
  ~Scores()
  {
  }
  void over_score(const wchar_t* text, int length);
  void under_score(const wchar_t* text, int length);
  void strikethrough_score(const wchar_t* text, int length);
  void close_scores(const wchar_t* text, int length);
  void draw_vector(const AcGePoint3d& p1, const AcGePoint3d& p2);
};
void process_uc_string(wchar_t* uc_string, int& uc_length, const TextParams* tp, int draw_scores, LineSegmentCallback line_segment = NULL, void* action = NULL);
void process_underoverline(const wchar_t* uc_string, int uc_length, const TextParams* tp, LineSegmentCallback line_segment, void* action = NULL);
class TrueTypeUnicodeBuffer
{
public:
  TrueTypeUnicodeBuffer(const wchar_t* text, int length, bool raw, Charset charset)
    : m_bDynamicBuffer(false)
    , m_bValid(true)
  {
    ADESK_UNREFED_PARAM(charset);
    if (length < -1)
    {
      m_iLen = -length - 1;
      m_pBuffer = (wchar_t*) text;
      return ;
    }
    if (length != -1)
    {
      m_iLen = length;
    }
    else 
    {
      const size_t nLen = ::wcslen(text);
#  ifdef ASSERT
#    define TrueTypeText_Assert	ASSERT
#  elif  defined(assert)
#    define TrueTypeText_Assert	assert
#  elif  defined(_ASSERTE)
#    define TrueTypeText_Assert	_ASSERTE
#  else 
#    define TrueTypeText_Assert(x)
#  endif
      TrueTypeText_Assert(nLen < 0x7FFFFFFE);
      TrueTypeText_Assert(nLen == (int) nLen);
      m_iLen = (int) nLen;
    }
    if (!raw)
    {
            // only need temporary string if converting %% sequences
      size_t nSize;
      if (m_iLen + 1 > m_kBufferLen)
      {
        m_bDynamicBuffer = true;
        m_pBuffer = new wchar_t[m_iLen + 1];
        nSize = m_iLen + 1;
        if (!m_pBuffer)
        {
          m_bValid = false;
          return ;
        }
      }
      else 
      {
        m_pBuffer = m_sBuffer;
        nSize = m_kBufferLen;
      }
      wcsncpy_s(m_pBuffer, nSize, text, m_iLen);
      m_pBuffer[m_iLen] = 0;
    }
    else 
    {
            // It is okay to cast away constness here -- we only call process_underoverline
            // which takes a const pointer
      m_pBuffer = const_cast<wchar_t*>(text);
    }
  }
  ~TrueTypeUnicodeBuffer()
  {
    if (m_bDynamicBuffer)
    {
      delete[] m_pBuffer;
    }
  }
  wchar_t* buf() const
  {
    return m_pBuffer;
  }
  int len() const
  {
    return m_iLen;
  }
  bool valid() const
  {
    return m_bValid;
  }
private:
  static const int m_kBufferLen = 256;
  bool m_bValid;
  wchar_t* m_pBuffer;
  int m_iLen;
  bool m_bDynamicBuffer;
  wchar_t m_sBuffer[m_kBufferLen];
};
#endif
