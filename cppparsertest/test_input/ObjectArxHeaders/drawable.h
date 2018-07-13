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
#ifndef __DRAWABLE_H
#define __DRAWABLE_H

#include "rxobject.h"
#include "rxoverrule.h"
#include "dbid.h"
#pragma pack (push, 8)


class AcGsModel;
class AcGiDrawableTraits;
class AcGiWorldDraw;
class AcGiViewportDraw;
class AcDbSubentId;
class AcDbExtents;
class AcGiDrawStream;

class ADESK_NO_VTABLE AcGiDrawable : public AcRxObject
{
public:

    ACRX_DECLARE_MEMBERS(AcGiDrawable);

    // Combine these flags in the return value
    // of setAttributes for efficiency of implementation
    // it is vital that if you use certain aspects of the
    // API that the correct flags be used. Otherwise the
    // display system may be incorrectly configured for
    // subsequent graphics. kIsCompoundObject gives
    // full access to the AcGi API, enabling the use
    // of draw() and the AcGi primitives together. Enabling
    // this makes the elaboration of an object marginally 
    // slower. So you should use the lowest value appropriate.
    //
    //
    enum SetAttributesFlags
    {
        // Default drawable, just uses acgi primitives and does not use 
        // nested calls to draw()
        kDrawableNone                           =  0, 

        // AcDbEntity derived classes (may require some special processing)
        kDrawableIsAnEntity                     =  1,

        // (block table record) Uses nesting but does not send down additional 
        // primitives. It uses draw() exclusively and makes no calls to the 
        // other AcGi primitives such as circle or shell
        kDrawableUsesNesting                    =  2,

        // You MUST specify this value if you nest entities as a block does.
        kDrawableIsCompoundObject               =  4, 
        
        // Drawable specifies when viewportDraw will be called.  Employ 
        // per-Viewport caching of viewportDraw geometry.  As well, this 
        // drawable does not use worldDraw.
        kDrawableViewIndependentViewportDraw    =  8,

        // If this entity is not visible (AcDbEntity::visibility())
        kDrawableIsInvisible                    =  16,

        // If a compound object has attributes it must specify this value
        kDrawableHasAttributes                  =  32,

        // If the geometry you elaborate is dependent on the regentype; for 
        // instance, if your drawable draws itself as a set of polygons in a 
        // "shaded" regen-mode but as a set of wires in "standard display", 
        // specify this flag
        kDrawableRegenTypeDependentGeometry     =  64,

        // Dimensions receive  special handling, behaving similarly to blocks
        kDrawableIsDimension = (kDrawableIsAnEntity + kDrawableIsCompoundObject + 128),

        // Always regenerate drawable
        kDrawableRegenDraw                      = 256,

        // Drawable has single level of detail for regen type 
        // kAcGiStandardDisplay 
        kDrawableStandardDisplaySingleLOD       = 512,

        // Drawable has single level of detail for regen type 
        // kAcGiShadedDisplay
        kDrawableShadedDisplaySingleLOD         = 1024,

        // Drawable requires viewportDraw be called on every view change.
        kDrawableViewDependentViewportDraw      =  2048,
      
        // Drawable requires unique viewportDraw elaboration for each block path.
        kDrawableBlockDependentViewportDraw     =  4096,

        // Drawable is an external reference 
        kDrawableIsExternalReference            =  8192,

        // Drawable will not be plotted
        kDrawableNotPlottable                   = 16384,

        // Drawable will never be drawn under the LCS mechanism 
        kDrawableNotAllowLCS                    = 32768,
        // this is used for wipeout plotting to pdf.
        kDrawableMergeControlOff                = 65536
    };


    // These are the Drawable types
    //
    enum DrawableType
    {
        kGeometry              = 0, 
        kDistantLight,
        kPointLight,            
        kSpotLight,
        kAmbientLight,
        kSolidBackground,
        kGradientBackground,
        kImageBackground,
        kGroundPlaneBackground,
        kViewport,
        kWebLight,
        kSkyBackground,
        kImageBasedLightingBackground
    };

#pragma warning(push)
#pragma warning(disable: 4481)
#pragma warning(disable: 4100)  // unreferenced formal params in RolloverHit()

    ACDBCORE2D_PORT  AcGiDrawable();
    ACDBCORE2D_PORT ~AcGiDrawable();

    // For default attributes
    ACDBCORE2D_PORT  ADESK_SEALED_VIRTUAL Adesk::UInt32   setAttributes   (AcGiDrawableTraits * traits) ADESK_SEALED;

    // For geometry shared between multiple viewports
    ACDBCORE2D_PORT  ADESK_SEALED_VIRTUAL Adesk::Boolean  worldDraw       (AcGiWorldDraw * wd) ADESK_SEALED;

    // For viewport-specific geometry
    ACDBCORE2D_PORT  ADESK_SEALED_VIRTUAL void            viewportDraw    (AcGiViewportDraw * vd) ADESK_SEALED;

    // For ViewIndependentViewportDraw caching
    // return bitwise combination of SetAttributesFlags
    // for now, 3D GS only investigates kDrawableRegenTypeDependentGeometry
	ACDBCORE2D_PORT  ADESK_SEALED_VIRTUAL Adesk::UInt32   viewportDrawLogicalFlags (AcGiViewportDraw * vd) ADESK_SEALED;

    // Persistent/transient
    virtual Adesk::Boolean  isPersistent    (void) const                    = 0;
    virtual AcDbObjectId    id              (void) const                    = 0;

    // Drawable type. 
    virtual DrawableType    drawableType    (void) const { return kGeometry; }

    // nMouseFlags are identical to the WM_MOUSEMOVE wParam windows message. See MSDN for those flags, they are provided as is.
    // reset is true if rollover is resetting or leaving your object.
    // return true if you want rollover to track your object, false to ignore it.
    virtual Adesk::Boolean  RolloverHit     (Adesk::ULongPtr /*nSubentId*/,
                                             Adesk::ULongPtr /*nMouseFlags*/,
                                             Adesk::Boolean  /*bReset*/)         { return Adesk::kFalse; }

    // Set the bounds of the drawable.  Return false if the drawable has no
    // bounds, the bounds cannot be set, or the method is unimplemented.
    virtual bool            bounds          (AcDbExtents& /*bounds*/) const { return false; }

    // Draw stream
    ACDBCORE2D_PORT virtual void            setDrawStream   (AcGiDrawStream * pStream);
    ACDBCORE2D_PORT virtual AcGiDrawStream* drawStream      (void) const;

#pragma warning(pop)

protected:
    friend class AcGiDrawableOverrule;

    virtual Adesk::UInt32   subSetAttributes   (AcGiDrawableTraits * traits)   = 0;

    virtual Adesk::Boolean  subWorldDraw       (AcGiWorldDraw * wd)            = 0;

    virtual void            subViewportDraw    (AcGiViewportDraw * vd)         = 0;

    virtual Adesk::UInt32   subViewportDrawLogicalFlags (AcGiViewportDraw * /*vd*/) { return 0; }

private:
    friend class AcGiDrawableAccessory;

    class AcGiDrawableAccessory* m_pAccessory;
};

/// <property name="versionspecific" value="=18.0.0.0" />
/// 
/// <description>
/// AcGiDrawableOverrule overrules a subset of draw related
/// operations that AcGiDrawable class specifies. It is intended
/// as a base class for clients who want to alter some or all
/// behavior of a given AcGiDrawable-derived class. At the base
/// level, each default implementation simply calls the
/// corresponding method in the target class.
/// </description>  
class AcGiDrawableOverrule : public AcRxOverrule
{
public:
    ACRX_DECLARE_MEMBERS(AcGiDrawableOverrule);

    ACDBCORE2D_PORT AcGiDrawableOverrule();
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcGiDrawable::setAttributes method.
    /// </description>
    /// <remarks>
    /// The default implementation of
    /// AcGiDrawableOverrule::setAttributes calls
    /// AcGiDrawable::subSetAttributes.
    /// </remarks>
    /// <param name="pSubject">Pointer to an AcRxObject that this
    ///                        overrule is applied against.</param>
    /// <param name="traits">Pointer to the graphics traits.</param>
    ACDBCORE2D_PORT virtual Adesk::UInt32   setAttributes (AcGiDrawable* pSubject, AcGiDrawableTraits * traits);
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcGiDrawable::worldDraw.
    /// </description>
    /// <param name="pSubject">Pointer to an AcRxObject that this
    ///                        overrule is applied against.</param>
    /// <param name="wd">Pointer to the graphics traits.</param>
    /// <remarks>
    /// The default implementation of AcGiDrawableOverrule::worldDraw
    /// calls the protected virtual AcGiDrawable::subWorldDraw
    /// method. 
    /// </remarks>                                                   
    ACDBCORE2D_PORT virtual Adesk::Boolean  worldDraw     (AcGiDrawable* pSubject, AcGiWorldDraw * wd);
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcGiDrawable::viewportDraw method.
    /// </description>
    /// <remarks>
    /// Default implementation of AcGiDrawableOverrule::viewportDraw
    /// calls protected virtual AcGiDrawable::subViewportDraw method.
    /// 
    /// </remarks>                                                   
    ACDBCORE2D_PORT virtual void            viewportDraw  (AcGiDrawable* pSubject, AcGiViewportDraw * vd);
    /// <property name="versionspecific" value="=18.0.0.0" />
    /// 
    /// <description>
    /// Overrules AcGiDrawable::viewportDrawLogicalFlags method.
    /// </description>
    /// <remarks>
    /// The default implementation of AcGiDrawableOverrule::
    /// viewportDrawLogicalFlags calls the protected virtual
    /// AcGiDrawable:: subViewportDrawLogicalFlags method. 
    /// </remarks>                                              
    ACDBCORE2D_PORT virtual Adesk::UInt32   viewportDrawLogicalFlags (AcGiDrawable* pSubject, AcGiViewportDraw * vd);
};

/// <description>
/// AcGiDrawableReactor provides notifications of key AcGiDrawable-
/// related events including begin/end regen, modification, and
/// erasure. Clients who derive from this class will receive these 
/// events after registering their reactor with 
/// acgiDrawableEvent->addReactor(). 
/// </description>  
class ACDBCORE2D_PORT AcGiDrawableReactor : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiDrawableReactor);

    /// <description>
    /// The graphics system which is regenerating the drawable.
    /// </description>
    enum RegenFlags
    {
        k2DRegen,
        k3DRegen
    };

    /// <description>
    /// This event signals the beginning of a drawable's regen.
    /// </description>
    /// <param name="pDrawable">Input drawable about to be regenerated.</param>
    /// <param name="flags">Input graphics system that will perform the regen. </param>
    virtual void beginRegen (AcGiDrawable* /*pDrawable*/, RegenFlags /*flags*/) {}

    /// <description>
    /// This event signals the end of a drawable's regen.
    /// </description>
    /// <param name="pDrawable">Input drawable that was regenerated.</param>
    /// <param name="flags">Input graphics system that performed the regen.</param>
    virtual void endRegen   (AcGiDrawable* /*pDrawable*/, RegenFlags /*flags*/) {}

    /// <description>
    /// This event signals the modification of a drawable's graphics.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were modified.</param>
    virtual void modified   (AcGiDrawable* /*pDrawable*/) {}

    /// <description>
    /// This event signals the erasure of a drawable's graphics.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were erased.</param>
    virtual void erased     (AcGiDrawable* /*pDrawable*/) {}

    /// <description>
    /// This event signals graphics are being handed over from one drawable to another drawable.
    /// </description>
    /// <param name="pDrawableFrom">Input drawable from which graphics will be handed over. </param>
    /// <param name="pDrawableTo">Input drawable to which graphics will be handed over. </param>
    virtual void handOverTo (AcGiDrawable* /*pDrawableFrom*/, AcGiDrawable* /*pDrawableTo*/) {}

    /// <description>
    /// This event signals the erasure of a drawable's graphics.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were erased.</param>
    /// <param name="parentID">Input id of parent drawable.</param>
    virtual void erased(AcGiDrawable* /*pDrawable*/, Adesk::IntDbId /*parentID*/) {}

    /// <description>
    /// This event signals the modification of a drawable's graphics.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were modified.</param>
    /// <param name="parentID">Input id of parent drawable.</param>
    virtual void modified(AcGiDrawable* /*pDrawable*/, Adesk::IntDbId /*parentID*/) {}

    /// <description>
    /// This event signals the addition of a drawable's graphics.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were added. </param>
    /// <param name="parentID">Input id of parent drawable.</param>
    /// <param name="databasePtr">Input database pointer cast as LONG_PTR.</param>
    virtual void added(AcGiDrawable* /*pDrawable*/, Adesk::IntDbId /*parentID*/, Adesk::LongPtr /*databasePtr*/) {}
};

/// <description>
/// AcGiDrawableEvent manages a set of AcGiDrawableReactors and sends 
/// notifications to them when certain events occur.  Access is through
/// a singleton instance of this class, acgiDrawableEvent. Clients of
/// AcGiDrawableEvent fall into three categories:
///
/// 1. Any client interested in making use of AcGiDrawableReactor must 
/// add and remove their reactor through addReactor/removeReactor.
///
/// 2. AcGiDrawable-derived clients may use this class to notify graphics 
/// systems of modifications and erasures of their graphics.
///
/// 3. Graphics systems may use this class to notify interested listeners
/// (e.g. AcGiDrawStream) of regen begin/end events.
/// </description>  
#define acgiDrawableEvent (&AcGiDrawableEvent::instance())

class AcGiDrawableEvent : public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcGiDrawableEvent);


    /// <description>
    /// This static method returns the singleton instance of this class.  Use the acgiDrawableEvent macro for convenience.
    /// </description>
    /// <returns>The one AcGiDrawableEvent.</returns>
    ACDBCORE2D_PORT static AcGiDrawableEvent& instance();

    /// <description>
    /// Add the reactor to the list of reactors that are notified when drawable events occur.
    /// </description>
    /// <param name="pReactor">Input reactor to enable notification of drawable events.</param>
    virtual void addReactor     (AcGiDrawableReactor* pReactor);

    /// <description>
    /// Remove the reactor from the list of reactors that are notified when drawable events occur.
    /// </description>
    /// <param name="pReactor">Input reactor to disable notification of drawable events. </param>
    virtual void removeReactor  (AcGiDrawableReactor* pReactor);

    /// <description>
    /// Signal the beginning of a drawable's regen to the list of reactors.
    /// </description>
    /// <param name="pDrawable">Input drawable about to be regenerated. </param>
    /// <param name="flags">Input graphics system that will perform the regen. </param>
    virtual void sendBeginRegen (AcGiDrawable* pDrawable, AcGiDrawableReactor::RegenFlags flags);

    /// <description>
    /// Signal the end of a drawable's regen to the list of reactors.
    /// </description>
    /// <param name="pDrawable">Input drawable that was regenerated.</param>
    /// <param name="flags">Input graphics system that performed the regen.</param>
    virtual void sendEndRegen   (AcGiDrawable* pDrawable, AcGiDrawableReactor::RegenFlags flags);

    /// <description>
    /// Signal the modification of a drawable's graphics to the list of reactors.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were modified. </param>
    virtual void sendModified   (AcGiDrawable* pDrawable);

    /// <description>
    /// Signal the erasure of a drawable's graphics to the list of reactors.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were erased. </param>
    virtual void sendErased     (AcGiDrawable* pDrawable);

    /// <description>
    /// Signal graphics are being handed over from one drawable to another drawable.
    /// </description>
    /// <param name="pDrawableFrom">Input drawable from which graphics will be handed over. </param>
    /// <param name="pDrawableTo">Input drawable to which graphics will be handed over. </param>
    virtual void sendHandOverTo (AcGiDrawable* pDrawableFrom, AcGiDrawable* pDrawableTo);

    /// <description>
    /// Signal the erasure of a drawable's graphics to the list of reactors.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were erased. </param>
    /// <param name="parentID">Input id of parent drawable.</param>
    virtual void sendErased     (AcGiDrawable* pDrawable, Adesk::IntDbId parentID);

    /// <description>
    /// Signal the modification of a drawable's graphics to the list of reactors.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were modified. </param>
    /// <param name="parentID">Input id of parent drawable.</param>
    virtual void sendModified   (AcGiDrawable* pDrawable, Adesk::IntDbId parentID);

    /// <description>
    /// Signal the addition of a drawable's graphics to the list of reactors.
    /// </description>
    /// <param name="pDrawable">Input drawable whose graphics were added. </param>
    /// <param name="parentID">Input id of parent drawable.</param>
    /// <param name="databasePtr">Input database pointer cast as LONG_PTR.</param>
    virtual void sendAdded      (AcGiDrawable* pDrawable, Adesk::IntDbId parentID, Adesk::LongPtr databasePtr);

private:
    AcGiDrawableEvent   ();
    AcGiDrawableEvent   (const AcGiDrawableEvent&);
    void operator=      (const AcGiDrawableEvent&);
   ~AcGiDrawableEvent   ();

    class AcGiImpDrawableEvent* m_pImp;
};

#pragma pack (pop)
#endif // __DRAWABLE_H
