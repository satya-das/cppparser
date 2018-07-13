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
#pragma once

#include "AcArray.h"
#include "AdAChar.h"
#include "gept3dar.h"
#include "dbid.h"
#include "AcString.h"
#include "acgi.h"

// ****************************************************************************
// Forward declarations
// ****************************************************************************

class AcGeMatrix3d;
class AcGePoint3d;
class AcGeVector3d;
class AcGePoint2d;

class AcGsModel;
class AcGsDevice;
class AcGsGraphicsKernel;
class AcGiVisualStyle;
class AcGiContextualColors;
class AcGiContextualAttributes;
struct AcGsClientViewInfo;
class AcGsRenderInterrupter;
class AcGsRenderProgressMonitor;

namespace Atil
{
    class Image;
};

// ****************************************************************************
// Helper classes
// ****************************************************************************

namespace GS
{
    // Error Codes
    enum ErrorStatus {
        kSuccess,
        kOutOfRange,
        kInvalidInput
    };

    enum DeviceType {
        kScreenDevice =         0,
        kOffScreenDevice =      1,
        kSelectionDevice =      2
    };

    enum HighlightStyle {
        kHighlightDashed =               0,
        kHighlightThicken =              1,
        kHighlightDashedAndThicken =     2,
        kHighlightCustom =               3,
        kHighlightDim =                  4,
        kHighlightThickDim =             5,
        kHighlightGlow =                 6
    };

    /// Sync behavior - defining if the request runs synchronously
    enum SyncBehavior
    {
        eSync               = 0,            /// The request runs  synchronously
        eAsync              = 1,            /// The request runs asynchronously
    };

    /// Image Properties - For screenshots, thumbnails...etc generated through Gs
    enum ImageOrientation
    {
        kTopDown            = 0,            //ATIL TopDownLeftRight
        kBottomUp           = 1             //ATIL BottomUpLeftRight
    };

    enum ImageDataFormat
    {
        kRGBA               = 0,
        kBGRA               = 1
    };
};

// copied (with modification) from limits.h to avoid extra #includes
#define SCALAR_MIN     (-2147483647 - 1) // minimum (signed) int value
#define SCALAR_MAX       2147483647      // maximum (signed) int value
#pragma pack (push, 8)

class AcGsDCPoint
{
public:
    enum            MaxFlag { Maximum };
    enum            MinFlag { Minimum };

                    AcGsDCPoint (void) { }
                    AcGsDCPoint (long xin, long yin) : x (xin), y (yin) { }

                    AcGsDCPoint (MaxFlag) { x = SCALAR_MAX; y = SCALAR_MAX; }
                    AcGsDCPoint (MinFlag) { x = SCALAR_MIN; y = SCALAR_MIN; }

    void            operator=   (MaxFlag) { x = SCALAR_MAX; y = SCALAR_MAX; }
    void            operator=   (MinFlag) { x = SCALAR_MIN; y = SCALAR_MIN; }

    void            operator=   (AcGsDCPoint const & r)              { x =  r.x;   y =  r.y; }
    bool            operator==  (AcGsDCPoint const & r) const { return x == r.x && y == r.y; }
    bool            operator!=  (AcGsDCPoint const & r) const { return x != r.x || y != r.y; }

    long            x;
    long            y;
};

class AcGsDCRect
{
public:
    enum            NullFlag { Null    };

                    AcGsDCRect (void) { }
                    AcGsDCRect (AcGsDCPoint const & min, AcGsDCPoint const & max)
                        : m_min (min)
                        , m_max (max) { }
                    AcGsDCRect (long l, long r, long b, long t)
                        : m_min (l,b)
                        , m_max (r,t) { }
                    AcGsDCRect (NullFlag) { set_null(); }

    AcGsDCRect &    operator= (AcGsDCRect const & other) {
                        m_min = other.m_min;
                        m_max = other.m_max;
                        return *this;
                    }
    void            operator|= (AcGsDCRect const & rightside) {
                        if (m_min.x > rightside.m_min.x)
                            m_min.x = rightside.m_min.x;
                        if (m_max.x < rightside.m_max.x)
                            m_max.x = rightside.m_max.x;

                        if (m_min.y > rightside.m_min.y)
                            m_min.y = rightside.m_min.y;
                        if (m_max.y < rightside.m_max.y)
                            m_max.y = rightside.m_max.y;
                    }
    void            operator&= (AcGsDCRect const & rightside) {
                        if (m_min.x < rightside.m_min.x)
                            m_min.x = rightside.m_min.x;
                        if (m_max.x > rightside.m_max.x)
                            m_max.x = rightside.m_max.x;

                        if (m_min.y < rightside.m_min.y)
                            m_min.y = rightside.m_min.y;
                        if (m_max.y > rightside.m_max.y)
                            m_max.y = rightside.m_max.y;

                        if (m_min.x > m_max.x || m_min.y > m_max.y)
                            *this = Null;
                    }
    bool            operator== (AcGsDCRect const & rightside) const {
                        return m_min == rightside.m_min &&
                               m_max == rightside.m_max;
                    }
    bool            operator!= (AcGsDCRect const & rightside) const {
                        return !(*this == rightside);
                    }

    void            set_null (void) {
                        m_min = AcGsDCPoint::Maximum;
                        m_max = AcGsDCPoint::Minimum;
                    }

    bool            is_null (void) const {// should be either valid or properly null
#ifdef ASSERT
                        ASSERT ((m_min.x <= m_max.x && m_min.y <= m_max.y) ||
                                (m_min == AcGsDCPoint::Maximum && m_max == AcGsDCPoint::Minimum));
#endif
                        return m_min.x > m_max.x;
                    }

    bool            within (AcGsDCRect const & rightside) const {
#ifdef ASSERT
                        ASSERT (!is_null());                        // (if *this is Null and rightside is not, does not work.
#endif
                        return m_min.x >= rightside.m_min.x &&      //  if *this is non-Null and right is Null, works.
                               m_min.y >= rightside.m_min.y &&      //  if both are Null, does not work.)
                               m_max.x <= rightside.m_max.x &&
                               m_max.y <= rightside.m_max.y;
                    }

    AcGsDCPoint     m_min;
    AcGsDCPoint     m_max;
};

struct AcGsColor
{
    unsigned char m_red;    // unicode safe
    unsigned char m_green;
    unsigned char m_blue;
    unsigned char m_filler;
};

typedef void *AcGsWindowingSystemID;      // i.e. -- HWND
typedef void *AcGsWindowId;               // Alias for AcGsWindowingSystemID


// ****************************************************************************
// AcGsNode
// ****************************************************************************

class AcGsNode
{
public:
    virtual ~AcGsNode() { }

    virtual AcGiDrawable *drawable       (void) const = 0;
};


// ****************************************************************************
// AcGsView
// ****************************************************************************

class AcGsView
{
public:

    enum Projection
    {
        kParallel,
        kPerspective
    };

    enum SelectionMode
    {
        kWindow,
        kCrossing,
        kFence,
        kWPoly,
        kCPoly,
    };

    enum DefaultLightingType
    {
        kOneLight,
        kTwoLights,
        kBackLight
    };

    enum ModelCloneOption
    {
        kCloneNoModels,
        kCloneMainPersistentModel,
        kCloneAllModels
    };

    virtual                    ~AcGsView            (void) { }

    // Who created this AcGsView?
    virtual AcGsGraphicsKernel &graphicsKernel(void)                                            = 0;

    // Viewport size & position in normalized device coords and screen coords
    //
    virtual void                setViewport         (const AcGePoint2d & lowerLeft,
                                                     const AcGePoint2d & upperRight)            = 0;
    virtual void                setViewport         (const AcGsDCRect  & screen_rect)           = 0;
    virtual void                getViewport         (      AcGePoint2d & lowerLeft,
                                                           AcGePoint2d & upperRight)  const     = 0;
    virtual void                getViewport         (      AcGsDCRect  & screen_rect) const     = 0;


    // Non-Rectangular Viewports
    //
    virtual void                setViewportClipRegion       (int                 contours,
                                                             int const *         counts,
                                                             AcGsDCPoint const * points)        = 0;
    virtual void                removeViewportClipRegion    (void)                              = 0;

    // Viewport Borders
    //
    virtual void                setViewportBorderProperties (AcGsColor const &   color,
                                                             int                 weight)        = 0;
    virtual void                getViewportBorderProperties (AcGsColor &         color,
                                                             int &               weight) const  = 0;

    virtual void                setViewportBorderVisibility (bool                bVisible)      = 0;
    virtual bool                isViewportBorderVisible     (void) const                        = 0;

    // View transformation
    //
    virtual void                setView             (const AcGePoint3d &  position,
                                                     const AcGePoint3d &  target,
                                                     const AcGeVector3d&  upVector,
                                                     double               fieldWidth,
                                                     double               fieldHeight,
                                                     Projection           projection = kParallel) = 0;

    virtual AcGePoint3d         position            (void) const            = 0;
    virtual AcGePoint3d         target              (void) const            = 0;
    virtual AcGeVector3d        upVector            (void) const            = 0;
    virtual bool                isPerspective       (void) const            = 0;
    virtual double              fieldWidth          (void) const            = 0;
    virtual double              fieldHeight         (void) const            = 0;

    // Clip Planes
    //
    virtual void                setEnableFrontClip  (bool enable)           = 0;
    virtual bool                isFrontClipped      (void) const            = 0;
    virtual void                setFrontClip        (double distance)       = 0;
    virtual double              frontClip           (void) const            = 0;

    virtual void                setEnableBackClip   (bool enable)           = 0;
    virtual bool                isBackClipped       (void) const            = 0;
    virtual void                setBackClip         (double distance)       = 0;
    virtual double              backClip            (void) const            = 0;

    // Matrix
    //
    virtual AcGeMatrix3d        viewingMatrix       (void) const            = 0;
    virtual AcGeMatrix3d        projectionMatrix    (void) const            = 0;
    virtual AcGeMatrix3d        screenMatrix        (void) const            = 0;
    virtual AcGeMatrix3d        worldToDeviceMatrix (void) const            = 0;
    virtual AcGeMatrix3d        objectToDeviceMatrix(void) const            = 0;

    // Drawables
    //
    virtual bool                add                 (AcGiDrawable * drawable,
                                                     AcGsModel    * model)    = 0;
    virtual bool                erase               (AcGiDrawable * drawable) = 0;
    virtual void                eraseAll            (void)                    = 0;

    // Validation
    //
    virtual void                invalidate          (void)                  = 0;
    virtual void                invalidate          (const AcGsDCRect &rect)= 0;
    virtual bool                isValid             (void) const            = 0;

    // Updates
    //
    virtual void                update              (void)                  = 0;
    virtual void                beginInteractivity  (double fFrameRateInHz) = 0;
    virtual void                endInteractivity    (void)                  = 0;
    virtual bool                isInteractive       (void) const            = 0;
    virtual void                flush               (void)                  = 0;

    // Degradation
    //
    virtual void                setMaximumUpgrade   (int step)              = 0;
    virtual int                 maximumUpgrade      (void)                  = 0;
    virtual void                setMinimumDegrade   (int step)              = 0;
    virtual int                 minimumDegrade      (void)                  = 0;

    // Visibility
    //
    virtual void                hide                (void)                  = 0;
    virtual void                show                (void)                  = 0;
    virtual bool                isVisible           (void)                  = 0;

    // Viewport visibility of layers
    //
    virtual void                freezeLayer         (Adesk::IntDbId layerID)      = 0;
    virtual void                thawLayer           (Adesk::IntDbId layerID)      = 0;
    virtual void                clearFrozenLayers   (void)                  = 0;

    // Logical View Control
    //

    /// <description>
    /// Notify graphics system that all view-independent viewport draw geometry is invalid and needs to be regenerated in this view.
    /// </description>
    virtual void                invalidateCachedViewportGeometry (void)     = 0;

    /// <description>
    /// Notify graphics system that viewport draw geometry for the specified AcGiDrawable is invalid and needs to be regenerated in this view.
    /// </description>
    /// <param name="pDrawable">Input the drawable that has invalid viewport draw graphics.</param>
    virtual void                invalidateCachedViewportGeometry(AcGiDrawable* pDrawable) = 0;

    // For client-friendly view manipulation
    //
    virtual void                dolly               (const AcGeVector3d & vector)   = 0;
    virtual void                dolly               (double x, double y, double z)  = 0;
    virtual void                roll                (double angle)                  = 0;
    virtual void                orbit               (double x, double y)            = 0;
    virtual void                zoom                (double factor)                 = 0;
    virtual void                zoomExtents         (const AcGePoint3d& minPoint,
                                                     const AcGePoint3d& maxPoint)   = 0;
    virtual void                zoomWindow          (const AcGePoint2d& lowerLeft,
                                                     const AcGePoint2d& upperRight) = 0;
    virtual void                pan                 (double x, double y)            = 0;

    virtual bool                pointInView         (const AcGePoint3d& pnt)        = 0;
    virtual bool                extentsInView       (const AcGePoint3d& minPoint,
                                                     const AcGePoint3d& maxPoint)   = 0;

    virtual AcGsView *          clone               (bool bCloneViewParameters = true,
                                                     bool bCloneGeometry       = false)  = 0;

    // Viewing limits
    //
    virtual bool                exceededBounds      (void)                          = 0;

    // Stereo
    //
    virtual void                enableStereo        (bool bEnable)                  = 0;
    virtual bool                isStereoEnabled     (void) const                    = 0;
    virtual void                setStereoParameters (double     magnitude,
                                                     double     parallax)           = 0;
    virtual void                getStereoParameters (double &   magnitude,
                                                     double &   parallax) const     = 0;

    // Off-screen Rendering
    //
    virtual void                getSnapShot         (Atil::Image       * pOutput,
                                                     AcGsDCPoint const & offset)    = 0;

    virtual bool                renderToImage       (Atil::Image* pOutput,
                                                     AcGiDrawable* pSettings,
                                                     AcGsRenderProgressMonitor* pProgressMonitor,
                                                     const AcGsDCRect & rectScreen,
                                                     bool bReuseScene = false)      = 0;

    // Device mapping
    virtual AcGsDevice *        getDevice(void) const = 0;

    // Visual Style
    virtual void                setVisualStyle      (const AcDbObjectId visualStyleId)      = 0;
    virtual AcDbObjectId        visualStyle         (void) const                            = 0;
    virtual void                setVisualStyle      (const AcGiVisualStyle &visualStyle)    = 0;
    virtual bool                visualStyle         (AcGiVisualStyle &visualStyle) const    = 0;

    // Background
    virtual void                setBackground       (const AcDbObjectId backgroundId)       = 0;
    virtual AcDbObjectId        background          (void) const                            = 0;

    // Default lighting
    virtual void                enableDefaultLighting (bool bEnable,
                                                       DefaultLightingType type = kTwoLights) = 0;

    virtual void                getNumPixelsInUnitSquare(const AcGePoint3d& givenWorldpt,          // Pixel information.
                                                               AcGePoint2d& pixelArea,
                                                               bool includePerspective = true) const = 0;

    // GS Model
    virtual AcGsModel*          getModel            (AcGiDrawable*) const                   = 0;
    virtual void                getModelList        (AcArray<AcGsModel*>&) const            = 0;

    virtual const               AcGsClientViewInfo& getClientViewInfo() const               = 0;

    // ************************************************************************
    // GSN additions
    // ************************************************************************
    virtual void                update              (GS::SyncBehavior sync) = 0;
    virtual bool                isPointInViewport   (const Adesk::Int32 x, const Adesk::Int32 y) = 0;
    virtual AcGsView *          clone               (bool bCloneViewParameters,
                                                     ModelCloneOption cloneOption)  = 0;
    virtual Atil::Image *       createSnapshot      (const AcGsDCPoint&     offset,
                                                     const AcGsDCRect&      imageDim,
                                                     GS::ImageDataFormat    format,
                                                     GS::ImageOrientation   orientation,
                                                     bool                   bOnlyCaptureRenderedImage = false)    = 0;

    enum EnableIRResult
    {
        kSuccess,
        kOutOfMemory
    };

    virtual EnableIRResult      beginInteractiveRender  (AcGsRenderProgressMonitor* pProgressMonitor) = 0;
    virtual void                endInteractiveRender    (void)                                        = 0;
    virtual bool                isRendering             (void) const                                  = 0;

    // Fast inteactivity status: 
    // trace some inteactivity behavior triggered by middle mouse zoom/pan with high frequency.
    virtual void                beginFastInteractivity   (void)            = 0;
    virtual bool                endFastInteractivity     (void)            = 0;// return if need update screen
    virtual bool                isFastInteractivity      (void)            = 0;                


};

// ****************************************************************************
// AcGsModel
// ****************************************************************************

class AcGsModel
{
public:

    enum RenderType
    {
        kMain,              // Use main Z-buffer
        kSprite,            // Use alternate Z-buffer, for sprites
        kDirect,            // Render into frame buffer without the z-test
        kHighlight,         // Render directly onto the device (skipping the frame buffer and the z-test)
        kHighlightSelection,// Render directly onto the device in selection highlight style (internal only)
        kDirectTopmost,     // Render above all other render types except contrast, and render without the z-test
        kContrast,          // Render directly onto the device in contrast style, for transients
        kCount              // Count of RenderTypes
    };

    enum InvalidationHint
    {
        kInvalidateNone,
        kInvalidateIsolines,
        kInvalidateViewportCache,
        kInvalidateAll,
        kInvalidateAllStatic,
        kInvalidateFacets,
        kInvalidateFills,
        kInvalidateLinetypes,
        kInvalidateMaterials,
        kInvalidateLayers,
        kInvalidateXrefs,
        kInvalidateRasterImages,
        kInvalidateAttributes,
        kInvalidateUnderlayFrame,
        kInvalidateLtScale,
        kInvalidateTransform,
        kInvalidateTransparencies,
        kInvalidateDrawableByView
    };

    enum OrderActionType
    {
        kMoveBelow,
        kMoveAbove,
        kSwapOrder,
    };

    virtual                    ~AcGsModel           (void) { }

    // Who created this AcGsModel?
    virtual AcGsGraphicsKernel &graphicsKernel(void)                            = 0;

    // Scene graph roots
    //
    virtual bool                addSceneGraphRoot   (AcGiDrawable * pRoot)      = 0;
    virtual bool                eraseSceneGraphRoot (AcGiDrawable * pRoot)      = 0;

    // Change notification
    //
    virtual void                onAdded             (AcGiDrawable * pAdded,
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onAdded             (AcGiDrawable * pAdded,
                                                     Adesk::IntDbId parentID)   = 0;

    virtual void                onModified          (AcGiDrawable * pModified,
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onModified          (AcGiDrawable * pModified,
                                                     Adesk::IntDbId parentID)   = 0;

    virtual void                onErased            (AcGiDrawable * pErased,
                                                     AcGiDrawable * pParent)    = 0;
    virtual void                onErased            (AcGiDrawable * pErased,
                                                     Adesk::IntDbId parentID)   = 0;

    virtual void                onPaletteModified   (void) = 0;

    // Transformations
    //
    virtual void                setTransform        (const AcGeMatrix3d &)      = 0;
    virtual AcGeMatrix3d        transform           (void) const                = 0;
    virtual void                setExtents          (const AcGePoint3d &,
                                                     const AcGePoint3d &)       = 0;

    // Invalidation notification
    //
    virtual void                invalidate          (InvalidationHint hint)     = 0;

    // View overrides
    //
    virtual void setViewClippingOverride (bool bOverride)      = 0;

    // Visual style
    //
    virtual void                setVisualStyle      (const AcDbObjectId visualStyleId)      = 0;
    virtual AcDbObjectId        visualStyle         (void) const                            = 0;
    virtual void                setVisualStyle      (const AcGiVisualStyle &visualStyle)    = 0;
    virtual bool                visualStyle         (AcGiVisualStyle &visualStyle) const    = 0;

    // Background
    virtual void                setBackground       (const AcDbObjectId backgroundId)       = 0;
    virtual AcDbObjectId        background          (void) const                            = 0;

    // Linetypes
    //
    virtual void                enableLinetypes     (bool bEnable)              = 0;
    virtual bool                linetypesEnabled    (void) const                = 0;

    // Sectioning
    //
    virtual void                setEnableSectioning      (bool enable)          = 0;
    virtual bool                isSectioningEnabled      (void) const           = 0;
    virtual bool                setSectioning            (const AcGePoint3dArray & pts,
                                                          const AcGeVector3d &     upVector) = 0;
    virtual bool                setSectioning            (const AcGePoint3dArray & pts,
                                                          const AcGeVector3d &     upVector,
                                                          double                   top,
                                                          double                   bottom)   = 0;
    virtual void                setSectioningVisualStyle (const AcDbObjectId visualStyleId)  = 0;

    // Render Type
    //
    virtual RenderType          renderType               (void)                     = 0;

    // Shadowing
    //
    virtual double              shadowPlaneLocation      (void) const               = 0;
    virtual void                setShadowPlaneLocation   (double planeLocationZ)    = 0;

    // Selection
    //
    virtual void                setSelectable            (bool bEnable)             = 0;
    virtual bool                selectable               (void) const               = 0;

    // ************************************************************************
    // GSN additions
    // ************************************************************************

    // Draw Order
    //
    virtual void                setDrawOrder             (AcGiDrawable*   pDrawable,
                                                          AcGiDrawable*   pRelativeDrawable,
                                                          AcGiDrawable*   pParent,
                                                          OrderActionType action)   = 0;

    // Bounds
    //
    virtual bool                bounds                   (const AcGiDrawable& drawable,
                                                          AcGePoint3d& minPt,
                                                          AcGePoint3d& maxPt) = 0;

    virtual void                onModified              (AcGiDrawable * pModified,
                                                         AcGiDrawable * pParent,
                                                         InvalidationHint hint)    = 0;
    virtual void                onModified              (AcGiDrawable * pModified,
                                                         Adesk::IntDbId  parentID,
                                                         InvalidationHint hint)   = 0;
    /// <description>
    /// Sets the unit scaling in meters per unit. This conversion scale is necessary for 
    /// any physical-based properties such as photometric lighting or real-world materials.
    /// </description>
    /// <param name="metersPerUnit">Input the unit scale in meters per unit.</param>
    virtual void                setUnitScale(double metersPerUnit) = 0;

    /// <description>
    /// Returns the unit scaling in meters per unit. This conversion scale is necessary for 
    /// any physical-based properties such as photometric lighting or real-world materials.
    /// </description>
    /// <returns>Returns the unit scale in meters per unit.</returns>
    virtual double              unitScale(void) const = 0;

    /// <description>
    /// Enables/disables photometric lighting.
    /// </description>
    /// <param name="bPhotometric">Input bool to control photometric lighting.</param>
    virtual void                setLightingPhotometric(bool bPhotometric) = 0;

    /// <description>
    /// Query photometric lighting status.
    /// </description>
    /// <returns>Returns true if photometric lighting is enabled.</returns>
    virtual bool                isLightingPhotometric(void) const = 0;

    /// <description>
    /// Enables/disables lights in blocks.
    /// </description>
    /// <param name="bPhotometric">Input bool to control lights in blocks.</param>
    virtual void                setLightsInBlocksEnabled(bool bEnabled) = 0;

    /// <description>
    /// Query lights in blocks status.
    /// </description>
    /// <returns>Returns true if lights in blocks are enabled.</returns>
    virtual bool                lightsInBlocksEnabled(void) const = 0;

};

// ****************************************************************************
// AcGsDevice
// ****************************************************************************

class AcGsDevice
{
public:

    enum RendererType
    {
        kDefault,
        kSoftware,
        kSoftwareNewViewsOnly,
        kFullRender,
        kSelectionRender,
        kFbxExportRender
    };

    virtual                    ~AcGsDevice          (void) { }

    // Who created this AcGsDevice?
    virtual AcGsGraphicsKernel &graphicsKernel(void)                        = 0;

    // Validation
    //
    virtual void                invalidate          (void)                  = 0;
    virtual void                invalidate          (const AcGsDCRect &rect)= 0;
    virtual bool                isValid             (void) const            = 0;

    // Updates
    //
    // Pass in a rectangle to know which region on the device was updated by the GS
    virtual void                update              (AcGsDCRect *pUpdatedRect = nullptr) = 0;

    // Change notification
    //
    virtual void                onSize              (int width, int height) = 0;
    virtual void                onRealizeForegroundPalette (void)           = 0;
    virtual void                onRealizeBackgroundPalette (void)           = 0;
    virtual void                onDisplayChange     (int nBitsPerPixel,
                                                     int nXRes,
                                                     int nYRes)             = 0;
    // View connections
    //
    virtual bool                add                 (AcGsView * view)       = 0;
    virtual bool                erase               (AcGsView * view)       = 0;
    virtual void                eraseAll            (void)                  = 0;

    virtual bool                setBackgroundColor  (AcGsColor color)       = 0;
    virtual AcGsColor           getBackgroundColor  (void)                  = 0;

    virtual void                setLogicalPalette   (const AcGsColor * palette,
                                                     int nCount)            = 0;
    virtual void                setPhysicalPalette  (const AcGsColor * palette,
                                                     int nCount)            = 0;

    // Off-screen Rendering
    virtual void                getSnapShot         (Atil::Image       * pOutput,
                                                     AcGsDCPoint const & offset) = 0;
    // Device Renderer type
    virtual void                setDeviceRenderer   (RendererType type)     = 0;
    virtual RendererType        getDeviceRenderer   (void)                  = 0;

    // Interruptible traversal
    virtual void                setRenderInterrupter(AcGsRenderInterrupter* pInterrupter) = 0;
    virtual AcGsRenderInterrupter* getRenderInterrupter(void) const = 0;
    virtual void                setDisplayUpdateSuppressed(bool bSuppressed) = 0;

    // *************************************************************************
    // GSN additions
    // *************************************************************************
    virtual void                invalidate          (AcGsModel::RenderType pane) = 0;
    virtual void                invalidate          (const AcGsDCRect &rect,
                                                     AcGsModel::RenderType pane) = 0;
    virtual void                update              (AcGsDCRect* pUpdatedRect, GS::SyncBehavior sync) = 0;
    virtual Atil::Image *       createSnapshot      (const AcGsDCPoint&     offset,
                                                     const AcGsDCRect&      imageDim,
                                                     GS::ImageDataFormat    format,
                                                     GS::ImageOrientation   orientation) = 0;

    // Maximum device size
    virtual int                 getMaxDeviceWidth  (void)                  = 0;
    virtual int                 getMaxDeviceHeight (void)                  = 0;

    // ************************************************************************
    // Below functions are for RapidRT Rendering.
    //

    //
    // Below four functions are device-related, should only exposed on GsDevice level.
    //
    virtual void                setDesiredFrameRate      (float frameRate)          = 0;
    virtual void                pauseInteractiveRender   (void)                     = 0;
    virtual void                resumeInteractiveRender  (void)                     = 0;
    virtual void                postRenderProgressCheckingReqeust()                 = 0;

    enum EnableIRResult
    {
        kSuccess,
        kOutOfMemory
    };
    //
    // Below three functions are both device and data relate, so exposed on GsDevice and GsView.
    //
    virtual EnableIRResult      beginInteractiveRender   (AcGsRenderProgressMonitor* pProgressMonitor) = 0;
    virtual void                endInteractiveRender     (void)                                        = 0;
    virtual bool                isRendering              (void) const                                  = 0;
    //
    // End of RapidRT
    // *************************************************************************

    // Text font kerning display setting
    virtual void                setFontKerningDisplay    (bool bDisplay)            = 0;
};


// ****************************************************************************
// AcGsConfig
// ****************************************************************************

class AcGsConfigReactor
{
public:
                 AcGsConfigReactor   (void) { }
    virtual     ~AcGsConfigReactor   (void) { }

    virtual void hardwareAccelerationWasModified(bool /*newValue*/) { }
    virtual void configWasModified              (void)          { }
    virtual void deviceSwitchToBegin            (void)          { }
    virtual void deviceSwitchHasEnded           (void)          { }
};

class AcGsConfig
{
protected:
    AcGsConfig(void) = default;    // pure virtual interface so only derived classes are allowed to make one

public:

    enum Handedness
    {
        kLeft,
        kRight
    };

    enum Quality
    {
        kLowQuality,
        kMediumQuality,
        kHighQuality
    };

    enum DegradationChannel
    {
        kViewportDraw,        // Viewport draw objects On to Off
        kLineAntialias,       // Line antialias On to Off
        kLighting,            // User lighting to Default lighting
        kTransparencyQuality, // Transparency quality High to Medium then Medium to Low
        kShadowsFull,         // Full Shadows to Ground Shadows
        kTransparency,        // Transparency On to Off
        kDiscardBackfaces,    // Discard Backfaces Off to On
        kShadowsGround,       // Ground Shadows to Shadows Off
        kEdgeStyles,          // Any Edge Style On to All Edge Styles Off
        kFacetEdges,          // Facet Edges to Isolines
        kFastSilhouette,      // Fast silhouettes On to Off
        kTextures,            // Textures On to Off
        kMaterials,           // Materials On to Off
        kLightingQuality,     // Lighting Quality Per-Vertex to Per-Face
        kBackgrounds,         // Backgrounds On to Off
        kIntersectEdges,      // Face Intersect Edges On to Off
        kFaceted,             // Faceted to Wireframe
        kWireframe,           // Wireframe to Bounding box
        kDegradationChannels
    };

    virtual                    ~AcGsConfig                      (void) = default;

    // dialog, read & write registry
    virtual bool                configure                       (void)                          = 0;
    virtual bool                showConfigDialog                (const wchar_t *strInput = nullptr) const = 0;

    // hardware & software drivers
    virtual void                driverName                      (ACHAR *pszPath,
                                                                 int nStrLen) const             = 0;
    virtual int                 driverVersion                   (void) const                    = 0;
    virtual int                 driverRevision                  (void) const                    = 0;
    virtual void                driverPath                      (ACHAR *pszPath,
                                                                 int    nStrLen) const          = 0;
    virtual void                setDriverPath                   (const ACHAR *pszPath)          = 0;

    virtual void                currentDisplayDriver            (ACHAR *pszPath,
                                                                 int    nPathStrLen,
                                                                 ACHAR *pszDriver,
                                                                 int    nDriverStrLen,
                                                                 bool  &bAccelerated) const     = 0;

    virtual void                hardwareAcceleratedDriver       (ACHAR *pszPath,
                                                                 int    nPathStrLen,
                                                                 ACHAR *pszDriver,
                                                                 int    nDriverStrLen) const    = 0;
    virtual void                setHardwareAcceleratedDriver    (const ACHAR *pszPath,
                                                                 const ACHAR *pszDriver)        = 0;

    virtual void                defaultHardwareAcceleratedDriver(ACHAR *pszPath,
                                                                 int    nPathStrLen,
                                                                 ACHAR *pszDriver,
                                                                 int    nDriverStrLen) const    = 0;
    virtual void                hardwareAcceleratedDrivers      (ACHAR  *pszPath,
                                                                 int     nPathStrLen,
                                                                 ACHAR **pszDrivers,
                                                                 int     nDrivers,
                                                                 int     nDriverStrLen)         = 0;
    virtual int                 numHardwareAcceleratedDrivers   (void)                          = 0;

    // level of detail & dynamic tessellation
    virtual void                setDynamicTessellation          (bool bDynamicTessellation)     = 0;
    virtual bool                dynamicTessellation             (void) const                    = 0;

    virtual GS::ErrorStatus     setMaxLODs                      (int nLevels)                   = 0;
    virtual int                 maxLODs                         (void) const                    = 0;

    virtual GS::ErrorStatus     setSurfaceTessellationTol       (int surfaceTessellationTol)    = 0;
    virtual int                 surfaceTessellationTol          (void) const                    = 0;

    virtual GS::ErrorStatus     setCurveTessellationTol         (int curveTessellationTol)      = 0;
    virtual int                 curveTessellationTol            (void) const                    = 0;

    // adaptive degradation
    virtual GS::ErrorStatus     setFrameRate                    (int nFramesPerSecond)          = 0;
    virtual int                 frameRate                       (void) const                    = 0;

    virtual void                setAdaptiveDegradation          (bool bAdaptiveDegradation)     = 0;
    virtual bool                adaptiveDegradation             (void) const                    = 0;

    virtual int                 degradationChainPosition        (DegradationChannel) const      = 0;
    virtual DegradationChannel  degradationChannelAt            (int position) const            = 0;
    virtual void                shiftDegradationChainPosition   (DegradationChannel,
                                                                 bool bShiftDown)               = 0;
    virtual void                setCanDegradeChannel            (DegradationChannel,
                                                                 bool bDegrade)                 = 0;
    virtual bool                canDegradeChannel               (DegradationChannel) const      = 0;

    // performance
    virtual void                setRedrawOnWindowExpose         (bool bRedrawWindowExpose)      = 0;  // internal use
    virtual bool                redrawOnWindowExpose            (void) const                    = 0;

    // display options
    virtual void                setHandedness                   (Handedness)                    = 0;
    virtual Handedness          handedness                      (void) const                    = 0;

    virtual void                setDiscardBackFaces             (bool bDiscardBackFaces)        = 0;
    virtual bool                discardBackFaces                (void) const                    = 0;

    virtual void                setTransparency                 (Quality quality)               = 0;
    virtual Quality             transparency                    (void) const                    = 0;

    virtual void                addReactor                      (AcGsConfigReactor *)           = 0;
    virtual void                removeReactor                   (AcGsConfigReactor *)           = 0;

    // ************************************************************************
    // GSN additions
    // ************************************************************************
    struct EffectStatus
    {
        const AcUniqueString* pUniqueString;            //Unique identifier for string
        AcString              effectName;               //Name of Effect
        int                   bEnabled;
        int                   bRecommended;
        int                   bAvailable;
        int                   nFeatureLevel;            //Minimum feature level required for effect
    };

    struct CertificationData
    {
        AcString              sCardName;                //Video Card Name
        AcString              sDriverVersion;           //Video Card Driver Version
        AcString              sProductDriverURL;        //URL to Autodesk Certification Site
        AcString              sTuningDate;              //Date of last tuning
        AcString              sDeviceFailed;            //List of failed devices
        int                   nHardwareFeatureLevel;    //Hardware supported feature level
        int                   nSoftwareFeatureLevel;    //Software supported feature level
        int                   nCertificationStatus;     //Certification Status
        int                   nHardwareID;              //Recommended HardwareID
    };

    enum EffectListType {
        kEL_Current,
        kEL_RegistryHardware,
        kEL_RegistrySoftware,
        kEL_File,
        kEL_HardwareEntry,
        kEL_HardwareBasic,
        kEL_HardwareAdvanced
    };

    // hardware features
    virtual AcArray<EffectStatus> *
                                getEffectList                    (EffectListType type) = 0;

    virtual bool                isFeatureEnabled                 (const AcUniqueString*) const  = 0;
    virtual void                setFeatureEnabled                (const AcUniqueString*,
                                                                  bool bEnable = true)          = 0;
    virtual int                 getFeatureVal                    (const AcUniqueString*) const  = 0;
    virtual void                setFeatureVal                    (const AcUniqueString*,
                                                                  int iVal = 0)                 = 0;
    virtual bool                isFeatureAvailable               (const AcUniqueString*) const  = 0;
    virtual bool                isFeatureRecommended             (const AcUniqueString*) const  = 0;
    virtual int                 getFeatureAvailableVal           (const AcUniqueString*) const  = 0;
    virtual int                 getFeatureRecommendedVal         (const AcUniqueString*) const  = 0;

    virtual void                setHardwareAcceleration          (bool bEnable)                 = 0;
    virtual bool                isHardwareAccelerationEnabled    (void)                         = 0;
    virtual bool                isHardwareAccelerationAvailable  (void)                         = 0;
    virtual bool                isHardwareAccelerationRecommended(void)                         = 0;
    virtual bool                isNoHardwareOverrideEnabled      (void)                         = 0;

    virtual CertificationData   getCertificationData             (void)                         = 0;
    virtual AcString            getVirtualDeviceName             (void)                         = 0;

    virtual void                setGenerateVertexNormals         (bool bEnable)                 = 0;
    virtual bool                generateVertexNormals            (void) const                   = 0;

    enum SpyglassType
    {
        kNone = 0,               
        kSoftware,
        kHardware
    };

    /// <description>
    /// Determine if the spyglass screen magnifer is available, and if so
    /// whether or not it's a hardware or software rendering implementation. 
    /// This is platform dependent feature not available for all platforms.
    /// </description>
    /// <returns>kNone, kSoftware, or kHardware</returns>
    virtual SpyglassType        spyglassType                     (void) const                   = 0;

    /// <description>
    /// Runtime Config if AA is disabled in Interactive mode (e.g. during Pan operation)
    /// This is platform dependent config only available for Web.
    /// </description>
    virtual bool                isAADisabledInInteractive        (void) const                   = 0;
    
    /// <description>
    /// Runtime Config if Level of details optimizations are enabled in retain mode in Interactive mode (e.g. during Pan operation)
    /// </description>
    virtual bool                isLODEnabledInRetainModeWhileInteractive        (void) const                   = 0;
    
};

// ****************************************************************************
// Access protocol for persistent drawables
// ****************************************************************************

typedef AcGiDrawable*    (* AcGsGetInterfaceFunc)            (Adesk::IntDbId objectId,
                                                              bool bNeedsValidation);   // does id need validation?
typedef void             (* AcGsReleaseInterfaceFunc)        (AcGiDrawable*);


// ****************************************************************************
// AcGsReactor
// ****************************************************************************

class AcGsReactor
{
public:
                                AcGsReactor                 (void) { }
    virtual                    ~AcGsReactor                 (void) { }

    enum ViewUpdateFlags        { kCameraChanged = 1 };

    virtual void                viewWasCreated              (AcGsView *)  { }
    virtual void                viewToBeDestroyed           (AcGsView *)  { }
    virtual void                viewToBeUpdated             (AcGsView *, int /*viewUpdateflags*/) { }
    virtual void                viewWasUpdated              (AcGsView *, int /*viewUpdateflags*/) { }
    virtual void                gsToBeUnloaded              (AcGsGraphicsKernel *) { }

    // ************************************************************************
    // GSN additions
    // ************************************************************************
    virtual void                viewInteractivityToBeChanged(const AcGsView *, bool /*interactive*/) { }
    virtual void                viewInteractivityWasChanged (const AcGsView *, bool /*interactive*/) { }
};

// ****************************************************************************
// AcGsModelReactor
// ****************************************************************************

class AcGsModelReactor
{
public:
                                AcGsModelReactor        (void)  { }
    virtual                    ~AcGsModelReactor        (void)  { }
    virtual bool                onSceneGraphRootAdded   (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pAdded*/)  { return true; }
    virtual bool                onSceneGraphRootErased  (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pErased*/) { return true; }
    virtual bool                onAdded                 (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pAdded*/,
                                                         AcGiDrawable * /*pParent*/)  { return true; }
    virtual bool                onAdded                 (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pAdded*/,
                                                         Adesk::IntDbId /*parentID*/) { return true; }
    virtual bool                onErased                (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pErased*/,
                                                         AcGiDrawable * /*pParent*/)  { return true; }
    virtual bool                onErased                (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pErased*/,
                                                         Adesk::IntDbId /*parentID*/) { return true; }
    virtual bool                onModified              (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pModified*/,
                                                         AcGiDrawable * /*pParent*/)  { return true; }
    virtual bool                onModified              (AcGsModel    * /*pModel*/,
                                                         AcGiDrawable * /*pModified*/,
                                                         Adesk::IntDbId /*parentID*/) { return true; }
};

// ****************************************************************************
// AcGsDrawablePath
// ****************************************************************************

struct AcGsDrawableLink
{
    Adesk::IntDbId id;
    AcGiDrawable *pDrawable;
    AcGsNode *pNode;
};

typedef AcArray<AcGsDrawableLink> AcGsDrawablePath;

// ****************************************************************************
// AcGsGraphicsKernel
// ****************************************************************************

struct AcGsClientViewInfo
{
    AcGsClientViewInfo()
        : viewportId(0)
        , acadWindowId(0)
        , viewportObjectId(0)
        , contextColors(nullptr)
        , contextualAttributes(nullptr) { }

    Adesk::LongPtr viewportId;                            // returned via AcGiViewport::viewportId()
    Adesk::LongPtr acadWindowId;                          // returned via AcGiViewport::acadWindowId()
    Adesk::IntDbId viewportObjectId;                      // returned via AcGiViewportDraw::viewportObjectId()
    AcGiContextualColors *contextColors;            // returned via AcGiViewport::contextualColors()
    AcGiContextualAttributes *contextualAttributes; // returned via AcGiViewport::contextualAttributes()

    AcDbObjectId viewportObjectAsObjectId() const;
};

//
// AcGsKernelDescriptor is used to describe the capabilities of
// a graphics kernel, or to specify the desired capabilities.
//
// Sample usage:
//      AcGsKernelDescriptor descriptor;
//      descriptor.addRequirement(AcGsKernelDescriptor::k3DDrawing);
//      requestKernel(descriptor);
//
//      const AcGsKernelDescriptor &descriptor = kernel.getDescriptor();
//      if (descriptor.supports(AcGsKernelDescriptor::k3DDrawing))
//          ...
//
#ifndef DRAWBRIDGE_API
#define DRAWBRIDGE_API __declspec(dllimport)
#endif // DRAWBRIDGE_API
class AcGsKernelDescriptor : public AcGiKernelDescriptor
{
public:
    // Used by a graphics kernel to define support for a given capability.
    void addSupport(const AcUniqueString *capability)     
    {
        if (capability)
            append(capability); 
    }

    // Used by a graphics kernel to make sure it supports what a client requires.
    bool requires(const AcUniqueString *capability) const 
    { 
        return capability ? contains(capability) : false; 
    }

    // Predefined capabilities.
    static DRAWBRIDGE_API const AcUniqueString *k2DDrawing;    // "2D Drawing"
    static DRAWBRIDGE_API const AcUniqueString *k3DDrawing;    // "3D Drawing"
    static DRAWBRIDGE_API const AcUniqueString *k3DSelection;  // "3D Selection"
    static DRAWBRIDGE_API const AcUniqueString *k3DRapidRTRendering;  // "RapidRT Rendering"
};

#ifdef __clang__
#define DRAWBRIDGE_MAC_API DRAWBRIDGE_API
#else
#define DRAWBRIDGE_MAC_API
#endif

/// <description>
/// This class is used in graphics system (GS) initialization and shutdown. 
/// The GS meta-API objects hide behind a pure virtual interface, and they 
/// are constructed via the AcGsGraphicsKernel.
/// </description>  
class DRAWBRIDGE_MAC_API AcGsGraphicsKernel : public AcGiGraphicsKernel
{
public:
                        AcGsGraphicsKernel   (void) : m_refCount(0) { }
    virtual            ~AcGsGraphicsKernel   (void) { }

    /// <description>
    /// Add a reference to this kernel.
    /// </description>
    DRAWBRIDGE_API void addRef               (void);

    /// <description>
    /// Delete a reference from this kernel.
    /// </description>
    /// <returns>True when the last reference is deleted.  The kernel is also deleted in this case.</returns>
    DRAWBRIDGE_API bool delRef               (void);

    /// <description>
    /// Determine if the kernel is compatible with the provided descriptor.
    /// </description>
    /// <param name="descriptor">Input the descriptor to examine.</param>
    /// <returns>True if the kernel is compatible with the descriptor, otherwise false.</returns>
    virtual bool        isCompatibleWith     (const AcGsKernelDescriptor &descriptor) const = 0;

    /// <description>
    /// Construct an AcGsModel of the specified RenderType.
    /// </description>
    /// <param name="type">Input render type.</param>
    /// <param name="databaseId">Input magic cookie with no meaning for the GS; it is returned to the caller in one of the AcGi query functions.</param>
    /// <param name="getFunc">Input pointer to a function used to transform persistent database IDs into AcGiDrawable pointers.</param>
    /// <param name="releaseFunc">Input pointer to a function which allows a persistent database to clean up any work performed by AcGsGetInterfaceFunc when the GS has finished with the drawable pointer.</param>
    /// <returns>The newly created model.</returns>
    virtual AcGsModel  *createModel          (AcGsModel::RenderType type, Adesk::IntDbId databaseId,
                                              AcGsGetInterfaceFunc getFunc, AcGsReleaseInterfaceFunc releaseFunc) = 0;

    /// <description>
    /// Delete an AcGsModel.
    /// </description>
    /// <param name="pModel">Input model to be deleted.</param>
    virtual void        deleteModel          (AcGsModel *pModel) = 0;

    /// <description>
    /// Construct an AcGsView. The first parameter includes magic cookies that are returned in 
    /// AcGiViewport::viewportId(), AcGiViewport::acadWindowId(), and AcGiViewportDraw::viewportObjectId() 
    /// (they don't have any other meaning to the GS). For the second parameter, pass in true if the 
    /// view will support layer visibility per view (such as modelspace viewports in layout mode).
    /// </description>
    /// <param name="pClientViewInfo">Input pointer to an AcGsClientViewInfo struct.</param>
    /// <param name="bEnableLayerVisibilityPerView">Input bool indicating whether view will support per view layer visibility.</param>
    /// <returns>The newly created view.</returns>
    virtual AcGsView   *createView           (const AcGsClientViewInfo * pClientViewInfo = nullptr,
                                              bool bEnableLayerVisibilityPerView = false) = 0;
    /// <description>
    /// Delete the specified AcGsView. Be sure this view has been erased from whatever device to which 
    /// it was added (if any). In addition, be sure that all drawables added to this view have been erased.
    /// </description>
    /// <param name="pView">Input view to be deleted.</param>
    virtual void        deleteView           (AcGsView *pView) = 0;

    /// <description>
    /// Construct an AcGsDevice corresponding to the specified AcGsWindowingSystemID and DeviceType.
    /// </description>
    /// <param name="id">Input window system ID.  On Windows this is an HWND.</param>
    /// <param name="deviceType">Input device type.</param>
    /// <returns>The newly created device.</returns>
    virtual AcGsDevice *createDevice         (AcGsWindowingSystemID id, GS::DeviceType deviceType = GS::kScreenDevice) = 0;

    /// <description>
    /// Construct an AcGsDevice that supports off-screen renderings.
    /// </description>
    /// <returns>The newly created offscreen device.</returns>
    virtual AcGsDevice *createOffScreenDevice(void) = 0;

    /// <description>
    /// Delete the specified AcGsDevice. Be sure to erase all added views before calling this method.
    /// </description>
    /// <param name="pDevice">Input device to be deleted.</param>
    virtual void        deleteDevice         (AcGsDevice *pDevice) = 0;

    /// <description>
    /// Retrieve a pointer to the singleton AcGsConfig object.
    /// </description>
    /// <returns>The singleton AcGsConfig object.</returns>
    virtual AcGsConfig *getConfig            (void) const = 0;

    /// <description>
    /// Add the specified AcGsReactor to the list of reactors that receive notifications of GS events.
    /// </description>
    /// <remarks>
    /// Do not delete the reactor before calling AcGsGraphicsKernel::removeReactor().
    /// </remarks>
    /// <param name="pReactor">Input AcGsReactor instance with implementations for those notifications of interest.</param>
    virtual void        addReactor           (AcGsReactor *pReactor) = 0;

    /// <description>
    /// Remove the specified AcGsReactor from the list of reactors that receive notifications of GS events.
    /// </description>
    /// <param name="pReactor">Input AcGsReactor to be removed when it no longer requires notification.</param>
    virtual void        removeReactor        (AcGsReactor *pReactor) = 0;

    /// <description>
    /// Add an AcGsModelReactor to receive notifications about the specified AcGsModel.
    /// </description>
    /// <param name="pModel">Input AcGsModel about which notifications will be received. </param>
    /// <param name="pReactor">Input AcGsModelReactor to add. </param>
    /// <remarks>
    /// If input AcGsModel value is not null, then the input AcGsModelReactor sends notifications about a particular AcGsModel. 
    /// If input AcGsModel value is null, then the input AcGsModelReactor sends notifications about all AcGsModels.
    /// </remarks>
    virtual void        addModelReactor      (AcGsModel *pModel, AcGsModelReactor *pReactor) = 0;

    /// <description>
    /// Remove an AcGsModelReactor to stop receiving notifications.
    /// </description>
    /// <param name="pModel">Input AcGsModel about which notifications were being received.</param>
    /// <param name="pReactor">Input AcGsModelReactor to remove. </param>
    virtual void        removeModelReactor   (AcGsModel *pModel, AcGsModelReactor *pReactor) = 0;

    /// <description>
    /// Associates a database with a model and render type.
    /// </description>
    /// <param name="databasePtr">Input pointer to database, cast as LONG_PTR.</param>
    /// <param name="pModel">Input pointer to model.</param>
    /// <param name="renderType">Input render type.</param>
    virtual void        associate            (Adesk::LongPtr databasePtr, AcGsModel *pModel, AcGsModel::RenderType renderType) = 0;

    /// <description>
    /// Finds a model for a given database and render type.
    /// </description>
    /// <param name="databasePtr">Input pointer to database cast as LONG_PTR.</param>
    /// <param name="renderType">Input render type.</param>
    /// <returns>The model associated with the database and render type.</returns>
    virtual AcGsModel*  find                 (Adesk::LongPtr databasePtr, AcGsModel::RenderType renderType) = 0;

protected:
    int m_refCount;
};

// ****************************************************************************
// AcGsRenderInterrupter
// ****************************************************************************

class AcGsRenderInterrupter
{
public:
    virtual bool interrupt(AcGsView* pView, AcGsModel::RenderType nType) = 0;
};

// ****************************************************************************
// AcGsRenderStatistics
// ****************************************************************************
/// <description>
/// A container for various statistics describing the data used to render an
/// image.
/// </description>
struct AcGsRenderStatistics
{
public:
    /// <description>
    /// The time it took to render the image, in seconds.
    /// </description>
    float fRenderTime;
  
    /// <description>
    /// The amount of memory in KB used by the renderer.
    /// </description>
    size_t iMemory;

    /// <description>
    /// The number of materials used to render the image.
    /// </description>
    size_t iMaterialCount;

    /// <description>
    /// The number of lights used to render the image.
    /// </description>
    size_t iLightCount;

    /// <description>
    /// The number of triangles used to render the image.
    /// </description>
    size_t iTriangleCount;
};

// ****************************************************************************
// AcGsRenderProgressMonitor
// ****************************************************************************
/// <description>
/// An interface implemented by a client of the AcGsView::renderToImage function
/// to get progress reports during the rendering process.
/// </description>
class AcGsRenderProgressMonitor
{
public:
    virtual ~AcGsRenderProgressMonitor() { }

    /// <description>
    /// The phases of the rendering process.  They are listed in sequential
    /// order from the first phase of rendering to the last phase.
    /// </description>
    enum Phase
    {
        /// <description>
        /// The scene translation phase, where AutoCAD entities are converted
        /// into a format suitable for rendering.
        /// </description>
        kTranslation,

        /// <description>
        /// The photon emission phase, which runs if global illumination is
        /// active in the render settings.
        /// </description>
        kPhotonEmission,

        /// <description>
        /// The final gathering phase, if final gathering is active in the
        /// render settings.
        /// </description>
        kFinalGather,

        /// <description>
        /// The normal rendering phase, which always happens.  Preview image
        /// tiles are generated during this phase only.
        /// </description>
        kRender,

        /// <description>
        /// This phase only happens when client's machine is relative low-end,
        /// and we will use tile rendering to resolve limited computer recourses.
        /// This phase is for generating tile preview for each tile before the
        /// normal rendering phase.
        /// </description>
        kDraft,

        /// <description>
        /// This the first stage of rendering, used for rendering initialization.
        /// </description>
        kInitialize,
    };

    /// <description>
    /// The status of the rendering process. 
    /// </description>
    enum RenderingStatus
    {
        /// <description>
        /// Current rendering process is running.
        /// </description>
        kRendering,

        /// <description>
        /// Current rendering process is paused.
        /// </description>
        kPaused,

        /// <description>
        /// Current rendering process is finished.
        /// </description>
		kFinished,

        /// <description>
        /// Current rendering process is canceled.
        /// </description>
		kAborted,

		/// <description>
		/// Won't start rendering, for current available memory does not meet rendering requirement.
		/// </description>
		kWillNotRender,

		/// <description>
		/// Current rendering is approaching out of memory situation, and rendering should be aborted.
		/// </description>
		kSoftOutOfMemory,

		/// <description>
		/// Memory allocation fails during rendering, and AutoCAD has to be restarted right now.
		/// </description>
		kHardOutOfMemory,

        /// <description>
        /// Current rendering process is aborted due to unknown errors.
        /// </description>
        kError,
    };

    /// <description>
    /// Called during the the rendering period to report the current rendering
    /// progress, which includes the rendering phase, overall rendering progress
    /// of the current phase, rendering time already spent, render level already
    /// achieved, and the progress of the current level. The last three parameters
    /// are only valid for rendering phase.
    /// </description>
    ///
    /// <param name="ePhase">
    /// The phase of rendering for which progress is being reported.
    /// </param>
    ///
    /// <param name="fOverallProgress">
    /// The percentage complete for the current rendering phase, as a floating-
    /// point number between 0.0 and 100.0.
    /// </param>
    ///
    /// <param name="iRenderTimeSpent">
    /// The time spent on rendering, which is measured by second.
    /// </param>
    ///
    /// <param name="iCurrentRenderLevel">
    /// The render level of rendering for which progress is being reported.
    /// </param>
    ///
    /// <param name="fCurrentLevelProgress">
    /// The percentage complete for the current render level, as a floating-
    /// point number between 0.0 and 100.0.
    /// </param>
    ///
    /// <param name="iTileIndex">
    /// This parameter only be valid when tile rendering is on, used to indicating
    /// which tile is being rendered.
    /// </param>
    ///
    /// <returns>
    /// The return value is only valid when called in AcGsView::renderToImage()
    /// function. Returning false means it's informing the caller to abort the
    /// current rendering. Or else, it will return true.
    /// </returns>
    ///
    /// <remarks>
    /// The implementation can use calls to this function to update a progress
    /// indicator.  It is recommended to be called at least once per second 
    /// during rendering.
    /// </remarks>
    virtual bool OnProgress(Phase ePhase,
                            float fOverallProgress,
                            int iRenderTimeSpent,
                            int iCurrentRenderLevel,
                            float fCurrentLevelProgress,
                            int iTileIndex = 0) = 0;

    /// <description>
    /// Called during the AcGsView::renderToImage() call to provide preview image
    /// tiles to the implementation.
    /// </description>
    ///
    /// <param name="x">
    /// The x-coordinate of the lower left corner of the image tile, in pixels.
    /// The lower left corner of the full image is (0,0).
    /// </param>
    ///
    /// <param name="y">
    /// The y-coordinate of the lower left corner of the image tile, in pixels.
    /// The bottom left corner of the full image is at (0,0).
    /// </param>
    ///
    /// <param name="w">
    /// The width of the image tile, in pixels.
    /// </param>
    ///
    /// <param name="h">
    /// The height of the image tile, in pixels.
    /// </param>
    ///
    /// <param name="pPixels">
    /// The image tile pixel data, as an array of bytes with four pixels per
    /// byte in BGRA order.  The size of the array is w * h * 4, and the first
    /// pixel in the array is at the bottom left corner of the image tile.
    /// </param>
    ///
    /// <remarks>
    /// This is only called during the render (kRender) phase.  The function is
    /// called twice for each tile: once before the tile is rendered to indicate
    /// the location and size of the upcoming tile (with parameter pPixels set
    /// to NULL) and again after the tile is rendered, with pixel data.  The
    /// implementation can use the first call to draw a preview bracket
    /// indicating where the tile will appear in the rendered image, and the
    /// second call to actually show the resulting tile.  It make seconds or
    /// even minutes to render each tile.  Each tile lies within the bounds of
    /// the output image.
    /// </remarks>
    virtual void OnTile(int x, int y, int w, int h, const unsigned char* pPixels) = 0;

    /// <description>
    /// Called to provide rendering status.
    /// </description>
    ///
    /// <param name="status">
    /// Status of current rendering process.
    /// </param>
    ///
    /// <remarks>
    /// This is called when status is changed.
    /// </remarks>
    virtual void OnStatusChanged(RenderingStatus status) = 0;

    /// <description>
    /// Called to provide rendering statistics to the implementation for the
    /// last rendered image.
    /// </description>
    ///
    /// <param name="pStats">
    /// A pointer to the statistics object containing information about the
    /// last rendered image.
    /// </param>
    ///
    /// <remarks>
    /// This is called after rendering is complete, and isn't called if
    /// rendering is aborted.
    /// </remarks>
    virtual void SetStatistics(const AcGsRenderStatistics* pStats) = 0;

    /// <description>
    /// Called to determine whether the database should be reused for the next
    /// rendered image.
    /// </description>
    ///
    /// <returns>
    /// The implementation should return true to reuse the rendering database
    /// for the next image.  If false is returned, the database is deleted.
    /// </returns>
    ///
    /// <remarks>
    /// This is called after rendering is completed, and isn't called if
    /// rendering is aborted.  This gives the implementation a chance to render
    /// the same scene without having to regenerate the rendering database,
    /// which is useful for animation where only the camera is changing.
    /// Only the camera will be updated if true is returned: all other data is
    /// reused for the next image.
    /// </remarks>
    virtual bool ShouldReuseDatabase() { return false; }

    /// <description>
    /// Called to determine whether the monitor is still eligible to receive notifications
    /// </description>
    /// <remarks>
    /// Can be used to terminate asynchronous rendering
    /// </remarks>
    virtual bool IsValid() { return true; }

    /// <description>
    /// Called to determine whether the rendering process is synchronous or asynchronous
    /// </description>
    /// <remarks>
    /// If async, renderToImage returns immediately.
    /// </remarks>
    virtual bool IsAsync() { return false; }

    /// <description>
    /// Output image is top-down by default.
    /// Called to determine whether the image should be bottom-up instead.
    /// </description>
    virtual bool IsOutputImageFlipped() { return false; }
};
#pragma pack(pop)
