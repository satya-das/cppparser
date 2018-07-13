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
// dmmapi.h
/// <summary>
/// this is the plot-time part of the Dwf Metadata Manager API
/// These notifications are sent only during the plot time portion of
/// a Publish to DWF operation. Additional notifications are sent from
/// the Publish code, before and after the plot time notifications
///
/// classes defined here include:
/// AcDMMSheetReactorInfo
/// AcDMMEntityReactorInfo
/// AcDMMReactor
/// </summary>


#ifndef _ACDMMAPI_H
#define _ACDMMAPI_H

// These are lightweight objects containing the data but not the complex
// behavior of the corresponding DWF toolkit object
#include "AdAChar.h"
#include "AcDMMEPlotProperty.h"
#include "AcDMMEPlotProperties.h"
#include "AcDMMutils.h"
#include "AcPlPlotLogger.h"
#include "Ac3dDwfNavTree.h"

///////////////////////////////////////////////////////////
// class AcDMMSheetReactorInfo
///////////////////////////////////////////////////////////
/// <summary>
/// This class is the context information supplied by the OnBeginSheet
/// and OnEndSheet notifiers of AcDMMReactor
/// You do not need to construct this class.
/// This is handed to the OnBeginSheet and OnEndSheet methods
/// </summary>
class AcDMMSheetReactorInfo
{
public:

    // Access to plot info:

    // Enums for returns, below.
    /// <summary>
    /// describes the plot area (what to plot) requested
    /// </summary>
    enum PlotArea {
        /// <summary>
        /// plot display, the visible portion of the picture
        /// </summary>
        kDisplay = 0,
        /// <summary>
        /// plot extents, i.e. all geometry
        /// </summary>
        kExtents = 1,
        /// <summary>
        /// plot the limits set by the user
        /// </summary>
        kLimits = 2,
        /// <summary>
        /// plot a named view
        /// </summary>
        kView,
        /// <summary>
        /// plot a user specified window - a rectangular area
        /// </summary>
        kWindow,
        /// <summary>
        /// plot the extents of the layout
        /// </summary>
        kLayout
    };

    /// <summary>
    /// how much camera rotation is applied for this plot
    /// </summary>
    enum PlotRotation {
        /// <summary>
        /// 0 degrees camera rotation
        /// </summary>
        k0degrees,
        /// <summary>
        /// 90 degrees camera rotation
        /// </summary>
        k90degrees,
        /// <summary>
        /// 180 degrees camera rotation, i.e., plot upside down
        /// </summary>
        k180degrees,
        /// <summary>
        /// 270 degrees camera rotation
        /// </summary>
        k270degrees
    };

    /// <summary>
    /// the configured media units. This will always be dimensional
    /// for DWF plots.
    /// </summary>
    enum PlotMediaUnits {
        /// <summary>
        /// using imperial units
        /// </summary>
        kInches,
        /// <summary>
        ///  using metric units
        /// </summary>
        kMillimeters,
        /// <summary>
        /// using dimensionaless raster units, not expected for DWF
        /// </summary>
        kPixels
    };

    /// <summary>
    /// provides access to the plotLogger object
    /// </summary>
    ///
    /// <returns>
    /// a pointer to an AcPlPlotLogger service
    /// </returns>
    ///
    virtual AcPlPlotLogger * GetPlotLogger() = 0;

    /// <summary>
    /// accessor for the database being plotted
    /// </summary>
    ///    
    /// <returns>
    /// a pointer to the database being plotted
    /// </returns>
    virtual AcDbDatabase* database()      const = 0;

    /// <summary>
    /// query the current plot status
    /// </summary> 
    /// <returns>
    /// true if the job has been cancelled or aborted
    /// </returns>
    ///
    /// <remarks>
    /// most useful in OnEndSheet callbacks
    /// </remarks>
    virtual bool    isPlotJobCancelled()    const = 0;

    /// <summary>
    /// This allows clients to add a list of properties 
    /// to the DWF file, to be associated with this page but not
    /// associated with any particular entity. These will be added
    /// to the page descriptor.
    /// </summary>
    ///
    /// <param name="props">
    /// a vector of AcDMMEPlotProperties
    /// </param>
    ///
    virtual void AddPageProperties(AcDMMEPlotPropertyVec props) = 0;

    /// <summary>
    /// This allows clients to add a list of resources (files)
    /// to the DWF file, to be associated with this page but not
    /// associated with any particular entity. 
    /// </summary>
    ///
    /// <param name="resources">
    /// a vector of AcDMMResourceInfo objects which include a mime 
    /// type, role and a full path to the resource to be added
    /// </param>
    ///
    virtual void AddPageResources(AcDMMResourceVec resources) = 0;

    ///////////////// WHAT TO PRINT /////////////////////////

    /// <summary>
    /// accessor for this sheet's unique identifier
    /// </summary>
    ///
    /// <returns>
    /// this returns a const pointer to the GUID assigned the first time this 
    /// layout was published (it gets reused on republish)
    /// </returns>
    virtual const ACHAR * UniqueLayoutId() = 0; 

    /// <summary>
    /// accessor for this layout's object ID
    /// </summary>
    /// <returns>
    /// AcDbLayout object ID
    /// </returns>
    virtual AcDbObjectId   plotLayoutId()           const = 0;

    /// <summary>
    /// is this the Model tab or a layout?
    /// </summary>
    ///
    /// <returns>
    /// true if this is the Model tab
    /// </returns>
    virtual bool           isModelLayout()          const = 0;

    // qv Plot Area of Print dialog
    /// <summary>
    /// accessor for the configured plot area (what to plot)
    /// </summary>
    ///
    /// <returns>
    /// a PlotArea enum
    /// </returns>
    ///
    virtual PlotArea plotArea() const = 0;

    /// <summary>
    /// accessor for the configured plot rotation (camera rotation)
    /// </summary>
    ///
    /// <returns>
    /// a PlotRotation enum
    /// </returns>
    ///
    virtual PlotRotation plotRotation() const = 0; 

    /// <summary>
    /// accessor for the configured plot media units
    /// </summary>
    ///
    /// <returns>
    /// a PlotMediaUnits enum
    /// </returns>
    ///
    virtual PlotMediaUnits plotMediaUnits() const = 0; 

    /// <summary>
    /// accessor for the configured paper scale. Divided by the
    /// drawing scale, this gives the plot scale in use
    /// </summary>
    ///
    /// <returns>
    /// the paper scale as a double precision number
    /// </returns>
    ///
    virtual double paperScale()                     const = 0; //

    /// <summary>
    /// accessor for the configured drawing scale aka model scale
    /// </summary>
    ///
    /// <returns>
    /// the drawing scale as a double precision number
    /// </returns>
    ///
    /// <remarks>
    /// this is useful when considered together with the paper scale
    /// the plot scale is "paper scale" : "drawing scale"
    /// </remarks>
    virtual double drawingScale()                   const = 0; //

    /// <summary>
    /// accessor for the x coordinate of the plot origin, in media units, 
    /// from the corner of the paper.
    /// </summary>
    ///
    /// <returns>
    /// the x coordinate of the plot origin, in media units, 
    /// from the corner of the paper. 
    /// </returns>
    ///
    /// <seealso cref="plotMediaUnits"/>
    /// <seealso cref="originY"/>
    /// <seealso cref="effectivePlotOffsetX"/>
    /// <seealso cref="effectivePlotOffsetY"/>
    /// <seealso cref="effectivePlotOffsetXdevice"/>
    /// <seealso cref="effectivePlotOffsetYdevice"/>
    ///
    virtual double originX()                        const = 0;

    /// <summary>
    /// accessor for the y coordinate of the plot origin, in media units, 
    /// from the corner of the paper.
    /// </summary>
    ///
    /// <returns>
    /// the y coordinate of the plot origin, in media units, 
    /// from the corner of the paper. 
    /// </returns>
    ///
    /// <seealso cref="plotMediaUnits"/>
    /// <seealso cref="originX"/>
    /// <seealso cref="effectivePlotOffsetX"/>
    /// <seealso cref="effectivePlotOffsetY"/>
    /// <seealso cref="effectivePlotOffsetXdevice"/>
    /// <seealso cref="effectivePlotOffsetYdevice"/>
    ///
    virtual double originY()                        const = 0;

    /// <summary>
    /// accessor for x coordinate of the lower left corner of the plot window
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the lower left corner of the plot window in world
    /// (model) coordinates
    /// </returns>
    ///
    /// <remarks>
    /// meaningful if plotArea() == kWindow; world coordinates
    /// </remarks>
    ///
    /// <seealso cref="plotArea"/>
    /// <seealso cref="plotWindowMinY"/>
    /// <seealso cref="plotWindowMaxX"/>
    /// <seealso cref="plotWindowMaxY"/>
    ///
    virtual double plotWindowMinX()                 const = 0; // 

    /// <summary>
    /// accessor for y coordinate of the lower left corner of the plot window
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the lower left corner of the plot window in world
    /// (model) coordinates
    /// </returns>
    ///
    /// <remarks>
    /// meaningful if plotArea() == kWindow; world coordinates
    /// </remarks>
    ///
    /// <seealso cref="plotArea"/>
    /// <seealso cref="plotWindowMinX"/>
    /// <seealso cref="plotWindowMaxX"/>
    /// <seealso cref="plotWindowMaxY"/>
    ///
    virtual double plotWindowMinY()                 const = 0; // 

    /// <summary>
    /// accessor for x coordinate of the upper right corner of the plot window
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the upper right corner of the plot window in world
    /// (model) coordinates
    /// </returns>
    ///
    /// <remarks>
    /// meaningful if plotArea() == kWindow; world coordinates
    /// </remarks>
    ///
    /// <seealso cref="plotArea"/>
    /// <seealso cref="plotWindowMinX"/>
    /// <seealso cref="plotWindowMinY"/>
    /// <seealso cref="plotWindowMaxY"/>
    ///
    virtual double plotWindowMaxX()                 const = 0; // 

    /// <summary>
    /// accessor for y coordinate of the upper right corner of the plot window
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the upper right corner of the plot window in world
    /// (model) coordinates
    /// </returns>
    ///
    /// <remarks>
    /// meaningful if plotArea() == kWindow; world coordinates
    /// </remarks>
    ///
    /// <seealso cref="plotArea"/>
    /// <seealso cref="plotWindowMinX"/>
    /// <seealso cref="plotWindowMinY"/>
    /// <seealso cref="plotWindowMaxX"/>
    ///
    virtual double plotWindowMaxY()                 const = 0; // 


    /// <summary>
    /// accessor for the name of the view bring plotted
    /// </summary>
    ///
    /// <returns>
    /// a null terminated string containing the view name
    /// </returns>
    ///
    /// <remarks>
    /// meaningful if plotArea() == kView; world coordinates
    /// </remarks>
    ///
    /// <seealso cref="plotArea"/>
    ///
    virtual const TCHAR*  viewPlotted()             const = 0; // 

    /// <summary>
    /// is a plot scale specified or is it scale "to fit"
    /// </summary>
    ///
    /// <returns>
    /// true if a plot scale was specified
    /// </returns>
    ///
    virtual bool isScaleSpecified()                 const = 0; //

    /// <summary>
    /// is hidden line removal configured?
    /// </summary>
    ///
    /// <returns>
    /// true if this plot is done with hidden line removal
    /// </returns>
    ///
    virtual bool areLinesHidden()                   const = 0; //

    /// <summary>
    /// are lineweights being plotted?
    /// </summary>
    ///
    /// <returns>
    /// true if lineweights are configured to be plotted
    /// </returns>
    ///
    virtual bool arePlottingLineWeights()           const = 0; //

    /// <summary>
    /// are lineweights being scaled?
    /// </summary>
    ///
    /// <returns>
    /// true if lineweights are being scaled
    /// </returns>
    ///
    virtual bool areScalingLineWeights()            const = 0; //

    // display extents; world coordinates

    /// <summary>
    /// accessor for x coordinate of the lower left corner of the display
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the lower left corner of the display window
    /// in world coordinates
    /// </returns>
    ///
    /// <seealso cref="AcDMMSheetReactorInfo.displayMinY"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMaxX"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMaxY"/>
    ///
    virtual double displayMinX()                    const = 0; //

    /// <summary>
    /// accessor for y coordinate of the lower left corner of the display
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the lower left corner of the display window
    /// in world coordinates
    /// </returns>
    ///
    /// <seealso cref="AcDMMSheetReactorInfo.displayMinX"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMaxX"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMaxY"/>
    ///
    virtual double displayMinY()                    const = 0; //

    /// <summary>
    /// accessor for x coordinate of the upper right corner of the display
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the upper right corner of the display window
    /// in world coordinates
    /// </returns>
    ///
    /// <seealso cref="AcDMMSheetReactorInfo.displayMinX"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMinY"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMaxY"/>
    ///
    virtual double displayMaxX()                    const = 0; //

    /// <summary>
    /// accessor for y coordinate of the upper right corner of the display
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the upper right corner of the display window
    /// in world coordinates
    /// </returns>
    ///
    /// <seealso cref="AcDMMSheetReactorInfo.displayMinX"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMinY"/>
    /// <seealso cref="AcDMMSheetReactorInfo.displayMaxX"/>
    ///
    virtual double displayMaxY()                    const = 0; //

    // unprintable area on the layout, measured from nearest edge, 
    // in PlotMediaUnits

    /// <summary>
    /// accessor for distance from the left edge of the paper to the
    /// left edge of the printable area
    /// </summary>
    ///
    /// <returns>
    /// distance from the left edge of the paper to the left edge of the 
    /// printable area, in the configured media units
    /// </returns>
    ///
    virtual double layoutMarginMinX()               const = 0; //

    /// <summary>
    /// accessor for distance from the bottom edge of the paper to the
    /// bottom edge of the printable area
    /// </summary>
    ///
    /// <returns>
    /// distance from the bottom edge of the paper to the bottom edge of the 
    /// printable area, in the configured media units
    /// </returns>
    ///
    virtual double layoutMarginMinY()               const = 0; //

    /// <summary>
    /// accessor for distance from the right edge of the paper to the
    /// right edge of the printable area
    /// </summary>
    ///
    /// <returns>
    /// distance from the right edge of the paper to the right edge of the 
    /// printable area, in the configured media units
    /// </returns>
    ///
    virtual double layoutMarginMaxX()               const = 0; //

    /// <summary>
    /// accessor for distance from the top edge of the paper to the
    /// top edge of the printable area
    /// </summary>
    ///
    /// <returns>
    /// distance from the top edge of the paper to the top edge of the 
    /// printable area, in the configured media units
    /// </returns>
    ///
    virtual double layoutMarginMaxY()               const = 0; //

    ///////////////////// HOW TO PRINT /////////////////////////////

    /// <summary>
    /// accessor for the width of the printable area
    /// </summary>
    ///
    /// <returns>
    /// the width of the printable area, in the configured media units
    /// </returns>
    ///
    virtual double printableBoundsX()               const = 0; //

    /// <summary>
    /// accessor for the height of the printable area
    /// </summary>
    ///
    /// <returns>
    /// the height of the printable area, in the configured media units
    /// </returns>
    ///
    virtual double printableBoundsY()               const = 0; //

    /// <summary>
    /// accessor for the width of the configured media
    /// </summary>
    ///
    /// <returns>
    /// the width of the configured media, in the configured media units
    /// </returns>
    ///
    virtual double maxBoundsX()                     const = 0; //

    /// <summary>
    /// accessor for the height of the configured media
    /// </summary>
    ///
    /// <returns>
    /// the height of the configured media, in the configured media units
    /// </returns>
    ///
    virtual double maxBoundsY()                     const = 0; //

    /// <summary>
    /// accessor for the configured vector resolution in dots per inch
    /// </summary>
    ///
    /// <returns>
    /// the configured vector resolution
    /// </returns>
    ///
    virtual double stepsPerInch()                  const = 0; //

    /// <summary>
    /// accessor for the configured device name (pc3 file or device name)
    /// </summary>
    ///
    /// <returns>
    /// the configured plotter name (pc3 file or device name)
    /// </returns>
    ///
    virtual const TCHAR* configuration()            const = 0;

    /// <summary>
    /// accessor for the plot to file path (directory)
    /// </summary>
    ///
    /// <returns>
    /// the plot to file path
    /// </returns>
    ///
    virtual const TCHAR* plotToFilePath()           const = 0;

    /// <summary>
    /// accessor for the plot to file filename
    /// </summary>
    ///
    /// <returns>
    /// the plot to file filename
    /// </returns>
    ///
    virtual const TCHAR* plotToFileName()           const = 0;

    /// <summary>
    /// accessor for the canonical name of the configured media size
    /// </summary>
    ///
    /// <returns>
    /// the canonical name of the configured media size
    /// </returns>
    ///
    virtual const TCHAR* canonicalMediaName()       const = 0;


    /// <summary>
    /// accessor for x coordinate of the lower left corner of the plot bounds
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the lower left corner of the plot bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) being plotted, regardless of plotArea()
    /// (Note: this is what is requested to be plotted; some clipping may occur
    /// depending on media size and rotation.)
    /// </remarks>
    virtual double plotBoundsMinX()                 const = 0; //

    /// <summary>
    /// accessor for y coordinate of the lower left corner of the plot bounds
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the lower left corner of the plot bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) being plotted, regardless of plotArea()
    /// (Note: this is what is requested to be plotted; some clipping may occur
    /// depending on media size and rotation.)
    /// </remarks>
    virtual double plotBoundsMinY()                 const = 0; //

    /// <summary>
    /// accessor for x coordinate of the upper right corner of the plot bounds
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the upper right corner of the plot bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) being plotted, regardless of plotArea()
    /// (Note: this is what is requested to be plotted; some clipping may occur
    /// depending on media size and rotation.)
    /// </remarks>
    virtual double plotBoundsMaxX()                 const = 0; //

    /// <summary>
    /// accessor for y coordinate of the upper right corner of the plot bounds
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the upper right corner of the plot bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) being plotted, regardless of plotArea()
    /// (Note: this is what is requested to be plotted; some clipping may occur
    /// depending on media size and rotation.)
    /// </remarks>
    virtual double plotBoundsMaxY()                 const = 0; //

    /// <summary>
    /// accessor for x coordinate of the lower left corner of the printable
    /// bounds
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the lower left corner of the layout (printable) bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) of the printable bounds of the medium 
    /// being plotted to. This may be larger or smaller than plotBounds...() 
    /// above, depending on what is being plotted, and the scale being used.
    /// For example, AutoCAD paperspace always plots to these bounds,
    /// trying to fit plotBounds into this rectangle (but not
    /// clipping to that rectangle.)  AutoCAD modelspace actually 
    /// plots the intersection of this rectangle (what *would* fit onto 
    /// the paper at the specified scale and offset) and plotBounds
    /// (what the user requested to plot.)  In this case, the
    /// plot is clipped.
    /// </remarks>
    virtual double layoutBoundsMinX()               const = 0; //

    /// <summary>
    /// accessor for y coordinate of the lower left corner of the printable
    /// bounds
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the lower left corner of the layout (printable) bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) of the printable bounds of the medium 
    /// being plotted to. This may be larger or smaller than plotBounds...() 
    /// above, depending on what is being plotted, and the scale being used.
    /// For example, AutoCAD paperspace always plots to these bounds,
    /// trying to fit plotBounds into this rectangle (but not
    /// clipping to that rectangle.)  AutoCAD modelspace actually 
    /// plots the intersection of this rectangle (what *would* fit onto 
    /// the paper at the specified scale and offset) and plotBounds
    /// (what the user requested to plot.)  In this case, the
    /// plot is clipped.
    /// </remarks>
    virtual double layoutBoundsMinY()               const = 0; //

    /// <summary>
    /// accessor for x coordinate of the upper right corner of the printable
    /// bounds
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the upper right corner of the layout (printable) bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) of the printable bounds of the medium 
    /// being plotted to. This may be larger or smaller than plotBounds...() 
    /// above, depending on what is being plotted, and the scale being used.
    /// For example, AutoCAD paperspace always plots to these bounds,
    /// trying to fit plotBounds into this rectangle (but not
    /// clipping to that rectangle.)  AutoCAD modelspace actually 
    /// plots the intersection of this rectangle (what *would* fit onto 
    /// the paper at the specified scale and offset) and plotBounds
    /// (what the user requested to plot.)  In this case, the
    /// plot is clipped.
    /// </remarks>
    virtual double layoutBoundsMaxX()               const = 0; //

    /// <summary>
    /// accessor for y coordinate of the upper right corner of the printable
    /// bounds
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the upper right corner of the layout (printable) bounds
    /// in world coordinates
    /// </returns>
    ///
    /// <remarks>
    /// the rectangle (in world coords) of the printable bounds of the medium 
    /// being plotted to. This may be larger or smaller than plotBounds...() 
    /// above, depending on what is being plotted, and the scale being used.
    /// For example, AutoCAD paperspace always plots to these bounds,
    /// trying to fit plotBounds into this rectangle (but not
    /// clipping to that rectangle.)  AutoCAD modelspace actually 
    /// plots the intersection of this rectangle (what *would* fit onto 
    /// the paper at the specified scale and offset) and plotBounds
    /// (what the user requested to plot.)  In this case, the
    /// plot is clipped.
    /// </remarks>
    virtual double layoutBoundsMaxY()               const = 0; //


    // May differ from origin, above, depending on rotation, scaling, etc.

    /// <summary>
    /// accessor for x coordinate of the effective plot origin
    /// in media units
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the x coordinate of the effective plot origin
    /// in configured media units
    /// </returns>
    ///
    virtual double effectivePlotOffsetX()           const = 0;   // in paper units

    /// <summary>
    /// accessor for y coordinate of the effective plot origin
    /// in media units
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the x coordinate of the effective plot origin
    /// in configured media units
    /// </returns>
    ///
    virtual double effectivePlotOffsetY()           const = 0;

    /// <summary>
    /// accessor for x coordinate of the effective plot origin
    /// in device coordinates (pixels)
    /// </summary>
    ///
    /// <returns>
    /// x coordinate of the x coordinate of the effective plot origin
    /// in device coordinates (pixels)
    /// </returns>
    ///
    virtual int    effectivePlotOffsetXdevice()     const = 0;   // in dev coords

    /// <summary>
    /// accessor for y coordinate of the effective plot origin
    /// in device coordinates (pixels)
    /// </summary>
    ///
    /// <returns>
    /// y coordinate of the x coordinate of the effective plot origin
    /// in device coordinates (pixels)
    /// </returns>
    ///
    virtual int    effectivePlotOffsetYdevice()     const = 0;

    /// <summary>
    /// Are we publishing a 3D DWF?
    /// </summary>
    ///
    /// <returns>
    /// returns true if the sheet is being published to a 3D DWF
    /// </returns>
    ///
    virtual bool    publishingTo3DDwf()     const = 0;

    /// <summary>
    /// Call this method to register the root of your Ac3DDwfNavTreeNode 
    /// during the Begin Sheet reactor call. Note the first client who 
    /// registers their root node wins. Root node that is set is used only
    /// at the end of End Sheet reactor call to publish the navigation tree.
    /// So it is OK to set a root node that is empty at the beginning of 
    /// Begin Sheet reactor call. 
    /// Since only the first client who register their nav tree root node wins,
    /// if the clients implements addChild and removeChild on Ac3dDwfNavTreeNode
    /// interface, other clients can get a chance to modify the navigation tree
    /// using addChild and removeChild
    /// </summary>
    ///
    /// <param name="root">
    /// a pointer to an Ac3dDwfNavTreeNode object that the clients wants
    /// to register.
    /// </param>
    ///
    /// <returns>
    /// returns true if successfully registers the Ac3dDwfNavTreeNode 
    /// passed in
    /// </returns>
    ///
    virtual bool set3dDwfNavigationTreeNode(const Ac3dDwfNavTreeNode* root) = 0;

    /// <summary>
    /// Call this method to get the current Ac3DDwfNavTreeNode root node. If 
    /// there is no root node registered, a NULL pointer is returned. If a root
    /// node is already registered, you can still modify the navigation tree,
    /// provided the client who registered the root node implements the addChild
    /// and removeChild methods.
    /// </summary>
    ///
    /// <returns>
    /// returns a pointer to the current Ac3dDwfNavTreeNode root node. If there is
    /// no root node registered, a NULL pointer is returned.
    /// </returns>
    ///
    virtual Ac3dDwfNavTreeNode* get3dDwfNavigationTreeNode() = 0;

public:
    /// <summary>
    /// destructor
    /// </summary>
    virtual ~AcDMMSheetReactorInfo() {};

protected:
    /// <summary>
    /// constructor - you don't construct this class. It is handed to you
    /// as context information in the reactor
    /// </summary>
    AcDMMSheetReactorInfo() {};
};



///////////////////////////////////////////////////////////
// class AcDMMEntityReactorInfo
///////////////////////////////////////////////////////////
/// <summary>
/// This class is the context information supplied by the OnBeginEntity
/// and OnEndEntity notifiers of AcDMMReactor
/// You do not need to construct this class.
/// This is handed to the OnBeginEntity and OnEndEntity methods
/// </summary>
class AcDMMEntityReactorInfo
{
public:

    ///////////////// Query functions  ////////////////////
    /// <summary>
    /// query the current plot status
    /// </summary> 
    /// <returns>
    /// true if cancelled or aborted
    /// </returns>
    ///
    /// <remarks>
    /// in case you'd like to know if the plot is being cancelled
    /// </remarks>
    virtual bool isCancelled()    const = 0;

    /// <summary>
    /// compute a unique entity id string
    /// </summary>
    ///
    /// <returns>
    /// dwg GUID + ASCII handles in xref path + object ASCII handle
    /// </returns>
    ///
    /// <remarks>
    /// This is handy for use as a unique Properties Id.
    /// </remarks>
    virtual const wchar_t * UniqueEntityId() = 0;

    
    /// <summary>
    /// accessor for the current entity 
    /// </summary>
    ///
    /// <returns>
    /// a pointer to the AcDbEntity
    /// </returns>
    ///
    /// <remarks>
    /// You'll use this to identify the entities of interest to you.
    /// </remarks>
    virtual AcDbEntity* entity()             const = 0;


    /// <summary>
    /// compute the effective layer ID
    /// </summary>
    ///
    /// <returns>
    /// the AcDbObjectId of the effective layer
    /// </returns>
    ///
    /// <remarks>
    /// useful for objects on Layer 0
    /// </remarks>
    virtual AcDbObjectId effectiveBlockLayerId()  const = 0;

    /// <summary>
    /// determine if this entity has already been assigned a Node
    /// </summary>
    ///
    /// <param name="node">
    /// an "out" parameter, a reference to the entity's node, if any
    /// </param>
    ///
    /// <param name="objIds">
    /// an additional AcDbObjectIdArray of objIds that should be empty if this
    /// entity is not part of a block, and should be array of objects ids of 
    /// each block that enclose this instance of the entity if it is part of
    /// a block. This is necessary to disambiguate multiple block insertions. 
    /// Most clients of the API will supply empty array here.
    /// </param>
    ///
    /// <returns>
    /// true if this entity has already been assigned a node
    /// false if no node has been assigned
    /// </returns>
    ///
    virtual bool GetCurrentEntityNode(AcDMMNode & node, AcDbObjectIdArray objIds) const = 0;

    /// <summary>
    /// fetch the next unused node number
    /// </summary>
    ///
    /// <returns>
    /// the next unused integer node number
    /// </returns>
    ///
    /// <remarks>
    /// client may assign Node name to this Node, it will initially have
    /// an empty string as its name. (Node name is optional.)
    /// </remarks>
    ///
    virtual int GetNextAvailableNodeId() const = 0;

    /// <summary>
    /// look up any entity ID in the map of Id to node, find out if a Node
    /// has already been assigned to a particular entity.
    /// </summary>
    ///
    /// <param name="id">
    /// the AcDbObjectId to look up
    /// </param>
    ///
    /// <param name="objIds">
    /// an additional AcDbObjectIdArray of objIds that should be empty if this
    /// entity is not part of a block, and should be array of objects ids of 
    /// each block that enclose this instance of the entity if it is part of
    /// a block. This is necessary to disambiguate multiple block insertions. 
    /// Most clients of the API will supply empty array here.
    /// </param>
    ///
    /// <param name="nodeId">
    /// "out" parameter, the NodeId for this entity, if one has already
    /// been assigned.
    /// </param>
    ///
    /// <returns>
    /// returns true if this entity has already been assigned a NodeId
    /// </returns>
    virtual bool GetEntityNode(AcDbObjectId id, AcDbObjectIdArray objIds, 
        int & nodeId) const = 0;

    /// <summary>
    /// finds a Node given its Id
    /// </summary>
    ///
    /// <param name="nodeId">
    /// the integer id of the Node to search for, should be > 0
    /// </param>
    ///
    /// <returns>
    /// NULL if node not found, otherwise returns a const pointer to the Node.
    /// </returns>
    ///
    virtual const AcDMMNode * GetNode(int nodeId) const = 0;


    /// <summary>
    /// provides access to the plotLogger object
    /// </summary>
    ///
    /// <returns>
    /// a pointer to an AcPlPlotLogger service
    /// </returns>
    ///
    virtual AcPlPlotLogger * GetPlotLogger() = 0;

    ///////////////// Feedback functions  /////////////////

    /// <summary>
    /// Determines which Node will be assigned to the current entity.
    /// This calls AddNodeToMaps or MapEntityToNode internally.
    /// </summary>
    ///
    /// <param name="nodeId">
    /// the NodeId to assign, should be > 0
    /// </param>
    ///
    /// <param name="objIds">
    /// an additional AcDbObjectIdArray of objIds that should be empty if this
    /// entity is not part of a block, and should be array of objects ids of 
    /// each block that enclose this instance of the entity if it is part of
    /// a block. This is necessary to disambiguate multiple block insertions. 
    /// Most clients of the API will supply empty array here.
    /// </param>
    ///
    /// <returns>
    /// returns true on success, false if this entity's nodeId has
    /// already been assigned or if an invalid nodeId is supplied.
    /// </returns>
    ///
    /// <remarks>
    /// It is neither necessary nor desirable to assign a Node to
    /// every entity. And it is not necessary to use this API to
    /// assign a Node to an entity, the method AddNodeToMap() is
    /// an alternate method of accomplishing this. To optimize DWF
    /// compression, Node Ids should be sequential whenever possible.
    /// Only add Nodes to entities for which you are publishing properties.
    /// </remarks>
    ///
    virtual bool SetCurrentNode(int nodeId, AcDbObjectIdArray objIds) = 0;

    /// <summary>
    /// allows client to change node name but not node number
    /// </summary>
    ///
    /// <param name="nodeNumber">
    /// the nodeNumber to operate on, should exist in the map 
    /// and should be > 0
    /// </param>
    ///
    /// <param name="name">
    /// the Node name to assign to the specified Node
    /// </param>
    /// 
    /// <returns>
    /// true on success, false if the Node doesn't exist
    /// </returns>
    virtual bool SetNodeName(int nodeNumber, const wchar_t *name) = 0;

    /// <summary>
    /// Allows a client to add free-floating AcDMMEPlotProperties objects.
    /// Each of these has a unique Id and may reference other 
    /// AcDMMEPlotProperties objects by Id.
    /// </summary>
    ///
    /// <param name="props">
    /// a const pointer to an AcDMMEPlotProperties object.
    /// </param>
    ///
    /// <returns>
    /// returns false on failure, e.g. if the properties are invalid
    /// </returns>
    ///
    /// <remarks>
    /// The DMM caches a vector of these objects until the end
    /// of the page. Multiple applications may contribute Properties from this
    /// or other entities The client assigns a unique Id to each Properties 
    /// object. A Properties object can includes other Properties objects by
    /// reference (using its Id) to avoid redundancy.
    /// The Properties objects will end up free floating in the page object 
    /// definition. Each has a unique string ID assigned by the client.
    /// Clients can associate Properties with a Node by using the related API
    /// AddPropertiesIds().
    /// The DMM will create one EPlotObject per Node and will have it
    /// refer to all the Properties (by Id) associated with that Node.
    /// Then the DMM creates one EPlotInstance with the node number and 
    /// the Object just created. 
    /// </remarks>
    ///
    virtual bool AddProperties(const AcDMMEPlotProperties * props) = 0;

    /// <summary>
    /// Assign a vector of AcDMMEplotProperties Ids to a Node.
    /// </summary>
    ///
    /// <param name ="IdVec">
    /// a vector of Unicode Id strings for AcDMMEplotProperties objects,
    /// all of which are to be associated with the specified NodeId.
    /// </param>
    ///
    /// <param name="node">
    /// the Node with which the IdVec should be associated. This node should
    /// be in the entity-nodeId map.
    /// </param>
    ///
    /// <returns>
    /// true on success
    /// </returns>
    ///
    /// <remarks>
    /// Here the client tells us which properties objects to
    /// associate with this Node. This is done by giving us
    /// a vector of unique properties Id strings. The DMM
    /// accumulates all the properties Ids from every entity and
    /// client that has a contribution for this node and eventually
    /// when it makes an Object for this node in the page object definition
    /// all of these properties Ids will be children in that Object's
    /// EPlotProperties element
    /// </remarks>
    ///
    virtual bool AddPropertiesIds(AcDMMStringVec * IdVec, AcDMMNode & node) = 0;


    /// <summary>
    /// Forces the graphic pipeline to be flushed, to ensure synchronization;
    /// when control returns, all geometry will have been pushed
    /// down to the driver. 
    /// </summary>
    ///
    virtual void flush()      = 0;

    /// <summary>
    /// If for any reason, you need to cancel the entire plot operation...
    /// </summary>
    /// 
    virtual void cancelTheJob()        = 0;

    /// <summary>
    /// assign a NodeId to any EntityId
    /// </summary>
    ///
    /// <param name="Id">
    /// the AcDbObjectId of the entity whose node Id is to be assigned
    /// </param>
    ///
    /// <param name="objIds">
    /// an additional AcDbObjectIdArray of objIds that should be empty if this
    /// entity is not part of a block, and should be array of objects ids of 
    /// each block that enclose this instance of the entity if it is part of
    /// a block. This is necessary to disambiguate multiple block insertions. 
    /// Most clients of the API will supply empty array here.
    /// </param>
    ///
    /// <param name="nodeId">
    /// the integer NodeId to be assigned to the specified entity,
    /// should be > 0.
    /// </param>
    ///
    /// <returns>
    /// returns false if the entity is already in the map or if it
    /// isn't possible to get the oldId of the entity. To optimize DWF
    /// compression, assign sequential Node Ids whenever possible.
    /// Also returns false if the nodeId is invalid i.e. less than 1.
    /// </returns>
    ///
    /// <remarks>
    /// if a "child" object is plotted before the "parent",
    /// this allows the child to determine the parent's Node ID
    /// </remarks>
    ///
    virtual bool AddNodeToMap(AcDbObjectId Id, AcDbObjectIdArray objIds, int nodeId) = 0;

    /// <summary>
    /// Call this method to add 3D DWF properties to entities when OnBeginEntity
    /// notification is received. You can call this n times to add n number of 
    /// properties.
    /// </summary>
    ///
    /// <param name="category">
    /// name of the category to which you want to add the property
    /// </param>
    ///
    /// <param name="name">
    /// property name
    /// </param>
    ///
    /// <param name="value">
    /// property value
    /// </param>
    ///
    /// <returns>
    /// returns true if property is added successfully
    /// </returns>
    ///
    virtual bool add3DDwfProperty(const wchar_t *category, const wchar_t *name, const wchar_t *value) = 0;

    /// <summary>
    /// Call this method to add 3D DWF properties to entities when OnBeginEntity
    /// notification is received. You can call this n times to add n number of 
    /// properties.
    /// </summary>
    ///
    /// <param name="category">
    /// name of the category to which you want to add the property
    /// </param>
    ///
    /// <param name="name">
    /// property name
    /// </param>
    ///
    /// <param name="ns">
    /// attribute namespace
    /// </param>
    ///
    /// <param name="nsUrl">
    /// attribute namespace url
    /// </param>
    ///
    /// <param name="attName">
    /// attribute name
    /// </param>
    ///
    /// <param name="attVal">
    /// attribute value
    /// </param>
    ///
    /// <returns>
    /// returns true if attribute is added successfully
    /// </returns>
    ///
    virtual bool add3DDwfAttribute(const wchar_t *category, const wchar_t *name, 
                                   const wchar_t *ns, const wchar_t *nsUrl,
                                   const wchar_t *attName, const wchar_t *attVal) = 0;

    /// <summary>
    /// Call this method to get an array of graphic Node ID's associated 
    /// with this entity
    /// </summary>
    ///
    /// <returns>
    /// returns the graphic Node ID's associated with entity
    /// </returns>
    virtual const AcArray<long>& getGraphicIDs() = 0;
    
    /// <summary>
    /// Call this  method to get the the block ref path for the current entity
    /// </summary>
    ///
    /// <returns>
    /// returns the block ref path for the current entity
    /// </returns>
    virtual const AcDbObjectIdArray& getEntityBlockRefPath() = 0;

public:
    /// <summary>
    /// destructor
    /// </summary>
    virtual ~AcDMMEntityReactorInfo() {};

protected:
    AcDMMEntityReactorInfo() {};
};

///////////////////////////////////////////////////////////////////
/// class AcDMMReactor
///////////////////////////////////////////////////////////////////
/// <summary>
/// Clients must derive from and instantiate this class.
/// These reactors are called only during Publish to DWF operations.
/// Clients are responsible for obtaining configuration data for their
/// metadata publication from the AcPublishReactor
/// </summary>
class AcDMMReactor : public AcRxObject // API
{
public:
    /// <summary>
    /// this reactor is called before any entities are plotted
    /// for this sheet, to let clients know about the sheet which
    /// is about to be plotted.
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcDMMSheetReactorInfo object is supplied
    /// to the reactor, providing both information and feedback
    /// functions to clients.
    /// </param>
    ///
    virtual void OnBeginSheet(AcDMMSheetReactorInfo * pInfo);

    /// <summary>
    /// this reactor is called before each entity is plotted. This
    /// allows a client to determine if this entity is one for which
    /// it will publiush metadata, and provides the APIs needed to
    /// associate a Node with this entity and to associate Properties
    /// with the Node. Clients should be parsimonious in assigning
    /// Nodes to entities.
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcDMMEntityReactorInfo object is supplied
    /// to the reactor, providing both information and feedback
    /// functions to clients.
    /// </param>
    ///
    virtual void OnBeginEntity(AcDMMEntityReactorInfo * pInfo);

    /// <summary>
    /// this reactor is called after each entity is plotted. 
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcDMMEntityReactorInfo object is supplied
    /// to the reactor, providing both information and feedback
    /// functions to clients.
    /// </param>
    ///
    virtual void OnEndEntity(AcDMMEntityReactorInfo * pInfo);

    /// <summary>
    /// this reactor is called after all entities on the sheet have been
    /// plotted, to let clients that plotting of the sheet is complete.
    /// At this time clients may add resources and/or properties to the
    /// sheet which are not associated with an specific entity.
    /// </summary>
    ///
    /// <param name="pInfo">
    /// a pointer to an AcDMMSheetReactorInfo object is supplied
    /// to the reactor, providing both information and feedback
    /// functions to clients.
    /// </param>
    ///
    virtual void OnEndSheet(AcDMMSheetReactorInfo * pInfo);

    /// <summary>
    /// destructor
    /// </summary>
    ///
    virtual ~AcDMMReactor() {};

protected:
    /// <summary>
    /// constructor
    /// protected, you must derive to instantiate one of these
    /// </summary>
    AcDMMReactor() {};
};

/// base class inlines for OnBegin and OnEnd methods
/// this is the default behavior for methods you choose
/// not to implement in your overridden reactor class
inline void AcDMMReactor::OnBeginSheet(AcDMMSheetReactorInfo * pInfo) {};
inline void AcDMMReactor::OnBeginEntity(AcDMMEntityReactorInfo * pInfo) {};
inline void AcDMMReactor::OnEndEntity(AcDMMEntityReactorInfo * pInfo) {};
inline void AcDMMReactor::OnEndSheet(AcDMMSheetReactorInfo * pInfo) {};

// Global functions that clients call to add and remove reactors

/// <summary>
/// the global function clients should call to add a reactor
/// </summary>
///
/// <param name="pReactor">
/// a pointer to the reactor the client has derived and instantiated
/// </param>
///
/// <remarks>
/// The AcDMMReactorManager, which is required to support these reactors,
/// only exists when AcPublish is running. The recommended practice is
/// to call this function in an AcPublishReactor OnAboutToBeginPublishing
/// and remove your DMM reactors in both OnEndPublish and in
/// OnCancelledOrFailedPublishing. Note that AcEPlotX must also be loaded
/// since that is where the AcDMMReactorManager is implemented.
/// </remarks>
///
void AcGlobAddDMMReactor(AcDMMReactor * pReactor);

/// <summary>
/// the global function clients should call to remove a reactor
/// </summary>
///
/// <param name="pReactor">
/// a pointer to the reactor the client has derived, instantiated and
/// previously added.
/// </param>
void AcGlobRemoveDMMReactor(AcDMMReactor * pReactor);

typedef void (__cdecl *ACGLOBADDDMMREACTOR)(AcDMMReactor * pReactor);
typedef void (__cdecl *ACGLOBREMOVEDMMREACTOR)(AcDMMReactor * pReactor);

#endif // _ACDMMAPI_H
