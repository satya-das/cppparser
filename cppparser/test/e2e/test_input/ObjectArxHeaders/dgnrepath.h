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

#include "acstring.h"
#include "acadstrc.h"

typedef Adesk::UInt64 AcDgnRefFileId;

struct AcDbDgnRefFileData {
    enum FileType{
        kDgnFile   = 1,
        kDwgFile   = 2,
        kImageFile = 3,
        kOtherFile = 4
    };
    FileType type;
    AcString savedPathAndName;
    AcString foundPathAndName;
    AcDgnRefFileId refId;
};

typedef AcArray<AcDbDgnRefFileData*> AcDbRefFileDataPtrArray;
typedef AcArray<AcDgnRefFileId>     AcDbDgnRefFileIdArray;

Acad::ErrorStatus
acdbGetDgnFileReferences(const ACHAR* fileName, const ACHAR* pwd,
    AcDbRefFileDataPtrArray& files);

class AcDbDgnRefFileRepath
{
public:
    AcDbDgnRefFileRepath() : m_fileHandle(NULL)  {};
    Acad::ErrorStatus setFile(const AcString& dgnPathAndFilename, const ACHAR* pwd);
    ~AcDbDgnRefFileRepath();
    Acad::ErrorStatus getReferenceFilePaths(AcDbRefFileDataPtrArray& refFiles);
    Acad::ErrorStatus rePath(const AcDbDgnRefFileIdArray& refFileIds,
        const AcStringArray& newRefFileNames);

private:
    void* m_fileHandle;
};