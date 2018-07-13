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
//  DESCRIPTION:  Header for AcRxEventReactor notification.
//
#ifndef   _ACRX_EVENT_H__
#define   _ACRX_EVENT_H__

#include "acarray.h"
#include "rxobject.h"
#include "AdAChar.h"
#include "dbid.h"
#pragma pack (push, 8)

#define ACRX_EVENT_OBJ ACRX_T("AcRxEvent")

class AcDbDatabase;
class AcGeMatrix3d;
class AcDbIdMapping;
class AcGePoint3d;
    
enum AcXrefSubCommand {
    kAttach = 0,
    kBind = 1,
    kDetach = 2,
    kOverlay = 3,
    kPath = 4,
    kReload = 5,
    kResolve = 6,
    kUnload = 7,
    kXBind = 8
};


class AcRxEventReactor: public AcRxObject 
{ 
public:

    ACRX_DECLARE_MEMBERS(AcRxEventReactor);

    // DWG/Save Events.
    //
    ADESK_DEPRECATED virtual void dwgFileOpened(AcDbDatabase*, ACHAR * ) final {}; //use const override instead
    virtual void dwgFileOpened(AcDbDatabase*, const ACHAR * /*fileName*/) {};
    virtual void initialDwgFileOpenComplete(AcDbDatabase*);
    virtual void databaseConstructed(AcDbDatabase*);
    virtual void databaseToBeDestroyed(AcDbDatabase*);

    virtual void beginSave    (AcDbDatabase*, const ACHAR * pIntendedName);
    virtual void saveComplete (AcDbDatabase*, const ACHAR * pActualName);
    virtual void abortSave    (AcDbDatabase*);

    // DXF In/Out Events.
    //
    virtual void beginDxfIn      (AcDbDatabase*);
    virtual void abortDxfIn      (AcDbDatabase*);
    virtual void dxfInComplete   (AcDbDatabase*);
    //
    virtual void beginDxfOut     (AcDbDatabase*);
    virtual void abortDxfOut     (AcDbDatabase*);
    virtual void dxfOutComplete  (AcDbDatabase*);
    
    // Insert Events.
    //
    virtual void beginInsert(AcDbDatabase* pTo, const ACHAR * pBlockName,
                             AcDbDatabase* pFrom);
    virtual void beginInsert(AcDbDatabase* pTo, const AcGeMatrix3d& xform,
                             AcDbDatabase* pFrom);
    virtual void otherInsert(AcDbDatabase* pTo, AcDbIdMapping& idMap,
                             AcDbDatabase* pFrom);
    virtual void abortInsert(AcDbDatabase* pTo);
    virtual void endInsert  (AcDbDatabase* pTo);

    // Wblock Events.
    //
    virtual void wblockNotice(AcDbDatabase* pDb);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom,
                             const AcGePoint3d*& insertionPoint);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom,
                             AcDbObjectId blockId);
    virtual void beginWblock(AcDbDatabase* pTo, AcDbDatabase* pFrom); 
    virtual void otherWblock(AcDbDatabase* pTo, AcDbIdMapping&,
                             AcDbDatabase* pFrom);
    virtual void abortWblock(AcDbDatabase* pTo);
    virtual void endWblock  (AcDbDatabase* pTo);
    virtual void beginWblockObjects(AcDbDatabase*, AcDbIdMapping&);

    // Deep Clone Events.
    //
    virtual void beginDeepClone       (AcDbDatabase* pTo, AcDbIdMapping&);
    virtual void beginDeepCloneXlation(AcDbIdMapping&, Acad::ErrorStatus*);
    virtual void abortDeepClone       (AcDbIdMapping&);
    virtual void endDeepClone         (AcDbIdMapping&);

    // Partial Open Events.
    //
    virtual void partialOpenNotice  (AcDbDatabase* pDb);

    // XREF-related Events
    //
    virtual void beginAttach (AcDbDatabase* pTo, const ACHAR *,
                              AcDbDatabase* pFrom);
    virtual void otherAttach (AcDbDatabase* pTo, AcDbDatabase* pFrom);
    virtual void abortAttach (AcDbDatabase* pFrom);
    virtual void endAttach   (AcDbDatabase* pTo);
    virtual void redirected  (AcDbObjectId  newId, AcDbObjectId oldId);
    virtual void comandeered (AcDbDatabase* pTo, AcDbObjectId id,
                              AcDbDatabase* pFrom);
    virtual void beginRestore(AcDbDatabase* pTo, const ACHAR *,
                              AcDbDatabase* pFrom);
    virtual void abortRestore(AcDbDatabase* pTo);
    virtual void endRestore  (AcDbDatabase* pTo);

    // More XREF related Events
    // 
    virtual void xrefSubcommandBindItem   (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandAttachItem (AcDbDatabase* pHost, int activity, const ACHAR* pPath);
    virtual void xrefSubcommandOverlayItem(AcDbDatabase* pHost, int activity, const ACHAR* pPath);
    virtual void xrefSubcommandDetachItem (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandPathItem   (int activity, AcDbObjectId blockId, 
                                           const ACHAR* pNewPath);
    virtual void xrefSubcommandReloadItem (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);
    virtual void xrefSubcommandUnloadItem (AcDbDatabase* pHost, int activity, AcDbObjectId blockId);

    virtual void xrefSubCommandStart(AcDbDatabase* pHostDb,
            AcXrefSubCommand op, const AcArray<AcDbObjectId>& ids,
            const ACHAR* const* btrNames, 
            const ACHAR* const* paths, bool& vetoOp); 

    virtual void xrefSubCommandAborted(AcDbDatabase* pHostDb,
            AcXrefSubCommand op, const AcArray<AcDbObjectId>& ids,
            const ACHAR* const* btrNames, 
            const ACHAR* const* paths); 

    virtual void xrefSubCommandEnd(AcDbDatabase* pHostDb,
            AcXrefSubCommand op, const AcArray<AcDbObjectId>& ids,
            const ACHAR* const* btrNames, 
            const ACHAR* const* paths);

    virtual void preXrefLockFile(AcDbDatabase* pDb,
            AcDbObjectId btrId);
};

#define acrxEvent AcRxEvent::cast(acrxSysRegistry()->at(ACRX_EVENT_OBJ))

class AcRxEvent: public AcRxObject 
{ 
public:
    ACRX_DECLARE_MEMBERS(AcRxEvent);
    virtual void addReactor   (AcRxEventReactor * newObj) = 0;
    virtual void removeReactor(AcRxEventReactor * delObj) = 0;
};

#pragma pack (pop)
#endif
