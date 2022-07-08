//	Tcsmr.c	implementing _IsiTcsmr. The routine maintains the Tcsmr timer and takes
//  action upon expiry.
//
//  A device supporting automatic connections and ISI-DA or ISI-DAS is supposed to monitor
//  DIDCF messages, and Tcsmr after receiving a Tcsmr message, to broadcast all CSMR messages -
//  the idea is to speed up the automatic connection process when a new device is registered on
//  the domain. To do so, each ISI-DA(S) device receiving a DIDCF flags all automatic, locally
//  hosted, connections with that new state. Whenever the regular broadcaster sends a CSMR, it
//  resets this connections's state to isiConnectionStateInUse. When the Tcsmr timer expires
//  following the receipt of a DIDCF, the TickDA and TickDas routines broadcast each remaining
//  CSMR.
//
//
// Copyright (c) 2005-2014 Echelon Corporation.  All rights reserved.
// Use of this code is subject to your compliance with the terms of the
// Echelon IzoT(tm) Software Developer's Kit License Agreement which is
// available at www.echelon.com/license/izot_sdk/.
//
//
//	Revision 0, July 2005, Bernd Gauweiler

#include "isi_int.h"

unsigned long   _isiTcsmr;

//  _IsiTcsmr maintains the Tcsmr timer and takes action upon expiry. Also called from
void _IsiTcsmr(void)
{
    unsigned index;
    const IsiConnection* pConnection;
    
    if (_isiTcsmr == 1)
    {
        _IsiAPIDebug("Start _IsiTcsmr - Timer is expired\n");

        // iterate through the connection table and send a CSMR for each entry that is still scheduled.
        // It would be madness to send all CSMR in one blast. Instead, we clear the timer if no CSMR was
        // send at all (so that we don't enter that loop at the next tick again). Whenever we do find
        // a CSMR that needs broadcasting, we send just this one, and keep the timer at 1 (indicating
        // expiry). Thus, at the next tick (250ms later) we process the next CSMR. This allows to
        // broadcast all scheduled CSMR messages quickly but not too closely.
        for (index = 0; index < _isiVolatile.ConnectionTableSize; ++index)
        {
            pConnection = IsiGetConnection(index);
            if (pConnection->Desc.OffsetAuto == ConnectionAuto_MASK && 
                LON_GET_ATTRIBUTE_P(pConnection,ISI_CONN_STATE) == isiConnectionStateTcsmr &&
                    pConnection->Host != ISI_NO_ASSEMBLY)
            {
                // This connection table entry is in use, in the Tcsmr state, is automatic, locally hosted, and has an offset of zero into the entire connection
                // _IsiSendCsmr issues the CSMR and resets the state to isiConnectionStateInUse
                _IsiSendCsmr(index, pConnection);
                // Bail out without clearing the timer. There might be more scheduled messages awaiting
                // delivery; check for those with the next tick:
                return;
            }
        }
        // no CSMR has been send, so let's clear this timer and indicate that this business is over:
        _isiTcsmr = 0;  // stop the timer

        _IsiAPIDebug("End _IsiTcsmr - Timer=%ld\n", _isiTcsmr);
    } 
    else if (_isiTcsmr)
    {
        // timer still ticking:
        --_isiTcsmr;
    }
}

//	end of Tcsmr.c
