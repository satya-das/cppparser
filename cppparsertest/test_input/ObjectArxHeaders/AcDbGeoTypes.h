//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////


#ifndef __GEOTYPE_H
#define __GEOTYPE_H

#pragma pack (push, 8)

/// <summary>
/// AcGeoMapType enum is used by both LiveMap and AcDbGeoMap which is a snapshot of the livemap. 
/// </summary>
///
enum AcGeoMapType 
{
    /// <summary> LiveMap is turned off. This is not used by AcDbGeoMap::mapType. </summary>
	kNoMap = 0, 
	
    /// <summary>
    /// Map in aerial view.
    /// </summary>
	kAerial = 1, 
	
    /// <summary>
    /// Map in road view.
    /// </summary>
	kRoad = 2, 

    /// <summary>
    /// Map in hybrid view.
    /// </summary>
	kHybrid = 3
};


/// <summary>
/// AcGeoMapResolution enum is applied to LiveMap Zoom Level (or Level Of Detail) number. 
/// </summary>
///
enum AcGeoMapResolution
{
    /// <summary>
    /// One level less than current zoom level
    /// </summary>
	kCoarse = -1, 

    /// <summary>
    /// Same as current zoom level
    /// </summary>
	kOptimal = 0, 
	
    /// <summary>
    /// One level higher than current zoom level
    /// </summary>
	kFine = 1, 

    /// <summary>
    /// Two levels higher than current zoom level
    /// </summary>
	kFiner = 2
};


#pragma pack (pop)
#endif // __GEOTYPE_H