#ifndef _ADSCODES_H
#define _ADSCODES_H 1
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
// 
//   DESCRIPTION - Definitions of the AutoCAD function request and result
//   codes used by ADS programs.
 


/*  AutoCAD to ADS program request type codes 
 */

#define RQSAVE  14 /* ACAD is saving the drawing */
#define RQEND   15 /* ACAD is ending the drawing editor */
#define RQQUIT  16 /* ACAD quits */
#define RQCFG   22 /* AutoCAD is returning from CONFIG */

/* The following are LISP to Application ONLY request codes.
   They form the interface for ADS
 */
#define RQXLOAD 100 /* Load external functions */
#define RQXUNLD 101 /* UN-Load application  */
#define RQSUBR  102 /* External subroutine request */
#define RQHUP   105 /* Acad has disconnected from the app */
#define RQXHELP 118 /* Define help for this function */

/*  ADS program to AutoCAD result type codes 
 */

#define RSRSLT   1 /* Result returned */
#define RSERR    3 /* Error in evaluation -- no result */

/*  Result value type codes 
 
       These are used in the resbuf.  These ARE NOT the same
       as the group codes used in the entity access routines, and should
       not be confused with those.  The same result buffer IS used for 
       entity records, however, in which case the restype field may take
       on many more values than those listed here.
*/
#define RTNONE    5000 /* No result */
#define RTREAL    5001 /*Real number */
#define RTPOINT   5002 /* 2D point X and Y only */
#define RTSHORT   5003 /* Short integer */
#define RTANG     5004 /* Angle */
#define RTSTR     5005 /* String */
#define RTENAME   5006 /* Entity name */
#define RTPICKS   5007 /* Pick set */
#define RTORINT   5008 /* Orientation */
#define RT3DPOINT 5009 /* 3D point - X, Y, and Z */
#define RTLONG    5010 /* Long integer */
#define RTVOID    5014 /* Blank symbol */
#define RTLB      5016 /* list begin */
#define RTLE      5017 /* list end */
#define RTDOTE    5018 /* dotted pair */
#define RTNIL     5019 /* nil */
#define RTDXF0    5020 /* DXF code 0 for ads_buildlist only */
#define RTT       5021 /* T atom */
#define RTRESBUF  5023 /* resbuf */
#define RTMODELESS 5027 /* interrupted by modeless dialog */


// These next two codes are added for developer convenience and are
// not supported by entity access, dxf, xdata or xrecord routines.
// They are, however, supported by the resbuf utility functions
// (acutBuildList, acutNewRb and acedInvoke).
//
#define RTLONG_PTR 5030 // integer value with pointer precision
#define RTINT64    5031 // integer value with 64-bit precision

#define RTCOROUTINEINFO 5035 /* For Internal Use Only */


/* The following RT codes are for the ADS program interface.
   They are used to signal success or failure (error) of the
   ADS library functions.  RTFAIL in particular means that 
   the link has failed (most likely because AutoLISP has
   died or exited), and the application should cleanup and exit.
*/
#define RTNORM    5100 /* Request succeeded */
 
/* Various error codes returned to ADS application by library
 */
#define RTERROR          (-5001) // Some other error
#define RTCAN            (-5002) // User cancelled request -- Ctl-C
#define RTREJ            (-5003) // AutoCAD rejected request -- invalid
#define RTFAIL           (-5004) // Link failure -- Lisp probably died 
#define RTKWORD          (-5005) // Keyword returned from getxxx() routine
#define RTINPUTTRUNCATED (-5008) // Input didn't all fit in the buffer
 
/* Message codes for use with modeless Windows dialogs
 */

/* Message codes for use with modeless Windows dialogs
   Note that WM_USER is defined as 0x0400
*/
#ifndef WM_ACAD_KEEPFOCUS
#ifndef WM_USER
#define WM_ACAD_KEEPFOCUS (0x0400+0x6D01)
#else
#define WM_ACAD_KEEPFOCUS (WM_USER+0x6D01)
#endif   
#endif

#endif
