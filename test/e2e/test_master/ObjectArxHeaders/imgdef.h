//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef __IMGDEF_H
#  define __IMGDEF_H	1
#  include "dbmain.h"
#  include "acgi.h"
#  include "gept2dar.h"
#  include "gemat2d.h"
#  include "AdAChar.h"
#  pragma  pack (push, 8)
class RasterImageDefImp;
class AcDbImpRasterImageDefReactor;
typedef struct tagBITMAPINFO BITMAPINFO;
namespace Atil
{
  class Image;
  class FileReadDescriptor;
}
enum ClassVersion
{
  kVersion1 = 0,
  kVersion2 = 1,
  kVersion3 = 2
};
#  pragma  warning( disable : 4275 ) 
#  ifdef ISMDLLACCESS
#    undef ISMDLLACCESS
#  endif
#  ifdef ISMDLLACCESSDATA
#    undef ISMDLLACCESSDATA
#  endif
#  ifdef ISM_OBJ
#    define ISMDLLACCESS	__declspec(dllexport)
#    define ISMDLLACCESSDATA
#  else 
#    define ISMDLLACCESS
#    define ISMDLLACCESSDATA	__declspec(dllimport)
#  endif
class IAcReadStream;
class ISMDLLACCESS AcDbRasterImageDef : public AcDbObject
{
public:
  static ClassVersion classVersion();
  ACRX_DECLARE_MEMBERS(AcDbRasterImageDef);
  AcDbRasterImageDef();
  virtual ~AcDbRasterImageDef();
  RasterImageDefImp* ptrImp() const;
  RasterImageDefImp* setPtrImp(RasterImageDefImp* pImp);
  virtual Acad::ErrorStatus subErase(Adesk::Boolean erasing) override;
  virtual Acad::ErrorStatus subClose() override;
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;
  virtual AcGiSentScanLines* makeScanLines(const AcGiRequestScanLines* pReq, const AcGeMatrix2d& pixToScreen, AcGePoint2dArray* pActiveClipBndy = 0, Adesk::Boolean draftQuality = false, Adesk::Boolean isTransparent = false, const double brightness = 50.0, const double contrast = 50.0, const double fade = 0.0) const;
  virtual Acad::ErrorStatus setSourceFileName(const ACHAR* pPathName);
  virtual Acad::ErrorStatus setActiveFileName(const ACHAR* pPathName);
  virtual const ACHAR* searchForActivePath();
  virtual const ACHAR* sourceFileName() const;
  virtual const ACHAR* activeFileName() const;
  virtual Acad::ErrorStatus embed();
  virtual Adesk::Boolean isEmbedded() const;
  virtual Acad::ErrorStatus load();
  virtual Acad::ErrorStatus unload(Adesk::Boolean modifyDatabase = true);
  virtual Adesk::Boolean isLoaded() const;
  virtual AcGeVector2d size() const;
  virtual AcGiImageOrg organization() const;
  virtual int colorDepth() const;
  virtual const ACHAR* fileType() const;
  virtual int entityCount(Adesk::Boolean* pbLocked = 0) const;
  virtual void updateEntities() const;
  enum Units
  {
    kNone = 0,
    kMillimeter = 1,
    kCentimeter = 2,
    kMeter = 3,
    kKilometer = 4,
    kInch = 5,
    kFoot = 6,
    kYard = 7,
    kMile = 8,
    kMicroinches = 9,
    kMils = 10,
    kAngstroms = 11,
    kNanometers = 12,
    kMicrons = 13,
    kDecimeters = 14,
    kDekameters = 15,
    kHectometers = 16,
    kGigameters = 17,
    kAstronomical = 18,
    kLightYears = 19,
    kParsecs = 20
  };
  virtual Acad::ErrorStatus setResolutionMMPerPixel(const AcGeVector2d& resMMPerPixel);
  virtual AcGeVector2d resolutionMMPerPixel() const;
  virtual void setResolutionUnits(AcDbRasterImageDef::Units units);
  virtual Units resolutionUnits() const;
  virtual Acad::ErrorStatus loadThumbnail(Adesk::UInt16& maxWidth, Adesk::UInt16& maxHeight, Adesk::UInt8* pPalette = 0, int nPaletteEntries = 0);
  virtual Acad::ErrorStatus unloadThumbnail();
  virtual void* createThumbnailBitmap(BITMAPINFO*& pBitmapInfo, Adesk::UInt8 brightness = 50, Adesk::UInt8 contrast = 50, Adesk::UInt8 fade = 0);
    ////////////////////////////////////////////////
    // Image access
    ////////////////////////////////////////////////
  virtual Atil::Image* imageCopy(Adesk::Boolean bForceImageLoad = true) const;
  virtual Atil::FileReadDescriptor* fileDescCopy() const;
  virtual Acad::ErrorStatus openImage(Atil::Image*& pImage);
  virtual Acad::ErrorStatus closeImage();
  virtual Acad::ErrorStatus setImage(const Atil::Image* pImage, const Atil::FileReadDescriptor* pFileDesc, Adesk::Boolean modifyDatabase = true);
  virtual Acad::ErrorStatus setUndoStoreSize(unsigned int maxImages = 10);
  virtual unsigned int undoStoreSize() const;
  virtual Adesk::Boolean imageModified() const;
  virtual Acad::ErrorStatus setImageModified(Adesk::Boolean modified);
  virtual IAcReadStream* getReadStream();
  Acad::ErrorStatus forceImageFileClosed(Adesk::Boolean modifyDatabase);
    ////////////////////////////////////////////////
    // Image dictionary access
    ////////////////////////////////////////////////
  static Acad::ErrorStatus createImageDictionary(AcDbDatabase* pDb, AcDbObjectId& dictId);
  static AcDbObjectId imageDictionary(AcDbDatabase* pDb);
  enum
  {
    kMaxSuggestNameSize = 2049
  };
  static Acad::ErrorStatus suggestName(AcDbDictionary* pImageDictionary, const ACHAR* pNewImagePathName, ACHAR* newImageName, size_t nSize);
private:
  RasterImageDefImp* mpImp;
  static ClassVersion mVersion;
};
inline RasterImageDefImp* AcDbRasterImageDef::ptrImp() const
{
  return mpImp;
}
inline RasterImageDefImp* AcDbRasterImageDef::setPtrImp(RasterImageDefImp* pImp)
{
  RasterImageDefImp* oldImp = mpImp;
  mpImp = pImp;
  return oldImp;
}
class ISMDLLACCESS AcDbRasterImageDefReactor : public AcDbObject
{
public:
  static ClassVersion classVersion();
  ACRX_DECLARE_MEMBERS(AcDbRasterImageDefReactor);
  AcDbRasterImageDefReactor();
  virtual ~AcDbRasterImageDefReactor();
  virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* filer) override;
  virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* filer) const override;
  virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* filer) override;
  virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* filer) const override;
  virtual void erased(const AcDbObject* dbObj, Adesk::Boolean pErasing = true) override;
  virtual void modified(const AcDbObject* dbObj) override;
  enum DeleteImageEvent
  {
    kUnload = 1,
    kErase = 2
  };
  virtual Adesk::Boolean onDeleteImage(const AcDbRasterImageDef* pImageDef, const Atil::Image* pImage, DeleteImageEvent event, Adesk::Boolean cancelAllowed);
  static void setEnable(Adesk::Boolean enable);
private:
  AcDbImpRasterImageDefReactor* mpImp;
  static ClassVersion mVersion;
};
class ISMDLLACCESS AcDbRasterImageDefTransReactor : public AcDbObjectReactor
{
public:
  ACRX_DECLARE_MEMBERS(AcDbRasterImageDefTransReactor);
  virtual ~AcDbRasterImageDefTransReactor();
  virtual Adesk::Boolean onDeleteImage(const AcDbRasterImageDef* pImageDef, const Atil::Image* pImage, AcDbRasterImageDefReactor::DeleteImageEvent event, Adesk::Boolean cancelAllowed) = 0;
};
class ISMDLLACCESS AcDbRasterImageDefFileAccessReactor : public AcDbObjectReactor
{
public:
  ACRX_DECLARE_MEMBERS(AcDbRasterImageDefFileAccessReactor);
  virtual ~AcDbRasterImageDefFileAccessReactor();
  virtual void onAttach(const AcDbRasterImageDef*, const ACHAR* pPath) = 0;
  virtual void onDetach(const AcDbRasterImageDef*, const ACHAR* pPath) = 0;
  virtual Adesk::Boolean onOpen(const AcDbRasterImageDef*, const ACHAR* pPath, const ACHAR* pActivePath, Adesk::Boolean& replacePath, ACHAR*& replacementPath) = 0;
  virtual Adesk::Boolean onPathChange(const AcDbRasterImageDef*, const ACHAR* pPath, const ACHAR* pActivePath, Adesk::Boolean& replacePath, ACHAR*& replacementPath) = 0;
  virtual void onClose(const AcDbRasterImageDef*, const ACHAR* pPath) = 0;
  virtual void onDialog(AcDbRasterImageDef*, const ACHAR* pCaption, const ACHAR* pFileExtensions) = 0;
};
//////////////////// inlines ////////////////////
inline ClassVersion AcDbRasterImageDef::classVersion()
{
  return mVersion;
}
inline ClassVersion AcDbRasterImageDefReactor::classVersion()
{
  return mVersion;
}
#  pragma  warning( default : 4275 ) 
#  pragma  pack (pop)
#endif
