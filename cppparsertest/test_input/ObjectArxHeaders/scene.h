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
//      SCENE.H
//
//      This header module is used in the AutoCAD and the Render sides.

#ifndef AD_SCENE_H
#define AD_SCENE_H

#include "AdAChar.h"

#pragma pack (push, 8)


#define FACEVER  0                    /* The internal version in header rec */

// These are used in the "id" fields of the structures below.  We leave
// them as chars (not widechars) for now.
#define         HEADER          /*MSG0*/'H'
#define         ENTITY          /*MSG0*/'E'
#define         EVERTEX         /*MSG0*/'V'
#define         POLYGON         /*MSG0*/'P'
#define         CONTOUR         /*MSG0*/'X'
#define         SHADER          /*MSG0*/'D'
#define         CMESH           /*MSG0*/'H'
#define         BLOCK_B         /*MSG0*/'U'     /* pUsh block */
#define         BLOCK_E         /*MSG0*/'O'     /* pOp block */
#define         E_LAYER         /*MSG0*/'L'     /* Layer entity */


/* The status field */
/*#define         CURVE           0x1*/
#define         TOPBOT          0x2


/* Bits defined for the entity flags field */
#define ENT_HAS_CMESH  1               /* set if cmesh output for this mesh */
#define ENT_HAS_XFORM  2               /* set if transform follows entity */
#define ENT_HAS_XDATA  4               /* Set if entity has xdata */
#define ENT_HAS_NORMAL 8               /* Set if entity has normals */
#define ENT_HAS_SUBENT 16              /* Set if entity has subentity */
 

#define RENDER_CACHE      1
 
/* The SCENE control mesh record. */
struct scn_cmesh {
    char   id;
    short  flags;
    long   next;
    short  mshtype;
    short  color;
    short  nverts;
    short  m;
    short  n;
};


/* The SCENE file vertex record. Note that all of the face's
   vertices will be written sequentially */
struct scn_vrtc {
    char   id;
    double vert[3];                   /* vertex coordinates */
};


/* The scene file polygonal mesh record */
struct scn_pmsh {
    char   id;
    short  flags;                     /* Flag    TOP/BOTTOM */
#if !defined(_WIN64) && !defined (_AC64)
    long   adr1;                      /* entity address */
    long   adr2;                      /* validation code of address */
#else
    __int64  adr1;
    __int64  adr2;
#endif
    long   layerindex;                /* index into the layer table for this */
    short  color;                     /* Face's color index */
    long   truecolor;                 /* Face's true color */
    short  ncvrtx;                    /* Number of contour vertexes */
#if !defined(_WIN64) && !defined (_AC64)
    long   mapperId;                  /* Mapper id */
#else
    __int64  mapperId;
#endif
};


/* The scene file polygon contour vertex record */
struct scn_cvrt {
    char   id;
    long   index;                     /* Mesh vertex number */
};


/* Description of the temporary record used to keep the polygonal mesh
   vertexes. This record belongs to the temporary file (VERTEX.$AS) which
   is a binary tree of all of the vertexes of a given polygonal mesh */
struct scn_node {
    double vertex[3];                   /* The vertex */
    double normal[3];                   /* The normal */
    long left;                        /* Address of the left node */
    long right;                       /* Address of the right node */
};


/* New record types for the ent2face() facility. We use a slightly
   different approach than the filmroll file, and treat everything
   as a polymesh.  We also put out an Entity record for each
   entity as it is regen'd and this record contains slightly
   different information than the current scn_ent record.
*/

/* Size of color map in bytes.  This is a bit-coded color map used
   to tell the application which colors are used in the ent2face file */
#define CMAPSIZE 32

struct e2f_hdr {                   /* Header Record */
    char id;                          /* Record type */
    short flags;                      /* bit flags */
    short version;                    /* version ID */
    long nents;                       /* Number of entities that follow */
    long npoly;                       /* Total number of polygons */
    long nlayers;                     /* Total number of layers */
    unsigned long bgcolor;            /* AutoCAD's background color */
    short cmaplen;                    /* Length of color map */
    char *cmap;                       /* Bit-coded colour map */
};


 
struct e2f_layer {                 /* Layer Record */
    char id;                          /* Record type */
    short layernamelen;               /* Length of layer name */
    ACHAR *lname;                      /* Name of the layer */
};
 


struct e2f_ent {                   /* Entity Record */
    char id;                          /* Record type */
    short flags;                      /* bit flags */
    short type;                       /* E.tcode */
#if !defined(_WIN64) && !defined (_AC64)
    long  adr1;                       /* entity address */
    long  adr2;                       /* validation code of address */
#else
    __int64  adr1;
    __int64  adr2;
#endif
    long  npoly;                      /* Number of polygons */
    long  nverts;                     /* Number of vertices */
    short color;                      /* color of entity */
    long  truecolor;                  /* true color of entity */
    long  layerindex;                 /* index into the layer table for this */
                                      /* entities layer */
#if !defined(_WIN64) && !defined (_AC64)
    long  materialId;                 /* Material database id */
#else
    __int64 materialId;
#endif
};

 
struct e2f_xform {                 /* Transform Record */
    char id;                          /* Record type */
    short flags;                      /* bit flags */
    double xfmatrix[4][4];              /* 4 x 4 transform */
};



extern struct e2f_hdr   e2fheader;    /* ent2face() header record */
extern struct e2f_ent   e2fentity;    /* ent2face() entity record */
extern struct e2f_layer e2flayer;     /* ent2face() entity record */
extern struct e2f_xform e2fxform;     /* Transform Record */
extern struct scn_vrtc  vrtcr;        /* vertex record */
extern struct scn_cvrt  cvrtr;        /* Contour vertex record */
extern struct scn_pmsh  pmshr;        /* Polygonal mesh record */



#ifdef RENDERDATA

typedef double dwg3dp[3];

class AcReCallout {
    public :
      virtual void e2fHeaderData(struct e2f_hdr *hdr) { };
      virtual void e2fLayerData(struct e2f_layer *lyr) { };
      virtual void e2fBlockData(struct e2f_ent *ent,
                                struct e2f_xform *xform) { };
      virtual void e2fEntityData(struct e2f_ent *ent) { };
      virtual void e2fVertexData(dwg3dp *vertex_array) { };
      virtual void e2fNormalData(dwg3dp *normals_array) { };
      virtual void e2fMeshData(struct scn_pmsh *polymesh,
                               long **polyindex) { };
   
      int flag;

};


int acreRegisterCallout(AcReCallout * imp);

Acad::ErrorStatus acreEntityToFaces(ads_name ss, ACHAR** const name, int normal);

#endif /*RENDERDATA*/

#pragma pack (pop)
#endif /* AD_SCENE_H */
