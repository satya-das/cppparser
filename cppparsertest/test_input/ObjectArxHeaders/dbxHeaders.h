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
// Written by Cyrille Fauvel
// Autodesk Developer Technical Services

//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//----- This file is preprocessor symbol driven.
//----- Define:
//-----		_HLR_SUPPORT_ to include and import HLR API headers and libs in your project.
//-----		_BREP_SUPPORT_ to include and import BRep API headers and libs in your project.
//-----		_AMODELER_SUPPORT_ to include and import AModeler API headers and libs in your project.
//-----		_DBX_HOST_APPLICATION_ if you are writting an ObjectDBX host application.

//-----------------------------------------------------------------------------
//----- Note libs must be included in the following order:
//----- RxApi.lib, AcDb20.lib, ...
//----- This headers file will make sure to set the order properly
#pragma pack (push, 8)
#pragma warning (disable: 4311 4312)

#ifdef _MANAGED
#pragma warning( disable : 4561 )
#endif

//-----------------------------------------------------------------------------
#ifdef _FULLDEBUG_
#define AC_FULL_DEBUG 1
#pragma message ("Warning! _FULLDEBUG_ is deprecated.")
#endif

#ifndef AC_FULL_DEBUG
#pragma comment (lib ,"rxapi.lib")
#pragma comment (lib ,"acdb23.lib")
#pragma comment (lib ,"acge23.lib")
#pragma comment (lib ,"acISMobj23.lib")
#pragma comment (lib ,"acgiapi.lib")
#pragma comment (lib ,"axdb.lib")
#pragma comment (lib ,"ac1st23.lib") 
#ifdef _BREP_SUPPORT_
	#pragma comment (lib ,"acgex23.lib")
	#pragma comment (lib ,"acbr23.lib")
#endif // _BREP_SUPPORT_
#else // AC_FULL_DEBUG
#pragma comment (lib ,"rxapi.lib")
#pragma comment (lib ,"acdb23d.lib")
#pragma comment (lib ,"acge23d.lib")
#pragma comment (lib ,"acISMobj23d.lib")
#pragma comment (lib ,"acgiapi.lib")
#pragma comment (lib ,"axdb.lib")
#pragma comment (lib ,"ac1st23d.lib") 
#ifdef _BREP_SUPPORT_
	#pragma comment (lib ,"acgex23d.lib")
	#pragma comment (lib ,"acbr23d.lib")
#endif // _BREP_SUPPORT_
#endif // AC_FULL_DEBUG

#ifdef _HLR_SUPPORT_
	#pragma comment (lib ,"AsdkHlrApi23.lib")
#endif

#ifdef _AMODELER_SUPPORT_
	#pragma comment (lib, "aecmodeler.lib")
#endif // _AMODELER_SUPPORT_

#pragma comment (lib, "acdbmgd.lib")

//----- Rx Kernels
#include "acmem.h"
#include "adesk.h"
#include "adeskabb.h"
#include "acadstrc.h"
#include "rxdefs.h"
#include "rxnames.h"
#include "rxboiler.h"
#include "rxclass.h"
#include "AcDbClassIter.h"
#include "rxdict.h"
#include "rxobject.h"
#include "rxsrvice.h"
#include "rxkernel.h"
#include "rxdlinkr.h"
#include "rxregsvc.h"
#include "rxevent.h"
#include "rxiter.h"
#include "rxditer.h"
#include "appinfo.h"
#include "rxprotevnt.h"

//----- Rx Un-Classified
#include "PAL/api/codepgid.h"	//----- This list contains identifiers for all of the code pages used with AutoCAD
#include "AcHeapOpers.h"
#include "AcString.h"
#include "AdAChar.h"
#include "acly.h"

//----- Db sub-system
#include "acarray.h"
#include "dbhandle.h"
#include "dbid.h"
#include "dbidar.h"
#include "dbcolor.h"
#include "dbptrar.h"
#include "drawable.h"
#include "dbsecurity.h"
#include "dbboiler.h"
#include "acdb.h"
#include "acdbabb.h"
#include "dbAlignment.h"
#include "dbfiler.h"
#include "dbintar.h"
#include "dbsubeid.h"
#include "dbaudita.h"
//#include "dbdimvar.h" !!! Never include that file !!!
#include "dbmain.h"
#include "dbdict.h"
#include "dbdate.h"
#include "dbsymtb.h"
#include "dbsymutl.h"
#include "dbdictdflt.h"
#include "dbDictUtil.h"
#include "dbcurve.h"
#include "dbmtext.h"
#include "dbdim.h"
#include "dbDimData.h"
#include "dbents.h"
#include "dbeval.h"
#include "AcField.h"
#include "DbField.h"
#include "dbtable.h"
#include "dbTableStyle.h"
#include "dbdynblk.h"
#include "dbproxy.h"
#include "dbfcf.h"
#include "dbapserv.h"
#include "dbgroup.h"
#include "dbhatch.h"
#include "dblead.h"
#include "dbelipse.h"
#include "dbspline.h"
#include "dbray.h"
#include "dbsol3d.h"
#include "dbregion.h"
#include "dbacis.h"
#include "dbbody.h"
#include "dbframe.h"
#include "dbole.h"
#include "imgdef.h"
#include "imgvars.h"
#include "dbimage.h"
#include "imgent.h"
#include "dblstate.h"
#include "dbmstyle.h"
#include "dbmline.h"
#include "dbxline.h"
#include "dbxrecrd.h"
#include "achapi.h"
#include "dbDataTable.h"
#include "dbfilter.h"
#ifndef _MANAGED
#include "dbgrip.h"
#endif
#include "dbappgrip.h"
#include "dbidmap.h"
#include "dbindex.h"
#include "dblaymgrrctr.h"
#include "dblayout.h"
#include "dbmaterial.h"
#include "dbpl.h"
#include "dbtrans.h"
#include "sorttab.h"
#include "xreflock.h"

//----- Db utils
#include "acgiutil.h"
#include "dbcfilrs.h"
#include "dblyfilt.h"
#include "dblyindx.h"
#include "dbspfilt.h"
#include "dbspindx.h"
#include "dbplhldr.h"
#include "dbxutil.h"
#include "idgraph.h"
#include "summinfo.h"
#include "textengine.h"
#include "graph.h"
#include "xgraph.h"
#include "dbplotsettings.h"
#include "dbplotsetval.h"
#include "AcDbLMgr.h"
#include "acappvar.h"


//----- AcGi Sub-system
#include "acgi.h"
#include "AcGiLineAttributes.h"
#include "AcGiLineAttrUtils.h"
#include "acgimaterial.h"
#include "AcGiStyleAttributes.h"
#include "linetypeengine.h"

//----- ADS & Db un-classified
#include "acutil.h"
#include "acestext.h"
#include "adsdef.h"
#include "acdbads.h"
#include "acutads.h"
#include "ads.h"
#include "adscodes.h"
#include "adsmigr.h"
#include "migrtion.h"

//----- Db Smart-pointers
#include "dbobjptr.h"

//----- Ge sub-system
#include "geassign.h"
#include "geblok2d.h"
#include "geblok3d.h"
#include "geell2d.h"
#include "geell3d.h"
#include "gecone.h"
#include "gecylndr.h"
#include "gesphere.h"
#include "getorus.h"
#include "geray2d.h"
#include "geray3d.h"
#include "gessint.h"
#include "gedwgio.h"
#include "gedxfio.h"
#include "gefiler.h"
#include "gecspl2d.h"
#include "gecspl3d.h"
#include "gepos2d.h"
#include "gepos3d.h"
#include "geoffc2d.h"
#include "geoffc3d.h"
#include "geoffsf.h"
#include "genurb2d.h"
#include "genurb3d.h"
#include "genurbsf.h"	//----- Representation for a non-uniform, rational BSpline surface.
#include "gecsint.h"
#include "geextc2d.h"
#include "geextc3d.h"
#include "geextsf.h"
#include "gecomp2d.h"
#include "gecomp3d.h"
#include "gecint2d.h"
#include "gecint3d.h"
#include "gescl2d.h"
#include "gescl3d.h"
#include "geclip2d.h"
#include "gexbndsf.h"
#include "gecbndry.h"
#include "geapln3d.h"
#include "gearc2d.h"
#include "gearc3d.h"
#include "gebndpln.h"
#include "gecurv2d.h"
#include "gecurv3d.h"
#include "gedblar.h"
#include "gedll.h"
#include "geent2d.h"
#include "geent3d.h"
#include "gefileio.h"
#include "gegbl.h"
#include "gegblabb.h"
#include "gegblge.h"
#include "gegblnew.h"
#include "geintarr.h"
#include "geintrvl.h"
#include "gekvec.h"
#include "gelent2d.h"
#include "gelent3d.h"
#include "gelibver.h"
#include "geline2d.h"
#include "geline3d.h"
#include "gelnsg2d.h"
#include "gelnsg3d.h"
#include "gemat2d.h"
#include "gemat3d.h"
#include "gepent2d.h"
#include "gepent3d.h"
#include "geplanar.h"
#include "geplane.h"
#include "geplin2d.h"
#include "geplin3d.h"
#include "gepnt2d.h"
#include "gepnt3d.h"
#include "geponc2d.h"
#include "geponc3d.h"
#include "geponsrf.h"
#include "gept2dar.h"
#include "gept3dar.h"
#include "gesent2d.h"
#include "gesent3d.h"
#include "gesurf.h"
#include "getol.h"
#include "gevc2dar.h"
#include "gevc3dar.h"
#include "gevec2d.h"
#include "gevec3d.h"
#include "gevptar.h"

//----- .NET extensions
#ifdef _MANAGED
#include <vcclr.h>
#include "mgdinterop.h"
#endif

//----- Db COM extensions
#ifdef __ATLCOM_H__
#ifndef _ACRXAPP
#include "axdb.h"		// axdb_i.c
#else
#include "acadi.h"		// acadi_i.c
#endif // _ACRXAPP
#include "oleaprot.h"
#include "category.h"
#include "axobjref.h"
#include "axboiler.h"
#include "acpi.h"		// acpi_i.c
#include "opmdialog.h"
#include "opmimp.h"
#include "opmdrvr.h"
#include "opmext.h"
#include "axtempl.h"
#include "axpnt2d.h"
#include "axpnt3d.h"
#include "axmat3d.h"
#include "axlock.h"
#include "dynprops.h"
#include "acpexctl.h"	// acpexctl_i.c
#include "AcPp.h"		// AcPp_i.c
#endif // __ATLCOM_H__

//----- AutoCAD utils
#include "acut.h"
#include "acutmem.h"
#include "acutmigr.h"

//----- AutoCAD Graphic System
#include "acgs.h"		//----- Access to AutoCAD Graphics System.

//----- AutoCAD Inet API
#include "inetstrc.h"

//----- Utils
#include "acsymutl.h"	//----- Utilities for working with symbol names, symbol records, and symbol tables.
#include "dbxEntryPoint.h"

//----- ObjectDBX specific
#ifdef _DBX_HOST_APPLICATION_
#include "truetypetext.h"
#include "dbhaext.h"
#include "acdbxref.h"
#endif // _DBX_HOST_APPLICATION_

//----- BRep
#ifdef _BREP_SUPPORT_
#include "brbctrav.h"
#include "brbetrav.h"
#include "brbftrav.h"
#include "brbrep.h"
#include "brbstrav.h"
#include "brbvtrav.h"
#include "brcplx.h"
#include "brcstrav.h"
#include "bredge.h"
#include "brelem.h"
#include "brelem2d.h"
#include "breltrav.h"
#include "brent.h"
#include "brentrav.h"
#include "brface.h"
#include "brfltrav.h"
#include "brgbl.h"
#include "brhit.h"
#include "brletrav.h"
#include "brloop.h"
#include "brlvtrav.h"
#include "brm2dctl.h"
#include "brmctl.h"
#include "brment.h"
#include "brmesh.h"
#include "brmesh2d.h"
#include "brmetrav.h"
#include "brnode.h"
#include "brprops.h"
#include "brsftrav.h"
#include "brshell.h"
#include "brtrav.h"
#include "brvetrav.h"
#include "brvltrav.h"
#include "brvtx.h"
#endif // _BREP_SUPPORT_

//----- Hidden Line removal API
#ifdef _HLR_SUPPORT_
#include "Hlr.h"
#include "BasePex.h"
#endif // _HLR_SUPPORT_

//----- Amodeler
#ifdef _AMODELER_SUPPORT_
#include "amodeler.h"
#include "body.h"
#include "callback.h"
#include "check.h"
#include "circle3d.h"
#include "color.h"
#include "curve.h"
#include "darray.h"
#include "deviat.h"
#include "dxfinpln.h"
#include "dxfout.h"
#include "edge.h"
#include "entity.h"
#include "enums.h"
#include "epsilon.h"
#include "errcodes.h"
#include "face.h"
#include "flags.h"
#include "global.h"
#include "interval.h"
#include "ipoint2d.h"
#include "ipoint3d.h"
#include "ivect2d.h"
#include "ivect3d.h"
#include "line3d.h"
#include "massert.h"
#include "morphmap.h"
#include "plane.h"
#include "point2d.h"
#include "point3d.h"
#include "surface.h"
#include "transf3d.h"
#include "util.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vertdata.h"
#include "vertex.h"
#include "vertsurf.h"
#include "wallcrnr.h"
#endif // _AMODELER_SUPPORT_

#pragma pack (pop)
