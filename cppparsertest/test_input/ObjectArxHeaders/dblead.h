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

#ifndef AD_DBLEAD_H
#define AD_DBLEAD_H 1

#include "dbmain.h"
#include "dbcurve.h"
#include "gescl3d.h"
#include "gepnt2d.h"
#include "geplane.h"

#pragma pack(push, 8)

class AcDbLeader: public  AcDbCurve
{
public:
    AcDbLeader();
    ~AcDbLeader();
    ACDB_DECLARE_MEMBERS(AcDbLeader);
    DBCURVE_METHODS

    // Leader orientation.
    //
    virtual void              setPlane          (const AcGePlane&);
    virtual AcGeVector3d      normal            () const;

    // Vertex manipulation.
    //
    virtual  int numVertices() const;
    virtual  Adesk::Boolean appendVertex(const AcGePoint3d&);
    virtual  void              removeLastVertex  ();
    virtual  AcGePoint3d firstVertex() const;
    virtual  AcGePoint3d lastVertex() const;
    virtual  AcGePoint3d vertexAt(int) const;
    virtual  Adesk::Boolean setVertexAt(int, const AcGePoint3d&);

    // Display characteristics.
    //
    virtual Adesk::Boolean    hasArrowHead      () const;
    virtual void              enableArrowHead   ();
    virtual void              disableArrowHead  ();
    ACDBCORE2D_PORT void            setHasArrowHead   (Adesk::Boolean bEnable);
    virtual Adesk::Boolean    hasHookLine       () const;
    //
    virtual void              setToSplineLeader ();
    virtual void              setToStraightLeader();
    virtual Adesk::Boolean    isSplined         () const;
    ACDBCORE2D_PORT void            setSplined        (Adesk::Boolean bSplined);
    //
    virtual AcDbHardPointerId dimensionStyle    () const;
    virtual void              setDimensionStyle (const AcDbHardPointerId&);
    
    Acad::ErrorStatus   getDimstyleData(AcDbDimStyleTableRecord*& pRecord) const;
    Acad::ErrorStatus   setDimstyleData(AcDbDimStyleTableRecord* pNewData);
    Acad::ErrorStatus   setDimstyleData(AcDbObjectId newDataId);
        
    // Associativity support.
    //
    virtual Acad::ErrorStatus attachAnnotation  (const AcDbObjectId& annoId);
    virtual Acad::ErrorStatus detachAnnotation  ();
    virtual AcDbObjectId      annotationObjId   () const;
    ACDBCORE2D_PORT Acad::ErrorStatus setAnnotationObjId(const AcDbObjectId& annoId);
    virtual Acad::ErrorStatus evaluateLeader    ();
    //
    // Relation of leader endpoint to annotation:
    //
    virtual AcGeVector3d      annotationOffset   () const;
    virtual Acad::ErrorStatus setAnnotationOffset(const AcGeVector3d& offset);

    enum AnnoType { 
        kMText = 0,
        kFcf,
        kBlockRef,
        kNoAnno 
    };
    AnnoType annoType()   const;
    double   annoHeight() const;
    double   annoWidth()  const;

    // Dimension variable get methods in alphabetic order:
    //
    virtual double           dimasz   () const;
    virtual AcCmColor        dimclrd  () const;
    virtual double           dimgap   () const;
    virtual AcDb::LineWeight dimlwd   () const;
    virtual AcDbObjectId     dimldrblk() const;
    virtual bool             dimsah   () const;
    virtual double           dimscale () const;
    virtual int              dimtad   () const;
    virtual AcDbObjectId     dimtxsty () const;
    virtual double           dimtxt   () const;

    // Dimension variable set methods in alphabetic order:
    //
    virtual Acad::ErrorStatus setDimasz   (double         val);
    virtual Acad::ErrorStatus setDimclrd  (AcCmColor&     val);
    virtual Acad::ErrorStatus setDimgap   (double         val);
    virtual Acad::ErrorStatus setDimldrblk(AcDbObjectId   val);
    virtual Acad::ErrorStatus setDimldrblk(const ACHAR *  val);
    virtual Acad::ErrorStatus setDimlwd   (AcDb::LineWeight v);  // new to R15
    virtual Acad::ErrorStatus setDimsah   (bool           val);
    virtual Acad::ErrorStatus setDimscale (double         val);
    virtual Acad::ErrorStatus setDimtad   (int            val);
    virtual Acad::ErrorStatus setDimtxsty (AcDbObjectId   val);
    virtual Acad::ErrorStatus setDimtxt   (double         val);

    // Support for persistent reactor to annotation.
    //
    virtual void              modified          (const AcDbObject*) override;
    virtual void              erased            (const AcDbObject*,
                                                 Adesk::Boolean = Adesk::kTrue) override;
    virtual void              goodbye           (const AcDbObject*) override;
    virtual void              copied            (const AcDbObject*,
                                                 const AcDbObject*) override;

    // DEPRECATED METHODS!
    // These are supported but will be removed in future releases:
    //
    virtual void              setDimVars        ();
    virtual Acad::ErrorStatus setColorIndex     (Adesk::UInt16,
                                 Adesk::Boolean doSubents = Adesk::kTrue) override;
    //
    // end DEPRECATED METHODS!

    protected:

    // Get corresponding COM wrapper class ID
    //
    virtual Acad::ErrorStatus   subGetClassID(CLSID* pClsid) const override;
};

// These are methods of AcDbCurve that aren't implemented for AcDbLeader:
//
inline Adesk::Boolean AcDbLeader::isClosed() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbLeader::isPeriodic() const
{
    return Adesk::kFalse;
}

inline Adesk::Boolean AcDbLeader::isPlanar() const
{
    return Adesk::kTrue;
}

inline Acad::ErrorStatus AcDbLeader::getStartParam(double& param) const
{
    param = 0.0;
    return Acad::eOk;
}

inline Acad::ErrorStatus AcDbLeader::getOrthoProjectedCurve(const AcGePlane&,
                                                AcDbCurve*& ) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::getProjectedCurve(const AcGePlane&,
                                                const AcGeVector3d&,
                                                AcDbCurve*&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::getOffsetCurves(double,
                                        AcDbVoidPtrArray&) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::getSecondDeriv (double,
                                        AcGeVector3d& ) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::getSecondDeriv (const AcGePoint3d&,
                                AcGeVector3d& ) const
{
    return Acad::eNotApplicable;
}


inline Acad::ErrorStatus AcDbLeader::getSplitCurves (const AcGeDoubleArray& ,
                                AcDbVoidPtrArray& ) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::getSplitCurves (const AcGePoint3dArray& ,
                                AcDbVoidPtrArray& ) const
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::extend(double)
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::extend(Adesk::Boolean, const AcGePoint3d&)
{
    return Acad::eNotApplicable;
}

inline Acad::ErrorStatus AcDbLeader::getArea(double&) const
{
    return Acad::eNotApplicable;
}

#pragma pack(pop)

#endif

