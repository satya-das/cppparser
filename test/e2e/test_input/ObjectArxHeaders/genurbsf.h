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
// Description:
//
// This file implements the class AcGeNurbSurface, a representation
// for a non-uniform, rational BSpline surface.
//

#ifndef AC_GENURBSF_H
#define AC_GENURBSF_H

#include "gegbl.h"
#include "gesurf.h"
#include "gept3dar.h"
#include "gedblar.h"
#pragma pack (push, 8)

class AcGeKnotVector;

class
GX_DLLEXPIMPORT
AcGeNurbSurface : public AcGeSurface
{
public:
   AcGeNurbSurface();
   AcGeNurbSurface(int degreeU, int degreeV, int propsInU, int propsInV,
                   int numControlPointsInU, int numControlPointsInV,
                   const AcGePoint3d controlPoints[],
                   const double weights[],
                   const AcGeKnotVector& uKnots,
                   const AcGeKnotVector& vKnots,
                   const AcGeTol& tol = AcGeContext::gTol);
   AcGeNurbSurface(const AcGeNurbSurface& nurb);

   // Assignment.
   //
   AcGeNurbSurface& operator = (const AcGeNurbSurface& nurb);

   // Geometric properties.
   //
   Adesk::Boolean   isRationalInU      () const;
   Adesk::Boolean   isPeriodicInU      (double&) const;
   Adesk::Boolean   isRationalInV      () const;
   Adesk::Boolean   isPeriodicInV      (double&) const;

   int singularityInU () const;
   int singularityInV () const;

   // Definition data.
   //
   int            degreeInU            () const;
   int            numControlPointsInU  () const;
   int            degreeInV            () const;
   int            numControlPointsInV  () const;
   void           getControlPoints     (AcGePoint3dArray& points) const;
   Adesk::Boolean getWeights           (AcGeDoubleArray& weights) const;

   int       numKnotsInU    () const;
   void      getUKnots      (AcGeKnotVector& uKnots) const;

   int       numKnotsInV    () const;
   void      getVKnots      (AcGeKnotVector& vKnots) const;

   void      getDefinition  (int& degreeU, int& degreeV,
                             int& propsInU,	int& propsInV,
                             int& numControlPointsInU,
                             int& numControlPointsInV,
                             AcGePoint3dArray& controlPoints,
                             AcGeDoubleArray& weights,
                             AcGeKnotVector& uKnots,
                             AcGeKnotVector& vKnots) const;

   // Reset surface
   //
   AcGeNurbSurface& set     (int degreeU, int degreeV,
                             int propsInU, int propsInV,
                             int numControlPointsInU,
                             int numControlPointsInV,
                             const AcGePoint3d controlPoints[],
                             const double weights[],
                             const AcGeKnotVector& uKnots,
                             const AcGeKnotVector& vKnots,
                             const AcGeTol& tol = AcGeContext::gTol);

};

#pragma pack (pop)
#endif
