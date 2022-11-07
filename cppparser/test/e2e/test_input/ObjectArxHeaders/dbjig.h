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
// DESCRIPTION:
//      Definition of class AcEdJig, an object onto which you clamp an
//      AcDbEntity while bending it into shape.  Comes with slots for a
//      few standard dragging attachments and a built-in tool or two.
//  

#ifndef   _DBJIG_H_
#define   _DBJIG_H_ 1

#if defined(__cplusplus)
#include "AcCoreDefs.h"
#include "dbdimdata.h"  // for dynamic dimensions
#pragma pack (push, 8)

class AcEdImpJig;
class AcDbEntity;
class AcEdImpDragStyle;
class AcGePoint3d;
class AcGiVisualStyle;
class AcEdDragStyle;

class AcEdJig: public AcRxObject
{
public:
    ACRX_DECLARE_MEMBERS(AcEdJig);

    enum UserInputControls {
        kGovernedByOrthoMode            = 0x000001,
        kNullResponseAccepted           = 0x000002,
        kDontEchoCancelForCtrlC         = 0x000004,
        kDontUpdateLastPoint            = 0x000008,
        kNoDwgLimitsChecking            = 0x000010,
        kNoZeroResponseAccepted         = 0x000020,
        kNoNegativeResponseAccepted     = 0x000040,
        kAccept3dCoordinates            = 0x000080,
        kAcceptMouseUpAsPoint           = 0x000100,
        kAnyBlankTerminatesInput        = 0x000200,
        kInitialBlankTerminatesInput    = 0x000400,
        kAcceptOtherInputString         = 0x000800,
        kGovernedByUCSDetect            = 0x001000,
        kNoZDirectionOrtho              = 0x002000,
        kImpliedFaceForUCSChange        = 0x004000,
        kUseBasePointElevation          = 0x008000,

        ///<summary> Disables direct distance input. When this flag is ON a
        ///distance input such as integer or real will not be accepted unless
        ///kAcceptOtherInputString is ON, in that case returned DragStatus is
        ///kOther. </summary>
        kDisableDirectDistanceInput     = 0x010000,
    };

    enum DragStatus {
        kModeless       = -17,
        kNoChange       = -6,
        kCancel         = -4,
        kOther          = -3,
        kNull           = -1,
        kNormal         = 0,
        kKW1,
        kKW2,
        kKW3,
        kKW4,
        kKW5,
        kKW6,
        kKW7,
        kKW8,
        kKW9
    };

    enum CursorType {
        kNoSpecialCursor = -1,           // No Special Cursor Specified
        kCrosshair = 0,                  // Full Screen Cross Hair. 
        kRectCursor,                     // Rectangular cursor. 
        kRubberBand,                     // Rubber band line. 
        kNotRotated,                     // NotRotated Type. 
        kTargetBox,                      // Target Box Type. 
        kRotatedCrosshair,               // Rotated Crosshair w/ rubber band. 
        kCrosshairNoRotate,              // Crosshairs forced non-rotated. 
        kInvisible,                      // Invisible cursor. 
        kEntitySelect,                   // Entity selection target cursor. 
        kParallelogram,                  // Parallelogram cursor. 
        kEntitySelectNoPersp,            // Pickbox, suppressed in persp. 
        kPkfirstOrGrips,                 // Auto-select cursor. 
        kCrosshairDashed                 // 15 dashed style crosshair cursor

    };
    AcEdJig();
    virtual ~AcEdJig();

    DragStatus drag();
    ACCORE_PORT DragStatus drag ( const AcEdDragStyle& style );
    virtual DragStatus sampler(); 
    virtual Adesk::Boolean update();
    AcDbObjectId append();

    const ACHAR* keywordList();
    void        setKeywordList(const ACHAR*);

    const ACHAR* dispPrompt();
    void        setDispPrompt(const ACHAR*, ...);


    ACCORE_PORT DragStatus acquireString(ACHAR (&str)[2049]);
    DragStatus acquireAngle(double &ang);
    DragStatus acquireAngle(double &ang, const AcGePoint3d& basePnt);
    DragStatus acquireDist(double &dist);
    DragStatus acquireDist(double &dist, const AcGePoint3d& basePnt);
    DragStatus acquirePoint(AcGePoint3d&);
    DragStatus acquirePoint(AcGePoint3d&, const AcGePoint3d&basePnt);

    AcEdJig::CursorType specialCursorType();
    void                setSpecialCursorType(CursorType);

    AcEdJig::UserInputControls userInputControls();
    void                       setUserInputControls(AcEdJig::UserInputControls);

    virtual AcDbEntity* entity() const;
    virtual AcDbDimDataPtrArray * dimData(const double dimScale);
    virtual Acad::ErrorStatus setDimValue(const AcDbDimData* dimData,
                                          const double dimValue); 

private:
    AcEdImpJig*  mpImpJig;
};

/// <summary>
/// This class allows clients to define the visual styles for both the original and the
/// dragged entity during a drag operation.  The client can define the visual style by
/// either explicitly specifying the AcGiVisualStyle or by specifying a pre-set type
/// that is used to set the AcGiVisualStyle.
/// </summary>
class ACCORE_PORT AcEdDragStyle
{
public:

    /// <summary>
    /// Enumeration controlling the graphics representation of the drag entity during dragging process.
    /// </summary>
    enum StyleType
    {
        /// <summary> Dragger will not modify the entity's visual style during drag. </summary>
        kNone = 0, 
        
        /// <summary> Entity will be hidden during drag. </summary>
        kHide,
        
        /// <summary> The dragger will apply 25% transparency to entity. </summary>
        kTransparent25,

        /// <summary> The dragger will apply 75% transparency to entity. </summary>
        kTransparent75,

        /// <summary> The dragger will apply the deletion effect to entity. </summary>
        kDeletedEffect,

        /// <summary> The dragger will apply highlight effect to entity. </summary>
        kHighlight,

        /// <summary> Style was set by client calling setVisualStyle(). </summary>
        kNotSet
    };

    /// <summary> Default constructor. The entity will be displayed in its default visual
    /// style.  This is equivalent to setting the style type to kNone. </summary>
    AcEdDragStyle  ();

    /// <summary> Construct by specifying style types for original and dragged entity. </summary>
    AcEdDragStyle  ( StyleType styleTypeForOriginal, StyleType styleTypeForDragged );

    /// <summary> Copy constructor. </summary>
    AcEdDragStyle  ( const AcEdDragStyle& dragStyle );

    /// <summary> Destructor. </summary>
    ~AcEdDragStyle ();

    /// <summary> Return the style type that was used to define the original entity's visual style.</summary>
    /// <returns> StyleType enum value that was used to define the original entity's visual style.</returns>
    StyleType             styleTypeForOriginal () const;

    /// <summary> Return the style type that was used to define the dragged entity's visual style.</summary>
    /// <returns> StyleType enum value that was used to define the dragged entity's visual style.</returns>
    StyleType             styleTypeForDragged () const;

    /// <summary> Set the original entity's visual style by specifying a style type. </summary>
    /// <param name="styleType"> Style type for the original entity.</param>
    /// <returns> eOk if sucessful.</returns>
    Acad::ErrorStatus     setStyleTypeForOriginal ( StyleType styleType );

    /// <summary> Set the dragged entity's visual style by specifying a style type. </summary>
    /// <param name="styleType"> Style type for the dragged entity.</param>
    /// <returns> eOk if sucessful.</returns>
    Acad::ErrorStatus     setStyleTypeForDragged ( StyleType styleType );
    
    /// <summary> Assignment operator. </summary>
    AcEdDragStyle&  operator = ( const AcEdDragStyle& src );

    /// <summary> Test equality</summary>
    bool operator == ( const AcEdDragStyle& other ) const;
    bool operator != ( const AcEdDragStyle& other ) const;

private:
    AcEdImpDragStyle  *mpOriginalDragStyle;
    AcEdImpDragStyle  *mpDraggedDragStyle;

    friend class AcEdImpDragStyle;
};


#pragma pack (pop)
#endif // cplusplus
#endif
