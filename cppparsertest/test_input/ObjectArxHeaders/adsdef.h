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

#ifndef _adsdef_h
#define _adsdef_h 1

#include <stdint.h>
#include "AdAChar.h"


#define TRUE    1
#define FALSE   0
#ifndef EOS
#define EOS     ACRX_T('\0')
#endif

#pragma pack(push, 8)

typedef double   ads_real;
typedef ads_real ads_point[3];
#if !defined(_WIN64) && !defined(_AC64)
typedef int32_t ads_name[2];
typedef int32_t *ads_namep;
#else
typedef int64_t ads_name[2];
typedef int64_t *ads_namep;
#endif
typedef ads_real ads_matrix[4][4];

/* When you want something that's explicitly a pointer type and not an array
   type, use ads_pointp and ads_namep.  Remember that if your function takes an
   *array* of points, it still declares ads_point[] foo; */
typedef ads_real *ads_pointp;

/* To protect macro-redefinition of the X, Y, Z, and T enumerated
   constants by legacy #define's, we remove their definition. */

#ifdef X
#undef X
#endif
#ifdef Y
#undef Y
#endif
#ifdef Z
#undef Z
#endif
#ifdef T
#undef T
#endif

#ifndef _XYZT_DEFINED
#define _XYZT_DEFINED
enum { X = 0, Y = 1, Z = 2 }; /* The coordinates of a point. */
enum { T = 3 };               /* The translation vector of a 3D matrix */
#endif // !_XYZT_DEFINED

/* The PAUSE token for ads_command and ads_cmd
 */
#define PAUSE ACRX_T("\\")

/* The ADS_INITGET control bits
 */

enum {
    RSG_NONULL      = 0x0001,  // Disallow null input 
    RSG_NOZERO      = 0x0002,  // Disallow zero input 
    RSG_NONEG       = 0x0004,  // Disallow negative input
    RSG_NOLIM       = 0x0008,  // Do not check limits
    RSG_GETZ        = 0x0010,  // Get Z coordinate
    RSG_DASH        = 0x0020,  // Draw dashed rubber band/box
                             // (not a GEDIT control bit)
    RSG_2D          = 0x0040,  // Restrict (getdist) to 2D (causes the
                             // UD_GETZ control bit to be cleared)
    RSG_OTHER       = 0x0080,  // Return input string if unknown 
    RSG_DDISTFIRST  = 0x0100, // Give DD entry precedence over arbitrary input
    RSG_TRACKUCS    = 0x0200, // Allow UCS tracking for faces 
                             // (causes the UD_TRACKUCS control bit to be set)
    RSG_NOORTHOZ    = 0x0400, // Disables polar/ortho tracking in the Z direction 
                             // (causes the UD_NOORTHOZ control bit to be set)
    RSG_NOOSNAP     = 0x0800,  // Disables object snaps
    RSG_NODDIST     = 0x1000,  // No direct distance
};

/* The following control bits are the old names for the RSG_
   control bits above.  These names are provided for
   backward compatibility.  You should use the RSG_ names
   above.
 */

enum {
    INP_NNULL   = RSG_NONULL,
    INP_NZERO   = RSG_NOZERO,
    INP_NNEG    = RSG_NONEG,
    INP_NLIM    = RSG_NOLIM,
    INP_DASH    = RSG_DASH,
    INP_NZCOORD = RSG_2D
};

enum SelectorType {
    SELECT_TYPE_FREE = 0,
    SELECT_TYPE_PICK,
    SELECT_TYPE_WPOLY,
    SELECT_TYPE_CPOLY,
    SELECT_TYPE_FENCE,
    SELECT_TYPE_SUBENTITY,
    SELECT_TYPE_BAG,
    SELECT_TYPE_LAST,
    SELECT_TYPE_LEAF,
    SELECT_TYPE_GROUP,
    SELECT_TYPE_PASTE,
    SELECT_TYPE_HATCHASC,
    SELECT_TYPE_NRVP,
    SELECT_TYPE_OCCLASS
};

/* Binary data stream structure
 */

struct ads_binary {    // Binary data chunk structure
    short clen;        // length of chunk in bytes (change to int?)
    // Unicode: leaving as char * for now, so that clients doing pointer
    // arithmetic with it will continue to work.  But it really should be 
    // a void *.
    char *buf;         // binary data
};

/*  Union for storing different ADS data types.
 */
 
union ads_u_val {
    ads_real rreal;
    ads_real rpoint[3];
    short rint;
    ACHAR *rstring;
#if !defined(_WIN64) && !defined(_AC64)
    int32_t  rlname[2];
    int32_t  mnLongPtr;  // use this instead of rlong for pointers
#else
    int64_t     rlname[2];
    int64_t     mnLongPtr;  // use this instead of rlong for pointers
#endif

    int32_t     rlong;      // a 32-bit integer value
    int64_t     mnInt64;    // a 64-bit integer value
    struct ads_binary rbinary;
/* TEMPORARY probably, for internal use only at the moment */
    // Unicode: leave as unsigned char for now
    unsigned char ihandle[8];
}; 
 
/* The following is the structure definition of the general result buffer.
   This is used for both passing back results from functions, as well
   as exotic applications like entity lists, and command function lists.
   It is as close as we come to the AutoLISP node structure.
 */
struct resbuf {                                                  
        struct resbuf *rbnext; // Allows them to be "linked"
        short restype;
        union ads_u_val resval;
};

typedef struct resbuf *pResbuf;
typedef const struct resbuf *kpResbuf;  // for declarations

#pragma pack(pop)

#endif
