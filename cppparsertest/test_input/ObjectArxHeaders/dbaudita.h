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
//      Header file for auditing routines

#ifndef DB_DBAUDITA_H
#define DB_DBAUDITA_H 1

#include "AdAChar.h"

#pragma pack(push, 8)

class AcDbDatabase;
class AcDbAuditInfo;
class AcDbImpAuditInfo;
class AcDbAuditImp;
class AcDbObject;

// ACDB_AUDIT_RETURN
//
// This macro encapsulates the recommended "contract" for arbitrating
// audit return statuses between parent class status and local class
// status.  If either the parent class audit member fails or the
// local audit member fails, the object audit fails, with the parent
// class failure taking precedence.  The last parameter is a bool
// which specifies whether to "boil down" failure status to the
// recommended audit return values or return the direct local status.
// If this member doesn't supermessage a parent class, then pass in
// "eOk" for BaseEs. 
//
// if AcDbImpObject::audit failed,
// then the audit "fails"           
// else if local test succeeded,     
// then the audit "succeeds" so far, 
// return different bad status or    
//  "boil down" to accepted status     
// else if audit is to fix errors
// then say we fixed all errors 
// else we didn't fix them!     
// Return local status              
//
#define ACDB_AUDIT_RETURN(pAuditInfo, baseEs, localEs, boilDownLocalStatus)        \
    return (baseEs != eOk)                ?  \
               baseEs                     :  \
               (eOk == localEs)           ?  \
                   eOk                    :  \
                   boilDownLocalStatus    ?  \
                       (pAuditInfo->fixErrors()?  \
                           eFixedAllErrors     :  \
                           eLeftErrorsUnfixed) :  \
                       localEs;


class AcDbAuditInfo
{
public:

    friend class AcDbImpAuditInfo;
    friend class AcDbAuditImp;
    enum AuditPass {
            PASS1 = 1,
            PASS2 = 2
    };

    AcDbAuditInfo();
    ~AcDbAuditInfo();

    bool           fixErrors(void) const;        // True if errors are to
                                                 // be fixed.

    int numErrors() const;

    int numFixes(void) const;

    void errorsFound(int count);            // Specify the number     
                                            // of errors found.

    void errorsFixed(int count);            // Specify the number of 
                                            // errors fixed.

    AuditPass auditPass(void) const;        // The audit pass
                                            // number:
                                            // 1 = pass 1,
                                            // 2 = pass 2.
    void printError(const ACHAR * name,
                    const ACHAR * value, 
                    const ACHAR * validation,
                    const ACHAR * defaultValue);   // Print an error 
                                            // message string to the
                                            // Audit report file.
                                            // Obeys AUDITCTL.

    // Same as above except that name is automatically constructed
    // from the AcDbObject.
    //
    void printError(const AcDbObject *pObj,
                    const ACHAR * value, 
                    const ACHAR * validation,
                    const ACHAR * defaultValue);

    void requestRegen();

    void resetNumEntities();
    
    void incNumEntities();

    int numEntities();

    void printNumEntities(const ACHAR* msg);

    /// <summary>
    /// fetchObject is invoked from AcDbObject::audit() override members, as
    /// well as the AcDb recovery-audit complex.   Its purpose is to retrieve
    /// an object id based on the input object id.   It will usually be the
    /// same object id as is passed in, but can differ when recover logic
    /// creates new objects under new object ids.
    /// </summary>
    ///
    /// <param name="originalObjId">
    /// The object id read in from the DWG file.
    /// </param>
    ///
    /// <param name="newObjId">
    /// The object id to use insetad of originalObjId.
    /// </param>
    ///
    /// <param name="pObjClass">
    /// The anticipated class of the missing-corrupted object.
    /// </param>
    ///
    /// <param name="uneraseIfPossible">
    /// If true, and the referenced object is erased, it will be
    /// unerased if the object permits itself to be unerased.
    /// </param>
    ///
    /// <param name="createIfNotFound">
    /// Every call to fetchObject with this parameter set to true will
    /// cause the object recreation mechanism to be invoked.
    /// if false, then fetchObject will return results based on what is
    /// already in the lookup table.
    /// </param>
    ///
    /// <param name="externalDbOk">
    /// true implies that objId and newObjId can reside in another database.
    /// Note:  Not yet implemented.
    /// </param>
    ///
    /// <returns>
    /// The following ErrorStatus values can be returned from this function.
    /// eOk:                   Success, objId has a valid valuel
    /// eInvalidInput:         Errors include newObjId being NULL and pObjClass
    ///                        being NULL.
    /// eNotImplementedYet:    returned if externalDbOk is true and newObjId is
    ///                        from an external database.
    /// eInvalidXrefObjectId:  objId cannot be a forwarding reference to another
    ///                        object Id in an xref database.
    /// eWasErased:            if an object is erased and the uneraseIfPossible
    ///                        parameter is false or the object cannot be unerased.
    /// eNullObjectPointer and    
    /// eNullObjectId:         if a valid object cannot be returned for various
    ///                        reasons.
    /// </returns>
    ///
    /// <remarks>
    /// If eOk is returned, then newObjId will be valid and should be used (and
    /// will most often be the same as objId).
    /// If any other value is returned, then both objId and newObjId should be
    /// considered to be invalid.
    /// </remarks>
    ///
    Acad::ErrorStatus fetchObject(AcDbObjectId    originalObjId,
                                    AcDbObjectId& newObjId,
                                    AcRxClass*    pObjClass,
                                    bool          uneraseIfPossible = false,
                                    bool          createIfNotFound = true,
                                    bool          externalDbOk = false);

    /// <summary>
    /// registerObject is invoked from AcDb Recover and Audit internals, and can
    /// also be invoked from AcDbObject::audit(), dwgInFields() and any other
    /// override members invoked during a recover operation and its subsequent
    /// audit.   It is the easy way to make entries for valid objects, compared
    /// to AcDbAuditInfo::updateObject, which has a much more verbose parameter
    /// list.
    /// </summary>
    ///
    /// <param name="handle">
    /// The handle of the original object, readily obtainable from an object
    /// id as well.  It is the lookup key for indirect object lookup table
    /// entries.
    /// </param>
    ///
    /// <param name="objIsValid">
    /// A bool indicating whether the object is valid or not.  If true is
    /// passed in, then the entire lookup table entry is filled out with
    /// the handle pointing to its own object id as its replacement.
    /// </param>
    ///
    /// <param name="pObjClass">
    /// The anticipated or known class of the missing-corrupted object.
    /// </param>
    ///
    /// <returns>
    /// The following ErrorStatus values can be returned from this function.
    /// eOk:                   Success, objId has a valid value.
    /// eInvalidInput:         The input handle cannot be null (0).
    /// eHandleInUse:          Returned if this function is invoked more than
    ///                        once for the input handle in a single recover
    ///                        operation.
    /// </returns>
    ///
    /// <remarks>
    /// The Recover logic usually populates the indirect object table
    /// with entries that map object ids to themselves.   But it can be invoked by
    /// applications as well.
    ///
    /// Once objIsValid is passed in as false, AcDbAuditInfo::updateObject
    /// must be invoked to establish the new object id.
    /// </remarks>
    ///
    Acad::ErrorStatus registerObject(AcDbHandle handle,
                                     bool       objIsValid,
                                     AcRxClass* pObjClass);

    /// <summary>
    /// updateObject is invoked from AcDb Recover and Audit internals, and can
    /// also be invoked from AcDbObject::audit(), dwgInFields() and any other
    /// override members invoked during a recover operation and its subsequent
    /// audit. 
    /// </summary>
    ///
    /// <param name="setFileObjIsValid">
    /// Boolean indicating whether the fileObjIsValid parameter should
    /// replace the corresponding field in the lookup table entry.
    /// </param>
    ///
    /// <param name="setNewObjIsValid">
    /// Boolean indicating whether the newObjIsValid parameter should
    /// replace the corresponding field in the lookup table entry.
    /// </param>
    ///
    /// <param name="setFileObjClass">
    /// Boolean indicating whether the fileObjClass parameter should
    /// replace the corresponding field in the lookup table entry.
    /// </param>
    ///
    /// <param name="setNewObjClass">
    /// Boolean indicating whether the setNewObjClass parameter should
    /// replace the corresponding field in the lookup table entry.
    /// </param>
    ///
    /// <param name="setNewObjId">
    /// Boolean indicating whether the newObjId parameter should
    /// replace the corresponding field in the lookup table entry.
    /// </param>
    ///
    /// <param name="fileObjIsValid">
    /// A bool indicating whether the object image in the DWG file was
    /// valid or not.
    /// </param>
    ///
    /// <param name="newObjIsValid">
    /// A bool indicating whether the object under newObjId is
    /// valid or not.   If not set to true, then fetchObject on
    /// objectHandle will return eNullObjectPointer.
    /// </param>
    ///
    /// <param name="pFileObjClass">
    /// The original class of the missing or corrupted object.
    /// </param>
    ///
    /// <param name="pNewObjClass">
    /// The class of the original or replacement object.
    /// </param>
    ///
    /// <param name="newObjId">
    /// Boolean indicating whether the newObjId parameter should
    /// replace the corresponding field in the lookup table entry.
    /// Usually that of objectHandle unless the object id had to
    /// be redirected.
    /// </param>
    ///
    /// <returns>
    /// The following ErrorStatus values can be returned from this function.
    /// eOk:                   Success, the indicated fields were replaced.
    /// eInvalidInput:         The input handle cannot be null (0).
    /// </returns>
    ///
    /// <remarks>
    /// The Recover logic makes use of this member to indicated fixed up
    /// objects and redirected object ids.  But it can be invoked by
    /// applications as well.
    ///
    /// This is the most powerful and most verbose way to create and update
    /// entries for the indirect object lookup table; with a separate parameter
    /// for every field in a table entry, and a boolean flag for each parameter,
    /// indicating whether the corresponding parameter should replace the current
    /// entry or not.
    /// </remarks>
    ///
    Acad::ErrorStatus updateObject( AcDbHandle   handle,
                                    bool         setFileObjIsValid,
                                    bool         setNewObjIsValid,
                                    bool         setFileObjClass,
                                    bool         setNewObjClass,
                                    bool         setNewObjId,
                                    bool         fileObjIsValid,
                                    bool         newObjIsValid,
                                    AcRxClass*   pFileObjClass,
                                    AcRxClass*   pNewObjClass,
                                    AcDbObjectId newObjId);

private:

    AcDbImpAuditInfo * getImpAudit() const;

    AcDbImpAuditInfo * mpImpAudit;
};

//    Class to hold the call back function.

class AcDbRecover{

    public:
    virtual  int callBack(AcDbDatabase*) = 0;
};

class  AcDbImpRecoverCallBack;

class AcDbRecoverCallBack {

    public:
    AcDbRecoverCallBack();
    virtual ~AcDbRecoverCallBack();

    virtual  Acad::ErrorStatus registerCallBack(AcDbRecover*);
    virtual  Acad::ErrorStatus removeCallBack();

    private:

        AcDbImpRecoverCallBack *mpImpRecoverCallBack;

};

#pragma pack(pop)

#endif
