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
// This file implements the class AcGeCylinder, a representation for
// a right circular cylinder.  It is defined by its radius,
// axis of symmetry, and the origin (a point on the axis). It
// is generated by revolving a line parallel to the axis of symmetry,
// at a	distance of radius. The cylinder is paramterized as follows.
// u is the angle of revolution, measured from the refAxis (an axis
// perpendicular to the axis of symmetry). Right hand rule applied
// along the direction of the axis of symmetry defines the positive
// direction.  For a closed cylinder, u defaults to [-PI, PI).
// v parameter varies along the axis of symmetry.  It is positive in
// the direction of the axis of symmetry.  v = 0 correspond to the
// cross section containing the origin of the cylinder.  v is
// dimensionless.  Its speed is determined by the initial radius
// of the cylinder.
// The surface is perodic in u with a period of 2PI.
// [umin, umax] x [vmin, vmax] defines a four sided cylindrical
// patch bounded by two straight lines (at umin and umax), and
// two circular arcs (at vmin and vmax).  Following constraints
// apply to the definition of a cylindrical patch.
// umin < umax and |umin - umax| <= 2PI.
//
#ifndef AC_GECYLNDR_H
#	define AC_GECYLNDR_H
#	include "gegbl.h"
#	include "gesurf.h"
#	include "gevec3d.h"
#	include "geintrvl.h"
#	include "gearc3d.h"
#	pragma  pack (push, 8)
class AcGeCircArc3d;
class GX_DLLEXPIMPORT AcGeCylinder : public AcGeSurface
{
public:
	AcGeCylinder();
	AcGeCylinder(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry);
	AcGeCylinder(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSymmetry, const AcGeVector3d& refAxis, const AcGeInterval& height, double startAngle, double endAngle);
	AcGeCylinder(const AcGeCylinder&);
    // Geometric properties.
    //
	double radius() const;
	AcGePoint3d origin() const;
	void getAngles(double& start, double& end) const;
	void getHeight(AcGeInterval& height) const;
	double heightAt(double u) const;
	AcGeVector3d axisOfSymmetry() const;
	AcGeVector3d refAxis() const;
	Adesk::Boolean isOuterNormal() const;
	Adesk::Boolean isClosed(const AcGeTol& tol = AcGeContext::gTol) const;
	AcGeCylinder& setRadius(double radius);
	AcGeCylinder& setAngles(double start, double end);
	AcGeCylinder& setHeight(const AcGeInterval& height);
	AcGeCylinder& set(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSym);
	AcGeCylinder& set(double radius, const AcGePoint3d& origin, const AcGeVector3d& axisOfSym, const AcGeVector3d& refAxis, const AcGeInterval& height, double startAngle, double endAngle);
    // Assignment operator.
    //
	AcGeCylinder& operator =(const AcGeCylinder& cylinder);
    // Intersection with a linear entity
    //
	Adesk::Boolean intersectWith(const AcGeLinearEnt3d& linEnt, int& intn, AcGePoint3d& p1, AcGePoint3d& p2, const AcGeTol& tol = AcGeContext::gTol) const;
};
#	pragma  pack (pop)
#endif