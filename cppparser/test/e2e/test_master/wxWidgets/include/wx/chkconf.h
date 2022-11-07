/*
 * Name:        wx/chkconf.h
 * Purpose:     check the config settings for consistency
 * Author:      Vadim Zeitlin
 * Modified by:
 * Created:     09.08.00
 * Copyright:   (c) 2000 Vadim Zeitlin <vadim@wxwidgets.org>
 * Licence:     wxWindows licence
 */

/* THIS IS A C FILE, DON'T USE C++ FEATURES (IN PARTICULAR COMMENTS) IN IT */
#ifndef _WX_CHKCONF_H_
#  define _WX_CHKCONF_H_
/*
              **************************************************
              PLEASE READ THIS IF YOU GET AN ERROR IN THIS FILE!
              **************************************************

    If you get an error saying "wxUSE_FOO must be defined", it means that you
    are not using the correct up-to-date version of setup.h. This happens most
    often when using git or snapshots and a new symbol was added to setup0.h
    and you haven't updated your local setup.h to reflect it. If this is the
    case, you need to propagate the changes from setup0.h to your setup.h and,
    if using makefiles under MSW, also remove setup.h under the build directory
    (lib/$(COMPILER)_{lib,dll}/msw[u][d][dll]/wx) so that the new setup.h is
    copied there.

    If you get an error of the form "wxFoo requires wxBar", then the settings
    in your setup.h are inconsistent. You have the choice between correcting
    them manually or commenting out #define wxABORT_ON_CONFIG_ERROR below to
    try to correct the problems automatically (not really recommended but
    might work).
 */

/*
   This file has the following sections:
    1. checks that all wxUSE_XXX symbols we use are defined
     a) first the non-GUI ones
     b) then the GUI-only ones
    2. platform-specific checks done in the platform headers
    3. generic consistency checks
     a) first the non-GUI ones
     b) then the GUI-only ones
 */

/*
   this global setting determines what should we do if the setting FOO
   requires BAR and BAR is not set: we can either silently unset FOO as well
   (do this if you're trying to build the smallest possible library) or give an
   error and abort (default as leads to least surprising behaviour)
 */
#  define wxABORT_ON_CONFIG_ERROR
/*
   global features
 */

/*
    If we're compiling without support for threads/exceptions we have to
    disable the corresponding features.
 */
#  ifdef wxNO_THREADS
#    undef wxUSE_THREADS
#    define wxUSE_THREADS	0
#  endif
#  ifdef wxNO_EXCEPTIONS
#    undef wxUSE_EXCEPTIONS
#    define wxUSE_EXCEPTIONS	0
#  endif
/* we also must disable exceptions if compiler doesn't support them */
#  if  defined(_MSC_VER) && !defined(_CPPUNWIND)
#    undef wxUSE_EXCEPTIONS
#    define wxUSE_EXCEPTIONS	0
#  endif
/*
   Section 1a: tests for non GUI features.

   please keep the options in alphabetical order!
 */
#  ifndef wxUSE_ANY
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_ANY	0
#    endif
#  endif
#  ifndef wxUSE_COMPILER_TLS
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_COMPILER_TLS	0
#    endif
#  endif
#  ifndef wxUSE_CONSOLE_EVENTLOOP
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_CONSOLE_EVENTLOOP	0
#    endif
#  endif
#  ifndef wxUSE_DYNLIB_CLASS
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_DYNLIB_CLASS	0
#    endif
#  endif
#  ifndef wxUSE_EXCEPTIONS
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_EXCEPTIONS	0
#    endif
#  endif
#  ifndef wxUSE_FILE_HISTORY
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_FILE_HISTORY	0
#    endif
#  endif
#  ifndef wxUSE_FILESYSTEM
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_FILESYSTEM	0
#    endif
#  endif
#  ifndef wxUSE_FS_ARCHIVE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_FS_ARCHIVE	0
#    endif
#  endif
#  ifndef wxUSE_FSVOLUME
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_FSVOLUME	0
#    endif
#  endif
#  ifndef wxUSE_FSWATCHER
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_FSWATCHER	0
#    endif
#  endif
#  ifndef wxUSE_DYNAMIC_LOADER
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_DYNAMIC_LOADER	0
#    endif
#  endif
#  ifndef wxUSE_INTL
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_INTL	0
#    endif
#  endif
#  ifndef wxUSE_IPV6
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_IPV6	0
#    endif
#  endif
#  ifndef wxUSE_LOG
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_LOG	0
#    endif
#  endif
#  ifndef wxUSE_LONGLONG
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_LONGLONG	0
#    endif
#  endif
#  ifndef wxUSE_MIMETYPE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_MIMETYPE	0
#    endif
#  endif
#  ifndef wxUSE_ON_FATAL_EXCEPTION
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_ON_FATAL_EXCEPTION	0
#    endif
#  endif
#  ifndef wxUSE_PRINTF_POS_PARAMS
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_PRINTF_POS_PARAMS	0
#    endif
#  endif
#  ifndef wxUSE_PROTOCOL
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_PROTOCOL	0
#    endif
#  endif
/* we may not define wxUSE_PROTOCOL_XXX if wxUSE_PROTOCOL is set to 0 */
#  if  !wxUSE_PROTOCOL
#    undef wxUSE_PROTOCOL_HTTP
#    undef wxUSE_PROTOCOL_FTP
#    undef wxUSE_PROTOCOL_FILE
#    define wxUSE_PROTOCOL_HTTP	0
#    define wxUSE_PROTOCOL_FTP	0
#    define wxUSE_PROTOCOL_FILE	0
#  endif
#  ifndef wxUSE_PROTOCOL_HTTP
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_PROTOCOL_HTTP	0
#    endif
#  endif
#  ifndef wxUSE_PROTOCOL_FTP
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_PROTOCOL_FTP	0
#    endif
#  endif
#  ifndef wxUSE_PROTOCOL_FILE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_PROTOCOL_FILE	0
#    endif
#  endif
#  ifndef wxUSE_REGEX
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_REGEX	0
#    endif
#  endif
#  ifndef wxUSE_SECRETSTORE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_SECRETSTORE	1
#    endif
#  endif
#  ifndef wxUSE_STDPATHS
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_STDPATHS	1
#    endif
#  endif
#  ifndef wxUSE_XML
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_XML	0
#    endif
#  endif
#  ifndef wxUSE_STD_CONTAINERS_COMPATIBLY
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_STD_CONTAINERS_COMPATIBLY	0
#    endif
#  endif
#  ifndef wxUSE_STD_STRING_CONV_IN_WXSTRING
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_STD_STRING_CONV_IN_WXSTRING	0
#    endif
#  endif
#  ifndef wxUSE_STREAMS
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_STREAMS	0
#    endif
#  endif
#  ifndef wxUSE_STOPWATCH
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_STOPWATCH	0
#    endif
#  endif
#  ifndef wxUSE_TEXTBUFFER
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_TEXTBUFFER	0
#    endif
#  endif
#  ifndef wxUSE_TEXTFILE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_TEXTFILE	0
#    endif
#  endif
#  ifndef wxUSE_UNSAFE_WXSTRING_CONV
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_UNSAFE_WXSTRING_CONV	0
#    endif
#  endif
#  ifndef wxUSE_URL
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_URL	0
#    endif
#  endif
#  ifndef wxUSE_VARIANT
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_VARIANT	0
#    endif
#  endif
#  ifndef wxUSE_XLOCALE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      define wxUSE_XLOCALE	0
#    endif
#  endif
/*
   Section 1b: all these tests are for GUI only.

   please keep the options in alphabetical order!
 */
#  if  wxUSE_GUI
/*
   all of the settings tested below must be defined or we'd get an error from
   preprocessor about invalid integer expression
 */
#    ifndef wxUSE_ABOUTDLG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ABOUTDLG	0
#      endif
#    endif
#    ifndef wxUSE_ACCEL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ACCEL	0
#      endif
#    endif
#    ifndef wxUSE_ACCESSIBILITY
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ACCESSIBILITY	0
#      endif
#    endif
#    ifndef wxUSE_ADDREMOVECTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ADDREMOVECTRL	0
#      endif
#    endif
#    ifndef wxUSE_ACTIVITYINDICATOR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ACTIVITYINDICATOR	0
#      endif
#    endif
#    ifndef wxUSE_ANIMATIONCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ANIMATIONCTRL	0
#      endif
#    endif
#    ifndef wxUSE_ARTPROVIDER_STD
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ARTPROVIDER_STD	0
#      endif
#    endif
#    ifndef wxUSE_ARTPROVIDER_TANGO
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ARTPROVIDER_TANGO	0
#      endif
#    endif
#    ifndef wxUSE_AUTOID_MANAGEMENT
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_AUTOID_MANAGEMENT	0
#      endif
#    endif
#    ifndef wxUSE_BITMAPCOMBOBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_BITMAPCOMBOBOX	0
#      endif
#    endif
#    ifndef wxUSE_BMPBUTTON
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_BMPBUTTON	0
#      endif
#    endif
#    ifndef wxUSE_BUTTON
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_BUTTON	0
#      endif
#    endif
#    ifndef wxUSE_CAIRO
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CAIRO	0
#      endif
#    endif
#    ifndef wxUSE_CALENDARCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CALENDARCTRL	0
#      endif
#    endif
#    ifndef wxUSE_CARET
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CARET	0
#      endif
#    endif
#    ifndef wxUSE_CHECKBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CHECKBOX	0
#      endif
#    endif
#    ifndef wxUSE_CHECKLISTBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CHECKLISTBOX	0
#      endif
#    endif
#    ifndef wxUSE_CHOICE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CHOICE	0
#      endif
#    endif
#    ifndef wxUSE_CHOICEBOOK
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CHOICEBOOK	0
#      endif
#    endif
#    ifndef wxUSE_CHOICEDLG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CHOICEDLG	0
#      endif
#    endif
#    ifndef wxUSE_CLIPBOARD
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_CLIPBOARD	0
#      endif
#    endif
#    ifndef wxUSE_COLLPANE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_COLLPANE	0
#      endif
#    endif
#    ifndef wxUSE_COLOURDLG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_COLOURDLG	0
#      endif
#    endif
#    ifndef wxUSE_COLOURPICKERCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_COLOURPICKERCTRL	0
#      endif
#    endif
#    ifndef wxUSE_COMBOBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_COMBOBOX	0
#      endif
#    endif
#    ifndef wxUSE_COMMANDLINKBUTTON
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_COMMANDLINKBUTTON	0
#      endif
#    endif
#    ifndef wxUSE_COMBOCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_COMBOCTRL	0
#      endif
#    endif
#    ifndef wxUSE_DATAOBJ
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DATAOBJ	0
#      endif
#    endif
#    ifndef wxUSE_DATAVIEWCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DATAVIEWCTRL	0
#      endif
#    endif
#    ifndef wxUSE_NATIVE_DATAVIEWCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_NATIVE_DATAVIEWCTRL	1
#      endif
#    endif
#    ifndef wxUSE_DATEPICKCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DATEPICKCTRL	0
#      endif
#    endif
#    ifndef wxUSE_DC_TRANSFORM_MATRIX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DC_TRANSFORM_MATRIX	1
#      endif
#    endif
#    ifndef wxUSE_DIRPICKERCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DIRPICKERCTRL	0
#      endif
#    endif
#    ifndef wxUSE_DISPLAY
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DISPLAY	0
#      endif
#    endif
#    ifndef wxUSE_DOC_VIEW_ARCHITECTURE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DOC_VIEW_ARCHITECTURE	0
#      endif
#    endif
#    ifndef wxUSE_FILECTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_FILECTRL	0
#      endif
#    endif
#    ifndef wxUSE_FILEDLG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_FILEDLG	0
#      endif
#    endif
#    ifndef wxUSE_FILEPICKERCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_FILEPICKERCTRL	0
#      endif
#    endif
#    ifndef wxUSE_FONTDLG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_FONTDLG	0
#      endif
#    endif
#    ifndef wxUSE_FONTMAP
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_FONTMAP	0
#      endif
#    endif
#    ifndef wxUSE_FONTPICKERCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_FONTPICKERCTRL	0
#      endif
#    endif
#    ifndef wxUSE_GAUGE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_GAUGE	0
#      endif
#    endif
#    ifndef wxUSE_GRAPHICS_CONTEXT
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_GRAPHICS_CONTEXT	0
#      endif
#    endif
#    ifndef wxUSE_GRID
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_GRID	0
#      endif
#    endif
#    ifndef wxUSE_HEADERCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_HEADERCTRL	0
#      endif
#    endif
#    ifndef wxUSE_HELP
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_HELP	0
#      endif
#    endif
#    ifndef wxUSE_HYPERLINKCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_HYPERLINKCTRL	0
#      endif
#    endif
#    ifndef wxUSE_HTML
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_HTML	0
#      endif
#    endif
#    ifndef wxUSE_LIBMSPACK
#      if  !defined(__UNIX__)
        /* set to 0 on platforms that don't have libmspack */
#        define wxUSE_LIBMSPACK	0
#      else 
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          define wxUSE_LIBMSPACK	0
#        endif
#      endif
#    endif
#    ifndef wxUSE_ICO_CUR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ICO_CUR	0
#      endif
#    endif
#    ifndef wxUSE_IFF
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_IFF	0
#      endif
#    endif
#    ifndef wxUSE_IMAGLIST
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_IMAGLIST	0
#      endif
#    endif
#    ifndef wxUSE_INFOBAR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_INFOBAR	0
#      endif
#    endif
#    ifndef wxUSE_JOYSTICK
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_JOYSTICK	0
#      endif
#    endif
#    ifndef wxUSE_LISTBOOK
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_LISTBOOK	0
#      endif
#    endif
#    ifndef wxUSE_LISTBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_LISTBOX	0
#      endif
#    endif
#    ifndef wxUSE_LISTCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_LISTCTRL	0
#      endif
#    endif
#    ifndef wxUSE_LOGGUI
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_LOGGUI	0
#      endif
#    endif
#    ifndef wxUSE_LOGWINDOW
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_LOGWINDOW	0
#      endif
#    endif
#    ifndef wxUSE_LOG_DIALOG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_LOG_DIALOG	0
#      endif
#    endif
#    ifndef wxUSE_MARKUP
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_MARKUP	0
#      endif
#    endif
#    ifndef wxUSE_MDI
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_MDI	0
#      endif
#    endif
#    ifndef wxUSE_MDI_ARCHITECTURE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_MDI_ARCHITECTURE	0
#      endif
#    endif
#    ifndef wxUSE_MENUBAR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_MENUBAR	0
#      endif
#    endif
#    ifndef wxUSE_MENUS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_MENUS	0
#      endif
#    endif
#    ifndef wxUSE_MSGDLG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_MSGDLG	0
#      endif
#    endif
#    ifndef wxUSE_NOTEBOOK
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_NOTEBOOK	0
#      endif
#    endif
#    ifndef wxUSE_NOTIFICATION_MESSAGE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_NOTIFICATION_MESSAGE	0
#      endif
#    endif
#    ifndef wxUSE_ODCOMBOBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_ODCOMBOBOX	0
#      endif
#    endif
#    ifndef wxUSE_PALETTE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_PALETTE	0
#      endif
#    endif
#    ifndef wxUSE_POPUPWIN
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_POPUPWIN	0
#      endif
#    endif
#    ifndef wxUSE_PREFERENCES_EDITOR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_PREFERENCES_EDITOR	0
#      endif
#    endif
#    ifndef wxUSE_PRIVATE_FONTS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_PRIVATE_FONTS	0
#      endif
#    endif
#    ifndef wxUSE_PRINTING_ARCHITECTURE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_PRINTING_ARCHITECTURE	0
#      endif
#    endif
#    ifndef wxUSE_RADIOBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_RADIOBOX	0
#      endif
#    endif
#    ifndef wxUSE_RADIOBTN
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_RADIOBTN	0
#      endif
#    endif
#    ifndef wxUSE_REARRANGECTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_REARRANGECTRL	0
#      endif
#    endif
#    ifndef wxUSE_RIBBON
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_RIBBON	0
#      endif
#    endif
#    ifndef wxUSE_RICHMSGDLG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_RICHMSGDLG	0
#      endif
#    endif
#    ifndef wxUSE_RICHTOOLTIP
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_RICHTOOLTIP	0
#      endif
#    endif
#    ifndef wxUSE_SASH
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SASH	0
#      endif
#    endif
#    ifndef wxUSE_SCROLLBAR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SCROLLBAR	0
#      endif
#    endif
#    ifndef wxUSE_SLIDER
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SLIDER	0
#      endif
#    endif
#    ifndef wxUSE_SOUND
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SOUND	0
#      endif
#    endif
#    ifndef wxUSE_SPINBTN
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SPINBTN	0
#      endif
#    endif
#    ifndef wxUSE_SPINCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SPINCTRL	0
#      endif
#    endif
#    ifndef wxUSE_SPLASH
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SPLASH	0
#      endif
#    endif
#    ifndef wxUSE_SPLITTER
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_SPLITTER	0
#      endif
#    endif
#    ifndef wxUSE_STATBMP
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_STATBMP	0
#      endif
#    endif
#    ifndef wxUSE_STATBOX
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_STATBOX	0
#      endif
#    endif
#    ifndef wxUSE_STATLINE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_STATLINE	0
#      endif
#    endif
#    ifndef wxUSE_STATTEXT
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_STATTEXT	0
#      endif
#    endif
#    ifndef wxUSE_STATUSBAR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_STATUSBAR	0
#      endif
#    endif
#    ifndef wxUSE_TASKBARICON
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_TASKBARICON	0
#      endif
#    endif
#    ifndef wxUSE_TIMEPICKCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_TIMEPICKCTRL	0
#      endif
#    endif
#    ifndef wxUSE_TIPWINDOW
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_TIPWINDOW	0
#      endif
#    endif
#    ifndef wxUSE_TOOLBAR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_TOOLBAR	0
#      endif
#    endif
#    ifndef wxUSE_TOOLTIPS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_TOOLTIPS	0
#      endif
#    endif
#    ifndef wxUSE_TREECTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_TREECTRL	0
#      endif
#    endif
#    ifndef wxUSE_TREELISTCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_TREELISTCTRL	0
#      endif
#    endif
#    ifndef wxUSE_UIACTIONSIMULATOR
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_UIACTIONSIMULATOR	0
#      endif
#    endif
#    ifndef wxUSE_VALIDATORS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_VALIDATORS	0
#      endif
#    endif
#    ifndef wxUSE_WEBVIEW
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_WEBVIEW	0
#      endif
#    endif
#    ifndef wxUSE_WXHTML_HELP
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_WXHTML_HELP	0
#      endif
#    endif
#    ifndef wxUSE_XRC
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_XRC	0
#      endif
#    endif
#  endif
/*
   Section 2: platform-specific checks.

   This must be done after checking that everything is defined as the platform
   checks use wxUSE_XXX symbols in #if tests.
 */
#  if  defined(__WINDOWS__)
#    include "wx/msw/chkconf.h"
#    if  defined(__WXGTK__)
#      include "wx/gtk/chkconf.h"
#    endif
#  elif  defined(__WXGTK__)
#    include "wx/gtk/chkconf.h"
#  elif  defined(__WXMAC__)
#    include "wx/osx/chkconf.h"
#  elif  defined(__WXDFB__)
#    include "wx/dfb/chkconf.h"
#  elif  defined(__WXMOTIF__)
#    include "wx/motif/chkconf.h"
#  elif  defined(__WXX11__)
#    include "wx/x11/chkconf.h"
#  elif  defined(__WXANDROID__)
#    include "wx/android/chkconf.h"
#  endif
/*
    __UNIX__ is also defined under Cygwin but we shouldn't perform these checks
    there if we're building Windows ports.
 */
#  if  defined(__UNIX__) && !defined(__WINDOWS__)
#    include "wx/unix/chkconf.h"
#  endif
#  ifdef __WXUNIVERSAL__
#    include "wx/univ/chkconf.h"
#  endif
/*
   Section 3a: check consistency of the non-GUI settings.
 */
#  if  wxUSE_ARCHIVE_STREAMS
#  endif
#  if  wxUSE_PROTOCOL_FILE || wxUSE_PROTOCOL_FTP || wxUSE_PROTOCOL_HTTP
#    if  !wxUSE_PROTOCOL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_PROTOCOL
#        define wxUSE_PROTOCOL	1
#      endif
#    endif
#  endif
#  if  wxUSE_URL
#    if  !wxUSE_PROTOCOL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_PROTOCOL
#        define wxUSE_PROTOCOL	1
#      endif
#    endif
#  endif
#  if  wxUSE_PROTOCOL
#    if  !wxUSE_STREAMS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_STREAMS
#        define wxUSE_STREAMS	1
#      endif
#    endif
#  endif
/* have to test for wxUSE_HTML before wxUSE_FILESYSTEM */
#  if  wxUSE_HTML
#    if  !wxUSE_FILESYSTEM
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_FILESYSTEM
#        define wxUSE_FILESYSTEM	1
#      endif
#    endif
#  endif
#  if  wxUSE_FS_ARCHIVE
#    if  !wxUSE_FILESYSTEM
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_FILESYSTEM
#        define wxUSE_FILESYSTEM	1
#      endif
#    endif
#    if  !wxUSE_ARCHIVE_STREAMS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_ARCHIVE_STREAMS
#        define wxUSE_ARCHIVE_STREAMS	1
#      endif
#    endif
#  endif
#  if  wxUSE_FILESYSTEM
#    if  !wxUSE_STREAMS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_STREAMS
#        define wxUSE_STREAMS	1
#      endif
#    endif
#    if  !wxUSE_FILE && !wxUSE_FFILE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_FILE
#        define wxUSE_FILE	1
#        undef wxUSE_FFILE
#        define wxUSE_FFILE	1
#      endif
#    endif
#  endif
#  if  wxUSE_FS_INET
#    if  !wxUSE_PROTOCOL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_PROTOCOL
#        define wxUSE_PROTOCOL	1
#      endif
#    endif
#  endif
#  if  wxUSE_STOPWATCH || wxUSE_DATETIME
#    if  !wxUSE_LONGLONG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_LONGLONG
#        define wxUSE_LONGLONG	1
#      endif
#    endif
#  endif
#  if  wxUSE_MIMETYPE && !wxUSE_TEXTFILE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      undef wxUSE_TEXTFILE
#      define wxUSE_TEXTFILE	1
#    endif
#  endif
#  if  wxUSE_TEXTFILE && !wxUSE_TEXTBUFFER
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      undef wxUSE_TEXTBUFFER
#      define wxUSE_TEXTBUFFER	1
#    endif
#  endif
#  if  wxUSE_TEXTFILE && !wxUSE_FILE
#    ifdef wxABORT_ON_CONFIG_ERROR
#    else 
#      undef wxUSE_FILE
#      define wxUSE_FILE	1
#    endif
#  endif
#  if  !wxUSE_DYNLIB_CLASS
#    if  wxUSE_DYNAMIC_LOADER
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        define wxUSE_DYNLIB_CLASS	1
#      endif
#    endif
#  endif
#  if  wxUSE_ZIPSTREAM
#    if  !wxUSE_ZLIB
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_ZLIB
#        define wxUSE_ZLIB	1
#      endif
#    endif
#    if  !wxUSE_ARCHIVE_STREAMS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_ARCHIVE_STREAMS
#        define wxUSE_ARCHIVE_STREAMS	1
#      endif
#    endif
#  endif
#  if  wxUSE_TARSTREAM
#    if  !wxUSE_ARCHIVE_STREAMS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_ARCHIVE_STREAMS
#        define wxUSE_ARCHIVE_STREAMS	1
#      endif
#    endif
#  endif
/*
   Section 3b: the tests for the GUI settings only.
 */
#  if  wxUSE_GUI
#    if  wxUSE_ACCESSIBILITY && !defined(__WXMSW__)
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_ACCESSIBILITY
#        define wxUSE_ACCESSIBILITY	0
#      endif
#    endif
#    if  wxUSE_BUTTON || \
    wxUSE_CALENDARCTRL || \
    wxUSE_CARET || \
    wxUSE_COMBOBOX || \
    wxUSE_BMPBUTTON || \
    wxUSE_CHECKBOX || \
    wxUSE_CHECKLISTBOX || \
    wxUSE_CHOICE || \
    wxUSE_GAUGE || \
    wxUSE_GRID || \
    wxUSE_HEADERCTRL || \
    wxUSE_LISTBOX || \
    wxUSE_LISTCTRL || \
    wxUSE_NOTEBOOK || \
    wxUSE_RADIOBOX || \
    wxUSE_RADIOBTN || \
    wxUSE_REARRANGECTRL || \
    wxUSE_SCROLLBAR || \
    wxUSE_SLIDER || \
    wxUSE_SPINBTN || \
    wxUSE_SPINCTRL || \
    wxUSE_STATBMP || \
    wxUSE_STATBOX || \
    wxUSE_STATLINE || \
    wxUSE_STATTEXT || \
    wxUSE_STATUSBAR || \
    wxUSE_TEXTCTRL || \
    wxUSE_TOOLBAR || \
    wxUSE_TREECTRL || \
    wxUSE_TREELISTCTRL
#      if  !wxUSE_CONTROLS
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_CONTROLS
#          define wxUSE_CONTROLS	1
#        endif
#      endif
#    endif
#    if  wxUSE_ADDREMOVECTRL
#      if  !wxUSE_BMPBUTTON
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_ADDREMOVECTRL
#          define wxUSE_ADDREMOVECTRL	0
#        endif
#      endif
#    endif
#    if  wxUSE_ANIMATIONCTRL
#      if  !wxUSE_STREAMS
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_ANIMATIONCTRL
#          define wxUSE_ANIMATIONCTRL	0
#        endif
#      endif
#    endif
#    if  wxUSE_BMPBUTTON
#      if  !wxUSE_BUTTON
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_BUTTON
#          define wxUSE_BUTTON	1
#        endif
#      endif
#    endif
#    if  wxUSE_COMMANDLINKBUTTON
#      if  !wxUSE_BUTTON
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_BUTTON
#          define wxUSE_BUTTON	1
#        endif
#      endif
#    endif
/*
   wxUSE_BOOKCTRL should be only used if any of the controls deriving from it
   are used
 */
#    ifdef wxUSE_BOOKCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_BOOKCTRL
#      endif
#    endif
#    define wxUSE_BOOKCTRL(wxUSE_AUI || \
                        wxUSE_NOTEBOOK || \
                        wxUSE_LISTBOOK || \
                        wxUSE_CHOICEBOOK || \
                        wxUSE_TOOLBOOK || \
                        wxUSE_TREEBOOK)
#    if  wxUSE_COLLPANE
#      if  !wxUSE_BUTTON || !wxUSE_STATLINE
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_COLLPANE
#          define wxUSE_COLLPANE	0
#        endif
#      endif
#    endif
#    if  wxUSE_LISTBOOK
#      if  !wxUSE_LISTCTRL
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LISTCTRL
#          define wxUSE_LISTCTRL	1
#        endif
#      endif
#    endif
#    if  wxUSE_CHOICEBOOK
#      if  !wxUSE_CHOICE
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_CHOICE
#          define wxUSE_CHOICE	1
#        endif
#      endif
#    endif
#    if  wxUSE_TOOLBOOK
#      if  !wxUSE_TOOLBAR
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_TOOLBAR
#          define wxUSE_TOOLBAR	1
#        endif
#      endif
#    endif
#    if  !wxUSE_ODCOMBOBOX
#      if  wxUSE_BITMAPCOMBOBOX
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_BITMAPCOMBOBOX
#          define wxUSE_BITMAPCOMBOBOX	0
#        endif
#      endif
#    endif
#    if  !wxUSE_HEADERCTRL
#      if  wxUSE_DATAVIEWCTRL || wxUSE_GRID
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_HEADERCTRL
#          define wxUSE_HEADERCTRL	1
#        endif
#      endif
#    endif
#    if  wxUSE_REARRANGECTRL
#      if  !wxUSE_CHECKLISTBOX
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_REARRANGECTRL
#          define wxUSE_REARRANGECTRL	0
#        endif
#      endif
#    endif
#    if  wxUSE_RICHMSGDLG
#      if  !wxUSE_MSGDLG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_MSGDLG
#          define wxUSE_MSGDLG	1
#        endif
#      endif
#    endif
/* don't attempt to use native status bar on the platforms not having it */
#    ifndef wxUSE_NATIVE_STATUSBAR
#      define wxUSE_NATIVE_STATUSBAR	0
#    elif  wxUSE_NATIVE_STATUSBAR
#      if  defined(__WXUNIVERSAL__) || !(defined(__WXMSW__) || defined(__WXMAC__))
#        undef wxUSE_NATIVE_STATUSBAR
#        define wxUSE_NATIVE_STATUSBAR	0
#      endif
#    endif
#    if  wxUSE_ACTIVITYINDICATOR && !wxUSE_GRAPHICS_CONTEXT
#      undef wxUSE_ACTIVITYINDICATOR
#      define wxUSE_ACTIVITYINDICATOR	0
#    endif
#    if  wxUSE_GRAPHICS_CONTEXT && !wxUSE_GEOMETRY
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_GRAPHICS_CONTEXT
#        define wxUSE_GRAPHICS_CONTEXT	0
#      endif
#    endif
#    if  wxUSE_DC_TRANSFORM_MATRIX && !wxUSE_GEOMETRY
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_DC_TRANSFORM_MATRIX
#        define wxUSE_DC_TRANSFORM_MATRIX	0
#      endif
#    endif
/* generic controls dependencies */
#    if  !defined(__WXMSW__) || defined(__WXUNIVERSAL__)
#      if  wxUSE_FONTDLG || wxUSE_FILEDLG || wxUSE_CHOICEDLG
        /* all common controls are needed by these dialogs */
#        if  !defined(wxUSE_CHOICE) || \
           !defined(wxUSE_TEXTCTRL) || \
           !defined(wxUSE_BUTTON) || \
           !defined(wxUSE_CHECKBOX) || \
           !defined(wxUSE_STATTEXT)
#          ifdef wxABORT_ON_CONFIG_ERROR
#          else 
#            undef wxUSE_CHOICE
#            define wxUSE_CHOICE	1
#            undef wxUSE_TEXTCTRL
#            define wxUSE_TEXTCTRL	1
#            undef wxUSE_BUTTON
#            define wxUSE_BUTTON	1
#            undef wxUSE_CHECKBOX
#            define wxUSE_CHECKBOX	1
#            undef wxUSE_STATTEXT
#            define wxUSE_STATTEXT	1
#          endif
#        endif
#      endif
#    endif
/* generic file dialog depends on (generic) file control */
#    if  wxUSE_FILEDLG && !wxUSE_FILECTRL && \
        (defined(__WXUNIVERSAL__) || defined(__WXGTK__))
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_FILECTRL
#        define wxUSE_FILECTRL	1
#      endif
#    endif
/* common dependencies */
#    if  wxUSE_ARTPROVIDER_TANGO
#      if  !(wxUSE_STREAMS && wxUSE_IMAGE && wxUSE_LIBPNG)
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_ARTPROVIDER_TANGO
#          define wxUSE_ARTPROVIDER_TANGO	0
#        endif
#      endif
#    endif
#    if  wxUSE_CALENDARCTRL
#      if  !(wxUSE_SPINBTN && wxUSE_COMBOBOX)
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_SPINBTN
#          undef wxUSE_COMBOBOX
#          define wxUSE_SPINBTN	1
#          define wxUSE_COMBOBOX	1
#        endif
#      endif
#    endif
#    if  wxUSE_DATEPICKCTRL
    /* Only the generic implementation, not used under MSW and OSX, needs
     * wxComboCtrl. */
#      if  !wxUSE_COMBOCTRL && (defined(__WXUNIVERSAL__) || \
            !(defined(__WXMSW__) || defined(__WXOSX_COCOA__)))
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_COMBOCTRL
#          define wxUSE_COMBOCTRL	1
#        endif
#      endif
#    endif
#    if  wxUSE_DATEPICKCTRL || wxUSE_TIMEPICKCTRL
#    endif
#    if  wxUSE_CHECKLISTBOX
#      if  !wxUSE_LISTBOX
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LISTBOX
#          define wxUSE_LISTBOX	1
#        endif
#      endif
#    endif
#    if  wxUSE_CHOICEDLG
#      if  !wxUSE_LISTBOX
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LISTBOX
#          define wxUSE_LISTBOX	1
#        endif
#      endif
#    endif
#    if  wxUSE_FILECTRL
#    endif
#    if  wxUSE_HELP
#      if  !wxUSE_BMPBUTTON
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_BMPBUTTON
#          define wxUSE_BMPBUTTON	1
#        endif
#      endif
#      if  !wxUSE_CHOICEDLG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_CHOICEDLG
#          define wxUSE_CHOICEDLG	1
#        endif
#      endif
#    endif
#    if  wxUSE_MS_HTML_HELP
    /*
        this doesn't make sense for platforms other than MSW but we still
        define it in wx/setup_inc.h so don't complain if it happens to be
        defined under another platform but just silently fix it.
     */
#      ifndef __WXMSW__
#        undef wxUSE_MS_HTML_HELP
#        define wxUSE_MS_HTML_HELP	0
#      endif
#    endif
#    if  wxUSE_WXHTML_HELP
#      if  !wxUSE_HELP || !wxUSE_HTML || !wxUSE_COMBOBOX || !wxUSE_NOTEBOOK || !wxUSE_SPINCTRL
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_HELP
#          define wxUSE_HELP	1
#          undef wxUSE_HTML
#          define wxUSE_HTML	1
#          undef wxUSE_COMBOBOX
#          define wxUSE_COMBOBOX	1
#          undef wxUSE_NOTEBOOK
#          define wxUSE_NOTEBOOK	1
#          undef wxUSE_SPINCTRL
#          define wxUSE_SPINCTRL	1
#        endif
#      endif
#    endif
#    if  !wxUSE_IMAGE
/*
   The default wxUSE_IMAGE setting is 1, so if it's set to 0 we assume the
   user explicitly wants this and disable all other features that require
   wxUSE_IMAGE.
 */
#      if  wxUSE_DRAGIMAGE
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_DRAGIMAGE
#          define wxUSE_DRAGIMAGE	0
#        endif
#      endif
#      if  wxUSE_LIBPNG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LIBPNG
#          define wxUSE_LIBPNG	0
#        endif
#      endif
#      if  wxUSE_LIBJPEG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LIBJPEG
#          define wxUSE_LIBJPEG	0
#        endif
#      endif
#      if  wxUSE_LIBTIFF
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LIBTIFF
#          define wxUSE_LIBTIFF	0
#        endif
#      endif
#      if  wxUSE_GIF
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_GIF
#          define wxUSE_GIF	0
#        endif
#      endif
#      if  wxUSE_PNM
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_PNM
#          define wxUSE_PNM	0
#        endif
#      endif
#      if  wxUSE_PCX
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_PCX
#          define wxUSE_PCX	0
#        endif
#      endif
#      if  wxUSE_IFF
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_IFF
#          define wxUSE_IFF	0
#        endif
#      endif
#      if  wxUSE_TOOLBAR
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_TOOLBAR
#          define wxUSE_TOOLBAR	0
#        endif
#      endif
#      if  wxUSE_XPM
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_XPM
#          define wxUSE_XPM	0
#        endif
#      endif
#    endif
#    if  wxUSE_DOC_VIEW_ARCHITECTURE
#      if  !wxUSE_MENUS
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_MENUS
#          define wxUSE_MENUS	1
#        endif
#      endif
#      if  !wxUSE_CHOICEDLG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_CHOICEDLG
#          define wxUSE_CHOICEDLG	1
#        endif
#      endif
#      if  !wxUSE_STREAMS && !wxUSE_STD_IOSTREAM
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_STREAMS
#          define wxUSE_STREAMS	1
#        endif
#      endif
#      if  !wxUSE_FILE_HISTORY
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_FILE_HISTORY
#          define wxUSE_FILE_HISTORY	1
#        endif
#      endif
#    endif
#    if  wxUSE_PRINTING_ARCHITECTURE
#      if  !wxUSE_COMBOBOX
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_COMBOBOX
#          define wxUSE_COMBOBOX	1
#        endif
#      endif
#    endif
#    if  wxUSE_MDI_ARCHITECTURE
#      if  !wxUSE_MDI
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_MDI
#          define wxUSE_MDI	1
#        endif
#      endif
#      if  !wxUSE_DOC_VIEW_ARCHITECTURE
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_DOC_VIEW_ARCHITECTURE
#          define wxUSE_DOC_VIEW_ARCHITECTURE	1
#        endif
#      endif
#    endif
#    if  !wxUSE_FILEDLG
#      if  wxUSE_DOC_VIEW_ARCHITECTURE || wxUSE_WXHTML_HELP
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_FILEDLG
#          define wxUSE_FILEDLG	1
#        endif
#      endif
#    endif
#    if  !wxUSE_GAUGE || !wxUSE_BUTTON
#      if  wxUSE_PROGRESSDLG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_GAUGE
#          undef wxUSE_BUTTON
#          define wxUSE_GAUGE	1
#          define wxUSE_BUTTON	1
#        endif
#      endif
#    endif
#    if  !wxUSE_BUTTON
#      if  wxUSE_FONTDLG || \
       wxUSE_FILEDLG || \
       wxUSE_CHOICEDLG || \
       wxUSE_NUMBERDLG || \
       wxUSE_TEXTDLG || \
       wxUSE_DIRDLG || \
       wxUSE_STARTUP_TIPS || \
       wxUSE_WIZARDDLG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_BUTTON
#          define wxUSE_BUTTON	1
#        endif
#      endif
#    endif
#    if  !wxUSE_TOOLBAR
#      if  wxUSE_TOOLBAR_NATIVE
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_TOOLBAR_NATIVE
#          define wxUSE_TOOLBAR_NATIVE	0
#        endif
#      endif
#    endif
#    if  !wxUSE_IMAGLIST
#      if  wxUSE_TREECTRL || wxUSE_NOTEBOOK || wxUSE_LISTCTRL || wxUSE_TREELISTCTRL
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_IMAGLIST
#          define wxUSE_IMAGLIST	1
#        endif
#      endif
#    endif
#    if  wxUSE_RADIOBOX
#      if  !wxUSE_RADIOBTN
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_RADIOBTN
#          define wxUSE_RADIOBTN	1
#        endif
#      endif
#      if  !wxUSE_STATBOX
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_STATBOX
#          define wxUSE_STATBOX	1
#        endif
#      endif
#    endif
#    if  wxUSE_LOGWINDOW
#    endif
#    if  wxUSE_LOG_DIALOG
#      if  !wxUSE_LISTCTRL || !wxUSE_BUTTON
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LISTCTRL
#          define wxUSE_LISTCTRL	1
#          undef wxUSE_BUTTON
#          define wxUSE_BUTTON	1
#        endif
#      endif
#    endif
#    if  wxUSE_CLIPBOARD && !wxUSE_DATAOBJ
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_DATAOBJ
#        define wxUSE_DATAOBJ	1
#      endif
#    endif
#    if  wxUSE_XRC && !wxUSE_XML
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_XRC
#        define wxUSE_XRC	0
#      endif
#    endif
#    if  wxUSE_SOCKETS && !wxUSE_STOPWATCH
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_SOCKETS
#        define wxUSE_SOCKETS	0
#      endif
#    endif
#    if  wxUSE_SVG && !wxUSE_STREAMS
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_SVG
#        define wxUSE_SVG	0
#      endif
#    endif
#    if  wxUSE_SVG && !wxUSE_IMAGE
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_SVG
#        define wxUSE_SVG	0
#      endif
#    endif
#    if  wxUSE_SVG && !wxUSE_LIBPNG
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_SVG
#        define wxUSE_SVG	0
#      endif
#    endif
#    if  !wxUSE_MENUS
#      if  wxUSE_MENUBAR
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_MENUBAR
#          define wxUSE_MENUBAR	0
#        endif
#      endif
#      if  wxUSE_TASKBARICON
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_TASKBARICON
#          define wxUSE_TASKBARICON	0
#        endif
#      endif
#    endif
#    if  !wxUSE_VARIANT
#      if  wxUSE_DATAVIEWCTRL
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_DATAVIEWCTRL
#          define wxUSE_DATAVIEWCTRL	0
#        endif
#      endif
#    endif
#    if  wxUSE_TREELISTCTRL && !wxUSE_DATAVIEWCTRL
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_TREELISTCTRL
#        define wxUSE_TREELISTCTRL	0
#      endif
#    endif
#    if  wxUSE_WEBVIEW && !(wxUSE_WEBVIEW_WEBKIT || wxUSE_WEBVIEW_WEBKIT2 || \
                       wxUSE_WEBVIEW_IE || wxUSE_WEBVIEW_EDGE)
#      ifdef wxABORT_ON_CONFIG_ERROR
#      else 
#        undef wxUSE_WEBVIEW
#        define wxUSE_WEBVIEW	0
#      endif
#    endif
#    if  wxUSE_PREFERENCES_EDITOR
    /*
        We can use either a generic implementation, using wxNotebook, or a
        native one under wxOSX/Cocoa but then we must be using the native
        toolbar.
    */
#      if  !wxUSE_NOTEBOOK
#        ifdef __WXOSX_COCOA__
#          if  !wxUSE_TOOLBAR || !wxOSX_USE_NATIVE_TOOLBAR
#            ifdef wxABORT_ON_CONFIG_ERROR
#            else 
#              undef wxUSE_PREFERENCES_EDITOR
#              define wxUSE_PREFERENCES_EDITOR	0
#            endif
#          endif
#        else 
#          ifdef wxABORT_ON_CONFIG_ERROR
#          else 
#            undef wxUSE_PREFERENCES_EDITOR
#            define wxUSE_PREFERENCES_EDITOR	0
#          endif
#        endif
#      endif
#    endif
#    if  wxUSE_PRIVATE_FONTS
#      if  !defined(__WXMSW__) && !defined(__WXGTK__) && !defined(__WXOSX__)
#        undef wxUSE_PRIVATE_FONTS
#        define wxUSE_PRIVATE_FONTS	0
#      endif
#    endif
#    if  wxUSE_MEDIACTRL
#      if  !wxUSE_LONGLONG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LONLONG
#          define wxUSE_LONLONG	1
#        endif
#      endif
#    endif
#    if  wxUSE_STC
#      if  !wxUSE_STOPWATCH
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_STC
#          define wxUSE_STC	0
#        endif
#      endif
#      if  !wxUSE_SCROLLBAR
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_STC
#          define wxUSE_STC	0
#        endif
#      endif
#    endif
#    if  wxUSE_RICHTEXT
#      if  !wxUSE_HTML
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_RICHTEXT
#          define wxUSE_RICHTEXT	0
#        endif
#      endif
#      if  !wxUSE_LONGLONG
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_LONLONG
#          define wxUSE_LONLONG	1
#        endif
#      endif
#      if  !wxUSE_VARIANT
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_VARIANT
#          define wxUSE_VARIANT	1
#        endif
#      endif
#    endif
#    if  wxUSE_RICHTOOLTIP
#      if  !wxUSE_POPUPWIN
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_POPUPWIN
#          define wxUSE_POPUPWIN	1
#        endif
#      endif
#    endif
#    if  wxUSE_PROPGRID
#      if  !wxUSE_VARIANT
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_VARIANT
#          define wxUSE_VARIANT	1
#        endif
#      endif
#    endif
#    if  wxUSE_TIPWINDOW
#      if  !wxUSE_POPUPWIN
#        ifdef wxABORT_ON_CONFIG_ERROR
#        else 
#          undef wxUSE_POPUPWIN
#          define wxUSE_POPUPWIN	1
#        endif
#      endif
#    endif
#  endif
#endif
