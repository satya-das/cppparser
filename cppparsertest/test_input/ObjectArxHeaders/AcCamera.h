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

#include "acdb.h"
#include "dbmain.h"
#include "dbents.h"

#pragma pack(push, 8)

// The following is part of the code used to export a API
// and/or use the exported API.
//
#pragma warning( disable: 4275 4251 )

#ifdef CAMERADLLIMPEXP
#undef CAMERADLLIMPEXP
#endif
#ifdef ACCAMERA_EXPORTS
#define CAMERADLLIMPEXP __declspec( dllexport )
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
#define CAMERADLLIMPEXP //__declspec( dllimport )
#endif

class AcDbImpCamera;

class CAMERADLLIMPEXP AcDbCamera: public AcDbEntity
{

public:
    //*************************************************************************
    // Constructors and Destructors
    //*************************************************************************
    AcDbCamera ();
    virtual ~AcDbCamera();
    ACDB_DECLARE_MEMBERS(AcDbCamera);

    //*************************************************************************
    // Camera Properties
    //*************************************************************************

    AcDbObjectId view() const; 
    Acad::ErrorStatus	setView(const AcDbObjectId viewId);

    //*************************************************************************
    // Overridden methods from AcDbObject
    //*************************************************************************
    virtual Acad::ErrorStatus   subErase(Adesk::Boolean erasing);
    virtual Acad::ErrorStatus   subOpen(AcDb::OpenMode openMode);
    virtual Acad::ErrorStatus   subClose();

    virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler* filer) const;
    
    virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler* filer) const;

protected:
    virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw*	mode);
    virtual void subViewportDraw(AcGiViewportDraw* mode);
    virtual Adesk::UInt32 subSetAttributes(AcGiDrawableTraits* pTraits);

    //*************************************************************************
    // Overridden methods from AcDbEntity
    //*************************************************************************
    virtual void              subList() const;
    virtual Acad::ErrorStatus subGetGripPoints(AcDbGripDataPtrArray& grips,
                                            const double curViewUnitSize,
                                            const int gripSize,
                                            const AcGeVector3d& curViewDir,
                                            const int bitflags) const;

    virtual Acad::ErrorStatus subMoveGripPointsAt(
                                            const AcDbVoidPtrArray& gripAppData,
                                            const AcGeVector3d& offset,
                                            const int bitflags);
    
    virtual Acad::ErrorStatus subGetStretchPoints(
                                            AcGePoint3dArray&  stretchPoints)
                                            const;
    virtual Acad::ErrorStatus subMoveStretchPointsAt(
                                            const AcDbIntArray& indices,
                                            const AcGeVector3d&     offset);
    virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);

    virtual Acad::ErrorStatus subDeepClone(AcDbObject* pOwnerObject,
        AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap,
        Adesk::Boolean isPrimary
        = Adesk::kTrue) const;
    
    virtual Acad::ErrorStatus subWblockClone(AcRxObject* pOwnerObject,
        AcDbObject*& pClonedObject,
        AcDbIdMapping& idMap,
        Adesk::Boolean isPrimary
        = Adesk::kTrue) const;
    
    virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const;

    virtual Acad::ErrorStatus subHighlight(const AcDbFullSubentPath& subId = kNullSubent, 
                                        const Adesk::Boolean highlightAll = Adesk::kFalse) const;
    virtual Acad::ErrorStatus subUnhighlight(const AcDbFullSubentPath& subId = kNullSubent, 
                                          const Adesk::Boolean highlightAll = Adesk::kFalse) const;

    virtual Acad::ErrorStatus subGetGeomExtents(AcDbExtents& extents) const;

private:
    friend class AcDbImpCamera;

    Adesk::UInt32       baseSetAttributes(AcGiDrawableTraits* pTraits);
    Acad::ErrorStatus   baseGetStretchPoints(AcGePoint3dArray&  stretchPoints) const;
    Acad::ErrorStatus   baseMoveStretchPointsAt(const AcDbIntArray & indices, const AcGeVector3d& offset);
    Acad::ErrorStatus   baseDeepClone(AcDbObject* pOwner,AcDbObject*& pClonedObject,
                                        AcDbIdMapping& idMap,Adesk::Boolean isPrimary) const;
    Acad::ErrorStatus   baseWblockClone(AcRxObject* pOwnerObject, AcDbObject*& pClonedObject, 
                                        AcDbIdMapping& idMap, Adesk::Boolean isPrimary) const;
    Acad::ErrorStatus   baseHighlight(const AcDbFullSubentPath& subId, 
                                        const Adesk::Boolean highlightAll) const;
    Acad::ErrorStatus   baseUnhighlight(const AcDbFullSubentPath& subId, 
                                        const Adesk::Boolean highlightAll) const;

    AcDbImpCamera* pImp;
};



#pragma pack (pop)
