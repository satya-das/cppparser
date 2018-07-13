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
//
// This is the Graphics Interface for view independent and dependent
// elaboration of AcDb Entities.
//
// The AutoCAD Graphics Interface (AcGi) is a set of objects comprising 
// an API for elaborating the graphics representation of new AutoCAD
// entitites.  These objects support many geometric primitives, 
// transformation matrix querying, and graphical attributes. 

#ifndef _ACGI_H
#define _ACGI_H 1

#include "adesk.h"

// Required for RX
//
#define ACGI_SERVICES  ACRX_T(/*MSG0*/"AcGiServices")

// Gcc not allow forward declaration of enum 
// I am moving some enum definitions to acgidefs.h
// So other header files can include that file instead of forward declaration.
#include "acgidefs.h"   

#include "rxobject.h"
#include "AdAChar.h"
#include "dbpl.h"
#include "gemat3d.h"
#include "gemat2d.h"
#include "gepnt2d.h"
#include "dbcolor.h"
#include "acdb.h"
#include "AcGiStyleAttributes.h"
#include "assert.h"
#include "AcGiParameter.h"
#include "PAL/api/charset.h"
#include "PAL/api/FontPitchAndFamily.h"

#pragma pack (push, 8)

struct AcGiSentScanLines 
{
    enum IsmRequestStatus {
        eOk,                           // No Failure.
        eInvalidInput,                 // unknown image organization
        eInvalidColorDepth,            // mColorDepth to big or too small for request
        eInvalidPixelRequest,          // IefAffine (matrix scaling) failed for some reason
        eInvalidDeliveryMethod,        // Frame buffer delivery + compression - not valid
        eNoValidCompressors,           // no compressors for image data
        eInsufficientMemory            // low memory conditions.. very bad 
    };

    Adesk::Int8 *    mpPixelBuffer;          // one pointer per scan line
    Adesk::UInt32    mRowBytes;              // number of bytes per scan line
    void *           mpImageId;              // image id ptr
    Adesk::Int16     mIsCancelled;           // boolean: user cancelled
    Adesk::Int16     mHasFailed;             // boolean: request failed
    Adesk::UInt32    mBytes;
    IsmRequestStatus mRequestStatus;

};



struct AcGiRequestScanLines 
{
    enum IEDitherMethod 
    {
        kIEAnyPalette,
        kCustomDithering,
        kCustomDitheringMethod
    };

    enum IEColorSystem
    {
        kBitonal,
        kCMY,
        kCMYK,
        kRGB
    };

    enum ImagePaletteType
    {
        kFromDevice,
        kFromIeWholeImage
    };

    AcGiRequestScanLines()
        : mImageOrg           (kAcGiBitonal)
        , mImageOrient        (kAcGiXLeftToRightTopFirst)
        , mPaletteType        (kFromDevice)
        , mScalingType        (kDefaultScale)
        , mScaleFilterType    (kDefaultScaleFilter)
        , mRotationFilterType (kDefaultRotationFilter)
    {
    }

    Adesk::UInt32       mPixelMinX = 0;         // requested pixel corners
    Adesk::UInt32       mPixelMinY = 0;
    Adesk::UInt32       mPixelMaxX = 0;
    Adesk::UInt32       mPixelMaxY = 0;
    AcGePoint2d         mLowerLeft;             // requested lower left corner
    AcGePoint2d         mUpperRight;            // requested upper right corner
    void *              mpImageId = nullptr;    // image handle
    AcGiImageOrg        mImageOrg;              // enum type: palette, RGB 
    AcGiImageOrient     mImageOrient;           // enum type
    Adesk::Int16        mWindowId = 0;          // acad window id
    Adesk::Int16        mColorDepth = 8;        // bits per pixel
    union {
        Adesk::Int16 mBackgroundIndex;
        Adesk::Int8 mBackgroundRGB[3];
    }                   mBackgroundColor;       // current background color
    union {
        Adesk::Int16 mTransparentIndex;
        Adesk::Int8 mTransparentRGB[3];
    } mTransparentColor;                        // current background color
    union {
        Adesk::Int16 mEntityIndex;
        Adesk::Int8 mEntityRGB[3];
    }                   mEntityColor;           // bitonal image foregrnd color
    Adesk::Int32        mPaletteIncarnation = 0; // unique palette indentifier
    Adesk::Int8 *       mpPalette = nullptr;    // pointer to 256 RGB triples
    Adesk::Int16        mIsDisplay = 0;         // boolean: TRUE=dsply, FALSE=hrdcpy
    double              mRasterRatio = 1.0;     // raster resolution
    AcGeMatrix2d        mPixelToDc;             // source pixel-to-dc transform
    ImagePaletteType    mPaletteType;
    void *              mpDataBuffer = nullptr;
    Adesk::Int32        mRowWidth = 0;
    Adesk::Int32        mNumRows;
    Adesk::Int32 const *mpBoundaryPoints = nullptr; // array of x,y pairs
    Adesk::UInt32       mnContours = 0;          // number of contours 
    Adesk::Int32 const *mpCounts = nullptr;      // pt count for each contour
    AcGiScaleType          mScalingType;
    AcGiScaleFilterType    mScaleFilterType;
    AcGiRotationFilterType mRotationFilterType;
    short                  mnTotalChunks = 0;   // how many chunks will be requested
    short                  mnThisChunk = 0;     // 1 based count of chunks
};

struct AcGiClipBoundary
{
    AcGeVector3d        m_vNormal;
    AcGePoint3d         m_ptPoint;
    AcGePoint2dArray    m_aptPoints;    

    AcGeMatrix3d        m_xToClipSpace;// Transformation from model to clip space
    AcGeMatrix3d        m_xInverseBlockRefXForm; // Xform from block space to world

    Adesk::Boolean      m_bClippingFront = false;
    Adesk::Boolean      m_bClippingBack = false;
    double              m_dFrontClipZ = 0.0;
    double              m_dBackClipZ = 0.0;

    Adesk::Boolean      m_bDrawBoundary= false ;
};

class OwnerDraw3d
{
public:
    virtual ~OwnerDraw3d(void) {};
};

// To be removed
enum AcGiColorIntensity 
{
    kAcGiMinColorIntensity = 0x0,
    kAcGiColorIntensity1   = 0x1,
    kAcGiColorIntensity2   = 0x2,
    kAcGiColorIntensity3   = 0x3,
    kAcGiColorIntensity4   = 0x4,
    kAcGiColorIntensity5   = 0x5,
    kAcGiColorIntensity6   = 0x6,
    kAcGiMaxColorIntensity = 0x7 
};

class AcGiColorRGB
{
public:
    AcGiColorRGB (void) 
        : red   (0.0)
        , green (0.0)
        , blue  (0.0)
    { }

    AcGiColorRGB (double r, double g, double b) 
        : red   (r)
        , green (g)
        , blue  (b)
    { }

    double red;
    double green;
    double blue;
};


inline AcGiColorRGB operator* (const AcGiColorRGB& c1, const AcGiColorRGB& c2)
{
    return AcGiColorRGB(c1.red   * c2.red, 
                        c1.green * c2.green, 
                        c1.blue  * c2.blue);
}

inline AcGiColorRGB operator* (const AcGiColorRGB& c, double s)
{
    return AcGiColorRGB(s * c.red, 
                        s * c.green, 
                        s * c.blue);
}

inline AcGiColorRGB operator* (double s, const AcGiColorRGB& c)
{
    return c * s;
}

inline AcGiColorRGB operator+ (const AcGiColorRGB& c1, const AcGiColorRGB& c2)
{
    return AcGiColorRGB(c1.red   + c2.red, 
                        c1.green + c2.green, 
                        c1.blue  + c2.blue);
}


class AcGiColorRGBA
{
public:
    AcGiColorRGBA (void)
        : red   (0.0)
        , green (0.0)
        , blue  (0.0)
        , alpha (1.0)
    { }

    AcGiColorRGBA (double r, double g, double b, double a) 
        : red   (r)
        , green (g)
        , blue  (b)
        , alpha (a)
    { }

    double red;
    double green;
    double blue;
    double alpha;
};

inline AcGiColorRGBA operator* (const AcGiColorRGBA& c1, const AcGiColorRGBA& c2)
{
    return AcGiColorRGBA(c1.red   * c2.red, 
                         c1.green * c2.green, 
                         c1.blue  * c2.blue, 
                         c1.alpha * c2.alpha);
}

inline AcGiColorRGBA operator*(const AcGiColorRGBA& c, double s)
{
    return AcGiColorRGBA(s * c.red, 
                         s * c.green, 
                         s * c.blue, 
                         s * c.alpha);
}

inline AcGiColorRGBA operator* (double s, const AcGiColorRGBA& c)
{
    return c * s;
}

inline AcGiColorRGBA operator+ (const AcGiColorRGBA& c1, const AcGiColorRGBA& c2)
{
    return AcGiColorRGBA(c1.red   + c2.red, 
                         c1.green + c2.green, 
                         c1.blue  + c2.blue, 
                         c1.alpha + c2.alpha);
}

class AcGiPixelBGRA32
{
public:
    AcGiPixelBGRA32 ()
    {
        m_bgra.b = 0;
        m_bgra.g = 0;
        m_bgra.r = 0;
        m_bgra.a = 255;
    }

    AcGiPixelBGRA32(Adesk::UInt32 bgra)
        : m_whole (bgra)
    { }

    AcGiPixelBGRA32 (Adesk::UInt8 blue,
                     Adesk::UInt8 green,
                     Adesk::UInt8 red,
                     Adesk::UInt8 alpha)
    {
        m_bgra.b = blue;
        m_bgra.g = green;
        m_bgra.r = red;
        m_bgra.a = alpha;
    }

    Adesk::UInt32     getBGRA   () const;
    Adesk::UInt32     getRGBA   () const;
    Adesk::UInt8      blue      () const;
    Adesk::UInt8      green     () const;
    Adesk::UInt8      red       () const;
    Adesk::UInt8      alpha     () const;

    void setBGRA    (Adesk::UInt32 bgra);
    void setBGRA    (Adesk::UInt8 blue, 
                     Adesk::UInt8 green, 
                     Adesk::UInt8 red,
                     Adesk::UInt8 alpha);
    void setRGBA    (Adesk::UInt32 rgba);
    void setRGBA    (Adesk::UInt8 red, 
                     Adesk::UInt8 green, 
                     Adesk::UInt8 blue,
                     Adesk::UInt8 alpha);
    void setBlue    (Adesk::UInt8 blue);
    void setGreen   (Adesk::UInt8 green);
    void setRed     (Adesk::UInt8 red);
    void setAlpha   (Adesk::UInt8 alpha);

private:
    union {
        Adesk::UInt32 m_whole;
#if defined(_ADESK_WINDOWS_)
        struct PIXEL{
#else
        // The GCC compiler requires the PIXEL struct to be anonymous as well.
        // I don't think we need the PIXEL struct identifier, so this should work.
        // If not, we'll have to provide a name for the union and update al the code
        // to use that name.
        //
        struct {
#endif
            Adesk::UInt8  b, g, r, a;
        }m_bgra;
    };
};

inline Adesk::UInt32 AcGiPixelBGRA32::getBGRA() const
{
    return m_whole;
}

inline Adesk::UInt32 AcGiPixelBGRA32::getRGBA() const
{
    return (Adesk::UInt32)(m_bgra.a)<<24 
           | (Adesk::UInt32)(m_bgra.b)<<16
           | (Adesk::UInt32)(m_bgra.g)<<8 
           | (Adesk::UInt32)(m_bgra.r);
}

inline Adesk::UInt8 AcGiPixelBGRA32::blue() const
{
    return m_bgra.b;
}

inline Adesk::UInt8 AcGiPixelBGRA32::green() const
{
    return m_bgra.g;
}

inline Adesk::UInt8 AcGiPixelBGRA32::red() const
{
    return m_bgra.r;
}

inline Adesk::UInt8 AcGiPixelBGRA32::alpha() const
{
    return m_bgra.a;
}

inline void AcGiPixelBGRA32::setBGRA(Adesk::UInt32 bgra)
{
    m_whole = bgra;
}

inline void AcGiPixelBGRA32::setBGRA(Adesk::UInt8 blue, 
                                     Adesk::UInt8 green, 
                                     Adesk::UInt8 red,
                                     Adesk::UInt8 alpha)
{
    m_bgra.b = blue;
    m_bgra.g = green;
    m_bgra.r = red;
    m_bgra.a = alpha;
}

inline void AcGiPixelBGRA32::setRGBA(Adesk::UInt32 rgba)
{
    m_bgra.r = (Adesk::UInt8)(rgba & 0x000000FF);
    m_bgra.g = (Adesk::UInt8)((rgba & 0x0000FF00) >> 8);
    m_bgra.b = (Adesk::UInt8)((rgba & 0x00FF0000) >> 16);
    m_bgra.a = (Adesk::UInt8)((rgba & 0xFF000000) >> 24);
}

inline void AcGiPixelBGRA32::setRGBA(Adesk::UInt8 red, 
                                     Adesk::UInt8 green, 
                                     Adesk::UInt8 blue,
                                     Adesk::UInt8 alpha)
{
    m_bgra.r = red;
    m_bgra.g = green;
    m_bgra.b = blue;
    m_bgra.a = alpha;
}

inline void AcGiPixelBGRA32::setBlue(Adesk::UInt8 blue)
{
    m_bgra.b = blue;
}

inline void AcGiPixelBGRA32::setGreen(Adesk::UInt8 green)
{
    m_bgra.g = green;
}

inline void AcGiPixelBGRA32::setRed(Adesk::UInt8 red)
{
    m_bgra.r = red;
}

inline void AcGiPixelBGRA32::setAlpha(Adesk::UInt8 alpha)
{
    m_bgra.a = alpha;
}

class AcGiImageBGRA32
{
public:
    AcGiImageBGRA32 ()
        : m_nImageWidth  (0)
        , m_nImageHeight (0)
        , m_pImageData   (NULL)
    { }

    AcGiImageBGRA32 (Adesk::UInt32 imageWidth, 
                     Adesk::UInt32 imageHeight, 
                     AcGiPixelBGRA32* imageData)
        : m_nImageWidth  (imageWidth)
        , m_nImageHeight (imageHeight)
        , m_pImageData   (imageData)
    { }

    AcGiPixelBGRA32* image  () const;
    Adesk::UInt32    width  () const;
    Adesk::UInt32    height () const;

    void setImage   (Adesk::UInt32 imageWidth, 
                    Adesk::UInt32 imageHeight, 
                    AcGiPixelBGRA32* imageData);

private:
    AcGiPixelBGRA32* m_pImageData;
    Adesk::UInt32 m_nImageWidth;
    Adesk::UInt32 m_nImageHeight;
};

inline AcGiPixelBGRA32* AcGiImageBGRA32::image() const
{
    return m_pImageData;
}

inline Adesk::UInt32 AcGiImageBGRA32::width() const
{
    return m_nImageWidth;
}

inline Adesk::UInt32 AcGiImageBGRA32::height() const
{
    return m_nImageHeight;
}

inline void AcGiImageBGRA32::setImage   (Adesk::UInt32 imageWidth, 
                                         Adesk::UInt32 imageHeight, 
                                         AcGiPixelBGRA32* imageData)
{
    m_nImageWidth   = imageWidth;
    m_nImageHeight  = imageHeight;
    m_pImageData    = imageData;
}

class AcGiSubEntityTraits;
class AcGiDrawableTraits;
class AcGiSubEntityTraitsImp;
class AcGiWorldGeometry;
class AcGiViewport;
class AcGiViewportGeometry;
class AcGiImpEdgeData;
class AcGiImpFaceData;
class AcGiImpVertexData;
class AcGiImpTextStyle;
class AcGiImpPolyline;
class AcGiTextStyle;
class AcGiEdgeData;
class AcGiFaceData;
class AcGiVertexData;
class OwnerDraw;
class AcGiImpVariant;
class AcGiVariant;
class AcGiContextImp;
class AcGiContext;
class AcGiCommonDraw;
class AcGiGeometry;
class AcCmEntityColor;
struct TextParams;
struct FontInfo;
class AcGiMapper;
class AcGiViewportTraits;
class AcGiVisualStyleTraits;
class AcGiContextualColors;
class AcGiGdiDrawObject;
class AcGiImpHatchPatternDefinition;
class AcGiImpHatchPattern;
class AcGiFill;
class AcGiImpFill;
class AcGiImpGradientFill;
class AcUniqueString;
class AcFontHandle;

typedef void (*AcGiWorldSegmentCallback)(const AcGePoint3d *);

bool acgiIsValidClipBoundary(const AcGePoint2dArray& pts);

Acad::ErrorStatus acgiGetRegenBlockRefStack(AcDbObjectIdArray& blkRefs);

class AcGiVariant : public AcRxObject
//
// Class for handling variant data
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiVariant);

    AcGiVariant(void);
    virtual ~AcGiVariant(void);

    AcGiVariant             (const AcGiVariant & value);
    AcGiVariant & operator= (const AcGiVariant & value);
    virtual bool  operator==(const AcGiVariant & value) const;
        // note that a variant copy is a deep copy. If describing a hierarchical
        // data structure, the entire structure is duplicated

    // AcRxObject protocol
    virtual Acad::ErrorStatus copyFrom(const AcRxObject* other) override;


    enum VariantType
    {
        kUndefined = 0,
        kBoolean,
        kInt,
        kDouble,
        kColor,
        kString,
        kTable,
    };

    class EnumType
    {
    public:
        explicit EnumType (int value) : m_value(value) { }
        
        template <typename T>
        operator T () { return static_cast<T>(m_value); }

        template <typename T>
        bool operator== (T right) const { return static_cast<int>(right) == m_value; }

        template <typename T>
        bool operator!= (T right) const { return !(*this == right); }

    protected:    
        int m_value;
    };

    AcGiVariant(bool);
    AcGiVariant(Adesk::Int32);
    AcGiVariant(double);
    AcGiVariant(const AcCmColor&); 
    AcGiVariant(const ACHAR *); 

    VariantType type() const;

    void                set(bool);
    void                set(Adesk::Int32);
    void                set(double);
    void                set(const AcCmColor&); 
    void                set(const ACHAR *); 

    bool                asBoolean() const;
    int                 asInt() const;
    double              asDouble() const;
    AcCmColor           asColor() const;
    AcString            asString() const;    

    ACDBCORE2D_PORT float               asFloat() const;
    ACDBCORE2D_PORT char                asChar() const;
    ACDBCORE2D_PORT unsigned char       asUchar() const;
    ACDBCORE2D_PORT short               asShort() const;
    ACDBCORE2D_PORT unsigned short      asUshort() const;
    ACDBCORE2D_PORT unsigned int        asUint() const;
    ACDBCORE2D_PORT Adesk::Int32        asLong() const;
    ACDBCORE2D_PORT Adesk::UInt32       asUlong() const;
    ACDBCORE2D_PORT EnumType            asEnum() const;


    // table access..
    Acad::ErrorStatus   getElem(const ACHAR * pKey, AcGiVariant & value) const;
    const AcGiVariant*  getElem(const ACHAR * pKey) const;
    void                setElem(const ACHAR * pKey, const AcGiVariant&);
    void                deleteElem(const ACHAR * pKey);

    int                 getElemCount() const;
    //
    ACDBCORE2D_PORT Acad::ErrorStatus getElemAt(int nIndex, AcString &, AcGiVariant &) const;
    // Deprecated. Caller is responsible for deleting returned ACHAR*
    Acad::ErrorStatus   getElemAt(int nIndex, ACHAR*&, AcGiVariant &) const;    // deprecated
    ACDBCORE2D_PORT AcGiVariant*      getElemAt(int nIndex, AcString &) const;
    // Deprecated. Caller is responsible for deleting returned ACHAR*
    AcGiVariant*        getElemAt(int nIndex, ACHAR*&) const;   // deprecated

    static bool         isEquivalent(const AcGiVariant*, const AcGiVariant*);

private:
    AcGiImpVariant * mpAcGiImpVariant;
};

// Deprecated - please use AcString-based overload
// caller is responsible for deleting returned ACHAR*
inline Acad::ErrorStatus AcGiVariant::getElemAt(int nIndex, ACHAR*&pStr, AcGiVariant &var) const
{
    AcString sElem;
    const Acad::ErrorStatus es = this->getElemAt(nIndex, sElem, var);
    if (es != Acad::eOk)
        pStr = nullptr;
    else
        ::acutNewString(sElem.constPtr(), pStr);
    return es;
}
inline AcGiVariant * AcGiVariant::getElemAt(int nIndex, ACHAR*&pStr) const
{
    AcString sElem;
    AcGiVariant *pVar = this->getElemAt(nIndex, sElem);
    ::acutNewString(sElem.constPtr(), pStr);
    return pVar;
}
template <typename T>
inline bool operator== (T left, const AcGiVariant::EnumType right)
{
    return (right == left);
}

template <typename T>
inline bool operator!= (T left, const AcGiVariant::EnumType right)
{
    return (right != left);
}

//
// AcGiKernelDescriptor is used to describe the capabilities of
// a graphics kernel, or to specify the desired capabilities.
//
// Sample usage:
//      const AcGiKernelDescriptor &descriptor = context()->kernel.getDescriptor();
//      static const AcUniqueString *kRequestedFeature = AcUniqueString::Intern(L"Requested Feature");
//      if (descriptor.supports(kRequestedFeature))
//          ...
//
// The default graphics kernel supports nothing.
class AcGiKernelDescriptor : public AcArray<const AcUniqueString *>
{
public:
    // Require support for a given capability.
    void addRequirement(const AcUniqueString *capability) 
    { 
        if (capability != nullptr)
            append(capability); 
    }

    // Query support for a given capability.
    bool supports(const AcUniqueString *capability) const 
    {
        return capability ? contains(capability) : false;
    }

    bool supports(const AcGiKernelDescriptor& desc) const
    {
        int len = desc.length();
        for (int i=0; i<len; i++)
        {
            if (!contains(desc[i]) && desc[i] != nullptr)
                return false;
        }
        return true;
    }
};

class AcGiGraphicsKernel
{
public:
    virtual ~AcGiGraphicsKernel() { }
    virtual const AcGiKernelDescriptor &getDescriptor(void) const { return m_descriptor; }

private:
    AcGiKernelDescriptor m_descriptor;
};

#pragma warning (push)
#pragma warning (disable : 4100)        // unreferenced formal parameter

class AcGiContext : public AcRxObject
    //
    // The base class for drawing contexts
    //
{
public:
    ACRX_DECLARE_MEMBERS(AcGiContext);

    virtual Adesk::Boolean   isPsOut() const = 0;
    virtual Adesk::Boolean   isPlotGeneration() const = 0;
    virtual AcDbDatabase    *database() const = 0;
    virtual bool             isBoundaryClipping() const = 0;

    // Which kernel is implementing this AcGi interface? The descriptor is very useful.
    // The default implementation is a kernel that supports nothing.
    virtual class AcGiGraphicsKernel &graphicsKernel() { static AcGiGraphicsKernel kernel; return kernel; }

    // If your object requires to be redrawn for translation
    // transforms (MOVE) you can force the system to rerequest 
    // graphics for all objects in the current drag, including
    // yourself. Use this option only if you really need to. 
    // E.g. If your object needs to update for each step in a 
    // MOVE drag
    // 
    virtual void             disableFastMoveDrag() const { }

    // Returns false if this is root level entity, e.g. a line in modelspace
    // and true if the object is contained within another object like a
    // block for example.
    //
    virtual bool isNesting() const { return false; }

    virtual AcCmEntityColor  effectiveColor()         const { return AcCmEntityColor(); }
    virtual AcDb::LineWeight byBlockLineWeight()      const { return AcDb::kLnWt000; }
    virtual AcDbObjectId     byBlockPlotStyleNameId() const { return AcDbObjectId::kNull; }
    virtual AcDbObjectId     byBlockMaterialId()      const { return AcDbObjectId::kNull; }

    virtual bool supportsTrueTypeText()    { return false; }
    virtual bool supportsOwnerDraw()       { return false; }
    virtual bool supportsFillTrait() const { return false; }

    /// <description>
    /// Indicate whether or not the backend driver supports fast AcGiRenderBuffer.
    /// </description>
    /// <remarks>
    /// Note that just because render buffer is supported doesn't mean it will be fast and cached on the hardware. 
    /// Driver memory and other runtime factors also play a role. This method, however, lets you determine if 
    /// you are using software renderer or another driver that will never draw fast renderBuffers.
    /// </remarks>
    /// <returns>True if fast render buffers supported, false otherwise.</returns>
    virtual Adesk::Boolean  supportsFastRenderBuffer() const { return Adesk::kFalse; }

    /// <description>
    /// Indicate whether or not the backend driver supports native AcGiPointCloud.
    /// </description>
    /// <returns>True if native point clouds supported, false otherwise.</returns>
    virtual Adesk::Boolean  supportsNativePointCloudRender() const { return Adesk::kFalse; }

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    // These APIs is provided for internal use only, do not use them
    // in external applications
    //
    virtual AcGiContextImp *getImpPtr() { return nullptr; }
    virtual const AcGiContextImp *getConstImpPtr() const { return nullptr; }
    //
    // End of Internal use only API
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////

protected:

    friend class AcGiTextHook;
    friend class CShFont;
    friend class AcDbImpText;

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    // These APIs is provided for internal use only, do not use them
    // in external applications
    //
    virtual AcGiWorldSegmentCallback wSegTaker() const { return nullptr; }
    virtual int getTrueTypeBoundingBox(AcGePoint3d const & /*location*/,
                                       const wchar_t * /*text*/, 
                                       int /*length*/, TextParams const * /*tp*/, 
                                       AcGePoint3d * /*bbox*/, float * /*char_widths*/) { return 0; }
    
    virtual int getTrueTypeTextExtents(ACHAR const *, Charset, double,
                                       int, int,
                                       int, short, short, double, double,
                                       AcGePoint2d &,AcGePoint2d &) { return -1; }

    virtual int setTrueTypeTransform(const AcGePoint3d &,const AcGeVector3d &,
                                     double, double, double, bool, bool) { return 0; }

    virtual int drawTrueTypeText(const ACHAR *,double,int,bool,
                                 const TextParams &,Charset) { return 0; }
    virtual int restoreTrueTypeTransform() { return 0; }
    virtual void bypassHiddenLineRemoval() { }
    virtual int setTextStyle(int);
    virtual AcFontHandle* loadTrueTypeFont(const ACHAR *, bool, bool, Charset, int, FontInfo &) { return nullptr; }
    //
    // End of Internal use only API
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
};

class AcGiCommonDraw : public AcRxObject
//
// The base class for drawing contexts
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiCommonDraw);
    virtual AcGiRegenType        regenType() const = 0;
    virtual Adesk::Boolean       regenAbort() const = 0;
    virtual AcGiSubEntityTraits &subEntityTraits() const = 0;
    virtual AcGiGeometry        *rawGeometry() const = 0;
    virtual Adesk::Boolean       isDragging() const = 0;

    // This function operates against the current active viewport
    //
    virtual double               deviation(const AcGiDeviationType, 
                                           const AcGePoint3d &) const = 0;
    virtual Adesk::UInt32        numberOfIsolines() const = 0;
    
    virtual AcGiContext         *context() = 0;

    virtual bool                 secondaryCall() const { return false; }
};

class AcGiWorldDraw: public AcGiCommonDraw
//
// This class provides an API for generating graphics
// in model coordinates.  These graphics cannot be
// controlled by any viewport, as can AcGiViewportDraw.
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiWorldDraw);
    virtual AcGiWorldGeometry&      geometry() const = 0;
};

class AcGiViewportDraw: public AcGiCommonDraw 
//
// This class provides an API for generating graphics
// that can be sent to a particular viewport.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportDraw);
    virtual AcGiViewport&        viewport() const = 0;
    virtual AcGiViewportGeometry& geometry() const = 0;
    virtual Adesk::UInt32        sequenceNumber() const = 0;
    // why is the following method's arg const?
    virtual Adesk::Boolean       isValidId(const Adesk::ULongPtr acgiId) const =0;
    virtual AcDbObjectId         viewportObjectId() const = 0;
};

class AcGiViewport: public AcRxObject 
//
// This class returns viewport info.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewport);

    // Get various view transformations.
    //
    virtual void getModelToEyeTransform(AcGeMatrix3d&) const = 0;
    virtual void getEyeToModelTransform(AcGeMatrix3d&) const = 0;
    virtual void getWorldToEyeTransform(AcGeMatrix3d&) const = 0;
    virtual void getEyeToWorldTransform(AcGeMatrix3d&) const = 0;

    // Perspective information.
    //
    virtual Adesk::Boolean isPerspective() const = 0;
    virtual Adesk::Boolean doPerspective(AcGePoint3d&) const = 0;
    virtual Adesk::Boolean doInversePerspective(AcGePoint3d&) const = 0;

    // Pixel information.
    //
    virtual void getNumPixelsInUnitSquare(const AcGePoint3d& givenWorldpt,
                                  AcGePoint2d& pixelArea,
                                  bool includePerspective = true) const = 0;

    // Camera information.
    //
    virtual void getCameraLocation(AcGePoint3d& location) const = 0;
    virtual void getCameraTarget(AcGePoint3d& target) const = 0;
    virtual void getCameraUpVector(AcGeVector3d& upVector) const = 0;

    // Viewport information.
    //
    virtual Adesk::ULongPtr viewportId() const = 0;
    virtual Adesk::Int16  acadWindowId() const = 0;
    virtual void getViewportDcCorners(AcGePoint2d& lower_left,
                                      AcGePoint2d& upper_right) const = 0;

    // Clipping
    //
    virtual Adesk::Boolean getFrontAndBackClipValues(Adesk::Boolean& clip_front,
                                         Adesk::Boolean& clip_back,
                                         double& front,
                                         double& back) const = 0;

    // The factor returned here affects the linetype scaling in this viewport
    // 1.0 is the default. Returning a value of 2 will ensure
    // that the pattern is twice as big as per default.
    //
    virtual double linetypeScaleMultiplier() const = 0;

    // If the calculated total pattern length of a linetyped object is less
    // than this (value in drawing units). Then a continuous pattern is used
    // instead. Several factors affect the linetype pattern length.
    // linetypeScaleMultiplier() is one of them. Note: If you set this value
    // high you could completely prevent the use of linetypes.
    //
    virtual double linetypeGenerationCriteria() const = 0;

    // Returns true if the layer is not frozen in this viewport and not globally
    // frozen. Indicating that geometry on this layer should be regenerated.
    //
    virtual Adesk::Boolean layerVisible(const AcDbObjectId & /*idLayer*/) const { return Adesk::kTrue; }

    virtual AcGeVector3d viewDir() const { return AcGeVector3d::kZAxis; }

    // Provides access to color information that is context-sensitive.
    //
    virtual const AcGiContextualColors* contextualColors() const { return NULL; }
};

class AcGiContextualColors : public AcRxObject
{
//
// This class returns color information for objects that can have different colors
// in different display contexts.
//
public:
    ACRX_DECLARE_MEMBERS(AcGiContextualColors);

    // Access to colors.
    virtual Adesk::UInt32 gridMajorLines() const = 0;
    virtual Adesk::UInt32 gridMinorLines() const = 0;
    virtual Adesk::UInt32 gridAxisLines() const = 0;
    virtual int gridMajorLineTintXYZ() const = 0;
    virtual int gridMinorLineTintXYZ() const = 0;
    virtual int gridAxisLineTintXYZ() const = 0;

    virtual Adesk::UInt32 lightGlyphs() const = 0;
    virtual Adesk::UInt32 lightHotspot() const = 0;
    virtual Adesk::UInt32 lightFalloff() const = 0;
    virtual Adesk::UInt32 lightStartLimit() const = 0;
    virtual Adesk::UInt32 lightEndLimit() const = 0;

    virtual Adesk::UInt32 cameraGlyphs() const = 0;
    virtual Adesk::UInt32 cameraFrustrum() const = 0;
    virtual Adesk::UInt32 cameraClipping() const = 0;

    // Access to context parameters.
    virtual void setContextFlags(Adesk::UInt32 flg, bool set = true) = 0;
    virtual bool flagsSet(Adesk::UInt32 flg) const = 0;
};


class AcGiContextualColors2 : public AcGiContextualColors
{
//
// This class returns color information for objects that can have different colors
// in different display contexts.  This class also includes the web mesh color 
// for photometric lights.
//
public:
    ACRX_DECLARE_MEMBERS(AcGiContextualColors2);

    virtual AcCmColor webMeshColor       (void) const = 0;
    virtual AcCmColor webMeshMissingColor(void) const = 0;
    virtual AcCmColor lightShapeColor    (void) const = 0;
    virtual AcCmColor lightDistanceColor (void) const = 0;
};


/* AutoCAD reserves a block of 64K marker ids for custom use. The range from INT_MIN thu INT_MIN+65535
   Callers of setSelectionMarker should not use this range except for the values below.
   The value of 0 has special meaning and indicates no selection marker.
*/
#define AcGiSelectionMarkerACADReserveStart         (-2147483647 - 1)   // INT_MIN without using limits.h
#define AcGiSelectionMarkerACADReserveEnd           (AcGiSelectionMarkerACADReserveStart + 65535)

#define AcGiSelectionMarkerACADSelectionPreviewOff  (AcGiSelectionMarkerACADReserveStart + 1)   // turn off selection preview display
#define AcGiSelectionMarkerACADSelectionPreviewOn   (AcGiSelectionMarkerACADReserveStart + 2)   // turn on selection preview display

class AcGiSubEntityTraits: public AcRxObject 
//
// This class applies attributes to subsequently drawn AcGi geometry
// primitives.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiSubEntityTraits);

    /// <summary>
    /// This is a new enumeration of valid bitmasks for calls to the
    /// AcGiSubEntityTraits::setDrawFlags() method.
    /// </summary>
    enum DrawFlags
    {
        /// <summary>
        /// The default value for the draw flags.This indicates no draw flags are active.
        /// </summary>
        kNoDrawFlags                     =   0,

        /// <summary>
        /// Indicates that shells or meshes that are part of the entity or sub - entity should
        /// always draw back - facing triangles.This is useful for 3D surfaces or solids that
        /// are not completely closed.Using this flag on closed solids is inefficient, but
        /// will still result in correct visual output.
        /// </summary>

        kDrawBackfaces                   =   1,

        /// <summary>
        /// Indicates that shells or meshes that are part of the entity or subentity should always draw hatches. 
        /// </summary>
        kDrawHatchGroup                  =   2,

        /// <summary>
        /// Draw front faces only (i.e. no back faces). Mutually exclusive with kDrawBackfaces flag. 
        /// Specifying them together will give the same behavior as kDrawBackfaces. 
        /// </summary>
        kDrawFrontfacesOnly              =   4,

        /// <summary>
        /// Draws with a gradient fill 
        /// </summary>
        kDrawGradientFill                =   8,

        /// <summary>
        /// Draws with a solid fill 
        /// </summary>
        kDrawSolidFill                   =   16,

        /// <summary>
        /// Draw with no line weight. Its enum value is 32.
        /// </summary>
        kDrawNoLineWeight                =   32,

        /// <summary>
        /// </summary>
        kDrawNoOptimization              =   64,

        /// <summary>
        /// For Autodesk Internal Use Only.
        /// </summary>
        kDrawUseAcGiEntityForDgnLineType = 128,  // For Autodesk Internal Use Only

        /// <summary>
        /// </summary>
        kDrawFillTextBoundaryStart       = 256,

        /// <summary>
        /// </summary>
        kDrawFillTextBoundaryEnd         = 512,

        /// <summary>
        /// </summary>
        kDrawFillSelectionWindow         = 1024,

        /// <summary>
        /// This item controls whether the newly set sub-entity traits, including color, transparency, line type, line weight and plot style, 
        /// will be force convert to ?ByLayer?, when the entity is in an external referenced drawing and the XREFOVERRIDE sysvar in the host drawing is set to 1.
        /// If this flag is set, newly set traits will not be force set to "ByLayer".
        /// If the flag is not set, newly set traits will be force set to "ByLayer".
        /// </summary>
        kDrawNoForceByLayer              = 2048
    };

    enum ShadowFlags
    {
        kShadowsCastAndReceive  = 0x00,
        kShadowsDoesNotCast     = 0x01,
        kShadowsDoesNotReceive  = 0x02,
        kShadowsIgnore          = kShadowsDoesNotCast | kShadowsDoesNotReceive,
    };

    enum SelectionFlags
    {
        kNoSelectionFlags   =   0x00,
        kSelectionIgnore    =   0x01
    };

    // Set properties of drawn objects.
    //
    virtual void              setColor              (const Adesk::UInt16 color) = 0;
    virtual void              setTrueColor          (const AcCmEntityColor& color) = 0;
    virtual void              setLayer              (const AcDbObjectId layerId) = 0;
    virtual void              setLineType           (const AcDbObjectId linetypeId) = 0;
    virtual void              setSelectionMarker    (const Adesk::LongPtr markerId) = 0;
    virtual void              setFillType           (const AcGiFillType) = 0;
    virtual void              setLineWeight         (const AcDb::LineWeight lw) = 0;
    virtual void              setLineTypeScale      (double dScale = 1.0) = 0;
    virtual void              setThickness          (double dThickness) = 0;
    virtual void              setVisualStyle        (const AcDbObjectId visualStyleId);
    virtual void              setPlotStyleName      (AcDb::PlotStyleNameType /*type*/,
                                                     const AcDbObjectId & /*id*/ = AcDbObjectId::kNull) { }
    virtual void              setMaterial           (const AcDbObjectId materialId);
    virtual void              setMapper             (const AcGiMapper * mapper);
    virtual void              setSectionable        (bool bSectionable);
    virtual Acad::ErrorStatus setDrawFlags          (Adesk::UInt32 flags);
    virtual Acad::ErrorStatus setShadowFlags        (ShadowFlags flags);
    virtual void              setSelectionGeom      (bool bSelectionflag);
    virtual void              setTransparency       (const AcCmTransparency &transparency);
    virtual void              setFill               (const AcGiFill* pFill);

    // Return current settings.
    //
    virtual Adesk::UInt16           color               (void) const = 0;
    virtual AcCmEntityColor         trueColor           (void) const = 0;
    virtual AcDbObjectId            layerId             (void) const = 0;
    virtual AcDbObjectId            lineTypeId          (void) const = 0;
    virtual AcGiFillType            fillType            (void) const = 0;
    virtual AcDb::LineWeight        lineWeight          (void) const = 0;
    virtual double                  lineTypeScale       (void) const = 0;
    virtual double                  thickness           (void) const = 0;
    virtual AcDbObjectId            visualStyle         (void) const;
    virtual AcDb::PlotStyleNameType getPlotStyleNameId  (AcDbObjectId & /*idResult*/) const
                                                                        { return AcDb::kPlotStyleNameByLayer; }
    virtual AcDbObjectId            materialId          (void) const;
    virtual const AcGiMapper *      mapper              (void) const;
    virtual bool                    sectionable         (void) const;
    virtual Adesk::UInt32           drawFlags           (void) const;
    virtual ShadowFlags             shadowFlags         (void) const;
    virtual bool                    selectionGeom       (void) const;
    virtual AcCmTransparency        transparency        (void) const;
    virtual const AcGiFill*         fill                (void) const;

    virtual void pushMarkerOverride(bool /*flag*/, const Adesk::LongPtr /*markerId*/) { }
    virtual void popMarkerOverride(void) { }
    virtual void clearMarkerOverride(void) { }
};


inline void 
AcGiSubEntityTraits::setMaterial(const AcDbObjectId /*materialId*/)
{
}

inline AcDbObjectId  
AcGiSubEntityTraits::materialId(void) const
{
    return AcDbObjectId::kNull;
}

inline
void AcGiSubEntityTraits::setMapper(const AcGiMapper * /*mapper*/)
{
}

inline const AcGiMapper * 
AcGiSubEntityTraits::mapper(void) const
{
    return NULL;
}

inline void 
AcGiSubEntityTraits::setVisualStyle(AcDbObjectId /*visualStyleId*/)
{
}

inline AcDbObjectId
AcGiSubEntityTraits::visualStyle(void) const
{
    return AcDbObjectId::kNull;
}

inline void 
AcGiSubEntityTraits::setSectionable(bool /*bSectionable*/)
{
}

inline bool 
AcGiSubEntityTraits::sectionable(void) const
{
    return false;
}

inline Acad::ErrorStatus
AcGiSubEntityTraits::setDrawFlags(Adesk::UInt32 /*flags*/)
{
    return Acad::eNotImplementedYet;
}

inline Adesk::UInt32 
AcGiSubEntityTraits::drawFlags(void) const
{
    return 0;
}

inline Acad::ErrorStatus 
AcGiSubEntityTraits::setShadowFlags(ShadowFlags /*flags*/)
{
    return Acad::eNotImplementedYet;
}

inline AcGiSubEntityTraits::ShadowFlags
AcGiSubEntityTraits::shadowFlags(void) const
{
    return kShadowsCastAndReceive;
}

inline void
AcGiSubEntityTraits::setSelectionGeom(bool)
{
}

inline bool 
AcGiSubEntityTraits::selectionGeom(void) const
{
    return false;
}

inline void
AcGiSubEntityTraits::setTransparency(const AcCmTransparency&)
{
}


inline AcCmTransparency
AcGiSubEntityTraits::transparency(void) const
{
   return AcCmTransparency();   // empty object
}

inline void AcGiSubEntityTraits::setFill(const AcGiFill * /*pFill*/)
{
}

inline const AcGiFill *AcGiSubEntityTraits::fill(void) const
{
    return nullptr;
}

class AcGiDrawableTraits : public AcGiSubEntityTraits 
//
// This class applies attributes to all AcGi geometry primitives
// for this drawable. This class is available to a drawable only during
// the setAttributes() call.
//
{ 
public:

    ACRX_DECLARE_MEMBERS(AcGiDrawableTraits);

    enum HighlightProperty
    {
        kVertexRolloverHighlightSize,
    };
    
    // Rather than using individual calls to the settings it is more efficient
    // to make this single call for an entity.
    //
    virtual void              setupForEntity       (AcDbEntity *pEntity);

    // Drawables that emit light can add one or more to the model. A unique
    // object id must be used for each light, though an object may pass
    // in its own object id.
    // This implementation ignores light information, so derived classes
    // must override this method in order to collect and use the illumination.
    //
    virtual void              addLight             (const AcDbObjectId& lightId);

    virtual void              setLinePattern       (const AcGiLineType linePattern);
    virtual AcGiLineType      linePattern          (void) const;

    virtual Acad::ErrorStatus setSelectionFlags    (const SelectionFlags flags);
    virtual SelectionFlags    selectionFlags       (void) const;

    virtual Acad::ErrorStatus setHighlightProperty (HighlightProperty property,
                                                    AcGiVariant&       value);
    virtual AcGiVariant       highlightProperty    (HighlightProperty property) const;

    virtual AcGiContext      *context              (void) const { return nullptr; }

protected:

    friend class AcDbImpLayerTableRecord;

    enum LayerFlags {
        kNone       = 0x00,
        kOff        = 0x01,
        kFrozen     = 0x02,
        kZero       = 0x04,
        kLocked     = 0x08
    };

    virtual void               setLayerFlags       (Adesk::UInt8 /*flags*/)        { }
};

// Default implementation does nothing with the illumination data.
//
inline void 
AcGiDrawableTraits::addLight(const AcDbObjectId& /*lightId*/)
{
}

inline void
AcGiDrawableTraits::setLinePattern (const AcGiLineType /*linePattern*/)
{
}

inline AcGiLineType
AcGiDrawableTraits::linePattern (void) const
{
    return kLineTypeSolid;
}

inline Acad::ErrorStatus
AcGiDrawableTraits::setSelectionFlags (const SelectionFlags /*flags*/)
{
    return Acad::eOk;
}

inline AcGiSubEntityTraits::SelectionFlags
AcGiDrawableTraits::selectionFlags (void) const
{
    return kNoSelectionFlags;
}

inline Acad::ErrorStatus
AcGiDrawableTraits::setHighlightProperty(HighlightProperty /*property*/,
                                         AcGiVariant&       /*value*/)
{
    return Acad::eOk;
}

inline AcGiVariant
AcGiDrawableTraits::highlightProperty(HighlightProperty /*property*/) const
{
    return AcGiVariant();
}

class AcGiNonEntityTraits : public AcGiDrawableTraits
// 
// This class implements empty AcGiDrawableTraits and AcGiSubEntityTraits
// interfaces, to allow non-entity drawables such as materials to elaborate 
// their unique properties through AcGiDrawableTraits
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiNonEntityTraits);

    // AcGiDrawableTraits interface
    virtual void                setupForEntity      (AcDbEntity* pEntity) override;
    virtual void                addLight(const AcDbObjectId& id) override;

    // AcGiSubEntityTraits interface
    virtual void                setColor            (const Adesk::UInt16 color) override;
    virtual Adesk::UInt16       color               (void) const override;
    virtual void                setTrueColor        (const AcCmEntityColor& color) override;
    virtual AcCmEntityColor     trueColor           (void) const override;
    virtual void                setLayer            (const AcDbObjectId layerId) override;
    virtual AcDbObjectId        layerId             (void) const override;
    virtual void                setLineType         (const AcDbObjectId linetypeId) override;
    virtual AcDbObjectId        lineTypeId          (void) const override;
    virtual void                setSelectionMarker  (const Adesk::LongPtr markerId) override;
    virtual void                setFillType         (const AcGiFillType fillType) override;
    virtual AcGiFillType        fillType            (void) const override;
    virtual void                setLineWeight       (const AcDb::LineWeight lw) override;
    virtual AcDb::LineWeight    lineWeight          (void) const override;
    virtual void                setThickness        (double thickness) override;
    virtual double              thickness           (void) const override;
    virtual void                setLineTypeScale    (double dScale) override;
    virtual double              lineTypeScale       (void) const override;
    virtual void                setMaterial         (const AcDbObjectId matId) override;
    virtual AcDbObjectId        materialId          (void) const override;
    virtual void                setSelectionGeom    (bool bSelectionflag) override;
    virtual bool                selectionGeom       ( void ) const override;

    virtual void                setTransparency     (const AcCmTransparency& transparency) override;
    virtual AcCmTransparency    transparency        (void) const override;

};

inline void 
AcGiNonEntityTraits::setupForEntity (AcDbEntity* /*pEntity*/)
{
    assert(false);
}

inline void 
AcGiNonEntityTraits::addLight(const AcDbObjectId& /*id*/)
{
    assert(false);
}

inline void 
AcGiNonEntityTraits::setColor (const Adesk::UInt16 /*color*/)     
{
    assert(false);
}

inline Adesk::UInt16 
AcGiNonEntityTraits::color (void) const      
{ 
    assert(false);
    return 0; 
}

inline void 
AcGiNonEntityTraits::setTrueColor (const AcCmEntityColor& /*color*/)  
{ 
    assert(false);
}

inline AcCmEntityColor 
AcGiNonEntityTraits::trueColor (void) const
{ 
    assert(false);
    return AcCmEntityColor(); 
}

inline void 
AcGiNonEntityTraits::setLayer (const AcDbObjectId /*layerId*/)    
{ 
    assert(false);
}

inline AcDbObjectId 
AcGiNonEntityTraits::layerId (void) const      
{ 
    assert(false);
    return AcDbObjectId::kNull; 
}

inline void 
AcGiNonEntityTraits::setLineType (const AcDbObjectId /*linetypeId*/)
{  
    assert(false);
}

inline AcDbObjectId AcGiNonEntityTraits::lineTypeId (void) const      
{ 
    assert(false);
    return  AcDbObjectId::kNull; 
}

inline void 
AcGiNonEntityTraits::setMaterial(const AcDbObjectId /*matId*/)
{  
    assert(false);
}

inline AcDbObjectId AcGiNonEntityTraits::materialId (void) const      
{ 
    assert(false);
    return  AcDbObjectId::kNull; 
}

inline void 
AcGiNonEntityTraits::setSelectionMarker (const Adesk::LongPtr /*markerId*/)   
{ 
    assert(false);
}

inline void 
AcGiNonEntityTraits::setFillType (const AcGiFillType /*fillType*/)   
{ 
    assert(false);
}

inline AcGiFillType 
AcGiNonEntityTraits::fillType (void) const      
{ 
    assert(false);
    return kAcGiFillAlways;
}

inline void 
AcGiNonEntityTraits::setLineWeight (const AcDb::LineWeight /*lw*/)     
{ 
    assert(false);
}

inline AcDb::LineWeight 
AcGiNonEntityTraits::lineWeight (void) const      
{ 
    assert(false);
    return AcDb::kLnWt000; 
}

inline void 
AcGiNonEntityTraits::setThickness (double /*thickness*/)
{ 
    assert(false);
}

inline double 
AcGiNonEntityTraits::thickness (void) const      
{ 
    assert(false);
    return 0.0; 
}

inline void 
AcGiNonEntityTraits::setLineTypeScale (double /*dScale*/)   
{  
    assert(false);
}

inline double 
AcGiNonEntityTraits::lineTypeScale (void) const      
{ 
    assert(false);
    return 0.0; 
}

inline void
AcGiNonEntityTraits::setSelectionGeom ( bool )
{
    assert(false);
}

inline bool 
AcGiNonEntityTraits::selectionGeom ( void ) const
{
    assert(false);
    return false;
}

inline void 
AcGiNonEntityTraits::setTransparency (const AcCmTransparency& )  
{ 
    assert(false);
}

inline AcCmTransparency 
AcGiNonEntityTraits::transparency (void) const
{ 
    assert(false);
    return AcCmTransparency(); 
}



#ifndef _WINDEF_
struct HDC__ ;
typedef     struct HDC__ *          HDC;
#endif

class AcGiGdiDrawObject: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGdiDrawObject);

    virtual Adesk::Boolean    draw(HDC hDC, int x, int y, int w, int h) = 0;
    virtual int               width() const = 0;
    virtual int               height() const = 0;

    virtual void              addRef() = 0;
    virtual void              delRef() = 0;
};

class ACDBCORE2D_PORT AcGiPolyline : public AcGiParameter
{
public:
    ACRX_DECLARE_MEMBERS_READWRITE(AcGiPolyline, AcGiImpPolyline);

    AcGiPolyline();
    AcGiPolyline(Adesk::UInt32 nbPoints, AcGePoint3d* pVertexList, AcGeVector3d* pNormal = NULL, Adesk::LongPtr lBaseSubEntMarker = -1);
    ~AcGiPolyline();

    enum LinetypeGeneration { kPerSegment, kEndToEnd };

    virtual Adesk::UInt32 points() const;
    virtual const AcGePoint3d* vertexList() const;
    virtual const AcGeVector3d* normal() const;
    virtual LinetypeGeneration linetypeGen() const;
    virtual Adesk::LongPtr baseSubEntMarker() const;
    virtual const Adesk::LongPtr* subEntMarkerList() const;
    virtual const bool* arcSegmentFlags() const;

    virtual void setVertexList(Adesk::UInt32 nbPoints, const AcGePoint3d* pVertexList);
    virtual void setNormal(const AcGeVector3d* pNormal);
    virtual void setLinetypeGen(LinetypeGeneration ltgen);
    virtual void setBaseSubEntMarker(Adesk::LongPtr lBaseSubEntMarker);
    virtual void setSubEntMarkerList(const Adesk::LongPtr* pSubEntMarkerList);
    virtual void setArcSegmentFlags(const bool *pArcSegmentFlags);
};


typedef enum { 
     kAcGiWorldPosition,
     kAcGiViewportPosition,
     kAcGiScreenPosition,
     kAcGiScreenLocalOriginPosition,
     kAcGiWorldWithScreenOffsetPosition
} AcGiPositionTransformBehavior;

typedef enum { 
     kAcGiWorldScale,
     kAcGiViewportScale,
     kAcGiScreenScale,
     kAcGiViewportLocalOriginScale,
     kAcGiScreenLocalOriginScale
} AcGiScaleTransformBehavior;

typedef enum { 
     kAcGiWorldOrientation,
     kAcGiScreenOrientation,
     kAcGiZAxisOrientation
} AcGiOrientationTransformBehavior;

class AcGiGeometry: public AcRxObject
//
// The base class for geometry toolkits
//
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGeometry);

    enum TransparencyMode
    {
        kTransparencyOff,  // pixel alpha ignored, all pixels are opaque
        kTransparency1Bit, // pixel alpha determines transparency on/off,
            // with 0 to 254 completely transparent and 255 completely opaque
        kTransparency8Bit, // pixel alpha determines transparency level,
        // from 0 (completely transparent) to 255 (completely opaque)
    };


    // Coordinate transformations.
    //
    virtual void getModelToWorldTransform(AcGeMatrix3d&) const = 0;
    virtual void getWorldToModelTransform(AcGeMatrix3d&) const = 0;

    virtual Adesk::Boolean pushModelTransform(const AcGeVector3d & vNormal) = 0;// Uses arbitrary Axis algorythm
    virtual Adesk::Boolean pushModelTransform(const AcGeMatrix3d & xMat) = 0;
    virtual Adesk::Boolean popModelTransform() = 0;
    virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint3d& offset) = 0; 
    virtual AcGeMatrix3d pushPositionTransform (AcGiPositionTransformBehavior behavior, const AcGePoint2d& offset) = 0; 
    virtual AcGeMatrix3d pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint3d& extents) = 0; 
    virtual AcGeMatrix3d pushScaleTransform (AcGiScaleTransformBehavior behavior, const AcGePoint2d& extents) = 0; 
    virtual AcGeMatrix3d pushOrientationTransform (AcGiOrientationTransformBehavior behavior) = 0;


    // For drawing various primitives.
    //
    virtual Adesk::Boolean  circle(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal) const = 0;

    virtual Adesk::Boolean  circle(const AcGePoint3d&, const AcGePoint3d&,
                                   const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& center,
                                   const double radius,
                                   const AcGeVector3d& normal,
                                   const AcGeVector3d& startVector,
                                   const double sweepAngle,
                                   const AcGiArcType arcType = kAcGiArcSimple) const = 0;

    virtual Adesk::Boolean  circularArc(const AcGePoint3d& start,
                                   const AcGePoint3d& point,
                                   const AcGePoint3d& end,
                                   const AcGiArcType arcType = kAcGiArcSimple) const = 0;
      
    virtual Adesk::Boolean  polyline(const Adesk::UInt32 nbPoints,
                                   const AcGePoint3d* pVertexList,
                                   const AcGeVector3d* pNormal = NULL,
                                   Adesk::LongPtr lBaseSubEntMarker = -1) const = 0;

    virtual Adesk::Boolean  polyline(const AcGiPolyline& polylineObj) const = 0;

    virtual Adesk::Boolean  polyPolyline (Adesk::UInt32 nbPolylines,
                                          const AcGiPolyline* pPolylines) const = 0;
      
    virtual Adesk::Boolean  polygon(const Adesk::UInt32 nbPoints,
                                    const AcGePoint3d* pVertexList) const = 0;

    virtual Adesk::Boolean  polyPolygon(const Adesk::UInt32 numPolygonIndices,
                                        const Adesk::UInt32* numPolygonPositions,
                                        const AcGePoint3d* polygonPositions,
                                        const Adesk::UInt32* numPolygonPoints,
                                        const AcGePoint3d* polygonPoints,
                                        const AcCmEntityColor* outlineColors = NULL,
                                        const AcGiLineType* outlineTypes = NULL,
                                        const AcCmEntityColor* fillColors = NULL,
                                        const AcCmTransparency* fillOpacities = NULL) const  = 0;

    virtual Adesk::Boolean  mesh(const Adesk::UInt32 rows,
                                 const Adesk::UInt32 columns,
                                 const AcGePoint3d* pVertexList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const bool bAutoGenerateNormals = true
                                 ) const = 0;

    virtual Adesk::Boolean  shell(const Adesk::UInt32 nbVertex,
                                 const AcGePoint3d* pVertexList,
                                 const Adesk::UInt32 faceListSize,
                                 const Adesk::Int32* pFaceList,
                                 const AcGiEdgeData* pEdgeData = NULL,
                                 const AcGiFaceData* pFaceData = NULL,
                                 const AcGiVertexData* pVertexData = NULL,
                                 const struct resbuf* pResBuf = NULL,
                                 const bool bAutoGenerateNormals = true
                                 ) const = 0;
      
    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const double height,
                                 const double width,
                                 const double oblique,
                                 const ACHAR* pMsg) const = 0;

    virtual Adesk::Boolean  text(const AcGePoint3d& position,
                                 const AcGeVector3d& normal,
                                 const AcGeVector3d& direction,
                                 const ACHAR* pMsg,
                                 const Adesk::Int32 length,
                                 const Adesk::Boolean raw,
                                 const AcGiTextStyle &pTextStyle
                                 ) const = 0;

    virtual Adesk::Boolean  xline(const AcGePoint3d&,
                                  const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  ray(const AcGePoint3d&,
                                const AcGePoint3d&) const = 0;

    virtual Adesk::Boolean  pline(const AcDbPolyline& lwBuf,
                                  Adesk::UInt32 fromIndex = 0,
                                  Adesk::UInt32 numSegs = 0
                                  ) const = 0;

    virtual Adesk::Boolean  draw(AcGiDrawable*) const = 0;

    virtual Adesk::Boolean  image(const AcGiImageBGRA32& imageSource,
                                  const AcGePoint3d& position,
                                  const AcGeVector3d& u, //orientation and magnitude of width
                                  const AcGeVector3d& v, //orientation and magnitude of height
                                  TransparencyMode transparencyMode = kTransparency8Bit
                                  ) const = 0;

    virtual Adesk::Boolean  rowOfDots(int count,
                                      const AcGePoint3d&     start,
                                      const AcGeVector3d&     step
                                     ) const = 0;

    virtual Adesk::Boolean  ellipticalArc(const AcGePoint3d&         center,
                                          const AcGeVector3d&        normal,
                                          double                     majorAxisLength,
                                          double                     minorAxisLength,
                                          double                     startDegreeInRads,
                                          double                     endDegreeInRads,
                                          double                     tiltDegreeInRads,
                                          AcGiArcType                arcType = kAcGiArcSimple
                                          ) const = 0 ;

    // If you push a clip boundary onto the stack you must pop it;
    //
    virtual Adesk::Boolean          pushClipBoundary(AcGiClipBoundary * pBoundary) = 0;
    virtual void                    popClipBoundary() = 0;
    virtual Adesk::Boolean   worldLine(const AcGePoint3d pnts[2]) {
                                        AcGePoint3d polyPnts[2];
                                        AcGeMatrix3d mat;
                                        getWorldToModelTransform(mat);
                                        polyPnts[0] = mat * pnts[0];
                                        polyPnts[1] = mat * pnts[1];
                                        return polyline(2, polyPnts);
                                    };
    // array of points
    virtual Adesk::Boolean  polypoint( const Adesk::UInt32 nbPoints,
                                       const AcGePoint3d* pVertexList,
                                       const AcGeVector3d* pNormal = NULL,
                                       const Adesk::LongPtr *pSubEntMarkers = NULL ) const {
                                           AcGePoint3d pline[2];
                                           Adesk::Boolean retval = Adesk::kFalse;
                                           for (Adesk::UInt32 i = 0; i < nbPoints; i++) {
                                               pline[1] = pline[0] = pVertexList[i];
                                               retval = polyline(2, pline, pNormal ? &pNormal[i] : NULL, pSubEntMarkers ? pSubEntMarkers[i] : -1);
                                               if (retval)
                                                   return retval;
                                           }
                                           return retval;
                                    };

    virtual Adesk::Boolean ownerDraw(AcGiGdiDrawObject*         /*pObject*/,
                                     const AcGePoint3d&         /*position*/,
                                     const AcGeVector3d&        /*u*/,
                                     const AcGeVector3d&        /*v*/
                                     ) const { return Adesk::kTrue; };


    virtual Adesk::Boolean  edge(const AcArray<AcGeCurve2d*>& edges) const = 0;
};

class AcGiWorldGeometry: public AcGiGeometry 
//
// This class contains the view independent, model coordinate,
// 3D geometry methods.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiWorldGeometry);

    virtual void setExtents(AcGePoint3d *pNewExtents) const = 0;

    // If this drawable is a block and has AcDbAttributes it must call
    // this method exactly once before sending the attributes to 
    // draw(). Once this is called the object may draw only attributes
    // and no more primitives
    // The attributes must be the last objects rendered
    //
    virtual void startAttributesSegment() {};
};

class AcGiViewportGeometry: public AcGiGeometry 
//
// This class contains the view dependent, model and drawing coordinate,
// 3D geometry methods.
//
{ 
public:
    ACRX_DECLARE_MEMBERS(AcGiViewportGeometry);

    virtual Adesk::Boolean  polylineEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;
    virtual Adesk::Boolean  polygonEye(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;

    virtual Adesk::Boolean  polylineDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;
    virtual Adesk::Boolean  polygonDc(const Adesk::UInt32 nbPoints,
                                const AcGePoint3d* pPoints) const = 0;

    enum ImageSource {
        kFromDwg,
        kFromOleObject,
        kFromRender
    };

    virtual Adesk::Boolean  rasterImageDc(
                const AcGePoint3d& origin,
                const AcGeVector3d& u,
                const AcGeVector3d& v,
                const AcGeMatrix2d& pixelToDc,
                AcDbObjectId entityId,
                AcGiImageOrg imageOrg,
                Adesk::UInt32 imageWidth,
                Adesk::UInt32 imageHeight,
                Adesk::Int16 imageColorDepth,
                Adesk::Boolean transparency,
                ImageSource source,
                const AcGeVector3d& unrotatedU,
                const AcGiImageOrg origionalImageOrg,
                const AcGeMatrix2d& unrotatedPixelToDc,
                const Adesk::UInt32 unrotatedImageWidth,
                const Adesk::UInt32 unrotatedImageHeight
                ) const = 0;

    virtual Adesk::Boolean  ownerDrawDc(
                Adesk::Int32                       vpnumber, 
                Adesk::Int32                       left, 
                Adesk::Int32                       top, 
                Adesk::Int32                       right, 
                Adesk::Int32                       bottom, 
                const OwnerDraw*           pOwnerDraw
                ) const = 0;

    virtual Adesk::Boolean  ownerDraw3d(
                AcGePoint3d&               /*minBounds*/,
                AcGePoint3d&               /*maxBounds*/,
                OwnerDraw3d*               /*pOwnerDraw*/
                ) const  { return Adesk::kFalse; };
};

#pragma warning (pop)   // disabled 4100 - unreferenced formal parameter

class ACDBCORE2D_PORT AcGiEdgeData : public AcGiParameter 
//
// This class contains arrays of edge attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS_READWRITE(AcGiEdgeData, AcGiImpEdgeData);

    ~AcGiEdgeData();
    AcGiEdgeData();

    virtual void            setColors(const short *colors);
    virtual void            setTrueColors(const AcCmEntityColor *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setLineTypes(const AcDbObjectId *linetypes);
    virtual void            setSelectionMarkers(const Adesk::LongPtr* pSelectionMarkers);
    virtual void            setVisibility(const Adesk::UInt8* pVisibility);
    
    virtual short*          colors() const;
    virtual AcCmEntityColor* trueColors() const;
    virtual AcDbObjectId*   layerIds() const;
    virtual AcDbObjectId*   linetypeIds() const;
    virtual Adesk::LongPtr* selectionMarkers() const;
    virtual Adesk::UInt8*   visibility() const;
};

class ACDBCORE2D_PORT AcGiFaceData: public AcGiParameter 
//
// This class contains arrays of face attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    ACRX_DECLARE_MEMBERS_READWRITE(AcGiFaceData, AcGiImpFaceData);

    ~AcGiFaceData();
    AcGiFaceData();

    virtual void            setColors(const short *colors);
    virtual void            setTrueColors(const AcCmEntityColor *colors);
    virtual void            setLayers(const AcDbObjectId *layers);
    virtual void            setSelectionMarkers(const Adesk::LongPtr* pSelectionMarkers);
    virtual void            setNormals(const AcGeVector3d* pNormals);
    virtual void            setVisibility(const Adesk::UInt8* vis);
    virtual void            setMaterials(const AcDbObjectId * materials);
    virtual void            setMappers(const AcGiMapper * mappers);
    virtual void            setTransparency(const AcCmTransparency *transparency);

    virtual short*          colors() const;
    virtual AcCmEntityColor* trueColors() const;
    virtual AcDbObjectId*   layerIds() const;
    virtual Adesk::LongPtr* selectionMarkers() const;
    virtual AcGeVector3d*   normals() const;
    virtual Adesk::UInt8*   visibility() const;
    virtual AcDbObjectId*   materials() const;
    virtual AcGiMapper*     mappers() const; 
    virtual AcCmTransparency* transparency() const;
};

class ACDBCORE2D_PORT AcGiVertexData: public AcGiParameter 
//
// This class contains arrays of vertex attributes for meshes and shells.
//
// NOTE:
//   Setting an 'improper' size array of color, layers, etc.
//   will cause unpredictable or fatal results.
//
{ 
public:
    enum MapChannel
    {
        kAllChannels,
        kMapChannels
    };

    ACRX_DECLARE_MEMBERS_READWRITE(AcGiVertexData, AcGiImpVertexData);
    ~AcGiVertexData();
    AcGiVertexData();

    virtual void setNormals(const AcGeVector3d* pNormals);
    virtual AcGeVector3d* normals() const;
    virtual void setOrientationFlag(const AcGiOrientationType oflag); 
    virtual AcGiOrientationType orientationFlag() const;
    virtual void setTrueColors(const AcCmEntityColor *colors);
    virtual AcCmEntityColor* trueColors() const;
    virtual void setMappingCoords (MapChannel mapChannel, const AcGePoint3d* pCoords);
    virtual AcGePoint3d* mappingCoords (MapChannel mapChannel) const;
};

class AcGiTextStyle: public AcGiParameter
// 
// This class contains methods to create and modify a text
// style object
//
{ 
public:
    ACRX_DECLARE_MEMBERS_READWRITE(AcGiTextStyle, AcGiImpTextStyle);
    ~AcGiTextStyle();
    AcGiTextStyle(AcDbDatabase* pDb = NULL);

    AcGiTextStyle(
        const ACHAR*  fontName, 
        const ACHAR*  bigFontName, 
        const double textSize, 
        const double xScale, 
        const double obliqueAngle, 
        const double trPercent,

        const Adesk::Boolean isBackward,
        const Adesk::Boolean isUpsideDown,
        const Adesk::Boolean isVertical, 

        const Adesk::Boolean isOverlined,
        const Adesk::Boolean isUnderlined,
        const Adesk::Boolean isStrikethrough = false,

        const ACHAR*          styleName = NULL);

    // Unicode: change from char to int, since in the implementation, the returned
    // result is actually bitmask indicating some status result.
    virtual int loadStyleRec(AcDbDatabase* pDb = NULL) const;
    virtual void setTextSize(const double size);
    virtual void setXScale(const double xScale);
    virtual void setObliquingAngle(const double obliquingAngle);

    virtual void setTrackingPercent(const double trPercent);

    virtual void setBackward(const Adesk::Boolean isBackward);
    virtual void setUpsideDown(const Adesk::Boolean isUpsideDown);
    virtual void setVertical(const Adesk::Boolean isVertical);

    virtual void setUnderlined(const Adesk::Boolean isUnderlined);
    virtual void setOverlined(const Adesk::Boolean isOverlined);
    virtual void setStrikethrough(const Adesk::Boolean isStrikethrough);

    virtual void setFileName(const ACHAR * fontName);
    virtual void setBigFontFileName(const ACHAR * bigFontFileName);

    virtual double textSize() const;
    virtual double xScale() const;
    virtual double obliquingAngle() const;

    virtual double trackingPercent() const;

    virtual Adesk::Boolean isBackward() const;
    virtual Adesk::Boolean isUpsideDown() const;
    virtual Adesk::Boolean isVertical() const;

    virtual Adesk::Boolean isUnderlined() const;
    virtual Adesk::Boolean isOverlined() const;
    virtual Adesk::Boolean isStrikethrough() const;

    virtual const ACHAR * fileName() const;
    virtual const ACHAR * bigFontFileName() const;

    virtual AcGePoint2d extents(const ACHAR * pStr, 
                const Adesk::Boolean penups,
                const int len,
                const Adesk::Boolean raw,
                AcGiWorldDraw *ctxt = NULL) const;

    virtual const ACHAR * styleName() const;
    virtual Acad::ErrorStatus setStyleName(const ACHAR *);
    
    ACDBCORE2D_PORT virtual Acad::ErrorStatus setFont(const ACHAR * pTypeface,
                                      Adesk::Boolean bold,
                                      Adesk::Boolean italic,
                                      Charset charset, 
                                      Autodesk::AutoCAD::PAL::FontUtils::FontPitch pitch,
                                      Autodesk::AutoCAD::PAL::FontUtils::FontFamily family);

    ACDBCORE2D_PORT virtual Acad::ErrorStatus font(AcString & sTypeface,
                                   bool & bold, bool & italic, Charset& charset,
                                   Autodesk::AutoCAD::PAL::FontUtils::FontPitch& pitch,
                                   Autodesk::AutoCAD::PAL::FontUtils::FontFamily& family) const;

    // deprecated. To be removed. Calls the above overload
    virtual Acad::ErrorStatus font(ACHAR *& pTypeface,
                                   bool & bold, bool & italic, Charset& charset,
                                   Autodesk::AutoCAD::PAL::FontUtils::FontPitch& pitch,
                                   Autodesk::AutoCAD::PAL::FontUtils::FontFamily& family) const final;

    virtual Acad::ErrorStatus  extentsBox(  const ACHAR * pStr, 
                                            const Adesk::Boolean penups,
                                            const int len,
                                            const Adesk::Boolean raw,
                                            AcGePoint2d &extMin,
                                            AcGePoint2d &extMax,
                                            AcGiWorldDraw *ctxt = NULL) const;

    virtual void setTrackKerning(double trackPercent) const;

    virtual bool preLoaded() const;
    virtual void setPreLoaded(bool);
};

// Deprecated and will be removed. If you need to override the font() method, please
// override the one taking AcString & arg.
inline Acad::ErrorStatus AcGiTextStyle::font(ACHAR *& pTypeface,
                                        bool & bold, bool & italic, Charset& charset,
                                        Autodesk::AutoCAD::PAL::FontUtils::FontPitch& pitch,
                                        Autodesk::AutoCAD::PAL::FontUtils::FontFamily& family) const
{
    AcString sTypeface;
    const Acad::ErrorStatus es = this->font(sTypeface, bold, italic, charset, pitch, family);
    ::acutNewString(sTypeface.constPtr(), pTypeface);
    return es; 
}

class ACDBCORE2D_PORT AcGiFill : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiFill);

    AcGiFill();
    AcGiFill(const AcGiFill&);
    virtual ~AcGiFill();

    double deviation() const;
    void   setDeviation(double dev);

private:
    AcGiImpFill *mpImp = nullptr;
};

class ACDBCORE2D_PORT AcGiHatchPatternDefinition
{
public:
    AcGiHatchPatternDefinition();
    AcGiHatchPatternDefinition(const AcGiHatchPatternDefinition &def);
    AcGiHatchPatternDefinition(double angle,
                         double baseX,
                         double baseY,
                         double offsetX,
                         double offsetY,
                         const AcGeDoubleArray& dashList);
    ~AcGiHatchPatternDefinition();

    double angle() const;
    double baseX() const;
    double baseY() const;
    double offsetX() const;
    double offsetY() const;
    const AcGeDoubleArray& dashList() const;

    AcGiHatchPatternDefinition & operator = (const AcGiHatchPatternDefinition &def);

private:
    AcGiImpHatchPatternDefinition *  mpImp = nullptr;
};

class ACDBCORE2D_PORT AcGiHatchPattern : public AcGiFill
{
public:
    ACRX_DECLARE_MEMBERS(AcGiHatchPattern);
    AcGiHatchPattern(const AcArray<AcGiHatchPatternDefinition>& );
    AcGiHatchPattern(const AcGiHatchPattern&);
    virtual ~AcGiHatchPattern();

    const AcArray<AcGiHatchPatternDefinition>& patternLines () const;

private:
    AcGiImpHatchPattern *mpImp = nullptr;
};

class ACDBCORE2D_PORT AcGiGradientFill : public AcGiFill
{
public:
    enum GradientType
    {
        kLinear,
        kCylinder,
        kInvCylinder,
        kSpherical,
        kHemispherical,
        kCurved,
        kInvSpherical,
        kInvHemispherical,
        kInvCurved
    };

    ACRX_DECLARE_MEMBERS(AcGiGradientFill);

    AcGiGradientFill(double                              gradientAngle,
                     double                              gradientShift,
                     bool                                bAdjustAspect,
                     AcArray<AcCmColor>&                 gradientColors,
                     AcGiGradientFill::GradientType type);

    AcGiGradientFill(const AcGiGradientFill&);
    virtual ~AcGiGradientFill();

    void setGradientAngle(double val);
    double gradientAngle() const;

    void setGradientShift(double val);
    double gradientShift() const;

    void setIsAdjustAspect(bool val);
    bool isAdjustAspect() const;

    void setGradientColors(const AcArray<AcCmColor>& val);
    const AcArray<AcCmColor>& gradientColors() const;

    void setGradientType(AcGiGradientFill::GradientType type);
    const AcGiGradientFill::GradientType gradientType() const;

private:
    AcGiImpGradientFill *mpImp = nullptr;
};

#pragma pack (pop)

#endif
