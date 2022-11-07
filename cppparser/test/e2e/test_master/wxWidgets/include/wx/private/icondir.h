///////////////////////////////////////////////////////////////////////////////
// Name:        wx/private/icondir.h
// Purpose:     Declarations of structs used for loading MS icons
// Author:      wxWidgets team
// Created:     2017-05-19
// Copyright:   (c) 2017 wxWidgets team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////
#ifndef _WX_PRIVATE_ICONDIR_H_
#  define _WX_PRIVATE_ICONDIR_H_
#  include "wx/defs.h"
// Structs declared here are used for loading group icons from
// .ICO files or MS Windows resources.
// Icon entry and directory structs for .ICO files and
// MS Windows resources are very similar but not identical.
#  if  wxUSE_ICO_CUR
#    if  wxUSE_STREAMS
// icon entry in .ICO files
struct ICONDIRENTRY
{
  wxUint8 bWidth;
  wxUint8 bHeight;
  wxUint8 bColorCount;
  wxUint8 bReserved;
    // these two are different in icons and cursors:
                                          // icon           or  cursor
  wxUint16 wPlanes;
  wxUint16 wBitCount;
  wxUint32 dwBytesInRes;
  wxUint32 dwImageOffset;
};
// icon directory in .ICO files
struct ICONDIR
{
  wxUint16 idReserved;
  wxUint16 idType;
  wxUint16 idCount;
};
#    endif
#    ifdef __WINDOWS__
#      pragma  pack(push)
#      pragma  pack(2)
// icon entry in MS Windows resources
struct GRPICONDIRENTRY
{
  wxUint8 bWidth;
  wxUint8 bHeight;
  wxUint8 bColorCount;
  wxUint8 bReserved;
    // these two are different in icons and cursors:
                                          // icon           or  cursor
  wxUint16 wPlanes;
  wxUint16 wBitCount;
  wxUint32 dwBytesInRes;
  wxUint16 nID;
};
// icon directory in MS Windows resources
struct GRPICONDIR
{
  wxUint16 idReserved;
  wxUint16 idType;
  wxUint16 idCount;
  GRPICONDIRENTRY idEntries[1];
};
#      pragma  pack(pop)
#    endif
#  endif
#endif
