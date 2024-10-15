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

#pragma once

#include "AdAChar.h"
#include "adesk.h"

// Forward class declarations

namespace Atil {
    class ImageFormatCodec;
    class ProgressCallbackInterface;
};

class AdHostImageAppServices;

////////////////////////////////////////////////////////////////////////
// class AdHostImageAppServices 
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class defines an interface to publish the 
/// initialization/un-initialization of format codecs with the imaging 
/// library that an application (like AutoCAD) might be internally using.
/// </summary>
///
/// <remarks>
/// Applications (like AutoCAD) which are clients of some imaging library 
/// themselves can provide implementation for this interface. It is preferred 
/// to have a singleton object implementing this interface for the entire 
/// application session. Using this interface, applications can mask the
/// internals of how it initializes the imaging library it uses. 
/// </remarks>
///
class ADESK_NO_VTABLE AdHostImageAppServices
{
public:

    /// 
    /// <summary>
    /// Use this function to get the list of image file extensions
    /// supported by the currently in use imaging library.
    /// </summary>
    /// 
    /// <param name="bRefresh">
    /// If set to true would re-populate the list of format file 
    /// extensions that the underlying imaging library supports.
    /// Callers to this function would usually set bRefresh parameter to 
    /// true after registering a new format codec with the imaging library.
    /// </param>
    ///
    /// <returns> 
    /// Returns a pointer to a array of character which has semicolon 
    /// separated extension strings.
    /// Format of the returned string will be as follows:
    /// "bmp;dib;rle;tif;tiff;cal;mil;rst;cg4;gp4;cals;gif"
    /// </returns>
    ///
    virtual const ACHAR* imageFileExtensions (bool bRefresh = false) = 0;

    /// 
    /// <summary>
    /// Use this function to get the filtered list of image 
    /// file descriptions and extensions supported by the currently 
    /// in use imaging library.
    /// </summary>
    /// 
    /// <param name="bRefresh">
    /// If set to true would re-populate the filter strings 
    /// supported by the underlying imaging library.
    /// Callers to this function would usually set bRefresh parameter to 
    /// true after registering a new format codec with the imaging library.
    /// </param>
    ///
    /// <returns> 
    /// Returns a pointer to a array of character which has semicolon 
    /// separated format specific filtered strings.
    /// Format of the returned string will be as follows:
    /// "Windows Bitmap:bmp,dib,rle;Tagged Image File Format:tif,tiff;
    /// CALS MIL-R-28002A Type I Reader:cal,mil,rst,cg4,gp4,cals;
    /// Image Systems CCITT Group 4 compression:ig4;Macintosh PICT:pct,pict;RLC:rlc;
    /// TrueVision Targa Bitmap:tga;
    /// Portable Network Graphics file (PNG):png;
    /// JFIF(JPEG) 6.0:jpg;ZSoft Paint:pcx;
    /// Autodesk Animator FLI/FLC File:fli,flc;Graphic Interchange format:gif"  
    /// </returns>
    ///
    virtual const ACHAR* imageFilterString (bool bRefresh = false) = 0;

    /// 
    /// <summary>
    /// Registers the supplied format codec with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the registration succeeded.
    /// </returns>
    ///
    virtual bool registerFormatCodec (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Use this method to find out if a format codec is already registered 
    /// with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the input format codec is already registered 
    /// with the imaging library.
    /// </returns>
    ///
    virtual bool formatCodecRegistered (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Re-registers the input format codec with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the reregistration process succeeded.
    /// </returns>
    ///
    virtual bool reRegisterFormatCodec (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Unregisters the input format codec with the imaging library.
    /// </summary>
    ///
    /// <param name="pCodec">
    /// A pointer to an object that implements Atil::ImageFormatCodec 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns true if the un-registration process succeeded.
    /// </returns>
    ///
    virtual bool unRegisterFormatCodec (Atil::ImageFormatCodec& codec) = 0;

    /// 
    /// <summary>
    /// Registers a progress call back with the imaging library.
    /// </summary>
    ///
    /// <param name="pCallback">
    /// A pointer to an object that implements Atil::ProgressCallbackInterface 
    /// interface.
    /// </param>
    ///
    /// <returns> 
    /// Returns the pointer to the old Atil::ProgressCallbackInterface object.
    /// </returns>
    ///
    virtual Atil::ProgressCallbackInterface* registerProgressCallback (Atil::ProgressCallbackInterface* pCallback ) = 0;
};

/// 
/// <summary>
/// Gives access to the global object that implements the 
/// AdHostImageAppServices interface.
/// </summary>
/// 
/// <returns> 
/// If succeeded, returns a pointer to the AdHostImageAppServices interface.
/// Returns NULL if failed.
/// </returns>
///
AdHostImageAppServices* getAdHostImageAppServices();
