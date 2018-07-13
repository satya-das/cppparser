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
#include <vcclr.h>
#include <gcroot.h>
///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
//

// Unmanaged types
class AcGeVector2d;
class AcGeVector3d;
class AcGeMatrix2d;
class AcGeMatrix3d;
class AcGePoint2d;
class AcGePoint3d;
class AcGeScale2d;
class AcGeScale3d;
class AcGeTol;
class AcDbObjectId;
class AcDbExtents;

// Managed types
namespace Autodesk 
{
    namespace AutoCAD 
    {
        namespace Runtime
        {
#ifdef __cplusplus_cli
            ref class DisposableWrapper;
#else
            public __gc __abstract class DisposableWrapper;
#endif
        }
    }
}

#ifdef __cplusplus_cli
 #define AC_GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
 #define AC_VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))
 #define AC_NULLPTR nullptr
 #define AC_GCNEW gcnew
 #define AC_WCHAR_PINNED_GCPTR pin_ptr<const wchar_t>
 typedef Autodesk::AutoCAD::Runtime::DisposableWrapper^ DisposableWrapper_GcPtr;
 typedef System::Type^ Type_GcPtr;
 typedef System::String^ String_GcPtr;
#else
 #define AC_GCHANDLE_TO_VOIDPTR(x) ((GCHandle::op_Explicit(x)).ToPointer())
 #define AC_VOIDPTR_TO_GCHANDLE(x) (GCHandle::op_Explicit(x))
 #define AC_NULLPTR 0
 #define AC_GCNEW new
 #define AC_WCHAR_PINNED_GCPTR const wchar_t __pin*
 typedef Autodesk::AutoCAD::Runtime::DisposableWrapper* DisposableWrapper_GcPtr;
 typedef System::Type* Type_GcPtr;
 typedef System::String* String_GcPtr;
#endif

///////////////////////////////////////////////////////////////////////////////
// Classes
//

class AcMgObjectFactoryBase : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcMgObjectFactoryBase);
    virtual gcroot<DisposableWrapper_GcPtr> createRCW(AcRxObject* unmanagedPointer, bool autoDelete) = 0;
    virtual bool isManaged()
    {
        return false;
    }
    virtual ~AcMgObjectFactoryBase(){}
    virtual gcroot<Type_GcPtr> getType() = 0;

};


template <typename RCW, typename ImpObj>
class AcMgObjectFactory : public AcMgObjectFactoryBase
{
   
public:
    gcroot<DisposableWrapper_GcPtr> createRCW(AcRxObject* unmanagedPointer, bool autoDelete)
    {
        gcroot<DisposableWrapper_GcPtr> temp = AC_GCNEW RCW(System::IntPtr(static_cast<ImpObj*>(unmanagedPointer)),autoDelete);
        return temp;
    }
    AcMgObjectFactory()
    {
        ImpObj::desc()->addX(AcMgObjectFactoryBase::desc(),this);
    }
    ~AcMgObjectFactory()
    {
        ImpObj::desc()->delX(AcMgObjectFactoryBase::desc());
    }
    virtual gcroot<Type_GcPtr> getType() ADESK_OVERRIDE
    {
#ifdef __cplusplus_cli
        return RCW::typeid;
#else
        return __typeof(RCW);
#endif
    }
};

///////////////////////////////////////////////////////////////////////////////
// Data Marshalling
//

class StringToWchar
{
    typedef System::Runtime::InteropServices::GCHandle GCHandle;

    const wchar_t* m_ptr;
    void* m_pinner;
    
public:

    StringToWchar(String_GcPtr str)
    {
        //pin the string
        m_pinner = AC_GCHANDLE_TO_VOIDPTR(
            GCHandle::Alloc(str,System::Runtime::InteropServices::GCHandleType::Pinned)
            );
        AC_WCHAR_PINNED_GCPTR tmp = PtrToStringChars(str);
        m_ptr = tmp;
    }
    ~StringToWchar()
    {
   		GCHandle g = AC_VOIDPTR_TO_GCHANDLE(m_pinner);
		g.Free();
		m_pinner = 0;
    }
    operator const wchar_t*()
    {
        return m_ptr;
    }
}; 
inline String_GcPtr WcharToString(const wchar_t* value)
{
    return AC_GCNEW System::String(value);
}

#undef AC_GCHANDLE_TO_VOIDPTR
#undef AC_VOIDPTR_TO_GCHANDLE
#undef AC_NULLPTR
#undef AC_GCNEW


//these defines make legacy clients happy
#define StringToCIF StringToWchar
#define CIFToString WcharToString

#ifndef ACDBMGD

#define GETVECTOR3D(vec3d)  (*reinterpret_cast<AcGeVector3d*>(&(vec3d)))
#define GETVECTOR2D(vec2d)  (*reinterpret_cast<AcGeVector2d*>(&(vec2d)))
#define GETMATRIX3D(mat3d)  (*reinterpret_cast<AcGeMatrix3d*>(&(mat3d)))
#define GETMATRIX2D(mat2d)  (*reinterpret_cast<AcGeMatrix2d*>(&(mat2d)))
#define GETPOINT3D(point3d) (*reinterpret_cast<AcGePoint3d*>(&(point3d)))
#define GETPOINT2D(point2d) (*reinterpret_cast<AcGePoint2d*>(&(point2d)))
#define GETSCALE2D(scale2d) (*reinterpret_cast<AcGeScale2d*>(&(scale2d)))
#define GETSCALE3D(scale3d) (*reinterpret_cast<AcGeScale3d*>(&(scale3d)))
#define GETTOL(tol)         (*reinterpret_cast<AcGeTol*>(&(tol)))
#define GETOBJECTID(id)     (*reinterpret_cast<AcDbObjectId*>(&(id)))
#define GETEXTENTS3D(ext3d) (*reinterpret_cast<AcDbExtents*>(&(ext3d)))
#define GETSUBENTITYID(subentityId) (*reinterpret_cast<AcDbSubentId*>(&(subentityId)))

#ifdef AC_GEVEC3D_H
inline Autodesk::AutoCAD::Geometry::Vector3d ToVector3d(const AcGeVector3d& pt)
{
    Autodesk::AutoCAD::Geometry::Vector3d ret;
    GETVECTOR3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEVEC2D_H
inline Autodesk::AutoCAD::Geometry::Vector2d ToVector2d(const AcGeVector2d& pt)
{
    Autodesk::AutoCAD::Geometry::Vector2d ret;
    GETVECTOR2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEMAT2D_H
inline Autodesk::AutoCAD::Geometry::Matrix3d ToMatrix3d(const AcGeMatrix3d& pt)
{
    Autodesk::AutoCAD::Geometry::Matrix3d ret;
    GETMATRIX3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEMAT3D_H
inline Autodesk::AutoCAD::Geometry::Matrix2d ToMatrix2d(const AcGeMatrix2d& pt)
{
    Autodesk::AutoCAD::Geometry::Matrix2d ret;
    GETMATRIX2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEPNT3D_H
inline Autodesk::AutoCAD::Geometry::Point3d ToPoint3d(const AcGePoint3d& pt)
{
    Autodesk::AutoCAD::Geometry::Point3d ret;
    GETPOINT3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GEPNT2D_H
inline Autodesk::AutoCAD::Geometry::Point2d ToPoint2d(const AcGePoint2d& pt)
{
    Autodesk::AutoCAD::Geometry::Point2d ret;
    GETPOINT2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GESCL2D_H
inline Autodesk::AutoCAD::Geometry::Scale2d ToScale2d(const AcGeScale2d& pt)
{
    Autodesk::AutoCAD::Geometry::Scale2d ret;
    GETSCALE2D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GESCL3D_H
inline Autodesk::AutoCAD::Geometry::Scale3d ToScale3d(const AcGeScale3d& pt)
{
    Autodesk::AutoCAD::Geometry::Scale3d ret;
    GETSCALE3D(ret) = pt;
    return ret;
}
#endif

#ifdef AC_GETOL_H
inline Autodesk::AutoCAD::Geometry::Tolerance ToTolerance(const AcGeTol& pt)
{
    Autodesk::AutoCAD::Geometry::Tolerance ret;
    GETTOL(ret) = pt;
    return ret;
}
#endif

#ifdef _AD_DBID_H
inline Autodesk::AutoCAD::DatabaseServices::ObjectId ToObjectId(const AcDbObjectId& pt)
{
    Autodesk::AutoCAD::DatabaseServices::ObjectId ret;
    GETOBJECTID(ret) = pt;
    return ret;
}
#endif

#ifdef AD_DBMAIN_H
inline Autodesk::AutoCAD::DatabaseServices::Extents3d ToExtents3d(const AcDbExtents& pt)
{
    Autodesk::AutoCAD::DatabaseServices::Extents3d ret;
    GETEXTENTS3D(ret) = pt;
    return ret;
}
#endif

#endif // #ifndef ACDBMGD
