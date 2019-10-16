//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ACAPPVAR_H
#  define ACAPPVAR_H
#  include "acdb.h"
#  include "acadstrc.h"
#  pragma  pack (push, 8)
enum
{
  kGroupsOn = 0x01,
  kHatchAssocOn = 0x02
};
class AcDbAppSystemVariables
{
public:
  inline AcDbAppSystemVariables();
  inline ~AcDbAppSystemVariables()
  {
  }
  Acad::ErrorStatus setAttdia(bool value, bool bUndo = false);
  inline bool attdia() const;
  Acad::ErrorStatus setAttreq(bool, bool bUndo = false);
  inline bool attreq() const;
  Acad::ErrorStatus setBlipmode(bool, bool bUndo = false);
  inline bool blipmode() const;
  Acad::ErrorStatus setCoords(Adesk::Int16 value, bool bUndo = false);
  inline Adesk::Int16 coords() const;
  Acad::ErrorStatus setStatusbar(Adesk::Int16 value, bool bUndo = false);
  inline Adesk::Int16 statusbar() const;
  Acad::ErrorStatus setMenubar(bool value, bool bUndo = false);
  inline bool menubar() const;
  Acad::ErrorStatus setAppStatusBarUseIcons(bool value, bool bUndo = false);
  inline bool appstatusbaruseicons() const;
  Acad::ErrorStatus setDelUsedObj(Adesk::Int16, bool bUndo = false);
  inline Adesk::Int16 delUsedObj() const;
  Acad::ErrorStatus setDragmode(Adesk::Int16, bool bUndo = false);
  inline Adesk::Int16 dragmode() const;
  Acad::ErrorStatus setOsmode(Adesk::Int16 value, bool bUndo = false);
  inline Adesk::Int16 osmode() const;
  Acad::ErrorStatus setPickstyle(Adesk::Int16 value, bool bUndo = false);
  inline Adesk::Int16 pickstyle() const;
  Acad::ErrorStatus setLwdefault(AcDb::LineWeight value, bool bUndo = false);
  inline AcDb::LineWeight lwdefault() const;
  Acad::ErrorStatus setHpassoc(bool value, bool bUndo = false);
  inline bool hpassoc() const;
private:
  bool m_attdia;
  bool m_attreq;
  bool m_blipmode;
  short m_delobj;
  short m_coords;
  short m_statusbar;
  bool m_menubar;
  bool m_appstatusbaruseicons;
  short m_dragmode;
  short m_osmode;
  short m_pkstyle;
  AcDb::LineWeight m_lwdefault;
  bool m_hpassoc;
};
inline AcDbAppSystemVariables::AcDbAppSystemVariables()
  : m_attdia(true)
  , m_attreq(true)
  , m_blipmode(false)
  , m_delobj(3)
  , m_coords(0)
  , m_statusbar(1)
  , m_menubar(false)
  , m_appstatusbaruseicons(true)
  , m_dragmode(2)
  , m_osmode(0)
  , m_pkstyle(kGroupsOn)
  , m_lwdefault(AcDb::kLnWt025)
  , m_hpassoc(1)
{
}
inline bool AcDbAppSystemVariables::attdia() const
{
  return m_attdia;
}
inline bool AcDbAppSystemVariables::attreq() const
{
  return m_attreq;
}
inline bool AcDbAppSystemVariables::blipmode() const
{
  return m_blipmode;
}
inline Adesk::Int16 AcDbAppSystemVariables::coords() const
{
  return m_coords;
}
inline Adesk::Int16 AcDbAppSystemVariables::statusbar() const
{
  return m_statusbar;
}
inline bool AcDbAppSystemVariables::menubar() const
{
  return m_menubar;
}
inline bool AcDbAppSystemVariables::appstatusbaruseicons() const
{
  return m_appstatusbaruseicons;
}
inline Adesk::Int16 AcDbAppSystemVariables::delUsedObj() const
{
  return m_delobj;
}
inline Adesk::Int16 AcDbAppSystemVariables::dragmode() const
{
  return m_dragmode;
}
inline Adesk::Int16 AcDbAppSystemVariables::osmode() const
{
  return m_osmode;
}
inline Adesk::Int16 AcDbAppSystemVariables::pickstyle() const
{
  return m_pkstyle;
}
inline AcDb::LineWeight AcDbAppSystemVariables::lwdefault() const
{
  return m_lwdefault;
}
inline bool AcDbAppSystemVariables::hpassoc() const
{
  return m_hpassoc;
}
#  pragma  pack (pop)
#endif
