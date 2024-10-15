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
#define SCENEDLLIMPEXP 
#endif

const ACHAR ACDB_NAMEDPATH_DICTIONARY[]  = /*MSG0*/ACRX_T("ACAD_NAMEDPATH");

Acad::ErrorStatus SCENEDLLIMPEXP acdbGetNamedPathDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                                            AcDb::OpenMode mode, bool createIfNonExist);
Acad::ErrorStatus SCENEDLLIMPEXP acdbGetNamedPathDictionary   (AcDbDatabase* pDb, AcDbDictionary*& pDict, 
                                                            AcDb::OpenMode mode);

class AcDbImpNamedPath;
class AcGeCurve3d;

class SCENEDLLIMPEXP AcDbNamedPath : public AcDbObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbNamedPath);
    virtual ~AcDbNamedPath();

    virtual Acad::ErrorStatus   getGeometry(AcGeCurve3d *& pCurveGeometry) const = 0;

protected:
    AcDbNamedPath (AcDbImpNamedPath* pImp);   
    AcDbImpNamedPath* imp() const; 

private:
    friend class AcDbImpNamedPath;
    AcDbImpNamedPath* mpImp;
};

class SCENEDLLIMPEXP AcDbCurvePath : public AcDbNamedPath
{
public:
    ACRX_DECLARE_MEMBERS(AcDbCurvePath);
    AcDbCurvePath();
    virtual ~AcDbCurvePath();

    virtual Acad::ErrorStatus   getGeometry(AcGeCurve3d *& pCurveGeometry) const;
    
    Acad::ErrorStatus   setGeometry(const AcDbObjectId& id);
    AcDbObjectId        entityId() const;

    // AcDbObject protocol
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

protected:
    // AcGiDrawable protocol
    //
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);

private:
    friend class AcDbImpCurvePath;

};

class SCENEDLLIMPEXP AcDbPointPath : public AcDbNamedPath
{
public:
    ACRX_DECLARE_MEMBERS(AcDbPointPath);
    AcDbPointPath();
    virtual ~AcDbPointPath();

    virtual Acad::ErrorStatus   getGeometry(AcGeCurve3d *& pCurveGeometry) const;
    
    Acad::ErrorStatus   setGeometry(const AcGePoint3d& pt);


    // AcDbObject protocol
    virtual Acad::ErrorStatus dwgInFields  (AcDbDwgFiler* pFiler);
    virtual Acad::ErrorStatus dwgOutFields (AcDbDwgFiler* pFiler) const;
    virtual Acad::ErrorStatus dxfInFields  (AcDbDxfFiler* pFiler);
    virtual Acad::ErrorStatus dxfOutFields (AcDbDxfFiler* pFiler) const;

protected:
    // AcGiDrawable protocol
    //
    virtual Adesk::UInt32  subSetAttributes (AcGiDrawableTraits* pTraits);

private:
#ifndef _ADESK_MAC_
    friend class AcDbPointPath;
#endif
};

#pragma pack(pop)

