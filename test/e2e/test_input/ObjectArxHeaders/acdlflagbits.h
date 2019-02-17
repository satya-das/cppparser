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

#pragma once

/// <summary>
/// These enum values are used as flags bits in the nFlags argument of
/// AcDbHostApplicationServices::selectFile(). Some of them are used by
/// AutoCAD's calls to selectFile() and should not be used by other
/// callers.  They are included here because they may be seen by
/// selectFile callback handlers (see
/// AcadHostApplicationServices::registerSelectFileCallback()).
/// </summary>
enum AcFileSelectFlags : unsigned int {
    /// <summary>
    /// No typeit button. This bit is obsolete.
    /// </summary>
    kDLFNoType    = 0x0,
    /// <summary>
    /// Creating file
    /// </summary>
    kDLFPut       = 0x1,
    /// <summary>
    /// Special action for drawing file
    /// </summary>
    kDLFDwg       = 0x2,
    /// <summary>
    /// Default name is path only
    /// </summary>
    kDLFPathOnly     = 0x4,
    /// <summary>
    /// No overwrite warning on Put file
    /// </summary>
    kDLFNoWarn    = 0x8,
    /// <summary>
    /// Don't check if file exists in Open dialog
    /// </summary>
    kDLFNoExistOk = 0x10,
    /// <summary>
    /// Accept any extension, don't strip
    /// </summary>
    kDLFAnyExt    = 0x20,
    /// <summary>
    /// User requested dialogue box via ~
    /// </summary>
    kDLFRqBox     = 0x40,
    /// <summary>
    /// SAVEAS use of the dialog. Distinguish .dwg action
    /// </summary>
    kDLFSaveas    = 0x80,
    /// <summary>
    /// Don't perform library search
    /// </summary>
    kDLFNoLib     = 0x0100,
    /// <summary>
    /// Internet: do not transfer file
    /// </summary>
    kDLFNoXfer    = 0x0200,
    /// <summary>
    /// Internet: do not allow URLs at all
    /// </summary>
    kDLFNoURLs    = 0x0400,
    /// <summary>
    /// Default is derived from DWG name
    /// </summary>
    kDLFDwgDef    = 0x0800,
    /// <summary>
    /// Special dialog definition for OPEN
    /// </summary>
    kDLFOpenDef   = 0x1000,
    /// <summary>
    /// Allow device names to be returned
    /// </summary>
    kDLFDvc      = 0x2000,
    /// <summary>
    /// Flag templates to lock directories
    /// </summary>
    kDLFDwt       = 0x4000,
    /// <summary>
    /// Display the "Options" item
    /// </summary>
    kDLFOpts      = 0x8000,
    /// <summary>
    /// Don't use last pop-up as the parent window
    /// </summary>
    kDLFNoPopup   = 0x10000,
    /// <summary>
    /// Force overwrite warning in scripts and Lisp
    /// </summary>
    kDLFFrcWarn   = 0x20000,
    /// <summary>
    /// Allow multiple drawing opens.
    ///
    /// WARNING: This flag must not be used in any AutoCAD command
    /// dialogs other then the OPEN command.  It is ok to use it for
    /// non-AutoCAD command dialogs.  For example, it is used in the
    /// acedGetFileNavDialog API to allow multiple file selection and
    /// return multiple file names to the caller.
    /// </summary>
    kDLFMulti     = 0x40000,
    /// <summary>
    /// Use the command line to get file name.
    /// </summary>
    kDLFCLI       = 0x80000,
    /// <summary>
    /// Doing a recover.
    /// </summary>
    kDLFRecover   = 0x100000,
    /// <summary>
    /// Force the initial directory to be the argument (only works with anav).
    /// </summary>
    kDLFForceDir  = 0x200000,
    /// <summary>
    /// Do not show FTP site (only works with anav).
    /// </summary>
    kDLFNoFTP     = 0x400000,
    /// <summary>
    /// Do not use the anav dialog, force use of Microsoft common file dialog.
    /// </summary>
    kDLFNoAnav    = 0x800000,
    /// <summary>
    /// Select folders only (only works with anav).
    /// </summary>
    kDLFFolders   = 0x1000000,
    /// <summary>
    /// Do not show shell namespace extension sites at all (only works with anav).
    /// </summary>
    kDLFNoExtensions = 0x2000000,                   
    /// <summary>
    /// Open with no Template - Imperial or Metric
    /// </summary>
    kDLFNoTemplate = 0x4000000,
    /// <summary>
    /// AutoCAD EXPORT dialog. Distinguish 2ddwf and 3ddwf action
    /// </summary>
    kDLFExport     = 0x8000000,
    /// <summary>
    /// Enable support for REMEMBERFOLDERS sysvar
    /// </summary>
    kDLFEnableRememberFolders = 0x10000000,
    /// <summary>
    /// Open dialog but for opening local/Online sample files.
    /// </summary>
    kDLFOpenSample = 0x20000000,
    /// <summary>
    /// Force the intial directory to the Autodesk Cloud (only works with anav).
    /// </summary>
    kDLFUseCloud = 0x40000000,
    /// <summary>
    /// Control display on the right side of dialog.
    /// </summary>
    kDLFCloudControls = 0x80000000,
};
