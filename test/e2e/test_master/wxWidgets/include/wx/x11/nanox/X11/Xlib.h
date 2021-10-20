/*
 * Xlib compatibility
 */
#ifndef _DUMMY_XLIBH_
#  define _DUMMY_XLIBH_
/* Move away the typedef in XtoNX.h */
#  define XFontStruct	XFontStruct1
#  include <XtoNX.h>
#  undef XFontStruct
#  undef XCharStruct
/* Data types */
typedef GR_PALETTE* Colormap;
typedef GR_DRAW_ID Drawable;
typedef int Status;
typedef unsigned long VisualID;
typedef int Bool;
typedef long XID;
typedef GR_SCANCODE KeySym;
typedef GR_EVENT_KEYSTROKE XKeyEvent;
typedef struct 
{
  GR_FONT_INFO info;
  GR_FONT_ID fid;
} XFontStruct;
typedef struct 
{
  short lbearing;
  short rbearing;
  short width;
  short ascent;
  short descent;
  unsigned short attributes;
} XCharStruct;
/* Configure window value mask bits */
#  define CWX(1<<0)
#  define CWY(1<<1)
#  define CWWidth(1<<2)
#  define CWHeight(1<<3)
#  define CWBorderWidth(1<<4)
#  define CWSibling(1<<5)
#  define CWStackMode(1<<6)
/* Values */
typedef struct 
{
  int x, y;
  int width, height;
  int border_width;
  Window sibling;
  int stack_mode;
} XWindowChanges;
/* typedef unsigned long Time; */
#  define Success	0
#  define GrabSuccess	Success
#  define GrabNotViewable(Success+1)
#  define InputOutput	1
#  define InputOnly	2
#  define IsUnmapped	0
#  define IsUnviewable	1
#  define IsViewable	2
/* Is this right? */
#  define PropertyChangeMask	GR_EVENT_MASK_SELECTION_CHANGED
#  define GraphicsExpose	GR_EVENT_TYPE_EXPOSURE
#  define GraphicsExposeMask	GR_EVENT_MASK_EXPOSURE
#  define ColormapChangeMask	0
#  define FillSolid	0
#  define LineSolid	0
#  define LineOnOffDash	0
#  define CapNotLast	0
#  define CapRound	0
#  define CapProjecting	0
#  define CapButt	0
#  define JoinRound	0
#  define JoinBevel	0
#  define JoinMiter	0
#  define IncludeInferiors	0
#  define ClipByChildren	0
#  define DoRed	0
#  define DoGreen	0
#  define DoBlue	0
#  define NoEventMask	GR_EVENT_MASK_NONE
#  define RevertToParent	0
#  define CurrentTime	0
#  define GrabModeAsync	0
#  define GXcopy	GR_MODE_COPY
#  define GXclear	GR_MODE_CLEAR
#  ifndef GXxor
#    define GXxor	GR_MODE_OR
#  endif
#  define GXinvert	GR_MODE_INVERT
#  define GXorReverse	GR_MODE_ORREVERSE
#  define GXandReverse	GR_MODE_ANDREVERSE
#  define GXand	GR_MODE_AND
#  define GXor	GR_MODE_OR
#  define GXandInverted	GR_MODE_ANDINVERTED
#  define GXnoop	GR_MODE_NOOP
#  define GXnor	GR_MODE_NOR
#  define GXequiv	GR_MODE_EQUIV
#  define GXcopyInverted	GR_MODE_COPYINVERTED
#  define GXorInverted	GR_MODE_ORINVERTED
#  define GXnand	GR_MODE_NAND
#  define GXset	GR_MODE_SET
#  define XSynchronize(display,sync)
#  define XDefaultRootWindow(d)	 GR_ROOT_WINDOW_ID
#  define RootWindowOfScreen(s)	 GR_ROOT_WINDOW_ID
#  define XFreePixmap(d, p)	 GrDestroyWindow(p)
#  define XFreeCursor(d, c)	 GrDestroyCursor(c)
#  define XFreeGC(d, gc)	 GrDestroyGC(gc)
#  define XSetBackground(d, gc, c)	 GrSetGCBackground(gc, c)
#  define DefaultVisual(d, s) (NULL)
#  define DefaultColormap(d, s)	 DefaultColormapOfScreen(NULL)
#  define DefaultScreenOfDisplay(d)	 0
#  define XSetFillStyle(d, gc, s)	 wxNoop()
#  define XSetLineAttributes(d, gc, a, b, c, e)	 wxNoop()
#  define XSetClipMask(d, gc, m)	 wxNoop()
#  define XSetTSOrigin(d, gc, x, y)	 wxNoop()
#  define XFillArc(d, w, gc, x, y, rx, ry, a1, a2)	 GrArcAngle(w, gc, x, y, rx, ry, a1, a2, GR_PIE)
#  define XDrawArc(d, w, gc, x, y, rx, ry, a1, a2)	 GrArcAngle(w, gc, x, y, rx, ry, a1, a2, GR_ARC)
#  define XDrawPoint(d, w, gc, x, y)	 GrPoint(w, gc, x, y)
#  define XFillPolygon(d, w, gc, p, n, s, m)	 GrFillPoly(w, gc, n, p)
#  define XDrawRectangle(d, w, gc, x, y, width, height)	 GrRect(w, gc, x, y, width, height)
#  define XSetClipOrigin(d, gc, x, y)	 GrSetGCClipOrigin(gc, x, y)
#  define XSetRegion(d, gc, r)	 GrSetGCRegion(gc, r)
#  define XSetTile(d, gc, p)	 wxNoop()
#  define XSetStipple(d, gc, p)	 wxNoop()
#  define XSetSubwindowMode(d, gc, mode)	 wxNoop()
#  define XFreeColormap(d, cmap)	 wxNoop()
#  define XSetTransientForHint(d, w, p)	 wxNoop()
#  define XUnionRegion(sr1,sr2,r)		GrUnionRegion(r,sr1,sr2)
#  define XIntersectRegion(sr1,sr2,r)		GrIntersectRegion(r,sr1,sr2)
#  define XEqualRegion(r1, r2)	 GrEqualRegion(r1, r2)
#  define XEmptyRegion(r)	 GrEmptyRegion(r)
#  define XOffsetRegion(r, x, y)	 GrOffsetRegion(r, x, y)
#  define XClipBox(r, rect)	 GrGetRegionBox(r, rect)
#  define XPointInRegion(r, x, y)	 GrPointInRegion(r, x, y)
#  define XXorRegion(sr1, sr2, r)	 GrXorRegion(r, sr1, sr2)
/* TODO: Cannot find equivalent for this. */
#  define XIconifyWindow(d, w, s)	 0
#  define XCreateWindowWithColor(d,p,x,y,w,h,bw,depth,cl,vis,backColor,foreColor)	 \
			GrNewWindow(p,x,y,w,h,bw,backColor,foreColor)
#  define XLookupString(event, buf, len, sym, status) (*sym = (event)->scancode)
#  define XBell(a, b)	 GrBell()
#  define DisplayWidthMM(d, s)	 100
#  define DisplayHeightMM(d, s)	 100
/* These defines are wrongly defined in XtoNX.h, IMHO,
 * since they reference a static global.
 * Redefined as functions, below.
 */
#  undef DisplayWidth
#  undef DisplayHeight
#  undef DefaultDepth
/*
 * Data structure used by color operations
 */
typedef struct 
{
  unsigned long pixel;
  unsigned short red, green, blue;
  char flags;
  char pad;
} XColor;
typedef struct 
{
  int type;
  Display* display;
  XID resourceid;
  unsigned long serial;
  unsigned char error_code;
  unsigned char request_code;
  unsigned char minor_code;
} XErrorEvent;
/*
 * Visual structure; contains information about colormapping possible.
 */
typedef struct 
{
  void* ext_data;
  VisualID visualid;
#  if  defined(__cplusplus) || defined(c_plusplus)
  int c_class;
#  else 
  int c_class;
#  endif
  unsigned long red_mask, green_mask, blue_mask;
  int bits_per_rgb;
  int map_entries;
} Visual;
/*
 * Depth structure; contains information for each possible depth.
 */
typedef struct 
{
  int depth;
  int nvisuals;
  Visual* visuals;
} Depth;
/*
 * Information about the screen.  The contents of this structure are
 * implementation dependent.  A Screen should be treated as opaque
 * by application code.
 */
struct _XDisplay;
typedef struct 
{
  void* ext_data;
  struct _XDisplay* display;
  Window root;
  int width, height;
  int mwidth, mheight;
  int ndepths;
  Depth* depths;
  int root_depth;
  Visual* root_visual;
  GC default_gc;
  Colormap cmap;
  unsigned long white_pixel;
  unsigned long black_pixel;
  int max_maps, min_maps;
  int backing_store;
  Bool save_unders;
  long root_input_mask;
} Screen;
typedef struct 
{
  int x, y;
  int width, height;
  int border_width;
  int depth;
  Visual* visual;
  Window root;
  int _class;
  int bit_gravity;
  int win_gravity;
  int backing_store;
  unsigned long backing_planes;
  unsigned long backing_pixel;
  Bool save_under;
  Colormap colormap;
  Bool map_installed;
  int map_state;
  long all_event_masks;
  long your_event_mask;
  long do_not_propagate_mask;
  Bool override_redirect;
  Screen* screen;
} XWindowAttributes;
typedef int (*XErrorHandler) (Display*, XErrorEvent*);
/* events*/

/* What should this be? */
#  ifndef MotionNotify
#    define MotionNotify	GR_EVENT_TYPE_MOUSE_POSITION
#    define PointerMotionMask	GR_EVENT_MASK_MOUSE_POSITION
#  endif
#  define ButtonMotionMask	GR_EVENT_MASK_MOUSE_POSITION
#  define KeymapStateMask	0
#  define StructureNotifyMask	GR_EVENT_MASK_UPDATE
#  ifdef ConfigureNotify
/* XtoNX.h gets it wrong */
#    undef ConfigureNotify
#  endif
#  define ConfigureNotify	GR_EVENT_TYPE_UPDATE
#  ifndef FocusIn
#    define FocusIn	GR_EVENT_TYPE_FOCUS_IN
#    define FocusOut	GR_EVENT_TYPE_FOCUS_OUT
#    define FocusChangeMask	GR_EVENT_MASK_FOCUS_IN|GR_EVENT_MASK_FOCUS_OUT
#  endif
/* Fuunctions */
#  ifdef __cplusplus
extern "C" {
#  endif
  Display* XOpenDisplay(char* name);
  Colormap DefaultColormapOfScreen(Screen*);
  int XSetGraphicsExposures(Display*, GC, Bool);
  int XWarpPointer(Display*, Window, Window, int, int, unsigned int, unsigned int, int destX, int destY);
  int XSetInputFocus(Display*, Window focus, int, Time);
  int XGetInputFocus(Display*, Window*, int*);
  int XGrabPointer(Display*, Window, Bool, unsigned int, int, int, Window, Cursor, Time);
  int XUngrabPointer(Display*, Time);
  int XCopyArea(Display*, Drawable src, Drawable dest, GC gc, int src_x, int src_y, unsigned int width, unsigned int height, int dest_x, int dest_y);
  int XCopyPlane(Display*, Drawable src, Drawable dest, GC gc, int src_x, int src_y, unsigned int width, unsigned int height, int dest_x, int dest_y, unsigned long);
  XErrorHandler XSetErrorHandler(XErrorHandler);
  Screen* XScreenOfDisplay(Display*, int);
  int DisplayWidth(Display*, int);
  int DisplayHeight(Display*, int);
  int DefaultDepth(Display*, int);
  int XAllocColor(Display*, Colormap, XColor* color);
  int XParseColor(Display* display, Colormap cmap, const char* cname, XColor* color);
  int XDrawLine(Display* display, Window win, GC gc, int x1, int y1, int x2, int y2);
  int XTextExtents(XFontStruct* font, char* s, int len, int* direction, int* ascent, int* descent2, XCharStruct* overall);
  int XPending(Display* d);
  XFontStruct* XLoadQueryFont(Display* display, const char* fontSpec);
  int XFreeFont(Display* display, XFontStruct* fontStruct);
  int XQueryColor(Display* display, Colormap cmap, XColor* color);
  Status XGetWindowAttributes(Display* display, Window w, XWindowAttributes* window_attributes);
  int XConfigureWindow(Display* display, Window w, int mask, XWindowChanges* changes);
  int XTranslateCoordinates(Display* display, Window srcWindow, Window destWindow, int srcX, int srcY, int* destX, int* destY, Window* childReturn);
  void wxNoop();
#  ifdef __cplusplus
  }
#  endif
#  define XMaxRequestSize(display)	 16384
#endif
  /* _DUMMY_XLIBH_ */
