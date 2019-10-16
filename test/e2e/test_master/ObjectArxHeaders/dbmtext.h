//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_DBMTEXT_H
#  define AD_DBMTEXT_H
#  include "dbmain.h"
#  pragma  pack(push, 8)
struct AcDbMTextFragment
{
  AcGePoint3d location;
  AcGeVector3d normal;
  AcGeVector3d direction;
  AcString msText;
  const ACHAR* text = nullptr;
  AcString msFont;
  const ACHAR* font = nullptr;
  AcString msBigFont;
  const ACHAR* bigfont = nullptr;
  AcGePoint2d extents;
  double capsHeight = 0.0;
  double widthFactor = 0.0;
  double obliqueAngle = 0.0;
  double trackingFactor = 0.0;
  AcCmEntityColor color;
  unsigned stackTop;
  unsigned stackBottom;
  unsigned underlined;
  unsigned overlined;
  unsigned strikethrough;
  AcGePoint3d underPoints[2] = {};
  AcGePoint3d overPoints[2] = {};
  AcGePoint3d strikePoints[2] = {};
  AcString msFontName;
  const ACHAR* fontname = nullptr;
  bool bold = false;
  bool italic = false;
};
typedef int (*AcDbMTextEnum) (AcDbMTextFragment*, void*);
class AcDbText;
class AcDbMText : public AcDbEntity
{
  ACDB_DECLARE_MEMBERS(AcDbMText);
public:
  AcDbMText();
  ~AcDbMText();
  AcGePoint3d location() const;
  Acad::ErrorStatus setLocation(const AcGePoint3d&);
  AcGeVector3d normal() const;
  Acad::ErrorStatus setNormal(const AcGeVector3d&);
  virtual Adesk::Boolean isPlanar() const override
  {
    return Adesk::kTrue;
  }
  ACDBCORE2D_PORT Acad::ErrorStatus getPlane(AcGePlane& plane, AcDb::Planarity& type) const override;
  AcGeVector3d direction() const;
  Acad::ErrorStatus setDirection(const AcGeVector3d&);
  double rotation() const;
  Acad::ErrorStatus setRotation(double);
  double width() const;
  Acad::ErrorStatus setWidth(double);
  double ascent() const;
  double descent() const;
  AcDbObjectId textStyle() const;
  Acad::ErrorStatus setTextStyle(AcDbObjectId);
  double textHeight() const;
  Acad::ErrorStatus setTextHeight(double);
  enum AttachmentPoint
  {
    kTopLeft = 1,
    kTopCenter = 2,
    kTopRight = 3,
    kMiddleLeft = 4,
    kMiddleCenter = 5,
    kMiddleRight = 6,
    kBottomLeft = 7,
    kBottomCenter = 8,
    kBottomRight = 9,
    kBaseLeft = 10,
    kBaseCenter = 11,
    kBaseRight = 12,
    kBaseAlign = 13,
    kBottomAlign = 14,
    kMiddleAlign = 15,
    kTopAlign = 16,
    kBaseFit = 17,
    kBottomFit = 18,
    kMiddleFit = 19,
    kTopFit = 20,
    kBaseMid = 21,
    kBottomMid = 22,
    kMiddleMid = 23,
    kTopMid = 24
  };
  AttachmentPoint attachment() const;
  Acad::ErrorStatus setAttachment(AttachmentPoint);
  Acad::ErrorStatus setAttachmentMovingLocation(AttachmentPoint);
  enum FlowDirection
  {
    kLtoR = 1,
    kRtoL = 2,
    kTtoB = 3,
    kBtoT = 4,
    kByStyle = 5
  };
  FlowDirection flowDirection() const;
  Acad::ErrorStatus setFlowDirection(FlowDirection);
  ACDBCORE2D_PORT Acad::ErrorStatus contents(AcString& sContents) const;
  ACHAR* contents() const;
  int setContents(const ACHAR*);
    /// <summary> This method returns an RTF encoded string that is a
    /// translated version of the contents of the AcDbMText object. MText
    /// codes are translated to RTF codes. Fonts, colors, tabs, and indents
    /// are preserved.
    /// The conversion uses 24 as the default point size. That is, text with
    /// no height override will have a point size of 24 and text with a height
    /// override will have a point size of the height override multiplied by 24.
    /// The caller is responsible for freeing the memory used by the
    /// returned string (preferrably by using acutDelString()).
    /// </summary>
  ACDBCORE2D_PORT Acad::ErrorStatus contentsRTF(AcString& sContentsRTF) const;
  ACHAR* contentsRTF() const;
    /// <summary> This method sets the contents of the AcDbMText object from
    /// the RTF-encoded text string pointed to by RTFString. RTF codes are
    /// translated to MText codes. Fonts, colors, tabs, and indents are
    /// preserved. Bullets and numbered lists are mapped to hanging paragraphs
    /// using the implied setting for tabs and indents.
    /// The conversion uses 24 as the default point size. That is, 24 point
    /// text (RTF \fs48) will have no height override and text with any other
    /// point size will have a height override of that point size divided by 24.
    /// </summary>
    /// <param name="RTFString">Input RTF-encoded string.</param>
    /// <returns>Returns 0 if successful.</returns>
  int setContentsRTF(const ACHAR* RTFString);
  ACDBCORE2D_PORT Acad::ErrorStatus text(AcString& sText) const;
  ACHAR* text() const;
  double actualHeight(AcGiWorldDraw* ctxt = NULL) const;
  double actualWidth() const;
  int correctSpelling();
  void getBoundingPoints(AcGePoint3dArray&) const;
  void explodeFragments(AcDbMTextEnum, void*, AcGiWorldDraw* ctxt = NULL) const;
  static const ACHAR* const nonBreakSpace();
  static const ACHAR* const overlineOn();
  static const ACHAR* const overlineOff();
  static const ACHAR* const underlineOn();
  static const ACHAR* const underlineOff();
  static const ACHAR* const colorChange();
  static const ACHAR* const fontChange();
  static const ACHAR* const heightChange();
  static const ACHAR* const widthChange();
  static const ACHAR* const obliqueChange();
  static const ACHAR* const trackChange();
  static const ACHAR* const lineBreak();
  static const ACHAR* const paragraphBreak();
  static const ACHAR* const stackStart();
  static const ACHAR* const alignChange();
  static const ACHAR* const blockBegin();
  static const ACHAR* const blockEnd();
  static const ACHAR* const strikethroughOn();
  static const ACHAR* const strikethroughOff();
  Acad::ErrorStatus setLineSpacingStyle(AcDb::LineSpacingStyle eStyle);
  AcDb::LineSpacingStyle lineSpacingStyle() const;
  Acad::ErrorStatus setLineSpacingFactor(double dFactor);
  double lineSpacingFactor() const;
  void getEcs(AcGeMatrix3d& retVal) const override;
    /// <summary> Get the flag controlling mtext border's visibility.
    /// <returns> bool </returns>
    /// </summary>
  ACDBCORE2D_PORT bool showBorders() const;
    /// <summary> Set the flag controlling mtext border's visibility.
    /// <param name = "enable"> true means borders will be visible
    ///                         false means borders will be invisible </param>
    /// <returns> Acad::ErrorStatus </returns>
    /// </summary>
  ACDBCORE2D_PORT Acad::ErrorStatus setShowBorders(bool enable);
  bool backgroundFillOn() const;
  Acad::ErrorStatus setBackgroundFill(bool enable);
  Acad::ErrorStatus getBackgroundFillColor(AcCmColor& color) const;
  Acad::ErrorStatus setBackgroundFillColor(const AcCmColor& color);
  Acad::ErrorStatus getBackgroundScaleFactor(double& scale) const;
  Acad::ErrorStatus setBackgroundScaleFactor(const double scale);
  Acad::ErrorStatus getBackgroundTransparency(AcCmTransparency& transp) const;
  Acad::ErrorStatus setBackgroundTransparency(const AcCmTransparency& transp);
  bool useBackgroundColorOn() const;
  Acad::ErrorStatus setUseBackgroundColor(bool enable);
  Acad::ErrorStatus setField(const ACHAR* pszPropName, AcDbField* pField, AcDbObjectId& fieldId) override;
  Acad::ErrorStatus removeField(AcDbObjectId fieldId) override;
  Acad::ErrorStatus removeField(const ACHAR* pszPropName, AcDbObjectId& returnId) override;
  Acad::ErrorStatus removeField(const ACHAR* pszPropName) override;
  Acad::ErrorStatus convertFieldToText();
  enum ColumnType
  {
    kNoColumns,
    kStaticColumns,
    kDynamicColumns
  };
  Acad::ErrorStatus setDynamicColumns(double width, double gutter, bool auto_height);
  Acad::ErrorStatus setStaticColumns(double width, double gutter, int count);
  Acad::ErrorStatus getColumnType(ColumnType&) const;
  Acad::ErrorStatus setColumnType(ColumnType);
  Acad::ErrorStatus getColumnAutoHeight(bool&) const;
  Acad::ErrorStatus setColumnAutoHeight(bool);
  Acad::ErrorStatus getColumnCount(int&) const;
  Acad::ErrorStatus setColumnCount(int);
  Acad::ErrorStatus getColumnWidth(double&) const;
  Acad::ErrorStatus setColumnWidth(double);
  Acad::ErrorStatus getColumnGutterWidth(double&) const;
  Acad::ErrorStatus setColumnGutterWidth(double);
  Acad::ErrorStatus getColumnFlowReversed(bool&) const;
  Acad::ErrorStatus setColumnFlowReversed(bool);
  Acad::ErrorStatus getColumnHeight(int, double&) const;
  Acad::ErrorStatus setColumnHeight(int, double);
  Acad::ErrorStatus setUseWordBreak(bool bEnable);
  bool useWordBreak() const;
  double height() const;
  Acad::ErrorStatus setHeight(double);
protected:
  virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};
inline ACHAR* AcDbMText::contents() const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbMText::contents);
}
inline ACHAR* AcDbMText::contentsRTF() const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbMText::contentsRTF);
}
inline ACHAR* AcDbMText::text() const
{
  return ::acutGetAcStringConvertToAChar(this, &AcDbMText::text);
}
#  pragma  pack(pop)
#endif
