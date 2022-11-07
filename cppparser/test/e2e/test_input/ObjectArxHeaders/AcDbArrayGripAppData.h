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
// DESCRIPTION:
//
// AcDbArrayGripAppData class. 
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "AcDbAssocArrayItem.h"
/// <summary> 
/// AcDbArrayGripAppData, represents grip specific data for associative array. 	  	 
/// Object of this class will be attached with AcDbGripData as appdata by 	  	 
/// AcDbAssocArrayActionBody and it's derived classes. 	  	 
/// </summary> 
/// <remarks> This class is currently for internal use only. </remarks>
///
class ACDB_PORT AcDbArrayGripAppData : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcDbArrayGripAppData);

    /// <summary>
    /// Default constructor. Can be initialized using position and mode.
    /// </summary>
    /// <param name="position"> The input position of the grip. </param>
    /// <param name="modes"> The input grip modes. </param>
    ///
    AcDbArrayGripAppData(const AcGePoint3d& position = AcGePoint3d(), 
                         unsigned int modes = 0);

    /// <summary>
    /// Default destructor.
    /// </summary>
    ///
    virtual ~AcDbArrayGripAppData();

    /// <summary>
    /// Returns position of the grip.
    /// </summary>
    /// <returns> The position of the grip. 
    /// </returns>
    ///
    const AcGePoint3d& position() const { return mPosition; }
    
    /// <summary>
    /// Returns modes of the grip.
    /// </summary>
    /// <returns> The modes of the grip. 
    /// </returns>
    ///
    unsigned int modes() const { return mnModes; }

    /// <summary>
    /// Adds additional grip mode.
    /// </summary>
    /// <param name="mode"> The input grip mode. </param>
    ///
    void addGripMode(unsigned int mode) { mnModes |= mode; }

    /// <summary>
    /// Returns app data and it's class attached with this grip.
    /// </summary>
    /// <param name="ppClass"> The input AcRxClass attached to this grip. </param>
    /// <returns> Pointer to app data.
    /// </returns>
    ///
    void* getAppData(AcRxClass** ppClass = NULL) const
    {
        if(NULL != ppClass)
            *ppClass = mpAppDataClass;
        return mpAppData;
    }

    /// <summary>
    /// Attaches app data and its class to the grip.
    /// </summary>
    /// <param name="pData"> The input app data. </param>
    /// <param name="pClass"> The input AcRxClass attached to this grip. </param>
    ///
    void setAppData(void* pData, AcRxClass* pClass)
    {
        mpAppData = pData; mpAppDataClass = pClass;
    }

    /// <summary>
    /// Checks if it represents an arrow grip.
    /// </summary>
    /// <returns> The boolean value indicating whether the grip is of arrow shape. 
    /// </returns>
    ///
    bool& arrowGrip() { return mbArrowGrip; }
    
    /// <summary>
    /// Returns x direction of the arrow grip.
    /// </summary>
    /// <returns> The x direction of the arrow grip. 
    /// </returns>
    ///
    AcGeVector3d& xDir() { return mDirections[0]; }
    
    /// <summary>
    /// Returns y direction of the arrow grip.
    /// </summary>
    /// <returns> The y direction of the arrow grip. 
    /// </returns>
    ///
    AcGeVector3d& yDir() { return mDirections[1]; }
    
    /// <summary>
    /// Returns locator index for the grip.
    /// </summary>
    /// <returns> The locator index for the grip. 
    /// </returns>
    ///
    AcDbItemLocator& locator() { return mLocator; }

    /// <summary>
    /// Returns the dynamic dimension data array.
    /// </summary>
    /// <returns> The dynamic dimension data array. 
    /// </returns>
    ///
    const AcDbDimDataPtrArray& dimData() const { return mDimData; }

    /// <summary>
    /// Adds the dynamic dimension data.
    /// </summary>
    /// <param name="pData"> The input dynamic dimension data. </param>
    ///
    void appendDimData(AcDbDimData* pData);


    /// <summary>
    /// deletes all AcDimAppData in AcDbDimData of the dynamic dimension data array..
    /// </summary>
    ///
    void deleteDimData();

    /// <summary>
    /// cache a base point for AcDbGripData if the rubber band is to be displayed from some other starting point.
    /// </summary>
    /// <param name="basePoint"> The input base point for AcDbGripData. </param>
    ///
    void setBasePoint(AcGePoint3d &basePoint);

    /// <summary>
    /// return the base point being cached. If NULL, then no need to set this base point for AcDbGripData.
    /// </summary>
    /// <returns> The base point being cached. 
    /// </returns>
    ///
    const AcGePoint3d* basePoint() const {return mpBasePoint;}

private:
    AcGePoint3d mPosition;
    unsigned int mnModes;
    void* mpAppData;
    AcRxClass* mpAppDataClass;
    AcDbItemLocator mLocator;
    bool mbArrowGrip;
    AcGeVector3d mDirections[2];
    AcDbDimDataPtrArray mDimData;
    AcGePoint3d *mpBasePoint;
};

