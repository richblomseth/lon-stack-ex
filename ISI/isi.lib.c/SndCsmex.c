//	SndCsmex.c	implementing _IsiSendCsmx
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, February 2005, Bernd Gauweiler
//

#include "isi_int.h"

void _IsiSendCsmex(LonBool RequireHost, IsiMessageCode Code, unsigned Repeats) 
{
	const IsiConnection *pConnection;

    _IsiAPIDebug("Start _IsiSendCsmex - PendingConnection=%d\n", _isiVolatile.pendingConnection);
    if (_isiVolatile.pendingConnection != ISI_NO_INDEX)
    {
        pConnection = IsiGetConnection(_isiVolatile.pendingConnection);
        if (!RequireHost || (pConnection->Host != ISI_NO_ASSEMBLY)) {
            _IsiSendCsmX(pConnection, Code, Repeats);
        }
    }
    _IsiAPIDebug("End _IsiSendCsmex\n");
}

//	end of SndCsmx.c
