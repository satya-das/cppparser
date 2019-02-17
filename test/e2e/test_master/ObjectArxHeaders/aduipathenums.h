//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#pragma  once
#pragma  pack (push, 8)
/* Define an error type for this package */
enum PathErr
{
  PATH_NOERR = 0,
  PATH_INVALID,
  PATH_BADOP,
  PATH_REFUSED,
  PATH_ERR
};
enum path_type
{
  NO_PATH = 0,
  NEW_PATH,
  WC_PATH,
  FILE_PATH,
  DIR_PATH,
  DEV_PATH
};
// What kind of path?
enum path_category
{
  DRIVE_TYPE,
  UNC_TYPE,
  ROOT_TYPE,
  RELATIVE_TYPE
};
// File system types.
enum FS_TYPE
{
  NOFS,
  UKFS,
  NTFS,
  FAT,
  VFAT,
  HPFS,
  CDFS,
  HFS,
  UFS
};
enum path_status
{
  PATH_NOTEXISTS = 0x00,
  PATH_EXISTS = 0x01,
  PATH_READ = 0x02,
  PATH_READWRITE = 0x04
};
#pragma  pack (pop)
