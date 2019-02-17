#ifndef AD_DBENTS_H
#define AD_DBENTS_H
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
//
//  DESCRIPTION: Exported pre-R13 Entity classes
//
//  AcRxObject
//    AcDbObject
//      AcDbEntity
//        AcDbText
//          AcDbAttribute
//          AcDbAttributeDefinition
//        AcDbBlockBegin
//        AcDbBlockEnd
//        AcDbSequenceEnd
//        AcDbBlockReference
//          AcDbMInsertBlock
//        AcDbVertex
//          AcDb2dVertex
//          AcDb3dPolylineVertex
//          AcDbPolygonMeshVertex
//          AcDbPolyFaceMeshVertex
//          AcDbFaceRecord
//        AcDbCurve
//          AcDb2dPolyline
//          AcDb3dPolyline
//          AcDbArc
//          AcDbCircle
//          AcDbLine
//        AcDbPoint
//        AcDbFace
//        AcDbPolyFaceMesh
//        AcDbPolygonMesh
//        AcDbTrace
//        AcDbSolid
//        AcDbShape
//        AcDbViewport
//

#include "dbmain.h"
#include "dbcurve.h"
#include "gescl3d.h"
#include "gepnt2d.h"
#include "dbmtext.h"
#include "dbbackground.h"
#include "dbdim.h"
#include "gept2dar.h"
#include "gedblar.h"
#include "dbsymtb.h"
#include "gemat3d.h"
#include "acdbxref.h"
#include "acgi.h"
#include "acgiviewport.h"
#include "acgivisualstyle.h"

#pragma pack(push, 8)

class AcDbAttribute;
class AcDbSequenceEnd;
class AcDb3dPolylineVertex;
class AcDb2dVertex;
class AcDbMText;
class AcDbAnnotationScale;


namespace Atil 
{
    class Image; // for Atil::Image
}

class AcDbText: public AcDbEntity
{
public:
    AcDbText();
    AcDbText(
        const AcGePoint3d&  position,
        const ACHAR*        text,
        AcDbObjectId        style = AcDbObjectId::kNull,
        double              height = 0,
        double              rotation = 0);
    ~AcDbText();
    ACDB_DECLARE_MEMBERS(AcDbText);

    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&);

    AcGePoint3d         alignmentPoint() const;
    Acad::ErrorStatus   setAlignmentPoint(const AcGePoint3d&);
    Adesk::Boolean      isDefaultAlignment() const;

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    virtual Adesk::Boolean    isPlanar() const override { return Adesk::kTrue; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const override;

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    double              oblique() const;
    Acad::ErrorStatus   setOblique(double);

    double              rotation() const; 
    Acad::ErrorStatus   setRotation(double);

    double              height() const; 
    Acad::ErrorStatus   setHeight(double);

    double              widthFactor() const; 
    Acad::ErrorStatus   setWidthFactor(double);

    ACDBCORE2D_PORT
    Acad::ErrorStatus   textString(AcString & sText) const;
    ACHAR*              textString() const;     // deprecated
    const ACHAR*        textStringConst() const;
    Acad::ErrorStatus   setTextString(const ACHAR*);
     
    AcDbObjectId        textStyle() const;
    Acad::ErrorStatus   setTextStyle(AcDbObjectId);
    
    Adesk::Boolean      isMirroredInX() const;
    Acad::ErrorStatus   mirrorInX(Adesk::Boolean);
     
    Adesk::Boolean      isMirroredInY() const;
    Acad::ErrorStatus   mirrorInY(Adesk::Boolean);
     
    AcDb::TextHorzMode  horizontalMode() const;
    Acad::ErrorStatus   setHorizontalMode(AcDb::TextHorzMode);
     
    AcDb::TextVertMode  verticalMode() const;
    Acad::ErrorStatus   setVerticalMode(AcDb::TextVertMode);

    int                 correctSpelling();

    virtual Acad::ErrorStatus   adjustAlignment(
        const AcDbDatabase* pDb = nullptr);

    Acad::ErrorStatus   setField(const ACHAR* pszPropName, AcDbField* pField,
                                 AcDbObjectId& fieldId) override;

    Acad::ErrorStatus   removeField(AcDbObjectId fieldId) override;
    Acad::ErrorStatus   removeField(const ACHAR* pszPropName, AcDbObjectId& returnId) override;
    Acad::ErrorStatus   removeField(const ACHAR* pszPropName) override;

    Acad::ErrorStatus   convertFieldToText();

    enum AcTextAlignment
    {
        kTextAlignmentLeft      = 0,
        kTextAlignmentCenter    = ( kTextAlignmentLeft + 1 ) ,
        kTextAlignmentRight     = ( kTextAlignmentCenter + 1 ) ,
        kTextAlignmentAligned   = ( kTextAlignmentRight + 1 ) ,
        kTextAlignmentMiddle    = ( kTextAlignmentAligned + 1 ) ,
        kTextAlignmentFit       = ( kTextAlignmentMiddle + 1 ) ,
        kTextAlignmentTopLeft   = ( kTextAlignmentFit + 1 ) ,
        kTextAlignmentTopCenter = ( kTextAlignmentTopLeft + 1 ) ,
        kTextAlignmentTopRight  = ( kTextAlignmentTopCenter + 1 ) ,
        kTextAlignmentMiddleLeft        = ( kTextAlignmentTopRight + 1 ) ,
        kTextAlignmentMiddleCenter      = ( kTextAlignmentMiddleLeft + 1 ) ,
        kTextAlignmentMiddleRight       = ( kTextAlignmentMiddleCenter + 1 ) ,
        kTextAlignmentBottomLeft        = ( kTextAlignmentMiddleRight + 1 ) ,
        kTextAlignmentBottomCenter      = ( kTextAlignmentBottomLeft + 1 ) ,
        kTextAlignmentBottomRight       = ( kTextAlignmentBottomCenter + 1 )
    };

    ACDBCORE2D_PORT AcTextAlignment              justification() const;
    ACDBCORE2D_PORT Acad::ErrorStatus            setJustification(AcTextAlignment);

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

// This overload is deprecated. It allocates a char buffer that the caller is
// responsible for freeing. Please use the other overload, taking an (AcString &) arg
inline ACHAR * AcDbText::textString() const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbText::textString);
}

class AcDbAttributeDefinition: public AcDbText
{
public:
    AcDbAttributeDefinition();
    AcDbAttributeDefinition(
        const AcGePoint3d& position,
        const ACHAR*       text,
        const ACHAR*       tag,
        const ACHAR*       prompt,
        AcDbObjectId       style = AcDbObjectId::kNull);
    ~AcDbAttributeDefinition();
    ACDB_DECLARE_MEMBERS(AcDbAttributeDefinition);

    ACDBCORE2D_PORT
    Acad::ErrorStatus   prompt(AcString & sTag) const;
    ACHAR*              prompt() const; // deprecated
    const ACHAR*        promptConst() const;
    Acad::ErrorStatus   setPrompt(const ACHAR*);
     
    ACDBCORE2D_PORT
    Acad::ErrorStatus   tag(AcString & sTag) const;
    ACHAR*              tag() const;    // deprecated
    const ACHAR*        tagConst() const;
    Acad::ErrorStatus   setTag(const ACHAR*);
 
    Adesk::Boolean      isInvisible() const;
    Acad::ErrorStatus   setInvisible(Adesk::Boolean);
 
    Adesk::Boolean      isConstant() const;
    Acad::ErrorStatus   setConstant(Adesk::Boolean);
 
    Adesk::Boolean      isVerifiable() const;
    Acad::ErrorStatus   setVerifiable(Adesk::Boolean);
 
    Adesk::Boolean      isPreset() const;
    Acad::ErrorStatus   setPreset(Adesk::Boolean);
     
    Adesk::UInt16       fieldLength() const;
    Acad::ErrorStatus   setFieldLength(Adesk::UInt16);

    virtual Acad::ErrorStatus   adjustAlignment(
        const AcDbDatabase* pDb = nullptr) override;
 
    bool lockPositionInBlock() const;
    Acad::ErrorStatus setLockPositionInBlock(bool bValue);

    // multiline attribute definition support
    bool              isMTextAttributeDefinition          () const;
    AcDbMText *       getMTextAttributeDefinition         () const;
    const AcDbMText * getMTextAttributeDefinitionConst    () const;
    Acad::ErrorStatus setMTextAttributeDefinition         (AcDbMText*);
    ACDBCORE2D_PORT Acad::ErrorStatus setMTextAttributeDefinitionConst(const AcDbMText*);
    Acad::ErrorStatus convertIntoMTextAttributeDefinition (Adesk::Boolean val = Adesk::kTrue);
    Acad::ErrorStatus updateMTextAttributeDefinition      ();

protected:
   virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

// This overload is deprecated. It allocates a char buffer that the caller is
// responsible for freeing. Please use the other overload, taking an (AcString &) arg
inline ACHAR * AcDbAttributeDefinition::prompt() const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbAttributeDefinition::prompt);
}

// This overload is deprecated. It allocates a char buffer that the caller is
// responsible for freeing. Please use the other overload, taking an (AcString &) arg
inline ACHAR * AcDbAttributeDefinition::tag() const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbAttributeDefinition::tag);
}

class AcDbAttribute: public AcDbText
{
public:
    AcDbAttribute();
    AcDbAttribute(
        const AcGePoint3d& position,
        const ACHAR*       text,
        const ACHAR*       tag,
        AcDbObjectId       style = AcDbObjectId::kNull);
    ~AcDbAttribute();
    ACDB_DECLARE_MEMBERS(AcDbAttribute);

    ACDBCORE2D_PORT
    Acad::ErrorStatus   tag(AcString & sTag) const;
    ACHAR*              tag() const;    // deprecated
    const ACHAR*        tagConst() const;
    Acad::ErrorStatus   setTag(const ACHAR* newTag);

    Adesk::Boolean      isInvisible() const;
    Acad::ErrorStatus   setInvisible(Adesk::Boolean);

    Adesk::Boolean      isConstant() const;
    Adesk::Boolean      isVerifiable() const;
    Adesk::Boolean      isPreset() const;

    Adesk::UInt16       fieldLength() const;
    Acad::ErrorStatus   setFieldLength(Adesk::UInt16);

    Acad::ErrorStatus setAttributeFromBlock(const AcGeMatrix3d& blkXform);
    Acad::ErrorStatus setAttributeFromBlock(
        const AcDbAttributeDefinition *pAttdef,
        const AcGeMatrix3d& blkXform);

    bool lockPositionInBlock() const;
    Acad::ErrorStatus setLockPositionInBlock(bool bValue);

    // multiline attribute support
    bool              isMTextAttribute          ()                        const;
    AcDbMText *       getMTextAttribute         ()                        const;
    const AcDbMText * getMTextAttributeConst    ()                        const;
    Acad::ErrorStatus setMTextAttribute         (AcDbMText *);
    ACDBCORE2D_PORT Acad::ErrorStatus setMTextAttributeConst(const AcDbMText *);
    Acad::ErrorStatus convertIntoMTextAttribute (Adesk::Boolean val = Adesk::kTrue);
    Acad::ErrorStatus updateMTextAttribute      ();
    bool              isReallyLocked            ()                        const;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

// This overload is deprecated. It allocates a char buffer that the caller is
// responsible for freeing. Please use the other overload, taking an (AcString &) arg
inline ACHAR * AcDbAttribute::tag() const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbAttribute::tag);
}

class AcDbBlockReference: public AcDbEntity
{
public:
            AcDbBlockReference();
            AcDbBlockReference(const AcGePoint3d&  position,
                                     AcDbObjectId  blockTableRec);
            ~AcDbBlockReference();
    ACDB_DECLARE_MEMBERS(AcDbBlockReference);

            AcDbObjectId      blockTableRecord() const;
    virtual Acad::ErrorStatus setBlockTableRecord(AcDbObjectId);

    virtual AcGePoint3d       position() const;
    virtual Acad::ErrorStatus setPosition(const AcGePoint3d&);

            AcGeScale3d       scaleFactors() const;
            AcGeScale3d       nonAnnotationScaleFactors() const;
    virtual Acad::ErrorStatus setScaleFactors(const AcGeScale3d& scale);
 
            double            rotation() const;
    virtual Acad::ErrorStatus setRotation(double newVal);
 
            AcGeVector3d      normal() const;
    virtual Acad::ErrorStatus setNormal(const AcGeVector3d& newVal);

    virtual Adesk::Boolean    isPlanar() const override { return Adesk::kTrue; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const override;

            AcGeMatrix3d      blockTransform() const;
            AcGeMatrix3d      nonAnnotationBlockTransform() const;
    virtual Acad::ErrorStatus setBlockTransform(const AcGeMatrix3d&);

            Acad::ErrorStatus appendAttribute(AcDbAttribute*);
            Acad::ErrorStatus appendAttribute(AcDbObjectId&, AcDbAttribute*);

            Acad::ErrorStatus openAttribute(AcDbAttribute*&, AcDbObjectId,
                                            AcDb::OpenMode,
                                            bool openErasedOne = false);

            Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

            AcDbObjectIterator*  attributeIterator() const;

    virtual Adesk::Boolean    treatAsAcDbBlockRefForExplode() const;

            Acad::ErrorStatus geomExtentsBestFit( 
                                        AcDbExtents& extents, 
                                        const AcGeMatrix3d& parentXform = 
                                            AcGeMatrix3d::kIdentity) const;

    virtual Acad::ErrorStatus explodeToOwnerSpace() const;


protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbMInsertBlock: public AcDbBlockReference
{
public:
    AcDbMInsertBlock();
    AcDbMInsertBlock(
        const AcGePoint3d&  position,
        AcDbObjectId        blockTableRec,
        Adesk::UInt16       columns,
        Adesk::UInt16       rows,
        double              colSpacing,
        double              rowSpacing);
    ~AcDbMInsertBlock();
    ACDB_DECLARE_MEMBERS(AcDbMInsertBlock);

    Adesk::UInt16      columns() const;
    Acad::ErrorStatus  setColumns(Adesk::UInt16);
 
    Adesk::UInt16      rows() const;
    Acad::ErrorStatus  setRows(Adesk::UInt16);
 
    double             columnSpacing() const;
    Acad::ErrorStatus  setColumnSpacing(double);
 
    double             rowSpacing() const;
    Acad::ErrorStatus  setRowSpacing(double);

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbBlockBegin: public AcDbEntity
{
public:
    AcDbBlockBegin();
    ~AcDbBlockBegin();
    ACDB_DECLARE_MEMBERS(AcDbBlockBegin);

};

class AcDbBlockEnd: public AcDbEntity
{
public:
    AcDbBlockEnd();
    ~AcDbBlockEnd();
    ACDB_DECLARE_MEMBERS(AcDbBlockEnd);
};

class AcDbSequenceEnd: public AcDbEntity
{
public:
    AcDbSequenceEnd();
    ~AcDbSequenceEnd();
    ACDB_DECLARE_MEMBERS(AcDbSequenceEnd);
};

class AcDbVertex: public AcDbEntity
{
public:
    AcDbVertex();
    ~AcDbVertex();
    ACDB_DECLARE_MEMBERS(AcDbVertex);
};

// Inline for performance, because derived classes' dtors
// call this explicitly.
//
inline AcDbVertex::~AcDbVertex()
{
}

class AcDb2dVertex: public AcDbVertex
{
public:
    AcDb2dVertex();
    ~AcDb2dVertex();
    ACDB_DECLARE_MEMBERS(AcDb2dVertex);
    AcDb2dVertex(
        const AcGePoint3d&  position,
        double   bulge      = 0,
        double   startWidth = 0,
        double   endWidth   = 0,
        double   tangent    = 0,
        Adesk::Int32 vertexIdentifier = 0);

    AcDb::Vertex2dType vertexType() const;


    // This method accesses the position in ECS.  See AcDb2dPolyline for WCS.
    //
    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

    double              startWidth() const; 
    Acad::ErrorStatus   setStartWidth(double newVal);

    double              endWidth() const; 
    Acad::ErrorStatus   setEndWidth(double newVal);

    double              bulge() const; 
    Acad::ErrorStatus   setBulge(double newVal);

    Adesk::Boolean      isTangentUsed() const;
    Acad::ErrorStatus   useTangent();
    Acad::ErrorStatus   ignoreTangent();
    ACDBCORE2D_PORT Acad::ErrorStatus   setTangentUsed(Adesk::Boolean);

    double              tangent() const; 
    Acad::ErrorStatus   setTangent(double newVal);

    Acad::ErrorStatus  setVertexIdentifier(Adesk::Int32 suggestedValue);
    int                   vertexIdentifier() const;

};

class AcDb3dPolylineVertex: public AcDbVertex
{
public:
    AcDb3dPolylineVertex();
    ~AcDb3dPolylineVertex();
    ACDB_DECLARE_MEMBERS(AcDb3dPolylineVertex);
    AcDb3dPolylineVertex(const AcGePoint3d&);

    AcDb::Vertex3dType vertexType() const;


    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

};

class AcDbPolygonMeshVertex: public AcDbVertex
{
public:
    AcDbPolygonMeshVertex();
    AcDbPolygonMeshVertex(const AcGePoint3d&  position);
    ~AcDbPolygonMeshVertex();
    ACDB_DECLARE_MEMBERS(AcDbPolygonMeshVertex);

    AcDb::Vertex3dType vertexType() const;

    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

};

class AcDbPolyFaceMeshVertex: public AcDbVertex
{
public:
    AcDbPolyFaceMeshVertex();
    AcDbPolyFaceMeshVertex(const AcGePoint3d&  position);
    ~AcDbPolyFaceMeshVertex();
    ACDB_DECLARE_MEMBERS(AcDbPolyFaceMeshVertex);

    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 

};

class AcDbFaceRecord: public AcDbVertex
{
public:
    AcDbFaceRecord();
    // Use negative values to indicate invisible faces
    AcDbFaceRecord(Adesk::Int16 vtx0, Adesk::Int16 vtx1,
                   Adesk::Int16 vtx2, Adesk::Int16 vtx3);
    ~AcDbFaceRecord();
    ACDB_DECLARE_MEMBERS(AcDbFaceRecord);

    // Input index must be 0-3.
    //
    Acad::ErrorStatus getVertexAt(Adesk::UInt16 faceIdx,
                                  Adesk::Int16& vtxIdx) const;
    Acad::ErrorStatus setVertexAt(Adesk::UInt16 faceIdx,
                                  Adesk::Int16  vtxIdx);

    Acad::ErrorStatus isEdgeVisibleAt(Adesk::UInt16 faceIndex,
                                      Adesk::Boolean& visible) const;

    Acad::ErrorStatus makeEdgeVisibleAt(Adesk::UInt16 faceIndex);
    Acad::ErrorStatus makeEdgeInvisibleAt(Adesk::UInt16 faceIndex);
};

class AcDb2dPolyline: public AcDbCurve
{
public:
    AcDb2dPolyline();
    ~AcDb2dPolyline();
    ACDB_DECLARE_MEMBERS(AcDb2dPolyline);
    AcDb2dPolyline (
        AcDb::Poly2dType  type,
        AcGePoint3dArray& vertices,
        double            elevation     = 0,
        Adesk::Boolean    closed        = Adesk::kFalse,
        double            defStartWidth = 0,
        double            defEndWidth   = 0,
        AcGeDoubleArray*  bulges        = nullptr,
        AcArray<Adesk::Int32>* vertexIdentifiers = nullptr
        );

    DBCURVE_METHODS

    AcDb::Poly2dType    polyType() const;
    Acad::ErrorStatus   setPolyType(AcDb::Poly2dType);
    Acad::ErrorStatus   convertToPolyType(AcDb::Poly2dType newVal);

    Acad::ErrorStatus              makeClosed();
    Acad::ErrorStatus              makeOpen();
    ACDBCORE2D_PORT Acad::ErrorStatus    setClosed(Adesk::Boolean);
    ACDBCORE2D_PORT Acad::ErrorStatus    constantWidth(double&) const;
    ACDBCORE2D_PORT Acad::ErrorStatus    setConstantWidth(double);
    ACDBCORE2D_PORT Acad::ErrorStatus    length(double &) const;

    double              defaultStartWidth() const;
    Acad::ErrorStatus   setDefaultStartWidth(double);

    double              defaultEndWidth() const;
    Acad::ErrorStatus   setDefaultEndWidth(double);

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    double              elevation() const;
    Acad::ErrorStatus   setElevation(double);

    Adesk::Boolean      isLinetypeGenerationOn() const;
    Acad::ErrorStatus   setLinetypeGenerationOn();
    Acad::ErrorStatus   setLinetypeGenerationOff();
    Acad::ErrorStatus   ACDBCORE2D_PORT setLinetypeGenerationOn(Adesk::Boolean bOn);

    Acad::ErrorStatus   straighten();
    Acad::ErrorStatus   splineFit();
    Acad::ErrorStatus   splineFit(AcDb::Poly2dType splineType,
                                  Adesk::Int16   splineSegs);
    Acad::ErrorStatus   curveFit();

    // Vertex access
    //
    Acad::ErrorStatus appendVertex(AcDb2dVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDb2dVertex*);

    Acad::ErrorStatus insertVertexAt(const AcDb2dVertex* pIndexVert,
        AcDb2dVertex* pNewVertex); 
    Acad::ErrorStatus insertVertexAt(AcDbObjectId& newVertId,
        const AcDbObjectId& indexVertId, AcDb2dVertex* pNewVertex);
    
    Acad::ErrorStatus openVertex(AcDb2dVertex*&, AcDbObjectId    vertId,
                                 AcDb::OpenMode,
                                 bool openErasedOne = false) const;
    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator*  vertexIterator() const;

    // Vertex position in WCS
    //
    AcGePoint3d       vertexPosition(const AcDb2dVertex& vert) const;

    // Does nothing and returns Acad::eOk if already closed or the start and end 
    // vertices do not coincide
    //
    ACDBCORE2D_PORT Acad::ErrorStatus makeClosedIfStartAndEndVertexCoincide(double distTol);

protected:
    // AcDbEntity overrides
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

inline Adesk::Boolean AcDb2dPolyline::isPeriodic() const
{
    return Adesk::kFalse;
}


inline Adesk::Boolean AcDb2dPolyline::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDb2dPolyline::getStartParam(double& param) const
{
    param = 0.0;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDb2dPolyline::extend (double param)
{
    param;      // avoid unreferenced formal parameter warning
    return Acad::eNotApplicable;
}


class AcDb3dPolyline: public AcDbCurve
{
public:
    AcDb3dPolyline();
    ~AcDb3dPolyline();
    ACDB_DECLARE_MEMBERS(AcDb3dPolyline);
    AcDb3dPolyline(AcDb::Poly3dType, AcGePoint3dArray& vertices,
                   Adesk::Boolean closed = Adesk::kFalse);

    DBCURVE_METHODS

    ACDBCORE2D_PORT Acad::ErrorStatus     length(double &) const;
    ACDBCORE2D_PORT Acad::ErrorStatus     setClosed(Adesk::Boolean);
    Acad::ErrorStatus               makeClosed();
    Acad::ErrorStatus               makeOpen();
 
    AcDb::Poly3dType    polyType() const;
    Acad::ErrorStatus   setPolyType(AcDb::Poly3dType);
    Acad::ErrorStatus   convertToPolyType(AcDb::Poly3dType newVal);

    Acad::ErrorStatus   straighten();
    Acad::ErrorStatus   splineFit();
    Acad::ErrorStatus   splineFit(AcDb::Poly3dType splineType,
                                  Adesk::Int16   splineSegs);

    // Vertex access
    //
    Acad::ErrorStatus appendVertex(AcDb3dPolylineVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDb3dPolylineVertex*);

    Acad::ErrorStatus insertVertexAt(const AcDb3dPolylineVertex* pIndexVert,
        AcDb3dPolylineVertex* pNewVertex); 
    Acad::ErrorStatus insertVertexAt(AcDbObjectId& newVertId,
        const AcDbObjectId& indexVertId, AcDb3dPolylineVertex* pNewVertex);
    
    Acad::ErrorStatus openVertex(AcDb3dPolylineVertex*&, AcDbObjectId vertId,
                                 AcDb::OpenMode,
                                 bool openErasedOne = false);

    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator* vertexIterator() const;

protected:
    // AcDbEntity overrides
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};


inline Adesk::Boolean    AcDb3dPolyline::isPeriodic   () const
{
    return Adesk::kFalse;
}

inline Acad::ErrorStatus AcDb3dPolyline::getStartParam(double& param) const
{
    param = 0.0;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDb3dPolyline::extend(double newparam)
{
    newparam;   // avoid unreferenced formal parameter warning
    // extending a pline based on a parameter is not supported.
    return Acad::eNotApplicable;
}


class AcDbArc: public AcDbCurve
{
public:
    AcDbArc();
    AcDbArc(const AcGePoint3d& center, double radius,
            double startAngle, double endAngle);
    AcDbArc(const AcGePoint3d& center, const AcGeVector3d& normal,
            double radius, double startAngle, double endAngle);
    ~AcDbArc();
    ACDB_DECLARE_MEMBERS(AcDbArc);

    DBCURVE_METHODS

    AcGePoint3d         center() const;
    Acad::ErrorStatus   setCenter(const AcGePoint3d&); 

    double              radius() const;
    Acad::ErrorStatus   setRadius(double);

    double              startAngle() const;
    Acad::ErrorStatus   setStartAngle(double);

    double              endAngle() const;
    Acad::ErrorStatus   setEndAngle(double);

    ACDBCORE2D_PORT double    totalAngle() const;

    ACDBCORE2D_PORT double    length() const;

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

inline Adesk::Boolean AcDbArc::isClosed() const
{
    return Adesk::kFalse;
}
inline Adesk::Boolean AcDbArc::isPeriodic() const
{
    return Adesk::kFalse;
}
inline Adesk::Boolean AcDbArc::isPlanar() const
{
    return Adesk::kTrue;
}

class AcDbCircle: public AcDbCurve
{
public:
    AcDbCircle();
    AcDbCircle(const AcGePoint3d& cntr, const AcGeVector3d& nrm, double radius);
    ~AcDbCircle();
    ACDB_DECLARE_MEMBERS(AcDbCircle);

    DBCURVE_METHODS



    AcGePoint3d         center() const;
    Acad::ErrorStatus   setCenter(const AcGePoint3d&); 

    double              radius() const;
    Acad::ErrorStatus   setRadius(double);

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    double              circumference() const;
    Acad::ErrorStatus   setCircumference(double);
    double              diameter() const;
    Acad::ErrorStatus   setDiameter(double);

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

inline Adesk::Boolean AcDbCircle::isClosed() const      
{
    return Adesk::kTrue;
}

inline Adesk::Boolean AcDbCircle::isPeriodic() const      
{
    return Adesk::kTrue;
}

inline Adesk::Boolean AcDbCircle::isPlanar () const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbCircle::getStartParam(double& p) const
{
    p = 0.0;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDbCircle::extend(double)
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbCircle::extend(Adesk::Boolean, const AcGePoint3d&)
{
    return Acad::eNotApplicable;
}



class AcDbLine: public AcDbCurve
{
public:
    AcDbLine();
    AcDbLine(const AcGePoint3d& start, const AcGePoint3d& end);
    ~AcDbLine();
    ACDB_DECLARE_MEMBERS(AcDbLine);
 
    DBCURVE_METHODS

    Acad::ErrorStatus getOffsetCurvesGivenPlaneNormal(
        const AcGeVector3d& normal, double offsetDist,
        AcDbVoidPtrArray& offsetCurves) const override;
    
    AcGePoint3d         startPoint() const;
    Acad::ErrorStatus   setStartPoint(const AcGePoint3d&); 

    AcGePoint3d         endPoint() const;
    Acad::ErrorStatus   setEndPoint(const AcGePoint3d&); 

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

inline Adesk::Boolean AcDbLine::isClosed() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbLine::isPeriodic() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbLine::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbLine::getStartParam(double& v1) const
{
    v1 = 0.0;
    return Acad::eOk;
}


class AcDbPoint: public AcDbEntity
{
public:
    AcDbPoint();
    AcDbPoint(const AcGePoint3d&   position);
    ~AcDbPoint();
    ACDB_DECLARE_MEMBERS(AcDbPoint);

    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&);

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    double              ecsRotation() const;
    Acad::ErrorStatus   setEcsRotation(double);

    // AcDbEntity overrides
    virtual Adesk::Boolean    isPlanar() const override { return Adesk::kTrue; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const override;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbFace: public AcDbEntity
{
public:                
    AcDbFace();
    AcDbFace(const AcGePoint3d&   pt0,
             const AcGePoint3d&   pt1,
             const AcGePoint3d&   pt2,
             const AcGePoint3d&   pt3,
                   Adesk::Boolean e0vis = Adesk::kTrue,
                   Adesk::Boolean e1vis = Adesk::kTrue,
                   Adesk::Boolean e2vis = Adesk::kTrue,
                   Adesk::Boolean e3vis = Adesk::kTrue);
    AcDbFace(const AcGePoint3d&   pt0,
             const AcGePoint3d&   pt1,
             const AcGePoint3d&   pt2,
                   Adesk::Boolean e0vis = Adesk::kTrue,
                   Adesk::Boolean e1vis = Adesk::kTrue,
                   Adesk::Boolean e2vis = Adesk::kTrue,
                   Adesk::Boolean e3vis = Adesk::kTrue);
    ~AcDbFace();
    ACDB_DECLARE_MEMBERS(AcDbFace);

    Acad::ErrorStatus getVertexAt(Adesk::UInt16, AcGePoint3d&) const;
    Acad::ErrorStatus setVertexAt(Adesk::UInt16, const AcGePoint3d&);

    Acad::ErrorStatus isEdgeVisibleAt(Adesk::UInt16, Adesk::Boolean&) const;
    Acad::ErrorStatus makeEdgeVisibleAt(Adesk::UInt16);
    Acad::ErrorStatus makeEdgeInvisibleAt(Adesk::UInt16);
    
    ACDBCORE2D_PORT virtual Adesk::Boolean      isPlanar() const override;
    ACDBCORE2D_PORT virtual Acad::ErrorStatus   getPlane(AcGePlane& plane, AcDb::Planarity& planarity) const override;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbPolyFaceMesh: public AcDbEntity
{
public:
    AcDbPolyFaceMesh();
    ~AcDbPolyFaceMesh();
    ACDB_DECLARE_MEMBERS(AcDbPolyFaceMesh);

    Adesk::Int16 numVertices() const;
    Adesk::Int16 numFaces() const;

    Acad::ErrorStatus appendVertex(AcDbPolyFaceMeshVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDbPolyFaceMeshVertex*);

    Acad::ErrorStatus appendFaceRecord(AcDbFaceRecord*);
    Acad::ErrorStatus appendFaceRecord(AcDbObjectId&, AcDbFaceRecord*);

    Acad::ErrorStatus openVertex(AcDbVertex*&, AcDbObjectId subObjId,
                                 AcDb::OpenMode,
                                 bool openErasedOne = false);

    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator*  vertexIterator() const;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbPolygonMesh: public AcDbEntity
{
public:
    AcDbPolygonMesh();
    AcDbPolygonMesh(AcDb::PolyMeshType pType,
                    Adesk::Int16       mSize,
                    Adesk::Int16       nSize,
                    const AcGePoint3dArray& vertices,
                    Adesk::Boolean     mClosed = Adesk::kTrue,
                    Adesk::Boolean     nClosed = Adesk::kTrue);
    ~AcDbPolygonMesh();
    ACDB_DECLARE_MEMBERS(AcDbPolygonMesh);

    AcDb::PolyMeshType  polyMeshType() const;
    Acad::ErrorStatus   setPolyMeshType(AcDb::PolyMeshType);
    Acad::ErrorStatus   convertToPolyMeshType(AcDb::PolyMeshType newVal);

    Adesk::Int16        mSize() const;
    Acad::ErrorStatus   setMSize(Adesk::Int16);

    Adesk::Int16        nSize() const;
    Acad::ErrorStatus   setNSize(Adesk::Int16);
 
    Adesk::Boolean      isMClosed() const;
    Acad::ErrorStatus   makeMClosed();
    Acad::ErrorStatus   makeMOpen();
 
    Adesk::Boolean      isNClosed() const;
    Acad::ErrorStatus   makeNClosed();
    Acad::ErrorStatus   makeNOpen();
 
    Adesk::Int16        mSurfaceDensity() const;
    Acad::ErrorStatus   setMSurfaceDensity(Adesk::Int16);

    Adesk::Int16        nSurfaceDensity() const;
    Acad::ErrorStatus   setNSurfaceDensity(Adesk::Int16);

    Acad::ErrorStatus   straighten();
    Acad::ErrorStatus   surfaceFit();
    Acad::ErrorStatus   surfaceFit(AcDb::PolyMeshType surfType,
                                   Adesk::Int16 surfu, Adesk::Int16 surfv);

    // Vertex access
    //
    Acad::ErrorStatus appendVertex(AcDbPolygonMeshVertex*);
    Acad::ErrorStatus appendVertex(AcDbObjectId& objId, AcDbPolygonMeshVertex*);

    Acad::ErrorStatus openVertex(AcDbPolygonMeshVertex*&, AcDbObjectId vertId,
                                 AcDb::OpenMode,
                                 bool openErasedOne = false);

    Acad::ErrorStatus openSequenceEnd(AcDbSequenceEnd*&, AcDb::OpenMode);

    AcDbObjectIterator*  vertexIterator() const;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbSolid: public AcDbEntity
{
public:
    AcDbSolid();
    AcDbSolid(const AcGePoint3d&    pt0,
              const AcGePoint3d&    pt1,
              const AcGePoint3d&    pt2,
              const AcGePoint3d&    pt3);
    AcDbSolid(const AcGePoint3d&    pt0,
              const AcGePoint3d&    pt1,
              const AcGePoint3d&    pt2);
    ~AcDbSolid();
    ACDB_DECLARE_MEMBERS(AcDbSolid);

    Acad::ErrorStatus getPointAt(Adesk::UInt16 idx, AcGePoint3d& pntRes) const;
    Acad::ErrorStatus setPointAt(Adesk::UInt16 idx, const AcGePoint3d&);

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    double              elevation() const;
    void                setElevation(double);

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbTrace: public AcDbEntity
{
public:
    AcDbTrace();
    AcDbTrace(const AcGePoint3d&    pt0,
              const AcGePoint3d&    pt1,
              const AcGePoint3d&    pt2,
              const AcGePoint3d&    pt3);
    ~AcDbTrace();
    ACDB_DECLARE_MEMBERS(AcDbTrace);

    // returns eInvalidIndex if index is out of range
    Acad::ErrorStatus getPointAt(Adesk::UInt16 idx, AcGePoint3d& PntRes) const;
    Acad::ErrorStatus setPointAt(Adesk::UInt16 idx, const AcGePoint3d&);

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    double              elevation() const;
    void                setElevation(double);

    virtual Adesk::Boolean    isPlanar() const override { return Adesk::kTrue; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const override;

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

class AcDbShape: public AcDbEntity
{
public:
    AcDbShape();
    AcDbShape(const AcGePoint3d&  position,
                    double        size,
                    double        rotation    = 0,
                    double        widthFactor = 0);
    ~AcDbShape();
    ACDB_DECLARE_MEMBERS(AcDbShape);

    AcGePoint3d         position() const;
    Acad::ErrorStatus   setPosition(const AcGePoint3d&); 
    
    double              size() const;
    Acad::ErrorStatus   setSize(double);
    
    ACDBCORE2D_PORT
    Acad::ErrorStatus   name(AcString &sName) const;
    ACHAR*              name() const;   // deprecated
    Acad::ErrorStatus   setName(const ACHAR*); 
    
    double              rotation() const;
    Acad::ErrorStatus   setRotation(double);
    
    double              widthFactor() const;
    Acad::ErrorStatus   setWidthFactor(double);
    
    double              oblique() const;
    Acad::ErrorStatus   setOblique(double);

    double              thickness() const;
    Acad::ErrorStatus   setThickness(double);

    AcGeVector3d        normal() const;
    Acad::ErrorStatus   setNormal(const AcGeVector3d&);

    virtual Adesk::Boolean    isPlanar() const override { return Adesk::kTrue; }
    virtual Acad::ErrorStatus getPlane(AcGePlane&, AcDb::Planarity&) const override;

    Adesk::Int16      shapeNumber() const;
    Acad::ErrorStatus setShapeNumber(Adesk::Int16);
 
    AcDbObjectId        styleId() const;
    Acad::ErrorStatus   setStyleId(AcDbObjectId id);

    // Obsolete names for the "shape style id" get/set methods:
    AcDbObjectId        shapeIndex() const { return this->styleId(); }
    Acad::ErrorStatus   setShapeIndex(AcDbObjectId id)
                                 { return this->setStyleId(id); }

protected:
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

// This overload returns a buffer which the caller is responsible for freeing.
// It will be removed soon. Please use the overload taking (AcString &) arg
//
inline ACHAR * AcDbShape::name() const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbShape::name);
}

typedef struct tagBITMAPINFO BITMAPINFO;

class AcDbViewport: public AcDbEntity
{
public:
                      AcDbViewport();
                      ~AcDbViewport();
    ACDB_DECLARE_MEMBERS(AcDbViewport);

    // view association

    Acad::ErrorStatus setModelView      (const AcDbXrefObjectId &xrefObjId);
    Acad::ErrorStatus getModelView      (AcDbXrefObjectId &xrefObjId) const;
    Acad::ErrorStatus removeModelView   (void);

    Acad::ErrorStatus setSheetView      (AcDbObjectId objId);
    Acad::ErrorStatus getSheetView      (AcDbObjectId &objId)const;
    Acad::ErrorStatus removeSheetView   (void);

    Acad::ErrorStatus setLabelBlock     (AcDbObjectId objId);
    Acad::ErrorStatus getLabelBlock     (AcDbObjectId &objId)const;
    Acad::ErrorStatus removeLabelBlock  (void);

    Acad::ErrorStatus syncModelView     (void);

    // Thumbnails

    /// <summary>
    /// This function provides BITMAP thumbnail of viewport as output
    /// </summary>
    /// <param name="thumbnail"> A reference to a pointer of Bitmap thumbnail, containing header and pixels </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    ///
    Acad::ErrorStatus getThumbnail (BITMAPINFO*& thumbnail) const;

    /// <summary>
    /// This function sets BITMAP thumbnail into viewport
    /// </summary>
    /// <param name="thumbnail"> A pointer of Bitmap thumbnail to be set into viewport </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    ///
    Acad::ErrorStatus setThumbnail(const BITMAPINFO * thumbnail);

    /// <summary>
    /// This function provides Atil::Image thumbnail of viewport as output
    /// </summary>
    /// <param name="pPreviewImage"> A reference to the pointer of Atil::Image thumbnail </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully retrieved. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus getPreviewImage(Atil::Image*& pPreviewImage) const;

    /// <summary>
    /// This functions sets Atil::Image thumbnail into viewport
    /// </summary>
    /// <param name="pPreviewImage"> A pointer of Atil::Image thumbnail to be set into viewport </param>
    /// <returns> This will return Acad::eOk if thumbnail is successfully set. It returns error status otherwise </returns>
    /// <remarks> Internal use only </remarks>
    ///
    Acad::ErrorStatus setPreviewImage (const Atil::Image * pPreviewImage);

    // Set methods will return eCannotChangeActiveViewport if called
    // when the Viewport is currently active.  

    double            height() const;
    Acad::ErrorStatus setHeight(double);

    double            width() const;
    Acad::ErrorStatus setWidth(double);

    AcGePoint3d       centerPoint() const;
    Acad::ErrorStatus setCenterPoint(const AcGePoint3d&);

    Adesk::Int16      number() const;

    bool              isOn() const;
    Acad::ErrorStatus setOn();
    Acad::ErrorStatus setOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setIsOn(bool bOn);

    AcGePoint3d       viewTarget() const;
    Acad::ErrorStatus setViewTarget(const AcGePoint3d&); 

    AcGeVector3d      viewDirection() const;
    Acad::ErrorStatus setViewDirection(const AcGeVector3d&);

    // Model Space height, and center in Display coordinates
    //
    double            viewHeight() const;
    Acad::ErrorStatus setViewHeight(double ht);

    AcGePoint2d       viewCenter() const;
    Acad::ErrorStatus setViewCenter(const AcGePoint2d& pt);

    double            twistAngle() const;
    Acad::ErrorStatus setTwistAngle(double);

    double            lensLength() const;
    Acad::ErrorStatus setLensLength(double);

    bool              isFrontClipOn() const;
    Acad::ErrorStatus setFrontClipOn();
    Acad::ErrorStatus setFrontClipOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setFrontClipOn(bool bOn);

    bool              isBackClipOn() const;
    Acad::ErrorStatus setBackClipOn();
    Acad::ErrorStatus setBackClipOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setBackClipOn(bool bOn);

    bool              isFrontClipAtEyeOn() const;
    Acad::ErrorStatus setFrontClipAtEyeOn();
    Acad::ErrorStatus setFrontClipAtEyeOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setFrontClipAtEyeOn(bool bOn);

    // FrontZ 
    double            frontClipDistance() const;
    Acad::ErrorStatus setFrontClipDistance(double newVal);

    // BackZ 
    double            backClipDistance() const;
    Acad::ErrorStatus setBackClipDistance(double newVal);

    bool              isPerspectiveOn() const;
    Acad::ErrorStatus setPerspectiveOn();
    Acad::ErrorStatus setPerspectiveOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setPerspectiveOn(bool bOn);

    bool              isUcsFollowModeOn() const;
    Acad::ErrorStatus setUcsFollowModeOn();
    Acad::ErrorStatus setUcsFollowModeOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setUcsFollowModeOn(bool bOn);

    bool              isUcsIconVisible() const;
    Acad::ErrorStatus setUcsIconVisible();
    Acad::ErrorStatus setUcsIconInvisible();
    ACDBCORE2D_PORT Acad::ErrorStatus setUcsIconVisible(bool );

    bool              isUcsIconAtOrigin() const;
    Acad::ErrorStatus setUcsIconAtOrigin();
    Acad::ErrorStatus setUcsIconAtCorner();
    ACDBCORE2D_PORT Acad::ErrorStatus setUcsIconAtOrigin(bool );

    bool              isFastZoomOn() const { return true; }
    Acad::ErrorStatus setFastZoomOn() { return Acad::eOk; }
    Acad::ErrorStatus setFastZoomOff() { return Acad::eOk; }
    ACDBCORE2D_PORT Acad::ErrorStatus setFastZoomOn(bool );

    Adesk::UInt16     circleSides() const;
    Acad::ErrorStatus setCircleSides(Adesk::UInt16);

    bool              isSnapOn() const;
    Acad::ErrorStatus setSnapOn();
    Acad::ErrorStatus setSnapOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setSnapOn(bool );

    bool              isSnapIsometric() const;
    Acad::ErrorStatus setSnapIsometric();
    Acad::ErrorStatus setSnapStandard();
    ACDBCORE2D_PORT Acad::ErrorStatus setSnapIsometric(bool );

    double            snapAngle() const;
    Acad::ErrorStatus setSnapAngle(double);

    AcGePoint2d       snapBasePoint() const;
    Acad::ErrorStatus setSnapBasePoint(const AcGePoint2d&); 

    AcGeVector2d      snapIncrement() const;
    Acad::ErrorStatus setSnapIncrement(const AcGeVector2d&);

    Adesk::UInt16     snapIsoPair() const;
    Acad::ErrorStatus setSnapIsoPair(Adesk::UInt16);

    bool              isGridOn() const;
    Acad::ErrorStatus setGridOn();
    Acad::ErrorStatus setGridOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setGridOn(bool );

    bool              isGridBoundToLimits() const;
    Acad::ErrorStatus setGridBoundToLimits(bool bNewVal);

    bool              isGridAdaptive() const;
    Acad::ErrorStatus setGridAdaptive(bool bNewVal);

    bool              isGridSubdivisionRestricted() const;
    Acad::ErrorStatus setGridSubdivisionRestricted(bool bNewVal);

    bool              isGridFollow() const;
    Acad::ErrorStatus setGridFollow(bool bNewVal);

    Adesk::UInt16     gridMajor() const;
    Acad::ErrorStatus setGridMajor(Adesk::UInt16);

    AcGeVector2d      gridIncrement() const;
    Acad::ErrorStatus setGridIncrement(const AcGeVector2d&);

    bool              hiddenLinesRemoved() const;
    Acad::ErrorStatus showHiddenLines();
    Acad::ErrorStatus removeHiddenLines();
    ACDBCORE2D_PORT Acad::ErrorStatus removeHiddenLines(bool );

    Acad::ErrorStatus freezeLayersInViewport(const AcDbObjectIdArray&);
    Acad::ErrorStatus thawLayersInViewport(const AcDbObjectIdArray&);
    Acad::ErrorStatus thawAllLayersInViewport();
    bool              isLayerFrozenInViewport(const AcDbObjectId& layerId) const;
    Acad::ErrorStatus getFrozenLayerList(AcDbObjectIdArray& ids) const;
    
    Acad::ErrorStatus updateDisplay() const;

    AcDbObjectId       background() const;
    Acad::ErrorStatus  setBackground(AcDbObjectId backgroundId);           
    AcDbObjectId       previousBackground(AcGiDrawable::DrawableType type
                                          = AcGiDrawable::kGeometry) const;
    Acad::ErrorStatus  setPreviousBackground(AcDbObjectId backgroundId,
                                             AcGiDrawable::DrawableType type
                                             = AcGiDrawable::kGeometry);
    Acad::ErrorStatus   setPreviousBackground(AcDbObjectId backgroundId,
                                            AcGiDrawable::DrawableType type,
                                            bool bForcedSwitch);
    bool                previousBackgroundForcedSwitch (void) const;

    // Visual Styles
    AcDbObjectId      visualStyle() const;
    Acad::ErrorStatus setVisualStyle(const AcDbObjectId oidVisualStyle);

    // Viewport Lighting
    //
    bool                isDefaultLightingOn() const;
    Acad::ErrorStatus   setDefaultLightingOn(bool on);
    AcGiViewportTraits::DefaultLightingType defaultLightingType() const;
    Acad::ErrorStatus   setDefaultLightingType(AcGiViewportTraits::DefaultLightingType typ);

    // Brightness controls the relative intensity of lights.
    double              brightness() const;
    Acad::ErrorStatus   setBrightness(double);
    // Contrast controls intensity of ambient light, relative to other lights.
    double              contrast() const;
    Acad::ErrorStatus   setContrast(double);

    AcCmColor           ambientLightColor() const;
    Acad::ErrorStatus   setAmbientLightColor(const AcCmColor& clr);

    // A single sun (distant light) can be associated with each viewport.
    AcDbObjectId        sunId() const;
    Acad::ErrorStatus   setSun(AcDbObjectId &retId, AcDbObject *pSun);
    Acad::ErrorStatus   setSun(AcDbObjectId &retId, AcDbObject *pSun, bool eraseOldSun);

    bool              isLocked() const;
    Acad::ErrorStatus setLocked();
    Acad::ErrorStatus setUnlocked();
    ACDBCORE2D_PORT Acad::ErrorStatus setLocked(bool );

    Acad::ErrorStatus setAnnotationScale(const AcDbAnnotationScale *pScaleObj);
    // get current annotation scale, return a pointer to AcDbAnnotationScale, 
    // caller is responsible for releasing the memory later
    AcDbAnnotationScale* annotationScale() const;

    bool              isTransparent() const;
    Acad::ErrorStatus setTransparent();
    Acad::ErrorStatus setOpaque();
    ACDBCORE2D_PORT Acad::ErrorStatus setTransparent(bool );
 
    enum StandardScaleType {
        kScaleToFit,        // Scaled to Fit
        kCustomScale,       // Scale is not a standard scale
        k1_1,               // 1:1
        k1_2,               // 1:2
        k1_4,               // 1:4
        k1_5,               // 1:5
        k1_8,               // 1:8
        k1_10,              // 1:10
        k1_16,              // 1:16
        k1_20,              // 1:20
        k1_30,              // 1:30
        k1_40,              // 1:40
        k1_50,              // 1:50
        k1_100,             // 1:100
        k2_1,               // 2:1
        k4_1,               // 4:1
        k8_1,               // 8:1
        k10_1,              // 10:1
        k100_1,             // 100:1
        k1_128in_1ft,       // 1/128"= 1'
        k1_64in_1ft,        // 1/64"= 1'
        k1_32in_1ft,        // 1/32"= 1'
        k1_16in_1ft,        // 1/16"= 1'
        k3_32in_1ft,        // 3/32"= 1'
        k1_8in_1ft,         // 1/8" = 1'
        k3_16in_1ft,        // 3/16"= 1'
        k1_4in_1ft,         // 1/4" = 1'
        k3_8in_1ft,         // 3/8" = 1'
        k1_2in_1ft,         // 1/2" = 1'
        k3_4in_1ft,         // 3/4" = 1'
        k1in_1ft,           // 1"= 1'
        k1and1_2in_1ft,     // 1 1/2"= 1'
        k3in_1ft,           // 3"= 1'
        k6in_1ft,           // 6"= 1'
        k1ft_1ft            // 1'= 1'
    };

    double            customScale() const;
    Acad::ErrorStatus setCustomScale(double);

    StandardScaleType standardScale() const;
    Acad::ErrorStatus setStandardScale(const StandardScaleType);

    ACDBCORE2D_PORT
    Acad::ErrorStatus plotStyleSheet(AcString &sName) const;
    Acad::ErrorStatus plotStyleSheet(ACHAR *&) const;   // deprecated
    Acad::ErrorStatus plotStyleSheet(const ACHAR *&) const;
    Acad::ErrorStatus effectivePlotStyleSheet(const ACHAR *&);
    Acad::ErrorStatus setPlotStyleSheet(const ACHAR *);

    bool              isNonRectClipOn() const;
    Acad::ErrorStatus setNonRectClipOn();
    Acad::ErrorStatus setNonRectClipOff();
    ACDBCORE2D_PORT Acad::ErrorStatus setNonRectClipOn(bool bOn);

    AcDbObjectId      nonRectClipEntityId() const;
    Acad::ErrorStatus setNonRectClipEntityId(AcDbObjectId);

    virtual void      erased(const AcDbObject* , Adesk::Boolean) override;
    virtual void      modified(const AcDbObject *) override;
    virtual void      copied(const AcDbObject* pDbObj,const AcDbObject* pNewObj) override;
    virtual void      subObjModified(const AcDbObject* pDbObj, 
                            const AcDbObject* pSubObj) override;

    // UCS query methods.
    //
    Acad::ErrorStatus getUcs (AcGePoint3d& origin,
                                AcGeVector3d& xAxis,
                                AcGeVector3d& yAxis ) const;
    bool              isUcsOrthographic(AcDb::OrthographicView& view) const;
    AcDbObjectId      ucsName           () const;
    double            elevation         () const;

    // UCS set methods.
    //
    Acad::ErrorStatus setUcs(const AcGePoint3d& origin,
                                const AcGeVector3d& xAxis,
                                const AcGeVector3d& yAxis);
    Acad::ErrorStatus setUcs(AcDb::OrthographicView view);
    Acad::ErrorStatus setUcs(const AcDbObjectId& ucsId);
    Acad::ErrorStatus setUcsToWorld();
    Acad::ErrorStatus setElevation(double elev );
 
    // Orthographic view methods.
    //
    bool           isViewOrthographic(AcDb::OrthographicView& view ) const;
    Acad::ErrorStatus setViewDirection(AcDb::OrthographicView view );

    // Methods to get/set UCSVP for viewport.
    //
    bool           isUcsSavedWithViewport () const;
    void           setUcsPerViewport ( bool ucsvp );

    // ShadePlot enum and get/set methods
    enum ShadePlotType {
        kAsDisplayed    = 0,
        kWireframe      = 1,
        kHidden         = 2,
        kRendered       = 3,
        kVisualStyle    = 4,
        kRenderPreset   = 5
    };

    ShadePlotType     shadePlot() const;
    Acad::ErrorStatus setShadePlot(const ShadePlotType);

    AcDbObjectId      shadePlotId() const;
    Acad::ErrorStatus setShadePlot(const ShadePlotType type,
                                   const AcDbObjectId shadePlotId);

    bool              plotWireframe() const;
    bool              plotAsRaster()  const;

    Acad::ErrorStatus toneOperatorParameters(AcGiToneOperatorParameters& params) const;
    Acad::ErrorStatus setToneOperatorParameters(const AcGiToneOperatorParameters& params);

protected:
    // AcDbEntity overrides
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

// This overload returns a buffer which the caller is responsible for freeing.
// It will be removed soon. Please use the overload taking (AcString &) arg
//
inline Acad::ErrorStatus AcDbViewport::plotStyleSheet(ACHAR *& pName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbViewport::plotStyleSheet, pName);
}

#pragma pack(pop)

#endif
