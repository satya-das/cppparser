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

#pragma once

#include "AcDbCore2dDefs.h"

#pragma pack (push, 8)


/// <summary>
/// This class serves as a base class for custom classes that receive notification of 
/// changes to the geo coordinate system that are made by the AcDbGeoData::setCoordinateSystem() API
/// </summary>
class AcDbGeoDataReactor
{
public:
    virtual ~AcDbGeoDataReactor()
    {
    }

    /// <summary>
    /// This method will be called when the coordinate system is about to change.
    /// Custom classes can return Acad::eVetoed to veto the change.
    /// </summary>
    ///
    /// <param name="pDb">
    /// The database where the AcDbGeoData object resides.
    /// </param>
    ///
    /// <param name="oldId">
    /// The coordinate system ID that is about to be replaced.
    /// </param>
    ///
    /// <param name="newId">
    /// The coordinate system ID that is about to be set.
    /// </param>
    ///
    /// <returns>Custom classes can return Acad::eVetoed to veto the change.</returns>
    ///
    virtual Acad::ErrorStatus geoCoordinateSystemWillChange(AcDbDatabase* /*pDb*/, const AcString& /*oldId*/, const AcString& /*newId*/)
    {
        return Acad::eOk;
    }

    /// <summary>
    /// This method will be called after the coordinate system has been changed.
    /// </summary>
    ///
    /// <param name="pDb">
    /// The database where the AcDbGeoData object resides.
    /// </param>
    ///
    /// <param name="oldId">
    /// The coordinate system ID that has been replaced.
    /// </param>
    ///
    /// <param name="newId">
    /// The newly set coordinate system ID.
    /// </param>
    ///
    virtual void geoCoordinateSystemChanged(AcDbDatabase* /*pDb*/, const AcString& /*oldId*/, const AcString& /*newId*/)
    {
    }
};

// AcDbGeoData Object

///// <summary>
/// This object identifies the geographical space a design is located in.  It
/// also provides all the information necessary to accurately map a design
/// coordinate system to a locating (location) on earth (a lat lon based
/// system).  Furthermore this object provides a simple transformation to
/// support efforts like Google Earth and geo-tagging and enough information
/// to initialize geospatial applications for accurate coordinate system
/// transformation and place design on the earth and relative to each other.
///
/// The minimum requirements for a valid object are:
///
/// 1> Type of design coordinates.
/// 2> Design point
/// 3> Reference point.
/// 4> A "design coordinate to geodetic coordinate" mesh with at least one
/// point.
///
/// It is the association of the Design point and the Reference point which
/// provides the minimum level of georeferencing.  Any application, regardless
/// of its access to a coordinate conversion library, may obtain a georefernce
/// for the object by calling one of the transformation functions with, for
/// example, the values specified by the setDesignPoint function.
///
/// For many applications, this minimum level of georeferencing is adequate.
/// Positioning a house within Google Earth, for example.  To the degree that
/// additional information is provided, more precise and comprehensive
/// transformation results become available.
///
/// Note that if the design coordinate type is kCoordTypGrid, most all properties
/// related to local coordinates are unused.  Nevertheless, appropriate default
/// values are specified.
///
/// Use of scale factors for units specifications are required as the number of
/// linear units used in mapping applications exceeds by a substantial amount
/// the number of units supported by the AcDb::UnitsValue enumeration.  Also,
/// ocassionaly it is necessary to support units which have not been
/// encountered previously.
///
/// Finally, under normal circumstances, this object is created by the original
/// application.  That is the application which actually posts this object to
/// the database.  Consuming applications should consider this object to be a
/// constant.  The design, however, does not require that.
/// </summary>

class AcDbGeoData : public AcDbObject
{
public:

    /// <summary>
    /// The following enumerates the currently supported types of design
    /// coordinate systems.  The term design, in this context, refers to the
    /// actual numeric values contained in the host database.  For example, the
    ///actual real coordinates contained internall to objects in the host
    /// database.
    /// </summary>
    enum TypeOfCoordinates
    {
        /// <summary>
        /// Georeferencing information has not been established, or for some
        /// resaon is invalid or inconsistent.
        /// </summary>
        kCoordTypUnknown = 0,

        /// <summary>
        /// The design coordinate system is considered to be local, aka
        /// an engineering coordinate system.
        /// </summary>
        kCoordTypLocal,

        /// <summary>
        /// The design coordinate system is known to be a grid system.  That is,
        /// coordinates of a defined Coordinate Reference System of the Projected
        /// Type; implying that conversion to geodetic coordinates is possible
        /// with reasonably high precision.
        /// </summary>
        kCoordTypGrid,

        /// <summary>
        /// The design coordinate system is known to be a geodetic system.  That
        /// is, coordinates of a defined Coordinate Reference System of the
        /// Geographic type; implying that conversion to geodetic coordinates
        /// referenced to the Reference System is possible with reasonably
        /// high precision.
        /// </summary>
        kCoordTypGeographic
    };

    /// <summary>
    /// The following enumerates the algorithms currently supported for
    /// dealing with the Grid Scale Factor distortion introduced by the
    /// projection used in coordinate systems of the grid type.
    /// </summary>
    enum ScaleEstimationMethod {
        /// <summary>
        /// This algorithm simply does nothing, implying that innsofar as grid
        /// scale distortion is concerned, design coordinates are the same as
        /// grid coordinates.
        /// </summary>
        kScaleEstMethodUnity = 1,

        /// <summary>
        /// This algorithm uses a constant, user specified, scale factor to
        /// correct for grid scale distortion introduced by the projection upon
        /// which the the grid coordinate system (i.e. the projected coordinate
        /// reference specified by the setCoordinateSystem member function) is
        /// based.  The specific value used is specified by the setUserScale
        /// member function.
        /// </summary>
        kScaleEstMethodUserDefined,

        /// <summary>
        /// This algorithm uses the grid scale factor of the referenced 
        /// coordinate reference system (i.e. grid) as determined at the local
        /// coordinate system reference point.  Note that use of this algorithm
        /// implies that the projection upon which the specified grid is based
        /// is of the conformal type.
        /// </summary>
        kScaleEstMethodReferencePoint,

        /// <summary>
        /// This algorithm corrects for grid scale distortion by evaluating
        /// the grid scale distortion at each point in the local coordinate
        /// system.  Note that use of this algorithm implies that the
        /// projection upon which the specified grid is based is of the
        /// conformal type.
        /// </summary>
        kScaleEstMethodPrismoidal
    };

    ACDBCORE2D_DECLARE_MEMBERS(AcDbGeoData);

    ACDBCORE2D_PORT AcDbGeoData();
    ACDBCORE2D_PORT virtual ~AcDbGeoData();

    //=========================================================================
    // Host Database Methods
    //=========================================================================
    ACDBCORE2D_PORT AcDbObjectId blockTableRecordId() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setBlockTableRecordId(const AcDbObjectId& blockId);

    ACDBCORE2D_PORT Acad::ErrorStatus postToDb(AcDbObjectId& objId);
    ACDBCORE2D_PORT Acad::ErrorStatus eraseFromDb(void);

    //=========================================================================
    // Georeferencing Functions
    //=========================================================================
    /// <summary>
    /// Use these methods to examine/set the type of the design coordinates;
    /// that is the type of the actual coordinates which appear in the host
    /// database entities.  Creators of this object must specify this value,
    /// and consumers of this object should not change this value.
    /// Default = kCoordTypUnknown.
    /// </summary>
    ACDBCORE2D_PORT TypeOfCoordinates coordinateType() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setCoordinateType(TypeOfCoordinates designCoordinateType);

    /// <summary>
    /// Use these methods to examine/set the design coordinates of the point
    /// associated with the location specified by the setReferencePoint
    /// method.  As the method names imply, the coordinates used by these
    /// methods are always design coordinates.  Thus, if the coordinate type is
    /// kCoordTypLocal, these must be coordinates in the local coordinate system.
    ///
    /// While its association with the specified referencePoint is the primary
    /// function of designPoint coordinates, when design coordinates are of the
    /// kCoordTypLocal type, the designPoint coordinates are also used by the
    /// local to grid transformation for other purposes, such as the sea level
    /// correction and grid scale distortion calculations.
    /// NO DEFAULT:  msut be specified.
    /// </summary>
    ACDBCORE2D_PORT AcGePoint3d designPoint() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setDesignPoint(const AcGePoint3d& point);

    /// <summary>
    /// Use these methods to examine/set the Reference point to be associated
    /// with the design coordinates specified by the setDesignPoint method.
    /// In the case where coordinate type is kCoordTypLocal, the point argument
    /// is that of the grid coordinate that corresponds to the designPoint
    /// location in the grid coordinate system defined by the
    /// setCoordinateSystem method of this object.  In the case of design
    /// coordinates of the kCoordTypGrid or kCoordTypGeodetic types, this
    /// specification is not required.
    /// </summary>
    ACDBCORE2D_PORT AcGePoint3d referencePoint() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setReferencePoint(const AcGePoint3d& point);

    /// <summary>
    /// Unit scale is the factor by which design coordinate must be multiplied
    /// to produce meters.  In the case of the setHorizontalUnits method, the
    /// method calculates the appropriate scale factor.
    /// Default = 1.0 (i.e. meters)
    /// </summary>
    ACDBCORE2D_PORT double horizontalUnitScale() const;
    ACDBCORE2D_PORT AcDb::UnitsValue horizontalUnits () const;
    ACDBCORE2D_PORT Acad::ErrorStatus setHorizontalUnitScale(double horzUnitScale);
    ACDBCORE2D_PORT Acad::ErrorStatus setHorizontalUnits (AcDb::UnitsValue horizUnits);

    /// <summary>
    /// Unit scale is the factor by which design coordinate must be multiplied
    /// to produce meters.  In the case of the setVerticalUnits method, the
    /// method calculates the appropriate scale factor.
    /// Default = 1.0 (i.e. meters)
    /// </summary>
    ACDBCORE2D_PORT double verticalUnitScale() const;
    ACDBCORE2D_PORT AcDb::UnitsValue verticalUnits () const;
    ACDBCORE2D_PORT Acad::ErrorStatus setVerticalUnitScale(double vertUnitScale);
    ACDBCORE2D_PORT Acad::ErrorStatus setVerticalUnits(AcDb::UnitsValue vertUnits);

    //=========================================================================
    // Grid Coordinate System Methods
    //=========================================================================

    /// <summary>
    /// This property method sets the coordinate system definition in string
    /// form.  Besides filing in and out the content of the string to
    /// the Autocad DWG and DXF files, Autocad also handles the content
    /// of this string directly and validation is executed on it when the
    /// coordinate system library is available. Vertical application can still
    /// register the callback method setValidateCoordinateSystemCallback
    /// to validate this string by them self.
    /// Default = null string.
    /// </summary>
    ACDBCORE2D_PORT const ACHAR* coordinateSystem() const;
    /// <summary>
    /// </summary>
    /// <param name="coordinateSystem">
    /// The spatial coordinate system string.
    /// It can be the id of the coordinate system or the XML/WKT representation
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT Acad::ErrorStatus setCoordinateSystem(const ACHAR* coordinateSystem);

    /// <summary>
    /// Applications can define a method to validate the coordinate system passed
    /// to setCoordinaSystem by providing a static method with the following
    /// signature.  Register the method with AutoCAD using the
    /// AcDbGeoData::setValidateCoordinateSystemCallback method declared below
    /// </summary>
    typedef bool (*ACDBGEODATA_VALIDATE_CS)(const ACHAR* coordinateSystem);

    /// <summary>
    /// Use this function to set the callback method described above.  To
    /// unregister the application-specific callback, call this method with
    /// the NULL pointer as its only arguemnet.. 
    /// </summary>
    static ACDBCORE2D_PORT Acad::ErrorStatus setValidateCoordinateSystemCallback(ACDBGEODATA_VALIDATE_CS pFuncValidateCs);
    static ACDBCORE2D_PORT ACDBGEODATA_VALIDATE_CS getValidateCoordinateSystemCallback();

    //=========================================================================
    // Local Coordinate System Definition Properties
    //=========================================================================

    /// <summary>
    /// Use these methods to examine/specify the direction of the vertical axis
    /// of a local coordinate system.  The value of this vector is used only in
    /// the local to grid portion of a LocalToGridToReference transformation.
    /// Default = (0,0,1).
    /// </summary>
    ACDBCORE2D_PORT AcGeVector3d upDirection() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setUpDirection(const AcGeVector3d& vec);

    /// <summary>
    /// Use these methods examine/set the azimuth of the local grid Y axis relative
    /// to true north.  When returned as a double, the value returned is in radians
    /// east of true north.  The value of this vector is used to calculate
    /// coordinate rotation in the local to grid portion of a LocalToGridToReference
    /// transformation.  The local coordinates are rotated about the point specified
    /// by the setLocalPoint method.  The setNorthDirectionVector member expects
    /// a unit vector, and the provided vector will be normalized before use.
    /// Defult = (0,1);
    /// </summary>
    ACDBCORE2D_PORT double northDirection() const;            // radians
    ACDBCORE2D_PORT AcGeVector2d northDirectionVector() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setNorthDirectionVector(const AcGeVector2d& north);

    /// <summary>
    /// Use these methods to examine/set the algorithm which is to be used when
    /// applying grid scale distortion corrections in the local to grid portion
    /// of any transformation.  The scale factor to be applied is determined
    /// at the Reference point, and scaling is applied relative to the Design
    /// point.
    /// Default = kScaleEstMethodReferencePoint
    /// </summary>
    ACDBCORE2D_PORT ScaleEstimationMethod scaleEstimationMethod() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setScaleEstimationMethod(ScaleEstimationMethod value);

    /// <summary>
    /// Use these methods to get/set the user specified scale factor to be used
    /// in the local to grid portion of any transformation in such cases where
    /// the scale estimation method is set to kScaleEstMethodUserDefined.
    /// It then defines the scale correction applied at each point; scaling
    /// is applied relative to the specified Design point.
    /// Default = 1.0
    /// </summary>
    ACDBCORE2D_PORT double scaleFactor() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setScaleFactor(double value);

    /// <summary>
    /// Use these methods examine/set the state of the internal state which
    /// controls the application of the sea level correction to horizontal
    /// coordinates during the transformation process.  The setDoSeaLevelCorrection
    /// will return Acad::eOk only when the information necessary to perform
    /// the sea level correction has been provided by the creator of this object.
    /// Sea level corrections are applied relative to the Design point.
    /// Default = false;
    /// </summary>
    ACDBCORE2D_PORT bool doSeaLevelCorrection() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setDoSeaLevelCorrection(bool seaLevelCorrectionOn);

    /// <summary>
    /// Use this method to specify, in meters, the elevation which is to be
    /// used in the sea level correction algorithm.  In the event that this
    /// value is not specified by the object creator, attempts by the
    /// consuming application to activate sea level correction will fail.
    /// Default = NAN
    /// </summary>
    ACDBCORE2D_PORT double seaLevelElevation() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setSeaLevelElevation(double value);

    /// <summary>
    /// Use this method to specify the radius, in meters, of the ellipsoid
    /// model to be used in the sea level correction algorithm.  Should the
    /// creator fail to specify a value, the implied value is the meridional
    /// radius of curvature of the WGS84 ellipsoid at the latitude of the
    /// referencePoint.  Note:
    ///  1> This value is used only when sea level correction is active.
    ///  2> This is the radius of curvature on the surface of the ellipsoid
    ///     model (i.e. ellipsoidal height == 0.0).
    /// Default = Meridional radius of curvature of the WGS84 ellipsoid at
    ///           the latitude of the Reference Point.
    /// </summary>
    ACDBCORE2D_PORT double coordinateProjectionRadius() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setCoordinateProjectionRadius(double value);

    //=========================================================================
    // GEORSS support
    //=========================================================================
    /// <summary>
    /// This returns the georss tag.  This is automatically updated to the
    /// global point if set.  For more information see http://georss.org/
    /// </summary>
    ACDBCORE2D_PORT const ACHAR* geoRSSTag() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setGeoRSSTag(const ACHAR* rssTag);

    //=============================================================================
    // Observation Methods
    //=============================================================================
    // Geospatial (currently) has no requirements with regard to these members.
    ACDBCORE2D_PORT const ACHAR* observationFrom() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setObservationFrom(const ACHAR* from);

    // Geospatial (currently) has no requirements with regard to these members.
    ACDBCORE2D_PORT const ACHAR* observationTo() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setObservationTo(const ACHAR* to);

    // Geospatial (currently) has no requirements with regard to these members.
    ACDBCORE2D_PORT const ACHAR* observationCoverage() const;
    ACDBCORE2D_PORT Acad::ErrorStatus setObservationCoverage(const ACHAR* coverage);

    //=========================================================================
    // Mesh and coordinate system transformation support
    //=========================================================================

    /// <summary>
    /// The mesh point mapping maps a design point to a geodetic point referenced
    /// to the referenceDatum.  The more points there are the more accurate the
    /// transformation.  Source point arguments are always design space coordinates
    /// while destination point arguments are always geographic points where the
    /// first ordinate is longtiude in degrees relative to Greenwich where positive
    /// values indicate east longitude; and the second ordinate is latitude in
    /// degrees where positive values indicate north latitude.
    ///
    /// A valid mesh with at least one point is a requirement for a valid object.
    /// Default = empty
    /// </summary>
    ACDBCORE2D_PORT int numMeshPoints() const;
    ACDBCORE2D_PORT Acad::ErrorStatus getMeshPointMap(int index, AcGePoint2d& sourcePt, AcGePoint2d& destPt) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getMeshPointMaps(AcGePoint2dArray& sourcePts, AcGePoint2dArray& destPts) const;
    ACDBCORE2D_PORT Acad::ErrorStatus addMeshPointMap(int index, const AcGePoint2d& sourcePt, const AcGePoint2d& destPt);
    ACDBCORE2D_PORT Acad::ErrorStatus setMeshPointMaps(const AcGePoint2dArray& sourcePts, const AcGePoint2dArray& destPts);
    ACDBCORE2D_PORT Acad::ErrorStatus resetMeshPointMaps();

    /// <summary>
    /// the Mesh transformation is done via approximation from Delaunay triangulation.
    /// These methods allow the access to this triangulation mesh.
    /// </summary>
    ACDBCORE2D_PORT int numMeshFaces() const;
    ACDBCORE2D_PORT Acad::ErrorStatus getMeshFace(int faceIndex, int& p0, int& p1, int& p2) const;
    ACDBCORE2D_PORT Acad::ErrorStatus addMeshFace(int faceIndex, int p0, int p1,int p2);

    /// <summary>
    /// After adding points or triangles this method will update the transform.
    /// This has to be called before transforming any points.  This method must
    /// must be called before this object is posted to the host database.
    /// </summary>
    ACDBCORE2D_PORT Acad::ErrorStatus updateTransformationMatrix();

    //=============================================================================
    // Transformation
    //=============================================================================

    /// <summary>
    /// Performs the transformation indicated by the current content of this
    /// object.  The most accurate transformation available is performed.  In
    /// the case where coordinate type is kCoordTypLocal, x and y coordinates
    /// are in the units specified by the setHorizontalUnits method, z coordinates
    /// are in the units specified by the setVerticalUnits method.  In the case
    /// where coordinate type is kCoordTypGrid, x, y, and z coordinates are in the
    /// units indicated by the coordinate reference system definition provided.
    /// In those frequent cases where the coordinate reference system definition
    /// technique is incapable of specifying separate units for vertical ordinates,
    /// the z argument will be specified in the same units as x and y.
    ///
    /// lon arguments are in degrees relative to Greenwich where positive indicates
    /// east longitude.  lat arguments are in degrees where positive values indicate
    /// north latitude.  alt arguments are in meters and represent orthometric
    /// heights (i.e. heights above the geoid) where positive indicates positions
    /// above the geoid.
    ///
    /// All transformation functions will return Acad::eOk for a normal conversion.
    /// An error status will be returned if the host object is invalid for any
    /// reason (typically, the definition is incomplete or inconsistent with the
    /// specified design coordinate type).
    ///
    /// Can return warnings if the transformation was not successful:
    ///  eGeoDataOutOfRangeFallbackTriggered: outside of useful range of datum transformation, fallback method used
    ///  eGeoDataOutOfRangeNoTransformation: outside of useful range of datum transformation, coordinates unshifted.
    /// </summary>
    ACDBCORE2D_PORT Acad::ErrorStatus transformToLonLatAlt(const AcGePoint3d& dwgPt,
                                                     AcGePoint3d& geoPt) const;
    ACDBCORE2D_PORT Acad::ErrorStatus transformToLonLatAlt(double x,
                                                     double y,
                                                     double z,
                                                     double& lon,
                                                     double& lat,
                                                     double& alt) const;
    ACDBCORE2D_PORT Acad::ErrorStatus transformFromLonLatAlt(const AcGePoint3d& geoPt,
                                                       AcGePoint3d& dwgPt) const;
    ACDBCORE2D_PORT Acad::ErrorStatus transformFromLonLatAlt(double lon,
                                                       double lat,
                                                       double alt,
                                                       double& x,
                                                       double& y,
                                                       double& z) const;

    /// <summary>
    /// Applications can define alternative coordinate transformation methods by
    /// providing static methods with the following signatures.  Register the methods
    /// with AutoCAD using the AcDbGeoData::setTransformCallbacks method below.
    /// </summary>
    typedef Acad::ErrorStatus (*ACDBGEODATA_GEOGRAPHICTODWG)(const AcDbGeoData* pGeoData,
                                                             const double& dblLongitude,
                                                             const double& dblLatitude,
                                                             const double& dblAltitude,
                                                             double& dblDwgX,
                                                             double& dblDwgY,
                                                             double& dblDwgZ );
    typedef Acad::ErrorStatus (*ACDBGEODATA_DWGTOGEOGRAPHIC)(const AcDbGeoData* pGeoData, 
                                                             const double& dblDwgX,
                                                             const double& dblDwgY,
                                                             const double& dblDwgZ,
                                                             double& dblLongitude,
                                                             double& dblLatitude,
                                                             double& dblAltitude );

    /// <summary>
    /// Use this function to set callback methods.  To unregister the application-specific
    /// callbacks, call this method with NULL for the second and third arguments. 
    /// </summary>
    static ACDBCORE2D_PORT Acad::ErrorStatus setTransformCallbacks(const ACHAR* zoneDescription,
                                                             ACDBGEODATA_GEOGRAPHICTODWG pFuncGeoToDwg,
                                                             ACDBGEODATA_DWGTOGEOGRAPHIC pFuncDwgToGeo);
    static ACDBCORE2D_PORT const ACHAR* getTransformCallbacks(ACDBGEODATA_GEOGRAPHICTODWG& pFuncGeoToDwg,
                                                        ACDBGEODATA_DWGTOGEOGRAPHIC& pFuncDwgToGeo);

    //=========================================================================
    // Overridden methods from AcDbObject
    //=========================================================================
    ACDBCORE2D_PORT virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler*) override;
    ACDBCORE2D_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler*) const override;

    ACDBCORE2D_PORT virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler*) override;
    ACDBCORE2D_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler*) const override;
};

//=============================================================================
//  Global API functions 
//=============================================================================
//
ACDBCORE2D_PORT Acad::ErrorStatus acdbGetGeoDataObjId(AcDbDatabase *pDb, AcDbObjectId& objId);

// Insertion method.
ACDBCORE2D_PORT Acad::ErrorStatus acdbGetGeoDataTransform(AcDbDatabase*   pDbSource,
                                                    AcDbDatabase*   pDbTarget,
                                                    AcGePoint3d&    insertionPt,
                                                    double&         rotation,
                                                    double&         scale);


/// <summary>
/// This function registers a reactor derived from AcDbGeoDataReactor.
/// If the reactor is already on the list, it is not added again. 
/// The client needs to call acdbRemoveGeoDataReactor and delete
/// reactor object after it is done.
/// 
/// </summary>
///
/// <param name="reactor">
/// Pointer to the reactor to be added.
/// </param>
ACDBCORE2D_PORT Acad::ErrorStatus acdbRegisterGeoDataReactor(AcDbGeoDataReactor *reactor);

/// <summary>
/// This function removes a reactor from the list of AcDbGeoDataReactors.
/// </summary>
///
/// <param name="reactor">
/// Pointer to the reactor to be removed.
/// </param>
ACDBCORE2D_PORT void acdbRemoveGeoDataReactor(AcDbGeoDataReactor *reactor);

#pragma pack (pop)
