//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//  dbcolor.h
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION: True Color Definitions

// headers
#ifndef AD_DBCOLOR_H
#define AD_DBCOLOR_H 1

#include "adesk.h"
#include "acadstrc.h"
#include "rxobject.h"
#include "AcDbCore2dDefs.h"     // ACDBCORE2D_PORT

#pragma pack (push, 8)


class AcCmEntityColor;


// It takes care of the color method, which is one of the following: 
// byBlock, byLayer, or byColor.
// Depending on this color method it stores RGB, ACI, or Layerindex.
//
// Note: To save memory I did the following:
//          It is not deriving from AcDbXObject. 
//          No virtual methods.
//          Color Method stored in last byte mRGBM.
class AcCmEntityColor
{
public:
    enum Color { kRed,
                 kGreen,
                 kBlue
    };

    // Color Method.
    enum ColorMethod {   kByLayer =0xC0, 
                         kByBlock,
                         kByColor,
                         kByACI,
                         kByPen,
                         kForeground,
                         kLayerOff,
                         // Run-time states
                         kLayerFrozen,
                         kNone
    };

    enum ACIcolorMethod {kACIbyBlock    = 0,
                         kACIforeground = 7,
                         kACIbyLayer    = 256,
                         // Run-time states
                         kACIclear      = 0,    
                         kACIstandard   = 7,
                         kACImaximum    = 255,
                         kACInone       = 257,
                         kACIminimum    = -255,
                         kACIfrozenLayer= -32700
    };

    // Blue, green, red, and Color Method (byBlock, byLayer, byColor).
    // Is stored that way for better performance. 
    //
    // Note the dependency on struct layout: we assume that indirect does not
    // overlap with colorMethod!
    //
    // Also note that RGBM is public because it's used by AcDbEntity
public:
    union RGBM {
        Adesk::UInt32    whole;
        Adesk::Int16     indirect;
        struct {
            Adesk::UInt8 blue, 
                         green, 
                         red, 
                         colorMethod;
        } mdata;
        Adesk::Int32    mnIndirect32;
        Adesk::Int32    indirect24() const;
    };

public:
    AcCmEntityColor     ();
    AcCmEntityColor     (const AcCmEntityColor & color);
    AcCmEntityColor     (ColorMethod eColorMethod);
    AcCmEntityColor     (Adesk::UInt8 red, 
                         Adesk::UInt8 green, 
                         Adesk::UInt8 blue);

    AcCmEntityColor&    operator =  (const AcCmEntityColor& color);
    bool                operator == (const AcCmEntityColor& color) const;
    bool                operator != (const AcCmEntityColor& color) const;


    // Set/get components
    Acad::ErrorStatus   setColorMethod  (ColorMethod eColorMethod);
    ColorMethod         colorMethod     () const;

    Acad::ErrorStatus   setColor        (Adesk::UInt32 color);
    Adesk::UInt32       color           () const;   

    Acad::ErrorStatus   setColorIndex   (Adesk::Int16 colorIndex);
    Adesk::Int16        colorIndex      () const;

    // For internal use. Index can only use 24 bits..
    Acad::ErrorStatus   setLayerIndex   (Adesk::Int32 layerIndex);
    Adesk::Int32        layerIndex      () const;   

    Acad::ErrorStatus   setPenIndex     (Adesk::UInt16 penIndex);
    Adesk::UInt16       penIndex        () const;   

    // Set/get RGB components
    Acad::ErrorStatus   setRGB  (Adesk::UInt8 red, 
                                 Adesk::UInt8 green, 
                                 Adesk::UInt8 blue);
    Acad::ErrorStatus   setRed  (Adesk::UInt8 red);
    Acad::ErrorStatus   setGreen(Adesk::UInt8 green);
    Acad::ErrorStatus   setBlue (Adesk::UInt8 blue);
    Adesk::UInt8        red     () const;
    Adesk::UInt8        green   () const;
    Adesk::UInt8        blue    () const;

    // Method check
    bool                isByColor   () const;
    bool                isByLayer   () const;
    bool                isByBlock   () const;
    bool                isByACI     ()   const;
    bool                isByPen     ()  const;
    bool                isForeground() const;
    bool                isLayerOff  () const;
    // Run time states.
    bool                isLayerFrozen() const;
    bool                isNone      ()   const;
    bool                isLayerFrozenOrOff() const;

    // conversion
    Adesk::UInt32       trueColor () const;
    Adesk::UInt8        trueColorMethod () const;
    Acad::ErrorStatus   setTrueColor ();
    Acad::ErrorStatus   setTrueColorMethod ();



    // static methods for reuse in other classes.
    static  Acad::ErrorStatus   setColorMethod(RGBM* rgbm, ColorMethod eColorMethod);
    static  ColorMethod         colorMethod   (const RGBM* rgbm);

    static  Acad::ErrorStatus   setColor      (RGBM* rgbm, Adesk::UInt32 color);
    static  Adesk::UInt32       color         (const RGBM* rgbm);   

    static  ACDBCORE2D_PORT Acad::ErrorStatus setColorIndex (RGBM* rgbm, Adesk::Int16 colorIndex);
    static  Adesk::Int16        colorIndex    (const RGBM* rgbm);

    // For internal use
    // Can return eNullPtr, eOutOfRange or eOk
    static  ACDBCORE2D_PORT Acad::ErrorStatus setLayerIndex(RGBM* rgbm, Adesk::Int32 layerIndex);
    static  Adesk::Int32        layerIndex    (const RGBM* rgbm);   

    static  ACDBCORE2D_PORT Acad::ErrorStatus setPenIndex(RGBM* rgbm, Adesk::UInt16 penIndex);
    static  Adesk::UInt16       penIndex      (const RGBM* rgbm);   

    // Set/get RGB components
    static Acad::ErrorStatus    setRGB  (RGBM* rgbm,
                                         Adesk::UInt8 red, 
                                         Adesk::UInt8 green, 
                                         Adesk::UInt8 blue);
    static Acad::ErrorStatus    setRed  (RGBM* rgbm, Adesk::UInt8 red);
    static Acad::ErrorStatus    setGreen(RGBM* rgbm, Adesk::UInt8 green);
    static Acad::ErrorStatus    setBlue (RGBM* rgbm, Adesk::UInt8 blue);
    static Adesk::UInt8         red     (const RGBM* rgbm);
    static Adesk::UInt8         green   (const RGBM* rgbm);
    static Adesk::UInt8         blue    (const RGBM* rgbm);

    // Method check
    static  bool                isByColor   (const RGBM* rgbm);
    static  bool                isByLayer   (const RGBM* rgbm);
    static  bool                isByBlock   (const RGBM* rgbm);
    static  bool                isByACI     (const RGBM* rgbm);
    static  bool                isByPen     (const RGBM* rgbm);
    static  bool                isForeground(const RGBM* rgbm);
    static  bool                isLayerOff  (const RGBM* rgbm);
    // Run time states.
    static  bool                isLayerFrozen(const RGBM* rgbm);
    static  bool                isNone      (const RGBM* rgbm);



    // Look up mapping between ACI and RGB.
    static Adesk::UInt32        trueColor       (const RGBM* rgbm);
    static ACDBCORE2D_PORT Adesk::UInt8         trueColorMethod (Adesk::Int16);
    static Acad::ErrorStatus    setTrueColor    (RGBM* rgbm);
    static Acad::ErrorStatus    setTrueColorMethod (RGBM* rgbm);

    static Adesk::UInt32        lookUpRGB       (Adesk::UInt8 colorIndex);
    static Adesk::UInt8         lookUpACI       (Adesk::UInt8 red,
                                                 Adesk::UInt8 green,
                                                 Adesk::UInt8 blue); 

protected:
    RGBM mRGBM;

public:
    // The Look Up Table (LUT) provides a mapping between ACI and RGB 
    // and contains each ACI's representation in RGB.
    static const Adesk::UInt8 mLUT[256][3]; 
};

// AcCmEntityColor inline
//

// Default color method is kByColor.
inline 
AcCmEntityColor::AcCmEntityColor()
{
    mRGBM.whole = 0;
    mRGBM.mdata.colorMethod = kByColor;
}

inline
AcCmEntityColor::AcCmEntityColor (const AcCmEntityColor & color)
{
    mRGBM.whole = color.mRGBM.whole;
}


// parameter:   eColorMethod    Color method information (byBlock, byLayer, byColor).
inline 
AcCmEntityColor::AcCmEntityColor(ColorMethod eColorMethod)
{
    mRGBM.whole = 0;
    mRGBM.mdata.colorMethod = static_cast<Adesk::UInt8>(eColorMethod);
}

// Default color method is kByColor.
// parameter:   red, green, blue
inline  
AcCmEntityColor::AcCmEntityColor(Adesk::UInt8 red, 
                                 Adesk::UInt8 green, 
                                 Adesk::UInt8 blue)
{
    mRGBM.mdata.red   = red;
    mRGBM.mdata.green = green;
    mRGBM.mdata.blue  = blue;
    mRGBM.mdata.colorMethod = kByColor;
}

inline AcCmEntityColor& 
AcCmEntityColor::operator= (const AcCmEntityColor & color)
{
    mRGBM.whole = color.mRGBM.whole;
    return *this;
}

inline bool
AcCmEntityColor::operator==(const AcCmEntityColor& color) const
{
    return mRGBM.whole == color.mRGBM.whole;
}

inline bool
AcCmEntityColor::operator!=(const AcCmEntityColor& color) const
{
    return mRGBM.whole != color.mRGBM.whole;
}

// get Color Method
inline AcCmEntityColor::ColorMethod     
AcCmEntityColor::colorMethod() const
{
    return (ColorMethod) mRGBM.mdata.colorMethod;
}

// get RGB
//
// return value:    Depending on color method (fourth byte):
//                  kByLayer:   Layer index in first and second byte.
//                  kByColor:   RGB and color method.
//                              First byte blue, second byte green and third byte red.
//                              Fourth byte is color method.
//
//                  kByACI:     ACI index in first and second byte.
//
//                  kByBlock,   
//                  kForeground: Only color method (fourth byte) is valid.    
inline Adesk::UInt32    
AcCmEntityColor::color () const
{
    return mRGBM.whole;
}

inline Adesk::Int16 AcCmEntityColor::colorIndex() const
{
    return colorIndex(&mRGBM);  // delegate to static method
}

inline Acad::ErrorStatus AcCmEntityColor::setColorMethod(ColorMethod eColorMethod)
{
    return setColorMethod(&mRGBM, eColorMethod);    // delegate to static method
}

inline Acad::ErrorStatus AcCmEntityColor::setColor(Adesk::UInt32 color)
{
    return setColor(&mRGBM, color);     // delegate to static method
}

inline Acad::ErrorStatus AcCmEntityColor::setColorIndex(Adesk::Int16 colorIndex)
{
    return setColorIndex(&mRGBM, colorIndex);     // delegate to static method
}


// Return signed 32-bit int obtained from low 3 bytes (24 bits) of the rgb struct
//
inline Adesk::Int32 AcCmEntityColor::RGBM::indirect24() const
{
    // We can only store a 24-bit index, because of the colorMethod field using bits 24..31
    Adesk::Int32 nRet = this->mnIndirect32;
    // Do sign extension if bit 23 is set
    if ((nRet & 0x800000) != 0)
        nRet |= 0xff000000;     // negative: set bits 24 through 31
    else
        nRet &= ~0xff000000;    // positive: clear bits 24 through 31
    return nRet;
}

inline Acad::ErrorStatus AcCmEntityColor::setLayerIndex(Adesk::Int32 layerIndex)
{
    return setLayerIndex(&mRGBM, layerIndex);   // delegate to static method
}

// return value:    Layer index.
inline Adesk::Int32 AcCmEntityColor::layerIndex(const RGBM* rgbm)
{
    if (rgbm == nullptr)
        return -1;      // error
    if (rgbm->mdata.colorMethod != kByLayer && rgbm->mdata.colorMethod != kLayerOff)
        return -1;      // error

    return rgbm->indirect24();
}

inline Adesk::Int32 AcCmEntityColor::layerIndex () const
{
    return layerIndex(&mRGBM);  // delegate to static inline method
}

inline Acad::ErrorStatus AcCmEntityColor::setPenIndex(Adesk::UInt16 penIndex)
{
    return setPenIndex(&mRGBM, penIndex);   // delegate to static method
}


inline Adesk::UInt16 AcCmEntityColor::penIndex(const RGBM* rgbm)
{
    if (rgbm == nullptr)
        return 0xffff;  // error
    if (rgbm->mdata.colorMethod != kByPen)
        return 0xffff;  // error
    return (Adesk::UInt16)rgbm->indirect;
}

inline Adesk::UInt16 AcCmEntityColor::penIndex () const
{
    return penIndex(&mRGBM);    // delegate to static inline method
}

// get red
inline Adesk::UInt8    
AcCmEntityColor::red  () const
{
    return mRGBM.mdata.red;
}

// get green
inline Adesk::UInt8
AcCmEntityColor::green() const
{
    return mRGBM.mdata.green;
}

// get blue
inline Adesk::UInt8    
AcCmEntityColor::blue () const
{
    return mRGBM.mdata.blue;
}

inline bool
AcCmEntityColor::isByColor() const
{
    return mRGBM.mdata.colorMethod == kByColor; 
}

inline bool
AcCmEntityColor::isByLayer() const
{
    return (mRGBM.mdata.colorMethod  == kByLayer ||
            (mRGBM.mdata.colorMethod == kByACI   && 
            mRGBM.indirect == kACIbyLayer)) ? true : false;
}

inline bool
AcCmEntityColor::isByBlock() const
{
    return (mRGBM.mdata.colorMethod  == kByBlock ||
            (mRGBM.mdata.colorMethod == kByACI   && 
            mRGBM.indirect == kACIbyBlock)) ? true : false;
}

inline bool
AcCmEntityColor::isByACI()   const
{
    return mRGBM.mdata.colorMethod == kByACI;
}

inline bool
AcCmEntityColor::isByPen()   const
{
    return mRGBM.mdata.colorMethod == kByPen;
}

inline bool
AcCmEntityColor::isForeground()   const
{
    return (mRGBM.mdata.colorMethod  == kForeground ||
            (mRGBM.mdata.colorMethod == kByACI      && 
            mRGBM.indirect == kACIforeground)) ? true : false;
}

inline bool
AcCmEntityColor::isLayerOff() const
{   
    return (mRGBM.mdata.colorMethod  == kLayerOff ||
            (mRGBM.mdata.colorMethod == kByACI && 
            mRGBM.indirect    <  0 && // layer off for ACI is negative
            mRGBM.indirect != kACIfrozenLayer)) ? true : false;
}

inline bool
AcCmEntityColor::isLayerFrozen() const
{   
    return (mRGBM.mdata.colorMethod  == kLayerFrozen ||
            (mRGBM.mdata.colorMethod == kByACI       && 
            mRGBM.indirect == kACIfrozenLayer)) ? true : false;
}

inline bool
AcCmEntityColor::isLayerFrozenOrOff() const
{
    return isLayerFrozen() || isLayerOff();
}

inline bool
AcCmEntityColor::isNone()   const
{
    return (mRGBM.mdata.colorMethod  == kNone ||
            (mRGBM.mdata.colorMethod == kByACI       && 
            mRGBM.indirect == kACInone)) ? true : false;
}

// parameter:   red, green, blue.
inline Acad::ErrorStatus AcCmEntityColor::setRGB(Adesk::UInt8 red, 
                                Adesk::UInt8 green, Adesk::UInt8 blue)
{
    return setRGB (&mRGBM, red, green, blue);
}

// set red
inline Acad::ErrorStatus AcCmEntityColor::setRed (Adesk::UInt8 red)
{
    return setRed (&mRGBM, red);
}

// set green
inline Acad::ErrorStatus AcCmEntityColor::setGreen (Adesk::UInt8 green)
{
    return setGreen (&mRGBM, green);
}

// set blue
inline Acad::ErrorStatus AcCmEntityColor::setBlue (Adesk::UInt8 blue)
{
    return setBlue (&mRGBM, blue);
}

// converts to true color
// returns result
inline Adesk::UInt32 AcCmEntityColor::trueColor () const
{
    return trueColor (&mRGBM);
}


// Base interface class for AcCmColor
class ADESK_NO_VTABLE AcCmColorBase
{
public:

    virtual ~AcCmColorBase() {}

    virtual AcCmEntityColor::ColorMethod  colorMethod() const = 0;;
    virtual Acad::ErrorStatus   setColorMethod(AcCmEntityColor::ColorMethod eColorMethod) = 0;

    virtual bool                isByColor() const = 0;
    virtual bool                isByLayer() const = 0;
    virtual bool                isByBlock() const = 0;
    virtual bool                isByACI()   const = 0;
    virtual bool                isByPen () const = 0;
    virtual bool                isForeground()   const = 0;

    virtual Adesk::UInt32       color() const = 0;
    virtual Acad::ErrorStatus   setColor(Adesk::UInt32 color) = 0;

    virtual Acad::ErrorStatus   setRGB  (Adesk::UInt8 red, 
                                         Adesk::UInt8 green, 
                                         Adesk::UInt8 blue) = 0;
    virtual Acad::ErrorStatus   setRed  (Adesk::UInt8 red) = 0;
    virtual Acad::ErrorStatus   setGreen(Adesk::UInt8 green) = 0;
    virtual Acad::ErrorStatus   setBlue (Adesk::UInt8 blue) = 0;
    virtual Adesk::UInt8        red  () const = 0;
    virtual Adesk::UInt8        green() const = 0;
    virtual Adesk::UInt8        blue () const = 0;

    virtual Adesk::UInt16       colorIndex() const = 0;
    virtual Acad::ErrorStatus   setColorIndex(Adesk::UInt16 colorIndex) = 0;
    virtual Adesk::UInt16       penIndex() const = 0;
    virtual Acad::ErrorStatus   setPenIndex (Adesk::UInt16 penIndex) = 0;

    virtual Acad::ErrorStatus   setNames(const ACHAR *colorName,
                                         const ACHAR *bookName = NULL) = 0;
    virtual const ACHAR *       colorName(void) const = 0;
    virtual const ACHAR *       bookName(void) const = 0;
    virtual const ACHAR *       colorNameForDisplay(void) = 0;
    virtual bool                hasColorName(void) const = 0;
    virtual bool                hasBookName(void) const = 0;

};


class AcCmTransparency {
public:

    enum transparencyMethod {
                kByLayer = 0,
                kByBlock,
                kByAlpha,


                kErrorValue     // must be last in enum
            };

    // Some Transparency constants
    enum {  kTransparencyByLayer    = (unsigned long)kByLayer,
            kTransparencyByBlock    = (unsigned long)kByBlock,
            kTransparencySolid      = ((unsigned long)(kByAlpha | (0xff << 24))),
            kTransparencyClear      = (unsigned long)kByAlpha
    };

    AcCmTransparency() { mAM.whole = kTransparencyByLayer; } // set all bytes
    AcCmTransparency(Adesk::UInt8 alpha);
    AcCmTransparency(double alphaPercent);
    AcCmTransparency(const AcCmTransparency& other) { mAM.whole = other.mAM.whole; }
    ~AcCmTransparency() {}

    AcCmTransparency& operator=(const AcCmTransparency& other);
    bool operator==(const AcCmTransparency& other) const;
    bool operator!=(const AcCmTransparency& other) const;

    void setAlpha(Adesk::UInt8 alpha);
    void setAlphaPercent(double alphaPercent);

    void setMethod(transparencyMethod method);

    Adesk::UInt8 alpha(void) const;
    double alphaPercent(void) const;

    bool isByAlpha(void) const { return (mAM.mdata.method == kByAlpha); }
    bool isByBlock(void) const { return (mAM.mdata.method == kByBlock); }
    bool isByLayer(void) const { return (mAM.mdata.method == kByLayer); }
    bool isInvalid(void) const { return (mAM.mdata.method == kErrorValue); }
    bool isClear(void) const;
    bool isSolid(void) const;

    Adesk::UInt32   serializeOut(void) const { return mAM.whole; }
    void            serializeIn(Adesk::UInt32);

private: 

    union AM {
        struct {
            Adesk::UInt8    alpha;          // low byte
            Adesk::UInt8    reserved1;    
            Adesk::UInt8    reserved2;
            Adesk::UInt8    method;         // high byte
        } mdata;  // byte data items
        Adesk::UInt32       whole;
    };

    AM mAM;
};

namespace AcCm
{
    enum DialogTabs
    {   
        //these flags can be OR-ed 
        kACITab = 1,
        kTrueColorTab = 2,
        kColorBookTab = 4,
    };

    enum ACIColors
    {   
        kACIByBlock     = 0,
        kACIRed         = 1,
        kACIYellow      = 2,
        kACIGreen       = 3,
        kACICyan        = 4,
        kACIBlue        = 5,
        kACIMagenta     = 6,
        kACIForeground  = 7,
        kACIByLayer     = 256,
    };
}

#pragma pack (pop)

#define ADSK_ACCMENTITYCOLOR_DEFINED
#include "acarrayhelper.h"

#endif // AD_DBCOLOR_H 
