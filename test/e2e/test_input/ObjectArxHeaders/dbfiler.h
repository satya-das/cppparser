#ifndef AD_DBFILER_H
#define AD_DBFILER_H
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
// DBFILER.H  -- AutoCAD Database Filer Definitions
//
// DESCRIPTION:
//
// This file contains "filer" class definitions, which are passed to
// AcDbObject objects by their parent AcDbDatabase object to
// perform I/O operations in various contexts.
//
// Common Filer Contracts are:
//
// 1. The Database object always controls the creation of the
//    filers, and passing them to objects.  The Database object
//    itself surrounds filing calls with I/O of class name/ID/DXF_name
//    maps, and common object information such as class IDs/DXF names,
//    checksums, record lengths and other common record information.
//    The database object also handles file section and object
//    sentinels for database recovery purposes.
//
// 2. For different I/O contexts, 3 different sets of AcDbObject
//    members are defined:  DXF, DWG File, and Paging
//    While DWG File and Paging members are supplied pagers of the
//    same abstract class, implementations of some members,
//    particularly those concerned with AcDbObjectId and AcDbHandle objects,
//    are very different.  Usage contract differs as follows, reason being
//    that notification chains are NOT limited to database objects:
//
//    Paging:  For Notification chains, use "void" filer method to
//               save/restore pointer.  Do not bother to pull out
//               of other notification chains.
//
//    DWG file: Pull out of other notification chains, and record
//                what is needed for reconstruction.
//
// 3. The filer methods of AcDbObject subclasses are named the same
//    as the parent class's methods, with "Fields" appended (as in
//    dwgInFields()).  Each such method (with a few exceptions in
//    class AcDbEntity) must invoke the same method in its parent
//    *before* performing any of its own filing actions.

#include <stdarg.h>
#include "AdAChar.h"
#include "acdb.h"
#include "rxobject.h"
#include "rxboiler.h"


#pragma pack (push, 8)

class AcDbAuditInfo;
class AcDbDatabase;
class AcDbFilerController;
class AcDbHandle;
class AcDbHardOwnershipId;
class AcDbSoftOwnershipId;
class AcDbHardPointerId;
class AcDbSoftPointerId;
class AcDbIdRefQueue;
class AcDbObjectId;
class AcGePoint2d;
class AcGePoint3d;
class AcGeScale3d;
class AcGeVector2d;
class AcGeVector3d;
class AcString;
struct resbuf;
struct ads_binary;

class ADESK_NO_VTABLE AcDbDwgFiler: public AcRxObject
// 
// Abstract class for DWG file and object I/O.  While protocol is virtually
// the same, the implementations will be different, and so will usage.  DWG
// filer will do byte-reversal, and convert AcDbStub and AcDbHandle values
// to/from char* values
//
// For each filer data type Xxx, there is a pair of write functions
// writeXxx(Xxx) and writeItem(Xxx).  The writeItem() functions, defined
// inline in terms of the writeXxx() functions, can be used when it is
// convenient or appropriate to let the argument type determine which function
// to call.  The writeXxx() functions are pure-virtual, i.e., must be defined
// by all concrete subclasses.
// 
// The same applies to the read functions.
// 
// Filers may also implement CRC accumulation. 
// 
{
  public:
    ACRX_DECLARE_MEMBERS(AcDbDwgFiler);
  protected:
    ACDBCORE2D_PORT AcDbDwgFiler();
  public:
    ACDBCORE2D_PORT virtual ~AcDbDwgFiler();

    virtual  Acad::ErrorStatus filerStatus() const = 0;
    virtual  AcDb::FilerType   filerType() const = 0;
    virtual void               setFilerStatus(Acad::ErrorStatus es) = 0;
    virtual void               resetFilerStatus() = 0;

    // version of the drawing file being read or written by this filer

    virtual  Acad::ErrorStatus  dwgVersion(AcDb::AcDbDwgVersion& ver,
                                AcDb::MaintenanceReleaseVersion& maintVer) const;

    ACDBCORE2D_PORT virtual  Acad::ErrorStatus  extendedDwgMaintenanceReleaseVersion(
                                                AcDb::MaintenanceReleaseVersion& maintVer) const;

    //        readXxx() and writeXxx() functions
    //
    virtual Acad::ErrorStatus   readHardOwnershipId(AcDbHardOwnershipId* pVal) = 0;
    virtual Acad::ErrorStatus   writeHardOwnershipId(
                                  const AcDbHardOwnershipId& val) = 0;

    virtual Acad::ErrorStatus   readSoftOwnershipId(AcDbSoftOwnershipId* pVal) = 0;
    virtual Acad::ErrorStatus   writeSoftOwnershipId(
                                  const AcDbSoftOwnershipId& val) = 0;

    virtual Acad::ErrorStatus   readHardPointerId(AcDbHardPointerId* pVal) = 0;
    virtual Acad::ErrorStatus   writeHardPointerId(const AcDbHardPointerId& val) = 0;

    virtual Acad::ErrorStatus   readSoftPointerId(AcDbSoftPointerId* pVal) = 0;
    virtual Acad::ErrorStatus   writeSoftPointerId(const AcDbSoftPointerId& val) = 0;

    virtual Acad::ErrorStatus   readInt8(Adesk::Int8* pVal) = 0;
    virtual Acad::ErrorStatus   writeInt8(Adesk::Int8 val) = 0;

    // Note: use of readString(ACHAR **) is discouraged, because
    // caller has to free the returned string.  It may be phased
    // out in a future release.
    virtual Acad::ErrorStatus   readString(ACHAR** pVal) = 0;
    virtual Acad::ErrorStatus   writeString(const ACHAR* pVal) = 0;

    virtual Acad::ErrorStatus   readString(AcString& val) = 0;
    virtual Acad::ErrorStatus   writeString(const AcString& pVal) = 0;

    virtual Acad::ErrorStatus   readBChunk(ads_binary* pVal) = 0;
    virtual Acad::ErrorStatus   writeBChunk(const ads_binary&) = 0;

    virtual Acad::ErrorStatus   readAcDbHandle(AcDbHandle* pVal) = 0;
    virtual Acad::ErrorStatus   writeAcDbHandle(const AcDbHandle& val) = 0;

    virtual Acad::ErrorStatus   readInt64(Adesk::Int64* pVal) = 0;
    virtual Acad::ErrorStatus   writeInt64(Adesk::Int64 val) = 0;

    virtual Acad::ErrorStatus   readInt32(Adesk::Int32* pVal) = 0;
    virtual Acad::ErrorStatus   writeInt32(Adesk::Int32 val) = 0;

    virtual Acad::ErrorStatus   readInt16(Adesk::Int16* pVal) = 0;
    virtual Acad::ErrorStatus   writeInt16(Adesk::Int16 val) = 0;

    virtual Acad::ErrorStatus   readUInt64(Adesk::UInt64* pVal) = 0;
    virtual Acad::ErrorStatus   writeUInt64(Adesk::UInt64 val) = 0;

    virtual Acad::ErrorStatus   readUInt32(Adesk::UInt32* pVal) = 0;
    virtual Acad::ErrorStatus   writeUInt32(Adesk::UInt32 val) = 0;

    virtual Acad::ErrorStatus   readUInt16(Adesk::UInt16* pVal) = 0;
    virtual Acad::ErrorStatus   writeUInt16(Adesk::UInt16 val) = 0;

    virtual Acad::ErrorStatus   readUInt8(Adesk::UInt8* pVal) = 0;
    virtual Acad::ErrorStatus   writeUInt8(Adesk::UInt8 val) = 0;

    virtual Acad::ErrorStatus   readBoolean(Adesk::Boolean* pVal) = 0;
    virtual Acad::ErrorStatus   writeBoolean(Adesk::Boolean val) = 0;

    virtual Acad::ErrorStatus   readBool(bool* pVal) = 0;
    virtual Acad::ErrorStatus   writeBool(bool val) = 0;

    virtual Acad::ErrorStatus   readDouble(double* pVal) = 0;
    virtual Acad::ErrorStatus   writeDouble(double val) = 0;

    virtual Acad::ErrorStatus   readPoint2d(AcGePoint2d* pVal) = 0;
    virtual Acad::ErrorStatus   writePoint2d(const AcGePoint2d& val) = 0;

    virtual Acad::ErrorStatus   readPoint3d(AcGePoint3d* pVal) = 0;
    virtual Acad::ErrorStatus   writePoint3d(const AcGePoint3d& val) = 0;

    virtual Acad::ErrorStatus   readVector2d(AcGeVector2d* pVal) = 0;
    virtual Acad::ErrorStatus   writeVector2d(const AcGeVector2d& val) = 0;

    virtual Acad::ErrorStatus   readVector3d(AcGeVector3d* pVal) = 0;
    virtual Acad::ErrorStatus   writeVector3d(const AcGeVector3d& val) = 0;

    virtual Acad::ErrorStatus   readScale3d(AcGeScale3d* pVal) = 0;
    virtual Acad::ErrorStatus   writeScale3d(const AcGeScale3d& val) = 0;

    virtual Acad::ErrorStatus   readBytes(void* pDest, Adesk::UIntPtr nBytes) = 0;
    virtual Acad::ErrorStatus   writeBytes(const void* pSrc, Adesk::UIntPtr nBytes) = 0;

    virtual Acad::ErrorStatus   readAddress(void ** pVal);
    virtual Acad::ErrorStatus   writeAddress(const void * pVal);

    //        readItem() and writeItem() functions
    //
            Acad::ErrorStatus   readItem(AcDbHardOwnershipId* pId);
            Acad::ErrorStatus   writeItem(const AcDbHardOwnershipId& id);

            Acad::ErrorStatus   readItem(AcDbSoftOwnershipId* pId);
            Acad::ErrorStatus   writeItem(const AcDbSoftOwnershipId& id);

            Acad::ErrorStatus   readItem(AcDbHardPointerId* pId);
            Acad::ErrorStatus   writeItem(const AcDbHardPointerId& id);

            Acad::ErrorStatus   readItem(AcDbSoftPointerId* pId);
            Acad::ErrorStatus   writeItem(const AcDbSoftPointerId& id);

            // Note: there are no filer methods for explicitly reading or
            // writing a single text character.
            //
            Acad::ErrorStatus   readItem(ACHAR** pVal);
            Acad::ErrorStatus   writeItem(const ACHAR* val);
            Acad::ErrorStatus   writeItem(const AcString& val);
            Acad::ErrorStatus   readItem(ads_binary* pVal);
            Acad::ErrorStatus   writeItem(const ads_binary& val);

            Acad::ErrorStatus   readItem(AcDbHandle* pVal);
            Acad::ErrorStatus   writeItem(const AcDbHandle& val);

            Acad::ErrorStatus   readItem(Adesk::Int32* pVal);
            Acad::ErrorStatus   writeItem(Adesk::Int32 val);

            Acad::ErrorStatus   readItem(Adesk::Int16* pVal);
            Acad::ErrorStatus   writeItem(Adesk::Int16 val);

            Acad::ErrorStatus   readItem(Adesk::Int8* pVal);
            Acad::ErrorStatus   writeItem(Adesk::Int8 val);

            Acad::ErrorStatus   readItem(Adesk::UInt32* pVal);
            Acad::ErrorStatus   writeItem(Adesk::UInt32 val);

            Acad::ErrorStatus   readItem(Adesk::UInt16* pVal);
            Acad::ErrorStatus   writeItem(Adesk::UInt16 val);

            Acad::ErrorStatus   readItem(Adesk::UInt8* pVal);
            Acad::ErrorStatus   writeItem(Adesk::UInt8 val);

            Acad::ErrorStatus   readItem(Adesk::Boolean* pVal);
            Acad::ErrorStatus   writeItem(Adesk::Boolean val);
    
#if !defined(Adesk_Boolean_is_bool) 
#error "Unexpected Adesk::Boolean is not bool"
            // We only need this when Adesk_Boolean_is_bool is
            // not defined since we have it covered already in
            // the Adesk::Boolean overload.
            Acad::ErrorStatus   readItem(bool* pVal);
            Acad::ErrorStatus   writeItem(bool val);
#endif
    
            Acad::ErrorStatus   readItem(double* pVal);
            Acad::ErrorStatus   writeItem(double val);

            Acad::ErrorStatus   readItem(AcGePoint2d* pVal);
            Acad::ErrorStatus   writeItem(const AcGePoint2d& val);

            Acad::ErrorStatus   readItem(AcGePoint3d* pVal);
            Acad::ErrorStatus   writeItem(const AcGePoint3d& val);

            Acad::ErrorStatus   readItem(AcGeVector2d* pVal);
            Acad::ErrorStatus   writeItem(const AcGeVector2d& val);

            Acad::ErrorStatus   readItem(AcGeVector3d* pVal);
            Acad::ErrorStatus   writeItem(const AcGeVector3d& val);

            Acad::ErrorStatus   readItem(AcGeScale3d* pVal);
            Acad::ErrorStatus   writeItem(const AcGeScale3d& val);

            Acad::ErrorStatus   readItem(void* pDest, Adesk::UIntPtr nBytes);
            Acad::ErrorStatus   writeItem(const void* pSrc, Adesk::UIntPtr nBytes);

            Acad::ErrorStatus   readItem(void** pp);
            Acad::ErrorStatus   writeItem(const void* p);

    virtual Acad::ErrorStatus   seek(Adesk::Int64 nOffset, int nMethod) = 0;
    virtual Adesk::Int64        tell() const = 0;
    virtual Acad::ErrorStatus   addReferences(AcDbIdRefQueue& /*qToAbsorb*/);
    virtual              bool   usesReferences() const;
    virtual AcDbAuditInfo *     getAuditInfo() const;

    virtual AcDbFilerController& controller() const;

private:
    AcDbDwgFiler & operator = (const AcDbDwgFiler &); // supress C4512 as we have a reference as data member

            AcDbFilerController& mController;
};


class ADESK_NO_VTABLE AcDbDxfFiler: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbDxfFiler);

    virtual int               rewindFiler() = 0;

    virtual Acad::ErrorStatus filerStatus() const = 0;
    virtual void              resetFilerStatus() = 0;

    virtual Acad::ErrorStatus setError(Acad::ErrorStatus es, const ACHAR* errMsg, ...);
    virtual Acad::ErrorStatus setError(const ACHAR* errMsg, ...);
    virtual const ACHAR* errorMessage() const;

    virtual  AcDb::FilerType filerType() const = 0;

    // working database being read or written by this filer
    virtual  AcDbDatabase*      database() const = 0;

    // version of the drawing file being read or written by this filer

    virtual  Acad::ErrorStatus  dwgVersion(AcDb::AcDbDwgVersion& ver,
                                AcDb::MaintenanceReleaseVersion& maintVer) const;

    ACDBCORE2D_PORT virtual  Acad::ErrorStatus  extendedDwgMaintenanceReleaseVersion(
                                                AcDb::MaintenanceReleaseVersion& maintVer) const;

    virtual int                 precision() const;
    virtual void                setPrecision(int prec);

    // Number of decimal digits printed in ASCII DXF file
    //
    enum { kDfltPrec = -1, kMaxPrec  = 16 };

    //        readXxx and writeXxx functions
    //
    virtual Acad::ErrorStatus readResBuf   (resbuf* pRb);
    virtual Acad::ErrorStatus writeResBuf  (const resbuf& rb);
    virtual Acad::ErrorStatus writeObjectId(AcDb::DxfCode code,
                                            const AcDbObjectId& id) = 0;
    virtual Acad::ErrorStatus writeInt8    (AcDb::DxfCode code, Adesk::Int8) = 0;

    virtual Acad::ErrorStatus writeString  (AcDb::DxfCode code, const ACHAR* pVal) = 0;
    virtual Acad::ErrorStatus writeString  (AcDb::DxfCode code, const AcString& pVal) = 0;
    virtual Acad::ErrorStatus writeBChunk  (AcDb::DxfCode code, const ads_binary& val) = 0;
    virtual Acad::ErrorStatus writeAcDbHandle(AcDb::DxfCode code,
                                              const AcDbHandle& val) = 0;
    virtual Acad::ErrorStatus writeInt64   (AcDb::DxfCode code, Adesk::Int64 val) = 0;
    virtual Acad::ErrorStatus writeInt32   (AcDb::DxfCode code, Adesk::Int32 val) = 0;
    virtual Acad::ErrorStatus writeInt16   (AcDb::DxfCode code, Adesk::Int16 val) = 0;
    virtual Acad::ErrorStatus writeUInt64  (AcDb::DxfCode code, Adesk::UInt64 val) = 0;
    virtual Acad::ErrorStatus writeUInt32  (AcDb::DxfCode code, Adesk::UInt32 val) = 0;
    virtual Acad::ErrorStatus writeUInt16  (AcDb::DxfCode code, Adesk::UInt16 val) = 0;
    virtual Acad::ErrorStatus writeUInt8   (AcDb::DxfCode code, Adesk::UInt8 val) = 0;
    virtual Acad::ErrorStatus writeBoolean (AcDb::DxfCode code, Adesk::Boolean val) = 0;
    virtual Acad::ErrorStatus writeBool    (AcDb::DxfCode code, bool val) = 0;
    virtual Acad::ErrorStatus writeDouble  (AcDb::DxfCode code, double val,
                                            int prec = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writePoint2d (AcDb::DxfCode code, const AcGePoint2d& val,
                                            int prec = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writePoint3d (AcDb::DxfCode code, const AcGePoint3d& val,
                                               int prec = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writeVector2d(AcDb::DxfCode code, const AcGeVector2d& val,
                                            int prec = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writeVector3d(AcDb::DxfCode code, const AcGeVector3d& val,
                                            int prec = kDfltPrec) = 0;
    virtual Acad::ErrorStatus writeScale3d (AcDb::DxfCode code, const AcGeScale3d& val,
                                            int prec = kDfltPrec) = 0;

    //        readItem and writeItem functions
    //
    Acad::ErrorStatus readItem        (resbuf* pItem);
    Acad::ErrorStatus writeItem (const resbuf& pItem);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcDbObjectId& id);

    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const ACHAR* val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcString& val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const ads_binary& val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcDbHandle& val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, Adesk::Int32 val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, Adesk::Int16 val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, Adesk::Int8 val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, Adesk::UInt32 val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, Adesk::UInt16 val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, Adesk::UInt8 val);

#ifndef Adesk_Boolean_is_bool
    // CAUTION: "int" parameters go to writeBoolean when Adesk_Boolean_is_bool
    // is not defined. When it is defined, the bool overload handles this
    // case.
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, Adesk::Boolean val);
#endif

    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, bool val);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, double val, int = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcGePoint2d& val,
                                 int prec = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcGePoint3d& val,
                                 int prec = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcGeVector2d& val,
                                 int prec = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcGeVector3d& val,
                                 int prec = kDfltPrec);
    Acad::ErrorStatus writeItem (AcDb::DxfCode dc, const AcGeScale3d& val,
                                 int prec = kDfltPrec);
    virtual Acad::ErrorStatus writeXDataStart ();
    virtual bool              includesDefaultValues() const = 0;

    virtual Acad::ErrorStatus pushBackItem();
    virtual bool              atEOF();
    virtual bool              atSubclassData(const ACHAR* subClassName);
    virtual bool              atExtendedData();
    virtual bool              atEndOfObject();
    virtual void              haltAtClassBoundaries(bool halt);

    virtual Acad::ErrorStatus writeEmbeddedObjectStart();
    virtual bool              atEmbeddedObjectStart();

    virtual double elevation() const;
    virtual double thickness() const;

    virtual bool              isModifyingExistingObject() const;

    AcDbDxfFiler();
    virtual ~AcDbDxfFiler();
    AcDbFilerController& controller() const;

private:
    AcDbDxfFiler & operator = (const AcDbDxfFiler &); // supress C4512 as we have a reference as data member

    AcDbFilerController& mController;
    virtual Acad::ErrorStatus setVAError(Acad::ErrorStatus, const ACHAR *,
                                         va_list);
};

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbHardOwnershipId* pId)
{   return readHardOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbHardOwnershipId& pId)
{   return writeHardOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbSoftOwnershipId* pId)
{   return readSoftOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbSoftOwnershipId& pId)
{   return writeSoftOwnershipId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbHardPointerId* pId)
{   return readHardPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbHardPointerId& pId)
{   return writeHardPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbSoftPointerId* pId)
{   return readSoftPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbSoftPointerId& pId)
{   return writeSoftPointerId(pId); }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(ACHAR ** pVal)
{   return readString(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const ACHAR * val)
{   return writeString(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(ads_binary* pVal)
{   return readBChunk(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const ads_binary& val)
{   return writeBChunk(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcDbHandle* pVal)
{   return readAcDbHandle(pVal);    }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcDbHandle& val)
{   return writeAcDbHandle(val);    }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Int32* pVal)
{   return readInt32(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Int32 val)
{   return writeInt32(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Int16* pVal)
{   return readInt16(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Int16 val)
{   return writeInt16(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Int8 * pVal)
{   return this->readInt8(pVal);       }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Int8 val)
{   return this->writeInt8(val);       }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::UInt32* pVal)
{   return readUInt32(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::UInt32 val)
{   return writeUInt32(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::UInt16* pVal)
{   return readUInt16(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::UInt16 val)
{   return writeUInt16(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::UInt8* pVal)
{   return readUInt8(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::UInt8 val)
{   return writeUInt8(val);            }

#if !defined(Adesk_Boolean_is_bool)
inline Acad::ErrorStatus AcDbDwgFiler::readItem(Adesk::Boolean* pVal)
{   return readBoolean(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(Adesk::Boolean val)
{   return writeBoolean(val);            }
#endif

inline Acad::ErrorStatus AcDbDwgFiler::readItem(bool* pVal)
{   return readBool(pVal);              }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(bool val)
{   return writeBool(val);              }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(double* pVal)
{   return readDouble(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(double val)
{   return writeDouble(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGePoint2d* pVal)
{   return readPoint2d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGePoint2d& val)
{   return writePoint2d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGePoint3d* pVal)
{   return readPoint3d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGePoint3d& val)
{   return writePoint3d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGeVector2d* pVal)
{   return readVector2d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGeVector2d& val)
{   return writeVector2d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGeVector3d* pVal)
{   return readVector3d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGeVector3d& val)
{   return writeVector3d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(AcGeScale3d* pVal)
{   return readScale3d(pVal);            }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcGeScale3d& val)
{   return writeScale3d(val);            }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(void *buf, Adesk::UIntPtr cnt)
{   return readBytes(buf, cnt);     }

inline Acad::ErrorStatus 
AcDbDwgFiler::writeItem(const void *buf, Adesk::UIntPtr cnt)
{   return writeBytes(buf, cnt);    }

inline Acad::ErrorStatus AcDbDwgFiler::readItem(void **pp)
{   return readAddress(pp);            }

inline Acad::ErrorStatus 
AcDbDwgFiler::writeItem(const void *p)
{   return writeAddress(p);            }

inline Acad::ErrorStatus
AcDbDxfFiler::readItem(resbuf* pVal)
{   return readResBuf(pVal);         }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(const resbuf& val)
{   return writeResBuf(val);            }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcDbObjectId& id)
{   return writeObjectId(dc, id); }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const ACHAR * val)
{   return writeString(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const ads_binary& val)
{   return writeBChunk(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcDbHandle& val)
{   return writeAcDbHandle(dc, val);    }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Int32 val)
{   return writeInt32(dc, val);         }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Int16 val)
{   return writeInt16(dc, val);         }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Int8 val)
{   return this->writeInt8(dc, val);    }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::UInt32 val)
{   return writeUInt32(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::UInt16 val)
{   return writeUInt16(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::UInt8 val)
{   return writeUInt8(dc, val);         }

#if !defined(Adesk_Boolean_is_bool) 
inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, Adesk::Boolean val)
{   return writeBoolean(dc, val);        }
#endif

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, bool val)
{   return writeBool(dc, val);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, double val, int prec)
{   return writeDouble(dc, val, prec);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGePoint2d& val, int prec)
{   return writePoint2d(dc, val, prec); }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGePoint3d& val, int prec)
{   return writePoint3d(dc, val, prec); }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGeVector2d& val, int prec)
{   return writeVector2d(dc, val, prec);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGeVector3d& val, int prec)
{   return writeVector3d(dc, val, prec);        }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcGeScale3d& val, int prec)
{   return writeScale3d(dc, val, prec); }

inline Acad::ErrorStatus AcDbDwgFiler::writeItem(const AcString & val)
{   return writeString(val);            }

inline Acad::ErrorStatus
AcDbDxfFiler::writeItem(AcDb::DxfCode dc, const AcString & val)
{   return writeString(dc, val);        }

#pragma pack (pop)

#endif
