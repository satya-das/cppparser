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

#ifndef   _ACDB_LAYOUT_MANAGER_REACTOR_H
#define   _ACDB_LAYOUT_MANAGER_REACTOR_H

#include "rxobject.h"
#include "dbid.h"
#include "AdAChar.h"
#pragma pack (push, 8)

class AcDbLayoutManagerReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbLayoutManagerReactor);

    virtual void layoutCreated(const ACHAR * newLayoutName,
                               const AcDbObjectId& layoutId);
    virtual void layoutToBeRemoved(const ACHAR * layoutName,
                                   const AcDbObjectId& layoutId);
    virtual void layoutRemoved(const ACHAR * layoutName,
                               const AcDbObjectId& layoutId);
    virtual void abortLayoutRemoved(const ACHAR * layoutName,
                                    const AcDbObjectId& layoutId);
    virtual void layoutToBeCopied(const ACHAR * layoutName,
                                  const AcDbObjectId& oldLayoutId);
    virtual void layoutCopied(const ACHAR * oldLayoutName,
                              const AcDbObjectId& oldLayoutId,
                              const ACHAR * newLayoutname,
                              const AcDbObjectId& newLayoutId);
    virtual void abortLayoutCopied(const ACHAR * layoutName,
                                   const AcDbObjectId& layoutId);
    virtual void layoutToBeRenamed(const ACHAR * oldName,
                                   const ACHAR * newName,
                                   const AcDbObjectId& layoutId);
    virtual void layoutRenamed(const ACHAR * oldName,
                               const ACHAR * newName,
                               const AcDbObjectId& layoutId);
    virtual void abortLayoutRename(const ACHAR * oldName,
                                   const ACHAR * newName,
                                   const AcDbObjectId& layoutId);
    virtual void layoutSwitched(const ACHAR * newLayoutname,
                                const AcDbObjectId& newLayoutId);
    virtual void plotStyleTableChanged(const ACHAR * newTableName,
                                       const AcDbObjectId& layoutId);
    virtual void layoutsReordered();

    virtual void refreshLayoutTabs();
 
};

#pragma pack (pop)
#endif // _ACDB_LAYOUT_MANAGER_REACTOR_H
