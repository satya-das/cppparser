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

#include "adesk.h"
#include "acdbport.h"
#include "mgdhost-core2d.h"

#ifndef MGDHOST_H
#define MGDHOST_H 1
#pragma once

ACDB_PORT HRESULT ADESK_STDCALL acdbInitializeManagedLayer();
ACDB_PORT HRESULT ADESK_STDCALL acdbTerminateManagedLayer();


#endif /* MGDHOST_H */
