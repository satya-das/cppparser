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
// DESCRIPTION: Exported class for underlay definitions in dwg file - AcDbUnderlayDefintion

#ifndef ACDB_DBUNDERLAYDEF_H
#define ACDB_DBUNDERLAYDEF_H
#pragma once

#include "dbmain.h"
#include "acstring.h"

#pragma pack (push, 8)

class AcDbUnderlayItem;
class AcDbUnderlayHost;
class IAcReadStream;

/// <summary>
/// Abstract class that handles the linkage to the external underlay content. Underlays are similar to raster images
/// but their content is snappable. An AcDbUnderlayDefinition is referenced by 0 or more AcDbUnderlayReferences.
/// The AcDbUnderlayRefernece is responsible for the placement of the content within the drawing while AcDbUnderlayDefinition
/// handles the linkage to the underlay content. 
/// Instances of AcDbUnderlayReference derived concrete classes are inserted in a block table record.
/// Instances of AcDbUnderlayDefinition derived concrete classes are inserted into a dictionay off of the named object dictionary.
/// </summary>
class ADESK_NO_VTABLE AcDbUnderlayDefinition: public AcDbObject
{
public:
    ACDB_DECLARE_MEMBERS(AcDbUnderlayDefinition);
    ///<summary>Default constructor.</summary>
    AcDbUnderlayDefinition();
    ///<summary>Destructor.</summary>
    virtual ~AcDbUnderlayDefinition() = 0;
    /// <summary>
    /// Sets the name of the file that this underlay references. This name can be the following form:
    /// 1. relative path (relative to the host drawing) 
    /// 2. file name only (will be searched on the support search path)
    /// 3. full path
    /// </summary>
    /// <param name="file">Name of the file</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setSourceFileName(const ACHAR* file);
    /// <summary>
    /// Gets the name of the file that this underlay references. This name is in the form (relative or full path) that the user specified.
    /// </summary>
    /// <returns>Returns a pointer to the internal datamember that holds the source file path.
    /// The string should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</returns>
    const ACHAR* getSourceFileName() const;
    /// <summary>
    /// This function returns a pointer to an IAcReadStream for the file that
    /// this underlay references, or NULL if there is no file available.
    /// </summary>
    IAcReadStream* getReadStream() const;
    /// <summary>
    /// Gets the name of the file that this underlay references. This name is always a full path.
    /// </summary>
    /// <param name="file">Variable that is set to point to the internal datamember that holds the active file path upon successful return.
    /// The string should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus getActiveFileName(const ACHAR*& file) const;
    /// <summary>
    /// Gets the name of the file that this underlay references. This name is always a full path.
    /// </summary>
    /// <param name="file">Variable that is set to hold the source file path upon successful return.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus getActiveFileName(AcString& file) const;
    /// <summary>
    /// Sets the name of the underlay item that this underlay should reference.
    /// </summary>
    /// <param name="item">Name of the item</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setItemName(const ACHAR* item);
    /// <summary>
    /// Gets the name of the underlay item that this underlay currently references.
    /// </summary>
    /// <returns>Returns a pointer to the internal datamember that holds the item name.
    /// The string should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</returns>
    const ACHAR* getItemName() const;
    /// <summary>
    /// Sets the source path and underlay item that this underlay should reference. Calls unload() to unload any previous underlay item.
    /// </summary>
    /// <param name="sourceFileName">Source file path.</param>
    /// <param name="activeFileName">Current or active file path. This points to the file where it is currently found.</param>
    /// <param name="pItem">The item to be referenced. The underlay definition takes ownership of the item and it should *not* be deleted by the client.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus setUnderlayItem(const ACHAR* sourceFileName, const ACHAR* activeFileName, AcDbUnderlayItem* pItem);
    /// <summary>
    /// Gets the underlay item that this underlay currently references.
    /// </summary>
    /// <returns>Returns a pointer to the internal datamember that holds the item.
    /// The object should not be modified or freed and it may get invalidated if modifications are made to underlay definition.</returns>
    const AcDbUnderlayItem* getUnderlayItem() const;
    /// <summary>
    /// Attempts to load the file returned by getActiveFileName().
    /// </summary>
    /// <param name="password">Optional password. I password is NULL but is necessary to open file this function will prompt the user.</param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus load(const wchar_t* password);
    /// <summary>
    /// Unloads the underlay file. References will behave as the file was never loaded.
    /// </summary>
    void unload();
    /// <summary>
    /// Gets a boolean indicating whether the underlay is currently loaded.
    /// </summary>
    /// <returns>Returns true, if the underlay is loaded.</returns>
    bool isLoaded() const;
    /// <summary>
    /// Gets the name of the dictionary that holds the AcDbUnderlayDefinition objects in the named objects dictionary.
    /// </summary>
    /// <param name="underlayDefinitionType">The class descriptor of the underlay type for which to retrive the dictionary name for.</param>
    /// <returns>Returns the name of the dictionary that holds the AcDbUnderlayDefinition objects in the named objects dictionary.</returns>
    static AcString dictionaryKey(const AcRxClass* underlayDefinitionType);
private:
    /// <summary>
    /// When overridden in derived classes it gets the underlay host to be used by this underlay definition.
    /// </summary>
    /// <returns>Returns the underlay host to be used by this underlay definition.</returns>
    virtual const AcDbUnderlayHost* getUnderlayHost() const = 0;
};
/// <summary>
/// Represents DWF underlays in the drawing. Underlays are similar to raster images
/// but their content is snappable.
/// </summary>
class AcDbDwfDefinition: public AcDbUnderlayDefinition
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDwfDefinition);
    ///<summary>Default constructor.</summary>
    AcDbDwfDefinition();
    ///<summary>Destructor.</summary>
    virtual ~AcDbDwfDefinition();
    ///<summary>returns true if this is a DWFx file</summary>
    Adesk::Boolean isDWFx(void) const;
private:
    virtual  const AcDbUnderlayHost* getUnderlayHost() const override;
};
/// <summary>
/// Represents DGN underlays in the drawing. Underlays are similar to raster images
/// but their content is snappable.
/// </summary>
class AcDbDgnDefinition: public AcDbUnderlayDefinition
{
public:
    ACDB_DECLARE_MEMBERS(AcDbDgnDefinition);
    ///<summary>Default constructor.</summary>
    AcDbDgnDefinition();
    ///<summary>Destructor.</summary>
    virtual ~AcDbDgnDefinition();
    /// <summary>
    /// Gets a boolean indicating whether the underlay uses master units
    /// in the DGN file when the DGN file is being translated to DWG for
    /// the underlay to use.
    /// </summary>
    /// <returns>
    /// Returns true, if the underlay uses Master units during translation.
    /// </returns>
    bool useMasterUnits() const;
    /// <summary>
    /// Sets a boolean indicating whether the underlay uses master units
    /// in the DGN file when the DGN file is being translated to DWG for
    /// the underlay to use.
    /// </summary>
    /// <param name="useMaster">
    /// Input bool indicating whether or not to use master units during translation.
    /// </param>
    void setUseMasterUnits(bool useMaster);
    /// <summary>
    /// Gets the xref depth value (if any) the underlay uses. This depth
    /// value is used if the dwg file is exported as DGN. For DWG to DGN
    /// translation, Dgn underlays become Dgn xrefs and will be given
    /// this depth value.
    /// </summary>
    /// <returns>
    /// Returns the xref depth value, or -1 if there is no depth value.
    /// </returns>
    int xrefDepth() const;
    /// <summary>
    /// Sets the xref depth value (if any) the underlay uses. This depth
    /// value is used if the dwg file is exported as DGN. For DWG to DGN
    /// translation, Dgn underlays become Dgn xrefs and will be given
    /// this depth value.
    /// </summary>
    /// <param name="depth">
    /// Input value to be used as the depth when this underlay becomes
    /// a DGN reference during a DGNEXPORT.  A value of -1 indicates that
    /// no depth value should be stored for this underlay.
    /// </param>
    void setXrefDepth(int depth);
    /// <summary>
    /// Gets a boolean indicating whether raster images should be displayed
    /// in referenced (xref) DGN files.
    /// </summary>
    /// <returns>
    /// Returns true, if images should be displayed in referenced DGN files.
    /// </returns>
    bool showRasterRef() const;
    /// <summary>
    /// Sets a boolean indicating whether raster images should be displayed
    /// in referenced DGN files.
    /// </summary>
    /// <param name="useMaster">
    /// Input bool indicating whether or not to display raster images in
    /// referenced DGN files.
    /// </param>
    void setShowRasterRef(bool bShow);
private:
    virtual const AcDbUnderlayHost* getUnderlayHost() const override;

};

class AcDbPdfDefinition: public AcDbUnderlayDefinition
{
public:
    ACDB_DECLARE_MEMBERS(AcDbPdfDefinition);
    ///<summary>Default constructor.</summary>
    ACDBCORE2D_PORT AcDbPdfDefinition();
    ///<summary>Destructor.</summary>
    ACDBCORE2D_PORT virtual ~AcDbPdfDefinition();
private:
    virtual  const AcDbUnderlayHost* getUnderlayHost() const override;
};
#pragma pack (pop)

#endif
