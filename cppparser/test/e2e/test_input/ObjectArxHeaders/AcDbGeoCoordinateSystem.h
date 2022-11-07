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
#include "acdb.h"
#include "AcString.h"
#include "gepnt3d.h"
#pragma pack (push, 8)

class AcDbGeoCoordinateSystem;

/// <summary>
/// The AcDbGeoDatum struct represents a datum definition of a coordinate reference system. 
/// General a datum specifies the relationship of a coordinate system to the earth. 
/// </summary>
///
struct AcDbGeoDatum
{
    /// <summary> ID of the datum definition. </summary>
    AcString id;
    
	/// <summary> Description of the datum definition. </summary>
    AcString desc;
};

/// <summary>
/// The AcDbGeoEllipsoid struct represents a ellipsoid definition of a coordinate reference system. 
/// An ellipsoid is a geometric figure that may be used to describe the approximate shape of the earth. 
/// </summary>
///
struct AcDbGeoEllipsoid
{
    /// <summary> ID of the ellipsoid definition. </summary>
    AcString id;
    
	/// <summary> Description of the ellipsoid definition. </summary>
    AcString desc;
    
	/// <summary> Length of the semi-minor axis of the ellipsoid definition. </summary>
    double   polarRadius; 

	/// <summary> Eccentricity value of the ellipsoid definition. </summary>
    double   eccentricity;
};

/// <summary>
/// The AcDbGeoProjectionParameter struct represents projection parameter of 
/// a coordinate reference system  
/// </summary>
///
struct AcDbGeoProjectionParameter
{
    /// <summary> The name of the projection parameter. </summary>
    AcString name;

    /// <summary> The value of the projection parameter. </summary>
    double   value;
};

/// <summary>
/// The AcDbGeoCoordinateSystemCategory class represents a category which holds 
/// string identifiers (IDs) referring to a group of coordinate reference systems  
/// </summary>
///
class AcDbGeoCoordinateSystemCategory 
{
public:
    /// <summary> Destructor. </summary>
    virtual ~AcDbGeoCoordinateSystemCategory(){};

    /// <summary> Returns the ID of the category. </summary>
    /// 
    /// <param name="categoryId">
    /// Input/output AcString object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus          getId(AcString& categoryId) const = 0;

    /// <summary> Returns number of coordinate systems belonging to this category. </summary>
    /// 
    /// <param name="num">
    /// Input/output integer.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus          getNumOfCoordinateSystem(int& num) const = 0;

    /// <summary> Returns the coordinate system at a given index. </summary>
    /// 
    /// <param name="index">
    /// Input integer.
    /// </param>
    /// <param name="pCoordSys">
    /// Input/output pointer to AcDbGeoCoordinateSystem object.
    /// Caller is responsible for deleting the returned object after use.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus          getCoordinateSystemAt(int index, AcDbGeoCoordinateSystem*& pCoordSys) const = 0;

    /// <summary> Returns all categories in a given array. </summary>
    /// 
    /// <param name="allCoordSys">
    /// Input/output array of AcDbGeoCoordinateSystem objects.
    /// Caller is responsible for deleting the returned AcDbGeoCoordinateSystem objects after use.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT static Acad::ErrorStatus createAll(AcArray<AcDbGeoCoordinateSystemCategory*>& allCategories);
};

/// <summary>
/// the AcDbGeoCoordinateSystem class represents a coordinate reference system (CRS) definition. 
/// A CRS is also being referred to as a spatial reference system (SRS). 
/// </summary>
///
class AcDbGeoCoordinateSystem 
{
public:
    /// <summary>
    /// brief Defines enums used to indicate the type of a coordinate reference system.
    /// </summary>
	///
    enum Type
    {
        /// <summary> brief Specifies the coordinate system is not set. </summary>
        kTypeUnknown = 0,

        /// <summary>
        /// brief Specifies that the coordinate system is arbitrary. It is not spatially bound to the earth.
        /// </summary>
        kTypeArbitrary = 1,

        /// <summary> brief Specifies that the coordinate system is geographic. </summary>
        kTypeGeographic = 2,
        /// <summary> brief Specifies that the coordinate system is projected. </summary>
        kTypeProjected = 3
    };

    /// <summary>
    /// brief Values that represent the coordinate reference system projection method types.
    /// </summary>
	///
    enum ProjectionCode
    {
        /// <summary> Unknown projection code. </summary>
        kProjectionCodeUnknown     = 0 ,

        /// <summary> Albers Equal Area Conic Projection. </summary>
        kProjectionCodeAlber       = 4,

        /// <summary> Azimuthal Equi-Distant; Elevated ellipsoid. </summary>
        kProjectionCodeAzede       = 59,

        /// <summary> Lambert Azimuthal Equal Area Projection. </summary>
        kProjectionCodeAzmea       = 11,

        /// <summary> Lambert Azimuthal Equidistant Projection. </summary>
        kProjectionCodeAzmed       = 7,

        /// <summary> Bipolar Oblique Conformal Conic Projection. </summary>
        kProjectionCodeBipolar     = 31,

        /// <summary> Bonne Pseudo conical Projection. </summary>
        kProjectionCodeBonne       = 24,

        /// <summary> Cassini Projection. </summary>
        kProjectionCodeCassini     = 22,

        /// <summary> Ekert Pseudocylindrical Projection; Number IV. </summary>
        kProjectionCodeEckert4     = 25, 

        /// <summary> Ekert Pseudocylindrical Projection; Number VI. </summary>
        kProjectionCodeEckert6     = 26, 

        /// <summary> Equidistant Conic Projection; aka Simple Conic. </summary>
        kProjectionCodeEdcnc       = 12,

        /// <summary> Equidistant Cylindrical Projection (Spherical only). </summary>
        kProjectionCodeEdcyl       = 20,

        /// <summary> Gauss-Kruger: Transverse Mercator without scale reduction parameter. </summary>
        kProjectionCodeGaussK      = 46, 

        /// <summary> Gnomonic Projection. </summary>
        kProjectionCodeGnomonic    = 19,

        /// <summary> Goode Homolosine Projection. </summary>
        kProjectionCodeGoode       = 28,

        /// <summary> Unrectified Hotine Oblique Mercator Projection; Sngl Point Form. </summary>
        kProjectionCodeHom1uv      = 1281,

        /// <summary> Rectified Hotine Oblique Mercator Projection; Single Point Form. </summary>
        kProjectionCodeHom1xy      = 1282,

        /// <summary> Unrectified Hotine Oblique Mercator Projection; Two Point Form. </summary>
        kProjectionCodeHom2uv      = 1283,

        /// <summary> Rectified Hotine Oblique Mercator Projection; Two Point Form. </summary>
        kProjectionCodeHom2xy      = 1284,

        /// <summary> Czech Krovak; original. </summary>
        kProjectionCodeKrovak      = 47,

        /// <summary> Czech Krovak; includes 1995 adjustment. </summary>
        kProjectionCodeKrvk95      = 51,

        /// <summary> Null Projection; produces/processes Latitude and Longitude. </summary>
        kProjectionCodeLL          = 1,

        /// <summary> Single standard parallel variation of the Lambert Conformal Conic. </summary>
        kProjectionCodeLm1sp       = 36,

        /// <summary> Double standard parallel variation of the Lambert Conformal Conic. </summary>
        kProjectionCodeLm2sp       = 37,

        /// <summary> Belgian variation of the Lambert Conformal Conic Projection. </summary>
        kProjectionCodeLmblg       = 38,

        /// <summary> Lambert Tangential Conformal Conic Projection. </summary>
        kProjectionCodeLmtan       = 8,

        /// <summary> Miller Cylindrical Projection. </summary>
        kProjectionCodeMiller      = 13,

        /// <summary> Minnesota DOT variation of the Lambert Conformal Conic. </summary>
        kProjectionCodeMndotl      = 41,

        /// <summary> Minnesota DOT variation of the Transverse Mercator projection. </summary>
        kProjectionCodeMndott      = 42, 

        /// <summary> Lallemand IMW Modified Polyconic Projection. </summary>
        kProjectionCodeModpc       = 10,

        /// <summary> Mollweide Projection. </summary>
        kProjectionCodeMollweid    = 27, 

        /// <summary> Mercator Cylindrical Projection. </summary>
        kProjectionCodeMrcat       = 6,

        /// <summary> Standard Mercator with a scale reduction factor instead of a standard parallel. </summary>
        kProjectionCodeMrcatK      = 49,

        /// <summary> Modified Stereographic Projection. </summary>
        kProjectionCodeMstero      = 15,

        /// <summary> Normal Aspect; Equal Area Cylindrical Projection. </summary>
        kProjectionCodeNeacyl      = 29,

        /// <summary> Non-georeferenced coordinate system.  Named Non-Earth by Map Info. </summary>
        kProjectionCodeNerth       = 55,

        /// <summary> New Zealand National Grid. </summary>
        kProjectionCodeNzealand    = 16,

        /// <summary> Oblique Mercator (obsolete). </summary>
        kProjectionCodeOblqM       = 5, 

        /// <summary> Oblique Cylindrical; a generalized version of the Swiss projection; specifically for Hungary. </summary>
        kProjectionCodeObqcyl      = 56, 

        /// <summary> Orthographic Projection. </summary>
        kProjectionCodeOrtho       = 18,

        /// <summary> 
        /// The Transverse Mercator with specific parameters; 
        /// with the OSTN02 grid shift tacked on.
        /// This is a combination of a projection and a datum shift.
        /// </summary>
        kProjectionCodeOstn02      = 60, 

        /// <summary>
        /// The Transverse Mercator with specific parameters;
        /// with the OSTN97 grid shift tacked on.  
        /// This is a combination of a projection and a datum shift. 
        /// </summary>
        kProjectionCodeOstn97      = 58, 

        /// <summary> Oblique Stereographic. </summary>
        kProjectionCodeOstro       = 34,

        /// <summary> Hassler American Polyconic Projection. </summary>
        kProjectionCodePlycn       = 9,

        /// <summary> Polar stereographic. </summary>
        kProjectionCodePstro       = 33,

        /// <summary> Polar stereographic with standard latitude. </summary>
        kProjectionCodePstrosl     = 53, 

        /// <summary> cs_PRJCOD_RSKEW. </summary>
        kProjectionCodeRskew       = 1285,

        /// <summary> cs_PRJCOD_RSKEWC. </summary>
        kProjectionCodeRskewc      = 1286,

        /// <summary> cs_PRJCOD_RSKEWO - Rectified Skew Orthomorphic; Skew Azimuth at Rectified Origin. </summary>
        kProjectionCodeRskewo      = 1287, 

        /// <summary> Robinson Cylindrical Projection. </summary>
        kProjectionCodeRobinson    = 23, 

        /// <summary> Sinusoidal Projection; Optionally Interrupted. </summary>
        kProjectionCodeSinus       = 17,

        /// <summary> South Oriented variation of the Transverse Mercator Projection. </summary>
        kProjectionCodeSotrm       = 43, 

        /// <summary> Synder's Oblique Stereographic. </summary>
        kProjectionCodeSstro       = 35, 

        /// <summary> "Swiss" Projection. </summary>
        kProjectionCodeSwiss       = 32,

        /// <summary> Combination of Transverse Mercator and a polynomial expansion used in Denmark. </summary>
        kProjectionCodeSys34       = 57, 

        /// <summary> 
        /// Combination of Transverse Mercator and polynomial expansion used in Denmark.
        /// Polynomials are of the 1999 vintage.
        /// </summary>
        kProjectionCodeSys34_99    = 61,

        /// <summary> Transverse Aspect; Equal Area Cylindrical Projection. </summary>
        kProjectionCodeTeacyl      = 30,

        /// <summary> Transverse Mercator or Gauss Kruger Projection. </summary>
        kProjectionCodeTm          = 3, 

        /// <summary> Transverse Mercator with affine post-processor. </summary>
        kProjectionCodeTrmeraf     = 54,

        /// <summary> Transverse Mercator using Kruger Formulation. </summary>
        kProjectionCodeTrmrkrg     = 62,

        /// <summary> Transverse Mercator per J. P. Snyder. </summary>
        kProjectionCodeTrmrs       = 45,

        /// <summary> Van Der Grinten Projection. </summary>
        kProjectionCodeVdgrntn     = 21, 

        /// <summary> Wisconsin County Coord System variation; Lambert Conformal Conic. </summary>
        kProjectionCodeWccsl       = 39, 

        /// <summary> Wisconsin County Coord System variation; Transverse Mercator projection. </summary>
        kProjectionCodeWccst       = 40, 

        /// <summary> The UTM direct variation of the Transverse Mercator projection. </summary>
        kProjectionCodeUtm         = 44, 

        /// <summary> Winkel-Tripel; variable standard latitude. </summary>
        kProjectionCodeWinkl       = 63, 

        /// <summary> Nerth with scale and rotation. </summary>
        kProjectionCodeNrthsrt     = 64, 

        /// <summary> Lambert Conformal Conic with affine post-processor. </summary>
        kProjectionCodeLmbrtaf     = 65, 

        /// <summary> 
        /// Combination of Transverse Mercator and polynomial expansion used in Denmark.
        /// Polynomials are of the 2001 vintage. 
        /// </summary>
        kProjectionCodeSys34_01    = 66, 

        /// <summary> Equidistant Cylindrical Projection, Ellipsoidal or Spherical. </summary>
        kProjectionCodeEdcylE      = 67, 

        /// <summary> Implementation of Plate Carree as a variation of the Equidistant Cylindrical. </summary>
        kProjectionCodePlateCarree = 68, 

        /// <summary> Popular Visualization Pseudo Mercator (aka Google Earth). </summary>
        kProjectionCodePvMercator  = 69,
    };

    /// <summary>
    /// brief Values that represent the linear or angular unit.
    /// </summary>
	///
    enum Unit
    {
        /// <summary> the unit is not set. </summary>
        kUnitUnknown = 0,
        kUnitMeter = 1,
        kUnitFoot = 2,
        kUnitInch = 3,
        kUnitIFoot = 4,
        kUnitClarkeFoot = 5,
        kUnitIInch = 6,
        kUnitCentimeter = 7,
        kUnitKilometer = 8,
        kUnitYard = 9,
        kUnitSearsYard = 10,
        kUnitMile = 11,
        kUnitIYard = 12,
        kUnitIMile = 13,
        kUnitKnot = 14,
        kUnitNautM = 15,
        kUnitLat66 = 16,
        kUnitLat83 = 17,
        kUnitDecimeter = 18,
        kUnitMillimeter = 19,
        kUnitDekameter = 20,
        kUnitHectometer = 21,
        kUnitGermanMeter = 22,
        kUnitCaGrid = 23,
        kUnitClarkeChain = 24,
        kUnitGunterChain = 25,
        kUnitBenoitChain = 26,
        kUnitSearsChain = 27,
        kUnitClarkeLink = 28,
        kUnitGunterLink = 29,
        kUnitBenoitLink = 30,
        kUnitSearsLink = 31,
        kUnitRod = 32,
        kUnitPerch = 33,
        kUnitPole = 34,
        kUnitFurlong = 35,
        kUnitRood = 36,
        kUnitCapeFoot = 37,
        kUnitBrealey = 38,
        kUnitSearsFoot = 39,
        kUnitGoldCoastFoot = 40,
        kUnitMicroInch = 41,
        kUnitIndianYard = 42,
        kUnitIndianFoot = 43,
        kUnitIndianFt37 = 44,
        kUnitIndianFt62 = 45,
        kUnitIndianFt75 = 46,
        kUnitIndianYd37 = 47,
        kUnitDecameter = 48,
        kUnitInternationalChain = 49,
        kUnitInternationalLink = 50,
        kUnitDegree = 1001,
        kUnitGrad = 1002,
        kUnitGrade = 1003,
        kUnitMapInfo = 1004,
        kUnitMil = 1005,
        kUnitMinute = 1006,
        kUnitRadian = 1007,
        kUnitSecond = 1008,
        kUnitDecisec = 1009,
        kUnitCentisec = 1010,
        kUnitMillisec = 1011,
    };

    /// <summary> 
    /// virtual destructor
    /// </summary>
    virtual ~AcDbGeoCoordinateSystem() {};

    /// <summary> 
    /// Get this CRS's identifier string, which is also being referred to as a (coordinate system) code.
    /// The id returned always belongs to the ADSK namespace and is never prefixed.
    /// </summary>
    /// 
    /// <param name="coordSysId">
    /// Input/output AcString object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getId(AcString& coordSysId) const = 0;

    /// <summary> 
    /// Get this CRS's EPSG code.
    /// </summary>
    /// 
    /// <param name="epsgCode">
    /// Input/output integer.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getEpsgCode(int& epsgCode) const = 0;

    /// <summary> 
    /// Get this CRS's type, e.g. geographic, projected, arbitrary etc.
    /// </summary>
    /// 
    /// <param name="type">
    /// Input/output AcDbGeoCoordinateSystem::Type.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getType(AcDbGeoCoordinateSystem::Type& type) const = 0;

    /// <summary> 
    /// Get this definition's description, if there's any.
    /// </summary>
    /// 
    /// <param name="coordSysDesc">
    /// Input/output AcString object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getDescription(AcString& coordSysDesc) const = 0;

    /// <summary> 
    /// Gets the unit of the coordinate system axis of this CRS. 
    /// All axis contains the same unit.
    /// </summary>
    /// 
    /// <param name="unit">
    /// Input/output AcDb::UnitsValue. AcDb::kUnitsUndefined is set if the
    /// underlying spatial unit cannot be converted to AcDb::UnitsValue directly.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getUnit(AcDb::UnitsValue& unit) const = 0;

    /// <summary> 
    /// Gets the unit of the coordinate system axis of this CRS. 
    /// All axis contains the same unit.
    /// </summary>
    /// 
    /// <param name="unit">
    /// Input/output AcDbGeoCoordinateSystem::Unit.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getUnit(AcDbGeoCoordinateSystem::Unit& unit) const = 0;

    /// <summary> 
    /// Gets a factor, that the length units of this CRS instance must be
    /// multiplied with to calculate the equivalent in meters.
    /// If the CRS is geographic, this value represents the distance in meters of 1 deg
    /// measured along the equatorial great circle of the underlying ellipsoid.
    /// </summary>
    /// 
    /// <param name="unitScale">
    /// Input/output double.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getUnitScale(double& unitScale) const = 0;
 
    /// <summary> 
    /// Gets the projection method of this CRS. 
    /// The projection is the conversion of the CRS..
    /// </summary>
    /// 
    /// <param name="prjCode">
    /// Input/output AcDbGeoCoordinateSystem::ProjectionCode object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getProjectionCode(AcDbGeoCoordinateSystem::ProjectionCode& prjCode) const = 0;
 
    /// <summary> 
    /// Gets the projection parameters of this CRS. 
    /// </summary>
    /// 
    /// <param name="prjParams">
    /// Input/output array of AcDbGeoProjectionParameter object.
    /// </param>
    /// <param name="includeSpecialParams">
    /// Input boolean to indicate if the special projection parameters should be counted.
    /// The special projection parameters may include some of the followings:
    /// Origin Longitude
    /// Origin Latitude
    /// False Easting
    /// False Northing
    /// Scale Reduction
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getProjectionParameters(AcArray<AcDbGeoProjectionParameter>& prjParams,
                                                      bool includeSpecialParams) const = 0;

    /// <summary> 
    /// Gets the datum, if any, this CRS is reference to.
    /// </summary>
    /// 
    /// <param name="datum">
    /// Input/output AcDbGeoDatum object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getDatum(AcDbGeoDatum& datum) const = 0;

    /// <summary> 
    /// Gets the related ellipsoid.
    /// Note: When a CRS contains an ellipsoid it will not be geodetic and
    /// the datum reference will be nothing..
    /// </summary>
    /// 
    /// <param name="ellipsoid">
    /// Input/output AcDbGeoEllipsoid object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getEllipsoid(AcDbGeoEllipsoid& ellipsoid) const = 0;

    /// <summary> 
    /// Gets the projection method parameter offset easting of this CRS.
    /// </summary>
    /// 
    /// <param name="offsetVec">
    /// Input/output AcGeVector2d object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getOffset(AcGeVector2d& offsetVec) const = 0;

    /// <summary> 
    /// Get the Cartesian extent of this CRS's.
    /// </summary>
    /// 
    /// <param name="exts">
    /// Input/output AcDbExtents2d object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getCartesianExtents(AcDbExtents2d& exts) const = 0;

    /// <summary> 
    /// Get the geodetic extent of this CRS's, the range of longitude and latitude.
    /// </summary>
    /// 
    /// <param name="exts">
    /// Input/output AcDbExtents2d object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getGeodeticExtents(AcDbExtents2d& exts) const = 0;

    /// <summary> 
    /// Get the representation string of this CRS's in XML format.
    /// </summary>
    /// 
    /// <param name="strXml">
    /// Input/output AcString object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getXmlRepresentation(AcString& strXml) const = 0;

    /// <summary> 
    /// Get the representation string of this CRS's in WKT format.
    /// </summary>
    /// 
    /// <param name="strWkt">
    /// Input/output AcString object.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getWktRepresentation(AcString& strWkt) const = 0;

    /// <summary> 
    /// Instantiates a new AcDbGeoCoordinateSystem object from the current virtual catalog. 
    /// If no such CRS definition exists but the input string contains enough information(i.e. WKT or XML) 
    /// for constructing a temporary AcDbGeoCoordinateSystem instance, this is being returned instead.
    /// </summary>
    /// <param name="coordSysIdOrFullDef">
    /// The ID, WKT or the (proprietary) XML representation of the CRS definition to load. Optionally, the string can be
    /// prefixed by the ID's namespace and a colon (:) where the following are supported: ADSK, EPSG, SRID, ORACLE. If no namespace
    /// has been specified, the ID is assumed to be a default Autodesk coordinate system identifier. If no definition exists with such a code
    /// and if it consists of numbers only, the ID string is considered an EPSG code.
    /// Valid examples are:
    ///    - LL84 > Autodesk identifier (default)
    ///    - ADSK:LL84 > Autodesk identifier
    ///    - EPSG:4326 > EPSG identifier
    ///    - SRID:4326 > Oracle SRID
    ///    - ORACLE:8307 > Oracle SRID
    ///    - 4326 > EPSG identifier
    ///    - GEOGCS["WGS 84", DATUM["WGS_1984", SPHEROID[...]]] > WKT    
    /// </param>
    /// <param name="pCoordSys">
    /// Input/output pointer to AcDbGeoCoordinateSystem object.
    /// Caller is responsible for deleting the returned object after use.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT static Acad::ErrorStatus create(const AcString& coordSysIdOrFullDef, 
                                              AcDbGeoCoordinateSystem*& pCoordSys);

    /// <summary> 
    /// Instantiates a new AcDbGeoCoordinateSystem object for every existing, 
    /// persistent project CRS definition from the current virtual catalog,
    /// when the passed in geodetic point within the geodetic extents of the CRS.
    /// </summary>
    /// 
    /// <param name="geoPt">
    /// Input geodetic point in (longitude, latitude, altitude) format.
    /// </param>
    /// <param name="allCoordSys">
    /// Input/output array of AcDbGeoCoordinateSystem objects.
    /// Caller is responsible for deleting the returned AcDbGeoCoordinateSystem objects after use.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT static Acad::ErrorStatus createAll(const AcGePoint3d& geoPt,
                                                 AcArray<AcDbGeoCoordinateSystem*>& allCoordSys);

    /// <summary> 
    /// Instantiates a new AcDbGeoCoordinateSystem object for every existing, 
    /// persistent CRS definition from the specified catalog.
    /// </summary>
    /// 
    /// <param name="allCoordSys">
    /// Input/output array of AcDbGeoCoordinateSystem objects.
    /// Caller is responsible for deleting the returned AcDbGeoCoordinateSystem objects after use.
    /// </param>
    /// <param name="pCategory">
    /// Input category.
    /// All existing and persistent CRS definitions are returned when pGategoery is NULL.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT static Acad::ErrorStatus createAll(AcArray<AcDbGeoCoordinateSystem*>& allCoordSys,
                                                 const AcDbGeoCoordinateSystemCategory* pCategory = NULL);

};

/// <summary>
/// the AcDbGeoCoordinateSystemTransformer class represents a transformer object 
/// which is used to transform points from the source CRS to the target CRS. 
/// </summary>
///
class AcDbGeoCoordinateSystemTransformer 
{
public:
    /// <summary> 
    /// virtual destructor
    /// </summary>
    virtual ~AcDbGeoCoordinateSystemTransformer() {};

    /// <summary> 
    /// get the source CRS id.
    /// </summary>
    /// <param name="sourceCoordSysId">
    /// Input/output source CRS id.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getSourceCoordinateSystemId(AcString& sourceCoordSysId) const = 0;

    /// <summary> 
    /// get the target CRS id.
    /// </summary>
    /// <param name="targetCoordSysId">
    /// Input/output target CRS id.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus getTargetCoordinateSystemId(AcString& targetCoordSysId) const = 0;

    /// <summary> 
    /// transform a point from source CRS to target CRS. 
    /// </summary>
    /// <param name="pointIn">
    /// Input point in the source CRS.
    /// </param>
    /// <param name="pointOut">
    /// Output point in the target CRS.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus transformPoint(const AcGePoint3d& pointIn, AcGePoint3d& pointOut) const = 0;

    /// <summary> 
    /// transform a group of points from source CRS to target CRS. 
    /// </summary>
    /// <param name="pointsIn">
    /// Input point array in the source CRS.
    /// </param>
    /// <param name="pointsOut">
    /// Output point array in the target CRS.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    virtual Acad::ErrorStatus transformPoints(const AcGePoint3dArray& pointsIn, AcGePoint3dArray& pointsOut) const = 0;

    /// <summary> 
    /// transform a group of points from source CRS to target CRS. 
    /// </summary>
    /// <param name="sourceCoordSysId">
    /// Input source CRS id.
    /// </param>
    /// <param name="targetCoordSysId">
    /// Input target CRS id.
    /// </param>
    /// <param name="pointIn">
    /// Input point in the source CRS.
    /// </param>
    /// <param name="pointOut">
    /// Output point in the target CRS.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT static Acad::ErrorStatus transformPoint(const AcString& sourceCoordSysId,
                                                      const AcString& targetCoordSysId,
                                                      const AcGePoint3d& pointIn,
                                                      AcGePoint3d& pointOut);

    /// <summary> 
    /// transform a point from source CRS to target CRS. 
    /// </summary>
    /// <param name="sourceCoordSysId">
    /// Input source CRS id.
    /// </param>
    /// <param name="targetCoordSysId">
    /// Input target CRS id.
    /// </param>
    /// <param name="pointsIn">
    /// Input point array in the source CRS.
    /// </param>
    /// <param name="pointsOut">
    /// Output point array in the target CRS.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT static Acad::ErrorStatus transformPoints(const AcString& sourceCoordSysId,
                                                       const AcString& targetCoordSysId,
                                                       const AcGePoint3dArray& pointsIn,
                                                       AcGePoint3dArray& pointsOut);

    /// <summary> 
    /// Instantiates a new AcDbGeoCoordinateSystemTransformer object 
    /// from the source CRS and target CRS.
    /// </summary>
    /// <param name="sourceCoordSysId">
    /// Input source CRS id.
    /// </param>
    /// <param name="targetCoordSysId">
    /// Input target CRS id.
    /// </param>
    /// <returns>Returns Acad::eOk if successful.</returns>
    ///
    ACDBCORE2D_PORT static Acad::ErrorStatus create(const AcString& sourceCoordSysId, 
                                              const AcString& targetCoordSysId,
                                              AcDbGeoCoordinateSystemTransformer*& pCoordSysTransformer);

};

#pragma pack (pop)
