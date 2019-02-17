//////////////////////////////////////////////////////////////////////////////
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

#include "gs.h" // for AcGsWindowingSystemID

class AcDbViewportTableRecord;
class AcGiDrawable;
class AcGsGraphicsKernel;
class AcGsKernelDescriptor;
class AcGsView;
class AcGsModel;
class AcGsDevice;
class AcGsConfig;
struct AcGsClientViewInfo;
class AcDbDatabase;

#ifndef DRAWBRIDGE_API
#define DRAWBRIDGE_API __declspec(dllimport)
#endif // DRAWBRIDGE_API

class AcGsManager
{
public:
    /// <description>
    /// Default constructor.
    /// </description>
                        AcGsManager                 (void) { }

    /// <description>
    /// Destructor.
    /// </description>
    virtual             ~AcGsManager                 (void) { }

    /// <description>
    /// Create an AcGsModel using the specified kernel.
    /// </description>
    /// <param name="kernel">Input kernel to be used to create the model.</param>
    /// <returns>
    /// The new AcGsModel.
    /// </returns>
    virtual AcGsModel*  createAutoCADModel          (AcGsGraphicsKernel &kernel)                                = 0;

    /// <description>
    /// Creates an AcGsView using the specified kernel and viewport table record.
    /// Created AcGsView is added to the GUI's AcGsDevice
    /// </description>
    /// <param name="kernel">Input the graphics kernel to be used to create the view. Kernel used must be compatible with the one used to create the GUI.</param>
    /// <param name="pVTR">Input the view table record to be associated with the view.</param>
    /// <returns>
    /// The new AcGsView.
    /// </returns>
    virtual AcGsView*   createAutoCADViewport       (AcGsGraphicsKernel &kernel, AcDbViewportTableRecord *pVTR) = 0;

    /// <description>
    /// Create an AcGsView using the specified kernel and drawable.
    /// Created AcGsView is added to the GUI's AcGsDevice
    /// </description>
    /// <param name="kernel">Input kernel to be used to create the view. Kernel used must be compatible with the one used to create the GUI.</param>
    /// <param name="pDrawable">Input drawable to be associated with the view.</param>
    /// <returns>
    /// The new AcGsView.
    /// </returns>
    virtual AcGsView*   createAutoCADView           (AcGsGraphicsKernel &kernel, AcGiDrawable *pDrawable)       = 0;

    /// <description>
    /// Create an AcGsDevice using the specified kernel and window.
    /// </description>
    /// <param name="kernel">Input kernel to be used to create the device.</param>
    /// <param name="id">Input window system ID to be associated with the device. On Windows this is an HWND</param>
    /// <returns>
    /// The new AcGsDevice.
    /// </returns>
    virtual AcGsDevice* createAutoCADDevice         (AcGsGraphicsKernel &kernel, AcGsWindowingSystemID id)      = 0;

    /// <description>
    /// Create an offscreen AcGsDevice using the specified kernel.
    /// </description>
    /// <param name="kernel">Input kernel to be used to create the offscreen device.</param>
    /// <returns>
    /// The new AcGsDevice.
    /// </returns>
    virtual AcGsDevice* createAutoCADOffScreenDevice(AcGsGraphicsKernel &kernel)                                = 0;

    /// <description>
    /// Destroy the specified AcGsModel. Corresponds to createAutoCADModel().
    /// </description>
    /// <param name="pModel">Input model to be destroyed.</param>
    virtual void        destroyAutoCADModel         (AcGsModel  *pModel)                                        = 0;

    /// <description>
    /// Destroy the specified AcGsView. Corresponds to createAutoCADView().
    /// Specified view will be removed from the GUI's AcGsDevice.
    /// </description>
    /// <param name="pView">Input view to be destroyed.</param>
    virtual void        destroyAutoCADView          (AcGsView   *pView)                                         = 0;

    /// <description>
    /// Destroy the specified AcGsDevice. Corresponds to createAutoCADDevice().
    /// </description>
    /// <param name="pDevice">Input device to be destroyed.</param>
    virtual void        destroyAutoCADDevice        (AcGsDevice *pDevice)                                       = 0;
    /// <description>
    /// Creates an AcGsView with the same kernel used to create the specified device and with the specified viewport table record.
    /// Created AcGsView is added to the specified device.
    /// </description>
    /// <param name="pDevice">Input the graphics device to be used to create the view.</param>
    /// <param name="pVTR">Input the view table record to be associated with the view.</param>
    /// <returns>
    /// The new AcGsView.
    /// </returns>
    virtual AcGsView*   createViewport              (AcGsDevice* pDevice, AcDbViewportTableRecord *pVTR)        = 0;

    /// <description>
    /// Create an AcGsView with the same kernel used to create the specified device.
    /// Note that there is no associated viewport table record with this AcGsView.
    /// Created AcGsView is added to the specified device.
    /// </description>
    /// <param name="pDevice">Input the graphics device to be used to create the view.</param>
    /// <returns>
    /// The new AcGsView.
    /// </returns>
    virtual AcGsView*   createView                  (AcGsDevice* pDevice)                                       = 0;
    /// <description>
    /// Destroy the specified AcGsView. Corresponds to createView() and createViewport().
    /// Specified AcGsView is removed from associated AcGsDevice.
    /// Specified View Table Record is disassociated but not destroyed by this call.
    /// </description>
    /// <param name="pView">Input view to be destroyed.</param>
    /// <param name="pVTR">[Optional] Associated view table record. Not destroyed by this function.</param>
    virtual void        destroyView                 (AcGsView*, AcDbViewportTableRecord* pVTR = nullptr)        = 0;
    /// <description>
    /// Get the AcGsModel associated with the current AutoCAD database and the specified kernel.
    /// </description>
    /// <param name="kernel">Input kernel to query for the model.</param>
    /// <returns>
    /// The AcGsModel associated with the current AutoCAD database and the specified kernel.
    /// </returns>
    virtual AcGsModel*  getDBModel                  (AcGsGraphicsKernel &kernel)                                = 0;

    /// <description>
    /// Get the AcGsDevice associated with the specified kernel.
    /// </description>
    /// <param name="kernel">Input kernel to query for the device.</param>
    /// <returns>
    /// The AcGsDevice associated with the specified kernel.
    /// </returns>
    virtual AcGsDevice* getGUIDevice                (AcGsGraphicsKernel &kernel)                                = 0;

    /// <description>
    /// Set the association between the specified database and model for the current display.
    /// </description>
    /// <param name="pDb">Input database to associate with model.</param>
    /// <param name="pModel">Input model to associate with database.</param>
    /// <remarks>The model must have been created by the current display's graphics kernel.
    /// </remarks>
    virtual void        setGsModel                  (const AcDbDatabase* pDb, AcGsModel* pModel)                = 0;

    /// <description>
    /// Get the current display's model that is associated with the specified database.
    /// </description>
    /// <param name="pDb">Input database.</param>
    /// <returns>
    /// The AcGsModel associated with the database.
    /// </returns>
    virtual AcGsModel*  gsModel                     (const AcDbDatabase* pDb) const                             = 0;

    /// <description>
    /// Set the association between the specified database and highlight model for the current display.
    /// </description>
    /// <param name="pDb">Input database to associate with highlight model.</param>
    /// <param name="pModel">Input highlight model to associate with database.</param>
    /// <remarks>The highlight model must have been created by the current display's graphics kernel.
    /// </remarks>
    virtual void        setGsHighlightModel         (const AcDbDatabase* pDb, AcGsModel* pModel)                = 0;

    /// <description>
    /// Get the current display's highlight model that is associated with the specified database.
    /// </description>
    /// <param name="pDb">Input database.</param>
    /// <returns>
    /// The highlight AcGsModel associated with the database.
    /// </returns>
    virtual AcGsModel*  gsHighlightModel            (const AcDbDatabase* pDb) const                             = 0;

    /// <description>
    /// Get an offscreen device for the specified kernel. 
    /// </description>
    /// <remarks>
    /// An offscreen device is created if none exists and is cached for subsequent use. 
    /// </remarks>
    /// <param name="kernel">Input kernel to query for the device.</param>
    /// <returns>
    /// A valid AcGsDevice if successful, otherwise null. 
    /// </returns>
    virtual AcGsDevice* getOffScreenDevice(AcGsGraphicsKernel &kernel) = 0;

    /// <description>
    /// Get an offscreen view for the specified kernel. 
    /// View is created without an associated viewport table record. If one is required, use createView(...)
    /// </description>   
    /// <remarks>
    /// The view is connected to the offscreen device. It is created on demand and cached, 
    /// however its lifetime is ephemeral and not guaranteed past the next call to this 
    /// function with different AcGsClientViewInfo parameters. 
    /// </remarks>   
    /// <param name="kernel">Input kernel. Currently only supports the k3DRapidRTRendering kernel. </param>
    /// <param name="clientViewInfo">Input client view informatino.</param>
    /// <returns>
    /// A valid offscreen AcGsView if successful, otherwise null. 
    /// </returns>
    virtual AcGsView*   getOffScreenView(AcGsGraphicsKernel &kernel, AcGsClientViewInfo &clientViewInfo)        = 0;

    /// <description>
    /// Test for an AcGsModel association with the specified AcDbDatabase. 
    /// </description>
    /// <remarks>
    /// This is a convenience method to test for non-null return value from AcGsManager::gsModel().
    /// </remarks>
    /// <param name="pDb">Input database.</param>
    /// <returns>
    /// Returns true if there is a model associated with the database.  
    /// </returns>
    virtual bool        hasGsModel(const AcDbDatabase* pDb) const                                               = 0;

    /// <description>
    /// Invalidate the AcGsModel associated with the specified AcDbDatabase.
    /// </description>
    /// <param name="pDb">Input database.</param>
    /// <returns>
    /// Returns false if the database has no associated model. 
    /// </returns>
    virtual bool        invalidateGsModel(const AcDbDatabase* pDb)                                              = 0;

    /// <description>
    /// Acquire a reference to the graphics kernel compatible with the specified descriptor.
    /// </description>
    /// <remarks>
    /// The graphics kernel is a handle to an underlying graphics system. Each kernel has its own 
    /// set of capabilities, and AutoCAD will pick the appropriate kernel to use based on the requested 
    /// capabilities. Graphics kernels are reference counted, so be sure to call releaseGraphicsKernel() 
    /// when you are done with the kernel.  This method is static, so it should be called as 
    /// AcGsManager::acquireGraphicsKernel(descriptor).
    ///
    /// Do not mix devices, views and models created by different graphics kernels.
    /// </remarks>
    /// <param name="descriptor">Input a descriptor defining the required capabilities of the kernel.</param>
    /// <returns>
    /// The graphics kernel object.
    /// </returns>
    static DRAWBRIDGE_API AcGsGraphicsKernel*  acquireGraphicsKernel(const AcGsKernelDescriptor &descriptor);

    /// <description>
    /// Release a reference to the specified graphics kernel.
    /// </description>
    /// <remarks>
    /// This method is static, so it should be called as AcGsManager::releaseGraphicsKernel(pKernel).
    /// </remarks>
    /// <param name="pKernel">Input kernel to release.</param>
    static DRAWBRIDGE_API void                  releaseGraphicsKernel(AcGsGraphicsKernel *pKernel);

    /// <description>
    /// Get the global AcGsConfig object. This object controls the configuration for all graphics kernels.
    /// </description>
    /// <returns>
    /// The global AcGsConfig object.
    /// </returns>
    static DRAWBRIDGE_API AcGsConfig*           getConfig            (void);
};
