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

#ifndef _adsmigr_h
#define _adsmigr_h 1


#define ads_malloc	acad_malloc
#define ads_free	acad_free
#define ads__msize	acad__msize
#define ads_realloc acad_realloc
#define ads_calloc	acad_calloc
#define ads_strdup	acad__strdup

// aced related #defines.
//
#define	ads_getappname	acedGetAppName
#define	ads_update	acedUpdate
#define	ads_command	MustSwitchTo_acedCommandC_or_acedCommandS - - !
#define	ads_cmd	MustSwitchTo_acedCmdC_or_acedCmdS
#define	ads_regfunc	acedRegFunc
#define	ads_usrbrk	acedUsrBrk
#define	ads_defun	acedDefun
#define	ads_setfunhelp	acedSetFunHelp
#define	ads_undef	acedUndef
#define	ads_getfuncode	acedGetFunCode
#define	ads_getargs	acedGetArgs
#define	ads_retlist	acedRetList
#define	ads_retval	acedRetVal
#define	ads_retpoint	acedRetPoint
#define	ads_retstr	acedRetStr
#define	ads_retname	acedRetName
#define	ads_retint	acedRetInt
#define	ads_retreal	acedRetReal
#define	ads_rett	acedRetT
#define	ads_retnil	acedRetNil
#define	ads_retvoid	acedRetVoid
#define	ads_entsel	acedEntSel
#define	ads_nentsel	acedNEntSel
#define	ads_nentselp	acedNEntSelP
#define	ads_ssget	acedSSGet

#define	ads_ssgetfirst	acedSSGetFirst
#define	ads_sssetfirst	acedSSSetFirst

#define	ads_ssfree	acedSSFree
#define	ads_sslength	acedSSLength
#define	ads_ssadd	acedSSAdd
#define	ads_ssdel	acedSSDel
#define	ads_ssmemb	acedSSMemb
#define	ads_ssname	acedSSName
#define	ads_ssnamex	acedSSNameX
#define	ads_ssGetKwordCallbackPtr	acedSSGetKwordCallbackPtr
#define	ads_ssSetKwordCallbackPtr	acedSSSetKwordCallbackPtr
#define	ads_ssGetOtherCallbackPtr	acedSSGetOtherCallbackPtr
#define	ads_ssSetOtherCallbackPtr	acedSSSetOtherCallbackPtr
#define	ads_setvar	acedSetVar
#define	ads_initget	acedInitGet
#define	ads_getsym	acedGetSym
#define	ads_putsym	acedPutSym
#define	ads_help	acedHelp
#define	ads_fnsplit	acedFNSplit
#define	ads_trans	acedTrans
#define	ads_arxloaded	acedArxLoaded
#define	ads_arxload	acedArxLoad
#define	ads_arxunload	acedArxUnload
#define	ads_invoke	acedInvoke
#define	ads_getvar	acedGetVar
#define	ads_findfile	acedFindFile
#define	ads_findtrustedfile	acedFindTrustedFile
#define	ads_agetenv	acedGetEnv
#define	ads_asetenv	acedSetEnv
#define	ads_getenv	acedGetEnv
#define	ads_setenv	acedSetEnv
#define	ads_agetcfg	acedGetCfg
#define	ads_asetcfg	acedSetCfg
#define	ads_getcfg	acedGetCfg
#define	ads_setcfg	acedSetCfg
#define	ads_getstring acedGetString
#define	ads_menucmd	acedMenuCmd
#define	ads_prompt	acedPrompt
#define	ads_alert	acedAlert
#define	ads_getangle	acedGetAngle
#define	ads_getcorner	acedGetCorner
#define	ads_getdist	acedGetDist
#define	ads_getorient	acedGetOrient
#define	ads_getpoint	acedGetPoint
#define	ads_getint	acedGetInt
#define	ads_getkword	acedGetKword
#define	ads_getreal	acedGetReal
#define	ads_getinput	acedGetInput
#define	ads_vports	acedVports
#define	ads_textscr	acedTextScr
#define	ads_graphscr	acedGraphScr
#define	ads_textpage	acedTextPage
#define	ads_redraw	acedRedraw
#define	ads_osnap	acedOsnap
#define	ads_grread	acedGrRead
#define	ads_grtext	acedGrText
#define	ads_grdraw	acedGrDraw
#define	ads_grvecs	acedGrVecs
#define	ads_xformss	acedXformSS
#define	ads_draggen	acedDragGen
#define	ads_setview	acedSetView
#define	ads_getfiled	acedGetFileD
#define	ads_textbox	acedTextBox
#define	ads_tablet	acedTablet
#define	ads_getcname	acedGetCName

// AcDb related #defines that are available to ObjectDBX
// applications.
#define	ads_xdroom	acdbXdRoom
#define	ads_xdsize	acdbXdSize

/* NOTE that the result is the SECOND argument,
   consistent with ADS usage.  The standard C ones require <string.h> */
#ifdef __STDC__
#define ads_name_set(from, to)  (memcpy(to, from, sizeof(ads_name)))
#define ads_point_set(from,to)  (memcpy(to, from, sizeof(ads_point)))
#else
#define ads_name_set(from, to)  (*(to)= *(from), (to)[1]=(from)[1])
#define ads_point_set(from, to) (*(to)= *(from), (to)[1]=(from)[1], (to)[2]=(from)[2])
#endif  /* !__STDC__ */

/* Define null value for ads_names.  These values are NOT guaranteed valid;
   that is, there is no actual guarantee (such as C gives with NULL) that the
   system will never under any circumstances generate the values as valid data.
   The correct values will be created as part of the Lisp reinitialization
   project, if we go through with that one, and will then be inserted here.
   */
#define ads_name_clear(name)    name[0] = name[1] = 0
#define ads_name_nil(name)      (name[0] == 0 && name[1] == 0)
#define ads_name_equal(name1, name2)  (name1[0]==name2[0] \
                                       && name1[1]==name2[1])


// AcDb related #defines that are not currently available
// to ObjectDBX applications.  7/14/98
#define	ads_entdel	acdbEntDel
#define	ads_entgetx	acdbEntGetX
#define	ads_entget	acdbEntGet
#define	ads_entlast	acdbEntLast
#define	ads_entnext	acdbEntNext
#define	ads_entupd	acdbEntUpd
#define	ads_entmod	acdbEntMod
#define	ads_entmake	acdbEntMake
#define	ads_entmakex	acdbEntMakeX
#define	ads_tblnext	acdbTblNext
#define	ads_tblsearch	acdbTblSearch
#define	ads_namedobjdict	acdbNamedObjDict
#define	ads_dictsearch	acdbDictSearch
#define	ads_dictnext	acdbDictNext
#define	ads_dictrename	acdbDictRename
#define	ads_dictremove	acdbDictRemove
#define	ads_dictadd	acdbDictAdd
#define	ads_tblobjname	acdbTblObjName
#define	ads_handent	acdbHandEnt
#define	ads_inters	acdbInters
#define	ads_snvalid	acdbSNValid
#define	ads_xstrsave	acdbXStrSave
#define	ads_xstrcase	acdbXStrCase
#define	ads_regapp	acdbRegApp
#define	ads_fail	acdbFail
#define	ads_angtos	acdbAngToS
#define	ads_rangtos	acdbRawAngToS
#define	ads_rtos	acdbRToS
#define	ads_angtof	acdbAngToF
#define	ads_rangtof	acdbRawAngToF
#define	ads_distof	acdbDisToF
// Obsolete: we don't save as r12 anymore, so the xsave12 arg
// is ignored.
#define ads_regappx(appname, xsave12)   acdbRegApp(appname)


// Functions that are now in acutil dll
#define	ads_printf	acutPrintf
#define	ads_cvunit	acutCvUnit
#define	ads_wcmatch	acutWcMatch
#define	ads_angle	acutAngle
#define	ads_distance	acutDistance
#define	ads_polar	acutPolar
#define	ads_isalpha	acutIsAlpha
#define	ads_isupper	acutIsUpper
#define	ads_islower	acutIsLower
#define	ads_isdigit	acutIsDigit
#define	ads_isxdigit	acutIsXDigit
#define	ads_isspace	acutIsSpace
#define	ads_ispunct	acutIsPunct
#define	ads_isalnum	acutIsAlNum
#define	ads_isprint	acutIsPrint
#define	ads_isgraph	acutIsGraph
#define	ads_iscntrl	acutIsCntrl
#define	ads_toupper	acutToUpper
#define	ads_tolower	acutToLower
#define	ads_newrb	acutNewRb
#define	ads_relrb	acutRelRb
#define	ads_buildlist	acutBuildList

#endif // !adsmigr_h
