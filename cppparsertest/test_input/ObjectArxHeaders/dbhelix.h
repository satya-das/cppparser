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
// DESCRIPTION: Exported class for Helix - AcDbHelix

#ifndef ACDB_DBHELIX_H
#define ACDB_DBHELIX_H

#include "gegbl.h"
#include "dbmain.h"
#include "dbspline.h"

#pragma pack (push, 8)

////////////////////////////////////////////////////////////////////////
// class AcDbHelix 
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class implements the AutoCAD helix entity.
/// Objects of the AcDbHelix class contain an embedded AcDbSpline which is
/// wrapped by the AcDbHelix in order to constrain it's behavior so that its
/// basic shape is maintained.
/// </summary>
///
/// <remarks>
/// AcDbHelix derives from AcDbSpline, but an attempt to modify the object by
/// fit or nurbs data will return an error.
/// </remarks>
///
class AcDbHelix: public AcDbSpline
{
public:

    /// <summary>
    /// Special constrain type values. 
    /// </summary>
    /// 
    enum ConstrainType {
        
        /// <summary>
        /// Constrain turn height. 
        /// </summary>
        /// 
        kTurnHeight = 0,

        /// <summary>
        /// Constrain turns. 
        /// </summary>
        /// 
        kTurns      = 1,

        /// <summary>
        /// Constrain height. 
        /// </summary>
        /// 
        kHeight     = 2
    };

public:
    ACDB_DECLARE_MEMBERS(AcDbHelix);

    /// <summary>
    /// Default constructor.
    /// </summary>
    AcDbHelix();
 
    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~AcDbHelix();

    /// <summary>
    /// Constructs the embedded spline data.
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    Acad::ErrorStatus createHelix();

    /// <summary>
    /// Axis point for the helix 
    /// </summary>
    /// <returns>
    /// Returns the start point the axis for the helix 
    /// </returns>
    virtual AcGePoint3d axisPoint() const;

    /// <summary>
    /// Sets the start point the axis for the helix 
    /// </summary>
    /// <param name="axisPoint">
    /// The 3d point where the axis starts
    /// </param>
    /// <param name="bMoveStartPoint">
    /// Also relocate the start point by the same offset that the axis point
    /// moved.
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setAxisPoint(const AcGePoint3d &axisPoint,
        const bool bMoveStartPoint = true);

    /// <summary>
    /// Start point for the helix
    /// </summary>
    /// <returns>
    /// Returns the start point of the helix
    /// </returns>
    virtual AcGePoint3d startPoint() const;

    /// <summary>
    /// Sets the start point of the helix 
    /// </summary>
    /// <param name="axisPoint">
    /// The 3d point where the helix starts
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setStartPoint(const AcGePoint3d &startPoint);

    /// <summary>
    /// Vector of the axis of the helix
    /// </summary>
    /// <returns>
    /// Returns the vector for the axis of the helix
    /// </returns>
    virtual AcGeVector3d axisVector() const;

    /// <summary>
    /// Sets the vector for the axis for the helix 
    /// </summary>
    /// <param name="axisPoint">
    /// The 3d vector for the  axis
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setAxisVector(const AcGeVector3d &axisVector);

    /// <summary>
    /// Height of the helix
    /// </summary>
    /// <returns>
    /// Returns the height of the helix
    /// </returns>
    virtual double height() const;

    /// <summary>
    /// Sets the height of the helix
    /// </summary>
    /// <param name="dHeigth">
    /// height for the helix entity
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    /// <remarks>
    /// This will change the turnHeight property, keeping the number of turns
    /// constant
    /// </remarks>
    virtual Acad::ErrorStatus setHeight(double dHeight);

    /// <summary>
    /// Base radius of the helix
    /// </summary>
    /// <returns>
    /// Returns the base radius of the helix
    /// </returns>
    virtual double baseRadius() const;

    /// <summary>
    /// Sets the base radius of the helix
    /// </summary>
    /// <param name="dRadius">
    /// base radius for the helix entity
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setBaseRadius(double dRadius);

    /// <summary>
    /// Top radius of the helix
    /// </summary>
    /// <returns>
    /// Returns the top radius of the helix
    /// </returns>
    virtual double topRadius() const;

    /// <summary>
    /// Sets the top radius of the helix
    /// </summary>
    /// <param name="dRadius">
    /// top radius for the helix entity
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setTopRadius(double dRadius);

    /// <summary>
    /// Number of turns (revolutions) of the helix
    /// </summary>
    /// <returns>
    /// Returns the number of turns (revolutions)
    /// </returns>
    virtual double turns() const;
    /// <summary>
    /// Sets the number of turns (revolutions)
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setTurns(double dTurns);

    /// <summary>
    /// Turn height (distance between threads)
    /// </summary>
    /// <returns>
    /// Returns the turn height (distance between threads)
    /// </returns>
    virtual double turnHeight() const;
    /// <summary>
    /// Sets the turn height (distance between threads)
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setTurnHeight(double dTurnHeight);

    /// <summary>
    /// Twist of the helix (clockwise or counter-clockwise)
    /// </summary>
    /// <returns>
    /// Returns the twist of the helix (clockwise or counter-clockwise)
    /// </returns>
    virtual Adesk::Boolean twist() const;
    /// <summary>
    /// Sets the twist of the helix (clockwise or counter-clockwise)
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setTwist(Adesk::Boolean bTwist);

    /// <summary>
    /// Constrain property of the helix
    /// </summary>
    /// <returns>
    /// Returns the constrain property of the helix
    /// </returns>
    virtual ConstrainType constrain() const;
    /// <summary>
    /// Sets the constrain property of the helix
    /// </summary>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    virtual Acad::ErrorStatus setConstrain(ConstrainType constrain);

    /// <summary>
    /// Turn slope of the helix
    /// </summary>
    /// <returns>
    /// Returns the turn slope angle of the helix
    /// </returns>
    virtual double turnSlope() const;

    /// <summary>
    /// Total length of the helix
    /// </summary>
    /// <returns>
    /// Returns the total length of the helix
    /// </returns>
    virtual double totalLength() const;

    /// <summary>
    /// Reverses the parameterization of the curve
    /// The start becomes the end and visa versa
    /// </summary>
    Acad::ErrorStatus reverseCurve() override;

protected:
    /// <summary>
    /// Gets the corresponding COM wrapper class ID.
    /// </summary>
    /// <param name="pClsid">
    /// Output pointer to class ID
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if succssful.
    /// </returns>
    Acad::ErrorStatus subGetClassID(CLSID* pClsid) const override;
};

#pragma pack (pop)

#endif
