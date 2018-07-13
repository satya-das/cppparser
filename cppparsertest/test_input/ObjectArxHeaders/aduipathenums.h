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

#pragma pack (push, 8)

/* Define an error type for this package */
typedef enum {
    PATH_NOERR = 0,
    PATH_INVALID,        /* invalid pathname    */
    PATH_BADOP,          /* invalid operation for path type */
    PATH_REFUSED,        /* operation refused.  This    error code is
                           returned when an operation (other than
                           Empty) would leave an empty path. */
    PATH_ERR            /* catchall error code */
} PathErr;

typedef enum {
    NO_PATH = 0,        /* new pathname object, no data yet    */
    NEW_PATH,           /* the path doesn't represent an existing file/dir */
    WC_PATH,            /* the path represents a wildcard specification */
    FILE_PATH,          /* the path represents a file */
    DIR_PATH,           /* the path represents a directory */
    DEV_PATH,           /* the path represents a device (LPT1: etc.) */
} path_type;

// What kind of path?
enum path_category {
    DRIVE_TYPE,         // ie. "c:\\" drive letter, colon, single backslash.
    UNC_TYPE,           // ie. \\jackl\public. A double backslash machine name backslash share name
    ROOT_TYPE,          // ie. a single backslash.
    RELATIVE_TYPE       
};
// File system types.
enum FS_TYPE {
    NOFS,        // no media in drive (floppy, etc.)
    UKFS,        // unknown, never heard of it!
    NTFS,        // NT file system 
    FAT,         // DOS 8.3 file system
    VFAT,        // Win95 LFN file system
    HPFS,        // OS/2 File system
    CDFS,        // ISO9660/High Sierra
    HFS,         // Mac HFS volume type
    UFS          // UNIX volume type
};

enum path_status{
    PATH_NOTEXISTS = 0x00,      // the file not exists
    PATH_EXISTS    = 0x01,      // the file exists
    PATH_READ      = 0x02,      // we have read access
    PATH_READWRITE = 0x04       // we can read and write it
};


#pragma pack (pop)

