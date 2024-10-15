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
// Name:            DbSection.h
//
// Description:     Header for AcDbSection class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "AdAChar.h"
#include "dbmain.h"
#include "dbhatch.h"
#include "acstring.h"

//prevent the MS header "use_ansi.h" from outputing
//its linker directives, we expect clients to specify
//what flavor (debug/release) of the C++ runtime they want to
//link against.
#pragma push_macro("_USE_ANSI_CPP")
#define _USE_ANSI_CPP
#include <map>
#pragma pop_macro("_USE_ANSI_CPP")
typedef std::map<AcDbEntity*, Adesk::UInt32> AcDbSectionGeometryMap;

class AcDbSectionSettings;


//*************************************************************************
// AcDbSection
//*************************************************************************
/// <summary>
/// This class represents the section plane entity in AutoCAD.
/// </summary>
class AcDbSection : public AcDbEntity
{
public:
    
    /// <summary>
    /// Section plane types: Plane, Boundary, and Volume 
    /// </summary>
    /// <param name="kPlane"> Section plane extends infinitely in all directions</param>
    /// <param name="kBoundary"> Section plane is bounded by the section line, two side lines, and a back line. However it extends infinitely up and down. </param>
    /// <param name="kVolume"> Section plane is bounded by the front, side, back, top, and bottom lines. </param>
    enum State
    {
        kPlane              = (0x1 << 0),
        kBoundary           = (0x1 << 1),
        kVolume             = (0x1 << 2),
    };

    /// <summary>
    /// Hit flags for section plane. This enum value is returned by the method hitTest. 
    /// </summary>
    enum SubItem
    {
        kNone               = 0,
        kSectionLine        = (0x1 << 0),
        kSectionLineTop     = (0x1 << 1),
        kSectionLineBottom  = (0x1 << 2),
        kBackLine           = (0x1 << 3),
        kBackLineTop        = (0x1 << 4),
        kBackLineBottom     = (0x1 << 5),
        kVerticalLineTop    = (0x1 << 6),
        kVerticalLineBottom = (0x1 << 7),
    };

    /// <summary>
    /// Height flags for section plane. 
    /// </summary>
    /// <param name="kHeightAboveSectionLine"> Height of the section plane above section line - from the section plane elevation to the top line of the section plane.  </param>
    /// <param name="kHeightBelowSectionLine"> Height of the section plane below the section line - from the section plane elevation to the bottom line of the section plane. </param>
    enum Height
    {
        kHeightAboveSectionLine = 0x1,
        kHeightBelowSectionLine = 0x2,
    };

public:
    ACDB_DECLARE_MEMBERS(AcDbSection);

    /// <summary>
    /// Default constructor. Constructs a section plane with the type initialized to AcDbSection::kPlane. Since a section plane should have at least two vertices, the section plane constructed by this constructor is invalid until vertices are added. Invalid section planes should not be posted to the database. If they are posted they will remain invisible in the database. 
    /// </summary>
    ACDB_PORT AcDbSection(void);
    /// <summary>
    /// Constructs a section plane using the specified points and vector. 
    /// </summary>
    /// <param name="pts">Input vertex points on the section line; should contain at least two points </param>
    /// <param name="verticalDir">Input vector on the first segment's plane, normal to the section line </param>
    ACDB_PORT AcDbSection(const AcGePoint3dArray& pts,
        const AcGeVector3d& verticalDir);
    /// <summary>
    /// Constructs a section plane using the specified points, normal, and viewing direction.
    /// </summary>
    /// <param name="pts">Input vertex points on the section line; should contain at least two points </param>
    /// <param name="verticalDir">Input vector on the first segment's plane, normal to the section line </param>
    /// <param name="vecViewingDir">Input vector specifying the viewing direction  </param>
    ACDB_PORT AcDbSection(const AcGePoint3dArray& pts,
        const AcGeVector3d& verticalDir, const AcGeVector3d& vecViewingDir);
    /// <summary>
    /// Destructor. 
    /// </summary>
    ACDB_PORT ~AcDbSection(void);
    /// <summary>
    /// Returns the state of this section object. See the AcDbSection::State enum for descriptions of possible states.
    /// </summary>
    ACDB_PORT AcDbSection::State state      (void) const;
    /// <summary>
    /// Sets the state of this section object. See the AcDbSection::State enum for descriptions of possible states.
    /// </summary>
    ACDB_PORT Acad::ErrorStatus setState    (AcDbSection::State nState);
    /// <summary>
    /// This function returns name of the section plane.
    /// </summary>
    ACDB_PORT const ACHAR* getName          (void) const;
    /// <summary>
    /// This function returns name of the section plane.
    /// </summary>
    ACDB_PORT Acad::ErrorStatus getName     (AcString& sName) const;
    /// <summary>
    /// This function returns name of the section plane.
    /// </summary>
    Acad::ErrorStatus getName     (ACHAR*& pszName) const;    // deprecated
    /// <summary>
    /// This function sets the name of the section plane. The name should not be blank and should be unique. It cannot contain the vertical bar, or pipe, character ("|").
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the input is invalid, or Acad::eDuplicateRecordName if the name is not unique.
    /// </summary>
    /// <param name="pszName"> Input the name.</param>
    ACDB_PORT Acad::ErrorStatus setName     (const ACHAR* pszName);
    /// <summary>
    /// This function returns a unit vector that specifies the viewing direction of the section plane. The returned vector is perpendicular to the first segment's plane.
    /// </summary>
    ACDB_PORT AcGeVector3d viewingDirection (void) const;
    /// <summary>
    /// This function sets the viewing direction of the section plane. The vector should be perpendicular to the first segment's plane.
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput if the input vector is invalid.
    /// </summary>
    /// <param name="dir">Input the view direction vector. </param>
    ACDB_PORT Acad::ErrorStatus setViewingDirection(const AcGeVector3d& dir);
    /// <summary>
    /// This function returns a unit vector specifying the vertical direction of the section plane. The returned vector is on first segment's plane, perpendicular to the section line.
     /// </summary>
    ACDB_PORT AcGeVector3d verticalDirection(void) const;
    /// <summary>
    /// This function sets the vertical direction of the section plane. The vector should be perpendicular to the section line.
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput if the input vector is invalid.
    /// </summary>
    /// <param name="dir">Input the vertical direction vector. </param>
    ACDB_PORT Acad::ErrorStatus setVerticalDirection(const AcGeVector3d& dir);
    /// <summary>
    /// This function returns the normal vector. The returned unit vector is perpendicular to the first segment of the section plane.
     /// </summary>
    ACDB_PORT AcGeVector3d normal           (void) const;
    /// <summary>
    /// This function returns the vectors of the section plane that form the first segment of the plane.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="uAxis">Output unit vector of the section line from the first vertex </param>
    /// <param name="vAxis">Output unit vector on the section plane, perpendicular to the section line </param>
    ACDB_PORT Acad::ErrorStatus plane       (AcGeVector3d& uAxis, 
                                             AcGeVector3d& vAxis) const;

    /// <summary>
    /// This function returns the transparency value for the section plane indicator. The transparency value is in the range 1 to 100.
     /// </summary>
    ACDB_PORT int   indicatorTransparency   (void) const;
    /// <summary>
    /// This function sets the transparency for the section plan indicator.
    /// Return Acad::eOk if successful, or Acad::eInvalidInput if the transparency value is invalid.
    /// </summary>
    /// <param name="nTransparency">Input transparency value in the range 1 to 100 </param>
    ACDB_PORT Acad::ErrorStatus setIndicatorTransparency(int nTransparency);

    /// <summary>
    /// This function returns the fill color of the section plane indicator.
    /// </summary>
    ACDB_PORT AcCmColor indicatorFillColor  (void) const;
    /// <summary>
    /// This function sets the fill color of the section plane indicator.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="color">Input fill color of the section plane indicator </param> 
    ACDB_PORT Acad::ErrorStatus setIndicatorFillColor(const AcCmColor& color);

    /// <summary>
    /// This function returns the number of vertices on the section of the section plane. A valid section plane has a minimum of two vertices.
    /// </summary>
    ACDB_PORT int numVertices               (void) const;
    /// <summary>
    /// Gets the position of the specified vertex.
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput if the index is out of range.
    /// </summary>
    /// <param name="nIndex">Input zero-based index of the vertex to be retrieved; should be less than the number of vertices </param> 
    /// <param name="pt">Output reference to receive the position of the vertex </param> 
    ACDB_PORT Acad::ErrorStatus getVertex   (int nIndex, 
                                             AcGePoint3d& pt) const;
    /// <summary>
    /// Sets the position of the specified vertex.
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the index is out of range or the position is invalid.
    /// Returns Acad::eNotApplicable if it's a slice type section.
    /// </summary>
    /// <param name="nIndex">Input zero-based index of the vertex to set; should be less than the number of vertices </param> 
    /// <param name="pt">Input new position of the vertex </param> 
    ACDB_PORT Acad::ErrorStatus setVertex   (int nIndex, 
                                             const AcGePoint3d& pt);
    /// <summary>
    /// Inserts or adds a new vertex to the section plane. If nInsertAt is less than zero, or is equal to or more than the number of vertices, the new vertex will be added after the last vertex.
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput if the position is invalid.
    /// </summary>
    /// <param name="nInsertAt"> Input index at which to add the new vertex  </param> 
    /// <param name="pt"> Input position of the new vertex  </param> 
    ACDB_PORT Acad::ErrorStatus addVertex   (int nInsertAt, 
                                             const AcGePoint3d& pt);
    /// <summary>
    /// This function removes a vertex from the section plane. The first vertex cannot be removed.
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the index specifies the first vertex or is out of range.
    /// </summary>
    /// <param name="nIndex">Input index of the vertex to remove </param> 
    ACDB_PORT Acad::ErrorStatus removeVertex(int nIndex);
    /// <summary>
    /// This function returns all section plane vertices in the pts array.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="pts"> Output reference to receive vertices </param> 
    ACDB_PORT Acad::ErrorStatus getVertices (AcGePoint3dArray& pts) const;
    /// <summary>
    /// Sets the vertices of the section plane. The current vertices are deleted. If the input array does not have at least two points, this function fails.
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput if the vertex points result in an invalid section.
    /// </summary>
    /// <param name="pts"> Input array of vertex points to set </param> 
    ACDB_PORT Acad::ErrorStatus setVertices (const AcGePoint3dArray& pts);

    /// <summary>
    /// This function returns the height of the section plane above or below the section line. The returned height is the indicator height when the section plane type is either plane or boundary, since the cut extends infinitely in the vertical direction for these two types. The height of the cut is returned when the section plane type is volume.
    /// </summary>
    /// <param name="nHeightType">Input one of the Height enum values: kHeightAboveSectionLine or kHeightBelowSectionLine </param> 
    ACDB_PORT double height                 (AcDbSection::Height nHeightType) const;
    /// <summary>
    /// This function sets the height of the section plane above or below the section line. The height is the indicator height when the section plane type is plane or boundary, since the cuts extends infinitely in the vertical direction for these two types.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nHeightType"> Input one of the Height enum values: kHeightAboveSectionLine or kHeightBelowSectionLine  </param> 
    /// <param name="fHeight"> Input height  </param> 
    ACDB_PORT Acad::ErrorStatus setHeight   (AcDbSection::Height nHeightType, 
                                             double fHeight);

    /// <summary>
    /// This function performs a hit test on the section plane and returns the result.
    /// Returns true if the point lies on the section plane.
    /// </summary>
    /// <param name="ptHit">  Input point to perform hit test </param> 
    /// <param name="pSegmentIndex">  Output zero-based index of the segment on the section line, which passes near or through the hit point </param> 
    /// <param name="ptOnSegment">  Output pointer to receive the actual point on the section plane geometry, or null if this is not required  </param> 
    /// <param name="pSubItem">  Output one or more of the SubItem enum values, or null if this is not required  </param> 
    ACDB_PORT bool  hitTest                 (const AcGePoint3d& ptHit, 
                                             int* pSegmentIndex, 
                                             AcGePoint3d* ptOnSegment, 
                                             AcDbSection::SubItem* pSubItem) const;

    /// <summary>
    /// Creates a jog in the section plane at the specified point.
    /// Returns Acad::eOk if successful. Returns Acad::eInvalidInput if the point does not lie on the section plane or if the jog cannot be created at the specified point.
    /// Returns Acad::eNotApplicable if it's a slice type section.
    /// </summary>
    /// <param name="ptOnSection"> Input point on the section line at which to create the jog </param>
    ACDB_PORT Acad::ErrorStatus createJog   (const AcGePoint3d& ptOnSection);

    /// <summary>
    /// The function returns the ID of the AcDbSectionSettings object, which stores all the settings for section creation.
    /// </summary>
    ACDB_PORT AcDbObjectId getSettings      (void) const;
    /// <summary>
    /// This function opens the AcDbSectionSettings object and returns it.
    /// Returns Acad::eOk if successful. Returns an AutoCAD error status if the function fails to open the object.
    /// </summary>
    /// <param name="pSettings"> Output reference to receive the opened object </param>
    /// <param name="mode"> Input open mode </param>
    ACDB_PORT Acad::ErrorStatus getSettings (AcDbSectionSettings*& pSettings, 
                                             AcDb::OpenMode mode) const;

    /// <summary>
    /// This function returns true if live sectioning is enabled in the section plane.
    /// </summary>
    ACDB_PORT bool  isLiveSectionEnabled    (void) const;
    /// <summary>
    /// If bEnable is true, this function enables live sectioning in the section plane. At any time, only one section plane in a drawing can have its live section enabled. Enabling live sectioning in one section plane will automatically disable it in other section planes.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="bEnable">Input Boolean indicating whether live sectioning should be enabled </param>
    ACDB_PORT Acad::ErrorStatus enableLiveSection(bool bEnable);

    /// <summary>
    /// This function generates 2D or 3D section geometry. Sectionable entities include AcDb3dSolid, AcDbSurface, AcDbBody, and AcDbRegion.
    /// Returns Acad::eOk if successful. Returns an AutoCAD error status if the function fails to open the object. Returns a modeling error if the plane and the solid do not intersect. 
    /// </summary>
    /// <param name="pEnt">  Input pointer to the sectionable entity  </param>
    /// <param name="intBoundaryEnts"> Output array containing intersection boundary geometry </param>
    /// <param name="intFillEnts"> Output array containing intersection fill annotation geometry </param>
    /// <param name="backgroundEnts"> Output array containing background geometry </param>
    /// <param name="foregroundEnts"> Output array containing foreground geometry </param>
    /// <param name="curveTangencyEnts"> Output array containing curve tangency geometry </param>
    /// <remarks>For each of the 5 output array arguments, the calling application is responsible for the resulting entities (that is, either appending them to a database or deleting them when they are no longer needed).</remarks>
    ACDB_PORT Acad::ErrorStatus generateSectionGeometry(AcDbEntity *pEnt,
                                                        AcArray<AcDbEntity*>& intBoundaryEnts,
                                                        AcArray<AcDbEntity*>& intFillEnts,
                                                        AcArray<AcDbEntity*>& backgroundEnts,
                                                        AcArray<AcDbEntity*>& foregroundEnts,
                                                        AcArray<AcDbEntity*>& curveTangencyEnts) const;
    
    /// <summary>
    /// The elevation of section.
    /// </summary>
    ACDB_PORT double elevation() const;
    /// <summary>
    /// Sets elev to be the Model Space ELEVATION value for the database.
    /// See the System Variables section of the AutoCAD Command Reference for information on ELEVATION.
    /// Returns Acad::eOk if successful.
    /// Note for Paper Space values, see AcDbDatabase::setPelevation function.
    /// </summary>
    /// <param name="elev"> Input ELEVATION value for model space. </param>
    ACDB_PORT Acad::ErrorStatus setElevation( double elev);
    /// <summary>
    /// The topPlane of section.
    /// </summary>
    ACDB_PORT double topPlane() const;
    /// <summary>
    /// Sets topPlane of section.
    /// <param name="value">  Input the top plane. </param>
    /// </summary>
    ACDB_PORT Acad::ErrorStatus setTopPlane( double);
    /// <summary>
    /// Bottom plane of section.
    /// </summary>
    ACDB_PORT double bottomPlane() const;
    /// <summary>
    /// Sets bottom plane of section.
    /// <param name="value">  Input the bottom plane. </param>
    /// </summary>
    ACDB_PORT Acad::ErrorStatus setBottomPlane( double );

public:
    // Base class overrides

    /// <summary>
    /// This function is called by dwgIn(). Its purpose is to allow the object to read in its data. 
    /// 
    /// There is a fixed set of steps that should be followed when implementing your own version of this function: 
    /// 
    /// Call assertWriteEnabled(). 
    /// Call the parent class's dwgInFields() passing it pFiler. If this returns Acad::eOk, then continue; otherwise, immediately return whatever the parent class's dwgInFields() returned. 
    /// Use pFiler to call the appropriate AcDbDwgFiler methods to read in the object's data items. It is essential that the same number of data items be read in, and in the same order, as those that are written out via dwgOutFields(). 
    /// 
    /// 
    /// Following these steps results in all base classes having their implementations of this function called as well, thus reading in all the object's data in class hierarchical order. 
    /// 
    /// The actual AcDbObject::dwgInFields() implementation takes care of reading in the object's handle as well as its persistent reactor, extension dictionary, and xdata information. 
    /// 
    /// This function should return Acad::eOk if successful. In your own custom class implementations of this function, it's easiest to just return pFiler->filerStatus(). 
    /// </summary>
    /// <remarks> Note:The designer of an application class may want to have the RECOVER and AUDIT commands fix the data in a custom class, in cases where its data is corrupted, or objects referred to from the custom object are invalid. If this is desired, then the dwgInFields() method for the custom class should be tolerant to invalid data (for example, null objectIds where non-null data is expected), and not return an error status when it is possible to recover from the errors. During RECOVER and AUDIT, the audit() method subsequently are called for the object, giving it an opportunity to fix its data and return to a reasonable state. 
    /// 
    /// Exercise care in this decision, as currently there exists no flag to inform dwgInFields() whether it is being called during RECOVER, or during another process; for example, OPEN. This implies that a too tolerant version of dwgInFields() may allow an invalid object to be read in, that may or may not be audited later.</remarks>
    /// <param name="pFiler"> Passed in pointer to filer to use to read in the object's data </param>
    ACDB_PORT virtual Acad::ErrorStatus dwgInFields (AcDbDwgFiler* pFiler) override;
    /// <summary>
    /// This function is called by dwgOut(). Its purpose is to allow the object to write out its data. 
    /// 
    /// There is a fixed set of steps that should be followed when implementing your own version of this function: 
    /// 
    /// 
    /// Call assertReadEnabled(). 
    /// Call the parent class's dwgOutFields() passing it pFiler. If this returns Acad::eOk, then continue; otherwise, immediately return whatever the parent class's dwgInFields() returned. 
    /// Use pFiler to call the appropriate AcDbDwgFiler methods to write out the object's data items. It is essential that the same number of data items be written out, and in the same order, as those that are read in via dwgInFields(). 
    ///  
    /// 
    /// Following these steps results in all base classes having their implementations of this function called as well, thus writing out all the object's data in class hierarchical order. 
    /// 
    /// The actual AcDbObject::dwgOutFields() implementation takes care of writing out the object's handle as well as its persistent reactor, extension dictionary, and xdata information. 
    /// 
    /// This function should return Acad::eOk if successful. In your own custom class implementations of this function, it's easiest to just return pFiler->filerStatus().
    /// 
    /// </summary>
    /// <param name="pFiler"> Passed in pointer to filer to use to write out the object's data </param>
    ACDB_PORT virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const override;
    /// <summary>
    /// This function is called by dxfIn(). Its purpose is to allow the object to read in its data. 
    /// 
    /// There is a fixed set of steps that should be followed when implementing your own version of this function: 
    /// 
    /// 
    /// Call assertWriteEnabled(). 
    /// Call the parent class's dxfInFields(), passing it pFiler. If this returns Acad::eOk, then continue; otherwise immediately return whatever the parent class's dxfInFields() returned. 
    /// Call pFiler->atSubclassData(), passing in the string that was written out with group code 100 in dxfOutFields(). If this returns Adesk::kTrue, then continue. Otherwise immediately return an error status other than Acad::eOk (for example, Acad::eBadDxfSequence). 
    /// Now read in the data. The DXF filer has only one readItem function which reads a single data item into a resbuf structure. The data read in must then be copied from the resbuf into whatever data member it belongs in. 
    /// 
    /// 
    /// As of R13, it is possible to have order-dependent data. In custom classes you can have all order-independent, all order-dependent, or a mix of some order-independent and some order-dependent. 
    /// 
    /// For order-independent read in, use a loop that reads a single data item and then uses a switch statement or if-then-elseif chain to figure out what has been read in and place it into the appropriate data member. If an unexpected or unknown group code is read in, use pFiler->pushBackitem() to rewind the file pointer back to the item that was wrong. Then return immediately with an appropriate error status (such as Acad::eBadDxfSequence or Acad::eInvalidDxfCode). 
    /// 
    /// For order-dependent read in, use individual pFiler->readItem() calls to read each data item. Be sure to verify that each item read in is what it's supposed to be. If not, use pFiler->pushBackitem() to rewind the file pointer back to the item that was wrong and then return immediately with an appropriate error status (such as Acad::eBadDxfSequence, or Acad::eInvalidDxfCode). 
    /// 
    /// <remarks>An object ID comes in as an ads_name in the resbuf's resval.rlname field. Use the global function acdbGetObjectId() to convert it into an objectId and place it in the appropriate data member. 
    /// 
    /// Following these steps results in all base classes having their implementations of this function called as well, thus reading in all the object's data in class hierarchical order. 
    /// 
    /// The actual AcDbObject::dxfInFields() implementation takes care of reading in the object's handle as well as its persistent reactor, extension dictionary, and xdata information. 
    /// 
    /// This function should return Acad::eOk if successful. In your own custom class implementations of this function, it's easiest to just return pFiler->filerStatus().</remarks>
    /// </summary>
    /// <param name="pFiler"> Passed in pointer to filer to use to read in the object's data  </param>
    ACDB_PORT virtual Acad::ErrorStatus dxfInFields (AcDbDxfFiler* pFiler) override;
    /// <summary>
    /// This function is called by dxfOut(). Its purpose is to allow the object to write out its data. 
    /// 
    /// There is a fixed set of steps that should be followed when implementing your own version of this function: 
    /// 
    /// 1. Call assertReadEnabled(). 
    /// 
    /// 2. Call the parent class's dxfOutFields(), passing it pFiler. If this returns Acad::eOk, then continue; otherwise immediately return whatever the parent class's dwgInFields() returned. 
    /// 
    /// 3. Use pFiler->writeItem(AcDb::kDxfSubclass, ), where is a string that is typically your class's name, but can be any string you wish up to 256 bytes long. This same string is used in dxfInFields(). 
    /// 
    /// 4. Use pFiler to call the appropriate AcDbDxfFiler methods to write out the object's data items along with the appropriate group code values (see table below). 
    /// 
    /// Following these steps results in all base classes having their implementations of this function called as well, thus writing out all the object's data in class hierarchical order. 
    /// 
    /// The actual AcDbObject::dxfOutFields() implementation takes care of writing out the object's handle as well as its persistent reactor, extension dictionary, and xdata information. 
    /// 
    /// This function should return Acad::eOk if successful. In your own custom class implementations of this function, it's easiest to just return pFiler->filerStatus(). 
    /// 
    /// Here are the DXF group code ranges for object representation: 
    /// 
    ///  
    /// 
    /// From  To  Data Type  
    /// 1  4  text  
    /// 6  9  text  
    /// 10  17  point or vector (3 reals)  
    /// 38  59  real  
    /// 60  79  16-bit integer  
    /// 90  99  32-bit integer  
    /// 100  100  subclass data marker  
    /// 102  102  text  
    /// 140  149  real  
    /// 170  179  16-bit integer  
    /// 210  219  3 reals  
    /// 270  279  16-bit integer  
    /// 280  289  8-bit integer  
    /// 300  309  text  
    /// 310  319  binary chunk  
    /// 320  329  handle  
    /// 330  339  soft pointer ID  
    /// 340  349  hard pointer ID  
    /// 350  359  soft owner ID  
    /// 360  369  hard owner ID  
    /// </summary>
    /// <param name="pFiler"> Passed in pointer to filer to use to write out the object's data </param>
    ACDB_PORT virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const override;
    /// <summary>
    /// Called from within close() before anything else is done. The default implementation is to return Acad::eOk. However, when overridden in custom classes, it provides a hook into the close operation. If it returns anything other than Acad::eOk, then the close operation is immediately terminated. 
    /// 
    /// When overriding this function, a sequence of steps is required: 
    /// 
    /// 
    /// Check to be sure everything is correct with the AcDbObject's state. If not, then immediately return a value other than Acad::eOk, which terminates the close operation. 
    /// Call the parent class's subClose(). If this returns Acad::eOk, then continue; otherwise immediately return whatever the parent class's subClose() returned. 
    /// Do any operations desired before the close operation continues. 
    /// Return Acad::eOk to allow the close operation to continue normally. 
    /// <remarks> When implementing your own subClose(), it is best not to change any of the object's state at all. But, if you must, then it is best to make such changes after invoking the parent class's subClose(), just in case it returns an error code other than Acad::eOk. If you must change state before invoking the parent class's subClose(), then be prepared to reverse the changes if the parent class returns a status other than Acad::eOk.</remarks>
    /// </summary>
    ACDB_PORT virtual Acad::ErrorStatus subClose() override;


    // INTERNAL USE ONLY
    /// <summary>
    /// This is internal use only.
    /// </summary>
    ACDB_PORT Acad::ErrorStatus generateSectionGeometry(const AcArray<AcDbEntity*>& entset,
                                                        AcArray<AcDbEntity*>& intBoundaryEnts,
                                                        AcArray<AcDbEntity*>& intFillEnts,
                                                        AcArray<AcDbEntity*>& backgroundEnts,
                                                        AcArray<AcDbEntity*>& foregroundEnts,
                                                        AcArray<AcDbEntity*>& curveTangencyEnts) const;
   
    // INTERNAL USE ONLY
    /// <summary>
    /// This is internal use only.
    /// </summary>
    ACDB_PORT Acad::ErrorStatus generateSectionGeometry(const AcDbVoidPtrArray& bodies,
                                                        const AcDbIntArray& instanceCount,
                                                        const AcArray<AcGeMatrix3d>& xforms,
                                                        const AcArray<AcRxClass*>& providerClasses,
                                                        AcArray<AcDbEntity*>& intBoundaryEnts,
                                                        AcArray<AcDbEntity*>& intFillEnts,
                                                        AcArray<AcDbEntity*>& backgroundEnts,
                                                        AcArray<AcDbEntity*>& foregroundEnts,
                                                        AcArray<AcDbEntity*>& curveTangencyEnts,
                                                        AcDbSectionGeometryMap* = NULL) const;
protected:
    ACDB_PORT virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;

public:
    /// <summary>
    /// If a section object is a slice type. If it is, the state will be set as kBoundary and all jogs will be removed.
    /// Returns Acad::eOk.
    /// </summary>
    ACDB_PORT bool                      isSlice          () const;
    /// <summary>
    /// Set the section object into slice type.
    /// This will also set the state into kBoundary if the value is true.
    /// Returns Acad::eOk.
    /// </summary>
    /// <param name="value"> True to set section into slice, false otherwise. </param>
    ACDB_PORT Acad::ErrorStatus         setIsSlice       (bool value);

    /// <summary>
    /// Return the thickness depth of a section. For slice type only, otherwise it will return 0.0
    /// </summary>
    ACDB_PORT double                    thicknessDepth   () const;
    /// <summary>
    /// Sets the thickness depth of a section. 
    /// Returns Acad::eNotApplicable if it is not a slice type section, otherwise it will return Acad::eOk if successfully.
    /// </summary>
    /// <param name="fThickness"> The thickness depth, 0 is not accepted. </param>
    ACDB_PORT Acad::ErrorStatus         setThicknessDepth(double fThickness);
    
    /// <summary>
    /// Check if the section has jogs. 
    /// </summary>
    ACDB_PORT bool                      hasJogs          () const;

    /// <summary>
    /// Return the section plane offset distance. The offset is the distance between the section plane
    /// and the parallel plane passing through WCS origin. If the section line has multiple segments,
    /// it is the plane of the first segment.
    /// </summary>
    ACDB_PORT double                    sectionPlaneOffset() const;
    /// <summary>
    /// Sets the offset distance of a section. 
    /// Returns Acad::eOk if successfully.
    /// </summary>
    /// <param name="offset"> the offset distance. </param>
    ACDB_PORT Acad::ErrorStatus         setSectionPlaneOffset(double offset);
};


//*************************************************************************
// AcDbSectionSettings
//*************************************************************************

/// <summary>
/// This class stores section geometry settings. 
/// </summary>
class AcDbSectionSettings : public AcDbObject
{
public:
    /// <summary>
    /// Options for section generation. This enum is used to get and set properties for generated section geometry. There are two groups of flags: type of section and type of generated geometry. The enum values kLiveSection, k2dSection, and k3dSection belong in first group and the values kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, and kCurveTangencyLines belong in second group. One value from each group should be OR'd to specify the geometry for which the property is obtained or set.
    /// </summary>
    /// <param name="kLiveSection"> Live sectioning.  </param>
    /// <param name="k2dSection"> 2d section. </param>
    /// <param name="k3dSection"> 3d section. </param>
    enum SectionType
    {
        // Section types
        kLiveSection                = (0x1 << 0),       // Live section
        k2dSection                  = (0x1 << 1),       // 2d section
        k3dSection                  = (0x1 << 2),       // 3d section
    };
    
    /// <summary>
    /// Generation flags to control section creation. There are three groups of flags: type of section to generate, source, and destination. One value from each group should be OR'd to set the generation options. The options kGenerate2dSection and kGenerate3dSection form the first group to specify the type of section. kSourceAllObjects and kSourceSelectedObjects form the second group to specify the source. kDestinationNewBlock, kDestinationReplaceBlock, and kDestinationFile form the third group to specify destination for the generated geometry.
    /// </summary>
    /// <param name="kIntersectionBoundary"> Intersection boundary settings. </param>
    /// <param name="kIntersectionFill"> Intersection surface settings.  </param>
    /// <param name="kBackgroundGeometry"> Background geometry settings. </param>
    /// <param name="kForegroundGeometry"> Foreground geometry settings. </param>
    /// <param name="kCurveTangencyLines"> Curve tangency line settings. </param>
    /// <remarks> Options for section generation. This enum is used to get and set properties for generated section geometry. </remarks>
    enum Geometry
    {
        // Geometry type
        kIntersectionBoundary       = (0x1 << 0),       // Intesection boundary
        kIntersectionFill           = (0x1 << 1),       // Intesection fill
        kBackgroundGeometry         = (0x1 << 2),       // Background geometry
        kForegroundGeometry         = (0x1 << 3),       // Foreground geometry
        kCurveTangencyLines         = (0x1 << 4),       // Curve tangency lines
    };

    /// <summary>
    /// Generation flags to control section creation. There are three groups of flags: type of section to generate, source, and destination. One value from each group should be OR'd to set the generation options. The options kGenerate2dSection and kGenerate3dSection form the first group to specify the type of section. kSourceAllObjects and kSourceSelectedObjects form the second group to specify the source. kDestinationNewBlock, kDestinationReplaceBlock, and kDestinationFile form the third group to specify destination for the generated geometry.
    /// </summary>
    /// <param name="kSourceAllObjects"> The section plane cuts all the objects found in the drawing  </param>
    /// <param name="kSourceSelectedObjects"> The section plane cuts only the selected objects  </param>
    /// <param name="kDestinationNewBlock"> Creates section as a new block  </param>
    /// <param name="kDestinationReplaceBlock"> Replaces an existing block while creating section  </param>
    /// <param name="kDestinationFile"> Saves the generated section in an external file.  </param>
    /// <remarks> Description: Generation flags to control section creation. There are three groups of flags: type of section to generate, source, and destination. One value from each group should be OR'd to set the generation options. The options kGenerate2dSection and kGenerate3dSection form the first group to specify the type of section. kSourceAllObjects and kSourceSelectedObjects form the second group to specify the source. kDestinationNewBlock, kDestinationReplaceBlock, and kDestinationFile form the third group to specify destination for the generated geometry. </remarks>
    enum Generation
    {
        // Source geometry options (bits 0 to 3)
        kSourceAllObjects           = (0x1 << 0),       // Include all objects
        kSourceSelectedObjects      = (0x1 << 1),       // Include selected objects

        // Destination options (bits 4 to 8)
        kDestinationNewBlock        = (0x1 << 4),       // Insert as new block
        kDestinationReplaceBlock    = (0x1 << 5),       // Replace existing block
        kDestinationFile            = (0x1 << 6),       // Export to a file
    };

public:
    ACDB_DECLARE_MEMBERS(AcDbSectionSettings);

    /// <summary>
    /// Default constructor. 
    /// </summary>
    AcDbSectionSettings();
    /// <summary>
    /// Destructor. 
    /// </summary>
    ~AcDbSectionSettings();

    /// <summary>
    /// This function resets the settings for all the section types to defaults.
    /// Returns Acad::eOk if successful. Otherwise, returns an AutoCAD error status.
    /// </summary>
    ACDB_PORT Acad::ErrorStatus reset(void);
    /// <summary>
    /// This function resets the settings for the specified section type to defaults.
    /// Returns Acad::eOk if successful. Otherwise, returns an AutoCAD error status.
    /// </summary>
    /// <param name="nSecType"> Input section type whose settings are to be reset </param>
    ACDB_PORT Acad::ErrorStatus reset(AcDbSectionSettings::SectionType nSecType);

    /// <summary>
    /// This function returns the current section type set in the section plane, expressed as an AcDbSectionSettings::SectionType enumerator.
    /// </summary>
    ACDB_PORT AcDbSectionSettings::SectionType currentSectionType(void) const;
    /// <summary>
    /// This function sets the current section type.
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput if the section type is invalid.
    /// </summary>
    /// <param name="nSecType"> Input section type to set as current </param>
    ACDB_PORT Acad::ErrorStatus setCurrentSectionType(AcDbSectionSettings::SectionType nSecType);
    
    /// <summary>
    /// This function returns the section generation options flag expressed as an Generation enumerator.
    /// </summary>
    /// <param name="nSecType"> Input section type for which the generation options object is to be returned </param>
    ACDB_PORT AcDbSectionSettings::Generation generationOptions(AcDbSectionSettings::SectionType nSecType) const;
    /// <summary>
    /// This function sets the generation options flag. This will overwrite all the current generation options.
    /// The options flag should contain one option from each of the following three groups of flags, combined using the OR operator:
    /// 
    /// Type of section: kGenerate2dSection or kGenerate3dSection 
    /// Source: kSourceAllObjects or kSourceSelectedObjects 
    /// Destination: kDestinationNewBlock, kDestinationReplaceBlock, or kDestinationFile 
    /// 
    /// Returns Acad::eOk if successful, or Acad::eInvalidInput if the flag is incorrect.
    /// 
    /// </summary>
    /// <param name="nSecType"> Input section type for which the generation options are to be set </param>
    /// <param name="nOptions"> Input options flag to set </param>
    ACDB_PORT Acad::ErrorStatus setGenerationOptions(AcDbSectionSettings::SectionType nSecType,
        AcDbSectionSettings::Generation nOptions);

    /// <summary>
    /// This function gets the source object IDs which are used to generate the section when the generation option is kSourceSelectedObjects.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type for which the source objects are to be returned </param>
    /// <param name="ids"> Output reference to an array to receive the object IDs </param>
    ACDB_PORT Acad::ErrorStatus getSourceObjects(AcDbSectionSettings::SectionType nSecType,
        AcDbObjectIdArray& ids) const;
    /// <summary>
    /// This function sets the source object IDs, which are used to generate a section when the generation option is kSourceSelectedObjects.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type for which the source objects are to be set </param>
    /// <param name="ids"> Input an array containing the object IDs </param>
    ACDB_PORT Acad::ErrorStatus setSourceObjects(AcDbSectionSettings::SectionType nSecType,
        const AcDbObjectIdArray& ids);
    
    /// <summary>
    /// Returns the ID of the block which will be replaced during section generation when the generation option is kDestinationReplaceBlock. Returns null if there is no destination block set.
    /// </summary>
    /// <param name="nSecType"> Input section type for which the destination block is to be returned  </param>
    ACDB_PORT AcDbObjectId destinationBlock(AcDbSectionSettings::SectionType nSecType) const;
    /// <summary>
    /// This function sets the block name that will be replaced during section generation when the generation option is kDestinationReplaceBlock.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type for which the destination block is to be set </param>
    /// <param name="ids"> Input ID of the block to be replaced during section generation </param>
    ACDB_PORT Acad::ErrorStatus setDestinationBlock(AcDbSectionSettings::SectionType nSecType,
        const AcDbObjectId& id);

    /// <summary>
    /// This function returns the output file name to which the generated section will be written when the generation option is kDestinationFile.
    /// </summary>
    /// <param name="nSecType"> Input section type for which the destination file is to be returned </param>
    ACDB_PORT const ACHAR* destinationFile(AcDbSectionSettings::SectionType nSecType) const;
    /// <summary>
    /// This function sets the output file name to which the generated section will be written when the generation option is kDestinationFile.
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type for which the destination file is to be set  </param>
    /// <param name="pszFileName"> Input destination file name  </param>
    ACDB_PORT Acad::ErrorStatus setDestinationFile(AcDbSectionSettings::SectionType nSecType,
        const ACHAR* pszFileName);

    /// <summary>
    /// This function returns true if the specified section geometry is visible, or false if it is not visible.
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input Geometry value </param>
    ACDB_PORT bool  visibility              (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the visibility of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="bVisible"> Input true to show the specified geometry, or false to hide it </param>
    ACDB_PORT Acad::ErrorStatus setVisibility(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bVisible);
    /// <summary>
    /// This function returns the color of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type
    /// kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type. </param>
    /// <param name="nGeometry"> Input geometry value.  </param>
    ACDB_PORT AcCmColor color               (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the color of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines. 
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="color"> Input color to set </param>
    ACDB_PORT Acad::ErrorStatus setColor    (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const AcCmColor& color);
    /// <summary>
    /// This function returns the layer name of the specified section geometry. 
    /// 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT const ACHAR* layer            (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the layer of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="pszLayer"> Input layer to set </param>
    ACDB_PORT Acad::ErrorStatus setLayer    (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const ACHAR* pszLayer);
    /// <summary>
    /// This function returns the linetype of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT const ACHAR* linetype         (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the linetype of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="pszLinetype"> Input linetype to set </param>
    ACDB_PORT Acad::ErrorStatus setLinetype (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const ACHAR* pszLinetype);
    /// <summary>
    /// This function returns the linetype scale of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT double linetypeScale          (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the linetype scale of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="fScale"> Input linetype scale to set </param>
    ACDB_PORT Acad::ErrorStatus setLinetypeScale(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fScale);
    /// <summary>
    /// This function returns the plot style name of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT const ACHAR* plotStyleName    (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the plot style of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="pszLinetype"> Input linetype to set </param>
    ACDB_PORT Acad::ErrorStatus setPlotStyleName(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             const ACHAR* pszPlotStyleName);
    /// <summary>
    /// This function returns the line weight of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT AcDb::LineWeight lineWeight   (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the line weight of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="nLineWeight"> Input line weight to set  </param>
    ACDB_PORT Acad::ErrorStatus setLineWeight(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             AcDb::LineWeight nLineWeight);
    /// <summary>
    /// This function returns the face transparency of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT int   faceTransparency        (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the face transparency of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="nTransparency"> Input face transparency to set, in the range 0-100 </param>
    ACDB_PORT Acad::ErrorStatus setFaceTransparency(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             int nTransparency);
    /// <summary>
    /// This function returns the edge transparency of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT int   edgeTransparency        (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the edge transparency of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// Returns Acad::eOk if successful 
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="nTransparency"> Input edge transparency to set, in the range 0-100  </param>
    ACDB_PORT Acad::ErrorStatus setEdgeTransparency(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             int nTransparency);
    /// <summary>
    /// This function returns the visibility of hatch in the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT bool  hatchVisibility         (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the hatch visibility of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// 
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="bVisible"> Input true to show hatch, or false to hide it </param>
    ACDB_PORT Acad::ErrorStatus setHatchVisibility(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bVisible);
    /// <summary>
    /// This function gets the hatch pattern type and pattern name of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="nPatternType"> Output reference to receive the hatch pattern type </param>
    /// <param name="pszPatternName"> Output reference to receive the hatch pattern name </param>
    ACDB_PORT Acad::ErrorStatus getHatchPattern(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             AcDbHatch::HatchPatternType& nPatternType, 
                                             const ACHAR*& pszPatternName) const;
    /// <summary>
    /// This function sets the hatch pattern of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="nPatternType"> Input hatch pattern type </param>
    /// <param name="pszPatternName"> Input hatch pattern name </param>
    ACDB_PORT Acad::ErrorStatus setHatchPattern(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             AcDbHatch::HatchPatternType nPatternType, 
                                             const ACHAR* pszPatternName);
    /// <summary>
    /// This function returns the hatch angle of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT double hatchAngle             (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the hatch angle of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="fAngle"> Input hatch angle </param>
    ACDB_PORT Acad::ErrorStatus setHatchAngle(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fAngle);
    /// <summary>
    /// This function returns the hatch spacing of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT double hatchSpacing           (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the hatch spacing of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// 
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="fSpacing"> Input hatch spacing  </param>
    ACDB_PORT Acad::ErrorStatus setHatchSpacing(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fSpacing);
    /// <summary>
    /// This function returns the hatch scale of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT double hatchScale             (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the hatch scale of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="fScale"> Input hatch scale </param>

    ACDB_PORT Acad::ErrorStatus setHatchScale(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             double fScale);
    /// <summary>
    /// This function returns the hidden line visibility of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT bool  hiddenLine              (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    /// This function sets the hidden line visibility of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="bHiddenLine"> Input true if hidden line is to be shown, or false if it is to be hidden </param>
    ACDB_PORT Acad::ErrorStatus setHiddenLine(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bHiddenLine);
    /// <summary>
    /// This function returns the visibility of division lines in the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    ACDB_PORT bool  divisionLines           (AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry) const;
    /// <summary>
    ///This function sets the division line visibility of the specified section geometry. 
    /// nGeometry should contain one flag from each of the following two groups of bit flags, combined with the OR operator:  
    /// Section type  kLiveSection, k2dSection, or k3dSection  
    /// Geometry type  kIntersectionBoundary, kIntersectionFill, kBackgroundGeometry, kForegroundGeometry, or kCurveTangencyLines.  
    /// Returns Acad::eOk if successful.
    /// </summary>
    /// <param name="nSecType"> Input section type </param>
    /// <param name="nGeometry"> Input geometry value </param>
    /// <param name="bShow"> Input true if division lines are to be shown, or false if they are to be hidden </param>

    ACDB_PORT Acad::ErrorStatus setDivisionLines(AcDbSectionSettings::SectionType nSecType, 
                                             AcDbSectionSettings::Geometry nGeometry, 
                                             bool bShow);

protected:
    ACDB_PORT virtual Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

// This overload is deprecated. Please use one of the other two overloads instead
inline Acad::ErrorStatus AcDbSection::getName (ACHAR*& pszName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbSection::getName, pszName);
}

