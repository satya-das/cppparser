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
#include "AcPointCloudEngineAPI.h"


/// <summary>
/// The PointCloudBinaryOperatorFilter is the base class for all filters that 
/// use binary operation on two filters
/// </summary>
class ACDB_PORT PointCloudBinaryOperatorFilter : public IPointCloudFilter
{
public:
    virtual ~PointCloudBinaryOperatorFilter();
    virtual int testCell(double minX, double minY,
                         double minZ, double maxX,
                         double maxY, double maxZ) const = 0;

    virtual bool testPoint(float x, float y, float z) const = 0;

    virtual IPointCloudFilter* clone() const = 0;

    virtual void freeObject(void) = 0;

    virtual bool isInverted() const;
    virtual void setIsInverted(bool bInverted);

protected:
    PointCloudBinaryOperatorFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    PointCloudBinaryOperatorFilter(const PointCloudBinaryOperatorFilter& other);

    IPointCloudFilter*  mpLeftFilter;
    IPointCloudFilter*  mpRightFilter;

private:
    bool                mbIsInverted;

private:
    // outlawed
    PointCloudBinaryOperatorFilter& operator = (const PointCloudBinaryOperatorFilter&);
};

/// <summary>
/// The PointCloudIntersectionFilter allows filter based on intersection of two filters
/// </summary>
class ACDB_PORT PointCloudIntersectionFilter : public PointCloudBinaryOperatorFilter
{
public:
    /// <Summary>
    /// Constructor
    /// </Summary>
    /// <param name="pLeft">The filter pointer of the left operand</param>
    /// <param name="pRight">The filter pointer of the right operand</param>
    PointCloudIntersectionFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    virtual ~PointCloudIntersectionFilter();
    virtual int testCell(double minX, double minY, double minZ,
                        double maxX, double maxY, double maxZ) const;
    virtual bool testPoint(float x, float y, float z) const;
    virtual IPointCloudFilter* clone() const;
    virtual void freeObject(void);
};

/// <summary>
/// The PointCloudUnionFilter allows filter based on union of two filters
/// </summary>
class ACDB_PORT PointCloudUnionFilter : public PointCloudBinaryOperatorFilter
{
public:
    /// <Summary>
    /// Constructor
    /// </Summary>
    /// <param name="pLeft">The filter pointer of the left operand</param>
    /// <param name="pRight">The filter pointer of the right operand</param>
    PointCloudUnionFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    virtual ~PointCloudUnionFilter();

    virtual int testCell(double minX, double minY, double minZ,
                        double maxX, double maxY, double maxZ) const;
    virtual bool testPoint(float x, float y, float z) const;
    virtual IPointCloudFilter* clone() const;
    virtual void freeObject(void);
};

/// <summary>
/// The PointCloudXORFilter allows filter based on symmetric difference of two filters
/// </summary>
class ACDB_PORT PointCloudXORFilter : public PointCloudBinaryOperatorFilter
{
public:
    /// <Summary>
    /// Constructor
    /// </Summary>
    /// <param name="pLeft">The filter pointer of the left operand</param>
    /// <param name="pRight">The filter pointer of the right operand</param>
    PointCloudXORFilter(IPointCloudFilter* pLeft, IPointCloudFilter* pRight);
    virtual ~PointCloudXORFilter();

    virtual int testCell(double minX, double minY, double minZ,
                        double maxX, double maxY, double maxZ) const;
    virtual bool testPoint(float x, float y, float z) const;
    virtual IPointCloudFilter* clone() const;
    virtual void freeObject(void);
};
