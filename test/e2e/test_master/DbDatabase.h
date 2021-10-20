/////////////////////////////////////////////////////////////////////////////// 
// Copyright ?2006, Open Design Alliance Inc. ("Open Design") 
// 
// This software is owned by Open Design, and may only be incorporated into 
// application programs owned by members of Open Design subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with 
// Open Design. The structure and organization of this Software are the valuable 
// trade secrets of Open Design and its suppliers. The Software is also protected 
// by copyright law and international treaty provisions. You agree not to 
// modify, adapt, translate, reverse engineer, decompile, disassemble or 
// otherwise attempt to discover the source code of the Software. Application 
// programs incorporating this software must include the following statement 
// with their copyright notices: 
// 
//      DWGdirect ?2006 by Open Design Alliance Inc. All rights reserved. 
// 
// By use of this software, you acknowledge and accept the terms of this 
// agreement. 
/////////////////////////////////////////////////////////////////////////////// 
#ifndef _ODDBDATABASE_INCLUDED_
#  define _ODDBDATABASE_INCLUDED_
#  include "DD_PackPush.h"
#  include "RxObject.h"
#  include "DbObjectId.h"
#  include "RxObjectImpl.h"
#  include "OdString.h"
#  include "DbDate.h"
#  include "OdCodePage.h"
#  include "OdToolKit.h"
#  include "DbObject.h"
#  include "CmColor.h"
#  include "DbSecurity.h"
#  include "DbSystemServices.h"
#  include "ViewportDefs.h"
class OdDbObject;
class OdDbSymbolTable;
class OdDbBlockTable;
class OdDbTextStyleTable;
class OdDbLinetypeTable;
class OdDbLayerTable;
class OdDbViewTable;
class OdDbUCSTable;
class OdDbUCSTable;
class OdDbViewportTable;
class OdDbRegAppTable;
class OdDbDimStyleTable;
class OdDbDimStyleTableRecord;
class OdDbBlockTableRecord;
class OdDbTextStyleTableRecord;
class OdDbRegAppTableRecord;
class OdDbLinetypeTableRecord;
class OdDbHostAppServices;
class OdDbLayout;
class OdDbLayoutManagerReactor;
class OdGsView;
class OdGsDevice;
class OdGsDCRect;
class OdDbDictionary;
class OdDbDictionaryWithDefault;
class OdDbFiler;
class OdDbIdMapping;
class OdDbDatabaseReactor;
class OdDbSpatialFilter;
class OdDbLayerFilter;
class OdDbAuditInfo;
class OdDbUndoController;
class OdDbTransactionReactor;
class OdDbEntity;
class OdGePoint2d;
class OdGePoint3d;
class OdGeMatrix3d;
class OdGeVector3d;
class OdDbDwgFiler;
class OdGsModel;
class OdStreamBuf;
class OdThumbnailImage;
class OdDbDatabaseImpl;
class OdResBuf;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdResBuf object pointers. 
*/
typedef OdSmartPtr<OdResBuf> OdResBufPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbDictionary object pointers. 
*/
typedef OdSmartPtr<OdDbDictionary> OdDbDictionaryPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbDictionaryWithDefault object pointers. 
*/
typedef OdSmartPtr<OdDbDictionaryWithDefault> OdDbDictionaryWithDefaultPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbSymbolTable object pointers. 
*/
typedef OdSmartPtr<OdDbSymbolTable> OdDbSymbolTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbBlockTable object pointers. 
*/
typedef OdSmartPtr<OdDbBlockTable> OdDbBlockTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbLayerTable object pointers. 
*/
typedef OdSmartPtr<OdDbLayerTable> OdDbLayerTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbTextStyleTable object pointers. 
*/
typedef OdSmartPtr<OdDbTextStyleTable> OdDbTextStyleTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbViewTable object pointers. 
*/
typedef OdSmartPtr<OdDbViewTable> OdDbViewTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbUCSTable object pointers. 
*/
typedef OdSmartPtr<OdDbUCSTable> OdDbUCSTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbViewportTable object pointers. 
*/
typedef OdSmartPtr<OdDbViewportTable> OdDbViewportTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbRegAppTable object pointers. 
*/
typedef OdSmartPtr<OdDbRegAppTable> OdDbRegAppTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbDimStyleTable object pointers. 
*/
typedef OdSmartPtr<OdDbDimStyleTable> OdDbDimStyleTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbLinetypeTable object pointers. 
*/
typedef OdSmartPtr<OdDbLinetypeTable> OdDbLinetypeTablePtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbBlockTableRecord object pointers. 
*/
typedef OdSmartPtr<OdDbBlockTableRecord> OdDbBlockTableRecordPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbDimStyleTableRecord object pointers. 
*/
typedef OdSmartPtr<OdDbDimStyleTableRecord> OdDbDimStyleTableRecordPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbTextStyleTableRecord object pointers. 
*/
typedef OdSmartPtr<OdDbTextStyleTableRecord> OdDbTextStyleTableRecordPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbRegAppTableRecord object pointers. 
*/
typedef OdSmartPtr<OdDbRegAppTableRecord> OdDbRegAppTableRecordPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbDimStyleTableRecord object pointers. 
*/
typedef OdSmartPtr<OdDbDimStyleTableRecord> OdDbDimStyleTableRecordPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbLinetypeTableRecord object pointers. 
*/
typedef OdSmartPtr<OdDbLinetypeTableRecord> OdDbLinetypeTableRecordPtr;
class OdSecurityParams;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdSecurityParams object pointers. 
*/
typedef OdSmartPtr<OdSecurityParams> OdSecurityParamsPtr;
class OdFileDependencyManager;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdFileDependencyManager object pointers. 
*/
typedef OdSmartPtr<OdFileDependencyManager> OdFileDependencyManagerPtr;
/** Description: 
  This template class is a specialization of the OdSmartPtr class for OdDbDatabase object pointers. 
*/
typedef OdSmartPtr<OdDbDatabase> OdDbDatabasePtr;
/** Description: 
 
    {group:DD_Namespaces} 
*/
namespace OdDb
{
  enum UnitsValue {
    kUnitsUndefined    = 0, 
    kUnitsInches       = 1, 
    kUnitsFeet         = 2, 
    kUnitsMiles        = 3, 
    kUnitsMillimeters  = 4, 
    kUnitsCentimeters  = 5, 
    kUnitsMeters       = 6, 
    kUnitsKilometers   = 7, 
    kUnitsMicroinches  = 8, 
    kUnitsMils         = 9, 
    kUnitsYards        = 10, 
    kUnitsAngstroms    = 11, 
    kUnitsNanometers   = 12, 
    kUnitsMicrons      = 13, 
    kUnitsDecimeters   = 14, 
    kUnitsDekameters   = 15, 
    kUnitsHectometers  = 16, 
    kUnitsGigameters   = 17, 
    kUnitsAstronomical = 18, 
    kUnitsLightYears   = 19, 
    kUnitsParsecs      = 20, 
    kUnitsMax          = kUnitsParsecs
  };
  enum SaveType {
    kDwg   = 0,   // Save as DWG file 
    kDxf   = 1,   // Save as DXF file 
    kDxb   = 2,   // Save as binary DXF file 
    kUnknown = -1 // Database was created from scratch
  };
  enum EndCaps {
    kEndCapNone       =  0, 
    kEndCapRound      =  1, 
    kEndCapAngle      =  2, 
    kEndCapSquare     =  3
  };
  enum JoinStyle {
    kJnStylNone       =  0, 
    kJnStylRound      =  1, 
    kJnStylAngle      =  2, 
    kJnStylFlat       =  3
  };
  enum DuplicateLinetypeLoading {
    kDltNotApplicable = 0, // Not Applicable. 
    kDltIgnore        = 1, // Ignore duplicate LineTypes. 
    kDltReplace       = 2  // Replace duplicate LineTypes.
  };
  enum TimeZone {
    kInternationalDateLine      = -12000,   //(GMT-12:00) International Date Line West 
    kMidwayIsland               = -11000,   //(GMT-11:00) Midway Island, Samoa 
    kHawaii                     = -10000,   //(GMT-10:00) Hawaii 
    kAlaska                     = -9000,    //(GMT-09:00) Alaska 
    kPacific                    = -8000,    //(GMT-08:00) Pacific Time (US & Canada); Tijuana 
    kMountain                   = -7000,    //(GMT-07:00) Mountain Time (US & Canada) 
    kArizona                    = -7001,    //(GMT-07:00) Arizona 
    kMazatlan                   = -7002,    //(GMT-07:00) Chihuahua, La Paz, Mazatlan 
    kCentral                    = -6000,    //(GMT-06:00) Central Time (US & Canada) 
    kCentralAmerica             = -6001,    //(GMT-06:00) Central America 
    kMexicoCity                 = -6002,    //(GMT-06:00) Guadalajara, Mexico City, Monterrey 
    kSaskatchewan               = -6003,    //(GMT-06:00) Saskatchewan 
    kEastern                    = -5000,    //(GMT-05:00) Eastern Time (US & Canada) 
    kIndiana                    = -5001,    //(GMT-05:00) Indiana (East) 
    kBogota                     = -5002,    //(GMT-05:00) Bogota, Lima, Quito 
    kAtlanticCanada             = -4000,    //(GMT-04:00) Atlantic Time (Canada) 
    kCaracas                    = -4001,    //(GMT-04:00) Caracas, La Paz 
    kSantiago                   = -4002,    //(GMT-04:00) Santiago 
    kNewfoundland               = -3300,    //(GMT-03:30) Newfoundland 
    kBrasilia                   = -3000,    //(GMT-03:00) Brasilia 
    kBuenosAires                = -3001,    //(GMT-03:00) Buenos Aires, Georgetown 
    kGreenland                  = -3002,    //(GMT-03:00) Greenland 
    kMidAtlantic                = -2000,    //(GMT-02:00) Mid-Atlantic 
    kAzores                     = -1000,    //(GMT-01:00) Azores 
    kCapeVerde                  = -1001,    //(GMT-01:00) Cape Verde Is. 
    kUTC                        =     0,    //(UTC) Universal Coordinated Time 
    kGMT                        =     1,    //(GMT) Greenwich Mean Time: Dublin, Edinburgh, Lisbon, London 
    kMonrovia                   =     2,    //(GMT) Casablanca, Monrovia 
    kBerlin                     =  1000,    //(GMT+01:00) Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna 
    kParis                      =  1001,    //(GMT+01:00) Brussels, Copenhagen, Madrid, Paris 
    kPrague                     =  1002,    //(GMT+01:00) Belgrade, Bratislava, Budapest, Ljubljana, Prague 
    kSarajevo                   =  1003,    //(GMT+01:00) Sarajevo, Skopje, Warsaw, Zagreb 
    kWestCentralAfrica          =  1004,    //(GMT+01:00) West Central Africa 
    kAthens                     =  2000,    //(GMT+02:00) Athens, Beirut, Istanbul, Minsk 
    kEasternEurope              =  2001,    //(GMT+02:00) Bucharest 
    kCairo                      =  2002,    //(GMT+02:00) Cairo 
    kHarare                     =  2003,    //(GMT+02:00) Harare, Pretoria 
    kHelsinki                   =  2004,    //(GMT+02:00) Helsinki, Kyiv, Riga, Sofia, Tallinn, Vilnius 
    kJerusalem                  =  2005,    //(GMT+02:00) Jerusalem 
    kMoscow                     =  3000,    //(GMT+03:00) Moscow, St. Petersburg, Volgograd 
    kRiyadh                     =  3001,    //(GMT+03:00) Kuwait, Riyadh 
    kBaghdad                    =  3002,    //(GMT+03:00) Baghdad 
    kEastAfrica                 =  3003,    //(GMT+03:00) Nairobi 
    kTehran                     =  3300,    //(GMT+03:30) Tehran 
    kAbuDhabi                   =  4000,    //(GMT+04:00) Abu Dhabi, Muscat 
    kCaucasus                   =  4001,    //(GMT+04:00) Baku, Tbilisi, Yerevan 
    kKabul                      =  4300,    //(GMT+04:30) Kabul 
    kEkaterinburg               =  5000,    //(GMT+05:00) Ekaterinburg 
    kIslamabad                  =  5001,    //(GMT+05:00) Islamabad, Karachi, Tashkent 
    kKolkata                    =  5300,    //(GMT+05:30) Chennai, Kolkata, Mumbai, New Delhi 
    kKathmandu                  =  5450,    //(GMT+05:45) Kathmandu 
    kAlmaty                     =  6000,    //(GMT+06:00) Almaty, Novosibirsk 
    kDhaka                      =  6001,    //(GMT+06:00) Astana, Dhaka 
    kSriLanka                   =  6002,    //(GMT+06:00) Sri Jayawardenepura 
    kRangoon                    =  6300,    //(GMT+06:30) Rangoon 
    kBangkok                    =  7000,    //(GMT+07:00) Bangkok, Hanoi, Jakarta 
    kKrasnoyarsk                =  7001,    //(GMT+07:00) Krasnoyarsk 
    kBeijing                    =  8000,    //(GMT+08:00) Beijing, Chongqing, Hong Kong, Urumqi 
    kSingapore                  =  8001,    //(GMT+08:00) Kuala Lumpur, Singapore 
    kTaipei                     =  8002,    //(GMT+08:00) Taipei 
    kIrkutsk                    =  8003,    //(GMT+08:00) Irkutsk, Ulaan Bataar 
    kPerth                      =  8004,    //(GMT+08:00) Perth 
    kTokyo                      =  9000,    //(GMT+09:00) Osaka, Sapporo, Tokyo 
    kSeoul                      =  9001,    //(GMT+09:00) Seoul 
    kYakutsk                    =  9002,    //(GMT+09:00) Yakutsk 
    kAdelaide                   =  9300,    //(GMT+09:30) Adelaide 
    kDarwin                     =  9301,    //(GMT+09:30) Darwin 
    kSydney                     = 10000,    //(GMT+10:00) Canberra, Melbourne, Sydney 
    kGuam                       = 10001,    //(GMT+10:00) Guam, Port Moresby 
    kBrisbane                   = 10002,    //(GMT+10:00) Brisbane 
    kHobart                     = 10003,    //(GMT+10:00) Hobart 
    kVladivostock               = 10004,    //(GMT+10:00) Vladivostok 
    kMagadan                    = 11000,    //(GMT+11:00) Magadan, Solomon Is., New Caledonia 
    kWellington                 = 12000,    //(GMT+12:00) Auckland, Wellington 
    kFiji                       = 12001,    //(GMT+12:00) Fiji, Kamchatka, Marshall Is. 
    kTonga                      = 13000     //(GMT+13:00) Nuku'alofa
  };
  enum ShadowFlags {
 kShadowsCastAndReceive  = 0x00, 
                         kShadowsDoesNotReceive  = 0x01, 
                         kShadowsDoesNotCast     = 0x02, 
                         kShadowsIgnore          = kShadowsDoesNotCast | kShadowsDoesNotReceive
  };
  /** Description: 
    Specifies settings that affect the shape of the  
    lofted solid or surface. 
  */
  enum LoftParamType {
 kLoftNoParam           = 0x00, 
                         kLoftNoTwist           = 0x01, 
                         kLoftAlignDirection    = 0x02, 
                         kLoftSimplify          = 0x04, 
                         kLoftClose             = 0x08, 
                         kLoftDefault           = kLoftNoTwist | kLoftAlignDirection | kLoftSimplify
  };
  /** Description: 
    Specifies the normals of the lofted object where it 
    passes through cross section curves. 
  */
  enum LoftNormalsType {
 kLoftRuled            = 0, 
                          kLoftSmooth           = 1, 
                          kLoftFirstNormal      = 2, 
                          kLoftLastNormal       = 3, 
                          kLoftEndsNormal       = 4, 
                          kLoftAllNormal        = 5, 
                          kLoftUseDraftAngles   = 6
  };
    /** Description: 
      Specifies how the entity interacts with collision detection. 
    */
  enum CollisionType {
 kCollisionTypeNone  = 0, 
                             kCollisionTypeSolid = 1
  };
}
/** Description: 
    This class represents a complete drawing file. 
 
    Library: 
    Db 
 
    {group:OdDb_Classes} 
*/
class TOOLKIT_EXPORT OdDbDatabase : public OdDbObject
{
protected:
  OdDbDatabase();
public:
  void getClassID(void** pClsid) const;
#  ifdef ZW_NEW_INTERFACES
  void RemoveObjectIdFromHandleTree(OdDbObjectId ObjId);
  void AddObjectIdToHandleTree(OdDbObjectId ObjId);
#  endif
  ODRX_DECLARE_MEMBERS(OdDbDatabase);
  void addRef();
  void release();
  /** Description: 
    Returns the OdDbHostAppServices object associated with this *database* object. 
  */
  OdDbHostAppServices* appServices() const;
  /** Description: 
    Adds the default set of objects and settings to this *database* object. 
 
    Remarks: 
    This includes the ModelSpace and PaperSpace blocks, default table entries, system variable settings, etc. 
 
    Remarks: 
    measurement must be one the following: 
 
    @table 
    Name              Value 
    OdDb::kEnglish    0 
    OdDb::kMetric     1 
 
    Arguments: 
    measurement (I) Units of *measurement*. 
  */
  void initialize(OdDb::MeasurementValue measurement = OdDb::kEnglish);
  virtual ~OdDbDatabase();
  /** Description: 
    Adds an object to this *database* object, and returns its Object ID. 
 
    Arguments: 
    pObject (I) Pointer to the object. 
    ownerId (I) Object ID of the owner of pObject. 
    handle (I) Handle for pObject 
 
    Remarks: 
    A unique *handle* will be generated if *handle* is not supplied or is 0. 
 
  */
  OdDbObjectId addOdDbObject(OdDbObject* pObject, OdDbObjectId ownerId = OdDbObjectId::kNull, OdDbHandle handle = 0);
  /** Description: 
    Adds the specified *name* to the APPID table of this *database* object. 
 
    Arguments: 
    regAppName (I) Application *name*. 
 
    Remarks: 
    True if and only if the specified *name* had not been, and is now, in the APPID table. 
  */
  bool newRegApp(const OdString& regAppName);
  /** Description: 
    Returns the Object ID of the BlockTable of this *database* object. 
  */
  OdDbObjectId getBlockTableId() const;
  /** Description: 
    Returns the Object ID of the LayerTable of this *database* object. 
  */
  OdDbObjectId getLayerTableId() const;
  /** Description: 
    Returns the Object ID of the TextStyleTable of this *database* object. 
  */
  OdDbObjectId getTextStyleTableId() const;
  /** Description: 
    Returns the Object ID of the LinetypeTable of this *database* object. 
  */
  OdDbObjectId getLinetypeTableId() const;
  /** Description: 
    Returns the Object ID of the ViewTable of this *database* object. 
  */
  OdDbObjectId getViewTableId() const;
  /** Description: 
    Returns the Object ID of the UCSTable of this *database* object. 
  */
  OdDbObjectId getUCSTableId() const;
  /** Description: 
    Returns the Object ID of the ViewportTable of this *database* object. 
  */
  OdDbObjectId getViewportTableId() const;
  /** Description: 
    Returns the Object ID of the RegAppTable of this *database* object. 
  */
  OdDbObjectId getRegAppTableId() const;
  /** Description: 
    Returns the Object ID of the DimStyleTable of this *database* object. 
  */
  OdDbObjectId getDimStyleTableId() const;
  /** Description: 
    Returns the Object ID of the MLineStyle dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getMLStyleDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the Group dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getGroupDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the Layout dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getLayoutDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the PlotStyleName dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getPlotStyleNameDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the NamedObjects dictionary of this *database* object. 
  */
  OdDbObjectId getNamedObjectsDictionaryId() const;
  /** Description: 
    Returns the Object ID of the PlotSettings dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getPlotSettingsDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the Color dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getColorDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the Material dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getMaterialDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the VisualStyle dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getVisualStyleDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the TableStyle dictionary of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
  */
  OdDbObjectId getTableStyleDictionaryId(bool createIfNotFound = true) const;
  /** Description: 
    Returns the Object ID of the current TableStyle of this *database* object. 
  */
  OdDbObjectId tablestyle() const;
  /** Description: 
    Sets the Object ID of the current TableStyle of this *database* object. 
    Arguments: 
    objectId (I) Object ID. 
  */
  void setTablestyle(OdDbObjectId objectId);
  /** Description: 
    Returns the Object ID of the "ACAD" RegApp object of this *database* object. 
  */
  OdDbObjectId getRegAppAcadId() const;
  /** Description: 
    Returns the Object ID of the "Continuous" Linetype object of this *database* object. 
  */
  OdDbObjectId getLinetypeContinuousId() const;
  /** Description: 
    Returns the Object ID of the "ByLayer" Linetype object of this *database* object. 
  */
  OdDbObjectId getLinetypeByLayerId() const;
  /** Description: 
    Returns the Object ID of the "ByBlock" Linetype object of this *database* object. 
  */
  OdDbObjectId getLinetypeByBlockId() const;
  /** Description: 
    Returns the Object ID of the ModelSpace Block object of this *database* object. 
  */
  OdDbObjectId getModelSpaceId() const;
  /** Description: 
    Returns the Object ID of the PaperSpace Block object of this *database* object. 
  */
  OdDbObjectId getPaperSpaceId() const;
  /** Description: 
    Returns the Object ID of the "Standard" text style object of this *database* object. 
  */
  OdDbObjectId getTextStyleStandardId() const;
  /** Description: 
    Returns the Object ID of the "Standard" dimension style object of this *database* object. 
  */
  OdDbObjectId getDimStyleStandardId() const;
  /** Description: 
    Returns the Object ID of the "0" layer object of this *database* object. 
  */
  OdDbObjectId getLayerZeroId() const;
  /** Description: 
    Returns the Object ID of the "DEFPOINTS" layer object of this *database* object. 
    Arguments: 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
 */
  OdDbObjectId getLayerDefpointsId(bool createIfNotFound = false) const;
  /** Description: 
    Returns the object ID of the section manager.  
 
    Remarks: 
    The ID may be null if the database  
    has never contained any section planes. 
  */
  OdDbObjectId getSectionManager() const;
  /** Description: 
    Returns the Class DXF Name for the specified class. 
 
    Arguments: 
    pClass (I) Pointer to the class object. 
 
    See Also: 
    OdRxClass 
  */ 
  /** { Secret } */
  const OdString classDxfName(const OdRxClass* pClass);
  /** Description: 
    Returns the Object ID corresponding to the specified *handle* object in this *database*. 
 
    Arguments: 
    objHandle (I) Database *handle*. 
    createIfNotFound (I) Controls the creation of the object if it does not exist. 
    xRefId (I) Not used. 
 
    Remarks: 
    If objHandle is 0, this function will create a new unique *handle* and return a 
    newly created Object ID corresponding to this *handle*. 
 
    Note: 
    createIfNotFound is for DWGdirect internal use only, and should always be false for DWGdirect applications. 
 
    See Also: 
    OdDbObjectId 
  */
  OdDbObjectId getOdDbObjectId(const OdDbHandle& objHandle, bool createIfNotFound = false, OdUInt32 xRefId = 0);
  /** Description: 
    Writes the contents of this *database* object to the specified StreamBuf object. 
 
    Arguments: 
    pStreamBuf (I) Pointer to the StreamBuf object to which the data are to be written. 
    fileType (I) File type. 
    fileVersion (I) File *version*. 
    saveThumbnailImage (I) Controls the saving of a thumbnail *image* to the file. 
    dxfPrecision (I) DXF file decimal digits precision. [0 .. 16]. 
 
    Remarks: 
    fileType must be one of the following: 
 
    @table 
    Name          Value   Description 
    OdDb::kDwg    0       DWG file. 
    OdDb::kDxf    1       DXF file. 
    OdDb::kDxb    2       Binary DXF file. 
 
    fileVersion must be one of the following: 
 
    @table 
    DWG    Name          Value  Description 
    .      OdDb::vAC09   11     Release 9 
    .      OdDb::vAC10   13     Release 10 
    o      OdDb::vAC12   16     Release 11-12 
    o      OdDb::vAC13   19     Release 13 
    o      OdDb::vAC14   21     Release 14 
    o      OdDb::vAC15   23     2000-2002 
    o      OdDb::vAC18   25     2004-2006 
    o      OdDb::vAC21   25     2007 
 
    Throws: 
    OdError if the write is unsuccessful. 
  */
  void writeFile(OdStreamBuf* pStreamBuf, OdDb::SaveType fileType, OdDb::DwgVersion fileVersion, bool saveThumbnailImage = false, int dxfPrecision = 16);
  /** 
    Arguments: 
    filename (I) Name of the file to which the data are to be written. 
  */
  void writeFile(const OdString& filename, OdDb::SaveType fileType, OdDb::DwgVersion fileVersion, bool saveThumbnailImage = false, int dxfPrecision = 16)
  {
    closeInput(); 
    OdStreamBufPtr pFile = odSystemServices()->createFile(filename, Oda::kFileWrite, Oda::kShareDenyReadWrite, Oda::kCreateAlways); 
    writeFile(pFile, fileType, fileVersion, saveThumbnailImage, dxfPrecision);
  }
  /** Description: 
    Reads the contents of the specified StreamBuf object or file into this *database* object. 
 
    Arguments: 
    pStreamBuf (I) Pointer to the StreamBuf object from which the data are to be read. 
    partialLoad (I) Controls the partial loading of DWG files. 
    pAuditInfo (I) Pointer to an OdDbAuditInfo object. 
    password (I) Password for file. 
    allowCPConversion (I) If and only if true, allows code page conversion. 
 
    Remarks: 
    The specified OdDbAuditInfo object controls the *audit*, and receives the *audit* status. 
 
    If pAuditInfo is non-zero, a recover will be performed instead of a load. 
 
    Throws: 
    OdError if the write is unsuccessful. 
  */
  void readFile(OdStreamBuf* pStreamBuf, bool partialLoad = false, OdDbAuditInfo* pAuditInfo = 0, const OdPassword& password = OdPassword(), bool allowCPConversion = false);
  /** 
    Arguments: 
    filename (I) Name of the file from which the data are to be read. 
    shareMode (I) Share mode to use when opening the specified file. 
 
    Remarks: 
    shareMode must be one of the following: 
 
    @table 
    Name                         Value       Description 
    Oda::kShareDenyReadWrite     0x10        deny read/write mode 
    Oda::kShareDenyWrite         0x20        deny write mode 
    Oda::kShareDenyRead          0x30        deny read mode 
    Oda::kShareDenyNo            0x40        deny none mode 
 
  */
  void readFile(const OdString& filename, bool partialLoad = false, Oda::FileShareMode shareMode = Oda::kShareDenyWrite, const OdPassword& password = OdPassword(), bool allowCPConversion = false)
  {
    readFile(odSystemServices()->createFile(filename, Oda::kFileRead, shareMode), partialLoad, 0, password, allowCPConversion);
  }
  /** Description: 
    Forces all data to be loaded from the input file associated with this *database* object, and closes the file. 
 
    Remarks: 
    Client applications will normally not need to call this function. 
  */ 
  /** { Secret } */
  void closeInput();
  /** Description: 
    Returns the approximate number of objects in this *database* object. 
 
    Remarks: 
    This function returns value greater than or equal to the number of objects 
    in this *database* object. 
 
    This number is used to construct an OdDbObjectIdArray that can hold all the objects in the *database*, avoiding 
    memory fragmentation and increasing performance. 
  */
  OdInt32 approxNumObjects() const;
  /** Description: 
    Returns the *version* of this *database* object. 
 
    Remarks: 
    The maintenance *release* *version* is returned if and only if pMaintReleaseVer != 0. 
 
    Arguments: 
    pMaintReleaseVer (I) Pointer to the MaintReleaseVer object to receive the maintenance *release* *version*. 
  */
  OdDb::DwgVersion version(OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;
  /** Description: 
    Returns the number of times this *database* object has been saved since it was opened. 
 
    Remarks: 
    This number may be zero. 
  */
  OdInt32 numberOfSaves() const;
  /** Description: 
    Returns the *version* to which this *database* object was last saved. 
 
    Arguments: 
    pMaintReleaseVer (I) Pointer to the MaintReleaseVer object to receive the maintenance *release* *version*. 
 
    Remarks: 
    The maintenance *release* *version* is returned if and only if pMaintReleaseVer != 0. 
  */
  OdDb::DwgVersion lastSavedAsVersion(OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;
  /** Description: 
    Returns the FileType of the file from which this *database* object was read. 
 
    Remarks: 
    originalFileType() returns one of the following: 
 
    @table 
    Name         Value   Description 
    OdDb::kDwg    0       DWG file. 
    OdDb::kDxf    0       DXF file. 
  */
  OdDb::SaveType originalFileType() const;
  /** Description: 
    Returns the *version* of the file from which this *database* object was read. 
 
    Arguments: 
    pMaintReleaseVer (I) Pointer to the MaintReleaseVer object to receive the maintenance *release* *version*. 
 
    Remarks: 
    The maintenance *release* *version* is returned if and only if pMaintReleaseVer != 0. 
  */
  OdDb::DwgVersion originalFileVersion(OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;
  /** Description: 
    Returns the *version* of the application that created the file from which this *database* object was read. 
 
    Arguments: 
    pMaintReleaseVer (I) Pointer to the MaintReleaseVer object to receive the maintenance *release* *version*. 
 
    Remarks: 
    The maintenance *release* *version* is returned if and only if pMaintReleaseVer != 0. 
  */
  OdDb::DwgVersion originalFileSavedByVersion(OdDb::MaintReleaseVer* pMaintReleaseVer = 0) const;
   /** 
    Description: 
    Adds the specified *reactor* to this object's *reactor* list. 
 
    Arguments: 
    pReactor (I) Pointer to the *reactor* object. 
  */
  void addReactor(OdDbDatabaseReactor* pReactor) const;
  /** Description: 
    Removes the specified *reactor* from this object's *reactor* list. 
 
    Arguments: 
    pReactor (I) Pointer to the *reactor* object. 
  */
  void removeReactor(OdDbDatabaseReactor* pReactor) const;
  /** Description: 
    Returns the R14 DIMFIT system variable of this *database* object. 
 
    Remarks: 
    The DIMATFIT and DIMTMOVE values will be converted to DIMFIT. The complete mapping is as follows: 
 
    @table 
    DIMTMOVE    DIMAFIT   DIMFIT 
    0           0         0 
    0           1         1 
    0           2         2 
    0           3         3 
    1           0         4 
    1           1         4 
    1           2         4 
    1           3         4 
    2           0         5 
    2           1         5 
    2           2         5 
    2           3         5 
  */
  int dimfit() const;
  /** Description: 
    Returns the R14 DIMUNIT system variable of this *database* object. 
 
    Remarks: 
    The DIMLUNIT and DIMFRAC values will be converted to DIMUNIT. The complete mapping is as follows: 
 
    @table 
    DIMFRAC   DIMLUNIT  DIMUNIT 
    0         1         1 
    0         2         2 
    0         3         3 
    0         4         4 
    0         5         5 
    0         6         8 
    1         1         1 
    1         2         2 
    1         3         3 
    1         4         4 
    1         5         5 
    1         6         8 
    2         1         1 
    2         2         2 
    2         3         3 
    2         4         6 
    2         5         7 
    2         6         8 
 
    All other input combinations return 2. 
  */
  int dimunit() const;
  /** Description: 
    Sets the R14 DIMFIT system variable of this *database* object. 
 
    Arguments: 
    val (I) New value for DIMFIT. [0..5] 
 
    Remarks: 
    The DIMFIT value will be converted to DIMATFIT and DIMTMOVE values. The complete mapping is as follows: 
  */
  void setDimfit(int val);
  /** Description: 
    Sets the R14 DIMUNIT system variable of this *database* object. 
 
    Arguments: 
    val (I) New value for DIMUNIT. [1..7] 
 
    Remarks: 
    The DIMUNIT value will be converted to DIMLUNIT and DIMFRAC values. 
  */
  void setDimunit(int val);
  /** Description: 
    Deep clones a set of objects, and appends the clones to the specified in owner object. 
 
    Arguments: 
    objectIds (I) Array of Object IDs of the objects to be cloned. 
    ownerId (I) Object ID of owner object. 
    idMap (I/O) ID map. 
    deferXlation (I) Defer translation. 
 
    Remarks: 
    idMap associates the Object IDs of the original objects with the Object IDs of the newly created clones. 
 
    When cloning objects with different owner IDs, a separate call to this function is required for each 
    ownerId. In this case, all but the final call to this function should be made with deferXlation == true. 
    This defers translation until all objects have been cloned. 
 
    A deep *clone* is a *clone* of the specified objects and everything they own. 
 
    See also: 
    wblockCloneObjects() 
 
  */
  void deepCloneObjects(const OdDbObjectIdArray& objectIds, OdDbObjectId ownerId, OdDbIdMapping& idMap, bool deferXlation = false);
  /** Description: 
    Shallow clones a set of objects, and appends the clones to the specified in owner object. 
 
    Arguments: 
    objectIds (I) Array of Object IDs of the objects to be cloned. 
    ownerId (I) Object ID of the owner object. 
    idMap (I/O) ID map. 
    deferXlation (I) Defer translation. 
 
    Remarks: 
    idMap associates the Object IDs of the original objects with the Object IDs of the newly created clones. 
 
    When cloning objects with different owner IDs, a separate call to this function is required for each 
    ownerId. In this case, all but the final call to this function should be made with deferXlation == true. 
    This defers translation until all objects have been cloned. 
 
    A shallow *clone* is a *clone* of the specified objects, but not what they own. 
 
    @table 
    Name                        Value   Description 
    OdDb::kDrcNotApplicable     0       Not applicable to the object. 
    OdDb::kDrcIgnore            1       If a duplicate record exists, use the existing record in the *database*, and ignore the clone. 
    OdDb::kDrcReplace           2       If a duplicate record exists, replace it with the cloned record. 
    OdDb::kDrcXrefMangleName    3       Incoming record names are mangled with <Xref>$0$<name> 
    OdDb::kDrcMangleName        4       Incoming record names are mangled with $0$<name> 
    OdDb::kDrcUnmangleName      5       Unmangle the names mangled by OdDb::kDrcMangleName, then default to OdDb::kDrcIgnore. Typically used by RefEdit when checking records into the original *database*. 
 
    duplicateRecordCloning must be one of the following: 
 
    See also: 
    deepCloneObjects() 
 
  */
  void wblockCloneObjects(const OdDbObjectIdArray& objectIds, OdDbObjectId ownerId, OdDbIdMapping& idMap, OdDb::DuplicateRecordCloning duplicateRecordCloning, bool deferXlation = false);
  /** Description: 
    Terminates a call to deepCloneObjects() or wblockCloneObjects(). 
 
    Arguments: 
    idMap (I/O) ID map of the function call to be terminated. 
 
    Remarks: 
    idMap associates the Object IDs of the original objects with the Object IDs of the newly created clones. 
 
    This call is necessary only when a call to deepCloneObjects() or wblockCloneObjects() is made with deferXlation == true, 
    and no call will be made with deferXlation == false. 
  */
  void abortDeepClone(OdDbIdMapping& idMap);
  /** Description: 
    Performs an *audit* operation on the header of this *database* object. 
 
    Arguments: 
    pAuditInfo (I) Pointer to an OdDbAuditInfo object. 
 
    Remarks: 
    The specified OdDbAuditInfo object controls the *audit*, and receives the *audit* status. 
  */
  void audit(OdDbAuditInfo* pAuditInfo);
  /** Description: 
    Starts a new transaction of this *database* object. 
  */
  virtual void startTransaction();
  /** Description: 
    Ends the current transaction associated with this *database* object. 
 
    Remarks: 
    This function commits all changes to objects since the start of the current transaction. 
  */
  virtual void endTransaction();
  /** Description: 
    Aborts the current transaction associated with this *database* object. 
 
    Remarks: 
    This function initiates an immediate rollback of all changes to objects 
    since the start of the current transaction. This rollback occurs for 
    all transaction-resident objects. 
  */
  virtual void abortTransaction();
  /** Description: 
    Returns the number of active transactions associated with this *database* object. 
  */
  virtual int numActiveTransactions();
  /** Description: 
    Adds a transaction *reactor* to this *database* object. 
 
    Arguments: 
    reactor (I) Transaction *reactor*. 
  */
  virtual void addTransactionReactor(OdDbTransactionReactor* reactor);
  /** Description: 
    Removes the specified transaction *reactor* from this *database* object. 
 
    Arguments: 
    reactor (I) Transaction *reactor*. 
  */
  virtual void removeTransactionReactor(OdDbTransactionReactor* reactor);
  /** Description: 
    Returns the thumbnail bitmap associated with this *database* object. 
 
    Remarks: 
    The thumbnail is in Windows BITMAPINFO* format. 
 
    Arguments: 
    dataLength (O) Receives the data length of the thumbnail. 
  */
  const void* thumbnailBitmap(OdUInt32& dataLength) const;
  /** Description: 
    Sets the thumbnail bitmap associated with this *database* object. 
 
    Remarks: 
    The thumbnail is in Windows BITMAPINFO* format. 
 
    Arguments: 
    dataLength (I) Data length of the thumbnail. 
    pBMPData (I) Pointer to the bitmap data. 
  */
  void setThumbnailBitmap(const void* pBMPData, OdUInt32 dataLength);
  /** Description: 
    Returns the state of the RetainOriginalThumbnailBitmap flag. 
  */
  bool retainOriginalThumbnailBitmap() const;
  /** Description: 
    Controls the state of the RetainOriginalThumbnailBitmap flag. 
 
    Arguments: 
    retain (I) Retain if and only if true. 
  */
  void setRetainOriginalThumbnailBitmap(bool retain);
  void dwgOutFields(OdDbDwgFiler* pFiler) const;
  OdResult dwgInFields(OdDbDwgFiler* pFiler);
/** { Secret } */
#  define VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)	\ 
  /** Description: Returns the ##NAME system variable of this *database* object. \ 
    Remarks: ##remarks \ 
    Notes: ##notes \ 
    See Also: ##see_also \ 
  */ \ 
  type get##name() const; 
#  include "SysVarDefs.h"
#  undef VAR_DEF
#  undef RO_VAR_DEF
/** { Secret } */
#  define RO_VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)
/** { Secret } */
#  define VAR_DEF(type, name, def_value, metric_def_value, reserve1, reserve2)	\ 
  /** Description: Sets the ##NAME system variable for this *database* object. \ 
    Arguments: val (I) New value for ##NAME.  ##RANGE  \ 
    Remarks: ##remarks \ 
    Notes: ##notes \ 
    See Also: ##see_also \ 
  */ \ 
  void set##name(type val); 
#  include "SysVarDefs.h"
#  undef RO_VAR_DEF
#  undef VAR_DEF
/** { Secret } */
#  define VAR_DEF(type, name, dxf, def_value, metric_def_value, reserve1, reserve2)	\ 
  /** Description: Returns the DIM##NAME system variable of this *database* object. \ 
    Remarks: ##remarks \ 
    Notes: ##notes \ 
    See Also: ##see_also \ 
  */ \ 
  type dim##name() const;\ 
  \ 
  /** Description: Sets the DIM##NAME system variable for this *database* object. \ 
    Arguments: val (I) New value for DIM##NAME.  ##RANGE  \ 
    Remarks: ##remarks \ 
    Notes: ##notes \ 
    See Also: ##see_also \ 
  */ \ 
  void setDim##name(type val); 
#  include "DimVarDefs.h"
#  undef VAR_DEF
  /** Description: 
    Returns the TDCREATE system variable of this *database* object. 
    Remarks: 
    TDUCREATE represents the time and date, in Local Time, that the *database* was created.  
  */
  OdDbDate getTDCREATE() const;
  /** Description: 
    Returns the TDUPDATE system variable of this *database* object. 
    Remarks: 
    TDUUPDATE represents the time and date, in Local Time, that the *database* was last saved. 
  */
  OdDbDate getTDUPDATE() const;
  /** Description: 
    Returns the specified system variable of this *database* object. 
 
    Arguments: 
    name (I) Name of the system variable. 
 
    Remarks: 
    Returns a SmartPointer to an OdResBuf object that contains the value. 
 
    System variable names are case-insensitive strings. 
 
    See also: 
    System Variables 
  */
  OdResBufPtr getSysVar(const OdString& name) const;
  /** Description: 
    Sets the specified system variable of this *database* object. 
 
    Arguments: 
    name (I) Name of the system variable. 
    pValue (I) Pointer to an OdResBuf object that contains the new value. 
 
    Remarks: 
    System variable names are case-insensitive strings. 
 
    See also: 
    System Variables 
  */
  void setSysVar(const OdString& name, const OdResBuf* pValue);
  /** Description: 
    Returns the next available *handle* number of this *database* object. 
    Remarks: 
    Use OdDbHandle::getIntoAsciiBuffer() to return the hex string *version* of the *handle*. 
  */
  OdDbHandle handseed() const;
  /** Description: 
    Copies the dimension variables of this *database* object to the 
    specified DimStyleTableRecord. 
 
    Arguments: 
    pDestination (I) Pointer to the destination record. 
  */
  void getDimstyleData(OdDbDimStyleTableRecord* pDestination) const;
  /** Description: 
    Copies the dimension style data from the specified DimStyleTableRecord 
    to the dimension variables of this *database* object. 
    Arguments: 
    pSource (I) Pointer to the source record. 
  */
  void setDimstyleData(const OdDbDimStyleTableRecord* pSource);
  /** Description: 
    Arguments: 
    objectId (I) Object ID of the source record. 
  */
  void setDimstyleData(OdDbObjectId objectId);
  /** Description: 
    Loads a linetype into this *database* object. 
 
    Arguments: 
    ltName (I) Name of the linetype to load. 
    filename (I) Name of the linetype file from which to load. 
 
    Remarks: 
    Wildcards are permitted in ltName; if "*" is specified, all LineTypes from filename will be loaded. 
 
    dlt must be one of the following: 
 
    @table 
    Name                      Value   Description 
    OdDb::kDltNotApplicable     0       Not Applicable. 
    OdDb::kDltIgnore            1       Ignore duplicate LineTypes. 
    OdDb::kDltReplace           2       Replace duplicate LineTypes. 
 
    Throws: 
    An appropriate error if not successful. 
  */
  void loadLineTypeFile(const OdString& ltName, const OdString& filename, OdDb::DuplicateLinetypeLoading dlt = OdDb::kDltNotApplicable);
  /** Description: 
      Returns the *name* of the file associated with this *database* object. 
  */
  OdString getFilename() const;
  /** Description: 
    Removes the Object IDs from the specified array that are hard referenced 
    in this *database* object. 
 
    Remarks: 
    Any remaining Object IDs can be safely *erased*. 
 
    Note: 
    This function does not modify this *database* object. 
 
    Arguments: 
    objectIds (I/O) Array of Object IDs. 
  */
  void purge(OdDbObjectIdArray& objectIds) const;
  /** Description: 
      Returns a count of hard references to each of the specified Object IDs. 
 
      Arguments: 
      objectIds (I) Array of Object IDs. 
      counts (O) Receives an array of hard reference counts. 
 
      Note: 
      counts must be the same size as objectIds. 
 
      Each element of counts will be incremented for each hard reference of the corresponding *objectId* 
      The caller must *initialize* the elements of count to zero or an appropriate value 
      before calling this function. 
  */
  void countHardReferences(const OdDbObjectIdArray& objectIds, OdUInt32* counts) const;
  /** Description: 
      Returns the Object ID of the active layout of this *database* object. 
  */
  OdDbObjectId currentLayoutId() const;
  /** Description: 
    Sets the current layout of this *database* object. 
 
    Arguments: 
    layoutName (I) Name of the layout. 
  */
  virtual void setCurrentLayout(const OdString& layoutName);
  /** 
    Arguments: 
    layoutId (I) Object ID of layout. 
  */
  virtual void setCurrentLayout(const OdDbObjectId& layoutId);
  /** Description: 
      Returns the *name* of the active layout of this *database* object. 
 
      Arguments: 
      allowModel (I) If and only if true, allows the ModelSpace layout *name* to be returned. 
       
      Remarks: 
      If allowModel == false, an empty string will be returned if the active layout is ModelSpace. 
  */
  virtual OdString findActiveLayout(bool allowModel) const;
  /** Description: 
    Returns the Object ID of the BlockTableRecord associated with the active 
    layout of this *database* object. 
  */
  virtual OdDbObjectId getActiveLayoutBTRId() const;
  /** Description: 
    Returns the Object ID of the specified layout in this *database* object. 
     
    Arguments: 
    layoutName (I) Layout *name*. 
       
    Remarks: 
    Returns a null Object ID if the specified layout is not found. 
  */
  virtual OdDbObjectId findLayoutNamed(const OdString& layoutName) const;
  /** Description: 
    Deletes the specified layout from this *database* object. 
     
    Arguments: 
    layoutName (I) Layout *name*. 
  */
  virtual void deleteLayout(const OdString& layoutName);
  /** Description: 
    Creates a new layout with the specified *name* in this *database* object. 
     
    Remarks: 
    The newly created layout is added to this *database* object along with its 
    newly created, associated OdDbBlockTableRecord.   
 
    Arguments: 
    layoutName (I) Layout *name*. 
    pBlockTableRecId (I) Pointer to the BlockTableRecID to receive the Object ID of the new BlockTableRecord object. 
  */
  virtual OdDbObjectId createLayout(const OdString& layoutName, OdDbObjectId* pBlockTableRecId = 0);
  /** Description: 
    Returns the number of layouts in this *database* object. 
  */
  virtual int countLayouts() const;
  /** Description: 
    Renames the specified layout in this *database* object. 
    Arguments: 
    oldName (I) Old *name*. 
    newName (I) New *name*. 
  */
  virtual void renameLayout(const OdString& oldName, const OdString& newName);
  /** Description: 
      Starts *undo* recording of this *database* object. 
  */
  void startUndoRecord();
  /** Description: 
      Returns true if *undo* information exists of this *database* object.  
  */
  bool hasUndo() const;
  /** Description: 
    Performs an *undo* operation on this *database* object.   
     
    Remarks: 
    All operations performed since the  
    last call to startUndoRecording will be undone. 
 
    At least 1 undo step is always supported by DWGdirect for internal needs. 
  */
  void undo();
  void blockUndoRecording(bool bBegin);
  bool isUndoBlockStarted();
  void setUndoMark();
  bool hasUndoMark() const;
  void undoBack();
  int getUNDOMARKS() const;
  void clearUndo();
  /** Description: 
    Returns true if *redo* information exists of this *database* object. 
  */
  bool hasRedo() const;
  /** Description: 
    Performs a *redo* operation on this *database* object. 
     
    Remarks: 
    Restores operations undone by the last *undo*.  
  */
  void redo();
  /** Description: 
    Performs an *audit* operation on the this entire *database* object. 
 
    Arguments: 
    pAuditInfo (I) Pointer to an AuditInfo object. 
   
    Remarks: 
    The specified AuditInfo object controls the *audit*, and receives the *audit* status. 
  */
  void auditDatabase(OdDbAuditInfo* pAuditInfo);
  void applyPartialUndo(OdDbDwgFiler* pUndoFiler, OdRxClass* pClassObj);
  OdDbDwgFiler* undoFiler();
  /** Description: 
    Mimics the INSERT command of this *database* object. 
         
    Arguments: 
    sourceBlockName (I) Name of the OdDbBlockTableRecord in pSource. 
    destinationBlockName (I) Name for the new OdDbBlockTableRecord. 
    pSource (I) Source *database*. 
    preserveSourceDatabase (I) True to *clone* entities, false to move entities. 
    xfm (I) Transformation matrix. 
 
    Remarks: 
    If destinationBlockName is specified, a new OdDbBlockTableRecord is created.  
     
    If both destinationBlockName and sourceBlockName are specified, all entities in the BlockTableRecord specified by sourceBlockName in pSource  
    are *copied* (or moved) into the new OdDbBlockTableRecord. 
        
    If destinationBlockName is specified, and sourceBlockName is not specified, all ModelSpace entities in pSource, are *copied* (or moved) into the new OdDbBlockTableRecord. 
 
    If xfm is specified, all ModelSpace entities in pSource are *copied* (or moved) into the  
    ModelSpace of this *database* object and transformed by xfm.  
  */
  OdDbObjectId insert(const OdString& destinationBlockName, OdDbDatabase* pSource, bool preserveSourceDatabase = true);
  OdDbObjectId insert(const OdString& sourceBlockName, const OdString& destinationBlockName, OdDbDatabase* pSource, bool preserveSourceDatabase = true);
  void insert(const OdGeMatrix3d& xfm, OdDbDatabase* pSource, bool preserveSourceDatabase = true);
  /** Description: 
     Mimics the WBLOCK command of this *database* object. 
      
     Arguments: 
     outObjIds (I) Array of Object IDs to be wblocked. 
     basePoint (I) WCS base point for the  
     blockId (I) Object ID of the BlockTableRecord to be wblocked. 
      
     Remarks: 
     Creates a new OdDbDatabase object, and returns a SmartPointer to the new *database*. 
      
     If called with no arguments, the entire contents of this *database* object are wblocked. 
  */
  OdDbDatabasePtr wblock(const OdDbObjectIdArray& outObjIds, const OdGePoint3d& basePoint);
  OdDbDatabasePtr wblock(OdDbObjectId blockId);
  OdDbDatabasePtr wblock();
 /**  
    Note: 
    As implemented, this function does nothing but return a null SmartPointer. 
    It will be fully implemented in a future *release*. 
  */
  OdDbObjectPtr wblockClone(OdDbIdMapping& ownerIdMap) const;
  /** Description: 
    Sets the security parameters of this *database* object. 
     
    Arguments:   
    secParams (I) Security params. 
    setDbMod (I) If and only if true, the DBMOD variable will be set if the security settings *modified*. 
     
    Note: 
    As implemented, this function ignores setDbMod, and never modifies the DBMOD variable. 
    It will be fully implemented in a future *release*. 
  */
  void setSecurityParams(const OdSecurityParams& secParams, bool setDbMod = true);
  /** Description: 
    Returns the security parameters of this *database* object. 
    Arguments:   
    secParams (I) Security params. 
    Remarks: 
    Returns true if and only if secParams.nFlags!=0 && secParams.password is not empty. 
  */
  bool securityParams(OdSecurityParams& secParams) const;
  /** Description: 
    Returns the OdFileDependencyManager object of this *database* object. 
  */
  OdFileDependencyManagerPtr fileDependencyManager() const;
  /** Description: 
    Recalculates the *extents* of this *database* object. 
  */
  void updateExt();
  /** Description: 
      Returns true if and only if this *database* object was created by an educational *version* of AutoCAD. 
  */
  bool isEMR() const;
  /** Description: 
    Returns the Object ID of the OdDbBlockTableRecord that references this *database* object as an Xref. 
  */
  OdDbObjectId xrefBlockId() const;
  /** Description: 
    Returns true if and only if this *database* object is partially opened.  
  */
  bool isPartiallyOpened() const;
  /** Description: 
    Sets the current UCS of this *database* object.  
 
    Arguments: 
    origin (I) The WCS *origin* of the UCS. 
    xAxis (I) The WCS X-axis of the UCS. 
    yAxis (I) The WCS Y-axis of the UCS. 
    viewType (I) Orthographic view type. 
    ucsId (I) Object ID of the UCS. 
     
    Remarks: 
    viewType must be one of the following: 
     
    @table 
    Name                  Value   View type 
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS  
    OdDb::kTopView        1       Top view with respect to the UCS  
    OdDb::kBottomView     2       Bottom view with respect to the UCS  
    OdDb::kFrontView      3       Front view with respect to the UCS  
    OdDb::kBackView       4       Back view with respect to the UCS  
    OdDb::kLeftView       5       Left view with respect to the UCS  
    OdDb::kRightView      6       Right view with respect to the UCS  
  */
  void setCurrentUCS(OdDb::OrthographicView viewType);
  void setCurrentUCS(const OdDbObjectId& ucsId);
  void setCurrentUCS(const OdGePoint3d& origin, const OdGeVector3d& xAxis, const OdGeVector3d& yAxis);
  /** Description: 
    Returns the UCS *origin* and orthographic view type for the current UCS. 
 
    Arguments: 
    viewType (I) Orthographic view type. 
 
    Remarks: 
    viewType must be one of the following: 
     
    @table 
    Name            Value   View type 
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS  
    OdDb::kTopView        1       Top view with respect to the UCS  
    OdDb::kBottomView     2       Bottom view with respect to the UCS  
    OdDb::kFrontView      3       Front view with respect to the UCS  
    OdDb::kBackView       4       Back view with respect to the UCS  
    OdDb::kLeftView       5       Left view with respect to the UCS  
    OdDb::kRightView      6       Right view with respect to the UCS  
  */
  OdGePoint3d getUCSBASEORG(OdDb::OrthographicView viewType) const;
  /** Description: 
    Sets the UCS *origin* and orthographic view type for the current UCS. 
 
    Arguments: 
    origin (I) The WCS *origin* of the UCS. 
    viewType (I) Orthographic view type. 
 
    Remarks: 
    viewType must be one of the following: 
     
    @table 
    Name            Value   View type 
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS  
    OdDb::kTopView        1       Top view with respect to the UCS  
    OdDb::kBottomView     2       Bottom view with respect to the UCS  
    OdDb::kFrontView      3       Front view with respect to the UCS  
    OdDb::kBackView       4       Back view with respect to the UCS  
    OdDb::kLeftView       5       Left view with respect to the UCS  
    OdDb::kRightView      6       Right view with respect to the UCS  
  */
  void setUCSBASEORG(OdDb::OrthographicView viewType, const OdGePoint3d& origin);
  /** Description: 
    Returns the UCS *origin* and orthographic view type for the current PaperSpace UCS. 
 
    Arguments: 
    viewType (I) Orthographic view type. 
 
    Remarks: 
    viewType must be one of the following: 
     
    @table 
    Name                  Value   View type 
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS  
    OdDb::kTopView        1       Top view with respect to the UCS  
    OdDb::kBottomView     2       Bottom view with respect to the UCS  
    OdDb::kFrontView      3       Front view with respect to the UCS  
    OdDb::kBackView       4       Back view with respect to the UCS  
    OdDb::kLeftView       5       Left view with respect to the UCS  
    OdDb::kRightView      6       Right view with respect to the UCS  
  */
  OdGePoint3d getPUCSBASEORG(OdDb::OrthographicView viewType) const;
 /** Description: 
    Sets the UCS *origin* and orthographic view type for the current PaperSpace UCS. 
 
    Arguments: 
    origin (I) The WCS *origin* of the UCS. 
    viewType (I) Orthographic view type. 
 
    Remarks: 
    viewType must be one of the following: 
     
    @table 
    Name                  Value   View type 
    OdDb::kNonOrthoView   0       Non-orthographic with respect to the UCS  
    OdDb::kTopView        1       Top view with respect to the UCS  
    OdDb::kBottomView     2       Bottom view with respect to the UCS  
    OdDb::kFrontView      3       Front view with respect to the UCS  
    OdDb::kBackView       4       Back view with respect to the UCS  
    OdDb::kLeftView       5       Left view with respect to the UCS  
    OdDb::kRightView      6       Right view with respect to the UCS  
  */
  void setPUCSBASEORG(OdDb::OrthographicView viewType, const OdGePoint3d& origin);
  /** Description: 
    Returns the DIMSTYLE system variable of this database object. 
    Remarks: 
    DIMSTYLE specifies the default dimension style for new entities. 
    Arguments: 
    val (I) New value for DIMSTYLE. 
  */
  void setDIMSTYLE(const OdDbObjectId& val);
  /*   
  bool plotStyleMode() const; 
 
  static bool isValidLineWeight(int weight); 
 
  static OdDb::LineWeight getNearestLineWeight(int weight); 
 
  void forceWblockDatabaseCopy(); 
  
  void auditXData(OdDbAuditInfo* pInfo); 
 
  OdDbUndoController* undoController() const; 
 
  void restoreOriginalXrefSymbols(); 
 
  void restoreForwardingXrefSymbols(); 
 
  void setDimblk(const OdChar*); 
  void setDimblk1(const OdChar*); 
  void setDimblk2(const OdChar*); 
  void setDimldrblk(const OdChar*); 
 
  void getDimstyleChildData(const OdRxClass *pDimClass, 
                            OdDbDimStyleTableRecordPtr& pRec, 
                            OdDbObjectId &style) const; 
 
  OdDbObjectId getDimstyleChildId(const OdRxClass *pDimClass, 
                                  OdDbObjectId &parentStyle) const; 
 
  OdDbObjectId getDimstyleParentId(OdDbObjectId &childStyle) const; 
 
  void getDimRecentStyleList(OdDbObjectIdArray& objIds) const; 
 
  void applyPartialOpenFilters(const OdDbSpatialFilter* pSpatialFilter, 
                               const OdDbLayerFilter* pLayerFilter); 
 
  void disablePartialOpen(); 
 
  void newFingerprintGuid(); 
 
  void newVersionGuid(); 
 
  double viewportScaleDefault() const; 
 
  void setViewportScaleDefault(double newDefaultVPScale); 
 
  OdDbObjectId getPaperSpaceVportId() const; 
 
  virtual void copyLayout(const OdChar* copyname, const OdChar* newname); 
 
  virtual void cloneLayout(const OdDbLayout* pLBTR, const OdChar* newname, int newTabOrder); 
 
  virtual OdDbObjectId getNonRectVPIdFromClipId(const OdDbObjectId& clipId); 
 
  virtual bool isViewportClipped(short index); 
 
  */
  OdDbObjectId byLayerMaterialId() const;
  OdDbObjectId byBlockMaterialId() const;
  OdDbObjectId globalMaterialId() const;
  OdDbObjectId activeViewportId() const;
  //[Added by chinaweal renkangcheng [2007/09/29] 
  //Reason:New Interface 
#  ifdef ZW_NEW_INTERFACES
  short ret_type();
   /** Description: 
    Returns true if the database saved with transformation, otherwise returns false. 
  */
  bool isFileNeedTransformed();
  /** Description: 
	Sets the flag *bTransform* to the database. 
    Arguments: 
    bTransform (I) The flag of *bTransform*. 
	Remarks: 
    Each *bTransform* must be one of the following: 
      
    @table 
    Name              Value   Description 
    true				0       saved with tramsformation  
    false				1       saved without tramsformation  
  */
  void setFileNeedTransformed(bool bTransform = false);
#  endif
  //]Added by chinaweal renkangcheng [2007/09/29] 
private:
  friend class OdDbDatabaseImpl;
  OdDbDatabaseImpl* m_pImpl;
};
/** Fills in OdThumbnailImage object from stream. Throws appropriate exception if an error occurred. 
*/
TOOLKIT_EXPORT void odDbGetPreviewBitmap(OdStreamBuf* pStreamBuf, OdThumbnailImage* pPreview);
// The functions below provide write access to "Read-Only" *database* variables. 
// Actually they are a OdDb::kludge for bypassing non-implemented DD functionality 
// or to repair invalid drawings. 
// They should be used with care. 
 
/** Description: 
    Sets the DWGCODEPAGE value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for DWGCODEPAGE. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetDWGCODEPAGE(OdDbDatabase& db, OdCodePageId val);
/** Description: 
    Sets the TDUCREATE system variable in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for TDUCREATE. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetTDUCREATE(OdDbDatabase& db, OdDbDate val);
/** Description: 
    Sets the TDUUPDATE value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for TDUUPDATE. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetTDUUPDATE(OdDbDatabase& db, OdDbDate val);
/** Description: 
    Sets the TDINDWG value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for TDINDWG. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetTDINDWG(OdDbDatabase& db, OdDbDate val);
/** Description: 
    Sets the TDUSRTIMER value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for TDUSRTIMER. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetTDUSRTIMER(OdDbDatabase& db, OdDbDate val);
/** Description: 
    Sets the PSTYLEMODE value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for PSTYLEMODE. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetPSTYLEMODE(OdDbDatabase& db, bool val);
/** Description: 
    Sets the UCSORG system variable in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for UCSORG. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetUCSORG(OdDbDatabase& db, OdGePoint3d val);
/** Description: 
    Sets the UCSXDIR value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for UCSXDIR. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetUCSXDIR(OdDbDatabase& db, OdGeVector3d val);
/** Description: 
    Sets the UCSYDIR value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for UCSYDIR. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetUCSYDIR(OdDbDatabase& db, OdGeVector3d val);
/** Description: 
    Sets the PUCSORG value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for PUCSORG. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetPUCSORG(OdDbDatabase& db, OdGePoint3d val);
/** Description: 
    Sets the PUCSXDIR value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for PUCSXDIR. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetPUCSXDIR(OdDbDatabase& db, OdGeVector3d val);
/** Description: 
    Sets the PUCSYDIR value in the specified OdDbDatabase instance. 
     
    Arguments: 
    db (I) Database. 
    val (I) Value for PUCSYDIR. 
     
    Note: 
    This function provides write access to "Read-Only" system variables. 
    It may be used to bypass non-implemented DWGdirect functionality or to repair drawings, 
    and should be used with care. 
*/
TOOLKIT_EXPORT void odDbSetPUCSYDIR(OdDbDatabase& db, OdGeVector3d val);
 /** Description: 
    Saves an MLineStyle to the specified file. 
    Arguments: 
    db (I) OdDbDatabase object. 
    filename (I) Name of the MlineStyle file to save. 
  */
TOOLKIT_EXPORT extern void odDbSaveLineTypeFile(OdDbDatabase& Db, OdStreamBuf& filename);
 /** Description: 
    Loads an MLineStyle into the specified *database* object. 
 
    Arguments: 
    db (I) OdDbDatabase object. 
    patternName (I) Name of the pattern to load.  
    filename (I) Name of the MlineStyle file from which to load. 
    dlt (I) Duplicate linetype loading. 
    Remarks: 
    dlt must be one of the following: 
     
    @table 
    Name                        Value   Description 
    OdDb::kDltNotApplicable     0       Not Applicable. 
    OdDb::kDltIgnore            1       Ignore duplicate LineTypes. 
    OdDb::kDltReplace           2       Replace duplicate LineTypes. 
     
    Throws: 
    An appropriate error if not successful. 
  */
TOOLKIT_EXPORT extern void odDbLoadMlineStyleFile(OdDbDatabase& db, const OdString& patternName, OdStreamBuf& filename, OdDb::DuplicateLinetypeLoading dlt = OdDb::kDltNotApplicable);
 /** Description: 
    Arguments: 
    db (I) OdDbDatabase object. 
    filename (I) Name of the MlineStyle file from which to load. 
  */
TOOLKIT_EXPORT extern void odDbSaveMlineStyleFile(OdDbDatabase& Db, OdStreamBuf& filename);
#  include "DD_PackPop.h"
#endif
