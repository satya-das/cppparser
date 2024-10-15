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
// DESCRIPTION: AcDbLayerStateManager class definition.
//
// WRITTEN: 11/99 by Anil Patel

#ifndef ACDB_LSTATE_H
#define ACDB_LSTATE_H

#include "dbmain.h"
#include "acarray.h"
#include "acstring.h"

#pragma pack(push, 8)

class AcDbImpLayerStateManager;
class AcDbLayerStateManagerReactor;

class AcDbLayerStateManager: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbLayerStateManager);
    // Construction/destruction
    AcDbLayerStateManager();
    AcDbLayerStateManager(AcDbDatabase *pHostDb);
    virtual ~AcDbLayerStateManager();

    enum LayerStateMask {
        kNone           = 0x0000,
        kOn             = 0x0001,
        kFrozen         = 0x0002,
        kLocked         = 0x0004,
        kPlot           = 0x0008,
        kNewViewport    = 0x0010,
        kColor          = 0x0020,
        kLineType       = 0x0040,
        kLineWeight     = 0x0080,
        kPlotStyle      = 0x0100,
        kCurrentViewport = 0x0200,
        kTransparency   = 0x0400,
        kAll            = kOn | kFrozen | kLocked | kPlot | kNewViewport |
                          kColor | kLineType | kLineWeight | kPlotStyle |
                          kCurrentViewport | kTransparency,
        kStateIsHidden  = 0x8000,        
        kLastRestored   = 0x10000,        
        kDecomposition  = kAll | 0x20000
    };

    enum {
        kUndefDoNothing = 0,
        kUndefTurnOff = 1,
        kUndefFreeze = 2,
        kRestoreAsOverrides = 4
    };


    bool                addReactor(AcDbLayerStateManagerReactor * pReactor);
    bool                removeReactor(AcDbLayerStateManagerReactor * pReactor);

    // Service methods
    AcDbObjectId        layerStatesDictionaryId(bool bCreateIfNotPresent=false);
    bool                hasLayerState(const ACHAR *sName);
    Acad::ErrorStatus   saveLayerState(const ACHAR *sName, LayerStateMask mask);
    Acad::ErrorStatus   restoreLayerState(const ACHAR *sName);
    Acad::ErrorStatus   setLayerStateMask(const ACHAR *sName, 
                                          LayerStateMask mask);
    Acad::ErrorStatus   getLayerStateMask(const ACHAR *sName,
                                          LayerStateMask &returnMask);
    Acad::ErrorStatus   deleteLayerState(const ACHAR *sName);
    Acad::ErrorStatus   renameLayerState(const ACHAR *sName,
                                         const ACHAR *sNewName);
    Acad::ErrorStatus   importLayerState(const ACHAR *sFilename);
    Acad::ErrorStatus   importLayerState(const ACHAR *sFilename, AcString & sName);

    Acad::ErrorStatus   exportLayerState(const ACHAR *sNameToExport,
                                         const ACHAR *sFilename);

    Acad::ErrorStatus   saveLayerState(const ACHAR *sName, LayerStateMask mask, const AcDbObjectId& idVp);
    Acad::ErrorStatus   restoreLayerState(const ACHAR *sName, const AcDbObjectId& idVp, int nRestoreFlags = 0, const LayerStateMask* pClientMask = NULL);

    Acad::ErrorStatus   setLayerStateDescription(const ACHAR* sName,
                                                 const ACHAR* sDesc);
    Acad::ErrorStatus   getLayerStateDescription(const ACHAR* sName, ACHAR*& sDesc);
    bool                layerStateHasViewportData(const ACHAR* sName);
    Acad::ErrorStatus   importLayerStateFromDb(const ACHAR *pStateName, AcDbDatabase* pDb);
    Acad::ErrorStatus   getLayerStateNames(AcStringArray& lsArray, bool bIncludeHidden = true, bool bIncludeXref = true);
    Acad::ErrorStatus   getLastRestoredLayerState(AcString & sName, AcDbObjectId &restoredLSId);
    Acad::ErrorStatus   getLayerStateLayers(AcStringArray& layerArray, const ACHAR* sName, bool bInvert = false);
    bool                compareLayerStateToDb(const ACHAR* sName, const AcDbObjectId& idVp);
    Acad::ErrorStatus   addLayerStateLayers(const ACHAR *sName, const AcDbObjectIdArray& layerIds);
    Acad::ErrorStatus   removeLayerStateLayers(const ACHAR *sName, const AcStringArray& layerNames);
    bool                isDependentLayerState(const ACHAR *sName);
    AcDbDatabase *      getDatabase() const;

private:
    friend class AcDbImpDatabase;
    AcDbImpLayerStateManager *mpImpLSM;
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
class AcDbLayerStateManagerReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbLayerStateManagerReactor);

    virtual void layerStateCreated(const ACHAR * layerStateName,
                                   const AcDbObjectId& layerStateId);
    virtual void layerStateCompareFailed(const ACHAR * layerStateName,
                                         const AcDbObjectId& layerStateId);

    virtual void layerStateToBeRestored(const ACHAR * layerStateName,
                                        const AcDbObjectId& layerStateId);
    virtual void layerStateRestored(const ACHAR * layerStateName,
                                    const AcDbObjectId& layerStateId);
    virtual void abortLayerStateRestore(const ACHAR * layerStateName,
                                        const AcDbObjectId& layerStateId);


    virtual void layerStateToBeDeleted(const ACHAR * layerStateName,
                                       const AcDbObjectId& layerStateId);
    virtual void layerStateDeleted(const ACHAR * layerStateName);
    virtual void abortLayerStateDelete(const ACHAR * layerStateName,
                                       const AcDbObjectId& layerStateId);

    virtual void layerStateToBeRenamed(const ACHAR * oldLayerStateName,
                                       const ACHAR * newLayerStateName);
    virtual void layerStateRenamed(const ACHAR * oldLayerStateName,
                                   const ACHAR * newLayerStateName);
    virtual void abortLayerStateRename(const ACHAR * oldLayerStateName,
                                       const ACHAR * newLayerStateName);


};

#pragma pack(pop)

#endif
