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
// Description:
//
// This file implements the class AcGeFiler, which defines the
// abstract interface for serialization requirements of ge entities. 
// An application that requires input/output of the definition of
// ge entities in a format defined by the application should provide 
// an implementation of this class.  An instance of this class is
// provided as an argument to the entity serialization functions, 
// thus allowing the input/output format to be controlled by the 
// client of gelib. An example of usage would be as follows.
//
// AcRfDwgFiler  format;
// AcGeVersion   dbVersion;
// AcGeLine3d    newLine;
// if (acmeGetGelibImageVersion(entity, dbVersion) == AcMe::eOk) 
// {
//     AcGeDwgIO::read(format, dbVersion, newLine) 
//     AcGeDwgIO::write(format, newLine)
// }
//

#ifndef AC_GEFILER_H
#define AC_GEFILER_H   

#include "AdAChar.h"
#include "gegbl.h"
#include "acdb.h"
#include "acadstrc.h"
#pragma pack (push, 8)
     
     
class AcDbDwgFiler;
class AcGePoint2d;
class AcGePoint3d;
class AcGeVector2d;
class AcGeVector3d;
class AcString;

class 
GE_DLLEXPIMPORT ADESK_NO_VTABLE
AcGeFiler
{
protected:
    AcGeFiler();
public:
    // Read/write functions.
    //
    virtual
    Acad::ErrorStatus      readBoolean(Adesk::Boolean*) = 0; 
    virtual
    Acad::ErrorStatus      writeBoolean(Adesk::Boolean) = 0;

    virtual
    Acad::ErrorStatus      readBool(bool*) = 0; 
    virtual
    Acad::ErrorStatus      writeBool(bool) = 0;

    virtual
    Acad::ErrorStatus      readSignedByte(char *) = 0; 
    virtual
    Acad::ErrorStatus      writeSignedByte(char) = 0;
     
    virtual
    Acad::ErrorStatus      readString(AcString &) = 0; 
    virtual
    Acad::ErrorStatus      writeString(const AcString &) = 0;
     
    virtual
    Acad::ErrorStatus      readShort(short*) = 0; 
    virtual
    Acad::ErrorStatus      writeShort(short) = 0;
     
    virtual
    Acad::ErrorStatus      readLong(Adesk::Int32*) = 0; 
    virtual
    Acad::ErrorStatus      writeLong(Adesk::Int32) = 0;
     
    // Unicode: this is assumed to be a binary value, not a text character!
    virtual
    Acad::ErrorStatus      readUChar(unsigned char*) = 0; 
    virtual
    Acad::ErrorStatus      writeUChar(unsigned char) = 0;
     
    virtual
    Acad::ErrorStatus      readUShort(unsigned short*) = 0; 
    virtual
    Acad::ErrorStatus      writeUShort(unsigned short) = 0;
     
    virtual
    Acad::ErrorStatus      readULong(Adesk::UInt32*) = 0; 
    virtual
    Acad::ErrorStatus      writeULong(Adesk::UInt32) = 0;
          
    virtual
    Acad::ErrorStatus      readDouble(double*) = 0; 
    virtual
    Acad::ErrorStatus      writeDouble(double) = 0;
     
    virtual
    Acad::ErrorStatus      readPoint2d(AcGePoint2d*) = 0; 
    virtual
    Acad::ErrorStatus      writePoint2d(const AcGePoint2d&) = 0;
     
    virtual
    Acad::ErrorStatus      readPoint3d(AcGePoint3d*) = 0; 
    virtual
    Acad::ErrorStatus      writePoint3d(const AcGePoint3d&) = 0;
     
    virtual
    Acad::ErrorStatus      readVector2d(AcGeVector2d*) = 0; 
    virtual
    Acad::ErrorStatus      writeVector2d(const AcGeVector2d&) = 0;
     
    virtual
    Acad::ErrorStatus      readVector3d(AcGeVector3d*) = 0; 
    virtual
    Acad::ErrorStatus      writeVector3d(const AcGeVector3d&) = 0;
     
    // This method must be implemented in order to read/write 
    // external curves and surfaces (and nurb surfaces). 
    virtual
    AcDbDwgFiler*          dwgFiler();

    virtual
    Acad::ErrorStatus      readBytes(void*, Adesk::UInt32) = 0;
    virtual
    Acad::ErrorStatus      writeBytes(const void*, Adesk::UInt32) = 0;
};

inline
AcDbDwgFiler* AcGeFiler::dwgFiler()
{
    return NULL;
}
     
     
#pragma pack (pop)
#endif
