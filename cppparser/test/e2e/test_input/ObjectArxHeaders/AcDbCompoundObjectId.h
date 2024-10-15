//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
// DESCRIPTION:
//
// Declaration of the AcDbCompoundObjectId class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbCore2dDefs.h"
#pragma pack (push, 8)


/// <summary><para>
/// Class used to identify an AcDbObject in an AcDbDatabase when the object is
/// references via a path of AcDbBlockReferences, and possibly by some other
/// ways in the future. The object may reside in the host database (the same 
/// database as the AcDbCompoundObjectId belongs to) or it may reside in an XREF
/// database or even in an unrelated database.
/// </para><para>
/// Notice that if the AcDbCompoundObjectId references an object in another 
/// database, reactors will be created to keep tract of relevant events happening 
/// to the database, such as database deletion or XREF unload/reload.
/// </para></summary> 
///
class ACDBCORE2D_PORT AcDbCompoundObjectId : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbCompoundObjectId);

    /// <summary> 
    /// The default constructor creates an empty AcDbCompoundObjectId.
    /// </summary> 
    ///
    AcDbCompoundObjectId();

    /// <summary> 
    /// Creates AcDbCompoundObjectId from an ordinary AcDbObjectId. If the
    /// host database is null, the host database is obtained from the given 
    /// AcDbObjectId. Even if it is in XREF database, the database hosting the 
    /// XREF is obtained.
    /// </summary>
    /// <param name="id"> AcDbObjectId of the AcDbObject that this AcDbCompoundObjectId 
    /// is going to reference. </param>
    /// <param name="pHostDatabase"> The host database. If null, the database 
    /// is taken from the AcDbObjectId (even if it is in XREF database). </param>
    ///
    AcDbCompoundObjectId(const AcDbObjectId& id, AcDbDatabase* pHostDatabase = NULL);

    /// <summary> Copy constructor. </summary> 
    ///
    AcDbCompoundObjectId(const AcDbCompoundObjectId&);

    /// <summary> 
    /// Creates AcDbCompoundObjectId from an ordinary AcDbObjectId and a path
    /// of AcDbBlockReferences. If the host database is null, the host database 
    /// is obtained from the first id in the path. Even if it is in XREF database, 
    /// the database hosting the XREF is obtained.
    /// </summary>
    /// <param name="id"> AcDbObjectId of the AcDbObject that this AcDbCompoundObjectId 
    /// is going to reference. </param>
    /// <param name="path"> The path of AcDbBlockReferences that lead to the
    /// referenced object. The first AcDbBlockReference in the path resides in the 
    /// host database, the second AcDbBlockReference is from the AcDbBlockTableRecord
    /// that the first AcDbBlockReference references, the third AcDbBlockReference 
    /// is from the AcDbBlockTableRecord that the second AcDbBlockReference 
    /// references, etc. </param>
    /// <param name="pHostDatabase"> The host database. If null, the database 
    /// is taken from the first AcDbBlockReference id in the path (even if it is 
    /// in XREF database). </param>
    ///
    AcDbCompoundObjectId(const AcDbObjectId& id, const AcDbObjectIdArray& path, AcDbDatabase* pHostDatabase = NULL);

    virtual ~AcDbCompoundObjectId();

    AcDbCompoundObjectId& operator =(const AcDbObjectId&);
    AcDbCompoundObjectId& operator =(const AcDbCompoundObjectId&);

    bool operator ==(const AcDbCompoundObjectId&) const;
    bool operator !=(const AcDbCompoundObjectId& other) const { return !(*this == other); }

    /// <summary> Returns the first AcDbObjectId (of an AcDbBlockReference) 
    /// in the path, or the leaf-node AcDbObjectId, if there is no path.
    /// </summary>
    ///
    AcDbObjectId topId() const; 

    /// <summary> Returns the leaf-node AcDbObjectId that resides in the 
    /// AcDbBlockTableRecord that the last AcDbBlockReference in the path references, 
    /// or simply the AcDbObjectId if there is no path. 
    /// </summary>
    ///
    AcDbObjectId leafId() const;

    /// <summary> Returns the full path, i.e. the given path of AcDbBlockReference
    /// ids appended with the leaf AcDbObjectId.
    /// </summary>
    ///
    Acad::ErrorStatus getFullPath(AcDbObjectIdArray& fullPath) const; // path + leaf object

    /// <summary> Returns the AcDbBlockReference path. </summary>
    ///
    Acad::ErrorStatus getPath(AcDbObjectIdArray& path) const;

    /// <summary> Sets the AcDbCompoundObjectId to be empty, containing no data. </summary>
    ///
    void setEmpty();

    /// <summary> 
    /// Sets this AcDbCompoundObjectId from an ordinary AcDbObjectId. If the
    /// host database is null, the host database is obtained from the given 
    /// AcDbObjectId. Even if it is in XREF database, the database hosting the 
    /// XREF is obtained.
    /// </summary>
    /// <param name="id"> AcDbObjectId of the AcDbObject that this AcDbCompoundObjectId 
    /// is going to reference. </param>
    /// <param name="pHostDatabase"> The host database. If null, the database 
    /// is taken from the AcDbObjectId (even if it is in XREF database). </param>
    ///
    Acad::ErrorStatus set(const AcDbObjectId&, AcDbDatabase* pHostDatabase = NULL);

    /// <summary> Sets this AcDbCompoundObjectId from another AcDbCompoundObjectId. </summary>
    ///
    Acad::ErrorStatus set(const AcDbCompoundObjectId&, AcDbDatabase* pHostDatabase = NULL);

    /// <summary> 
    /// Sets this AcDbCompoundObjectId from an ordinary AcDbObjectId and a path
    /// of AcDbBlockReferences. If the host database is null, the host database 
    /// is obtained from the first id in the path. Even if it is in XREF database, 
    /// the database hosting the XREF is obtained.
    /// </summary>
    /// <param name="id"> AcDbObjectId of the AcDbObject that this AcDbCompoundObjectId 
    /// is going to reference. </param>
    /// <param name="path"> The path of AcDbBlockReferences that lead to the
    /// referenced object. The first AcDbBlockReference in the path resides in the 
    /// host database, the second AcDbBlockReference is from the AcDbBlockTableRecord
    /// that the first AcDbBlockReference references, the third AcDbBlockReference 
    /// is from the AcDbBlockTableRecord that the second AcDbBlockReference 
    /// references, etc. </param>
    /// <param name="pHostDatabase"> The host database. If null, the database 
    /// is taken from the first AcDbBlockReference id in the path (even if it is 
    /// in XREF database). </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus set(const AcDbObjectId& id, const AcDbObjectIdArray& path, AcDbDatabase* pHostDatabase = NULL);

    /// <summary> Sets this AcDbCompoundObjectId from the path that contains the 
    /// path of AcDbBlockReferences apppended by the leaf AcDbObjectId. 
    /// </summary> 
    /// <param name="fullPath"> The path of AcDbBlockReferences and the leaf level 
    /// object itself as the last element of the array.
    /// </param>
    /// <param name="pHostDatabase"> The host database. If null, the database 
    /// is taken from the first AcDbBlockReference id in the fullPath. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus setFullPath(const AcDbObjectIdArray& fullPath, AcDbDatabase* pHostDatabase = NULL);

    /// <summary> Checks if the AcDbCompoundObjectId contains no data. </summary>
    ///
    bool isEmpty() const;

    /// <summary> Returns true if the AcDbCompoundObjectId is valid. The given
    /// validityCheckingLevel specifies the level of testing. Bigger number means
    /// more thorough checks are being performed. At this moment the 
    /// validityCheckingLevel argument is unused but will be used in the future.
    /// </summary>
    ///
    bool isValid(int validityCheckingLevel = 1) const;

    /// <summary> Returns true if the AcDbCompoundObjectId is from an external 
    /// drawing. </summary>
    ///
    bool isExternal() const;

    /// <summary> Returns true if there is no path, only the leaf id (which may be null). 
    /// </summary>
    ///
    bool isSimpleObjectId() const;

    enum Status 
    {
        kValid                      = 0,  // Good to go, can be Null
        kWasLoadedNowUnloaded       = 1,  // Loaded during dwgOpen, then xref was unloaded
        kCouldNotResolveNonTerminal = 2,  // Couldn't be resolved - xref not found, unloaded when last saved, etc. non-terminal
        kCouldNotResolveTerminal    = 3,  // Couldn't be resolved, bad sceario - xref dwg replaced, not referenced, etc.
        kCouldNotResolveTooEarly    = 4,  // Couldn't be resolved yet - too early - xref not finished resolving
        kIncompatibleIdType         = 1000,
    };

    Status status() const;

    /// <summary> 
    /// Returns the compound transform from the leaf object to the world,
    /// concatennating all the AcDbBlockReference transforms, from the most nested
    /// one to the topmost one. This transformation represents mapping of the
    /// coordinates of the leaf-level object from its AcDbBlockTableRecord 
    /// coordinate space to the world coordinate space.
    /// </summary>
    /// <param name="trans"> The returned compound transform. </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus getTransform(AcGeMatrix3d& trans) const;

    /// <summary> Remaps all the AcDbObjectIds in this AcDbCompoundObjectId by 
    /// the given AcDbIdMapping. Returns true if any remapping actually happened, 
    /// false otherwise. </summary>
    /// <param name="idMap"> See the description of the AcDbIdMapping class. </param>
    /// <returns> True if some ids actually changed, false otherwise. </returns>
    ///
    bool remap(const AcDbIdMapping& idMap);  

    Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler, AcDbDatabase* pHostDatabase) const;

    /// <remarks>
    /// The ownerVersion greater or equal to 0 means the new format, less than 0
    /// means the old format (w/o the class name and object version) that we need 
    /// to maintain only to be able to read Beta1/2 drawings.
    /// </remarks>
    ///
    Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler, int ownerVersion);

    Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler, AcDbDatabase* pHostDatabase) const;

    /// <remarks>
    /// The ownerVersion greater or equal to 0 means the new format, less than 0
    /// means the old format (w/o the class name and object version) that we need 
    /// to maintain only to be able to read Beta1/2 drawings.
    /// </remarks>
    ///
    Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler, AcDbDatabase* pHostDatabase, int ownerVersion);

    /// <summary> Returns an empty AcDbCompoundObjectId. </summary> 
    ///
    static const AcDbCompoundObjectId& nullId();

private:
    class AcDbImpCompoundObjectId* mpImp;
};


/// <summary>
/// Protocol extension used by AcDbCompoundObjectId::getTransform() to find the 
/// transform that the parent object applies to its child object, if the AcDbCompoundObjectId 
/// contains a whole path of objects. For example for AcDbBlockReference the returned 
/// transform is AcDbBlockReference::blockTransform(). If the path contains other parent 
/// objects than AcDbBlockReference (it seems to be allowed, e.g. the parent object may
/// be a custom entity), the parent object may specify the transform. If the parent object
/// does not expose this PE, an identify transform is assumed.
/// </summary>
///
class ACDBCORE2D_PORT AcDbParentTransformOfChildPE : public AcRxObject
{
public:
	ACRX_DECLARE_MEMBERS(AcDbParentTransformOfChildPE);

    /// <summary>
    /// Returns the transform of the child object in the parent object.
    /// </summary>
    ///
    virtual Acad::ErrorStatus getParentTransformOfChild(const AcDbObject* pThisParent, const AcDbObjectId& childId, AcGeMatrix3d&) = 0;
};

#pragma pack (pop)
