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
//   AutoCAD Release 12 On-Line application Error codes (set in the "_ERRNO"
//   system variable).
//
//   NOTE:  The "_ERRNO" values are subject to change with major  
//   releases of AutoCAD.  To ensure proper error diagnostics, be
//   sure to include the proper version of this file with your program.

#ifndef  _OL_ERRNO_H
#define  _OL_ERRNO_H

#define  OL_GOOD	0 /* Everything is just fine */
#define  OL_ESNVALID    1 /* Invalid symbol table name */
#define  OL_ENAMEVALID  2 /* Invalid name (entity or ss) value */
#define  OL_ESSMAX      3 /* Exceeded max number of sel. sets */
#define  OL_ESSVALID    4 /* Invalid selection set */
#define  OL_EBDEVALID   5 /* Improper use of block def. entity */
#define  OL_EXDEVALID   6 /* Improper use of xref entity */
#define  OL_ENTSELPICK  7 /* Entity selection (failed pick) */
#define  OL_EEOEF       8 /* End of entity file */
#define  OL_EEOBD       9 /* End of Block def. file */
#define  OL_EEMPDB     10 /* Failure of entlast */
#define  OL_EDELVPORT  11 /* Illegal entdel of VPORT */
#define  OL_EACQPLINE  12 /* Operation not allowed during PLINE */
#define  OL_EHANDLE    13 /* Invalid handle */
#define  OL_ENOHAND    14 /* Handles not enabled */
#define  OL_ETRANS     15 /* Invalid trans request */
#define  OL_EXSPACE    16 /* Invalid space trans request */
#define  OL_EDELENT    17 /* Invalid use of deleted entity */
#define  OL_ETBLNAME   18 /* Invalid table name */
#define  OL_ETBLARG    19 /* Invalid table function argument */
#define  OL_ERDONLY    20 /* Attempt to set read only variable */
#define  OL_ENONZERO   21 /* Zero value invalid */
#define  OL_ERANGE     22 /* Value out of range */
#define  OL_ERGBUSY    23 /* Complex regen in progress */
#define  OL_EMMTYPE    24 /* Attempt to change entity type */
#define  OL_EMMLAY     25 /* Bad layer name */
#define  OL_EMMLT      26 /* Bad linetype name */
#define  OL_EMMCOLOR   27 /* Bad color name */
#define  OL_EMMSTYLE   28 /* Bad text style name */
#define  OL_EMMSHAPE   29 /* Bad shape name */
#define  OL_EMMFTYPE   30 /* Bad field for entity type */
#define  OL_EMODDEL    31 /* Attempted entmod of deleted entity */
#define  OL_EMODSEQ    32 /* Attempted entmod of SEQEND */
#define  OL_EMODHAND   33 /* Attempt to change handle */
#define  OL_EMODVPVIS  34 /* Illegal modification of vport vis. */
#define  OL_EMMLL      35 /* Entity on locked layer */
#define  OL_EMKTYPE    36 /* Bad entity type */
#define  OL_EMKPLINE   37 /* Bad PLINE entity */
#define  OL_EMKCMPLX   38 /* Incomplete complex ent in block */
#define  OL_EMKBNAME   39 /* Invalid block name field */
#define  OL_EMKBFLAG   40 /* Duplicate block flag fields */
#define  OL_EMKDBNAME  41 /* Duplicate block name fields */
#define  OL_EMKNORM    42 /* Bad normal vector */
#define  OL_EMKNOBNM   43 /* Missing block name */
#define  OL_EMKNOBFLG  44 /* Missing block flags */
#define  OL_EMKANON    45 /* Invalid anonymous block */
#define  OL_EMKBLOCK   46 /* Invalid block definition entity */
#define  OL_EMKMANDF   47 /* Manditory field missing */
#define  OL_EMMXDTYPE  48 /* Unrecognized extended data type */
#define  OL_EMMXDNEST  49 /* Improper nesting of list in xdata */
#define  OL_EMMXDAPPID 50 /* Improper location of APPID field */
#define  OL_EMMXDSIZE  51 /* Exceeded maximum xdata size */
#define  OL_ENTSELNULL 52 /* Entity selection (null response) */
#define  OL_EMXDAPPID  53 /* Entmod/entmake with duplicate appid */
#define  OL_EMMVPORT   54 /* Entmod/entmake of VPORT failed */
#define  OL_INVEXT     55 /* Entmake of XDEF/XREF/XDEP */
#define  OL_EFLTR1     56 /* Bad SSGET filter: premature end */
#define  OL_EFLTR2     57 /*       "     missing test operand */
#define  OL_EFLTR3     58 /*       "     invalid opcode string */
#define  OL_EFLTR4     59 /*       "     void clause/bad nesting */
#define  OL_EFLTR5     60 /*       "     beg/end clause mismatch */
#define  OL_EFLTR6     61 /*       "     wrong # of XOR/NOT args */
#define  OL_EFLTR7     62 /*       "     max nesting exceeded */
#define  OL_EFLTR8     63 /*       "     invalid group code */
#define  OL_EFLTR9     64 /*       "     invalid string test */
#define  OL_EFLTR10    65 /*       "     invalid vector test */
#define  OL_EFLTR11    66 /*       "     invliad real test */
#define  OL_EFLTR12    67 /*       "     invalid integer test */
#define  OL_TABNOT     68 /* Digitizer isn't a tablet */
#define  OL_TABNOCAL   69 /* Tablet isn't calibrated. */
#define  OL_TABERR     70 /* Invalid (tablet) arguments */
#define  OL_ENEWRB     71 /* Unable to allocate resbuf */
#define  OL_ENULLPTR   72 /* NULL Pointer detected */ 
#define  OL_EOPEN      73 /* Can't open file */ 
#define  OL_ELOADED    74 /* Application is already loaded */ 
#define  OL_EMAXAPP    75 /* Number of apps exceeds limit */ 
#define  OL_EEXEC      76 /* Unable to execute the application */
#define  OL_EVERSION   77 /* Incompatible version number */ 
#define  OL_EDENIED    78 /* Unable to unload nested ADS app */
#define  OL_EREFUSE    79 /* The application refused to XUNLOAD */ 
#define  OL_ENOTLOADED 80 /* The application isn't loaded */ 
#define  OL_ENOMEM     81 /* Out of memory */
#define  OL_EXFMVALID  82 /* Invalid transformation matrix */
#define  OL_ESYMNAM    83 /* Invalid symbol name */
#define  OL_ESYMVAL    84 /* Invalid symbol value */
#define  OL_NONDIALOG  85 /* Not allowed while dialogue up */

      /*  Error codes 86-91 reserved.  */

#define  OL_ECMDINP    92  /* Illegal while command in progress */
#define  OL_EBADTYPE   93  /* Bad value type */
#define  OL_EBADVPID   94  /* Invalid viewport id */
#define  OL_EBADVIEW   95  /* Bad view definition */
#define  OL_EGCODE     96  /* Unexpected group code */
#define  OL_EGDUP      97  /* Duplicate group code specified */
#define  OL_EBADSSMOD  98  /* Bad ssget mode string */
#define  OL_EARGMATCH  99  /* Arguments are not in agreement */
#define  OL_SVRECURSE  100 /* Do not call setvar recursively */
#define  OL_MODOPEN    101 /* Attempt to modify an open entity */
#define  OL_NOTENTITY  102 /* ENTNEXT on a non-entity */
#define  OL_BADPLMOD   103 /* Invalid modification of a pline */
#define  OL_BADCTLSTR  104 /* Badly nested control string */
#define  OL_EXDICT_PR  105 /* Failure to modify extension dict 
                              or Persistent reactor on r12 entity */

/* If you add a new error code, be sure to add it to the set of errors
   described by ADS_PERR.C.  In addition, please update the following:
 */
#define  MAX_OL_ERRNO  105 /* Could be used for range check */

#endif
