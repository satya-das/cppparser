
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
//
// Visual Styles AcGi interfaces
//

#pragma once

#include "acgi.h"

class AcGiImpVisualStyle;

/// <summary>
/// Container for visual style property related enumerations.
/// </summary>
namespace AcGiVisualStyleProperties
{
    /// <summary>
    /// Describes the properties that can be set/get on a visual style.
    /// </summary>
    enum Property {
        /// <summary>
        /// Invalid property.
        /// </summary>
        kInvalidProperty = -1,

        // Face properties
        //

        /// <summary>
        /// See FaceLightingModel summary.
        /// </summary>
        kFaceLightingModel,

        /// <summary>
        /// See FaceLightingQuality summary.
        /// </summary>
        kFaceLightingQuality,

        /// <summary>
        /// See FaceColorMode summary.
        /// </summary>
        kFaceColorMode,

        /// <summary>
        /// See FaceModifiers summary.
        /// </summary>
        kFaceModifiers,

        /// <summary>
        /// Double indicating the level of face opacity in the range from 
        /// 0.0 to 1.0, with 1.0 representing full opacity (0% transparent) 
        /// and 0.0 representing no opacity (100% transparent).
        /// </summary>
        kFaceOpacity,

        /// <summary>
        /// Double representing the specular highlight amount (indicating 
        /// reflection and shininess values) of the material that is applied 
        /// to faces. 
        /// </summary>
        kFaceSpecular,

        /// <summary>
        /// AcCmColor representing the color applied to produce a "monochromatic" effect on faces.
        /// </summary>
        kFaceMonoColor,

        // Edge properties
        //

        /// <summary>
        /// See EdgeModel summary.
        /// </summary>
        kEdgeModel,    

        /// <summary>
        /// See EdgeStyles summary.
        /// </summary>
        kEdgeStyles,    

        /// <summary>
        /// AcCmColor representing the color applied to intersection edges.
        /// </summary>
        kEdgeIntersectionColor,  

        /// <summary>
        /// AcCmColor representing the color applied to obscured edges.
        /// </summary>
        kEdgeObscuredColor,    

        /// <summary>
        /// EdgeLinePattern applied to obscured edges.
        /// See EdgeLinePattern summary.
        /// </summary>
        kEdgeObscuredLinePattern,  

        /// <summary>
        /// EdgeLinePattern applied to intersection edges.
        /// See EdgeLinePattern summary.
        /// </summary>
        kEdgeIntersectionLinePattern,

        /// <summary>
        /// Double, in degrees, indicating the angle threshold above which 
        /// facet edges between adjoining facets will be displayed.
        /// </summary>
        kEdgeCreaseAngle,

        /// <summary>
        /// See EdgeModifier summary.
        /// </summary>
        kEdgeModifiers,

        /// <summary>
        /// AcCmColor representing the color applied to edges.
        /// </summary>
        kEdgeColor,

        /// <summary>
        /// Double indicating the level of edge opacity in the range from 
        /// 0.0 to 1.0, with 1.0 representing full opacity (0% transparent) 
        /// and 0.0 representing no opacity (100% transparent).
        /// </summary>
        kEdgeOpacity,

        /// <summary>
        /// Int representing edge width in pixels.
        /// </summary>
        kEdgeWidth,

        /// <summary>
        /// Int representing the amount, in pixels, that edges should overhang
        /// their start and end points.
        /// </summary>
        kEdgeOverhang,

        /// <summary>
        /// See EdgeJitterAmount summary.
        /// </summary>
        kEdgeJitterAmount,

        /// <summary>
        /// AcCmColor representing the color applied to silhouette edges.
        /// </summary>
        kEdgeSilhouetteColor,

        /// <summary>
        /// Short representing silhouette edge width in pixels.
        /// </summary>
        kEdgeSilhouetteWidth,

        /// <summary>
        /// Int from 0 to 100 representing the halo gap.
        /// </summary>
        kEdgeHaloGap,

        /// <summary>
        /// Unsigned short, between 0 and 2047, indicating the number of 
        /// isolines to display for curved surfaces.
        /// </summary>
        kEdgeIsolines,

        /// <summary>
        /// Bool indicating hide precision enabled. True if enabled,
        /// false otherwise.
        /// </summary>
        kEdgeHidePrecision,

        // Display properties
        //

        /// <summary>
        /// See DisplayStyles summary.
        /// </summary>
        kDisplayStyles,

        /// <summary>
        /// Double indicating brightness.
        /// </summary>
        kDisplayBrightness,

        /// <summary>
        /// See DisplayShadowType summary.
        /// </summary>
        kDisplayShadowType,

        /// <summary>
        /// Bool indicating use DB display draw order. True if enabled,
        /// false otherwise. When true Z depth is ignored for draw order.
        /// </summary>
        kUseDrawOrder,

        /// <summary>
        /// Bool indicating if viewport transparency is enabled.  True if enabled,
        /// false otherwise.
        /// </summary>
        kViewportTransparency,

        /// <summary>
        /// Bool indicating if lighting is enabled. True if enabled, false
        /// otherwise.
        /// </summary>
        kLightingEnabled,

        /// <summary>
        /// Bool indicating use Posterize global effect. True if enabled,
        /// false otherwise.
        /// </summary>
        kPosterizeEffect,

        /// <summary>
        /// Bool indicating use Mono global effect. True if enabled,
        /// false otherwise.
        /// </summary>
        kMonoEffect,

        /// <summary>
        /// Bool indicating use Blur global effect. True if enabled,
        /// false otherwise.
        /// </summary>
        kBlurEffect,

        /// <summary>
        /// Bool indicating use Pencil global effect. True if enabled,
        /// false otherwise.
        /// </summary>
        kPencilEffect,

        /// <summary>
        /// Bool indicating use Bloom global effect. True if enabled,
        /// false otherwise.
        /// </summary>
        kBloomEffect,

        /// <summary>
        /// Bool indicating use Pastel global effect. True if enabled,
        /// false otherwise.
        /// </summary>
        kPastelEffect,

        /// <summary>
        /// Int indicating blur amount. Range [0.0f, 5.0f].
        /// </summary>
        kBlurAmount,

        /// <summary>
        /// Float indicating the angle para of pencil effect. Range [0.0f, 360.0f].
        /// </summary>
        kPencilAngle,

        /// <summary>
        /// Int indicating the scale para of pencil effect. Range [0.0f, 3.0f].
        /// </summary>
        kPencilScale,

        /// <summary>
        /// Int indicating the pattern para of pencil effect. Range [0, 3].
        /// </summary>
        kPencilPattern,

        /// <summary>
        /// AcCmColor indicating the color para of pencil effect.
        /// </summary>
        kPencilColor,

        /// <summary>
        /// Float indicating the bright threshold para of bloom effect. Range [0.0f, INF].
        /// </summary>
        kBloomThreshold,

        /// <summary>
        /// Float indicating the radius para of bloom effect. Range [1.0f, 5.0f].
        /// </summary>
        kBloomRadius,

        /// <summary>
        /// AcCmColor indicating the tint color para.
        /// </summary>
        kTintColor,

        /// <summary>
        /// Bool indicating the contrast/brightness/power functions are applied
        /// false otherwise.
        /// </summary>
        kFaceAdjustment,

        /// <summary>
        /// Adjust overall contrast of image, higher giving more contrast.
        /// </summary>
        kPostContrast,

        /// <summary>
        /// Adjust overall brightness of image, higher making it brighter. 
        /// </summary>
        kPostBrightness,

        /// <summary>
        /// Change the power response curve. For example, gamma correction
        /// is a setting of about 0.4. However, this control is meant more
        /// as a way to control the appearance of the mid-tones: a lower number
        /// brightens the midtones more.
        /// </summary>
        kPostPower,

        /// <summary>
        /// Bool indicating the tint color is used. True if enabled,
        /// false otherwise.
        /// </summary>
        kTintEffect,

        /// <summary>
        /// Float indicating the intensity of bloom effect. Range [0.0f, INF].
        /// </summary>
        kBloomIntensity,

        /// <summary>
        /// AcCmColor overrides the color of drawables
        /// </summary>
        kColor,

        /// <summary>
        /// Float overrides the transparency of drawables. Range [0.0f, INF].
        /// </summary>
        kTransparency,

        /// <summary>
        /// Int indicating the amount of wiggle.
        /// </summary>
        kEdgeWiggleAmount,

        /// <summary>
        /// String overrides the edge texture path of drawables.
        /// </summary>
        kEdgeTexturePath,

        /// <summary>
        /// Bool. Camera Effect. Keep objects in focus whose distance from the camera is within
        /// the Focus Width around the Focus Distance.
        /// </summary>
        kDepthOfField,

        /// <summary>
        /// Float specifies the distance from the camera to focus on.
        /// </summary>
        kFocusDistance,

        /// <summary>
        /// Float specifies the distance from the focus distance to keep in focus.
        /// </summary>
        kFocusWidth,

        /// <summary>
        /// The number of visual style properties
        /// </summary>
        // NOTE!!! All new properties should be added immediately above kPropertyCount.
        kPropertyCount,

        /// <summary>
        /// The number of visual style properties for Pre-2013 drawing formats
        /// </summary>
        // kUseDrawOrder is the first new property added for the 2013 format. It is
        // also the same value as the pre-2013 property count.
        kPropertyCountPre2013 = kUseDrawOrder,
    };

    ////////////////////////////////////////////////////////////////////////////
    // Face properties
    //

    /// <summary>
    /// Describes the lighting model to apply to the faces of drawables.
    /// </summary>
    enum FaceLightingModel {
        /// <summary>
        /// Faces are not drawn.
        /// </summary>
        kInvisible,
        /// <summary>
        /// Faces are drawn in a constant color.
        /// </summary>
        kConstant,
        /// <summary>
        /// Faces are drawn to approximate realistic direct lighting.
        /// </summary>
        kPhong,
        /// <summary>
        //  Faces are drawn for technical illustration.
        /// Gooch, A., Gooch, B., Shirley, P., and Cohen, E. 1998.  
        /// A non-photorealistic lighting model for automatic technical
        /// illustration.  In proceedings of the 25th Annual Conference
        /// on Computer Graphics and Interactive Techniques SIGGRAPH '98.
        /// ACM Press, New York, NY, 447-452.
        /// </summary>
        kGooch,
        /// <summary>
        /// Faces are drawn in zebra stripes for surface analysis.
        /// </summary>
        kZebra
    };

    /// <summary>
    /// Describes the calculation method used for application of
    /// lighting effects to faces.
    /// </summary>
    enum FaceLightingQuality {
        /// <summary>
        /// Apply no lighting calculations to the faces.
        /// </summary>
        kNoLighting,
        /// <summary>
        /// Each face has a color calculated based on its orientation to the 
        /// light source(s) of the scene. 
        /// </summary>
        kPerFaceLighting,
        /// <summary>
        /// Each vertex of a face has its color calculated based on its 
        /// orientation to the light source(s) of the scene. 
        /// </summary>
        kPerVertexLighting,
        /// <summary>
        /// Each pixel of a face has its color calculated based on its 
        /// orientation to the light source(s) of the scene. 
        /// </summary>
        kPerPixelLighting
    };

    /// <summary>
    /// Describes modifications that affect the color of a face before 
    /// any lighting and shading calculations have been performed.
    /// </summary>
    enum FaceColorMode {
        /// <summary>
        /// No modifications are to be applied to the faces.
        /// </summary>
        kNoColorMode,
        /// <summary>
        /// Apply the color of the drawable to the faces.
        /// </summary>
        kObjectColor,
        /// <summary>
        /// Apply the display background color to the faces.
        /// </summary>
        kBackgroundColor,
        /// <summary>
        /// All faces are treated as having a specific color, resulting in a 
        /// "monochromatic" effect.
        /// </summary>
        kMono,
        /// <summary>
        /// All faces have the hue and saturation values of their color mapped 
        /// to the hue and saturation values of a specific color, resulting in
        /// a "tinted" effect.  The luminance value remains unchanged.
        /// </summary>
        kTint,
        /// <summary>
        /// Apply a desaturation percentage to the diffuse color of a material.
        /// </summary>
        kDesaturate
    };

    /// <summary>
    /// Bitfield that describes modifications to faces made before any
    /// lighting and shading calculations have been performed.
    /// </summary>
    enum FaceModifiers {
        /// <summary>
        /// Apply no face modifiers to the faces.
        /// </summary>
        kNoFaceModifiers    = 0,
        /// <summary>
        /// Apply an opacity value to the faces.  If unset, faces are displayed with
        /// full opacity.  If set, faces are displayed with a specified degree of
        /// opacity from completely opaque to completely transparent.   
        /// </summary>
        kFaceOpacityFlag    = 1,
        /// <summary>
        /// Apply a specular highlight (indicating reflection and shininess values)
        /// to a material that is applied to the faces.  
        /// </summary>
        kSpecularFlag       = 2
    };

    ////////////////////////////////////////////////////////////////////////////
    // Edge properties
    //

    /// <summary>
    /// Describes the model to use as a source of edges.
    /// </summary>
    enum  EdgeModel {
        /// <summary>
        /// No edges will be displayed.
        /// </summary>
        kNoEdges,
        /// <summary>
        /// Display isolines, imaginary lines (edges) which represent the curvature
        /// and shape of a drawable.
        /// </summary>
        kIsolines,
        /// <summary>
        /// Display facet edges, the edges between adjoining facets.
        /// </summary>
        kFacetEdges,
    };

    /// <summary>
    /// Bitfield which describes the combination of edge styles to display.
    /// </summary>
    enum EdgeStyles {
        /// <summary>
        /// No edges styles will be displayed
        /// </summary>
        kNoEdgeStyle        =  0,
        /// <summary>
        /// Visible edges will be displayed.
        /// </summary>
        kVisibleFlag        =  1,
        /// <summary>
        /// Silhouette edges will be displayed.  A silhouette edge is an edge
        /// connecting a back facing polygon with a front facing polygon.
        /// </summary>
        kSilhouetteFlag     =  2,
        /// <summary>
        /// Obscured edges will be displayed.  An obscured edge is that which
        /// would not be normally be visible when in a shaded view.
        /// </summary>
        kObscuredFlag       =  4,
        /// <summary>
        /// Intersection edges will be displayed.  An intersection edges is that
        /// which is inferred from intersecting facets.
        /// </summary>
        kIntersectionFlag   = 8
    };

    /// <summary>
    /// Bitfield which describes the combination of modifiers to apply to displayed edges.
    /// </summary>
    enum EdgeModifiers {
        /// <summary>
        /// Apply no modifiers to the edges.
        /// </summary>
        kNoEdgeModifiers    =   0,
        /// <summary>
        /// Allow an edge to overhang its start and end points by a specified amount.
        /// </summary>
        kEdgeOverhangFlag       =   1,
        /// <summary>
        /// Apply a jitter effect to the edges.  The jitter effect is produced by drawing
        /// extra lines adjacent to the original line, with a specific amount of 
        /// perturbation away from the original line.
        /// </summary>
        kEdgeJitterFlag     =   2,
        /// <summary>
        /// Apply a width > 1 to the edges.
        /// </summary>
        kEdgeWidthFlag      =   4,
        /// <summary>
        /// Apply a color other than the drawable object color to the edges.
        /// </summary>
        kEdgeColorFlag      =   8,
        /// <summary>
        /// Apply a halo gap percentage to the edges of an object that is hidden
        /// by another object, such that the specified gap is displayed between the
        /// edges of the hidden object and the edges of the object which hides it.  
        /// </summary>
        kEdgeHaloGapFlag    =  16,
        /// <summary>
        /// Force edges to be on top.  Edges will not participate in the Z-ordering
        /// of the displayed drawables.
        /// </summary>
        kAlwaysOnTopFlag    =  64,
        /// <summary>
        /// Apply an opacity value to the edges.  If unset, edges are displayed with
        /// full opacity.  If set, edges are displayed with a specified degree of
        /// opacity from completely opaque to completely transparent.
        /// </summary>
        kEdgeOpacityFlag        = 128,
        /// <summary>
        /// Apply a wiggle effect to the edges.  The wiggle effect is produced by drawing
        /// extra lines adjacent to the original line, with a specific amount of 
        /// perturbation away from the original line.
        /// </summary>
        kEdgeWiggleFlag         = 256,
        /// <summary>
        /// Apply a texture effect to the edges.  The texture effect is produced by drawing
        /// texure on the original line.
        /// </summary>
        kEdgeTextureFlag         = 512,
    };

    /// <summary>
    /// Describes the amount of jitter effect to apply to edges.
    /// </summary>
    enum EdgeJitterAmount {
        /// <summary>
        /// A small amount of perturbation will be applied to edges.
        /// </summary>
        kJitterLow = 1,
        /// <summary>
        /// A medium amount of perturbation will be applied to edges.
        /// </summary>
        kJitterMedium,
        /// <summary>
        /// A large amount of perturbation will be applied to edges.
        /// </summary>
        kJitterHigh,
    };


    /// <summary>
    /// Describes the amount of jitter effect to apply to edges.
    /// </summary>
    enum EdgeWiggleAmount {
        /// <summary>
        /// A small amount of perturbation will be applied to edges.
        /// </summary>
        kWiggleLow = 1,
        /// <summary>
        /// A medium amount of perturbation will be applied to edges.
        /// </summary>
        kWiggleMedium,
        /// <summary>
        /// A large amount of perturbation will be applied to edges.
        /// </summary>
        kWiggleHigh,
    };

    /// <summary>
    /// Describes the raster-based line patterns to apply to edges.
    /// </summary>
    enum EdgeLinePattern {
        /// <summary>
        /// Display edges with a solid line pattern.
        /// </summary>
        kSolid = 1,
        /// <summary>
        /// Display edges with a dashed line pattern.
        /// </summary>
        kDashedLine,
        /// <summary>
        /// Display edges with a dotted line pattern.
        /// </summary>
        kDotted,
        /// <summary>
        /// Display edges with a short dashed line pattern.
        /// </summary>
        kShortDash,
        /// <summary>
        /// Display edges with a medium dashed line pattern.
        /// </summary>
        kMediumDash,
        /// <summary>
        /// Display edges with a long dashed line pattern.
        /// </summary>
        kLongDash,
        /// <summary>
        /// Display edges with a double short dashed line pattern.
        /// </summary>
        kDoubleShortDash,
        /// <summary>
        /// Display edges with a double medium dashed line pattern.
        /// </summary>
        kDoubleMediumDash,
        /// <summary>
        /// Display edges with a double long dashed line pattern.
        /// </summary>
        kDoubleLongDash,
        /// <summary>
        /// Display edges with a medium long dashed line pattern.
        /// </summary>
        kMediumLongDash,
        /// <summary>
        /// Display edges with a sparse dotted line pattern.
        /// </summary>
        kSparseDot
    };

    ////////////////////////////////////////////////////////////////////////////
    // Display properties
    //

    /// <summary>
    /// Bitfield which describes the combination of enabled display settings.
    /// </summary>
    enum DisplayStyles {
        /// <summary>
        /// No display settings are enabled.
        /// </summary>
        kNoDisplayStyle      =  0,
        /// <summary>
        /// Backgrounds are displayed.
        /// </summary>
        kBackgroundsFlag     =  1,
        /// <summary>
        /// Lighting is displayed.
        /// </summary>
        kLightingFlag        =  2,
        /// <summary>
        /// Materials are displayed.
        /// </summary>
        kMaterialsFlag       =  4,
        /// <summary>
        /// Textures are displayed.
        /// </summary>
        kTexturesFlag        =  8,
    };

    /// <summary>
    /// Describes the type of shadow to enable.
    /// </summary>
    enum DisplayShadowType {
        /// <summary>
        /// No shadows are displayed.
        /// </summary>
        kShadowsNone,
        /// <summary>
        /// Ground plane shadows are displayed.
        /// </summary>
        kShadowsGroundPlane,
        /// <summary>
        /// Full shadows are displayed.
        /// </summary>
        kShadowsFull,
        /// <summary>
        /// Full and ground plane shadows are displayed.
        /// </summary>
        kShadowsFullAndGround,
    };
};

/// <summary>
/// Container for visual style Operation enumeration.
/// </summary>
namespace AcGiVisualStyleOperations
{
    /// <summary>
    /// Describes what kind of operation to perform when setting a visual 
    //  style property.
    /// </summary>
    enum Operation {
        kInvalidOperation = -1,
        /// <summary>
        /// Use the last property value specified.  NOTE: Reserved for future 
        /// use.  Specifying this currently will be treated the same as kSet.
        /// </summary>
        kInherit = 0,

        /// <summary>
        /// Replace the last property value with the one specified.
        /// </summary>
        kSet,

        /// <summary>
        /// Disable the specified bits in the property bitmask.
        /// </summary>
        kDisable,

        /// <summary>
        /// Enable the specified bits in the property bitmask.
        /// </summary>
        kEnable
    };
};

////////////////////////////////////////////////////////////////////////
// class AcGiVisualStyle
//
/// <summary> 
/// This class defines the collection of visual properties that can be 
/// applied to drawables.
/// </summary>
/// 
/// <remarks>
/// 
/// </remarks>
//
class AcGiVisualStyle : public AcRxObject
{
public:
    friend class            AcDbImpVisualStyle;

    ACRX_DECLARE_MEMBERS(AcGiVisualStyle);

    typedef AcGiVisualStyleProperties::Property Property;
    typedef AcGiVisualStyleOperations::Operation Operation;

    /// <summary>
    /// Describes the visual style type, based on multiple property settings.
    /// </summary>
    enum Type {
        // Legacy (shademode) styles
        /// <summary>
        /// Flat shaded visual style.
        /// </summary>
        kFlat,
        /// <summary>
        /// Flat shaded visual style with edges displayed.
        /// </summary>
        kFlatWithEdges,
        /// <summary>
        /// Gouraud shaded visual style.
        /// </summary>
        kGouraud,
        /// <summary>
        /// Gouraud shaded visual style with edges displayed.
        /// </summary>
        kGouraudWithEdges,
        /// <summary>
        /// 2D wireframe visual style (using 2D graphics system).
        /// </summary>
        k2DWireframe,
        /// <summary>
        /// 3D wireframe visual style (using 3D graphics system).
        /// </summary>
        k3DWireframe,
        /// <summary>
        /// Hidden visual style.
        /// </summary>
        kHidden,
        // Visual Styles
        /// <summary>
        /// Basic default visual style.
        /// </summary>
        kBasic,
        /// <summary>
        /// Phong shaded visual style.
        /// </summary>
        kRealistic,
        /// <summary>
        /// Gooch shaded visual style.
        /// </summary>
        kConceptual,
        /// <summary>
        /// Custom, user defined visual visual style.
        /// </summary>
        kCustom,
        // Highlight visual styles
        /// <summary>
        /// Visual style used for a dimming effect.
        /// </summary>
        kDim,
        /// <summary>
        /// Visual style used for a brightening effect.
        /// </summary>
        kBrighten,
        /// <summary>
        /// Visual style used for a thickening effect.
        /// </summary>
        kThicken,
        /// <summary>
        /// Visual style used to apply a line pattern.
        /// </summary>
        kLinePattern,
        /// <summary>
        /// Visual style used to apply a face pattern.
        /// </summary>
        kFacePattern,
        /// <summary>
        /// Visual style used to apply a change of color.
        /// </summary>
        kColorChange,

        // Face-only/edge-only visual styles
        //

        /// <summary>
        /// Face properties only visual style.  All non-face properties are set to inherit.
        /// </summary>
        kFaceOnly,

        /// <summary>
        /// Edge properties only visual style.  All non-edge properties are set to inherit.
        /// </summary>
        kEdgeOnly,

        /// <summary>
        /// Display properties only visual style.  All non-display properties are set to inherit.
        /// </summary>
        kDisplayOnly,

        // Edge Style Override visual styles
        //

        /// <summary>
        /// Edge style override visual style with jitter edges off.  All other properties are
        /// set to inherit.
        /// </summary>
        kJitterOff,

        /// <summary>
        /// Edge style override visual style with overhang edges off.  All other properties are
        /// set to inherit.
        /// </summary>
        kOverhangOff,

        /// <summary>
        /// Edge style override visual style with edge color off.  All other properties are
        /// set to inherit.
        /// </summary>
        kEdgeColorOff,

        /// <summary>
        /// shades of gary visual style
        /// </summary>
        kShadesOfGray,
        /// <summary>
        /// sketchy visual style
        /// </summary>
        kSketchy,
        /// <summary>
        /// xray visual style
        /// </summary>
        kXRay,
        /// <summary>
        /// shade with edges visual style
        /// </summary>
        kShadedWithEdges,
        /// <summary>
        /// shaded visual style
        /// </summary>
        kShaded,
        /// <summary>
        /// dummy visual style
        /// </summary>
        kByViewport,
        /// <summary>
        /// dummy visual style
        /// </summary>
        kByLayer,
        /// <summary>
        /// dummy visual style
        /// </summary>
        kByBlock,

        /// <summary>
        /// Visual style with all properties set to inherit.  This effectively
        /// creates an empty style upon which a custom visual style can be built.
        /// </summary>
        kEmptyStyle,

    };

    /// <summary>
    /// Default constructor.  Initializes members to default values.
    /// </summary>
                            AcGiVisualStyle     (void);

    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="type">
    /// Input Type. The type of visual style to configure - a built-in type or
    /// custom.
    /// </param>
                            AcGiVisualStyle     (Type type);

    /// <summary>
    /// Copy constructor.  Copies the given visual style into this visual style.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle. A constant reference to the visual style 
    /// which will be copied into this visual style.
    /// </param>
                            AcGiVisualStyle     (const AcGiVisualStyle& visualStyle);

    /// <summary>
    /// Destructor.  Performs any necessary cleanup of the visual style.
    /// </summary>
                            ~AcGiVisualStyle    (void);

    /// <summary>
    /// Assignment operator.  Copies the given visual style into this visual style.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle. A constant reference to the visual style 
    /// which will be copied into this visual style.
    /// </param>                               
    /// <returns>
    /// Returns a reference to the visual style into which the copy was made.
    /// </returns>
    AcGiVisualStyle& operator=(const AcGiVisualStyle& visualStyle);

    /// <summary>
    /// Comparison operator.  Compares the given visual style with this visual style.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle. A constant reference to the visual style 
    /// which will be compared to this visual style.
    /// </param>                               
    /// <returns>
    /// Returns boolean value representing whether the given visual style is equivalent
    /// to this visual style.
    /// </returns>
    bool operator==(const AcGiVisualStyle& visualStyle) const;

    ////////////////////////////////////////////////////////////////////////////
    // Type - custom, built-in, face/edge only, etc.
    //

    /// <summary>
    /// Sets the visual style type, modifying multiple properties as necessary to 
    /// change the visual style into the specified type.
    /// </summary>
    /// <param name="type">
    /// Input enum Type to set into the visual style.
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    ACDBCORE2D_PORT bool              setType     (Type type);

    /// <summary>
    /// Gets the visual style type.
    /// </summary>
    /// <returns>
    /// Type of visual style.
    /// </returns>    
    ACDBCORE2D_PORT Type              type        (void) const;

    ////////////////////////////////////////////////////////////////////////////
    // Property set/get
    //

    /// <summary>
    /// Sets the operation associated with a property.
    /// </summary>
    /// <param name="prop">
    /// The AcGiVisualStyleProperties::Property to set the operation for.
    /// </param>
    /// <param name="op">
    /// The AcGiVisualStyleOperations::Operation for the property to use. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    ACDBCORE2D_PORT virtual bool      setTrait    (Property prop, Operation op);

    /// <summary>
    /// Sets a property of the visual style.  
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.
    /// </param>                               
    /// <param name="pVal">
    /// Input AcGiVariant property value to set into the visual style.
    /// </param>                               
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    /// <example>
    ///
    /// // Set brightness to 1.0
    /// AcGiVariant displayBrightness.set(1.0);
    /// acgiVisualStyle.setTrait (AcGiVisualStyleProperties::kDisplayBrightness, &displayBrightness);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTrait    (Property prop, 
                                             const AcGiVariant *pVal,
                                             Operation op = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets an integer property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceLightingModel
    ////    kFaceLightingQuality
    ////    kFaceColorMode
    ////    kFaceModifier
    ////    kEdgeModel
    ////    kEdgeStyle
    ////    kEdgeObscuredLinePattern
    ////    kEdgeIntersectionLinePattern
    ////    kEdgeModifier
    ////    kEdgeWidth
    ////    kEdgeOverhang
    ////    kEdgeJitter
    ////    kEdgeSilhouetteWidth
    ////    kEdgeHaloGap
    ////    kEdgeIsolines
    ////    kDisplayStyle
    ////    kDisplayShadowType
    /// </param>                               
    /// <param name="nVal">
    /// Input integer property value to set into the visual style.
    /// </param>                               
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    /// <example>
    ///
    /// // Set lighting model to kGooch
    /// using namespace AcGiVisualStyleProperties;
    /// acgiVisualStyle.setTrait (kFaceLightingModel, kGooch);
    ///
    /// // Set halogap to 20
    /// acgiVisualStyle.setTrait (AcGiVisualStyleProperties::kEdgeHaloGap, 20);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTrait    (Property prop, 
                                             int nVal,
                                             Operation op = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a boolean property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kEdgeHidePrecision
    ////    kUseDrawOrder
    ////    kIsViewportTransparent
    ////    kLightingEnabled
    /// </param>                               
    /// <param name="bVal">
    /// Input boolean property value to set into the visual style.
    /// </param>                               
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    /// <example>
    ///
    /// // Set hide precision to false
    /// acgiVisualStyle.setTrait (AcGiVisualStyleProperties::kEdgeHidePrecision, false);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTrait    (Property prop, 
                                             bool bVal,
                                             Operation op = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a double property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceOpacity
    ////    kFaceSpecular
    ////    kEdgeCreaseAngle
    ////    kEdgeOpacity
    ////    kDisplayBrightness
    /// </param>                               
    /// <param name="dVal">
    /// Input double property value to set into the visual style.
    /// </param>                               
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    /// <example>
    ///
    /// // Set brightness to 1.0
    /// acgiVisualStyle.setTrait (AcGiVisualStyleProperties::kDisplayBrightness, 1.0);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTrait    (Property prop, 
                                             double dVal,
                                             Operation op = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a color property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceMonoColor
    ////    kEdgeIntersectionColor
    ////    kEdgeObscuredColor
    ////    kEdgeColor
    ////    kEdgeSilhouetteColor
    /// </param>
    /// <param name="red">
    /// Input red color value to set into the visual style.  Valid value is from 0.0 to 1.0.
    /// </param>
    /// <param name="green">
    /// Input green color value to set into the visual style.  Valid value is from 0.0 to 1.0.
    /// </param>
    /// <param name="blue">
    /// Input blue color value to set into the visual style.  Valid value is from 0.0 to 1.0.
    /// </param>
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    /// <example>
    ///
    /// // Set edge intersection color to 110% red
    /// acgiVisualStyle.setTrait (AcGiVisualStyleProperties::kEdgeIntersectionColor, 1.1, 1.0, 1.0);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTrait    (Property prop, 
                                             double red,
                                             double green,
                                             double blue,
                                             Operation op = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a color property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kFaceMonoColor
    ////    kEdgeIntersectionColor
    ////    kEdgeObscuredColor
    ////    kEdgeColor
    ////    kEdgeSilhouetteColor
    /// </param>
    /// <param name="pColor">
    /// Input AcCmColor property value to set into the visual style.
    /// </param>
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    /// <example>
    ///
    /// // Set monoColor to white
    /// AcCmColor monoColor;
    /// monoColor.setRGB(255,255,255);
    /// acgiVisualStyle.setTrait (AcGiVisualStyleProperties::kFaceMonoColor, &monoColor);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTrait    (Property prop, 
                                             const AcCmColor *pColor,
                                             Operation op = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Sets a AcString property of the visual style.
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to set into the visual style.  Valid
    /// Property values for this method are:
    ////    kEdgeTexturePath
    /// </param>
    /// <param name="pStr">
    /// Input AcString property value to set into the visual style.
    /// </param>
    /// <param name="op">
    /// Input AcGiVisualStyleOperations::Operation to use when setting the property into the visual style. 
    /// </param>
    /// <returns>
    /// Returns Acad::eOk if successful; otherwise, returns Acad::eInvalidInput.
    /// </returns>
    /// <example>
    ///
    /// AcString texturePath("strokes_ogs.tif");
    /// acdbVisualStyle.setTrait (AcGiVisualStyleProperties::kEdgeTexturePath, &texturePath);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTrait    (AcGiVisualStyleProperties::Property prop, 
                                             const AcString *pStr,
                                             AcGiVisualStyleOperations::Operation op
                                             = AcGiVisualStyleOperations::kSet);

    /// <summary>
    /// Gets a property of the visual style.  
    /// </summary>
    /// <param name="prop">
    /// Input AcGiVisualStyleProperties::Property to get from the visual style.
    /// </param>                               
    /// <param name="pOp">
    /// Output AcGiVisualStyleOperations::Operation to get the operation 
    /// currently in effect for this property.  If NULL, nothing is returned.
    /// </param>
    /// <returns>
    /// Returns the AcGiVariant value of the property if successful; otherwise,
    /// returns an AcGiVariant of type AcGiVariant::kUndefined.
    /// </returns>    
    /// <example>
    ///
    /// AcGiVariant displayBrightness = 
    ///     acgiVisualStyle.trait (AcGiVisualStyleProperties::kDisplayBrightness);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual const AcGiVariant& trait (Property prop, 
                                             Operation *pOp = NULL) const;

    /// <summary>
    /// Gets the operation associated with a property.
    /// </summary>
    /// <param name="prop">
    /// Name of the property for which to get the associated operation value.
    /// </param>
    /// <returns>
    /// The operation associated with the property.  For invalid property
    /// values, the return value is kInvalidOperation.
    /// </returns>
    ACDBCORE2D_PORT virtual Operation          operation (Property prop) const;

    /// <summary>
    /// Sets a property flag into the visual style, for properties which are bitfield enums.
    /// </summary>
    /// <param name="flagProp">
    /// Input bitfield enum AcGiVisualStyleProperties::Property to set into the visual style.
    /// </param>                               
    /// <param name="flagVal">
    /// Input bit flag enum unsigned long property to set into the visual style.
    /// </param>                               
    /// <param name="bEnable">
    /// Input bool set to true to enable the flag, false to disable. 
    /// </param>
    /// <returns>
    /// Returns true if successful; otherwise, returns false.
    /// </returns>
    /// <example>
    ///
    /// using namespace AcGiVisualStyleProperties;
    /// acgiVisualStyle.setTraitFlag (kEdgeModifier, kJitter, true);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      setTraitFlag(Property flagProp,
                                             Adesk::UInt32 flagVal,
                                             bool bEnable = true);

    /// <summary>
    /// Gets a property flag from the visual style, for properties which are bitfield enums.
    /// </summary>
    /// <param name="flagProp">
    /// Input bitfield enum AcGiVisualStyleProperties::Property to get from the visual style.
    /// </param>                               
    /// <param name="flagVal">
    /// Input bit flag enum unsigned long property to get from the visual style.
    /// </param>                               
    /// <returns>
    /// Returns true if flag is enabled, false otherwise. 
    /// </returns>    
    /// <example>
    ///
    /// using namespace AcGiVisualStyleProperties;
    /// bool bJitterEnabled = acgiVisualStyle.traitFlag(kEdgeModifier, kJitter);
    ///
    /// </example>
    ACDBCORE2D_PORT virtual bool      traitFlag   (Property flagProp,
                                             Adesk::UInt32 flagVal) const;

    /// <summary>
    /// Gets data type of the specified visual style property.
    /// </summary>
    /// <param name="prop">
    /// Input enum AcGiVisualStyleProperties::Property.
    /// </param>                               
    /// <returns>
    /// Returns the AcGiVariant::VariantType of the specified visual style property.
    /// </returns>    
    ACDBCORE2D_PORT static AcGiVariant::VariantType propertyType(Property prop);

private:
    const AcGiImpVisualStyle* readImp  (void) const;
    AcGiImpVisualStyle*       writeImp (void);

    AcGiImpVisualStyle* mpAcGiImpVisualStyle;
};

////////////////////////////////////////////////////////////////////////
// class AcGiVisualStyleTraits
////////////////////////////////////////////////////////////////////////

/// <summary> 
/// This class defines the visual style traits.  Derived from AcGiDrawableTraits,
/// this class provides the interfaces to implement for setting and returning the
/// visual style via drawable traits.
/// </summary>
/// 
/// <remarks>
/// 
/// </remarks>
class AcGiVisualStyleTraits : public AcGiDrawableTraits
{
public:
    ACRX_DECLARE_MEMBERS(AcGiVisualStyleTraits);

    /// <summary>
    /// Sets the visual style to capture in the drawable traits.
    /// </summary>
    /// <param name="visualStyle">
    /// Input AcGiVisualStyle const reference to the visual style to capture.
    /// </param>                               
    virtual void                   setAcGiVisualStyle   (const AcGiVisualStyle& visualStyle) = 0;

    /// <summary>
    /// Reports the visual style that is currently captured in this drawable traits.
    /// </summary>
    /// <returns>
    /// Returns AcGiVisualStyle const reference to the visual style that is 
    /// currently captured in this drawable traits.
    /// </returns>
    virtual const AcGiVisualStyle& acgiVisualStyle      (void) const = 0;
};
