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

class AcDbPointCloudCropStateManagerImp;
class AcDbPointCloudEx;

/// <summary>
/// This class includes all the crop states functions for point cloud.
/// From the class you can get the saved crop states name, save current crops,
/// delete a crop state, rename a crop state and get the current active crop state.
/// The crop state manager is per point cloud object, you can get its pointer
/// from AcDbPointCloudEx::cropStatesManager() or AcDbPointCloudEx::cropStatesManagerConst().
/// </summary>
class ACDB_PORT AcDbPointCloudCropStateManager
{
public:
    /// <summary>
    /// Restore the crop state. 
    /// </summary>
    /// <param name="name">
    /// The name of the crop state.
    /// </param>
    /// <returns>
    /// Return Acad::eOk if it success to restore the crop state.
    /// Return Acad::eNotApplicable if there is no this "name" crop state.
    /// </returns>
    Acad::ErrorStatus  restoreCropState(const AcString& name);
    /// <summary>
    /// Get all the crop states name.
    /// </summary>
    /// <param name="states">
    /// The output parameter to hold all the crop states name.
    /// </param>
    /// <returns>
    /// Return Acad::eOk if it success.
    /// Return Acad::eNotApplicable if it meets errors.
    /// </returns>
    Acad::ErrorStatus  getAllCropStates(AcArray<AcString>& states) const;
    /// <summary>
    /// Remove the specified crop state. 
    /// </summary>
    /// <param name="name">
    /// The name of the crop state.
    /// </param>
    /// <returns>
    /// Return Acad::eOk if it success to restore the crop state.
    /// Return Acad::eNotApplicable if there is no this "name" crop state.
    /// </returns>
    Acad::ErrorStatus  removeCropState(const AcString& name);
    /// <summary>
    /// Rename the specified crop state. Note that the name should honor the rules for symbol names.
    /// These general rules are: 
    /// Names may be as long as you need them to be (longer than 32 characters, as defined by previous versions of AutoCAD). 
    /// Names may contain additional characters, such as the space character (' '), the apostrophe ('''), and so on. 
    /// Names are treated case-insensitively. 
    /// Names can not contain the following illegal characters: 
    /// vertical bar ('|') 
    /// asterisk ('*'), except as noted above 
    /// backslash ('') 
    /// colon (':') 
    /// semicolon (';') 
    /// angle brackets ('>', '<') 
    /// question mark ('?') 
    /// double quote ('"') 
    /// comma (',') 
    /// equal sign ('=') 
    /// grave accent ('`') 
    /// </summary>
    /// <param name="oldName">
    /// The old name of the crop state.
    /// </param>
    /// <param name="newName">
    /// The new name you want to set.
    /// </param>
    /// <returns>
    /// Return Acad::eOk if it success to restore the crop state.
    /// Return Acad::eNotApplicable if there is no this "name" crop state.
    /// </returns>
    Acad::ErrorStatus  renameCropState(const AcString& oldName, const AcString& newName);
    /// <summary>
    /// Save the current crop, and specify a name. It honors the rules for symbol names. 
    /// These general rules are: 
    /// Names may be as long as you need them to be (longer than 32 characters, as defined by previous versions of AutoCAD). 
    /// Names may contain additional characters, such as the space character (' '), the apostrophe ('''), and so on. 
    /// Names are treated case-insensitively. 
    /// Names can not contain the following illegal characters: 
    /// vertical bar ('|') 
    /// asterisk ('*'), except as noted above 
    /// backslash ('') 
    /// colon (':') 
    /// semicolon (';') 
    /// angle brackets ('>', '<') 
    /// question mark ('?') 
    /// double quote ('"') 
    /// comma (',') 
    /// equal sign ('=') 
    /// grave accent ('`') 
    /// </summary>
    /// <param name="state">
    /// The name of the crop state you specified.
    /// </param>
    /// <returns>
    /// Return Acad::eOk if it success to add the crop state.
    /// Return Acad::eDuplicateRecordName if it has this "name" crop states.
    /// </returns>
    Acad::ErrorStatus  addCropState(const AcString& state);
    /// <summary>
    /// Get the current crop state name. 
    /// </summary>
    /// <returns>
    /// Return the name of the current crop state. If there is no current
    /// crop state, it returns empty string. If you changed crop properties, 
    /// or change the invisible scans/regions, it also return empty string.
    /// </returns>
    AcString           currentCropState() const;

private:
    AcDbPointCloudCropStateManager();
    AcDbPointCloudCropStateManager(AcDbPointCloudEx* pCloud);
    virtual ~AcDbPointCloudCropStateManager();

    AcDbPointCloudCropStateManagerImp* m_pImpCropStatesManager;

    friend class PointCloudExImp;
    friend class PointCloudCropStateRoundtripManager;
};