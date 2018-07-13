//////////////////////////////////////////////////////////////////////////////
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

#include "acarray.h"
#include "adsdef.h"
#include "acstring.h"
//////////////////////////////////////////////////////////////////////////

class AcPointCloudItem;
typedef AcPointCloudItem* PPointCloudItem;
typedef AcArray<AcPointCloudItem*> AcPointCloudItemArray;


/// <summary>
/// Class point cloud item, which presents different type of point cloud elements
/// e.g. project, scan, region, etc. 
/// </summary>
class ACDB_PORT AcPointCloudItem 
{
public:

    /// <summary>
    /// Describes the type of point cloud item
    /// </summary>
    enum AcPointCloudItemType
    {
        /// <summary>
        /// Legacy point cloud (load from a .pcg, .isd file).
        /// </summary>
        kLegacyPointCloud = 0,

        /// <summary>
        /// Point cloud project (load from a .rcp file which contains several .rcs files).
        /// </summary>
        kPointCloudProject,

        /// <summary>
        /// Individual scan (load from a .rcs file directly).
        /// </summary>
        kIndividualScan,
        
        /// <summary>
        /// Scan (a scan file included in a point cloud project file).
        /// </summary>
        kScan,
        
        /// <summary>
        /// A region is a Non-overlapping area that are defined in a point cloud for the purpose of filtering the display of meaningful volumes in the scene.
        /// </summary>
        kRegion,
        
        /// <summary>
        /// Folder to contain all scan items.
        /// </summary>
        kScanRootGroup,
        
        /// <summary>
        /// Folder to contain all region items.
        /// </summary>
        kRegionRootGroup, 
        
        /// <summary>
        /// Points which are not assigned to any region.
        /// </summary>
        kUnassignedPoint
    };

    /// <summary>
    /// Default constructor
    /// </summary>
    AcPointCloudItem();

    /// <summary>
    /// Destructor
    /// </summary>
    ~AcPointCloudItem() {}

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="name"> name of the item. </param>
    /// <param name="projectname"> project name which the item belongs to. </param>
    /// <param name="objectid"> index where the item is in the list. </param>
    /// <param name="categoryid"> category id which the item belongs to. </param>
    /// <param name="visibility"> specify if the item is visible. </param>
    /// <param name="highlight"> specify if the item is highlighted. </param>
    /// <param name="guid"> GUID of the item </param>
    AcPointCloudItem(const AcString& name, const AcString& projectname, int objectid, AcPointCloudItemType categoryid, bool visibility = true, bool highlight = false, AcString guid = L"");

    /// <summary>
    /// Copy constructor
    /// </summary>
    /// <param name="item"> the item which will be copied. </param>
    AcPointCloudItem(const AcPointCloudItem& item); 

    /// <summary>
    /// Assign operator
    /// </summary>
    /// <param name="other"> the item which will be assigned to current item. </param>
    /// <returns>Returns a reference of current item.</returns>
    AcPointCloudItem& operator =  (const AcPointCloudItem& other);

    /// <summary>
    /// Parse a string and assign the value to a new created item
    /// </summary>
    /// <param name="cmd">The string which needs to be parsed. 
    /// The format is [ads name1:ads name2]|[name]|[guid]|[id]|[type]|[true|false]. 
    /// For example: 8796086754688:8796056998051|Room|{1CD49BCD_32FC_4A2E_92EA_C6ED69672F4E}|2|Scan|True
    /// </param>
    /// <returns>new created point cloud item</returns>
    static AcPointCloudItem* CreateFromCmdString(const ACHAR* cmd);

public:
    /// <summary>
    /// Sets the name of item.
    /// </summary>
    /// <param name="val">item name</param>
    void        setName(const AcString& val);

    /// <summary>
    /// Gets the name of item.
    /// </summary>
    /// <returns>item name</returns>
    /// <remarks>default value of name is set to empty string in default constructor</remarks>
    AcString    name() const;

    /// <summary>
    /// Sets the name of project which current item belongs to
    /// </summary>
    /// <param name="val">project name</param>
    void        setProjectName(const AcString& val);

    /// <summary>
    /// Gets the name of project which current item belongs to.
    /// </summary>
    /// <returns>project name</returns>
    /// <remarks>default value of project name is set to empty string in default constructor</remarks>
    AcString    projectName() const;

    /// <summary>
    /// Sets the GUID of item
    /// </summary>
    /// <param name="val">GUID value</param>
    void        setGuid(const AcString& val);

    /// <summary>
    /// Gets the GUID of item
    /// </summary>
    /// <returns>GUID of item</returns>
    /// <remarks>default value of GUID is set to empty string in default constructor</remarks>
    const AcString&    guid() const;

    /// <summary>
    /// Sets id of item.
    /// </summary>
    /// <param name="val">id of item</param>
    /// <remarks>
    /// Basically, the id is the index where the item in the list, the value is read from ReCap SDK.
    /// If the type of item is kScan, id is the index in the list. 
    /// If the type of item is kRegion, then id is the value of layer id defined in ReCap SDK 
    /// </remarks>
    void        setId(int val);

    /// <summary>
    /// Gets id of item.
    /// </summary>
    /// <returns>id of item</returns>
    /// <remarks>default value is set to 0 in default constructor</remarks>
    int         id() const;

    /// <summary>
    /// Sets the visibility of item.
    /// </summary>
    /// <param name="val"> the item is visible or not.</param>
    void        setVisibility(bool val);

    /// <summary>
    /// Gets the visibility of item.
    /// </summary>
    /// <returns>Returns true if the item is visible or false otherwise.</returns>
    /// <remarks>default value of visibility is set to true in default constructor</remarks>
    bool        visibility() const;

    /// <summary>
    /// Sets the highlight of item.
    /// </summary>
    /// <param name="val">The val showing whether the item is highlighted or not.</param>
    void        setHighlight(bool val);

    /// <summary>
    /// Gets the highlight of item.
    /// </summary>
    /// <returns>Returns true if the item is highlighted or false otherwise.</returns>
    /// <remarks>default value of highlight is set to false in default constructor</remarks>
    bool        highlight() const;


    /// <summary>
    /// Sets the color which is used to highlight item
    /// </summary>
    /// <param name="red">value of red color.</param>
    /// <param name="green">value of green color.</param>
    /// <param name="blue">value of blue color.</param>
    void        setColor(float red, float green, float blue);

    /// <summary>
    /// Gets the value of red color 
    /// </summary>
    /// <returns>value of red color</returns>
    /// <remarks>default value of red color is set to 0.0 in default constructor</remarks>
    float       red() const;

    /// <summary>
    /// Gets the value of green color
    /// </summary>
    /// <returns>value of green color</returns>
    /// <remarks>default value of green color is set to 0.0 in default constructor</remarks>
    float       green() const;

    /// <summary>
    /// Gets the value of blue color
    /// </summary>
    /// <returns>value of blue color</returns>
    /// <remarks>default value of blue color is set to 0.0 in default constructor</remarks>
    float       blue() const;

    /// <summary>
    /// Sets the ADS name of AcDbPointCloudEx which the item belongs to
    /// </summary>
    /// <param name="val">ADS name.</param>
    /// <remarks>
    /// ADS name is transformed from ObjectId of AcDbPointCloudEx
    /// </remarks>
    void                    setAdsName(const ads_name& val);

    /// <summary>
    /// Gets the ADS name of AcDbPointCloudEx which the item belongs to
    /// </summary>
    /// <returns>ADS name</returns>
    /// <remarks>default value of ADS name is set to 0 in default constructor</remarks>
    const ads_name&         adsName() const;

    /// <summary>
    /// Sets the type of the item.
    /// </summary>
    /// <param name="val">type of the item.</param>
    void                    setItemType(AcPointCloudItemType val);

    /// <summary>
    /// Gets the type of the item.
    /// </summary>
    /// <returns>type of the item.</returns>
    /// <remarks>default value of item type is set to kPointCloudProject in default constructor</remarks>
    AcPointCloudItemType    itemType() const;

private:
    void        copyItem(const AcPointCloudItem& other);

private:
    // data fields
    AcString    m_name;
    AcString    m_projectName;
    AcString    m_guid;
    int         m_id;
    bool        m_visibility;
    bool        m_highlight;
    ads_name    m_adsName;
    float       m_red;
    float       m_green;
    float       m_blue; 
    AcPointCloudItemType    m_itemType;

};

