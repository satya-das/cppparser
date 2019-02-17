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
#ifndef __DBMLEADERSTYLE_H__
#define __DBMLEADERSTYLE_H__

#pragma once

#include "AcString.h"
#include "dbmain.h"

////////////////////////////////////////////////////////////////////////
// class AcDbMLeader
////////////////////////////////////////////////////////////////////////

/// <summary>
/// This class is the main class used for the multiple leader style object.
/// </summary>
///
/// <remarks>
/// </remarks>
///
class AcDbMLeaderStyle : public AcDbObject
{
public:
    /// <summary>
    /// This enum is content type of mleader.
    /// </summary>
    ///
    enum ContentType {
        /// <summary>
        /// mleader has none content
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kNoneContent                = 0,
        /// <summary>
        /// mleader has block content
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kBlockContent               = 1,
        /// <summary>
        /// mleader has mtext content
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kMTextContent               = 2,
        /// <summary>
        /// mleader has tolerance content
        /// </summary>
        ///
        /// <value>
        /// 3
        /// </value>
        kToleranceContent           = 3,
    };

    /// <summary>
    /// This enum is draw mleader order type.
    /// </summary>
    ///
    enum DrawMLeaderOrderType {
        /// <summary>
        /// draw mleader content first
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kDrawContentFirst           = 0,
        /// <summary>
        /// draw mleader leaderline first
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kDrawLeaderFirst            = 1
    };

    /// <summary>
    /// This enum is draw mleaderLine order type.
    /// </summary>
    ///
    enum DrawLeaderOrderType {
        /// <summary>
        /// draw leaderline head first
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kDrawLeaderHeadFirst        = 0,
        /// <summary>
        /// draw leaderline tail first
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kDrawLeaderTailFirst        = 1
    };

    /// <summary>
    /// This enum is leader type of mleader.
    /// </summary>
    ///
    enum LeaderType {
        /// <summary>
        /// invisible leader
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kInVisibleLeader            = 0,
        /// <summary>
        /// straight line leader
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kStraightLeader             = 1,
        /// <summary>
        /// spline line leader
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kSplineLeader               = 2
    };

    /// <summary>
    /// This enum is text attachment direction of mleader text content.
    /// </summary>
    ///
    enum TextAttachmentDirection {
        /// <summary>
        /// Horizontally attach to mtext content
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kAttachmentHorizontal       = 0,
        /// <summary>
        /// Vertically attach to mtext content
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kAttachmentVertical         = 1
    };

    /// <summary>
    /// This enum is text attachment type of mleader text content.
    /// </summary>
    ///
    enum TextAttachmentType {
        /// <summary>
        /// attach to top of top text line of mtext content
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kAttachmentTopOfTop         = 0,
        /// <summary>
        /// attach to middle of top text line of mtext content
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kAttachmentMiddleOfTop      = 1,
        /// <summary>
        /// attach to middle of mtext content
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kAttachmentMiddle           = 2,
        /// <summary>
        /// attach to middle of bottom text line of mtext content
        /// </summary>
        ///
        /// <value>
        /// 3
        /// </value>
        kAttachmentMiddleOfBottom   = 3,
        /// <summary>
        /// attach to bottom of bottom text line of mtext content
        /// </summary>
        ///
        /// <value>
        /// 4
        /// </value>
        kAttachmentBottomOfBottom   = 4,
        /// <summary>
        /// attach to bottom of bottom text line of mtext content and draw a underline
        /// </summary>
        ///
        /// <value>
        /// 5
        /// </value>
        kAttachmentBottomLine       = 5,
        /// <summary>
        /// attach to bottom of top text line of mtext content and draw a underline
        /// </summary>
        ///
        /// <value>
        /// 6
        /// </value>
        kAttachmentBottomOfTopLine  = 6,
        /// <summary>
        /// attach to bottom of top text line of mtext content
        /// </summary>
        ///
        /// <value>
        /// 7
        /// </value>
        kAttachmentBottomOfTop      = 7,
        /// <summary>
        /// attach to bottom of top text line of mtext content, and draw underline to whole mtext
        /// </summary>
        ///
        /// <value>
        /// 8
        /// </value>
        kAttachmentAllLine          = 8,
        /// <summary>
        /// vertically attach to center of mtext content top/bottom
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kAttachmentCenter           = 9,
        /// <summary>
        /// vertically attach to center of mtext content top/bottom, and draw a overline/underline
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kAttachmentLinedCenter      = 10
    };

    /// <summary>
    /// This enum is text angle type of mleader text content.
    /// </summary>
    ///
    enum TextAngleType {
        /// <summary>
        /// The direction of text is according to the last leaderline segment.
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kInsertAngle                = 0,
        /// <summary>
        /// The direction of text is always horizontal.
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kHorizontalAngle            = 1,
        /// <summary>
        /// The direction of text is according to the last leaderline segment and text is always right-side up.
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kAlwaysRightReadingAngle    = 2
    };

    /// <summary>
    /// This enum is text alignment type.
    /// </summary>
    ///
    enum TextAlignmentType {
        /// <summary>
        /// Left-justifies text in the MText.
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kLeftAlignment              = 0,
        /// <summary>
        /// Centers text in MText.
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kCenterAlignment            = 1,
        /// <summary>
        /// Right-justifies text in MText.
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kRightAlignment             = 2
    };

    /// <summary>
    /// This enum is block connection type of mleader block content.
    /// </summary>
    ///
    enum BlockConnectionType {
        /// <summary>
        /// Connect to extents of block.
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kConnectExtents             = 0,
        /// <summary>
        /// Connect to block base(origin) point.
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kConnectBase                = 1
    };

    /// <summary>
    /// This enum is leader direction type.
    /// </summary>
    ///
    enum LeaderDirectionType {
        /// <summary>
        /// unkown direction leader.
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kUnknownLeader              = 0,
        /// <summary>
        /// left leader.
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kLeftLeader                 = 1,
        /// <summary>
        /// right leader.
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kRightLeader                = 2,
        /// <summary>
        /// top leader.
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        kTopLeader                  = 3,
        /// <summary>
        /// bottom leader.
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        kBottomLeader               = 4
    };


    /// <summary>
    /// This enum is segment angle type.
    /// </summary>
    ///
    enum SegmentAngleType {
        /// <summary>
        /// Any degrees.
        /// </summary>
        ///
        /// <value>
        /// 0
        /// </value>
        kAny                        = 0, 
        /// <summary>
        /// 15 degrees.
        /// </summary>
        ///
        /// <value>
        /// 1
        /// </value>
        k15                         = 1,
        /// <summary>
        /// 30 degrees.
        /// </summary>
        ///
        /// <value>
        /// 2
        /// </value>
        k30                         = 2,
        /// <summary>
        /// 45 degrees.
        /// </summary>
        ///
        /// <value>
        /// 3
        /// </value>
        k45                         = 3,
        /// <summary>
        /// 60 degrees.
        /// </summary>
        ///
        /// <value>
        /// 4
        /// </value>
        k60                         = 4,
        /// <summary>
        /// 90 degrees.
        /// </summary>
        ///
        /// <value>
        /// 5
        /// </value>
        k90                         = 6,
        /// <summary>
        /// 180 degrees.
        /// </summary>
        ///
        /// <value>
        /// 6
        /// </value>
        kHorz                       = 12
    };

public:
    /// <summary>
    /// Default constructor.
    /// </summary>
    ///
    /// <remarks> 
    /// Default constructor.
    /// </remarks>
    ///
    AcDbMLeaderStyle();

    /// <summary>
    /// Default destructor.
    /// </summary>
    ///
    /// <remarks> 
    /// Default destructor.
    /// </remarks>
    ///
    virtual ~AcDbMLeaderStyle();

    ACDB_DECLARE_MEMBERS(AcDbMLeaderStyle);

    /// <summary>
    /// Get the name of AcDbMLeaderStyle
    /// </summary>
    ///
    /// <param name="pszName">
    /// Output the name of AcDbMLeaderStyle
    /// </param>
    ///
    /// <returns>
    /// Return Acae::eOk if Successful
    /// </returns>
    virtual Acad::ErrorStatus   getName(AcString & sName) const;
    virtual Acad::ErrorStatus   getName(ACHAR*& pszName) const final;   // deprecated

    /// <summary>
    /// Set the name of AcDbMLeaderStyle
    /// </summary>
    ///
    /// <param name="pszName">
    /// Input the name of AcDbMLeaderStyle
    /// </param>
    ///
    /// <returns>
    /// Return Acae::eOk if Successful
    /// </returns>
    virtual Acad::ErrorStatus   setName(const ACHAR * pszName);

    /// <summary>
    /// Return if the AcDbMLeaderStyle can be renamed.
    /// </summary>
    ///
    /// <returns>
    /// Return true if the AcDbMLeaderStyle is not Standard style.
    /// </returns>
    bool isRenamable() const;

    /// <summary>
    /// Return the pointer to a string containing the description of this mleader style.
    /// </summary>
    ///
    /// <returns>
    /// Return the pointer to a string containing the description of this mleader style.
    /// </returns>
    virtual const ACHAR*        description(void) const;

    /// <summary>
    /// Set the pointer to a string containing the description of this mleader style.
    /// </summary>
    ///
    /// <param name="pszDescription">
    /// Input the pointer to a string containing the description of this mleader style.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   setDescription(const ACHAR * pszDescription);

    /// <summary>
    /// Return an unsigned integer representing the operation bit set for the AcDbMLeaderStyle object.
    /// </summary>
    ///
    /// <returns>
    /// Return an unsigned integer representing the operation bit set for the AcDbMLeaderStyle object.
    /// </returns>
    virtual Adesk::UInt32       bitFlags() const;

    /// <summary>
    /// Set the operation bit set for the AcDbMLeaderStyle object.
    /// </summary>
    ///
    /// <param name="flags">
    /// Input the operation bit set for the AcDbMLeaderStyle object.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    virtual Acad::ErrorStatus   setBitFlags(Adesk::UInt32 flags);

    /// <summary>
    /// Set the content type of AcDbMLeaderStyle.
    /// </summary>
    ///
    /// <param name="contentType">
    /// Input the content type
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setContentType                (ContentType contentType);

    /// <summary>
    /// Return the content type of AcDbMLeaderStyle.
    /// </summary>
    ///
    /// <returns>
    /// Return the content type of AcDbMLeaderStyle.
    /// </returns>
    ContentType               contentType                   () const;

    /// <summary>
    /// Set the order of MLeader creation.
    /// </summary>
    ///
    /// <param name="drawMLeaderOrderType">
    /// Input the order of MLeader creation
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setDrawMLeaderOrderType       (DrawMLeaderOrderType drawMLeaderOrderType);

    /// <summary>
    /// Return the order of MLeader creation.
    /// </summary>
    ///
    /// <returns>
    /// Return the order of MLeader creation.
    /// </returns>
    DrawMLeaderOrderType      drawMLeaderOrderType          () const;

    /// <summary>
    /// Set the order of Leader line creation when creating a MLeader.
    /// </summary>
    ///
    /// <param name="drawLeaderOrderType">
    /// Input the order of Leader line creation when creating a MLeader
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setDrawLeaderOrderType        (DrawLeaderOrderType drawLeaderOrderType);

    /// <summary>
    /// Return the order of Leader line creation when creating a MLeader.
    /// </summary>
    ///
    /// <returns>
    /// Return the order of Leader line creation when creating a MLeader.
    /// </returns>
    DrawLeaderOrderType       drawLeaderOrderType           () const;

    /// <summary>
    /// Set the max number of segment points in leader lines.
    /// </summary>
    ///
    /// <param name="maxLeaderSegmentsPoints">
    /// Input the max number of segment points in leader lines
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    /// 
    /// <remarks>
    /// If maxLeaderSegmentsPoints is 0, the max number of points is unlimited.
    /// </remarks>
    Acad::ErrorStatus         setMaxLeaderSegmentsPoints    (int maxLeaderSegmentsPoints);

    /// <summary>
    /// Return the max number of segment points in leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Return the max number of segment points in leader lines.
    /// If the max number of points is unlimited, 0 will be returned.
    /// </returns>
    int                       maxLeaderSegmentsPoints       () const;

    /// <summary>
    /// Set the first segment angle constraint when creating a MLeader
    /// </summary>
    ///
    /// <param name="angle">
    /// Input the first segment angle constraint when creating a MLeader
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    /// 
    /// <remarks>
    /// If angle is kAny, the angle constraint is unused.
    /// </remarks>
    Acad::ErrorStatus         setFirstSegmentAngleConstraint (SegmentAngleType angle);

    /// <summary>
    /// Return the first segment angle constraint when creating a MLeader.
    /// </summary>
    ///
    /// <returns>
    /// Return the first segment angle constraint when creating a MLeader.
    /// If the angle constraint is unused, kAny will be returned.
    /// </returns>
    SegmentAngleType          firstSegmentAngleConstraint    () const;

    /// <summary>
    /// Set the second segment angle constraint when creating a MLeader
    /// </summary>
    ///
    /// <param name="angle">
    /// Input the second segment angle constraint when creating a MLeader
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful
    /// </returns>
    /// 
    /// <remarks>
    /// If angle is kAny, the angle constraint is unused.
    /// </remarks>
    Acad::ErrorStatus         setSecondSegmentAngleConstraint(SegmentAngleType angle);

    /// <summary>
    /// Return the second segment angle constraint when creating a MLeader.
    /// </summary>
    ///
    /// <returns>
    /// Return the second segment angle constraint when creating a MLeader.
    /// If the angle constraint is unused, kAny will be returned. 
    /// </returns>
    SegmentAngleType          secondSegmentAngleConstraint   () const;

    /// <summary>
    /// Set the leader line type.
    /// </summary>
    ///
    /// <param name="leaderLineType">
    /// Input the leader line type
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setLeaderLineType             (LeaderType leaderLineType);

    /// <summary>
    /// Return the leader line type.
    /// </summary>
    ///
    /// <returns>
    /// Return the leader line type.
    /// </returns>
    LeaderType                leaderLineType                () const;

    /// <summary>
    /// Set the color of leader lines.
    /// </summary>
    ///
    /// <param name="leaderLineColor">
    /// Input the color of leader lines
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setLeaderLineColor            (const AcCmColor& leaderLineColor);

    /// <summary>
    /// Return the color of leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Return the color of leader lines.
    /// </returns>
    AcCmColor                 leaderLineColor               () const;

    /// <summary>
    /// Set the linetype of leader lines.
    /// </summary>
    ///
    /// <param name="leaderLineTypeId">
    /// Input the linetype Id.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setLeaderLineTypeId           (AcDbObjectId leaderLineTypeId);

    /// <summary>
    /// Return the linetype Id of leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Return the linetype Id of leader lines.
    /// </returns>
    AcDbObjectId              leaderLineTypeId              () const;

    /// <summary>
    /// Set the line weight of leader lines.
    /// </summary>
    ///
    /// <param name="leaderLineWeight">
    /// Input the line weight of leader lines
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setLeaderLineWeight           (AcDb::LineWeight leaderLineWeight);

    /// <summary>
    /// Return the line weight of leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Return the line weight of leader lines.
    /// </returns>
    AcDb::LineWeight          leaderLineWeight              () const;

    /// <summary>
    /// Enable/disable landing of leader line.
    /// </summary>
    ///
    /// <param name="enableLanding">
    /// Input boolean to enable/disable landing of leader line.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// If disable landing, the landing gap will be ignored.
    /// </remarks>
    Acad::ErrorStatus         setEnableLanding              (bool enableLanding);

    /// <summary>
    /// Indicate whether landing of leader line is enabled.
    /// </summary>
    ///
    /// <returns>
    /// If landing of leader line is enabled, returns true; otherwise, returns false.
    /// </returns>
    bool                      enableLanding                 () const;

    /// <summary>
    /// Set the gap between MText and the tail of leader lines.
    /// </summary>
    ///
    /// <param name="landingGap">
    /// Input the gap between MText and the tail of leader lines.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setLandingGap                 (double landingGap);

    /// <summary>
    /// Return the gap between MText and the tail of leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Return the gap between MText and the tail of leader lines.
    /// </returns>
    double                    landingGap                    () const;

    /// <summary>
    /// Enable or disable dog-leg leader lines.
    /// </summary>
    ///
    /// <param name="enableDogleg">
    /// Input boolean to enable/disable dog-leg leader lines.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setEnableDogleg               (bool enableDogleg);

    /// <summary>
    /// Indicate whether dog-leg leader lines are enabled.
    /// </summary>
    ///
    /// <returns>
    /// Return true if dog-leg leader lines are enabled; otherwise, returns false.
    /// </returns>
    bool                      enableDogleg                  () const;

    /// <summary>
    /// Return the length of dog-leg leader line.
    /// </summary>
    ///
    /// <param name="doglegLength">
    /// Input the length of dog-leg leader line.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setDoglegLength               (double doglegLength);

    /// <summary>
    /// Return the length of dog-leg leader line.
    /// </summary>
    ///
    /// <returns>
    /// Return the length of dog-leg leader line.
    /// </returns>
    double                    doglegLength                  () const;

    /// <summary>
    /// Set the arrow symbol id by arrow name.
    /// </summary>
    ///
    /// <param name="name">
    /// Input the name of arrow symbol.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setArrowSymbolId              (const ACHAR* name);

    /// <summary>
    /// Set the arrow symbol by objectId.
    /// </summary>
    ///
    /// <param name="arrowSymbolId">
    /// Input the objectId of arrow symbol.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setArrowSymbolId              (AcDbObjectId arrowSymbolId);

    /// <summary>
    /// Return objectId of the arrow symbol.
    /// </summary>
    ///
    /// <returns>
    /// Return objectId of the arrow symbol.
    /// </returns>
    AcDbObjectId              arrowSymbolId                 () const;

    /// <summary>
    /// Set the arrow size.
    /// </summary>
    ///
    /// <param name="arrowSize">
    /// Input arrow size.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setArrowSize                  (double arrowSize);

    /// <summary>
    /// Return arrow size.
    /// </summary>
    ///
    /// <returns>
    /// Return arrow size.
    /// </returns>
    double                    arrowSize                     () const;

    /// <summary>
    /// Set the default text displayed in MText of balloon content.
    /// </summary>
    ///
    /// <param name="defaultMText">
    /// Input the default text displayed in MText of balloon content.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// This function just copies the mtext's content and fields.
    /// </remarks>
    Acad::ErrorStatus         setDefaultMText               (const AcDbMText* defaultMText);

    /// <summary>
    /// Return the default mtext
    /// </summary>
    ///
    /// <returns>
    /// Return the cloned mtext. If there is no default mtext, return NULL.
    /// </returns>
    AcDbMText*                defaultMText                  () const;

    /// <summary>
    /// Set text style by objectId.
    /// </summary>
    ///
    /// <param name="textStyleId">
    /// Input the objectId of text style.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setTextStyleId                (AcDbObjectId textStyleId);

    /// <summary>
    /// Return the objectId of text style.
    /// </summary>
    ///
    /// <returns>
    /// Return the objectId of text style.
    /// </returns>
    AcDbObjectId              textStyleId                   () const;

    /// <summary>
    /// Set the type of text attachment to specific direction leader.
    /// </summary>
    ///
    /// <param name="textAttachmentType">
    /// Input the type of text attachment.
    /// </param>
    /// <param name="leaderDirection">
    /// Input text leader direction type.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setTextAttachmentType         (TextAttachmentType textAttachmentType,
                                                             LeaderDirectionType leaderDirection);

    /// <summary>
    /// Returns text attachment type of specific direction leader.
    /// </summary>
    ///
    /// <param name="leaderDirection">
    /// Input text leader direction type.
    /// </param>
    ///
    /// <returns>
    /// Return text attachment type.
    /// </returns>
    TextAttachmentType        textAttachmentType            (LeaderDirectionType leaderDirection) const;

    /// <remarks>
    /// Deprecated: This method will be removed in a future release.
    /// Instead, use the method:
    /// <code>
    /// Acad::ErrorStatus setTextAttachmentType(TextAttachmentType textAttachmentType,
    ///                                         LeaderDirectionType leaderDirection);
    /// </code>
    /// </remarks>
    Acad::ErrorStatus         setTextAttachmentType         (TextAttachmentType textAttachmentType);

    /// <remarks>
    /// Deprecated: This method will be removed in a future release.
    /// Instead, use the method:
    /// <code>
    /// TextAttachmentType textAttachmentType(LeaderDirectionType leaderDirection) const;
    /// </code>
    /// </remarks>
    TextAttachmentType        textAttachmentType            () const;

    /// <summary>
    /// Set the angle type of text with respect to the last leader line segment.
    /// </summary>
    ///
    /// <param name="textAngleType">
    /// Input the angle type.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setTextAngleType              (TextAngleType textAngleType);

    /// <summary>
    /// Return the angle type of text with respect to the last leader line segment.
    /// </summary>
    ///
    /// <returns>
    /// Return the angle type of text with respect to the last leader line segment.
    /// </returns>
    TextAngleType             textAngleType                 () const;

    /// <summary>
    /// Set text alignment type.
    /// </summary>
    ///
    /// <param name="textAlignmentType">
    /// Input text alignment type.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setTextAlignmentType          (TextAlignmentType textAlignmentType);

    /// <summary>
    /// Return text alignment type.
    /// </summary>
    ///
    /// <returns>
    /// Return text alignment type.
    /// </returns>
    TextAlignmentType         textAlignmentType             () const;

    /// <summary>
    /// Input true to always align text on the left when creating a mleader.
    /// </summary>
    ///
    /// <param name="bAlwaysLeft">
    /// Input true to always align text on the left when creating a mleader.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setTextAlignAlwaysLeft        (bool bAlwaysLeft);

    /// <summary>
    /// Return true if always align text on the left when creating a mleader.
    /// </summary>
    ///
    /// <returns>
    /// Return true if always align text on the left when creating a mleader.
    /// </returns>
    bool                      textAlignAlwaysLeft           () const;

    /// <summary>
    /// Set text color of MText.
    /// </summary>
    ///
    /// <param name="textColor">
    /// Input the color.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setTextColor                  (const AcCmColor& textColor);

    /// <summary>
    /// Return text color of MText.
    /// </summary>
    ///
    /// <returns>
    /// Return text color of MText.
    /// </returns>
    AcCmColor                 textColor                     () const;

    /// <summary>
    /// Set the text height of MText.
    /// </summary>
    ///
    /// <param name="textHeight">
    /// Input text height.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setTextHeight                 (double textHeight);

    /// <summary>
    /// Return text height of MText.
    /// </summary>
    ///
    /// <returns>
    /// Return text height of MText.
    /// </returns>
    double                    textHeight                    () const;

    /// <summary>
    /// Display or hide text frame around the MText.
    /// </summary>
    ///
    /// <param name="enableFrameText">
    /// Input boolean to display/hide frame text.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setEnableFrameText            (bool enableFrameText);

    /// <summary>
    /// Indicate whether or not the text frame is displayed around the MText.
    /// </summary>
    ///
    /// <returns>
    /// Return true if the text frame is enabled; otherwise, return false.
    /// </returns>
    bool                      enableFrameText               () const;

    /// <summary>
    /// Set the alignment space value.
    /// </summary>
    ///
    /// <param name="alignSpace">
    /// Input alignment space value.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setAlignSpace                 (double alignSpace);

    /// <summary>
    /// Return alignment space value.
    /// </summary>
    ///
    /// <returns>
    /// Return alignment space value.
    /// </returns>
    double                    alignSpace                    () const;

    /// <summary>
    /// Set the Id of the block by name.
    /// </summary>
    ///
    /// <param name="name">
    /// Name of the built-in block.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setBlockId                    (const ACHAR* name);

    /// <summary>
    /// Set the Id of the block referenced by MLeader, it's a block table record id.
    /// </summary>
    ///
    /// <param name="blockId">
    /// Id of the block table record refenrenced by MLeader.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setBlockId                    (AcDbObjectId blockId);

    /// <summary>
    /// Return the Id of the block table record referenced by MLeader.
    /// </summary>
    ///
    /// <returns>
    /// Return the Id of the block table record referenced by MLeader.
    /// </returns>
    AcDbObjectId              blockId                       () const;

    /// <summary>
    /// Set block color in block content.
    /// </summary>
    ///
    /// <param name="blockColor">
    /// Input block color.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setBlockColor                 (const AcCmColor& blockColor);

    /// <summary>
    /// Return block color in block content.
    /// </summary>
    ///
    /// <returns>
    /// Return block color in block content.
    /// </returns>
    AcCmColor                 blockColor                    () const;

    /// <summary>
    /// Set the scale of the block referenced by MLeader.
    /// </summary>
    ///
    /// <param name="scale">
    /// Scale of the block refenrenced by MLeader.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    Acad::ErrorStatus         setBlockScale                 (const AcGeScale3d& scale);

    /// <summary>
    /// Return the sacle of the block referenced by MLeader.
    /// </summary>
    ///
    /// <returns>
    /// Return the sacle of the block referenced by MLeader.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    AcGeScale3d               blockScale                    () const;

    /// <summary>
    /// Disable/enable the blockScale value managed by setBlockScale().
    /// </summary>
    ///
    /// <param name="enableBlockScale">
    /// Input boolean to disable/enable blockScale.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    Acad::ErrorStatus         setEnableBlockScale           (bool enableBlockScale);

    /// <summary>
    /// Indicate whether the blockScale value managed by setBlockScale() works.
    /// </summary>
    ///
    /// <returns>
    /// Return true if the blockScale is enabled; otherwise, return false.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    bool                      enableBlockScale              () const;

    /// <summary>
    /// Set the rotation of the block referenced by MLeader.
    /// </summary>
    ///
    /// <param name="rotation">
    /// Rotation of the block refenrenced by MLeader.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    Acad::ErrorStatus         setBlockRotation              (double rotation);

    /// <summary>
    /// Return the rotation of the block referenced by MLeader.
    /// </summary>
    ///
    /// <returns>
    /// Return the rotation of the block referenced by MLeader.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    double                    blockRotation                 () const;

    /// <summary>
    /// Disable/enable the blockRotation value managed by setBlockRotation().
    /// </summary>
    ///
    /// <param name="enableBlockRotation">
    /// Input boolean to disable/enable blockRotation.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    Acad::ErrorStatus         setEnableBlockRotation        (bool enableBlockRotation);

    /// <summary>
    /// Indicate whether the blockRotation value managed by setBlockRotation() works.
    /// </summary>
    ///
    /// <returns>
    /// Return true if the blockRotation is enabled; otherwise, returns false.
    /// </returns>
    ///
    /// <remarks>
    /// Currently AutoCAD and the ARX API libraries make no use of this method.
    /// This method is deprecated and will be removed in a future version.
    /// </remarks>
    bool                      enableBlockRotation           () const;

    /// <summary>
    /// Set block connection type.
    /// </summary>
    ///
    /// <param name="blockConnectionType">
    /// Input block connection type.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setBlockConnectionType        (BlockConnectionType blockConnectionType);

    /// <summary>
    /// Return block connection type.
    /// </summary>
    ///
    /// <returns>
    /// Return block connection type.
    /// </returns>
    BlockConnectionType       blockConnectionType           () const;

    /// <summary>
    /// Set the scale of mleader created by this style.
    /// </summary>
    ///
    /// <param name="scale">
    /// Scale of mleader created by this style.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setScale                      (double scale);

    /// <summary>
    /// Return the scale of mleader created by this style.
    /// </summary>
    ///
    /// <returns>
    /// Return the scale of mleader created by this style.
    /// </returns>
    double                    scale                         () const;

    /// <summary>
    /// Indicate whether properties were changed.
    /// </summary>
    ///
    /// <returns>
    /// Return true if properties were changed; otherwise, returns false.
    /// </returns>
    bool                      overwritePropChanged          () const;

    /// <summary>
    /// Add this AcDbMLeaderStyle into database.
    /// </summary>
    ///
    /// <param name="pDb">
    /// Pointer of the database which will hold the style
    /// </param>
    /// <param name="styleName">
    /// Name of the MLeader Style
    /// </param>
    /// <param name="mleaderStyleId">
    /// Output the AcDbObjectId of the AcDbMLeaderStyle posted into database
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         postMLeaderStyleToDb          (AcDbDatabase* pDb, const ACHAR* styleName, AcDbObjectId & mleaderStyleId);

    /// <summary>
    /// Set the annotative status of AcDbMLeaderStyle.
    /// </summary>
    ///
    /// <param name="isAnnotative">
    /// New annotative status for AcDbMLeaderStyle
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setAnnotative              (bool isAnnotative);

    /// <summary>
    /// Return AcDbMLeaderStyle's annotative status.
    /// </summary>
    ///
    /// <returns>
    /// Return true if this is a annotative AcDbMLeaderStyle;
    /// Otherwise, return false.
    /// </returns>
    bool                      annotative                 () const;

    /// <summary>
    /// Set the break size used for breaking leader lines.
    /// </summary>
    ///
    /// <param name="size">
    /// Size specifies the gap used for breaking leader lines.
    /// </param>
    ///
    /// <returns>
    /// Return Acad::eOk if successful.
    /// </returns>
    Acad::ErrorStatus         setBreakSize (double size);

    /// <summary>
    /// Return the size of the gap used for breaking leader lines.
    /// </summary>
    ///
    /// <returns>
    /// Return the size of the gap used for breaking leader lines.
    /// </returns>
    double                    breakSize () const;

    /// <summary>
    /// Sets text attachment Direction of MText content.
    /// </summary>
    ///
    /// <param name="textAttachmentDirection">
    /// Input text attachment direction defined in AcDbMLeaderStyle::TextAttachmentDirection.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus         setTextAttachmentDirection(AcDbMLeaderStyle::TextAttachmentDirection textAttachmentDirection);

    /// <summary>
    /// Gets text attachment direction of MText content.
    /// </summary>
    ///
    /// <returns>
    /// Returns text attachment direction of MText content.
    /// </returns>
    ///
    TextAttachmentDirection   textAttachmentDirection() const;

    /// <summary>
    /// Sets if horizontal leader lines are automatically extended to text.
    /// </summary>
    ///
    /// <param name="value">
    /// Input boolean to make the automatically leader extension on/off.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    Acad::ErrorStatus setExtendLeaderToText(bool value);

    /// <summary>
    /// Gets if horizontal leader lines are automatically extended to text.
    /// </summary>
    ///
    /// <returns>
    /// Returns true if horizontal leader lines are automatically extended to text; otherwise, returns false.
    /// </returns>
    ///
    bool extendLeaderToText() const;

protected:

    /// <summary>
    /// Gets corresponding COM wrapper class ID.
    /// </summary>
    ///
    /// <param name="pClsid">
    /// OutPut corresponding COM wrapper class ID.
    /// </param>
    ///
    /// <returns>
    /// Returns Acad::eOk if successful.Return values for errors are implementation-dependent.
    /// </returns>
    ///
    virtual Acad::ErrorStatus subGetClassID                    (CLSID* pClsid) const override;
};

// Deprecated method. Please use the overload taking AcString & arg
inline Acad::ErrorStatus AcDbMLeaderStyle::getName(ACHAR*& pName) const
{
    return ::acutGetAcStringConvertToAChar(this, &AcDbMLeaderStyle::getName, pName);
}

#endif // __DBMLEADERSTYLE_H__

