//////////////////////////////////////////////////////////////////////////////
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

/// <summary>
/// Profile curve, it may be a line or an arc.
/// </summary>
///
class ACDB_PORT ProfileCurve2d
{
public:
    /// <summary>
    /// Curve type, linesegment or arc.
    /// </summary>
    ///
    enum ProfileurveType
    {
        kLineSeg = 0,
        kArc,
    };    
private:
    AcGeLineSeg2d m_seg;
    AcGeCircArc2d m_arc;
    ProfileurveType m_type;

public:
    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    ProfileCurve2d()
    {
        m_type = kLineSeg;
    }
    /// <summary>
    /// Construct it as a line segment.
    /// </summary>
    ///
    ProfileCurve2d(const AcGeLineSeg2d& seg)
    {
        m_seg = seg;
        m_type = kLineSeg;
    }
    /// <summary>
    /// Construct it as an arc.
    /// </summary>
    ///
    ProfileCurve2d(const AcGeCircArc2d& arc)
    {
        m_arc = arc;
        m_type = kArc;
    }

    /// <summary>
    /// If it's a line segment
    /// </summary>
    ///
    bool isSegment() const
    {
        return m_type == kLineSeg;
    }
    /// <summary>
    /// If it's an arc.
    /// </summary>
    ///
    bool isArc() const
    {
        return m_type == kArc;
    }

    /// <summary>
    /// Gets the line segment.
    /// </summary>
    ///
    AcGeLineSeg2d lineSeg() const
    {
        return m_seg;
    }
    /// <summary>
    /// Sets the line segment.
    /// </summary>
    ///
    void setLineSeg(const AcGeLineSeg2d& lineSeg)
    {
        m_seg = lineSeg;
        m_type = kLineSeg;
    }

    /// <summary>
    /// Gets the arc.
    /// </summary>
    ///
    AcGeCircArc2d arc() const
    {
        return m_arc;
    }
    /// <summary>
    /// Sets the arc.
    /// </summary>
    ///
    void setArc(const AcGeCircArc2d& arc)
    {
        m_arc = arc;
        m_type = kArc;
    }
};

/// <summary>
/// Point cloud line extraction result.
/// </summary>
///
class ACDB_PORT AcPointCloudExtractResult
{
public:
    /// <summary>
    /// The generated curves, they're 2d and in ecs size.
    /// </summary>
    ///
    AcArray<ProfileCurve2d> Curves;
    /// <summary>
    /// The matrix to transform these 2d linework into 3d wcs linework.
    /// </summary>
    ///
    AcGeMatrix3d            transform;
    /// <summary>
    /// The plane you want the linework to be projected.
    /// </summary>
    ///
    AcGePlane               ProjectedPlane;
};