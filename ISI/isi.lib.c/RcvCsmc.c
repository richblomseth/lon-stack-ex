//	RcvCsmc.c	implementing _IsiReceiveCsmc
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//	Revision 0, February 2005, Bernd Gauweiler

#include "isi_int.h"

void _IsiReceiveCsmc(const IsiCsmc* pCsmc)
{
	const IsiConnection *pConnection;
    LonByte connectionState, connectionExtend;

    _IsiAPIDebug("_IsiReceiveCsmc ");
    _IsiAPIDump("0x", (void *)pCsmc, sizeof(IsiCsmc), "\n");

    if (_isiVolatile.State != isiStateAccepted)
    {
        // the CSMC didn't really apply to us. It seems we were still pending for a different connection,
        // maybe because we missed a number of messages...? Let's call _IsiReceiveCsmx(), just to clear out
        // the state.
        _IsiReceiveCsmx(pCsmc);
    }
    else
    {
        // search the connection table. This time we are looking for the first not-hosted but pending entry.
        // Take the extend flag and assembly number from there, and implement the darn thing:
        pConnection = IsiGetConnection(_isiVolatile.pendingConnection);
        connectionState = LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_STATE);       
        if (pConnection->Member != ISI_NO_ASSEMBLY
            && connectionState == isiConnectionStatePending
            && !memcmp(&pConnection->Header.Cid, &pCsmc->Cid, (unsigned)sizeof(IsiCid)))
        {
            // this connection table entry is one that refers to a remotely hosted connection (we are just a plain member):
            connectionExtend = LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_EXTEND);
            _IsiImplementEnrollment(connectionExtend, pConnection->Member);
        }
    }
}

//	end of RcvCsmc.c
