//
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
//

#pragma once

#include "dbmain.h"
#include "acgienvironment.h"
#include "dbcolor.h"
#include "AdAChar.h"

#pragma pack(push, 8)

// The following is part of the code used to export a API
// and/or use the exported API.
//
#pragma warning( disable: 4275 4251 )

#ifdef SCENEDLLIMPEXP
#undef SCENEDLLIMPEXP
#endif
#ifdef SCENEOE
#define SCENEDLLIMPEXP __declspec( dllexport )
#else
// Note: we don't use __declspec(dllimport) here, because of the
// "local vtable" problem with msvc.  If you use __declspec(dllimport),
// then, when a client dll does a new on the class, the object's
// vtable pointer points to a vtable allocated in that client
// dll.  If the client dll then passes the object to another dll,
// and the client dll is then unloaded, the vtable becomes invalid
// and any virtual calls on the object will access invalid memory.
//
// By not using __declspec(dllimport), we guarantee that the
// vtable is allocated in the server dll during the ctor and the
// client dll does not overwrite the vtable pointer after calling
// the ctor.  And, since we expect the server dll to remain in
// memory indefinitely, there is no problem with vtables unexpectedly
// going away.
// 
#define SCENEDLLIMPEXP //__declspec( dllimport )
#endif

const ACHAR ACDB_BACKGROUND_DICTIONARY[]  = /*MSG0*/ACRX_T("ACAD_BACKGROUND");

Acad::ErrorStatus SCENEDLLIMPEXP getBackgroundDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                             AcDb::OpenMode mode, bool createIfNonExist);
Acad::ErrorStatus SCENEDLLIMPEXP getBackgroundDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                             AcDb::OpenMode mode);

class AcDbImpBackground;

class SCENEDLLIMPEXP AcDbBackground : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbBackground);
    virtual ~AcDbBackground();
    virtual AcGiDrawable*  drawable () override;

protected:
    AcDbBackground(AcDbImpBackground* pImp);
    AcDbImpBackground* imp() const; 

private:
    friend class AcDbImpBackground;
    AcDbImpBackground* mpImp;
};

class SCENEDLLIMPEXP AcDbSolidBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSolidBackground);
    AcDbSolidBackground();
    virtual ~AcDbSolidBackground();

    // Solid Background Property
    void            setColorSolid   (const AcCmEntityColor & color);
    AcCmEntityColor colorSolid      (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const override;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other) override;

    virtual AcGiDrawable::DrawableType    drawableType() const override;

protected:
    // AcGiDrawable protocol
    //
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits) override;

private:
    friend class AcDbImpSolidBackground;
};

class SCENEDLLIMPEXP AcDbGradientBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGradientBackground);
    AcDbGradientBackground();
    virtual ~AcDbGradientBackground();

    // Gradient Background Properties
    void            setColorTop    (const AcCmEntityColor & color);
    AcCmEntityColor colorTop       (void) const;
    void            setColorMiddle (const AcCmEntityColor & color);
    AcCmEntityColor colorMiddle    (void) const;
    void            setColorBottom (const AcCmEntityColor & color);
    AcCmEntityColor colorBottom    (void) const;
    void            setHorizon     (double horizon);
    double          horizon        (void) const;
    void            setHeight      (double height);
    double          height         (void) const ;
    void            setRotation    (double rotation);
    double          rotation       (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const override;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other) override;

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const override;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits) override;

private:
    friend class AcDbImpGradientBackground;
};

class SCENEDLLIMPEXP AcDbImageBackground : public AcDbBackground
{
public:

    ACRX_DECLARE_MEMBERS(AcDbImageBackground);
    AcDbImageBackground();
    virtual ~AcDbImageBackground();

    // Image Background Properties
    void            setImageFilename        (const ACHAR* filename);
    const ACHAR *   imageFilename           (void) const;
    void            setFitToScreen          (bool bFitToScreen);
    bool            fitToScreen             (void) const;
    void            setMaintainAspectRatio  (bool bMaintainAspectRatio);
    bool            maintainAspectRatio     (void) const;
    void            setUseTiling            (bool bUseTiling);
    bool            useTiling               (void) const;
    void            setXOffset              (double xOffset);
    double          xOffset                 (void) const;
    void            setYOffset              (double yOffset);
    double          yOffset                 (void) const;
    void            setXScale               (double xScale);
    double          xScale                  (void) const;
    void            setYScale               (double yScale);
    double          yScale                  (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const override;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other) override;

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const override;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits) override;

private:
    friend class AcDbImpImageBackground;
};

class SCENEDLLIMPEXP AcDbGroundPlaneBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbGroundPlaneBackground);
    AcDbGroundPlaneBackground();
    virtual ~AcDbGroundPlaneBackground();

    // GroundPlane Background Properties
    void            setColorSkyZenith       (const AcCmEntityColor & color);
    AcCmEntityColor colorSkyZenith          (void) const;
    void            setColorSkyHorizon      (const AcCmEntityColor & color);
    AcCmEntityColor colorSkyHorizon         (void) const;
    void            setColorUndergroundHorizon  (const AcCmEntityColor & color);
    AcCmEntityColor colorUndergroundHorizon     (void) const;
    void            setColorUndergroundAzimuth  (const AcCmEntityColor & color);
    AcCmEntityColor colorUndergroundAzimuth     (void) const;
    void            setColorGroundPlaneNear (const AcCmEntityColor & color);
    AcCmEntityColor colorGroundPlaneNear    (void) const;
    void            setColorGroundPlaneFar  (const AcCmEntityColor & color);
    AcCmEntityColor colorGroundPlaneFar     (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const override;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other) override;

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const override;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits) override;

private:
    friend class AcDbImpGroundPlaneBackground;
};

class SCENEDLLIMPEXP AcDbSkyBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbSkyBackground);
    AcDbSkyBackground();
    virtual ~AcDbSkyBackground();

    // Sky Background Property
    Acad::ErrorStatus         setSunId     (AcDbObjectId sunId);
    AcDbObjectId              sunId        (void) const;

    // AcDbObject protocol
    //
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const override;

    virtual Acad::ErrorStatus copyFrom     (const AcRxObject* other) override;

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const override;

protected:
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits) override;

private:
    friend class AcDbImpSkyBackground;
};

/// <summary>
/// Image based lighting background
/// </summary>
class SCENEDLLIMPEXP AcDbIBLBackground : public AcDbBackground
{
public:
    ACRX_DECLARE_MEMBERS(AcDbIBLBackground);
    
    /// <summary>
    /// Constructor.
    /// </summary>
    AcDbIBLBackground();
    
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbIBLBackground();

    virtual AcGiDrawable* drawable() override;

    /// <summary>
    /// Sets whether IBL is currently active
    /// When disabled, the background will be default black transparent
    /// </summary>
    /// <param name="name">
    /// Name of IBL image
    /// </param>
    virtual Acad::ErrorStatus setEnable               (const bool bEnable);
    /// <summary>
    /// Gets whether IBL is currently active
    /// </summary>
    /// <returns>
    /// Name of IBL image
    /// </returns>
    virtual bool              enable                  (void) const;
    /// <summary>
    /// Sets the image used for IBL
    /// </summary>
    /// <param name="name">
    /// Name of IBL image
    /// </param>
    virtual Acad::ErrorStatus setIBLImageName         (const AcString& name);
    /// <summary>
    /// Gets the image used for IBL
    /// </summary>
    /// <returns>
    /// Name of IBL image
    /// </returns>
    virtual AcString          IBLImageName            (void) const;
    /// <summary>
    /// Sets the rotation value for the IBL image
    /// -180 to 180 degrees
    /// </summary>
    /// <param name="rotation">
    /// Rotation value in degrees (-180 to 180)
    /// </param>
    virtual Acad::ErrorStatus setRotation             (const double rotation);
    /// <summary>
    /// Gets the rotation value for the IBL image
    /// </summary>
    /// <returns>
    /// Rotation value in degrees
    /// </returns>
    virtual double            rotation                (void) const;
    /// <summary>
    /// Sets whether to display the IBL image as the background
    /// </summary>
    /// <param name="bdisplay">
    /// Set to true to display IBL image in background
    /// </param>
    virtual Acad::ErrorStatus setDisplayImage         (const bool bdisplay);
    /// <summary>
    /// Gets whether to display the IBL image as the background
    /// </summary>
    /// <returns>
    /// True if IBL image is to be displayed as background
    /// </returns>
    virtual bool              displayImage            (void) const;
    /// <summary>
    /// Sets the background to display when DisplayImage is set to false
    /// Limited to 2D backgrounds only - Solid, Gradient, Image
    /// </summary>
    /// <remarks>
    /// Ownership of secondary background is not assumed.
    /// Cloning an AcDbIBLBackground will result in two backgrounds sharing the same secondary background
    /// </remarks>
    /// <param name="bg">
    /// Background db Id
    /// </param>
    virtual Acad::ErrorStatus setSecondaryBackground  (const AcDbObjectId bg);
    /// <summary>
    /// Gets the background to display when DisplayImage is set to false
    /// </summary>
    /// <returns>
    /// Background db Id
    /// </returns>
    virtual AcDbObjectId      secondaryBackground     (void) const;

    // AcDbObject functions
    virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler) override;
    virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler) override;
    virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;

    // AcGiDrawable protocol
    //
    virtual AcGiDrawable::DrawableType    drawableType() const override;

	virtual bool operator==(const AcDbIBLBackground& environment);

protected:
    // AcGiDrawable functions
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits) override;
};

#pragma pack (pop)
