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
//  dbosnap.h - public header file for custom osnap api
//

#ifndef _DBOSNAP_H
#define _DBOSNAP_H

#include "Adesk.h"

#pragma warning (disable: 4786)

#pragma pack (push, 8)

class AcDbCustomOsnapInfo : public AcRxObject {
public:
    ACRX_DECLARE_MEMBERS(AcDbCustomOsnapInfo);

virtual Acad::ErrorStatus   getOsnapInfo(
                           AcDbEntity*           pickedObject,
                           Adesk::GsMarker       gsSelectionMark,
                           const AcGePoint3d&    pickPoint,
                           const AcGePoint3d&    lastPoint,
                           const AcGeMatrix3d&   viewXform,
                           AcArray<AcGePoint3d>& snapPoints,
                           AcDbIntArray &     geomIdsForPts,
                           AcArray<AcGeCurve3d*>& snapCurves,
                           AcDbIntArray &     geomIdsForLines) = 0;
};





class AcGiGlyph : public AcGiDrawable
{
public:
    ACRX_DECLARE_MEMBERS(AcGiGlyph);

    // AcGiGlyph-specific member(s)
    //

    // setLocation
    //
    // Invoked from host application immediately prior to invoking
    // viewportDraw or worldDraw on the glyph.
    //
    virtual Acad::ErrorStatus setLocation(const AcGePoint3d& dcsPoint) = 0;

    // These don't apply to a glyph, and are implemented here as no-ops.
    //
    virtual Adesk::Boolean  isPersistent() const override { return Adesk::kFalse; }
    virtual AcDbObjectId    id() const override         { return 0; }

protected:
    // Glyphs typically draw viewport-specific graphics only.  Exceptions
    // are OK, if you have good cause.  If you do want worldDraw to be
    // called, then you must override the next two default implementations,
    // else they cause the system to go directly to the viewportDraw
    // member, after invoking setLocation() as described above.
    //
    virtual Adesk::UInt32   subSetAttributes(AcGiDrawableTraits*) override
                         { return 0; }

    // Glyphs typically draw viewport-specific graphics only.  Don't
    // override this unless you have good cause.
    //
    virtual Adesk::Boolean  subWorldDraw(AcGiWorldDraw*) override {return Adesk::kFalse;};

    // Here is what you really have to implement, accounting for location,
    // pixel/display coordinate size ratio and the osnapglyphsize setting.
    //
    virtual void            subViewportDraw(AcGiViewportDraw* vportDrawContext) override = 0;

};





class AcDbCustomOsnapMode {
  public:
    // Returns custom osnap keyword string that user must type in.
    // The actual text string which AutoCAD point acquisition and running OSNAP
    // modes will recognize. Both Local and Global strings will be searched
    // at runtime.  String should adhere to following rules:
    // As with builtin OSNAP modes, the strings should be
    // capitalized through the requisite minimum portion of the keyword,
    // after which is should be completed with lower case letters.
    // String should consist entirely of alphanumeric characters of the localized
    // language for localModeString, English for globalModeString, no blanks
    // tabs or punctuation permitted.
    // For example:  SOCket, requires at least "soc" to be entered.
    //
    virtual const ACHAR * localModeString() const = 0;
    virtual const ACHAR * globalModeString() const = 0;

    // An AcRxClass* pointer of a protocol extension class which will be associated
    // with all known entity classes that can support the new OSNAP mode.  This
    // class must be derived from a common class AcDbCustomOsnapInfo, described
    // next.  Then actual per-class protocol extension implementations of this
    // class must be associated with actual entity classes to perform per-entity
    // processing of the custom OSNAP mode.
    //
    virtual const AcRxClass* entityOsnapClass() const = 0;

    // OSNAP mode glyph.  See AcGiGlyph protocol in the following section.
    //
    // NULL is permissible if the developer does not want to specify a custom
    // glyph.
    //
    virtual AcGiGlyph* glyph() const = 0;

    // OSNAP mode glyph and default tooltip String.  String should be
    // localized.
    //
    // NULL is permissible, in which case the input keyword string will be
    // displayed.
    //
    virtual const ACHAR *               tooltipString() const = 0;
    virtual ~AcDbCustomOsnapMode() {}
};





// AcDbCustomOsnapManager defines the manager object for registered
// custom OSNAP modes.  Custom modes are registered and de-registered
// through this object, they can be activated and deactivated, and the
// set of currently active modes can be queried through this object.
//
class AcDbCustomOsnapManager {
public:
    virtual ~AcDbCustomOsnapManager() { }

    // addCustomOsnapMode
    //
    // used to add Custom OSNAP modes to the system. 
    // OSNAP modes with duplicate strings, local-to-local or
    // global-to-global, will result in addCustomOsnapMode returning
    // Acad::eDuplicateKey rather than Acad::eOk.
    // If the OSNAP Mode has either
    // a NULL local or global string, then Acad::eInvalidKey is returned.
    // If the OsnapMode object.  If the OSNAP modes' "entityOsnapClass"
    // member returns NULL, Acad::eInvalidInput.
    // There are no other error statuses for addCustomOsnapMode
    //
    virtual Acad::ErrorStatus addCustomOsnapMode(AcDbCustomOsnapMode* pMode) = 0;

    // removeCustomOsnapMode
    //
    // used to remove a custom OSNAP modes.
    // Acad::eOk is returned if the input address is found in the set
    // of registered OSNAP modes.
    // Acad::eKeyNotFound is returned otherwise. 
    //
    virtual Acad::ErrorStatus removeCustomOsnapMode(AcDbCustomOsnapMode* pMode) = 0;

    // activateOsnapMode
    //
    // Used to activate an OSNAP mode.  The input string is compared with
    // local mode strings if it does not begin with "_",, and with the
    // global mode strings if it DOES begin with "_".  The comparision is
    // made in a case-insensitive manner until a non-capitalized character
    // is encountered in the registered mode string, or until non-equal
    // characters are encountered. Possible return statuses are:
    // Acad::eOk is returned if mode was found and activated.
    // Acad::eKeyNotFound is returned if mode wasn't found.
    // Acad::eAlreadyActive (new status) is returned if mode was found but
    //                      is already active. 
    //
    virtual Acad::ErrorStatus activateOsnapMode(const ACHAR * modeStr) = 0;

    // deactivateOsnapMode
    //
    // Used to deactivate an OSNAP mode.  The same search rules and return
    // statuses apply as for activateOsnapMode, just the effect is reversed.
    // Except that instead of returning Acad::eAlreadyActive when a mode is
    // found that is already deactivated, new mode Acad::eAlreadyInactive
    // is returned.
    // 
    virtual Acad::ErrorStatus deactivateOsnapMode(const ACHAR * modeStr) = 0;

    // modeIsActive
    //
    // Is used to query whether a specified Osnap mode is active.
    // Returns Adesk::kTrue if the mode is registered and active, and
    // returns Adesk::kFalse otherwise.
    //
    virtual Adesk::Boolean modeIsActive(const ACHAR * modeStr) = 0;

    // osnapGlyphSize
    //
    // Indicates size of OSNAP glyphs in pixels, same as $APERTURE and
    // $PICKBOX system variables.
    // 
    virtual int osnapGlyphSize() const = 0;
};


AcDbCustomOsnapManager* acdbCustomOsnapManager();

extern "C" __declspec (dllexport)
bool acedIsOsnapOverride();

#pragma pack (pop)

#endif  // _DBOSNAP_H

