/*
 * wx/setup.h
 *
 * This file should not normally be used, except where makefiles
 * have not yet been adjusted to take into account of the new scheme
 * whereby a setup.h is created under the lib directory.
 *
 * Copyright:   (c) Vadim Zeitlin
 * Licence:     wxWindows Licence
 */
#ifdef __WXMSW__
#  include "wx/msw/setup.h"
#else 
#  undef error Please adjust your include path to pick up the wx/setup.h file under lib first.

#endif
