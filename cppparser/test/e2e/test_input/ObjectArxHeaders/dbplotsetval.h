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
// Name:    dbplotsetval.h
//
// Remarks: This class exports access methods which validate data on an 
//          AcDbPlotSettings object before actually setting the data on
//          the object.
//
//////////////////////////////////////////////////////////////////////////////
//

#ifndef AD_DBPLOTSETVAL_H
#define AD_DBPLOTSETVAL_H

#include "AdAChar.h"

#pragma pack (push, 8)
template <class T, class R> class AcArray;
class AcDbPlotSettings;

typedef AcDbPlotSettings::PlotPaperUnits PlotPaperUnits;
typedef AcDbPlotSettings::PlotRotation   PlotRotation;
typedef AcDbPlotSettings::PlotType       PlotType;
typedef AcDbPlotSettings::StdScaleType   StdScaleType;

class AcDbPlotSettingsValidator {
public:    
    virtual Acad::ErrorStatus 
    setPlotCfgName            (AcDbPlotSettings* pPlotSet,
                               const ACHAR * plotDeviceName,
                               const ACHAR * mediaName = NULL     ) = 0;
    virtual Acad::ErrorStatus 
    setCanonicalMediaName     (AcDbPlotSettings* pPlotSet,
                               const ACHAR * mediaName            ) = 0;
    virtual Acad::ErrorStatus
    setPlotOrigin             (AcDbPlotSettings *pPlotSet, 
                               const double xCoordinate,
                               const double yCoordinate         ) = 0;
    virtual Acad::ErrorStatus 
    setPlotPaperUnits         (AcDbPlotSettings* pPlotSet,
                               const PlotPaperUnits units       ) = 0;
    virtual Acad::ErrorStatus 
    setPlotRotation           (AcDbPlotSettings* pPlotSet,
                               const PlotRotation rotationType  ) = 0;
    virtual Acad::ErrorStatus 
    setPlotCentered           (AcDbPlotSettings* pPlotSet,
                               Adesk::Boolean isCentered        ) = 0;
    virtual Acad::ErrorStatus 
    setPlotType               (AcDbPlotSettings* pPlotSet,
                               const PlotType plotAreaType      ) = 0;
    virtual Acad::ErrorStatus 
    setPlotWindowArea         (AcDbPlotSettings* pPlotSet,
                               const double xmin,
                               const double ymin,
                               const double xmax,
                               const double ymax                ) = 0;
    virtual Acad::ErrorStatus 
    setPlotViewName           (AcDbPlotSettings* pPlotSet,
                               const ACHAR * viewName             ) = 0;
    virtual Acad::ErrorStatus 
    setUseStandardScale       (AcDbPlotSettings* pPlotSet,
                               Adesk::Boolean useStandard       ) = 0;
    virtual Acad::ErrorStatus 
    setCustomPrintScale       (AcDbPlotSettings* pPlotSet,
                               const double numerator,
                               const double denominator         ) = 0;
    virtual Acad::ErrorStatus 
    setCurrentStyleSheet      (AcDbPlotSettings* pPlotSet,
                               const ACHAR * styleSheetName       ) = 0;
    virtual Acad::ErrorStatus 
    setStdScaleType           (AcDbPlotSettings* pPlotSet,
                               const StdScaleType scaleType     ) = 0;
    virtual Acad::ErrorStatus 
    setStdScale               (AcDbPlotSettings* pPlotSet,
                               const double standardScale       ) = 0;
    virtual Acad::ErrorStatus               
    plotDeviceList            (AcArray<const ACHAR *> & deviceList) = 0;

    virtual Acad::ErrorStatus               
    canonicalMediaNameList    (AcDbPlotSettings* pPlotSet,
                               AcArray<const ACHAR *> & mediaList ) = 0;
    virtual Acad::ErrorStatus
    getLocaleMediaName        (AcDbPlotSettings *pPlotSet,
                               const ACHAR *  canonicalName,
                               const ACHAR *& localeName          ) = 0;
    virtual Acad::ErrorStatus
    getLocaleMediaName        (AcDbPlotSettings *pPlotSet,
                               int index,
                               const ACHAR *& localeName          ) = 0;
    virtual Acad::ErrorStatus
    setClosestMediaName       (AcDbPlotSettings* pPlotSet,
                               const double paperWidth,
                               const double paperHeight,
                               const PlotPaperUnits units,       
                               Adesk::Boolean matchPrintableArea) = 0;
    virtual Acad::ErrorStatus               
    plotStyleSheetList        (AcArray<const ACHAR *> & styleList ) = 0;  

    virtual void              
    refreshLists              (AcDbPlotSettings* pPlotSet       ) = 0;

    virtual void
    setZoomToPaperOnUpdate    (AcDbPlotSettings* pPlotSet,
                               Adesk::Boolean doZoom            ) = 0;

    virtual Acad::ErrorStatus
    setDefaultPlotConfig       (AcDbPlotSettings* pPlotSet      ) = 0;
};
#pragma pack (pop)
#endif // AD_DBPLOTSETVAL_H

