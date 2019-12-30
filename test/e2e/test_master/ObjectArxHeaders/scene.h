//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2018 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
#ifndef AD_SCENE_H
#  define AD_SCENE_H
#  include "AdAChar.h"
#  pragma  pack (push, 8)
#  define FACEVER	0                    /* The internal version in header rec */
#  define HEADER	'H'
#  define ENTITY	'E'
#  define EVERTEX	'V'
#  define POLYGON	'P'
#  define CONTOUR	'X'
#  define SHADER	'D'
#  define CMESH	'H'
#  define BLOCK_B	'U'     /* pUsh block */
#  define BLOCK_E	'O'     /* pOp block */
#  define E_LAYER	'L'     /* Layer entity */
/*#define         CURVE           0x1*/
#  define TOPBOT	0x2
#  define ENT_HAS_CMESH	1               /* set if cmesh output for this mesh */
#  define ENT_HAS_XFORM	2               /* set if transform follows entity */
#  define ENT_HAS_XDATA	4               /* Set if entity has xdata */
#  define ENT_HAS_NORMAL	8               /* Set if entity has normals */
#  define ENT_HAS_SUBENT	16              /* Set if entity has subentity */
#  define RENDER_CACHE	1
struct scn_cmesh
{
  char id;
  short flags;
  long next;
  short mshtype;
  short color;
  short nverts;
  short m;
  short n;
};
struct scn_vrtc
{
  char id;
  double vert[3];
};
struct scn_pmsh
{
  char id;
  short flags;
#  if  !defined(_WIN64) && !defined (_AC64)
  long adr1;
  long adr2;
#  else 
  __int64 adr1;
  __int64 adr2;
#  endif
  long layerindex;
  short color;
  long truecolor;
  short ncvrtx;
#  if  !defined(_WIN64) && !defined (_AC64)
  long mapperId;
#  else 
  __int64 mapperId;
#  endif
};
struct scn_cvrt
{
  char id;
  long index;
};
struct scn_node
{
  double vertex[3];
  double normal[3];
  long left;
  long right;
};
#  define CMAPSIZE	32
struct e2f_hdr
{
  char id;
  short flags;
  short version;
  long nents;
  long npoly;
  long nlayers;
  unsigned long bgcolor;
  short cmaplen;
  char* cmap;
};
struct e2f_layer
{
  char id;
  short layernamelen;
  ACHAR* lname;
};
struct e2f_ent
{
  char id;
  short flags;
  short type;
#  if  !defined(_WIN64) && !defined (_AC64)
  long adr1;
  long adr2;
#  else 
  __int64 adr1;
  __int64 adr2;
#  endif
  long npoly;
  long nverts;
  short color;
  long truecolor;
  long layerindex;
#  if  !defined(_WIN64) && !defined (_AC64)
  long materialId;
#  else 
  __int64 materialId;
#  endif
};
struct e2f_xform
{
  char id;
  short flags;
  double xfmatrix[4][4];
};
extern struct e2f_hdr e2fheader;
extern struct e2f_ent e2fentity;
extern struct e2f_layer e2flayer;
extern struct e2f_xform e2fxform;
extern struct scn_vrtc vrtcr;
extern struct scn_cvrt cvrtr;
extern struct scn_pmsh pmshr;
#  ifdef RENDERDATA
typedef double dwg3dp[3];
class AcReCallout
{
public:
  virtual void e2fHeaderData(struct e2f_hdr* hdr)
  {
  }
  virtual void e2fLayerData(struct e2f_layer* lyr)
  {
  }
  virtual void e2fBlockData(struct e2f_ent* ent, struct e2f_xform* xform)
  {
  }
  virtual void e2fEntityData(struct e2f_ent* ent)
  {
  }
  virtual void e2fVertexData(dwg3dp* vertex_array)
  {
  }
  virtual void e2fNormalData(dwg3dp* normals_array)
  {
  }
  virtual void e2fMeshData(struct scn_pmsh* polymesh, long** polyindex)
  {
  }
  int flag;
};
int acreRegisterCallout(AcReCallout* imp);
Acad::ErrorStatus acreEntityToFaces(ads_name ss, ACHAR** const name, int normal);
#  endif
#  pragma  pack (pop)
#endif
