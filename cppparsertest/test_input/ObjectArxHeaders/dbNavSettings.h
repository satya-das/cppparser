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
// Name:            dbNavSettings.h
//
// Description:     3D Navigation Tools DB Settings API, along with AcDbHomeView
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#pragma pack(push, 8)

class AcDbImpHomeView;

///////////////////////////////////////////////////////////////////////////////
//
// class AcDbHomeView - navigation home view settings class
//

class AcDbHomeView
{
public:
    ACDBCORE2D_PORT AcDbHomeView();
    ACDBCORE2D_PORT AcDbHomeView(const AcDbHomeView& rhvw);
    ACDBCORE2D_PORT virtual ~AcDbHomeView();

    // Member variable routines
    ACDBCORE2D_PORT const AcGePoint3d&     eye()           const;
    ACDBCORE2D_PORT const AcGePoint3d&     center()        const;
    ACDBCORE2D_PORT const AcGeVector3d&    up()            const;
    ACDBCORE2D_PORT const double           width()         const;
    ACDBCORE2D_PORT const double           height()        const;
    ACDBCORE2D_PORT const bool             isPerspective() const;

    ACDBCORE2D_PORT void setEye         (const AcGePoint3d& ptEye);
    ACDBCORE2D_PORT void setCenter      (const AcGePoint3d& ptCenter);
    ACDBCORE2D_PORT void setUp          (const AcGeVector3d& vUp);
    ACDBCORE2D_PORT void setWidth       (double dWidth);
    ACDBCORE2D_PORT void setHeight      (double dHeight);
    ACDBCORE2D_PORT void setPerspective (bool bPerspective);

    // DB access utility
    ACDBCORE2D_PORT Acad::ErrorStatus setHomeView(AcDbDatabase * pDb) const;
    ACDBCORE2D_PORT Acad::ErrorStatus getHomeView(AcDbDatabase * pDb,
                                            bool           bCreateDefault = false);

    // Fill members with default values
    ACDBCORE2D_PORT void toggleDefaultSettings();

    ACDBCORE2D_PORT bool            operator == (const AcDbHomeView& rhvw) const;
    ACDBCORE2D_PORT bool            operator != (const AcDbHomeView& rhvw) const;
    ACDBCORE2D_PORT AcDbHomeView&   operator  = (const AcDbHomeView& rhvw);

    ACDBCORE2D_PORT bool isDefaultHomeView() const;

private:
    AcDbImpHomeView * mpImpObj;
};

// Navigation home view routine
ACDBCORE2D_PORT 
Acad::ErrorStatus acdbSetHomeView(AcDbDatabase *        pDb, 
                                  const AcDbHomeView&   hmView);

ACDBCORE2D_PORT 
Acad::ErrorStatus acdbGetHomeView(AcDbDatabase *        pDb, 
                                  AcDbHomeView&         hmView);

// ViewCube compass show/hide
ACDBCORE2D_PORT Acad::ErrorStatus 
acdbSetShowCompass(AcDbDatabase *         pDb, 
                   bool                   bShow);

ACDBCORE2D_PORT Acad::ErrorStatus 
acdbGetShowCompass(AcDbDatabase *         pDb, 
                   bool &                 bShow);

#pragma pack(pop)