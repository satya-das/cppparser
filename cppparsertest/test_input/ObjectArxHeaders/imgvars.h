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
#ifndef __IMGVARS_H
#define __IMGVARS_H

#include "dbmain.h"
#include "imgdef.h"

#pragma pack (push, 8)

// Opaque types
//
class AcDbImpRasterVariables;

// Silence compiler
//
#pragma warning( disable : 4275 ) 

#ifdef ISMDLLACCESS
#undef ISMDLLACCESS
#endif
#ifdef ISMDLLACCESSDATA
#undef ISMDLLACCESSDATA
#endif
#ifdef ISM_OBJ // For DwgUnplugged ISMobj.arx:
// Classes to be exported have to have ISMDLLACCESS definition in its header.
// Example: class ISMDLLACCESS AcDbImpRasterImageDef
#define ISMDLLACCESS __declspec(dllexport)
#define ISMDLLACCESSDATA
#else
#define ISMDLLACCESS 
#define ISMDLLACCESSDATA __declspec(dllimport)
#endif

class ISMDLLACCESS AcDbRasterVariables : public AcDbObject
{
public:

    static ClassVersion        classVersion();

    ACRX_DECLARE_MEMBERS(AcDbRasterVariables);

    // Enums, for the allowable variable values
    enum FrameSettings {
        kImageFrameInvalid  = -1,
        kImageFrameOff      =  0,
        kImageFrameAbove    =  1,
        kImageFrameBelow    =  2,
        kImageFrameOnNoPlot =  3
    };
    enum ImageQuality {
        kImageQualityInvalid = -1,
        kImageQualityDraft = 0,
        kImageQualityHigh  = 1
    };

    static AcDbRasterVariables* create(); 
    AcDbRasterVariables();
    virtual     ~AcDbRasterVariables();

    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer) override;
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const override;

    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer) override;
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const override;

    virtual FrameSettings       imageFrame() const;
    virtual Acad::ErrorStatus   setImageFrame( FrameSettings value );

    virtual ImageQuality        imageQuality() const;
    virtual Acad::ErrorStatus   setImageQuality( ImageQuality value );

    virtual AcDbRasterImageDef::Units userScale() const;
    virtual Acad::ErrorStatus   setUserScale(
                                    AcDbRasterImageDef::Units units );

    static AcDbRasterVariables* openRasterVariables(
                                    AcDb::OpenMode mode,
                                    AcDbDatabase* pDatabase = 0
                                    );

private:

    // These are here because otherwise dllexport tries to export the
    // private methods of AcDbObject.  They're private in AcDbObject
    // because vc5 does not properly support array new and delete.
    // It tends to call the wrong delete operator and to not call
    // the dtors on all elements in the array.  So we make them
    // private in order to prevent usage of them.
    //
    void *operator new[](size_t) throw() { return 0;}
    void operator delete[](void *) {};
    void *operator new[](size_t, const char *, int) throw() { return 0;}

    // Data members
    //
    AcDbImpRasterVariables*     mpImp;
    static ClassVersion         mVersion;
};

inline ClassVersion
AcDbRasterVariables::classVersion()
{   return mVersion; }

#pragma warning( default : 4275 ) 


#pragma pack (pop)
#endif  // __IMGVARS_H
