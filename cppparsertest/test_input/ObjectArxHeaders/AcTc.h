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
// Name:            AcTc.h
//
// Description:     Header for all the published API classes
//
//////////////////////////////////////////////////////////////////////////////

#include "AdAChar.h"

#pragma once

#ifdef  _ACTC_BUILD
#  define   ACTC_PORT  __declspec(dllexport)
#else
#  define   ACTC_PORT  
#endif

class AcTcTool;
class AcTcStockTool;
class AcTcCatalog;
class AcTcCatalogItem;
class AcTcScheme;
class AcTcCatalogSet;
class AcTcSystemInternals;
class AcTcImpCatalogItem;
class AcTcCatalogItemReactor;

// Context flags
#define ACTC_IMAGE_NORMAL                   (0x1 << 0)
#define ACTC_IMAGE_SELECTED                 (0x1 << 1)
#define ACTC_IMAGE_HALO                     (0x1 << 2)
#define ACTC_IMAGE_SHADOW                   (0x1 << 3)

// Buffer sizes
#define ACTC_MAX_CATALOG_ITEM_NAME          256
#define ACTC_MAX_CATALOG_ITEM_DESCRIPTION   2048
#define ACTC_MAX_CATALOG_ITEM_KEYWORDS      1024
#define ACTC_MAX_CATALOG_ITEM_TOOLTIP_TEXT  1024
#define ACTC_MAX_CATALOG_ITEM_LINK_NAME     256
#define ACTC_MAX_SCHEME_NAME                256
#define ACTC_MAX_TOOL_NAME                  ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_STOCKTOOL_NAME             ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_PALETTE_NAME               ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_PACKAGE_NAME               ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_CATEGORY_NAME              ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_CATALOG_NAME               ACTC_MAX_CATALOG_ITEM_NAME
#define ACTC_MAX_URL                        1024
#define ACTC_MAX_PATH                       MAX_PATH
#define ACTC_MAX_COMMAND_NAME               256
#define ACTC_MAX_COMMAND_ARGS               1024
#define ACTC_MAX_HELPINFO_FILE              ACTC_MAX_URL
#define ACTC_MAX_HELPINFO_COMMAND           256
#define ACTC_MAX_HELPINFO_DATA              ACTC_MAX_URL
#define ACTC_MAX_PARENT_DOCUMENT_NAME       256
#define ACTC_MAX_PUBLISHER_NAME             256
#define ACTC_MAX_PRODUCT_NAME               256
#define ACTC_MAX_LOCALE                     512


// Commands to execute after downloading stock tool binary files
#define ACTC_POSTDOWNLOADCMD_EXECUTE        ACRX_T(/*MSGO*/"Execute")

#define ACTC_DEFAULTDIR_IMAGE               ACRX_T(/*MSGO*/"Images")
#define ACTC_DEFAULTFILE_IMAGE              ACRX_T(/*MSGO*/"Image")

namespace AcTc
{
    enum AccessRight
    {
        kAccessRead             = (0x1 << 0),
        kAccessReadWrite        = (0x1 << 1),
        kAccessReadOnlyFile     = (0x1 << 2),
        kAccessMultiple         = (0x1 << 3),       // For internal use
        kAccessNewerVersion     = (0x1 << 4),       // For internal use
    };

    enum CatalogItemType
    {
        kItemUnknown            = 0,
        kItemTool               = (0x1 << 0),
        kItemPackage            = (0x1 << 1),
        kItemPalette            = (0x1 << 2),
        kItemCategory           = (0x1 << 3),
        kItemCatalog            = (0x1 << 4),
        kItemStockTool          = (0x1 << 5),
    };

    enum ReferencePath
    {
        kLoadRefPath            = 1,
        kSaveRefPath            = 2,
    };

    enum ImageType
    { 
        kImageTypeUninitialized = -1,
        kImageTypeBitmap        = 1,
        kImageTypeMetaFile      = 2,
        kImageTypeIcon          = 3,
        kImageTypeEnhMetaFile   = 4,
        kImageTypeJpeg          = 5,
        kImageTypePng           = 6,
        kImageTypeGif           = 7,
        kImageTypeTif           = 8
    };

    enum ImageOption
    {
        kImageOptionNone                = 0x0,
        kImageOptionRenderBitmapOpaque  = (0x1 << 0),
        kImageOptionUserOverride        = (0x1 << 1),
    };

    enum LoadOption
    {
        kLoadLinks              = (0x1 << 0),
        kLoadImages             = (0x1 << 1),
        kLoadOverlayImages      = (0x1 << 2),       // For internal use
        kDoNotNotifyReactor     = (0x1 << 3),       // For internal use
    };

    enum SaveOption
    {
        kSaveLinksAsLinks       = (0x1 << 0),
        kSaveLinksAsEmbedded    = (0x1 << 1),
        kSaveImages             = (0x1 << 2),
        kSaveAs                 = (0x1 << 3),       // For internal use
        kSaveOverlayImages      = (0x1 << 4),       // For internal use
        kSaveAnsi               = (0x1 << 5),       // For internal use
    };

    enum DownloadOption
    { 
        kDownloadItem           = (0x1 << 0),
        kDownloadLinkedItem     = (0x1 << 1),
        kDownloadImage          = (0x1 << 2),
        kDownloadStockTool      = (0x1 << 3),
        kDownloadChildren       = (0x1 << 4),
        kDownloadAll            = kDownloadItem | kDownloadLinkedItem |
                                  kDownloadImage | kDownloadStockTool |
                                  kDownloadChildren,
        kDownloadCleanDownloadDir = (0x1 << 5),
        kDownloadShowProgress   = (0x1 << 6),
        kDownloadUseNewIds      = (0x1 << 7),       // For internal use
        kDownloadNotifyTool     = (0x1 << 12)       // For internal use. Note: kDownloadNotifyTool 
                                                    // and kRefreshNotifyTool must have different values.
    };

    enum RefreshOption
    { 
        kRefreshItem            = kDownloadItem,
        kRefreshLinkedItem      = kDownloadLinkedItem,
        kRefreshImage           = kDownloadImage,
        kRefreshStockTool       = kDownloadStockTool,
        kRefreshChildren        = kDownloadChildren,
        kRefreshAll             = kDownloadAll,
        kRefreshShowProgress    = kDownloadShowProgress,
        kRefreshNotifyTool      = (0x1 << 16)       // For internal use. Note: kDownloadNotifyTool 
                                                    // and kRefreshNotifyTool must have different values.
    };

    enum CatalogType
    {
        kCatalog                = (0x1 << 0),
        kStockToolCatalog       = (0x1 << 1),
        kShapeCatalog           = (0x1 << 2)
    };

    enum ToolType
    {
        kToolNormal             = 1,
        kToolFlyout             = 2,
        kToolText               = 3,
        kToolSeparator          = 4,
    };

    enum SortOption
    {
        kSortByName             = (0x1 << 0),
        kSortByStockTool        = (0x1 << 1),
        kSortByCustom           = (0x1 << 2),
        kAscending              = (0x1 << 3),
        kDescending             = (0x1 << 4),
    };

    enum ItemOption
    {
        kItemOptionNone                 = 0x0,
        kItemOptionSupportsAutoImage    = (0x1 << 0),
        kItemOptionSupportsUserImage    = (0x1 << 1),
        kItemOptionMenuUpdateImage      = (0x1 << 2),
        kItemOptionMenuSetImage         = (0x1 << 3),
        kItemOptionMenuRemoveImage      = (0x1 << 4),
    };
};


using namespace AcTc;

struct ACTC_IMAGE_INFO
{
    SIZE                mSize;
    ACHAR               mszResourceName[MAX_PATH];
    ACHAR               mszSourceFile[MAX_PATH];
};


struct ACTC_TARGET_PRODUCT_INFO 
{
    ACHAR               mszProductName[ACTC_MAX_PRODUCT_NAME];
    ACHAR               mszLocaleIds[ACTC_MAX_LOCALE];
    DWORD               mdwMinVersion;
    DWORD               mdwMaxVersion;
};


//
// Classes
//

class ACTC_PORT AcTcImage
{
public:
    AcTcImage();
    AcTcImage(const AcTcImage& srcImage);
    virtual ~AcTcImage();

    AcTcImage&          operator=           (const AcTcImage& acTcImage);
    BOOL                Load                (LPCTSTR pszFile);
    BOOL                Load                (HBITMAP hBitmap);
    BOOL                Load                (IStream* pStream);
    BOOL                Save                (LPCTSTR pszFile);
    BOOL                Save                (LPCTSTR sFileName, 
                                             AcTc::ImageType nSaveAsType);
    BOOL                Save                (IStream* pStream);
    BOOL                Render              (HDC hDC, 
                                             int xPos, 
                                             int yPos, 
                                             int nWidth, 
                                             int nHeight,
                                             UINT nStyle = ACTC_IMAGE_NORMAL,
                                             BOOL bTransparentBitmap = TRUE);
    BOOL                GetSize             (LPSIZE pSize) const;
    AcTc::ImageType     GetType             (void) const;
    BOOL                IsImageLoaded       (void) const;
    BOOL                GetHICON            (HICON &hIcon);
    BOOL                GetHBITMAP          (COLORREF cBackGroundColor, 
                                             HBITMAP& hBitmap);
    AcTc::ImageType     GetSaveType         (void) const;
    BOOL                SetSaveType         (AcTc::ImageType nSaveType);
    BOOL                ConvertTo           (AcTc::ImageType nToImageType, 
                                             BOOL bTransparent);
    BOOL                IsForDarkTheme      (void) const;
    void                SetIsForDarkTheme   (BOOL bValue);

protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class ACTC_PORT AcTcImageList
{
    friend class AcTcImpCatalogItem;
public:
    virtual ~AcTcImageList();

    AcTcImageList&      operator=           (const AcTcImageList& acTcImageList);
    INT_PTR             GetImageCount       (void) const;
    BOOL                GetImageInfo        (INT_PTR iIndex, 
                                             ACTC_IMAGE_INFO* pImageInfo,
                                             BOOL bUseDarkTheme = FALSE) const;
    BOOL                GetEditImageInfo    (INT_PTR iIndex,
                                             ACTC_IMAGE_INFO* pImageInfo,
                                             BOOL bUseDarkTheme = FALSE);
    BOOL                SetImageInfo        (INT_PTR iIndex, 
                                             const ACTC_IMAGE_INFO* pImageInfo,
                                             BOOL bUseDarkTheme = FALSE);
    AcTcImage*          GetImage            (INT_PTR iIndex,BOOL bUseDarkTheme = FALSE);
    INT_PTR             SetImage            (INT_PTR iIndex, 
                                             const AcTcImage* pImage,
                                             BOOL bUseDarkTheme = FALSE);
    INT_PTR             Add                 (const AcTcImage* pImage,BOOL bUseDarkTheme = FALSE);
    INT_PTR             Add                 (const ACTC_IMAGE_INFO* pImageInfo);
    INT_PTR             UpdateImage         (const AcTcImage* pImage,BOOL bUseDarkTheme = FALSE);
    BOOL                Delete              (INT_PTR iIndex);
    BOOL                DeleteAllImages     (void);
    BOOL                LoadImage           (INT_PTR iIndex,BOOL bUseDarkTheme = FALSE);
    INT_PTR             GetImageIndex       (const SIZE* pSize, 
                                             BOOL bExactMatch = FALSE,
                                             BOOL bUseDarkTheme = FALSE);
    AcTc::ImageOption   GetOption           (void) const;
    BOOL                SetOption           (AcTc::ImageOption nOption);

protected:
    AcTcImageList(AcTcCatalogItem* pCatalogItem);
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;

};


class ACTC_PORT AcTcManager
{
public:
    AcTcManager();
    virtual ~AcTcManager();

    INT_PTR             GetStockToolCatalogCount(void) const;
    AcTcCatalogItem *   GetStockToolCatalog (int nIndex) const;
    AcTcStockTool   *   FindStockTool       (const GUID& id) const;

    INT_PTR             GetCatalogCount     (void) const;
    AcTcCatalogItem *   GetCatalog          (int nIndex) const;
    AcTcCatalogItem *   FindItem            (const GUID& id) const;
    
    int                 GetCatalogPath      (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetCatalogPath      (LPCTSTR pszPath);
    int                 GetStockToolCatalogPath(LPTSTR pszString,
                                                int cchSize) const;
    BOOL                SetStockToolCatalogPath(LPCTSTR pszPath);
    int                 GetShapeCatalogFile (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetShapeCatalogFile (LPCTSTR pszFile);
    INT_PTR             AddStockToolCatalog (AcTcCatalogItem* pCatalogItem);
    INT_PTR             AddCatalog          (AcTcCatalogItem* pCatalogItem);
    BOOL                LoadCatalogs        (DWORD dwCatalogType= kCatalog | kStockToolCatalog,
                                             DWORD dwLoadOption = kLoadLinks);
    BOOL                UnloadCatalogs      (DWORD dwCatalogType= kCatalog | kStockToolCatalog);
    BOOL                SaveCatalogs        (DWORD dwCatalogType= kCatalog | kStockToolCatalog,
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    AcTcCatalogItem*    GetShapeCatalog     (void);
    AcTcCatalogItem *   GetShapePackage     (LPCTSTR lpszName = NULL) const;
    INT_PTR             InsertStockToolCatalog(INT_PTR nIndex,
                                             AcTcCatalogItem* pCatalog);
    AcTcCatalogItem*    RemoveStockToolCatalog(int nIndex);

    INT_PTR             GetSchemeCount      (void) const;
    AcTcScheme      *   GetScheme           (int nIndex) const;
    AcTcScheme      *   GetScheme           (LPCTSTR pszSchemeName) const;
    INT_PTR             AddScheme           (AcTcScheme* pScheme);
    BOOL                RemoveScheme        (AcTcScheme* pScheme);

protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class ACTC_PORT AcTcScheme
{
public:
    AcTcScheme(LPCTSTR pszSchemeName);
    virtual ~AcTcScheme();

    int                 GetName             (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetName             (LPCTSTR pszString);

    AcTcCatalogSet  *   GetCatalogSet       (DWORD dwCatalogType) const;

    AcTcCatalogItem *   FindItem            (const GUID& id) const;
    AcTcCatalogItem *   FindItem            (const GUID& id,
                                             DWORD dwCatalogType) const;

    BOOL                LoadCatalogs        (void);
    BOOL                LoadCatalogs        (DWORD dwCatalogType,
                                             DWORD dwLoadOption);
    BOOL                UnloadCatalogs      (void);
    BOOL                UnloadCatalogs      (DWORD dwCatalogType);
    BOOL                SaveCatalogs        (void);
    BOOL                SaveCatalogs        (DWORD dwCatalogType,
                                             DWORD dwSaveOption);

protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class ACTC_PORT AcTcCatalogSet
{
public:
    virtual ~AcTcCatalogSet();

    AcTcScheme      *   GetScheme           (void) const;

    INT_PTR             GetCatalogCount     (void) const;
    AcTcCatalogItem *   GetCatalog          (int nIndex) const;

    AcTcCatalogItem *   FindItem            (const GUID& id) const;
    
    int                 GetCatalogPath      (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetCatalogPath      (LPCTSTR pszPath);

    INT_PTR             AddCatalog          (AcTcCatalogItem* pCatalog);
    INT_PTR             InsertCatalog       (INT_PTR nIndex,
                                             AcTcCatalogItem* pCatalog);
    AcTcCatalogItem*    RemoveCatalog       (int nIndex);

    BOOL                LoadCatalogs        (void);
    BOOL                LoadCatalogs        (DWORD dwLoadOption);
    BOOL                UnloadCatalogs      (void);
    BOOL                SaveCatalogs        (void);
    BOOL                SaveCatalogs        (DWORD dwSaveOption);

protected:
    // Protected constructor
    AcTcCatalogSet(DWORD dwCatalogType);

protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class ACTC_PORT AcTcCatalogItem 
{
    // For protected funcion access from imp class
    friend class AcTcImpCatalogItem;

public:
    static AcTcCatalogItem * FromFile       (LPCTSTR pszFile, 
                                             BOOL bLoad         = FALSE, 
                                             DWORD dwLoadOption = kLoadLinks);
    static CatalogItemType   GetType        (LPCTSTR pszFile);

public:
    virtual ~AcTcCatalogItem();

    BOOL                Load                (LPCTSTR pszUrl, 
                                             DWORD dwLoadOption = kLoadLinks);
    BOOL                LoadLink            (void);
    BOOL                Save                (LPCTSTR pszUrl,
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    INT_PTR             AddChild            (AcTcCatalogItem* pNewItem);
    INT_PTR             InsertChild         (INT_PTR iIndex, 
                                             AcTcCatalogItem* pNewItem);
    BOOL                DeleteChild         (AcTcCatalogItem* pItem);
    BOOL                DetachChild         (AcTcCatalogItem* pItem);
    INT_PTR             GetChildCount       (void) const;
    INT_PTR             GetChildCount       (CatalogItemType nType) const;
    AcTcCatalogItem *   GetChild            (INT_PTR iIndex) const;
    AcTcCatalogItem *   GetNextChild        (int iIndex, 
                                             CatalogItemType nType) const;
    BOOL                DeleteAllChildren   (void);
    BOOL                HasChildren         (void) const;

    BOOL                GetID               (GUID* pId) const;
    BOOL                SetID               (const GUID* pId);
    AcTc::AccessRight   GetAccessRight      (void) const;
    BOOL                SetAccessRight      (AcTc::AccessRight nAccessRight);
    BOOL                IsReadOnly          (void) const;
    int                 GetName             (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetName             (LPCTSTR pszString);
    int                 GetDescription      (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetDescription      (LPCTSTR pszString);
    int                 GetToolTipText      (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetToolTipText      (LPCTSTR pszString);
    INT_PTR             GetImageFilePath    (INT_PTR iIndex,
                                             LPTSTR pszString,
                                             size_t cchSize) const;    
    BOOL                GetHelpInfo         (LPTSTR pszFile, 
                                             LPTSTR pszCommand, 
                                             LPTSTR pszData) const;
    BOOL                SetHelpInfo         (LPCTSTR pszFile, 
                                             LPCTSTR pszCommand, 
                                             LPCTSTR pszData);
    int                 GetKeywords         (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetKeywords         (LPCTSTR pszString);
    int                 GetLinkUrl          (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetLinkUrl          (LPCTSTR pszString);
    int                 GetSourceUrl        (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetSourceUrl        (LPCTSTR pszString);
    int                 GetParentDocumentName(LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetParentDocumentName(LPCTSTR pszString);
    int                 GetParentDocumentDescription(LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetParentDocumentDescription(LPCTSTR pszString);
    int                 GetParentDocumentUrl(LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetParentDocumentUrl(LPCTSTR pszString);
    int                 GetPublisherName    (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetPublisherName    (LPCTSTR pszString);
    int                 GetPublisherDescription(LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetPublisherDescription(LPCTSTR pszString);
    int                 GetPublisherCountry (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetPublisherCountry (LPCTSTR pszString);
    int                 GetPublisherEmail   (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetPublisherEmail   (LPCTSTR pszString);
    int                 GetPublisherUrl     (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetPublisherUrl     (LPCTSTR pszString);
    int                 GetUrl              (LPTSTR pszString, 
                                             int cchSize) const;
    int                 GetLocalFile        (LPTSTR pszString, 
                                             int cchSize) const;
    AcTcCatalogItem *   GetRoot             (void) const;
    AcTcScheme      *   GetScheme           (void) const;
    AcTcCatalogItem *   GetParent           (void) const;
    BOOL                SetParent           (AcTcCatalogItem* pParent);
    BOOL                IsRoot              (void) const;
    BOOL                IsLink              (void) const;
    BOOL                IsLinkLoaded        (void) const;
    AcTcImageList   *   GetImageList        (void) const;
    AcTcImage       *   GetImage            (const SIZE* pSize,BOOL bUseDarkTheme=FALSE);
    int                 GetXml              (LPTSTR pszString, 
                                             int cchSize, 
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    virtual AcTcCatalogItem* FindInChildren (const GUID& id, 
                                             BOOL bRecursive = TRUE);
    AcTcCatalogItem *   FindInChildren      (LPCTSTR pszName);
    AcTcCatalogItem *   FindInChildren      (LPCTSTR pszName,
                                             BOOL bRecursive);
    BOOL                GetTime             (time_t* pCreated, 
                                             time_t* pLastModified, 
                                             time_t* pLastRefreshed) const;
    BOOL                SetTime             (const time_t* pCreated, 
                                             const time_t* pLastModified, 
                                             const time_t* pLastRefreshed);
    BOOL                CanRefresh          (void) const;
    BOOL                SetRefresh          (BOOL bRefresh);
    BOOL                GetRefresh          (void) const;
    virtual BOOL        Refresh             (DWORD dwRefreshFlag    = kRefreshAll);
    virtual BOOL        Download            (LPCTSTR pszUrl, 
                                             DWORD dwDownloadFlag  = kDownloadAll, 
                                             LPCTSTR pszDownloadPath        = NULL);
    BOOL                SetAutoRefresh       (BOOL bAutoRefresh);
    BOOL                GetAutoRefresh      (void) const;
    int                 GetReferencePath    (LPTSTR pszString, 
                                             int cchSize, 
                                             int nFlag) const;
    BOOL                SetReferencePath    (LPCTSTR pszString, 
                                             int nFlag);
    BOOL                GetCustomData       (IUnknown** ppCustomData);
    BOOL                SetNewID            (BOOL bRecursive = FALSE);
    BOOL                DeleteImageFile     (BOOL bRecursive = FALSE);
    int                 GetLinkFilePath     (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                DeleteLinkFile      (BOOL bRecursive = FALSE);
    BOOL                GetSourceID         (GUID* pId) const;
    BOOL                SetSourceID         (const GUID* pId);
    AcTcImage       *   GetOverlayImage     (BOOL bUseDarkTheme = FALSE) const;
    BOOL                SetOverlayImage     (const AcTcImage* pImage,BOOL bUseDarkTheme = FALSE);
    BOOL                GetOverlayImageInfo (ACTC_IMAGE_INFO* pImageInfo, BOOL bUseDarkTheme = FALSE) const;
    BOOL                SetOverlayImageInfo (const ACTC_IMAGE_INFO* pImageInfo);
    INT_PTR             GetOverlayImageFilePath(LPTSTR pszString, 
                                             size_t cchSize,
                                             BOOL bUseDarkTheme = FALSE) const;
    BOOL                DeleteOverlayImageFile(BOOL bRecursive = FALSE);
    INT_PTR             GetTargetProductCount(void) const;
    BOOL                GetTargetProduct    (INT_PTR iIndex,
                                             ACTC_TARGET_PRODUCT_INFO* pProductInfo) const; 
    INT_PTR             AddTargetProduct    (const ACTC_TARGET_PRODUCT_INFO* pProductInfo);
    BOOL                DeleteTargetProduct (int iIndex);
    BOOL                IsValidForProduct   (LPCTSTR pszProductName, 
                                             int nMajorVersion,
                                             int nMinorVersion,
                                             DWORD dwLocaleId = 0);
    BOOL                AddReactor          (AcTcCatalogItemReactor* pReactor);
    BOOL                RemoveReactor       (AcTcCatalogItemReactor* pReactor);
    BOOL                Sort                (int nSortOption,
                                             BOOL bRecursive);
    BOOL                SetItemOrder        (AcTcCatalogItem** pItems,
                                             INT_PTR nNumItems);
    AcTc::ItemOption    GetOption           (void) const;
    BOOL                SetOption           (AcTc::ItemOption nOption);
    // Revision
    BOOL                GetFileRevision     (long& lMajorVersion,
                                             long& lMinorVersion) const;
    BOOL                GetRevision         (long& lMajorVersion,
                                             long& lMinorVersion,
                                             long& lUserVersion) const;
    BOOL                IsUserModified      (void) const;

public:
    // Overridables
    virtual AcTcCatalogItem&    operator=   (const AcTcCatalogItem& srcItem);
    virtual BOOL        Reset               (void);

    virtual CatalogItemType GetType         (void) const;
    virtual int         GetTypeString       (LPTSTR pszString, 
                                             int cchSize,
                                             BOOL bLocalized    = FALSE, 
                                             BOOL bPluralForm   = FALSE) const;
    virtual int         GetTagName          (LPTSTR pszString, 
                                             int cchSize) const;

    virtual BOOL        Load                (IUnknown* pUnknown, 
                                             DWORD dwLoadOption = kLoadLinks);
    virtual BOOL        Load                (IStream* pStream, 
                                             DWORD dwLoadOption = kLoadLinks);
    virtual BOOL        Save                (IUnknown* pUnknown, 
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    virtual BOOL        Save                (IStream* pStream, 
                                             DWORD dwSaveOption = kSaveLinksAsLinks);
    virtual BOOL        Clone               (BOOL bDeep, 
                                             AcTcCatalogItem*& pClone,
                                             BOOL bCopyId = FALSE) const;
    virtual BOOL        CopyFrom            (const AcTcCatalogItem* pSrcItem, 
                                             BOOL bCopyId = FALSE);
    virtual BOOL        IsValidChild        (const CatalogItemType nType) const;

protected:
    // Overridables
    virtual AcTcCatalogItem * CreateObject  (void) const;

protected:
    // Protected constructor
    AcTcCatalogItem(AcTcSystemInternals*);
    
protected:
    void            *   mpImpObj;

private:
    friend class AcTcSystemInternals;
};


class ACTC_PORT AcTcCategory : public AcTcCatalogItem
{
public:
    AcTcCategory();
    AcTcCategory(const AcTcCategory& srcItem);
    virtual ~AcTcCategory();

protected:
    // Protected constructor
    AcTcCategory(AcTcSystemInternals*);
};


class ACTC_PORT AcTcCatalog : public AcTcCategory
{
public:
    AcTcCatalog();
    AcTcCatalog(const AcTcCatalog& srcItem);
    virtual ~AcTcCatalog();

protected:
    // Protected constructor
    AcTcCatalog(AcTcSystemInternals*);
};


class ACTC_PORT AcTcStockTool : public AcTcCatalogItem
{
public:
    AcTcStockTool();
    AcTcStockTool(const AcTcStockTool& srcItem);
    virtual ~AcTcStockTool();

    AcTcTool        *   CreateTool          (BOOL bSetDefaults = TRUE);

    BOOL                CreateAcadStockTool (IUnknown** ppStockTool);
    BOOL                CreateAcadTool      (IUnknown** ppUnknown);

    BOOL                GetComClassID       (CLSID& clsid) const;
    BOOL                SetComClassID       (const  CLSID& clsid);
    int                 GetModuleFileName   (LPTSTR pszString, 
                                            int cchSize) const;
    BOOL                SetModuleFileName   (LPCTSTR pszString);
    int                 GetModuleInstallUrl (LPTSTR pszString,
                                             int cchSize) const;
    BOOL                SetModuleInstallUrl (LPCTSTR pszString);
    int                 GetModuleInstallArguments(LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetModuleInstallArguments(LPCTSTR pszString);

protected:
    // Protected constructor
    AcTcStockTool(AcTcSystemInternals*);

private:
    friend class AcTcSystemInternals;
};


class  ACTC_PORT AcTcTool : public AcTcCatalogItem  
{
public:
    AcTcTool();
    AcTcTool(const AcTcTool& srcItem);
    virtual ~AcTcTool();

    virtual BOOL        Execute             (int nFlag, 
                                             HWND hWnd, 
                                             POINT point, 
                                             DWORD dwKeyState);
    BOOL                GetToolData         (IUnknown** ppUnknown);
    AcTcStockTool *     GetStockTool        (void) const;
    BOOL                CreateAcadTool      (IUnknown** ppTool, 
                                             BOOL bLoadData = TRUE);
    BOOL                GetStockToolID      (GUID* pId) const;
    BOOL                SetStockToolID      (const GUID* pId);
    int                 GetStockToolFileUrl (LPTSTR pszString, 
                                             int cchSize) const;
    BOOL                SetStockToolFileUrl (LPCTSTR pszString);
    ToolType            GetToolType         (void) const;
    BOOL                SetToolType         (ToolType nToolType);
    BOOL                IsFlyoutEnabled     (void) const;
    BOOL                EnableFlyout        (BOOL bUseFlyout);
    AcTcCatalogItem*    GetShapePackage     (void) const;
    BOOL                SetShapePackage     (AcTcCatalogItem* pPackage);
    AcTcTool*           GetCurrentShape     (void) const;
    BOOL                SetCurrentShape     (AcTcTool* pTool); 
    BOOL                SetCurrentShape     (const GUID& id); 
    BOOL                GetActiveShapes     (AcTcCatalogItem** pItems, 
                                             INT_PTR & nNumItems);
    BOOL                SetActiveShapes     (AcTcCatalogItem** pItems, 
                                             int nNumItems);
protected:
    // Protected constructor
    AcTcTool(AcTcSystemInternals*);
};


class ACTC_PORT AcTcPackage : public AcTcCatalogItem  
{
public:
    AcTcPackage();
    AcTcPackage(const AcTcPackage& srcItem);
    virtual ~AcTcPackage();

protected:
    // Protected constructor
    AcTcPackage(AcTcSystemInternals*);
};


class ACTC_PORT AcTcPalette : public AcTcPackage
{
public:
    AcTcPalette();
    AcTcPalette(const AcTcPalette& srcItem);
    virtual ~AcTcPalette();

protected:
    // Protected constructor
    AcTcPalette(AcTcSystemInternals*);
};


class ACTC_PORT AcTcCatalogItemReactor
{
public:
    virtual ~AcTcCatalogItemReactor(void);

    BOOL                Enable              (BOOL bEnable);
    BOOL                IsEnabled           (void) const;

    virtual void        ChildAdded          (AcTcCatalogItem* pChild);
    virtual void        ChildDeleted        (AcTcCatalogItem* pChild);
    virtual void        ChildDetached       (AcTcCatalogItem* pChild);

protected:
    void            *   mpImpObj;

protected:
    // Protected constructor
    AcTcCatalogItemReactor();

private:
    friend class AcTcSystemInternals;
};


//
// Global exported functions
//
ACTC_PORT BOOL AcTcInitialize   (void);
ACTC_PORT BOOL AcTcUninitialize (void);
ACTC_PORT AcTcManager* AcTcGetManager(void);
ACTC_PORT BOOL AcTcDownloadItem (LPCTSTR pszUrl, 
                                 AcTcCatalogItem*& pNewItem, 
                                 DWORD dwItemTypes      = -1,
                                 DWORD dwDownloadFlag   = kDownloadAll,
                                 LPCTSTR pszDownloadPath= NULL);
ACTC_PORT int AcTcDownloadItem  (LPTSTR* pUrls, 
                                 int nNumUrls, 
                                 AcTcCatalogItem** pItems, 
                                 DWORD dwItemTypes      = -1,
                                 DWORD dwDownloadFlag   = kDownloadAll, 
                                 LPCTSTR pszDownloadPath= NULL);
ACTC_PORT BOOL AcTcRefreshItem  (AcTcCatalogItem** pItems,
                                 int nNumItems,
                                 DWORD dwItemTypes      = -1,
                                 DWORD dwRefreshFlag    = kRefreshAll);
ACTC_PORT BOOL AcTcSort         (AcTcCatalogItem** pItems, 
                                 int nNumItems,
                                 int nSortOption);
ACTC_PORT BOOL AcTcSetHostInfo  (long lCurrentMajorVersion,
                                 long lCurrentMinorVersion,
                                 bool bBldEnv);
