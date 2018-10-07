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
// DESCRIPTION:C ADS definitions supported in Arx environment, plus
//             a few acrxXX function definitions.
//
#ifndef _ADSRXDEF_H_
#	define _ADSRXDEF_H_	1
#	pragma  pack (push, 8)
typedef struct fchnd
{
	struct fchnd* next;
	int fcode;
	int (*fhdl) ();
} FunHandList;
class AcRxGenHand;
/* The following typedef is used for maintaining a connection between
 * AutoLISP and an RXADS application.  It is for internal use only
 */
class RxADSAppTableEntryType
{
public:
	int lflag;
	ACHAR* appname;
	Adesk::LongPtr apphandle;
	int ads_fcode;
	int ads_invkcnt;
	struct resbuf* ads_argl;
	FunHandList* ads_fhdl;
	AcRxGenHand* modhandle;
	resbuf* ads_ret;
	int ads_rettype;
};
#	pragma  pack (pop)
#endif
