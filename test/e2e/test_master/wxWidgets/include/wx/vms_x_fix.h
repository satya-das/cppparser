/***************************************************************************
 *                                                                         *
 * Author : Jouk Jansen (joukj@hrem.stm.tudelft.nl)                        *
 *                                                                         *
 * Last revision : 7 October 2005                                          *
 *                                                                         *
 * Repair definitions of Runtime library functions when compiling with     *
 * /name=(as_is) on OpenVMS                                                *
 *                                                                         *
 ***************************************************************************/
#ifndef VMS_X_FIX
#  define VMS_X_FIX
#  define decw	$_select DECW$_SELECT
#  define DtSaverGetWindows	DTSAVERGETWINDOWS
#  define MrmFetchWidget	MRMFETCHWIDGET
#  define MrmInitialize	MRMINITIALIZE
#  define MrmOpenHierarchy	MRMOPENHIERARCHY
#  define MrmRegisterNames	MRMREGISTERNAMES
#  define XAddExtension	XADDEXTENSION
#  define XAddHosts	XADDHOSTS
#  define XAllocClassHint	XALLOCCLASSHINT
#  define XAllocColor	XALLOCCOLOR
#  define XAllocColorCells	XALLOCCOLORCELLS
#  define XAllocIconSize	XALLOCICONSIZE
#  define XAllocNamedColor	XALLOCNAMEDCOLOR
#  define XAllocSizeHints	XALLOCSIZEHINTS
#  define XAllocStandardColormap	XALLOCSTANDARDCOLORMAP
#  define XAllocWMHints	XALLOCWMHINTS
#  define XAllowEvents	XALLOWEVENTS
#  define XAutoRepeatOff	XAUTOREPEATOFF
#  define XAutoRepeatOn	XAUTOREPEATON
#  define XBaseFontNameListOfFontSet	XBASEFONTNAMELISTOFFONTSET
#  define XBell	XBELL
#  define XBitmapPad	XBITMAPPAD
#  define XBlackPixel	XBLACKPIXEL
#  define XBlackPixelOfScreen	XBLACKPIXELOFSCREEN
#  define XCellsOfScreen	XCELLSOFSCREEN
#  define XChangeActivePointerGrab	XCHANGEACTIVEPOINTERGRAB
#  define XChangeGC	XCHANGEGC
#  define XChangeKeyboardControl	XCHANGEKEYBOARDCONTROL
#  define XChangePointerControl	XCHANGEPOINTERCONTROL
#  define XChangeProperty	XCHANGEPROPERTY
#  define XChangeWindowAttributes	XCHANGEWINDOWATTRIBUTES
#  define XCheckIfEvent	XCHECKIFEVENT
#  define XCheckMaskEvent	XCHECKMASKEVENT
#  define XCheckTypedEvent	XCHECKTYPEDEVENT
#  define XCheckTypedWindowEvent	XCHECKTYPEDWINDOWEVENT
#  define XCheckWindowEvent	XCHECKWINDOWEVENT
#  define XClearArea	XCLEARAREA
#  define XClearWindow	XCLEARWINDOW
#  define XClipBox	XCLIPBOX
#  define XCloseDisplay	XCLOSEDISPLAY
#  define XCloseIM	XCLOSEIM
#  define XConfigureWindow	XCONFIGUREWINDOW
#  define XConvertSelection	XCONVERTSELECTION
#  define XCopyArea	XCOPYAREA
#  define XCopyColormapAndFree	XCOPYCOLORMAPANDFREE
#  define XCopyGC	XCOPYGC
#  define XCopyPlane	XCOPYPLANE
#  define XCreateBitmapFromData	XCREATEBITMAPFROMDATA
#  define XCreateColormap	XCREATECOLORMAP
#  define XCreateFontCursor	XCREATEFONTCURSOR
#  define XCreateFontSet	XCREATEFONTSET
#  define XCreateGC	XCREATEGC
#  define XCreateGlyphCursor	XCREATEGLYPHCURSOR
#  define XCreateIC	XCREATEIC
#  define XCreateImage	XCREATEIMAGE
#  define XCreatePixmap	XCREATEPIXMAP
#  define XCreatePixmapCursor	XCREATEPIXMAPCURSOR
#  define XCreatePixmapFromBitmapData	XCREATEPIXMAPFROMBITMAPDATA
#  define XCreateRegion	XCREATEREGION
#  define XCreateSimpleWindow	XCREATESIMPLEWINDOW
#  define XCreateWindow	XCREATEWINDOW
#  define XDefaultColormap	XDEFAULTCOLORMAP
#  define XDefaultColormapOfScreen	XDEFAULTCOLORMAPOFSCREEN
#  define XDefaultDepth	XDEFAULTDEPTH
#  define XDefaultDepthOfScreen	XDEFAULTDEPTHOFSCREEN
#  define XDefaultGC	XDEFAULTGC
#  define XDefaultRootWindow	XDEFAULTROOTWINDOW
#  define XDefaultScreen	XDEFAULTSCREEN
#  define XDefaultScreenOfDisplay	XDEFAULTSCREENOFDISPLAY
#  define XDefaultVisual	XDEFAULTVISUAL
#  define XDefaultVisualOfScreen	XDEFAULTVISUALOFSCREEN
#  define XDefineCursor	XDEFINECURSOR
#  define XDeleteContext	XDELETECONTEXT
#  define XDeleteProperty	XDELETEPROPERTY
#  define XDestroyIC	XDESTROYIC
#  define XDestroyRegion	XDESTROYREGION
#  define XDestroySubwindows	XDESTROYSUBWINDOWS
#  define XDestroyWindow	XDESTROYWINDOW
#  define XDisableAccessControl	XDISABLEACCESSCONTROL
#  define XDisplayCells	XDISPLAYCELLS
#  define XDisplayHeight	XDISPLAYHEIGHT
#  define XDisplayKeycodes	XDISPLAYKEYCODES
#  define XDisplayName	XDISPLAYNAME
#  define XDisplayOfIM	XDISPLAYOFIM
#  define XDisplayOfScreen	XDISPLAYOFSCREEN
#  define XDisplayString	XDISPLAYSTRING
#  define XDisplayWidth	XDISPLAYWIDTH
#  define XDoesBackingStore	XDOESBACKINGSTORE
#  define XDrawArc	XDRAWARC
#  define XDrawArcs	XDRAWARCS
#  define XDrawImageString	XDRAWIMAGESTRING
#  define XDrawImageString16	XDRAWIMAGESTRING16
#  define XDrawLine	XDRAWLINE
#  define XDrawLines	XDRAWLINES
#  define XDrawPoint	XDRAWPOINT
#  define XDrawPoints	XDRAWPOINTS
#  define XDrawRectangle	XDRAWRECTANGLE
#  define XDrawRectangles	XDRAWRECTANGLES
#  define XDrawSegments	XDRAWSEGMENTS
#  define XDrawString	XDRAWSTRING
#  define XDrawString16	XDRAWSTRING16
#  define XDrawText	XDRAWTEXT
#  define XDrawText16	XDRAWTEXT16
#  define XESetCloseDisplay	XESETCLOSEDISPLAY
#  define XEmptyRegion	XEMPTYREGION
#  define XEnableAccessControl	XENABLEACCESSCONTROL
#  define XEqualRegion	XEQUALREGION
#  define XEventsQueued	XEVENTSQUEUED
#  define XExtendedMaxRequestSize	XEXTENDEDMAXREQUESTSIZE
#  define XExtentsOfFontSet	XEXTENTSOFFONTSET
#  define XFetchBuffer	XFETCHBUFFER
#  define XFetchBytes	XFETCHBYTES
#  define XFetchName	XFETCHNAME
#  define XFillArc	XFILLARC
#  define XFillArcs	XFILLARCS
#  define XFillPolygon	XFILLPOLYGON
#  define XFillRectangle	XFILLRECTANGLE
#  define XFillRectangles	XFILLRECTANGLES
#  define XFilterEvent	XFILTEREVENT
#  define XFindContext	XFINDCONTEXT
#  define XFlush	XFLUSH
#  define XFontsOfFontSet	XFONTSOFFONTSET
#  define XForceScreenSaver	XFORCESCREENSAVER
#  define XFree	XFREE
#  define XFreeColormap	XFREECOLORMAP
#  define XFreeColors	XFREECOLORS
#  define XFreeCursor	XFREECURSOR
#  define XFreeDeviceList	XFREEDEVICELIST
#  define XFreeDeviceState	XFREEDEVICESTATE
#  define XFreeFont	XFREEFONT
#  define XFreeFontInfo	XFREEFONTINFO
#  define XFreeFontNames	XFREEFONTNAMES
#  define XFreeFontSet	XFREEFONTSET
#  define XFreeGC	XFREEGC
#  define XFreeModifiermap	XFREEMODIFIERMAP
#  define XFreePixmap	XFREEPIXMAP
#  define XFreeStringList	XFREESTRINGLIST
#  define XGContextFromGC	XGCONTEXTFROMGC
#  define XGeometry	XGEOMETRY
#  define XGetAtomName	XGETATOMNAME
#  define XGetCommand	XGETCOMMAND
#  define XGetDefault	XGETDEFAULT
#  define XGetErrorDatabaseText	XGETERRORDATABASETEXT
#  define XGetErrorText	XGETERRORTEXT
#  define XGetExtensionVersion	XGETEXTENSIONVERSION
#  define XGetFontProperty	XGETFONTPROPERTY
#  define XGetGCValues	XGETGCVALUES
#  define XGetGeometry	XGETGEOMETRY
#  define XGetICValues	XGETICVALUES
#  define XGetIMValues	XGETIMVALUES
#  define XGetIconName	XGETICONNAME
#  define XGetIconSizes	XGETICONSIZES
#  define XGetImage	XGETIMAGE
#  define XGetInputFocus	XGETINPUTFOCUS
#  define XGetKeyboardControl	XGETKEYBOARDCONTROL
#  define XGetKeyboardMapping	XGETKEYBOARDMAPPING
#  define XGetModifierMapping	XGETMODIFIERMAPPING
#  define XGetMotionEvents	XGETMOTIONEVENTS
#  define XGetNormalHints	XGETNORMALHINTS
#  define XGetPointerMapping	XGETPOINTERMAPPING
#  define XGetRGBColormaps	XGETRGBCOLORMAPS
#  define XGetScreenSaver	XGETSCREENSAVER
#  define XGetSelectionOwner	XGETSELECTIONOWNER
#  define XGetStandardColormap	XGETSTANDARDCOLORMAP
#  define XGetSubImage	XGETSUBIMAGE
#  define XGetTextProperty	XGETTEXTPROPERTY
#  define XGetVisualInfo	XGETVISUALINFO
#  define XGetWMColormapWindows	XGETWMCOLORMAPWINDOWS
#  define XGetWMHints	XGETWMHINTS
#  define XGetWMIconName	XGETWMICONNAME
#  define XGetWMName	XGETWMNAME
#  define XGetWMNormalHints	XGETWMNORMALHINTS
#  define XGetWindowAttributes	XGETWINDOWATTRIBUTES
#  define XGetWindowProperty	XGETWINDOWPROPERTY
#  define XGrabButton	XGRABBUTTON
#  define XGrabKeyboard	XGRABKEYBOARD
#  define XGrabPointer	XGRABPOINTER
#  define XGrabServer	XGRABSERVER
#  define XHeightMMOfScreen	XHEIGHTMMOFSCREEN
#  define XHeightOfScreen	XHEIGHTOFSCREEN
#  define XIconifyWindow	XICONIFYWINDOW
#  define XIfEvent	XIFEVENT
#  define XInitExtension	XINITEXTENSION
#  define XInitImage	XINITIMAGE
#  define XInstallColormap	XINSTALLCOLORMAP
#  define XInternAtom	XINTERNATOM
#  define XInternAtoms	XINTERNATOMS
#  define XIntersectRegion	XINTERSECTREGION
#  define XKeycodeToKeysym	XKEYCODETOKEYSYM
#  define XKeysymToKeycode	XKEYSYMTOKEYCODE
#  define XKeysymToString	XKEYSYMTOSTRING
#  define XKillClient	XKILLCLIENT
#  define XListDepths	XLISTDEPTHS
#  define XListFonts	XLISTFONTS
#  define XListFontsWithInfo	XLISTFONTSWITHINFO
#  define XListHosts	XLISTHOSTS
#  define XListInputDevices	XLISTINPUTDEVICES
#  define XListInstalledColormaps	XLISTINSTALLEDCOLORMAPS
#  define XListPixmapFormats	XLISTPIXMAPFORMATS
#  define XListProperties	XLISTPROPERTIES
#  define XLoadFont	XLOADFONT
#  define XLoadQueryFont	XLOADQUERYFONT
#  define XLookupColor	XLOOKUPCOLOR
#  define XLookupKeysym	XLOOKUPKEYSYM
#  define XLookupString	XLOOKUPSTRING
#  define XLowerWindow	XLOWERWINDOW
#  define XMapRaised	XMAPRAISED
#  define XMapSubwindows	XMAPSUBWINDOWS
#  define XMapWindow	XMAPWINDOW
#  define XMatchVisualInfo	XMATCHVISUALINFO
#  define XMaxRequestSize	XMAXREQUESTSIZE
#  define XMissingExtension	XMISSINGEXTENSION
#  define XMoveResizeWindow	XMOVERESIZEWINDOW
#  define XMoveWindow	XMOVEWINDOW
#  define XNextEvent	XNEXTEVENT
#  define XNextRequest	XNEXTREQUEST
#  define XNoOp	XNOOP
#  define XOffsetRegion	XOFFSETREGION
#  define XOpenDevice	XOPENDEVICE
#  define XOpenDisplay	XOPENDISPLAY
#  define XOpenIM	XOPENIM
#  define XParseColor	XPARSECOLOR
#  define XParseGeometry	XPARSEGEOMETRY
#  define XPeekEvent	XPEEKEVENT
#  define XPeekIfEvent	XPEEKIFEVENT
#  define XPending	XPENDING
#  define XPointInRegion	XPOINTINREGION
#  define XPolygonRegion	XPOLYGONREGION
#  define XPutBackEvent	XPUTBACKEVENT
#  define XPutImage	XPUTIMAGE
#  define XQLength	XQLENGTH
#  define XQueryBestCursor	XQUERYBESTCURSOR
#  define XQueryBestStipple	XQUERYBESTSTIPPLE
#  define XQueryColor	XQUERYCOLOR
#  define XQueryColors	XQUERYCOLORS
#  define XQueryDeviceState	XQUERYDEVICESTATE
#  define XQueryExtension	XQUERYEXTENSION
#  define XQueryFont	XQUERYFONT
#  define XQueryKeymap	XQUERYKEYMAP
#  define XQueryPointer	XQUERYPOINTER
#  define XQueryTree	XQUERYTREE
#  define XRaiseWindow	XRAISEWINDOW
#  define XReadBitmapFile	XREADBITMAPFILE
#  define XRecolorCursor	XRECOLORCURSOR
#  define XReconfigureWMWindow	XRECONFIGUREWMWINDOW
#  define XRectInRegion	XRECTINREGION
#  define XRefreshKeyboardMapping	XREFRESHKEYBOARDMAPPING
#  define XRemoveHosts	XREMOVEHOSTS
#  define XReparentWindow	XREPARENTWINDOW
#  define XResetScreenSaver	XRESETSCREENSAVER
#  define XResizeWindow	XRESIZEWINDOW
#  define XResourceManagerString	XRESOURCEMANAGERSTRING
#  define XRestackWindows	XRESTACKWINDOWS
#  define XRotateBuffers	XROTATEBUFFERS
#  define XRootWindow	XROOTWINDOW
#  define XRootWindowOfScreen	XROOTWINDOWOFSCREEN
#  define XSaveContext	XSAVECONTEXT
#  define XScreenNumberOfScreen	XSCREENNUMBEROFSCREEN
#  define XScreenOfDisplay	XSCREENOFDISPLAY
#  define XSelectAsyncEvent	XSELECTASYNCEVENT
#  define XSelectAsyncInput	XSELECTASYNCINPUT
#  define XSelectExtensionEvent	XSELECTEXTENSIONEVENT
#  define XSelectInput	XSELECTINPUT
#  define XSendEvent	XSENDEVENT
#  define XServerVendor	XSERVERVENDOR
#  define XSetArcMode	XSETARCMODE
#  define XSetBackground	XSETBACKGROUND
#  define XSetClassHint	XSETCLASSHINT
#  define XSetClipMask	XSETCLIPMASK
#  define XSetClipOrigin	XSETCLIPORIGIN
#  define XSetClipRectangles	XSETCLIPRECTANGLES
#  define XSetCloseDownMode	XSETCLOSEDOWNMODE
#  define XSetCommand	XSETCOMMAND
#  define XSetDashes	XSETDASHES
#  define XSetErrorHandler	XSETERRORHANDLER
#  define XSetFillRule	XSETFILLRULE
#  define XSetFillStyle	XSETFILLSTYLE
#  define XSetFont	XSETFONT
#  define XSetForeground	XSETFOREGROUND
#  define XSetFunction	XSETFUNCTION
#  define XSetGraphicsExposures	XSETGRAPHICSEXPOSURES
#  define XSetICFocus	XSETICFOCUS
#  define XSetICValues	XSETICVALUES
#  define XSetIOErrorHandler	XSETIOERRORHANDLER
#  define XSetIconName	XSETICONNAME
#  define XSetInputFocus	XSETINPUTFOCUS
#  define XSetLineAttributes	XSETLINEATTRIBUTES
#  define XSetLocaleModifiers	XSETLOCALEMODIFIERS
#  define XSetNormalHints	XSETNORMALHINTS
#  define XSetPlaneMask	XSETPLANEMASK
#  define XSetRegion	XSETREGION
#  define XSetRGBColormaps	XSETRGBCOLORMAPS
#  define XSetScreenSaver	XSETSCREENSAVER
#  define XSetSelectionOwner	XSETSELECTIONOWNER
#  define XSetStandardProperties	XSETSTANDARDPROPERTIES
#  define XSetState	XSETSTATE
#  define XSetStipple	XSETSTIPPLE
#  define XSetSubwindowMode	XSETSUBWINDOWMODE
#  define XSetTSOrigin	XSETTSORIGIN
#  define XSetTextProperty	XSETTEXTPROPERTY
#  define XSetTile	XSETTILE
#  define XSetTransientForHint	XSETTRANSIENTFORHINT
#  define XSetWMClientMachine	XSETWMCLIENTMACHINE
#  define XSetWMColormapWindows	XSETWMCOLORMAPWINDOWS
#  define XSetWMHints	XSETWMHINTS
#  define XSetWMIconName	XSETWMICONNAME
#  define XSetWMName	XSETWMNAME
#  define XSetWMNormalHints	XSETWMNORMALHINTS
#  define XSetWMProperties	XSETWMPROPERTIES
#  define XSetWMProtocols	XSETWMPROTOCOLS
#  define XSetWMSizeHints	XSETWMSIZEHINTS
#  define XSetWindowBackground	XSETWINDOWBACKGROUND
#  define XSetWindowBackgroundPixmap	XSETWINDOWBACKGROUNDPIXMAP
#  define XSetWindowBorder	XSETWINDOWBORDER
#  define XSetWindowBorderPixmap	XSETWINDOWBORDERPIXMAP
#  define XSetWindowBorderWidth	XSETWINDOWBORDERWIDTH
#  define XSetWindowColormap	XSETWINDOWCOLORMAP
#  define XShapeCombineMask	XSHAPECOMBINEMASK
#  define XShapeCombineRectangles	XSHAPECOMBINERECTANGLES
#  define XShapeGetRectangles	XSHAPEGETRECTANGLES
#  define XShapeQueryExtension	XSHAPEQUERYEXTENSION
#  define XShmAttach	XSHMATTACH
#  define XShmCreateImage	XSHMCREATEIMAGE
#  define XShmCreatePixmap	XSHMCREATEPIXMAP
#  define XShmDetach	XSHMDETACH
#  define XShmGetEventBase	XSHMGETEVENTBASE
#  define XShmPutImage	XSHMPUTIMAGE
#  define XShmQueryExtension	XSHMQUERYEXTENSION
#  define XShmQueryVersion	XSHMQUERYVERSION
#  define XShrinkRegion	XSHRINKREGION
#  define XStoreBuffer	XSTOREBUFFER
#  define XStoreBytes	XSTOREBYTES
#  define XStoreColor	XSTORECOLOR
#  define XStoreColors	XSTORECOLORS
#  define XStoreName	XSTORENAME
#  define XStringListToTextProperty	XSTRINGLISTTOTEXTPROPERTY
#  define XStringToKeysym	XSTRINGTOKEYSYM
#  define XSubtractRegion	XSUBTRACTREGION
#  define XSupportsLocale	XSUPPORTSLOCALE
#  define XSync	XSYNC
#  define XSynchronize	XSYNCHRONIZE
#  define XTextExtents	XTEXTEXTENTS
#  define XTextExtents16	XTEXTEXTENTS16
#  define XTextPropertyToStringList	XTEXTPROPERTYTOSTRINGLIST
#  define XTextWidth	XTEXTWIDTH
#  define XTextWidth16	XTEXTWIDTH16
#  define XTranslateCoordinates	XTRANSLATECOORDINATES
#  define XUndefineCursor	XUNDEFINECURSOR
#  define XUngrabButton	XUNGRABBUTTON
#  define XUngrabKeyboard	XUNGRABKEYBOARD
#  define XUngrabPointer	XUNGRABPOINTER
#  define XUngrabServer	XUNGRABSERVER
#  define XUninstallColormap	XUNINSTALLCOLORMAP
#  define XUnionRectWithRegion	XUNIONRECTWITHREGION
#  define XUnionRegion	XUNIONREGION
#  define XUniqueContext	XUNIQUECONTEXT
#  define XUnmapWindow	XUNMAPWINDOW
#  define XUnsetICFocus	XUNSETICFOCUS
#  define XVaCreateNestedList	XVACREATENESTEDLIST
#  define XVisualIDFromVisual	XVISUALIDFROMVISUAL
#  define XWMGeometry	XWMGEOMETRY
#  define XWarpPointer	XWARPPOINTER
#  define XWhitePixel	XWHITEPIXEL
#  define XWhitePixelOfScreen	XWHITEPIXELOFSCREEN
#  define XWidthMMOfScreen	XWIDTHMMOFSCREEN
#  define XWidthOfScreen	XWIDTHOFSCREEN
#  define XWindowEvent	XWINDOWEVENT
#  define XWithdrawWindow	XWITHDRAWWINDOW
#  define XXorRegion	XXORREGION
#  define XcmsQueryColor	XCMSQUERYCOLOR
#  define XdbeAllocateBackBufferName	XDBEALLOCATEBACKBUFFERNAME
#  define XdbeFreeVisualInfo	XDBEFREEVISUALINFO
#  define XdbeGetVisualInfo	XDBEGETVISUALINFO
#  define XdbeQueryExtension	XDBEQUERYEXTENSION
#  define XdbeSwapBuffers	XDBESWAPBUFFERS
#  define XextAddDisplay	XEXTADDDISPLAY
#  define XextFindDisplay	XEXTFINDDISPLAY
#  define XextRemoveDisplay	XEXTREMOVEDISPLAY
#  define XkbSetDetectableAutoRepeat	XKBSETDETECTABLEAUTOREPEAT
#  define XmActivateProtocol	XMACTIVATEPROTOCOL
#  define XmAddProtocolCallback	XMADDPROTOCOLCALLBACK
#  define XmAddProtocols	XMADDPROTOCOLS
#  define XmChangeColor	XMCHANGECOLOR
#  define XmClipboardCopy	XMCLIPBOARDCOPY
#  define XmClipboardCopyByName	XMCLIPBOARDCOPYBYNAME
#  define XmClipboardEndCopy	XMCLIPBOARDENDCOPY
#  define XmClipboardEndRetrieve	XMCLIPBOARDENDRETRIEVE
#  define XmClipboardInquireCount	XMCLIPBOARDINQUIRECOUNT
#  define XmClipboardInquireFormat	XMCLIPBOARDINQUIREFORMAT
#  define XmClipboardInquireLength	XMCLIPBOARDINQUIRELENGTH
#  define XmClipboardLock	XMCLIPBOARDLOCK
#  define XmClipboardRetrieve	XMCLIPBOARDRETRIEVE
#  define XmClipboardStartCopy	XMCLIPBOARDSTARTCOPY
#  define XmClipboardStartRetrieve	XMCLIPBOARDSTARTRETRIEVE
#  define XmClipboardUnlock	XMCLIPBOARDUNLOCK
#  define XmCommandError	XMCOMMANDERROR
#  define XmCommandGetChild	XMCOMMANDGETCHILD
#  define XmCommandSetValue	XMCOMMANDSETVALUE
#  define XmCreateArrowButton	XMCREATEARROWBUTTON
#  define XmCreateArrowButtonGadget	XMCREATEARROWBUTTONGADGET
#  define XmCreateBulletinBoardDialog	XMCREATEBULLETINBOARDDIALOG
#  define XmCreateCascadeButton	XMCREATECASCADEBUTTON
#  define XmCreateCascadeButtonGadget	XMCREATECASCADEBUTTONGADGET
#  define XmCreateDialogShell	XMCREATEDIALOGSHELL
#  define XmCreateDragIcon	XMCREATEDRAGICON
#  define XmCreateDrawingArea	XMCREATEDRAWINGAREA
#  define XmCreateDrawnButton	XMCREATEDRAWNBUTTON
#  define XmCreateErrorDialog	XMCREATEERRORDIALOG
#  define XmCreateFileSelectionBox	XMCREATEFILESELECTIONBOX
#  define XmCreateFileSelectionDialog	XMCREATEFILESELECTIONDIALOG
#  define XmCreateForm	XMCREATEFORM
#  define XmCreateFormDialog	XMCREATEFORMDIALOG
#  define XmCreateFrame	XMCREATEFRAME
#  define XmCreateInformationDialog	XMCREATEINFORMATIONDIALOG
#  define XmCreateLabel	XMCREATELABEL
#  define XmCreateLabelGadget	XMCREATELABELGADGET
#  define XmCreateList	XMCREATELIST
#  define XmCreateMainWindow	XMCREATEMAINWINDOW
#  define XmCreateMenuBar	XMCREATEMENUBAR
#  define XmCreateMessageBox	XMCREATEMESSAGEBOX
#  define XmCreateMessageDialog	XMCREATEMESSAGEDIALOG
#  define XmCreateOptionMenu	XMCREATEOPTIONMENU
#  define XmCreatePanedWindow	XMCREATEPANEDWINDOW
#  define XmCreatePopupMenu	XMCREATEPOPUPMENU
#  define XmCreatePromptDialog	XMCREATEPROMPTDIALOG
#  define XmCreatePulldownMenu	XMCREATEPULLDOWNMENU
#  define XmCreatePushButton	XMCREATEPUSHBUTTON
#  define XmCreatePushButtonGadget	XMCREATEPUSHBUTTONGADGET
#  define XmCreateQuestionDialog	XMCREATEQUESTIONDIALOG
#  define XmCreateRadioBox	XMCREATERADIOBOX
#  define XmCreateRowColumn	XMCREATEROWCOLUMN
#  define XmCreateScale	XMCREATESCALE
#  define XmCreateScrollBar	XMCREATESCROLLBAR
#  define XmCreateScrolledList	XMCREATESCROLLEDLIST
#  define XmCreateScrolledText	XMCREATESCROLLEDTEXT
#  define XmCreateScrolledWindow	XMCREATESCROLLEDWINDOW
#  define XmCreateSelectionDialog	XMCREATESELECTIONDIALOG
#  define XmCreateSeparator	XMCREATESEPARATOR
#  define XmCreateSeparatorGadget	XMCREATESEPARATORGADGET
#  define XmCreateTemplateDialog	XMCREATETEMPLATEDIALOG
#  define XmCreateText	XMCREATETEXT
#  define XmCreateTextField	XMCREATETEXTFIELD
#  define XmCreateToggleButton	XMCREATETOGGLEBUTTON
#  define XmCreateToggleButtonGadget	XMCREATETOGGLEBUTTONGADGET
#  define XmCreateWarningDialog	XMCREATEWARNINGDIALOG
#  define XmCvtCTToXmString	XMCVTCTTOXMSTRING
#  define XmDestroyPixmap	XMDESTROYPIXMAP
#  define XmDragStart	XMDRAGSTART
#  define XmDropSiteRegister	XMDROPSITEREGISTER
#  define XmDropSiteUnregister	XMDROPSITEUNREGISTER
#  define XmDropSiteUpdate	XMDROPSITEUPDATE
#  define XmDropTransferStart	XMDROPTRANSFERSTART
#  define XmFileSelectionBoxGetChild	XMFILESELECTIONBOXGETCHILD
#  define XmFileSelectionDoSearch	XMFILESELECTIONDOSEARCH
#  define XmFontListAppendEntry	XMFONTLISTAPPENDENTRY
#  define XmFontListCopy	XMFONTLISTCOPY
#  define XmFontListCreate	XMFONTLISTCREATE
#  define XmFontListEntryCreate	XMFONTLISTENTRYCREATE
#  define XmFontListEntryFree	XMFONTLISTENTRYFREE
#  define XmFontListEntryGetFont	XMFONTLISTENTRYGETFONT
#  define XmFontListEntryGetTag	XMFONTLISTENTRYGETTAG
#  define XmFontListEntryLoad	XMFONTLISTENTRYLOAD
#  define XmFontListFree	XMFONTLISTFREE
#  define XmFontListFreeFontContext	XMFONTLISTFREEFONTCONTEXT
#  define XmFontListGetNextFont	XMFONTLISTGETNEXTFONT
#  define XmFontListInitFontContext	XMFONTLISTINITFONTCONTEXT
#  define XmFontListNextEntry	XMFONTLISTNEXTENTRY
#  define XmGetColors	XMGETCOLORS
#  define XmGetColorCalculation	XMGETCOLORCALCULATION
#  define XmGetFocusWidget	XMGETFOCUSWIDGET
#  define XmGetMenuCursor	XMGETMENUCURSOR
#  define XmGetPixmap	XMGETPIXMAP
#  define XmGetPixmapByDepth	XMGETPIXMAPBYDEPTH
#  define XmGetTearOffControl	XMGETTEAROFFCONTROL
#  define XmGetXmDisplay	XMGETXMDISPLAY
#  define XmImMbLookupString	XMIMMBLOOKUPSTRING
#  define XmImRegister	XMIMREGISTER
#  define XmImSetFocusValues	XMIMSETFOCUSVALUES
#  define XmImSetValues	XMIMSETVALUES
#  define XmImUnregister	XMIMUNREGISTER
#  define XmImUnsetFocus	XMIMUNSETFOCUS
#  define XmInstallImage	XMINSTALLIMAGE
#  define XmInternAtom	XMINTERNATOM
#  define XmIsMotifWMRunning	XMISMOTIFWMRUNNING
#  define XmListAddItem	XMLISTADDITEM
#  define XmListAddItemUnselected	XMLISTADDITEMUNSELECTED
#  define XmListAddItems	XMLISTADDITEMS
#  define XmListAddItemsUnselected	XMLISTADDITEMSUNSELECTED
#  define XmListDeleteAllItems	XMLISTDELETEALLITEMS
#  define XmListDeleteItem	XMLISTDELETEITEM
#  define XmListDeleteItemsPos	XMLISTDELETEITEMSPOS
#  define XmListDeletePos	XMLISTDELETEPOS
#  define XmListDeselectAllItems	XMLISTDESELECTALLITEMS
#  define XmListDeselectPos	XMLISTDESELECTPOS
#  define XmListGetKbdItemPos	XMLISTGETKBDITEMPOS
#  define XmListGetMatchPos	XMLISTGETMATCHPOS
#  define XmListGetSelectedPos	XMLISTGETSELECTEDPOS
#  define XmListItemExists	XMLISTITEMEXISTS
#  define XmListItemPos	XMLISTITEMPOS
#  define XmListPosSelected	XMLISTPOSSELECTED
#  define XmListReplaceItems	XMLISTREPLACEITEMS
#  define XmListReplaceItemsPos	XMLISTREPLACEITEMSPOS
#  define XmListSelectItem	XMLISTSELECTITEM
#  define XmListSelectPos	XMLISTSELECTPOS
#  define XmListSetBottomPos	XMLISTSETBOTTOMPOS
#  define XmListSetItem	XMLISTSETITEM
#  define XmListSetKbdItemPos	XMLISTSETKBDITEMPOS
#  define XmListSetPos	XMLISTSETPOS
#  define XmMainWindowSetAreas	XMMAINWINDOWSETAREAS
#  define XmMenuPosition	XMMENUPOSITION
#  define XmMessageBoxGetChild	XMMESSAGEBOXGETCHILD
#  define XmOptionButtonGadget	XMOPTIONBUTTONGADGET
#  define XmOptionLabelGadget	XMOPTIONLABELGADGET
#  define XmProcessTraversal	XMPROCESSTRAVERSAL
#  define XmQmotif	XMQMOTIF
#  define XmRemoveProtocolCallback	XMREMOVEPROTOCOLCALLBACK
#  define XmRemoveProtocols	XMREMOVEPROTOCOLS
#  define XmRemoveTabGroup	XMREMOVETABGROUP
#  define XmRepTypeGetId	XMREPTYPEGETID
#  define XmRepTypeGetRecord	XMREPTYPEGETRECORD
#  define XmRepTypeInstallTearOffModelCon	XMREPTYPEINSTALLTEAROFFMODELCON
#  define XmRepTypeRegister	XMREPTYPEREGISTER
#  define XmRepTypeValidValue	XMREPTYPEVALIDVALUE
#  define XmScrollBarGetValues	XMSCROLLBARGETVALUES
#  define XmScrollBarSetValues	XMSCROLLBARSETVALUES
#  define XmScrolledWindowSetAreas	XMSCROLLEDWINDOWSETAREAS
#  define XmSelectionBoxGetChild	XMSELECTIONBOXGETCHILD
#  define XmSetColorCalculation	XMSETCOLORCALCULATION
#  define XmStringByteCompare	XMSTRINGBYTECOMPARE
#  define XmStringCompare	XMSTRINGCOMPARE
#  define XmStringConcat	XMSTRINGCONCAT
#  define XmStringCopy	XMSTRINGCOPY
#  define XmStringCreate	XMSTRINGCREATE
#  define XmStringCreateLocalized	XMSTRINGCREATELOCALIZED
#  define XmStringCreateLtoR	XMSTRINGCREATELTOR
#  define XmStringCreateSimple	XMSTRINGCREATESIMPLE
#  define XmStringDraw	XMSTRINGDRAW
#  define XmStringDrawUnderline	XMSTRINGDRAWUNDERLINE
#  define XmStringExtent	XMSTRINGEXTENT
#  define XmStringFree	XMSTRINGFREE
#  define XmStringFreeContext	XMSTRINGFREECONTEXT
#  define XmStringGetLtoR	XMSTRINGGETLTOR
#  define XmStringGetNextComponent	XMSTRINGGETNEXTCOMPONENT
#  define XmStringGetNextSegment	XMSTRINGGETNEXTSEGMENT
#  define XmStringInitContext	XMSTRINGINITCONTEXT
#  define XmStringLength	XMSTRINGLENGTH
#  define XmStringLtoRCreate	XMSTRINGLTORCREATE
#  define XmStringNConcat	XMSTRINGNCONCAT
#  define XmStringSegmentCreate	XMSTRINGSEGMENTCREATE
#  define XmStringSeparatorCreate	XMSTRINGSEPARATORCREATE
#  define XmStringWidth	XMSTRINGWIDTH
#  define XmTextClearSelection	XMTEXTCLEARSELECTION
#  define XmTextCopy	XMTEXTCOPY
#  define XmTextCut	XMTEXTCUT
#  define XmTextFieldClearSelection	XMTEXTFIELDCLEARSELECTION
#  define XmTextFieldCopy	XMTEXTFIELDCOPY
#  define XmTextFieldCut	XMTEXTFIELDCUT
#  define XmTextFieldGetEditable	XMTEXTFIELDGETEDITABLE
#  define XmTextFieldGetInsertionPosition	XMTEXTFIELDGETINSERTIONPOSITION
#  define XmTextFieldGetLastPosition	XMTEXTFIELDGETLASTPOSITION
#  define XmTextFieldGetMaxLength	XMTEXTFIELDGETMAXLENGTH
#  define XmTextFieldGetSelection	XMTEXTFIELDGETSELECTION
#  define XmTextFieldGetSelectionPosition	XMTEXTFIELDGETSELECTIONPOSITION
#  define XmTextFieldGetString	XMTEXTFIELDGETSTRING
#  define XmTextFieldInsert	XMTEXTFIELDINSERT
#  define XmTextFieldPaste	XMTEXTFIELDPASTE
#  define XmTextFieldRemove	XMTEXTFIELDREMOVE
#  define XmTextFieldReplace	XMTEXTFIELDREPLACE
#  define XmTextFieldSetAddMode	XMTEXTFIELDSETADDMODE
#  define XmTextFieldSetHighlight	XMTEXTFIELDSETHIGHLIGHT
#  define XmTextFieldSetInsertionPosition	XMTEXTFIELDSETINSERTIONPOSITION
#  define XmTextFieldSetMaxLength	XMTEXTFIELDSETMAXLENGTH
#  define XmTextFieldSetSelection	XMTEXTFIELDSETSELECTION
#  define XmTextFieldSetString	XMTEXTFIELDSETSTRING
#  define XmTextFieldShowPosition	XMTEXTFIELDSHOWPOSITION
#  define XmTextGetCursorPosition	XMTEXTGETCURSORPOSITION
#  define XmTextGetEditable	XMTEXTGETEDITABLE
#  define XmTextGetInsertionPosition	XMTEXTGETINSERTIONPOSITION
#  define XmTextGetLastPosition	XMTEXTGETLASTPOSITION
#  define XmTextGetMaxLength	XMTEXTGETMAXLENGTH
#  define XmTextGetSelection	XMTEXTGETSELECTION
#  define XmTextGetSelectionPosition	XMTEXTGETSELECTIONPOSITION
#  define XmTextGetString	XMTEXTGETSTRING
#  define XmTextInsert	XMTEXTINSERT
#  define XmTextPaste	XMTEXTPASTE
#  define XmTextPosToXY	XMTEXTPOSTOXY
#  define XmTextRemove	XMTEXTREMOVE
#  define XmTextReplace	XMTEXTREPLACE
#  define XmTextSetCursorPosition	XMTEXTSETCURSORPOSITION
#  define XmTextSetEditable	XMTEXTSETEDITABLE
#  define XmTextSetHighlight	XMTEXTSETHIGHLIGHT
#  define XmTextSetInsertionPosition	XMTEXTSETINSERTIONPOSITION
#  define XmTextSetSelection	XMTEXTSETSELECTION
#  define XmTextSetString	XMTEXTSETSTRING
#  define XmTextSetTopCharacter	XMTEXTSETTOPCHARACTER
#  define XmTextShowPosition	XMTEXTSHOWPOSITION
#  define XmToggleButtonGadgetGetState	XMTOGGLEBUTTONGADGETGETSTATE
#  define XmToggleButtonGadgetSetState	XMTOGGLEBUTTONGADGETSETSTATE
#  define XmToggleButtonGetState	XMTOGGLEBUTTONGETSTATE
#  define XmToggleButtonSetState	XMTOGGLEBUTTONSETSTATE
#  define XmUninstallImage	XMUNINSTALLIMAGE
#  define XmUpdateDisplay	XMUPDATEDISPLAY
#  define XmVaCreateSimpleRadioBox	XMVACREATESIMPLERADIOBOX
#  define XmbDrawString	XMBDRAWSTRING
#  define XmbLookupString	XMBLOOKUPSTRING
#  define XmbResetIC	XMBRESETIC
#  define XmbSetWMProperties	XMBSETWMPROPERTIES
#  define XmbTextEscapement	XMBTEXTESCAPEMENT
#  define XmbTextExtents	XMBTEXTEXTENTS
#  define XmbTextListToTextProperty	XMBTEXTLISTTOTEXTPROPERTY
#  define XmbTextPropertyToTextList	XMBTEXTPROPERTYTOTEXTLIST
#  define XmbufCreateBuffers	XMBUFCREATEBUFFERS
#  define XmbufDestroyBuffers	XMBUFDESTROYBUFFERS
#  define XmbufDisplayBuffers	XMBUFDISPLAYBUFFERS
#  define XmbufQueryExtension	XMBUFQUERYEXTENSION
#  define Xmemory_free	XMEMORY_FREE
#  define Xmemory_malloc	XMEMORY_MALLOC
#  define XmuClientWindow	XMUCLIENTWINDOW
#  define XmuConvertStandardSelection	XMUCONVERTSTANDARDSELECTION
#  define XmuCvtStringToBitmap	XMUCVTSTRINGTOBITMAP
#  define XmuInternAtom	XMUINTERNATOM
#  define XmuInternStrings	XMUINTERNSTRINGS
#  define XmuLookupStandardColormap	XMULOOKUPSTANDARDCOLORMAP
#  define XmuPrintDefaultErrorMessage	XMUPRINTDEFAULTERRORMESSAGE
#  define XrmCombineDatabase	XRMCOMBINEDATABASE
#  define XrmCombineFileDatabase	XRMCOMBINEFILEDATABASE
#  define XrmDestroyDatabase	XRMDESTROYDATABASE
#  define XrmGetDatabase	XRMGETDATABASE
#  define XrmGetFileDatabase	XRMGETFILEDATABASE
#  define XrmGetResource	XRMGETRESOURCE
#  define XrmGetStringDatabase	XRMGETSTRINGDATABASE
#  define XrmInitialize	XRMINITIALIZE
#  define XrmMergeDatabases	XRMMERGEDATABASES
#  define XrmParseCommand	XRMPARSECOMMAND
#  define XrmPermStringToQuark	XRMPERMSTRINGTOQUARK
#  define XrmPutFileDatabase	XRMPUTFILEDATABASE
#  define XrmPutLineResource	XRMPUTLINERESOURCE
#  define XrmPutStringResource	XRMPUTSTRINGRESOURCE
#  define XrmQGetResource	XRMQGETRESOURCE
#  define XrmQPutStringResource	XRMQPUTSTRINGRESOURCE
#  define XrmQuarkToString	XRMQUARKTOSTRING
#  define XrmSetDatabase	XRMSETDATABASE
#  define XrmStringToBindingQuarkList	XRMSTRINGTOBINDINGQUARKLIST
#  define XrmStringToQuark	XRMSTRINGTOQUARK
#  define XtAddCallback	XTADDCALLBACK
#  define XtAddCallbacks	XTADDCALLBACKS
#  define XtAddConverter	XTADDCONVERTER
#  define XtAddEventHandler	XTADDEVENTHANDLER
#  define XtAddExposureToRegion	XTADDEXPOSURETOREGION
#  define XtAddGrab	XTADDGRAB
#  define XtAddRawEventHandler	XTADDRAWEVENTHANDLER
#  define XtAllocateGC	XTALLOCATEGC
#  define XtAppAddActions	XTAPPADDACTIONS
#  define XtAppAddInput	XTAPPADDINPUT
#  define XtAppAddTimeOut	XTAPPADDTIMEOUT
#  define XtAppAddWorkProc	XTAPPADDWORKPROC
#  define XtAppCreateShell	XTAPPCREATESHELL
#  define XtAppError	XTAPPERROR
#  define XtAppErrorMsg	XTAPPERRORMSG
#  define XtAppInitialize	XTAPPINITIALIZE
#  define XtAppMainLoop	XTAPPMAINLOOP
#  define XtAppNextEvent	XTAPPNEXTEVENT
#  define XtAppPeekEvent	XTAPPPEEKEVENT
#  define XtAppPending	XTAPPPENDING
#  define XtAppProcessEvent	XTAPPPROCESSEVENT
#  define XtAppSetErrorHandler	XTAPPSETERRORHANDLER
#  define XtAppSetFallbackResources	XTAPPSETFALLBACKRESOURCES
#  define XtAppSetTypeConverter	XTAPPSETTYPECONVERTER
#  define XtAppSetWarningHandler	XTAPPSETWARNINGHANDLER
#  define XtAppWarningMsg	XTAPPWARNINGMSG
#  define XtAppSetWarningMsgHandler	XTAPPSETWARNINGMSGHANDLER
#  define XtAppWarning	XTAPPWARNING
#  define XtAugmentTranslations	XTAUGMENTTRANSLATIONS
#  define XtCallActionProc	XTCALLACTIONPROC
#  define XtCallCallbackList	XTCALLCALLBACKLIST
#  define XtCallCallbacks	XTCALLCALLBACKS
#  define XtCallConverter	XTCALLCONVERTER
#  define XtCalloc	XTCALLOC
#  ifndef NOXTDISPLAY
#    define XtClass	XTCLASS
#  endif
#  define XtCloseDisplay	XTCLOSEDISPLAY
#  define XtConfigureWidget	XTCONFIGUREWIDGET
#  define XtConvert	XTCONVERT
#  define XtConvertAndStore	XTCONVERTANDSTORE
#  define XtCreateApplicationContext	XTCREATEAPPLICATIONCONTEXT
#  define XtCreateManagedWidget	XTCREATEMANAGEDWIDGET
#  define XtCreatePopupShell	XTCREATEPOPUPSHELL
#  define XtCreateWidget	XTCREATEWIDGET
#  define XtCreateWindow	XTCREATEWINDOW
#  define XtCvtStringToFont	XTCVTSTRINGTOFONT
#  define XtDatabase	XTDATABASE
#  define XtDestroyApplicationContext	XTDESTROYAPPLICATIONCONTEXT
#  define XtDestroyWidget	XTDESTROYWIDGET
#  define XtDisownSelection	XTDISOWNSELECTION
#  define XtDispatchEvent	XTDISPATCHEVENT
#  ifndef NOXTDISPLAY
#    define XtDisplay	XTDISPLAY
#  endif
#  define XtDisplayOfObject	XTDISPLAYOFOBJECT
#  define XtDisplayStringConvWarning	XTDISPLAYSTRINGCONVWARNING
#  define XtDisplayToApplicationContext	XTDISPLAYTOAPPLICATIONCONTEXT
#  define XtError	XTERROR
#  define XtErrorMsg	XTERRORMSG
#  define XtFree	XTFREE
#  define XtGetActionKeysym	XTGETACTIONKEYSYM
#  define XtGetActionList	XTGETACTIONLIST
#  define XtGetApplicationNameAndClass	XTGETAPPLICATIONNAMEANDCLASS
#  define XtGetApplicationResources	XTGETAPPLICATIONRESOURCES
#  define XtGetClassExtension	XTGETCLASSEXTENSION
#  define XtGetConstraintResourceList	XTGETCONSTRAINTRESOURCELIST
#  define XtGetGC	XTGETGC
#  define XtGetMultiClickTime	XTGETMULTICLICKTIME
#  define XtGetResourceList	XTGETRESOURCELIST
#  define XtGetSelectionValue	XTGETSELECTIONVALUE
#  define XtGetSelectionValues	XTGETSELECTIONVALUES
#  define XtGetSubresources	XTGETSUBRESOURCES
#  define XtGetValues	XTGETVALUES
#  define XtGrabButton	XTGRABBUTTON
#  define XtGrabKeyboard	XTGRABKEYBOARD
#  define XtGrabPointer	XTGRABPOINTER
#  define XtHasCallbacks	XTHASCALLBACKS
#  define XtInitialize	XTINITIALIZE
#  define XtInitializeWidgetClass	XTINITIALIZEWIDGETCLASS
#  define XtInsertEventHandler	XTINSERTEVENTHANDLER
#  define XtInsertRawEventHandler	XTINSERTRAWEVENTHANDLER
#  define XtInstallAccelerators	XTINSTALLACCELERATORS
#  define XtIsManaged	XTISMANAGED
#  define XtIsObject	XTISOBJECT
#  ifndef NOXTDISPLAY
#    define XtIsRealized	XTISREALIZED
#  endif
#  define XtIsSensitive	XTISSENSITIVE
#  define XtIsSubclass	XTISSUBCLASS
#  define XtLastTimestampProcessed	XTLASTTIMESTAMPPROCESSED
#  define XtMainLoop	XTMAINLOOP
#  define XtMakeGeometryRequest	XTMAKEGEOMETRYREQUEST
#  define XtMakeResizeRequest	XTMAKERESIZEREQUEST
#  define XtMalloc	XTMALLOC
#  define XtManageChild	XTMANAGECHILD
#  define XtManageChildren	XTMANAGECHILDREN
#  define XtMergeArgLists	XTMERGEARGLISTS
#  define XtMoveWidget	XTMOVEWIDGET
#  define XtName	XTNAME
#  define XtNameToWidget	XTNAMETOWIDGET
#  define XtOpenApplication	XTOPENAPPLICATION
#  define XtOpenDisplay	XTOPENDISPLAY
#  define XtOverrideTranslations	XTOVERRIDETRANSLATIONS
#  define XtOwnSelection	XTOWNSELECTION
#  ifndef NOXTDISPLAY
#    define XtParent	XTPARENT
#  endif
#  define XtParseAcceleratorTable	XTPARSEACCELERATORTABLE
#  define XtParseTranslationTable	XTPARSETRANSLATIONTABLE
#  define XtPopdown	XTPOPDOWN
#  define XtPopup	XTPOPUP
#  define XtPopupSpringLoaded	XTPOPUPSPRINGLOADED
#  define XtQueryGeometry	XTQUERYGEOMETRY
#  define XtRealizeWidget	XTREALIZEWIDGET
#  define XtRealloc	XTREALLOC
#  define XtRegisterDrawable	_XTREGISTERWINDOW
#  define XtRegisterGrabAction	XTREGISTERGRABACTION
#  define XtReleaseGC	XTRELEASEGC
#  define XtRemoveAllCallbacks	XTREMOVEALLCALLBACKS
#  define XtRemoveCallback	XTREMOVECALLBACK
#  define XtRemoveEventHandler	XTREMOVEEVENTHANDLER
#  define XtRemoveGrab	XTREMOVEGRAB
#  define XtRemoveInput	XTREMOVEINPUT
#  define XtRemoveTimeOut	XTREMOVETIMEOUT
#  define XtRemoveWorkProc	XTREMOVEWORKPROC
#  define XtResizeWidget	XTRESIZEWIDGET
#  define XtResolvePathname	XTRESOLVEPATHNAME
#  ifndef NOXTDISPLAY
#    define XtScreen	XTSCREEN
#  endif
#  define XtScreenDatabase	XTSCREENDATABASE
#  define XtScreenOfObject	XTSCREENOFOBJECT
#  define XtSessionReturnToken	XTSESSIONRETURNTOKEN
#  define XtSetErrorHandler	XTSETERRORHANDLER
#  define XtSetKeyboardFocus	XTSETKEYBOARDFOCUS
#  define XtSetLanguageProc	XTSETLANGUAGEPROC
#  define XtSetMappedWhenManaged	XTSETMAPPEDWHENMANAGED
#  define XtSetSensitive	XTSETSENSITIVE
#  define XtSetTypeConverter	XTSETTYPECONVERTER
#  define XtSetValues	XTSETVALUES
#  define XtShellStrings	XTSHELLSTRINGS
#  define XtStringConversionWarning	XTSTRINGCONVERSIONWARNING
#  define XtStrings	XTSTRINGS
#  define XtToolkitInitialize	XTTOOLKITINITIALIZE
#  define XtTranslateCoords	XTTRANSLATECOORDS
#  define XtTranslateKeycode	XTTRANSLATEKEYCODE
#  define XtUngrabButton	XTUNGRABBUTTON
#  define XtUngrabKeyboard	XTUNGRABKEYBOARD
#  define XtUngrabPointer	XTUNGRABPOINTER
#  define XtUnmanageChild	XTUNMANAGECHILD
#  define XtUnmanageChildren	XTUNMANAGECHILDREN
#  define XtUnrealizeWidget	XTUNREALIZEWIDGET
#  define XtUnregisterDrawable	_XTUNREGISTERWINDOW
#  define XtVaCreateManagedWidget	XTVACREATEMANAGEDWIDGET
#  define XtVaCreatePopupShell	XTVACREATEPOPUPSHELL
#  define XtVaCreateWidget	XTVACREATEWIDGET
#  define XtVaGetApplicationResources	XTVAGETAPPLICATIONRESOURCES
#  define XtVaGetValues	XTVAGETVALUES
#  define XtVaSetValues	XTVASETVALUES
#  define XtWarning	XTWARNING
#  define XtWarningMsg	XTWARNINGMSG
#  define XtWidgetToApplicationContext	XTWIDGETTOAPPLICATIONCONTEXT
#  ifndef NOXTDISPLAY
#    define XtWindow	XTWINDOW
#  endif
#  define XtWindowOfObject	XTWINDOWOFOBJECT
#  define XtWindowToWidget	XTWINDOWTOWIDGET
#  define XwcDrawImageString	XWCDRAWIMAGESTRING
#  define XwcDrawString	XWCDRAWSTRING
#  define XwcFreeStringList	XWCFREESTRINGLIST
#  define XwcTextEscapement	XWCTEXTESCAPEMENT
#  define XwcTextExtents	XWCTEXTEXTENTS
#  define XwcTextListToTextProperty	XWCTEXTLISTTOTEXTPROPERTY
#  define XwcLookupString	XWCLOOKUPSTRING
#  define XwcTextPropertyToTextList	XWCTEXTPROPERTYTOTEXTLIST
#  define _XAllocTemp	_XALLOCTEMP
#  define _XDeqAsyncHandler	_XDEQASYNCHANDLER
#  define _XEatData	_XEATDATA
#  define _XFlush	_XFLUSH
#  define _XFreeTemp	_XFREETEMP
#  define _XGetAsyncReply	_XGETASYNCREPLY
#  define _XInitImageFuncPtrs	_XINITIMAGEFUNCPTRS
#  define _XRead	_XREAD
#  define _XReadPad	_XREADPAD
#  define _XRegisterFilterByType	_XREGISTERFILTERBYTYPE
#  define _XReply	_XREPLY
#  define _XSend	_XSEND
#  define _XUnregisterFilter	_XUNREGISTERFILTER
#  define _XVIDtoVisual	_XVIDTOVISUAL
#  define _XmBottomShadowColorDefault	_XMBOTTOMSHADOWCOLORDEFAULT
#  define _XmClearBorder	_XMCLEARBORDER
#  define _XmConfigureObject	_XMCONFIGUREOBJECT
#  define _XmDestroyParentCallback	_XMDESTROYPARENTCALLBACK
#  define _XmDrawArrow	_XMDRAWARROW
#  define _XmDrawShadows	_XMDRAWSHADOWS
#  define _XmFontListGetDefaultFont	_XMFONTLISTGETDEFAULTFONT
#  define _XmFromHorizontalPixels	_XMFROMHORIZONTALPIXELS
#  define _XmFromVerticalPixels	_XMFROMVERTICALPIXELS
#  define _XmGetClassExtensionPtr	_XMGETCLASSEXTENSIONPTR
#  define _XmGetDefaultFontList	_XMGETDEFAULTFONTLIST
#  define _XmGetTextualDragIcon	_XMGETTEXTUALDRAGICON
#  define _XmGetWidgetExtData	_XMGETWIDGETEXTDATA
#  define _XmGrabKeyboard	_XMGRABKEYBOARD
#  define _XmGrabPointer	_XMGRABPOINTER
#  define _XmInheritClass	_XMINHERITCLASS
#  define _XmInputForGadget	_XMINPUTFORGADGET
#  define _XmInputInGadget	_XMINPUTINGADGET
#  define _XmMakeGeometryRequest	_XMMAKEGEOMETRYREQUEST
#  define _XmMenuPopDown	_XMMENUPOPDOWN
#  define _XmMoveObject	_XMMOVEOBJECT
#  define _XmNavigChangeManaged	_XMNAVIGCHANGEMANAGED
#  define _XmOSBuildFileList	_XMOSBUILDFILELIST
#  define _XmOSFileCompare	_XMOSFILECOMPARE
#  define _XmOSFindPatternPart	_XMOSFINDPATTERNPART
#  define _XmOSQualifyFileSpec	_XMOSQUALIFYFILESPEC
#  define _XmPostPopupMenu	_XMPOSTPOPUPMENU
#  define _XmPrimitiveEnter	_XMPRIMITIVEENTER
#  define _XmPrimitiveLeave	_XMPRIMITIVELEAVE
#  define _XmRedisplayGadgets	_XMREDISPLAYGADGETS
#  define _XmShellIsExclusive	_XMSHELLISEXCLUSIVE
#  define _XmStringDraw	_XMSTRINGDRAW
#  define _XmStringGetTextConcat	_XMSTRINGGETTEXTCONCAT
#  define _XmStrings	_XMSTRINGS
#  define _XmToHorizontalPixels	_XMTOHORIZONTALPIXELS
#  define _XmToVerticalPixels	_XMTOVERTICALPIXELS
#  define _XmTopShadowColorDefault	_XMTOPSHADOWCOLORDEFAULT
#  define _Xm_fastPtr	_XM_FASTPTR
#  define _XtCheckSubclassFlag	_XTCHECKSUBCLASSFLAG
#  define _XtCopyFromArg	_XTCOPYFROMARG
#  define _XtCountVaList	_XTCOUNTVALIST
#  define _XtInherit	_XTINHERIT
#  define _XtInheritTranslations	_XTINHERITTRANSLATIONS
#  define _XtIsSubclassOf	_XTISSUBCLASSOF
#  define _XtVaToArgList	_XTVATOARGLIST
#  define applicationShellWidgetClass	APPLICATIONSHELLWIDGETCLASS
#  define cli	$dcl_parse CLI$DCL_PARSE
#  define cli	$get_value CLI$GET_VALUE
#  define cli	$present  CLI$PRESENT
#  define compositeClassRec	COMPOSITECLASSREC
#  define compositeWidgetClass	COMPOSITEWIDGETCLASS
#  define constraintClassRec	CONSTRAINTCLASSREC
#  define constraintWidgetClass	CONSTRAINTWIDGETCLASS
#  define coreWidgetClass	COREWIDGETCLASS
#  define exe	$getspi EXE$GETSPI
#  define lbr	$close LBR$CLOSE
#  define lbr	$get_header LBR$GET_HEADER
#  define lbr	$get_index LBR$GET_INDEX
#  define lbr	$get_record LBR$GET_RECORD
#  define lbr	$ini_control LBR$INI_CONTROL
#  define lbr	$lookup_key LBR$LOOKUP_KEY
#  define lbr	$open LBR$OPEN
#  define lbr	$output_help LBR$OUTPUT_HELP
#  define lib	$add_times LIB$ADD_TIMES
#  define lib	$addx LIB$ADDX
#  define lib	$create_dir LIB$CREATE_DIR
#  define lib	$create_vm_zone LIB$CREATE_VM_ZONE
#  define lib	$cvt_from_internal_time LIB$CVT_FROM_INTERNAL_TIME
#  define lib	$cvt_htb LIB$CVT_HTB
#  define lib	$cvt_vectim LIB$CVT_VECTIM
#  define lib	$day LIB$DAY
#  define lib	$day_of_week LIB$DAY_OF_WEEK
#  define lib	$delete_symbol LIB$DELETE_SYMBOL
#  define lib	$delete_vm_zone LIB$DELETE_VM_ZONE
#  define lib	$disable_ctrl LIB$DISABLE_CTRL
#  define lib	$ediv LIB$EDIV
#  define lib	$emul LIB$EMUL
#  define lib	$enable_ctrl LIB$ENABLE_CTRL
#  define lib	$find_vm_zone LIB$FIND_VM_ZONE
#  define lib	$format_date_time LIB$FORMAT_DATE_TIME
#  define lib	$free_timer LIB$FREE_TIMER
#  define lib	$free_vm LIB$FREE_VM
#  define lib	$get_ef LIB$GET_EF
#  define lib	$get_foreign LIB$GET_FOREIGN
#  define lib	$get_input LIB$GET_INPUT
#  define lib	$get_users_language LIB$GET_USERS_LANGUAGE
#  define lib	$get_vm LIB$GET_VM
#  define lib	$get_symbol LIB$GET_SYMBOL
#  define lib	$getdvi LIB$GETDVI
#  define lib	$init_date_time_context LIB$INIT_DATE_TIME_CONTEXT
#  define lib	$init_timer LIB$INIT_TIMER
#  define lib	$find_file LIB$FIND_FILE
#  define lib	$find_file_end LIB$FIND_FILE_END
#  define lib	$find_image_symbol LIB$FIND_IMAGE_SYMBOL
#  define lib	$mult_delta_time LIB$MULT_DELTA_TIME
#  define lib	$put_output LIB$PUT_OUTPUT
#  define lib	$rename_file LIB$RENAME_FILE
#  define lib	$reset_vm_zone LIB$RESET_VM_ZONE
#  define lib	$set_symbol LIB$SET_SYMBOL
#  define lib	$sfree1_dd LIB$SFREE1_DD
#  define lib	$show_vm LIB$SHOW_VM
#  define lib	$show_vm_zone LIB$SHOW_VM_ZONE
#  define lib	$spawn LIB$SPAWN
#  define lib	$stat_timer LIB$STAT_TIMER
#  define lib	$subx LIB$SUBX
#  define lib	$sub_times LIB$SUB_TIMES
#  define lib	$wait LIB$WAIT
#  define mail	$send_add_address MAIL$SEND_ADD_ADDRESS
#  define mail	$send_add_attribute MAIL$SEND_ADD_ATTRIBUTE
#  define mail	$send_add_bodypart MAIL$SEND_ADD_BODYPART
#  define mail	$send_begin MAIL$SEND_BEGIN
#  define mail	$send_end MAIL$SEND_END
#  define mail	$send_message MAIL$SEND_MESSAGE
#  define ncs	$convert NCS$CONVERT
#  define ncs	$get_cf NCS$GET_CF
#  define objectClass	OBJECTCLASS
#  define objectClassRec	OBJECTCLASSREC
#  define overrideShellClassRec	OVERRIDESHELLCLASSREC
#  define overrideShellWidgetClass	OVERRIDESHELLWIDGETCLASS
#  define pthread_attr_create	PTHREAD_ATTR_CREATE
#  define pthread_attr_delete	PTHREAD_ATTR_DELETE
#  define pthread_attr_destroy	PTHREAD_ATTR_DESTROY
#  define pthread_attr_getdetach_np	PTHREAD_ATTR_GETDETACH_NP
#  define pthread_attr_getguardsize_np	PTHREAD_ATTR_GETGUARDSIZE_NP
#  define pthread_attr_getinheritsched	PTHREAD_ATTR_GETINHERITSCHED
#  define pthread_attr_getprio	PTHREAD_ATTR_GETPRIO
#  define pthread_attr_getsched	PTHREAD_ATTR_GETSCHED
#  define pthread_attr_getschedparam	PTHREAD_ATTR_GETSCHEDPARAM
#  define pthread_attr_getschedpolicy	PTHREAD_ATTR_GETSCHEDPOLICY
#  define pthread_attr_getstacksize	PTHREAD_ATTR_GETSTACKSIZE
#  define pthread_attr_init	PTHREAD_ATTR_INIT
#  define pthread_attr_setdetach_np	PTHREAD_ATTR_SETDETACH_NP
#  define pthread_attr_setdetachstate	PTHREAD_ATTR_SETDETACHSTATE
#  define pthread_attr_setguardsize_np	PTHREAD_ATTR_SETGUARDSIZE_NP
#  define pthread_attr_setinheritsched	PTHREAD_ATTR_SETINHERITSCHED
#  define pthread_attr_setprio	PTHREAD_ATTR_SETPRIO
#  define pthread_attr_setsched	PTHREAD_ATTR_SETSCHED
#  define pthread_attr_setschedparam	PTHREAD_ATTR_SETSCHEDPARAM
#  define pthread_attr_setschedpolicy	PTHREAD_ATTR_SETSCHEDPOLICY
#  ifndef pthread_attr_setscope
#    define pthread_attr_setscope	PTHREAD_ATTR_SETSCOPE
#  endif
#  define pthread_attr_setstacksize	PTHREAD_ATTR_SETSTACKSIZE
#  define pthread_cancel	PTHREAD_CANCEL
#  define pthread_cancel_e	PTHREAD_CANCEL_E
#  define pthread_cond_broadcast	PTHREAD_COND_BROADCAST
#  define pthread_cond_destroy	PTHREAD_COND_DESTROY
#  define pthread_cond_init	PTHREAD_COND_INIT
#  define pthread_cond_sig_preempt_int_np	PTHREAD_COND_SIG_PREEMPT_INT_NP
#  define pthread_cond_signal	PTHREAD_COND_SIGNAL
#  define pthread_cond_signal_int_np	PTHREAD_COND_SIGNAL_INT_NP
#  define pthread_cond_timedwait	PTHREAD_COND_TIMEDWAIT
#  define pthread_cond_wait	PTHREAD_COND_WAIT
#  define pthread_condattr_create	PTHREAD_CONDATTR_CREATE
#  define pthread_condattr_delete	PTHREAD_CONDATTR_DELETE
#  define pthread_condattr_init	PTHREAD_CONDATTR_INIT
#  define pthread_create	PTHREAD_CREATE
#  define pthread_delay_np	PTHREAD_DELAY_NP
#  define pthread_detach	PTHREAD_DETACH
#  define pthread_equal	PTHREAD_EQUAL
#  define pthread_exc_fetch_fp_np	PTHREAD_EXC_FETCH_FP_NP
#  define pthread_exc_handler_np	PTHREAD_EXC_HANDLER_NP
#  define pthread_exc_matches_np	PTHREAD_EXC_MATCHES_NP
#  define pthread_exc_pop_ctx_np	PTHREAD_EXC_POP_CTX_NP
#  define pthread_exc_push_ctx_np	PTHREAD_EXC_PUSH_CTX_NP
#  define pthread_exc_raise_np	PTHREAD_EXC_RAISE_NP
#  define pthread_exc_savecontext_np	PTHREAD_EXC_SAVECONTEXT_NP
#  define pthread_exit	PTHREAD_EXIT
#  define pthread_get_expiration_np	PTHREAD_GET_EXPIRATION_NP
#  define pthread_getprio	PTHREAD_GETPRIO
#  define pthread_getschedparam	PTHREAD_GETSCHEDPARAM
#  define pthread_getscheduler	PTHREAD_GETSCHEDULER
#  define pthread_getspecific	PTHREAD_GETSPECIFIC
#  define pthread_getunique_np	PTHREAD_GETUNIQUE_NP
#  define pthread_join	PTHREAD_JOIN
#  define pthread_join32	PTHREAD_JOIN32
#  define pthread_key_create	PTHREAD_KEY_CREATE
#  define pthread_key_delete	PTHREAD_KEY_DELETE
#  define pthread_keycreate	PTHREAD_KEYCREATE
#  define pthread_kill	PTHREAD_KILL
#  define pthread_lock_global_np	PTHREAD_LOCK_GLOBAL_NP
#  define pthread_mutex_destroy	PTHREAD_MUTEX_DESTROY
#  define pthread_mutex_init	PTHREAD_MUTEX_INIT
#  define pthread_mutex_lock	PTHREAD_MUTEX_LOCK
#  define pthread_mutex_trylock	PTHREAD_MUTEX_TRYLOCK
#  define pthread_mutex_unlock	PTHREAD_MUTEX_UNLOCK
#  define pthread_mutexattr_create	PTHREAD_MUTEXATTR_CREATE
#  define pthread_mutexattr_delete	PTHREAD_MUTEXATTR_DELETE
#  define pthread_mutexattr_destroy	PTHREAD_MUTEXATTR_DESTROY
#  define pthread_mutexattr_getkind_np	PTHREAD_MUTEXATTR_GETKIND_NP
#  define pthread_mutexattr_init	PTHREAD_MUTEXATTR_INIT
#  define pthread_mutexattr_setkind_np	PTHREAD_MUTEXATTR_SETKIND_NP
#  define pthread_mutexattr_settype_np	PTHREAD_MUTEXATTR_SETTYPE_NP
#  define pthread_once	PTHREAD_ONCE
#  define pthread_resume_np	PTHREAD_RESUME_NP
#  define pthread_self	PTHREAD_SELF
#  define pthread_setasynccancel	PTHREAD_SETASYNCCANCEL
#  define pthread_setcancel	PTHREAD_SETCANCEL
#  define pthread_setcancelstate	PTHREAD_SETCANCELSTATE
#  define pthread_setcanceltype	PTHREAD_SETCANCELTYPE
#  define pthread_setprio	PTHREAD_SETPRIO
#  define pthread_setschedparam	PTHREAD_SETSCHEDPARAM
#  define pthread_setscheduler	PTHREAD_SETSCHEDULER
#  define pthread_setspecific	PTHREAD_SETSPECIFIC
#  define pthread_suspend_np	PTHREAD_SUSPEND_NP
#  define pthread_testcancel	PTHREAD_TESTCANCEL
#  define pthread_unlock_global_np	PTHREAD_UNLOCK_GLOBAL_NP
#  define pthread_yield	PTHREAD_YIELD
#  define pthread_yield_np	PTHREAD_YIELD_NP
#  define rectObjClass	RECTOBJCLASS
#  define rectObjClassRec	RECTOBJCLASSREC
#  define sessionShellWidgetClass	SESSIONSHELLWIDGETCLASS
#  define shellWidgetClass	SHELLWIDGETCLASS
#  define shmat	SHMAT
#  define shmctl	SHMCTL
#  define shmdt	SHMDT
#  define shmget	SHMGET
#  define smg	$create_key_table SMG$CREATE_KEY_TABLE
#  define smg	$create_virtual_keyboard SMG$CREATE_VIRTUAL_KEYBOARD
#  define smg	$read_composed_line SMG$READ_COMPOSED_LINE
#  define sys	$add_ident SYS$ADD_IDENT
#  define sys	$asctoid SYS$ASCTOID
#  define sys	$assign SYS$ASSIGN
#  define sys	$bintim SYS$BINTIM
#  define sys	$cancel SYS$CANCEL
#  define sys	$cantim SYS$CANTIM
#  define sys	$check_access SYS$CHECK_ACCESS
#  define sys	$close SYS$CLOSE
#  define sys	$connect SYS$CONNECT
#  define sys	$create SYS$CREATE
#  define sys	$create_user_profile SYS$CREATE_USER_PROFILE
#  define sys	$crembx SYS$CREMBX
#  define sys	$creprc SYS$CREPRC
#  define sys	$crmpsc SYS$CRMPSC
#  define sys	$dassgn SYS$DASSGN
#  define sys	$dclast SYS$DCLAST
#  define sys	$dclexh SYS$DCLEXH
#  define sys	$delprc SYS$DELPRC
#  define sys	$deq SYS$DEQ
#  define sys	$dgblsc SYS$DGBLSC
#  define sys	$display SYS$DISPLAY
#  define sys	$enq SYS$ENQ
#  define sys	$enqw SYS$ENQW
#  define sys	$erase SYS$ERASE
#  define sys	$fao SYS$FAO
#  define sys	$faol SYS$FAOL
#  define sys	$find_held SYS$FIND_HELD
#  define sys	$finish_rdb SYS$FINISH_RDB
#  define sys	$flush SYS$FLUSH
#  define sys	$forcex SYS$FORCEX
#  define sys	$get SYS$GET
#  define sys	$get_security SYS$GET_SECURITY
#  define sys	$getdviw SYS$GETDVIW
#  define sys	$getjpi SYS$GETJPI
#  define sys	$getjpiw SYS$GETJPIW
#  define sys	$getlkiw SYS$GETLKIW
#  define sys	$getmsg SYS$GETMSG
#  define sys	$getsyi SYS$GETSYI
#  define sys	$getsyiw SYS$GETSYIW
#  define sys	$gettim SYS$GETTIM
#  define sys	$getuai SYS$GETUAI
#  define sys	$grantid SYS$GRANTID
#  define sys	$hash_password SYS$HASH_PASSWORD
#  define sys	$hiber SYS$HIBER
#  define sys	$mgblsc SYS$MGBLSC
#  define sys	$numtim SYS$NUMTIM
#  define sys	$open SYS$OPEN
#  define sys	$parse SYS$PARSE
#  define sys	$parse_acl SYS$PARSE_ACL
#  define sys	$parse_acl SYS$PARSE_ACL
#  define sys	$persona_assume SYS$PERSONA_ASSUME
#  define sys	$persona_create SYS$PERSONA_CREATE
#  define sys	$persona_delete SYS$PERSONA_DELETE
#  define sys	$process_scan SYS$PROCESS_SCAN
#  define sys	$put SYS$PUT
#  define sys	$qio SYS$QIO
#  define sys	$qiow SYS$QIOW
#  define sys	$read SYS$READ
#  define sys	$resched SYS$RESCHED
#  define sys	$rewind SYS$REWIND
#  define sys	$search SYS$SEARCH
#  define sys	$set_security SYS$SET_SECURITY
#  define sys	$setast SYS$SETAST
#  define sys	$setef SYS$SETEF
#  define sys	$setimr SYS$SETIMR
#  define sys	$setpri SYS$SETPRI
#  define sys	$setprn SYS$SETPRN
#  define sys	$setprv SYS$SETPRV
#  define sys	$setswm SYS$SETSWM
#  define sys	$setuai SYS$SETUAI
#  define sys	$sndopr SYS$SNDOPR
#  define sys	$synch SYS$SYNCH
#  define sys	$trnlnm SYS$TRNLNM
#  define sys	$update SYS$UPDATE
#  define sys	$wake SYS$WAKE
#  define sys	$write SYS$WRITE
#  define topLevelShellClassRec	TOPLEVELSHELLCLASSREC
#  define topLevelShellWidgetClass	TOPLEVELSHELLWIDGETCLASS
#  define transientShellWidgetClass	TRANSIENTSHELLWIDGETCLASS
#  define vendorShellClassRec	VENDORSHELLCLASSREC
#  define vendorShellWidgetClass	VENDORSHELLWIDGETCLASS
#  define widgetClass	WIDGETCLASS
#  define widgetClassRec	WIDGETCLASSREC
#  define wmShellClassRec	WMSHELLCLASSREC
#  define wmShellWidgetClass	WMSHELLWIDGETCLASS
#  define x	$soft_ast_lib_lock X$SOFT_AST_LIB_LOCK
#  define x	$soft_ast_lock_depth X$SOFT_AST_LOCK_DEPTH
#  define x	$soft_reenable_asts X$SOFT_REENABLE_ASTS
#  define xmArrowButtonWidgetClass	XMARROWBUTTONWIDGETCLASS
#  define xmBulletinBoardWidgetClass	XMBULLETINBOARDWIDGETCLASS
#  define xmCascadeButtonClassRec	XMCASCADEBUTTONCLASSREC
#  define xmCascadeButtonGadgetClass	XMCASCADEBUTTONGADGETCLASS
#  define xmCascadeButtonWidgetClass	XMCASCADEBUTTONWIDGETCLASS
#  define xmCommandWidgetClass	XMCOMMANDWIDGETCLASS
#  define xmDialogShellWidgetClass	XMDIALOGSHELLWIDGETCLASS
#  define xmDrawingAreaWidgetClass	XMDRAWINGAREAWIDGETCLASS
#  define xmDrawnButtonWidgetClass	XMDRAWNBUTTONWIDGETCLASS
#  define xmFileSelectionBoxWidgetClass	XMFILESELECTIONBOXWIDGETCLASS
#  define xmFormWidgetClass	XMFORMWIDGETCLASS
#  define xmFrameWidgetClass	XMFRAMEWIDGETCLASS
#  define xmGadgetClass	XMGADGETCLASS
#  define xmLabelGadgetClass	XMLABELGADGETCLASS
#  define xmLabelWidgetClass	XMLABELWIDGETCLASS
#  define xmListWidgetClass	XMLISTWIDGETCLASS
#  define xmMainWindowWidgetClass	XMMAINWINDOWWIDGETCLASS
#  define xmManagerClassRec	XMMANAGERCLASSREC
#  define xmManagerWidgetClass	XMMANAGERWIDGETCLASS
#  define xmMenuShellWidgetClass	XMMENUSHELLWIDGETCLASS
#  define xmMessageBoxWidgetClass	XMMESSAGEBOXWIDGETCLASS
#  define xmPrimitiveClassRec	XMPRIMITIVECLASSREC
#  define xmPrimitiveWidgetClass	XMPRIMITIVEWIDGETCLASS
#  define xmPushButtonClassRec	XMPUSHBUTTONCLASSREC
#  define xmPushButtonGadgetClass	XMPUSHBUTTONGADGETCLASS
#  define xmPushButtonWidgetClass	XMPUSHBUTTONWIDGETCLASS
#  define xmRowColumnWidgetClass	XMROWCOLUMNWIDGETCLASS
#  define xmSashWidgetClass	XMSASHWIDGETCLASS
#  define xmScaleWidgetClass	XMSCALEWIDGETCLASS
#  define xmScrollBarWidgetClass	XMSCROLLBARWIDGETCLASS
#  define xmScrolledWindowClassRec	XMSCROLLEDWINDOWCLASSREC
#  define xmScrolledWindowWidgetClass	XMSCROLLEDWINDOWWIDGETCLASS
#  define xmSeparatorGadgetClass	XMSEPARATORGADGETCLASS
#  define xmSeparatorWidgetClass	XMSEPARATORWIDGETCLASS
#  define xmTextFieldWidgetClass	XMTEXTFIELDWIDGETCLASS
#  define xmTextWidgetClass	XMTEXTWIDGETCLASS
#  define xmToggleButtonGadgetClass	XMTOGGLEBUTTONGADGETCLASS
#  define xmToggleButtonWidgetClass	XMTOGGLEBUTTONWIDGETCLASS
#  if  (__VMS_VER < 80200000)
#    define SetReqLen(req,n,badlen)	 \
    if ((req->length + n) > (unsigned)65535) { \
        n = badlen; \
        req->length += n; \
    } else \
    req->length += n
#  endif
extern "C" {
  extern void XtFree(char*);
  }
#endif
