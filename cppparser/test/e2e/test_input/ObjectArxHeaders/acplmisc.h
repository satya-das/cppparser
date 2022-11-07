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

#include "acpldsddata.h"

class AcPlPlotConfig;

/// <summary>
/// This function publishes the data in dsdDataObj to a device or DWF file specified
/// and configured by the data in the PlotConfig object pointed to by pConfig.
///
/// If bShowPlotProgress is true, then a plot progress dialog/meter will be displayed.
/// </summary>
/// <param name="dsdDataObj">Input object containing data to be plotted</param>
/// <param name="pConfig">Input pointer to plotConfig object</param>
/// <param name="bShowPlotProgress">Input bool specifying whether or not to display
/// a plot progress dialog</param>
void acplPublishExecute(AcPlDSDData dsdDataObj, AcPlPlotConfig* pConfig, 
    bool bShowPlotProgress);
