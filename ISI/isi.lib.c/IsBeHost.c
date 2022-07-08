//	IsBeHost.c	implementing IsiIsBecomingHost
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"
#include <stddef.h>

LonBool IsiIsBecomingHost(unsigned Assembly)
{
	const IsiConnection *pConnection;
    LonBool b = FALSE;

    _IsiAPIDebug("Start IsiIsBecomingHost - Assembly=%d State=%d\n", Assembly,
        _isiVolatile.State);
	if (_isiVolatile.State & HOST_STATES)
    {
		// we are about to become a host. is it this assembly?
        pConnection = IsiGetConnection(_isiVolatile.pendingConnection);
        b = pConnection->Host == Assembly && LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_STATE) == isiConnectionStatePending;
	}
    _IsiAPIDebug("End IsiIsBecomingHost - Retval=%d\n", b);
	return b;
}

//	end of IsBeHost.c
