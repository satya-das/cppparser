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
#include "dbmain.h"

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

const ACHAR ACDB_MOTIONPATH_DICTIONARY[]  = /*MSG0*/ACRX_T("ACAD_MOTION");

Acad::ErrorStatus SCENEDLLIMPEXP acdbGetMotionPathDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                                            AcDb::OpenMode mode, bool createIfNonExist);
Acad::ErrorStatus SCENEDLLIMPEXP acdbGetMotionPathDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                                            AcDb::OpenMode mode);

class AcDbImpMotionPath;

class SCENEDLLIMPEXP AcDbMotionPath : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbMotionPath);
	AcDbMotionPath();
    virtual ~AcDbMotionPath();

    AcDbObjectId        cameraPath() const;
    Acad::ErrorStatus   setCameraPath(const AcDbObjectId& id);

    AcDbObjectId        targetPath() const;
    Acad::ErrorStatus   setTargetPath(const AcDbObjectId& id);

    AcDbObjectId        viewTableRecordId() const;
    Acad::ErrorStatus   setViewTableRecordId(const AcDbObjectId& id);

    Adesk::UInt32       frames() const;
    Acad::ErrorStatus   setFrames(Adesk::UInt16 frames);

    Adesk::UInt32       frameRate() const;
    Acad::ErrorStatus   setFrameRate(Adesk::UInt16 rate);

    bool				cornerDecel() const;
    Acad::ErrorStatus   setCornerDecel(bool cornerDecel);

    // AcDbObject protocol
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

protected:
    // AcGiDrawable protocol
    //
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);
    
    AcDbImpMotionPath* imp() const; 

private:
    friend class AcDbImpMotionPath;
    AcDbImpMotionPath* mpImp;
};

