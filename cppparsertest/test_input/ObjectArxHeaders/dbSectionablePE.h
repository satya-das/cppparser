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

///////////////////////////////////////////////////////////////////////////////
// AcDbSectionablePE Protocol extension
//
class AcDbSectionablePE : public AcRxObject
{
public:
    // Only need to export run-time class methods
    ACRX_DECLARE_MEMBERS_EXPIMP(AcDbSectionablePE, ACDBCORE2D_PORT);

    // Check if the AcDbObject is sectionable
    // AcDbSection object will check this protocol extension,
    // if the AcDbObject support section, AcDbSection will apply to it. 
    //
    virtual bool supportSection(const AcDbObject& pObject) = 0;
};