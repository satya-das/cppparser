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
//  AcDbLMgr.h - Exported Interface class for Database specific 
//               routines that manipulate and access AcDbLayout 
//               objects.
//

#ifndef   _ACDBLMGR_H
#define   _ACDBLMGR_H

#include "adesk.h"
#include "dbid.h"
#include "dblayout.h"
#include "dblaymgrrctr.h"
#pragma pack (push, 8)

// The maximum number of layouts in a single drawing.
#define  MAX_PSPACE_LAYOUTS     256

class AcDbObjectId;

class AcDbLayoutManager: public AcRxObject  {
  public:

    /// <sumary>
    /// This function sets the layout named newname as the current layout in the database pointed to by pDb. If pDb is NULL, then the current workingDatabase will be used.
    /// </sumary>
    /// <param name="newname">Input name of layout to be set as current.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus 
        setCurrentLayout        (const ACHAR * newname,
                                 AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function makes the AcDbLayout object associated with the given AcDbObjectId the current layout in the active database. 
    /// </sumary>
    /// <param name="layoutId">Input AcDbObjectId for the AcDbLayout object to make current </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus 
        setCurrentLayoutId      (AcDbObjectId layoutId) = 0;

    /// <sumary>
    /// If allowModel is true, then this function will return the name of the active layout in the database pointed to by pDb (or the workingDatabase if pDb is NULL) even if the layout is the ModelSpace layout. If allowModel is false, then the current PaperSpace layout name will be returned even if it is not the currently active layout.
    /// </sumary>
    /// <param name="allowModel">Input bool indicating whether or not to allow the ModelSpace layout to be included.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    virtual Acad::ErrorStatus   getActiveLayoutName(AcString & sName, bool allowModel,
                                                    const AcDbDatabase* pDb = nullptr) = 0;

    // This overload is deprecated and will be removed. Please use getActiveLayoutName()
    virtual const ACHAR *               findActiveLayout(bool allowModel,
                                 const AcDbDatabase* pDb = nullptr) final;      // deprecated

    /// <sumary>
    /// This function returns the block table record id for the current AcDbLayout object. If TILEMODE is 1, then this will retrieve the *MODEL_SPACE block table record. If TILEMODE is 0, then this will retrieve the *PAPER_SPACE block table record; which represents the current paper space layout. 
    ///
    /// To retrieve the associated layout, open the returned block table record for read and then use the getLayoutId() method to retrieve the object ID of the associated layout.
    /// </sumary>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    virtual AcDbObjectId      
        getActiveLayoutBTRId    (const AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function returns the objectId of the layout named name in the database pointed to by pDb.  If pDb is NULL, then the workingDatabase will be used.  If no layout is found, then the returned id will be null.
    /// </sumary>
    /// <param name="name">Input name of layout to find.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    virtual AcDbObjectId      
        findLayoutNamed         (const ACHAR* name, 
                                 const AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function will find the layout named name in the database pointed to by pDb, open it in the specified mode, and set pLayout to point to the opened AcDbLayout object.   If pDb is NULL, then the workingDatabase will be used.
    /// </sumary>
    /// <param name="name">Input name of layout to get.</param>
    /// <param name="pLayout">Output pointer to layout object.</param>
    /// <param name="mode">Input mode to open layout.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus
        getLayoutNamed          (const ACHAR* name,
                                 AcDbLayout*& pLayout,
                                 AcDb::OpenMode mode = AcDb::kForRead,
                                 const AcDbDatabase* pDb = nullptr);
    
    /// <sumary>
    /// This function returns true if the layout named name is found in the database pointed to by pDb.  If pDb is NULL, then the workingDatabase will be used.
    /// </sumary>
    /// <param name="name">Input name of layout to find.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    bool
        layoutExists            (const ACHAR* name,
                                 const AcDbDatabase* pDb = nullptr);
                                  
    /// <sumary>
    /// This function creates a copy of the layout named copyname in the database pointed to by pDb (or the workingDatabase if pDb is NULL) and names the copy newname.
    /// </sumary>
    /// <param name="copyname">Input name of layout to copy.</param>
    /// <param name="newname">Input name to be given to the layout copy.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    /// <returns>Returns Acad::eOk if successful. Returns Acad::eMaxLayouts if there are already the maximum number of layouts in the database. Returns Acad::eRenameInvalidLayoutName if newname &gt; 255 characters long. Returns Acad::eCopyDoesNotExist if there is no layout named copyname. Returns Acad::eCopyIsModelSpace if copyname is the ModelSpace layout.</returns>
    virtual Acad::ErrorStatus 
        copyLayout              (const ACHAR * copyname, 
                                 const ACHAR * newname,
                                 AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function deletes the layout named delname from the database pointed to by pDb (or the workingDatabase if pDb is NULL).
    /// </sumary>
    /// <param name="delname">Input name of layout to delete.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    /// <returns>Returns Acad::eOk if successful. Returns Acad::eDelLastLayout if delname is the last PaperSpace layout in the database. Returns Acad::eDelIsModelSpace if delname is the ModelSpace layout. Returns Acad::eDelDoesNotExist if delname is not found in the database.</returns>
    virtual Acad::ErrorStatus 
        deleteLayout            (const ACHAR * delname,
                                 AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function creates a new AcDbLayout object given a unique layout name. The default viewports for the new layout are not created until the layout is first activated.
    /// </sumary>
    /// <param name="newname">Input pointer of name to give new AcDbLayout object</param>
    /// <param name="layoutId">Output reference to AcDbObjectId for the newly created AcDbLayout object</param>
    /// <param name="blockTableRecId">Output reference to AcDbObject block table record Id for the newly created AcDbLayout object</param>
    /// <param name="pDb">Optional input pointer to AcDbDatabase. The default is the current database.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    virtual Acad::ErrorStatus 
        createLayout            (const ACHAR *newname,
                                 AcDbObjectId& layoutId, 
                                 AcDbObjectId& blockTableRecId, 
                                 AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function renames the layout named "oldname" to the new name "newname" in the database pointed to by pDb (or the workingDatabase if pDb is NULL).
    /// </sumary>
    /// <param name="oldname">Input name of layout to rename.</param>
    /// <param name="newname">Input new name for layout.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    /// <returns>Returns Acad::eOk if successful. Returns Acad::eRenameDoesNotExist if oldname isn't in the database. Returns Acad::eRenameIsModelSpace if the oldname is the ModelSpace layout. Returns Acad::eRenameInvalidLayoutName if newname is not a valid layout name. Returns Acad::eRenameLayoutAlreadyExists if newname already exists in the database.</returns>
    virtual Acad::ErrorStatus 
        renameLayout            (const ACHAR * oldname, 
                                 const ACHAR * newname,
                                 AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function copies the layout pointed to by pLBTR which must be in the database pointed to by pDb (or the workingDatabase if pDb is NULL), adds it to the same database using the name newname, sets it in the layout tab order at index newTabOrder, then closes both the layout pointed to by pLBTR and the newly created layout.
    /// </sumary>
    /// <param name="pLBTR">Input pointer to layout to clone</param>
    /// <param name="newname">Input name for layout clone.</param>
    /// <param name="newTabOrder">Input tab index for the location of the new layout.</param>
    /// <param name="pDb">Input AcDbDatabase to use.</param>
    /// <returns>Returns Acad::eOk if successful. Returns Acad::eCopyNameExists if newname already exists in the database. Returns Acad::eMaxLayouts if there are already the maximum number of layouts in the database. Returns Acad::eCopyIsModelSpace if pLBTR is the ModelSpace layout.</returns>
    virtual Acad::ErrorStatus 
        cloneLayout             (AcDbLayout* pLBTR, 
                                 const ACHAR * newname, 
                                 int newTabOrder = 0,
                                 AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function returns the AcDbObjectId for the non rectangular viewport ID associated with the given clipId. Returns NULL if given entity isn't a valid clip entity.
    /// </sumary>
    /// <param name="clipId">Input AcDbObjectId of clip entity to get the nonrectangular viewport ID from</param>
    virtual AcDbObjectId  
        getNonRectVPIdFromClipId (AcDbObjectId clipId) = 0;

    /// <sumary>
    /// For Autodesk Internal Use.
    /// </sumary>
    /// <param name="index">For Autodesk Internal Use.</param>
    /// <param name="pDb">For Autodesk Internal Use.</param>
    virtual bool              
        isVpnumClipped          (int index, const AcDbDatabase* pDb = NULL) = 0;

    /// <sumary>
    /// This function returns the number of items in the layout dictionary which should represent the number of AcDbLayout objects in the drawing. This includes the Model tab, which is always present.
    /// </sumary>
    /// <param name="pDb">Input pointer of AcDbDatabase to use. Default is the current database.</param>
    virtual int               
        countLayouts            (AcDbDatabase *pDb = NULL) = 0;

    /// <sumary>
    /// This method adds the newObj reactor object to the layout manager's reactor list.
    /// </sumary>
    /// <param name="newObj">Input pointer to a reactor object</param>
    virtual void 
        addReactor              (AcDbLayoutManagerReactor * newObj) = 0;

    /// <sumary>
    /// This method removes the newObj reactor object from the layout manager's reactor list. If newObj is not in the layout manager's reactor list, then this function does nothing.
    /// </sumary>
    /// <param name="delObj">Input pointer to a reactor object</param>
    virtual void 
        removeReactor           (AcDbLayoutManagerReactor * delObj) = 0;
};

// Deprecated and scheduled for removal. Please use the other overload taking AcString & arg
inline const ACHAR * AcDbLayoutManager::findActiveLayout(bool allowModel, const AcDbDatabase* pDb)
{
    static AcString sCachedName;
    this->getActiveLayoutName(sCachedName, allowModel, pDb);
    return sCachedName.constPtr();
}

inline Acad::ErrorStatus AcDbLayoutManager::getLayoutNamed(const ACHAR* name,
    AcDbLayout*& pLayout, AcDb::OpenMode mode, const AcDbDatabase* pDb)
{
    AcDbObjectId id = findLayoutNamed(name, pDb);
    if (id.isNull())
        return Acad::eKeyNotFound;

    return acdbOpenObject(pLayout, id, mode);
}    

inline bool AcDbLayoutManager::layoutExists(const ACHAR* name, const AcDbDatabase* pDb)
{
    return !(findLayoutNamed(name, pDb)).isNull();
}
                              
/// <sumary>
/// This function sets the layout manager to work on the database pointed to by pDatabase, even if this database is not loaded in the AutoCAD editor. 
///
/// When you are done, you must use acdbClearSetupForLayouts(), passing it the contextHandle returned by this function. This action resets the layout manager to work with the document/database it was using before the call to acdbDoSetupForLayouts(). 
///
/// acdbDoSetupForLayouts() calls cannot be nested. acdbClearSetupForLayouts() must be called before another call to acdbDoSetupForLayouts() can be made.
/// </sumary>
/// <param name="pDatabase">Input database on which the layout manager is to work</param>
/// <param name="contextHandle">Output a handle identifying the document on which the layout manager was working before this call</param>
/// <returns>Returns Acad::eOk if successful. Returns Acad::eInvalidInput if pDatabase is null.</returns>
Acad::ErrorStatus acdbDoSetupForLayouts(AcDbDatabase* pDatabase,
                                        Adesk::ULongPtr& contextHandle);

/// <sumary>
/// This function resets the layout manager to work with the document/database identified by contextHandle.
/// </sumary>
/// <param name="contextHandle">Input contextHandle returned by a previous call to acdbDoSetupForLayouts()</param>
/// <returns>Returns Acad::eOk if successful.</returns>
Acad::ErrorStatus acdbClearSetupForLayouts(Adesk::ULongPtr contextHandle);

#pragma pack (pop)
#endif // _ACDBLMGR_H
