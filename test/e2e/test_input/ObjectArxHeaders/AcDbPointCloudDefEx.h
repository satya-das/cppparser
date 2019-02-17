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
#include "dbmain.h"

static const TCHAR* kpPointCloudExDictionaryName = /*NOXLATE*/ACRX_T("ACAD_POINTCLOUD_EX_DICT");

class PointCloudDefExImp;
namespace Autodesk { namespace RealityStudio { namespace SDK { namespace Interface {
    class IRCData;
}}}}

//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// The AcDbPointCloudDefEx object (or "point cloud extension definition object")
/// controls the actual point cloud data associated with one or more 
/// AcDbPointCloudEx entities (or "point cloud extension entity"). These objects
/// link the .rcp/.rcs file to the dwg file, similar to how Xrefs work.
/// 
/// The relationship between the AcDbPointCloudDefEx and 
/// AcDbPointCloudEx classes is much like the relationship 
/// between an AutoCAD block definition object and a block reference entity.
/// 
/// AcDbPointCloudDefEx objects are stored in a special AcDbDictionary named 
/// "ACAD_POINTCLOUD_EX_DICT". These objects are not AutoCAD entities, so they
/// can't be displayed or selected by the end user.
/// </summary>
class ACDB_PORT AcDbPointCloudDefEx : public AcDbObject
{
public:
    /// <summary>
    /// This enumeration defines the current state of supported properties in
    /// the point cloud data.
    /// </summary>
    enum PropState
    {
        /// <summary>
        /// No scan in the point cloud has the property.
        /// </summary>
        kNone = -1,

        /// <summary>
        /// Some scans in the point cloud have the property, but some do not.
        /// </summary>
        kSome = 0,

        /// <summary>
        /// All scans in the point cloud have the property.
        /// </summary>
        kAll = 1
    };

    /// <summary>
    /// This enumeration defines the types of properties that a point cloud can have.
    /// </summary>
    enum Property
    {
        /// <summary> The Color property. </summary>
        kColor          = 1,

        /// <summary> The Intensity property. </summary>
        kIntensity      = 2,

        /// <summary> The Classification property. </summary>
        kClassification = 3,

        /// <summary> The Normal property. </summary>
        kNormal         = 4,

        /// <summary> The Segmentation property. </summary>
        kSegmentation   = 5, 

        /// <summary> The Geo Graphic property. </summary>
        kGeoGraphic     = 6
    };

    ACRX_DECLARE_MEMBERS(AcDbPointCloudDefEx);

    /// <summary>
    /// Default constructor
    /// </summary>
    AcDbPointCloudDefEx();

    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~AcDbPointCloudDefEx();

    /// <summary>
    /// Returns the class version number that indicates which version of 
    /// AcDbPointCloudEx this object represents. This is primarily used during
    /// filing operations to determine what data to read or write.
    /// </summary>
    static int                  classVersion();

    // create / get point cloud dictionary
    //

    /// <summary>
    /// This function creates a new point cloud extension dictionary. 
    /// If the dictionary could not be created,
    /// then AcDbPointCloudDefEx::pointCloudExDictionary() will return 0.
    /// Otherwise, dictId is set by this function, and can be used as if the value had 
    /// been returned by pointCloudExDictionary().
    /// If the dictionary already exists, this method will simply set dictId to the
    /// existing dictionary's ID.   
    /// </summary>
    /// <param name="pDb">
    /// Input AutoCAD database in which to create the dictionary
    /// </param>
    /// <param name="dictId">
    /// Output parameter that will be set to the object ID of the newly created dictionary, or existing dictionary 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// Returns Acad::eAlreadyInDb if the dictionary "ACAD_POINTCLOUD_EX_DICT"
    /// already exists, and no new dictionary was created.
    /// Other values are returned if the dictionary could not be created or doesn't exist.
    /// </returns>
    static Acad::ErrorStatus    createPointCloudExDictionary(AcDbDatabase* pDb, AcDbObjectId& dictId);

    /// <summary>
    /// Returns the object ID of the point cloud extension dictionary in the
    /// specified drawing database or 0 if the dictionary was not found.
    /// </summary>
    /// <param name="pDb">
    /// Input AutoCAD database in which to search for the dictionary.
    /// </param>
    static AcDbObjectId         pointCloudExDictionary(AcDbDatabase* pDb);

    /// <summary>
    /// Returns a pointer to the point cloud extension dictionary for the
    /// given AcDbPointCloudDefEx's database, or NULL if the dictionary
    /// was not found.
    /// If the pDefEx is NULL, the AutoCAD database for the dictionary is
    /// typically acdbCurDwg().
    /// </summary>
    /// <param name="pDefEx">
    /// Input AcDbPointCloudDefEx object for which to find the dictionary.
    /// </param>
    static AcDbDictionary*      getPointCloudExDictionary(AcDbPointCloudDefEx* pDefEx);

    // Overridden methods from AcDbObject
    // 

    /// <summary>
    /// This function is called by dwgIn(). Its purpose is to allow this object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to the filer to use to read in the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler) override;

    /// <summary>
    /// This function is called by dwgOut(). Its purpose is to allow this object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to filer to use to write out the object's data .
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const override;

    /// <summary>
    /// This function is called by dxfIn(). Its purpose is to allow this object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to filer to use to read in the object's data.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler) override;

    /// <summary>
    /// This function is called by dxfOut(). Its purpose is to allow this object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to filer to use to write out the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const override;

    /// <summary>
    /// Called from within erase() before anything else is done.
    /// </summary>
    /// <param name="erasing">
    /// The erasing argument that was passed into the corresponding call to erase().
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if erasing is successful. 
    /// If this function returns anything other than Acad::eOk, then the 
    /// erase operation is immediately terminated.
    /// </returns>
    virtual Acad::ErrorStatus   subErase(Adesk::Boolean erasing) override;

    /// <summary>
    /// Returns a pointer to the ReCap point cloud data, which will
    /// be shared by all AcDbPointCloudEx entities that reference the same ReCap project.
    /// </summary>
    /// <remarks> Internal use only </remarks>
    Autodesk::RealityStudio::SDK::Interface::IRCData*   getRCData();

    /// <summary>
    /// Loads point cloud data from the source point cloud file. 
    /// If the point cloud is already loaded, Acad::eOk is returned.
    /// This will notifies all dependent AcDbPointCloudEx 
    /// entities to be redrawn.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput otherwise.
    /// </returns>
    Acad::ErrorStatus   load();

    /// <summary>
    /// Immediately unloads all point cloud data in the AcDbPointCloudDefEx, 
    /// but does not delete the 
    /// AcDbPointCloudDefEx itself. This method notifies all dependent
    /// AcDbPointCloudEx entities to be redrawn.
    /// </summary>
    /// <returns> Returns Acad::eOk if successful. </returns>
    Acad::ErrorStatus   unload();

    /// <summary>
    /// Returns Adesk::kTrue if the point cloud is loaded, or Adesk::kFalse otherwise.
    /// </summary>
    Adesk::Boolean      isLoaded() const;

    /// <summary>
    /// Returns the number of AcDbPointCloudEx entities in the current drawing
    /// that are dependent upon this object for display graphics. If the pointer
    /// pbLocked is non-zero, then this function will set the value at that 
    /// pointer to Adesk::kTrue if any dependent entities reside on locked 
    /// layers. It returns Adesk::kFalse otherwise.
    /// </summary>
    /// <param name="pbLocked">
    /// Input pointer value
    /// </param>
    int                 entityCount(Adesk::Boolean* pbLocked = 0) const;

    /// <summary>
    /// This function sets the pathname of the externally referenced point cloud
    /// file. The point cloud file path name is stored when the current drawing
    /// is saved. The point cloud extension definition is initialized and 
    /// a file descriptor is created for access to the point cloud file. 
    /// </summary>
    /// <param name="pPathName">
    /// Input path name of the point cloud
    /// </param>
    /// <returns> 
    /// Returns Acad::eOk if successful. 
    /// Returns Acad::eInvalidInput if the input path is invalid.
    /// </returns>
    Acad::ErrorStatus   setSourceFileName(const TCHAR* pPathName);

    /// <summary>
    /// Returns the path name of the externally referenced point cloud file name.
    /// This file name is saved in the DWG file with the object.
    /// </summary>
    const TCHAR*        sourceFileName() const;

    /// <summary>
    /// This function sets the active path name of the externally referenced
    /// point cloud file. The active path points to the file that is
    /// actually used to define the point cloud in the current drawing. 
    /// However, the active path is not persistent, and is not saved in the 
    /// drawing file. If pPathName does not point to a valid point cloud file,
    /// then the active path is unchanged.
    /// </summary>
    /// <param name="pPathName">
    /// Input path name of the point cloud
    /// </param>
    /// <returns> 
    /// Returns Acad::eOk if successful. 
    /// Returns Acad::eInvalidInput if the input path is invalid.
    /// </returns>
    Acad::ErrorStatus   setActiveFileName(const TCHAR* pPathName);

    /// <summary>
    /// Returns the path name of the actual file being currently used to define
    /// the point cloud.
    /// </summary>
    const TCHAR*        activeFileName() const;

    /// <summary>
    /// Returns the file extension of this definition's point cloud file.
    /// There are two types: RCP for a ReCap project file; RCS for a ReCap scan file.
    /// </summary>
    const TCHAR*        fileType() const;

    /// <summary>
    /// Returns the total point count for the point cloud file.
    /// </summary>
    unsigned long long  totalPointsCount() const;

    /// <summary>
    /// Returns the total region count for the point cloud file.
    /// </summary>
    int                 totalRegionsCount() const;

    /// <summary>
    /// Returns the total scan count for the point cloud file.
    /// </summary>
    int                 totalScansCount() const;

    /// <summary>
    /// Returns the default extent's width of the point cloud file.
    /// </summary>
    double              defaultWidth() const;

    /// <summary>
    /// Returns the default extent's length of the point cloud file.
    /// </summary>
    double              defaultLength() const;

    /// <summary>
    /// Returns the default extent's height of the point cloud file.
    /// </summary>
    double              defaultHeight() const;

    /// <summary>
    /// Returns the property state of a specified property in the point cloud file.
    /// This will tell if a given property is present in all, some, or none of the 
    /// scans that are in the current point cloud file.
    /// </summary>
    /// <param name="prop">
    /// Input property type of the point cloud
    /// </param>
    PropState           hasProperty(Property prop) const;

    /// <summary>
    /// Create a thumbnail image of the point cloud that is 
    /// a specified width and height.
    /// </summary>
    /// <param name="pBmpInfo">
    /// A pointer to the bitmap upon successful return. The caller is responsible
    /// for freeing this data structure using GlobalFree().
    /// </param>
    /// <param name="width">
    /// The width value of the preview bitmap
    /// </param>
    /// <param name="height">
    /// The height value of the preview bitmap
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    Acad::ErrorStatus   createThumbnailBitmap( BITMAPINFO*& pBmpInfo,
                                               int width,
                                               int height ) const;
    /// <summary>
    /// Gets the whole extents of attached point cloud
    /// </summary>
    AcDbExtents         extents() const;

    /// <summary>
    /// Gets the coordinate system name of attached point cloud 
    /// </summary>
    const TCHAR*        coordinateSystemName() const;

    /// <summary>
    /// Gets the file path of specified RCS
    /// </summary>
    /// <param name="guid">
    /// the GUID of the RCS
    /// </param>
    /// <returns>Returns file path</returns>
    const TCHAR*        getRcsFilePath(const AcString& guid) const;

    /// <summary>
    /// Gets the list which contains all RCS file path
    /// </summary>
    /// <param name="list">
    /// array used to contain all RCS file path
    /// </param>
    void                getAllRcsFilePaths(AcStringArray& list) const;

private:
    PointCloudDefExImp*   m_pImp;
    static int          m_nVersion;
};


class PointCloudDefReactorExImp;


//////////////////////////////////////////////////////////////////////////////
/// <summary>
/// The AcDbPointCloudDefReactorEx class is used to notify AcDbPointCloudEx
/// entities of relevant modifications to their associated AcDbPointCloudDefEx
/// object. It is a persistent reactor of AcDbPointCloudDefEx object, used to 
/// connect AcDbPointCloudEx entities.
/// 
/// Specifically, modification of the AcDbPointCloudDefEx object triggers the
/// redraw of each of its dependent AcDbPointCloudEx entities. 
/// Erasing the AcDbPointCloudDefEx object triggers the erasing of its dependent
/// AcDbPointCloudEx entities.
/// </summary>
class ACDB_PORT AcDbPointCloudDefReactorEx : public AcDbObject
{
public:
    /// <summary>
    /// Returns the class version number that indicates which version of 
    /// AcDbPointCloudEx this object represents. This is primarily used during
    /// filing operations to determine what data to read or write.
    /// </summary>
    static int                  classVersion();

    /// <summary>
    /// This method is used to temporarily disable notification of AcDbPointCloudEx 
    /// entities when an AcDbPointCloudDefEx object is modified or erased.
    /// 
    /// If enable is set to Adesk::kTrue, normal reactor operation is turned on.
    /// If set to Adesk::kFalse, reactor notification is turned off. 
    /// </summary>
    /// <param name="bEnable">
    /// Input Boolean to enable/disable notification 
    /// </param>
    static void                 setEnable(Adesk::Boolean bEnable);

    /// <summary>
    /// Returns a Boolean value whether the notification is enabled or disabled.
    /// </summary>
    static Adesk::Boolean       isEnabled();

    ACRX_DECLARE_MEMBERS(AcDbPointCloudDefReactorEx);

    /// <summary>
    /// Default constructor
    /// </summary>
    AcDbPointCloudDefReactorEx();

    /// <summary>
    /// Destructor
    /// </summary>
    virtual ~AcDbPointCloudDefReactorEx();

    // Overridden methods from AcDbObject
    // 

    /// <summary>
    /// This function is called by dwgIn(). Its purpose is to allow the object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to a filer to use to read in the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* pFiler) override;

    /// <summary>
    /// This function is called by dwgOut(). Its purpose is to allow the object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to a filer to use to write out the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* pFiler) const override;

    /// <summary>
    /// This function is called by dxfIn(). Its purpose is to allow the object to read in its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to a filer to use to read in the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* pFiler) override;

    /// <summary>
    /// This function is called by dxfOut(). Its purpose is to allow the object to write out its data. 
    /// </summary>
    /// <param name="pFiler">
    /// Pointer to filer to use to write out the object's data 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* pFiler) const override;

    // Notification
    //

    /// <summary>
    /// This method is called when the AcDbPointCloudDefEx object is deleted.
    /// It responds by deleting the AcDbPointCloudEx entity that owns the reactor.
    /// 
    /// A pErasing value of Adesk::kTrue indicates the definition object is being erased.
    /// A value of Adesk::kFalse indicates that the object is being restored (unerased).
    /// </summary>
    /// <param name="dbObj">
    /// Pointer to the AcDbPointCloudDefEx object sending the notification 
    /// </param>
    /// <param name="pErasing">
    /// Boolean indicating the erasing status 
    /// </param>
    virtual void                erased(const AcDbObject* dbObj,
                                        Adesk::Boolean pErasing = true) override;

    /// <summary>
    /// This method is called when the AcDbPointCloudDefEx object is modified.
    /// It responds by redrawing the AcDbPointCloudEx entity that owns the reactor.
    /// </summary>
    /// <param name="dbObj">
    /// Pointer to the AcDbPointCloudDefEx object sending the notification
    /// </param>
    virtual void                modified(const AcDbObject* dbObj) override;

private:
    static int m_version;
    static Adesk::Boolean       m_bIsEnabled;

    PointCloudDefReactorExImp*  m_pImp;
};
