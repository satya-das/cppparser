//
////////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// dbsymtb.h
//
// DESCRIPTION: Exported protocol for AutoCAD's built in symbol
//              tables, their table  specific record types, and
//              their iterators.

#ifndef AD_DBSYMTB_H
#define AD_DBSYMTB_H

#include "dbmain.h"
#include "dbdict.h"
#include "dbdate.h"
#include "dbbackground.h"
#include "gevec2d.h"
#include "acgiviewport.h"
#include "acgivisualstyle.h"
#include "acdbcore2ddefs.h"
#include "PAL/api/charset.h"
#include "PAL/api/FontPitchAndFamily.h"

#pragma pack(push, 8)

#ifdef target
# undef target 
#endif

class AcDbSortentsTable;
class AcDbSymbolTableIterator;
class AcDbSymbolTable;
class AcDbAnnotationScale;
class AcGsView;
class AcString;

namespace Atil 
{
    class Image; // for Atil::Image
}

class ADESK_NO_VTABLE AcDbSymbolTableRecord: public  AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbSymbolTableRecord);
    AcDbSymbolTableRecord();
    virtual ~AcDbSymbolTableRecord();

    typedef AcDbSymbolTable TableType;

    Acad::ErrorStatus getName(ACHAR*& pName) const;     // deprecated
    Acad::ErrorStatus getName(AcString & sName) const;
    Acad::ErrorStatus getName(const ACHAR*& pName) const;
    Acad::ErrorStatus setName(const ACHAR* pName);

    bool isDependent() const;

    bool isResolved() const;

    bool isRenamable() const;
};

class AcDbBlockTable;
class AcDbBlockTableIterator;
class AcDbBlockTableRecordIterator;
class AcDbBlockReferenceIdIterator;

class AcDbBlockTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBlockTableRecord);

    AcDbBlockTableRecord();
    virtual ~AcDbBlockTableRecord();

    typedef AcDbBlockTable TableType;
    typedef AcArray<Adesk::UInt8> PreviewIcon;

    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;

    Acad::ErrorStatus appendAcDbEntity(AcDbEntity* pEntity)
    {
        AcDbObjectId id;
        return this->appendAcDbEntity(id, pEntity);
    }

    // Note: does not close the entity. Caller must close it
    // after entity is successfully appended.
    Acad::ErrorStatus appendAcDbEntity(AcDbObjectId& pOutputId,
        AcDbEntity* pEntity);

    Acad::ErrorStatus newIterator(
        AcDbBlockTableRecordIterator*& pIterator,
        bool atBeginning = true,
        bool skipDeleted = true) const;

    Acad::ErrorStatus comments(ACHAR*& pString) const;  // deprecated
    Acad::ErrorStatus comments(const ACHAR*& pString) const;
    ACDBCORE2D_PORT Acad::ErrorStatus comments(AcString & sComments) const;
    Acad::ErrorStatus setComments(const ACHAR* pString);

    Acad::ErrorStatus pathName(ACHAR*& pPath) const;    // deprecated
    Acad::ErrorStatus pathName(const ACHAR*& pPath) const;
    ACDBCORE2D_PORT Acad::ErrorStatus pathName(AcString & sPath) const;
    Acad::ErrorStatus setPathName(const ACHAR* pathStr);
 
    AcGePoint3d       origin() const;
    Acad::ErrorStatus setOrigin(const AcGePoint3d& pt);

    Acad::ErrorStatus openBlockBegin(AcDbBlockBegin*& pBlockBegin,
                                     AcDb::OpenMode   openMode = AcDb::kForRead);
 
    Acad::ErrorStatus openBlockEnd(AcDbBlockEnd*& pBlockEnd,
                                   AcDb::OpenMode openMode = AcDb::kForRead);

    bool              hasAttributeDefinitions() const;

    bool              hasPreviewIcon() const;
    Acad::ErrorStatus getPreviewIcon(PreviewIcon &previewIcon) const;
    Acad::ErrorStatus setPreviewIcon(const PreviewIcon &previewIcon);

    bool              isAnonymous() const;

    bool              isFromExternalReference() const;

    bool              isFromOverlayReference() const;
    Acad::ErrorStatus setIsFromOverlayReference(bool bIsOverlay);

    bool              isLayout() const;

    AcDbObjectId      getLayoutId() const;
    Acad::ErrorStatus setLayoutId(AcDbObjectId);


    Acad::ErrorStatus newBlockReferenceIdIterator(
        AcDbBlockReferenceIdIterator*& pIter) const;

    // AcDbBlockReferenceIdIterator will be going away. 
    // Use getBlockReferenceIds() instead.
    //
    Acad::ErrorStatus getBlockReferenceIds(AcDbObjectIdArray& ids,
                                           bool bDirectOnly = true,
                                           bool bForceValidity = false) const; 

    Acad::ErrorStatus getErasedBlockReferenceIds(AcDbObjectIdArray&);

    // getSortentsTable 
    //
    // Returns the sortents table opened as requested, sparing the caller
    // the work of getting the extension dictionary and looking the sortents
    // table up in it.
    // If the dictionary is successfully opened and returned, it is the
    // caller's responsibility to close it.
    //
    // ErrorStatus returns errors if the sortents dictionary cannot be opened,
    //             doesn't exist, and createIfNecessary
    //             is false, or if createIfNecessary is true, but
    //             the BTR is not open for write, or if its
    //             extension dictionary could not be created or
    //             opened.
    //                            
    Acad::ErrorStatus
    getSortentsTable(AcDbSortentsTable*& pSortents,
                     AcDb::OpenMode openMode = AcDb::kForRead,
                     bool createIfNecessary=false);

    AcDbDatabase*     xrefDatabase(bool incUnres = false) const;

    bool              isUnloaded() const;
    Acad::ErrorStatus setIsUnloaded(bool isUnloaded);

    AcDb::XrefStatus  xrefStatus() const;

    // Drawable API
    //
    AcGiDrawable*     drawable() override;

    virtual Acad::ErrorStatus decomposeForSave(AcDb::AcDbDwgVersion ver,
                                               AcDbObject*& replaceObj,
                                               AcDbObjectId& replaceId,
                                               Adesk::Boolean& exchangeXData) override;

    virtual Acad::ErrorStatus assumeOwnershipOf(const AcDbObjectIdArray &entitiesToMove);

    // Block scaling and exploding control

    enum BlockScaling {
        kAny,
        kUniform
    };


    AcDbBlockTableRecord::BlockScaling blockScaling () const;
    Acad::ErrorStatus  setBlockScaling (
                        AcDbBlockTableRecord::BlockScaling blockScaling);

    Acad::ErrorStatus setExplodable (bool bExplodable);
    bool              explodable () const;

    Acad::ErrorStatus setBlockInsertUnits(AcDb::UnitsValue insunits);
    AcDb::UnitsValue blockInsertUnits() const;

    Acad::ErrorStatus postProcessAnnotativeBTR(int& stripCnt,
                                               bool bqueryOnly = false, bool bScale = true);
    Acad::ErrorStatus addAnnoScalestoBlkRefs(bool bScale = false);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbLayerTable;

class AcDbLayerTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayerTableRecord);

    AcDbLayerTableRecord();
    virtual ~AcDbLayerTableRecord();

    typedef AcDbLayerTable TableType;

    bool              isFrozen() const;
    Acad::ErrorStatus setIsFrozen(bool frozen);

    bool              isOff() const;
    void              setIsOff(bool off);

    bool              VPDFLT() const;
    void              setVPDFLT(bool frozen);

    bool              isLocked() const;
    void              setIsLocked(bool locked);

    AcCmColor         color() const;
    void              setColor(const AcCmColor &color);
    AcCmEntityColor   entityColor(void) const;

    AcCmTransparency  transparency(void) const;
    Acad::ErrorStatus setTransparency(const AcCmTransparency& trans);

    AcDbObjectId      linetypeObjectId() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setLinetypeObjectId(AcDbObjectId id);

    AcDbObjectId      materialId() const;
    Acad::ErrorStatus setMaterialId(AcDbObjectId id);

    enum { kDxfLayerPlotBit = AcDb::kDxfBool };
    bool              isPlottable() const;
    Acad::ErrorStatus setIsPlottable(bool plot);

    AcDb::LineWeight  lineWeight() const;
    Acad::ErrorStatus setLineWeight(AcDb::LineWeight weight);

    ACHAR*            plotStyleName() const;    // deprecated
    ACDBCORE2D_PORT Acad::ErrorStatus plotStyleName(AcString &) const;
    AcDbObjectId      plotStyleNameId() const;
    Acad::ErrorStatus setPlotStyleName(const ACHAR* newName);
    Acad::ErrorStatus setPlotStyleName(const AcDbObjectId& newId);

    // Drawable API
    //
    AcGiDrawable*     drawable() override;

    bool              isInUse() const;
    ACHAR*            description() const;      // deprecated
    ACDBCORE2D_PORT Acad::ErrorStatus description(AcString &) const;
    Acad::ErrorStatus setDescription(const ACHAR* description);

    bool              isHidden() const;
    Acad::ErrorStatus setIsHidden(bool on);
    static bool isHidden(AcDbObjectId);

    // Property override API
    //
    AcCmColor         color(const AcDbObjectId& viewportId, bool& isOverride) const;
    Acad::ErrorStatus setColor(const AcCmColor& color, 
                               const AcDbObjectId& viewportId);

    AcDbObjectId      linetypeObjectId(const AcDbObjectId& viewportId, bool& isOverride) const;
    Acad::ErrorStatus setLinetypeObjectId(const AcDbObjectId& id, 
                                          const AcDbObjectId& viewportId);

    AcDb::LineWeight  lineWeight(const AcDbObjectId& viewportId, bool& isOverride) const;
    Acad::ErrorStatus setLineWeight(AcDb::LineWeight weight, 
                                    const AcDbObjectId& viewportId);

    ACDBCORE2D_PORT   Acad::ErrorStatus plotStyleName(const AcDbObjectId& viewportId,
                                AcString &sName, bool& isOverride) const;
    // The overload returning an ACHAR buffer is deprecated
    ACHAR*            plotStyleName(const AcDbObjectId& viewportId, bool& isOverride) const;
    AcDbObjectId      plotStyleNameId(const AcDbObjectId& viewportId, bool& isOverride) const;
    Acad::ErrorStatus setPlotStyleName(const ACHAR* newName, 
                                       const AcDbObjectId& viewportId);
    Acad::ErrorStatus setPlotStyleName(const AcDbObjectId& newId, 
                                       const AcDbObjectId& viewportId);

    AcCmTransparency  transparency(const AcDbObjectId& viewportId, bool& isOvr) const;
    Acad::ErrorStatus setTransparency(const AcCmTransparency& trans, 
                               const AcDbObjectId& viewportId);
                                                                                                 
    Acad::ErrorStatus removeColorOverride(const AcDbObjectId& viewportId);
    Acad::ErrorStatus removeLinetypeOverride(const AcDbObjectId& viewportId);
    Acad::ErrorStatus removeLineWeightOverride(const AcDbObjectId& viewportId);
    Acad::ErrorStatus removePlotStyleOverride(const AcDbObjectId& viewportId);
    Acad::ErrorStatus removeTransparencyOverride(const AcDbObjectId& viewportId);
    Acad::ErrorStatus removeViewportOverrides(const AcDbObjectId& viewportId);
    Acad::ErrorStatus removeAllOverrides();

    bool              hasOverrides(const AcDbObjectId& viewportId) const;
    bool              hasAnyOverrides() const;

    bool              isReconciled() const;
    Acad::ErrorStatus setIsReconciled(bool bReconcile = true);
    static bool       isReconciled(const AcDbObjectId& id);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

// Utility for changing Layer Table Records in the Current Drawing
Acad::ErrorStatus applyCurDwgLayerTableChanges();

// AcDbTextStyleTableRecord:

class AcDbTextStyleTable;

class AcDbTextStyleTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTextStyleTableRecord);

    AcDbTextStyleTableRecord();
    virtual ~AcDbTextStyleTableRecord();

    typedef AcDbTextStyleTable TableType;

    Adesk::Boolean isShapeFile() const;
    void setIsShapeFile(Adesk::Boolean shape);

    Adesk::Boolean isVertical() const;
    void setIsVertical(Adesk::Boolean vertical);

    double textSize() const;
    Acad::ErrorStatus setTextSize(double size);

    double xScale() const;
    Acad::ErrorStatus setXScale(double xScale);

    double obliquingAngle() const;
    Acad::ErrorStatus setObliquingAngle(double obliquingAngle);

    Adesk::UInt8 flagBits() const;
    void setFlagBits(Adesk::UInt8 flagBits);

    double priorSize() const;
    Acad::ErrorStatus setPriorSize(double priorSize);

    ACDBCORE2D_PORT Acad::ErrorStatus fileName(AcString & sFileName) const;
    Acad::ErrorStatus fileName(ACHAR*& fileName) const; // deprecated
    Acad::ErrorStatus fileName(const ACHAR*& fileName) const;
    Acad::ErrorStatus setFileName(const ACHAR* fileName);

    ACDBCORE2D_PORT Acad::ErrorStatus bigFontFileName(AcString & sFileName) const;
    Acad::ErrorStatus bigFontFileName(ACHAR*& fileName) const;  // deprecated
    Acad::ErrorStatus bigFontFileName(const ACHAR*& fileName) const;
    Acad::ErrorStatus setBigFontFileName(const ACHAR* fileName);

    /// <summary>
    /// This method sets the TextStyleTableRecord to use the Windows font as specified by the passed in arguments. 
    /// If pTypeFace == NULL or points to an empty string, and the other arguments are Adesk::kFalse or 0 (as appropriate),
    /// then all existing Windows font information in this TextStyleTableRecord is removed from the record.
    /// WARNING: This method should not be used to set an old style SHX font. To set the TextStyleTableRecord to use
    /// an SHX font, you need to use the AcDbTextStyleTableRecord::setFileName() method. 
    /// </summary>
    /// <param name="pTypeface">Input pointer to the font file name string of the desired font</param>
    /// <param name="bold">Input Boolean indicating whether or not the font is to be bold</param>
    /// <param name="italic">Input Boolean indicating whether or not the font is to be italic</param>
    /// <param name="charset">Input integer that is the Windows character set identifier </param>
    /// <param name="pitch">Input indicating the pitch being used</param>
    /// <param name="family">Input indicating the family being used</param>
    /// <param name="bAllowMissingFont">Input bool indicating whether or not to allow the set to succeed if the font is not installed on the computer </param>
    /// <returns>Returns Acad::eOk if successful and Acad::eInvalidInput if bAllowMissingFont is false and the font
    /// is not installed on the system.</returns>
    ACDBCORE2D_PORT Acad::ErrorStatus setFont(const ACHAR* pTypeface, Adesk::Boolean bold, 
                                              Adesk::Boolean italic, Charset charset,
                                              Autodesk::AutoCAD::PAL::FontUtils::FontPitch pitch,
                                              Autodesk::AutoCAD::PAL::FontUtils::FontFamily family,
                                              bool bAllowMissingFont = false);

    /// <summary>
    /// This method returns the font definition data from the text style record. The returned values are the typeface,
    /// the bold and italics style attributes, the character set, and the pitch and family attributes. 
    ///
    /// This function allocates the memory for the typeface string and then sets pTypeface to point it.
    /// It is the caller's responsibility to free the memory that pTypeface is set to point to. 
    ///
    /// If the TextStyleTableRecord is not using a Windows font (that is, if it's using an SHX font),
    /// then pTypeface is NULL, bold and italic are Adesk::kFalse, and charset and pitchAndFamily are 0. 
    /// <summary>
    /// <param name="pTypeface">Input uninitialized pointer to char; output pointer to font file name string</param>
    /// <param name="bold">Output Boolean indicating whether or not the font is bold</param>
    /// <param name="italic">Output Boolean indicating whether or not the font is italic</param>
    /// <param name="charset">Output integer that is the Windows character set identifier</param>
    /// <param name="pitch">Output the pitch being used </param>
    /// <param name="family">Output the family being used </param>
    /// <returns>Returns Acad::eOk if successful. Returns Acad::eOutOfMemory if there is insufficient memory for pTypeFace.</returns>
    ACDBCORE2D_PORT Acad::ErrorStatus font   (AcString & sTypeface,
                                              bool & bold, 
                                              bool & italic,
                                              Charset& charset,
                                              Autodesk::AutoCAD::PAL::FontUtils::FontPitch& pitch,
                                              Autodesk::AutoCAD::PAL::FontUtils::FontFamily& family) const;
    Acad::ErrorStatus                 font   (ACHAR*& pTypeface,        // deprecated
                                              Adesk::Boolean& bold, 
                                              Adesk::Boolean& italic,
                                              Charset& charset,
                                              Autodesk::AutoCAD::PAL::FontUtils::FontPitch& pitch,
                                              Autodesk::AutoCAD::PAL::FontUtils::FontFamily& family) const;
protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbLinetypeTable;

class AcDbLinetypeTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLinetypeTableRecord);

    AcDbLinetypeTableRecord();
    virtual ~AcDbLinetypeTableRecord();

    typedef AcDbLinetypeTable TableType;

    Acad::ErrorStatus comments(ACHAR*& pString) const;  // deprecated
    Acad::ErrorStatus comments(const ACHAR*& pString) const;
    ACDBCORE2D_PORT Acad::ErrorStatus comments(AcString & sComments) const;
    Acad::ErrorStatus setComments(const ACHAR* pString);

    // These methods are deprecated. Please use the comments() methods
    Acad::ErrorStatus asciiDescription(ACHAR*& pString) const
                      { return comments(pString); }
    Acad::ErrorStatus asciiDescription(const ACHAR*& pString) const
                      { return comments(pString); }
    Acad::ErrorStatus setAsciiDescription(const ACHAR* pString)
                      { return setComments(pString); }

    double                            patternLength() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setPatternLength(double patternLength);

    int                               numDashes() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setNumDashes(int count);

    double                            dashLengthAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setDashLengthAt(int index , double value);

    AcDbObjectId                      shapeStyleAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setShapeStyleAt(int index, AcDbObjectId id);

    int                               shapeNumberAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setShapeNumberAt(int index, int shapeNumber);

    AcGeVector2d                      shapeOffsetAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setShapeOffsetAt(int index, const AcGeVector2d& offset);

    double                            shapeScaleAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setShapeScaleAt(int index, double scale);

    bool              isScaledToFit() const;
    void              setIsScaledToFit(bool scaledToFit);

    bool                              shapeIsUcsOrientedAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setShapeIsUcsOrientedAt(int index, bool isUcsOriented);

    bool                              shapeIsUprightAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setShapeIsUprightAt(int index, bool isUpright);

    double                            shapeRotationAt(int index) const;
    ACDBCORE2D_PORT Acad::ErrorStatus setShapeRotationAt(int index, double rotation);

    ACDBCORE2D_PORT Acad::ErrorStatus textAt(int index, AcString & sText) const;
    Acad::ErrorStatus textAt(int index, ACHAR*& text) const;    // deprecated
    Acad::ErrorStatus textAt(int index, const ACHAR*& text) const;
    Acad::ErrorStatus setTextAt(int index, const ACHAR* text);

    // Drawable API
    //
    AcGiDrawable*     drawable() override;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class ADESK_NO_VTABLE AcDbAbstractViewTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbAbstractViewTableRecord);

    AcDbAbstractViewTableRecord();
    virtual ~AcDbAbstractViewTableRecord();

    AcGePoint2d    centerPoint() const;
    void           setCenterPoint(const AcGePoint2d&);

    double         height() const;
    void           setHeight(double height);

    double         width() const;
    void           setWidth(double width);

    AcGePoint3d    target() const;
    void           setTarget(const AcGePoint3d& target);

    AcGeVector3d   viewDirection() const;
    void           setViewDirection(const AcGeVector3d& viewDirection);

    double         viewTwist() const;
    void           setViewTwist(double angle);

    double         lensLength() const;
    void           setLensLength(double length);

    double         frontClipDistance() const;
    void           setFrontClipDistance(double distance);

    double         backClipDistance() const;
    void           setBackClipDistance(double distance);

    bool           perspectiveEnabled() const;
    void           setPerspectiveEnabled(bool enabled);

    bool           frontClipEnabled() const;
    void           setFrontClipEnabled(bool enabled);

    bool           backClipEnabled() const;
    void           setBackClipEnabled(bool enabled);

    bool           frontClipAtEye() const;
    void           setFrontClipAtEye(bool atEye);

    // Background
    const AcDbObjectId&  background() const;
    AcDbObjectId&       background();
    Acad::ErrorStatus   setBackground(const AcDbObjectId& backgroundId);

   // VisualStyle
    AcDbObjectId visualStyle() const;
    Acad::ErrorStatus   setVisualStyle(const AcDbObjectId& visualStyleId);           

    // Viewport Lighting
    //
    bool                isDefaultLightingOn() const;
    Acad::ErrorStatus   setDefaultLightingOn(bool on);
    AcGiViewportTraits::DefaultLightingType defaultLightingType() const;
    Acad::ErrorStatus   setDefaultLightingType(AcGiViewportTraits::DefaultLightingType typ);

    // Brightness controls the relative intensity of lights.
    double              brightness() const;
    Acad::ErrorStatus   setBrightness(double);
    // Contrast controls intensity of ambient light, relative to other lights.
    double              contrast() const;
    Acad::ErrorStatus   setContrast(double);

    AcCmColor           ambientLightColor() const;
    Acad::ErrorStatus   setAmbientLightColor(const AcCmColor& clr);

    // A single sun (distant light) can be associated with each viewport.
    AcDbObjectId        sunId() const;
    Acad::ErrorStatus   setSun(AcDbObjectId &retId, AcDbObject *pSun);
    Acad::ErrorStatus   setSun(AcDbObjectId &retId, AcDbObject *pSun, bool eraseOldSun);

    // Tone operator parameters
    Acad::ErrorStatus toneOperatorParameters(AcGiToneOperatorParameters& params) const;
    Acad::ErrorStatus setToneOperatorParameters(const AcGiToneOperatorParameters& params);

    // UCS query methods.
    //
    Acad::ErrorStatus getUcs            ( AcGePoint3d& origin,
                                          AcGeVector3d& xAxis,
                                          AcGeVector3d& yAxis ) const;
    bool              isUcsOrthographic ( AcDb::OrthographicView& view ) const;
    AcDbObjectId      ucsName           () const;
    double            elevation         () const;

    // UCS set methods.
    //
    Acad::ErrorStatus setUcs        ( const AcGePoint3d& origin,
                                      const AcGeVector3d& xAxis,
                                      const AcGeVector3d& yAxis );
    Acad::ErrorStatus setUcs        ( AcDb::OrthographicView view );
    Acad::ErrorStatus setUcs        ( const AcDbObjectId& ucsId );
    Acad::ErrorStatus setUcsToWorld ();
    Acad::ErrorStatus setElevation  ( double elev );
 
    // Orthographic view methods.
    //
    bool              isViewOrthographic ( AcDb::OrthographicView& view ) const;
    Acad::ErrorStatus setViewDirection   ( AcDb::OrthographicView view );
};

typedef struct tagBITMAPINFO BITMAPINFO;

class AcDbViewTable;

class AcDbViewTableRecord: public  AcDbAbstractViewTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewTableRecord);

    AcDbViewTableRecord();
    virtual ~AcDbViewTableRecord();

    typedef AcDbViewTable TableType;

    Acad::ErrorStatus setParametersFromViewport(AcDbObjectId objId);

    bool isPaperspaceView() const;
    void setIsPaperspaceView(bool pspace);
    
    bool    isUcsAssociatedToView   () const;
    Acad::ErrorStatus disassociateUcsFromView ();

    ACDBCORE2D_PORT Acad::ErrorStatus getCategoryName(AcString & sCategoryName) const;
    Acad::ErrorStatus getCategoryName(ACHAR *& categoryName) const;     // deprecated
    Acad::ErrorStatus setCategoryName(const ACHAR * categoryName);

    ACDBCORE2D_PORT Acad::ErrorStatus getLayerState(AcString & layerStateName) const;
    Acad::ErrorStatus getLayerState(ACHAR*& layerStateName) const;      // deprecated
    Acad::ErrorStatus setLayerState(const ACHAR *layerStateName);
 
    Acad::ErrorStatus getLayout (AcDbObjectId& layoutId) const;
    Acad::ErrorStatus setLayout(AcDbObjectId layoutId);

    bool              isViewAssociatedToViewport () const;
    Acad::ErrorStatus setViewAssociatedToViewport (bool bVPflag);

    bool              isCameraPlottable () const;
    Acad::ErrorStatus setIsCameraPlottable (bool plottable);

    // Live Section
    AcDbObjectId      liveSection() const;
    Acad::ErrorStatus setLiveSection(const AcDbObjectId& liveSectionId);           

    /// <summary>
    /// This function provides BITMAP thumbnail of view as output
    /// </summary>
    /// <param name="thumbnail"> A reference to a pointer of Bitmap thumbnail, containing header and pixels </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    ///
    Acad::ErrorStatus getThumbnail (BITMAPINFO*& thumbnail) const;

    /// <summary>
    /// This function sets BITMAP thumbnail into view
    /// </summary>
    /// <param name="thumbnail"> A pointer of Bitmap thumbnail to be set into view </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    ///
    Acad::ErrorStatus setThumbnail(const BITMAPINFO * thumbnail);

    /// <summary>
    /// This function provides Atil::Image thumbnail of view as output
    /// </summary>
    /// <param name="pPreviewImage"> A reference to the pointer of Atil::Image thumbnail </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus getPreviewImage(Atil::Image*& pPreviewImage) const;

    /// <summary>
    /// This functions sets Atil::Image thumbnail into view
    /// </summary>
    /// <param name="pPreviewImage"> A pointer of Atil::Image thumbnail to be set into view </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus setPreviewImage (const Atil::Image * pPreviewImage);

    // Camera methods
    AcDbObjectId      camera          () const;
    Acad::ErrorStatus setCamera(AcDbObjectId cameraId);

    // Annotation scaling methods
    // Caller of this method will have to delete the AcDbAnnotationScale object
    // that is returned
    AcDbAnnotationScale* annotationScale() const;
    Acad::ErrorStatus setAnnotationScale(const AcDbAnnotationScale* pScaleObj);

    // A single sun (distant light) can be associated with each view.
    AcDbObjectId      sunId() const;
    Acad::ErrorStatus setSun(AcDbObjectId &retId, AcDbObject *pSun);
    Acad::ErrorStatus setSun(AcDbObjectId &retId, AcDbObject *pSun, bool eraseOldSun);

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbUCSTable;

class AcDbUCSTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbUCSTableRecord);

    AcDbUCSTableRecord();
    virtual ~AcDbUCSTableRecord();

    typedef AcDbUCSTable TableType;

    AcGePoint3d  origin() const;
    void         setOrigin(const AcGePoint3d& newOrigin);

    AcGeVector3d xAxis() const;
    void         setXAxis(const AcGeVector3d& xAxis);

    AcGeVector3d yAxis() const;
    void         setYAxis(const AcGeVector3d& yAxis);

    AcGePoint3d       ucsBaseOrigin    ( AcDb::OrthographicView view ) const;
    Acad::ErrorStatus setUcsBaseOrigin ( const AcGePoint3d& origin,
                                         AcDb::OrthographicView view );

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbViewportTable;

class AcDbViewportTableRecord: public  AcDbAbstractViewTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewportTableRecord);

    AcDbViewportTableRecord();
    virtual ~AcDbViewportTableRecord();

    typedef AcDbViewportTable TableType;

    Adesk::Int16   number()  const;

    AcGePoint2d    lowerLeftCorner() const;
    void           setLowerLeftCorner(const AcGePoint2d& pt);

    AcGePoint2d    upperRightCorner() const;
    void           setUpperRightCorner(const AcGePoint2d& pt);

    bool           ucsFollowMode() const;
    void           setUcsFollowMode(bool enabled);

    Adesk::UInt16  circleSides() const;
    void           setCircleSides(Adesk::UInt16 circleSides);

    bool           fastZoomsEnabled() const { return true; }
    void           setFastZoomsEnabled(bool enabled)
    {
        enabled;        // avoid unreferenced parameter warning
    }

    bool           iconEnabled() const;
    void           setIconEnabled(bool enabled);

    bool           iconAtOrigin() const;
    void           setIconAtOrigin(bool atOrigin);

    bool           gridEnabled() const;
    void           setGridEnabled(bool enabled);

    AcGePoint2d    gridIncrements() const;
    void           setGridIncrements(const AcGePoint2d& base);

    bool           snapEnabled() const;
    void           setSnapEnabled(bool enabled);

    bool           isometricSnapEnabled() const;
    void           setIsometricSnapEnabled(bool enabled);

    Adesk::Int16   snapPair() const;
    void           setSnapPair(Adesk::Int16 pairType);

    double         snapAngle() const;
    void           setSnapAngle(double angle);

    AcGePoint2d    snapBase() const;
    void           setSnapBase(const AcGePoint2d& base);

    AcGePoint2d    snapIncrements() const;
    void           setSnapIncrements(const AcGePoint2d& base);

    void           setGsView(AcGsView* pView);
    AcGsView*      gsView() const;

    bool           isUcsSavedWithViewport () const;
    void           setUcsPerViewport ( bool ucsvp );

    // GridDisplay
    bool           isGridBoundToLimits() const;
    void           setGridBoundToLimits(bool enabled);
                  
    bool           isGridAdaptive() const;
    void           setGridAdaptive(bool enabled);
                  
    bool           isGridSubdivisionRestricted() const;
    void           setGridSubdivisionRestricted(bool enabled);
                  
    bool           isGridFollow() const;
    void           setGridFollow(bool enabled);

    Adesk::Int16   gridMajor() const;
    void           setGridMajor(Adesk::Int16 value);

    // Background
    Acad::ErrorStatus   setBackground(const AcDbObjectId& backgroundId);
    AcDbObjectId        previousBackground(AcGiDrawable::DrawableType type
                                           = AcGiDrawable::kGeometry) const;
    Acad::ErrorStatus   setPreviousBackground(AcDbObjectId backgroundId,
                                              AcGiDrawable::DrawableType type
                                              = AcGiDrawable::kGeometry);
    Acad::ErrorStatus   setPreviousBackground(AcDbObjectId backgroundId,
                                              AcGiDrawable::DrawableType type,
                                              bool bForcedSwitch);
    bool                previousBackgroundForcedSwitch (void) const;
    
    // Drawable API
    //
    AcGiDrawable*  drawable() override;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbRegAppTable;

class AcDbRegAppTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbRegAppTableRecord);

    AcDbRegAppTableRecord();
    virtual ~AcDbRegAppTableRecord();

    typedef AcDbRegAppTable TableType;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbDimStyleTable;

class AcDbDimStyleTableRecord: public  AcDbSymbolTableRecord
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDimStyleTableRecord);

    AcDbDimStyleTableRecord();
    virtual ~AcDbDimStyleTableRecord();

    typedef AcDbDimStyleTable TableType;

    // Dimension variable api:
    //
    #undef DBDIMVAR_H         // force the file to get read again
    #include "dbdimvar.h"


    AcDbObjectId      arrowId(AcDb::DimArrowFlags whichArrow) const;


    // DEPRECATED METHODS!
    // These are supported but will be removed in future releases:
    //
    Acad::ErrorStatus getDimpost(ACHAR*& pOutput) const;
    Acad::ErrorStatus getDimapost(ACHAR*& pOutput) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getDimblk(AcString & sOutput) const;
                    Acad::ErrorStatus getDimblk(ACHAR*& pOutput) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getDimblk1(AcString & sOutput) const;
                    Acad::ErrorStatus getDimblk1(ACHAR*& pOutput) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getDimblk2(AcString & sOutput) const;
                    Acad::ErrorStatus getDimblk2(ACHAR*& pOutput) const;

    int dimfit() const;
    int dimunit() const;

    Acad::ErrorStatus setDimfit(int fit);
    Acad::ErrorStatus setDimunit(int unit);
    //
    // end DEPRECATED METHODS!

    bool isModifiedForRecompute() const;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class ADESK_NO_VTABLE AcDbSymbolTable: public AcDbObject
//
// (... and Subclasses)
//
// Note that there is both overloading of functions within each
// class defined by these macros and overriding of non virtual
// functions between classes.  The overriding of these functions
// is necessary to allow some member functions to take arguments
// that are appropriate for a given table.
//
{
public:
    ACDB_DECLARE_MEMBERS(AcDbSymbolTable);
    AcDbSymbolTable();
    virtual ~AcDbSymbolTable();

    typedef AcDbSymbolTableRecord RecordType;

    Acad::ErrorStatus getAt (const ACHAR* entryName,
                             AcDbSymbolTableRecord*& pRec,
                             AcDb::OpenMode openMode = AcDb::kForRead,
                             bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }

    ACDBCORE2D_PORT Acad::ErrorStatus getIdAt(const ACHAR* entryName,
                                              AcDbObjectId& recordId,
                                              bool getErasedRecord = false) const;
    Acad::ErrorStatus getAt (const ACHAR* entryName,
                             AcDbObjectId& recordId,
                             bool getErasedRecord = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRecord);
    }

    bool has(const ACHAR* name) const
    {
        AcDbObjectId id;
        this->assertReadEnabled();
        return this->getIdAt(name, id) == Acad::eOk;
    }

    ACDBCORE2D_PORT bool      has(AcDbObjectId id) const;
    Acad::ErrorStatus newIterator(AcDbSymbolTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add(AcDbSymbolTableRecord* pRecord);
    Acad::ErrorStatus add(AcDbObjectId& recordId, AcDbSymbolTableRecord* pRecord);

  protected:
    template<class RecordType> Acad::ErrorStatus openAt(const ACHAR* entryName,
                    RecordType * & pRec, AcDb::OpenMode nMode, bool bOpenErased) const
    {
        pRec = nullptr;
        AcDbObjectId id;
        Acad::ErrorStatus es = this->getIdAt(entryName, id, bOpenErased);
        if (es == Acad::eOk)
            es = ::acdbOpenObject(pRec, id, nMode, bOpenErased);
        return es;
    }
};


class AcDbBlockTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbBlockTable);
    AcDbBlockTable();
    virtual ~AcDbBlockTable();

    typedef AcDbBlockTableRecord RecordType;

    Acad::ErrorStatus getAt (const ACHAR* entryName,
                             AcDbBlockTableRecord*& pRec,
                             AcDb::OpenMode openMode = AcDb::kForRead,
                             bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }

    Acad::ErrorStatus getAt (const ACHAR* entryName,
                             AcDbObjectId& recordId,
                             bool getErasedRec = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRec);
    }
    Acad::ErrorStatus newIterator(AcDbBlockTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add   (AcDbBlockTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }

    Acad::ErrorStatus add   (AcDbObjectId& recordId, AcDbBlockTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }


protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbLayerTableRecord;
class AcDbLayerTableIterator;

class AcDbLayerTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLayerTable);
    AcDbLayerTable();
    virtual ~AcDbLayerTable();

    typedef AcDbLayerTableRecord RecordType;

    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbLayerTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbObjectId& recordId,
                            bool getErasedRecord = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRecord);
    }
    Acad::ErrorStatus newIterator(AcDbLayerTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add (AcDbLayerTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus add (AcDbObjectId& recordId, AcDbLayerTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

    void generateUsageData();

    bool hasUnreconciledLayers() const;
    Acad::ErrorStatus getUnreconciledLayers(AcDbObjectIdArray& idArray) const;

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbTextStyleTableRecord;
class AcDbTextStyleTableIterator;

class AcDbTextStyleTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbTextStyleTable);
    AcDbTextStyleTable();
    virtual ~AcDbTextStyleTable();

    typedef AcDbTextStyleTableRecord RecordType;

    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbTextStyleTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt (const ACHAR* entryName,
                             AcDbObjectId& recordId,
                             bool getErasedRecord = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRecord);
    }
    Acad::ErrorStatus newIterator(AcDbTextStyleTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add   (AcDbTextStyleTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus add   (AcDbObjectId&  recordId,
        AcDbTextStyleTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbLinetypeTableRecord;
class AcDbLinetypeTableIterator;

class AcDbLinetypeTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbLinetypeTable);
    AcDbLinetypeTable();
    virtual ~AcDbLinetypeTable();

    typedef AcDbLinetypeTableRecord RecordType;

    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbLinetypeTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbObjectId& recordId,
                            bool getErasedRec = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRec);
    }
    Acad::ErrorStatus newIterator(AcDbLinetypeTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add  (AcDbLinetypeTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus add  (AcDbObjectId& recordId,
        AcDbLinetypeTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbAbstractViewTableRecord;
class AcDbAbstractViewTableIterator;

class ADESK_NO_VTABLE AcDbAbstractViewTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbAbstractViewTable);
    AcDbAbstractViewTable();
    virtual ~AcDbAbstractViewTable();
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbAbstractViewTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbObjectId& recordId,
                            bool getErasedRecord = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRecord);
    }
    Acad::ErrorStatus newIterator(AcDbAbstractViewTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add  (AcDbAbstractViewTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus add  (AcDbObjectId&  recordId,
        AcDbAbstractViewTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }
};

class AcDbViewTableRecord;
class AcDbViewTableIterator;

class AcDbViewTable: public AcDbAbstractViewTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewTable);
    AcDbViewTable();
    virtual ~AcDbViewTable();

    typedef AcDbViewTableRecord RecordType;

    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbViewTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbObjectId& recordId,
                            bool getErasedRec = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRec);
    }
    Acad::ErrorStatus newIterator(AcDbViewTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add  (AcDbViewTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus add  (AcDbObjectId&  recordId,
        AcDbViewTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbUCSTableRecord;
class AcDbUCSTableIterator;

class AcDbUCSTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbUCSTable);
    AcDbUCSTable();
    virtual ~AcDbUCSTable();

    typedef AcDbUCSTableRecord RecordType;

    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbUCSTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbObjectId& recordId,
                            bool getErasedRecord = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRecord);
    }
    Acad::ErrorStatus newIterator(AcDbUCSTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add  (AcDbUCSTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus add  (AcDbObjectId&  recordId,
        AcDbUCSTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbViewportTableRecord;
class AcDbViewportTableIterator;

class AcDbViewportTable: public AcDbAbstractViewTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbViewportTable);
    AcDbViewportTable();
    virtual ~AcDbViewportTable();

    typedef AcDbViewportTableRecord RecordType;

    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbViewportTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbObjectId& recordId,
                            bool getErasedRecord = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRecord);
    }
    Acad::ErrorStatus newIterator(AcDbViewportTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus add  (AcDbViewportTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus add  (AcDbObjectId& recordId,
        AcDbViewportTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbRegAppTableRecord;
class AcDbRegAppTableIterator;

class AcDbRegAppTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbRegAppTable);
    AcDbRegAppTable();
    virtual ~AcDbRegAppTable();

    typedef AcDbRegAppTableRecord RecordType;

    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbRegAppTableRecord*& pRec,
                            AcDb::OpenMode openMode = AcDb::kForRead,
                            bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus getAt(const ACHAR* entryName,
                            AcDbObjectId& recordId,
                            bool getErasedRec = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRec);
    }
    Acad::ErrorStatus newIterator(AcDbRegAppTableIterator*& pIterator,
                                  bool atBeginning = true,
                                  bool skipDeleted = true) const;
    Acad::ErrorStatus   add     (AcDbRegAppTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus   add     (AcDbObjectId&  recordId,
        AcDbRegAppTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

class AcDbDimStyleTableRecord;
class AcDbDimStyleTableIterator;

class AcDbDimStyleTable: public AcDbSymbolTable
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDimStyleTable);
    AcDbDimStyleTable();
    virtual ~AcDbDimStyleTable();

    typedef AcDbDimStyleTableRecord RecordType;

    Acad::ErrorStatus   getAt   (const ACHAR* entryName,
                                 AcDbDimStyleTableRecord*& pRec,
                                 AcDb::OpenMode openMode = AcDb::kForRead,
                                 bool openErasedRec = false) const
    {
        return this->openAt(entryName, pRec, openMode, openErasedRec);
    }
    Acad::ErrorStatus   getAt   (const ACHAR* entryName,
                                 AcDbObjectId& recordId,
                                 bool getErasedRec = false) const
    {
        return this->getIdAt(entryName, recordId, getErasedRec);
    }
    Acad::ErrorStatus   newIterator(AcDbDimStyleTableIterator*& pIterator,
                                    bool atBeginning = true,
                                    bool skipDeleted = true) const;
    Acad::ErrorStatus   add     (AcDbDimStyleTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(pRecord);
    }
    Acad::ErrorStatus   add     (AcDbObjectId&  recordId,
        AcDbDimStyleTableRecord* pRecord)
    {
        return this->AcDbSymbolTable::add(recordId, pRecord);
    }

protected:
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

///// AcDbSymbolTableIterator
//
// This class is responsible for iterating over the records in a symbol
// table.
//
// This is a completely "generic" symbol table iterator in that it can 
// be used to iterate over the contents of any AcDbSymbolTable subclass.
// However, symbol table specific iterators are defined below.
//
// One major item of note.  The creation of one of these iterators
// requires the opening (for read) of the table being iterated over.
// This read stays in effect until the iterator is destroyed.
//
class AcDbSymbolTableIterator
{
public:
    virtual ~AcDbSymbolTableIterator();

    void                start   (bool atBeginning = true,
                                 bool skipDeleted = true);

    bool                done    () const;


    Acad::ErrorStatus   getRecordId(AcDbObjectId& id) const;

    Acad::ErrorStatus   getRecord(AcDbSymbolTableRecord*& pRecord,
                                 AcDb::OpenMode openMode = AcDb::kForRead,
                                 bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

    void                step    (bool forward = true,
                                 bool skipDeleted = true);

    ACDBCORE2D_PORT Acad::ErrorStatus   seek    (AcDbObjectId id);

    ACDBCORE2D_PORT Acad::ErrorStatus   seek    (const AcDbSymbolTableRecord* pRecord);
protected:
    template<class RecordType> Acad::ErrorStatus openRecord(RecordType * & pRec,
                                 AcDb::OpenMode nMode, bool bOpenErased) const
    {
        pRec = nullptr;
        AcDbObjectId id;
        Acad::ErrorStatus es = this->getRecordId(id);
        if (es == Acad::eOk)
            es = ::acdbOpenObject(pRec, id, nMode, bOpenErased);
        return es;
    }
                                                
    class AcDbImpSymbolTableIterator * mpImp;
    AcDbSymbolTableIterator();
    friend class AcDbSymbolTable;
};

class AcDbBlockTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbBlockTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbBlockTableIterator();
    friend class AcDbBlockTable;
};

class AcDbLayerTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbLayerTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }
    bool getSkipHidden() const;
    void setSkipHidden(bool value);
    bool getSkipReconciled() const;
    void setSkipReconciled(bool value);
protected:
    AcDbLayerTableIterator();
    friend class AcDbLayerTable;
};

class AcDbTextStyleTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbTextStyleTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbTextStyleTableIterator();
    friend class AcDbTextStyleTable;
};

class AcDbLinetypeTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbLinetypeTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbLinetypeTableIterator();
    friend class AcDbLinetypeTable;
};

class AcDbAbstractViewTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbAbstractViewTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbAbstractViewTableIterator();
    friend class AcDbAbstractViewTable;
};

class AcDbViewTableIterator : public AcDbAbstractViewTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbViewTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbViewTableIterator();
    friend class AcDbViewTable;
};

class AcDbUCSTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbUCSTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbUCSTableIterator();
    friend class AcDbUCSTable;
};

class AcDbViewportTableIterator : public AcDbAbstractViewTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbViewportTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbViewportTableIterator();
    friend class AcDbViewportTable;
};

class AcDbRegAppTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbRegAppTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbRegAppTableIterator();
    friend class AcDbRegAppTable;
};

class AcDbDimStyleTableIterator : public AcDbSymbolTableIterator
{
public:
    Acad::ErrorStatus getRecord(AcDbDimStyleTableRecord*& pRecord,
        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedRec = false) const
    {
        return this->openRecord(pRecord, openMode, openErasedRec);
    }

protected:
    AcDbDimStyleTableIterator();
    friend class AcDbDimStyleTable;
};


class AcDbBlockTableRecordIterator
{
public:
    virtual ~AcDbBlockTableRecordIterator();

    void              start (bool atBeginning = true,
                             bool skipDeleted = true);

    bool              done  () const;

    Acad::ErrorStatus getEntityId (AcDbObjectId& entityId) const;

    Acad::ErrorStatus getEntity(AcDbEntity*& pEntity, AcDb::OpenMode openMode = AcDb::kForRead,
                                bool openErasedEntity = false) const;

    AcDbBlockTableRecord* blockTableRecord() const;

    void              step (bool forward = true,
                            bool skipDeleted = true);

    ACDBCORE2D_PORT Acad::ErrorStatus seek (AcDbObjectId id);

    ACDBCORE2D_PORT Acad::ErrorStatus seek (const AcDbEntity* pEntity);

protected:
    class AcDbImpBlockTableRecordIterator* mpImp;
private:
    AcDbBlockTableRecordIterator();
    friend class AcDbImpBlockTableRecord;
};


// This class will be removed in the next release.   Instead, use
// AcDbBlockTableRecord::getBlockReferenceIds().
//
class AcDbBlockReferenceIdIterator
{
public:
    ~AcDbBlockReferenceIdIterator();

    void              start () { mPos = 0; }
        
    bool              done  () const { return mPos >= mAry.length(); }

    Acad::ErrorStatus getBlockReferenceId (AcDbObjectId& id) const;

    Acad::ErrorStatus getDatabase (AcDbDatabase*& pDb) const;

    Acad::ErrorStatus getBlockReference(AcDbBlockReference*& pBlkRef,
                        AcDb::OpenMode openMode = AcDb::kForRead, bool openErasedEntity = false) const;

    void              step () { mPos++; }

    ACDBCORE2D_PORT Acad::ErrorStatus seek (AcDbObjectId id);

private:
    AcDbBlockReferenceIdIterator();
    friend class AcDbBlockTableRecord;

    int               mPos;
    AcDbObjectIdArray mAry;
};

#pragma pack(pop)

// These are deprecated and will be removed in the future. Please
// use the methods that take an AcString & arg.
inline Acad::ErrorStatus AcDbSymbolTableRecord::getName(ACHAR*& pName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbSymbolTableRecord::getName, pName);
}
inline Acad::ErrorStatus AcDbBlockTableRecord::comments(ACHAR*& pComments) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbBlockTableRecord::comments, pComments);
}
inline Acad::ErrorStatus AcDbBlockTableRecord::pathName(ACHAR*& pPath) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbBlockTableRecord::pathName, pPath);
}
inline ACHAR * AcDbLayerTableRecord::plotStyleName() const
{
    AcString sName;
    return ::acutAcStringToAChar(sName, this->plotStyleName(sName));
}
inline ACHAR * AcDbLayerTableRecord::plotStyleName(const AcDbObjectId& viewportId,
                                                   bool& isOverride) const
{
    AcString sName;
    return ::acutAcStringToAChar(sName, this->plotStyleName(viewportId, sName, isOverride));
}
inline ACHAR * AcDbLayerTableRecord::description() const
{
    AcString sDescription;
    return ::acutAcStringToAChar(sDescription, this->description(sDescription));
}
inline Acad::ErrorStatus AcDbTextStyleTableRecord::fileName(ACHAR*& fileName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbTextStyleTableRecord::fileName, fileName);
}
inline Acad::ErrorStatus AcDbTextStyleTableRecord::bigFontFileName(ACHAR*& fileName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbTextStyleTableRecord::bigFontFileName, fileName);
}
inline Acad::ErrorStatus AcDbTextStyleTableRecord::font(ACHAR*& pTypeface,        // deprecated
                                        bool & bold, 
                                        bool & italic,
                                        Charset& charset,
                                        Autodesk::AutoCAD::PAL::FontUtils::FontPitch& pitch,
                                        Autodesk::AutoCAD::PAL::FontUtils::FontFamily& family) const
{
    pTypeface = nullptr;
    AcString sTypeface;
    const Acad::ErrorStatus es = this->font(sTypeface, bold, italic, charset, pitch, family);
    if (es == Acad::eOk)
        ::acutNewString(sTypeface.kwszPtr(), pTypeface);
    return es;
}
inline Acad::ErrorStatus AcDbLinetypeTableRecord::comments(ACHAR*& pComments) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbLinetypeTableRecord::comments, pComments);
}
inline Acad::ErrorStatus AcDbLinetypeTableRecord::textAt(int nIndex, ACHAR*& pText) const
{
    AcString sText;
    return ::acutAcStringToAChar(sText, pText, this->textAt(nIndex, sText));
}

inline Acad::ErrorStatus AcDbViewTableRecord::getCategoryName(ACHAR*& pCategoryName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbViewTableRecord::getCategoryName, pCategoryName);
}
inline Acad::ErrorStatus AcDbViewTableRecord::getLayerState(ACHAR*& pLayerStateName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbViewTableRecord::getLayerState, pLayerStateName);
}
inline Acad::ErrorStatus AcDbDimStyleTableRecord::getDimpost(ACHAR *& pOutput) const
{
    return ::acutNewString(this->dimpost(), pOutput);
}

inline Acad::ErrorStatus AcDbDimStyleTableRecord::getDimapost(ACHAR *& pOutput) const
{
    return ::acutNewString(this->dimapost(), pOutput);
}
inline Acad::ErrorStatus AcDbDimStyleTableRecord::getDimblk(ACHAR *& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDimStyleTableRecord::getDimblk, pOutput);
}
inline Acad::ErrorStatus AcDbDimStyleTableRecord::getDimblk1(ACHAR *& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDimStyleTableRecord::getDimblk1, pOutput);
}
inline Acad::ErrorStatus AcDbDimStyleTableRecord::getDimblk2(ACHAR *& pOutput) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbDimStyleTableRecord::getDimblk2, pOutput);
}

#endif

