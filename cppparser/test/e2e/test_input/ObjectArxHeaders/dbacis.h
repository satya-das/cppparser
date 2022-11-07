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
//
// DESCRIPTION:
//
// Internal AutoCAD functions dealing with ASM-based entities which are 
// exported to be used by platform clients
//
#ifndef DB_API_DBACIS_H
#define DB_API_DBACIS_H

#include "acdb.h"
#include "acadstrc.h"
#include "AcArray.h"
#include "acdbport.h"

class AcDbDatabase;
#pragma pack (push, 8)

class AcDbDwgFiler;
class AcDbDxfFiler;
class AcDbObject;
class ENTITY;

extern "C"
{
    void acdbModelerStart();
    void acdbModelerEnd();
    Adesk::Boolean acdbIsModelerStarted();
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Get the modeler version that is appropriate for the given drawing version
/// and the object pointer (optional).
/// </summary>
/// <returns>
/// The modeler version
/// </returns>
/// <param name="dwgVer">Drawing version enum value</param>
/// <param name="pObj">Optional object pointer that determines what version
/// to save to</param>
///
ACDB_PORT
int acdbGetModelerDwgVer(AcDb::AcDbDwgVersion dwgVer,
                         AcDbObject* pObj = nullptr);

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Save the entity to DWG filer. The filed modeler version is dependent on
/// modelerVersion as follows:
///     < 0 - Deduce from the filer's drawing version (default, -1)
///     0 - Current version of the modeler
///     > 0 - A valid modeler version such as 2170, corresponding to 217.0
/// 
/// </summary>
/// <returns>
/// Acad::eOk if the entity is saved successfully
/// </returns>
/// <param name="filer">Filer to write to</param>
/// <param name="entity">Entity to be saved</param>
/// <param name="pDb">Database in which entity resides</param>
/// <param name="modelerVersion">Modeler version to save to (see summary)</param>
///
ACDB_PORT
Acad::ErrorStatus acdbModelerSaveEntityToDwgFiler(AcDbDwgFiler* filer, 
                                                  ENTITY*       entity,
                                                  AcDbDatabase* pDb,
                                                  int modelerVersion = -1);

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Save the array of entities to the DWG filer. The filed modeler version is 
/// dependent on modelerVersion as follows:
///     < 0 - Deduce from the filer's drawing version (default, -1)
///     0 - Current version of the modeler
///     > 0 - A valid modeler version such as 2170, corresponding to 217.0
/// 
/// </summary>
/// <returns>
/// Acad::eOk if all entities are saved successfully
/// </returns>
/// <param name="filer">Filer to write to</param>
/// <param name="entities">Array of entities to be saved</param>
/// <param name="pDb">Database in which entities reside</param>
/// <param name="modelerVersion">Modeler version to save to (see summary)</param>
///
ACDB_PORT
Acad::ErrorStatus acdbModelerSaveEntitiesToDwgFiler(AcDbDwgFiler* filer, 
                                                    const AcArray<ENTITY*>& entities,
                                                    AcDbDatabase* pDb,
                                                    int modelerVersion = -1);

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Save the entity to DXF filer. The filed modeler version is dependent on
/// modelerVersion as follows:
///     < 0 - Deduce from the filer's drawing version (default, -1)
///     0 - Current version of the modeler
///     > 0 - A valid modeler version such as 2170, corresponding to 217.0
/// 
/// </summary>
/// <returns>
/// Acad::eOk if the entity is saved successfully
/// </returns>
/// <param name="filer">Filer to write to</param>
/// <param name="entity">Entity to be saved</param>
/// <param name="pDb">Database in which entity resides</param>
/// <param name="modelerVersion">Modeler version to save to (see summary)</param>
///
ACDB_PORT
Acad::ErrorStatus acdbModelerSaveEntityToDxfFiler(AcDbDxfFiler* filer,
                                                  ENTITY*       entity,
                                                  AcDbDatabase* pDb,
                                                  int modelerVersion = -1);

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Save the array of entities to the DXF filer. The filed modeler version is 
/// dependent on modelerVersion as follows:
///     < 0 - Deduce from the filer's drawing version (default, -1)
///     0 - Current version of the modeler
///     > 0 - A valid modeler version such as 2170, corresponding to 217.0
/// 
/// </summary>
/// <returns>
/// Acad::eOk if all entities are saved successfully
/// </returns>
/// <param name="filer">Filer to write to</param>
/// <param name="entities">Array of entities to be saved</param>
/// <param name="pDb">Database in which entities reside</param>
/// <param name="modelerVersion">Modeler version to save to (see summary)</param>
///
ACDB_PORT
Acad::ErrorStatus acdbModelerSaveEntitiesToDxfFiler(AcDbDxfFiler* filer,
                                                    const AcArray<ENTITY*>& entities,
                                                    AcDbDatabase* pDb,
                                                    int modelerVersion = -1);

/// Some options enumerated to be used as bit flags, to be used with the entity
/// restoration (read) functions below.
/// 
enum ModelerRestoreOptions
{
    kReadForeignEntities = 0x01,    // Set this to restore foreign entities
    kReadUnknownEntities = 0x02,   // Set this to restore unknown entities
    kLoseUnknownCustomAttributes = 0x04, // Unset this to restore unknown custom attributes

    kReadStrangerEntityDefault= (kReadForeignEntities |
                                kReadUnknownEntities |
                                kLoseUnknownCustomAttributes), // Recommended default

    kModelerRestoreOptionsFuture1 = 0x08, // Unused, ignore
    kModelerRestoreOptionsFuture2 = 0x10, // Unused, ignore
    kModelerRestoreOptionsFuture3 = 0x20, // Unused, ignore
    kModelerRestoreOptionsFuture4 = 0x40, // Unused, ignore
};

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Restore a single entity from the DWG filer and return in pEntity. The
/// modeler version of restored entities is optionally returned in pModelerVersion.
/// Pass an appropriate value for restoreOptions to control restore behavior.
/// </summary>
/// <returns>
/// Acad::eOk if the entity is restored successfully (including a null entity)
/// </returns>
/// <param name="filer">DWG Filer to restore from</param>
/// <param name="pEntity">Restored entity if any</param>
/// <param name="pModelerVersion">If valid, set to the modeler version of restored entities</param>
/// <param name="restoreOptions">A valid combination of ModelerRestoreOptions enum values </param>
///
ACDB_PORT
Acad::ErrorStatus acdbModelerRestoreEntityFromDwgFiler(AcDbDwgFiler* filer,
                                                       ENTITY*& pEntity,
                                                       int* pModelerVersion = nullptr,
                                                       unsigned restoreOptions = kReadStrangerEntityDefault);

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Restore entities from the DWG filer and return in the array, entities. The
/// modeler version of restored entities is optionally returned in pModelerVersion.
/// Pass an appropriate value for restoreOptions to control restore behavior.
/// </summary>
/// <returns>
/// Acad::eOk if all entities are restored successfully
/// </returns>
/// <param name="filer">DWG Filer to restore from</param>
/// <param name="entities">Restored array of entities</param>
/// <param name="pModelerVersion">If valid, set to the modeler version of restored entities</param>
/// <param name="restoreOptions">A valid combination of ModelerRestoreOptions enum values </param>
///
ACDB_PORT
Acad::ErrorStatus acdbModelerRestoreEntitiesFromDwgFiler(AcDbDwgFiler* filer,
                                                         AcArray<ENTITY*>& entities,
                                                         int* pModelerVersion = nullptr,
                                                         unsigned restoreOptions = kReadStrangerEntityDefault);

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Restore a single entity from the DXF filer and return in entity. The
/// modeler version of restored entities is optionally returned in pModelerVersion.
/// Pass an appropriate value for restoreOptions to control restore behavior.
/// </summary>
/// <returns>
/// Acad::eOk if the entity is restored successfully, (including a null entity)
/// </returns>
/// <param name="filer">DXF Filer to restore from</param>
/// <param name="pEntity">Restored entity if any</param>
/// <param name="pModelerVersion">If valid, set to the modeler version of restored entities</param>
/// <param name="restoreOptions">A valid combination of ModelerRestoreOptions enum values </param>
///
ACDB_PORT
Acad::ErrorStatus acdbModelerRestoreEntityFromDxfFiler(AcDbDxfFiler* filer,
                                                       ENTITY*& pEntity,
                                                       int* pModelerVersion = nullptr,
                                                       unsigned restoreOptions = kReadStrangerEntityDefault);
#pragma pack (pop)
#endif
